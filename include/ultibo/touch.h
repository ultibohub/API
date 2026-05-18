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
#ifndef _ULTIBO_TOUCH_H
#define _ULTIBO_TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/** Touch specific constants */
#define TOUCH_NAME_PREFIX	"Touch" ///< Name prefix for Touch Devices

/** Touch Device Types */
#define TOUCH_TYPE_NONE	0
#define TOUCH_TYPE_RESISTIVE	1
#define TOUCH_TYPE_CAPACITIVE	2

#define TOUCH_TYPE_MAX	2

/** Touch Device States */
#define TOUCH_STATE_DISABLED	0
#define TOUCH_STATE_ENABLED	1

#define TOUCH_STATE_MAX	1

/** Touch Device Flags */
#define TOUCH_FLAG_NONE	0x00000000
#define TOUCH_FLAG_NON_BLOCK	0x00000001 ///< If set device reads are non blocking (Also supported in Flags parameter of TouchDeviceRead)
#define TOUCH_FLAG_PEEK_BUFFER	0x00000002 ///< Peek at the buffer to see if any data is available, don't remove it (Used only in Flags parameter of TouchDeviceRead)
#define TOUCH_FLAG_MOUSE_DATA	0x00000004 ///< If set the device will write a mouse data event for each touch event
#define TOUCH_FLAG_MULTI_POINT	0x00000008 ///< If set the device supports multi point touch
#define TOUCH_FLAG_PRESSURE	0x00000010 ///< If set the device supports pressure value on touch points
#define TOUCH_FLAG_SWAP_XY	0x00000020 ///< If set swap the X and Y coordinates
#define TOUCH_FLAG_INVERT_X	0x00000040 ///< If set invert the X coordinate
#define TOUCH_FLAG_INVERT_Y	0x00000080 ///< If set invert the Y coordinate
#define TOUCH_FLAG_SWAP_MAX_XY	0x00000100 ///< If set swap the maximum X and Y values
#define TOUCH_FLAG_RELEASE_TIMER	0x00000200 ///< If set enable the touch release timer for devices that don't provide release events

/** Flags supported by TOUCH_CONTROL_GET/SET/CLEAR_FLAG */
#define TOUCH_FLAG_MASK	TOUCH_FLAG_NON_BLOCK | TOUCH_FLAG_MOUSE_DATA | TOUCH_FLAG_MULTI_POINT | TOUCH_FLAG_PRESSURE | TOUCH_FLAG_SWAP_XY | TOUCH_FLAG_INVERT_X | TOUCH_FLAG_INVERT_Y | TOUCH_FLAG_SWAP_MAX_XY | TOUCH_FLAG_RELEASE_TIMER

/** Touch Device Control Codes */
#define TOUCH_CONTROL_GET_FLAG	1 ///< Get Flag
#define TOUCH_CONTROL_SET_FLAG	2 ///< Set Flag
#define TOUCH_CONTROL_CLEAR_FLAG	3 ///< Clear Flag
#define TOUCH_CONTROL_FLUSH_BUFFER	4 ///< Flush Buffer
#define TOUCH_CONTROL_GET_WIDTH	5 ///< Get Screen Width
#define TOUCH_CONTROL_GET_HEIGHT	6 ///< Get Screen Height
#define TOUCH_CONTROL_GET_MAX_X	7 ///< Get Maximum X value (Only applies to Absolute X values)
#define TOUCH_CONTROL_GET_MAX_Y	8 ///< Get Maximum Y value (Only applies to Absolute Y values)
#define TOUCH_CONTROL_GET_MAX_Z	9 ///< Get Maximum Z value (Only applies to Absolute Z values)
#define TOUCH_CONTROL_GET_MAX_POINTS	10 ///< Get Maximum number of Touch Points
#define TOUCH_CONTROL_GET_ROTATION	11 ///< Get Rotation value (0, 90, 180, 270)(Only where supported by the driver)
#define TOUCH_CONTROL_SET_ROTATION	12 ///< Set Rotation value (0, 90, 180, 270)(Only where supported by the driver)
#define TOUCH_CONTROL_GET_CALLBACK	13 ///< Get the registered callback function for touch events
#define TOUCH_CONTROL_SET_CALLBACK	14 ///< Set the registered callback function for touch events

/** Touch Buffer Size */
#define TOUCH_BUFFER_SIZE	1024

/** Touch Data Definitions (Values for TTouchData.Info) */
#define TOUCH_FINGER	0x00000001 ///< A finger is pressed at this touch point

/** Touch Data Definitions (Values for TTouchData.PointID) */
#define TOUCH_ID_UNKNOWN	(uint16_t)-1

/** Touch Data Definitions (Values for TTouchData.PositionX) */
#define TOUCH_X_UNKNOWN	-1

/** Touch Data Definitions (Values for TTouchData.PositionY) */
#define TOUCH_Y_UNKNOWN	-1

/** Touch Data Definitions (Values for TTouchData.PositionZ) */
#define TOUCH_Z_UNKNOWN	-1

/** Touch Rotation */
#define TOUCH_ROTATION_0	FRAMEBUFFER_ROTATION_0 ///< No rotation
#define TOUCH_ROTATION_90	FRAMEBUFFER_ROTATION_90 ///< 90 degree rotation
#define TOUCH_ROTATION_180	FRAMEBUFFER_ROTATION_180 ///< 180 degree rotation
#define TOUCH_ROTATION_270	FRAMEBUFFER_ROTATION_270 ///< 270 degree rotation

/** Touch specific types */
/** Touch Data */
typedef struct _TOUCH_DATA TOUCH_DATA;
struct _TOUCH_DATA
{
	uint32_t info; ///< Bitmap of touch info values (eg TOUCH_FINGER)
	uint16_t pointid; ///< The touch point ID value for this touch (First ID is 1)
	int16_t positionx; ///< The X position of this touch point
	int16_t positiony; ///< The Y position of this touch point
	int16_t positionz; ///< The Z position of this touch point (If applicable)
	uint16_t touchwidth; ///< The Width of this touch point (If applicable)
	uint16_t touchheight; ///< The Height of this touch point (If applicable)
	void *parameter; ///< The parameter for the event callback (If applicable)
};

/** Touch Buffer */
typedef struct _TOUCH_BUFFER TOUCH_BUFFER;
struct _TOUCH_BUFFER
{
	SEMAPHORE_HANDLE wait; ///< Buffer ready semaphore
	uint32_t start; ///< Index of first buffer ready
	uint32_t count; ///< Number of entries ready in buffer
	TOUCH_DATA buffer[TOUCH_BUFFER_SIZE];
};

/** Touch Properties */
typedef struct _TOUCH_PROPERTIES TOUCH_PROPERTIES;
struct _TOUCH_PROPERTIES
{
	uint32_t flags; ///< Device flags (eg TOUCH_FLAG_MULTI_POINT)
	uint32_t width; ///< Screen Width
	uint32_t height; ///< Screen Height
	uint32_t rotation; ///< Screen Rotation (eg TOUCH_ROTATION_180)
	uint32_t maxx; ///< Maximum (absolute) X position for the touch device
	uint32_t maxy; ///< Maximum (absolute) Y position for the touch device
	uint32_t maxz; ///< Maximum (absolute) Z position for the touch device (If applicable)
	uint32_t maxwidth; ///< Maximum touch width value for the touch device (If applicable)
	uint32_t maxheight; ///< Maximum touch height value for the touch device (If applicable)
	uint32_t maxpoints; ///< Maximum number of touch points
};

/** Touch Device */
typedef struct _TOUCH_DEVICE TOUCH_DEVICE;

/** Touch Event Callback */
typedef uint32_t STDCALL (*touch_event_cb)(TOUCH_DEVICE *touch, TOUCH_DATA *data);

/** Touch Enumeration Callback */
typedef uint32_t STDCALL (*touch_enumerate_cb)(TOUCH_DEVICE *touch, void *data);
/** Touch Notification Callback */
typedef uint32_t STDCALL (*touch_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** Touch Device Methods */
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
	DEVICE device; ///< The Device entry for this Touch device
	// Touch Properties
	uint32_t touchid; ///< Unique Id of this Touch device in the Touch device table
	uint32_t touchstate; ///< Touch device state (eg TOUCH_STATE_ENABLED)
	touch_device_start_proc devicestart; ///< A Device specific DeviceStart method implementing the standard Touch device interface (Mandatory)
	touch_device_stop_proc devicestop; ///< A Device specific DeviceStop method implementing the standard Touch device interface (Mandatory)
	touch_device_peek_proc devicepeek; ///< A Device specific DevicePeek method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_read_proc deviceread; ///< A Device specific DeviceRead method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_write_proc devicewrite; ///< A Device specific DeviceWrite method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_flush_proc deviceflush; ///< A Device specific DeviceFlush method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_update_proc deviceupdate; ///< A Device specific DeviceUpdate method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_control_proc devicecontrol; ///< A Device specific DeviceControl method implementing a standard Touch device interface (Or nil if the default method is suitable)
	touch_device_get_properties_proc devicegetproperties; ///< A Device specific DeviceGetProperties method implementing a standard Touch device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; ///< Device lock
	touch_event_cb event; ///< Event callback function (If assigned)
	void *parameter; ///< Parameter for the event callback (or nil)
	TOUCH_BUFFER buffer; ///< Touch input buffer
	TOUCH_PROPERTIES properties; ///< Device properties
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t bufferoverruns;
	// Internal Properties
	TOUCH_DEVICE *prev; ///< Previous entry in Touch device table
	TOUCH_DEVICE *next; ///< Next entry in Touch device table
};

/** Touch Functions */

/**
 * @brief Start the specified Touch device ready for receiving events
 * @param Touch The Touch device to start
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_start(TOUCH_DEVICE *touch);

/**
 * @brief Stop the specified Touch device and terminate receiving events
 * @param Touch The Touch device to stop
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_stop(TOUCH_DEVICE *touch);

/**
 * @brief Peek at the buffer of the specified touch device to see if any data packets are ready
 * @param Touch The Touch device to peek at
 * @return ERROR_SUCCESS if packets are ready, ERROR_NO_MORE_ITEMS if not or another error code on failure
 */
uint32_t STDCALL touch_device_peek(TOUCH_DEVICE *touch);

/**
 * @brief Read touch data packets from the buffer of the specified touch device
 * @param Touch The Touch device to read from
 * @param Buffer Pointer to a buffer to copy the touch data packets to
 * @param Size The size of the buffer in bytes (Must be at least TTouchData or greater)
 * @param Flags The flags for the behaviour of the read (eg TOUCH_FLAG_NON_BLOCK)
 * @param Count The number of touch data packets copied to the buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_read(TOUCH_DEVICE *touch, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Write touch data packets to the buffer of the specified touch device
 * @param Touch The Touch device to write to
 * @param Buffer Pointer to a buffer to copy the touch data packets from
 * @param Size The size of the buffer in bytes (Must be at least TTouchData or greater)
 * @param Count The number of touch data packets to copy from the buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_write(TOUCH_DEVICE *touch, void *buffer, uint32_t size, uint32_t count);

/**
 * @brief Flush the contents of the buffer of the specified touch device
 * @param Touch The Touch device to flush
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_flush(TOUCH_DEVICE *touch);

/**
 * @brief Request the specified touch device to update the current configuration
 * @param Touch The Touch device to update
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Items updated can include rotation, maximum X and Y and flags (If supported)
 */
uint32_t STDCALL touch_device_update(TOUCH_DEVICE *touch);

/**
 * @brief Perform a control request on the specified touch device
 * @param Touch The Touch device to control
 * @param Request The request code for the operation (eg TOUCH_CONTROL_GET_FLAG)
 * @param Argument1 The first argument for the operation (Dependent on request code)
 * @param Argument2 The second argument for the operation (Dependent on request code)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_control(TOUCH_DEVICE *touch, int request, size_t argument1, size_t *argument2);

/**
 * @brief Get the properties for the specified Touch device
 * @param Touch The Touch device to get properties from
 * @param Properties Pointer to a TTouchProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Replaced by TouchDeviceGetProperties for consistency
 */
uint32_t STDCALL touch_device_properties(TOUCH_DEVICE *touch, TOUCH_PROPERTIES *properties);

/**
 * @brief Get the properties for the specified Touch device
 * @param Touch The Touch device to get properties from
 * @param Properties Pointer to a TTouchProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_get_properties(TOUCH_DEVICE *touch, TOUCH_PROPERTIES *properties);

/**
 * @brief Create a new Touch device entry
 * @return Pointer to new Touch device entry or nil if Touch device could not be created
 */
TOUCH_DEVICE * STDCALL touch_device_create(void);

/**
 * @brief Create a new Touch device entry
 * @param Size Size in bytes to allocate for new Touch device (Including the Touch device entry)
 * @return Pointer to new Touch device entry or nil if Touch device could not be created
 */
TOUCH_DEVICE * STDCALL touch_device_create_ex(uint32_t size);

/**
 * @brief Destroy an existing Touch device entry
 * @param Touch The Touch device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_destroy(TOUCH_DEVICE *touch);

/**
 * @brief Register a new Touch device in the Touch device table
 * @param Touch The Touch device to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_register(TOUCH_DEVICE *touch);

/**
 * @brief Deregister a Touch device from the Touch device table
 * @param Touch The Touch device to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_deregister(TOUCH_DEVICE *touch);

/**
 * @brief Find a Touch device by ID in the Touch device table
 * @param TouchId The ID number of the Touch device to find
 * @return Pointer to Touch device entry or nil if not found
 */
TOUCH_DEVICE * STDCALL touch_device_find(uint32_t touchid);

/**
 * @brief Find a Touch device by name in the device table
 * @param Name The name of the Touch device to find (eg Touch0)
 * @return Pointer to Touch device entry or nil if not found
 */
TOUCH_DEVICE * STDCALL touch_device_find_by_name(const char *name);

/**
 * @brief Find a Touch device by description in the device table
 * @param Description The description of the Touch to find (eg USB Touchscreen)
 * @return Pointer to Touch device entry or nil if not found
 */
TOUCH_DEVICE * STDCALL touch_device_find_by_description(const char *description);

/**
 * @brief Enumerate all Touch devices in the Touch device table
 * @param Callback The callback function to call for each Touch device in the table
 * @param Data A private data pointer to pass to callback for each Touch device in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_enumerate(touch_enumerate_cb callback, void *data);

/**
 * @brief Register a notification for Touch device changes
 * @param Touch The Touch device to notify changes for (Optional, pass nil for all Touch devices)
 * @param Callback The function to call when a notification event occurs
 * @param Data A private data pointer to pass to callback when a notification event occurs
 * @param Notification The events to register for notification of (eg DEVICE_NOTIFICATION_REGISTER)
 * @param Flags The flags to control the notification (eg NOTIFIER_FLAG_WORKER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_notification(TOUCH_DEVICE *touch, touch_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/** Touch Helper Functions */

/**
 * @brief Get the current Touch device count
 * @return The number of Touch devices
 */
uint32_t STDCALL touch_get_count(void);

/**
 * @brief Get the current default Touch device
 * @return Pointer to default Touch device entry
 */
TOUCH_DEVICE * STDCALL touch_device_get_default(void);

/**
 * @brief Set the current default Touch device
 * @param Touch The Touch device to set as default
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL touch_device_set_default(TOUCH_DEVICE *touch);

/**
 * @brief Check if the supplied Touch device is in the Touch device table
 * @param Touch The Touch device to check
 * @return Pointer to Touch device entry or nil if not found
 */
TOUCH_DEVICE * STDCALL touch_device_check(TOUCH_DEVICE *touch);

/**
 * @brief Return a string describing the Touch device type (eg TOUCH_TYPE_CAPACITIVE)
 */
uint32_t STDCALL touch_device_type_to_string(uint32_t touchtype, char *string, uint32_t len);

/**
 * @brief Return a string describing the Touch device state (eg TOUCH_STATE_ENABLED)
 */
uint32_t STDCALL touch_device_state_to_string(uint32_t touchstate, char *string, uint32_t len);

/**
 * @brief Return a string describing the supplied touch rotation value
 */
uint32_t STDCALL touch_device_rotation_to_string(uint32_t rotation, char *string, uint32_t len);

/**
 * @brief Resolve a value of 0, 90, 180 or 270 to a touch rotation constant (eg TOUCH_ROTATION_180)
 * @note Also accepts passing the touch rotation constant values directly
 */
uint32_t STDCALL touch_device_resolve_rotation(uint32_t rotation);

/**
 * @brief Set the event callback function for the specified touch device
 * @param Touch The touch device to set the event callback for
 * @param Event The event callback function to be called when touch data is received
 * @param Parameter A pointer to private data to be passed to the callback with each event
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note This function also clears the TOUCH_FLAG_MOUSE_DATA flag because the event
 *       callback is not compatible with receiving touch events as mouse data
 */
uint32_t STDCALL touch_device_set_callback(TOUCH_DEVICE *touch, touch_event_cb event, void *parameter);

/**
 * @brief Insert a TTouchData entry into the touch device buffer
 * @param Touch The touch device to insert data for
 * @param Data The TTouchData entry to insert
 * @param Signal If True then signal that new data is available in the buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must hold the touch device lock
 */
uint32_t STDCALL touch_insert_data(TOUCH_DEVICE *touch, TOUCH_DATA *data, BOOL signal);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_TOUCH_H