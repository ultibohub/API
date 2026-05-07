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
#ifndef _ULTIBO_PS2_H
#define _ULTIBO_PS2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globalconst.h"

/** PS2 specific constants */
/** Keyboard command constants (See: http://wiki.osdev.org/PS/2_Keyboard) */
#define PS2_KEYBOARD_COMMAND_SET_LEDS	0xED ///< Set LEDS (Data: See below)
#define PS2_KEYBOARD_COMMAND_ECHO	0xEE ///< Echo (Data: None)
#define PS2_KEYBOARD_COMMAND_SCANCODE	0xF0 ///< Get/set current scan code (Data: See below)
#define PS2_KEYBOARD_COMMAND_IDENTIFY	0xF2 ///< Identify (Data: None) (See: http://wiki.osdev.org/%228042%22_PS/2_Controller#Detecting_PS.2F2_Device_Types)
#define PS2_KEYBOARD_COMMAND_SET_RATE_DELAY	0xF3 ///< Set typematic rate and delay (Data: See below)
#define PS2_KEYBOARD_COMMAND_ENABLE_SCAN	0xF4 ///< Enable scanning (keyboard will send scan codes) (Data: None)
#define PS2_KEYBOARD_COMMAND_DISABLE_SCAN	0xF5 ///< Disable scanning (keyboard won't send scan codes) (Data: None) Note: May also restore default parameters
#define PS2_KEYBOARD_COMMAND_SET_DEFAULTS	0xF6 ///< Set default parameters  (Data: None)
#define PS2_KEYBOARD_COMMAND_SET_ALL_TYPEMATIC_ONLY	0xF7 ///< Set all keys to typematic/autorepeat only (Scancode set 3 only) (Data: None)
#define PS2_KEYBOARD_COMMAND_SET_ALL_MAKE_RELEASE	0xF8 ///< Set all keys to make/release (Scancode set 3 only) (Data: None)
#define PS2_KEYBOARD_COMMAND_SET_ALL_MAKE_ONLY	0xF9 ///< Set all keys to make only (Scancode set 3 only) (Data: None)
#define PS2_KEYBOARD_COMMAND_SET_ALL_MAKE_TYPEMATIC	0xFA ///< Set all keys to typematic/autorepeat/make/release (Scancode set 3 only) (Data: None)
#define PS2_KEYBOARD_COMMAND_SET_TYPEMATIC_ONLY	0xFB ///< Set specific key to typematic/autorepeat only (Scancode set 3 only)  (Data: Scancode for key)
#define PS2_KEYBOARD_COMMAND_SET_MAKE_RELEASE	0xFC ///< Set specific key to make/release (Scancode set 3 only) (Data: Scancode for key)
#define PS2_KEYBOARD_COMMAND_SET_MAKE_ONLY	0xFD ///< Set specific key to make only (Scancode set 3 only) (Data: Scancode for key)
#define PS2_KEYBOARD_COMMAND_RESEND	0xFE ///< Resend last byte (Data: None)
#define PS2_KEYBOARD_COMMAND_RESET	0xFF ///< Reset and start self-test (Data: None)

#define PS2_KEYBOARD_SET_LEDS_SCROLLLOCK	(1 << 0) ///< ScrollLock
#define PS2_KEYBOARD_SET_LEDS_NUMLOCK	(1 << 1) ///< NumberLock
#define PS2_KEYBOARD_SET_LEDS_CAPSLOCK	(1 << 2) ///< CapsLock

#define PS2_KEYBOARD_SCANCODE_GET	0 ///< Get current scan code set
#define PS2_KEYBOARD_SCANCODE_SET1	1 ///< Set scan code set 1
#define PS2_KEYBOARD_SCANCODE_SET2	2 ///< Set scan code set 2
#define PS2_KEYBOARD_SCANCODE_SET3	3 ///< Set scan code set 3

#define PS2_KEYBOARD_SET_REPEAT_RATE_MASK	0x0F ///< Repeat rate (00000b = 30 Hz, ..., 11111b = 2 Hz)
#define PS2_KEYBOARD_SET_DELAY_MASK	0x70 ///< Delay before keys repeat (00b = 250 ms, 01b = 500 ms, 10b = 750 ms, 11b = 1000 ms)
/** Bit 7 Must be zero  */

#define PS2_KEYBOARD_SET_REPEAT_RATE_30_0	0x00 ///< 30.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_26_7	0x01 ///< 26.7cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_24_0	0x02 ///< 24.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_21_8	0x03 ///< 21.8cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_20_7	0x04 ///< 20.7cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_18_5	0x05 ///< 18.5cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_17_1	0x06 ///< 17.1cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_16_0	0x07 ///< 16.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_15_0	0x08 ///< 15.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_13_3	0x09 ///< 13.3cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_12_0	0x0A ///< 12.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_10_9	0x0B ///< 10.9cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_10_0	0x0C ///< 10.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_9_2	0x0D ///< 9.2cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_8_6	0x0E ///< 8.6cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_8_0	0x0F ///< 8.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_7_5	0x10 ///< 7.5cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_6_7	0x11 ///< 6.7cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_6_0	0x12 ///< 6.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_5_5	0x13 ///< 5.5cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_5_0	0x14 ///< 5.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_4_6	0x15 ///< 4.6cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_4_3	0x16 ///< 4.3cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_4_0	0x17 ///< 4.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_3_7	0x18 ///< 3.7cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_3_3	0x19 ///< 3.3cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_3_0	0x1A ///< 3.0cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_2_7	0x1B ///< 2.7cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_2_5	0x1C ///< 2.5cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_2_3	0x1D ///< 2.3cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_2_1	0x1E ///< 2.1cps
#define PS2_KEYBOARD_SET_REPEAT_RATE_2_0	0x1F ///< 2.0cps

#define PS2_KEYBOARD_SET_DELAY_250	0x00 ///< 250ms
#define PS2_KEYBOARD_SET_DELAY_500	0x10 ///< 500ms
#define PS2_KEYBOARD_SET_DELAY_750	0x20 ///< 750ms
#define PS2_KEYBOARD_SET_DELAY_1000	0x30 ///< 1000ms

/** Mouse command constants (See: http://wiki.osdev.org/PS/2_Mouse) */
#define PS2_MOUSE_COMMAND_RESET	0xFF ///< Reset (Data: None)
#define PS2_MOUSE_COMMAND_RESEND	0xFE ///< Resend (Data: None)
#define PS2_MOUSE_COMMAND_SET_DEFAULTS	0xF6 ///< Set Defaults (Data: None)
#define PS2_MOUSE_COMMAND_DISABLE_REPORT	0xF5 ///< Disable Data Reporting (Data: None)
#define PS2_MOUSE_COMMAND_ENABLE_REPORT	0xF4 ///< Enable Data Reporting (Data: None)
#define PS2_MOUSE_COMMAND_SET_SAMPLE_RATE	0xF3 ///< Set Sample Rate (Data: Sample rate, ranges from 10-200)
#define PS2_MOUSE_COMMAND_GET_DEVICE_ID	0xF2 ///< Get Device ID (Data: None) (See: http://wiki.osdev.org/%228042%22_PS/2_Controller#Detecting_PS.2F2_Device_Types)
#define PS2_MOUSE_COMMAND_SET_REMOTE_MODE	0xF0 ///< Set Remote Mode (Data: None)
#define PS2_MOUSE_COMMAND_SET_WRAP_MODE	0xEE ///< Set Wrap Mode (Data: None)
#define PS2_MOUSE_COMMAND_RESET_WRAP_MODE	0xEC ///< Reset Wrap Mode (Data: None)
#define PS2_MOUSE_COMMAND_READ_DATA	0xEB ///< Read Data (Data: None)
#define PS2_MOUSE_COMMAND_SET_STREAM_MODE	0xEA ///< Set Stream Mode (Data: None)
#define PS2_MOUSE_COMMAND_STATUS_REQUEST	0xE9 ///< Status Request (Data: None)
#define PS2_MOUSE_COMMAND_SET_RESOLUTION	0xE8 ///< Set Resolution (Data: See below)

#define PS2_MOUSE_COMMAND_SAMPLE_RATE_10	10 ///< 10 samples/sec
#define PS2_MOUSE_COMMAND_SAMPLE_RATE_20	20 ///< 20 samples/sec
#define PS2_MOUSE_COMMAND_SAMPLE_RATE_40	40 ///< 40 samples/sec
#define PS2_MOUSE_COMMAND_SAMPLE_RATE_60	60 ///< 60 samples/sec
#define PS2_MOUSE_COMMAND_SAMPLE_RATE_80	80 ///< 80 samples/sec
#define PS2_MOUSE_COMMAND_SAMPLE_RATE_100	100 ///< 100 samples/sec
#define PS2_MOUSE_COMMAND_SAMPLE_RATE_200	200 ///< 200 samples/sec

#define PS2_MOUSE_COMMAND_RESOLUTION_1	0x00 ///< 1 count/mm
#define PS2_MOUSE_COMMAND_RESOLUTION_2	0x01 ///< 2 count/mm
#define PS2_MOUSE_COMMAND_RESOLUTION_4	0x02 ///< 4 count/mm
#define PS2_MOUSE_COMMAND_RESOLUTION_5	0x03 ///< 8 count/mm

/** Response constants */
#define PS2_RESPONSE_NONE	0x00 ///< Key detection error or internal buffer overrun
#define PS2_RESPONSE_SELF_TEST_PASS	0xAA ///< Self test passed (sent after "0xFF (reset)" command or keyboard power up)
#define PS2_RESPONSE_ECHO	0xEE ///< Response to "0xEE (echo)" command
#define PS2_RESPONSE_ACK	0xFA ///< Command acknowledged (ACK)
#define PS2_RESPONSE_SELFTEST_FAIL1	0xFC ///< Self test failed (sent after "0xFF (reset)" command or keyboard power up)
#define PS2_RESPONSE_SELFTEST_FAIL2	0xFD ///< Self test failed (sent after "0xFF (reset)" command or keyboard power up)
#define PS2_RESPONSE_RESEND	0xFE ///< Resend (keyboard wants controller to repeat last command it sent)
#define PS2_RESPONSE_ERROR	0xFF ///< Key detection error or internal buffer overrun

/** Mouse packet bits */
#define PS2_MOUSE_BITS_YO	(1 << 7) ///< Y-Axis Overflow
#define PS2_MOUSE_BITS_XO	(1 << 6) ///< X-Axis Overflow
#define PS2_MOUSE_BITS_YS	(1 << 5) ///< Y-Axis Sign Bit (9-Bit Y-Axis Relative Offset)
#define PS2_MOUSE_BITS_XS	(1 << 4) ///< X-Axis Sign Bit (9-Bit X-Axis Relative Offset)
#define PS2_MOUSE_BITS_AO	(1 << 3) ///< Always One
#define PS2_MOUSE_BITS_BM	(1 << 2) ///< Button Middle (Normally Off = 0)
#define PS2_MOUSE_BITS_BR	(1 << 1) ///< Button Right (Normally Off = 0)
#define PS2_MOUSE_BITS_BL	(1 << 0) ///< Button Left (Normally Off = 0)

/** Keyboard scancode types */
#define PS2_SCANCODE_MAKE	0 ///< Key Down (Press)
#define PS2_SCANCODE_BREAK	1 ///< Key Up (Release)

/** Keyboard scancode counts */
#define PS2_SCANCODE_PC104_COUNT	104
#define PS2_SCANCODE_ACPI_COUNT	3
#define PS2_SCANCODE_MULTIMEDIA_COUNT	18
#define PS2_SCANCODE_COUNT	PS2_SCANCODE_PC104_COUNT + PS2_SCANCODE_ACPI_COUNT + PS2_SCANCODE_MULTIMEDIA_COUNT

/** PS2 specific types */
typedef uint8_t PS2_SCANCODE_DATA[PS2_SCANCODE_COUNT * 2][10];

/** Keyboard types */
typedef struct _PS2_KEYBOARD_SCANCODE PS2_KEYBOARD_SCANCODE;
struct _PS2_KEYBOARD_SCANCODE
{
	uint8_t scancodeset;
	uint8_t scancode[8];
};


/** Mouse types */
typedef struct _PS2_MOUSE_PACKET PS2_MOUSE_PACKET;
struct _PS2_MOUSE_PACKET
{
	uint8_t mousebits; ///< Bits (See PS2_MOUSE_BITS_* above)
	uint8_t mousex; ///< X-Axis Movement Value (Relative)
	uint8_t mousey; ///< Y-Axis Movement Value (Relative)
};

/** PS2 Helper Functions */
uint32_t STDCALL keyboard_leds_to_ps2_leds(uint32_t leds, uint8_t *ps2leds);
uint32_t STDCALL keyboard_rate_and_delay_to_ps2_typematic(uint32_t rate, uint32_t delay, uint8_t *ps2typematic);

uint32_t STDCALL ps2_keyboard_scancode_match(PS2_KEYBOARD_SCANCODE *keyboardscancode, int32_t *index);

uint32_t STDCALL ps2_keyboard_scancode_to_scan_code(PS2_KEYBOARD_SCANCODE *keyboardscancode, int32_t index, uint16_t *scancode);
uint32_t STDCALL ps2_keyboard_scancode_to_modifiers(PS2_KEYBOARD_SCANCODE *keyboardscancode, int32_t index, uint32_t *modifiers);

uint32_t STDCALL mouse_sample_rate_to_ps2_sample_rate(uint32_t rate, uint8_t *ps2rate);

uint32_t STDCALL ps2_mouse_packet_to_mouse_data(PS2_MOUSE_PACKET *mousepacket, MOUSE_DATA *mousedata, uint32_t flags, uint32_t rotation);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PS2_H
