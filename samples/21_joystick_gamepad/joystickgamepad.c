/*
 *
 * Joystick Gamepad example project for Ultibo API
 * 
 * An example that shows how to use the Joystick unit to read input from a USB
 * joystick or gamepad device and use it to move a cross around the screen and
 * draw a colored circle wherever a button is pressed.
 *
 * It's more exciting than it sounds, even if you don't want to use a joystick
 * in your application if you have one lying around give it a go just for fun.
 * 
 * 
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Garry Wood <garry@softoz.com.au>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"
#include "ultibo/font.h"
#include "ultibo/joystick.h"
#include "ultibo/framebuffer.h"
#include "ultibo/graphicsconsole.h"

/* Define some custom colors (From: https://www.w3schools.com/tags/ref_colornames.asp) */
#define Aqua 0xFF00FFFF
#define BlueViolet 0xFF8A2BE2
#define Chartreuse 0xFF7FFF00
#define Crimson 0xFFDC143C
#define DarkOrange 0xFFFF8C00
#define DarkRed 0xFF8B0000
#define DeepPink 0xFFFF1493
#define DeepSkyBlue 0xFF00BFFF
#define FireBrick 0xFFB22222
#define ForestGreen 0xFF228B22
#define Fuchsia 0xFFFF00FF
#define Gold 0xFFFFD700
#define GreenYellow 0xFFADFF2F
#define HotPink 0xFFFF69B4
#define Indigo 0xFF4B0082
#define LawnGreen 0xFF7CFC00
#define LightCoral 0xFFF08080
#define LightGreen 0xFF90EE90
#define LightPink 0xFFFFB6C1
#define LightSkyBlue 0xFF87CEFA
#define Lime 0xFF00FF00
#define Maroon 0xFF800000
#define MediumOrchid 0xFFBA55D3
#define MediumPurple 0xFF9370DB
#define MidnightBlue 0xFF191970
#define Moccasin 0xFFFFE4B5
#define Olive 0xFF808000
#define Orange 0xFFFFA500
#define Orchid 0xFFDA70D6
#define Peru 0xFFCD853F
#define Plum 0xFFDDA0DD
#define RoyalBlue 0xFF4169E1
#define SeaGreen 0xFF2E8B57
#define SkyBlue 0xFF87CEEB
#define SlateBlue 0xFF6A5ACD
#define SpringGreen 0xFF00FF7F
#define SteelBlue 0xFF4682B4
#define Teal 0xFF008080
#define Tomato 0xFFFF6347
#define Violet 0xFFEE82EE
#define Yellow 0xFFFFFF00
#define Magenta 0xFFFF00FF
#define Red 0xFFFF0000

static uint32_t BUTTON_COLORS[] = {
  Aqua,
  BlueViolet,
  Chartreuse,
  Crimson,
  DarkOrange,
  Yellow,
  DeepPink,
  DeepSkyBlue,
  Tomato,
  SpringGreen,
  Fuchsia,
  Gold,
  GreenYellow,
  HotPink,
  Indigo,
  LawnGreen,
  LightCoral,
  LightGreen,
  LightPink,
  LightSkyBlue,
  Lime,
  Magenta,
  MediumOrchid,
  MediumPurple,
  MidnightBlue,
  Moccasin,
  Olive,
  Orange,
  Orchid,
  Peru,
  Plum,
  Red
};

/* Define a custom cursor */
#define CURSOR_WIDTH 32
#define CURSOR_HEIGHT 32
#define CURSOR_FORMAT COLOR_FORMAT_DEFAULT
#define CURSOR_HOTSPOTX 16
#define CURSOR_HOTSPOTY 16

static uint32_t CURSOR_CROSS[CURSOR_HEIGHT * CURSOR_WIDTH] = {
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
  COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE
};

/* Some global variables to track our cursor */
int32_t cursor_x, cursor_y;
int32_t button_x, button_y, button_index;
uint32_t screen_width, screen_height;

/* The thread function to read input from our joystick */
ssize_t STDCALL joystick_thread(void * parameter)
{
  int res = 0;
  uint32_t count;
  JOYSTICK_DATA joystick_data;
  JOYSTICK_DEVICE *joystick_device;
  JOYSTICK_PROPERTIES joystick_properties;

  /* Get the joystick or gamepad device */
  joystick_device = joystick_device_find_by_name("Joystick0");
  if (!joystick_device)
    return res;

  /* Get the joystick or gamepad properties */
  if (joystick_device_get_properties(joystick_device, &joystick_properties) != ERROR_SUCCESS)
    return res;

  /* Find the X and Y axes from our device */
  /* The properties will include the number of axes, hats and buttons found.
   *
   * For each axis or hat we can find the name and minimum and maximum values,
   * for each button there is just a name that identifies the button.
   * 
   * The name isn't a text value, that would be too slow, instead the name is
   * a numeric identifier that can be easily checked by an application. We've
   * defined some values in the Joystick unit but you can also assign your own
   * values since the underlying code doesn't look at the name for anything
   */
  int32_t index_x = -1;
  int32_t index_y = -1;
  int32_t middle_x = -1;
  int32_t middle_y = -1;
  if (joystick_properties.axiscount > 0)
  {

    for (count = 0; count < joystick_properties.axiscount; count++)
    {
      /* Check if this is an X axis */
      if (joystick_properties.axes[count].name == JOYSTICK_AXIS_X)
      {
        /* Save the Index which we can use to lookup the X value in the input data */
        index_x = count;

        /* Calculate the middle value, most joysticks will report the middle value when idle */
        middle_x = (joystick_properties.axes[count].logical.maximum - joystick_properties.axes[count].logical.minimum) / 2;
      }

      /* Check if this is a Y axis */
      if (joystick_properties.axes[count].name == JOYSTICK_AXIS_Y)
      {
        /* Save the Index again so we can lookup the Y value in the input data */
        index_y = count;

        /* Calculate the middle value for Y */
        middle_y = (joystick_properties.axes[count].logical.maximum - joystick_properties.axes[count].logical.minimum) / 2;
      }
    }

  }

  /* Save the current cursor X and Y, just for this thread */
  int32_t axis_x = cursor_x;
  int32_t axis_y = cursor_y;

  while (true)
  {
    /* Read the next joystick input report from the queue */
    uint32_t status = joystick_device_read(joystick_device, &joystick_data, sizeof(joystick_data), JOYSTICK_FLAG_NONE, &count);
    if (status == ERROR_SUCCESS)
    {
      /* Check if we found an X axis */
      if (index_x != -1)
      {
        /* Use the latest X value to update our cursor position.
         *
         * Notice that we can use the index value from the properties to access
         * the X axis value in the joystick data, that's because the indexes will
         * be the same for every report received and will always match the properties.
         *
         * The same applies to hats and buttons so we can quickly reference any
         * item in the data if we've already located it during initialization
         */
        if (joystick_data.axes[index_x] < middle_x)
          axis_x--;
        else if (joystick_data.axes[index_x] > middle_x)
          axis_x++;
      }

      /* Check if we found a Y axis */
      if (index_y != -1)
      {
        /* Use the latest Y value to update our cursor position */
        if (joystick_data.axes[index_y] < middle_y)
          axis_y--;
        else if (joystick_data.axes[index_y] > middle_y)
          axis_y++;
      }

      /* Check that our X value doesn't go off the screen */
      if (axis_x < 0)
        axis_x = 0;
      if (axis_x > screen_width - 1)
        axis_x = screen_width - 1;

      /* Check that our Y value doesn't go off the screen */
      if (axis_y < 0)
        axis_y = 0;
      if (axis_y > screen_height - 1)
        axis_y = screen_height - 1;

      /* Update the real cursor X and Y values */
      cursor_x = axis_x;
      cursor_y = axis_y;

      /* Check if any buttons were found */
      if (joystick_data.buttoncount > 0)
      {
        for (count = 0; count < joystick_data.buttoncount; count++)
        {
          /* Check if this button is pressed, buttons are only
           * either on or off and don't return a value.
           *
           * Some devices have analog buttons that return a number
           * and these will be reported in the axes array instead
           */
          if ((joystick_data.buttons & (1 << count)) != 0)
          {
            button_x = cursor_x;
            button_y = cursor_y;
            button_index = count;

            break;
          }
        }
      }
    }
    else if (status == ERROR_NO_MORE_ITEMS)
    {
      /* If something went wrong like the joystick or gamepad got
       * unplugged then stop reading events and terminate our thread
       */
      break;
    }
  }

  return res;
}


int apimain(int argc, char **argv)
{
  char value[256];
  WINDOW_HANDLE windowhandle;
  THREAD_HANDLE threadhandle;
  FRAMEBUFFER_DEVICE *framebuffer_device;
  FRAMEBUFFER_PROPERTIES framebuffer_properties;

  /* Create a graphics console window that covers the full screen */
  windowhandle = graphics_window_create(console_device_get_default(), CONSOLE_POSITION_FULLSCREEN);

  /* Get the width and height of the font from our window */
  uint32_t font_width = font_get_width(graphics_window_get_font(windowhandle));
  uint32_t font_height = font_get_height(graphics_window_get_font(windowhandle));

  /* Output some welcome text on the console window */
  graphics_window_draw_text(windowhandle, "Welcome to Example 21 Joystick Gamepad", 1, 1);
  graphics_window_draw_text(windowhandle, "Use the joystick to move the cross", 1, (font_height * 2) + 1);
  graphics_window_draw_text(windowhandle, "Press any button to draw a colored circle", 1, (font_height * 3) + 1);

  /* Wait for a joystick or gamepad to be available */
  if (joystick_device_find_by_name("Joystick0") == NULL)
  {
    graphics_window_draw_text(windowhandle, "Waiting for a joystick or gamepad device", 1, (font_height * 5) + 1);

    /* Get the current tick count (in milliseconds) */
    uint64_t start = get_tick_count64();
    while (joystick_device_find_by_name("Joystick0") == NULL)
    {
      /* Sleep for 10 milliseconds */
      thread_sleep(10);

      /* Check the tick count to see if 10 seconds has passed */
      if (get_tick_count64() > (start + 10000))
        break;
    }
  }

  /* Check to see if a joystick or gamepad was found */
  if (joystick_device_find_by_name("Joystick0") == NULL)
    graphics_window_draw_text(windowhandle, "Unable to detect a joystick or gamepad device, the example may not work", 1, (font_height * 6) + 1);
  else
    graphics_window_draw_text(windowhandle, "Joystick0 detected successfully", 1, (font_height * 6) + 1);

  /* We'll setup the cursor much the same as we did in Example 15. First we get the size of the screen
   * by getting the properties of the default framebuffer and storing the width and height for later
   */

  /* Get the default framebuffer device */
  framebuffer_device = framebuffer_device_get_default();

  /* Get the properties of the default framebuffer */
  framebuffer_device_get_properties(framebuffer_device, &framebuffer_properties);

  /* Get the screen width and height from the properties */
  screen_width = framebuffer_properties.physicalwidth;
  screen_height = framebuffer_properties.physicalheight;

  /* Set the cursor, this time we're using a custom cursor shape and not the default arrow */
  framebuffer_device_set_cursor(framebuffer_device, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_HOTSPOTX, CURSOR_HOTSPOTY, CURSOR_CROSS, sizeof(CURSOR_CROSS));

  /* Setup the cursor state, because we are going to use a thread to read the joystick input
   * we'll also store the last X and Y position of the cursor so we know if it has been moved
   */
  cursor_x = screen_width / 2;
  cursor_y = screen_height / 2;
  uint32_t cursor_last_x = cursor_x;
  uint32_t cursor_last_y = cursor_y;

  /* Enable the cursor and set it to the center of the screen */
  framebuffer_device_update_cursor(framebuffer_device, TRUE, cursor_x, cursor_y, FALSE);

  /* Setup our button state, again we track the last position as well for easy comparison */
  button_x = -1;
  button_y = -1;
  button_index = -1;
  int32_t button_last_x = -1;
  int32_t button_last_y = -1;
  int32_t button_last_index = -1;

  /* Joysticks and Gamepads can send data at a very rapid rate so we're going to use a thread
   * to read the input data from the joystick and update the position of the cursor and our
   * button state. This thread only reads the data and doesn't try to draw anything on the
   * screen which means it can process the joystick events very quickly.
   * 
   * If we tried to read the data and draw the screen the input buffer from the joystick
   * might overflow and we could lose events coming from the joystick
   */
  threadhandle = begin_thread(NULL, thread_get_stack_size(thread_get_current()), joystick_thread, NULL, THREAD_CREATE_NONE, &threadhandle);

  /* Loop endlessly, checking for cursor and button changes */
  while (true)
  {
    /* Check if the cursor has moved */
    if (cursor_x != cursor_last_x || cursor_y != cursor_last_y)
    {
      /* Move the cursor on the screen */
      framebuffer_device_update_cursor(framebuffer_device, TRUE, cursor_x, cursor_y, FALSE);

      /* Save the last X and Y of the cursor */
      cursor_last_x = cursor_x;
      cursor_last_y = cursor_y;
    }

    /* Check if a button has been pressed */
    if (button_x != button_last_x || button_y != button_last_y || button_index != button_last_index)
    {
      /* Draw a circle on the screen */
      graphics_window_draw_circle(windowhandle, button_x, button_y, BUTTON_COLORS[button_index], 40, 40);

      /* These two lines to put the button index number in the middle of the circle 
       * so you can see the relationship between the buttons and the joystick data
       */
      sprintf(value, "%d", (int)button_index);
      graphics_window_draw_text(windowhandle, value, button_x - (font_width / 2), button_y - (font_height / 2));

      /* Save the last X, Y and Index of the button */
      button_last_x = button_x;
      button_last_y = button_y;
      button_last_index = button_index;
    }

    /* Yield the CPU so other threads can run */
    thread_sleep(0);
  }
  
  /* No need to halt, since we never exit the loop */
  
  return 0;
}
