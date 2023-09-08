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
#ifndef _ULTIBO_SYSTEM_H
#define _ULTIBO_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"

/* ============================================================================== */
/* System types */

/* RTL Heap Manager Types */
typedef struct _FPC_HEAP_STATUS
{
	size_t maxheapsize;
	size_t maxheapused;
	size_t currheapsize;
	size_t currheapused;
	size_t currheapfree;
} FPC_HEAP_STATUS;

typedef struct _HEAP_STATUS
{
	uint32_t totaladdrspace;
	uint32_t totaluncommitted;
	uint32_t totalcommitted;
	uint32_t totalallocated;
	uint32_t totalfree;
	uint32_t freesmall;
	uint32_t freebig;
	uint32_t unused;
	uint32_t overhead;
	uint32_t heaperrorcode;
} HEAP_STATUS;

/* RTL Thread Manager Types */
typedef ssize_t STDCALL (*thread_func)(void * parameter);
typedef HANDLE THREAD_ID;

typedef struct _THREAD_INFO
{
	thread_func threadfunction;
	void *threadparameter;
	uint32_t stacklength;
} THREAD_INFO;

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_SYSTEM_H