/*
 *
 * Keyboard Input example project for Ultibo API
 *
 * Example 03 showed some of the screen output capabilities, now we want to
 * read from a connected keyboard and print the typed characters on the screen.
 *
 * In this example we also begin to use the USB which is an important element
 * to allow Raspberry Pi to communicate with other devices.
 *
 *
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Garry Wood <garry@softoz.com.au>
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

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"

int apimain(int argc, char **argv)
{
  char character;
  WINDOW_HANDLE windowhandle;

  /* Create a console window at full size */
  windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);

  /* Output some welcome text on the console window */
  console_window_write_ln(windowhandle, "Welcome to Example 04 Keyboard Input");
  console_window_write_ln(windowhandle, "Make sure you have a USB keyboard connected and start typing some characters");
 
  /* Loop endlessly while checking for Keyboard characters */
  while (1) {
      
      /* Read a character from the global keyboard buffer. If multiple keyboards are
       * connected all characters will end up in a single buffer and be received here
       *
       * What happens if no keyboard is connected?
       *
       * Ultibo has dynamic USB attach and detach so just plug one in and start typing */
      if (console_get_key(&character, NULL)) {
        
        /* Before we print the character to the screen, check what was pressed */
        if ((uint8_t)character == 0) {

          /* If a control character like a function key or one of the arrow keys was pressed then
           * console_get_key() will return 0 first to let us know, we need to read the next character
           * to get the key that was pressed */
          console_get_key(&character, NULL);

        } else if ((uint8_t)character == 13) {
          /* If the enter key was pressed, write a new line to the console instead of a
           * character */

          console_window_write_ln(windowhandle, "");

        } else {

          /* Something other than enter was pressed, print that character on the screen */
          console_window_write_chr(windowhandle, character);
          
        }
      }

    /* No need to sleep on each loop, ConsoleGetKey will wait until a key is pressed */

  }

  /* No need to halt, we never reach this point */

  return 0;
}
