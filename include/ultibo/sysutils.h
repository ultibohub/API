/*
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2026 Garry Wood <garry@softoz.com.au>
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

/** SysUtils constants */
#define MAX_PATH	260 ///< Maximum length for a file path

/** SysUtils types */

typedef struct _SYSTEMTIME
{
	uint16_t wyear; ///< The year
	uint16_t wmonth; ///< The month
	uint16_t wdayofweek; ///< The day of the week
	uint16_t wday; ///< The day of the month
	uint16_t whour; ///< The hour
	uint16_t wminute; ///< The minute
	uint16_t wsecond; ///< The second
	uint16_t wmilliseconds; ///< The millisecond
} SYSTEMTIME;

typedef struct _FILETIME
{
    DWORD dwLowDateTime; ///< The low-order part of the file time
    DWORD dwHighDateTime; ///< The high-order part of the file time
} FILETIME;

typedef struct _WIN32_FIND_DATAA
{
    DWORD    dwFileAttributes; ///< The file attributes of a file
    FILETIME ftCreationTime; ///< A FILETIME structure that specifies when a file or directory was created
    FILETIME ftLastAccessTime; ///< A FILETIME structure that specifies when a file was last read from or written to
    FILETIME ftLastWriteTime; ///< A FILETIME structure that specifies when the file was last written to, truncated, or overwritten
    DWORD    nFileSizeHigh; ///< The high-order DWORD value of the file size, in bytes
    DWORD    nFileSizeLow; ///< The low-order DWORD value of the file size, in bytes
    DWORD    dwReserved0; ///< If the dwFileAttributes member includes the faReparse attribute, this member specifies the reparse point tag
    DWORD    dwReserved1; ///< Reserved for future use
    char     cFileName[MAX_PATH]; ///< The name of the file
    char     cAlternateFileName[14]; ///< An alternative name for the file (This name is in the 8.3 file name format)
} WIN32_FIND_DATAA;

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_SYSUTILS_H