#ifndef _PWMSOUND_H
#define _PWMSOUND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/pwm.h"

#ifdef RPI4B
/* Define ID and channel for the PWM devices */
#define PWMSOUND_PWM1_ID 1
#define PWMSOUND_PWM1_CH 0
#define PWMSOUND_PWM2_ID 1
#define PWMSOUND_PWM2_CH 1

/* Define clock frequencies for the PWM clock */
#define PWMSOUND_PWM_OSC_CLOCK 54000000
#define PWMSOUND_PWM_PLLD_CLOCK 750000000
#else
/* Define ID and channel for the PWM devices */
#define PWMSOUND_PWM1_ID 0
#define PWMSOUND_PWM1_CH 0
#define PWMSOUND_PWM2_ID 1
#define PWMSOUND_PWM2_CH 0

/* Define clock frequencies for the PWM clock */
#define PWMSOUND_PWM_OSC_CLOCK 19200000   
#define PWMSOUND_PWM_PLLD_CLOCK 500000000 
#endif

/* Define sound parameters */
#define SOUND_BITS 16
#define SOUND_CHANNELS 2
#define SAMPLE_RATE 44100

/* Platform specific definitions */
#ifdef RPIB
/* Define clock rate */
#define CLOCK_RATE 125000000

/* Define GPIO pins */
#define PWMSOUND_PWM1_GPIO GPIO_PIN_40
#define PWMSOUND_PWM2_GPIO GPIO_PIN_45

/* Define BCM27XX PWM device */
typedef struct _BCM27XX_PWM_DEVICE BCM27XX_PWM_DEVICE;
struct _BCM27XX_PWM_DEVICE
{
    // PWM Properties
    PWM_DEVICE pwm;
    // BCM27XX Properties
    void *address; // Device register base address
    uint32_t channel; // Channel for this device
    uint32_t scaler; // Scaler for Duty cycle and Period
    BCM27XX_PWM_DEVICE *pair; // The paired PWM device for the other channel
    // Note: Audio properties omitted
};

// Physical memory addresses of BCM283X peripherals
#define BCM283X_PERIPHERALS_BASE 0x20000000  // Mapped to VC address 7E000000

#endif

#ifdef RPI2B
/* Define clock rate */
#define CLOCK_RATE 125000000

/* Define GPIO pins */
#define PWMSOUND_PWM1_GPIO GPIO_PIN_40
#define PWMSOUND_PWM2_GPIO GPIO_PIN_45

/* Define BCM27XX PWM device */
typedef struct _BCM27XX_PWM_DEVICE BCM27XX_PWM_DEVICE;
struct _BCM27XX_PWM_DEVICE
{
    // PWM Properties
    PWM_DEVICE pwm;
    // BCM27XX Properties
    void *address; // Device register base address
    uint32_t channel; // Channel for this device
    uint32_t scaler; // Scaler for Duty cycle and Period
    BCM27XX_PWM_DEVICE *pair; // The paired PWM device for the other channel
    // Note: Audio properties omitted
};

// Physical memory addresses of BCM283X peripherals
#define BCM283X_PERIPHERALS_BASE 0x3F000000  // Mapped to VC address 7E000000

#endif

#ifdef RPI3B
/* Define clock rate */
#define CLOCK_RATE 250000000

/* Define GPIO pins */
#define PWMSOUND_PWM1_GPIO GPIO_PIN_40
#define PWMSOUND_PWM2_GPIO GPIO_PIN_41

/* Define BCM27XX PWM device */
typedef struct _BCM27XX_PWM_DEVICE BCM27XX_PWM_DEVICE;
struct _BCM27XX_PWM_DEVICE
{
    // PWM Properties
    PWM_DEVICE pwm;
    // BCM27XX Properties
    void *address; // Device register base address
    uint32_t channel; // Channel for this device
    uint32_t scaler; // Scaler for Duty cycle and Period
    BCM27XX_PWM_DEVICE *pair; // The paired PWM device for the other channel
    // Note: Audio properties omitted
};

// Physical memory addresses of BCM283X peripherals
#define BCM283X_PERIPHERALS_BASE 0x3F000000  // Mapped to VC address 7E000000

#endif

#ifdef RPI4B
/* Define clock rate */
#define CLOCK_RATE 125000000

/* Define GPIO pins */
#define PWMSOUND_PWM1_GPIO GPIO_PIN_40
#define PWMSOUND_PWM2_GPIO GPIO_PIN_41

/* Define BCM27XX PWM device */
typedef struct _BCM27XX_PWM_DEVICE BCM27XX_PWM_DEVICE;
struct _BCM27XX_PWM_DEVICE
{
    // PWM Properties
    PWM_DEVICE pwm;
    // BCM27XX Properties
    uint32_t id; // Id of this device (0/1)
    void *address; // Device register base address
    uint32_t channel; // Channel for this device
    uint32_t scaler; // Scaler for Duty cycle and Period
    BCM27XX_PWM_DEVICE *pair; // The paired PWM device for the other channel
    // Note: Audio properties omitted
};

// Physical memory addresses of BCM283X peripherals
#define BCM283X_PERIPHERALS_BASE 0xFE000000  // Mapped to VC legacy address 7E000000

#endif

/* Define BCM283X PWM registers */
typedef struct _BCM283X_PWM_REGISTERS BCM283X_PWM_REGISTERS;
struct _BCM283X_PWM_REGISTERS
{
    uint32_t CTL; // PWM Control
    uint32_t STA; // PWM Status
    uint32_t DMAC; // PWM DMA Configuration
    uint32_t reserved1;   
    uint32_t RNG1; // PWM Channel 1 Range
    uint32_t DAT1; // PWM Channel 1 Data
    uint32_t FIF1; // PWM FIFO Input
    uint32_t reserved2;   
    uint32_t RNG2; // PWM Channel 2 Range
    uint32_t DAT2; // PWM Channel 2 Data
};

// Clock Management
#define BCM283X_CM_REGS_BASE BCM283X_PERIPHERALS_BASE + 0x101000

// Clock Manager Registers
#define BCM283X_CM_PWMCTL 0x000000A0 // PWM Clock Control
#define BCM283X_CM_PWMDIV 0x000000A4 // PWM Clock Divisor

// Clock Management
#define BCM283X_CM_PASSWORD 0x5A000000

// Clock Manager CM_*CTL register bits
#define BCM283X_CM_CTL_MASH_0         (0 << 9) // MASH control - 0 = integer division
#define BCM283X_CM_CTL_MASH_1         (1 << 9) // MASH control - 1 = 1-stage MASH (equivalent to non-MASH dividers)
#define BCM283X_CM_CTL_MASH_2         (2 << 9) // MASH control - 2 = 2-stage MASH
#define BCM283X_CM_CTL_MASH_3         (3 << 9) // MASH control - 3 = 3-stage MASH (To avoid lock-ups and glitches do not change this control while BUSY=1 and do not change this control at the same time as asserting ENAB)
#define BCM283X_CM_CTL_FLIP           (1 << 8) // MASH control - Invert the clock generator output (To avoid output glitches do not switch this control while BUSY=1)
#define BCM283X_CM_CTL_BUSY           (1 << 7) // Clock generator is running (To avoid glitches and lock-ups, clock sources and setups must not be changed while this flag is set)
#define BCM283X_CM_CTL_GATE           (1 << 6) // Unused
#define BCM283X_CM_CTL_KILL           (1 << 5) // Kill the clock generator (0 = no action / 1 = stop and reset the clock generator) (This is intended for test/debug only)
#define BCM283X_CM_CTL_ENAB           (1 << 4) // Enable the clock generator
 
#define BCM283X_CM_CTL_SRC_GND        (0 << 0) // Clock source - 0 Hz GND
#define BCM283X_CM_CTL_SRC_OSC        (1 << 0) // Clock source - 19.2 MHz Oscillator
#define BCM283X_CM_CTL_SRC_TESTDEBUG0 (2 << 0) // Clock source - 0 Hz Testdebug0
#define BCM283X_CM_CTL_SRC_TESTDEBUG1 (3 << 0) // Clock source - 0 Hz Testdebug1
#define BCM283X_CM_CTL_SRC_PLLA       (4 << 0) // Clock source - 0 Hz PLLA per
#define BCM283X_CM_CTL_SRC_PLLC       (5 << 0) // Clock source - 1000 MHz PLLC per (changes with overclock settings)
#define BCM283X_CM_CTL_SRC_PLLD       (6 << 0) // Clock source - 500 MHz PLLD per
#define BCM283X_CM_CTL_SRC_HDMI       (7 << 0) // Clock source - 216 MHz HDMI auxiliary
 
// Clock Manager CM_*DIV register bits
#define BCM283X_CM_DIV_INT_MASK  0x00FFF000 // Integer part of divisor (This value has a minimum limit determined by the MASH setting) (To avoid lock-ups and glitches do not change this control while BUSY=1)
#define BCM283X_CM_DIV_FRAC_MASK 0x00000FFF // Fractional part of divisor (To avoid lock-ups and glitches do not change this control while BUSY=1)

// Pulse Width Modulator (PWM) Control register bits
#define BCM283X_PWM_CTL_MSEN2 (1 << 15) // Channel 2 M/S Enable (0: PWM algorithm is used / 1: M/S transmission is used)
 // Bit 14 Reserved - Write as 0, read as don't care
#define BCM283X_PWM_CTL_USEF2 (1 << 13) // Channel 2 Use Fifo (0: Data register is transmitted / 1: Fifo is used for transmission)
#define BCM283X_PWM_CTL_POLA2 (1 << 12) // Channel 2 Polarity (0 : 0=low 1=high / 1: 1=low 0=high)
#define BCM283X_PWM_CTL_SBIT2 (1 << 11) // Channel 2 Silence Bit (Defines the state of the output when no transmission takes place)
#define BCM283X_PWM_CTL_RPTL2 (1 << 10) // Channel 2 Repeat Last Data (0: Transmission interrupts when FIFO is empty / 1: Last data in FIFO is transmitted repetedly until FIFO is not empty)
#define BCM283X_PWM_CTL_MODE2 (1 << 9)  // Channel 2 Mode (0: PWM mode / 1: Serialiser mode)
#define BCM283X_PWM_CTL_PWEN2 (1 << 8)  // Channel 2 Enable (0: Channel is disabled / 1: Channel is enabled)
#define BCM283X_PWM_CTL_MSEN1 (1 << 7)  // Channel 1 M/S Enable (0: PWM algorithm is used / 1: M/S transmission is used)
#define BCM283X_PWM_CTL_CLRF1 (1 << 6)  // Clear Fifo (1: Clears FIFO / 0: Has no effect) (This is a single shot operation. This bit always reads 0)
#define BCM283X_PWM_CTL_USEF1 (1 << 5)  // Channel 1 Use Fifo (0: Data register is transmitted / 1: Fifo is used for transmission)
#define BCM283X_PWM_CTL_POLA1 (1 << 4)  // Channel 1 Polarity (0 : 0=low 1=high / 1: 1=low 0=high)
#define BCM283X_PWM_CTL_SBIT1 (1 << 3)  // Channel 1 Silence Bit (Defines the state of the output when no transmission takes place)
#define BCM283X_PWM_CTL_RPTL1 (1 << 2)  // Channel 1 Repeat Last Data (0: Transmission interrupts when FIFO is empty / 1: Last data in FIFO is transmitted repetedly until FIFO is not empty)
#define BCM283X_PWM_CTL_MODE1 (1 << 1)  // Channel 1 Mode (0: PWM mode / 1: Serialiser mode)
#define BCM283X_PWM_CTL_PWEN1 (1 << 0)  // Channel 1 Enable (0: Channel is disabled / 1: Channel is enabled)
 
// Pulse Width Modulator (PWM) Status register bits
#define BCM283X_PWM_STA_STA4  (1 << 12) // Channel 4 State
#define BCM283X_PWM_STA_STA3  (1 << 11) // Channel 3 State
#define BCM283X_PWM_STA_STA2  (1 << 10) // Channel 2 State
#define BCM283X_PWM_STA_STA1  (1 << 9)  // Channel 1 State
#define BCM283X_PWM_STA_BERR  (1 << 8)  // Bus Error Flag
#define BCM283X_PWM_STA_GAPO4 (1 << 7)  // Channel 4 Gap Occurred Flag
#define BCM283X_PWM_STA_GAPO3 (1 << 6)  // Channel 3 Gap Occurred Flag
#define BCM283X_PWM_STA_GAPO2 (1 << 5)  // Channel 2 Gap Occurred Flag
#define BCM283X_PWM_STA_GAPO1 (1 << 4)  // Channel 1 Gap Occurred Flag
#define BCM283X_PWM_STA_RERR1 (1 << 3)  // Fifo Read Error Flag
#define BCM283X_PWM_STA_WERR1 (1 << 2)  // Fifo Write Error Flag
#define BCM283X_PWM_STA_EMPT1 (1 << 1)  // Fifo Empty Flag
#define BCM283X_PWM_STA_FULL1 (1 << 0)  // Fifo Full Flag
 
 // Pulse Width Modulator (PWM) DMA configuration register bits (See 9.6)
#define BCM283X_PWM_DMAC_ENAB  (1 << 31)  // DMA Enable (0: DMA disabled / 1: DMA enabled)
#define BCM283X_PWM_DMAC_PANIC (0xFF << 8) // DMA Threshold for PANIC signal (Default: 0x7)
#define BCM283X_PWM_DMAC_DREQ  (0xFF << 0) // DMA Threshold for DREQ signal (Default: 0x7)

 // Pulse Width Modulator (PWM) Registers
#define BCM283X_PWM_CTL  0x00000000 // PWM Control
#define BCM283X_PWM_STA  0x00000004 // PWM Status
#define BCM283X_PWM_DMAC 0x00000008 // PWM DMA Configuration
#define BCM283X_PWM_RNG1 0x00000010 // PWM Channel 1 Range
#define BCM283X_PWM_DAT1 0x00000014 // PWM Channel 1 Data
#define BCM283X_PWM_FIF1 0x00000018 // PWM FIFO Input
#define BCM283X_PWM_RNG2 0x00000020 // PWM Channel 2 Range
#define BCM283X_PWM_DAT2 0x00000024 // PWM Channel 2 Data

/* Import functions from BCM27XX driver units */
BOOL STDCALL bcm27xx_pwm_clock_enabled(PWM_DEVICE *pwm);
uint32_t STDCALL bcm27xx_pwm_clock_stop(PWM_DEVICE *pwm);

#endif // _PWMSOUND_H