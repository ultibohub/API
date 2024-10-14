/*
 *
 * Multi Threading example project for Ultibo API
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
#include <pthread.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"

#include "thread1.h"
#include "thread2.h"

int apimain(int argc, char **argv)
{
  char name[256], value[512];
  WINDOW_HANDLE windowhandle;
  THREAD_HANDLE thread1handle;
  pthread_t thread2handle; 

  /* Create our window */
  windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_LEFT, TRUE);

  /* Output the message */
  console_window_write_ln(windowhandle, "Welcome to Example 10 Multi Threading");
  console_window_write_ln(windowhandle, "");

  /* There are basically two ways to create a thread in Ultibo, you can call the 
   * thread functions defined in the API or you can use the POSIX thread functions.
   *
   * In this example we'll create one thread using each of these methods so you can
   * compare. There is no right or wrong way, it depends on your code which method
   * you decide to use
   */

  /* First let's try the API method which uses begin_thread(). There are a couple of
   * variations of begin_thread() declared in the API, they all do the same job but
   * some allow you to pass extra parameters to control the setup of the thread
   */

  /* Every thread needs at least a function to run, the thread function */
  console_window_write_ln(windowhandle, "Creating Thread1 using begin_thread()");
  thread1handle = begin_thread(NULL, thread_get_stack_size(thread_get_current()),  thread1_execute, NULL, THREAD_CREATE_NONE, &thread1handle);
  if (thread1handle == INVALID_HANDLE_VALUE)
  {
    /* If the thread handle is not valid then begin_thread() failed */
    console_window_write_ln(windowhandle, "Failed to create Thread1");
  }
  else
  {
    /* Otherwise the thread was created and will start running soon, we have a handle
     * to reference it if we want. The thread1_execute function is in the thread1.c source
     * file, have a look there to see what it will be doing
     */
    sprintf(value, "Thread1 was created successfully, the handle is %x", (unsigned int)thread1handle);
    console_window_write_ln(windowhandle, value);

    /* Let's wait a bit to see what happens */
    thread_sleep(5000);
  }
  console_window_write_ln(windowhandle, "");

  /* Now let's create a thread using the POSIX thread functions to see how that differs.
   *
   * We still need a thread function, you can find it in the thread2.c source file, the
   * difference is we call pthread_create() to create the thread this time
   */
  console_window_write_ln(windowhandle, "Creating Thread2 using pthread_create()");
  if (pthread_create(&thread2handle, NULL, *thread2_execute, NULL))
  {
    /* If the result is not zero then pthread_create() failed */
    console_window_write_ln(windowhandle, "Failed to create Thread2");
  }
  else
  {
    /* If our thread was created successfully we can write the handle to the console */
    sprintf(value, "Thread2 was created successfully, the handle is %x", (unsigned int)thread2handle);
    console_window_write_ln(windowhandle, value);

    /* We also need to detach our thread so it is automatically destroyed when it completes */
    pthread_detach(thread2handle);
  }
  console_window_write_ln(windowhandle, "");

  /* Say goodbye from this thread */
  thread_get_name(thread_get_current(), name, sizeof(name));
  sprintf(value, "Goodbye from %s, my ID is %x", name, (unsigned int)thread_get_current());
  console_window_write_ln(windowhandle, value);
  
  /* We haven't talked about locks and synchronization in this example. Ultibo supports
   * a full range of locking and synchronization primitives which are very important as
   * soon as you start to use multiple threads. See the wiki and other resources for
   * more information on these and other topics to do with multi thread programming.
   */
 
  /* Halt thread, the others will keep running */
  thread_halt(0);

  return 0;
}
