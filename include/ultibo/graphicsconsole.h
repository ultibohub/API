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
#ifndef _ULTIBO_GRAPHICSCONSOLE_H
#define _ULTIBO_GRAPHICSCONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/console.h"

/* ============================================================================== */
/* Graphics Console specific constants */

/* ============================================================================== */
/* Graphics Console specific types */
/* Graphics Window Enumeration Callback */
typedef console_window_enumerate_cb graphics_window_enumerate_cb;

/* Graphics Window */
typedef CONSOLE_WINDOW GRAPHICS_WINDOW;

/* ============================================================================== */
/* Graphics Console Functions */
WINDOW_HANDLE STDCALL graphics_window_create(CONSOLE_DEVICE *console, uint32_t position);
WINDOW_HANDLE STDCALL graphics_window_create_ex(CONSOLE_DEVICE *console, FONT_HANDLE font, uint32_t size, uint32_t state, uint32_t mode, uint32_t position);
uint32_t STDCALL graphics_window_destroy(WINDOW_HANDLE handle);

uint32_t STDCALL graphics_window_show(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_hide(WINDOW_HANDLE handle);

uint32_t STDCALL graphics_window_activate(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_deactivate(WINDOW_HANDLE handle);

WINDOW_HANDLE STDCALL graphics_window_next(CONSOLE_DEVICE *console, BOOL visible);
WINDOW_HANDLE STDCALL graphics_window_previous(CONSOLE_DEVICE *console, BOOL visible);

WINDOW_HANDLE STDCALL graphics_window_at(CONSOLE_DEVICE *console, uint32_t x, uint32_t y, BOOL visible);
WINDOW_HANDLE STDCALL graphics_window_find(CONSOLE_DEVICE *console, uint32_t position);
uint32_t STDCALL graphics_window_enumerate(CONSOLE_DEVICE *console, graphics_window_enumerate_cb callback, void *data);

BOOL STDCALL graphics_window_check_flag(WINDOW_HANDLE handle, uint32_t flag);
uint32_t STDCALL graphics_window_update_flag(WINDOW_HANDLE handle, uint32_t flag, BOOL clear);

uint32_t STDCALL graphics_window_get_mode(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_get_state(WINDOW_HANDLE handle);

uint32_t STDCALL graphics_window_get_position(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_position(WINDOW_HANDLE handle, uint32_t position);

uint32_t STDCALL graphics_window_get_properties(WINDOW_HANDLE handle, WINDOW_PROPERTIES *properties);

uint32_t STDCALL graphics_window_get_min_x(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_get_min_y(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_get_max_x(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_get_max_y(WINDOW_HANDLE handle);

CONSOLE_RECT STDCALL graphics_window_get_rect(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_rect(WINDOW_HANDLE handle, CONSOLE_RECT *rect);
uint32_t STDCALL graphics_window_reset_rect(WINDOW_HANDLE handle);

uint32_t STDCALL graphics_window_get_viewport(WINDOW_HANDLE handle, uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2);
uint32_t STDCALL graphics_window_set_viewport(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
uint32_t STDCALL graphics_window_reset_viewport(WINDOW_HANDLE handle);

uint32_t STDCALL graphics_window_get_cols(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_get_rows(WINDOW_HANDLE handle);

uint32_t STDCALL graphics_window_get_width(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_get_height(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_get_format(WINDOW_HANDLE handle);

uint32_t STDCALL graphics_window_get_forecolor(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_forecolor(WINDOW_HANDLE handle, uint32_t color);
uint32_t STDCALL graphics_window_get_backcolor(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_backcolor(WINDOW_HANDLE handle, uint32_t color);

FONT_HANDLE STDCALL graphics_window_get_font(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_font(WINDOW_HANDLE handle, FONT_HANDLE font);

uint32_t STDCALL graphics_window_get_cursor_xy(WINDOW_HANDLE handle, uint32_t *x, uint32_t *y);
uint32_t STDCALL graphics_window_set_cursor_xy(WINDOW_HANDLE handle, uint32_t x, uint32_t y);
CURSOR_MODE STDCALL graphics_window_get_cursor_mode(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_cursor_mode(WINDOW_HANDLE handle, CURSOR_MODE cursormode);
BOOL STDCALL graphics_window_get_cursor_blink(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_cursor_blink(WINDOW_HANDLE handle, BOOL cursorblink);
CURSOR_STATE STDCALL graphics_window_get_cursor_state(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_cursor_state(WINDOW_HANDLE handle, CURSOR_STATE cursorstate);
CURSOR_SHAPE STDCALL graphics_window_get_cursor_shape(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_set_cursor_shape(WINDOW_HANDLE handle, CURSOR_SHAPE cursorshape);

uint32_t STDCALL graphics_window_cursor_on(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_cursor_off(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_cursor_line(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_cursor_bar(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_cursor_block(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_cursor_move(WINDOW_HANDLE handle, uint32_t x, uint32_t y);
uint32_t STDCALL graphics_window_cursor_blink(WINDOW_HANDLE handle, BOOL enabled);

uint32_t STDCALL graphics_window_clear(WINDOW_HANDLE handle);
uint32_t STDCALL graphics_window_clear_ex(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);

uint32_t STDCALL graphics_window_draw_box(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
uint32_t STDCALL graphics_window_draw_line(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, uint32_t width);
uint32_t STDCALL graphics_window_draw_block(WINDOW_HANDLE handle, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
uint32_t STDCALL graphics_window_draw_circle(WINDOW_HANDLE handle, uint32_t x, uint32_t y, uint32_t color, uint32_t width, uint32_t radius);

uint32_t STDCALL graphics_window_draw_char(WINDOW_HANDLE handle, char ch, uint32_t x, uint32_t y);
uint32_t STDCALL graphics_window_draw_char_ex(WINDOW_HANDLE handle, FONT_HANDLE font, char ch, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

uint32_t STDCALL graphics_window_draw_text(WINDOW_HANDLE handle, const char *text, uint32_t x, uint32_t y);
uint32_t STDCALL graphics_window_draw_text_ex(WINDOW_HANDLE handle, FONT_HANDLE font, const char *text, uint32_t x, uint32_t y, uint32_t forecolor, uint32_t backcolor);

uint32_t STDCALL graphics_window_draw_pixel(WINDOW_HANDLE handle, uint32_t x, uint32_t y, uint32_t color);
uint32_t STDCALL graphics_window_draw_image(WINDOW_HANDLE handle, uint32_t x, uint32_t y, void *image, uint32_t width, uint32_t height, uint32_t format);

uint32_t STDCALL graphics_window_get_pixel(WINDOW_HANDLE handle, uint32_t x, uint32_t y);
uint32_t STDCALL graphics_window_get_image(WINDOW_HANDLE handle, uint32_t x, uint32_t y, void *image, uint32_t width, uint32_t height, uint32_t format);

uint32_t STDCALL graphics_window_copy_image(WINDOW_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, uint32_t width, uint32_t height);
uint32_t STDCALL graphics_window_move_image(WINDOW_HANDLE handle, CONSOLE_POINT *source, CONSOLE_POINT *dest, uint32_t width, uint32_t height, uint32_t fillcolor);

uint32_t STDCALL graphics_window_image_size(WINDOW_HANDLE handle, uint32_t width, uint32_t height, uint32_t format, uint32_t stride);

/* ============================================================================== */
/* Graphics Console Helper Functions */
uint32_t STDCALL graphics_window_get_count(CONSOLE_DEVICE *console);
WINDOW_HANDLE STDCALL graphics_window_get_active(CONSOLE_DEVICE *console);

GRAPHICS_WINDOW * STDCALL graphics_window_check(CONSOLE_DEVICE *console, GRAPHICS_WINDOW *window);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_GRAPHICSCONSOLE_H