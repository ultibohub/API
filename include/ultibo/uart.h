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
#ifndef _ULTIBO_UART_H
#define _ULTIBO_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"
#include "ultibo/serial.h"

/** UART specific constants */
#define UART_NAME_PREFIX	"UART" ///< Name prefix for UART Devices

#define UART_PUSH_TIMEOUT	SERIAL_PUSH_TIMEOUT ///< Timeout (Milliseconds) for Push RX/TX (Implementation specific)

/** UART Device Types */
#define UART_TYPE_NONE	0
#define UART_TYPE_8250	1 ///< 8250 UART and similar variants (Differences are handled by driver)
#define UART_TYPE_16550	2 ///< 16550 UART and similar variants (eg 16550A) (Differences are handled by driver)
#define UART_TYPE_16650	3 ///< 16650 UART and similar variants (eg 16C650) (Differences are handled by driver)

#define UART_TYPE_MAX	3

/** UART Device Modes */
#define UART_MODE_NONE	0
#define UART_MODE_UART	1 ///< The UART was opened as a UART device and all reads and writes are direct
#define UART_MODE_SERIAL	2 ///< The UART was opened as a Serial device so reads and writes are being buffered

#define UART_MODE_MAX	2

/** UART Device States */
#define UART_STATE_DISABLED	0
#define UART_STATE_ENABLED	1

#define UART_STATE_MAX	1

/** UART Device Flags */
#define UART_FLAG_NONE	SERIAL_FLAG_NONE
#define UART_FLAG_DATA_8BIT	SERIAL_FLAG_DATA_8BIT ///< Device supports 8 data bits
#define UART_FLAG_DATA_7BIT	SERIAL_FLAG_DATA_7BIT ///< Device supports 7 data bits
#define UART_FLAG_DATA_6BIT	SERIAL_FLAG_DATA_6BIT ///< Device supports 6 data bits
#define UART_FLAG_DATA_5BIT	SERIAL_FLAG_DATA_5BIT ///< Device supports 5 data bits
#define UART_FLAG_STOP_1BIT	SERIAL_FLAG_STOP_1BIT ///< Device supports 1 stop bit
#define UART_FLAG_STOP_2BIT	SERIAL_FLAG_STOP_2BIT ///< Device supports 2 stop bits
#define UART_FLAG_STOP_1BIT5	SERIAL_FLAG_STOP_1BIT5 ///< Device supports 1.5 stop bits
#define UART_FLAG_PARITY_ODD	SERIAL_FLAG_PARITY_ODD ///< Device supports odd parity
#define UART_FLAG_PARITY_EVEN	SERIAL_FLAG_PARITY_EVEN ///< Device supports even parity
#define UART_FLAG_PARITY_MARK	SERIAL_FLAG_PARITY_MARK ///< Device supports mark parity
#define UART_FLAG_PARITY_SPACE	SERIAL_FLAG_PARITY_SPACE ///< Device supports space parity
#define UART_FLAG_FLOW_RTS_CTS	SERIAL_FLAG_FLOW_RTS_CTS ///< Device supports RTS/CTS flow control
#define UART_FLAG_FLOW_DSR_DTR	SERIAL_FLAG_FLOW_DSR_DTR ///< Device supports DSR/DTR flow control
#define UART_FLAG_PUSH_RX	SERIAL_FLAG_PUSH_RX ///< Device requires pushed receive (Implementation specific)
#define UART_FLAG_PUSH_TX	SERIAL_FLAG_PUSH_TX ///< Device requires pushed transmit (Implementation specific)

/** UART Read Flags */
#define UART_READ_NONE	SERIAL_READ_NONE
#define UART_READ_NON_BLOCK	SERIAL_READ_NON_BLOCK ///< Do not block when receiving, if the FIFO is empty return immediately

/** UART Write Flags */
#define UART_WRITE_NONE	SERIAL_WRITE_NONE
#define UART_WRITE_NON_BLOCK	SERIAL_WRITE_NON_BLOCK ///< Do not block when transmitting, if the FIFO is full return immediately

/** UART Wait Directions */
#define UART_WAIT_NONE	SERIAL_WAIT_NONE
#define UART_WAIT_RECEIVE	SERIAL_WAIT_RECEIVE ///< Wait for data to be available in the receive FIFO
#define UART_WAIT_TRANSMIT	SERIAL_WAIT_TRANSMIT ///< Wait for space to be available in the transmit FIFO

/** UART Status Flags */
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

/** UART specific types */

/** UART Properties */
typedef struct _UART_PROPERTIES UART_PROPERTIES;
struct _UART_PROPERTIES
{
	uint32_t flags; ///< Device flags (eg UART_FLAG_DATA_8BIT)
	uint32_t minrate; ///< Minimum supported baud rate
	uint32_t maxrate; ///< Maximum supported baud rate
	uint32_t baudrate; ///< Current baud rate setting
	uint32_t databits; ///< Current data bits setting
	uint32_t stopbits; ///< Current stop bits setting
	uint32_t parity; ///< Current parity setting
	uint32_t flowcontrol; ///< Current flow control setting
};

/** UART Device */
typedef struct _UART_DEVICE UART_DEVICE;

/** UART Enumeration Callback */
typedef uint32_t STDCALL (*uart_enumerate_cb)(UART_DEVICE *uart, void *data);
/** UART Notification Callback */
typedef uint32_t STDCALL (*uart_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** UART Device Methods */
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
	DEVICE device; ///< The Device entry for this UART
	// UART Properties
	uint32_t uartid; ///< Unique Id of this UART in the UART table
	uint32_t uartmode; ///< UART mode (eg UART_MODE_SERIAL)
	uint32_t uartstate; ///< UART state (eg UART_STATE_ENABLED)
	uint32_t uartstatus; ///< UART status (eg UART_STATUS_RX_FULL)(May not be real time status depending on the driver)
	uart_device_open_proc deviceopen; ///< A Device specific DeviceOpen method implementing the standard UART device interface (Mandatory)
	uart_device_close_proc deviceclose; ///< A Device specific DeviceClose method implementing the standard UART device interface (Mandatory)
	uart_device_read_proc deviceread; ///< A Device specific DeviceRead method implementing the standard UART device interface (Mandatory)
	uart_device_write_proc devicewrite; ///< A Device specific DeviceWrite method implementing the standard UART device interface (Mandatory)
	uart_device_wait_proc devicewait; ///< A Device specific DeviceWait method implementing the standard UART device interface (Or nil if the default method is suitable)
	uart_device_get_status_proc devicegetstatus; ///< A Device specific DeviceGetStatus method implementing the standard UART device interface (Or nil if the default method is suitable)
	uart_device_set_status_proc devicesetstatus; ///< A Device specific DeviceSetStatus method implementing the standard UART device interface (Optional)
	uart_device_get_properties_proc devicegetproperties; ///< A Device specific DeviceGetProperties method implementing the standard UART device interface (Or nil if the default method is suitable)
	uart_device_set_properties_proc devicesetproperties; ///< A Device specific DeviceSetProperties method implementing the standard UART device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; ///< Device lock
	EVENT_HANDLE receivewait; ///< Read wait event
	EVENT_HANDLE transmitwait; ///< Write wait event
	UART_PROPERTIES properties; ///< Device properties
	// Serial Properties
	SERIAL_DEVICE *serial; ///< The Serial device represented by this UART
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t transmitcount;
	uint32_t transmiterrors;
	// Internal Properties
	UART_DEVICE *prev; ///< Previous entry in UART table
	UART_DEVICE *next; ///< Next entry in UART table
};

/** UART Functions */

/**
 * @brief Open a UART device ready for sending and receiving
 * @param UART The UART device to open
 * @param BaudRate Baud rate for the connection (eg 9600, 57600, 115200 etc
 * @param DataBits Size of the data (eg SERIAL_DATA_8BIT)
 * @param StopBits Number of stop bits (eg SERIAL_STOP_1BIT)
 * @param Parity Parity type for the data (eg SERIAL_PARITY_NONE)
 * @param FlowControl Flow control for the connection (eg SERIAL_FLOW_NONE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_open(UART_DEVICE *uart, uint32_t baudrate, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t flowcontrol);

/**
 * @brief Close a UART device and terminate sending and receiving
 * @param UART The UART device to close
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_close(UART_DEVICE *uart);

/**
 * @brief Read data from a UART device
 * @param UART The UART device to read from
 * @param Buffer Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Flags The flags to control reading (eg UART_READ_NON_BLOCK)
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_read(UART_DEVICE *uart, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Write data to a UART device
 * @param UART The UART device to write to
 * @param Buffer Pointer to a buffer of data to transmit
 * @param Size The size of the buffer
 * @param Flags The flags to control writing (eg UART_WRITE_NON_BLOCK)
 * @param Count The number of bytes written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_write(UART_DEVICE *uart, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Wait for data to be available in the receive or transmit FIFO of a UART device
 * @param UART The UART device to wait for
 * @param Direction The direction of data to wait for (eg UART_WAIT_RECEIVE)
 * @param Timeout The number of milliseconds to wait for data (INFINITE to wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_wait(UART_DEVICE *uart, uint32_t direction, uint32_t timeout);

/**
 * @brief Get the current line status of a UART device
 * @param UART The UART device to get the status from
 * @return A set of flags containing the device status (eg UART_STATUS_RTS)
 * @note Replaced by UARTDeviceGetStatus for consistency
 */
uint32_t STDCALL uart_device_status(UART_DEVICE *uart);

/**
 * @brief Get the current line status of a UART device
 * @param UART The UART device to get the status from
 * @return A set of flags containing the device status (eg UART_STATUS_RTS)
 */
uint32_t STDCALL uart_device_get_status(UART_DEVICE *uart);

/**
 * @brief Set the current line status of a UART device
 * @param UART The UART device to set the status for
 * @param Status The device status flags to be set (eg UART_STATUS_RTS)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Not all UART_STATUS_* flags can be set, the device may ignore invalid values
 * @note Not all UART devices support set status, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 */
uint32_t STDCALL uart_device_set_status(UART_DEVICE *uart, uint32_t status);

/**
 * @brief Get the properties for the specified UART device
 * @param UART The UART device to get properties from
 * @param Properties Pointer to a PUARTProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Replaced by UARTDeviceGetProperties for consistency
 */
uint32_t STDCALL uart_device_properties(UART_DEVICE *uart, UART_PROPERTIES *properties);

/**
 * @brief Get the properties for the specified UART device
 * @param UART The UART device to get properties from
 * @param Properties Pointer to a PUARTProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_get_properties(UART_DEVICE *uart, UART_PROPERTIES *properties);

/**
 * @brief Set the properties for the specified UART device
 * @param UART The UART device to set properties for
 * @param Properties Pointer to a PUARTProperties structure to use
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_set_properties(UART_DEVICE *uart, UART_PROPERTIES *properties);

/**
 * @brief Create a new UART entry
 * @return Pointer to new UART entry or nil if UART could not be created
 */
UART_DEVICE * STDCALL uart_device_create(void);

/**
 * @brief Create a new UART entry
 * @param Size Size in bytes to allocate for new UART (Including the UART entry)
 * @return Pointer to new UART entry or nil if UART could not be created
 */
UART_DEVICE * STDCALL uart_device_create_ex(uint32_t size);

/**
 * @brief Destroy an existing UART entry
 * @param UART The UART device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_destroy(UART_DEVICE *uart);

/**
 * @brief Register a new UART in the UART table
 * @param UART The UART device to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_register(UART_DEVICE *uart);

/**
 * @brief Deregister a UART from the UART table
 * @param UART The UART device to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_deregister(UART_DEVICE *uart);

/**
 * @brief Find a UART device by ID in the UART table
 * @param UARTId The ID number of the UART to find
 * @return Pointer to UART device entry or nil if not found
 */
UART_DEVICE * STDCALL uart_device_find(uint32_t uartid);

/**
 * @brief Find a UART device by name in the UART table
 * @param Name The name of the UART to find (eg UART0)
 * @return Pointer to UART device entry or nil if not found
 */
UART_DEVICE * STDCALL uart_device_find_by_name(const char *name);

/**
 * @brief Find a UART device by description in the UART table
 * @param Description The description of the UART to find (eg BCM2836 PL011 UART)
 * @return Pointer to UART device entry or nil if not found
 */
UART_DEVICE * STDCALL uart_device_find_by_description(const char *description);

/**
 * @brief Enumerate all UART devices in the UART table
 * @param Callback The callback function to call for each UART in the table
 * @param Data A private data pointer to pass to callback for each UART in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL uart_device_enumerate(uart_enumerate_cb callback, void *data);

/**
 * @brief Register a notification for UART device changes
 * @param UART The UART device to notify changes for (Optional, pass nil for all UART devices)
 * @param Callback The function to call when a notification event occurs
 * @param Data A private data pointer to pass to callback when a notification event occurs
 * @param Notification The events to register for notification of (eg DEVICE_NOTIFICATION_REGISTER)
 * @param Flags The flags to control the notification (eg NOTIFIER_FLAG_WORKER)
 */
uint32_t STDCALL uart_device_notification(UART_DEVICE *uart, uart_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/** UART Helper Functions */

/**
 * @brief Get the current UART count
 */
uint32_t STDCALL uart_get_count(void);

/**
 * @brief Get the current default UART device
 */
UART_DEVICE * STDCALL uart_device_get_default(void);

/**
 * @brief Set the current default UART device
 */
uint32_t STDCALL uart_device_set_default(UART_DEVICE *uart);

/**
 * @brief Check if the supplied UART is in the UART table
 */
UART_DEVICE * STDCALL uart_device_check(UART_DEVICE *uart);

/**
 * @brief Convert a UART type value to a string
 */
uint32_t STDCALL uart_type_to_string(uint32_t uarttype, char *string, uint32_t len);

/**
 * @brief Convert a UART mode to a string
 */
uint32_t STDCALL uart_mode_to_string(uint32_t uartmode, char *string, uint32_t len);

/**
 * @brief Convert a UART state value to a string
 */
uint32_t STDCALL uart_state_to_string(uint32_t uartstate, char *string, uint32_t len);

/** UART Serial Helper Functions */

/**
 * @brief Read data from a UART device into the receive buffer of the associated Serial device
 * @note Not intended to be called directly by applications
 * @note Caller must hold the lock on the serial device which owns the UART
 */
uint32_t STDCALL uart_serial_device_receive(UART_DEVICE *uart);

/**
 * @brief Write data to a UART device from the transmit buffer of the associated Serial device
 * @note Not intended to be called directly by applications
 * @note Caller must hold the lock on the serial device which owns the UART
 */
uint32_t STDCALL uart_serial_device_transmit(UART_DEVICE *uart);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_UART_H