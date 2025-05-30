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
#ifndef _ULTIBO_GOODIXTOUCH_H
#define _ULTIBO_GOODIXTOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"
#include "ultibo/touch.h"

/* ============================================================================== */
/* Goodix specific constants */
#define GOODIX_TOUCH_DESCRIPTION	"Goodix Touch Controller" // Description of Goodix Touch device

#define GOODIX_MAX_HEIGHT	4096
#define GOODIX_MAX_WIDTH	4096
#define GOODIX_INT_TRIGGER	1
#define GOODIX_CONTACT_SIZE	8
#define GOODIX_MAX_CONTACT_SIZE	9
#define GOODIX_MAX_CONTACTS	10
#define GOODIX_MAX_KEYS	7

#define GOODIX_CONFIG_MIN_LENGTH	186
#define GOODIX_CONFIG_911_LENGTH	186
#define GOODIX_CONFIG_967_LENGTH	228
#define GOODIX_CONFIG_GT9X_LENGTH	240
#define GOODIX_CONFIG_MAX_LENGTH	240

/* Goodix I2C constants */
#define GOODIX_I2C_RATE	400000 // Default I2C clock rate
#define GOODIX_CONFIG_TIMEOUT	3000 // Timeout to wait for firmware ready

/* Goodix register constants */
#define GOODIX_REG_COMMAND	0x8040
#define GOODIX_CMD_SCREEN_OFF	0x05

#define GOODIX_READ_COOR_ADDR	0x814E
#define GOODIX_GT1X_REG_CONFIG_DATA	0x8050
#define GOODIX_GT9X_REG_CONFIG_DATA	0x8047
#define GOODIX_REG_ID	0x8140

#define GOODIX_BUFFER_STATUS_READY	(1 << 7)
#define GOODIX_HAVE_KEY	(1 << 4)
#define GOODIX_BUFFER_STATUS_TIMEOUT	20

#define GOODIX_ID_MAX_LEN	4

#define GOODIX_RESOLUTION_OFFSET	1
#define GOODIX_MAX_CONTACTS_OFFSET	5
#define GOODIX_TRIGGER_OFFSET	6

static const uint32_t GOODIX_IRQ_TRIGGERS[4] = {GPIO_TRIGGER_RISING, GPIO_TRIGGER_FALLING, GPIO_TRIGGER_LOW, GPIO_TRIGGER_HIGH};

/* ============================================================================== */
/* Goodix specific types */
typedef struct _GOODIX_TOUCH GOODIX_TOUCH;
struct _GOODIX_TOUCH
{
	// Touch Properties
	TOUCH_DEVICE touch;
	// I2C Properties
	I2C_DEVICE *i2c; // The I2C device this device is connected to
	uint16_t address; // The I2C address of the device
	// General Properties
	GPIO_INFO irq; // The GPIO information for the IRQ line (Optional)
	GPIO_INFO rst; // The GPIO information for the Reset line (Optional)
	uint16_t maxx; // Maximum X value from current configuration
	uint16_t maxy; // Maximum Y value from current configuration
	uint16_t width; // Screen width value supplied during create
	uint16_t height; // Screen height value supplied during create
	uint32_t maxpoints; // Maximum touch points from current configuration
	uint32_t lastkeys; // Keys reported in last input report
	uint32_t lastpoints; // Points reported in last input report
	// Goodix Properties
	char *id; // ID String for this device
	uint16_t version; // Version number for this device
	uint16_t configaddress; // Configuration data address
	uint32_t configlength; // Configuration data length in bytes
	uint32_t checksumsize; // Configuration checksum size
	uint32_t contactsize; // Size of each contact point coordinate in touch data
	uint8_t configuration[GOODIX_CONFIG_MAX_LENGTH];
	uint16_t keycodes[GOODIX_MAX_KEYS];
	uint16_t scancodes[GOODIX_MAX_KEYS];
	BOOL swapconfigxy; // If True swap the max X and Y values in the configuration
	BOOL swapreportxy; // If True swap the X and Y values in the input report
	BOOL invertreportx; // If True invert the X value in the input report
	BOOL invertreporty; // If True invert the Y value in the input report
	char *configfilename; // The configuration filename to load during initialization
	BOOL resetcontroller; // If True reset the controller during initialization
};

typedef uint8_t GOODIX_POINT_DATA[2 + GOODIX_MAX_CONTACT_SIZE * GOODIX_MAX_CONTACTS];

/* ============================================================================== */
/* Initialization Functions */
void STDCALL goodix_init(void);

/* ============================================================================== */
/* Goodix Functions */
TOUCH_DEVICE * STDCALL goodix_touch_create(I2C_DEVICE *i2c, uint16_t address, uint32_t width, uint32_t height, GPIO_INFO *irq, GPIO_INFO *rst);
uint32_t STDCALL goodix_touch_destroy(TOUCH_DEVICE *touch);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_GOODIXTOUCH_H
