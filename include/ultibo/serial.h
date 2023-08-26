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
#ifndef _ULTIBO_SERIAL_H
#define _ULTIBO_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* Serial specific constants */
#define SERIAL_NAME_PREFIX	"Serial" // Name prefix for Serial Devices

#define SERIAL_LOGGING_DESCRIPTION	"Serial Logging"

#define SERIAL_RECEIVE_DEPTH_DEFAULT	SIZE_2K // Default receive buffer size in bytes
#define SERIAL_TRANSMIT_DEPTH_DEFAULT	SIZE_2K // Default transmit buffer size in bytes

#define SERIAL_PUSH_TIMEOUT	50 // Timeout (Milliseconds) for Push RX/TX (Implementation specific)

/* Serial Device Types */
#define SERIAL_TYPE_NONE	0
#define SERIAL_TYPE_UART	1
#define SERIAL_TYPE_USB	2

/* Serial Device States */
#define SERIAL_STATE_CLOSED	0
#define SERIAL_STATE_CLOSING	1
#define SERIAL_STATE_OPENING	2
#define SERIAL_STATE_OPEN	3

/* Serial Device Flags */
#define SERIAL_FLAG_NONE	0x00000000
#define SERIAL_FLAG_DATA_8BIT	0x00000001 // Device supports 8 data bits
#define SERIAL_FLAG_DATA_7BIT	0x00000002 // Device supports 7 data bits
#define SERIAL_FLAG_DATA_6BIT	0x00000004 // Device supports 6 data bits
#define SERIAL_FLAG_DATA_5BIT	0x00000008 // Device supports 5 data bits
#define SERIAL_FLAG_STOP_1BIT	0x00000010 // Device supports 1 stop bit
#define SERIAL_FLAG_STOP_2BIT	0x00000020 // Device supports 2 stop bits
#define SERIAL_FLAG_STOP_1BIT5	0x00000040 // Device supports 1.5 stop bits
#define SERIAL_FLAG_PARITY_ODD	0x00000080 // Device supports odd parity
#define SERIAL_FLAG_PARITY_EVEN	0x00000100 // Device supports even parity
#define SERIAL_FLAG_PARITY_MARK	0x00000200 // Device supports mark parity
#define SERIAL_FLAG_PARITY_SPACE	0x00000400 // Device supports space parity
#define SERIAL_FLAG_FLOW_RTS_CTS	0x00000800 // Device supports RTS/CTS flow control
#define SERIAL_FLAG_FLOW_DSR_DTR	0x00001000 // Device supports DSR/DTR flow control
#define SERIAL_FLAG_PUSH_RX	0x00002000 // Device requires pushed receive (Implementation specific)
#define SERIAL_FLAG_PUSH_TX	0x00004000 // Device requires pushed transmit (Implementation specific)

/* Serial Read Flags */
#define SERIAL_READ_NONE	0x00000000
#define SERIAL_READ_NON_BLOCK	0x00000001 // Do not block when reading, if the buffer is empty return immediately
#define SERIAL_READ_PEEK_BUFFER	0x00000002 // Return the number of bytes available in the receive buffer without reading them

/* Serial Write Flags */
#define SERIAL_WRITE_NONE	0x00000000
#define SERIAL_WRITE_NON_BLOCK	0x00000001 // Do not block when writing, if the buffer is full return immediately
#define SERIAL_WRITE_PEEK_BUFFER	0x00000002 // Return the number of bytes free in the transmit buffer without writing anything

/* Serial Wait Directions */
#define SERIAL_WAIT_NONE	0
#define SERIAL_WAIT_RECEIVE	1 // Wait for data to be available in the receive buffer
#define SERIAL_WAIT_TRANSMIT	2 // Wait for space to be available in the transmit buffer

/* Serial Flush Flags */
#define SERIAL_FLUSH_NONE	0x00000000
#define SERIAL_FLUSH_RECEIVE	0x00000001 // Flush the receive buffer
#define SERIAL_FLUSH_TRANSMIT	0x00000002 // Flush the transmit buffer

/* Serial Status Flags */
#define SERIAL_STATUS_NONE	0x00000000
#define SERIAL_STATUS_RTS	0x00000001 // RTS (Request to Send) is set (If applicable)
#define SERIAL_STATUS_CTS	0x00000002 // CTS (Clear to Send) is set (If applicable)
#define SERIAL_STATUS_DSR	0x00000004 // DSR (Data Set Ready) is set (If applicable)
#define SERIAL_STATUS_DTR	0x00000008 // DTR (Data Terminal Ready) is set (If applicable)
#define SERIAL_STATUS_RX_FULL	0x00000010 // Receive buffer is full
#define SERIAL_STATUS_RX_EMPTY	0x00000020 // Receive buffer is empty
#define SERIAL_STATUS_TX_FULL	0x00000040 // Transmit buffer is full
#define SERIAL_STATUS_TX_EMPTY	0x00000080 // Transmit buffer is empty
#define SERIAL_STATUS_BUSY	0x00000100 // Device is busy
#define SERIAL_STATUS_BREAK_ERROR	0x00000200 // Break error reported
#define SERIAL_STATUS_PARITY_ERROR	0x00000400 // Parity error reported
#define SERIAL_STATUS_FRAMING_ERROR	0x00000800 // Framing error reported
#define SERIAL_STATUS_OVERRUN_ERROR	0x00001000 // Overrun error reported
#define SERIAL_STATUS_DCD	0x00002000 // DCD (Data Carrier Detect) is set (If applicable)
#define SERIAL_STATUS_RI	0x00004000 // RI (Ring Indicator) is set (If applicable)

/* ============================================================================== */
/* Serial specific types */

/* Serial Properties */
typedef struct _SERIAL_PROPERTIES SERIAL_PROPERTIES;
struct _SERIAL_PROPERTIES
{
	uint32_t flags; // Device flags (eg SERIAL_FLAG_DATA_8BIT)
	uint32_t minrate; // Minimum supported baud rate (0 for any rate supported)
	uint32_t maxrate; // Maximum supported baud rate (0 for any rate supported)
	uint32_t baudrate; // Current baud rate setting
	uint32_t databits; // Current data bits setting
	uint32_t stopbits; // Current stop bits setting
	uint32_t parity; // Current parity setting
	uint32_t flowcontrol; // Current flow control setting
	uint32_t receivedepth; // Current receive depth setting
	uint32_t transmitdepth; // Current transmit depth setting
};

/* Serial Buffer */
typedef struct _SERIAL_BUFFER SERIAL_BUFFER;
struct _SERIAL_BUFFER
{
	EVENT_HANDLE wait; // Data ready / Buffer free event
	uint32_t start; // Index of first byte in buffer
	uint32_t count; // Number of bytes in buffer
	uint32_t size; // Size of buffer
	void *data; // Buffered data
};

/* Serial Device */
typedef struct _SERIAL_DEVICE SERIAL_DEVICE;

/* Serial Enumeration Callback */
typedef uint32_t STDCALL (*serial_enumerate_cb)(SERIAL_DEVICE *serial, void *data);
/* Serial Notification Callback */
typedef uint32_t STDCALL (*serial_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Serial Device Methods */
typedef uint32_t STDCALL (*serial_device_open_proc)(SERIAL_DEVICE *serial, uint32_t baudrate, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t flowcontrol, uint32_t receivedepth, uint32_t transmitdepth);
typedef uint32_t STDCALL (*serial_device_close_proc)(SERIAL_DEVICE *serial);

typedef uint32_t STDCALL (*serial_device_read_proc)(SERIAL_DEVICE *serial, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*serial_device_write_proc)(SERIAL_DEVICE *serial, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

typedef uint32_t STDCALL (*serial_device_wait_proc)(SERIAL_DEVICE *serial, uint32_t direction, uint32_t timeout, uint32_t *count);
typedef uint32_t STDCALL (*serial_device_flush_proc)(SERIAL_DEVICE *serial, uint32_t flags);

typedef uint32_t STDCALL (*serial_device_get_status_proc)(SERIAL_DEVICE *serial);
typedef uint32_t STDCALL (*serial_device_set_status_proc)(SERIAL_DEVICE *serial, uint32_t status);

typedef uint32_t STDCALL (*serial_device_get_properties_proc)(SERIAL_DEVICE *serial, SERIAL_PROPERTIES *properties);
typedef uint32_t STDCALL (*serial_device_set_properties_proc)(SERIAL_DEVICE *serial, SERIAL_PROPERTIES *properties);

struct _SERIAL_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Serial
	// Serial Properties
	uint32_t serialid; // Unique Id of this Serial device in the Serial device table
	uint32_t serialstate; // Serial state (eg SERIAL_STATE_OPEN)
	uint32_t serialstatus; // Serial status (eg SERIAL_STATUS_RX_FULL)(May not be real time status depending on the driver)
	serial_device_open_proc deviceopen; // A Device specific DeviceOpen method implementing the standard Serial device interface (Mandatory)
	serial_device_close_proc deviceclose; // A Device specific DeviceClose method implementing the standard Serial device interface (Mandatory)
	serial_device_read_proc deviceread; // A Device specific DeviceRead method implementing the standard Serial device interface (Mandatory)
	serial_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing the standard Serial device interface (Mandatory)
	serial_device_wait_proc devicewait; // A Device specific DeviceWait method implementing the standard Serial device interface (Or nil if the default method is suitable)
	serial_device_flush_proc deviceflush; // A Device specific DeviceFlush method implementing the standard Serial device interface (Or nil if the default method is suitable)
	serial_device_get_status_proc devicegetstatus; // A Device specific DeviceGetStatus method implementing the standard Serial device interface (Or nil if the default method is suitable)
	serial_device_set_status_proc devicesetstatus; // A Device specific DeviceSetStatus method implementing the standard Serial device interface (Optional)
	serial_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing the standard Serial device interface (Or nil if the default method is suitable)
	serial_device_set_properties_proc devicesetproperties; // A Device specific DeviceSetProperties method implementing the standard Serial device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	SERIAL_BUFFER receive; // Serial receive buffer
	SERIAL_BUFFER transmit; // Serial transmit buffer
	SERIAL_PROPERTIES properties; // Device properties
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t receiveoverruns;
	uint32_t transmitcount;
	uint32_t transmiterrors;
	uint32_t transmitoverruns;
	// Internal Properties
	SERIAL_DEVICE *prev; // Previous entry in Serial table
	SERIAL_DEVICE *next; // Next entry in Serial table
};

/* ============================================================================== */
/* Serial Functions */
uint32_t STDCALL serial_device_open(SERIAL_DEVICE *serial, uint32_t baudrate, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t flowcontrol, uint32_t receivedepth, uint32_t transmitdepth);
uint32_t STDCALL serial_device_close(SERIAL_DEVICE *serial);

uint32_t STDCALL serial_device_read(SERIAL_DEVICE *serial, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
uint32_t STDCALL serial_device_write(SERIAL_DEVICE *serial, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

uint32_t STDCALL serial_device_wait(SERIAL_DEVICE *serial, uint32_t direction, uint32_t timeout, uint32_t *count);
uint32_t STDCALL serial_device_flush(SERIAL_DEVICE *serial, uint32_t flags);

uint32_t STDCALL serial_device_status(SERIAL_DEVICE *serial);
uint32_t STDCALL serial_device_get_status(SERIAL_DEVICE *serial);
uint32_t STDCALL serial_device_set_status(SERIAL_DEVICE *serial, uint32_t status);

uint32_t STDCALL serial_device_properties(SERIAL_DEVICE *serial, SERIAL_PROPERTIES *properties);
uint32_t STDCALL serial_device_get_properties(SERIAL_DEVICE *serial, SERIAL_PROPERTIES *properties);
uint32_t STDCALL serial_device_set_properties(SERIAL_DEVICE *serial, SERIAL_PROPERTIES *properties);

SERIAL_DEVICE * STDCALL serial_device_create(void);
SERIAL_DEVICE * STDCALL serial_device_create_ex(uint32_t size);
uint32_t STDCALL serial_device_destroy(SERIAL_DEVICE *serial);

uint32_t STDCALL serial_device_register(SERIAL_DEVICE *serial);
uint32_t STDCALL serial_device_deregister(SERIAL_DEVICE *serial);

SERIAL_DEVICE * STDCALL serial_device_find(uint32_t serialid);
SERIAL_DEVICE * STDCALL serial_device_find_by_name(char *name);
SERIAL_DEVICE * STDCALL serial_device_find_by_description(char *description);
uint32_t STDCALL serial_device_enumerate(serial_enumerate_cb callback, void *data);

uint32_t STDCALL serial_device_notification(SERIAL_DEVICE *serial, serial_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Serial Helper Functions */
uint32_t STDCALL serial_get_count(void);

SERIAL_DEVICE * STDCALL serial_device_get_default(void);
uint32_t STDCALL serial_device_set_default(SERIAL_DEVICE *serial);

SERIAL_DEVICE * STDCALL serial_device_check(SERIAL_DEVICE *serial);

uint32_t STDCALL serial_type_to_string(uint32_t serialtype, char *string, uint32_t len);
uint32_t STDCALL serial_state_to_string(uint32_t serialstate, char *string, uint32_t len);

BOOL STDCALL serial_device_redirect_input(SERIAL_DEVICE *serial);
BOOL STDCALL serial_device_redirect_output(SERIAL_DEVICE *serial);

void * STDCALL serial_buffer_read_start(SERIAL_BUFFER *buffer, uint32_t *available);
BOOL STDCALL serial_buffer_read_complete(SERIAL_BUFFER *buffer, uint32_t removed);

void * STDCALL serial_buffer_write_start(SERIAL_BUFFER *buffer, uint32_t *available);
BOOL STDCALL serial_buffer_write_complete(SERIAL_BUFFER *buffer, uint32_t added);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_SERIAL_H