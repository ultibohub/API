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
#ifndef _ULTIBO_FRAMEBUFFER_H
#define _ULTIBO_FRAMEBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/** Framebuffer specific constants */
#define FRAMEBUFFER_NAME_PREFIX	"Framebuffer" ///< Name prefix for Framebuffer Devices

/** Framebuffer Device Types */
#define FRAMEBUFFER_TYPE_NONE	0
#define FRAMEBUFFER_TYPE_HARDWARE	1
#define FRAMEBUFFER_TYPE_VIRTUAL	2

#define FRAMEBUFFER_TYPE_MAX	2

/** Framebuffer Device States */
#define FRAMEBUFFER_STATE_DISABLED	0
#define FRAMEBUFFER_STATE_ENABLED	1

#define FRAMEBUFFER_STATE_MAX	1

/** Framebuffer Cursor States */
#define FRAMEBUFFER_CURSOR_DISABLED	0
#define FRAMEBUFFER_CURSOR_ENABLED	1

/** Framebuffer Device Flags */
#define FRAMEBUFFER_FLAG_NONE	0x00000000
#define FRAMEBUFFER_FLAG_DMA	0x00000001 ///< If set the framebuffer supports DMA for read/write operations
#define FRAMEBUFFER_FLAG_MARK	0x00000002 ///< If set the framebuffer requires mark after write operations
#define FRAMEBUFFER_FLAG_COMMIT	0x00000004 ///< If set the framebuffer requires commit after write operations
#define FRAMEBUFFER_FLAG_BLANK	0x00000008 ///< If set the framebuffer supports blanking the screen
#define FRAMEBUFFER_FLAG_CACHED	0x00000010 ///< If set framebuffer is in cached memory and cache cleaning should be used
#define FRAMEBUFFER_FLAG_SWAP	0x00000020 ///< If set framebuffer requires byte order of colors to be reversed (BGR <-> RGB)
#define FRAMEBUFFER_FLAG_BACKLIGHT	0x00000040 ///< If set the framebuffer supports setting the backlight brightness
#define FRAMEBUFFER_FLAG_VIRTUAL	0x00000080 ///< If set the framebuffer supports virtual width and height
#define FRAMEBUFFER_FLAG_OFFSETX	0x00000100 ///< If set the framebuffer supports virtual offset X (Horizontal Pan/Flip etc)
#define FRAMEBUFFER_FLAG_OFFSETY	0x00000200 ///< If set the framebuffer supports virtual offset Y (Vertical Pan/Flip etc)
#define FRAMEBUFFER_FLAG_SYNC	0x00000400 ///< If set the framebuffer supports waiting for vertical sync
#define FRAMEBUFFER_FLAG_CURSOR	0x00000800 ///< If set the framebuffer supports a hardware mouse cursor

/** Framebuffer Transfer Flags */
#define FRAMEBUFFER_TRANSFER_NONE	0x00000000
#define FRAMEBUFFER_TRANSFER_DMA	0x00000001 ///< Use DMA for transfer operations (Note: Buffers must be DMA compatible)

/** Framebuffer specific types */
typedef struct _FRAMEBUFFER_PALETTE FRAMEBUFFER_PALETTE;
struct _FRAMEBUFFER_PALETTE
{
	uint32_t start; ///< The number of the first valid entry in the palette
	uint32_t count; ///< The total number of entries in the palette
	uint32_t entries[256]; ///< The palette entries in COLOR_FORMAT_DEFAULT format
};

typedef struct _FRAMEBUFFER_PROPERTIES FRAMEBUFFER_PROPERTIES;
struct _FRAMEBUFFER_PROPERTIES
{
	uint32_t flags; ///< Framebuffer device flags (eg FRAMEBUFFER_FLAG_COMMIT) (Ignored for Allocate / SetProperties)
	size_t address; ///< Framebuffer address (Ignored for Allocate / SetProperties)
	uint32_t size; ///< Framebuffer size (Bytes) (Ignored for Allocate / SetProperties)
	uint32_t pitch; ///< Framebuffer pitch (Bytes per Line) (Ignored for Allocate / SetProperties)
	uint32_t depth; ///< Framebuffer depth (Bits per Pixel)(8/16/24/32)
	uint32_t order; ///< Framebuffer pixel order (BGR/RGB)
	uint32_t mode; ///< Framebuffer alpha mode (Enabled/Reversed/Ignored)
	uint32_t format; ///< Framebuffer color format (eg COLOR_FORMAT_ARGB32) (Ignored for Allocate / SetProperties)
	uint32_t physicalwidth; ///< Framebuffer Physical Width (Pixels)
	uint32_t physicalheight; ///< Framebuffer Physical Height (Pixels)
	uint32_t virtualwidth; ///< Framebuffer Virtual Width (Pixels)
	uint32_t virtualheight; ///< Framebuffer Virtual Height (Pixels)
	uint32_t offsetx; ///< Framebuffer Virtual Offset X (Pixels)
	uint32_t offsety; ///< Framebuffer Virtual Offset Y (Pixels)
	uint32_t overscantop; ///< Framebuffer Overscan Top (Pixels)
	uint32_t overscanbottom; ///< Framebuffer Overscan Bottom (Pixels)
	uint32_t overscanleft; ///< Framebuffer Overscan Left (Pixels)
	uint32_t overscanright; ///< Framebuffer Overscan Right (Pixels)
	uint32_t rotation; ///< Framebuffer Rotation (eg FRAMEBUFFER_ROTATION_180)
	uint32_t cursorx; ///< Framebuffer Cursor X (Pixels) (Ignored for Allocate / SetProperties)
	uint32_t cursory; ///< Framebuffer Cursor Y (Pixels) (Ignored for Allocate / SetProperties)
	uint32_t cursorstate; ///< Framebuffer Cursor State (eg FRAMEBUFFER_CURSOR_ENABLED) (Ignored for Allocate / SetProperties)
};

typedef struct _FRAMEBUFFER_DEVICE FRAMEBUFFER_DEVICE;

/** Framebuffer Enumeration Callback */
typedef uint32_t STDCALL (*framebuffer_enumerate_cb)(FRAMEBUFFER_DEVICE *framebuffer, void *data);
/** Framebuffer Notification Callback */
typedef uint32_t STDCALL (*framebuffer_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** Framebuffer Device Methods */
typedef uint32_t STDCALL (*framebuffer_device_allocate_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);
typedef uint32_t STDCALL (*framebuffer_device_release_proc)(FRAMEBUFFER_DEVICE *framebuffer);

typedef uint32_t STDCALL (*framebuffer_device_blank_proc)(FRAMEBUFFER_DEVICE *framebuffer, BOOL blank);

typedef uint32_t STDCALL (*framebuffer_device_read_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t len, uint32_t flags);
typedef uint32_t STDCALL (*framebuffer_device_write_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t len, uint32_t flags);

typedef uint32_t STDCALL (*framebuffer_device_mark_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t flags);
typedef uint32_t STDCALL (*framebuffer_device_commit_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t address, uint32_t size, uint32_t flags);

typedef uint32_t STDCALL (*framebuffer_device_get_rect_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t skip, uint32_t flags);
typedef uint32_t STDCALL (*framebuffer_device_put_rect_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t skip, uint32_t flags);
typedef uint32_t STDCALL (*framebuffer_device_copy_rect_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t width, uint32_t height, uint32_t flags);
typedef uint32_t STDCALL (*framebuffer_device_fill_rect_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color, uint32_t flags);

typedef void * STDCALL (*framebuffer_device_get_line_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t y);
typedef void * STDCALL (*framebuffer_device_get_point_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y);

typedef uint32_t STDCALL (*framebuffer_device_wait_sync_proc)(FRAMEBUFFER_DEVICE *framebuffer);

typedef uint32_t STDCALL (*framebuffer_device_get_offset_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t *x, uint32_t *y);
typedef uint32_t STDCALL (*framebuffer_device_set_offset_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, BOOL pan);
typedef uint32_t STDCALL (*framebuffer_device_set_offset_ex_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, BOOL pan, BOOL _switch);

typedef uint32_t STDCALL (*framebuffer_device_get_palette_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PALETTE *palette);
typedef uint32_t STDCALL (*framebuffer_device_set_palette_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PALETTE *palette);

typedef uint32_t STDCALL (*framebuffer_device_set_backlight_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t brightness);

typedef uint32_t STDCALL (*framebuffer_device_set_cursor_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t width, uint32_t height, uint32_t hotspotx, uint32_t hotspoty, void *image, uint32_t len);
typedef uint32_t STDCALL (*framebuffer_device_update_cursor_proc)(FRAMEBUFFER_DEVICE *framebuffer, BOOL enabled, int32_t x, int32_t y, BOOL relative);

typedef uint32_t STDCALL (*framebuffer_device_get_properties_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);
typedef uint32_t STDCALL (*framebuffer_device_set_properties_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);

/** Framebuffer Device */
struct _FRAMEBUFFER_DEVICE
{
	// Device Properties
	DEVICE device; ///< The Device entry for this Framebuffer device
	// Framebuffer Properties
	uint32_t framebufferid; ///< Unique Id of this Framebuffer device in the Framebuffer device table
	uint32_t framebufferstate; ///< Framebuffer device state (eg FRAMEBUFFER_STATE_ENABLED)
	framebuffer_device_allocate_proc deviceallocate; ///< A device specific DeviceAllocate method implementing a standard framebuffer device interface (Mandatory)
	framebuffer_device_release_proc devicerelease; ///< A device specific DeviceRelease method implementing a standard framebuffer device interface (Mandatory)
	framebuffer_device_blank_proc deviceblank; ///< A device specific DeviceBlank method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_read_proc deviceread; ///< A device specific DeviceRead method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_write_proc devicewrite; ///< A device specific DeviceWrite method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_mark_proc devicemark; ///< A device specific DeviceMark method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_commit_proc devicecommit; ///< A device specific DeviceCommit method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_get_rect_proc devicegetrect; ///< A device specific DeviceGetRect method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_put_rect_proc deviceputrect; ///< A device specific DevicePutRect method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_copy_rect_proc devicecopyrect; ///< A device specific DeviceCopyRect method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_fill_rect_proc devicefillrect; ///< A device specific DeviceFillRect method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_get_line_proc devicegetline; ///< A device specific DeviceGetLine method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_get_point_proc devicegetpoint; ///< A device specific DeviceGetPoint method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_wait_sync_proc devicewaitsync; ///< A device specific DeviceWaitSync method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_get_offset_proc devicegetoffset; ///< A device specific DeviceGetOffset method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_offset_proc devicesetoffset; ///< A device specific DeviceSetOffset method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_offset_ex_proc devicesetoffsetex; ///< A device specific DeviceSetOffsetEx method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_get_palette_proc devicegetpalette; ///< A device specific DeviceGetPalette method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_palette_proc devicesetpalette; ///< A device specific DeviceSetPalette method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_backlight_proc devicesetbacklight; ///< A device specific DeviceSetBacklight method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_cursor_proc devicesetcursor; ///< A device specific DeviceSetCursor method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_update_cursor_proc deviceupdatecursor; ///< A device specific DeviceUpdateCursor method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_get_properties_proc devicegetproperties; ///< A device specific DeviceGetProperties method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_set_properties_proc devicesetproperties; ///< A device specific DeviceSetProperties method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t allocatecount;
	uint32_t releasecount;
	uint32_t readcount;
	uint32_t writecount;
	uint32_t getcount;
	uint32_t putcount;
	uint32_t copycount;
	uint32_t fillcount;
	// Driver Properties
	MUTEX_HANDLE lock; ///< Device lock
	size_t address; ///< Framebuffer address
	uint32_t size; ///< Framebuffer size (Bytes)
	uint32_t pitch; ///< Framebuffer pitch (Bytes per Line)
	uint32_t depth; ///< Framebuffer depth (Bits per Pixel)(8/16/24/32)
	uint32_t order; ///< Framebuffer pixel order (BGR/RGB)
	uint32_t mode; ///< Framebuffer alpha mode (Enabled/Reversed/Ignored)
	uint32_t format; ///< Framebuffer color format (eg COLOR_FORMAT_ARGB32)
	uint32_t physicalwidth; ///< Framebuffer Physical Width (Pixels)
	uint32_t physicalheight; ///< Framebuffer Physical Height (Pixels)
	uint32_t virtualwidth; ///< Framebuffer Virtual Width (Pixels)
	uint32_t virtualheight; ///< Framebuffer Virtual Height (Pixels)
	uint32_t offsetx; ///< Framebuffer Virtual Offset X (Pixels)
	uint32_t offsety; ///< Framebuffer Virtual Offset Y (Pixels)
	uint32_t overscantop; ///< Framebuffer Overscan Top (Pixels)
	uint32_t overscanbottom; ///< Framebuffer Overscan Bottom (Pixels)
	uint32_t overscanleft; ///< Framebuffer Overscan Left (Pixels)
	uint32_t overscanright; ///< Framebuffer Overscan Right (Pixels)
	uint32_t rotation; ///< Framebuffer Rotation (eg FRAMEBUFFER_ROTATION_180)
	uint32_t cursorx; ///< Framebuffer Cursor X (Pixels)
	uint32_t cursory; ///< Framebuffer Cursor Y (Pixels)
	uint32_t cursorstate; ///< Framebuffer Cursor State (eg FRAMEBUFFER_CURSOR_ENABLED)
	// Buffer Properties
	void *linebuffer; ///< Buffer for line fills
	void *copybuffer; ///< Buffer for overlapped copy
	// Cursor Properties
	LONGBOOL cursorupdate; ///< Flag to indicate if cursor update (Show/Hide) is in progress
	void *cursorimage; ///< Buffer for cursor image pixels (COLOR_FORMAT_DEFAULT)
	void *cursorinput; ///< Buffer for cursor image pixels (Native color format)
	void *cursorbuffer; ///< Buffer for pixels currently under cursor (Native color format)
	void *cursoroutput; ///< Buffer for cursor pixels currently displayed (Native color format)
	uint32_t cursorwidth; ///< Framebuffer Cursor Width (Pixels)
	uint32_t cursorheight; ///< Framebuffer Cursor Height (Pixels)
	uint32_t cursorhotspotx; ///< Framebuffer Cursor Hotspot X (Pixels)
	uint32_t cursorhotspoty; ///< Framebuffer Cursor Hotspot Y (Pixels)
	// Internal Properties
	FRAMEBUFFER_DEVICE *prev; ///< Previous entry in Framebuffer device table
	FRAMEBUFFER_DEVICE *next; ///< Next entry in Framebuffer device table
};

/** Framebuffer Functions */

/**
 * @brief Allocate and enable a framebuffer device using supplied properties or defaults
 * @param Framebuffer The framebuffer device to allocate
 * @param Properties The framebuffer properties (Width/Height/Depth etc) to use for allocation (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL framebuffer_device_allocate(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);

/**
 * @brief Disable and release a framebuffer device
 * @param Framebuffer The framebuffer device to release
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL framebuffer_device_release(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief Blank (Turn off) the display of a framebuffer device
 * @param Framebuffer The framebuffer device to blank
 * @param Blank Turn off the display if True / Turn on the display if False
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Not all framebuffer devices support blank, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 *       Devices that support blank should set the flag FRAMEBUFFER_FLAG_BLANK
 */
uint32_t STDCALL framebuffer_device_blank(FRAMEBUFFER_DEVICE *framebuffer, BOOL blank);

/**
 * @brief Read one or more pixels from framebuffer device memory to a supplied buffer
 * @param Framebuffer The framebuffer device to read from
 * @param X The column to start reading from
 * @param Y The row to start reading from
 * @param Buffer Pointer to a buffer to receive the read pixels
 * @param Len The number of pixels to read starting at X,Y
 * @param Flags The flags for the transfer (eg FRAMEBUFFER_TRANSFER_DMA)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Pixel data will be returned in the color format of the framebuffer
 * @note X and Y are relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 * @note The default method assumes that framebuffer memory is DMA coherent and does not require cache cleaning before a DMA read
 */
uint32_t STDCALL framebuffer_device_read(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t len, uint32_t flags);

/**
 * @brief Write one or more pixels to framebuffer device memory from a supplied buffer
 * @param Framebuffer The framebuffer device to write to
 * @param X The column to start writing from
 * @param Y The row to start writing from
 * @param Buffer Pointer to a buffer containing the pixels to write
 * @param Len The number of pixels to write starting at X,Y
 * @param Flags The flags for the transfer (eg FRAMEBUFFER_TRANSFER_DMA)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must ensure pixel data is in the correct color format for the framebuffer
 * @note X and Y are relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 * @note The default method assumes that framebuffer memory is DMA coherent and does not require cache invalidation after a DMA write
 */
uint32_t STDCALL framebuffer_device_write(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t len, uint32_t flags);

/**
 * @brief Mark a region written to the framebuffer and signal the device to take any necessary actions
 * @param Framebuffer The framebuffer device to mark
 * @param X The starting column of the mark
 * @param Y The starting row of the mark
 * @param Width The number of columns to mark
 * @param Height The number of rows to mark
 * @param Flags The flags used for the transfer (eg FRAMEBUFFER_TRANSFER_DMA)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note X and Y are relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 * @note Not all framebuffer devices support mark, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 *       Devices that support and require mark should set the flag FRAMEBUFFER_FLAG_MARK
 */
uint32_t STDCALL framebuffer_device_mark(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t flags);

/**
 * @brief Commit a region written to the framebuffer and signal the device to take any necessary actions
 * @param Framebuffer The framebuffer device to commit
 * @param Address The starting address of the commit
 * @param Size The size in bytes of the commit
 * @param Flags The flags used for the transfer (eg FRAMEBUFFER_TRANSFER_DMA)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Not all framebuffer devices support commit, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 *       Devices that support and require commit should set the flag FRAMEBUFFER_FLAG_COMMIT
 */
uint32_t STDCALL framebuffer_device_commit(FRAMEBUFFER_DEVICE *framebuffer, size_t address, uint32_t size, uint32_t flags);

/**
 * @brief Get a rectangular area of pixels from framebuffer memory to a supplied buffer
 * @param Framebuffer The framebuffer device to get from
 * @param X The starting column of the get
 * @param Y The starting row of the get
 * @param Buffer Pointer to a block of memory large enough to hold the pixels in a contiguous block of rows
 * @param Width The number of columns to get
 * @param Height The number of rows to get
 * @param Skip The number of pixels to skip in the buffer after each row (Optional)
 * @param Flags The flags for the transfer (eg FRAMEBUFFER_TRANSFER_DMA)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Pixel data will be returned in the color format of the framebuffer
 * @note X and Y are relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 * @note The default method assumes that framebuffer memory is DMA coherent and does not require cache cleaning before a DMA read
 */
uint32_t STDCALL framebuffer_device_get_rect(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t skip, uint32_t flags);

/**
 * @brief Put a rectangular area of pixels from a supplied buffer to framebuffer memory
 * @param Framebuffer The framebuffer device to put to
 * @param X The starting column of the put
 * @param Y The starting row of the put
 * @param Buffer Pointer to a block of memory containing the pixels in a contiguous block of rows
 * @param Width The number of columns to put
 * @param Height The number of rows to put
 * @param Skip The number of pixels to skip in the buffer after each row (Optional)
 * @param Flags The flags for the transfer (eg FRAMEBUFFER_TRANSFER_DMA)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must ensure pixel data is in the correct color format for the framebuffer
 * @note X and Y are relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 * @note The default method assumes that framebuffer memory is DMA coherent and does not require cache invalidation after a DMA write
 */
uint32_t STDCALL framebuffer_device_put_rect(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t skip, uint32_t flags);

/**
 * @brief Copy a rectangular area of pixels within framebuffer memory
 * @param Framebuffer The framebuffer device to copy on
 * @param X1 The starting column to copy from
 * @param Y1 The starting row to copy from
 * @param X2 The starting column to copy to
 * @param Y2 The starting row to copy to
 * @param Width The number of columns to copy
 * @param Height The number of rows to copy
 * @param Flags The flags for the transfer (eg FRAMEBUFFER_TRANSFER_DMA)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note X1, Y1, X2 and Y2 are relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 * @note The default method assumes that framebuffer memory is DMA coherent and does not require cache clean/invalidate before or after a DMA read/write
 */
uint32_t STDCALL framebuffer_device_copy_rect(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t width, uint32_t height, uint32_t flags);

/**
 * @brief Fill a rectangular area of pixels within framebuffer memory
 * @param Framebuffer The framebuffer device to fill on
 * @param X The starting column of the fill
 * @param Y The starting row of the fill
 * @param Width The number of columns to fill
 * @param Height The number of rows to fill
 * @param Color The color to use for the fill
 * @param Flags The flags for the transfer (eg FRAMEBUFFER_TRANSFER_DMA)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the correct format for the framebuffer
 * @note X and Y are relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 * @note The default method assumes that framebuffer memory is DMA coherent and does not require cache invalidation after a DMA write
 */
uint32_t STDCALL framebuffer_device_fill_rect(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color, uint32_t flags);

/**
 * @brief Get the address of the start of a row in framebuffer memory
 * @param Framebuffer The framebuffer device to get the start address from
 * @param Y The row to get the start address of
 * @return Pointer to the start address of the row or nil on failure
 * @note Y is relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 */
void * STDCALL framebuffer_device_get_line(FRAMEBUFFER_DEVICE *framebuffer, uint32_t y);

/**
 * @brief Get the address of the specified row and column in framebuffer memory
 * @param Framebuffer The framebuffer device to get the address from
 * @param X The column to get the start address of
 * @param Y The row to get the start address of
 * @return Pointer to the address of the row and column or nil on failure
 * @note X and Y are relative to the physical screen and will be translated to the virtual buffer (Where applicable)
 */
void * STDCALL framebuffer_device_get_point(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y);

/**
 * @brief Wait for the next vertical sync signal from the display hardware
 * @param Framebuffer The framebuffer device to wait for
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Not all framebuffer devices support wait sync, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 *       Devices that support wait sync should set the flag FRAMEBUFFER_FLAG_SYNC
 */
uint32_t STDCALL framebuffer_device_wait_sync(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief Get the virtual offset X and Y from a framebuffer device
 * @param Framebuffer The framebuffer device to get the offset from
 * @param X The X (Column) offset value in pixels returned from the device if successful
 * @param Y The Y (Row) offset value in pixels returned from the device if successful
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note X and Y are relative to the virtual buffer and NOT the physical screen (Where applicable)
 * @note Not all framebuffer devices support X and/or Y offset
 *       Devices that support offset X should set the flag FRAMEBUFFER_FLAG_OFFSETX
 *       Devices that support offset Y should set the flag FRAMEBUFFER_FLAG_OFFSETY
 */
uint32_t STDCALL framebuffer_device_get_offset(FRAMEBUFFER_DEVICE *framebuffer, uint32_t *x, uint32_t *y);

/**
 * @brief Set the virtual offset X and Y of a framebuffer device
 * @param Framebuffer The framebuffer device to set the offset for
 * @param X The X (Column) offset value in pixels to set
 * @param Y The Y (Row) offset value in pixels to set
 * @param Pan If True then pan the display without updating the Offset X and/or Y
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note X and Y are relative to the virtual buffer and NOT the physical screen (Where applicable)
 * @note Not all framebuffer devices support X and/or Y offset, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 *       Devices that support offset X should set the flag FRAMEBUFFER_FLAG_OFFSETX
 *       Devices that support offset Y should set the flag FRAMEBUFFER_FLAG_OFFSETY
 */
uint32_t STDCALL framebuffer_device_set_offset(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, BOOL pan);

/**
 * @brief Set the virtual offset X and Y of a framebuffer device
 * @param Framebuffer The framebuffer device to set the offset for
 * @param X The X (Column) offset value in pixels to set
 * @param Y The Y (Row) offset value in pixels to set
 * @param Pan If True then pan the display without updating the Offset X and/or Y
 * @param Switch If False then update the Offset X and/or Y without moving the display
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note X and Y are relative to the virtual buffer and NOT the physical screen (Where applicable)
 * @note Not all framebuffer devices support X and/or Y offset, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 *       Devices that support offset X should set the flag FRAMEBUFFER_FLAG_OFFSETX
 *       Devices that support offset Y should set the flag FRAMEBUFFER_FLAG_OFFSETY
 */
uint32_t STDCALL framebuffer_device_set_offset_ex(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, BOOL pan, BOOL _switch);

/**
 * @brief Get the 8 bit color palette from a framebuffer device
 * @param Framebuffer The framebuffer device to get the palette from
 * @param Palette Pointer to a TFramebufferPalette structure for the palette data
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Not all framebuffer devices support 8 bit palette, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 */
uint32_t STDCALL framebuffer_device_get_palette(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PALETTE *palette);

/**
 * @brief Set the 8 bit color palette of a framebuffer device
 * @param Framebuffer The framebuffer device to set the palette for
 * @param Palette Pointer to a TFramebufferPalette structure for the palette data
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Not all framebuffer devices support 8 bit palette, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 */
uint32_t STDCALL framebuffer_device_set_palette(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PALETTE *palette);

/**
 * @brief Set the brightness of the backlight of a framebuffer device
 * @param Framebuffer The framebuffer device to set the backlight
 * @param Brightness The brightness value to set (Normally 0 to 100)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Not all framebuffer devices support set backlight, returns ERROR_CALL_NOT_IMPLEMENTED if not supported
 *       Devices that support set backlight should set the flag FRAMEBUFFER_FLAG_BACKLIGHT
 */
uint32_t STDCALL framebuffer_device_set_backlight(FRAMEBUFFER_DEVICE *framebuffer, uint32_t brightness);

/**
 * @brief Set the mouse cursor image and properties of a framebuffer device
 * @param Framebuffer The framebuffer device to set the cursor
 * @param Width The width of the cursor image in pixels
 * @param Height The height of the cursor image in pixels
 * @param HotspotX The X hotspot of the cursor image, where the cursor X location will be (Normally 0)
 * @param HotspotY The Y hotspot of the cursor image, where the cursor Y location will be (Normally 0)
 * @param Image A buffer containing the cursor image pixels in COLOR_FORMAT_DEFAULT format
 * @param Len The length of the image buffer in bytes
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For devices that don't support hardware mouse cursor a software cursor will be implemented
 *        If image is nil then the default cursor image will be used
 */
uint32_t STDCALL framebuffer_device_set_cursor(FRAMEBUFFER_DEVICE *framebuffer, uint32_t width, uint32_t height, uint32_t hotspotx, uint32_t hotspoty, void *image, uint32_t len);

/**
 * @brief Update the position and state for the mouse cursor of a framebuffer device
 * @param Framebuffer The framebuffer device to update the cursor
 * @param Enabled If true then show the cursor else hide it
 * @param X The cursor X location in pixels
 * @param Y The cursor Y location in pixels
 * @param Relative If true then X and Y are considered relative to the current position
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For devices that don't support hardware mouse cursor a software cursor will be implemented
 */
uint32_t STDCALL framebuffer_device_update_cursor(FRAMEBUFFER_DEVICE *framebuffer, BOOL enabled, int32_t x, int32_t y, BOOL relative);

/**
 * @brief Get the current properties from a framebuffer device
 * @param Framebuffer The framebuffer device to get properties from
 * @param Properties Pointer to a TFramebufferProperties structure to return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL framebuffer_device_get_properties(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);

/**
 * @brief Set the current properties for a framebuffer device
 * @param Framebuffer The framebuffer device to set properties for
 * @param Properties Pointer to a TFramebufferProperties structure containing the properties
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Changing certain properties may cause the framebuffer to be reallocated
 */
uint32_t STDCALL framebuffer_device_set_properties(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);

/**
 * @brief Check if a framebuffer device supports a flag value
 * @param Framebuffer The framebuffer device to check
 * @param Flag The framebuffer flag to check (eg FRAMEBUFFER_FLAG_BACKLIGHT)
 * @return True if flag is supported, False if not or on error
 */
BOOL STDCALL framebuffer_device_check_flag(FRAMEBUFFER_DEVICE *framebuffer, uint32_t flag);

/**
 * @brief Get the color format of a framebuffer device
 * @param Framebuffer The framebuffer device to get from
 * @return The color format of the framebuffer (eg COLOR_FORMAT_RGB24)
 */
uint32_t STDCALL framebuffer_device_get_format(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief Create a new Framebuffer entry
 * @return Pointer to new Framebuffer entry or nil if Framebuffer could not be created
 */
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_create(void);

/**
 * @brief Create a new Framebuffer entry
 * @param Size Size in bytes to allocate for new Framebuffer (Including the Framebuffer entry)
 * @return Pointer to new Framebuffer entry or nil if Framebuffer could not be created
 */
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_create_ex(uint32_t size);

/**
 * @brief Destroy an existing Framebuffer entry
 * @param Framebuffer The framebuffer device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL framebuffer_device_destroy(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief Register a new Framebuffer in the Framebuffer table
 * @param Framebuffer The framebuffer device to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL framebuffer_device_register(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief Deregister a Framebuffer from the Framebuffer table
 * @param Framebuffer The framebuffer device to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL framebuffer_device_deregister(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief Find a framebuffer device by ID in the framebuffer table
 * @param FramebufferId The ID number of the framebuffer to find
 * @return Pointer to framebuffer device entry or nil if not found
 */
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_find(uint32_t framebufferid);

/**
 * @brief Find a framebuffer device by name in the framebuffer table
 * @param Name The name of the framebuffer to find (eg Framebuffer0)
 * @return Pointer to framebuffer device entry or nil if not found
 */
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_find_by_name(const char *name);

/**
 * @brief Find a framebuffer device by description in the framebuffer table
 * @param Description The description of the framebuffer to find (eg BCM2836 Framebuffer)
 * @return Pointer to framebuffer device entry or nil if not found
 */
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_find_by_description(const char *description);

/**
 * @brief Enumerate all framebuffer devices in the framebuffer table
 * @param Callback The callback function to call for each framebuffer in the table
 * @param Data A private data pointer to pass to callback for each framebuffer in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL framebuffer_device_enumerate(framebuffer_enumerate_cb callback, void *data);

/**
 * @brief Register a notification for framebuffer device changes
 * @param Framebuffer The framebuffer device to notify changes for (Optional, pass nil for all framebuffer devices)
 * @param Callback The function to call when a notification event occurs
 * @param Data A private data pointer to pass to callback when a notification event occurs
 * @param Notification The events to register for notification of (eg DEVICE_NOTIFICATION_REGISTER)
 * @param Flags The flags to control the notification (eg NOTIFIER_FLAG_WORKER)
 */
uint32_t STDCALL framebuffer_device_notification(FRAMEBUFFER_DEVICE *framebuffer, framebuffer_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/** Framebuffer Helper Functions */

/**
 * @brief Get the current framebuffer device count
 */
uint32_t STDCALL framebuffer_device_get_count(void);

/**
 * @brief Get the current default framebuffer device
 */
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_get_default(void);

/**
 * @brief Set the current default framebuffer device
 */
uint32_t STDCALL framebuffer_device_set_default(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief Check if the supplied Framebuffer device is in the Framebuffer table
 */
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_check(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief No longer required (See ColorDefaultToFormat and ColorFormatToDefault)
 */
uint32_t STDCALL framebuffer_device_swap(uint32_t value);

/**
 * @brief Convert a Framebuffer type value to a string
 */
uint32_t STDCALL framebuffer_type_to_string(uint32_t framebuffertype, char *string, uint32_t len);

/**
 * @brief Convert a Framebuffer state value to a string
 */
uint32_t STDCALL framebuffer_state_to_string(uint32_t framebufferstate, char *string, uint32_t len);

/**
 * @brief Restore the framebuffer area under the cursor from the cursor buffer
 * @note Caller must hold the framebuffer lock
 * @note Driver support function only, not intended for direct use by applications
 */
void STDCALL framebuffer_device_hide_cursor(FRAMEBUFFER_DEVICE *framebuffer);

/**
 * @brief Save the framebuffer area under the cursor to the cursor buffer and merge the
 *  cursor input with it to create the cursor output. Put the output to the framebuffer
 * @note Caller must hold the framebuffer lock
 * @note Driver support function only, not intended for direct use by applications
 */
void STDCALL framebuffer_device_show_cursor(FRAMEBUFFER_DEVICE *framebuffer);

uint32_t STDCALL framebuffer_cursor_to_string(uint32_t state, char *string, uint32_t len);

uint32_t STDCALL framebuffer_depth_to_string(uint32_t depth, char *string, uint32_t len);
uint32_t STDCALL framebuffer_order_to_string(uint32_t order, char *string, uint32_t len);
uint32_t STDCALL framebuffer_mode_to_string(uint32_t mode, char *string, uint32_t len);
uint32_t STDCALL framebuffer_rotation_to_string(uint32_t rotation, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_FRAMEBUFFER_H