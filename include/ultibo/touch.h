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
#ifndef _ULTIBO_TOUCH_H
#define _ULTIBO_TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* Touch specific constants */
#define TOUCH_NAME_PREFIX	"Touch" // Name prefix for Touch Devices

/* Touch Device Types */
#define TOUCH_TYPE_NONE	0
#define TOUCH_TYPE_RESISTIVE	1
#define TOUCH_TYPE_CAPACITIVE	2

#define TOUCH_TYPE_MAX	2

/* Touch Device States */
#define TOUCH_STATE_DISABLED	0
#define TOUCH_STATE_ENABLED	1

#define TOUCH_STATE_MAX	1

/* Touch Device Flags */
#define TOUCH_FLAG_NONE	0x00000000
#define TOUCH_FLAG_NON_BLOCK	0x00000001 // If set device reads are non blocking (Also supported in Flags parameter of TouchDeviceRead)
#define TOUCH_FLAG_PEEK_BUFFER	0x00000002 // Peek at the buffer to see if any data is available, don't remove it (Used only in Flags parameter of TouchDeviceRead)
#define TOUCH_FLAG_MOUSE_DATA	0x00000004 // If set the device will write a mouse data event for each touch event
#define TOUCH_FLAG_MULTI_POINT	0x00000008 // If set the device supports multi point touch
#define TOUCH_FLAG_PRESSURE	0x00000010 // If set the device supports pressure value on touch points
#define TOUCH_FLAG_SWAP_XY	0x00000020 // If set swap the X and Y coordinates
#define TOUCH_FLAG_INVERT_X	0x00000040 // If set invert the X coordinate
#define TOUCH_FLAG_INVERT_Y	0x00000080 // If set invert the Y coordinate
#define TOUCH_FLAG_SWAP_MAX_XY	0x00000100 // If set swap the maximum X and Y values
#define TOUCH_FLAG_RELEASE_TIMER	0x00000200 // If set enable the touch release timer for devices that don't provide release events

/* Flags supported by TOUCH_CONTROL_GET/SET/CLEAR_FLAG */
#define TOUCH_FLAG_MASK	TOUCH_FLAG_NON_BLOCK | TOUCH_FLAG_MOUSE_DATA | TOUCH_FLAG_MULTI_POINT | TOUCH_FLAG_PRESSURE | TOUCH_FLAG_SWAP_XY | TOUCH_FLAG_INVERT_X | TOUCH_FLAG_INVERT_Y | TOUCH_FLAG_SWAP_MAX_XY | TOUCH_FLAG_RELEASE_TIMER

/* Touch Device Control Codes */
#define TOUCH_CONTROL_GET_FLAG	1 // Get Flag
#define TOUCH_CONTROL_SET_FLAG	2 // Set Flag
#define TOUCH_CONTROL_CLEAR_FLAG	3 // Clear Flag
#define TOUCH_CONTROL_FLUSH_BUFFER	4 // Flush Buffer
#define TOUCH_CONTROL_GET_WIDTH	5 // Get Screen Width
#define TOUCH_CONTROL_GET_HEIGHT	6 // Get Screen Height
#define TOUCH_CONTROL_GET_MAX_X	7 // Get Maximum X value (Only applies to Absolute X values)
#define TOUCH_CONTROL_GET_MAX_Y	8 // Get Maximum Y value (Only applies to Absolute Y values)
#define TOUCH_CONTROL_GET_MAX_Z	9 // Get Maximum Z value (Only applies to Absolute Z values)
#define TOUCH_CONTROL_GET_MAX_POINTS	10 // Get Maximum number of Touch Points
#define TOUCH_CONTROL_GET_ROTATION	11 // Get Rotation value (0, 90, 180, 270)(Only where supported by the driver)
#define TOUCH_CONTROL_SET_ROTATION	12 // Set Rotation value (0, 90, 180, 270)(Only where supported by the driver)
#define TOUCH_CONTROL_GET_CALLBACK	13 // Get the registered callback function for touch events
#define TOUCH_CONTROL_SET_CALLBACK	14 // Set the registered callback function for touch events

/* Touch Buffer Size */
#define TOUCH_BUFFER_SIZE	1024

/* Touch Data Definitions (Values for TTouchData.Info) */
#define TOUCH_FINGER	0x00000001 // A finger is pressed at this touch point

/* Touch Data Definitions (Values for TTouchData.PointID) */
#define TOUCH_ID_UNKNOWN	(uint16_t)-1

/* Touch Data Definitions (Values for TTouchData.PositionX) */
#define TOUCH_X_UNKNOWN	-1

/* Touch Data Definitions (Values for TTouchData.PositionY) */
#define TOUCH_Y_UNKNOWN	-1

/* Touch Data Definitions (Values for TTouchData.PositionZ) */
#define TOUCH_Z_UNKNOWN	-1

/* Touch Rotation */
#define TOUCH_ROTATION_0	FRAMEBUFFER_ROTATION_0 // No rotation
#define TOUCH_ROTATION_90	FRAMEBUFFER_ROTATION_90 // 90 degree rotation
#define TOUCH_ROTATION_180	FRAMEBUFFER_ROTATION_180 // 180 degree rotation
#define TOUCH_ROTATION_270	FRAMEBUFFER_ROTATION_270 // 270 degree rotation

/* ============================================================================== */
/* Touch specific types */
/* Touch Data */
typedef struct _TOUCH_DATA TOUCH_DATA;
struct _TOUCH_DATA
{
	uint32_t info; // Bitmap of touch info values (eg TOUCH_FINGER)
	uint16_t pointid; // The touch point ID value for this touch (First ID is 1)
	int16_t positionx; // The X position of this touch point
	int16_t positiony; // The Y position of this touch point
	int16_t positionz; // The Z position of this touch point (If applicable)
	uint16_t touchwidth; // The Width of this touch point (If applicable)
	uint16_t touchheight; // The Height of this touch point (If applicable)
	void *parameter; // The parameter for the event callback (If applicable)
};

/* Touch Buffer */
typedef struct _TOUCH_BUFFER TOUCH_BUFFER;
struct _TOUCH_BUFFER
{
	SEMAPHORE_HANDLE wait; // Buffer ready semaphore
	uint32_t start; // Index of first buffer ready
	uint32_t count; // Number of entries ready in buffer
	TOUCH_DATA buffer[TOUCH_BUFFER_SIZE];
};

/* Touch Properties */
typedef struct _TOUCH_PROPERTIES TOUCH_PROPERTIES;
struct _TOUCH_PROPERTIES
{
	uint32_t flags; // Device flags (eg TOUCH_FLAG_MULTI_POINT)
	uint32_t width; // Screen Width
	uint32_t height; // Screen Height
	uint32_t rotation; // Screen Rotation (eg TOUCH_ROTATION_180)
	uint32_t maxx; // Maximum (absolute) X position for the touch device
	uint32_t maxy; // Maximum (absolute) Y position for the touch device
	uint32_t maxz; // Maximum (absolute) Z position for the touch device (If applicable)
	uint32_t maxwidth; // Maximum touch width value for the touch device (If applicable)
	uint32_t maxheight; // Maximum touch height value for the touch device (If applicable)
	uint32_t maxpoints; // Maximum number of touch points
};

/* Touch Device */
typedef struct _TOUCH_DEVICE TOUCH_DEVICE;

/* Touch Event Callback */
typedef uint32_t STDCALL (*touch_event_cb)(TOUCH_DEVICE *touch, TOUCH_DATA *data);

/* Touch Enumeration Callback */
typedef uint32_t STDCALL (*touch_enumerate_cb)(TOUCH_DEVICE *touch, void *data);
/* Touch Notification Callback */
typedef uint32_t STDCALL (*touch_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Touch Device Methods */
typedef uint32_t STDCALL (*touch_device_start_proc)(TOUCH_DEVICE *touch);
typedef uint32_t STDCALL (*touch_device_stop_proc)(TOUCH_DEVICE *touch);

typedef uint32_t STDCALL (*touch_device_peek_proc)(TOUCH_DEVICE *touch);
typedef uint32_t STDCALL (*touch_device_read_proc)(TOUCH_DEVICE *touch, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*touch_device_write_proc)(TOUCH_DEVICE *touch, void *buffer, uint32_t size, uint32_t count);
typedef uint32_t STDCALL (*touch_device_flush_proc)(TOUCH_DEVICE *touch);
typedef uint32_t STDCALL (*touch_device_update_proc)(TOUCH_DEVICE *touch);
typedef uint32_t STDCALL (*touch_device_control_proc)(TOUCH_DEVICE *touch, int request, size_t argument1, size_t *argument2);

typedef uint32_t STDCALL (*touch_device_get_properties_proc)(TOUCH_DEVICE *touch, TOUCH_PROPERTIES *properties);

struct _TOUCH_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Touch device
	// Touch Properties
	uint32_t touchid; // Unique Id of this Touch device in the Touch device table
	uint32_t touchstate; // Touch device state (eg TOUCH_STATE_ENABLED)
	touch_device_start_proc devicestart; // A Device specific DeviceStart method implementing the standard Touch device interface (Mandatory)
	touch_device_stop_proc devicestop; // A Device specific DeviceStop method implementing the standard Touch device interface (Mandatory)
	touch_device_peek_proc devicepeek; // A Device specific DevicePeek method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_read_proc deviceread; // A Device specific DeviceRead method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_flush_proc deviceflush; // A Device specific DeviceFlush method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_update_proc deviceupdate; // A Device specific DeviceUpdate method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_control_proc devicecontrol; // A Device specific DeviceControl method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing a standard Touch device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	touch_event_cb event; // Event callback function (If assigned)
	void *parameter; // Parameter for the event callback (or nil)
	TOUCH_BUFFER buffer; // Touch input buffer
	TOUCH_PROPERTIES properties; // Device properties
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t bufferoverruns;
	// Internal Properties
	TOUCH_DEVICE *prev; // Previous entry in Touch device table
	TOUCH_DEVICE *next; // Next entry in Touch device table
};

/* ============================================================================== */
/* Touch Functions */
uint32_t STDCALL touch_device_start(TOUCH_DEVICE *touch);
uint32_t STDCALL touch_device_stop(TOUCH_DEVICE *touch);

uint32_t STDCALL touch_device_peek(TOUCH_DEVICE *touch);

uint32_t STDCALL touch_device_read(TOUCH_DEVICE *touch, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
uint32_t STDCALL touch_device_write(TOUCH_DEVICE *touch, void *buffer, uint32_t size, uint32_t count);

uint32_t STDCALL touch_device_flush(TOUCH_DEVICE *touch);
uint32_t STDCALL touch_device_update(TOUCH_DEVICE *touch);

uint32_t STDCALL touch_device_control(TOUCH_DEVICE *touch, int request, size_t argument1, size_t *argument2);

uint32_t STDCALL touch_device_properties(TOUCH_DEVICE *touch, TOUCH_PROPERTIES *properties);
uint32_t STDCALL touch_device_get_properties(TOUCH_DEVICE *touch, TOUCH_PROPERTIES *properties);

TOUCH_DEVICE * STDCALL touch_device_create(void);
TOUCH_DEVICE * STDCALL touch_device_create_ex(uint32_t size);
uint32_t STDCALL touch_device_destroy(TOUCH_DEVICE *touch);

uint32_t STDCALL touch_device_register(TOUCH_DEVICE *touch);
uint32_t STDCALL touch_device_deregister(TOUCH_DEVICE *touch);

TOUCH_DEVICE * STDCALL touch_device_find(uint32_t touchid);
TOUCH_DEVICE * STDCALL touch_device_find_by_name(const char *name);
TOUCH_DEVICE * STDCALL touch_device_find_by_description(const char *description);
uint32_t STDCALL touch_device_enumerate(touch_enumerate_cb callback, void *data);

uint32_t STDCALL touch_device_notification(TOUCH_DEVICE *touch, touch_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Touch Helper Functions */
uint32_t STDCALL touch_get_count(void);
TOUCH_DEVICE * STDCALL touch_device_get_default(void);
uint32_t STDCALL touch_device_set_default(TOUCH_DEVICE *touch);

TOUCH_DEVICE * STDCALL touch_device_check(TOUCH_DEVICE *touch);

uint32_t STDCALL touch_device_type_to_string(uint32_t touchtype, char *string, uint32_t len);
uint32_t STDCALL touch_device_state_to_string(uint32_t touchstate, char *string, uint32_t len);

uint32_t STDCALL touch_device_rotation_to_string(uint32_t rotation, char *string, uint32_t len);

uint32_t STDCALL touch_device_resolve_rotation(uint32_t rotation);

uint32_t STDCALL touch_device_set_callback(TOUCH_DEVICE *touch, touch_event_cb event, void *parameter);

uint32_t STDCALL touch_insert_data(TOUCH_DEVICE *touch, TOUCH_DATA *data, BOOL signal);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_TOUCH_H