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
#ifndef _ULTIBO_STMPE_H
#define _ULTIBO_STMPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/gpio.h"
#include "ultibo/i2c.h"
#include "ultibo/spi.h"
#include "ultibo/touch.h"

/* ============================================================================== */
/* STMPE specific constants */
#define STMPE610_GPIO_DESCRIPTION	"STMicroelectronics STMPE610 I/O Expander" // Description of STMPE610 GPIO device
#define STMPE801_GPIO_DESCRIPTION	"STMicroelectronics STMPE801 I/O Expander" // Description of STMPE801 GPIO device
#define STMPE811_GPIO_DESCRIPTION	"STMicroelectronics STMPE811 I/O Expander" // Description of STMPE811 GPIO device
#define STMPE1601_GPIO_DESCRIPTION	"STMicroelectronics STMPE1601 I/O Expander" // Description of STMPE1601 GPIO device
#define STMPE1801_GPIO_DESCRIPTION	"STMicroelectronics STMPE1801 I/O Expander" // Description of STMPE1801 GPIO device
#define STMPE2401_GPIO_DESCRIPTION	"STMicroelectronics STMPE2401 I/O Expander" // Description of STMPE2401 GPIO device
#define STMPE2403_GPIO_DESCRIPTION	"STMicroelectronics STMPE2403 I/O Expander" // Description of STMPE2403 GPIO device

#define STMPE610_TOUCH_DESCRIPTION	"STMicroelectronics STMPE610 Touch Controller" // Description of STMPE610 Touch device
#define STMPE811_TOUCH_DESCRIPTION	"STMicroelectronics STMPE811 Touch Controller" // Description of STMPE811 Touch device

#define STMPE610_GPIO_MIN_PIN	GPIO_PIN_2
#define STMPE610_GPIO_MAX_PIN	GPIO_PIN_7
#define STMPE610_GPIO_PIN_COUNT	6

#define STMPE801_GPIO_MIN_PIN	GPIO_PIN_0
#define STMPE801_GPIO_MAX_PIN	GPIO_PIN_7
#define STMPE801_GPIO_PIN_COUNT	8

#define STMPE811_GPIO_MIN_PIN	GPIO_PIN_0
#define STMPE811_GPIO_MAX_PIN	GPIO_PIN_7
#define STMPE811_GPIO_PIN_COUNT	8

#define STMPE1601_GPIO_MIN_PIN	GPIO_PIN_0
#define STMPE1601_GPIO_MAX_PIN	GPIO_PIN_15
#define STMPE1601_GPIO_PIN_COUNT	16

#define STMPE1801_GPIO_MIN_PIN	GPIO_PIN_0
#define STMPE1801_GPIO_MAX_PIN	GPIO_PIN_17
#define STMPE1801_GPIO_PIN_COUNT	18

#define STMPE240X_GPIO_MIN_PIN	GPIO_PIN_0
#define STMPE240X_GPIO_MAX_PIN	GPIO_PIN_23
#define STMPE240X_GPIO_PIN_COUNT	24

#define STMPE_GPIO_MAX_LEVEL	GPIO_LEVEL_HIGH

#define STMPE_GPIO_MAX_PULL	GPIO_PULL_DOWN

#define STMPE610_GPIO_MIN_FUNCTION	GPIO_FUNCTION_IN
#define STMPE610_GPIO_MAX_FUNCTION	GPIO_FUNCTION_ALT0
#define STMPE610_GPIO_FUNCTION_COUNT	3

#define STMPE801_GPIO_MIN_FUNCTION	GPIO_FUNCTION_IN
#define STMPE801_GPIO_MAX_FUNCTION	GPIO_FUNCTION_OUT
#define STMPE801_GPIO_FUNCTION_COUNT	2

#define STMPE811_GPIO_MIN_FUNCTION	GPIO_FUNCTION_IN
#define STMPE811_GPIO_MAX_FUNCTION	GPIO_FUNCTION_ALT0
#define STMPE811_GPIO_FUNCTION_COUNT	3

#define STMPE1601_GPIO_MIN_FUNCTION	GPIO_FUNCTION_IN
#define STMPE1601_GPIO_MAX_FUNCTION	GPIO_FUNCTION_ALT1 // Alternate function 0 = Keypad / Alternate function 1 = PWM
#define STMPE1601_GPIO_FUNCTION_COUNT	4

#define STMPE1801_GPIO_MIN_FUNCTION	GPIO_FUNCTION_IN
#define STMPE1801_GPIO_MAX_FUNCTION	GPIO_FUNCTION_ALT0
#define STMPE1801_GPIO_FUNCTION_COUNT	3

#define STMPE240X_GPIO_MIN_FUNCTION	GPIO_FUNCTION_IN
#define STMPE240X_GPIO_MAX_FUNCTION	GPIO_FUNCTION_ALT2
#define STMPE240X_GPIO_FUNCTION_COUNT	5

#define STMPE610_MAX_POINTS	1
#define STMPE610_MAX_X	0xFFF
#define STMPE610_MAX_Y	0xFFF
#define STMPE610_MAX_Z	0xFF

#define STMPE811_MAX_POINTS	1
#define STMPE811_MAX_X	0xFFF
#define STMPE811_MAX_Y	0xFFF
#define STMPE811_MAX_Z	0xFF

/* STMPE Chip constants */
#define STMPE_CHIP_STMPE610	1
#define STMPE_CHIP_STMPE801	2
#define STMPE_CHIP_STMPE811	3
#define STMPE_CHIP_STMPE1601	4
#define STMPE_CHIP_STMPE1801	5
#define STMPE_CHIP_STMPE2401	6
#define STMPE_CHIP_STMPE2403	7

/* STMPE Direction constants */
#define STMPE_DIR_ASCENDING	0 // Register addresses in ascending order (Bits go from LSB to MSB)
#define STMPE_DIR_DESCENDING	1 // Register addresses in descending order (Bits go from MSB to LSB)

/* STMPE I2C constants */
#define STMPE_I2C_RATE	400000 // Default I2C clock rate (Device supports 100KHz and 400KHz)

/* STMPE SPI constants */
#define STMPE_SPI_RATE	500000 // Default SPI clock rate (Device supports up to 1MHz)

#define STMPE_SPI_READ_CMD	(1 << 7) // First bit of address must be set for a read

/* STMPE Register constants */
/* STMPE610 / STMPE811 */
#define STMPE811_REG_CHIP_ID	0x00 // Device identification
#define STMPE811_REG_ID_VER	0x02 // Revision number (0x01 for engineering sample / 0x03 for final silicon)
#define STMPE811_REG_SYS_CTRL1	0x03 // Reset control
#define STMPE811_REG_SYS_CTRL2	0x04 // Clock control
#define STMPE811_REG_SPI_CFG	0x08 // SPI interface configuration
#define STMPE811_REG_INT_CTRL	0x09 // Interrupt control register
#define STMPE811_REG_INT_EN	0x0A // Interrupt enable register
#define STMPE811_REG_INT_STA	0x0B // Interrupt status register

#define STMPE811_REG_GPIO_INT_EN	0x0C // GPIO interrupt enable register
#define STMPE811_REG_GPIO_INT_STA	0x0D // GPIO interrupt status register
#define STMPE811_REG_ADC_INT_EN	0x0E // ADC interrupt enable register
#define STMPE811_REG_ADC_INT_STA	0x0F // ADC interrupt status register
#define STMPE811_REG_GPIO_SET_PIN	0x10 // GPIO set pin register
#define STMPE811_REG_GPIO_CLR_PIN	0x11 // GPIO clear pin register
#define STMPE811_REG_GPIO_MP_STA	0x12 // GPIO monitor pin state register
#define STMPE811_REG_GPIO_SET_DIR	0x13 // GPIO direction register
#define STMPE811_REG_GPIO_ED	0x14 // GPIO edge detect register
#define STMPE811_REG_GPIO_RE	0x15 // GPIO rising edge register
#define STMPE811_REG_GPIO_FE	0x16 // GPIO falling edge register
#define STMPE811_REG_GPIO_AF	0x17 // Alternate function register

#define STMPE811_REG_ADC_CTRL1	0x20 // ADC control
#define STMPE811_REG_ADC_CTRL2	0x21 // ADC control
#define STMPE811_REG_ADC_CAPT	0x22 // To initiate ADC data acquisition
#define STMPE811_REG_ADC_DATA_CH0	0x30 // ADC channel 0
#define STMPE811_REG_ADC_DATA_CH1	0x32 // ADC channel 1
#define STMPE811_REG_ADC_DATA_CH2	0x34 // ADC channel 2
#define STMPE811_REG_ADC_DATA_CH3	0x36 // ADC channel 3
#define STMPE811_REG_ADC_DATA_CH4	0x38 // ADC channel 4
#define STMPE811_REG_ADC_DATA_CH5	0x3A // ADC channel 5
#define STMPE811_REG_ADC_DATA_CH6	0x3C // ADC channel 6
#define STMPE811_REG_ADC_DATA_CH7	0x3E // ADC channel 7

#define STMPE811_REG_TSC_CTRL	0x40 // 4-wire touchscreen controller setup
#define STMPE811_REG_TSC_CFG	0x41 // Touchscreen controller configuration
#define STMPE811_REG_WDW_TR_X	0x42 // Window setup for top right X
#define STMPE811_REG_WDW_TR_Y	0x44 // Window setup for top right Y
#define STMPE811_REG_WDW_BL_X	0x46 // Window setup for bottom left X
#define STMPE811_REG_WDW_BL_Y	0x48 // Window setup for bottom left Y
#define STMPE811_REG_FIFO_TH	0x4A // FIFO level to generate interrupt
#define STMPE811_REG_FIFO_STA	0x4B // Current status of FIFO
#define STMPE811_REG_FIFO_SIZE	0x4C // Current filled level of FIFO
#define STMPE811_REG_TSC_DATA_X	0x4D // Data port for touchscreen controller data access
#define STMPE811_REG_TSC_DATA_Y	0x4F // Data port for touchscreen controller data access
#define STMPE811_REG_TSC_DATA_Z	0x51 // Data port for touchscreen controller data access
#define STMPE811_REG_TSC_DATA_XYZ	0x52 // Data port for touchscreen controller data access
#define STMPE811_REG_TSC_FRACTION_Z	0x56 // Touchscreen controller FRACTION_Z
#define STMPE811_REG_TSC_DATA	0x57 // Data port for touchscreen controller data access
#define STMPE811_REG_TSC_I_DRIVE	0x58 // Touchscreen controller drive I
#define STMPE811_REG_TSC_SHIELD	0x59 // Touchscreen controller shield
/* STMPE811 */
#define STMPE811_REG_TEMP_CTRL	0x60 // Temperature sensor setup
#define STMPE811_REG_TEMP_DATA	0x61 // Temperature data access port
#define STMPE811_REG_TEMP_TH	0x62 // Threshold for temperature controlled interrupt

#define STMPE811_REG_MAX	0x62
#define STMPE811_REG_SIZE	1

/* STMPE801 */
#define STMPE801_REG_CHIP_ID	0x00 // Device identification
#define STMPE801_REG_ID_VER	0x02 // Revision number (0x01 for engineering sample / 0x02 for final silicon)
#define STMPE801_REG_SYS_CTRL	0x04 // Reset and interrupt control
#define STMPE801_REG_GPIO_INT_EN	0x08 // GPIO interrupt enable register
#define STMPE801_REG_GPIO_INT_STA	0x09 // GPIO interrupt status register
#define STMPE801_REG_GPIO_MP_STA	0x10 // GPIO monitor pin state register
#define STMPE801_REG_GPIO_SET_PIN	0x11 // GPIO set pin state register
#define STMPE801_REG_GPIO_SET_DIR	0x12 // GPIO set pin direction register

#define STMPE801_REG_MAX	0x12
#define STMPE801_REG_SIZE	1

/* STMPE1601 */
#define STMPE1601_REG_CHIP_ID	0x80 // Device identification
#define STMPE1601_REG_ID_VER	0x81 // Revision number

#define STMPE1601_REG_SYS_CTRL	0x02 // System control register
#define STMPE1601_REG_SYS_CTRL2	0x03 // System control register 2
#define STMPE1601_REG_INT_CTRL_MSB	0x10 // Interrupt control register
#define STMPE1601_REG_INT_CTRL_LSB	0x11
#define STMPE1601_REG_INT_EN_MSB	0x12 // Interrupt enable mask register
#define STMPE1601_REG_INT_EN_LSB	0x13
#define STMPE1601_REG_INT_STA_MSB	0x14 // Interrupt status register
#define STMPE1601_REG_INT_STA_LSB	0x15

#define STMPE1601_REG_GPIO_INT_EN_MSB	0x16 // Interrupt enable GPIO mask register
#define STMPE1601_REG_GPIO_INT_EN_LSB	0x17
#define STMPE1601_REG_GPIO_INT_STA_MSB	0x18 // Interrupt status GPIO register
#define STMPE1601_REG_GPIO_INT_STA_LSB	0x19

#define STMPE1601_REG_GPIO_SET_PIN_MSB	0x82 // GPIO set pin state register
#define STMPE1601_REG_GPIO_SET_PIN_LSB	0x83
#define STMPE1601_REG_GPIO_CLR_PIN_MSB	0x84 // GPIO clear pin state register
#define STMPE1601_REG_GPIO_CLR_PIN_LSB	0x85
#define STMPE1601_REG_GPIO_MP_STA_MSB	0x86 // GPIO monitor pin state register
#define STMPE1601_REG_GPIO_MP_STA_LSB	0x87
#define STMPE1601_REG_GPIO_SET_DIR_MSB	0x88 // GPIO set pin direction register
#define STMPE1601_REG_GPIO_SET_DIR_LSB	0x89

#define STMPE1601_REG_GPIO_ED_MSB	0x8A // GPIO edge detect status register
#define STMPE1601_REG_GPIO_ED_LSB	0x8B
#define STMPE1601_REG_GPIO_RE_MSB	0x8C // GPIO rising edge register
#define STMPE1601_REG_GPIO_RE_LSB	0x8D
#define STMPE1601_REG_GPIO_FE_MSB	0x8E // GPIO falling edge register
#define STMPE1601_REG_GPIO_FE_LSB	0x8F
#define STMPE1601_REG_GPIO_PU_MSB	0x90 // GPIO pull up register
#define STMPE1601_REG_GPIO_PU_LSB	0x91
#define STMPE1601_REG_GPIO_AF_U_MSB	0x92 // GPIO alternate function register (upper word)
#define STMPE1601_REG_GPIO_AF_U_LSB	0x93
#define STMPE1601_REG_GPIO_AF_L_MSB	0x94 // GPIO alternate function register (lower word)
#define STMPE1601_REG_GPIO_AF_L_LSB	0x95

#define STMPE1601_REG_GPIO_LT_EN	0x96 // GPIO level translator enable
#define STMPE1601_REG_GPIO_LT_DIR	0x97 // GPIO level translator direction

#define STMPE1601_REG_MAX	0xBF
#define STMPE1601_REG_SIZE	2

/* STMPE1801 */
#define STMPE1801_REG_CHIP_ID	0x00 // Device identification
#define STMPE1801_REG_ID_VER	0x01 // Revision number

#define STMPE1801_REG_SYS_CTRL	0x02 // System control
#define STMPE1801_REG_INT_CTRL_LOW	0x04 // Interrupt control
#define STMPE1801_REG_INT_CTRL_HIGH	0x05
#define STMPE1801_REG_INT_EN_LOW	0x06 // Interrupt enable mask
#define STMPE1801_REG_INT_EN_HIGH	0x07
#define STMPE1801_REG_INT_STA_LOW	0x08 // Interrupt status
#define STMPE1801_REG_INT_STA_HIGH	0x09

#define STMPE1801_REG_GPIO_INT_EN_LOW	0x0A // Interrupt enable GPIO mask
#define STMPE1801_REG_GPIO_INT_EN_MID	0x0B
#define STMPE1801_REG_GPIO_INT_EN_HIGH	0x0C
#define STMPE1801_REG_GPIO_INT_STA_LOW	0x0D // Interrupt status GPIO
#define STMPE1801_REG_GPIO_INT_STA_MID	0x0E
#define STMPE1801_REG_GPIO_INT_STA_HIGH	0x0F
#define STMPE1801_REG_GPIO_SET_PIN_LOW	0x10 // GPIO set pin state
#define STMPE1801_REG_GPIO_SET_PIN_MID	0x11
#define STMPE1801_REG_GPIO_SET_PIN_HIGH	0x12
#define STMPE1801_REG_GPIO_CLR_PIN_LOW	0x13 // GPIO clear pin state
#define STMPE1801_REG_GPIO_CLR_PIN_MID	0x14
#define STMPE1801_REG_GPIO_CLR_PIN_HIGH	0x15
#define STMPE1801_REG_GPIO_MP_STA_LOW	0x16 // GPIO monitor pin state
#define STMPE1801_REG_GPIO_MP_STA_MID	0x17
#define STMPE1801_REG_GPIO_MP_STA_HIGH	0x18
#define STMPE1801_REG_GPIO_SET_DIR_LOW	0x19 // GPIO set pin direction register
#define STMPE1801_REG_GPIO_SET_DIR_MID	0x1A
#define STMPE1801_REG_GPIO_SET_DIR_HIGH	0x1B

#define STMPE1801_REG_GPIO_RE_LOW	0x1C // GPIO rising edge
#define STMPE1801_REG_GPIO_RE_MID	0x1D
#define STMPE1801_REG_GPIO_RE_HIGH	0x1E
#define STMPE1801_REG_GPIO_FE_LOW	0x1F // GPIO falling edge
#define STMPE1801_REG_GPIO_FE_MID	0x20
#define STMPE1801_REG_GPIO_FE_HIGH	0x21
#define STMPE1801_REG_GPIO_PULL_UP_LOW	0x22 // GPIO pull up
#define STMPE1801_REG_GPIO_PULL_UP_MID	0x23
#define STMPE1801_REG_GPIO_PULL_UP_HIGH	0x24

#define STMPE1801_REG_KPC_ROW	0x30 // Keypad row scanning
#define STMPE1801_REG_KPC_COL_LOW	0x31 // Keypad column scanning
#define STMPE1801_REG_KPC_COL_HIGH	0x32
#define STMPE1801_REG_KPC_CTRL_LOW	0x33 // Key config: Scan count and dedicated key
#define STMPE1801_REG_KPC_CTRL_MID	0x34
#define STMPE1801_REG_KPC_CTRL_HIGH	0x35
#define STMPE1801_REG_KPC_CMD	0x36 // Keypad command
#define STMPE1801_REG_KPC_COMB_KEY_0	0x37 // Keypad combination key mask
#define STMPE1801_REG_KPC_COMB_KEY_1	0x38
#define STMPE1801_REG_KPC_COMB_KEY_2	0x39
#define STMPE1801_REG_KPC_DATA_BYTE0	0x3A // Keypad data
#define STMPE1801_REG_KPC_DATA_BYTE1	0x3B
#define STMPE1801_REG_KPC_DATA_BYTE2	0x3C
#define STMPE1801_REG_KPC_DATA_BYTE3	0x3D
#define STMPE1801_REG_KPC_DATA_BYTE4	0x3E

#define STMPE1801_REG_MAX	0x3E
#define STMPE1801_REG_SIZE	3

/* STMPE2401 / STMPE2403 */
#define STMPE240X_REG_CHIP_ID	0x80 // Device identification
#define STMPE240X_REG_ID_VER	0x81 // Revision number

#define STMPE240X_REG_SYS_CTRL	0x02 // System control register
#define STMPE240X_REG_INT_CTRL_MSB	0x10 // Interrupt Control Register
#define STMPE240X_REG_INT_CTRL_LSB	0x11
#define STMPE240X_REG_INT_EN_MSB	0x12 // Interrupt Enable Mask Register
#define STMPE240X_REG_INT_EN_LSB	0x13
#define STMPE240X_REG_INT_STA_MSB	0x14 // Interrupt Status Register
#define STMPE240X_REG_INT_STA_LSB	0x15

#define STMPE240X_REG_GPIO_INT_EN_MSB	0x16 // Interrupt Enable GPIO Mask Register
#define STMPE240X_REG_GPIO_INT_EN_MID	0x17
#define STMPE240X_REG_GPIO_INT_EN_LSB	0x18
#define STMPE240X_REG_GPIO_INT_STA_MSB	0x19 // Interrupt Status GPIO Register
#define STMPE240X_REG_GPIO_INT_STA_MID	0x1A
#define STMPE240X_REG_GPIO_INT_STA_LSB	0x1B
#define STMPE240X_REG_GPIO_MP_STA_MSB	0xA2 // GPIO Monitor Pin State Register
#define STMPE240X_REG_GPIO_MP_STA_MID	0xA3
#define STMPE240X_REG_GPIO_MP_STA_LSB	0xA4
#define STMPE240X_REG_GPIO_SET_PIN_MSB	0x83 // GPIO Set Pin State Register
#define STMPE240X_REG_GPIO_SET_PIN_MID	0x84
#define STMPE240X_REG_GPIO_SET_PIN_LSB	0x85
#define STMPE240X_REG_GPIO_CLR_PIN_MSB	0x86 // GPIO Clear Pin State Register
#define STMPE240X_REG_GPIO_CLR_PIN_MID	0x87
#define STMPE240X_REG_GPIO_CLR_PIN_LSB	0x88
#define STMPE240X_REG_GPIO_SET_DIR_MSB	0x89 // GPIO Set Pin Direction Register
#define STMPE240X_REG_GPIO_SET_DIR_MID	0x8A
#define STMPE240X_REG_GPIO_SET_DIR_LSB	0x8B
#define STMPE240X_REG_GPIO_ED_MSB	0x8C // GPIO Edge Detect Status Register
#define STMPE240X_REG_GPIO_ED_MID	0x8D
#define STMPE240X_REG_GPIO_ED_LSB	0x8E
#define STMPE240X_REG_GPIO_RE_MSB	0x8F // GPIO Rising Edge Register
#define STMPE240X_REG_GPIO_RE_MID	0x90
#define STMPE240X_REG_GPIO_RE_LSB	0x91
#define STMPE240X_REG_GPIO_FE_MSB	0x92 // GPIO Falling Edge Register
#define STMPE240X_REG_GPIO_FE_MID	0x93
#define STMPE240X_REG_GPIO_FE_LSB	0x94
#define STMPE240X_REG_GPIO_PULL_UP_MSB	0x95 // GPIO Pull Up Register
#define STMPE240X_REG_GPIO_PULL_UP_MID	0x96
#define STMPE240X_REG_GPIO_PULL_UP_LSB	0x97
#define STMPE240X_REG_GPIO_PULL_DN_MSB	0x98 // GPIO Pull Down Register
#define STMPE240X_REG_GPIO_PULL_DN_MID	0x99
#define STMPE240X_REG_GPIO_PULL_DN_LSB	0x9A
#define STMPE240X_REG_GPIO_AF_U_MSB	0x9B // GPIO Alternate Function Register (Upper Bit)
#define STMPE240X_REG_GPIO_AF_U_MID	0x9C
#define STMPE240X_REG_GPIO_AF_U_LSB	0x9D
#define STMPE240X_REG_GPIO_AF_L_MSB	0x9E // GPIO Alternate Function Register(Lower Bit)
#define STMPE240X_REG_GPIO_AF_L_MID	0x9F
#define STMPE240X_REG_GPIO_AF_L_LSB	0xA0

#define STMPE240X_REG_PWMCS	0x30 // PWM Control and Status register
#define STMPE240X_REG_PWMIC0	0x38 // PWM instructions are initialized through this data port
#define STMPE240X_REG_PWMIC1	0x39
#define STMPE240X_REG_PWMIC2	0x3A

#define STMPE240X_REG_KPC_COL	0x60 // Keypad column scanning register
#define STMPE240X_REG_KPC_ROW_MSB	0x61 // Keypad row scanning register
#define STMPE240X_REG_KPC_ROW_LSB	0x62
#define STMPE240X_REG_KPC_CTRL_MSB	0x63 // Keypad control register
#define STMPE240X_REG_KPC_CTRL_LSB	0x64
#define STMPE240X_REG_KPC_DATA_BYTE0	0x68 // Keypad data register
#define STMPE240X_REG_KPC_DATA_BYTE1	0x69
#define STMPE240X_REG_KPC_DATA_BYTE2	0x6A

#define STMPE240X_REG_MAX	0xBF
#define STMPE240X_REG_SIZE	3

#define STMPE_REG_UNKNOWN	0xFF

/* STMPE ID constants */
/* STMPE610 / STMPE811 */
#define STMPE811_CHIP_ID	0x0811

/* STMPE801 */
#define STMPE801_CHIP_ID	0x0801

/* STMPE1601 */
#define STMPE1601_CHIP_ID	0x02

/* STMPE1801 */
#define STMPE1801_CHIP_ID	0xC1

/* STMPE2401 / STMPE2403 */
#define STMPE240X_CHIP_ID	0x01

/* STMPE System Control constants */
/* STMPE610 / STMPE811 */
#define STMPE811_SYS_CTRL2_TS_OFF	(1 << 3) // 1: Switches off the clock supply to the temperature sensor
#define STMPE811_SYS_CTRL2_GPIO_OFF	(1 << 2) // 1: Switches off the clock supply to the GPIO
#define STMPE811_SYS_CTRL2_TSC_OFF	(1 << 1) // 1: Switches off the clock supply to the touchscreen controller
#define STMPE811_SYS_CTRL2_ADC_OFF	(1 << 0) // 1: Switches off the clock supply to the ADC

/* STMPE801 */
#define STMPE801_SYS_CTRL_RESET	(1 << 7) // Writing 1 to this bit causes a soft reset
#define STMPE801_SYS_CTRL_INT_EN	(1 << 2) // INT Enable 1 to enable, 0 to disable INT output
#define STMPE801_SYS_CTRL_INT_HI	(1 << 0) // INT Polarity 1 for active HI, 0 for active LOW

/* STMPE1601 */
#define STMPE1601_SYS_CTRL_RESET	(1 << 7) // Writing a 1 to this bit will do a soft reset of the device. Once the reset is done, this bit will be cleared to 0 by the HW
#define STMPE1601_SYS_CTRL_ENABLE_GPIO	(1 << 3) // Writing a 0 to this bit will gate off the clock to the GPIO module, thus stopping its operation
#define STMPE1601_SYS_CTRL_ENABLE_KPC	(1 << 1) // Writing a 0 to this bit will gate off the clock to the keypad controller module, thus stopping its operation
#define STMPE1601_SYS_CTRL_ENABLE_SPWM	(1 << 0) // Writing a 0 to this bit will gate off the clock to the simple PWM controller module, thus stopping its operation

/* STMPE1801 */
#define STMPE1801_SYS_CTRL_RESET	(1 << 7) // Writing a 1 to this bit will do a soft reset of the device. Once the reset is done, this bit will be cleared to 0 by the HW

/* STMPE240X */
#define STMPE240X_SYS_CTRL_RESET	(1 << 7) // Writing a 1 to this bit will do a soft reset of the device. Once the reset is done, this bit will be cleared to 0 by the HW
#define STMPE240X_SYS_CTRL_ENABLE_GPIO	(1 << 3) // Writing a 0 to this bit will gate off the clock to the GPIO module, thus stopping its operation
#define STMPE240X_SYS_CTRL_ENABLE_PWM	(1 << 2) // Writing a 0 to this bit will gate off the clock to the PWM module, thus stopping its operation
#define STMPE240X_SYS_CTRL_ENABLE_KPC	(1 << 1) // Writing a 0 to this bit will gate off the clock to the Keypad Controller module, thus stopping its operation
#define STMPE240X_SYS_CTRL_ENABLE_ROT	(1 << 0) // Writing a 0 to this bit will gate off the clock to the Rotator module, thus stopping its operation

/* STMPE Touchscreen Control constants */
/* STMPE610 / STMPE811 */
#define STMPE811_TSC_CTRL_TSC_STA	(1 << 7) // TSC status (Reads '1' when touch is detected / Reads '0' when touch is not detected)
#define STMPE811_TSC_CTRL_TRACK_MASK	(7 << 4) // TRACK: Tracking index
#define STMPE811_TSC_CTRL_OPMODE_XYZ	(0 << 1) // OP_MOD: TSC operating mode: X, Y, Z acquisition
#define STMPE811_TSC_CTRL_OPMODE_XY	(1 << 1) // OP_MOD: TSC operating mode: X, Y only
#define STMPE811_TSC_CTRL_OPMODE_X	(2 << 1) // OP_MOD: TSC operating mode: X only
#define STMPE811_TSC_CTRL_OPMODE_Y	(3 << 1) // OP_MOD: TSC operating mode: Y only
#define STMPE811_TSC_CTRL_OPMODE_Z	(4 << 1) // OP_MOD: TSC operating mode: Z only
#define STMPE811_TSC_CTRL_TSC_EN	(1 << 0) // Enable TSC

/* STMPE Touchscreen Config constants */
/* STMPE610 / STMPE811 */
#define STMPE811_TSC_CFG_AVE_CTRL_1	(0 << 6) // AVE_CTRL: Average control: 1 sample
#define STMPE811_TSC_CFG_AVE_CTRL_2	(1 << 6) // AVE_CTRL: Average control: 2 samples
#define STMPE811_TSC_CFG_AVE_CTRL_4	(2 << 6) // AVE_CTRL: Average control: 4 samples
#define STMPE811_TSC_CFG_AVE_CTRL_8	(3 << 6) // AVE_CTRL: Average control: 8 samples
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_MASK	(7 << 3) // TOUCH_DET_DELAY: Touch detect delay
#define STMPE811_TSC_CFG_SETTLING_MASK	(7 << 0) // SETTLING: Panel driver settling time

/* STMPE ADC Control 1 constants */
/* STMPE610 / STMPE811 */
#define STMPE811_ADC_CTRL1_SAMPLE_TIME_MASK	(7 << 4) // SAMPLE_TIMEn: ADC conversion time in number of clock
#define STMPE811_ADC_CTRL1_MOD_12B	(1 << 3) // MOD_12B: Selects 10 or 12-bit ADC operation (1: 12 bit ADC / 0: 10 bit ADC)
#define STMPE811_ADC_CTRL1_REF_SEL	(1 << 1) // REF_SEL: Selects between internal or external reference for the ADC (1: External reference / 0: Internal reference)

/* STMPE ADC Control 2 constants */
/* STMPE610 / STMPE811 */
#define STMPE811_ADC_CTRL2_ADC_FREQ_MASK	(3 << 0) // ADC_FREQ: Selects the clock speed of ADC

/* STMPE FIFO Control and Status constants */
/* STMPE610 / STMPE811 */
#define STMPE811_FIFO_STA_RESET	(1 << 0) // FIFO Reset (Write 0 : FIFO put out of reset mode  / Write 1 : Resets FIFO. All data in FIFO will be cleared)

/* STMPE Interrupt Control constants */
/* STMPE610 / STMPE811 */
#define STMPE811_INT_CTRL_POLARITY	(1 << 2) // This bit sets the INT pin polarity (1: Active high/rising edge / 0: Active low/falling edge)
#define STMPE811_INT_CTRL_TYPE	(1 << 1) // This bit sets the type of interrupt signal required by the host (1: Edge interrupt / 0: Level interrupt)
#define STMPE811_INT_CTRL_GLOBAL	(1 << 0) // This is master enable for the interrupt system (1: Global interrupt / 0: Stops all interrupts)

/* STMPE Interrupt Enable constants */
/* STMPE610 / STMPE811 */
#define STMPE811_INT_EN_GPIO	(1 << 7) // GPIO: Any enabled GPIO interrupts
#define STMPE811_INT_EN_ADC	(1 << 6) // ADC: Any enabled ADC interrupts
#define STMPE811_INT_EN_TEMP_SENS	(1 << 5) // TEMP_SENS: Temperature threshold triggering
#define STMPE811_INT_EN_FIFO_EMPTY	(1 << 4) // FIFO_EMPTY: FIFO is empty
#define STMPE811_INT_EN_FIFO_FULL	(1 << 3) // FIFO_FULL: FIFO is full
#define STMPE811_INT_EN_FIFO_OFLOW	(1 << 2) // FIFO_OFLOW: FIFO is overflowed
#define STMPE811_INT_EN_FIFO_TH	(1 << 1) // FIFO_TH: FIFO is equal or above threshold value
#define STMPE811_INT_EN_TOUCH_DET	(1 << 0) // TOUCH_DET: Touch is detected

/* STMPE Interrupt Status constants */
/* STMPE610 / STMPE811 */
#define STMPE811_INT_STA_GPIO	(1 << 7) // GPIO: Any enabled GPIO interrupts
#define STMPE811_INT_STA_ADC	(1 << 6) // ADC: Any enabled ADC interrupts
#define STMPE811_INT_STA_TEMP_SENS	(1 << 5) // TEMP_SENS: Temperature threshold triggering
#define STMPE811_INT_STA_FIFO_EMPTY	(1 << 4) // FIFO_EMPTY: FIFO is empty
#define STMPE811_INT_STA_FIFO_FULL	(1 << 3) // FIFO_FULL: FIFO is full
#define STMPE811_INT_STA_FIFO_OFLOW	(1 << 2) // FIFO_OFLOW: FIFO is overflowed
#define STMPE811_INT_STA_FIFO_TH	(1 << 1) // FIFO_TH: FIFO is equal or above threshold value
#define STMPE811_INT_STA_TOUCH_DET	(1 << 0) // TOUCH_DET: Touch is detected

#define STMPE811_INT_STA_TOUCH_MASK	STMPE811_INT_STA_FIFO_EMPTY | STMPE811_INT_STA_FIFO_FULL | STMPE811_INT_STA_FIFO_OFLOW | STMPE811_INT_STA_FIFO_TH | STMPE811_INT_STA_TOUCH_DET

/* ============================================================================== */
/* STMPE specific types */
typedef struct _STMPE_CONTROL STMPE_CONTROL;
struct _STMPE_CONTROL
{
	// General Properties
	uint32_t chip; // The chip type (eg STMPE_CHIP_STMPE610)
	GPIO_INFO irq; // The GPIO information for the IRQ line (Optional)
	// I2C Properties
	I2C_DEVICE *i2c; // The I2C device this device is connected to (Optional)
	uint16_t address; // The I2C address of the device
	// SPI Properties
	SPI_DEVICE *spi; // The SPI device this device is connected to (Optional)
	uint16_t chipselect; // The SPI chip select of the device
	// Register Properties
	uint32_t regmax; // The maximum register address for read or write
	uint32_t regdir; // The register address direction (Ascending / Descending)
	uint32_t regsize; // The standard size of a register read or write
};


typedef struct _STMPE_OFFSETS STMPE_OFFSETS;
struct _STMPE_OFFSETS
{
	// Control Register offsets
	uint8_t sysctrl;
	uint8_t intctrl;
	uint8_t intenable;
	uint8_t intstatus;
	// GPIO Registers offsets
	uint8_t gpiointenable;
	uint8_t gpiointstatus;
	uint8_t gpiopinget;
	uint8_t gpiopinset;
	uint8_t gpiopinclr;
	uint8_t gpiodirset;
	uint8_t gpiofuncset;
	uint8_t gpiopullup;
	uint8_t gpiopulldown;
	uint8_t gpioedgedetect;
	uint8_t gpiorisingedge;
	uint8_t gpiofallingedge;
	// Touchscreen Register offsets (610 and 811 Only)
	uint8_t adcctrl1;
	uint8_t adcctrl2;
	uint8_t tscctrl;
	uint8_t tsccfg;
	uint8_t fifothreshold;
	uint8_t fifostatus;
	uint8_t tscdataxyz;
	uint8_t tscfractionz;
	uint8_t tscidrive;
};


typedef struct _STMPE_GPIO STMPE_GPIO;
struct _STMPE_GPIO
{
	// GPIO Properties
	GPIO_DEVICE gpio;
	// STMPE Properties
	STMPE_CONTROL control; // The control information (Chip, I2C, SPI etc) for this device
	STMPE_OFFSETS offsets; // The register offsets for this device
};


typedef struct _STMPE_TOUCH STMPE_TOUCH;
struct _STMPE_TOUCH
{
	// Touch Properties
	TOUCH_DEVICE touch;
	// General Properties
	uint16_t maxx; // Maximum X value for this device
	uint16_t maxy; // Maximum Y value for this device
	uint16_t maxz; // Maximum Z value for this device
	uint16_t width; // Screen width for this device
	uint16_t height; // Screen height for this device
	uint32_t maxpoints; // Maximum touch points for this device
	// STMPE Properties
	STMPE_CONTROL control; // The control information (Chip, I2C, SPI etc) for this device
	STMPE_OFFSETS offsets; // The register offsets for this device
	TIMER_HANDLE timer; // Handle for touch release timer
};

/* ============================================================================== */
/* STMPE specific variables */
static uint8_t STMPE_SAMPLE_TIME = 4;
static uint8_t STMPE_MOD_12B = 1;
static uint8_t STMPE_REF_SEL = 0;
static uint8_t STMPE_ADC_FREQ = 2;
static uint8_t STMPE_AVE_CTRL = 3;
static uint8_t STMPE_TOUCH_DET_DELAY = 4;
static uint8_t STMPE_SETTLING = 2;
static uint8_t STMPE_FRACTION_Z = 7;
static uint8_t STMPE_I_DRIVE = 0;

/* ============================================================================== */
/* Initialization Functions */
void STDCALL stmpe_init(void);

/* ============================================================================== */
/* STMPE Functions */
GPIO_DEVICE * STDCALL stmpe610_gpio_create(I2C_DEVICE *i2c, SPI_DEVICE *spi, uint16_t address, uint16_t chipselect, GPIO_INFO *irq);
GPIO_DEVICE * STDCALL stmpe801_gpio_create(I2C_DEVICE *i2c, uint16_t address, GPIO_INFO *irq);
GPIO_DEVICE * STDCALL stmpe811_gpio_create(I2C_DEVICE *i2c, SPI_DEVICE *spi, uint16_t address, uint16_t chipselect, GPIO_INFO *irq);
GPIO_DEVICE * STDCALL stmpe1601_gpio_create(I2C_DEVICE *i2c, uint16_t address, GPIO_INFO *irq);
GPIO_DEVICE * STDCALL stmpe1801_gpio_create(I2C_DEVICE *i2c, uint16_t address, GPIO_INFO *irq);
GPIO_DEVICE * STDCALL stmpe2401_gpio_create(I2C_DEVICE *i2c, uint16_t address, GPIO_INFO *irq);

uint32_t STDCALL stmpe_gpio_destroy(GPIO_DEVICE *gpio);

TOUCH_DEVICE * STDCALL stmpe610_touch_create(I2C_DEVICE *i2c, SPI_DEVICE *spi, uint16_t address, uint16_t chipselect, uint32_t width, uint32_t height, GPIO_INFO *irq);
TOUCH_DEVICE * STDCALL stmpe811_touch_create(I2C_DEVICE *i2c, SPI_DEVICE *spi, uint16_t address, uint16_t chipselect, uint32_t width, uint32_t height, GPIO_INFO *irq);

uint32_t STDCALL stmpe_touch_destroy(TOUCH_DEVICE *touch);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_STMPE_H
