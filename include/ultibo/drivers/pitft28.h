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
#ifndef _ULTIBO_PITFT28_H
#define _ULTIBO_PITFT28_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"
#include "ultibo/spi.h"
#include "ultibo/framebuffer.h"
#include "ultibo/touch.h"

/** PiTFT28 specific constants */
#define PITFT28_FRAMEBUFFER_DESCRIPTION	"Adafruit PiTFT 2.8" LCD" ///< Description of PiTFT28 device

#define PITFT28_SIGNATURE	0xAF000028

#define PITFT28_SCREEN_WIDTH	240
#define PITFT28_SCREEN_HEIGHT	320

/** PiTFT28 GPIO constants */
#define PITFT28_LCD_DC	GPIO_PIN_25
#define PITFT28_TOUCH_IRQ	GPIO_PIN_24

#define PITFT28_LCD_BL	GPIO_PIN_2 ///< STMPE GPIO

/** PiTFT28 specific types */
typedef struct _PITFT28LCD PITFT28LCD;
struct _PITFT28LCD
{
	uint32_t signature; ///< Signature for entry validation
	uint32_t rotation; ///< Framebuffer rotation (eg FRAMEBUFFER_ROTATION_180)
	SPI_DEVICE *spi; ///< SPI device for this display
	I2C_DEVICE *i2c; ///< I2C device for this display
	GPIO_DEVICE *gpio; ///< GPIO device for this display
	TOUCH_DEVICE *touch; ///< Touch (STMPE or FT6236) device for this display
	GPIO_DEVICE *backlight; ///< Backlight GPIO (STMPE) device for this display
	FRAMEBUFFER_DEVICE *framebuffer; ///< Framebuffer (ILI9340) device for this display
};

/** PiTFT28 Functions */
HANDLE STDCALL pitft28_start(uint32_t rotation, char *device, uint16_t displayselect, uint16_t touchselect);
HANDLE STDCALL pitft28_resistive_start(uint32_t rotation, char *device, uint16_t displayselect, uint16_t touchselect);
HANDLE STDCALL pitft28_capacitive_start(uint32_t rotation, char *spidevice, char *i2cdevice, uint16_t displayselect, uint16_t touchaddress);
BOOL STDCALL pitft28_stop(HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif //  _ULTIBO_PITFT28_H
