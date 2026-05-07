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
#ifndef _ULTIBO_PL011_H
#define _ULTIBO_PL011_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/uart.h"
#include "ultibo/threads.h"

#define PL011_UART_RX_BUFFER

/** PL011 specific constants */
#define PL011_UART_DESCRIPTION	"ARM PrimeCell PL011 UART" ///< Description of PL011 device

#define PL011_UART_MIN_BAUD	300 ///< Default minimum of 300 baud
#define PL011_UART_MAX_BAUD	1500000 ///< Default maximum based on 24MHz clock

#define PL011_UART_MIN_DATABITS	SERIAL_DATA_5BIT
#define PL011_UART_MAX_DATABITS	SERIAL_DATA_8BIT

#define PL011_UART_MIN_STOPBITS	SERIAL_STOP_1BIT
#define PL011_UART_MAX_STOPBITS	SERIAL_STOP_2BIT

#define PL011_UART_MAX_PARITY	SERIAL_PARITY_EVEN

#define PL011_UART_MAX_FLOW	SERIAL_FLOW_RTS_CTS

#define PL011_UART_CLOCK_RATE	24000000
#ifdef PL011_UART_RX_BUFFER
#define PL011_UART_RX_POLL_LIMIT	256 ///< Number of times interrupt handler may poll the read FIFO
#define PL011_UART_RX_BUFFER_SIZE	1024
#endif

/** PL011 UART Data register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_DR_OE	(1 << 11) ///< Overrun error
#define PL011_UART_DR_BE	(1 << 10) ///< Break error
#define PL011_UART_DR_PE	(1 << 9) ///< Parity error
#define PL011_UART_DR_FE	(1 << 8) ///< Framing error
#define PL011_UART_DR_DATA	(0xFF << 0) ///< Receive / Transmit data
#define PL011_UART_DR_ERROR	PL011_UART_DR_OE | PL011_UART_DR_BE | PL011_UART_DR_PE | PL011_UART_DR_FE

/** PL011 UART Receive Status / Error Clear register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_RSRECR_OE	(1 << 3) ///< Overrun error
#define PL011_UART_RSRECR_BE	(1 << 2) ///< Break error
#define PL011_UART_RSRECR_PE	(1 << 1) ///< Parity error
#define PL011_UART_RSRECR_FE	(1 << 0) ///< Framing error

/** PL011 UART Flag register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_FR_RI	(1 << 8) ///< Unsupported, write zero, read as don't care
#define PL011_UART_FR_TXFE	(1 << 7) ///< Transmit FIFO empty
#define PL011_UART_FR_RXFF	(1 << 6) ///< Receive FIFO full
#define PL011_UART_FR_TXFF	(1 << 5) ///< Transmit FIFO full
#define PL011_UART_FR_RXFE	(1 << 4) ///< Receive FIFO empty
#define PL011_UART_FR_BUSY	(1 << 3) ///< UART busy
#define PL011_UART_FR_DCD	(1 << 2) ///< Unsupported, write zero, read as don't care
#define PL011_UART_FR_DSR	(1 << 1) ///< Unsupported, write zero, read as don't care
#define PL011_UART_FR_CTS	(1 << 0) ///< Clear to send (This bit is the complement of the UART clear to send, nUARTCTS, modem status input. That is, the bit is 1 when nUARTCTS is LOW)

/** PL011 UART IrDA register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */

/** PL011 UART Integer Baud Rate Divisor register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_IBRD_MASK	(0xFFFF << 0)

/** PL011 UART Fractional Baud Rate Divisor register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_FBRD_MASK	(0x3F << 0)

/** PL011 UART Line Control register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_LCRH_SPS	(1 << 7) ///< Stick parity select
#define PL011_UART_LCRH_WLEN	(3 << 5) ///< Word length
#define PL011_UART_LCRH_WLEN8	(3 << 5) ///<  8 bits
#define PL011_UART_LCRH_WLEN7	(2 << 5) ///<  7 bits
#define PL011_UART_LCRH_WLEN6	(1 << 5) ///<  6 bits
#define PL011_UART_LCRH_WLEN5	(0 << 5) ///<  5 bits
#define PL011_UART_LCRH_FEN	(1 << 4) ///< Enable FIFOs
#define PL011_UART_LCRH_STP2	(1 << 3) ///< Two stop bits select
#define PL011_UART_LCRH_EPS	(1 << 2) ///< Even parity select (0 = odd parity / 1 = even parity)
#define PL011_UART_LCRH_PEN	(1 << 1) ///< Parity enable
#define PL011_UART_LCRH_BRK	(1 << 0) ///< Send break

/** PL011 UART Control register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_CR_CTSEN	(1 << 15) ///< CTS hardware flow control enable (If this bit is set to 1 data is only transmitted when the nUARTCTS signal is asserted)
#define PL011_UART_CR_RTSEN	(1 << 14) ///< RTS hardware flow control enable (If this bit is set to 1 data is only requested when there is space in the receive FIFO for it to be received)
#define PL011_UART_CR_OUT2	(1 << 13) ///< Unsupported, write zero, read as don't care
#define PL011_UART_CR_OUT1	(1 << 12) ///< Unsupported, write zero, read as don't care
#define PL011_UART_CR_RTS	(1 << 11) ///< Request to send (This bit is the complement of the UART request to send, nUARTRTS, modem status output. That is, when the bit is programmed to a 1 then nUARTRTS is LOW)
#define PL011_UART_CR_DTR	(1 << 10) ///< Unsupported, write zero, read as don't care
#define PL011_UART_CR_RXE	(1 << 9) ///< Receive enable
#define PL011_UART_CR_TXE	(1 << 8) ///< Transmit enable
#define PL011_UART_CR_LBE	(1 << 7) ///< Loopback enable
/** Bits 6:3 Reserved - Write as 0, read as don't care */
#define PL011_UART_CR_SIRLP	(1 << 2) ///< Unsupported, write zero, read as don't care
#define PL011_UART_CR_SIREN	(1 << 1) ///< Unsupported, write zero, read as don't care
#define PL011_UART_CR_UARTEN	(1 << 0) ///< UART enable

/** PL011 UART Interrupt FIFO Level Select register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_IFLS_RXIFPSEL	(7 << 9) ///< Unsupported, write zero, read as don't care
#define PL011_UART_IFLS_TXIFPSEL	(7 << 6) ///< Unsupported, write zero, read as don't care
#define PL011_UART_IFLS_RXIFLSEL	(7 << 3) ///< Receive interrupt FIFO level select
#define PL011_UART_IFLS_RXIFLSEL1_8	(0 << 3) ///<  b000 = Receive FIFO becomes >= 1/8 full
#define PL011_UART_IFLS_RXIFLSEL1_4	(1 << 3) ///<  b001 = Receive FIFO becomes >= 1/4 full
#define PL011_UART_IFLS_RXIFLSEL1_2	(2 << 3) ///<  b010 = Receive FIFO becomes >= 1/2 full
#define PL011_UART_IFLS_RXIFLSEL3_4	(3 << 3) ///<  b011 = Receive FIFO becomes >= 3/4 full
#define PL011_UART_IFLS_RXIFLSEL7_8	(4 << 3) ///<  b100 = Receive FIFO becomes >= 7/8 full
#define PL011_UART_IFLS_TXIFLSEL	(7 << 0) ///< Transmit interrupt FIFO level select
#define PL011_UART_IFLS_TXIFLSEL1_8	(0 << 0) ///<  b000 = Transmit FIFO becomes <= 1/8 full
#define PL011_UART_IFLS_TXIFLSEL1_4	(1 << 0) ///<  b001 = Transmit FIFO becomes <= 1/4 full
#define PL011_UART_IFLS_TXIFLSEL1_2	(2 << 0) ///<  b010 = Transmit FIFO becomes <= 1/2 full
#define PL011_UART_IFLS_TXIFLSEL3_4	(3 << 0) ///<  b011 = Transmit FIFO becomes <= 3/4 full
#define PL011_UART_IFLS_TXIFLSEL7_8	(4 << 0) ///<  b100 = Transmit FIFO becomes <= 7/8 full

/** PL011 UART Interrupt Mask Set/Clear register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_IMSC_OEIM	(1 << 10) ///< Overrun error interrupt mask
#define PL011_UART_IMSC_BEIM	(1 << 9) ///< Break error interrupt mask
#define PL011_UART_IMSC_PEIM	(1 << 8) ///< Parity error interrupt mask
#define PL011_UART_IMSC_FEIM	(1 << 7) ///< Framing error interrupt mask
#define PL011_UART_IMSC_RTIM	(1 << 6) ///< Receive timeout interrupt mask
#define PL011_UART_IMSC_TXIM	(1 << 5) ///< Transmit interrupt mask
#define PL011_UART_IMSC_RXIM	(1 << 4) ///< Receive interrupt mask
#define PL011_UART_IMSC_DSRMIM	(1 << 3) ///< Unsupported, write zero, read as don't care
#define PL011_UART_IMSC_DCDMIM	(1 << 2) ///< Unsupported, write zero, read as don't care
#define PL011_UART_IMSC_CTSMIM	(1 << 1) ///< nUARTCTS modem interrupt mask
#define PL011_UART_IMSC_RIMIM	(1 << 0) ///< Unsupported, write zero, read as don't care

/** PL011 UART Raw Interrupt Status register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_RIS_OERIS	(1 << 10) ///< Overrun error interrupt status
#define PL011_UART_RIS_BERIS	(1 << 9) ///< Break error interrupt status
#define PL011_UART_RIS_PERIS	(1 << 8) ///< Parity error interrupt status
#define PL011_UART_RIS_FERIS	(1 << 7) ///< Framing error interrupt status
#define PL011_UART_RIS_RTRIS	(1 << 6) ///< Receive timeout interrupt status
#define PL011_UART_RIS_TXRIS	(1 << 5) ///< Transmit interrupt status
#define PL011_UART_RIS_RXRIS	(1 << 4) ///< Receive interrupt status
#define PL011_UART_RIS_DSRMRIS	(1 << 3) ///< Unsupported, write zero, read as don't care
#define PL011_UART_RIS_DCDMRIS	(1 << 2) ///< Unsupported, write zero, read as don't care
#define PL011_UART_RIS_CTSMRIS	(1 << 1) ///< nUARTCTS modem interrupt status
#define PL011_UART_RIS_RIMRIS	(1 << 0) ///< Unsupported, write zero, read as don't care

/** PL011 UART Masked Interrupt Status register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_MIS_OEMIS	(1 << 10) ///< Overrun error masked interrupt status
#define PL011_UART_MIS_BEMIS	(1 << 9) ///< Break error masked interrupt status
#define PL011_UART_MIS_PEMIS	(1 << 8) ///< Parity error masked interrupt status
#define PL011_UART_MIS_FEMIS	(1 << 7) ///< Framing error masked interrupt status
#define PL011_UART_MIS_RTMIS	(1 << 6) ///< Receive timeout masked interrupt status
#define PL011_UART_MIS_TXMIS	(1 << 5) ///< Transmit masked interrupt status
#define PL011_UART_MIS_RXMIS	(1 << 4) ///< Receive masked interrupt status
#define PL011_UART_MIS_DSRMMIS	(1 << 3) ///< Unsupported, write zero, read as don't care
#define PL011_UART_MIS_DCDMMIS	(1 << 2) ///< Unsupported, write zero, read as don't care
#define PL011_UART_MIS_CTSMMIS	(1 << 1) ///< nUARTCTS modem masked interrupt status
#define PL011_UART_MIS_RIMMIS	(1 << 0) ///< Unsupported, write zero, read as don't care

/** PL011 UART Interrupt Clear register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
#define PL011_UART_ICR_OEIC	(1 << 10) ///< Overrun error interrupt clear
#define PL011_UART_ICR_BEIC	(1 << 9) ///< Break error interrupt clear
#define PL011_UART_ICR_PEIC	(1 << 8) ///< Parity error interrupt clear
#define PL011_UART_ICR_FEIC	(1 << 7) ///< Framing error interrupt clear
#define PL011_UART_ICR_RTIC	(1 << 6) ///< Receive timeout interrupt clear
#define PL011_UART_ICR_TXIC	(1 << 5) ///< Transmit interrupt clear
#define PL011_UART_ICR_RXIC	(1 << 4) ///< Receive interrupt clear
#define PL011_UART_ICR_DSRMIC	(1 << 3) ///< Unsupported, write zero, read as don't care
#define PL011_UART_ICR_DCDMIC	(1 << 2) ///< Unsupported, write zero, read as don't care
#define PL011_UART_ICR_CTSMIC	(1 << 1) ///< nUARTCTS modem interrupt clear
#define PL011_UART_ICR_RIMIC	(1 << 0) ///< Unsupported, write zero, read as don't care

/** PL011 UART DMA Control register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */
/** This register is disabled, writing to it has no effect and reading returns 0 */

/** PL011 UART Test Control register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */

/** PL011 UART Integration Test Input register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */

/** PL011 UART Integration Test Output register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */

/** PL011 UART Test Data register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/index.html) */

/** PL011 specific types */
/** Layout of the PL011 registers (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/I18702.html) */
typedef struct _PL011_UART_REGISTERS PL011_UART_REGISTERS;
struct _PL011_UART_REGISTERS
{
	uint32_t dr; ///< Data Register
	uint32_t rsrecr; ///< Receive Status Register / Error Clear Register
	uint32_t reserved01;
	uint32_t reserved02;
	uint32_t reserved03;
	uint32_t reserved04;
	uint32_t fr; ///< Flag register
	uint32_t reserved05;
	uint32_t ilpr; ///< IrDA Low-Power Counter Register
	uint32_t ibrd; ///< Integer Baud rate divisor
	uint32_t fbrd; ///< Fractional Baud rate divisor
	uint32_t lcrh; ///< Line Control register
	uint32_t cr; ///< Control register
	uint32_t ifls; ///< Interrupt FIFO Level Select Register
	uint32_t imsc; ///< Interrupt Mask Set Clear Register
	uint32_t ris; ///< Raw Interrupt Status Register
	uint32_t mis; ///< Masked Interrupt Status Register
	uint32_t icr; ///< Interrupt Clear Register
	uint32_t dmacr; ///< DMA Control Register
	uint32_t reserved11;
	uint32_t reserved12;
	uint32_t reserved13;
	uint32_t reserved14;
	uint32_t reserved15;
	uint32_t reserved16;
	uint32_t reserved17;
	uint32_t reserved18;
	uint32_t reserved19;
	uint32_t reserved1a;
	uint32_t reserved1b;
	uint32_t reserved1c;
	uint32_t reserved1d;
	uint32_t itcr; ///< Test Control Register
	uint32_t itip; ///< Integration Test Input Register
	uint32_t itop; ///< Integration Test Output Register
	uint32_t tdr; ///< Test Data Register
};


typedef struct _PL011_UART PL011_UART;
struct _PL011_UART
{
	// UART Properties
	UART_DEVICE uart;
	// PL011 Properties
	uint32_t irq;
	SPIN_HANDLE lock; ///< Device lock (Differs from lock in UART device) (Spin lock due to use by interrupt handler)
	uint32_t clockrate; ///< Device clock rate
	PL011_UART_REGISTERS *registers; ///< Device registers
	#ifdef PL011_UART_RX_BUFFER
	uint32_t start; ///< Index of first available buffer entry
	uint32_t count; ///< Number of available entries in the buffer
	uint16_t buffer[PL011_UART_RX_BUFFER_SIZE]; ///< Buffer for received data (Includes data and status)
	#endif
	// Statistics Properties
	uint32_t interruptcount; ///< Number of interrupt requests received by the device
};

/** PL011 Functions */
UART_DEVICE * STDCALL pl011_uart_create(size_t address, char *name, uint32_t irq, uint32_t clockrate);
uint32_t STDCALL pl011_uart_destroy(UART_DEVICE *uart);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PL011_H
