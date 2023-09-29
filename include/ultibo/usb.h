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
#ifndef _ULTIBO_USB_H
#define _ULTIBO_USB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/system.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* USB Device, Driver and Host specific constants */
#define USB_DEVICE_PREFIX	"USB" // Name prefix for USB Devices
#define USB_DRIVER_PREFIX	"USB" // Name prefix for USB Drivers
#define USB_HOST_PREFIX	"USBHost" // Name prefix for USB Hosts

/* USB Device Types */
#define USB_TYPE_NONE	0

#define USB_TYPE_MAX	0

/* USB Device States */
#define USB_STATE_DETACHED	0
#define USB_STATE_DETACHING	1
#define USB_STATE_ATTACHING	2
#define USB_STATE_ATTACHED	3

#define USB_STATE_MAX	3

/* USB Device Status */
#define USB_STATUS_UNBOUND	0
#define USB_STATUS_BOUND	1

#define USB_STATUS_MAX	1

/* USB Device Flags */
#define USB_FLAG_NONE	0x00000000

/* USB Host Types */
#define USBHOST_TYPE_NONE	0
#define USBHOST_TYPE_EHCI	1
#define USBHOST_TYPE_OHCI	2
#define USBHOST_TYPE_UHCI	3
#define USBHOST_TYPE_XHCI	4
#define USBHOST_TYPE_DWCOTG	5

#define USBHOST_TYPE_MAX	5

/* USB Host States */
#define USBHOST_STATE_DISABLED	0
#define USBHOST_STATE_ENABLED	1

#define USBHOST_STATE_MAX	1

/* USB Host Flags */
#define USBHOST_FLAG_NONE	0x00000000
#define USBHOST_FLAG_SHARED	0x00000001
#define USBHOST_FLAG_NOCACHE	0x00000002

/* USB Status Codes */
#define USB_STATUS_SUCCESS	0 // Function successful
#define USB_STATUS_DEVICE_DETACHED	1 // USB device was detached
#define USB_STATUS_DEVICE_UNSUPPORTED	2 // USB device is unsupported by the driver
#define USB_STATUS_HARDWARE_ERROR	3 // Hardware error of some form occurred
#define USB_STATUS_INVALID_DATA	4 // Invalid data was received
#define USB_STATUS_INVALID_PARAMETER	5 // An invalid parameter was passed to the function
#define USB_STATUS_NOT_PROCESSED	6 // The USB request has been submitted but not yet processed
#define USB_STATUS_OUT_OF_MEMORY	7 // Failed to allocate memory
#define USB_STATUS_TIMEOUT	8 // The operation timed out
#define USB_STATUS_UNSUPPORTED_REQUEST	9 // The request is unsupported
#define USB_STATUS_HARDWARE_STALL	10 // The device reported an endpoint STALL
#define USB_STATUS_OPERATION_FAILED	11 // The operation was not able to be completed
#define USB_STATUS_NOT_BOUND	12 // USB device is not bound to a driver
#define USB_STATUS_ALREADY_BOUND	13 // USB device is already bound to a driver
#define USB_STATUS_NOT_READY	14 // USB device is not in a ready state
#define USB_STATUS_NOT_COMPLETED	15 // The USB request has been scheduled but not yet completed
#define USB_STATUS_CANCELLED	16 // The USB request was cancelled
#define USB_STATUS_NOT_VALID	17 // The USB request is not valid

/* USB Request Flags */
#define USB_REQUEST_FLAG_NONE	0x00000000
#define USB_REQUEST_FLAG_ALLOCATED	0x00000001 // Request data has been allocated by USBBufferAllocate (and can be freed by USBBufferRelease)
#define USB_REQUEST_FLAG_COMPATIBLE	0x00000002 // Request data is compatible with DMA requirements of host configuration (Can be passed directly to DMA)
#define USB_REQUEST_FLAG_ALIGNED	0x00000004 // Request data is aligned according to host configuration
#define USB_REQUEST_FLAG_SIZED	0x00000008 // Request data is sized according to host configuration
#define USB_REQUEST_FLAG_SHARED	0x00000010 // Request data has been allocated from Shared memory
#define USB_REQUEST_FLAG_NOCACHE	0x00000020 // Request data has been allocated from Non Cached memory

/* USB Control Phases */
#define USB_CONTROL_PHASE_SETUP	0 // Setup phase of a Control request (Using SetupData)
#define USB_CONTROL_PHASE_DATA	1 // Data phase of a Control request (Using Data buffer)
#define USB_CONTROL_PHASE_STATUS	2 // Status phase of a Control request (Using StatusData)

/* USB Control Timeouts */
#define USB_CONTROL_GET_TIMEOUT	5000
#define USB_CONTROL_SET_TIMEOUT	5000

/* Default maximum packet size for unconfigured Endpoints */
#define USB_DEFAULT_MAX_PACKET_SIZE	8
#define USB_ALTERNATE_MAX_PACKET_SIZE	64

/* Maximum packet size of any USB Endpoint  (1024 is the maximum allowed by USB 2.0) */
#define USB_MAX_PACKET_SIZE	1024

/* Number of USB frames per millisecond */
#define USB_FRAMES_PER_MS	1

/* Number of USB microframes per millisecond */
#define USB_UFRAMES_PER_MS	8

/* Values for bmAttributes in type TUSBConfigurationDescriptor */
#define USB_CONFIGURATION_ATTRIBUTE_RESERVED_HIGH	0x80
#define USB_CONFIGURATION_ATTRIBUTE_SELF_POWERED	0x40
#define USB_CONFIGURATION_ATTRIBUTE_REMOTE_WAKEUP	0x20
#define USB_CONFIGURATION_ATTRIBUTE_RESERVED_LOW	0x1f

/* Values for wStatus in type TUSBDeviceStatus (Device Recipient) (See Figure 9-4 of Section 9.4 of the USB 2.0 specification) */
#define USB_DEVICE_STATUS_SELF_POWERED	(1 << 0)
#define USB_DEVICE_STATUS_REMOTE_WAKEUP	(1 << 1)

/* Values for vStatus in type TUSBDeviceStatus (Endpoint Recipient) (See Figure 9-6 of Section 9.4 of the USB 2.0 specification) */
#define USB_ENDPOINT_STATUS_HALT	(1 << 0)

/* USB Device Speeds */
#define USB_SPEED_HIGH	0 // 480 Mb/s
#define USB_SPEED_FULL	1 // 12 Mb/s
#define USB_SPEED_LOW	2 // 1.5 Mb/s
#define USB_SPEED_SUPER	3 // 5 Gb/s
#define USB_SPEED_SUPERPLUS	4 // 10 Gb/s

/* Values for bmAttributes (bits 1..0) in type TUSBEndpointDescriptor */
/* USB Transfer Types */
#define USB_TRANSFER_TYPE_CONTROL	0
#define USB_TRANSFER_TYPE_ISOCHRONOUS	1
#define USB_TRANSFER_TYPE_BULK	2
#define USB_TRANSFER_TYPE_INTERRUPT	3
#define USB_TRANSFER_TYPE_MASK	0x03

/* USB Transfer Sizes */
#define USB_TRANSFER_SIZE_8_BIT	0
#define USB_TRANSFER_SIZE_16_BIT	1
#define USB_TRANSFER_SIZE_32_BIT	2
#define USB_TRANSFER_SIZE_64_BIT	3

/* Values for bDescriptorType in types TUSBDescriptorHeader and TUSBDeviceDescriptor */
/* USB Descriptor Types (See Table 9-5 in Section 9.4 of the USB 2.0 specification) */
#define USB_DESCRIPTOR_TYPE_DEVICE	1
#define USB_DESCRIPTOR_TYPE_CONFIGURATION	2
#define USB_DESCRIPTOR_TYPE_STRING	3
#define USB_DESCRIPTOR_TYPE_INTERFACE	4
#define USB_DESCRIPTOR_TYPE_ENDPOINT	5
#define USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER	6
#define USB_DESCRIPTOR_TYPE_OTHER_SPEED_CONFIGURATION	7
#define USB_DESCRIPTOR_TYPE_INTERFACE_POWER	8
#define USB_DESCRIPTOR_TYPE_CLASS_DEVICE	0x21 // (USB_REQUEST_TYPE_CLASS << 5) | USB_DESCRIPTOR_TYPE_DEVICE
#define USB_DESCRIPTOR_TYPE_CLASS_CONFIGURATION	0x22 // (USB_REQUEST_TYPE_CLASS << 5) | USB_DESCRIPTOR_TYPE_CONFIGURATION
#define USB_DESCRIPTOR_TYPE_CLASS_STRING	0x23 // (USB_REQUEST_TYPE_CLASS << 5) | USB_DESCRIPTOR_TYPE_STRING
#define USB_DESCRIPTOR_TYPE_CLASS_INTERFACE	0x24 // (USB_REQUEST_TYPE_CLASS << 5) | USB_DESCRIPTOR_TYPE_INTERFACE
#define USB_DESCRIPTOR_TYPE_CLASS_ENDPOINT	0x25 // (USB_REQUEST_TYPE_CLASS << 5) | USB_DESCRIPTOR_TYPE_ENDPOINT
#define USB_DESCRIPTOR_TYPE_HUB	0x29

/* Values for bmRequestType (bit 7) in type TUSBControlSetupData (See Table 9-2 of Section 9.3 of the USB 2.0 specification) */
/* USB Transfer Directions (Relative to the host) */
#define USB_DIRECTION_OUT	0 // Host to Device
#define USB_DIRECTION_IN	1 // Device to Host

/* USB Request Types (bits 6..5 of bmRequestType in type TUSBControlSetupData) (See Table 9-2 of Section 9.3 of the USB 2.0 specification) */
#define USB_REQUEST_TYPE_STANDARD	0
#define USB_REQUEST_TYPE_CLASS	1
#define USB_REQUEST_TYPE_VENDOR	2
#define USB_REQUEST_TYPE_RESERVED	3

/* USB Request Recipients (bits 4..0 of bmRequestType in type TUSBControlSetupData) (See Table 9-2 of Section 9.3 of the USB 2.0 specification) */
#define USB_REQUEST_RECIPIENT_DEVICE	0
#define USB_REQUEST_RECIPIENT_INTERFACE	1
#define USB_REQUEST_RECIPIENT_ENDPOINT	2
#define USB_REQUEST_RECIPIENT_OTHER	3

/* Values of the bitfields within the bmRequestType member of TUSBControlSetupData (See Table 9-2 of Section 9.3 of the USB 2.0 specification) */
#define USB_BMREQUESTTYPE_DIR_OUT	(USB_DIRECTION_OUT << 7)
#define USB_BMREQUESTTYPE_DIR_IN	(USB_DIRECTION_IN << 7)
#define USB_BMREQUESTTYPE_DIR_MASK	(0x01 << 7)
#define USB_BMREQUESTTYPE_TYPE_STANDARD	(USB_REQUEST_TYPE_STANDARD << 5)
#define USB_BMREQUESTTYPE_TYPE_CLASS	(USB_REQUEST_TYPE_CLASS << 5)
#define USB_BMREQUESTTYPE_TYPE_VENDOR	(USB_REQUEST_TYPE_VENDOR << 5)
#define USB_BMREQUESTTYPE_TYPE_RESERVED	(USB_REQUEST_TYPE_RESERVED << 5)
#define USB_BMREQUESTTYPE_TYPE_MASK	(0x03 << 5)
#define USB_BMREQUESTTYPE_RECIPIENT_DEVICE	(USB_REQUEST_RECIPIENT_DEVICE << 0)
#define USB_BMREQUESTTYPE_RECIPIENT_INTERFACE	(USB_REQUEST_RECIPIENT_INTERFACE << 0)
#define USB_BMREQUESTTYPE_RECIPIENT_ENDPOINT	(USB_REQUEST_RECIPIENT_ENDPOINT << 0)
#define USB_BMREQUESTTYPE_RECIPIENT_OTHER	(USB_REQUEST_RECIPIENT_OTHER << 0)
#define USB_BMREQUESTTYPE_RECIPIENT_MASK	(0x1f << 0)

/* Values for bRequest in type TUSBControlSetupData */
/* USB Device Requests (See Table 9-3 in Section 9.4 of the USB 2.0 specification) */
#define USB_DEVICE_REQUEST_GET_STATUS	0
#define USB_DEVICE_REQUEST_CLEAR_FEATURE	1
#define USB_DEVICE_REQUEST_SET_FEATURE	3
#define USB_DEVICE_REQUEST_SET_ADDRESS	5
#define USB_DEVICE_REQUEST_GET_DESCRIPTOR	6
#define USB_DEVICE_REQUEST_SET_DESCRIPTOR	7
#define USB_DEVICE_REQUEST_GET_CONFIGURATION	8
#define USB_DEVICE_REQUEST_SET_CONFIGURATION	9
#define USB_DEVICE_REQUEST_GET_INTERFACE	10
#define USB_DEVICE_REQUEST_SET_INTERFACE	11
#define USB_DEVICE_REQUEST_SYNCH_FRAME	12

/* Values for wValue in type TUSBControlSetupData */
/* USB Device Features (See Table 9-6 in Section 9.4 of the USB 2.0 specification) */
#define USB_DEVICE_FEATURE_ENDPOINT_HALT	0 // Endpoint Only
#define USB_DEVICE_FEATURE_REMOTE_WAKEUP	1 // Device Only
#define USB_DEVICE_FEATURE_TEST_MODE	2 // Device Only

/* Values for wIndex in type TUSBControlSetupData */
/* USB Test Modes (See Table 9-7 in Section 9.4 of the USB 2.0 specification) */
#define USB_DEVICE_TEST_MODE_J	0x01
#define USB_DEVICE_TEST_MODE_K	0x02
#define USB_DEVICE_TEST_MODE_SE0_NAK	0x03
#define USB_DEVICE_TEST_MODE_PACKET	0x04
#define USB_DEVICE_TEST_MODE_FORCE_ENABLE	0x05

/* USB Packet ID values (See ????????) */
#define USB_PACKETID_UNDEF_0	0xf0
#define USB_PACKETID_OUT	0xe1
#define USB_PACKETID_ACK	0xd2
#define USB_PACKETID_DATA0	0xc3
#define USB_PACKETID_UNDEF_4	0xb4
#define USB_PACKETID_SOF	0xa5
#define USB_PACKETID_UNDEF_6	0x96
#define USB_PACKETID_UNDEF_7	0x87
#define USB_PACKETID_UNDEF_8	0x78
#define USB_PACKETID_IN	0x69
#define USB_PACKETID_NAK	0x5a
#define USB_PACKETID_DATA1	0x4b
#define USB_PACKETID_PREAMBLE	0x3c
#define USB_PACKETID_SETUP	0x2d
#define USB_PACKETID_STALL	0x1e
#define USB_PACKETID_UNDEF_F	0x0f

/* USB Class Codes (bDeviceClass / bInterfaceClass) (See: https://www.usb.org/defined-class-codes) (Note that only the hub class is defined in the USB 2.0 specification itself the other standard class codes are defined in additional specifications) */
#define USB_CLASS_CODE_INTERFACE_SPECIFIC	0x00 // Use class code info from Interface Descriptors 
#define USB_CLASS_CODE_AUDIO	0x01 // Audio device
#define USB_CLASS_CODE_COMMUNICATIONS_AND_CDC_CONTROL	0x02 // Communication device class
#define USB_CLASS_CODE_COMMS	USB_CLASS_CODE_COMMUNICATIONS_AND_CDC_CONTROL
#define USB_CLASS_CODE_HID	0x03 // HID device class
#define USB_CLASS_CODE_PHYSICAL	0x05 // Physical device class
#define USB_CLASS_CODE_IMAGE	0x06 // Still Imaging device
#define USB_CLASS_CODE_PRINTER	0x07 // Printer device
#define USB_CLASS_CODE_MASS_STORAGE	0x08 // Mass Storage device
#define USB_CLASS_CODE_HUB	0x09 // Hub Device
#define USB_CLASS_CODE_CDC_DATA	0x0a // CDC data device
#define USB_CLASS_CODE_SMART_CARD	0x0b // Smart Card device
#define USB_CLASS_CODE_CONTENT_SECURITY	0x0d // Content Security device
#define USB_CLASS_CODE_VIDEO	0x0e // Video device
#define USB_CLASS_CODE_PERSONAL_HEALTHCARE	0x0f // Personal Healthcare device
#define USB_CLASS_CODE_AUDIO_VIDEO	0x10 // Audio/Video Devices
#define USB_CLASS_CODE_BILLBOARD	0x11 // Billboard Device
#define USB_CLASS_CODE_DIAGNOSTIC	0xDC // Diagnostic Device
#define USB_CLASS_CODE_WIRELESS_CONTROLLER	0xe0 // Wireless Controller
#define USB_CLASS_CODE_MISCELLANEOUS	0xef // Miscellaneous
#define USB_CLASS_CODE_APPLICATION_SPECIFIC	0xfe // Application Specific
#define USB_CLASS_CODE_VENDOR_SPECIFIC	0xff // Vendor Specific

/* USB SubClass Codes (bDeviceSubClass/bInterfaceSubClass) (See: https://www.usb.org/defined-class-codes) */
/* Communications Devices */
#define USB_SUBCLASS_CDC_DLCM	0x01 // Direct Line Control Model (USBPSTN1.2)
#define USB_SUBCLASS_CDC_ACM	0x02 // Abstract Control Model (USBPSTN1.2)
#define USB_SUBCLASS_CDC_TCM	0x03 // Telephone Control Model (USBPSTN1.2)
#define USB_SUBCLASS_CDC_MCCM	0x04 // Multi-Channel Control Model (USBISDN1.2)
#define USB_SUBCLASS_CDC_CCM	0x05 // CAPI Control Model (USBISDN1.2)
#define USB_SUBCLASS_CDC_ETHERNET	0x06 // Ethernet Networking Control Model (USBECM1.2)
#define USB_SUBCLASS_CDC_WHCM	0x08 // Wireless Handset Control Model (USBWMC1.1)
#define USB_SUBCLASS_CDC_DMM	0x09 // Device Management Model (USBWMC1.1)
#define USB_SUBCLASS_CDC_MDLM	0x0a // Mobile Direct Line Model (USBWMC1.1)
#define USB_SUBCLASS_CDC_OBEX	0x0b // OBEX (USBWMC1.1)
#define USB_SUBCLASS_CDC_EEM	0x0c // Ethernet Emulation Model (USBEEM1.0)
#define USB_SUBCLASS_CDC_NCM	0x0d // Network Control Model (USBNCM1.0)
#define USB_SUBCLASS_CDC_MBIM	0x0e
/* Still Image Devices */
#define USB_SUBCLASS_IMAGE_DEFAULT	0x01
/* Mass Storage Devices */
#define USB_SUBCLASS_MASS_STORAGE_DEFAULT	0x00 // SCSI command set not reported, De facto use
#define USB_SUBCLASS_MASS_STORAGE_RBC	0x01 // Reduced Block Commands (RBC), INCITS 330:2000, available at http://www.t10.org
#define USB_SUBCLASS_MASS_STORAGE_MMC5	0x02 // Multi-Media Command Set 5 (MMC-5), T10/1675-D available at http://www.t10.org
#define USB_SUBCLASS_MASS_STORAGE_QIC157	0x03 // Obsolete was QIC-157
#define USB_SUBCLASS_MASS_STORAGE_UFI	0x04 // UFI Specifies how to interface Floppy Disk Drives to USB
#define USB_SUBCLASS_MASS_STORAGE_SFF8070I	0x05 // Obsolete Was SFF-8070i
#define USB_SUBCLASS_MASS_STORAGE_SCSI	0x06 // SCSI transparent command set
#define USB_SUBCLASS_MASS_STORAGE_LSDFS	0x07 // LSD FS 
#define USB_SUBCLASS_MASS_STORAGE_IEEE1667	0x08 // IEEE 1667 Standard Protocol for Authentication in Host Attachments of Transient Storage Devices (IEEE 1667) available at www.ieee1667.com
#define USB_SUBCLASS_MASS_STORAGE_VENDOR_SPECIFIC	0xff // Specific to device vendor, De facto use
/* Content Security Devices */
#define USB_SUBCLASS_CONTENT_SECURITY_DEFAULT	0x00
/* Audio/Video Devices */
#define USB_SUBCLASS_AUDIO_VIDEO_CONTROL	0x01 // Audio/Video Device – AVControl Interface
#define USB_SUBCLASS_AUDIO_VIDEO_DATA_VIDEO	0x02 // Audio/Video Device – AVData Video Streaming Interface
#define USB_SUBCLASS_AUDIO_VIDEO_DATA_AUDIO	0x03 // Audio/Video Device – AVData Audio Streaming Interface
/* Billboard Devices */
#define USB_SUBCLASS_BILLBOARD_DEFAULT	0x00
/* Diagnostic Device */
#define USB_SUBCLASS_DIAGNOSTIC_DEFAULT	0x01
/* Wireless Controller */
#define USB_SUBCLASS_WIRELESS_CONTROLLER_BLUETOOTH	0x01
#define USB_SUBCLASS_WIRELESS_CONTROLLER_USB	0x02
/* Miscellaneous */
#define USB_SUBCLASS_MISCELLANEOUS_SYNC	0x01
#define USB_SUBCLASS_MISCELLANEOUS_IAD_WAMP	0x02 // Interface Association Descriptor / Wire Adapter Multifunction Peripheral
#define USB_SUBCLASS_MISCELLANEOUS_CBAF	0x03 // Cable Based Association Framework
#define USB_SUBCLASS_MISCELLANEOUS_RNDIS	0x04
#define USB_SUBCLASS_MISCELLANEOUS_USB3VISION	0x05
/* Application Specific */
#define USB_SUBCLASS_APPLICATION_SPECIFIC_DFU	0x01
#define USB_SUBCLASS_APPLICATION_SPECIFIC_IRDA	0x02
#define USB_SUBCLASS_APPLICATION_SPECIFIC_TMC	0x02
/* Vendor Specific */
#define USB_SUBCLASS_VENDOR_SPECIFIC	0xff // Vendor Specific

/* USB Protocol Codes (bDeviceProtocol/bInterfaceProtocol) (See: https://www.usb.org/defined-class-codes) */
/* Communications Devices */
#define USB_PROTOCOL_CDC_ACM_NONE	0 // Abstract Control Model - No class specific protocol required
#define USB_PROTOCOL_CDC_ACM_AT_V25TER	1 // Abstract Control Model - AT Commands: V.250 etc
#define USB_PROTOCOL_CDC_ACM_AT_PCCA101	2 // Abstract Control Model - AT Commands defined by PCCA-101
#define USB_PROTOCOL_CDC_ACM_AT_PCCA101_WAKE	3 // Abstract Control Model - AT Commands defined by PCCA-101 & Annex O
#define USB_PROTOCOL_CDC_ACM_AT_GSM	4 // Abstract Control Model - AT Commands defined by GSM 07.07
#define USB_PROTOCOL_CDC_ACM_AT_3G	5 // Abstract Control Model - AT Commands defined by 3GPP 27.007
#define USB_PROTOCOL_CDC_ACM_AT_CDMA	6 // Abstract Control Model - AT Commands defined by TIA for CDMA
#define USB_PROTOCOL_CDC_ACM_VENDOR	0xff // Abstract Control Model - Vendor-specific
#define USB_PROTOCOL_CDC_EEM	7 // Ethernet Emulation Model
#define USB_PROTOCOL_CDC_NCM_NTB	1 // Network Control Model - Network Transfer Block
#define USB_PROTOCOL_CDC_MBIM_NTB	2 // Network Transfer Block
/* Still Image Devices */
#define USB_PROTOCOL_IMAGE_DEFAULT	0x01
/* Mass Storage Devices */
#define USB_PROTOCOL_MASS_STORAGE_CBI	0x00 // CBI (with command completion interrupt) USB Mass Storage Class Control/Bulk/Interrupt Transport
#define USB_PROTOCOL_MASS_STORAGE_CB	0x01 // CBI (with no command completion interrupt) USB Mass Storage Class Control/Bulk/Interrupt Transport
#define USB_PROTOCOL_MASS_STORAGE_BBB	0x50 // BBB USB Mass Storage Class Bulk-Only Transport 
#define USB_PROTOCOL_MASS_STORAGE_UAS	0x62 // UAS 
#define USB_PROTOCOL_MASS_STORAGE_VENDOR_SPECIFIC	0xff // Specific to device vendor, De facto use
/* Hub Devices */
#define USB_PROTOCOL_HUB_FULLSPEED	0x00 // Full speed Hub
#define USB_PROTOCOL_HUB_HIGHSPEED_SINGLE_TT	0x01 // Hi-speed hub with single Transaction Translator
#define USB_PROTOCOL_HUB_HIGHSPEED_MULTI_TT	0x02 // Hi-speed hub with multiple Transaction Translators
/* Content Security Devices */
#define USB_PROTOCOL_CONTENT_SECURITY_DEFAULT	0x00
/* Audio/Video Devices */
#define USB_PROTOCOL_AUDIO_VIDEO_DEFAULT	0x00
/* Billboard Devices */
#define USB_PROTOCOL_BILLBOARD_DEFAULT	0x00
/* Diagnostic Device */
#define USB_PROTOCOL_DIAGNOSTIC_DEFAULT	0x01
/* Wireless Controller */
#define USB_PROTOCOL_WIRELESS_CONTROLLER_BLUETOOTH	0x01 // See: http://www.bluetooth.com/
#define USB_PROTOCOL_WIRELESS_CONTROLLER_UWB	0x02 // See: Wireless USB Specification in Chapter 8
#define USB_PROTOCOL_WIRELESS_CONTROLLER_NDIS	0x03 // See: http://www.microsoft.com/windowsmobile/mobileoperators/default.mspx
#define USB_PROTOCOL_WIRELESS_CONTROLLER_BLUETOOTH_AMP	0x04 // See: http://www.bluetooth.com/
#define USB_PROTOCOL_WIRELESS_CONTROLLER_USB_HOST	0x01 // Host Wire Adapter Control/Data interface.  Definition can be found in the Wireless USB Specification in Chapter 8
#define USB_PROTOCOL_WIRELESS_CONTROLLER_USB_DEVICE	0x02 // Device Wire Adapter Control/Data interface.  Definition can be found in the Wireless USB Specification in Chapter 8
#define USB_PROTOCOL_WIRELESS_CONTROLLER_USB_DEVICE_ISOC	0x03 // Device Wire Adapter Isochronous interface.  Definition can be found in the Wireless USB Specification in Chapter 8
/* Miscellaneous */
#define USB_PROTOCOL_MISCELLANEOUS_ACTIVESYNC	0x01 // Active Sync device
#define USB_PROTOCOL_MISCELLANEOUS_PALMSYNC	0x02 // Palm Sync
#define USB_PROTOCOL_MISCELLANEOUS_IAD	0x01 // Interface Association Descriptor. The usage of this class code triple is defined in the Interface Association Descriptor ECN 
#define USB_PROTOCOL_MISCELLANEOUS_WAMP	0x02 // Wire Adapter Multifunction Peripheral programming interface. Definition can be found in the Wireless USB Specification in Chapter 8
#define USB_PROTOCOL_MISCELLANEOUS_CBAF	0x01 // Cable Based Association Framework. This is defined in the Association Model addendum to the Wireless USB specification
#define USB_PROTOCOL_MISCELLANEOUS_RNDIS_ETHERNET	0x01 // RNDIS over Ethernet
#define USB_PROTOCOL_MISCELLANEOUS_RNDIS_WIFI	0x02 // RNDIS over WiFi
#define USB_PROTOCOL_MISCELLANEOUS_RNDIS_WIMAX	0x03 // RNDIS over WiMAX
#define USB_PROTOCOL_MISCELLANEOUS_RNDIS_WWAN	0x04 // RNDIS over WWAN
#define USB_PROTOCOL_MISCELLANEOUS_RNDIS_IPV4	0x05 // RNDIS for Raw IPv4
#define USB_PROTOCOL_MISCELLANEOUS_RNDIS_IPV6	0x06 // RNDIS for Raw IPv6
#define USB_PROTOCOL_MISCELLANEOUS_RNDIS_GPRS	0x07 // RNDIS for GPRS
#define USB_PROTOCOL_MISCELLANEOUS_USB3VISION_CONTROL	0x00 // USB3 Vision Control Interface 
#define USB_PROTOCOL_MISCELLANEOUS_USB3VISION_EVENT	0x01 // USB3 Vision Event Interface
#define USB_PROTOCOL_MISCELLANEOUS_USB3VISION_STREAM	0x02 // USB3 Vision Streaming Interface
/* Application Specific */
#define USB_PROTOCOL_APPLICATION_SPECIFIC_DFU_DEFAULT	0x01 // Device Firmware Upgrade
#define USB_PROTOCOL_APPLICATION_SPECIFIC_IRDA_DEFAULT	0x00 // IRDA Bridge device
#define USB_PROTOCOL_APPLICATION_SPECIFIC_TMC_DEFAULT	0x00 // USB Test and Measurement Device
#define USB_PROTOCOL_APPLICATION_SPECIFIC_TMC_488	0x01 // USB Test and Measurement Device conforming to the USBTMC USB488 Subclass Specification

/* USB Primary Language IDs (See Language Identifiers supplement to the USB 2.0 specification) (These are the first 10 bits of the 16-bit language identifier) */
/* Reserved 0x00 */
#define USB_LANG_ARABIC	0x01 // Arabic
#define USB_LANG_BULGARIAN	0x02 // Bulgarian
#define USB_LANG_CATALAN	0x03 // Catalan
#define USB_LANG_CHINESE	0x04 // Chinese
#define USB_LANG_CZECH	0x05 // Czech
#define USB_LANG_DANISH	0x06 // Danish
#define USB_LANG_GERMAN	0x07 // German
#define USB_LANG_GREEK	0x08 // Greek
#define USB_LANG_ENGLISH	0x09 // English
#define USB_LANG_SPANISH	0x0a // Spanish
#define USB_LANG_FINNISH	0x0b // Finnish
#define USB_LANG_FRENCH	0x0c // French
#define USB_LANG_HEBREW	0x0d // Hebrew
#define USB_LANG_HUNGARIAN	0x0e // Hungarian
#define USB_LANG_ICELANDIC	0x0f // Icelandic
#define USB_LANG_ITALIAN	0x10 // Italian
#define USB_LANG_JAPANESE	0x11 // Japanese
#define USB_LANG_KOREAN	0x12 // Korean
#define USB_LANG_DUTCH	0x13 // Dutch
#define USB_LANG_NORWEGIAN	0x14 // Norwegian
#define USB_LANG_POLISH	0x15 // Polish
#define USB_LANG_PORTUGUESE	0x16 // Portuguese
#define USB_LANG_ROMANIAN	0x18 // Romanian
#define USB_LANG_RUSSIAN	0x19 // Russian
#define USB_LANG_CROATIAN	0x1a // Croatian
#define USB_LANG_SERBIAN	0x1a // Serbian
#define USB_LANG_SLOVAK	0x1b // Slovak
#define USB_LANG_ALBANIAN	0x1c // Albanian
#define USB_LANG_SWEDISH	0x1d // Swedish
#define USB_LANG_THAI	0x1e // Thai
#define USB_LANG_TURKISH	0x1f // Turkish
#define USB_LANG_URDU	0x20 // Urdu
#define USB_LANG_INDONESIAN	0x21 // Indonesian
#define USB_LANG_UKRANIAN	0x22 // Ukrainian
#define USB_LANG_BELARUSIAN	0x23 // Belarusian
#define USB_LANG_SLOVENIAN	0x24 // Slovenian
#define USB_LANG_ESTONIAN	0x25 // Estonian
#define USB_LANG_LATVIAN	0x26 // Latvian
#define USB_LANG_LITHUANIAN	0x27 // Lithuanian
#define USB_LANG_FARSI	0x29 // Farsi
#define USB_LANG_VIETNAMESE	0x2a // Vietnamese
#define USB_LANG_ARMENIAN	0x2b // Armenian
#define USB_LANG_AZERI	0x2c // Azeri
#define USB_LANG_BASQUE	0x2d // Basque
#define USB_LANG_MACEDONIAN	0x2f // Macedonian
#define USB_LANG_AFRIKAANS	0x36 // Afrikaans
#define USB_LANG_GEORGIAN	0x37 // Georgian
#define USB_LANG_FAEROESE	0x38 // Faeroese
#define USB_LANG_HINDI	0x39 // Hindi
#define USB_LANG_MALAY	0x3e // Malay
#define USB_LANG_KAZAK	0x3f // Kazak
#define USB_LANG_SWAHILI	0x41 // Swahili
#define USB_LANG_UZBEK	0x43 // Uzbek
#define USB_LANG_TATAR	0x44 // Tatar
#define USB_LANG_BENGALI	0x45 // Bengali
#define USB_LANG_PUNJABI	0x46 // Punjabi
#define USB_LANG_GUJARATI	0x47 // Gujarati
#define USB_LANG_ORIYA	0x48 // Oriya
#define USB_LANG_TAMIL	0x49 // Tamil
#define USB_LANG_TELUGU	0x4a // Telugu
#define USB_LANG_KANNADA	0x4b // Kannada
#define USB_LANG_MALAYALAM	0x4c // Malayalam
#define USB_LANG_ASSAMESE	0x4d // Assamese
#define USB_LANG_MARATHI	0x4e // Marathi
#define USB_LANG_SANSKRIT	0x4f // Sanskrit
#define USB_LANG_KONKANI	0x57 // Konkani
#define USB_LANG_MANIPURI	0x58 // Manipuri
#define USB_LANG_SINDHI	0x59 // Sindhi
#define USB_LANG_KASHMIRI	0x60 // Kashmiri
#define USB_LANG_NEPALI	0x61 // Nepali
/* Reserved 0x62-0xfe */
#define USB_LANG_HID	0xff // Reserved for USB HID Class use
/* Reserved 0x100-0x3ff */

#define USB_PRIMARY_LANGUAGE_MASK	0x3ff

/* USB SubLanguage IDs (See Language Identifiers supplement to the USB 2.0 specification) (These are the upper 6 bits of the 16-bit language identifier) */
/* Reserved 0x00-0x02 */
#define USB_SUBLANG_ARABIC_SAUDI_ARABIA	0x01 // Arabic (Saudi Arabia)
#define USB_SUBLANG_ARABIC_IRAQ	0x02 // Arabic (Iraq)
#define USB_SUBLANG_ARABIC_EGYPT	0x03 // Arabic (Egypt)
#define USB_SUBLANG_ARABIC_LIBYA	0x04 // Arabic (Libya)
#define USB_SUBLANG_ARABIC_ALGERIA	0x05 // Arabic (Algeria)
#define USB_SUBLANG_ARABIC_MOROCCO	0x06 // Arabic (Morocco)
#define USB_SUBLANG_ARABIC_TUNISIA	0x07 // Arabic (Tunisia)
#define USB_SUBLANG_ARABIC_OMAN	0x08 // Arabic (Oman)
#define USB_SUBLANG_ARABIC_YEMEN	0x09 // Arabic (Yemen)
#define USB_SUBLANG_ARABIC_SYRIA	0x10 // Arabic (Syria)
#define USB_SUBLANG_ARABIC_JORDAN	0x11 // Arabic (Jordan)
#define USB_SUBLANG_ARABIC_LEBANON	0x12 // Arabic (Lebanon)
#define USB_SUBLANG_ARABIC_KUWAIT	0x13 // Arabic (Kuwait)
#define USB_SUBLANG_ARABIC_UAE	0x14 // Arabic (U.A.E.)
#define USB_SUBLANG_ARABIC_BAHRAIN	0x15 // Arabic (Bahrain)
#define USB_SUBLANG_ARABIC_QATAR	0x16 // Arabic (Qatar)
#define USB_SUBLANG_AZERI_CYRILLIC	0x01 // Azeri (Cyrillic)
#define USB_SUBLANG_AZERI_LATIN	0x02 // Azeri (Latin)
#define USB_SUBLANG_CHINESE_TRADITIONAL	0x01 // Chinese (Traditional)
#define USB_SUBLANG_CHINESE_SIMPLIFIED	0x02 // Chinese (Simplified)
#define USB_SUBLANG_CHINESE_HONGKONG	0x03 // Chinese (Hong Kong SAR, PRC)
#define USB_SUBLANG_CHINESE_SINGAPORE	0x04 // Chinese (Singapore)
#define USB_SUBLANG_CHINESE_MACAU	0x05 // Chinese (Macau SAR)
#define USB_SUBLANG_DUTCH	0x01 // Dutch
#define USB_SUBLANG_DUTCH_BELGIAN	0x02 // Dutch (Belgian)
#define USB_SUBLANG_ENGLISH_US	0x01 // English (US)
#define USB_SUBLANG_ENGLISH_UK	0x02 // English (UK)
#define USB_SUBLANG_ENGLISH_AUS	0x03 // English (Australian)
#define USB_SUBLANG_ENGLISH_CAN	0x04 // English (Canadian)
#define USB_SUBLANG_ENGLISH_NZ	0x05 // English (New Zealand)
#define USB_SUBLANG_ENGLISH_EIRE	0x06 // English (Ireland)
#define USB_SUBLANG_ENGLISH_SOUTH_AFRICA	0x07 // English (South Africa)
#define USB_SUBLANG_ENGLISH_JAMAICA	0x08 // English (Jamaica)
#define USB_SUBLANG_ENGLISH_CARIBBEAN	0x09 // English (Caribbean)
#define USB_SUBLANG_ENGLISH_BELIZE	0x0a // English (Belize)
#define USB_SUBLANG_ENGLISH_TRINIDAD	0x0b // English (Trinidad)
#define USB_SUBLANG_ENGLISH_PHILIPPINES	0x0c // English (Zimbabwe)
#define USB_SUBLANG_ENGLISH_ZIMBABWE	0x0d // English (Philippines)
#define USB_SUBLANG_FRENCH	0x01 // French
#define USB_SUBLANG_FRENCH_BELGIAN	0x02 // French (Belgian)
#define USB_SUBLANG_FRENCH_CANADIAN	0x03 // French (Canadian)
#define USB_SUBLANG_FRENCH_SWISS	0x04 // French (Swiss)
#define USB_SUBLANG_FRENCH_LUXEMBOURG	0x05 // French (Luxembourg)
#define USB_SUBLANG_FRENCH_MONACO	0x06 // French (Monaco)
#define USB_SUBLANG_GERMAN	0x01 // German
#define USB_SUBLANG_GERMAN_SWISS	0x02 // German (Swiss)
#define USB_SUBLANG_GERMAN_AUSTRIAN	0x03 // German (Austrian)
#define USB_SUBLANG_GERMAN_LUXEMBOURG	0x04 // German (Luxembourg)
#define USB_SUBLANG_GERMAN_LIECHTENSTEIN	0x05 // German (Liechtenstein)
#define USB_SUBLANG_ITALIAN	0x01 // Italian
#define USB_SUBLANG_ITALIAN_SWISS	0x02 // Italian (Swiss)
#define USB_SUBLANG_KASHMIRI_INDIA	0x02 // Kashmiri (India)
#define USB_SUBLANG_KOREAN	0x01 // Korean
#define USB_SUBLANG_LITHUANIAN	0x01 // Lithuanian
#define USB_SUBLANG_MALAY_MALAYSIA	0x01 // Malay (Malaysia)
#define USB_SUBLANG_MALAY_BRUNEI_DARUSSALAM	0x02 // Malay (Brunei Darassalam)
#define USB_SUBLANG_NEPALI_INDIA	0x02 // Nepali (India)
#define USB_SUBLANG_NORWEGIAN_BOKMAL	0x01 // Norwegian (Bokmal)
#define USB_SUBLANG_NORWEGIAN_NYNORSK	0x02 // Norwegian (Nynorsk)
#define USB_SUBLANG_PORTUGUESE	0x01 // Portuguese (Brazilian)
#define USB_SUBLANG_PORTUGUESE_BRAZILIAN	0x02 // Portuguese
#define USB_SUBLANG_SERBIAN_LATIN	0x02 // Serbian (Latin)
#define USB_SUBLANG_SERBIAN_CYRILLIC	0x03 // Serbian (Cyrillic)
#define USB_SUBLANG_SPANISH	0x01 // Spanish (Castilian)
#define USB_SUBLANG_SPANISH_MEXICAN	0x02 // Spanish (Mexican)
#define USB_SUBLANG_SPANISH_MODERN	0x03 // Spanish (Modern)
#define USB_SUBLANG_SPANISH_GUATEMALA	0x04 // Spanish (Guatemala)
#define USB_SUBLANG_SPANISH_COSTA_RICA	0x05 // Spanish (Costa Rica)
#define USB_SUBLANG_SPANISH_PANAMA	0x06 // Spanish (Panama)
#define USB_SUBLANG_SPANISH_DOMINICAN_REPUBLIC	0x07 // Spanish (Dominican Republic)
#define USB_SUBLANG_SPANISH_VENEZUELA	0x08 // Spanish (Venezuela)
#define USB_SUBLANG_SPANISH_COLOMBIA	0x09 // Spanish (Colombia)
#define USB_SUBLANG_SPANISH_PERU	0x0a // Spanish (Peru)
#define USB_SUBLANG_SPANISH_ARGENTINA	0x0b // Spanish (Argentina)
#define USB_SUBLANG_SPANISH_ECUADOR	0x0c // Spanish (Ecuador)
#define USB_SUBLANG_SPANISH_CHILE	0x0d // Spanish (Chile)
#define USB_SUBLANG_SPANISH_URUGUAY	0x0e // Spanish (Uruguay)
#define USB_SUBLANG_SPANISH_PARAGUAY	0x0f // Spanish (Paraguay)
#define USB_SUBLANG_SPANISH_BOLIVIA	0x10 // Spanish (Bolivia)
#define USB_SUBLANG_SPANISH_EL_SALVADOR	0x11 // Spanish (El Salvador)
#define USB_SUBLANG_SPANISH_HONDURAS	0x12 // Spanish (Honduras)
#define USB_SUBLANG_SPANISH_NICARAGUA	0x13 // Spanish (Nicaragua)
#define USB_SUBLANG_SPANISH_PUERTO_RICO	0x14 // Spanish (Puerto Rico)
#define USB_SUBLANG_SWEDISH	0x01 // Swedish
#define USB_SUBLANG_SWEDISH_FINLAND	0x02 // Swedish (Finland)
#define USB_SUBLANG_URDU_PAKISTAN	0x01 // Urdu (Pakistan)
#define USB_SUBLANG_URDU_INDIA	0x02 // Urdu (India)
#define USB_SUBLANG_UZBEK_LATIN	0x01 // Uzbek (Latin)
#define USB_SUBLANG_UZBEK_CYRILLIC	0x02 // Uzbek (Cyrillic)
#define USB_SUBLANG_HID_USAGE_DATA_DESCRIPTOR	0x01 // HID (Usage Data Descriptor)
#define USB_SUBLANG_HID_VENDOR_DEFINED_1	0x3c // HID (Vendor Defined 1)
#define USB_SUBLANG_HID_VENDOR_DEFINED_2	0x3d // HID (Vendor Defined 2)
#define USB_SUBLANG_HID_VENDOR_DEFINED_3	0x3e // HID (Vendor Defined 3)
#define USB_SUBLANG_HID_VENDOR_DEFINED_4	0x3f // HID (Vendor Defined 4)

/* USB Primary Language Identifiers (See Language Identifiers supplement to the USB 2.0 specification) */
#define USB_LANGID_US_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_US << 10)) // English (US)
#define USB_LANGID_UK_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_UK << 10)) // English (UK)
#define USB_LANGID_AUS_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_AUS << 10)) // English (Australian)
#define USB_LANGID_CAN_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_CAN << 10)) // English (Canadian)
#define USB_LANGID_NZ_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_NZ << 10)) // English (New Zealand)
#define USB_LANGID_EIRE_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_EIRE << 10)) // English (Ireland)
#define USB_LANGID_SOUTH_AFRICA_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_SOUTH_AFRICA << 10)) // English (South Africa)
#define USB_LANGID_JAMAICA_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_JAMAICA << 10)) // English (Jamaica)
#define USB_LANGID_CARIBBEAN_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_CARIBBEAN << 10)) // English (Caribbean)
#define USB_LANGID_BELIZE_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_BELIZE << 10)) // English (Belize)
#define USB_LANGID_TRINIDAD_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_TRINIDAD << 10)) // English (Trinidad)
#define USB_LANGID_PHILIPPINES_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_PHILIPPINES << 10)) // English (Philippines)
#define USB_LANGID_ZIMBABWE_ENGLISH	(USB_LANG_ENGLISH | (USB_SUBLANG_ENGLISH_ZIMBABWE << 10)) // English (Zimbabwe)

#define USB_LANGID_USAGE_HID	(USB_LANG_HID | (USB_SUBLANG_HID_USAGE_DATA_DESCRIPTOR << 10))
#define USB_LANGID_VENDOR1_HID	(USB_LANG_HID | (USB_SUBLANG_HID_VENDOR_DEFINED_1 << 10))
#define USB_LANGID_VENDOR2_HID	(USB_LANG_HID | (USB_SUBLANG_HID_VENDOR_DEFINED_2 << 10))
#define USB_LANGID_VENDOR3_HID	(USB_LANG_HID | (USB_SUBLANG_HID_VENDOR_DEFINED_3 << 10))
#define USB_LANGID_VENDOR4_HID	(USB_LANG_HID | (USB_SUBLANG_HID_VENDOR_DEFINED_4 << 10))

/* USB Vendor IDs */
#define USB_VENDORID_REALTEK	0x0BDA // Realtek

/* ============================================================================== */
/* USB Hub specific constants */
#define USB_HUB_PREFIX	"USBHub" // Name prefix for USB Hubs

/* USB Hub Types */
#define USBHUB_TYPE_NONE	0

#define USBHUB_TYPE_MAX	0

/* USB Hub States */
#define USBHUB_STATE_DETACHED	0
#define USBHUB_STATE_DETACHING	1
#define USBHUB_STATE_ATTACHING	2
#define USBHUB_STATE_ATTACHED	3

#define USBHUB_STATE_MAX	3

/* USB Hub Flags */
#define USBHUB_FLAG_NONE	0x00000000
#define USBHUB_FLAG_COMPOUND	0x00000001 // The Hub is part of a compound device
#define USBHUB_FLAG_PORT_POWER	0x00000002 // The Hub supports per port power switching
#define USBHUB_FLAG_PORT_PROTECTION	0x00000004 // The Hub supports per port over current protection
#define USBHUB_FLAG_MULTI_TRANSLATOR	0x00000008 // The Hub includes multiple transaction translators (1 per port)

#define USBHUB_THREAD_STACK_SIZE	SIZE_32K // Stack size of USB hub thread
#define USBHUB_THREAD_PRIORITY	THREAD_PRIORITY_HIGHEST // Priority of USB hub thread
#define USBHUB_THREAD_NAME	"USB Hub" // Name of USB hub thread

#define USBHUB_DEVICE_DESCRIPTION	"USB Hub" // Description of USB hub device

#define USBHUB_DRIVER_NAME	"USB Hub Driver" // Name of USB hub driver

/* USB_HUB_MAX_PORTS = 255; */

#define USB_PORT_RESET_TIMEOUT	500 // Maximum milliseconds to wait for a port to reset (500 is the same value that Linux uses)
#define USB_PORT_RESET_RECOVERY	30 // Milliseconds to wait after port reset to allow the device attached to the port to recover before any data transfers. USB 2.0 spec says 10ms
#define USB_PORT_SHORT_RESET_DELAY	10 // Milliseconds between each status check on the port while waiting for it to finish being reset (Linux uses 10ms as the default value)
#define USB_PORT_LONG_RESET_DELAY	200 // Milliseconds between each status check on the port while waiting for it to finish being reset (Linux uses 200ms for Low Speed devices)
#define USB_PORT_ROOT_RESET_DELAY	60 // Milliseconds between each status check on the port while waiting for it to finish being reset (Linux uses 60ms for Root hub ports)

#define USB_ATTACH_DEBOUNCE_INTERVAL	100 // Milliseconds to wait after attachment for debounce (TATTDB)
#define USB_ADDRESS_COMPLETION_TIME	50 // Milliseconds to wait for set address completion (TDSETADDR)

/* Values for wHubCharacteristics in type TUSBHubDescriptor (See Table 11-13 in Section 11.23.2.1 of the USB 2.0 specification) */
#define USB_HUB_CHARACTERISTIC_LPSM	(3 << 0) // Logical Power Switching Mode
#define USB_HUB_CHARACTERISTIC_LPSM_GANGED	(0 << 0) // Ganged power switching (all ports power at once)
#define USB_HUB_CHARACTERISTIC_LPSM_PORT	(1 << 0) // Individual port power switching
#define USB_HUB_CHARACTERISTIC_IS_COMPOUND_DEVICE	(1 << 2) // Identifies a Compound Device (0 = Hub is not part of a compound device / 1 = Hub is part of a compound device)
#define USB_HUB_CHARACTERISTIC_OCPM	(3 << 3) // Over-current Protection Mode
#define USB_HUB_CHARACTERISTIC_OCPM_GLOBAL	(0 << 3) // Global Over-current Protection
#define USB_HUB_CHARACTERISTIC_OCPM_PORT	(1 << 3) // Individual Port Over-current Protection
#define USB_HUB_CHARACTERISTIC_OCPM_NONE	(2 << 3) // No Over-current Protection
#define USB_HUB_CHARACTERISTIC_TTTT	(3 << 5) // TT Think Time
#define USB_HUB_CHARACTERISTIC_TTTT_8	(0 << 5) // TT requires at most 8 FS bit times of inter transaction gap
#define USB_HUB_CHARACTERISTIC_TTTT_16	(1 << 5) // TT requires at most 16 FS bit times of inter transaction gap
#define USB_HUB_CHARACTERISTIC_TTTT_24	(2 << 5) // TT requires at most 24 FS bit times of inter transaction gap
#define USB_HUB_CHARACTERISTIC_TTTT_32	(3 << 5) // TT requires at most 32 FS bit times of inter transaction gap
#define USB_HUB_CHARACTERISTIC_PORT_INDICATOR	(1 << 7) // Port Indicators Supported (0 = Port Indicators are not supported / 1 =  Port Indicators are supported)

/* USB Hub Features (See Table 11-17 in Section 11.24.2 of the USB 2.0 specification) */
#define USB_C_HUB_LOCAL_POWER	0
#define USB_C_HUB_OVER_CURRENT	1

/* USB Port Features (See Table 11-17 in Section 11.24.2 of the USB 2.0 specification) */
#define USB_PORT_CONNECTION	0
#define USB_PORT_ENABLE	1
#define USB_PORT_SUSPEND	2
#define USB_PORT_OVER_CURRENT	3
#define USB_PORT_RESET	4
#define USB_PORT_POWER	8
#define USB_PORT_LOW_SPEED	9
#define USB_C_PORT_CONNECTION	16
#define USB_C_PORT_ENABLE	17
#define USB_C_PORT_SUSPEND	18
#define USB_C_PORT_OVER_CURRENT	19
#define USB_C_PORT_RESET	20
#define USB_PORT_TEST	21
#define USB_PORT_INDICATOR	22

/* USB Hub Class Requests (See Table 11-16 in Section 11.24.2 of the USB 2.0 specification) */
#define USB_HUB_REQUEST_GET_STATUS	0
#define USB_HUB_REQUEST_CLEAR_FEATURE	1
#define USB_HUB_REQUEST_SET_FEATURE	3
#define USB_HUB_REQUEST_GET_DESCRIPTOR	6
#define USB_HUB_REQUEST_SET_DESCRIPTOR	7
#define USB_HUB_REQUEST_CLEAR_TT_BUFFER	8
#define USB_HUB_REQUEST_RESET_TT	9
#define USB_HUB_REQUEST_GET_TT_STATE	10
#define USB_HUB_REQUEST_STOP_TT	11

/* Values for wPortStatus in type TUSBPortStatus (See Table 11-21 in Section 11.24.2.7.1 of the USB 2.0 specification) */
#define USB_PORT_STATUS_CONNNECTED	(1 << 0)
#define USB_PORT_STATUS_ENABLED	(1 << 1)
#define USB_PORT_STATUS_SUSPENDED	(1 << 2)
#define USB_PORT_STATUS_OVERCURRENT	(1 << 3)
#define USB_PORT_STATUS_RESET	(1 << 4)
#define USB_PORT_STATUS_POWERED	(1 << 8)
#define USB_PORT_STATUS_LOW_SPEED_ATTACHED	(1 << 9)
#define USB_PORT_STATUS_HIGH_SPEED_ATTACHED	(1 << 10)
#define USB_PORT_STATUS_TEST_MODE	(1 << 11)
#define USB_PORT_STATUS_INDICATOR_CONTROL	(1 << 12)

/* Values for wPortChange in type TUSBPortStatus (See Table 11-20 in Section 11.24.2.6 of the USB 2.0 specification) */
#define USB_PORT_CHANGE_CONNECTED	(1 << 0)
#define USB_PORT_CHANGE_ENABLED	(1 << 1)
#define USB_PORT_CHANGE_SUSPENDED	(1 << 2)
#define USB_PORT_CHANGE_OVERCURRENT	(1 << 3)
#define USB_PORT_CHANGE_RESET	(1 << 4)

/* Values for wHubStatus in type TUSBHubStatus (See Table 11-19 in Section 11.24.2.6 of the USB 2.0 specification) */
#define USB_HUB_STATUS_LOCAL_POWER	(1 << 0)
#define USB_HUB_STATUS_OVERCURRENT	(1 << 1)

/* Values for wHubChange in type TUSBHubStatus (See Table 11-20 in Section 11.24.2.6 of the USB 2.0 specification) */
#define USB_HUB_CHANGE_LOCAL_POWER	(1 << 0)
#define USB_HUB_CHANGE_OVERCURRENT	(1 << 1)

/* ============================================================================== */
/* USB Device, Driver and Host specific types */
typedef struct _USB_DEVICE_ID USB_DEVICE_ID; // USB Device Id record for driver device identification (Not part of USB specification)
struct _USB_DEVICE_ID
{
	uint16_t idvendor;
	uint16_t idproduct;
};

typedef struct _USB_INTERFACE_ID USB_INTERFACE_ID; // USB Interface Id record for driver device identification (Not part of USB specification)
struct _USB_INTERFACE_ID
{
	uint8_t binterfaceclass;
	uint8_t binterfacesubclass;
	uint8_t binterfaceprotocol;
};

typedef struct _USB_DEVICE_AND_INTERFACE_ID USB_DEVICE_AND_INTERFACE_ID; // USB Device and Interface Id record for driver device identification (Not part of USB specification)
struct _USB_DEVICE_AND_INTERFACE_ID
{
	uint16_t idvendor;
	uint16_t idproduct;
	uint8_t binterfaceclass;
	uint8_t binterfacesubclass;
	uint8_t binterfaceprotocol;
};

typedef struct _USB_DEVICE_AND_INTERFACE_NO USB_DEVICE_AND_INTERFACE_NO; // USB Device and Interface No record for driver device identification (Not part of USB specification)
struct _USB_DEVICE_AND_INTERFACE_NO
{
	uint16_t idvendor;
	uint16_t idproduct;
	uint8_t binterfacenumber;
};

/* USB Control Request SETUP data (See Table 9-2 in Section 9.3 of the USB 2.0 specification) */
typedef struct _USB_CONTROL_SETUP_DATA USB_CONTROL_SETUP_DATA;
struct _USB_CONTROL_SETUP_DATA
{
	uint8_t bmrequesttype;
	uint8_t brequest;
	uint16_t wvalue;
	uint16_t windex;
	uint16_t wlength;
} PACKED;

/* USB Device Descriptor Header (See Table 9-8 in 9.6.1 of the USB 2.0 specification) */
typedef struct _USB_DESCRIPTOR_HEADER USB_DESCRIPTOR_HEADER;
struct _USB_DESCRIPTOR_HEADER
{
	uint8_t blength;
	uint8_t bdescriptortype;
} PACKED;

/* USB Device Descriptor (See Table 9-8 in 9.6.1 of the USB 2.0 specification) */
typedef struct _USB_DEVICE_DESCRIPTOR USB_DEVICE_DESCRIPTOR;
struct _USB_DEVICE_DESCRIPTOR
{
	uint8_t blength;
	uint8_t bdescriptortype;
	uint16_t bcdusb;
	uint8_t bdeviceclass;
	uint8_t bdevicesubclass;
	uint8_t bdeviceprotocol;
	uint8_t bmaxpacketsize0;
	uint16_t idvendor;
	uint16_t idproduct;
	uint16_t bcddevice;
	uint8_t imanufacturer;
	uint8_t iproduct;
	uint8_t iserialnumber;
	uint8_t bnumconfigurations;
} PACKED;

/* USB Configuration Descriptor (See Table 9-10 in Section 9.6.3 of the USB 2.0 specification) */
typedef struct _USB_CONFIGURATION_DESCRIPTOR USB_CONFIGURATION_DESCRIPTOR;
struct _USB_CONFIGURATION_DESCRIPTOR
{
	uint8_t blength;
	uint8_t bdescriptortype;
	uint16_t wtotallength;
	uint8_t bnuminterfaces;
	uint8_t bconfigurationvalue;
	uint8_t iconfiguration;
	uint8_t bmattributes;
	uint8_t bmaxpower;
} PACKED;

/* USB Interface Descriptor (See Table 9-12 in Section 9.6.6 of the USB 2.0 specification) */
typedef struct _USB_INTERFACE_DESCRIPTOR USB_INTERFACE_DESCRIPTOR;
struct _USB_INTERFACE_DESCRIPTOR
{
	uint8_t blength;
	uint8_t bdescriptortype;
	uint8_t binterfacenumber;
	uint8_t balternatesetting;
	uint8_t bnumendpoints;
	uint8_t binterfaceclass;
	uint8_t binterfacesubclass;
	uint8_t binterfaceprotocol;
	uint8_t iinterface;
} PACKED;

/* USB Endpoint Descriptor (See Table 9-13 in Section 9.6.6 of the USB 2.0 specification) */
typedef struct _USB_ENDPOINT_DESCRIPTOR USB_ENDPOINT_DESCRIPTOR;
struct _USB_ENDPOINT_DESCRIPTOR
{
	uint8_t blength;
	uint8_t bdescriptortype;
	uint8_t bendpointaddress;
	uint8_t bmattributes;
	uint16_t wmaxpacketsize;
	uint8_t binterval;
} PACKED;

/* USB String Descriptor (See Table 9-16 in Section 9.7 of the USB 2.0 specification) */
typedef struct _USB_STRING_DESCRIPTOR USB_STRING_DESCRIPTOR;
struct _USB_STRING_DESCRIPTOR
{
	uint8_t blength;
	uint8_t bdescriptortype;
	uint16_t bstring[]; // UTF-16LE encoded string (specification says "UNICODE")
} PACKED;

typedef uint16_t USB_STRING_DESCRIPTOR_STRING[126]; // Array type to allow typecasting of bString element in TUSBStringDescriptor (Maximum size of descriptor is 255) (126 x 2 + 2 = 254)

typedef uint16_t USB_STRING_DESCRIPTOR_LANGIDS[126]; // Array type to allow typecasting of bString element in TUSBStringDescriptor (Maximum size of descriptor is 255) (126 x 2 + 2 = 254)

/* Device status information returned by a USB_DEVICE_REQUEST_GET_STATUS control message (See Section 9.4.6 of the USB 2.0 specification) */
typedef struct _USB_DEVICE_STATUS USB_DEVICE_STATUS;
struct _USB_DEVICE_STATUS
{
	uint16_t wstatus;
} PACKED;

/* USB Device */
typedef struct _USB_HOST USB_HOST; // Forward declared to satisfy USBDevice
typedef struct _USB_DRIVER USB_DRIVER; // Forward declared to satisfy USBDevice
typedef struct _USB_ALTERNATE USB_ALTERNATE; // Forward declared to satisfy USBDevice
typedef struct _USB_INTERFACE USB_INTERFACE; // Forward declared to satisfy USBDevice
typedef struct _USB_CONFIGURATION USB_CONFIGURATION; // Forward declared to satisfy USBDevice
typedef struct _USB_DEVICE USB_DEVICE;

/* USB Device Bind Callback */
typedef uint32_t STDCALL (*usb_device_bind_proc)(USB_DEVICE *device);
/* USB Device Unbind Callback */
typedef uint32_t STDCALL (*usb_device_unbind_proc)(USB_DEVICE *device, USB_DRIVER *driver);
/* USB Device Enumeration Callback */
typedef uint32_t STDCALL (*usb_device_enumerate_cb)(USB_DEVICE *device, void *data);
/* USB Device Notification Callback */
typedef uint32_t STDCALL (*usb_device_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* USB Device Methods */
/* None */

struct _USB_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this USB device
	// USB Properties
	uint32_t usbid; // Unique Id of this USB in the USB device table
	uint32_t usbstate; // USB device state (eg USB_STATE_ATTACHED)
	uint32_t usbstatus; // USB device status (eg USB_STATUS_BOUND)
	USB_HOST *host; // Host controller this USB device is connected to (Set by USB core)
	USB_DEVICE *parent; // Hub this USB device is connected to, or nil if this is the Root Hub (Set by USB core)
	USB_DRIVER *driver; // Driver this USB device is bound to, if any (Set by USB core)
	// Driver Properties
	MUTEX_HANDLE lock; // USB device lock
	uint32_t address; // Address of this device (Set by USB core)
	uint32_t speed; // Speed at which this device is attached (Set by USB core)
	uint32_t depth; // Depth of this device (Root Hub is 0, next level hub is 1 etc) (Set by USB core)
	uint32_t portnumber; // 1 based index of the USB port on the parent hub this device is plugged into (0 for the Root Hub) (Set by USB core)
	uint32_t configurationvalue; // The current configuration value of this USB device (Set by USB core)
	USB_DEVICE_DESCRIPTOR *descriptor; // Device descriptor of this device (Set by USB core)
	USB_CONFIGURATION *configuration; // Currently selected configuration of this USB device (Set by USB core)
	USB_CONFIGURATION *configurations; // All available configurations on this device (Set by USB core)
	char product[128]; // Null terminated product string (ASCII encoded, English if available) of this device
	char manufacturer[128]; // Null terminated manufacturer string (ASCII encoded, English if available) of this device
	char serialnumber[128]; // Null terminated serial number string (ASCII encoded, English if available) of this device
	void *driverdata; // Private data for the driver of this USB device
	uint32_t lasterror; // Last error to occur on this device
	uint32_t pendingcount; // Number of USB requests pending for this device (Set by USB core)
	THREAD_ID waiterthread; // Thread waiting for pending requests to complete (for device detachment) (Set by USB core)
	// Statistics Properties
	uint32_t requestcount; // Number of USB requests that have been submitted to this device
	uint32_t requesterrors; // Number of USB requests that have failed on this device
	// Internal Properties
	USB_DEVICE *prev; // Previous entry in USB device table
	USB_DEVICE *next; // Next entry in USB device table
};

/* USB Configuration */
/* PUSBConfiguration = ^TUSBConfiguration; */
struct _USB_CONFIGURATION
{
	// Driver Properties
	USB_CONFIGURATION_DESCRIPTOR *descriptor; // Configuration descriptor of this configuration (Set by USB core)
	USB_INTERFACE *interfaces; // All available interfaces in this configuration (Set by USB core)
	char description[128]; // Null terminated description string (ASCII encoded, English if available) of this configuration
};

/* USB Interface */
/* PUSBInterface = ^TUSBInterface; */
struct _USB_INTERFACE
{
	// USB Properties
	USB_DRIVER *driver; // Driver this USB interface is bound to, if any (Set by USB core)
	// Driver Properties
	uint32_t alternatecount; // The number of alternate settings available for this interface (Set by USB core)
	uint32_t alternatesetting; // The currently selected alternate setting for this interface (Set by USB core)
	USB_INTERFACE_DESCRIPTOR *descriptor; // Interface descriptor of this interface (Set by USB core)
	USB_ENDPOINT_DESCRIPTOR *endpoints; // All available endpoint descriptors on this interface (Set by USB core)
	USB_ALTERNATE *alternates; // All available alternate settings for this interface (Set by USB core)
	char description[128]; // Null terminated description string (ASCII encoded, English if available) of this interface
	uint8_t *classdata; // Pointer to the start of any class specific descriptors for this interface (Set by USB core)
	uint32_t classsize; // Size of any class specific descriptors for this interface (Set by USB core)
	void *driverdata; // Private data for the driver of this USB interface
};

/* USB Alternate */
struct _USB_ALTERNATE
{
	// Driver Properties
	USB_INTERFACE_DESCRIPTOR *descriptor; // Interface descriptor of this alternate setting (Set by USB core)
	USB_ENDPOINT_DESCRIPTOR *endpoints; // All available endpoint descriptors on this alternate setting (Set by USB core)
	char description[128]; // Null terminated description string (ASCII encoded, English if available) of this alternate setting
};

/* USB Driver */
/* PUSBDriver = ^TUSBDriver; */

/* USB Driver Enumeration Callback */
typedef uint32_t STDCALL (*usb_driver_enumerate_cb)(USB_DRIVER *driver, void *data);

/* USB Driver Methods */
typedef uint32_t STDCALL (*usb_driver_bind_proc)(USB_DEVICE *device, USB_INTERFACE *interrface);
typedef uint32_t STDCALL (*usb_driver_unbind_proc)(USB_DEVICE *device, USB_INTERFACE *interrface);

struct _USB_DRIVER
{
	// Driver Properties
	DRIVER driver; // The Driver entry for this USB Driver
	// USB Properties
	usb_driver_bind_proc driverbind; // A Driver specific DriverBind method implementing the standard USB driver interface
	usb_driver_unbind_proc driverunbind; // A Driver specific DriverUnbind method implementing the standard USB driver interface
	// Interface Properties
	MUTEX_HANDLE lock; // Driver lock
	// Internal Properties
	USB_DRIVER *prev; // Previous entry in Driver table
	USB_DRIVER *next; // Next entry in Driver table
};

/* USB Host */
typedef struct _USB_REQUEST USB_REQUEST; // Forward declared to satisfy USBHost

/* USB Host Enumeration Callback */
typedef uint32_t STDCALL (*usb_host_enumerate_cb)(USB_HOST *host, void *data);
/* USB Host Notification Callback */
typedef uint32_t STDCALL (*usb_host_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* USB Host Methods */
typedef uint32_t STDCALL (*usb_host_start_proc)(USB_HOST *host);
typedef uint32_t STDCALL (*usb_host_stop_proc)(USB_HOST *host);
typedef uint32_t STDCALL (*usb_host_reset_proc)(USB_HOST *host);
typedef uint32_t STDCALL (*usb_host_submit_proc)(USB_HOST *host, USB_REQUEST *request);
typedef uint32_t STDCALL (*usb_host_cancel_proc)(USB_HOST *host, USB_REQUEST *request);

struct _USB_HOST
{
	// Device Properties
	DEVICE device; // The Device entry for this USB Host
	// USB Properties
	uint32_t hostid; // Unique Id of this Host in the Host table
	uint32_t hoststate; // Host state (eg USBHOST_STATE_ENABLED)
	usb_host_start_proc hoststart; // A Host specific HostStart method implementing the standard USB host interface
	usb_host_stop_proc hoststop; // A Host specific HostStop method implementing the standard USB host interface
	usb_host_reset_proc hostreset; // A Host specific HostReset method implementing the standard USB host interface
	usb_host_submit_proc hostsubmit; // A Host specific HostSubmit method implementing the standard USB host interface
	usb_host_cancel_proc hostcancel; // A Host specific HostCancel method implementing the standard USB host interface
	// Driver Properties
	MUTEX_HANDLE lock; // Host lock
	USB_DEVICE *roothub; // The Root hub for this Host (or nil if the Host has not yet been started)
	uint32_t alignment; // Host data buffer alignment (for DMA requests etc)
	uint32_t multiplier; // Host data buffer multiplier (for DMA requests etc)
	uint32_t maxtransfer; // Host maximum transfer size
	// Statistics Properties
	uint32_t requestcount; // Number of USB requests that have been submitted to this host
	uint32_t requesterrors; // Number of USB requests that have failed on this host
	// Internal Properties
	USB_HOST *prev; // Previous entry in Host table
	USB_HOST *next; // Next entry in Host table
};

/* USB Request */

/* USB Request Methods */
typedef void STDCALL (*usb_request_completed_cb)(USB_REQUEST *request);

struct _USB_REQUEST
{
	// Request Properties
	USB_DEVICE *device; // USB Device to send this request to
	USB_ENDPOINT_DESCRIPTOR *endpoint; // Endpoint descriptor on the device to send this request to
	void *data; // Data buffer for the request (IN or OUT)
	uint32_t size; // Size of data buffer (For IN requests, the maximum number of bytes of data to receive) (For OUT requests, the exact number of bytes of data to send)
	uint32_t flags; // Flags for the request (eg USB_REQUEST_FLAG_ALIGNED)
	usb_request_completed_cb callback; // Callback function that will be called when this USB request has been successfully completed or has failed
	void *driverdata; // USB device driver private data for the completion callback (Optional)
	// Control Properties
	USB_CONTROL_SETUP_DATA *setupdata; // Data for the Setup phase of a USB control request (Must be provided for control requests, ignored otherwise)
	uint32_t statusdata; // Data for the Status phase of a USB control request (For safety only as no data is normally transferred in the status phase)
	// Result Properties
	uint32_t status; // Status of the transfer (USB_STATUS_SUCCESS if successful, or another error code if the transfer failed)
	uint32_t actualsize; // Actual size of the data transferred (Should be checked after a successful IN request)
	// Driver Properties
	void *transferdata; // Host driver private data for transfer handling
	void *currentdata; // Host driver data pointer during transaction processing
	LONGBOOL isping; // Ping request in progress as part of request processing
	LONGBOOL issplit; // Request is a split transaction due to full or low speed device
	LONGBOOL completesplit; // On a split transaction indicates if the request is on the start split or complete split phase
	LONGBOOL shortattempt; // The current transaction for this request is a short read or write
	LONGBOOL startofframe; // The request needs to wait for the next start of frame to be started
	uint32_t controlphase; // The currently processing phase of a control request
	uint32_t nextdatapid; // The next Data PID for the data toggle during IN or OUT (Data0/Data1 etc)
	uint32_t attemptedsize;
	uint32_t attemptedpacketsremaining;
	uint32_t attemptedbytesremaining;
	uint32_t bytesattempted;
	uint32_t bytestransferred;
	uint32_t spliterrorcount;
	uint32_t completesplitretries;
	THREAD_HANDLE resubmitthread; // The handle of the thread performing resubmit for this request (or INVALID_HANDLE_VALUE)
	SEMAPHORE_HANDLE resubmitsemaphore; // The handle of the semaphore used to signal the resubmit thread (or INVALID_HANDLE_VALUE)
	// $IFDEF USB_DEBUG
	// Debug Statistics
	uint32_t startsplitattempts;
	uint32_t completesplitattempts;
	uint32_t completesplitrestarts;
	uint32_t startsplitnaks;
	uint32_t completesplitnyets;
	uint32_t completesplitnaks;
	// $ENDIF
};

/* ============================================================================== */
/* USB Hub specific types */

/* USB Hub Descriptor (See Table 11-13 in Section 11.23 of the USB 2.0 specification) */
typedef struct _USB_HUB_DESCRIPTOR USB_HUB_DESCRIPTOR;
struct _USB_HUB_DESCRIPTOR
{
	uint8_t bdesclength;
	uint8_t bdescriptortype;
	uint8_t bnbrports;
	uint16_t whubcharacteristics;
	uint8_t bpwron2pwrgood;
	uint8_t bhubcontrcurrent;
	uint8_t vardata[]; // Variable length field, 64 should be the maximum possible length (255 ports = 2 x 32 bytes of data)
} PACKED;

typedef uint8_t USB_HUB_DESCRIPTOR_DATA[64]; // Array type to allow typecasting of varData element in TUSBHubDescriptor

/* USB Port Status (See Section 11.24.2.7 of the USB 2.0 specification) */
typedef struct _USB_PORT_STATUS USB_PORT_STATUS;
struct _USB_PORT_STATUS
{
	uint16_t wportstatus; // See: USB_PORT_STATUS values above
	uint16_t wportchange; // See: USB_PORT_CHANGE values above
} PACKED;

/* USB Hub Status (See Section 11.24.2.6 of the USB 2.0 specification) */
typedef struct _USB_HUB_STATUS USB_HUB_STATUS;
struct _USB_HUB_STATUS
{
	uint16_t whubstatus; // See: USB_HUB_STATUS values above
	uint16_t whubchange; // See: USB_HUB_CHANGE values above
} PACKED;

/* USB Hub Status Change Data */
typedef struct _USB_HUB_DATA USB_HUB_DATA;
struct _USB_HUB_DATA
{
	uint8_t data[8];
};

/* USB Port */
typedef struct _USB_HUB USB_HUB; // Forward declared to satisfy USBPort
typedef struct _USB_PORT USB_PORT;
struct _USB_PORT
{
	USB_HUB *hub; // Pointer to the USB hub this port is attached to
	uint8_t number; // Number of this port (1-based)
	USB_DEVICE *child; // Pointer to the USB device attached to this port, or nil if there is none
	USB_PORT_STATUS status; // Status of this port
};

/* USB Hub */

/* USB Hub Enumeration Callback */
typedef uint32_t STDCALL (*usb_hub_enumerate_cb)(USB_HUB *hub, void *data);
/* USB Hub Notification Callback */
typedef uint32_t STDCALL (*usb_hub_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* USB Hub Methods */
/* None */

struct _USB_HUB
{
	// Device Properties
	DEVICE device; // The Device entry for this Hub
	// Hub Properties
	uint32_t hubid; // Unique Id of this Hub in the Hub table
	uint32_t hubstate; // Hub state (eg USBHUB_STATE_ATTACHED)
	// Driver Properties
	MUTEX_HANDLE lock; // Hub lock
	USB_HUB_DESCRIPTOR *descriptor; // Class specific Descriptor for this hub
	USB_PORT *ports; // Ports on this hub (Set by USBHubCreatePorts using the value in Descriptor.bNbrPorts)
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	// USB Properties
	USB_HUB_DATA *statusdata; // Hub status change data buffer
	USB_REQUEST *statusrequest; // Hub status change request
	USB_ENDPOINT_DESCRIPTOR *statusendpoint; // Hub Interrupt IN Endpoint
	uint32_t pendingcount; // Number of USB requests pending for this hub
	THREAD_ID waiterthread; // Thread waiting for pending requests to complete (for hub detachment)
	// Internal Properties
	USB_HUB *prev; // Previous entry in Hub table
	USB_HUB *next; // Next entry in Hub table
};

/* USB Logging specific types */
typedef void STDCALL (*usb_log_output_proc)(char *text, void *data);

/* ============================================================================== */
/* Initialization Functions */
uint32_t STDCALL usb_start(void);
uint32_t STDCALL usb_stop(void);

void STDCALL usb_async_start(USB_HOST *host);

/* ============================================================================== */
/* USB Device, Driver and Host Functions */
// Device Methods
uint8_t STDCALL usb_device_get_address(USB_DEVICE *device);
uint32_t STDCALL usb_device_set_address(USB_DEVICE *device, uint8_t address);

uint32_t STDCALL usb_device_get_descriptor(USB_DEVICE *device, uint8_t brequest, uint8_t bmrequesttype, uint16_t wvalue, uint16_t windex, void *data, uint16_t length);

uint32_t STDCALL usb_device_get_device_descriptor(USB_DEVICE *device, void *data, uint16_t length);

uint32_t STDCALL usb_device_create_device_descriptor(USB_DEVICE *device, uint16_t length);
uint32_t STDCALL usb_device_read_device_descriptor(USB_DEVICE *device, uint16_t length);
uint32_t STDCALL usb_device_read_device_descriptor_ex(USB_DEVICE *device, uint16_t length, BOOL allowshort);

uint32_t STDCALL usb_device_create_configurations(USB_DEVICE *device);
uint32_t STDCALL usb_device_read_configurations(USB_DEVICE *device);

uint32_t STDCALL usb_device_create_configuration(USB_DEVICE *device, uint8_t index, uint16_t size);
uint32_t STDCALL usb_device_read_configuration(USB_DEVICE *device, uint8_t index);

uint32_t STDCALL usb_device_get_string_descriptor(USB_DEVICE *device, uint8_t index, void *data, uint16_t length);
uint32_t STDCALL usb_device_get_string_descriptor_ex(USB_DEVICE *device, uint8_t index, uint16_t languageid, void *data, uint16_t length);

void STDCALL usb_device_read_string_language_ids(USB_DEVICE *device, USB_STRING_DESCRIPTOR_LANGIDS *languageids);

uint32_t STDCALL usb_device_read_string_descriptor(USB_DEVICE *device, uint8_t index, char *value, uint32_t len);
uint32_t STDCALL usb_device_read_string_descriptor_ex(USB_DEVICE *device, uint8_t index, uint16_t languageid, char *value, uint32_t len);
uint32_t STDCALL usb_device_read_string_descriptor_w(USB_DEVICE *device, uint8_t index, WCHAR *value, uint32_t len);
uint32_t STDCALL usb_device_read_string_descriptor_ex_w(USB_DEVICE *device, uint8_t index, uint16_t languageid, WCHAR *value, uint32_t len);

uint32_t STDCALL usb_device_get_configuration_descriptor(USB_DEVICE *device, uint8_t index, void *data, uint16_t length);

uint32_t STDCALL usb_device_get_configuration(USB_DEVICE *device, uint8_t *configurationvalue);
uint32_t STDCALL usb_device_set_configuration(USB_DEVICE *device, uint8_t configurationvalue);
USB_CONFIGURATION * STDCALL usb_device_find_configuration_by_value(USB_DEVICE *device, uint8_t configurationvalue);

USB_HUB * STDCALL usb_device_get_hub(USB_DEVICE *device);
USB_PORT * STDCALL usb_device_get_port(USB_DEVICE *device);

uint32_t STDCALL usb_device_get_interface(USB_DEVICE *device, uint8_t index, uint8_t *alternatesetting);
uint32_t STDCALL usb_device_set_interface(USB_DEVICE *device, uint8_t index, uint8_t alternatesetting);
USB_INTERFACE * STDCALL usb_device_find_interface_by_index(USB_DEVICE *device, uint8_t index);
USB_INTERFACE * STDCALL usb_device_find_interface_by_class_only(USB_DEVICE *device, uint8_t interfaceclass);
USB_INTERFACE * STDCALL usb_device_find_interface_by_class(USB_DEVICE *device, uint8_t interfaceclass, uint8_t interfacesubclass, uint8_t interfaceprotocol);

USB_ENDPOINT_DESCRIPTOR * STDCALL usb_device_find_endpoint_by_index(USB_DEVICE *device, USB_INTERFACE *interrface, uint8_t index);
USB_ENDPOINT_DESCRIPTOR * STDCALL usb_device_find_endpoint_by_type(USB_DEVICE *device, USB_INTERFACE *interrface, uint8_t direction, uint8_t transfertype);
USB_ENDPOINT_DESCRIPTOR * STDCALL usb_device_find_endpoint_by_type_ex(USB_DEVICE *device, USB_INTERFACE *interrface, uint8_t direction, uint8_t transfertype, uint8_t *index);

uint8_t STDCALL usb_device_count_endpoints_by_type(USB_DEVICE *device, USB_INTERFACE *interrface, uint8_t direction, uint8_t transfertype);

USB_ALTERNATE * STDCALL usb_device_find_alternate_by_index(USB_DEVICE *device, USB_INTERFACE *interrface, uint8_t index);
USB_ALTERNATE * STDCALL usb_device_find_alternate_by_setting(USB_DEVICE *device, USB_INTERFACE *interrface, uint8_t alternatesetting);

USB_ENDPOINT_DESCRIPTOR * STDCALL usb_device_find_alternate_endpoint_by_index(USB_DEVICE *device, USB_INTERFACE *interrface, USB_ALTERNATE *alternate, uint8_t index);
USB_ENDPOINT_DESCRIPTOR * STDCALL usb_device_find_alternate_endpoint_by_type(USB_DEVICE *device, USB_INTERFACE *interrface, USB_ALTERNATE *alternate, uint8_t direction, uint8_t transfertype);

uint32_t STDCALL usb_device_set_feature(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, uint16_t feature, uint16_t index);
uint32_t STDCALL usb_device_clear_feature(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, uint16_t feature);

uint32_t STDCALL usb_device_set_state(USB_DEVICE *device, uint32_t state);
uint32_t STDCALL usb_device_set_status(USB_DEVICE *device, uint32_t status);

uint32_t STDCALL usb_device_bind(USB_DEVICE *device);
uint32_t STDCALL usb_device_unbind(USB_DEVICE *device, USB_DRIVER *driver);

uint32_t STDCALL usb_device_attach(USB_DEVICE *device);
uint32_t STDCALL usb_device_detach(USB_DEVICE *device);

USB_DEVICE * STDCALL usb_device_allocate(USB_HOST *host, USB_DEVICE *parent);
uint32_t STDCALL usb_device_release(USB_DEVICE *device);

USB_DEVICE * STDCALL usb_device_find(uint32_t usbid);
USB_DEVICE * STDCALL usb_device_find_by_id(uint16_t vendorid, uint16_t productid);
USB_DEVICE * STDCALL usb_device_find_by_name(char *name);
USB_DEVICE * STDCALL usb_device_find_by_description(char *description);
uint32_t STDCALL usb_device_enumerate(usb_device_enumerate_cb callback, void *data);

uint32_t STDCALL usb_device_notification(USB_DEVICE *device, usb_device_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

// Driver Methods
USB_DRIVER * STDCALL usb_driver_create(void);
USB_DRIVER * STDCALL usb_driver_create_ex(uint32_t size);
uint32_t STDCALL usb_driver_destroy(USB_DRIVER *driver);

uint32_t STDCALL usb_driver_register(USB_DRIVER *driver);
uint32_t STDCALL usb_driver_deregister(USB_DRIVER *driver);

USB_DRIVER * STDCALL usb_driver_find(uint32_t driverid);
USB_DRIVER * STDCALL usb_driver_find_by_name(char *name);
uint32_t STDCALL usb_driver_enumerate(usb_driver_enumerate_cb callback, void *data);

// Host Methods
uint32_t STDCALL usb_host_set_state(USB_HOST *host, uint32_t state);

USB_HOST * STDCALL usb_host_create(void);
USB_HOST * STDCALL usb_host_create_ex(uint32_t size);
uint32_t STDCALL usb_host_destroy(USB_HOST *host);

uint32_t STDCALL usb_host_register(USB_HOST *host);
uint32_t STDCALL usb_host_deregister(USB_HOST *host);

USB_HOST * STDCALL usb_host_find(uint32_t hostid);
USB_HOST * STDCALL usb_host_find_by_name(char *name);
USB_HOST * STDCALL usb_host_find_by_description(char *description);
uint32_t STDCALL usb_host_enumerate(usb_host_enumerate_cb callback, void *data);

uint32_t STDCALL usb_host_notification(USB_HOST *host, usb_host_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

// Buffer Methods
void * STDCALL usb_buffer_allocate(USB_DEVICE *device, uint32_t size);
void * STDCALL usb_buffer_allocate_ex(USB_DEVICE *device, uint32_t size, uint32_t *flags);
uint32_t STDCALL usb_buffer_validate(USB_DEVICE *device, void *buffer, uint32_t size, uint32_t *flags);
uint32_t STDCALL usb_buffer_release(void *buffer);

// Request Methods
USB_REQUEST * STDCALL usb_request_allocate(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, usb_request_completed_cb callback, uint32_t size, void *driverdata);
USB_REQUEST * STDCALL usb_request_allocate_ex(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, usb_request_completed_cb callback, void *data, uint32_t size, void *driverdata);
uint32_t STDCALL usb_request_release(USB_REQUEST *request);
uint32_t STDCALL usb_request_initialize(USB_REQUEST *request, usb_request_completed_cb callback, void *data, uint32_t size, void *driverdata);

uint32_t STDCALL usb_request_submit(USB_REQUEST *request);
uint32_t STDCALL usb_request_cancel(USB_REQUEST *request);

// Control Methods
uint32_t STDCALL usb_control_request(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, uint8_t brequest, uint8_t bmrequesttype, uint16_t wvalue, uint16_t windex, void *data, uint16_t wlength);
uint32_t STDCALL usb_control_request_ex(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, uint8_t brequest, uint8_t bmrequesttype, uint16_t wvalue, uint16_t windex, void *data, uint16_t wlength, uint32_t timeout, BOOL allowshort);

// Synchronous Transfer Methods
uint32_t STDCALL usb_control_transfer(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, uint8_t brequest, uint8_t bmrequesttype, uint16_t wvalue, uint16_t windex, void *data, uint16_t wlength, uint32_t *count, uint32_t timeout);
uint32_t STDCALL usb_bulk_transfer(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, void *data, uint32_t size, uint32_t *count, uint32_t timeout);
uint32_t STDCALL usb_interrupt_transfer(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *endpoint, void *data, uint32_t size, uint32_t *count, uint32_t timeout);

/* ============================================================================== */
/* USB Hub Functions */
// Hub Methods
uint32_t STDCALL usb_hub_create_ports(USB_HUB *hub);
uint32_t STDCALL usb_hub_power_on_ports(USB_HUB *hub);

uint32_t STDCALL usb_hub_create_hub_descriptor(USB_HUB *hub);
uint32_t STDCALL usb_hub_read_hub_descriptor(USB_HUB *hub);

uint32_t STDCALL usb_hub_lock(USB_HUB *hub);
uint32_t STDCALL usb_hub_unlock(USB_HUB *hub);

uint32_t STDCALL usb_hub_set_state(USB_HUB *hub, uint32_t state);

USB_HUB * STDCALL usb_hub_allocate(USB_DEVICE *device);
uint32_t STDCALL usb_hub_release(USB_HUB *hub);

USB_HUB * STDCALL usb_hub_find(uint32_t hubid);
USB_HUB * STDCALL usb_hub_find_by_name(char *name);
USB_HUB * STDCALL usb_hub_find_by_description(char *description);
uint32_t STDCALL usb_hub_enumerate(usb_hub_enumerate_cb callback, void *data);

uint32_t STDCALL usb_hub_notification(USB_HUB *hub, usb_hub_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

void STDCALL usb_hub_bind_devices(USB_DEVICE *device, usb_device_bind_proc callback);
void STDCALL usb_hub_unbind_devices(USB_DEVICE *device, USB_DRIVER *driver, usb_device_unbind_proc callback);
void STDCALL usb_hub_enumerate_devices(USB_DEVICE *device, usb_device_enumerate_cb callback, void *data);

// Hub Port Methods
uint32_t STDCALL usb_hub_port_reset(USB_PORT *port, uint32_t delay);

uint32_t STDCALL usb_hub_port_disable(USB_PORT *port);

uint32_t STDCALL usb_hub_port_power_on(USB_PORT *port);
uint32_t STDCALL usb_hub_port_power_off(USB_PORT *port);

uint32_t STDCALL usb_hub_port_get_status(USB_PORT *port);

uint32_t STDCALL usb_hub_port_set_feature(USB_PORT *port, uint16_t feature);
uint32_t STDCALL usb_hub_port_clear_feature(USB_PORT *port, uint16_t feature);
uint32_t STDCALL usb_hub_port_change_feature(USB_PORT *port, uint16_t feature, BOOL enable);

uint32_t STDCALL usb_hub_port_attach_device(USB_PORT *port);
uint32_t STDCALL usb_hub_port_detach_device(USB_PORT *port);

uint32_t STDCALL usb_hub_port_status_changed(USB_PORT *port);

/* ============================================================================== */
/* USB Device, Driver and Host Helper Functions */
uint32_t STDCALL usb_device_get_count(void);

USB_DEVICE * STDCALL usb_device_check(USB_DEVICE *device);

uint32_t STDCALL usb_driver_get_count(void);

USB_DRIVER * STDCALL usb_driver_check(USB_DRIVER *driver);

uint32_t STDCALL usb_host_get_count(void);

USB_HOST * STDCALL usb_host_check(USB_HOST *host);

BOOL STDCALL usb_is_hub(USB_DEVICE *device);
BOOL STDCALL usb_is_root_hub(USB_DEVICE *device);

BOOL STDCALL usb_is_control_request(USB_REQUEST *request);
BOOL STDCALL usb_is_bulk_request(USB_REQUEST *request);
BOOL STDCALL usb_is_interrupt_request(USB_REQUEST *request);
BOOL STDCALL usb_is_isochronous_request(USB_REQUEST *request);

BOOL STDCALL usb_is_in_endpoint(USB_ENDPOINT_DESCRIPTOR *endpoint);
BOOL STDCALL usb_is_out_endpoint(USB_ENDPOINT_DESCRIPTOR *endpoint);

BOOL STDCALL usb_is_bulk_endpoint(USB_ENDPOINT_DESCRIPTOR *endpoint);
BOOL STDCALL usb_is_interrupt_endpoint(USB_ENDPOINT_DESCRIPTOR *endpoint);
BOOL STDCALL usb_is_isochronous_endpoint(USB_ENDPOINT_DESCRIPTOR *endpoint);

uint32_t STDCALL usb_status_to_string(uint32_t status, char *string, uint32_t len);

uint32_t STDCALL usb_device_type_to_string(uint32_t usbtype, char *string, uint32_t len);
uint32_t STDCALL usb_device_state_to_string(uint32_t usbstate, char *string, uint32_t len);
uint32_t STDCALL usb_device_status_to_string(uint32_t usbstatus, char *string, uint32_t len);

uint32_t STDCALL usb_device_state_to_notification(uint32_t state);
uint32_t STDCALL usb_device_status_to_notification(uint32_t status);

uint32_t STDCALL usb_host_type_to_string(uint32_t hosttype, char *string, uint32_t len);
uint32_t STDCALL usb_host_state_to_string(uint32_t hoststate, char *string, uint32_t len);

uint32_t STDCALL usb_host_state_to_notification(uint32_t state);

void STDCALL usb_log_device_configuration(USB_DEVICE *device, usb_log_output_proc output, void *data);
void STDCALL usb_log_device_descriptor(USB_DEVICE *device, USB_DEVICE_DESCRIPTOR *descriptor, usb_log_output_proc output, void *data);
void STDCALL usb_log_configuration_descriptor(USB_DEVICE *device, USB_CONFIGURATION_DESCRIPTOR *descriptor, usb_log_output_proc output, void *data);
void STDCALL usb_log_interface_descriptor(USB_DEVICE *device, USB_INTERFACE_DESCRIPTOR *descriptor, usb_log_output_proc output, void *data);
void STDCALL usb_log_endpoint_descriptor(USB_DEVICE *device, USB_ENDPOINT_DESCRIPTOR *descriptor, usb_log_output_proc output, void *data);

uint32_t STDCALL usb_log_devices(void);
uint32_t STDCALL usb_log_devices_ex(USB_DEVICE *device, usb_log_output_proc output, usb_device_enumerate_cb devicecallback, usb_device_enumerate_cb treecallback, void *data);

uint32_t STDCALL usb_log_device_callback(USB_DEVICE *device, void *data);
uint32_t STDCALL usb_log_tree_callback(USB_DEVICE *device, void *data);

/* ============================================================================== */
/* USB Hub Helper Functions */
uint32_t STDCALL usb_hub_get_count(void);

USB_HUB * STDCALL usb_hub_check(USB_HUB *hub);

BOOL STDCALL usb_hub_is_multi_tt(USB_HUB *hub);
BOOL STDCALL usb_hub_is_compound(USB_HUB *hub);

BOOL STDCALL usb_hub_has_port_indicator(USB_HUB *hub);
BOOL STDCALL usb_hub_has_port_power_switching(USB_HUB *hub);
BOOL STDCALL usb_hub_has_port_current_protection(USB_HUB *hub);

uint8_t STDCALL usb_hub_get_tt_think_time(USB_HUB *hub);

uint32_t STDCALL usb_hub_type_to_string(uint32_t hubtype, char *string, uint32_t len);
uint32_t STDCALL usb_hub_state_to_string(uint32_t hubstate, char *string, uint32_t len);

uint32_t STDCALL usb_hub_state_to_notification(uint32_t state);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_USB_H