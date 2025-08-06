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

 #include <stdarg.h>
 #include <fcntl.h>
 #include <reent.h>

 #define	F_DUPFD_CLOEXEC	14	/* As F_DUPFD, but set close-on-exec flag */

/* Implementation of fcntl() for Ultibo API */
int fcntl (int fd, int cmd, ...)
{
    int res = -1;
    va_list args;
    int intarg = 0;

    va_start(args, cmd);

    switch (cmd)
    {
        /* These commands take no argument */
        case F_GETFD:
        case F_GETFL:
        {
            intarg = 0;

            break;
        }
        /* These commands take an 'int' argument */
        case F_DUPFD:
        case F_DUPFD_CLOEXEC:
        case F_SETFD:
        case F_SETFL:
        {
            intarg = va_arg(args, int);

            break;
        }
    }

    /* Call reentrant function with int argument
     *
     * Some commands take a pointer argument
     * but they are not currently supported
     */
    res = _fcntl_r(_REENT, fd, cmd, intarg);

    va_end(args);

    return res;
}
