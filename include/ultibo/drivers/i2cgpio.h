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
#ifndef _ULTIBO_I2CGPIO_H
#define _ULTIBO_I2CGPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/i2c.h"

/* ============================================================================== */
/* I2CGPIO specific constants */
#define I2CGPIO_I2C_DESCRIPTION	"GPIO Software I2C" // Description of I2CGPIO I2C device

#define I2CGPIO_I2C_MAX_SIZE	0xFFFF
#define I2CGPIO_I2C_MIN_CLOCK	10000 // Arbitrary minimum of 10KHz, actual rate is determined by Delay parameter
#define I2CGPIO_I2C_MAX_CLOCK	100000 // Arbitrary maximum of 100KHz, actual rate is determined by Delay parameter

#define I2CGPIO_RETRY_COUNT	3

#define I2CGPIO_DEFAULT_TIMEOUT	100

/* ============================================================================== */
/* I2CGPIO specific types */
typedef struct _I2CGPIO_DEVICE I2CGPIO_DEVICE;
struct _I2CGPIO_DEVICE
{
	// I2C Properties
	I2C_DEVICE i2c;
	// I2CGPIO Properties
	GPIO_DEVICE *gpio; // The GPIO device this device is connected to
	uint32_t sda; // GPIO pin for the SDA line
	uint32_t scl; // GPIO pin for the SCL line
	uint32_t delay; // Clock and Data delay in microseconds
	uint32_t timeout; // Clock timeout in milliseconds
	LONGBOOL outputonly; // Clock line is output only, no test for SCL high
	LONGBOOL opendrain; // Clock and Data are open drain, no need to simulate by switching direction
};

/* ============================================================================== */
/* I2CGPIO Functions */
I2C_DEVICE * STDCALL i2cgpio_create(GPIO_DEVICE *gpio, uint32_t sda, uint32_t scl, uint32_t delay, uint32_t timeout, BOOL outputonly, BOOL opendrain);
uint32_t STDCALL i2cgpio_destroy(I2C_DEVICE *i2c);

/* ============================================================================== */
/* I2CGPIO Helper Functions */

#ifdef __cplusplus
}
#endif

#endif