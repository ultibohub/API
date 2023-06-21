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
#ifndef _ULTIBO_DEVICE_H
#define _ULTIBO_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/platform.h"

/* ============================================================================== */
/* Device specific constants */
#define DEVICE_NAME_PREFIX	"Device" // Name prefix for Devices

/* Device Signature */
#define DEVICE_SIGNATURE	0xAD03FE3C

/* Device name constants */
#define DEVICE_NAME_LENGTH	SIZE_64 // Length of device name
#define DEVICE_DESC_LENGTH	SIZE_128 // Length of device description

/* Device Busses */
#define DEVICE_BUS_NONE	0
#define DEVICE_BUS_PCI	1
#define DEVICE_BUS_USB	2
#define DEVICE_BUS_ISA	3
#define DEVICE_BUS_PS2	4
#define DEVICE_BUS_FIREWIRE	5
#define DEVICE_BUS_SD	6 // SD/SDHC/SDXC/SDIO etc
#define DEVICE_BUS_MMC	7 // MMC/eMMC etc
#define DEVICE_BUS_ATA	8
#define DEVICE_BUS_IDE	9
#define DEVICE_BUS_SCSI	10
#define DEVICE_BUS_ATAPI	11
#define DEVICE_BUS_SATA	12
#define DEVICE_BUS_SERIAL	13
#define DEVICE_BUS_SPI	14 // Serial Peripheral Interface device
#define DEVICE_BUS_MMIO	15 // Memory Mapped IO device (No Bus)
#define DEVICE_BUS_PCIE	16
#define DEVICE_BUS_I2C	17 // I2C connected device
#define DEVICE_BUS_VIRTIO	18 // Virtual devices
#define DEVICE_BUS_BLUETOOTH	19 // Bluetooth connected devices

#define DEVICE_BUS_MAX	19

/* Device States */
#define DEVICE_STATE_UNREGISTERED	0
#define DEVICE_STATE_REGISTERED	1

#define DEVICE_STATE_MAX	1

/* Device Ids */
#define DEVICE_ID_ANY	0xFFFFFFFF // Any Device (Pass to DeviceFind to match all devices)

/* Device Classes */
#define DEVICE_CLASS_NONE	0 // No Device
#define DEVICE_CLASS_USBHOST	1 // A USB Host Controller (eg XHCI/EHCI/UHCI/OHCI or DWCOTG etc) (Implementing a standard USB host interface)
#define DEVICE_CLASS_PCIHOST	2 // A PCI Host Controller (Implementing a standard PCI host interface)
#define DEVICE_CLASS_USB	3 // A USB Device (eg Hub/Keyboard/Mouse/Mass Storage/Vendor Specific etc) (Implementing a standard USB device interface)
#define DEVICE_CLASS_PCI	4 // A PCI Device (eg Graphics/Controller etc) (Implementing a standard PCI device interface)
#define DEVICE_CLASS_NETWORK	5 // A Network Device (Implementing a standard Network device interface). May also be a USB or PCI device
#define DEVICE_CLASS_STORAGE	6 // A Storage Device (Implementing a standard Storage device interface). May also be a USB, PCI, MMC, SCSI or ATA device
#define DEVICE_CLASS_BLOCK	DEVICE_CLASS_STORAGE
#define DEVICE_CLASS_FILESYSTEM	7 // A FileSystem Device (eg FAT/NTFS/CDFS/EXTFS etc)(Implementing a standard FileSystem device interface)
#define DEVICE_CLASS_PROTOCOL	8 // A Protocol Device (eg TCP/UDP/IP/ICMP etc) (Implementing a standard Protocol device interface)
#define DEVICE_CLASS_TRANSPORT	DEVICE_CLASS_PROTOCOL
#define DEVICE_CLASS_KEYBOARD	9 // A Keyboard Device (Implementing a standard Keyboard device interface)
#define DEVICE_CLASS_MOUSE	10 // A Mouse Device (Implementing a standard Mouse device interface)
#define DEVICE_CLASS_BLUETOOTH	11 // A Bluetooth Device (eg Keyboard/Mouse/Audio/Serial) (Implementing a standard Bluetooth device interface)
#define DEVICE_CLASS_SERIAL	12 // A Serial Device (Implementing a standard Serial device interface)
#define DEVICE_CLASS_AUDIO	13 // An Audio Device (Implementing a standard Audio device interface)
#define DEVICE_CLASS_VIDEO	14 // A Video Device (Implementing a standard Video device interface)
#define DEVICE_CLASS_SCSI	15 // A SCSI Device (Implementing a standard SCSI device interface). May also be a PCI device
#define DEVICE_CLASS_ATA	16 // An ATA/ATAPI Device (Implementing a standard ATA/ATAPI device interface). May also be a PCI device
#define DEVICE_CLASS_IDE	DEVICE_CLASS_ATA
#define DEVICE_CLASS_ATAPI	DEVICE_CLASS_ATA
#define DEVICE_CLASS_IMAGE	17 // An Image Device (eg Camera) (Implementing a standard Image device interface)
#define DEVICE_CLASS_PRINTER	18 // A Printer Device (Implementing a standard Printer device interface)
#define DEVICE_CLASS_COMMUNICATIONS	19 // A Communications Device (Implementing a standard Communications device interface)
#define DEVICE_CLASS_SMART_CARD	20 // A Smart Card Device (Implementing a standard Smart Card device interface)
#define DEVICE_CLASS_MONITOR	21 // A Monitor Device (Implementing a standard Monitor device interface)
#define DEVICE_CLASS_DISPLAY	22 // A Display Device (eg Billboard) (Implementing a standard Display device interface)
#define DEVICE_CLASS_AUDIOVIDEO	23 // An Audio/Video Device (Implementing a standard Audio/Video device interface)
#define DEVICE_CLASS_IRDA	24 // An Infrared Device (Implementing a standard Infrared device interface)
#define DEVICE_CLASS_SPI	25 // An SPI Device (Implementing a standard SPI device interface)
#define DEVICE_CLASS_I2C	26 // An I2C Device (Implementing a standard I2C device interface)
#define DEVICE_CLASS_UART	27 // A UART Device (Implementing a standard UART device interface)
#define DEVICE_CLASS_MMC	28 // An MMC Device (Implementing a standard MMC device interface)
#define DEVICE_CLASS_SD	29 // An SD Device (Implementing a standard SD device interface)
#define DEVICE_CLASS_SDHCI	30 // An SD/MMC Host Controller (Implementing a standard SDHCI device interface)
#define DEVICE_CLASS_SDHOST	DEVICE_CLASS_SDHCI
#define DEVICE_CLASS_MMCHOST	DEVICE_CLASS_SDHCI
#define DEVICE_CLASS_MMCIHOST	DEVICE_CLASS_SDHCI
#define DEVICE_CLASS_DFU	31 // A Device Firmware Update Device (Implementing a standard DFU device interface)
#define DEVICE_CLASS_GPIO	32 // A GPIO Device (Implementing a standard GPIO device interface)
#define DEVICE_CLASS_MAILBOX	33 // A Mailbox Device
#define DEVICE_CLASS_OPENGL	34 // An OpenGL Device
#define DEVICE_CLASS_DVB	35 // A Digital Video Broadcast (DVB) Device
#define DEVICE_CLASS_DAB	36 // A Digital Audio Broadcast (DAB) Device
#define DEVICE_CLASS_DMA	37 // A DMA Controller Device (Implementing a standard DMA controller interface)
#define DEVICE_CLASS_SCSIHOST	38 // A SCSI Host Device (Implementing a standard SCSI host interface)
#define DEVICE_CLASS_ATAHOST	39 // An ATA Host Device (Implementing a standard ATA host interface)
#define DEVICE_CLASS_TIMER	40 // A Timer or Counter Device
#define DEVICE_CLASS_RANDOM	41 // A Random Number Generator Device
#define DEVICE_CLASS_FRAMEBUFFER	42 // A Frame Buffer Device
#define DEVICE_CLASS_WATCHDOG	43 // A Watchdog Timer Device
#define DEVICE_CLASS_CLOCK	44 // A Clock (Date/Time) Device
#define DEVICE_CLASS_CONSOLE	45 // A Console Device
#define DEVICE_CLASS_RTC	46 // A Real Time Clock (Battery Backed) Device
#define DEVICE_CLASS_USBHUB	47 // A USB Hub (Implementing a standard USB hub interface)
#define DEVICE_CLASS_LOGGING	48 // A Logging Device (Implementing a standard Logging device interface)
#define DEVICE_CLASS_PCM	49 // A PCM Sound Device (Implementing a standard PCM device interface)
#define DEVICE_CLASS_I2S	DEVICE_CLASS_PCM
#define DEVICE_CLASS_PWM	50 // A Pulse Width Modulation (PWM) Device
#define DEVICE_CLASS_1WIRE	51 // A 1-Wire Device (Implementing a standard W1 device interface)
#define DEVICE_CLASS_CLOCK_MANAGER	52 // A Clock Manager Device
#define DEVICE_CLASS_CODEC	53 // A CODEC Device (eg Audio or Video)
#define DEVICE_CLASS_TOUCH	54 // A Touch Device
#define DEVICE_CLASS_MEMORY	55 // A Memory Device (eg OTP, NVRAM or Flash)
#define DEVICE_CLASS_GENERIC	56 // A Generic Device
#define DEVICE_CLASS_VIRTIO	57 // A VIRTIO Device (eg Block/Network/Memory/Console/Input etc) (Implementing a standard VIRTIO device interface)
#define DEVICE_CLASS_BLUETOOTHHOST	58 // A Bluetooth Host Controller (Implementing a standard Bluetooth host interface)
#define DEVICE_CLASS_JOYSTICK	59 // A Joystick or Gamepad Device
#define DEVICE_CLASS_HID	60 // A Human Interface Device (HID)

#define DEVICE_CLASS_MAX	60

#define DEVICE_CLASS_ANY	0xFFFFFFFF // Any Device (Pass to DeviceFind or DeviceEnumerate to match all devices)

/* Device Notification Flags */
#define DEVICE_NOTIFICATION_NONE	0x00000000 // Pass to DeviceNotification to cancel an existing Notification
#define DEVICE_NOTIFICATION_REGISTER	0x00000001
#define DEVICE_NOTIFICATION_DEREGISTER	0x00000002
#define DEVICE_NOTIFICATION_OPEN	0x00000004
#define DEVICE_NOTIFICATION_CLOSE	0x00000008
#define DEVICE_NOTIFICATION_UP	0x00000010
#define DEVICE_NOTIFICATION_DOWN	0x00000020
#define DEVICE_NOTIFICATION_INSERT	0x00000040
#define DEVICE_NOTIFICATION_EJECT	0x00000080
#define DEVICE_NOTIFICATION_ATTACH	0x00000100
#define DEVICE_NOTIFICATION_DETACH	0x00000200
#define DEVICE_NOTIFICATION_ENABLE	0x00000400
#define DEVICE_NOTIFICATION_DISABLE	0x00000800
#define DEVICE_NOTIFICATION_BIND	0x00001000
#define DEVICE_NOTIFICATION_UNBIND	0x00002000
#define DEVICE_NOTIFICATION_ATTACHING	0x00004000
#define DEVICE_NOTIFICATION_DETACHING	0x00008000
#define DEVICE_NOTIFICATION_INSERTING	0x00010000
#define DEVICE_NOTIFICATION_EJECTING	0x00020000
#define DEVICE_NOTIFICATION_OPENING	0x00040000
#define DEVICE_NOTIFICATION_CLOSING	0x00080000
#define DEVICE_NOTIFICATION_RESIZE	0x00100000
#define DEVICE_NOTIFICATION_RESIZING	0x00200000

/* Firmware name constants */
#define FIRMWARE_NAME_LENGTH	SIZE_256 // Length of firmware name

/* Firmware Actions */
#define FIRMWARE_ACTION_NONE	0
#define FIRMWARE_ACTION_SIZE	1 // Return the size in bytes of the firmware item
#define FIRMWARE_ACTION_OPEN	2 // Open the firmware item and return a handle
#define FIRMWARE_ACTION_READ	3 // Read from the firmware item specified by a given handle
#define FIRMWARE_ACTION_SEEK	4 // Seek to a location in the firmware item specified by a given handle
#define FIRMWARE_ACTION_CLOSE	5 // Close a handle to the firmware item
#define FIRMWARE_ACTION_ACQUIRE	6 // Acquire a memory block containing the firmware item
#define FIRMWARE_ACTION_RELEASE	7 // Release a memory block containing the firmware item

/* Firmware Constants */
#define FIRMWARE_WAIT_DELAY	100 // Delay between retries for firmware while waiting for timeout (Milliseconds)
#define FIRMWARE_MAX_BUFFER	SIZE_4M // Maximum size buffer able to be allocated for firmware by acquire

/* Notifier Signature */
#define NOTIFIER_SIGNATURE	0x6FA1BEC9

/* Notifier States */
#define NOTIFIER_STATE_UNREGISTERED	0
#define NOTIFIER_STATE_REGISTERED	1

/* Notifier Flags */
#define NOTIFIER_FLAG_NONE	0x00000000
#define NOTIFIER_FLAG_WORKER	0x00000001 // If set, notification callback event will be scheduled on a worker thread
#define NOTIFIER_FLAG_UNLOCK	0x00000002 // If set, the notifier table lock will be released before calling the notification callback event

/* ============================================================================== */
/* Driver specific constants */
#define DRIVER_NAME_PREFIX	"Driver" // Name prefix for Drivers

/* Driver Signature */
#define DRIVER_SIGNATURE	0x1EB4980A

/* Driver name constants */
#define DRIVER_NAME_LENGTH	SIZE_64 // Length of driver name

/* Driver States */
#define DRIVER_STATE_UNREGISTERED	0
#define DRIVER_STATE_REGISTERED	1

#define DRIVER_STATE_MAX	1

/* Driver Ids */
#define DRIVER_ID_ANY	0xFFFFFFFF // Any Driver (Pass to DriverFind to match all drivers)

/* Driver Classes */
#define DRIVER_CLASS_NONE	0 // No Driver
#define DRIVER_CLASS_USB	1 // A USB Driver (Implementing a standard USB driver interface)
#define DRIVER_CLASS_PCI	2 // A PCI Driver (Implementing a standard PCI driver interface)
#define DRIVER_CLASS_SDIO	3 // An SDIO Driver (Implementing a standard SDIO driver interface)
#define DRIVER_CLASS_BLUETOOTH	4 // A Bluetooth Driver (Implementing a standard Bluetooth driver interface)
#define DRIVER_CLASS_VIRTIO	5 // A VIRTIO Driver (Implementing a standard VIRTIO driver interface)
#define DRIVER_CLASS_HID	6 // A Human Interface Device (HID) Driver (Implementing a standard HID driver interface)

#define DRIVER_CLASS_MAX	6

#define DRIVER_CLASS_ANY	0xFFFFFFFF // Any Driver (Pass to DriverFind or DriverEnumerate to match all drivers)

/* ============================================================================== */
/* Host specific constants */
#define HOST_NAME_PREFIX	"Host" // Name prefix for Hosts

/* Host Signature */
#define HOST_SIGNATURE	0xF45D30FE

/* Host name constants */
#define HOST_NAME_LENGTH	SIZE_64 // Length of host name

/* Host States */
#define HOST_STATE_UNREGISTERED	0
#define HOST_STATE_REGISTERED	1

#define HOST_STATE_MAX	1

/* Host Ids */
#define HOST_ID_ANY	0xFFFFFFFF // Any Host (Pass to HostFind to match all hosts)

/* Host Classes */
#define HOST_CLASS_NONE	0 // No Host
#define HOST_CLASS_USB	1 // A USB Host (eg XHCI/EHCI/UHCI/OHCI or DWCOTG etc) (Implementing a standard USB host interface)
#define HOST_CLASS_PCI	2 // A PCI Host (eg AHCI etc) (Implementing a standard PCI host interface)
#define HOST_CLASS_SD	3 // An SD Host (eg MMC/SDIO etc) (Implementing a standard SD host interface)
#define HOST_CLASS_BLUETOOTH	4 // A Bluetooth Host (Implementing a standard Bluetooth host interface)

#define HOST_CLASS_MAX	4

#define HOST_CLASS_ANY	0xFFFFFFFF // Any Host (Pass to HostFind or HostEnumerate to match all hosts)

/* ============================================================================== */
/* Clock specific constants */
#define CLOCK_NAME_PREFIX	"Clock" // Name prefix for Clock Devices

/* Clock Device Types */
#define CLOCK_TYPE_NONE	0
#define CLOCK_TYPE_HARDWARE	1

#define CLOCK_TYPE_MAX	1

/* Clock Device States */
#define CLOCK_STATE_DISABLED	0
#define CLOCK_STATE_ENABLED	1

#define CLOCK_STATE_MAX	1

/* Clock Device Flags */
#define CLOCK_FLAG_NONE	0x00000000
#define CLOCK_FLAG_WRITABLE	0x00000001 // Device supports writing the clock value
#define CLOCK_FLAG_VARIABLE	0x00000002 // Device supports setting the clock rate

/* ============================================================================== */
/* Timer specific constants */
#define TIMER_NAME_PREFIX	"Timer" // Name prefix for Timer Devices

/* Timer Device Types */
#define TIMER_TYPE_NONE	0
#define TIMER_TYPE_HARDWARE	1

#define TIMER_TYPE_MAX	1

/* Timer Device States */
#define TIMER_STATE_DISABLED	0
#define TIMER_STATE_ENABLED	1

#define TIMER_STATE_MAX	1

/* Timer Device Flags */
#define TIMER_FLAG_NONE	0x00000000
#define TIMER_FLAG_WRAPPING	0x00000001 // Device provides a wrapping or self reloading counter
#define TIMER_FLAG_COUNTER	0x00000002 // Device will appear as a continuously incrementing counter when read
#define TIMER_FLAG_DOWN	0x00000004 // Device counts down from the starting value to zero (And optionally triggers an event)

/* Timer Event Flags */
#define TIMER_EVENT_FLAG_NONE	0x00000000
#define TIMER_EVENT_FLAG_REPEAT	0x00000001 // Event will be repeated until cancelled
#define TIMER_EVENT_FLAG_INTERRUPT	0x00000002 // Event will be dispatched by interrupt handler (If applicable)
/* Caution: Events called by the interrupt handler must obey interrupt rules with regard to locks, memory allocation and latency */

/* ============================================================================== */
/* Random specific constants */
#define RANDOM_NAME_PREFIX	"Random" // Name prefix for Random Devices

/* Random Device Types */
#define RANDOM_TYPE_NONE	0
#define RANDOM_TYPE_HARDWARE	1
#define RANDOM_TYPE_SOFTWARE	2

#define RANDOM_TYPE_MAX	2

/* Random Device States */
#define RANDOM_STATE_DISABLED	0
#define RANDOM_STATE_ENABLED	1

#define RANDOM_STATE_MAX	1

/* Random Device Flags */
#define RANDOM_FLAG_NONE	0x00000000

/* ============================================================================== */
/* Mailbox specific constants */
#define MAILBOX_NAME_PREFIX	"Mailbox" // Name prefix for Mailbox Devices

/* Mailbox Device Types */
#define MAILBOX_TYPE_NONE	0
#define MAILBOX_TYPE_GPU	1
#define MAILBOX_TYPE_LOCAL	2

#define MAILBOX_TYPE_MAX	2

/* Mailbox Device States */
#define MAILBOX_STATE_DISABLED	0
#define MAILBOX_STATE_ENABLED	1

#define MAILBOX_STATE_MAX	1

/* Mailbox Device Flags */
#define MAILBOX_FLAG_NONE	0x00000000

/* ============================================================================== */
/* Watchdog specific constants */
#define WATCHDOG_NAME_PREFIX	"Watchdog" // Name prefix for Watchdog Devices

/* Watchdog Device Types */
#define WATCHDOG_TYPE_NONE	0
#define WATCHDOG_TYPE_HARDWARE	1

#define WATCHDOG_TYPE_MAX	1

/* Watchdog Device States */
#define WATCHDOG_STATE_DISABLED	0
#define WATCHDOG_STATE_ENABLED	1

#define WATCHDOG_STATE_MAX	1

/* Watchdog Device Flags */
#define WATCHDOG_FLAG_NONE	0x00000000

/* ============================================================================== */
/* Device specific types */
typedef struct _DEVICE DEVICE;

/* Device Enumeration Callback */
typedef uint32_t STDCALL (*device_enumerate_cb)(DEVICE *device, void *data);
/* Device Notification Callback */
typedef uint32_t STDCALL (*device_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Device Entry */
struct _DEVICE
{
	// Device Properties
	uint32_t signature; // Signature for entry validation
	uint32_t deviceid; // Unique Id of this Device in the Device table
	uint32_t devicestate; // Device state (eg Registered/Unregistered)
	char devicename[DEVICE_NAME_LENGTH] // The name of the Device (eg Keyboard0, Storage0 or Network0 etc)
	uint32_t deviceclass; // The class of this Device (eg DEVICE_CLASS_USB, DEVICE_CLASS_NETWORK, DEVICE_CLASS_STORAGE etc)
	uint32_t devicebus; // The Bus type for the Device (eg DEVICE_BUS_USB)
	uint32_t devicetype; // A class specific Device type (eg KEYBOARD_TYPE_USB, MOUSE_TYPE_USB, NETWORK_TYPE_ETHERNET etc)
	uint32_t deviceflags; // The class specific Device flags
	void *devicedata; // A pointer to a class specific Device interface (eg PUSBDevice, PNetworkDevice or PStorageDevice etc) (Used by Drivers)
	char devicedescription[DEVICE_DESC_LENGTH] // A description of the Device (eg BCM2835 PL011 UART)
	// Internal Properties
	DEVICE *prev; // Previous entry in Device table
	DEVICE *next; // Next entry in Device table
};

typedef _DEVICE_FIRMWARE DEVICE_FIRMWARE;

/* Device Firmware Handler */
typedef uint32_t STDCALL (*device_firmware_handler)(DEVICE_FIRMWARE *firmware, uint32_t action, HANDLE *handle, void *buffer, uint32_t *value);

typedef _FIRMWARE_HANDLE FIRMWARE_HANDLE;

/* Device Firmware */
struct _DEVICE_FIRMWARE
{
	uint32_t deviceclass; // The Device class supported by this firmware (or DEVICE_CLASS_ANY for all devices)
	char name[FIRMWARE_NAME_LENGTH] // The device specific name of the firmware which may be a filename, a device model, id or type
	uint32_t size; // For block (memory) based firmware, the size passed to Create or 0 for other firmware types
	void *buffer; // For block (memory) based firmware, the buffer passed to Create or nil for other firmware types
	FIRMWARE_HANDLE *handles; // List of currently open handles for this firmware
	device_firmware_handler handler; // The device specific callback for the handler which provides this firmware
	// Internal Properties
	DEVICE_FIRMWARE *prev; // Previous entry in Device Firmware table
	DEVICE_FIRMWARE *next; // Next entry in Device Firmware table
};

/* Firmware Handle */
struct _FIRMWARE_HANDLE
{
	HANDLE handle;
	FIRMWARE_HANDLE *next;
};

/* Notifier Entry */
typedef struct _NOTIFIER NOTIFIER;
struct _NOTIFIER
{
	// Notifier Properties
	uint32_t signature; // Signature for entry validation
	uint32_t notifierstate; // Notifier state (eg Registered/Unregistered)
	uint32_t notifierflags; // Notifier flags (eg NOTIFIER_FLAG_WORKER)
	DEVICE *device; // The Device to notify on (or nil for all devices)
	uint32_t deviceclass; // The Device class to notify on (or DEVICE_CLASS_ANY for all devices)
	device_notification_cb callback; // The callback for device notifications
	void *data; // A pointer to callback specific data to be passed with notifications (Optional)
	uint32_t notification; // The mask of events to notify on (eg DEVICE_NOTIFICATION_REGISTER etc)
	// Internal Properties
	NOTIFIER *prev; // Previous entry in Notifier table
	NOTIFIER *next; // Next entry in Notifier table
};

/* Notifier Task */
typedef struct _NOTIFIER_TASK NOTIFIER_TASK;
struct _NOTIFIER_TASK
{
	DEVICE *device;
	device_notification_cb callback;
	void *data;
	uint32_t notification;
	NOTIFIER_TASK *next;
};

/* Notifier Retry */
typedef _NOTIFIER_RETRY NOTIFIER_RETRY;
struct _NOTIFIER_RETRY
{
	DEVICE *device;
	uint32_t notification;
};

/* ============================================================================== */
/* Driver specific types */
typedef struct _DRIVER DRIVER;

/* Driver Enumeration Callback */
typedef uint32_t STDCALL (*driver_enumerate_cb)(DRIVER *driver, void *data);

/* Driver Entry */
struct _DRIVER
{
	// Driver Properties
	uint32_t signature; // Signature for entry validation
	uint32_t driverid; // Unique Id of this Driver in the Driver table
	uint32_t driverstate; // Driver state (eg Registered/Unregistered)
	char drivername[DRIVER_NAME_LENGTH] // Descriptive name for the Driver (eg USB Mouse Driver)
	uint32_t driverclass; // The class of this Driver (eg DRIVER_CLASS_USB etc)
	// Internal Properties
	DRIVER *prev; // Previous entry in Driver table
	DRIVER *next; // Next entry in Driver table
};

/* ============================================================================== */
/* Host specific types */
typedef struct _HOST HOST;

/* Host Enumeration Callback */
typedef uint32_t STDCALL (*host_enumerate_cb)(HOST *host, void *data);

/* Host Entry */
struct _HOST
{
	// Host Properties
	uint32_t signature; // Signature for entry validation
	uint32_t hostid; // Unique Id of this Host in the Host table
	uint32_t hoststate; // Host state (eg Registered/Unregistered)
	char hostname[HOST_NAME_LENGTH] // Descriptive name for the Host (eg DWC OTG Host)
	uint32_t hostclass; // The class of this Host (eg HOST_CLASS_USB etc)
	// Internal Properties
	HOST *prev; // Previous entry in Host table
	HOST *next; // Next entry in Host table
};

/* ============================================================================== */
/* Clock specific types */
/* Clock Properties */
typedef struct _CLOCK_PROPERTIES CLOCK_PROPERTIES;
struct _CLOCK_PROPERTIES
{
	uint32_t flags; // Device flags (eg CLOCK_FLAG_WRITABLE)
	uint32_t rate; // Device current clock rate (Hz)
	uint32_t minrate; // Device minimum clock rate (Hz)
	uint32_t maxrate; // Device maximum clock rate (Hz)
};

/* Clock Device */
typedef struct _CLOCK_DEVICE CLOCK_DEVICE;

/* Clock Enumeration Callback */
typedef uint32_t STDCALL (*clock_enumerate_cb)(CLOCK_DEVICE *clock, void *data);
/* Clock Notification Callback */
typedef uint32_t STDCALL (*clock_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Clock Device Methods */
typedef uint32_t STDCALL (*clock_device_start_proc)(CLOCK_DEVICE *clock);
typedef uint32_t STDCALL (*clock_device_stop_proc)(CLOCK_DEVICE *clock);
typedef uint32_t STDCALL (*clock_device_read_proc)(CLOCK_DEVICE *clock);
typedef int64_t STDCALL (*clock_device_read64_proc)(CLOCK_DEVICE *clock);
typedef uint32_t STDCALL (*clock_device_write64_proc)(CLOCK_DEVICE *clock, int64_t value);
typedef uint32_t STDCALL (*clock_device_get_rate_proc)(CLOCK_DEVICE *clock);
typedef uint32_t STDCALL (*clock_device_set_rate_proc)(CLOCK_DEVICE *clock, uint32_t rate);
typedef uint32_t STDCALL (*clock_device_get_properties_proc)(CLOCK_DEVICE *clock, CLOCK_PROPERTIES *properties);

/* Clock Device */
struct _CLOCK_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Clock device
	// Clock Properties
	uint32_t clockid; // Unique Id of this Clock device in the Clock device table
	uint32_t clockstate; // Clock device state (eg CLOCK_STATE_ENABLED)
	clock_device_start_proc devicestart; // A device specific DeviceStart method implementing a standard clock device interface (Or nil if the default method is suitable)
	clock_device_stop_proc devicestop; // A device specific DeviceStop method implementing a standard clock device interface (Or nil if the default method is suitable)
	clock_device_read_proc deviceread; // A device specific DeviceRead method implementing a standard clock device interface (Or nil if the default method is suitable)
	clock_device_read64_proc deviceread64; // A device specific DeviceRead64 method implementing a standard clock device interface (Mandatory)
	clock_device_write64_proc devicewrite64; // A device specific DeviceWrite64 method implementing a standard clock device interface (Optional)
	clock_device_get_rate_proc devicegetrate; // A device specific DeviceGetRate method implementing a standard clock device interface (Or nil if the default method is suitable)
	clock_device_set_rate_proc devicesetrate; // A device specific DeviceSetRate method implementing a standard clock device interface (Optional)
	clock_device_get_properties_proc devicegetproperties; // A device specific DeviceGetProperties method implementing a standard clock device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t readcount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	void *address; // Device register base address
	uint32_t rate; // Device rate (Hz)
	uint32_t minrate; // Device minimum rate (Hz)
	uint32_t maxrate; // Device maximum rate (Hz)
	// Internal Properties
	CLOCK_DEVICE *prev; // Previous entry in Clock device table
	CLOCK_DEVICE *next; // Next entry in Clock device table
};

/* ============================================================================== */
/* Timer specific types */
typedef counter_event_cb timer_cb; // Counter callback from Platform

/* Timer Properties */
typedef struct _TIMER_PROPERTIES TIMER_PROPERTIES;
struct _TIMER_PROPERTIES
{
	uint32_t flags; // Device flags (eg TIMER_FLAG_WRAPPING)
	uint32_t bits; // Number of valid bits in timer read (eg 32 or 64)
	uint32_t minrate; // Device minimum clock rate (Hz)
	uint32_t maxrate; // Device maximum clock rate (Hz)
	uint32_t mininterval; // Device minimum interval (Ticks)
	uint32_t maxinterval; // Device maximum interval (Ticks)
};


/* Timer Device */
typedef struct _TIMER_DEVICE TIMER_DEVICE; // Forward declared for TimerWaiter

/* Timer Waiter (TTimerEvent is used already by the Threads unit) */
typedef struct _TIMER_WAITER TIMER_WAITER;
struct _TIMER_WAITER
{
	TIMER_DEVICE *timer; // Timer device this waiter belongs to
	timer_cb callback; // Callback function to call when event occurs
	void *data; // Pointer to pass to the callback function when event occurs
	TIMER_WAITER *prev; // Previous event in the list
	TIMER_WAITER *next; // Next event in the list
};

/* Timer Enumeration Callback */
typedef uint32_t STDCALL (*timer_enumerate_cb)(TIMER_DEVICE *timer, void *data);
/* Timer Notification Callback */
typedef uint32_t STDCALL (*timer_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Timer Device Methods */
typedef uint32_t STDCALL (*timer_device_start_proc)(TIMER_DEVICE *timer);
typedef uint32_t STDCALL (*timer_device_stop_proc)(TIMER_DEVICE *timer);
typedef uint32_t STDCALL (*timer_device_read_proc)(TIMER_DEVICE *timer);
typedef int64_t STDCALL (*timer_device_read64_proc)(TIMER_DEVICE *timer);
typedef uint32_t STDCALL (*timer_device_wait_proc)(TIMER_DEVICE *timer);
typedef uint32_t STDCALL (*timer_device_event_proc)(TIMER_DEVICE *timer, uint32_t flags, timer_cb callback, void *data);
typedef uint32_t STDCALL (*timer_device_cancel_proc)(TIMER_DEVICE *timer);
typedef uint32_t STDCALL (*timer_device_get_rate_proc)(TIMER_DEVICE *timer);
typedef uint32_t STDCALL (*timer_device_set_rate_proc)(TIMER_DEVICE *timer, uint32_t rate);
typedef uint32_t STDCALL (*timer_device_get_interval_proc)(TIMER_DEVICE *timer);
typedef uint32_t STDCALL (*timer_device_set_interval_proc)(TIMER_DEVICE *timer, uint32_t interval);
typedef uint32_t STDCALL (*timer_device_get_properties_proc)(TIMER_DEVICE *timer, TIMER_PROPERTIES *properties);

struct _TIMER_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Timer device
	// Timer Properties
	uint32_t timerid; // Unique Id of this Timer device in the Timer device table
	uint32_t timerstate; // Timer device state (eg TIMER_STATE_ENABLED)
	timer_device_start_proc devicestart; // A device specific DeviceStart method implementing a standard timer device interface (Mandatory)
	timer_device_stop_proc devicestop; // A device specific DeviceStop method implementing a standard timer device interface (Mandatory)
	timer_device_read_proc deviceread; // A device specific DeviceRead method implementing a standard timer device interface (One of Read or Read64 is Mandatory)
	timer_device_read64_proc deviceread64; // A device specific DeviceRead64 method implementing a standard timer device interface (One of Read or Read64 is Mandatory
	timer_device_wait_proc devicewait; // A device specific DeviceWait method implementing a standard timer device interface (Or nil if the operation is not supported)
	timer_device_event_proc deviceevent; // A device specific DeviceEvent method implementing a standard timer device interface (Or nil if the operation is not supported)
	timer_device_cancel_proc devicecancel; // A device specific DeviceCancel method implementing a standard timer device interface (Or nil if the operation is not supported)
	timer_device_get_rate_proc devicegetrate; // A device specific DeviceGetRate method implementing a standard timer device interface (Or nil if the default method is suitable)
	timer_device_set_rate_proc devicesetrate; // A device specific DeviceSetRate method implementing a standard timer device interface (Or nil if the default method is suitable)
	timer_device_get_interval_proc devicegetinterval; // A device specific DeviceGetInterval method implementing a standard timer device interface (Or nil if the default method is suitable)
	timer_device_set_interval_proc devicesetinterval; // A device specific DeviceSetInterval method implementing a standard timer device interface (Or nil if the default method is suitable)
	timer_device_get_properties_proc devicegetproperties; // A device specific DeviceGetProperties method implementing a standard timer device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t readcount;
	uint32_t waitcount;
	uint32_t eventcount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	void *address; // Device register base address
	uint32_t rate; // Device rate (Hz)
	uint32_t interval; // Device interval (Ticks)
	TIMER_PROPERTIES properties; // Device properties
	// Event Properties
	uint32_t flags; // Event flags for this timer (eg TIMER_EVENT_FLAG_REPEAT)
	uint32_t count; // Count of threads and events waiting for this timer
	EVENT_HANDLE event; // Event for threads waiting for this timer
	TIMER_WAITER *waiters; // List of events waiting for this timer
	// Internal Properties
	TIMER_DEVICE *prev; // Previous entry in Timer device table
	TIMER_DEVICE *next; // Next entry in Timer device table
};

/* ============================================================================== */
/* Random specific types */
typedef struct _RANDOM_DEVICE RANDOM_DEVICE;

/* Random Enumeration Callback */
typedef uint32_t STDCALL (*random_enumerate_cb)(RANDOM_DEVICE *random, void *data);
/* Random Notification Callback */
typedef uint32_t STDCALL (*random_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Random Device Methods */
typedef uint32_t STDCALL (*random_device_start_proc)(RANDOM_DEVICE *random);
typedef uint32_t STDCALL (*random_device_stop_proc)(RANDOM_DEVICE *random);
typedef uint32_t STDCALL (*random_device_seed_proc)(RANDOM_DEVICE *random, uint32_t seed);
typedef uint8_t STDCALL (*random_device_read_byte_proc)(RANDOM_DEVICE *random);
typedef uint16_t STDCALL (*random_device_read_word_proc)(RANDOM_DEVICE *random);
typedef uint32_t STDCALL (*random_device_read_longword_proc)(RANDOM_DEVICE *random);
typedef int64_t STDCALL (*random_device_read_long_long_proc)(RANDOM_DEVICE *random);
typedef double_t STDCALL (*random_device_read_double_proc)(RANDOM_DEVICE *random);

/* Random Device */
struct _RANDOM_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Random device
	// Random Properties
	uint32_t randomid; // Unique Id of this Random device in the Random device table
	uint32_t randomstate; // Random device state (eg RANDOM_STATE_ENABLED)
	random_device_start_proc devicestart; // A device specific DeviceStart method implementing a standard random device interface (Mandatory)
	random_device_stop_proc devicestop; // A device specific DeviceStop method implementing a standard random device interface (Or nil if the default method is suitable)
	random_device_seed_proc deviceseed; // A device specific DeviceSeed method implementing a standard random device interface (Or nil if the default method is suitable)
	random_device_read_byte_proc devicereadbyte; // A device specific DeviceReadByte method implementing a standard random device interface (Or nil if the default method is suitable)
	random_device_read_word_proc devicereadword; // A device specific DeviceReadWord method implementing a standard random device interface (Or nil if the default method is suitable)
	random_device_read_longword_proc devicereadlongword; // A device specific DeviceReadLongWord method implementing a standard random device interface (Mandatory)
	random_device_read_long_long_proc devicereadquadword; // A device specific DeviceReadQuadWord method implementing a standard random device interface (Or nil if the default method is suitable)
	random_device_read_double_proc devicereaddouble; // A device specific DeviceReadFloat method implementing a standard random device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t seedcount;
	uint32_t readcount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	void *address; // Device register base address
	// Internal Properties
	RANDOM_DEVICE *prev; // Previous entry in Random device table
	RANDOM_DEVICE *next; // Next entry in Random device table
};

/* ============================================================================== */
/* Mailbox specific types */
typedef struct _MAILBOX_DEVICE MAILBOX_DEVICE;

/* Mailbox Enumeration Callback */
typedef uint32_t STDCALL (*mailbox_enumerate_cb)(MAILBOX_DEVICE *mailbox, void *data);
/* Mailbox Notification Callback */
typedef uint32_t STDCALL (*mailbox_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Mailbox Device Methods */
typedef uint32_t STDCALL (*mailbox_device_start_proc)(MAILBOX_DEVICE *mailbox);
typedef uint32_t STDCALL (*mailbox_device_stop_proc)(MAILBOX_DEVICE *mailbox);
typedef uint32_t STDCALL (*mailbox_device_receive_proc)(MAILBOX_DEVICE *mailbox, uint32_t channel);
typedef uint32_t STDCALL (*mailbox_device_send_proc)(MAILBOX_DEVICE *mailbox, uint32_t channel, uint32_t data);
typedef uint32_t STDCALL (*mailbox_device_call_proc)(MAILBOX_DEVICE *mailbox, uint32_t channel, uint32_t data, uint32_t *response);
typedef uint32_t STDCALL (*mailbox_device_get_timeout_proc)(MAILBOX_DEVICE *mailbox);
typedef uint32_t STDCALL (*mailbox_device_set_timeout_proc)(MAILBOX_DEVICE *mailbox, uint32_t timeout);

/* Mailbox Device */
struct _MAILBOX_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Mailbox device
	// Mailbox Properties
	uint32_t mailboxid; // Unique Id of this Mailbox device in the Mailbox device table
	uint32_t mailboxstate; // Mailbox device state (eg MAILBOX_STATE_ENABLED)
	mailbox_device_start_proc devicestart; // A device specific DeviceStart method implementing a standard mailbox device interface (Or nil if the default method is suitable)
	mailbox_device_stop_proc devicestop; // A device specific DeviceStop method implementing a standard mailbox device interface (Or nil if the default method is suitable)
	mailbox_device_receive_proc devicereceive; // A device specific DeviceReceive method implementing a standard mailbox device interface (Mandatory)
	mailbox_device_send_proc devicesend; // A device specific DeviceSend method implementing a standard mailbox device interface (Mandatory)
	mailbox_device_call_proc devicecall; // A device specific DeviceCall method implementing a standard mailbox device interface (Mandatory)
	mailbox_device_get_timeout_proc devicegettimeout; // A device specific DeviceGetTimeout method implementing a standard mailbox device interface (Or nil if the default method is suitable)
	mailbox_device_set_timeout_proc devicesettimeout; // A device specific DeviceSetTimeout method implementing a standard mailbox device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t receivecount;
	uint32_t sendcount;
	uint32_t callcount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	void *address; // Device register base address
	uint32_t timeout; // Device timeout (Milliseconds)
	// Internal Properties
	MAILBOX_DEVICE *prev; // Previous entry in Mailbox device table
	MAILBOX_DEVICE *next; // Next entry in Mailbox device table
};

/* ============================================================================== */
/* Watchdog specific types */
typedef struct _WATCHDOG_DEVICE WATCHDOG_DEVICE;

/* Watchdog Enumeration Callback */
typedef uint32_t STDCALL (*watchdog_enumerate_cb)(WATCHDOG_DEVICE *watchdog, void *data);
/* Watchdog Notification Callback */
typedef uint32_t STDCALL (*watchdog_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Watchdog Device Methods */
typedef uint32_t STDCALL (*watchdog_device_start_proc)(WATCHDOG_DEVICE *watchdog);
typedef uint32_t STDCALL (*watchdog_device_stop_proc)(WATCHDOG_DEVICE *watchdog);
typedef uint32_t STDCALL (*watchdog_device_refresh_proc)(WATCHDOG_DEVICE *watchdog);
typedef uint32_t STDCALL (*watchdog_device_get_remain_proc)(WATCHDOG_DEVICE *watchdog);
typedef uint32_t STDCALL (*watchdog_device_get_timeout_proc)(WATCHDOG_DEVICE *watchdog);
typedef uint32_t STDCALL (*watchdog_device_set_timeout_proc)(WATCHDOG_DEVICE *watchdog, uint32_t timeout);

/* Watchdog Device */
struct _WATCHDOG_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Watchdog device
	// Watchdog Properties
	uint32_t watchdogid; // Unique Id of this Watchdog device in the Watchdog device table
	uint32_t watchdogstate; // Watchdog device state (eg WATCHDOG_STATE_ENABLED)
	watchdog_device_start_proc devicestart; // A device specific DeviceStart method implementing a standard watchdog device interface (Mandatory)
	watchdog_device_stop_proc devicestop; // A device specific DeviceStop method implementing a standard watchdog device interface (Mandatory)
	watchdog_device_refresh_proc devicerefresh; // A device specific DeviceRefresh method implementing a standard watchdog device interface (Mandatory)
	watchdog_device_get_remain_proc devicegetremain; // A device specific DeviceGetRemain method implementing a standard watchdog device interface (Mandatory)
	watchdog_device_get_timeout_proc devicegettimeout; // A device specific DeviceGetTimeout method implementing a standard watchdog device interface (Or nil if the default method is suitable)
	watchdog_device_set_timeout_proc devicesettimeout; // A device specific DeviceSetTimeout method implementing a standard watchdog device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t startcount;
	uint32_t stopcount;
	uint32_t refreshcount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	void *address; // Device register base address
	uint32_t timeout; // Device timeout (Milliseconds)
	// Internal Properties
	WATCHDOG_DEVICE *prev; // Previous entry in Watchdog device table
	WATCHDOG_DEVICE *next; // Next entry in Watchdog device table
};

/* ============================================================================== */
/* Device Functions */
DEVICE * STDCALL device_create(void);
DEVICE * STDCALL device_create_ex(uint32_t size);
uint32_t STDCALL device_destroy(DEVICE *device);

uint32_t STDCALL device_get_name(DEVICE *device, char *name, uint32_t len);
uint32_t STDCALL device_set_name(DEVICE *device, char *name);

uint32_t STDCALL device_get_description(DEVICE *device, char *name, uint32_t len);
uint32_t STDCALL device_set_description(DEVICE *device, char *description);

uint32_t STDCALL device_register(DEVICE *device);
uint32_t STDCALL device_deregister(DEVICE *device);

DEVICE * STDCALL device_find(uint32_t deviceclass, uint32_t deviceid);
DEVICE * STDCALL device_find_by_device_data(void *devicedata);
DEVICE * STDCALL device_find_by_name(char *name);
DEVICE * STDCALL device_find_by_name_ex(uint32_t deviceclass, char *name);
DEVICE * STDCALL device_find_by_description(char *description);
DEVICE * STDCALL device_find_by_description_ex(uint32_t deviceclass, char *description);
uint32_t STDCALL device_enumerate(uint32_t deviceclass, device_enumerate_cb callback, void *data);

uint32_t STDCALL device_notification(DEVICE *device, uint32_t deviceclass, device_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

BOOL STDCALL device_firmware_create(uint32_t deviceclass, char *name, void *buffer, uint32_t size);

HANDLE STDCALL device_firmware_register(uint32_t deviceclass, char *name, device_firmware_handler handler);
uint32_t STDCALL device_firmware_deregister(HANDLE handle);

DEVICE_FIRMWARE * STDCALL device_firmware_find(uint32_t deviceclass, char *name);
DEVICE_FIRMWARE * STDCALL device_firmware_find_by_handle(HANDLE handle);

uint32_t STDCALL device_firmware_open(uint32_t deviceclass, char *name, uint32_t timeout, HANDLE *handle);
uint32_t STDCALL device_firmware_close(HANDLE handle);

int32_t STDCALL device_firmware_size(HANDLE handle);
int32_t STDCALL device_firmware_seek(HANDLE handle, int32_t position);
int32_t STDCALL device_firmware_read(HANDLE handle, void *buffer, int32_t count);

uint32_t STDCALL device_firmware_acquire(uint32_t deviceclass, char *name, uint32_t timeout, HANDLE *handle, void *buffer, uint32_t *size);
uint32_t STDCALL device_firmware_release(HANDLE handle, void *buffer, uint32_t size);

NOTIFIER * STDCALL notifier_allocate(DEVICE *device, uint32_t deviceclass, device_notification_cb callback, void *data, uint32_t notification, uint32_t flags);
uint32_t STDCALL notifier_release(NOTIFIER *notifier);

NOTIFIER * STDCALL notifier_find(DEVICE *device, uint32_t deviceclass, device_notification_cb callback, void *data);
uint32_t STDCALL notifier_notify(DEVICE *device, uint32_t notification);

void STDCALL notifier_retry(NOTIFIER_RETRY *retry);
void STDCALL notifier_worker(NOTIFIER_TASK *task);

/* ============================================================================== */
/* Driver Functions */
DRIVER * STDCALL driver_create(void);
DRIVER * STDCALL driver_create_ex(uint32_t size);
uint32_t STDCALL driver_destroy(DRIVER *driver);

uint32_t STDCALL driver_get_name(DRIVER *driver, char *name, uint32_t len);
uint32_t STDCALL driver_set_name(DRIVER *driver, char *name);

uint32_t STDCALL driver_register(DRIVER *driver);
uint32_t STDCALL driver_deregister(DRIVER *driver);

DRIVER * STDCALL driver_find(uint32_t driverclass, uint32_t driverid);
DRIVER * STDCALL driver_find_by_name(char *name);
uint32_t STDCALL driver_enumerate(uint32_t driverclass, driver_enumerate_cb callback, void *data);

/* ============================================================================== */
/* Clock Device Functions */
uint32_t STDCALL clock_device_start(CLOCK_DEVICE *clock);
uint32_t STDCALL clock_device_stop(CLOCK_DEVICE *clock);

uint32_t STDCALL clock_device_read(CLOCK_DEVICE *clock);
int64_t STDCALL clock_device_read64(CLOCK_DEVICE *clock);
uint32_t STDCALL clock_device_write64(CLOCK_DEVICE *clock, int64_t value);

uint32_t STDCALL clock_device_get_rate(CLOCK_DEVICE *clock);
uint32_t STDCALL clock_device_set_rate(CLOCK_DEVICE *clock, uint32_t rate);

uint32_t STDCALL clock_device_properties(CLOCK_DEVICE *clock, CLOCK_PROPERTIES *properties);
uint32_t STDCALL clock_device_get_properties(CLOCK_DEVICE *clock, CLOCK_PROPERTIES *properties);

CLOCK_DEVICE * STDCALL clock_device_create(void);
CLOCK_DEVICE * STDCALL clock_device_create_ex(uint32_t size);
uint32_t STDCALL clock_device_destroy(CLOCK_DEVICE *clock);

uint32_t STDCALL clock_device_register(CLOCK_DEVICE *clock);
uint32_t STDCALL clock_device_deregister(CLOCK_DEVICE *clock);

CLOCK_DEVICE * STDCALL clock_device_find(uint32_t clockid);
CLOCK_DEVICE * STDCALL clock_device_find_by_name(char *name);
CLOCK_DEVICE * STDCALL clock_device_find_by_description(char *description);
uint32_t STDCALL clock_device_enumerate(clock_enumerate_cb callback, void *data);

uint32_t STDCALL clock_device_notification(CLOCK_DEVICE *clock, clock_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Timer Device Functions */
uint32_t STDCALL timer_device_start(TIMER_DEVICE *timer);
uint32_t STDCALL timer_device_stop(TIMER_DEVICE *timer);
uint32_t STDCALL timer_device_read(TIMER_DEVICE *timer);
int64_t STDCALL timer_device_read64(TIMER_DEVICE *timer);
uint32_t STDCALL timer_device_wait(TIMER_DEVICE *timer);
uint32_t STDCALL timer_device_event(TIMER_DEVICE *timer, uint32_t flags, timer_cb callback, void *data);
uint32_t STDCALL timer_device_cancel(TIMER_DEVICE *timer);
uint32_t STDCALL timer_device_get_rate(TIMER_DEVICE *timer);
uint32_t STDCALL timer_device_set_rate(TIMER_DEVICE *timer, uint32_t rate);
uint32_t STDCALL timer_device_get_interval(TIMER_DEVICE *timer);
uint32_t STDCALL timer_device_set_interval(TIMER_DEVICE *timer, uint32_t interval);

uint32_t STDCALL timer_device_properties(TIMER_DEVICE *timer, TIMER_PROPERTIES *properties);
uint32_t STDCALL timer_device_get_properties(TIMER_DEVICE *timer, TIMER_PROPERTIES *properties);

TIMER_DEVICE * STDCALL timer_device_create(void);
TIMER_DEVICE * STDCALL timer_device_create_ex(uint32_t size);
uint32_t STDCALL timer_device_destroy(TIMER_DEVICE *timer);

uint32_t STDCALL timer_device_register(TIMER_DEVICE *timer);
uint32_t STDCALL timer_device_deregister(TIMER_DEVICE *timer);

TIMER_DEVICE * STDCALL timer_device_find(uint32_t timerid);
TIMER_DEVICE * STDCALL timer_device_find_by_name(char *name);
TIMER_DEVICE * STDCALL timer_device_find_by_description(char *description);
uint32_t STDCALL timer_device_enumerate(timer_enumerate_cb callback, void *data);

uint32_t STDCALL timer_device_notification(TIMER_DEVICE *timer, timer_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Random Device Functions */
uint32_t STDCALL random_device_start(RANDOM_DEVICE *random);
uint32_t STDCALL random_device_stop(RANDOM_DEVICE *random);

uint32_t STDCALL random_device_seed(RANDOM_DEVICE *random, uint32_t seed);
uint8_t STDCALL random_device_read_byte(RANDOM_DEVICE *random);
uint16_t STDCALL random_device_read_word(RANDOM_DEVICE *random);
uint32_t STDCALL random_device_read_long_word(RANDOM_DEVICE *random);
int64_t STDCALL random_device_read_quad_word(RANDOM_DEVICE *random);
double_t STDCALL random_device_read_double(RANDOM_DEVICE *random);
double_t STDCALL random_device_read_extended(RANDOM_DEVICE *random);

RANDOM_DEVICE * STDCALL random_device_create(void);
RANDOM_DEVICE * STDCALL random_device_create_ex(uint32_t size);
uint32_t STDCALL random_device_destroy(RANDOM_DEVICE *random);

uint32_t STDCALL random_device_register(RANDOM_DEVICE *random);
uint32_t STDCALL random_device_deregister(RANDOM_DEVICE *random);

RANDOM_DEVICE * STDCALL random_device_find(uint32_t randomid);
RANDOM_DEVICE * STDCALL random_device_find_by_name(char *name);
RANDOM_DEVICE * STDCALL random_device_find_by_description(char *description);
uint32_t STDCALL random_device_enumerate(random_enumerate_cb callback, void *data);

uint32_t STDCALL random_device_notification(RANDOM_DEVICE *random, random_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Mailbox Device Functions */
uint32_t STDCALL mailbox_device_start(MAILBOX_DEVICE *mailbox);
uint32_t STDCALL mailbox_device_stop(MAILBOX_DEVICE *mailbox);
uint32_t STDCALL mailbox_device_receive(MAILBOX_DEVICE *mailbox, uint32_t channel);
uint32_t STDCALL mailbox_device_send(MAILBOX_DEVICE *mailbox, uint32_t channel, uint32_t data);
uint32_t STDCALL mailbox_device_call(MAILBOX_DEVICE *mailbox, uint32_t channel, uint32_t data, uint32_t *response);
uint32_t STDCALL mailbox_device_get_timeout(MAILBOX_DEVICE *mailbox);
uint32_t STDCALL mailbox_device_set_timeout(MAILBOX_DEVICE *mailbox, uint32_t timeout);

MAILBOX_DEVICE * STDCALL mailbox_device_create(void);
MAILBOX_DEVICE * STDCALL mailbox_device_create_ex(uint32_t size);
uint32_t STDCALL mailbox_device_destroy(MAILBOX_DEVICE *mailbox);

uint32_t STDCALL mailbox_device_register(MAILBOX_DEVICE *mailbox);
uint32_t STDCALL mailbox_device_deregister(MAILBOX_DEVICE *mailbox);

MAILBOX_DEVICE * STDCALL mailbox_device_find(uint32_t mailboxid);
MAILBOX_DEVICE * STDCALL mailbox_device_find_by_name(char *name);
MAILBOX_DEVICE * STDCALL mailbox_device_find_by_description(char *description);
uint32_t STDCALL mailbox_device_enumerate(mailbox_enumerate_cb callback, void *data);

uint32_t STDCALL mailbox_device_notification(MAILBOX_DEVICE *mailbox, mailbox_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Watchdog Device Functions */
uint32_t STDCALL watchdog_device_start(WATCHDOG_DEVICE *watchdog);
uint32_t STDCALL watchdog_device_stop(WATCHDOG_DEVICE *watchdog);
uint32_t STDCALL watchdog_device_refresh(WATCHDOG_DEVICE *watchdog);

uint32_t STDCALL watchdog_device_get_remain(WATCHDOG_DEVICE *watchdog);
uint32_t STDCALL watchdog_device_get_timeout(WATCHDOG_DEVICE *watchdog);
uint32_t STDCALL watchdog_device_set_timeout(WATCHDOG_DEVICE *watchdog, uint32_t timeout);

WATCHDOG_DEVICE * STDCALL watchdog_device_create(void);
WATCHDOG_DEVICE * STDCALL watchdog_device_create_ex(uint32_t size);
uint32_t STDCALL watchdog_device_destroy(WATCHDOG_DEVICE *watchdog);

uint32_t STDCALL watchdog_device_register(WATCHDOG_DEVICE *watchdog);
uint32_t STDCALL watchdog_device_deregister(WATCHDOG_DEVICE *watchdog);

WATCHDOG_DEVICE * STDCALL watchdog_device_find(uint32_t watchdogid);
WATCHDOG_DEVICE * STDCALL watchdog_device_find_by_name(char *name);
WATCHDOG_DEVICE * STDCALL watchdog_device_find_by_description(char *description);
uint32_t STDCALL watchdog_device_enumerate(watchdog_enumerate_cb callback, void *data);

uint32_t STDCALL watchdog_device_notification(WATCHDOG_DEVICE *watchdog, watchdog_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Device Helper Functions */
uint32_t STDCALL device_get_count(void);

DEVICE * STDCALL device_check(DEVICE *device);

uint32_t STDCALL notifier_get_count(void);

NOTIFIER * STDCALL notifier_check(NOTIFIER *notifier);

uint32_t STDCALL device_bus_to_string(uint32_t devicebus, char *string, uint32_t len);
uint32_t STDCALL device_state_to_string(uint32_t devicestate, char *string, uint32_t len);
uint32_t STDCALL device_class_to_string(uint32_t deviceclass, char *string, uint32_t len);

uint32_t STDCALL notification_to_string(uint32_t notification, char *string, uint32_t len);

/* ============================================================================== */
/* Driver Helper Functions */
uint32_t STDCALL driver_get_count(void);

DRIVER * STDCALL driver_check(DRIVER *driver);

uint32_t STDCALL driver_state_to_string(uint32_t driverstate, char *string, uint32_t len);
uint32_t STDCALL driver_class_to_string(uint32_t driverclass, char *string, uint32_t len);

/* ============================================================================== */
/* Clock Device Helper Functions */
uint32_t STDCALL clock_device_get_count(void);
CLOCK_DEVICE * STDCALL clock_device_get_default(void);
uint32_t STDCALL clock_device_set_default(CLOCK_DEVICE *clock);

CLOCK_DEVICE * STDCALL clock_device_check(CLOCK_DEVICE *clock);

uint32_t STDCALL clock_type_to_string(uint32_t clocktype, char *string, uint32_t len);
uint32_t STDCALL clock_state_to_string(uint32_t clockstate, char *string, uint32_t len);

/* ============================================================================== */
/* Timer Device Helper Functions */
uint32_t STDCALL timer_device_get_count(void);
TIMER_DEVICE * STDCALL timer_device_get_default(void);
uint32_t STDCALL timer_device_set_default(TIMER_DEVICE *timer);

TIMER_DEVICE * STDCALL timer_device_check(TIMER_DEVICE *timer);

uint32_t STDCALL timer_type_to_string(uint32_t timertype, char *string, uint32_t len);
uint32_t STDCALL timer_state_to_string(uint32_t timerstate, char *string, uint32_t len);

TIMER_WAITER * STDCALL timer_device_create_waiter(TIMER_DEVICE *timer, timer_cb callback, void *data);
uint32_t STDCALL timer_device_destroy_waiter(TIMER_DEVICE *timer, TIMER_WAITER *waiter);

uint32_t STDCALL timer_device_register_waiter(TIMER_DEVICE *timer, TIMER_WAITER *waiter);
uint32_t STDCALL timer_device_deregister_waiter(TIMER_DEVICE *timer, TIMER_WAITER *waiter);

/* ============================================================================== */
/* Random Device Helper Functions */
uint32_t STDCALL random_device_get_count(void);
RANDOM_DEVICE * STDCALL random_device_get_default(void);
uint32_t STDCALL random_device_set_default(RANDOM_DEVICE *random);

RANDOM_DEVICE * STDCALL random_device_check(RANDOM_DEVICE *random);

uint32_t STDCALL random_type_to_string(uint32_t randomtype, char *string, uint32_t len);
uint32_t STDCALL random_state_to_string(uint32_t randomstate, char *string, uint32_t len);

/* ============================================================================== */
/* Mailbox Device Helper Functions */
uint32_t STDCALL mailbox_device_get_count(void);
MAILBOX_DEVICE * STDCALL mailbox_device_get_default(void);
uint32_t STDCALL mailbox_device_set_default(MAILBOX_DEVICE *mailbox);

MAILBOX_DEVICE * STDCALL mailbox_device_check(MAILBOX_DEVICE *mailbox);

uint32_t STDCALL mailbox_type_to_string(uint32_t mailboxtype, char *string, uint32_t len);
uint32_t STDCALL mailbox_state_to_string(uint32_t mailboxstate, char *string, uint32_t len);

/* ============================================================================== */
/* Watchdog Device Helper Functions */
uint32_t STDCALL watchdog_device_get_count(void);
WATCHDOG_DEVICE * STDCALL watchdog_device_get_default(void);
uint32_t STDCALL watchdog_device_set_default(WATCHDOG_DEVICE *watchdog);

WATCHDOG_DEVICE * STDCALL watchdog_device_check(WATCHDOG_DEVICE *watchdog);

uint32_t STDCALL watchdog_type_to_string(uint32_t watchdogtype, char *string, uint32_t len);
uint32_t STDCALL watchdog_state_to_string(uint32_t watchdogstate, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_DEVICE_H