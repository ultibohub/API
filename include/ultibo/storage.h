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
#ifndef _ULTIBO_STORAGE_H
#define _ULTIBO_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/system.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* Storage specific constants */
#define STORAGE_NAME_PREFIX	"Storage" // Name prefix for Storage Devices

#define STORAGE_STATUS_TIMER_INTERVAL	1000

/* Storage Device Types */
#define STORAGE_TYPE_NONE	0
#define STORAGE_TYPE_HDD	1
#define STORAGE_TYPE_FDD	2
#define STORAGE_TYPE_CDROM	3
#define STORAGE_TYPE_OPTICAL	4
#define STORAGE_TYPE_TAPE	5
#define STORAGE_TYPE_REMOVABLE	6

/* Storage Device States */
#define STORAGE_STATE_EJECTED	0
#define STORAGE_STATE_EJECTING	1
#define STORAGE_STATE_INSERTING	2
#define STORAGE_STATE_INSERTED	3

/* Storage Device Flags */
#define STORAGE_FLAG_NONE	0x00000000
#define STORAGE_FLAG_REMOVABLE	0x00000001
#define STORAGE_FLAG_LBA48	0x00000002
#define STORAGE_FLAG_NOT_READY	0x00000004
#define STORAGE_FLAG_NO_MEDIA	0x00000008
#define STORAGE_FLAG_READ_ONLY	0x00000010
#define STORAGE_FLAG_WRITE_ONLY	0x00000020
#define STORAGE_FLAG_ERASEABLE	0x00000040
#define STORAGE_FLAG_LOCKABLE	0x00000080
#define STORAGE_FLAG_LOCKED	0x00000100
#define STORAGE_FLAG_EJECTABLE	0x00000200
#define STORAGE_FLAG_CHANGABLE	0x00000400

/* Storage Device Control Codes */
#define STORAGE_CONTROL_TEST_READY	1 // Test Unit Ready
#define STORAGE_CONTROL_RESET	2 // Reset Device
#define STORAGE_CONTROL_TEST_MEDIA	3 // Test No Media
#define STORAGE_CONTROL_LOCK	4 // Lock Media
#define STORAGE_CONTROL_UNLOCK	5 // Unlock Media
#define STORAGE_CONTROL_EJECT	6 // Eject Media
#define STORAGE_CONTROL_TEST_LOCKED	7 // Test Media Locked
#define STORAGE_CONTROL_TEST_CHANGED	8 // Test Media Changed
#define STORAGE_CONTROL_GET_VENDORID	9 // Get Vendor ID
#define STORAGE_CONTROL_GET_PRODUCTID	10 // Get Product ID
#define STORAGE_CONTROL_GET_SERIAL	11 // Get Serial No
#define STORAGE_CONTROL_GET_REVISION	12 // Get Revision No
#define STORAGE_CONTROL_GET_PRODUCT	13 // Get Product Name
#define STORAGE_CONTROL_GET_MANUFACTURER	14 // Get Manufacturer Name

/* ============================================================================== */
/* Storage specific types */
/* Storage Device */
typedef struct _STORAGE_DEVICE STORAGE_DEVICE;

/* Storage Enumeration Callback */
typedef uint32_t STDCALL (*storage_enumerate_cb)(STORAGE_DEVICE *storage, void *data);
/* Storage Notification Callback */
typedef uint32_t STDCALL (*storage_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Storage Device Methods */
typedef uint32_t STDCALL (*storage_device_read_proc)(STORAGE_DEVICE *storage, int64_t start, int64_t count, void *buffer);
typedef uint32_t STDCALL (*storage_device_write_proc)(STORAGE_DEVICE *storage, int64_t start, int64_t count, void *buffer);
typedef uint32_t STDCALL (*storage_device_erase_proc)(STORAGE_DEVICE *storage, int64_t start, int64_t count);
typedef uint32_t STDCALL (*storage_device_control_proc)(STORAGE_DEVICE *storage, int request, size_t argument1, size_t *argument2);

struct _STORAGE_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Storage
	// Storage Properties
	uint32_t storageid; // Unique Id of this Storage in the Storage table
	uint32_t storagestate; // Storage state (eg STORAGE_STATE_INSERTED)
	storage_device_read_proc deviceread; // A Device specific DeviceRead method implementing a standard Storage device interface
	storage_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing a standard Storage device interface
	storage_device_erase_proc deviceerase; // A Device specific DeviceErase method implementing a standard Storage device interface
	storage_device_control_proc devicecontrol; // A Device specific DeviceControl method implementing a standard Storage device interface
	// Driver Properties
	MUTEX_HANDLE lock; // Storage lock
	uint32_t targetid; // SCSI ID
	uint32_t targetlun; // LUN
	uint32_t blocksize; // Block Size
	int64_t blockcount; // Number of Blocks
	uint32_t blockshift; // Shift Count for Blocks to Bytes conversion (eg 9 for 512 byte blocks)
	char *vendor; // ATA Model, SCSI Vendor
	char *product; // ATA Serial No, SCSI Product
	char *revision; // Firmware Revision
	TIMER_HANDLE statustimer; // Timer for status change detection
	// Statistics Properties
	uint64_t readcount;
	uint64_t readerrors;
	uint64_t writecount;
	uint64_t writeerrors;
	uint64_t erasecount;
	uint64_t eraseerrors;
	// Internal Properties
	STORAGE_DEVICE *prev; // Previous entry in Storage table
	STORAGE_DEVICE *next; // Next entry in Storage table
};

/* ============================================================================== */
/* Storage Functions */
uint32_t STDCALL storage_device_read(STORAGE_DEVICE *storage, int64_t start, int64_t count, void *buffer);
uint32_t STDCALL storage_device_write(STORAGE_DEVICE *storage, int64_t start, int64_t count, void *buffer);
uint32_t STDCALL storage_device_erase(STORAGE_DEVICE *storage, int64_t start, int64_t count);
uint32_t STDCALL storage_device_control(STORAGE_DEVICE *storage, int request, size_t argument1, size_t *argument2);

uint32_t STDCALL storage_device_set_state(STORAGE_DEVICE *storage, uint32_t state);

uint32_t STDCALL storage_device_start_status(STORAGE_DEVICE *storage, uint32_t interval);
uint32_t STDCALL storage_device_stop_status(STORAGE_DEVICE *storage);

STORAGE_DEVICE * STDCALL storage_device_create(void);
STORAGE_DEVICE * STDCALL storage_device_create_ex(uint32_t size);
uint32_t STDCALL storage_device_destroy(STORAGE_DEVICE *storage);

uint32_t STDCALL storage_device_register(STORAGE_DEVICE *storage);
uint32_t STDCALL storage_device_deregister(STORAGE_DEVICE *storage);

STORAGE_DEVICE * STDCALL storage_device_find(uint32_t storageid);
STORAGE_DEVICE * STDCALL storage_device_find_by_device(DEVICE *device);
STORAGE_DEVICE * STDCALL storage_device_find_by_name(char *name);
STORAGE_DEVICE * STDCALL storage_device_find_by_description(char *description);
uint32_t STDCALL storage_device_enumerate(storage_enumerate_cb callback, void *data);

uint32_t STDCALL storage_device_notification(STORAGE_DEVICE *storage, storage_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Storage Helper Functions */
uint32_t STDCALL storage_get_count(void);

STORAGE_DEVICE * STDCALL storage_device_check(STORAGE_DEVICE *storage);

uint32_t STDCALL storage_device_type_to_string(uint32_t storagetype, char *string, uint32_t len);
uint32_t STDCALL storage_device_state_to_string(uint32_t storagestate, char *string, uint32_t len);

uint32_t STDCALL storage_device_state_to_notification(uint32_t state);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_STORAGE_H