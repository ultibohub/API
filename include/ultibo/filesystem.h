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
#ifndef _ULTIBO_FILESYSTEM_H
#define _ULTIBO_FILESYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/storage.h"
#include "ultibo/ultibo.h"

/* ============================================================================== */
/* FileSystem specific constants */
#define FILESYS_LOGGING_DESCRIPTION	"Filesystem Logging"

#define FILESYS_STORAGE_TIMER_INTERVAL	100 // Timer interval for device additions or insertions

/* FileSystem Lock States */
#define FILESYS_LOCK_NONE	0
#define FILESYS_LOCK_READ	1
#define FILESYS_LOCK_WRITE	2
#define FILESYS_LOCK_AUTO	3 // Not intended for use in all situations, use with extreme caution

/* FileSystem Cache */
#define FILESYS_CACHE_THREAD_NAME	"Filesystem Cache" // Thread name for Filesystem cache threads
#define FILESYS_CACHE_THREAD_PRIORITY	THREAD_PRIORITY_HIGHER // Thread priority for Filesystem cache threads

#define FILESYS_CACHE_TIMER_INTERVAL	50 // 50ms timer interval for Filesystem cache
#define FILESYS_CACHE_FLUSH_TIMEOUT	3000 // Filesystem cache flush timeout 3 seconds
#define FILESYS_CACHE_DISCARD_TIMEOUT	180000 // Filesystem cache discard timeout 3 minutes

/* Entry Timer */
#define FILESYS_ENTRY_TIMER_INTERVAL	1000 // 1000ms timer interval for Filesystem entries
#define FILESYS_ENTRY_DELETE_TIMEOUT	30000 // Filesystem entry delete timeout 30 seconds

/* Cache Timer */
#define CACHE_TIMER_KEY_NONE	TIMER_KEY_NONE
#define CACHE_TIMER_KEY_MAX	TIMER_KEY_MAX
#define CACHE_TIMER_KEY_MIN	TIMER_KEY_MIN

/* Entry Timer */
#define ENTRY_TIMER_KEY_NONE	TIMER_KEY_NONE
#define ENTRY_TIMER_KEY_MAX	TIMER_KEY_MAX
#define ENTRY_TIMER_KEY_MIN	TIMER_KEY_MIN

/* Partition, Device, Volume constants */
#define MIN_FLOPPY_DEVICE	0x00
#define MAX_FLOPPY_DEVICE	0x7F

#define MIN_FIXED_DEVICE	0x80
#define MAX_FIXED_DEVICE	0xFF // Extends over CDROM/Other

#define MIN_CDROM_DEVICE	0xE0
#define MAX_CDROM_DEVICE	0xEF

#define MIN_OTHER_DEVICE	0xF0
#define MAX_OTHER_DEVICE	0xFF

#define INVALID_PARTITION	-1
#define INVALID_DEVICE	-1
#define INVALID_VOLUME	0

#define MIN_PARTITION	0
#define MAX_PARTITION	3
#define MAX_EXTENDED	1 // Only 2 partitions in second level
#define MAX_PARTITION_COUNT 4

#define MIN_FLOPPY_DRIVE	MIN_DRIVE
#define MAX_FLOPPY_DRIVE	MIN_DRIVE + 1

#define MIN_FIXED_DRIVE	MIN_DRIVE + 2
#define MAX_FIXED_DRIVE	MAX_DRIVE

#define MIN_SECTOR_SIZE	512
#define MAX_SECTOR_SIZE	4096
#define ISO_SECTOR_SIZE	2048

#define VOLUME_PREFIX	"\\Volume" // eg \Volume1
#define EXTENDED_PREFIX	"\\Extended" // eg \Extended1
#define PARTITION_PREFIX	"\\Partition" // eg \Partition1
#define CONTROLLER_PREFIX	"\\Controller" // eg \Controller0
#define CDROM_DEVICE_PREFIX	"\\Cdrom" // eg \Cdrom0
#define OTHER_DEVICE_PREFIX	"\\Other" // eg \Other0
#define FIXED_DEVICE_PREFIX	"\\Harddisk" // eg \Harddisk0
#define FLOPPY_DEVICE_PREFIX	"\\Floppy" // eg \Floppy0
#define UNKNOWN_DEVICE_PREFIX	"\\Unknown" // eg \Unknown0

#define VOLUME_PATH_PREFIX	"\\\\?" // eg \\?\Volume1\Home
#define DEVICE_PATH_PREFIX	"\\\." // eg \\.\Harddisk0\Partition1\Home
#define REPARSE_PATH_PREFIX	"\\??\\"

#define BOOT_RECORD_SIGNATURE	0xAA55
#define PARTITION_RECORD_SIGNATURE	0xAA55
#define BOOT_SECTOR_SIGNATURE	0xAA55

/* Find Flags */
#define FIND_FLAG_NONE	0x00000000
#define FIND_FLAG_FILE_NAMES	0x00000001

/* Find Wildcards */
#define FIND_WILDCARD_NAME	"*.*"
#define FIND_WILDCARD_STREAM	"*"

/* File Seek origins */
#define fsFromBeginning	0
#define fsFromCurrent	1
#define fsFromEnd	2

/* File Mode constants */
#define fmOpenRead	0x0000
#define fmOpenWrite	0x0001
#define fmOpenReadWrite	0x0002
#define fmShareCompat	0x0000
#define fmShareExclusive	0x0010
#define fmShareDenyWrite	0x0020
#define fmShareDenyRead	0x0030
#define fmShareDenyNone	0x0040

#define fmOpenMask	0x000F
#define fmShareMask	0x00F0

/* File Attribute constants */
#define faReadOnly	0x00000001
#define faHidden	0x00000002
#define faSysFile	0x00000004
#define faVolumeID	0x00000008
#define faDirectory	0x00000010
#define faArchive	0x00000020
#define faSymLink	0x00000400
#define faVirtual	0x00010000
#define faAnyFile	0x000001FF

#define faDot	0x01000000
#define faDotDot	0x02000000
#define faFile	0x04000000
#define faStream	0x08000000
#define faFlagName	0x00100000 // Used for FAT case flags
#define faFlagExt	0x00200000 // Used for FAT case flags
#define faFlagBoth	(faFlagName | faFlagExt)
#define faFlagLong	0x00400000 // Not currently used
#define faFlagMetafile	0x00800000 // Used for NTFS Metafiles

#define faFlagMask	0x0FFF0000 // Used to preserve internal attributes
#define faFindMask	0x0000FFFF // Used to mask internal attributes
#define faMatchMask	(faFile | faStream | faVolumeID | faDirectory)

/* Additional File Attribute Flags for NTFS/EXTFS/NSS */
#define faDevice	0x00000040
#define faNormal	0x00000080
#define faTemporary	0x00000100
#define faSparse	0x00000200
#define faReparse	0x00000400 // See also faSymLink
#define faCompressed	0x00000800
#define faOffline	0x00001000
#define faNotIndexed	0x00002000
#define faEncrypted	0x00004000

#define faMftDirectory	0x10000000 // Used only by FileName Attribute
#define faMftIndexView	0x20000000 // Used by both the StandardInformation and FileName attributes

/* Note: NTFS does not store the faVolumeID or faDirectory attributes */

/* Additional File Attribute constants */
#define faNone	0x00000000
#define faStandard	(faReadOnly | faHidden | faSysFile | faArchive)
#define faLongName	(faReadOnly | faHidden | faSysFile | faVolumeID)
#define faLongMask	(faReadOnly | faHidden | faSysFile | faVolumeID | faDirectory | faArchive)

/* Volume Attribute constants */
#define vaNone	0x00000000
#define vaCaseSensitive	0x00000001
#define vaCasePreserved	0x00000002
#define vaUnicode	0x00000004
#define vaPersistentAcls	0x00000008
#define vaFileCompression	0x00000010
#define vaVolumeQuotas	0x00000020
#define vaSparseFiles	0x00000040
#define vaReparsePoints	0x00000080
#define vaRemoteStorage	0x00000100
#define vaLongNamesApi	0x00004000
#define vaVolumeCompressed	0x00008000
#define vaObjectIds	0x00010000
#define vaEncryption	0x00020000
#define vaNamedStreams	0x00040000
#define vaReadOnly	0x00080000

/* Additional Volume Attribute constants */
#define vaBootCatalog	0x01000000 // Used to indicate support for ISO Boot Catalogs
#define vaVirtualVolume	0x02000000 // Used to indicate Volume is Virtual or on a Virtual Device
#define vaFolderEncryption	0x04000000 // Used to indicate support for Folder Encryption (New files in folder are automatically encrypted)
#define vaFolderCompression	0x08000000 // Used to indicate support for Folder Compression (New files in folder are automatically compressed)

/* Device Attribute constants */
#define daNone	0x00000000
#define daWriteable	0x00000001
#define daVirtual	0x00000002

/* Image Attribute constants */
#define iaNone	0x00000000
#define iaDisk	0x00000001 // Memory/File/Device
#define iaPartition	0x00000002 // Memory/File/Device
#define iaVolume	0x00000004 // Memory/File/Device
#define iaDrive	0x00000008 // Memory/File/Device
#define iaCDROM	0x00000010 // Memory/File/Device/Iso
#define iaDVD	0x00000020 // Memory/File/Device/Iso
#define iaFlat	0x00000040 // Bochs
#define iaSparse	0x00000080 // Bochs
#define iaGrowing	0x00000100 // Bochs
#define iaFixed	0x00000200 // Vpc/Vbox/Vmware
#define iaDynamic	0x00000400 // Vpc/Vbox/Vmware
#define iaSplit	0x00000800 // Vpc/Vmware/WIM/Ghost/Portlock/Powerquest
#define iaUndoable	0x00001000 // Vpc/Vbox/Vmware

#define iaReadable	0x00010000 // All
#define iaWriteable	0x00020000 // All
#define iaEraseable	0x00040000 // All

/* Catalog Attribute constants */
#define caNone	0x00000000
#define caDefault	0x00000001 // Initial/Default Entry
#define caBootable	0x00000002 // Boot Indicator
#define caNoEmulation	0x00000004 // No Emulation
#define caFloppy12M	0x00000008 // 1.2M
#define caFloppy144M	0x00000010 // 1.44M
#define caFloppy288M	0x00000020 // 2.88M
#define caHardDisk	0x00000040 // Hard Disk

/* Misc constants */
#define NAME_HASH_SIZE	8 // Used for Internal Name Hash Generation only

/* Partition Ids */
#define MAX_PARTITION_ID	255
#define pidUnused	0 // Empty
#define pidFAT12	1
#define pidXENIXROOT	2
#define pidXENIXUSR	3
#define pidFAT16	4 // under 32M
#define pidExtended	5
#define pidFAT16HUGE	6 // over 32M
#define pidHPFSNTFS	7
#define pidAIXOS2	8
#define pidAIX	9
#define pidOS2BOOT	10
#define pidFAT32	11
#define pidFAT32LBA	12
#define pidUnknown013	13
#define pidFAT16LBA	14
#define pidExtLBA	15
#define pidOPUS	16
#define pidHIDDEN12	17
#define pidCompaqDiag	18
#define pidUnknown019	19
#define pidHIDDEN16	20
#define pidUnknown021	21
#define pidHIDDEN16HUGE	22 // ??????
#define pidHIDDENHPFS	23
#define pidASTSWAP	24
#define pidWillowtech	25
#define pidUnknown026	26
#define pidHIDDEN32	27
#define pidHIDDEN32LBA	28
#define pidUnknown029	29
#define pidHIDDEN16LBA	30
#define pidUnknown031	31
#define pidWillowsoft	32
#define pidOxygen	33
#define pidOxygenExtended	34
#define pidReserved035	35
#define pidNECMSDOS	36
#define pidUnknown037	37
#define pidUnknown038	38
#define pidUnknown039	39
#define pidUnknown040	40
#define pidUnknown041	41
#define pidUnknown042	42
#define pidUnknown043	43
#define pidUnknown044	44
#define pidUnknown045	45
#define pidUnknown046	46
#define pidUnknown047	47
#define pidUnknown048	48
#define pidReserved049	49
#define pidAlienNOS	50
#define pidReserved051	51
#define pidReserved052	52
#define pidOS2JFS	53
#define pidReserved054	54
#define pidUnknown055	55
#define pidTheos057	56
#define pidPlan9	57
#define pidTheos058	58
#define pidTheos059	59
#define pidPowerQuest	60
#define pidHiddenNetware	61
#define pidUnknown062	62
#define pidUnknown063	63
#define pidVENIX286	64
#define pidPersonalRISC	65
#define pidSFS	66
#define pidPTSDOS	67
#define pidGoBack	68
#define pidEUMEL069	69
#define pidEUMEL070	70
#define pidEUMEL071	71
#define pidEUMEL072	72
#define pidUnknown073	73
#define pidAdaOS	74
#define pidUnknown075	75
#define pidOberon	76
#define pidQNX4077	77
#define pidQNX4078	78
#define pidQNX4079	79
#define pidOnTrack080	80
#define pidNOVELL081	81
#define pidCPM	82
#define pidOnTrack083	83
#define pidOnTrack084	84
#define pidEZDrive	85
#define pidGoldenBow	86
#define pidUnknown087	87
#define pidUnknown088	88
#define pidUnknown089	89
#define pidUnknown090	90
#define pidUnknown091	91
#define pidPriamEdisk	92
#define pidUnknown093	93
#define pidUnknown094	94
#define pidUnknown095	95
#define pidUnknown096	96
#define pidSpeedStor097	97
#define pidUnknown098	98
#define pidSysV	99
#define pidNetware286	100
#define pidNWFS	101 // Traditional / Netware 6 Master
#define pidUnknown102	102
#define pidNovell103	103
#define pidNovell104	104
#define pidNSS	105 // NSS / Netware 6
#define pidUnknown106	106
#define pidUnknown107	107
#define pidUnknown108	108
#define pidUnknown109	109
#define pidUnknown110	110
#define pidUnknown111	111
#define pidDiskSecure	112
#define pidUnknown113	113
#define pidUnknown114	114
#define pidReserved115	115
#define pidReserved116	116
#define pidPCIX	117
#define pidReserved118	118
#define pidUnknown119	119
#define pidUnknown120	120
#define pidUnknown121	121
#define pidUnknown122	122
#define pidUnknown123	123
#define pidUnknown124	124
#define pidUnknown125	125
#define pidUnknown126	126
#define pidUnknown127	127
#define pidMinix	128
#define pidLinuxMinix	129
#define pidLinuxSwap	130
#define pidLinuxNative	131
#define pidHIDDENC	132
#define pidLinuxExtended	133
#define pidFAT16Stripe	134
#define pidNTFSStripe	135
#define pidUnknown136	136
#define pidUnknown137	137
#define pidUnknown138	138
#define pidUnknown139	139
#define pidUnknown140	140
#define pidUnknown141	141
#define pidUnknown142	142
#define pidUnknown143	143
#define pidUnknown144	144
#define pidUnknown145	145
#define pidUnknown146	146
#define pidAmoeba	147
#define pidAmoebaBBT	148
#define pidUnknown149	149
#define pidUnknown150	150
#define pidUnknown151	151
#define pidUnknown152	152
#define pidUnknown153	153
#define pidUnknown154	154
#define pidUnknown155	155
#define pidUnknown156	156
#define pidUnknown157	157
#define pidUnknown158	158
#define pidUnknown159	159
#define pidPhoenixPM	160
#define pidReserved161	161
#define pidUnknown162	162
#define pidReserved163	163
#define pidReserved164	164
#define pidFreeBSD	165
#define pidOpenBSD	166
#define pidNeXTStep	167
#define pidUnknown168	168
#define pidUnknown169	169
#define pidUnknown170	170
#define pidDarwinBoot	171
#define pidUnknown172	172
#define pidUnknown173	173
#define pidUnknown174	174
#define pidUnknown175	175
#define pidUnknown176	176
#define pidUnknown177	177
#define pidUnknown178	178
#define pidUnknown179	179
#define pidReserved180	180
#define pidUnknown181	181
#define pidFAT16MirrorA	182
#define pidNTFSMirrorA	183
#define pidBSDIswap	184
#define pidUnknown185	185
#define pidUnknown186	186
#define pidUnknown187	187
#define pidUnknown188	188
#define pidUnknown189	189
#define pidUnknown190	190
#define pidUnknown191	191
#define pidUnknown192	192
#define pidDRDOSFAT12	193
#define pidUnknown194	194
#define pidUnknown195	195
#define pidDRDOSFAT16	196
#define pidUnknown197	197
#define pidFAT16MirrorB	198
#define pidNTFSMirrorB	199
#define pidUnknown200	200
#define pidUnknown201	201
#define pidUnknown202	202
#define pidUnknown203	203
#define pidUnknown204	204
#define pidUnknown205	205
#define pidUnknown206	206
#define pidUnknown207	207
#define pidUnknown208	208
#define pidUnknown209	209
#define pidTinyEFAT	210
#define pidEFAT	211
#define pidSecuredEFAT	212
#define pidOpticalEFAT	213
#define pidUnknown214	214
#define pidUnknown215	215
#define pidCPM86	216
#define pidUnknown217	217
#define pidUnknown218	218
#define pidConcurrentCPM	219
#define pidUnknown220	220
#define pidUnknown221	221
#define pidUnknown222	222
#define pidUnknown223	223
#define pidUnknown224	224
#define pidSpeedStorFAT12	225
#define pidUnknown226	226
#define pidUnknown227	227
#define pidSpeedStorFAT16	228
#define pidReserved229	229
#define pidReserved230	230
#define pidUnknown231	231
#define pidUnknown232	232
#define pidUnknown233	233
#define pidUnknown234	234
#define pidBeOSBFS1	235
#define pidUnknown236	236
#define pidUnknown237	237
#define pidUnknown238	238
#define pidUnknown239	239
#define pidLinuxRISC	240
#define pidStorageDimension	241
#define pidDOS33Secondary	242
#define pidSpeedStor243	243
#define pidSpeedStor244	244
#define pidPrologue	245
#define pidSpeedStor246	246
#define pidOSGEFAT	247
#define pidUnknown248	248
#define pidUnknown249	249
#define pidBochsX86	250
#define pidVMware	251
#define pidVMwareSwap	252
#define pidLinuxRAID	253
#define pidLANstep	254
#define pidXenixBBT	255

/* Device descriptions */
#define FILESYS_ATA_DEVICE_DESCRIPTION	"ATA Storage Device"
#define FILESYS_ATAPI_DEVICE_DESCRIPTION	"ATAPI Storage Device"
#define FILESYS_SCSI_DEVICE_DESCRIPTION	"SCSI Storage Device"
#define FILESYS_USB_DEVICE_DESCRIPTION	"USB Storage Device"
#define FILESYS_MMC_DEVICE_DESCRIPTION	"MMC/SD Storage Device"

/* Controller descriptions */
#define FILESYS_ATA_CONTROLLER_DESCRIPTION	"ATA Storage Controller"
#define FILESYS_ATAPI_CONTROLLER_DESCRIPTION	"ATAPI Storage Controller"
#define FILESYS_SCSI_CONTROLLER_DESCRIPTION	"SCSI Storage Controller"
#define FILESYS_USB_CONTROLLER_DESCRIPTION	"USB Storage Controller"
#define FILESYS_MMC_CONTROLLER_DESCRIPTION	"MMC/SD Storage Controller"

/* ============================================================================== */
/* FileSystem specific types */
typedef struct _STORAGE_DEVICE_EVENT STORAGE_DEVICE_EVENT;
struct _STORAGE_DEVICE_EVENT
{
	TIMER_HANDLE timer;
	STORAGE_DEVICE *device;
};

typedef enum _MEDIA_TYPE
{
 mtUNKNOWN,
 mtINVALID,
 mtFLOPPY,
 mtFIXED,
 mtREMOVABLE,
 mtCDROM,
 mtDVD,
 mtOTHER
} MEDIA_TYPE;

typedef enum _FLOPPY_TYPE
{
 ftUNKNOWN,
 ftINVALID,
 ft360K,
 ft12M,
 ft720K,
 ft144M,
 ft288M,
 ftATAPI
} FLOPPY_TYPE;

typedef enum _IMAGE_TYPE
{
 itUNKNOWN,
 itINVALID,
 itMEMORY,
 itFILE,
 itDEVICE,
 itISO,
 itBOCHS,
 itVMWARE,
 itVPC,
 itVBOX
} IMAGE_TYPE;

/* Cache types */
typedef enum _CACHE_STATE
{
 csCLEAN,
 csDIRTY
} CACHE_STATE;

typedef enum _CACHE_MODE
{
 cmNONE,
 cmREADONLY,
 cmREADWRITE
} CACHE_MODE;

typedef enum _CACHE_PAGE_TYPE
{
 ptNONE,
 ptDEVICE
} CACHE_PAGE_TYPE;

typedef enum _CACHE_PAGE_STATE
{
 psUNKNOWN,
 psEMPTY,
 psCLEAN,
 psDIRTY
} CACHE_PAGE_STATE;

typedef enum _CACHE_PAGE_CONTENT
{
 pcUNKNOWN,
 pcDATA,
 pcDIRECTORY,
 pcENTRY,
 pcSYSTEM
} CACHE_PAGE_CONTENT;

/* Cache Statistics */
typedef struct _CACHE_STATISTICS CACHE_STATISTICS;
struct _CACHE_STATISTICS
{
	// Information
	uint32_t pagesize;
	uint32_t pagecount;
	uint32_t cachesize;
	CACHE_MODE cachemode;
	CACHE_STATE cachestate;
	uint32_t flushtimeout;
	uint32_t discardtimeout;
	// Read / Write
	int64_t readcached;
	int64_t readdirect;
	int64_t writeback;
	int64_t writethrough;
	int64_t writedirect;
	// Hit / Miss
	int64_t hitcount;
	int64_t misscount;
	// Allocate Success / Failure
	int64_t failcount;
	int64_t successcount;
	// Page Flush / Discard
	int64_t flushcount;
	int64_t discardcount;
	int64_t unknowncount;
	// Page Times
	int64_t oldestclean;
	int64_t newestclean;
	int64_t oldestdirty;
	int64_t newestdirty;
};

/* Search types */
typedef struct _FILE_SEARCH_REC
{
	HANDLE findhandle;
	WIN32_FIND_DATA finddata;
} FILE_SEARCH_REC;

typedef struct _DISK_SEARCH_REC
{
	char name[MAX_PATH];
	MEDIA_TYPE mediatype;
	FLOPPY_TYPE floppytype;
	HANDLE findhandle;
	uint32_t context;
	BOOL verbose;
} DISK_SEARCH_REC;

typedef struct _PARTITION_SEARCH_REC
{
	char name[MAX_PATH];
	uint32_t index;
	HANDLE findhandle;
	uint32_t context;
	BOOL verbose;
} PARTITION_SEARCH_REC;

typedef struct _VOLUME_SEARCH_REC
{
	char name[MAX_PATH];
	uint32_t attributes;
	char volumelabel[64];
	char volumeguid[64];
	uint32_t volumeserial;
	DRIVE_TYPE drivetype;
	FILE_SYS_TYPE filesystype;
	HANDLE findhandle;
	uint32_t context;
	BOOL verbose;
} VOLUME_SEARCH_REC;

typedef struct _DRIVE_SEARCH_REC
{
	char name[MAX_PATH];
	uint32_t attributes;
	char volumelabel[64];
	char volumeguid[64];
	uint32_t volumeserial;
	DRIVE_TYPE drivetype;
	FILE_SYS_TYPE filesystype;
	HANDLE findhandle;
	uint32_t context;
	BOOL verbose;
} DRIVE_SEARCH_REC;

typedef struct _IMAGE_SEARCH_REC
{
	char name[MAX_PATH];
	int imageno;
	IMAGE_TYPE imagetype;
	MEDIA_TYPE mediatype;
	FLOPPY_TYPE floppytype;
	uint32_t attributes;
	uint16_t sectorsize;
	int64_t sectorcount;
	uint32_t cylinders;
	uint32_t heads;
	uint32_t sectors;
	uint8_t partitionid;
	HANDLE findhandle;
	uint32_t context;
	BOOL verbose;
} IMAGE_SEARCH_REC;

typedef struct _CATALOG_SEARCH_REC
{
	char name[MAX_PATH];
    char path[MAX_PATH];
	uint32_t catalogno;
	MEDIA_TYPE mediatype;
	FLOPPY_TYPE floppytype;
	uint32_t attributes;
	uint16_t sectorsize;
	int64_t sectorcount;
	HANDLE findhandle;
	uint32_t context;
} CATALOG_SEARCH_REC;

typedef struct _MOUNT_SEARCH_REC
{
	char name[MAX_PATH];
	HANDLE findhandle;
	uint32_t context;
} MOUNT_SEARCH_REC;

typedef struct _JUNCTION_SEARCH_REC
{
	char name[MAX_PATH];
	HANDLE findhandle;
	uint32_t context;
} JUNCTION_SEARCH_REC;

typedef struct _STREAM_SEARCH_REC
{
	HANDLE findhandle;
	void *context;
	WIN32_FIND_STREAM_DATA finddata;
} STREAM_SEARCH_REC;

typedef struct _LINK_SEARCH_REC
{
	char name[MAX_PATH];
	HANDLE findhandle;
	void *context;
} LINK_SEARCH_REC;

/* FAT12/FAT16 BIOS Parameter Block */
typedef struct _BIOS_PB
{
	uint16_t bytespersector; // 512,1024,2048,4096 - Usually 512
	uint8_t sectorspercluster; // 1,2,4,8,16,32,64,128
	uint16_t reservedsectors; // FAT12/16 - Usually 1, FAT32 - Usually 32
	uint8_t numberoffats; // Usually 2
	uint16_t rootentrycount; // FAT32 always 0, FAT16 usually 512
	// RootEntryCount * 32 must be even multiple of BytesPerSector
	uint16_t totalsectors16; // Total Sectors on the drive or 0 if TotalSectors32 used
	uint8_t mediaid; // F8 for Fixed media, F0 usually for Removable media
	uint16_t sectorsperfat16; // FAT32 always 0, Number of Sectors per FAT
	uint16_t sectorspertrack; // Sectors Per Track for Int13
	uint16_t numberofheads; // Number of Header for Int13 eg 1.44MB = 2
	uint32_t hiddensectors; // Number of Hidden Sectors preceeding Partition
	// Only valid on Partitioned media
	uint32_t totalsectors32; // Total Sectors on the drive or 0 if TotalSectors16 used
} PACKED BIOS_PB;

/* FAT32 BIOS Parameter Block */
typedef struct _EXT_BIOS_PB
{
	uint16_t bytespersector; // 512,1024,2048,4096 - Usually 512
	uint8_t sectorspercluster; // 1,2,4,8,16,32,64,128
	uint16_t reservedsectors; // FAT12/16 - Usually 1, FAT32 - Usually 32
	uint8_t numberoffats; // Usually 2
	uint16_t rootentrycount; // FAT32 always 0, FAT16 usually 512
	// RootEntryCount * 32 must be even multiple of BytesPerSector
	uint16_t totalsectors16; // Total Sectors on the drive or 0 if TotalSectors32 used
	uint8_t mediaid; // F8 for Fixed media, F0 usually for Removable media
	uint16_t sectorsperfat16; // FAT32 always 0, Number of Sectors per FAT
	uint16_t sectorspertrack; // Sectors Per Track for Int13
	uint16_t numberofheads; // Number of Header for Int13 eg 1.44MB = 2
	uint32_t hiddensectors; // Number of Hidden Sectors preceeding Partition
	// Only valid on Partitioned media
	uint32_t totalsectors32; // Total Sectors on the drive or 0 if TotalSectors16 used
	uint32_t sectorsperfat32; // Number of Sectors per FAT
	uint16_t extendedflags; // Bits 0-3  -- Zero-based number of active FAT. Only valid if mirroring
	//              is disabled.
	// Bits 4-6  -- Reserved.
	// Bit 7     -- 0 means the FAT is mirrored at runtime into all FATs.
	// it is the one referenced}
	//              in bits 0-3.
	// Bits 8-15 -- Reserved.
	uint16_t filesysversion; // FAT32 Version (Current 0:0)
	uint32_t rootcluster; // Usually Cluster 2
	uint16_t filesysinfosector; // Usually 1
	uint16_t backupbootsector; // Usually 6
	uint8_t reserved[12]; // Always 0
} PACKED EXT_BIOS_PB;

/* NTFS BIOS Parameter Block */
typedef struct _NTFS_BIOS_PB
{
	uint16_t bytespersector; // 512,1024,2048,4096 - Usually 512
	uint8_t sectorspercluster; // 1,2,4,8,16,32,64,128 - Usually 8
	uint16_t reservedsectors; // Must always be 0 on NTFS
	uint8_t reserved1[3]; // Must always be 0 on NTFS
	uint16_t reserved2; // Must always be 0 on NTFS
	uint8_t mediaid; // F8 for Fixed media, F0 usually for Removable media
	uint16_t reserved3; // Must always be 0 on NTFS
	uint16_t sectorspertrack; // Sectors Per Track for Int13
	uint16_t numberofheads; // Number of Header for Int13 eg 1.44MB = 2
	uint32_t hiddensectors; // Number of Hidden Sectors preceeding Partition
	uint32_t reserved4; // Must always be 0 on NTFS
	uint32_t reserved5; // Not used by NTFS - Usually 80008000
	int64_t totalsectors; // Total Sectors on the drive
	int64_t mftcluster; // Start Cluster of $MFT
	int64_t mftmirror; // Start Cluster of $MFTMirr
	int32_t clustersperfile; // Clusters Per File Record (Can be negative) (F6 = 1024 - See Notes)
	int32_t clustersperindex; // Clusters Per Index Record (Can be negative) (F6 = 1024 - See Notes)
	int64_t volumeserial; // Volume Serial Number
	uint32_t checksum; // Checksum
} PACKED NTFS_BIOS_PB;

/* Partition types */
typedef struct _PARTITION_ENTRY
{
	uint8_t bootindicator; // 80 for active partition
	uint8_t starthead; // Either Bits 0-3 only or Bits 0-7 depending on BIOS
	uint8_t startsector; // Bits 0-5 = Sector, Bits 6-7 = Bits 8-9 of Cylinder
	uint8_t startcylinder; // Bits 0-7 Only, Bits 8-9 in Sector
	uint8_t typeindicator; // See Table in Interrupt List and Below
	uint8_t endhead; // Either Bits 0-3 only or Bits 0-7 depending on BIOS
	uint8_t endsector; // Bits 0-5 = Sector, Bits 6-7 = Bits 8-9 of Cylinder
	uint8_t endcylinder; // Bits 0-7 Only, Bits 8-9 in Sector
	uint32_t sectoroffset; // Offset in sectors from current position to Start of Partition
	uint32_t sectorcount; // Size in Sectors of the Partition
} PACKED PARTITION_ENTRY;

typedef struct _PARTITION_TABLE
{
	PARTITION_ENTRY partitionentry[MAX_PARTITION_COUNT];
} PACKED PARTITION_TABLE;

typedef uint8_t MASTER_BOOT_CODE[446];

typedef struct _MASTER_BOOT_RECORD
{
	MASTER_BOOT_CODE bootcode;
	PARTITION_TABLE partitiontable;
	uint16_t signature; // Magic Number $AA55
} PACKED MASTER_BOOT_RECORD;

typedef uint8_t EXT_MASTER_BOOT_CODE[440];

typedef struct _EXT_MASTER_BOOT_RECORD
{
	EXT_MASTER_BOOT_CODE bootcode;
	uint32_t disksignature;
	uint16_t reserved1;
	PARTITION_TABLE partitiontable;
	uint16_t signature; // Magic Number $AA55
} PACKED EXT_MASTER_BOOT_RECORD;

typedef struct _PARTITION_RECORD
{
	uint8_t dummy[446];
	PARTITION_TABLE partitiontable; // Only first 2 ever used
	uint16_t signature; // Magic Number $AA55
} PACKED PARTITION_RECORD;

/* Sector types */
typedef uint8_t DISK_SECTOR[512];

typedef uint8_t BOOT_SECTOR_JUMP[3];
typedef uint8_t BOOT_SECTOR_CODE[448];

typedef struct _BOOT_SECTOR
{
	BOOT_SECTOR_JUMP bootjump; // JMP - EBh,??h,90h or E9h,??h,??h
	char oemname[8]; // MSWIN4.0/MSWIN4.1/MSDOS5.0
	BIOS_PB bpb; // See Above
	uint8_t drivenumber; // BIOS Int13 Drive No 00h, 80h, FFh etc
	uint8_t reserved1; // Always 00h
	uint8_t bootsignature; // Always 29h
	uint32_t volumeserial; // Serial No (Date/Time when Formatted)
	char volumename[11]; // Volume Label or "NO NAME"
	char systemname[8]; // System Type FAT12, FAT16, FAT32 etc
	BOOT_SECTOR_CODE bootcode; // Executable Code
	uint16_t signature; // Magic Number $AA55
} PACKED BOOT_SECTOR;

typedef uint8_t EXT_BOOT_SECTOR_JUMP[3];
typedef uint8_t EXT_BOOT_SECTOR_CODE[420];

typedef struct _EXT_BOOT_SECTOR
{
	EXT_BOOT_SECTOR_JUMP bootjump; // JMP - EBh,??h,90h or E9h,??h,??h
	char oemname[8]; // MSWIN4.1
	EXT_BIOS_PB bpb; // See Above
	uint8_t drivenumber; // BIOS Int13 Drive No 00h, 80h, FFh etc
	uint8_t reserved1; // Always 00h
	uint8_t bootsignature; // Always 29h
	uint32_t volumeserial; // Serial No (Date/Time when Formatted)
	char volumename[11]; // Volume Label or "NO NAME"
	char systemname[8]; // System Type FAT12, FAT16, FAT32 etc
	EXT_BOOT_SECTOR_CODE bootcode; // Executable Code
	uint16_t signature; // Magic Number $AA55
} PACKED EXT_BOOT_SECTOR;

typedef uint8_t NTFS_BOOT_SECTOR_JUMP[3];
typedef uint8_t NTFS_BOOT_SECTOR_CODE[426];

typedef struct _NTFS_BOOT_SECTOR
{
	NTFS_BOOT_SECTOR_JUMP bootjump; // JMP - EBh,??h,90h
	char oemname[8]; // Always NTFS
	NTFS_BIOS_PB bpb; // See Above (73 Bytes BPB and ExtBPB)
	NTFS_BOOT_SECTOR_CODE bootcode; // Executable Code
	uint16_t signature; // Magic Number $AA55
} PACKED NTFS_BOOT_SECTOR;

typedef struct _EXTFS_BOOT_SECTOR
{
	// To Do
} PACKED EXTFS_BOOT_SECTOR;

/* ============================================================================== */
/* Initialization Functions */
uint32_t STDCALL file_sys_start(void);
uint32_t STDCALL file_sys_stop(void);

BOOL STDCALL file_sys_start_completed(void);

void STDCALL file_sys_async_start(void *data);

/* ============================================================================== */
/* FileSystem Functions (Ultibo) */
/* Drive Functions */
uint8_t STDCALL GetPathDrive(char *path);
DRIVE_TYPE STDCALL GetDriveType(uint8_t drive);
void STDCALL GetDriveData(uint8_t drive, DRIVE_DATA *data);
uint32_t STDCALL GetDriveAttr(uint8_t drive);
uint32_t STDCALL GetDriveLabel(uint8_t drive, char *label, uint32_t len);
BOOL STDCALL SetDriveLabel(uint8_t drive, char *label);
uint32_t STDCALL GetDriveSerial(uint8_t drive);
BOOL STDCALL SetDriveSerial(uint8_t drive, uint32_t serial);
BOOL STDCALL IsDriveValid(uint8_t drive);
uint32_t STDCALL GetValidDrives(void);
uint32_t STDCALL GetValidDriveNames(char *names, uint32_t len);
uint32_t STDCALL GetDriveFreeSpace(uint8_t drive);
int64_t STDCALL GetDriveFreeSpaceEx(uint8_t drive);
uint32_t STDCALL GetDriveTotalSpace(uint8_t drive);
int64_t STDCALL GetDriveTotalSpaceEx(uint8_t drive);

BOOL STDCALL GetDriveInformation(char *path, uint32_t *clustersize, int64_t *totalclustercount, int64_t *freeclustercount);

uint8_t STDCALL GetCurrentDrive(void);
BOOL STDCALL SetCurrentDrive(char *drive);

/* File Functions */
HANDLE STDCALL FileOpen(char *filename, int mode);
HANDLE STDCALL FileCreate(char *filename);
BOOL STDCALL DeleteFile(char *filename);
void STDCALL FileClose(int handle);
BOOL STDCALL RenameFile(char *oldname, char *newname);
int32_t STDCALL FileSeek(HANDLE handle, int32_t offset, int32_t origin);
BOOL STDCALL FileFlush(int handle);
BOOL STDCALL FileTruncate(int handle);
BOOL STDCALL SetEndOfFile(HANDLE handle);

BOOL STDCALL EndOfFile(int handle);
int32_t STDCALL FilePos(HANDLE handle);
int32_t STDCALL FileSize(HANDLE handle);

int STDCALL FileAge(char *filename);
BOOL STDCALL FileExists(char *filename);
int STDCALL FileGetAttr(char *filename);
int STDCALL FileGetDate(int handle);
int STDCALL FileSetAttr(char *filename, int attr);
int STDCALL FileSetDate(int handle, int age);

int32_t STDCALL FileRead(HANDLE handle, void *buffer, int32_t count);
int32_t STDCALL FileWrite(HANDLE handle, void *buffer, int32_t count);

/* Directory Functions */
BOOL STDCALL CreateDir(char *dirname);
BOOL STDCALL RemoveDir(char *dirname);
BOOL STDCALL RenameDir(char *oldname, char *newname);
uint32_t STDCALL GetCurrentDir(char *dirname, uint32_t len);
BOOL STDCALL SetCurrentDir(char *dirname);
BOOL STDCALL DirectoryExists(char *dirname);
void STDCALL ForceDirectories(char *dirname);
void STDCALL DeleteTree(char *dirname);

/* Search Functions */

/* Additional Functions */
BOOL STDCALL FileCopy(char *sourcefile, char *destfile, BOOL failifexists);
BOOL STDCALL FileCopyEx(char *sourcefile, char *destfile, BOOL failifexists, BOOL usesourcedate, int destdate, BOOL usesourceattr, int destattr);

uint32_t STDCALL GetShortName(char *filename, char *shortname, uint32_t len);
uint32_t STDCALL GetLongName(char *filename, char *longname, uint32_t len);
uint32_t STDCALL GetTrueName(char *filename, char *truename, uint32_t len);

/* Extended Functions */
int64_t STDCALL FileSeekEx(HANDLE handle, int64_t offset, int32_t origin);

BOOL STDCALL EndOfFileEx(int handle);
int64_t STDCALL FilePosEx(HANDLE handle);
int64_t STDCALL FileSizeEx(HANDLE handle);

FILETIME STDCALL FileAgeEx(char *filename);

int STDCALL FileGetAttrEx(int handle);

FILETIME STDCALL FileGetDateEx(int handle);
int STDCALL FileSetDateEx(int handle, FILETIME age);

BOOL STDCALL GetFileTime(HANDLE handle, FILETIME *createtime, FILETIME *accesstime, FILETIME *writetime);
BOOL STDCALL SetFileTime(HANDLE handle, FILETIME *createtime, FILETIME *accesstime, FILETIME *writetime);

int STDCALL FindFirstEx(char *path, FILE_SEARCH_REC *searchrec);
int STDCALL FindNextEx(FILE_SEARCH_REC *searchrec);
void STDCALL FindCloseEx(FILE_SEARCH_REC *searchrec);

/* ============================================================================== */
/* FileSystem Functions (Win32 Compatibility) */
/* Drive Functions */
BOOL STDCALL DefineDosDevice(uint32_t dwflags, char *lpdevicename, char *lptargetpath);
UINT STDCALL GetDiskType(char *lprootpathname); // GetDriveType - Already defined above
BOOL STDCALL GetDiskFreeSpace(char *lprootpathname, uint32_t *lpsectorspercluster, uint32_t *lpbytespersector, uint32_t *lpnumberoffreeclusters, uint32_t *lptotalnumberofclusters);
BOOL STDCALL GetDiskFreeSpaceEx(char *lpdirectoryname, ULARGE_INTEGER *lpfreebytesavailabletocaller, ULARGE_INTEGER *lptotalnumberofbytes, ULARGE_INTEGER *lptotalnumberoffreebytes);
uint32_t STDCALL GetLogicalDrives(void);
uint32_t STDCALL GetLogicalDriveStrings(uint32_t nbufferlength, char *lpbuffer);
BOOL STDCALL GetVolumeInformation(char *lprootpathname, char *lpvolumenamebuffer, uint32_t nvolumenamesize, DWORD *lpvolumeserialnumber, uint32_t *lpmaximumcomponentlength, uint32_t *lpfilesystemflags, char *lpfilesystemnamebuffer, uint32_t nfilesystemnamesize);
uint32_t STDCALL QueryDosDevice(char *lpdevicename, char *lptargetpath, uint32_t ucchmax);
BOOL STDCALL SetVolumeLabel(char *lprootpathname, char *lpvolumename);

/* File Functions */
BOOL STDCALL AreFileApisANSI(void);
BOOL STDCALL CloseHandle(HANDLE hobject);
BOOL STDCALL CopyFile(char *lpexistingfilename, char *lpnewfilename, BOOL bfailifexists);
HANDLE STDCALL CreateFile(char *lpfilename, uint32_t dwdesiredaccess, uint32_t dwsharemode, SECURITY_ATTRIBUTES *lpsecurityattributes, uint32_t dwcreationdisposition, uint32_t dwflagsandattributes, HANDLE htemplatefile);
BOOL STDCALL FindCloseFile(HANDLE hfindfile);
HANDLE STDCALL FindFirstFile(char *lpfilename, WIN32_FIND_DATAA *lpfindfiledata);
BOOL STDCALL FindNextFile(HANDLE hfindfile, WIN32_FIND_DATAA *lpfindfiledata);
BOOL STDCALL FlushFileBuffers(HANDLE hfile);
uint32_t STDCALL GetFileAttributes(char *lpfilename);
BOOL STDCALL GetFileInformationByHandle(HANDLE hfile, BY_HANDLE_FILE_INFORMATION *lpfileinformation);
uint32_t STDCALL GetFileSize(HANDLE hfile, DWORD *lpfilesizehigh);
uint32_t STDCALL GetFullPathName(char *lpfilename, uint32_t nbufferlength, char *lpbuffer, char *lpfilepart);
uint32_t STDCALL GetShortPathName(char *lpszlongpath, char *lpszshortpath, uint32_t cchbuffer);
BOOL STDCALL MoveFile(char *lpexistingfilename, char *lpnewfilename);
BOOL STDCALL ReadFile(HANDLE hfile, void *lpbuffer, uint32_t nnumberofbytestoread, DWORD *lpnumberofbytesread, OVERLAPPED *lpoverlapped);
void STDCALL SetFileApisToANSI(void);
void STDCALL SetFileApisToOEM(void);
BOOL STDCALL SetFileAttributes(char *lpfilename, uint32_t dwfileattributes);
uint32_t STDCALL SetFilePointer(HANDLE hfile, long ldistancetomove, long *lpdistancetomovehigh, uint32_t dwmovemethod);
BOOL STDCALL SetFilePointerEx(HANDLE hfile, LARGE_INTEGER lidistancetomove, LARGE_INTEGER *lpnewfilepointer, uint32_t dwmovemethod);
BOOL STDCALL WriteFile(HANDLE hfile, void *lpbuffer, uint32_t nnumberofbytestowrite, DWORD *lpnumberofbyteswritten, OVERLAPPED *lpoverlapped);
uint32_t STDCALL GetLongPathName(char *lpszshortpath, char *lpszlongpath, uint32_t cchbuffer);

BOOL STDCALL SetFileShortName(HANDLE hfile, char *lpshortname);
BOOL STDCALL CreateHardLink(char *lpfilename, char *lpexistingfilename, SECURITY_ATTRIBUTES *lpsecurityattributes);
BOOL STDCALL CreateSymbolicLink(char *lpsymlinkfilename, char *lptargetfilename, uint32_t dwflags);

/* Directory Functions */
BOOL STDCALL CreateDirectory(char *lppathname, SECURITY_ATTRIBUTES *lpsecurityattributes);
uint32_t STDCALL GetCurrentDirectory(uint32_t nbufferlength, char *lpbuffer);
BOOL STDCALL RemoveDirectory(char *lppathname);
BOOL STDCALL SetCurrentDirectory(char *lppathname);

/* ============================================================================== */
/* FileSystem Helper Functions */
BOOL STDCALL file_sys_redirect_input(HANDLE handle);
BOOL STDCALL file_sys_redirect_output(HANDLE handle);

int STDCALL compare_partitions(void *partition1, void *partition2);

uint32_t STDCALL disk_media_type_to_string(MEDIA_TYPE _type, char *string, uint32_t len);
uint32_t STDCALL floppy_type_to_string(FLOPPY_TYPE _type, char *string, uint32_t len);
uint32_t STDCALL image_type_to_string(IMAGE_TYPE _type, char *string, uint32_t len);

uint32_t STDCALL drive_type_to_string(DRIVE_TYPE _type, char *string, uint32_t len);

uint32_t STDCALL file_sys_type_to_string(FILE_SYS_TYPE _type, char *string, uint32_t len);
FILE_SYS_TYPE STDCALL string_to_file_sys_type(char *filesystype);

uint32_t STDCALL partition_id_to_string(uint8_t id, char *string, uint32_t len);
uint8_t STDCALL string_to_partition_id(char *partitionid);

uint32_t STDCALL cache_mode_to_string(CACHE_MODE cachemode, char *string, uint32_t len);
uint32_t STDCALL cache_state_to_string(CACHE_STATE cachestate, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_FILESYSTEM_H