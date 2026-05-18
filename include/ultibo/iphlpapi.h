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
#ifndef _ULTIBO_IPHLPAPI_H
#define _ULTIBO_IPHLPAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/ultibo.h"

/** IP Helper specific constants */
#define MAX_INTERFACE_NAME_LEN	256
#define IPRTRMGR_PID	10000
#define ANY_SIZE	1

#define MAX_ADAPTER_NAME	128

#define MAX_ADAPTER_DESCRIPTION_LENGTH	128
#define MAX_ADAPTER_NAME_LENGTH	256
#define MAX_ADAPTER_ADDRESS_LENGTH	8
#define DEFAULT_MINIMUM_ENTITIES	32
#define MAX_HOSTNAME_LEN	128
#define MAX_DOMAIN_NAME_LEN	128
#define MAX_SCOPE_ID_LEN	256

#define MAXLEN_IFDESCR	256
#define MAXLEN_PHYSADDR	8

#define MIB_IF_OPER_STATUS_NON_OPERATIONAL	0
#define MIB_IF_OPER_STATUS_UNREACHABLE	1
#define MIB_IF_OPER_STATUS_DISCONNECTED	2
#define MIB_IF_OPER_STATUS_CONNECTING	3
#define MIB_IF_OPER_STATUS_CONNECTED	4
#define MIB_IF_OPER_STATUS_OPERATIONAL	5

#define MIB_IF_TYPE_OTHER	1
#define MIB_IF_TYPE_ETHERNET	6
#define MIB_IF_TYPE_TOKENRING	9
#define MIB_IF_TYPE_FDDI	15
#define MIB_IF_TYPE_PPP	23
#define MIB_IF_TYPE_LOOPBACK	24
#define MIB_IF_TYPE_SLIP	28
#define MIB_IF_TYPE_IEEE80211	71

#define IF_TYPE_OTHER	MIB_IF_TYPE_OTHER
#define IF_TYPE_ETHERNET_CSMACD	MIB_IF_TYPE_ETHERNET
#define IF_TYPE_ISO88025_TOKENRING	MIB_IF_TYPE_TOKENRING
#define IF_TYPE_FDDI	MIB_IF_TYPE_FDDI
#define IF_TYPE_PPP	MIB_IF_TYPE_PPP
#define IF_TYPE_SOFTWARE_LOOPBACK	MIB_IF_TYPE_LOOPBACK
#define IF_TYPE_ATM	MIB_IF_TYPE_SLIP
#define IF_TYPE_IEEE80211	MIB_IF_TYPE_IEEE80211
#define IF_TYPE_TUNNEL	131
#define IF_TYPE_IEEE1394	144
#define IF_TYPE_IEEE80216_WMAN	237
#define IF_TYPE_WWANPP	243
#define IF_TYPE_WWANPP2	244

#define MIB_IF_ADMIN_STATUS_UP	1
#define MIB_IF_ADMIN_STATUS_DOWN	2
#define MIB_IF_ADMIN_STATUS_TESTING	3

#define MIB_TCP_RTO_OTHER	1
#define MIB_TCP_RTO_CONSTANT	2
#define MIB_TCP_RTO_RSRE	3
#define MIB_TCP_RTO_VANJ	4
#define MIB_TCP_MAXCONN_DYNAMIC	(DWORD)-1

#define MIB_TCP_STATE_CLOSED	1
#define MIB_TCP_STATE_LISTEN	2
#define MIB_TCP_STATE_SYN_SENT	3
#define MIB_TCP_STATE_SYN_RCVD	4
#define MIB_TCP_STATE_ESTAB	5
#define MIB_TCP_STATE_FIN_WAIT1	6
#define MIB_TCP_STATE_FIN_WAIT2	7
#define MIB_TCP_STATE_CLOSE_WAIT	8
#define MIB_TCP_STATE_CLOSING	9
#define MIB_TCP_STATE_LAST_ACK	10
#define MIB_TCP_STATE_TIME_WAIT	11
#define MIB_TCP_STATE_DELETE_TCB	12

#define MIB_USE_CURRENT_TTL	(DWORD)-1
#define MIB_USE_CURRENT_FORWARDING	(DWORD)-1

#define MIB_IP_FORWARDING	1
#define MIB_IP_NOT_FORWARDING	2

#define MIB_IPROUTE_TYPE_OTHER	1
#define MIB_IPROUTE_TYPE_INVALID	2
#define MIB_IPROUTE_TYPE_DIRECT	3
#define MIB_IPROUTE_TYPE_INDIRECT	4
#define MIB_IPROUTE_METRIC_UNUSED	(DWORD)-1

#define MIB_IPPROTO_OTHER	1
#define MIB_IPPROTO_LOCAL	2
#define MIB_IPPROTO_NETMGMT	3
#define MIB_IPPROTO_ICMP	4
#define MIB_IPPROTO_EGP	5
#define MIB_IPPROTO_GGP	6
#define MIB_IPPROTO_HELLO	7
#define MIB_IPPROTO_RIP	8
#define MIB_IPPROTO_IS_IS	9
#define MIB_IPPROTO_ES_IS	10
#define MIB_IPPROTO_CISCO	11
#define MIB_IPPROTO_BBN	12
#define MIB_IPPROTO_OSPF	13
#define MIB_IPPROTO_BGP	14
#define MIB_IPPROTO_NT_AUTOSTATIC	10002
#define MIB_IPPROTO_NT_STATIC	10006
#define MIB_IPPROTO_NT_STATIC_NON_DOD	10007

#define MIB_IPNET_TYPE_OTHER	1
#define MIB_IPNET_TYPE_INVALID	2
#define MIB_IPNET_TYPE_DYNAMIC	3
#define MIB_IPNET_TYPE_STATIC	4

/** IP Helper specific types */
typedef uint32_t IP_ADDR; ///< An IP address
typedef uint32_t IP_MASK; ///< An IP netmask
typedef uint32_t IP_STATUS; ///< Status code returned from IP APIs

typedef struct _MIB_IFNUMBER
{
	uint32_t dwvalue;
} MIB_IFNUMBER;

typedef struct _MIB_IFROW
{
	WCHAR wszname[MAX_INTERFACE_NAME_LEN];
	uint32_t dwindex;
	uint32_t dwtype;
	uint32_t dwmtu;
	uint32_t dwspeed;
	uint32_t dwphysaddrlen;
	uint8_t bphysaddr[MAXLEN_PHYSADDR];
	uint32_t dwadminstatus;
	uint32_t dwoperstatus;
	uint32_t dwlastchange;
	uint32_t dwinoctets;
	uint32_t dwinucastpkts;
	uint32_t dwinnucastpkts;
	uint32_t dwindiscards;
	uint32_t dwinerrors;
	uint32_t dwinunknownprotos;
	uint32_t dwoutoctets;
	uint32_t dwoutucastpkts;
	uint32_t dwoutnucastpkts;
	uint32_t dwoutdiscards;
	uint32_t dwouterrors;
	uint32_t dwoutqlen;
	uint32_t dwdescrlen;
	uint8_t bdescr[MAXLEN_IFDESCR];
} MIB_IFROW;

typedef struct _MIB_IFTABLE
{
	uint32_t dwnumentries;
	MIB_IFROW table[ANY_SIZE - 1];
} MIB_IFTABLE;

typedef struct _MIBICMPSTATS
{
	uint32_t dwmsgs;
	uint32_t dwerrors;
	uint32_t dwdestunreachs;
	uint32_t dwtimeexcds;
	uint32_t dwparmprobs;
	uint32_t dwsrcquenchs;
	uint32_t dwredirects;
	uint32_t dwechos;
	uint32_t dwechoreps;
	uint32_t dwtimestamps;
	uint32_t dwtimestampreps;
	uint32_t dwaddrmasks;
	uint32_t dwaddrmaskreps;
} MIBICMPSTATS;

typedef struct _MIBICMPINFO
{
	MIBICMPSTATS icmpinstats;
	MIBICMPSTATS icmpoutstats;
} MIBICMPINFO;

typedef struct _MIB_ICMP
{
	MIBICMPINFO stats;
} MIB_ICMP;

typedef struct _MIB_UDPSTATS
{
	uint32_t dwindatagrams;
	uint32_t dwnoports;
	uint32_t dwinerrors;
	uint32_t dwoutdatagrams;
	uint32_t dwnumaddrs;
} MIB_UDPSTATS;

typedef struct _MIB_UDPROW
{
	uint32_t dwlocaladdr;
	uint32_t dwlocalport;
} MIB_UDPROW;

typedef struct _MIB_UDPTABLE
{
	uint32_t dwnumentries;
	MIB_UDPROW table[ANY_SIZE - 1];
} MIB_UDPTABLE;

typedef struct _MIB_TCPSTATS
{
	uint32_t dwrtoalgorithm;
	uint32_t dwrtomin;
	uint32_t dwrtomax;
	uint32_t dwmaxconn;
	uint32_t dwactiveopens;
	uint32_t dwpassiveopens;
	uint32_t dwattemptfails;
	uint32_t dwestabresets;
	uint32_t dwcurrestab;
	uint32_t dwinsegs;
	uint32_t dwoutsegs;
	uint32_t dwretranssegs;
	uint32_t dwinerrs;
	uint32_t dwoutrsts;
	uint32_t dwnumconns;
} MIB_TCPSTATS;

typedef struct _MIB_TCPROW
{
	uint32_t dwstate;
	uint32_t dwlocaladdr;
	uint32_t dwlocalport;
	uint32_t dwremoteaddr;
	uint32_t dwremoteport;
} MIB_TCPROW;

typedef struct _MIB_TCPTABLE
{
	uint32_t dwnumentries;
	MIB_TCPROW table[ANY_SIZE - 1];
} MIB_TCPTABLE;

typedef struct _MIB_IPSTATS
{
	uint32_t dwforwarding;
	uint32_t dwdefaultttl;
	uint32_t dwinreceives;
	uint32_t dwinhdrerrors;
	uint32_t dwinaddrerrors;
	uint32_t dwforwdatagrams;
	uint32_t dwinunknownprotos;
	uint32_t dwindiscards;
	uint32_t dwindelivers;
	uint32_t dwoutrequests;
	uint32_t dwroutingdiscards;
	uint32_t dwoutdiscards;
	uint32_t dwoutnoroutes;
	uint32_t dwreasmtimeout;
	uint32_t dwreasmreqds;
	uint32_t dwreasmoks;
	uint32_t dwreasmfails;
	uint32_t dwfragoks;
	uint32_t dwfragfails;
	uint32_t dwfragcreates;
	uint32_t dwnumif;
	uint32_t dwnumaddr;
	uint32_t dwnumroutes;
} MIB_IPSTATS;

typedef struct _MIB_IPADDRROW
{
	uint32_t dwaddr;
	uint32_t dwindex;
	uint32_t dwmask;
	uint32_t dwbcastaddr;
	uint32_t dwreasmsize;
	uint16_t unused1;
	uint16_t unused2;
} MIB_IPADDRROW;

typedef struct _MIB_IPADDRTABLE
{
	uint32_t dwnumentries;
	MIB_IPADDRROW table[ANY_SIZE - 1];
} MIB_IPADDRTABLE;

typedef struct _MIB_IPFORWARDNUMBER
{
	uint32_t dwvalue;
} MIB_IPFORWARDNUMBER;

typedef struct _MIB_IPFORWARDROW
{
	uint32_t dwforwarddest;
	uint32_t dwforwardmask;
	uint32_t dwforwardpolicy;
	uint32_t dwforwardnexthop;
	uint32_t dwforwardifindex;
	uint32_t dwforwardtype;
	uint32_t dwforwardproto;
	uint32_t dwforwardage;
	uint32_t dwforwardnexthopas;
	uint32_t dwforwardmetric1;
	uint32_t dwforwardmetric2;
	uint32_t dwforwardmetric3;
	uint32_t dwforwardmetric4;
	uint32_t dwforwardmetric5;
} MIB_IPFORWARDROW;

typedef struct _MIB_IPFORWARDTABLE
{
	uint32_t dwnumentries;
	MIB_IPFORWARDROW table[ANY_SIZE - 1];
} MIB_IPFORWARDTABLE;

typedef struct _MIB_IPNETROW
{
	uint32_t dwindex;
	uint32_t dwphysaddrlen;
	uint8_t bphysaddr[MAXLEN_PHYSADDR];
	uint32_t dwaddr;
	uint32_t dwtype;
} MIB_IPNETROW;

typedef struct _MIB_IPNETTABLE
{
	uint32_t dwnumentries;
	MIB_IPNETROW table[ANY_SIZE - 1];
} MIB_IPNETTABLE;

typedef struct _IP_ADAPTER_INDEX_MAP
{
	ULONG index;
	WCHAR name[MAX_ADAPTER_NAME];
} IP_ADAPTER_INDEX_MAP;

typedef struct _IP_INTERFACE_INFO
{
	int32_t numadapters;
	IP_ADAPTER_INDEX_MAP adapter[0];
} IP_INTERFACE_INFO;

typedef struct _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS
{
	ULONG numadapters;
	IP_ADDR address[0];
} IP_UNIDIRECTIONAL_ADAPTER_ADDRESS;

typedef struct _IP_ADDRESS_STRING
{
	char s[16];
} IP_ADDRESS_STRING;

typedef IP_ADDRESS_STRING IP_MASK_STRING;

typedef struct _IP_ADDR_STRING
{
	struct _IP_ADDR_STRING *next;
	IP_ADDRESS_STRING ipaddress;
	IP_MASK_STRING ipmask;
	uint32_t context;
} IP_ADDR_STRING;

typedef struct _IP_ADAPTER_INFO
{
	struct _IP_ADAPTER_INFO *next;
	uint32_t comboindex;
	char adaptername[MAX_ADAPTER_NAME_LENGTH + 4];
	char description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
	UINT addresslength;
	uint8_t address[MAX_ADAPTER_ADDRESS_LENGTH];
	uint32_t index;
	UINT type_;
	UINT dhcpenabled;
	IP_ADDR_STRING *currentipaddress;
	IP_ADDR_STRING ipaddresslist;
	IP_ADDR_STRING gatewaylist;
	IP_ADDR_STRING dhcpserver;
	BOOL havewins;
	IP_ADDR_STRING primarywinsserver;
	IP_ADDR_STRING secondarywinsserver;
	time_t leaseobtained;
	time_t leaseexpires;
} IP_ADAPTER_INFO;

typedef struct _IP_PER_ADAPTER_INFO
{
	UINT autoconfigenabled;
	UINT autoconfigactive;
	IP_ADDR_STRING *currentdnsserver;
	IP_ADDR_STRING dnsserverlist;
} IP_PER_ADAPTER_INFO;

typedef struct _FIXED_INFO
{
	char hostname[MAX_HOSTNAME_LEN + 4];
	char domainname[MAX_DOMAIN_NAME_LEN + 4];
	IP_ADDR_STRING *currentdnsserver;
	IP_ADDR_STRING dnsserverlist;
	UINT nodetype;
	char scopeid[MAX_SCOPE_ID_LEN + 4];
	UINT enablerouting;
	UINT enableproxy;
	UINT enabledns;
} FIXED_INFO;

/** IP Helper Functions */

/**
 * @brief Retrieve the number of interfaces on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetNumberOfInterfaces(uint32_t *pdwnumif);

/**
 * @brief Retrieve information for the specified interface on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetIfEntry(MIB_IFROW *pifrow);

/**
 * @brief Retrieve the MIB-II interface table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetIfTable(MIB_IFTABLE *piftable, uint32_t *pdwsize, BOOL border);

/**
 * @brief Retrieve the interface to IPv4 address mapping table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetIpAddrTable(MIB_IPADDRTABLE *pipaddrtable, uint32_t *pdwsize, BOOL border);

/**
 * @brief Retrieve the IPv4 to physical address mapping table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetIpNetTable(MIB_IPNETTABLE *pipnettable, uint32_t *pdwsize, BOOL border);

/**
 * @brief Retrieve the IPv4 routing table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetIpForwardTable(MIB_IPFORWARDTABLE *pipforwardtable, uint32_t *pdwsize, BOOL border);

/**
 * @brief Retrieve the IPv4 TCP connection table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetTcpTable(MIB_TCPTABLE *ptcptable, uint32_t *pdwsize, BOOL border);

/**
 * @brief Retrieve the IPv4 User Datagram Protocol (UDP) listener table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetUdpTable(MIB_UDPTABLE *pudptable, uint32_t *pdwsize, BOOL border);

/**
 * @brief Retrieve the IP statistics for the current computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetIpStatistics(MIB_IPSTATS *pstats);

/**
 * @brief Retrieve the Internet Control Message Protocol (ICMP) for IPv4 statistics for the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetIcmpStatistics(MIB_ICMP *pstats);

/**
 * @brief Retrieve the TCP statistics for the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetTcpStatistics(MIB_TCPSTATS *pstats);

/**
 * @brief Retrieve the User Datagram Protocol (UDP) statistics for the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetUdpStatistics(MIB_UDPSTATS *pstats);

/**
 * @brief Set the administrative status of an interface
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL SetIfEntry(MIB_IFROW *pifrow);

/**
 * @brief Create a route in the local computer's IPv4 routing table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL CreateIpForwardEntry(MIB_IPFORWARDROW *proute);

/**
 * @brief Modify an existing route in the local computer's IPv4 routing table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL SetIpForwardEntry(MIB_IPFORWARDROW *proute);

/**
 * @brief Delete an existing route in the local computer's IPv4 routing table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL DeleteIpForwardEntry(MIB_IPFORWARDROW *proute);

/**
 * @brief Toggle IP forwarding on or off and set the default time-to-live (TTL) value for the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL SetIpStatistics(MIB_IPSTATS *pipstats);

/**
 * @brief Set the default time-to-live (TTL) value for the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL SetIpTTL(UINT nttl);

/**
 * @brief Create an Address Resolution Protocol (ARP) entry in the ARP table on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL CreateIpNetEntry(MIB_IPNETROW *parpentry);

/**
 * @brief Modify an existing ARP entry in the ARP table on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL SetIpNetEntry(MIB_IPNETROW *parpentry);

/**
 * @brief Delete an ARP entry from the ARP table on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL DeleteIpNetEntry(MIB_IPNETROW *parpentry);

/**
 * @brief Delete all ARP entries for the specified interface from the ARP table on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL FlushIpNetTable(uint32_t dwifindex);

/**
 * @brief Create a Proxy Address Resolution Protocol (PARP) entry on the local computer for the specified IPv4 address
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL CreateProxyArpEntry(uint32_t dwaddress, uint32_t dwmask, uint32_t dwifindex);

/**
 * @brief Delete the PARP entry on the local computer specified by the dwAddress and dwIfIndex parameters
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL DeleteProxyArpEntry(uint32_t dwaddress, uint32_t dwmask, uint32_t dwifindex);

/**
 * @brief Set the state of a TCP connection
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL SetTcpEntry(MIB_TCPROW *ptcprow);

/**
 * @brief Obtain the list of the network interface adapters with IPv4 enabled on the local system
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetInterfaceInfo(IP_INTERFACE_INFO *piftable, uint32_t *dwoutbuflen);

/**
 * @brief Retrieve information about the unidirectional adapters installed on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetUniDirectionalAdapterInfo(IP_UNIDIRECTIONAL_ADAPTER_ADDRESS *pipifinfo, uint32_t *dwoutbuflen);

/**
 * @brief Retrieve the index of the interface that has the best route to the specified IPv4 address
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetBestInterface(IP_ADDR dwdestaddr, uint32_t *pdwbestifindex);

/**
 * @brief Retrieve the best route to the specified destination IP address
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetBestRoute(uint32_t dwdestaddr, uint32_t dwsourceaddr, MIB_IPFORWARDROW *pbestroute);

/**
 * @brief Cause a notification to be sent to the caller whenever a change occurs in the table that maps IPv4 addresses to interfaces
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL NotifyAddrChange(HANDLE *handle, OVERLAPPED *overlapped);

/**
 * @brief Cause a notification to be sent to the caller whenever a change occurs in the IPv4 routing table
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL NotifyRouteChange(HANDLE *handle, OVERLAPPED *overlapped);

/**
 * @brief Obtain the index of an adapter, given its name
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetAdapterIndex(WCHAR *adaptername, uint32_t *ifindex);

/**
 * @brief Add the specified IPv4 address to the specified adapter
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL AddIPAddress(IP_ADDR address, IP_MASK ipmask, uint32_t ifindex, uint32_t *ntecontext, uint32_t *nteinstance);

/**
 * @brief Delete an IP address previously added using AddIPAddress
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL DeleteIPAddress(uint32_t ntecontext);

/**
 * @brief Retrieve network parameters for the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetNetworkParams(FIXED_INFO *pfixedinfo, uint32_t *poutbuflen);

/**
 * @brief Retrieve adapter information for the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetAdaptersInfo(IP_ADAPTER_INFO *padapterinfo, uint32_t *poutbuflen);

/**
 * @brief Retrieve information about the adapter corresponding to the specified interface
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetPerAdapterInfo(uint32_t ifindex, IP_PER_ADAPTER_INFO *pperadapterinfo, uint32_t *poutbuflen);

/**
 * @brief Release an IPv4 address previously obtained through the Dynamic Host Configuration Protocol (DHCP)
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL IpReleaseAddress(IP_ADAPTER_INDEX_MAP *adapterinfo);

/**
 * @brief Renew a lease on an IPv4 address previously obtained through Dynamic Host Configuration Protocol (DHCP)
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL IpRenewAddress(IP_ADAPTER_INDEX_MAP *adapterinfo);

/**
 * @brief Sends an Address Resolution Protocol (ARP) request to obtain the physical address that corresponds to the specified destination IPv4 address
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL SendARP(IP_ADDR *destip, IP_ADDR *srcip, DWORD *pmacaddr, uint32_t *phyaddrlen);

/**
 * @brief Determine the round-trip time (RTT) and hop count to the specified destination
 * See the Windows IP Helper documentation for additional information
 */
BOOL STDCALL GetRTTAndHopCount(IP_ADDR destipaddress, uint32_t *hopcount, uint32_t maxhops, uint32_t *rtt);

/**
 * @brief Take an interface index and return a backward-compatible interface index
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL GetFriendlyIfIndex(uint32_t ifindex);

/**
 * @brief Turn on IPv4 forwarding on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL EnableRouter(HANDLE *phandle, OVERLAPPED *poverlapped);

/**
 * @brief Turn off IPv4 forwarding on the local computer
 * See the Windows IP Helper documentation for additional information
 */
uint32_t STDCALL UnenableRouter(OVERLAPPED *poverlapped, DWORD *lpdwenablecount);

/** IP Helper Helper Functions */
uint32_t STDCALL MIBIFOperStatusToString(uint32_t value, char *string, uint32_t len);
uint32_t STDCALL MIBIFTypeToString(uint32_t value, char *string, uint32_t len);
uint32_t STDCALL MIBIFAdminStatusToString(uint32_t value, char *string, uint32_t len);

uint32_t STDCALL MIBTCPRTOToString(uint32_t value, char *string, uint32_t len);
uint32_t STDCALL MIBTCPStateToString(uint32_t value, char *string, uint32_t len);

uint32_t STDCALL MIBIPForwardingToString(uint32_t value, char *string, uint32_t len);
uint32_t STDCALL MIBIPRouteTypeToString(uint32_t value, char *string, uint32_t len);
uint32_t STDCALL MIBIPProtoToString(uint32_t value, char *string, uint32_t len);
uint32_t STDCALL MIBIPNetTypeToString(uint32_t value, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_IPHLPAPI_H