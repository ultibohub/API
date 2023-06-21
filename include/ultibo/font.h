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
#ifndef _ULTIBO_FONT_H
#define _ULTIBO_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"

/* ============================================================================== */
/* Font specific constants */
#define FONT_MIN_COUNT	256

#define FONT_MIN_WIDTH	8
#define FONT_MAX_WIDTH	32

#define FONT_MIN_HEIGHT	6
#define FONT_MAX_HEIGHT	64

/* Font Signature */
#define FONT_SIGNATURE	0x77DE1BBC

/* Font name constants */
#define FONT_NAME_LENGTH	SIZE_64 // Length of font name
#define FONT_DESC_LENGTH	SIZE_128 // Length of font description

/* Font Mode constants */
#define FONT_MODE_NONE	0
#define FONT_MODE_PIXEL	1 // A font with 1 bit per pixel in the character data
#define FONT_MODE_ALPHA8	2 // A font with 8 bits of alpha blending per pixel in the character data
#define FONT_MODE_RGBA32	3 // A font with 32 bits RGBA per pixel in the character data

/* Font Flag constants */
#define FONT_FLAG_NONE	0x00000000
#define FONT_FLAG_UNICODE	0x00000001 // Font includes a unicode translation table
#define FONT_FLAG_CODEPAGE	0x00000002 // Font has a specified codepage
#define FONT_FLAG_BIGENDIAN	0x00000004 // Font characters are in big endian order (Only applies to characters larger than one byte)
#define FONT_FLAG_RIGHTALIGN	0x00000008 // Font characters are right aligned, no need to shift during load
#define FONT_FLAG_VARIABLE	0x00000010 // Font characters are variable width rather than fixed

/* ============================================================================== */
/* Font specific types */

/* Font Header */
typedef struct _FONT_HEADER FONT_HEADER;
struct _FONT_HEADER
{
	uint32_t width; // Width of each character in pixels
	uint32_t height; // Height of each character in pixels
	uint32_t count; // Number of character glyphs in data
	uint32_t mode; // Font mode (eg FONT_MODE_PIXEL)
	uint32_t flags; // Font flags (eg FONT_FLAG_UNICODE)
	uint32_t mask; // Transparency mask for a bitmap font
	uint32_t codepage; // Font codepage (CP_ACP if not specified)
	char name[64]; // Font name //NOT null terminated, index 0 is the length
	char description[128]; // Font description //NOT null terminated, index 0 is the length
};

/* Font Data */
typedef struct _FONT_DATA FONT_DATA;
struct _FONT_DATA
{
	uint8_t data[0];
};

/* Font Data (8 bit width) (uint8_t) */
typedef struct _FONT_DATA_8X6 FONT_DATA_8X6;
struct _FONT_DATA_8X6
{
    uint8_t data[256][6];
};

typedef struct _FONT_DATA_8X7 FONT_DATA_8X7;
struct _FONT_DATA_8X7
{
	uint8_t data[256][7];
};

typedef struct _FONT_DATA_8X8 FONT_DATA_8X8;
struct _FONT_DATA_8X8
{
	uint8_t data[256][8];
};

typedef struct _FONT_DATA_8X9 FONT_DATA_8X9;
struct _FONT_DATA_8X9
{
	uint8_t data[256][9];
};

typedef struct _FONT_DATA_8X10 FONT_DATA_8X10;
struct _FONT_DATA_8X10
{
	uint8_t data[256][10];
};

typedef struct _FONT_DATA_8X11 FONT_DATA_8X11;
struct _FONT_DATA_8X11
{
	uint8_t data[256][11];
};

typedef struct _FONT_DATA_8X12 FONT_DATA_8X12;
struct _FONT_DATA_8X12
{
	uint8_t data[256][12];
};

typedef struct _FONT_DATA_8X13 FONT_DATA_8X13;
struct _FONT_DATA_8X13
{
	uint8_t data[256][13];
};

typedef struct _FONT_DATA_8X14 FONT_DATA_8X14;
struct _FONT_DATA_8X14
{
	uint8_t data[256][14];
};

typedef struct _FONT_DATA_8X15 FONT_DATA_8X15;
struct _FONT_DATA_8X15
{
	uint8_t data[256][15];
};

typedef struct _FONT_DATA_8X16 FONT_DATA_8X16;
struct _FONT_DATA_8X16
{
	uint8_t data[256][16];
};

/* Font Data (12 bit width) (uint16_t) */
typedef struct _FONT_DATA_12X12 FONT_DATA_12X12;
struct _FONT_DATA_12X12
{
	uint16_t data[256][12];
};

typedef struct _FONT_DATA_12X14 FONT_DATA_12X14;
struct _FONT_DATA_12X14
{
	uint16_t data[256][14];
};

typedef struct _FONT_DATA_12X16 FONT_DATA_12X16;
struct _FONT_DATA_12X16
{
	uint16_t data[256][16];
};

typedef struct _FONT_DATA_12X18 FONT_DATA_12X18;
struct _FONT_DATA_12X18
{
	uint16_t data[256][18];
};

typedef struct _FONT_DATA_12X20 FONT_DATA_12X20;
struct _FONT_DATA_12X20
{
	uint16_t data[256][20];
};

typedef struct _FONT_DATA_12X22 FONT_DATA_12X22;
struct _FONT_DATA_12X22
{
	uint16_t data[256][22];
};

/* Font Data (16 bit width) (uint16_t) */
typedef struct _FONT_DATA_16X16 FONT_DATA_16X16;
struct _FONT_DATA_16X16
{
	uint16_t data[256][16];
};

typedef struct _FONT_DATA_16X24 FONT_DATA_16X24;
struct _FONT_DATA_16X24
{
	uint16_t data[256][24];
};

typedef struct _FONT_DATA_16X32 FONT_DATA_16X32;
struct _FONT_DATA_16X32
{
	uint16_t data[256][32];
};

/* Font Data (32 bit width) (uint32_t) */
typedef struct _FONT_DATA_32X32 FONT_DATA_32X32;
struct _FONT_DATA_32X32
{
	uint32_t data[256][32];
};

typedef struct _FONT_DATA_32X48 FONT_DATA_32X48;
struct _FONT_DATA_32X48
{
	uint32_t data[256][48];
};

typedef struct _FONT_DATA_32X64 FONT_DATA_32X64;
struct _FONT_DATA_32X64
{
	uint32_t data[256][64];
};

/* Font Chars */
typedef uint8_t FONT_CHARS_8[];
typedef uint16_t FONT_CHARS_16[];
typedef uint32_t FONT_CHARS_32[];

/* Font Unicode */
typedef struct _FONT_UNICODE FONT_UNICODE;
struct _FONT_UNICODE
{
	// To Do
};

/* Font Properties */
typedef struct _FONT_PROPERTIES FONT_PROPERTIES;
struct _FONT_PROPERTIES
{
	uint32_t fontmode; // Font mode (eg FONT_MODE_PIXEL)
	uint32_t fontflags; // Font flags (eg FONT_FLAG_UNICODE)
	char fontname[FONT_NAME_LENGTH]; // Font name
	char fontdescription[FONT_DESC_LENGTH]; // Font description
	uint32_t charwidth; // Font character width in pixels
	uint32_t charheight; // Font character height in pixels
	uint32_t charcount; // Number of glyphs in font character table
	uint32_t charmask; // Transparency mask for a bitmap font (Not used for a pixel font)
	uint32_t codepage; // Font codepage (CP_ACP if not specified)
};

typedef struct _FONT_ENTRY FONT_ENTRY;

/* Font Enumeration Callback */
typedef uint32_t STDCALL (*font_enumerate_cb)(FONT_HANDLE handle, void *data);

/* Font Entry */
struct _FONT_ENTRY
{
	// Font Properties
	uint32_t signature; // Signature for entry validation
	uint32_t fontmode; // Font mode (eg FONT_MODE_PIXEL)
	uint32_t fontflags; // Font flags (eg FONT_FLAG_UNICODE)
	char fontname[FONT_NAME_LENGTH]; // Font name
	char fontdescription[FONT_DESC_LENGTH]; // Font description
	// Driver Properties
	uint32_t charwidth; // Font character width in pixels
	uint32_t charheight; // Font character height in pixels
	uint32_t charcount; // Number of glyphs in font character table
	uint32_t charmask; // Transparency mask for a bitmap font (Not used for a pixel font)
	uint32_t codepage; // Font codepage (CP_ACP if not specified)
	void *chardata; // Font character pixel or bitmap data
	FONT_UNICODE *unicodedata; // Font unicode translation data (Only if FONT_FLAG_UNICODE)
	// Internal Properties
	FONT_ENTRY *prev; // Previous entry in Font table
	FONT_ENTRY *next; // Next entry in Font table
};

/* ============================================================================== */
/* Font Functions */
FONT_HANDLE STDCALL font_load(FONT_HEADER *header, FONT_DATA *data, uint32_t size);
FONT_HANDLE STDCALL font_load_ex(FONT_HEADER *header, FONT_DATA *data, FONT_UNICODE *unicode, uint32_t size, FONT_PROPERTIES *properties);
uint32_t STDCALL font_unload(FONT_HANDLE handle);

uint32_t STDCALL font_get_name(FONT_HANDLE handle, char *name, uint32_t len);
uint32_t STDCALL font_get_description(FONT_HANDLE handle, char *description, uint32_t len);

uint32_t STDCALL font_get_width(FONT_HANDLE handle);
uint32_t STDCALL font_get_height(FONT_HANDLE handle);

uint32_t STDCALL font_get_properties(FONT_HANDLE handle, FONT_PROPERTIES *properties);

uint32_t STDCALL font_char_width(FONT_HANDLE handle, uint16_t character);
uint32_t STDCALL font_char_height(FONT_HANDLE handle, uint16_t character);

uint32_t STDCALL font_text_width(FONT_HANDLE handle, char *text);
uint32_t STDCALL font_text_height(FONT_HANDLE handle, char *text);

FONT_HANDLE STDCALL font_find_by_name(char *name);
FONT_HANDLE STDCALL font_find_by_description(char *description);
uint32_t STDCALL font_enumerate(font_enumerate_cb callback, void *data);

/* ============================================================================== */
/* PSF Font Functions */
FONT_HANDLE STDCALL psf_font_load(char *filename);
FONT_HANDLE STDCALL psf_font_load_ex(void *data, uint32_t size);

/* ============================================================================== */
/* Font Helper Functions */
uint32_t STDCALL font_get_count(void);
FONT_HANDLE STDCALL font_get_default(void);
uint32_t STDCALL font_set_default(FONT_HANDLE handle);

FONT_ENTRY * STDCALL font_check(FONT_ENTRY *font);

/* ============================================================================== */
/* PSF Font Helper Functions */

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_FONT_H