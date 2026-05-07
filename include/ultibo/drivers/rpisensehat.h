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
#ifndef _ULTIBO_RPISENSEHAT_H
#define _ULTIBO_RPISENSEHAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"
#include "ultibo/keyboard.h"
#include "ultibo/framebuffer.h"

/** RPiSenseHat specific constants */
#define RPISENSE_SIGNATURE	0xEAEBECED

/** Framebuffer */
#define RPISENSE_FRAMEBUFFER_DESCRIPTION	"Raspberry Pi Sense HAT Framebuffer" ///< Description of RPiSense framebuffer device

#define RPISENSE_PHYSICAL_WIDTH	8
#define RPISENSE_PHYSICAL_HEIGHT	8

/** Joystick */
#define RPISENSE_JOYSTICK_DESCRIPTION	"Raspberry Pi Sense HAT Joystick" ///< Description of RPiSense joystick device

static const uint16_t RPISENSE_JOYSTICK_KEYMAP[5] = {
 SCAN_CODE_DOWN_ARROW,
 SCAN_CODE_RIGHT_ARROW,
 SCAN_CODE_UP_ARROW,
 SCAN_CODE_ENTER,
 SCAN_CODE_LEFT_ARROW};

/** RPiSenseHat register values */
#define RPISENSE_FB	0x00
#define RPISENSE_WAI	0xF0
#define RPISENSE_VER	0xF1
#define RPISENSE_KEYS	0xF2
#define RPISENSE_EE_WP	0xF3

/** RPiSenseHat gamma reset values */
#define RPISENSE_GAMMA_VALUES_DEFAULT	0
#define RPISENSE_GAMMA_VALUES_LOW	1
#define RPISENSE_GAMMA_VALUES_USER	2

/** RPiSenseHat specific types */
typedef struct _RPISENSE RPISENSE;
struct _RPISENSE
{
	uint32_t signature; ///< Signature for entry validation
	I2C_DEVICE *i2c; ///< I2C device
	GPIO_DEVICE *gpio; ///< GPIO device
	FRAMEBUFFER_DEVICE *framebuffer; ///< Framebuffer device
	KEYBOARD_DEVICE *joystick; ///< Joystick (Keyboard) device
};

typedef struct _RPISENSE_FRAMEBUFFER RPISENSE_FRAMEBUFFER;
struct _RPISENSE_FRAMEBUFFER
{
	// Framebuffer Properties
	FRAMEBUFFER_DEVICE framebuffer;
	// RPiSense Properties
	I2C_DEVICE *i2c; ///< The I2C device the device is connected to
	uint32_t width; ///< Framebuffer Width in Pixels (Virtual)
	uint32_t height; ///< Framebuffer Height in Pixels (Virtual)
	uint32_t rotation; ///< Framebuffer Rotation (eg FRAMEBUFFER_ROTATION_180)
	uint32_t dirtyy1; ///< First line of dirty region (or Height - 1 if none dirty)
	uint32_t dirtyy2; ///< Last line of dirty region (or 0 if none dirty)
	LONGBOOL ready; ///< If True timer should be enabled during Mark operation
	LONGBOOL blank; ///< If True then display is currently blanked
	MUTEX_HANDLE lock; ///< Lock for dirty region redraw
	TIMER_HANDLE timer; ///< Handle for dirty region redraw timer
	uint32_t framerate; ///< Frame rate for display refresh (in Frames Per Second)
	uint8_t gamma[32]; ///< Current gamma values
	uint8_t gammauser[32]; ///< User gamma values
	uint16_t pixeldata[64]; ///< Pixel data for framebuffer update
	uint8_t blockdata[193]; ///< Block data for display update
};


typedef struct _RPISENSE_JOYSTICK RPISENSE_JOYSTICK;
struct _RPISENSE_JOYSTICK
{
	// Keyboard Properties
	KEYBOARD_DEVICE keyboard;
	// RPiSense Properties
	I2C_DEVICE *i2c; ///< The I2C device the device is connected to
	GPIO_DEVICE *gpio; ///< The GPIO device the device is connected to
	uint32_t pin; ///< The GPIO pin used to signal joystick events (GPIO_PIN_23)
	uint32_t trigger; ///< The GPIO trigger to detect joystick events (GPIO_TRIGGER_RISING)
	int32_t previouskeys; ///< The keys pressed on the last GPIO event callback
	// Statistics Properties
	uint32_t callbackcount; ///< Number of callback requests received by the device
};

/** RPiSenseHat Functions */
HANDLE STDCALL rpisense_start(char *i2cdevice, char *gpiodevice, uint32_t rotation, uint32_t width, uint32_t height);
BOOL STDCALL rpisense_stop(HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_RPISENSEHAT_H
