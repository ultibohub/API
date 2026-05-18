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
#ifndef _ULTIBO_IPSTFT19_H
#define _ULTIBO_IPSTFT19_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/spi.h"
#include "ultibo/framebuffer.h"

/** IPSTFT19 specific constants */
#define IPSTFT19_FRAMEBUFFER_DESCRIPTION	"Adafruit 1.9" IPS TFT" ///< Description of IPSTFT19 device

#define IPSTFT19_SIGNATURE	0xAF000019

#define IPSTFT19_SCREEN_WIDTH	170
#define IPSTFT19_SCREEN_HEIGHT	320
#define IPSTFT19_COLSTART	35
#define IPSTFT19_DEFAULT_ROTATION	FRAMEBUFFER_ROTATION_90

/** IPSTFT19 GPIO constants */
#define IPSTFT19_LCD_DC	GPIO_PIN_25
#define IPSTFT19_LCD_RST	GPIO_PIN_27 ///< Add this one
#define IPSTFT19_LCD_BL	GPIO_PIN_18

/** IPSTFT19 specific types */
typedef struct _IPSTFT19LCD IPSTFT19LCD;
struct _IPSTFT19LCD
{
	uint32_t signature; ///< Signature for entry validation
	uint32_t rotation; ///< Framebuffer rotation (eg FRAMEBUFFER_ROTATION_180)
	SPI_DEVICE *spi; ///< SPI device for this display
	GPIO_DEVICE *gpio; ///< GPIO device for this display
	FRAMEBUFFER_DEVICE *framebuffer; ///< Framebuffer (ST7789) device for this display
};

/** IPSTFT19 Functions */

/**
 * @brief Start the IPSTFT19 driver and Framebuffer device associated with the display
 * @param Rotation The rotation of the display (eg FRAMEBUFFER_ROTATION_180)
 * @param Device The SPI device that the ST7789 device is connected to
 * @param DisplaySelect The SPI chip select of the ST7789 LCD controller
 * @return The handle of the IPSTFT19 on success or INVALID_HANDLE_VALUE on failure
 * @note This function will be called during startup if the parameter IPSTFT19_AUTOSTART is True
 *        Can be called multiple times to support more than one IPSTFT LCD display
 */
HANDLE STDCALL ipstft19_start(uint32_t rotation, char *device, uint16_t displayselect);

/**
 * @brief Stop the IPSTFT19 driver and Framebuffer device associated with the display
 * @param Handle The handle of the IPSTFT19 or INVALID_HANDLE_VALUE for the default display
 * @return True if completed or False on failure
 */
BOOL STDCALL ipstft19_stop(HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_IPSTFT19_H
