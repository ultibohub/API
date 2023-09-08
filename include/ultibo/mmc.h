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
#ifndef _ULTIBO_MMC_H
#define _ULTIBO_MMC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"
#include "ultibo/storage.h"
#include "ultibo/dma.h"

/* ============================================================================== */
/* MMC specific constants */
#define MMC_NAME_PREFIX	"MMC" // Name prefix for MMC Devices

#define MMC_DEVICE_DESCRIPTION	"MMC/SD Device" // Description of MMC/SD device
#define MMC_STORAGE_DESCRIPTION	"MMC/SD Storage Device" // Description of MMC/SD storage device

#define MMC_STATUS_TIMER_INTERVAL	1000

#define MMC_DEFAULT_BLOCKSIZE	512
#define MMC_DEFAULT_BLOCKSHIFT	9

/* MMC Device Types */
#define MMC_TYPE_NONE	0
#define MMC_TYPE_MMC	1 // An MMC specification card
#define MMC_TYPE_SD	2 // An SD specification card
#define MMC_TYPE_SDIO	3 // An SDIO specification card
#define MMC_TYPE_SD_COMBO	4 // An SD/SDIO combination card

#define MMC_TYPE_MAX	4

/* MMC Device States */
#define MMC_STATE_EJECTED	0
#define MMC_STATE_INSERTED	1

#define MMC_STATE_MAX	1

/* MMC Device Flags */
#define MMC_FLAG_NONE	0x00000000
#define MMC_FLAG_CARD_PRESENT	0x00000001 // Card is present
#define MMC_FLAG_WRITE_PROTECT	0x00000002 // Card is write protected
#define MMC_FLAG_HIGH_CAPACITY	0x00000004 // High Capacity (SDHC)
#define MMC_FLAG_EXT_CAPACITY	0x00000008 // Extended Capacity (SDXC)
#define MMC_FLAG_UHS_I	0x00000010 // Ultra High Speed (UHS-I)
#define MMC_FLAG_UHS_II	0x00000020 // Ultra High Speed (UHS-II)
#define MMC_FLAG_BLOCK_ADDRESSED	0x00000040 // Block Addressed (SDHC/SDXC and others)
#define MMC_FLAG_AUTO_BLOCK_COUNT	0x00000080 // Controller supports Auto CMD23 (Set Block Count)
#define MMC_FLAG_AUTO_COMMAND_STOP	0x00000100 // Controller supports Auto CMD12 (Stop Transmission)
#define MMC_FLAG_DDR_MODE	0x00000200 // Device supports DDR mode
#define MMC_FLAG_NON_REMOVABLE	0x00000400 // Device is non removable, only check for presence once
#define MMC_FLAG_SET_BLOCK_COUNT	0x00000800 // Device supports CMD23 (Set Block Count)

/* MMC/SD/SDIO Status Codes */
#define MMC_STATUS_SUCCESS	0 // Function successful
#define MMC_STATUS_TIMEOUT	1 // The operation timed out
#define MMC_STATUS_NO_MEDIA	2 // No media present in device
#define MMC_STATUS_HARDWARE_ERROR	3 // Hardware error of some form occurred
#define MMC_STATUS_INVALID_DATA	4 // Invalid data was received
#define MMC_STATUS_INVALID_PARAMETER	5 // An invalid parameter was passed to the function
#define MMC_STATUS_INVALID_SEQUENCE	6 // Invalid sequence encountered
#define MMC_STATUS_OUT_OF_MEMORY	7 // No memory available for operation
#define MMC_STATUS_UNSUPPORTED_REQUEST	8 // The request is unsupported
#define MMC_STATUS_NOT_PROCESSED	9 // The MMC transfer has not yet been processed
#define MMC_STATUS_OPERATION_FAILED	10 // The operation was not able to be completed
#define MMC_STATUS_DEVICE_DETACHED	11 // SDIO device was detached
#define MMC_STATUS_DEVICE_UNSUPPORTED	12 // SDIO device is unsupported by the driver
#define MMC_STATUS_NOT_BOUND	13 // SDIO device is not bound to a driver
#define MMC_STATUS_ALREADY_BOUND	14 // SDIO device is already bound to a driver
#define MMC_STATUS_NOT_READY	15 // The device is not ready yet, retry again later

/* MMC/SD/SDIO Versions */
#define SDIO_VERSION_SDIO	0x00040000
#define SDIO_VERSION_1_00	(SDIO_VERSION_SDIO | $0100)
#define SDIO_VERSION_1_10	(SDIO_VERSION_SDIO | $010a)
#define SDIO_VERSION_1_20	(SDIO_VERSION_SDIO | $0114)
#define SDIO_VERSION_2_00	(SDIO_VERSION_SDIO | $0200)
#define SDIO_VERSION_3_00	(SDIO_VERSION_SDIO | $0300)

#define SD_VERSION_SD	0x00020000
#define SD_VERSION_1_0	(SD_VERSION_SD | $0100)
#define SD_VERSION_1_10	(SD_VERSION_SD | $010a)
#define SD_VERSION_2	(SD_VERSION_SD | $0200)
#define SD_VERSION_3	(SD_VERSION_SD | $0300)
#define SD_VERSION_4	(SD_VERSION_SD | $0400)

#define MMC_VERSION_MMC	0x00010000
#define MMC_VERSION_1_2	(MMC_VERSION_MMC | $0102)
#define MMC_VERSION_1_4	(MMC_VERSION_MMC | $0104)
#define MMC_VERSION_2_2	(MMC_VERSION_MMC | $0202)
#define MMC_VERSION_3	(MMC_VERSION_MMC | $0300)
#define MMC_VERSION_4	(MMC_VERSION_MMC | $0400)
#define MMC_VERSION_4_1	(MMC_VERSION_MMC | $0401)
#define MMC_VERSION_4_2	(MMC_VERSION_MMC | $0402)
#define MMC_VERSION_4_3	(MMC_VERSION_MMC | $0403)
#define MMC_VERSION_4_41	(MMC_VERSION_MMC | $0429)
#define MMC_VERSION_4_5	(MMC_VERSION_MMC | $0405)
#define MMC_VERSION_5_0	(MMC_VERSION_MMC | $0500)
#define MMC_VERSION_5_1	(MMC_VERSION_MMC | $0501)
#define MMC_VERSION_UNKNOWN	(MMC_VERSION_MMC)

/* MMC/SD Capabilities (From: /include/linux/mmc/host.h) */
#define MMC_CAP_4_BIT_DATA	(1 << 0) // Can the host do 4 bit transfers
#define MMC_CAP_MMC_HIGHSPEED	(1 << 1) // Can do MMC high-speed timing
#define MMC_CAP_SD_HIGHSPEED	(1 << 2) // Can do SD high-speed timing
#define MMC_CAP_SDIO_IRQ	(1 << 3) // Can signal pending SDIO IRQs
#define MMC_CAP_SPI	(1 << 4) // Talks only SPI protocols
#define MMC_CAP_NEEDS_POLL	(1 << 5) // Needs polling for card-detection
#define MMC_CAP_8_BIT_DATA	(1 << 6) // Can the host do 8 bit transfers
#define MMC_CAP_AGGRESSIVE_PM	(1 << 7) // Suspend = (e)MMC/SD at idle
#define MMC_CAP_NONREMOVABLE	(1 << 8) // Nonremovable eg. eMMC
#define MMC_CAP_WAIT_WHILE_BUSY	(1 << 9) // Waits while card is busy
#define MMC_CAP_3_3V_DDR	(1 << 11) // Host supports eMMC DDR 3.3V
#define MMC_CAP_1_8V_DDR	(1 << 12) // Host supports eMMC DDR 1.8V
#define MMC_CAP_1_2V_DDR	(1 << 13) // Host supports eMMC DDR 1.2V
#define MMC_CAP_DDR	(MMC_CAP_3_3V_DDR | MMC_CAP_1_8V_DDR | MMC_CAP_1_2V_DDR)
#define MMC_CAP_POWER_OFF_CARD	(1 << 14) // Can power off after boot
#define MMC_CAP_BUS_WIDTH_TEST	(1 << 15) // CMD14/CMD19 bus width ok
#define MMC_CAP_UHS_SDR12	(1 << 16) // Host supports UHS SDR12 mode
#define MMC_CAP_UHS_SDR25	(1 << 17) // Host supports UHS SDR25 mode
#define MMC_CAP_UHS_SDR50	(1 << 18) // Host supports UHS SDR50 mode
#define MMC_CAP_UHS_SDR104	(1 << 19) // Host supports UHS SDR104 mode
#define MMC_CAP_UHS_DDR50	(1 << 20) // Host supports UHS DDR50 mode
#define MMC_CAP_UHS	(MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_DDR50)
#define MMC_CAP_SYNC_RUNTIME_PM	(1 << 21) // Synced runtime PM suspends
#define MMC_CAP_NEED_RSP_BUSY	(1 << 22) // Commands with R1B can't use R1
#define MMC_CAP_DRIVER_TYPE_A	(1 << 23) // Host supports Driver Type A
#define MMC_CAP_DRIVER_TYPE_C	(1 << 24) // Host supports Driver Type C
#define MMC_CAP_DRIVER_TYPE_D	(1 << 25) // Host supports Driver Type D
#define MMC_CAP_DONE_COMPLETE	(1 << 27) // RW reqs can be completed within mmc_request_done()
#define MMC_CAP_CD_WAKE	(1 << 28) // Enable card detect wake
#define MMC_CAP_CMD_DURING_TFR	(1 << 29) // Commands during data transfer
#define MMC_CAP_CMD23	(1 << 30) // CMD23 supported
#define MMC_CAP_HW_RESET	(1 << 31) // Reset the eMMC card via RST_n

/* MMC/SD Capabilities2 (From: /include/linux/mmc/host.h) */
#define MMC_CAP2_BOOTPART_NOACC	(1 << 0) // Boot partition no access
#define MMC_CAP2_FULL_PWR_CYCLE	(1 << 2) // Can do full power cycle
#define MMC_CAP2_FULL_PWR_CYCLE_IN_SUSPEND	(1 << 3) // Can do full power cycle in suspend
#define MMC_CAP2_HS200_1_8V_SDR	(1 << 5) // Can support HS200 1.8V
#define MMC_CAP2_HS200_1_2V_SDR	(1 << 6) // Can support HS200 1.2V
#define MMC_CAP2_HS200	(MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_HS200_1_2V_SDR)
#define MMC_CAP2_CD_ACTIVE_HIGH	(1 << 10) // Card-detect signal active high
#define MMC_CAP2_RO_ACTIVE_HIGH	(1 << 11) // Write-protect signal active high
#define MMC_CAP2_NO_PRESCAN_POWERUP	(1 << 14) // Don't power up before scan
#define MMC_CAP2_HS400_1_8V	(1 << 15) // Can support HS400 1.8V
#define MMC_CAP2_HS400_1_2V	(1 << 16) // Can support HS400 1.2V
#define MMC_CAP2_HS400	(MMC_CAP2_HS400_1_8V | MMC_CAP2_HS400_1_2V)
#define MMC_CAP2_HSX00_1_8V	(MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_HS400_1_8V)
#define MMC_CAP2_HSX00_1_2V	(MMC_CAP2_HS200_1_2V_SDR | MMC_CAP2_HS400_1_2V)
#define MMC_CAP2_SDIO_IRQ_NOTHREAD	(1 << 17) // Don't create a thread to poll for SDIO IRQ
#define MMC_CAP2_NO_WRITE_PROTECT	(1 << 18) // No physical write protect pin, assume that card is always read-write
#define MMC_CAP2_NO_SDIO	(1 << 19) // Do not send SDIO commands during initialization
#define MMC_CAP2_HS400_ES	(1 << 20) // Host supports enhanced strobe
#define MMC_CAP2_NO_SD	(1 << 21) // Do not send SD commands during initialization
#define MMC_CAP2_NO_MMC	(1 << 22) // Do not send = (e)MMC commands during initialization
#define MMC_CAP2_CQE	(1 << 23) // Has eMMC command queue engine
#define MMC_CAP2_CQE_DCMD	(1 << 24) // CQE can issue a direct command
#define MMC_CAP2_AVOID_3_3V	(1 << 25) // Host must negotiate down from 3.3V
#define MMC_CAP2_MERGE_CAPABLE	(1 << 26) // Host can merge a segment over the segment size

/* MMC/SD Directions */
#define MMC_DATA_READ	1
#define MMC_DATA_WRITE	2

/* MMC/SD Bus Widths */
#define MMC_BUS_WIDTH_1	0
#define MMC_BUS_WIDTH_4	2
#define MMC_BUS_WIDTH_8	3

/* MMC Bus Speeds (Hz) */
#define MMC_BUS_SPEED_DEFAULT	0
#define MMC_BUS_SPEED_HS26	26000000
#define MMC_BUS_SPEED_HS52	52000000
#define MMC_BUS_SPEED_DDR	52000000
#define MMC_BUS_SPEED_HS200	200000000

/* MMC/SD Timing (From: /include/linux/mmc/host.h) */
#define MMC_TIMING_LEGACY	0
#define MMC_TIMING_MMC_HS	1
#define MMC_TIMING_SD_HS	2
#define MMC_TIMING_UHS_SDR12	3
#define MMC_TIMING_UHS_SDR25	4
#define MMC_TIMING_UHS_SDR50	5
#define MMC_TIMING_UHS_SDR104	6
#define MMC_TIMING_UHS_DDR50	7
#define MMC_TIMING_MMC_DDR52	8
#define MMC_TIMING_MMC_HS200	9
#define MMC_TIMING_MMC_HS400	10

/* MMC/SD Signal Voltage (From: /include/linux/mmc/host.h) */
#define MMC_SIGNAL_VOLTAGE_330	0
#define MMC_SIGNAL_VOLTAGE_180	1
#define MMC_SIGNAL_VOLTAGE_120	2

/* MMC/SD Driver Type (From: /include/linux/mmc/host.h) */
#define MMC_SET_DRIVER_TYPE_B	0
#define MMC_SET_DRIVER_TYPE_A	1
#define MMC_SET_DRIVER_TYPE_C	2
#define MMC_SET_DRIVER_TYPE_D	3

/* MMC Commands (From: /include/linux/mmc/mmc.h) */
/* Class 1 */
#define MMC_CMD_GO_IDLE_STATE	0
#define MMC_CMD_SEND_OP_COND	1
#define MMC_CMD_ALL_SEND_CID	2
#define MMC_CMD_SET_RELATIVE_ADDR	3
#define MMC_CMD_SET_DSR	4
#define MMC_CMD_SLEEP_AWAKE	5
#define MMC_CMD_SWITCH	6
#define MMC_CMD_SELECT_CARD	7
#define MMC_CMD_SEND_EXT_CSD	8
#define MMC_CMD_SEND_CSD	9
#define MMC_CMD_SEND_CID	10
#define MMC_CMD_READ_DAT_UNTIL_STOP	11
#define MMC_CMD_STOP_TRANSMISSION	12
#define MMC_CMD_SEND_STATUS	13
#define MMC_CMD_BUS_TEST_R	14
#define MMC_CMD_GO_INACTIVE_STATE	15
#define MMC_CMD_BUS_TEST_W	19
#define MMC_CMD_SPI_READ_OCR	58
#define MMC_CMD_SPI_CRC_ON_OFF	59

/* Class 2 */
#define MMC_CMD_SET_BLOCKLEN	16
#define MMC_CMD_READ_SINGLE_BLOCK	17
#define MMC_CMD_READ_MULTIPLE_BLOCK	18
#define MMC_CMD_SEND_TUNING_BLOCK	19
#define MMC_CMD_SEND_TUNING_BLOCK_HS200	21

/* Class 3 */
#define MMC_CMD_WRITE_DAT_UNTIL_STOP	20

/* Class 4 */
#define MMC_CMD_SET_BLOCK_COUNT	23
#define MMC_CMD_WRITE_SINGLE_BLOCK	24
#define MMC_CMD_WRITE_MULTIPLE_BLOCK	25
#define MMC_CMD_PROGRAM_CID	26
#define MMC_CMD_PROGRAM_CSD	27

/* Class 6 */
#define MMC_CMD_SET_WRITE_PROT	28
#define MMC_CMD_CLR_WRITE_PROT	29
#define MMC_CMD_SEND_WRITE_PROT	30

/* Class 5 */
#define MMC_CMD_ERASE_GROUP_START	35
#define MMC_CMD_ERASE_GROUP_END	36
#define MMC_CMD_ERASE	38

/* Class 9 */
#define MMC_CMD_FAST_IO	39
#define MMC_CMD_GO_IRQ_STATE	40

/* Class 7 */
#define MMC_CMD_LOCK_UNLOCK	42

/* Class 8 */
#define MMC_CMD_APP_CMD	55
#define MMC_CMD_GEN_CMD	56
#define MMC_CMD_RES_MAN	62

#define MMC_CMD62_ARG1	0xEFAC62EC
#define MMC_CMD62_ARG2	0x00CBAEA7

/* MMC Response Types (From: /include/linux/mmc/mmc.h) */
/* Native */
#define MMC_RSP_PRESENT	(1 << 0)
#define MMC_RSP_136	(1 << 1) // 136 bit response
#define MMC_RSP_CRC	(1 << 2) // Expect valid crc
#define MMC_RSP_BUSY	(1 << 3) // Card may send busy
#define MMC_RSP_OPCODE	(1 << 4) // Response contains opcode

/* These are the native response types, and correspond to valid bit patterns of the above flags. One additional valid pattern is all zeros, which means we don't expect a response */
#define MMC_RSP_NONE	(0)
#define MMC_RSP_R1	(MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)
#define MMC_RSP_R1B	(MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE | MMC_RSP_BUSY)
#define MMC_RSP_R2	(MMC_RSP_PRESENT | MMC_RSP_136 | MMC_RSP_CRC)
#define MMC_RSP_R3	(MMC_RSP_PRESENT)
#define MMC_RSP_R4	(MMC_RSP_PRESENT)
#define MMC_RSP_R5	(MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)
#define MMC_RSP_R6	(MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)
#define MMC_RSP_R7	(MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)

/* Non-SPI Command Type Flags */
#define MMC_CMD_MASK	(3 << 5)
#define MMC_CMD_AC	(0 << 5) // Addressed Command, no Data
#define MMC_CMD_ADTC	(1 << 5) // Addressed Data Transfer Command
#define MMC_CMD_BC	(2 << 5) // Broadcast Command, no Response
#define MMC_CMD_BCR	(3 << 5) // Broadcast Command with Response

/* SPI */
#define MMC_RSP_SPI_S1	(1 << 7) // One status byte
#define MMC_RSP_SPI_S2	(1 << 8) // Second byte
#define MMC_RSP_SPI_B4	(1 << 9) // Four data bytes
#define MMC_RSP_SPI_BUSY	(1 << 10) // Card may send busy

/* These are the SPI response types for MMC, SD, and SDIO cards. Commands return R1, with maybe more info. Zero is an error type, callers must always provide the appropriate MMC_RSP_SPI_Rx flags */
#define MMC_RSP_SPI_R1	(MMC_RSP_SPI_S1)
#define MMC_RSP_SPI_R1B	(MMC_RSP_SPI_S1 | MMC_RSP_SPI_BUSY)
#define MMC_RSP_SPI_R2	(MMC_RSP_SPI_S1 | MMC_RSP_SPI_S2)
#define MMC_RSP_SPI_R3	(MMC_RSP_SPI_S1 | MMC_RSP_SPI_B4)
#define MMC_RSP_SPI_R4	(MMC_RSP_SPI_S1 | MMC_RSP_SPI_B4)
#define MMC_RSP_SPI_R5	(MMC_RSP_SPI_S1 | MMC_RSP_SPI_S2)
#define MMC_RSP_SPI_R7	(MMC_RSP_SPI_S1 | MMC_RSP_SPI_B4)

/* MMC Response Values */
/* R1 - MMC status in R1, for native mode (SPI bits are different) */
#define MMC_RSP_R1_OUT_OF_RANGE	(1 << 31)
#define MMC_RSP_R1_ADDRESS_ERROR	(1 << 30)
#define MMC_RSP_R1_BLOCK_LEN_ERROR	(1 << 29)
#define MMC_RSP_R1_ERASE_SEQ_ERROR	(1 << 28)
#define MMC_RSP_R1_ERASE_PARAM	(1 << 27)
#define MMC_RSP_R1_WP_VIOLATION	(1 << 26)
#define MMC_RSP_R1_CARD_IS_LOCKED	(1 << 25)
#define MMC_RSP_R1_LOCK_UNLOCK_FAILED	(1 << 24)
#define MMC_RSP_R1_COM_CRC_ERROR	(1 << 23)
#define MMC_RSP_R1_ILLEGAL_COMMAND	(1 << 22)
#define MMC_RSP_R1_CARD_ECC_FAILED	(1 << 21)
#define MMC_RSP_R1_CC_ERROR	(1 << 20)
#define MMC_RSP_R1_ERROR	(1 << 19)
#define MMC_RSP_R1_UNDERRUN	(1 << 18)
#define MMC_RSP_R1_OVERRUN	(1 << 17)
#define MMC_RSP_R1_CID_CSD_OVERWRITE	(1 << 16)
#define MMC_RSP_R1_WP_ERASE_SKIP	(1 << 15)
#define MMC_RSP_R1_CARD_ECC_DISABLED	(1 << 14)
#define MMC_RSP_R1_ERASE_RESET	(1 << 13)
// MMC_RSP_R1_STATUS(x)            (x & 0xFFFFE000)
// MMC_RSP_R1_CURRENT_STATE(x)	((x & 0x00001E00) >> 9)
#define MMC_RSP_R1_READY_FOR_DATA	(1 << 8)
#define MMC_RSP_R1_SWITCH_ERROR	(1 << 7)
#define MMC_RSP_R1_EXCEPTION_EVENT	(1 << 6)
#define MMC_RSP_R1_APP_CMD	(1 << 5)
#define MMC_RSP_R1_AKE_SEQ_ERROR	(1 << 3)

/* R1 SPI - MMC/SD in SPI mode reports R1 status always, and R2 for SEND_STATUS. R1 is the low order byte, R2 is the next highest byte, when present */
#define MMC_RSP_R1_SPI_IDLE	(1 << 0)
#define MMC_RSP_R1_SPI_ERASE_RESET	(1 << 1)
#define MMC_RSP_R1_SPI_ILLEGAL_COMMAND	(1 << 2)
#define MMC_RSP_R1_SPI_COM_CRC	(1 << 3)
#define MMC_RSP_R1_SPI_ERASE_SEQ	(1 << 4)
#define MMC_RSP_R1_SPI_ADDRESS	(1 << 5)
#define MMC_RSP_R1_SPI_PARAMETER	(1 << 6)
/* R1 bit 7 is always zero */

/* R2 SPI - See above */
#define MMC_RSP_R2_SPI_CARD_LOCKED	(1 << 8)
#define MMC_RSP_R2_SPI_WP_ERASE_SKIP	(1 << 9) // Or lock/unlock fail
#define MMC_RSP_R2_SPI_LOCK_UNLOCK_FAIL	MMC_RSP_R2_SPI_WP_ERASE_SKIP
#define MMC_RSP_R2_SPI_ERROR	(1 << 10)
#define MMC_RSP_R2_SPI_CC_ERROR	(1 << 11)
#define MMC_RSP_R2_SPI_CARD_ECC_ERROR	(1 << 12)
#define MMC_RSP_R2_SPI_WP_VIOLATION	(1 << 13)
#define MMC_RSP_R2_SPI_ERASE_PARAM	(1 << 14)
#define MMC_RSP_R2_SPI_OUT_OF_RANGE	(1 << 15) // Or CSD overwrite
#define MMC_RSP_R2_SPI_CSD_OVERWRITE	MMC_RSP_R2_SPI_OUT_OF_RANGE

/* MMC Operation Condition Register (OCR) values */
#define MMC_OCR_BUSY	0x80000000 // Busy Status - 0 = Initializing / 1 = Initialization Complete
#define MMC_OCR_HCS	0x40000000 // Card Capacity Status - 0 = SDSC / 1 = SDHC or SDXC
#define MMC_OCR_UHS_II	0x20000000 // UHS-II Card Status - 0 = Non UHS-II Card / 1 = UHS-II Card
#define MMC_OCR_S18A	0x01000000 // Switching to 1.8V Accepted - 0 = Continue current voltage signaling / 1 = Ready for switching signal voltage
#define MMC_OCR_VOLTAGE_MASK	0x007FFF80
#define MMC_OCR_ACCESS_MODE	0x60000000

/* MMC Card Status Register (CSR) values */
/* Note: These map to the Native mode R1 response values */
#define MMC_CARD_STATUS_MASK	(~0x0206BF7F)
#define MMC_CARD_STATUS_ERROR	(1 << 19)
#define MMC_CARD_STATUS_CURRENT_STATE	(0x0F << 9) // See MMC_CURRENT_STATE_ definitions below
#define MMC_CARD_STATUS_READY_FOR_DATA	(1 << 8)
#define MMC_CARD_STATUS_SWITCH_ERROR	(1 << 7)

/* MMC Current State values (From Card Status Register or R1 Response) */
#define MMC_CURRENT_STATE_IDLE	(0 << 9)
#define MMC_CURRENT_STATE_READY	(1 << 9)
#define MMC_CURRENT_STATE_IDENT	(2 << 9)
#define MMC_CURRENT_STATE_STBY	(3 << 9)
#define MMC_CURRENT_STATE_TRAN	(4 << 9)
#define MMC_CURRENT_STATE_DATA	(5 << 9)
#define MMC_CURRENT_STATE_RCV	(6 << 9)
#define MMC_CURRENT_STATE_PRG	(7 << 9)
#define MMC_CURRENT_STATE_DIS	(8 << 9)

/* MMC Card Identification Data (CID) values */
/* MMC CID Fields */
#define MMC_CID_MID	1 // Manufacturer ID
#define MMC_CID_OID	2 // OEM/Application ID
#define MMC_CID_PNM0	3 // Product name (Byte 0)
#define MMC_CID_PNM1	4 // Product name (Byte 1)
#define MMC_CID_PNM2	5 // Product name (Byte 2)
#define MMC_CID_PNM3	6 // Product name (Byte 3)
#define MMC_CID_PNM4	7 // Product name (Byte 4)
#define MMC_CID_PNM5	8 // Product name (Byte 5)
#define MMC_CID_PNM6	9 // Product name (Byte 6)
#define MMC_CID_PRV	10 // Product revision
#define MMC_CID_HRV	11 // Hardware revision
#define MMC_CID_FRV	12 // Firmware revision
#define MMC_CID_PSN	13 // Product serial number
#define MMC_CID_MDT_YEAR	14 // Manufacturing year
#define MMC_CID_MDT_MONTH	15 // Manufacturing month
#define MMC_CID_CRC	16 // CRC

/* MMC Card Specific Data (CSD) values */
/* MMC CSD Fields */
#define MMC_CSD_STRUCTURE	1
#define MMC_CSD_SPECVER	2 // MMC/eMMC Only
#define MMC_CSD_TAAC_UNIT	3
#define MMC_CSD_TAAC_VALUE	4
#define MMC_CSD_NSAC	5
#define MMC_CSD_TRAN_SPEED_UNIT	6
#define MMC_CSD_TRAN_SPEED_VALUE	37
#define MMC_CSD_CCC	7
#define MMC_CSD_READ_BL_LEN	8
#define MMC_CSD_READ_BL_PARTIAL	9
#define MMC_CSD_WRITE_BLK_MISALIGN	10
#define MMC_CSD_READ_BLK_MISALIGN	11
#define MMC_CSD_DSR_IMP	12
#define MMC_CSD_C_SIZE	13
#define MMC_CSD_VDD_R_CURR_MIN	14
#define MMC_CSD_VDD_R_CURR_MAX	15
#define MMC_CSD_VDD_W_CURR_MIN	16
#define MMC_CSD_VDD_W_CURR_MAX	17
#define MMC_CSD_C_SIZE_MULT	18
#define MMC_CSD_ERASE_BLK_EN	19 // SD Specification
#define MMC_CSD_SECTOR_SIZE	20 // MMC/eMMC Specification / SD Specification
#define MMC_CSD_ERASE_GRP_SIZE	21 // MMC/eMMC Specification
#define MMC_CSD_ERASE_GRP_MULT	22 // MMC/eMMC Specification
#define MMC_CSD_WP_GRP_SIZE	23
#define MMC_CSD_WP_GRP_ENABLE	24
#define MMC_CSD_DEFAULT_ECC	25 // MMC/eMMC Only
#define MMC_CSD_R2W_FACTOR	26
#define MMC_CSD_WRITE_BL_LEN	27
#define MMC_CSD_WRITE_BL_PARTIAL	28
#define MMC_CSD_CONTENT_PROT_APP	29 // MMC/eMMC Only
#define MMC_CSD_FILE_FORMAT_GRP	30
#define MMC_CSD_COPY	31
#define MMC_CSD_PERM_WRITE_PROTECT	32
#define MMC_CSD_TMP_WRITE_PROTECT	33
#define MMC_CSD_FILE_FORMAT	34
#define MMC_CSD_ECC	35 // MMC/eMMC Only
#define MMC_CSD_CRC	36

/* MMC CSD Structure values */
#define MMC_CSD_STRUCT_VER_1_0	0 // Valid for system specification 1.0 - 1.2
#define MMC_CSD_STRUCT_VER_1_1	1 // Valid for system specification 1.4 - 2.2
#define MMC_CSD_STRUCT_VER_1_2	2 // Valid for system specification 3.1 - 3.2 - 3.31 - 4.0 - 4.1
#define MMC_CSD_STRUCT_EXT_CSD	3 // Version is coded in CSD_STRUCTURE in EXT_CSD

/* MMC CSD Spec Version values */
#define MMC_CSD_SPEC_VER_0	0 // Implements system specification 1.0 - 1.2
#define MMC_CSD_SPEC_VER_1	1 // Implements system specification 1.4
#define MMC_CSD_SPEC_VER_2	2 // Implements system specification 2.0 - 2.2
#define MMC_CSD_SPEC_VER_3	3 // Implements system specification 3.1 - 3.2 - 3.31
#define MMC_CSD_SPEC_VER_4	4 // Implements system specification 4.0 - 4.1

/* MMC CSD TAAC Time units */
const uint32_t MMC_CSD_TAAC_UNITS[] = {
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000};

/* MMC CSD TAAC Time values */
const uint32_t MMC_CSD_TAAC_VALUES[] = {
	0,
	10,
	12,
	13,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	70,
	80};

/* MMC CSD Card Command Class (CCC) values */
#define MMC_CCC_BASIC	(1 << 0) // (Class 0) Basic protocol functions (CMD0,1,2,3,4,7,9,10,12,13,15) (and for SPI, CMD58,59)
#define MMC_CCC_STREAM_READ	(1 << 1) // (Class 1) Stream read commands (CMD11)
#define MMC_CCC_BLOCK_READ	(1 << 2) // (Class 2) Block read commands (CMD16,17,18)
#define MMC_CCC_STREAM_WRITE	(1 << 3) // (Class 3) Stream write commands (CMD20)
#define MMC_CCC_BLOCK_WRITE	(1 << 4) // (Class 4) Block write commands (CMD16,24,25,26,27)
#define MMC_CCC_ERASE	(1 << 5) // (Class 5) Ability to erase blocks (CMD32,33,34,35,36,37,38,39)
#define MMC_CCC_WRITE_PROT	(1 << 6) // (Class 6) Ability to write protect blocks (CMD28,29,30)
#define MMC_CCC_LOCK_CARD	(1 << 7) // (Class 7) Ability to lock down card (CMD16,CMD42)
#define MMC_CCC_APP_SPEC	(1 << 8) // (Class 8) Application specific (CMD55,56,57,ACMD*)
#define MMC_CCC_IO_MODE	(1 << 9) // (Class 9) I/O mode (CMD5,39,40,52,53)
#define MMC_CCC_SWITCH	(1 << 10) // (Class 10) High speed switch (CMD6,34,35,36,37,50)
#define MMC_CCC_EXTENSION	(1 << 11) // (Class 11) Extension (CMD?)

/* MMC CSD Transfer Speed Rate units */
const uint32_t MMC_CSD_TRAN_SPEED_UNITS[] = {
	10000,
	100000,
	1000000,
	10000000,
	0,
	0,
	0,
	0};

/* MMC CSD Transfer Speed Time values */
const uint32_t MMC_CSD_TRAN_SPEED_VALUES[] = {
	0,
	10,
	12,
	13,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	70,
	80};

#define SECURE_ERASE	0x80000000

/* MMC Voltage Values */
#define MMC_VDD_165_195	0x00000080 // VDD voltage 1.65 - 1.95
#define MMC_VDD_20_21	0x00000100 // VDD voltage 2.0 ~ 2.1
#define MMC_VDD_21_22	0x00000200 // VDD voltage 2.1 ~ 2.2
#define MMC_VDD_22_23	0x00000400 // VDD voltage 2.2 ~ 2.3
#define MMC_VDD_23_24	0x00000800 // VDD voltage 2.3 ~ 2.4
#define MMC_VDD_24_25	0x00001000 // VDD voltage 2.4 ~ 2.5
#define MMC_VDD_25_26	0x00002000 // VDD voltage 2.5 ~ 2.6
#define MMC_VDD_26_27	0x00004000 // VDD voltage 2.6 ~ 2.7
#define MMC_VDD_27_28	0x00008000 // VDD voltage 2.7 ~ 2.8
#define MMC_VDD_28_29	0x00010000 // VDD voltage 2.8 ~ 2.9
#define MMC_VDD_29_30	0x00020000 // VDD voltage 2.9 ~ 3.0
#define MMC_VDD_30_31	0x00040000 // VDD voltage 3.0 ~ 3.1
#define MMC_VDD_31_32	0x00080000 // VDD voltage 3.1 ~ 3.2
#define MMC_VDD_32_33	0x00100000 // VDD voltage 3.2 ~ 3.3
#define MMC_VDD_33_34	0x00200000 // VDD voltage 3.3 ~ 3.4
#define MMC_VDD_34_35	0x00400000 // VDD voltage 3.4 ~ 3.5
#define MMC_VDD_35_36	0x00800000 // VDD voltage 3.5 ~ 3.6

/* MMC Switch Mode Values */
#define MMC_SWITCH_MODE_CMD_SET	0x00 // Change the command set
#define MMC_SWITCH_MODE_SET_BITS	0x01 // Set bits in EXT_CSD byte addressed by index which are 1 in value field
#define MMC_SWITCH_MODE_CLEAR_BITS	0x02 // Clear bits in EXT_CSD byte	addressed by index, which are 1 in value field
#define MMC_SWITCH_MODE_WRITE_BYTE	0x03 // Set target byte to value

/* MMC EXT_CSD fields */
#define EXT_CSD_CMDQ_MODE_EN	15 // R/W
#define EXT_CSD_FLUSH_CACHE	32 // W
#define EXT_CSD_CACHE_CTRL	33 // R/W
#define EXT_CSD_POWER_OFF_NOTIFICATION	34 // R/W
#define EXT_CSD_PACKED_FAILURE_INDEX	35 // RO
#define EXT_CSD_PACKED_CMD_STATUS	36 // RO
#define EXT_CSD_EXP_EVENTS_STATUS	54 // RO, 2 bytes
#define EXT_CSD_EXP_EVENTS_CTRL	56 // R/W, 2 bytes
#define EXT_CSD_DATA_SECTOR_SIZE	61 // R
#define EXT_CSD_ENH_START_ADDR	136 // R/W
#define EXT_CSD_ENH_SIZE_MULT	140 // R/W
#define EXT_CSD_GP_SIZE_MULT	143 // R/W
#define EXT_CSD_PARTITION_SETTING_COMPLETED	155 // R/W
#define EXT_CSD_PARTITION_ATTRIBUTE	156 // R/W
#define EXT_CSD_MAX_ENH_SIZE_MULT	157 // R
#define EXT_CSD_PARTITION_SUPPORT	160 // RO
#define EXT_CSD_HPI_MGMT	161 // R/W
#define EXT_CSD_RST_N_FUNCTION	162 // R/W
#define EXT_CSD_BKOPS_EN	163 // R/W
#define EXT_CSD_BKOPS_START	164 // W
#define EXT_CSD_SANITIZE_START	165 // W
#define EXT_CSD_WR_REL_PARAM	166 // RO
#define EXT_CSD_WR_REL_SET	167 // R/W
#define EXT_CSD_RPMB_MULT	168 // RO
#define EXT_CSD_FW_CONFIG	169 // R/W
#define EXT_CSD_BOOT_WP	173 // R/W
#define EXT_CSD_ERASE_GROUP_DEF	175 // R/W
#define EXT_CSD_BOOT_BUS_CONDITIONS	177 // R/W/E
#define EXT_CSD_PART_CONFIG	179 // R/W
#define EXT_CSD_ERASED_MEM_CONT	181 // RO
#define EXT_CSD_BUS_WIDTH	183 // R/W
#define EXT_CSD_STROBE_SUPPORT	184 // RO
#define EXT_CSD_HS_TIMING	185 // R/W
#define EXT_CSD_POWER_CLASS	187 // R/W
#define EXT_CSD_REV	192 // RO
#define EXT_CSD_STRUCTURE	194 // RO
#define EXT_CSD_CARD_TYPE	196 // RO
#define EXT_CSD_DRIVER_STRENGTH	197 // RO
#define EXT_CSD_OUT_OF_INTERRUPT_TIME	198 // RO
#define EXT_CSD_PART_SWITCH_TIME	199 // RO
#define EXT_CSD_PWR_CL_52_195	200 // RO
#define EXT_CSD_PWR_CL_26_195	201 // RO
#define EXT_CSD_PWR_CL_52_360	202 // RO
#define EXT_CSD_PWR_CL_26_360	203 // RO
#define EXT_CSD_SEC_CNT	212 // RO, 4 bytes
#define EXT_CSD_S_A_TIMEOUT	217 // RO
#define EXT_CSD_REL_WR_SEC_C	222 // RO
#define EXT_CSD_HC_WP_GRP_SIZE	221 // RO
#define EXT_CSD_ERASE_TIMEOUT_MULT	223 // RO
#define EXT_CSD_HC_ERASE_GRP_SIZE	224 // RO
#define EXT_CSD_BOOT_SIZE_MULT	226 // RO
#define EXT_CSD_SEC_TRIM_MULT	229 // RO
#define EXT_CSD_SEC_ERASE_MULT	230 // RO
#define EXT_CSD_SEC_FEATURE_SUPPORT	231 // RO
#define EXT_CSD_TRIM_MULT	232 // RO
#define EXT_CSD_PWR_CL_200_195	236 // RO
#define EXT_CSD_PWR_CL_200_360	237 // RO
#define EXT_CSD_PWR_CL_DDR_52_195	238 // RO
#define EXT_CSD_PWR_CL_DDR_52_360	239 // RO
#define EXT_CSD_BKOPS_STATUS	246 // RO
#define EXT_CSD_POWER_OFF_LONG_TIME	247 // RO
#define EXT_CSD_GENERIC_CMD6_TIME	248 // RO
#define EXT_CSD_CACHE_SIZE	249 // RO, 4 bytes
#define EXT_CSD_PWR_CL_DDR_200_360	253 // RO
#define EXT_CSD_FIRMWARE_VERSION	254 // RO, 8 bytes
#define EXT_CSD_PRE_EOL_INFO	267 // RO
#define EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_A	268 // RO
#define EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_B	269 // RO
#define EXT_CSD_CMDQ_DEPTH	307 // RO
#define EXT_CSD_CMDQ_SUPPORT	308 // RO
#define EXT_CSD_SUPPORTED_MODE	493 // RO
#define EXT_CSD_TAG_UNIT_SIZE	498 // RO
#define EXT_CSD_DATA_TAG_SUPPORT	499 // RO
#define EXT_CSD_MAX_PACKED_WRITES	500 // RO
#define EXT_CSD_MAX_PACKED_READS	501 // RO
#define EXT_CSD_BKOPS_SUPPORT	502 // RO
#define EXT_CSD_HPI_FEATURES	503 // RO

/* MMC EXT_CSD field definitions */
#define EXT_CSD_PARTITION_ATTRIBUTE_ENH_4	0x10
#define EXT_CSD_PARTITION_ATTRIBUTE_ENH_3	0x08
#define EXT_CSD_PARTITION_ATTRIBUTE_ENH_2	0x04
#define EXT_CSD_PARTITION_ATTRIBUTE_ENH_1	0x02
#define EXT_CSD_PARTITION_ATTRIBUTE_ENH_USR	0x01

#define EXT_CSD_PARTITION_EXT_ATTRIBUTE_EN	0x04
#define EXT_CSD_PARTITION_ENH_ATTRIBUTE_EN	0x02
#define EXT_CSD_PARTITION_PARTITIONING_EN	0x01

#define EXT_CSD_WR_REL_PARAM_EN	(1 << 2)
#define EXT_CSD_WR_REL_PARAM_EN_RPMB_REL_WR	(1 << 4)

#define EXT_CSD_BOOT_WP_B_PWR_WP_DIS	0x40
#define EXT_CSD_BOOT_WP_B_PERM_WP_DIS	0x10
#define EXT_CSD_BOOT_WP_B_PERM_WP_EN	0x04
#define EXT_CSD_BOOT_WP_B_PWR_WP_EN	0x01

#define EXT_CSD_PART_CONFIG_ACC_MASK	0x07
#define EXT_CSD_PART_CONFIG_ACC_BOOT0	0x01
#define EXT_CSD_PART_CONFIG_ACC_RPMB	0x03
#define EXT_CSD_PART_CONFIG_ACC_GP0	0x04

#define EXT_CSD_PART_SETTING_COMPLETED	0x01
#define EXT_CSD_PART_SUPPORT_PART_EN	0x01

#define EXT_CSD_CMD_SET_NORMAL	(1 << 0)
#define EXT_CSD_CMD_SET_SECURE	(1 << 1)
#define EXT_CSD_CMD_SET_CPSECURE	(1 << 2)

#define EXT_CSD_CARD_TYPE_HS_26	(1 << 0) // Card can run at 26MHz
#define EXT_CSD_CARD_TYPE_HS_52	(1 << 1) // Card can run at 52MHz
#define EXT_CSD_CARD_TYPE_HS	(EXT_CSD_CARD_TYPE_HS_26 | EXT_CSD_CARD_TYPE_HS_52)
#define EXT_CSD_CARD_TYPE_DDR_1_8V	(1 << 2) // Card can run at 52MHz / DDR mode @1.8V or 3V I/O
#define EXT_CSD_CARD_TYPE_DDR_1_2V	(1 << 3) // Card can run at 52MHz / DDR mode @1.2V I/O
#define EXT_CSD_CARD_TYPE_DDR_52	(EXT_CSD_CARD_TYPE_DDR_1_8V | EXT_CSD_CARD_TYPE_DDR_1_2V)
#define EXT_CSD_CARD_TYPE_HS200_1_8V	(1 << 4) // Card can run at 200MHz
#define EXT_CSD_CARD_TYPE_HS200_1_2V	(1 << 5) // Card can run at 200MHz / SDR mode @1.2V I/O
#define EXT_CSD_CARD_TYPE_HS200	(EXT_CSD_CARD_TYPE_HS200_1_8V | EXT_CSD_CARD_TYPE_HS200_1_2V)
#define EXT_CSD_CARD_TYPE_HS400_1_8V	(1 << 6) // Card can run at 200MHz DDR, 1.8V
#define EXT_CSD_CARD_TYPE_HS400_1_2V	(1 << 7) // Card can run at 200MHz DDR, 1.2V
#define EXT_CSD_CARD_TYPE_HS400	(EXT_CSD_CARD_TYPE_HS400_1_8V | EXT_CSD_CARD_TYPE_HS400_1_2V)
#define EXT_CSD_CARD_TYPE_HS400ES	(1 << 8) // Card can run at HS400ES

#define EXT_CSD_BUS_WIDTH_1	0 // Card is in 1 bit mode
#define EXT_CSD_BUS_WIDTH_4	1 // Card is in 4 bit mode
#define EXT_CSD_BUS_WIDTH_8	2 // Card is in 8 bit mode
#define EXT_CSD_DDR_BUS_WIDTH_4	5 // Card is in 4 bit DDR mode
#define EXT_CSD_DDR_BUS_WIDTH_8	6 // Card is in 8 bit DDR mode
#define EXT_CSD_BUS_WIDTH_STROBE	1 << 7 // Enhanced strobe mode

#define EXT_CSD_TIMING_BC	0 // Backwards compatility
#define EXT_CSD_TIMING_HS	1 // High speed
#define EXT_CSD_TIMING_HS200	2 // HS200
#define EXT_CSD_TIMING_HS400	3 // HS400
#define EXT_CSD_DRV_STR_SHIFT	4 // Driver Strength shift

#define EXT_CSD_SEC_ER_EN	1 << 0
#define EXT_CSD_SEC_BD_BLK_EN	1 << 2
#define EXT_CSD_SEC_GB_CL_EN	1 << 4
#define EXT_CSD_SEC_SANITIZE	1 << 6 // v4.5 only

#define EXT_CSD_RST_N_EN_MASK	0x03
#define EXT_CSD_RST_N_ENABLED	1 // RST_n is enabled on card

#define EXT_CSD_NO_POWER_NOTIFICATION	0
#define EXT_CSD_POWER_ON	1
#define EXT_CSD_POWER_OFF_SHORT	2
#define EXT_CSD_POWER_OFF_LONG	3

#define EXT_CSD_PWR_CL_8BIT_MASK	0xF0 // 8 bit PWR CLS
#define EXT_CSD_PWR_CL_4BIT_MASK	0x0F // 8 bit PWR CLS
#define EXT_CSD_PWR_CL_8BIT_SHIFT	4
#define EXT_CSD_PWR_CL_4BIT_SHIFT	0

#define EXT_CSD_PACKED_EVENT_EN	1 << 3

/* EXCEPTION_EVENT_STATUS field */
#define EXT_CSD_URGENT_BKOPS	1 << 0
#define EXT_CSD_DYNCAP_NEEDED	1 << 1
#define EXT_CSD_SYSPOOL_EXHAUSTED	1 << 2
#define EXT_CSD_PACKED_FAILURE	1 << 3

#define EXT_CSD_PACKED_GENERIC_ERROR	1 << 0
#define EXT_CSD_PACKED_INDEXED_ERROR	1 << 1

/* BKOPS status level */
#define EXT_CSD_BKOPS_LEVEL_2	0x02

/* BKOPS modes */
#define EXT_CSD_MANUAL_BKOPS_MASK	0x01
#define EXT_CSD_AUTO_BKOPS_MASK	0x02

/* Command Queue */
#define EXT_CSD_CMDQ_MODE_ENABLED	1 << 0
#define EXT_CSD_CMDQ_DEPTH_MASK	0x1F
#define EXT_CSD_CMDQ_SUPPORTED	1 << 0

/* High Speed Max */
#define MMC_HIGH_26_MAX_DTR	26000000
#define MMC_HIGH_52_MAX_DTR	52000000
#define MMC_HIGH_DDR_MAX_DTR	52000000
#define MMC_HS200_MAX_DTR	200000000

/* Minimum partition switch timeout */
#define MMC_MIN_PART_SWITCH_TIME	300 // Milliseconds

/* MMC ????? */
#define MMCPART_NOAVAILABLE	(0xff)
#define PART_ACCESS_MASK	(0x07)
#define PART_SUPPORT	(0x01)
#define ENHNCD_SUPPORT	(0x02)
#define PART_ENH_ATTRIB	(0x1f)

/* Maximum block size for MMC */
#define MMC_MAX_BLOCK_LEN	512

/* Maximum block count for MMC */
#define MMC_MAX_BLOCK_COUNT	65535

/* The number of MMC physical partitions.  These consist of: boot partitions (2), general purpose partitions (4) and RPMB partition (1) in MMC v4.4 */
#define MMC_NUM_BOOT_PARTITION	2
#define MMC_NUM_GP_PARTITION	4
#define MMC_NUM_PHY_PARTITION	7

/* Timeouts */
#define MMC_DEFAULT_CMD6_TIMEOUT_MS	500
#define MMC_MIN_CACHE_EN_TIMEOUT_MS	1600

/* Sizes */
#define MMC_FIRMWARE_VERSION_LEN	8

/* Version specific features */
#define MMC_DISCARD_FEATURE	0x01

/* Busy Poll Commands */
#define MMC_BUSY_CMD6	0
#define MMC_BUSY_ERASE	1
#define MMC_BUSY_HPI	2

/* Erase/Trim/Discard Arguments */
#define MMC_ERASE_ARG	0x00000000
#define MMC_SECURE_ERASE_ARG	0x80000000
#define MMC_TRIM_ARG	0x00000001
#define MMC_DISCARD_ARG	0x00000003
#define MMC_SECURE_TRIM1_ARG	0x80000001
#define MMC_SECURE_TRIM2_ARG	0x80008000
#define MMC_SECURE_ARGS	0x80000000
#define MMC_TRIM_ARGS	0x00008001

/* ============================================================================== */
/* SD specific constants */
#define SD_DEFAULT_BLOCKSIZE	512
#define SD_DEFAULT_BLOCKSHIFT	9

/* SD Bus Widths */
#define SD_BUS_WIDTH_1	0
#define SD_BUS_WIDTH_4	2

/* SD Bus Speeds (Hz) */
#define SD_BUS_SPEED_DEFAULT	25000000
#define SD_BUS_SPEED_HS	50000000
#define SD_BUS_SPEED_UHS_SDR12	25000000
#define SD_BUS_SPEED_UHS_SDR25	50000000
#define SD_BUS_SPEED_UHS_DDR50	50000000
#define SD_BUS_SPEED_UHS_SDR50	100000000
#define SD_BUS_SPEED_UHS_SDR104	208000000

/* SD Commands (From: /include/linux/mmc/sd.h) */
/* Class 0 */
#define SD_CMD_SEND_RELATIVE_ADDR	3
#define SD_CMD_SEND_IF_COND	8
#define SD_CMD_SWITCH_VOLTAGE	11

/* Class 10 */
#define SD_CMD_SWITCH	6 // See: 4.3.10 Switch Function Command

/* Class 5 */
#define SD_CMD_ERASE_WR_BLK_START	32
#define SD_CMD_ERASE_WR_BLK_END	33

/* Application commands */
#define SD_CMD_APP_SET_BUS_WIDTH	6
#define SD_CMD_APP_SD_STATUS	13
#define SD_CMD_APP_SEND_NUM_WR_BLKS	22
#define SD_CMD_APP_SEND_OP_COND	41
#define SD_CMD_APP_SEND_SCR	51

/* SD_CMD_SWITCH argument format:
      [31] Check (0) or switch (1)
      [30:24] Reserved (0)
      [23:20] Function group 6
      [19:16] Function group 5
      [15:12] Function group 4
      [11:8] Function group 3
      [7:4] Function group 2
      [3:0] Function group 1 */

/* SD Switch Mode Values */
#define SD_SWITCH_MODE_CHECK	0
#define SD_SWITCH_MODE_SWITCH	1

/* SD Switch Function Groups */
#define SD_SWITCH_FUNCTION_GROUP_ACCESS	0 // Access Mode
#define SD_SWITCH_FUNCTION_GROUP_COMMAND	1 // Command System
#define SD_SWITCH_FUNCTION_GROUP_DRIVER	2 // Driver Strength
#define SD_SWITCH_FUNCTION_GROUP_POWER	3 // Power Limit

/* SD Switch Access Modes */
#define SD_SWITCH_ACCESS_MODE_DEF	0 // Default SDR12
#define SD_SWITCH_ACCESS_MODE_HS	1 // High Speed SDR25
#define SD_SWITCH_ACCESS_MODE_SDR50	2 // SDR50 (1.8V only)
#define SD_SWITCH_ACCESS_MODE_SDR104	3 // SDR104 (1.8V only)
#define SD_SWITCH_ACCESS_MODE_DDR50	4 // DDR50 (1.8V only)

/* SD Switch Command System */
#define SD_SWITCH_COMMAND_SYSTEM_DEF	0 // Default
#define SD_SWITCH_COMMAND_SYSTEM_EC	1 // For eC
#define SD_SWITCH_COMMAND_SYSTEM_OTP	3 // OTP
#define SD_SWITCH_COMMAND_SYSTEM_ASSD	4 // ASSD

/* SD Switch Driver Strength */
#define SD_SWITCH_DRIVER_STRENGTH_DEF	0 // Default Type B
#define SD_SWITCH_DRIVER_STRENGTH_TYPE_A	1 // Type A
#define SD_SWITCH_DRIVER_STRENGTH_TYPE_C	2 // Type C
#define SD_SWITCH_DRIVER_STRENGTH_TYPE_D	3 // Type D

/* SD Switch Power Limit */
#define SD_SWITCH_POWER_LIMIT_DEF	0 // Default 0.72W
#define SD_SWITCH_POWER_LIMIT_144	1 // 1.44W
#define SD_SWITCH_POWER_LIMIT_216	2 // 2.16W (Embedded only)
#define SD_SWITCH_POWER_LIMIT_288	3 // 2.88W (Embedded only)
#define SD_SWITCH_POWER_LIMIT_180	4 // 1.80W

/* SD_CMD_SEND_IF_COND argument format:
      [31:12] Reserved (0)
      [11:8] Host Voltage Supply Flags
      [7:0] Check Pattern (0xAA) */

/* SD Send Interface Condition Values */
#define SD_SEND_IF_COND_CHECK_PATTERN	0xAA
#define SD_SEND_IF_COND_VOLTAGE_MASK	0x00FF8000 // MMC_VDD_27_28, MMC_VDD_28_29, MMC_VDD_29_30, MMC_VDD_30_31, MMC_VDD_31_32, MMC_VDD_32_33, MMC_VDD_33_34, MMC_VDD_34_35, MMC_VDD_35_36

/* SD Send Operation Condition Values */
#define SD_SEND_OP_COND_VOLTAGE_MASK	0x00FF8000 // MMC_VDD_27_28, MMC_VDD_28_29, MMC_VDD_29_30, MMC_VDD_30_31, MMC_VDD_31_32, MMC_VDD_32_33, MMC_VDD_33_34, MMC_VDD_34_35, MMC_VDD_35_36

/* SD Operation Condition Register values */
#define SD_OCR_CCS	0x40000000 // Card Capacity Status - 0 = SDSC / 1 = SDHC or SDXC
#define SD_OCR_UHS_II	0x20000000 // UHS-II Card Status - 0 = Non UHS-II Card / 1 = UHS-II Card
#define SD_OCR_XPC	0x10000000 // SDXC Power Control
#define SD_OCR_S18A	0x01000000 // 1.8V Switching Accepted

/* SD CSD Structure values */
#define SD_CSD_STRUCT_VER_1_0	0 // Standard Capacity
#define SD_CSD_STRUCT_VER_2_0	1 // High Capacity and Extended Capacity

/* SD Status Register (SSR) values */
/* SD SSR Fields */
#define SD_SSR_DAT_BUS_WIDTH	1
#define SD_SSR_SECURED_MODE	2
#define SD_SSR_SD_CARD_TYPE	3
#define SD_SSR_SIZE_OF_PROTECTED_AREA	4
#define SD_SSR_SPEED_CLASS	5
#define SD_SSR_PERFORMANCE_MOVE	6
#define SD_SSR_AU_SIZE	7
#define SD_SSR_ERASE_SIZE	8
#define SD_SSR_ERASE_TIMEOUT	9
#define SD_SSR_ERASE_OFFSET	10
#define SD_SSR_UHS_SPEED_GRADE	11
#define SD_SSR_UHS_AU_SIZE	12

/* SD SSR Bus Width values */
#define SD_SSR_BUS_WIDTH_1	0 // 1 (default)
#define SD_SSR_BUS_WIDTH_4	2 // 4 bit width

/* SD SSR Card Type values */
#define SD_SSR_CARD_TYPE_RW	0x0000 // Regular SD RD/WR Card
#define SD_SSR_CARD_TYPE_ROM	0x0001 // SD ROM Card
#define SD_SSR_CARD_TYPE_OTP	0x0002 // OTP

/* SD SSR Speed Class values */
#define SD_SSR_SPEED_CLASS_0	0x00 // Class 0
#define SD_SSR_SPEED_CLASS_2	0x01 // Class 2
#define SD_SSR_SPEED_CLASS_4	0x02 // Class 4
#define SD_SSR_SPEED_CLASS_6	0x03 // Class 6
#define SD_SSR_SPEED_CLASS_10	0x04 // Class 10

/* SD SSR AU Size values */
const uint32_t SD_SSR_AU_SIZE_VALUES[] = {
	0, // Not Defined
	0x00004000, // 16 KB
	0x00008000, // 32 KB
	0x00010000, // 64 KB
	0x00020000, // 128 KB
	0x00040000, // 256 KB
	0x00080000, // 512 KB
	0x00100000, // 1 MB
	0x00200000, // 2 MB
	0x00400000, // 4 MB
	0x00800000, // 8 MB
	0x00800000 + 0x00400000, // 12 MB
	0x01000000, // 16 MB
	0x01000000 + 0x00800000, // 24 MB
	0x02000000, // 32 MB
	0x04000000}; // 64 MB

/* SD SSR UHS Speed Grade values */
#define SD_SSR_UHS_SPEED_GRADE_0	0 // Less than 10MB/sec
#define SD_SSR_UHS_SPEED_GRADE_1	1 // 10MB/sec and above

/* SD SSR UHS AU Size values */
const uint32_t SD_SSR_UHS_AU_SIZE_VALUES[] = {
	0, // Not Defined
	0, // Not Used
	0, // Not Used
	0, // Not Used
	0, // Not Used
	0, // Not Used
	0, // Not Used
	0x00100000, // 1 MB
	0x00200000, // 2 MB
	0x00400000, // 4 MB
	0x00800000, // 8 MB
	0x00800000 + 0x00400000, // 12 MB
	0x01000000, // 16 MB
	0x01000000 + 0x00800000, // 24 MB
	0x02000000, // 32 MB
	0x04000000}; // 64 MB

/* SD Switch Status values */
/* SD Switch Fields */
#define SD_SWITCH_MAXIMUM_CURRENT	1
#define SD_SWITCH_GROUP6_SUPPORT	2
#define SD_SWITCH_GROUP5_SUPPORT	3
#define SD_SWITCH_GROUP4_SUPPORT	4
#define SD_SWITCH_GROUP3_SUPPORT	5
#define SD_SWITCH_GROUP2_SUPPORT	6
#define SD_SWITCH_GROUP1_SUPPORT	7
#define SD_SWITCH_GROUP6_SELECTION	8
#define SD_SWITCH_GROUP5_SELECTION	9
#define SD_SWITCH_GROUP4_SELECTION	10
#define SD_SWITCH_GROUP3_SELECTION	11
#define SD_SWITCH_GROUP2_SELECTION	12
#define SD_SWITCH_GROUP1_SELECTION	13
#define SD_SWITCH_STRUCT_VERSION	14
#define SD_SWITCH_GROUP6_BUSY_STATUS	15
#define SD_SWITCH_GROUP5_BUSY_STATUS	16
#define SD_SWITCH_GROUP4_BUSY_STATUS	17
#define SD_SWITCH_GROUP3_BUSY_STATUS	18
#define SD_SWITCH_GROUP2_BUSY_STATUS	19
#define SD_SWITCH_GROUP1_BUSY_STATUS	20

/* SD Switch Access Mode (Bus Speed) Support (Group 1) */
#define SD_SWITCH_GROUP1_SDR12	(1 << 0)
#define SD_SWITCH_GROUP1_HS	(1 << 1)
#define SD_SWITCH_GROUP1_SDR25	(1 << 1)
#define SD_SWITCH_GROUP1_SDR50	(1 << 2)
#define SD_SWITCH_GROUP1_SDR104	(1 << 3)
#define SD_SWITCH_GROUP1_DDR50	(1 << 4)

/* SD Switch Driver Strength Support (Group 3) */
#define SD_SWITCH_GROUP3_TYPE_B	(1 << 0)
#define SD_SWITCH_GROUP3_TYPE_A	(1 << 1)
#define SD_SWITCH_GROUP3_TYPE_C	(1 << 2)
#define SD_SWITCH_GROUP3_TYPE_D	(1 << 3)

/* SD Switch Structure Versions */
#define SD_SWITCH_STRUCT_VER_0	0 // Bits 511:376 are defined (SD_SWITCH_MAXIMUM_CURRENT to SD_SWITCH_GROUP1_SELECTION)
#define SD_SWITCH_STRUCT_VER_1	1 // Bits 511:272 are defined (SD_SWITCH_MAXIMUM_CURRENT to SD_SWITCH_GROUP1_BUSY_STATUS

/* SD Configuration Register (SCR) values */
/* SD SCR Fields */
#define SD_SCR_STRUCTURE	1
#define SD_SCR_SD_SPEC	2
#define SD_SCR_DATA_STAT_AFTER_ERASE	3
#define SD_SCR_SD_SECURITY	4
#define SD_SCR_SD_BUS_WIDTHS	5
#define SD_SCR_SD_SPEC3	6
#define SD_SCR_EX_SECURITY	7
#define SD_SCR_SD_SPEC4	8
#define SD_SCR_CMD_SUPPORT	9

/* SD SCR Structure values */
#define SD_SCR_STRUCT_VER_1_0	0 // Valid for system specification 1.01 - 4.0

/* SD SCR Spec Version values */
#define SD_SCR_SPEC_VER_0	0 // Implements system specification 1.0 - 1.01
#define SD_SCR_SPEC_VER_1	1 // Implements system specification 1.10
#define SD_SCR_SPEC_VER_2	2 // Implements system specification 2.00-4.0X

/* SD SCR Security values */
#define SD_SCR_SECURITY_VER_0	0 // No Security
#define SD_SCR_SECURITY_VER_2	2 // SDSC Card (Security Version 1.01)
#define SD_SCR_SECURITY_VER_3	3 // SDHC Card (Security Version 2.00)
#define SD_SCR_SECURITY_VER_4	4 // SDXC Card (Security Version 3.xx)

/* SD SCR Bus Width values */
#define SD_SCR_BUS_WIDTH_1	(1 << 0) // 1 bit (DAT0)
#define SD_SCR_BUS_WIDTH_4	(1 << 2) // 4 bit (DAT0-3)

/* SD SCR Extended Security values */
#define SD_SCR_EX_SECURITY_VER_0	0 // Extended Security is not supported

/* SD SCR Command Support values */
#define SD_SCR_CMD20_SUPPORT	(1 << 0) // Mandatory for SDXC card
#define SD_SCR_CMD23_SUPPORT	(1 << 1) // Mandatory for UHS104 card
#define SD_SCR_CMD48_49_SUPPORT	(1 << 2) // Optional
#define SD_SCR_CMD58_59_SUPPORT	(1 << 3) // Optional (If CMD58/59 is supported, CMD48/49 shall be supported)

/* ============================================================================== */
/* SDIO specific constants */
/* SDIO Function States */
#define SDIO_STATE_DETACHED	0
#define SDIO_STATE_DETACHING	1
#define SDIO_STATE_ATTACHING	2
#define SDIO_STATE_ATTACHED	3

#define SDIO_STATE_MAX	3

/* SDIO Function Status */
#define SDIO_STATUS_UNBOUND	0
#define SDIO_STATUS_BOUND	1

#define SDIO_STATUS_MAX	1

/* SDIO Commands (From: /include/linux/mmc/sdio.h) */
#define SDIO_CMD_SEND_OP_COND	5
#define SDIO_CMD_RW_DIRECT	52
#define SDIO_CMD_RW_EXTENDED	53

/* SDIO_CMD_RW_DIRECT argument format:
       [31] R/W flag
       [30:28] Function number
       [27] RAW flag
       [25:9] Register address
       [7:0] Data */

/* SDIO_CMD_RW_EXTENDED argument format:
       [31] R/W flag
       [30:28] Function number
       [27] Block mode
       [26] Increment address
       [25:9] Register address
       [8:0] Byte/block count */


/* SDIO Response Values (From: /include/linux/mmc/sdio.h) */
/* R4 */
#define SDIO_RSP_R4_18V_PRESENT	(1 << 24)
#define SDIO_RSP_R4_MEMORY_PRESENT	(1 << 27)

/* R5 */
#define SDIO_RSP_R5_COM_CRC_ERROR	(1 << 15)
#define SDIO_RSP_R5_ILLEGAL_COMMAND	(1 << 14)
#define SDIO_RSP_R5_ERROR	(1 << 11)
#define SDIO_RSP_R5_FUNCTION_NUMBER	(1 << 9)
#define SDIO_RSP_R5_OUT_OF_RANGE	(1 << 8)
// SDIO_RSP_R5_STATUS(x)		(x & 0xCB00)
// SDIO_RSP_R5_IO_CURRENT_STATE(x)	((x & 0x3000) >> 12) /* s, b */

/* SDIO status in R5
  Type
	e : error bit
	s : status bit
	r : detected and set for the actual command response
	x : detected and set during command execution. the host must poll the card by sending status command in order to read these bits.
  Clear condition
	a : according to the card state
	b : always related to the previous command. Reception of a valid command will clear it (with a delay of one command)
	c : clear by read */

/* SDIO Card Common Control Registers (CCCR) */
#define SDIO_CCCR_CCCR	0x00
#define SDIO_CCCR_SD	0x01
#define SDIO_CCCR_IOEx	0x02
#define SDIO_CCCR_IORx	0x03
#define SDIO_CCCR_IENx	0x04 // Function/Master Interrupt Enable
#define SDIO_CCCR_INTx	0x05 // Function Interrupt Pending
#define SDIO_CCCR_ABORT	0x06 // Function abort/card reset
#define SDIO_CCCR_IF	0x07 // Bus interface controls
#define SDIO_CCCR_CAPS	0x08
#define SDIO_CCCR_CIS	0x09 // Common CIS pointer (3 bytes)
/* Following 4 regs are valid only if SBS is set */
#define SDIO_CCCR_SUSPEND	0x0c
#define SDIO_CCCR_SELx	0x0d
#define SDIO_CCCR_EXECx	0x0e
#define SDIO_CCCR_READYx	0x0f
#define SDIO_CCCR_BLKSIZE	0x10
#define SDIO_CCCR_POWER	0x12
#define SDIO_CCCR_SPEED	0x13
#define SDIO_CCCR_UHS	0x14
#define SDIO_CCCR_DRIVE_STRENGTH	0x15

/* SDIO CCCR CCCR Register values */
#define SDIO_CCCR_REV_1_00	0 // CCCR/FBR Version 1.00
#define SDIO_CCCR_REV_1_10	1 // CCCR/FBR Version 1.10
#define SDIO_CCCR_REV_1_20	2 // CCCR/FBR Version 1.20
#define SDIO_CCCR_REV_3_00	3 // CCCR/FBR Version 3.00

#define SDIO_SDIO_REV_1_00	0 // SDIO Spec Version 1.00
#define SDIO_SDIO_REV_1_10	1 // SDIO Spec Version 1.10
#define SDIO_SDIO_REV_1_20	2 // SDIO Spec Version 1.20
#define SDIO_SDIO_REV_2_00	3 // SDIO Spec Version 2.00
#define SDIO_SDIO_REV_3_00	4 // SDIO Spec Version 3.00

/* SDIO CCCR SD Register values */
#define SDIO_SD_REV_1_01	0 // SD Physical Spec Version 1.01
#define SDIO_SD_REV_1_10	1 // SD Physical Spec Version 1.10
#define SDIO_SD_REV_2_00	2 // SD Physical Spec Version 2.00
#define SDIO_SD_REV_3_00	3 // SD Physical Spev Version 3.00

/* SDIO CCCR IF Register values */
#define SDIO_BUS_WIDTH_MASK	0x03 // data bus width setting
#define SDIO_BUS_WIDTH_1BIT	0x00
#define SDIO_BUS_WIDTH_RESERVED	0x01
#define SDIO_BUS_WIDTH_4BIT	0x02
#define SDIO_BUS_ECSI	0x20 // Enable continuous SPI interrupt
#define SDIO_BUS_SCSI	0x40 // Support continuous SPI interrupt

#define SDIO_BUS_ASYNC_INT	0x20

#define SDIO_BUS_CD_DISABLE	0x80 // disable pull-up on DAT3 (pin 1)

/* SDIO CCCR CAPS Register values */
#define SDIO_CCCR_CAP_SDC	0x01 // Can do CMD52 while data transfer
#define SDIO_CCCR_CAP_SMB	0x02 // Can do multi-block xfers (CMD53)
#define SDIO_CCCR_CAP_SRW	0x04 // Supports read-wait protocol
#define SDIO_CCCR_CAP_SBS	0x08 // Supports suspend/resume
#define SDIO_CCCR_CAP_S4MI	0x10 // Interrupt during 4-bit CMD53
#define SDIO_CCCR_CAP_E4MI	0x20 // Enable ints during 4-bit CMD53
#define SDIO_CCCR_CAP_LSC	0x40 // Low speed card
#define SDIO_CCCR_CAP_4BLS	0x80 // 4 bit low speed card

/* SDIO CCCR POWER Register values */
#define SDIO_POWER_SMPC	0x01 // Supports Master Power Control
#define SDIO_POWER_EMPC	0x02 // Enable Master Power Control

/* SDIO CCCR SPEED Register values */
#define SDIO_SPEED_SHS	0x01 // Supports High-Speed mode
#define SDIO_SPEED_BSS_SHIFT	1
#define SDIO_SPEED_BSS_MASK	(7 << SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_SDR12	(0 << SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_SDR25	(1 << SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_SDR50	(2 << SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_SDR104	(3 << SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_DDR50	(4 << SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_EHS	SDIO_SPEED_SDR25 // Enable High-Speed

/* SDIO CCCR UHS Register values */
#define SDIO_UHS_SDR50	0x01
#define SDIO_UHS_SDR104	0x02
#define SDIO_UHS_DDR50	0x04

/* SDIO CCCR DRIVE STRENGTH Register values */
#define SDIO_SDTx_MASK	0x07
#define SDIO_DRIVE_SDTA	(1 << 0)
#define SDIO_DRIVE_SDTC	(1 << 1)
#define SDIO_DRIVE_SDTD	(1 << 2)
#define SDIO_DRIVE_DTSx_MASK	0x03
#define SDIO_DRIVE_DTSx_SHIFT	4
#define SDIO_DTSx_SET_TYPE_B	(0 << SDIO_DRIVE_DTSx_SHIFT)
#define SDIO_DTSx_SET_TYPE_A	(1 << SDIO_DRIVE_DTSx_SHIFT)
#define SDIO_DTSx_SET_TYPE_C	(2 << SDIO_DRIVE_DTSx_SHIFT)
#define SDIO_DTSx_SET_TYPE_D	(3 << SDIO_DRIVE_DTSx_SHIFT)

/* SDIO Function Basic Registers (FBR) */
#define SDIO_FBR_BASE(f)	((f) * 0x100) /* base of function f's FBRs */
#define SDIO_FBR_STD_IF	0x00
#define SDIO_FBR_STD_IF_EXT	0x01
#define SDIO_FBR_POWER	0x02
#define SDIO_FBR_CIS	0x09 // CIS pointer (3 bytes)
#define SDIO_FBR_CSA	0x0C // CSA pointer (3 bytes)
#define SDIO_FBR_CSA_DATA	0x0F
#define SDIO_FBR_BLKSIZE	0x10 // Block size (2 bytes)

/* SDIO FBR IF Register values */
#define SDIO_FBR_SUPPORTS_CSA	0x40 // Supports Code Storage Area
#define SDIO_FBR_ENABLE_CSA	0x80 // Enable Code Storage Area

/* SDIO FBR POWER Register values */
#define SDIO_FBR_POWER_SPS	0x01 // Supports Power Selection
#define SDIO_FBR_POWER_EPS	0x02 // Enable (low) Power Selection

/* SDIO Function Classes */
#define SDIO_CLASS_NONE	0x00 // Not a SDIO standard interface
#define SDIO_CLASS_UART	0x01 // Standard UART interface
#define SDIO_CLASS_BT_A	0x02 // Type-A BlueTooth std interface
#define SDIO_CLASS_BT_B	0x03 // Type-B BlueTooth std interface
#define SDIO_CLASS_GPS	0x04 // GPS standard interface
#define SDIO_CLASS_CAMERA	0x05 // Camera standard interface
#define SDIO_CLASS_PHS	0x06 // PHS standard interface
#define SDIO_CLASS_WLAN	0x07 // WLAN interface
#define SDIO_CLASS_ATA	0x08 // Embedded SDIO-ATA std interface
#define SDIO_CLASS_BT_AMP	0x09 // Type-A Bluetooth AMP interface

/* SDIO Vendors */
#define SDIO_VENDOR_ID_STE	0x0020
#define SDIO_VENDOR_ID_INTEL	0x0089
#define SDIO_VENDOR_ID_CGUYS	0x0092
#define SDIO_VENDOR_ID_TI	0x0097
#define SDIO_VENDOR_ID_ATHEROS	0x0271
#define SDIO_VENDOR_ID_BROADCOM	0x02d0
#define SDIO_VENDOR_ID_MARVELL	0x02df
#define SDIO_VENDOR_ID_MEDIATEK	0x037a
#define SDIO_VENDOR_ID_MICROCHIP_WILC	0x0296
#define SDIO_VENDOR_ID_SIANO	0x039a
#define SDIO_VENDOR_ID_RSI	0x041b
#define SDIO_VENDOR_ID_TI_WL1251	0x104c

/* SDIO Devices */
#define SDIO_DEVICE_ID_STE_CW1200	0x2280

#define SDIO_DEVICE_ID_INTEL_IWMC3200WIMAX	0x1402
#define SDIO_DEVICE_ID_INTEL_IWMC3200WIFI	0x1403
#define SDIO_DEVICE_ID_INTEL_IWMC3200TOP	0x1404
#define SDIO_DEVICE_ID_INTEL_IWMC3200GPS	0x1405
#define SDIO_DEVICE_ID_INTEL_IWMC3200BT	0x1406
#define SDIO_DEVICE_ID_INTEL_IWMC3200WIMAX_2G5	0x1407

#define SDIO_DEVICE_ID_CGUYS_EW_CG1102GC	0x0004

#define SDIO_DEVICE_ID_TI_WL1271	0x4076

#define SDIO_DEVICE_ID_ATHEROS_AR6003_00	0x0300
#define SDIO_DEVICE_ID_ATHEROS_AR6003_01	0x0301
#define SDIO_DEVICE_ID_ATHEROS_AR6004_00	0x0400
#define SDIO_DEVICE_ID_ATHEROS_AR6004_01	0x0401
#define SDIO_DEVICE_ID_ATHEROS_AR6004_02	0x0402
#define SDIO_DEVICE_ID_ATHEROS_AR6004_18	0x0418
#define SDIO_DEVICE_ID_ATHEROS_AR6004_19	0x0419
#define SDIO_DEVICE_ID_ATHEROS_AR6005	0x050A
#define SDIO_DEVICE_ID_ATHEROS_QCA9377	0x0701

#define SDIO_DEVICE_ID_BROADCOM_NINTENDO_WII	0x044b
#define SDIO_DEVICE_ID_BROADCOM_43241	0x4324
#define SDIO_DEVICE_ID_BROADCOM_4329	0x4329
#define SDIO_DEVICE_ID_BROADCOM_4330	0x4330
#define SDIO_DEVICE_ID_BROADCOM_4334	0x4334
#define SDIO_DEVICE_ID_BROADCOM_4335_4339	0x4335
#define SDIO_DEVICE_ID_BROADCOM_4339	0x4339
#define SDIO_DEVICE_ID_BROADCOM_4345	0x4345
#define SDIO_DEVICE_ID_BROADCOM_4354	0x4354
#define SDIO_DEVICE_ID_BROADCOM_CYPRESS_89359	0x4355
#define SDIO_DEVICE_ID_BROADCOM_4356	0x4356
#define SDIO_DEVICE_ID_BROADCOM_4359	0x4359
#define SDIO_DEVICE_ID_BROADCOM_CYPRESS_4373	0x4373
#define SDIO_DEVICE_ID_BROADCOM_CYPRESS_43012	0xa804
#define SDIO_DEVICE_ID_BROADCOM_43143	0xa887
#define SDIO_DEVICE_ID_BROADCOM_43340	0xa94c
#define SDIO_DEVICE_ID_BROADCOM_43341	0xa94d
#define SDIO_DEVICE_ID_BROADCOM_43362	0xa962
#define SDIO_DEVICE_ID_BROADCOM_43364	0xa9a4
#define SDIO_DEVICE_ID_BROADCOM_43430	0xa9a6
#define SDIO_DEVICE_ID_BROADCOM_43455	0xa9bf

#define SDIO_DEVICE_ID_MARVELL_LIBERTAS	0x9103
#define SDIO_DEVICE_ID_MARVELL_8688_WLAN	0x9104
#define SDIO_DEVICE_ID_MARVELL_8688_BT	0x9105
#define SDIO_DEVICE_ID_MARVELL_8786_WLAN	0x9116
#define SDIO_DEVICE_ID_MARVELL_8787_WLAN	0x9119
#define SDIO_DEVICE_ID_MARVELL_8787_BT	0x911a
#define SDIO_DEVICE_ID_MARVELL_8787_BT_AMP	0x911b
#define SDIO_DEVICE_ID_MARVELL_8797_F0	0x9128
#define SDIO_DEVICE_ID_MARVELL_8797_WLAN	0x9129
#define SDIO_DEVICE_ID_MARVELL_8797_BT	0x912a
#define SDIO_DEVICE_ID_MARVELL_8897_WLAN	0x912d
#define SDIO_DEVICE_ID_MARVELL_8897_BT	0x912e
#define SDIO_DEVICE_ID_MARVELL_8887_F0	0x9134
#define SDIO_DEVICE_ID_MARVELL_8887_WLAN	0x9135
#define SDIO_DEVICE_ID_MARVELL_8887_BT	0x9136
#define SDIO_DEVICE_ID_MARVELL_8801_WLAN	0x9139
#define SDIO_DEVICE_ID_MARVELL_8997_F0	0x9140
#define SDIO_DEVICE_ID_MARVELL_8997_WLAN	0x9141
#define SDIO_DEVICE_ID_MARVELL_8997_BT	0x9142
#define SDIO_DEVICE_ID_MARVELL_8977_WLAN	0x9145
#define SDIO_DEVICE_ID_MARVELL_8977_BT	0x9146
#define SDIO_DEVICE_ID_MARVELL_8987_WLAN	0x9149
#define SDIO_DEVICE_ID_MARVELL_8987_BT	0x914a

#define SDIO_DEVICE_ID_MEDIATEK_MT7663	0x7663
#define SDIO_DEVICE_ID_MEDIATEK_MT7668	0x7668

#define SDIO_DEVICE_ID_MICROCHIP_WILC1000	0x5347

#define SDIO_DEVICE_ID_SIANO_NOVA_B0	0x0201
#define SDIO_DEVICE_ID_SIANO_NICE	0x0202
#define SDIO_DEVICE_ID_SIANO_VEGA_A0	0x0300
#define SDIO_DEVICE_ID_SIANO_VENICE	0x0301
#define SDIO_DEVICE_ID_SIANO_MING	0x0302
#define SDIO_DEVICE_ID_SIANO_PELE	0x0500
#define SDIO_DEVICE_ID_SIANO_RIO	0x0600
#define SDIO_DEVICE_ID_SIANO_DENVER_2160	0x0700
#define SDIO_DEVICE_ID_SIANO_DENVER_1530	0x0800
#define SDIO_DEVICE_ID_SIANO_NOVA_A0	0x1100
#define SDIO_DEVICE_ID_SIANO_STELLAR	0x5347

#define SDIO_DEVICE_ID_TI_WL1251	0x9066

/* SDIO CIS Tuple Codes */
#define CISTPL_NULL	0x00
#define CISTPL_CHECKSUM	0x10
#define CISTPL_VERS_1	0x15
#define CISTPL_ALTSTR	0x16
#define CISTPL_MANFID	0x20
#define CISTPL_FUNCID	0x21
#define CISTPL_FUNCE	0x22
#define CISTPL_SDIO_STD	0x91
#define CISTPL_SDIO_EXT	0x92
#define CISTPL_END	0xFF

#define SDIO_MAX_FUNCTIONS	7

#define SDIO_READ_CIS_TIMEOUT_MS	(10 * 1000) // 10 seconds

/* ============================================================================== */
/* SDHCI specific constants */
#define SDHCI_NAME_PREFIX	"SDHCI" // Name prefix for SDHCI Devices

/* SDHCI Host Types */
#define SDHCI_TYPE_NONE	0
#define SDHCI_TYPE_MMC	1 // An MMC specification host controller
#define SDHCI_TYPE_SD	2 // An SD specification host controller
#define SDHCI_TYPE_MMCI	3 // An MMCI specification host controller

#define SDHCI_TYPE_MAX	3

/* SDHCI Host States */
#define SDHCI_STATE_DISABLED	0
#define SDHCI_STATE_ENABLED	1

#define SDHCI_STATE_MAX	1

/* SDHCI Host Flags */
#define SDHCI_FLAG_NONE	0x00000000
#define SDHCI_FLAG_SDMA	0x00000001 // Host Controller supports SDMA specification
#define SDHCI_FLAG_ADMA	0x00000002 // Host Controller supports ADMA specification
#define SDHCI_FLAG_SPI	0x00000004 // Host Controller uses SPI interface
#define SDHCI_FLAG_CRC_ENABLE	0x00000008
#define SDHCI_FLAG_NON_STANDARD	0x00000010 // Host Controller uses a non standard interface (not supporting SDHCI register layout)
#define SDHCI_FLAG_AUTO_CMD12	0x00000020 // Host Controller supports Auto CMD12 (Stop Transmission)
#define SDHCI_FLAG_AUTO_CMD23	0x00000040 // Host Controller supports Auto CMD23 (Set Block Count)
#define SDHCI_FLAG_64_BIT_DMA	0x00000080 // Host Controller supports 64-bit ADMA
#define SDHCI_FLAG_EXTERNAL_DMA	0x00000100 // Host Controller requires external DMA engine to perform transfers
#define SDHCI_FLAG_BUS_ADDRESSES	0x00000200 // Host Controller requires use of bus addresses for SDMA/ADMA transfers

/* SDHCI Controller Registers */
#define SDHCI_DMA_ADDRESS	0x00
#define SDHCI_ARGUMENT2	SDHCI_DMA_ADDRESS
#define SDHCI_32BIT_BLK_CNT	SDHCI_DMA_ADDRESS
#define SDHCI_BLOCK_SIZE	0x04
#define SDHCI_BLOCK_COUNT	0x06
#define SDHCI_ARGUMENT	0x08
#define SDHCI_TRANSFER_MODE	0x0C
#define SDHCI_COMMAND	0x0E
#define SDHCI_RESPONSE	0x10
#define SDHCI_BUFFER	0x20
#define SDHCI_PRESENT_STATE	0x24
#define SDHCI_HOST_CONTROL	0x28
#define SDHCI_POWER_CONTROL	0x29
#define SDHCI_BLOCK_GAP_CONTROL	0x2A
#define SDHCI_WAKE_UP_CONTROL	0x2B
#define SDHCI_CLOCK_CONTROL	0x2C
#define SDHCI_TIMEOUT_CONTROL	0x2E
#define SDHCI_SOFTWARE_RESET	0x2F
#define SDHCI_INT_STATUS	0x30
#define SDHCI_INT_ENABLE	0x34
#define SDHCI_SIGNAL_ENABLE	0x38
#define SDHCI_AUTO_CMD_STATUS	0x3C // SDHCI_ACMD12_ERR
#define SDHCI_HOST_CONTROL2	0x3E
#define SDHCI_CAPABILITIES	0x40
#define SDHCI_CAPABILITIES_1	0x44
#define SDHCI_MAX_CURRENT	0x48
/* 4C-4F reserved for more max current */
#define SDHCI_SET_ACMD12_ERROR	0x50
#define SDHCI_SET_INT_ERROR	0x52
#define SDHCI_ADMA_ERROR	0x54
/* 55-57 reserved */
#define SDHCI_ADMA_ADDRESS	0x58
#define SDHCI_ADMA_ADDRESS_HI	0x5C
/* 5D-65 reserved */
#define SDHCI_PRESET_FOR_SDR12	0x66
#define SDHCI_PRESET_FOR_SDR25	0x68
#define SDHCI_PRESET_FOR_SDR50	0x6A
#define SDHCI_PRESET_FOR_SDR104	0x6C
#define SDHCI_PRESET_FOR_DDR50	0x6E
/* 6F-73 reserved */
#define SDHCI_PRESET_FOR_HS400	0x74 // Non-standard
/* 75-FB reserved */
#define SDHCI_SLOT_INT_STATUS	0xFC
#define SDHCI_HOST_VERSION	0xFE

/* SDHCI Transfer Modes */
#define SDHCI_TRNS_DMA	0x01
#define SDHCI_TRNS_BLK_CNT_EN	0x02
#define SDHCI_TRNS_AUTO_CMD12	0x04 // SDHCI_TRNS_ACMD12
#define SDHCI_TRNS_AUTO_CMD23	0x08
#define SDHCI_TRNS_AUTO_SEL	SDHCI_TRNS_AUTO_CMD12 | SDHCI_TRNS_AUTO_CMD23
#define SDHCI_TRNS_READ	0x10
#define SDHCI_TRNS_MULTI	0x20

/* SDHCI Command Values */
#define SDHCI_CMD_RESP_MASK	0x03
#define SDHCI_CMD_CRC	0x08
#define SDHCI_CMD_INDEX	0x10
#define SDHCI_CMD_DATA	0x20
#define SDHCI_CMD_ABORTCMD	0xC0

/* SDHCI Command Response Values */
#define SDHCI_CMD_RESP_NONE	0x00
#define SDHCI_CMD_RESP_LONG	0x01
#define SDHCI_CMD_RESP_SHORT	0x02
#define SDHCI_CMD_RESP_SHORT_BUSY	0x03

/* SDHCI Present State Values */
#define SDHCI_CMD_INHIBIT	0x00000001
#define SDHCI_DATA_INHIBIT	0x00000002
#define SDHCI_DOING_WRITE	0x00000100
#define SDHCI_DOING_READ	0x00000200
#define SDHCI_SPACE_AVAILABLE	0x00000400
#define SDHCI_DATA_AVAILABLE	0x00000800
#define SDHCI_CARD_PRESENT	0x00010000
#define SDHCI_CARD_STATE_STABLE	0x00020000 // SDHCI_CD_STABLE
#define SDHCI_CARD_DETECT_PIN_LEVEL	0x00040000 // SDHCI_CD_LVL
#define SDHCI_WRITE_PROTECT	0x00080000 // Set if Write Enabled / Clear if Write Protected
#define SDHCI_DATA_LEVEL_MASK	0x00F00000 // SDHCI_DATA_LVL_MASK
#define SDHCI_DATA_0_LEVEL_MASK	0x00100000 // SDHCI_DATA_0_LVL_MASK
#define SDHCI_CMD_LEVEL	0x01000000 // SDHCI_CMD_LVL

/* SDHCI Host Control Values */
#define SDHCI_CTRL_LED	0x01
#define SDHCI_CTRL_4BITBUS	0x02
#define SDHCI_CTRL_HISPD	0x04
#define SDHCI_CTRL_DMA_MASK	0x18
#define SDHCI_CTRL_SDMA	0x00
#define SDHCI_CTRL_ADMA1	0x08
#define SDHCI_CTRL_ADMA32	0x10
#define SDHCI_CTRL_ADMA64	0x18
#define SDHCI_CTRL_ADMA3	0x18
#define SDHCI_CTRL_8BITBUS	0x20
#define SDHCI_CTRL_CD_TEST_INS	0x40
#define SDHCI_CTRL_CD_TEST	0x80

/* SDHCI Power Control Values */
#define SDHCI_POWER_ON	0x01
#define SDHCI_POWER_180	0x0A
#define SDHCI_POWER_300	0x0C
#define SDHCI_POWER_330	0x0E

/* SDHCI Wakeup Control Values */
#define SDHCI_WAKE_ON_INT	0x01
#define SDHCI_WAKE_ON_INSERT	0x02
#define SDHCI_WAKE_ON_REMOVE	0x04

/* SDHCI Clock Control Values */
#define SDHCI_DIVIDER_SHIFT	8
#define SDHCI_DIVIDER_HI_SHIFT	6
#define SDHCI_DIV_MASK	0xFF
#define SDHCI_DIV_MASK_LEN	8
#define SDHCI_DIV_HI_MASK	0x0300
#define SDHCI_PROG_CLOCK_MODE	0x0020
#define SDHCI_CLOCK_CARD_EN	0x0004
#define SDHCI_CLOCK_PLL_EN	0x0008
#define SDHCI_CLOCK_INT_STABLE	0x0002
#define SDHCI_CLOCK_INT_EN	0x0001

/* SDHCI Software Reset Values */
#define SDHCI_RESET_ALL	0x01
#define SDHCI_RESET_CMD	0x02
#define SDHCI_RESET_DATA	0x04

/* SDHCI Interrupt Values */
#define SDHCI_INT_RESPONSE	0x00000001
#define SDHCI_INT_DATA_END	0x00000002
#define SDHCI_INT_BLK_GAP	0x00000004
#define SDHCI_INT_DMA_END	0x00000008
#define SDHCI_INT_SPACE_AVAIL	0x00000010
#define SDHCI_INT_DATA_AVAIL	0x00000020
#define SDHCI_INT_CARD_INSERT	0x00000040
#define SDHCI_INT_CARD_REMOVE	0x00000080
#define SDHCI_INT_CARD_INT	0x00000100
#define SDHCI_INT_RETUNE	0x00001000
#define SDHCI_INT_CQE	0x00004000
#define SDHCI_INT_ERROR	0x00008000
#define SDHCI_INT_TIMEOUT	0x00010000
#define SDHCI_INT_CRC	0x00020000
#define SDHCI_INT_END_BIT	0x00040000
#define SDHCI_INT_INDEX	0x00080000
#define SDHCI_INT_DATA_TIMEOUT	0x00100000
#define SDHCI_INT_DATA_CRC	0x00200000
#define SDHCI_INT_DATA_END_BIT	0x00400000
#define SDHCI_INT_BUS_POWER	0x00800000
#define SDHCI_INT_AUTO_CMD_ERR	0x01000000 // SDHCI_INT_ACMD12ERR
#define SDHCI_INT_ADMA_ERROR	0x02000000

#define SDHCI_INT_NORMAL_MASK	0x00007FFF
#define SDHCI_INT_ERROR_MASK	0xFFFF8000

#define SDHCI_INT_CMD_MASK	(SDHCI_INT_RESPONSE | SDHCI_INT_TIMEOUT | SDHCI_INT_CRC | SDHCI_INT_END_BIT | SDHCI_INT_INDEX | SDHCI_INT_AUTO_CMD_ERR)
#define SDHCI_INT_DATA_MASK	(SDHCI_INT_DATA_END | SDHCI_INT_DMA_END | SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL | SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_END_BIT | SDHCI_INT_ADMA_ERROR | SDHCI_INT_BLK_GAP)
#define SDHCI_INT_ALL_MASK	(LongWord(-1))

#define SDHCI_CQE_INT_ERR_MASK	(SDHCI_INT_ADMA_ERROR | SDHCI_INT_BUS_POWER | SDHCI_INT_DATA_END_BIT | SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CRC | SDHCI_INT_TIMEOUT)
#define SDHCI_CQE_INT_MASK	(SDHCI_CQE_INT_ERR_MASK | SDHCI_INT_CQE)

/* SDHCI Auto CMD Status Values */
#define SDHCI_AUTO_CMD_TIMEOUT	0x00000002
#define SDHCI_AUTO_CMD_CRC	0x00000004
#define SDHCI_AUTO_CMD_END_BIT	0x00000008
#define SDHCI_AUTO_CMD_INDEX	0x00000010

/* SDHCI Host Control 2 Values */
#define SDHCI_CTRL_UHS_MASK	0x0007
#define SDHCI_CTRL_UHS_SDR12	0x0000
#define SDHCI_CTRL_UHS_SDR25	0x0001
#define SDHCI_CTRL_UHS_SDR50	0x0002
#define SDHCI_CTRL_UHS_SDR104	0x0003
#define SDHCI_CTRL_UHS_DDR50	0x0004
#define SDHCI_CTRL_HS400	0x0005 // Non-standard
#define SDHCI_CTRL_VDD_180	0x0008
#define SDHCI_CTRL_DRV_TYPE_MASK	0x0030
#define SDHCI_CTRL_DRV_TYPE_B	0x0000
#define SDHCI_CTRL_DRV_TYPE_A	0x0010
#define SDHCI_CTRL_DRV_TYPE_C	0x0020
#define SDHCI_CTRL_DRV_TYPE_D	0x0030
#define SDHCI_CTRL_EXEC_TUNING	0x0040
#define SDHCI_CTRL_TUNED_CLK	0x0080
#define SDHCI_CMD23_ENABLE	0x0800
#define SDHCI_CTRL_V4_MODE	0x1000
#define SDHCI_CTRL_64BIT_ADDR	0x2000
#define SDHCI_CTRL_PRESET_VAL_ENABLE	0x8000

/* SDHCI Capabilities Values */
#define SDHCI_TIMEOUT_CLK_MASK	0x0000003F
#define SDHCI_TIMEOUT_CLK_SHIFT	0
#define SDHCI_TIMEOUT_CLK_UNIT	0x00000080
#define SDHCI_CLOCK_BASE_MASK	0x00003F00
#define SDHCI_CLOCK_V3_BASE_MASK	0x0000FF00
#define SDHCI_CLOCK_BASE_SHIFT	8
#define SDHCI_CLOCK_BASE_MULTIPLIER	1000000
#define SDHCI_MAX_BLOCK_MASK	0x00030000
#define SDHCI_MAX_BLOCK_SHIFT	16
#define SDHCI_CAN_DO_8BIT	0x00040000
#define SDHCI_CAN_DO_ADMA2	0x00080000
#define SDHCI_CAN_DO_ADMA1	0x00100000
#define SDHCI_CAN_DO_HISPD	0x00200000
#define SDHCI_CAN_DO_SDMA	0x00400000
#define SDHCI_CAN_VDD_330	0x01000000
#define SDHCI_CAN_VDD_300	0x02000000
#define SDHCI_CAN_VDD_180	0x04000000
#define SDHCI_CAN_64BIT_V4	0x08000000
#define SDHCI_CAN_64BIT	0x10000000

/* SDHCI Capabilities 1 Values */
#define SDHCI_SUPPORT_SDR50	0x00000001
#define SDHCI_SUPPORT_SDR104	0x00000002
#define SDHCI_SUPPORT_DDR50	0x00000004
#define SDHCI_DRIVER_TYPE_A	0x00000010
#define SDHCI_DRIVER_TYPE_C	0x00000020
#define SDHCI_DRIVER_TYPE_D	0x00000040
#define SDHCI_RETUNING_TIMER_COUNT_MASK	0x00000F00 // GENMASK(11,8)
#define SDHCI_USE_SDR50_TUNING	0x00002000
#define SDHCI_RETUNING_MODE_MASK	0x0000C000 // GENMASK(15,14)
#define SDHCI_CLOCK_MUL_MASK	0x00FF0000 // GENMASK(23,16)
#define SDHCI_CAN_DO_ADMA3	0x08000000
#define SDHCI_SUPPORT_HS400	0x80000000 // Non-standard

/* SDHCI Max Current Values */
#define SDHCI_MAX_CURRENT_LIMIT	0x000000FF // GENMASK(7,0)
#define SDHCI_MAX_CURRENT_330_MASK	0x000000FF // GENMASK(7,0)
#define SDHCI_MAX_CURRENT_300_MASK	0x0000FF00 // GENMASK(15,8)
#define SDHCI_MAX_CURRENT_180_MASK	0x00FF0000 // GENMASK(23,16)
#define SDHCI_MAX_CURRENT_MULTIPLIER	4

/* SDHCI Preset Values */
#define SDHCI_PRESET_DRV_MASK	0x0000C000 // GENMASK(15,14)
#define SDHCI_PRESET_DRV_SHIFT	14
#define SDHCI_PRESET_CLKGEN_SEL	1 << 10 // BIT(10)
#define SDHCI_PRESET_SDCLK_FREQ_MASK	0x000003FF // GENMASK(9,0)

/* SDHCI Host Version Values */
#define SDHCI_VENDOR_VER_MASK	0xFF00
#define SDHCI_VENDOR_VER_SHIFT	8
#define SDHCI_SPEC_VER_MASK	0x00FF
#define SDHCI_SPEC_VER_SHIFT	0
#define SDHCI_SPEC_100	0
#define SDHCI_SPEC_200	1
#define SDHCI_SPEC_300	2
#define SDHCI_SPEC_400	3
#define SDHCI_SPEC_410	4
#define SDHCI_SPEC_420	5

/* SDHCI Clock Dividers */
#define SDHCI_MAX_CLOCK_DIV_SPEC_200	256
#define SDHCI_MAX_CLOCK_DIV_SPEC_300	2046

/* SDHCI Quirks/Bugs */
/* From Linux /include/linux/mmc/sdhci.h */
#define SDHCI_QUIRK_CLOCK_BEFORE_RESET	(1 << 0) // Controller doesn't honor resets unless we touch the clock register
#define SDHCI_QUIRK_FORCE_DMA	(1 << 1) // Controller has bad caps bits, but really supports DMA
#define SDHCI_QUIRK_NO_CARD_NO_RESET	(1 << 2) // Controller doesn't like to be reset when there is no card inserted
#define SDHCI_QUIRK_SINGLE_POWER_WRITE	(1 << 3) // Controller doesn't like clearing the power reg before a change
#define SDHCI_QUIRK_RESET_CMD_DATA_ON_IOS	(1 << 4) // Controller has flaky internal state so reset it on each ios change
#define SDHCI_QUIRK_BROKEN_DMA	(1 << 5) // Controller has an unusable DMA engine
#define SDHCI_QUIRK_BROKEN_ADMA	(1 << 6) // Controller has an unusable ADMA engine
#define SDHCI_QUIRK_32BIT_DMA_ADDR	(1 << 7) // Controller can only DMA from 32-bit aligned addresses
#define SDHCI_QUIRK_32BIT_DMA_SIZE	(1 << 8) // Controller can only DMA chunk sizes that are a multiple of 32 bits
#define SDHCI_QUIRK_32BIT_ADMA_SIZE	(1 << 9) // Controller can only ADMA chunks that are a multiple of 32 bits
#define SDHCI_QUIRK_RESET_AFTER_REQUEST	(1 << 10) // Controller needs to be reset after each request to stay stable
#define SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER	(1 << 11) // Controller needs voltage and power writes to happen separately
#define SDHCI_QUIRK_BROKEN_TIMEOUT_VAL	(1 << 12) // Controller provides an incorrect timeout value for transfers
#define SDHCI_QUIRK_BROKEN_SMALL_PIO	(1 << 13) // Controller has an issue with buffer bits for small transfers
#define SDHCI_QUIRK_NO_BUSY_IRQ	(1 << 14) // Controller does not provide transfer-complete interrupt when not busy
#define SDHCI_QUIRK_BROKEN_CARD_DETECTION	(1 << 15) // Controller has unreliable card detection
#define SDHCI_QUIRK_INVERTED_WRITE_PROTECT	(1 << 16) // Controller reports inverted write-protect state
#define SDHCI_QUIRK_PIO_NEEDS_DELAY	(1 << 18) // Controller does not like fast PIO transfers
#define SDHCI_QUIRK_FORCE_BLK_SZ_2048	(1 << 20) // Controller has to be forced to use block size of 2048 bytes
#define SDHCI_QUIRK_NO_MULTIBLOCK	(1 << 21) // Controller cannot do multi-block transfers
#define SDHCI_QUIRK_FORCE_1_BIT_DATA	(1 << 22) // Controller can only handle 1-bit data transfers
#define SDHCI_QUIRK_DELAY_AFTER_POWER	(1 << 23) // Controller needs 10ms delay between applying power and clock
#define SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK	(1 << 24) // Controller uses SDCLK instead of TMCLK for data timeouts
#define SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN	(1 << 25) // Controller reports wrong base clock capability
#define SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC	(1 << 26) // Controller cannot support End Attribute in NOP ADMA descriptor
#define SDHCI_QUIRK_MISSING_CAPS	(1 << 27) // Controller is missing device caps. Use caps provided by host
#define SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12	(1 << 28) // Controller uses Auto CMD12 command to stop the transfer
#define SDHCI_QUIRK_NO_HISPD_BIT	(1 << 29) // Controller doesn't have HISPD bit field in HI-SPEED SD card
#define SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC	(1 << 30) // Controller treats ADMA descriptors with length 0000h incorrectly
#define SDHCI_QUIRK_UNSTABLE_RO_DETECT	(1 << 31) // The read-only detection via SDHCI_PRESENT_STATE register is unstable

/* SDHCI More Quirks/Bugs */
/* From Linux /include/linux/mmc/sdhci.h */
#define SDHCI_QUIRK2_HOST_OFF_CARD_ON	(1 << 0)
#define SDHCI_QUIRK2_HOST_NO_CMD23	(1 << 1)
#define SDHCI_QUIRK2_NO_1_8_V	(1 << 2) // The system physically doesn't support 1.8v, even if the host does
#define SDHCI_QUIRK2_PRESET_VALUE_BROKEN	(1 << 3)
#define SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON	(1 << 4)
#define SDHCI_QUIRK2_BROKEN_HOST_CONTROL	(1 << 5) // Controller has a non-standard host control register
#define SDHCI_QUIRK2_BROKEN_HS200	(1 << 6) // Controller does not support HS200
#define SDHCI_QUIRK2_BROKEN_DDR50	(1 << 7) // Controller does not support DDR50
#define SDHCI_QUIRK2_STOP_WITH_TC	(1 << 8) // Stop command (CMD12) can set Transfer Complete when not using MMC_RSP_BUSY
#define SDHCI_QUIRK2_BROKEN_64_BIT_DMA	(1 << 9) // Controller does not support 64-bit DMA
#define SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD	(1 << 10) // Need clear transfer mode register before send cmd
#define SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400	(1 << 11) // Capability register bit-63 indicates HS400 support
#define SDHCI_QUIRK2_TUNING_WORK_AROUND	(1 << 12) // Forced tuned clock
#define SDHCI_QUIRK2_SUPPORT_SINGLE	(1 << 13) // Disable the block count for single block transactions
#define SDHCI_QUIRK2_ACMD23_BROKEN	(1 << 14) // Controller broken with using ACMD23
#define SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN	(1 << 15) // Broken Clock divider zero in controller
#define SDHCI_QUIRK2_RSP_136_HAS_CRC	(1 << 16) // Controller has CRC in 136 bit Command Response
#define SDHCI_QUIRK2_DISABLE_HW_TIMEOUT	(1 << 17) // Disable HW timeout if the requested timeout is more than the maximum obtainable timeout
#define SDHCI_QUIRK2_USE_32BIT_BLK_CNT	(1 << 18) // 32-bit block count may not support eMMC where upper bits of CMD23 are used for other purposes
/* Support 16-bit block count by default otherwise, SDHCI_QUIRK2_USE_32BIT_BLK_CNT can be selected to use 32-bit block count */

/* SDHCI Host SDMA buffer boundary (Valid values from 4K to 512K in powers of 2) */
#define SDHCI_DEFAULT_BOUNDARY_SIZE	(512 * 1024) // Default to 512K boundary
#define SDHCI_DEFAULT_BOUNDARY_ARG	7 // (ilog2(SDHCI_DEFAULT_BOUNDARY_SIZE) - 12)

/* ADMA2 32-bit DMA descriptor size */
#define SDHCI_ADMA2_32_DESC_SIZE	8

/* ADMA2 data alignment */
#define SDHCI_ADMA2_ALIGN	4
#define SDHCI_ADMA2_MASK	(SDHCI_ADMA2_ALIGN - 1)

/* ADMA2 descriptor alignment */
#define SDHCI_ADMA2_DESC_ALIGN	8

/* ADMA2 64-bit DMA descriptor size */
#define SDHCI_ADMA2_64_DESC_SIZE	12
#define SDHCI_ADMA2_64_DESC_V4_SIZE	16 // Use 128-bit descriptor, if Host Version 4 Enable is set in the Host Control 2 register

/* ADMA2 descriptor attributes */
#define SDHCI_ADMA2_DESC_ATTR_VALID	0x01
#define SDHCI_ADMA2_DESC_ATTR_END	0x02
#define SDHCI_ADMA2_DESC_ATTR_INT	0x04
#define SDHCI_ADMA2_DESC_ATTR_NOP	0x00
#define SDHCI_ADMA2_DESC_ATTR_TRAN	0x20
#define SDHCI_ADMA2_DESC_ATTR_LINK	0x30

#define SDHCI_ADMA2_DESC_TRAN_VALID	SDHCI_ADMA2_DESC_ATTR_TRAN | SDHCI_ADMA2_DESC_ATTR_VALID // 0x21
#define SDHCI_ADMA2_DESC_NOP_END_VALID	SDHCI_ADMA2_DESC_ATTR_NOP | SDHCI_ADMA2_DESC_ATTR_END | SDHCI_ADMA2_DESC_ATTR_VALID // 0x3
#define SDHCI_ADMA2_DESC_END	SDHCI_ADMA2_DESC_ATTR_END // 0x2

/* SDHCI maximum segments (assuming a 512KB maximum request size and a minimum 4KB page size) */
#define SDHCI_MAX_SEGS	128

/* SDHCI Timeout Value */
#define SDHCI_TIMEOUT_VALUE	0x0E

/* ============================================================================== */
/* MMC specific types */

/* MMC Command */
typedef struct _MMC_DATA MMC_DATA;
typedef struct _MMC_COMMAND MMC_COMMAND;
struct _MMC_COMMAND
{
	// Command Properties
	uint16_t command;
	uint32_t argument;
	uint32_t responsetype;
	uint32_t response[4];
	uint32_t status;
	MMC_DATA *data;
    uint32_t timeout; // Milliseconds
	// Host Properties
	BOOL datacompleted;
	BOOL busycompleted;
	BOOL tuningcompleted;
	BOOL commandcompleted;
};

/* MMC Data */
struct _MMC_DATA
{
	// Data Properties
	void *data;
	uint32_t flags;
	uint32_t blocksize;
	uint32_t blockcount;
	// Host Properties
	uint32_t blockoffset;
	uint32_t blocksremaining;
	uint32_t bytesremaining;
	uint32_t bytestransfered;
};

/* MMC Card Identification Data (CID) */
typedef struct _MMC_CARD_IDENTIFICATION_DATA
{
	// Card Values
	uint8_t manufacturerid;
	uint16_t oemid;
	char productname[8]; // Max 0 to 6, 1 extra for null terminator
	uint8_t productrevision;
	uint8_t hardwarerevision;
	uint8_t firmwarerevision;
	uint32_t productserialnumber;
	uint8_t manufacturingmonth;
	uint16_t manufacturingyear;
	uint8_t crc; // CRC7 checksum
} MMC_CARD_IDENTIFICATION_DATA;

/* MMC Card Specific Data (CSD) */
typedef struct _MMC_CARD_SPECIFIC_SD_ERASE_DATA
{
	BOOL eraseblockenable; // Erase single block enable
	uint8_t sectorsize; // Erase sector size
} MMC_CARD_SPECIFIC_SD_ERASE_DATA;

typedef struct _MMC_CARD_SPECIFIC_MM_C22_ERASE_DATA
{
	uint8_t sectorsize; // Erase sector size
	uint8_t erasegroupsize; // Erase group size
} MMC_CARD_SPECIFIC_MM_C22_ERASE_DATA;

typedef struct _MMC_CARD_SPECIFIC_MM_C31_ERASE_DATA
{
	uint8_t erasegroupsize; // Erase group size
	uint8_t erasegroupmultiplier; // Erase group size multiplier
} MMC_CARD_SPECIFIC_MM_C31_ERASE_DATA;

typedef union _MMC_CARD_SPECIFIC_ERASE_DATA
{
	struct {
     MMC_CARD_SPECIFIC_MM_C22_ERASE_DATA MMC22;
    };
	struct {
     MMC_CARD_SPECIFIC_MM_C31_ERASE_DATA MMC31;
    };
	struct {
     MMC_CARD_SPECIFIC_SD_ERASE_DATA SD;
    };
} MMC_CARD_SPECIFIC_ERASE_DATA;

typedef struct _MMC_CARD_SPECIFIC_DATA MMC_CARD_SPECIFIC_DATA;
struct _MMC_CARD_SPECIFIC_DATA
{
	// Card Values
	uint8_t csdstructure; // CSD structure version
	uint8_t specversion; // System specification version
	//uint8_t taac; // Data read access-time-1
	//uint8_t nsac; // Data read access-time-2 in CLK cycles (NSAC*100)
	//uint8_t transferspeed; // Max. data transfer rate
	uint16_t ccc; // Card command classes
	uint8_t readblocklength; // Max. read data block length
	BOOL readblockpartial; // Partial blocks for read allowed
	BOOL writeblockmisalign; // Write block misalignment
	BOOL readblockmisalign; // Read block misalignment
	BOOL dsrimplemented; // DSR implemented
	uint16_t devicesize; // Device size
	uint8_t vddreadcurrentmin; // Max. read current @VDD min
	uint8_t vddreadcurrentmax; // Max. read current @VDD max
	uint8_t vddwritecurrentmin; // Max. write current @VDD min
	uint8_t vddwritecurrentmax; // Max. write current @VDD max
	uint8_t devicesizemultiplier; // Device size multiplier
	MMC_CARD_SPECIFIC_ERASE_DATA erase; // Erase group details
	uint8_t writeprotectgroupsize; // Write protect group size
	BOOL writeprotectgroupenable; // Write protect group enable
	uint8_t defaultecc; // Manufacturer default ECC
	uint8_t readtowritefactor; // Write speed factor
	uint8_t writeblocklength; // Max. write data block length
	BOOL writeblockpartial; // Partial blocks for write allowed
	BOOL contentprotectapplication; // Content protection application
	uint8_t fileformatgroup; // File format group
	BOOL copyflag; // Copy flag
	BOOL permanentwriteprotect; // Permanent write protection
	BOOL temporarywriteprotect; // Temporary write protection
	uint8_t fileformat; // File format
	uint8_t ecc; // ECC code
	uint8_t crc; // CRC
	// Calculated Values
	uint32_t dataaccesstime; // In Nanoseconds
	uint16_t dataaccessclocks; // In Clock cycles
	uint32_t datatransferrate; // In Hz
	uint32_t erasesize; // In Sectors
	uint32_t blocksize; // "Normalized" Block Size
	uint32_t blockcount; // In "Normalized" Blocks
	uint32_t blockshift; // "Normalized" Block Shift
};

typedef struct _MMC_EXTENDED_CARD_SPECIFIC_DATA MMC_EXTENDED_CARD_SPECIFIC_DATA;
struct _MMC_EXTENDED_CARD_SPECIFIC_DATA
{
	// Card Values
	uint8_t revision; // Extended CSD revision (192)
	uint8_t cachecontrol; // Control to turn the Cache ON/OFF (33)
	uint8_t poweroffnotification; // Power Off Notification (34)
	uint8_t partitionsupport; // Partitioning Support (160)
	uint8_t hardwareresetfunction; // H/W reset function (162])
	uint8_t writereliabilityparameter; // Write reliability parameter register (166])
	uint8_t rpmbsizemult; // RPMB Size Multiplier (168)
	uint8_t erasegroupdef; // High-density erase group definition (175)
	uint8_t partconfig; // Partition configuration (179)
	uint8_t erasedmemorycontent; // Erased memory content (181)
	uint8_t strobesupport; // Strobe Support (184)
	uint8_t csdstructure; // CSD STRUCTURE (194)
	uint8_t cardtype; // Device type (196)
	uint8_t driverstrength; // I/O Driver Strength (197)
	uint8_t outofinterrupttime; // Out-of-interrupt busy timing (198)
	uint8_t sectorcount[4]; // Sector Count (212)(4 bytes)
	uint8_t satimeout; // Sleep/awake timeout (217)
	uint8_t hcerasegapsize; // High-capacity write protect group size (221)
	uint8_t reliablesectors; // Reliable write sector count (222)
	uint8_t erasetimeoutmult; // High-capacity erase timeout (223)
	uint8_t hcerasegrpsize; // High-capacity erase unit size (224)
	uint8_t sectrimmult; // Secure TRIM Multiplier (229)
	uint8_t secerasemult; // Secure Erase Multiplier (230)
	uint8_t secfeaturesupport; // Secure Feature support (231)
	uint8_t trimmult; // TRIM Multiplier (232)
	uint8_t powerclass52mhz195; // Power class for 52 MHz at 1.95 V (200)
	uint8_t powerclass26mhz195; // Power class for 26 MHz at 1.95 V (201)
	uint8_t powerclass52mhz360; // Power class for 52 MHz at 3.6 V (202)
	uint8_t powerclass26mhz360; // Power class for 26 MHz at 3.6 V (203)
	uint8_t powerclass200mhz195; // Power class for 200MHz, at VCCQ = 1.3V, VCC = 3.6V (236)
	uint8_t powerclass200mhz360; // Power class for 200MHz at VCCQ = 1.95V, VCC = 3.6V (237)
	uint8_t powerclassddr52mhz195; // Power class for 52MHz, DDR at VCC = 1.95V (238)
	uint8_t powerclassddr52mhz360; // Power class for 52MHz, DDR at VCC = 3.6V (239)
	uint8_t powerclassddr200mhz360; // Power class for 200MHz, DDR at VCC = 3.6V (253)
	uint8_t bkopsstatus; // Background operations status (246)
	uint8_t firmwareversion[MMC_FIRMWARE_VERSION_LEN]; // (254) (8 bytes)
	uint8_t preendoflifeinfo; // Pre EOL information (267)
	uint8_t devicelifetimeestimatea; // Device life time estimation type A (268)
	uint8_t devicelifetimeestimateb; // Device life time estimation type B (269)
	uint8_t maxpackedwrites; // Max packed write commands (500)
	uint8_t maxpackedreads; // Max packed read commands (501])
	// Calculated Values
	uint32_t sectors;
	uint32_t sleepawaketime; // 100ns units
	uint32_t partitionswitchtime; // ms
	uint32_t genericcmd6time; // 10ms units
	uint32_t powerofflongtime; // ms
	uint32_t hcerasesize; // Sectors
	uint32_t hcerasetimeout; // Milliseconds
	uint32_t datasectorsize; // 512 bytes or 4KB
	uint32_t datatagunitsize;
	uint32_t hsmaxrate; // Hz
	uint32_t hs200maxrate; // Hz
	uint32_t availabletypes;
	uint64_t bootpartitionsize; // Bytes
	uint64_t enhancedareaoffset; // Bytes
	uint64_t enhancedareasize; // KB
	uint32_t cachesize; // KB
	BOOL partitionsettingcompleted; // Enable Bit
	uint32_t trimtimeout; // Milliseconds
	uint64_t partitionsizes[MMC_NUM_GP_PARTITION]; // Bytes
	uint32_t bootreadonlysupport; // Read Only Lock Support
	BOOL bootreadonlylockable;
	BOOL fieldfirmwareupdate; // Firmware upgrade support
	BOOL commandqueuesupport; // Command Queue supported
	uint32_t commandqueuedepth; // Command Queue depth
	BOOL backgroundoperations; // BKOPS Supported
	BOOL manualbkopsenable; // Manual BKOPS Supported
	BOOL autobkopsenable; // Auto BKOPS Supported
	BOOL hpi; // HPI (High Priority Interrupt) Supported
	BOOL hpienable; // HPI Enabled
	uint32_t hpicommand; // CMD used as HPI
	uint64_t rpmbsize; // Bytes
	BOOL enhancedrpmbsupport;
	uint8_t erasedbyte; // Value after Erase
	uint32_t featuresupport; // Version specific features (eg MMC_DISCARD_FEATURE)
};

/* SD Status Data (SSR) */
typedef struct _SD_STATUS_DATA SD_STATUS_DATA;
struct _SD_STATUS_DATA
{
	// Card Values
	uint8_t buswidth; // Shows the currently defined data bus width that was defined by SET_BUS_WIDTH command
	BOOL securedmode; // Card is in Secured Mode of operation (refer to the "Part 3 Security Specification")
	uint16_t cardtype; // In the future, the 8 LSBs will be used to define different variations of an SD Memory Card (Each bit will define different SD Types). The 8 MSBs will be used to define SD Cards that do not comply with the Physical Layer Specification
	uint32_t protectedsize; // Size of protected area
	uint8_t speedclass; // Speed Class of the card
	uint8_t performancemove; // Performance of move indicated by 1 [MB/s] step
	uint16_t erasesize; // Number of AUs to be erased at a time
	uint8_t erasetimeout; // Timeout value for erasing areas specified by UNIT_OF_ERASE_AU
	uint8_t eraseoffset; // Fixed offset value added to erase time
	uint8_t uhsspeedgrade; // Speed Grade for UHS mode
	// Calculated Values
	uint8_t allocationunitsize; // Size of Allocation Unit
	uint8_t uhsallocationunitsize; // Size of Allocation Unit for UHS mode
};

/* SD Switch Data */
typedef struct _SD_SWITCH_DATA SD_SWITCH_DATA;
struct _SD_SWITCH_DATA
{
	// Card Values
	uint16_t maximumcurrent; // Maximum Current/Power Consumption
	uint16_t group6support; // Support Bits of Functions in Function Group 6
	uint16_t group5support; // Support Bits of Functions in Function Group 5
	uint16_t group4support; // Support Bits of Functions in Function Group 4
	uint16_t group3support; // Support Bits of Functions in Function Group 3
	uint16_t group2support; // Support Bits of Functions in Function Group 2
	uint16_t group1support; // Support Bits of Functions in Function Group 1
	uint8_t group6selection; // Function Selection of Function Group 6
	uint8_t group5selection; // Function Selection of Function Group 5
	uint8_t group4selection; // Function Selection of Function Group 4
	uint8_t group3selection; // Function Selection of Function Group 3
	uint8_t group2selection; // Function Selection of Function Group 2
	uint8_t group1selection; // Function Selection of Function Group 1
	uint8_t structureversion; // Data Structure Version
	uint16_t group6busystatus; // Busy Status of functions in group 6
	uint16_t group5busystatus; // Busy Status of functions in group 5
	uint16_t group4busystatus; // Busy Status of functions in group 4
	uint16_t group3busystatus; // Busy Status of functions in group 3
	uint16_t group2busystatus; // Busy Status of functions in group 2
	uint16_t group1busystatus; // Busy Status of functions in group 1
};

/* SD Configuration Data (SCR) */
typedef struct _SD_CONFIGURATION_DATA SD_CONFIGURATION_DATA;
struct _SD_CONFIGURATION_DATA
{
	// Card Values
	uint8_t scrstructure; // SCR Structure version
	uint8_t specversion; // SD Memory Card - Spec. Version
	uint8_t dataaftererase; // Data status after erases
	uint8_t security; // CPRM Security Support
	uint8_t buswidths; // DAT Bus widths supported
	BOOL specversion3; // Spec. Version 3.00 or higher
	uint8_t extendedsecurity; // Extended Security Support
	BOOL specversion4; // Spec. Version 4.00 or higher
	uint8_t commandsupport; // Command Support bits
	// Calculated Values
	uint8_t erasedbyte; // Value after Erase
};

/* MMC Device */
typedef struct _MMC_DEVICE MMC_DEVICE;
typedef struct _SDIO_CCCR SDIO_CCCR; // Forward declared to satisfy MMCDevice
typedef struct _SDIO_CIS SDIO_CIS; // Forward declared to satisfy MMCDevice
typedef struct _SDIO_TUPLE SDIO_TUPLE; // Forward declared to satisfy MMCDevice
typedef struct _SDIO_FUNCTION SDIO_FUNCTION; // Forward declared to satisfy MMCDevice

/* MMC Enumeration Callback */
typedef uint32_t STDCALL (*mmc_enumerate_cb)(MMC_DEVICE *mmc, void *data);
/* MMC Notification Callback */
typedef uint32_t STDCALL (*mmc_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* MMC Device Methods */
typedef uint32_t STDCALL (*mmc_device_initialize_proc)(MMC_DEVICE *mmc);
typedef uint32_t STDCALL (*mmc_device_deinitialize_proc)(MMC_DEVICE *mmc);
typedef uint32_t STDCALL (*mmc_device_get_card_detect_proc)(MMC_DEVICE *mmc);
typedef uint32_t STDCALL (*mmc_device_get_write_protect_proc)(MMC_DEVICE *mmc);
typedef uint32_t STDCALL (*mmc_device_send_command_proc)(MMC_DEVICE *mmc, MMC_COMMAND *command);
typedef uint32_t STDCALL (*mmc_device_set_ios_proc)(MMC_DEVICE *mmc);

struct _MMC_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this MMC
	// MMC Properties
	uint32_t mmcid; // Unique Id of this MMC in the MMC table
	uint32_t mmcstate; // MMC state (eg MMC_STATE_INSERTED)
	mmc_device_initialize_proc deviceinitialize; // A Device specific DeviceInitialize method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_deinitialize_proc devicedeinitialize; // A Device specific DeviceDeinitialize method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_get_card_detect_proc devicegetcarddetect; // A Device specific DeviceGetCardDetect method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_get_write_protect_proc devicegetwriteprotect; // A Device specific DeviceGetWriteProtect method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_send_command_proc devicesendcommand; // A Device specific DeviceSendCommand method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_set_ios_proc devicesetios; // A Device specific DeviceSetIOS method implementing a standard MMC device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t commandcount;
	uint32_t commanderrors;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	uint32_t version;
	uint32_t clock;
	uint32_t timing;
	uint32_t buswidth;
	uint32_t drivertype;
	uint32_t signalvoltage;
	uint32_t voltages;
	uint32_t capabilities;
	uint32_t capabilities2;
	uint32_t erasesize; // Erase Size in Sectors
	uint32_t eraseshift;
	uint32_t eraseargument;
	uint32_t preferrederasesize; // Preferred Erase Size in Sectors
	LONGBOOL enhancedstrobe;
	// Register Properties
	uint32_t interfacecondition; // Interface Condition Result
	uint32_t operationcondition; // Operation Condition Register (OCR)
	uint32_t relativecardaddress; // Relative Card Address (RCA) (Word)
	uint32_t cardspecific[4]; // Card Specific Data (CSD)
	uint32_t cardidentification[4]; // Card Identification Data (CID)
	uint8_t *extendedcardspecific; // Extended Card Specific Data (EXTCSD)
	uint32_t cardstatus; // Card Status Register (CSR)
	uint32_t driverstage; // Driver Stage Register (DSR) (Word)
	uint32_t sdstatus[16]; // SD Status Register (SSR)
	uint32_t sdswitch[16]; // SD Switch Status
	uint32_t sdconfiguration[2]; // SD Configuration Register (SCR)
	// Configuration Properties
	MMC_CARD_SPECIFIC_DATA cardspecificdata;
	MMC_CARD_IDENTIFICATION_DATA cardidentificationdata;
	MMC_EXTENDED_CARD_SPECIFIC_DATA extendedcardspecificdata;
	SD_STATUS_DATA sdstatusdata;
	SD_SWITCH_DATA sdswitchdata;
	SD_CONFIGURATION_DATA sdconfigurationdata;
	// SDIO Properties
	SDIO_CCCR *cccr; // SDIO Common Card Register Information
	SDIO_CIS *cis; // SDIO Common CIS (Card Information Structure) Information
	SDIO_TUPLE *tuples; // SDIO CIS (Card Information Structure) tuples on this MMC
	uint32_t sdiocount; // SDIO function count for this MMC (Where Applicable)
	SDIO_FUNCTION *sdiofunctions[SDIO_MAX_FUNCTIONS]; // SDIO functions on this MMC (Where Applicable)
	SDIO_FUNCTION *sdiointerruptfunction; // SDIO function for all interrupts (If only one interrupt is registered)
	// Storage Properties
	STORAGE_DEVICE *storage; // The Storage entry for this MMC (Where Applicable)
	// Internal Properties
	MMC_DEVICE *prev; // Previous entry in MMC table
	MMC_DEVICE *next; // Next entry in MMC table
};

/* ============================================================================== */
/* SD specific types */

/* ============================================================================== */
/* SDIO specific types */
struct _SDIO_CCCR
{
	// SDIO Properties
	uint8_t cccrversion; // CCCR (Card Common Control Register) Version (00h)
	uint8_t sdioversion; // SDIO Specification Version (00h)
	uint8_t sdversion; // SD Specification Version (04h)
	uint8_t cccrcapabilities; // CCCR Capabilities Register (08h)
	uint8_t cccrpowercontrol; // CCCR Power Control Register (12h)
	uint8_t cccrbusspeed; // CCCR Bus Speed Select Register (13h)
	uint8_t cccruhssupport; // CCCR UHS-I Support Register (14h)
	uint8_t cccrdriverstrength; // CCCR Driver Strength Register (15h)
	// Driver Properties
	BOOL multiblock; // Card Capability Multi Block Transfer (SMB)
	BOOL lowspeed; // Card Capability Low Speed Card (LSC)
	BOOL widebus; // Card Capability 4-bit Mode for Low Speed Card (4BLS)
	BOOL highpower; // Support Master Power Control (SMPC)
	BOOL highspeed; // Support High Speed (SHS)
};

/* Common SDIO CIS tuple */
struct _SDIO_CIS
{
	uint16_t vendor;
	uint16_t device;
	uint16_t blocksize;
	uint32_t maxclock;
};

/* SDIO function CIS tuple (Function specific) */
struct _SDIO_TUPLE
{
	SDIO_TUPLE *next;
	uint8_t code;
	uint8_t size;
	uint8_t data[];
};

/* SDIO Function */
typedef struct _SDIO_DRIVER SDIO_DRIVER; // Forward declared to satisfy SDIOFunction

/* SDIO Function Interrupt Handler */
typedef void STDCALL (*sdio_interrupt_handler)(SDIO_FUNCTION *func);

/* SDIO Function Enumeration Callback */
typedef uint32_t STDCALL (*sdio_function_enumerate_cb)(SDIO_FUNCTION *func, void *data);

struct _SDIO_FUNCTION
{
	// Function Properties
	uint32_t sdiostate; // SDIO function state (eg SDIO_STATE_ATTACHED)
	uint32_t sdiostatus; // SDIO function status (eg SDIO_STATUS_BOUND)
	MMC_DEVICE *mmc; // The MMC device for this function
	uint32_t number; // The function number
	uint8_t classid; // Standard class Id
	uint16_t vendorid; // Vendor Id
	uint16_t deviceid; // Device Id
	uint32_t blocksize; // Current block size
	uint32_t maxblocksize; // Maximum block size
	uint32_t enabletimeout; // Function enable timeout
	sdio_interrupt_handler handler; // Interrupt handler for this function
	void *dmabuffer; // DMA compatible buffer for small reads and writes
	SDIO_TUPLE *tuples; // CIS (Card Information Structure) tuples for this function
	SDIO_DRIVER *driver; // Driver this function is bound to, if any
	void *driverdata; // Private data for the driver of this SDIO device
};

/* SDIO Driver */

/* SDIO Driver Enumeration Callback */
typedef uint32_t STDCALL (*sdio_driver_enumerate_cb)(SDIO_DRIVER *driver, void *data);

/* SDIO Driver Methods */
typedef uint32_t STDCALL (*sdio_driver_bind_proc)(MMC_DEVICE *mmc, SDIO_FUNCTION *func);
typedef uint32_t STDCALL (*sdio_driver_unbind_proc)(MMC_DEVICE *mmc, SDIO_FUNCTION *func);

struct _SDIO_DRIVER
{
	// Driver Properties
	DRIVER driver; // The Driver entry for this SDIO Driver
	// SDIO Properties
	sdio_driver_bind_proc driverbind; // A Driver specific DriverBind method implementing the standard SDIO driver interface
	sdio_driver_unbind_proc driverunbind; // A Driver specific DriverUnbind method implementing the standard SDIO driver interface
	// Interface Properties
	MUTEX_HANDLE lock; // Driver lock
	// Internal Properties
	SDIO_DRIVER *prev; // Previous entry in Driver table
	SDIO_DRIVER *next; // Next entry in Driver table
};

/* ============================================================================== */
/* SDHCI specific types */
/* ADMA2 32-bit descriptor (See ADMA2 Descriptor Format - SD Host Controller Simplified Specification Version 4.20) */
typedef struct _SDHCI_ADMA2_DESCRIPTOR32 SDHCI_ADMA2_DESCRIPTOR32;
struct _SDHCI_ADMA2_DESCRIPTOR32
{
	uint16_t command;
	uint16_t len;
	uint32_t address;
} PACKED;


/* ADMA2 64-bit descriptors (See ADMA2 Descriptor Format - SD Host Controller Simplified Specification Version 4.20) */
/* Note 12-byte descriptor can't always be 8-byte aligned */
typedef struct _SDHCI_ADMA2_DESCRIPTOR64 SDHCI_ADMA2_DESCRIPTOR64;
struct _SDHCI_ADMA2_DESCRIPTOR64
{
	uint16_t command;
	uint16_t len;
	uint32_t addresslow;
	uint32_t addresshigh;
} PACKED;


typedef struct _SDHCI_ADMA2_DESCRIPTOR64_V4 SDHCI_ADMA2_DESCRIPTOR64_V4;
struct _SDHCI_ADMA2_DESCRIPTOR64_V4
{
	uint16_t command;
	uint16_t len;
	uint32_t addresslow;
	uint32_t addresshigh;
	uint32_t reserved;
} PACKED;

/* SDHCI Host */
typedef struct _SDHCI_HOST SDHCI_HOST;

/* SDHCI Enumeration Callback */
typedef uint32_t STDCALL (*sdhci_enumerate_cb)(SDHCI_HOST *sdhci, void *data);
/* SDHCI Notification Callback */
typedef uint32_t STDCALL (*sdhci_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* SDHCI Host Methods */
typedef uint32_t STDCALL (*sdhci_host_start_proc)(SDHCI_HOST *sdhci);
typedef uint32_t STDCALL (*sdhci_host_stop_proc)(SDHCI_HOST *sdhci);
typedef uint32_t STDCALL (*sdhci_host_lock_proc)(SDHCI_HOST *sdhci);
typedef uint32_t STDCALL (*sdhci_host_unlock_proc)(SDHCI_HOST *sdhci);
typedef uint32_t STDCALL (*sdhci_host_signal_proc)(SDHCI_HOST *sdhci, SEMAPHORE_HANDLE semaphore);
typedef uint8_t STDCALL (*sdhci_host_read_byte_proc)(SDHCI_HOST *sdhci, uint32_t reg);
typedef uint16_t STDCALL (*sdhci_host_read_word_proc)(SDHCI_HOST *sdhci, uint32_t reg);
typedef uint32_t STDCALL (*sdhci_host_read_long_proc)(SDHCI_HOST *sdhci, uint32_t reg);
typedef void STDCALL (*sdhci_host_write_byte_proc)(SDHCI_HOST *sdhci, uint32_t reg, uint8_t value);
typedef void STDCALL (*sdhci_host_write_word_proc)(SDHCI_HOST *sdhci, uint32_t reg, uint16_t value);
typedef void STDCALL (*sdhci_host_write_long_proc)(SDHCI_HOST *sdhci, uint32_t reg, uint32_t value);
typedef uint32_t STDCALL (*sdhci_host_reset_proc)(SDHCI_HOST *sdhci, uint8_t mask);
typedef uint32_t STDCALL (*sdhci_host_hardware_reset_proc)(SDHCI_HOST *sdhci);
typedef uint32_t STDCALL (*sdhci_host_set_power_proc)(SDHCI_HOST *sdhci, uint16_t power);
typedef uint32_t STDCALL (*sdhci_host_set_clock_proc)(SDHCI_HOST *sdhci, uint32_t clock);
typedef uint32_t STDCALL (*sdhci_host_set_timing_proc)(SDHCI_HOST *sdhci, uint32_t timing);
typedef uint32_t STDCALL (*sdhci_host_set_buswidth_proc)(SDHCI_HOST *sdhci, uint32_t buswidth);
typedef uint32_t STDCALL (*sdhci_host_set_clock_divider_proc)(SDHCI_HOST *sdhci, int index, uint32_t divider);
typedef uint32_t STDCALL (*sdhci_host_set_control_register_proc)(SDHCI_HOST *sdhci);
typedef uint32_t STDCALL (*sdhci_host_prepare_dma_proc)(SDHCI_HOST *sdhci, MMC_COMMAND *command);
typedef uint32_t STDCALL (*sdhci_host_start_dma_proc)(SDHCI_HOST *sdhci, MMC_COMMAND *command);
typedef uint32_t STDCALL (*sdhci_host_stop_dma_proc)(SDHCI_HOST *sdhci, MMC_COMMAND *command);
typedef uint32_t STDCALL (*sdhci_host_setup_card_irq_proc)(SDHCI_HOST *sdhci, LONGBOOL enable);
typedef uint32_t STDCALL (*sdhci_host_complete_card_irq_proc)(SDHCI_HOST *sdhci);

struct _SDHCI_HOST
{
	// Device Properties
	DEVICE device; // The Device entry for this SDHCI
	// SDHCI Properties
	uint32_t sdhciid; // Unique Id of this SDHCI in the SDHCI table
	uint32_t sdhcistate; // SDHCI state (eg SDHCI_STATE_ENABLED)
	sdhci_host_start_proc hoststart; // A Host specific HostStart method implementing a standard SDHCI host interface
	sdhci_host_stop_proc hoststop; // A Host specific HostStop method implementing a standard SDHCI host interface
	sdhci_host_lock_proc hostlock; // A Host specific HostLock method implementing a standard SDHCI host interface
	sdhci_host_unlock_proc hostunlock; // A Host specific HostUnlock method implementing a standard SDHCI host interface
	sdhci_host_signal_proc hostsignal; // A Host specific HostSignal method implementing a standard SDHCI host interface
	sdhci_host_read_byte_proc hostreadbyte; // A Host specific HostReadByte method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_read_word_proc hostreadword; // A Host specific HostReadWord method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_read_long_proc hostreadlong; // A Host specific HostReadLong method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_write_byte_proc hostwritebyte; // A Host specific HostWriteByte method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_write_word_proc hostwriteword; // A Host specific HostWriteWord method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_write_long_proc hostwritelong; // A Host specific HostWriteLong method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_reset_proc hostreset; // A Host specific HostReset method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_hardware_reset_proc hosthardwarereset; // A Host specific HostHardwareReset method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_set_power_proc hostsetpower; // A Host specific HostSetPower method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_set_clock_proc hostsetclock; // A Host specific HostSetClock method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_set_timing_proc hostsettiming; // A Host specific HostSetTiming method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_set_buswidth_proc hostsetbuswidth; // A Host specific HostSetBusWidth method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_set_clock_divider_proc hostsetclockdivider;
	sdhci_host_set_control_register_proc hostsetcontrolregister;
	sdhci_host_prepare_dma_proc hostpreparedma; // A Host specific HostPrepareDMA method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_start_dma_proc hoststartdma; // A Host specific HostStartDMA method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_stop_dma_proc hoststopdma; // A Host specific HostStopDMA method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_setup_card_irq_proc hostsetupcardirq; // A Host specific HostSetupCardIRQ method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	sdhci_host_complete_card_irq_proc hostcompletecardirq; // A Host specific HostCompleteCardIRQ method implementing a standard SDHCI host interface (Or nil if the default method is suitable)
	mmc_device_initialize_proc deviceinitialize; // A Device specific DeviceInitialize method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_deinitialize_proc devicedeinitialize; // A Device specific DeviceDeinitialize method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_get_card_detect_proc devicegetcarddetect; // A Device specific DeviceGetCardDetect method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_get_write_protect_proc devicegetwriteprotect; // A Device specific DeviceGetWriteProtect method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_send_command_proc devicesendcommand; // A Device specific DeviceSendCommand method implementing a standard MMC device interface (Or nil if the default method is suitable)
	mmc_device_set_ios_proc devicesetios; // A Device specific DeviceSetIOS method implementing a standard MMC device interface (Or nil if the default method is suitable)
	// Driver Properties
	SPIN_HANDLE spin; // Host lock (Spin) for use by interrupt handlers
	MUTEX_HANDLE lock; // Host lock (Mutex) for use by other functions
	void *address; // Host register base address
	uint32_t version; // Host version information
	uint32_t quirks; // Host quirks/bugs flags
	uint32_t quirks2; // Host additional quirks/bugs flags
	uint32_t clock; // Host current clock
	uint32_t power; // Host current power
	uint32_t timing; // Host current timing
	uint32_t buswidth; // Host current bus width
	uint32_t interrupts; // Host interrupts to be handled
	uint32_t voltages; // Host configured voltage flags
	uint32_t capabilities; // Host configured capabilities flags
	uint32_t capabilities2; // Host configured additional capabilities flags
	uint32_t timeoutfrequency; // Host configured timeout clock frequency (KHz)
	uint32_t minimumfrequency; // Host configured minimum frequency (Hz)
	uint32_t maximumfrequency; // Host configured maximum frequency (Hz)
	uint32_t maximumblocksize; // Host configured maximum block size
	uint32_t maximumblockcount; // Host configured maximum block count
	uint32_t maximumrequestsize; // Host configured maximum request size
	uint32_t maximumbusytimeout; // Host configured maximum busy timeout (Milliseconds)
	uint32_t minimumdmasize; // Minimum size for DMA read or write (Use PIO if less)
	uint32_t maximumpioblocks; // Maximum blocks for PIO read or write (Use DMA if greater)
	LONGBOOL presetenabled; // Version 3.00 Preset Values Enabled (If applicable)
	LONGBOOL cardirqenabled; // SDIO card interrupt is enabled
	WORKER_HANDLE cardirqworker; // SDIO card interrupt current worker
	MMC_DEVICE *cardirqdevice; // SDIO card interrupt device
	uint32_t cardirqcount; // SDIO card interrupt function registered count
	MMC_COMMAND *command; // Currently processing command
	SEMAPHORE_HANDLE wait; // Command completed semaphore
	LONGBOOL usedma; // Use DMA for the current data transfer
	DMA_DATA dmadata; // External DMA data descriptor for current request (If applicable)
	SEMAPHORE_HANDLE dmawait; // External DMA completed semaphore
	uint32_t dmaslave; // External DMA slave (DREQ) Id for this device (If applicable)
	void *dmabuffer; // DMA bounce buffer for the current request (If applicable)
	uint32_t dmadirection; // DMA data direction for current request (If applicable)
	uint32_t sdmaboundary; // SDMA buffer boundary argument
	SDHCI_ADMA2_DESCRIPTOR64_V4 *admatable; // ADMA descriptors for current request (If applicable)
	void *admabuffer; // ADMA alignment buffers for the current request (If applicable)
	uint32_t admatablesize; // ADMA descriptor table size in bytes (If applicable)
	uint32_t admatablecount; // ADMA descriptor table entry count (If applicable)
	uint32_t admabuffersize; // ADMA alignment buffers size in bytes (If applicable)
	uint32_t admadescriptorsize; // ADMA descriptor size in bytes (If applicable)
	// Configuration Properties
	uint32_t presetvoltages; // Host predefined voltage flags
	uint32_t presetcapabilities; // Host predefined capabilities flags
	uint32_t presetcapabilities2; // Host predefined additional capabilities flags
	uint32_t clockminimum; // Host predefined minimum clock frequency
	uint32_t clockmaximum; // Host predefined maximum clock frequency
	uint32_t driverstageregister; // Host predefined driver stage register (DSR)
	LONGBOOL enablev4mode; // Enable SDHCI version 4 protocol support
	// Statistics Properties
	uint32_t requestcount; // Number of requests that have been submitted to this host
	uint32_t requesterrors; // Number of requests that have failed on this host
	uint32_t datarequestcount; // Number of data requests that have been submitted to this host
	uint32_t commandrequestcount; // Number of command requests that have been submitted to this host
	uint32_t piodatatransfercount; // Number of data requests that have been submitted for PIO transfer on this host
	uint32_t dmadatatransfercount; // Number of data requests that have been submitted for DMA transfer on this host
	uint32_t interruptcount; // Number of interrupt requests received by the host
	uint32_t datainterruptcount; // Number of data interrupt requests received by the host
	uint32_t commandinterruptcount; // Number of command interrupt requests received by the host
	// Internal Properties
	SDHCI_HOST *prev; // Previous entry in SDHCI table
	SDHCI_HOST *next; // Next entry in SDHCI table
};

/* ============================================================================== */
/* Initialization Functions */
uint32_t STDCALL mmc_start(void);
uint32_t STDCALL mmc_stop(void);

void STDCALL mmc_async_start(SDHCI_HOST *sdhci);

/* ============================================================================== */
/* MMC Functions */
uint32_t STDCALL mmc_device_read_blocks(MMC_DEVICE *mmc, int64_t start, int64_t count, void *buffer);
uint32_t STDCALL mmc_device_write_blocks(MMC_DEVICE *mmc, int64_t start, int64_t count, void *buffer);

uint32_t STDCALL mmc_device_erase_blocks(MMC_DEVICE *mmc, int64_t start, int64_t count);

uint32_t STDCALL mmc_device_go_idle(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_set_clock(MMC_DEVICE *mmc, uint32_t clock);
uint32_t STDCALL mmc_device_set_timing(MMC_DEVICE *mmc, uint32_t timing);
uint32_t STDCALL mmc_device_set_bus_width(MMC_DEVICE *mmc, uint32_t width);

uint32_t STDCALL mmc_device_set_block_length(MMC_DEVICE *mmc, uint32_t length);
uint32_t STDCALL mmc_device_set_block_count(MMC_DEVICE *mmc, uint32_t count, BOOL relative);
uint32_t STDCALL mmc_device_set_driver_stage(MMC_DEVICE *mmc, uint32_t driverstage);

uint32_t STDCALL mmc_device_stop_transmission(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_select_card(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_deselect_card(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_switch(MMC_DEVICE *mmc, uint8_t setting, uint8_t index, uint8_t value, uint32_t timeout);
uint32_t STDCALL mmc_device_switch_ex(MMC_DEVICE *mmc, uint8_t setting, uint8_t index, uint8_t value, uint32_t timeout, uint32_t timing, BOOL sendstatus, BOOL retrycrcerror);

uint32_t STDCALL mmc_device_poll_for_busy(MMC_DEVICE *mmc, uint32_t timeout, uint32_t command);
uint32_t STDCALL mmc_device_poll_for_busy_ex(MMC_DEVICE *mmc, uint32_t timeout, uint32_t command, BOOL sendstatus, BOOL retrycrcerror);

uint32_t STDCALL mmc_device_send_card_status(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_send_operation_condition(MMC_DEVICE *mmc, BOOL probe);

uint32_t STDCALL mmc_device_send_card_specific(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_decode_card_specific(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_send_card_identification(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_send_all_card_identification(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_decode_card_identification(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_get_extended_card_specific(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_send_extended_card_specific(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_decode_extended_card_specific(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_set_relative_address(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_spi_set_crc(MMC_DEVICE *mmc, BOOL enable);
uint32_t STDCALL mmc_device_spi_read_operation_condition(MMC_DEVICE *mmc, BOOL highcapacity);

uint32_t STDCALL mmc_device_insert(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_remove(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_initialize(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_deinitialize(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_get_card_detect(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_get_write_protect(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_send_command(MMC_DEVICE *mmc, MMC_COMMAND *command);
uint32_t STDCALL mmc_device_set_ios(MMC_DEVICE *mmc);

MMC_DEVICE * STDCALL mmc_device_create(void);
MMC_DEVICE * STDCALL mmc_device_create_ex(uint32_t size);
uint32_t STDCALL mmc_device_destroy(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_device_register(MMC_DEVICE *mmc);
uint32_t STDCALL mmc_device_deregister(MMC_DEVICE *mmc);

MMC_DEVICE * STDCALL mmc_device_find(uint32_t mmcid);
MMC_DEVICE * STDCALL mmc_device_find_by_device(DEVICE *device);
MMC_DEVICE * STDCALL mmc_device_find_by_name(char *name);
MMC_DEVICE * STDCALL mmc_device_find_by_description(char *description);
uint32_t STDCALL mmc_device_enumerate(mmc_enumerate_cb callback, void *data);

uint32_t STDCALL mmc_device_notification(MMC_DEVICE *mmc, mmc_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* SD Functions */
uint32_t STDCALL sd_device_switch(MMC_DEVICE *mmc, int mode, int group, uint8_t value, void *buffer);

uint32_t STDCALL sd_device_switch_highspeed(MMC_DEVICE *mmc);

uint32_t STDCALL sd_device_set_bus_width(MMC_DEVICE *mmc, uint32_t width);

uint32_t STDCALL sd_device_send_interface_condition(MMC_DEVICE *mmc);

uint32_t STDCALL sd_device_send_operation_condition(MMC_DEVICE *mmc, BOOL probe);

uint32_t STDCALL sd_device_get_card_specific(MMC_DEVICE *mmc);
uint32_t STDCALL sd_device_decode_card_specific(MMC_DEVICE *mmc);

uint32_t STDCALL sd_device_get_card_identification(MMC_DEVICE *mmc);
uint32_t STDCALL sd_device_decode_card_identification(MMC_DEVICE *mmc);

uint32_t STDCALL sd_device_send_sd_status(MMC_DEVICE *mmc);
uint32_t STDCALL sd_device_decode_sd_status(MMC_DEVICE *mmc);

uint32_t STDCALL sd_device_send_sd_switch(MMC_DEVICE *mmc);
uint32_t STDCALL sd_device_decode_sd_switch(MMC_DEVICE *mmc);

uint32_t STDCALL sd_device_send_sd_configuration(MMC_DEVICE *mmc);
uint32_t STDCALL sd_device_decode_sd_configuration(MMC_DEVICE *mmc);

uint32_t STDCALL sd_device_send_relative_address(MMC_DEVICE *mmc);

uint32_t STDCALL sd_device_send_application_command(MMC_DEVICE *mmc, MMC_COMMAND *command);

/* ============================================================================== */
/* SDIO Functions */
// Device Methods
uint32_t STDCALL sdio_device_reset(MMC_DEVICE *mmc);

uint32_t STDCALL sdio_device_enable_wide_bus(MMC_DEVICE *mmc);
uint32_t STDCALL sdio_device_disable_wide_bus(MMC_DEVICE *mmc);

uint32_t STDCALL sdio_device_enable_highspeed(MMC_DEVICE *mmc);
uint32_t STDCALL sdio_device_switch_highspeed(MMC_DEVICE *mmc, BOOL enable);

uint32_t STDCALL sdio_device_send_operation_condition(MMC_DEVICE *mmc, BOOL probe);

uint32_t STDCALL sdio_device_read_write_direct(MMC_DEVICE *mmc, BOOL write, uint32_t operation, uint32_t address, uint8_t input, uint8_t *output);
uint32_t STDCALL sdio_device_read_write_extended(MMC_DEVICE *mmc, BOOL write, uint32_t operation, uint32_t address, BOOL increment, void *buffer, uint32_t blockcount, uint32_t blocksize);

uint32_t STDCALL sdio_device_read_byte(MMC_DEVICE *mmc, uint32_t address, uint8_t *output);
uint32_t STDCALL sdio_device_write_byte(MMC_DEVICE *mmc, uint32_t address, uint8_t input);

uint32_t STDCALL sdio_device_read_cccr(MMC_DEVICE *mmc);

uint32_t STDCALL sdio_device_read_fbr(SDIO_FUNCTION *func);

uint32_t STDCALL sdio_device_read_cis(MMC_DEVICE *mmc, SDIO_FUNCTION *func);

uint32_t STDCALL sdio_device_read_common_cis(MMC_DEVICE *mmc);
uint32_t STDCALL sdio_device_read_function_cis(SDIO_FUNCTION *func);

uint32_t STDCALL sdio_device_process_interrupts(MMC_DEVICE *mmc);
uint32_t STDCALL sdio_device_register_interrupt(MMC_DEVICE *mmc, SDIO_FUNCTION *func, sdio_interrupt_handler handler);
uint32_t STDCALL sdio_device_deregister_interrupt(MMC_DEVICE *mmc, SDIO_FUNCTION *func);

uint32_t STDCALL sdio_device_bind_functions(MMC_DEVICE *mmc);
uint32_t STDCALL sdio_device_unbind_functions(MMC_DEVICE *mmc, SDIO_DRIVER *driver);

// Function Methods
SDIO_FUNCTION * STDCALL sdio_function_allocate(MMC_DEVICE *mmc, uint32_t number);
uint32_t STDCALL sdio_function_release(SDIO_FUNCTION *func);

SDIO_FUNCTION * STDCALL sdio_function_find(MMC_DEVICE *mmc, uint32_t number);
SDIO_FUNCTION * STDCALL sdio_function_find_by_id(MMC_DEVICE *mmc, uint16_t vendorid, uint16_t deviceid);
uint32_t STDCALL sdio_function_enumerate(MMC_DEVICE *mmc, sdio_function_enumerate_cb callback, void *data);

uint32_t STDCALL sdio_function_bind(SDIO_FUNCTION *func, SDIO_DRIVER *driver);
uint32_t STDCALL sdio_function_unbind(SDIO_FUNCTION *func, SDIO_DRIVER *driver);

uint32_t STDCALL sdio_function_enable(SDIO_FUNCTION *func);
uint32_t STDCALL sdio_function_disable(SDIO_FUNCTION *func);

uint32_t STDCALL sdio_function_set_block_size(SDIO_FUNCTION *func, uint32_t blocksize);

uint32_t STDCALL sdio_function_read_write_extended(SDIO_FUNCTION *func, BOOL write, uint32_t address, BOOL increment, void *buffer, uint32_t size);

uint32_t STDCALL sdio_function_read(SDIO_FUNCTION *func, uint32_t address, void *buffer, uint32_t size);
uint32_t STDCALL sdio_function_write(SDIO_FUNCTION *func, uint32_t address, void *buffer, uint32_t size);

uint32_t STDCALL sdio_function_read_byte(SDIO_FUNCTION *func, uint32_t address, uint8_t *output);
uint32_t STDCALL sdio_function_write_byte(SDIO_FUNCTION *func, uint32_t address, uint8_t input);
uint32_t STDCALL sdio_function_write_read_byte(SDIO_FUNCTION *func, uint32_t address, uint8_t input, uint8_t *output);

uint32_t STDCALL sdio_function_read_word(SDIO_FUNCTION *func, uint32_t address, uint16_t *output);
uint32_t STDCALL sdio_function_write_word(SDIO_FUNCTION *func, uint32_t address, uint16_t input);

uint32_t STDCALL sdio_function_read_long(SDIO_FUNCTION *func, uint32_t address, uint32_t *output);
uint32_t STDCALL sdio_function_write_long(SDIO_FUNCTION *func, uint32_t address, uint32_t input);

uint32_t STDCALL sdio_function_register_interrupt(SDIO_FUNCTION *func, sdio_interrupt_handler handler);
uint32_t STDCALL sdio_function_deregister_interrupt(SDIO_FUNCTION *func);

// Host Methods
uint32_t STDCALL sdio_host_dispatch_interrupt(SDHCI_HOST *sdhci, BOOL irq, BOOL fiq);

// Driver Methods
SDIO_DRIVER * STDCALL sdio_driver_create(void);
SDIO_DRIVER * STDCALL sdio_driver_create_ex(uint32_t size);
uint32_t STDCALL sdio_driver_destroy(SDIO_DRIVER *driver);

uint32_t STDCALL sdio_driver_register(SDIO_DRIVER *driver);
uint32_t STDCALL sdio_driver_deregister(SDIO_DRIVER *driver);

SDIO_DRIVER * STDCALL sdio_driver_find(uint32_t driverid);
SDIO_DRIVER * STDCALL sdio_driver_find_by_name(char *name);
uint32_t STDCALL sdio_driver_enumerate(sdio_driver_enumerate_cb callback, void *data);

/* ============================================================================== */
/* SDHCI Functions */
uint32_t STDCALL sdhci_host_reset(SDHCI_HOST *sdhci, uint8_t mask);
uint32_t STDCALL sdhci_host_hardware_reset(SDHCI_HOST *sdhci);

uint32_t STDCALL sdhci_host_set_power(SDHCI_HOST *sdhci, uint16_t power);
uint32_t STDCALL sdhci_host_set_clock(SDHCI_HOST *sdhci, uint32_t clock);
uint32_t STDCALL sdhci_host_set_timing(SDHCI_HOST *sdhci, uint32_t timing);
uint32_t STDCALL sdhci_host_set_bus_width(SDHCI_HOST *sdhci, uint32_t buswidth);

uint32_t STDCALL sdhci_host_prepare_dma(SDHCI_HOST *sdhci, MMC_COMMAND *command);
uint32_t STDCALL sdhci_host_start_dma(SDHCI_HOST *sdhci, MMC_COMMAND *command);
uint32_t STDCALL sdhci_host_stop_dma(SDHCI_HOST *sdhci, MMC_COMMAND *command);
void STDCALL sdhci_host_complete_dma(DMA_REQUEST *request);

uint32_t STDCALL sdhci_host_setup_card_irq(SDHCI_HOST *sdhci, LONGBOOL enable);
uint32_t STDCALL sdhci_host_complete_card_irq(SDHCI_HOST *sdhci);

uint32_t STDCALL sdhci_host_transfer_pio(SDHCI_HOST *sdhci);
uint32_t STDCALL sdhci_host_transfer_dma(SDHCI_HOST *sdhci);

uint32_t STDCALL sdhci_host_finish_command(SDHCI_HOST *sdhci);
uint32_t STDCALL sdhci_host_finish_data(SDHCI_HOST *sdhci);

uint32_t STDCALL sdhci_host_command_interrupt(SDHCI_HOST *sdhci, uint32_t interruptmask, uint32_t *returnmask);
uint32_t STDCALL sdhci_host_data_interrupt(SDHCI_HOST *sdhci, uint32_t interruptmask);

uint32_t STDCALL sdhci_host_start(SDHCI_HOST *sdhci);
uint32_t STDCALL sdhci_host_stop(SDHCI_HOST *sdhci);

uint32_t STDCALL sdhci_host_lock(SDHCI_HOST *sdhci);
uint32_t STDCALL sdhci_host_unlock(SDHCI_HOST *sdhci);

uint32_t STDCALL sdhci_host_signal(SDHCI_HOST *sdhci, SEMAPHORE_HANDLE semaphore);

uint8_t STDCALL sdhci_host_read_byte(SDHCI_HOST *sdhci, uint32_t reg);
uint16_t STDCALL sdhci_host_read_word(SDHCI_HOST *sdhci, uint32_t reg);
uint32_t STDCALL sdhci_host_read_long(SDHCI_HOST *sdhci, uint32_t reg);
void STDCALL sdhci_host_write_byte(SDHCI_HOST *sdhci, uint32_t reg, uint8_t value);
void STDCALL sdhci_host_write_word(SDHCI_HOST *sdhci, uint32_t reg, uint16_t value);
void STDCALL sdhci_host_write_long(SDHCI_HOST *sdhci, uint32_t reg, uint32_t value);

uint32_t STDCALL sdhci_host_set_clock_divider(SDHCI_HOST *sdhci, int index, uint32_t divider);
uint32_t STDCALL sdhci_host_set_control_register(SDHCI_HOST *sdhci);

size_t STDCALL sdhci_host_get_adma_address(SDHCI_HOST *sdhci);
void STDCALL sdhci_host_set_adma_address(SDHCI_HOST *sdhci, size_t address);
size_t STDCALL sdhci_host_get_sdma_address(SDHCI_HOST *sdhci, MMC_COMMAND *command);
void STDCALL sdhci_host_set_sdma_address(SDHCI_HOST *sdhci, size_t address);

void STDCALL sdhci_host_write_adma_descriptor(SDHCI_HOST *sdhci, void *descriptor, uint16_t command, uint16_t len, size_t address);

SDHCI_HOST * STDCALL sdhci_host_create(void);
SDHCI_HOST * STDCALL sdhci_host_create_ex(uint32_t size);
uint32_t STDCALL sdhci_host_destroy(SDHCI_HOST *sdhci);

uint32_t STDCALL sdhci_host_register(SDHCI_HOST *sdhci);
uint32_t STDCALL sdhci_host_deregister(SDHCI_HOST *sdhci);

SDHCI_HOST * STDCALL sdhci_host_find(uint32_t sdhciid);
uint32_t STDCALL sdhci_host_enumerate(sdhci_enumerate_cb callback, void *data);

uint32_t STDCALL sdhci_host_notification(SDHCI_HOST *sdhci, sdhci_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* MMC Helper Functions */
uint32_t STDCALL mmc_get_count(void);

MMC_DEVICE * STDCALL mmc_device_check(MMC_DEVICE *mmc);

BOOL STDCALL mmc_is_sd(MMC_DEVICE *mmc);
BOOL STDCALL mmc_is_sdio(MMC_DEVICE *mmc);

SDHCI_HOST * STDCALL mmc_get_sdhci(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_get_cid_value(MMC_DEVICE *mmc, uint32_t version, uint32_t value);
uint32_t STDCALL mmc_get_csd_value(MMC_DEVICE *mmc, uint32_t value);

uint32_t STDCALL mmc_extract_bits(void *buffer, uint32_t start, uint32_t size);
uint32_t STDCALL mmc_extract_bits_ex(void *buffer, uint32_t length, uint32_t start, uint32_t size);

BOOL STDCALL mmc_is_multi_command(uint16_t command);

BOOL STDCALL mmc_is_non_removable(MMC_DEVICE *mmc);
BOOL STDCALL mmc_has_extended_csd(MMC_DEVICE *mmc);
BOOL STDCALL mmc_has_set_block_count(MMC_DEVICE *mmc);
BOOL STDCALL mmc_has_auto_block_count(MMC_DEVICE *mmc);
BOOL STDCALL mmc_has_auto_command_stop(MMC_DEVICE *mmc);

uint32_t STDCALL mmc_status_to_string(uint32_t status, char *string, uint32_t len);

uint32_t STDCALL mmc_version_to_string(uint32_t version, char *string, uint32_t len);
uint32_t STDCALL mmc_timing_to_string(uint32_t timing, char *string, uint32_t len);
uint32_t STDCALL mmc_bus_width_to_string(uint32_t buswidth, char *string, uint32_t len);
uint32_t STDCALL mmc_driver_type_to_string(uint32_t drivertype, char *string, uint32_t len);
uint32_t STDCALL mmc_signal_voltage_to_string(uint32_t signalvoltage, char *string, uint32_t len);

uint32_t STDCALL mmc_device_type_to_string(uint32_t mmctype, char *string, uint32_t len);
uint32_t STDCALL mmc_device_state_to_string(uint32_t mmcstate, char *string, uint32_t len);

uint32_t STDCALL mmc_device_state_to_notification(uint32_t state);

/* ============================================================================== */
/* SD Helper Functions */
uint32_t STDCALL sd_get_max_clock(MMC_DEVICE *mmc);

uint32_t STDCALL sd_get_cid_value(MMC_DEVICE *mmc, uint32_t value);
uint32_t STDCALL sd_get_csd_value(MMC_DEVICE *mmc, uint32_t version, uint32_t value);
uint32_t STDCALL sd_get_scr_value(MMC_DEVICE *mmc, uint32_t value);
uint32_t STDCALL sd_get_ssr_value(MMC_DEVICE *mmc, uint32_t value);
uint32_t STDCALL sd_get_switch_value(MMC_DEVICE *mmc, uint32_t value);

uint32_t STDCALL sd_version_to_string(uint32_t version, char *string, uint32_t len);
uint32_t STDCALL sd_bus_width_to_string(uint32_t buswidth, char *string, uint32_t len);

/* ============================================================================== */
/* SDIO Helper Functions */
uint32_t STDCALL sdio_driver_get_count(void);

SDIO_DRIVER * STDCALL sdio_driver_check(SDIO_DRIVER *driver);

uint32_t STDCALL sdio_device_get_max_clock(MMC_DEVICE *mmc);

MMC_DEVICE * STDCALL sdio_function_get_mmc(SDIO_FUNCTION *func);
SDHCI_HOST * STDCALL sdio_function_get_sdhci(SDIO_FUNCTION *func);

uint32_t STDCALL sdio_version_to_string(uint32_t version, char *string, uint32_t len);

uint32_t STDCALL sdio_function_state_to_string(uint32_t sdiostate, char *string, uint32_t len);
uint32_t STDCALL sdio_function_status_to_string(uint32_t sdiostatus, char *string, uint32_t len);

uint32_t STDCALL sdio_function_state_to_notification(uint32_t state);
uint32_t STDCALL sdio_function_status_to_notification(uint32_t status);

/* ============================================================================== */
/* SDHCI Helper Functions */
uint32_t STDCALL sdhci_get_count(void);

SDHCI_HOST * STDCALL sdhci_host_check(SDHCI_HOST *sdhci);

BOOL STDCALL sdhci_is_spi(SDHCI_HOST *sdhci);
BOOL STDCALL sdhci_has_dma(SDHCI_HOST *sdhci);
BOOL STDCALL sdhci_has_cm_d23(SDHCI_HOST *sdhci);
BOOL STDCALL sdhci_auto_cm_d12(SDHCI_HOST *sdhci);
BOOL STDCALL sdhci_auto_cm_d23(SDHCI_HOST *sdhci);

uint16_t STDCALL sdhci_get_version(SDHCI_HOST *sdhci);

uint16_t STDCALL sdhci_get_command(uint16_t command);
uint16_t STDCALL sdhci_make_command(uint16_t command, uint16_t flags);
uint16_t STDCALL sdhci_make_block_size(uint16_t dma, uint16_t blocksize);

uint32_t STDCALL sdhci_version_to_string(uint32_t version, char *name, uint32_t len);
uint32_t STDCALL sdhci_power_to_string(uint32_t power, char *name, uint32_t len);

uint32_t STDCALL sdhci_device_type_to_string(uint32_t sdhcitype, char *name, uint32_t len);
uint32_t STDCALL sdhci_host_type_to_string(uint32_t sdhcitype, char *name, uint32_t len);
uint32_t STDCALL sdhci_device_state_to_string(uint32_t sdhcistate, char *name, uint32_t len);
uint32_t STDCALL sdhci_host_state_to_string(uint32_t sdhcistate, char *name, uint32_t len);

uint32_t STDCALL sdhci_host_state_to_notification(uint32_t state);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_MMC_H