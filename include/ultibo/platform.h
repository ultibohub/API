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
#ifndef _ULTIBO_PLATFORM_H
#define _ULTIBO_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"

/** Platform specific constants */

/** Handle Flags */
#define HANDLE_FLAG_NONE	0x00000000
#define HANDLE_FLAG_NAMED	0x00000001 ///< Set if the handle has a name
#define HANDLE_FLAG_DUPLICATE	0x00000002 ///< Set if the handle can be duplicated

#define HANDLE_FLAG_INTERNAL	HANDLE_FLAG_NONE + 0x80000000 ///< Note: Temporary value to avoid warning

/** Handle constants */
#define HANDLE_SIGNATURE	0xCD15E20A

#define HANDLE_TABLE_MIN	0x100 ///< Minimum handle number (Skip first 256)
#define HANDLE_TABLE_MAX	0x7FFFFFFF ///< Maximum handle number (Avoid MSB as THandle is a signed value)

#define HANDLE_TABLE_MASK	0x7FF ///< 2048 buckets for handle lookups

#define HANDLE_NAME_LENGTH	256 ///< Maximum length of handle name

/** DMA Data Flags */
#define DMA_DATA_FLAG_NONE	0x00000000
#define DMA_DATA_FLAG_STRIDE	0x00000001 ///< Transfer from the source to the destination using 2D stride (If supported)
#define DMA_DATA_FLAG_SOURCE_NOINCREMENT	0x00000002 ///< Don't increment the source address during the DMA request (If supported)
#define DMA_DATA_FLAG_DEST_NOINCREMENT	0x00000004 ///< Don't increment the dest address during the DMA request (If supported)
#define DMA_DATA_FLAG_SOURCE_DREQ	0x00000008 ///< Use DREQ gating on the source address during the DMA request (If supported)
#define DMA_DATA_FLAG_DEST_DREQ	0x00000010 ///< Use DREQ gating on the dest address during the DMA request (If supported)
#define DMA_DATA_FLAG_SOURCE_WIDE	0x00000020 ///< Use wide reads on the source address during the DMA request (If supported)
#define DMA_DATA_FLAG_DEST_WIDE	0x00000040 ///< Use wide writes on the dest address during the DMA request (If supported)
#define DMA_DATA_FLAG_NOREAD	0x00000080 ///< Ignore the source address and zero fill the destination (If supported)
#define DMA_DATA_FLAG_NOWRITE	0x00000100 ///< Ignore the dest address and cache fill from the source (If supported)
#define DMA_DATA_FLAG_NOCLEAN	0x00000200 ///< Do not perform cache clean on the source address (If applicable)
#define DMA_DATA_FLAG_NOINVALIDATE	0x00000400 ///< Do not perform cache invalidate on the dest address (If applicable)
#define DMA_DATA_FLAG_BULK	0x00000800 ///< Perform a bulk transfer (Higher transfer throughput)(If applicable)
#define DMA_DATA_FLAG_LITE	0x00001000 ///< Perform a "lite" transfer (Lower transfer throughput but less waiting for free channel) (If applicable)
#define DMA_DATA_FLAG_40BIT	0x00002000 ///< Perform a 40-bit address transfer (Address to memory above 1GB or 4GB depending on SoC) (If applicable)

/** Page Table Flags */
#define PAGE_TABLE_FLAG_NONE	0x00000000
/** Reserved 0x00000001 (Previously used incorrectly for PAGE_TABLE_FLAG_NONE) */
#define PAGE_TABLE_FLAG_NORMAL	0x00000002 ///< Page Table Entry represents Normal memory
#define PAGE_TABLE_FLAG_DEVICE	0x00000004 ///< Page Table Entry represents Device memory
#define PAGE_TABLE_FLAG_ORDERED	0x00000008 ///< Page Table Entry represents Ordered memory
#define PAGE_TABLE_FLAG_SHARED	0x00000010 ///< Page Table Entry represents Shared memory
#define PAGE_TABLE_FLAG_CACHEABLE	0x00000020 ///< Page Table Entry represents Cacheable memory
#define PAGE_TABLE_FLAG_READONLY	0x00000040 ///< Page Table Entry represents Read Only memory
#define PAGE_TABLE_FLAG_READWRITE	0x00000080 ///< Page Table Entry represents Read Write memory
#define PAGE_TABLE_FLAG_EXECUTABLE	0x00000100 ///< Page Table Entry represents Executable memory
#define PAGE_TABLE_FLAG_WRITEBACK	0x00000200 ///< Page Table Entry is Writeback Cacheable memory
#define PAGE_TABLE_FLAG_WRITETHROUGH	0x00000400 ///< Page Table Entry is Writethrough Cacheable memory
#define PAGE_TABLE_FLAG_WRITEALLOCATE	0x00000800 ///< Page Table Entry is Writeallocate Cacheable memory
#if defined (__i386__) || defined (__arm__)
#define PAGE_TABLE_FLAG_LARGEADDRESS	0x00001000 ///< Page Table Entry is mapped to Large Physical Address range
#endif

/** Interrupt Entry Flags */
#define INTERRUPT_FLAG_NONE	0x00000000
#define INTERRUPT_FLAG_SHARED	0x00000001 ///< A shared interrupt, multiple devices can register for the same interrupt and each will be called until one returns INTERRUPT_RETURN_HANDLED
#define INTERRUPT_FLAG_LOCAL	0x00000002 ///< A local interrupt, generated only on the CPU it is associated with
#define INTERRUPT_FLAG_IPI	0x00000004 ///< A software interrupt or inter processor interrupt, generated by a software request instead of hardware
#define INTERRUPT_FLAG_FIQ	0x00000008 ///< A fast interrupt, takes precedence over all other interrupts (where applicable)
#define INTERRUPT_FLAG_CHAINED	0x00000010 ///< A chained interrupt, multiple devices can register for the same interrupt and all will be called when it occurs

/** Interrupt Priority Values */
#define INTERRUPT_PRIORITY_MAXIMUM	0x00
#define INTERRUPT_PRIORITY_FIQ	0x40
#define INTERRUPT_PRIORITY_DEFAULT	0xA0
#define INTERRUPT_PRIORITY_MINIMUM	0xF0

/** Interrupt Return Values */
#define INTERRUPT_RETURN_NONE	0 ///< Shared interrupt not handled or not for this device
#define INTERRUPT_RETURN_HANDLED	1 ///< Shared interrupt handled, no further processing

/** Vector Table Entries */
/** ARM */
#define VECTOR_TABLE_ENTRY_ARM_RESET	0 ///< ARM Reset Vector
#define VECTOR_TABLE_ENTRY_ARM_UNDEFINED	1 ///< ARM Undefined Vector
#define VECTOR_TABLE_ENTRY_ARM_SWI	2 ///< ARM Software Interrupt (SWI) Vector
#define VECTOR_TABLE_ENTRY_ARM_PREFETCH	3 ///< ARM Prefetch Abort Vector
#define VECTOR_TABLE_ENTRY_ARM_ABORT	4 ///< ARM Data Abort Vector
#define VECTOR_TABLE_ENTRY_ARM_RESERVED	5 ///< ARM Reserved Vector
#define VECTOR_TABLE_ENTRY_ARM_IRQ	6 ///< ARM IRQ Vector
#define VECTOR_TABLE_ENTRY_ARM_FIQ	7 ///< ARM FIQ Vector
/** AARCH64 */

/** Shutdown Flags */
#define SHUTDOWN_FLAG_NONE	0x00000000
#define SHUTDOWN_FLAG_RESTART	0x00000001 ///< The system is shutting down and restarting
#define SHUTDOWN_FLAG_FORCE	0x00000002 ///< Forced shutdown or restart requested, registered callbacks will be bypassed

/** Shutdown constants */
#define SHUTDOWN_SIGNATURE	0xA73D8B0C

#define SHUTDOWN_DEFAULT_DELAY	1000 ///< Default delay before starting a shutdown or restart (Milliseconds)
#define SHUTDOWN_MINIMUM_DELAY	10 ///< Minimum delay before starting a shutdown or restart (Milliseconds)

#define SHUTDOWN_DEFAULT_TIMEOUT	5000 ///< Default time to wait for a shutdown callback to complete before continuing (Milliseconds)

/** Exception Types */
#define EXCEPTION_TYPE_DATA_ABORT	1
#define EXCEPTION_TYPE_PREFETCH_ABORT	2
#define EXCEPTION_TYPE_UNDEFINED_INSTRUCTION	3

/** Firmware Throttling Flags */
#define FIRMWARE_THROTTLE_NONE	(0 << 0)
#define FIRMWARE_THROTTLE_UNDER_VOLTAGE	(1 << 0) ///< Under voltage is occurring
#define FIRMWARE_THROTTLE_FREQUENCY_LIMIT	(1 << 1) ///< Frequency limiting is occurring
#define FIRMWARE_THROTTLE_THROTTLED	(1 << 2) ///< Throttling is occurring
#define FIRMWARE_THROTTLE_SOFT_TEMP_LIMIT	(1 << 3) ///< Soft temperature limit is active
#define FIRMWARE_THROTTLE_WAS_UNDER_VOLTAGE	(1 << 16) ///< Under voltage has occurred
#define FIRMWARE_THROTTLE_WAS_FREQUENCY_LIMIT	(1 << 17) ///< Frequency limiting has occurred
#define FIRMWARE_THROTTLE_WAS_THROTTLED	(1 << 18) ///< Throttling has occurred
#define FIRMWARE_THROTTLE_WAS_SOFT_TEMP_LIMIT	(1 << 19) ///< Soft temperature limit has occurred

/** Platform specific types */

/** IRQ/FIQ Masks */
typedef uint32_t IRQ_MASK;
typedef uint32_t FIQ_MASK;
typedef uint32_t IRQ_FIQ_MASK;

/** Abort Masks */
typedef uint32_t ABORT_MASK;

/** DMA Data */
typedef struct _DMA_DATA DMA_DATA;
struct _DMA_DATA
{
	// Data Properties
	void *source; ///< Source address for DMA (May need to be allocated in accordance with DMA host configuration)
	#if defined (__i386__) || defined (__arm__)
	uint32_t sourcerange; ///< Source address range for DMA (Only applicable when performing a 40-bit transfer)
	#endif
	void *dest; ///< Dest address for DMA (May need to be allocated in accordance with DMA host configuration)
	#if defined (__i386__) || defined (__arm__)
	uint32_t destrange; ///< Dest address range for DMA (Only applicable when performing a 40-bit transfer)
	#endif
	uint32_t size; ///< Size for DMA transfer (For 2D stride the length of a row multiplied by the count of rows)
	uint32_t flags; ///< Flags for DMA transfer (See DMA_DATA_FLAG_* above)
	// Stride Properties
	uint32_t stridelength; ///< Length of each row during 2D stride (If supported)
	int32_t sourcestride; ///< Increment between rows for source address during 2D stride (If supported)
	int32_t deststride; ///< Increment between rows for destination address during 2D stride (If supported)
	// Next Block
	DMA_DATA *next; ///< Link to next DMA data block (or nil for the last block)
};

/** System Call Request (SWI) */
typedef struct _SYSTEM_CALL_REQUEST SYSTEM_CALL_REQUEST;
struct _SYSTEM_CALL_REQUEST
{
	uint32_t number;
	size_t param1;
	size_t param2;
	size_t param3;
};

/** Prototypes for Handle methods */
typedef void STDCALL (*handle_close_proc)(HANDLE data);
typedef uint32_t STDCALL (*handle_close_ex_proc)(HANDLE data);
typedef HANDLE STDCALL (*handle_duplicate_proc)(HANDLE data);

/** Handle Entry */
typedef struct _HANDLE_ENTRY HANDLE_ENTRY;

/** Handle Enumeration Callback */
typedef uint32_t STDCALL (*handle_enumerate_cb)(HANDLE_ENTRY *handle, void *data);

struct _HANDLE_ENTRY
{
	// Handle Properties
	uint32_t signature; ///< Signature for entry validation
	HANDLE handle; ///< Handle (Number) of this Handle
	uint32_t handletype; ///< Type of this Handle (eg HANDLE_TYPE_FILE)
	uint32_t count; ///< Reference Count of the Handle
	uint32_t flags; ///< Flags for the Handle (eg HANDLE_FLAG_NAMED)
	char *name; ///< The name of the Handle (Optional)
	uint32_t hash; ///< Hash of the Handle name (Only if named)
	HANDLE data; ///< Purpose specific data for the Handle (eg a file handle or a socket handle)
	handle_close_proc close; ///< Procedure to call on final close (Optional)
	handle_close_ex_proc closeex; ///< Function to call on final close (Optional)
	handle_duplicate_proc duplicate; ///< Function to call when duplicating handle (Optional)
	// Internal Properties
	HANDLE_ENTRY *prev; ///< Previous entry in Handle table
	HANDLE_ENTRY *next; ///< Next entry in Handle table
	// Statistics Properties
};

/** Prototype for Shutdown Callback */
typedef uint32_t STDCALL (*shutdown_cb)(uint32_t flags, void *parameter);

/** Prototypes for Interrupt (IRQ/FIQ) Handlers */
typedef void STDCALL (*interrupt_handler)(void *parameter);
typedef THREAD_HANDLE STDCALL (*interrupt_ex_handler)(uint32_t cpuid, THREAD_HANDLE thread, void *parameter);
typedef uint32_t STDCALL (*shared_interrupt_handler)(uint32_t number, uint32_t cpuid, uint32_t flags, void *parameter);

/** Interrupt Entry (IRQ/FIQ */
typedef struct _INTERRUPT_ENTRY INTERRUPT_ENTRY;
struct _INTERRUPT_ENTRY
{
	// Interrupt Properties
	uint32_t number;
	uint32_t flags;
	uint32_t cpumask;
	uint32_t priority;
	interrupt_handler handler;
	interrupt_ex_handler handlerex;
	shared_interrupt_handler sharedhandler;
	void *parameter;
	// Internal Properties
	INTERRUPT_ENTRY *prev;
	INTERRUPT_ENTRY *next;
};

/** System Call Entry (SWI) */
typedef struct _SYSTEM_CALL_ENTRY SYSTEM_CALL_ENTRY;
struct _SYSTEM_CALL_ENTRY
{
	uint32_t number;
	uint32_t cpuid;
    void STDCALL (*handler)(SYSTEM_CALL_REQUEST *request);
    THREAD_HANDLE STDCALL (*handlerex)(uint32_t cpuid, THREAD_HANDLE thread, SYSTEM_CALL_REQUEST *request);
};

/** Page Table Entry */
typedef struct _PAGE_TABLE_ENTRY PAGE_TABLE_ENTRY;
struct _PAGE_TABLE_ENTRY
{
	size_t virtualaddress;
#if defined (__i386__) || defined (__arm__)
	uint32_t physicalrange; ///< Physical Address Range referenced by entry when using Large Physical Address Extensions (LPAE)
#endif
	size_t physicaladdress;
	uint32_t size;
	uint32_t flags;
};

/** Prototype for Inter Processor Interrupt (IPI) Handlers */
/** Note: When used for IPI the CPUID parameter will be the sending CPU */
typedef shared_interrupt_handler ipi_handler;

/** Prototype for System Call (SWI) Handlers */
typedef void STDCALL (*system_call_handler)(SYSTEM_CALL_REQUEST *request);
typedef THREAD_HANDLE STDCALL (*system_call_ex_handler)(uint32_t cpuid, THREAD_HANDLE thread, SYSTEM_CALL_REQUEST *request);

/** Prototypes for Thread Yield/Wait/Release/Abandon Handlers */
typedef uint32_t STDCALL (*thread_yield_proc)(void);
typedef uint32_t STDCALL (*thread_wait_proc)(LIST_HANDLE list, SPIN_HANDLE lock, uint32_t flags);
typedef uint32_t STDCALL (*thread_wait_ex_proc)(LIST_HANDLE list, SPIN_HANDLE lock, uint32_t flags, uint32_t timeout);
typedef uint32_t STDCALL (*thread_release_proc)(LIST_HANDLE list);
typedef uint32_t STDCALL (*thread_abandon_proc)(LIST_HANDLE list);

/** Prototype for Timer Event Handler */
typedef void STDCALL (*timer_event_proc)(void *data);

/** Prototype for Worker Task/Callback Handlers */
typedef void STDCALL (*worker_task_proc)(void *data);
typedef void STDCALL (*worker_cb)(void *data);

/** Prototype for Counter Callback Handlers */
typedef void STDCALL (*counter_event_cb)(void *data);

/** Prototype for GPIO Callback Handlers */
typedef void STDCALL (*gpio_event_cb)(void *data, uint32_t pin, uint32_t trigger);

/** Device Tree Functions */

/**
 * @brief Check if valid Device Tree information was provided by the firmware/bootloader
 */
BOOL STDCALL device_tree_valid(void);

/**
 * @brief Get the base address of the Device Tree Blob (Where Applicable)
 */
size_t STDCALL device_tree_get_base(void);

/**
 * @brief Get the total size of the Device Tree Blob (Where Applicable)
 */
uint32_t STDCALL device_tree_get_size(void);

/**
 * @brief Read the raw value of a Device Tree property (Where Applicable)
 * @param Path The path of the requested property
 * @param Name The name of the requested property
 * @param Buffer A pointer to a buffer to receive the raw value
 * @param Size The size in byte of the buffer, updated on return with the actual size of the value
 * @return ERROR_SUCCESS if the property value was read or another error code on failure
 */
uint32_t STDCALL device_tree_read(const char *path, const char *name, void *buffer, uint32_t *size);

/**
 * @brief Read a 32-bit value from a Device Tree property (Where Applicable)
 * @param Path The path of the requested property
 * @param Name The name of the requested property
 * @param Value The returned value of the property
 * @return ERROR_SUCCESS if the property value was read or another error code on failure
 */
uint32_t STDCALL device_tree_read32(const char *path, const char *name, uint32_t *value);

/**
 * @brief Read a 64-bit value from a Device Tree property (Where Applicable)
 * @param Path The path of the requested property
 * @param Name The name of the requested property
 * @param Value The returned value of the property
 * @return ERROR_SUCCESS if the property value was read or another error code on failure
 */
uint32_t STDCALL device_tree_read64(const char *path, const char *name, uint64_t *value);

/**
 * @brief Read a string value from a Device Tree property (Where Applicable)
 * @param Path The path of the requested property
 * @param Name The name of the requested property
 * @param Value The returned value of the property
 * @return ERROR_SUCCESS if the property value was read or another error code on failure
 */
uint32_t STDCALL device_tree_read_string(const char *path, const char *name, char *value, uint32_t len);

/** Boot Functions */

/**
 * @brief Blink the Activity LED (Where Applicable)
 * @note Intended for startup diagnostics when bootstrapping a new board
 */
void STDCALL boot_blink(void);

/**
 * @brief Output boot time information (Where Applicable)
 * @note Intended for startup diagnostics when bootstrapping a new board
 */
void STDCALL boot_output(uint32_t value);

/**
 * @brief Start the boot time console display (Where Applicable)
 * @note Intended for startup diagnostics when bootstrapping a new board
 */
void STDCALL boot_console_start(void);

/**
 * @brief Output text to the boot time console display (Where Applicable)
 * @note Intended for startup diagnostics when bootstrapping a new board
 */
void STDCALL boot_console_write(const char *value);

/**
 * @brief Output text to the boot time console display at the specified X and Y position (Where Applicable)
 * @note Intended for startup diagnostics when bootstrapping a new board
 */
void STDCALL boot_console_write_ex(const char *value, uint32_t x, uint32_t y);

/**
 * @brief Get the current X position of the boot time console display (Where Applicable)
 * @note Intended for startup diagnostics when bootstrapping a new board
 */
uint32_t STDCALL boot_console_get_x(void);

/**
 * @brief Get the current Y position of the boot time console display (Where Applicable)
 * @note Intended for startup diagnostics when bootstrapping a new board
 */
uint32_t STDCALL boot_console_get_y(void);

/** LED Functions */

/**
 * @brief Enable the Power LED (Where Applicable)
 */
void STDCALL power_led_enable(void);

/**
 * @brief Turn On the Power LED (Where Applicable)
 */
void STDCALL power_led_on(void);

/**
 * @brief Turn Off the Power LED (Where Applicable)
 */
void STDCALL power_led_off(void);

/**
 * @brief Enable the Activity LED (Where Applicable)
 */
void STDCALL activity_led_enable(void);

/**
 * @brief Turn On the Activity LED (Where Applicable)
 */
void STDCALL activity_led_on(void);

/**
 * @brief Turn Off the Activity LED (Where Applicable)
 */
void STDCALL activity_led_off(void);

/** Counter Functions (Timer device) */

/**
 * @brief Check if a counter is currently available
 */
BOOL STDCALL counter_available(void);

/**
 * @brief Read the current value of the default counter
 * @return The 32 bit current value of the counter or 0 on failure
 */
uint32_t STDCALL counter_read(void);

/**
 * @brief Read the current value of the default counter
 * @return The 64 bit current value of the counter or 0 on failure
 */
int64_t STDCALL counter_read64(void);

/**
 * @brief Wait for the current interval to expire on the default counter
 * @return ERROR_SUCCESS if the interval expired or another error code on failure
 */
uint32_t STDCALL counter_wait(void);

/**
 * @brief Schedule a function to be called when the current interval expires on the default counter
 * @param Callback The function to be called when the interval expires
 * @param Data A pointer to be pass to the function when the interval expires (Optional)
 * @return ERROR_SUCCESS if the callback was scheduled successfully or another error code on failure
 */
uint32_t STDCALL counter_event(counter_event_cb callback, void *data);

/**
 * @brief Cancel a previously scheduled event callback function on the default counter
 * @return ERROR_SUCCESS if the callback was cancelled successfully or another error code on failure
 */
uint32_t STDCALL counter_cancel(void);

/**
 * @brief Get the current clock rate in Hz of the default counter
 * @return The current clock rate in Hz or 0 on failure
 */
uint32_t STDCALL counter_get_rate(void);

/**
 * @brief Set the current clock rate in Hz of the default counter
 * @param Rate The clock rate in Hz to set
 * @return ERROR_SUCCESS if the clock rate was set or another error code on failure
 */
uint32_t STDCALL counter_set_rate(uint32_t rate);

/**
 * @brief Get the current interval in ticks of the default counter
 * @return The current interval in ticks or 0 on failure (or not set)
 * @note The tick rate is determined by the clock rate
 */
uint32_t STDCALL counter_get_interval(void);

/**
 * @brief Set the current interval in ticks of the default counter
 * @param Interval The interval in ticks to set
 * @return ERROR_SUCCESS if the interval was set or another error code on failure
 * @note The tick rate is determined by the clock rate
 */
uint32_t STDCALL counter_set_interval(uint32_t interval);

/** Mailbox Functions */

/**
 * @brief Receive from specified mailbox on specified channel
 */
uint32_t STDCALL mailbox_receive(uint32_t mailbox, uint32_t channel);

/**
 * @brief Send to specified mailbox on specified channel
 */
void STDCALL mailbox_send(uint32_t mailbox, uint32_t channel, uint32_t data);

/**
 * @brief Perform a transaction (Send/Receive) to specified mailbox on specified channel
 */
uint32_t STDCALL mailbox_call(uint32_t mailbox, uint32_t channel, uint32_t data, uint32_t *response);

/**
 * @brief Perform a transaction (Send/Receive) to specified mailbox on specified channel
 */
uint32_t STDCALL mailbox_call_ex(uint32_t mailbox, uint32_t channel, uint32_t data, uint32_t *response, uint32_t timeout);

/**
 * @brief Perform a property tag transaction (Send/Receive) to specified mailbox on specified channel
 */
uint32_t STDCALL mailbox_property_call(uint32_t mailbox, uint32_t channel, void *data, uint32_t *response);

/**
 * @brief Perform a property tag transaction (Send/Receive) to specified mailbox on specified channel
 */
uint32_t STDCALL mailbox_property_call_ex(uint32_t mailbox, uint32_t channel, void *data, uint32_t *response, uint32_t timeout);

/**
 * @brief Request a property tag (Get/Set) from the mailbox property channel
 */
uint32_t STDCALL mailbox_property_tag(uint32_t tag, void *data, uint32_t size);

/** Random Number Functions */

/**
 * @brief Check if a hardware random number generator is currently available
 * The software random number generator from the RTL is always available
 */
BOOL STDCALL random_available(void);

void STDCALL random_seed(uint32_t seed);

int32_t STDCALL random_read_longint(int32_t limit);
int64_t STDCALL random_read_int64(int64_t limit);
double_t STDCALL random_read_double(void);

/**
 * @note Replaced by RandomReadDouble
 */
double_t STDCALL random_read_extended(void);

/** Watchdog Functions */

/**
 * @brief Check if a watchdog timer is currently available
 */
BOOL STDCALL watchdog_available(void);

uint32_t STDCALL watchdog_start(uint32_t milliseconds);
uint32_t STDCALL watchdog_stop(void);
uint32_t STDCALL watchdog_refresh(uint32_t milliseconds);

/** Interrupt Request (IRQ) Functions */

/**
 * @brief Request registration of the supplied handler to the specified IRQ number
 * @param CPUID CPU to route IRQ to
 * @param Number IRQ number to register
 * @param Handler Interrupt handler function to register
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note If the IRQ number is already registered then the request will fail
 */
uint32_t STDCALL request_irq(uint32_t cpuid, uint32_t number, interrupt_handler handler, void *parameter);

/**
 * @brief Request deregistration of the supplied handler from the specified IRQ number
 * @param CPUID CPU to unroute IRQ from
 * @param Number IRQ number to deregister
 * @param Handler Interrupt handler function to deregister
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note If the IRQ number is not currently registered then the request will fail
 */
uint32_t STDCALL release_irq(uint32_t cpuid, uint32_t number, interrupt_handler handler, void *parameter);

/**
 * @brief Request registration of the supplied extended handler to the specified IRQ number
 * @param CPUID CPU to route IRQ to
 * @param Number IRQ number to register
 * @param Handler Interrupt handler function to register
 * @param HandlerEx Extended Interrupt handler function to register
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note Only one of Handler or HandlerEx can be specified
 * @note If the IRQ number is already registered then the request will fail
 */
uint32_t STDCALL request_ex_irq(uint32_t cpuid, uint32_t number, interrupt_handler handler, interrupt_ex_handler handlerex, void *parameter);

/**
 * @brief Request deregistration of the supplied extended handler from the specified IRQ number
 * @param CPUID CPU to unroute IRQ from
 * @param Number IRQ number to deregister
 * @param Handler Interrupt handler function to deregister
 * @param HandlerEx Extended Interrupt handler function to deregister
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note Only one of Handler or HandlerEx can be specified
 * @note If the IRQ number is not currently registered then the request will fail
 */
uint32_t STDCALL release_ex_irq(uint32_t cpuid, uint32_t number, interrupt_handler handler, interrupt_ex_handler handlerex, void *parameter);

/** Fast Interrupt Request (FIQ) Functions */

/**
 * @brief Request registration of the supplied handler to the specified FIQ number (Where Applicable)
 * @param CPUID CPU to route FIQ to
 * @param Number FIQ number to register
 * @param Handler Interrupt handler function to register
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note If the FIQ number is already registered then the request will fail
 */
uint32_t STDCALL request_fiq(uint32_t cpuid, uint32_t number, interrupt_handler handler, void *parameter);

/**
 * @brief Request deregistration of the supplied handler from the specified FIQ number (Where Applicable)
 * @param CPUID CPU to unroute FIQ from
 * @param Number FIQ number to deregister
 * @param Handler Interrupt handler function to deregister
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note If the FIQ number is not currently registered then the request will fail
 */
uint32_t STDCALL release_fiq(uint32_t cpuid, uint32_t number, interrupt_handler handler, void *parameter);

/**
 * @brief Request registration of the supplied extended handler to the specified FIQ number (Where Applicable)
 * @param CPUID CPU to route FIQ to
 * @param Number FIQ number to register
 * @param Handler Interrupt handler function to register
 * @param HandlerEx Extended Interrupt handler function to register
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note Only one of Handler or HandlerEx can be specified
 * @note If the FIQ number is already registered then the request will fail
 */
uint32_t STDCALL request_ex_fiq(uint32_t cpuid, uint32_t number, interrupt_handler handler, interrupt_ex_handler handlerex, void *parameter);

/**
 * @brief Request deregistration of the supplied extended handler from the specified FIQ number (Where Applicable)
 * @param CPUID CPU to unroute FIQ from
 * @param Number FIQ number to deregister
 * @param Handler Interrupt handler function to deregister
 * @param HandlerEx Extended Interrupt handler function to deregister
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note Only one of Handler or HandlerEx can be specified
 * @note If the FIQ number is not currently registered then the request will fail
 */
uint32_t STDCALL release_ex_fiq(uint32_t cpuid, uint32_t number, interrupt_handler handler, interrupt_ex_handler handlerex, void *parameter);

/** Inter Processor Interrupt (IPI) Functions */

/**
 * @brief Request registration of the supplied handler to the specified IPI (Inter-processor interrupt) number (Where Applicable)
 * @param CPUID CPU to route IPI to
 * @param Number IPI number to register
 * @param Handler Interrupt handler function to register
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note If the IPI number is already registered then the request will fail
 */
uint32_t STDCALL request_ipi(uint32_t cpuid, uint32_t number, ipi_handler handler, void *parameter);

/**
 * @brief Request deregistration of the supplied handler from the specified IPI (Inter-processor interrupt) number (Where Applicable)
 * @param CPUID CPU to unroute IPI from
 * @param Number IPI number to deregister
 * @param Handler Interrupt handler function to deregister
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @note If the IPI number is not currently registered then the request will fail
 */
uint32_t STDCALL release_ipi(uint32_t cpuid, uint32_t number, ipi_handler handler, void *parameter);

/** Interrupt Register/Deregister Functions */

/**
 * @brief Request registration of the supplied handler to the specified interrupt number (Where Applicable)
 * @param Number The interrupt number to register the handler for
 * @param Mask The mask of CPUs to register the handler for (eg CPU_MASK_0, CPU_MASK_1) (Where Applicable)
 * @param Priority The priority level of the interrupt to be registered (eg INTERRUPT_PRIORITY_MAXIMUM) (Where Applicable)
 * @param Flags The flags to control the registration of the interrupt (eg INTERRUPT_FLAG_SHARED) (Where Applicable)
 * @param Handler The shared interrupt handler to be called when the interrupt occurs
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @return ERROR_SUCCESS if the callback was scheduled successfully or another error code on failure
 */
uint32_t STDCALL register_interrupt(uint32_t number, uint32_t mask, uint32_t priority, uint32_t flags, shared_interrupt_handler handler, void *parameter);

/**
 * @brief Request deregistration of the supplied handler from the specified interrupt number (Where Applicable)
 * @param Number The interrupt number to deregister the hanlder for
 * @param Mask The mask of CPUs to deregister the handler for (eg CPU_MASK_0, CPU_MASK_1) (Where Applicable)
 * @param Priority The priority level of the interrupt to be deregistered (eg INTERRUPT_PRIORITY_MAXIMUM) (Where Applicable)
 * @param Flags The flags to control the deregistration of the interrupt (eg INTERRUPT_FLAG_SHARED, INTERRUPT_FLAG_LOCAL, INTERRUPT_FLAG_FIQ) (Where Applicable)
 * @param Handler The shared interrupt handler to be called when the interrupt occurs
 * @param Parameter A pointer to be passed to the handler when the interrupt occurs (Optional)
 * @return ERROR_SUCCESS if the callback was scheduled successfully or another error code on failure
 */
uint32_t STDCALL deregister_interrupt(uint32_t number, uint32_t mask, uint32_t priority, uint32_t flags, shared_interrupt_handler handler, void *parameter);

/** System Call (SWI) Functions */

/**
 * @brief Perform a System Call function with the supplied parameters (Where Applicable)
 * @param Number The System Call number to be called
 * @param Param1 The first parameter to pass to the function (Optional / Function defined)
 * @param Param2 The second parameter to pass to the function (Optional / Function defined)
 * @param Param3 The third parameter to pass to the function (Optional / Function defined)
 */
void STDCALL system_call(uint32_t number, size_t param1, size_t param2, size_t param3);

/**
 * @brief Request registration of the supplied handler to the specified System Call number (Where Applicable)
 * @param Number The System Call number to be registered
 * @param Handler The handler function to be registered
 * @note If the System Call number is already registered then the request will fail
 */
uint32_t STDCALL register_system_call(uint32_t number, system_call_handler handler);

/**
 * @brief Request deregistration of the supplied handler from the specified System Call number (Where Applicable)
 * @param Number The System Call number to be deregistered
 * @param Handler The handler function to be deregistered
 * @note If the System Call number is not currently registered then the request will fail
 */
uint32_t STDCALL deregister_system_call(uint32_t number, system_call_handler handler);

/**
 * @brief Request registration of the supplied extended handler to the specified System Call number (Where Applicable)
 * @param CPUID The CPU ID to register the System Call against (or CPU_ID_ALL)
 * @param Number The System Call number to be registered
 * @param Handler The handler function to be registered (Optional) (Handler or HandlerEx must be specified, not both)
 * @param HandlerEx The extended handler function to be registered (Optional) (Handler or HandlerEx must be specified, not both)
 * @note If the System Call number is already registered then the request will fail
 */
uint32_t STDCALL register_system_call_ex(uint32_t cpuid, uint32_t number, system_call_handler handler, system_call_ex_handler handlerex);

/**
 * @brief Request deregistration of the supplied extended handler from the specified System Call number (Where Applicable)
 * @param CPUID The CPU ID to deregister the System Call from (or CPU_ID_ALL)
 * @param Number The System Call number to be deregistered
 * @param Handler The handler function to be deregistered (Optional) (Handler or HandlerEx must be specified, not both)
 * @param HandlerEx The extended handler function to be deregistered (Optional) (Handler or HandlerEx must be specified, not both)
 * @note If the System Call number is not currently registered then the request will fail
 */
uint32_t STDCALL deregister_system_call_ex(uint32_t cpuid, uint32_t number, system_call_handler handler, system_call_ex_handler handlerex);

/** Interrupt Entry Functions */

/**
 * @brief Get the number of interrupt entries for the current platform
 */
uint32_t STDCALL get_interrupt_count(void);

/**
 * @brief Get the starting number of interrupt entries for the current platform
 */
uint32_t STDCALL get_interrupt_start(void);

/**
 * @brief Get the interrupt entry for the specified interrupt number and instance
 */
uint32_t STDCALL get_interrupt_entry(uint32_t number, uint32_t instance, INTERRUPT_ENTRY *interrupt);

/** Local Interrupt Entry Functions */

/**
 * @brief Get the number of local interrupt entries for the current platform (Where Applicable)
 */
uint32_t STDCALL get_local_interrupt_count(void);

/**
 * @brief Get the starting number of local interrupt entries for the current platform (Where Applicable)
 */
uint32_t STDCALL get_local_interrupt_start(void);

/**
 * @brief Get the local interrupt entry for the specified interrupt number (Where Applicable)
 */
uint32_t STDCALL get_local_interrupt_entry(uint32_t cpuid, uint32_t number, uint32_t instance, INTERRUPT_ENTRY *interrupt);

/** Software Interrupt Entry (IPI) Functions */

/**
 * @brief Get the number of software interrupt entries for the current platform (Where Applicable)
 */
uint32_t STDCALL get_software_interrupt_count(void);

/**
 * @brief Get the starting number of software interrupt entries for the current platform (Where Applicable)
 */
uint32_t STDCALL get_software_interrupt_start(void);

/**
 * @brief Get the software interrupt entry for the specified interrupt number and instance (Where Applicable)
 */
uint32_t STDCALL get_software_interrupt_entry(uint32_t cpuid, uint32_t number, uint32_t instance, INTERRUPT_ENTRY *interrupt);

/** System Call Entry Functions */

/**
 * @brief Get the number of system call entries for the current platform (Where Applicable)
 */
uint32_t STDCALL get_system_call_count(void);

/**
 * @brief Get the system call entry for the specified system call number (Where Applicable)
 */
SYSTEM_CALL_ENTRY STDCALL get_system_call_entry(uint32_t number);

/** System Functions */

/**
 * @brief Restart the system
 * @param Delay How long to delay before commencing the restart (Milliseconds)
 * @return ERROR_SUCCESS if the restart was successfully initiated or another error code on failure
 */
uint32_t STDCALL system_restart(uint32_t delay);

/**
 * @brief Shutdown the system
 * @param Delay How long to delay before commencing the shutdown (Milliseconds)
 * @return ERROR_SUCCESS if the shutdown was successfully initiated or another error code on failure
 */
uint32_t STDCALL system_shutdown(uint32_t delay);

/**
 * @brief Register a procedure to be called during system shutdown or restart
 * @param Callback The procedure to be called on shutdown or restart
 * @param Parameter A pointer to be passed to the callback procedure
 * @param Timeout Time the shutdown process should wait for this callback to complete (0 for the default timeout) (Milliseconds)
 * @return ERROR_SUCCESS if the callback was successfully registered or another error code on failure
 */
uint32_t STDCALL system_register_shutdown(shutdown_cb callback, void *parameter, uint32_t timeout);

/**
 * @brief Deregister a procedure from being called during system shutdown or restart
 * @param Callback The procedure previously registered for shutdown or restart
 * @param Parameter The pointer previously registered for the callback procedure
 * @return ERROR_SUCCESS if the callback was successfully deregistered or another error code on failure
 */
uint32_t STDCALL system_deregister_shutdown(shutdown_cb callback, void *parameter);

/**
 * @brief Get the current system up time in 100 nanosecond ticks since 1 January 1601
 * @return The current system up time
 * @note This is the same time format as Windows FILE_TIME and is intended to allow
 *  compatibility with file system functions etc.
 */
int64_t STDCALL system_get_uptime(void);

/**
 * @brief Get the current command line
 */
uint32_t STDCALL system_get_command_line(char *commandline, uint32_t len);

/**
 * @brief Get the current environment
 */
void * STDCALL system_get_environment(void);

/**
 * @brief Return the supplied date value as a string in the system defined format
 * @param Date The date in Pascal TDateTime format
 * @return The date formatted according to the system date format
 * @note Applications should use FormatDateTime or DateTimeToString directly
 *       This function is intended to provide a uniform and generic date and
 *       time output from system functions such as logging and debug output
 */
uint32_t STDCALL system_date_to_string(double_t date, char *value, uint32_t len);

/**
 * @brief Return the supplied time value as a string in the system defined format
 * @param Time The time in Pascal TDateTime format
 * @return The time formatted according to the system time format
 * @note Applications should use FormatDateTime or DateTimeToString directly
 *       This function is intended to provide a uniform and generic date and
 *       time output from system functions such as logging and debug output
 */
uint32_t STDCALL system_time_to_string(double_t time, char *value, uint32_t len);

/**
 * @brief Return the supplied date and time value as a string in the system defined format
 * @param DateTime The date and time in Pascal TDateTime format
 * @return The date and time formatted according to the system date and time format
 * @note Applications should use FormatDateTime or DateTimeToString directly
 *       This function is intended to provide a uniform and generic date and
 *       time output from system functions such as logging and debug output
 */
uint32_t STDCALL system_date_time_to_string(double_t datetime, char *value, uint32_t len);

/**
 * @brief Return the supplied time interval as a string in the system defined format
 * @param Interval The time interval in Pascal TDateTime format
 * @return The time interval formatted according to the system time format
 */
uint32_t STDCALL system_interval_to_string(double_t interval, char *value, uint32_t len);

/** CPU Functions */

/**
 * @brief Get the CPU architecture for this board
 */
uint32_t STDCALL cpu_get_arch(void);

/**
 * @brief Get the CPU type for this board
 */
uint32_t STDCALL cpu_get_type(void);

/**
 * @brief Get the boot CPU for this board
 */
uint32_t STDCALL cpu_get_boot(void);

/**
 * @brief Get the CPU mask for this board
 */
uint32_t STDCALL cpu_get_mask(void);

/**
 * @brief Get the CPU count for this board
 */
uint32_t STDCALL cpu_get_count(void);

/**
 * @brief Get the current CPU mode
 * @note The return value is specific to the CPU type
 */
uint32_t STDCALL cpu_get_mode(void);

/**
 * @brief Get the current CPU state
 */
uint32_t STDCALL cpu_get_state(void);

/**
 * @brief Get the current CPU group
 */
uint32_t STDCALL cpu_get_group(void);

/**
 * @brief Get the current CPU ID
 */
uint32_t STDCALL cpu_get_current(void);

/**
 * @brief Get the memory start and size available to the CPU
 */
uint32_t STDCALL cpu_get_memory(size_t *address, uint64_t *length);

/**
 * @brief Get the last second utilization of the specified CPU in percentage
 * @param CPUID The CPU to get utilization from or CPU_ID_ALL for average of all CPUs
 */
double_t STDCALL cpu_get_percentage(uint32_t cpuid);

/**
 * @brief Get the last second utilization of the specified CPU
 * @param CPUID The CPU to get utilization from or CPU_ID_ALL for average of all CPUs
 */
uint32_t STDCALL cpu_get_utilization(uint32_t cpuid);

/**
 * @brief Get the CPU model of the current CPU
 */
uint32_t STDCALL cpu_get_model(void);

/**
 * @brief Get the CPU revision of the current CPU
 * @note The return value is specific to the CPU type and model
 */
uint32_t STDCALL cpu_get_revision(void);

/**
 * @brief Get the CPU description of the current CPU
 */
uint32_t STDCALL cpu_get_description(char *description, uint32_t len);

/** FPU Functions */

/**
 * @brief Get the FPU type for this board
 */
uint32_t STDCALL fpu_get_type(void);

/**
 * @brief Get the current FPU state
 */
uint32_t STDCALL fpu_get_state(void);

/** GPU Functions */

/**
 * @brief Get the GPU type for this board
 */
uint32_t STDCALL gpu_get_type(void);

/**
 * @brief Get the current GPU state
 */
uint32_t STDCALL gpu_get_state(void);

/**
 * @brief Get the memory start and size available to the GPU
 */
uint32_t STDCALL gpu_get_memory(size_t *address, uint64_t *length);

/** Cache Functions */

/**
 * @brief Get the L1 cache type for this board
 */
uint32_t STDCALL l1_cache_get_type(void);

/**
 * @brief Get the L1 data cache size for this board
 * @note If data cache is not supported, the size returned is zero
 * @note If separate data and instruction caches are not supported, the size returned is the unified size
 */
uint32_t STDCALL l1_data_cache_get_size(void);

/**
 * @brief Get the L1 data cache line size for this board
 * @note If data cache is not supported, the size returned is zero
 * @note If separate data and instruction caches are not supported, the size returned is the unified size
 */
uint32_t STDCALL l1_data_cache_get_line_size(void);

/**
 * @brief Get the L1 instruction cache size for this board
 * @note If instruction cache is not supported, the size returned is zero
 * @note If separate data and instruction caches are not supported, the size returned is the unified size
 */
uint32_t STDCALL l1_instruction_cache_get_size(void);

/**
 * @brief Get the L1 instruction cache line size for this board
 * @note If instruction cache is not supported, the size returned is zero
 * @note If separate data and instruction caches are not supported, the size returned is the unified size
 */
uint32_t STDCALL l1_instruction_cache_get_line_size(void);

/**
 * @brief Get the L2 cache type for this board
 */
uint32_t STDCALL l2_cache_get_type(void);

/**
 * @brief Get the L2 cache size for this board
 * @note If L2 cache is not supported, the size returned is zero
 */
uint32_t STDCALL l2_cache_get_size(void);

/**
 * @brief Get the L2 cache line size for this board
 * @note If L2 cache is not supported, the size returned is zero
 */
uint32_t STDCALL l2_cache_get_line_size(void);

/** Version Functions */

/**
 * @brief Get the version information of the currently running system
 */
void STDCALL version_get_info(uint32_t *major, uint32_t *minor, uint32_t *revision);

/**
 * @brief Get the version release date of the currently running system
 */
uint32_t STDCALL version_get_date(char *date, uint32_t len);

/**
 * @brief Get the version release name of the currently running system
 */
uint32_t STDCALL version_get_name(char *name, uint32_t len);

/**
 * @brief Get the version string of the currently running system
 */
uint32_t STDCALL version_get_version(char *version, uint32_t len);

/** Board Functions */

/**
 * @brief Get the current Board type
 */
uint32_t STDCALL board_get_type(void);

/**
 * @brief Get the current Board model
 */
uint32_t STDCALL board_get_model(void);

/**
 * @brief Get the current Board serial number
 */
int64_t STDCALL board_get_serial(void);

/**
 * @brief Get the current Board revision number
 */
uint32_t STDCALL board_get_revision(void);

/**
 * @brief Get the current Board MAC address (Where Applicable)
 */
uint32_t STDCALL board_get_mac_address(char *address, uint32_t len);

/** Chip Functions */

/**
 * @brief Get the current Chip revision number
 */
uint32_t STDCALL chip_get_revision(void);

/** Firmware Functions */

/**
 * @brief Get the current board Firmware Revision
 */
uint32_t STDCALL firmware_get_revision(void);

/**
 * @brief Get the current throttling state from the firmware
 * @return A bit mask of FIRMWARE_THROTTLE_* values for the throttling state
 */
uint32_t STDCALL firmware_get_throttled(void);

/** Machine Functions */

/**
 * @brief Get the current Machine type
 */
uint32_t STDCALL machine_get_type(void);

/** Memory Functions */

/**
 * @brief Get the base address of system memory
 */
size_t STDCALL memory_get_base(void);

/**
 * @brief Get the total size of system memory
 */
uint64_t STDCALL memory_get_size(void);

/**
 * @brief Get the page size of system memory
 */
uint32_t STDCALL memory_get_page_size(void);

/**
 * @brief Get the large page size of system memory (Where Applicable)
 */
uint32_t STDCALL memory_get_large_page_size(void);

/**
 * @brief Get the section size of system memory (Where Applicable)
 */
uint32_t STDCALL memory_get_section_size(void);

/**
 * @brief Get the large section size of system memory (Where Applicable)
 */
uint32_t STDCALL memory_get_large_section_size(void);

/** Power Functions */

/**
 * @brief Power On the specified device
 */
uint32_t STDCALL power_on(uint32_t powerid);

/**
 * @brief Power Off the specified device
 */
uint32_t STDCALL power_off(uint32_t powerid);

/**
 * @brief Get the enable wait time in Microseconds of the specified device
 */
uint32_t STDCALL power_get_wait(uint32_t powerid);

/**
 * @brief Get the power state of the specified device
 */
uint32_t STDCALL power_get_state(uint32_t powerid);

/**
 * @brief Set the power state of the specified device (Optionally waiting for ready)
 */
uint32_t STDCALL power_set_state(uint32_t powerid, uint32_t state, BOOL wait);

/** Clock Functions */

/**
 * @brief Get the current number of clock ticks (When this reaches CLOCK_TICKS_PER_SECOND then ClockSeconds is incremented and this is reset to zero)
 * @return The current number of clock ticks
 */
uint32_t STDCALL clock_ticks(void);

/**
 * @brief Get the number of clock seconds since the system was started (This forms the system clock)
 * @return The current number of clock seconds
 */
uint32_t STDCALL clock_seconds(void);

/**
 * @brief Get the number of clock milliseconds since the system was started
 * @return The current number of clock milliseconds
 */
int64_t STDCALL clock_milliseconds(void);

/**
 * @brief Get the number of clock microseconds since the system was started
 * @return The current number of clock microseconds
 */
int64_t STDCALL clock_microseconds(void);

/**
 * @brief Get the number of clock nanoseconds since the system was started
 * @return The current number of clock nanoseconds
 */
int64_t STDCALL clock_nanoseconds(void);

/**
 * @brief Get the current clock base in 100 nanosecond ticks since 1 January 1601
 * @return The current clock base or zero if not set
 * @note Clock base is the value added to the system clock to obtain the current time
 *        which is calculated at the last setting of the clock
 * @note This is the same time format as Windows FILE_TIME and is intended to allow
 *        compatibility with file system functions etc.
 * @note By default the time returned by this function is considered to be UTC but
 *        the actual conversion between UTC and local time is handled at a higher level
 */
int64_t STDCALL clock_get_base(void);

/**
 * @brief Get the current system time in 100 nanosecond ticks since 1 January 1601
 * @return The current system time
 * @note This is the same time format as Windows FILE_TIME and is intended to allow
 *        compatibility with file system functions etc.
 * @note By default the time returned by this function is considered to be UTC but
 *        the actual conversion between UTC and local time is handled at a higher level
 */
int64_t STDCALL clock_get_time(void);

/**
 * @brief Set the current system time in 100 nanosecond ticks since 1 January 1601
 * @param Time The time to be set
 * @param RTC Set the default RTC (real time clock) if available
 * @return The system time after setting
 * @note This is the same time format as Windows FILE_TIME and is intended to allow
 *        compatibility with file system functions etc.
 * @note By default the time passed to this function is considered to be UTC but
 *        the actual conversion between UTC and local time is handled at a higher level
 */
int64_t STDCALL clock_set_time(int64_t time, BOOL rtc);

/**
 * @brief Gets the current system clock count (32 least significant bits of total)
 * @note This will normally come from the free running system timer in the board
 *  and is useful as a form of tick count but not for time keeping because
 *  the actual rate at which this increments is dependent on the system timer clock
 *  frequency of the specific board and may not be a measure of time in its raw form
 */
uint32_t STDCALL clock_get_count(void);

/**
 * @brief Gets the total system clock count
 * @note This will normally come from the free running system timer in the board
 *  and is useful as a form of tick count but not for time keeping because
 *  the actual rate at which this increments is dependent on the system timer clock
 *  frequency of the specific board and may not be a measure of time in its raw form
 */
int64_t STDCALL clock_get_total(void);

/**
 * @brief Update the system time offset between UTC and Local
 */
uint32_t STDCALL clock_update_offset(void);

/**
 * @brief Calculate the system time offset between UTC and Local at the given date and time
 * @param DateTime The date and time to calculate the offset for (Assumed to be Local)
 * @param Offset The returned Offset in minutes
 * @param Daylight True on return if daylight savings is in effect at the specified date and time
 * @return ERROR_SUCCESS if the offset was calculated or another error code on failure
 */
uint32_t STDCALL clock_calculate_offset(double_t datetime, int32_t *offset, BOOL *daylight);

/**
 * @brief Get the clock rate in Hz of the specified Clock
 */
uint32_t STDCALL clock_get_rate(uint32_t clockid);

/**
 * @brief Set the clock rate in Hz of the specified Clock
 */
uint32_t STDCALL clock_set_rate(uint32_t clockid, uint32_t rate, BOOL turbo);

/**
 * @brief Get the state of the specified Clock
 */
uint32_t STDCALL clock_get_state(uint32_t clockid);

/**
 * @brief Set the state of the specified Clock
 */
uint32_t STDCALL clock_set_state(uint32_t clockid, uint32_t state);

/**
 * @brief Get the minimum clock rate in Hz of the specified Clock
 */
uint32_t STDCALL clock_get_min_rate(uint32_t clockid);

/**
 * @brief Get the maximum clock rate in Hz of the specified Clock
 */
uint32_t STDCALL clock_get_max_rate(uint32_t clockid);

/**
 * @brief Get the measured or actual clock rate in Hz of the specified Clock
 */
uint32_t STDCALL clock_get_measured_rate(uint32_t clockid);

/** Turbo Functions */

/**
 * @brief Get the Turbo state (0 equals Off / 1 equals On) of the specified device
 */
uint32_t STDCALL turbo_get_state(uint32_t turboid);

/**
 * @brief Set the Turbo state (0 equals Off / 1 equals On) of the specified device
 */
uint32_t STDCALL turbo_set_state(uint32_t turboid, uint32_t state);

/** Voltage Functions */

/**
 * @brief Get the current voltage level of the specified device
 */
uint32_t STDCALL voltage_get_value(uint32_t voltageid);

/**
 * @brief Set the current voltage level of the specified device
 */
uint32_t STDCALL voltage_set_value(uint32_t voltageid, uint32_t value);

/**
 * @brief Get the minimum voltage level of the specified device
 */
uint32_t STDCALL voltage_get_min_value(uint32_t voltageid);

/**
 * @brief Get the maximum voltage level of the specified device
 */
uint32_t STDCALL voltage_get_max_value(uint32_t voltageid);

/** Temperature Functions */

/**
 * @brief Get the current temperature in thousandths of a degree C of the specified device
 */
uint32_t STDCALL temperature_get_current(uint32_t temperatureid);

/**
 * @brief Get the maximum temperature in thousandths of a degree C of the specified device
 */
uint32_t STDCALL temperature_get_maximum(uint32_t temperatureid);

/** GPU Memory Functions */

/**
 * @brief Allocate memory from the GPU
 */
HANDLE STDCALL gpu_memory_allocate(uint32_t length, uint32_t alignment, uint32_t flags);

/**
 * @brief Release memory allocated from the GPU
 */
uint32_t STDCALL gpu_memory_release(HANDLE handle);

/**
 * @brief Lock memory allocated from the GPU and return an address
 */
uint32_t STDCALL gpu_memory_lock(HANDLE handle);

/**
 * @brief Unlock memory allocated from the GPU
 */
uint32_t STDCALL gpu_memory_unlock(HANDLE handle);

/** GPU Misc Functions */

/**
 * @brief Execute a block of code on the GPU
 */
uint32_t STDCALL gpu_execute_code(void *address, uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3, uint32_t r4, uint32_t r5);

/**
 * @brief Convert a Dispmanx Resource handle to a Memory handle (Which can be passed to Lock/Unlock above)
 */
HANDLE STDCALL dispmanx_handle_get(HANDLE resource);

/**
 * @brief Get an EDID block from HDMI
 */
uint32_t STDCALL edid_block_get(uint32_t block, void *buffer, uint32_t length);

/** Framebuffer Functions */

/**
 * @brief Check if a framebuffer device is currently available
 */
BOOL STDCALL framebuffer_available(void);

/**
 * @brief Allocate a new Framebuffer
 */
uint32_t STDCALL framebuffer_allocate(uint32_t alignment, uint32_t *address, uint32_t *length);

/**
 * @brief Release the current Framebuffer
 */
uint32_t STDCALL framebuffer_release(void);

/**
 * @brief Set the current Framebuffer (Display) state (0 for Off / 1 for On)
 */
uint32_t STDCALL framebuffer_set_state(uint32_t state);

/**
 * @brief Get the default Dimensions of the Framebuffer (Physical Width, Height and Overscan Top, Bottom, Left, Right in Pixels)
 */
uint32_t STDCALL framebuffer_get_dimensions(uint32_t *width, uint32_t *height, uint32_t *top, uint32_t *bottom, uint32_t *left, uint32_t *right);

/**
 * @brief Get the Physical Framebuffer Width and Height in Pixels
 * @note The "physical" size is the size of the allocated buffer in memory,
 *        not the resolution of the video signal sent to the display device
 */
uint32_t STDCALL framebuffer_get_physical(uint32_t *width, uint32_t *height);

/**
 * @brief Set the Physical Framebuffer Width and Height in Pixels
 */
uint32_t STDCALL framebuffer_set_physical(uint32_t *width, uint32_t *height);

/**
 * @brief Test the Physical Framebuffer Width and Height in Pixels
 */
uint32_t STDCALL framebuffer_test_physical(uint32_t *width, uint32_t *height);

/**
 * @brief Get the Virtual Framebuffer Width and Height in Pixels
 * @note The "virtual" size is the portion of buffer that is sent to the display device,
 *        not the resolution the buffer itself. This may be smaller than the allocated
 *        buffer size in order to implement panning
 */
uint32_t STDCALL framebuffer_get_virtual(uint32_t *width, uint32_t *height);

/**
 * @brief Set the Virtual Framebuffer Width and Height in Pixels
 */
uint32_t STDCALL framebuffer_set_virtual(uint32_t *width, uint32_t *height);

/**
 * @brief Test the Virtual Framebuffer Width and Height in Pixels
 */
uint32_t STDCALL framebuffer_test_virtual(uint32_t *width, uint32_t *height);

/**
 * @brief Get the Framebuffer Depth in Bits per Pixel
 */
uint32_t STDCALL framebuffer_get_depth(uint32_t *depth);

/**
 * @brief Set the Framebuffer Depth in Bits per Pixel
 */
uint32_t STDCALL framebuffer_set_depth(uint32_t *depth);

/**
 * @brief Test the Framebuffer Depth in Bits per Pixel
 */
uint32_t STDCALL framebuffer_test_depth(uint32_t *depth);

/**
 * @brief Get the Framebuffer Pixel Order (0 = BGR / 1 = RGB)
 */
uint32_t STDCALL framebuffer_get_pixel_order(uint32_t *order);

/**
 * @brief Set the Framebuffer Pixel Order (0 = BGR / 1 = RGB)
 */
uint32_t STDCALL framebuffer_set_pixel_order(uint32_t *order);

/**
 * @brief Test the Framebuffer Pixel Order (0 = BGR / 1 = RGB)
 */
uint32_t STDCALL framebuffer_test_pixel_order(uint32_t *order);

/**
 * @brief Get the Framebuffer Alpha Mode
 */
uint32_t STDCALL framebuffer_get_alpha_mode(uint32_t *mode);

/**
 * @brief Set the Framebuffer Alpha Mode
 */
uint32_t STDCALL framebuffer_set_alpha_mode(uint32_t *mode);

/**
 * @brief Test the Framebuffer Alpha Mode
 */
uint32_t STDCALL framebuffer_test_alpha_mode(uint32_t *mode);

/**
 * @brief Get the Framebuffer Pitch in Bytes per Line
 */
uint32_t STDCALL framebuffer_get_pitch(void);

/**
 * @brief Get the Framebuffer Virtual Offset in Pixels
 */
uint32_t STDCALL framebuffer_get_offset(uint32_t *x, uint32_t *y);

/**
 * @brief Set the Framebuffer Virtual Offset in Pixels
 */
uint32_t STDCALL framebuffer_set_offset(uint32_t *x, uint32_t *y);

/**
 * @brief Test the Framebuffer Virtual Offset in Pixels
 */
uint32_t STDCALL framebuffer_test_offset(uint32_t *x, uint32_t *y);

/**
 * @brief Get the Framebuffer Top, Bottom, Left and Right Overscan in Pixels
 */
uint32_t STDCALL framebuffer_get_overscan(uint32_t *top, uint32_t *bottom, uint32_t *left, uint32_t *right);

/**
 * @brief Set the Framebuffer Top, Bottom, Left and Right Overscan in Pixels
 */
uint32_t STDCALL framebuffer_set_overscan(uint32_t *top, uint32_t *bottom, uint32_t *left, uint32_t *right);

/**
 * @brief Test the Framebuffer Top, Bottom, Left and Right Overscan in Pixels
 */
uint32_t STDCALL framebuffer_test_overscan(uint32_t *top, uint32_t *bottom, uint32_t *left, uint32_t *right);

/**
 * @brief Get the Framebuffer Palette in RGBA values
 */
uint32_t STDCALL framebuffer_get_palette(void *buffer, uint32_t length);

/**
 * @brief Set the Framebuffer Palette in RGBA values
 */
uint32_t STDCALL framebuffer_set_palette(uint32_t start, uint32_t count, void *buffer, uint32_t length);

/**
 * @brief Test the Framebuffer Palette in RGBA values
 */
uint32_t STDCALL framebuffer_test_palette(uint32_t start, uint32_t count, void *buffer, uint32_t length);

/**
 * @brief Get the Framebuffer Layer
 */
uint32_t STDCALL framebuffer_get_layer(int32_t *layer);

/**
 * @brief Set the Framebuffer Layer
 */
uint32_t STDCALL framebuffer_set_layer(int32_t *layer);

/**
 * @brief Test the Framebuffer Layer
 */
uint32_t STDCALL framebuffer_test_layer(int32_t *layer);

/**
 * @brief Test the Framebuffer Vertical Sync (Where Applicable)
 */
uint32_t STDCALL framebuffer_test_vsync(void);

/**
 * @brief Set (Wait For) the Framebuffer Vertical Sync (Where Applicable)
 */
uint32_t STDCALL framebuffer_set_vsync(void);

/**
 * @brief Set the Framebuffer Backlight brightness (Where Applicable)
 */
uint32_t STDCALL framebuffer_set_backlight(uint32_t brightness);

/**
 * @brief Get the number of framebuffer displays (Where Applicable)
 */
uint32_t STDCALL framebuffer_get_num_displays(uint32_t *numdisplays);

/**
 * @brief Get the display id for the specified display number (Where Applicable)
 */
uint32_t STDCALL framebuffer_get_display_id(uint32_t displaynum);

/**
 * @brief Set the current framebuffer display number (Where Applicable)
 */
uint32_t STDCALL framebuffer_set_display_num(uint32_t displaynum);

/**
 * @brief Get the display settings for the specified display number (Where Applicable)
 */
uint32_t STDCALL framebuffer_get_display_settings(uint32_t displaynum, DISPLAY_SETTINGS *displaysettings);

/**
 * @brief Get the name for the specified display id (Where Applicable)
 */
uint32_t STDCALL framebuffer_display_id_to_name(uint32_t displayid, char *name, uint32_t len);

/** Touch Functions */

/**
 * @brief Get the Touchscreen memory buffer (Where Applicable)
 */
uint32_t STDCALL touch_get_buffer(size_t *address);

/**
 * @brief Set the Touchscreen memory buffer (Where Applicable)
 */
uint32_t STDCALL touch_set_buffer(size_t address);

/** Cursor Functions */

/**
 * @brief Set the default Cursor Info (Where Applicable)
 */
uint32_t STDCALL cursor_set_default(void);

/**
 * @brief Set the Cursor Info (Width and Height, Hotspot and Pixel image)
 */
uint32_t STDCALL cursor_set_info(uint32_t width, uint32_t height, uint32_t hotspotx, uint32_t hotspoty, void *pixels, uint32_t length);

/**
 * @brief Set the Cursor State (Enabled, X and Y)
 * @param Relative X, Y is relative to Display (Virtual) not Framebuffer (Physical)
 */
uint32_t STDCALL cursor_set_state(BOOL enabled, uint32_t x, uint32_t y, BOOL relative);

/** DMA Functions */

/**
 * @brief Check if DMA is currently available
 */
BOOL STDCALL dma_available(void);

/**
 * @brief Perform a DMA transfer using the list of DMA data blocks provided
 * @param Data A linked list of DMA data blocks for the transfer
 * @param Direction The direction of the DMA request (eg DMA_DIR_MEM_TO_MEM)
 * @param Peripheral The peripheral ID for data request gating (eg DMA_DREQ_ID_NONE)
 */
uint32_t STDCALL dma_transfer(DMA_DATA *data, uint32_t direction, uint32_t peripheral);

/**
 * @brief Fill memory at the destination address using DMA
 * @param Dest The address to start the memory fill
 * @param Size The size of memory to fill in bytes
 * @param Value The value to fill the memory with
 */
uint32_t STDCALL dma_fill_memory(void *dest, uint32_t size, uint8_t value);

/**
 * @brief Copy memory from the source to the destination address using DMA
 * @param Source The source address to start the memory copy
 * @param Dest The destination address to start the memory copy
 * @param Size The size of memory to copy in bytes
 */
uint32_t STDCALL dma_copy_memory(void *source, void *dest, uint32_t size);

/**
 * @brief Read from a peripheral address to the destination address using DMA
 * @param Address The address of the peripheral register to read from
 * @param Dest The destination address to start writing to
 * @param Size The size of the read in bytes
 * @param Peripheral The peripheral ID for data request gating (eg DMA_DREQ_ID_UART_RX)
 */
uint32_t STDCALL dma_read_peripheral(void *address, void *dest, uint32_t size, uint32_t peripheral);

/**
 * @brief Write to a peripheral address from the source address using DMA
 * @param Source The source address to start reading from
 * @param Address The address of the peripheral register to write to
 * @param Size The size of the write in bytes
 * @param Peripheral The peripheral ID for data request gating (eg DMA_DREQ_ID_UART_TX)
 */
uint32_t STDCALL dma_write_peripheral(void *source, void *address, uint32_t size, uint32_t peripheral);

/**
 * @brief Allocate a buffer compatible with DMA memory reads or writes
 * @param Size The size of the buffer to allocate
 */
void * STDCALL dma_allocate_buffer(uint32_t size);

/**
 * @brief Allocate a buffer compatible with DMA memory reads or writes
 * @param Size The size of the buffer to allocate (Updated on return to actual size)
 */
void * STDCALL dma_allocate_buffer_ex(uint32_t *size);

/**
 * @brief Release a buffer allocated with DMAAllocateBuffer
 * @param Buffer The buffer to be released
 */
uint32_t STDCALL dma_release_buffer(void *buffer);

/**
 * @brief Get the currently enabled DMA channel bitmap (If supported)
 */
uint32_t STDCALL dma_get_channels(void);

/** Handle Functions */

/**
 * @brief Create and Open a new unnamed handle of the supplied type
 * @param Data Purpose specific data to be referenced by the new handle (Optional)
 * @param AType The type of the new handle (eg HANDLE_TYPE_FILE)
 * @return The newly created handle or INVALID_HANDLE_VALUE on failure
 */
HANDLE STDCALL handle_create(HANDLE data, uint32_t _type);

/**
 * @brief Create and Open a new named or unnamed handle of the supplied type
 * @param Name The name of the new handle (Optional)
 * @param Flags The flags for the new handle (eg HANDLE_FLAG_DUPLICATE)
 * @param Data Purpose specific data to be referenced by the new handle (Optional)
 * @param AType The type of the new handle (eg HANDLE_TYPE_FILE)
 * @return The newly created handle entry or nil on failure
 */
HANDLE_ENTRY * STDCALL handle_create_ex(const char *name, uint32_t flags, HANDLE data, uint32_t _type);

/**
 * @brief Close and Destroy a named or unnamed handle
 * @param Handle The handle to be closed and destroyed
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 * @note For handles which have been opened multiple times, the handle is not destroyed until the last reference is closed.
 *        If there are still open references to the handle the return value will be ERROR_IN_USE instead of ERROR_SUCCESS
 */
uint32_t STDCALL handle_destroy(HANDLE handle);

/**
 * @brief Get the handle entry for the supplied handle
 * @param Handle The handle to get the entry for
 * @return The handle entry on success or nil on failure
 */
HANDLE_ENTRY * STDCALL handle_get(HANDLE handle);

/**
 * @brief Find an existing named handle of the supplied type
 * @param Name The name of the handle to find
 * @return The handle entry on success or nil on failure
 */
HANDLE_ENTRY * STDCALL handle_find(const char *name);

/**
 * @brief Enumerate all handles in the handle table
 * @param Callback The callback function to call for each handle in the table
 * @param Data A private data pointer to pass to callback for each device in the table
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL handle_enumerate(handle_enumerate_cb callback, void *data);

/**
 * @brief Open an existing named handle
 * @param Name The name of the handle to open
 * @return The handle matching the name or INVALID_HANDLE_VALUE on failure
 */
HANDLE STDCALL handle_open(const char *name);

/**
 * @brief Close a named or unnamed handle
 * @param Handle The handle to be closed
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 * @note For handles which have been opened multiple times, the handle is destroyed when the last reference is closed
 */
uint32_t STDCALL handle_close(HANDLE handle);

/**
 * @brief Duplicate an existing named or unnamed handle
 * @param Handle The handle to be duplicated
 * @return The newly duplicated handle or INVALID_HANDLE_VALUE on failure
 * @note Handles must be marked as HANDLE_FLAG_DUPLICATE to support duplication
 */
HANDLE STDCALL handle_duplicate(HANDLE handle);

/** GPIO Functions */

/**
 * @brief Check if a GPIO device is available
 */
BOOL STDCALL gpio_available(void);

/**
 * @brief Perform a direct read from a GPIO register
 * @param Reg The memory register to read from
 * @return The value of the memory register
 */
uint32_t STDCALL gpio_read(uint32_t reg);

/**
 * @brief Perform a direct write to a GPIO register
 * @param Reg The memory register to write to
 * @param Value The value to write to the register
 */
void STDCALL gpio_write(uint32_t reg, uint32_t value);

/**
 * @brief Get the current state of a GPIO input pin
 * @param Pin The pin to get the state for (eg GPIO_PIN_1)
 * @return The current state (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure
 */
uint32_t STDCALL gpio_input_get(uint32_t pin);

/**
 * @brief Wait for the state of a GPIO input pin to change
 * @param Pin The pin to wait for the state to change (eg GPIO_PIN_1)
 * @param Trigger The trigger event to wait for (eg GPIO_TRIGGER_HIGH)
 * @param Timeout Number of milliseconds to wait for the change (INFINITE to wait forever)
 * @return The state after the change (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure or timeout
 */
uint32_t STDCALL gpio_input_wait(uint32_t pin, uint32_t trigger, uint32_t timeout);

/**
 * @brief Schedule a function to be called when the state of a GPIO input pin changes
 * @param Pin The pin to schedule the state change for (eg GPIO_PIN_1)
 * @param Trigger The trigger event which will cause the function to be called (eg GPIO_TRIGGER_HIGH)
 * @param Timeout The number of milliseconds before the scheduled trigger expires (INFINITE to never expire)
 * @param Callback The function to be called when the trigger occurs
 * @param Data A pointer to be pass to the function when the trigger occurs (Optional)
 * @return ERROR_SUCCESS if the trigger was scheduled successfully or another error code on failure
 * @note The pin and trigger that caused the event will be passed to the callback function
 */
uint32_t STDCALL gpio_input_event(uint32_t pin, uint32_t trigger, uint32_t timeout, gpio_event_cb callback, void *data);

/**
 * @brief Set the state of a GPIO output pin
 * @param Pin The pin to set the state for (eg GPIO_PIN_1)
 * @param Level The state to set the pin to (eg GPIO_LEVEL_HIGH)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 */
uint32_t STDCALL gpio_output_set(uint32_t pin, uint32_t level);

/**
 * @brief Get the current level (state) of a GPIO pin
 * @param Pin The pin to get the level for (eg GPIO_PIN_1)
 * @return The current level (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure
 * @note This function is a synonym for GPIOInputGet as in many cases the
 *        level can be read from a pin regardless of input or output mode. This
 *        may help to make code clearer or easier to understand in some cases
 */
uint32_t STDCALL gpio_level_get(uint32_t pin);

/**
 * @brief Set the level (state) of a GPIO pin
 * @param Pin The pin to set the level for (eg GPIO_PIN_1)
 * @param Level The level to set the pin to (eg GPIO_LEVEL_HIGH)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 * @note This function is a synonym for GPIOOutputSet as in many cases the
 *        level can be set for a pin regardless of input or output mode. This
 *        may help to make code clearer or easier to understand in some cases
 */
uint32_t STDCALL gpio_level_set(uint32_t pin, uint32_t level);

/**
 * @brief Get the current pull state of a GPIO pin
 * @param Pin The pin to get the pull state for (eg GPIO_PIN_1)
 * @return The current pull state of the pin (eg GPIO_PULL_UP) or GPIO_PULL_UNKNOWN on failure
 */
uint32_t STDCALL gpio_pull_get(uint32_t pin);

/**
 * @brief Change the pull state of a GPIO pin
 * @param Pin The pin to change the pull state for (eg GPIO_PIN_1)
 * @param Mode The pull state to set for the pin (eg GPIO_PULL_UP)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 */
uint32_t STDCALL gpio_pull_select(uint32_t pin, uint32_t mode);

/**
 * @brief Get the current function of a GPIO pin
 * @param Pin The pin to get the function for (eg GPIO_PIN_1)
 * @return The current function of the pin (eg GPIO_FUNCTION_IN) or GPIO_FUNCTION_UNKNOWN on failure
 */
uint32_t STDCALL gpio_function_get(uint32_t pin);

/**
 * @brief Change the function of a GPIO pin
 * @param Pin The pin to change the function for (eg GPIO_PIN_1)
 * @param Mode The function to set for the pin (eg GPIO_FUNCTION_OUT)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 */
uint32_t STDCALL gpio_function_select(uint32_t pin, uint32_t mode);

/** Virtual GPIO Functions */

/**
 * @brief Get the current state of a virtual GPIO input pin
 * @param Pin The pin to get the state for (eg VIRTUAL_GPIO_PIN_1)
 * @return The current state (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure
 */
uint32_t STDCALL virtual_gpio_input_get(uint32_t pin);

/**
 * @brief Set the state of a virtual GPIO output pin
 * @param Pin The pin to set the state for (eg GPIO_PIN_1)
 * @param Level The state to set the pin to (eg GPIO_LEVEL_HIGH)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 */
uint32_t STDCALL virtual_gpio_output_set(uint32_t pin, uint32_t level);

/**
 * @brief Get the current level (state) of a virtual GPIO pin
 * @param Pin The pin to get the level for (eg GPIO_PIN_1)
 * @return The current level (eg GPIO_LEVEL_HIGH) or GPIO_LEVEL_UNKNOWN on failure
 * @note This function is a synonym for VirtualGPIOInputGet as in many cases the
 *        level can be read from a pin regardless of input or output mode. This
 *        may help to make code clearer or easier to understand in some cases
 */
uint32_t STDCALL virtual_gpio_level_get(uint32_t pin);

/**
 * @brief Set the level (state) of a virtual GPIO pin
 * @param Pin The pin to set the level for (eg GPIO_PIN_1)
 * @param Level The level to set the pin to (eg GPIO_LEVEL_HIGH)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 * @note This function is a synonym for VirtualGPIOOutputSet as in many cases the
 *        level can be set for a pin regardless of input or output mode. This
 *        may help to make code clearer or easier to understand in some cases
 */
uint32_t STDCALL virtual_gpio_level_set(uint32_t pin, uint32_t level);

/**
 * @brief Get the current function of a virtual GPIO pin
 * @param Pin The pin to get the function for (eg GPIO_PIN_1)
 * @return The current function of the pin (eg GPIO_FUNCTION_IN) or GPIO_FUNCTION_UNKNOWN on failure
 */
uint32_t STDCALL virtual_gpio_function_get(uint32_t pin);

/**
 * @brief Change the function of a virtual GPIO pin
 * @param Pin The pin to change the function for (eg GPIO_PIN_1)
 * @param Mode The function to set for the pin (eg GPIO_FUNCTION_OUT)
 * @return ERROR_SUCCESS if completed successfully or another error code on failure
 */
uint32_t STDCALL virtual_gpio_function_select(uint32_t pin, uint32_t mode);

/** SPI Functions */

/**
 * @brief Check if an SPI device is available
 */
BOOL STDCALL spi_available(void);

/**
 * @brief Start the default SPI device ready for writing and reading
 * @param Mode The device mode to set (eg SPI_MODE_4WIRE)
 * @param ClockRate The clock rate to set for the device
 * @param ClockPhase The clock phase to set (eg SPI_CLOCK_PHASE_LOW)
 * @param ClockPolarity The clock polarity to set (eg SPI_CLOCK_POLARITY_LOW)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_start(uint32_t mode, uint32_t clockrate, uint32_t clockphase, uint32_t clockpolarity);

/**
 * @brief Stop the default SPI device and terminate writing and reading
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_stop(void);

/**
 * @brief Read data from the default SPI device
 * Because SPI writes and then reads for each byte, dummy data will be written for each byte to be read
 * @param ChipSelect The chip select for the slave to read from (eg SPI_CS_0)
 * @param Dest Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_read(uint16_t chipselect, void *dest, uint32_t size, uint32_t *count);

/**
 * @brief Write data to the default SPI device
 * Because SPI writes and then reads for each byte, received data will be discarded for each byte written
 * @param ChipSelect The chip select for the slave to write to (eg SPI_CS_0)
 * @param Source Pointer to a buffer of data to transmit
 * @param Size The size of the buffer
 * @param Count The number of bytes written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_write(uint16_t chipselect, void *source, uint32_t size, uint32_t *count);

/**
 * @brief Write data to and Read data from the default SPI device in one operation
 * Because SPI writes and then reads for each byte, both the source and dest buffers must be the same size
 * @param ChipSelect The chip select for the slave to write to and read from (eg SPI_CS_0)
 * @param Source Pointer to a buffer of data to transmit
 * @param Dest Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Count The number of bytes written and read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_write_read(uint16_t chipselect, void *source, void *dest, uint32_t size, uint32_t *count);

/**
 * @brief Get the device mode of the default SPI device
 * @return The device mode or SPI_MODE_UNKNOWN on failure
 */
uint32_t STDCALL spi_get_mode(void);

/**
 * @brief Set the device mode for the default SPI device
 * @param Mode The device mode to set (eg SPI_MODE_4WIRE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_set_mode(uint32_t mode);

/**
 * @brief Get the clock rate of the default SPI device
 * @param ChipSelect The chip select number to get clock rate from (SPI_CS_NONE for default)
 * @return The clock rate in Hz or 0 on failure
 */
uint32_t STDCALL spi_get_clock_rate(uint16_t chipselect);

/**
 * @brief Set the clock rate for the default SPI device
 * @param ClockRate The clock rate to set in Hz
 * @param ChipSelect The chip select number to set clock rate for (SPI_CS_NONE for default)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_set_clock_rate(uint16_t chipselect, uint32_t clockrate);

/**
 * @brief Get the clock phase of the default SPI device
 * @return The clock phase or SPI_CLOCK_PHASE_UNKNOWN on failure
 */
uint32_t STDCALL spi_get_clock_phase(void);

/**
 * @brief Set the clock phase for the default SPI device
 * @param ClockPhase The clock phase to set (eg SPI_CLOCK_PHASE_LOW)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_set_clock_phase(uint32_t clockphase);

/**
 * @brief Get the clock polarity of the default SPI device
 * @return The clock polarity or SPI_CLOCK_POLARITY_UNKNOWN on failure
 */
uint32_t STDCALL spi_get_clock_polarity(void);

/**
 * @brief Set the clock polarity for the default SPI device
 * @param ClockPolarity The clock polarity to set (eg SPI_CLOCK_POLARITY_LOW)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_set_clock_polarity(uint32_t clockpolarity);

/**
 * @brief Get the chip select polarity of the default SPI device
 * @param ChipSelect The chip select number to get polarity from (SPI_CS_NONE for default)
 * @return The chip select polarity or SPI_CS_POLARITY_UNKNOWN on failure
 */
uint32_t STDCALL spi_get_select_polarity(uint16_t chipselect);

/**
 * @brief Set the chip select polarity for the default SPI device
 * @param ChipSelect The chip select number to set polarity for (SPI_CS_NONE for default)
 * @param SelectPolarity The chip select polarity to set (eg SPI_CS_POLARITY_LOW)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spi_set_select_polarity(uint16_t chipselect, uint32_t selectpolarity);

/**
 * @brief Return the device description of an SPI device
 * @param Id The Id number of the SPI device as shown in the official documentation
 * @return The correct device description suitable for passing to SPIDeviceFindByDescription
 * @note The Id number supplied to this function may differ from the Ultibo device id value
 */
uint32_t STDCALL spi_get_description(uint32_t id, char *description, uint32_t len);

/** I2C Functions */

/**
 * @brief Check if an I2C device is available
 */
BOOL STDCALL i2c_available(void);

/**
 * @brief Start the default I2C device ready for reading and writing
 * @param Rate The clock rate to set for the device (0 to use the default rate)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_start(uint32_t rate);

/**
 * @brief Stop the default I2C device and terminate reading and writing
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_stop(void);

/**
 * @brief Read data from the default I2C device
 * @param Address The slave address to read from (I2C_ADDRESS_INVALID to use the current address)
 * @param Buffer Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_read(uint16_t address, void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Write data to the default I2C device
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Buffer Pointer to a buffer of data to transmit
 * @param Size The size of the buffer
 * @param Count The number of bytes written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_write(uint16_t address, void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Write data to and Read data from the default I2C device in one operation
 * Useful for devices that require a register address specified before a read (eg EEPROM devices)
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Initial Pointer to the initial buffer to transmit
 * @param Len The size of the initial buffer
 * @param Data Pointer to a buffer to receive the data
 * @param Size The size of the data buffer
 * @param Count The number of bytes read on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_write_read(uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t *count);

/**
 * @brief Write 2 data blocks to the default I2C device in one operation
 * Useful for devices that require a register address specified before a write (eg EEPROM devices)
 * @param Address The slave address to write to (I2C_ADDRESS_INVALID to use the current address)
 * @param Initial Pointer to the initial buffer to transmit
 * @param Len The size of the initial buffer
 * @param Data Pointer to a buffer of data to transmit
 * @param Size The size of the data buffer
 * @param Count The number of bytes of data written on return
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_write_write(uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t *count);

/**
 * @brief Get the clock rate of the default I2C device
 * @return The clock rate in Hz or 0 on failure
 */
uint32_t STDCALL i2c_get_rate(void);

/**
 * @brief Set the clock rate for the default I2C device
 * @param Rate The clock rate to set in Hz
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_set_rate(uint32_t rate);

/**
 * @brief Get the slave address for the default I2C device
 * @return The slave address or I2C_ADDRESS_INVALID on failure
 */
uint16_t STDCALL i2c_get_address(void);

/**
 * @brief Set the slave address for the default I2C device
 * @param Address The slave address to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL i2c_set_address(uint16_t address);

/**
 * @brief Get the device description of an I2C device
 * @param Id The Id number of the I2C device as shown in the official documentation
 * @return The correct device description suitable for passing to I2CDeviceFindByDescription
 * @note The Id number supplied to this function may differ from the Ultibo device id value
 */
uint32_t STDCALL i2c_get_description(uint32_t id, char *description, uint32_t len);

/**
 * @brief Get the device description of an I2C slave device
 * @param Id The Id number of the I2C slave device as shown in the official documentation
 * @return The correct device description suitable for passing to I2CSlaveFindByDescription
 * @note The Id number supplied to this function may differ from the Ultibo device id value
 */
uint32_t STDCALL i2c_slave_get_description(uint32_t id, char *description, uint32_t len);

/** PWM Functions */

/**
 * @brief Check if a PWM device is available
 */
BOOL STDCALL pwm_available(void);

/**
 * @brief Start the default PWM device
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL pwm_start(void);

/**
 * @brief Stop the default PWM device
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL pwm_stop(void);

/**
 * @brief Write a value to the default PWM device
 * @param Value The value to write
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The exact meaning of value may depend on the device and other configured options,
 *        in many cases the value will represent the "on" time of each pulse with regard to
 *        the duty cycle of the waveform output by the device
 */
uint32_t STDCALL pwm_write(uint32_t value);

/**
 * @brief Set the mode for the default PWM device
 * @param Mode The mode value to set (eg PWM_MODE_MARKSPACE)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL pwm_set_mode(uint32_t mode);

/**
 * @brief Set the range for the default PWM device
 * @param Range The range value to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The exact meaning of range may depend on the device and other configured options,
 *        in many cases the range will represent the period of one full cycle of the
 *        waveform output by the device
 */
uint32_t STDCALL pwm_set_range(uint32_t range);

/**
 * @brief Set the clock frequency for the default PWM device
 * @param Frequency The frequency to set in Hz
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL pwm_set_frequency(uint32_t frequency);

/**
 * @brief Set the configuration of the default PWM device
 * @param DutyNS The "on" time part of the cycle (Nanoseconds)
 * @param PeriodNS The duration of one full cycle (Nanoseconds)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL pwm_configure(uint32_t dutyns, uint32_t periodns);

/**
 * @brief Get the device description of an PWM device
 * @param Id The Id number of the PWM device as shown in the official documentation
 * @param Channel The channel number of the PWM device as shown in the official documentation
 * @return The correct device description suitable for passing to PWMDeviceFindByDescription
 * @note The Id number supplied to this function may differ from the Ultibo device id value
 */
uint32_t STDCALL pwm_get_description(uint32_t id, uint32_t channel, char *description, uint32_t len);

/** RTC Functions */

/**
 * @brief Check if a Real Time Clock (RTC) device is available
 */
BOOL STDCALL rtc_available(void);

/**
 * @brief Get the current time from a Real Time Clock device
 * Returned time is 100 nanosecond ticks since 1 January 1601
 * The same format as the ClockGetTime function
 */
int64_t STDCALL rtc_get_time(void);

/**
 * @brief Set the current time for a Real Time Clock device
 * @param Time The time to be set
 * @return The device time after setting (or 0 on failure)
 * Time and returned time is 100 nanosecond ticks since 1 January 1601
 * The same format as the ClockSetTime function
 */
int64_t STDCALL rtc_set_time(int64_t time);

/** UART Functions */

/**
 * @brief Get the device description of a UART device
 * @param Id The Id number of the UART device as shown in the official documentation
 * @return The correct device description suitable for passing to UARTDeviceFindByDescription
 * @note The Id number supplied to this function may differ from the Ultibo device id value
 */
uint32_t STDCALL uart_get_description(uint32_t id, char *description, uint32_t len);

/** Serial Functions */

/**
 * @brief Check if a Serial device is available
 */
BOOL STDCALL serial_available(void);

/**
 * @brief Open the default Serial device ready for sending and receiving
 * @param BaudRate Baud rate for the connection (eg 9600, 57600, 115200 etc
 * @param DataBits Size of the data (eg SERIAL_DATA_8BIT)
 * @param StopBits Number of stop bits (eg SERIAL_STOP_1BIT)
 * @param Parity Parity type for the data (eg SERIAL_PARITY_NONE)
 * @param FlowControl Flow control for the connection (eg SERIAL_FLOW_NONE)
 * @param ReceiveDepth Size of the receive buffer (0 = Default size)
 * @param TransmitDepth Size of the transmit buffer (0 = Default size)
 */
uint32_t STDCALL serial_open(uint32_t baudrate, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t flowcontrol, uint32_t receivedepth, uint32_t transmitdepth);

/**
 * @brief Close the default Serial device and terminate sending and receiving
 */
uint32_t STDCALL serial_close(void);

/**
 * @brief Read data from the default Serial device
 * @param Buffer Pointer to a buffer to receive the data
 * @param Size The size of the buffer
 * @param Count The number of bytes read on return
 */
uint32_t STDCALL serial_read(void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Write data to the default Serial device
 * @param Buffer Pointer to a buffer of data to transmit
 * @param Size The size of the buffer
 * @param Count The number of bytes written on return
 */
uint32_t STDCALL serial_write(void *buffer, uint32_t size, uint32_t *count);

/**
 * @brief Print formatted text to the default Serial device
 * @param Format The formatted text to print (As per printf in standard C library)
 * @return On success the total number of characters sent to the serial device, on error a negative value is returned and errno is set to the error code
 */
int STDCALL serial_printf(const char *format, ...) _ATTRIBUTE ((__format__ (__printf__, 1, 2)));

/** Peripheral Functions */

/**
 * @brief Get the base address of the peripherals
 */
size_t STDCALL peripheral_get_base(void);

/**
 * @brief Get the total size of the peripherals
 */
uint32_t STDCALL peripheral_get_size(void);

/**
 * @brief Read from a Peripheral register
 */
uint32_t STDCALL peripheral_read(uint32_t base, uint32_t reg);

/**
 * @brief Write to a Peripheral register
 */
void STDCALL peripheral_write(uint32_t base, uint32_t reg, uint32_t value);

/**
 * @brief Get the base address of the local peripherals (Peripherals local to each CPU)
 */
size_t STDCALL local_peripheral_get_base(void);

/**
 * @brief Get the total size of the local peripherals (Peripherals local to each CPU)
 */
uint32_t STDCALL local_peripheral_get_size(void);

/** System Functions */

/**
 * @brief Get the current stack pointer (SP)
 */
size_t STDCALL get_sp(void);

/**
 * @brief Get the current program counter (PC)
 */
size_t STDCALL get_pc(void);

/**
 * @brief Get Interrupts (IRQ) state
 * @return True if enabled, False if disabled
 */
BOOL STDCALL get_irq(void);

/**
 * @brief Enable Interrupts (IRQ) unconditionally
 */
void STDCALL enable_irq(void);

/**
 * @brief Disable Interrupts (IRQ) unconditionally
 */
void STDCALL disable_irq(void);

/**
 * @brief Disable Interrupts (IRQ) and return the previous state
 * @return IRQ state when called
 */
IRQ_MASK STDCALL save_irq(void);

/**
 * @brief Restore Interrupts (IRQ) to a previous state
 * @param IRQMask IRQ state to restore
 * @return IRQ state when called
 */
IRQ_MASK STDCALL restore_irq(IRQ_MASK irqmask);

/**
 * @brief Get Fast Interrupts (FIQ) state
 * @return True if enabled, False if disabled
 */
BOOL STDCALL get_fiq(void);

/**
 * @brief Enable Fast Interrupts (FIQ) unconditionally
 */
void STDCALL enable_fiq(void);

/**
 * @brief Disable Fast Interrupts (FIQ) unconditionally
 */
void STDCALL disable_fiq(void);

/**
 * @brief Disable Fast Interrupts (FIQ) and return the previous state
 * @return FIQ state when called
 */
FIQ_MASK STDCALL save_fiq(void);

/**
 * @brief Restore Fast Interrupts (FIQ) to a previous state
 * @param FIQMask FIQ state to restore
 * @return FIQ state when called
 */
FIQ_MASK STDCALL restore_fiq(FIQ_MASK fiqmask);

/**
 * @brief Enable Interrupts and Fast Interrupts (IRQ/FIQ) unconditionally
 */
void STDCALL enable_irq_fiq(void);

/**
 * @brief Disable Interrupts and Fast Interrupts (IRQ/FIQ) unconditionally
 */
void STDCALL disable_irq_fiq(void);

/**
 * @brief Disable Interrupts and Fast Interrupts (IRQ/FIQ) and return the previous state
 * @return IRQ/FIQ state when called
 */
IRQ_FIQ_MASK STDCALL save_irq_fiq(void);

/**
 * @brief Restore Interrupts and Fast Interrupts (IRQ/FIQ) to a previous state
 * @param IRQFIQMask IRQ/FIQ state to restore
 * @return IRQ/FIQ state when called
 */
IRQ_FIQ_MASK STDCALL restore_irq_fiq(IRQ_FIQ_MASK irqfiqmask);

/**
 * @brief Get Abort state
 * @return True if enabled, False if disabled
 */
BOOL STDCALL get_abort(void);

/**
 * @brief Enable Abort unconditionally
 */
void STDCALL enable_abort(void);

/**
 * @brief Disable Abort unconditionally
 */
void STDCALL disable_abort(void);

/**
 * @brief Disable Abort and return the previous state
 * @return Abort state when called
 */
ABORT_MASK STDCALL save_abort(void);

/**
 * @brief Restore Abort to a previous state
 * @param AbortMask Abort state to restore
 * @return Abort state when called
 */
ABORT_MASK STDCALL restore_abort(ABORT_MASK abortmask);

/**
 * @brief Halt the current processor
 */
void STDCALL halt_cpu(void);

/**
 * @brief Pause the current processor and wait for an Event or Interrupt (Where Applicable)
 */
void STDCALL pause_cpu(void);

/**
 * @brief Halt the current thread
 */
uint32_t STDCALL halt_thread(uint32_t exitcode);

/**
 * @brief Send a signal that an Event has occurred (Where Applicable)
 */
void STDCALL send_event(void);

/**
 * @brief Wait for an Event to occur (Where Applicable)
 */
void STDCALL wait_for_event(void);

/**
 * @brief Wait for an Interrupt to occur (Where Applicable)
 */
void STDCALL wait_for_interrupt(void);

/**
 * @brief Perform a Read Memory Barrier operation (Where Applicable)
 */
void STDCALL read_memory_barrier(void);

/**
 * @brief Perform a Write Memory Barrier operation (Where Applicable)
 */
void STDCALL write_memory_barrier(void);

/**
 * @brief Perform a Data Memory Barrier operation (Where Applicable)
 */
void STDCALL data_memory_barrier(void);

/**
 * @brief Perform a Data Synchronization Barrier operation (Where Applicable)
 */
void STDCALL data_synchronization_barrier(void);

/**
 * @brief Perform an Instruction Memory Barrier operation (Where Applicable)
 */
void STDCALL instruction_memory_barrier(void);

/**
 * @brief Perform an Invalidate Entire TLB operation (Where Applicable)
 */
void STDCALL invalidate_tlb(void);

/**
 * @brief Perform an Invalidate Data TLB operation (Where Applicable)
 */
void STDCALL invalidate_data_tlb(void);

/**
 * @brief Perform an Invalidate Instruction TLB operation (Where Applicable)
 */
void STDCALL invalidate_instruction_tlb(void);

/**
 * @brief Perform an Invalidate Entire Cache operation (Where Applicable)
 */
void STDCALL invalidate_cache(void);

/**
 * @brief Perform a Clean Data Cache operation (Where Applicable)
 */
void STDCALL clean_data_cache(void);

/**
 * @brief Perform an Invalidate Data Cache operation (Where Applicable)
 */
void STDCALL invalidate_data_cache(void);

/**
 * @brief Perform a Clean and Invalidate Data Cache operation (Where Applicable)
 */
void STDCALL clean_and_invalidate_data_cache(void);

/**
 * @brief Perform an Invalidate Instruction Cache operation (Where Applicable)
 */
void STDCALL invalidate_instruction_cache(void);

/**
 * @brief Perform a Clean Data Cache Range operation (Where Applicable)
 */
void STDCALL clean_data_cache_range(size_t address, uint32_t size);

/**
 * @brief Perform an Invalidate Data Cache Range operation (Where Applicable)
 */
void STDCALL invalidate_data_cache_range(size_t address, uint32_t size);

/**
 * @brief Perform a Clean and Invalidate Data Cache Range operation (Where Applicable)
 */
void STDCALL clean_and_invalidate_data_cache_range(size_t address, uint32_t size);

/**
 * @brief Perform an Invalidate Instruction Cache Range operation (Where Applicable)
 */
void STDCALL invalidate_instruction_cache_range(size_t address, uint32_t size);

/**
 * @brief Perform a Flush Prefetch Buffer operation (Where Applicable)
 */
void STDCALL flush_prefetch_buffer(void);

/**
 * @brief Perform a Flush Entire Branch Target Cache operation (Where Applicable)
 */
void STDCALL flush_branch_target_cache(void);

/**
 * @brief Perform a Context Switch from one thread to another
 */
void STDCALL context_switch(void *oldstack, void *newstack, THREAD_HANDLE newthread);

/**
 * @brief Perform a Context Switch from one thread to another from an IRQ handler
 */
void STDCALL context_switch_irq(void *oldstack, void *newstack, THREAD_HANDLE newthread);

/**
 * @brief Perform a Context Switch from one thread to another from an FIQ handler
 */
void STDCALL context_switch_fiq(void *oldstack, void *newstack, THREAD_HANDLE newthread);

/**
 * @brief Perform a Context Switch from one thread to another from a software interrupt handler
 */
void STDCALL context_switch_swi(void *oldstack, void *newstack, THREAD_HANDLE newthread);

/**
 * @brief Perform an atomic OR operation
 */
int32_t STDCALL interlocked_or(int32_t *target, int32_t value);

/**
 * @brief Perform an atomic XOR operation
 */
int32_t STDCALL interlocked_xor(int32_t *target, int32_t value);

/**
 * @brief Perform an atomic AND operation
 */
int32_t STDCALL interlocked_and(int32_t *target, int32_t value);

/**
 * @brief Perform an atomic decrement operation
 */
int32_t STDCALL interlocked_decrement(int32_t *target);

/**
 * @brief Perform an atomic increment operation
 */
int32_t STDCALL interlocked_increment(int32_t *target);

/**
 * @brief Perform an atomic exchange operation
 */
int32_t STDCALL interlocked_exchange(int32_t *target, int32_t source);

/**
 * @brief Perform an atomic add and exchange operation
 */
int32_t STDCALL interlocked_add_exchange(int32_t *target, int32_t source);

/**
 * @brief Perform an atomic compare and exchange operation
 */
int32_t STDCALL interlocked_compare_exchange(int32_t *target, int32_t source, int32_t compare);

/**
 * @brief Get the number of page table levels for the current platform
 */
uint32_t STDCALL page_table_get_levels(void);

/**
 * @brief Get the base address of the first level page directory (Where applicable)
 */
size_t STDCALL page_directory_get_base(void);

/**
 * @brief Get the size of the first level page directory (Where applicable)
 */
uint32_t STDCALL page_directory_get_size(void);

/**
 * @brief Get the base address of the first or second level page table
 */
size_t STDCALL page_table_get_base(void);

/**
 * @brief Get the size of the first or second level page table
 */
uint32_t STDCALL page_table_get_size(void);

/**
 * @brief Get the Page Table entry that corresponds to the supplied virtual address
 */
void STDCALL page_table_get_entry(size_t address, PAGE_TABLE_ENTRY *entry);

/**
 * @brief Set the Page Table entry that corresponds to the supplied virtual address
 */
uint32_t STDCALL page_table_set_entry(PAGE_TABLE_ENTRY *entry);

/**
 * @brief Get the Size from the Page Table page that corresponds to the supplied virtual address
 */
uint32_t STDCALL page_table_get_page_size(size_t address);

/**
 * @brief Get the Flags from the Page Table page that corresponds to the supplied virtual address
 */
uint32_t STDCALL page_table_get_page_flags(size_t address);

#if defined (__i386__) || defined (__arm__)
/**
 * @brief Get the Physical Range from the Page Table page that corresponds to the supplied virtual address
 */
uint32_t STDCALL page_table_get_page_range(size_t address);
#endif

/**
 * @brief Get the Physical Address from the Page Table page that corresponds to the supplied virtual address
 */
size_t STDCALL page_table_get_page_physical(size_t address);

/**
 * @brief Get the address of the second or third level page tables
 */
size_t STDCALL page_tables_get_address(void);

/**
 * @brief Get the size of the second or third level page tables
 */
uint32_t STDCALL page_tables_get_length(void);

/**
 * @brief Get the number of second or third level page tables
 */
uint32_t STDCALL page_tables_get_count(void);

/**
 * @brief Get the multiplier to convert count to actual size of the second or third level page tables
 */
uint32_t STDCALL page_tables_get_shift(void);

/**
 * @brief Get the address of the next available second or third level page table
 */
size_t STDCALL page_tables_get_next(void);

/**
 * @brief Get the number of used second or third level page tables
 */
uint32_t STDCALL page_tables_get_used(void);

/**
 * @brief Get the number of available second or third level page tables
 */
uint32_t STDCALL page_tables_get_free(void);

/**
 * @brief Get the base address of the interrupt vector table
 */
size_t STDCALL vector_table_get_base(void);

/**
 * @brief Get the size in bytes of the interrupt vector table
 */
uint32_t STDCALL vector_table_get_size(void);

/**
 * @brief Get the number of entries in the interrupt vector table
 */
uint32_t STDCALL vector_table_get_count(void);

/**
 * @brief Get the interrupt vector table entry that corresponds to the supplied number
 */
size_t STDCALL vector_table_get_entry(uint32_t number);

/**
 * @brief Set the interrupt vector table entry that corresponds to the supplied number
 */
uint32_t STDCALL vector_table_set_entry(uint32_t number, size_t address);

/** Console Functions */
BOOL STDCALL console_get_key(char *ch, void *userdata);
BOOL STDCALL console_peek_key(char *ch, void *userdata);

BOOL STDCALL console_write_char(char ch, void *userdata);
BOOL STDCALL console_read_char(char *ch, void *userdata);
BOOL STDCALL console_read_wide_char(WCHAR *ch, void *userdata);

BOOL STDCALL console_hide_mouse(void *userdata);
BOOL STDCALL console_show_mouse(uint32_t x, uint32_t y, void *userdata);
BOOL STDCALL console_read_mouse(uint32_t *x, uint32_t *y, uint32_t *buttons, void *userdata);

/** CodePage Functions */
WCHAR STDCALL code_page_to_wide_char(char ch);
char STDCALL wide_char_to_code_page(WCHAR ch);

/** Name Functions */
uint32_t STDCALL host_get_name(char *name, uint32_t len);
BOOL STDCALL host_set_name(const char *name);
uint32_t STDCALL host_get_domain(char *domain, uint32_t len);
BOOL STDCALL host_set_domain(const char *domain);

/** Module Functions */
HANDLE STDCALL module_load(const char *name);
HANDLE STDCALL module_load_ex(const char *name, uint32_t flags);
BOOL STDCALL module_unload(HANDLE handle);
uint32_t STDCALL module_get_name(HANDLE handle, char *name, uint32_t len);
HANDLE STDCALL module_get_handle(char *name);

/** Symbol Functions */
BOOL STDCALL symbol_add(HANDLE handle, const char *name, size_t address);
BOOL STDCALL symbol_remove(HANDLE handle, const char *name);
size_t STDCALL symbol_get_address(HANDLE handle, const char *name);

/** Logging Functions */
void STDCALL logging_output(const char *text);
void STDCALL logging_output_ex(uint32_t facility, uint32_t severity, const char *tag, const char *content);

/**
 * @brief Output formatted text to the default logging
 * @param Format The formatted text to output (As per printf in standard C library)
 * @return On success the total number of characters output to the logging device, on error a negative value is returned and errno is set to the error code
 */
int STDCALL logging_outputf(const char *format, ...) _ATTRIBUTE ((__format__ (__printf__, 1, 2)));

/** Environment Functions */

/**
 * @brief Locate an environment variable and return the current value
 * @param Name The name of the variable to locate (eg TZ)
 * @return The value of the variable or an empty string if not found
 */
uint32_t STDCALL environment_get(const char *name, char *value, uint32_t len);

/**
 * @brief Add an environment variable or update an existing variable
 * @param Name The name of the variable to add or update (eg TZ)
 * @param Value The new value of the variable (eg EST+5)
 * @return ERROR_SUCCESS if the value was set or another error code on failure
 * @note Passing an empty value will delete the environment variable if it exists
 */
uint32_t STDCALL environment_set(const char *name, const char *value);

/**
 * @brief Get the current number of environment variables
 * @param Reset If True then force a recount
 * @return The number of environment variables
 */
uint32_t STDCALL environment_count(BOOL reset);

/**
 * @brief Locate an environment variable and return the index
 * @param Name The name of the variable to locate (eg TZ)
 * @return The index of the environment variable or 0 if not found
 */
uint32_t STDCALL environment_index(const char *name);

/**
 * @brief Get an environment variable by index
 * @param Index The index of the variable to get (1 to EnvironmentCount)
 * @return The environment variable or an empty string if index is not valid
 */
uint32_t STDCALL environment_string(uint32_t index, char *string, uint32_t len);

/** Environment Functions (From stdlib.h) */
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);

/** Utility Functions */

/**
 * @brief Find the first set bit in a nonzero 32 bit value
 * @return 31 for MSB and 0 for LSB (0xFFFFFFFF / -1 if no bits are set)
 * @note Similar in operation to the fls() macro, equivalent to fls() - 1
 */
uint32_t STDCALL first_bit_set(uint32_t value);

/**
 * @brief Find the last set bit in a nonzero 32 bit value
 * @return 31 for MSB and 0 for LSB (0xFFFFFFFF / -1 if no bits are set)
 * @note Similar in operation to the ffs() builtin, equivalent to ffs() - 1
 */
uint32_t STDCALL last_bit_set(uint32_t value);

/**
 * @brief Count the number of leading 0 bits in a nonzero 32 bit value
 * @return 32 if no bits are set
 */
uint32_t STDCALL count_leading_zeros(uint32_t value);

/**
 * @brief Count the number of trailing 0 bits in a nonzero 32 bit value
 * @return 32 if no bits are set
 */
uint32_t STDCALL count_trailing_zeros(uint32_t value);

/**
 * @brief Convert Physical address to an IO addresses (Where Applicable)
 */
size_t STDCALL physical_to_io_address(void *address);

/**
 * @brief Convert an IO address to a Physical address (Where Applicable)
 */
size_t STDCALL io_address_to_physical(void *address);

/**
 * @brief Convert a Physical address to a Bus address (Where Applicable)
 */
size_t STDCALL physical_to_bus_address(void *address);

/**
 * @brief Convert a Bus address to a Physical address (Where Applicable)
 */
size_t STDCALL bus_address_to_physical(void *address);

/**
 * @brief Non sleep wait for a number of nanoseconds
 * @param Nanoseconds Number of nanoseconds to wait
 */
void STDCALL nanosecond_delay(uint32_t nanoseconds);

/**
 * @brief Non sleep wait for a number of microseconds
 * @param Microseconds Number of microseconds to wait
 */
void STDCALL microsecond_delay(uint32_t microseconds);

/**
 * @brief Non sleep wait for a number of milliseconds
 * @param Milliseconds Number of milliseconds to wait
 */
void STDCALL millisecond_delay(uint32_t milliseconds);

/**
 * @brief Non sleep wait for a number of nanoseconds
 * @param Nanoseconds Number of nanoseconds to wait
 * @param Wait Use WaitForEvent on each loop to reduce power consumption
 * @note Not suitable for use by interrupt handlers if wait is true
 */
void STDCALL nanosecond_delay_ex(uint32_t nanoseconds, BOOL wait);

/**
 * @brief Non sleep wait for a number of microseconds
 * @param Microseconds Number of microseconds to wait
 * @param Wait Use WaitForEvent on each loop to reduce power consumption
 * @note Not suitable for use by interrupt handlers if wait is true
 */
void STDCALL microsecond_delay_ex(uint32_t microseconds, BOOL wait);

/**
 * @brief Non sleep wait for a number of milliseconds
 * @param Milliseconds Number of milliseconds to wait
 * @param Wait Use WaitForEvent on each loop to reduce power consumption
 * @note Not suitable for use by interrupt handlers if wait is true
 */
void STDCALL millisecond_delay_ex(uint32_t milliseconds, BOOL wait);

/** RTL Functions */
uint32_t get_tick_count(void);
uint64_t get_tick_count64(void);

/** LIBC Functions (From stdlib.h) */
int posix_memalign(void **memptr, size_t alignment, size_t size);
char *realpath(const char *__restrict path, char *__restrict resolved_path);
int getpagesize(void);

/** LIBC Functions (From unistd.h) */
int dup3(int oldfd, int newfd, int flags);
int getentropy(void *buffer, size_t length);
int usleep(useconds_t useconds);
int symlink(const char *path1, const char *path2);

int ftruncate(int fd, off_t length);
int truncate(const char *path, off_t length);

int fdatasync(int fd);

int sethostname (const char *name, size_t size);
#if !(defined (_WINSOCK_H) || defined (_WINSOCKAPI_) || defined (__USE_W32_SOCKETS))
/** winsock[2].h defines as __stdcall, and with int as 2nd arg */
 int gethostname (char *name, size_t size);
#endif

/** LIBC Functions (From sys/mman.h) */
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);

/** LIBC Functions (From sys/time.h) */
int settimeofday(const struct timeval *tv, const struct timezone *tz);

/** LIBC Functions (From sched.h) */
int sched_getcpu(void);
#ifdef _SYS_CPUSET_H_
int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
int sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
#endif /* _SYS_CPUSET_H_ */

/** LIBC Functions (Non Standard) */
void msleep(unsigned int msecs);
pid_t gettid(void);
HANDLE fd_handle(int fd);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PLATFORM_H