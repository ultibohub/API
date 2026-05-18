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
#ifndef _ULTIBO_PITFT35_H
#define _ULTIBO_PITFT35_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/spi.h"
#include "ultibo/pwm.h"
#include "ultibo/framebuffer.h"
#include "ultibo/touch.h"

/** PiTFT35 specific constants */
#define PITFT35_FRAMEBUFFER_DESCRIPTION	"Adafruit PiTFT 3.5" LCD" ///< Description of PiTFT35 device

#define PITFT35_SIGNATURE	0xAF000035

#define PITFT35_SCREEN_WIDTH	320
#define PITFT35_SCREEN_HEIGHT	480

/** PiTFT35 GPIO constants */
#define PITFT35_LCD_DC	GPIO_PIN_25
#define PITFT35_TOUCH_IRQ	GPIO_PIN_24

#define PITFT35_LCD_BL	GPIO_PIN_2 ///< STMPE GPIO
#define PITFT35_LCD_BL_PWM	GPIO_PIN_18

/** PiTFT35 specific types */
typedef struct _PITFT35LCD PITFT35LCD;
struct _PITFT35LCD
{
	uint32_t signature; ///< Signature for entry validation
	uint32_t rotation; ///< Framebuffer rotation (eg FRAMEBUFFER_ROTATION_180)
	SPI_DEVICE *spi; ///< SPI device for this display
	GPIO_DEVICE *gpio; ///< GPIO device for this display
	TOUCH_DEVICE *touch; ///< Touch (STMPE) device for this display
	GPIO_DEVICE *backlight; ///< Backlight GPIO (STMPE) device for this display
	FRAMEBUFFER_DEVICE *framebuffer; ///< Framebuffer (HX8357D) device for this display
};

/** PiTFT35 Functions */

/**
 * @brief Start the PiTFT35 driver and register the Touch, Backlight (GPIO) and Framebuffer devices associated with the display
 * @param Rotation The rotation of the display (eg FRAMEBUFFER_ROTATION_180)
 * @param Device The SPI device that the HX8357D and STMPE610 devices are connected to
 * @param DisplaySelect The SPI chip select of the HX8357D LCD controller
 * @param TouchSelect The SPI chip select of the STMPE610 touch controller
 * @return The handle of the PiTFT35 on success or INVALID_HANDLE_VALUE on failure
 * @note This function will be called during startup if the parameter PITFT35_AUTOSTART is True
 *        Can be called multiple times to support more than one PiTFT LCD display
 */
HANDLE STDCALL pitft35_start(uint32_t rotation, char *device, uint16_t displayselect, uint16_t touchselect);

/**
 * @brief Stop the PiTFT35 driver and deregister the Touch, Backlight (GPIO) and Framebuffer devices associated with the display
 * @param Handle The handle of the PiTFT35 or INVALID_HANDLE_VALUE for the default display
 * @return True if completed or False on failure
 */
BOOL STDCALL pitft35_stop(HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PITFT35_H
