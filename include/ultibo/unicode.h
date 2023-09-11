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
#ifndef _ULTIBO_UNICODE_H
#define _ULTIBO_UNICODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/locale.h"

/* ============================================================================== */
/* Unicode Functions */
int STDCALL MultiByteToWideChar(unsigned int codepage, uint32_t dwflags, char *lpmultibytestr, int cbmultibyte, WCHAR *lpwidecharstr, int cchwidechar);
int STDCALL WideCharToMultiByte(unsigned int codepage, uint32_t dwflags, WCHAR *lpwidecharstr, int cchwidechar, char *lpmultibytestr, int cbmultibyte, char *lpdefaultchar, BOOL *lpuseddefaultchar);

int STDCALL CompareString(LCID locale, uint32_t dwcmpflags, char *lpstring1, int cchcount1, char *lpstring2, int cchcount2);
int STDCALL CompareStringA(LCID locale, uint32_t dwcmpflags, char *lpstring1, int cchcount1, char *lpstring2, int cchcount2);
int STDCALL CompareStringW(LCID locale, uint32_t dwcmpflags, WCHAR *lpstring1, int cchcount1, WCHAR *lpstring2, int cchcount2);

char * STDCALL CharUpper(char *lpsz);
char * STDCALL CharUpperA(char *lpsz);
WCHAR * STDCALL CharUpperW(WCHAR *lpsz);

uint32_t STDCALL CharUpperBuff(char *lpsz, uint32_t cchlength);
uint32_t STDCALL CharUpperBuffA(char *lpsz, uint32_t cchlength);
uint32_t STDCALL CharUpperBuffW(WCHAR *lpsz, uint32_t cchlength);

char * STDCALL CharLower(char *lpsz);
char * STDCALL CharLowerA(char *lpsz);
WCHAR * STDCALL CharLowerW(WCHAR *lpsz);

uint32_t STDCALL CharLowerBuff(char *lpsz, uint32_t cchlength);
uint32_t STDCALL CharLowerBuffA(char *lpsz, uint32_t cchlength);
uint32_t STDCALL CharLowerBuffW(WCHAR *lpsz, uint32_t cchlength);

BOOL STDCALL AnsiToOem(char *lpszsrc, char *lpszdst);
BOOL STDCALL AnsiToOemBuff(char *lpszsrc, char *lpszdst, uint32_t cchdstlength);
BOOL STDCALL OemToAnsi(char *lpszsrc, char *lpszdst);
BOOL STDCALL OemToAnsiBuff(char *lpszsrc, char *lpszdst, uint32_t cchdstlength);

BOOL STDCALL CharToOem(char *lpszsrc, char *lpszdst);
BOOL STDCALL CharToOemA(char *lpszsrc, char *lpszdst);
BOOL STDCALL CharToOemW(WCHAR *lpszsrc, char *lpszdst);

BOOL STDCALL OemToChar(char *lpszsrc, char *lpszdst);
BOOL STDCALL OemToCharA(char *lpszsrc, char *lpszdst);
BOOL STDCALL OemToCharW(char *lpszsrc, WCHAR *lpszdst);

BOOL STDCALL CharToOemBuff(char *lpszsrc, char *lpszdst, uint32_t cchdstlength);
BOOL STDCALL CharToOemBuffA(char *lpszsrc, char *lpszdst, uint32_t cchdstlength);
BOOL STDCALL CharToOemBuffW(WCHAR *lpszsrc, char *lpszdst, uint32_t cchdstlength);

BOOL STDCALL OemToCharBuff(char *lpszsrc, char *lpszdst, uint32_t cchdstlength);
BOOL STDCALL OemToCharBuffA(char *lpszsrc, char *lpszdst, uint32_t cchdstlength);
BOOL STDCALL OemToCharBuffW(char *lpszsrc, WCHAR *lpszdst, uint32_t cchdstlength);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_UNICODE_H