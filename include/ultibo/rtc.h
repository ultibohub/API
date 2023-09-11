/*
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Garry Wood <garry@softoz.com.au>
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
#ifndef _ULTIBO_RTC_H
#define _ULTIBO_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"
#include "ultibo/sysutils.h"

/* ============================================================================== */
/* RTC specific constants */
#define RTC_NAME_PREFIX	"RTC" // Name prefix for RTC Devices

/* RTC Device Types */
#define RTC_TYPE_NONE	0

#define RTC_TYPE_MAX	0

/* RTC Device States */
#define RTC_STATE_DISABLED	0
#define RTC_STATE_ENABLED	1

#define RTC_STATE_MAX	1

/* RTC Device Flags */
#define RTC_FLAG_NONE	0x00000000
#define RTC_FLAG_ALARM	0x00000001 // Device supports one or more alarms
#define RTC_FLAG_WATCHDOG	0x00000002 // Device has a watchdog timer function

/* ============================================================================== */
/* RTC specific types */

/* RTC Properties */
typedef struct _RTC_PROPERTIES RTC_PROPERTIES;
struct _RTC_PROPERTIES
{
	uint32_t flags; // Device flags (eg RTC_FLAG_ALARM)
	int64_t mintime; // Minimum time value represented by the device (Normally the power on reset value)
	int64_t maxtime; // Maximum time value represented by the device (Time when a rollover will occur)
	uint32_t alarmcount; // Number of alarms supported by the device (0 if not supported)
};

/* RTC Device */
typedef struct _RTC_DEVICE RTC_DEVICE;

/* RTC Enumeration Callback */
typedef uint32_t STDCALL (*rtc_enumerate_cb)(RTC_DEVICE *rtc, void *data);
/* RTC Notification Callback */
typedef uint32_t STDCALL (*rtc_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* RTC Device Methods */
typedef uint32_t STDCALL (*rtc_device_start_proc)(RTC_DEVICE *rtc);
typedef uint32_t STDCALL (*rtc_device_stop_proc)(RTC_DEVICE *rtc);
typedef int64_t STDCALL (*rtc_device_get_time_proc)(RTC_DEVICE *rtc);
typedef int64_t STDCALL (*rtc_device_set_time_proc)(RTC_DEVICE *rtc, int64_t time);
typedef uint32_t STDCALL (*rtc_device_get_properties_proc)(RTC_DEVICE *rtc, RTC_PROPERTIES *properties);

struct _RTC_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this RTC
	// RTC Properties
	uint32_t rtcid; // Unique Id of this RTC in the RTC table
	uint32_t rtcstate; // RTC state (eg RTC_STATE_ENABLED)
	rtc_device_start_proc devicestart; // A Device specific DeviceStart method implementing the standard RTC device interface
	rtc_device_stop_proc devicestop; // A Device specific DeviceStop method implementing the standard RTC device interface
	rtc_device_get_time_proc devicegettime; // A Device specific DeviceGetTime method implementing the standard RTC device interface
	rtc_device_set_time_proc devicesettime; // A Device specific DeviceSetTime method implementing the standard RTC device interface
	rtc_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing the standard RTC device interface
	// Statistics Properties
	uint32_t getcount;
	uint32_t setcount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	RTC_PROPERTIES properties; // Device properties
	// Internal Properties
	RTC_DEVICE *prev; // Previous entry in RTC table
	RTC_DEVICE *next; // Next entry in RTC table
};

/* ============================================================================== */
/* RTC Functions */
uint32_t STDCALL rtc_device_start(RTC_DEVICE *rtc);
uint32_t STDCALL rtc_device_stop(RTC_DEVICE *rtc);

int64_t STDCALL rtc_device_get_time(RTC_DEVICE *rtc);
int64_t STDCALL rtc_device_set_time(RTC_DEVICE *rtc, int64_t time);

uint32_t STDCALL rtc_device_properties(RTC_DEVICE *rtc, RTC_PROPERTIES *properties);
uint32_t STDCALL rtc_device_get_properties(RTC_DEVICE *rtc, RTC_PROPERTIES *properties);

RTC_DEVICE * STDCALL rtc_device_create(void);
RTC_DEVICE * STDCALL rtc_device_create_ex(uint32_t size);
uint32_t STDCALL rtc_device_destroy(RTC_DEVICE *rtc);

uint32_t STDCALL rtc_device_register(RTC_DEVICE *rtc);
uint32_t STDCALL rtc_device_deregister(RTC_DEVICE *rtc);

RTC_DEVICE * STDCALL rtc_device_find(uint32_t rtcid);
RTC_DEVICE * STDCALL rtc_device_find_by_name(char *name);
RTC_DEVICE * STDCALL rtc_device_find_by_description(char *description);
uint32_t STDCALL rtc_device_enumerate(rtc_enumerate_cb callback, void *data);

uint32_t STDCALL rtc_device_notification(RTC_DEVICE *rtc, rtc_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* RTC Helper Functions */
uint32_t STDCALL rtc_get_count(void);
RTC_DEVICE * STDCALL rtc_device_get_default(void);
uint32_t STDCALL rtc_device_set_default(RTC_DEVICE *rtc);

RTC_DEVICE * STDCALL rtc_device_check(RTC_DEVICE *rtc);

uint32_t STDCALL rtc_device_type_to_string(uint32_t rtctype, char *string, uint32_t len);
uint32_t STDCALL rtc_device_state_to_string(uint32_t rtcstate, char *string, uint32_t len);

BOOL STDCALL rtc_time_is_valid(SYSTEMTIME *time);

BOOL STDCALL rtc_systemtime_to_filetime(SYSTEMTIME *systemtime, int64_t *filetime);
BOOL STDCALL rtc_filetime_to_systemtime(int64_t filetime, SYSTEMTIME *systemtime);

#endif // _ULTIBO_RTC_H