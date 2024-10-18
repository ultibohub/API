/*
 *
 * Bouncing Boxes example project for Ultibo API
 * 
 * A simple demonstration of animation using the framebuffer device in Ultibo
 * with a virtual width and height that allows fast swapping between pages.
 *
 * The example creates 200 colored boxes and moves them around the screen so
 * that they appear to bounce off the sides.
 *
 * Even though the example is doing all of the drawing using nothing but the
 * CPU it is able to maintain 60 frames per second on any size screen due to
 * some simple optimizations.
 *
 * There are lots of variables that can be changed within the code to make
 * different effects like the speed and number of boxes, colors, sizes and more.
 * Experiment on your own to see what you can create.
 *
 * Warning, the animation is very hypnotic. If you're not careful you can find
 * yourself watching it for hours!
 *
 *
 * This example was originally created by Raspberry Compote for an excellent
 * series entitled 'Low-level Graphics on Raspberry Pi'.
 *
 *  You can find the original series of articles here:
 *   http://raspberrycompote.blogspot.com.au/2012/12/low-level-graphics-on-raspberry-pi-part_9509.html
 *
 *  And the original C source code here:
 *   https://github.com/rst-/raspberry-compote/blob/master/fb/fbtestXIII.c
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
#include "ultibo/framebuffer.h"

/* Some variables used by the animation */
int page_size;
int current_page;
void *buffer_start;
FRAMEBUFFER_DEVICE *framebuffer_device;
FRAMEBUFFER_PROPERTIES framebuffer_properties;

/* A couple of definitions, what happens if you change NUM_ELEMENTS? */
#define NUM_ELEMENTS 200
#define RANDOM_MAX 2147483647

/* Some array variables to track the position of each box */
int element_x[NUM_ELEMENTS];
int element_y[NUM_ELEMENTS];
int element_dir_x[NUM_ELEMENTS];
int element_dir_y[NUM_ELEMENTS];

/* The "standard" VGA Mode 13h palette for 8 bit colors (See: https://en.wikipedia.org/wiki/Mode_13h) */
static FRAMEBUFFER_PALETTE vga_palette = {
  .start = 0,
  .count = 256,
  .entries = {
    0xFF000000, 0xFF0000AA, 0xFF00AA00, 0xFF00AAAA, 0xFFAA0000, 0xFFAA00AA, 0xFFAA5500, 0xFFAAAAAA, 0xFF555555, 0xFF5555FF, 0xFF55FF55, 0xFF55FFFF, 0xFFFF5555, 0xFFFF55FF, 0xFFFFFF55, 0xFFFFFFFF, 
    0xFF000000, 0xFF141414, 0xFF202020, 0xFF2C2C2C, 0xFF383838, 0xFF444444, 0xFF505050, 0xFF606060, 0xFF707070, 0xFF808080, 0xFF909090, 0xFFA0A0A0, 0xFFB4B4B4, 0xFFC8C8C8, 0xFFE0E0E0, 0xFFFCFCFC, 
    0xFF0000FC, 0xFF4000FC, 0xFF7C00FC, 0xFFBC00FC, 0xFFFC00FC, 0xFFFC00BC, 0xFFFC007C, 0xFFFC0040, 0xFFFC0000, 0xFFFC4000, 0xFFFC7C00, 0xFFFCBC00, 0xFFFCFC00, 0xFFBCFC00, 0xFF7CFC00, 0xFF40FC00, 
    0xFF00FC00, 0xFF00FC40, 0xFF00FC7C, 0xFF00FCBC, 0xFF00FCFC, 0xFF00BCFC, 0xFF007CFC, 0xFF0040FC, 0xFF7C7CFC, 0xFF9C7CFC, 0xFFBC7CFC, 0xFFDC7CFC, 0xFFFC7CFC, 0xFFFC7CDC, 0xFFFC7CBC, 0xFFFC7C9C, 
    0xFFFC7C7C, 0xFFFC9C7C, 0xFFFCBC7C, 0xFFFCDC7C, 0xFFFCFC7C, 0xFFDCFC7C, 0xFFBCFC7C, 0xFF9CFC7C, 0xFF7CFC7C, 0xFF7CFC9C, 0xFF7CFCBC, 0xFF7CFCDC, 0xFF7CFCFC, 0xFF7CDCFC, 0xFF7CBCFC, 0xFF7C9CFC, 
    0xFFB4B4FC, 0xFFC4B4FC, 0xFFD8B4FC, 0xFFE8B4FC, 0xFFFCB4FC, 0xFFFCB4E8, 0xFFFCB4D8, 0xFFFCB4C4, 0xFFFCB4B4, 0xFFFCC4B4, 0xFFFCD8B4, 0xFFFCE8B4, 0xFFFCFCB4, 0xFFE8FCB4, 0xFFD8FCB4, 0xFFC4FCB4, 
    0xFFB4FCB4, 0xFFB4FCC4, 0xFFB4FCD8, 0xFFB4FCE8, 0xFFB4FCFC, 0xFFB4E8FC, 0xFFB4D8FC, 0xFFB4C4FC, 0xFF000070, 0xFF1C0070, 0xFF380070, 0xFF540070, 0xFF700070, 0xFF700054, 0xFF700038, 0xFF70001C, 
    0xFF700000, 0xFF701C00, 0xFF703800, 0xFF705400, 0xFF707000, 0xFF547000, 0xFF387000, 0xFF1C7000, 0xFF007000, 0xFF00701C, 0xFF007038, 0xFF007054, 0xFF007070, 0xFF005470, 0xFF003870, 0xFF001C70, 
    0xFF383870, 0xFF443870, 0xFF543870, 0xFF603870, 0xFF703870, 0xFF703860, 0xFF703854, 0xFF703844, 0xFF703838, 0xFF704438, 0xFF705438, 0xFF706038, 0xFF707038, 0xFF607038, 0xFF547038, 0xFF447038, 
    0xFF387038, 0xFF387044, 0xFF387054, 0xFF387060, 0xFF387070, 0xFF386070, 0xFF385470, 0xFF384470, 0xFF505070, 0xFF585070, 0xFF605070, 0xFF685070, 0xFF705070, 0xFF705068, 0xFF705060, 0xFF705058, 
    0xFF705050, 0xFF705850, 0xFF706050, 0xFF706850, 0xFF707050, 0xFF687050, 0xFF607050, 0xFF587050, 0xFF507050, 0xFF507058, 0xFF507060, 0xFF507068, 0xFF507070, 0xFF506870, 0xFF506070, 0xFF505870, 
    0xFF000040, 0xFF100040, 0xFF200040, 0xFF300040, 0xFF400040, 0xFF400030, 0xFF400020, 0xFF400010, 0xFF400000, 0xFF401000, 0xFF402000, 0xFF403000, 0xFF404000, 0xFF304000, 0xFF204000, 0xFF104000, 
    0xFF004000, 0xFF004010, 0xFF004020, 0xFF004030, 0xFF004040, 0xFF003040, 0xFF002040, 0xFF001040, 0xFF202040, 0xFF282040, 0xFF302040, 0xFF382040, 0xFF402040, 0xFF402038, 0xFF402030, 0xFF402028, 
    0xFF402020, 0xFF402820, 0xFF403020, 0xFF403820, 0xFF404020, 0xFF384020, 0xFF304020, 0xFF284020, 0xFF204020, 0xFF204028, 0xFF204030, 0xFF204038, 0xFF204040, 0xFF203840, 0xFF203040, 0xFF202840, 
    0xFF2C2C40, 0xFF302C40, 0xFF342C40, 0xFF3C2C40, 0xFF402C40, 0xFF402C3C, 0xFF402C34, 0xFF402C30, 0xFF402C2C, 0xFF40302C, 0xFF40342C, 0xFF403C2C, 0xFF40402C, 0xFF3C402C, 0xFF34402C, 0xFF30402C, 
    0xFF2C402C, 0xFF2C4030, 0xFF2C4034, 0xFF2C403C, 0xFF2C4040, 0xFF2C3C40, 0xFF2C3440, 0xFF2C3040, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000}
};

/* This example was originally ported from C source code but it limited the screen size
 * to 960 x 540, possibly get the frame rate high enough for the animation to run smoothly.
 *
 * With some optimizations it is possible to get a high frame rate even at a screen size
 * of 1920 x 1080, out of interest the 'orignal' functions plus another variation have been
 * left here to show the optimization process.
 * 
 * The functions put_pixel() and fill_rect1() were ported directly from the original source
 * but the calculation of the pixel_offset value for each pixel in the frame seems to be
 * too slow (it's possible that the C compiler did extra optimization on the original).
 * 
 * The fill_rect2() function is an intermediate step which improved the rate dramatically
 * but was optimized a little more by the final fill_rect() which is the most efficient
 * version and obtains 60 frames per second at any screen size
 */

/* Helper function to 'plot' a pixel in given color */
//static inline void put_pixel(int x, int y, int color)
//{
//  uint8_t *buffer = (uint8_t *)buffer_start;
//
//  /* Calculate the pixel's byte offset inside the buffer */
//  uint32_t pixel_offset = x + (y * framebuffer_properties.pitch);
//
//  /* Offset by the current buffer start */
//  pixel_offset += (current_page * page_size);
//
//  /* This is about the same as 'buffer_start[pixel_offset] = color' */
//  //*((uint8_t*)(buffer_start + pixel_offset)) = color;
//  *((uint8_t*)(buffer + pixel_offset)) = color;
//}

/* Helper function to draw a rectangle in given color */
//static inline void fill_rect1(int x, int y, int width, int height, int color)
//{
//  /* Draw each row of pixels */
//  for (int current_y = 0; current_y < height; current_y++)
//  {
//    /* Draw the pixel for each column */
//    for (int current_x = 0; current_x < width; current_x++)
//    {
//      /* Draw the pixel */
//      put_pixel(x + current_x, y + current_y, color);
//    }
//  }
//}

/* Helper function to draw a rectangle in given color */
//static inline void fill_rect2(int x, int y, int width, int height, int color)
//{
//  uint8_t *buffer = (uint8_t *)buffer_start;
//
//  /* Calculate the pixel's byte offset inside the buffer */
//  uint32_t pixel_offset = (current_page * page_size) + x + (y * framebuffer_properties.pitch);
//
//  /* Draw each row of pixels */
//  for (int current_y = 0; current_y < height; current_y++)
//  {
//    /* Draw the pixel for each column */
//    for (int current_x = 0; current_x < width; current_x++)
//    {
//      //*((uint8_t*)(buffer_start + pixel_offset)) = color; // This is slower
//      *((uint8_t*)(buffer + pixel_offset)) = color;
//
//      /* Move to the next pixel */
//      pixel_offset++;
//    }
//
//    /* Move to the next row */
//    pixel_offset += framebuffer_properties.pitch - width;
//  }
//}

/* Helper function to draw a rectangle in given color */
static inline void fill_rect(int x, int y, int width, int height, int color)
{
  /* Calculate the byte offset of the top left */
  uint32_t pixel_offset = (current_page * page_size) + x + (y * framebuffer_properties.pitch);

  /* Draw each row of pixels */
  for (int current_y = 0; current_y < height; current_y++)
  {
    memset((void *)(buffer_start + pixel_offset), color, width);

    /* Move to the next row */
    pixel_offset += framebuffer_properties.pitch;
  }
}

/* Helper function to clear the entire screen in one color */
static void clear_screen(int color)
{
  memset((void *)(buffer_start + (current_page * page_size)), color, page_size);
}

/* This is the animation drawing function, if you compare with the original source you
 * might notice that all of the variable names of been updated to be more readable so
 * instead of DX we have direction_x for example. This doesn't make any difference to
 * the speed, size or memory use of the application because it is all removed by
 * GCC during the compile process but it does make it easier to read
 */
static void draw()
{
  char value[256];

  int frame;
  int x, y;
  int width, height;
  int direction_x, direction_y;

  uint64_t start_time;
  uint64_t complete_time;
  uint64_t time_difference;

  int element, fps, seconds;
  int offset_x, offset_y;

  /* Intialize the random number generator */
  random_seed(clock_get_count());

  /* Setup the rectangle dimensions, actually they are a square but you could set Width and
   * Height to be different. There are lots of values you can experiment with in this function 
   */
  width = framebuffer_properties.physicalwidth / 10;
  height = width;

  /* Setup the starting position of each box, the first part sets the X and Y coordinates and
   * the second part sets the direction and speed of the movement. Try changing the mod 10 to
   * a higher or lower value to see what happens
   */
  for (element = 0; element < NUM_ELEMENTS; element++)
  {
    element_x[element] = random_read_longint(RANDOM_MAX) % (framebuffer_properties.physicalwidth - width);
    element_y[element] = random_read_longint(RANDOM_MAX) % (framebuffer_properties.physicalheight - height);

    element_dir_x[element] = (random_read_longint(RANDOM_MAX) % 10) + 1;
    element_dir_y[element] = (random_read_longint(RANDOM_MAX) % 10) + 1;
  }

  /* Setup the frames and seconds, actually we are just setting the total number of frames to be
   * drawn but since we know if will draw 60 frames per second then we can confidently predict
   * how many seconds the animation will last
   */
  fps = 60;
  seconds = 60;

  /* Get the starting time in milliseconds ticks from the RTL GetTickCount64 function */
  start_time = get_tick_count64();

  /* Loop for the number of seconds times the number of frames per second */
  for (frame = 0; frame < (fps * seconds); frame++)
  {
    /* Change page to draw to (between 0 and 1), while page 0 is on screen we will draw
     * page 1 and while page 1 is on screen we will draw page 0. Doing it that way means
     * you don't see any sign of the drawing happening, it just looks like the boxes are
     * smoothly floating around the screen.
     * 
     * This variable determines the Y offset to pass to the framebuffer device and also
     * the offset from the start of our framebuffer memory
     */
    current_page = (current_page + 1) % 2;

    /* Clear the entire page to black so we can draw the boxes. It might look like the
     * boxes are moving but in actual fact we have to draw them completely for every
     * frame of the animation. No wonder we need to optimize our functions carefully
     */
    clear_screen(0);

    /* Draw each element (or box) on the current page. For each one there is an X and Y
    value that determines the current position, there is also a direction X and a
    direction Y which determines which direction the box is moving (Up/Down/Left/Right)
    and also how fast it is moving.
    
    The width and height of each box were set above to a static value, can you see 
    how you could make the boxes different sizes? */
    for (element = 0; element < NUM_ELEMENTS; element++)
    {
      /* Earlier we declared some arrays to store the position of each box and above
       * we setup the starting positions. On each iteration of the loop we need to
       * retrieve those values from the arrays so we can use them to draw the current
       * box
       */
      x = element_x[element];
      y = element_y[element];
      direction_x = element_dir_x[element];
      direction_y = element_dir_y[element];

      /* Draw the bouncing box, if you looked at the original code you might notice
       * that we have changed the value here for the Ultibo version. What would be
       * the result if you changed it back to 15 or even 63 instead?
       */
      fill_rect(x, y, width, height, (element % 127) + 1);

      /* We've drawn the box so move it ready for the next frame. This is simply a
       * matter of adding the direction X and Y values to the current position
       */
      x += direction_x;
      y += direction_y;

      /* Check for the left and right sides of the screen. We want our boxes to
       * 'bounce' whenever they hit the side of the screen and go the other way.
       *      
       * Here we check for the X position being either less than 0 which is the
       * left side of the screen or greater than the screen width minus the box
       * width which will be the right side of the screen.
       * 
       * If we reach either of those we invert the direction value so our box
       * moves in the opposite direction. Notice that the direction values are
       * signed integers so they an be either positive or negative
       */
      if (x < 0 || x > framebuffer_properties.physicalwidth - width)
      {
        direction_x = -direction_x; /* Reverse the direction by inverting the value */
        x += (2 * direction_x); /* Counteract the move we already did by adding double the new value */
      }

      /* Just like the sides we also check for the top and bottom of the screen */
      if (y < 0 || y > framebuffer_properties.physicalheight - height)
      {
        direction_y = -direction_y;
        y += (2 * direction_y);
      }

      /* Save the new position of the current box back to the arrays for the next frame */
      element_x[element] = x;
      element_y[element] = y;
      element_dir_x[element] = direction_x;
      element_dir_y[element] = direction_y;
    }

    /* After drawing our frame we need to make sure that all of our pixels have
     * actually been written back to memory by the CPU. 
     *
     * Since the Raspberry Pi uses both Level 1 and Level 2 caching in order to
     * improve the performance it may have only written our pixels to cache so 
     * far and not to memory.
     * 
     * Because the graphics processor (GPU) is separate from the CPU it cannot
     * see into the CPU cache so we need to clean the cache to make the CPU
     * write everything to memory. The framebuffer properties gives us a flag
     * to check that says if the memory is cached and if we need to do cleaning
     */
    if ((framebuffer_properties.flags & FRAMEBUFFER_FLAG_CACHED) != 0)
    {
      /* If the flag is set we call clean_data_cache_range() and pass the address and
      size of the current page. This is the fastest way to clean just the area that
      matters to us for the animation */
      clean_data_cache_range((size_t)buffer_start + (current_page * page_size), page_size);
    }

    /* Switch to the new page by setting the Y offset of the framebuffer device, this
     * will cause our new page to appear and then we can start all over again on the
     * other page
     */
    offset_x = 0;
    offset_y = current_page * framebuffer_properties.physicalheight;
    framebuffer_device_set_offset(framebuffer_device, offset_x, offset_y, TRUE);

    /* Because the actual video hardware only refreshes the screen 60 times per second
     * (or 60 FPS) then even though we have changed the Y offset above if we start
     * drawing on the next page immediately it may still be showing on screen.
     * 
     * This would produce a tearing effect of horizontal lines on the screen which
     * doesn't look good for our smooth animation.
     * 
     * In order to handle this we check the framebuffer properties to see if the
     * device supports waiting for vertical sync (the time between each frame)
     * before we proceed. If it doesn't support this option then we do the best we
     * can and wait for an approximate amount of time
     */
    if ((framebuffer_properties.flags & FRAMEBUFFER_FLAG_SYNC) != 0)
    {
      framebuffer_device_wait_sync(framebuffer_device);
    }
    else
    {
      microsecond_delay(1000000 / fps);
    }
  }

  /* Get the completion time in milliseconds ticks */
  complete_time = get_tick_count64();

  /* Work out the number of milliseconds between the start and end and display some information */
  time_difference = complete_time - start_time;
  sprintf(value, "Completed %u frames of %u elements in %us %ums", (unsigned int)fps * seconds, (unsigned int)NUM_ELEMENTS, (unsigned int)time_difference / 1000, (unsigned int)time_difference % 1000);
  console_write_ln(value);
  sprintf(value, "Frame rate %u frames per second", (unsigned int)((fps * seconds) / (time_difference / 1000)));
  console_write_ln(value);
}

int apimain(int argc, char **argv)
{
  /* This is the starting point of our program, first of all we need to do some setup */

  /* When doing animation we'd like to be sure the CPU is not too busy doing something else
   * to make time for our thread. Because the main thread will always be created on CPU0 and
   * on the Raspberry Pi we know that CPU0 is also reponsible for most of the interrupts in
   * the system then we'll ask the scheduler to move us to another CPU just so we have a 
   * little bit less to compete with
   */
  thread_set_cpu(thread_get_current(), CPU_ID_3);

  /* CPU migrations only happen during context switching so after setting our new CPU we
   * call thread_sleep() with any value and when we return we'll be running on CPU3
   */
  thread_sleep(0);

  /* Get the framebuffer device, we could use any device but most likely there is only
   * one available so we just ask for the default device
   */
  framebuffer_device = framebuffer_device_get_default();
  if (framebuffer_device)
  {
    /* Request the framebuffer properties which will tell us the size, depth and all
     * sorts of other information about the framebuffer device
     */
    framebuffer_device_get_properties(framebuffer_device, &framebuffer_properties);

    /* Release the current framebuffer so we can setup a new one with different settings */
    framebuffer_device_release(framebuffer_device);

    /* Wait for second to allow any messages generated by releasing the framebuffer to
     * propogate through the system. To do this properly we really should tell the console
     * not to attach to the framebuffer during boot, one of the many details needed when 
     * creating real world applications
     */
    thread_sleep(1000);

    /* Now we can adjust the framebuffer properties so that the color depth is 8 bits per
     * pixel and the virtual height is twice the physical height which will give us two
     * pages to draw our animation on. Again if we were doing this in a real application
     * it would be best to check the flags first to see if the framebuffer device even
     * supports virtual width and height
     */
    framebuffer_properties.depth = 8;

    /* The original source changes the width and height to 960 x 540 but with a little bit
     * of optimization there isn't any reason to do this. The animation works at any size
     * but you can try out the different values yourself for fun
     */
    //if (framebuffer_properties.physicalwidth < 960 || framebuffer_properties.physicalheight > 540)
    //{
    //  framebuffer_properties.physicalwidth = 960;
    //  framebuffer_properties.physicalheight = 540;
    //}

    framebuffer_properties.virtualwidth = framebuffer_properties.physicalwidth;
    framebuffer_properties.virtualheight = framebuffer_properties.physicalheight * 2;

    /* Pass the modified properties to the allocate function to allocate a new
     * framebuffer with our changes enabled. Checking the return of this function
     * would tell you if it was successful or not
     */
    framebuffer_device_allocate(framebuffer_device, &framebuffer_properties);

    /* Wait again just to be safe */
    thread_sleep(1000);

    /* Because we set 8 bit color for the framebuffer to do this example we also
     * need to set a palette. The framebuffer device or the driver might provide 
     * a default palette but the simplest option is to set the one we want.
     *
     * Here we pass a prebuilt structure that contains the VGA Mode 13h color
     * palette (or at least one version of it)
     */
    framebuffer_device_set_palette(framebuffer_device, &vga_palette);

    /* We need to get the framebuffer properties again because we want to know the
     * address of the framebuffer memory and also the length of each line in bytes
     * which is known as the pitch 
     */
    framebuffer_device_get_properties(framebuffer_device, &framebuffer_properties);

    /* From the properties work out the framebuffer variables */
    buffer_start = (void *)framebuffer_properties.address;
    page_size = framebuffer_properties.pitch * framebuffer_properties.physicalheight;
    current_page = 0;
  }

  /* Create a full screen console window (So we can output some information later) */
  console_window_create(console_device_get_default(), CONSOLE_POSITION_FULLSCREEN, TRUE);

  /* Go ahead and draw the animation */
  draw();

  /* Halt this thread when the drawing is done */
  thread_halt(0);
  
  return 0;
}
