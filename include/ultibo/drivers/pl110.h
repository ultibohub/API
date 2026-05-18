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
#ifndef _ULTIBO_PL110_H
#define _ULTIBO_PL110_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/framebuffer.h"

/** PL110 specific constants */
#define PL110_FRAMEBUFFER_DESCRIPTION	"ARM PrimeCell PL110 Color LCD" ///< Description of PL110 device

#define PL110_MAX_PHYSICALWIDTH	1024
#define PL110_MAX_PHYSICALHEIGHT	1024

/** PL110 mode constants */
#define PL110_MODE_UNKNOWN	0
#define PL110_MODE_VGA	1 ///< Connected to a VGA display
#define PL110_MODE_SVGA	2 ///< Connected to a SVGA display
#define PL110_MODE_TFT	3 ///< Connected to a TFT display
#define PL110_MODE_STN	4 ///< Connected to an STN display

/** PL110 register offsets (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0161e/I913915.html) */
#define PL110_CLCD_TIMING0	0x00000000 ///< Horizontal Axis Panel Control Register
#define PL110_CLCD_TIMING1	0x00000004 ///< Vertical Axis Panel Control Register
#define PL110_CLCD_TIMING2	0x00000008 ///< Clock and Signal Polarity Control Register
#define PL110_CLCD_TIMING3	0x0000000c ///< Line End Control Register
#define PL110_CLCD_UPBASE	0x00000010 ///< Upper Panel Frame Base Address Registers
#define PL110_CLCD_LPBASE	0x00000014 ///< Lower Panel Frame Base Address Registers
#define PL110_CLCD_CONTROL	0x00000018 ///< Control Register
#define PL110_CLCD_IMSC	0x0000001c ///< Interrupt Mask Set/Clear Register
#define PL110_CLCD_RIS	0x00000020 ///< Raw Interrupt Status Register
#define PL110_CLCD_MIS	0x00000024 ///< Masked Interrupt Status Register
#define PL110_CLCD_ICR	0x00000028 ///< Interrupt Clear Register
#define PL110_CLCD_UPCURR	0x0000002C ///< Upper Panel Current Address Value Registers
#define PL110_CLCD_LPCURR	0x00000030 ///< Lower Panel Current Address Value Registers
#define PL110_CLCD_PALETTE	0x00000200 ///< Color Palette Register

/** PL110 Timing0 register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0161e/I913915.html) */
#define PL110_CLCD_TIMING0_HBP	(0xFF << 24) ///< Horizontal back porch
#define PL110_CLCD_TIMING0_HFP	(0xFF << 16) ///< Horizontal front porch
#define PL110_CLCD_TIMING0_HSW	(0xFF << 8) ///< Horizontal synchronization pulse width
#define PL110_CLCD_TIMING0_PPL	(0xFC << 2) ///< Pixels-per-line (Actual pixels-per-line = 16 * (PPL + 1))

/** PL110 Timing1 register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0161e/I913915.html) */
#define PL110_CLCD_TIMING1_VBP	(0xFF << 24) ///< Vertical back porch
#define PL110_CLCD_TIMING1_VFP	(0xFF << 16) ///< Vertical front porch
#define PL110_CLCD_TIMING1_VSW	(0xFC << 10) ///< Vertical synchronization pulse width
#define PL110_CLCD_TIMING1_LPP	(0x3FF << 0) ///< Lines per panel is the number of active lines per screen (Program to number of lines required minus 1)

/** PL110 Timing2 register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0161e/I913915.html) */
#define PL110_CLCD_TIMING2_PCD_HI	(0x1F << 27) ///< Upper five bits of Panel Clock Divisor
#define PL110_CLCD_TIMING2_BCD	(1 << 26) ///< Bypass pixel clock divider
#define PL110_CLCD_TIMING2_CPL	(0x3FF << 16) ///< Clocks per line
#define PL110_CLCD_TIMING2_IOE	(1 << 14) ///< Invert output enable
#define PL110_CLCD_TIMING2_IPC	(1 << 13) ///< Invert panel clock
#define PL110_CLCD_TIMING2_IHS	(1 << 12) ///< Invert horizontal synchron
#define PL110_CLCD_TIMING2_IVS	(1 << 11) ///< Invert vertical synchronization
#define PL110_CLCD_TIMING2_ACB	(0x1F << 6) ///< AC bias pin frequency
#define PL110_CLCD_TIMING2_CLKSEL	(1 << 5) ///< This bit drives the CLCDCLKSEL signal which is used as the select signal for the external LCD clock multiplexor
#define PL110_CLCD_TIMING2_PCD_LO	(0x1F << 0) ///< Lower five bits of Panel Clock Divisor

/** PL110 Timing3 register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0161e/I913915.html) */
#define PL110_CLCD_TIMING3_LEE	(1 << 16) ///< LCD Line end enable: 0 = CLLE disabled (held LOW) / 1 = CLLE signal active
#define PL110_CLCD_TIMING3_LED	(0x3F << 0) ///< Line-end signal delay from the rising-edge of the last panel clock

/** PL110 Control register bits (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0161e/I913915.html) */
#define PL110_CLCD_CONTROL_LCDEN	(1 << 0)
#define PL110_CLCD_CONTROL_LCDBPP1	(0 << 1) ///< LCD bits per pixel: 000 = 1 bpp
#define PL110_CLCD_CONTROL_LCDBPP2	(1 << 1) ///<                     001 = 2 bpp
#define PL110_CLCD_CONTROL_LCDBPP4	(2 << 1) ///<                     010 = 4 bpp
#define PL110_CLCD_CONTROL_LCDBPP8	(3 << 1) ///<                     011 = 8 bpp
#define PL110_CLCD_CONTROL_LCDBPP16	(4 << 1) ///<                     100 = 16 bpp
#define PL110_CLCD_CONTROL_LCDBPP16_565	(6 << 1) ///<                     110 = 16 bpp 565 (PL111 only)
#define PL110_CLCD_CONTROL_LCDBPP16_444	(7 << 1) ///<                     111 = 16 bpp 444 (PL111 only)
#define PL110_CLCD_CONTROL_LCDBPP24	(5 << 1) ///<                     101 = 24 bpp
#define PL110_CLCD_CONTROL_LCDBW	(1 << 4) ///< STN LCD is monochrome (black and white) (0 = STN LCD is color / 1 = STN LCD is monochrome)
#define PL110_CLCD_CONTROL_LCDTFT	(1 << 5) ///< LCD is TFT (0 = LCD is an STN display, use gray scaler / 1 = LCD is TFT, do not use gray scaler)
#define PL110_CLCD_CONTROL_LCDMONO8	(1 << 6) ///< Monochrome LCD has an 8-bit interface (0 = mono LCD uses 4-bit interface / 1 = mono LCD uses 8-bit interface)
#define PL110_CLCD_CONTROL_LCDDUAL	(1 << 7) ///< LCD interface is dual panel STN (0 = single panel LCD is in use / 1 = dual panel LCD is in use)
#define PL110_CLCD_CONTROL_BGR	(1 << 8) ///< RGB or BGR format selection (0 = RGB normal output / 1 = BGR red and blue swapped.)
#define PL110_CLCD_CONTROL_BEBO	(1 << 9) ///< Big-endian byte order (0 = little-endian byte order / 1 = big-endian byte order)
#define PL110_CLCD_CONTROL_BEPO	(1 << 10) ///< Big-endian pixel ordering within a byte (0 = little-endian pixel ordering within a byte / 1= big-endian pixel ordering within a byte)
#define PL110_CLCD_CONTROL_LCDPWR	(1 << 11) ///< LCD power enable
#define PL110_CLCD_CONTROL_LCDVCOMP_VSYNC	(0 << 12) ///< Generate interrupt at: 00 = start of vertical synchronization
#define PL110_CLCD_CONTROL_LCDVCOMP_BPORCH	(1 << 12) ///<                        01 = start of back porch
#define PL110_CLCD_CONTROL_LCDVCOMP_VIDEO	(2 << 12) ///<                        10 = start of active video
#define PL110_CLCD_CONTROL_LCDVCOMP_FPORCH	(3 << 12) ///<                        11 = start of front porch
#define PL110_CLCD_CONTROL_LDMAFIFOTIME	(1 << 15) ///< Unknown
#define PL110_CLCD_CONTROL_WATERMARK	(1 << 16) ///< LCD DMA FIFO Watermark level

/** PL110 control constants */
#define PL110_CONTROL_VGA	PL110_CLCD_CONTROL_LCDTFT | PL110_CLCD_CONTROL_LCDVCOMP_BPORCH
#define PL110_CONTROL_SVGA	PL110_CLCD_CONTROL_LCDTFT | PL110_CLCD_CONTROL_LCDVCOMP_BPORCH

/** PL110 timing0 constants */
#define PL110_TIMING0_VGA	0x3F1F3F9C
#define PL110_TIMING0_SVGA	0x1313A4C4

/** PL110 timing1 constants */
#define PL110_TIMING1_VGA	0x090B61DF
#define PL110_TIMING1_SVGA	0x0505F657

/** PL110 timing2 constants */
#define PL110_TIMING2_VGA	0x067F1800
#define PL110_TIMING2_SVGA	0x071F1800

/** PL110 specific types */
/** Layout of the PL110 registers (See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0161e/I904421.html) */
typedef struct _PL110_CLCD_REGISTERS PL110_CLCD_REGISTERS;
struct _PL110_CLCD_REGISTERS
{
	uint32_t timing0; ///< Horizontal Axis Panel Control Register
	uint32_t timing1; ///< Vertical Axis Panel Control Register
	uint32_t timing2; ///< Clock and Signal Polarity Control Register
	uint32_t timing3; ///< Line End Control Register
	uint32_t upbase; ///< Upper Panel Frame Base Address Registers
	uint32_t lpbase; ///< Lower Panel Frame Base Address Registers
	uint32_t control; ///< Control Register
	uint32_t imsc; ///< Interrupt Mask Set/Clear Register
	uint32_t ris; ///< Raw Interrupt Status Register
	uint32_t mis; ///< Masked Interrupt Status Register
	uint32_t icr; ///< Interrupt Clear Register
	uint32_t upcurr; ///< Upper Panel Current Address Value Registers
	uint32_t lpcurr; ///< Lower Panel Current Address Value Registers

};


typedef struct _PL110_FRAMEBUFFER PL110_FRAMEBUFFER;
struct _PL110_FRAMEBUFFER
{
	// Framebuffer Properties
	FRAMEBUFFER_DEVICE framebuffer;
	// PL110 Properties
	uint32_t mode; ///< PL110 framebuffer mode (eg PL110_MODE_TFT)
	uint32_t depth; ///< Framebuffer color depth (eg FRAMEBUFFER_DEPTH_16)
	uint32_t width; ///< Framebuffer width in pixels
	uint32_t height; ///< Framebuffer height in pixels
	uint32_t rotation; ///< Framebuffer rotation (eg FRAMEBUFFER_ROTATION_180)
	// Driver Properties
	uint32_t control; ///< Preset Control register value
	uint32_t timing0; ///< Preset Timing0 register value
	uint32_t timing1; ///< Preset Timing1 register value
	uint32_t timing2; ///< Preset Timing2 register value
	uint32_t timing3; ///< Preset Timing2 register value
	PL110_CLCD_REGISTERS *registers; ///< PL110 registers
};

/** PL110 Functions */

/**
 * @brief Create, register and allocate a new PL110 Framebuffer device which can be accessed using the framebuffer API
 * @param Address The address of the PL110 registers
 * @param Name The text description of this device which will show in the device list (Optional)
 * @param Rotation The rotation value for the framebuffer device (eg FRAMEBUFFER_ROTATION_180)
 * @param Width The width of the framebuffer in pixels
 * @param Height The height of the framebuffer in pixels
 * @param Depth The color depth (bits per pixel) for the framebuffer (eg FRAMEBUFFER_DEPTH_16)
 * @return Pointer to the new Framebuffer device or nil if the framebuffer device could not be created
 */
FRAMEBUFFER_DEVICE * STDCALL pl110_framebuffer_create_vga(size_t address, char *name, uint32_t rotation, uint32_t width, uint32_t height, uint32_t depth);

/**
 * @brief Create, register and allocate a new PL110 Framebuffer device which can be accessed using the framebuffer API
 * @param Address The address of the PL110 registers
 * @param Name The text description of this device which will show in the device list (Optional)
 * @param Rotation The rotation value for the framebuffer device (eg FRAMEBUFFER_ROTATION_180)
 * @param Width The width of the framebuffer in pixels
 * @param Height The height of the framebuffer in pixels
 * @param Depth The color depth (bits per pixel) for the framebuffer (eg FRAMEBUFFER_DEPTH_16)
 * @return Pointer to the new Framebuffer device or nil if the framebuffer device could not be created
 */
FRAMEBUFFER_DEVICE * STDCALL pl110_framebuffer_create_svga(size_t address, char *name, uint32_t rotation, uint32_t width, uint32_t height, uint32_t depth);

/**
 * @brief Release, deregister and destroy a PL110 Framebuffer device created by this driver
 * @param Framebuffer The Framebuffer device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL pl110_framebuffer_destroy(FRAMEBUFFER_DEVICE *framebuffer);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PL110_H
