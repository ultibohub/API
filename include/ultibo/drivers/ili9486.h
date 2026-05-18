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
#ifndef _ULTIBO_ILI9486_H
#define _ULTIBO_ILI9486_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/spi.h"
#include "ultibo/framebuffer.h"
#include "ultibo/tftframebuffer.h"

/** ILI9486 specific constants */
#define ILI9486_FRAMEBUFFER_DESCRIPTION	"ILITEK ILI9486 TFT LCD" ///< Description of ILI9486 device

/** ILI9486 SPI constants */
#define ILI9486_SPI_RATE	32000000 ///< Default SPI clock rate

/** ILI9486 Command constants */
#define ILI9486_CMD_NOP	0x00 ///< 8.2.1. NOP: No Operation
#define ILI9486_CMD_SWRESET	0x01 ///< 8.2.2. SWRESET: Software Reset

#define ILI9486_CMD_SLPOUT	0x11 ///< 8.2.13. SLPOUT: Sleep Out (This command turns off sleep mode)

#define ILI9486_CMD_DISPOFF	0x28 ///< 8.2.18. DISPOFF: Display OFF (This command is used to enter into DISPLAY OFF mode. In this mode, the output from Frame Memory is disabled and blank page inserted)
#define ILI9486_CMD_DISPON	0x29 ///< 8.2.19. DISPON: Display ON (This command is used to recover from DISPLAY OFF mode. Output from the Frame Memory is enabled)

#define ILI9486_CMD_CASET	0x2A ///< 8.2.20. CASET: Column Address Set (This command is used to define area of frame memory where MCU can access)
#define ILI9486_CMD_PASET	0x2B ///< 8.2.21. PASET: Page Address Set (This command is used to define area of frame memory where MCU can access)
#define ILI9486_CMD_RAMWR	0x2C ///< 8.2.22. Memory Write (This command is used to transfer data from MCU to frame memory)

#define ILI9486_CMD_MADCTL	0x36 ///< 8.2.28. MADCTL: Memory Access Control (This command defines read/write scanning direction of frame memory)

#define ILI9486_CMD_COLMOD	0x3A ///< 8.2.32. COLMOD: Pixel Format Set (This command sets the pixel format for the RGB image data used by the interface)

#define ILI9486_CMD_IFMODE	0xB0 ///< 8.2.50. IFMODE : Interface Mode Control

#define ILI9486_CMD_FRMCTR1	0xB1 ///< 8.2.51. FRMCTR1: Frame Rate Control (In Normal Mode/Full Colors)

#define ILI9486_CMD_DISCTRL	0xB6 ///< 8.2.56. DISCTRL: Display Function Control

#define ILI9486_CMD_PWCTRL1	0xC0 ///< 8.2.58. PWCTRL1: Power Control 1
#define ILI9486_CMD_PWCTRL2	0xC1 ///< 8.2.59. PWCTRL2: Power Control 2
#define ILI9486_CMD_PWCTRL3	0xC2 ///< 8.2.60. PWCTRL3: Power Control 3 (For Normal Mode)

#define ILI9486_CMD_VMCTRL1	0xC5 ///< 8.2.63. VMCTRL1: VCOM Control 1

#define ILI9486_CMD_PGAMCTRL	0xE0 ///< 8.2.77. PGAMCTRL: Positive Gamma Correction (Set the gray scale voltage to adjust the gamma characteristics of the TFT panel)
#define ILI9486_CMD_NGAMCTRL	0xE1 ///< 8.2.78. NGAMCTRL: Negative Gamma Correction (Set the gray scale voltage to adjust the gamma characteristics of the TFT panel)
#define ILI9486_CMD_DGAMCTRL	0xE2 ///< 8.2.79. DGAMCTRL: Digital Gamma Control 1 (Gamma Macro-adjustment registers for red gamma curve)

/** ILI9486 Memory access control constants (See ILI9486 datasheet 8.2.28. Memory Access Control) */
#define ILI9486_CMD_MADCTL_MY	0x80 ///< Row Address Order
#define ILI9486_CMD_MADCTL_MX	0x40 ///< Column Address Order
#define ILI9486_CMD_MADCTL_MV	0x20 ///< Row / Column Exchange
#define ILI9486_CMD_MADCTL_ML	0x10 ///< Vertical Refresh Order
#define ILI9486_CMD_MADCTL_RGB	0x00 ///< Colour selector switch control(0=RGB colour filter panel, 1=BGR colour filter panel)
#define ILI9486_CMD_MADCTL_BGR	0x08
#define ILI9486_CMD_MADCTL_MH	0x04 ///< Horizontal Refresh Order

/** ILI9486 specific types */
typedef struct _ILI9486_FRAMEBUFFER ILI9486_FRAMEBUFFER;
struct _ILI9486_FRAMEBUFFER
{
	// TFT Properties
	TFT_FRAMEBUFFER tft;
	// ILI9486 Properties
};

/** ILI9486 Functions */

/**
 * @brief Create, register and allocate a new ILI9486 Framebuffer device which can be accessed using the framebuffer API
 * @param SPI The SPI device that this ILI9486 is connected to
 * @param ChipSelect The SPI chip select to use when communicating with this device
 * @param Name The text description of this device which will show in the device list (Optional)
 * @param Rotation The rotation value for the framebuffer device (eg FRAMEBUFFER_ROTATION_180)
 * @param Width The width of the framebuffer in pixels
 * @param Height The height of the framebuffer in pixels
 * @param RST GPIO pin information for the Reset pin (Optional)
 * @param DC GPIO pin information for the Data/Command pin
 * @param BL GPIO pin information for the Backlight pin (Optional)
 * @return Pointer to the new Framebuffer device or nil if the framebuffer device could not be created
 */
FRAMEBUFFER_DEVICE * STDCALL ili9486_framebuffer_create(SPI_DEVICE *spi, uint16_t chipselect, char *name, uint32_t rotation, uint32_t width, uint32_t height, GPIO_INFO *rst, GPIO_INFO *dc, GPIO_INFO *bl);

/**
 * @brief Release, deregister and destroy an ILI9486 Framebuffer device created by this driver
 * @param Framebuffer The Framebuffer device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL ili9486_framebuffer_destroy(FRAMEBUFFER_DEVICE *framebuffer);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_ILI9486_H
