/*
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
#ifndef _ULTIBO_SPI_H
#define _ULTIBO_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* SPI specific constants */
#define SPI_NAME_PREFIX	"SPI" // Name prefix for SPI Devices
#define SPISLAVE_NAME_PREFIX	"SPISlave" // Name prefix for SPI Slave Devices

/* SPI Device Types */
#define SPI_TYPE_NONE	0
#define SPI_TYPE_MASTER	1
#define SPI_TYPE_SLAVE	2

#define SPI_TYPE_MAX	2

/* SPI Device States */
#define SPI_STATE_DISABLED	0
#define SPI_STATE_ENABLED	1

#define SPI_STATE_MAX	1

/* SPI Device Flags */
#define SPI_FLAG_NONE	0x00000000
#define SPI_FLAG_SLAVE	0x00000001 // Device is a slave not a master
#define SPI_FLAG_4WIRE	0x00000002 // Device supports 4 wire operation (CS/MISO/MOSI/SCLK)
#define SPI_FLAG_3WIRE	0x00000004 // Device supports 3 wire operation (CS/MIMO/SCLK)
#define SPI_FLAG_LOSSI	0x00000008 // Device supports LoSSI (Low Speed Serial) mode (CS/SCL/SDA)
#define SPI_FLAG_CPOL	0x00000010 // Device supports Clock Polarity setting
#define SPI_FLAG_CPHA	0x00000020 // Device supports Clock Phase setting
#define SPI_FLAG_CSPOL	0x00000040 // Device supports Chip Select Polarity setting
#define SPI_FLAG_NO_CS	0x00000080 // Device supports Chip Select None (CS handled externally)
#define SPI_FLAG_DMA	0x00000100 // Device supports DMA transfers

/* SPI Transfer Flags */
#define SPI_TRANSFER_NONE	0x00000000
#define SPI_TRANSFER_DMA	0x00000001 // Use DMA for transfer (Write/Read) (Note: Buffers must be DMA compatible)
#define SPI_TRANSFER_PIO	0x00000002 // Use PIO (Polling) for transfer (Write/Read)
#define SPI_TRANSFER_DELAY	0x00000004 // Add a delay after each byte written (Write/Read) (Note: Only available with PIO transfer unless provided directly by hardware)

/* ============================================================================== */
/* SPI specific types */

/* SPI Properties */
typedef struct _SPI_PROPERTIES SPI_PROPERTIES;
struct _SPI_PROPERTIES
{
	uint32_t flags; // Device flags (eg SPI_FLAG_SLAVE)
	uint32_t maxsize; // Maximum supported data transfer size
	uint32_t minclock; // Minimum supported clock rate
	uint32_t maxclock; // Maximum supported clock rate
	uint32_t selectcount; // Number of chip selects supported
	uint32_t mode; // Current mode (eg SPI_MODE_4WIRE)
	uint32_t clockrate; // Current clock rate
	uint32_t clockphase; // Current clock phase (CPHA) (eg SPI_CLOCK_PHASE_LOW)
	uint32_t clockpolarity; // Current clock polarity (CPOL) (eg SPI_CLOCK_POLARITY_LOW)
	uint32_t selectpolarity; // Default chip select polarity (eg SPI_CS_POLARITY_LOW)
	uint32_t bytedelay; // Delay between bytes written (Microseconds)
};


/* SPI Chip Select */
typedef struct _SPI_CHIP_SELECT SPI_CHIP_SELECT;
struct _SPI_CHIP_SELECT
{
	uint32_t pin; // The GPIO pin for this chip select (eg GPIO_PIN_46)(GPIO_PIN_UNKNOWN for internal)
	uint32_t mode; // The mode for this chip select (eg SPI_MODE_0)
	uint32_t divider; // The clock divider for this chip select (Used internally by drivers)
	uint32_t clockrate; // The clock rate for this chip select
	uint32_t clockphase; // The clock phase (CPHA) for this chip select (eg SPI_CLOCK_PHASE_LOW)
	uint32_t clockpolarity; // The clock polarity (CPOL) for this chip select (eg SPI_CLOCK_POLARITY_LOW)
	uint32_t selectpolarity; // The chip select polarity for this chip select (eg SPI_CS_POLARITY_LOW)
	uint32_t bytedelay; // Delay between bytes written for this chip select (Microseconds)
};


/* SPI Device */
typedef struct _SPI_DEVICE SPI_DEVICE;

/* SPI Enumeration Callback */
typedef uint32_t STDCALL (*spi_enumerate_cb)(SPI_DEVICE *spi, void *data);
/* SPI Notification Callback */
typedef uint32_t STDCALL (*spi_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* SPI Device Methods */
typedef uint32_t STDCALL (*spi_device_start_proc)(SPI_DEVICE *spi, uint32_t mode, uint32_t clockrate, uint32_t clockphase, uint32_t clockpolarity);
typedef uint32_t STDCALL (*spi_device_stop_proc)(SPI_DEVICE *spi);

typedef uint32_t STDCALL (*spi_device_read_proc)(SPI_DEVICE *spi, uint16_t chipselect, void *dest, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*spi_device_write_proc)(SPI_DEVICE *spi, uint16_t chipselect, void *source, uint32_t size, uint32_t flags, uint32_t *count);
typedef uint32_t STDCALL (*spi_device_write_read_proc)(SPI_DEVICE *spi, uint16_t chipselect, void *source, void *dest, uint32_t size, uint32_t flags, uint32_t *count);

typedef uint32_t STDCALL (*spi_device_get_mode_proc)(SPI_DEVICE *spi);
typedef uint32_t STDCALL (*spi_device_set_mode_proc)(SPI_DEVICE *spi, uint32_t mode);

typedef uint32_t STDCALL (*spi_device_get_clock_rate_proc)(SPI_DEVICE *spi, uint16_t chipselect);
typedef uint32_t STDCALL (*spi_device_set_clock_rate_proc)(SPI_DEVICE *spi, uint16_t chipselect, uint32_t clockrate);

typedef uint32_t STDCALL (*spi_device_get_clock_phase_proc)(SPI_DEVICE *spi);
typedef uint32_t STDCALL (*spi_device_set_clock_phase_proc)(SPI_DEVICE *spi, uint32_t clockphase);

typedef uint32_t STDCALL (*spi_device_get_clock_polarity_proc)(SPI_DEVICE *spi);
typedef uint32_t STDCALL (*spi_device_set_clock_polarity_proc)(SPI_DEVICE *spi, uint32_t clockpolarity);

typedef uint32_t STDCALL (*spi_device_get_select_polarity_proc)(SPI_DEVICE *spi, uint16_t chipselect);
typedef uint32_t STDCALL (*spi_device_set_select_polarity_proc)(SPI_DEVICE *spi, uint16_t chipselect, uint32_t selectpolarity);

typedef uint32_t STDCALL (*spi_device_get_byte_delay_proc)(SPI_DEVICE *spi);
typedef uint32_t STDCALL (*spi_device_set_byte_delay_proc)(SPI_DEVICE *spi, uint32_t delay);

typedef uint32_t STDCALL (*spi_device_get_properties_proc)(SPI_DEVICE *spi, SPI_PROPERTIES *properties);

struct _SPI_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this SPI
	// SPI Properties
	uint32_t spiid; // Unique Id of this SPI in the SPI table
	uint32_t spistate; // SPI state (eg SPI_STATE_ENABLED)
	uint32_t spimode; // SPI mode (eg SPI_MODE_4WIRE)
	spi_device_start_proc devicestart; // A Device specific DeviceStart method implementing the standard SPI device interface (Mandatory)
	spi_device_stop_proc devicestop; // A Device specific DeviceStop method implementing the standard SPI device interface (Mandatory)
	spi_device_read_proc deviceread; // A Device specific DeviceRead method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_write_read_proc devicewriteread; // A Device specific DeviceWriteRead method implementing the standard SPI device interface (Mandatory)
	spi_device_get_mode_proc devicegetmode; // A Device specific DeviceGetMode method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_set_mode_proc devicesetmode; // A Device specific DeviceSetMode method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_get_clock_rate_proc devicegetclockrate; // A Device specific DeviceGetClockRate method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_set_clock_rate_proc devicesetclockrate; // A Device specific DeviceSetClockRate method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_get_clock_phase_proc devicegetclockphase; // A Device specific DeviceGetClockPhase method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_set_clock_phase_proc devicesetclockphase; // A Device specific DeviceSetClockPhase method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_get_clock_polarity_proc devicegetclockpolarity; // A Device specific DeviceGetClockPolarity method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_set_clock_polarity_proc devicesetclockpolarity; // A Device specific DeviceSetClockPolarity method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_get_select_polarity_proc devicegetselectpolarity; // A Device specific DeviceGetSelectPolarity method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_set_select_polarity_proc devicesetselectpolarity; // A Device specific DeviceSetSelectPolarity method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_get_byte_delay_proc devicegetbytedelay; // A Device specific DeviceGetByteDelay method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_set_byte_delay_proc devicesetbytedelay; // A Device specific DeviceSetByteDelay method implementing the standard SPI device interface (Or nil if the default method is suitable)
	spi_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing the standard SPI device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t transfercount;
	uint32_t transfererrors;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	SEMAPHORE_HANDLE wait; // Write/Read wait event
	uint32_t divider; // Clock divider (Used internally by drivers)
	uint32_t clockrate; // Clock rate (Hz)
	uint32_t clockphase; // Clock Phase (eg SPI_CLOCK_PHASE_LOW)
	uint32_t clockpolarity; // Clock Polarity (eg SPI_CLOCK_POLARITY_LOW)
	uint32_t selectpolarity; // Default Chip Select Polarity (eg SPI_CS_POLARITY_LOW)
	uint32_t bytedelay; // Delay between bytes written (Microseconds)
	SPI_PROPERTIES properties; // Device properties
	SPI_CHIP_SELECT chipselects[SPI_CS_MAX + 1]; // Chip selects
	// Internal Properties
	SPI_DEVICE *prev; // Previous entry in SPI table
	SPI_DEVICE *next; // Next entry in SPI table
};

/* ============================================================================== */
/* SPI Functions */
uint32_t STDCALL spi_device_start(SPI_DEVICE *spi, uint32_t mode, uint32_t clockrate, uint32_t clockphase, uint32_t clockpolarity);
uint32_t STDCALL spi_device_stop(SPI_DEVICE *spi);

uint32_t STDCALL spi_device_read(SPI_DEVICE *spi, uint16_t chipselect, void *dest, uint32_t size, uint32_t flags, uint32_t *count);
uint32_t STDCALL spi_device_write(SPI_DEVICE *spi, uint16_t chipselect, void *source, uint32_t size, uint32_t flags, uint32_t *count);
uint32_t STDCALL spi_device_write_read(SPI_DEVICE *spi, uint16_t chipselect, void *source, void *dest, uint32_t size, uint32_t flags, uint32_t *count);

uint32_t STDCALL spi_device_get_mode(SPI_DEVICE *spi);
uint32_t STDCALL spi_device_set_mode(SPI_DEVICE *spi, uint32_t mode);

uint32_t STDCALL spi_device_get_clock_rate(SPI_DEVICE *spi, uint16_t chipselect);
uint32_t STDCALL spi_device_set_clock_rate(SPI_DEVICE *spi, uint16_t chipselect, uint32_t clockrate);

uint32_t STDCALL spi_device_get_clock_phase(SPI_DEVICE *spi);
uint32_t STDCALL spi_device_set_clock_phase(SPI_DEVICE *spi, uint32_t clockphase);

uint32_t STDCALL spi_device_get_clock_polarity(SPI_DEVICE *spi);
uint32_t STDCALL spi_device_set_clock_polarity(SPI_DEVICE *spi, uint32_t clockpolarity);

uint32_t STDCALL spi_device_get_select_polarity(SPI_DEVICE *spi, uint16_t chipselect);
uint32_t STDCALL spi_device_set_select_polarity(SPI_DEVICE *spi, uint16_t chipselect, uint32_t selectpolarity);

uint32_t STDCALL spi_device_get_byte_delay(SPI_DEVICE *spi);
uint32_t STDCALL spi_device_set_byte_delay(SPI_DEVICE *spi, uint32_t delay);

uint32_t STDCALL spi_device_properties(SPI_DEVICE *spi, SPI_PROPERTIES *properties);
uint32_t STDCALL spi_device_get_properties(SPI_DEVICE *spi, SPI_PROPERTIES *properties);

SPI_DEVICE * STDCALL spi_device_create(void);
SPI_DEVICE * STDCALL spi_device_create_ex(uint32_t size);
uint32_t STDCALL spi_device_destroy(SPI_DEVICE *spi);

uint32_t STDCALL spi_device_register(SPI_DEVICE *spi);
uint32_t STDCALL spi_device_deregister(SPI_DEVICE *spi);

SPI_DEVICE * STDCALL spi_device_find(uint32_t spiid);
SPI_DEVICE * STDCALL spi_device_find_by_name(char *name);
SPI_DEVICE * STDCALL spi_device_find_by_description(char *description);
uint32_t STDCALL spi_device_enumerate(spi_enumerate_cb callback, void *data);

uint32_t STDCALL spi_device_notification(SPI_DEVICE *spi, spi_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* SPI Helper Functions */
uint32_t STDCALL spi_get_count(void);
SPI_DEVICE * STDCALL spi_device_get_default(void);
uint32_t STDCALL spi_device_set_default(SPI_DEVICE *spi);

SPI_DEVICE * STDCALL spi_device_check(SPI_DEVICE *spi);

uint32_t STDCALL spi_type_to_string(uint32_t spitype, char *string, uint32_t len);
uint32_t STDCALL spi_state_to_string(uint32_t spistate, char *string, uint32_t len);

uint32_t STDCALL spi_chip_select_to_string(uint16_t chipselect, char *string, uint32_t len);
uint32_t STDCALL spi_mode_to_string(uint32_t mode, char *string, uint32_t len);
uint32_t STDCALL spi_clock_phase_to_string(uint32_t phase, char *string, uint32_t len);
uint32_t STDCALL spi_clock_polarity_to_string(uint32_t polarity, char *string, uint32_t len);
uint32_t STDCALL spi_select_polarity_to_string(uint32_t polarity, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_SPI_H