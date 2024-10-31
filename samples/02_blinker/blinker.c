/*
 *
 * Blinker example project for Ultibo API
 *
 * This example shows the standard starting point for bare metal programming
 * by blinking the activity LED on and off repeatedly.
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

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"

int apimain(int argc, char **argv)
{
 HANDLE window_handle;

 /* Before we can turn the LED on or off we need to enable it which sets the GPIO
  * pins to the appropriate function. */
 activity_led_enable();
 
 /* So that we can see what's happening, let's create a console window. */
 window_handle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);
 
 /* Let's create a loop so that the blinking happens forever, or until you pull the
  * power plug at least.
  *
  * This loop will execute while the condition is true. Since the value TRUE is always
  * true then the loop will continue forever. */
 while (TRUE) {
  /* Write to the console */
  console_window_write_ln(window_handle, "Turning on the Activity LED");
 
  /* Turn on the LED */
  activity_led_on();
 
  /* Wait for a while so that things happen at a speed we can see, 500 milliseconds,
   * or half a second, should be enough. */ 
  thread_sleep(500);
  
  /* Write to the console */
  console_window_write_ln(window_handle, "Turning off the Activity LED");
  
  /* Turn off the LED */ 
  activity_led_off();
  
  /* Wait a while before turning the LED back on again. */
  thread_sleep(500);
  
  /* You might want to experiment with the values of thread_sleep() to make things
   * happen faster or maybe you might try rearranging the code in the loop to do
   * a double blink each time. */
 }
 
 /* We will never get to here, so there is no need for thread_halt() like in other
  * examples even though the blinkerproject wrapper does it for us anyway. */
  
 return 0;
}
