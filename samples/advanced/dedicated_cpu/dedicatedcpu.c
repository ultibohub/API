/*
 *
 * Dedicated CPU advanced example project for Ultibo API
 * 
 * This example shows how to take control of a CPU in Ultibo core and use it as
 * a high speed micro controller doing real time operations.
 *
 * Using this technique you can take advantage of the functionality of Ultibo
 * core to handle things like networking, devices and files but still get real
 * time performance using one CPU dedicated to the task.
 *
 * !! WARNING, WARNING, WARNING, WARNING, WARNING, WARNING, WARNING, WARNING !!
 *
 * Using a single CPU for real time tasks in a sophisticated preemptive multi
 * CPU environment is NOT a free lunch, you MUST obey very strict rules about
 * the functions that can be called from the dedicated CPU or you will quickly
 * find that the result is a complete and total deadlock.
 *
 * Please read all of the comments in the start_dedicated_thread() function and
 * the dedicated_thread_execute() function before you try using this in your own
 * projects.
 *
 *                     !!! You have been warned !!!
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

#include "dedicatedthread.h"

int apimain(int argc, char **argv)
{
  WINDOW_HANDLE left_window;

  /* Create a console window to show what is happening */
  left_window = console_window_create(console_device_get_default(), CONSOLE_POSITION_LEFT, TRUE);

  /* Display a startup message on the console */
  console_window_write_ln(left_window, "Starting dedicated CPU example");

  /* Start our dedicated CPU thread */
  start_dedicated_thread(left_window);

  /* Halt this thread */
  thread_halt(0);

  return 0;
}
