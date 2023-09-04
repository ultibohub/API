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
#ifndef _ULTIBO_JOYSTICK_H
#define _ULTIBO_JOYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* Joystick specific constants */
#define JOYSTICK_NAME_PREFIX	"Joystick" // Name prefix for Joystick Devices

/* Joystick Device Types */
#define JOYSTICK_TYPE_NONE	0
#define JOYSTICK_TYPE_JOYSTICK	1
#define JOYSTICK_TYPE_GAMEPAD	2

#define JOYSTICK_TYPE_MAX	2

/* Joystick Device States */
#define JOYSTICK_STATE_DISABLED	0
#define JOYSTICK_STATE_ENABLED	1

#define JOYSTICK_STATE_MAX	1

/* Joystick Device Flags */
#define JOYSTICK_FLAG_NONE	0x00000000
#define JOYSTICK_FLAG_NON_BLOCK	0x00000001 // If set device reads are non blocking (Also supported in Flags parameter of JoystickDeviceRead)
#define JOYSTICK_FLAG_PEEK_BUFFER	0x00000002 // Peek at the buffer to see if any data is available, don't remove it (Used only in Flags parameter of JoystickDeviceRead)
#define JOYSTICK_FLAG_LED	0x00000004 // If set the device contains one or more LEDs
#define JOYSTICK_FLAG_RGBLED	0x00000008 // If set the device contains one or more RGB LEDs
#define JOYSTICK_FLAG_RUMBLE	0x00000010 // If set the device has rumble or force feedback
#define JOYSTICK_FLAG_GYROSCOPE	0x00000020 // If set the device contains a gyroscope
#define JOYSTICK_FLAG_TOUCHPAD	0x00000040 // If set the device contains a touchpad

/* Flags supported by JOYSTICK_CONTROL_GET/SET/CLEAR_FLAG */
#define JOYSTICK_FLAG_MASK	JOYSTICK_FLAG_NON_BLOCK | JOYSTICK_FLAG_LED | JOYSTICK_FLAG_RGBLED | JOYSTICK_FLAG_RUMBLE | JOYSTICK_FLAG_GYROSCOPE | JOYSTICK_FLAG_TOUCHPAD

/* Joystick Device Control Codes */
#define JOYSTICK_CONTROL_GET_FLAG	1 // Get Flag
#define JOYSTICK_CONTROL_SET_FLAG	2 // Set Flag
#define JOYSTICK_CONTROL_CLEAR_FLAG	3 // Clear Flag
#define JOYSTICK_CONTROL_FLUSH_BUFFER	4 // Flush Buffer
#define JOYSTICK_CONTROL_GET_HAT	5 // Get the name (identifier) associated with a Hat
#define JOYSTICK_CONTROL_SET_HAT	6 // Set the name (identifier) associated with a Hat
#define JOYSTICK_CONTROL_GET_AXIS	7 // Get the name (identifier) associated with an Axis
#define JOYSTICK_CONTROL_SET_AXIS	8 // Set the name (identifier) associated with an Axis
#define JOYSTICK_CONTROL_GET_BUTTON	9 // Get the name (identifier) associated with a Button
#define JOYSTICK_CONTROL_SET_BUTTON	10 // Set the name (identifier) associated with a Button
#define JOYSTICK_CONTROL_GET_CALLBACK	11 // Get the registered callback function for joystick events
#define JOYSTICK_CONTROL_SET_CALLBACK	12 // Set the registered callback function for joystick events

/* Joystick Buffer Size */
#define JOYSTICK_BUFFER_SIZE	2048

/* Joystick Axis, Hat and Button Maximum */
#define JOYSTICK_MAX_AXIS	16
#define JOYSTICK_MAX_HAT	4
#define JOYSTICK_MAX_BUTTON	32

/* Joystick Default Minimum and Maximum */
#define JOYSTICK_DEFAULT_MINIMUM	0
#define JOYSTICK_DEFAULT_MAXIMUM	255

/* Joystick and Gamepad Axis Names (Includes Buttons, Sliders, Wheels etc that report an analog value) */
#define JOYSTICK_AXIS_NONE	0
#define JOYSTICK_AXIS_1	1
#define JOYSTICK_AXIS_2	2
#define JOYSTICK_AXIS_3	3
#define JOYSTICK_AXIS_4	4
#define JOYSTICK_AXIS_5	5
#define JOYSTICK_AXIS_6	6
#define JOYSTICK_AXIS_7	7
#define JOYSTICK_AXIS_8	8
#define JOYSTICK_AXIS_9	9
#define JOYSTICK_AXIS_10	10
#define JOYSTICK_AXIS_11	11
#define JOYSTICK_AXIS_12	12
#define JOYSTICK_AXIS_13	13
#define JOYSTICK_AXIS_14	14
#define JOYSTICK_AXIS_15	15
#define JOYSTICK_AXIS_16	16

#define JOYSTICK_AXIS_X	17 // X
#define JOYSTICK_AXIS_Y	18 // Y
#define JOYSTICK_AXIS_Z	19 // Z
#define JOYSTICK_ROTATION_X	20 // Rotation X
#define JOYSTICK_ROTATION_Y	21 // Rotation Y
#define JOYSTICK_ROTATION_Z	22 // Rotation Z
#define JOYSTICK_SLIDER	23 // Slider

#define GAMEPAD_AXIS_LEFT_X	24 // Left X
#define GAMEPAD_AXIS_LEFT_Y	25 // Left Y
#define GAMEPAD_AXIS_X	GAMEPAD_AXIS_LEFT_X
#define GAMEPAD_AXIS_Y	GAMEPAD_AXIS_LEFT_Y
#define GAMEPAD_AXIS_RIGHT_X	26 // Right X
#define GAMEPAD_AXIS_RIGHT_Y	27 // Right Y
#define GAMEPAD_CONTROL_LT	28 // Left Trigger analog button
#define GAMEPAD_CONTROL_L2	GAMEPAD_CONTROL_LT
#define GAMEPAD_CONTROL_RT	29 // Right Trigger analog button
#define GAMEPAD_CONTROL_R2	GAMEPAD_CONTROL_RT
#define GAMEPAD_CONTROL_UP	30 // Up analog button
#define GAMEPAD_CONTROL_RIGHT	31 // Right analog button
#define GAMEPAD_CONTROL_DOWN	32 // Down analog button
#define GAMEPAD_CONTROL_LEFT	33 // Left analog button
#define GAMEPAD_CONTROL_L1	34 // L1 analog button
#define GAMEPAD_CONTROL_R1	35 // R1 analog button
#define GAMEPAD_CONTROL_TRIANGLE	36 // Triangle analog button
#define GAMEPAD_CONTROL_CIRCLE	37 // Circle analog button
#define GAMEPAD_CONTROL_CROSS	38 // Cross analog button
#define GAMEPAD_CONTROL_SQUARE	39 // Square analog button

#define JOYSTICK_AXIS_MAX	39

/* Joystick and Gamepad Hat Names */
#define JOYSTICK_HAT_NONE	0
#define JOYSTICK_HAT_1	1
#define JOYSTICK_HAT_2	2
#define JOYSTICK_HAT_3	3
#define JOYSTICK_HAT_4	4

#define JOYSTICK_HAT_POV	5 // Point of View (POV)

#define JOYSTICK_HAT_MAX	5

/* Joystick and Gamepad Button Names */
#define JOYSTICK_BUTTON_NONE	0
#define JOYSTICK_BUTTON_1	1
#define JOYSTICK_BUTTON_2	2
#define JOYSTICK_BUTTON_3	3
#define JOYSTICK_BUTTON_4	4
#define JOYSTICK_BUTTON_5	5
#define JOYSTICK_BUTTON_6	6
#define JOYSTICK_BUTTON_7	7
#define JOYSTICK_BUTTON_8	8
#define JOYSTICK_BUTTON_9	9
#define JOYSTICK_BUTTON_10	10
#define JOYSTICK_BUTTON_11	11
#define JOYSTICK_BUTTON_12	12
#define JOYSTICK_BUTTON_13	13
#define JOYSTICK_BUTTON_14	14
#define JOYSTICK_BUTTON_15	15
#define JOYSTICK_BUTTON_16	16
#define JOYSTICK_BUTTON_17	17
#define JOYSTICK_BUTTON_18	18
#define JOYSTICK_BUTTON_19	19
#define JOYSTICK_BUTTON_20	20
#define JOYSTICK_BUTTON_21	21
#define JOYSTICK_BUTTON_22	22
#define JOYSTICK_BUTTON_23	23
#define JOYSTICK_BUTTON_24	24
#define JOYSTICK_BUTTON_25	25
#define JOYSTICK_BUTTON_26	26
#define JOYSTICK_BUTTON_27	27
#define JOYSTICK_BUTTON_28	28
#define JOYSTICK_BUTTON_29	29
#define JOYSTICK_BUTTON_30	30
#define JOYSTICK_BUTTON_31	31
#define JOYSTICK_BUTTON_32	32

#define GAMEPAD_BUTTON_HOME	33 // Home or special function button
#define GAMEPAD_BUTTON_PS	GAMEPAD_BUTTON_HOME // Playstation button
#define GAMEPAD_BUTTON_XBOX	GAMEPAD_BUTTON_HOME // XBox button
#define GAMEPAD_BUTTON_GUIDE	GAMEPAD_BUTTON_HOME // Guide button
#define GAMEPAD_BUTTON_LT	34 // Left Trigger button
#define GAMEPAD_BUTTON_L2	GAMEPAD_BUTTON_LT
#define GAMEPAD_BUTTON_LZ	GAMEPAD_BUTTON_LT
#define GAMEPAD_BUTTON_RT	35 // Right Trigger button
#define GAMEPAD_BUTTON_R2	GAMEPAD_BUTTON_RT
#define GAMEPAD_BUTTON_RZ	GAMEPAD_BUTTON_RT
#define GAMEPAD_BUTTON_LB	36 // Left Bumper button
#define GAMEPAD_BUTTON_L1	GAMEPAD_BUTTON_LB
#define GAMEPAD_BUTTON_L	GAMEPAD_BUTTON_LB
#define GAMEPAD_BUTTON_RB	37 // Right Bumper button
#define GAMEPAD_BUTTON_R1	GAMEPAD_BUTTON_RB
#define GAMEPAD_BUTTON_R	GAMEPAD_BUTTON_RB
#define GAMEPAD_BUTTON_Y	38 // Y button
#define GAMEPAD_BUTTON_TRIANGLE	GAMEPAD_BUTTON_Y // Triangle button
#define GAMEPAD_BUTTON_B	39 // B button
#define GAMEPAD_BUTTON_CIRCLE	GAMEPAD_BUTTON_B // Circle button
#define GAMEPAD_BUTTON_A	40 // A button
#define GAMEPAD_BUTTON_CROSS	GAMEPAD_BUTTON_A // Cross button
#define GAMEPAD_BUTTON_X	41 // X button
#define GAMEPAD_BUTTON_SQUARE	GAMEPAD_BUTTON_X // Square button
#define GAMEPAD_BUTTON_SELECT	42 // Select button
#define GAMEPAD_BUTTON_BACK	GAMEPAD_BUTTON_SELECT // Back button
#define GAMEPAD_BUTTON_SHARE	GAMEPAD_BUTTON_SELECT // Share button
#define GAMEPAD_BUTTON_CAPTURE	GAMEPAD_BUTTON_SELECT // Capture button
#define GAMEPAD_BUTTON_L3	43 // Left Stick or Left Axis button
#define GAMEPAD_BUTTON_SL	GAMEPAD_BUTTON_L3
#define GAMEPAD_BUTTON_R3	44 // Right Stick or Right Axis button
#define GAMEPAD_BUTTON_SR	GAMEPAD_BUTTON_R3
#define GAMEPAD_BUTTON_START	45 // Start button
#define GAMEPAD_BUTTON_OPTIONS	GAMEPAD_BUTTON_START
#define GAMEPAD_BUTTON_UP	46 // Up button
#define GAMEPAD_BUTTON_RIGHT	47 // Right button
#define GAMEPAD_BUTTON_DOWN	48 // Down button
#define GAMEPAD_BUTTON_LEFT	49 // Left button
#define GAMEPAD_BUTTON_PLUS	50 // Plus button
#define GAMEPAD_BUTTON_MINUS	51 // Minus button
#define GAMEPAD_BUTTON_TOUCHPAD	52 // Touchpad button

#define JOYSTICK_BUTTON_MAX	52

/* ============================================================================== */
/* Joystick specific types */
/* Joystick Data */
typedef struct _JOYSTICK_DATA JOYSTICK_DATA;
struct _JOYSTICK_DATA 
{
	int32_t axiscount; // The number of Axes reported by this device
	int16_t axes[JOYSTICK_MAX_AXIS]; // The currently reported value of each Axis
	int32_t hatcount; // The number of Hats reported by this device
	int16_t hats[JOYSTICK_MAX_HAT]; // The currently reported value of each Hat
	int32_t buttoncount; // The number of Buttons reported by this device
	uint32_t buttons; // The currently reported state of each Button
	void *parameter; // The parameter for the event callback (If applicable)
};


/* Joystick Buffer */
typedef struct _JOYSTICK_BUFFER JOYSTICK_BUFFER;
struct _JOYSTICK_BUFFER 
{
	SEMAPHORE_HANDLE wait; // Buffer ready semaphore
	uint32_t start; // Index of first buffer ready
	uint32_t count; // Number of entries ready in buffer
	JOYSTICK_DATA buffer[JOYSTICK_BUFFER_SIZE];
};


/* Joystick Properties */
typedef struct _JOYSTICK_EXTENT JOYSTICK_EXTENT;
struct _JOYSTICK_EXTENT
{
	int32_t minimum; // The minimum value for this extent
	int32_t maximum; // The maximum value for this extent
};


typedef struct _JOYSTICK_AXIS JOYSTICK_AXIS;
struct _JOYSTICK_AXIS
{
	uint32_t name; // The associated name (identifier) for this Axis
	JOYSTICK_EXTENT logical; // The minimum and maximum logical values for this Axis
	JOYSTICK_EXTENT physical; // The minimum and maximum physical values for this Axis
	double_t multiplier; // The conversion multiplier for this Axis from logical to physical units
	double_t resolution; // The unit resolution for this Axis in counts per physical unit
};


typedef struct _JOYSTICK_HAT JOYSTICK_HAT;
struct _JOYSTICK_HAT
{
	uint32_t name; // The associated name (identifier) for this Hat
	JOYSTICK_EXTENT logical; // The minimum and maximum logical values for this Hat
	JOYSTICK_EXTENT physical; // The minimum and maximum physical values for this Hat
	double_t multiplier; // The conversion multiplier for this Hat from logical to physical units
	double_t resolution; // The unit resolution for this Hat in counts per physical unit
};


typedef struct _JOYSTICK_PROPERTIES JOYSTICK_PROPERTIES;
struct _JOYSTICK_PROPERTIES 
{
	uint32_t flags; // Device flags (eg JOYSTICK_FLAG_LED)
	uint32_t axiscount; // The number of Axes reported by this device
	JOYSTICK_AXIS axes[JOYSTICK_MAX_AXIS]; // The current properties of each Axis
	uint32_t hatcount; // The number of Hats reported by this device
	JOYSTICK_HAT hats[JOYSTICK_MAX_HAT]; // The current properties of each Hat
	uint32_t buttoncount; // The number of Buttons reported by this device
	uint32_t buttons[JOYSTICK_MAX_BUTTON]; // The current name (identifier) of each Button
};


/* Joystick Device */
typedef struct _JOYSTICK_DEVICE JOYSTICK_DEVICE;

/* Joystick Event Callback */
typedef uint32_t STDCALL (*joystick_event_cb)(JOYSTICK_DEVICE *joystick, JOYSTICK_DATA *data);

/* Joystick Enumeration Callback */
typedef uint32_t STDCALL (*joystick_enumerate_cb)(JOYSTICK_DEVICE *joystick, void *data);
/* Joystick Notification Callback */
typedef uint32_t STDCALL (*joystick_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Joystick Device Methods */
typedef uint32_t STDCALL (*joystick_device_start_proc)(JOYSTICK_DEVICE *joystick);
typedef uint32_t STDCALL (*joystick_device_stop_proc)(JOYSTICK_DEVICE *joystick);

typedef uint32_t STDCALL (*joystick_device_peek_proc)(JOYSTICK_DEVICE *joystick);
typedef uint32_t STDCALL (*joystick_device_read_proc)(JOYSTICK_DEVICE *joystick, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*joystick_device_write_proc)(JOYSTICK_DEVICE *joystick, void *buffer, uint32_t size, uint32_t count);
typedef uint32_t STDCALL (*joystick_device_flush_proc)(JOYSTICK_DEVICE *joystick);
typedef uint32_t STDCALL (*joystick_device_update_proc)(JOYSTICK_DEVICE *joystick);
typedef uint32_t STDCALL (*joystick_device_control_proc)(JOYSTICK_DEVICE *joystick, int request, size_t argument1, size_t *argument2);

typedef uint32_t STDCALL (*joystick_device_get_properties_proc)(JOYSTICK_DEVICE *joystick, JOYSTICK_PROPERTIES *properties);

struct _JOYSTICK_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Joystick device
	// Joystick Properties
	uint32_t joystickid; // Unique Id of this Joystick device in the Joystick device table
	uint32_t joystickstate; // Joystick device state (eg JOYSTICK_STATE_ENABLED)
	joystick_device_start_proc devicestart; // A Device specific DeviceStart method implementing the standard Joystick device interface (Mandatory)
	joystick_device_stop_proc devicestop; // A Device specific DeviceStop method implementing the standard Joystick device interface (Mandatory)
	joystick_device_peek_proc devicepeek; // A Device specific DevicePeek method implementing a standard Joystick device interface (Or nil if the default method is suitable)
	joystick_device_read_proc deviceread; // A Device specific DeviceRead method implementing a standard Joystick device interface (Or nil if the default method is suitable)
	joystick_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing a standard Joystick device interface (Or nil if the default method is suitable)
	joystick_device_flush_proc deviceflush; // A Device specific DeviceFlush method implementing a standard Joystick device interface (Or nil if the default method is suitable)
	joystick_device_update_proc deviceupdate; // A Device specific DeviceUpdate method implementing a standard Joystick device interface (Or nil if the default method is suitable)
	joystick_device_control_proc devicecontrol; // A Device specific DeviceControl method implementing a standard Joystick device interface (Or nil if the default method is suitable)
	joystick_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing a standard Joystick device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	joystick_event_cb event; // Event callback function (If assigned)
	void *parameter; // Parameter for the event callback (or nil)
	JOYSTICK_BUFFER buffer; // Joystick input buffer
	JOYSTICK_PROPERTIES properties; // Device properties
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t bufferoverruns;
	// Internal Properties
	JOYSTICK_DEVICE *prev; // Previous entry in Joystick device table
	JOYSTICK_DEVICE *next; // Next entry in Joystick device table
};


/* ============================================================================== */
/* Joystick Functions */
uint32_t STDCALL joystick_device_start(JOYSTICK_DEVICE *joystick);
uint32_t STDCALL joystick_device_stop(JOYSTICK_DEVICE *joystick);

uint32_t STDCALL joystick_device_peek(JOYSTICK_DEVICE *joystick);

uint32_t STDCALL joystick_device_read(JOYSTICK_DEVICE *joystick, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
uint32_t STDCALL joystick_device_write(JOYSTICK_DEVICE *joystick, void *buffer, uint32_t size, uint32_t count);

uint32_t STDCALL joystick_device_flush(JOYSTICK_DEVICE *joystick);
uint32_t STDCALL joystick_device_update(JOYSTICK_DEVICE *joystick);

uint32_t STDCALL joystick_device_control(JOYSTICK_DEVICE *joystick, int request, size_t argument1, size_t *argument2);

uint32_t STDCALL joystick_device_get_properties(JOYSTICK_DEVICE *joystick, JOYSTICK_PROPERTIES *properties);

uint32_t STDCALL joystick_device_set_state(JOYSTICK_DEVICE *joystick, uint32_t state);

JOYSTICK_DEVICE * STDCALL joystick_device_create(void);
JOYSTICK_DEVICE * STDCALL joystick_device_create_ex(uint32_t size);
uint32_t STDCALL joystick_device_destroy(JOYSTICK_DEVICE *joystick);

uint32_t STDCALL joystick_device_register(JOYSTICK_DEVICE *joystick);
uint32_t STDCALL joystick_device_deregister(JOYSTICK_DEVICE *joystick);

JOYSTICK_DEVICE * STDCALL joystick_device_find(uint32_t joystickid);
JOYSTICK_DEVICE * STDCALL joystick_device_find_by_name(char *name);
JOYSTICK_DEVICE * STDCALL joystick_device_find_by_description(char *description);
uint32_t STDCALL joystick_device_enumerate(joystick_enumerate_cb callback, void *data);

uint32_t STDCALL joystick_device_notification(JOYSTICK_DEVICE *joystick, joystick_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Joystick Helper Functions */
uint32_t STDCALL joystick_get_count(void);
JOYSTICK_DEVICE * STDCALL joystick_device_get_default(void);
uint32_t STDCALL joystick_device_set_default(JOYSTICK_DEVICE *joystick);

JOYSTICK_DEVICE * STDCALL joystick_device_check(JOYSTICK_DEVICE *joystick);

uint32_t STDCALL joystick_device_axis_to_string(uint32_t name, char *string, uint32_t len);
uint32_t STDCALL joystick_device_hat_to_string(uint32_t name, char *string, uint32_t len);
uint32_t STDCALL joystick_device_button_to_string(uint32_t name, char *string, uint32_t len);

uint32_t STDCALL joystick_device_type_to_string(uint32_t joysticktype, char *string, uint32_t len);
uint32_t STDCALL joystick_device_state_to_string(uint32_t joystickstate, char *string, uint32_t len);

uint32_t STDCALL joystick_device_state_to_notification(uint32_t state);

uint32_t STDCALL joystick_device_get_axis(JOYSTICK_DEVICE *joystick, uint32_t index);
uint32_t STDCALL joystick_device_set_axis(JOYSTICK_DEVICE *joystick, uint32_t index, uint32_t name);

uint32_t STDCALL joystick_device_get_hat(JOYSTICK_DEVICE *joystick, uint32_t index);
uint32_t STDCALL joystick_device_set_hat(JOYSTICK_DEVICE *joystick, uint32_t index, uint32_t name);

uint32_t STDCALL joystick_device_get_button(JOYSTICK_DEVICE *joystick, uint32_t index);
uint32_t STDCALL joystick_device_set_button(JOYSTICK_DEVICE *joystick, uint32_t index, uint32_t name);

uint32_t STDCALL joystick_device_set_callback(JOYSTICK_DEVICE *joystick, joystick_event_cb event, void *parameter);

uint32_t STDCALL joystick_insert_data(JOYSTICK_DEVICE *joystick, JOYSTICK_DATA *data, BOOL signal);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_JOYSTICK_H