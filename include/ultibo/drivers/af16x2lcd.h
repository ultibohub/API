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
#ifndef _ULTIBO_AF16X2LCD_H
#define _ULTIBO_AF16X2LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"
#include "ultibo/console.h"

/** AF16x2LCD specific constants */
#define AF16X2LCD_CONSOLE_DESCRIPTION	"Adafruit 16x2 LCD" ///< Description of AF16x2LCD device

#define AF16X2LCD_SIGNATURE	0x000AF162

#define AF16X2LCD_MODEL_MONO	0 ///< LCD with Monochrome backlight
#define AF16X2LCD_MODEL_RGB	1 ///< LCD with RGB backlight

/** AF16x2LCD GPIO constants */
#define AF16X2LCD_PLATE_RS	GPIO_PIN_15 ///< GPIO pin for the LCD RS line
#define AF16X2LCD_PLATE_RW	GPIO_PIN_14 ///< GPIO pin for the LCD RW line
#define AF16X2LCD_PLATE_EN	GPIO_PIN_13 ///< GPIO pin for the LCD EN line
#define AF16X2LCD_PLATE_D4	GPIO_PIN_12 ///< GPIO pin for the LCD D4 line
#define AF16X2LCD_PLATE_D5	GPIO_PIN_11 ///< GPIO pin for the LCD D5 line
#define AF16X2LCD_PLATE_D6	GPIO_PIN_10 ///< GPIO pin for the LCD D6 line
#define AF16X2LCD_PLATE_D7	GPIO_PIN_9 ///< GPIO pin for the LCD D7 line
#define AF16X2LCD_PLATE_RED	GPIO_PIN_6 ///< GPIO pin for the Backlight Red LED
#define AF16X2LCD_PLATE_GREEN	GPIO_PIN_7 ///< GPIO pin for the Backlight Green LED
#define AF16X2LCD_PLATE_BLUE	GPIO_PIN_8 ///< GPIO pin for the Backlight Blue LED

#define AF16X2LCD_BUTTON_SELECT	GPIO_PIN_0 ///< GPIO pin for the Select button
#define AF16X2LCD_BUTTON_RIGHT	GPIO_PIN_1 ///< GPIO pin for the Right button
#define AF16X2LCD_BUTTON_DOWN	GPIO_PIN_2 ///< GPIO pin for the Down button
#define AF16X2LCD_BUTTON_UP	GPIO_PIN_3 ///< GPIO pin for the Up button
#define AF16X2LCD_BUTTON_LEFT	GPIO_PIN_4 ///< GPIO pin for the Left button

/** AF16x2LCD specific types */
typedef struct _AF16X2LCD_PLATE AF16X2LCD_PLATE;
struct _AF16X2LCD_PLATE
{
	uint32_t signature; ///< Signature for entry validation
	uint32_t model; ///< Plate model (eg AF16X2LCD_MODEL_MONO)
	LONGBOOL invert; ///< Invert polarity of Backlight (Active low if True)
	I2C_DEVICE *i2c; ///< I2C device for this plate
	GPIO_DEVICE *gpio; ///< GPIO (MCP23017) device for this plate
	CONSOLE_DEVICE *console; ///< Console (HD44780) device for this plate
};


/** AF16x2LCD Functions */

/**
 * @brief Start the AF16x2LCD driver and register the GPIO and Console devices associated with the display
 * @param Model The Adafruit 16x2 LCD Plate model (eg AF16X2LCD_MODEL_RGB)
 * @param Invert Invert the signal level for the LCD backlight (If True then GPIO_LEVEL_LOW equals On)
 * @param Device The I2C device that the MCP23017 I/O Expander on the LCD Plate is connected to
 * @param Address The I2C address of the MCP23017 I/O Expander on the LCD Plate
 * @return The handle of the AF16x2LCD on success or INVALID_HANDLE_VALUE on failure
 * @note This function will be called during startup if the parameter AF16X2LCD_AUTOSTART is True
 *        Can be called multiple times to support more than one 16x2 LCD display
 */
HANDLE STDCALL af16x2lcd_start(uint32_t model, BOOL invert, char *device, uint16_t address);

/**
 * @brief Stop the AF16x2LCD driver and deregister the GPIO and Console devices associated with the display
 * @param Handle The handle of the AF16x2LCD or INVALID_HANDLE_VALUE for the default display
 * @return True if completed or False on failure
 */
BOOL STDCALL af16x2lcd_stop(HANDLE handle);

/**
 * @brief Get the GPIO level of a button on the AF16x2LCD display
 * @param Handle The handle of the AF16x2LCD or INVALID_HANDLE_VALUE for the default display
 * @param Button The button to get the level for (eg AF16X2LCD_BUTTON_LEFT)
 * @return The GPIO level of the button (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure
 */
uint32_t STDCALL af16x2lcd_get_button(HANDLE handle, uint32_t button);

/**
 * @brief Turn on the backlight on the AF16x2LCD display
 * @param Handle The handle of the AF16x2LCD or INVALID_HANDLE_VALUE for the default display
 * @return True if completed or False on failure
 */
BOOL STDCALL af16x2lcd_backlight_on(HANDLE handle);

/**
 * @brief Turn off the backlight on the AF16x2LCD display
 * @param Handle The handle of the AF16x2LCD or INVALID_HANDLE_VALUE for the default display
 * @return True if completed or False on failure
 */
BOOL STDCALL af16x2lcd_backlight_off(HANDLE handle);

/**
 * @brief Set the backlight color on the AF16x2LCD display
 * @param Handle The handle of the AF16x2LCD or INVALID_HANDLE_VALUE for the default display
 * @param Red The Red value (0 for Off / 1 for On)
 * @param Green The Green value (0 for Off / 1 for On)
 * @param Blue The Blue value (0 for Off / 1 for On)
 * @return True if completed or False on failure
 */
BOOL STDCALL af16x2lcd_backlight_color(HANDLE handle, uint8_t red, uint8_t green, uint8_t blue);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_AF16X2LCD_H
