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
#ifndef _ULTIBO_DS1307_H
#define _ULTIBO_DS1307_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/i2c.h"
#include "ultibo/rtc.h"

/* ============================================================================== */
/* DS1307 specific constants */
#define DS1307_RTC_DESCRIPTION	"Maxim DS1307 Real Time Clock" // Description of DS1307 device

#define DS1307_MIN_TIME	125911584000000000 // Time starts at 01/01/2000 00:00:00 (MM/DD/YY HH:MM:SS)
#define DS1307_MAX_TIME	157469183990000000 // Time ends at 12/31/2099 23:59:59 (MM/DD/YY HH:MM:SS)

/* DS1307 chip constants */
#define DS1307_CHIP_DS1307	0
#define DS1307_CHIP_DS1337	1
#define DS1307_CHIP_DS1338	2
#define DS1307_CHIP_DS1339	3
#define DS1307_CHIP_DS1340	4
#define DS1307_CHIP_DS1388	5
#define DS1307_CHIP_DS3231	6
#define DS1307_CHIP_M41T00	7
#define DS1307_CHIP_MCP794XX	8
#define DS1307_CHIP_RX8025	9

/* DS1307 RTC registers */
#define DS1307_REG_SECONDS	0x00 // 00-59
#define DS1307_REG_MINUTE	0x01 // 00-59
#define DS1307_REG_HOUR	0x02 // 00-23 (or 1-12am,pm)
#define DS1307_REG_WEEKDAY	0x03 // 01-07
#define DS1307_REG_DAY	0x04 // 01-31
#define DS1307_REG_MONTH	0x05 // 01-12
#define DS1307_REG_YEAR	0x06 // 00-99

/* DS1307 Control and Status registers */
#define DS1307_REG_CONTROL	0x07 // Also DS1338
#define DS1337_REG_CONTROL	0x0e
#define DS1340_REG_CONTROL	0x07
#define DS1340_REG_FLAG	0x09
#define DS1337_REG_STATUS	0x0f
#define DS1339_REG_ALARM1_SECONDS	0x07
#define RX8025_REG_CONTROL1	0x0e
#define RX8025_REG_CONTROL2	0x0f

/* DS1307 Seconds register bits */
#define DS1307_REG_SECONDS_CH	0x80 // Clock Halt bit (1 to Disable / 0 to Enable the clock)
#define DS1340_REG_SECONDS_nEOSC	0x80
#define MCP794XX_REG_SECONDS_ST	0x80 // Clock Stop Bit (1 to Enable / 0 to Disable the clock)

/* DS1307 Hour register bits */
#define DS1307_REG_HOUR_12HR	0x40 // 12/24 hour bit (1 = 12 hour mode / 0 = 24 hour mode)
#define DS1307_REG_HOUR_PM	0x20 // AM/PM bit (1 = PM / 0 = AM) (Only in 12 hour mode)
#define DS1340_REG_HOUR_CENTURY_EN	0x80
#define DS1340_REG_HOUR_CENTURY	0x40

/* MCP794XX Weekday register bits */
#define MCP794XX_REG_WEEKDAY_VBATEN	0x08 // Battery Backup Enabled (1 to Enable / 0 to Disable)

/* DS1337 Month register bits */
#define DS1337_REG_MONTH_CENTURY	0x80

/* DS1307 Control register bits */
#define DS1307_REG_CONTROL_OUT	0x80 // Output Control (Output level of SQW/OUT pin when SQWE = 0)
#define DS1338_REG_CONTROL_OSF	0x20
#define DS1307_REG_CONTROL_SQWE	0x10 // Square-Wave Enable (When set to 1, enables the oscillator output)
#define DS1307_REG_CONTROL_RS1	0x02 // Rate Select 1 (See datasheet for values)
#define DS1307_REG_CONTROL_RS0	0x01 // Rate Select 2 (See datasheet for values)

/* DS1337 Control register bits */
#define DS1337_REG_CONTROL_nEOSC	0x80
#define DS1339_REG_CONTROL_BBSQI	0x20
#define DS3231_REG_CONTROL_BBSQW	0x40 // same as BBSQI
#define DS1337_REG_CONTROL_RS2	0x10
#define DS1337_REG_CONTROL_RS1	0x08
#define DS1337_REG_CONTROL_INTCN	0x04
#define DS1337_REG_CONTROL_A2IE	0x02
#define DS1337_REG_CONTROL_A1IE	0x01

/* DS1340 Control register bits */
#define DS1340_REG_CONTROL_OUT	0x80
#define DS1340_REG_CONTROL_FT	0x40
#define DS1340_REG_CONTROL_CALIB_SIGN	0x20
#define DS1340_REG_CONTROL_M_CALIBRATION	0x1f

/* DS1340 Flag register bits */
#define DS1340_REG_FLAG_OSF	0x80

/* DS1337 Status register bits */
#define DS1337_REG_STATUS_OSF	0x80
#define DS1337_REG_STATUS_A2I	0x02
#define DS1337_REG_STATUS_A1I	0x01

/* RX8025 Control1 register bits */
#define RX8025_REG_CONTROL1_2412	0x20

/* RX8025 Control2 register bits */
#define RX8025_REG_CONTROL2_PON	0x10
#define RX8025_REG_CONTROL2_VDET	0x40
#define RX8025_REG_CONTROL2_XST	0x20

/* ============================================================================== */
/* DS1307 specific types */
typedef uint8_t DS1307_RTC_TIME[7];

typedef struct _DS1307_RTC_DEVICE DS1307_RTC_DEVICE;
struct _DS1307_RTC_DEVICE
{
	// RTC Properties
	RTC_DEVICE rtc;
	// DS1307 Properties
	I2C_DEVICE *i2c; // The I2C device this RTC is connected to
	uint16_t address; // The I2C address of the device
	uint32_t chip; // The chip type (eg DS1307_CHIP_DS1307)
	uint8_t rtcreg; // The register offset for the RTC
	uint8_t nvramreg; // The register offset for the NVRAM
	uint8_t nvramsize; // The NVRAM size
	uint8_t controlreg; // The control register offset
	// Statistics Properties
	uint32_t readcount; // Number of direct RTC/NVRAM/Control reads to the device
	uint32_t writecount; // Number of direct RTC/NVRAM/Control writes to the device
};


/* ============================================================================== */
/* DS1307 Functions */
RTC_DEVICE * STDCALL ds1307_rtc_create(char *device, uint16_t address, uint32_t chip);
uint32_t STDCALL ds1307_rtc_destroy(RTC_DEVICE *rtc);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_DS1307_H
