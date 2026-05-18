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
#ifndef _ULTIBO_KEYBOARD_H
#define _ULTIBO_KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/** Keyboard specific constants */
#define KEYBOARD_NAME_PREFIX	"Keyboard" ///< Name prefix for Keyboard Devices

/** Keyboard Device Types */
#define KEYBOARD_TYPE_NONE	0
#define KEYBOARD_TYPE_USB	1
#define KEYBOARD_TYPE_PS2	2
#define KEYBOARD_TYPE_SERIAL	3

#define KEYBOARD_TYPE_MAX	3

/** Keyboard Device States */
#define KEYBOARD_STATE_DETACHED	0
#define KEYBOARD_STATE_DETACHING	1
#define KEYBOARD_STATE_ATTACHING	2
#define KEYBOARD_STATE_ATTACHED	3

#define KEYBOARD_STATE_MAX	3

/** Keyboard Device Flags */
#define KEYBOARD_FLAG_NONE	0x00000000
#define KEYBOARD_FLAG_NON_BLOCK	0x00000001 ///< If set device reads are non blocking (Also supported in Flags parameter of KeyboardReadEx)
#define KEYBOARD_FLAG_DIRECT_READ	0x00000002 ///< If set device writes keyboard data to its local buffer which must be read using KeyboardDeviceRead
#define KEYBOARD_FLAG_PEEK_BUFFER	0x00000004 ///< Peek at the buffer to see if any data is available, don't remove it (Used only in Flags parameter of KeyboardReadEx)

#define KEYBOARD_FLAG_MASK	KEYBOARD_FLAG_NON_BLOCK | KEYBOARD_FLAG_DIRECT_READ | KEYBOARD_FLAG_PEEK_BUFFER

/** Keyboard Device Control Codes */
#define KEYBOARD_CONTROL_GET_FLAG	1 ///< Get Flag
#define KEYBOARD_CONTROL_SET_FLAG	2 ///< Set Flag
#define KEYBOARD_CONTROL_CLEAR_FLAG	3 ///< Clear Flag
#define KEYBOARD_CONTROL_FLUSH_BUFFER	4 ///< Flush Buffer
#define KEYBOARD_CONTROL_GET_LED	5 ///< Get LED
#define KEYBOARD_CONTROL_SET_LED	6 ///< Set LED
#define KEYBOARD_CONTROL_CLEAR_LED	7 ///< Clear LED
#define KEYBOARD_CONTROL_GET_REPEAT_RATE	8 ///< Get Repeat Rate
#define KEYBOARD_CONTROL_SET_REPEAT_RATE	9 ///< Set Repeat Rate
#define KEYBOARD_CONTROL_GET_REPEAT_DELAY	10 ///< Get Repeat Delay
#define KEYBOARD_CONTROL_SET_REPEAT_DELAY	11 ///< Set Repeat Delay

/** Keyboard Device LEDs */
#define KEYBOARD_LED_NONE	0x00000000
#define KEYBOARD_LED_NUMLOCK	0x00000001
#define KEYBOARD_LED_CAPSLOCK	0x00000002
#define KEYBOARD_LED_SCROLLLOCK	0x00000004
#define KEYBOARD_LED_COMPOSE	0x00000008
#define KEYBOARD_LED_KANA	0x00000010

#define KEYBOARD_LED_MASK	KEYBOARD_LED_NUMLOCK | KEYBOARD_LED_CAPSLOCK | KEYBOARD_LED_SCROLLLOCK | KEYBOARD_LED_COMPOSE | KEYBOARD_LED_KANA

/** Keyboard Buffer Size */
#define KEYBOARD_BUFFER_SIZE	512

/** Keyboard Sampling Rate */
#define KEYBOARD_REPEAT_RATE	40 ///< 40msec -> 25cps
#define KEYBOARD_REPEAT_DELAY	10 ///< 10 x KEYBOARD_REPEAT_RATE = 400msec initial delay before repeat

/** Keyboard Data Definitions (Values for TKeyboardData.Modifiers) */
#define KEYBOARD_LEFT_CTRL	0x00000001 ///< The Left Control key is pressed
#define KEYBOARD_LEFT_SHIFT	0x00000002 ///< The Left Shift key is pressed
#define KEYBOARD_LEFT_ALT	0x00000004 ///< The Left Alt key is pressed
#define KEYBOARD_LEFT_GUI	0x00000008 ///< The Left GUI (or Windows) key is pressed
#define KEYBOARD_RIGHT_CTRL	0x00000010 ///< The Right Control key is pressed
#define KEYBOARD_RIGHT_SHIFT	0x00000020 ///< The Right Shift key is pressed
#define KEYBOARD_RIGHT_ALT	0x00000040 ///< The Right Alt key is pressed
#define KEYBOARD_RIGHT_GUI	0x00000080 ///< The Right GUI (or Windows) key is pressed
#define KEYBOARD_NUM_LOCK	0x00000100 ///< Num Lock is currently on
#define KEYBOARD_CAPS_LOCK	0x00000200 ///< Caps Lock is currently on
#define KEYBOARD_SCROLL_LOCK	0x00000400 ///< Scroll Lock is currently on
#define KEYBOARD_COMPOSE	0x00000800 ///< Compose is currently on
#define KEYBOARD_KANA	0x00001000 ///< Kana is currently on
#define KEYBOARD_KEYUP	0x00002000 ///< The key state changed to up
#define KEYBOARD_KEYDOWN	0x00004000 ///< The key state changed to down
#define KEYBOARD_KEYREPEAT	0x00008000 ///< The key is being repeated
#define KEYBOARD_DEADKEY	0x00010000 ///< The key is a being handled as a deadkey
#define KEYBOARD_ALTGR	0x00020000 ///< The AltGr key is pressed (Normally also Right Alt but may be Ctrl-Alt)

/** USB Keyboard specific constants */
/** Note: The following constants are duplicated with the USBKeyboard unit for backwards compatibility */

/** HID Interface Subclass types (See USB HID v1.11 specification) */
#define USB_HID_SUBCLASS_NONE	0 ///< Section 4.2
#define USB_HID_SUBCLASS_BOOT	1 ///< Section 4.2

/** HID Interface Protocol types (See USB HID v1.11 specification) */
#define USB_HID_BOOT_PROTOCOL_NONE	0 ///< Section 4.3
#define USB_HID_BOOT_PROTOCOL_KEYBOARD	1 ///< Section 4.3
#define USB_HID_BOOT_PROTOCOL_MOUSE	2 ///< Section 4.3

/** HID Class Descriptor Types (See USB HID v1.11 specification) */
#define USB_HID_DESCRIPTOR_TYPE_HID	0x21 ///< Section 7.1
#define USB_HID_DESCRIPTOR_TYPE_REPORT	0x22 ///< Section 7.1
#define USB_HID_DESCRIPTOR_TYPE_PHYSICAL_DESCRIPTOR	0x23 ///< Section 7.1

/** HID Request types */
#define USB_HID_REQUEST_GET_REPORT	0x01 ///< Section 7.2
#define USB_HID_REQUEST_GET_IDLE	0x02 ///< Section 7.2
#define USB_HID_REQUEST_GET_PROTOCOL	0x03 ///< Section 7.2
#define USB_HID_REQUEST_SET_REPORT	0x09 ///< Section 7.2
#define USB_HID_REQUEST_SET_IDLE	0x0A ///< Section 7.2
#define USB_HID_REQUEST_SET_PROTOCOL	0x0B ///< Section 7.2

/** HID Protocol types */
#define USB_HID_PROTOCOL_BOOT	0 ///< Section 7.2.5
#define USB_HID_PROTOCOL_REPORT	1 ///< Section 7.2.5

/** HID Report types */
#define USB_HID_REPORT_INPUT	1 ///< Section 7.2.1
#define USB_HID_REPORT_OUTPUT	2 ///< Section 7.2.1
#define USB_HID_REPORT_FEATURE	3 ///< Section 7.2.1

/** HID Report IDs */
#define USB_HID_REPORTID_NONE	0 ///< Section 7.2.1

/** HID Boot Protocol Modifier bits */
#define USB_HID_BOOT_LEFT_CTRL	(1 << 0)
#define USB_HID_BOOT_LEFT_SHIFT	(1 << 1)
#define USB_HID_BOOT_LEFT_ALT	(1 << 2)
#define USB_HID_BOOT_LEFT_GUI	(1 << 3)
#define USB_HID_BOOT_RIGHT_CTRL	(1 << 4)
#define USB_HID_BOOT_RIGHT_SHIFT	(1 << 5)
#define USB_HID_BOOT_RIGHT_ALT	(1 << 6)
#define USB_HID_BOOT_RIGHT_GUI	(1 << 7)

/** HID Boot Protocol Report data */
#define USB_HID_BOOT_REPORT_SIZE	8 ///< Appendix B of HID Device Class Definition 1.11

/** HID Boot Protocol Output bits */
#define USB_HID_BOOT_NUMLOCK_LED	(1 << 0)
#define USB_HID_BOOT_CAPSLOCK_LED	(1 << 1)
#define USB_HID_BOOT_SCROLLLOCK_LED	(1 << 2)
#define USB_HID_BOOT_COMPOSE_LED	(1 << 3)
#define USB_HID_BOOT_KANA_LED	(1 << 4)

#define USB_HID_BOOT_LEDMASK	USB_HID_BOOT_NUMLOCK_LED | USB_HID_BOOT_CAPSLOCK_LED | USB_HID_BOOT_SCROLLLOCK_LED | USB_HID_BOOT_COMPOSE_LED | USB_HID_BOOT_KANA_LED

/** HID Boot Protocol Output data */
#define USB_HID_BOOT_OUTPUT_SIZE	1 ///< Appendix B of HID Device Class Definition 1.11

#define USB_HID_BOOT_USAGE_NUMLOCK	SCAN_CODE_NUMLOCK ///< 83
#define USB_HID_BOOT_USAGE_CAPSLOCK	SCAN_CODE_CAPSLOCK ///< 57
#define USB_HID_BOOT_USAGE_SCROLLLOCK	SCAN_CODE_SCROLLLOCK ///< 71

/** Keyboard specific types */
/** Keyboard Data */
typedef struct _KEYBOARD_DATA KEYBOARD_DATA;
struct _KEYBOARD_DATA
{
	uint32_t modifiers; ///< Keyboard modifier flags for Shift, Alt, Control etc (eg KEYBOARD_LEFT_CTRL)
	uint16_t scancode; ///< Untranslated scan code value from keyboard (See SCAN_CODE_* constants)
	uint16_t keycode; ///< Translated key code value from keyboard (See KEY_CODE_* constants)
	char charcode; ///< ANSI character representing the translated key code
	WCHAR charunicode; ///< Unicode character representing the translated key code
};

/** Keyboard Buffer */
typedef struct _KEYBOARD_BUFFER KEYBOARD_BUFFER;
struct _KEYBOARD_BUFFER
{
	SEMAPHORE_HANDLE wait; ///< Data ready semaphore
	uint32_t start; ///< Index of first buffer ready
	uint32_t count; ///< Number of messages ready in buffer
	KEYBOARD_DATA buffer[KEYBOARD_BUFFER_SIZE];
};

/** Keyboard Device */
typedef struct _KEYBOARD_DEVICE KEYBOARD_DEVICE;

/** Keyboard Enumeration Callback */
typedef uint32_t STDCALL (*keyboard_enumerate_cb)(KEYBOARD_DEVICE *keyboard, void *data);
/** Keyboard Notification Callback */
typedef uint32_t STDCALL (*keyboard_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** Keyboard Device Methods */
typedef uint32_t STDCALL (*keyboard_device_get_proc)(KEYBOARD_DEVICE *keyboard, uint16_t *keycode);
typedef uint32_t STDCALL (*keyboard_device_read_proc)(KEYBOARD_DEVICE *keyboard, void *buffer, uint32_t size, uint32_t *count);
typedef uint32_t STDCALL (*keyboard_device_control_proc)(KEYBOARD_DEVICE *keyboard, int request, size_t argument1, size_t *argument2);

struct _KEYBOARD_DEVICE
{
	// Device Properties
	DEVICE device; ///< The Device entry for this Keyboard
	// Keyboard Properties
	uint32_t keyboardid; ///< Unique Id of this Keyboard in the Keyboard table
	uint32_t keyboardstate; ///< Keyboard state (eg KEYBOARD_STATE_ATTACHED)
	uint32_t keyboardleds; ///< Keyboard LEDs (eg KEYBOARD_LED_NUMLOCK)
	uint32_t keyboardrate; ///< Keyboard repeat rate (Milliseconds)
	uint32_t keyboarddelay; ///< Keyboard repeat delay (Number of KeyboardRate intervals before first repeat)
	keyboard_device_get_proc deviceget; ///< A Device specific DeviceGet method implementing a standard Keyboard device interface (Or nil if the default method is suitable)
	keyboard_device_read_proc deviceread; ///< A Device specific DeviceRead method implementing a standard Keyboard device interface (Or nil if the default method is suitable)
	keyboard_device_control_proc devicecontrol; ///< A Device specific DeviceControl method implementing a standard Keyboard device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; ///< Keyboard lock
	uint16_t code; ///< Scan code of current deadkey (If Applicable)
	uint16_t index; ///< Index state for current deadkey (If Applicable)
	uint32_t modifiers; ///< Modifier state for current deadkey (If Applicable)
	KEYBOARD_BUFFER buffer; ///< Keyboard input buffer
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	uint32_t bufferoverruns;
	// Internal Properties
	KEYBOARD_DEVICE *prev; ///< Previous entry in Keyboard table
	KEYBOARD_DEVICE *next; ///< Next entry in Keyboard table
};

/** USB Keyboard specific types */
/** Note: The following structure is duplicated with the USBKeyboard unit for backwards compatibility */

#ifndef _ULTIBO_MOUSE_H
/** USB HID Descriptor */
typedef struct _USB_HID_DESCRIPTOR USB_HID_DESCRIPTOR;
struct _USB_HID_DESCRIPTOR
{
	uint8_t blength;
	uint8_t bdescriptortype;
	uint16_t bcdhid;
	uint8_t bcountrycode;
	uint8_t bnumdescriptors;
	uint8_t bhiddescriptortype;
	uint16_t whiddescriptorlength;
	// Note: Up to two optional bHIDDescriptorType/wHIDDescriptorLength pairs after the Report descriptor details
} PACKED;
#endif // _ULTIBO_MOUSE_H

/** Keyboard Functions */

/**
 * @brief Get the first key code from the global keyboard buffer
 * @param KeyCode The returned key code read from the buffer (eg KEY_CODE_A)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Key code is the value translated from the scan code using the current keymap
 *        it may not be a character code and it may include non printable characters.
 *
 *        To translate a key code to a character call KeymapGetCharCode()
 */
uint32_t STDCALL keyboard_get(uint16_t *keycode);

/**
 * @brief Peek at the global keyboard buffer to see if any data packets are ready
 * @return ERROR_SUCCESS if packets are ready, ERROR_NO_MORE_ITEMS if not or another error code on failure
 */
uint32_t STDCALL keyboard_peek(void);

/**
 * @brief Read keyboard data packets from the global keyboard buffer
 * @param Buffer Pointer to a buffer to copy the keyboard data packets to
 * @param Size The size of the buffer in bytes (Must be at least TKeyboardData or greater)
 * @param Count The number of keyboard data packets copied to the buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_read(void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Read keyboard data packets from the global keyboard buffer
 * @param Buffer Pointer to a buffer to copy the keyboard data packets to
 * @param Size The size of the buffer in bytes (Must be at least TKeyboardData or greater)
 * @param Flags The flags to use for the read (eg KEYBOARD_FLAG_NON_BLOCK)
 * @param Count The number of keyboard data packets copied to the buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_read_ex(void *buffer, uint32_t size, uint32_t flags, uint32_t *count);

/**
 * @brief Put a scan code and key code in the global keyboard buffer
 * @param ScanCode The scan code to write to the buffer (eg SCAN_CODE_A)
 * @param KeyCode The key code to write to the buffer (eg KEY_CODE_A)
 * @param Modifiers The modifier keys to write to the buffer (eg KEYBOARD_LEFT_CTRL)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_put(uint16_t scancode, uint16_t keycode, uint32_t modifiers);

/**
 * @brief Write keyboard data packets to the global keyboard buffer
 * @param Buffer Pointer to a buffer to copy the keyboard data packets from
 * @param Size The size of the buffer in bytes (Must be at least TKeyboardData or greater)
 * @param Count The number of keyboard data packets to copy from the buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_write(void *buffer, uint32_t size, uint32_t count);

/**
 * @brief Flush the contents of the global keyboard buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_flush(void);

/**
 * @brief Get the first key code from the buffer of the specified keyboard
 * @param Keyboard The keyboard device to get from
 * @param KeyCode The returned key code read from the buffer (eg KEY_CODE_A)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Key code is the value translated from the scan code using the current keymap
 *        it may not be a character code and it may include non printable characters.
 *
 *        To translate a key code to a character call KeymapGetCharCode()
 */
uint32_t STDCALL keyboard_device_get(KEYBOARD_DEVICE *keyboard, uint16_t *keycode);

/**
 * @brief Read keyboard data packets from the buffer of the specified keyboard
 * @param Keyboard The keyboard device to read from
 * @param Buffer Pointer to a buffer to copy the keyboard data packets to
 * @param Size The size of the buffer in bytes (Must be at least TKeyboardData or greater)
 * @param Count The number of keyboard data packets copied to the buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_device_read(KEYBOARD_DEVICE *keyboard, void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Perform a control request on the specified keyboard device
 * @param Keyboard The keyboard device to control
 * @param Request The request code for the operation (eg KEYBOARD_CONTROL_GET_FLAG)
 * @param Argument1 The first argument for the operation (Dependent on request code)
 * @param Argument2 The second argument for the operation (Dependent on request code)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_device_control(KEYBOARD_DEVICE *keyboard, int request, size_t argument1, size_t *argument2);

/**
 * @brief Set the state of the specified keyboard and send a notification
 * @param Keyboard The keyboard to set the state for
 * @param State The new state to set and notify
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_device_set_state(KEYBOARD_DEVICE *keyboard, uint32_t state);

/**
 * @brief Create a new Keyboard device entry
 * @return Pointer to new Keyboard device entry or nil if keyboard could not be created
 */
KEYBOARD_DEVICE * STDCALL keyboard_device_create(void);

/**
 * @brief Create a new Keyboard device entry
 * @param Size Size in bytes to allocate for new keyboard (Including the keyboard device entry)
 * @return Pointer to new Keyboard device entry or nil if keyboard could not be created
 */
KEYBOARD_DEVICE * STDCALL keyboard_device_create_ex(uint32_t size);

/**
 * @brief Destroy an existing Keyboard device entry
 * @param Keyboard The keyboard device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_device_destroy(KEYBOARD_DEVICE *keyboard);

/**
 * @brief Register a new Keyboard device in the Keyboard table
 * @param Keyboard The keyboard device to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_device_register(KEYBOARD_DEVICE *keyboard);

/**
 * @brief Deregister a Keyboard device from the Keyboard table
 * @param Keyboard The keyboard device to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_device_deregister(KEYBOARD_DEVICE *keyboard);

/**
 * @brief Find a keyboard device by ID in the keyboard table
 * @param KeyboardId The ID number of the keyboard to find
 * @return Pointer to keyboard device entry or nil if not found
 */
KEYBOARD_DEVICE * STDCALL keyboard_device_find(uint32_t keyboardid);

/**
 * @brief Find a keyboard device by name in the keyboard table
 * @param Name The name of the keyboard to find (eg Keyboard0)
 * @return Pointer to keyboard device entry or nil if not found
 */
KEYBOARD_DEVICE * STDCALL keyboard_device_find_by_name(const char *name);

/**
 * @brief Find a keyboard device by description in the keyboard table
 * @param Description The description of the keyboard to find (eg USB HID Keyboard)
 * @return Pointer to keyboard device entry or nil if not found
 */
KEYBOARD_DEVICE * STDCALL keyboard_device_find_by_description(const char *description);

/**
 * @brief Enumerate all keyboard devices in the keyboard table
 * @param Callback The callback function to call for each keyboard in the table
 * @param Data A private data pointer to pass to callback for each keyboard in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL keyboard_device_enumerate(keyboard_enumerate_cb callback, void *data);

/**
 * @brief Register a notification for keyboard device changes
 * @param Keyboard The keyboard device to notify changes for (Optional, pass nil for all keyboards)
 * @param Callback The function to call when a notification event occurs
 * @param Data A private data pointer to pass to callback when a notification event occurs
 * @param Notification The events to register for notification of (eg DEVICE_NOTIFICATION_REGISTER)
 * @param Flags The flags to control the notification (eg NOTIFIER_FLAG_WORKER)
 */
uint32_t STDCALL keyboard_device_notification(KEYBOARD_DEVICE *keyboard, keyboard_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/** Keyboard Helper Functions */

/**
 * @brief Get the current keyboard count
 */
uint32_t STDCALL keyboard_get_count(void);

/**
 * @brief Check if the supplied Keyboard is in the keyboard table
 */
KEYBOARD_DEVICE * STDCALL keyboard_device_check(KEYBOARD_DEVICE *keyboard);

uint32_t STDCALL keyboard_device_type_to_string(uint32_t keyboardtype, char *string, uint32_t len);
uint32_t STDCALL keyboard_device_state_to_string(uint32_t keyboardstate, char *string, uint32_t len);

/**
 * @brief Convert a Keyboard state value into the notification code for device notifications
 */
uint32_t STDCALL keyboard_device_state_to_notification(uint32_t state);

/**
 * @brief Remap Ctrl-<Key> combinations to ASCII control codes
 * @note Caller must check for Left-Ctrl or Right-Ctrl modifiers
 */
uint16_t STDCALL keyboard_remap_ctrl_code(uint16_t keycode, uint16_t charcode);

/**
 * @brief Remap the SCAN_CODE_* and KEY_CODE_* values to DOS compatible scan codes
 * @return True if the key was remapped, False if it was not
 * @see http://www.freepascal.org/docs-html/rtl/keyboard/kbdscancode.html
 * @note See below for a version that uses SCAN_CODE_* values instead of translated KEY_CODE_* values
 */
BOOL STDCALL keyboard_remap_key_code(uint16_t scancode, uint16_t keycode, uint8_t *charcode, uint32_t modifiers);

/**
 * @brief Remap the SCAN_CODE_* and KEY_CODE_* values to DOS compatible scan codes
 * @return True if the key was remapped, False if it was not
 * @see http://www.freepascal.org/docs-html/rtl/keyboard/kbdscancode.html
 * @note Same as above except using SCAN_CODE_* values instead of translated KEY_CODE_* values
 */
BOOL STDCALL keyboard_remap_scan_code(uint16_t scancode, uint16_t keycode, uint8_t *charcode, uint32_t modifiers);

/**
 * @brief Insert a TKeyboardData entry into the keyboard buffer (Direct or Global)
 * @param Keyboard The keyboard device to insert data for
 * @param Data The TKeyboardData entry to insert
 * @param Signal If True then signal that new data is available in the buffer
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must hold the keyboard lock
 */
uint32_t STDCALL keyboard_insert_data(KEYBOARD_DEVICE *keyboard, KEYBOARD_DATA *data, BOOL signal);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_KEYBOARD_H