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
#ifndef _ULTIBO_CONSOLE_H
#define _ULTIBO_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* Console specific constants */
#define CONSOLE_NAME_PREFIX	"Console" // Name prefix for Console Devices

/* Console Device Types */
#define CONSOLE_TYPE_NONE	0
#define CONSOLE_TYPE_FRAMEBUFFER	1
#define CONSOLE_TYPE_SERIAL	2
#define CONSOLE_TYPE_REMOTE	3
#define CONSOLE_TYPE_LCD	4

#define CONSOLE_TYPE_MAX	4

/* Console Device States */
#define CONSOLE_STATE_CLOSED	0
#define CONSOLE_STATE_OPEN	1

#define CONSOLE_STATE_MAX	1

/* Console Device Flags */
#define CONSOLE_FLAG_NONE	0x00000000
#define CONSOLE_FLAG_LINE_WRAP	0x00000001 // Wrap long lines to the next line if set
#define CONSOLE_FLAG_DMA_BOX	0x00000002 // Use DMA to draw boxes (Where applicable)
#define CONSOLE_FLAG_DMA_LINE	0x00000004 // Use DMA to draw lines (Where applicable)
#define CONSOLE_FLAG_DMA_FILL	0x00000008 // Use DMA to fill blocks (Where applicable)
#define CONSOLE_FLAG_DMA_CLEAR	0x00000010 // Use DMA to clear blocks (Where applicable)
#define CONSOLE_FLAG_DMA_SCROLL	0x00000020 // Use DMA to scroll blocks (Where applicable)
#define CONSOLE_FLAG_SINGLE_WINDOW	0x00000040 // Console supports only one window (Not multiple)
#define CONSOLE_FLAG_HARDWARE_CURSOR	0x00000080 // Console supports a hardware cursor (Mouse pointer) (Character mode only)
#define CONSOLE_FLAG_HARDWARE_CARET	0x00000100 // Console supports a hardware caret (Text cursor)
#define CONSOLE_FLAG_BLINK_CARET	0x00000200 // Console supports blinking caret
#define CONSOLE_FLAG_TEXT_MODE	0x00000400 // Console supports text mode settings
#define CONSOLE_FLAG_TEXT_BLINK	0x00000800 // Console supports blinking text
#define CONSOLE_FLAG_COLOR	0x00001000 // Console supports colors
#define CONSOLE_FLAG_FONT	0x00002000 // Console supports fonts
#define CONSOLE_FLAG_FULLSCREEN	0x00004000 // Console supports creating a fullscreen window
#define CONSOLE_FLAG_AUTO_SCROLL	0x00008000 // Automatically scroll up on reaching the last line
#define CONSOLE_FLAG_DMA_TEXT	0x00010000 // Use DMA to draw text (Where applicable)
#define CONSOLE_FLAG_COLOR_REVERSE	0x00020000 // Console requires colors to be reversed for underlying hardware
#define CONSOLE_FLAG_TEXT_CARET	0x00040000 // Console supports a caret (Text cursor
#define CONSOLE_FLAG_FOCUS_CARET	0x00080000 // Only show caret on the focused (active) window

#define CONSOLE_FLAG_DMA_MASK	CONSOLE_FLAG_DMA_BOX | CONSOLE_FLAG_DMA_LINE | CONSOLE_FLAG_DMA_FILL | CONSOLE_FLAG_DMA_CLEAR | CONSOLE_FLAG_DMA_SCROLL | CONSOLE_FLAG_DMA_TEXT

/* Flags that cannot be changed by ConsoleDeviceUpdateFlag */
#define CONSOLE_FLAG_INTERNAL	CONSOLE_FLAG_SINGLE_WINDOW | CONSOLE_FLAG_HARDWARE_CURSOR | CONSOLE_FLAG_HARDWARE_CARET | CONSOLE_FLAG_BLINK_CARET | CONSOLE_FLAG_TEXT_MODE | CONSOLE_FLAG_TEXT_BLINK | CONSOLE_FLAG_COLOR | CONSOLE_FLAG_FONT | CONSOLE_FLAG_FULLSCREEN | CONSOLE_FLAG_COLOR_REVERSE | CONSOLE_FLAG_TEXT_CARET

/* Console Device Modes */
#define CONSOLE_MODE_NONE	0
#define CONSOLE_MODE_PIXEL	1
#define CONSOLE_MODE_CHARACTER	2

/* Console Caret Signature */
#define CARET_SIGNATURE	0x9A2D40E3

/* Console Window Signature */
#define WINDOW_SIGNATURE	0xDE3A5C04

/* Console Window States */
#define WINDOW_STATE_INVISIBLE	0
#define WINDOW_STATE_VISIBLE	1

#define WINDOW_STATE_MAX	1

/* Console Window Modes */
#define WINDOW_MODE_NONE	0
#define WINDOW_MODE_TEXT	1
#define WINDOW_MODE_GRAPHICS	2

#define WINDOW_MODE_MAX	2

/* Console Window Flags */
#define WINDOW_FLAG_NONE	0x00000000
#define WINDOW_FLAG_LINE_WRAP	0x00000001 // Wrap long lines to the next line if set
#define WINDOW_FLAG_BUFFERED	0x00000002 // Buffer output for scroll back and redraw
#define WINDOW_FLAG_FULLSCREEN	0x00000004 // Window occupies the full screen
#define WINDOW_FLAG_AUTO_SCROLL	0x00000008 // Automatically scroll up on reaching the last line
#define WINDOW_FLAG_CHARACTER	0x00000010 // Console for this Window is character mode only
#define WINDOW_FLAG_AUTO_UPDATE	0x00000020 // Automatically update output of buffered window
#define WINDOW_FLAG_FOCUS_CURSOR	0x00000040 // Only show cursor (caret) on the focused (active) window

/* Flags that cannot be changed by ConsoleWindowUpdateFlag */
#define WINDOW_FLAG_INTERNAL	WINDOW_FLAG_FULLSCREEN | WINDOW_FLAG_CHARACTER

/* Console Window Draw Flags */
#define WINDOW_DRAW_FLAG_NONE	0x00000000
#define WINDOW_DRAW_FLAG_BODY	0x00000001 // Draw the Window body
#define WINDOW_DRAW_FLAG_TITLE	0x00000002 // Draw the Window title
#define WINDOW_DRAW_FLAG_BORDER	0x00000004 // Draw the Window border

#define WINDOW_DRAW_FLAG_ALL	WINDOW_DRAW_FLAG_BODY | WINDOW_DRAW_FLAG_TITLE | WINDOW_DRAW_FLAG_BORDER

/* Console Window History */
#define WINDOW_HISTORY_MAX_COUNT	100

/* ============================================================================== */
/* Framebuffer Console specific constants */
#define FRAMEBUFFER_CONSOLE_DESCRIPTION	"Framebuffer Console" // Description of the Framebuffer Console device

/* ============================================================================== */
/* Console specific types */
typedef enum
{
 CURSOR_MODE_INSERT,
 CURSOR_MODE_OVERWRITE
} CURSOR_MODE;

typedef enum
{
 CURSOR_STATE_ON,
 CURSOR_STATE_OFF
} CURSOR_STATE;

// Line is a vertical line, Bar is a horizontal bar and Block is a solid block (All shapes inverse any character data under them)
typedef enum
{
 CURSOR_SHAPE_LINE,
 CURSOR_SHAPE_BAR,
 CURSOR_SHAPE_BLOCK
} CURSOR_SHAPE;

typedef struct _CONSOLE_CHAR CONSOLE_CHAR;
struct _CONSOLE_CHAR
{
	char ch;
	uint32_t forecolor;
	uint32_t backcolor;
};

typedef struct
{
	uint32_t x;
	uint32_t y;
} CONSOLE_POINT;

typedef struct
{
	uint32_t x1;
	uint32_t y1;
	uint32_t x2;
	uint32_t y2;
} CONSOLE_RECT;

typedef struct _CONSOLE_PROPERTIES CONSOLE_PROPERTIES;
struct _CONSOLE_PROPERTIES
{
	uint32_t flags; // Console device flags (eg CONSOLE_FLAG_FULLSCREEN)
	uint32_t mode; // Console device mode (eg CONSOLE_MODE_PIXEL)
	uint32_t width; // Console Width (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t height; // Console Height (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t format; // Color Format (eg COLOR_FORMAT_ARGB32)(Only applicable if CONSOLE_MODE_PIXEL)
};

typedef struct _CONSOLE_DEVICE CONSOLE_DEVICE;

/* Console Enumeration Callback */
typedef uint32_t STDCALL (*console_enumerate_cb)(CONSOLE_DEVICE *console, void *data);
/* Console Notification Callback */
typedef uint32_t STDCALL (*console_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* Console Device Methods */
typedef uint32_t STDCALL (*console_device_open_proc)(CONSOLE_DEVICE *console);
typedef uint32_t STDCALL (*console_device_close_proc)(CONSOLE_DEVICE *console);
typedef uint32_t STDCALL (*console_device_clear_proc)(CONSOLE_DEVICE *console, uint32_t color);
typedef uint32_t STDCALL (*console_device_scroll_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t count, uint32_t direction);
typedef uint32_t STDCALL (*console_device_draw_box_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
typedef uint32_t STDCALL (*console_device_draw_line_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
typedef uint32_t STDCALL (*console_device_plot_line_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
typedef uint32_t STDCALL (*console_device_draw_char_proc)(CONSOLE_DEVICE *console, FONT_HANDLE handle, char ch, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);
typedef uint32_t STDCALL (*console_device_draw_text_proc)(CONSOLE_DEVICE *console, FONT_HANDLE handle, char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, uint32_t len);
typedef uint32_t STDCALL (*console_device_draw_pixel_proc)(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t color);
typedef uint32_t STDCALL (*console_device_draw_block_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
typedef uint32_t STDCALL (*console_device_draw_circle_proc)(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t color, uint32_t width, uint32_t radius);
typedef uint32_t STDCALL (*console_device_draw_image_proc)(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t format, uint32_t skip);
typedef uint32_t STDCALL (*console_device_draw_window_proc)(CONSOLE_DEVICE *console, WINDOW_HANDLE handle, uint32_t flags);

typedef uint32_t STDCALL (*console_device_get_pixel_proc)(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t *color);
typedef uint32_t STDCALL (*console_device_get_image_proc)(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t format, uint32_t skip);

typedef uint32_t STDCALL (*console_device_put_text_proc)(CONSOLE_DEVICE *console, FONT_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, CONSOLE_CHAR *buffer, uint32_t width, uint32_t height, uint32_t skip);

typedef uint32_t STDCALL (*console_device_copy_image_proc)(CONSOLE_DEVICE *console, CONSOLE_POINT *source, CONSOLE_POINT *dest, uint32_t width, uint32_t height);

typedef HANDLE STDCALL (*console_device_add_caret_proc)(CONSOLE_DEVICE *console, uint32_t width, uint32_t height, uint32_t offsetx, uint32_t offsety);
typedef uint32_t STDCALL (*console_device_delete_caret_proc)(CONSOLE_DEVICE *console, HANDLE handle);
typedef uint32_t STDCALL (*console_device_update_caret_proc)(CONSOLE_DEVICE *console, HANDLE handle, uint32_t x, uint32_t y, BOOL visible, BOOL blink);
typedef uint32_t STDCALL (*console_device_update_caret_ex_proc)(CONSOLE_DEVICE *console, HANDLE handle, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, BOOL visible, BOOL blink, BOOL reverse);

typedef uint32_t STDCALL (*console_device_set_cursor_proc)(CONSOLE_DEVICE *console, uint32_t width, uint32_t height, char *chars);
typedef uint32_t STDCALL (*console_device_update_cursor_proc)(CONSOLE_DEVICE *console, BOOL enabled, int32_t x, int32_t y, BOOL relative);

typedef uint32_t STDCALL (*console_device_get_position_proc)(CONSOLE_DEVICE *console, uint32_t position, uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2);
typedef uint32_t STDCALL (*console_device_get_properties_proc)(CONSOLE_DEVICE *console, CONSOLE_PROPERTIES *properties);

typedef struct _CONSOLE_CARET CONSOLE_CARET;
typedef struct _CONSOLE_WINDOW CONSOLE_WINDOW;
typedef struct _CONSOLE_HISTORY CONSOLE_HISTORY;

/* Console Device */
struct _CONSOLE_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this Console device
	// Console Properties
	uint32_t consoleid; // Unique Id of this Console device in the Console device table
	uint32_t consolestate; // Console device state (eg CONSOLE_STATE_OPEN)
	uint32_t consolemode; // Console device mode (eg CONSOLE_MODE_PIXEL)
	console_device_open_proc deviceopen; // A device specific DeviceOpen method implementing a standard console device interface (Mandatory)
	console_device_close_proc deviceclose; // A device specific DeviceClose method implementing a standard console device interface (Mandatory)
	console_device_clear_proc deviceclear; // A device specific DeviceClear method implementing a standard console device interface (Mandatory)
	console_device_scroll_proc devicescroll; // A device specific DeviceScroll method implementing a standard console device interface (Mandatory)
	console_device_draw_box_proc devicedrawbox; // A device specific DeviceDrawBox method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_draw_line_proc devicedrawline; // A device specific DeviceDrawLine method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_plot_line_proc deviceplotline; // A device specific DevicePlotLine method implementing a standard console device interface (Or nil if the default method is suitable)
	console_device_draw_char_proc devicedrawchar; // A device specific DeviceDrawChar method implementing a standard console device interface (Mandatory)
	console_device_draw_text_proc devicedrawtext; // A device specific DeviceDrawText method implementing a standard console device interface (Mandatory)
	console_device_draw_pixel_proc devicedrawpixel; // A device specific DeviceDrawPixel method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_draw_block_proc devicedrawblock; // A device specific DeviceDrawBlock method implementing a standard console device interface (Mandatory)
	console_device_draw_circle_proc devicedrawcircle; // A device specific DeviceDrawCircle method implementing a standard console device interface (Or nil if the default method is suitable)
	console_device_draw_image_proc devicedrawimage; // A device specific DeviceDrawImage method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_draw_window_proc devicedrawwindow; // A device specific DeviceDrawWindow method implementing a standard console device interface (Mandatory)
	console_device_get_pixel_proc devicegetpixel; // A device specific DeviceGetPixel method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_get_image_proc devicegetimage; // A device specific DeviceGetImage method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_put_text_proc deviceputtext; // A device specific DevicePutText method implementing a standard console device interface (Mandatory)
	console_device_copy_image_proc devicecopyimage; // A device specific DeviceCopyImage method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_add_caret_proc deviceaddcaret; // A device specific DeviceAddCaret method implementing a standard console device interface (Optional)
	console_device_delete_caret_proc devicedeletecaret; // A device specific DeviceDeleteCaret method implementing a standard console device interface (Optional)
	console_device_update_caret_proc deviceupdatecaret; // A device specific DeviceUpdateCaret method implementing a standard console device interface (Optional)
	console_device_update_caret_ex_proc deviceupdatecaretex; // A device specific DeviceUpdateCaretEx method implementing a standard console device interface (Optional)
	console_device_set_cursor_proc devicesetcursor; // A device specific DeviceSetCursor method implementing a standard console device interface (Or nil if the default method is suitable)(CONSOLE_MODE_CHARACTER only)
	console_device_update_cursor_proc deviceupdatecursor; // A device specific DeviceUpdateCursor method implementing a standard console device interface (Or nil if the default method is suitable)(CONSOLE_MODE_CHARACTER only)
	console_device_get_position_proc devicegetposition; // A device specific DeviceGetPosition method implementing a standard console device interface (Mandatory)
	console_device_get_properties_proc devicegetproperties; // A device specific DeviceGetProperties method implementing a standard console device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t opencount;
	uint32_t closecount;
	uint32_t clearcount;
	uint32_t scrollcount;
	uint32_t drawcount;
	uint32_t getcount;
	uint32_t putcount;
	uint32_t copycount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	uint32_t width; // Console Width (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t height; // Console Height (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t format; // Color Format (eg COLOR_FORMAT_ARGB32)(Only applicable if CONSOLE_MODE_PIXEL)
	uint32_t forecolor; // Foreground Color
	uint32_t backcolor; // Background Color
	uint32_t borderwidth; // Border Width (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t bordercolor; // Border Color
	// Font Properties
	FONT_HANDLE font; // Console Font
	uint32_t fontratio; // Font Characters to Pixels Ratio (Normally 1 for Pixel Console / 0 for Character Console)
	// Cursor Properties
	LONGBOOL cursorupdate; // Flag to indicate if cursor update (Show/Hide) is in progress (CONSOLE_MODE_CHARACTER only)
	uint32_t cursorx; // Cursor X (Characters)(CONSOLE_MODE_CHARACTER only)
	uint32_t cursory; // Cursor Y (Characters)(CONSOLE_MODE_CHARACTER only)
	uint32_t cursorwidth; // Cursor Width (Characters)(CONSOLE_MODE_CHARACTER only)
	uint32_t cursorheight; // Cursor Height (Characters)(CONSOLE_MODE_CHARACTER only)
	LONGBOOL cursorvisible; // Cursor Visible On/Off (CONSOLE_MODE_CHARACTER only)
	char *cursorchars; // Buffer for cursor characters (CONSOLE_MODE_CHARACTER only)
	char *cursorbuffer; // Buffer for characters currently under cursor (CONSOLE_MODE_CHARACTER only)
	// Caret Properties
	CONSOLE_CARET *caretfirst;
	CRITICAL_SECTION_HANDLE caretlock;
	uint32_t caretcount;
	// Window Properties
	CONSOLE_WINDOW *windowfirst;
	CRITICAL_SECTION_HANDLE windowlock;
	uint32_t windowcount;
	CONSOLE_WINDOW *windowactive; // The active console Window (ie the Window that is shown as selected)
	WINDOW_HANDLE windowdefault; // The default console Window (ie the Window that receives standard output)(WINDOW_MODE_TEXT only)
	// Internal Properties
	CONSOLE_DEVICE *prev; // Previous entry in Console device table
	CONSOLE_DEVICE *next; // Next entry in Console device table
};

/* Console Caret */
struct _CONSOLE_CARET
{
	// Caret Properties
	uint32_t signature; // Signature for entry validation
	uint32_t x; // Caret X (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t y; // Caret Y (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t width; // Caret Width (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t height; // Caret Height (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t offsetx; // Caret Offset X (Pixels for CONSOLE_MODE_PIXEL / Always 0 for CONSOLE_MODE_CHARACTER)
	uint32_t offsety; // Caret Offset Y (Pixels for CONSOLE_MODE_PIXEL / Always 0 for CONSOLE_MODE_CHARACTER)
	LONGBOOL visible; // Caret Visible On/Off
	LONGBOOL blink; // Caret Blink On/Off
	LONGBOOL reverse; // Caret Color Reverse or Inverse
	uint32_t forecolor; // Caret Foreground Color
	uint32_t backcolor; // Caret Background Color
	CONSOLE_DEVICE *console; // Console device
	// Driver Properties
	HANDLE handle; // Device specific handle
	LONGBOOL active; // Caret currently active (displayed) (Independent of Visible to account for Blink)
	void *image; // Device specific buffer for caret image
	void *buffer; // Device specific buffer for area underneath caret
	void *output; // Device specific buffer for curently displayed caret
	// Internal Properties
	CONSOLE_CARET *prev; // Previous entry in Console Caret table
	CONSOLE_CARET *next; // Next entry in Console Caret table
};

typedef struct _WINDOW_PROPERTIES WINDOW_PROPERTIES;
struct _WINDOW_PROPERTIES
{
	uint32_t position; // Console Window Position (eg CONSOLE_POSITION_TOP)
	uint32_t state; // Console Window State (eg WINDOW_STATE_VISIBLE)
	uint32_t mode; // Console Window Mode (eg WINDOW_MODE_TEXT)
	uint32_t flags; // Console Window Flags (eg WINDOW_FLAG_LINE_WRAP)
	uint32_t x1; // Window X1
	uint32_t y1; // Window Y1
	uint32_t x2; // Window X2
	uint32_t y2; // Window Y2
	uint32_t width; // Window Width in Columns (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t height; // Window Height in Rows (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t offsetx; // Window X Offset (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t offsety; // Window Y Offset (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t fontwidth; // Font Width (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t fontheight; // Font Height (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t borderwidth; // Current Border Width
	FONT_HANDLE font; // Window Font
	CONSOLE_DEVICE *console; // Window console
};

/* Console Window Enumeration Callback */
typedef uint32_t STDCALL (*console_window_enumerate_cb)(CONSOLE_DEVICE *console, WINDOW_HANDLE handle, void *data);

/* Console Window Completion Callback */
typedef uint32_t STDCALL (*console_window_completion_cb)(WINDOW_HANDLE handle, char *buffer, void *data);

/* Console Window */
struct _CONSOLE_WINDOW
{
	// Window Properties
	uint32_t signature; // Signature for entry validation
	uint32_t position; // Console Window Position (eg CONSOLE_POSITION_TOP)
	uint32_t windowstate; // Console Window State (eg WINDOW_STATE_VISIBLE)
	uint32_t windowmode; // Console Window Mode (eg WINDOW_MODE_TEXT)
	uint32_t windowflags; // Console Window Flags (eg WINDOW_FLAG_LINE_WRAP)
	uint32_t x1; // Window X1
	uint32_t y1; // Window Y1
	uint32_t x2; // Window X2
	uint32_t y2; // Window Y2
	uint32_t width; // Window Width in Columns (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t height; // Window Height in Rows (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t offsetx; // Window X Offset (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t offsety; // Window Y Offset (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t minx; // Viewport X1
	uint32_t miny; // Viewport Y1
	uint32_t maxx; // Viewport X2
	uint32_t maxy; // Viewport Y2
	uint32_t x; // Current X
	uint32_t y; // Current Y
	uint32_t cols; // Viewport Columns (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t rows; // Viewport Rows (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t format; // Color Format (eg COLOR_FORMAT_ARGB32)(Only applicable if CONSOLE_MODE_PIXEL)
	uint32_t forecolor; // Current Foreground Color
	uint32_t backcolor; // Current Background Color
	uint32_t borderwidth; // Current Border Width
	uint32_t bordercolor; // Current Border Color
	// Font Properties
	FONT_HANDLE font; // Window Font
	uint32_t fontwidth; // Font Width (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t fontheight; // Font Height (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	// Cursor Properties
	uint32_t cursorx; // Cursor X
	uint32_t cursory; // Cursor Y
	CURSOR_MODE cursormode; // Cursor Mode Insert/Overwrite
	LONGBOOL cursorblink; // Cursor Blink On/Off
	CURSOR_STATE cursorstate; // Cursor State On/Off
	CURSOR_SHAPE cursorshape; // Cursor Shape Line/Bar/Block
	LONGBOOL cursorreverse; // Cursor Color Reverse or Inverse (WINDOW_MODE_TEXT only)
	uint32_t cursorforecolor; // Cursor Foreground Color (WINDOW_MODE_TEXT only)
	uint32_t cursorbackcolor; // Cursor Background Color (WINDOW_MODE_TEXT only)
	// Caret Properties
	uint32_t caretx; // Caret X
	uint32_t carety; // Caret Y
	HANDLE carethandle; // Caret (Cursor) Handle (or INVALID_HANDLE_VALUE)
	// History Properties
	CONSOLE_HISTORY *historyfirst;
	CONSOLE_HISTORY *historylast;
	CONSOLE_HISTORY *historycurrent;
	uint32_t historycount;
	// Driver Properties
	MUTEX_HANDLE lock; // Window lock
	CONSOLE_DEVICE *console; // Window console
	// Internal Properties
	CONSOLE_WINDOW *prev; // Previous entry in Console Window table
	CONSOLE_WINDOW *next; // Next entry in Console Window table
};

struct _CONSOLE_HISTORY
{
	// History Properties
	char *value;
	int length;
	// Internal Properties
	CONSOLE_HISTORY *prev; // Previous entry in History table
	CONSOLE_HISTORY *next; // Next entry in History table
};

/* ============================================================================== */
/* Console Functions */
uint32_t STDCALL console_device_open(CONSOLE_DEVICE *console);
uint32_t STDCALL console_device_close(CONSOLE_DEVICE *console);

uint32_t STDCALL console_device_clear(CONSOLE_DEVICE *console, uint32_t color);
uint32_t STDCALL console_device_scroll(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t count, uint32_t direction);

uint32_t STDCALL console_device_draw_box(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
uint32_t STDCALL console_device_draw_line(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
uint32_t STDCALL console_device_plot_line(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
uint32_t STDCALL console_device_draw_char(CONSOLE_DEVICE *console, FONT_HANDLE handle, char ch, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);
uint32_t STDCALL console_device_draw_text(CONSOLE_DEVICE *console, FONT_HANDLE handle, char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, uint32_t len);
uint32_t STDCALL console_device_draw_pixel(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t color);
uint32_t STDCALL console_device_draw_block(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
uint32_t STDCALL console_device_draw_circle(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t color, uint32_t width, uint32_t radius);
uint32_t STDCALL console_device_draw_image(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t format, uint32_t skip);
uint32_t STDCALL console_device_draw_window(CONSOLE_DEVICE *console, WINDOW_HANDLE handle, uint32_t flags);

uint32_t STDCALL console_device_get_pixel(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t *color);
uint32_t STDCALL console_device_get_image(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t format, uint32_t skip);

uint32_t STDCALL console_device_put_text(CONSOLE_DEVICE *console, FONT_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, CONSOLE_CHAR *buffer, uint32_t width, uint32_t height, uint32_t skip);

uint32_t STDCALL console_device_copy_image(CONSOLE_DEVICE *console, CONSOLE_POINT *source, CONSOLE_POINT *dest, uint32_t width, uint32_t height);

HANDLE STDCALL console_device_add_caret(CONSOLE_DEVICE *console, uint32_t width, uint32_t height, uint32_t offsetx, uint32_t offsety);
uint32_t STDCALL console_device_delete_caret(CONSOLE_DEVICE *console, HANDLE handle);
uint32_t STDCALL console_device_update_caret(CONSOLE_DEVICE *console, HANDLE handle, uint32_t x, uint32_t y, BOOL visible, BOOL blink);
uint32_t STDCALL console_device_update_caret_ex(CONSOLE_DEVICE *console, HANDLE handle, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, BOOL visible, BOOL blink, BOOL reverse);

uint32_t STDCALL console_device_set_cursor(CONSOLE_DEVICE *console, uint32_t width, uint32_t height, char *chars);
uint32_t STDCALL console_device_update_cursor(CONSOLE_DEVICE *console, BOOL enabled, int32_t x, int32_t y, BOOL relative);

uint32_t STDCALL console_device_get_position(CONSOLE_DEVICE *console, uint32_t position, uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2);
uint32_t STDCALL console_device_get_properties(CONSOLE_DEVICE *console, CONSOLE_PROPERTIES *properties);

BOOL STDCALL console_device_check_flag(CONSOLE_DEVICE *console, uint32_t flag);
uint32_t STDCALL console_device_update_flag(CONSOLE_DEVICE *console, uint32_t flag, BOOL clear);

uint32_t STDCALL console_device_get_mode(CONSOLE_DEVICE *console);
uint32_t STDCALL console_device_get_state(CONSOLE_DEVICE *console);

CONSOLE_DEVICE * STDCALL console_device_create(void);
CONSOLE_DEVICE * STDCALL console_device_create_ex(uint32_t size);
uint32_t STDCALL console_device_destroy(CONSOLE_DEVICE *console);

uint32_t STDCALL console_device_register(CONSOLE_DEVICE *console);
uint32_t STDCALL console_device_deregister(CONSOLE_DEVICE *console);

CONSOLE_DEVICE * STDCALL console_device_find(uint32_t consoleid);
CONSOLE_DEVICE * STDCALL console_device_find_by_device(DEVICE *device);
CONSOLE_DEVICE * STDCALL console_device_find_by_name(char *name);
CONSOLE_DEVICE * STDCALL console_device_find_by_description(char *description);
uint32_t STDCALL console_device_enumerate(console_enumerate_cb callback, void *data);

uint32_t STDCALL console_device_notification(CONSOLE_DEVICE *console, console_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* Text Console Functions */
WINDOW_HANDLE STDCALL console_window_create(CONSOLE_DEVICE *console, uint32_t position, BOOL _default);
WINDOW_HANDLE STDCALL console_window_create_ex(CONSOLE_DEVICE *console, FONT_HANDLE font, uint32_t size, uint32_t state, uint32_t mode, uint32_t position, BOOL _default);
uint32_t STDCALL console_window_destroy(WINDOW_HANDLE handle);

uint32_t STDCALL console_window_show(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_hide(WINDOW_HANDLE handle);

uint32_t STDCALL console_window_activate(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_deactivate(WINDOW_HANDLE handle);

WINDOW_HANDLE STDCALL console_window_next(CONSOLE_DEVICE *console, BOOL visible);
WINDOW_HANDLE STDCALL console_window_previous(CONSOLE_DEVICE *console, BOOL visible);

WINDOW_HANDLE STDCALL console_window_at(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, BOOL visible);
WINDOW_HANDLE STDCALL console_window_find(CONSOLE_DEVICE *console, uint32_t position);
uint32_t STDCALL console_window_enumerate(CONSOLE_DEVICE *console, console_window_enumerate_cb callback, void *data);

BOOL STDCALL console_window_check_flag(WINDOW_HANDLE handle, uint32_t flag);
uint32_t STDCALL console_window_update_flag(WINDOW_HANDLE handle, uint32_t flag, BOOL clear);

uint32_t STDCALL console_window_get_mode(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_get_state(WINDOW_HANDLE handle);

uint32_t STDCALL console_window_get_position(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_position(WINDOW_HANDLE handle, uint32_t position);

uint32_t STDCALL console_window_get_properties(WINDOW_HANDLE handle, WINDOW_PROPERTIES *properties);

uint32_t STDCALL console_window_get_min_x(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_get_min_y(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_get_max_x(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_get_max_y(WINDOW_HANDLE handle);

CONSOLE_RECT STDCALL console_window_get_rect(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_rect(WINDOW_HANDLE handle, CONSOLE_RECT *rect);
uint32_t STDCALL console_window_reset_rect(WINDOW_HANDLE handle);

uint32_t STDCALL console_window_get_viewport(WINDOW_HANDLE handle, uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2);
uint32_t STDCALL console_window_set_viewport(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
uint32_t STDCALL console_window_reset_viewport(WINDOW_HANDLE handle);

uint32_t STDCALL console_window_get_x(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_x(WINDOW_HANDLE handle, uint32_t x);
uint32_t STDCALL console_window_get_y(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_y(WINDOW_HANDLE handle, uint32_t y);

uint32_t STDCALL console_window_get_xy(WINDOW_HANDLE handle, uint32_t *x, uint32_t *y);
uint32_t STDCALL console_window_set_xy(WINDOW_HANDLE handle, uint32_t x, uint32_t y);

CONSOLE_POINT STDCALL console_window_get_point(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_point(WINDOW_HANDLE handle, CONSOLE_POINT *point);

uint32_t STDCALL console_window_get_cols(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_get_rows(WINDOW_HANDLE handle);

uint32_t STDCALL console_window_get_width(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_get_height(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_get_format(WINDOW_HANDLE handle);

uint32_t STDCALL console_window_get_forecolor(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_forecolor(WINDOW_HANDLE handle, uint32_t color);
uint32_t STDCALL console_window_get_backcolor(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_backcolor(WINDOW_HANDLE handle, uint32_t color);

FONT_HANDLE STDCALL console_window_get_font(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_font(WINDOW_HANDLE handle, FONT_HANDLE font);

uint32_t STDCALL console_window_get_cursor_xy(WINDOW_HANDLE handle, uint32_t *x, uint32_t *y);
uint32_t STDCALL console_window_set_cursor_xy(WINDOW_HANDLE handle, uint32_t x, uint32_t y);
CURSOR_MODE STDCALL console_window_get_cursor_mode(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_cursor_mode(WINDOW_HANDLE handle, CURSOR_MODE cursormode);
BOOL STDCALL console_window_get_cursor_blink(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_cursor_blink(WINDOW_HANDLE handle, BOOL cursorblink);
CURSOR_STATE STDCALL console_window_get_cursor_state(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_cursor_state(WINDOW_HANDLE handle, CURSOR_STATE cursorstate);
CURSOR_SHAPE STDCALL console_window_get_cursor_shape(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_cursor_shape(WINDOW_HANDLE handle, CURSOR_SHAPE cursorshape);
uint32_t STDCALL console_window_get_cursor_color(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_cursor_color(WINDOW_HANDLE handle, uint32_t color);
BOOL STDCALL console_window_get_cursor_reverse(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_set_cursor_reverse(WINDOW_HANDLE handle, BOOL cursorreverse);

uint32_t STDCALL console_window_cursor_on(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_cursor_off(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_cursor_line(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_cursor_bar(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_cursor_block(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_cursor_move(WINDOW_HANDLE handle, uint32_t x, uint32_t y);
uint32_t STDCALL console_window_cursor_blink(WINDOW_HANDLE handle, BOOL enabled);
uint32_t STDCALL console_window_cursor_color(WINDOW_HANDLE handle, uint32_t color);
uint32_t STDCALL console_window_cursor_reverse(WINDOW_HANDLE handle, BOOL enabled);

uint32_t STDCALL console_window_add_history(WINDOW_HANDLE handle, char *value);
uint32_t STDCALL console_window_clear_history(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_first_history(WINDOW_HANDLE handle, char *value, uint32_t len);
uint32_t STDCALL console_window_last_history(WINDOW_HANDLE handle, char *value, uint32_t len);
uint32_t STDCALL console_window_next_history(WINDOW_HANDLE handle, char *value, uint32_t len);
uint32_t STDCALL console_window_previous_history(WINDOW_HANDLE handle, char *value, uint32_t len);
uint32_t STDCALL console_window_current_history(WINDOW_HANDLE handle, char *value, uint32_t len);

uint32_t STDCALL console_window_scroll_up(WINDOW_HANDLE handle, uint32_t row, uint32_t lines);
uint32_t STDCALL console_window_scroll_down(WINDOW_HANDLE handle, uint32_t row, uint32_t lines);

uint32_t STDCALL console_window_scroll_left(WINDOW_HANDLE handle, uint32_t row, uint32_t col, uint32_t lines, uint32_t chars);
uint32_t STDCALL console_window_scroll_right(WINDOW_HANDLE handle, uint32_t row, uint32_t col, uint32_t lines, uint32_t chars);

uint32_t STDCALL console_window_clear(WINDOW_HANDLE handle);
uint32_t STDCALL console_window_clear_ex(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, BOOL cursor);

uint32_t STDCALL console_window_write(WINDOW_HANDLE handle, char *text);
uint32_t STDCALL console_window_write_ex(WINDOW_HANDLE handle, char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

uint32_t STDCALL console_window_write_ln(WINDOW_HANDLE handle, char *text);
uint32_t STDCALL console_window_write_ln_ex(WINDOW_HANDLE handle, char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

uint32_t STDCALL console_window_write_chr(WINDOW_HANDLE handle, char ch);
uint32_t STDCALL console_window_write_chr_ex(WINDOW_HANDLE handle, char ch, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

uint32_t STDCALL console_window_output(WINDOW_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, CONSOLE_CHAR *buffer, uint32_t width, uint32_t height, uint32_t skip);

uint32_t STDCALL console_window_read(WINDOW_HANDLE handle, char *text, uint32_t *len);

uint32_t STDCALL console_window_read_ln(WINDOW_HANDLE handle, char *text, uint32_t *len);
uint32_t STDCALL console_window_read_ln_ex(WINDOW_HANDLE handle, char *text, uint32_t *len, char *prompt, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, BOOL scroll, BOOL history, console_window_completion_cb completion, void *data);

uint32_t STDCALL console_window_read_chr(WINDOW_HANDLE handle, char *ch);
uint32_t STDCALL console_window_read_chr_ex(WINDOW_HANDLE handle, char *ch, char *prompt, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, BOOL echo, BOOL scroll);

/* ============================================================================== */
/* CRT Console Functions */
void STDCALL console_clr_eol(void);
void STDCALL console_clr_scr(void);
void STDCALL console_delay(uint16_t ms);
void STDCALL console_del_line(void);
void STDCALL console_goto_xy(int x, int y);
void STDCALL console_high_video(void);
void STDCALL console_ins_line(void);
BOOL STDCALL console_keypressed(void);
void STDCALL console_low_video(void);
void STDCALL console_norm_video(void);
void STDCALL console_no_sound(void);
char STDCALL console_read_key(void);
void STDCALL console_sound(uint16_t hz);
void STDCALL console_text_background(uint32_t color);
void STDCALL console_text_color(uint32_t color);
void STDCALL console_text_mode(int mode);
int STDCALL console_where_x(void);
int STDCALL console_where_y(void);
void STDCALL console_window(int x1, int y1, int x2, int y2);
void STDCALL console_scroll_up(int row, int lines);
void STDCALL console_scroll_down(int row, int lines);

void STDCALL console_write(char *text);
void STDCALL console_write_ln(char *text);
void STDCALL console_write_chr(char ch);

void STDCALL console_read(char *text, uint32_t *len);
void STDCALL console_read_ln(char *text, uint32_t *len);
void STDCALL console_read_chr(char *ch);

/* ============================================================================== */
/* Console Helper Functions */
uint32_t STDCALL console_device_get_count(void);
CONSOLE_DEVICE * STDCALL console_device_get_default(void);
uint32_t STDCALL console_device_set_default(CONSOLE_DEVICE *console);

CONSOLE_DEVICE * STDCALL console_device_check(CONSOLE_DEVICE *console);
CONSOLE_CARET * STDCALL console_device_caret_check(CONSOLE_DEVICE *console, CONSOLE_CARET *caret);

uint32_t STDCALL console_type_to_string(uint32_t consoletype, char *value, uint32_t len);
uint32_t STDCALL console_state_to_string(uint32_t consolestate, char *value, uint32_t len);

FONT_HANDLE STDCALL console_device_get_default_font(void);

uint32_t STDCALL console_position_to_string(uint32_t position, char *value, uint32_t len);

/* ============================================================================== */
/* Text Console Helper Functions */
uint32_t STDCALL console_window_get_count(CONSOLE_DEVICE *console);
WINDOW_HANDLE STDCALL console_window_get_active(CONSOLE_DEVICE *console);
WINDOW_HANDLE STDCALL console_window_get_default(CONSOLE_DEVICE *console);
uint32_t STDCALL console_window_set_default(CONSOLE_DEVICE *console, WINDOW_HANDLE handle);

CONSOLE_WINDOW * STDCALL console_window_check(CONSOLE_DEVICE *console, CONSOLE_WINDOW *window);

uint32_t STDCALL console_window_state_to_string(uint32_t windowstate, char *value, uint32_t len);
uint32_t STDCALL console_window_mode_to_string(uint32_t windowmode, char *value, uint32_t len);

FONT_HANDLE STDCALL console_window_get_default_font(void);

BOOL STDCALL console_window_redirect_output(WINDOW_HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_CONSOLE_H