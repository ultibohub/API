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
#ifndef _ULTIBO_PL18X_H
#define _ULTIBO_PL18X_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/mmc.h"

/** PL18X specific constants */
#define PL180_MMCI_DESCRIPTION	"ARM PrimeCell PL180 MMCI Host" ///< Description of PL180 device
#define PL181_MMCI_DESCRIPTION	"ARM PrimeCell PL181 MMCI Host" ///< Description of PL181 device

/** PL18X Power control register */
#define PL18X_MMCI_POWER	0x000
#define PL18X_MMCI_POWER_OFF	0x00 ///< Power-off
/** Bits 1:0 - 0x01 Reserved */
#define PL18X_MMCI_POWER_UP	0x02 ///< Power-up
#define PL18X_MMCI_POWER_ON	0x03 ///< Power-on
/** Bits 5:2 - Output Voltage */
#define PL18X_MMCI_POWER_OD	(1 << 6) ///< MCICMD output control
#define PL18X_MMCI_POWER_ROD	(1 << 7) ///< Rod control

/** The ST Micro version does not have ROD and reuses the voltage registers for direction settings */
#define PL18X_MMCI_POWER_ST_DATA2DIREN	(1 << 2)
#define PL18X_MMCI_POWER_ST_CMDDIREN	(1 << 3)
#define PL18X_MMCI_POWER_ST_DATA0DIREN	(1 << 4)
#define PL18X_MMCI_POWER_ST_DATA31DIREN	(1 << 5)
#define PL18X_MMCI_POWER_ST_FBCLKEN	(1 << 7)
#define PL18X_MMCI_POWER_ST_DATA74DIREN	(1 << 8)

/** PL18X Clock control register */
#define PL18X_MMCI_CLOCK	0x004
#define PL18X_MMCI_CLOCK_ENABLE	(1 << 8) ///< Enable MCI bus clock: 0 = Clock disabled / 1 = Clock enabled
#define PL18X_MMCI_CLOCK_PWRSAVE	(1 << 9) ///< Disable MCI clock output when bus is idle: 0 = Always enabled / 1 = Clock enabled when bus is active
#define PL18X_MMCI_CLOCK_BYPASS	(1 << 10) ///< Enable bypass of clock divide logic: 0 = Disable bypass / 1 = Enable bypass
#define PL18X_MMCI_CLOCK_4BIT_BUS	(1 << 11) ///< Enable wide bus mode: 0 = Standard bus mode (only MCIDAT0 used) / 1 = Wide bus mode (MCIDAT3:0 used)

/** 8bit wide buses, hardware flow contronl, negative edges and clock inversion supported in ST Micro U300 and Ux500 versions */
#define PL18X_MMCI_CLOCK_ST_8BIT_BUS	(1 << 12)
#define PL18X_MMCI_CLOCK_ST_U300_HWFCEN	(1 << 13)
#define PL18X_MMCI_CLOCK_ST_UX500_NEG_EDGE	(1 << 13)
#define PL18X_MMCI_CLOCK_ST_UX500_HWFCEN	(1 << 14)
#define PL18X_MMCI_CLOCK_ST_UX500_CLK_INV	(1 << 15)
/** Modified PL180 on Versatile Express platform */
#define PL18X_MMCI_CLOCK_ARM_HWFCEN	(1 << 12)

/** Modified on Qualcomm Integrations */
#define PL18X_MMCI_CLOCK_QCOM_WIDEBUS_8	(1 << 10) | (1 << 11)
#define PL18X_MMCI_CLOCK_QCOM_FLOWENA	(1 << 12)
#define PL18X_MMCI_CLOCK_QCOM_INVERTOUT	(1 << 13)

/** Select in latch data and command in */
#define PL18X_MMCI_CLOCK_QCOM_SELECT_IN_FBCLK	(1 << 15)
#define PL18X_MMCI_CLOCK_QCOM_SELECT_IN_DDR_MODE	(1 << 14) | (1 << 15)

/** PL18X Argument register */
#define PL18X_MMCI_ARGUMENT	0x008
/** Bits 31:0 Command Argument */

/** PL18X Command register */
#define PL18X_MMCI_COMMAND	0x00c
/** Bits 5:0 Command Index */
#define PL18X_MMCI_CPSM_RESPONSE	(1 << 6) ///< If set, CPSM waits for a response
#define PL18X_MMCI_CPSM_LONGRSP	(1 << 7) ///< If set, CPSM receives a 136-bit long response
#define PL18X_MMCI_CPSM_INTERRUPT	(1 << 8) ///< If set, CPSM disables command timer and waits for interrupt request
#define PL18X_MMCI_CPSM_PENDING	(1 << 9) ///< If set, CPSM waits for CmdPend before it starts sending a command
#define PL18X_MMCI_CPSM_ENABLE	(1 << 10) ///< If set, CPSM is enabled
/** Argument flag extenstions in the ST Micro versions */
#define PL18X_MMCI_CPSM_ST_SDIO_SUSP	(1 << 11)
#define PL18X_MMCI_CPSM_ST_ENCMD_COMPL	(1 << 12)
#define PL18X_MMCI_CPSM_ST_NIEN	(1 << 13)
#define PL18X_MMCI_CPSM_ST_CE_ATACMD	(1 << 14)

/** Modified on Qualcomm Integrations */
#define PL18X_MMCI_CPSM_QCOM_DATCMD	(1 << 12)
#define PL18X_MMCI_CPSM_QCOM_MCIABORT	(1 << 13)
#define PL18X_MMCI_CPSM_QCOM_CCSENABLE	(1 << 14)
#define PL18X_MMCI_CPSM_QCOM_CCSDISABLE	(1 << 15)
#define PL18X_MMCI_CPSM_QCOM_AUTO_CMD19	(1 << 16)
#define PL18X_MMCI_CPSM_QCOM_AUTO_CMD21	(1 << 21)

/** PL18X Command response register */
#define PL18X_MMCI_RESPCMD	0x010
/** Bits 5:0  Response command index */
/** Bits 31:6 Reserved */

/** PL18X Response registers */
#define PL18X_MMCI_RESPONSE0	0x014
#define PL18X_MMCI_RESPONSE1	0x018
#define PL18X_MMCI_RESPONSE2	0x01c
#define PL18X_MMCI_RESPONSE3	0x020
/** Bits 31:0 Card Status */

/** PL18X Data timer register */
#define PL18X_MMCI_DATATIMER	0x024
/** Bits 31:0 Data Timeout Period */

/** PL18X Data length register */
#define PL18X_MMCI_DATALENGTH	0x028
/** Bits 15:0  Data Length Value */
/** Bits 31:16 Reserved */

/** PL18X Data control register */
#define PL18X_MMCI_DATACTRL	0x02c
#define PL18X_MMCI_DPSM_ENABLE	(1 << 0) ///< Data transfer enabled
#define PL18X_MMCI_DPSM_DIRECTION	(1 << 1) ///< Data transfer direction: 0 = From controller to card / 1 = From card to controller
#define PL18X_MMCI_DPSM_MODE	(1 << 2) ///< Data transfer mode: 0 = Block data transfer / 1 = Stream data transfer
#define PL18X_MMCI_DPSM_DMAENABLE	(1 << 3) ///< Enable DMA: 0 = DMA disabled / 1 = DMA enabled
#define PL18X_MMCI_DPSM_BLOCKSIZE	(1 << 4) ///< Data block length
/** Control register extensions in the ST Micro U300 and Ux500 versions */
#define PL18X_MMCI_ST_DPSM_RWSTART	(1 << 8)
#define PL18X_MMCI_ST_DPSM_RWSTOP	(1 << 9)
#define PL18X_MMCI_ST_DPSM_RWMOD	(1 << 10)
#define PL18X_MMCI_ST_DPSM_SDIOEN	(1 << 11)
/** Control register extensions in the ST Micro Ux500 versions */
#define PL18X_MMCI_ST_DPSM_DMAREQCTL	(1 << 12)
#define PL18X_MMCI_ST_DPSM_DBOOTMODEEN	(1 << 13)
#define PL18X_MMCI_ST_DPSM_BUSYMODE	(1 << 14)
#define PL18X_MMCI_ST_DPSM_DDRMODE	(1 << 15)

/** PL18X Data counter register */
#define PL18X_MMCI_DATACNT	0x030
/** Bits 15:0  Remaining Data */
/** Bits 31:16 Reserved */

/** PL18X Status register */
#define PL18X_MMCI_STATUS	0x034
#define PL18X_MMCI_CMDCRCFAIL	(1 << 0)
#define PL18X_MMCI_DATACRCFAIL	(1 << 1)
#define PL18X_MMCI_CMDTIMEOUT	(1 << 2)
#define PL18X_MMCI_DATATIMEOUT	(1 << 3)
#define PL18X_MMCI_TXUNDERRUN	(1 << 4)
#define PL18X_MMCI_RXOVERRUN	(1 << 5)
#define PL18X_MMCI_CMDRESPEND	(1 << 6)
#define PL18X_MMCI_CMDSENT	(1 << 7)
#define PL18X_MMCI_DATAEND	(1 << 8)
#define PL18X_MMCI_STARTBITERR	(1 << 9)
#define PL18X_MMCI_DATABLOCKEND	(1 << 10)
#define PL18X_MMCI_CMDACTIVE	(1 << 11)
#define PL18X_MMCI_TXACTIVE	(1 << 12)
#define PL18X_MMCI_RXACTIVE	(1 << 13)
#define PL18X_MMCI_TXFIFOHALFEMPTY	(1 << 14)
#define PL18X_MMCI_RXFIFOHALFFULL	(1 << 15)
#define PL18X_MMCI_TXFIFOFULL	(1 << 16)
#define PL18X_MMCI_RXFIFOFULL	(1 << 17)
#define PL18X_MMCI_TXFIFOEMPTY	(1 << 18)
#define PL18X_MMCI_RXFIFOEMPTY	(1 << 19)
#define PL18X_MMCI_TXDATAAVLBL	(1 << 20)
#define PL18X_MMCI_RXDATAAVLBL	(1 << 21)
/** Extended status bits for the ST Micro variants */
#define PL18X_MMCI_ST_SDIOIT	(1 << 22)
#define PL18X_MMCI_ST_CEATAEND	(1 << 23)
#define PL18X_MMCI_ST_CARDBUSY	(1 << 24)

/** PL18X Clear register */
#define PL18X_MMCI_CLEAR	0x038
#define PL18X_MMCI_CMDCRCFAILCLR	(1 << 0)
#define PL18X_MMCI_DATACRCFAILCLR	(1 << 1)
#define PL18X_MMCI_CMDTIMEOUTCLR	(1 << 2)
#define PL18X_MMCI_DATATIMEOUTCLR	(1 << 3)
#define PL18X_MMCI_TXUNDERRUNCLR	(1 << 4)
#define PL18X_MMCI_RXOVERRUNCLR	(1 << 5)
#define PL18X_MMCI_CMDRESPENDCLR	(1 << 6)
#define PL18X_MMCI_CMDSENTCLR	(1 << 7)
#define PL18X_MMCI_DATAENDCLR	(1 << 8)
#define PL18X_MMCI_STARTBITERRCLR	(1 << 9)
#define PL18X_MMCI_DATABLOCKENDCLR	(1 << 10)
/** Extended status bits for the ST Micro variants */
#define PL18X_MMCI_ST_SDIOITC	(1 << 22)
#define PL18X_MMCI_ST_CEATAENDC	(1 << 23)
#define PL18X_MMCI_ST_BUSYENDC	(1 << 24)

/** PL18X Interrupt mask registers */
#define PL18X_MMCI_MASK0	0x03c
#define PL18X_MMCI_MASK1	0x040
#define PL18X_MMCI_CMDCRCFAILMASK	(1 << 0)
#define PL18X_MMCI_DATACRCFAILMASK	(1 << 1)
#define PL18X_MMCI_CMDTIMEOUTMASK	(1 << 2)
#define PL18X_MMCI_DATATIMEOUTMASK	(1 << 3)
#define PL18X_MMCI_TXUNDERRUNMASK	(1 << 4)
#define PL18X_MMCI_RXOVERRUNMASK	(1 << 5)
#define PL18X_MMCI_CMDRESPENDMASK	(1 << 6)
#define PL18X_MMCI_CMDSENTMASK	(1 << 7)
#define PL18X_MMCI_DATAENDMASK	(1 << 8)
#define PL18X_MMCI_STARTBITERRMASK	(1 << 9)
#define PL18X_MMCI_DATABLOCKENDMASK	(1 << 10)
#define PL18X_MMCI_CMDACTIVEMASK	(1 << 11)
#define PL18X_MMCI_TXACTIVEMASK	(1 << 12)
#define PL18X_MMCI_RXACTIVEMASK	(1 << 13)
#define PL18X_MMCI_TXFIFOHALFEMPTYMASK	(1 << 14)
#define PL18X_MMCI_RXFIFOHALFFULLMASK	(1 << 15)
#define PL18X_MMCI_TXFIFOFULLMASK	(1 << 16)
#define PL18X_MMCI_RXFIFOFULLMASK	(1 << 17)
#define PL18X_MMCI_TXFIFOEMPTYMASK	(1 << 18)
#define PL18X_MMCI_RXFIFOEMPTYMASK	(1 << 19)
#define PL18X_MMCI_TXDATAAVLBLMASK	(1 << 20)
#define PL18X_MMCI_RXDATAAVLBLMASK	(1 << 21)
/** Extended status bits for the ST Micro variants */
#define PL18X_MMCI_ST_SDIOITMASK	(1 << 22)
#define PL18X_MMCI_ST_CEATAENDMASK	(1 << 23)
#define PL18X_MMCI_ST_BUSYEND	(1 << 24)

/** PL18X SD card select register */
#define PL18X_MMCI_SELECT	0x044

/** PL18X FIFO counter register */
#define PL18X_MMCI_FIFOCNT	0x048

/** PL18X Data FIFO register */
#define PL18X_MMCI_FIFO	0x080 ///< To 0x0bc

/** PL18X Peripheral identification register */
#define PL18X_MMCI_PERIPHID	0xFE0

/** PL18X PrimeCell identification register */
#define PL18X_MMCI_PCELLID	0xFF0

#define PL18X_MMCI_IRQENABLE	(PL18X_MMCI_CMDCRCFAILMASK | PL18X_MMCI_DATACRCFAILMASK | PL18X_MMCI_CMDTIMEOUTMASK |  PL18X_MMCI_DATATIMEOUTMASK | PL18X_MMCI_TXUNDERRUNMASK | PL18X_MMCI_RXOVERRUNMASK | PL18X_MMCI_CMDRESPENDMASK | PL18X_MMCI_CMDSENTMASK | PL18X_MMCI_STARTBITERRMASK)
/** These interrupts are directed to IRQ1 when two IRQ lines are available */
#define PL18X_MMCI_IRQ1MASK	(PL18X_MMCI_RXFIFOHALFFULLMASK | PL18X_MMCI_RXDATAAVLBLMASK | PL18X_MMCI_TXFIFOHALFEMPTYMASK)

/** PL18X specific types */
typedef struct _PL18X_VERSIONDATA PL18X_VERSIONDATA;

typedef struct _PL18X_VERSIONID PL18X_VERSIONID;
struct _PL18X_VERSIONID
{
	uint32_t peripheralid;
	uint32_t peripheralmask;
	PL18X_VERSIONDATA *versiondata;
};


struct _PL18X_VERSIONDATA
{
	char *name; ///< Name of the device
	uint32_t clockregister; ///< Default value for MCICLOCK register
	uint32_t clockenable; ///< Enable value for MMCICLOCK register
	uint32_t clock8bitenable; ///< Enable value for 8 bit bus
	uint32_t clocknegativeedgeenable; ///< Enable value for inverted data/cmd output
	uint32_t datalengthbits; ///< Number of bits in the MMCIDATALENGTH register
	uint32_t fifosize; ///< Number of bytes that can be written when MMCI_TXFIFOEMPTY is asserted (likewise for RX)
	uint32_t fifohalfsize; ///< Number of bytes that can be written when MCI_TXFIFOHALFEMPTY is asserted (likewise for RX)
	uint32_t datacommandenable; ///< Enable value for data commands
	uint32_t datacontrolmaskddr; ///< DDR mode mask in MMCIDATACTRL register
	uint32_t datacontrolmasksdio; ///< SDIO enable mask in MMCIDATACTRL register
	LONGBOOL stsdio; ///< Enable ST specific SDIO logic
	LONGBOOL stclockdivider; ///< True if using a ST-specific clock divider algorithm
	LONGBOOL blocksizedatacontrol16; ///< True if Block size is at b16..b30 position in MMCIDATACTRL register
	LONGBOOL blocksizedatacontrol4; ///< True if Block size is at b4..b16 position in MMCIDATACTRL register
	uint32_t powerpowerup; ///< Power up value for MMCIPOWER register
	uint32_t clockmaximum; ///< Maximum clk frequency supported by the controller
	LONGBOOL signaldirection; ///< Input/out direction of bus signals can be indicated
	LONGBOOL powerclockgate; ///< MMCIPOWER register must be used to gate the clock
	LONGBOOL busydetect; ///< True if busy detection on dat0 is supported
	LONGBOOL powernopower; ///< Bits in MMCIPOWER don't control external power supply
	LONGBOOL explicitmclockcontrol; ///< Enable explicit mclk control in driver
	LONGBOOL qualcommfifo; ///< Enable Qualcomm specific FIFO PIO read logic
	LONGBOOL qualcommdma; ///< Enable Qualcomm specific DMA glue for DMA transfers
	LONGBOOL reversedirq; ///< Handle data irq before cmd irq
};


/** Layout of the PL18X registers (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0172a/i1006458.html) */
typedef struct _PL18X_MMCIREGISTERS PL18X_MMCIREGISTERS;
struct _PL18X_MMCIREGISTERS
{
	uint32_t power; ///< Power control register
	uint32_t clock; ///< Clock control register
	uint32_t argument; ///< Argument register
	uint32_t command; ///< Command register
	uint32_t respcmd; ///< Response command register
	uint32_t response0; ///< Response register
	uint32_t response1; ///< Response register
	uint32_t response2; ///< Response register
	uint32_t response3; ///< Response register
	uint32_t datatimer; ///< Data timer
	uint32_t datalength; ///< Data length register
	uint32_t datactrl; ///< Data control register
	uint32_t datacnt; ///< Data counter
	uint32_t status; ///< Status register
	uint32_t clear; ///< Clear register
	uint32_t mask0; ///< Interrupt 0 mask register
	uint32_t mask1; ///< Interrupt 1 mask register
	uint32_t select; ///< Secure digital memory card select register
	uint32_t fifocnt; ///< FIFO counter
	uint8_t reserved[0x30]; ///< Reserved
	uint32_t fifo; ///< Data FIFO register (0x80 to 0xBC)
};


/** PL18X SDHCI types */
typedef struct _PL18X_SDHCIHOST PL18X_SDHCIHOST;

/** PL18X SDHCI Host Methods */
typedef uint32_t STDCALL (*pl18xsdhci_get_rxfifo_count_proc)(PL18X_SDHCIHOST *sdhci, uint32_t status, uint32_t remain);

struct _PL18X_SDHCIHOST
{
	// SDHCI Properties
	SDHCI_HOST sdhci;
	// PL18X Properties
	uint32_t irq0; ///< First host IRQ line
	uint32_t irq1; ///< Second host IRQ line
	LONGBOOL enablefiq; ///< Use FIQ instead of IRQ
	LONGBOOL singleirq; ///< The host only has a single IRQ line instead of the standard 2 lines
	PL18X_MMCIREGISTERS *registers; ///< Host registers
	PL18X_VERSIONDATA *version; ///< Host version data
	uint32_t clockregister; ///< Current clock register value
	uint32_t powerregister; ///< Current power register value
	uint32_t datactrlregister; ///< Current data control register value
	uint32_t busystatus; ///< Current Busy Status for ST Micro variants
	pl18xsdhci_get_rxfifo_count_proc getrxfifocount; ///< Model specific get_rxfifo_count function
};

/** Initialization Functions */
void STDCALL pl18x_init(void);

/** PL18X Functions */

/**
 * @brief Create and register a new PL180 SDHCI device which can be accessed using the SDHCI API
 * @param Address The address of the PL180 registers
 * @param Name The text description of this device which will show in the device list (Optional)
 * @param IRQ0 The interrupt 0 number for the PL180
 * @param IRQ1 The interrupt 1 number for the PL180
 * @param ClockMinimum The minimum frequency for the Pl180 clock
 * @param ClockMaximum The maximum frequency for the Pl180 clock
 * @return Pointer to the new SDHCI device or nil if the SDHCI device could not be created
 */
SDHCI_HOST * STDCALL pl180sdhci_create(size_t address, char *name, uint32_t irq0, uint32_t irq1, uint32_t clockminimum, uint32_t clockmaximum, mmc_device_get_card_detect_proc carddetect, mmc_device_get_write_protect_proc writeprotect);

/**
 * @brief Create and register a new PL181 SDHCI device which can be accessed using the SDHCI API
 * @param Address The address of the PL181 registers
 * @param Name The text description of this device which will show in the device list (Optional)
 * @param IRQ0 The interrupt 0 number for the PL181
 * @param IRQ1 The interrupt 1 number for the PL181
 * @param ClockMinimum The minimum frequency for the Pl181 clock
 * @param ClockMaximum The maximum frequency for the Pl181 clock
 * @return Pointer to the new SDHCI device or nil if the SDHCI device could not be created
 */
SDHCI_HOST * STDCALL pl181sdhci_create(size_t address, char *name, uint32_t irq0, uint32_t irq1, uint32_t clockminimum, uint32_t clockmaximum, mmc_device_get_card_detect_proc carddetect, mmc_device_get_write_protect_proc writeprotect);

/**
 * @brief Stop, deregister and destroy a PL18X SDHCI device created by this driver
 * @param SDHCI The SDHCI device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL pl18xsdhci_destroy(SDHCI_HOST *sdhci);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PL18X_H
