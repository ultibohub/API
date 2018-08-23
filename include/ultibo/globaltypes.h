/*
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Garry Wood <garry@softoz.com.au>
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
#ifndef _ULTIBO_GLOBALTYPES_H
#define _ULTIBO_GLOBALTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <math.h>

#include <sys/types.h>

/* ============================================================================== */
/* Compiler definitions */
#ifdef __i386__
#define STDCALL __stdcall
#else
#define STDCALL
#endif

#define PACKED __attribute__((__packed__))

/* ============================================================================== */
/* Compatibility definitions */
typedef size_t HANDLE;

typedef uint32_t DWORD;

typedef _Bool BOOL; // Built in Boolean type (1 byte) (Redeclared here for flexibility)
typedef int32_t LONGBOOL; // Compatibility with FPC LongBool type (4 bytes)

typedef wchar_t WCHAR; // Standard WideChar type (4 bytes) (Redeclared here for flexibility)

typedef size_t SOCKET;

typedef HANDLE WSAEVENT;

typedef void *FARPROC; //To Do //

#define TRUE -1
#define FALSE 0

/* ============================================================================== */
/* Structure types */
typedef struct _OVERLAPPED
{
  size_t Internal;
  size_t InternalHigh;
  union
    {
    struct
    {
      DWORD Offset;
      DWORD OffsetHigh;
    };
    void *Pointer;
  };
  HANDLE hEvent;
} OVERLAPPED;

/* ============================================================================== */
/* Handle types */
typedef HANDLE SPIN_HANDLE;
typedef HANDLE MUTEX_HANDLE;
typedef HANDLE CRITICAL_SECTION_HANDLE;
typedef HANDLE SEMAPHORE_HANDLE;
typedef HANDLE SYNCHRONIZER_HANDLE;
typedef HANDLE CONDITION_HANDLE;
typedef HANDLE COMPLETION_HANDLE;
typedef HANDLE LIST_HANDLE;
typedef HANDLE QUEUE_HANDLE;
typedef HANDLE THREAD_HANDLE;
typedef HANDLE MESSAGESLOT_HANDLE;
typedef HANDLE MAILSLOT_HANDLE;
typedef HANDLE BUFFER_HANDLE;
typedef HANDLE EVENT_HANDLE;

typedef HANDLE TIMER_HANDLE;
typedef HANDLE WORKER_HANDLE;
typedef HANDLE WINDOW_HANDLE;
typedef HANDLE FONT_HANDLE;
typedef HANDLE KEYMAP_HANDLE;


#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_GLOBALTYPES_H