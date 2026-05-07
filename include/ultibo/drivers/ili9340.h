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
#ifndef _ULTIBO_ILI9340_H
#define _ULTIBO_ILI9340_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/spi.h"
#include "ultibo/framebuffer.h"
#include "ultibo/tftframebuffer.h"

/** ILI9340 specific constants */
#define ILI9340_FRAMEBUFFER_DESCRIPTION	"ILITEK ILI9340 TFT LCD" ///< Description of ILI9340 device

/** ILI9340 SPI constants */
#define ILI9340_SPI_RATE	32000000 ///< Default SPI clock rate

/** ILI9340 Command constants */
#define ILI9340_CMD_NOP	0x00 ///< 8.2.1. NOP: No Operation
#define ILI9340_CMD_SWRESET	0x01 ///< 8.2.2. SWRESET: Software Reset

#define ILI9340_CMD_SLPOUT	0x11 ///< 8.2.12. SLPOUT: Sleep Out (This command turns off sleep mode)

#define ILI9340_CMD_GAMSET	0x26 ///< 8.2.17. GAMSET: Gamma Set (This command is used to select the desired Gamma curve for the current display)

#define ILI9340_CMD_DISPOFF	0x28 ///< 8.2.18. DISPOFF: Display OFF (This command is used to enter into DISPLAY OFF mode. In this mode, the output from Frame Memory is disabled and blank page inserted)
#define ILI9340_CMD_DISPON	0x29 ///< 8.2.19. DISPON: Display ON (This command is used to recover from DISPLAY OFF mode. Output from the Frame Memory is enabled)

#define ILI9340_CMD_CASET	0x2A ///< 8.2.20. CASET: Column Address Set (This command is used to define area of frame memory where MCU can access)
#define ILI9340_CMD_PASET	0x2B ///< 8.2.21. PASET: Page Address Set (This command is used to define area of frame memory where MCU can access)
#define ILI9340_CMD_RAMWR	0x2C ///< 8.2.22. Memory Write (This command is used to transfer data from MCU to frame memory)

#define ILI9340_CMD_MADCTL	0x36 ///< 8.2.29. MADCTL: Memory Access Control (This command defines read/write scanning direction of frame memory)

#define ILI9340_CMD_COLMOD	0x3A ///< 8.2.33. COLMOD: Pixel Format Set (This command sets the pixel format for the RGB image data used by the interface)

#define ILI9340_CMD_FRMCTR1	0xB1 ///< 8.3.2. FRMCTR1: Frame Rate Control (In Normal Mode/Full Colors)

#define ILI9340_CMD_DISCTRL	0xB6 ///< 8.3.7. DISCTRL: Display Function Control

#define ILI9340_CMD_PWCTRL1	0xC0 ///< 8.3.16. PWCTRL1: Power Control 1
#define ILI9340_CMD_PWCTRL2	0xC1 ///< 8.3.17. PWCTRL2: Power Control 2

#define ILI9340_CMD_VMCTRL1	0xC5 ///< 8.3.21. VMCTRL1: VCOM Control 1
#define ILI9340_CMD_VMCTRL2	0xC7 ///< 8.3.22. VMCTRL2: VCOM Control 2

#define ILI9340_CMD_PGAMCTRL	0xE0 ///< 8.3.27. PGAMCTRL: Positive Gamma Correction (Set the gray scale voltage to adjust the gamma characteristics of the TFT panel)
#define ILI9340_CMD_NGAMCTRL	0xE1 ///< 8.3.28. NGAMCTRL: Negative Gamma Correction (Set the gray scale voltage to adjust the gamma characteristics of the TFT panel)

/** ILI9340 Memory access control constants (See ILI9340 datasheet 8.2.29. Memory Access Control) */
#define ILI9340_CMD_MADCTL_MY	0x80 ///< Row Address Order
#define ILI9340_CMD_MADCTL_MX	0x40 ///< Column Address Order
#define ILI9340_CMD_MADCTL_MV	0x20 ///< Row / Column Exchange
#define ILI9340_CMD_MADCTL_ML	0x10 ///< Vertical Refresh Order
#define ILI9340_CMD_MADCTL_RGB	0x00 ///< Colour selector switch control(0=RGB colour filter panel, 1=BGR colour filter panel)
#define ILI9340_CMD_MADCTL_BGR	0x08
#define ILI9340_CMD_MADCTL_MH	0x04 ///< Horizontal Refresh Order

/** ILI9340 specific types */
typedef struct _ILI9340_FRAMEBUFFER ILI9340_FRAMEBUFFER;
struct _ILI9340_FRAMEBUFFER
{
	// TFT Properties
	TFT_FRAMEBUFFER tft;
	// ILI9340 Properties
};

/** ILI9340 Functions */
FRAMEBUFFER_DEVICE * STDCALL ili9340_framebuffer_create(SPI_DEVICE *spi, uint16_t chipselect, char *name, uint32_t rotation, uint32_t width, uint32_t height, GPIO_INFO *rst, GPIO_INFO *dc, GPIO_INFO *bl);

uint32_t STDCALL ili9340_framebuffer_destroy(FRAMEBUFFER_DEVICE *framebuffer);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_ILI9340_H
