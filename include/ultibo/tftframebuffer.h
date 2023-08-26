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
#ifndef _ULTIBO_TFTFRAMEBUFFER_H
#define _ULTIBO_TFTFRAMEBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/framebuffer.h"
#include "ultibo/gpio.h"
#include "ultibo/spi.h"

/* ============================================================================== */
/* TFTFramebuffer specific constants */
#define TFT_FRAMEBUFFER_FRAME_RATE_DEFAULT	20 // Default frame rate of 20 frames per second refresh

/* ============================================================================== */
/* TFTFramebuffer specific types */
typedef struct _TFT_FRAMEBUFFER TFT_FRAMEBUFFER;

/* TFTFramebuffer Device Methods */
typedef uint32_t STDCALL (*tft_framebuffer_initialize_proc)(TFT_FRAMEBUFFER *framebuffer, FRAMEBUFFER_PROPERTIES *defaults);
typedef uint32_t STDCALL (*tft_framebuffer_deinitialize_proc)(TFT_FRAMEBUFFER *framebuffer);

typedef uint32_t STDCALL (*tft_framebuffer_get_defaults_proc)(TFT_FRAMEBUFFER *framebuffer, FRAMEBUFFER_PROPERTIES *properties, FRAMEBUFFER_PROPERTIES *defaults);
typedef uint32_t STDCALL (*tft_framebuffer_set_write_address_proc)(TFT_FRAMEBUFFER *framebuffer, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

typedef uint32_t STDCALL (*tft_framebuffer_write_memory_proc)(TFT_FRAMEBUFFER *framebuffer, size_t address, uint32_t size);

/* TFTFramebuffer Device */
struct _TFT_FRAMEBUFFER
{
	// Framebuffer Properties
	FRAMEBUFFER_DEVICE framebuffer;
	// TFT Properties
	SPI_DEVICE *spi; // The SPI device this Framebuffer is connected to
	uint16_t chipselect; // The SPI chip select of the device
	GPIO_INFO rst; // The GPIO information for the reset line
	GPIO_INFO dc; // The GPIO information for the data/command line
	GPIO_INFO bl; // The GPIO information for the backlight line
	tft_framebuffer_initialize_proc initialize; // A device specific Initialize method (Optional)
	tft_framebuffer_deinitialize_proc deinitialize; // A device specific Deinitialize method (Optional)
	tft_framebuffer_get_defaults_proc getdefaults; // A device specific GetDefaults method (Mandatory)
	tft_framebuffer_set_write_address_proc setwriteaddress; // A device specific SetWriteAddress method (Mandatory)
	tft_framebuffer_write_memory_proc writememory; // A device specific WriteMemory method (Mandatory)
	// Driver Properties
	uint32_t width; // Framebuffer Width in Pixels
	uint32_t height; // Framebuffer Height in Pixels
	uint32_t rotation; // Framebuffer Rotation (eg FRAMEBUFFER_ROTATION_180)
	uint32_t dirtyy1; // First line of dirty region (or Height - 1 if none dirty)
	uint32_t dirtyy2; // Last line of dirty region (or 0 if none dirty)
	LONGBOOL ready; // If True timer should be enabled during Mark operation
	MUTEX_HANDLE lock; // Lock for dirty region redraw
	TIMER_HANDLE timer; // Handle for dirty region redraw timer
	uint32_t framerate; // Frame rate for display refresh (in Frames Per Second)
	uint32_t transfersize; // Maximum transfer size for the SPI device (or -1 if No Maximum)
};

/* ============================================================================== */
/* TFTFramebuffer Functions */
uint32_t STDCALL tft_framebuffer_allocate(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);
uint32_t STDCALL tft_framebuffer_release(FRAMEBUFFER_DEVICE *framebuffer);

uint32_t STDCALL tft_framebuffer_mark(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t flags);
uint32_t STDCALL tft_framebuffer_commit(FRAMEBUFFER_DEVICE *framebuffer, size_t address, uint32_t size, uint32_t flags);

void STDCALL tft_framebuffer_update_display(TFT_FRAMEBUFFER *framebuffer);

/* ============================================================================== */
/* TFTFramebuffer Helper Functions */

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_TFTFRAMEBUFFER_H