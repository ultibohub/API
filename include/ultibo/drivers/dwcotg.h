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
#ifndef _ULTIBO_DWCOTG_H
#define _ULTIBO_DWCOTG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/threads.h"
#include "ultibo/usb.h"

/* ============================================================================== */
/* DWCOTG specific constants */
#define DWCOTG_USBHOST_DESCRIPTION	"DWCOTG USB Host" // Description of DWCOTG host

#define DWC_MAX_CHANNELS	16 // Maximum number of DWC host channels

#define DWC_SCHEDULER_MAILSLOT_SIZE	SIZE_1K // Mailslot size for USB request scheduler

#define DWC_SCHEDULER_THREAD_STACK_SIZE	SIZE_32K // Stack size of USB request scheduler thread
#define DWC_SCHEDULER_THREAD_PRIORITY	THREAD_PRIORITY_HIGHEST // Priority of USB request scheduler thread (should be fairly high so that USB transfers can be started as soon as possible)

#define DWC_SCHEDULER_THREAD_NAME	"DWC Transfer Scheduler" // Name of USB request scheduler thread

#define DWC_COMPLETION_THREAD_STACK_SIZE	SIZE_32K // Stack size of USB request completion thread
#define DWC_COMPLETION_THREAD_PRIORITY	THREAD_PRIORITY_HIGHEST // Priority of USB request completion thread (should be fairly high so that USB transfers can be completed as soon as possible)

#define DWC_COMPLETION_THREAD_NAME	"DWC Transfer Completion" // Name of USB request completion thread

#define DWC_RESUBMIT_THREAD_STACK_SIZE	SIZE_32K // Stack size of USB request resubmit threads
#define DWC_RESUBMIT_THREAD_PRIORITY	THREAD_PRIORITY_CRITICAL // Priority of USB request resubmit threads (should be very high since these threads are used for the necessary software polling of interrupt endpoints, which are supposed to have guaranteed bandwidth)

#define DWC_RESUBMIT_THREAD_NAME	"DWC Transfer Resubmit" // Name of USB request resubmit threads

/* DWC USB packet ID constants recognized by the DWC hardware */
#define DWC_USB_PID_DATA0	0
#define DWC_USB_PID_DATA1	2
#define DWC_USB_PID_DATA2	1
#define DWC_USB_PID_SETUP	3
#define DWC_USB_PID_MDATA	3

/* DWC FIFO values */
#define DWC_RECEIVE_WORDS	1024 // Size of Rx FIFO in 4-byte words
#define DWC_TRANSMIT_WORDS	1024 // Size of Non-periodic Tx FIFO in 4-byte words
#define DWC_PERIODIC_TRANSMIT_WORDS	1024 // Size of Periodic Tx FIFO in 4-byte words

/* DWC Status codes */
#define DWC_STATUS_SUCCESS	0
#define DWC_STATUS_STALLED	1
#define DWC_STATUS_FAILED	2
#define DWC_STATUS_TRANSFER_RESUBMIT	3
#define DWC_STATUS_TRANSFER_RESTART	4
#define DWC_STATUS_TRANSACTION_RESTART	5
#define DWC_STATUS_HOST_PORT_CHANGE	6
#define DWC_STATUS_ROOT_HUB_REQUEST	7
#define DWC_STATUS_INVALID	8
#define DWC_STATUS_CANCELLED	9

/* DWC Complete Split */
#define DWC_SPLIT_ERROR_RETRIES	3
#define DWC_COMPLETE_SPLIT_RETRIES	10

/* DWC Register values */
/* TDWCRegisters: 0x0000 : OTG Control Register */
#define DWC_OTG_CTRL_HST_SET_HNP_EN	(1 << 10)

/* TDWCRegisters: 0x0008 : AHB Configuration Register */
/* Enable interrupts from the USB controller.  Disabled by default */
#define DWC_AHB_INTERRUPT_ENABLE	(1 << 0)
/* Bits [4:1] of the AHB Configuration register were redefined by Broadcom for the BCM2835 */
/* Max AXI burst length */
#define BCM_DWC_AHB_AXI_BURST_MASK	(3 << 1)
/* Wait for all outstanding AXI writes to complete before signalling (internally) that DMA is done */
#define BCM_DWC_AHB_AXI_WAIT	(1 << 4)
/* Writing 1 to this bit in the AHB Configuration Register allows the USB controller to perform DMA (Disabled by default) */
#define DWC_AHB_DMA_ENABLE	(1 << 5)
/* Unknown */
#define DWC_AHB_MASTER_IDLE	(1 << 31)

/* TDWCRegisters: 0x000c : Core USB Configuration Register */
#define DWC_USB_CFG_TOUTCAL_MASK	(7 << 0)
#define DWC_USB_CFG_TOUTCAL_LIMIT	(7 << 0)
#define DWC_USB_CFG_PHYIF16	(1 << 3)
#define DWC_USB_CFG_ULPI_UTMI_SEL	(1 << 4)
#define DWC_USB_CFG_FS_INTF	(1 << 5)
#define DWC_USB_CFG_PHY_SEL	(1 << 6)
#define DWC_USB_CFG_DDR_SEL	(1 << 7)
#define DWC_USB_CFG_SRP_CAPABLE	(1 << 8)
#define DWC_USB_CFG_HNP_CAPABLE	(1 << 9)
#define DWC_USB_CFG_USB_TRDTIM_MASK	(0xF << 10)
#define DWC_USB_CFG_RESERVED14	(1 << 14)
#define DWC_USB_CFG_PHY_LOW_PWR_CLK_SEL	(1 << 15)
#define DWC_USB_CFG_OTG_UTMI_FS_SEL	(1 << 16)
#define DWC_USB_CFG_ULPI_FSLS	(1 << 17)
#define DWC_USB_CFG_ULPI_AUTO_RES	(1 << 18)
#define DWC_USB_CFG_ULPI_CLK_SUS_M	(1 << 19)
#define DWC_USB_CFG_ULPI_EXT_VBUS_DRV	(1 << 20)
#define DWC_USB_CFG_ULPI_INT_VBUS_INDICATOR	(1 << 21)
#define DWC_USB_CFG_TERM_SEL_DL_PULSE	(1 << 22)
#define DWC_USB_CFG_INDICATOR_COMPLEMENT	(1 << 23)
#define DWC_USB_CFG_INDICATOR_PASS_THROUGH	(1 << 24)
#define DWC_USB_CFG_ULPI_INT_PROT_DIS	(1 << 25)
#define DWC_USB_CFG_IC_USB_CAP	(1 << 26)
#define DWC_USB_CFG_IC_TRAFFIC_PULL_REMOVE	(1 << 27)
#define DWC_USB_CFG_TX_END_DELAY	(1 << 28)
#define DWC_USB_CFG_FORCE_HOST_MODE	(1 << 29)
#define DWC_USB_CFG_FORCE_DEV_MODE	(1 << 30)
#define DWC_USB_CFG_RESERVED31	(1 << 31)

/* TDWCRegisters: 0x0010 : Core Reset Register */
/* Write 1 to this location in the Core Reset Register to start a soft reset.  This bit will then be cleared by the hardware when the reset is complete */
#define DWC_SOFT_RESET	(1 << 0)

/* TDWCRegisters: 0x0014 : Core Interrupt Register */
/* This register contains the state of pending top-level DWC interrupts.  1 means interrupt pending while 0 means no interrupt pending */
/* Note that at least for port_intr and host_channel_intr, software must clear the interrupt somewhere else rather than by writing to this register */
/* Start of Frame. */
#define DWC_CORE_INTERRUPTS_SOF_INTR	(1 << 3) // Bit 3
/* Host port status changed.  Software must examine the Host Port Control and Status Register to determine the current status of
  the host port and clear any flags in it that indicate a status change */
#define DWC_CORE_INTERRUPTS_PORT_INTR	(1 << 24) // Bit 24
/* Channel interrupt occurred.  Software must examine the Host All Channels Interrupt Register to determine which channel(s) have
  pending interrupts, then handle and clear the interrupts for these channels */
#define DWC_CORE_INTERRUPTS_HOST_CHANNEL_INTR	(1 << 25) // Bit 25
/* Disconnect interrupt indicated that a device has been disconnected from the root port */
#define DWC_CORE_INTERRUPTS_DISCONNECT	(1 << 29) // Bit 29

/* TDWCRegisters: 0x0040 : Vendor Id Register */
#define DWC_VENDOR_ID_OTG2	0x4f542000
#define DWC_VENDOR_ID_OTG3	0x4f543000

#define DWC_VENDOR_ID_MASK	0xfffff000

/* TDWCRegisters: 0x0048 : Hardware Configuration 2 */
#define DWC_HWCFG2_OP_MODE_MASK	(7 << 0)
#define DWC_HWCFG2_OP_MODE_HNP_SRP_CAPABLE_OTG	(0 << 0)
#define DWC_HWCFG2_OP_MODE_SRP_ONLY_CAPABLE_OTG	(1 << 0)
#define DWC_HWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE_OTG	(2 << 0)
#define DWC_HWCFG2_OP_MODE_SRP_CAPABLE_DEVICE	(3 << 0)
#define DWC_HWCFG2_OP_MODE_NO_SRP_CAPABLE_DEVICE	(4 << 0)
#define DWC_HWCFG2_OP_MODE_SRP_CAPABLE_HOST	(5 << 0)
#define DWC_HWCFG2_OP_MODE_NO_SRP_CAPABLE_HOST	(6 << 0)

#define DWC_HWCFG2_ARCHITECTURE_MASK	(3 << 3)
#define DWC_HWCFG2_ARCHITECTURE_SLAVE_ONLY	(0 << 3)
#define DWC_HWCFG2_ARCHITECTURE_EXT_DMA	(1 << 3)
#define DWC_HWCFG2_ARCHITECTURE_INT_DMA	(2 << 3)

#define DWC_HWCFG2_POINT2POINT	(1 << 5)

#define DWC_HWCFG2_HS_PHY_TYPE_MASK	(3 << 6)
#define DWC_HWCFG2_HS_PHY_TYPE_NOT_SUPPORTED	(0 << 6)
#define DWC_HWCFG2_HS_PHY_TYPE_UTMI	(1 << 6)
#define DWC_HWCFG2_HS_PHY_TYPE_ULPI	(2 << 6)
#define DWC_HWCFG2_HS_PHY_TYPE_UTMI_ULPI	(3 << 6)

#define DWC_HWCFG2_FS_PHY_TYPE_MASK	(3 << 8)
#define DWC_HWCFG2_FS_PHY_TYPE_NOT_SUPPORTED	(0 << 8)
#define DWC_HWCFG2_FS_PHY_TYPE_DEDICATED	(1 << 8)
#define DWC_HWCFG2_FS_PHY_TYPE_SHARED_UTMI	(2 << 8)
#define DWC_HWCFG2_FS_PHY_TYPE_SHARED_ULPI	(3 << 8)

#define DWC_HWCFG2_NUM_DEV_ENDPOINTS	(0xF << 10)
#define DWC_HWCFG2_NUM_HOST_CHANNELS	(0xF << 14)

#define DWC_HWCFG2_PERIODIC_ENDPOINT_SUPPORTED	(1 << 18)
#define DWC_HWCFG2_DYNAMIC_FIFO	(1 << 19)
#define DWC_HWCFG2_MULTI_PROC_INT	(1 << 20)
#define DWC_HWCFG2_RESERVED21	(1 << 21)
#define DWC_HWCFG2_NON_PERIODIC_TX_QUEUE_DEPTH	(3 << 22)
#define DWC_HWCFG2_HOST_PERIODIC_TX_QUEUE_DEPTH	(3 << 24)
#define DWC_HWCFG2_DEV_TOKEN_QUEUE_DEPTH	(0x1F << 26)
#define DWC_HWCFG2_OTG_ENABLE_IC_USB	(1 << 31)

/* TDWCRegisters: 0x0400 : Host Configuration Register */
#define DWC_HCFG_FS_LS_PHY_CLK_SEL_MASK	(3 << 0) // FS/LS Phy Clock Select
#define DWC_HCFG_FS_LS_PHY_CLK_SEL_SHIFT	0
#define DWC_HCFG_FS_LS_PHY_CLK_SEL_30_60_MHZ	0
#define DWC_HCFG_FS_LS_PHY_CLK_SEL_48_MHZ	1
#define DWC_HCFG_FS_LS_PHY_CLK_SEL_6_MHZ	2

#define DWC_HCFG_FS_LS_SUPPORT_ONLY	(1 << 2) // FS/LS Only Support

#define DWC_HCFG_ENABLE_32KHZ	(1 << 7) // Enable 32-KHz Suspend Mode

#define DWC_HCFG_RESUME_VALID_MASK	(0xFF << 8) // Resume Validation Period
#define DWC_HCFG_RESUME_VALID_SHIFT	8

#define DWC_HCFG_DESC_DMA	(1 << 23) // Enable Scatter/gather DMA in Host mode

#define DWC_HCFG_FRAME_LIST_ENTRIES_MASK	(3 << 24) // Frame List Entries
#define DWC_HCFG_FRAME_LIST_ENTRIES_SHIFT	24
#define DWC_HCFG_FRAME_LIST_ENTRIES_8	(0 << 24)
#define DWC_HCFG_FRAME_LIST_ENTRIES_8_SIZE	8
#define DWC_HCFG_FRAME_LIST_ENTRIES_16	(1 << 24)
#define DWC_HCFG_FRAME_LIST_ENTRIES_16_SIZE	16
#define DWC_HCFG_FRAME_LIST_ENTRIES_32	(3 << 24)
#define DWC_HCFG_FRAME_LIST_ENTRIES_32_SIZE	32
#define DWC_HCFG_FRAME_LIST_ENTRIES_64	(3 << 24)
#define DWC_HCFG_FRAME_LIST_ENTRIES_64_SIZE	64

#define DWC_HCFG_PERSCHED_ENA	(1 << 26) // Enable Periodic Scheduling
#define DWC_HCFG_MODE_CH_TIM_EN	(1 << 31)

/* TDWCRegisters: 0x0404 : Host Frame Interval Register */
#define DWC_HFIR_FRAME_INTERVAL_MASK	(0xFFFF << 0)
#define DWC_HFIR_FRAME_INT_RELOAD_CTL	(1 << 16)
#define DWC_HFIR_RESERVED1	(0xFFFE  << 17)

/* TDWCRegisters: 0x0408 : Host Frame Register */
#define DWC_HFNUM_FRAME_NUMBER_MASK	0xFFFF

/* TDWCRegisters: 0x0440 : Host Port Control and Status Register */
/* This register provides the information needed to respond to status queries about the "host port", which is the port that is logically attached to the root hub */
/* When changing this register, software must read its value, then clear the enabled, connected_changed, enabled_changed, and overcurrent_changed members to avoid
  changing them, as those particular bits are cleared by writing 1 */
/* 1: a device is connected to this port. 0: no device is connected to this port. Changed by hardware only */
#define DWC_HOST_PORT_CTRLSTATUS_CONNECTED	(1 << 0) // Bit 0
/* Set by hardware when connected bit changes.  Software can write 1 to acknowledge and clear.  The setting of this bit by hardware generates an interrupt that can be
  enabled by setting port_intr in the core_interrupt_mask register */
#define DWC_HOST_PORT_CTRLSTATUS_CONNECTED_CHANGED	(1 << 1) // Bit 1
/* 1: port is enabled. 0: port is disabled. Note: the host port is enabled by default after it is reset. Note: Writing 1 here appears to disable the port */
#define DWC_HOST_PORT_CTRLSTATUS_ENABLED	(1 << 2) // Bit 2
/* Set by hardware when enabled bit changes.  Software can write 1 to acknowledge and clear.  The setting of this bit by hardware generates an interrupt that can be
  enabled by setting port_intr in the core_interrupt_mask register */
#define DWC_HOST_PORT_CTRLSTATUS_ENABLED_CHANGED	(1 << 3) // Bit 3
/* 1: overcurrent condition active on this port 0: no overcurrent condition active on this port Changed by hardware only */
#define DWC_HOST_PORT_CTRLSTATUS_OVERCURRENT	(1 << 4) // Bit 4
/* Set by hardware when the overcurrent bit changes.  The software can write 1 to acknowledge and clear.  The setting of this bit by hardware generates the interrupt that can be
  enabled by setting port_intr in the core_interrupt_mask register */
#define DWC_HOST_PORT_CTRLSTATUS_OVERCURRENT_CHANGED	(1 << 5) // Bit 5
/* Set by software to set resume signalling */
#define DWC_HOST_PORT_CTRLSTATUS_RESUME	(1 << 6) // Bit 6
/* Set by software to suspend the port */
#define DWC_HOST_PORT_CTRLSTATUS_SUSPENDED	(1 << 7) // Bit 7
/* Software can set this to start a reset on this port. Software must clear this after waiting 60 milliseconds for the reset to complete */
#define DWC_HOST_PORT_CTRLSTATUS_RESET	(1 << 8) // Bit 8
#define DWC_HOST_PORT_CTRLSTATUS_RESERVED	(1 << 9) // Bit 9
/* Current logic of data lines (10: logic of D+; 11: logic of D-). Changed by hardware only */
#define DWC_HOST_PORT_CTRLSTATUS_LINE_STATUS	(3 << 10) // Bits 10-11
/* 1: port is powered. 0: port is not powered. Software can change this bit to power on (1) or power off (0) the port */
#define DWC_HOST_PORT_CTRLSTATUS_POWERED	(1 << 12) // Bit 12
#define DWC_HOST_PORT_CTRLSTATUS_TEST_CONTROL	(0x0F << 13) // Bits 13-16
/* Speed of attached device (if any).  This should only be considered meaningful if the connected bit is set. 00: high speed; 01: full speed; 10: low speed Changed by hardware only */
#define DWC_HOST_PORT_CTRLSTATUS_SPEED	(3 << 17) // Bits 17-18
#define DWC_HOST_PORT_CTRLSTATUS_RESERVED2	(0x1FFF << 19) // Bits 19-32

/* TDWCHostChannel: 0x0000 : Channel Characteristics Register */
/* Contains various fields that must be set to prepare this channel for a transfer to or from a particular endpoint on a particular USB device */
/* This register only needs to be programmed one time when doing a transfer, regardless of how many packets it consists of, unless the channel is
  re-programmed for a different transfer or the transfer is moved to a different channel */
/* Maximum packet size the endpoint is capable of sending or receiving.  Must be programmed by software before starting the transfer */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_MAX_PACKET_SIZE	(0x7FF << 0) // Bits 0-10
/* Endpoint number (low 4 bits of bEndpointAddress).  Must be programmed by software before starting the transfer */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_ENDPOINT_NUMBER	(0x0F << 11) // Bits 11-14
/* Endpoint direction (high bit of bEndpointAddress).  Must be programmed by software before starting the transfer */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_ENDPOINT_DIRECTION	(1 << 15) // Bit  15
#define DWC_HOST_CHANNEL_CHARACTERISTICS_RESERVED	(1 << 16) // Bit  16
/* 1 when the device being communicated with is attached at low speed; 0 otherwise.  Must be programmed by software before starting the transfer */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_LOWSPEED	(1 << 17) // Bit  17
/* Endpoint type (low 2 bits of bmAttributes).  Must be programmed by software before starting the transfer */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_ENDPOINT_TYPE	(3 << 18) // Bits 18-19
/* Maximum number of transactions that can be executed per microframe as part of this transfer.  Normally 1, but should be set to 1 + (bits 11 and 12 of wMaxPacketSize)
  for high-speed interrupt and isochronous endpoints.  Must be programmed by software before starting the transfer */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_PACKETS_PER_FRAME	(3 << 20) // Bits 20-21
/* USB device address of the device on which the endpoint is located.  Must be programmed by software before starting the transfer */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_DEVICE_ADDRESS	(0x7F << 22) // Bits 22-28
/* Just before enabling the channel (for all transactions), software needs to set this to the opposite of the low bit of the host_frame_number register.
  Otherwise the hardware will issue frame overrun errors on some transactions.  TODO: what exactly does this do? */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_ODD_FRAME	(1 << 29) // Bit  29
/* Software can set this to 1 to halt the channel. Not needed during normal operation as the channel halts automatically when a transaction completes or an error occurs */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_CHANNEL_DISABLE	(1 << 30) // Bit  30
/* Software can set this to 1 to enable the channel, thereby actually starting the transaction on the USB.  This must only be done after the characteristics, split_control,
  and transfer registers, and possibly other registers (depending on the transfer) have been programmed */
#define DWC_HOST_CHANNEL_CHARACTERISTICS_CHANNEL_ENABLE	(1 << 31) // Bit  31

/* TDWCHostChannel: 0x0004 : Channel Split Control Register */
/* This register is used to set up Split Transactions for communicating with low or full-speed devices attached to a high-speed hub.  When doing so, set split_enable to 1 and
  the other fields as documented. Otherwise, software must clear this register before starting the transfer */
/* Like the Channel Characteristics register, this register only needs to be programmed one time if the channel is enabled multiple times to send all the packets of a single transfer */
/* 0-based index of the port on the high-speed hub on which the low or full-speed device is attached. */
#define DWC_HOST_CHANNEL_SPLIT_CONTROL_PORT_ADDRESS	(0x7F << 0) // Bits 0-6
/* USB device address of the high-speed hub that acts as the Transaction Translator for this low or full-speed device. This is not necessarily the hub the device is physically
  connected to, since that could be a full-speed or low-speed hub.  Instead, software must walk up the USB device tree (towards the root hub) until a high-speed hub is found and
  use its device address here */
#define DWC_HOST_CHANNEL_SPLIT_CONTROL_HUB_ADDRESS	(0x7F << 7) // Bits 7-13
/* TODO: what exactly does this do? */
#define DWC_HOST_CHANNEL_SPLIT_CONTROL_TRANSACTION_POSITION	(3 << 14) // Bits 14-15
/* 0: Do a Start Split transaction 1: Do a Complete Split transaction. When split transactions are enabled, this must be programmed by software before enabling the channel.
  Note that you must begin with a Start Split transaction and alternate this bit for each transaction until the transfer is complete */
#define DWC_HOST_CHANNEL_SPLIT_CONTROL_COMPLETE_SPLIT	(1 << 16) // Bit  16
#define DWC_HOST_CHANNEL_SPLIT_CONTROL_RESERVED	(0x3FFF << 17) // Bits 17-30
/* Set to 1 to enable Split Transactions */
#define DWC_HOST_CHANNEL_SPLIT_CONTROL_SPLIT_ENABLE	(1 << 31) // Bit  31

/* TDWCHostChannel: 0x0008 : Channel Interrupts Register */
/* Bitmask of status conditions that have occurred on this channel */
/* These bits can be used with or without "real" interrupts.  To have the CPU get a real interrupt when one of these bits gets set, set the appropriate bit in the interrupt_mask,
  and also ensure that interrupts from the channel are enabled in the host_channels_interrupt_mask register, channel interrupts overall are enabled in the core_interrupt_mask register,
  and interrupts from the DWC hardware overall are enabled in the ahb_configuration register and by any system-specific interrupt controller */
/* The requested USB transfer has successfully completed
  Exceptions and caveats:
  - When doing split transactions, this bit will be set after a Complete Split transaction has finished, even though the overall transfer may not actually be complete.
  - The transfer will only be complete up to the extent that data was programmed into the channel.  For example, control transfers have 3 phases, each of which must be programmed
    into the channel separately.  This flag will be set after each of these phases has successfully completed.
  - An OUT transfer is otherwise considered complete when exactly the requested number of bytes of data have been successfully transferred, while an IN transfer is otherwise
    considered complete when exactly the requested number of bytes of data have been successfully transferred or a shorter-than-expected packet was received */
#define DWC_HOST_CHANNEL_INTERRUPTS_TRANSFER_COMPLETED	(1 << 0) // Bit 0
/* The channel has halted.  After this bit has been set, the channel sits idle and nothing else will happen until software takes action.
  Channels may halt for several reasons.  From our experience these cover all possible situations in which software needs to take action, so this is the only channel interrupt that
  actually needs to be enabled.  At least in DMA mode, the controller to some extent will act autonomously to complete transfers and only issue this interrupt when software needs
  to take action.
  Situations in which a channel will halt include but probably are not limited to:
  - The transfer has completed, thereby setting the transfer_completed flag as documented above.
  - A Start Split or Complete Split transaction has finished.                 
  - The hub sent a NYET packet when trying to execute a Complete Split transaction, thereby signalling that the Split transaction is not yet complete.
  - The device sent a NAK packet, thereby signalling it had no data to send at the time, when trying to execute an IN interrupt transfer.
  - One of several errors has occurred, such as an AHB error, data toggle error, tranasction error, stall condition, or frame overrun error */
#define DWC_HOST_CHANNEL_INTERRUPTS_CHANNEL_HALTED	(1 << 1) // Bit 1
/* An error occurred on the ARM Advanced High-Performance Bus (AHB) */
#define DWC_HOST_CHANNEL_INTERRUPTS_AHB_ERROR	(1 << 2) // Bit 2
/* The device issued a STALL handshake packet (endpoint is halted or control pipe request is not supported) */
#define DWC_HOST_CHANNEL_INTERRUPTS_STALL_RESPONSE_RECEIVED	(1 << 3) // Bit 3
/* The device issued a NAK handshake packet (receiving device cannot accept data or transmitting device cannot send data)
  The channel will halt with this bit set when performing an IN transfer from an interrupt endpoint that has no data to send
  As this requires software intervention to restart the channel, this means that polling of interrupt endpoints (e.g. on hubs and HID devices) must be done in software, even if
  the actual transactions themselves are interrupt-driven */
#define DWC_HOST_CHANNEL_INTERRUPTS_NAK_RESPONSE_RECEIVED	(1 << 4) // Bit 4
/* The device issued an ACK handshake packet (receiving device acknowledged error-free packet) */
#define DWC_HOST_CHANNEL_INTERRUPTS_ACK_RESPONSE_RECEIVED	(1 << 5) // Bit 5
/* The device issued a NYET handshake packet */
#define DWC_HOST_CHANNEL_INTERRUPTS_NYET_RESPONSE_RECEIVED	(1 << 6) // Bit 6
/* From our experience this seems to usually indicate that software programmed the channel incorrectly */
#define DWC_HOST_CHANNEL_INTERRUPTS_TRANSACTION_ERROR	(1 << 7) // Bit 7
/* Unexpected bus activity occurred */
#define DWC_HOST_CHANNEL_INTERRUPTS_BABBLE_ERROR	(1 << 8) // Bit 8
/* TODO */
#define DWC_HOST_CHANNEL_INTERRUPTS_FRAME_OVERRUN	(1 << 9) // Bit 9
/* When issuing a series of DATA transactions to an endpoint, the correct DATA0 or DATA1 packet ID was not specified in the packet_id member of the transfer register */
#define DWC_HOST_CHANNEL_INTERRUPTS_DATA_TOGGLE_ERROR	(1 << 10) // Bit 10
#define DWC_HOST_CHANNEL_INTERRUPTS_BUFFER_NOT_AVAILABLE	(1 << 11) // Bit 11
#define DWC_HOST_CHANNEL_INTERRUPTS_EXCESS_TRANSACTION_ERROR	(1 << 12) // Bit 12
#define DWC_HOST_CHANNEL_INTERRUPTS_FRAME_LIST_ROLLOVER	(1 << 13) // Bit 13
#define DWC_HOST_CHANNEL_INTERRUPTS_RESERVED	(0x3FFFF << 14) // Bits 14-31

/* TDWCHostChannel: 0x000c : Channel Interrupts Mask Register */
/* This has the same format as the Channel Interrupts Register, but software uses this to enable (1) or disable (0) the corresponding interrupt.  Defaults to all 0's after a reset */
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_TRANSFER_COMPLETED	DWC_HOST_CHANNEL_INTERRUPTS_TRANSFER_COMPLETED
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_CHANNEL_HALTED	DWC_HOST_CHANNEL_INTERRUPTS_CHANNEL_HALTED
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_AHB_ERROR	DWC_HOST_CHANNEL_INTERRUPTS_AHB_ERROR
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_STALL_RESPONSE_RECEIVED	DWC_HOST_CHANNEL_INTERRUPTS_STALL_RESPONSE_RECEIVED
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_NAK_RESPONSE_RECEIVED	DWC_HOST_CHANNEL_INTERRUPTS_NAK_RESPONSE_RECEIVED
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_ACK_RESPONSE_RECEIVED	DWC_HOST_CHANNEL_INTERRUPTS_ACK_RESPONSE_RECEIVED
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_NYET_RESPONSE_RECEIVED	DWC_HOST_CHANNEL_INTERRUPTS_NYET_RESPONSE_RECEIVED
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_TRANSACTION_ERROR	DWC_HOST_CHANNEL_INTERRUPTS_TRANSACTION_ERROR
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_BABBLE_ERROR	DWC_HOST_CHANNEL_INTERRUPTS_BABBLE_ERROR
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_FRAME_OVERRUN	DWC_HOST_CHANNEL_INTERRUPTS_FRAME_OVERRUN
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_DATA_TOGGLE_ERROR	DWC_HOST_CHANNEL_INTERRUPTS_DATA_TOGGLE_ERROR
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_BUFFER_NOT_AVAILABLE	DWC_HOST_CHANNEL_INTERRUPTS_BUFFER_NOT_AVAILABLE
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_EXCESS_TRANSACTION_ERROR	DWC_HOST_CHANNEL_INTERRUPTS_EXCESS_TRANSACTION_ERROR
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_FRAME_LIST_ROLLOVER	DWC_HOST_CHANNEL_INTERRUPTS_FRAME_LIST_ROLLOVER
#define DWC_HOST_CHANNEL_INTERRUPT_MASK_RESERVED	DWC_HOST_CHANNEL_INTERRUPTS_RESERVED

/* TDWCHostChannel: 0x0010 : Channel Transfer Register */
/* Used to store additional information about the transfer.  This must be programmed before beginning the transfer */
/* Size of the data to send or receive, in bytes.  Software must program this before beginning the transfer.  This can be greater than the maximum packet length.
  For IN transfers, the hardware decrements this field for each packet received by the number of bytes received.  For split transactions, the decrement happens after the Complete Split
  rather than the Start Split.  Software can subtract this field from the original transfer size in order to determine the number of bytes received at any given point, including
  when the transfer has encountered an error or has completed with either the full size or a short size.
  For OUT transfers, the hardware does not update this field as expected.  It will not be decremented when data is transmitted, at least not in every case; hence, software
  cannot rely on its value to indicate how many bytes of data have been transmitted so far.  Instead, software must inspect the packet_count field and assume that all data was
  transmitted if packet_count is 0, or that the amount of data transmitted is equal to the endpoint's maximum packet size times [the original packet count minus packet_count] if
  packet_count is nonzero */
#define DWC_HOST_CHANNEL_TRANSFER_SIZE	(0x7FFFF << 0) // Bits 0-18
/* Number of packets left to transmit or maximum number of packets left to receive.  Software must program this before beginning the transfer.  The packet count is calculated as
  the size divided by the maximum packet size, rounded up to the nearest whole packet.  As a special case, if the transfer size is 0 bytes, the packet count must be set to 1.
  The hardware will decrement this register when a packet is successfully sent or received.  In the case of split transactions, this happens after the Complete Split rather
  than after the Start Split.  If the final received packet of an IN transfer is short, it is still counted */
#define DWC_HOST_CHANNEL_TRANSFER_PACKET_COUNT	(0x3FF << 19) // Bits 19-28
/* High 2 bits of the Packet ID used in the USB protocol. When performing the SETUP phase of a control transfer, specify 0x3 here to generate the needed SETUP token.
  When performing the DATA phase of a control transfer, initially specify 0x2 here to begin the DATA packets with the needed DATA1 Packet ID.
  When performing the STATUS phase of a control transfer, specify 0x2 here to generate the needed DATA1 Packet ID.
  When starting a bulk, isochronous, or interrupt transfer, specify 0x0 here to generate the needed DATA0 Packet ID.
  In the case of a transfer consisting of multiple DATA packets, the hardware will update this field with the Packet ID to use for the next packet.  This field therefore only
  needs to be re-programmed if the transfer is moved to a different channel or the channel is re-used before the transfer is complete.  When doing so, software must save this
  field so that it can be re-programmed correctly */
#define DWC_HOST_CHANNEL_TRANSFER_PACKET_ID	(0x03 << 29) // Bits 29-30
/* Do PING protocol when 1 (See Section 8.5.1 of Universal Serial Bus Specification 2.0) */
#define DWC_HOST_CHANNEL_TRANSFER_DO_PING	(1 << 31) // Bit  31

/* ============================================================================== */
/* DWCOTG specific types */

/* TDWCRegisters: 0x0500 : Array of host channels. Each host channel can be used to
  execute an independent USB transfer or transaction simultaneously.  A USB
  transfer may consist of multiple transactions, or packets.  To avoid
  having to re-program the channel, it may be useful to use one channel for
  all transactions of a transfer before allowing other transfers to be
  scheduled on it. */
typedef struct _DWC_HOST_CHANNEL DWC_HOST_CHANNEL;
struct _DWC_HOST_CHANNEL
{
	// 0x0000 : Channel Characteristics
	// Contains various fields that must be set to prepare this channel for a transfer to or from a particular endpoint on a particular USB device
	// This register only needs to be programmed one time when doing a transfer, regardless of how many packets it consists of, unless the channel is
	// re-programmed for a different transfer or the transfer is moved to a different channel}
	uint32_t characteristics;
	// 0x0004 : Channel Split Control
	// This register is used to set up Split Transactions for communicating with low or full-speed devices attached to a high-speed hub.  When doing so, set split_enable to 1 and
	// the other fields as documented. Otherwise, software must clear this register before starting the transfer}
	// Like the Channel Characteristics register, this register only needs to be programmed one time if the channel is enabled multiple times to send all the packets of a single transfer
	uint32_t splitcontrol;
	// 0x0008 : Channel Interrupts
	// Bitmask of status conditions that have occurred on this channel
	// These bits can be used with or without "real" interrupts.  To have the CPU get a real interrupt when one of these bits gets set, set the appropriate bit in the interrupt_mask,
	// and also ensure that interrupts from the channel are enabled in the host_channels_interrupt_mask register, channel interrupts overall are enabled in the core_interrupt_mask register,
	// and interrupts from the DWC hardware overall are enabled in the ahb_configuration register and by any system-specific interrupt controller}
	uint32_t interrupts;
	// 0x000c : Channel Interrupts Mask
	// This has the same format as the Channel Interrupts Register, but software uses this to enable (1) or disable (0) the corresponding interrupt.  Defaults to all 0's after a reset
	uint32_t interruptmask;
	// 0x0010 : Channel Transfer
	// Used to store additional information about the transfer.  This must be programmed before beginning the transfer
	uint32_t transfer;
	// 0x0014 : Channel DMA Address
	// Word-aligned address at which the hardware will read or write data using Direct Memory Access.  This must be programmed before beginning the transfer, unless the size of the data
	// to send or receive is 0. The hardware will increment this address by the number of bytes successfully received or sent, which will correspond to the size decrease in transfer.size}
	// Note: DMA must be enabled in the AHB Configuration Register before this register can be used.  Otherwise, the hardware is considered to be in Slave mode and must be controlled a
	// different way, which we do not use in our driver and do not attempt to document}
	// BCM2835-specific note:  Addresses written to this register must be bus addresses, not ARM physical addresses
	uint32_t dmaaddress;
	// 0x0018 : Reserved
	uint32_t reserved0x0018;
	// 0x001C : Reserved
	uint32_t reserved0x001c;
};


/* Layout of the registers of the DesignWare Hi-Speed USB 2.0 On-The-Go
  Controller.  There is no official documentation for these; however, the
  register locations (and to some extent the meanings) can be found in other
  code, such as the Linux driver for this hardware that Synopsys contributed.
 
  We do not explicitly define every bit in the registers because the majority
  are not used by our driver and would complicate this file.  For example, we
  do not attempt to document any features that are specific to suspend,
  hibernation, the OTG protocol, or to the core acting in device mode rather
  than host mode.
 
  The bits and fields we do use in our driver we have tried to completely
  document based on our understanding of what they do.  We cannot guarantee
  that all the information is correct, as we do not have access to any official
  documentation */
typedef struct _DWC_REGISTERS DWC_REGISTERS;
struct _DWC_REGISTERS
{
	// Core registers
	// 0x0000 : OTG Control and Status
	uint32_t otgcontrol;
	// 0x0004 : OTG Interrupt
	uint32_t otginterrupt;
	// 0x0008 : Core AHB Configuration
	// This register configures some of the interactions the DWC has with the rest of the system
	uint32_t ahbconfiguration;
	// 0x000c : Core USB Configuration
	uint32_t coreusbconfiguration;
	// 0x0010 : Core Reset
	// Software can use this register to cause the DWC to reset itself
	uint32_t corereset;
	// 0x0014 : Core Interrupt
	// This register contains the state of pending top-level DWC interrupts.  1 means interrupt pending while 0 means no interrupt pending
	// Note that at least for port_intr and host_channel_intr, software must clear the interrupt somewhere else rather than by writing to this register
	uint32_t coreinterrupts;
	// 0x0018 : Core Interrupt Mask
	// This register has the same format as the Core Interrupt Register and configures whether the corresponding interrupt is enabled (1) or disabled (0).  Initial state after reset is all 0's
	uint32_t coreinterruptmask;
	// 0x001c : Receive Status Queue Read (Read Only)
	uint32_t receivestatus;
	// 0x0020 : Receive Status Queue Read & POP (Read Only)
	uint32_t receivestatuspop;
	// 0x0024 : Receive FIFO Size
	// This register contains the size of the Receive FIFO, in 4-byte words
	// see the note in the documentation for the hwcfg3 register about configuring the dynamic FIFOs}
	uint32_t receivefifosize;
	// 0x0028 : Non Periodic Transmit FIFO Size
	// The low 16 bits of this register contain the offset of the Nonperiodic Transmit FIFO, in 4-byte words, from the start of the memory reserved by the controller for dynamic FIFOs.
	// The high 16 bits of this register contain its size, in 4-byte words}
	// see the note in the documentation for the hwcfg3 register about configuring the dynamic FIFOs}
	uint32_t nonperiodictransmitfifosize;
	// 0x002c : Non Periodic Transmit FIFO/Queue Status (Read Only)
	uint32_t nonperiodictransmitfifostatus;
	// 0x0030 : I2C Access
	uint32_t i2ccontrol;
	// 0x0034 : PHY Vendor Control
	uint32_t phyvendorcontrol;
	// 0x0038 : General Purpose Input/Output
	uint32_t gpio;
	// 0x003c : User ID
	uint32_t userid;
	// 0x0040 : Vendor ID (Read Only)
	uint32_t vendorid;
	// 0x0044 : User HW Config1 (Read Only)
	uint32_t hwcfg1;
	// 0x0048 : User HW Config2 (Read Only)
	uint32_t hwcfg2;
	// 0x004c : User HW Config3 (Read Only)
	// The high 16 bits of this read-only register contain the maximum total size, in words, of the dynamic FIFOs (Rx, Nonperiodic Tx, and Periodic Tx).
	// Software must set up these three dynamic FIFOs in the rx_fifo_size, nonperiodic_tx_fifo_size, and host_periodic_tx_fifo_size registers such that
	// their total size does not exceed this maximum total size and no FIFOs overlap}
	// Note: Software must explicitly configure the dynamic FIFOs even if the controller is operating in DMA mode, since the default values for the
	// FIFO sizes and offsets may be invalid.  For example, in Broadcom's instantiation of this controller for the BCM2835, only 4080 words are
	// available for dynamic FIFOs, but the dynamic FIFO sizes are set to 4096, 32, and 0, which are invalid as they add up to more than 4080.
	// IF YOU DO NOT DO THIS YOU WILL GET SILENT MEMORY CORRUPTION}
	// The low 16 bits of this register contain various flags that are not documented here as we don't use any in our driver
	uint32_t hwcfg3;
	// 0x0050 : User HW Config4 (Read Only)
	uint32_t hwcfg4;
	// 0x0054 :  Core LPM Configuration
	uint32_t corelpmconfiguration;
	// 0x0058 : Global PowerDown
	uint32_t globalpowerdown;
	// 0x005c : Global DFIFO SW Config
	uint32_t globalfifoconfig;
	// 0x0060 : ADP Control (Attach Detection Protocol)
	uint32_t adpcontrol;
	// 0x0064 : Reserved 
	uint32_t reserved0x0064[39];
	// 0x0100 : Host Periodic Transmit FIFO Size
	// The low 16 bits of this register configure the offset of the Periodic Transmit FIFO, in 4-byte words, from the start of the memory reserved by the controller for dynamic FIFOs.
	// The high 16 bits of this register configure its size, in 4-byte words}
	// see the note in the documentation for the hwcfg3 register about configuring the dynamic FIFOs}
	uint32_t hostperiodictransmitfifosize;
	// 0x0104 : Device Periodic Transmit FIFO#n (if dedicated fifos are disabled, otherwise Device Transmit FIFO#n)
	uint32_t reserved0x0104[191];
	// Host registers
	// The registers beginning at this point are considered to be the "Host" registers. These are used for the "Host" half of the OTG (On-The-Go) protocol, which allows this hardware
	// to act as either a USB host or a USB device.  This is the only half we are concerned with in this driver and we do not declare the corresponding Device registers}
	// 0x0400 : Host Configuration
	uint32_t hostconfiguration;
	// 0x0404 : Host Frame Interval
	uint32_t hostframeinterval;
	// 0x0408 : Host Frame Number / Frame Remaining
	uint32_t hostframenumber;
	// 0x040c : Reserved
	uint32_t reserved0x040c;
	// 0x0410 : Host Periodic Transmit FIFO/ Queue Status
	uint32_t hostfifostatus;
	// 0x0414 : Host All Channels Interrupt
	// This register contains a bit for each host channel that indicates whether an interrupt has occurred on that host channel.  You cannot clear the interrupts by writing
	// use the channel-specific interrupt registers instead}
	uint32_t hostchannelsinterrupt;
	// 0x0418 : Host All Channels Interrupt Mask
	// Same format as the Host All Channels Interrupt Register, but a 1 in this register indicates that the corresponding host channel interrupt is enabled.  Software can
	// change this register.  Defaults to all 0's after a reset}
	uint32_t hostchannelsinterruptmask;
	// 0x041c : Host Frame List Base Address Register
	uint32_t hostframelist;
	// 0x0420
	uint32_t reserved0x0420[8];
	// 0x0440 : Host Port Control and Status
	// This register provides the information needed to respond to status queries about the "host port", which is the port that is logically attached to the root hub
	// When changing this register, software must read its value, then clear the enabled, connected_changed, enabled_changed, and overcurrent_changed members to avoid
	// changing them, as those particular bits are cleared by writing 1}
	uint32_t hostportcontrolstatus;
	// 0x0444
	uint32_t reserved0x0444[47];
	// Host channel registers
	// 0x0500 : Array of Host Channels
	// Each host channel can be used to execute an independent USB transfer or transaction simultaneously.  A USB transfer may consist of multiple transactions, or packets.
	// To avoid having to re-program the channel, it may be useful to use one channel for all transactions of a transfer before allowing other transfers to be scheduled on it}
	DWC_HOST_CHANNEL hostchannels[DWC_MAX_CHANNELS];
	// 0x0700
	uint32_t reserved0x0700[((0x800 - 0x500) - (DWC_MAX_CHANNELS * sizeof(DWC_HOST_CHANNEL))) / sizeof(uint32_t)];
	// Device registers
	// 0x0800
	uint32_t reserved0x0800[(0xE00 - 0x800) / sizeof(uint32_t)];
	// 0x0e00 : Power and Clock Gating Control
	uint32_t powerclockcontrol;
};


/* DWC Root Hub Configuration */
typedef struct _DWC_ROOTHUB_CONFIGURATION DWC_ROOTHUB_CONFIGURATION;
struct _DWC_ROOTHUB_CONFIGURATION
{
	USB_CONFIGURATION_DESCRIPTOR configurationdescriptor;
	USB_INTERFACE_DESCRIPTOR interfacedescriptor;
	USB_ENDPOINT_DESCRIPTOR endpointdescriptor;
} PACKED;


/* DWC USB Host */
typedef struct _DWC_USB_HOST DWC_USB_HOST;
struct _DWC_USB_HOST
{
	// USB Properties
	USB_HOST host;
	// DWCOTG Properties
	SPIN_HANDLE lock; // Host lock (Differs from lock in Host portion) (Spin lock due to use by interrupt handler)
	uint32_t irq; // The IRQ assigned to this host
	uint32_t powerid; // The Power ID required to power on this host
	DWC_REGISTERS *registers; // Memory mapped registers of the Synopsys DesignWare Hi-Speed USB 2.0 OTG Controller
	uint32_t channelcount; // The number of channels available on this host
	THREAD_HANDLE schedulerthread; // Thread ID of USB request scheduler thread
	THREAD_HANDLE completionthread; // Thread ID of USB request completion thread
	MAILSLOT_HANDLE schedulermailslot; // USB requests that have been submitted to the Host but not yet started on a channel
	// Channel Properties
	void *dmabuffers[DWC_MAX_CHANNELS]; // DMA buffers allocated for each hardware channel (4 byte aligned / 1 per channel)
	USB_REQUEST *channelrequests[DWC_MAX_CHANNELS]; // Current USB request pending on each hardware channel (or nil of no request is pending)
	uint32_t channelfreemask; // Bitmap of channel free (1) or used (0) status
	MUTEX_HANDLE channelfreelock; // Lock for access to ChannelFreeMask
	SEMAPHORE_HANDLE channelfreewait; // Number of free channels in ChannelFreeMask
	uint32_t startofframemask; // Bitmap of channels waiting for Start of Frame
	SPIN_HANDLE startofframelock; // Lock for access to StartOfFrameMask (Spin lock due to use by interrupt handler)
	uint32_t lastframenumber; // Frame Number at the last Start Of Frame interrupt
	// Root Hub Properties
	USB_HUB_STATUS *hubstatus; // Hub status for the root hub
	USB_PORT_STATUS *portstatus; // Host port status for the root hub (Obtained from port interrupt due to status change)
	USB_DEVICE_STATUS *devicestatus; // Device status for the root hub
	USB_HUB_DESCRIPTOR *hubdescriptor; // Hub descriptor for the root hub
	USB_DEVICE_DESCRIPTOR *devicedescriptor; // Device descriptor for the root hub
	DWC_ROOTHUB_CONFIGURATION *hubconfiguration; // Configuration, Interface and Endpoint descriptors for the root hub
	USB_STRING_DESCRIPTOR *hubstringtable[3]; // String table for Language, Product and Manufacturer strings for the root hub
	USB_STRING_DESCRIPTOR *hubproductstring; // Product identifier string for the root hub
	USB_STRING_DESCRIPTOR *hublanguagestring; // Language identifier string for the root hub
	USB_STRING_DESCRIPTOR *hubmanufacturerstring; // Manufacturer identifier string for the root hub
	USB_REQUEST *hubstatuschange; // Status change request to the root hub interrupt endpoint (nil if no request is pending)
	// Statistics Properties
	uint32_t interruptcount; // Number of interrupt requests received by the host controller
	uint32_t portinterruptcount; // Number of port interrupts received by the host controller
	uint32_t channelinterruptcount; // Number of channel interrupts received by the host controller
	uint32_t startofframeinterruptcount; // Number of start of frame interrupts received by the host controller
	uint32_t disconnectinterruptcount; // Number of disconnect interrupts received by the host controller
	uint32_t resubmitcount; // Number of requests resubmitted for later retry
	uint32_t startofframecount; // Number of requests queued to wait for start of frame
	uint32_t dmabufferreadcount; // Number of IN requests that required a DMA buffer copy
	uint32_t dmabufferwritecount; // Number of OUT requests that required a DMA buffer copy
	uint32_t nakresponsecount; // Number of NAK responses received by the host controller
	uint32_t nyetresponsecount; // Number of NYET responses received by the host controller
	uint32_t stallresponsecount; // Number of Stall responses received by the host controller
	uint32_t requestcancelcount; // Number of requests Cancelled by the host controller
	uint32_t ahberrorcount; // Number of AHB errors received by the host controller
	uint32_t transactionerrorcount; // Number of transaction errors received by the host controller
	uint32_t babbleerrorcount; // Number of babble errors received by the host controller
	uint32_t excesstransactioncount; // Number of excess transaction errors received by the host controller
	uint32_t framelistrollovercount; // Number of frame list rollover errors received by the host controller
	uint32_t datatoggleerrorcount; // Number of data toggle errors received by the host controller
	uint32_t frameoverruncount; // Number of frame overrun errors received by the host controller
	uint32_t shortattemptcount; // Number of short attempts where transfer size was less than the request size
	uint32_t startsplitcount; // Number of start split transactions
	uint32_t completesplitcount; // Number of complete split transactions
	uint32_t completesplitrestartcount; // Number of times a complete split transaction has been restarted at start split due to errors
	uint32_t transferrestartcount; // Number of times a transfer is restarted to continue or retry the transfer
	uint32_t transactionrestartcount; // Number of times a transaction is restarted to continue or complete the transfer
	uint32_t nochannelcompletedcount; // Number of times the channel completed interrupt bit was not set when a request completed
	uint32_t nopacketstransferredcount; // Number of times no packets were transferred but no error occured when a channel halted
};

/* ============================================================================== */
/* DWCOTG Functions */
USB_HOST * STDCALL dwc_host_create(size_t address, uint32_t irq, uint32_t powerid);
uint32_t STDCALL dwc_host_destroy(USB_HOST *host);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_DWCOTG_H
