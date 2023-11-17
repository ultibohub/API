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
#ifndef _ULTIBO_WINSOCK_H
#define _ULTIBO_WINSOCK_H

#define _WINSOCKAPI_

/* Note: To use winsock.h either include it before sys/types.h */
/* Note: or add the following define before sys/types.h is included */
/* #define __USE_W32_SOCKETS */

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/ultibo.h"

/* ============================================================================== */
/* Remove any socket definitions set by sys/types.h */
#ifdef _SYS_TYPES_FD_SET
#undef _SYS_TYPES_FD_SET
#undef NBBY
#undef NFDBITS
#undef fd_set
#undef FD_SET
#undef FD_CLR
#undef FD_ISSET
#undef FD_ZERO
#endif

/* ============================================================================== */
/* Winsock specific constants */
#define WINSOCK_VERSION	0x0101

#define FD_SETSIZE	64

#define IOCPARM_MASK	0x7f
#define IOC_VOID	0x20000000
#define IOC_OUT	0x40000000
#define IOC_IN	0x80000000
#define IOC_INOUT	(IOC_IN | IOC_OUT)

#define _IO(x,y)        (IOC_VOID|((x)<<8)|(y))

#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define FIONREAD    _IOR('f', 127, u_long) // get # bytes to read */
#define FIONBIO     _IOW('f', 126, u_long) // set/clear non-blocking i/o */
#define FIOASYNC    _IOW('f', 125, u_long) // set/clear async i/o */

/* Socket I/O Controls */
#define SIOCSHIWAT  _IOW('s',  0, u_long)  // set high watermark
#define SIOCGHIWAT  _IOR('s',  1, u_long)  // get high watermark
#define SIOCSLOWAT  _IOW('s',  2, u_long)  // set low watermark
#define SIOCGLOWAT  _IOR('s',  3, u_long)  // get low watermark
#define SIOCATMARK  _IOR('s',  7, u_long)  // at oob mark?

/*  Protocols  */
#define IPPROTO_IP	0 //  dummy for IP
#define IPPROTO_ICMP	1 //  control message protocol
#define IPPROTO_IGMP	2 //  group management protocol
#define IPPROTO_GGP	3 //  gateway^2 (deprecated)
#define IPPROTO_TCP	6 //  tcp
#define IPPROTO_EGP	8 //  egp
#define IPPROTO_PUP	12 //  pup
#define IPPROTO_UDP	17 //  user datagram protocol
#define IPPROTO_HMP	20 //  hmp
#define IPPROTO_IDP	22 //  xns idp
#define IPPROTO_RDP	27 //  rdp
#define IPPROTO_IPV6	41 //  IP6 header
#define IPPROTO_ROUTING	43 //  IP6 routing header
#define IPPROTO_FRAGMENT	44 //  IP6 fragmentation header
#define IPPROTO_ICMPV6	58 //  ICMP6
#define IPPROTO_RVD	66 //  rvd
#define IPPROTO_ND	77 //  UNOFFICIAL net disk proto
#define IPPROTO_RAW	255 //  raw IP packet
#define IPPROTO_MAX	256

#define NSPROTO_IPX	1000 //  ipx protocol
#define NSPROTO_SPX	1256 //  spx protocol
#define NSPROTO_SPXII	1257 //  spxii protocol

/*  Port/socket numbers: network standard functions */
#define IPPORT_ANY	0
#define IPPORT_ECHO	7
#define IPPORT_DISCARD	9
#define IPPORT_SYSTAT	11
#define IPPORT_DAYTIME	13
#define IPPORT_NETSTAT	15
#define IPPORT_FTP	21
#define IPPORT_TELNET	23
#define IPPORT_SMTP	25
#define IPPORT_TIMESERVER	37
#define IPPORT_NAMESERVER	42
#define IPPORT_WHOIS	43
#define IPPORT_DNS	53
#define IPPORT_MTP	57
#define IPPORT_BOOTPS	67
#define IPPORT_BOOTPC	68

/*  Port/socket numbers: host specific functions  */
#define IPPORT_TFTP	69
#define IPPORT_RJE	77
#define IPPORT_FINGER	79
#define IPPORT_TTYLINK	87
#define IPPORT_SUPDUP	95

/*  UNIX TCP sockets  */
#define IPPORT_EXECSERVER	512
#define IPPORT_LOGINSERVER	513
#define IPPORT_CMDSERVER	514
#define IPPORT_EFSSERVER	520

/*  UNIX UDP sockets  */
#define IPPORT_BIFFUDP	512
#define IPPORT_WHOSERVER	513
#define IPPORT_ROUTESERVER	520

/*  Ports < IPPORT_RESERVED are reserved for
privileged processes (e.g. root).  */
#define IPPORT_RESERVED	1024

/*  Link numbers  */
#define IMPLINK_IP	155
#define IMPLINK_LOWEXPER	156
#define IMPLINK_HIGHEXPER	158

#define INADDR_ANY	0x00000000
#define INADDR_LOOPBACK	0x7F000001
#define INADDR_BROADCAST	0xFFFFFFFF
#define INADDR_NONE	0xFFFFFFFF

#define IN_CLASSA_NET	0xff000000
#define IN_CLASSA_NSHIFT	24
#define IN_CLASSA_HOST	0x00ffffff
#define IN_CLASSA_MAX	128
#define IN_CLASSB_NET	0xffff0000
#define IN_CLASSB_NSHIFT	16
#define IN_CLASSB_HOST	0x0000ffff
#define IN_CLASSB_MAX	65536
#define IN_CLASSC_NET	0xffffff00
#define IN_CLASSC_NSHIFT	8
#define IN_CLASSC_HOST	0x000000ff

#define WSADESCRIPTION_LEN	256
#define WSASYS_STATUS_LEN	128

#define TF_DISCONNECT	0x01
#define TF_REUSE_SOCKET	0x02
#define TF_WRITE_BEHIND	0x04

/*  Options for use with [gs]etsockopt at the IP level.  */
#define IP_OPTIONS	1
#define IP_MULTICAST_IF	2 //  set/get IP multicast interface
#define IP_MULTICAST_TTL	3 //  set/get IP multicast timetolive
#define IP_MULTICAST_LOOP	4 //  set/get IP multicast loopback
#define IP_ADD_MEMBERSHIP	5 //  add  an IP group membership
#define IP_DROP_MEMBERSHIP	6 //  drop an IP group membership
#define IP_TTL	7 //  set/get IP Time To Live
#define IP_TOS	8 //  set/get IP Type Of Service
#define IP_DONTFRAGMENT	9 //  set/get IP Don't Fragment flag
#define IP_HDRINCL	10 //  set/get IP Header include

#define IP_DEFAULT_MULTICAST_TTL	1 //  normally limit m'casts to 1 hop
#define IP_DEFAULT_MULTICAST_LOOP	1 //  normally hear sends if a member
#define IP_MAX_MEMBERSHIPS	20 //  per socket; must fit in one mbuf

/*  This is used instead of -1, since the SOCKET type is unsigned. */
#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCKET_ERROR	-1

/*  Types  */
#define SOCK_UNSPEC	0 //  unspecified
#define SOCK_STREAM	1 //  stream socket
#define SOCK_DGRAM	2 //  datagram socket
#define SOCK_RAW	3 //  raw-protocol interface
#define SOCK_RDM	4 //  reliably-delivered message
#define SOCK_SEQPACKET	5 //  sequenced packet stream
#define SOCK_PACKET	10 //  linux specific way of
                       //  getting packets at the dev
                       //  level.  For writing rarp and
                       //  other similar things on the
                       //  user level.

/*  Option flags per-socket.  */
#define SO_DEBUG	0x0001 //  turn on debugging info recording
#define SO_ACCEPTCONN	0x0002 //  socket has had listen()
#define SO_REUSEADDR	0x0004 //  allow local address reuse
#define SO_KEEPALIVE	0x0008 //  keep connections alive
#define SO_DONTROUTE	0x0010 //  just use interface addresses
#define SO_BROADCAST	0x0020 //  permit sending of broadcast msgs
#define SO_USELOOPBACK	0x0040 //  bypass hardware when possible
#define SO_LINGER	0x0080 //  linger on close if data present
#define SO_OOBINLINE	0x0100 //  leave received OOB data in line

#define SO_DONTLINGER	0xff7f

/*  Additional options.  */
#define SO_SNDBUF	0x1001 //  send buffer size
#define SO_RCVBUF	0x1002 //  receive buffer size
#define SO_SNDLOWAT	0x1003 //  send low-water mark
#define SO_RCVLOWAT	0x1004 //  receive low-water mark
#define SO_SNDTIMEO	0x1005 //  send timeout
#define SO_RCVTIMEO	0x1006 //  receive timeout
#define SO_ERROR	0x1007 //  get error status and clear
#define SO_TYPE	0x1008 //  get socket type
#define SO_CONNTIMEO	0x1009 //  connection timeout

/*  Options for connect and disconnect data and options.  Used only by
non-TCP/IP transports such as DECNet, OSI TP4, etc.  */
#define SO_CONNDATA	0x7000
#define SO_CONNOPT	0x7001
#define SO_DISCDATA	0x7002
#define SO_DISCOPT	0x7003
#define SO_CONNDATALEN	0x7004
#define SO_CONNOPTLEN	0x7005
#define SO_DISCDATALEN	0x7006
#define SO_DISCOPTLEN	0x7007

/*  Option for opening sockets for synchronous access.  */
#define SO_OPENTYPE	0x7008
#define SO_SYNCHRONOUS_ALERT	0x10
#define SO_SYNCHRONOUS_NONALERT	0x20

/*  Other NT-specific options.  */
#define SO_MAXDG	0x7009
#define SO_MAXPATHDG	0x700A
#define SO_UPDATE_ACCEPT_CONTEXT	0x700B
#define SO_CONNECT_TIME	0x700C

/*  TCP options.  */
#define TCP_NODELAY	0x0001
#define TCP_MAXSEG	0x0002
#define TCP_NOPUSH	0x0004
#define TCP_NOOPT	0x0008
#define TCP_BSDURGENT	0x7000 // Implement BSD Urgent instead of RFC793/1122

#define TCP_WSCALE	0x0010
#define TCP_NOSACK	0x0020

/*  UDP options.  */
#define UDP_NOCHECKSUM	0x0001

/*  Address families.  */
#define AF_UNSPEC	0 //  unspecified
#define AF_UNIX	1 //  local to host (pipes, portals)
#define AF_INET	2 //  internetwork: UDP, TCP, etc.
#define AF_IMPLINK	3 //  arpanet imp addresses
#define AF_PUP	4 //  pup protocols: e.g. BSP
#define AF_CHAOS	5 //  mit CHAOS protocols
#define AF_IPX	6 //  IPX and SPX
#define AF_NS	6 //  XEROX NS protocols
#define AF_ISO	7 //  ISO protocols
#define AF_OSI	AF_ISO //  OSI is ISO
#define AF_ECMA	8 //  european computer manufacturers
#define AF_DATAKIT	9 //  datakit protocols
#define AF_CCITT	10 //  CCITT protocols, X.25 etc
#define AF_SNA	11 //  IBM SNA
#define AF_DECnet	12 //  DECnet
#define AF_DLI	13 //  Direct data link interface
#define AF_LAT	14 //  LAT
#define AF_HYLINK	15 //  NSC Hyperchannel
#define AF_APPLETALK	16 //  AppleTalk
#define AF_NETBIOS	17 //  NetBios-style addresses
#define AF_VOICEVIEW	18 //  VoiceView
#define AF_FIREFOX	19 //  FireFox
#define AF_UNKNOWN1	20 //  Somebody is using this!
#define AF_BAN	21 //  Banyan
#define AF_ATM	22 //  Native ATM Services
#define AF_INET6	23 //  Internetwork Version 6
#define AF_CLUSTER	24 //  Microsoft Wolfpack
#define AF_12844	25 //  IEEE 1284.4 WG AF
#define AF_IRDA	26 //  IrDA
#define AF_NETDES	28 //  Network Designers OSI & gateway enabled

#define AF_MAX	29

/*  Protocol families, same as address families for now.  */
#define PF_UNSPEC	AF_UNSPEC
#define PF_UNIX	AF_UNIX
#define PF_INET	AF_INET
#define PF_IMPLINK	AF_IMPLINK
#define PF_PUP	AF_PUP
#define PF_CHAOS	AF_CHAOS
#define PF_NS	AF_NS
#define PF_IPX	AF_IPX
#define PF_ISO	AF_ISO
#define PF_OSI	AF_OSI
#define PF_ECMA	AF_ECMA
#define PF_DATAKIT	AF_DATAKIT
#define PF_CCITT	AF_CCITT
#define PF_SNA	AF_SNA
#define PF_DECnet	AF_DECnet
#define PF_DLI	AF_DLI
#define PF_LAT	AF_LAT
#define PF_HYLINK	AF_HYLINK
#define PF_APPLETALK	AF_APPLETALK
#define PF_VOICEVIEW	AF_VOICEVIEW
#define PF_FIREFOX	AF_FIREFOX
#define PF_UNKNOWN1	AF_UNKNOWN1
#define PF_BAN	AF_BAN
#define PF_ATM	AF_ATM
#define PF_INET6	AF_INET6
#define PF_CLUSTER	AF_CLUSTER
#define PF_12844	AF_12844
#define PF_IRDA	AF_IRDA
#define PF_NETDES	AF_NETDES

#define PF_MAX	AF_MAX

/*  Level number for (get/set)sockopt() to apply to socket itself.  */
#define SOL_SOCKET	0xffff // options for socket level

/*  Maximum queue length specifiable by listen.  */
#define SOMAXCONN	5

#define MSG_OOB	0x1 // process out-of-band data
#define MSG_PEEK	0x2 // peek at incoming message
#define MSG_DONTROUTE	0x4 // send without using routing tables

#define MSG_INTERRUPT	0x10 // send/recv in the interrupt context
#define MSG_MAXIOVLEN	16

#define MSG_PARTIAL	0x8000 // partial send or recv for message xport

/*  Define constant based on rfc883, used by gethostbyxxxx() calls.  */
#define MAXGETHOSTSTRUCT	1024

/*  Define flags to be used with the WSAAsyncSelect() call.  */
#define FD_READ	0x01
#define FD_WRITE	0x02
#define FD_OOB	0x04
#define FD_ACCEPT	0x08
#define FD_CONNECT	0x10
#define FD_CLOSE	0x20

/*  All Windows Sockets error constants are biased by WSABASEERR from the "normal" */
#define WSABASEERR	10000

/*  Windows Sockets definitions of regular Microsoft C error constants  */

#define WSAEINTR	(WSABASEERR+4)
#define WSAEBADF	(WSABASEERR+9)
#define WSAEACCES	(WSABASEERR+13)
#define WSAEFAULT	(WSABASEERR+14)
#define WSAEINVAL	(WSABASEERR+22)
#define WSAEMFILE	(WSABASEERR+24)

/*  Windows Sockets definitions of regular Berkeley error constants  */

#define WSAEWOULDBLOCK	(WSABASEERR+35)
#define WSAEINPROGRESS	(WSABASEERR+36)
#define WSAEALREADY	(WSABASEERR+37)
#define WSAENOTSOCK	(WSABASEERR+38)
#define WSAEDESTADDRREQ	(WSABASEERR+39)
#define WSAEMSGSIZE	(WSABASEERR+40)
#define WSAEPROTOTYPE	(WSABASEERR+41)
#define WSAENOPROTOOPT	(WSABASEERR+42)
#define WSAEPROTONOSUPPORT	(WSABASEERR+43)
#define WSAESOCKTNOSUPPORT	(WSABASEERR+44)
#define WSAEOPNOTSUPP	(WSABASEERR+45)
#define WSAEPFNOSUPPORT	(WSABASEERR+46)
#define WSAEAFNOSUPPORT	(WSABASEERR+47)
#define WSAEADDRINUSE	(WSABASEERR+48)
#define WSAEADDRNOTAVAIL	(WSABASEERR+49)
#define WSAENETDOWN	(WSABASEERR+50)
#define WSAENETUNREACH	(WSABASEERR+51)
#define WSAENETRESET	(WSABASEERR+52)
#define WSAECONNABORTED	(WSABASEERR+53)
#define WSAECONNRESET	(WSABASEERR+54)
#define WSAENOBUFS	(WSABASEERR+55)
#define WSAEISCONN	(WSABASEERR+56)
#define WSAENOTCONN	(WSABASEERR+57)
#define WSAESHUTDOWN	(WSABASEERR+58)
#define WSAETOOMANYREFS	(WSABASEERR+59)
#define WSAETIMEDOUT	(WSABASEERR+60)
#define WSAECONNREFUSED	(WSABASEERR+61)
#define WSAELOOP	(WSABASEERR+62)
#define WSAENAMETOOLONG	(WSABASEERR+63)
#define WSAEHOSTDOWN	(WSABASEERR+64)
#define WSAEHOSTUNREACH	(WSABASEERR+65)
#define WSAENOTEMPTY	(WSABASEERR+66)
#define WSAEPROCLIM	(WSABASEERR+67)
#define WSAEUSERS	(WSABASEERR+68)
#define WSAEDQUOT	(WSABASEERR+69)
#define WSAESTALE	(WSABASEERR+70)
#define WSAEREMOTE	(WSABASEERR+71)

#define WSAEDISCON	(WSABASEERR+101)

/*  Extended Windows Sockets error constant definitions  */

#define WSASYSNOTREADY	(WSABASEERR+91)
#define WSAVERNOTSUPPORTED	(WSABASEERR+92)
#define WSANOTINITIALISED	(WSABASEERR+93)

#define WSAENOMORE	(WSABASEERR+102)
#define WSAECANCELLED	(WSABASEERR+103)
#define WSAEINVALIDPROCTABLE	(WSABASEERR+104)
#define WSAEINVALIDPROVIDER	(WSABASEERR+105)
#define WSAEPROVIDERFAILEDINIT	(WSABASEERR+106)
#define WSASYSCALLFAILURE	(WSABASEERR+107)
#define WSASERVICE_NOT_FOUND	(WSABASEERR+108)
#define WSATYPE_NOT_FOUND	(WSABASEERR+109)
#define WSA_E_NO_MORE	(WSABASEERR+110)
#define WSA_E_CANCELLED	(WSABASEERR+111)
#define WSAEREFUSED	(WSABASEERR+112)

/*  Error return codes from gethostbyname() and gethostbyaddr()
(when using the resolver). Note that these errors are
retrieved via WSAGetLastError() and must therefore follow
the rules for avoiding clashes with error numbers from
specific implementations or language run-time systems.
For this reason the codes are based at WSABASEERR+1001.
Note also that [WSA]NO_ADDRESS is defined only for
compatibility purposes.  */

/*  Authoritative Answer: Host not found  */

#define WSAHOST_NOT_FOUND	(WSABASEERR+1001)
#define HOST_NOT_FOUND	WSAHOST_NOT_FOUND

/*  Non-Authoritative: Host not found, or SERVERFAIL  */

#define WSATRY_AGAIN	(WSABASEERR+1002)
#define TRY_AGAIN	WSATRY_AGAIN

/*  Non recoverable errors, FORMERR, REFUSED, NOTIMP  */

#define WSANO_RECOVERY	(WSABASEERR+1003)
#define NO_RECOVERY	WSANO_RECOVERY

/*  Valid name, no data record of requested type  */

#define WSANO_DATA	(WSABASEERR+1004)
#define NO_DATA	WSANO_DATA

/*  no address, look for MX record  */

#define WSANO_ADDRESS	WSANO_DATA
#define NO_ADDRESS	WSANO_ADDRESS

/*  Windows Sockets errors redefined as regular Berkeley error constants.
These are commented out in Windows NT to avoid conflicts with errno.h.
Use the WSA constants instead.  */

#define EWOULDBLOCK	WSAEWOULDBLOCK
#define EINPROGRESS	WSAEINPROGRESS
#define EALREADY	WSAEALREADY
#define ENOTSOCK	WSAENOTSOCK
#define EDESTADDRREQ	WSAEDESTADDRREQ
#define EMSGSIZE	WSAEMSGSIZE
#define EPROTOTYPE	WSAEPROTOTYPE
#define ENOPROTOOPT	WSAENOPROTOOPT
#define EPROTONOSUPPORT	WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT	WSAESOCKTNOSUPPORT
#define EOPNOTSUPP	WSAEOPNOTSUPP
#define EPFNOSUPPORT	WSAEPFNOSUPPORT
#define EAFNOSUPPORT	WSAEAFNOSUPPORT
#define EADDRINUSE	WSAEADDRINUSE
#define EADDRNOTAVAIL	WSAEADDRNOTAVAIL
#define ENETDOWN	WSAENETDOWN
#define ENETUNREACH	WSAENETUNREACH
#define ENETRESET	WSAENETRESET
#define ECONNABORTED	WSAECONNABORTED
#define ECONNRESET	WSAECONNRESET
#define ENOBUFS	WSAENOBUFS
#define EISCONN	WSAEISCONN
#define ENOTCONN	WSAENOTCONN
#define ESHUTDOWN	WSAESHUTDOWN
#define ETOOMANYREFS	WSAETOOMANYREFS
#define ETIMEDOUT	WSAETIMEDOUT
#define ECONNREFUSED	WSAECONNREFUSED
#define ELOOP	WSAELOOP
#define ENAMETOOLONG	WSAENAMETOOLONG
#define EHOSTDOWN	WSAEHOSTDOWN
#define EHOSTUNREACH	WSAEHOSTUNREACH
#define ENOTEMPTY	WSAENOTEMPTY
#define EPROCLIM	WSAEPROCLIM
#define EUSERS	WSAEUSERS
#define EDQUOT	WSAEDQUOT
#define ESTALE	WSAESTALE
#define EREMOTE	WSAEREMOTE

#define ENOTREADY	WSASYSNOTREADY
#define EVERNOTSUPPORTED	WSAVERNOTSUPPORTED
#define ENOTINITIALISED	WSANOTINITIALISED

/* ============================================================================== */
/* Global Socket types */
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

typedef char MBChar;

typedef struct _fd_set
{
	u_int fd_count;
	SOCKET fd_array[FD_SETSIZE];
} fd_set;

typedef struct _timeval
{
	int32_t tv_sec;
	int32_t tv_usec;
} timeval;

typedef struct _hostent
{
	char *h_name;
	char **h_aliases;
	int16_t h_addrtype;
	int16_t h_length;
	char **h_addr_list;
} hostent;

typedef struct _netent
{
	char *n_name;
	char **n_aliases;
	int16_t n_addrtype;
	u_long n_net;
} netent;

typedef struct _servent
{
	char *s_name;
	char **s_aliases;
	int16_t s_port;
	char *s_proto;
} servent;

typedef struct _protoent
{
	char *p_name;
	char **p_aliases;
	int16_t p_proto;
} protoent;

typedef struct _in_addr
{
	union
	{
		struct { u_char s_b1,s_b2,s_b3,s_b4; } S_un_b;
		struct { u_short s_w1,s_w2; } S_un_w;
		u_long S_addr;
        u_char S_bytes[4];
	} S_un;
#define s_addr  S_un.S_addr
} in_addr;

typedef struct _sockaddr_in
{
	u_short sin_family;
	u_short sin_port;
	in_addr sin_addr;
	char sin_zero[8];
} sockaddr_in;

typedef struct _WSADATA
{
	uint16_t wversion;
	uint16_t whighversion;
	char szdescription[WSADESCRIPTION_LEN + 1];
	char szsystemstatus[WSASYS_STATUS_LEN + 1];
	uint16_t imaxsockets;
	uint16_t imaxudpdg;
	char *lpvendorinfo;
} WSADATA;

typedef struct _TRANSMIT_FILE_BUFFERS
{
	void *head;
	uint32_t headlength;
	void *tail;
	uint32_t taillength;
} TRANSMIT_FILE_BUFFERS;

/*  Structure used by kernel to store most addresses.  */
typedef struct _sockaddr
{
	u_short sa_family;    // address family
	char    sa_data[14];  // up to 14 bytes of direct address
} sockaddr;

typedef struct sockaddr SOCKADDR;

/*  Structure used by kernel to pass protocol information in raw sockets.  */
typedef struct _sockproto
{
	u_short sp_family;
	u_short sp_protocol;
} sockproto;

/*  Structure used for manipulating linger option.  */
typedef struct _linger
{
	u_short l_onoff;
	u_short l_linger;
} linger;

/* Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP */
typedef struct _ip_mreq
{
	in_addr imrmultiaddr; // IP multicast address of group
	in_addr imrinterface; // local IP address of interface
} ip_mreq;

/* ============================================================================== */
/* Initialization Functions */
BOOL STDCALL WSStart(void);
BOOL STDCALL WSStop(void);

void STDCALL WSAsyncStart(void *data);

/* ============================================================================== */
/* Winsock Functions */
SOCKET STDCALL accept(SOCKET s, SOCKADDR *addr, int *addrlen);
int STDCALL bind(SOCKET s, SOCKADDR *addr, int namelen);
int STDCALL closesocket(SOCKET s);
int STDCALL connect(SOCKET s, SOCKADDR *name, int namelen);
int STDCALL ioctlsocket(SOCKET s, int32_t cmd, u_long *arg);
int STDCALL getpeername(SOCKET s, SOCKADDR *name, int *namelen);
int STDCALL getsockname(SOCKET s, SOCKADDR *name, int *namelen);
int STDCALL getsockopt(SOCKET s, int level, int optname, char *optval, int *optlen);
u_long STDCALL htonl(u_long hostlong);
u_short STDCALL htons(u_short hostshort);
u_long STDCALL inet_addr(char *cp);
char * STDCALL inet_ntoa(in_addr inaddr);
int STDCALL listen(SOCKET s, int backlog);
u_long STDCALL ntohl(u_long netlong);
u_short STDCALL ntohs(u_short netshort);
int STDCALL recv(SOCKET s, char *buf, int len, int flags);
int STDCALL recvfrom(SOCKET s, char *buf, int len, int flags, SOCKADDR *from, int *fromlen);
int STDCALL select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, timeval *timeout);
int STDCALL send(SOCKET s, char *buf, int len, int flags);
int STDCALL sendto(SOCKET s, char *buf, int len, int flags, SOCKADDR *toaddr, int tolen);
int STDCALL setsockopt(SOCKET s, int level, int optname, char *optval, int optlen);
int STDCALL shutdown(SOCKET s, int how);
SOCKET STDCALL socket(int af, int type, int protocol);

hostent * STDCALL gethostbyaddr(char *addr, int len, int family);
hostent * STDCALL gethostbyname(char *name);
int STDCALL gethostname(char *name, int namelen);
servent * STDCALL getservbyport(int port, char *proto);
servent * STDCALL getservbyname(char *name, char *proto);
protoent * STDCALL getprotobynumber(int proto);
protoent * STDCALL getprotobyname(char *name);

int STDCALL WSAStartup(uint16_t wversionrequired, WSADATA *wsadata);
int STDCALL WSACleanup(void);
void STDCALL WSASetLastError(int ierror);
int STDCALL WSAGetLastError(void);
BOOL STDCALL WSAIsBlocking(void);
int STDCALL WSAUnhookBlockingHook(void);
FARPROC STDCALL WSASetBlockingHook(FARPROC lpblockfunc);
int STDCALL WSACancelBlockingCall(void);
HANDLE STDCALL WSAAsyncGetServByName(HWND hwnd, u_int wmsg, char *name, char *proto, char *buf, int buflen);
HANDLE STDCALL WSAAsyncGetServByPort(HWND hwnd, u_int wmsg, int port, char *proto, char *buf, int buflen);
HANDLE STDCALL WSAAsyncGetProtoByName(HWND hwnd, u_int wmsg, char *name, char *buf, int buflen);
HANDLE STDCALL WSAAsyncGetProtoByNumber(HWND hwnd, u_int wmsg, int number, char *buf, int buflen);
HANDLE STDCALL WSAAsyncGetHostByName(HWND hwnd, u_int wmsg, char *name, char *buf, int buflen);
HANDLE STDCALL WSAAsyncGetHostByAddr(HWND hwnd, u_int wmsg, char *addr, int len, int family, char *buf, int buflen);
int STDCALL WSACancelAsyncRequest(HANDLE hasynctaskhandle);
int STDCALL WSAAsyncSelect(SOCKET s, HWND hwnd, u_int wmsg, int32_t levent);
int STDCALL WSARecvEx(SOCKET s, char *buf, int len, int *flags);
BOOL STDCALL __WSAFDIsSet(SOCKET s, fd_set *fdset);
int STDCALL __WSAFDIsSet_(SOCKET s, fd_set *fdset);

BOOL STDCALL TransmitFile(SOCKET hsocket, HANDLE hfile, uint32_t nnumberofbytestowrite, uint32_t nnumberofbytespersend, OVERLAPPED *lpoverlapped, TRANSMIT_FILE_BUFFERS *lptransmitbuffers, uint32_t dwreserved);

BOOL STDCALL AcceptEx(SOCKET slistensocket, SOCKET sacceptsocket, void *lpoutputbuffer, uint32_t dwreceivedatalength, uint32_t dwlocaladdresslength, uint32_t dwremoteaddresslength, uint32_t *lpdwbytesreceived, OVERLAPPED *lpoverlapped);

void STDCALL GetAcceptExSockaddrs(void *lpoutputbuffer, uint32_t dwreceivedatalength, uint32_t dwlocaladdresslength, uint32_t dwremoteaddresslength, SOCKADDR **localsockaddr, int *localsockaddrlength, SOCKADDR **remotesockaddr, int *remotesockaddrlength);

uint32_t STDCALL WSAMakeSyncReply(uint16_t buflen, uint16_t error);
uint32_t STDCALL WSAMakeSelectReply(uint16_t event, uint16_t error);
uint16_t STDCALL WSAGetAsyncBuflen(uint32_t param);
uint16_t STDCALL WSAGetAsyncError(uint32_t param);
uint16_t STDCALL WSAGetSelectEvent(uint32_t param);
uint16_t STDCALL WSAGetSelectError(uint32_t param);

void STDCALL FD_CLR(SOCKET socket, fd_set *fdset);
BOOL STDCALL FD_ISSET(SOCKET socket, fd_set *fdset);
void STDCALL FD_SET(SOCKET socket, fd_set *fdset);
void STDCALL FD_ZERO(fd_set *fdset);

/* ============================================================================== */
/* Winsock Undocumented Functions */
int STDCALL WsControl(uint32_t proto, uint32_t action, void *prequestinfo, uint32_t *pcbrequestinfolen, void *presponseinfo, uint32_t *pcbresponseinfolen);

netent * STDCALL getnetbyaddr(void *addr, int len, int type);
netent * STDCALL getnetbyname(char *name);

/* ============================================================================== */
/* Winsock Enhanced Functions */
int STDCALL WsControlEx(uint32_t proto, uint32_t action, void *prequestinfo, uint32_t *pcbrequestinfolen, void *presponseinfo, uint32_t *pcbresponseinfolen);

/* ============================================================================== */
/* Winsock Helper Functions */
BOOL STDCALL WinsockRedirectInput(SOCKET s);
BOOL STDCALL WinsockRedirectOutput(SOCKET s);

uint32_t STDCALL WinsockErrorToString(int32_t error, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_WINSOCK_H