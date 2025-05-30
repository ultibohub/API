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
#ifndef _ULTIBO_BCMSDHOST_H
#define _ULTIBO_BCMSDHOST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/threads.h"
#include "ultibo/mmc.h"

/* ============================================================================== */
/* BCMSDHOST specific constants */
#define BCMSDHOST_DESCRIPTION	"Broadcom BCM27XX SDHOST" // Description of BCMSDHOST device

#define BCMSDHOST_FIFO_READ_THRESHOLD	4
#define BCMSDHOST_FIFO_WRITE_THRESHOLD	4
#define BCMSDHOST_ALLOW_CMD23_READ	1
#define BCMSDHOST_ALLOW_CMD23_WRITE	0
#define BCMSDHOST_SDDATA_FIFO_PIO_BURST	8
#define BCMSDHOST_CMD_DALLY_US	1

/* BCMSDHOST register constants */
#define BCMSDHOST_SDCMD	0x00 // Command to SD card              - 16 R/W
#define BCMSDHOST_SDARG	0x04 // Argument to SD card             - 32 R/W
#define BCMSDHOST_SDTOUT	0x08 // Start value for timeout counter - 32 R/W
#define BCMSDHOST_SDCDIV	0x0c // Start value for clock divider   - 11 R/W
#define BCMSDHOST_SDRSP0	0x10 // SD card response (31:0)         - 32 R  
#define BCMSDHOST_SDRSP1	0x14 // SD card response (63:32)        - 32 R  
#define BCMSDHOST_SDRSP2	0x18 // SD card response (95:64)        - 32 R  
#define BCMSDHOST_SDRSP3	0x1c // SD card response (127:96)       - 32 R  
#define BCMSDHOST_SDHSTS	0x20 // SD host status                  - 11 R  
#define BCMSDHOST_SDVDD	0x30 // SD card power control           -  1 R/W
#define BCMSDHOST_SDEDM	0x34 // Emergency Debug Mode            - 13 R/W
#define BCMSDHOST_SDHCFG	0x38 // Host configuration              -  2 R/W
#define BCMSDHOST_SDHBCT	0x3c // Host byte count (debug)         - 32 R/W
#define BCMSDHOST_SDDATA	0x40 // Data to/from SD card            - 32 R/W
#define BCMSDHOST_SDHBLC	0x50 // Host block count (SDIO/SDHC)    -  9 R/W

/* BCMSDHOST command register constants */
#define BCMSDHOST_SDCMD_NEW_FLAG	0x8000
#define BCMSDHOST_SDCMD_FAIL_FLAG	0x4000
#define BCMSDHOST_SDCMD_BUSYWAIT	0x800
#define BCMSDHOST_SDCMD_NO_RESPONSE	0x400
#define BCMSDHOST_SDCMD_LONG_RESPONSE	0x200
#define BCMSDHOST_SDCMD_WRITE_CMD	0x80
#define BCMSDHOST_SDCMD_READ_CMD	0x40
#define BCMSDHOST_SDCMD_CMD_MASK	0x3f

/* BCMSDHOST clock divider register constants */
#define BCMSDHOST_SDCDIV_MAX_CDIV	0x7ff

/* BCMSDHOST host status register constants */
#define BCMSDHOST_SDHSTS_BUSY_IRPT	0x400
#define BCMSDHOST_SDHSTS_BLOCK_IRPT	0x200
#define BCMSDHOST_SDHSTS_SDIO_IRPT	0x100
#define BCMSDHOST_SDHSTS_REW_TIME_OUT	0x80
#define BCMSDHOST_SDHSTS_CMD_TIME_OUT	0x40
#define BCMSDHOST_SDHSTS_CRC16_ERROR	0x20
#define BCMSDHOST_SDHSTS_CRC7_ERROR	0x10
#define BCMSDHOST_SDHSTS_FIFO_ERROR	0x08
/* 04 Reserved */
/* 02 Reserved */
#define BCMSDHOST_SDHSTS_DATA_FLAG	0x01

#define BCMSDHOST_SDHSTS_TRANSFER_ERROR_MASK	BCMSDHOST_SDHSTS_CRC7_ERROR | BCMSDHOST_SDHSTS_CRC16_ERROR | BCMSDHOST_SDHSTS_REW_TIME_OUT | BCMSDHOST_SDHSTS_FIFO_ERROR
#define BCMSDHOST_SDHSTS_ERROR_MASK	BCMSDHOST_SDHSTS_CMD_TIME_OUT | BCMSDHOST_SDHSTS_TRANSFER_ERROR_MASK

/* BCMSDHOST host configuration register constants */
#define BCMSDHOST_SDHCFG_BUSY_IRPT_EN	(1 << 10)
#define BCMSDHOST_SDHCFG_BLOCK_IRPT_EN	(1 << 8)
#define BCMSDHOST_SDHCFG_SDIO_IRPT_EN	(1 << 5)
#define BCMSDHOST_SDHCFG_DATA_IRPT_EN	(1 << 4)
#define BCMSDHOST_SDHCFG_SLOW_CARD	(1 << 3)
#define BCMSDHOST_SDHCFG_WIDE_EXT_BUS	(1 << 2)
#define BCMSDHOST_SDHCFG_WIDE_INT_BUS	(1 << 1)
#define BCMSDHOST_SDHCFG_REL_CMD_LINE	(1 << 0)

/* BCMSDHOST emergency debug mode register constants */
#define BCMSDHOST_SDEDM_FORCE_DATA_MODE	(1 << 19)
#define BCMSDHOST_SDEDM_CLOCK_PULSE	(1 << 20)
#define BCMSDHOST_SDEDM_BYPASS	(1 << 21)

#define BCMSDHOST_SDEDM_WRITE_THRESHOLD_SHIFT	9
#define BCMSDHOST_SDEDM_READ_THRESHOLD_SHIFT	14
#define BCMSDHOST_SDEDM_THRESHOLD_MASK	0x1f

#define BCMSDHOST_SDEDM_FSM_MASK	0xf
#define BCMSDHOST_SDEDM_FSM_IDENTMODE	0x0
#define BCMSDHOST_SDEDM_FSM_DATAMODE	0x1
#define BCMSDHOST_SDEDM_FSM_READDATA	0x2
#define BCMSDHOST_SDEDM_FSM_WRITEDATA	0x3
#define BCMSDHOST_SDEDM_FSM_READWAIT	0x4
#define BCMSDHOST_SDEDM_FSM_READCRC	0x5
#define BCMSDHOST_SDEDM_FSM_WRITECRC	0x6
#define BCMSDHOST_SDEDM_FSM_WRITEWAIT1	0x7
#define BCMSDHOST_SDEDM_FSM_POWERDOWN	0x8
#define BCMSDHOST_SDEDM_FSM_POWERUP	0x9
#define BCMSDHOST_SDEDM_FSM_WRITESTART1	0xa
#define BCMSDHOST_SDEDM_FSM_WRITESTART2	0xb
#define BCMSDHOST_SDEDM_FSM_GENPULSES	0xc
#define BCMSDHOST_SDEDM_FSM_WRITEWAIT2	0xd
#define BCMSDHOST_SDEDM_FSM_STARTPOWDOWN	0xf

#define BCMSDHOST_SDDATA_FIFO_WORDS	16

#define BCMSDHOST_USE_CMD23_FLAGS	(BCMSDHOST_ALLOW_CMD23_READ * MMC_DATA_READ) | (BCMSDHOST_ALLOW_CMD23_WRITE * MMC_DATA_WRITE)

/* Mailbox constants */
#define BCMSDHOST_MBOX_TAG_SET_SDHOST_CLOCK	0x00038042 // Tell the firmware the SD Host clock setting so it will be adjusted for changes in core frequency

/* ============================================================================== */
/* BCMSDHOST specific types */
/* Mailbox tag request for BCMSDHOST_MBOX_TAG_SET_SDHOST_CLOCK */
typedef struct _BCMSDHOST_MAILBOX_TAG_SET_SDHOST_CLOCK BCMSDHOST_MAILBOX_TAG_SET_SDHOST_CLOCK;
struct _BCMSDHOST_MAILBOX_TAG_SET_SDHOST_CLOCK
{
	uint32_t clock;
	uint32_t value1;
	uint32_t value2;
};

typedef struct _BCMSDHOST_HOST BCMSDHOST_HOST;
struct _BCMSDHOST_HOST
{
	// SDHCI Properties
	SDHCI_HOST sdhci;
	// BCMSDHOST Properties
	uint32_t irq; // The IRQ number for this device
	SPIN_HANDLE lock; // Host lock (Differs from lock in Host portion) (Spin lock due to use by interrupt handler)
	LONGBOOL enablefiq; // Use FIQ instead of IRQ
	uint32_t gpiofirst; // The starting pin number for GPIO assignments (or GPIO_PIN_UNKNOWN if externally configured)
	uint32_t gpiolast; // The ending pin number for GPIO assignments (or GPIO_PIN_UNKNOWN if externally configured)
	uint32_t gpiofunction; // The function number for GPIO assignments (or GPIO_FUNCTION_UNKNOWN if externally configured)
	uint32_t clockdivider; // Cached Clock Divider (CDIV) register
	uint32_t hostconfiguration; // Cached Host Configuration (HCFG) register
	LONGBOOL firmwaresetsclockdivider; // True if the firmware controls the clock divider
	uint32_t commandquickpollretries;
	uint32_t nanosecondsperfifoword;
	LONGBOOL allowdma; // Allow DMA to be used for data transfers
	LONGBOOL resetclock; // Reset the clock for the next request
	uint32_t maxdelay; // Maximum length of time spent waiting (in Milliseconds)
	int64_t stoptime; // When the last stop was issued (in Clock Ticks)
	uint32_t drainwords; // Last words of FIFO to drain on DMA read
	uint32_t drainoffset; // Offset for data during FIFO drain on DMA read
	LONGBOOL usesbc; // Use CMD23 (Set Block Count) for the current transfer
	LONGBOOL usebusy; // Wait for busy interrupt on current command
	uint32_t delayafterstop; // Minimum time between stop and subsequent data transfer (in Microseconds)
	uint32_t delayafterthisstop; // Minimum time between this stop and subsequent data transfer (in Microseconds)
	uint32_t useroverclock50; // User's preferred frequency to use when 50MHz is requested (in MHz)
	uint32_t overclock50; // Frequency to use when 50MHz is requested (in MHz)
	uint32_t overclock; // Current frequency if overclocked, else zero (in Hz)
	uint32_t piolimit; // Maximum block count for PIO (0 = always DMA / 0x7FFFFFF = always PIO)
	uint32_t piotimeout; // PIO Read or Write block timeout (in milliseconds)
};

/* ============================================================================== */
/* BCMSDHOST Functions */
SDHCI_HOST * STDCALL bcmsdhost_create(size_t address, char *name, uint32_t irq, uint32_t dreq, uint32_t clockminimum, uint32_t clockmaximum, uint32_t gpiofirst, uint32_t gpiolast, uint32_t gpiofunction, BOOL enablefiq);
uint32_t STDCALL bcmsdhost_destroy(SDHCI_HOST *sdhci);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_BCMSDHOST_H
