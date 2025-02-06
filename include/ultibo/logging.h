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
#ifndef _ULTIBO_LOGGING_H
#define _ULTIBO_LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"
#include "ultibo/console.h"

/* ============================================================================== */
/* Logging specific constants */
#define LOGGING_NAME_PREFIX	"Logging" // Name prefix for Logging Devices

#define LOGGING_THREAD_NAME	"Logging" // Thread name for Logging threads
#define LOGGING_THREAD_PRIORITY	THREAD_PRIORITY_NORMAL // Thread priority for Logging threads

/* Logging Device Types */
#define LOGGING_TYPE_NONE	0
#define LOGGING_TYPE_CONSOLE	1
#define LOGGING_TYPE_FILE	2
#define LOGGING_TYPE_SYSLOG	3
#define LOGGING_TYPE_SERIAL	4

/* Logging Device States */
#define LOGGING_STATE_DISABLED	0
#define LOGGING_STATE_ENABLED	1

/* Logging Device Flags */
#define LOGGING_FLAG_NONE	0x00000000

/* ============================================================================== */
/* Console Logging specific constants */
#define CONSOLE_LOGGING_DESCRIPTION	"Console Logging"

/* ============================================================================== */
/* Logging specific types */
typedef struct _LOGGING_ENTRY LOGGING_ENTRY;
struct _LOGGING_ENTRY
{
	char *data; // TMessage.Msg:PtrUInt
	size_t reserved1; // TMessage.wParam:PtrUInt
	ssize_t reserved2; // TMessage.lParam:PtrInt
	uint32_t reserved3; // TMessage.Time:LongWord
};

typedef struct _LOGGING_ENTRY_EX LOGGING_ENTRY_EX;
struct _LOGGING_ENTRY_EX
{
	char *content; // TMessage.Msg:PtrUInt
	char *tag; // TMessage.wParam:PtrUInt
	ssize_t severity; // TMessage.lParam:PtrInt
	uint32_t facility; // TMessage.Time:LongWord
};

typedef struct _LOGGING_DEVICE LOGGING_DEVICE;

/* Logging Enumeration Callback */
typedef uint32_t STDCALL (*logging_enumerate_cb)(LOGGING_DEVICE *logging, void *data);
/* Logging Notification Callback */
typedef uint32_t STDCALL (*logging_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Logging Device Methods */
typedef uint32_t STDCALL (*logging_device_start_proc)(LOGGING_DEVICE *logging);
typedef uint32_t STDCALL (*logging_device_stop_proc)(LOGGING_DEVICE *logging);
typedef uint32_t STDCALL (*logging_device_output_proc)(LOGGING_DEVICE *logging, const char *data);
typedef uint32_t STDCALL (*logging_device_output_ex_proc)(LOGGING_DEVICE *logging, uint32_t facility, uint32_t severity, const char *tag, const char *content); // Syslog compatible output
typedef char * STDCALL (*logging_device_get_target_proc)(LOGGING_DEVICE *logging);
typedef uint32_t STDCALL (*logging_device_set_target_proc)(LOGGING_DEVICE *logging, const char *target);

/* Logging Device */
struct _LOGGING_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Logging device
	// Logging Properties
	uint32_t loggingid; // Unique Id of this Logging device in the Logging device table
	uint32_t loggingstate; // Logging device state (eg LOGGING_STATE_ENABLED)
	logging_device_start_proc devicestart; // A device specific DeviceStart method implementing a standard logging device interface (Or nil if the default method is suitable)
	logging_device_stop_proc devicestop; // A device specific DeviceStop method implementing a standard logging device interface (Or nil if the default method is suitable)
	logging_device_output_proc deviceoutput; // A device specific DeviceOutput method implementing a standard logging device interface
	logging_device_output_ex_proc deviceoutputex; // A device specific DeviceOutputEx method implementing a standard logging device interface
	logging_device_get_target_proc devicegettarget; // A device specific DeviceGetTarget method implementing a standard logging device interface (Or nil if the default method is suitable)
	logging_device_set_target_proc devicesettarget; // A device specific DeviceSetTarget method implementing a standard logging device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t outputcount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	HANDLE handle; // Device output handle
	char *target; // Device output target
	LONGBOOL _default; // Device can be the default logging device
	// Internal Properties
	LOGGING_DEVICE *prev; // Previous entry in Logging device table
	LOGGING_DEVICE *next; // Next entry in Logging device table
};

/* ============================================================================== */
/* Logging Functions */
uint32_t STDCALL logging_device_start(LOGGING_DEVICE *logging);
uint32_t STDCALL logging_device_stop(LOGGING_DEVICE *logging);

uint32_t STDCALL logging_device_output(LOGGING_DEVICE *logging, const char *data);
uint32_t STDCALL logging_device_output_ex(LOGGING_DEVICE *logging, uint32_t facility, uint32_t severity, const char *tag, const char *content);

uint32_t STDCALL logging_device_get_target(LOGGING_DEVICE *logging, char *target, uint32_t len);
uint32_t STDCALL logging_device_set_target(LOGGING_DEVICE *logging, const char *target);

LOGGING_DEVICE * STDCALL logging_device_create(BOOL _default);
LOGGING_DEVICE * STDCALL logging_device_create_ex(uint32_t size, BOOL _default);
uint32_t STDCALL logging_device_destroy(LOGGING_DEVICE *logging);

uint32_t STDCALL logging_device_register(LOGGING_DEVICE *logging);
uint32_t STDCALL logging_device_deregister(LOGGING_DEVICE *logging);

LOGGING_DEVICE * STDCALL logging_device_find(uint32_t loggingid);
LOGGING_DEVICE * STDCALL logging_device_find_by_type(uint32_t loggingtype);
LOGGING_DEVICE * STDCALL logging_device_find_by_device(DEVICE *device);
LOGGING_DEVICE * STDCALL logging_device_find_by_name(const char *name);
LOGGING_DEVICE * STDCALL logging_device_find_by_description(const char *description);

uint32_t STDCALL logging_device_enumerate(logging_enumerate_cb callback, void *data);

uint32_t STDCALL logging_device_notification(LOGGING_DEVICE *logging, logging_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

int STDCALL logging_device_outputf(LOGGING_DEVICE *logging, const char *format, ...) _ATTRIBUTE ((__format__ (__printf__, 2, 3)));

/* ============================================================================== */
/* Logging Helper Functions */
uint32_t STDCALL logging_device_get_count(void);

LOGGING_DEVICE * STDCALL logging_device_get_default(void);
uint32_t STDCALL logging_device_set_default(LOGGING_DEVICE *logging);

LOGGING_DEVICE * STDCALL logging_device_check(LOGGING_DEVICE *logging);

uint32_t STDCALL logging_type_to_string(uint32_t loggingtype, char *string, uint32_t len);
uint32_t STDCALL logging_state_to_string(uint32_t loggingstate, char *string, uint32_t len);

BOOL STDCALL logging_device_redirect_output(LOGGING_DEVICE *logging);

uint32_t STDCALL logging_get_messageslot_flags(void);

uint32_t STDCALL logging_console_device_add(CONSOLE_DEVICE *console);
uint32_t STDCALL logging_console_device_remove(CONSOLE_DEVICE *console);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_LOGGING_H