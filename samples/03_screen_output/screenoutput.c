/*
 *
 * Screen Output example project for Ultibo API
 *
 * This example builds on the previous ones by demonstrating some of the console
 * functions available in Ultibo and how to use them to manipulate text on the
 * screen.
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
  char value[256];
  uint32_t rowcount;
  uint32_t columncount;
  uint32_t currentx;
  uint32_t currenty;
  WINDOW_HANDLE handle1;
  WINDOW_HANDLE handle2;

  /* Let's create a console window again but this time on the left side of the screen */
  handle1 = console_window_create(console_device_get_default(), CONSOLE_POSITION_LEFT, TRUE);

  /* To prove that worked let's output some text on the console window */
  console_window_write_ln(handle1, "Welcome to Example 03 Screen Output");

  /* So that things happen in a time frame we can see, let's wait about 3 seconds */
  thread_sleep(3 * 1000);

  /* Now let's get the current position of the console cursor into a couple of variables */
  console_window_get_xy(handle1, &currentx, &currenty);

  /* And we'll display those values on the screen */
  sprintf(value, "CurrentX = %d", (int)currentx);
  console_window_write_ln(handle1, value);
  sprintf(value, "CurrentY = %d", (int)currenty);
  console_window_write_ln(handle1, value);

  /* Wait another 3 seconds so we can see that */
  thread_sleep(3 * 1000);

  /* Let's find out how big our console window is */
  columncount = console_window_get_cols(handle1);
  rowcount = console_window_get_rows(handle1);

  /* And print that on the screen as well */
  sprintf(value, "ColumnCount = %d RowCount = %d", (int)columncount, (int)rowcount);
  console_window_write_ln(handle1, value);

  /* Wait 3 seconds again so we can see that */
  thread_sleep(3 * 1000);

  /* Now let's create another console window on the right side of the screen, notice
   * that we use a different variable for the handle so we can still access the first
   * console window. */
  handle2 = console_window_create(console_device_get_default(), CONSOLE_POSITION_RIGHT, TRUE);

  /* Update our original console */
  console_window_write_ln(handle1, "Printing some colored text on the new console");

  /* Using some more of the console function we can print to the screen using
   * console_window_write_ln_ex() which allows us to control the color of the
   * text and background as well as where to output the text */
  currentx = console_window_get_x(handle2);
  currenty = console_window_get_y(handle2);
  console_window_write_ln_ex(handle2, "This is some text in red", currentx, currenty, COLOR_RED, console_window_get_backcolor(handle2));

  /* console_window_write_ln_ex() doesn't update the position of X and Y for us, we
   * need to move to the next row so we can write the next line underneath */
  currenty++;
  console_window_set_y(handle2, currenty);
  console_window_write_ln_ex(handle2, "This is some text in green", currentx, currenty, COLOR_GREEN, console_window_get_backcolor(handle2));

  /* And one more time in yellow */
  currenty++;
  console_window_set_y(handle2, currenty);
  console_window_write_ln_ex(handle2, "This is some text in yellow", currentx, currenty, COLOR_YELLOW, console_window_get_backcolor(handle2));

  /* Wait a few more seconds so we can see that */
  thread_sleep(5 * 1000);

  /* Update our original console */
  console_window_write_ln(handle1, "Printing some text at the bottom of the new console");

  /* What about some text at the bottom of the screen instead, we'll use console_window_write_ex()
   * instead so it doesn't scroll the screen up */
  console_window_write_ex(handle2, "This text should be in the last row of the screen", currentx, console_window_get_max_y(handle2), console_window_get_forecolor(handle2), console_window_get_backcolor(handle2));

  /* Wait a bit more */
  thread_sleep(5 * 1000);

  /* Update our original console */
  console_window_write_ln(handle1, "Clearing the new console");

  /* Finally how about we clear the console window to get rid of all of that */
  console_window_clear(handle2);

  /* And say goodbye */
  console_window_write_ln(handle1, "All done, thanks for watching");

  /* We're not doing a loop this time so we better halt this thread before it exits */
  thread_halt(0);

  return 0;
}
