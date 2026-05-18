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
#ifndef _ULTIBO_FT5X06TOUCH_H
#define _ULTIBO_FT5X06TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"
#include "ultibo/touch.h"

/** FT5x06 specific constants */
#define FT5X06_TOUCH_DESCRIPTION	"EDT FocalTech FT5x06 Touch Controller" ///< Description of FT5x06 Touch device

/** FT5x06 I2C constants */
#define FT5X06_I2C_RATE	400000 ///< Default I2C clock rate

/** FT5x06 register constants */
#define FT5X06_WORK_REGISTER_THRESHOLD	0x00
#define FT5X06_WORK_REGISTER_REPORT_RATE	0x08
#define FT5X06_WORK_REGISTER_GAIN	0x30
#define FT5X06_WORK_REGISTER_OFFSET	0x31
#define FT5X06_WORK_REGISTER_NUM_X	0x33
#define FT5X06_WORK_REGISTER_NUM_Y	0x34

#define FT5X06_PMOD_REGISTER_ACTIVE	0x00
#define FT5X06_PMOD_REGISTER_HIBERNATE	0x03

#define FT5X06_M09_REGISTER_THRESHOLD	0x80
#define FT5X06_M09_REGISTER_GAIN	0x92
#define FT5X06_M09_REGISTER_OFFSET	0x93
#define FT5X06_M09_REGISTER_NUM_X	0x94
#define FT5X06_M09_REGISTER_NUM_Y	0x95

#define FT5X06_EV_REGISTER_THRESHOLD	0x40
#define FT5X06_EV_REGISTER_GAIN	0x41
#define FT5X06_EV_REGISTER_OFFSET_Y	0x45
#define FT5X06_EV_REGISTER_OFFSET_X	0x46

#define FT5X06_NO_REGISTER	0xff

#define FT5X06_WORK_REGISTER_OPMODE	0x3c
#define FT5X06_FACTORY_REGISTER_OPMODE	0x01
#define FT5X06_PMOD_REGISTER_OPMODE	0xa5

#define FT5X06_TOUCH_EVENT_DOWN	0x00
#define FT5X06_TOUCH_EVENT_UP	0x01
#define FT5X06_TOUCH_EVENT_ON	0x02
#define FT5X06_TOUCH_EVENT_RESERVED	0x03

#define FT5X06_EDT_NAME_LEN	23
#define FT5X06_EDT_SWITCH_MODE_RETRIES	10
#define FT5X06_EDT_SWITCH_MODE_DELAY	5 ///< msec
#define FT5X06_EDT_RAW_DATA_RETRIES	100
#define FT5X06_EDT_RAW_DATA_DELAY	1000 ///< usec

#define FT5X06_POLL_INTERVAL_MS	17 ///< 17ms = 60fps

/** FT5x06 version constants */
#define FT5X06_EDT_M06	0
#define FT5X06_EDT_M09	1
#define FT5X06_EDT_M12	2
#define FT5X06_EV_FT	3
#define FT5X06_GENERIC_FT	4

/** FT5x06 specific types */
typedef struct _FT5X06_REGISTERS FT5X06_REGISTERS;
struct _FT5X06_REGISTERS
{
	uint8_t threshold;
	uint8_t reportrate;
	uint8_t gain;
	uint8_t offset;
	uint8_t offsetx;
	uint8_t offsety;
	uint8_t numx;
	uint8_t numy;
};


typedef struct _FT5X06_PARAMETERS FT5X06_PARAMETERS;
struct _FT5X06_PARAMETERS
{
	uint8_t threshold;
	uint8_t reportrate;
	uint8_t gain;
	uint8_t offset;
	uint8_t offsetx;
	uint8_t offsety;
	uint8_t numx;
	uint8_t numy;
};


typedef struct _FT5X06_TOUCH FT5X06_TOUCH;
struct _FT5X06_TOUCH
{
	// Touch Properties
	TOUCH_DEVICE touch;
	// I2C Properties
	I2C_DEVICE *i2c; ///< The I2C device this device is connected to
	uint16_t address; ///< The I2C address of the device
	// General Properties
	GPIO_INFO irq; ///< The GPIO information for the IRQ line (Optional)
	GPIO_INFO rst; ///< The GPIO information for the Reset line (Optional)
	TIMER_HANDLE timer; ///< Handle for touch polling timer
	uint16_t maxx; ///< Maximum X value from current configuration
	uint16_t maxy; ///< Maximum Y value from current configuration
	uint16_t width; ///< Screen width value supplied during create
	uint16_t height; ///< Screen height value supplied during create
	uint32_t maxpoints; ///< Maximum touch points for this device
	uint32_t lastpoints; ///< Points reported in last input report
	// FT5x06 Properties
	uint32_t version; ///< Version constant for this device (eg FT5X06_EDT_M06)
	char *modelname; ///< Model name string for this device
	char *firmwareversion; ///< Firmware version string for this device
	FT5X06_REGISTERS registers; ///< Register addresses for this device
	FT5X06_PARAMETERS parameters; ///< Configuration parameters for this device
	BOOL swapreportxy; ///< If True swap the X and Y values in the input report
	BOOL invertreportx; ///< If True invert the X value in the input report
	BOOL invertreporty; ///< If True invert the Y value in the input report
};

/** Initialization Functions */
void STDCALL ft5x06_init(void);

/** FT5x06 Functions */

/**
 * @brief Create, register and start a new FT5x06 Touch device connected to the specified I2C device
 * @param I2C The I2C device this FT5x06 Touch device is connected to
 * @param Address The I2C address for this FT5x06 Touch device
 * @param Width The width of the screen in pixels (When set at TOUCH_ROTATION_0)
 * @param Height The height of the screen in pixels (When set at TOUCH_ROTATION_0)
 * @param IRQ The GPIO information for the IRQ line (Optional)
 * @return Pointer to the new Touch device or nil on failure
 */
TOUCH_DEVICE * STDCALL ft5x06_touch_create(I2C_DEVICE *i2c, uint16_t address, uint32_t width, uint32_t height, GPIO_INFO *irq, GPIO_INFO *rst);

/**
 * @brief Stop, deregister and destroy a FT5x06 Touch device created by this driver
 * @param Touch The Touch device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL ft5x06_touch_destroy(TOUCH_DEVICE *touch);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_FT5X06TOUCH_H
