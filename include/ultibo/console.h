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
#ifndef _ULTIBO_CONSOLE_H
#define _ULTIBO_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/** Console specific constants */
#define CONSOLE_NAME_PREFIX	"Console" ///< Name prefix for Console Devices

/** Console Device Types */
#define CONSOLE_TYPE_NONE	0
#define CONSOLE_TYPE_FRAMEBUFFER	1
#define CONSOLE_TYPE_SERIAL	2
#define CONSOLE_TYPE_REMOTE	3
#define CONSOLE_TYPE_LCD	4

#define CONSOLE_TYPE_MAX	4

/** Console Device States */
#define CONSOLE_STATE_CLOSED	0
#define CONSOLE_STATE_OPEN	1

#define CONSOLE_STATE_MAX	1

/** Console Device Flags */
#define CONSOLE_FLAG_NONE	0x00000000
#define CONSOLE_FLAG_LINE_WRAP	0x00000001 ///< Wrap long lines to the next line if set
#define CONSOLE_FLAG_DMA_BOX	0x00000002 ///< Use DMA to draw boxes (Where applicable)
#define CONSOLE_FLAG_DMA_LINE	0x00000004 ///< Use DMA to draw lines (Where applicable)
#define CONSOLE_FLAG_DMA_FILL	0x00000008 ///< Use DMA to fill blocks (Where applicable)
#define CONSOLE_FLAG_DMA_CLEAR	0x00000010 ///< Use DMA to clear blocks (Where applicable)
#define CONSOLE_FLAG_DMA_SCROLL	0x00000020 ///< Use DMA to scroll blocks (Where applicable)
#define CONSOLE_FLAG_SINGLE_WINDOW	0x00000040 ///< Console supports only one window (Not multiple)
#define CONSOLE_FLAG_HARDWARE_CURSOR	0x00000080 ///< Console supports a hardware cursor (Mouse pointer) (Character mode only)
#define CONSOLE_FLAG_HARDWARE_CARET	0x00000100 ///< Console supports a hardware caret (Text cursor)
#define CONSOLE_FLAG_BLINK_CARET	0x00000200 ///< Console supports blinking caret
#define CONSOLE_FLAG_TEXT_MODE	0x00000400 ///< Console supports text mode settings
#define CONSOLE_FLAG_TEXT_BLINK	0x00000800 ///< Console supports blinking text
#define CONSOLE_FLAG_COLOR	0x00001000 ///< Console supports colors
#define CONSOLE_FLAG_FONT	0x00002000 ///< Console supports fonts
#define CONSOLE_FLAG_FULLSCREEN	0x00004000 ///< Console supports creating a fullscreen window
#define CONSOLE_FLAG_AUTO_SCROLL	0x00008000 ///< Automatically scroll up on reaching the last line
#define CONSOLE_FLAG_DMA_TEXT	0x00010000 ///< Use DMA to draw text (Where applicable)
#define CONSOLE_FLAG_COLOR_REVERSE	0x00020000 ///< Console requires colors to be reversed for underlying hardware
#define CONSOLE_FLAG_TEXT_CARET	0x00040000 ///< Console supports a caret (Text cursor
#define CONSOLE_FLAG_FOCUS_CARET	0x00080000 ///< Only show caret on the focused (active) window

#define CONSOLE_FLAG_DMA_MASK	CONSOLE_FLAG_DMA_BOX | CONSOLE_FLAG_DMA_LINE | CONSOLE_FLAG_DMA_FILL | CONSOLE_FLAG_DMA_CLEAR | CONSOLE_FLAG_DMA_SCROLL | CONSOLE_FLAG_DMA_TEXT

/** Flags that cannot be changed by ConsoleDeviceUpdateFlag */
#define CONSOLE_FLAG_INTERNAL	CONSOLE_FLAG_SINGLE_WINDOW | CONSOLE_FLAG_HARDWARE_CURSOR | CONSOLE_FLAG_HARDWARE_CARET | CONSOLE_FLAG_BLINK_CARET | CONSOLE_FLAG_TEXT_MODE | CONSOLE_FLAG_TEXT_BLINK | CONSOLE_FLAG_COLOR | CONSOLE_FLAG_FONT | CONSOLE_FLAG_FULLSCREEN | CONSOLE_FLAG_COLOR_REVERSE | CONSOLE_FLAG_TEXT_CARET

/** Console Device Modes */
#define CONSOLE_MODE_NONE	0
#define CONSOLE_MODE_PIXEL	1
#define CONSOLE_MODE_CHARACTER	2

/** Console Caret Signature */
#define CARET_SIGNATURE	0x9A2D40E3

/** Console Window Signature */
#define WINDOW_SIGNATURE	0xDE3A5C04

/** Console Window States */
#define WINDOW_STATE_INVISIBLE	0
#define WINDOW_STATE_VISIBLE	1

#define WINDOW_STATE_MAX	1

/** Console Window Modes */
#define WINDOW_MODE_NONE	0
#define WINDOW_MODE_TEXT	1
#define WINDOW_MODE_GRAPHICS	2

#define WINDOW_MODE_MAX	2

/** Console Window Flags */
#define WINDOW_FLAG_NONE	0x00000000
#define WINDOW_FLAG_LINE_WRAP	0x00000001 ///< Wrap long lines to the next line if set
#define WINDOW_FLAG_BUFFERED	0x00000002 ///< Buffer output for scroll back and redraw
#define WINDOW_FLAG_FULLSCREEN	0x00000004 ///< Window occupies the full screen
#define WINDOW_FLAG_AUTO_SCROLL	0x00000008 ///< Automatically scroll up on reaching the last line
#define WINDOW_FLAG_CHARACTER	0x00000010 ///< Console for this Window is character mode only
#define WINDOW_FLAG_AUTO_UPDATE	0x00000020 ///< Automatically update output of buffered window
#define WINDOW_FLAG_FOCUS_CURSOR	0x00000040 ///< Only show cursor (caret) on the focused (active) window

/** Flags that cannot be changed by ConsoleWindowUpdateFlag */
#define WINDOW_FLAG_INTERNAL	WINDOW_FLAG_FULLSCREEN | WINDOW_FLAG_CHARACTER

/** Console Window Draw Flags */
#define WINDOW_DRAW_FLAG_NONE	0x00000000
#define WINDOW_DRAW_FLAG_BODY	0x00000001 ///< Draw the Window body
#define WINDOW_DRAW_FLAG_TITLE	0x00000002 ///< Draw the Window title
#define WINDOW_DRAW_FLAG_BORDER	0x00000004 ///< Draw the Window border

#define WINDOW_DRAW_FLAG_ALL	WINDOW_DRAW_FLAG_BODY | WINDOW_DRAW_FLAG_TITLE | WINDOW_DRAW_FLAG_BORDER

/** Console Window History */
#define WINDOW_HISTORY_MAX_COUNT	100

/** Framebuffer Console specific constants */
#define FRAMEBUFFER_CONSOLE_DESCRIPTION	"Framebuffer Console" ///< Description of the Framebuffer Console device

/** Console specific types */
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

typedef enum
{
 CURSOR_SHAPE_LINE, ///< Line is a vertical line and (All shapes inverse any character data under them)
 CURSOR_SHAPE_BAR, ///< Bar is a horizontal bar (All shapes inverse any character data under them)
 CURSOR_SHAPE_BLOCK ///< Block is a solid block (All shapes inverse any character data under them)
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
	uint32_t flags; ///< Console device flags (eg CONSOLE_FLAG_FULLSCREEN)
	uint32_t mode; ///< Console device mode (eg CONSOLE_MODE_PIXEL)
	uint32_t width; ///< Console Width (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t height; ///< Console Height (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t format; ///< Color Format (eg COLOR_FORMAT_ARGB32)(Only applicable if CONSOLE_MODE_PIXEL)
};

typedef struct _CONSOLE_DEVICE CONSOLE_DEVICE;

/** Console Enumeration Callback */
typedef uint32_t STDCALL (*console_enumerate_cb)(CONSOLE_DEVICE *console, void *data);
/** Console Notification Callback */
typedef uint32_t STDCALL (*console_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** Console Device Methods */
typedef uint32_t STDCALL (*console_device_open_proc)(CONSOLE_DEVICE *console);
typedef uint32_t STDCALL (*console_device_close_proc)(CONSOLE_DEVICE *console);
typedef uint32_t STDCALL (*console_device_clear_proc)(CONSOLE_DEVICE *console, uint32_t color);
typedef uint32_t STDCALL (*console_device_scroll_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t count, uint32_t direction);
typedef uint32_t STDCALL (*console_device_draw_box_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
typedef uint32_t STDCALL (*console_device_draw_line_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
typedef uint32_t STDCALL (*console_device_plot_line_proc)(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
typedef uint32_t STDCALL (*console_device_draw_char_proc)(CONSOLE_DEVICE *console, FONT_HANDLE handle, char ch, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);
typedef uint32_t STDCALL (*console_device_draw_text_proc)(CONSOLE_DEVICE *console, FONT_HANDLE handle, const char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, uint32_t len);
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

/** Console Device */
struct _CONSOLE_DEVICE
{
	// Device Properties
	DEVICE device; ///< The Device entry for this Console device
	// Console Properties
	uint32_t consoleid; ///< Unique Id of this Console device in the Console device table
	uint32_t consolestate; ///< Console device state (eg CONSOLE_STATE_OPEN)
	uint32_t consolemode; ///< Console device mode (eg CONSOLE_MODE_PIXEL)
	console_device_open_proc deviceopen; ///< A device specific DeviceOpen method implementing a standard console device interface (Mandatory)
	console_device_close_proc deviceclose; ///< A device specific DeviceClose method implementing a standard console device interface (Mandatory)
	console_device_clear_proc deviceclear; ///< A device specific DeviceClear method implementing a standard console device interface (Mandatory)
	console_device_scroll_proc devicescroll; ///< A device specific DeviceScroll method implementing a standard console device interface (Mandatory)
	console_device_draw_box_proc devicedrawbox; ///< A device specific DeviceDrawBox method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_draw_line_proc devicedrawline; ///< A device specific DeviceDrawLine method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_plot_line_proc deviceplotline; ///< A device specific DevicePlotLine method implementing a standard console device interface (Or nil if the default method is suitable)
	console_device_draw_char_proc devicedrawchar; ///< A device specific DeviceDrawChar method implementing a standard console device interface (Mandatory)
	console_device_draw_text_proc devicedrawtext; ///< A device specific DeviceDrawText method implementing a standard console device interface (Mandatory)
	console_device_draw_pixel_proc devicedrawpixel; ///< A device specific DeviceDrawPixel method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_draw_block_proc devicedrawblock; ///< A device specific DeviceDrawBlock method implementing a standard console device interface (Mandatory)
	console_device_draw_circle_proc devicedrawcircle; ///< A device specific DeviceDrawCircle method implementing a standard console device interface (Or nil if the default method is suitable)
	console_device_draw_image_proc devicedrawimage; ///< A device specific DeviceDrawImage method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_draw_window_proc devicedrawwindow; ///< A device specific DeviceDrawWindow method implementing a standard console device interface (Mandatory)
	console_device_get_pixel_proc devicegetpixel; ///< A device specific DeviceGetPixel method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_get_image_proc devicegetimage; ///< A device specific DeviceGetImage method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_put_text_proc deviceputtext; ///< A device specific DevicePutText method implementing a standard console device interface (Mandatory)
	console_device_copy_image_proc devicecopyimage; ///< A device specific DeviceCopyImage method implementing a standard console device interface (Mandatory for CONSOLE_MODE_PIXEL)
	console_device_add_caret_proc deviceaddcaret; ///< A device specific DeviceAddCaret method implementing a standard console device interface (Optional)
	console_device_delete_caret_proc devicedeletecaret; ///< A device specific DeviceDeleteCaret method implementing a standard console device interface (Optional)
	console_device_update_caret_proc deviceupdatecaret; ///< A device specific DeviceUpdateCaret method implementing a standard console device interface (Optional)
	console_device_update_caret_ex_proc deviceupdatecaretex; ///< A device specific DeviceUpdateCaretEx method implementing a standard console device interface (Optional)
	console_device_set_cursor_proc devicesetcursor; ///< A device specific DeviceSetCursor method implementing a standard console device interface (Or nil if the default method is suitable)(CONSOLE_MODE_CHARACTER only)
	console_device_update_cursor_proc deviceupdatecursor; ///< A device specific DeviceUpdateCursor method implementing a standard console device interface (Or nil if the default method is suitable)(CONSOLE_MODE_CHARACTER only)
	console_device_get_position_proc devicegetposition; ///< A device specific DeviceGetPosition method implementing a standard console device interface (Mandatory)
	console_device_get_properties_proc devicegetproperties; ///< A device specific DeviceGetProperties method implementing a standard console device interface (Or nil if the default method is suitable)
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
	MUTEX_HANDLE lock; ///< Device lock
	uint32_t width; ///< Console Width (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t height; ///< Console Height (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t format; ///< Color Format (eg COLOR_FORMAT_ARGB32)(Only applicable if CONSOLE_MODE_PIXEL)
	uint32_t forecolor; ///< Foreground Color
	uint32_t backcolor; ///< Background Color
	uint32_t borderwidth; ///< Border Width (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t bordercolor; ///< Border Color
	// Font Properties
	FONT_HANDLE font; ///< Console Font
	uint32_t fontratio; ///< Font Characters to Pixels Ratio (Normally 1 for Pixel Console / 0 for Character Console)
	// Cursor Properties
	LONGBOOL cursorupdate; ///< Flag to indicate if cursor update (Show/Hide) is in progress (CONSOLE_MODE_CHARACTER only)
	uint32_t cursorx; ///< Cursor X (Characters)(CONSOLE_MODE_CHARACTER only)
	uint32_t cursory; ///< Cursor Y (Characters)(CONSOLE_MODE_CHARACTER only)
	uint32_t cursorwidth; ///< Cursor Width (Characters)(CONSOLE_MODE_CHARACTER only)
	uint32_t cursorheight; ///< Cursor Height (Characters)(CONSOLE_MODE_CHARACTER only)
	LONGBOOL cursorvisible; ///< Cursor Visible On/Off (CONSOLE_MODE_CHARACTER only)
	char *cursorchars; ///< Buffer for cursor characters (CONSOLE_MODE_CHARACTER only)
	char *cursorbuffer; ///< Buffer for characters currently under cursor (CONSOLE_MODE_CHARACTER only)
	// Caret Properties
	CONSOLE_CARET *caretfirst;
	CRITICAL_SECTION_HANDLE caretlock;
	uint32_t caretcount;
	// Window Properties
	CONSOLE_WINDOW *windowfirst;
	CRITICAL_SECTION_HANDLE windowlock;
	uint32_t windowcount;
	CONSOLE_WINDOW *windowactive; ///< The active console Window (ie the Window that is shown as selected)
	WINDOW_HANDLE windowdefault; ///< The default console Window (ie the Window that receives standard output)(WINDOW_MODE_TEXT only)
	// Internal Properties
	CONSOLE_DEVICE *prev; ///< Previous entry in Console device table
	CONSOLE_DEVICE *next; ///< Next entry in Console device table
};

/** Console Caret */
struct _CONSOLE_CARET
{
	// Caret Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t x; ///< Caret X (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t y; ///< Caret Y (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t width; ///< Caret Width (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t height; ///< Caret Height (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t offsetx; ///< Caret Offset X (Pixels for CONSOLE_MODE_PIXEL / Always 0 for CONSOLE_MODE_CHARACTER)
	uint32_t offsety; ///< Caret Offset Y (Pixels for CONSOLE_MODE_PIXEL / Always 0 for CONSOLE_MODE_CHARACTER)
	LONGBOOL visible; ///< Caret Visible On/Off
	LONGBOOL blink; ///< Caret Blink On/Off
	LONGBOOL reverse; ///< Caret Color Reverse or Inverse
	uint32_t forecolor; ///< Caret Foreground Color
	uint32_t backcolor; ///< Caret Background Color
	CONSOLE_DEVICE *console; ///< Console device
	// Driver Properties
	HANDLE handle; ///< Device specific handle
	LONGBOOL active; ///< Caret currently active (displayed) (Independent of Visible to account for Blink)
	void *image; ///< Device specific buffer for caret image
	void *buffer; ///< Device specific buffer for area underneath caret
	void *output; ///< Device specific buffer for curently displayed caret
	// Internal Properties
	CONSOLE_CARET *prev; ///< Previous entry in Console Caret table
	CONSOLE_CARET *next; ///< Next entry in Console Caret table
};

typedef struct _WINDOW_PROPERTIES WINDOW_PROPERTIES;
struct _WINDOW_PROPERTIES
{
	uint32_t position; ///< Console Window Position (eg CONSOLE_POSITION_TOP)
	uint32_t state; ///< Console Window State (eg WINDOW_STATE_VISIBLE)
	uint32_t mode; ///< Console Window Mode (eg WINDOW_MODE_TEXT)
	uint32_t flags; ///< Console Window Flags (eg WINDOW_FLAG_LINE_WRAP)
	uint32_t x1; ///< Window X1
	uint32_t y1; ///< Window Y1
	uint32_t x2; ///< Window X2
	uint32_t y2; ///< Window Y2
	uint32_t width; ///< Window Width in Columns (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t height; ///< Window Height in Rows (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t offsetx; ///< Window X Offset (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t offsety; ///< Window Y Offset (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t fontwidth; ///< Font Width (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t fontheight; ///< Font Height (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t borderwidth; ///< Current Border Width
	FONT_HANDLE font; ///< Window Font
	CONSOLE_DEVICE *console; ///< Window console
};

/** Console Window Enumeration Callback */
typedef uint32_t STDCALL (*console_window_enumerate_cb)(CONSOLE_DEVICE *console, WINDOW_HANDLE handle, void *data);

/** Console Window Completion Callback */
typedef uint32_t STDCALL (*console_window_completion_cb)(WINDOW_HANDLE handle, char *buffer, void *data);

/** Console Window */
struct _CONSOLE_WINDOW
{
	// Window Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t position; ///< Console Window Position (eg CONSOLE_POSITION_TOP)
	uint32_t windowstate; ///< Console Window State (eg WINDOW_STATE_VISIBLE)
	uint32_t windowmode; ///< Console Window Mode (eg WINDOW_MODE_TEXT)
	uint32_t windowflags; ///< Console Window Flags (eg WINDOW_FLAG_LINE_WRAP)
	uint32_t x1; ///< Window X1
	uint32_t y1; ///< Window Y1
	uint32_t x2; ///< Window X2
	uint32_t y2; ///< Window Y2
	uint32_t width; ///< Window Width in Columns (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t height; ///< Window Height in Rows (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t offsetx; ///< Window X Offset (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t offsety; ///< Window Y Offset (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
	uint32_t minx; ///< Viewport X1
	uint32_t miny; ///< Viewport Y1
	uint32_t maxx; ///< Viewport X2
	uint32_t maxy; ///< Viewport Y2
	uint32_t x; ///< Current X
	uint32_t y; ///< Current Y
	uint32_t cols; ///< Viewport Columns (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t rows; ///< Viewport Rows (Characters for WINDOW_MODE_TEXT / Pixels for WINDOW_MODE_GRAPHICS)
	uint32_t format; ///< Color Format (eg COLOR_FORMAT_ARGB32)(Only applicable if CONSOLE_MODE_PIXEL)
	uint32_t forecolor; ///< Current Foreground Color
	uint32_t backcolor; ///< Current Background Color
	uint32_t borderwidth; ///< Current Border Width
	uint32_t bordercolor; ///< Current Border Color
	// Font Properties
	FONT_HANDLE font; ///< Window Font
	uint32_t fontwidth; ///< Font Width (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	uint32_t fontheight; ///< Font Height (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
	// Cursor Properties
	uint32_t cursorx; ///< Cursor X
	uint32_t cursory; ///< Cursor Y
	CURSOR_MODE cursormode; ///< Cursor Mode Insert/Overwrite
	LONGBOOL cursorblink; ///< Cursor Blink On/Off
	CURSOR_STATE cursorstate; ///< Cursor State On/Off
	CURSOR_SHAPE cursorshape; ///< Cursor Shape Line/Bar/Block
	LONGBOOL cursorreverse; ///< Cursor Color Reverse or Inverse (WINDOW_MODE_TEXT only)
	uint32_t cursorforecolor; ///< Cursor Foreground Color (WINDOW_MODE_TEXT only)
	uint32_t cursorbackcolor; ///< Cursor Background Color (WINDOW_MODE_TEXT only)
	// Caret Properties
	uint32_t caretx; ///< Caret X
	uint32_t carety; ///< Caret Y
	HANDLE carethandle; ///< Caret (Cursor) Handle (or INVALID_HANDLE_VALUE)
	// History Properties
	CONSOLE_HISTORY *historyfirst;
	CONSOLE_HISTORY *historylast;
	CONSOLE_HISTORY *historycurrent;
	uint32_t historycount;
	// Driver Properties
	MUTEX_HANDLE lock; ///< Window lock
	CONSOLE_DEVICE *console; ///< Window console
	// Internal Properties
	CONSOLE_WINDOW *prev; ///< Previous entry in Console Window table
	CONSOLE_WINDOW *next; ///< Next entry in Console Window table
};

struct _CONSOLE_HISTORY
{
	// History Properties
	char *value;
	int length;
	// Internal Properties
	CONSOLE_HISTORY *prev; ///< Previous entry in History table
	CONSOLE_HISTORY *next; ///< Next entry in History table
};

/** Console Functions */

/**
 * @brief Open a console device ready for drawing
 * @param Console The console device to open
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_open(CONSOLE_DEVICE *console);

/**
 * @brief Close a console device to prevent drawing
 * @param Console The console device to close
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_close(CONSOLE_DEVICE *console);

/**
 * @brief Clear a console device using the specified color
 * @param Console The console device to clear
 * @param Color The color to use when clearing the console
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_clear(CONSOLE_DEVICE *console, uint32_t color);

/**
 * @brief Scroll all or part of a console device in the specified direction
 * @param Console The console device to scroll
 * @param X1 The left edge of the area to scroll (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y1 The top edge of the area to scroll (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param X2 The right edge of the area to scroll (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y2 The bottom edge of the area to scroll (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Count The number of pixels or characters (depending on console mode) to scroll
 * @param Direction The direction to scroll (eg CONSOLE_DIRECTION_UP)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_scroll(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t count, uint32_t direction);

/**
 * @brief Draw an outline of a box on a console device
 * @param Console The console device to draw on
 * @param X1 The left edge of the box (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y1 The top edge of the box (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param X2 The right edge of the box (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y2 The bottom edge of the box (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @param Width The width of the box outline (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_draw_box(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);

/**
 * @brief Draw a horizontal or vertical line on a console device
 * @param Console The console device to draw on
 * @param X1 The left starting point of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y1 The top starting point of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param X2 The right ending point of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y2 The bottom ending point of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @param Width The width of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_draw_line(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);

/**
 * @brief Draw a line in any direction on a console device
 * @param Console The console device to draw on
 * @param X1 The left starting point of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y1 The top starting point of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param X2 The right ending point of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y2 The bottom ending point of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @param Width The width of the line (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 * @note Character consoles may implement plot line but the default method only supports pixel consoles
 */
uint32_t STDCALL console_device_plot_line(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);

/**
 * @brief Draw a character on a console device
 * @param Console The console device to draw on
 * @param Handle The handle of the font to draw with
 * @param Ch The character to draw
 * @param X The left starting point of the character (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The top starting point of the character (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Forecolor The foreground color for the character (eg COLOR_WHITE)
 * @param Backcolor The background color for the character (eg COLOR_BLACK)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Forecolor and Backcolor must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_draw_char(CONSOLE_DEVICE *console, FONT_HANDLE handle, char ch, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

/**
 * @brief Draw a text string on a console device
 * @param Console The console device to draw on
 * @param Handle The handle of the font to draw with
 * @param Text The text to draw
 * @param X The left starting point of the text (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The top starting point of the text (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Forecolor The foreground color for the text (eg COLOR_WHITE)
 * @param Backcolor The background color for the text (eg COLOR_BLACK)
 * @param Len The length of the text (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Forecolor and Backcolor must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_draw_text(CONSOLE_DEVICE *console, FONT_HANDLE handle, const char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, uint32_t len);

/**
 * @brief Draw a pixel on a console device
 * @param Console The console device to draw on
 * @param X The column to draw the pixel (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The row to draw the pixel (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_draw_pixel(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t color);

/**
 * @brief Draw a filled block on a console device
 * @param Console The console device to draw on
 * @param X1 The left edge of the block (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y1 The top edge of the block (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param X2 The right edge of the block (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y2 The bottom edge of the block (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_draw_block(CONSOLE_DEVICE *console, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);

/**
 * @brief Draw a circle on a console device
 * @param Console The console device to draw on
 * @param X The column center point of the circle (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The row center point of the circle (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @param Width The width of the circle outline (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Radius The radius of the circle (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 * @note Character consoles may implement draw circle but the default method only supports pixel consoles
 */
uint32_t STDCALL console_device_draw_circle(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t color, uint32_t width, uint32_t radius);

/**
 * @brief Draw an image on a console device
 * @param Console The console device to draw on
 * @param X The starting column of the image (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The starting row of the image (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Buffer Pointer to a block of memory containing the pixels of the image in a contiguous block of rows
 * @param Width The number of columns in the image (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Height The number of rows in the image (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Format The color format of the image (eg COLOR_FORMAT_RGB24)
 * @param Skip The number of pixels to skip in the buffer after each row (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_draw_image(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t format, uint32_t skip);

/**
 * @brief Draw a console window on a console device
 * @param Console The console device to draw on
 * @param Handle The handle of the console window to draw
 * @param Flags Flags to specify what should be drawn (eg WINDOW_DRAW_FLAG_BORDER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_draw_window(CONSOLE_DEVICE *console, WINDOW_HANDLE handle, uint32_t flags);

/**
 * @brief Read a pixel from a console device
 * @param Console The console device to read from
 * @param X The column to read the pixel from (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The row to read the pixel from (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Color The color value read from the console (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color is returned in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_get_pixel(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, uint32_t *color);

/**
 * @brief Read an image from a console device
 * @param Console The console device to read from
 * @param X The starting column to read the image from (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The starting row to read the image from (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Buffer Pointer to a block of memory large enough to hold the pixels of the image in a contiguous block of rows
 * @param Width The number of columns to store in the image (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Height The number of rows to store in the image (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Format The color format to store the image in (eg COLOR_FORMAT_RGB24)
 * @param Skip The number of pixels to skip in the buffer after each row (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_get_image(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, void *buffer, uint32_t width, uint32_t height, uint32_t format, uint32_t skip);

/**
 * @brief Output a rectangular area of text to a console device
 * @param Console The console device to output to
 * @param Source The X and Y point in the source buffer to copy text from (Characters)
 * @param Dest The X and Y point on the console device to copy text to (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Buffer A pointer to a buffer of TConsoleChar structures which represent rows of text
 * @param Width The width of the area to be output (Characters)
 * @param Height The height of the area to be output (Characters)
 * @param Skip The number of characters to skip in the buffer after each row (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Source, Width, Height and Skip are based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_device_put_text(CONSOLE_DEVICE *console, FONT_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, CONSOLE_CHAR *buffer, uint32_t width, uint32_t height, uint32_t skip);

/**
 * @brief Copy an image within a console device
 * @param Console The console device to copy on
 * @param Source The starting point for the source of the copy (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Dest The starting point for the destination of the copy (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Width The number of columns in the image (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Height The number of rows in the image (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_copy_image(CONSOLE_DEVICE *console, CONSOLE_POINT *source, CONSOLE_POINT *dest, uint32_t width, uint32_t height);

/**
 * @brief Create a new caret (cursor) of the specified size
 * @param Console The console device to create the caret on
 * @param Width The width of the new caret (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
 * @param Height The height of the new caret (Pixels for CONSOLE_MODE_PIXEL / Always 1 for CONSOLE_MODE_CHARACTER)
 * @param OffsetX The X offset of the new caret (Optional)(Pixels for CONSOLE_MODE_PIXEL / Always 0 for CONSOLE_MODE_CHARACTER)
 * @param OffsetY The Y offset of the new caret (Optional)(Pixels for CONSOLE_MODE_PIXEL / Always 0 for CONSOLE_MODE_CHARACTER)
 * @return Handle to new caret on success or INVALID_HANDLE_VALUE on failure
 */
HANDLE STDCALL console_device_add_caret(CONSOLE_DEVICE *console, uint32_t width, uint32_t height, uint32_t offsetx, uint32_t offsety);

/**
 * @brief Delete an existing caret (cursor)
 * @param Console The console device to delete the caret on
 * @param Handle The handle of the caret to delete (as returned from ConsoleDeviceAddCaret)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_delete_caret(CONSOLE_DEVICE *console, HANDLE handle);

/**
 * @brief Update an existing carets position, visibility or blink
 * @param Console The console device to update the caret on
 * @param Handle The handle of the caret to update (as returned from ConsoleDeviceAddCaret)
 * @param X The X position of the caret (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The Y position of the caret (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Visible If true then show the caret else hide it
 * @param Blink If true then blink the caret at the default blink rate
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_update_caret(CONSOLE_DEVICE *console, HANDLE handle, uint32_t x, uint32_t y, BOOL visible, BOOL blink);

/**
 * @brief Update an existing carets position, colors, visibility, blink or reverse
 * @param Console The console device to update the caret on
 * @param Handle The handle of the caret to update (as returned from ConsoleDeviceAddCaret)
 * @param X The X position of the caret (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y The Y position of the caret (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Forecolor The cursor foreground color if set or COLOR_NONE to disable
 * @param Backcolor The cursor background color if set or COLOR_NONE to disable
 * @param Visible If true then show the caret else hide it
 * @param Blink If true then blink the caret at the default blink rate
 * @param Reverse If true then enable reverse color else enable inverse color
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Forecolor and Backcolor must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_device_update_caret_ex(CONSOLE_DEVICE *console, HANDLE handle, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, BOOL visible, BOOL blink, BOOL reverse);

/**
 * @brief Set the mouse cursor properties of a console device (CONSOLE_MODE_CHARACTER only)
 * @param Console The console device to set the cursor
 * @param Width The width of the cursor in characters
 * @param Height The height of the cursor in characters
 * @param Chars A buffer containing the cursor characters
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For devices that don't support hardware mouse cursor a software cursor will be implemented
 *        If chars is nil then the default cursor will be used
 */
uint32_t STDCALL console_device_set_cursor(CONSOLE_DEVICE *console, uint32_t width, uint32_t height, char *chars);

/**
 * @brief Update the position and state for the mouse cursor of a console device (CONSOLE_MODE_CHARACTER only)
 * @param Console The console device to update the cursor
 * @param Enabled If true then show the cursor else hide it
 * @param X The cursor X location in characters
 * @param Y The cursor Y location in characters
 * @param Relative If true then X and Y are considered relative to the current position
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For devices that don't support hardware mouse cursor a software cursor will be implemented
 */
uint32_t STDCALL console_device_update_cursor(CONSOLE_DEVICE *console, BOOL enabled, int32_t x, int32_t y, BOOL relative);

/**
 * @brief Get the coordinates of a console position from a console device
 * @param Console The console device to get from
 * @param Position The console position to get the coordinates for (eg CONSOLE_POSITION_FULL)
 * @param X1 The left edge of the console position (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y1 The top edge of the console position (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param X2 The right edge of the console position (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @param Y2 The bottom edge of the console position (Pixels for CONSOLE_MODE_PIXEL / Characters for CONSOLE_MODE_CHARACTER)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_get_position(CONSOLE_DEVICE *console, uint32_t position, uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2);

/**
 * @brief Get the current properties from a console device
 * @param Console The console device to get properties from
 * @param Properties Pointer to a TConsoleProperties structure to return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_get_properties(CONSOLE_DEVICE *console, CONSOLE_PROPERTIES *properties);

/**
 * @brief Check if a console device supports a flag value
 * @param Console The console device to check
 * @param Flag The console flag to check (eg CONSOLE_FLAG_FULLSCREEN)
 * @return True if flag is supported, False if not or on error
 */
BOOL STDCALL console_device_check_flag(CONSOLE_DEVICE *console, uint32_t flag);

/**
 * @brief Set or clear a flag on a console device
 * @param Console The console device to set or clear the flag on
 * @param Flag The console flag to set or clear (eg CONSOLE_FLAG_LINE_WRAP)
 * @param Clear If true clear the flag, else set it
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_update_flag(CONSOLE_DEVICE *console, uint32_t flag, BOOL clear);

/**
 * @brief Get the mode of a console device
 * @param Console The console device to get from
 * @return The mode of the console (eg CONSOLE_MODE_PIXEL) or CONSOLE_MODE_NONE on error
 */
uint32_t STDCALL console_device_get_mode(CONSOLE_DEVICE *console);

/**
 * @brief Get the state of a console device
 * @param Console The console device to get from
 * @return The current state of the console (eg CONSOLE_STATE_OPEN)
 */
uint32_t STDCALL console_device_get_state(CONSOLE_DEVICE *console);

/**
 * @brief Create a new Console entry
 * @return Pointer to new Console entry or nil if Console could not be created
 */
CONSOLE_DEVICE * STDCALL console_device_create(void);

/**
 * @brief Create a new Console entry
 * @param Size Size in bytes to allocate for new Console (Including the Console entry)
 * @return Pointer to new Console entry or nil if Console could not be created
 */
CONSOLE_DEVICE * STDCALL console_device_create_ex(uint32_t size);

/**
 * @brief Destroy an existing Console entry
 * @param Console The console device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_destroy(CONSOLE_DEVICE *console);

/**
 * @brief Register a new Console in the Console table
 * @param Console The console device to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_register(CONSOLE_DEVICE *console);

/**
 * @brief Deregister a Console from the Console table
 * @param Console The console device to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_deregister(CONSOLE_DEVICE *console);

/**
 * @brief Find a console device by ID in the console table
 * @param ConsoleId The ID number of the console to find
 * @return Pointer to console device entry or nil if not found
 */
CONSOLE_DEVICE * STDCALL console_device_find(uint32_t consoleid);

/**
 * @brief Find a console device by its related device in the console table
 * @param Device Pointer to the related device to find
 * @return Pointer to console device entry or nil if not found
 */
CONSOLE_DEVICE * STDCALL console_device_find_by_device(DEVICE *device);

/**
 * @brief Find a console device by name in the console table
 * @param Name The name of the console to find (eg Console0)
 * @return Pointer to console device entry or nil if not found
 */
CONSOLE_DEVICE * STDCALL console_device_find_by_name(const char *name);

/**
 * @brief Find a console device by description in the console table
 * @param Description The description of the console to find (eg Framebuffer Console (Framebuffer0))
 * @return Pointer to console device entry or nil if not found
 */
CONSOLE_DEVICE * STDCALL console_device_find_by_description(const char *description);

/**
 * @brief Enumerate all console devices in the console table
 * @param Callback The callback function to call for each console in the table
 * @param Data A private data pointer to pass to callback for each console in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_device_enumerate(console_enumerate_cb callback, void *data);

/**
 * @brief Register a notification for console device changes
 * @param Console The console device to notify changes for (Optional, pass nil for all console devices)
 * @param Callback The function to call when a notification event occurs
 * @param Data A private data pointer to pass to callback when a notification event occurs
 * @param Notification The events to register for notification of (eg DEVICE_NOTIFICATION_REGISTER)
 * @param Flags The flags to control the notification (eg NOTIFIER_FLAG_WORKER)
 */
uint32_t STDCALL console_device_notification(CONSOLE_DEVICE *console, console_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/** Text Console Functions */

/**
 * @brief Create a new Console window
 * @param Console The console device to create the new window on
 * @param Position The console position to create the new window at (eg CONSOLE_POSITION_FULL)
 * @param Default If true allow the new window to be the default window if there is no current default
 * @return Handle to new Console window or INVALID_HANDLE_VALUE if Console window could not be created
 */
WINDOW_HANDLE STDCALL console_window_create(CONSOLE_DEVICE *console, uint32_t position, BOOL _default);

/**
 * @brief Create a new Console window
 * @param Console The console device to create the new window on
 * @param Font The handle of the default font for the new console window
 * @param Size The size in bytes to allocate for the new window entry (Defaults to SizeOf(TConsoleWindow))
 * @param State The state of the new console window (WINDOW_STATE_VISIBLE or WINDOW_STATE_INVISIBLE)
 * @param Mode The mode of the new console window (Normally WINDOW_MODE_TEXT)
 * @param Position The console position to create the new window at (eg CONSOLE_POSITION_FULL)
 * @param Default If true allow the new window to be the default window if there is no current default
 * @return Handle to new Console window or INVALID_HANDLE_VALUE if Console window could not be created
 */
WINDOW_HANDLE STDCALL console_window_create_ex(CONSOLE_DEVICE *console, FONT_HANDLE font, uint32_t size, uint32_t state, uint32_t mode, uint32_t position, BOOL _default);

/**
 * @brief Close and Destroy an existing console window
 * @param Handle The handle of the window to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_destroy(WINDOW_HANDLE handle);

/**
 * @brief Make an existing console window visible and show it on screen
 * @param Handle The handle of the window to show
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_show(WINDOW_HANDLE handle);

/**
 * @brief Make an existing console window invisible and hide it on screen
 * @param Handle The handle of the window to hide
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_hide(WINDOW_HANDLE handle);

/**
 * @brief Make an existing console window the active window
 * @param Handle The handle of the window to activate
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_activate(WINDOW_HANDLE handle);

/**
 * @brief Make an existing console window inactive
 * @param Handle The handle of the window to deactivate
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note On success there will be no active window set
 */
uint32_t STDCALL console_window_deactivate(WINDOW_HANDLE handle);

/**
 * @brief Get the next console window starting with the active window
 * @param Console The console device to change the active window on
 * @param Visible If true only return windows that are visible
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
WINDOW_HANDLE STDCALL console_window_next(CONSOLE_DEVICE *console, BOOL visible);

/**
 * @brief Get the previous console window starting with the active window
 * @param Console The console device to change the active window on
 * @param Visible If true only return windows that are visible
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
WINDOW_HANDLE STDCALL console_window_previous(CONSOLE_DEVICE *console, BOOL visible);

/**
 * @brief Find the console window that X and Y coordinates are within
 * @param Console The console device to find the window on
 * @param X The X coordinate to find the window for
 * @param Y The Y coordinate to find the window for
 * @param Visible If true only return windows that are visible
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, X and Y are based on character columns not screen pixels
 */
WINDOW_HANDLE STDCALL console_window_at(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, BOOL visible);

/**
 * @brief Find an existing console window in the position specified
 * @param Console The console device to find the window on
 * @param Position The window position to find (eg CONSOLE_POSITION_FULL)
 * @return The handle of the existing window or INVALID_HANDLE_VALUE if not found
 */
WINDOW_HANDLE STDCALL console_window_find(CONSOLE_DEVICE *console, uint32_t position);

/**
 * @brief Enumerate existing console windows on the specified console device
 * @param Console The console device to enumerate windows for
 * @param Callback The function to call for each window enumerated
 * @param Data A pointer to private data to be passed to the callback (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_enumerate(CONSOLE_DEVICE *console, console_window_enumerate_cb callback, void *data);

/**
 * @brief Check an existing console window to determine if a flag is set or not
 * @param Handle The handle of the window to check
 * @param Flag The window flag to check for (eg WINDOW_FLAG_LINE_WRAP)
 * @return True if the flag is set, False if not set
 */
BOOL STDCALL console_window_check_flag(WINDOW_HANDLE handle, uint32_t flag);

/**
 * @brief Set or clear a flag on an existing console window
 * @param Handle The handle of the window to set or clear the flag on
 * @param Flag The window flag to set or clear (eg WINDOW_FLAG_LINE_WRAP)
 * @param Clear If true clear the flag, else set it
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_update_flag(WINDOW_HANDLE handle, uint32_t flag, BOOL clear);

/**
 * @brief Get the window mode of an existing console window
 * @param Handle The handle of the window to get the mode for
 * @return The window mode (eg WINDOW_MODE_TEXT)
 */
uint32_t STDCALL console_window_get_mode(WINDOW_HANDLE handle);

/**
 * @brief Get the window state of an existing console window
 * @param Handle The handle of the window to get the state for
 * @return The window state (eg WINDOW_STATE_INVISIBLE)
 */
uint32_t STDCALL console_window_get_state(WINDOW_HANDLE handle);

/**
 * @brief Get the position of an existing console window
 * @param Handle The handle of the window to get the position for
 * @return The window position (eg CONSOLE_POSITION_FULL)
 */
uint32_t STDCALL console_window_get_position(WINDOW_HANDLE handle);

/**
 * @brief Set the position of an existing console window
 * @param Handle The handle of the window to set the position for
 * @param Position The new window position to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The function will return ERROR_INVALID_PARAMETER if another window exists at the position
 */
uint32_t STDCALL console_window_set_position(WINDOW_HANDLE handle, uint32_t position);

/**
 * @brief Get the properties for the specified console window
 * @param Handle The handle of the window to get the properties from
 * @param Properties Pointer to a TWindowProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_get_properties(WINDOW_HANDLE handle, WINDOW_PROPERTIES *properties);

/**
 * @brief Get the current minimum X of the window viewport for an existing console window
 * @param Handle The handle of the window to get MinX for
 * @return The minimum X value for the current window viewport
 * @note For Text Console functions, X is based on character columns not screen pixels
 */
uint32_t STDCALL console_window_get_min_x(WINDOW_HANDLE handle);

/**
 * @brief Get the current minimum Y of the window viewport for an existing console window
 * @param Handle The handle of the window to get MinY for
 * @return The minimum Y value for the current window viewport
 * @note For Text Console functions, Y is based on character rows not screen pixels
 */
uint32_t STDCALL console_window_get_min_y(WINDOW_HANDLE handle);

/**
 * @brief Get the current maximum X of the window viewport for an existing console window
 * @param Handle The handle of the window to get MaxX for
 * @return The maximum X value for the current window viewport
 * @note For Text Console functions, X is based on character columns not screen pixels
 */
uint32_t STDCALL console_window_get_max_x(WINDOW_HANDLE handle);

/**
 * @brief Get the current maximum Y of the window viewport for an existing console window
 * @param Handle The handle of the window to get MaxY for
 * @return The maximum Y value for the current window viewport
 * @note For Text Console functions, Y is based on character rows not screen pixels
 */
uint32_t STDCALL console_window_get_max_y(WINDOW_HANDLE handle);

/**
 * @brief Get the rectangle X1,Y1,X2,Y2 of the window viewport for an existing console window
 * @param Handle The handle of the window to get the rectangle for
 * @return The rectangle of the current window viewport
 * @note For Text Console functions, Rect is based on character rows and columns not screen pixels
 */
CONSOLE_RECT STDCALL console_window_get_rect(WINDOW_HANDLE handle);

/**
 * @brief Set the rectangle X1,Y1,X2,Y2 of the window viewport for an existing console window
 * @param Handle The handle of the window to set the rectangle for
 * @param Rect The rectangle to set for the window viewport
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, Rect is based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_set_rect(WINDOW_HANDLE handle, CONSOLE_RECT *rect);

/**
 * @brief Reset the window viewport for an existing console window to the maximum size
 * @param Handle The handle of the window to reset the viewport for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_reset_rect(WINDOW_HANDLE handle);

/**
 * @brief Get the X1,Y1,X2,Y2 of the window viewport for an existing console window
 * @param Handle The handle of the window to get the viewport for
 * @param X1 The left edge of the current viewport
 * @param Y1 The top edge of the current viewport
 * @param X2 The right edge of the current viewport
 * @param Y2 The bottom edge of the current viewport
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, Viewport is based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_get_viewport(WINDOW_HANDLE handle, uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2);

/**
 * @brief Set the X1,Y1,X2,Y2 of the window viewport for an existing console window
 * @param Handle The handle of the window to get the viewport for
 * @param X1 The left edge of the window viewport
 * @param Y1 The top edge of the window viewport
 * @param X2 The right edge of the window viewport
 * @param Y2 The bottom edge of the window viewport
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, Viewport is based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_set_viewport(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

/**
 * @brief Reset the window viewport for an existing console window to the maximum size
 * @param Handle The handle of the window to reset the viewport for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_reset_viewport(WINDOW_HANDLE handle);

/**
 * @brief Get the current X (Column) position of an existing console window
 * @param Handle The handle of the window to get X for
 * @return The X value for the window
 * @note For Text Console functions, X is based on character columns not screen pixels
 */
uint32_t STDCALL console_window_get_x(WINDOW_HANDLE handle);

/**
 * @brief Set the current X (Column) position of an existing console window
 * @param Handle The handle of the window to set X for
 * @param X The new X value to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, X is based on character columns not screen pixels
 */
uint32_t STDCALL console_window_set_x(WINDOW_HANDLE handle, uint32_t x);

/**
 * @brief Get the current Y (Row) position of an existing console window
 * @param Handle The handle of the window to get Y for
 * @return The Y value for the window
 * @note For Text Console functions, Y is based on character rows not screen pixels
 */
uint32_t STDCALL console_window_get_y(WINDOW_HANDLE handle);

/**
 * @brief Set the current Y (Row) position of an existing console window
 * @param Handle The handle of the window to set Y for
 * @param Y The new Y value to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, Y is based on character rows not screen pixels
 */
uint32_t STDCALL console_window_set_y(WINDOW_HANDLE handle, uint32_t y);

/**
 * @brief Get the current X and Y positions of an existing console window
 * @param Handle The handle of the window to get X and Y for
 * @param X The returned X value
 * @param Y The returned Y value
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, X and Y are based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_get_xy(WINDOW_HANDLE handle, uint32_t *x, uint32_t *y);

/**
 * @brief Set the current X and Y positions of an existing console window
 * @param Handle The handle of the window to set X and Y for
 * @param X The new X value
 * @param Y The new Y value
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, X and Y are based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_set_xy(WINDOW_HANDLE handle, uint32_t x, uint32_t y);

/**
 * @brief Get the point X,Y of an existing console window
 * @param Handle The handle of the window to get the point for
 * @return The current point of the window
 * @note For Text Console functions, Point is based on character rows and columns not screen pixels
 */
CONSOLE_POINT STDCALL console_window_get_point(WINDOW_HANDLE handle);

/**
 * @brief Set the point X,Y of an existing console window
 * @param Handle The handle of the window to set the point for
 * @param Point The new point to set for the window
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, Point is based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_set_point(WINDOW_HANDLE handle, CONSOLE_POINT *point);

/**
 * @brief Get the current columns of the window viewport for an existing console window
 * @param Handle The handle of the window to get columns for
 * @return The columns value for the current window viewport
 * @note For Text Console functions, Columns is based on character columns not screen pixels
 */
uint32_t STDCALL console_window_get_cols(WINDOW_HANDLE handle);

/**
 * @brief Get the current rows of the window viewport for an existing console window
 * @param Handle The handle of the window to get rows for
 * @return The rows value for the current window viewport
 * @note For Text Console functions, Rows is based on character rows not screen pixels
 */
uint32_t STDCALL console_window_get_rows(WINDOW_HANDLE handle);

/**
 * @brief Get the absolute width of an existing console window
 * @param Handle The handle of the window to get the width for
 * @return The absolute width of the window
 * @note For Text Console functions, Width is based on character columns not screen pixels
 */
uint32_t STDCALL console_window_get_width(WINDOW_HANDLE handle);

/**
 * @brief Get the absolute height of an existing console window
 * @param Handle The handle of the window to get the height for
 * @return The absolute height of the window
 * @note For Text Console functions, Height is based on character rows not screen pixels
 */
uint32_t STDCALL console_window_get_height(WINDOW_HANDLE handle);

/**
 * @brief Get the color format of an existing console window
 * @param Handle The handle of the window to get the format for
 * @return The color format of the window (eg COLOR_FORMAT_ARGB32)
 */
uint32_t STDCALL console_window_get_format(WINDOW_HANDLE handle);

/**
 * @brief Get the current foreground color of an existing console window
 * @param Handle The handle of the window to get the foreground color for
 * @return The foreground color of the window (eg COLOR_WHITE)
 */
uint32_t STDCALL console_window_get_forecolor(WINDOW_HANDLE handle);

/**
 * @brief Set the current foreground color of an existing console window
 * @param Handle The handle of the window to set the foreground color for
 * @param Color The foreground color to set (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_set_forecolor(WINDOW_HANDLE handle, uint32_t color);

/**
 * @brief Get the current background color of an existing console window
 * @param Handle The handle of the window to get the background color for
 * @return The background color of the window (eg COLOR_BLACK)
 */
uint32_t STDCALL console_window_get_backcolor(WINDOW_HANDLE handle);

/**
 * @brief Set the current background color of an existing console window
 * @param Handle The handle of the window to set the background color for
 * @param Color The background color to set (eg COLOR_BLACK)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_set_backcolor(WINDOW_HANDLE handle, uint32_t color);

/**
 * @brief Get the default font of an existing console window
 * @param Handle The handle of the window to get the default font for
 * @return The font handle of the default font or INVALID_HANDLE_VALUE on error
 */
FONT_HANDLE STDCALL console_window_get_font(WINDOW_HANDLE handle);

/**
 * @brief Set the default font of an existing console window
 * @param Handle The handle of the window to set the default font for
 * @param Font The font handle of the default font to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console windows, setting the font also clears the window
 */
uint32_t STDCALL console_window_set_font(WINDOW_HANDLE handle, FONT_HANDLE font);

/**
 * @brief Get the current cursor X and Y positions of an existing console window
 * @param Handle The handle of the window to get cursor X and Y for
 * @param X The returned cursor X value
 * @param Y The returned cursor Y value
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, cursor X and Y are based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_get_cursor_xy(WINDOW_HANDLE handle, uint32_t *x, uint32_t *y);

/**
 * @brief Set the current cursor X and Y positions of an existing console window
 * @param Handle The handle of the window to set cursor X and Y for
 * @param X The new cursor X value
 * @param Y The new cursor Y value
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, cursor X and Y are based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_set_cursor_xy(WINDOW_HANDLE handle, uint32_t x, uint32_t y);

/**
 * @brief Get the current cursor mode of an existing console window
 * @param Handle The handle of the window to get the mode for
 * @return The current cursor mode (eg CURSOR_MODE_INSERT)
 */
CURSOR_MODE STDCALL console_window_get_cursor_mode(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor mode of an existing console window
 * @param Handle The handle of the window to set the mode for
 * @param CursorMode The cursor mode to set (eg CURSOR_MODE_INSERT)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_set_cursor_mode(WINDOW_HANDLE handle, CURSOR_MODE cursormode);

/**
 * @brief Get the current cursor blink state of an existing console window
 * @param Handle The handle of the window to get blink state for
 * @return True if blink is enabled, False if not or on error
 */
BOOL STDCALL console_window_get_cursor_blink(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor blink state of an existing console window
 * @param Handle The handle of the window to set the blink state for
 * @param CursorBlink True to enable blink, False to disable
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_set_cursor_blink(WINDOW_HANDLE handle, BOOL cursorblink);

/**
 * @brief Get the current cursor state of an existing console window
 * @param Handle The handle of the window to get the state for
 * @return The current cursor state (eg CURSOR_STATE_ON)
 */
CURSOR_STATE STDCALL console_window_get_cursor_state(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor state of an existing console window
 * @param Handle The handle of the window to set the state for
 * @param CursorState The cursor state to set (eg CURSOR_STATE_ON)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_set_cursor_state(WINDOW_HANDLE handle, CURSOR_STATE cursorstate);

/**
 * @brief Get the current cursor shape of an existing console window
 * @param Handle The handle of the window to get the shape for
 * @return The current cursor shape (eg CURSOR_SHAPE_LINE)
 */
CURSOR_SHAPE STDCALL console_window_get_cursor_shape(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor shape of an existing console window
 * @param Handle The handle of the window to set the shape for
 * @param CursorShape The cursor shape to set (eg CURSOR_SHAPE_LINE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_set_cursor_shape(WINDOW_HANDLE handle, CURSOR_SHAPE cursorshape);

/**
 * @brief Get the current cursor color of an existing console window
 * @param Handle The handle of the window to get cursor color for
 * @return The cursor color of the window (eg COLOR_WHITE)
 * @note Color will be returned in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_window_get_cursor_color(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor color of an existing console window
 * @param Handle The handle of the window to set the cursor color for
 * @param Color The cursor color to set (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_window_set_cursor_color(WINDOW_HANDLE handle, uint32_t color);

/**
 * @brief Get the current cursor reverse state of an existing console window
 * @param Handle The handle of the window to get reverse state for
 * @return True if reverse color is enabled, False if inverse color is enabled
 */
BOOL STDCALL console_window_get_cursor_reverse(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor reverse state of an existing console window
 * @param Handle The handle of the window to set the reverse state for
 * @param CursorReverse True to enable reverse color, False to enable inverse color
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_set_cursor_reverse(WINDOW_HANDLE handle, BOOL cursorreverse);

/**
 * @brief Enable the cursor on an existing console window
 * @param Handle The handle of the window to enable the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_cursor_on(WINDOW_HANDLE handle);

/**
 * @brief Disable the cursor on an existing console window
 * @param Handle The handle of the window to disable the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_cursor_off(WINDOW_HANDLE handle);

/**
 * @brief Change the cursor to a vertical line on an existing console window
 * @param Handle The handle of the window to change the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_cursor_line(WINDOW_HANDLE handle);

/**
 * @brief Change the cursor to a horizontal bar on an existing console window
 * @param Handle The handle of the window to change the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_cursor_bar(WINDOW_HANDLE handle);

/**
 * @brief Change the cursor to a solid block on an existing console window
 * @param Handle The handle of the window to change the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_cursor_block(WINDOW_HANDLE handle);

/**
 * @brief Move the cursor on an existing console window
 * @param Handle The handle of the window to move the cursor for
 * @param X The column to move the cursor to
 * @param Y The row to move the cursor to
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, X and Y are based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_cursor_move(WINDOW_HANDLE handle, uint32_t x, uint32_t y);

/**
 * @brief Set the blink state of the cursor on an existing console window
 * @param Handle The handle of the window to set the blink state for
 * @param Enabled True if the cursor is blinking, False if not
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_cursor_blink(WINDOW_HANDLE handle, BOOL enabled);

/**
 * @brief Set the color of the cursor on an existing console window
 * @param Handle The handle of the window to set the color for
 * @param Color The cursor color to set (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Color must be specified in the default color format (See COLOR_FORMAT_DEFAULT)
 */
uint32_t STDCALL console_window_cursor_color(WINDOW_HANDLE handle, uint32_t color);

/**
 * @brief Set the reverse state of the cursor on an existing console window
 * @param Handle The handle of the window to set the reverse state for
 * @param Enabled True if the cursor shows in reverse colors, False if it shows in inverse colors
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_cursor_reverse(WINDOW_HANDLE handle, BOOL enabled);

/**
 * @brief Add a value to the command history table of an existing console window
 * @param Handle The handle of the window to add to
 * @param Value The text to add to the command history
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note When the number of entries in the table reaches the maximum the first entry will be removed
 */
uint32_t STDCALL console_window_add_history(WINDOW_HANDLE handle, const char *value);

/**
 * @brief Remove all entries from the command history table of an existing console window
 * @param Handle The handle of the window to clear
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_clear_history(WINDOW_HANDLE handle);

/**
 * @brief Get the first (oldest) command history value from an existing console window
 * @param Handle The handle of the window to get from
 * @return The command history value or an empty string on failure
 */
uint32_t STDCALL console_window_first_history(WINDOW_HANDLE handle, char *value, uint32_t len);

/**
 * @brief Get the last (most recent) command history value from an existing console window
 * @param Handle The handle of the window to get from
 * @return The command history value or an empty string on failure
 */
uint32_t STDCALL console_window_last_history(WINDOW_HANDLE handle, char *value, uint32_t len);

/**
 * @brief Get the next (after current) command history value from an existing console window
 * @param Handle The handle of the window to get from
 * @return The command history value or an empty string on failure
 */
uint32_t STDCALL console_window_next_history(WINDOW_HANDLE handle, char *value, uint32_t len);

/**
 * @brief Get the next (before current) command history value from an existing console window
 * @param Handle The handle of the window to get from
 * @return The command history value or an empty string on failure
 * @note If there is no current history value the last value is returned
 */
uint32_t STDCALL console_window_previous_history(WINDOW_HANDLE handle, char *value, uint32_t len);

/**
 * @brief Get the current command history value from an existing console window
 * @param Handle The handle of the window to get from
 * @return The command history value or an empty string on failure
 * @note If there is no current history value the last value is returned
 */
uint32_t STDCALL console_window_current_history(WINDOW_HANDLE handle, char *value, uint32_t len);

/**
 * @brief Scroll the current viewport of an existing console window up
 * @param Handle The handle of the window to scroll
 * @param Row The starting row (Y) for the scroll up, all rows from top plus Lines down to Row will be scrolled up
 * @param Lines The number of character lines to scroll up, Lines number of rows at the top will be discarded
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The starting Row will be blanked with the background color
 */
uint32_t STDCALL console_window_scroll_up(WINDOW_HANDLE handle, uint32_t row, uint32_t lines);

/**
 * @brief Scroll the current viewport of an existing console window down
 * @param Handle The handle of the window to scroll
 * @param Row The starting row (Y) for the scroll down, all rows from bottom minus Lines up to Row will be scrolled down
 * @param Lines The number of character lines to scroll down, Lines number of rows at the bottom will be discarded
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The starting Row will be blanked with the background color
 */
uint32_t STDCALL console_window_scroll_down(WINDOW_HANDLE handle, uint32_t row, uint32_t lines);

/**
 * @brief Scroll the current viewport of an existing console window left
 * @param Handle The handle of the window to scroll
 * @param Row The starting row (Y) for the scroll left, all rows from Row down to Row + Lines will be scrolled left
 * @param Lines The number of rows to scroll left, all rows from Row down to Row + Lines will be scrolled left
 * @param Col The starting column (X) for the scroll left, all cols from left plus Chars to Col with be scrolled left
 * @param Chars The number of characters to scroll left, Chars number of columns at the left will be discarded
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The starting Col will be blanked with the background color
 */
uint32_t STDCALL console_window_scroll_left(WINDOW_HANDLE handle, uint32_t row, uint32_t col, uint32_t lines, uint32_t chars);

/**
 * @brief Scroll the current viewport of an existing console window right
 * @param Handle The handle of the window to scroll
 * @param Row The starting row (Y) for the scroll right, all rows from Row down to Row + Lines will be scrolled right
 * @param Lines The number of rows to scroll right, all rows from Row down to Row + Lines will be scrolled right
 * @param Col The starting column (X) for the scroll right, all rows from right minus Chars to Col will be scrolled right
 * @param Chars The number of characters to scroll right, Chars number of columns at the right will be discarded
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The starting Col will be blanked with the background color
 */
uint32_t STDCALL console_window_scroll_right(WINDOW_HANDLE handle, uint32_t row, uint32_t col, uint32_t lines, uint32_t chars);

/**
 * @brief Clear the current viewport of an existing console window
 * @param Handle The handle of the window to clear
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_clear(WINDOW_HANDLE handle);

/**
 * @brief Clear part of the the current viewport of an existing console window
 * @param Handle The handle of the window to clear
 * @param X1 The left edge of the area to clear (relative to current viewport)
 * @param Y1 The top edge of the area to clear (relative to current viewport)
 * @param X2 The right edge of the area to clear (relative to current viewport)
 * @param Y2 The bottom edge of the area to clear (relative to current viewport)
 * @param Cursor If True update the cursor position after clearing
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, Window is based on screen character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_clear_ex(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, BOOL cursor);

/**
 * @brief Write text on an existing console window at the current position in the current color
 * @param Handle The handle of the window to write text on
 * @param Text The text to write
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The window will not scroll up at the end of the line
 */
uint32_t STDCALL console_window_write(WINDOW_HANDLE handle, const char *text);

/**
 * @brief Write text on an existing console window
 * @param Handle The handle of the window to write text on
 * @param Text The text to write
 * @param X The column to start writing the text at
 * @param Y The row to start writing the text at
 * @param Forecolor The foreground color to use (eg COLOR_WHITE)
 * @param Backcolor The background color to use (eg COLOR_BLACK)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, X and Y are based on screen character rows and columns not screen pixels
 * @note The window will not scroll up at the end of the line
 */
uint32_t STDCALL console_window_write_ex(WINDOW_HANDLE handle, const char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

/**
 * @brief Write text on an existing console window at the current position in the current color
 * @param Handle The handle of the window to write text on
 * @param Text The text to write
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The window will scroll up at the end of the line
 */
uint32_t STDCALL console_window_write_ln(WINDOW_HANDLE handle, const char *text);

/**
 * @brief Write text on an existing console window
 * @param Handle The handle of the window to write text on
 * @param Text The text to write
 * @param X The column to start writing the text at
 * @param Y The row to start writing the text at
 * @param Forecolor The foreground color to use (eg COLOR_WHITE)
 * @param Backcolor The background color to use (eg COLOR_BLACK)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, X and Y are based on character rows and columns not screen pixels
 * @note The window will scroll up at the end of the line
 */
uint32_t STDCALL console_window_write_ln_ex(WINDOW_HANDLE handle, const char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

/**
 * @brief Write a character on an existing console window at the current position in the current color
 * @param Handle The handle of the window to write the character on
 * @param Chr The character to write
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_write_chr(WINDOW_HANDLE handle, char ch);

/**
 * @brief Write a character on an existing console window
 * @param Handle The handle of the window to write the character on
 * @param Chr The character to write
 * @param X The column to start writing the character at
 * @param Y The row to start writing the character at
 * @param Forecolor The foreground color to use (eg COLOR_WHITE)
 * @param Backcolor The background color to use (eg COLOR_BLACK)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, X and Y are based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_write_chr_ex(WINDOW_HANDLE handle, char ch, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

/**
 * @brief Output a rectangular area of text to a console window
 * @param Handle The console window to output to
 * @param Source The X and Y point in the source buffer to copy text from (Characters)
 * @param Dest The X and Y point on the console window to copy text to (Characters)
 * @param Buffer A pointer to a buffer of TConsoleChar structures which represent rows of text
 * @param Width The width of the area to be output (Characters)
 * @param Height The height of the area to be output (Characters)
 * @param Skip The number of characters to skip in the buffer after each row (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Text Console functions, Source, Dest, Width, Height and Skip are based on character rows and columns not screen pixels
 */
uint32_t STDCALL console_window_output(WINDOW_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, CONSOLE_CHAR *buffer, uint32_t width, uint32_t height, uint32_t skip);

/**
 * @brief Read text input from the console and echo to an existing console window at the current position in the current color
 * @param Handle The handle of the window to echo input to
 * @param Text The text read from the console on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The console window will not scroll up on return
 */
uint32_t STDCALL console_window_read(WINDOW_HANDLE handle, char *text, uint32_t *len);

/**
 * @brief Read text input from the console and echo to an existing console window at the current position in the current color
 * @param Handle The handle of the window to echo input to
 * @param Text The text read from the console on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The console window will scroll up one line on return
 */
uint32_t STDCALL console_window_read_ln(WINDOW_HANDLE handle, char *text, uint32_t *len);

/**
 * @brief Read text input from the console and echo to an existing console window at the specified position in the specified color
 * @param Handle The handle of the window to echo input to
 * @param Text The text read from the console on return
 * @param Prompt An optional text prompt to display at the start of the line
 * @param X The starting X position for the output (0 for current position)
 * @param Y The starting Y position for the output (0 for current position)
 * @param Forecolor The text forecolor for the output (COLOR_NONE for current color)
 * @param Backcolor The text backcolor for the output (COLOR_NONE for current color)
 * @param Scroll If true then scroll up one line on return
 * @param History If true then support console history buffer using Up, Down and F3 keys
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Supports common line editing behaviour including Home, End, Left, Right, Up, Down, Insert, Backspace and Delete
 */
uint32_t STDCALL console_window_read_ln_ex(WINDOW_HANDLE handle, char *text, uint32_t *len, char *prompt, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, BOOL scroll, BOOL history, console_window_completion_cb completion, void *data);

/**
 * @brief Read one character input from the console and echo to an existing console window at the current position in the current color
 * @param Handle The handle of the window to echo input to
 * @param Chr The character read from the console on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The console window will not scroll up on return
 */
uint32_t STDCALL console_window_read_chr(WINDOW_HANDLE handle, char *ch);

/**
 * @brief Read one character input from the console and optionally echo to an existing console window at the specified position in the specified color
 * @param Handle The handle of the window to echo input to
 * @param Chr The character read from the console on return
 * @param Prompt An optional text prompt to display at the start of the line
 * @param X The starting X position for the output (0 for current position)
 * @param Y The starting Y position for the output (0 for current position)
 * @param Forecolor The text forecolor for the output (COLOR_NONE for current color)
 * @param Backcolor The text backcolor for the output (COLOR_NONE for current color)
 * @param Echo If true then echo the character to the console window
 * @param Scroll If true then scroll up one line on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_read_chr_ex(WINDOW_HANDLE handle, char *ch, char *prompt, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor, BOOL echo, BOOL scroll);

/**
 * @brief Print formatted text to an existing console window at the current position in the current color
 * @param Handle The handle of the window to print to
 * @param Format The formatted text to print (As per printf in standard C library)
 * @return On success the total number of characters output to the console, on error a negative value is returned and errno is set to the error code
 */
int STDCALL console_window_printf(WINDOW_HANDLE handle, const char *format, ...) _ATTRIBUTE ((__format__ (__printf__, 2, 3)));

/** CRT Console Functions */

/**
 * @brief Compatible with RTL Crt unit function ClrEol
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/clreol.html
 */
void STDCALL console_clr_eol(void);

/**
 * @brief Compatible with RTL Crt unit function ClrScr
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/clrscr.html
 */
void STDCALL console_clr_scr(void);

/**
 * @brief Compatible with RTL Crt unit function Delay
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/delay.html
 */
void STDCALL console_delay(uint16_t ms);

/**
 * @brief Compatible with RTL Crt unit function DelLine
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/delline.html
 */
void STDCALL console_del_line(void);

/**
 * @brief Compatible with RTL Crt unit function GotoXY
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/gotoxy.html
 * @note For CRT Console functions, X and Y are based on character rows and columns not screen pixels
 */
void STDCALL console_goto_xy(int x, int y);

/**
 * @brief Compatible with RTL Crt unit function HighVideo
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/highvideo.html
 */
void STDCALL console_high_video(void);

/**
 * @brief Compatible with RTL Crt unit function InsLine
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/insline.html
 */
void STDCALL console_ins_line(void);

/**
 * @brief Compatible with RTL Crt unit function KeyPressed
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/keypressed.html
 */
BOOL STDCALL console_keypressed(void);

/**
 * @brief Compatible with RTL Crt unit function LowVideo
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/lowvideo.html
 */
void STDCALL console_low_video(void);

/**
 * @brief Compatible with RTL Crt unit function NormVideo
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/normvideo.html
 */
void STDCALL console_norm_video(void);

/**
 * @brief Compatible with RTL Crt unit function NoSound
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/nosound.html
 */
void STDCALL console_no_sound(void);

/**
 * @brief Compatible with RTL Crt unit function ReadKey
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/readkey.html
 * @note For extended key scan codes see: http://www.freepascal.org/docs-html/rtl/keyboard/kbdscancode.html
 */
char STDCALL console_read_key(void);

/**
 * @brief Compatible with RTL Crt unit function Sound
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/sound.html
 */
void STDCALL console_sound(uint16_t hz);

/**
 * @brief Compatible with RTL Crt unit function TextBackground
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/textbackground.html
 */
void STDCALL console_text_background(uint32_t color);

/**
 * @brief Compatible with RTL Crt unit function TextColor
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/textcolor.html
 */
void STDCALL console_text_color(uint32_t color);

/**
 * @brief Compatible with RTL Crt unit function TextMode
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/textmode.html
 */
void STDCALL console_text_mode(int mode);

/**
 * @brief Compatible with RTL Crt unit function WhereX
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/wherex.html
 * @note For CRT Console functions, X is based on character columns not screen pixels
 */
int STDCALL console_where_x(void);

/**
 * @brief Compatible with RTL Crt unit function WhereY
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/wherey.html
 * @note For CRT Console functions, Y is based on character row not screen pixels
 */
int STDCALL console_where_y(void);

/**
 * @brief Compatible with RTL Crt unit function Window
 * @see http://www.freepascal.org/docs-html-3.0.0/rtl/crt/window.html
 * @note For CRT Console functions, X1, Y1, X2 and Y2 are based on character rows and columns not screen pixels
 */
void STDCALL console_window(int x1, int y1, int x2, int y2);

/**
 * @brief Scroll the default console window up
 * @param Row The starting row (Y) for the scroll up, all rows from top plus Lines down to Row will be scrolled up
 * @param Lines The number of character lines to scroll up, Lines number of rows at the top will be discarded
 * @note For CRT Console functions, Row and Lines are based on character rows and columns not screen pixels
 */
void STDCALL console_scroll_up(int row, int lines);

/**
 * @brief Scroll the default console window down
 * @param Row The starting row (Y) for the scroll down, all rows from bottom minus Lines up to Row will be scrolled down
 * @param Lines The number of character lines to scroll down, Lines number of rows at the bottom will be discarded
 * @note For CRT Console functions, Row and Lines are based on character rows and columns not screen pixels
 */
void STDCALL console_scroll_down(int row, int lines);

/**
 * @brief Write text on the default console window at the current position in the current color
 * @param Text The text to write
 * @note The window will not scroll up at the end of the line
 */
void STDCALL console_write(const char *text);

/**
 * @brief Write text on the default console window at the current position in the current color
 * @param Text The text to write
 * @note The window will scroll up at the end of the line
 */
void STDCALL console_write_ln(const char *text);

/**
 * @brief Write a character on the default console window at the current position in the current color
 * @param Chr The character to write
 */
void STDCALL console_write_chr(char ch);

/**
 * @brief Read text from console input and echo to the screen
 * @param Text The text read from the console input
 */
void STDCALL console_read(char *text, uint32_t *len);

/**
 * @brief Read text from console input and echo to the screen
 * @param Text The text read from the console input
 */
void STDCALL console_read_ln(char *text, uint32_t *len);

/**
 * @brief Read a character from console input and echo to the screen
 * @param Chr The character read from the console input
 */
void STDCALL console_read_chr(char *ch);

/**
 * @brief Print formatted text to the default console window at the current position in the current color
 * @param Format The formatted text to print (As per printf in standard C library)
 * @return On success the total number of characters output to the console, on error a negative value is returned and errno is set to the error code
 */
int STDCALL console_printf(const char *format, ...) _ATTRIBUTE ((__format__ (__printf__, 1, 2)));

/** Console Helper Functions */

/**
 * @brief Get the current console device count
 */
uint32_t STDCALL console_device_get_count(void);

/**
 * @brief Get the current default console device
 */
CONSOLE_DEVICE * STDCALL console_device_get_default(void);

/**
 * @brief Set the current default console device
 */
uint32_t STDCALL console_device_set_default(CONSOLE_DEVICE *console);

/**
 * @brief Check if the supplied Console device is in the Console table
 */
CONSOLE_DEVICE * STDCALL console_device_check(CONSOLE_DEVICE *console);

/**
 * @brief Check if a console caret entry is valid
 * @param Console The console device to search for the caret
 * @param Caret The caret entry to check for validity
 * @return The supplied caret if successful or nil on failure
 */
CONSOLE_CARET * STDCALL console_device_caret_check(CONSOLE_DEVICE *console, CONSOLE_CARET *caret);

/**
 * @brief Convert a Console type value to a string
 */
uint32_t STDCALL console_type_to_string(uint32_t consoletype, char *value, uint32_t len);

/**
 * @brief Convert a Console state value to a string
 */
uint32_t STDCALL console_state_to_string(uint32_t consolestate, char *value, uint32_t len);

/**
 * @brief Get the default console font
 */
FONT_HANDLE STDCALL console_device_get_default_font(void);
uint32_t STDCALL console_position_to_string(uint32_t position, char *value, uint32_t len);

/** Text Console Helper Functions */

/**
 * @brief Get the current console window count
 * @param Console The console device to get the window count for
 * @return The current number of console windows on the specified console device
 */
uint32_t STDCALL console_window_get_count(CONSOLE_DEVICE *console);

/**
 * @brief Get the current console active window
 * @param Console The console device to get the active window for
 * @return The window handle of the current active window or INVALID_HANDLE_VALUE on failure
 */
WINDOW_HANDLE STDCALL console_window_get_active(CONSOLE_DEVICE *console);

/**
 * @brief Get the current console default window
 * @param Console The console device to get the default window for
 * @return The window handle of the current default window or INVALID_HANDLE_VALUE on failure
 */
WINDOW_HANDLE STDCALL console_window_get_default(CONSOLE_DEVICE *console);

/**
 * @brief Set the current console default window
 * @param Console The console device to set the default window for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL console_window_set_default(CONSOLE_DEVICE *console, WINDOW_HANDLE handle);

/**
 * @brief Check if a console window entry is valid
 * @param Console The console device to search for the window
 * @param Window The window entry to check for validity
 * @return The supplied window if successful or nil on failure
 */
CONSOLE_WINDOW * STDCALL console_window_check(CONSOLE_DEVICE *console, CONSOLE_WINDOW *window);

/**
 * @brief Convert a Console Window state value to a string
 */
uint32_t STDCALL console_window_state_to_string(uint32_t windowstate, char *value, uint32_t len);

/**
 * @brief Convert a Console Window mode value to a string
 */
uint32_t STDCALL console_window_mode_to_string(uint32_t windowmode, char *value, uint32_t len);

/**
 * @brief Get the default console window font
 */
FONT_HANDLE STDCALL console_window_get_default_font(void);

/**
 * @brief Redirect standard output to the console window specified by Handle
 * @param Handle The window handle to redirect output to (or INVALID_HANDLE_VALUE to stop redirection)
 * @return True if completed successfully or False if an error occurred
 * @note Redirects the output of the text files Output, ErrOutput, StdOut and StdErr
 *        which also redirects the output of Write, WriteLn and the standard C library
 */
BOOL STDCALL console_window_redirect_output(WINDOW_HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_CONSOLE_H