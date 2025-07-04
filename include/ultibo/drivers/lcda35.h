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
#ifndef _ULTIBO_LCDA35_H
#define _ULTIBO_LCDA35_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/spi.h"
#include "ultibo/pwm.h"
#include "ultibo/framebuffer.h"
#include "ultibo/touch.h"

/* ============================================================================== */
/* LCDA35 specific constants */
#define LCDA35_FRAMEBUFFER_DESCRIPTION	"Waveshare RPi LCD(A) 3.5""

#define LCDA35_SIGNATURE	0xAF000A35

#define LCDA35_SCREEN_WIDTH	320
#define LCDA35_SCREEN_HEIGHT	480

/* LCDA35 GPIO constants */
#define LCDA35_LCD_DC	GPIO_PIN_24
#define LCDA35_LCD_RST	GPIO_PIN_25
#define LCDA35_LCD_BL	GPIO_PIN_UNKNOWN // Not supported on this screen

#define LCDA35_TOUCH_IRQ	GPIO_PIN_17

/* ============================================================================== */
/* LCDA35 specific types */
typedef struct _LCDA35LCD LCDA35LCD;
struct _LCDA35LCD
{
	uint32_t signature; // Signature for entry validation
	uint32_t rotation; // Framebuffer rotation (eg FRAMEBUFFER_ROTATION_180)
	uint32_t direction; // Framebuffer direction (eg FRAMEBUFFER_DIRECTION_REVERSE)
	SPI_DEVICE *spi; // SPI device for this display
	GPIO_DEVICE *gpio; // GPIO device for this display
	TOUCH_DEVICE *touch; // Touch device for this display
	GPIO_DEVICE *backlight; // Backlight GPIO device for this display
	FRAMEBUFFER_DEVICE *framebuffer; // Framebuffer (ILI9486) device for this display
};

/* ============================================================================== */
/* LCDA35 Functions */
HANDLE STDCALL lcda35_start(uint32_t rotation, char *device, uint16_t displayselect, uint16_t touchselect);
BOOL STDCALL lcda35_stop(HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_LCDA35_H
