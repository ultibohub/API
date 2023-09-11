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
#ifndef _ULTIBO_LOCALE_H
#define _ULTIBO_LOCALE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/sysutils.h"

/* ============================================================================== */
/* Locale specific constants */

/* Default Code Pages */
#define CP_ACP	0 // Default to ANSI code page
#define CP_OEMCP	1 // Default to OEM  code page
#define CP_MACCP	2 // Default to MAC  code page
#define CP_THREAD_ACP	3 // Current thread's ANSI code page
#define CP_SYMBOL	42 // SYMBOL translations
#define CP_UTF16	1200 // UTF-16 translation
#define CP_UNICODE	1200 // Unicode translation
#define CP_UTF16_BE	1201 // UTF-16 (unicodeFFFE) translation
#define CP_UTF7	65000 // UTF-7 translation
#define CP_UTF8	65001 // UTF-8 translation
//#define CP_ASCII  20127 {US-ASCII}
//#define CP_NONE   0xFFFF {FPC RawByteString}

/* Code Page Identifiers (See: https://en.wikipedia.org/wiki/Code_page) */
#define CP_OEM_437	437 // US
#define CP_OEM_720	720 // Arabic
#define CP_OEM_737	737 // Greek
#define CP_OEM_775	775 // Baltic
#define CP_OEM_850	850 // Latin I
#define CP_OEM_852	852 // Latin II
#define CP_OEM_857	857 // Turkish
#define CP_OEM_862	862 // Hebrew
#define CP_OEM_866	866 // Russian
#define CP_OEM_874	874 // Thai
#define CP_OEM_1258	1258 // Vietnam

#define CP_ANSI_1250	1250 // Central Europe
#define CP_ANSI_1251	1251 // Cyrillic
#define CP_ANSI_1252	1252 // Latin I
#define CP_ANSI_1253	1253 // Greek
#define CP_ANSI_1254	1254 // Turkish
#define CP_ANSI_1255	1255 // Hebrew
#define CP_ANSI_1256	1256 // Arabic
#define CP_ANSI_1257	1257 // Baltic
#define CP_ANSI_1258	1258 // Vietnam
#define CP_ANSI_874	874 // Thai

/* Default Locales */
#define LOCALE_SYSTEM_DEFAULT	0x800
#define LOCALE_USER_DEFAULT	0x400

/* String Length Maximums */
#define MAX_LEADBYTES	12 // 5 ranges, 2 bytes each, 0 terminated
#define MAX_DEFAULTCHAR	2 // single or double byte

/* MBCS and Unicode Translation Flags */
#define MB_PRECOMPOSED	0x00000001 // use precomposed chars
#define MB_COMPOSITE	0x00000002 // use composite chars
#define MB_USEGLYPHCHARS	0x00000004 // use glyph chars, not ctrl chars
#define MB_ERR_INVALID_CHARS	0x00000008 // error for invalid chars

#define WC_COMPOSITECHECK	0x00000200 // convert composite to precomposed
#define WC_DISCARDNS	0x00000010 // discard non-spacing chars
#define WC_SEPCHARS	0x00000020 // generate separate chars
#define WC_DEFAULTCHAR	0x00000040 // replace w/ default AnsiChar

#define WC_NO_BEST_FIT_CHARS	0x00000400 // do not use best fit chars

/* Character Type Flags */
#define CT_CTYPE1	0x00000001 //  ctype 1 information
#define CT_CTYPE2	0x00000002 //  ctype 2 information
#define CT_CTYPE3	0x00000004 //  ctype 3 information

/* CType 1 Flag Bits */
#define C1_UPPER	0x0001 //  upper case
#define C1_LOWER	0x0002 //  lower case
#define C1_DIGIT	0x0004 //  decimal digits
#define C1_SPACE	0x0008 //  spacing characters
#define C1_PUNCT	0x0010 //  punctuation characters
#define C1_CNTRL	0x0020 //  control characters
#define C1_BLANK	0x0040 //  blank characters
#define C1_XDIGIT	0x0080 //  other digits
#define C1_ALPHA	0x0100 //  any linguistic character
#define C1_DEFINED	0x0200 //  defined character

/* CType 2 Flag Bits */
#define C2_LEFTTORIGHT	0x0001 //  left to right
#define C2_RIGHTTOLEFT	0x0002 //  right to left

#define C2_EUROPENUMBER	0x0003 //  European number, digit
#define C2_EUROPESEPARATOR	0x0004 //  European numeric separator
#define C2_EUROPETERMINATOR	0x0005 //  European numeric terminator
#define C2_ARABICNUMBER	0x0006 //  Arabic number
#define C2_COMMONSEPARATOR	0x0007 //  common numeric separator

#define C2_BLOCKSEPARATOR	0x0008 //  block separator
#define C2_SEGMENTSEPARATOR	0x0009 //  segment separator
#define C2_WHITESPACE	0x000A //  white space
#define C2_OTHERNEUTRAL	0x000B //  other neutrals

#define C2_NOTAPPLICABLE	0x0000 //  no implicit directionality

/* CType 3 Flag Bits */
#define C3_NONSPACING	0x0001 //  nonspacing character
#define C3_DIACRITIC	0x0002 //  diacritic mark
#define C3_VOWELMARK	0x0004 //  vowel mark
#define C3_SYMBOL	0x0008 //  symbols

#define C3_KATAKANA	0x0010 //  katakana character
#define C3_HIRAGANA	0x0020 //  hiragana character
#define C3_HALFWIDTH	0x0040 //  half width character
#define C3_FULLWIDTH	0x0080 //  full width character
#define C3_IDEOGRAPH	0x0100 //  ideographic character
#define C3_KASHIDA	0x0200 //  Arabic kashida character
#define C3_LEXICAL	0x0400 //  lexical character

#define C3_ALPHA	0x8000 //  any linguistic AnsiChar (C1_ALPHA)

#define C3_NOTAPPLICABLE	0x0000 //  ctype 3 is not applicable

/* String Flags */
#define NORM_IGNORECASE	0x00000001 //  ignore case
#define NORM_IGNORENONSPACE	0x00000002 //  ignore nonspacing chars
#define NORM_IGNORESYMBOLS	0x00000004 //  ignore symbols

#define NORM_IGNOREKANATYPE	0x00010000 //  ignore kanatype
#define NORM_IGNOREWIDTH	0x00020000 //  ignore width

/* Locale Independent Mapping Flags */
#define MAP_FOLDCZONE	0x00000010 //  fold compatibility zone chars
#define MAP_PRECOMPOSED	0x00000020 //  convert to precomposed chars
#define MAP_COMPOSITE	0x00000040 //  convert to composite chars
#define MAP_FOLDDIGITS	0x00000080 //  all digits to ASCII 0-9

#define MAP_EXPAND_LIGATURES	0x00002000 //  expand all ligatures

/* Locale Dependent Mapping Flags */
#define LCMAP_LOWERCASE	0x00000100 //  lower case letters
#define LCMAP_UPPERCASE	0x00000200 //  upper case letters
#define LCMAP_SORTKEY	0x00000400 //  WC sort key (normalize)
#define LCMAP_BYTEREV	0x00000800 //  byte reversal

#define LCMAP_HIRAGANA	0x00100000 //  map katakana to hiragana
#define LCMAP_KATAKANA	0x00200000 //  map hiragana to katakana
#define LCMAP_HALFWIDTH	0x00400000 //  map double byte to single byte
#define LCMAP_FULLWIDTH	0x00800000 //  map single byte to double byte

#define LCMAP_LINGUISTIC_CASING	0x01000000 //  use linguistic rules for casing

#define LCMAP_SIMPLIFIED_CHINESE	0x02000000 //  map traditional chinese to simplified chinese
#define LCMAP_TRADITIONAL_CHINESE	0x04000000 //  map simplified chinese to traditional chinese

/* Language Group Enumeration Flags */
#define LGRPID_INSTALLED	0x00000001 //  installed language group ids
#define LGRPID_SUPPORTED	0x00000002 //  supported language group ids

/* Locale Enumeration Flags */
#define LCID_INSTALLED	0x00000001 //  installed locale ids
#define LCID_SUPPORTED	0x00000002 //  supported locale ids
#define LCID_ALTERNATE_SORTS	0x00000004 //  alternate sort locale ids

/* Code Page Enumeration Flags */
#define CP_INSTALLED	0x00000001 //  installed code page ids
#define CP_SUPPORTED	0x00000002 //  supported code page ids

/* Sorting Flags */
//     WORD Sort:    culturally correct sort
//                   hyphen and apostrophe are special cased
//                   example: "coop" and "co-op" will sort together in a list
// 
//                         co_op     <-------  underscore (symbol)
//                         coat
//                         comb
//                         coop
//                         co-op     <-------  hyphen (punctuation)
//                         cork
//                         went
//                         were
//                         we're     <-------  apostrophe (punctuation)
// 
// 
//     STRING Sort:  hyphen and apostrophe will sort with all other symbols
// 
//                         co-op     <-------  hyphen (punctuation)
//                         co_op     <-------  underscore (symbol)
//                         coat
//                         comb
//                         coop
//                         cork
//                         we're     <-------  apostrophe (punctuation)
//                         went
//                         were
// 
#define SORT_STRINGSORT	0x00001000 //  use string sort method

/* Compare String Return Values */
#define CSTR_LESS_THAN	1 //  string 1 less than string 2
#define CSTR_EQUAL	2 //  string 1 equal to string 2
#define CSTR_GREATER_THAN	3 //  string 1 greater than string 2

/* Country/Region Codes */
#define CTRY_DEFAULT	0

#define CTRY_ALBANIA	355 //  Albania
#define CTRY_ALGERIA	213 //  Algeria
#define CTRY_ARGENTINA	54 //  Argentina
#define CTRY_ARMENIA	374 //  Armenia
#define CTRY_AUSTRALIA	61 //  Australia
#define CTRY_AUSTRIA	43 //  Austria
#define CTRY_AZERBAIJAN	994 //  Azerbaijan
#define CTRY_BAHRAIN	973 //  Bahrain
#define CTRY_BELARUS	375 //  Belarus
#define CTRY_BELGIUM	32 //  Belgium
#define CTRY_BELIZE	501 //  Belize
#define CTRY_BOLIVIA	591 //  Bolivia
#define CTRY_BRAZIL	55 //  Brazil
#define CTRY_BRUNEI_DARUSSALAM	673 //  Brunei Darussalam
#define CTRY_BULGARIA	359 //  Bulgaria
#define CTRY_CANADA	2 //  Canada
#define CTRY_CARIBBEAN	1 //  Caribbean
#define CTRY_CHILE	56 //  Chile
#define CTRY_COLOMBIA	57 //  Colombia
#define CTRY_COSTA_RICA	506 //  Costa Rica
#define CTRY_CROATIA	385 //  Croatia
#define CTRY_CZECH	420 //  Czech Republic
#define CTRY_DENMARK	45 //  Denmark
#define CTRY_DOMINICAN_REPUBLIC	1 //  Dominican Republic
#define CTRY_ECUADOR	593 //  Ecuador
#define CTRY_EGYPT	20 //  Egypt
#define CTRY_EL_SALVADOR	503 //  El Salvador
#define CTRY_ESTONIA	372 //  Estonia
#define CTRY_FAEROE_ISLANDS	298 //  Faeroe Islands
#define CTRY_FINLAND	358 //  Finland
#define CTRY_FRANCE	33 //  France
#define CTRY_GEORGIA	995 //  Georgia
#define CTRY_GERMANY	49 //  Germany
#define CTRY_GREECE	30 //  Greece
#define CTRY_GUATEMALA	502 //  Guatemala
#define CTRY_HONDURAS	504 //  Honduras
#define CTRY_HONG_KONG	852 //  Hong Kong S.A.R., P.R.C.
#define CTRY_HUNGARY	36 //  Hungary
#define CTRY_ICELAND	354 //  Iceland
#define CTRY_INDIA	91 //  India
#define CTRY_INDONESIA	62 //  Indonesia
#define CTRY_IRAN	981 //  Iran
#define CTRY_IRAQ	964 //  Iraq
#define CTRY_IRELAND	353 //  Ireland
#define CTRY_ISRAEL	972 //  Israel
#define CTRY_ITALY	39 //  Italy
#define CTRY_JAMAICA	1 //  Jamaica
#define CTRY_JAPAN	81 //  Japan
#define CTRY_JORDAN	962 //  Jordan
#define CTRY_KAZAKSTAN	7 //  Kazakstan
#define CTRY_KENYA	254 //  Kenya
#define CTRY_KUWAIT	965 //  Kuwait
#define CTRY_KYRGYZSTAN	996 //  Kyrgyzstan
#define CTRY_LATVIA	371 //  Latvia
#define CTRY_LEBANON	961 //  Lebanon
#define CTRY_LIBYA	218 //  Libya
#define CTRY_LIECHTENSTEIN	41 //  Liechtenstein
#define CTRY_LITHUANIA	370 //  Lithuania
#define CTRY_LUXEMBOURG	352 //  Luxembourg
#define CTRY_MACAU	853 //  Macau S.A.R., PRC
#define CTRY_MACEDONIA	389 //  Former Yugoslav Republic of Macedonia
#define CTRY_MALAYSIA	60 //  Malaysia
#define CTRY_MALDIVES	960 //  Maldives
#define CTRY_MEXICO	52 //  Mexico
#define CTRY_MONACO	33 //  Principality of Monaco
#define CTRY_MONGOLIA	976 //  Mongolia
#define CTRY_MOROCCO	212 //  Morocco
#define CTRY_NETHERLANDS	31 //  Netherlands
#define CTRY_NEW_ZEALAND	64 //  New Zealand
#define CTRY_NICARAGUA	505 //  Nicaragua
#define CTRY_NORWAY	47 //  Norway
#define CTRY_OMAN	968 //  Oman
#define CTRY_PAKISTAN	92 //  Islamic Republic of Pakistan
#define CTRY_PANAMA	507 //  Panama
#define CTRY_PARAGUAY	595 //  Paraguay
#define CTRY_PERU	51 //  Peru
#define CTRY_PHILIPPINES	63 //  Republic of the Philippines
#define CTRY_POLAND	48 //  Poland
#define CTRY_PORTUGAL	351 //  Portugal
#define CTRY_PRCHINA	86 //  People's Republic of China
#define CTRY_PUERTO_RICO	1 //  Puerto Rico
#define CTRY_QATAR	974 //  Qatar
#define CTRY_ROMANIA	40 //  Romania
#define CTRY_RUSSIA	7 //  Russia
#define CTRY_SAUDI_ARABIA	966 //  Saudi Arabia
#define CTRY_SERBIA	381 //  Serbia
#define CTRY_SINGAPORE	65 //  Singapore
#define CTRY_SLOVAK	421 //  Slovak Republic
#define CTRY_SLOVENIA	386 //  Slovenia
#define CTRY_SOUTH_AFRICA	27 //  South Africa
#define CTRY_SOUTH_KOREA	82 //  Korea
#define CTRY_SPAIN	34 //  Spain
#define CTRY_SWEDEN	46 //  Sweden
#define CTRY_SWITZERLAND	41 //  Switzerland
#define CTRY_SYRIA	963 //  Syria
#define CTRY_TAIWAN	886 //  Taiwan
#define CTRY_TATARSTAN	7 //  Tatarstan
#define CTRY_THAILAND	66 //  Thailand
#define CTRY_TRINIDAD_Y_TOBAGO	1 //  Trinidad y Tobago
#define CTRY_TUNISIA	216 //  Tunisia
#define CTRY_TURKEY	90 //  Turkey
#define CTRY_UAE	971 //  U.A.E.
#define CTRY_UKRAINE	380 //  Ukraine
#define CTRY_UNITED_KINGDOM	44 //  United Kingdom
#define CTRY_UNITED_STATES	1 //  United States
#define CTRY_URUGUAY	598 //  Uruguay
#define CTRY_UZBEKISTAN	7 //  Uzbekistan
#define CTRY_VENEZUELA	58 //  Venezuela
#define CTRY_VIET_NAM	84 //  Viet Nam
#define CTRY_YEMEN	967 //  Yemen
#define CTRY_ZIMBABWE	263 //  Zimbabwe

/* Locale Types */
// To Do

/* Time Flags for GetTimeFormat */
// To Do

/* Date Flags for GetDateFormat */
// To Do

/* Calendar Types */
// To Do

/* Calendar Enumeration Value */
// To Do

/* Calendar ID Values */
// To Do

/* Language Group ID Values */
// To Do

/* Primary language ID Values */
#define LANG_NEUTRAL	0x00
// To Do
#define LANG_ENGLISH	0x09
// To Do

/* Sublanguage ID Values */
#define SUBLANG_NEUTRAL	0x00 //  language neutral
#define SUBLANG_DEFAULT	0x01 //  user default
#define SUBLANG_SYS_DEFAULT	0x02 //  system default
// To Do
#define SUBLANG_ENGLISH_US	0x01 //  English (USA)
// To Do

/* ============================================================================== */
/* Locale specific types */

/* Locale and Language Ids */
typedef uint32_t LCID;
typedef uint16_t LANGID;

/* Language Group ID */
typedef uint32_t LGRPID;
/* Locale type constant */
typedef uint32_t LCTYPE;
/* Calendar type constant */
typedef uint32_t CALTYPE;
/* Calendar ID */
typedef uint32_t CALID;

/* CP Info */
typedef struct _CPINFO CPINFO;
struct _CPINFO
{
	unsigned int maxcharsize; //  max length (in bytes) of a AnsiChar
	uint8_t defaultchar[MAX_DEFAULTCHAR]; //  default character
	uint8_t leadbyte[MAX_LEADBYTES]; //  lead byte ranges
};

typedef CPINFO _cpinfo;

typedef struct _CPINFOEXA CPINFOEXA;
struct _CPINFOEXA
{
	unsigned int maxcharsize; //  max length (in bytes) of a AnsiChar
	uint8_t defaultchar[MAX_DEFAULTCHAR]; //  default character (MB)
	uint8_t leadbyte[MAX_LEADBYTES]; //  lead byte ranges
	WCHAR unicodedefaultchar; //  default character (Unicode)
	unsigned int codepage; //  code page id
	char codepagename[MAX_PATH]; //  code page name (Ansi)
};

typedef CPINFOEXA _cpinfoexA;

typedef struct _CPINFOEXW CPINFOEXW;
struct _CPINFOEXW
{
	unsigned int maxcharsize; //  max length (in bytes) of a AnsiChar
	uint8_t defaultchar[MAX_DEFAULTCHAR]; //  default character (MB)
	uint8_t leadbyte[MAX_LEADBYTES]; //  lead byte ranges
	WCHAR unicodedefaultchar; //  default character (Unicode)
	unsigned int codepage; //  code page id
	WCHAR codepagename[MAX_PATH]; //  code page name (Unicode)
};

typedef CPINFOEXW _cpinfoexW;

typedef CPINFOEXA CPINFOEX;

/* Code Table - The OEM/ANSI to UNICODE Values of a Code Page */
typedef struct _CODE_TABLE CODE_TABLE;
struct _CODE_TABLE
{
	unsigned int maxcharsize; // Max Length (Bytes) of a Char
	uint8_t defaultchar[MAX_DEFAULTCHAR]; // Default Character
	uint8_t leadbyte[MAX_LEADBYTES]; // Lead Byte Ranges
	uint16_t values[0xFF];
};

/* Trans Table - The OEM/ANSI to ANSI/OEM Values of a Code Page */
typedef struct _TRANS_TABLE TRANS_TABLE;
struct _TRANS_TABLE
{
	uint16_t transid; // Translate Code Page
	uint16_t values[0xFF]; // Word to allow for DBCS
};

/* Lower Table - Upper to Lower case values of a Code Page */
typedef struct _LOWER_TABLE LOWER_TABLE;
struct _LOWER_TABLE
{
	uint16_t lowerid; // Lowercase Code Page
	uint16_t values[0xFF]; // Word to allow for DBCS
};

/* Upper Table - Lower to Upper case values of a Code Page */
typedef struct _UPPER_TABLE UPPER_TABLE;
struct _UPPER_TABLE
{
	uint16_t upperid; // Uppercase Code Page
	uint16_t values[0xFF]; // Word to allow for DBCS
};

/* Unicode Table - The UNICODE to OEM/ANSI Values of a Code Page */
typedef struct _UNICODE_TABLE UNICODE_TABLE;
struct _UNICODE_TABLE
{
	uint16_t values[0xFFFF]; // Word to allow for DBCS
};

/* Lead Bytes - The extended Page Tables for DBCS Pages */
typedef struct _LEAD_BYTES LEAD_BYTES;
struct _LEAD_BYTES
{
	CODE_TABLE* tables[0xFF]; //To Do //Test
};

/* Each Code Table provides the OEM to UNICODE Values */
/* To convert back use the main Unicode Table in the Code Page */
/* which was populated when the Code Page was loaded */

/* Code Page - The actual information for an OEM/ANSI Code Page */
typedef struct _CODE_PAGE CODE_PAGE;
struct _CODE_PAGE
{
	uint16_t pageid; // Code Page ID (eg 437 or 1252)
	HANDLE handle; // Handle of Code Page Module
	CODE_TABLE *codetable; // The OEM/ANSI Values
	LEAD_BYTES *leadbytes; // The Lead Byte Tables
	TRANS_TABLE *transtable; // The OEM <-> ANSI Values
	LOWER_TABLE *lowertable; // The Upper to Lower Values
	UPPER_TABLE *uppertable; // The Lower to Upper Values
	UNICODE_TABLE *unicodetable; // The UNICODE Values
	CODE_PAGE *prevpage; // Prev Code Page
	CODE_PAGE *nextpage; // Next Code Page
};

/* ============================================================================== */
/* Locale Functions */
BOOL STDCALL IsValidCodePage(unsigned int codepage);

unsigned int STDCALL GetACP(void);
unsigned int STDCALL GetOEMCP(void);

BOOL STDCALL SetACP(unsigned int codepage);
BOOL STDCALL SetOEMCP(unsigned int codepage);

unsigned int STDCALL GetConsoleCP(void);
BOOL STDCALL SetConsoleCP(unsigned int wcodepageid);

unsigned int STDCALL GetConsoleOutputCP(void);
BOOL STDCALL SetConsoleOutputCP(unsigned int wcodepageid);

BOOL STDCALL GetCPInfo(unsigned int codepage, CPINFO *lpcpinfo);

BOOL STDCALL GetCPInfoEx(unsigned int codepage, uint32_t dwflags, CPINFOEXA *lpcpinfoex);
BOOL STDCALL GetCPInfoExA(unsigned int codepage, uint32_t dwflags, CPINFOEXA *lpcpinfoex);
BOOL STDCALL GetCPInfoExW(unsigned int codepage, uint32_t dwflags, CPINFOEXW *lpcpinfoex);

BOOL STDCALL IsValidLocale(LCID locale, uint32_t dwflags);

LCID STDCALL GetSystemDefaultLCID(void);
LCID STDCALL GetUserDefaultLCID(void);

BOOL STDCALL SetSystemDefaultLCID(LCID locale);

LANGID STDCALL GetSystemDefaultLangID(void);
LANGID STDCALL GetUserDefaultLangID(void);

/* ============================================================================== */
/* Locale Helper Functions */
uint16_t STDCALL map_page(unsigned int codepage);
CODE_PAGE * STDCALL get_page(uint16_t pageid);
BOOL STDCALL check_page(CODE_PAGE *page);

BOOL STDCALL link_page(CODE_PAGE *page);
BOOL STDCALL unlink_page(CODE_PAGE *page);

BOOL STDCALL load_page(uint16_t pageid, CODE_TABLE *table, LOWER_TABLE *lower, UPPER_TABLE *upper);
BOOL STDCALL unload_page(uint16_t pageid, CODE_PAGE *page);

BOOL STDCALL default_trans(uint16_t pageid, uint16_t transid);
BOOL STDCALL install_trans(uint16_t pageid, TRANS_TABLE *table);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_LOCALE_H