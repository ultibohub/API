/*
 *
 * Multi CPU example project for Ultibo API
 *
 * Multi CPU is a fundamental part of the design of Ultibo. It does not need
 * to be enabled and while you can change some configuration it is generally
 * just there whenever the target board has more than one CPU.
 *
 * In this example we'll look at some of the multi CPU information available
 * in Ultibo.
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
#include <stdlib.h>
#include <stdbool.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"
#include "ultibo/ultibo.h"

int apimain(int argc, char **argv)
{
  char description[256], value[512];
  int count, loops;
  WINDOW_HANDLE windowhandle;

  /* Create our window */
  windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);

  /* Output the message */
  console_window_write_ln(windowhandle, "Welcome to Example 11 Multi CPU");
  console_window_write_ln(windowhandle, "");

  /* First print some basic information */
  sprintf(value, "CPU Count is %d", (int)cpu_get_count());
  console_window_write_ln(windowhandle, value);
  
  sprintf(value, "Boot CPU is %d", (int)cpu_get_boot());
  console_window_write_ln(windowhandle, value);
  
  sprintf(value, "Current CPU is %d", (int)cpu_get_current());
  console_window_write_ln(windowhandle, value);
  
  cpu_get_description(description, sizeof(description));
  sprintf(value, "CPU Description is %s", description);
  console_window_write_ln(windowhandle, value);
  
  sprintf(value, "Total thread count is %d", (int)thread_get_count());
  console_window_write_ln(windowhandle, value);
  console_window_write_ln(windowhandle, "");
  
  /* Let's do an endless loop and print some information each time */
  loops = 0;
  while (true)
  {
    /* To get the utilization for each CPU we need to call cpu_get_percentage(),
     * but we need to call it once for each CPU in the system. So we'll use a
     * loop to count from 0 to the number of CPUs minus 1
     */
    console_window_write_ex(windowhandle, "CPU Utilization:", 1, 9, console_window_get_forecolor(windowhandle), console_window_get_backcolor(windowhandle));
    for (count = 0; count < cpu_get_count(); count++)
    {
      /* Check if this CPU is the one we are running on */
      if (count != cpu_get_current())
      {
        /* Get the utilization and write it to the screen using console_window_write_ex()
         * so we can control where it goes
         */
        sprintf(value, " CPU%d %.2f%%   ", count, cpu_get_percentage(count));
        console_window_write_ex(windowhandle, value, 1, 10 + count, console_window_get_forecolor(windowhandle), console_window_get_backcolor(windowhandle));
      }
      else
      {
        /* Get the utilization and write it to the screen but set the color to raspberry
         * so we can see which CPU is ours
         */
        sprintf(value, " CPU%d %.2f%%   ", count, cpu_get_percentage(count));
        console_window_write_ex(windowhandle, value, 1, 10 + count, COLOR_RASPBERRY, console_window_get_backcolor(windowhandle));
      }
    }

    /* We can also get the ready thread count for each CPU to see what is queued for
     * the scheduler to run. Again we loop through each CPU and write it to the screen
     */
    console_window_write_ex(windowhandle, "Ready Thread count:", 1, 14, console_window_get_forecolor(windowhandle), console_window_get_backcolor(windowhandle));
    for (count = 0; count < cpu_get_count(); count++)
    {
      /* The scheduler_get_thread_count() function returns the number of ready threads on each
       * CPU. Ready threads are those that could run immediately and doesn't include threads
       * that are waiting, sleeping or already running
       */
      sprintf(value, " CPU%d %d   ", count, (int)scheduler_get_thread_count(count));
      console_window_write_ex(windowhandle, value, 1, 15 + count, console_window_get_forecolor(windowhandle), console_window_get_backcolor(windowhandle));
    }
      
    /* Let's do the scheduler thread quantum as well which determines how long each
     * thread gets to run before another thread is scheduled
     */
    console_window_write_ex(windowhandle, "Scheduler Thread quantum:", 1, 19, console_window_get_forecolor(windowhandle), console_window_get_backcolor(windowhandle));
    for (count = 0; count < cpu_get_count(); count++)
    {
      /* The scheduler_get_thread_quantum() function returns the number of scheduler ticks
       * remaining before the currently running thread will be rescheduled. A thread gives
       * up its quantum whenever it sleeps or waits and the scheduler may decide to run
       * a higher priority thread instead of the current thread on the next tick
       */
      sprintf(value, " CPU%d %d   ", count, (int)scheduler_get_thread_quantum(count));
      console_window_write_ex(windowhandle, value, 1, 20 + count, console_window_get_forecolor(windowhandle), console_window_get_backcolor(windowhandle));
    }

    /* Now finally let's keep track of how many loops we have done and change CPUs when
     * we reach a certain number
     */
    loops++;

    /* Check for about 100 loops, that should be about 10 seconds */
    if (loops >= 100)
    {
      /* Call the thread_migrate function and specify a random CPU */
      thread_migrate(GetCurrentThreadId(), abs(random_read_longint(cpu_get_count() - 1)));

      /* Reset our loop counter */
      loops = 0;
    }

    /* Sleep a while so we don't mess with the utilization too much */
    thread_sleep(100);
  }
  
  /* No need to Halt, we never get to here */

  return 0;
}
