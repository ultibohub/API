/*
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 Garry Wood <garry@softoz.com.au>
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
#include <stdarg.h>

#include "ultibo/console.h"

#if !defined(__GNU_VISIBLE) || __GNU_VISIBLE == 0
/* These are only available in stdio.h if __GNU_VISIBLE is defined as 1 (see features.h) */
int asprintf(char **__restrict, const char *__restrict, ...) _ATTRIBUTE ((__format__ (__printf__, 2, 3)));
int vasprintf(char **, const char *, __VALIST) _ATTRIBUTE ((__format__ (__printf__, 2, 0)));
#endif 

/* Implementation of console_window_printf() for Ultibo API
 *
 * Supports the same set of formatting variables as printf()
 */
int STDCALL console_window_printf(WINDOW_HANDLE handle, const char *format, ...)
{
    int res = -1;
    char *str;
    va_list args;

    va_start(args, format);

    // Use vasprintf() to print to an allocated string
    res = vasprintf(&str, format, args);
    if (res >= 0)
    {
        // Write the string to the console
        if (console_window_write(handle, str) != ERROR_SUCCESS)
            res = -1;

        // Free the string allocated by vasprintf()
        free(str);
    }
    va_end(args);

    return res;
}
