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
#ifndef _ULTIBO_PL050_H
#define _ULTIBO_PL050_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/keyboard.h"
#include "ultibo/mouse.h"
#include "ultibo/ps2.h"

/* ============================================================================== */
/* PL050 specific constants */
#define PL050_KEYBOARD_DESCRIPTION	"ARM PrimeCell PL050 PS2 Keyboard" // Description of PL050 Keyboard device
#define PL050_MOUSE_DESCRIPTION	"ARM PrimeCell PL050 PS2 Mouse" // Description of PL050 Mouse device

#define PL050_KEYBOARD_SCANCODE_COUNT	256 // Number of keyboard scancode buffers for receive
#define PL050_MOUSE_PACKET_COUNT	256 // Number of mouse packet buffers for receive

#define PL050_KEYBOARD_CLOCK_RATE	8000000 // Default clock rate
#define PL050_MOUSE_CLOCK_RATE	8000000 // Default clock rate

#define PL050_KEYBOARD_SHIFTSTATE_MASK	KEYBOARD_LEFT_CTRL | KEYBOARD_LEFT_SHIFT | KEYBOARD_LEFT_ALT | KEYBOARD_RIGHT_CTRL | KEYBOARD_RIGHT_SHIFT | KEYBOARD_RIGHT_ALT

/* PL050 Control register bits */
#define PL050_CR_TYPE	(1 << 5) // 0 = PS2/AT mode / 1 = No line control bit mode
#define PL050_CR_RXINTREN	(1 << 4) // Enable receiver interrupt. This bit field is used to enable the PrimeCell KMI receiver interrupt (If KMIRXINTREn = 1, the receiver interrupt is enabled)
#define PL050_CR_TXINTREN	(1 << 3) // Enable transmitter interrupt. This bit field is used to enable the PrimeCell KMI transmitter interrupt (If KMITXINTREn = 1, the transfer interrupt is enabled)
#define PL050_CR_EN	(1 << 2) // The enable PrimeCell KMI bit field is used to enable the KMI (If KmiEn = 1, the KMI is enabled)
#define PL050_CR_FDL	(1 << 1) // The force KMI data LOW bit field is used to force the PrimeCell KMI data pad LOW regardless of the state of the KMI finite state machine (FSM) (If FKMID = 1, the PrimeCell KMI data pad is forced LOW)
#define PL050_CR_FCL	(1 << 0) // The force KMI clock LOW bit field is used to force the PrimeCell KMI clock pad LOW regardless of the state of the KMI FSM (If FKMIC = 1, the PrimeCell KMI clock pad is forced LOW)

/* PL050 Status register bits */
#define PL050_STAT_TXEMPTY	(1 << 6) // This bit indicates that the transmit register is empty and ready to transmit (0 = Transmit register full / 1 = Transmit register empty, ready to be written)
#define PL050_STAT_TXBUSY	(1 << 5) // This bit indicates that the PrimeCell KMI is currently sending data (0 = Idle / 1 = Currently sending data)
#define PL050_STAT_RXFULL	(1 << 4) // This bit indicates that the receiver register is full and ready to be read (0 = Receive register empty / 1 = Receive register full, ready to be read)
#define PL050_STAT_RXBUSY	(1 << 3) // This bit indicates that the PrimeCell KMI is currently receiving data (0 = Idle / 1 = Currently receiving data)
#define PL050_STAT_RXPARITY	(1 << 2) // This bit reflects the parity bit for the last received data byte (odd parity)
#define PL050_STAT_IC	(1 << 1) // This bit reflects the status of the KMICLKIN line after synchronizing and sampling
#define PL050_STAT_ID	(1 << 0) // This bit reflects the status of the KMIDATAIN line after synchronizing

/* PL050 Interrupt register bits */
#define PL050_IIR_TXINTR	(1 << 1) // This bit is set to 1 if the KMITXINTR transmit interrupt is asserted
#define PL050_IIR_RXINTR	(1 << 0) // This bit is set to 1 if the KMIRXINTR receive interrupt is asserted

/* ============================================================================== */
/* PL050 specific types */
/* Layout of the PL050 registers (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0143c/i1005653.html) */
typedef struct _PL050_KMI_REGISTERS PL050_KMI_REGISTERS;
struct _PL050_KMI_REGISTERS
{
	uint32_t cr; // Control register
	uint32_t stat; // Status register
	uint32_t data; // Received data (read)/ Data to be transmitted (write)
	uint32_t clkdiv; // Clock divisor register
	uint32_t iir; // Interrupt status register
};


typedef struct _PL050_KEYBOARD PL050_KEYBOARD;

typedef struct _PL050_KEYBOARD_SCANCODE PL050_KEYBOARD_SCANCODE;
struct _PL050_KEYBOARD_SCANCODE
{
	PL050_KEYBOARD *keyboard;
	uint32_t count;
	int32_t index;
	PS2_KEYBOARD_SCANCODE scancode;
};


struct _PL050_KEYBOARD
{
	// Keyboard Properties
	KEYBOARD_DEVICE keyboard;
	// PL050 Properties
	uint32_t irq;
	PL050_KMI_REGISTERS *registers; // Device registers
	uint8_t scancodeset; // The currently selected scancode set
	PL050_KEYBOARD_SCANCODE scancodedata[PL050_KEYBOARD_SCANCODE_COUNT]; // Buffers for scancode receiving
	uint32_t scancodestart; // The scancode buffer to use for the next receive
	uint32_t scancodecount; // The number of scancode buffers that are in use
	uint16_t lastcode; // The scan code of the last key pressed
	uint32_t shiftstate; // The modifier flags of the current shift state
	// Statistics Properties
	uint32_t discardcount; // Number of received bytes discarded (due to no buffer or other reasons)
	uint32_t interruptcount; // Number of interrupt requests received by the device
};


typedef struct _PL050_MOUSE PL050_MOUSE;

typedef struct _PL050_MOUSE_PACKET PL050_MOUSE_PACKET;
struct _PL050_MOUSE_PACKET
{
	PL050_MOUSE *mouse;
	uint32_t count;
	PL050_MOUSE_PACKET packet;
};


struct _PL050_MOUSE
{
	// Mouse Properties
	MOUSE_DEVICE mouse;
	// PL050 Properties
	uint32_t irq;
	PL050_KMI_REGISTERS *registers; // Device registers
	PL050_MOUSE_PACKET packetdata[PL050_MOUSE_PACKET_COUNT]; // Buffers for mouse packet receiving
	uint32_t packetstart; // The mouse packet buffer to use for the next receive
	uint32_t packetcount; // The number of mouse packet buffers that are in use
	// Statistics Properties
	uint32_t discardcount; // Number of received bytes discarded (due to no buffer or other reasons)
	uint32_t interruptcount; // Number of interrupt requests received by the device
};

/* ============================================================================== */
/* PL050 Functions */
KEYBOARD_DEVICE * STDCALL pl050_keyboard_create(size_t address, char *name, uint32_t irq, uint32_t clockrate);
uint32_t STDCALL pl050_keyboard_destroy(KEYBOARD_DEVICE *keyboard);

MOUSE_DEVICE * STDCALL pl050_mouse_create(size_t address, char *name, uint32_t irq, uint32_t clockrate);
uint32_t STDCALL pl050_mouse_destroy(MOUSE_DEVICE *mouse);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PL050_H
