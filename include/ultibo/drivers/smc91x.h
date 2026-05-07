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
#ifndef _ULTIBO_SMC91X_H
#define _ULTIBO_SMC91X_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/network.h"
#include "ultibo/threads.h"

/** SMC91X specific constants */
#define SMC91X_NETWORK_DESCRIPTION	"SMSC 91C9x/91C1xx Ethernet" ///< Description of SMC91X device

#define SMC91X_COMPLETION_THREAD_STACK_SIZE	SIZE_128K ///< Stack size of receive and transmit completion thread
#define SMC91X_COMPLETION_THREAD_PRIORITY	THREAD_PRIORITY_HIGHER ///< Priority of receive and transmit completion thread

#define SMC91X_COMPLETION_THREAD_NAME	"SMSC 91C9x/91C1xx Completion" ///< Name of receive and transmit completion thread

#define SMC91X_COMPLETION_RECEIVE	0 ///< A receive message sent to the completion thread
#define SMC91X_COMPLETION_TRANSMIT	1 ///< A transmit message sent to the completion thread
#define SMC91X_COMPLETION_ALLOCATE	2 ///< An allocate message sent to the completion thread
#define SMC91X_COMPLETION_TERMINATE	3 ///< A terminate message sent to the completion thread

#define SMC91X_MAX_TX_ENTRIES	SIZE_16 ///< Number of Transmit buffers allocated
#define SMC91X_MAX_RX_ENTRIES	SIZE_256 ///< Number of Receive buffers allocated

#define SMC91X_MAX_PACKET_SIZE	2048

/** SMC91X Transmit Control register constants */
#define SMC91X_TCR_ENABLE	0x0001 ///< Transmit enabled when set
#define SMC91X_TCR_LOOP	0x0002 ///< Loopback. General purpose output port used to control the LBK pin
#define SMC91X_TCR_FORCOL	0x0004 ///< When set, the FORCOL bit will force a collision by not deferring deliberately
#define SMC91X_TCR_PAD_EN	0x0080 ///< When set, will pad transmit frames shorter than 64 bytes with 00
#define SMC91X_TCR_NOCRC	0x0100 ///< Does not append CRC to transmitted frames when set
#define SMC91X_TCR_MON_CSN	0x0400 ///< When set monitors carrier while transmitting
#define SMC91X_TCR_FDUPLX	0x0800 ///< When set will cause frames to be received if they pass the address filter regardless of the source for the frame. When clear the node will not receive a frame sourced by itself
#define SMC91X_TCR_STP_SQET	0x1000 ///< Stop transmission on SQET error. If this bit is set, will stop and disable the transmitter on SQE test error
#define SMC91X_TCR_EPH_LOOP	0x2000 ///< Internal loopback at the EPH block
#define SMC91X_TCR_SWFDUP	0x8000 ///< Enables Switched Full Duplex mode

/** Default settings */
#define SMC91X_TCR_DEFAULT	SMC91X_TCR_ENABLE | SMC91X_TCR_PAD_EN
#define SMC91X_TCR_CLEAR	0

/** SMC91X EPH Status register constants (Ethernet Protocol Handler) */
#define SMC91X_EPH_STATUS_TX_SUC	0x0001 ///< Last transmit was successful. Set if transmit completes without a fatal error
#define SMC91X_EPH_STATUS_SNGL_COL	0x0002 ///< Single collision detected for the last transmit frame. Set when a collision is detected
#define SMC91X_EPH_STATUS_MUL_COL	0x0004 ///< Multiple collision detected for the last transmit frame. Set when more than one collision was experienced
#define SMC91X_EPH_STATUS_LTX_MULT	0x0008 ///< Last transmit frame was a multicast. Set if frame was a multicast
#define SMC91X_EPH_STATUS_16COL	0x0010 ///< 16 collisions reached. Set when 16 collisions are detected for a transmit frame
#define SMC91X_EPH_STATUS_SQET	0x0020 ///< Signal Quality Error Test
#define SMC91X_EPH_STATUS_LTXBRD	0x0040 ///< Last transmit frame was a broadcast. Set if frame was broadcast
#define SMC91X_EPH_STATUS_TXDEFR	0x0080 ///< Transmit Deferred. When set, carrier was detected during the first 6.4us of the inter frame gap
#define SMC91X_EPH_STATUS_LATCOL	0x0200 ///< Late collision detected on last transmit frame. If set a late collision was detected (later than 64 byte times into the frame)
#define SMC91X_EPH_STATUS_LOSTCARR	0x0400 ///< Lost Carrier Sense. When set indicates that Carrier Sense was not present at end of preamble
#define SMC91X_EPH_STATUS_EXC_DEF	0x0800 ///< Excessive Deferral. When set last/current transmit was deferred for more than 1518 * 2 byte times
#define SMC91X_EPH_STATUS_CTR_ROL	0x1000 ///< Counter Roll Over. When set one or more 4 bit counters have reached maximum count (15)
#define SMC91X_EPH_STATUS_LINK_OK	0x4000 ///< General purpose input port driven by nLNK pin inverted
#define SMC91X_EPH_STATUS_TXUNRN	0x8000 ///< TX Underrun

/** SMC91X Receive Control register constants */
#define SMC91X_RCR_RX_ABORT	0x0001 ///< This bit is set if a receive frame was aborted due to length longer than 2K bytes. The frame will not be received. The bit is cleared by RESET or by the CPU writing it low
#define SMC91X_RCR_PRMS	0x0002 ///< Promiscuous mode. When set receives all frames. Does not receive its own transmission unless it is in Full Duplex
#define SMC91X_RCR_ALMUL	0x0004 ///< When set accepts all multicast frames (frames in which the first bit of DA is '1'). When clear accepts only the multicast frames that match the multicast table setting. Defaults low
#define SMC91X_RCR_RXEN	0x0100 ///< Enables the receiver when set. If cleared, completes receiving current frame and then goes idle. Defaults low on reset
#define SMC91X_RCR_STRIP_CRC	0x0200 ///< When set, it strips the CRC on received frames. As a result, both the Byte Count and the frame format do not contain the CRC. When clear, the CRC is stored in memory following the packet. Defaults low
#define SMC91X_RCR_ABORT_ENB	0x0200 ///< Enables abort of receive when collision occurs. Defaults low. When set, will automatically abort a packet being received when the appropriate collision input is activated
#define SMC91X_RCR_FILT_CAR	0x0400 ///< Filter Carrier. When set filters leading edge of carrier sense for 12 bit times (3 nibble times). Otherwise recognizes a receive frame as soon as carrier sense is active. (Does NOT filter RX DV on MII)
#define SMC91X_RCR_SOFTRST	0x8000 ///< Software-Activated Reset. Active high. Initiated by writing this bit high and terminated by writing the bit low

/** Default settings */
#define SMC91X_RCR_DEFAULT	SMC91X_RCR_STRIP_CRC | SMC91X_RCR_RXEN
#define SMC91X_RCR_CLEAR	0

/** SMC91X Receive/PHY Control register constants */
#define SMC91X_RPC_SPEED	0x2000 ///< Speed select Input (1=100Mbps / 0=0Mbps)
#define SMC91X_RPC_DPLX	0x1000 ///< Duplex Select - This bit selects Full/Half Duplex operation (1=Full Duplex / 0=Half Duplex))
#define SMC91X_RPC_ANEG	0x0800 ///< Auto-Negotiation mode select
#define SMC91X_RPC_LS2A	0x0080 ///< LED select Signal Enable. These bits define what LED control signals are routed to the LEDA output pin on the Ethernet Controller. The default is 10/100 Link detected
#define SMC91X_RPC_LS1A	0x0040
#define SMC91X_RPC_LS0A	0x0020
#define SMC91X_RPC_LS2B	0x0010 ///< LED select Signal Enable. These bits define what LED control signals are routed to the LEDB output pin on the Ethernet Controller. The default is 10/100 Link detected
#define SMC91X_RPC_LS1B	0x0008
#define SMC91X_RPC_LS0B	0x0004

/** Default Settings */
#define SMC91X_RPC_DEFAULT	SMC91X_RPC_ANEG | SMC91X_RPC_SPEED | SMC91X_RPC_DPLX

/** RPC LS2A/LS1A/LS0A and LS2B/LS1B/LS0B values */
#define SMC91X_RPC_LED_100_10	0x00 ///< LED = 100Mbps OR's with 10Mbps link detect
#define SMC91X_RPC_LED_RES	0x01 ///< LED = Reserved
#define SMC91X_RPC_LED_10	0x02 ///< LED = 10Mbps link detect
#define SMC91X_RPC_LED_FD	0x03 ///< LED = Full Duplex Mode
#define SMC91X_RPC_LED_TX_RX	0x04 ///< LED = TX or RX packet occurred
#define SMC91X_RPC_LED_100	0x05 ///< LED = 100Mbps link detect
#define SMC91X_RPC_LED_TX	0x06 ///< LED = TX packet occurred
#define SMC91X_RPC_LED_RX	0x07 ///< LED = RX packet occurred

/** SMC91X Configuration register constants */
#define SMC91X_CONFIG_EXT_PHY	0x0200 ///< External PHY Enabled (1=Enables the external MII / 0=Internal PHY is enabled)
#define SMC91X_CONFIG_GPCNTRL	0x0400 ///< This bit is a general purpose output port. Its inverse value drives pin nCNTRL and it is typically connected to a SELECT pin of the external PHY device such as a power enable
#define SMC91X_CONFIG_NO_WAIT	0x1000 ///< When set, does not request additional wait states. An exception to this are accesses to the Data Register if not ready for a transfer
#define SMC91X_CONFIG_EPH_POWER_EN	0x8000 ///< Used to selectively power transition the EPH to a low power mode. When this bit is cleared (0), the Host will place the EPH into a low power mode
#define SMC91X_CONFIG_RESERVED	0x20B1 ///< Reserved values

/** Default is powered-up, Internal Phy, Wait States, and pin nCNTRL=low */
#define SMC91X_CONFIG_DEFAULT	SMC91X_CONFIG_EPH_POWER_EN

/** SMC91X Control register constants */
#define SMC91X_CTL_RCV_BAD	0x4000 ///< When set, bad CRC packets are received. When clear bad CRC packets do not generate interrupts and their memory is released
#define SMC91X_CTL_AUTO_RELEASE	0x0800 ///< When set, transmit pages are released by transmit completion if the transmission was successful (when TX_SUC is set)
#define SMC91X_CTL_LE_ENABLE	0x0080 ///< Link Error Enable. When set it enables the LINK_OK bit transition as one of the interrupts merged into the EPH INT bit
#define SMC91X_CTL_CR_ENABLE	0x0040 ///< Counter Roll over Enable. When set, it enables the CTR_ROL bit as one of the interrupts merged into the EPH INT bit
#define SMC91X_CTL_TE_ENABLE	0x0020 ///< Transmit Error Enable. When set it enables Transmit Error as one of the interrupts merged into the EPH INT bit
#define SMC91X_CTL_EEPROM_SELECT	0x0004 ///< This bit allows the CPU to specify which registers the EEPROM RELOAD or STORE refers to
#define SMC91X_CTL_RELOAD	0x0002 ///< When set it will read the EEPROM and update relevant registers with its contents
#define SMC91X_CTL_STORE	0x0001 ///< When set, stores the contents of all relevant registers in the serial EEPROM

/** SMC91X MMU Command register constants */
#define SMC91X_MMU_CMD_BUSY	1 ///< When 1 the last command has not completed
#define SMC91X_MMU_CMD_NOP	(0 << 5) ///< NOOP - NO OPERATION
#define SMC91X_MMU_CMD_ALLOC	(1 << 5) ///< ALLOCATE MEMORY FOR TX (OR with number of 256 byte packets)
#define SMC91X_MMU_CMD_RESET	(2 << 5) ///< RESET MMU TO INITIAL STATE (Frees all memory allocations, clears relevant interrupts, resets packet FIFO pointers)
#define SMC91X_MMU_CMD_REMOVE	(3 << 5) ///< REMOVE FRAME FROM TOP OF RX FIFO (To be issued after CPU has completed processing of present receive frame)
#define SMC91X_MMU_CMD_RELEASE	(4 << 5) ///< REMOVE AND RELEASE TOP OF RX FIFO (Like 3) but also releases all memory used by the packet presently at the RX FIFO output)
#define SMC91X_MMU_CMD_FREEPKT	(5 << 5) ///< RELEASE SPECIFIC PACKET (Frees all pages allocated to the packet specified in the PACKET NUMBER REGISTER)
#define SMC91X_MMU_CMD_ENQUEUE	(6 << 5) ///< ENQUEUE PACKET NUMBER INTO TX FIFO (This is the normal method of transmitting a packet just loaded into RAM)
#define SMC91X_MMU_CMD_RSTTXFIFO	(7 << 5) ///< RESET TX FIFOs (This command will reset both TX FIFOs)

/** SMC91X Allocation Result register constants */
#define SMC91X_AR_FAILED	0x80 ///< FAILED - A zero indicates a successful allocation completion. If the allocation fails the bit is set and only cleared when the pending allocation is satisfied

/** SMC91X TX FIFO Ports register constants */
#define SMC91X_TXFIFO_TEMPTY	0x80 ///< TEMPTY - No transmit packets in completion queue. For polling purposes, uses the TX_INT bit in the Interrupt Status Register

/** SMC91X RX FIFO Ports register constants */
#define SMC91X_RXFIFO_REMPTY	0x80 ///< REMPTY - No receive packets queued in the RX FIFO. For polling purposes, uses the RCV_INT bit in the Interrupt Status Register

/** SMC91X Pointer register constants */
#define SMC91X_PTR_RCV	0x8000 ///< When RCV is set the address refers to the receive area and uses the output of RX FIFO as the packet number, when RCV is clear the address refers to the transmit area and uses the packet number at the Packet Number Register
#define SMC91X_PTR_AUTOINC	0x4000 ///< It will auto-increment on accesses to the data register when AUTO INCR is set. The increment is by one for every byte access, by two for every word access, and by four for every double word access
#define SMC91X_PTR_READ	0x2000 ///< Determines the type of access to follow. If the READ bit is high the operation intended is a read

/** SMC91X Interrupt Mask register constants */
#define SMC91X_IM_MDINT	0x80 ///< PHY MI Register 18 Interrupt
#define SMC91X_IM_ERCV_INT	0x40 ///< Early Receive Interrupt
#define SMC91X_IM_EPH_INT	0x20 ///< Set by Ethernet Protocol Handler section
#define SMC91X_IM_RX_OVRN_INT	0x10 ///< Set by Receiver Overruns
#define SMC91X_IM_ALLOC_INT	0x08 ///< Set when allocation request is completed
#define SMC91X_IM_TX_EMPTY_INT	0x04 ///< Set if the TX FIFO goes empty
#define SMC91X_IM_TX_INT	0x02 ///< Transmit Interrupt
#define SMC91X_IM_RCV_INT	0x01 ///< Receive Interrupt

/** SMC91X Management Interface register constants */
#define SMC91X_MII_MSK_CRS100	0x4000 ///< Disables CRS100 detection during tx half dup
#define SMC91X_MII_MDOE	0x0008 ///< MII Output Enable
#define SMC91X_MII_MCLK	0x0004 ///< MII Clock, pin MDCLK
#define SMC91X_MII_MDI	0x0002 ///< MII Input, pin MDI
#define SMC91X_MII_MDO	0x0001 ///< MII Output, pin MDO

#define SMC91X_MII_DELAY	1 ///< The MII clock high/low times. 2 x this number gives the MII clock period in microseconds

/** SMC91X Receive register constants */
#define SMC91X_RCV_RCV_DISCRD	0x0080 ///< Set to discard a packet being received. Will discard packets only in the process of being received
#define SMC91X_RCV_THRESHOLD	0x001F ///< RCV Threshold Mask

/** SMC91X Receive status constants */
#define SMC91X_RCV_ALGNERR	0x8000 ///< Frame has alignment error
#define SMC91X_RCV_BRODCAST	0x4000 ///< Receive frame was Broadcast (The Multicast bit may also be set, software must ignore the Multicast bit for a Broadcast packet)
#define SMC91X_RCV_BADCRC	0x2000 ///< Frame has CRC error or RX_ER was asserted during reception
#define SMC91X_RCV_ODDFRAME	0x1000 ///< This bit when set indicates that the received frame has an odd number of bytes
#define SMC91X_RCV_TOOLONG	0x0800 ///< Frame length was longer than 802.3 maximum size (1518 bytes on the cable)
#define SMC91X_RCV_TOOSHORT	0x0400 ///< Frame length was shorter than 802.3 minimum size (64 bytes on the cable)
#define SMC91X_RCV_MULTICAST	0x0001 ///< Receive frame was Multicast
#define SMC91X_RCV_ERRORS	(SMC91X_RCV_ALGNERR | SMC91X_RCV_BADCRC | SMC91X_RCV_TOOLONG | SMC91X_RCV_TOOSHORT)

/** SMC91X Bank Select register constants */
#define SMC91X_BANK_SELECT_0	0
#define SMC91X_BANK_SELECT_1	1
#define SMC91X_BANK_SELECT_2	2
#define SMC91X_BANK_SELECT_3	3

/** SMC91X Chip constants (Bits 4-7 of the Revision register) */
#define SMC91X_CHIP_COUNT	16

#define SMC91X_CHIP_9192	3
#define SMC91X_CHIP_9194	4
#define SMC91X_CHIP_9195	5
#define SMC91X_CHIP_9196	6
#define SMC91X_CHIP_91100	7
#define SMC91X_CHIP_91100FD	8
#define SMC91X_CHIP_91111FD	9

/** SMC91X PHY IDs */
#define SMC91X_PHY_LAN83C183	0x0016f840 ///< LAN83C183 = LAN91C111 Internal PHY
#define SMC91X_PHY_LAN83C180	0x02821c50

/** SMC91X PHY Register Addresses (LAN91C111 Internal PHY) */
/** Register 0. Control Register */
/** See: Network Generic MII registers (MII_BMCR) */

/** Register 1. Status Register */
/** See: Network Generic MII registers (MII_BMSR) */

/** Register 2 & 3. PHY Identifier Register */
/** See: Network Generic MII registers (MII_PHYSID1 / MII_PHYSID2) */

/** Register 4. Auto-Negotiation Advertisement Register */
/** See: Network Generic MII registers (MII_ADVERTISE) */

/** Register 5. Auto-Negotiation Remote End Capability Register */
/** See: Network Generic MII registers (MII_LPA) */

/** Register 16. Configuration 1- Structure and Bit Definition */
#define SMC91X_PHY_CFG1_REG	0x10
#define SMC91X_PHY_CFG1_LNKDIS	0x8000 ///< 1=Rx Link Detect Function disabled
#define SMC91X_PHY_CFG1_XMTDIS	0x4000 ///< 1=TP Transmitter Disabled
#define SMC91X_PHY_CFG1_XMTPDN	0x2000 ///< 1=TP Transmitter Powered Down
#define SMC91X_PHY_CFG1_BYPSCR	0x0400 ///< 1=Bypass scrambler/descrambler
#define SMC91X_PHY_CFG1_UNSCDS	0x0200 ///< 1=Unscramble Idle Reception Disable
#define SMC91X_PHY_CFG1_EQLZR	0x0100 ///< 1=Rx Equalizer Disabled
#define SMC91X_PHY_CFG1_CABLE	0x0080 ///< 1=STP(150ohm), 0=UTP(100ohm)
#define SMC91X_PHY_CFG1_RLVL0	0x0040 ///< 1=Rx Squelch level reduced by 4.5db
#define SMC91X_PHY_CFG1_TLVL_SHIFT	2 ///< Transmit Output Level Adjust
#define SMC91X_PHY_CFG1_TLVL_MASK	0x003C
#define SMC91X_PHY_CFG1_TRF_MASK	0x0003 ///< Transmitter Rise/Fall time

/** Register 17. Configuration 2 - Structure and Bit Definition */
#define SMC91X_PHY_CFG2_REG	0x11
#define SMC91X_PHY_CFG2_APOLDIS	0x0020 ///< 1=Auto Polarity Correction disabled
#define SMC91X_PHY_CFG2_JABDIS	0x0010 ///< 1=Jabber disabled
#define SMC91X_PHY_CFG2_MREG	0x0008 ///< 1=Multiple register access (MII mgt)
#define SMC91X_PHY_CFG2_INTMDIO	0x0004 ///< 1=Interrupt signaled with MDIO pulseo

/** Register 18. Status Output - Structure and Bit Definition */
#define SMC91X_PHY_INT_REG	0x12 ///< Status Output (Interrupt Status)
#define SMC91X_PHY_INT_INT	0x8000 ///< 1=bits have changed since last read
#define SMC91X_PHY_INT_LNKFAIL	0x4000 ///< 1=Link Not detected
#define SMC91X_PHY_INT_LOSSSYNC	0x2000 ///< 1=Descrambler has lost sync
#define SMC91X_PHY_INT_CWRD	0x1000 ///< 1=Invalid 4B5B code detected on rx
#define SMC91X_PHY_INT_SSD	0x0800 ///< 1=No Start Of Stream detected on rx
#define SMC91X_PHY_INT_ESD	0x0400 ///< 1=No End Of Stream detected on rx
#define SMC91X_PHY_INT_RPOL	0x0200 ///< 1=Reverse Polarity detected
#define SMC91X_PHY_INT_JAB	0x0100 ///< 1=Jabber detected
#define SMC91X_PHY_INT_SPDDET	0x0080 ///< 1=100Base-TX mode, 0=10Base-T mode
#define SMC91X_PHY_INT_DPLXDET	0x0040 ///< 1=Device in Full Duplex

/** Register 19. Mask - Structure and Bit Definition */
#define SMC91X_PHY_MASK_REG	0x13 ///< Interrupt Mask

/** Register 20. Reserved - Structure and Bit Definition */
/** Nothing */

/** SMC91X specific types */
/** Layout of the SMC91X registers */
typedef struct
{
	uint16_t tcr; ///< Transmit Control Register
	uint16_t eph_status; ///< EPH Status Register
	uint16_t rcr; ///< Receive Control Register
	uint16_t counter; ///< Counter Register
	uint16_t mir; ///< Memory Information Register
	uint16_t rpcr; ///< Receive/Phy Control Register
	uint16_t reserved; ///< Reserved
	uint16_t bank; ///< Bank Select Register
} PACKED SMC91X_BANK0_REGISTERS;


typedef struct
{
	uint16_t config; ///< Configuration Register
	uint16_t base; ///< Base Address Register
	uint16_t addr0; ///< Individual Address Registers (0 and 1)
	uint16_t addr1; ///< Individual Address Registers (2 and 3)
	uint16_t addr2; ///< Individual Address Registers (4 and 5)
	uint16_t gp; ///< General Purpose Register
	uint16_t ctl; ///< Control Register
	uint16_t bank; ///< Bank Select Register
} PACKED SMC91X_BANK1_REGISTERS;


typedef union
{
	uint16_t fifo;
	struct
	{
		uint8_t tx;
		uint8_t rx;
	};
} PACKED SMC91X_FIFO_REGISTERS;


typedef union
{
	uint32_t data;
	struct
	{
		uint16_t datah;
		uint16_t datal;
	};
	struct
	{
		uint8_t data0;
		uint8_t data1;
		uint8_t data2;
		uint8_t data3;
	};
} PACKED SMC91X_DATA_REGISTERS;


typedef struct
{
	uint16_t mmu_cmd; ///< MMU Command Register
	uint8_t pn; ///< Packet Number Register
	uint8_t ar; ///< Allocation Result Register
	SMC91X_FIFO_REGISTERS fifo; ///< FIFO Ports Register
	uint16_t ptr; ///< Pointer Register
	SMC91X_DATA_REGISTERS data; ///< Data Register
	uint8_t int_sts; ///< Interrupt Status Register
	uint8_t im; ///< Interrupt Mask Register
	uint16_t bank; ///< Bank Select Register
} PACKED SMC91X_BANK2_REGISTERS;


typedef struct
{
	uint16_t mcast1; ///< Multicast Table Registers (0 and 1)
	uint16_t mcast2; ///< Multicast Table Registers (2 and 3)
	uint16_t mcast3; ///< Multicast Table Registers (4 and 5)
	uint16_t mcast4; ///< Multicast Table Registers (6 and 7)
	uint16_t mii; ///< Management Interface Register
	uint16_t rev; ///< Revision Register
	uint16_t rcv; ///< RCV Register
	uint16_t bank; ///< Bank Select Register
} PACKED SMC91X_BANK3_REGISTERS;


typedef union _SMC91X_REGISTERS SMC91X_REGISTERS;
union _SMC91X_REGISTERS
{
	SMC91X_BANK0_REGISTERS bank0; ///< Bank 0 Registers
	SMC91X_BANK1_REGISTERS bank1; ///< Bank 1 Registers
	SMC91X_BANK2_REGISTERS bank2; ///< Bank 2 Registers
	SMC91X_BANK3_REGISTERS bank3; ///< Bank 3 Registers
} PACKED;


typedef struct _SMC91X_NETWORK SMC91X_NETWORK;
struct _SMC91X_NETWORK
{
	// Network Properties
	NETWORK_DEVICE network;
	// SMC91X Properties
	uint32_t irq;
	SPIN_HANDLE lock; ///< Device lock (Differs from lock in Network device) (Spin lock due to use by interrupt handler)
	THREAD_HANDLE thread; ///< Thread for handling packet receive and transmit completion
	uint32_t start; ///< First receive entry available for incoming packet
	uint32_t count; ///< Number of receive entries available for incoming packets
	NETWORK_ENTRY *entries[SMC91X_MAX_RX_ENTRIES]; ///< Queue of receive entries for handling incoming packets
	SMC91X_REGISTERS *registers; ///< Device registers
	uint16_t revision; ///< Device revision
	uint32_t phyid; ///< Physical Interface (PHY) Address
	uint32_t phytype; ///< Physical Interface (PHY) Type
	uint32_t tcrflags; ///< Current Transmit Control Register (TCR) flags
	uint32_t rcrflags; ///< Current Receive Control Register (RCR) flags
	uint32_t rpcflags; ///< Current Receive/PHY Control Register (RPC) flags
	// Statistics Properties
	uint32_t interruptcount; ///< Number of interrupt requests received by the device
	uint32_t collisioncount; ///< Number of transmit collisions detected by the device
};

/** SMC91X Functions */
NETWORK_DEVICE * STDCALL smc91x_network_create(size_t address, char *name, uint32_t irq);
uint32_t STDCALL smc91x_network_destroy(NETWORK_DEVICE *network);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_SMC91X_H
