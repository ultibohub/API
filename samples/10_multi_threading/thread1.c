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
#include <stdlib.h>
#include <stdbool.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"

ssize_t STDCALL thread1_execute(void * parameter)
{
    int count;
    char name[256], value[512];
    WINDOW_HANDLE windowhandle;

    /* This is the thread function for thread1, when thread1 is created it will start
     * running here and will continue to run until it exits here or calls end_thread()
     *
     * Most threads will do something in a loop and only exit when they have either
     * completed their task or been signalled by another thread to end
     * 
     * For this example we'll use an endless loop but first let's create a console
     * window to print some output */
    windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_TOPRIGHT, FALSE);

    /* We'll also set the thread name to something meaningful so we can use it in our output */
    thread_set_name(thread_get_current(), "Example Thread1");

    /* And write something to the console to say we're here */
    thread_get_name(thread_get_current(), name, sizeof(name));
    sprintf(value, "Hi, this is thread %s, my thread ID is %x", name, (unsigned int)thread_get_current());
    console_window_write_ln(windowhandle, value);

    count = 0;
    while (true)
    {
        /* Let's keep a count of how many times this thread loops */
        count++;

        /* And then we'll print that on our console window */
        thread_get_name(thread_get_current(), name, sizeof(name));
        sprintf(value, "Thread %s, count is now %d", name, (int)count);
        console_window_write_ln(windowhandle, value);

        /* Even though Ultibo uses preemptive thread scheduling every thread should either
         * wait or sleep when it has nothing to do, that way other threads can use the CPU
         * time for their work
         */
        thread_sleep(abs(random_read_longint(4000)));
    }

    return 0;
}
