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
#ifndef _ULTIBO_NETWORK_H
#define _ULTIBO_NETWORK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* Network specific constants */
#define NETWORK_NAME_PREFIX	"Network" // Name prefix for Network Devices

/* Network Device Types */
#define NETWORK_TYPE_NONE	0
#define NETWORK_TYPE_ETHERNET	1
#define NETWORK_TYPE_TOKENRING	2
#define NETWORK_TYPE_80211	3 // IEEE 802.11 Wireless (WiFi) network

#define NETWORK_TYPE_MAX	3

/* Network Device States */
#define NETWORK_STATE_CLOSED	0
#define NETWORK_STATE_CLOSING	1
#define NETWORK_STATE_OPENING	2
#define NETWORK_STATE_OPEN	3

#define NETWORK_STATE_MAX	3

/* Network Device Status */
#define NETWORK_STATUS_DOWN	0
#define NETWORK_STATUS_UP	1

#define NETWORK_STATUS_MAX	1

/* Network Device Flags */
#define NETWORK_FLAG_NONE	0x00000000
#define NETWORK_FLAG_RX_BUFFER	0x00000001 // Device supports Receive Buffer (NetworkBufferReceive/NetworkBufferRelease)
#define NETWORK_FLAG_TX_BUFFER	0x00000002 // Device supports Transmit Buffer (NetworkBufferAllocate/NetworkBufferTransmit)
#define NETWORK_FLAG_RX_MULTIPACKET	0x00000004 // Device supports multiple packets in the same Receive entry
#define NETWORK_FLAG_TX_MULTIPACKET	0x00000008 // Device supports multiple packets in the same Transmit entry

/* Network Device Control Codes */
#define NETWORK_CONTROL_CLEAR_STATS	1 // Clear Statistics
#define NETWORK_CONTROL_SET_MAC	2 // Set the MAC for this device
#define NETWORK_CONTROL_GET_MAC	3 // Get the MAC for this device
#define NETWORK_CONTROL_SET_LOOPBACK	4 // Set Loopback Mode
#define NETWORK_CONTROL_RESET	5 // Reset the device
#define NETWORK_CONTROL_DISABLE	6 // Disable the device
#define NETWORK_CONTROL_GET_HARDWARE	7 // Get Hardware address for this device
#define NETWORK_CONTROL_GET_BROADCAST	8 // Get Broadcast address for this device
#define NETWORK_CONTROL_GET_MTU	9 // Get MTU for this device
#define NETWORK_CONTROL_GET_HEADERLEN	10 // Get Header length for this device
#define NETWORK_CONTROL_GET_LINK	11 // Get link status for this device
#define NETWORK_CONTROL_GET_SPEED	12 // Get link speed for this device
#define NETWORK_CONTROL_GET_DUPLEX	13 // Get link speed for this device
#define NETWORK_CONTROL_RESET_LINK	14 // Reset link for this device
#define NETWORK_CONTROL_GET_STATS	15 // Get statistics for this device
#define NETWORK_CONTROL_ADD_MULTICAST	16 // Add a multicast address to this device
#define NETWORK_CONTROL_DEL_MULTICAST	17 // Delete a multicast address from this device
#define NETWORK_CONTROL_GET_MULTICAST	18 // Get the list of multicast address for this device

/* Network Link States */
#define NETWORK_LINK_DOWN	NETWORK_STATUS_DOWN
#define NETWORK_LINK_UP	NETWORK_STATUS_UP

/* Network Speed States */
#define NETWORK_SPEED_NONE	0
#define NETWORK_SPEED_10	10
#define NETWORK_SPEED_100	100
#define NETWORK_SPEED_1000	1000

/* Network Duplex States */
#define NETWORK_DUPLEX_NONE	0
#define NETWORK_DUPLEX_HALF	1
#define NETWORK_DUPLEX_FULL	2

/* Network Lock States */
#define NETWORK_LOCK_NONE	0
#define NETWORK_LOCK_READ	1
#define NETWORK_LOCK_WRITE	2

/* Network Buffer Size */
#define NETWORK_BUFFER_SIZE	1024

/* Network Events */
#define NETWORK_EVENT_NONE	0x00000000
#define NETWORK_EVENT_SYSTEM_START	0x00000001 // The network sub system is starting
#define NETWORK_EVENT_SYSTEM_STOP	0x00000002 // The network sub system has stopped
#define NETWORK_EVENT_ADAPTERS_START	0x00000004 // All network adapters are being started
#define NETWORK_EVENT_ADAPTERS_STOP	0x00000008 // All network adapters have been stopped
#define NETWORK_EVENT_TRANSPORTS_START	0x00000010 // All network transports are being started
#define NETWORK_EVENT_TRANSPORTS_STOP	0x00000020 // All network transports have been stopped
#define NETWORK_EVENT_PROTOCOLS_START	0x00000040 // All network protocols are being started
#define NETWORK_EVENT_PROTOCOLS_STOP	0x00000080 // All network protocols have been stopped

/* Network Event Signature */
#define NETWORK_EVENT_SIGNATURE	0xBE1D50C2

/* Network Event States */
#define NETWORK_EVENT_STATE_UNREGISTERED	0
#define NETWORK_EVENT_STATE_REGISTERED	1

/* Network Event Flags */
#define NETWORK_EVENT_FLAG_NONE	0x00000000

/* Adapter Types */
#define ADAPTER_TYPE_UNKNOWN	0
#define ADAPTER_TYPE_WIRED	1
#define ADAPTER_TYPE_LOOPBACK	2
#define ADAPTER_TYPE_WIRELESS	3
#define ADAPTER_TYPE_SLIP	4
#define ADAPTER_TYPE_PPP	5

/* Adapter Threads */
#define ADAPTER_THREAD_NAME	"Network Adapter" // Thread name for Network adapter threads
#define ADAPTER_THREAD_PRIORITY	THREAD_PRIORITY_HIGHER // Thread priority for Network adapter threads

/* Adapter State */
#define ADAPTER_STATE_DISABLED	0
#define ADAPTER_STATE_ENABLED	1

/* Adapter Status */
#define ADAPTER_STATUS_DOWN	0
#define ADAPTER_STATUS_UP	1

/* Configuration Types */
#define CONFIG_TYPE_AUTO	0 
#define CONFIG_TYPE_STATIC	1
#define CONFIG_TYPE_RARP	2
#define CONFIG_TYPE_BOOTP	3
#define CONFIG_TYPE_DHCP	4
#define CONFIG_TYPE_PSEUDO	5
#define CONFIG_TYPE_LOOPBACK	6
#define CONFIG_TYPE_SLIP	7
#define CONFIG_TYPE_PPP	8

#define CONFIG_TYPE_UNKNOWN	Word(-1)

/* Authentication Types */
#define AUTH_TYPE_UNKNOWN	0
#define AUTH_TYPE_EAP	1
#define AUTH_TYPE_RSN	2

/* Frame Types */
#define FRAME_TYPE_UNKNOWN	0
#define FRAME_TYPE_ETHERNET_II	1 // Blue Book
#define FRAME_TYPE_TOKEN_RING	3 // IEEE 802.5
#define FRAME_TYPE_APPLETALK	5 // LocalTalk
#define FRAME_TYPE_ETHERNET_8022	11 // IEEE 802.2 LLC
#define FRAME_TYPE_ETHERNET_SNAP	98 // IEEE 802.2 LLC with SNAP Header
#define FRAME_TYPE_ETHERNET_8023	99 // 802.3 RAW (Novell)

#define FRAME_START_ETHERNET_SNAP	0xAAAA
#define FRAME_START_ETHERNET_8023	0xFFFF

#define ADAPTER_MODE_NONE	1
#define ADAPTER_MODE_LOCAL	2
#define ADAPTER_MODE_BROADCAST	3 // This is the default
#define ADAPTER_MODE_LOCAL_MULTI	4 // Mode 3 plus directed Multicast
#define ADAPTER_MODE_BROADCAST_MULTI	5 // Mode 3 plus all Multicast
#define ADAPTER_MODE_PROMISCUOUS	6 // Promiscuous mode

/* Configuration Commands */
#define CONFIG_ADAPTER_DISCOVER	0 // Discover an Address from the ConfigHandler
#define CONFIG_ADAPTER_REQUEST	1 // Request an Address from the ConfigHandler
#define CONFIG_ADAPTER_RELEASE	2 // Release the Address obtained from ConfigHandler
#define CONFIG_ADAPTER_RENEW	3 // Renew the Address obtained from ConfigHandler
#define CONFIG_ADAPTER_REBIND	4 // Rebind the Address obtained from ConfigHandler
#define CONFIG_ADAPTER_INFORM	5 // Obtain information only from the ConfigHandler
#define CONFIG_ADAPTER_REBOOT	6 // Request previous Address after a Reboot

#define CONFIG_RETRY_TIMEOUT	300000 // 5 min Config Retry Timeout
#define CONFIG_RENEW_TIMEOUT	60000 // 1 min Config Renew Timeout
#define CONFIG_REBIND_TIMEOUT	60000 // 1 min Config Rebind Timeout

/* Authentication Commands */
#define AUTH_COMMAND_ASSOCIATE	0
#define AUTH_COMMAND_DISASSOCIATE	1
#define AUTH_COMMAND_AUTHENTICATE	2
#define AUTH_COMMAND_UNAUTHENTICATE	3

/* Multicast Addressing */
#define MAX_MULTICAST_ADDRESS	8 // Maximum number of addresses per adapter

#define MAX_PHYSICAL_PACKET	2048 // Large enough for all media types

/* Hardare Addressing */
#define HARDWARE_ADDRESS_SIZE	6 // SizeOf(THardwareAddress)

/* Media Types */
#define MEDIA_TYPE_UNKNOWN	0x0000

#define MEDIA_TYPE_ETHERNET	0x0001 // ARP type of Ethernet Hardware (This value must not change, it is the actual values used by ARP packets)
#define MEDIA_TYPE_TOKENRING	0x0006 // ARP type of Token-Ring Hardware (This value must not change, it is the actual values used by ARP packets)
#define MEDIA_TYPE_IEEE80211	0x1000
#define MEDIA_TYPE_LOOPBACK	0x1001
#define MEDIA_TYPE_PPP	0x1002
#define MEDIA_TYPE_SLIP	0x1003

/* Packet Types */
#define PACKET_MIN_TYPE	0x0600 // If the value Ethernet header TypeLength field is greater than this the frame is Ethernet II

#define PACKET_TYPE_IP	0x0800
#define PACKET_TYPE_IP6	0x86DD
#define PACKET_TYPE_ARP	0x0806
#define PACKET_TYPE_RARP	0x8035
#define PACKET_TYPE_8021Q	0x8100 // 802.1Q with extended Ethernet header
#define PACKET_TYPE_IPX	0x8137 // IPX on EII

#define PACKET_TYPE_EAPOL	0x888E // EAP-over-LAN (EAPOL)
#define PACKET_TYPE_RSN	0x88C7 // RSN pre-authentication
#define PACKET_TYPE_TDLS	0x890D // Tunneled direct-link setup

#define PACKET_TYPE_RAW	0xFFFF // IPX on 802.3
#define PACKET_TYPE_LLC	0x0001 // IPX on 802.2

/* Generic MII registers (Management Interface) */
#define MII_BMCR	0x00 // Basic mode control register
#define MII_BMSR	0x01 // Basic mode status register 
#define MII_PHYSID1	0x02 // PHYS ID 1
#define MII_PHYSID2	0x03 // PHYS ID 2
#define MII_ADVERTISE	0x04 // Advertisement control reg
#define MII_LPA	0x05 // Link partner ability reg
#define MII_EXPANSION	0x06 // Expansion register
#define MII_CTRL1000	0x09 // 1000BASE-T control
#define MII_STAT1000	0x0a // 1000BASE-T status
#define MII_MMD_CTRL	0x0d // MMD Access Control Register
#define MII_MMD_DATA	0x0e // MMD Access Data Register
#define MII_ESTATUS	0x0f // Extended Status
#define MII_DCOUNTER	0x12 // Disconnect counter
#define MII_FCSCOUNTER	0x13 // False carrier counter
#define MII_NWAYTEST	0x14 // N-way auto-neg test reg
#define MII_RERRCOUNTER	0x15 // Receive error counter
#define MII_SREVISION	0x16 // Silicon revision
#define MII_RESV1	0x17 // Reserved...
#define MII_LBRERROR	0x18 // Lpback, rx, bypass error
#define MII_PHYADDR	0x19 // PHY address
#define MII_RESV2	0x1a // Reserved...
#define MII_TPISTATUS	0x1b // TPI status for 10mbps
#define MII_NCONFIG	0x1c // Network interface config

/* Basic mode control register */
#define BMCR_RESV	0x003f // Unused...
#define BMCR_SPEED1000	0x0040 // MSB of Speed (1000)
#define BMCR_CTST	0x0080 // Collision test
#define BMCR_FULLDPLX	0x0100 // Full duplex
#define BMCR_ANRESTART	0x0200 // Auto negotiation restart
#define BMCR_ISOLATE	0x0400 // Isolate data paths from MII
#define BMCR_PDOWN	0x0800 // Enable low power state
#define BMCR_ANENABLE	0x1000 // Enable auto negotiation
#define BMCR_SPEED100	0x2000 // Select 100Mbps
#define BMCR_LOOPBACK	0x4000 // TXD loopback bits
#define BMCR_RESET	0x8000 // Reset to default state

/* Basic mode status register */
#define BMSR_ERCAP	0x0001 // Ext-reg capability
#define BMSR_JCD	0x0002 // Jabber detected
#define BMSR_LSTATUS	0x0004 // Link status
#define BMSR_ANEGCAPABLE	0x0008 // Able to do auto-negotiation
#define BMSR_RFAULT	0x0010 // Remote fault detected
#define BMSR_ANEGCOMPLETE	0x0020 // Auto-negotiation complete
#define BMSR_RESV	0x00c0 // Unused...
#define BMSR_ESTATEN	0x0100 // Extended Status in R15
#define BMSR_100HALF2	0x0200 // Can do 100BASE-T2 HDX
#define BMSR_100FULL2	0x0400 // Can do 100BASE-T2 FDX
#define BMSR_10HALF	0x0800 // Can do 10mbps, half-duplex
#define BMSR_10FULL	0x1000 // Can do 10mbps, full-duplex
#define BMSR_100HALF	0x2000 // Can do 100mbps, half-duplex
#define BMSR_100FULL	0x4000 // Can do 100mbps, full-duplex
#define BMSR_100BASE4	0x8000 // Can do 100mbps, 4k packets

/* Advertisement control register */
#define ADVERTISE_SLCT	0x001f // Selector bits
#define ADVERTISE_CSMA	0x0001 // Only selector supported
#define ADVERTISE_10HALF	0x0020 // Try for 10mbps half-duplex
#define ADVERTISE_1000XFULL	0x0020 // Try for 1000BASE-X full-duplex
#define ADVERTISE_10FULL	0x0040 // Try for 10mbps full-duplex
#define ADVERTISE_1000XHALF	0x0040 // Try for 1000BASE-X half-duplex
#define ADVERTISE_100HALF	0x0080 // Try for 100mbps half-duplex
#define ADVERTISE_1000XPAUSE	0x0080 // Try for 1000BASE-X pause
#define ADVERTISE_100FULL	0x0100 // Try for 100mbps full-duplex
#define ADVERTISE_1000XPSE_ASYM	0x0100 // Try for 1000BASE-X asym pause
#define ADVERTISE_100BASE4	0x0200 // Try for 100mbps 4k packets
#define ADVERTISE_PAUSE_CAP	0x0400 // Try for pause
#define ADVERTISE_PAUSE_ASYM	0x0800 // Try for asymetric pause
#define ADVERTISE_RESV	0x1000 // Unused...
#define ADVERTISE_RFAULT	0x2000 // Say we can detect faults
#define ADVERTISE_LPACK	0x4000 // Ack link partners response
#define ADVERTISE_NPAGE	0x8000 // Next page bit

#define ADVERTISE_FULL	ADVERTISE_100FULL | ADVERTISE_10FULL | ADVERTISE_CSMA
#define ADVERTISE_ALL	ADVERTISE_10HALF | ADVERTISE_10FULL | ADVERTISE_100HALF | ADVERTISE_100FULL

/* Link partner ability register */
#define LPA_SLCT	0x001f // Same as advertise selector
#define LPA_10HALF	0x0020 // Can do 10mbps half-duplex
#define LPA_1000XFULL	0x0020 // Can do 1000BASE-X full-duplex
#define LPA_10FULL	0x0040 // Can do 10mbps full-duplex
#define LPA_1000XHALF	0x0040 // Can do 1000BASE-X half-duplex
#define LPA_100HALF	0x0080 // Can do 100mbps half-duplex
#define LPA_1000XPAUSE	0x0080 // Can do 1000BASE-X pause
#define LPA_100FULL	0x0100 // Can do 100mbps full-duplex
#define LPA_1000XPAUSE_ASYM	0x0100 // Can do 1000BASE-X pause asym
#define LPA_100BASE4	0x0200 // Can do 100mbps 4k packets
#define LPA_PAUSE_CAP	0x0400 // Can pause
#define LPA_PAUSE_ASYM	0x0800 // Can pause asymetrically
#define LPA_RESV	0x1000 // Unused...
#define LPA_RFAULT	0x2000 // Link partner faulted
#define LPA_LPACK	0x4000 // Link partner acked us
#define LPA_NPAGE	0x8000 // Next page bit

#define LPA_DUPLEX	LPA_10FULL | LPA_100FULL
#define LPA_100	LPA_100FULL | LPA_100HALF | LPA_100BASE4

/* Expansion register for auto-negotiation */
#define EXPANSION_NWAY	0x0001 // Can do N-way auto-nego
#define EXPANSION_LCWP	0x0002 // Got new RX page code word
#define EXPANSION_ENABLENPAGE	0x0004 // This enables npage words
#define EXPANSION_NPCAPABLE	0x0008 // Link partner supports npage
#define EXPANSION_MFAULTS	0x0010 // Multiple faults detected
#define EXPANSION_RESV	0xffe0 // Unused...

#define ESTATUS_1000_TFULL	0x2000 // Can do 1000BT Full
#define ESTATUS_1000_THALF	0x1000 // Can do 1000BT Half

/* N-way test register */
#define NWAYTEST_RESV1	0x00ff // Unused...
#define NWAYTEST_LOOPBACK	0x0100 // Enable loopback for N-way
#define NWAYTEST_RESV2	0xfe00 // Unused...

/* 1000BASE-T Control register */
#define ADVERTISE_1000FULL	0x0200 // Advertise 1000BASE-T full duplex
#define ADVERTISE_1000HALF	0x0100 // Advertise 1000BASE-T half duplex
#define CTL1000_AS_MASTER	0x0800
#define CTL1000_ENABLE_MASTER	0x1000

/* 1000BASE-T Status register */
#define LPA_1000MSFAIL	0x8000 // Master/Slave resolution failure
#define LPA_1000LOCALRXOK	0x2000 // Link partner local receiver status
#define LPA_1000REMRXOK	0x1000 // Link partner remote receiver status
#define LPA_1000FULL	0x0800 // Link partner 1000BASE-T full duplex
#define LPA_1000HALF	0x0400 // Link partner 1000BASE-T half duplex

/* Flow control flags */
#define FLOW_CTRL_TX	0x01
#define FLOW_CTRL_RX	0x02

/* MMD Access Control register fields */
#define MII_MMD_CTRL_DEVAD_MASK	0x1f // Mask MMD DEVAD
#define MII_MMD_CTRL_ADDR	0x0000 // Address
#define MII_MMD_CTRL_NOINCR	0x4000 // no post increment
#define MII_MMD_CTRL_INCR_RDWT	0x8000 // post increment on reads & writes
#define MII_MMD_CTRL_INCR_ON_WT	0xC000 // post increment on writes only

/* PHY Link State */
#define PHY_LINK_DOWN	0
#define PHY_LINK_UP	1

#define PHY_LINK_UNKNOWN	-1

/* PHY Interface Modes */
#define PHY_INTERFACE_MODE_NONE	0
#define PHY_INTERFACE_MODE_INTERNAL	1
#define PHY_INTERFACE_MODE_MII	2
#define PHY_INTERFACE_MODE_GMII	3
#define PHY_INTERFACE_MODE_SGMII	4
#define PHY_INTERFACE_MODE_TBI	5
#define PHY_INTERFACE_MODE_REVMII	6
#define PHY_INTERFACE_MODE_RMII	7
#define PHY_INTERFACE_MODE_RGMII	8
#define PHY_INTERFACE_MODE_RGMII_ID	9
#define PHY_INTERFACE_MODE_RGMII_RXID	10
#define PHY_INTERFACE_MODE_RGMII_TXID	11
#define PHY_INTERFACE_MODE_RTBI	12
#define PHY_INTERFACE_MODE_SMII	13
#define PHY_INTERFACE_MODE_XGMII	14
#define PHY_INTERFACE_MODE_MOCA	15
#define PHY_INTERFACE_MODE_QSGMII	16
#define PHY_INTERFACE_MODE_TRGMII	17
#define PHY_INTERFACE_MODE_1000BASEX	18
#define PHY_INTERFACE_MODE_2500BASEX	19
#define PHY_INTERFACE_MODE_RXAUI	20
#define PHY_INTERFACE_MODE_XAUI	21
#define PHY_INTERFACE_MODE_10GKR	22 // 10GBASE-KR, XFI, SFI - single lane 10G Serdes
#define PHY_INTERFACE_MODE_USXGMII	23

/* PHY Link Speeds */
#define PHY_SPEED_10	10
#define PHY_SPEED_100	100
#define PHY_SPEED_1000	1000

#define PHY_SPEED_UNKNOWN	-1

/* PHY Duplex Modes */
#define PHY_DUPLEX_HALF	0
#define PHY_DUPLEX_FULL	1

#define PHY_DUPLEX_UNKNOWN	-1

/* Service Sets */
#define SERVICE_SET_UNKNOWN	0
#define SERVICE_SET_BSS	1 // Basic Service Set
#define SERVICE_SET_ESS	2 // Extended Service Set
#define SERVICE_SET_IBSS	3 // Independent Basic Service Set
#define SERVICE_SET_MBSS	4 // Mesh Basic Service Set

/* ============================================================================== */
/* Ethernet specific constants */
#define ETHERNET_ADDRESS_SIZE	6 // SizeOf(TEthernetAddress)
#define ETHERNET_HEADER_SIZE	14 // SizeOf(TEthernetHeader)
#define ETHERNET_VLAN_SIZE	4 // Length of Ethernet VLAN tag
#define ETHERNET_CRC_SIZE	4 // Length of Ethernet CRC (FCS)

/* Ethernet specific sizes */
#define ETHERNET_MTU	1500
#define ETHERNET_MIN_PAYLOAD	46
#define ETHERNET_MIN_PACKET_SIZE	ETHERNET_HEADER_SIZE + ETHERNET_VLAN_SIZE + ETHERNET_MIN_PAYLOAD
#define ETHERNET_MAX_PACKET_SIZE	ETHERNET_HEADER_SIZE + ETHERNET_VLAN_SIZE + ETHERNET_MTU

#define ETHERNET_TRANSMIT_BUFFER_SIZE	ETHERNET_MAX_PACKET_SIZE

/* Ethernet 802.3 Network */
#define LLC_HEADER_SIZE	3 // SizeOf(TLLCHeader)

/* Ethernet SNAP Network */
#define SNAP_HEADER_SIZE	5 // SizeOf(TSNAPHeader)

/* ============================================================================== */
/* Network specific types */
typedef uint8_t HARDWARE_ADDRESS[HARDWARE_ADDRESS_SIZE];

typedef HARDWARE_ADDRESS HARDWARE_ADDRESSES[];

typedef HARDWARE_ADDRESS MULTICAST_ADDRESSES[MAX_MULTICAST_ADDRESS];

typedef struct _PACKET_FRAGMENT PACKET_FRAGMENT;
struct _PACKET_FRAGMENT
{
	int size;
	void *data;
	PACKET_FRAGMENT *next;
};

/* Adapter Statistics */
typedef struct _ADAPTER_STATISTICS ADAPTER_STATISTICS;
struct _ADAPTER_STATISTICS
{
	uint64_t packetsin;
	uint64_t packetsout;
	uint64_t bytesin;
	uint64_t bytesout;
	uint64_t errorsin;
	uint64_t errorsout;
	uint64_t packetslost;
};

/* Network Packet */
typedef struct _NETWORK_PACKET NETWORK_PACKET;
struct _NETWORK_PACKET
{
	void *buffer; // Pointer to buffer (Set by driver that owns this packet)
	void *data; // Start of data within buffer (Set by driver that owns this packet)
	int32_t length; // Length of packet data (Set by driver on Receive / Set by caller on Transmit, contains maximum length on Allocate)
	uint32_t flags; // Packet specific flags (eg Error, Broadcast etc) (Dependent on network type)
};

/* Network Buffer */
typedef struct _NETWORK_BUFFER NETWORK_BUFFER;
struct _NETWORK_BUFFER
{
	SEMAPHORE_HANDLE wait; // Packet ready semaphore
	uint32_t start; // Index of first packet ready
	uint32_t count; // Number of packets ready in buffer
	NETWORK_PACKET *packets[NETWORK_BUFFER_SIZE];
};

/* Network Entry */
typedef struct _NETWORK_ENTRY NETWORK_ENTRY;
struct _NETWORK_ENTRY
{
	void *buffer; // Pointer to buffer (Allocated by driver that owns this entry)
	uint32_t size; // Size of the buffer (Total size, usable size is Size minus Offset)
	uint32_t offset; // Offset to start of data (Data for first packet will be at Buffer plus Offset, must be less than size)
	uint32_t count; // Number of packets in the entry (Set by driver that owns this entry, must be at least one)
	void *driverdata; // Driver private data (Managed by driver that owns this entry)
	NETWORK_PACKET *packets[]; // Array of 0 to Count - 1 packets in this entry (Allocated by driver that owns this entry, must be at least one)
};

/* Network Queue */
typedef struct _NETWORK_QUEUE NETWORK_QUEUE;
struct _NETWORK_QUEUE
{
	BUFFER_HANDLE buffer; // Handle for entry buffers
	SEMAPHORE_HANDLE wait; // Entry ready semaphore
	uint32_t start; // Index of first entry ready
	uint32_t count; // Number of entries ready in queue
	uint32_t flags; // Queue specific flags (eg Paused, Halted etc) (Managed by driver)
	NETWORK_ENTRY *entries[]; // Array of 0 to Total - 1 entries in this queue (Allocated by driver that owns this queue)
};

/* Network Statistics (Returned by NETWORK_CONTROL_GET_STATS) */
typedef struct _NETWORK_STATISTICS NETWORK_STATISTICS;
struct _NETWORK_STATISTICS
{
	uint64_t receivebytes;
	uint64_t receivecount;
	uint64_t receiveerrors;
	uint64_t transmitbytes;
	uint64_t transmitcount;
	uint64_t transmiterrors;
	uint64_t statuscount;
	uint64_t statuserrors;
	uint64_t bufferoverruns;
	uint64_t bufferunavailable;
};

/* Network Device */
typedef struct _NETWORK_DEVICE NETWORK_DEVICE;

/* Network Enumeration Callback */
typedef uint32_t STDCALL (*network_enumerate_cb)(NETWORK_DEVICE *network, void *data);
/* Network Notification Callback */
typedef uint32_t STDCALL (*network_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Network Device Methods */
typedef uint32_t STDCALL (*network_device_open_proc)(NETWORK_DEVICE *network);
typedef uint32_t STDCALL (*network_device_close_proc)(NETWORK_DEVICE *network);
typedef uint32_t STDCALL (*network_device_read_proc)(NETWORK_DEVICE *network, void *buffer, uint32_t size, uint32_t *length);
typedef uint32_t STDCALL (*network_device_write_proc)(NETWORK_DEVICE *network, void *buffer, uint32_t size, uint32_t *length);
typedef uint32_t STDCALL (*network_device_control_proc)(NETWORK_DEVICE *network, int request, size_t argument1, size_t *argument2);

typedef uint32_t STDCALL (*network_buffer_allocate_proc)(NETWORK_DEVICE *network, NETWORK_ENTRY *entry);
typedef uint32_t STDCALL (*network_buffer_release_proc)(NETWORK_DEVICE *network, NETWORK_ENTRY *entry);
typedef uint32_t STDCALL (*network_buffer_receive_proc)(NETWORK_DEVICE *network, NETWORK_ENTRY *entry);
typedef uint32_t STDCALL (*network_buffer_transmit_proc)(NETWORK_DEVICE *network, NETWORK_ENTRY *entry);

struct _NETWORK_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Network
	// Network Properties
	uint32_t networkid; // Unique Id of this Network in the Network table
	uint32_t networkstate; // Network state (eg NETWORK_STATE_OPEN)
	uint32_t networkstatus; // Network status (eg NETWORK_STATUS_UP)
	network_device_open_proc deviceopen; // A Device specific DeviceOpen method implementing a standard Network device interface
	network_device_close_proc deviceclose; // A Device specific DeviceClose method implementing a standard Network device interface
	network_device_read_proc deviceread; // A Device specific DeviceRead method implementing a standard Network device interface
	network_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing a standard Network device interface
	network_device_control_proc devicecontrol; // A Device specific DeviceControl method implementing a standard Network device interface
	network_buffer_allocate_proc bufferallocate; // A Device specific BufferAllocate method implementing a standard Network device interface
	network_buffer_release_proc bufferrelease; // A Device specific BufferRelease method implementing a standard Network device interface
	network_buffer_receive_proc bufferreceive; // A Device specific BufferReceive method implementing a standard Network device interface
	network_buffer_transmit_proc buffertransmit; // A Device specific BufferTransmit method implementing a standard Network device interface
	// Driver Properties
	MUTEX_HANDLE lock; // Network lock
	NETWORK_BUFFER buffer; // Network receive buffer
	SEMAPHORE_HANDLE transmitwait; // Transmit complete semaphore
	BUFFER_HANDLE receivebuffer; // Buffer for receive packets
	BUFFER_HANDLE transmitbuffer; // Buffer for transmit packets
	NETWORK_QUEUE receivequeue; // Queue for receive packets
	NETWORK_QUEUE transmitqueue; // Queue for transmit packets (If applicable)
	// Statistics Properties
	uint64_t receivebytes;
	uint64_t receivecount;
	uint64_t receiveerrors;
	uint64_t transmitbytes;
	uint64_t transmitcount;
	uint64_t transmiterrors;
	uint64_t statuscount;
	uint64_t statuserrors;
	uint64_t bufferoverruns;
	uint64_t bufferunavailable;
	// Internal Properties
	NETWORK_DEVICE *prev; // Previous entry in Network table
	NETWORK_DEVICE *next; // Next entry in Network table
};

/* Network Event */
typedef struct _NETWORK_EVENT NETWORK_EVENT;

/* Network Event Callback */
typedef uint32_t STDCALL (*network_event_callback_cb)(void *data, uint32_t event);

struct _NETWORK_EVENT
{
	// Event Properties
	uint32_t signature; // Signature for entry validation
	uint32_t eventstate; // Event state (eg Registered/Unregistered)
	uint32_t eventflags; // Event flags (eg NETWORK_EVENT_FLAG_NONE)
	network_event_callback_cb callback; // The callback for network events
	void *data; // A pointer to callback specific data to be passed with events (Optional)
	uint32_t event; // The mask of events to notify on (eg NETWORK_EVENT_SYSTEM_START etc)
	// Internal Properties
	NETWORK_EVENT *prev; // Previous entry in Event table
	NETWORK_EVENT *next; // Next entry in Event table
};

/* ============================================================================== */
/* Network specific constants */
/* Generic Network */
const HARDWARE_ADDRESS HARDWARE_DEFAULT = {0x00,0x00,0x00,0x00,0x00,0x00};
const HARDWARE_ADDRESS HARDWARE_LOOPBACK = {0x00,0x00,0x00,0x00,0x00,0x01};
const HARDWARE_ADDRESS HARDWARE_BROADCAST = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

/* ============================================================================== */
/* Ethernet specific types */
typedef uint8_t ETHERNET_ADDRESS[ETHERNET_ADDRESS_SIZE];

/* Ethernet Network */
typedef struct _ETHERNET_HEADER ETHERNET_HEADER;
struct _ETHERNET_HEADER
{
	HARDWARE_ADDRESS destaddress;
	HARDWARE_ADDRESS sourceaddress;
	uint16_t typelength; // Length or Type (IEEE 802.3 or BlueBook/DIX Ethernet)
	uint8_t data[]; // Not part of header, included to provide a pointer to the start of data
} PACKED;

/* Ethernet 802.3 Network */
typedef struct _LLC_HEADER LLC_HEADER;
struct _LLC_HEADER
{
	uint8_t dsap;
	uint8_t ssap;
	uint8_t control;
	uint8_t information[]; // Optional (Control byte can be 1 or 2 octets)
} PACKED;

/* Ethernet SNAP Network */
typedef struct _SNAP_HEADER SNAP_HEADER;
struct _SNAP_HEADER
{
	uint8_t oui[3];
	uint16_t protocolid;
	uint8_t data[]; // Not part of header, included to provide a pointer to the start of data
} PACKED;

/* ============================================================================== */
/* Ethernet specific constants */
const HARDWARE_ADDRESS ETHERNET_DEFAULT = {0x00,0x00,0x00,0x00,0x00,0x00};
const HARDWARE_ADDRESS ETHERNET_LOOPBACK = {0x00,0x00,0x00,0x00,0x00,0x01};
const HARDWARE_ADDRESS ETHERNET_BROADCAST = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const HARDWARE_ADDRESS ETHERNET_MULTICAST = {0x01,0x00,0x5E,0x00,0x00,0x00};

/* ============================================================================== */
/* Initialization Functions */
uint32_t STDCALL network_start(void);
uint32_t STDCALL network_stop(void);

BOOL STDCALL network_start_completed(void);

/* ============================================================================== */
/* Network Functions */
uint32_t STDCALL network_device_open(NETWORK_DEVICE *network);
uint32_t STDCALL network_device_close(NETWORK_DEVICE *network);
uint32_t STDCALL network_device_read(NETWORK_DEVICE *network, void *buffer, uint32_t size, uint32_t *length);
uint32_t STDCALL network_device_write(NETWORK_DEVICE *network, void *buffer, uint32_t size, uint32_t *length);
uint32_t STDCALL network_device_control(NETWORK_DEVICE *network, int request, size_t argument1, size_t *argument2);

uint32_t STDCALL network_buffer_allocate(NETWORK_DEVICE *network, NETWORK_ENTRY *entry);
uint32_t STDCALL network_buffer_release(NETWORK_DEVICE *network, NETWORK_ENTRY *entry);
uint32_t STDCALL network_buffer_receive(NETWORK_DEVICE *network, NETWORK_ENTRY *entry);
uint32_t STDCALL network_buffer_transmit(NETWORK_DEVICE *network, NETWORK_ENTRY *entry);

uint32_t STDCALL network_device_set_state(NETWORK_DEVICE *network, uint32_t state);
uint32_t STDCALL network_device_set_status(NETWORK_DEVICE *network, uint32_t status);

NETWORK_DEVICE * STDCALL network_device_create(void);
NETWORK_DEVICE * STDCALL network_device_create_ex(uint32_t size);
uint32_t STDCALL network_device_destroy(NETWORK_DEVICE *network);

uint32_t STDCALL network_device_register(NETWORK_DEVICE *network);
uint32_t STDCALL network_device_deregister(NETWORK_DEVICE *network);

NETWORK_DEVICE * STDCALL network_device_find(uint32_t networkid);
NETWORK_DEVICE * STDCALL network_device_find_by_name(char *name);
NETWORK_DEVICE * STDCALL network_device_find_by_description(char *description);
uint32_t STDCALL network_device_enumerate(network_enumerate_cb callback, void *data);

uint32_t STDCALL network_device_notification(NETWORK_DEVICE *network, network_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

NETWORK_EVENT * STDCALL network_event_allocate(network_event_callback_cb callback, void *data, uint32_t event);
uint32_t STDCALL network_event_release(NETWORK_EVENT *event);

HANDLE STDCALL network_event_register(network_event_callback_cb callback, void *data, uint32_t event);
uint32_t STDCALL network_event_deregister(HANDLE handle);

uint32_t STDCALL network_event_notify(uint32_t event);

/* ============================================================================== */
/* Network Helper Functions */
int32_t STDCALL network_get_last_error(void);
void STDCALL network_set_last_error(int32_t error);

uint32_t STDCALL network_get_count(void);

NETWORK_DEVICE * STDCALL network_device_check(NETWORK_DEVICE *network);

uint32_t STDCALL network_device_type_to_string(uint32_t networktype, char *string, uint32_t len);
uint32_t STDCALL network_device_state_to_string(uint32_t networkstate, char *string, uint32_t len);
uint32_t STDCALL network_device_status_to_string(uint32_t networkstatus, char *string, uint32_t len);

uint32_t STDCALL network_device_state_to_notification(uint32_t state);
uint32_t STDCALL network_device_status_to_notification(uint32_t status);

NETWORK_EVENT * STDCALL network_event_check(NETWORK_EVENT *event);

uint32_t STDCALL hardware_address_to_string(HARDWARE_ADDRESS *address, char *separator, char *string, uint32_t len);
void STDCALL string_to_hardware_address(char *string, HARDWARE_ADDRESS *address);

BOOL STDCALL valid_hardware_address(HARDWARE_ADDRESS *address);
void STDCALL random_hardware_address(HARDWARE_ADDRESS *address);

BOOL STDCALL compare_hardware_address(HARDWARE_ADDRESS *address1, HARDWARE_ADDRESS *address2);
BOOL STDCALL compare_hardware_default(HARDWARE_ADDRESS *address);
BOOL STDCALL compare_hardware_broadcast(HARDWARE_ADDRESS *address);
BOOL STDCALL compare_hardware_multicast(HARDWARE_ADDRESS *address);

uint32_t STDCALL adapter_type_to_string(uint16_t _type, char *string, uint32_t len);
uint32_t STDCALL adapter_mode_to_string(uint16_t mode, char *string, uint32_t len);
uint32_t STDCALL adapter_config_to_string(uint16_t config, char *string, uint32_t len);
uint32_t STDCALL adapter_state_to_string(int state, char *string, uint32_t len);
uint32_t STDCALL adapter_status_to_string(int status, char *string, uint32_t len);

uint32_t STDCALL frame_type_to_string(uint16_t _type, char *string, uint32_t len);
uint32_t STDCALL media_type_to_string(uint16_t _type, char *string, uint32_t len);
uint32_t STDCALL packet_type_to_string(uint16_t _type, char *string, uint32_t len);

uint32_t STDCALL config_type_to_string(uint16_t _type, char *string, uint32_t len);
uint32_t STDCALL config_command_to_string(uint16_t command, char *string, uint32_t len);

uint32_t STDCALL auth_type_to_string(uint16_t _type, char *string, uint32_t len);
uint32_t STDCALL auth_command_to_string(uint16_t command, char *string, uint32_t len);

uint32_t STDCALL phy_interface_mode_to_string(uint16_t mode, char *string, uint32_t len);
uint32_t STDCALL phy_link_speed_to_string(uint16_t speed, char *string, uint32_t len);
uint32_t STDCALL phy_duplex_mode_to_string(uint16_t mode, char *string, uint32_t len);

uint16_t STDCALL match_string_to_phy_interface_mode(char *mode);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_NETWORK_H