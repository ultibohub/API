/*
 *
 * PWM Control example project for Ultibo API
 * 
 * This example demonstrates using the PWM devices in Ultibo to control two
 * LEDs. The PWM outputs are alternated so that the LEDs start off and gradually
 * increase in brightness until they are fully on, the cycle then reverses so
 * that the LEDs gradually decrease in brightness until they are off.
 *
 * To make it even more interesting the LEDs are opposite to each other so when
 * one is increasing in brightness the other is decreasing.
 *
 * To try this example you'll need the following:
 *
 * An LED and a 330 ohm resistor connected between GPIO Pin 18 and Ground
 *  (Ensure you connect the LED and resistor in series with each other and that
 *   the short leg or the flat side of the LED is connected to Ground)
 *
 * An LED and a 330 ohm resistor connected between GPIO Pin 19 and Ground
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
 * We've also included a diagram that shows the connections, look at the file
 * PWM Example.png in the same folder as this example.
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
#include "ultibo/pwm.h"

int apimain(int argc, char **argv)
{
  int count;
  char pwm0_desc[256];
  char pwm1_desc[256];

  WINDOW_HANDLE handle;

  PWM_DEVICE *pwm0_device;
  PWM_DEVICE *pwm1_device;

  /* Create a console window and display a welcome message */
  handle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);
  console_window_write_ln(handle, "Welcome to Example 18 PWM Control");

  /* First locate the PWM devices
   *
   * The Raspberry Pi has two PWM channels which will normally end up with the names
   * PWM0 and PWM1 when the driver is included in an application.
   *
   * You could use pwm_device_find_by_name() here and simply request PWM0 and PWM1 but
   * that could fail if for any reason one of the devices has been disabled.
   * 
   * The better option is to use pwm_device_find_by_description() and pass the result of
   * the pwm_get_description() which will determine the correct device description for 
   * the current board model and always find the correct device regardless of the specific
   * configuration details.
   *
   */
  
  /* Get the PWM device descriptions */
  pwm_get_description(0, 0, pwm0_desc, sizeof(pwm0_desc));
  pwm_get_description(1, 0, pwm1_desc, sizeof(pwm1_desc));

  /* Find the PWM devices */
  pwm0_device = pwm_device_find_by_description(pwm0_desc);
  pwm1_device = pwm_device_find_by_description(pwm1_desc);
  if (pwm0_device && pwm1_device)
  {
    /* This example uses the default GPIO pin values which are GPIO_PIN_18 for PWM0
     * and GPIO_PIN_19 for PWM1. If you need to use one of the alternate GPIO pins
     * then you can call pwm_device_set_gpio() with the required pin number. 
     *
     * You can also use pwm_device_get_gpio() to find out the currently configured pin
     */

    /* On the Raspberry Pi the PWM setup requires 3 values. 
     *
     * The first is the Mode which can be PWM_MODE_MARKSPACE, PWM_MODE_BALANCED or 
     * PWM_MODE_SERIALIZED. These are described in detail in the BCM2835 ARM Peripherals
     * documentation which can be found via the resources page on the Ultibo wiki.
     *
     * The second value is the Frequency which controls the frequency of the clock
     * used by the PWM device. On the Raspberry Pi both PWM devices share a common
     * clock so changing the frequency on one device also changes it on the other.
     *
     * The final setup value is the Range, the exact meaning of the range value varies
     * depending on the mode selected but in general it represents the time period of
     * one full cycle of the waveform output by the device.
     *
     * The range and the data define what is actually output onto the GPIO pin, as an
     * alternative to setting them individually you can call pwm_device_configure()
     * which allows you to specify both a Range and a Duty cycle in nanoseconds.
     *
     * Try experimenting with the range and data values to see how they affect the LEDs
     */

    /* Setup PWM device 0 */
    /* Set the range to 1000 */
    pwm_device_set_range(pwm0_device, 1000);
    /* And the mode to PWM_MODE_MARKSPACE */
    pwm_device_set_mode(pwm0_device, PWM_MODE_MARKSPACE);
    /* Finally set the frequency to 9.6MHz */
    pwm_device_set_frequency(pwm0_device, 9600000);

    /* Setup PWM device 1 */
    /* Use exactly the same settings as PWM0 */
    pwm_device_set_range(pwm1_device, 1000);
    pwm_device_set_mode(pwm1_device, PWM_MODE_MARKSPACE);
    pwm_device_set_frequency(pwm1_device, 9600000);

    /* Start the PWM devices
     *
     * This will start the clock and enable the devices, the final step to
     * output something is to write some actual data which will specify how
     * many pulses are output within the time period defined by the range.
     *
     * A data value of 0 will turn off the output whereas a data value equal 
     * to the range will mean the output is always on (pulses are continuous).
     * We can use this to make our LED go from fully off to fully on in gradual
     * steps, the time it takes to make this transition is simply controlled by
     * the value passed to thread_sleep()
     */
    if ((pwm_device_start(pwm0_device) == ERROR_SUCCESS) && (pwm_device_start(pwm1_device) == ERROR_SUCCESS))
    {
      /* Start an endless loop writing data values to the PWM devices */
      while (true)
      {
        /* Cycle the devices through the entire range from 0 to 1000.
         *
         * The PWM0 device goes upwards (from off to full brightness)
         * and the PWM1 device goes down (from full brightness to off)
         */
        for (count = 0; count <= 1000; count++)
        {
          pwm_device_write(pwm0_device, count);
          pwm_device_write(pwm1_device, 1000 - count);

          thread_sleep(1);
        }

        /* Reverse the directions from above so PWM0 starts at full and
         * PWM1 starts at off, then repeat from the beginning
         */
        for (count = 0; count <= 1000; count++)
        {
          pwm_device_write(pwm0_device, 1000 - count);
          pwm_device_write(pwm1_device, count);

          thread_sleep(1);
        }
      }

      /* Stop the PWM devices
       * 
       * This will disable the devices and stop the clock, remember that the
       * clock is shared between both devices so the driver will only actually
       * stop the clock when pwm_device_stop() is called for both of them
       */
      pwm_device_stop(pwm0_device);
      pwm_device_stop(pwm1_device);
    }
    else
    {
      console_window_write_ln(handle, "Error: Failed to start PWM devices 0 and 1");
    }
  }
  else
  {
    console_window_write_ln(handle, "Error: Failed to locate PWM devices 0 and 1");
  }

  /* Halt the thread if we return */
  thread_halt(0);
  
  return 0;
}
