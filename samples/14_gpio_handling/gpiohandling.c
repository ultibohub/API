/*
 *
 * GPIO Handling example project for Ultibo API
 * 
 * In this example we look at using the GPIO functions to detect a simple switch
 * being opened or closed and turn on or off an LED in response.
 *
 * To try this example you'll need the following:
 *
 * A switch connected between GPIO Pin 18 and Ground
 *
 * An LED and a 330 ohm resistor connected between GPIO Pin 16 and Ground
 *  (Ensure you connect the LED and resistor in series with each other and that
 *   the short leg or the flat side of the LED is connected to Ground)
 *
 * It's usually best to use a breadboard or breakout board to connect components
 * to the Pi just to avoid any accidental damage.
 *
 * The documentation below shows you where to find each of the pins.
 *
 * Raspberry Pi Models A+/B+/Zero/ZeroW/2B/3B/4B/400/Zero2W (40 pin header)
 *  https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#gpio
 *
 * Raspberry Pi Pinout (26 and 40 pin header)
 *  https://pinout.xyz/
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
#include "ultibo/gpio.h"

/* We add an extra function, see below for what it does */
static void gpio_pin_event(void *data, uint32_t pin, uint32_t trigger)
{
  char value[256];
  char pin_name[64], trigger_name[64];
  WINDOW_HANDLE *windowhandle = data;

  /* Print a message to show what the event was. You might notice that sometimes
   * multiple events occur when opening or closing the switch. This can be caused
   * by the contacts in the switch bouncing, see below for one way to handle this.
   * 
   * Notice that we get the window handle for our console window from the data 
   * parameter that was passed to gpio_input_event(). You can use this parameter
   * in any way you like in your application to pass values to the event handler
   */
  gpio_pin_to_string(pin, pin_name, sizeof(pin_name));
  gpio_trigger_to_string(trigger, trigger_name, sizeof(trigger_name));
  sprintf(value, "GPIO Pin Event on pin %s the event is %s", pin_name, trigger_name);
  console_window_write_ln(*windowhandle, value);
}

int apimain(int argc, char **argv)
{
  uint32_t last_value;
  uint32_t current_value;
  WINDOW_HANDLE windowhandle;

  /* Let's create a console window so we can report what is happening */
  windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);

  /* Display a welcome message */
  console_window_write_ln(windowhandle, "Welcome to Example 14 GPIO Handling");

  /* We'll use the GPIO functions in the platform header for this example, there are
   * also GPIO functions in the gpio header that allow you to specify some extra
   * parameters if you need them.
   *
   * We need to do some setup of the GPIO pins to tell the GPIO controller what we 
   * want to do with them.
   *
   * All of the GPIO_* values used below are available in the globalconst header
   */

  /* Set GPIO pin 18 which is our switch to Pull Up so that when the switch is open
   * the value read from the pin will be High
   */
  gpio_pull_select(GPIO_PIN_18, GPIO_PULL_UP);

  /* And make GPIO pin 18 an Input so we can detect the switch being opened or closed */
  gpio_function_select(GPIO_PIN_18, GPIO_FUNCTION_IN);

  /* Now set GPIO pin 16 to Pull None */
  gpio_pull_select(GPIO_PIN_16, GPIO_PULL_NONE);

  /* And make GPIO pin 16 an Output so we can turn the LED on or off */
  gpio_function_select(GPIO_PIN_16, GPIO_FUNCTION_OUT);

  /* Finally set the value of GPIO pin 16 to Low so the LED will be off */
  gpio_output_set(GPIO_PIN_16, GPIO_LEVEL_LOW);

  /* Let's read the current value of GPIO pin 18 so we know the position of the switch */
  last_value = gpio_input_get(GPIO_PIN_18);

  /* Start an endless loop checking the switch */
  while (true)
  {
    /* Read the value of the switch on GPIO pin 18 */
    current_value = gpio_input_get(GPIO_PIN_18);

    /* Compare the latest value with the old value */
    if (current_value != last_value)
    {
      /* Check if the switch is on 
       *
       * Notice that we check for Low to see if the switch is on, that's because we
       * connected the switch from GPIO pin 18 to Ground so the value will be Low when
       * the switch is closed and High when the switch is open
       */
      if (current_value == GPIO_LEVEL_LOW)
      {
        /* Display a message on the console */
        console_window_write_ln(windowhandle, "The switch is ON");

        /* Turn on the LED to match the switch */
        gpio_output_set(GPIO_PIN_16, GPIO_LEVEL_HIGH);
      }
      else
      {
        /* Display a message on the console */
        console_window_write_ln(windowhandle, "The switch is OFF");

        /* Turn off the LED when the switch is off */
        gpio_output_set(GPIO_PIN_16, GPIO_LEVEL_LOW);
      }

      /* Save the value of GPIO pin 18 for next time */
      last_value = current_value;
    }

    /* Instead of just looping over and over we can use the features of the GPIO controller
     * to tell us when the pin our switch is connected to has changed. That way our thread
     * does not consume any CPU time and other things can happen while we wait
     */

    /* There are two ways to wait for a GPIO pin to change, you can call gpio_input_wait() which
     * will cause the current thread to wait until the change occurs and then return.
     *
     * Alternatively we can use gpio_input_event() to register a function to be called when the
     * GPIO pin changes, this can be useful if you want your thread to be doing something else
     * instead of waiting.
     *
     * We'll do both here just to show what happens
     */
    
    /* First we check the value of the switch and decide what to wait for */
    if (current_value == GPIO_LEVEL_LOW)
    {
      /* The switch is currently closed (value is Low) so we wait for it to change to High */

      /* Let's register an event to call when the pin changes to High.
       *
       * The GPIO_TRIGGER_HIGH parameter tells the GPIO driver what change to wait for.
       * 
       * You can also pass a data parameter to the event, this can be anything you want
       * and is not used by the GPIO driver. For example you could use the same function
       * for multiple different events and use the data to detect which one occurred.
       * 
       * In this example we'll pass our console window handle, to see why have a look at
       * the gpio_pin_event() function above
       */
      gpio_input_event(GPIO_PIN_18, GPIO_TRIGGER_HIGH, INFINITE, gpio_pin_event, &windowhandle);

      /* And make the current thread wait for the change as well.
       *
       * The INFINITE parameter tells the driver to wait forever
       */
      gpio_input_wait(GPIO_PIN_18, GPIO_TRIGGER_HIGH, INFINITE);

      /* The thread will return here when the GPIO pin changes to High but sometimes switches
       * do not change from open to closed cleanly and the contacts may "bounce" and cause a
       * false change to occur. To stop this we add a little sleep here to give the switch time
       * to settle before checking for the new state, this is called "debouncing"
       */
      thread_sleep(10);
    }
    else
    {
      /* The value is High so the switch must be open, wait for it to change to Low */

      /* The same as above but in reverse, register an event for when the pin changes to Low */
      gpio_input_event(GPIO_PIN_18, GPIO_TRIGGER_LOW, INFINITE, gpio_pin_event, &windowhandle);

      /* And wait as well for the change to Low */
      gpio_input_wait(GPIO_PIN_18, GPIO_TRIGGER_LOW, INFINITE);

      /* Add our sleep for debouncing */
      thread_sleep(10);
    }
  }

  /* Halt the main thread if we ever get to here */
  thread_halt(0);

  return 0;
}
