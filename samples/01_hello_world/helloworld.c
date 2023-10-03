/*
 *
 * Hello World sample project for Ultibo API
 *
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

#include "ultibo/console.h"
 
int apimain(int argc, char **argv)
{
 /* Declare a variable to hold a console window handle */
 HANDLE window_handle;
 
 /* First we create a console window to write our text on, we make it the full
  * size of the screen by specifying CONSOLE_POSITION_FULL and allow it to be the
  * default window by passing TRUE as the last parameter. */ 
 window_handle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);

 /* Next write some text on our newly created console window, we pass the handle
  * of the console window created above to tell it where to write the text since
  * there can be multiple console windows on screen at once.

  * This will appear in the top left corner of the screen in the default color
  * and font. Notice that we don't need to put \n on the end of the string because
  * console_window_write_ln() adds the end of line for us. */ 
 console_window_write_ln(window_handle, "Hello Ultibo!");

 /* There are multiple ways to achieve the same thing, because we allowed our console
  * window to be the default and we know there are no other windows present, we could
  * simply call console_write_ln() or even printf() instead and the text would appear
  * on the default console window. Try them out if you want to experiment. */
 
 /* Because Ultibo is always multi threaded, we should never allow the code to exit
  * from the main function of the program. See the Wiki for more information on
  * why but unless you are sure of what will happen it is best to simply halt the
  * thread here which you can do by calling thread_halt(), for this example the
  * consoleproject wrapper already calls ThreadHalt when we return. */
 
 return 0;
}
