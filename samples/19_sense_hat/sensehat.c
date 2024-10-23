/*
 *
 * Sense HAT example project for Ultibo API
 * 
 * A very simple example that shows how you can use the Raspberry Pi SenseHAT
 * with Ultibo.
 *
 * The joystick buttons are read and the names displayed on the LED matrix to
 * show which button was pressed.
 *
 * If the device tree files (*.dtb) are present on your SD card then you must
 * ensure the overlays folder is also present and add the following line to
 * the config.txt file in the root directory:
 *
 * dtoverlay=rpi-sense
 *
 * or alternatively disable device tree loading by adding the following line to
 * the config.txt file:
 *
 * device_tree=
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
#include "ultibo/font.h"
#include "ultibo/console.h"
#include "ultibo/keyboard.h"
#include "ultibo/framebuffer.h"
#include "ultibo/graphicsconsole.h"

int apimain(int argc, char **argv)
{
  int count;
  char character;
  char buffer[256];

  WINDOW_HANDLE windowhandle;
  char name[DEVICE_NAME_LENGTH];
  char description[DEVICE_DESC_LENGTH];
  FRAMEBUFFER_DEVICE *framebuffer_device;

  /* Get the framebuffer device which represents our SenseHAT 8x8 LED matrix, 
   * the description can be found in the header of the SenseHAT driver unit
   */
  framebuffer_device = framebuffer_device_find_by_description("Raspberry Pi Sense HAT Framebuffer");

  /* Now we create a graphics window on the console which is attached to our SenseHAT.
   *
   * All framebuffer console devices will have a description that begins with the words
   * "Framebuffer Console" and has the name of the framebuffer device in brackets
   */
  device_get_name(&framebuffer_device->device, name, sizeof(name));
  sprintf(description, "Framebuffer Console (%s)", name);
  windowhandle = graphics_window_create(console_device_find_by_description(description), CONSOLE_POSITION_FULLSCREEN);

  /* Set the graphics window font to be Latin1 8x8 */
  graphics_window_set_font(windowhandle, font_find_by_name("Latin1-8x8"));

  /* Set the foreground and background colors to be white on black */
  graphics_window_set_backcolor(windowhandle, COLOR_BLACK);
  graphics_window_set_forecolor(windowhandle, COLOR_WHITE);

  /* And finally clear the window which will blank our SenseHAT display */
  graphics_window_clear(windowhandle);

  /* The SenseHAT joystick appears in Ultibo as a keyboard so we can just
   * use console_get_key() to check for the Left, Right, Up, Down and Enter 
   * keys will be sent by the joystick.  
   
   * If you have a real keyboard plugged in you will also see that the arrow
   * and enter keys do the same thing
   */

  /* Loop endlessly while checking for Keyboard characters */
  while (true)
  {
    /* Read a character from the global keyboard buffer */
    if (console_get_key(&character, NULL))
    {
      /* Empty our buffer */
      memset(buffer, 0, sizeof(buffer));

      /* Before we do anything, check what key was pressed */
      if ((uint8_t)character == 0)
      {
        /* The Left, Right, Up and Down arrows will appear as extended keys so
         * the first character received will be 0, we call console_get_key()
         * again to receive the actual character.
         
         * You can find the complete list of these extended keys here:
         
         * https://www.freepascal.org/docs-html/rtl/keyboard/kbdscancode.html
         */
        console_get_key(&character, NULL);

        switch ((uint8_t)character)
        {
          /* Left Arrow */
          case 75:
            sprintf(buffer, "Left");

            break;
          /* Right Arrow */
          case 77:
            sprintf(buffer, "Right");

            break;
          /* Up Arrow */
          case 72:
            sprintf(buffer, "Up");

            break;
          /* Down Arrow */
          case 80:
            sprintf(buffer, "Down");
        }
      }
      else if ((uint8_t)character == 13)
      {
        /* Check if the enter key was pressed */
        sprintf(buffer, "Enter");
      }
      else
      {
        /* Some other key was pressed, just ignore it */
      }

      /* If one of the joystick buttons was pressed above then our buffer will
       * contain the message to be displayed
       */
      if (strlen(buffer))
      {
        /* Display each character in the buffer on our SenseHAT window */
        for (count = 0; count < strlen(buffer); count++)
        {
          /* The SenseHAT is exactly 8x8 pixels just like our Latin1 8x8 font
           * so we just display the character at position 0, 0
           */
          graphics_window_draw_text(windowhandle, &buffer[count], 0, 0);

          /* Sleep for a short time to allow us to see the character */
          thread_sleep(400);

          /* Then loop and display the next one */
        }

        /* Sleep for a little longer after the last character before returning
         * to check for the next key press
         */   
        thread_sleep(1000);

        /* Clear the display */
        graphics_window_clear(windowhandle);
      }
    }

    /* No need to sleep on each loop, console_get_key() will wait until a key is pressed */
  }
  
  /* No need to halt, since we never exit the loop */
  
  return 0;
}
