/*
 *
 * Serial Connection example project for Ultibo API
 * 
 * This example uses the serial (UART) device in the Raspberry Pi to connect
 * to another computer and echo back any line of text it receives.
 *
 * You will need a serial cable or a USB to serial converter to connect the Pi
 * to your computer, the Pi uses GPIO 14 (Transmit) and 15 (Receive) as well as
 * a Ground pin to make the connection. The documentation below shows you where
 * to find each of the GPIO connections on the physical pins of your Pi.
 *
 * Raspberry Pi Models A+/B+/Zero/ZeroW/2B/3B/4B/400/Zero2W (40 pin header)
 *  https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#gpio
 *
 * Raspberry Pi Pinout (26 and 40 pin header)
 *  https://pinout.xyz/
 *
 * You will also need a terminal program running on your computer, you can use
 * something like PuTTY to create a serial connection to the COM port you are
 * using. For this example we'll use these connection settings:
 *
 * Speed: 9600
 * Data Bits: 8
 * Stop Bits: 1
 * Parity: None
 * Flow Control: None
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
#include <string.h>
#include <stdbool.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"
#include "ultibo/serial.h"
#include "ultibo/ultibo.h"

int apimain(int argc, char **argv)
{
  int index;
  uint32_t count;
  uint8_t character;
  char characters[256], value[512];
  WINDOW_HANDLE windowhandle;

  /* Create our window */
  windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);

  /* Output the message */
  console_window_write_ln(windowhandle, "Welcome to Example 13 Multi CPU");
  console_window_write_ln(windowhandle, "Connect the Raspberry Pi to your computer using a serial cable or USB to Serial converter");
  console_window_write_ln(windowhandle, "Open a terminal program like PuTTY on your computer and connect to the appropriate COM port");

  /* First we need to open the serial device and set the speed and other parameters.
   *
   * We can use the serial_open() function from the platform header to open the default
   * serial device or we can use the serial_device_open() function from the serial header
   * if we need to specify which device to open.
   * 
   * We'll use serial_open() and specify 9600 as the speed with 8 data bits, 1 stop bit,
   * no parity and no flow control. The constants used here can be found in the globalconst
   * header.
   * 
   * The last 2 parameters allow setting the size of the transmit and receive buffers,
   * passing 0 means use the default size
   */
  if (serial_open(9600, SERIAL_DATA_8BIT, SERIAL_STOP_1BIT, SERIAL_PARITY_NONE, SERIAL_FLOW_NONE, 0, 0) == ERROR_SUCCESS)
  {
    /* Opened successfully, display a message */
    console_window_write_ln(windowhandle, "Serial device opened, type some text in your terminal program and press Enter");

    /* Setup our starting point */
    count = 0;
    index = 0;
    memset(characters, 0, sizeof(characters));

    /* Loop endlessly waiting for data */
    while (true)
    {
      /* Read from the serial device using the serial_read() function, to be safe we
       * would normally check the result of this function before using the value
       */
      serial_read(&character, sizeof(character), &count);

      /* Check what character we received */
      if (character == 13)
      {
        /* If we received a carriage return then write our characters to the console */
        sprintf(value, "Received a line: %s", characters);
        console_window_write_ln(windowhandle, value);

        /* Check for 4 characters */
        if (strlen(characters) == 4)
        {
          /* Copy to a temporary buffer */
          strcpy(value, characters);

          /* And convert to uppercase */
          CharUpperBuff(value, 4);

          /* Check for the word Quit */
          if (!strncmp(value, "QUIT", 4))
          {
            /* If received then say goodbye and exit our loop */
            sprintf(value, "Goodbye!\r\n");
            serial_write(value, strlen(value), &count);

            /* Wait for the data to be sent */
            thread_sleep(1000);

            break;
          }
        }

        /* Add a carriage return and line feed */
        sprintf(value, "%s\r\n", characters);
        
        /* And echo them back to the serial device using serial_write() */
        serial_write(value, strlen(value), &count);

        /* Now clear the characters and wait for more */
        index = 0;
        memset(characters, 0, sizeof(characters));
      }
      else
      {
        /* Add the character to what we have already recevied */
        characters[index] = (char)character;
        index++;
        
        /* Check if our character buffer is full */
        if (index == 255)
        {
          /* Write the received characters to the console */
          sprintf(value, "Received so far: %s", characters);
          console_window_write_ln(windowhandle, value);
          
          /* Write the character buffer to the serial device */
          serial_write(characters, strlen(characters), &count);

          /* Clear the characters and wait for more */ 
          index = 0;
          memset(characters, 0, sizeof(characters));
        }
      }

      /* No need to sleep on each loop, serial_read() will wait until data is received */
    }

    /* Close the serial device using serial_close() */
    serial_close();

    console_window_write_ln(windowhandle, "Serial device closed");
  }
  else
  {
    /* Must have been an error, print a message on the console */
    console_window_write_ln(windowhandle, "An error occurred opening the serial device");
  }

  /* Halt the thread if we exit the loop */
  thread_halt(0);
  
  return 0;
}
