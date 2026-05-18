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
#ifndef _ULTIBO_SERIAL_H
#define _ULTIBO_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/** Serial specific constants */
#define SERIAL_NAME_PREFIX	"Serial" ///< Name prefix for Serial Devices

#define SERIAL_LOGGING_DESCRIPTION	"Serial Logging"

#define SERIAL_RECEIVE_DEPTH_DEFAULT	SIZE_2K ///< Default receive buffer size in bytes
#define SERIAL_TRANSMIT_DEPTH_DEFAULT	SIZE_2K ///< Default transmit buffer size in bytes

#define SERIAL_PUSH_TIMEOUT	50 ///< Timeout (Milliseconds) for Push RX/TX (Implementation specific)

/** Serial Device Types */
#define SERIAL_TYPE_NONE	0
#define SERIAL_TYPE_UART	1
#define SERIAL_TYPE_USB	2

#define SERIAL_TYPE_MAX	2

/** Serial Device States */
#define SERIAL_STATE_CLOSED	0
#define SERIAL_STATE_CLOSING	1
#define SERIAL_STATE_OPENING	2
#define SERIAL_STATE_OPEN	3

#define SERIAL_STATE_MAX	3

/** Serial Device Flags */
#define SERIAL_FLAG_NONE	0x00000000
#define SERIAL_FLAG_DATA_8BIT	0x00000001 ///< Device supports 8 data bits
#define SERIAL_FLAG_DATA_7BIT	0x00000002 ///< Device supports 7 data bits
#define SERIAL_FLAG_DATA_6BIT	0x00000004 ///< Device supports 6 data bits
#define SERIAL_FLAG_DATA_5BIT	0x00000008 ///< Device supports 5 data bits
#define SERIAL_FLAG_STOP_1BIT	0x00000010 ///< Device supports 1 stop bit
#define SERIAL_FLAG_STOP_2BIT	0x00000020 ///< Device supports 2 stop bits
#define SERIAL_FLAG_STOP_1BIT5	0x00000040 ///< Device supports 1.5 stop bits
#define SERIAL_FLAG_PARITY_ODD	0x00000080 ///< Device supports odd parity
#define SERIAL_FLAG_PARITY_EVEN	0x00000100 ///< Device supports even parity
#define SERIAL_FLAG_PARITY_MARK	0x00000200 ///< Device supports mark parity
#define SERIAL_FLAG_PARITY_SPACE	0x00000400 ///< Device supports space parity
#define SERIAL_FLAG_FLOW_RTS_CTS	0x00000800 ///< Device supports RTS/CTS flow control
#define SERIAL_FLAG_FLOW_DSR_DTR	0x00001000 ///< Device supports DSR/DTR flow control
#define SERIAL_FLAG_PUSH_RX	0x00002000 ///< Device requires pushed receive (Implementation specific)
#define SERIAL_FLAG_PUSH_TX	0x00004000 ///< Device requires pushed transmit (Implementation specific)

/** Serial Read Flags */
#define SERIAL_READ_NONE	0x00000000
#define SERIAL_READ_NON_BLOCK	0x00000001 ///< Do not block when reading, if the buffer is empty return immediately
#define SERIAL_READ_PEEK_BUFFER	0x00000002 ///< Return the number of bytes available in the receive buffer without reading them

/** Serial Write Flags */
#define SERIAL_WRITE_NONE	0x00000000
#define SERIAL_WRITE_NON_BLOCK	0x00000001 ///< Do not block when writing, if the buffer is full return immediately
#define SERIAL_WRITE_PEEK_BUFFER	0x00000002 ///< Return the number of bytes free in the transmit buffer without writing anything

/** Serial Wait Directions */
#define SERIAL_WAIT_NONE	0
#define SERIAL_WAIT_RECEIVE	1 ///< Wait for data to be available in the receive buffer
#define SERIAL_WAIT_TRANSMIT	2 ///< Wait for space to be available in the transmit buffer

/** Serial Flush Flags */
#define SERIAL_FLUSH_NONE	0x00000000
#define SERIAL_FLUSH_RECEIVE	0x00000001 ///< Flush the receive buffer
#define SERIAL_FLUSH_TRANSMIT	0x00000002 ///< Flush the transmit buffer

/** Serial Status Flags */
#define SERIAL_STATUS_NONE	0x00000000
#define SERIAL_STATUS_RTS	0x00000001 ///< RTS (Request to Send) is set (If applicable)
#define SERIAL_STATUS_CTS	0x00000002 ///< CTS (Clear to Send) is set (If applicable)
#define SERIAL_STATUS_DSR	0x00000004 ///< DSR (Data Set Ready) is set (If applicable)
#define SERIAL_STATUS_DTR	0x00000008 ///< DTR (Data Terminal Ready) is set (If applicable)
#define SERIAL_STATUS_RX_FULL	0x00000010 ///< Receive buffer is full
#define SERIAL_STATUS_RX_EMPTY	0x00000020 ///< Receive buffer is empty
#define SERIAL_STATUS_TX_FULL	0x00000040 ///< Transmit buffer is full
#define SERIAL_STATUS_TX_EMPTY	0x00000080 ///< Transmit buffer is empty
#define SERIAL_STATUS_BUSY	0x00000100 ///< Device is busy
#define SERIAL_STATUS_BREAK_ERROR	0x00000200 ///< Break error reported
#define SERIAL_STATUS_PARITY_ERROR	0x00000400 ///< Parity error reported
#define SERIAL_STATUS_FRAMING_ERROR	0x00000800 ///< Framing error reported
#define SERIAL_STATUS_OVERRUN_ERROR	0x00001000 ///< Overrun error reported
#define SERIAL_STATUS_DCD	0x00002000 ///< DCD (Data Carrier Detect) is set (If applicable)
#define SERIAL_STATUS_RI	0x00004000 ///< RI (Ring Indicator) is set (If applicable)

/** Serial specific types */

/** Serial Properties */
typedef struct _SERIAL_PROPERTIES SERIAL_PROPERTIES;
struct _SERIAL_PROPERTIES
{
	uint32_t flags; ///< Device flags (eg SERIAL_FLAG_DATA_8BIT)
	uint32_t minrate; ///< Minimum supported baud rate (0 for any rate supported)
	uint32_t maxrate; ///< Maximum supported baud rate (0 for any rate supported)
	uint32_t baudrate; ///< Current baud rate setting
	uint32_t databits; ///< Current data bits setting
	uint32_t stopbits; ///< Current stop bits setting
	uint32_t parity; ///< Current parity setting
	uint32_t flowcontrol; ///< Current flow control setting
	uint32_t receivedepth; ///< Current receive depth setting
	uint32_t transmitdepth; ///< Current transmit depth setting
};

/** Serial Buffer */
typedef struct _SERIAL_BUFFER SERIAL_BUFFER;
struct _SERIAL_BUFFER
{
	EVENT_HANDLE wait; ///< Data ready / Buffer free event
	uint32_t start; ///< Index of first byte in buffer
	uint32_t count; ///< Number of bytes in buffer
	uint32_t size; ///< Size of buffer
	void *data; ///< Buffered data
};

/** Serial Device */
typedef struct _SERIAL_DEVICE SERIAL_DEVICE;

/** Serial Enumeration Callback */
typedef uint32_t STDCALL (*serial_enumerate_cb)(SERIAL_DEVICE *serial, void *data);
/** Serial Notification Callback */
typedef uint32_t STDCALL (*serial_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** Serial Device Methods */
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
	DEVICE device; ///< The Device entry for this Serial
	// Serial Properties
	uint32_t serialid; ///< Unique Id of this Serial device in the Serial device table
	uint32_t serialstate; ///< Serial state (eg SERIAL_STATE_OPEN)
	uint32_t serialstatus; ///< Serial status (eg SERIAL_STATUS_RX_FULL)(May not be real time status depending on the driver)
	serial_device_open_proc deviceopen; ///< A Device specific DeviceOpen method implementing the standard Serial device interface (Mandatory)
	serial_device_close_proc deviceclose; ///< A Device specific DeviceClose method implementing the standard Serial device interface (Mandatory)
	serial_device_read_proc deviceread; ///< A Device specific DeviceRead method implementing the standard Serial device interface (Mandatory)
	serial_device_write_proc devicewrite; ///< A Device specific DeviceWrite method implementing the standard Serial device interface (Mandatory)
	serial_device_wait_proc devicewait; ///< A Device specific DeviceWait method implementing the standard Serial device interface (Or nil if the default method is suitable)
	serial_device_flush_proc deviceflush; ///< A Device specific DeviceFlush method implementing the standard Serial device interface (Or nil if the default method is suitable)
	serial_device_get_status_proc devicegetstatus; ///< A Device specific DeviceGetStatus method implementing the standard Serial device interface (Or nil if the default method is suitable)
	serial_device_set_status_proc devicesetstatus; ///< A Device specific DeviceSetStatus method implementing the standard Serial device interface (Optional)
	serial_device_get_properties_proc devicegetproperties; ///< A Device specific DeviceGetProperties method implementing the standard Serial device interface (Or nil if the default method is suitable)
	serial_device_set_properties_proc devicesetproperties; ///< A Device specific DeviceSetProperties method implementing the standard Serial device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; ///< Device lock
	SERIAL_BUFFER receive; ///< Serial receive buffer
	SERIAL_BUFFER transmit; ///< Serial transmit buffer
	SERIAL_PROPERTIES properties; ///< Device properties
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t receiveoverruns;
	uint32_t transmitcount;
	uint32_t transmiterrors;
	uint32_t transmitoverruns;
	// Internal Properties
	SERIAL_DEVICE *prev; ///< Previous entry in Serial table
	SERIAL_DEVICE *next; ///< Next entry in Serial table
};

/** Serial Functions */

/**
 * @brief Open a Serial device ready for sending and receiving
 * @param Serial The Serial device to open
 * @param BaudRate Baud rate for the connection (eg 9600, 57600, 115200 etc
 * @param DataBits Size of the data (eg SERIAL_DATA_8BIT)
 * @param StopBits Number of stop bits (eg SERIAL_STOP_1BIT)
 * @param Parity Parity type for the data (eg SERIAL_PARITY_NONE)
 * @param FlowControl Flow control for the connection (eg SERIAL_FLOW_NONE)
 * @param ReceiveDepth Size of the receive buffer (0 = Default size)
 * @param TransmitDepth Size of the transmit buffer (0 = Default size)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_open(SERIAL_DEVICE *serial, uint32_t baudrate, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t flowcontrol, uint32_t receivedepth, uint32_t transmitdepth);

/**
 * @brief Close a Serial device and terminate sending and receiving
 * @param Serial The Serial device to close
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_close(SERIAL_DEVICE *serial);

/**
 * @brief Read data from a Serial device
 * @param Serial The Serial device to read from
 * @param Buffer Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Flags The flags to control reading (eg SERIAL_READ_NON_BLOCK)
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_read(SERIAL_DEVICE *serial, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Write data to a Serial device
 * @param Serial The Serial device to write to
 * @param Buffer Pointer to a buffer of data to transmit
 * @param Size The size of the buffer
 * @param Flags The flags to control writing (eg SERIAL_WRITE_NON_BLOCK)
 * @param Count The number of bytes written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_write(SERIAL_DEVICE *serial, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Wait for data to be available in the receive or transmit buffers of a Serial device
 * @param Serial The Serial device to wait for
 * @param Direction The direction of data to wait for (eg SERIAL_WAIT_RECEIVE)
 * @param Timeout The number of milliseconds to wait for data (INFINITE to wait forever)
 * @param Count The number of bytes available on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_wait(SERIAL_DEVICE *serial, uint32_t direction, uint32_t timeout, uint32_t *count);

/**
 * @brief Discard the contents of the receive and/or transmit buffers of a Serial device
 * @param Serial The Serial device to flush
 * @param Flags The flags to indicate what to flush (eg SERIAL_FLUSH_RECEIVE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_flush(SERIAL_DEVICE *serial, uint32_t flags);

/**
 * @brief Get the current line status of a Serial device
 * @param Serial The Serial device to get the status from
 * @return A set of flags containing the device status (eg SERIAL_STATUS_RTS)
 * @note Replaced by SerialDeviceGetStatus for consistency
 */
uint32_t STDCALL serial_device_status(SERIAL_DEVICE *serial);

/**
 * @brief Get the current line status of a Serial device
 * @param Serial The Serial device to get the status from
 * @return A set of flags containing the device status (eg SERIAL_STATUS_RTS)
 */
uint32_t STDCALL serial_device_get_status(SERIAL_DEVICE *serial);

/**
 * @brief Set the current line status of a Serial device
 * @param Serial The Serial device to set the status for
 * @param Status The device status flags to be set (eg SERIAL_STATUS_RTS)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Not all SERIAL_STATUS_* flags can be set, the device may ignore invalid values
 * @note Not all serial devices support set status, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 */
uint32_t STDCALL serial_device_set_status(SERIAL_DEVICE *serial, uint32_t status);

/**
 * @brief Get the properties for the specified Serial device
 * @param Serial The Serial device to get properties from
 * @param Properties Pointer to a PSerialProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Replaced by SerialDeviceGetProperties for consistency
 */
uint32_t STDCALL serial_device_properties(SERIAL_DEVICE *serial, SERIAL_PROPERTIES *properties);

/**
 * @brief Get the properties for the specified Serial device
 * @param Serial The Serial device to get properties from
 * @param Properties Pointer to a PSerialProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_get_properties(SERIAL_DEVICE *serial, SERIAL_PROPERTIES *properties);

/**
 * @brief Set the properties for the specified Serial device
 * @param Serial The Serial device to set properties for
 * @param Properties Pointer to a PSerialProperties structure to use
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_set_properties(SERIAL_DEVICE *serial, SERIAL_PROPERTIES *properties);

/**
 * @brief Create a new Serial entry
 * @return Pointer to new Serial entry or nil if Serial could not be created
 */
SERIAL_DEVICE * STDCALL serial_device_create(void);

/**
 * @brief Create a new Serial entry
 * @param Size Size in bytes to allocate for new Serial (Including the Serial entry)
 * @return Pointer to new Serial entry or nil if Serial could not be created
 */
SERIAL_DEVICE * STDCALL serial_device_create_ex(uint32_t size);

/**
 * @brief Destroy an existing Serial entry
 * @param Serial The serial device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_destroy(SERIAL_DEVICE *serial);

/**
 * @brief Register a new Serial in the Serial table
 * @param Serial The serial device to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_register(SERIAL_DEVICE *serial);

/**
 * @brief Deregister a Serial from the Serial table
 * @param Serial The serial device to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_deregister(SERIAL_DEVICE *serial);

/**
 * @brief Find a serial device by ID in the serial table
 * @param SerialId The ID number of the serial to find
 * @return Pointer to serial device entry or nil if not found
 */
SERIAL_DEVICE * STDCALL serial_device_find(uint32_t serialid);

/**
 * @brief Find a serial device by name in the serial table
 * @param Name The name of the serial to find (eg Serial0)
 * @return Pointer to serial device entry or nil if not found
 */
SERIAL_DEVICE * STDCALL serial_device_find_by_name(const char *name);

/**
 * @brief Find a serial device by description in the serial table
 * @param Description The description of the serial to find (eg BCM2836 PL011 UART)
 * @return Pointer to serial device entry or nil if not found
 */
SERIAL_DEVICE * STDCALL serial_device_find_by_description(const char *description);

/**
 * @brief Enumerate all serial devices in the serial table
 * @param Callback The callback function to call for each serial in the table
 * @param Data A private data pointer to pass to callback for each serial in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL serial_device_enumerate(serial_enumerate_cb callback, void *data);

/**
 * @brief Register a notification for serial device changes
 * @param Serial The serial device to notify changes for (Optional, pass nil for all serial devices)
 * @param Callback The function to call when a notification event occurs
 * @param Data A private data pointer to pass to callback when a notification event occurs
 * @param Notification The events to register for notification of (eg DEVICE_NOTIFICATION_REGISTER)
 * @param Flags The flags to control the notification (eg NOTIFIER_FLAG_WORKER)
 */
uint32_t STDCALL serial_device_notification(SERIAL_DEVICE *serial, serial_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/**
 * @brief Print formatted text to a Serial device
 * @param Serial The serial device to print text to
 * @param Format The formatted text to print (As per printf in standard C library)
 * @return On success the total number of characters sent to the serial device, on error a negative value is returned and errno is set to the error code
 */
int STDCALL serial_device_printf(SERIAL_DEVICE *serial, const char *format, ...) _ATTRIBUTE ((__format__ (__printf__, 2, 3)));

/** Serial Helper Functions */

/**
 * @brief Get the current Serial count
 */
uint32_t STDCALL serial_get_count(void);

/**
 * @brief Get the current default Serial device
 */
SERIAL_DEVICE * STDCALL serial_device_get_default(void);

/**
 * @brief Set the current default Serial device
 */
uint32_t STDCALL serial_device_set_default(SERIAL_DEVICE *serial);

/**
 * @brief Check if the supplied Serial is in the Serial table
 */
SERIAL_DEVICE * STDCALL serial_device_check(SERIAL_DEVICE *serial);

/**
 * @brief Convert a Serial type value to a string
 */
uint32_t STDCALL serial_type_to_string(uint32_t serialtype, char *string, uint32_t len);

/**
 * @brief Convert a Serial state value to a string
 */
uint32_t STDCALL serial_state_to_string(uint32_t serialstate, char *string, uint32_t len);

/**
 * @brief Redirect standard input to the serial device specified by Serial
 * @param Serial The serial device to redirect input to (or nil to stop redirection)
 * @return True if completed successfully or False if an error occurred
 * @note Redirects the input of the text file Input which also
 *        redirects the input of Read, ReadLn and the standard C library
 */
BOOL STDCALL serial_device_redirect_input(SERIAL_DEVICE *serial);

/**
 * @brief Redirect standard output to the serial device specified by Serial
 * @param Serial The serial device to redirect output to (or nil to stop redirection)
 * @return True if completed successfully or False if an error occurred
 * @note Redirects the output of the text files Output, ErrOutput, StdOut and StdErr
 *        which also redirects the output of Write, WriteLn and the standard C library
 */
BOOL STDCALL serial_device_redirect_output(SERIAL_DEVICE *serial);

/**
 * @brief Return a pointer to the next read from the buffer and the number of bytes that can be read
 * @note Caller must hold the lock on the serial device which owns the buffer
 */
void * STDCALL serial_buffer_read_start(SERIAL_BUFFER *buffer, uint32_t *available);

/**
 * @brief Update the buffer to reflect the number of bytes removed when reading
 * @note Caller must hold the lock on the serial device which owns the buffer
 */
BOOL STDCALL serial_buffer_read_complete(SERIAL_BUFFER *buffer, uint32_t removed);

/**
 * @brief Return a pointer to the next write to the buffer and the number of bytes that can be written
 * @note Caller must hold the lock on the serial device which owns the buffer
 */
void * STDCALL serial_buffer_write_start(SERIAL_BUFFER *buffer, uint32_t *available);

/**
 * @brief Update the buffer to reflect the number of bytes added when writing
 * @note Caller must hold the lock on the serial device which owns the buffer
 */
BOOL STDCALL serial_buffer_write_complete(SERIAL_BUFFER *buffer, uint32_t added);

uint32_t STDCALL serial_data_bits_to_string(uint32_t bits, char *string, uint32_t len);
uint32_t STDCALL serial_stop_bits_to_string(uint32_t bits, char *string, uint32_t len);
uint32_t STDCALL serial_parity_to_string(uint32_t parity, char *string, uint32_t len);
uint32_t STDCALL serial_flow_control_to_string(uint32_t flow, char *string, uint32_t len);

/** Serial Logging Helper Functions */

/**
 * @brief Add a new serial logging device on receipt of a device register notification
 */
uint32_t STDCALL serial_logging_device_add(SERIAL_DEVICE *serial);

/**
 * @brief Remove a serial logging device on receipt of a device deregister notification
 */
uint32_t STDCALL serial_logging_device_remove(SERIAL_DEVICE *serial);

/**
 * @brief Break down the serial parameters value into component parts of baud rate, parity, data bits and stop bits
 * The parameters must be in the form 'BaudRate,Parity,DataBits,StopBits' (eg '115200,N,8,1')
 */
uint32_t STDCALL serial_logging_device_parameters(SERIAL_DEVICE *serial, const char *parameters, uint32_t *baudrate, uint32_t *parity, uint32_t *databits, uint32_t *stopbits);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_SERIAL_H