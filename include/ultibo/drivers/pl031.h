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
#ifndef _ULTIBO_PL031_H
#define _ULTIBO_PL031_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/rtc.h"

/* ============================================================================== */
/* PL031 specific constants */
#define PL031_RTC_DESCRIPTION	"ARM PrimeCell PL031 Real Time Clock" // Description of PL031 device

#define PL031_MIN_TIME	TIME_TICKS_TO_1970 // Time starts at 01/01/1970 00:00:00 (MM/DD/YY HH:MM:SS)
#define PL031_MAX_TIME	137919572470000000 // Time ends at 19/1/2038 03:14:07 (MM/DD/YY HH:MM:SS)

/* PL031 RTC Control register bits */
#define PL031_RTC_CR_EN	(1 << 0) // If set to 1, the RTC is enabled. Once it is enabled, any writes to this bit have no effect on the RTC until a system reset. A read returns the status of the RTC

/* PL031 RTC Interrupt mask set and clear register bits */
#define PL031_RTC_IMSC_INTR_SET	(1 << 0)
#define PL031_RTC_IMSC_INTR_CLEAR	(0 << 0)

/* PL031 RTC Raw interrupt status register bits */
#define PL031_RTC_RIS_INTR	(1 << 0)

/* PL031 RTC Masked interrupt status register bits */
#define PL031_RTC_MIS_INTR	(1 << 0)

/* PL031 RTC Interrupt clear register bits */
#define PL031_RTC_ICR_INTR	(1 << 0)

/* ============================================================================== */
/* PL031 specific types */
/* Layout of the PL031 registers (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0224b/i1005653.html) */
typedef struct _PL031_RTC_REGISTERS PL031_RTC_REGISTERS;
struct _PL031_RTC_REGISTERS
{
	uint32_t dr; // Data register
	uint32_t mr; // Match register
	uint32_t lr; // Load register
	uint32_t cr; // Control register
	uint32_t imsc; // Interrupt mask set and clear register
	uint32_t ris; // Raw interrupt status register
	uint32_t mis; // Masked interrupt status register
	uint32_t icr; // Interrupt clear register
};


typedef struct _PL031_RTC PL031_RTC;
struct _PL031_RTC
{
	// RTC Properties
	RTC_DEVICE rtc;
	// PL031 Properties
	uint32_t irq;
	PL031_RTC_REGISTERS *registers; // Device registers
	// Statistics Properties
	uint32_t interruptcount; // Number of interrupt requests received by the device
};

/* ============================================================================== */
/* PL031 Functions */
RTC_DEVICE * STDCALL pl031_rtc_create(size_t address, char *name, uint32_t irq);
uint32_t STDCALL pl031_rtc_destroy(RTC_DEVICE *rtc);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PL031_H
