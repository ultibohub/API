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
#ifndef _ULTIBO_MCP230XX_H
#define _ULTIBO_MCP230XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"

/* ============================================================================== */
/* MCP230XX specific constants */
#define MCP23008_GPIO_DESCRIPTION	"Microchip MCP23008 8-bit I/O Expander" // Description of MCP23008 device
#define MCP23017_GPIO_DESCRIPTION	"Microchip MCP23016 16-bit I/O Expander" // Description of MCP23017 device

#define MCP23008_GPIO_MIN_PIN	GPIO_PIN_0
#define MCP23008_GPIO_MAX_PIN	GPIO_PIN_7
#define MCP23008_GPIO_PIN_COUNT	8

#define MCP23017_GPIO_MIN_PIN	GPIO_PIN_0
#define MCP23017_GPIO_MAX_PIN	GPIO_PIN_15
#define MCP23017_GPIO_PIN_COUNT	16

#define MCP230XX_GPIO_MAX_LEVEL	GPIO_LEVEL_HIGH

#define MCP230XX_GPIO_MAX_PULL	GPIO_PULL_UP

#define MCP230XX_GPIO_MIN_FUNCTION	GPIO_FUNCTION_IN
#define MCP230XX_GPIO_MAX_FUNCTION	GPIO_FUNCTION_OUT

/* MCP230XX chip constants */
#define MCP230XX_CHIP_MCP23008	0
#define MCP230XX_CHIP_MCP23017	1

/* MCP230XX I2C constants */
#define MCP230XX_I2C_RATE	400000 // Default I2C clock rate (Device supports 100KHz, 400KHz and 1.7MHz

#define MCP23008_I2C_SIZE	1 // Number of bytes to read/write all pin values for any register
#define MCP23017_I2C_SIZE	2 // Number of bytes to read/write all pin values for any register

#define MCP230XX_I2C_MAX_SIZE	2 // Maximum number of bytes to read/write all pin values for any register

#define MCP23008_I2C_MAX_REG	0x0A // Maximum register address for the I2C interface
#define MCP23017_I2C_MAX_REG	0x1A // Maximum register address for the I2C interface (Only 21 (0x15) registers exists, mappings differ between modes)

/* ============================================================================== */
/* MCP230XX specific types */
typedef struct _MCP230XXGPIO MCP230XXGPIO;
struct _MCP230XXGPIO
{
	// GPIO Properties
	GPIO_DEVICE gpio;
	// MCP230XX Properties
	I2C_DEVICE *i2c; // The I2C device this GPIO is connected to
	uint16_t address; // The I2C address of the device
	uint32_t chip; // The chip type (eg MCP230XX_CHIP_MCP23008)
	uint32_t size; // Size of an I2C read/write for the device
	uint8_t gpioreg; // GPIO port register for the device
	uint8_t gppureg; // GPPU pull up resistor register for the device
	uint8_t iodirreg; // IODIR I/O direction register for the device
	uint8_t gpiovalues[MCP230XX_I2C_MAX_SIZE]; // Buffer for GPIO port values (Output only)
	uint8_t gppuvalues[MCP230XX_I2C_MAX_SIZE]; // Buffer for GPPU pull up values
	uint8_t iodirvalues[MCP230XX_I2C_MAX_SIZE]; // Buffer for IODIR I/O direction values
};

/* ============================================================================== */
/* MCP230XX Functions */
GPIO_DEVICE * STDCALL mcp23008_gpio_create(I2C_DEVICE *i2c, uint16_t address);
GPIO_DEVICE * STDCALL mcp23017_gpio_create(I2C_DEVICE *i2c, uint16_t address);

uint32_t STDCALL mcp230xx_gpio_destroy(GPIO_DEVICE *gpio);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_MCP230XX_H
