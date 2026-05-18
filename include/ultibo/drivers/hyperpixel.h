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
#ifndef _ULTIBO_HYPERPIXEL_H
#define _ULTIBO_HYPERPIXEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"

/** HyperPixel specific constants */
/** HyperPixel model constants */
#define HYPERPIXEL40_RECTANGLE	0
#define HYPERPIXEL40_SQUARE	1
#define HYPERPIXEL40_SQUARE2021	2
#define HYPERPIXEL21_ROUND	3

/** HyperPixel GPIO pins (All Models) */
#define HYPERPIXEL_GPIO_PIN_FUNCTION	GPIO_FUNCTION_ALT2
#define HYPERPIXEL_GPIO_PIN_PULL	GPIO_PULL_NONE
#define HYPERPIXEL_GPIO_PIN_COUNT	22
static const uint32_t HYPERPIXEL_GPIO_PINS[HYPERPIXEL_GPIO_PIN_COUNT] = {
 GPIO_PIN_0,
 GPIO_PIN_1,
 GPIO_PIN_2,
 GPIO_PIN_3,
 GPIO_PIN_4,
 GPIO_PIN_5,
 GPIO_PIN_6,
 GPIO_PIN_7,
 GPIO_PIN_8,
 GPIO_PIN_9,

 GPIO_PIN_12,
 GPIO_PIN_13,
 GPIO_PIN_14,
 GPIO_PIN_15,
 GPIO_PIN_16,
 GPIO_PIN_17,

 GPIO_PIN_20,
 GPIO_PIN_21,
 GPIO_PIN_22,
 GPIO_PIN_23,
 GPIO_PIN_24,
 GPIO_PIN_25};

/** HyperPixel SPI pins (All Models) */
#define HYPERPIXEL_SPI_FUNCTION	GPIO_FUNCTION_OUT
#define HYPERPIXEL_SPI_PULL	GPIO_PULL_NONE
#define HYPERPIXEL_SPI_CLK	GPIO_PIN_27
#define HYPERPIXEL_SPI_MOSI	GPIO_PIN_26
#define HYPERPIXEL_SPI_CS	GPIO_PIN_18
#define HYPERPIXEL_SPI_DELAY	100 ///< Clock pulse time in microseconds
#define HYPERPIXEL_SPI_WAIT	120 ///< Wait time in milliseconds before display on

#define HYPERPIXEL_SPI_CLK_ALT	GPIO_PIN_11 ///< CLK Pin (Round model)
#define HYPERPIXEL_SPI_MOSI_ALT	GPIO_PIN_10 ///< MOSI Pin (Round model)

#define HYPERPIXEL_SPI_DELAY_ALT	10 ///< Clock pulse time in microseconds (Rectangle model)
#define HYPERPIXEL_SPI_WAIT_ALT	200 ///< Wait time in milliseconds before display on (Rectangle model)

/** HyperPixel Touch I2C pins (All Models) */
#define HYPERPIXEL_I2C_SDA	GPIO_PIN_10
#define HYPERPIXEL_I2C_SCL	GPIO_PIN_11
#define HYPERPIXEL_I2C_DELAY	4

/** HyperPixel Backlight pins (All Models) */
#define HYPERPIXEL_BACKLIGHT_FUNCTION	GPIO_FUNCTION_OUT
#define HYPERPIXEL_BACKLIGHT_PULL	GPIO_PULL_NONE
#define HYPERPIXEL_BACKLIGHT_PIN	GPIO_PIN_19

/** HyperPixel Touch interrupt pins (All Models) */
#define HYPERPIXEL_TOUCH_INTERRUPT_TRIGGER	GPIO_TRIGGER_FALLING
#define HYPERPIXEL_TOUCH_INTERRUPT_FUNCTION	GPIO_FUNCTION_IN
#define HYPERPIXEL_TOUCH_INTERRUPT_PULL	GPIO_PULL_UP
#define HYPERPIXEL_TOUCH_INTERRUPT_PIN	GPIO_PIN_27

/** HyperPixel specific types */
/** Software SPI Data */
typedef struct _HYPERPIXEL_DATA HYPERPIXEL_DATA;
struct _HYPERPIXEL_DATA
{
	GPIO_DEVICE *device; ///< The GPIO device to use
	uint32_t fsel; ///< The GPIO function select value
	uint32_t pull; ///< The GPIO pull select value
	uint32_t clk; ///< The CLK pin for software SPI
	uint32_t mosi; ///< The MOSI pin for software SPI
	uint32_t cs; ///< The CS pin for software SPI
	uint32_t wait; ///< Wait time in milliseconds before display on
	uint32_t delay; ///< Clock delay time in microseconds
};

/** HyperPixel Functions */
uint32_t STDCALL hyperpixel_initialize(uint32_t model);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_HYPERPIXEL_H
