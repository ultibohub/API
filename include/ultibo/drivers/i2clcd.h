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
#ifndef _ULTIBO_I2CLCD_H
#define _ULTIBO_I2CLCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"
#include "ultibo/console.h"

/* ============================================================================== */
/* I2CLCD specific constants */
#define I2CLCD_CONSOLE_DESCRIPTION	"Generic I2C LCD" // Description of I2CLCD device

#define I2CLCD_SIGNATURE	0x00CF8574

/* I2CLCD GPIO constants */
#define I2CLCD_PIN_RS	GPIO_PIN_0 // GPIO pin for the LCD RS line
#define I2CLCD_PIN_RW	GPIO_PIN_1 // GPIO pin for the LCD RW line
#define I2CLCD_PIN_EN	GPIO_PIN_2 // GPIO pin for the LCD EN line
#define I2CLCD_PIN_BACKLIGHT	GPIO_PIN_3 // GPIO pin for the LCD Backlight
#define I2CLCD_PIN_D4	GPIO_PIN_4 // GPIO pin for the LCD D4 line
#define I2CLCD_PIN_D5	GPIO_PIN_5 // GPIO pin for the LCD D5 line
#define I2CLCD_PIN_D6	GPIO_PIN_6 // GPIO pin for the LCD D6 line
#define I2CLCD_PIN_D7	GPIO_PIN_7 // GPIO pin for the LCD D7 line

/* ============================================================================== */
/* I2CLCD specific types */
typedef struct _I2CLCD_DISPLAY I2CLCD_DISPLAY;
struct _I2CLCD_DISPLAY
{
	uint32_t signature; // Signature for entry validation
	uint32_t width; // Width in columns of this display
	uint32_t height; // Height in rows of this display
	I2C_DEVICE *i2c; // I2C device for this display
	GPIO_DEVICE *gpio; // GPIO (PCF8574) device for this display
	CONSOLE_DEVICE *console; // Console (HD44780) device for this display
};

/* ============================================================================== */
/* I2CLCD Functions */
HANDLE STDCALL i2clcd_start(char *device, uint16_t address, uint32_t width, uint32_t height);
BOOL STDCALL i2clcd_stop(HANDLE handle);

BOOL STDCALL i2clcd_backlight_on(HANDLE handle);
BOOL STDCALL i2clcd_backlight_off(HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_I2CLCD_H
