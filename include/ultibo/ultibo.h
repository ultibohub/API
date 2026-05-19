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
#ifndef _ULTIBO_ULTIBO_H
#define _ULTIBO_ULTIBO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/timezone.h"
#include "ultibo/locale.h"
#include "ultibo/sysutils.h"

/** Compatibility constants */
/** 64bit Constants */
#define MAXLONGLONG	0x7fffffffffffffff

/** Thread Constants */
#define CREATE_SUSPENDED	0x00000004

/** Message Constants */
#define PM_NOREMOVE	0x0000
#define PM_REMOVE	0x0001
#define PM_NOYIELD	0x0002

/** Timezone Constants */
/** (See timezone.h)   */

/** Shutdown/Restart Constants */
#define EWX_LOGOFF	0x00000000
#define EWX_SHUTDOWN	0x00000001
#define EWX_REBOOT	0x00000002
#define EWX_FORCE	0x00000004
#define EWX_POWEROFF	0x00000008
#define EWX_FORCEIFHUNG	0x00000010

/** Drive Type Constants */
#define DRIVE_UNKNOWN	0
#define DRIVE_NO_ROOT_DIR	1
#define DRIVE_REMOVABLE	2
#define DRIVE_FIXED	3
#define DRIVE_REMOTE	4
#define DRIVE_CDROM	5
#define DRIVE_RAMDISK	6

/** Symbolic Link Constants */
#define SYMBOLIC_LINK_FLAG_FILE	0x00000000 ///< The link target is a file
#define SYMBOLIC_LINK_FLAG_DIRECTORY	0x00000001 ///< The link target is a directory

/** Local Memory Constants */
#define LMEM_FIXED	0x0000
#define LMEM_MOVEABLE	0x0002
#define LMEM_NOCOMPACT	0x0010
#define LMEM_NODISCARD	0x0020
#define LMEM_ZEROINIT	0x0040
#define LMEM_MODIFY	0x0080
#define LMEM_DISCARDABLE	0x0F00
#define LMEM_VALID_FLAGS	0x0F72
#define LMEM_INVALID_HANDLE	0x8000

#define LHND	(LMEM_MOVEABLE | LMEM_ZEROINIT)
#define LPTR	(LMEM_FIXED | LMEM_ZEROINIT)

#define NONZEROLHND	(LMEM_MOVEABLE)
#define NONZEROLPTR	(LMEM_FIXED)

/** Global Memory Constants */
#define GMEM_FIXED	0x0000
#define GMEM_MOVEABLE	0x0002
#define GMEM_NOCOMPACT	0x0010
#define GMEM_NODISCARD	0x0020
#define GMEM_ZEROINIT	0x0040
#define GMEM_MODIFY	0x0080
#define GMEM_DISCARDABLE	0x0100
#define GMEM_NOT_BANKED	0x1000
#define GMEM_SHARE	0x2000
#define GMEM_DDESHARE	0x2000
#define GMEM_NOTIFY	0x4000
#define GMEM_LOWER	GMEM_NOT_BANKED
#define GMEM_VALID_FLAGS	0x7F72
#define GMEM_INVALID_HANDLE	0x8000

#define GHND	(GMEM_MOVEABLE | GMEM_ZEROINIT)
#define GPTR	(GMEM_FIXED | GMEM_ZEROINIT)

/** Virtual Page Constants */
#define PAGE_NOACCESS	0x01
#define PAGE_READONLY	0x02
#define PAGE_READWRITE	0x04
#define PAGE_WRITECOPY	0x08
#define PAGE_EXECUTE	0x10
#define PAGE_EXECUTE_READ	0x20
#define PAGE_EXECUTE_READWRITE	0x40
#define PAGE_EXECUTE_WRITECOPY	0x80
#define PAGE_GUARD	0x100
#define PAGE_NOCACHE	0x200
#define PAGE_WRITECOMBINE	0x400

/** Virtual Memory Constants */
#define MEM_COMMIT	0x1000
#define MEM_RESERVE	0x2000
#define MEM_DECOMMIT	0x4000
#define MEM_RELEASE	0x8000
#define MEM_FREE	0x10000
#define MEM_PRIVATE	0x20000
#define MEM_MAPPED	0x40000
#define MEM_RESET	0x80000
#define MEM_TOP_DOWN	0x100000
#define MEM_WRITE_WATCH	0x200000
#define MEM_PHYSICAL	0x400000
#define MEM_4MB_PAGES	(DWORD)0x80000000
#define SEC_FILE	0x800000
#define SEC_IMAGE	0x1000000
#define SEC_RESERVE	0x4000000
#define SEC_COMMIT	(DWORD)0x8000000
#define SEC_NOCACHE	0x10000000
#define MEM_IMAGE	SEC_IMAGE
#define WRITE_WATCH_FLAG_RESET	0x01
#define MEM_LARGE_PAGES	0x20000000

/** Processor Architechture Constants */
#define PROCESSOR_ARCHITECTURE_INTEL	0
#define PROCESSOR_ARCHITECTURE_MIPS	1
#define PROCESSOR_ARCHITECTURE_ALPHA	2
#define PROCESSOR_ARCHITECTURE_PPC	3
#define PROCESSOR_ARCHITECTURE_SHX	4
#define PROCESSOR_ARCHITECTURE_ARM	5
#define PROCESSOR_ARCHITECTURE_IA64	6
#define PROCESSOR_ARCHITECTURE_ALPHA64	7
#define PROCESSOR_ARCHITECTURE_MSIL	8
#define PROCESSOR_ARCHITECTURE_AMD64	9

#define PROCESSOR_ARCHITECTURE_UNKNOWN	0xFFFF

/** Processor Type Constants */
#define PROCESSOR_INTEL_386	386
#define PROCESSOR_INTEL_486	486
#define PROCESSOR_INTEL_PENTIUM	586
#define PROCESSOR_INTEL_IA64	2200
#define PROCESSOR_ARM_6	60999
#define PROCESSOR_ARM_7	70999
#define PROCESSOR_ARM_8	80999

/** Version Info Constants */
#define VER_PLATFORM_ULTIBO	10011

/** Dos Device Constants */
#define DDD_RAW_TARGET_PATH	0x00000001
#define DDD_REMOVE_DEFINITION	0x00000002
#define DDD_EXACT_MATCH_ON_REMOVE	0x00000004
#define DDD_NO_BROADCAST_SYSTEM	0x00000008
#define DDD_LUID_BROADCAST_DRIVE	0x00000010

/** Compatibility types */
/** Signed types */
typedef int INT;
typedef int32_t LONG; ///< long // In Windows LONG remains as 4 bytes (32-bit) regardless of 32-bit or 64-bit compiler

/** Unsigned types */
typedef unsigned char BYTE;
typedef unsigned short WORD;

typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef uint32_t ULONG; ///< unsigned long // In Windows ULONG remains as 4 bytes (32-bit) regardless of 32-bit or 64-bit compiler

/** Pointer types */
typedef ssize_t INT_PTR;
typedef size_t UINT_PTR;
typedef ssize_t LONG_PTR;
typedef size_t ULONG_PTR;
typedef ULONG_PTR DWORD_PTR;

/** 64bit types */
typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;
typedef ULONGLONG DWORDLONG;

/** Size types */
typedef size_t SIZE_T;
typedef ssize_t SSIZE_T;

/** Handle types */
typedef HANDLE HLOCAL;
typedef HANDLE HGLOBAL;
typedef HANDLE HWND;

/** Parameter types */
typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;

typedef struct _QUAD
{								// QUAD is for those times we want
	double_t donotusethisfield;	// an 8 byte aligned 8 byte long structure
								// which is NOT really a floating point
} QUAD;							// number.  Use DOUBLE if you want an FP number.

typedef QUAD UQUAD;

typedef struct _GUID
{
  DWORD Data1;
  WORD  Data2;
  WORD  Data3;
  BYTE  Data4[8];
} GUID;

/** Locale and Language Ids */
/** (See locale.h)   */

/** Large Integer types */
typedef union _LARGE_INTEGER
{
  struct {
    DWORD LowPart;
    LONG  HighPart;
  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER;

typedef union _ULARGE_INTEGER
{
  struct {
    DWORD LowPart;
    DWORD HighPart;
  };
  struct {
    DWORD LowPart;
    DWORD HighPart;
  } u;
  ULONGLONG QuadPart;
} ULARGE_INTEGER;

/** Version Info types */
typedef struct _OSVERSIONINFOA
{
  DWORD dwOSVersionInfoSize;
  DWORD dwMajorVersion;
  DWORD dwMinorVersion;
  DWORD dwBuildNumber;
  DWORD dwPlatformId;
  char szCSDVersion[128];
} OSVERSIONINFOA;

typedef struct _OSVERSIONINFOW
{
  DWORD dwOSVersionInfoSize;
  DWORD dwMajorVersion;
  DWORD dwMinorVersion;
  DWORD dwBuildNumber;
  DWORD dwPlatformId;
  WCHAR szCSDVersion[128];
} OSVERSIONINFOW;

typedef OSVERSIONINFOA OSVERSIONINFO;

typedef struct _SYSTEM_INFO
{
  WORD      wProcessorArchitecture;
  WORD      wReserved;
  DWORD     dwPageSize;
  void     *lpMinimumApplicationAddress;
  void     *lpMaximumApplicationAddress;
  DWORD_PTR dwActiveProcessorMask;
  DWORD     dwNumberOfProcessors;
  DWORD     dwProcessorType;
  DWORD     dwAllocationGranularity;
  WORD      wProcessorLevel;
  WORD      wProcessorRevision;
} SYSTEM_INFO;

/** Computer Name types */
typedef enum _COMPUTER_NAME_FORMAT
{
   ComputerNameNetBIOS,
   ComputerNameDnsHostname,
   ComputerNameDnsDomain,
   ComputerNameDnsFullyQualified,
   ComputerNamePhysicalNetBIOS,
   ComputerNamePhysicalDnsHostname,
   ComputerNamePhysicalDnsDomain,
   ComputerNamePhysicalDnsFullyQualified,
   ComputerNameMax
} COMPUTER_NAME_FORMAT;

/** System Time types */
/** (See sysutils.h)   */

/** File Time types */
/** (See sysutils.h)   */

/** File Search types */
/** (See also sysutils.h)   */

typedef struct _WIN32_FIND_DATAW
{
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  WCHAR    cFileName[MAX_PATH];
  WCHAR    cAlternateFileName[14];
} WIN32_FIND_DATAW;

typedef WIN32_FIND_DATAA WIN32_FIND_DATA;

/** Stream Search types */
typedef enum _STREAM_INFO_LEVELS
{
 FindStreamInfoStandard,
 FindStreamInfoMaxInfoLevel
} STREAM_INFO_LEVELS;

typedef struct _WIN32_FIND_STREAM_DATA
{
  LARGE_INTEGER StreamSize;
  WCHAR         cStreamName[MAX_PATH + 36];
} WIN32_FIND_STREAM_DATA;

/** Timezone types */
/** (See timezone.h)   */

/** Memory Status types */
typedef struct _MEMORYSTATUS
{
  DWORD  dwLength;
  DWORD  dwMemoryLoad;
  SIZE_T dwTotalPhys;
  SIZE_T dwAvailPhys;
  SIZE_T dwTotalPageFile;
  SIZE_T dwAvailPageFile;
  SIZE_T dwTotalVirtual;
  SIZE_T dwAvailVirtual;
} MEMORYSTATUS;

typedef struct _MEMORYSTATUSEX
{
  DWORD     dwLength;
  DWORD     dwMemoryLoad;
  DWORDLONG ullTotalPhys;
  DWORDLONG ullAvailPhys;
  DWORDLONG ullTotalPageFile;
  DWORDLONG ullAvailPageFile;
  DWORDLONG ullTotalVirtual;
  DWORDLONG ullAvailVirtual;
  DWORDLONG ullAvailExtendedVirtual;
} MEMORYSTATUSEX;

/** Security Attributes types */
typedef struct _SECURITY_ATTRIBUTES
{
  DWORD  nLength;
  void  *lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES;

/** Thread Start types */
typedef uint32_t STDCALL (*THREAD_START_ROUTINE)(void *lpthreadparameter);

/** Point and Rect types */
typedef struct _RECT
{
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
} RECT;

typedef struct _POINT
{
  LONG x;
  LONG y;
} POINT;

/** Message types */
typedef struct _MSG
{
  HANDLE hThread;
  UINT   message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD  time;
  POINT  pt;
} MSG;

/** List types */
typedef struct _LOCKS_LIST_ENTRY
{
  struct _LOCKS_LIST_ENTRY  *Flink;
  struct _LOCKS_LIST_ENTRY  *Blink;
} LOCKS_LIST_ENTRY;

/** Critical Section types */
typedef struct _RTL_CRITICAL_SECTION RTL_CRITICAL_SECTION;

typedef struct _RTL_CRITICAL_SECTION_DEBUG
{
  WORD Type;
  WORD CreatorBackTraceIndex;
  RTL_CRITICAL_SECTION *CriticalSection;
  LOCKS_LIST_ENTRY ProcessLocksList;
  DWORD EntryCount;
  DWORD ContentionCount;
  DWORD Spare[2];
} RTL_CRITICAL_SECTION_DEBUG;

struct _RTL_CRITICAL_SECTION
{
  RTL_CRITICAL_SECTION_DEBUG *DebugInfo;

  //   The following three fields control entering and exiting the critical
  //   section for the resource

  long LockCount;
  long RecursionCount;
  HANDLE OwningThread; ///<  from the thread's ClientId->UniqueThread
  HANDLE LockSemaphore;
  ULONG_PTR SpinCount; ///<  force size on 64-bit systems when packed
};

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;

/** Condition Variable types */
typedef struct _RTL_CONDITION_VARIABLE
{
  void *ptr;
} RTL_CONDITION_VARIABLE;

typedef RTL_CONDITION_VARIABLE CONDITION_VARIABLE;

/** Counter types */
typedef struct _IO_COUNTERS
{
  ULONGLONG ReadOperationCount;
  ULONGLONG WriteOperationCount;
  ULONGLONG OtherOperationCount;
  ULONGLONG ReadTransferCount;
  ULONGLONG WriteTransferCount;
  ULONGLONG OtherTransferCount;
} IO_COUNTERS;

/** Code Page types */
/** (See locale.h)   */

/** Memory Information Types */
typedef struct _MEMORY_BASIC_INFORMATION
{
  void  *BaseAddress;
  void  *AllocationBase;
  DWORD  AllocationProtect;
  SIZE_T RegionSize;
  DWORD  State;
  DWORD  Protect;
  DWORD  Type;
} MEMORY_BASIC_INFORMATION;

/** RGB Color Types */
typedef int32_t FXPT16DOT16;
typedef int32_t FXPT2DOT30;


typedef struct _CIEXYZ
{
  FXPT2DOT30 ciexyzX;
  FXPT2DOT30 ciexyzY;
  FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct _CIEXYZTRIPLE
 {
  CIEXYZ ciexyzRed;
  CIEXYZ ciexyzGreen;
  CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;

/** Bitmap Types */
typedef struct _BITMAP
{
  LONG   bmType;
  LONG   bmWidth;
  LONG   bmHeight;
  LONG   bmWidthBytes;
  WORD   bmPlanes;
  WORD   bmBitsPixel;
  void  *bmBits;
} BITMAP;

typedef struct _RGBTRIPLE
{
  BYTE rgbtBlue;
  BYTE rgbtGreen;
  BYTE rgbtRed;
} RGBTRIPLE;

typedef struct _RGBQUAD
{
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;

/** Bitmap Header Types */
typedef struct _BITMAPCOREHEADER
{
  DWORD bcSize;
  WORD  bcWidth;
  WORD  bcHeight;
  WORD  bcPlanes;
  WORD  bcBitCount;
} BITMAPCOREHEADER;

typedef struct _BITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct
{
  DWORD        bV4Size;
  LONG         bV4Width;
  LONG         bV4Height;
  WORD         bV4Planes;
  WORD         bV4BitCount;
  DWORD        bV4V4Compression;
  DWORD        bV4SizeImage;
  LONG         bV4XPelsPerMeter;
  LONG         bV4YPelsPerMeter;
  DWORD        bV4ClrUsed;
  DWORD        bV4ClrImportant;
  DWORD        bV4RedMask;
  DWORD        bV4GreenMask;
  DWORD        bV4BlueMask;
  DWORD        bV4AlphaMask;
  DWORD        bV4CSType;
  CIEXYZTRIPLE bV4Endpoints;
  DWORD        bV4GammaRed;
  DWORD        bV4GammaGreen;
  DWORD        bV4GammaBlue;
} BITMAPV4HEADER;

typedef struct
{
  DWORD        bV5Size;
  LONG         bV5Width;
  LONG         bV5Height;
  WORD         bV5Planes;
  WORD         bV5BitCount;
  DWORD        bV5Compression;
  DWORD        bV5SizeImage;
  LONG         bV5XPelsPerMeter;
  LONG         bV5YPelsPerMeter;
  DWORD        bV5ClrUsed;
  DWORD        bV5ClrImportant;
  DWORD        bV5RedMask;
  DWORD        bV5GreenMask;
  DWORD        bV5BlueMask;
  DWORD        bV5AlphaMask;
  DWORD        bV5CSType;
  CIEXYZTRIPLE bV5Endpoints;
  DWORD        bV5GammaRed;
  DWORD        bV5GammaGreen;
  DWORD        bV5GammaBlue;
  DWORD        bV5Intent;
  DWORD        bV5ProfileData;
  DWORD        bV5ProfileSize;
  DWORD        bV5Reserved;
} BITMAPV5HEADER;

/** Bitmap Info Types */
typedef struct _BITMAPINFO
{
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD          bmiColors[1];
} BITMAPINFO;

typedef struct _BITMAPCOREINFO
{
  BITMAPCOREHEADER bmciHeader;
  RGBTRIPLE        bmciColors[1];
} BITMAPCOREINFO;

typedef struct _BITMAPFILEHEADER
{
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER;

/** File Information Types */
typedef struct _BY_HANDLE_FILE_INFORMATION
{
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    dwVolumeSerialNumber;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    nNumberOfLinks;
  DWORD    nFileIndexHigh;
  DWORD    nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION;

/** Compatibility variables */
static const CONDITION_VARIABLE CONDITION_VARIABLE_INIT = {NULL};

/** Ultibo constants */
static const FILETIME TIME_NULL_TIME = {0x00000000, 0x00000000};

/** Drive constants */
#define DEFAULT_DRIVE	0 ///< 0 is Current Drive
#define INVALID_DRIVE	0 ///< Where Current is not appropriate
#define MIN_DRIVE	1 ///< 1 = A:, 2 = B:, 3 = C:, 26 = Z: etc
#define MAX_DRIVE	26
#define NON_DRIVE	27 ///< 27 for Non Drive (UNC) Path

#define DRIVE_A	1
#define DRIVE_B	2
#define DRIVE_C	3

/** Path and File constants */
#define MAX_FAT_PATH	64
#define MAX_FAT_FILE	12
#define MAX_VFAT_PATH	260
#define MAX_VFAT_FILE	255

#define FAT_PATH_CHAR	"\\" ///< Path separator
#define FAT_NAME_CHAR	":" ///< Stream separator
#define FAT_FILE_CHAR	"." ///< Extension separator
#define FAT_DRIVE_CHAR	":" ///< Drive separator

#define UNIX_PATH_CHAR	"/" ///< Path separator
#define UNIX_NAME_CHAR	":" ///< Stream separator
#define UNIX_FILE_CHAR	"." ///< Extension separator

/** Wildcard Filename Chars */
#define MACRO_FILENAME_CHAR	"%"
#define WILDCARD_FILENAME_CHAR "*"

/** Ultibo types */
typedef enum _DRIVE_TYPE
{
 dtUNKNOWN,
 dtINVALID,
 dtFIXED,
 dtFLOPPY,
 dtREMOVABLE,
 dtNETWORK,
 dtSUBSTITUTED,
 dtRAMDRIVE,
 dtCDROM
} DRIVE_TYPE;

typedef enum _FILE_SYS_TYPE
{
 fsUNKNOWN,
 fsINVALID,
 fsFAT12,
 fsFAT16,
 fsFAT32,
 fsEXFAT,
 fsHPFS,
 fsNTFS,
 fsNTFS5,
 fsNTFS51,
 fsCDFS,
 fsUDF,
 fsEXT2,
 fsEXT3,
 fsEXT4
} FILE_SYS_TYPE;

/** Drive types */
typedef struct _DRIVE_DATA
{
	uint8_t drive;
	DRIVE_TYPE drivetype;
	FILE_SYS_TYPE filesystype;
	int maxfile;
	int maxpath;
	uint32_t attributes;
	char systemname[33]; //NOT null terminated, index 0 is the length
	char volumename[33]; //NOT null terminated, index 0 is the length
	uint32_t volumeserial;
} DRIVE_DATA;

/** General Functions (Compatibility) */
uint32_t STDCALL GetVersion(void);

BOOL STDCALL GetVersionEx(OSVERSIONINFOA *lpversioninformation);
BOOL STDCALL GetVersionExA(OSVERSIONINFOA *lpversioninformation);
BOOL STDCALL GetVersionExW(OSVERSIONINFOW *lpversioninformation);

void STDCALL GetSystemInfo(SYSTEM_INFO *lpsysteminfo);
void STDCALL GetNativeSystemInfo(SYSTEM_INFO *lpsysteminfo);
SIZE_T STDCALL GetLargePageMinimum(void);

BOOL STDCALL GetComputerName(char *lpbuffer, uint32_t *nsize);
BOOL STDCALL GetComputerNameA(char *lpbuffer, uint32_t *nsize);
BOOL STDCALL GetComputerNameW(WCHAR *lpbuffer, uint32_t *nsize);

BOOL STDCALL SetComputerName(const char *lpcomputername);
BOOL STDCALL SetComputerNameA(const char *lpcomputername);
BOOL STDCALL SetComputerNameW(const WCHAR *lpcomputername);

BOOL STDCALL GetComputerNameEx(COMPUTER_NAME_FORMAT nametype, char *lpbuffer, uint32_t *nsize);
BOOL STDCALL GetComputerNameExA(COMPUTER_NAME_FORMAT nametype, char *lpbuffer, uint32_t *nsize);
BOOL STDCALL GetComputerNameExW(COMPUTER_NAME_FORMAT nametype, WCHAR *lpbuffer, uint32_t *nsize);

BOOL STDCALL SetComputerNameEx(COMPUTER_NAME_FORMAT nametype, const char *lpbuffer);
BOOL STDCALL SetComputerNameExA(COMPUTER_NAME_FORMAT nametype, const char *lpbuffer);
BOOL STDCALL SetComputerNameExW(COMPUTER_NAME_FORMAT nametype, const WCHAR *lpbuffer);

BOOL STDCALL ExitUltibo(uint32_t dwreserved, UINT ureserved);
BOOL STDCALL ExitUltiboEx(UINT uflags, uint32_t dwreserved);

/** General Functions (Ultibo) */

/**
 * @param Delay Milliseconds to delay before restart
 */
BOOL STDCALL RestartComputer(uint32_t delay);

/**
 * @param Delay Milliseconds to delay before shutdown
 */
BOOL STDCALL ShutdownComputer(uint32_t delay);

/**
 * @brief Get the current system up time as a FileTime value
 */
FILETIME STDCALL Uptime(void);

/** Time Functions (Compatibility) */
uint32_t STDCALL GetTickCount(void);
ULONGLONG STDCALL GetTickCount64(void);

/**
 * @brief Get the current system time in UTC
 */
void STDCALL GetSystemTime(SYSTEMTIME *lpsystemtime);

/**
 * @brief Get the current system time in UTC as a FileTime value
 */
void STDCALL GetSystemTimeAsFileTime(FILETIME *lpsystemtimeasfiletime);

/**
 * @brief Set the current system time in UTC
 */
BOOL STDCALL SetSystemTime(SYSTEMTIME *lpsystemtime);

/**
 * @brief Get the current local time
 */
void STDCALL GetLocalTime(SYSTEMTIME *lpsystemtime);

/**
 * @brief Set the current local time
 */
BOOL STDCALL SetLocalTime(SYSTEMTIME *lpsystemtime);

BOOL STDCALL SystemTimeToTzSpecificLocalTime(TIME_ZONE_INFORMATION *lptimezoneinformation, SYSTEMTIME *lpuniversaltime, SYSTEMTIME *lplocaltime);
BOOL STDCALL TzSpecificLocalTimeToSystemTime(TIME_ZONE_INFORMATION *lptimezoneinformation, SYSTEMTIME *lplocaltime, SYSTEMTIME *lpuniversaltime);

uint32_t STDCALL GetTimeZoneInformation(TIME_ZONE_INFORMATION *lptimezoneinformation);
BOOL STDCALL SetTimeZoneInformation(TIME_ZONE_INFORMATION *lptimezoneinformation);

/**
 * @brief Convert a SystemTime value to a FileTime value
 * @note lpSystemTime is assumed to be UTC / lpFileTime is returned as UTC
 */
BOOL STDCALL SystemTimeToFileTime(SYSTEMTIME *lpsystemtime, FILETIME *lpfiletime);

/**
 * @brief Convert a FileTime value to a SystemTime value
 * @note lpFileTime is assumed to be UTC / lpSystemTime is returned as UTC
 * @note If lpFileTime is less than 30 December 1899 then SystemTime will be zero
 */
BOOL STDCALL FileTimeToSystemTime(FILETIME *lpfiletime, SYSTEMTIME *lpsystemtime);

/**
 * @brief Convert a FileTime in UTC to a FileTime in Local time
 * @note TIMEZONE_TIME_OFFSET is the number of minutes offset from UTC
 */
BOOL STDCALL FileTimeToLocalFileTime(FILETIME *lpfiletime, FILETIME *lplocalfiletime);

/**
 * @brief Convert a FileTime in Local time to a FileTime in UTC
 * @note TIMEZONE_TIME_OFFSET is the number of minutes offset from UTC
 */
BOOL STDCALL LocalFileTimeToFileTime(FILETIME *lplocalfiletime, FILETIME *lpfiletime);

long STDCALL CompareFileTime(FILETIME *lpfiletime1, FILETIME *lpfiletime2);

/**
 * @brief Convert a FileTime value to a DOS date and time value
 * @note FileTime is assumed to be Local / DOS date and time is returned as Local
 * @note If FileTime is less than 1 January 1980 then DOS date and time will be 1 January 1980
 */
BOOL STDCALL FileTimeToDosDateTime(FILETIME *lpfiletime, uint16_t *lpfatdate, uint16_t *lpfattime);

/**
 * @brief Convert a DOS date and time value to a FileTime value
 * @note DOS date and time is assumed to be Local / FileTime is returned as Local
 * @note If DOS date and time is less than 1 January 1980 then FileTime will be 1 January 1980
 */
BOOL STDCALL DosDateTimeToFileTime(uint16_t wfatdate, uint16_t wfattime, FILETIME *lpfiletime);

/**
 * @brief Retrieves the current value of the performance counter, which is a high
 *  resolution (<1us) time stamp that can be used for time-interval measurements
 */
BOOL STDCALL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);

/**
 * @brief Retrieves the frequency of the performance counter.
 *  The frequency of the performance counter is fixed at system boot and is
 *  consistent across all processors. Therefore, the frequency need only be
 *  queried upon application initialization, and the result can be cached
 */
BOOL STDCALL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);

/** Time Functions (Ultibo) */

/**
 * @brief Get the current system time in UTC as a FileTime value
 */
FILETIME STDCALL GetCurrentTime(void);

/**
 * @brief Set the current system time in UTC from a FileTime value
 */
void STDCALL SetCurrentTime(FILETIME *time);

/**
 * @brief Gets the time adjustment used internally
 */
int32_t STDCALL GetTimeAdjust(void);

/**
 * @brief Sets the time adjustment used internally
 */
void STDCALL SetTimeAdjust(int32_t adjust);

/**
 * @brief Get the name of the current Timezone
 */
uint32_t STDCALL GetCurrentTimezone(char *name, uint32_t len);

/**
 * @brief Set the current Timezone by name
 */
BOOL STDCALL SetCurrentTimezone(const char *name);

/**
 * @brief Gets the Active Offset from the current Timezone
 */
int32_t STDCALL GetTimezoneActiveOffset(void);

/**
 * @brief Gets the Standard Offset from the current Timezone
 */
int32_t STDCALL GetTimezoneStandardOffset(void);

/**
 * @brief Sets the Standard Offset for the current Timezone
 */
void STDCALL SetTimezoneStandardOffset(int32_t offset);

/**
 * @brief Gets the Daylight Offset from the current Timezone
 */
int32_t STDCALL GetTimezoneDaylightOffset(void);

/**
 * @brief Sets the Daylight Offset for the current Timezone
 */
void STDCALL SetTimezoneDaylightOffset(int32_t offset);

/**
 * @brief Get the description of the standard time start for the current Timezone
 */
uint32_t STDCALL GetTimezoneStandardStart(char *description, uint32_t len);

/**
 * @brief Get the description of the daylight time start for the current Timezone
 */
uint32_t STDCALL GetTimezoneDaylightStart(char *description, uint32_t len);

/**
 * @brief Get the next date of the standard time start for the current Timezone
 */
double_t STDCALL GetTimezoneStandardDate(void);

/**
 * @brief Get the next date of the daylight time start for the current Timezone
 */
double_t STDCALL GetTimezoneDaylightDate(void);

/**
 * @brief Convert a FileTime value to a DateTime value
 * @note FileTime is assumed to be UTC / DateTime is returned as Local
 * @note If FileTime is less than 30 December 1899 then Result will be zero
 */
double_t STDCALL FileTimeToDateTime(FILETIME *filetime);

/**
 * @brief Convert a DateTime value to a FileTime value
 * @note DateTime is assumed to be Local / FileTime is returned as UTC
 */
FILETIME STDCALL DateTimeToFileTime(double_t datetime);

/**
 * @brief Convert a FileTime value to a DateTime value
 * @note FileTime is assumed to be Local / DateTime is returned as Local
 * @note If FileTime is less than 30 December 1899 then Result will be zero
 */
double_t STDCALL LocalFileTimeToDateTime(FILETIME *filetime);

/**
 * @brief Convert a DateTime value to a FileTime value
 * @note DateTime is assumed to be Local / FileTime is returned as Local
 */
FILETIME STDCALL DateTimeToLocalFileTime(double_t datetime);

/**
 * @brief Convert a FileTime value to a DateTime value
 * @note FileTime is assumed to be UTC / DateTime is returned as UTC
 * @note If FileTime is less than 30 December 1899 then Result will be zero
 * @note Same as LocalFileTimeToDateTime but renamed for clarity
 */
double_t STDCALL SystemFileTimeToDateTime(FILETIME *filetime);

/**
 * @brief Convert a DateTime value to a FileTime value
 * @note DateTime is assumed to be UTC / FileTime is returned as UTC
 * @note Same as DateTimeToLocalFileTime but renamed for clarity
 */
FILETIME STDCALL DateTimeToSystemFileTime(double_t datetime);

/**
 * @brief Convert a FileTime value to a Unix/Linux time value
 * @note FileTime is assumed to be Local / UnixTime is returned as Local
 * @note If FileTime is less than 1 January 1970 then Result will be zero
 */
time_t STDCALL FileTimeToUnixTime(FILETIME *filetime);

/**
 * @brief Convert a Unix/Linux time value to a FileTime value
 * @note UnixTime is assumed to be Local / FileTime is returned as Local
 */
FILETIME STDCALL UnixTimeToFileTime(time_t unixtime);

/**
 * @brief Convert a Unix/Linux time value to a DateTime value
 * @note UnixTime is assumed to be Local / DateTime is returned as Local
 */
double_t STDCALL UnixTimeToDateTime(time_t unixtime);

/**
 * @brief Convert a DateTime value to a Unix/Linux time value
 * @note DateTime is assumed to be Local / UnixTime is returned as Local
 * @note If DateTime is less than 1 January 1970 then Result will be zero
 */
time_t STDCALL DateTimeToUnixTime(double_t datetime);

/**
 * @brief Convert a FileTime value to a DOS date value
 * @note FileTime is assumed to be UTC / FileDate is returned as Local
 * @note If FileTime is less than 1 January 1980 then Result will be zero
 */
int STDCALL FileTimeToFileDate(FILETIME *filetime);

/**
 * @brief Convert a DOS date value to a FileTime value
 * @note FileDate is assumed to be Local / FileTime is returned as UTC
 * @note If FileDate is less than 1 January 1980 then Result will be zero
 */
FILETIME STDCALL FileDateToFileTime(int filedate);

/**
 * @brief Convert a local FileTime value to a DST adjusted FileTime value
 * @note TIMEZONE_TIME_ADJUST is the number of minutes difference from TIMEZONE_TIME_OFFSET
 */
FILETIME STDCALL FileTimeToAdjustedTime(FILETIME *filetime);

/**
 * @brief Convert a DST adjusted FileTime value to a local FileTime value
 * @note TIMEZONE_TIME_ADJUST is the number of minutes difference from TIMEZONE_TIME_OFFSET
 */
FILETIME STDCALL AdjustedTimeToFileTime(FILETIME *filetime);

/**
 * @brief Round FileTime to nearest 2 seconds for compatibility with FileDate
 */
FILETIME STDCALL RoundFileTime(FILETIME *filetime);

/**
 * @brief Convert a FileTime value to a specified offset (Local or UTC)
 * @note Offset is the number of minutes to adjust in conversion
 *       Local indicates whether the source time is Local or UTC
 */
FILETIME STDCALL ConvertFileTime(FILETIME *filetime, int offset, BOOL local);

/**
 * @brief Convert a DateTime value to a specified offset (Local or UTC)
 * @note Offset is the number of minutes to adjust in conversion
 *       Local indicates whether the source time is Local or UTC
 */
double_t STDCALL ConvertDateTime(double_t datetime, int offset, BOOL local);

/** Drive Functions (Compatibility) */
UINT STDCALL GetDiskType(const char *lprootpathname); ///< GetDriveType - Already defined below
UINT STDCALL GetDriveTypeA(const char *lprootpathname);
UINT STDCALL GetDriveTypeW(const WCHAR *lprootpathname);

uint32_t STDCALL GetLogicalDrives(void);

uint32_t STDCALL GetLogicalDriveStrings(uint32_t nbufferlength, char *lpbuffer);
uint32_t STDCALL GetLogicalDriveStringsA(uint32_t nbufferlength, char *lpbuffer);
uint32_t STDCALL GetLogicalDriveStringsW(uint32_t nbufferlength, WCHAR *lpbuffer);

BOOL STDCALL DefineDosDevice(uint32_t dwflags, const char *lpdevicename, const char *lptargetpath);
BOOL STDCALL DefineDosDeviceA(uint32_t dwflags, const char *lpdevicename, const char *lptargetpath);
BOOL STDCALL DefineDosDeviceW(uint32_t dwflags, const WCHAR *lpdevicename, const WCHAR *lptargetpath);

uint32_t STDCALL QueryDosDevice(const char *lpdevicename, char *lptargetpath, uint32_t ucchmax);
uint32_t STDCALL QueryDosDeviceA(const char *lpdevicename, char *lptargetpath, uint32_t ucchmax);
uint32_t STDCALL QueryDosDeviceW(const WCHAR *lpdevicename, WCHAR *lptargetpath, uint32_t ucchmax);

BOOL STDCALL SetVolumeLabel(const char *lprootpathname, const char *lpvolumename);
BOOL STDCALL SetVolumeLabelA(const char *lprootpathname, const char *lpvolumename);
BOOL STDCALL SetVolumeLabelW(const WCHAR *lprootpathname, const WCHAR *lpvolumename);

BOOL STDCALL GetVolumeInformation(const char *lprootpathname, char *lpvolumenamebuffer, uint32_t nvolumenamesize, DWORD *lpvolumeserialnumber, uint32_t *lpmaximumcomponentlength, uint32_t *lpfilesystemflags, char *lpfilesystemnamebuffer, uint32_t nfilesystemnamesize);
BOOL STDCALL GetVolumeInformationA(const char *lprootpathname, char *lpvolumenamebuffer, uint32_t nvolumenamesize, DWORD *lpvolumeserialnumber, uint32_t *lpmaximumcomponentlength, uint32_t *lpfilesystemflags, char *lpfilesystemnamebuffer, uint32_t nfilesystemnamesize);
BOOL STDCALL GetVolumeInformationW(const WCHAR *lprootpathname, WCHAR *lpvolumenamebuffer, uint32_t nvolumenamesize, DWORD *lpvolumeserialnumber, uint32_t *lpmaximumcomponentlength, uint32_t *lpfilesystemflags, WCHAR *lpfilesystemnamebuffer, uint32_t nfilesystemnamesize);

BOOL STDCALL GetDiskFreeSpace(const char *lprootpathname, uint32_t *lpsectorspercluster, uint32_t *lpbytespersector, uint32_t *lpnumberoffreeclusters, uint32_t *lptotalnumberofclusters);
BOOL STDCALL GetDiskFreeSpaceA(const char *lprootpathname, uint32_t *lpsectorspercluster, uint32_t *lpbytespersector, uint32_t *lpnumberoffreeclusters, uint32_t *lptotalnumberofclusters);
BOOL STDCALL GetDiskFreeSpaceW(const WCHAR *lprootpathname, uint32_t *lpsectorspercluster, uint32_t *lpbytespersector, uint32_t *lpnumberoffreeclusters, uint32_t *lptotalnumberofclusters);

BOOL STDCALL GetDiskFreeSpaceEx(const char *lpdirectoryname, ULARGE_INTEGER *lpfreebytesavailabletocaller, ULARGE_INTEGER *lptotalnumberofbytes, ULARGE_INTEGER *lptotalnumberoffreebytes);
BOOL STDCALL GetDiskFreeSpaceExA(const char *lpdirectoryname, ULARGE_INTEGER *lpfreebytesavailabletocaller, ULARGE_INTEGER *lptotalnumberofbytes, ULARGE_INTEGER *lptotalnumberoffreebytes);
BOOL STDCALL GetDiskFreeSpaceExW(const WCHAR *lpdirectoryname, ULARGE_INTEGER *lpfreebytesavailabletocaller, ULARGE_INTEGER *lptotalnumberofbytes, ULARGE_INTEGER *lptotalnumberoffreebytes);

/** Drive Functions (Ultibo) */
uint8_t STDCALL GetPathDrive(const char *path);
DRIVE_TYPE STDCALL GetDriveType(uint8_t drive);
void STDCALL GetDriveData(uint8_t drive, DRIVE_DATA *data);
uint32_t STDCALL GetDriveAttr(uint8_t drive);
uint32_t STDCALL GetDriveLabel(uint8_t drive, char *label, uint32_t len);
BOOL STDCALL SetDriveLabel(uint8_t drive, const char *label);
uint32_t STDCALL GetDriveSerial(uint8_t drive);
BOOL STDCALL SetDriveSerial(uint8_t drive, uint32_t serial);
BOOL STDCALL IsDriveValid(uint8_t drive);
uint32_t STDCALL GetValidDrives(void);
uint32_t STDCALL GetValidDriveNames(char *names, uint32_t len);
uint32_t STDCALL GetDriveFreeSpace(uint8_t drive);
int64_t STDCALL GetDriveFreeSpaceEx(uint8_t drive);
uint32_t STDCALL GetDriveTotalSpace(uint8_t drive);
int64_t STDCALL GetDriveTotalSpaceEx(uint8_t drive);

BOOL STDCALL GetDriveInformation(const char *path, uint32_t *clustersize, int64_t *totalclustercount, int64_t *freeclustercount);

uint8_t STDCALL GetCurrentDrive(void);
BOOL STDCALL SetCurrentDrive(const char *drive);

/** File Functions (Compatibility) */
BOOL STDCALL AreFileApisANSI(void);
void STDCALL SetFileApisToOEM(void);
void STDCALL SetFileApisToANSI(void);

HANDLE STDCALL CreateFile(const char *lpfilename, uint32_t dwdesiredaccess, uint32_t dwsharemode, SECURITY_ATTRIBUTES *lpsecurityattributes, uint32_t dwcreationdisposition, uint32_t dwflagsandattributes, HANDLE htemplatefile);

/**
 * @note lpSecurityAttributes and hTemplateFile are currently ignored by Ultibo
 */
HANDLE STDCALL CreateFileA(const char *lpfilename, uint32_t dwdesiredaccess, uint32_t dwsharemode, SECURITY_ATTRIBUTES *lpsecurityattributes, uint32_t dwcreationdisposition, uint32_t dwflagsandattributes, HANDLE htemplatefile);

/**
 * @note lpSecurityAttributes and hTemplateFile are currently ignored by Ultibo
 */
HANDLE STDCALL CreateFileW(const WCHAR *lpfilename, uint32_t dwdesiredaccess, uint32_t dwsharemode, SECURITY_ATTRIBUTES *lpsecurityattributes, uint32_t dwcreationdisposition, uint32_t dwflagsandattributes, HANDLE htemplatefile);

BOOL STDCALL SetFileAttributes(const char *lpfilename, uint32_t dwfileattributes);
BOOL STDCALL SetFileAttributesA(const char *lpfilename, uint32_t dwfileattributes);
BOOL STDCALL SetFileAttributesW(const WCHAR *lpfilename, uint32_t dwfileattributes);

uint32_t STDCALL GetFileAttributes(const char *lpfilename);
uint32_t STDCALL GetFileAttributesA(const char *lpfilename);
uint32_t STDCALL GetFileAttributesW(const WCHAR *lpfilename);

BOOL STDCALL DeleteFile(const char *lpfilename);
BOOL STDCALL DeleteFileA(const char *lpfilename);
BOOL STDCALL DeleteFileW(const WCHAR *lpfilename);

BOOL STDCALL MoveFile(const char *lpexistingfilename, const char *lpnewfilename);
BOOL STDCALL MoveFileA(const char *lpexistingfilename, const char *lpnewfilename);
BOOL STDCALL MoveFileW(const WCHAR *lpexistingfilename, const WCHAR *lpnewfilename);

HANDLE STDCALL FindFirstFile(const char *lpfilename, WIN32_FIND_DATAA *lpfindfiledata);
HANDLE STDCALL FindFirstFileA(const char *lpfilename, WIN32_FIND_DATAA *lpfindfiledata);
HANDLE STDCALL FindFirstFileW(const WCHAR *lpfilename, WIN32_FIND_DATAW *lpfindfiledata);

BOOL STDCALL FindNextFile(HANDLE hfindfile, WIN32_FIND_DATAA *lpfindfiledata);
BOOL STDCALL FindNextFileA(HANDLE hfindfile, WIN32_FIND_DATAA *lpfindfiledata);
BOOL STDCALL FindNextFileW(HANDLE hfindfile, WIN32_FIND_DATAW *lpfindfiledata);

BOOL STDCALL FindCloseFile(HANDLE hfindfile);

uint32_t STDCALL GetFileSize(HANDLE hfile, DWORD *lpfilesizehigh);
BOOL STDCALL GetFileSizeEx(HANDLE hfile, LARGE_INTEGER *lpfilesize);

BOOL STDCALL GetFileTime(HANDLE hfile, FILETIME *lpcreationtime, FILETIME *lplastaccesstime, FILETIME *lplastwritetime);
BOOL STDCALL SetFileTime(HANDLE hfile, FILETIME *lpcreationtime, FILETIME *lplastaccesstime, FILETIME *lplastwritetime);

BOOL STDCALL ReadFile(HANDLE hfile, void *lpbuffer, uint32_t nnumberofbytestoread, DWORD *lpnumberofbytesread, OVERLAPPED *lpoverlapped);
BOOL STDCALL WriteFile(HANDLE hfile, void *lpbuffer, uint32_t nnumberofbytestowrite, DWORD *lpnumberofbyteswritten, OVERLAPPED *lpoverlapped);

BOOL STDCALL SetEndOfFile(HANDLE hfile);

uint32_t STDCALL SetFilePointer(HANDLE hfile, long ldistancetomove, long *lpdistancetomovehigh, uint32_t dwmovemethod);
BOOL STDCALL SetFilePointerEx(HANDLE hfile, LARGE_INTEGER lidistancetomove, LARGE_INTEGER *lpnewfilepointer, uint32_t dwmovemethod);

BOOL STDCALL FlushFileBuffers(HANDLE hfile);

BOOL STDCALL CopyFile(const char *lpexistingfilename, const char *lpnewfilename, BOOL bfailifexists);
BOOL STDCALL CopyFileA(const char *lpexistingfilename, const char *lpnewfilename, BOOL bfailifexists);
BOOL STDCALL CopyFileW(const WCHAR *lpexistingfilename, const WCHAR *lpnewfilename, BOOL bfailifexists);

BOOL STDCALL SetFileShortName(HANDLE hfile, const char *lpshortname);
BOOL STDCALL SetFileShortNameA(HANDLE hfile, const char *lpshortname);
BOOL STDCALL SetFileShortNameW(HANDLE hfile, const WCHAR *lpshortname);

BOOL STDCALL CreateHardLink(const char *lpfilename, const char *lpexistingfilename, SECURITY_ATTRIBUTES *lpsecurityattributes);

/**
 * @note lpSecurityAttributes is currently ignored by Ultibo
 */
BOOL STDCALL CreateHardLinkA(const char *lpfilename, const char *lpexistingfilename, SECURITY_ATTRIBUTES *lpsecurityattributes);

/**
 * @note lpSecurityAttributes is currently ignored by Ultibo
 */
BOOL STDCALL CreateHardLinkW(const WCHAR *lpfilename, const WCHAR *lpexistingfilename, SECURITY_ATTRIBUTES *lpsecurityattributes);

BOOL STDCALL CreateSymbolicLink(const char *lpsymlinkfilename, const char *lptargetfilename, uint32_t dwflags);
BOOL STDCALL CreateSymbolicLinkA(const char *lpsymlinkfilename, const char *lptargetfilename, uint32_t dwflags);
BOOL STDCALL CreateSymbolicLinkW(const WCHAR *lpsymlinkfilename, const WCHAR *lptargetfilename, uint32_t dwflags);

BOOL STDCALL GetFileInformationByHandle(HANDLE hfile, BY_HANDLE_FILE_INFORMATION *lpfileinformation);

/**
 * @brief Retrieves the final path for the specified open file handle
 */
uint32_t STDCALL GetFinalPathNameByHandle(HANDLE hfile, char *lpszFilePath, uint32_t cchFilePath, uint32_t dwFlags);

/**
 * @brief Retrieves the final path for the specified open file handle
 */
uint32_t STDCALL GetFinalPathNameByHandleA(HANDLE hfile, char *lpszFilePath, uint32_t cchFilePath, uint32_t dwFlags);

/**
 * @brief Retrieves the final path for the specified open file handle
 */
uint32_t STDCALL GetFinalPathNameByHandleW(HANDLE hfile, WCHAR *lpszFilePath, uint32_t cchFilePath, uint32_t dwFlags);

/** File Functions (Ultibo) */

/** Directory Functions (Compatibility) */
BOOL STDCALL CreateDirectory(const char *lppathname, SECURITY_ATTRIBUTES *lpsecurityattributes);

/**
 * @note lpSecurityAttributes is currently ignored by Ultibo
 */
BOOL STDCALL CreateDirectoryA(const char *lppathname, SECURITY_ATTRIBUTES *lpsecurityattributes);

/**
 * @note lpSecurityAttributes is currently ignored by Ultibo
 */
BOOL STDCALL CreateDirectoryW(const WCHAR *lppathname, SECURITY_ATTRIBUTES *lpsecurityattributes);

BOOL STDCALL RemoveDirectory(const char *lppathname);
BOOL STDCALL RemoveDirectoryA(const char *lppathname);
BOOL STDCALL RemoveDirectoryW(const WCHAR *lppathname);

BOOL STDCALL SetCurrentDirectory(const char *lppathname);
BOOL STDCALL SetCurrentDirectoryA(const char *lppathname);
BOOL STDCALL SetCurrentDirectoryW(const WCHAR *lppathname);

uint32_t STDCALL GetCurrentDirectory(uint32_t nbufferlength, char *lpbuffer);
uint32_t STDCALL GetCurrentDirectoryA(uint32_t nbufferlength, char *lpbuffer);
uint32_t STDCALL GetCurrentDirectoryW(uint32_t nbufferlength, WCHAR *lpbuffer);

uint32_t STDCALL GetLongPathName(const char *lpszshortpath, char *lpszlongpath, uint32_t cchbuffer);
uint32_t STDCALL GetLongPathNameA(const char *lpszshortpath, char *lpszlongpath, uint32_t cchbuffer);
uint32_t STDCALL GetLongPathNameW(const WCHAR *lpszshortpath, WCHAR *lpszlongpath, uint32_t cchbuffer);

uint32_t STDCALL GetShortPathName(const char *lpszlongpath, char *lpszshortpath, uint32_t cchbuffer);
uint32_t STDCALL GetShortPathNameA(const char *lpszlongpath, char *lpszshortpath, uint32_t cchbuffer);
uint32_t STDCALL GetShortPathNameW(const WCHAR *lpszlongpath, WCHAR *lpszshortpath, uint32_t cchbuffer);

uint32_t STDCALL GetFullPathName(const char *lpfilename, uint32_t nbufferlength, char *lpbuffer, char *lpfilepart);

/**
 * @note lpFilePart is currently ignored by Ultibo
 */
uint32_t STDCALL GetFullPathNameA(const char *lpfilename, uint32_t nbufferlength, char *lpbuffer, char *lpfilepart);

/**
 * @note lpFilePart is currently ignored by Ultibo
 */
uint32_t STDCALL GetFullPathNameW(const WCHAR *lpfilename, uint32_t nbufferlength, WCHAR *lpbuffer, WCHAR *lpfilepart);

/** Directory Functions (Ultibo) */

/** Command Line Functions (Compatibility) */
char * STDCALL GetCommandLine(void);

/**
 * @note The returned string must be freed with SysUtils.StrDispose
 */
char * STDCALL GetCommandLineA(void);

/**
 * @note The returned string must be freed with SysUtils.StrDispose
 */
WCHAR * STDCALL GetCommandLineW(void);

/** Command Line Functions (Ultibo) */

/**
 * @brief Check if the specified parameter is present in the command line
 */
BOOL STDCALL IsParamPresent(const char *param);

/**
 * @brief Get the index of the specified parameter in the command line
 */
int STDCALL GetParamIndex(const char *param);

/**
 * @brief Get the value of the specified parameter from the command line
 */
uint32_t STDCALL GetParamValue(const char *param, char *value, uint32_t len);

/** Environment Functions (Compatibility) */
char * STDCALL GetEnvironmentStrings(void);
char * STDCALL GetEnvironmentStringsA(void);
WCHAR * STDCALL GetEnvironmentStringsW(void);

BOOL STDCALL FreeEnvironmentStrings(char *pstr);
BOOL STDCALL FreeEnvironmentStringsA(char *pstr);
BOOL STDCALL FreeEnvironmentStringsW(WCHAR *pstr);

uint32_t STDCALL GetEnvironmentVariable(const char *lpname, char *lpbuffer, uint32_t nsize);
uint32_t STDCALL GetEnvironmentVariableA(const char *lpname, char *lpbuffer, uint32_t nsize);
uint32_t STDCALL GetEnvironmentVariableW(const WCHAR *lpname, WCHAR *lpbuffer, uint32_t nsize);

BOOL STDCALL SetEnvironmentVariable(const char *lpname, const char *lpvalue);
BOOL STDCALL SetEnvironmentVariableA(const char *lpname, const char *lpvalue);
BOOL STDCALL SetEnvironmentVariableW(const WCHAR *lpname, const WCHAR *lpvalue);

uint32_t STDCALL ExpandEnvironmentStrings(const char *lpsrc, char *lpdst, uint32_t nsize);
uint32_t STDCALL ExpandEnvironmentStringsA(const char *lpsrc, char *lpdst, uint32_t nsize);
uint32_t STDCALL ExpandEnvironmentStringsW(const WCHAR *lpsrc, WCHAR *lpdst, uint32_t nsize);

/** Error Functions (Compatibility) */

/**
 * @brief Get the last error value for the calling thread
 */
uint32_t STDCALL GetLastError(void);

/**
 * @brief Set the last error value for the calling thread
 */
void STDCALL SetLastError(uint32_t dwerrcode);

/** String Functions (Ultibo) */

/** GUID Functions (Ultibo) */

/**
 * @brief Create a new GUID
 * GUID has the following format DWORD-WORD-WORD-WORD-WORDDWORD
 *                                              | Not Swapped  |
 */
GUID STDCALL CreateGUID(void);

/**
 * @brief Convert a TGUID to a string representation
 */
uint32_t STDCALL GUIDToString(GUID *value, char *string, uint32_t len);

/**
 * @brief Convert a string to a native TGUID type
 */
GUID STDCALL StringToGUID(const char *value);

/**
 * @brief Check if a TGUID is empty (All zeroes)
 */
BOOL STDCALL NullGUID(GUID *guid);

/**
 * @brief Check whether two TGUID variables are equal
 */
BOOL STDCALL CompareGUID(GUID *guid1, GUID *guid2);

/** SID Functions (Ultibo) */
//uint32_t STDCALL SIDToString(SID *sid, char *string, uint32_t len); //To Do //security.h
//SID * STDCALL StringToSID(char *value); //To Do //security.h

/** Date Functions (Ultibo) */

/** Numeric Functions (Ultibo) */
int STDCALL Min(int a, int b);
int STDCALL Max(int a, int b);

uint32_t STDCALL MinEx(uint32_t a, uint32_t b);
uint32_t STDCALL MaxEx(uint32_t a, uint32_t b);

int64_t STDCALL Min64(int64_t *a, int64_t *b);
int64_t STDCALL Max64(int64_t *a, int64_t *b);

int64_t STDCALL Or64(int64_t *value1, int64_t *value2);
int64_t STDCALL And64(int64_t *value1, int64_t *value2);
int64_t STDCALL Xor64(int64_t *value1, int64_t *value2);
int64_t STDCALL Not64(int64_t *value);

uint32_t STDCALL Rol32(uint32_t value, uint8_t count);
uint32_t STDCALL Ror32(uint32_t value, uint8_t count);

uint16_t STDCALL WordSwap(uint16_t value);
uint32_t STDCALL LongSwap(uint32_t value);
int64_t STDCALL Int64Swap(int64_t *value);

/**
 * @brief Swap each word in the buffer supplied up to size
 * @note Size is the number of Bytes in the buffer to swap
 */
BOOL STDCALL BufferSwap(void *buffer, uint32_t size);

/** Hash Functions (Ultibo) */

/**
 * @brief Sum of (byte value + 1) * (position + 257) for all bytes in uppercase string
 * @note Case Insensitive Hash
 */
uint32_t STDCALL GenerateNameHash(const char *name, int size);

/**
 * @brief Sum of (byte value + 1) * (position + 257) for all bytes in string
 */
uint32_t STDCALL GenerateStringHash(const char *value, BOOL casesensitive);

/** Locale Functions (Compatibility) */
BOOL STDCALL IsValidLocale(LCID localeid, uint32_t dwflags);

LCID STDCALL GetSystemDefaultLCID(void);
LCID STDCALL GetUserDefaultLCID(void);

LCID STDCALL GetThreadLocale(void);
BOOL STDCALL SetThreadLocale(LCID localeid);

/** Locale Functions (Ultibo) */
BOOL STDCALL SetSystemDefaultLCID(LCID localeid);

/**
 * @brief A replacement for WideCharToString in System unit to allow cross platform compatibility
 * @note The WideStringManager installed by the Unicode unit should make the System version equivalent
 */
uint32_t STDCALL WideCharToString(const WCHAR *buffer, char *string, uint32_t len);

/**
 * @brief A replacement for WideCharLenToString in System unit to allow cross platform compatibility
 * @note Length is the size of the Buffer in WideChars (not Bytes)
 * @note The WideStringManager installed by the Unicode unit should make the System version equivalent
 */
uint32_t STDCALL WideCharLenToString(const WCHAR *buffer, int length, char *string, uint32_t len);

/**
 * @brief A replacement for StringToWideChar in System unit to allow cross platform compatibility
 * @note Size is the size of the Buffer in Bytes (not WideChars)
 * @note The WideStringManager installed by the Unicode unit should make the System version equivalent
 */
BOOL STDCALL StringToWideChar(const char *string, WCHAR *buffer, int size);

/** Code Page Functions (Compatibility) */
BOOL STDCALL IsValidCodePage(UINT codepage);

UINT STDCALL GetACP(void);
UINT STDCALL GetOEMCP(void);

UINT STDCALL GetConsoleCP(void);
BOOL STDCALL SetConsoleCP(UINT wcodepageid);

UINT STDCALL GetConsoleOutputCP(void);
BOOL STDCALL SetConsoleOutputCP(UINT wcodepageid);

BOOL STDCALL GetCPInfo(UINT codepage, CPINFO *lpcpinfo);

BOOL STDCALL GetCPInfoEx(UINT codepage, uint32_t dwflags, CPINFOEXA *lpcpinfoex);
BOOL STDCALL GetCPInfoExA(UINT codepage, uint32_t dwflags, CPINFOEXA *lpcpinfoex);
BOOL STDCALL GetCPInfoExW(UINT codepage, uint32_t dwflags, CPINFOEXW *lpcpinfoex);

/** Code Page Functions (Ultibo) */
BOOL STDCALL SetACP(UINT codepage);
BOOL STDCALL SetOEMCP(UINT codepage);

/** Translation Functions (Compatibility) */
int STDCALL MultiByteToWideChar(UINT codepage, uint32_t dwflags, char *lpmultibytestr, int cbmultibyte, WCHAR *lpwidecharstr, int cchwidechar);
int STDCALL WideCharToMultiByte(UINT codepage, uint32_t dwflags, WCHAR *lpwidecharstr, int cchwidechar, char *lpmultibytestr, int cbmultibyte, char *lpdefaultchar, BOOL *lpuseddefaultchar);

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

/** Handle Functions (Compatibility) */
BOOL STDCALL CloseHandle(HANDLE hobject);
BOOL STDCALL DuplicateHandle(HANDLE hsourceprocesshandle, HANDLE hsourcehandle, HANDLE htargetprocesshandle, HANDLE *lptargethandle, uint32_t dwdesiredaccess, BOOL binherithandle, uint32_t dwoptions);

BOOL STDCALL GetHandleInformation(HANDLE hobject, uint32_t *lpdwflags);
BOOL STDCALL SetHandleInformation(HANDLE hobject, uint32_t dwmask, uint32_t dwflags);

/** Memory Functions (Compatibility) */
void STDCALL MoveMemory(void *destination, void *source, SIZE_T length);
void STDCALL CopyMemory(void *destination, void *source, SIZE_T length);
void STDCALL FillMemory(void *destination, SIZE_T length, uint8_t fill);
void STDCALL ZeroMemory(void *destination, SIZE_T length);

HGLOBAL STDCALL GlobalAlloc(UINT uflags, SIZE_T dwbytes);
HGLOBAL STDCALL GlobalReAlloc(HGLOBAL hmem, SIZE_T dwbytes, UINT uflags);
HGLOBAL STDCALL GlobalFree(HGLOBAL hmem);

SIZE_T STDCALL GlobalSize(HGLOBAL hmem);
UINT STDCALL GlobalFlags(HGLOBAL hmem);

void * STDCALL GlobalLock(HGLOBAL hmem);
BOOL STDCALL GlobalUnlock(HGLOBAL hmem);

HGLOBAL STDCALL GlobalHandle(void *pmem);

void STDCALL GlobalMemoryStatus(MEMORYSTATUS *lpbuffer);
BOOL STDCALL GlobalMemoryStatusEx(MEMORYSTATUSEX *lpbuffer);

HLOCAL STDCALL LocalAlloc(UINT uflags, SIZE_T ubytes);
HLOCAL STDCALL LocalReAlloc(HLOCAL hmem, SIZE_T ubytes, UINT uflags);
HLOCAL STDCALL LocalFree(HLOCAL hmem);

SIZE_T STDCALL LocalSize(HLOCAL hmem);
UINT STDCALL LocalFlags(HLOCAL hmem);

void * STDCALL LocalLock(HLOCAL hmem);
BOOL STDCALL LocalUnlock(HLOCAL hmem);

HLOCAL STDCALL LocalHandle(void *pmem);

/**
 * @note The value of lpAddress on entry is currently ignored by Ultibo
 * @note The value of flProtect is currently ignored by Ultibo
 * @note As per Win32, the value of dwSize is rounded to the next page multiple
 */
void * STDCALL VirtualAlloc(void *lpaddress, SIZE_T dwsize, uint32_t flallocationtype, uint32_t flprotect);
BOOL STDCALL VirtualFree(void *lpaddress, SIZE_T dwsize, uint32_t dwfreetype);

uint32_t STDCALL VirtualQuery(void *lpaddress, MEMORY_BASIC_INFORMATION *lpbuffer, uint32_t dwlength);

BOOL STDCALL VirtualLock(void *lpaddress, SIZE_T dwsize);
BOOL STDCALL VirtualUnlock(void *lpaddress, SIZE_T dwsize);

BOOL STDCALL FlushInstructionCache(HANDLE hprocess, void *lpbaseaddress, uint32_t dwsize);

BOOL STDCALL GetNumaHighestNodeNumber(ULONG *highestnodenumber);
BOOL STDCALL GetNumaProcessorNode(uint8_t *processor, uint8_t *nodenumber);

/** Tls Functions (Compatibility) */
uint32_t STDCALL TlsAlloc(void);

/**
 * @param bFree If true then TlsValue will be freed on TlsFree or thread terminate
 */
uint32_t STDCALL TlsAllocEx(BOOL bfree);
void * STDCALL TlsGetValue(uint32_t dwtlsindex);
BOOL STDCALL TlsSetValue(uint32_t dwtlsindex, void *lptlsvalue);
BOOL STDCALL TlsFree(uint32_t dwtlsindex);

/** Thread Functions (Compatibility) */
BOOL STDCALL SwitchToThread(void);

void STDCALL Sleep(uint32_t dwmilliseconds);

/**
 * @note The bAlertable parameter is not currently used but is intended for I/O completion callback from ReadFileEx/WriteFileEx
 */
uint32_t STDCALL SleepEx(uint32_t dwmilliseconds, BOOL balertable);

HANDLE STDCALL GetCurrentThread(void);

/**
 * @note Thread Id and Thread Handle are currently equivalent
 */
uint32_t STDCALL GetCurrentThreadId(void);

/**
 * @note Returns priority values in the range -15..+15, must use the FPC RTL function
 */
int STDCALL GetThreadPriority(HANDLE hthread);

/**
 * @note Expects priority values in the range -15..+15, must use the FPC RTL function
 */
BOOL STDCALL SetThreadPriority(HANDLE hthread, int npriority);

BOOL STDCALL GetExitCodeThread(HANDLE hthread, uint32_t *lpexitcode);

DWORD_PTR STDCALL GetThreadAffinityMask(HANDLE hthread);
DWORD_PTR STDCALL SetThreadAffinityMask(HANDLE hthread, DWORD_PTR dwthreadaffinitymask);

BOOL STDCALL GetThreadTimes(HANDLE hthread, FILETIME *lpcreationtime, FILETIME *lpexittime, FILETIME *lpkerneltime, FILETIME *lpusertime);

HANDLE STDCALL CreateThread(SECURITY_ATTRIBUTES *lpthreadattributes, uint32_t dwstacksize, THREAD_START_ROUTINE lpstartaddress, void *lpparameter, uint32_t dwcreationflags, DWORD *lpthreadid);
HANDLE STDCALL OpenThread(uint32_t dwdesiredaccess, BOOL binherithandle, uint32_t dwthreadid);

uint32_t STDCALL SuspendThread(HANDLE hthread);
uint32_t STDCALL ResumeThread(HANDLE hthread);

BOOL STDCALL TerminateThread(HANDLE hthread, uint32_t dwexitcode);

void STDCALL ExitThread(uint32_t dwexitcode);

uint32_t STDCALL WaitForSingleObject(HANDLE hhandle, uint32_t dwmilliseconds);
uint32_t STDCALL WaitForMultipleObjects(uint32_t ncount, HANDLE *lphandles, BOOL bwaitall, uint32_t dwmilliseconds);

/**
 * @note The bAlertable parameter is not currently used but is intended for I/O completion callback from ReadFileEx/WriteFileEx
 */
uint32_t STDCALL WaitForSingleObjectEx(HANDLE hhandle, uint32_t dwmilliseconds, BOOL balertable);

/**
 * @note The bAlertable parameter is not currently used but is intended for I/O completion callback from ReadFileEx/WriteFileEx
 */
uint32_t STDCALL WaitForMultipleObjectsEx(uint32_t ncount, HANDLE *lphandles, BOOL bwaitall, uint32_t dwmilliseconds, BOOL balertable);

/** Thread Functions (Ultibo) */
THREAD_ID STDCALL BeginThreadEx(thread_func threadfunction, void *parameter, THREAD_ID *threadid, size_t *stacksize, uint32_t priority, uint32_t affinity, uint32_t cpu, const char *name);

/** Message Functions (Compatibility) */
BOOL STDCALL WaitMessage(void);

BOOL STDCALL GetMessage(MSG *lpmsg, HANDLE hthread, UINT wmsgfiltermin, UINT wmsgfiltermax);
BOOL STDCALL PeekMessage(MSG *lpmsg, HANDLE hthread, UINT wmsgfiltermin, UINT wmsgfiltermax, UINT wremovemsg);

BOOL STDCALL PostMessage(HANDLE hthread, UINT msg, WPARAM wparam, LPARAM lparam);
LRESULT STDCALL SendMessage(HANDLE hthread, UINT msg, WPARAM wparam, LPARAM lparam);
LRESULT STDCALL SendMessageTimeout(HANDLE hthread, UINT msg, WPARAM wparam, LPARAM lparam, UINT fuflags, UINT utimeout, DWORD_PTR *lpdwresult);

/** Notification Functions (Compatibility) */

/** Interlocked Functions (Compatibility) */
long STDCALL InterlockedIncrement(long *lpaddend);
long STDCALL InterlockedDecrement(long *lpaddend);

long STDCALL InterlockedExchange(long *target, long value);
void * STDCALL InterlockedExchangePointer(void *target, void *value);

long STDCALL InterlockedExchangeAdd(long *addend, long value);
long STDCALL InterlockedCompareExchange(long *destination, long exchange, long comperand);
void * STDCALL InterlockedCompareExchangePointer(void *destination, void *exchange, void *comperand);

/** Mutex Functions (Compatibility) */
HANDLE STDCALL CreateMutex(SECURITY_ATTRIBUTES *lpmutexattributes, BOOL binitialowner, const char *lpname);
HANDLE STDCALL CreateMutexA(SECURITY_ATTRIBUTES *lpmutexattributes, BOOL binitialowner, const char *lpname);
HANDLE STDCALL CreateMutexW(SECURITY_ATTRIBUTES *lpmutexattributes, BOOL binitialowner, const WCHAR *lpname);

HANDLE STDCALL OpenMutex(uint32_t dwdesiredaccess, BOOL binherithandle, const char *lpname);
HANDLE STDCALL OpenMutexA(uint32_t dwdesiredaccess, BOOL binherithandle, const char *lpname);
HANDLE STDCALL OpenMutexW(uint32_t dwdesiredaccess, BOOL binherithandle, const WCHAR *lpname);

BOOL STDCALL ReleaseMutex(HANDLE hmutex);

/** Semaphore Functions (Compatibility) */
HANDLE STDCALL CreateSemaphore(SECURITY_ATTRIBUTES *lpsemaphoreattributes, long linitialcount, long lmaximumcount, const char *lpname);
HANDLE STDCALL CreateSemaphoreA(SECURITY_ATTRIBUTES *lpsemaphoreattributes, long linitialcount, long lmaximumcount, const char *lpname);
HANDLE STDCALL CreateSemaphoreW(SECURITY_ATTRIBUTES *lpsemaphoreattributes, long linitialcount, long lmaximumcount, const WCHAR *lpname);

HANDLE STDCALL OpenSemaphore(uint32_t dwdesiredaccess, BOOL binherithandle, const char *lpname);
HANDLE STDCALL OpenSemaphoreA(uint32_t dwdesiredaccess, BOOL binherithandle, const char *lpname);
HANDLE STDCALL OpenSemaphoreW(uint32_t dwdesiredaccess, BOOL binherithandle, const WCHAR *lpname);

BOOL STDCALL ReleaseSemaphore(HANDLE hsemaphore, long lreleasecount, long *lppreviouscount);

/** Critical Section Functions (Compatibility) */
void STDCALL InitializeCriticalSection(CRITICAL_SECTION *lpcriticalsection);
void STDCALL EnterCriticalSection(CRITICAL_SECTION *lpcriticalsection);
void STDCALL LeaveCriticalSection(CRITICAL_SECTION *lpcriticalsection);
BOOL STDCALL TryEnterCriticalSection(CRITICAL_SECTION *lpcriticalsection);

BOOL STDCALL InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION *lpcriticalsection, uint32_t dwspincount);
uint32_t STDCALL SetCriticalSectionSpinCount(CRITICAL_SECTION *lpcriticalsection, uint32_t dwspincount);

void STDCALL DeleteCriticalSection(CRITICAL_SECTION *lpcriticalsection);

/** Condition Variable Functions (Compatibility) */

/**
 * @brief Initializes a condition variable
 * @param ConditionVariable The condition variable to initialize
 */
void STDCALL InitializeConditionVariable(CONDITION_VARIABLE *conditionvariable);

/**
 * @brief Wake a single thread waiting on the specified condition variable
 * @param ConditionVariable The condition variable to wake
 */
void STDCALL WakeConditionVariable(CONDITION_VARIABLE *conditionvariable);

/**
 * @brief Wake all threads waiting on the specified condition variable
 * @param ConditionVariable The condition variable to wake
 */
void STDCALL WakeAllConditionVariable(CONDITION_VARIABLE *conditionvariable);

/**
 * @brief Sleeps on the specified condition variable and releases the specified critical section as an atomic operation
 * @param ConditionVariable The condition variable to sleep on
 * @param CriticalSection The critical section object to release (This critical section must be entered exactly once by the caller at the time SleepConditionVariableCS is called)
 * @param dwMilliseconds The time-out interval, in milliseconds. (If the time-out interval elapses, the function re-acquires the critical section and returns false)
 */
BOOL STDCALL SleepConditionVariableCS(CONDITION_VARIABLE *conditionvariable, CRITICAL_SECTION *criticalsection, uint32_t dwmilliseconds);

/**
 * @brief Destroy a condition variable
 * @param ConditionVariable The condition variable to destroy
 * @note This function is Ultibo specific and is not part of the normal Windows API
 */
void STDCALL DeleteConditionVariable(CONDITION_VARIABLE *conditionvariable);

/** Event Functions (Compatibility) */
HANDLE STDCALL CreateEvent(SECURITY_ATTRIBUTES *lpeventattributes, BOOL bmanualreset, BOOL binitialstate, const char *lpname);
HANDLE STDCALL CreateEventA(SECURITY_ATTRIBUTES *lpeventattributes, BOOL bmanualreset, BOOL binitialstate, const char *lpname);
HANDLE STDCALL CreateEventW(SECURITY_ATTRIBUTES *lpeventattributes, BOOL bmanualreset, BOOL binitialstate, const WCHAR *lpname);

HANDLE STDCALL OpenEvent(uint32_t dwdesiredaccess, BOOL binherithandle, const char *lpname);
HANDLE STDCALL OpenEventA(uint32_t dwdesiredaccess, BOOL binherithandle, const char *lpname);
HANDLE STDCALL OpenEventW(uint32_t dwdesiredaccess, BOOL binherithandle, const WCHAR *lpname);

BOOL STDCALL SetEvent(HANDLE hevent);
BOOL STDCALL ResetEvent(HANDLE hevent);
BOOL STDCALL PulseEvent(HANDLE hevent);

/** Process Functions (Compatibility) */

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 */
BOOL STDCALL GetProcessAffinityMask(HANDLE hprocess, DWORD_PTR *lpprocessaffinitymask, DWORD_PTR *lpsystemaffinitymask);

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 */
BOOL STDCALL SetProcessAffinityMask(HANDLE hprocess, DWORD_PTR dwprocessaffinitymask);

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 */
BOOL STDCALL GetProcessTimes(HANDLE hprocess, FILETIME *lpcreationtime, FILETIME *lpexittime, FILETIME *lpkerneltime, FILETIME *lpusertime);

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 */
BOOL STDCALL GetProcessIoCounters(HANDLE hprocess, IO_COUNTERS *lpiocounters);

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 */
HANDLE STDCALL GetCurrentProcess(void);

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 * @note Thread Id and Thread Handle are currently equivalent
 */
uint32_t STDCALL GetCurrentProcessId(void);

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 */
void STDCALL ExitProcess(UINT uexitcode);

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 */
void STDCALL FatalExit(int exitcode);

/**
 * @note Ultibo has no concept of a Process so this function is mapped to Threads instead
 */
BOOL STDCALL TerminateProcess(HANDLE hprocess, UINT uexitcode);

/** Debug Functions (Compatibility) */
void STDCALL OutputDebugString(const char *lpoutputstring);
void STDCALL OutputDebugStringA(const char *lpoutputstring);
void STDCALL OutputDebugStringW(const WCHAR *lpoutputstring);

/** Library Functions (Compatibility) */
int STDCALL lstrcmp(char *lpstring1, char *lpstring2);
int STDCALL lstrcmpA(char *lpstring1, char *lpstring2);
int STDCALL lstrcmpW(WCHAR *lpstring1, WCHAR *lpstring2);

int STDCALL lstrcmpi(char *lpstring1, char *lpstring2);
int STDCALL lstrcmpiA(char *lpstring1, char *lpstring2);
int STDCALL lstrcmpiW(WCHAR *lpstring1, WCHAR *lpstring2);

char * STDCALL lstrcpy(char *lpstring1, char *lpstring2);
char * STDCALL lstrcpyA(char *lpstring1, char *lpstring2);
WCHAR * STDCALL lstrcpyW(WCHAR *lpstring1, WCHAR *lpstring2);

char * STDCALL lstrcpyn(char *lpstring1, char *lpstring2, int imaxlength);
char * STDCALL lstrcpynA(char *lpstring1, char *lpstring2, int imaxlength);
WCHAR * STDCALL lstrcpynW(WCHAR *lpstring1, WCHAR *lpstring2, int imaxlength);

char * STDCALL lstrcat(char *lpstring1, char *lpstring2);
char * STDCALL lstrcatA(char *lpstring1, char *lpstring2);
WCHAR * STDCALL lstrcatW(WCHAR *lpstring1, WCHAR *lpstring2);

int STDCALL lstrlen(char *lpstring);
int STDCALL lstrlenA(char *lpstring);
int STDCALL lstrlenW(WCHAR *lpstring);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_ULTIBO_H
