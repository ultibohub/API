/*
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Garry Wood <garry@softoz.com.au>
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
#ifndef _ULTIBO_HID_H
#define _ULTIBO_HID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* HID specific constants */
#define HID_NAME_PREFIX	"HID" // Name prefix for HID Devices

/* HID Device Types */
#define HID_TYPE_NONE	0
#define HID_TYPE_USB	1

#define HID_TYPE_MAX	1

/* HID Device States */
#define HID_STATE_DETACHED	0
#define HID_STATE_DETACHING	1
#define HID_STATE_ATTACHING	2
#define HID_STATE_ATTACHED	3

#define HID_STATE_MAX	3

/* HID Device Flags */
#define HID_FLAG_NONE	0x00000000

/* HID Interface Subclass types (See USB HID v1.11 specification)(Section 4.2) */
#define HID_SUBCLASS_NONE	0
#define HID_SUBCLASS_BOOT	1

/* HID Interface Protocol types (See USB HID v1.11 specification)(Section 4.3) */
#define HID_BOOT_PROTOCOL_NONE	0
#define HID_BOOT_PROTOCOL_KEYBOARD	1
#define HID_BOOT_PROTOCOL_MOUSE	2

/* HID Class Descriptor Types (See USB HID v1.11 specification)(Section 7.1) */
#define HID_DESCRIPTOR_TYPE_HID	0x21
#define HID_DESCRIPTOR_TYPE_REPORT	0x22
#define HID_DESCRIPTOR_TYPE_PHYSICAL_DESCRIPTOR	0x23

/* HID Request types (Section 7.2) */
#define HID_REQUEST_GET_REPORT	0x01
#define HID_REQUEST_GET_IDLE	0x02
#define HID_REQUEST_GET_PROTOCOL	0x03
#define HID_REQUEST_SET_REPORT	0x09
#define HID_REQUEST_SET_IDLE	0x0A
#define HID_REQUEST_SET_PROTOCOL	0x0B

/* HID Protocol types (Section 7.2.5) */
#define HID_PROTOCOL_BOOT	0
#define HID_PROTOCOL_REPORT	1

/* HID Report types (Section 7.2.1) */
#define HID_REPORT_INPUT	1
#define HID_REPORT_OUTPUT	2
#define HID_REPORT_FEATURE	3

/* HID Report IDs (Section 7.2.1) */
#define HID_REPORTID_NONE	0

/* HID Item Sizes (Section 6.2.2.2) */
#define HID_SIZE_0	(0 << 0)
#define HID_SIZE_1	(1 << 0)
#define HID_SIZE_2	(2 << 0)
#define HID_SIZE_4	(3 << 0)
#define HID_SIZE_MASK	0x03

/* HID Item Types (Section 6.2.2.2) */
#define HID_TYPE_MAIN	(0 << 2)
#define HID_TYPE_GLOBAL	(1 << 2)
#define HID_TYPE_LOCAL	(2 << 2)
#define HID_TYPE_RESERVED	(3 << 2)
#define HID_TYPE_MASK	0x0C

/* HID Item Tags (Section 6.2.2.1) */
/* HID Main Item Tags (Section 6.2.2.4) */
#define HID_TAG_MAIN_INPUT	0x80 // Input
#define HID_TAG_MAIN_OUTPUT	0x90 // Output
#define HID_TAG_MAIN_FEATURE	0xB0 // Feature
#define HID_TAG_MAIN_COLLECTION	0xA0 // Collection
#define HID_TAG_MAIN_END_COLLECTION	0xC0 // End Collection

/* HID Global Item Tags (Section 6.2.2.7) */
#define HID_TAG_GLOBAL_USAGE_PAGE	0x04 // Usage Page
#define HID_TAG_GLOBAL_LOGICAL_MINIMUM	0x14 // Logical Minimum
#define HID_TAG_GLOBAL_LOGICAL_MAXIMUM	0x24 // Logical Maximum
#define HID_TAG_GLOBAL_PHYSICAL_MINIMUM	0x34 // Physical Minimum
#define HID_TAG_GLOBAL_PHYSICAL_MAXIMUM	0x44 // Physical Maximum
#define HID_TAG_GLOBAL_UNIT_EXPONENT	0x54 // Unit Exponent
#define HID_TAG_GLOBAL_UNIT	0x64 // Unit
#define HID_TAG_GLOBAL_REPORT_SIZE	0x74 // Report Size
#define HID_TAG_GLOBAL_REPORT_ID	0x84 // Report ID
#define HID_TAG_GLOBAL_REPORT_COUNT	0x94 // Report Count
#define HID_TAG_GLOBAL_PUSH	0xA4 // Push
#define HID_TAG_GLOBAL_POP	0xB4 // Pop

/* HID Local Item Tags (Section 6.2.2.8) */
#define HID_TAG_LOCAL_USAGE	0x08 // Usage
#define HID_TAG_LOCAL_USAGE_MINIMUM	0x18 // Usage Minimum
#define HID_TAG_LOCAL_USAGE_MAXIMUM	0x28 // Usage Maximum
#define HID_TAG_LOCAL_DESIGNATOR_INDEX	0x38 // Designator Index
#define HID_TAG_LOCAL_DESIGNATOR_MINIMUM	0x48 // Designator Minimum
#define HID_TAG_LOCAL_DESIGNATOR_MAXIMUM	0x58 // Designator Maximum
#define HID_TAG_LOCAL_STRING_INDEX	0x78 // String Index
#define HID_TAG_LOCAL_STRING_MINIMUM	0x88 // String Minimum
#define HID_TAG_LOCAL_STRING_MAXIMUM	0x98 // String Maximum
#define HID_TAG_LOCAL_DELIMITER	0xA8 // Delimiter

#define HID_TAG_LONG	0xFC // Always HID_SIZE_2 (Followed by 1 byte DataSize / 1 byte LongItemTag / n bytes Data)
#define HID_TAG_MASK	0xFC

/* HID Main Item Input, Ouput and Feature Values (Section 6.2.2.5) */
#define HID_MAIN_ITEM_CONSTANT	(1 << 0) // Data (0) | Constant (1)
#define HID_MAIN_ITEM_VARIABLE	(1 << 1) // Array (0) | Variable (1)
#define HID_MAIN_ITEM_RELATIVE	(1 << 2) // Absolute (0) | Relative (1)
#define HID_MAIN_ITEM_WRAP	(1 << 3) // No Wrap (0) | Wrap (1)
#define HID_MAIN_ITEM_NON_LINEAR	(1 << 4) // Linear (0) | Non Linear (1)
#define HID_MAIN_ITEM_NO_PREFERRED	(1 << 5) // Preferred State (0) | No Preferred (1)
#define HID_MAIN_ITEM_NULL_STATE	(1 << 6) // No Null position (0) | Null state(1)
#define HID_MAIN_ITEM_RESERVED1	(1 << 7) // Reserved (0)
#define HID_MAIN_ITEM_BUFFERED_BYTES	(1 << 8) // Bit Field (0) | Buffered Bytes (1)
#define HID_MAIN_ITEM_RESERVED2	(0xFFFFFE00 << 9) // Reserved (0)

/* HID Main Item Collection Values (Section 6.2.2.6) */
#define HID_MAIN_COLLECTION_PHYSICAL	0x00 // Physical (Group of axes)
#define HID_MAIN_COLLECTION_APPLICATION	0x01 // Application (Mouse, Keyboard)
#define HID_MAIN_COLLECTION_LOGICAL	0x02 // Logical (Interrelated data)
#define HID_MAIN_COLLECTION_REPORT	0x03 // Report
#define HID_MAIN_COLLECTION_NAMED_ARRAY	0x04 // Named Array
#define HID_MAIN_COLLECTION_USAGE_SWITCH	0x05 // Usage Switch
#define HID_MAIN_COLLECTION_USAGE_MODIFIER	0x06 // Usage Modifier
/* 0x07 to 0x7F Reserved */
/* 0x80 to 0xFF Vendor Defined */

/* HID Global Item Unit Values (Section 6.2.2.7) */
/* For more information see https://physics.nist.gov/cuu/Units/units.html */
#define HID_GLOBAL_UNIT_SYSTEM_MASK	0xF // System of Measurement
#define HID_GLOBAL_UNIT_SYSTEM_SHIFT	0

#define HID_GLOBAL_UNIT_SYSTEM_NONE	0
#define HID_GLOBAL_UNIT_SYSTEM_SI_LINEAR	1 // SI linear unit
#define HID_GLOBAL_UNIT_SYSTEM_SI_ROTATION	2 // SI rotational units
#define HID_GLOBAL_UNIT_SYSTEM_ENGLISH_LINEAR	3 // English (Imperial) linear units
#define HID_GLOBAL_UNIT_SYSTEM_ENGLISH_ROTATION	4 // English (Imperial) rotational units

#define HID_GLOBAL_UNIT_LENGTH_MASK	0xF // Length (Centimeters in SI, Inches in English)
#define HID_GLOBAL_UNIT_LENGTH_SHIFT	4

#define HID_GLOBAL_UNIT_ROTATION_MASK	0xF // Rotation (Radians in SI, Degrees in English)
#define HID_GLOBAL_UNIT_ROTATION_SHIFT	4

#define HID_GLOBAL_UNIT_MASS_MASK	0xF // Mass (Grams in SI, Slugs in English)
#define HID_GLOBAL_UNIT_MASS_SHIFT	8

#define HID_GLOBAL_UNIT_TIME_MASK	0xF // Time (Seconds)
#define HID_GLOBAL_UNIT_TIME_SHIFT	12

#define HID_GLOBAL_UNIT_TEMPERATURE_MASK	0xF // Temperature (Kelvin in SI, Fahrenheit in English)
#define HID_GLOBAL_UNIT_TEMPERATURE_SHIFT	16

#define HID_GLOBAL_UNIT_CURRENT_MASK	0xF // Current (Amperes)
#define HID_GLOBAL_UNIT_CURRENT_SHIFT	20

#define HID_GLOBAL_UNIT_LIGHT_MASK	0xF // Luminous Intensity (Candelas)
#define HID_GLOBAL_UNIT_LIGHT_SHIFT	24

/* Common HID Global Item Unit Values */
/* For a more detailed list see the k.0UNIT definitions in https://github.com/abend0c1/hidrdd/blob/master/rd.rex */
/* SI Base Units */
#define HID_GLOBAL_UNIT_SI_ROTATION	0x00000012 // Rotation (Radians)
#define HID_GLOBAL_UNIT_SI_LENGTH	0x00000011 // Length (Centimeters)
#define HID_GLOBAL_UNIT_SI_MASS	0x00000101 // Mass (Grams)
#define HID_GLOBAL_UNIT_SI_TIME	0x00001001 // Time (Seconds)
#define HID_GLOBAL_UNIT_SI_TEMPERATURE	0x00010001 // Temperature (Kelvin)
#define HID_GLOBAL_UNIT_SI_CURRENT	0x00100001 // Current (Amperes)
#define HID_GLOBAL_UNIT_SI_LIGHT	0x01000001 // Luminous Intensity (Candelas)

/* SI Derived Units */
#define HID_GLOBAL_UNIT_SI_AREA	0x00000021 // Area (Square Centimeters)
#define HID_GLOBAL_UNIT_SI_VOLUME	0x00000031 // Volume (Cubic Centimeters
#define HID_GLOBAL_UNIT_SI_VELOCITY	0x0000F011 // Velocity (Centimeters per second)
#define HID_GLOBAL_UNIT_SI_ACCELERATION	0x0000E011 // Acceleration (Centimeters per second squared)

#define HID_GLOBAL_UNIT_SI_FREQUENCY	0x0000F001 // Frequency (Hertz)
#define HID_GLOBAL_UNIT_SI_FORCE	0x0000E111 // Force (Newtons)
#define HID_GLOBAL_UNIT_SI_PRESSURE	0x0000E1F1 // Pressure (Pascals)
#define HID_GLOBAL_UNIT_SI_ENERGY	0x0000E121 // Energy (Joules)
#define HID_GLOBAL_UNIT_SI_POWER	0x0000D121 // Power (Watts)

/* English Base Units */
#define HID_GLOBAL_UNIT_ENGLISH_ROTATION	0x00000014 // Rotation (Degrees)
#define HID_GLOBAL_UNIT_ENGLISH_LENGTH	0x00000013 // Length (Inches)
#define HID_GLOBAL_UNIT_ENGLISH_TIME	0x00001003 // Time (Seconds)
#define HID_GLOBAL_UNIT_ENGLISH_TEMPERATURE	0x00010003 // Temperature (Fahrenheit)
#define HID_GLOBAL_UNIT_ENGLISH_CURRENT	0x00100003 // Current (Amperes)
#define HID_GLOBAL_UNIT_ENGLISH_LIGHT	0x01000003 // Luminous Intensity (Candelas)

#define HID_GLOBAL_UNIT_ENGLISH_AREA	0x00000023 // Area (Square Inches)
#define HID_GLOBAL_UNIT_ENGLISH_VOLUME	0x00000033 // Volume (Cubic Inches)

/* HID Global Item Unit Exponent Values (Section 6.2.2.7) */
static const unsigned int HID_GLOBAL_UNIT_EXPONENTS[0x10] = {
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	-8,
	-7,
	-6,
	-5,
	-4,
	-3,
	-2,
	-1};

static const double_t HID_GLOBAL_UNIT_MULTIPLIERS[0x10] = {
	1,          // 10^0
	10,         // 10^1
	100,        // 10^2
	1000,       // 10^3
	10000,      // 10^4
	100000,     // 10^5
	1000000,    // 10^6
	10000000,   // 10^7
	0.00000001, // 10^-8
	0.0000001,  // 10^-7
	0.000001,   // 10^-6
	0.00001,    // 10^-5
	0.0001,     // 10^-4
	0.001,      // 10^-3
	0.01,       // 10^-2
	0.1};       // 10^-1

/* HID Local Item Delimiter Values (Section 6.2.2.8) */
#define HID_LOCAL_DELIMITER_CLOSE	0
#define HID_LOCAL_DELIMITER_OPEN	1

/* HID Physical Descriptor Bias Values (Section 6.2.3) */
#define HID_PHYSICAL_BIAS_NONE	(0 << 5) // Not applicable
#define HID_PHYSICAL_BIAS_RIGHT_HAND	(1 << 5) // Right hand
#define HID_PHYSICAL_BIAS_LEFT_HAND	(2 << 5) // Left hand
#define HID_PHYSICAL_BIAS_BOTH_HANDS	(3 << 5) // Both hands
#define HID_PHYSICAL_BIAS_EITHER_HAND	(4 << 5) // Either hand

/* HID Physical Descriptor Designator Values (Section 6.2.3) */
#define HID_PHYSICAL_DESIGNATOR_NONE	0x00 // None
#define HID_PHYSICAL_DESIGNATOR_HAND	0x01 // Hand
#define HID_PHYSICAL_DESIGNATOR_EYEBALL	0x02 // Eyeball
#define HID_PHYSICAL_DESIGNATOR_EYEBROW	0x03 // Eyebrow
#define HID_PHYSICAL_DESIGNATOR_EYELID	0x04 // Eyelid
#define HID_PHYSICAL_DESIGNATOR_EAR	0x05 // Ear
#define HID_PHYSICAL_DESIGNATOR_NOSE	0x06 // Nose
#define HID_PHYSICAL_DESIGNATOR_MOUTH	0x07 // Mouth
#define HID_PHYSICAL_DESIGNATOR_UPPER_LIP	0x08 // Upper lip
#define HID_PHYSICAL_DESIGNATOR_LOWER_LIP	0x09 // Lower lip
#define HID_PHYSICAL_DESIGNATOR_JAW	0x0A // Jaw
#define HID_PHYSICAL_DESIGNATOR_NECK	0x0B // Neck
#define HID_PHYSICAL_DESIGNATOR_UPPER_ARM	0x0C // Upper arm
#define HID_PHYSICAL_DESIGNATOR_ELBOW	0x0D // Elbow
#define HID_PHYSICAL_DESIGNATOR_FOREARM	0x0E // Forearm
#define HID_PHYSICAL_DESIGNATOR_WRIST	0x0F // Wrist
#define HID_PHYSICAL_DESIGNATOR_PALM	0x10 // Palm
#define HID_PHYSICAL_DESIGNATOR_THUMB	0x11 // Thumb
#define HID_PHYSICAL_DESIGNATOR_INDEX_FINGER	0x12 // Index finger
#define HID_PHYSICAL_DESIGNATOR_MIDDLE_FINGER	0x13 // Middle finger
#define HID_PHYSICAL_DESIGNATOR_RING_FINGER	0x14 // Ring finger
#define HID_PHYSICAL_DESIGNATOR_LITTLE_FINGER	0x15 // Little finger
#define HID_PHYSICAL_DESIGNATOR_HEAD	0x16 // Head
#define HID_PHYSICAL_DESIGNATOR_SHOULDER	0x17 // Shoulder
#define HID_PHYSICAL_DESIGNATOR_HIP	0x18 // Hip
#define HID_PHYSICAL_DESIGNATOR_WAIST	0x19 // Waist
#define HID_PHYSICAL_DESIGNATOR_THIGH	0x1A // Thigh
#define HID_PHYSICAL_DESIGNATOR_KNEE	0x1B // Knee
#define HID_PHYSICAL_DESIGNATOR_CALF	0x1C // Calf
#define HID_PHYSICAL_DESIGNATOR_ANKLE	0x1D // Ankle
#define HID_PHYSICAL_DESIGNATOR_FOOT	0x1E // Foot
#define HID_PHYSICAL_DESIGNATOR_HEEL	0x1F // Heel
#define HID_PHYSICAL_DESIGNATOR_BALL_OF_FOOT	0x20 // Ball of foot
#define HID_PHYSICAL_DESIGNATOR_BIG_TOE	0x21 // Big toe
#define HID_PHYSICAL_DESIGNATOR_SECOND_TOE	0x22 // Second toe
#define HID_PHYSICAL_DESIGNATOR_THIRD_TOE	0x23 // Third toe
#define HID_PHYSICAL_DESIGNATOR_FOURTH_TOE	0x24 // Fourth toe
#define HID_PHYSICAL_DESIGNATOR_LITTLE_TOE	0x25 // Little toe
#define HID_PHYSICAL_DESIGNATOR_BROW	0x26 // Brow
#define HID_PHYSICAL_DESIGNATOR_CHEEK	0x27 // Cheek

/* HID Physical Descriptor Qualifier Values (Section 6.2.3) */
#define HID_PHYSICAL_QUALIFIER_NONE	(0 << 5) // Not applicable
#define HID_PHYSICAL_QUALIFIER_RIGHT	(1 << 5) // Right
#define HID_PHYSICAL_QUALIFIER_LEFT	(2 << 5) // Left
#define HID_PHYSICAL_QUALIFIER_BOTH	(3 << 5) // Both
#define HID_PHYSICAL_QUALIFIER_EITHER	(4 << 5) // Either
#define HID_PHYSICAL_QUALIFIER_CENTER	(5 << 5) // Center

/* HID Usage Pages (See HID Usage Tables 1.3) */
#define HID_PAGE_UNDEFINED	0x00 // Undefined
#define HID_PAGE_GENERIC_DESKTOP	0x01 // Generic Desktop Page
#define HID_PAGE_SIMULATION_CONTROLS	0x02 // Simulation Controls Page
#define HID_PAGE_VR_CONTROLS	0x03 // VR Controls Page
#define HID_PAGE_SPORT_CONTROLS	0x04 // Sport Controls Page
#define HID_PAGE_GAME_CONTROLS	0x05 // Game Controls Page
#define HID_PAGE_GENERIC_DEVICE_CONTROLS	0x06 // Generic Device Controls Page
#define HID_PAGE_KEYBOARD_KEYPAD	0x07 // Keyboard/Keypad Page
#define HID_PAGE_LED	0x08 // LED Page
#define HID_PAGE_BUTTON	0x09 // Button Page
#define HID_PAGE_ORDINAL	0x0A // Ordinal Page
#define HID_PAGE_TELEPHONY_DEVICE	0x0B // Telephony Device Page
#define HID_PAGE_CONSUMER	0x0C // Consumer Page
#define HID_PAGE_DIGITIZERS	0x0D // Digitizers Page
#define HID_PAGE_HAPTICS	0x0E // Haptics Page
#define HID_PAGE_PHYSICAL_INPUT_DEVICE	0x0F // Physical Input Device Page
#define HID_PAGE_UNICODE	0x10 // Unicode Page
/* 0x11-0x11 Reserved */
#define HID_PAGE_EYE_AND_HEAD_TRACKERS	0x12 // Eye and Head Trackers Page
/* 0x13-0x13 Reserved */
#define HID_PAGE_AUXILIARY_DISPLAY	0x14 // Auxiliary Display Page
/* 0x15-0x1F Reserved */
#define HID_PAGE_SENSORS	0x20 // Sensors Page
/* 0x21-0x3F Reserved */
#define HID_PAGE_MEDICAL_INSTRUMENT	0x40 // Medical Instrument Page
#define HID_PAGE_BRAILLE_DISPLAY	0x41 // Braille Display Page
/* 0x42-0x58 Reserved */
#define HID_PAGE_LIGHTING_AND_ILLUMINATION	0x59 // Lighting And Illumination Page
/* 0x5A-0x7F Reserved */
#define HID_PAGE_MONITOR	0x80 // Monitor Page
#define HID_PAGE_MONITOR_ENUMERATED	0x81 // Monitor Enumerated Page
#define HID_PAGE_VESA_VIRTUAL_CONTROLS	0x82 // VESA Virtual Controls Page
/* 0x83-0x83 Reserved */
#define HID_PAGE_POWER	0x84 // Power Page
#define HID_PAGE_BATTERY_SYSTEM	0x85 // Battery System Page
/* 0x86-0x8B Reserved */
#define HID_PAGE_BARCODE_SCANNER	0x8C // Barcode Scanner Page
#define HID_PAGE_SCALES	0x8D // Scales Page
#define HID_PAGE_MAGNETIC_STRIPE_READER	0x8E // Magnetic Stripe Reader Page
/* 0x8F-0x8F Reserved */
#define HID_PAGE_CAMERA_CONTROL	0x90 // Camera Control Page
#define HID_PAGE_ARCADE	0x91 // Arcade Page
#define HID_PAGE_GAMING_DEVICE	0x92 // Gaming Device Page
/* 0x93-0xF1CF Reserved */
#define HID_PAGE_FIDO_ALLIANCE	0xF1D0 // FIDO Alliance Page
/* 0xF1D1-0xFEFF Reserved */
#define HID_PAGE_VENDOR_MINIMUM	0xFF00 // Vendor-defined
/* 0xFF00-0xFFFF Vendor-defined */
#define HID_PAGE_VENDOR_MAXIMUM	0xFFFF // Vendor-defined

/* HID Usage Tables (See HID Usage Tables 1.3) */
/* HID Generic Desktop Page (Partial) */
#define HID_DESKTOP_UNDEFINED	0x00 // Undefined
#define HID_DESKTOP_POINTER	0x01 // Pointer
#define HID_DESKTOP_MOUSE	0x02 // Mouse
/* 0x03-0x03 Reserved */
#define HID_DESKTOP_JOYSTICK	0x04 // Joystick
#define HID_DESKTOP_GAMEPAD	0x05 // Gamepad
#define HID_DESKTOP_KEYBOARD	0x06 // Keyboard
#define HID_DESKTOP_KEYPAD	0x07 // Keypad
#define HID_DESKTOP_MULTI_AXIS_CONTROLLER	0x08 // Multi-axis Controller
#define HID_DESKTOP_TABLET_PC_SYSTEM_CONTROLS	0x09 // Tablet PC System Controls
#define HID_DESKTOP_WATER_COOLING_DEVICE	0x0A // Water Cooling Device
#define HID_DESKTOP_COMPUTER_CHASSIS_DEVICE	0x0B // Computer Chassis Device
#define HID_DESKTOP_WIRELESS_RADIO_CONTROLS	0x0C // Wireless Radio Controls
#define HID_DESKTOP_PORTABLE_DEVICE_CONTROL	0x0D // Portable Device Control
#define HID_DESKTOP_SYSTEM_MULTI_AXIS_CONTROLLER	0x0E // System Multi-Axis Controller
#define HID_DESKTOP_SPATIAL_CONTROLLER	0x0F // Spatial Controller
#define HID_DESKTOP_ASSISTIVE_CONTROL	0x10 // Assistive Control
#define HID_DESKTOP_DEVICE_DOCK	0x11 // Device Dock
#define HID_DESKTOP_DOCKABLE_DEVICE	0x12 // Dockable Device
#define HID_DESKTOP_CALL_STATE_MANAGEMENT_CONTROL	0x13 // Call State Management Control
/* 0x14-0x2F Reserved */
#define HID_DESKTOP_X	0x30 // X
#define HID_DESKTOP_Y	0x31 // Y
#define HID_DESKTOP_Z	0x32 // Z
#define HID_DESKTOP_RX	0x33 // Rx
#define HID_DESKTOP_RY	0x34 // Ry
#define HID_DESKTOP_RZ	0x35 // Rz
#define HID_DESKTOP_SLIDER	0x36 // Slider
#define HID_DESKTOP_DIAL	0x37 // Dial
#define HID_DESKTOP_WHEEL	0x38 // Wheel
#define HID_DESKTOP_HAT_SWITCH	0x39 // Hat Switch
#define HID_DESKTOP_COUNTED_BUFFER	0x3A // Counted Buffer
#define HID_DESKTOP_BYTE_COUNT	0x3B // Byte Count
#define HID_DESKTOP_MOTION_WAKEUP	0x3C // Motion Wakeup
#define HID_DESKTOP_START	0x3D // Start
#define HID_DESKTOP_SELECT	0x3E // Select
/* 0x3F-0x3F Reserved */
#define HID_DESKTOP_VX	0x40 // Vx
#define HID_DESKTOP_VY	0x41 // Vy
#define HID_DESKTOP_VZ	0x42 // Vz
#define HID_DESKTOP_VBRX	0x43 // Vbrx
#define HID_DESKTOP_VBRY	0x44 // Vbry
#define HID_DESKTOP_VBRZ	0x45 // Vbrz
#define HID_DESKTOP_VNO	0x46 // Vno
#define HID_DESKTOP_FEATURE_NOTIFICATION	0x47 // Feature Notification
#define HID_DESKTOP_RESOLUTION_MULTIPLIER	0x48 // Resolution Multiplier
#define HID_DESKTOP_QX	0x49 // Qx
#define HID_DESKTOP_QY	0x4A // Qy
#define HID_DESKTOP_QZ	0x4B // Qz
#define HID_DESKTOP_QW	0x4C // Qw

/* HID Keyboard/Keypad Page */
/* Note: These are the same as the SCAN_CODE_* values in GlobalConst */

/* HID LED Page (Partial) */
#define HID_LED_UNDEFINED	00 // Undefined
#define HID_LED_NUM_LOCK	01 // Num Lock
#define HID_LED_CAPS_LOCK	02 // Caps Lock
#define HID_LED_SCROLL_LOCK	03 // Scroll Lock
#define HID_LED_COMPOSE	04 // Compose
#define HID_LED_KANA	05 // Kana
#define HID_LED_POWER	06 // Power
#define HID_LED_SHIFT	07 // Shift
#define HID_LED_DO_NOT_DISTURB	08 // Do Not Disturb
#define HID_LED_MUTE	09 // Mute

/* HID Button Page (Partial) */
#define HID_BUTTON_NONE	0
#define HID_BUTTON_1	1
#define HID_BUTTON_2	2
#define HID_BUTTON_3	3
#define HID_BUTTON_4	4
#define HID_BUTTON_5	5
#define HID_BUTTON_PRIMARY	HID_BUTTON_1
#define HID_BUTTON_SECONDARY	HID_BUTTON_2
#define HID_BUTTON_TERTIARY	HID_BUTTON_3
/* Note: Buttons are defined as Button1 to Button65535 */
#define HID_BUTTON_65535	0xFFFF

/* HID Digitizers Page (Partial) */
#define HID_DIGITIZERS_UNDEFINED	0x00 // Undefined
#define HID_DIGITIZERS_DIGITIZER	0x01 // Digitizer
#define HID_DIGITIZERS_PEN	0x02 // Pen
#define HID_DIGITIZERS_LIGHT_PEN	0x03 // Light Pen
#define HID_DIGITIZERS_TOUCH_SCREEN	0x04 // Touch Screen
#define HID_DIGITIZERS_TOUCH_PAD	0x05 // Touch Pad
#define HID_DIGITIZERS_WHITEBOARD	0x06 // Whiteboard
#define HID_DIGITIZERS_COORD_MEASURING	0x07 // Coordinate Measuring Machine
#define HID_DIGITIZERS_3D_DIGITIZER	0x08 // 3D Digitizer
#define HID_DIGITIZERS_STEREO_PLOTTER	0x09 // Stereo Plotter
#define HID_DIGITIZERS_ARTICULATED_ARM	0x0A // Articulated Arm
#define HID_DIGITIZERS_ARMATURE	0x0B // Armature
#define HID_DIGITIZERS_MULTI_POINT_DIGITIZER	0x0C // Multiple Point Digitizer
#define HID_DIGITIZERS_FREE_SPACE_WAND	0x0D // Free Space Wand
#define HID_DIGITIZERS_DEVICE_CONFIGURATION	0x0E // Device Configuration
#define HID_DIGITIZERS_CAPACITIVE_HEAT_MAP	0x0F // Capacitive Heat Map Digitizer
/* 0x10-0x1F Reserved */
#define HID_DIGITIZERS_STYLUS	0x20 // Stylus
#define HID_DIGITIZERS_PUCK	0x21 // Puck
#define HID_DIGITIZERS_FINGER	0x22 // Finger
#define HID_DIGITIZERS_DEVICE_SETTINGS	0x23 // Device settings
#define HID_DIGITIZERS_CHARACTER_GESTURE	0x24 // Character Gesture
/* 0x25-0x2F Reserved */
#define HID_DIGITIZERS_TIP_PRESSURE	0x30 // Tip Pressure
#define HID_DIGITIZERS_BARREL_PRESSURE	0x31 // Barrel Pressure
#define HID_DIGITIZERS_IN_RANGE	0x32 // In Range
#define HID_DIGITIZERS_TOUCH	0x33 // Touch
#define HID_DIGITIZERS_UNTOUCH	0x34 // Untouch
#define HID_DIGITIZERS_TAP	0x35 // Tap
#define HID_DIGITIZERS_QUALITY	0x36 // Quality
#define HID_DIGITIZERS_DATA_VALID	0x37 // Data Valid
#define HID_DIGITIZERS_TRANSDUCER_INDEX	0x38 // Transducer Index
#define HID_DIGITIZERS_TABLET_FUNCTION_KEYS	0x39 // Tablet Function Keys
#define HID_DIGITIZERS_PROGRAM_CHANGE_KEYS	0x3A // Program Change Keys
#define HID_DIGITIZERS_BATTERY_STRENGTH	0x3B // Battery Strength
#define HID_DIGITIZERS_INVERT	0x3C // Invert
#define HID_DIGITIZERS_X_TILT	0x3D // X Tilt
#define HID_DIGITIZERS_Y_TILT	0x3E // Y Tilt
#define HID_DIGITIZERS_AZIMUTH	0x3F // Azimuth
#define HID_DIGITIZERS_ALTITUDE	0x40 // Altitude
#define HID_DIGITIZERS_TWIST	0x41 // Twist
#define HID_DIGITIZERS_TIP_SWITCH	0x42 // Tip Switch
#define HID_DIGITIZERS_SECONDARY_TIP_SWITCH	0x43 // Secondary Tip Switch
#define HID_DIGITIZERS_BARREL_SWITCH	0x44 // Barrel Switch
#define HID_DIGITIZERS_ERASER	0x45 // Eraser
#define HID_DIGITIZERS_TABLET_PICK	0x46 // Tablet Pick
#define HID_DIGITIZERS_TOUCH_VALID	0x47 // Touch Valid (Confidence)
#define HID_DIGITIZERS_WIDTH	0x48 // Width
#define HID_DIGITIZERS_HEIGHT	0x49 // Height
/* 0x4A-0x50 Reserved */
#define HID_DIGITIZERS_CONTACT_IDENTIFIER	0x51 // Contact Identifier
#define HID_DIGITIZERS_DEVICE_MODE	0x52 // Device Mode
#define HID_DIGITIZERS_DEVICE_IDENTIFIER	0x53 // Device Identifier
#define HID_DIGITIZERS_CONTACT_COUNT	0x54 // Contact Count
#define HID_DIGITIZERS_CONTACT_COUNT_MAXIMUM	0x55 // Contact Count Maximum
#define HID_DIGITIZERS_SCAN_TIME	0x56 // Scan Time

/* ============================================================================== */
/* HID specific types */
/* HID Descriptor  (Section 6.2.1) */
typedef struct _HID_DESCRIPTOR HID_DESCRIPTOR;
struct _HID_DESCRIPTOR
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


/* HID Report Descriptor  (Section 6.2.2) */
typedef void HID_REPORT_DESCRIPTOR;

/* HID Physical Descriptor (Section 6.2.3) */
typedef struct _HID_PHYSICAL_DESCRIPTOR HID_PHYSICAL_DESCRIPTOR;
struct _HID_PHYSICAL_DESCRIPTOR
{
	uint8_t bdesignator; // Indicates which part of the body affects the item
	uint8_t bflags; // Bits specifying flags (7..5 Qualifier / 4..0 Effort)
} PACKED;


typedef struct _HID_PHYSICAL_DESCRIPTOR_SET0 HID_PHYSICAL_DESCRIPTOR_SET0;
struct _HID_PHYSICAL_DESCRIPTOR_SET0
{
	uint8_t bnumber; // Number of Physical Descriptor sets not including Physical Descriptor set 0
	uint16_t wlength; // Length of each Physical descriptor set
} PACKED;


typedef struct _HID_PHYSICAL_DESCRIPTOR_SET HID_PHYSICAL_DESCRIPTOR_SET;
struct _HID_PHYSICAL_DESCRIPTOR_SET
{
	uint8_t bphysicalinfo; // Bits specifying physical information (7..5 Bias / 4..0 Preference)
	HID_PHYSICAL_DESCRIPTOR wphysicaldescriptor[1]; // Physical descriptor data
} PACKED;


/* Structures for HID report parsing */
/* HID State */
typedef struct _HID_STATE HID_STATE;
struct _HID_STATE
{
	// Local State
	uint32_t usage;
	uint32_t usagecount; // Provides UsageMinimum/UsageMaximum
	uint32_t designatorindex;
	uint32_t designatorcount; // Provides DesignatorMinimum/DesignatorMaximum
	uint32_t stringindex;
	uint32_t stringcount; // Provides StringMinimum/StringMaximum
	BOOL delimiter;
	// Global State
	uint16_t usagepage;
	int32_t logicalminimum;
	int32_t logicalmaximum;
	int32_t physicalminimum;
	int32_t physicalmaximum;
	uint32_t unittype;
	uint32_t unitexponent;
	uint32_t reportsize;
	uint32_t reportid;
	uint32_t reportcount;
};


/* HID Stack */
typedef struct _HID_STACK HID_STACK;
struct _HID_STACK
{
	HID_STATE *state;
	HID_STACK *next;
};


/* HID Usage */
typedef struct _HID_USAGE HID_USAGE;
typedef struct _HID_REPORT HID_REPORT; // Forward declared to satisfy HIDUsage
typedef struct _HID_COLLECTION HID_COLLECTION; // Forward declared to satisfy HIDReport

typedef struct _HID_DEVICE HID_DEVICE; // Forward declared to satisfy HIDCollection
typedef struct _HID_CONSUMER HID_CONSUMER; // Forward declared to satisfy HIDCollection

struct _HID_USAGE
{
	uint16_t page; // The usage page this usage refers to
	uint16_t usage; // The usage within the usage page
	uint16_t count; // The total number of sequential usages where Usage represents the minimum value or 1 for a single usage (Usage range is from Usage to Usage + Count - 1)
	uint32_t index; // The index of this usage in the report (First usage is 0)
	uint32_t stringindex; // The string index for this usage
	uint32_t stringcount; // The total number of sequential string index values where string index represents the minimum value or 1 for a single string
	uint32_t designatorindex; // The designator index for this usage
	uint32_t designatorcount; // The total number of sequential designator index values where designator index represents the minimum value or 1 for a single designator
	int32_t logicalminimum; // The logical minimum value for this usage
	int32_t logicalmaximum; // The logical maximum value for this usage
	int32_t physicalminimum; // The physical minimum value for this usage (in Units)
	int32_t physicalmaximum; // The physical maximum value for this usage (in Units)
	uint32_t unittype; // The unit type for this usage
	uint32_t unitexponent; // The unit exponent index for this usage
	HID_USAGE *aliases; // The list of aliased usages for this control (See Delimiters in Section 6.2.2.8)
	uint32_t aliascount; // The number of aliased usages contained for this control
	HID_REPORT *report; // The report this usage belongs to
};


/* HID Report */
struct _HID_REPORT
{
	uint8_t id; // The Id of this report
	uint8_t kind; // The type of report (Input, Output or Feature) (eg HID_REPORT_INPUT)
	uint32_t flags; // The main item flags for this report (eg HID_MAIN_ITEM_VARIABLE)
	uint32_t size; // The number of bits per field in this report
	uint32_t count; // The number of fields in this report
	uint32_t index; // The index of this report in the collection (First report is 0)
	uint32_t sequence; // The sequence of this report in all collections (First report is 0)
	HID_USAGE *usages; // The list of usages contained in this report
	uint32_t usagecount; // The number of usages contained in this report
	HID_COLLECTION *collection; // The collection this report belongs to
};


/* HID Collection */
struct _HID_COLLECTION
{
	uint16_t page; // The usage page this collection refers to (eg HID_PAGE_GENERIC_DESKTOP)
	uint16_t usage; // The usage within the usage page (eg HID_DESKTOP_MOUSE)
	uint32_t flags; // The main item flags for this collection (eg HID_MAIN_COLLECTION_APPLICATION)
	uint32_t start; // The first byte of this collection in the report descriptor
	HID_REPORT *reports; // The list of reports contained in this collection
	uint32_t reportcount; // The number of reports contained in this collection
	HID_COLLECTION *collections; // The list of collections contained in this collection
	uint32_t collectioncount; // The number of collections contained in this collection
	HID_COLLECTION *parent; // The parent collection or nil if this is a top level collection
	HID_DEVICE *device; // The device this collection belongs to
	HID_CONSUMER *consumer; // The consumer which is bound to this collection (or nil if not bound)
	void *privatedata; // Private data for the consumer of this collection
};

/* HID Device */

/* HID Device Enumeration Callback */
typedef uint32_t STDCALL (*hid_device_enumerate_cb)(HID_DEVICE *device, void *data);

/* HID Device Notification Callback */
typedef uint32_t STDCALL (*hid_device_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* HID Device Methods */
typedef uint32_t STDCALL (*hid_device_get_idle_proc)(HID_DEVICE *device, uint16_t *duration, uint8_t reportid);
typedef uint32_t STDCALL (*hid_device_set_idle_proc)(HID_DEVICE *device, uint16_t duration, uint8_t reportid);

typedef uint32_t STDCALL (*hid_device_get_report_proc)(HID_DEVICE *device, uint8_t reporttype, uint8_t reportid, void *reportdata, uint32_t reportsize);
typedef uint32_t STDCALL (*hid_device_set_report_proc)(HID_DEVICE *device, uint8_t reporttype, uint8_t reportid, void *reportdata, uint32_t reportsize);

typedef uint32_t STDCALL (*hid_device_allocate_report_proc)(HID_DEVICE *device, HID_COLLECTION *collection, uint8_t reportid, uint32_t reportsize);
typedef uint32_t STDCALL (*hid_device_release_report_proc)(HID_DEVICE *device, uint8_t reportid);

typedef uint32_t STDCALL (*hid_device_submit_report_proc)(HID_DEVICE *device, uint8_t reportid);
typedef uint32_t STDCALL (*hid_device_cancel_report_proc)(HID_DEVICE *device, uint8_t reportid);

typedef uint32_t STDCALL (*hid_device_get_protocol_proc)(HID_DEVICE *device, uint8_t *protocol);
typedef uint32_t STDCALL (*hid_device_set_protocol_proc)(HID_DEVICE *device, uint8_t protocol);

typedef uint32_t STDCALL (*hid_device_get_interval_proc)(HID_DEVICE *device, uint32_t *interval);
typedef uint32_t STDCALL (*hid_device_set_interval_proc)(HID_DEVICE *device, uint32_t interval);

typedef uint32_t STDCALL (*hid_device_get_report_descriptor_proc)(HID_DEVICE *device, HID_REPORT_DESCRIPTOR *descriptor, uint32_t size);
typedef uint32_t STDCALL (*hid_device_get_physical_descriptor_set0_proc)(HID_DEVICE *device, HID_PHYSICAL_DESCRIPTOR_SET0 *descriptor);
typedef uint32_t STDCALL (*hid_device_get_physical_descriptor_set_proc)(HID_DEVICE *device, HID_PHYSICAL_DESCRIPTOR_SET *descriptor, uint8_t index, uint32_t size);

struct _HID_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this HID
	// HID Properties
	uint32_t hidid; // Unique Id of this HID in the HID device table
	uint32_t hidstate; // HID device state (eg HID_STATE_ATTACHED)
	HID_CONSUMER *consumer; // The consumer which is bound to this device (or nil if not bound)
	hid_device_get_idle_proc devicegetidle; // A device specific GetIdle method (If supported by provider)
	hid_device_set_idle_proc devicesetidle; // A device specific SetIdle method (If supported by provider)
	hid_device_get_report_proc devicegetreport; // A device specific GetReport method (If supported by provider)
	hid_device_set_report_proc devicesetreport; // A device specific SetReport method (If supported by provider)
	hid_device_allocate_report_proc deviceallocatereport; // A device specific AllocateReport method (If supported by provider)
	hid_device_release_report_proc devicereleasereport; // A device specific ReleaseReport method (If supported by provider)
	hid_device_submit_report_proc devicesubmitreport; // A device specific SubmitReport method (If supported by provider)
	hid_device_cancel_report_proc devicecancelreport; // A device specific CancelReport method (If supported by provider)
	hid_device_get_protocol_proc devicegetprotocol; // A device specific GetProtocol method (If supported by provider)
	hid_device_set_protocol_proc devicesetprotocol; // A device specific SetProtocol method (If supported by provider)
	hid_device_get_interval_proc devicegetinterval; // A device specific GetInterval method (If supported by provider)
	hid_device_set_interval_proc devicesetinterval; // A device specific SetInterval method (If supported by provider)
	hid_device_get_report_descriptor_proc devicegetreportdescriptor; // A device specific GetReportDescriptor method (If supported by provider)
	hid_device_get_physical_descriptor_set0_proc devicegetphysicaldescriptorset0; // A device specific GetPhysicalDescriptorSet0 method (If supported by provider)
	hid_device_get_physical_descriptor_set_proc devicegetphysicaldescriptorset; // A device specific GetPhysicalDescriptorSet method (If supported by provider)
	// Driver Properties
	MUTEX_HANDLE lock; // HID device lock
	void *privatedata; // Private data for the consumer of this HID device (If applicable)
	HID_COLLECTION *collections; // The parsed report descriptor with collections, reports and usages
	uint32_t collectioncount; // The number of top level collections contained in the report descriptor
	HID_REPORT_DESCRIPTOR *descriptor; // The raw report descriptor obtained from the device
	uint32_t descriptorsize; // The size of the data pointed to by Descriptor
	// Statistics Properties
	uint32_t receivecount;
	uint32_t receiveerrors;
	// Internal Properties
	HID_DEVICE *prev; // Previous entry in Device table
	HID_DEVICE *next; // Next entry in Device table
};


/* HID Consumer */

/* HID Consumer Enumeration Callback */
typedef uint32_t STDCALL (*hid_consumer_enumerate_cb)(HID_CONSUMER *consumer, void *data);

/* HID Consumer Methods */
typedef uint32_t STDCALL (*hid_device_bind_proc)(HID_DEVICE *device);
typedef uint32_t STDCALL (*hid_device_unbind_proc)(HID_DEVICE *device);

typedef uint32_t STDCALL (*hid_collection_bind_proc)(HID_DEVICE *device, HID_COLLECTION *collection);
typedef uint32_t STDCALL (*hid_collection_unbind_proc)(HID_DEVICE *device, HID_COLLECTION *collection);

typedef uint32_t STDCALL (*hid_report_receive_proc)(HID_COLLECTION *collection, uint8_t reportid, void *reportdata, uint32_t reportsize);

struct _HID_CONSUMER
{
	// Driver Properties
	DRIVER driver; // The Driver entry for this HID Consumer
	// Consumer Properties
	hid_device_bind_proc devicebind; // A Device Bind method to be called when a HID device bind is requested by a provider (Optional)
	hid_device_unbind_proc deviceunbind; // A Device Ubind method to be called when a HID device unbind is requested by a provider (Optional)
	hid_collection_bind_proc collectionbind; // A Collection Bind method to be called when a HID collection bind is requested by a provider (Mandatory)
	hid_collection_unbind_proc collectionunbind; // A Collection Unbind method to be called when a HID collection unbind is requested by a provider (Mandatory)
	hid_report_receive_proc reportreceive; // A Report Receive method to be called when a HID input report is received by a provider (Mandatory)
	// Interface Properties
	MUTEX_HANDLE lock; // Consumer lock
	// Internal Properties
	HID_CONSUMER *prev; // Previous entry in Consumer table
	HID_CONSUMER *next; // Next entry in Consumer table
};


/* Structures for HID consumer report processing */
/* HID Report Extent */
typedef struct _HID_EXTENT HID_EXTENT;
struct _HID_EXTENT
{
	int32_t minimum; // The minimum value for this extent
	int32_t maximum; // The maximum value for this extent
};


/* HID Report Field */
typedef struct _HID_FIELD HID_FIELD;
struct _HID_FIELD
{
	uint16_t page; // The usage page of this field
	uint16_t usage; // The usage within the usage page
	uint32_t count; // The total number of sequential usages where Usage represents the minimum value or 1 for a single usage (Usage range is from Usage to Usage + Count - 1)
	uint32_t flags; // The flags for this field
	uint32_t size; // The length in bytes of this field within the input, output or feature report
	uint32_t bits; // The length in bits of this field within the input, output or feature report
	uint32_t offset; // The byte offset of this field within the input, output or feature report
	uint32_t shift; // The number shift bits to access this field in the input, output or feature report
	HID_EXTENT logical; // The minimum and maximum logical values for this field
	HID_EXTENT physical; // The minimum and maximum physical values for this field
	double_t multiplier; // The conversion multiplier for this field from logical to physical units
	double_t resolution; // The unit resolution for this field in counts per physical unit
	HID_FIELD *next; // The next field in the list
};


/* HID Report Definition */
typedef struct _HID_DEFINITION HID_DEFINITION;
struct _HID_DEFINITION
{
	uint8_t id; // The Id of this report
	uint8_t kind; // The type of this report (Input, Output or Feature)
	uint32_t size; // The total length of this input, output or feature report in bytes (Including the Id byte)
	HID_FIELD *fields; // Linked list of fields in this input, output or feature report
	HID_DEFINITION *next; // The next definition in the list
};

/* ============================================================================== */
/* HID Functions */
uint32_t STDCALL hid_parser_parse_collections(HID_DEVICE *device, HID_COLLECTION **collections, uint32_t *count);
uint32_t STDCALL hid_parser_free_collections(HID_COLLECTION *collections, uint32_t count);

uint32_t STDCALL hid_parser_count_collections(HID_DEVICE *device, HID_COLLECTION *parent);
uint32_t STDCALL hid_parser_count_reports(HID_DEVICE *device, HID_COLLECTION *collection);
uint32_t STDCALL hid_parser_count_usages(HID_DEVICE *device, HID_REPORT *report);

HID_COLLECTION * STDCALL hid_parser_allocate_collection(HID_DEVICE *device, HID_COLLECTION *parent, HID_STATE *state, uint32_t flags, uint32_t start);
HID_REPORT * STDCALL hid_parser_allocate_report(HID_DEVICE *device, HID_COLLECTION *collection, HID_STATE *state, uint8_t kind, uint32_t flags, uint32_t index, uint32_t sequence);
HID_USAGE * STDCALL hid_parser_allocate_usage(HID_DEVICE *device, HID_REPORT *report, HID_STATE *state, uint32_t index);
BOOL STDCALL hid_parser_update_usage(HID_DEVICE *device, HID_REPORT *report, HID_STATE *state, HID_USAGE *usage);
BOOL STDCALL hid_parser_free_usage(HID_DEVICE *device, HID_USAGE *usage);

uint32_t STDCALL hid_parser_pop_stack(HID_STACK *stack, HID_STATE *state);
uint32_t STDCALL hid_parser_push_stack(HID_STACK *stack);
uint32_t STDCALL hid_parser_free_stack(HID_STACK *stack);

uint32_t STDCALL hid_parser_reset_state(HID_STATE *state);
uint32_t STDCALL hid_parser_clean_state(HID_STATE *state);

HID_COLLECTION * STDCALL hid_find_collection(HID_DEVICE *device, uint16_t page, uint16_t usage);

uint32_t STDCALL hid_find_report_ids(HID_DEVICE *device, HID_COLLECTION *collection, uint8_t *minid, uint8_t *maxid);
uint32_t STDCALL hid_find_report_sizes(HID_DEVICE *device, HID_COLLECTION *collection, uint8_t kind, uint32_t *minsize, uint32_t *maxsize);

uint32_t STDCALL hid_count_reports(HID_DEVICE *device, HID_COLLECTION *collection, uint8_t kind, uint8_t id, uint32_t *count);
uint32_t STDCALL hid_find_reports(HID_DEVICE *device, HID_COLLECTION *collection, uint8_t kind, uint8_t id, HID_REPORT *reports, uint32_t count);

HID_DEFINITION * STDCALL hid_allocate_definition(HID_DEVICE *device, HID_COLLECTION *collection, uint8_t kind, uint8_t id);
uint32_t STDCALL hid_free_definition(HID_DEFINITION *definition);

uint32_t STDCALL hid_insert_bit_field(HID_FIELD *field, void *buffer, uint32_t size, BOOL value);
uint32_t STDCALL hid_insert_signed_field(HID_FIELD *field, void *buffer, uint32_t size, int32_t value);
uint32_t STDCALL hid_insert_unsigned_field(HID_FIELD *field, void *buffer, uint32_t size, uint32_t value);

uint32_t STDCALL hid_extract_bit_field(HID_FIELD *field, void *buffer, uint32_t size, BOOL *value);
uint32_t STDCALL hid_extract_signed_field(HID_FIELD *field, void *buffer, uint32_t size, int32_t *value);
uint32_t STDCALL hid_extract_unsigned_field(HID_FIELD *field, void *buffer, uint32_t size, uint32_t *value);

/* ============================================================================== */
/* HID Device Functions */
uint32_t STDCALL hid_device_set_state(HID_DEVICE *device, uint32_t state);

uint32_t STDCALL hid_device_get_idle(HID_DEVICE *device, uint16_t *duration, uint8_t reportid);
uint32_t STDCALL hid_device_set_idle(HID_DEVICE *device, uint16_t duration, uint8_t reportid);

uint32_t STDCALL hid_device_get_report(HID_DEVICE *device, uint8_t reporttype, uint8_t reportid, void *reportdata, uint32_t reportsize);
uint32_t STDCALL hid_device_set_report(HID_DEVICE *device, uint8_t reporttype, uint8_t reportid, void *reportdata, uint32_t reportsize);

uint32_t STDCALL hid_device_allocate_report(HID_DEVICE *device, HID_COLLECTION *collection, uint8_t reportid, uint32_t reportsize);
uint32_t STDCALL hid_device_release_report(HID_DEVICE *device, uint8_t reportid);

uint32_t STDCALL hid_device_submit_report(HID_DEVICE *device, uint8_t reportid);
uint32_t STDCALL hid_device_cancel_report(HID_DEVICE *device, uint8_t reportid);

uint32_t STDCALL hid_device_get_protocol(HID_DEVICE *device, uint8_t *protocol);
uint32_t STDCALL hid_device_set_protocol(HID_DEVICE *device, uint8_t protocol);

uint32_t STDCALL hid_device_get_interval(HID_DEVICE *device, uint32_t *interval);
uint32_t STDCALL hid_device_set_interval(HID_DEVICE *device, uint32_t interval);

uint32_t STDCALL hid_device_get_report_descriptor(HID_DEVICE *device, HID_REPORT_DESCRIPTOR *descriptor, uint32_t size);
uint32_t STDCALL hid_device_get_physical_descriptor_set0(HID_DEVICE *device, HID_PHYSICAL_DESCRIPTOR_SET0 *descriptor);
uint32_t STDCALL hid_device_get_physical_descriptor_set(HID_DEVICE *device, HID_PHYSICAL_DESCRIPTOR_SET *descriptor, uint8_t index, uint32_t size);

uint32_t STDCALL hid_device_bind_device(HID_DEVICE *device);
uint32_t STDCALL hid_device_unbind_device(HID_DEVICE *device, HID_CONSUMER *consumer);

uint32_t STDCALL hid_device_bind_collections(HID_DEVICE *device);
uint32_t STDCALL hid_device_unbind_collections(HID_DEVICE *device, HID_CONSUMER *consumer);

HID_DEVICE * STDCALL hid_device_create(void);
HID_DEVICE * STDCALL hid_device_create_ex(uint32_t size);
uint32_t STDCALL hid_device_destroy(HID_DEVICE *device);

uint32_t STDCALL hid_device_register(HID_DEVICE *device);
uint32_t STDCALL hid_device_deregister(HID_DEVICE *device);

HID_DEVICE * STDCALL hid_device_find(uint32_t hidid);
HID_DEVICE * STDCALL hid_device_find_by_name(char *name);
HID_DEVICE * STDCALL hid_device_find_by_description(char *description);
uint32_t STDCALL hid_device_enumerate(hid_device_enumerate_cb callback, void *data);

uint32_t STDCALL hid_device_notification(HID_DEVICE *device, hid_device_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* HID Consumer Functions */
HID_CONSUMER * STDCALL hid_consumer_create(void);
HID_CONSUMER * STDCALL hid_consumer_create_ex(uint32_t size);
uint32_t STDCALL hid_consumer_destroy(HID_CONSUMER *consumer);

uint32_t STDCALL hid_consumer_register(HID_CONSUMER *consumer);
uint32_t STDCALL hid_consumer_deregister(HID_CONSUMER *consumer);

HID_CONSUMER * STDCALL hid_consumer_find(uint32_t consumerid);
HID_CONSUMER * STDCALL hid_consumer_find_by_name(char *name);
uint32_t STDCALL hid_consumer_enumerate(hid_consumer_enumerate_cb callback, void *data);

/* ============================================================================== */
/* HID Helper Functions */
BOOL STDCALL hid_is_bit_field(HID_FIELD *field);
BOOL STDCALL hid_is_byte_field(HID_FIELD *field);
BOOL STDCALL hid_is_word_field(HID_FIELD *field);
BOOL STDCALL hid_is_long_field(HID_FIELD *field);
BOOL STDCALL hid_is_signed_field(HID_FIELD *field);

uint32_t STDCALL hid_page_to_string(uint16_t page, char *string, uint32_t len);
uint32_t STDCALL hid_usage_to_string(uint16_t page, uint16_t usage, uint16_t count, char *string, uint32_t len);

uint32_t STDCALL hid_unit_type_to_string(uint32_t unittype, char *string, uint32_t len);

uint32_t STDCALL hid_report_kind_to_string(uint8_t kind, char *string, uint32_t len);
uint32_t STDCALL hid_report_flags_to_string(uint32_t flags, char *string, uint32_t len);

uint32_t STDCALL hid_collection_flags_to_string(uint32_t flags, char *string, uint32_t len);

/* ============================================================================== */
/* HID Device Helper Functions */
uint32_t STDCALL hid_device_get_count(void);

HID_DEVICE * STDCALL hid_device_check(HID_DEVICE *device);

uint32_t STDCALL hid_device_type_to_string(uint32_t hidtype, char *string, uint32_t len);
uint32_t STDCALL hid_device_state_to_string(uint32_t hidstate, char *string, uint32_t len);

uint32_t STDCALL hid_device_state_to_notification(uint32_t state);

/* ============================================================================== */
/* HID Consumer Helper Functions */
uint32_t STDCALL hid_consumer_get_count(void);

HID_CONSUMER * STDCALL hid_consumer_check(HID_CONSUMER *consumer);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_HID_H