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
#ifndef _ULTIBO_GRAPHICSCONSOLE_H
#define _ULTIBO_GRAPHICSCONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/console.h"

/** Graphics Console specific constants */

/** Graphics Console specific types */
/** Graphics Window Enumeration Callback */
typedef console_window_enumerate_cb graphics_window_enumerate_cb;

/** Graphics Window */
typedef CONSOLE_WINDOW GRAPHICS_WINDOW;

/** Graphics Console Functions */

/**
 * @brief Create a new Graphics window
 * @param Console The console device to create the new window on
 * @param Position The console position to create the new window at (eg CONSOLE_POSITION_FULL)
 * @return Handle to new Graphics window or INVALID_HANDLE_VALUE if the window could not be created
 */
WINDOW_HANDLE STDCALL graphics_window_create(CONSOLE_DEVICE *console, uint32_t position);

/**
 * @brief Create a new Graphics window
 * @param Console The console device to create the new window on
 * @param Font The handle of the default font for the new console window
 * @param Size The size in bytes to allocate for the new window entry (Defaults to SizeOf(TGraphicsWindow))
 * @param State The state of the new console window (WINDOW_STATE_VISIBLE or WINDOW_STATE_INVISIBLE)
 * @param Mode The mode of the new console window (Normally WINDOW_MODE_GRAPHICS)
 * @param Position The console position to create the new window at (eg CONSOLE_POSITION_FULL)
 * @return Handle to new Graphics window or INVALID_HANDLE_VALUE if the window could not be created
 */
WINDOW_HANDLE STDCALL graphics_window_create_ex(CONSOLE_DEVICE *console, FONT_HANDLE font, uint32_t size, uint32_t state, uint32_t mode, uint32_t position);

/**
 * @brief Close and Destroy an existing console window
 * @param Handle The handle of the window to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_destroy(WINDOW_HANDLE handle);

/**
 * @brief Make an existing console window visible and show it on screen
 * @param Handle The handle of the window to show
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_show(WINDOW_HANDLE handle);

/**
 * @brief Make an existing console window invisible and hide it on screen
 * @param Handle The handle of the window to hide
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_hide(WINDOW_HANDLE handle);

/**
 * @brief Make an existing console window the active window
 * @param Handle The handle of the window to activate
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_activate(WINDOW_HANDLE handle);

/**
 * @brief Make an existing console window inactive
 * @param Handle The handle of the window to deactivate
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note On success there will be no active window set
 */
uint32_t STDCALL graphics_window_deactivate(WINDOW_HANDLE handle);

/**
 * @brief Get the next console window starting with the active window
 * @param Console The console device to change the active window on
 * @param Visible If true only return windows that are visible
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
WINDOW_HANDLE STDCALL graphics_window_next(CONSOLE_DEVICE *console, BOOL visible);

/**
 * @brief Get the previous console window starting with the active window
 * @param Console The console device to change the active window on
 * @param Visible If true only return windows that are visible
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
WINDOW_HANDLE STDCALL graphics_window_previous(CONSOLE_DEVICE *console, BOOL visible);

/**
 * @brief Find the console window that X and Y coordinates are within
 * @param Console The console device to find the window on
 * @param X The X coordinate to find the window for
 * @param Y The Y coordinate to find the window for
 * @param Visible If true only return windows that are visible
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, X and Y are based on screen pixels not characters
 */
WINDOW_HANDLE STDCALL graphics_window_at(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, BOOL visible);

/**
 * @brief Find an existing console window in the position specified
 * @param Console The console device to find the window on
 * @param Position The window position to find (eg CONSOLE_POSITION_FULL)
 * @return The handle of the existing window or INVALID_HANDLE_VALUE if not found
 */
WINDOW_HANDLE STDCALL graphics_window_find(CONSOLE_DEVICE *console, uint32_t position);

/**
 * @brief Enumerate existing console windows on the specified console device
 * @param Console The console device to enumerate windows for
 * @param Callback The function to call for each window enumerated
 * @param Data A pointer to private data to be passed to the callback (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_enumerate(CONSOLE_DEVICE *console, graphics_window_enumerate_cb callback, void *data);

/**
 * @brief Check an existing console window to determine if a flag is set or not
 * @param Handle The handle of the window to check
 * @param Flag The window flag to check for (eg WINDOW_FLAG_LINE_WRAP)
 * @return True if the flag is set, False if not set
 */
BOOL STDCALL graphics_window_check_flag(WINDOW_HANDLE handle, uint32_t flag);

/**
 * @brief Set or clear a flag on an existing console window
 * @param Handle The handle of the window to set or clear the flag on
 * @param Flag The window flag to set or clear (eg WINDOW_FLAG_LINE_WRAP)
 * @param Clear If true clear the flag, else set it
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_update_flag(WINDOW_HANDLE handle, uint32_t flag, BOOL clear);

/**
 * @brief Get the window mode of an existing console window
 * @param Handle The handle of the window to get the mode for
 * @return The window mode (eg WINDOW_MODE_GRAPHICS)
 */
uint32_t STDCALL graphics_window_get_mode(WINDOW_HANDLE handle);

/**
 * @brief Get the window state of an existing console window
 * @param Handle The handle of the window to get the state for
 * @return The window state (eg WINDOW_STATE_INVISIBLE)
 */
uint32_t STDCALL graphics_window_get_state(WINDOW_HANDLE handle);

/**
 * @brief Get the position of an existing console window
 * @param Handle The handle of the window to get the position for
 * @return The window position (eg CONSOLE_POSITION_FULL)
 */
uint32_t STDCALL graphics_window_get_position(WINDOW_HANDLE handle);

/**
 * @brief Set the position of an existing console window
 * @param Handle The handle of the window to set the position for
 * @param Position The new window position to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The function will return ERROR_INVALID_PARAMETER if another window exists at the position
 */
uint32_t STDCALL graphics_window_set_position(WINDOW_HANDLE handle, uint32_t position);

/**
 * @brief Get the properties for the specified console window
 * @param Handle The handle of the window to get the properties from
 * @param Properties Pointer to a TWindowProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_get_properties(WINDOW_HANDLE handle, WINDOW_PROPERTIES *properties);

/**
 * @brief Get the current minimum X of the window viewport for an existing console window
 * @param Handle The handle of the window to get MinX for
 * @return The minimum X value for the current window viewport
 * @note For Graphics Console functions, X is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_min_x(WINDOW_HANDLE handle);

/**
 * @brief Get the current minimum Y of the window viewport for an existing console window
 * @param Handle The handle of the window to get MinY for
 * @return The minimum Y value for the current window viewport
 * @note For Graphics Console functions, Y is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_min_y(WINDOW_HANDLE handle);

/**
 * @brief Get the current maximum X of the window viewport for an existing console window
 * @param Handle The handle of the window to get MaxX for
 * @return The maximum X value for the current window viewport
 * @note For Graphics Console functions, X is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_max_x(WINDOW_HANDLE handle);

/**
 * @brief Get the current maximum Y of the window viewport for an existing console window
 * @param Handle The handle of the window to get MaxY for
 * @return The maximum Y value for the current window viewport
 * @note For Graphics Console functions, Y is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_max_y(WINDOW_HANDLE handle);

/**
 * @brief Get the rectangle X1,Y1,X2,Y2 of the window viewport for an existing console window
 * @param Handle The handle of the window to get the rectangle for
 * @return The rectangle of the current window viewport
 * @note For Graphics Console functions, Rect is based on screen pixels not characters
 */
CONSOLE_RECT STDCALL graphics_window_get_rect(WINDOW_HANDLE handle);

/**
 * @brief Set the rectangle X1,Y1,X2,Y2 of the window viewport for an existing console window
 * @param Handle The handle of the window to set the rectangle for
 * @param Rect The rectangle to set for the window viewport
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Rect is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_set_rect(WINDOW_HANDLE handle, CONSOLE_RECT *rect);

/**
 * @brief Reset the window viewport for an existing console window to the maximum size
 * @param Handle The handle of the window to reset the viewport for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_reset_rect(WINDOW_HANDLE handle);

/**
 * @brief Get the X1,Y1,X2,Y2 of the window viewport for an existing console window
 * @param Handle The handle of the window to get the viewport for
 * @param X1 The left edge of the current viewport
 * @param Y1 The top edge of the current viewport
 * @param X2 The right edge of the current viewport
 * @param Y2 The bottom edge of the current viewport
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_viewport(WINDOW_HANDLE handle, uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2);

/**
 * @brief Set the X1,Y1,X2,Y2 of the window viewport for an existing console window
 * @param Handle The handle of the window to get the viewport for
 * @param X1 The left edge of the window viewport
 * @param Y1 The top edge of the window viewport
 * @param X2 The right edge of the window viewport
 * @param Y2 The bottom edge of the window viewport
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_set_viewport(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

/**
 * @brief Reset the window viewport for an existing console window to the maximum size
 * @param Handle The handle of the window to reset the viewport for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_reset_viewport(WINDOW_HANDLE handle);

/**
 * @brief Get the current columns of the window viewport for an existing console window
 * @param Handle The handle of the window to get columns for
 * @return The columns value for the current window viewport
 * @note For Graphics Console functions, Columns is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_cols(WINDOW_HANDLE handle);

/**
 * @brief Get the current rows of the window viewport for an existing console window
 * @param Handle The handle of the window to get rows for
 * @return The rows value for the current window viewport
 * @note For Graphics Console functions, Rows is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_rows(WINDOW_HANDLE handle);

/**
 * @brief Get the absolute width of an existing console window
 * @param Handle The handle of the window to get the width for
 * @return The absolute width of the window
 * @note For Graphics Console functions, Width is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_width(WINDOW_HANDLE handle);

/**
 * @brief Get the absolute height of an existing console window
 * @param Handle The handle of the window to get the height for
 * @return The absolute height of the window
 * @note For Graphics Console functions, Height is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_height(WINDOW_HANDLE handle);

/**
 * @brief Get the color format of an existing console window
 * @param Handle The handle of the window to get the format for
 * @return The color format of the window (eg COLOR_FORMAT_ARGB32)
 */
uint32_t STDCALL graphics_window_get_format(WINDOW_HANDLE handle);

/**
 * @brief Get the current foreground color of an existing console window
 * @param Handle The handle of the window to get the foreground color for
 * @return The foreground color of the window (eg COLOR_WHITE)
 */
uint32_t STDCALL graphics_window_get_forecolor(WINDOW_HANDLE handle);

/**
 * @brief Set the current foreground color of an existing console window
 * @param Handle The handle of the window to set the foreground color for
 * @param Color The foreground color to set (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_set_forecolor(WINDOW_HANDLE handle, uint32_t color);

/**
 * @brief Get the current background color of an existing console window
 * @param Handle The handle of the window to get the background color for
 * @return The background color of the window (eg COLOR_BLACK)
 */
uint32_t STDCALL graphics_window_get_backcolor(WINDOW_HANDLE handle);

/**
 * @brief Set the current background color of an existing console window
 * @param Handle The handle of the window to set the background color for
 * @param Color The background color to set (eg COLOR_BLACK)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_set_backcolor(WINDOW_HANDLE handle, uint32_t color);

/**
 * @brief Get the default font of an existing console window
 * @param Handle The handle of the window to get the default font for
 * @return The font handle of the default font or INVALID_HANDLE_VALUE on error
 */
FONT_HANDLE STDCALL graphics_window_get_font(WINDOW_HANDLE handle);

/**
 * @brief Set the default font of an existing console window
 * @param Handle The handle of the window to set the default font for
 * @param Font The font handle of the default font to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_set_font(WINDOW_HANDLE handle, FONT_HANDLE font);

/**
 * @brief Get the current cursor X and Y positions of an existing console window
 * @param Handle The handle of the window to get cursor X and Y for
 * @param X The returned cursor X value
 * @param Y The returned cursor Y value
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, cursor X and Y are based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_cursor_xy(WINDOW_HANDLE handle, uint32_t *x, uint32_t *y);

/**
 * @brief Set the current cursor X and Y positions of an existing console window
 * @param Handle The handle of the window to set cursor X and Y for
 * @param X The new cursor X value
 * @param Y The new cursor Y value
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, cursor X and Y are based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_set_cursor_xy(WINDOW_HANDLE handle, uint32_t x, uint32_t y);

/**
 * @brief Get the current cursor mode of an existing console window
 * @param Handle The handle of the window to get the mode for
 * @return The current cursor mode (eg CURSOR_MODE_INSERT)
 */
CURSOR_MODE STDCALL graphics_window_get_cursor_mode(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor mode of an existing console window
 * @param Handle The handle of the window to set the mode for
 * @param CursorMode The cursor mode to set (eg CURSOR_MODE_INSERT)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_set_cursor_mode(WINDOW_HANDLE handle, CURSOR_MODE cursormode);

/**
 * @brief Get the current cursor blink state of an existing console window
 * @param Handle The handle of the window to get blink state for
 * @return True if blink is enabled, False if not or on error
 */
BOOL STDCALL graphics_window_get_cursor_blink(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor blink state of an existing console window
 * @param Handle The handle of the window to set the blink state for
 * @param CursorBlink True to enable blink, False to disable
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_set_cursor_blink(WINDOW_HANDLE handle, BOOL cursorblink);

/**
 * @brief Get the current cursor state of an existing console window
 * @param Handle The handle of the window to get the state for
 * @return The current cursor state (eg CURSOR_STATE_ON)
 */
CURSOR_STATE STDCALL graphics_window_get_cursor_state(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor state of an existing console window
 * @param Handle The handle of the window to set the state for
 * @param CursorState The cursor state to set (eg CURSOR_STATE_ON)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_set_cursor_state(WINDOW_HANDLE handle, CURSOR_STATE cursorstate);

/**
 * @brief Get the current cursor shape of an existing console window
 * @param Handle The handle of the window to get the shape for
 * @return The current cursor shape (eg CURSORLINE)
 */
CURSOR_SHAPE STDCALL graphics_window_get_cursor_shape(WINDOW_HANDLE handle);

/**
 * @brief Set the current cursor shape of an existing console window
 * @param Handle The handle of the window to set the shape for
 * @param CursorShape The cursor shape to set (eg CURSORLINE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_set_cursor_shape(WINDOW_HANDLE handle, CURSOR_SHAPE cursorshape);

/**
 * @brief Enable the cursor on an existing console window
 * @param Handle The handle of the window to enable the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_cursor_on(WINDOW_HANDLE handle);

/**
 * @brief Disable the cursor on an existing console window
 * @param Handle The handle of the window to disable the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_cursor_off(WINDOW_HANDLE handle);

/**
 * @brief Change the cursor to a vertical line on an existing console window
 * @param Handle The handle of the window to change the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_cursor_line(WINDOW_HANDLE handle);

/**
 * @brief Change the cursor to a horizontal bar on an existing console window
 * @param Handle The handle of the window to change the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_cursor_bar(WINDOW_HANDLE handle);

/**
 * @brief Change the cursor to a solid block on an existing console window
 * @param Handle The handle of the window to change the cursor for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_cursor_block(WINDOW_HANDLE handle);

/**
 * @brief Move the cursor on an existing console window
 * @param Handle The handle of the window to move the cursor for
 * @param X The column to move the cursor to
 * @param Y The row to move the cursor to
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, X and Y are based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_cursor_move(WINDOW_HANDLE handle, uint32_t x, uint32_t y);

/**
 * @brief Set the blink state of the cursor on an existing console window
 * @param Handle The handle of the window to set the blink state for
 * @param Enabled True if the cursor is blinking, False if not
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_cursor_blink(WINDOW_HANDLE handle, BOOL enabled);

/**
 * @brief Clear the current viewport of an existing console window
 * @param Handle The handle of the window to clear
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL graphics_window_clear(WINDOW_HANDLE handle);

/**
 * @brief Clear part of the the current viewport of an existing console window
 * @param Handle The handle of the window to clear
 * @param X1 The left edge of the area to clear (relative to current viewport)
 * @param Y1 The top edge of the area to clear (relative to current viewport)
 * @param X2 The right edge of the area to clear (relative to current viewport)
 * @param Y2 The bottom edge of the area to clear (relative to current viewport)
 * @param Color The fill color for the area to clear (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_clear_ex(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);

/**
 * @brief Draw a rectangular box outline on an existing console window
 * @param Handle The handle of the window to draw on
 * @param X1 The left edge of the box (relative to current viewport)
 * @param Y1 The top edge of the box (relative to current viewport)
 * @param X2 The right edge of the box (relative to current viewport)
 * @param Y2 The bottom edge of the box (relative to current viewport)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @param Width The width of the box outline
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_box(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);

/**
 * @brief Draw a line on an existing console window
 * @param Handle The handle of the window to draw on
 * @param X1 The left starting point of the line (relative to current viewport)
 * @param Y1 The top starting point of the line (relative to current viewport)
 * @param X2 The right ending point of the line (relative to current viewport)
 * @param Y2 The bottom ending point of the line (relative to current viewport)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @param Width The width of the line
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_line(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);

/**
 * @brief Draw a rectangular filled block on an existing console window
 * @param Handle The handle of the window to draw on
 * @param X1 The left edge of the block (relative to current viewport)
 * @param Y1 The top edge of the block (relative to current viewport)
 * @param X2 The right edge of the block (relative to current viewport)
 * @param Y2 The bottom edge of the block (relative to current viewport)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_block(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);

/**
 * @brief Draw a circle on an existing console window
 * @param Handle The handle of the window to draw on
 * @param X The left starting point of the circle (relative to current viewport)
 * @param Y The top starting point of the circle (relative to current viewport)
 * @param Color The color to draw with (eg COLOR_WHITE)
 * @param Width The width of the circle outline
 * @param Radius The radius of the circle
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_circle(WINDOW_HANDLE handle, uint32_t x, uint32_t y, uint32_t color, uint32_t width, uint32_t radius);

/**
 * @brief Draw a character on an existing console window
 * @param Handle The handle of the window to draw on
 * @param Ch The character to draw
 * @param X The left starting point of the character (relative to current viewport)
 * @param Y The top starting point of the character (relative to current viewport)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_char(WINDOW_HANDLE handle, char ch, uint32_t x, uint32_t y);

/**
 * @brief Draw a character on an existing console window
 * @param Handle The handle of the window to draw on
 * @param Font The handle of the font to draw the character with
 * @param Ch The character to draw
 * @param X The left starting point of the character (relative to current viewport)
 * @param Y The top starting point of the character (relative to current viewport)
 * @param Forecolor The foreground color for the character (eg COLOR_WHITE)
 * @param Backcolor The background color for the character (eg COLOR_BLACK)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_char_ex(WINDOW_HANDLE handle, FONT_HANDLE font, char ch, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

/**
 * @brief Draw a text string on an existing console window
 * @param Handle The handle of the window to draw on
 * @param Text The text to draw
 * @param X The left starting point of the text (relative to current viewport)
 * @param Y The top starting point of the text (relative to current viewport)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_text(WINDOW_HANDLE handle, const char *text, uint32_t x, uint32_t y);

/**
 * @brief Draw a text string on an existing console window
 * @param Handle The handle of the window to draw on
 * @param Font The handle of the font to draw the text with
 * @param Text The text to draw
 * @param X The left starting point of the text (relative to current viewport)
 * @param Y The top starting point of the text (relative to current viewport)
 * @param Forecolor The foreground color for the text (eg COLOR_WHITE)
 * @param Backcolor The background color for the text (eg COLOR_BLACK)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_text_ex(WINDOW_HANDLE handle, FONT_HANDLE font, const char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

/**
 * @brief Draw a single pixel on an existing console window
 * @param Handle The handle of the window to draw on
 * @param X The column for the pixel (relative to current viewport)
 * @param Y The row for the pixel (relative to current viewport)
 * @param Color The color for the pixel (eg COLOR_WHITE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_pixel(WINDOW_HANDLE handle, uint32_t x, uint32_t y, uint32_t color);

/**
 * @brief Draw an image on an existing console window
 * @param Handle The handle of the window to draw on
 * @param X The left starting point of the image (relative to current viewport)
 * @param Y The top starting point of the image (relative to current viewport)
 * @param Image Pointer to the image data in a contiguous block of pixel rows
 * @param Width The width in pixels of a row in the image data
 * @param Height The height in pixels of all rows in the image data
 * @param Format The color format of the image data (eg COLOR_FORMAT_ARGB32) Pass COLOR_FORMAT_UNKNOWN to use the window format
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_draw_image(WINDOW_HANDLE handle, uint32_t x, uint32_t y, void *image, uint32_t width, uint32_t height, uint32_t format);

/**
 * @brief Get a single pixel from an existing console window
 * @param Handle The handle of the window to get from
 * @param X The column of the pixel (relative to current viewport)
 * @param Y The row of the pixel (relative to current viewport)
 * @return The color of the pixel at X,Y (eg COLOR_WHITE)
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_pixel(WINDOW_HANDLE handle, uint32_t x, uint32_t y);

/**
 * @brief Get an image from an existing console window
 * @param Handle The handle of the window to get from
 * @param X The left starting point of the image (relative to current viewport)
 * @param Y The top starting point of the image (relative to current viewport)
 * @param Image Pointer to a block of memory large enough to hold the image in a contiguous block of pixel rows
 * @param Width The width in pixels of a row of the image
 * @param Height The height in pixels of all rows of the image
 * @param Format The color format to store in the image data (eg COLOR_FORMAT_ARGB32) Pass COLOR_FORMAT_UNKNOWN to use the window format
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_get_image(WINDOW_HANDLE handle, uint32_t x, uint32_t y, void *image, uint32_t width, uint32_t height, uint32_t format);

/**
 * @brief Copy an image from one place to another in an existing console window
 * @param Handle The handle of the window to copy from and to
 * @param Source The starting point (X,Y) to copy the image from
 * @param Dest The starting point (X,Y) to copy the image to
 * @param Width The width in pixels of each row of the image
 * @param Height The height in pixels of all rows of the image
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_copy_image(WINDOW_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, uint32_t width, uint32_t height);

/**
 * @brief Move an image from one place to another in an existing console window
 * @param Handle The handle of the window to copy from and to
 * @param Source The starting point (X,Y) to copy the image from
 * @param Dest The starting point (X,Y) to copy the image to
 * @param Width The width in pixels of each row of the image
 * @param Height The height in pixels of all rows of the image
 * @param Fillcolor The color to fill the area where the image was moved from (COLOR_NONE for no fill, same as copy)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note For Graphics Console functions, Viewport is based on screen pixels not characters
 */
uint32_t STDCALL graphics_window_move_image(WINDOW_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, uint32_t width, uint32_t height, uint32_t fillcolor);

/**
 * @brief Calculate the size in bytes of an image that is Width by Height in the color format specified
 * @param Handle The handle of the window for the image
 * @param Width The width of the image in pixels
 * @param Height The height of the image in pixels
 * @param Format The color format to use for the calculation (eg COLOR_FORMAT_ARGB32) Pass COLOR_FORMAT_UNKNOWN to use the window format
 * @param Stride The distance in bytes between each row of pixels (Optional)
 * @return The size in bytes for an image of the specified size and format or 0 on error
 */
uint32_t STDCALL graphics_window_image_size(WINDOW_HANDLE handle, uint32_t width, uint32_t height, uint32_t format, uint32_t stride);

/** Graphics Console Helper Functions */

/**
 * @brief Get the current console window count
 * @param Console The console device to get the window count for
 * @return The current number of console windows on the specified console device
 */
uint32_t STDCALL graphics_window_get_count(CONSOLE_DEVICE *console);

/**
 * @brief Get the current console active window
 * @param Console The console device to get the active window for
 * @return The window handle of the current active window or INVALID_HANDLE_VALUE on failure
 */
WINDOW_HANDLE STDCALL graphics_window_get_active(CONSOLE_DEVICE *console);

/**
 * @brief Check if a console window entry is valid
 * @param Console The console device to search for the window
 * @param Window The window entry to check for validity
 * @return The supplied window if successful or nil on failure
 */
GRAPHICS_WINDOW * STDCALL graphics_window_check(CONSOLE_DEVICE *console, GRAPHICS_WINDOW *window);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_GRAPHICSCONSOLE_H