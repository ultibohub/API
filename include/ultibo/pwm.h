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
#ifndef _ULTIBO_PWM_H
#define _ULTIBO_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* PWM specific constants */
#define PWM_NAME_PREFIX	"PWM" // Name prefix for PWM Devices

/* PWM Device Types */
#define PWM_TYPE_NONE	0

/* PWM Device States */
#define PWM_STATE_DISABLED	0
#define PWM_STATE_ENABLED	1

/* PWM Device Flags */
#define PWM_FLAG_NONE	0x00000000
#define PWM_FLAG_GPIO	0x00000001 // Device supports Get/Set GPIO
#define PWM_FLAG_MODE	0x00000002 // Device supports Get/Set Mode
#define PWM_FLAG_RANGE	0x00000004 // Device supports Get/Set Range
#define PWM_FLAG_FREQUENCY	0x00000008 // Device supports Get/Set Frequency
#define PWM_FLAG_POLARITY	0x00000010 // Device supports Get/Set Polarity

/* PWM Mode Values */
#define PWM_MODE_MARKSPACE	0 // Standard PWM Mark / Space mode
#define PWM_MODE_BALANCED	1 // Balanced mode (Device specific)
#define PWM_MODE_SERIALIZED	2 // Serialized mode (Device specific)

/* PWM Polarity Values */
#define PWM_POLARITY_NORMAL	0
#define PWM_POLARITY_INVERSE	1

/* ============================================================================== */
/* PWM specific types */

/* PWM Properties */
typedef struct _PWM_PROPERTIES PWM_PROPERTIES;
struct _PWM_PROPERTIES
{
	uint32_t flags; // Device flags (eg PWM_FLAG_MODE)
	uint32_t gpio;
	uint32_t mode;
	uint32_t range;
	uint32_t frequency;
	uint32_t polarity;
	uint32_t dutyns;
	uint32_t periodns;
	uint32_t minperiod;
};

/* PWM Device */
typedef struct _PWM_DEVICE PWM_DEVICE;

/* PWM Enumeration Callback */
typedef uint32_t STDCALL (*pwm_enumerate_cb)(PWM_DEVICE *pwm, void *data);
/* PWM Notification Callback */
typedef uint32_t STDCALL (*pwm_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* PWM Device Methods */
typedef uint32_t STDCALL (*pwm_device_start_proc)(PWM_DEVICE *pwm);
typedef uint32_t STDCALL (*pwm_device_stop_proc)(PWM_DEVICE *pwm);

typedef uint32_t STDCALL (*pwm_device_write_proc)(PWM_DEVICE *pwm, uint32_t value);

typedef uint32_t STDCALL (*pwm_device_get_gpio_proc)(PWM_DEVICE *pwm);
typedef uint32_t STDCALL (*pwm_device_set_gpio_proc)(PWM_DEVICE *pwm, uint32_t gpio);
typedef uint32_t STDCALL (*pwm_device_get_mode_proc)(PWM_DEVICE *pwm);
typedef uint32_t STDCALL (*pwm_device_set_mode_proc)(PWM_DEVICE *pwm, uint32_t mode);
typedef uint32_t STDCALL (*pwm_device_get_range_proc)(PWM_DEVICE *pwm);
typedef uint32_t STDCALL (*pwm_device_set_range_proc)(PWM_DEVICE *pwm, uint32_t range);
typedef uint32_t STDCALL (*pwm_device_get_frequency_proc)(PWM_DEVICE *pwm);
typedef uint32_t STDCALL (*pwm_device_set_frequency_proc)(PWM_DEVICE *pwm, uint32_t frequency);
typedef uint32_t STDCALL (*pwm_device_get_polarity_proc)(PWM_DEVICE *pwm);
typedef uint32_t STDCALL (*pwm_device_set_polarity_proc)(PWM_DEVICE *pwm, uint32_t polarity);

typedef uint32_t STDCALL (*pwm_device_configure_proc)(PWM_DEVICE *pwm, uint32_t dutyns, uint32_t periodns);

typedef uint32_t STDCALL (*pwm_device_get_properties_proc)(PWM_DEVICE *pwm, PWM_PROPERTIES *properties);

struct _PWM_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this PWM
	// PWM Properties
	uint32_t pwmid; // Unique Id of this PWM in the PWM table
	uint32_t pwmstate; // PWM state (eg PWM_STATE_ENABLED)
	pwm_device_start_proc devicestart; // A Device specific DeviceStart method implementing the standard PWM device interface (Mandatory)
	pwm_device_stop_proc devicestop; // A Device specific DeviceStop method implementing the standard PWM device interface (Mandatory)
	pwm_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing the standard PWM device interface (Mandatory)
	pwm_device_get_gpio_proc devicegetgpio; // A Device specific DeviceGetGPIO method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_set_gpio_proc devicesetgpio; // A Device specific DeviceSetGPIO method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_get_mode_proc devicegetmode; // A Device specific DeviceGetMode method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_set_mode_proc devicesetmode; // A Device specific DeviceSetMode method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_get_range_proc devicegetrange; // A Device specific DeviceGetRange method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_set_range_proc devicesetrange; // A Device specific DeviceSetRange method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_get_frequency_proc devicegetfrequency; // A Device specific DeviceGetFrequency method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_set_frequency_proc devicesetfrequency; // A Device specific DeviceSetFrequency method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_get_polarity_proc devicegetpolarity; // A Device specific DeviceGetPolarity method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_set_polarity_proc devicesetpolarity; // A Device specific DeviceSetPolarity method implementing the standard PWM device interface (Or nil if the operation is not supported)
	pwm_device_configure_proc deviceconfigure; // A Device specific DeviceConfigure method implementing the standard PWM device interface (Mandatory)
	pwm_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing the standard PWM device interface (Or nil if the default method is suitable)
	// Statistics Properties
	uint32_t getcount;
	uint32_t setcount;
	uint32_t writecount;
	uint32_t configcount;
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	uint32_t gpio; // GPIO Pin
	uint32_t mode; // Device Mode
	uint32_t range; // Device Range
	uint32_t frequency; // Clock Frequency
	uint32_t polarity; // Output Polarity
	uint32_t dutyns; // Duty Nanoseconds
	uint32_t periodns; // Period Nanonseconds
	PWM_PROPERTIES properties; // Device properties
	// Internal Properties
	PWM_DEVICE *prev; // Previous entry in PWM table
	PWM_DEVICE *next; // Next entry in PWM table
};

/* ============================================================================== */
/* PWM Functions */
uint32_t STDCALL pwm_device_start(PWM_DEVICE *pwm);
uint32_t STDCALL pwm_device_stop(PWM_DEVICE *pwm);

uint32_t STDCALL pwm_device_write(PWM_DEVICE *pwm, uint32_t value);

uint32_t STDCALL pwm_device_get_gpio(PWM_DEVICE *pwm);
uint32_t STDCALL pwm_device_set_gpio(PWM_DEVICE *pwm, uint32_t gpio);
uint32_t STDCALL pwm_device_get_mode(PWM_DEVICE *pwm);
uint32_t STDCALL pwm_device_set_mode(PWM_DEVICE *pwm, uint32_t mode);
uint32_t STDCALL pwm_device_get_range(PWM_DEVICE *pwm);
uint32_t STDCALL pwm_device_set_range(PWM_DEVICE *pwm, uint32_t range);
uint32_t STDCALL pwm_device_get_frequency(PWM_DEVICE *pwm);
uint32_t STDCALL pwm_device_set_frequency(PWM_DEVICE *pwm, uint32_t frequency);
uint32_t STDCALL pwm_device_get_polarity(PWM_DEVICE *pwm);
uint32_t STDCALL pwm_device_set_polarity(PWM_DEVICE *pwm, uint32_t polarity);

uint32_t STDCALL pwm_device_configure(PWM_DEVICE *pwm, uint32_t dutyns, uint32_t periodns);

uint32_t STDCALL pwm_device_properties(PWM_DEVICE *pwm, PWM_PROPERTIES *properties);
uint32_t STDCALL pwm_device_get_properties(PWM_DEVICE *pwm, PWM_PROPERTIES *properties);

PWM_DEVICE * STDCALL pwm_device_create(void);
PWM_DEVICE * STDCALL pwm_device_create_ex(uint32_t size);
uint32_t STDCALL pwm_device_destroy(PWM_DEVICE *pwm);

uint32_t STDCALL pwm_device_register(PWM_DEVICE *pwm);
uint32_t STDCALL pwm_device_deregister(PWM_DEVICE *pwm);

PWM_DEVICE * STDCALL pwm_device_find(uint32_t pwmid);
PWM_DEVICE * STDCALL pwm_device_find_by_name(char *name);
PWM_DEVICE * STDCALL pwm_device_find_by_description(char *description);
uint32_t STDCALL pwm_device_enumerate(pwm_enumerate_cb callback, void *data);

uint32_t STDCALL pwm_device_notification(PWM_DEVICE *pwm, pwm_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* PWM Helper Functions */
uint32_t STDCALL pwm_get_count(void);
PWM_DEVICE * STDCALL pwm_device_get_default(void);
uint32_t STDCALL pwm_device_set_default(PWM_DEVICE *pwm);

PWM_DEVICE * STDCALL pwm_device_check(PWM_DEVICE *pwm);

uint32_t STDCALL pwm_type_to_string(uint32_t pwmtype, char *string, uint32_t len);
uint32_t STDCALL pwm_state_to_string(uint32_t pwmstate, char *string, uint32_t len);
uint32_t STDCALL pwm_mode_to_string(uint32_t pwmmode, char *string, uint32_t len);
uint32_t STDCALL pwm_polarity_to_string(uint32_t pwmpolarity, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PWM_H