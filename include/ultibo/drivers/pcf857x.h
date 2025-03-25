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
#ifndef _ULTIBO_PCF857X_H
#define _ULTIBO_PCF857X_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"

/* ============================================================================== */
/* PCF857X specific constants */
#define PCF8574_GPIO_DESCRIPTION	"NXP PCF8574 8-bit I/O Expander" // Description of PCF8574 device

#define PCF8574_GPIO_MIN_PIN	GPIO_PIN_0
#define PCF8574_GPIO_MAX_PIN	GPIO_PIN_7
#define PCF8574_GPIO_PIN_COUNT	8

#define PCF857X_GPIO_MAX_LEVEL	GPIO_LEVEL_HIGH

#define PCF857X_GPIO_MAX_PULL	GPIO_PULL_UP

#define PCF857X_GPIO_MIN_FUNCTION	GPIO_FUNCTION_IN
#define PCF857X_GPIO_MAX_FUNCTION	GPIO_FUNCTION_OUT

/* PCF857X chip constants */
#define PCF857X_CHIP_PCF8574	0

/* PCF857X I2C constants */
#define PCF8574_I2C_RATE	100000 // Default I2C clock rate (Device supports 100KHz only)

#define PCF8574_I2C_SIZE	1 // Number of bytes to read/write all pin values

#define PCF857X_I2C_MAX_SIZE	2 // Maximum number of bytes to read/write all pin values

/* Note: The PCF857X is a single register device and does not have any direction, pull or configuration registers */

/* ============================================================================== */
/* PCF857X specific types */
typedef struct _PCF857XGPIO PCF857XGPIO;
struct _PCF857XGPIO
{
	// GPIO Properties
	GPIO_DEVICE gpio;
	// PCF857X Properties
	I2C_DEVICE *i2c; // The I2C device this GPIO is connected to
	uint16_t address; // The I2C address of the device
	uint32_t chip; // The chip type (eg PCF857X_CHIP_PCF8574)
	uint32_t size; // Size of an I2C read/write for the device
	uint32_t rate; // Clock rate for this device
    uint8_t gpiovalues[PCF857X_I2C_MAX_SIZE]; // Buffer for GPIO port values (Output only)
	uint8_t gppuvalues[PCF857X_I2C_MAX_SIZE]; // Buffer for GPPU pull up values
	uint8_t iodirvalues[PCF857X_I2C_MAX_SIZE]; // Buffer for IODIR I/O direction values
};

/* ============================================================================== */
/* PCF857X Functions */
GPIO_DEVICE * STDCALL pcf8574gpio_create(I2C_DEVICE *i2c, uint16_t address);

uint32_t STDCALL pcf857xgpio_destroy(GPIO_DEVICE *gpio);

/* ============================================================================== */
/* PCF857X Helper Functions */

#ifdef __cplusplus
}
#endif

#endif
