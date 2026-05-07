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
#ifndef _ULTIBO_ST77XX_H
#define _ULTIBO_ST77XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/spi.h"
#include "ultibo/framebuffer.h"

/** ST77XX specific constants */
#define ST77XX_FRAMEBUFFER_DESCRIPTION	"ST77XX TFT LCD DRIVER" ///< Description of ST77XX device

/** ST77XX SPI constants */
#define ST77XX_SPI_RATE	32000000 ///< Default SPI clock rate

#define ST_CMD_DELAY	0x80 ///<  special signifier for command lists

/** ST77XX specific commands used in init */
#define ST77XX_NOP	0x00 ///< 8.2.1. NOP: No Operation
#define ST77XX_SWRESET	0x01 ///< 8.2.2. SWRESET: Software Reset
#define ST77XX_RDDID	0x04 ///< new_cmd
#define ST77XX_RDDST	0x09 ///< new_cmd

#define ST77XX_SLPIN	0x10 ///< new_cmd
#define ST77XX_SLPOUT	0x11 ///< 8.2.12. SLPOUT: Sleep Out (This command turns off sleep mode)
#define ST77XX_PTLON	0x12 ///< new_cmd
#define ST77XX_NORON	0x13 ///< new_cmd

#define ST77XX_INVOFF	0x20 ///< new_cmd
#define ST77XX_INVON	0x21 ///< new_cmd
#define ST77XX_GAMSET	0x26 ///< 8.2.17. GAMSET: Gamma Set (This command is used to select the desired Gamma curve for the current display)
#define ST77XX_DISPOFF	0x28 ///< 8.2.18. DISPOFF: Display OFF (This command is used to enter into DISPLAY OFF mode. In this mode, the output from Frame Memory is disabled and blank page inserted)
#define ST77XX_DISPON	0x29 ///< 8.2.19. DISPON: Display ON (This command is used to recover from DISPLAY OFF mode. Output from the Frame Memory is enabled)
#define ST77XX_CASET	0x2A ///< 8.2.20. CASET: Column Address Set (This command is used to define area of frame memory where MCU can access)
#define ST77XX_RASET	0x2B ///< 8.2.21. PASET: Page Address Set (This command is used to define area of frame memory where MCU can access)
#define ST77XX_RAMWR	0x2C ///< 8.2.22. Memory Write (This command is used to transfer data from MCU to frame memory)
#define ST77XX_RGBSET	0x2D ///< new_cmd
#define ST77XX_RAMRD	0x2E ///< new_cmd

#define ST77XX_RDDPM	0x0A ///< new_cmd
#define ST77XX_RDD_MADCTL	0x0B ///< new_cmd
#define ST77XX_RDD_COLMOD	0x0C ///< new_cmd
#define ST77XX_RDDIM	0x0D ///< new_cmd
#define ST77XX_RDDSM	0x0E ///< new_cmd
#define ST77XX_RDDSR	0x0F ///< new_cmd

#define ST77XX_PTLAR	0x30 ///< new_cmd
#define ST77XX_VSCRDEF	0x33 ///< new_cmd
#define ST77XX_TEOFF	0x34 ///< new_cmd
#define ST77XX_TEON	0x35 ///< new_cmd
#define ST77XX_MADCTL	0x36 ///< 8.2.29. MADCTL: Memory Access Control (This command defines read/write scanning direction of frame memory)
#define ST77XX_IDMOFF	0x38 ///< new_cmd
#define ST77XX_IDMON	0x39 ///< new_cmd
#define ST77XX_RAMWRC	0x3C ///< new_cmd
#define ST77XX_RAMRDC	0x3E ///< new_cmd
#define ST77XX_COLMOD	0x3A ///< 8.2.33. COLMOD: Pixel Format Set (This command sets the pixel format for the RGB image data used by the interface)


/** ST77XX Memory access control constants (See ST77XX datasheet 8.2.29. Memory Access Control) */
#define ST77XX_MADCTL_MY	0x80 ///< Row Address Order
#define ST77XX_MADCTL_MX	0x40 ///< Column Address Order
#define ST77XX_MADCTL_MV	0x20 ///< Row / Column Exchange
#define ST77XX_MADCTL_ML	0x10 ///< Row / Column Exchange
#define ST77XX_MADCTL_MH	0x04 ///< Horizontal Refresh Order
#define ST77XX_MADCTL_RGB	0x00 ///< Colour selector switch control(0=RGB colour filter panel, 1=BGR colour filter panel)
#define ST77XX_MADCTL_BGR	0x08

#define ST77XX_RAMCTRL	0xB0 ///< new_cmd
#define ST77XX_RGBCTRL	0xB1 ///< new_cmd
#define ST77XX_PORCTRL	0xB2 ///< new_cmd
#define ST77XX_FRCTR1	0xB3 ///< 8.3.2. FRCTR1: Frame Rate Control (In Normal Mode/Full Colors)
#define ST77XX_PARCTRL	0xB5 ///< new_cmd
#define ST77XX_GCTRL	0xB7 ///< new_cmd
#define ST77XX_GTADJ	0xB8 ///< new_cmd
#define ST77XX_DGMEN	0xBA ///< new_cmd
#define ST77XX_VCOMS	0xBB ///< new_cmd
#define ST77XX_DISCTRL	0xB6 ///< 8.3.7. DISCTRL: Display Function Control

#define ST77XX_LCMCTRL	0xC0 ///< new_cmd
#define ST77XX_IDSET	0xC1 ///< new_cmd
#define ST77XX_VDVVRHEN	0xC2 ///< new_cmd
#define ST77XX_VRHS	0xC3 ///< new_cmd
#define ST77XX_VDVSET	0xC4 ///< new_cmd
#define ST77XX_VCMOFSET	0xC5 ///< new_cmd
#define ST77XX_FRCTR2	0xC6 ///< new_cmd
#define ST77XX_CABCCTRL	0xC7 ///< new_cmd
#define ST77XX_REGSEL1	0xC8 ///< new_cmd
#define ST77XX_REGSEL2	0xCA ///< new_cmd
#define ST77XX_PWMFRSEL	0xCC ///< new_cmd

#define ST77XX_PWCTRL1	0xD0 ///< 8.3.16. PWCTRL1: Power Control 1
#define ST77XX_VAPVANEN	0xD2 ///< new_cmd
#define ST77XX_CMD2EN	0xDF ///< new_cmd

#define ST77XX_VMCTRL1	0xC5 ///< 8.3.21. VMCTRL1: VCOM Control 1
#define ST77XX_VMCTRL2	0xC7 ///< 8.3.22. VMCTRL2: VCOM Control 2

#define ST77XX_PGAMCTRL	0xE0 ///< new_cmd
#define ST77XX_NGAMCTRL	0xE1 ///< new_cmd
#define ST77XX_DGMLUTR	0xE2 ///< new_cmd
#define ST77XX_DGMLUTB	0xE3 ///< new_cmd
#define ST77XX_GATECTRL	0xE4 ///< new_cmd
#define ST77XX_SPI2EN	0xE7 ///< new_cmd
#define ST77XX_PWCTRL2	0xE8 ///< new_cmd
#define ST77XX_EQCTRL	0xE9 ///< new_cmd
#define ST77XX_PROMCTRL	0xEC ///< new_cmd

#define ST77XX_PROMEN	0xFA ///< new_cmd
#define ST77XX_NVMSET	0xFC ///< new_cmd
#define ST77XX_PROMACT	0xFE ///< new_cmd

#define ST77XX_COLOR_MODE_16bit	0x55
#define ST77XX_COLOR_MODE_18bit	0x66

/** ST77XX specific types */
typedef struct _ST77XX_FRAMEBUFFER ST77XX_FRAMEBUFFER;
struct _ST77XX_FRAMEBUFFER
{
	// TFT Properties
	TFT_FRAMEBUFFER tft;
	// ST77XX Properties
};

/** ST77XX Functions */
FRAMEBUFFER_DEVICE * STDCALL st77xx_framebuffer_create(SPI_DEVICE *spi, uint16_t chipselect, char *name, uint32_t rotation, uint32_t width, uint32_t height, uint32_t colstart, GPIO_INFO *rst, GPIO_INFO *dc, GPIO_INFO *bl);

uint32_t STDCALL st77xx_framebuffer_destroy(FRAMEBUFFER_DEVICE *framebuffer);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_ST77XX_H
