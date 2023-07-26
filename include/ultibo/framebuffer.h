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
#ifndef _ULTIBO_FRAMEBUFFER_H
#define _ULTIBO_FRAMEBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* Framebuffer specific constants */
#define FRAMEBUFFER_NAME_PREFIX	"Framebuffer" // Name prefix for Framebuffer Devices

/* Framebuffer Device Types */
#define FRAMEBUFFER_TYPE_NONE	0
#define FRAMEBUFFER_TYPE_HARDWARE	1
#define FRAMEBUFFER_TYPE_VIRTUAL	2

/* Framebuffer Device States */
#define FRAMEBUFFER_STATE_DISABLED	0
#define FRAMEBUFFER_STATE_ENABLED	1

/* Framebuffer Cursor States */
#define FRAMEBUFFER_CURSOR_DISABLED	0
#define FRAMEBUFFER_CURSOR_ENABLED	1

/* Framebuffer Device Flags */
#define FRAMEBUFFER_FLAG_NONE	0x00000000
#define FRAMEBUFFER_FLAG_DMA	0x00000001 // If set the framebuffer supports DMA for read/write operations
#define FRAMEBUFFER_FLAG_MARK	0x00000002 // If set the framebuffer requires mark after write operations
#define FRAMEBUFFER_FLAG_COMMIT	0x00000004 // If set the framebuffer requires commit after write operations
#define FRAMEBUFFER_FLAG_BLANK	0x00000008 // If set the framebuffer supports blanking the screen
#define FRAMEBUFFER_FLAG_CACHED	0x00000010 // If set framebuffer is in cached memory and cache cleaning should be used
#define FRAMEBUFFER_FLAG_SWAP	0x00000020 // If set framebuffer requires byte order of colors to be reversed (BGR <-> RGB)
#define FRAMEBUFFER_FLAG_BACKLIGHT	0x00000040 // If set the framebuffer supports setting the backlight brightness
#define FRAMEBUFFER_FLAG_VIRTUAL	0x00000080 // If set the framebuffer supports virtual width and height
#define FRAMEBUFFER_FLAG_OFFSETX	0x00000100 // If set the framebuffer supports virtual offset X (Horizontal Pan/Flip etc)
#define FRAMEBUFFER_FLAG_OFFSETY	0x00000200 // If set the framebuffer supports virtual offset Y (Vertical Pan/Flip etc)
#define FRAMEBUFFER_FLAG_SYNC	0x00000400 // If set the framebuffer supports waiting for vertical sync
#define FRAMEBUFFER_FLAG_CURSOR	0x00000800 // If set the framebuffer supports a hardware mouse cursor

/* Framebuffer Transfer Flags */
#define FRAMEBUFFER_TRANSFER_NONE	0x00000000
#define FRAMEBUFFER_TRANSFER_DMA	0x00000001 // Use DMA for transfer operations (Note: Buffers must be DMA compatible)

/* ============================================================================== */
/* Framebuffer specific types */
typedef struct _FRAMEBUFFER_PALETTE FRAMEBUFFER_PALETTE;
struct _FRAMEBUFFER_PALETTE
{
	uint32_t start; // The number of the first valid entry in the palette
	uint32_t count; // The total number of entries in the palette
	uint32_t entries[256]; // The palette entries in COLOR_FORMAT_DEFAULT format
};

typedef struct _FRAMEBUFFER_PROPERTIES FRAMEBUFFER_PROPERTIES;
struct _FRAMEBUFFER_PROPERTIES
{
	uint32_t flags; // Framebuffer device flags (eg FRAMEBUFFER_FLAG_COMMIT) (Ignored for Allocate / SetProperties)
	size_t address; // Framebuffer address (Ignored for Allocate / SetProperties)
	uint32_t size; // Framebuffer size (Bytes) (Ignored for Allocate / SetProperties)
	uint32_t pitch; // Framebuffer pitch (Bytes per Line) (Ignored for Allocate / SetProperties)
	uint32_t depth; // Framebuffer depth (Bits per Pixel)(8/16/24/32)
	uint32_t order; // Framebuffer pixel order (BGR/RGB)
	uint32_t mode; // Framebuffer alpha mode (Enabled/Reversed/Ignored)
	uint32_t format; // Framebuffer color format (eg COLOR_FORMAT_ARGB32) (Ignored for Allocate / SetProperties)
	uint32_t physicalwidth; // Framebuffer Physical Width (Pixels)
	uint32_t physicalheight; // Framebuffer Physical Height (Pixels)
	uint32_t virtualwidth; // Framebuffer Virtual Width (Pixels)
	uint32_t virtualheight; // Framebuffer Virtual Height (Pixels)
	uint32_t offsetx; // Framebuffer Virtual Offset X (Pixels)
	uint32_t offsety; // Framebuffer Virtual Offset Y (Pixels)
	uint32_t overscantop; // Framebuffer Overscan Top (Pixels)
	uint32_t overscanbottom; // Framebuffer Overscan Bottom (Pixels)
	uint32_t overscanleft; // Framebuffer Overscan Left (Pixels)
	uint32_t overscanright; // Framebuffer Overscan Right (Pixels)
	uint32_t rotation; // Framebuffer Rotation (eg FRAMEBUFFER_ROTATION_180)
	uint32_t cursorx; // Framebuffer Cursor X (Pixels) (Ignored for Allocate / SetProperties)
	uint32_t cursory; // Framebuffer Cursor Y (Pixels) (Ignored for Allocate / SetProperties)
	uint32_t cursorstate; // Framebuffer Cursor State (eg FRAMEBUFFER_CURSOR_ENABLED) (Ignored for Allocate / SetProperties)
};

typedef struct _FRAMEBUFFER_DEVICE FRAMEBUFFER_DEVICE;

/* Framebuffer Enumeration Callback */
typedef uint32_t STDCALL (*framebuffer_enumerate_cb)(FRAMEBUFFER_DEVICE *framebuffer, void *data);
/* Framebuffer Notification Callback */
typedef uint32_t STDCALL (*framebuffer_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Framebuffer Device Methods */
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

typedef uint32_t STDCALL (*framebuffer_device_get_palette_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PALETTE *palette);
typedef uint32_t STDCALL (*framebuffer_device_set_palette_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PALETTE *palette);

typedef uint32_t STDCALL (*framebuffer_device_set_backlight_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t brightness);

typedef uint32_t STDCALL (*framebuffer_device_set_cursor_proc)(FRAMEBUFFER_DEVICE *framebuffer, uint32_t width, uint32_t height, uint32_t hotspotx, uint32_t hotspoty, void *image, uint32_t len);
typedef uint32_t STDCALL (*framebuffer_device_update_cursor_proc)(FRAMEBUFFER_DEVICE *framebuffer, BOOL enabled, int32_t x, int32_t y, BOOL relative);

typedef uint32_t STDCALL (*framebuffer_device_get_properties_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);
typedef uint32_t STDCALL (*framebuffer_device_set_properties_proc)(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);

/* Framebuffer Device */
struct _FRAMEBUFFER_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Framebuffer device
	// Framebuffer Properties
	uint32_t framebufferid; // Unique Id of this Framebuffer device in the Framebuffer device table
	uint32_t framebufferstate; // Framebuffer device state (eg FRAMEBUFFER_STATE_ENABLED)
	framebuffer_device_allocate_proc deviceallocate; // A device specific DeviceAllocate method implementing a standard framebuffer device interface (Mandatory)
	framebuffer_device_release_proc devicerelease; // A device specific DeviceRelease method implementing a standard framebuffer device interface (Mandatory)
	framebuffer_device_blank_proc deviceblank; // A device specific DeviceBlank method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_read_proc deviceread; // A device specific DeviceRead method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_write_proc devicewrite; // A device specific DeviceWrite method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_mark_proc devicemark; // A device specific DeviceMark method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_commit_proc devicecommit; // A device specific DeviceCommit method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_get_rect_proc devicegetrect; // A device specific DeviceGetRect method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_put_rect_proc deviceputrect; // A device specific DevicePutRect method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_copy_rect_proc devicecopyrect; // A device specific DeviceCopyRect method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_fill_rect_proc devicefillrect; // A device specific DeviceFillRect method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_get_line_proc devicegetline; // A device specific DeviceGetLine method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_get_point_proc devicegetpoint; // A device specific DeviceGetPoint method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_wait_sync_proc devicewaitsync; // A device specific DeviceWaitSync method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_get_offset_proc devicegetoffset; // A device specific DeviceGetOffset method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_offset_proc devicesetoffset; // A device specific DeviceSetOffset method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_get_palette_proc devicegetpalette; // A device specific DeviceGetPalette method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_palette_proc devicesetpalette; // A device specific DeviceSetPalette method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_backlight_proc devicesetbacklight; // A device specific DeviceSetBacklight method implementing a standard framebuffer device interface (Optional)
	framebuffer_device_set_cursor_proc devicesetcursor; // A device specific DeviceSetCursor method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_update_cursor_proc deviceupdatecursor; // A device specific DeviceUpdateCursor method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_get_properties_proc devicegetproperties; // A device specific DeviceGetProperties method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
	framebuffer_device_set_properties_proc devicesetproperties; // A device specific DeviceSetProperties method implementing a standard framebuffer device interface (Or nil if the default method is suitable)
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
	MUTEX_HANDLE lock; // Device lock
	size_t address; // Framebuffer address
	uint32_t size; // Framebuffer size (Bytes)
	uint32_t pitch; // Framebuffer pitch (Bytes per Line)
	uint32_t depth; // Framebuffer depth (Bits per Pixel)(8/16/24/32)
	uint32_t order; // Framebuffer pixel order (BGR/RGB)
	uint32_t mode; // Framebuffer alpha mode (Enabled/Reversed/Ignored)
	uint32_t format; // Framebuffer color format (eg COLOR_FORMAT_ARGB32)
	uint32_t physicalwidth; // Framebuffer Physical Width (Pixels)
	uint32_t physicalheight; // Framebuffer Physical Height (Pixels)
	uint32_t virtualwidth; // Framebuffer Virtual Width (Pixels)
	uint32_t virtualheight; // Framebuffer Virtual Height (Pixels)
	uint32_t offsetx; // Framebuffer Virtual Offset X (Pixels)
	uint32_t offsety; // Framebuffer Virtual Offset Y (Pixels)
	uint32_t overscantop; // Framebuffer Overscan Top (Pixels)
	uint32_t overscanbottom; // Framebuffer Overscan Bottom (Pixels)
	uint32_t overscanleft; // Framebuffer Overscan Left (Pixels)
	uint32_t overscanright; // Framebuffer Overscan Right (Pixels)
	uint32_t rotation; // Framebuffer Rotation (eg FRAMEBUFFER_ROTATION_180)
	uint32_t cursorx; // Framebuffer Cursor X (Pixels)
	uint32_t cursory; // Framebuffer Cursor Y (Pixels)
	uint32_t cursorstate; // Framebuffer Cursor State (eg FRAMEBUFFER_CURSOR_ENABLED)
	// Buffer Properties
	void *linebuffer; // Buffer for line fills
	void *copybuffer; // Buffer for overlapped copy
	// Cursor Properties
	LONGBOOL cursorupdate; // Flag to indicate if cursor update (Show/Hide) is in progress
	void *cursorimage; // Buffer for cursor image pixels (COLOR_FORMAT_DEFAULT)
	void *cursorinput; // Buffer for cursor image pixels (Native color format)
	void *cursorbuffer; // Buffer for pixels currently under cursor (Native color format)
	void *cursoroutput; // Buffer for cursor pixels currently displayed (Native color format)
	uint32_t cursorwidth; // Framebuffer Cursor Width (Pixels)
	uint32_t cursorheight; // Framebuffer Cursor Height (Pixels)
	uint32_t cursorhotspotx; // Framebuffer Cursor Hotspot X (Pixels)
	uint32_t cursorhotspoty; // Framebuffer Cursor Hotspot Y (Pixels)
	// Internal Properties
	FRAMEBUFFER_DEVICE *prev; // Previous entry in Framebuffer device table
	FRAMEBUFFER_DEVICE *next; // Next entry in Framebuffer device table
};

/* ============================================================================== */
/* Framebuffer Functions */
uint32_t STDCALL framebuffer_device_allocate(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);
uint32_t STDCALL framebuffer_device_release(FRAMEBUFFER_DEVICE *framebuffer);

uint32_t STDCALL framebuffer_device_blank(FRAMEBUFFER_DEVICE *framebuffer, BOOL blank);

uint32_t STDCALL framebuffer_device_read(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t len, uint32_t flags);
uint32_t STDCALL framebuffer_device_write(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t len, uint32_t flags);

uint32_t STDCALL framebuffer_device_mark(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t flags);
uint32_t STDCALL framebuffer_device_commit(FRAMEBUFFER_DEVICE *framebuffer, size_t address, uint32_t size, uint32_t flags);

uint32_t STDCALL framebuffer_device_get_rect(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t skip, uint32_t flags);
uint32_t STDCALL framebuffer_device_put_rect(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t skip, uint32_t flags);
uint32_t STDCALL framebuffer_device_copy_rect(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t width, uint32_t height, uint32_t flags);
uint32_t STDCALL framebuffer_device_fill_rect(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color, uint32_t flags);

void * STDCALL framebuffer_device_get_line(FRAMEBUFFER_DEVICE *framebuffer, uint32_t y);
void * STDCALL framebuffer_device_get_point(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y);

uint32_t STDCALL framebuffer_device_wait_sync(FRAMEBUFFER_DEVICE *framebuffer);

uint32_t STDCALL framebuffer_device_get_offset(FRAMEBUFFER_DEVICE *framebuffer, uint32_t *x, uint32_t *y);
uint32_t STDCALL framebuffer_device_set_offset(FRAMEBUFFER_DEVICE *framebuffer, uint32_t x, uint32_t y, BOOL pan);

uint32_t STDCALL framebuffer_device_get_palette(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PALETTE *palette);
uint32_t STDCALL framebuffer_device_set_palette(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PALETTE *palette);

uint32_t STDCALL framebuffer_device_set_backlight(FRAMEBUFFER_DEVICE *framebuffer, uint32_t brightness);

uint32_t STDCALL framebuffer_device_set_cursor(FRAMEBUFFER_DEVICE *framebuffer, uint32_t width, uint32_t height, uint32_t hotspotx, uint32_t hotspoty, void *image, uint32_t len);
uint32_t STDCALL framebuffer_device_update_cursor(FRAMEBUFFER_DEVICE *framebuffer, BOOL enabled, int32_t x, int32_t y, BOOL relative);

uint32_t STDCALL framebuffer_device_get_properties(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);
uint32_t STDCALL framebuffer_device_set_properties(FRAMEBUFFER_DEVICE *framebuffer, FRAMEBUFFER_PROPERTIES *properties);

BOOL STDCALL framebuffer_device_check_flag(FRAMEBUFFER_DEVICE *framebuffer, uint32_t flag);

uint32_t STDCALL framebuffer_device_get_format(FRAMEBUFFER_DEVICE *framebuffer);

FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_create(void);
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_create_ex(uint32_t size);
uint32_t STDCALL framebuffer_device_destroy(FRAMEBUFFER_DEVICE *framebuffer);

uint32_t STDCALL framebuffer_device_register(FRAMEBUFFER_DEVICE *framebuffer);
uint32_t STDCALL framebuffer_device_deregister(FRAMEBUFFER_DEVICE *framebuffer);

FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_find(uint32_t framebufferid);
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_find_by_name(char *name);
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_find_by_description(char *description);
uint32_t STDCALL framebuffer_device_enumerate(framebuffer_enumerate_cb callback, void *data);

uint32_t STDCALL framebuffer_device_notification(FRAMEBUFFER_DEVICE *framebuffer, framebuffer_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Framebuffer Helper Functions */
uint32_t STDCALL framebuffer_device_get_count(void);
FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_get_default(void);
uint32_t STDCALL framebuffer_device_set_default(FRAMEBUFFER_DEVICE *framebuffer);

FRAMEBUFFER_DEVICE * STDCALL framebuffer_device_check(FRAMEBUFFER_DEVICE *framebuffer);

uint32_t STDCALL framebuffer_device_swap(uint32_t value);

uint32_t STDCALL framebuffer_type_to_string(uint32_t framebuffertype, char *string, uint32_t len);
uint32_t STDCALL framebuffer_state_to_string(uint32_t framebufferstate, char *string, uint32_t len);

void STDCALL framebuffer_device_hide_cursor(FRAMEBUFFER_DEVICE *framebuffer);
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