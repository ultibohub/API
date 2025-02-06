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
#ifndef _ULTIBO_KEYMAP_H
#define _ULTIBO_KEYMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"

/* ============================================================================== */
/* Keymap specific constants */
#define KEYMAP_KEY_COUNT	256 // Number of key mappings in a keymap entry
#define KEYMAP_ROW_COUNT	4 // Number of mapping rows per key in a keymap entry (Normal, Shift, AltGr, Shift_AltGr)
#define KEYMAP_ROW_SIZE	sizeof(uint16_t)

#define KEYMAP_MAX_CAPSKEYS	50 // Maximum number of keys that can be listed in the TKeymapCapskeys structure
#define KEYMAP_MAX_DEADKEYS	5 // Maximum number of keys that can be listed in the TKeymapDeadkeys structure
#define KEYMAP_MAX_RESOLVES	20 // Maximum number of resolves that can be listed in the TKeymapDeadkey structure

/* Keymap Signature */
#define KEYMAP_SIGNATURE	0x863FDBA1

/* Keymap name constants */
#define KEYMAP_NAME_LENGTH	SIZE_64 // Length of keymap name
#define KEYMAP_DESC_LENGTH	SIZE_128 // Length of keymap description

/* Keymap Mode constants */
#define KEYMAP_MODE_NONE	0

/* Keymap Flag constants */
#define KEYMAP_FLAG_NONE	0x00000000
#define KEYMAP_FLAG_ALTGR	0x00000001 // The key mapping uses the AltGr key
#define KEYMAP_FLAG_CAPS_ALL	0x00000002 // Caps Lock shifts all characters not just alphabetic
#define KEYMAP_FLAG_CAPS_ASCII	0x00000004 // Caps Lock shifts only ASCII characters A to Z

/* Keymap Index constants */
#define KEYMAP_INDEX_NORMAL	0 // Normal (unshifted) value
#define KEYMAP_INDEX_SHIFT	1 // Shifted value
#define KEYMAP_INDEX_ALTGR	2 // AltGr value
#define KEYMAP_INDEX_SHIFT_ALTGR	3 // Shift plus AltGr value

#define KEYMAP_INDEX_COUNT	4

/* ============================================================================== */
/* Keymap specific types */

/* Keymap Header */
typedef struct _KEYMAP_HEADER
{
	uint32_t mode; // Keymap mode (eg KEYMAP_MODE_NONE)
	uint32_t flags; // Keymap flags (eg KEYMAP_FLAG_ALTGR)
	uint32_t keycount; // Number of keys in keymap (Default: KEYMAP_KEY_COUNT)
	uint32_t rowcount; // Number of index rows in keymap (Default: KEYMAP_ROW_COUNT)
	char name[256]; // Keymap name //NOT null terminated, index 0 is the length
	char description[256]; // Keymap description //NOT null terminated, index 0 is the length
} KEYMAP_HEADER;

/* Keymap Data */
typedef struct _KEYMAP_DATA
{
	uint16_t data[256][KEYMAP_INDEX_COUNT]; // Key mapping data, 4 words for Normal, Shift, AltGr, Shift+AltGr for each of the 256 keys (See KEY_CODE_* constants)
} KEYMAP_DATA;

/* Keymap Chars */
typedef uint16_t KEYMAP_CHARS[];

/* Keymap Capskey (Keys affected by the Caps Lock function) */
typedef struct _KEYMAP_CAPSKEY
{
	uint16_t first; // First key in caps key range (SCAN_CODE_* value)
	uint16_t last; // Last key in caps key range (SCAN_CODE_* value)(Make first and last the same for a single key)
} KEYMAP_CAPSKEY;

/* Keymap Capskeys */
typedef struct _KEYMAP_CAPSKEYS
{
	uint32_t count;
	KEYMAP_CAPSKEY keys[KEYMAP_MAX_CAPSKEYS];
} KEYMAP_CAPSKEYS;

/* Keymap Resolve */
typedef struct _KEYMAP_RESOLVE
{
	uint16_t key; // The scan code of the key pressed after the deadkey (SCAN_CODE_* value)
	uint8_t index; // The index state of the key pressed after the deadkey (eg KEYMAP_INDEX_NORMAL)
	uint16_t code; // The key code of the resulting character (KEY_CODE_* value)
} KEYMAP_RESOLVE;

/* Keymap Deadkey (Keys which behave as dead keys) */
typedef struct _KEYMAP_DEADKEY
{
	uint16_t key; // The scan code of the key which behaves as a deadkey (SCAN_CODE_* value)
	uint8_t index; // The index state in which the key behaves as a deadkey (eg KEYMAP_INDEX_NORMAL)
	KEYMAP_RESOLVE resolves[KEYMAP_MAX_RESOLVES];
} KEYMAP_DEADKEY;

/* Keymap Deadkeys */
typedef struct _KEYMAP_DEADKEYS
{
	uint32_t count;
	KEYMAP_DEADKEY keys[KEYMAP_MAX_DEADKEYS];
} KEYMAP_DEADKEYS;

/* Keymap Properties */
typedef struct _KEYMAP_PROPERTIES KEYMAP_PROPERTIES;
struct _KEYMAP_PROPERTIES
{
	uint32_t keymapmode; // Keymap mode (eg KEYMAP_MODE_NONE)
	uint32_t keymapflags; // Keymap flags (eg KEYMAP_FLAG_ALTGR)
	uint32_t keycount; // Number of keys in keymap (Default: KEYMAP_KEY_COUNT)
	uint32_t rowcount; // Number of index rows in keymap (Default: KEYMAP_ROW_COUNT)
	char keymapname[KEYMAP_NAME_LENGTH]; // Keymap name
	char keymapdescription[KEYMAP_DESC_LENGTH]; // Keymap description
};

typedef struct _KEYMAP_ENTRY KEYMAP_ENTRY;

/* Keymap Enumeration Callback */
typedef uint32_t STDCALL (*keymap_enumerate_cb)(KEYMAP_HANDLE handle, void *data);

/* Keymap Entry */
struct _KEYMAP_ENTRY
{
	// Keymap Properties
	uint32_t signature; // Signature for entry validation
	uint32_t keymapmode; // Keymap mode (eg KEYMAP_MODE_NONE)
	uint32_t keymapflags; // Keymap flags (eg KEYMAP_FLAG_ALTGR)
	char keymapname[KEYMAP_NAME_LENGTH]; // Keymap name
	char keymapdescription[KEYMAP_DESC_LENGTH]; // Keymap description
	// Driver Properties
	void *keydata; // Keymap key data
	uint32_t keycount; // Number of keys in key data (Default: KEYMAP_KEY_COUNT)
	uint32_t rowcount; // Number of index rows in key data (Default: KEYMAP_ROW_COUNT)
	KEYMAP_CAPSKEYS *capskeysdata; // Keymap Capskeys data (Keys affected by Caps Lock)
	KEYMAP_DEADKEYS *deadkeysdata; // Keymap Deadkeys data (Keys which behave as Dead keys)
	// Internal Properties
	KEYMAP_ENTRY *prev; // Previous entry in Keymap table
	KEYMAP_ENTRY *next; // Next entry in Keymap table
};

/* ============================================================================== */
/* Keymap Functions */
KEYMAP_HANDLE STDCALL keymap_load(KEYMAP_HEADER *header, KEYMAP_DATA *data, uint32_t size);
KEYMAP_HANDLE STDCALL keymap_load_ex(KEYMAP_HEADER *header, KEYMAP_DATA *data, KEYMAP_CAPSKEYS *capskeys, KEYMAP_DEADKEYS *deadkeys, uint32_t size, KEYMAP_PROPERTIES *properties);
uint32_t STDCALL keymap_unload(KEYMAP_HANDLE handle);

uint32_t STDCALL keymap_get_name(KEYMAP_HANDLE handle, char *name, uint32_t len);
uint32_t STDCALL keymap_get_description(KEYMAP_HANDLE handle, char *description, uint32_t len);

BOOL STDCALL keymap_check_flag(KEYMAP_HANDLE handle, uint32_t flag);

uint16_t STDCALL keymap_get_key_code(KEYMAP_HANDLE handle, uint16_t scancode, uint8_t index);

char STDCALL keymap_get_char_code(KEYMAP_HANDLE handle, uint16_t keycode);
WCHAR STDCALL keymap_get_char_unicode(KEYMAP_HANDLE handle, uint16_t keycode);

BOOL STDCALL keymap_check_capskey(KEYMAP_HANDLE handle, uint16_t scancode);

BOOL STDCALL keymap_check_deadkey(KEYMAP_HANDLE handle, uint16_t scancode, uint8_t index);
BOOL STDCALL keymap_resolve_deadkey(KEYMAP_HANDLE handle, uint16_t deadcode, uint16_t scancode, uint8_t deadindex, uint8_t scanindex, uint16_t *keycode);

uint32_t STDCALL keymap_get_properties(KEYMAP_HANDLE handle, KEYMAP_PROPERTIES *properties);

KEYMAP_HANDLE STDCALL keymap_find_by_name(const char *name);
KEYMAP_HANDLE STDCALL keymap_find_by_description(const char *description);
uint32_t STDCALL keymap_enumerate(keymap_enumerate_cb callback, void *data);

/* ============================================================================== */
/* Keymap Helper Functions */
uint32_t STDCALL keymap_get_count(void);
KEYMAP_HANDLE STDCALL keymap_get_default(void);
uint32_t STDCALL keymap_set_default(KEYMAP_HANDLE handle);

KEYMAP_ENTRY * STDCALL keymap_check(KEYMAP_ENTRY *keymap);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_KEYMAP_H