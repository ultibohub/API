/*
 *
 * Time Date example project for Ultibo API
 *
 * The Raspberry Pi has no real time clock built in to the board so the normal
 * way to get the correct time is from an internet time server.
 *
 * In this example the network will be started and an IP address obtained from
 * DHCP, once that has happened the time will be obtained via NTP.
 *
 *
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Garry Wood <garry@softoz.com.au>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"
#include "ultibo/ultibo.h"

int apimain(int argc, char **argv)
{
  time_t utctime;
  struct tm *info;
  char value[512];
  char buffer[256];
  uint32_t counter;
  WINDOW_HANDLE windowhandle;

  /* Create a console window at full size */
  windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);

  /* Output some welcome text on the console window */
  console_window_write_ln(windowhandle, "Welcome to Example 05 Date Time");
  console_window_write_ln(windowhandle, "Waiting for network address to be configured and NTP time synchronisation to occur");

  /* Print out the current time and date */
  /* This will probably show sometime in 1970, this is the start of C time */
  time(&utctime);
  info = localtime(&utctime);
  sprintf(value, "The current date and time is %s", asctime(info));
  console_window_write_ln(windowhandle, value);

  /* Initialize a variable so we can count how long we've been waiting */
  counter = 0;

  /* Let's wait for a while for the time to be updated (tm_year is years since 1900) */
  while (info->tm_year < 100) {
    
    /* Sleep for a second */
    sleep(1);

    /* Update our counter */
    counter++;

    /* Check how long we have waited */
    if (counter > 90) {

      /* Print a failure message on the console */
      console_window_write_ln(windowhandle, "Sorry, failed to get the time after 90 seconds. Is the network connected?");

      /* Break out of the loop and continue */
      break;
    }

    /* Get the time again */
    time(&utctime);
    info = localtime(&utctime);
  }

  /* Check our counter to see if we got here by success or failure */
  if (counter <= 90) {

    /* We must have been successful so let's print the date and time again */
    console_window_write_ln(windowhandle, "Success, time has been updated from the internet");
    time(&utctime);
    info = localtime(&utctime);
    sprintf(value, "The date and time is now %s", asctime(info));
    console_window_write_ln(windowhandle, value);

    /* How about showing the date and time in some different ways? */
    /* Time only */
    strftime(value, sizeof(value), "Time is %X", info);
    console_window_write_ln(windowhandle, value);

    /* Date only */
    strftime(value, sizeof(value), "Date is %x", info);
    console_window_write_ln(windowhandle, value);

    /* Date and Time formatted to the long format */
    strftime(value, sizeof(value), "Formatted Date and Time is %c", info);
    console_window_write_ln(windowhandle, value);
    console_window_write_ln(windowhandle, "");

    /* Unless you live in certain parts of the world then the dates and times shown might not seem correct */
    /* Let's print the timezone to see what it is set to */
    if (GetCurrentTimezone(buffer, sizeof(buffer)) <= sizeof(buffer))
    {
      sprintf(value, "Timezone is %s", buffer);
      console_window_write_ln(windowhandle, value);
    }

    /* Now we can set the timezone to another place and see what the time is there */
    /* Australia */
    console_window_write_ln(windowhandle, "Setting Timezone to \"AUS Eastern Standard Time\"");
    SetCurrentTimezone("AUS Eastern Standard Time");
    time(&utctime);
    info = localtime(&utctime);
    strftime(value, sizeof(value), "The date and time is now %c", info);
    console_window_write_ln(windowhandle, value);
    console_window_write_ln(windowhandle, "");
    
    /* North America */
    console_window_write_ln(windowhandle, "Setting Timezone to \"Central Standard Time\"");
    SetCurrentTimezone("Central Standard Time");
    time(&utctime);
    info = localtime(&utctime);
    strftime(value, sizeof(value), "The date and time is now %c", info);
    console_window_write_ln(windowhandle, value);
    console_window_write_ln(windowhandle, "");

    /* India */
    console_window_write_ln(windowhandle, "Setting Timezone to \"India Standard Time\"");
    SetCurrentTimezone("India Standard Time");
    time(&utctime);
    info = localtime(&utctime);
    strftime(value, sizeof(value), "The date and time is now %c", info);
    console_window_write_ln(windowhandle, value);
    console_window_write_ln(windowhandle, "");

    /* Western Europe */
    console_window_write_ln(windowhandle, "Setting Timezone to \"W. Europe Standard Time\"");
    SetCurrentTimezone("W. Europe Standard Time");
    time(&utctime);
    info = localtime(&utctime);
    strftime(value, sizeof(value), "The date and time is now %c", info);
    console_window_write_ln(windowhandle, value);
    console_window_write_ln(windowhandle, "");

    /* That's it for example 05, try out example 06 next */
  }

  /* Halt this thread, the example is done */
  thread_halt(0);

  return 0;
}
