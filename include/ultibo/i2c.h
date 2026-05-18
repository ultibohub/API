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
#ifndef _ULTIBO_I2C_H
#define _ULTIBO_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/** I2C specific constants */
#define I2C_NAME_PREFIX	"I2C" ///< Name prefix for I2C Devices
#define I2CSLAVE_NAME_PREFIX	"I2CSlave" ///< Name prefix for I2C Slave Devices

/** I2C Device Types */
#define I2C_TYPE_NONE	0
#define I2C_TYPE_MASTER	1
#define I2C_TYPE_SLAVE	2

#define I2C_TYPE_MAX	2

/** I2C Device States */
#define I2C_STATE_DISABLED	0
#define I2C_STATE_ENABLED	1

#define I2C_STATE_MAX	1

/** I2C Device Flags */
#define I2C_FLAG_NONE	0x00000000
#define I2C_FLAG_SLAVE	0x00000001 ///< Device is a slave not a master
#define I2C_FLAG_10BIT	0x00000002 ///< Device supports 10bit addressing
#define I2C_FLAG_16BIT	0x00000004 ///< Device supports 16bit addressing
#define I2C_FLAG_DMA	0x00000008 ///< Device supports DMA transfers

/** I2C Transfer Flags */
#define I2C_TRANSFER_NONE	0x00000000
#define I2C_TRANSFER_DMA	0x00000001 ///< Use DMA for transfer (Write/Read) (If supported) (Note: Buffers must be DMA compatible)
#define I2C_TRANSFER_IGNORE_NAK	0x00000002 ///< Ignore NAK responses and continue (For compatibility with unusual devices)

/** I2C specific types */

/** I2C Properties */
typedef struct _I2C_PROPERTIES I2C_PROPERTIES;
struct _I2C_PROPERTIES
{
	uint32_t flags; ///< Device flags (eg I2C_FLAG_SLAVE)
	uint32_t maxsize; ///< Maximum supported data transfer size
	uint32_t minclock; ///< Minimum supported clock rate
	uint32_t maxclock; ///< Maximum supported clock rate
	uint32_t clockrate; ///< Current clock rate
	uint16_t slaveaddress; ///< Current slave address
};

/** I2C Device */
typedef struct _I2C_DEVICE I2C_DEVICE;

/** I2C Enumeration Callback */
typedef uint32_t STDCALL (*i2c_enumerate_cb)(I2C_DEVICE *i2c, void *data);
/** I2C Notification Callback */
typedef uint32_t STDCALL (*i2c_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** I2C Device Methods */
typedef uint32_t STDCALL (*i2c_device_start_proc)(I2C_DEVICE *i2c, uint32_t rate);
typedef uint32_t STDCALL (*i2c_device_stop_proc)(I2C_DEVICE *i2c);

typedef uint32_t STDCALL (*i2c_device_read_proc)(I2C_DEVICE *i2c, uint16_t address, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*i2c_device_write_proc)(I2C_DEVICE *i2c, uint16_t address, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*i2c_device_write_read_proc)(I2C_DEVICE *i2c, uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*i2c_device_write_write_proc)(I2C_DEVICE *i2c, uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t flags, uint32_t *count);

typedef uint32_t STDCALL (*i2c_device_get_rate_proc)(I2C_DEVICE *i2c);
typedef uint32_t STDCALL (*i2c_device_set_rate_proc)(I2C_DEVICE *i2c, uint32_t rate);

typedef uint16_t STDCALL (*i2c_device_get_address_proc)(I2C_DEVICE *i2c);
typedef uint32_t STDCALL (*i2c_device_set_address_proc)(I2C_DEVICE *i2c, uint16_t address);

typedef uint32_t STDCALL (*i2c_device_get_properties_proc)(I2C_DEVICE *i2c, I2C_PROPERTIES *properties);

struct _I2C_DEVICE
{
	// Device Properties
	DEVICE device; ///< The Device entry for this I2C
	// I2C Properties
	uint32_t i2cid; ///< Unique Id of this I2C in the I2C table
	uint32_t i2cstate; ///< I2C state (eg I2C_STATE_ENABLED)
	i2c_device_start_proc devicestart; ///< A Device specific DeviceStart method implementing the standard I2C device interface (Mandatory)
	i2c_device_stop_proc devicestop; ///< A Device specific DeviceStop method implementing the standard I2C device interface (Mandatory)
	i2c_device_read_proc deviceread; ///< A Device specific DeviceRead method implementing the standard I2C device interface (Mandatory)
	i2c_device_write_proc devicewrite; ///< A Device specific DeviceWrite method implementing the standard I2C device interface (Mandatory)
	i2c_device_write_read_proc devicewriteread; ///< A Device specific DeviceWriteRead method implementing the standard I2C device interface (Or nil if the default method is suitable)
	i2c_device_write_write_proc devicewritewrite; ///< A Device specific DeviceWriteWrite method implementing the standard I2C device interface (Or nil if the default method is suitable)
	i2c_device_get_rate_proc devicegetrate; ///< A Device specific DeviceGetRate method implementing the standard I2C device interface (Or nil if the default method is suitable)
	i2c_device_set_rate_proc devicesetrate; ///< A Device specific DeviceSetRate method implementing the standard I2C device interface (Or nil if the default method is suitable)
	i2c_device_get_address_proc devicegetaddress; ///< A Device specific DeviceGetAddress method implementing the standard I2C device interface (Or nil if the default method is suitable)
	i2c_device_set_address_proc devicesetaddress; ///< A Device specific DeviceSetAddress method implementing the standard I2C device interface (Or nil if the default method is suitable)
	i2c_device_get_properties_proc devicegetproperties; ///< A Device specific DeviceGetProperties method implementing the standard I2C device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t readcount;
	uint32_t writecount;
	uint32_t readerrors;
	uint32_t writeerrors;
	// Driver Properties
	MUTEX_HANDLE lock; ///< Device lock
	SEMAPHORE_HANDLE wait; ///< Read/Write wait event
	uint32_t clockrate; ///< Clock rate (Hz)
	uint16_t slaveaddress; ///< Slave address
	I2C_PROPERTIES properties; ///< Device properties
	// Internal Properties
	I2C_DEVICE *prev; ///< Previous entry in I2C table
	I2C_DEVICE *next; ///< Next entry in I2C table
};

/** I2C Functions */

/**
 * @brief Start the specified I2C device ready for reading and writing
 * @param I2C The I2C device to start
 * @param Rate The clock rate to set for the device (0 to use the default rate)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_start(I2C_DEVICE *i2c, uint32_t rate);

/**
 * @brief Stop the specified I2C device and terminate reading and writing
 * @param I2C The I2C device to stop
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_stop(I2C_DEVICE *i2c);

/**
 * @brief Read data from the specified I2C device
 * @param I2C The I2C device to read from
 * @param Address The slave address to read from (I2C_ADDRESS_INVALID to use the current address)
 * @param Buffer Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_read(I2C_DEVICE *i2c, uint16_t address, void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Read data from the specified I2C device
 * @param I2C The I2C device to read from
 * @param Address The slave address to read from (I2C_ADDRESS_INVALID to use the current address)
 * @param Buffer Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Flags The flags for this transfer (eg I2C_TRANSFER_DMA)
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_read_ex(I2C_DEVICE *i2c, uint16_t address, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Write data to the specified I2C device
 * @param I2C The I2C device to write to
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Buffer Pointer to a buffer of data to transmit
 * @param Size The size of the buffer
 * @param Count The number of bytes written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_write(I2C_DEVICE *i2c, uint16_t address, void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Write data to the specified I2C device
 * @param I2C The I2C device to write to
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Buffer Pointer to a buffer of data to transmit
 * @param Size The size of the buffer
 * @param Flags The flags for this transfer (eg I2C_TRANSFER_DMA)
 * @param Count The number of bytes written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_write_ex(I2C_DEVICE *i2c, uint16_t address, void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Write data to and Read data from the specified I2C device in one operation
 * Useful for devices that require a register address specified before a read (eg EEPROM devices)
 * @param I2C The I2C device to write to and read from
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Initial Pointer to the initial buffer to transmit
 * @param Len The size of the initial buffer
 * @param Data Pointer to a buffer to receive the data
 * @param Size The size of the data buffer
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_write_read(I2C_DEVICE *i2c, uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t *count);

/**
 * @brief Write data to and Read data from the specified I2C device in one operation
 * Useful for devices that require a register address specified before a read (eg EEPROM devices)
 * @param I2C The I2C device to write to and read from
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Initial Pointer to the initial buffer to transmit
 * @param Len The size of the initial buffer
 * @param Data Pointer to a buffer to receive the data
 * @param Size The size of the data buffer
 * @param Flags The flags for this transfer (eg I2C_TRANSFER_DMA)
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_write_read_ex(I2C_DEVICE *i2c, uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Write 2 data blocks to the specified I2C device in one operation
 * Useful for devices that require a register address specified before a write (eg EEPROM devices)
 * @param I2C The I2C device to write to
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Initial Pointer to the initial buffer to transmit
 * @param Len The size of the initial buffer
 * @param Data Pointer to a buffer of data to transmit
 * @param Size The size of the data buffer
 * @param Count The number of bytes of data written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_write_write(I2C_DEVICE *i2c, uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t *count);

/**
 * @brief Write 2 data blocks to the specified I2C device in one operation
 * Useful for devices that require a register address specified before a write (eg EEPROM devices)
 * @param I2C The I2C device to write to
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Initial Pointer to the initial buffer to transmit
 * @param Len The size of the initial buffer
 * @param Data Pointer to a buffer of data to transmit
 * @param Size The size of the data buffer
 * @param Flags The flags for this transfer (eg I2C_TRANSFER_DMA)
 * @param Count The number of bytes of data written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_write_write_ex(I2C_DEVICE *i2c, uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Get the clock rate of the specified I2C device
 * @param I2C The I2C device to get the clock rate from
 * @return The clock rate in Hz or 0 on failure
 */
uint32_t STDCALL i2c_device_get_rate(I2C_DEVICE *i2c);

/**
 * @brief Set the clock rate for the specified I2C device
 * @param I2C The I2C device to set the clock rate for
 * @param Rate The clock rate to set in Hz
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_set_rate(I2C_DEVICE *i2c, uint32_t rate);

/**
 * @brief Get the slave address for the specified I2C device
 * @param I2C The I2C device to get the slave address from
 * @return The slave address or I2C_ADDRESS_INVALID on failure
 */
uint16_t STDCALL i2c_device_get_address(I2C_DEVICE *i2c);

/**
 * @brief Set the slave address for the specified I2C device
 * @param I2C The I2C device to set the slave address for
 * @param Address The slave address to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_set_address(I2C_DEVICE *i2c, uint16_t address);

/**
 * @brief Get the properties for the specified I2C device
 * @param I2C The I2C device to get properties from
 * @param Properties Pointer to a TI2CProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Replaced by I2CDeviceGetProperties for consistency
 */
uint32_t STDCALL i2c_device_properties(I2C_DEVICE *i2c, I2C_PROPERTIES *properties);

/**
 * @brief Get the properties for the specified I2C device
 * @param I2C The I2C device to get properties from
 * @param Properties Pointer to a TI2CProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_get_properties(I2C_DEVICE *i2c, I2C_PROPERTIES *properties);

/**
 * @brief Create a new I2C entry
 * @return Pointer to new I2C entry or nil if I2C could not be created
 */
I2C_DEVICE * STDCALL i2c_device_create(void);

/**
 * @brief Create a new I2C entry
 * @param Size Size in bytes to allocate for new I2C (Including the I2C entry)
 * @return Pointer to new I2C entry or nil if I2C could not be created
 */
I2C_DEVICE * STDCALL i2c_device_create_ex(uint32_t size);

/**
 * @brief Destroy an existing I2C entry
 * @param I2C The I2C device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_destroy(I2C_DEVICE *i2c);

/**
 * @brief Register a new I2C in the I2C table
 * @param I2C The I2C device to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_register(I2C_DEVICE *i2c);

/**
 * @brief Deregister an I2C from the I2C table
 * @param I2C The I2C device to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_deregister(I2C_DEVICE *i2c);

/**
 * @brief Find an I2C device by ID in the I2C table
 * @param I2CId The ID number of the I2C device to find
 * @return Pointer to I2C device entry or nil if not found
 */
I2C_DEVICE * STDCALL i2c_device_find(uint32_t i2cid);

/**
 * @brief Find an I2C device by name in the device table
 * @param Name The name of the I2C device to find (eg I2C0)
 * @return Pointer to I2C device entry or nil if not found
 */
I2C_DEVICE * STDCALL i2c_device_find_by_name(const char *name);

/**
 * @brief Find an I2C device by description in the device table
 * @param Description The description of the I2C to find (eg BCM2837 BSC1 Master I2C)
 * @return Pointer to I2C device entry or nil if not found
 */
I2C_DEVICE * STDCALL i2c_device_find_by_description(const char *description);

/**
 * @brief Enumerate all I2C devices in the I2C table
 * @param Callback The callback function to call for each I2C device in the table
 * @param Data A private data pointer to pass to callback for each I2C device in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_device_enumerate(i2c_enumerate_cb callback, void *data);

/**
 * @brief Register a notification for I2C device changes
 * @param Device The I2C device to notify changes for (Optional, pass nil for all I2C devices)
 * @param Callback The function to call when a notification event occurs
 * @param Data A private data pointer to pass to callback when a notification event occurs
 * @param Notification The events to register for notification of (eg DEVICE_NOTIFICATION_REGISTER)
 * @param Flags The flags to control the notification (eg NOTIFIER_FLAG_WORKER)
 */
uint32_t STDCALL i2c_device_notification(I2C_DEVICE *i2c, i2c_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/** I2C Slave Functions */

/**
 * @brief Start the specified I2C slave ready for reading and writing
 * @param I2C The I2C slave to start
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_start(I2C_DEVICE *i2c);

/**
 * @brief Stop the specified I2C slave and terminate reading and writing
 * @param I2C The I2C slave to stop
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_stop(I2C_DEVICE *i2c);

/**
 * @brief Read data from the specified I2C slave
 * @param I2C The I2C slave to read from
 * @param Buffer Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_read(I2C_DEVICE *i2c, void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Write data to the specified I2C slave
 * @param I2C The I2C slave to write to
 * @param Buffer Pointer to a buffer of data to transmit
 * @param Size The size of the buffer
 * @param Count The number of bytes written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_write(I2C_DEVICE *i2c, void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Get the address for the specified I2C slave
 * @param I2C The I2C slave to get the address from
 * @return The address or I2C_ADDRESS_INVALID on failure
 */
uint16_t STDCALL i2c_slave_get_address(I2C_DEVICE *i2c);

/**
 * @brief Set the address for the specified I2C slave
 * @param I2C The I2C slave to set the address for
 * @param Address The address to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_set_address(I2C_DEVICE *i2c, uint16_t address);

/**
 * @brief Get the properties for the specified I2C slave
 * @param I2C The I2C slave to get properties from
 * @param Properties Pointer to a TI2CProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_get_properties(I2C_DEVICE *i2c, I2C_PROPERTIES *properties);

/**
 * @brief Create a new I2C slave entry
 * @return Pointer to new I2C slave entry or nil if I2C could not be created
 */
I2C_DEVICE * STDCALL i2c_slave_create(void);

/**
 * @brief Create a new I2C slave entry
 * @param Size Size in bytes to allocate for new I2C (Including the I2C slave entry)
 * @return Pointer to new I2C slave entry or nil if I2C could not be created
 */
I2C_DEVICE * STDCALL i2c_slave_create_ex(uint32_t size);

/**
 * @brief Destroy an existing I2C slave entry
 * @param I2C The I2C slave to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_destroy(I2C_DEVICE *i2c);

/**
 * @brief Register a new I2C slave in the I2C table
 * @param I2C The I2C slave to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_register(I2C_DEVICE *i2c);

/**
 * @brief Deregister an I2C slave from the I2C table
 * @param I2C The I2C slave to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_slave_deregister(I2C_DEVICE *i2c);

/**
 * @brief Find an I2C slave by ID in the I2C table
 * @param I2CId The ID number of the I2C slave to find
 * @return Pointer to I2C slave entry or nil if not found
 */
I2C_DEVICE * STDCALL i2c_slave_find(uint32_t i2cid);

/**
 * @brief Find an I2C slave by name in the device table
 * @param Name The name of the I2C slave to find (eg I2CSlave0)
 * @return Pointer to I2C slave entry or nil if not found
 */
I2C_DEVICE * STDCALL i2c_slave_find_by_name(const char *name);

/**
 * @brief Find an I2C slave by description in the device table
 * @param Description The description of the I2C slave to find (eg BCM2837 I2C Slave)
 * @return Pointer to I2C slave entry or nil if not found
 */
I2C_DEVICE * STDCALL i2c_slave_find_by_description(const char *description);

/** I2C Helper Functions */

/**
 * @brief Get the current I2C count
 */
uint32_t STDCALL i2c_get_count(void);

/**
 * @brief Get the current default I2C device
 */
I2C_DEVICE * STDCALL i2c_device_get_default(void);

/**
 * @brief Set the current default I2C device
 */
uint32_t STDCALL i2c_device_set_default(I2C_DEVICE *i2c);

/**
 * @brief Check if the supplied I2C is in the I2C table
 */
I2C_DEVICE * STDCALL i2c_device_check(I2C_DEVICE *i2c);

/**
 * @brief Check if the supplied I2C is a slave device
 */
BOOL STDCALL i2c_device_is_slave(I2C_DEVICE *i2c);

/**
 * @brief Convert an I2C type value to a string
 */
uint32_t STDCALL i2c_type_to_string(uint32_t i2ctype, char *string, uint32_t len);

/**
 * @brief Convert an I2C state value to a string
 */
uint32_t STDCALL i2c_state_to_string(uint32_t i2cstate, char *string, uint32_t len);

/**
 * @brief Determine if the supplied address is a 7bit address
 */
BOOL STDCALL i2c_is7bit_address(uint16_t address);

/**
 * @brief Determine if the supplied address is a 10bit address
 */
BOOL STDCALL i2c_is10bit_address(uint16_t address);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_I2C_H