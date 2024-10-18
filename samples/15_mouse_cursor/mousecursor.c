/*
 *
 * Mouse Cursor example project for Ultibo API
 * 
 * This is a simple example that shows how to read data from the mouse buffer
 * and use it to track the position of a mouse cursor on the screen.
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
#include <stdbool.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"
#include "ultibo/mouse.h"
#include "ultibo/framebuffer.h"

int apimain(int argc, char **argv)
{
  char value[256];
  char buttons[64];

  WINDOW_HANDLE handle1, handle2;

  int32_t cursor_x, cursor_y;
  double_t scaling_x, scaling_y;
  uint32_t screen_width, screen_height;

  uint32_t count;
  MOUSE_DATA mouse_data;
  FRAMEBUFFER_DEVICE *framebuffer_device;
  FRAMEBUFFER_PROPERTIES framebuffer_properties;

  /* Create a console window on the left */
  handle1 = console_window_create(console_device_get_default(), CONSOLE_POSITION_LEFT, FALSE);

  /* And another one on the right */
  handle2 = console_window_create(console_device_get_default(), CONSOLE_POSITION_RIGHT, TRUE);

  /* Output some welcome text on the left console window */
  console_window_write_ln(handle1, "Welcome to Example 15 Mouse Cursor");
  console_window_write_ln(handle1, "Make sure you have a USB mouse connected, try moving it and clicking the buttons to see what happens");

  /* Let's setup the mouse cursor so we can move it around the screen. The Raspberry Pi
   * has cursor support built in to the graphics processor (GPU) so we can use that to
   * display the cursor on screen.
   * 
   * First we need to find out how big the screen is in pixels wide and high, to do this
   * we ask for the default framebuffer device and then retrieve the properties which will
   * give us the size as well as lots of other information.
   * 
   * Get the default framebuffer device
   */
  framebuffer_device = framebuffer_device_get_default();

  /* Get the properties of the default framebuffer */
  framebuffer_device_get_properties(framebuffer_device, &framebuffer_properties);

  /* Get the screen width and height from the properties */
  screen_width = framebuffer_properties.physicalwidth;
  screen_height = framebuffer_properties.physicalheight;

  /* Print our screen dimensions on the console */
  sprintf(value, "Screen is %u pixels wide by %u pixels high", (unsigned int)screen_width, (unsigned int)screen_height);
  console_window_write_ln(handle1, value);

  /* We need to create a mouse cursor to display on the screen, for this example we'll just
   * use the built in arrow which is the default cursor. If you read the description of the
   * framebuffer_device_set_cursor function you will see that you can define a block of pixels
   * to create your own cursor shape, to use the default we simply pass zero or nil for all
   * the parameters except the framebuffer device itself 
   */
  framebuffer_device_set_cursor(framebuffer_device, 0, 0, 0, 0, NULL, 0);

  /* Now we can turn on the cursor and set it to the middle of the screen.
   *
   * We'll use a couple of variables to track the position in response to mouse messages
   */
  cursor_x = screen_width / 2;
  cursor_y = screen_height / 2;
  framebuffer_device_update_cursor(framebuffer_device, TRUE, cursor_x, cursor_y, FALSE);

  /* Loop endlessly checking for Mouse messages */
  while (true)
  {
    /* Read the next message from the global mouse buffer. If there are multiple mice
     * attached then messages from all of them will appear in the same buffer.
     *
     * What happens if no mouse is attached?
     * 
     * The mouse_read() function will simply wait forever, Ultibo has dynamic USB attach
     * and detach so as soon as you plug in a mouse the messages will start to arrive
     */

    /* The mouse_read() function needs a buffer to return MOUSE_DATA structures into, if
     * you pass a buffer that is bigger than a single MOUSE_DATA then it can return
     * multiple messages in one request and the count variable will tell you how many
     * messages were received
     */
    if (mouse_read(&mouse_data, sizeof(MOUSE_DATA), &count) == ERROR_SUCCESS)
    {
      /* We received a mouse message so let's process it to see what it contains.
       *
       * The MOUSE_DATA structure will give us an X an Y Offset as well as any buttons
       * that are currently pressed
       */

      /* Check the buttons */
      if ((mouse_data.buttons & ~(MOUSE_ABSOLUTE_X | MOUSE_ABSOLUTE_Y | MOUSE_ABSOLUTE_WHEEL)) == 0)
        sprintf(buttons, "None");
      else
      {
        if ((mouse_data.buttons & (MOUSE_LEFT_BUTTON | MOUSE_RIGHT_BUTTON)) == (MOUSE_LEFT_BUTTON | MOUSE_RIGHT_BUTTON))
          sprintf(buttons, "Both");
        else if ((mouse_data.buttons & MOUSE_LEFT_BUTTON) == MOUSE_LEFT_BUTTON)
          sprintf(buttons, "Left");
        else if ((mouse_data.buttons & MOUSE_RIGHT_BUTTON) == MOUSE_RIGHT_BUTTON)
          sprintf(buttons, "Right");
        else if ((mouse_data.buttons & MOUSE_MIDDLE_BUTTON) == MOUSE_MIDDLE_BUTTON)
          sprintf(buttons, "Middle");
        else if ((mouse_data.buttons & MOUSE_SIDE_BUTTON) == MOUSE_SIDE_BUTTON)
          sprintf(buttons, "Side");
        else if ((mouse_data.buttons & MOUSE_EXTRA_BUTTON) == MOUSE_EXTRA_BUTTON)
          sprintf(buttons, "Extra");
        else if ((mouse_data.buttons & MOUSE_TOUCH_BUTTON) == MOUSE_TOUCH_BUTTON)
          sprintf(buttons, "Touch");
        else
          sprintf(buttons, "Other");
      }
      
      /* Display the mouse data in the right window */
      sprintf(value, "Mouse OffsetX = %d OffsetY = %d Buttons = %s", (int)mouse_data.offsetx, (int)mouse_data.offsety, buttons);
      console_window_write_ln(handle2, value);

      /* Now update our mouse tracking for cursor X and Y */
      /* Check if the X value is absolute instead of relative */
      if ((mouse_data.buttons & MOUSE_ABSOLUTE_X) == MOUSE_ABSOLUTE_X)
      {
        /* For absolute values the maximum X field allows us to scale
         * the cursor X value relative to the size of our screen
         */
        scaling_x = (double_t)mouse_data.maximumx / screen_width;
        if (scaling_x <= 0)
          scaling_x = 1.0;
        
        cursor_x = (int32_t)mouse_data.offsetx / scaling_x;
      }
      else
        cursor_x += mouse_data.offsetx;
      
      if (cursor_x < 0)
        cursor_x = 0;
      if (cursor_x > screen_width - 1) 
        cursor_x = screen_width - 1;

      /* Check if the Y value is absolute */
      if ((mouse_data.buttons & MOUSE_ABSOLUTE_Y) == MOUSE_ABSOLUTE_Y)
      {
        /* Use maximum Y to scale the Y value to the screen */
        scaling_y = (double_t)mouse_data.maximumy / screen_height;
        if (scaling_y <= 0)
          scaling_y = 1.0;
        
        cursor_y = (int32_t)mouse_data.offsety / scaling_y;
      }
      else
        cursor_y += mouse_data.offsety;

      if (cursor_y < 0)
        cursor_y = 0;
      if (cursor_y > screen_height - 1) 
        cursor_y = screen_height - 1;

      /* And move the cursor on the screen */
      framebuffer_device_update_cursor(framebuffer_device, TRUE, cursor_x, cursor_y, FALSE);
    }
    else
    {
      /* For some reason there was an error, print a message on the console */
      console_window_write_ln(handle2, "An error occurred reading the mouse, trying again");
    }
  }
  
  /* No need to halt, since we never exit the loop */

  return 0;
}
