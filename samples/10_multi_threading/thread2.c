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
#include <pthread.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"

void * thread2_execute(void * args)
{
    int count;
    char name[256], value[512];
    WINDOW_HANDLE windowhandle;

    /* This is the thread function for our POSIX thread. When thread2 is created
     * it will start running here and will continue to run until it exits here
     *
     * Like our other thread we'll use an endless loop and create a console window
     * to print some output */
    windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_BOTTOMRIGHT, FALSE);

    /* Set the thread name of this thread to Example Thread2 */
    thread_set_name(thread_get_current(), "Example Thread2");

    /* And write something to the console to say we're here */
    thread_get_name(thread_get_current(), name, sizeof(name));
    sprintf(value, "Hi, this is thread %s, my thread ID is %x", name, (unsigned int)thread_get_current());
    console_window_write_ln(windowhandle, value);

    count = 0;
    while (true)
    {
        /* Update our loop counter */
        count++;

        /* And print that on our console window */
        thread_get_name(thread_get_current(), name, sizeof(name));
        sprintf(value, "Thread %s, count is now %d", name, (int)count);
        console_window_write_ln(windowhandle, value);

        /* Sleep so other threads can use the CPU time */
        thread_sleep(abs(random_read_longint(6000)));
    }

    /* Note that when using POSIX threads you can use the pthread_self() function in place
     * of thread_get_current() as both the THREAD_HANDLE and pthread_t are the same value 
     */

    return NULL;
}

