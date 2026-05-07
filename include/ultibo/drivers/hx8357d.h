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
#ifndef _ULTIBO_HX8357D_H
#define _ULTIBO_HX8357D_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/spi.h"
#include "ultibo/framebuffer.h"
#include "ultibo/tftframebuffer.h"

/** HX8357D specific constants */
#define HX8357D_FRAMEBUFFER_DESCRIPTION	"Himax HX8357D TFT LCD" ///< Description of HX8357D device

/** HX8357D SPI constants */
#define HX8357D_SPI_RATE	32000000 ///< Default SPI clock rate

/** HX8357D Command constants (See HX8357-D datasheet) */
#define HX8357D_CMD_NOP	0x00 ///< 6.2.1 NOP: No Operation
#define HX8357D_CMD_SWRESET	0x01 ///< 6.2.2 SWRESET: Software reset

#define HX8357D_CMD_RDDIDIF	0x04 ///< 6.2.3 Read display identification information

#define HX8357D_CMD_SLPIN	0x10 ///< 6.2.14 SLPIN: Sleep in (Enter the minimum power consumption mode) (Wait 120ms)
#define HX8357D_CMD_SLPOUT	0x11 ///< 6.2.15 SLPOUT: Sleep out (Wait 5ms)

#define HX8357D_CMD_PTLON	0x12 ///< 6.2.16 PTLON: Partial mode on (This command turns on partial mode. The partial mode window is described by the Partial Area command (30H))
#define HX8357D_CMD_NORON	0x13 ///< 6.2.17 NORON: Normal display mode on (This command returns the display to normal mode)

#define HX8357D_CMD_INVOFF	0x20 ///< 6.2.18 INVOFF: Display inversion off (This command is used to recover from display inversion mode)
#define HX8357D_CMD_INVON	0x21 ///< 6.2.19 INVON: Display inversion on (This command is used to enter into display inversion mode)

#define HX8357D_CMD_ALLPOFF	0x22 ///< 6.2.20 All pixel off (This command turns the display panel black in ‘Sleep Out’ mode)
#define HX8357D_CMD_ALLPON	0x23 ///< 6.2.21 All pixel on (This command turns the display panel white in ‘Sleep Out‘ mode)

#define HX8357D_CMD_DISPOFF	0x28 ///< 6.2.23 DISPOFF: Display off (This command is used to enter into DISPLAY OFF mode. In this mode, the output from Frame Memory is disabled and blank page inserted)
#define HX8357D_CMD_DISPON	0x29 ///< 6.2.24 DISPON: Display on (This command is used to recover from DISPLAY OFF mode. Output from the Frame Memory is enabled)

#define HX8357D_CMD_CASET	0x2A ///< 6.2.25 CASET: Column address set (This command is used to define area of frame memory where MCU can access)
#define HX8357D_CMD_PASET	0x2B ///< 6.2.26 PASET: Page address set (This command is used to define area of frame memory where MCU can access)
#define HX8357D_CMD_RAMWR	0x2C ///< 6.2.27 RAMWR: Memory write (This command is used to transfer data from MCU to frame memory)
#define HX8357D_CMD_RAMRD	0x2E ///< 6.2.28 RAMRD: Memory read (This command is used to transfer data from frame memory to MCU)

#define HX8357D_CMD_TEON	0x35 ///< 6.2.32 TEON: Tearing effect line on

#define HX8357D_CMD_MADCTL	0x36 ///< 6.2.33 MADCTL: Memory access control
#define HX8357D_CMD_COLMOD	0x3A ///< 6.2.37 COLMOD: Interface pixel format

#define HX8357D_CMD_TESL	0x44 ///< 6.2.40 TESL: Set tear scan line

#define HX8357D_CMD_SETOSC	0xB0 ///< 6.2.73 SETOSC: set internal oscillator
#define HX8357D_CMD_SETPOWER	0xB1 ///< 6.2.74 SETPOWER: set power control
#define HX8357D_CMD_SETRGB	0xB3 ///< 6.2.76 SETRGB: set RGB interface
#define HX8357D_CMD_SETCYC	0xB4 ///< 6.2.77 SETCYC: set display cycle register
#define HX8357D_CMD_SETCOM	0xB6 ///< 6.2.79 SETCOM: set VCOM voltage related register

#define HX8357D_CMD_SETEXTC	0xB9 ///< 6.2.81 SETEXTC: enable extension command (Enable: FFh,83h,57h / Disable: xxh,xxh,xxh)

#define HX8357D_CMD_SETSTBA	0xC0 ///< 6.2.82 SETSTBA: Set Source Option

#define HX8357D_CMD_SETPANEL	0xCC ///< 6.2.87 SETPanel: set panel characteristic

#define HX8357D_CMD_SETGAMMA	0xE0 ///< 6.2.88 SETGamma: set gamma curve

/** HX8357D Memory access control constants (See HX8357-D datasheet 6.2.33 Memory access control) */
#define HX8357D_CMD_MADCTL_MY	0x80 ///< Page Address Order
#define HX8357D_CMD_MADCTL_MX	0x40 ///< Column Address Order
#define HX8357D_CMD_MADCTL_MV	0x20 ///< Page / Column Selection
#define HX8357D_CMD_MADCTL_ML	0x10 ///< Vertical Order
#define HX8357D_CMD_MADCTL_RGB	0x00 ///< Colour selector switch control(0=RGB colour filter panel, 1=BGR colour filter panel)
#define HX8357D_CMD_MADCTL_BGR	0x08
#define HX8357D_CMD_MADCTL_SS	0x04 ///< Horizontal Order
#define HX8357D_CMD_MADCTL_MH	HX8357D_CMD_MADCTL_SS

/** HX8357D specific types */
typedef struct _HX8357D_FRAMEBUFFER HX8357D_FRAMEBUFFER;
struct _HX8357D_FRAMEBUFFER
{
	// TFT Properties
	TFT_FRAMEBUFFER tft;
	// HX8357D Properties
};

/** HX8357D Functions */
FRAMEBUFFER_DEVICE * STDCALL hx8357d_framebuffer_create(SPI_DEVICE *spi, uint16_t chipselect, char *name, uint32_t rotation, uint32_t width, uint32_t height, GPIO_INFO *rst, GPIO_INFO *dc, GPIO_INFO *bl);

uint32_t STDCALL hx8357d_framebuffer_destroy(FRAMEBUFFER_DEVICE *framebuffer);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_HX8357D_H
