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
#ifndef _ULTIBO_GENET_H
#define _ULTIBO_GENET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/threads.h"
#include "ultibo/network.h"

/** GENET specific constants (Broadcom Gigabit Ethernet controller) */
#define GENET_NETWORK_DESCRIPTION	"Broadcom GENET (Gigabit Ethernet) controller" ///< Description of GENET device

#define GENET_MAX_TX_ENTRIES	SIZE_256 ///< Number of Transmit buffers allocated
#define GENET_MAX_RX_ENTRIES	SIZE_512 ///< Number of Receive buffers allocated

#define GENET_MAX_PACKET_SIZE	2048

/** Version information */
#define GENET_V1	1
#define GENET_V2	2
#define GENET_V3	3
#define GENET_V4	4
#define GENET_V5	5

/** Total number of Buffer Descriptors, same for RX/TX */
#define GENET_TOTAL_DESC	256

/** Max number of descriptor queues (plus 1 for default) */
#define GENET_DESC_INDEX	16

/** Body(1500) + Header(14) + VLANTAG(4) + BRCMTAG(6) + FCS(4) = 1528 */
/** Plus PAD(6) = 1536 which is a multiple of 256 bytes */
#define GENET_ETH_BRCM_TAG_LEN	6
#define GENET_ETH_PAD	8
#define GENET_ETH_MAX_MTU_SIZE	(ETHERNET_MTU + ETHERNET_HEADER_SIZE + ETHERNET_VLAN_SIZE + GENET_ETH_BRCM_TAG_LEN + ETHERNET_CRC_SIZE + GENET_ETH_PAD)

/** Default highest priority queue for multi queue support */
#define GENET_Q0_PRIORITY	0

/** Misc configuration */
#define CLEAR_ALL_HFB	0xFF

/** DMA configuration */
#define DMA_MAX_BURST_LENGTH	0x08
#define DMA_FC_THRESH_HI	(GENET_TOTAL_DESC >> 4)
#define DMA_FC_THRESH_LO	5

/** RX status bits */
#define STATUS_RX_EXT_MASK	0x1FFFFF
#define STATUS_RX_CSUM_MASK	0xFFFF
#define STATUS_RX_CSUM_OK	0x10000
#define STATUS_RX_CSUM_FR	0x20000
#define STATUS_RX_PROTO_TCP	0
#define STATUS_RX_PROTO_UDP	1
#define STATUS_RX_PROTO_ICMP	2
#define STATUS_RX_PROTO_OTHER	3
#define STATUS_RX_PROTO_MASK	3
#define STATUS_RX_PROTO_SHIFT	18
#define STATUS_FILTER_INDEX_MASK	0xFFFF

/** TX status bits */
#define STATUS_TX_CSUM_START_MASK	0x7FFF
#define STATUS_TX_CSUM_START_SHIFT	16
#define STATUS_TX_CSUM_PROTO_UDP	0x8000
#define STATUS_TX_CSUM_OFFSET_MASK	0x7FFF
#define STATUS_TX_CSUM_LV	0x80000000

/** DMA Descriptor */
#define DMA_DESC_LENGTH_STATUS	0x00 ///< in bytes of data in buffer
#define DMA_DESC_ADDRESS_LO	0x04 ///< lower bits of PA
#define DMA_DESC_ADDRESS_HI	0x08 ///< upper 32 bits of PA, GENETv4+

/** UniMAC registers */
#define UMAC_HD_BKP_CTRL	0x004
#define HD_FC_EN	(1 << 0)
#define HD_FC_BKOFF_OK	(1 << 1)
#define IPG_CONFIG_RX_SHIFT	2
#define IPG_CONFIG_RX_MASK	0x1F

#define UMAC_CMD	0x008
#define CMD_TX_EN	(1 << 0)
#define CMD_RX_EN	(1 << 1)
#define UMAC_SPEED_10	0
#define UMAC_SPEED_100	1
#define UMAC_SPEED_1000	2
#define UMAC_SPEED_2500	3
#define CMD_SPEED_SHIFT	2
#define CMD_SPEED_MASK	3
#define CMD_PROMISC	(1 << 4)
#define CMD_PAD_EN	(1 << 5)
#define CMD_CRC_FWD	(1 << 6)
#define CMD_PAUSE_FWD	(1 << 7)
#define CMD_RX_PAUSE_IGNORE	(1 << 8)
#define CMD_TX_ADDR_INS	(1 << 9)
#define CMD_HD_EN	(1 << 10)
#define CMD_SW_RESET	(1 << 13)
#define CMD_LCL_LOOP_EN	(1 << 15)
#define CMD_AUTO_CONFIG	(1 << 22)
#define CMD_CNTL_FRM_EN	(1 << 23)
#define CMD_NO_LEN_CHK	(1 << 24)
#define CMD_RMT_LOOP_EN	(1 << 25)
#define CMD_PRBL_EN	(1 << 27)
#define CMD_TX_PAUSE_IGNORE	(1 << 28)
#define CMD_TX_RX_EN	(1 << 29)
#define CMD_RUNT_FILTER_DIS	(1 << 30)

#define UMAC_MAC0	0x00C
#define UMAC_MAC1	0x010
#define UMAC_MAX_FRAME_LEN	0x014

#define UMAC_MODE	0x44
#define MODE_LINK_STATUS	(1 << 5)

#define UMAC_EEE_CTRL	0x064
#define EN_LPI_RX_PAUSE	(1 << 0)
#define EN_LPI_TX_PFC	(1 << 1)
#define EN_LPI_TX_PAUSE	(1 << 2)
#define EEE_EN	(1 << 3)
#define RX_FIFO_CHECK	(1 << 4)
#define EEE_TX_CLK_DIS	(1 << 5)
#define DIS_EEE_10M	(1 << 6)
#define LP_IDLE_PREDICTION_MODE	(1 << 7)

#define UMAC_EEE_LPI_TIMER	0x068
#define UMAC_EEE_WAKE_TIMER	0x06C
#define UMAC_EEE_REF_COUNT	0x070
#define EEE_REFERENCE_COUNT_MASK	0xffff

#define UMAC_TX_FLUSH	0x334

#define UMAC_MIB_START	0x400

#define UMAC_MDIO_CMD	0x614
#define MDIO_START_BUSY	(1 << 29)
#define MDIO_READ_FAIL	(1 << 28)
#define MDIO_RD	(2 << 26)
#define MDIO_WR	(1 << 26)
#define MDIO_PMD_SHIFT	21
#define MDIO_PMD_MASK	0x1F
#define MDIO_REG_SHIFT	16
#define MDIO_REG_MASK	0x1F

#define UMAC_RBUF_OVFL_CNT_V1	0x61C
#define RBUF_OVFL_CNT_V2	0x80
#define RBUF_OVFL_CNT_V3PLUS	0x94

#define UMAC_MPD_CTRL	0x620
#define MPD_EN	(1 << 0)
#define MPD_PW_EN	(1 << 27)
#define MPD_MSEQ_LEN_SHIFT	16
#define MPD_MSEQ_LEN_MASK	0xFF

#define UMAC_MPD_PW_MS	0x624
#define UMAC_MPD_PW_LS	0x628
#define UMAC_RBUF_ERR_CNT_V1	0x634
#define RBUF_ERR_CNT_V2	0x84
#define RBUF_ERR_CNT_V3PLUS	0x98
#define UMAC_MDF_ERR_CNT	0x638
#define UMAC_MDF_CTRL	0x650
#define UMAC_MDF_ADDR	0x654
#define UMAC_MIB_CTRL	0x580
#define MIB_RESET_RX	(1 << 0)
#define MIB_RESET_RUNT	(1 << 1)
#define MIB_RESET_TX	(1 << 2)

/** Receive buffer registers */
#define RBUF_CTRL	0x00
#define RBUF_64B_EN	(1 << 0)
#define RBUF_ALIGN_2B	(1 << 1)
#define RBUF_BAD_DIS	(1 << 2)

#define RBUF_STATUS	0x0C
#define RBUF_STATUS_WOL	(1 << 0)
#define RBUF_STATUS_MPD_INTR_ACTIVE	(1 << 1)
#define RBUF_STATUS_ACPI_INTR_ACTIVE	(1 << 2)

#define RBUF_CHK_CTRL	0x14
#define RBUF_RXCHK_EN	(1 << 0)
#define RBUF_SKIP_FCS	(1 << 4)

#define RBUF_ENERGY_CTRL	0x9c
#define RBUF_EEE_EN	(1 << 0)
#define RBUF_PM_EN	(1 << 1)

#define RBUF_TBUF_SIZE_CTRL	0xb4

/** Hardware Filter Block (HFB) */
#define RBUF_HFB_CTRL_V1	0x38
#define RBUF_HFB_FILTER_EN_SHIFT	16
#define RBUF_HFB_FILTER_EN_MASK	0xffff0000
#define RBUF_HFB_EN	(1 << 0)
#define RBUF_HFB_256B	(1 << 1)
#define RBUF_ACPI_EN	(1 << 2)

#define RBUF_HFB_LEN_V1	0x3C
#define RBUF_FLTR_LEN_MASK	0xFF
#define RBUF_FLTR_LEN_SHIFT	8

/** Transmit buffer registers */
#define TBUF_CTRL	0x00
#define TBUF_BP_MC	0x0C
#define TBUF_ENERGY_CTRL	0x14
#define TBUF_EEE_EN	(1 << 0)
#define TBUF_PM_EN	(1 << 1)

#define TBUF_CTRL_V1	0x80
#define TBUF_BP_MC_V1	0xA0

/** Hardware Filter Block (HFB) registers */
#define HFB_CTRL	0x00
#define HFB_FLT_ENABLE_V3PLUS	0x04
#define HFB_FLT_LEN_V2	0x04
#define HFB_FLT_LEN_V3PLUS	0x1C

/** UniMAC intrl2 registers */
#define INTRL2_CPU_STAT	0x00
#define INTRL2_CPU_SET	0x04
#define INTRL2_CPU_CLEAR	0x08
#define INTRL2_CPU_MASK_STATUS	0x0C
#define INTRL2_CPU_MASK_SET	0x10
#define INTRL2_CPU_MASK_CLEAR	0x14

/** INTRL2 IRQ0 definitions */
#define UMAC_IRQ0_SCB	(1 << 0)
#define UMAC_IRQ0_EPHY	(1 << 1)
#define UMAC_IRQ0_PHY_DET_R	(1 << 2)
#define UMAC_IRQ0_PHY_DET_F	(1 << 3)
#define UMAC_IRQ0_LINK_UP	(1 << 4)
#define UMAC_IRQ0_LINK_DOWN	(1 << 5)
#define UMAC_IRQ0_LINK_EVENT	(UMAC_IRQ0_LINK_UP | UMAC_IRQ0_LINK_DOWN)
#define UMAC_IRQ0_UMAC	(1 << 6)
#define UMAC_IRQ0_UMAC_TSV	(1 << 7)
#define UMAC_IRQ0_TBUF_UNDERRUN	(1 << 8)
#define UMAC_IRQ0_RBUF_OVERFLOW	(1 << 9)
#define UMAC_IRQ0_HFB_SM	(1 << 10)
#define UMAC_IRQ0_HFB_MM	(1 << 11)
#define UMAC_IRQ0_MPD_R	(1 << 12)
#define UMAC_IRQ0_RXDMA_MBDONE	(1 << 13)
#define UMAC_IRQ0_RXDMA_PDONE	(1 << 14)
#define UMAC_IRQ0_RXDMA_BDONE	(1 << 15)
#define UMAC_IRQ0_RXDMA_DONE	UMAC_IRQ0_RXDMA_MBDONE
#define UMAC_IRQ0_TXDMA_MBDONE	(1 << 16)
#define UMAC_IRQ0_TXDMA_PDONE	(1 << 17)
#define UMAC_IRQ0_TXDMA_BDONE	(1 << 18)
#define UMAC_IRQ0_TXDMA_DONE	UMAC_IRQ0_TXDMA_MBDONE

/** Only valid for GENETv3+ */
#define UMAC_IRQ0_MDIO_DONE	(1 << 23)
#define UMAC_IRQ0_MDIO_ERROR	(1 << 24)

/** INTRL2 IRQ1 definitions */
#define UMAC_IRQ1_TX_INTR_MASK	0xFFFF
#define UMAC_IRQ1_RX_INTR_MASK	0xFFFF
#define UMAC_IRQ1_RX_INTR_SHIFT	16

/** Register block offsets */
#define GENET_SYS_OFF	0x0000
#define GENET_GR_BRIDGE_OFF	0x0040
#define GENET_EXT_OFF	0x0080
#define GENET_INTRL2_0_OFF	0x0200
#define GENET_INTRL2_1_OFF	0x0240
#define GENET_RBUF_OFF	0x0300
#define GENET_UMAC_OFF	0x0800

/** SYS block offsets and register definitions */
#define SYS_REV_CTRL	0x00
#define SYS_PORT_CTRL	0x04
#define PORT_MODE_INT_EPHY	0
#define PORT_MODE_INT_GPHY	1
#define PORT_MODE_EXT_EPHY	2
#define PORT_MODE_EXT_GPHY	3
#define PORT_MODE_EXT_RVMII_25	(4 | (1 << 4))
#define PORT_MODE_EXT_RVMII_50	4
#define LED_ACT_SOURCE_MAC	(1 << 9)

#define SYS_RBUF_FLUSH_CTRL	0x08
#define SYS_TBUF_FLUSH_CTRL	0x0C
#define RBUF_FLUSH_CTRL_V1	0x04

/** Ext block register offsets and definitions */
#define EXT_EXT_PWR_MGMT	0x00
#define EXT_PWR_DOWN_BIAS	(1 << 0)
#define EXT_PWR_DOWN_DLL	(1 << 1)
#define EXT_PWR_DOWN_PHY	(1 << 2)
#define EXT_PWR_DN_EN_LD	(1 << 3)
#define EXT_ENERGY_DET	(1 << 4)
#define EXT_IDDQ_FROM_PHY	(1 << 5)
#define EXT_IDDQ_GLBL_PWR	(1 << 7)
#define EXT_PHY_RESET	(1 << 8)
#define EXT_ENERGY_DET_MASK	(1 << 12)
#define EXT_PWR_DOWN_PHY_TX	(1 << 16)
#define EXT_PWR_DOWN_PHY_RX	(1 << 17)
#define EXT_PWR_DOWN_PHY_SD	(1 << 18)
#define EXT_PWR_DOWN_PHY_RD	(1 << 19)
#define EXT_PWR_DOWN_PHY_EN	(1 << 20)

#define EXT_RGMII_OOB_CTRL	0x0C
#define RGMII_MODE_EN_V123	(1 << 0)
#define RGMII_LINK	(1 << 4)
#define OOB_DISABLE	(1 << 5)
#define RGMII_MODE_EN	(1 << 6)
#define ID_MODE_DIS	(1 << 16)

#define EXT_GPHY_CTRL	0x1C
#define EXT_CFG_IDDQ_BIAS	(1 << 0)
#define EXT_CFG_PWR_DOWN	(1 << 1)
#define EXT_CK25_DIS	(1 << 4)
#define EXT_GPHY_RESET	(1 << 5)

/** DMA rings size */
#define DMA_RING_SIZE	0x40
#define DMA_RINGS_SIZE	(DMA_RING_SIZE * (GENET_DESC_INDEX + 1))

/** DMA registers common definitions */
#define DMA_RW_POINTER_MASK	0x1FF
#define DMA_P_INDEX_DISCARD_CNT_MASK	0xFFFF
#define DMA_P_INDEX_DISCARD_CNT_SHIFT	16
#define DMA_BUFFER_DONE_CNT_MASK	0xFFFF
#define DMA_BUFFER_DONE_CNT_SHIFT	16
#define DMA_P_INDEX_MASK	0xFFFF
#define DMA_C_INDEX_MASK	0xFFFF

/** DMA ring size register */
#define DMA_RING_SIZE_MASK	0xFFFF
#define DMA_RING_SIZE_SHIFT	16
#define DMA_RING_BUFFER_SIZE_MASK	0xFFFF

/** DMA interrupt threshold register */
#define DMA_INTR_THRESHOLD_MASK	0x01FF

/** DMA XON/XOFF register */
#define DMA_XON_THREHOLD_MASK	0xFFFF
#define DMA_XOFF_THRESHOLD_MASK	0xFFFF
#define DMA_XOFF_THRESHOLD_SHIFT	16

/** DMA flow period register */
#define DMA_FLOW_PERIOD_MASK	0xFFFF
#define DMA_MAX_PKT_SIZE_MASK	0xFFFF
#define DMA_MAX_PKT_SIZE_SHIFT	16

/** DMA control register */
#define DMA_EN	(1 << 0)
#define DMA_RING_BUF_EN_SHIFT	0x01
#define DMA_RING_BUF_EN_MASK	0xFFFF
#define DMA_TSB_SWAP_EN	(1 << 20)

/** DMA status register */
#define DMA_DISABLED	(1 << 0)
#define DMA_DESC_RAM_INIT_BUSY	(1 << 1)

/** DMA SCB burst size register */
#define DMA_SCB_BURST_SIZE_MASK	0x1F

/** DMA activity vector register */
#define DMA_ACTIVITY_VECTOR_MASK	0x1FFFF

/** DMA backpressure mask register */
#define DMA_BACKPRESSURE_MASK	0x1FFFF
#define DMA_PFC_ENABLE	(1 << 31)

/** DMA backpressure status register */
#define DMA_BACKPRESSURE_STATUS_MASK	0x1FFFF

/** DMA override register */
#define DMA_LITTLE_ENDIAN_MODE	(1 << 0)
#define DMA_REGISTER_MODE	(1 << 1)

/** DMA timeout register */
#define DMA_TIMEOUT_MASK	0xFFFF
#define DMA_TIMEOUT_VAL	5000 ///< micro seconds

/** TDMA rate limiting control register */
#define DMA_RATE_LIMIT_EN_MASK	0xFFFF

/** TDMA arbitration control register */
#define DMA_ARBITER_MODE_MASK	0x03
#define DMA_RING_BUF_PRIORITY_MASK	0x1F
#define DMA_RING_BUF_PRIORITY_SHIFT	5
#define DMA_RATE_ADJ_MASK	0xFF

/** TX/RX DMA Descriptor common bits */
#define DMA_BUFLENGTH_MASK	0x0fff
#define DMA_BUFLENGTH_SHIFT	16
#define DMA_OWN	0x8000
#define DMA_EOP	0x4000
#define DMA_SOP	0x2000
#define DMA_WRAP	0x1000

/** TX specific DMA descriptor bits */
#define DMA_TX_UNDERRUN	0x0200
#define DMA_TX_APPEND_CRC	0x0040
#define DMA_TX_OW_CRC	0x0020
#define DMA_TX_DO_CSUM	0x0010
#define DMA_TX_QTAG_SHIFT	7

/** RX Specific DMA descriptor bits */
#define DMA_RX_CHK_V3PLUS	0x8000
#define DMA_RX_CHK_V12	0x1000
#define DMA_RX_BRDCAST	0x0040
#define DMA_RX_MULT	0x0020
#define DMA_RX_LG	0x0010
#define DMA_RX_NO	0x0008
#define DMA_RX_RXER	0x0004
#define DMA_RX_CRC_ERROR	0x0002
#define DMA_RX_OV	0x0001
#define DMA_RX_FI_MASK	0x001F
#define DMA_RX_FI_SHIFT	0x0007
#define DMA_DESC_ALLOC_MASK	0x00FF

#define DMA_ARBITER_RR	0x00
#define DMA_ARBITER_WRR	0x01
#define DMA_ARBITER_SP	0x02

/** Power management mode */
#define GENET_POWER_CABLE_SENSE	0
#define GENET_POWER_PASSIVE	1
#define GENET_POWER_WOL_MAGIC	2

/** Hardware flags */
#define GENET_HAS_40BITS	(1 << 0)
#define GENET_HAS_EXT	(1 << 1)
#define GENET_HAS_MDIO_INTR	(1 << 2)
#define GENET_HAS_MOCA_LINK_DET	(1 << 3)

/** RX/TX DMA registers */
#define DMA_RING_CFG	0
#define DMA_CTRL	1
#define DMA_STATUS	2
#define DMA_SCB_BURST_SIZE	3
#define DMA_ARB_CTRL	4
#define DMA_PRIORITY_0	5
#define DMA_PRIORITY_1	6
#define DMA_PRIORITY_2	7
#define DMA_INDEX2RING_0	8
#define DMA_INDEX2RING_1	9
#define DMA_INDEX2RING_2	10
#define DMA_INDEX2RING_3	11
#define DMA_INDEX2RING_4	12
#define DMA_INDEX2RING_5	13
#define DMA_INDEX2RING_6	14
#define DMA_INDEX2RING_7	15
#define DMA_RING0_TIMEOUT	16
#define DMA_RING1_TIMEOUT	17
#define DMA_RING2_TIMEOUT	18
#define DMA_RING3_TIMEOUT	19
#define DMA_RING4_TIMEOUT	20
#define DMA_RING5_TIMEOUT	21
#define DMA_RING6_TIMEOUT	22
#define DMA_RING7_TIMEOUT	23
#define DMA_RING8_TIMEOUT	24
#define DMA_RING9_TIMEOUT	25
#define DMA_RING10_TIMEOUT	26
#define DMA_RING11_TIMEOUT	27
#define DMA_RING12_TIMEOUT	28
#define DMA_RING13_TIMEOUT	29
#define DMA_RING14_TIMEOUT	30
#define DMA_RING15_TIMEOUT	31
#define DMA_RING16_TIMEOUT	32

/** RDMA/TDMA ring registers */
/** Merge the common fields and just prefix with T/D the registers having different meaning depending on the direction */
#define TDMA_READ_PTR	0
#define RDMA_WRITE_PTR	TDMA_READ_PTR
#define TDMA_READ_PTR_HI	1
#define RDMA_WRITE_PTR_HI	TDMA_READ_PTR_HI
#define TDMA_CONS_INDEX	2
#define RDMA_PROD_INDEX	TDMA_CONS_INDEX
#define TDMA_PROD_INDEX	3
#define RDMA_CONS_INDEX	TDMA_PROD_INDEX
#define DMA_RING_BUF_SIZE	4
#define DMA_START_ADDR	5
#define DMA_START_ADDR_HI	6
#define DMA_END_ADDR	7
#define DMA_END_ADDR_HI	8
#define DMA_MBUF_DONE_THRESH	9
#define TDMA_FLOW_PERIOD	10
#define RDMA_XON_XOFF_THRESH	TDMA_FLOW_PERIOD
#define TDMA_WRITE_PTR	11
#define RDMA_READ_PTR	TDMA_WRITE_PTR
#define TDMA_WRITE_PTR_HI	12
#define RDMA_READ_PTR_HI	TDMA_WRITE_PTR_HI

/** UniMAC specific constants (Broadcom UniMAC MDIO bus controller) */
#define MDIO_CMD	0x00
/** See UMAC_MDIO_CMD */
/** MDIO_START_BUSY =(1 shl 29);
   MDIO_READ_FAIL  =(1 shl 28);
   MDIO_RD  = (2 shl 26);
   MDIO_WR  = (1 shl 26);
   MDIO_PMD_SHIFT = 21;
   MDIO_PMD_MASK = 0x1F;
   MDIO_REG_SHIFT = 16;
   MDIO_REG_MASK = 0x1F; */

#define MDIO_CFG	0x04
#define MDIO_C22	(1 << 0)
#define MDIO_C45	0
#define MDIO_CLK_DIV_SHIFT	4
#define MDIO_CLK_DIV_MASK	0x3F
#define MDIO_SUPP_PREAMBLE	(1 << 12)

/** Broadcom PHY ID */
#define PHY_ID_BCM50610	0x0143bd60
#define PHY_ID_BCM50610M	0x0143bd70
#define PHY_ID_BCM5241	0x0143bc30
#define PHY_ID_BCMAC131	0x0143bc70
#define PHY_ID_BCM5481	0x0143bca0
#define PHY_ID_BCM5395	0x0143bcf0
#define PHY_ID_BCM54810	0x03625d00
#define PHY_ID_BCM5482	0x0143bcb0
#define PHY_ID_BCM5411	0x00206070
#define PHY_ID_BCM5421	0x002060e0
#define PHY_ID_BCM54210E	0x600d84a0
#define PHY_ID_BCM5464	0x002060b0
#define PHY_ID_BCM5461	0x002060c0
#define PHY_ID_BCM54612E	0x03625e60
#define PHY_ID_BCM54616S	0x03625d10
#define PHY_ID_BCM57780	0x03625d90
#define PHY_ID_BCM89610	0x03625cd0

#define PHY_ID_BCM7250	0xae025280
#define PHY_ID_BCM7255	0xae025120
#define PHY_ID_BCM7260	0xae025190
#define PHY_ID_BCM7268	0xae025090
#define PHY_ID_BCM7271	0xae0253b0
#define PHY_ID_BCM7278	0xae0251a0
#define PHY_ID_BCM7364	0xae025260
#define PHY_ID_BCM7366	0x600d8490
#define PHY_ID_BCM7346	0x600d8650
#define PHY_ID_BCM7362	0x600d84b0
#define PHY_ID_BCM7425	0x600d86b0
#define PHY_ID_BCM7429	0x600d8730
#define PHY_ID_BCM7435	0x600d8750
#define PHY_ID_BCM74371	0xae0252e0
#define PHY_ID_BCM7439	0x600d8480
#define PHY_ID_BCM7439_2	0xae025080
#define PHY_ID_BCM7445	0x600d8510

#define PHY_ID_BCM_CYGNUS	0xae025200
#define PHY_ID_BCM_OMEGA	0xae025100

#define PHY_ID_MASK	0xfffffff0

/** Broadcom PHY Flags */
#define PHY_BCM_FLAGS_MODE_COPPER	0x00000001
#define PHY_BCM_FLAGS_MODE_1000BX	0x00000002
#define PHY_BCM_FLAGS_INTF_SGMII	0x00000010
#define PHY_BCM_FLAGS_INTF_XAUI	0x00000020
#define PHY_BRCM_WIRESPEED_ENABLE	0x00000100
#define PHY_BRCM_AUTO_PWRDWN_ENABLE	0x00000200
#define PHY_BRCM_RX_REFCLK_UNUSED	0x00000400
#define PHY_BRCM_STD_IBND_DISABLE	0x00000800
#define PHY_BRCM_EXT_IBND_RX_ENABLE	0x00001000
#define PHY_BRCM_EXT_IBND_TX_ENABLE	0x00002000
#define PHY_BRCM_CLEAR_RGMII_MODE	0x00004000
#define PHY_BRCM_DIS_TXCRXC_NOENRGY	0x00008000
#define PHY_BRCM_EN_MASTER_MODE	0x00010000

/** Broadcom BCM54XX register definitions, common to most Broadcom PHYs */
#define MII_BCM54XX_ECR	0x10 ///< BCM54xx extended control register
#define MII_BCM54XX_ECR_IM	0x1000 ///< Interrupt mask
#define MII_BCM54XX_ECR_IF	0x0800 ///< Interrupt force

#define MII_BCM54XX_ESR	0x11 ///< BCM54xx extended status register
#define MII_BCM54XX_ESR_IS	0x1000 ///< Interrupt status

#define MII_BCM54XX_EXP_DATA	0x15 ///< Expansion register data
#define MII_BCM54XX_EXP_SEL	0x17 ///< Expansion register select
#define MII_BCM54XX_EXP_SEL_SSD	0x0e00 ///< Secondary SerDes select
#define MII_BCM54XX_EXP_SEL_ER	0x0f00 ///< Expansion register select
#define MII_BCM54XX_EXP_SEL_ETC	0x0d00 ///< Expansion register spare + 2k mem

#define MII_BCM54XX_AUX_CTL	0x18 ///< Auxiliary control register
#define MII_BCM54XX_ISR	0x1a ///< BCM54xx interrupt status register
#define MII_BCM54XX_IMR	0x1b ///< BCM54xx interrupt mask register
#define MII_BCM54XX_INT_CRCERR	0x0001 ///< CRC error
#define MII_BCM54XX_INT_LINK	0x0002 ///< Link status changed
#define MII_BCM54XX_INT_SPEED	0x0004 ///< Link speed change
#define MII_BCM54XX_INT_DUPLEX	0x0008 ///< Duplex mode changed
#define MII_BCM54XX_INT_LRS	0x0010 ///< Local receiver status changed
#define MII_BCM54XX_INT_RRS	0x0020 ///< Remote receiver status changed
#define MII_BCM54XX_INT_SSERR	0x0040 ///< Scrambler synchronization error
#define MII_BCM54XX_INT_UHCD	0x0080 ///< Unsupported HCD negotiated
#define MII_BCM54XX_INT_NHCD	0x0100 ///< No HCD
#define MII_BCM54XX_INT_NHCDL	0x0200 ///< No HCD link
#define MII_BCM54XX_INT_ANPR	0x0400 ///< Auto-negotiation page received
#define MII_BCM54XX_INT_LC	0x0800 ///< All counters below 128
#define MII_BCM54XX_INT_HC	0x1000 ///< Counter above 32768
#define MII_BCM54XX_INT_MDIX	0x2000 ///< MDIX status change
#define MII_BCM54XX_INT_PSERR	0x4000 ///< Pair swap error

#define MII_BCM54XX_SHD	0x1c ///< 0x1c shadow registers
#define MII_BCM54XX_SHD_WRITE	0x8000

/** Broadcom Auxilliary Control Shadow Access Registers (PHY REG 0x18) */
#define MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL	0x00
#define MII_BCM54XX_AUXCTL_ACTL_TX_6DB	0x0400
#define MII_BCM54XX_AUXCTL_ACTL_SMDSP_ENA	0x0800

#define MII_BCM54XX_AUXCTL_SHDWSEL_MISC	0x07
#define MII_BCM54XX_AUXCTL_SHDWSEL_MISC_WIRESPEED_EN	0x0010
#define MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN	0x0100
#define MII_BCM54XX_AUXCTL_MISC_FORCE_AMDIX	0x0200
#define MII_BCM54XX_AUXCTL_MISC_WREN	0x8000

#define MII_BCM54XX_AUXCTL_SHDWSEL_READ_SHIFT	12
#define MII_BCM54XX_AUXCTL_SHDWSEL_MASK	0x0007

/** Broadcom LED source encodings (These are used in BCM5461, BCM5481,BCM5482, and possibly some others) */
#define BCM_LED_SRC_LINKSPD1	0x0
#define BCM_LED_SRC_LINKSPD2	0x1
#define BCM_LED_SRC_XMITLED	0x2
#define BCM_LED_SRC_ACTIVITYLED	0x3
#define BCM_LED_SRC_FDXLED	0x4
#define BCM_LED_SRC_SLAVE	0x5
#define BCM_LED_SRC_INTR	0x6
#define BCM_LED_SRC_QUALITY	0x7
#define BCM_LED_SRC_RCVLED	0x8
#define BCM_LED_SRC_WIRESPEED	0x9
#define BCM_LED_SRC_MULTICOLOR1	0xa
#define BCM_LED_SRC_OPENSHORT	0xb
#define BCM_LED_SRC_OFF	0xe ///< Tied high
#define BCM_LED_SRC_ON	0xf ///< Tied low

/** Broadcom Multicolor LED configurations (expansion register 4) */
#define BCM_EXP_MULTICOLOR	(MII_BCM54XX_EXP_SEL_ER + 0x04)
#define BCM_LED_MULTICOLOR_IN_PHASE	1 << 8
#define BCM_LED_MULTICOLOR_LINK_ACT	0x0
#define BCM_LED_MULTICOLOR_SPEED	0x1
#define BCM_LED_MULTICOLOR_ACT_FLASH	0x2
#define BCM_LED_MULTICOLOR_FDX	0x3
#define BCM_LED_MULTICOLOR_OFF	0x4
#define BCM_LED_MULTICOLOR_ON	0x5
#define BCM_LED_MULTICOLOR_ALT	0x6
#define BCM_LED_MULTICOLOR_FLASH	0x7
#define BCM_LED_MULTICOLOR_LINK	0x8
#define BCM_LED_MULTICOLOR_ACT	0x9
#define BCM_LED_MULTICOLOR_PROGRAM	0xa

/** BCM5482 Shadow registers */
/** Shadow values go into bits [14:10] of register 0x1c to select a shadow register to access */
/** 00100: Reserved control register 2 */
#define BCM54XX_SHD_SCR2	0x04
#define BCM54XX_SHD_SCR2_WSPD_RTRY_DIS	0x100
#define BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_SHIFT	2
#define BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_OFFSET	2
#define BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_MASK	0x7

/** 00101: Spare Control Register 3 */
#define BCM54XX_SHD_SCR3	0x05
#define BCM54XX_SHD_SCR3_DEF_CLK125	0x0001
#define BCM54XX_SHD_SCR3_DLLAPD_DIS	0x0002
#define BCM54XX_SHD_SCR3_TRDDAPD	0x0004

/** 01010: Auto Power-Down */
#define BCM54XX_SHD_APD	0x0a
#define BCM_APD_CLR_MASK	0xFE9F ///< clear bits 5, 6 & 8
#define BCM54XX_SHD_APD_EN	0x0020
#define BCM_NO_ANEG_APD_EN	0x0060 ///< bits 5 & 6
#define BCM_APD_SINGLELP_EN	0x0100 ///< Bit 8

#define BCM5482_SHD_LEDS1	0x0d ///< 01101: LED Selector 1
#define BCM54XX_SHD_RGMII_MODE	0x0b ///< 01011: RGMII Mode Selector
#define BCM5482_SHD_SSD	0x14 ///< 10100: Secondary SerDes control
#define BCM5482_SHD_SSD_LEDM	0x0008 ///< SSD LED Mode enable
#define BCM5482_SHD_SSD_EN	0x0001 ///< SSD enable
#define BCM5482_SHD_MODE	0x1f ///< 11111: Mode Control Register
#define BCM5482_SHD_MODE_1000BX	0x0001 ///< Enable 1000BASE-X registers

/** Expansion Shadow Access Registers (PHY REG 0x15, 0x16, and 0x17) */
#define MII_BCM54XX_EXP_AADJ1CH0	0x001f
#define MII_BCM54XX_EXP_AADJ1CH0_SWP_ABCD_OEN	0x0200
#define MII_BCM54XX_EXP_AADJ1CH0_SWSEL_THPF	0x0100
#define MII_BCM54XX_EXP_AADJ1CH3	0x601f
#define MII_BCM54XX_EXP_AADJ1CH3_ADCCKADJ	0x0002
#define MII_BCM54XX_EXP_EXP08	0x0F08
#define MII_BCM54XX_EXP_EXP08_RJCT_2MHZ	0x0001
#define MII_BCM54XX_EXP_EXP08_EARLY_DAC_WAKE	0x0200
#define MII_BCM54XX_EXP_EXP75	0x0f75
#define MII_BCM54XX_EXP_EXP75_VDACCTRL	0x003c
#define MII_BCM54XX_EXP_EXP75_CM_OSC	0x0001
#define MII_BCM54XX_EXP_EXP96	0x0f96
#define MII_BCM54XX_EXP_EXP96_MYST	0x0010
#define MII_BCM54XX_EXP_EXP97	0x0f97
#define MII_BCM54XX_EXP_EXP97_MYST	0x0c0c

/** BCM5482 Secondary SerDes registers */
#define BCM5482_SSD_1000BX_CTL	0x00 ///< 1000BASE-X Control
#define BCM5482_SSD_1000BX_CTL_PWRDOWN	0x0800 ///< Power-down SSD
#define BCM5482_SSD_SGMII_SLAVE	0x15 ///< SGMII Slave Register
#define BCM5482_SSD_SGMII_SLAVE_EN	0x0002 ///< Slave mode enable
#define BCM5482_SSD_SGMII_SLAVE_AD	0x0001 ///< Slave auto-detection

/** BCM54810 Registers */
#define BCM54810_EXP_BROADREACH_LRE_MISC_CTL	(MII_BCM54XX_EXP_SEL_ER + 0x90)
#define BCM54810_EXP_BROADREACH_LRE_MISC_CTL_EN	(1 << 0)
#define BCM54810_SHD_CLK_CTL	0x3
#define BCM54810_SHD_CLK_CTL_GTXCLK_EN	(1 << 9)

/** BCM54612E Registers */
#define BCM54612E_EXP_SPARE0	(MII_BCM54XX_EXP_SEL_ETC + 0x34)
#define BCM54612E_LED4_CLK125OUT_EN	(1 << 1)

/** GENET specific types (Broadcom Gigabit Ethernet controller) */
typedef struct _GENET_NETWORK GENET_NETWORK;

/** RX/TX Control Block */
typedef struct _GENET_CONTROL_BLOCK GENET_CONTROL_BLOCK;
struct _GENET_CONTROL_BLOCK
{
	size_t descriptoraddress;
	NETWORK_ENTRY *entry;
};


typedef GENET_CONTROL_BLOCK GENET_CONTROL_BLOCKS[GENET_TOTAL_DESC];

/** RX Ring Buffer */
typedef struct _GENET_RX_RING GENET_RX_RING;

typedef void STDCALL (*genet_rx_ring_int_enable_proc)(GENET_NETWORK *network, GENET_RX_RING *ring);
typedef void STDCALL (*genet_rx_ring_int_disable_proc)(GENET_NETWORK *network, GENET_RX_RING *ring);

struct _GENET_RX_RING
{
	GENET_NETWORK *network; ///< The owner of this RX ring
	WORKER_HANDLE worker; ///< Handle of worker currently servicing RX ring
	uint32_t index; ///< RX ring index
	uint32_t size; ///< RX ring size
	uint32_t consumer; ///< RX last consumer index
	uint32_t read; ///< RX ring read pointer
	uint32_t first; ///< RX ring initial CB ptr
	uint32_t last; ///< RX ring end CB ptr
	uint32_t olddiscards;
	GENET_CONTROL_BLOCKS *controlblocks; ///< RX ring buffer control block
	genet_rx_ring_int_enable_proc intenable;
	genet_rx_ring_int_disable_proc intdisable;
};


typedef GENET_RX_RING GENET_RX_RINGS[GENET_DESC_INDEX + 1];

/** TX Ring Buffer */
typedef struct _GENET_TX_RING GENET_TX_RING;

typedef void STDCALL (*genet_tx_ring_int_enable_proc)(GENET_NETWORK *network, GENET_TX_RING *ring);
typedef void STDCALL (*genet_tx_ring_int_disable_proc)(GENET_NETWORK *network, GENET_TX_RING *ring);

struct _GENET_TX_RING
{
	GENET_NETWORK *network; ///< The owner of this TX ring
	WORKER_HANDLE worker; ///< Handle of worker currently servicing TX ring
	uint32_t index; ///< TX ring index
	uint32_t queue; ///< TX queue index
	uint32_t size; ///< TX ring size
	uint32_t clean; ///< TX ring clean pointer
	uint32_t consumer; ///< TX last consumer index
	uint32_t free; ///< TX number of free descriptors
	uint32_t write; ///< TX ring write pointer SW copy
	uint32_t producer; ///< TX ring producer index SW copy
	uint32_t first; ///< TX ring initial CB ptr
	uint32_t last; ///< TX ring end CB ptr
	GENET_CONTROL_BLOCKS *controlblocks; ///< TX ring buffer control block
	genet_tx_ring_int_enable_proc intenable;
	genet_tx_ring_int_disable_proc intdisable;
};


typedef GENET_TX_RING GENET_TX_RINGS[GENET_DESC_INDEX + 1];

/** RX/TX DMA registers */
typedef uint8_t GENET_DMA_REGISTERS[DMA_RING_CFG - DMA_RING16_TIMEOUT + 1];

/** RX/TX DMA ring registers */
typedef uint8_t GENET_DMA_RING_REGISTERS[TDMA_READ_PTR - TDMA_WRITE_PTR_HI + 1];

struct _GENET_NETWORK
{
	// Network Properties
	NETWORK_DEVICE network;
	// Driver Properties
	uint32_t irq0;
	uint32_t irq1;
	void *address; ///< Device register base address
	uint32_t mdiooffset;
	SPIN_HANDLE lock; ///< Device lock (Differs from lock in Network device) (Spin lock due to use by interrupt handler)
	uint32_t version; ///< Device version (GENET_V1..GENETV5)
	uint32_t phyrevision; ///< PHY revision (GENET_V1..GENETV4 devices only)
	LONGBOOL status64enable; ///< True if 64 byte RX/TX status block is enabled (for hardware checksum etc)
	LONGBOOL rxchecksumenable; ///< True if RX checksum is enabled
	LONGBOOL crcforwardenable; ///< True if CRC forwarding is enabled
	uint32_t irqstatus; ///< Non TX/RX interrupts forwarded to worker thread for servicing
	uint32_t pendingcount; ///< Number of worker requests pending for this network
	THREAD_ID waiterthread; ///< Thread waiting for pending requests to complete (for network close)
	TIMER_HANDLE statustimer; ///< Timer for status change detection
	// Hardware Parameters (Version specific)
	uint32_t txqueues;
	uint32_t txdescriptorsperqueue;
	uint32_t rxqueues;
	uint32_t rxdescriptorsperqueue;
	uint32_t backpressureenableshift;
	uint32_t backpressuremask;
	uint32_t hfbfiltercount;
	uint32_t hfbfiltersize;
	uint32_t qtagmask;
	uint32_t txbufferoffset;
	uint32_t hfboffset;
	uint32_t hfbregoffset;
	uint32_t rxdmaoffset;
	uint32_t txdmaoffset;
	uint32_t wordsperdescriptor;
	uint32_t flags;
	uint32_t q16txdescriptorcount;
	uint32_t q16rxdescriptorcount;
	// DMA Parameters (Version specific)
	uint32_t dmarxcheckbit;
	uint32_t rxdmaregoffset;
	uint32_t txdmaregoffset;
	uint32_t dmadescriptorsize;
	GENET_DMA_REGISTERS dmaregisters;
	GENET_DMA_RING_REGISTERS dmaringregisters;
	// PHY Parameters
	uint32_t phyid; ///< PHY Identifier
	uint32_t phyaddr; ///< PHY Bus Address
	uint32_t phymode; ///< PHY Interface Mode
	uint32_t phyflags; ///< PHY Flags
	LONGBOOL phyinternal;
	LONGBOOL phyexternal;
	int32_t link; ///< 0 = Down / 1 = Up
	int32_t speed; ///< 10/100/1000 Mbps
	int32_t duplex; ///< 0 = Half / 1 = Full
	int32_t pause;
	int32_t oldlink;
	int32_t oldspeed;
	int32_t oldduplex;
	int32_t oldpause;
	// RX/TX Parameters
	GENET_RX_RINGS rxrings;
	GENET_TX_RINGS txrings;
	GENET_CONTROL_BLOCKS *rxcontrolblocks;
	GENET_CONTROL_BLOCKS *txcontrolblocks;
	// Statistics Properties
	uint32_t interruptcount; ///< Number of interrupt requests received by the device
};


typedef struct _GENET_STATUS64 GENET_STATUS64;
struct _GENET_STATUS64
{
	uint32_t lengthstatus; ///< Length and peripheral status
	uint32_t extendedstatus; ///< Extended status
	uint32_t rxchecksum; ///< Partial RX checksum
	uint32_t unused1[9]; ///< Unused
	uint32_t txcheckusminfo; ///< TX checksum info
	uint32_t unused2[3]; ///< Unused
};


/** UniMAC specific types (Broadcom UniMAC MDIO bus controller) */
/** Nothing */

/** Initialization Functions */
void STDCALL genet_init(void);

/** GENET Functions */

/**
 * @brief Create and register a new GENET Network device which can be accessed using the Network API
 * @param Address The address of the GENET registers
 * @param MDIOOffset The offset from address of the MDIO registers
 * @param IRQ0 The interrupt number for interrupt 0 of the GENET
 * @param IRQ1 The interrupt number for interrupt 1 of the GENET
 * @return Pointer to the new Network device or nil if the Network device could not be created
 */
NETWORK_DEVICE * STDCALL genet_network_create(size_t address, uint32_t mdiooffset, uint32_t irq0, uint32_t irq1);

/**
 * @brief Close, deregister and destroy a GENET Network device created by this driver
 * @param Network The Network device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL genet_network_destroy(NETWORK_DEVICE *network);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_GENET_H
