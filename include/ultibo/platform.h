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
#ifndef _ULTIBO_PLATFORM_H
#define _ULTIBO_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"

/* ============================================================================== */
/* Platform specific constants */

/* Handle Flags */
#define HANDLE_FLAG_NONE	0x00000000
#define HANDLE_FLAG_NAMED	0x00000001 // Set if the handle has a name
#define HANDLE_FLAG_DUPLICATE	0x00000002 // Set if the handle can be duplicated

#define HANDLE_FLAG_INTERNAL	HANDLE_FLAG_NONE + $80000000 // Note: Temporary value to avoid warning

/* Handle constants */
#define HANDLE_SIGNATURE	0xCD15E20A

#define HANDLE_TABLE_MIN	0x100 // Minimum handle number (Skip first 256)
#define HANDLE_TABLE_MAX	0x7FFFFFFF // Maximum handle number (Avoid MSB as THandle is a signed value)

#define HANDLE_TABLE_MASK	0x7FF // 2048 buckets for handle lookups

#define HANDLE_NAME_LENGTH	256 // Maximum length of handle name

/* DMA Data Flags */
#define DMA_DATA_FLAG_NONE	0x00000000
#define DMA_DATA_FLAG_STRIDE	0x00000001 // Transfer from the source to the destination using 2D stride (If supported)
#define DMA_DATA_FLAG_SOURCE_NOINCREMENT	0x00000002 // Don't increment the source address during the DMA request (If supported)
#define DMA_DATA_FLAG_DEST_NOINCREMENT	0x00000004 // Don't increment the dest address during the DMA request (If supported)
#define DMA_DATA_FLAG_SOURCE_DREQ	0x00000008 // Use DREQ gating on the source address during the DMA request (If supported)
#define DMA_DATA_FLAG_DEST_DREQ	0x00000010 // Use DREQ gating on the dest address during the DMA request (If supported)
#define DMA_DATA_FLAG_SOURCE_WIDE	0x00000020 // Use wide reads on the source address during the DMA request (If supported)
#define DMA_DATA_FLAG_DEST_WIDE	0x00000040 // Use wide writes on the dest address during the DMA request (If supported)
#define DMA_DATA_FLAG_NOREAD	0x00000080 // Ignore the source address and zero fill the destination (If supported)
#define DMA_DATA_FLAG_NOWRITE	0x00000100 // Ignore the dest address and cache fill from the source (If supported)
#define DMA_DATA_FLAG_NOCLEAN	0x00000200 // Do not perform cache clean on the source address (If applicable)
#define DMA_DATA_FLAG_NOINVALIDATE	0x00000400 // Do not perform cache invalidate on the dest address (If applicable)
#define DMA_DATA_FLAG_BULK	0x00000800 // Perform a bulk transfer (Higher transfer throughput)(If applicable)
#define DMA_DATA_FLAG_LITE	0x00001000 // Perform a "lite" transfer (Lower transfer throughput but less waiting for free channel) (If applicable)
#define DMA_DATA_FLAG_40BIT	0x00002000 // Perform a 40-bit address transfer (Address to memory above 1GB or 4GB depending on SoC) (If applicable)

/* Page Table Flags */
#define PAGE_TABLE_FLAG_NONE	0x00000000
/* Reserved 0x00000001 (Previously used incorrectly for PAGE_TABLE_FLAG_NONE) */
#define PAGE_TABLE_FLAG_NORMAL	0x00000002 // Page Table Entry represents Normal memory
#define PAGE_TABLE_FLAG_DEVICE	0x00000004 // Page Table Entry represents Device memory
#define PAGE_TABLE_FLAG_ORDERED	0x00000008 // Page Table Entry represents Ordered memory
#define PAGE_TABLE_FLAG_SHARED	0x00000010 // Page Table Entry represents Shared memory
#define PAGE_TABLE_FLAG_CACHEABLE	0x00000020 // Page Table Entry represents Cacheable memory
#define PAGE_TABLE_FLAG_READONLY	0x00000040 // Page Table Entry represents Read Only memory
#define PAGE_TABLE_FLAG_READWRITE	0x00000080 // Page Table Entry represents Read Write memory
#define PAGE_TABLE_FLAG_EXECUTABLE	0x00000100 // Page Table Entry represents Executable memory
#define PAGE_TABLE_FLAG_WRITEBACK	0x00000200 // Page Table Entry is Writeback Cacheable memory
#define PAGE_TABLE_FLAG_WRITETHROUGH	0x00000400 // Page Table Entry is Writethrough Cacheable memory
#define PAGE_TABLE_FLAG_WRITEALLOCATE	0x00000800 // Page Table Entry is Writeallocate Cacheable memory
#if defined (__i386__) || defined (__arm__)
#define PAGE_TABLE_FLAG_LARGEADDRESS	0x00001000 // Page Table Entry is mapped to Large Physical Address range
#endif

/* Interrupt Entry Flags */
#define INTERRUPT_FLAG_NONE	0x00000000
#define INTERRUPT_FLAG_SHARED	0x00000001 // A shared interrupt, multiple devices can register for the same interrupt and each will be called until one returns INTERRUPT_RETURN_HANDLED
#define INTERRUPT_FLAG_LOCAL	0x00000002 // A local interrupt, generated only on the CPU it is associated with
#define INTERRUPT_FLAG_IPI	0x00000004 // A software interrupt or inter processor interrupt, generated by a software request instead of hardware
#define INTERRUPT_FLAG_FIQ	0x00000008 // A fast interrupt, takes precedence over all other interrupts (where applicable)
#define INTERRUPT_FLAG_CHAINED	0x00000010 // A chained interrupt, multiple devices can register for the same interrupt and all will be called when it occurs

/* Interrupt Priority Values */
#define INTERRUPT_PRIORITY_MAXIMUM	0x00
#define INTERRUPT_PRIORITY_FIQ	0x40
#define INTERRUPT_PRIORITY_DEFAULT	0xA0
#define INTERRUPT_PRIORITY_MINIMUM	0xF0

/* Interrupt Return Values */
#define INTERRUPT_RETURN_NONE	0 // Shared interrupt not handled or not for this device
#define INTERRUPT_RETURN_HANDLED	1 // Shared interrupt handled, no further processing

/* Vector Table Entries */
/* ARM */
#define VECTOR_TABLE_ENTRY_ARM_RESET	0 // ARM Reset Vector
#define VECTOR_TABLE_ENTRY_ARM_UNDEFINED	1 // ARM Undefined Vector
#define VECTOR_TABLE_ENTRY_ARM_SWI	2 // ARM Software Interrupt (SWI) Vector
#define VECTOR_TABLE_ENTRY_ARM_PREFETCH	3 // ARM Prefetch Abort Vector
#define VECTOR_TABLE_ENTRY_ARM_ABORT	4 // ARM Data Abort Vector
#define VECTOR_TABLE_ENTRY_ARM_RESERVED	5 // ARM Reserved Vector
#define VECTOR_TABLE_ENTRY_ARM_IRQ	6 // ARM IRQ Vector
#define VECTOR_TABLE_ENTRY_ARM_FIQ	7 // ARM FIQ Vector
/* AARCH64 */

/* Shutdown Flags */
#define SHUTDOWN_FLAG_NONE	0x00000000
#define SHUTDOWN_FLAG_RESTART	0x00000001 // The system is shutting down and restarting
#define SHUTDOWN_FLAG_FORCE	0x00000002 // Forced shutdown or restart requested, registered callbacks will be bypassed

/* Shutdown constants */
#define SHUTDOWN_SIGNATURE	0xA73D8B0C

#define SHUTDOWN_DEFAULT_DELAY	1000 // Default delay before starting a shutdown or restart (Milliseconds)
#define SHUTDOWN_MINIMUM_DELAY	10 // Minimum delay before starting a shutdown or restart (Milliseconds)

#define SHUTDOWN_DEFAULT_TIMEOUT	5000 // Default time to wait for a shutdown callback to complete before continuing (Milliseconds)

/* Exception Types */
#define EXCEPTION_TYPE_DATA_ABORT	1
#define EXCEPTION_TYPE_PREFETCH_ABORT	2
#define EXCEPTION_TYPE_UNDEFINED_INSTRUCTION	3

/* Firmware Throttling Flags */
#define FIRMWARE_THROTTLE_NONE	(0 << 0)
#define FIRMWARE_THROTTLE_UNDER_VOLTAGE	(1 << 0) // Under voltage is occurring
#define FIRMWARE_THROTTLE_FREQUENCY_LIMIT	(1 << 1) // Frequency limiting is occurring
#define FIRMWARE_THROTTLE_THROTTLED	(1 << 2) // Throttling is occurring
#define FIRMWARE_THROTTLE_SOFT_TEMP_LIMIT	(1 << 3) // Soft temperature limit is active
#define FIRMWARE_THROTTLE_WAS_UNDER_VOLTAGE	(1 << 16) // Under voltage has occurred
#define FIRMWARE_THROTTLE_WAS_FREQUENCY_LIMIT	(1 << 17) // Frequency limiting has occurred
#define FIRMWARE_THROTTLE_WAS_THROTTLED	(1 << 18) // Throttling has occurred
#define FIRMWARE_THROTTLE_WAS_SOFT_TEMP_LIMIT	(1 << 19) // Soft temperature limit has occurred

/* ============================================================================== */
/* Platform specific types */

/* IRQ/FIQ Masks */
typedef uint32_t IRQ_MASK;
typedef uint32_t FIQ_MASK;
typedef uint32_t IRQ_FIQ_MASK;

/* Abort Masks */
typedef uint32_t ABORT_MASK;

/* DMA Data */
typedef struct _DMA_DATA DMA_DATA;
struct _DMA_DATA
{
	// Data Properties
	void *source; // Source address for DMA (May need to be allocated in accordance with DMA host configuration)
	#if defined (__i386__) || defined (__arm__)
	uint32_t sourcerange; // Source address range for DMA (Only applicable when performing a 40-bit transfer)
	#endif
	void *dest; // Dest address for DMA (May need to be allocated in accordance with DMA host configuration)
	#if defined (__i386__) || defined (__arm__)
	uint32_t destrange; // Dest address range for DMA (Only applicable when performing a 40-bit transfer)
	#endif
	uint32_t size; // Size for DMA transfer (For 2D stride the length of a row multiplied by the count of rows)
	uint32_t flags; // Flags for DMA transfer (See DMA_DATA_FLAG_* above)
	// Stride Properties
	uint32_t stridelength; // Length of each row during 2D stride (If supported)
	int32_t sourcestride; // Increment between rows for source address during 2D stride (If supported)
	int32_t deststride; // Increment between rows for destination address during 2D stride (If supported)
	// Next Block
	DMA_DATA *next; // Link to next DMA data block (or nil for the last block)
};

/* System Call Request (SWI) */
typedef struct _SYSTEM_CALL_REQUEST SYSTEM_CALL_REQUEST;
struct _SYSTEM_CALL_REQUEST
{
	uint32_t number;
	size_t param1;
	size_t param2;
	size_t param3;
};

/* Prototypes for Handle methods */
typedef void STDCALL (*handle_close_proc)(HANDLE data);
typedef uint32_t STDCALL (*handle_close_ex_proc)(HANDLE data);
typedef HANDLE STDCALL (*handle_duplicate_proc)(HANDLE data);

/* Handle Entry */
typedef struct _HANDLE_ENTRY HANDLE_ENTRY;

/* Handle Enumeration Callback */
typedef uint32_t STDCALL (*handle_enumerate_cb)(HANDLE_ENTRY *handle, void *data);

struct _HANDLE_ENTRY
{
	// Handle Properties
	uint32_t signature; // Signature for entry validation
	HANDLE handle; // Handle (Number) of this Handle
	uint32_t handletype; // Type of this Handle (eg HANDLE_TYPE_FILE)
	uint32_t count; // Reference Count of the Handle
	uint32_t flags; // Flags for the Handle (eg HANDLE_FLAG_NAMED)
	char *name; // The name of the Handle (Optional)
	uint32_t hash; // Hash of the Handle name (Only if named)
	HANDLE data; // Purpose specific data for the Handle (eg a file handle or a socket handle)
	handle_close_proc close; // Procedure to call on final close (Optional)
	handle_close_ex_proc closeex; // Function to call on final close (Optional)
	handle_duplicate_proc duplicate; // Function to call when duplicating handle (Optional)
	// Internal Properties
	HANDLE_ENTRY *prev; // Previous entry in Handle table
	HANDLE_ENTRY *next; // Next entry in Handle table
	// Statistics Properties
};

/* Prototype for Shutdown Callback */
typedef uint32_t STDCALL (*shutdown_cb)(uint32_t flags, void *parameter);

/* Prototypes for Interrupt (IRQ/FIQ) Handlers */
typedef void STDCALL (*interrupt_handler)(void *parameter);
typedef THREAD_HANDLE STDCALL (*interrupt_ex_handler)(uint32_t cpuid, THREAD_HANDLE thread, void *parameter);
typedef uint32_t STDCALL (*shared_interrupt_handler)(uint32_t number, uint32_t cpuid, uint32_t flags, void *parameter);

/* Interrupt Entry (IRQ/FIQ */
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

/* System Call Entry (SWI) */
typedef struct _SYSTEM_CALL_ENTRY SYSTEM_CALL_ENTRY;
struct _SYSTEM_CALL_ENTRY
{
	uint32_t number;
	uint32_t cpuid;
    void STDCALL (*handler)(SYSTEM_CALL_REQUEST *request);
    THREAD_HANDLE STDCALL (*handlerex)(uint32_t cpuid, THREAD_HANDLE thread, SYSTEM_CALL_REQUEST *request);
};

/* Page Table Entry */
typedef struct _PAGE_TABLE_ENTRY PAGE_TABLE_ENTRY;
struct _PAGE_TABLE_ENTRY
{
	size_t virtualaddress;
#if defined (__i386__) || defined (__arm__)
	uint32_t physicalrange; // Physical Address Range referenced by entry when using Large Physical Address Extensions (LPAE)
#endif
	size_t physicaladdress;
	uint32_t size;
	uint32_t flags;
};

/* Prototype for Inter Processor Interrupt (IPI) Handlers */
/* Note: When used for IPI the CPUID parameter will be the sending CPU */
typedef shared_interrupt_handler ipi_handler;

/* Prototype for System Call (SWI) Handlers */
typedef void STDCALL (*system_call_handler)(SYSTEM_CALL_REQUEST *request);
typedef THREAD_HANDLE STDCALL (*system_call_ex_handler)(uint32_t cpuid, THREAD_HANDLE thread, SYSTEM_CALL_REQUEST *request);

/* Prototypes for Thread Yield/Wait/Release/Abandon Handlers */
typedef uint32_t STDCALL (*thread_yield_proc)(void);
typedef uint32_t STDCALL (*thread_wait_proc)(LIST_HANDLE list, SPIN_HANDLE lock, uint32_t flags);
typedef uint32_t STDCALL (*thread_wait_ex_proc)(LIST_HANDLE list, SPIN_HANDLE lock, uint32_t flags, uint32_t timeout);
typedef uint32_t STDCALL (*thread_release_proc)(LIST_HANDLE list);
typedef uint32_t STDCALL (*thread_abandon_proc)(LIST_HANDLE list);

/* Prototype for Timer Event Handler */
typedef void STDCALL (*timer_event_proc)(void *data);

/* Prototype for Worker Task/Callback Handlers */
typedef void STDCALL (*worker_task_proc)(void *data);
typedef void STDCALL (*worker_cb)(void *data);

/* Prototype for Counter Callback Handlers */
typedef void STDCALL (*counter_event_cb)(void *data);

/* Prototype for GPIO Callback Handlers */
typedef void STDCALL (*gpio_event_cb)(void *data, uint32_t pin, uint32_t trigger);

/* ============================================================================== */
/* Device Tree Functions */
BOOL STDCALL device_tree_valid(void);
size_t STDCALL device_tree_get_base(void);
uint32_t STDCALL device_tree_get_size(void);

uint32_t STDCALL device_tree_read(const char *path, const char *name, void *buffer, uint32_t *size);
uint32_t STDCALL device_tree_read32(const char *path, const char *name, uint32_t *value);
uint32_t STDCALL device_tree_read64(const char *path, const char *name, uint64_t *value);
uint32_t STDCALL device_tree_read_string(const char *path, const char *name, char *value, uint32_t len);

/* ============================================================================== */
/* Boot Functions */
void STDCALL boot_blink(void);
void STDCALL boot_output(uint32_t value);
void STDCALL boot_console_start(void);
void STDCALL boot_console_write(const char *value);
void STDCALL boot_console_write_ex(const char *value, uint32_t x, uint32_t y);
uint32_t STDCALL boot_console_get_x(void);
uint32_t STDCALL boot_console_get_y(void);

/* ============================================================================== */
/* LED Functions */
void STDCALL power_led_enable(void);
void STDCALL power_led_on(void);
void STDCALL power_led_off(void);

void STDCALL activity_led_enable(void);
void STDCALL activity_led_on(void);
void STDCALL activity_led_off(void);

/* ============================================================================== */
/* Counter Functions (Timer device) */
BOOL STDCALL counter_available(void);

uint32_t STDCALL counter_read(void);
int64_t STDCALL counter_read64(void);
uint32_t STDCALL counter_wait(void);
uint32_t STDCALL counter_event(counter_event_cb callback, void *data);
uint32_t STDCALL counter_cancel(void);

uint32_t STDCALL counter_get_rate(void);
uint32_t STDCALL counter_set_rate(uint32_t rate);

uint32_t STDCALL counter_get_interval(void);
uint32_t STDCALL counter_set_interval(uint32_t interval);

/* ============================================================================== */
/* Mailbox Functions */
uint32_t STDCALL mailbox_receive(uint32_t mailbox, uint32_t channel);
void STDCALL mailbox_send(uint32_t mailbox, uint32_t channel, uint32_t data);

uint32_t STDCALL mailbox_call(uint32_t mailbox, uint32_t channel, uint32_t data, uint32_t *response);
uint32_t STDCALL mailbox_call_ex(uint32_t mailbox, uint32_t channel, uint32_t data, uint32_t *response, uint32_t timeout);
uint32_t STDCALL mailbox_property_call(uint32_t mailbox, uint32_t channel, void *data, uint32_t *response);
uint32_t STDCALL mailbox_property_call_ex(uint32_t mailbox, uint32_t channel, void *data, uint32_t *response, uint32_t timeout);

uint32_t STDCALL mailbox_property_tag(uint32_t tag, void *data, uint32_t size);

/* ============================================================================== */
/* Random Number Functions */
BOOL STDCALL random_available(void);

void STDCALL random_seed(uint32_t seed);

int32_t STDCALL random_read_longint(int32_t limit);
int64_t STDCALL random_read_int64(int64_t limit);
double_t STDCALL random_read_double(void);
double_t STDCALL random_read_extended(void);

/* ============================================================================== */
/* Watchdog Functions */
BOOL STDCALL watchdog_available(void);

uint32_t STDCALL watchdog_start(uint32_t milliseconds);
uint32_t STDCALL watchdog_stop(void);
uint32_t STDCALL watchdog_refresh(uint32_t milliseconds);

/* ============================================================================== */
/* Interrupt Request (IRQ) Functions */
uint32_t STDCALL request_irq(uint32_t cpuid, uint32_t number, interrupt_handler handler, void *parameter);
uint32_t STDCALL release_irq(uint32_t cpuid, uint32_t number, interrupt_handler handler, void *parameter);
uint32_t STDCALL request_ex_irq(uint32_t cpuid, uint32_t number, interrupt_handler handler, interrupt_ex_handler handlerex, void *parameter);
uint32_t STDCALL release_ex_irq(uint32_t cpuid, uint32_t number, interrupt_handler handler, interrupt_ex_handler handlerex, void *parameter);

/* ============================================================================== */
/* Fast Interrupt Request (FIQ) Functions */
uint32_t STDCALL request_fiq(uint32_t cpuid, uint32_t number, interrupt_handler handler, void *parameter);
uint32_t STDCALL release_fiq(uint32_t cpuid, uint32_t number, interrupt_handler handler, void *parameter);
uint32_t STDCALL request_ex_fiq(uint32_t cpuid, uint32_t number, interrupt_handler handler, interrupt_ex_handler handlerex, void *parameter);
uint32_t STDCALL release_ex_fiq(uint32_t cpuid, uint32_t number, interrupt_handler handler, interrupt_ex_handler handlerex, void *parameter);

/* ============================================================================== */
/* Inter Processor Interrupt (IPI) Functions */
uint32_t STDCALL request_ipi(uint32_t cpuid, uint32_t number, ipi_handler handler, void *parameter);
uint32_t STDCALL release_ipi(uint32_t cpuid, uint32_t number, ipi_handler handler, void *parameter);

/* ============================================================================== */
/* Interrupt Register/Deregister Functions */
uint32_t STDCALL register_interrupt(uint32_t number, uint32_t mask, uint32_t priority, uint32_t flags, shared_interrupt_handler handler, void *parameter);
uint32_t STDCALL deregister_interrupt(uint32_t number, uint32_t mask, uint32_t priority, uint32_t flags, shared_interrupt_handler handler, void *parameter);

/* ============================================================================== */
/* System Call (SWI) Functions */
void STDCALL system_call(uint32_t number, size_t param1, size_t param2, size_t param3);

uint32_t STDCALL register_system_call(uint32_t number, system_call_handler handler);
uint32_t STDCALL deregister_system_call(uint32_t number, system_call_handler handler);
uint32_t STDCALL register_system_call_ex(uint32_t cpuid, uint32_t number, system_call_handler handler, system_call_ex_handler handlerex);
uint32_t STDCALL deregister_system_call_ex(uint32_t cpuid, uint32_t number, system_call_handler handler, system_call_ex_handler handlerex);

/* ============================================================================== */
/* Interrupt Entry Functions */
uint32_t STDCALL get_interrupt_count(void);
uint32_t STDCALL get_interrupt_start(void);
uint32_t STDCALL get_interrupt_entry(uint32_t number, uint32_t instance, INTERRUPT_ENTRY *interrupt);

/* ============================================================================== */
/* Local Interrupt Entry Functions */
uint32_t STDCALL get_local_interrupt_count(void);
uint32_t STDCALL get_local_interrupt_start(void);
uint32_t STDCALL get_local_interrupt_entry(uint32_t cpuid, uint32_t number, uint32_t instance, INTERRUPT_ENTRY *interrupt);

/* ============================================================================== */
/* Software Interrupt Entry (IPI) Functions */
uint32_t STDCALL get_software_interrupt_count(void);
uint32_t STDCALL get_software_interrupt_start(void);
uint32_t STDCALL get_software_interrupt_entry(uint32_t cpuid, uint32_t number, uint32_t instance, INTERRUPT_ENTRY *interrupt);

/* ============================================================================== */
/* System Call Entry Functions */
uint32_t STDCALL get_system_call_count(void);
SYSTEM_CALL_ENTRY STDCALL get_system_call_entry(uint32_t number);

/* ============================================================================== */
/* System Functions */
uint32_t STDCALL system_restart(uint32_t delay);
uint32_t STDCALL system_shutdown(uint32_t delay);

uint32_t STDCALL system_register_shutdown(shutdown_cb callback, void *parameter, uint32_t timeout);
uint32_t STDCALL system_deregister_shutdown(shutdown_cb callback, void *parameter);

int64_t STDCALL system_get_uptime(void);
uint32_t STDCALL system_get_command_line(char *commandline, uint32_t len);
void * STDCALL system_get_environment(void);

uint32_t STDCALL system_date_to_string(double_t date, char *value, uint32_t len);
uint32_t STDCALL system_time_to_string(double_t time, char *value, uint32_t len);
uint32_t STDCALL system_date_time_to_string(double_t datetime, char *value, uint32_t len);
uint32_t STDCALL system_interval_to_string(double_t interval, char *value, uint32_t len);

/* ============================================================================== */
/* CPU Functions */
uint32_t STDCALL cpu_get_arch(void);
uint32_t STDCALL cpu_get_type(void);
uint32_t STDCALL cpu_get_boot(void);
uint32_t STDCALL cpu_get_mask(void);
uint32_t STDCALL cpu_get_count(void);
uint32_t STDCALL cpu_get_mode(void);
uint32_t STDCALL cpu_get_state(void);
uint32_t STDCALL cpu_get_group(void);
uint32_t STDCALL cpu_get_current(void);
uint32_t STDCALL cpu_get_memory(size_t *address, uint64_t *length);
double_t STDCALL cpu_get_percentage(uint32_t cpuid);
uint32_t STDCALL cpu_get_utilization(uint32_t cpuid);

uint32_t STDCALL cpu_get_model(void);
uint32_t STDCALL cpu_get_revision(void);
uint32_t STDCALL cpu_get_description(char *description, uint32_t len);

/* ============================================================================== */
/* FPU Functions */
uint32_t STDCALL fpu_get_type(void);
uint32_t STDCALL fpu_get_state(void);

/* ============================================================================== */
/* GPU Functions */
uint32_t STDCALL gpu_get_type(void);
uint32_t STDCALL gpu_get_state(void);
uint32_t STDCALL gpu_get_memory(size_t *address, uint64_t *length);

/* ============================================================================== */
/* Cache Functions */
uint32_t STDCALL l1_cache_get_type(void);
uint32_t STDCALL l1_data_cache_get_size(void);
uint32_t STDCALL l1_data_cache_get_line_size(void);
uint32_t STDCALL l1_instruction_cache_get_size(void);
uint32_t STDCALL l1_instruction_cache_get_line_size(void);

uint32_t STDCALL l2_cache_get_type(void);
uint32_t STDCALL l2_cache_get_size(void);
uint32_t STDCALL l2_cache_get_line_size(void);

/* ============================================================================== */
/* Version Functions */
void STDCALL version_get_info(uint32_t *major, uint32_t *minor, uint32_t *revision);
uint32_t STDCALL version_get_date(char *date, uint32_t len);
uint32_t STDCALL version_get_name(char *name, uint32_t len);
uint32_t STDCALL version_get_version(char *version, uint32_t len);

/* ============================================================================== */
/* Board Functions */
uint32_t STDCALL board_get_type(void);
uint32_t STDCALL board_get_model(void);
int64_t STDCALL board_get_serial(void);
uint32_t STDCALL board_get_revision(void);
uint32_t STDCALL board_get_mac_address(char *address, uint32_t len);

/* ============================================================================== */
/* Chip Functions */
uint32_t STDCALL chip_get_revision(void);

/* ============================================================================== */
/* Firmware Functions */
uint32_t STDCALL firmware_get_revision(void);
uint32_t STDCALL firmware_get_throttled(void);

/* ============================================================================== */
/* Machine Functions */
uint32_t STDCALL machine_get_type(void);

/* ============================================================================== */
/* Memory Functions */
size_t STDCALL memory_get_base(void);
uint64_t STDCALL memory_get_size(void);

uint32_t STDCALL memory_get_page_size(void);
uint32_t STDCALL memory_get_large_page_size(void);

uint32_t STDCALL memory_get_section_size(void);
uint32_t STDCALL memory_get_large_section_size(void);

/* ============================================================================== */
/* Power Functions */
uint32_t STDCALL power_on(uint32_t powerid);
uint32_t STDCALL power_off(uint32_t powerid);

uint32_t STDCALL power_get_wait(uint32_t powerid);
uint32_t STDCALL power_get_state(uint32_t powerid);
uint32_t STDCALL power_set_state(uint32_t powerid, uint32_t state, BOOL wait);

/* ============================================================================== */
/* Clock Functions */
uint32_t STDCALL clock_ticks(void);
uint32_t STDCALL clock_seconds(void);

int64_t STDCALL clock_milliseconds(void);
int64_t STDCALL clock_microseconds(void);
int64_t STDCALL clock_nanoseconds(void);

int64_t STDCALL clock_get_time(void);
int64_t STDCALL clock_set_time(int64_t time, BOOL rtc);

uint32_t STDCALL clock_get_count(void);
int64_t STDCALL clock_get_total(void);

uint32_t STDCALL clock_update_offset(void);

uint32_t STDCALL clock_get_rate(uint32_t clockid);
uint32_t STDCALL clock_set_rate(uint32_t clockid, uint32_t rate, BOOL turbo);

uint32_t STDCALL clock_get_state(uint32_t clockid);
uint32_t STDCALL clock_set_state(uint32_t clockid, uint32_t state);

uint32_t STDCALL clock_get_min_rate(uint32_t clockid);
uint32_t STDCALL clock_get_max_rate(uint32_t clockid);

uint32_t STDCALL clock_get_measured_rate(uint32_t clockid);

/* ============================================================================== */
/* Turbo Functions */
uint32_t STDCALL turbo_get_state(uint32_t turboid);
uint32_t STDCALL turbo_set_state(uint32_t turboid, uint32_t state);

/* ============================================================================== */
/* Voltage Functions */
uint32_t STDCALL voltage_get_value(uint32_t voltageid);
uint32_t STDCALL voltage_set_value(uint32_t voltageid, uint32_t value);

uint32_t STDCALL voltage_get_min_value(uint32_t voltageid);
uint32_t STDCALL voltage_get_max_value(uint32_t voltageid);

/* ============================================================================== */
/* Temperature Functions */
uint32_t STDCALL temperature_get_current(uint32_t temperatureid);
uint32_t STDCALL temperature_get_maximum(uint32_t temperatureid);

/* ============================================================================== */
/* GPU Memory Functions */
HANDLE STDCALL gpu_memory_allocate(uint32_t length, uint32_t alignment, uint32_t flags);
uint32_t STDCALL gpu_memory_release(HANDLE handle);
uint32_t STDCALL gpu_memory_lock(HANDLE handle);
uint32_t STDCALL gpu_memory_unlock(HANDLE handle);

/* ============================================================================== */
/* GPU Misc Functions */
uint32_t STDCALL gpu_execute_code(void *address, uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3, uint32_t r4, uint32_t r5);

HANDLE STDCALL dispmanx_handle_get(HANDLE resource);
uint32_t STDCALL edid_block_get(uint32_t block, void *buffer, uint32_t length);

/* ============================================================================== */
/* Framebuffer Functions */
BOOL STDCALL framebuffer_available(void);

uint32_t STDCALL framebuffer_allocate(uint32_t alignment, uint32_t *address, uint32_t *length);
uint32_t STDCALL framebuffer_release(void);
uint32_t STDCALL framebuffer_set_state(uint32_t state);

uint32_t STDCALL framebuffer_get_dimensions(uint32_t *width, uint32_t *height, uint32_t *top, uint32_t *bottom, uint32_t *left, uint32_t *right);

uint32_t STDCALL framebuffer_get_physical(uint32_t *width, uint32_t *height);
uint32_t STDCALL framebuffer_set_physical(uint32_t *width, uint32_t *height);
uint32_t STDCALL framebuffer_test_physical(uint32_t *width, uint32_t *height);

uint32_t STDCALL framebuffer_get_virtual(uint32_t *width, uint32_t *height);
uint32_t STDCALL framebuffer_set_virtual(uint32_t *width, uint32_t *height);
uint32_t STDCALL framebuffer_test_virtual(uint32_t *width, uint32_t *height);

uint32_t STDCALL framebuffer_get_depth(uint32_t *depth);
uint32_t STDCALL framebuffer_set_depth(uint32_t *depth);
uint32_t STDCALL framebuffer_test_depth(uint32_t *depth);

uint32_t STDCALL framebuffer_get_pixel_order(uint32_t *order);
uint32_t STDCALL framebuffer_set_pixel_order(uint32_t *order);
uint32_t STDCALL framebuffer_test_pixel_order(uint32_t *order);

uint32_t STDCALL framebuffer_get_alpha_mode(uint32_t *mode);
uint32_t STDCALL framebuffer_set_alpha_mode(uint32_t *mode);
uint32_t STDCALL framebuffer_test_alpha_mode(uint32_t *mode);

uint32_t STDCALL framebuffer_get_pitch(void);

uint32_t STDCALL framebuffer_get_offset(uint32_t *x, uint32_t *y);
uint32_t STDCALL framebuffer_set_offset(uint32_t *x, uint32_t *y);
uint32_t STDCALL framebuffer_test_offset(uint32_t *x, uint32_t *y);

uint32_t STDCALL framebuffer_get_overscan(uint32_t *top, uint32_t *bottom, uint32_t *left, uint32_t *right);
uint32_t STDCALL framebuffer_set_overscan(uint32_t *top, uint32_t *bottom, uint32_t *left, uint32_t *right);
uint32_t STDCALL framebuffer_test_overscan(uint32_t *top, uint32_t *bottom, uint32_t *left, uint32_t *right);

uint32_t STDCALL framebuffer_get_palette(void *buffer, uint32_t length);
uint32_t STDCALL framebuffer_set_palette(uint32_t start, uint32_t count, void *buffer, uint32_t length);
uint32_t STDCALL framebuffer_test_palette(uint32_t start, uint32_t count, void *buffer, uint32_t length);

uint32_t STDCALL framebuffer_get_layer(int32_t *layer);
uint32_t STDCALL framebuffer_set_layer(int32_t *layer);
uint32_t STDCALL framebuffer_test_layer(int32_t *layer);

uint32_t STDCALL framebuffer_test_vsync(void);
uint32_t STDCALL framebuffer_set_vsync(void);

uint32_t STDCALL framebuffer_set_backlight(uint32_t brightness);

uint32_t STDCALL framebuffer_get_num_displays(uint32_t *numdisplays);
uint32_t STDCALL framebuffer_get_display_id(uint32_t displaynum);
uint32_t STDCALL framebuffer_set_display_num(uint32_t displaynum);
uint32_t STDCALL framebuffer_get_display_settings(uint32_t displaynum, DISPLAY_SETTINGS *displaysettings);
uint32_t STDCALL framebuffer_display_id_to_name(uint32_t displayid, char *name, uint32_t len);

/* ============================================================================== */
/* Touch Functions */
uint32_t STDCALL touch_get_buffer(size_t *address);
uint32_t STDCALL touch_set_buffer(size_t address);

/* ============================================================================== */
/* Cursor Functions */
uint32_t STDCALL cursor_set_default(void);
uint32_t STDCALL cursor_set_info(uint32_t width, uint32_t height, uint32_t hotspotx, uint32_t hotspoty, void *pixels, uint32_t length);
uint32_t STDCALL cursor_set_state(BOOL enabled, uint32_t x, uint32_t y, BOOL relative);

/* ============================================================================== */
/* DMA Functions */
BOOL STDCALL dma_available(void);

uint32_t STDCALL dma_transfer(DMA_DATA *data, uint32_t direction, uint32_t peripheral);

uint32_t STDCALL dma_fill_memory(void *dest, uint32_t size, uint8_t value);
uint32_t STDCALL dma_copy_memory(void *source, void *dest, uint32_t size);

uint32_t STDCALL dma_read_peripheral(void *address, void *dest, uint32_t size, uint32_t peripheral);
uint32_t STDCALL dma_write_peripheral(void *source, void *address, uint32_t size, uint32_t peripheral);

void * STDCALL dma_allocate_buffer(uint32_t size);
void * STDCALL dma_allocate_buffer_ex(uint32_t *size);
uint32_t STDCALL dma_release_buffer(void *buffer);

uint32_t STDCALL dma_get_channels(void);

/* ============================================================================== */
/* Handle Functions */
HANDLE STDCALL handle_create(HANDLE data, uint32_t _type);
HANDLE_ENTRY * STDCALL handle_create_ex(const char *name, uint32_t flags, HANDLE data, uint32_t _type);
uint32_t STDCALL handle_destroy(HANDLE handle);

HANDLE_ENTRY * STDCALL handle_get(HANDLE handle);
HANDLE_ENTRY * STDCALL handle_find(const char *name);
uint32_t STDCALL handle_enumerate(handle_enumerate_cb callback, void *data);

HANDLE STDCALL handle_open(const char *name);
uint32_t STDCALL handle_close(HANDLE handle);
HANDLE STDCALL handle_duplicate(HANDLE handle);

/* ============================================================================== */
/* GPIO Functions */
BOOL STDCALL gpio_available(void);

uint32_t STDCALL gpio_read(uint32_t reg);
void STDCALL gpio_write(uint32_t reg, uint32_t value);

uint32_t STDCALL gpio_input_get(uint32_t pin);
uint32_t STDCALL gpio_input_wait(uint32_t pin, uint32_t trigger, uint32_t timeout);
uint32_t STDCALL gpio_input_event(uint32_t pin, uint32_t trigger, uint32_t timeout, gpio_event_cb callback, void *data);

uint32_t STDCALL gpio_output_set(uint32_t pin, uint32_t level);

uint32_t STDCALL gpio_level_get(uint32_t pin);
uint32_t STDCALL gpio_level_set(uint32_t pin, uint32_t level);

uint32_t STDCALL gpio_pull_get(uint32_t pin);
uint32_t STDCALL gpio_pull_select(uint32_t pin, uint32_t mode);

uint32_t STDCALL gpio_function_get(uint32_t pin);
uint32_t STDCALL gpio_function_select(uint32_t pin, uint32_t mode);

/* ============================================================================== */
/* Virtual GPIO Functions */
uint32_t STDCALL virtual_gpio_input_get(uint32_t pin);
uint32_t STDCALL virtual_gpio_output_set(uint32_t pin, uint32_t level);

uint32_t STDCALL virtual_gpio_level_get(uint32_t pin);
uint32_t STDCALL virtual_gpio_level_set(uint32_t pin, uint32_t level);

uint32_t STDCALL virtual_gpio_function_get(uint32_t pin);
uint32_t STDCALL virtual_gpio_function_select(uint32_t pin, uint32_t mode);

/* ============================================================================== */
/* SPI Functions */
BOOL STDCALL spi_available(void);

uint32_t STDCALL spi_start(uint32_t mode, uint32_t clockrate, uint32_t clockphase, uint32_t clockpolarity);
uint32_t STDCALL spi_stop(void);

uint32_t STDCALL spi_read(uint16_t chipselect, void *dest, uint32_t size, uint32_t *count);
uint32_t STDCALL spi_write(uint16_t chipselect, void *source, uint32_t size, uint32_t *count);
uint32_t STDCALL spi_write_read(uint16_t chipselect, void *source, void *dest, uint32_t size, uint32_t *count);

uint32_t STDCALL spi_get_mode(void);
uint32_t STDCALL spi_set_mode(uint32_t mode);

uint32_t STDCALL spi_get_clock_rate(uint16_t chipselect);
uint32_t STDCALL spi_set_clock_rate(uint16_t chipselect, uint32_t clockrate);

uint32_t STDCALL spi_get_clock_phase(void);
uint32_t STDCALL spi_set_clock_phase(uint32_t clockphase);

uint32_t STDCALL spi_get_clock_polarity(void);
uint32_t STDCALL spi_set_clock_polarity(uint32_t clockpolarity);

uint32_t STDCALL spi_get_select_polarity(uint16_t chipselect);
uint32_t STDCALL spi_set_select_polarity(uint16_t chipselect, uint32_t selectpolarity);

uint32_t STDCALL spi_get_description(uint32_t id, char *description, uint32_t len);

/* ============================================================================== */
/* I2C Functions */
BOOL STDCALL i2c_available(void);

uint32_t STDCALL i2c_start(uint32_t rate);
uint32_t STDCALL i2c_stop(void);

uint32_t STDCALL i2c_read(uint16_t address, void *buffer, uint32_t size, uint32_t *count);
uint32_t STDCALL i2c_write(uint16_t address, void *buffer, uint32_t size, uint32_t *count);
uint32_t STDCALL i2c_write_read(uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t *count);
uint32_t STDCALL i2c_write_write(uint16_t address, void *initial, uint32_t len, void *data, uint32_t size, uint32_t *count);

uint32_t STDCALL i2c_get_rate(void);
uint32_t STDCALL i2c_set_rate(uint32_t rate);

uint16_t STDCALL i2c_get_address(void);
uint32_t STDCALL i2c_set_address(uint16_t address);

uint32_t STDCALL i2c_get_description(uint32_t id, char *description, uint32_t len);
uint32_t STDCALL i2c_slave_get_description(uint32_t id, char *description, uint32_t len);

/* ============================================================================== */
/* PWM Functions */
BOOL STDCALL pwm_available(void);

uint32_t STDCALL pwm_start(void);
uint32_t STDCALL pwm_stop(void);

uint32_t STDCALL pwm_write(uint32_t value);

uint32_t STDCALL pwm_set_mode(uint32_t mode);
uint32_t STDCALL pwm_set_range(uint32_t range);
uint32_t STDCALL pwm_set_frequency(uint32_t frequency);

uint32_t STDCALL pwm_configure(uint32_t dutyns, uint32_t periodns);

uint32_t STDCALL pwm_get_description(uint32_t id, uint32_t channel, char *description, uint32_t len);

/* ============================================================================== */
/* RTC Functions */
BOOL STDCALL rtc_available(void);

int64_t STDCALL rtc_get_time(void);
int64_t STDCALL rtc_set_time(int64_t time);

/* ============================================================================== */
/* UART Functions */
uint32_t STDCALL uart_get_description(uint32_t id, char *description, uint32_t len);

/* ============================================================================== */
/* Serial Functions */
BOOL STDCALL serial_available(void);

uint32_t STDCALL serial_open(uint32_t baudrate, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t flowcontrol, uint32_t receivedepth, uint32_t transmitdepth);
uint32_t STDCALL serial_close(void);

uint32_t STDCALL serial_read(void *buffer, uint32_t size, uint32_t *count);
uint32_t STDCALL serial_write(void *buffer, uint32_t size, uint32_t *count);

int STDCALL serial_printf(const char *format, ...) _ATTRIBUTE ((__format__ (__printf__, 1, 2)));

/* ============================================================================== */
/* Peripheral Functions */
size_t STDCALL peripheral_get_base(void);
uint32_t STDCALL peripheral_get_size(void);

uint32_t STDCALL peripheral_read(uint32_t base, uint32_t reg);
void STDCALL peripheral_write(uint32_t base, uint32_t reg, uint32_t value);

size_t STDCALL local_peripheral_get_base(void);
uint32_t STDCALL local_peripheral_get_size(void);

/* ============================================================================== */
/* System Functions */
size_t STDCALL get_sp(void);
size_t STDCALL get_pc(void);

BOOL STDCALL get_irq(void);
void STDCALL enable_irq(void);
void STDCALL disable_irq(void);
IRQ_MASK STDCALL save_irq(void);
IRQ_MASK STDCALL restore_irq(IRQ_MASK irqmask);

BOOL STDCALL get_fiq(void);
void STDCALL enable_fiq(void);
void STDCALL disable_fiq(void);
FIQ_MASK STDCALL save_fiq(void);
FIQ_MASK STDCALL restore_fiq(FIQ_MASK fiqmask);

void STDCALL enable_irq_fiq(void);
void STDCALL disable_irq_fiq(void);
IRQ_FIQ_MASK STDCALL save_irq_fiq(void);
IRQ_FIQ_MASK STDCALL restore_irq_fiq(IRQ_FIQ_MASK irqfiqmask);

BOOL STDCALL get_abort(void);
void STDCALL enable_abort(void);
void STDCALL disable_abort(void);
ABORT_MASK STDCALL save_abort(void);
ABORT_MASK STDCALL restore_abort(ABORT_MASK abortmask);

void STDCALL halt_cpu(void);
void STDCALL pause_cpu(void);

uint32_t STDCALL halt_thread(uint32_t exitcode);

void STDCALL send_event(void);
void STDCALL wait_for_event(void);
void STDCALL wait_for_interrupt(void);

void STDCALL read_memory_barrier(void);
void STDCALL write_memory_barrier(void);

void STDCALL data_memory_barrier(void);
void STDCALL data_synchronization_barrier(void);
void STDCALL instruction_memory_barrier(void);

void STDCALL invalidate_tlb(void);
void STDCALL invalidate_data_tlb(void);
void STDCALL invalidate_instruction_tlb(void);

void STDCALL invalidate_cache(void);
void STDCALL clean_data_cache(void);
void STDCALL invalidate_data_cache(void);
void STDCALL clean_and_invalidate_data_cache(void);
void STDCALL invalidate_instruction_cache(void);

void STDCALL clean_data_cache_range(size_t address, uint32_t size);
void STDCALL invalidate_data_cache_range(size_t address, uint32_t size);
void STDCALL clean_and_invalidate_data_cache_range(size_t address, uint32_t size);
void STDCALL invalidate_instruction_cache_range(size_t address, uint32_t size);

void STDCALL flush_prefetch_buffer(void);

void STDCALL flush_branch_target_cache(void);

void STDCALL context_switch(void *oldstack, void *newstack, THREAD_HANDLE newthread);
void STDCALL context_switch_irq(void *oldstack, void *newstack, THREAD_HANDLE newthread);
void STDCALL context_switch_fiq(void *oldstack, void *newstack, THREAD_HANDLE newthread);
void STDCALL context_switch_swi(void *oldstack, void *newstack, THREAD_HANDLE newthread);

int32_t STDCALL interlocked_or(int32_t *target, int32_t value);
int32_t STDCALL interlocked_xor(int32_t *target, int32_t value);
int32_t STDCALL interlocked_and(int32_t *target, int32_t value);

int32_t STDCALL interlocked_decrement(int32_t *target);
int32_t STDCALL interlocked_increment(int32_t *target);
int32_t STDCALL interlocked_exchange(int32_t *target, int32_t source);
int32_t STDCALL interlocked_add_exchange(int32_t *target, int32_t source);
int32_t STDCALL interlocked_compare_exchange(int32_t *target, int32_t source, int32_t compare);

uint32_t STDCALL page_table_get_levels(void);

size_t STDCALL page_directory_get_base(void);
uint32_t STDCALL page_directory_get_size(void);

size_t STDCALL page_table_get_base(void);
uint32_t STDCALL page_table_get_size(void);

void STDCALL page_table_get_entry(size_t address, PAGE_TABLE_ENTRY *entry);
uint32_t STDCALL page_table_set_entry(PAGE_TABLE_ENTRY *entry);

uint32_t STDCALL page_table_get_page_size(size_t address);
uint32_t STDCALL page_table_get_page_flags(size_t address);
#if defined (__i386__) || defined (__arm__)
uint32_t STDCALL page_table_get_page_range(size_t address);
#endif
size_t STDCALL page_table_get_page_physical(size_t address);

size_t STDCALL page_tables_get_address(void);
uint32_t STDCALL page_tables_get_length(void);
uint32_t STDCALL page_tables_get_count(void);
uint32_t STDCALL page_tables_get_shift(void);

size_t STDCALL page_tables_get_next(void);
uint32_t STDCALL page_tables_get_used(void);
uint32_t STDCALL page_tables_get_free(void);

size_t STDCALL vector_table_get_base(void);
uint32_t STDCALL vector_table_get_size(void);
uint32_t STDCALL vector_table_get_count(void);
size_t STDCALL vector_table_get_entry(uint32_t number);
uint32_t STDCALL vector_table_set_entry(uint32_t number, size_t address);

/* ============================================================================== */
/* Console Functions */
BOOL STDCALL console_get_key(char *ch, void *userdata);
BOOL STDCALL console_peek_key(char *ch, void *userdata);

BOOL STDCALL console_write_char(char ch, void *userdata);
BOOL STDCALL console_read_char(char *ch, void *userdata);
BOOL STDCALL console_read_wide_char(WCHAR *ch, void *userdata);

BOOL STDCALL console_hide_mouse(void *userdata);
BOOL STDCALL console_show_mouse(uint32_t x, uint32_t y, void *userdata);
BOOL STDCALL console_read_mouse(uint32_t *x, uint32_t *y, uint32_t *buttons, void *userdata);

/* ============================================================================== */
/* CodePage Functions */
WCHAR STDCALL code_page_to_wide_char(char ch);
char STDCALL wide_char_to_code_page(WCHAR ch);

/* ============================================================================== */
/* Name Functions */
uint32_t STDCALL host_get_name(char *name, uint32_t len);
BOOL STDCALL host_set_name(const char *name);
uint32_t STDCALL host_get_domain(char *domain, uint32_t len);
BOOL STDCALL host_set_domain(const char *domain);

/* ============================================================================== */
/* Module Functions */
HANDLE STDCALL module_load(const char *name);
HANDLE STDCALL module_load_ex(const char *name, uint32_t flags);
BOOL STDCALL module_unload(HANDLE handle);
uint32_t STDCALL module_get_name(HANDLE handle, char *name, uint32_t len);

/* ============================================================================== */
/* Symbol Functions */
BOOL STDCALL symbol_add(HANDLE handle, const char *name, size_t address);
BOOL STDCALL symbol_remove(HANDLE handle, const char *name);
size_t STDCALL symbol_get_address(HANDLE handle, const char *name);

/* ============================================================================== */
/* Logging Functions */
void STDCALL logging_output(const char *text);
void STDCALL logging_output_ex(uint32_t facility, uint32_t severity, const char *tag, const char *content);

int STDCALL logging_outputf(const char *format, ...) _ATTRIBUTE ((__format__ (__printf__, 1, 2)));

/* ============================================================================== */
/* Environment Functions */
uint32_t STDCALL environment_get(const char *name, char *value, uint32_t len);
uint32_t STDCALL environment_set(const char *name, const char *value);
uint32_t STDCALL environment_count(BOOL reset);
uint32_t STDCALL environment_index(const char *name);
uint32_t STDCALL environment_string(uint32_t index, char *string, uint32_t len);

/* ============================================================================== */
/* Environment Functions (From stdlib.h) */
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);

/* ============================================================================== */
/* Utility Functions */
uint32_t STDCALL first_bit_set(uint32_t value);
uint32_t STDCALL last_bit_set(uint32_t value);
uint32_t STDCALL count_leading_zeros(uint32_t value);
uint32_t STDCALL count_trailing_zeros(uint32_t value);

size_t STDCALL physical_to_io_address(void *address);
size_t STDCALL io_address_to_physical(void *address);

size_t STDCALL physical_to_bus_address(void *address);
size_t STDCALL bus_address_to_physical(void *address);

void STDCALL nanosecond_delay(uint32_t nanoseconds);
void STDCALL microsecond_delay(uint32_t microseconds);
void STDCALL millisecond_delay(uint32_t milliseconds);

void STDCALL nanosecond_delay_ex(uint32_t nanoseconds, BOOL wait);
void STDCALL microsecond_delay_ex(uint32_t microseconds, BOOL wait);
void STDCALL millisecond_delay_ex(uint32_t milliseconds, BOOL wait);

/* ============================================================================== */
/* RTL Functions */
uint32_t get_tick_count(void);
uint64_t get_tick_count64(void);

/* ============================================================================== */
/* LIBC Functions (From stdlib.h) */
int posix_memalign(void **memptr, size_t alignment, size_t size);
char *realpath(const char *__restrict path, char *__restrict resolved_path);
int getpagesize(void);

/* ============================================================================== */
/* LIBC Functions (From unistd.h) */
int dup3(int oldfd, int newfd, int flags);
int getentropy(void *buffer, size_t length);
int usleep(useconds_t useconds);
int symlink(const char *path1, const char *path2);

int ftruncate(int fd, off_t length);
int truncate(const char *path, off_t length);

int fdatasync(int fd);

/* ============================================================================== */
/* LIBC Functions (From sys/mman.h) */
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);

/* ============================================================================== */
/* LIBC Functions (From sys/time.h) */
int settimeofday(const struct timeval *tv, const struct timezone *tz);

/* ============================================================================== */
/* LIBC Functions (From sched.h) */
int sched_getcpu(void);
#ifdef _SYS_CPUSET_H_
int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
int sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
#endif /* _SYS_CPUSET_H_ */

/* ============================================================================== */
/* LIBC Functions (Non Standard) */
void msleep(unsigned int msecs);
pid_t gettid(void);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_PLATFORM_H