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
#ifndef _ULTIBO_GPIO_H
#define _ULTIBO_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/devices.h"

/** GPIO specific constants */
#define GPIO_NAME_PREFIX	"GPIO" ///< Name prefix for GPIO Devices

/** GPIO Device Types */
#define GPIO_TYPE_NONE	0

#define GPIO_TYPE_MAX	0

/** GPIO Device States */
#define GPIO_STATE_DISABLED	0
#define GPIO_STATE_ENABLED	1

#define GPIO_STATE_MAX	1

/** GPIO Device Flags */
#define GPIO_FLAG_NONE	0x00000000
#define GPIO_FLAG_PULL_UP	0x00000001 ///< Device supports Pull Up on a pin
#define GPIO_FLAG_PULL_DOWN	0x00000002 ///< Device supports Pull Down on a pin
#define GPIO_FLAG_TRIGGER_LOW	0x00000004 ///< Device supports Trigger on Low level on a pin
#define GPIO_FLAG_TRIGGER_HIGH	0x00000008 ///< Device supports Trigger on High level on a pin
#define GPIO_FLAG_TRIGGER_RISING	0x00000010 ///< Device supports Trigger on Rising edge on a pin
#define GPIO_FLAG_TRIGGER_FALLING	0x00000020 ///< Device supports Trigger on Falling edge on a pin
#define GPIO_FLAG_TRIGGER_EDGE	0x00000040 ///< Device supports Trigger on any edge (Rising or Falling) on a pin
#define GPIO_FLAG_TRIGGER_ASYNC	0x00000080 ///< Device supports Trigger on Asynchronous Rising/Falling edge on a pin

/** GPIO Event Flags */
#define GPIO_EVENT_FLAG_NONE	0x00000000
#define GPIO_EVENT_FLAG_REPEAT	0x00000001 ///< Event will be repeated until cancelled
#define GPIO_EVENT_FLAG_INTERRUPT	0x00000002 ///< Event will be dispatched by interrupt handler (If applicable)
                                               // Caution: Events called by the interrupt handler must obey interrupt
                                               //          rules with regard to locks, memory allocation and latency

/** GPIO specific types */

/** GPIO Properties */
typedef struct _GPIO_PROPERTIES GPIO_PROPERTIES;
struct _GPIO_PROPERTIES
{
	uint32_t flags; ///< Device flags (eg GPIO_FLAG_TRIGGER_HIGH)
	uint32_t pinmin;
	uint32_t pinmax;
	uint32_t pincount;
	uint32_t functionmin;
	uint32_t functionmax;
	uint32_t functioncount;
};

/** GPIO Device */
typedef struct _GPIO_DEVICE GPIO_DEVICE; ///< Forward declared for GPIOPin
typedef struct _GPIO_PIN GPIO_PIN; ///< Forward declared for GPIOEvent

/** GPIO Event */
typedef struct _GPIO_EVENT GPIO_EVENT;
struct _GPIO_EVENT
{
	GPIO_PIN *pin; ///< GPIO Pin this event belongs to
	gpio_event_cb callback; ///< Callback function to call when trigger occurs
	void *data; ///< Pointer to pass to the callback function when trigger occurs
	uint32_t timeout; ///< Timeout in milliseconds for this callback (or INFINITE for no timeout)
	GPIO_EVENT *prev; ///< Previous event in the list
	GPIO_EVENT *next; ///< Next event in the list
};

/** GPIO Pin */
struct _GPIO_PIN
{
	GPIO_DEVICE *gpio; ///< GPIO device this pin belongs to
	uint32_t pin; ///< Pin number of this pin on the device (May be used by drivers for internal numbering)
	uint32_t flags; ///< Current flags for this pin (eg GPIO_EVENT_FLAG_REPEAT)
	uint32_t trigger; ///< Current trigger value for this pin (or GPIO_TRIGGER_NONE if no triggers current)
	uint32_t count; ///< Count of threads and events waiting for the trigger
	EVENT_HANDLE event; ///< Event for threads waiting for the trigger
	GPIO_EVENT *events; ///< List of events waiting for the trigger
};

/** GPIO Enumeration Callback */
typedef uint32_t STDCALL (*gpio_enumerate_cb)(GPIO_DEVICE *gpio, void *data);
/** GPIO Notification Callback */
typedef uint32_t STDCALL (*gpio_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** GPIO Device Methods */
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
	DEVICE device; ///< The Device entry for this GPIO
	// GPIO Properties
	uint32_t gpioid; ///< Unique Id of this GPIO in the GPIO table
	uint32_t gpiostate; ///< GPIO state (eg GPIO_STATE_ENABLED)
	gpio_device_start_proc devicestart; ///< A Device specific DeviceStart method implementing the standard GPIO device interface (Mandatory)
	gpio_device_stop_proc devicestop; ///< A Device specific DeviceStop method implementing the standard GPIO device interface (Mandatory)
	gpio_device_read_proc deviceread; ///< A Device specific DeviceRead method implementing the standard GPIO device interface (Or nil if the default method is suitable)
	gpio_device_write_proc devicewrite; ///< A Device specific DeviceWrite method implementing the standard GPIO device interface (Or nil if the default method is suitable)
	gpio_device_input_get_proc deviceinputget; ///< A Device specific DeviceInputGet method implementing the standard GPIO device interface (Mandatory)
	gpio_device_input_wait_proc deviceinputwait; ///< A Device specific DeviceInputWait method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_input_event_proc deviceinputevent; ///< A Device specific DeviceInputEvent method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_input_cancel_proc deviceinputcancel; ///< A Device specific DeviceInputCancel method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_output_set_proc deviceoutputset; ///< A Device specific DeviceOutputSet method implementing the standard GPIO device interface (Mandatory)
	gpio_device_pull_get_proc devicepullget; ///< A Device specific DevicePullGet method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_pull_select_proc devicepullselect; ///< A Device specific DevicePullSelect method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_function_get_proc devicefunctionget; ///< A Device specific DeviceFunctionGet method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_function_select_proc devicefunctionselect; ///< A Device specific DeviceFunctionSelect method implementing the standard GPIO device interface (Or nil if the operation is not supported)
	gpio_device_get_properties_proc devicegetproperties; ///< A Device specific DeviceGetProperties method implementing the standard GPIO device interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; ///< Device lock
	void *address; ///< Device register base address
	GPIO_PIN *pins; ///< Device pins
	GPIO_PROPERTIES properties; ///< Device properties
	// Statistics Properties
	uint32_t getcount;
	uint32_t setcount;
	uint32_t waitcount;
	uint32_t eventcount;
	// Internal Properties
	GPIO_DEVICE *prev; ///< Previous entry in GPIO table
	GPIO_DEVICE *next; ///< Next entry in GPIO table
};

/** GPIO Info (Pin Information) */
typedef struct _GPIO_INFO GPIO_INFO;
struct _GPIO_INFO
{
	GPIO_DEVICE *gpio; ///< Device for this GPIO pin
	uint32_t pin; ///< Pin number (eg GPIO_PIN_59)
	uint32_t func; ///< Function value (or GPIO_FUNCTION_UNKNOWN)
	uint32_t pull; ///< Pull Up/Down value (or GPIO_PULL_UNKNOWN)
	uint32_t trigger; ///< Trigger value (or GPIO_TRIGGER_UNKNOWN)
};

/** GPIO Info Unknown */
static const GPIO_INFO GPIO_INFO_UNKNOWN = {
  NULL,
  GPIO_PIN_UNKNOWN,
  GPIO_FUNCTION_UNKNOWN,
  GPIO_PULL_UNKNOWN,
  GPIO_TRIGGER_UNKNOWN};

/** GPIO Functions */

/**
 * @brief Start the specified GPIO device and enable access
 * @param GPIO The GPIO device to start
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL gpio_device_start(GPIO_DEVICE *gpio);

/**
 * @brief Stop the specified GPIO device and disable access
 * @param GPIO The GPIO device to stop
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL gpio_device_stop(GPIO_DEVICE *gpio);

/**
 * @brief Perform a direct read from a register of the specified GPIO device
 * @param GPIO The GPIO device to read from
 * @param Reg The memory register to read from
 * @return The value of the memory register
 */
uint32_t STDCALL gpio_device_read(GPIO_DEVICE *gpio, uint32_t reg);

/**
 * @brief Perform a direct write to a register of the specified GPIO device
 * @param GPIO The GPIO device to write to
 * @param Reg The memory register to write to
 * @param Value The value to write to the register
 */
void STDCALL gpio_device_write(GPIO_DEVICE *gpio, uint32_t reg, uint32_t value);

/**
 * @brief Get the current state of an input pin on the specified GPIO device
 * @param GPIO The GPIO device to get from
 * @param Pin The pin to get the state for (eg GPIO_PIN_1)
 * @return The current state (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure
 */
uint32_t STDCALL gpio_device_input_get(GPIO_DEVICE *gpio, uint32_t pin);

/**
 * @brief Wait for the state of a input pin to change on the specified GPIO device
 * @param GPIO The GPIO device to wait for
 * @param Pin The pin to wait for the state to change (eg GPIO_PIN_1)
 * @param Trigger The trigger event to wait for (eg GPIO_TRIGGER_HIGH)
 * @param Timeout Number of milliseconds to wait for the change (INFINITE to wait forever)
 * @return The state after the change (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure or timeout
 */
uint32_t STDCALL gpio_device_input_wait(GPIO_DEVICE *gpio, uint32_t pin, uint32_t trigger, uint32_t timeout);

/**
 * @brief Schedule a function to be called when the state of a input pin changes on the specified GPIO device
 * @param GPIO The GPIO device to schedule the callback for
 * @param Pin The pin to schedule the state change for (eg GPIO_PIN_1)
 * @param Trigger The trigger event which will cause the function to be called (eg GPIO_TRIGGER_HIGH)
 * @param Flags The flags to control the event (eg GPIO_EVENT_FLAG_REPEAT)
 * @param Timeout The number of milliseconds before the scheduled trigger expires (INFINITE to never expire)
 * @param Callback The function to be called when the trigger occurs
 * @param Data A pointer to be pass to the function when the trigger occurs (Optional)
 * @return ERROR_SUCCESS if the trigger was scheduled successfully or another error code on failure
 * @note The pin and trigger that caused the event will be passed to the callback function
 */
uint32_t STDCALL gpio_device_input_event(GPIO_DEVICE *gpio, uint32_t pin, uint32_t trigger, uint32_t flags, uint32_t timeout, gpio_event_cb callback, void *data);

/**
 * @brief Cancel a previously scheduled event callback function for an input pin on the specified GPIO device
 * @param GPIO The GPIO device to cancel the callback for
 * @param Pin The pin to cancel the state change for (eg GPIO_PIN_1)
 * @return ERROR_SUCCESS if the callback was cancelled successfully or another error code on failure
 */
uint32_t STDCALL gpio_device_input_cancel(GPIO_DEVICE *gpio, uint32_t pin);

/**
 * @brief Set the state of a output pin on the specified GPIO device
 * @param GPIO The GPIO device to set for
 * @param Pin The pin to set the state for (eg GPIO_PIN_1)
 * @param Level The state to set the pin to (eg GPIO_LEVEL_HIGH)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 */
uint32_t STDCALL gpio_device_output_set(GPIO_DEVICE *gpio, uint32_t pin, uint32_t level);

/**
 * @brief Get the current level (state) of a pin on the specified GPIO device
 * @param GPIO The GPIO device to get from
 * @param Pin The pin to get the level for (eg GPIO_PIN_1)
 * @return The current level (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure
 * @note This function is a synonym for GPIODeviceInputGet as in many cases the
 *        level can be read from a pin regardless of input or output mode. This
 *        may help to make code clearer or easier to understand in some cases
 */
uint32_t STDCALL gpio_device_level_get(GPIO_DEVICE *gpio, uint32_t pin);

/**
 * @brief Set the level (state) of a pin on the specified GPIO device
 * @param GPIO The GPIO device to set for
 * @param Pin The pin to set the level for (eg GPIO_PIN_1)
 * @param Level The level to set the pin to (eg GPIO_LEVEL_HIGH)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 * @note This function is a synonym for GPIODeviceOutputSet as in many cases the
 *        level can be set for a pin regardless of input or output mode. This
 *        may help to make code clearer or easier to understand in some cases
 */
uint32_t STDCALL gpio_device_level_set(GPIO_DEVICE *gpio, uint32_t pin, uint32_t level);

/**
 * @brief Get the current pull state of a pin on the specified GPIO device
 * @param GPIO The GPIO device to get from
 * @param Pin The pin to get the pull state for (eg GPIO_PIN_1)
 * @return The current pull state of the pin (eg GPIO_PULL_UP) or GPIO_PULL_UNKNOWN on failure
 */
uint32_t STDCALL gpio_device_pull_get(GPIO_DEVICE *gpio, uint32_t pin);

/**
 * @brief Change the pull state of a pin on the specified GPIO device
 * @param GPIO The GPIO device to set for
 * @param Pin The pin to change the pull state for (eg GPIO_PIN_1)
 * @param Mode The pull state to set for the pin (eg GPIO_PULL_UP)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 */
uint32_t STDCALL gpio_device_pull_select(GPIO_DEVICE *gpio, uint32_t pin, uint32_t mode);

/**
 * @brief Get the current function of a pin on the specified GPIO device
 * @param GPIO The GPIO device to get from
 * @param Pin The pin to get the function for (eg GPIO_PIN_1)
 * @return The current function of the pin (eg GPIO_FUNCTION_IN) or GPIO_FUNCTION_UNKNOWN on failure
 */
uint32_t STDCALL gpio_device_function_get(GPIO_DEVICE *gpio, uint32_t pin);

/**
 * @brief Change the function of a pin on the specified GPIO device
 * @param GPIO The GPIO device to set for
 * @param Pin The pin to change the function for (eg GPIO_PIN_1)
 * @param Mode The function to set for the pin (eg GPIO_FUNCTION_OUT)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 */
uint32_t STDCALL gpio_device_function_select(GPIO_DEVICE *gpio, uint32_t pin, uint32_t mode);

/**
 * @brief Get the properties for the specified GPIO device
 * @param GPIO The GPIO device to get properties from
 * @param Properties Pointer to a TGPIOProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Replaced by GPIODeviceGetProperties for consistency
 */
uint32_t STDCALL gpio_device_properties(GPIO_DEVICE *gpio, GPIO_PROPERTIES *properties);

/**
 * @brief Get the properties for the specified GPIO device
 * @param GPIO The GPIO device to get properties from
 * @param Properties Pointer to a TGPIOProperties structure to fill in
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL gpio_device_get_properties(GPIO_DEVICE *gpio, GPIO_PROPERTIES *properties);

/**
 * @brief Create a new GPIO entry
 * @return Pointer to new GPIO entry or nil if GPIO could not be created
 */
GPIO_DEVICE * STDCALL gpio_device_create(void);

/**
 * @brief Create a new GPIO entry
 * @param Size Size in bytes to allocate for new GPIO (Including the GPIO entry)
 * @return Pointer to new GPIO entry or nil if GPIO could not be created
 */
GPIO_DEVICE * STDCALL gpio_device_create_ex(uint32_t size);

/**
 * @brief Destroy an existing GPIO entry
 * @param GPIO The GPIO device to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL gpio_device_destroy(GPIO_DEVICE *gpio);

/**
 * @brief Register a new GPIO in the GPIO table
 * @param GPIO The GPIO device to register
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL gpio_device_register(GPIO_DEVICE *gpio);

/**
 * @brief Deregister a GPIO from the GPIO table
 * @param GPIO The GPIO device to deregister
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL gpio_device_deregister(GPIO_DEVICE *gpio);

/**
 * @brief Find a GPIO device by ID in the GPIO table
 * @param GPIOId The ID number of the GPIO device to find
 * @return Pointer to GPIO device entry or nil if not found
 */
GPIO_DEVICE * STDCALL gpio_device_find(uint32_t gpioid);

/**
 * @brief Find a GPIO device by name in the GPIO table
 * @param Name The name of the GPIO to find (eg GPIO0)
 * @return Pointer to GPIO device entry or nil if not found
 */
GPIO_DEVICE * STDCALL gpio_device_find_by_name(const char *name);

/**
 * @brief Find a GPIO device by description in the GPIO table
 * @param Description The description of the GPIO to find (eg BCM2836 GPIO)
 * @return Pointer to GPIO device entry or nil if not found
 */
GPIO_DEVICE * STDCALL gpio_device_find_by_description(const char *description);

/**
 * @brief Enumerate all GPIO devices in the GPIO table
 * @param Callback The callback function to call for each GPIO in the table
 * @param Data A private data pointer to pass to callback for each GPIO in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL gpio_device_enumerate(gpio_enumerate_cb callback, void *data);

/**
 * @brief Register a notification for GPIO device changes
 * @param GPIO The GPIO device to notify changes for (Optional, pass nil for all GPIO devices)
 * @param Callback The function to call when a notification event occurs
 * @param Data A private data pointer to pass to callback when a notification event occurs
 * @param Notification The events to register for notification of (eg DEVICE_NOTIFICATION_REGISTER)
 * @param Flags The flags to control the notification (eg NOTIFIER_FLAG_WORKER)
 */
uint32_t STDCALL gpio_device_notification(GPIO_DEVICE *gpio, gpio_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/** GPIO Helper Functions */

/**
 * @brief Get the current GPIO count
 */
uint32_t STDCALL gpio_get_count(void);

/**
 * @brief Get the current default GPIO device
 */
GPIO_DEVICE * STDCALL gpio_device_get_default(void);

/**
 * @brief Set the current default GPIO device
 */
uint32_t STDCALL gpio_device_set_default(GPIO_DEVICE *gpio);

/**
 * @brief Check if the supplied GPIO is in the GPIO table
 */
GPIO_DEVICE * STDCALL gpio_device_check(GPIO_DEVICE *gpio);

/**
 * @brief Convert a GPIO type value to a string
 */
uint32_t STDCALL gpio_type_to_string(uint32_t gpiotype, char *string, uint32_t len);

/**
 * @brief Convert a GPIO state value to a string
 */
uint32_t STDCALL gpio_state_to_string(uint32_t gpiostate, char *string, uint32_t len);

/**
 * @brief Create a new event using the supplied parameters
 * @note Event must be registered by calling GPIODeviceRegisterEvent
 * @note Caller must hold the GPIO device lock
 */
GPIO_EVENT * STDCALL gpio_device_create_event(GPIO_DEVICE *gpio, GPIO_PIN *pin, gpio_event_cb callback, void *data, uint32_t timeout);

/**
 * @brief Destroy an existing event
 * @note Event must be deregistered first by calling GPIODeviceDeregisterEvent
 * @note Caller must hold the GPIO device lock
 */
uint32_t STDCALL gpio_device_destroy_event(GPIO_DEVICE *gpio, GPIO_EVENT *event);

/**
 * @brief Register an event in the event list of the supplied Pin
 * @note Event must be created by calling GPIODeviceCreateEvent
 * @note Caller must hold the GPIO device lock
 */
uint32_t STDCALL gpio_device_register_event(GPIO_DEVICE *gpio, GPIO_PIN *pin, GPIO_EVENT *event);

/**
 * @brief Deregister an event from the event list of the supplied Pin
 * @note Event must be destroyed by calling GPIODeviceDestroyEvent
 * @note Caller must hold the GPIO device lock
 */
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