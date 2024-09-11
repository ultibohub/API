/*
 *
 * Log Output example project for Ultibo API
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

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"
#include "ultibo/logging.h"

int apimain(int argc, char **argv)
{
  char value[256];
  WINDOW_HANDLE windowhandle;

  /* Create our window */
  windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_LEFT, TRUE);

  /* Output the message */
  console_window_write_ln(windowhandle, "Welcome to Example 09 Log Output");
  console_window_write_ln(windowhandle, "");

  /* Because console logging is disabled by default we need to enable it first.
   *
   * For this example the following line has been added to the Free Pascal part
   * of the project which enables console logging prior to calling our main() function
   * 
   * CONSOLE_REGISTER_LOGGING:=True;
   * 
   * This can also be done using the command line parameter CONSOLE_REGISTER_LOGGING=1
   * in the cmdline.txt file on the SD card.
   */

  /* Now we can register a new console logging device by passing the default console
   * device to the function logging_console_device_add().
   *
   * The parameters CONSOLE_LOGGING_DEFAULT and CONSOLE_LOGGING_POSITION control if
   * the new logging device can be the default device and where the console window
   * will appear. By default the logging console will be on the right side of the
   * screen.
   */
  logging_console_device_add(console_device_get_default());

  /* We can set the new console logging device as the default by using the function 
   * logging_device_set_default() and passing to it the first available console logging
   * device obtained by logging_device_find_by_type()
   */
  logging_device_set_default(logging_device_find_by_type(LOGGING_TYPE_CONSOLE));

  /* The console logging window should now be visible on the right side of the screen
   * and we can try writing to it using logging_output()
   */
  console_window_write_ln(windowhandle, "Sending a message to the log");
  logging_output("This is a logging message, it should go to the logging screen");

  /* Sleep a few seconds so we can see that */
  thread_sleep(3000);

  /* Notice that the logging output automatically includes a counter and the ThreadId
   * of the thread that sent the message, this helps with debugging your program.
   *
   * On the Raspberry Pi 2, 3 or 4 the logging message will also include the CPU Id of
   * the CPU that the thread was running on when it sent the message.
   * 
   * You might also notice a logging message saying that a logging device was created
   * and enabled. Many parts of Ultibo automatically send logging messages to indicate
   * events and errors.
   */

  /* Let's send a few more messages to the log */
  console_window_write_ln(windowhandle, "Sending lots of messages to the log");
  for (int count = 1; count <= 100; count++)
  {
    time_t utctime;
    struct tm *info;

    time(&utctime);
    info = localtime(&utctime);

    sprintf(value, "Message no %d sent at %s", count, asctime(info));
    logging_output(value);

    /* Sleep for a random amount of time to mix up the output */
    thread_sleep(random_read_longint(350));
  }

  /* The logging output is handled by its own thread so even in this simple example
   * logging is handled in the background by the logging unit, your code just sends
   * the message and doesn't have to think about where the logs are going after that
   */
  
  /* Halt the thread */
  thread_halt(0);

  return 0;
}
