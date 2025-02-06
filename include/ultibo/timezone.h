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
#ifndef _ULTIBO_TIMEZONE_H
#define _ULTIBO_TIMEZONE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/sysutils.h"

/* ============================================================================== */
/* Timezone specific constants */
#define TIME_ZONE_ID_UNKNOWN	0
#define TIME_ZONE_ID_STANDARD	1
#define TIME_ZONE_ID_DAYLIGHT	2
#define TIME_ZONE_ID_INVALID	(DWORD)0xFFFFFFFF

/* Timezone Signature */
#define TIMEZONE_SIGNATURE	0xED9A1BC3

/* Timezone name constants */
#define TIMEZONE_NAME_LENGTH	SIZE_64 // Length of timezone name
#define TIMEZONE_DESC_LENGTH	SIZE_128 // Length of timezone description

/* ============================================================================== */
/* Timezone specific types */

/* Timezone types */
typedef struct _TIME_ZONE_INFORMATION TIME_ZONE_INFORMATION;
struct _TIME_ZONE_INFORMATION
{
	long bias;
	WCHAR standardname[32];
	SYSTEMTIME standarddate;
	long standardbias;
	WCHAR daylightname[32];
	SYSTEMTIME daylightdate;
	long daylightbias;
};

/* Timezone Data */
typedef struct _TIMEZONE_DATA TIMEZONE_DATA;
struct _TIMEZONE_DATA
{
	char name[33]; //NOT null terminated, index 0 is the length
	char description[65]; //NOT null terminated, index 0 is the length
	int32_t bias;
	char standardname[33]; //NOT null terminated, index 0 is the length
	int32_t standardbias;
	SYSTEMTIME standardstart;
	char daylightname[33]; //NOT null terminated, index 0 is the length
	int32_t daylightbias;
	SYSTEMTIME daylightstart;
};

typedef struct _TIMEZONE_ENTRY TIMEZONE_ENTRY;

/* Timezone Enumeration Callback */
typedef uint32_t STDCALL (*timezone_enumerate_cb)(TIMEZONE_ENTRY *timezone, void *data);

/* Timezone Entry */
struct _TIMEZONE_ENTRY
{
	// Timezone Properties
	uint32_t signature; // Signature for entry validation
	char name[TIMEZONE_NAME_LENGTH]; // Timezone name
	char description[TIMEZONE_DESC_LENGTH]; // Timezone description
	int32_t bias;
	char standardname[TIMEZONE_NAME_LENGTH]; // Standard name
	int32_t standardbias;
	SYSTEMTIME standardstart;
	char daylightname[TIMEZONE_NAME_LENGTH]; // Daylight name
	int32_t daylightbias;
	SYSTEMTIME daylightstart;
	// Internal Properties
	TIMEZONE_ENTRY *prev; // Previous entry in Timezone table
	TIMEZONE_ENTRY *next; // Next entry in Timezone table
};

/* ============================================================================== */
/* Timezone Functions */
uint32_t STDCALL timezone_add(TIMEZONE_DATA *data, BOOL _default);
uint32_t STDCALL timezone_delete(TIMEZONE_ENTRY *timezone);

uint32_t STDCALL timezone_get_name(TIMEZONE_ENTRY *timezone, char *name, uint32_t len);
uint32_t STDCALL timezone_get_description(TIMEZONE_ENTRY *timezone, char *description, uint32_t len);

int32_t STDCALL timezone_get_bias(TIMEZONE_ENTRY *timezone);
uint32_t STDCALL timezone_get_state(TIMEZONE_ENTRY *timezone);
uint32_t STDCALL timezone_get_state_ex(TIMEZONE_ENTRY *timezone, double_t datetime);
int32_t STDCALL timezone_get_active_bias(TIMEZONE_ENTRY *timezone);
int32_t STDCALL timezone_get_active_bias_ex(TIMEZONE_ENTRY *timezone, double_t datetime);

uint32_t STDCALL timezone_get_standard_name(TIMEZONE_ENTRY *timezone, char *name, uint32_t len);
int32_t STDCALL timezone_get_standard_bias(TIMEZONE_ENTRY *timezone);
double_t STDCALL timezone_get_standard_date(TIMEZONE_ENTRY *timezone, BOOL next);
SYSTEMTIME STDCALL timezone_get_standard_start(TIMEZONE_ENTRY *timezone);

uint32_t STDCALL timezone_get_daylight_name(TIMEZONE_ENTRY *timezone, char *name, uint32_t len);
int32_t STDCALL timezone_get_daylight_bias(TIMEZONE_ENTRY *timezone);
double_t STDCALL timezone_get_daylight_date(TIMEZONE_ENTRY *timezone, BOOL next);
SYSTEMTIME STDCALL timezone_get_daylight_start(TIMEZONE_ENTRY *timezone);

TIMEZONE_ENTRY * STDCALL timezone_find(const char *name);
TIMEZONE_ENTRY * STDCALL timezone_find_by_standard(const char *standardname);
TIMEZONE_ENTRY * STDCALL timezone_find_by_daylight(const char *daylightname);

uint32_t STDCALL timezone_enumerate(timezone_enumerate_cb callback, void *data);

/* ============================================================================== */
/* Timezone Helper Functions */
uint32_t STDCALL timezone_get_count(void);
TIMEZONE_ENTRY * STDCALL timezone_get_default(void);
uint32_t STDCALL timezone_set_default(TIMEZONE_ENTRY *timezone);

TIMEZONE_ENTRY * STDCALL timezone_check(TIMEZONE_ENTRY *timezone);

uint32_t STDCALL timezone_update_offset(void);

double_t STDCALL timezone_start_to_date_time(SYSTEMTIME *start, uint16_t year);
uint32_t STDCALL timezone_start_to_description(SYSTEMTIME *start, char *description, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_TIMEZONE_H