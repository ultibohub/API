/*
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Garry Wood <garry@softoz.com.au>
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
#ifndef _ULTIBO_GLOBALCONST_H
#define _ULTIBO_GLOBALCONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"

/* ============================================================================== */
/* Global constants */
/* Universal error constants */
#define ERROR_SUCCESS	0 // Success
#define NO_ERROR	0 // Success

#define ERROR_INVALID_FUNCTION	1 // Invalid function
#define ERROR_FILE_NOT_FOUND	2 // The file cannot be found
#define ERROR_PATH_NOT_FOUND	3 // The path cannot be found
#define ERROR_TOO_MANY_OPEN_FILES	4 // Too many open files
#define ERROR_ACCESS_DENIED	5 // Access is denied
#define ERROR_INVALID_HANDLE	6 // Invalid handle
#define ERROR_NOT_ENOUGH_MEMORY	(DWORD)8 // Not enough storage is available to process this command

#define ERROR_INVALID_ACCESS	12 // Invalid access
#define ERROR_INVALID_DATA	13 // The data is invalid
#define ERROR_OUTOFMEMORY	14 // Not enough memory is available
#define ERROR_INVALID_DRIVE	15 // Cannot find the drive specified
#define ERROR_CURRENT_DIRECTORY	16 // Current directory cannot be removed
#define ERROR_NOT_SAME_DEVICE	17 // Cannot move the file to a different disk drive
#define ERROR_NO_MORE_FILES	18 // There are no more files
#define ERROR_WRITE_PROTECT	19 // Media is write protected
#define ERROR_BAD_UNIT	20 // Cannot find the device specified
#define ERROR_NOT_READY	21 // The device is not ready
#define ERROR_BAD_COMMAND	22 // The device does not recognise the command

#define ERROR_WRITE_FAULT	29 // The device cannot be written to
#define ERROR_READ_FAULT	30 // The device cannot be read from
#define ERROR_GEN_FAILURE	31 // The device has failed

#define ERROR_NOT_SUPPORTED	50 // The request is not supported

#define ERROR_DEV_NOT_EXIST	55 // The device does not exist

#define ERROR_BAD_DEV_TYPE	66 // Invalid device type

#define ERROR_ALREADY_ASSIGNED	85 // The device name is already in use
#define ERROR_INVALID_PASSWORD	86 // Invalid pasword
#define ERROR_INVALID_PARAMETER	87 // Invalid parameter

#define ERROR_SEM_IS_SET	102 // The semaphore is in use and cannot be closed
#define ERROR_OPEN_FAILED	110 // The file or device could not be opened
#define ERROR_CALL_NOT_IMPLEMENTED	120 // The function is not currently implemented
#define ERROR_INSUFFICIENT_BUFFER	122 // The buffer passed is too small for the requested data
#define ERROR_WAIT_NO_CHILDREN	128 // There are no child processes to wait for

#define ERROR_NOT_LOCKED	158 // The entry is not locked

#define ERROR_LOCK_FAILED	167 // The lock operation failed

#define ERROR_ALREADY_EXISTS	183 // The file or object already exists

#define ERROR_ENVVAR_NOT_FOUND	203 // The environment variable could not be found

#define ERROR_LOCKED	212 // The entry is already locked

#define ERROR_MORE_DATA	234 // More data is available than the provided buffer

#define ERROR_WAIT_TIMEOUT	258 // The operation timed out
#define ERROR_NO_MORE_ITEMS	259 // No more items available

#define ERROR_NOT_OWNER	288 // The current thread is not the owner

#define ERROR_OPERATION_ABORTED	(DWORD)995 // The I/O operation has been aborted because of either a thread exit or an application request
#define ERROR_IO_INCOMPLETE	(DWORD)996 // Overlapped I/O event is not in a signaled state
#define ERROR_IO_PENDING	(DWORD)997 // Overlapped I/O operation is in progress

#define ERROR_CAN_NOT_COMPLETE	1003 // Cannot complete the function

#define ERROR_NOT_FOUND	1168 // The entry or device was not found

#define ERROR_INVALID_ACL	(DWORD)1336 // The access control list (ACL) structure is invalid
#define ERROR_INVALID_SID	(DWORD)1337 // The security ID structure is invalid
#define ERROR_INVALID_SECURITY_DESCR	(DWORD)1338 // The security descriptor structure is invalid

#define ERROR_TIMEOUT	1460 // The operation returned because the timeout expired

#define ERROR_FUNCTION_FAILED	1627 // The function call failed

/* Errors below here have no compatibility equivalent */
#define ERROR_NOT_VALID	1000001 // The entry or device is not valid
#define ERROR_NOT_ASSIGNED	1000002 // The device is not assigned
#define ERROR_IN_USE	1000003 // The device is in use
#define ERROR_OPERATION_FAILED	1000004 // The operation failed
#define ERROR_NOT_OPEN	1000005 // The file or device is not open
#define ERROR_ALREADY_OPEN	1000006 // The file or device is already open
#define ERROR_WAIT_ABANDONED	1000007 // The operation was abandoned
#define ERROR_IN_PROGRESS	1000008 // An operation is already in progress
#define ERROR_RUNTIME_ERROR	1000009 // A run time occurred
#define ERROR_EXCEPTION	1000010 // An exception occurred
#define ERROR_NOT_PROCESSED	1000011 // The entry has not been processed
#define ERROR_NOT_COMPLETED	1000012 // The entry or operation has not completed
#define ERROR_NOT_COMPATIBLE	1000013 // The entry is not compatible for the operation
#define ERROR_CANCELLED	1000014 // The entry or operation has been cancelled
#define ERROR_NOT_EXACT	1000015 // The result of the operation is not exact
#define ERROR_ALREADY_OWNER	1000016 // The current thread is already the owner

#define ERROR_UNKNOWN	0xFFFFFFFF

/* ============================================================================== */
/* Universal value constants */
#define INVALID_HANDLE_VALUE	(HANDLE)-1 // (DWORD)-1;
#define INVALID_FILE_SIZE	(DWORD)0xFFFFFFFF
#define INVALID_SET_FILE_POINTER	(DWORD)-1
#define INVALID_FILE_ATTRIBUTES	(DWORD)-1

/* File position constants */
#define FILE_BEGIN	0
#define FILE_CURRENT	1
#define FILE_END	2

/* File open/create constants */
#define CREATE_NEW	1
#define CREATE_ALWAYS	2
#define OPEN_EXISTING	3
#define OPEN_ALWAYS	4
#define TRUNCATE_EXISTING	5

/* File creation flag constants */
#define FILE_FLAG_WRITE_THROUGH	(DWORD)0x80000000
#define FILE_FLAG_OVERLAPPED	0x40000000
#define FILE_FLAG_NO_BUFFERING	0x20000000
#define FILE_FLAG_RANDOM_ACCESS	0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN	0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE	0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS	0x02000000
#define FILE_FLAG_POSIX_SEMANTICS	0x01000000
#define FILE_FLAG_OPEN_REPARSE_POINT	0x00200000
#define FILE_FLAG_OPEN_NO_RECALL	0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE	0x00080000

/* File attribute constants */
#define FILE_ATTRIBUTE_READONLY	0x00000001
#define FILE_ATTRIBUTE_HIDDEN	0x00000002
#define FILE_ATTRIBUTE_SYSTEM	0x00000004
#define FILE_ATTRIBUTE_DIRECTORY	0x00000010
#define FILE_ATTRIBUTE_ARCHIVE	0x00000020
#define FILE_ATTRIBUTE_DEVICE	0x00000040
#define FILE_ATTRIBUTE_NORMAL	0x00000080
#define FILE_ATTRIBUTE_TEMPORARY	0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE	0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT	0x00000400
#define FILE_ATTRIBUTE_COMPRESSED	0x00000800
#define FILE_ATTRIBUTE_OFFLINE	0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED	0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED	0x00004000

/* Filesystem attribute constants */
#define FS_CASE_SENSITIVE_SEARCH	0x00000001
#define FS_CASE_PRESERVED_NAMES	0x00000002
#define FS_UNICODE_ON_DISK	0x00000004
#define FS_PERSISTENT_ACLS	0x00000008
#define FS_FILE_COMPRESSION	0x00000010
#define FS_VOLUME_QUOTAS	0x00000020
#define FS_SUPPORTS_SPARSE_FILES	0x00000040
#define FS_SUPPORTS_REPARSE_POINTS	0x00000080
#define FS_SUPPORTS_REMOTE_STORAGE	0x00000100
#define FS_VOLUME_IS_COMPRESSED	0x00008000
#define FS_SUPPORTS_OBJECT_IDS	0x00010000
#define FS_SUPPORTS_ENCRYPTION	0x00020000
#define FS_NAMED_STREAMS	0x00040000
#define FS_READ_ONLY_VOLUME	0x00080000

/* File Access Constants */
#define GENERIC_READ	(DWORD)0x80000000
#define GENERIC_WRITE	0x40000000
#define GENERIC_EXECUTE	0x20000000
#define GENERIC_ALL	0x10000000

/* File Share Constants */
#define FILE_SHARE_READ	0x00000001
#define FILE_SHARE_WRITE	0x00000002
#define FILE_SHARE_DELETE	0x00000004

/* Timeout constants */
#define INFINITE	(DWORD)-1

/* TLS constants */
#define TLS_OUT_OF_INDEXES	(DWORD)0xFFFFFFFF

/* Wait constants */
#define WAIT_OBJECT_0	ERROR_SUCCESS + 0
#define WAIT_ABANDONED	0x00000080 + 0 // STATUS_ABANDONED_WAIT_0
#define WAIT_ABANDONED_0	0x00000080 + 0 // STATUS_ABANDONED_WAIT_0
#define WAIT_TIMEOUT	ERROR_WAIT_TIMEOUT
#define WAIT_FAILED	(DWORD)0xFFFFFFFF

#define WAIT_IO_COMPLETION	0x000000C0 // STATUS_USER_APC

#define MAXIMUM_WAIT_OBJECTS	64 // Maximum number of wait objects

/* Thread state constants */
#define STILL_ACTIVE	ERROR_NO_MORE_ITEMS

/* TimeZone constants */
#define TIME_ZONE_ID_INVALID	(DWORD)0xFFFFFFFF

/* ============================================================================== */
/* Universal key code constants */
/* Keyboard key codes are based on the Unicode standard with each key code mapped to the code point for that character (See http://unicode.org or http://unicode-table.com) */
/* Keyboard keymaps map the scan code value to the key code value for the specific keyboard layout and include alternate mappings for Shift and AltGr */
/* Non character codes for keys like Home, End, Arrows, F1..F24, Shift, Caps Lock etc are mapped in the Unicode Private Use Area (E000-F8FF) */
/* These are the values reported in the KeyCode field of the TKeyboardData structure returned by the KeyboardRead function */
/* Control Characters (0000-001F) */
#define KEY_CODE_NONE	0x0000 // 0
#define KEY_CODE_BACKSPACE	0x0008 // 8
#define KEY_CODE_TAB	0x0009 // 9
#define KEY_CODE_ENTER	0x000D // 13
#define KEY_CODE_ESCAPE	0x001B // 27
#define KEY_CODE_DELETE	0x007F // 127

/* Basic Latin Characters (0020-007F) */
/* Punctuation */
#define KEY_CODE_SPACE	0x0020 // 32
#define KEY_CODE_EXCLAMATION	0x0021 // 33
#define KEY_CODE_QUOTATION	0x0022 // 34
#define KEY_CODE_NUMBER	0x0023 // 35
#define KEY_CODE_DOLLAR	0x0024 // 36
#define KEY_CODE_PERCENT	0x0025 // 37
#define KEY_CODE_AMPERSAND	0x0026 // 38
#define KEY_CODE_APOSTROPHE	0x0027 // 39
#define KEY_CODE_LEFT_BRACKET	0x0028 // 40
#define KEY_CODE_RIGHT_BRACKET	0x0029 // 41
#define KEY_CODE_ASTERISK	0x002A // 42
#define KEY_CODE_PLUS	0x002B // 43
#define KEY_CODE_COMMA	0x002C // 44
#define KEY_CODE_MINUS	0x002D // 45
#define KEY_CODE_PERIOD	0x002E // 46
#define KEY_CODE_SLASH	0x002F // 47
/* Numerals */
#define KEY_CODE_0	0x0030 // 48
#define KEY_CODE_1	0x0031 // 49
#define KEY_CODE_2	0x0032 // 50
#define KEY_CODE_3	0x0033 // 51
#define KEY_CODE_4	0x0034 // 52
#define KEY_CODE_5	0x0035 // 53
#define KEY_CODE_6	0x0036 // 54
#define KEY_CODE_7	0x0037 // 55
#define KEY_CODE_8	0x0038 // 56
#define KEY_CODE_9	0x0039 // 57
/* Punctuation */
#define KEY_CODE_COLON	0x003A // 58
#define KEY_CODE_SEMICOLON	0x003B // 59
#define KEY_CODE_LESSTHAN	0x003C // 60
#define KEY_CODE_EQUALS	0x003D // 61
#define KEY_CODE_GREATERTHAN	0x003E // 62
#define KEY_CODE_QUESTION	0x003F // 63
#define KEY_CODE_AT	0x0040 // 64
/* Capital Characters */
#define KEY_CODE_CAPITAL_A	0x0041 // 65
#define KEY_CODE_CAPITAL_B	0x0042 // 66
#define KEY_CODE_CAPITAL_C	0x0043 // 67
#define KEY_CODE_CAPITAL_D	0x0044 // 68
#define KEY_CODE_CAPITAL_E	0x0045 // 69
#define KEY_CODE_CAPITAL_F	0x0046 // 70
#define KEY_CODE_CAPITAL_G	0x0047 // 71
#define KEY_CODE_CAPITAL_H	0x0048 // 72
#define KEY_CODE_CAPITAL_I	0x0049 // 73
#define KEY_CODE_CAPITAL_J	0x004A // 74
#define KEY_CODE_CAPITAL_K	0x004B // 75
#define KEY_CODE_CAPITAL_L	0x004C // 76
#define KEY_CODE_CAPITAL_M	0x004D // 77
#define KEY_CODE_CAPITAL_N	0x004E // 78
#define KEY_CODE_CAPITAL_O	0x004F // 79
#define KEY_CODE_CAPITAL_P	0x0050 // 80
#define KEY_CODE_CAPITAL_Q	0x0051 // 81
#define KEY_CODE_CAPITAL_R	0x0052 // 82
#define KEY_CODE_CAPITAL_S	0x0053 // 83
#define KEY_CODE_CAPITAL_T	0x0054 // 84
#define KEY_CODE_CAPITAL_U	0x0055 // 85
#define KEY_CODE_CAPITAL_V	0x0056 // 86
#define KEY_CODE_CAPITAL_W	0x0057 // 87
#define KEY_CODE_CAPITAL_X	0x0058 // 88
#define KEY_CODE_CAPITAL_Y	0x0059 // 89
#define KEY_CODE_CAPITAL_Z	0x005A // 90
/* Punctuation */
#define KEY_CODE_LEFT_SQUARE	0x005B // 91
#define KEY_CODE_BACKSLASH	0x005C // 92
#define KEY_CODE_RIGHT_SQUARE	0x005D // 93
#define KEY_CODE_CARET	0x005E // 94
#define KEY_CODE_UNDERSCORE	0x005F // 95
#define KEY_CODE_GRAVE	0x0060 // 96
/* Lowercase Characters */
#define KEY_CODE_A	0x0061 // 97
#define KEY_CODE_B	0x0062 // 98
#define KEY_CODE_C	0x0063 // 99
#define KEY_CODE_D	0x0064 // 100
#define KEY_CODE_E	0x0065 // 101
#define KEY_CODE_F	0x0066 // 102
#define KEY_CODE_G	0x0067 // 103
#define KEY_CODE_H	0x0068 // 104
#define KEY_CODE_I	0x0069 // 105
#define KEY_CODE_J	0x006A // 106
#define KEY_CODE_K	0x006B // 107
#define KEY_CODE_L	0x006C // 108
#define KEY_CODE_M	0x006D // 109
#define KEY_CODE_N	0x006E // 110
#define KEY_CODE_O	0x006F // 111
#define KEY_CODE_P	0x0070 // 112
#define KEY_CODE_Q	0x0071 // 113
#define KEY_CODE_R	0x0072 // 114
#define KEY_CODE_S	0x0073 // 115
#define KEY_CODE_T	0x0074 // 116
#define KEY_CODE_U	0x0075 // 117
#define KEY_CODE_V	0x0076 // 118
#define KEY_CODE_W	0x0077 // 119
#define KEY_CODE_X	0x0078 // 120
#define KEY_CODE_Y	0x0079 // 121
#define KEY_CODE_Z	0x007A // 122
/* Punctuation */
#define KEY_CODE_LEFT_BRACE	0x007B // 123
#define KEY_CODE_PIPE	0x007C // 124
#define KEY_CODE_RIGHT_BRACE	0x007D // 125
#define KEY_CODE_TILDE	0x007E // 126
/* KEY_CODE_DELETE (See above) */

/* Latin-1 Supplement Characters (0080-00FF) (Partial, add extras as required) */
#define KEY_CODE_INVERTED_EXCLAMATION	0x00A1
#define KEY_CODE_CENT	0x00A2
#define KEY_CODE_POUND	0x00A3
#define KEY_CODE_CURRENCY	0x00A4
#define KEY_CODE_YEN	0x00A5
#define KEY_CODE_BROKEN_BAR	0x00A6
#define KEY_CODE_SECTION	0x00A7
#define KEY_CODE_DIAERESIS	0x00A8
#define KEY_CODE_COPYRIGHT	0x00A9
#define KEY_CODE_FEMININE	0x00AA
#define KEY_CODE_LEFT_DOUBLE_ANGLE	0x00AB
#define KEY_CODE_NOT	0x00AC
#define KEY_CODE_REGISTERED	0x00AE
#define KEY_CODE_MACRON	0x00AF
#define KEY_CODE_DEGREE	0x00B0
#define KEY_CODE_PLUS_MINUS	0x00B1
#define KEY_CODE_SUPERSCRIPT_2	0x00B2
#define KEY_CODE_SUPERSCRIPT_3	0x00B3
#define KEY_CODE_ACUTE	0x00B4
#define KEY_CODE_MICRO	0x00B5
#define KEY_CODE_PILCROW	0x00B6
#define KEY_CODE_MIDDLE_DOT	0x00B7
#define KEY_CODE_CEDILLA	0x00B8
#define KEY_CODE_SUPERSCRIPT_1	0x00B9
#define KEY_CODE_MASCULINE	0x00BA
#define KEY_CODE_RIGHT_DOUBLE_ANGLE	0x00BB
#define KEY_CODE_ONE_QUARTER	0x00BC
#define KEY_CODE_ONE_HALF	0x00BD
#define KEY_CODE_THREE_QUARTER	0x00BE
#define KEY_CODE_INVERTED_QUESTION	0x00BF
#define KEY_CODE_CAPITAL_GRAVE_A	0x00C0
#define KEY_CODE_CAPITAL_ACUTE_A	0x00C1
#define KEY_CODE_CAPITAL_CIRCUMFLEX_A	0x00C2
#define KEY_CODE_CAPITAL_TILDE_A	0x00C3
#define KEY_CODE_CAPITAL_DIAERESIS_A	0x00C4
#define KEY_CODE_CAPITAL_RING_A	0x00C5
#define KEY_CODE_CAPITAL_AE	0x00C6
#define KEY_CODE_CAPITAL_CEDILLA_C	0x00C7
#define KEY_CODE_CAPITAL_GRAVE_E	0x00C8
#define KEY_CODE_CAPITAL_ACUTE_E	0x00C9
#define KEY_CODE_CAPITAL_CIRCUMFLEX_E	0x00CA
#define KEY_CODE_CAPITAL_DIAERESIS_E	0x00CB
#define KEY_CODE_CAPITAL_GRAVE_I	0x00CC
#define KEY_CODE_CAPITAL_ACUTE_I	0x00CD
#define KEY_CODE_CAPITAL_CIRCUMFLEX_I	0x00CE
#define KEY_CODE_CAPITAL_DIAERESIS_I	0x00CF
#define KEY_CODE_CAPITAL_ETH	0x00D0
#define KEY_CODE_CAPITAL_TILDE_N	0x00D1
#define KEY_CODE_CAPITAL_GRAVE_O	0x00D2
#define KEY_CODE_CAPITAL_ACUTE_O	0x00D3
#define KEY_CODE_CAPITAL_CIRCUMFLEX_O	0x00D4
#define KEY_CODE_CAPITAL_TILDE_O	0x00D5
#define KEY_CODE_CAPITAL_DIAERESIS_O	0x00D6
#define KEY_CODE_MULTIPLY	0x00D7
#define KEY_CODE_CAPITAL_STROKE_O	0x00D8
#define KEY_CODE_CAPITAL_GRAVE_U	0x00D9
#define KEY_CODE_CAPITAL_ACUTE_U	0x00DA
#define KEY_CODE_CAPITAL_CIRCUMFLEX_U	0x00DB
#define KEY_CODE_CAPITAL_DIAERESIS_U	0x00DC
#define KEY_CODE_CAPITAL_ACUTE_Y	0x00DD
#define KEY_CODE_CAPITAL_THORN	0x00DE
#define KEY_CODE_SHARP_S	0x00DF
#define KEY_CODE_GRAVE_A	0x00E0
#define KEY_CODE_ACUTE_A	0x00E1
#define KEY_CODE_CIRCUMFLEX_A	0x00E2
#define KEY_CODE_TILDE_A	0x00E3
#define KEY_CODE_DIAERESIS_A	0x00E4
#define KEY_CODE_RING_A	0x00E5
#define KEY_CODE_AE	0x00E6
#define KEY_CODE_CEDILLA_C	0x00E7
#define KEY_CODE_GRAVE_E	0x00E8
#define KEY_CODE_ACUTE_E	0x00E9
#define KEY_CODE_CIRCUMFLEX_E	0x00EA
#define KEY_CODE_DIAERESIS_E	0x00EB
#define KEY_CODE_GRAVE_I	0x00EC
#define KEY_CODE_ACUTE_I	0x00ED
#define KEY_CODE_CIRCUMFLEX_I	0x00EE
#define KEY_CODE_DIAERESIS_I	0x00EF
#define KEY_CODE_ETH	0x00F0
#define KEY_CODE_TILDE_N	0x00F1
#define KEY_CODE_GRAVE_O	0x00F2
#define KEY_CODE_ACUTE_O	0x00F3
#define KEY_CODE_CIRCUMFLEX_O	0x00F4
#define KEY_CODE_TILDE_O	0x00F5
#define KEY_CODE_DIAERESIS_O	0x00F6
#define KEY_CODE_DIVISION	0x00F7
#define KEY_CODE_STROKE_O	0x00F8
#define KEY_CODE_GRAVE_U	0x00F9
#define KEY_CODE_ACUTE_U	0x00FA
#define KEY_CODE_CIRCUMFLEX_U	0x00FB
#define KEY_CODE_DIAERESIS_U	0x00FC
#define KEY_CODE_ACUTE_Y	0x00FD
#define KEY_CODE_THORN	0x00FE
#define KEY_CODE_DIAERESIS_Y	0x00FF

/* General Punctuation (2000-206F) (Partial, add extras as required) */
#define KEY_CODE_LEFT_QUOTE	0x2018
#define KEY_CODE_RIGHT_QUOTE	0x2019

/* Currency Symbols (20A0-20CF) (Partial, add extras as required) */
#define KEY_CODE_EURO	0x20AC

/* Private Area (E000-F8FF) */
/* Non Character Codes */
#define KEY_CODE_CAPSLOCK	0xE000
#define KEY_CODE_F1	0xE001
#define KEY_CODE_F2	0xE002
#define KEY_CODE_F3	0xE003
#define KEY_CODE_F4	0xE004
#define KEY_CODE_F5	0xE005
#define KEY_CODE_F6	0xE006
#define KEY_CODE_F7	0xE007
#define KEY_CODE_F8	0xE008
#define KEY_CODE_F9	0xE009
#define KEY_CODE_F10	0xE00A
#define KEY_CODE_F11	0xE00B
#define KEY_CODE_F12	0xE00C
#define KEY_CODE_PRINTSCREEN	0xE00D
#define KEY_CODE_SCROLLLOCK	0xE00E
#define KEY_CODE_PAUSE	0xE00F
#define KEY_CODE_INSERT	0xE010
#define KEY_CODE_HOME	0xE011
#define KEY_CODE_PAGEUP	0xE012
#define KEY_CODE_END	0xE013
#define KEY_CODE_PAGEDN	0xE014
#define KEY_CODE_RIGHT_ARROW	0xE015
#define KEY_CODE_LEFT_ARROW	0xE016
#define KEY_CODE_DOWN_ARROW	0xE017
#define KEY_CODE_UP_ARROW	0xE018
#define KEY_CODE_NUMLOCK	0xE019
#define KEY_CODE_APPLICATION	0xE01A
#define KEY_CODE_POWER	0xE01B
#define KEY_CODE_F13	0xE01C
#define KEY_CODE_F14	0xE01D
#define KEY_CODE_F15	0xE01E
#define KEY_CODE_F16	0xE01F
#define KEY_CODE_F17	0xE020
#define KEY_CODE_F18	0xE021
#define KEY_CODE_F19	0xE022
#define KEY_CODE_F20	0xE023
#define KEY_CODE_F21	0xE024
#define KEY_CODE_F22	0xE025
#define KEY_CODE_F23	0xE026
#define KEY_CODE_F24	0xE027
#define KEY_CODE_EXECUTE	0xE028
#define KEY_CODE_HELP	0xE029
#define KEY_CODE_MENU	0xE02A
#define KEY_CODE_SELECT	0xE02B
#define KEY_CODE_STOP	0xE02C
#define KEY_CODE_AGAIN	0xE02D
#define KEY_CODE_UNDO	0xE02E
#define KEY_CODE_CUT	0xE02F
#define KEY_CODE_COPY	0xE030
#define KEY_CODE_PASTE	0xE031
#define KEY_CODE_FIND	0xE032
#define KEY_CODE_MUTE	0xE033
#define KEY_CODE_VOLUMEUP	0xE034
#define KEY_CODE_VOLUMEDOWN	0xE035
#define KEY_CODE_LOCKING_CAPSLOCK	0xE036
#define KEY_CODE_LOCKING_NUMLOCK	0xE037
#define KEY_CODE_LOCKING_SCROLLLOCK	0xE038
#define KEY_CODE_INTERNATIONAL1	0xE039
#define KEY_CODE_INTERNATIONAL2	0xE03A
#define KEY_CODE_INTERNATIONAL3	0xE03B
#define KEY_CODE_INTERNATIONAL4	0xE03C
#define KEY_CODE_INTERNATIONAL5	0xE03D
#define KEY_CODE_INTERNATIONAL6	0xE03E
#define KEY_CODE_INTERNATIONAL7	0xE03F
#define KEY_CODE_INTERNATIONAL8	0xE040
#define KEY_CODE_INTERNATIONAL9	0xE041
#define KEY_CODE_LANG1	0xE042
#define KEY_CODE_LANG2	0xE043
#define KEY_CODE_LANG3	0xE044
#define KEY_CODE_LANG4	0xE045
#define KEY_CODE_LANG5	0xE046
#define KEY_CODE_LANG6	0xE047
#define KEY_CODE_LANG7	0xE048
#define KEY_CODE_LANG8	0xE049
#define KEY_CODE_LANG9	0xE04A
#define KEY_CODE_ALT_ERASE	0xE04B
#define KEY_CODE_SYSREQ	0xE04C
#define KEY_CODE_CANCEL	0xE04D
#define KEY_CODE_CLEAR	0xE04E
#define KEY_CODE_PRIOR	0xE04F
#define KEY_CODE_RETURN	0xE050
#define KEY_CODE_SEPARATOR	0xE051
#define KEY_CODE_OUT	0xE052
#define KEY_CODE_OPER	0xE053
#define KEY_CODE_CLEAR_AGAIN	0xE054
#define KEY_CODE_CRSEL_PROPS	0xE055
#define KEY_CODE_EXSEL	0xE056
#define KEY_CODE_00	0xE057
#define KEY_CODE_000	0xE058
#define KEY_CODE_THOUSANDS_SEPARATOR	0xE059
#define KEY_CODE_DECIMAL_SEPARATOR	0xE05A
#define KEY_CODE_CURRENCY_UNIT	0xE05B
#define KEY_CODE_CURRENCY_SUBUNIT	0xE05C
#define KEY_CODE_XOR	0xE05D
#define KEY_CODE_MEM_STORE	0xE05E
#define KEY_CODE_MEM_RECALL	0xE05F
#define KEY_CODE_MEM_CLEAR	0xE060
#define KEY_CODE_MEM_ADD	0xE061
#define KEY_CODE_MEM_SUBTRACT	0xE062
#define KEY_CODE_MEM_MULTIPLY	0xE063
#define KEY_CODE_MEM_DIVIDE	0xE064
#define KEY_CODE_CLEAR_ENTRY	0xE065
#define KEY_CODE_BINARY	0xE066
#define KEY_CODE_OCTAL	0xE067
#define KEY_CODE_DECIMAL	0xE068
#define KEY_CODE_HEX	0xE069
#define KEY_CODE_CTRL	0xE06A
#define KEY_CODE_SHIFT	0xE06B
#define KEY_CODE_ALT	0xE06C
#define KEY_CODE_GUI	0xE06D
#define KEY_CODE_DOUBLE_AMPERSAND	0xE06E
#define KEY_CODE_DOUBLE_PIPE	0xE06F
#define KEY_CODE_CENTER	0xE070

#define KEY_CODE_TRANSLATE_START	0x0080 // Key codes below this are direct characters in all code pages
#define KEY_CODE_PRIVATE_START	0xE000 // Key codes in this range are private area mappings for non character keys
#define KEY_CODE_PRIVATE_END	0xF8FF

/* Universal scan code constants */
/* Keyboard scan codes are based on the USB HID Usages (See Section 10 of the Universal Serial Bus HID Usage Tables v1.12) */
/* These are the values reported in the ScanCode field of the TKeyboardData structure returned by the KeyboardRead function */
/* Any keyboard driver supporting legacy keyboards (eg PC/AT or PS/2) should translate the reported codes to be compatible with this set */
#define SCAN_CODE_NONE	0 // Reserved (no event indicated)
#define SCAN_CODE_ROLLOVER	1 // Keyboard ErrorRollOver
#define SCAN_CODE_POSTFAIL	2 // Keyboard POSTFail
#define SCAN_CODE_ERROR	3 // Keyboard ErrorUndefined
#define SCAN_CODE_A	4 // Keyboard a or A
#define SCAN_CODE_B	5 // Keyboard b or B
#define SCAN_CODE_C	6 // Keyboard c or C
#define SCAN_CODE_D	7 // Keyboard d or D
#define SCAN_CODE_E	8 // Keyboard e or E
#define SCAN_CODE_F	9 // Keyboard f or F
#define SCAN_CODE_G	10 // Keyboard g or G
#define SCAN_CODE_H	11 // Keyboard h or H
#define SCAN_CODE_I	12 // Keyboard i or I
#define SCAN_CODE_J	13 // Keyboard j or J
#define SCAN_CODE_K	14 // Keyboard k or K
#define SCAN_CODE_L	15 // Keyboard l or L
#define SCAN_CODE_M	16 // Keyboard m or M
#define SCAN_CODE_N	17 // Keyboard n or N
#define SCAN_CODE_O	18 // Keyboard o or O
#define SCAN_CODE_P	19 // Keyboard p or P
#define SCAN_CODE_Q	20 // Keyboard q or Q
#define SCAN_CODE_R	21 // Keyboard r or R
#define SCAN_CODE_S	22 // Keyboard s or S
#define SCAN_CODE_T	23 // Keyboard t or T
#define SCAN_CODE_U	24 // Keyboard u or U
#define SCAN_CODE_V	25 // Keyboard v or V
#define SCAN_CODE_W	26 // Keyboard w or W
#define SCAN_CODE_X	27 // Keyboard x or X
#define SCAN_CODE_Y	28 // Keyboard y or Y
#define SCAN_CODE_Z	29 // Keyboard z or Z
#define SCAN_CODE_1	30 // Keyboard 1 or !
#define SCAN_CODE_2	31 // Keyboard 2 or @
#define SCAN_CODE_3	32 // Keyboard 3 or #
#define SCAN_CODE_4	33 // Keyboard 4 or $
#define SCAN_CODE_5	34 // Keyboard 5 or %
#define SCAN_CODE_6	35 // Keyboard 6 or ^
#define SCAN_CODE_7	36 // Keyboard 7 or &
#define SCAN_CODE_8	37 // Keyboard 8 or *
#define SCAN_CODE_9	38 // Keyboard 9 or (
#define SCAN_CODE_0	39 // Keyboard 0 or )
#define SCAN_CODE_ENTER	40 // Keyboard Enter)
#define SCAN_CODE_ESCAPE	41 // Keyboard Escape
#define SCAN_CODE_BACKSPACE	42 // Keyboard Backspace
#define SCAN_CODE_TAB	43 // Keyboard Tab
#define SCAN_CODE_SPACE	44 // Keyboard Spacebar
#define SCAN_CODE_MINUS	45 // Keyboard - or _
#define SCAN_CODE_EQUALS	46 // Keyboard = or +
#define SCAN_CODE_LEFT_SQUARE	47 // Keyboard [ or Left Brace
#define SCAN_CODE_RIGHT_SQUARE	48 // Keyboard ] or Right Brace
#define SCAN_CODE_BACKSLASH	49 // Keyboard \ or |
#define SCAN_CODE_NONUS_NUMBER	50 // Keyboard Non-US # and ~
#define SCAN_CODE_SEMICOLON	51 // Keyboard ; or :
#define SCAN_CODE_APOSTROPHE	52 // Keyboard ' or "
#define SCAN_CODE_GRAVE	53 // Keyboard ` or ~
#define SCAN_CODE_COMMA	54 // Keyboard , or <
#define SCAN_CODE_PERIOD	55 // Keyboard . or >
#define SCAN_CODE_SLASH	56 // Keyboard / or ?
#define SCAN_CODE_CAPSLOCK	57 // Keyboard Caps Lock
#define SCAN_CODE_F1	58 // Keyboard F1
#define SCAN_CODE_F2	59 // Keyboard F2
#define SCAN_CODE_F3	60 // Keyboard F3
#define SCAN_CODE_F4	61 // Keyboard F4
#define SCAN_CODE_F5	62 // Keyboard F5
#define SCAN_CODE_F6	63 // Keyboard F6
#define SCAN_CODE_F7	64 // Keyboard F7
#define SCAN_CODE_F8	65 // Keyboard F8
#define SCAN_CODE_F9	66 // Keyboard F9
#define SCAN_CODE_F10	67 // Keyboard F10
#define SCAN_CODE_F11	68 // Keyboard F11
#define SCAN_CODE_F12	69 // Keyboard F12
#define SCAN_CODE_PRINTSCREEN	70 // Keyboard Print Screen
#define SCAN_CODE_SCROLLLOCK	71 // Keyboard Scroll Lock
#define SCAN_CODE_PAUSE	72 // Keyboard Pause
#define SCAN_CODE_INSERT	73 // Keyboard Insert
#define SCAN_CODE_HOME	74 // Keyboard Home
#define SCAN_CODE_PAGEUP	75 // Keyboard PageUp
#define SCAN_CODE_DELETE	76 // Keyboard Delete
#define SCAN_CODE_END	77 // Keyboard End
#define SCAN_CODE_PAGEDN	78 // Keyboard PageDn
#define SCAN_CODE_RIGHT_ARROW	79 // Keyboard Right Arrow
#define SCAN_CODE_LEFT_ARROW	80 // Keyboard Left Arrow
#define SCAN_CODE_DOWN_ARROW	81 // Keyboard Down Arrow
#define SCAN_CODE_UP_ARROW	82 // Keyboard Up Arrow
#define SCAN_CODE_NUMLOCK	83 // Keyboard Num Lock
#define SCAN_CODE_KEYPAD_SLASH	84 // Keypad /
#define SCAN_CODE_KEYPAD_ASTERISK	85 // Keypad *
#define SCAN_CODE_KEYPAD_MINUS	86 // Keypad -
#define SCAN_CODE_KEYPAD_PLUS	87 // Keypad +
#define SCAN_CODE_KEYPAD_ENTER	88 // Keypad Enter
#define SCAN_CODE_KEYPAD_1	89 // Keypad 1 and End
#define SCAN_CODE_KEYPAD_2	90 // Keypad 2 and Down Arrow
#define SCAN_CODE_KEYPAD_3	91 // Keypad 3 and PageDn
#define SCAN_CODE_KEYPAD_4	92 // Keypad 4 and Left Arrow
#define SCAN_CODE_KEYPAD_5	93 // Keypad 5 and Center
#define SCAN_CODE_KEYPAD_6	94 // Keypad 6 and Right Arrow
#define SCAN_CODE_KEYPAD_7	95 // Keypad 7 and Home
#define SCAN_CODE_KEYPAD_8	96 // Keypad 8 and Up Arrow
#define SCAN_CODE_KEYPAD_9	97 // Keypad 9 and PageUp
#define SCAN_CODE_KEYPAD_0	98 // Keypad 0 and Insert
#define SCAN_CODE_KEYPAD_PERIOD	99 // Keypad . and Delete
#define SCAN_CODE_NONUS_BACKSLASH	100 // Keyboard Non-US \ and |
#define SCAN_CODE_APPLICATION	101 // Keyboard Application
#define SCAN_CODE_POWER	102 // Keyboard Power
#define SCAN_CODE_KEYPAD_EQUALS	103 // Keypad =
#define SCAN_CODE_F13	104 // Keyboard F13
#define SCAN_CODE_F14	105 // Keyboard F14
#define SCAN_CODE_F15	106 // Keyboard F15
#define SCAN_CODE_F16	107 // Keyboard F16
#define SCAN_CODE_F17	108 // Keyboard F17
#define SCAN_CODE_F18	109 // Keyboard F18
#define SCAN_CODE_F19	110 // Keyboard F19
#define SCAN_CODE_F20	111 // Keyboard F20
#define SCAN_CODE_F21	112 // Keyboard F21
#define SCAN_CODE_F22	113 // Keyboard F22
#define SCAN_CODE_F23	114 // Keyboard F23
#define SCAN_CODE_F24	115 // Keyboard F24
#define SCAN_CODE_EXECUTE	116 // Keyboard Execute
#define SCAN_CODE_HELP	117 // Keyboard Help
#define SCAN_CODE_MENU	118 // Keyboard Menu
#define SCAN_CODE_SELECT	119 // Keyboard Select
#define SCAN_CODE_STOP	120 // Keyboard Stop
#define SCAN_CODE_AGAIN	121 // Keyboard Again
#define SCAN_CODE_UNDO	122 // Keyboard Undo
#define SCAN_CODE_CUT	123 // Keyboard Cut
#define SCAN_CODE_COPY	124 // Keyboard Copy
#define SCAN_CODE_PASTE	125 // Keyboard Paste
#define SCAN_CODE_FIND	126 // Keyboard Find
#define SCAN_CODE_MUTE	127 // Keyboard Mute
#define SCAN_CODE_VOLUMEUP	128 // Keyboard Volume Up
#define SCAN_CODE_VOLUMEDN	129 // Keyboard Volume Down
#define SCAN_CODE_LOCKING_CAPSLOCK	130 // Keyboard Locking Caps Lock
#define SCAN_CODE_LOCKING_NUMLOCK	131 // Keyboard Locking Num Lock
#define SCAN_CODE_LOCKING_SCROLLLOCK	132 // Keyboard Locking Scroll Lock
#define SCAN_CODE_KEYPAD_COMMA	133 // Keypad Comma
#define SCAN_CODE_KEYPAD_EQUAL_SIGN	134 // Keypad Equal Sign
#define SCAN_CODE_INTERNATIONAL1	135 // Keyboard International1
#define SCAN_CODE_INTERNATIONAL2	136 // Keyboard International2
#define SCAN_CODE_INTERNATIONAL3	137 // Keyboard International3
#define SCAN_CODE_INTERNATIONAL4	138 // Keyboard International4
#define SCAN_CODE_INTERNATIONAL5	139 // Keyboard International5
#define SCAN_CODE_INTERNATIONAL6	140 // Keyboard International6
#define SCAN_CODE_INTERNATIONAL7	141 // Keyboard International7
#define SCAN_CODE_INTERNATIONAL8	142 // Keyboard International8
#define SCAN_CODE_INTERNATIONAL9	143 // Keyboard International9
#define SCAN_CODE_LANG1	144 // Keyboard LANG1
#define SCAN_CODE_LANG2	145 // Keyboard LANG2
#define SCAN_CODE_LANG3	146 // Keyboard LANG3
#define SCAN_CODE_LANG4	147 // Keyboard LANG4
#define SCAN_CODE_LANG5	148 // Keyboard LANG5
#define SCAN_CODE_LANG6	149 // Keyboard LANG6
#define SCAN_CODE_LANG7	150 // Keyboard LANG7
#define SCAN_CODE_LANG8	151 // Keyboard LANG8
#define SCAN_CODE_LANG9	152 // Keyboard LANG9
#define SCAN_CODE_ALT_ERASE	153 // Keyboard Alternate Erase
#define SCAN_CODE_SYSREQ	154 // Keyboard SysReq/Attention
#define SCAN_CODE_CANCEL	155 // Keyboard Cancel
#define SCAN_CODE_CLEAR	156 // Keyboard Clear
#define SCAN_CODE_PRIOR	157 // Keyboard Prior
#define SCAN_CODE_RETURN	158 // Keyboard Return
#define SCAN_CODE_SEPARATOR	159 // Keyboard Separator
#define SCAN_CODE_OUT	160 // Keyboard Out
#define SCAN_CODE_OPER	161 // Keyboard Oper
#define SCAN_CODE_CLEAR_AGAIN	162 // Keyboard Clear/Again
#define SCAN_CODE_CRSEL_PROPS	163 // Keyboard CrSel/Props
#define SCAN_CODE_EXSEL	164 // Keyboard ExSel
/* Codes 165 to 175 Reserved */
#define SCAN_CODE_KEYPAD_00	176 // Keypad 00
#define SCAN_CODE_KEYPAD_000	177 // Keypad 000
#define SCAN_CODE_THOUSANDS_SEPARATOR	178 // Thousands Separator
#define SCAN_CODE_DECIMAL_SEPARATOR	179 // Decimal Separator
#define SCAN_CODE_CURRENCY_UNIT	180 // Currency Unit
#define SCAN_CODE_CURRENCY_SUBUNIT	181 // Currenct Sub-unit
#define SCAN_CODE_KEYPAD_LEFT_BRACKET	182 // Keypad (
#define SCAN_CODE_KEYPAD_RIGHT_BRACKET	183 // Keypad )
#define SCAN_CODE_KEYPAD_LEFT_BRACE	184 // Keypad Left Brace
#define SCAN_CODE_KEYPAD_RIGHT_BRACE	185 // Keypad Right Brace
#define SCAN_CODE_KEYPAD_TAB	186 // Keypad Tab
#define SCAN_CODE_KEYPAD_BACKSPACE	187 // Keypad Backspace
#define SCAN_CODE_KEYPAD_A	188 // Keypad A
#define SCAN_CODE_KEYPAD_B	189 // Keypad B
#define SCAN_CODE_KEYPAD_C	190 // Keypad C
#define SCAN_CODE_KEYPAD_D	191 // Keypad D
#define SCAN_CODE_KEYPAD_E	192 // Keypad E
#define SCAN_CODE_KEYPAD_F	193 // Keypad F
#define SCAN_CODE_KEYPAD_XOR	194 // Keypad XOR
#define SCAN_CODE_KEYPAD_CARET	195 // Keypad ^
#define SCAN_CODE_KEYPAD_PERCENT	196 // Keypad %
#define SCAN_CODE_KEYPAD_LESSTHAN	197 // Keypad <
#define SCAN_CODE_KEYPAD_GREATERTHAN	198 // Keypad >
#define SCAN_CODE_KEYPAD_AMPERSAND	199 // Keypad &
#define SCAN_CODE_KEYPAD_DOUBLE_AMPERSAND	200 // Keypad &&
#define SCAN_CODE_KEYPAD_PIPE	201 // Keypad |
#define SCAN_CODE_KEYPAD_DOUBLE_PIPE	202 // Keypad ||
#define SCAN_CODE_KEYPAD_COLON	203 // Keypad :
#define SCAN_CODE_KEYPAD_NUMBER	204 // Keypad #
#define SCAN_CODE_KEYPAD_SPACE	205 // Keypad Space
#define SCAN_CODE_KEYPAD_AT	206 // Keypad @
#define SCAN_CODE_KEYPAD_EXCLAMATION	207 // Keypad !
#define SCAN_CODE_KEYPAD_MEM_STORE	208 // Keypad Memory Store
#define SCAN_CODE_KEYPAD_MEM_RECALL	209 // Keypad Memory Recall
#define SCAN_CODE_KEYPAD_MEM_CLEAR	210 // Keypad Memory Clear
#define SCAN_CODE_KEYPAD_MEM_ADD	211 // Keypad Memory Add
#define SCAN_CODE_KEYPAD_MEM_SUB	212 // Keypad Memory Subtract
#define SCAN_CODE_KEYPAD_MEM_MULTIPLY	213 // Keypad Memory Multiply
#define SCAN_CODE_KEYPAD_MEM_DIVIDE	214 // Keypad Memory Divide
#define SCAN_CODE_KEYPAD_PLUS_MINUS	215 // Keypad +/-
#define SCAN_CODE_KEYPAD_CLEAR	216 // Keypad Clear
#define SCAN_CODE_KEYPAD_CLEAR_ENTRY	217 // Keypad Clear Entry
#define SCAN_CODE_KEYPAD_BINARY	218 // Keypad Binary
#define SCAN_CODE_KEYPAD_OCTAL	219 // Keypad Octal
#define SCAN_CODE_KEYPAD_DECIMAL	220 // Keypad Decimal
#define SCAN_CODE_KEYPAD_HEX	221 // Keypad Hexadecimal
/* Codes 222 to 223 Reserved */
#define SCAN_CODE_LEFT_CTRL	224 // Keyboard LeftControl
#define SCAN_CODE_LEFT_SHIFT	225 // Keyboard LeftShift
#define SCAN_CODE_LEFT_ALT	226 // Keyboard LeftAlt
#define SCAN_CODE_LEFT_GUI	227 // Keyboard Left GUI
#define SCAN_CODE_RIGHT_CTRL	228 // Keyboard RightControl
#define SCAN_CODE_RIGHT_SHIFT	229 // Keyboard RightShift
#define SCAN_CODE_RIGHT_ALT	230 // Keyboard RightAlt
#define SCAN_CODE_RIGHT_GUI	231 // Keyboard Right GUI
/* Codes 232 to 65535 Reserved */

/* Alternate names for above */
#define SCAN_CODE_EXCLAMATION	30 // Keyboard 1 or !
#define SCAN_CODE_AT	31 // Keyboard 2 or @
#define SCAN_CODE_NUMBER	32 // Keyboard 3 or #
#define SCAN_CODE_CURRENCY	33 // Keyboard 4 or $
#define SCAN_CODE_PERCENT	34 // Keyboard 5 or %
#define SCAN_CODE_CARET	35 // Keyboard 6 or ^
#define SCAN_CODE_AMPERSAND	36 // Keyboard 7 or &
#define SCAN_CODE_ASTERISK	37 // Keyboard 8 or *
#define SCAN_CODE_LEFT_BRACKET	38 // Keyboard 9 or (
#define SCAN_CODE_RIGHT_BRACKET	39 // Keyboard 0 or )

#define SCAN_CODE_DASH	45 // Keyboard - or _
#define SCAN_CODE_UNDERSCORE	45 // Keyboard - or _
#define SCAN_CODE_PLUS	46 // Keyboard = or +
#define SCAN_CODE_LEFT_BRACE	47 // Keyboard [ or Left Brace
#define SCAN_CODE_RIGHT_BRACE	48 // Keyboard ] or Right Brace
#define SCAN_CODE_PIPE	49 // Keyboard \ or |
#define SCAN_CODE_NONUS_TILDE	50 // Keyboard Non-US # and ~
#define SCAN_CODE_COLON	51 // Keyboard ; or :
#define SCAN_CODE_QUOTATION	52 // Keyboard ' or "
#define SCAN_CODE_TILDE	53 // Keyboard ` or ~
#define SCAN_CODE_LESSTHAN	54 // Keyboard , or <
#define SCAN_CODE_GREATERTHAN	55 // Keyboard . or >
#define SCAN_CODE_QUESTION	56 // Keyboard / or ?

#define SCAN_CODE_ALTGR	SCAN_CODE_RIGHT_ALT // Keyboard RightAlt

#define SCAN_CODE_KEYPAD_FIRST	SCAN_CODE_NUMLOCK
#define SCAN_CODE_KEYPAD_LAST	SCAN_CODE_KEYPAD_PERIOD

/* ============================================================================== */
/* Universal color constants */
/* Basic 32 bit RGB colors (8 bit Transparency, 8 bit Red, 8 bit Green, 8 bit Blue) */
#define COLOR_NONE	0x00000000
#define COLOR_BLACK	0xFF000000
#define COLOR_RED	0xFFFF0000
#define COLOR_ORANGE	0xFFFF8500
#define COLOR_LEAFGREEN	0xFF009900
#define COLOR_GREEN	0xFF00FF00
#define COLOR_YELLOW	0xFFFFFF00
#define COLOR_DARKGREEN	0xFF254117
#define COLOR_DARKGRAY	0xFF595959
#define COLOR_BROWN	0xFF6F4E37
#define COLOR_INDIGO	0xFF2E0854
#define COLOR_RASPBERRY	0xFFE30B5C
#define COLOR_GRAY	0xFF808080
#define COLOR_PURPLE	0xFF4B0082
#define COLOR_PINK	0xFFFF0090
#define COLOR_DARKBLUE	0xFF0000A0
#define COLOR_SILVER	0xFFC0C0C0
#define COLOR_BLUEIVY	0xFF3090C7
#define COLOR_MIDGRAY	0xFFE0E0E0
#define COLOR_LIGHTGRAY	0xFFF7F7F7
#define COLOR_BLUE	0xFF0000FF
#define COLOR_MAGENTA	0xFFFF00FF
#define COLOR_CYAN	0xFF00FFFF
#define COLOR_WHITE	0xFFFFFFFF

/* Ultibo release RGB colors */
#define COLOR_ULTIBO_LETTUCE	0xFF000000 // Ultibo Version 0.0 (Lettuce)
#define COLOR_ULTIBO_POTATO	0xFF0000A0 // Ultibo Version 1.0 (Potato)
#define COLOR_ULTIBO_CUCUMBER	0xFFFF8500 // Ultibo Version 1.x (Cucumber)
#define COLOR_ULTIBO_BEETROOT	0xFF00BB00 // Ultibo Version 2.x (Beetroot)

#define COLOR_ULTIBO	COLOR_ULTIBO_BEETROOT

/* Color format constants */
/* See: https://en.wikipedia.org/wiki/Color_depth and https://en.wikipedia.org/wiki/RGBA_color_space */
#define COLOR_FORMAT_ARGB32	0 // 32 bits per pixel Alpha/Red/Green/Blue (ARGB8888)
#define COLOR_FORMAT_ABGR32	1 // 32 bits per pixel Alpha/Blue/Green/Red (ABGR8888)
#define COLOR_FORMAT_RGBA32	2 // 32 bits per pixel Red/Green/Blue/Alpha (RGBA8888)
#define COLOR_FORMAT_BGRA32	3 // 32 bits per pixel Blue/Green/Red/Alpha (BGRA8888)
#define COLOR_FORMAT_URGB32	4 // 32 bits per pixel Unused/Red/Green/Blue (URGB8888)
#define COLOR_FORMAT_UBGR32	5 // 32 bits per pixel Unused/Blue/Green/Red (UBGR8888)
#define COLOR_FORMAT_RGBU32	6 // 32 bits per pixel Red/Green/Blue/Unused (RGBU8888)
#define COLOR_FORMAT_BGRU32	7 // 32 bits per pixel Blue/Green/Red/Unused (BGRU8888)
#define COLOR_FORMAT_RGB24	8 // 24 bits per pixel Red/Green/Blue (RGB888)
#define COLOR_FORMAT_BGR24	9 // 24 bits per pixel Blue/Green/Red (BGR888)
#define COLOR_FORMAT_RGB16	10 // 16 bits per pixel Red/Green/Blue (RGB565)
#define COLOR_FORMAT_BGR16	11 // 16 bits per pixel Blue/Green/Red (BGR565)
#define COLOR_FORMAT_RGB15	12 // 15 bits per pixel Red/Green/Blue (RGB555)
#define COLOR_FORMAT_BGR15	13 // 15 bits per pixel Blue/Green/Red (BGR555)
#define COLOR_FORMAT_RGB8	14 // 8 bits per pixel Red/Green/Blue (RGB332)
#define COLOR_FORMAT_BGR8	15 // 8 bits per pixel Blue/Green/Red (BGR233)
#define COLOR_FORMAT_GRAY16	16 // 16 bits per pixel grayscale
#define COLOR_FORMAT_GRAY8	17 // 8 bits per pixel grayscale
#define COLOR_FORMAT_INDEX16	18 // 16 bits per pixel palette index
#define COLOR_FORMAT_INDEX8	19 // 8 bits per pixel palette index

#define COLOR_FORMAT_MAX	19

#define COLOR_FORMAT_DEFAULT	COLOR_FORMAT_ARGB32 // The default color format (Used for the COLOR_* constants above)

#define COLOR_FORMAT_UNKNOWN	(uint32_t)-1

/* ============================================================================== */
/* Universal size constants (From /include/linux/sizes.h) */
#define SIZE_0	0x00000000
#define SIZE_1	0x00000001
#define SIZE_2	0x00000002
#define SIZE_4	0x00000004
#define SIZE_8	0x00000008
#define SIZE_16	0x00000010
#define SIZE_32	0x00000020
#define SIZE_64	0x00000040
#define SIZE_128	0x00000080
#define SIZE_256	0x00000100
#define SIZE_512	0x00000200

#define SIZE_1K	0x00000400
#define SIZE_2K	0x00000800
#define SIZE_4K	0x00001000
#define SIZE_8K	0x00002000
#define SIZE_16K	0x00004000
#define SIZE_32K	0x00008000
#define SIZE_64K	0x00010000
#define SIZE_128K	0x00020000
#define SIZE_256K	0x00040000
#define SIZE_512K	0x00080000

#define SIZE_1M	0x00100000
#define SIZE_2M	0x00200000
#define SIZE_4M	0x00400000
#define SIZE_8M	0x00800000
#define SIZE_16M	0x01000000
#define SIZE_32M	0x02000000
#define SIZE_64M	0x04000000
#define SIZE_128M	0x08000000
#define SIZE_256M	0x10000000
#define SIZE_512M	0x20000000

#define SIZE_1G	0x40000000
#define SIZE_2G	0x80000000

/* ============================================================================== */
/* Universal time constants */
#define MILLISECONDS_PER_SECOND	1000
#define MICROSECONDS_PER_SECOND	1000000
#define NANOSECONDS_PER_SECOND	1000000000

/* Ultibo time constants (100 nanosecond ticks since 1/1/1601) */
/* Note: Nanoseconds is 10^9 so 100 nanosecond ticks is 10^7 */
#define TIME_TICKS_PER_MICROSECOND	10 // 10^7 / 10^6
#define TIME_TICKS_PER_MILLISECOND	10000 // 10^7 / 10^3
#define TIME_TICKS_PER_SECOND	10000000 // 10^7
#define TIME_TICKS_PER_MINUTE	600000000 // 60 * 10^7
#define TIME_TICKS_PER_HOUR	36000000000 // 60 * 60 * 10^7
#define TIME_TICKS_PER_DAY	864000000000 // 24 * 60 * 60 * 10^7

#define TIME_TICKS_TO_1899	94353120000000000 // Offset between 1/1/1601 (Ultibo) and 30/12/1899 (FreePascal)
#define TIME_TICKS_TO_1970	116444736000000000 // Offset between 1/1/1601 (Ultibo) and 1/1/1970 (Unix/Linux)
#define TIME_TICKS_TO_1980	119600064000000000 // Offset between 1/1/1601 (Ultibo) and 1/1/1980 (DOS)
#define TIME_TICKS_TO_2001	126227808000000000 // Offset between 1/1/1601 (Ultibo) and 1/1/2001 (Clock is assumed not set if time is less than this)

#define TIME_TICKS_PER_10MILLISECONDS	100000 // 10^7 / 10^2

/* Unix/Linux time constants (Seconds since 1/1/1970) */
#define UNIX_TIME_SECONDS_PER_DAY	86400 // 60*60*24;
#define UNIX_TIME_DAYS_TO_1970	25569.0 // Offset between 1899 (FreePascal) and 1970 (Unix/Linux)

/* FreePascal time constants (TDateTime starts at 30/12/1899) */
#define PASCAL_TIME_MILLISECONDS_PER_DAY	86400000 // 60*60*24*1000;
#define PASCAL_TIME_SECONDS_PER_DAY	86400 // 60*60*24;
#define PASCAL_TIME_DOS_TIME_START	2162688 // DOS date time value for start of DOS time (1/1/1980)

#define PASCAL_DAY_OFFSET	1.0 // TDateTime value 1 day
#define PASCAL_MINUTE_OFFSET	0.000694444444444444 // TDateTime value of 1 minute

/* ============================================================================== */
/* System Call constants */
#define SYSTEM_CALL_UNDEFINED	0x00000000
#define SYSTEM_CALL_CONTEXT_SWITCH	0x00000001

/* ============================================================================== */
/* Machine Type constants */
#define MACHINE_TYPE_UNKNOWN	0
#define MACHINE_TYPE_BCM2708	1 // Broadcom BCM2708 (Raspberry Pi)
#define MACHINE_TYPE_BCM2709	2 // Broadcom BCM2709 (Raspberry Pi 2)
#define MACHINE_TYPE_BCM2710	3 // Broadcom BCM2710 (Raspberry Pi 3)
#define MACHINE_TYPE_VERSATILEPB	4 // ARM Versatile PB (QEMU)

/* ============================================================================== */
/* Board Type constants */
#define BOARD_TYPE_UNKNOWN	0
#define BOARD_TYPE_RPIA	1 // Raspberry Pi Model A
#define BOARD_TYPE_RPIB	2 // Raspberry Pi Model B
#define BOARD_TYPE_RPI_COMPUTE	3 // Raspberry Pi Compute Module
#define BOARD_TYPE_RPIA_PLUS	4 // Raspberry Pi Model A+
#define BOARD_TYPE_RPIB_PLUS	5 // Raspberry Pi Model B+
#define BOARD_TYPE_RPI2B	6 // Raspberry Pi 2 Model B
#define BOARD_TYPE_RPI_ZERO	7 // Raspberry Pi Model Zero
#define BOARD_TYPE_BPI	8 // Banana Pi
#define BOARD_TYPE_BPRO	9 // Banana Pro
#define BOARD_TYPE_BBB_REVC	10 // Beagle Bone Black (Revision C)
#define BOARD_TYPE_CUBOX_I	11 // Cubox i1/i2/i2ex/i4pro/i4x4
#define BOARD_TYPE_HUMMINGBOARD	12 // Hummingboard
#define BOARD_TYPE_CREATOR_CI20	13 // MIPS Creator CI20
#define BOARD_TYPE_PCDUINO1	14 // pcDuino V1
#define BOARD_TYPE_PCDUINO2	15 // pcDuino V2
#define BOARD_TYPE_PCDUINO3	16 // pcDuino V3
#define BOARD_TYPE_ODROID_C1	17 // Odroid C1/C1+
#define BOARD_TYPE_ODROID_U2	18 // Odroid U2
#define BOARD_TYPE_ODROID_U3	19 // Odroid U3
#define BOARD_TYPE_ODROID_XU3	20 // Odroid XU3
#define BOARD_TYPE_ODROID_XU4	21 // Odroid XU4
#define BOARD_TYPE_PC_X86	22 // PC x86
#define BOARD_TYPE_PC_X86_64	23 // PC x86 64bit
#define BOARD_TYPE_RPI3B	24 // Raspberry Pi 3 Model B
#define BOARD_TYPE_QEMUVPB	25 // QEMU Versatile PB
#define BOARD_TYPE_RPI_COMPUTE3	26 // Raspberry Pi Compute Module 3
#define BOARD_TYPE_RPI_ZERO_W	27 // Raspberry Pi Model Zero W
#define BOARD_TYPE_RPI3B_PLUS	28 // Raspberry Pi 3 Model B+

/* ============================================================================== */
/* CPU Arch constants */
#define CPU_ARCH_UNKNOWN	0
#define CPU_ARCH_ARM32	1 // ARM Arch 32 (ARMv6/ARMv7)(ARMv8 in 32bit mode)
#define CPU_ARCH_ARM64	2 // ARM Arch 64 (ARMv8

/* CPU Type constants */
#define CPU_TYPE_UNKNOWN	0
#define CPU_TYPE_ARMV6	1 // ARMv6 (ARM1176 etc)
#define CPU_TYPE_ARMV7	2 // ARMv7 (Cortex A5/A7/A8/A9/A15/A17 etc)
#define CPU_TYPE_ARMV8	3 // ARMv8 (Cortex A53/A57/A72 etc)

/* CPU Model constants */
#define CPU_MODEL_UNKNOWN	0
#define CPU_MODEL_ARM1176JZFS	1 // ARM1176JZF-S
#define CPU_MODEL_CORTEX_A5	2 // ARM Cortex-A5
#define CPU_MODEL_CORTEX_A7	3 // ARM Cortex-A7
#define CPU_MODEL_CORTEX_A8	4 // ARM Cortex-A8
#define CPU_MODEL_CORTEX_A9	5 // ARM Cortex-A9
#define CPU_MODEL_CORTEX_A15	6 // ARM Cortex-A15
#define CPU_MODEL_CORTEX_A17	7 // ARM Cortex-A17
#define CPU_MODEL_CORTEX_A53	8 // ARM Cortex-A53
#define CPU_MODEL_CORTEX_A57	9 // ARM Cortex-A57
#define CPU_MODEL_CORTEX_A72	10 // ARM Cortex-A72

/* CPU Description constants */
#define CPU_DESCRIPTION_UNKNOWN	"Unknown"
#define CPU_DESCRIPTION_ARM1176JZFS	"ARM1176JZF-S"
#define CPU_DESCRIPTION_CORTEX_A5	"ARM Cortex-A5"
#define CPU_DESCRIPTION_CORTEX_A5_MP	"ARM Cortex-A5 MPCore"
#define CPU_DESCRIPTION_CORTEX_A7	"ARM Cortex-A7 MPCore"
#define CPU_DESCRIPTION_CORTEX_A8	"ARM Cortex-A8"
#define CPU_DESCRIPTION_CORTEX_A9	"ARM Cortex-A9"
#define CPU_DESCRIPTION_CORTEX_A9_MP	"ARM Cortex-A9 MPCore"
#define CPU_DESCRIPTION_CORTEX_A15	"ARM Cortex-A15 MPCore"
#define CPU_DESCRIPTION_CORTEX_A17	"ARM Cortex-A17 MPCore"
#define CPU_DESCRIPTION_CORTEX_A53	"ARM Cortex-A53 MPCore"
#define CPU_DESCRIPTION_CORTEX_A57	"ARM Cortex-A57 MPCore"
#define CPU_DESCRIPTION_CORTEX_A72	"ARM Cortex-A72 MPCore"

/* CPU State constants */
#define CPU_STATE_NONE	(0 << 0)
#define CPU_STATE_MMU_ENABLED	(1 << 0)
#define CPU_STATE_DATA_CACHE_ENABLED	(1 << 1)
#define CPU_STATE_INSTRUCTION_CACHE_ENABLED	(1 << 2)
#define CPU_STATE_BRANCH_PREDICTION_ENABLED	(1 << 3)

/* CPU Group constants */
#define CPU_GROUP_0	0
#define CPU_GROUP_1	1
#define CPU_GROUP_2	2
#define CPU_GROUP_3	3
#define CPU_GROUP_4	4
#define CPU_GROUP_5	5
#define CPU_GROUP_6	6
#define CPU_GROUP_7	7
#define CPU_GROUP_8	8
#define CPU_GROUP_9	9
#define CPU_GROUP_10	10
#define CPU_GROUP_11	11
#define CPU_GROUP_12	12
#define CPU_GROUP_13	13
#define CPU_GROUP_14	14
#define CPU_GROUP_15	15
#define CPU_GROUP_16	16
#define CPU_GROUP_17	17
#define CPU_GROUP_18	18
#define CPU_GROUP_19	19
#define CPU_GROUP_20	20
#define CPU_GROUP_21	21
#define CPU_GROUP_22	22
#define CPU_GROUP_23	23
#define CPU_GROUP_24	24
#define CPU_GROUP_25	25
#define CPU_GROUP_26	26
#define CPU_GROUP_27	27
#define CPU_GROUP_28	28
#define CPU_GROUP_29	29
#define CPU_GROUP_30	30
#define CPU_GROUP_31	31

#define CPU_GROUP_ALL	0xFFFFFFFF

/* CPU ID constants */
#define CPU_ID_0	0
#define CPU_ID_1	1
#define CPU_ID_2	2
#define CPU_ID_3	3
#define CPU_ID_4	4
#define CPU_ID_5	5
#define CPU_ID_6	6
#define CPU_ID_7	7
#define CPU_ID_8	8
#define CPU_ID_9	9
#define CPU_ID_10	10
#define CPU_ID_11	11
#define CPU_ID_12	12
#define CPU_ID_13	13
#define CPU_ID_14	14
#define CPU_ID_15	15
#define CPU_ID_16	16
#define CPU_ID_17	17
#define CPU_ID_18	18
#define CPU_ID_19	19
#define CPU_ID_20	20
#define CPU_ID_21	21
#define CPU_ID_22	22
#define CPU_ID_23	23
#define CPU_ID_24	24
#define CPU_ID_25	25
#define CPU_ID_26	26
#define CPU_ID_27	27
#define CPU_ID_28	28
#define CPU_ID_29	29
#define CPU_ID_30	30
#define CPU_ID_31	31

#define CPU_ID_ALL	0xFFFFFFFF

/* CPU Affinity constants */
#define CPU_AFFINITY_0	(1 << CPU_ID_0)
#define CPU_AFFINITY_1	(1 << CPU_ID_1)
#define CPU_AFFINITY_2	(1 << CPU_ID_2)
#define CPU_AFFINITY_3	(1 << CPU_ID_3)
#define CPU_AFFINITY_4	(1 << CPU_ID_4)
#define CPU_AFFINITY_5	(1 << CPU_ID_5)
#define CPU_AFFINITY_6	(1 << CPU_ID_6)
#define CPU_AFFINITY_7	(1 << CPU_ID_7)
#define CPU_AFFINITY_8	(1 << CPU_ID_8)
#define CPU_AFFINITY_9	(1 << CPU_ID_9)
#define CPU_AFFINITY_10	(1 << CPU_ID_10)
#define CPU_AFFINITY_11	(1 << CPU_ID_11)
#define CPU_AFFINITY_12	(1 << CPU_ID_12)
#define CPU_AFFINITY_13	(1 << CPU_ID_13)
#define CPU_AFFINITY_14	(1 << CPU_ID_14)
#define CPU_AFFINITY_15	(1 << CPU_ID_15)
#define CPU_AFFINITY_16	(1 << CPU_ID_16)
#define CPU_AFFINITY_17	(1 << CPU_ID_17)
#define CPU_AFFINITY_18	(1 << CPU_ID_18)
#define CPU_AFFINITY_19	(1 << CPU_ID_19)
#define CPU_AFFINITY_20	(1 << CPU_ID_20)
#define CPU_AFFINITY_21	(1 << CPU_ID_21)
#define CPU_AFFINITY_22	(1 << CPU_ID_22)
#define CPU_AFFINITY_23	(1 << CPU_ID_23)
#define CPU_AFFINITY_24	(1 << CPU_ID_24)
#define CPU_AFFINITY_25	(1 << CPU_ID_25)
#define CPU_AFFINITY_26	(1 << CPU_ID_26)
#define CPU_AFFINITY_27	(1 << CPU_ID_27)
#define CPU_AFFINITY_28	(1 << CPU_ID_28)
#define CPU_AFFINITY_29	(1 << CPU_ID_29)
#define CPU_AFFINITY_30	(1 << CPU_ID_30)
#define CPU_AFFINITY_31	(1 << CPU_ID_31)

#define CPU_AFFINITY_NONE	0x00000000
#define CPU_AFFINITY_ALL	0xFFFFFFFF

/* ============================================================================== */
/* FPU Type constants */
#define FPU_TYPE_UNKNOWN	0
#define FPU_TYPE_SOFT	1
#define FPU_TYPE_VFPV2	2
#define FPU_TYPE_VFPV3	3
#define FPU_TYPE_VFPV4	4

/* FPU State constants */
#define FPU_STATE_NONE	(0 << 0)
#define FPU_STATE_ENABLED	(1 << 0)

/* ============================================================================== */
/* GPU Type constants */
#define GPU_TYPE_UNKNOWN	0
#define GPU_TYPE_VC4	1 // Broadcom VideoCore IV
#define GPU_TYPE_MALI400	2 // ARM Mali 400
#define GPU_TYPE_MALI450	3 // ARM Mali 450
#define GPU_TYPE_GC880	4 // Vivante GC880
#define GPU_TYPE_GC2000	5 // Vivante GC2000

/* GPU State constants */
#define GPU_STATE_NONE	(0 << 0)
#define GPU_STATE_ENABLED	(1 << 0)

/* ============================================================================== */
/* Cache Type constants */
#define CACHE_TYPE_NONE	0 // No Cache
#define CACHE_TYPE_DATA	1 // Data Cache Only
#define CACHE_TYPE_INSTRUCTION	2 // Instruction Cache Only
#define CACHE_TYPE_SEPARATE	3 // Separate Data and Instruction Caches
#define CACHE_TYPE_UNIFIED	4 // Unified Data and Instruction Cache

/* ============================================================================== */
/* DMA Direction constants */
#define DMA_DIR_NONE	0 // No direction (No special handling by controller)
#define DMA_DIR_MEM_TO_MEM	1
#define DMA_DIR_MEM_TO_DEV	2
#define DMA_DIR_DEV_TO_MEM	3
#define DMA_DIR_DEV_TO_DEV	4

/* DMA DREQ ID constants */
#define DMA_DREQ_ID_NONE	0 // No peripheral gating (memory to memory transfer)
#define DMA_DREQ_ID_UART_TX	1
#define DMA_DREQ_ID_UART_RX	2
#define DMA_DREQ_ID_SPI_TX	3
#define DMA_DREQ_ID_SPI_RX	4
#define DMA_DREQ_ID_SPI_SLAVE_TX	5
#define DMA_DREQ_ID_SPI_SLAVE_RX	6
#define DMA_DREQ_ID_PCM_TX	7
#define DMA_DREQ_ID_PCM_RX	8
#define DMA_DREQ_ID_PWM	9
#define DMA_DREQ_ID_MMC	10
#define DMA_DREQ_ID_SDHOST	11

/* ============================================================================== */
/* GPIO Pin constants */
#define GPIO_PIN_0	0
#define GPIO_PIN_1	1
#define GPIO_PIN_2	2
#define GPIO_PIN_3	3
#define GPIO_PIN_4	4
#define GPIO_PIN_5	5
#define GPIO_PIN_6	6
#define GPIO_PIN_7	7
#define GPIO_PIN_8	8
#define GPIO_PIN_9	9
#define GPIO_PIN_10	10
#define GPIO_PIN_11	11
#define GPIO_PIN_12	12
#define GPIO_PIN_13	13
#define GPIO_PIN_14	14
#define GPIO_PIN_15	15
#define GPIO_PIN_16	16
#define GPIO_PIN_17	17
#define GPIO_PIN_18	18
#define GPIO_PIN_19	19
#define GPIO_PIN_20	20
#define GPIO_PIN_21	21
#define GPIO_PIN_22	22
#define GPIO_PIN_23	23
#define GPIO_PIN_24	24
#define GPIO_PIN_25	25
#define GPIO_PIN_26	26
#define GPIO_PIN_27	27
#define GPIO_PIN_28	28
#define GPIO_PIN_29	29
#define GPIO_PIN_30	30
#define GPIO_PIN_31	31
#define GPIO_PIN_32	32
#define GPIO_PIN_33	33
#define GPIO_PIN_34	34
#define GPIO_PIN_35	35
#define GPIO_PIN_36	36
#define GPIO_PIN_37	37
#define GPIO_PIN_38	38
#define GPIO_PIN_39	39
#define GPIO_PIN_40	40
#define GPIO_PIN_41	41
#define GPIO_PIN_42	42
#define GPIO_PIN_43	43
#define GPIO_PIN_44	44
#define GPIO_PIN_45	45
#define GPIO_PIN_46	46
#define GPIO_PIN_47	47
#define GPIO_PIN_48	48
#define GPIO_PIN_49	49
#define GPIO_PIN_50	50
#define GPIO_PIN_51	51
#define GPIO_PIN_52	52
#define GPIO_PIN_53	53
#define GPIO_PIN_54	54
#define GPIO_PIN_55	55
#define GPIO_PIN_56	56
#define GPIO_PIN_57	57
#define GPIO_PIN_58	58
#define GPIO_PIN_59	59
#define GPIO_PIN_60	60

#define GPIO_PIN_MAX	60

#define GPIO_PIN_UNKNOWN	(uint32_t)-1

/* GPIO Function constants */
#define GPIO_FUNCTION_IN	0
#define GPIO_FUNCTION_OUT	1
#define GPIO_FUNCTION_ALT0	2
#define GPIO_FUNCTION_ALT1	3
#define GPIO_FUNCTION_ALT2	4
#define GPIO_FUNCTION_ALT3	5
#define GPIO_FUNCTION_ALT4	6
#define GPIO_FUNCTION_ALT5	7

#define GPIO_FUNCTION_UNKNOWN	(uint32_t)-1 // Returned by GPIOFunctionGet on error (eg device does not support reading the function state)

/* GPIO Level constants */
#define GPIO_LEVEL_LOW	0
#define GPIO_LEVEL_HIGH	1

#define GPIO_LEVEL_UNKNOWN	(uint32_t)-1 // Returned by GPIOInputGet/Wait on error (eg device does not exist)

/* GPIO Pull constants */
#define GPIO_PULL_NONE	0
#define GPIO_PULL_UP	1
#define GPIO_PULL_DOWN	2

#define GPIO_PULL_UNKNOWN	(uint32_t)-1 // Returned by GPIOPullGet on error (eg device does not support reading the PullUp/Down state)

/* GPIO Trigger constants */
#define GPIO_TRIGGER_NONE	0
#define GPIO_TRIGGER_LOW	1
#define GPIO_TRIGGER_HIGH	2
#define GPIO_TRIGGER_RISING	3
#define GPIO_TRIGGER_FALLING	4
#define GPIO_TRIGGER_ASYNC_RISING	5
#define GPIO_TRIGGER_ASYNC_FALLING	6
#define GPIO_TRIGGER_EDGE	7

#define GPIO_TRIGGER_UNKNOWN	(uint32_t)-1 // Passed to GPIO callback event when device does not support determining the trigger source

/* ============================================================================== */
/* Virtual GPIO Pin constants */
#define VIRTUAL_GPIO_PIN_0	0
#define VIRTUAL_GPIO_PIN_1	1
#define VIRTUAL_GPIO_PIN_2	2
#define VIRTUAL_GPIO_PIN_3	3
#define VIRTUAL_GPIO_PIN_4	4
#define VIRTUAL_GPIO_PIN_5	5
#define VIRTUAL_GPIO_PIN_6	6
#define VIRTUAL_GPIO_PIN_7	7

/* Virtual GPIO Function constants */
#define VIRTUAL_GPIO_FUNCTION_IN	0
#define VIRTUAL_GPIO_FUNCTION_OUT	1

/* ============================================================================== */
/* Serial Baud Rate constants */
#define SERIAL_BAUD_RATE_DEFAULT	0

#define SERIAL_BAUD_RATE_STANDARD	115200 // If SERIAL_BAUD_RATE_DEFAULT is passed to SerialOpen then this is the baud rate to use
#define SERIAL_BAUD_RATE_FALLBACK	9600 // The fallback baud rate if SERIAL_BAUD_RATE_STANDARD is not supported by the device

/* Serial Data bit constants */
#define SERIAL_DATA_8BIT	8
#define SERIAL_DATA_7BIT	7
#define SERIAL_DATA_6BIT	6
#define SERIAL_DATA_5BIT	5

/* Serial Stop bit constants */
#define SERIAL_STOP_1BIT	1
#define SERIAL_STOP_2BIT	2
#define SERIAL_STOP_1BIT5	3 // 1.5 Stop bits

/* Serial Parity constants */
#define SERIAL_PARITY_NONE	0
#define SERIAL_PARITY_ODD	1
#define SERIAL_PARITY_EVEN	2
#define SERIAL_PARITY_MARK	3
#define SERIAL_PARITY_SPACE	4

/* Serial Flow Control constants */
#define SERIAL_FLOW_NONE	0
#define SERIAL_FLOW_RTS_CTS	1
#define SERIAL_FLOW_DSR_DTR	2

/* ============================================================================== */
/* I2C Address constants */
#define I2C_ADDRESS_INVALID	(uint16_t)-1

/* ============================================================================== */
/* SPI Protocol constants */
// SPI_PROTOCOL_ //To Do //Continuing //4WIRE/3WIRE/LOSSI etc //SPI_MODE_* becomes 0/1/2/3 instead

/* SPI Mode constants */
#define SPI_MODE_4WIRE	0
#define SPI_MODE_3WIRE	1
#define SPI_MODE_LOSSI	2

#define SPI_MODE_UNKNOWN	(uint32_t)-1 // Returned by SPIGetMode on error (eg device does not exist)

/* SPI Chip Select constants */
#define SPI_CS_0	0
#define SPI_CS_1	1
#define SPI_CS_2	2
#define SPI_CS_3	3
#define SPI_CS_4	4
#define SPI_CS_5	5
#define SPI_CS_6	6
#define SPI_CS_7	7
#define SPI_CS_8	8
#define SPI_CS_9	9
#define SPI_CS_10	10
#define SPI_CS_11	11
#define SPI_CS_12	12
#define SPI_CS_13	13
#define SPI_CS_14	14
#define SPI_CS_15	15

#define SPI_CS_MAX	15

#define SPI_CS_NONE	(uint16_t)-1 // Special value for No Chip Select to allow external control of additional CS lines

/* SPI Clock Phase (CPHA) constants */
#define SPI_CLOCK_PHASE_LOW	0 // Clock edge rising or falling for data input/output
#define SPI_CLOCK_PHASE_HIGH	1 // See https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus for more information

#define SPI_CLOCK_PHASE_UNKNOWN	(uint32_t)-1 // Returned by SPIGetClockPhase on error (eg device does not exist)

/* SPI Clock Polarity (CPOL) constants */
#define SPI_CLOCK_POLARITY_LOW	0 // Clock is low when not transmitting
#define SPI_CLOCK_POLARITY_HIGH	1 // Clock is high when not transmitting

#define SPI_CLOCK_POLARITY_UNKNOWN	(uint32_t)-1 // Returned by SPIGetClockPolarity on error (eg device does not exist)

/* SPI Chip Select Polarity (CSPOL) constants */
#define SPI_CS_POLARITY_LOW	0 // Chip select is active low (Default)
#define SPI_CS_POLARITY_HIGH	1 // Chip select is active high

#define SPI_CS_POLARITY_UNKNOWN	(uint32_t)-1 // Returned by SPIGetSelectPolarity on error (eg device does not exist)

/* ============================================================================== */
/* Power ID constants */
#define POWER_ID_MMC0	0
#define POWER_ID_MMC1	1
#define POWER_ID_MMC2	2
#define POWER_ID_MMC3	3
#define POWER_ID_UART0	4
#define POWER_ID_UART1	5
#define POWER_ID_UART2	6
#define POWER_ID_UART3	7
#define POWER_ID_USB0	8
#define POWER_ID_USB1	9
#define POWER_ID_USB2	10
#define POWER_ID_USB3	11
#define POWER_ID_I2C0	12
#define POWER_ID_I2C1	13
#define POWER_ID_I2C2	14
#define POWER_ID_I2C3	15
#define POWER_ID_SPI0	16
#define POWER_ID_SPI1	17
#define POWER_ID_SPI2	18
#define POWER_ID_SPI3	19
#define POWER_ID_CCP2TX	20

/* Power State constants */
#define POWER_STATE_OFF	0
#define POWER_STATE_ON	1

/* ============================================================================== */
/* Clock ID constants */
#define CLOCK_ID_MMC0	0
#define CLOCK_ID_MMC1	1
#define CLOCK_ID_MMC2	2
#define CLOCK_ID_MMC3	3
#define CLOCK_ID_UART0	4
#define CLOCK_ID_UART1	5
#define CLOCK_ID_UART2	6
#define CLOCK_ID_UART3	7
#define CLOCK_ID_CPU	8
#define CLOCK_ID_CORE	9
#define CLOCK_ID_GPU	10
#define CLOCK_ID_V3D	11
#define CLOCK_ID_H264	12
#define CLOCK_ID_ISP	13
#define CLOCK_ID_SDRAM	14
#define CLOCK_ID_PIXEL	15
#define CLOCK_ID_PWM0	16
#define CLOCK_ID_PWM1	17
#define CLOCK_ID_I2C0	18
#define CLOCK_ID_I2C1	19
#define CLOCK_ID_I2C2	20
#define CLOCK_ID_I2C3	21
#define CLOCK_ID_SPI0	22
#define CLOCK_ID_SPI1	23
#define CLOCK_ID_SPI2	24
#define CLOCK_ID_SPI3	25

/* Clock State constants */
#define CLOCK_STATE_OFF	0
#define CLOCK_STATE_ON	1

/* ============================================================================== */
/* Turbo ID constants */
#define TURBO_ID_SOC	0

/* ============================================================================== */
/* Voltage ID constants */
#define VOLTAGE_ID_CORE	0
#define VOLTAGE_ID_SDRAM_C	1
#define VOLTAGE_ID_SDRAM_P	2
#define VOLTAGE_ID_SDRAM_I	3

/* ============================================================================== */
/* Temperature ID constants */
#define TEMPERATURE_ID_SOC	0

/* ============================================================================== */
/* Console Direction constants */
#define CONSOLE_DIRECTION_UP	0 // Scroll Console Up
#define CONSOLE_DIRECTION_DOWN	1 // Scroll Console Down
#define CONSOLE_DIRECTION_LEFT	2 // Scroll Console Left
#define CONSOLE_DIRECTION_RIGHT	3 // Scroll Console Right

/* Console Position constants */
#define CONSOLE_POSITION_FULL	0 // Console Window will appear in the full console
#define CONSOLE_POSITION_TOP	1 // Console Window will appear in the top half of the console
#define CONSOLE_POSITION_BOTTOM	2 // Console Window will appear in the bottom half of the console
#define CONSOLE_POSITION_LEFT	3 // Console Window will appear in the left half of the console
#define CONSOLE_POSITION_RIGHT	4 // Console Window will appear in the right half of the console
#define CONSOLE_POSITION_TOPLEFT	5 // Console Window will appear in the top left corner of the console
#define CONSOLE_POSITION_TOPRIGHT	6 // Console Window will appear in the top right corner of the console
#define CONSOLE_POSITION_BOTTOMLEFT	7 // Console Window will appear in the bottom left corner of the console
#define CONSOLE_POSITION_BOTTOMRIGHT	8 // Console Window will appear in the bottom right corner of the console

#define CONSOLE_POSITION_FULLSCREEN	9 // Console Window will occupy the entire screen (Without any border or desktop)(If supported)

#define CONSOLE_POSITION_UNKNOWN	(uint32_t)-1

/* ============================================================================== */
/* Framebuffer Depth constants */
#define FRAMEBUFFER_DEPTH_8	8
#define FRAMEBUFFER_DEPTH_16	16
#define FRAMEBUFFER_DEPTH_24	24
#define FRAMEBUFFER_DEPTH_32	32

/* Framebuffer Pixel Order constants */
#define FRAMEBUFFER_ORDER_BGR	0
#define FRAMEBUFFER_ORDER_RGB	1

/* Framebuffer Alpha Mode constants */
#define FRAMEBUFFER_MODE_ENABLED	0 // Alpha channel enabled (0 = Fully opaque)
#define FRAMEBUFFER_MODE_REVERSED	1 // Alpha channel reversed (0 = Fully transparent)
#define FRAMEBUFFER_MODE_IGNORED	2 // Alpha channel ignored

/* Framebuffer Rotation constants */
#define FRAMEBUFFER_ROTATION_0	0 // No rotation
#define FRAMEBUFFER_ROTATION_90	1 // 90 degree rotation
#define FRAMEBUFFER_ROTATION_180	2 // 180 degree rotation
#define FRAMEBUFFER_ROTATION_270	3 // 270 degree rotation

/* ============================================================================== */
/* Log Level constants */
#define LOG_LEVEL_DEBUG	1 // Debugging messages
#define LOG_LEVEL_INFO	2 // Informational messages
#define LOG_LEVEL_WARN	3 // Warning messages
#define LOG_LEVEL_ERROR	4 // Error messages
#define LOG_LEVEL_NONE	5 // No messages

/* Logging Protocol constants */
#define LOGGING_PROTOCOL_UDP	0
#define LOGGING_PROTOCOL_TCP	1

/* Logging Facility constants */
#define LOGGING_FACILITY_KERNEL	0 // Core "kernel" log messages
#define LOGGING_FACILITY_PLATFORM	1 // Platform log messages
#define LOGGING_FACILITY_THREADS	2 // Thread log messages
#define LOGGING_FACILITY_DEVICES	3 // Device log messages
#define LOGGING_FACILITY_NETWORK	4 // Network log messages
#define LOGGING_FACILITY_STORAGE	5 // Storage log messages
#define LOGGING_FACILITY_FILESYSTEM	6 // Filesystem log messages
#define LOGGING_FACILITY_KEYBOARD	7 // Keyboard log messages
#define LOGGING_FACILITY_MOUSE	8 // Mouse log messages
#define LOGGING_FACILITY_SCSI	9 // SCSI log messages
#define LOGGING_FACILITY_DMA	10 // DMA log messages
#define LOGGING_FACILITY_GPIO	11 // GPIO log messages
#define LOGGING_FACILITY_MMC	12 // MMC/SD log messages
#define LOGGING_FACILITY_USB	13 // USB log messages
#define LOGGING_FACILITY_SERVICES	14 // Services log messages
#define LOGGING_FACILITY_HTTP	15 // HTTP log messages
#define LOGGING_FACILITY_IMAP	16 // IMAP4 log messages
#define LOGGING_FACILITY_POP	17 // POP3 log messages
#define LOGGING_FACILITY_SMTP	18 // SMTP log messages
#define LOGGING_FACILITY_TELNET	19 // Telnet log messages
#define LOGGING_FACILITY_SSH	20 // SSH log messages
#define LOGGING_FACILITY_SHELL	21 // Shell log messages
#define LOGGING_FACILITY_NTP	22 // NTP log messages
#define LOGGING_FACILITY_FTP	23 // FTP log messages
#define LOGGING_FACILITY_RTC	24 // RTC log messages
#define LOGGING_FACILITY_I2C	25 // I2C log messages
#define LOGGING_FACILITY_I2S	26 // I2S log messages
#define LOGGING_FACILITY_PWM	27 // PWM log messages
#define LOGGING_FACILITY_SERIAL	28 // Serial log messages
#define LOGGING_FACILITY_SPI	29 // SPI log messages
#define LOGGING_FACILITY_UART	30 // UART log messages
#define LOGGING_FACILITY_AUDIO	31 // Audio log messages
#define LOGGING_FACILITY_1WIRE	32 // 1-Wire log messages
#define LOGGING_FACILITY_TOUCH	33 // Touch log messages
#define LOGGING_FACILITY_VIDEO	34 // Video log messages
#define LOGGING_FACILITY_CODEC	35 // Codec log messages
#define LOGGING_FACILITY_NFS	36 // NFS log messages
#define LOGGING_FACILITY_RPC	37 // RPC log messages

#define LOGGING_FACILITY_USER	1000 // User log messages

#define LOGGING_FACILITY_INVALID	0xFFFFFFFF

/* Logging Severity constants */
#define LOGGING_SEVERITY_ERROR	0 // Error log messages
#define LOGGING_SEVERITY_WARN	1 // Warning log messages
#define LOGGING_SEVERITY_INFO	2 // Informational log messages
#define LOGGING_SEVERITY_DEBUG	3 // Debugging log messages

#define LOGGING_SEVERITY_INVALID	0xFFFFFFFF

/* ============================================================================== */
/* Handle Type constants */
#define HANDLE_TYPE_SPIN	1
#define HANDLE_TYPE_MUTEX	2
#define HANDLE_TYPE_SECTION	3
#define HANDLE_TYPE_SEMAPHORE	4
#define HANDLE_TYPE_SYNCHRONIZER	5
#define HANDLE_TYPE_CONDITION	6
#define HANDLE_TYPE_COMPLETION	7
#define HANDLE_TYPE_LIST	8
#define HANDLE_TYPE_QUEUE	9
#define HANDLE_TYPE_THREAD	10
#define HANDLE_TYPE_MESSAGESLOT	11
#define HANDLE_TYPE_MAILSLOT	12
#define HANDLE_TYPE_BUFFER	13
#define HANDLE_TYPE_EVENT	14

#define HANDLE_TYPE_TIMER	15
#define HANDLE_TYPE_WORKER	16
#define HANDLE_TYPE_WINDOW	17
#define HANDLE_TYPE_FONT	18
#define HANDLE_TYPE_KEYMAP	19

#define HANDLE_TYPE_FILE	100
#define HANDLE_TYPE_PIPE	101
#define HANDLE_TYPE_SOCKET	102
#define HANDLE_TYPE_DEVICE	103

#define HANDLE_TYPE_USER_BASE	1000 // Base value for user or application defined handle types

/* ============================================================================== */
/* Filesystem Cache Mode constants */
#define FILESYS_CACHE_MODE_NONE	0
#define FILESYS_CACHE_MODE_READONLY	1
#define FILESYS_CACHE_MODE_READWRITE	2

/* ============================================================================== */
/* Cursor constants */
/* Standard Arrow in 32 bit ARGB */
#define CURSOR_ARROW_DEFAULT_WIDTH	16 // Must be >= 16 and <= 64 on Raspberry Pi
#define CURSOR_ARROW_DEFAULT_HEIGHT	18 // Must be >= 16 and <= 64 on Raspberry Pi
#define CURSOR_ARROW_DEFAULT_FORMAT	COLOR_FORMAT_DEFAULT // COLOR_FORMAT_ARGB32
const uint32_t CURSOR_ARROW_DEFAULT[CURSOR_ARROW_DEFAULT_WIDTH * CURSOR_ARROW_DEFAULT_HEIGHT] = {
 COLOR_BLACK,COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_BLACK,COLOR_NONE, COLOR_NONE, COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_BLACK,COLOR_NONE, COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_BLACK,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_BLACK,COLOR_WHITE,COLOR_WHITE,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE,
 COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_BLACK,COLOR_BLACK,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE ,COLOR_NONE};

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_GLOBALCONST_H