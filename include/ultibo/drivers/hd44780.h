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
#ifndef _ULTIBO_HD44780_H
#define _ULTIBO_HD44780_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/console.h"

/** HD44780 specific constants */
#define HD44780_CONSOLE_DESCRIPTION	"Hitachi HD44780 LCD Controller" ///< Description of HD44780 device

/** HD44780 Instruction constants */
#define HD44780_CLEARDISPLAY	0x01
#define HD44780_RETURNHOME	0x02
#define HD44780_ENTRYMODESET	0x04
#define HD44780_DISPLAYCONTROL	0x08
#define HD44780_CURSORSHIFT	0x10
#define HD44780_FUNCTIONSET	0x20
#define HD44780_SETCGRAMADDR	0x40
#define HD44780_SETDDRAMADDR	0x80

/** HD44780 Entry Mode Set constants */
#define HD44780_ENTRYMODESET_RIGHT	0x00
#define HD44780_ENTRYMODESET_LEFT	0x02
#define HD44780_ENTRYMODESET_SHIFTINC	0x01
#define HD44780_ENTRYMODESET_SHIFTDEC	0x00

/** HD44780 Display Control constants */
#define HD44780_DISPLAYCONTROL_DISPLAYON	0x04
#define HD44780_DISPLAYCONTROL_DISPLAYOFF	0x00
#define HD44780_DISPLAYCONTROL_CURSORON	0x02
#define HD44780_DISPLAYCONTROL_CURSOROFF	0x00
#define HD44780_DISPLAYCONTROL_BLINKON	0x01
#define HD44780_DISPLAYCONTROL_BLINKOFF	0x00

/** HD44780 Cursor Shift constants */
#define HD44780_CURSORSHIFT_DISPLAY	0x08
#define HD44780_CURSORSHIFT_CURSOR	0x00
#define HD44780_CURSORSHIFT_RIGHT	0x04
#define HD44780_CURSORSHIFT_LEFT	0x00

/** HD44780 Function Set constants */
#define HD44780_FUNCTIONSET_8BITMODE	0x10
#define HD44780_FUNCTIONSET_4BITMODE	0x00
#define HD44780_FUNCTIONSET_2LINE	0x08
#define HD44780_FUNCTIONSET_1LINE	0x00
#define HD44780_FUNCTIONSET_5X10DOTS	0x04
#define HD44780_FUNCTIONSET_5X8DOTS	0x00

/** HD44780 Row Offset constants (4 rows) */
static const uint8_t HD44780_ROW_OFFSETS[4] = {0x00, 0x40, 0x14, 0x54};

/** HD44780 specific types */
typedef struct _HD44780_CONSOLE HD44780_CONSOLE;
struct _HD44780_CONSOLE
{
	// Console Properties
	CONSOLE_DEVICE console;
	// HD44780 Properties
	GPIO_DEVICE *gpio; ///< The GPIO device this Console is connected to
	uint32_t rs; ///< The GPIO pin for the RS line
	uint32_t rw; ///< The GPIO pin for the RW line
	uint32_t en; ///< The GPIO pin for the EN line
	uint32_t d4; ///< The GPIO pin for the D4 line
	uint32_t d5; ///< The GPIO pin for the D5 line
	uint32_t d6; ///< The GPIO pin for the D6 line
	uint32_t d7; ///< The GPIO pin for the D7 line
	uint8_t entrymode; ///< Current value of the Entry Mode settings
	uint8_t functionset; ///< Current value of the Function Set settings
	uint8_t displaycontrol; ///< Current value of the Display Control settings
	// Cursor Properties
	uint8_t cursorx;
	uint8_t cursory;
	// Buffer Properties
	uint32_t size;
	uint8_t *buffer;
};

/** HD44780 Functions */
CONSOLE_DEVICE * STDCALL hd44780_console_create(GPIO_DEVICE *gpio, char *name, uint32_t width, uint32_t height, uint32_t rs, uint32_t rw, uint32_t en, uint32_t d4, uint32_t d5, uint32_t d6, uint32_t d7);
uint32_t STDCALL hd44780_console_destroy(CONSOLE_DEVICE *console);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_HD44780_H
