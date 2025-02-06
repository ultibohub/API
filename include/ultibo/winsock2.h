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
#ifndef _ULTIBO_WINSOCK2_H
#define _ULTIBO_WINSOCK2_H

#define _ULTIBO_WINSOCK_H // Prevent inclusion of winsock.h
#define _WINSOCK2API_
#define _WINSOCKAPI_

/* Note: To use winsock2.h either include it before sys/types.h */
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
/* Winsock2 specific constants */
#define WINSOCK_VERSION	0x0202

#ifndef FD_SETSIZE
#define FD_SETSIZE	64
#endif

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
#define SOMAXCONN	0x7fffffff

#define MSG_OOB	0x1 // process out-of-band data
#define MSG_PEEK	0x2 // peek at incoming message
#define MSG_DONTROUTE	0x4 // send without using routing tables

#define MSG_INTERRUPT	0x10 // send/recv in the interrupt context
#define MSG_MAXIOVLEN	16

#define MSG_PARTIAL	0x8000 // partial send or recv for message xport

/*  Define constant based on rfc883, used by gethostbyxxxx() calls.  */
#define MAXGETHOSTSTRUCT	1024

/*  WinSock 2 extension -- bit values and indices for FD_XXX network events  */
#define FD_READ_BIT	0
#define FD_READ	(1  <<  FD_READ_BIT)
#define FD_WRITE_BIT	1
#define FD_WRITE	(1  <<  FD_WRITE_BIT)
#define FD_OOB_BIT	2
#define FD_OOB	(1  <<  FD_OOB_BIT)
#define FD_ACCEPT_BIT	3
#define FD_ACCEPT	(1  <<  FD_ACCEPT_BIT)
#define FD_CONNECT_BIT	4
#define FD_CONNECT	(1  <<  FD_CONNECT_BIT)
#define FD_CLOSE_BIT	5
#define FD_CLOSE	(1  <<  FD_CLOSE_BIT)
#define FD_QOS_BIT	6
#define FD_QOS	(1  <<  FD_QOS_BIT)
#define FD_GROUP_QOS_BIT	7
#define FD_GROUP_QOS	(1  <<  FD_GROUP_QOS_BIT)
#define FD_MAX_EVENTS	8
#define FD_ALL_EVENTS	((1  <<  FD_MAX_EVENTS) - 1)

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

/*  WinSock 2 extension -- new error codes and type definition  */
#define WSA_IO_PENDING	ERROR_IO_PENDING
#define WSA_IO_INCOMPLETE	ERROR_IO_INCOMPLETE
#define WSA_INVALID_HANDLE	ERROR_INVALID_HANDLE
#define WSA_INVALID_PARAMETER	ERROR_INVALID_PARAMETER
#define WSA_NOT_ENOUGH_MEMORY	ERROR_NOT_ENOUGH_MEMORY
#define WSA_OPERATION_ABORTED	ERROR_OPERATION_ABORTED
#define WSA_INVALID_EVENT	(WSAEVENT)NULL
#define WSA_MAXIMUM_WAIT_EVENTS	MAXIMUM_WAIT_OBJECTS
#define WSA_WAIT_FAILED	0xffffffff
#define WSA_WAIT_EVENT_0	WAIT_OBJECT_0
#define WSA_WAIT_IO_COMPLETION	WAIT_IO_COMPLETION
#define WSA_WAIT_TIMEOUT	WAIT_TIMEOUT
#define WSA_INFINITE	INFINITE

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

#define WSADESCRIPTION_LEN	256
#define WSASYS_STATUS_LEN	128
#define MAX_PROTOCOL_CHAIN	7
#define BASE_PROTOCOL	1
#define LAYERED_PROTOCOL	0
#define WSAPROTOCOL_LEN	255

/*  WinSock 2 extension -- WSABUF and QOS struct, include qos.h to pull in FLOWSPEC and related definitions  */
#define SERVICETYPE_NOTRAFFIC	0x00000000 //  No data in this direction
#define SERVICETYPE_BESTEFFORT	0x00000001 //  Best Effort
#define SERVICETYPE_CONTROLLEDLOAD	0x00000002 //  Controlled Load
#define SERVICETYPE_GUARANTEED	0x00000003 //  Guaranteed
#define SERVICETYPE_NETWORK_UNAVAILABLE	0x00000004 //  Used to notify change to user
#define SERVICETYPE_GENERAL_INFORMATION	0x00000005 //  corresponds to "General Parameters" defined by IntServ
#define SERVICETYPE_NOCHANGE	0x00000006 //  used to indicate that the flow spec contains no change from any previous one

#define SERVICE_IMMEDIATE_TRAFFIC_CONTROL	0x80000000 //  to turn on immediate traffic control, OR this flag with the ServiceType field in teh FLOWSPEC

/*  WinSock 2 extension -- manifest constants for return values of the condition function  */
#define CF_ACCEPT	0x0000
#define CF_REJECT	0x0001
#define CF_DEFER	0x0002

/*  WinSock 2 extension -- manifest constants for shutdown()  */
#define SD_RECEIVE	0x00
#define SD_SEND	0x01
#define SD_BOTH	0x02

/*  WinSock 2 extension -- data type and manifest constants for socket groups  */
#define SG_UNCONSTRAINED_GROUP	0x01
#define SG_CONSTRAINED_GROUP	0x02

/*  Flag bit definitions for dwProviderFlags */
#define PFL_MULTIPLE_PROTO_ENTRIES	0x00000001
#define PFL_RECOMMENDED_PROTO_ENTRY	0x00000002
#define PFL_HIDDEN	0x00000004
#define PFL_MATCHES_PROTOCOL_ZERO	0x00000008

/*  Flag bit definitions for dwServiceFlags1 */
#define XP1_CONNECTIONLESS	0x00000001
#define XP1_GUARANTEED_DELIVERY	0x00000002
#define XP1_GUARANTEED_ORDER	0x00000004
#define XP1_MESSAGE_ORIENTED	0x00000008
#define XP1_PSEUDO_STREAM	0x00000010
#define XP1_GRACEFUL_CLOSE	0x00000020
#define XP1_EXPEDITED_DATA	0x00000040
#define XP1_CONNECT_DATA	0x00000080
#define XP1_DISCONNECT_DATA	0x00000100
#define XP1_SUPPORT_BROADCAST	0x00000200
#define XP1_SUPPORT_MULTIPOINT	0x00000400
#define XP1_MULTIPOINT_CONTROL_PLANE	0x00000800
#define XP1_MULTIPOINT_DATA_PLANE	0x00001000
#define XP1_QOS_SUPPORTED	0x00002000
#define XP1_INTERRUPT	0x00004000
#define XP1_UNI_SEND	0x00008000
#define XP1_UNI_RECV	0x00010000
#define XP1_IFS_HANDLES	0x00020000
#define XP1_PARTIAL_MESSAGE	0x00040000

#define BIGENDIAN	0x0000
#define LITTLEENDIAN	0x0001

#define SECURITY_PROTOCOL_NONE	0x0000

/*  WinSock 2 extension -- manifest constants for WSAJoinLeaf()  */
#define JL_SENDER_ONLY	0x01
#define JL_RECEIVER_ONLY	0x02
#define JL_BOTH	0x04

/*  WinSock 2 extension -- manifest constants for WSASocket()  */
#define WSA_FLAG_OVERLAPPED	0x01
#define WSA_FLAG_MULTIPOINT_C_ROOT	0x02
#define WSA_FLAG_MULTIPOINT_C_LEAF	0x04
#define WSA_FLAG_MULTIPOINT_D_ROOT	0x08
#define WSA_FLAG_MULTIPOINT_D_LEAF	0x10

/*  WinSock 2 extension -- manifest constants for WSAIoctl()  */
#define IOC_UNIX	0x00000000
#define IOC_WS2	0x08000000
#define IOC_PROTOCOL	0x10000000
#define IOC_VENDOR	0x18000000

#define SIO_ASSOCIATE_HANDLE	IOC_IN | IOC_WS2 | 1
#define SIO_ENABLE_CIRCULAR_QUEUEING	IOC_WS2 | 2
#define SIO_FIND_ROUTE	IOC_OUT | IOC_WS2 | 3
#define SIO_FLUSH	IOC_WS2 | 4
#define SIO_GET_BROADCAST_ADDRESS	IOC_OUT | IOC_WS2 | 5
#define SIO_GET_EXTENSION_FUNCTION_POINTER	IOC_INOUT | IOC_WS2 | 6
#define SIO_GET_QOS	IOC_INOUT | IOC_WS2 | 7
#define SIO_GET_GROUP_QOS	IOC_INOUT | IOC_WS2 | 8
#define SIO_MULTIPOINT_LOOPBACK	IOC_IN | IOC_WS2 | 9
#define SIO_MULTICAST_SCOPE	IOC_IN | IOC_WS2 | 10
#define SIO_SET_QOS	IOC_IN | IOC_WS2 | 11
#define SIO_SET_GROUP_QOS	IOC_IN | IOC_WS2 | 12
#define SIO_TRANSLATE_HANDLE	IOC_INOUT | IOC_WS2 | 13

/*  WinSock 2 extension -- manifest constants for SIO_TRANSLATE_HANDLE ioctl  */
#define TH_NETDEV	0x00000001
#define TH_TAPI	0x00000002

#define SERVICE_MULTIPLE	0x00000001

/*  Name Spaces  */
#define NS_ALL	(0)

#define NS_SAP	(1)
#define NS_NDS	(2)
#define NS_PEER_BROWSE	(3)

#define NS_TCPIP_LOCAL	(10)
#define NS_TCPIP_HOSTS	(11)
#define NS_DNS	(12)
#define NS_NETBT	(13)
#define NS_WINS	(14)

#define NS_NBP	(20)

#define NS_MS	(30)
#define NS_STDA	(31)
#define NS_NTDS	(32)

#define NS_X500	(40)
#define NS_NIS	(41)
#define NS_NISPLUS	(42)

#define NS_WRQ	(50)

/*  Resolution flags for WSAGetAddressByName() Note these are also used by the 1.1 API GetAddressByName, so leave them around.  */
#define RES_UNUSED_1	0x00000001
#define RES_FLUSH_CACHE	0x00000002
#define RES_SERVICE	0x00000004

/*  Well known value names for Service Types  */
#define SERVICE_TYPE_VALUE_IPXPORTA "IpxSocket"
#define SERVICE_TYPE_VALUE_IPXPORTW L"IpxSocket"

#define SERVICE_TYPE_VALUE_SAPIDA	"SapId"
#define SERVICE_TYPE_VALUE_SAPIDW   L"SapId"

#define SERVICE_TYPE_VALUE_TCPPORTA	"TcpPort"
#define SERVICE_TYPE_VALUE_TCPPORTW L"TcpPort"

#define SERVICE_TYPE_VALUE_UDPPORTA	"UdpPort"
#define SERVICE_TYPE_VALUE_UDPPORTW L"UdpPort"

#define SERVICE_TYPE_VALUE_OBJECTIDA	"ObjectId"
#define SERVICE_TYPE_VALUE_OBJECTIDW    L"ObjectId"

#define SERVICE_TYPE_VALUE_SAPID	SERVICE_TYPE_VALUE_SAPIDA
#define SERVICE_TYPE_VALUE_TCPPORT	SERVICE_TYPE_VALUE_TCPPORTA
#define SERVICE_TYPE_VALUE_UDPPORT	SERVICE_TYPE_VALUE_UDPPORTA
#define SERVICE_TYPE_VALUE_OBJECTID	SERVICE_TYPE_VALUE_OBJECTIDA

#define LUP_DEEP	0x0001
#define LUP_CONTAINERS	0x0002
#define LUP_NOCONTAINERS	0x0004
#define LUP_NEAREST	0x0008
#define LUP_RETURN_NAME	0x0010
#define LUP_RETURN_TYPE	0x0020
#define LUP_RETURN_VERSION	0x0040
#define LUP_RETURN_COMMENT	0x0080
#define LUP_RETURN_ADDR	0x0100
#define LUP_RETURN_BLOB	0x0200
#define LUP_RETURN_ALIASES	0x0400
#define LUP_RETURN_QUERY_STRING	0x0800
#define LUP_RETURN_ALL	0x0FF0
#define LUP_RES_SERVICE	0x8000

#define LUP_FLUSHCACHE	0x1000
#define LUP_FLUSHPREVIOUS	0x2000

/*  Return flags  */
#define RESULT_IS_ALIAS	0x0001

/* Error codes from getaddrinfo() */
#define EAI_AGAIN	WSATRY_AGAIN
#define EAI_BADFLAGS	WSAEINVAL
#define EAI_FAIL	WSANO_RECOVERY
#define EAI_FAMILY	WSAEAFNOSUPPORT
#define EAI_MEMORY	WSA_NOT_ENOUGH_MEMORY
/* EAI_NODATA   = WSANO_DATA; */
#define EAI_NONAME	WSAHOST_NOT_FOUND
#define EAI_SERVICE	WSATYPE_NOT_FOUND
#define EAI_SOCKTYPE	WSAESOCKTNOSUPPORT

#define EAI_NODATA	EAI_NONAME

/* Flags used in "hints" argument to getaddrinfo() */
/* Note: Under Linux these values may be different */
#define AI_PASSIVE	0x00000001 // Socket address will be used in bind() call
#define AI_CANONNAME	0x00000002 // Return canonical name from DNS in the first ai_canonname (Cannot be used with AI_FQDN)
#define AI_NUMERICHOST	0x00000004 // Nodename must be a numeric address string
#define AI_NUMERICSERV	0x00000008 // Servicename must be a numeric port string
#define AI_ALL	0x00000100 // Return both IPv6 and IPv4 addresses
#define AI_ADDRCONFIG	0x00000400 // Only return addresses if a global address is configured (IPv4 or IPv6), loopback addresses do not count as global
#define AI_V4MAPPED	0x00000800 // Map returned IPv4 addresses to IPv6 address format
#define AI_NON_AUTHORITATIVE	0x00004000 // Allow both autoritive and non authoritive return addresses (NS_EMAIL only)
#define AI_SECURE	0x00008000 // Obtain result using enhanced security only (NS_EMAIL only)
#define AI_RETURN_PREFERRED_NAMES	0x00010000 // Return preferred names (NS_EMAIL only)
#define AI_FQDN	0x00020000 // Return the FQDN for the single name specified on NodeName (Cannot be used with AI_CANONNAME)
#define AI_FILESERVER	0x00040000 // The requested name is being used for file sharing (Hint Only)

/* Flags for getnameinfo() */
#define NI_NOFQDN	0x01 // Only return nodename portion for local hosts
#define NI_NUMERICHOST	0x02 // Return numeric form of the host's address
#define NI_NAMEREQD	0x04 // Error if the host's name not in DNS
#define NI_NUMERICSERV	0x08 // Return numeric form of the service (port #)
#define NI_DGRAM	0x10 // Service is a datagram service

#define NI_MAXHOST	1025 // Max size of a fully-qualified domain name
#define NI_MAXSERV	32 // Max size of a service name

#define INET_ADDRSTR_ANY	"0.0.0.0"
#define INET6_ADDRSTR_INIT	"0::0"

#define INET_ADDRSTR_BROADCAST	"255.255.255.255"

#define INET_ADDRSTRLEN	16 // Max size of numeric form of IPv4 address
#define INET6_ADDRSTRLEN	46 // Max size of numeric form of IPv6 address

//#define IN6ADDR_ANY_INIT:TIn6Addr	(u6_addr16: (0, 0, 0, 0, 0, 0, 0, 0)) //To Do //Make these const
//#define IN6ADDR_LOOPBACK_INIT:TIn6Addr	(u6_addr8: (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)) //To Do //Make these const

/* ============================================================================== */
/* Winsock2 specific types */
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

typedef struct _wstimeval
{
	int32_t tv_sec;
	int32_t tv_usec;
} wstimeval;

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

/* IPv6 version of above */
typedef struct _in6_addr
{
	union
	{
		uint8_t u6_addr8[16];
		uint16_t u6_addr16[8];
		uint32_t u6_addr32[4];
		int8_t s6_addr8[16];
		int8_t s6_addr[16];
		int16_t s6_addr16[8];
		int32_t s6_addr32[4];
    };
} in6_addr;

/* IPX version of above */
typedef struct _ipx_addr
{
	uint8_t s_net[4];
	uint8_t s_node[6];
	uint16_t s_socket;
} ipx_addr;

typedef struct _sockaddr_in
{
	u_short sin_family;
	u_short sin_port;
	in_addr sin_addr;
	char sin_zero[8];
} sockaddr_in;

/* IPv6 version of above */
typedef struct _sockaddr_in6
{
	u_short sin6_family; //  AF_INET6
	u_short sin6_port; //  transport layer port #
	u_int sin6_flowinfo; //  IPv6 flow information
	in6_addr sin6_addr; //  IPv6 address
	u_int sin6_scope_id; //  set of interfaces for a scope
} sockaddr_in6;

/* IPX version of above */
typedef struct _sockaddr_ipx
{
	u_short sipx_family; //  AF_IPX
	ipx_addr sipx_addr; //  IPX address
} sockaddr_ipx;

/*  Structure used by kernel to store most addresses.  */
typedef struct _sockaddr
{
	u_short sa_family;    // address family
	char    sa_data[14];  // up to 14 bytes of direct address
} sockaddr;

typedef sockaddr SOCKADDR;

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

typedef OVERLAPPED WSAOVERLAPPED;

typedef struct _BLOB
{
	uint32_t cbsize;
	uint8_t *pblobdata;
} BLOB;

/*  WinSock 2 extension -- WSABUF and QOS struct, include qos.h to pull in FLOWSPEC and related definitions  */
typedef struct _WSABUF
{
	uint32_t len; //  the length of the buffer
	char *buf; //  the pointer to the buffer
} WSABUF;

typedef int32_t SERVICETYPE;

typedef struct _FLOWSPEC
{
	int32_t tokenrate; //  In Bytes/sec
	int32_t tokenbucketsize; //  In Bytes
	int32_t peakbandwidth; //  In Bytes/sec
	int32_t latency; //  In microseconds
	int32_t delayvariation; //  In microseconds
	SERVICETYPE servicetype;
	int32_t maxsdusize;
	int32_t minimumpolicedsize; //  In Bytes
} FLOWSPEC;

typedef struct _QOS
{
	FLOWSPEC sendingflowspec; //  the flow spec for data sending
	FLOWSPEC receivingflowspec; //  the flow spec for data receiving
	WSABUF providerspecific; //  additional provider specific stuff
} QOS;

typedef u_long GROUP;

/*  WinSock 2 extension -- data type for WSAEnumNetworkEvents()  */
typedef struct _WSANETWORKEVENTS
{
	long lnetworkevents;
	int ierrorcode[FD_MAX_EVENTS];
} WSANETWORKEVENTS;

typedef struct _WSAPROTOCOLCHAIN
{
    int ChainLen;                                 // the length of the chain,
                                                  // length = 0 means layered protocol,
                                                  // length = 1 means base protocol,
                                                  // length > 1 means protocol chain
    DWORD ChainEntries[MAX_PROTOCOL_CHAIN];       // a list of dwCatalogEntryIds
} WSAPROTOCOLCHAIN;

typedef struct _WSAPROTOCOL_INFOA
{
	int32_t dwserviceflags1;
	int32_t dwserviceflags2;
	int32_t dwserviceflags3;
	int32_t dwserviceflags4;
	int32_t dwproviderflags;
	GUID providerid;
	int32_t dwcatalogentryid;
	WSAPROTOCOLCHAIN protocolchain;
	int32_t iversion;
	int32_t iaddressfamily;
	int32_t imaxsockaddr;
	int32_t iminsockaddr;
	int32_t isockettype;
	int32_t iprotocol;
	int32_t iprotocolmaxoffset;
	int32_t inetworkbyteorder;
	int32_t isecurityscheme;
	int32_t dwmessagesize;
	int32_t dwproviderreserved;
	char szprotocol[WSAPROTOCOL_LEN + 1];
} WSAPROTOCOL_INFOA;

typedef struct _WSAPROTOCOL_INFOW
{
	int32_t dwserviceflags1;
	int32_t dwserviceflags2;
	int32_t dwserviceflags3;
	int32_t dwserviceflags4;
	int32_t dwproviderflags;
	GUID providerid;
	int32_t dwcatalogentryid;
	WSAPROTOCOLCHAIN protocolchain;
	int32_t iversion;
	int32_t iaddressfamily;
	int32_t imaxsockaddr;
	int32_t iminsockaddr;
	int32_t isockettype;
	int32_t iprotocol;
	int32_t iprotocolmaxoffset;
	int32_t inetworkbyteorder;
	int32_t isecurityscheme;
	int32_t dwmessagesize;
	int32_t dwproviderreserved;
	WCHAR szprotocol[WSAPROTOCOL_LEN + 1];
} WSAPROTOCOL_INFOW;

/*  SockAddr Information  */
typedef struct _SOCKET_ADDRESS
{
	SOCKADDR *lpsockaddr;
	int32_t isockaddrlength;
} SOCKET_ADDRESS;

/*  CSAddr Information  */
typedef struct _CSADDR_INFO
{
	SOCKET_ADDRESS localaddr;
    SOCKET_ADDRESS remoteaddr;
	int32_t isockettype;
    int32_t iprotocol;
} CSADDR_INFO;

/*  Address Family/Protocol Tuples  */
typedef struct _AFPROTOCOLS
{
	int32_t iaddressfamily;
	int32_t iprotocol;
} AFPROTOCOLS;

/*  Client Query API Typedefs  */

/*  The comparators  */
typedef enum _WSAECOMPARATOR
{
 COMP_EQUAL = 0,
 COMP_NOTLESS
} WSAECOMPARATOR;

typedef struct _WSAVERSION
{
	int32_t dwversion;
	WSAECOMPARATOR echow;
} WSAVERSION;

typedef struct _WSAQUERYSETA
{
	int32_t dwsize;
	char *lpszserviceinstancename;
	GUID *lpserviceclassid;
	WSAVERSION *lpversion;
	char *lpszcomment;
	int32_t dwnamespace;
	GUID *lpnsproviderid;
	char *lpszcontext;
	int32_t dwnumberofprotocols;
	AFPROTOCOLS *lpafpprotocols;
	char *lpszquerystring;
	int32_t dwnumberofcsaddrs;
	CSADDR_INFO *lpcsabuffer;
	int32_t dwoutputflags;
	BLOB *lpblob;
} WSAQUERYSETA;

typedef struct _WSAQUERYSETW
{
	int32_t dwsize;
	WCHAR *lpszserviceinstancename;
	GUID *lpserviceclassid;
	WSAVERSION *lpversion;
	WCHAR *lpszcomment;
	int32_t dwnamespace;
	GUID *lpnsproviderid;
	WCHAR *lpszcontext;
	int32_t dwnumberofprotocols;
	AFPROTOCOLS *lpafpprotocols;
	WCHAR *lpszquerystring;
	int32_t dwnumberofcsaddrs;
	CSADDR_INFO *lpcsabuffer;
	int32_t dwoutputflags;
	BLOB *lpblob;
} WSAQUERYSETW;

typedef WSAQUERYSETA WSAQUERYSET;

typedef struct _WSAMSG
{
	SOCKET_ADDRESS *name;
	int32_t namelen;
	WSABUF *lpbuffers;
	uint32_t dwbuffercount;
	WSABUF control;
	uint32_t dwflags;
} WSAMSG;

/*  Service Address Registration and Deregistration Data Types.  */
typedef enum _WSAESETSERVICEOP
{
 RNRSERVICE_REGISTER = 0,
 RNRSERVICE_DEREGISTER,
 RNRSERVICE_DELETE
} WSAESETSERVICEOP;

/*  Service Installation/Removal Data Types.  */
typedef struct _WSANSCLASSINFOA
{
	char *lpszname;
	int32_t dwnamespace;
	int32_t dwvaluetype;
	int32_t dwvaluesize;
	void *lpvalue;
} WSANSCLASSINFOA;

typedef struct _WSANSCLASSINFOW
{
	WCHAR *lpszname;
	int32_t dwnamespace;
	int32_t dwvaluetype;
	int32_t dwvaluesize;
	void *lpvalue;
} WSANSCLASSINFOW;

typedef WSANSCLASSINFOA WSANSCLASSINFO;

typedef struct _WSASERVICECLASSINFOA
{
	GUID *lpserviceclassid;
	char *lpszserviceclassname;
	int32_t dwcount;
	WSANSCLASSINFOA *lpclassinfos;
} WSASERVICECLASSINFOA;

typedef struct _WSASERVICECLASSINFOW
{
	GUID *lpserviceclassid;
	WCHAR *lpszserviceclassname;
	int32_t dwcount;
	WSANSCLASSINFOW *lpclassinfos;
} WSASERVICECLASSINFOW;

typedef WSASERVICECLASSINFOA WSASERVICECLASSINFO;

typedef struct _WSANAMESPACE_INFOA
{
	GUID nsproviderid;
	int32_t dwnamespace;
	BOOL factive;
	int32_t dwversion;
	char *lpszidentifier;
} WSANAMESPACE_INFOA;

typedef struct _WSANAMESPACE_INFOW
{
	GUID nsproviderid;
	int32_t dwnamespace;
	BOOL factive;
	int32_t dwversion;
	WCHAR *lpszidentifier;
} WSANAMESPACE_INFOW;

typedef WSANAMESPACE_INFOA WSANAMESPACE_INFO;

/*  WinSock 2 extensions -- data types for the condition function in  */
/*  WSAAccept() and overlapped I/O completion routine.  */
typedef int32_t STDCALL (*LPCONDITIONPROC)(WSABUF *lpcallerid, WSABUF *lpcallerdata, QOS *lpsqos, QOS *lpgqos, WSABUF *lpcalleeid, WSABUF *lpcalleedata, GROUP g, uint32_t dwcallbackdata);
typedef void STDCALL (*LPWSAOVERLAPPED_COMPLETION_ROUTINE)(uint32_t dwerror, uint32_t cbtransferred, WSAOVERLAPPED *lpoverlapped, uint32_t dwflags);

/* Structure used in getaddrinfo() call */
typedef struct _ADDRINFO ADDRINFO;
struct _ADDRINFO
{
	int32_t ai_flags; // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
	int32_t ai_family; // PF_xxx
	int32_t ai_socktype; // SOCK_xxx
	int32_t ai_protocol; // 0 or IPPROTO_xxx for IPv4 and IPv6
	size_t ai_addrlen; // Length of ai_addr
	char *ai_canonname; // Canonical name for nodename
	SOCKADDR *ai_addr; // Binary address
	ADDRINFO *ai_next; // Next structure in linked list
};

/* ============================================================================== */
/* Initialization Functions */
BOOL STDCALL WS2Start(void);
BOOL STDCALL WS2Stop(void);

void STDCALL WS2AsyncStart(void *data);

/* ============================================================================== */
/* Winsock2 Functions */
SOCKET STDCALL accept(SOCKET s, SOCKADDR *addr, int32_t *addrlen);
int32_t STDCALL bind(SOCKET s, SOCKADDR *addr, int32_t namelen);
int32_t STDCALL closesocket(SOCKET s);
int32_t STDCALL connect(SOCKET s, SOCKADDR *name, int32_t namelen);
int32_t STDCALL ioctlsocket(SOCKET s, int32_t cmd, u_long *arg);
int32_t STDCALL getpeername(SOCKET s, SOCKADDR *name, int32_t *namelen);
int32_t STDCALL getsockname(SOCKET s, SOCKADDR *name, int32_t *namelen);
int32_t STDCALL getsockopt(SOCKET s, int32_t level, int32_t optname, char *optval, int32_t *optlen);
u_long STDCALL htonl(u_long hostlong);
u_short STDCALL htons(u_short hostshort);
u_long STDCALL inet_addr(const char *cp);
char * STDCALL inet_ntoa(in_addr inaddr);
int32_t STDCALL listen(SOCKET s, int32_t backlog);
u_long STDCALL ntohl(u_long netlong);
u_short STDCALL ntohs(u_short netshort);
int32_t STDCALL recv(SOCKET s, char *buf, int32_t len, int32_t flags);
int32_t STDCALL recvfrom(SOCKET s, char *buf, int32_t len, int32_t flags, SOCKADDR *from, int32_t *fromlen);
int32_t STDCALL select(int32_t nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, wstimeval *timeout);
int32_t STDCALL send(SOCKET s, const char *buf, int32_t len, int32_t flags);
int32_t STDCALL sendto(SOCKET s, const char *buf, int32_t len, int32_t flags, SOCKADDR *addrto, int32_t tolen);
int32_t STDCALL setsockopt(SOCKET s, int32_t level, int32_t optname, const char *optval, int32_t optlen); // overload;
int32_t STDCALL shutdown(SOCKET s, int32_t how);
SOCKET STDCALL socket(int32_t af, int32_t type, int32_t protocol);

hostent * STDCALL gethostbyaddr(void *addr, int32_t len, int32_t family);
hostent * STDCALL gethostbyname(const char *name);
int32_t STDCALL gethostname(char *name, int32_t len);
servent * STDCALL getservbyport(int32_t port, const char *proto);
servent * STDCALL getservbyname(const char *name, const char *proto);
protoent * STDCALL getprotobynumber(int32_t proto);
protoent * STDCALL getprotobyname(const char *name);

int32_t STDCALL getaddrinfo(const char *pnodename, const char *pservicename, ADDRINFO *phints, ADDRINFO **ppresult);
void STDCALL freeaddrinfo(ADDRINFO *ai);
int STDCALL getnameinfo(SOCKADDR *sa, int salen, char *host, uint32_t hostlen, char *serv, uint32_t servlen, int flags);

int32_t STDCALL WSAStartup(uint16_t wversionrequired, WSADATA *wsdata);
int32_t STDCALL WSACleanup(void);
void STDCALL WSASetLastError(int32_t ierror);
int32_t STDCALL WSAGetLastError(void);
BOOL STDCALL WSAIsBlocking(void);
int32_t STDCALL WSAUnhookBlockingHook(void);
FARPROC STDCALL WSASetBlockingHook(FARPROC lpblockfunc);
int32_t STDCALL WSACancelBlockingCall(void);
HANDLE STDCALL WSAAsyncGetServByName(HWND hwindow, u_int wmsg, const char *name, const char *proto, char *buf, int32_t buflen);
HANDLE STDCALL WSAAsyncGetServByPort(HWND hwindow, u_int wmsg, u_int port, const char *proto, char *buf, int32_t buflen);
HANDLE STDCALL WSAAsyncGetProtoByName(HWND hwindow, u_int wmsg, const char *name, char *buf, int32_t buflen);
HANDLE STDCALL WSAAsyncGetProtoByNumber(HWND hwindow, u_int wmsg, int32_t number, char *buf, int32_t buflen);
HANDLE STDCALL WSAAsyncGetHostByName(HWND hwindow, u_int wmsg, const char *name, char *buf, int32_t buflen);
HANDLE STDCALL WSAAsyncGetHostByAddr(HWND hwindow, u_int wmsg, const char *addr, int32_t len, int32_t family, char *buf, int32_t buflen);
int32_t STDCALL WSACancelAsyncRequest(HANDLE hasynctaskhandle);
int32_t STDCALL WSAAsyncSelect(SOCKET s, HWND hwindow, u_int wmsg, int32_t levent);
BOOL STDCALL __WSAFDIsSet(SOCKET s, fd_set *fdset);

/*  WinSock 2 API new function prototypes  */
int32_t STDCALL inet_pton(int32_t family, const char *pszaddrstring, void *paddrbuf);
int32_t STDCALL InetPtonA(int32_t family, const char *pszaddrstring, void *paddrbuf);
int32_t STDCALL InetPtonW(int32_t family, const WCHAR *pszaddrstring, void *paddrbuf);

char * STDCALL inet_ntop(int32_t family, void *paddr, char *pstringbuf, int32_t stringbufsize);
char * STDCALL InetNtopA(int32_t family, void *paddr, char *pstringbuf, int32_t stringbufsize);
WCHAR * STDCALL InetNtopW(int32_t family, void *paddr, WCHAR *pstringbuf, int32_t stringbufsize);

SOCKET STDCALL WSAAccept(SOCKET s, SOCKADDR addr, int32_t *addrlen, LPCONDITIONPROC lpfncondition, uint32_t dwcallbackdata);
BOOL STDCALL WSACloseEvent(WSAEVENT hevent);
int32_t STDCALL WSAConnect(SOCKET s, SOCKADDR *name, int32_t namelen, WSABUF *lpcallerdata, WSABUF *lpcalleedata, QOS *lpsqos, QOS *lpgqos);
WSAEVENT STDCALL WSACreateEvent(void);
int32_t STDCALL WSADuplicateSocketA(SOCKET s, uint32_t dwprocessid, WSAPROTOCOL_INFOA *lpprotocolinfo);
int32_t STDCALL WSADuplicateSocketW(SOCKET s, uint32_t dwprocessid, WSAPROTOCOL_INFOW *lpprotocolinfo);
int32_t STDCALL WSAEnumNetworkEvents(SOCKET s, WSAEVENT heventobject, WSANETWORKEVENTS *lpnetworkevents);
int32_t STDCALL WSAEnumProtocolsA(int32_t *lpiprotocols, WSAPROTOCOL_INFOA *lpprotocolbuffer, uint32_t *lpdwbufferlength);
int32_t STDCALL WSAEnumProtocolsW(int32_t *lpiprotocols, WSAPROTOCOL_INFOW *lpprotocolbuffer, uint32_t *lpdwbufferlength);
int32_t STDCALL WSAEventSelect(SOCKET s, WSAEVENT heventobject, int32_t lnetworkevents);
BOOL STDCALL WSAGetOverlappedResult(SOCKET s, WSAOVERLAPPED *lpoverlapped, DWORD *lpcbtransfer, BOOL fwait, uint32_t *lpdwflags);
BOOL STDCALL WSAGetQosByName(SOCKET s, WSABUF *lpqosname, QOS *lpqos);
int32_t STDCALL WSAhtonl(SOCKET s, u_long hostlong, uint32_t *lpnetlong);
int32_t STDCALL WSAhtons(SOCKET s, u_short hostshort, uint16_t *lpnetshort);
int32_t STDCALL WSAIoctl(SOCKET s, uint32_t dwiocontrolcode, void *lpvinbuffer, uint32_t cbinbuffer, void *lpvoutbuffer, uint32_t cboutbuffer, DWORD *lpcbbytesreturned, WSAOVERLAPPED *lpoverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpcompletionroutine);
SOCKET STDCALL WSAJoinLeaf(SOCKET s, SOCKADDR *name, int32_t namelen, WSABUF *lpcallerdata, WSABUF *lpcalleedata, QOS *lpsqos, QOS *lpgqos, uint32_t dwflags);
int32_t STDCALL WSANtohl(SOCKET s, u_long netlong, uint32_t *lphostlong);
int32_t STDCALL WSANtohs(SOCKET s, u_short netshort, uint16_t *lphostshort);
int32_t STDCALL WSARecv(SOCKET s, WSABUF *lpbuffers, uint32_t dwbuffercount, uint32_t *lpnumberofbytesrecvd, uint32_t *lpflags, WSAOVERLAPPED *lpoverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpcompletionroutine);
int32_t STDCALL WSARecvDisconnect(SOCKET s, WSABUF *lpinbounddisconnectdata);
int32_t STDCALL WSARecvFrom(SOCKET s, WSABUF *lpbuffers, uint32_t dwbuffercount, uint32_t *lpnumberofbytesrecvd, uint32_t *lpflags, SOCKADDR *lpfrom, int32_t *lpfromlen, WSAOVERLAPPED *lpoverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpcompletionroutine);
int32_t STDCALL WSARecvMsg(SOCKET s, WSAMSG *lpmsg, uint32_t lpdwnumberofbytesrecvd, WSAOVERLAPPED *lpoverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpcompletionroutine);
BOOL STDCALL WSAResetEvent(WSAEVENT hevent);
int32_t STDCALL WSASend(SOCKET s, WSABUF *lpbuffers, uint32_t dwbuffercount, uint32_t *lpnumberofbytessent, uint32_t dwflags, WSAOVERLAPPED *lpoverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpcompletionroutine);
int32_t STDCALL WSASendDisconnect(SOCKET s, WSABUF *lpoutbounddisconnectdata);
int32_t STDCALL WSASendTo(SOCKET s, WSABUF *lpbuffers, uint32_t dwbuffercount, uint32_t *lpnumberofbytessent, uint32_t dwflags, SOCKADDR *lpto, int32_t itolen, WSAOVERLAPPED *lpoverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpcompletionroutine);
int32_t STDCALL WSASendMsg(SOCKET s, WSAMSG *lpmsg, uint32_t dwflags, uint32_t lpnumberofbytessent, WSAOVERLAPPED *lpoverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpcompletionroutine);
BOOL STDCALL WSASetEvent(WSAEVENT hevent);
SOCKET STDCALL WSASocketA(int32_t af, int32_t itype, int32_t protocol, WSAPROTOCOL_INFOA *lpprotocolinfo, GROUP g, uint32_t dwflags);
SOCKET STDCALL WSASocketW(int32_t af, int32_t itype, int32_t protocol, WSAPROTOCOL_INFOW *lpprotocolinfo, GROUP g, uint32_t dwflags);

uint32_t STDCALL WSAWaitForMultipleEvents(uint32_t cevents, WSAEVENT *lphevents, LONGBOOL fwaitall, uint32_t dwtimeout, LONGBOOL falertable);
int32_t STDCALL WSAAddressToStringA(SOCKADDR *lpsaaddress, uint32_t *dwaddresslength, WSAPROTOCOL_INFOA *lpprotocolinfo, char *lpszaddressstring, uint32_t *lpdwaddressstringlength);
int32_t STDCALL WSAAddressToStringW(SOCKADDR *lpsaaddress, uint32_t *dwaddresslength, WSAPROTOCOL_INFOW *lpprotocolinfo, WCHAR *lpszaddressstring, uint32_t *lpdwaddressstringlength);

int32_t STDCALL WSAStringToAddressA(char *addressstring, int32_t *addressfamily, WSAPROTOCOL_INFOA *lpprotocolinfo, SOCKADDR *lpaddress, int32_t *lpaddresslength);
int32_t STDCALL WSAStringToAddressW(WCHAR *addressstring, int32_t *addressfamily, WSAPROTOCOL_INFOA *lpprotocolinfo, SOCKADDR *lpaddress, int32_t *lpaddresslength);

/*  Registration and Name Resolution API functions  */
int32_t STDCALL WSALookupServiceBeginA(WSAQUERYSETA *lpqsrestrictions, uint32_t *dwcontrolflags, HANDLE *lphlookup);
int32_t STDCALL WSALookupServiceBeginW(WSAQUERYSETW *lpqsrestrictions, uint32_t *dwcontrolflags, HANDLE *lphlookup);

int32_t STDCALL WSALookupServiceNextA(HANDLE *hlookup, uint32_t *dwcontrolflags, uint32_t *lpdwbufferlength, WSAQUERYSETA *lpqsresults);
int32_t STDCALL WSALookupServiceNextW(HANDLE *hlookup, uint32_t *dwcontrolflags, uint32_t *lpdwbufferlength, WSAQUERYSETW *lpqsresults);
int32_t STDCALL WSALookupServiceEnd(HANDLE *hlookup);
int32_t STDCALL WSAInstallServiceClassA(WSASERVICECLASSINFOA *lpserviceclassinfo);
int32_t STDCALL WSAInstallServiceClassW(WSASERVICECLASSINFOW *lpserviceclassinfo);
int32_t STDCALL WSARemoveServiceClass(GUID *lpserviceclassid);
int32_t STDCALL WSAGetServiceClassInfoA(GUID *lpproviderid, GUID *lpserviceclassid, uint32_t *lpdwbufsize, WSASERVICECLASSINFOA *lpserviceclassinfo);
int32_t STDCALL WSAGetServiceClassInfoW(GUID *lpproviderid, GUID *lpserviceclassid, uint32_t *lpdwbufsize, WSASERVICECLASSINFOW *lpserviceclassinfo);

int32_t STDCALL WSAEnumNameSpaceProvidersA(uint32_t *lpdwbufferlength, WSANAMESPACE_INFOA *lpnspbuffer);
int32_t STDCALL WSAEnumNameSpaceProvidersW(uint32_t *lpdwbufferlength, WSANAMESPACE_INFOW *lpnspbuffer);

int32_t STDCALL WSAGetServiceClassNameByClassIdA(GUID *lpserviceclassid, char *lpszserviceclassname, uint32_t *lpdwbufferlength);
int32_t STDCALL WSAGetServiceClassNameByClassIdW(GUID *lpserviceclassid, WCHAR *lpszserviceclassname, uint32_t *lpdwbufferlength);
int32_t STDCALL WSASetServiceA(WSAQUERYSETA *lpqsreginfo, WSAESETSERVICEOP *essoperation, uint32_t *dwcontrolflags);
int32_t STDCALL WSASetServiceW(WSAQUERYSETW *lpqsreginfo, WSAESETSERVICEOP *essoperation, uint32_t *dwcontrolflags);

int32_t STDCALL WSAMakeSyncReply(uint16_t buflen, uint16_t error);
int32_t STDCALL WSAMakeSelectReply(uint16_t event, uint16_t error);
uint16_t STDCALL WSAGetAsyncBuflen(int32_t param);
uint16_t STDCALL WSAGetAsyncError(int32_t param);
uint16_t STDCALL WSAGetSelectEvent(int32_t param);
uint16_t STDCALL WSAGetSelectError(int32_t param);

void STDCALL FD_CLR(SOCKET socket, fd_set *fdset);
BOOL STDCALL FD_ISSET(SOCKET socket, fd_set *fdset);
void STDCALL FD_SET(SOCKET socket, fd_set *fdset);
void STDCALL FD_ZERO(fd_set *fdset);

/* ============================================================================== */
/* Winsock2 Undocumented Functions */
int STDCALL WsControl(uint32_t proto, uint32_t action, void *prequestinfo, uint32_t *pcbrequestinfolen, void *presponseinfo, uint32_t *pcbresponseinfolen);

netent * STDCALL getnetbyaddr(void *addr, int len, int type);
netent * STDCALL getnetbyname(const char *name);

/* ============================================================================== */
/* Winsock2 Enhanced Functions */
int STDCALL WsControlEx(uint32_t proto, uint32_t action, void *prequestinfo, uint32_t *pcbrequestinfolen, void *presponseinfo, uint32_t *pcbresponseinfolen);

/* ============================================================================== */
/* Winsock2 Helper Functions */
BOOL STDCALL Winsock2RedirectInput(SOCKET s);
BOOL STDCALL Winsock2RedirectOutput(SOCKET s);

uint32_t STDCALL Winsock2ErrorToString(int32_t error, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_WINSOCK2_H