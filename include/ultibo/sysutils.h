/*
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
#ifndef _ULTIBO_SYSUTILS_H
#define _ULTIBO_SYSUTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/system.h"

/* ============================================================================== */
/* SysUtils constants */
#define MAX_PATH	260

/* ============================================================================== */
/* SysUtils types */

typedef struct _SYSTEMTIME
{
	uint16_t wyear;
	uint16_t wmonth;
	uint16_t wdayofweek;
	uint16_t wday;
	uint16_t whour;
	uint16_t wminute;
	uint16_t wsecond;
	uint16_t wmilliseconds;
} SYSTEMTIME;

typedef struct _FILETIME
{
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME;

typedef struct _WIN32_FIND_DATAA
{
    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwReserved0;
    DWORD    dwReserved1;
    char     cFileName[MAX_PATH];
    char     cAlternateFileName[14];
} WIN32_FIND_DATAA;

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_SYSUTILS_H