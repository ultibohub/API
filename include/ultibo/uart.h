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
#ifndef _ULTIBO_UART_H
#define _ULTIBO_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"
#include "ultibo/serial.h"

/* ============================================================================== */
/* UART specific constants */
#define UART_NAME_PREFIX	"UART" // Name prefix for UART Devices

#define UART_PUSH_TIMEOUT	SERIAL_PUSH_TIMEOUT // Timeout (Milliseconds) for Push RX/TX (Implementation specific)

/* UART Device Types */
#define UART_TYPE_NONE	0
#define UART_TYPE_8250	1 // 8250 UART and similar variants (Differences are handled by driver)
#define UART_TYPE_16550	2 // 16550 UART and similar variants (eg 16550A) (Differences are handled by driver)
#define UART_TYPE_16650	3 // 16650 UART and similar variants (eg 16C650) (Differences are handled by driver)

#define UART_TYPE_MAX	3

/* UART Device Modes */
#define UART_MODE_NONE	0
#define UART_MODE_UART	1 // The UART was opened as a UART device and all reads and writes are direct
#define UART_MODE_SERIAL	2 // The UART was opened as a Serial device so reads and writes are being buffered

#define UART_MODE_MAX	2

/* UART Device States */
#define UART_STATE_DISABLED	0
#define UART_STATE_ENABLED	1

#define UART_STATE_MAX	1

/* UART Device Flags */
#define UART_FLAG_NONE	SERIAL_FLAG_NONE
#define UART_FLAG_DATA_8BIT	SERIAL_FLAG_DATA_8BIT // Device supports 8 data bits
#define UART_FLAG_DATA_7BIT	SERIAL_FLAG_DATA_7BIT // Device supports 7 data bits
#define UART_FLAG_DATA_6BIT	SERIAL_FLAG_DATA_6BIT // Device supports 6 data bits
#define UART_FLAG_DATA_5BIT	SERIAL_FLAG_DATA_5BIT // Device supports 5 data bits
#define UART_FLAG_STOP_1BIT	SERIAL_FLAG_STOP_1BIT // Device supports 1 stop bit
#define UART_FLAG_STOP_2BIT	SERIAL_FLAG_STOP_2BIT // Device supports 2 stop bits
#define UART_FLAG_STOP_1BIT5	SERIAL_FLAG_STOP_1BIT5 // Device supports 1.5 stop bits
#define UART_FLAG_PARITY_ODD	SERIAL_FLAG_PARITY_ODD // Device supports odd parity
#define UART_FLAG_PARITY_EVEN	SERIAL_FLAG_PARITY_EVEN // Device supports even parity
#define UART_FLAG_PARITY_MARK	SERIAL_FLAG_PARITY_MARK // Device supports mark parity
#define UART_FLAG_PARITY_SPACE	SERIAL_FLAG_PARITY_SPACE // Device supports space parity
#define UART_FLAG_FLOW_RTS_CTS	SERIAL_FLAG_FLOW_RTS_CTS // Device supports RTS/CTS flow control
#define UART_FLAG_FLOW_DSR_DTR	SERIAL_FLAG_FLOW_DSR_DTR // Device supports DSR/DTR flow control
#define UART_FLAG_PUSH_RX	SERIAL_FLAG_PUSH_RX // Device requires pushed receive (Implementation specific)
#define UART_FLAG_PUSH_TX	SERIAL_FLAG_PUSH_TX // Device requires pushed transmit (Implementation specific)

/* UART Read Flags */
#define UART_READ_NONE	SERIAL_READ_NONE
#define UART_READ_NON_BLOCK	SERIAL_READ_NON_BLOCK // Do not block when receiving, if the FIFO is empty return immediately

/* UART Write Flags */
#define UART_WRITE_NONE	SERIAL_WRITE_NONE
#define UART_WRITE_NON_BLOCK	SERIAL_WRITE_NON_BLOCK // Do not block when transmitting, if the FIFO is full return immediately

/* UART Wait Directions */
#define UART_WAIT_NONE	SERIAL_WAIT_NONE
#define UART_WAIT_RECEIVE	SERIAL_WAIT_RECEIVE // Wait for data to be available in the receive FIFO
#define UART_WAIT_TRANSMIT	SERIAL_WAIT_TRANSMIT // Wait for space to be available in the transmit FIFO

/* UART Status Flags */
#define UART_STATUS_NONE	SERIAL_STATUS_NONE
#define UART_STATUS_RTS	SERIAL_STATUS_RTS
#define UART_STATUS_CTS	SERIAL_STATUS_CTS
#define UART_STATUS_DSR	SERIAL_STATUS_DSR
#define UART_STATUS_DTR	SERIAL_STATUS_DTR
#define UART_STATUS_RX_FULL	SERIAL_STATUS_RX_FULL
#define UART_STATUS_RX_EMPTY	SERIAL_STATUS_RX_EMPTY
#define UART_STATUS_TX_FULL	SERIAL_STATUS_TX_FULL
#define UART_STATUS_TX_EMPTY	SERIAL_STATUS_TX_EMPTY
#define UART_STATUS_BUSY	SERIAL_STATUS_BUSY
#define UART_STATUS_BREAK_ERROR	SERIAL_STATUS_BREAK_ERROR
#define UART_STATUS_PARITY_ERROR	SERIAL_STATUS_PARITY_ERROR
#define UART_STATUS_FRAMING_ERROR	SERIAL_STATUS_FRAMING_ERROR
#define UART_STATUS_OVERRUN_ERROR	SERIAL_STATUS_OVERRUN_ERROR
#define UART_STATUS_DCD	SERIAL_STATUS_DCD
#define UART_STATUS_RI	SERIAL_STATUS_RI

/* ============================================================================== */
/* UART specific types */

/* UART Properties */
typedef struct _UART_PROPERTIES UART_PROPERTIES;
struct _UART_PROPERTIES
{
	uint32_t flags; // Device flags (eg UART_FLAG_DATA_8BIT)
	uint32_t minrate; // Minimum supported baud rate
	uint32_t maxrate; // Maximum supported baud rate
	uint32_t baudrate; // Current baud rate setting
	uint32_t databits; // Current data bits setting
	uint32_t stopbits; // Current stop bits setting
	uint32_t parity; // Current parity setting
	uint32_t flowcontrol; // Current flow control setting
};

/* UART Device */
typedef struct _UART_DEVICE UART_DEVICE;

/* UART Enumeration Callback */
typedef uint32_t STDCALL (*uart_enumerate_cb)(UART_DEVICE *uart, void *data);
/* UART Notification Callback */
typedef uint32_t STDCALL (*uart_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* UART Device Methods */
typedef uint32_t STDCALL (*uart_device_open_proc)(UART_DEVICE *uart, uint32_t baudrate, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t flowcontrol);
typedef uint32_t STDCALL (*uart_device_close_proc)(UART_DEVICE *uart);

typedef uint32_t STDCALL (*uart_device_read_proc)(UART_DEVICE *uart, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*uart_device_write_proc)(UART_DEVICE *uart, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

typedef uint32_t STDCALL (*uart_device_wait_proc)(UART_DEVICE *uart, uint32_t direction, uint32_t timeout);

typedef uint32_t STDCALL (*uart_device_get_status_proc)(UART_DEVICE *uart);
typedef uint32_t STDCALL (*uart_device_set_status_proc)(UART_DEVICE *uart, uint32_t status);

typedef uint32_t STDCALL (*uart_device_get_properties_proc)(UART_DEVICE *uart, UART_PROPERTIES *properties);
typedef uint32_t STDCALL (*uart_device_set_properties_proc)(UART_DEVICE *uart, UART_PROPERTIES *properties);

struct _UART_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this UART
	// UART Properties
	uint32_t uartid; // Unique Id of this UART in the UART table
	uint32_t uartmode; // UART mode (eg UART_MODE_SERIAL)
	uint32_t uartstate; // UART state (eg UART_STATE_ENABLED)
	uint32_t uartstatus; // UART status (eg UART_STATUS_RX_FULL)(May not be real time status depending on the driver)
	uart_device_open_proc deviceopen; // A Device specific DeviceOpen method implementing the standard UART device interface (Mandatory)
	uart_device_close_proc deviceclose; // A Device specific DeviceClose method implementing the standard UART device interface (Mandatory)
	uart_device_read_proc deviceread; // A Device specific DeviceRead method implementing the standard UART device interface (Mandatory)
	uart_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing the standard UART device interface (Mandatory)
	uart_device_wait_proc devicewait; // A Device specific DeviceWait method implementing the standard UART device interface (Or nil if the default method is suitable)
	uart_device_get_status_proc devicegetstatus; // A Device specific DeviceGetStatus method implementing the standard UART device interface (Or nil if the default method is suitable)
	uart_device_set_status_proc devicesetstatus; // A Device specific DeviceSetStatus method implementing the standard UART device interface (Optional)
	uart_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing the standard UART device interface (Or nil if the default method is suitable)
	uart_device_set_properties_proc devicesetproperties; // A Device specific DeviceSetProperties method implementing the standard UART device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	EVENT_HANDLE receivewait; // Read wait event
	EVENT_HANDLE transmitwait; // Write wait event
	UART_PROPERTIES properties; // Device properties
	// Serial Properties
	SERIAL_DEVICE *serial; // The Serial device represented by this UART
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t transmitcount;
	uint32_t transmiterrors;
	// Internal Properties
	UART_DEVICE *prev; // Previous entry in UART table
	UART_DEVICE *next; // Next entry in UART table
};

/* ============================================================================== */
/* UART Functions */
uint32_t STDCALL uart_device_open(UART_DEVICE *uart, uint32_t baudrate, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t flowcontrol);
uint32_t STDCALL uart_device_close(UART_DEVICE *uart);

uint32_t STDCALL uart_device_read(UART_DEVICE *uart, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
uint32_t STDCALL uart_device_write(UART_DEVICE *uart, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

uint32_t STDCALL uart_device_wait(UART_DEVICE *uart, uint32_t direction, uint32_t timeout);

uint32_t STDCALL uart_device_status(UART_DEVICE *uart);
uint32_t STDCALL uart_device_get_status(UART_DEVICE *uart);
uint32_t STDCALL uart_device_set_status(UART_DEVICE *uart, uint32_t status);

uint32_t STDCALL uart_device_properties(UART_DEVICE *uart, UART_PROPERTIES *properties);
uint32_t STDCALL uart_device_get_properties(UART_DEVICE *uart, UART_PROPERTIES *properties);
uint32_t STDCALL uart_device_set_properties(UART_DEVICE *uart, UART_PROPERTIES *properties);

UART_DEVICE * STDCALL uart_device_create(void);
UART_DEVICE * STDCALL uart_device_create_ex(uint32_t size);
uint32_t STDCALL uart_device_destroy(UART_DEVICE *uart);

uint32_t STDCALL uart_device_register(UART_DEVICE *uart);
uint32_t STDCALL uart_device_deregister(UART_DEVICE *uart);

UART_DEVICE * STDCALL uart_device_find(uint32_t uartid);
UART_DEVICE * STDCALL uart_device_find_by_name(const char *name);
UART_DEVICE * STDCALL uart_device_find_by_description(const char *description);
uint32_t STDCALL uart_device_enumerate(uart_enumerate_cb callback, void *data);

uint32_t STDCALL uart_device_notification(UART_DEVICE *uart, uart_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* UART Helper Functions */
uint32_t STDCALL uart_get_count(void);
UART_DEVICE * STDCALL uart_device_get_default(void);
uint32_t STDCALL uart_device_set_default(UART_DEVICE *uart);

UART_DEVICE * STDCALL uart_device_check(UART_DEVICE *uart);

uint32_t STDCALL uart_type_to_string(uint32_t uarttype, char *string, uint32_t len);
uint32_t STDCALL uart_mode_to_string(uint32_t uartmode, char *string, uint32_t len);
uint32_t STDCALL uart_state_to_string(uint32_t uartstate, char *string, uint32_t len);

/* ============================================================================== */
/* UART Serial Helper Functions */
uint32_t STDCALL uart_serial_device_receive(UART_DEVICE *uart);
uint32_t STDCALL uart_serial_device_transmit(UART_DEVICE *uart);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_UART_H