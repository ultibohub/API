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
#ifndef _ULTIBO_GPIO_H
#define _ULTIBO_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/* ============================================================================== */
/* GPIO specific constants */
#define GPIO_NAME_PREFIX	"GPIO" // Name prefix for GPIO Devices

/* GPIO Device Types */
#define GPIO_TYPE_NONE	0

#define GPIO_TYPE_MAX	0

/* GPIO Device States */
#define GPIO_STATE_DISABLED	0
#define GPIO_STATE_ENABLED	1

#define GPIO_STATE_MAX	1

/* GPIO Device Flags */
#define GPIO_FLAG_NONE	0x00000000
#define GPIO_FLAG_PULL_UP	0x00000001 // Device supports Pull Up on a pin
#define GPIO_FLAG_PULL_DOWN	0x00000002 // Device supports Pull Down on a pin
#define GPIO_FLAG_TRIGGER_LOW	0x00000004 // Device supports Trigger on Low level on a pin
#define GPIO_FLAG_TRIGGER_HIGH	0x00000008 // Device supports Trigger on High level on a pin
#define GPIO_FLAG_TRIGGER_RISING	0x00000010 // Device supports Trigger on Rising edge on a pin
#define GPIO_FLAG_TRIGGER_FALLING	0x00000020 // Device supports Trigger on Falling edge on a pin
#define GPIO_FLAG_TRIGGER_EDGE	0x00000040 // Device supports Trigger on any edge (Rising or Falling) on a pin
#define GPIO_FLAG_TRIGGER_ASYNC	0x00000080 // Device supports Trigger on Asynchronous Rising/Falling edge on a pin

/* GPIO Event Flags */
#define GPIO_EVENT_FLAG_NONE	0x00000000
#define GPIO_EVENT_FLAG_REPEAT	0x00000001 // Event will be repeated until cancelled
#define GPIO_EVENT_FLAG_INTERRUPT	0x00000002 // Event will be dispatched by interrupt handler (If applicable)
                                               // Caution: Events called by the interrupt handler must obey interrupt
                                               //          rules with regard to locks, memory allocation and latency

/* ============================================================================== */
/* GPIO specific types */

/* GPIO Properties */
typedef struct _GPIO_PROPERTIES GPIO_PROPERTIES;
struct _GPIO_PROPERTIES
{
	uint32_t flags; // Device flags (eg GPIO_FLAG_TRIGGER_HIGH)
	uint32_t pinmin;
	uint32_t pinmax;
	uint32_t pincount;
	uint32_t functionmin;
	uint32_t functionmax;
	uint32_t functioncount;
};

/* GPIO Device */
typedef struct _GPIO_DEVICE GPIO_DEVICE; // Forward declared for GPIOPin
typedef struct _GPIO_PIN GPIO_PIN; // Forward declared for GPIOEvent

/* GPIO Event */
typedef struct _GPIO_EVENT GPIO_EVENT;
struct _GPIO_EVENT
{
	GPIO_PIN *pin; // GPIO Pin this event belongs to
	gpio_event_cb callback; // Callback function to call when trigger occurs
	void *data; // Pointer to pass to the callback function when trigger occurs
	uint32_t timeout; // Timeout in milliseconds for this callback (or INFINITE for no timeout)
	GPIO_EVENT *prev; // Previous event in the list
	GPIO_EVENT *next; // Next event in the list
};

/* GPIO Pin */
struct _GPIO_PIN
{
	GPIO_DEVICE *gpio; // GPIO device this pin belongs to
	uint32_t pin; // Pin number of this pin on the device (May be used by drivers for internal numbering)
	uint32_t flags; // Current flags for this pin (eg GPIO_EVENT_FLAG_REPEAT)
	uint32_t trigger; // Current trigger value for this pin (or GPIO_TRIGGER_NONE if no triggers current)
	uint32_t count; // Count of threads and events waiting for the trigger
	EVENT_HANDLE event; // Event for threads waiting for the trigger
	GPIO_EVENT *events; // List of events waiting for the trigger
};

/* GPIO Enumeration Callback */
typedef uint32_t STDCALL (*gpio_enumerate_cb)(GPIO_DEVICE *gpio, void *data);
/* GPIO Notification Callback */
typedef uint32_t STDCALL (*gpio_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/* GPIO Device Methods */
typedef uint32_t STDCALL (*gpio_device_start_proc)(GPIO_DEVICE *gpio);
typedef uint32_t STDCALL (*gpio_device_stop_proc)(GPIO_DEVICE *gpio);

typedef uint32_t STDCALL (*gpio_device_read_proc)(GPIO_DEVICE *gpio, uint32_t reg);
typedef void STDCALL (*gpio_device_write_proc)(GPIO_DEVICE *gpio, uint32_t reg, uint32_t value);

typedef uint32_t STDCALL (*gpio_device_input_get_proc)(GPIO_DEVICE *gpio, uint32_t pin);
typedef uint32_t STDCALL (*gpio_device_input_wait_proc)(GPIO_DEVICE *gpio, uint32_t pin, uint32_t trigger, uint32_t timeout);
typedef uint32_t STDCALL (*gpio_device_input_event_proc)(GPIO_DEVICE *gpio, uint32_t pin, uint32_t trigger, uint32_t flags, uint32_t timeout, gpio_event_cb callback, void *data);
typedef uint32_t STDCALL (*gpio_device_input_cancel_proc)(GPIO_DEVICE *gpio, uint32_t pin);

typedef uint32_t STDCALL (*gpio_device_output_set_proc)(GPIO_DEVICE *gpio, uint32_t pin, uint32_t level);

typedef uint32_t STDCALL (*gpio_device_pull_get_proc)(GPIO_DEVICE *gpio, uint32_t pin);
typedef uint32_t STDCALL (*gpio_device_pull_select_proc)(GPIO_DEVICE *gpio, uint32_t pin, uint32_t mode);

typedef uint32_t STDCALL (*gpio_device_function_get_proc)(GPIO_DEVICE *gpio, uint32_t pin);
typedef uint32_t STDCALL (*gpio_device_function_select_proc)(GPIO_DEVICE *gpio, uint32_t pin, uint32_t mode);

typedef uint32_t STDCALL (*gpio_device_get_properties_proc)(GPIO_DEVICE *gpio, GPIO_PROPERTIES *properties);

struct _GPIO_DEVICE
{
	// Device Properties
	DEVICE device; // The Device entry for this GPIO
	// GPIO Properties
	uint32_t gpioid; // Unique Id of this GPIO in the GPIO table
	uint32_t gpiostate; // GPIO state (eg GPIO_STATE_ENABLED)
	gpio_device_start_proc devicestart; // A Device specific DeviceStart method implementing the standard GPIO device interface (Mandatory)
	gpio_device_stop_proc devicestop; // A Device specific DeviceStop method implementing the standard GPIO device interface (Mandatory)
	gpio_device_read_proc deviceread; // A Device specific DeviceRead method implementing the standard GPIO device interface (Or nil if the default method is suitable)
	gpio_device_write_proc devicewrite; // A Device specific DeviceWrite method implementing the standard GPIO device interface (Or nil if the default method is suitable)
	gpio_device_input_get_proc deviceinputget; // A Device specific DeviceInputGet method implementing the standard GPIO device interface (Mandatory)
	gpio_device_input_wait_proc deviceinputwait; // A Device specific DeviceInputWait method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_input_event_proc deviceinputevent; // A Device specific DeviceInputEvent method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_input_cancel_proc deviceinputcancel; // A Device specific DeviceInputCancel method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_output_set_proc deviceoutputset; // A Device specific DeviceOutputSet method implementing the standard GPIO device interface (Mandatory)
	gpio_device_pull_get_proc devicepullget; // A Device specific DevicePullGet method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_pull_select_proc devicepullselect; // A Device specific DevicePullSelect method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_function_get_proc devicefunctionget; // A Device specific DeviceFunctionGet method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_function_select_proc devicefunctionselect; // A Device specific DeviceFunctionSelect method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_get_properties_proc devicegetproperties; // A Device specific DeviceGetProperties method implementing the standard GPIO device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; // Device lock
	void *address; // Device register base address
	GPIO_PIN *pins; // Device pins
	GPIO_PROPERTIES properties; // Device properties
	// Statistics Properties
	uint32_t getcount;
	uint32_t setcount;
	uint32_t waitcount;
	uint32_t eventcount;
	// Internal Properties
	GPIO_DEVICE *prev; // Previous entry in GPIO table
	GPIO_DEVICE *next; // Next entry in GPIO table
};

/* GPIO Info (Pin Information) */
typedef struct _GPIO_INFO GPIO_INFO;
struct _GPIO_INFO
{
	GPIO_DEVICE *gpio; // Device for this GPIO pin
	uint32_t pin; // Pin number (eg GPIO_PIN_59)
	uint32_t func; // Function value (or GPIO_FUNCTION_UNKNOWN)
	uint32_t pull; // Pull Up/Down value (or GPIO_PULL_UNKNOWN)
	uint32_t trigger; // Trigger value (or GPIO_TRIGGER_UNKNOWN)
};

/* GPIO Info Unknown */
static const GPIO_INFO GPIO_INFO_UNKNOWN = {
  NULL,
  GPIO_PIN_UNKNOWN,
  GPIO_FUNCTION_UNKNOWN,
  GPIO_PULL_UNKNOWN,
  GPIO_TRIGGER_UNKNOWN};

/* ============================================================================== */
/* GPIO Functions */
uint32_t STDCALL gpio_device_start(GPIO_DEVICE *gpio);
uint32_t STDCALL gpio_device_stop(GPIO_DEVICE *gpio);

uint32_t STDCALL gpio_device_read(GPIO_DEVICE *gpio, uint32_t reg);
void STDCALL gpio_device_write(GPIO_DEVICE *gpio, uint32_t reg, uint32_t value);

uint32_t STDCALL gpio_device_input_get(GPIO_DEVICE *gpio, uint32_t pin);
uint32_t STDCALL gpio_device_input_wait(GPIO_DEVICE *gpio, uint32_t pin, uint32_t trigger, uint32_t timeout);
uint32_t STDCALL gpio_device_input_event(GPIO_DEVICE *gpio, uint32_t pin, uint32_t trigger, uint32_t flags, uint32_t timeout, gpio_event_cb callback, void *data);
uint32_t STDCALL gpio_device_input_cancel(GPIO_DEVICE *gpio, uint32_t pin);

uint32_t STDCALL gpio_device_output_set(GPIO_DEVICE *gpio, uint32_t pin, uint32_t level);

uint32_t STDCALL gpio_device_level_get(GPIO_DEVICE *gpio, uint32_t pin);
uint32_t STDCALL gpio_device_level_set(GPIO_DEVICE *gpio, uint32_t pin, uint32_t level);

uint32_t STDCALL gpio_device_pull_get(GPIO_DEVICE *gpio, uint32_t pin);
uint32_t STDCALL gpio_device_pull_select(GPIO_DEVICE *gpio, uint32_t pin, uint32_t mode);

uint32_t STDCALL gpio_device_function_get(GPIO_DEVICE *gpio, uint32_t pin);
uint32_t STDCALL gpio_device_function_select(GPIO_DEVICE *gpio, uint32_t pin, uint32_t mode);

uint32_t STDCALL gpio_device_properties(GPIO_DEVICE *gpio, GPIO_PROPERTIES *properties);
uint32_t STDCALL gpio_device_get_properties(GPIO_DEVICE *gpio, GPIO_PROPERTIES *properties);

GPIO_DEVICE * STDCALL gpio_device_create(void);
GPIO_DEVICE * STDCALL gpio_device_create_ex(uint32_t size);
uint32_t STDCALL gpio_device_destroy(GPIO_DEVICE *gpio);

uint32_t STDCALL gpio_device_register(GPIO_DEVICE *gpio);
uint32_t STDCALL gpio_device_deregister(GPIO_DEVICE *gpio);

GPIO_DEVICE * STDCALL gpio_device_find(uint32_t gpioid);
GPIO_DEVICE * STDCALL gpio_device_find_by_name(const char *name);
GPIO_DEVICE * STDCALL gpio_device_find_by_description(const char *description);
uint32_t STDCALL gpio_device_enumerate(gpio_enumerate_cb callback, void *data);

uint32_t STDCALL gpio_device_notification(GPIO_DEVICE *gpio, gpio_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/* ============================================================================== */
/* GPIO Helper Functions */
uint32_t STDCALL gpio_get_count(void);
GPIO_DEVICE * STDCALL gpio_device_get_default(void);
uint32_t STDCALL gpio_device_set_default(GPIO_DEVICE *gpio);

GPIO_DEVICE * STDCALL gpio_device_check(GPIO_DEVICE *gpio);

uint32_t STDCALL gpio_type_to_string(uint32_t gpiotype, char *string, uint32_t len);
uint32_t STDCALL gpio_state_to_string(uint32_t gpiostate, char *string, uint32_t len);

GPIO_EVENT * STDCALL gpio_device_create_event(GPIO_DEVICE *gpio, GPIO_PIN *pin, gpio_event_cb callback, void *data, uint32_t timeout);
uint32_t STDCALL gpio_device_destroy_event(GPIO_DEVICE *gpio, GPIO_EVENT *event);

uint32_t STDCALL gpio_device_register_event(GPIO_DEVICE *gpio, GPIO_PIN *pin, GPIO_EVENT *event);
uint32_t STDCALL gpio_device_deregister_event(GPIO_DEVICE *gpio, GPIO_PIN *pin, GPIO_EVENT *event);

uint32_t STDCALL gpio_pin_to_string(uint32_t pin, char *string, uint32_t len);
uint32_t STDCALL gpio_level_to_string(uint32_t level, char *string, uint32_t len);
uint32_t STDCALL gpio_trigger_to_string(uint32_t trigger, char *string, uint32_t len);

uint32_t STDCALL gpio_pull_to_string(uint32_t value, char *string, uint32_t len);
uint32_t STDCALL gpio_function_to_string(uint32_t value, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_GPIO_H