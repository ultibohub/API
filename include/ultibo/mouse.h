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
#ifndef _ULTIBO_MOUSE_H
#define _ULTIBO_MOUSE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* Mouse specific constants */
#define MOUSE_NAME_PREFIX	"Mouse" // Name prefix for Mouse Devices

/* Mouse Device Types */
#define MOUSE_TYPE_NONE	0
#define MOUSE_TYPE_USB	1
#define MOUSE_TYPE_PS2	2
#define MOUSE_TYPE_SERIAL	3

#define MOUSE_TYPE_MAX	3

/* Mouse Device States */
#define MOUSE_STATE_DETACHED	0
#define MOUSE_STATE_DETACHING	1
#define MOUSE_STATE_ATTACHING	2
#define MOUSE_STATE_ATTACHED	3

#define MOUSE_STATE_MAX	3

/* Mouse Device Flags */
#define MOUSE_FLAG_NONE	0x00000000
#define MOUSE_FLAG_NON_BLOCK	0x00000001 // If set device reads are non blocking (Also supported in Flags parameter of MouseReadEx)
#define MOUSE_FLAG_DIRECT_READ	0x00000002 // If set device writes mouse data to its local buffer which must be read using MouseDeviceRead
#define MOUSE_FLAG_SWAP_BUTTONS	0x00000004 // If set left and right mouse buttons will be swapped in mouse data
#define MOUSE_FLAG_PEEK_BUFFER	0x00000008 // Peek at the buffer to see if any data is available, don't remove it (Used only in Flags parameter of MouseReadEx)
#define MOUSE_FLAG_SWAP_XY	0x00000010 // If set swap the X and Y coordinates
#define MOUSE_FLAG_INVERT_X	0x00000020 // If set invert the X coordinate
#define MOUSE_FLAG_INVERT_Y	0x00000040 // If set invert the Y coordinate
#define MOUSE_FLAG_SWAP_MAX_XY	0x00000080 // If set swap the maximum X and Y values

/* Flags supported by MOUSE_CONTROL_GET/SET/CLEAR_FLAG */
#define MOUSE_FLAG_MASK	MOUSE_FLAG_NON_BLOCK | MOUSE_FLAG_DIRECT_READ | MOUSE_FLAG_SWAP_BUTTONS | MOUSE_FLAG_SWAP_XY | MOUSE_FLAG_INVERT_X | MOUSE_FLAG_INVERT_Y | MOUSE_FLAG_SWAP_MAX_XY

/* Mouse Device Control Codes */
#define MOUSE_CONTROL_GET_FLAG	1 // Get Flag
#define MOUSE_CONTROL_SET_FLAG	2 // Set Flag
#define MOUSE_CONTROL_CLEAR_FLAG	3 // Clear Flag
#define MOUSE_CONTROL_FLUSH_BUFFER	4 // Flush Buffer
#define MOUSE_CONTROL_GET_SAMPLE_RATE	5 // Get Sample Rate
#define MOUSE_CONTROL_SET_SAMPLE_RATE	6 // Set Sample Rate
#define MOUSE_CONTROL_GET_MAX_X	7 // Get Maximum X value (Only applies to Absolute X values)
#define MOUSE_CONTROL_GET_MAX_Y	8 // Get Maximum Y value (Only applies to Absolute Y values)
#define MOUSE_CONTROL_GET_MAX_WHEEL	9 // Get Maximum Wheel value (Only applies to Absolute Wheel values)
#define MOUSE_CONTROL_GET_MAX_BUTTONS	10 // Get Maximum Buttons mask (eg MOUSE_LEFT_BUTTON or MOUSE_RIGHT_BUTTON etc)
#define MOUSE_CONTROL_GET_ROTATION	11 // Get Rotation value (0, 90, 180, 270)(Only where supported by the driver)
#define MOUSE_CONTROL_SET_ROTATION	12 // Set Rotation value (0, 90, 180, 270)(Only where supported by the driver)

/* Mouse Buffer Size */
#define MOUSE_BUFFER_SIZE	512

/* Mouse Sampling Rate */
#define MOUSE_SAMPLE_RATE	100 // 100 samples/sec

/* Mouse Data Definitions (Values for TMouseData.Buttons) */
#define MOUSE_LEFT_BUTTON	0x0001 // The Left mouse button is pressed
#define MOUSE_RIGHT_BUTTON	0x0002 // The Right mouse button is pressed
#define MOUSE_MIDDLE_BUTTON	0x0004 // The Middle mouse button is pressed
#define MOUSE_SIDE_BUTTON	0x0008 // The Side mouse button is pressed
#define MOUSE_EXTRA_BUTTON	0x0010 // The Extra mouse button is pressed
#define MOUSE_TOUCH_BUTTON	0x0020 // The Touch screen is being touched
#define MOUSE_ABSOLUTE_X	0x0040 // The OffsetX value is absolute not relative
#define MOUSE_ABSOLUTE_Y	0x0080 // The OffsetY value is absolute not relative
#define MOUSE_ABSOLUTE_WHEEL	0x0100 // The OffsetWheel value is absolute not relative

/* Mouse Rotation */
#define MOUSE_ROTATION_0	FRAMEBUFFER_ROTATION_0 // No rotation
#define MOUSE_ROTATION_90	FRAMEBUFFER_ROTATION_90 // 90 degree rotation
#define MOUSE_ROTATION_180	FRAMEBUFFER_ROTATION_180 // 180 degree rotation
#define MOUSE_ROTATION_270	FRAMEBUFFER_ROTATION_270 // 270 degree rotation

/* ============================================================================== */
/* USB Mouse specific constants */
/* Note: The following constants are duplicated with the USBMouse unit for backwards compatibility */

/* HID Interface Subclass types (See USB HID v1.11 specification) */
#define USB_HID_SUBCLASS_NONE	0 // Section 4.2
#define USB_HID_SUBCLASS_BOOT	1 // Section 4.2

/* HID Interface Protocol types (See USB HID v1.11 specification) */
#define USB_HID_BOOT_PROTOCOL_NONE	0 // Section 4.3
#define USB_HID_BOOT_PROTOCOL_KEYBOARD	1 // Section 4.3
#define USB_HID_BOOT_PROTOCOL_MOUSE	2 // Section 4.3

/* HID Class Descriptor Types (See USB HID v1.11 specification) */
#define USB_HID_DESCRIPTOR_TYPE_HID	0x21 // Section 7.1
#define USB_HID_DESCRIPTOR_TYPE_REPORT	0x22 // Section 7.1
#define USB_HID_DESCRIPTOR_TYPE_PHYSICAL_DESCRIPTOR	0x23 // Section 7.1

/* HID Request types */
#define USB_HID_REQUEST_GET_REPORT	0x01
#define USB_HID_REQUEST_GET_IDLE	0x02
#define USB_HID_REQUEST_GET_PROTOCOL	0x03 // Section 7.2
#define USB_HID_REQUEST_SET_REPORT	0x09
#define USB_HID_REQUEST_SET_IDLE	0x0A
#define USB_HID_REQUEST_SET_PROTOCOL	0x0B // Section 7.2

/* HID Protocol types */
#define USB_HID_PROTOCOL_BOOT	0 // Section 7.2.5
#define USB_HID_PROTOCOL_REPORT	1 // Section 7.2.5

/* HID Report types */
#define USB_HID_REPORT_INPUT	1 // Section 7.2.1
#define USB_HID_REPORT_OUTPUT	2 // Section 7.2.1
#define USB_HID_REPORT_FEATURE	3 // Section 7.2.1

/* HID Report IDs */
#define USB_HID_REPORTID_NONE	0 // Section 7.2.1

/* HID Boot Protocol Button bits */
#define USB_HID_BOOT_LEFT_BUTTON	(1 << 0)
#define USB_HID_BOOT_RIGHT_BUTTON	(1 << 1)
#define USB_HID_BOOT_MIDDLE_BUTTON	(1 << 2)
#define USB_HID_BOOT_SIDE_BUTTON	(1 << 3)
#define USB_HID_BOOT_EXTRA_BUTTON	(1 << 4)

/* HID Boot Protocol Report data */
#define USB_HID_BOOT_REPORT_SIZE	8 // 3 // Appendix B of HID Device Class Definition 1.11
#define USB_HID_BOOT_DATA_SIZE	8 // Allocate more than the minimum to allow for extra data

/* ============================================================================== */
/* Mouse specific types */
/* Mouse Data */
typedef struct _MOUSE_DATA MOUSE_DATA;
struct _MOUSE_DATA
{
	uint16_t buttons; // The bitmap of current button values (eg MOUSE_LEFT_BUTTON or MOUSE_RIGHT_BUTTON)
	int16_t offsetx; // The X offset of the mouse pointer (May be negative, read as absolute if Buttons includes MOUSE_ABSOLUTE_X)
	int16_t offsety; // The Y offset of the mouse pointer (May be negative, read as absolute if Buttons includes MOUSE_ABSOLUTE_Y)
	int16_t offsetwheel; // The X offset of the mouse pointer (May be negative, read as absolute if Buttons includes MOUSE_ABSOLUTE_WHEEL)
	uint16_t maximumx; // The maximum X value of the mouse (Only applicable if Buttons includes MOUSE_ABSOLUTE_X, otherwise must be 0)
	uint16_t maximumy; // The maximum Y value of the mouse (Only applicable if Buttons includes MOUSE_ABSOLUTE_Y, otherwise must be 0)
	uint16_t maximumwheel; // The maximum Wheel value of the mouse (Only applicable if Buttons includes MOUSE_ABSOLUTE_WHEEL, otherwise must be 0)
	uint16_t reserved; // Reserved field (Round structure to 16 bytes)
};

/* Mouse Buffer */
typedef struct _MOUSE_BUFFER MOUSE_BUFFER;
struct _MOUSE_BUFFER
{
	SEMAPHORE_HANDLE wait; // Buffer ready semaphore
	uint32_t start; // Index of first buffer ready
	uint32_t count; // Number of entries ready in buffer
	MOUSE_DATA buffer[MOUSE_BUFFER_SIZE];
};

/* Mouse Properties */
typedef struct _MOUSE_PROPERTIES MOUSE_PROPERTIES;
struct _MOUSE_PROPERTIES
{
	uint32_t flags; // Device flags (eg MOUSE_FLAG_SWAP_BUTTONS)
	uint32_t rotation; // Screen Rotation (eg MOUSE_ROTATION_180)
	uint32_t maxx; // Maximum (absolute) X value for the mouse device
	uint32_t maxy; // Maximum (absolute) Y value for the mouse device
	uint32_t maxwheel; // Maximum (absolute) wheel value for the mouse device
	uint32_t maxbuttons; // Maximum buttons mask (eg MOUSE_LEFT_BUTTON or MOUSE_RIGHT_BUTTON etc)
};

/* Mouse Device */
typedef struct _MOUSE_DEVICE MOUSE_DEVICE;

/* Mouse Enumeration Callback */
typedef uint32_t STDCALL (*mouse_enumerate_cb)(MOUSE_DEVICE *mouse, void *data);
/* Mouse Notification Callback */
typedef uint32_t STDCALL (*mouse_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Mouse Device Methods */
typedef uint32_t STDCALL (*mouse_device_read_proc)(MOUSE_DEVICE *mouse, void *buffer, uint32_t size, uint32_t *count);
typedef uint32_t STDCALL (*mouse_device_update_proc)(MOUSE_DEVICE *mouse);
typedef uint32_t STDCALL (*mouse_device_control_proc)(MOUSE_DEVICE *mouse, int request, size_t argument1, size_t *argument2);

typedef uint32_t STDCALL (*mouse_device_get_properties_proc)(MOUSE_DEVICE *mouse, MOUSE_PROPERTIES *properties);

struct _MOUSE_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Mouse
	// Mouse Properties
	uint32_t mouseid; // Unique Id of this Mouse in the Mouse table
	uint32_t mousestate; // Mouse state (eg MOUSE_STATE_ATTACHED)
	uint32_t mouserate; // Mouse sample rate (Samples per second)
	mouse_device_read_proc deviceread; // A Device specific DeviceRead method implementing a standard Mouse device interface (Or nil if the default method is suitable)
	mouse_device_update_proc deviceupdate; // A Device specific DeviceUpdate method implementing a standard Mouse device interface (Or nil if the default method is suitable)
	mouse_device_control_proc devicecontrol; // A Device specific DeviceControl method implementing a standard Mouse device interface (Or nil if the default method is suitable)
	mouse_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing a standard Mouse device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; // Mouse lock
	MOUSE_BUFFER buffer; // Mouse input buffer
	MOUSE_PROPERTIES properties; // Device properties
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t bufferoverruns;
	// Internal Properties
	MOUSE_DEVICE *prev; // Previous entry in Mouse table
	MOUSE_DEVICE *next; // Next entry in Mouse table
};

/* ============================================================================== */
/* USB Mouse specific types */
/* Note: The following structure is duplicated with the USBMouse unit for backwards compatibility */

#ifndef _ULTIBO_KEYBOARD_H
/* USB HID Descriptor */
typedef struct _USB_HID_DESCRIPTOR USB_HID_DESCRIPTOR;
struct _USB_HID_DESCRIPTOR
{
	uint8_t blength;
	uint8_t bdescriptortype;
	uint16_t bcdhid;
	uint8_t bcountrycode;
	uint8_t bnumdescriptors;
	uint8_t bhiddescriptortype;
	uint16_t whiddescriptorlength;
	// Note: Up to two optional bHIDDescriptorType/wHIDDescriptorLength pairs after the Report descriptor details
} PACKED;
#endif // _ULTIBO_KEYBOARD_H

/* ============================================================================== */
/* Mouse Functions */
uint32_t STDCALL mouse_peek(void);
uint32_t STDCALL mouse_read(void *buffer, uint32_t size, uint32_t *count);
uint32_t STDCALL mouse_read_ex(void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

uint32_t STDCALL mouse_write(void *buffer, uint32_t size, uint32_t count);

uint32_t STDCALL mouse_flush(void);

uint32_t STDCALL mouse_device_read(MOUSE_DEVICE *mouse, void *buffer, uint32_t size, uint32_t *count);
uint32_t STDCALL mouse_device_update(MOUSE_DEVICE *mouse);
uint32_t STDCALL mouse_device_control(MOUSE_DEVICE *mouse, int request, size_t argument1, size_t *argument2);

uint32_t STDCALL mouse_device_get_properties(MOUSE_DEVICE *mouse, MOUSE_PROPERTIES *properties);

uint32_t STDCALL mouse_device_set_state(MOUSE_DEVICE *mouse, uint32_t state);

MOUSE_DEVICE * STDCALL mouse_device_create(void);
MOUSE_DEVICE * STDCALL mouse_device_create_ex(uint32_t size);
uint32_t STDCALL mouse_device_destroy(MOUSE_DEVICE *mouse);

uint32_t STDCALL mouse_device_register(MOUSE_DEVICE *mouse);
uint32_t STDCALL mouse_device_deregister(MOUSE_DEVICE *mouse);

MOUSE_DEVICE * STDCALL mouse_device_find(uint32_t mouseid);
MOUSE_DEVICE * STDCALL mouse_device_find_by_name(const char *name);
MOUSE_DEVICE * STDCALL mouse_device_find_by_description(const char *description);
uint32_t STDCALL mouse_device_enumerate(mouse_enumerate_cb callback, void *data);

uint32_t STDCALL mouse_device_notification(MOUSE_DEVICE *mouse, mouse_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Mouse Helper Functions */
uint32_t STDCALL mouse_get_count(void);

MOUSE_DEVICE * STDCALL mouse_device_check(MOUSE_DEVICE *mouse);

uint32_t STDCALL mouse_device_type_to_string(uint32_t mousetype, char *string, uint32_t len);
uint32_t STDCALL mouse_device_state_to_string(uint32_t mousestate, char *string, uint32_t len);

uint32_t STDCALL mouse_device_rotation_to_string(uint32_t rotation, char *string, uint32_t len);

uint32_t STDCALL mouse_device_state_to_notification(uint32_t state);

uint32_t STDCALL mouse_device_resolve_rotation(uint32_t rotation);

uint32_t STDCALL mouse_insert_data(MOUSE_DEVICE *mouse, MOUSE_DATA *data, BOOL signal);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_MOUSE_H