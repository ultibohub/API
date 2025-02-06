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
#ifndef _ULTIBO_THREADS_H
#define _ULTIBO_THREADS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/system.h"
#include "ultibo/platform.h"
#include "ultibo/locale.h"

/* ============================================================================== */
/* Thread specific constants */

/* Lock constants */
#define LOCK_FLAG_NONE	0x00000000
#define LOCK_FLAG_IRQ	0x00000001
#define LOCK_FLAG_FIQ	0x00000002
#define LOCK_FLAG_IRQFIQ	0x00000004

/* Spin constants */
#define SPIN_SIGNATURE	0x0FEC3B82

/* Spin state constants */
#define SPIN_STATE_UNLOCKED	0
#define SPIN_STATE_LOCKED	1

/* Mutex constants */
#define MUTEX_SIGNATURE	0x1C5D7FA4

/* Mutex state constants */
#define MUTEX_STATE_UNLOCKED	0
#define MUTEX_STATE_LOCKED	1

/* Mutex flags constants */
#define MUTEX_FLAG_NONE	0x00000000
#define MUTEX_FLAG_RECURSIVE	0x00000001 // Mutex can be locked multiple times by the same thread if set (Must be unlocked the same number of times)
#define MUTEX_FLAG_ERRORCHECK	0x00000002 // Mutex will perform a deadlock check if set, will return with an error if already owned by the same thread (and not recursive)

/* Critical Section constants */
#define CRITICAL_SECTION_SIGNATURE	0x25F3AE01

/* Critical Section state constants */
#define CRITICAL_SECTION_STATE_UNLOCKED	0
#define CRITICAL_SECTION_STATE_LOCKED	1

/* Semaphore constants */
#define SEMAPHORE_SIGNATURE	0x390A1EB4

/* Semaphore flag constants */
#define SEMAPHORE_FLAG_NONE	LOCK_FLAG_NONE
#define SEMAPHORE_FLAG_IRQ	LOCK_FLAG_IRQ
#define SEMAPHORE_FLAG_FIQ	LOCK_FLAG_FIQ
#define SEMAPHORE_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ

/* Synchronizer constants */
#define SYNCHRONIZER_SIGNATURE	0xC5D081FB

/* Synchronizer state constants */
#define SYNCHRONIZER_STATE_UNLOCKED	0
#define SYNCHRONIZER_STATE_READER_LOCKED	1
#define SYNCHRONIZER_STATE_WRITER_LOCKED	2

/* Synchronizer flag constants */
#define SYNCHRONIZER_FLAG_NONE	0x00000000
#define SYNCHRONIZER_FLAG_READ_PRIORITY	0x00000001 // Synchronizer prioritises readers over writers
#define SYNCHRONIZER_FLAG_WRITE_PRIORITY	0x00000002 // Synchronizer prioritises writers over readers

/* Condition constants */
#define CONDITION_SIGNATURE	0xD14D3C0A

/* Condition flag constants */
#define CONDITION_FLAG_NONE	0x00000000

/* Condition lock flag constants */
#define CONDITION_LOCK_FLAG_NONE	0x00000000
#define CONDITION_LOCK_FLAG_WRITER	0x00000001 // Condition should release and acquire the writer lock on a Synchronizer when ConditionWaitSynchronizer is called (otherwise release and acquire the reader lock)

/* Completion constants */
#define COMPLETION_SIGNATURE	0xFCE24CA1

/* Completion state constants */
#define COMPLETION_STATE_RESET	0
#define COMPLETION_STATE_COMPLETE	1

/* Completion flag constants */
#define COMPLETION_FLAG_NONE	LOCK_FLAG_NONE
#define COMPLETION_FLAG_IRQ	LOCK_FLAG_IRQ // Disable IRQ during completion operations (Wait/Reset/Complete)
#define COMPLETION_FLAG_FIQ	LOCK_FLAG_FIQ // Disable FIQ during completion operations (Wait/Reset/Complete)
#define COMPLETION_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ // Disable IRQ and FIQ during completion operations (Wait/Reset/Complete)
#define COMPLETION_FLAG_COUNTED	0x00000008 // Use a counted value instead of a single state (Affects behaviour of Wait and Complete)

/* List constants */
#define LIST_SIGNATURE	0x4A98BE2A

/* List type constants */
#define LIST_TYPE_NOT_SPECIFIED	0 // A generic thread list without a specific purpose
#define LIST_TYPE_WAIT_SECTION	1 // A Critical Section Wait List
#define LIST_TYPE_WAIT_SEMAPHORE	2 // A Semaphore Wait List
#define LIST_TYPE_WAIT_SYNCHRONIZER	3 // A Synchronizer Wait List
#define LIST_TYPE_WAIT_CONDITION	4 // A Condition Wait List
#define LIST_TYPE_WAIT_COMPLETION	5 // A Condition Wait List
#define LIST_TYPE_WAIT_EVENT	6 // An Event Wait List
#define LIST_TYPE_WAIT_THREAD	7 // A Thread Wait List
#define LIST_TYPE_WAIT_MESSAGESLOT	8 // A Messageslot Wait List
#define LIST_TYPE_WAIT_OTHER	9 // Another type of Wait List (Suitable for passing to ThreadWait/ThreadWaitEx/ThreadWaitMultiple/ThreadRelease)

/* List flag constants */
#define LIST_FLAG_NONE	LOCK_FLAG_NONE
#define LIST_FLAG_IRQ	LOCK_FLAG_IRQ
#define LIST_FLAG_FIQ	LOCK_FLAG_FIQ
#define LIST_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ

/* Queue constants */
#define QUEUE_SIGNATURE	0x57A3BF9E

/* Queue type constants */
#define QUEUE_TYPE_NOT_SPECIFIED	0 // A generic thread queue without a specific purpose
#define QUEUE_TYPE_SCHEDULE_SLEEP	1 // A Scheduler Sleep Queue
#define QUEUE_TYPE_SCHEDULE_TIMEOUT	2 // A Scheduler Timeout Queue
#define QUEUE_TYPE_SCHEDULE_TERMINATION	3 // A Scheduler Termination Queue (Threads are placed on termination queue when they exit or are terminated)
#define QUEUE_TYPE_SCHEDULE_NONE	4 // A Scheduler No Priority Queue (Only used for IRQ/FIQ threads which are never selected for scheduling)
#define QUEUE_TYPE_SCHEDULE_IDLE	5 // A Scheduler Idle Priority Queue
#define QUEUE_TYPE_SCHEDULE_LOWEST	6 // A Scheduler Lowest Priority Queue
#define QUEUE_TYPE_SCHEDULE_LOWER	7 // A Scheduler Lower Priority Queue
#define QUEUE_TYPE_SCHEDULE_NORMAL	8 // A Scheduler Normal Priority Queue
#define QUEUE_TYPE_SCHEDULE_HIGHER	9 // A Scheduler Higher Priority Queue
#define QUEUE_TYPE_SCHEDULE_HIGHEST	10 // A Scheduler Highest Priority Queue
#define QUEUE_TYPE_SCHEDULE_CRITICAL	11 // A Scheduler Critical Priority Queue

/* Queue flag constants */
#define QUEUE_FLAG_NONE	LOCK_FLAG_NONE
#define QUEUE_FLAG_IRQ	LOCK_FLAG_IRQ
#define QUEUE_FLAG_FIQ	LOCK_FLAG_FIQ
#define QUEUE_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ
#define QUEUE_FLAG_DESCENDING	0x00000008
#define QUEUE_FLAG_DELTA	0x00000010

/* Queue key constants */
#define QUEUE_KEY_NONE	(int32_t)0x7FFFFFFF // Null key value returned from an empty Queue
#define QUEUE_KEY_MAX	(int32_t)0x7FFFFFFE // Max key that can be ordered in a Queue
#define QUEUE_KEY_MIN	(int32_t)0x80000000 // Min key that can be ordered in a Queue

/* Thread constants */
#define THREAD_SIGNATURE	0x6C2BA10F

/* Thread type constants */
#define THREAD_TYPE_NORMAL	0 // A Normal thread (No special case handling)
#define THREAD_TYPE_IDLE	1 // An Idle thread (Used to calculate ultilization and provide an always ready thread)
#define THREAD_TYPE_IRQ	2 // An IRQ thread (Used by the IRQ handler during interrupt time)
#define THREAD_TYPE_FIQ	3 // An FIQ thread (Used by the FIQ handler during interrupt time)
#define THREAD_TYPE_SWI	4 // A Software Interrupt (SWI) thread (Used by the SWI handler during a system call)

/* Thread flag constants */
#define THREAD_FLAG_NONE	0x00000000
#define THREAD_FLAG_PERSIST	0x00000001 // If set thread handle will persist until explicitly destroyed (Otherwise destroyed after termination quantum has elapsed)
#define THREAD_FLAG_CANCELLED	0x00000002 // Indicates that thread has been cancelled, for support of external thread APIs (eg pThreads)(Not used internally by Ultibo)
#define THREAD_FLAG_CANCEL_DISABLE	0x00000004 // Indicates that thread cancellation is disabled for a thread, for support of external thread APIs (eg pThreads)(Not used internally by Ultibo)
#define THREAD_FLAG_CANCEL_ASYNCHRONOUS	0x00000008 // Indicates that asynchronous thread cancellation is enabled for a thread, for support of external thread APIs (eg pThreads)(Not used internally by Ultibo)

#define THREAD_FLAG_INTERNAL	THREAD_FLAG_NONE + $80000000 // Note: Temporary value to avoid warning

/* Thread state constants */
#define THREAD_STATE_RUNNING	1 // Thread is currently running
#define THREAD_STATE_READY	2 // Thread is on ready queue
#define THREAD_STATE_SLEEP	3 // Thread is sleeping
#define THREAD_STATE_SUSPENDED	4 // Thread is suspended
#define THREAD_STATE_WAIT	5 // Thread is on a wait list
#define THREAD_STATE_WAIT_TIMEOUT	6 // Thread is on a wait list with timeout
#define THREAD_STATE_RECEIVE	7 // Thread is waiting to receive a message
#define THREAD_STATE_RECEIVE_TIMEOUT	8 // Thread is waiting to receive a message with timeout
#define THREAD_STATE_HALTED	9 // Thread has been halted (Due to an unhandled exception etc)
#define THREAD_STATE_TERMINATED	10 // Thread has been terminated
// To Do THREAD_STATE_SEND / THREAD_STATE_SEND_TIMEOUT ?  //Who would wake them up ? //Timeout is ok, but what about send only ?

/* Thread priority constants */
#define THREAD_PRIORITY_NONE	0 // Only used for IRQ/FIQ threads which are never selected for scheduling
#define THREAD_PRIORITY_IDLE	1
#define THREAD_PRIORITY_LOWEST	2
#define THREAD_PRIORITY_LOWER	3
#define THREAD_PRIORITY_NORMAL	4
#define THREAD_PRIORITY_HIGHER	5
#define THREAD_PRIORITY_HIGHEST	6
#define THREAD_PRIORITY_CRITICAL	7

#define THREAD_PRIORITY_DEFAULT	THREAD_PRIORITY_NORMAL // Default thread priority
#define THREAD_PRIORITY_MINIMUM	THREAD_PRIORITY_IDLE // Minimum thread priority
#define THREAD_PRIORITY_MAXIMUM	THREAD_PRIORITY_CRITICAL // Maximum thread priority
#define THREAD_PRIORITY_COUNT	THREAD_PRIORITY_MAXIMUM + 1 // Number of thread priority levels

/* Additional priority aliases for compatibility */
#define THREAD_PRIORITY_BELOW_NORMAL	THREAD_PRIORITY_LOWER
#define THREAD_PRIORITY_ABOVE_NORMAL	THREAD_PRIORITY_HIGHER
#define THREAD_PRIORITY_TIME_CRITICAL	THREAD_PRIORITY_CRITICAL

/* Thread name constants */
#define THREAD_NAME_LENGTH	SIZE_64 // Length of thread name

#define IRQ_THREAD_NAME	"IRQ"
#define FIQ_THREAD_NAME	"FIQ"
#define SWI_THREAD_NAME	"SWI"
#define IDLE_THREAD_NAME	"Idle"
#define MAIN_THREAD_NAME	"Main"
#define TIMER_THREAD_NAME	"Timer"
#define WORKER_THREAD_NAME	"Worker"
#define TIMER_PRIORITY_THREAD_NAME	"Priority Timer"
#define WORKER_PRIORITY_THREAD_NAME	"Priority Worker"
#define RTL_THREAD_NAME	"RTL Thread"

/* Thread priority constants */
#define TIMER_THREAD_PRIORITY	THREAD_PRIORITY_NORMAL
#define WORKER_THREAD_PRIORITY	THREAD_PRIORITY_NORMAL
#define TIMER_PRIORITY_THREAD_PRIORITY	THREAD_PRIORITY_HIGHEST
#define WORKER_PRIORITY_THREAD_PRIORITY	THREAD_PRIORITY_HIGHER

/* Thread create constants */
#define THREAD_CREATE_NONE	0x00000000
#define THREAD_CREATE_SUSPENDED	0x00000004

/* Thread TLS constants */
#define THREAD_TLS_FREE	0x00000000
#define THREAD_TLS_USED	0x00000001
#define THREAD_TLS_INVALID	0xFFFFFFFF

#define THREAD_TLS_MAXIMUM	SIZE_64 // The maximum number TLS index slots available

/* Thread TLS flag constants */
#define THREAD_TLS_FLAG_NONE	0x00000000
#define THREAD_TLS_FLAG_FREE	0x00000001 // If set then pointer in thread TLS index will be freed on ThreadReleaseTlsIndex or ThreadDestroy

/* Thread wait constants */
#define THREAD_LISTS_MAXIMUM	SIZE_64 // Maximum number of lists a thread can wait on at the same time

/* Messageslot constants */
#define MESSAGESLOT_SIGNATURE	0xB631CE4B

/* Messageslot flag constants */
#define MESSAGESLOT_FLAG_NONE	LOCK_FLAG_NONE
#define MESSAGESLOT_FLAG_IRQ	LOCK_FLAG_IRQ
#define MESSAGESLOT_FLAG_FIQ	LOCK_FLAG_FIQ
#define MESSAGESLOT_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ

/* Mailslot constants */
#define MAILSLOT_SIGNATURE	0x7A409BF3

/* Buffer constants */
#define BUFFER_SIGNATURE	0x830BEA71

/* Buffer flag constants */
#define BUFFER_FLAG_NONE	0x00000000
#define BUFFER_FLAG_SHARED	0x00000001 // If set the buffer memory (Not the buffer entry itself) is allocated from shared memory

/* Event constants */
#define EVENT_SIGNATURE	0x903BA69D

/* Event state constants */
#define EVENT_STATE_UNSIGNALED	0
#define EVENT_STATE_SIGNALED	1

/* Event flag constants */
#define EVENT_FLAG_NONE	0x00000000
#define EVENT_FLAG_INITIAL_STATE	0x00000001
#define EVENT_FLAG_MANUAL_RESET	0x00000002

/* Timer constants */
#define TIMER_SIGNATURE	0xAB7E07FB

/* Timer state constants */
#define TIMER_STATE_DISABLED	0
#define TIMER_STATE_ENABLED	1

/* Timer flag constants */
#define TIMER_FLAG_NONE	0x00000000
#define TIMER_FLAG_RESCHEDULE	0x00000001 // Timer should be rescheduled each time the event completes
#define TIMER_FLAG_IMMEDIATE	0x00000002 // Timer event should be executed immediately and then each interval milliseconds
#define TIMER_FLAG_WORKER	0x00000004 // Timer event should be executed by a worker thread instead of a timer thread
#define TIMER_FLAG_PRIORITY	0x00000008 // Timer event should be executed by a priority timer thread

/* Timer key constants */
#define TIMER_KEY_NONE	(int32_t)0x7FFFFFFF // Null key value returned from an empty Timer list
#define TIMER_KEY_MAX	(int32_t)0x7FFFFFFE // Max key that can be ordered in a Timer list
#define TIMER_KEY_MIN	(int32_t)0x80000000 // Min key that can be ordered in a Timer list

/* Worker constants */
#define WORKER_SIGNATURE	0xEF6A901B

/* Worker flag constants */
#define WORKER_FLAG_NONE	0x00000000
#define WORKER_FLAG_RESCHEDULE	0x00000001 // Worker task should be rescheduled each time the task completes
#define WORKER_FLAG_IMMEDIATE	0x00000002 // Worker task should be executed immediately and then each interval milliseconds
#define WORKER_FLAG_CANCEL	0x00000004 // Internal flag to indicate the worker task should be cancelled next time the interval expires
#define WORKER_FLAG_NOFREE	0x00000008 // Internal flag to tell worker execute not to free the worker request when it is completed
#define WORKER_FLAG_TERMINATE	0x00000010 // Internal flag to tell worker execute to terminate the worker thread
#define WORKER_FLAG_IRQ	0x00000020 // Internal flag to tell worker execute to free IRQ memory when the request is completed
#define WORKER_FLAG_FIQ	0x00000040 // Internal flag to tell worker execute to free FIQ memory when the request is completed
#define WORKER_FLAG_PRIORITY	0x00000080 // Worker task should be executed by a priority worker thread

#define WORKER_FLAG_INTERNAL	WORKER_FLAG_CANCEL | WORKER_FLAG_NOFREE | WORKER_FLAG_TERMINATE | WORKER_FLAG_IRQ | WORKER_FLAG_FIQ // Internal only flags

#define WORKER_FLAG_EXCLUDED_IRQ	WORKER_FLAG_RESCHEDULE | WORKER_FLAG_IMMEDIATE // Excluded flags
#define WORKER_FLAG_EXCLUDED_FIQ	WORKER_FLAG_RESCHEDULE | WORKER_FLAG_IMMEDIATE // Excluded flags

/* Tasker task constants */
#define TASKER_TASK_THREADSENDMESSAGE	1 // Perform a ThreadSendMessage() function using the tasker list
#define TASKER_TASK_MESSAGESLOTSEND	2 // Perform a MessageslotSend() function using the tasker list
#define TASKER_TASK_SEMAPHORESIGNAL	3 // Perform a SemaphoreSignal() function using the tasker list
#define TASKER_TASK_COMPLETIONRESET	4 // Perform a CompletionReset() function using the tasker list
#define TASKER_TASK_COMPLETIONCOMPLETE	5 // Perform a CompletionComplete() or CompletionCompleteAll() function using the tasker list

/* Scheduler migration constants */
#define SCHEDULER_MIGRATION_DISABLED	0
#define SCHEDULER_MIGRATION_ENABLED	1

/* Scheduler preempt constants */
#define SCHEDULER_PREEMPT_DISABLED	0
#define SCHEDULER_PREEMPT_ENABLED	1

/* Scheduler allocation constants */
#define SCHEDULER_ALLOCATION_DISABLED	0
#define SCHEDULER_ALLOCATION_ENABLED	1

/* Scheduler mask constants */
#define SCHEDULER_MASK_NONE	(1 << THREAD_PRIORITY_NONE)
#define SCHEDULER_MASK_IDLE	(1 << THREAD_PRIORITY_IDLE)
#define SCHEDULER_MASK_LOWEST	(1 << THREAD_PRIORITY_LOWEST)
#define SCHEDULER_MASK_LOWER	(1 << THREAD_PRIORITY_LOWER)
#define SCHEDULER_MASK_NORMAL	(1 << THREAD_PRIORITY_NORMAL)
#define SCHEDULER_MASK_HIGHER	(1 << THREAD_PRIORITY_HIGHER)
#define SCHEDULER_MASK_HIGHEST	(1 << THREAD_PRIORITY_HIGHEST)
#define SCHEDULER_MASK_CRITICAL	(1 << THREAD_PRIORITY_CRITICAL)

static const uint32_t SCHEDULER_MASKS[THREAD_PRIORITY_COUNT] = {
  SCHEDULER_MASK_NONE,
  SCHEDULER_MASK_IDLE,
  SCHEDULER_MASK_LOWEST,
  SCHEDULER_MASK_LOWER,
  SCHEDULER_MASK_NORMAL,
  SCHEDULER_MASK_HIGHER,
  SCHEDULER_MASK_HIGHEST,
  SCHEDULER_MASK_CRITICAL};

/* Scheduler quantum constants */
#define SCHEDULER_QUANTUM_NONE	0
#define SCHEDULER_QUANTUM_IDLE	0
#define SCHEDULER_QUANTUM_LOWEST	1
#define SCHEDULER_QUANTUM_LOWER	2
#define SCHEDULER_QUANTUM_NORMAL	4
#define SCHEDULER_QUANTUM_HIGHER	6
#define SCHEDULER_QUANTUM_HIGHEST	8
#define SCHEDULER_QUANTUM_CRITICAL	10

static const uint32_t SCHEDULER_QUANTUMS[THREAD_PRIORITY_COUNT] = {
  SCHEDULER_QUANTUM_NONE,
  SCHEDULER_QUANTUM_IDLE,
  SCHEDULER_QUANTUM_LOWEST,
  SCHEDULER_QUANTUM_LOWER,
  SCHEDULER_QUANTUM_NORMAL,
  SCHEDULER_QUANTUM_HIGHER,
  SCHEDULER_QUANTUM_HIGHEST,
  SCHEDULER_QUANTUM_CRITICAL};

/* ============================================================================== */
/* Thread specific types */

/* See also Handle types in GlobalConst */

/* Spin entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _SPIN_ENTRY SPIN_ENTRY;
struct _SPIN_ENTRY
{
	// Spin Properties
	uint32_t signature; // Signature for entry validation
	uint32_t state; // State of the lock (Locked/Unlocked)
	uint32_t mask; // IRQ/FIQ Mask for Save/Restore
	THREAD_HANDLE owner; // Currently owning thread (or INVALID_HANDLE_VALUE if not locked)
	// Internal Properties
	SPIN_ENTRY *prev; // Previous entry in Spin table
	SPIN_ENTRY *next; // Next entry in Spin table
	// Statistics Properties
};

/* Mutex entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _MUTEX_ENTRY MUTEX_ENTRY;
struct _MUTEX_ENTRY
{
	// Mutex Properties
	uint32_t signature; // Signature for entry validation
	uint32_t state; // State of the lock (Locked/Unlocked)
	THREAD_HANDLE owner; // Currently owning thread (or INVALID_HANDLE_VALUE if not locked)
	thread_yield_proc yield; // Yield function to call while waiting
	uint32_t count; // Count of lock recursions (only if Flags includes MUTEX_FLAG_RECURSIVE)
	uint32_t flags; // Mutex Flags (eg MUTEX_FLAG_RECURSIVE)
	uint32_t spincount; // Number of times to spin wait for lock before Yield is called (Always 0 if SCHEDULER_CPU_COUNT = 1)
	// Internal Properties
	MUTEX_ENTRY *prev; // Previous entry in Mutex table
	MUTEX_ENTRY *next; // Next entry in Mutex table
	// Statistics Properties
};

/* Critical Section entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _CRITICAL_SECTION_ENTRY CRITICAL_SECTION_ENTRY;
struct _CRITICAL_SECTION_ENTRY
{
	// Critical Section Properties
	uint32_t signature; // Signature for entry validation
	uint32_t state; // State of the lock (Locked/Unlocked)
	uint32_t count; // Count of lock recursions
	THREAD_HANDLE owner; // Currently owning thread (or INVALID_HANDLE_VALUE if not locked)
	uint32_t spincount; // Number of times to spin wait for lock before Wait is called (Always 0 if SCHEDULER_CPU_COUNT = 1)
	SPIN_HANDLE lock; // Critical Section Lock
	LIST_HANDLE list; // List of threads waiting on this CriticalSection (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; // Wait function to call to wait on the CriticalSection if it is already locked
	thread_wait_ex_proc waitex; // Wait function to call to wait with timeout on the CriticalSection if it is already locked
	thread_release_proc release; // Release function to call if any threads are waiting when CriticalSection is unlocked
	thread_abandon_proc abandon; // Abandon function to call if any threads are waiting when CriticalSection is destroyed
	// Internal Properties
	CRITICAL_SECTION_ENTRY *prev; // Previous entry in CriticalSection table
	CRITICAL_SECTION_ENTRY *next; // Next entry in CriticalSection table
	// Statistics Properties
};

/* Semaphore entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _SEMAPHORE_ENTRY SEMAPHORE_ENTRY;
struct _SEMAPHORE_ENTRY
{
	// Semaphore Properties
	uint32_t signature; // Signature for entry validation
	uint32_t count; // Count for this Semaphore (Can be negative when Threads are waiting)
	uint32_t maximum; // Maximum count for this Semaphore
	uint32_t flags; // Semaphore Flags (eg SEMAPHORE_FLAG_IRQ)
	SPIN_HANDLE lock; // Semaphore Lock
	LIST_HANDLE list; // List of threads waiting on this Semaphore (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; // Wait function to call to wait on the Semaphore if the count is equal to zero on SemaphoreWait
	thread_wait_ex_proc waitex; // Wait function to call to wait with timeout on the Semaphore if the count is equal to zero on SemaphoreWait
	thread_release_proc release; // Release function to call if any threads are waiting on SemaphoreSignal
	thread_abandon_proc abandon; // Abandon function to call if any threads are waiting when SemaphoreSignal is destroyed
	// Internal Properties
	SEMAPHORE_ENTRY *prev; // Previous entry in Semaphore table
	SEMAPHORE_ENTRY *next; // Next entry in Semaphore table
	// Statistics Properties
};

/* Synchronizer entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _SYNCHRONIZER_ENTRY SYNCHRONIZER_ENTRY;
struct _SYNCHRONIZER_ENTRY
{
	// Synchronizer Properties
	uint32_t signature; // Signature for entry validation
	uint32_t state; // State of the lock (Locked/Unlocked)
	SPIN_HANDLE lock; // Synchronizer Lock
	uint32_t readercount; // Count of current reader locks
	uint32_t writercount; // Count of current writer lock recursions
	THREAD_HANDLE readerlast; // Last thread to acquire reader lock (or INVALID_HANDLE_VALUE if no reader)
	THREAD_HANDLE writerowner; // Currently owning writer thread (or INVALID_HANDLE_VALUE if no writer)
	LIST_HANDLE readerlist; // List of reader threads waiting on this Synchronizer (or INVALID_HANDLE_VALUE if never used)
	LIST_HANDLE writerlist; // List of writer threads waiting on this Synchronizer (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; // Wait function to call to wait on the Synchronizer if it is already locked
	thread_wait_ex_proc waitex; // Wait function to call to wait with timeout on the Synchronizer if it is already locked
	thread_release_proc release; // Release function to call if any threads are waiting when Synchronizer is unlocked
	thread_abandon_proc abandon; // Abandon function to call if any threads are waiting when Synchronizer is destroyed
	// Internal Properties
	SYNCHRONIZER_ENTRY *prev; // Previous entry in Synchronizer table
	SYNCHRONIZER_ENTRY *next; // Next entry in Synchronizer table
	// Statistics Properties
};

/* Condition entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _CONDITION_ENTRY CONDITION_ENTRY;
struct _CONDITION_ENTRY
{
	// Condition Properties
	uint32_t signature; // Signature for entry validation
	uint32_t flags; // Condition Flags (eg CONDITION_FLAG_NONE)
	SPIN_HANDLE lock; // Condition Lock
	LIST_HANDLE list; // List of threads waiting on this Condition (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; // Wait function to call to wait on the Condition
	thread_wait_ex_proc waitex; // Wait function to call to wait with timeout on the Condition
	thread_release_proc release; // Release function to call if any threads are waiting when Condition is woken
	thread_abandon_proc abandon; // Abandon function to call if any threads are waiting when Condition is destroyed
	// Internal Properties
	CONDITION_ENTRY *prev; // Previous entry in Condition table
	CONDITION_ENTRY *next; // Next entry in Condition table
	// Statistics Properties
};

/* Completion entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _COMPLETION_ENTRY COMPLETION_ENTRY;
struct _COMPLETION_ENTRY
{
	// Completion Properties
	uint32_t signature; // Signature for entry validation
	uint32_t state; // State of the completion (Reset/Complete)
	uint32_t count; // Count of the completion (Only applicable if COMPLETION_FLAG_COUNTED)
	uint32_t flags; // Completion Flags (eg COMPLETION_FLAG_IRQ)
	SPIN_HANDLE lock; // Completion Lock
	LIST_HANDLE list; // List of threads waiting on this Completion (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; // Wait function to call to wait on the Completion
	thread_wait_ex_proc waitex; // Wait function to call to wait with timeout on the Completion
	thread_release_proc release; // Release function to call if any threads are waiting when Completion is completed
	thread_abandon_proc abandon; // Abandon function to call if any threads are waiting when Completion is destroyed
	// Internal Properties
	COMPLETION_ENTRY *prev; // Previous entry in Completion table
	COMPLETION_ENTRY *next; // Next entry in Completion table
	// Statistics Properties
};

/* List entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _LIST_ELEMENT LIST_ELEMENT;
typedef struct _LIST_ENTRY LIST_ENTRY;
struct _LIST_ENTRY
{
	// List Properties
	uint32_t signature; // Signature for entry validation
	uint32_t listtype; // Type of this List (eg LIST_TYPE_WAIT_SECTION)
	uint32_t count; // Count of items currently in this List
	uint32_t flags; // List Flags (eg LIST_FLAG_IRQ)
	SPIN_HANDLE lock; // List Lock
	LIST_ELEMENT *first; // First element in List
	LIST_ELEMENT *last; // Last element in List
	// Internal Properties
	LIST_ENTRY *prev; // Previous entry in List table
	LIST_ENTRY *next; // Next entry in List table
	// Statistics Properties
};

/* List element */
struct _LIST_ELEMENT
{
	THREAD_HANDLE thread; // The thread referenced by this List element
	LIST_ELEMENT *prev; // Previous element in List
	LIST_ELEMENT *next; // Next element in List
};

/* List handles */
typedef LIST_HANDLE LIST_HANDLES[THREAD_LISTS_MAXIMUM];

/* Queue entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _QUEUE_ELEMENT QUEUE_ELEMENT;
typedef struct _QUEUE_ENTRY QUEUE_ENTRY;
struct _QUEUE_ENTRY
{
	// Queue Properties
	uint32_t signature; // Signature for entry validation
	uint32_t queuetype; // Type of this Queue (eg QUEUE_TYPE_SCHEDULE_IDLE)
	uint32_t count; // Count of items currently in this Queue
	uint32_t flags; // Queue Flags (eg QUEUE_FLAG_IRQ)
	SPIN_HANDLE lock; // Queue Lock
	QUEUE_ELEMENT *first; // First element in Queue
	QUEUE_ELEMENT *last; // Last element in Queue
	// Internal Properties
	QUEUE_ENTRY *prev; // Previous entry in Queue table
	QUEUE_ENTRY *next; // Next entry in Queue table
	// Statistics Properties
};

/* Queue element */
struct _QUEUE_ELEMENT
{
	int key; // Ordering key for Queue
	THREAD_HANDLE thread; // The thread referenced by this Queue element
	QUEUE_ELEMENT *prev; // Previous element in Queue
	QUEUE_ELEMENT *next; // Next element in Queue
};

/* Message list */
typedef struct _THREAD_MESSAGE THREAD_MESSAGE;
typedef struct _MESSAGE_LIST MESSAGE_LIST;
struct _MESSAGE_LIST
{
	// Header Properties
	uint32_t maximum; // Maximum number of messages in list
	uint32_t count; // Current number of messages in list
	uint32_t start; // First message available in list
	// Internal Properties
	THREAD_MESSAGE *list; // Message list
	// Statistics Properties
};

/* Message */
struct _THREAD_MESSAGE
{
	size_t msg;
	size_t wparam;
	ssize_t lparam;
	uint32_t time;
};

/* Thread entry */
/* Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _THREAD_ENTRY THREAD_ENTRY;
struct _THREAD_ENTRY
{
	// Thread Properties
	uint32_t signature; // Signature for entry validation
	uint32_t state; // State of the Thread (eg THREAD_STATE_RUNNING)
	uint32_t flags; // Flags of the Thread (eg THREAD_FLAG_PERSIST)
	uint32_t priority; // Priority of the Thread (eg THREAD_PRIORITY_NORMAL)
	uint32_t affinity; // CPU Affinity mask of the Thread
	void *stackbase; // Base (Top) of the thread stack
	uint32_t stacksize; // Stack length in bytes
	char name[THREAD_NAME_LENGTH]; // The name of the Thread
	SPIN_HANDLE lock; // Thread Lock
	THREAD_HANDLE parent; // Handle of the parent thread
	MESSAGE_LIST messages; // Messages sent to this thread
	void *tlspointer; // Thread Local Storage Memory (RTL ThreadVars)
	void *tlstable[THREAD_TLS_MAXIMUM]; // Thread Local Storage Index Pointers (for ThreadGetTlsValue/ThreadSetTlsValue) //To Do //Test
	uint32_t tlsflags[THREAD_TLS_MAXIMUM]; // Thread Local Storage Index Flags (eg THREAD_TLS_FLAG_FREE)
	uint32_t exitcode; // Thread Exit Code
	uint32_t lasterror; // Thread Last Error
	LCID locale; // Thread Locale
	// Internal Properties
	uint32_t currentcpu; // Saved current CPU from last ContextSwitch
	void *stackpointer; // Saved current stack pointer from last ContextSwitch
	uint32_t targetcpu; // Target CPU of the Thread for next ContextSwitch
	uint32_t targetpriority; // Target Priority of the Thread for next ContextSwitch (eg THREAD_PRIORITY_NORMAL)
	LIST_HANDLE list; // List of threads waiting on this thread (or INVALID_HANDLE_VALUE if never used)
	LIST_HANDLE waitlist; // The wait list this thread is currently in (or INVALID_HANDLE_VALUE)
	LIST_HANDLES *waitlists; // The wait lists this thread is currently in if doing a multiple wait (or nil)
	uint32_t waitresult; // The result code for the last wait with timeout (eg WAIT_TIMEOUT)
	uint32_t receiveresult; // The result code for the last receive with timeout (eg WAIT_TIMEOUT)
	QUEUE_HANDLE schedulequeue; // The scheduler queue this thread is currently in  (or INVALID_HANDLE_VALUE)
	LIST_ELEMENT listelement; // List element for this thread when in a Wait List
	QUEUE_ELEMENT queueelement; // Queue element for this thread when in a Schedule Queue
	THREAD_ENTRY *prev; // Previous entry in Thread table
	THREAD_ENTRY *next; // Next entry in Thread table
	// Statistics Properties
	int64_t createtime; // The time when this thread was created
	int64_t exittime; // The time when this thread exited or was terminated
	int64_t kerneltime; // The total amount of time this thread has been in the running state (ie CPU time consumed)
	int64_t switchcount; // The number of times this thread has been selected to run by a context switch
};

/* Thread snapshot */
typedef struct _THREAD_SNAPSHOT THREAD_SNAPSHOT;
struct _THREAD_SNAPSHOT
{
	// Snapshot Properties
	THREAD_HANDLE handle; // Handle of the thread
	uint32_t state; // State of the Thread (eg THREAD_STATE_RUNNING)
	uint32_t flags; // Flags of the Thread (eg THREAD_FLAG_PERSIST)
	uint32_t cpu; // CPU from last ContextSwitch
	uint32_t priority; // Priority of the Thread (eg THREAD_PRIORITY_NORMAL)
	uint32_t affinity; // CPU Affinity mask of the Thread
	void *stackbase; // Base (Top) of the thread stack
	uint32_t stacksize; // Stack length in bytes
	void *stackpointer; // Stack pointer from last ContextSwitch
	char name[THREAD_NAME_LENGTH]; // The name of the Thread
	THREAD_HANDLE parent; // Handle of the parent thread
	uint32_t exitcode; // Thread Exit Code
	uint32_t lasterror; // Thread Last Error
	LCID locale; // Thread Locale
	uint32_t targetcpu; // Target CPU of the Thread for next ContextSwitch
	uint32_t targetpriority; // Target Priority of the Thread for next ContextSwitch (eg THREAD_PRIORITY_NORMAL)
	int64_t createtime; // The time when this thread was created
	int64_t exittime; // The time when this thread exited or was terminated
	int64_t kerneltime; // The total amount of time this thread has been in the running state (ie CPU time consumed)
	int64_t switchcount; // The number of times this thread has been selected to run by a context switch
	// Internal Properties
	THREAD_SNAPSHOT *next; // Next entry in Thread snapshot
};

/* Messageslot entry */
typedef struct _MESSAGESLOT_ENTRY MESSAGESLOT_ENTRY;
struct _MESSAGESLOT_ENTRY
{
	// Messageslot Properties
	uint32_t signature; // Signature for entry validation
	uint32_t flags; // Messageslot Flags (eg MESSAGESLOT_FLAG_IRQ)
	SPIN_HANDLE lock; // Messageslot Lock
	LIST_HANDLE list; // List of threads waiting on this Messageslot (or INVALID_HANDLE_VALUE if never used)
	MESSAGE_LIST messages; // Messageslot message queue
	thread_wait_proc wait; // Wait function to call to wait on the Messageslot if there are no messages
	thread_wait_ex_proc waitex; // Wait function to call to wait with timeout on the Messageslot if there are no messages
	thread_release_proc release; // Release function to call if any threads are waiting when a message is sent
	thread_abandon_proc abandon; // Abandon function to call if any threads are waiting when Messageslot is destroyed
	// Internal Properties
	MESSAGESLOT_ENTRY *prev; // Previous entry in Messageslot table
	MESSAGESLOT_ENTRY *next; // Next entry in Messageslot table
	// Statistics Properties
};

/* Mailslot entry */
typedef struct _MAILSLOT_ENTRY MAILSLOT_ENTRY;
struct _MAILSLOT_ENTRY
{
	// Mailslot Properties
	uint32_t signature; // Signature for entry validation
	uint32_t maximum; // Maximum number of messages in Mailslot
	uint32_t count; // Current number of messages in Mailslot
	uint32_t start; // First message available in Mailslot
	SPIN_HANDLE lock; // Mailslot Lock
	SEMAPHORE_HANDLE sender; // Mailslot send Semaphore
	SEMAPHORE_HANDLE receiver; // Mailslot receive Semaphore
	ssize_t *messages; // Mailslot message queue
	// Internal Properties
	MAILSLOT_ENTRY *prev; // Previous entry in Mailslot table
	MAILSLOT_ENTRY *next; // Next entry in Mailslot table
	// Statistics Properties
};

/* Buffer entry */
typedef struct _BUFFER_ITEM BUFFER_ITEM;
typedef struct _BUFFER_ENTRY BUFFER_ENTRY;
struct _BUFFER_ENTRY
{
	// Buffer Properties
	uint32_t signature; // Signature for entry validation
	uint32_t size; // Size of each buffer
	uint32_t count; // Number of buffers
	uint32_t flags; // Buffer Flags (eg BUFFER_FLAG_SHARED)
	SPIN_HANDLE lock; // Buffer Lock
	SEMAPHORE_HANDLE available; // Buffer available Semaphore
	BUFFER_ITEM *buffers; // Buffer list
	// Internal Properties
	BUFFER_ENTRY *prev; // Previous entry in Buffer table
	BUFFER_ENTRY *next; // Next entry in Buffer table
	BUFFER_ITEM *first; // First available buffer item
	// Statistics Properties
};

/* Buffer item */
struct _BUFFER_ITEM
{
	BUFFER_HANDLE parent; // Handle of Buffer owning this item
	BUFFER_ITEM *next; // Next item in list
	void *buffer; // Pointer to item data
	uint32_t reserved; // Align to 16 bytes
};

/* Event entry */
typedef struct _EVENT_ENTRY EVENT_ENTRY;
struct _EVENT_ENTRY
{
	// Event Properties
	uint32_t signature; // Signature for entry validation
	uint32_t state; // State of the event (Signaled/Unsignaled)
	uint32_t flags; // Event Flags (eg EVENT_FLAG_MANUAL)
	SPIN_HANDLE lock; // Event Lock
	LIST_HANDLE list; // List of threads waiting on this Event (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; // Wait function to call to wait on the Event if it is not Signaled
	thread_wait_ex_proc waitex; // Wait function to call to wait with timeout on the Event if it is not Signaled
	thread_release_proc release; // Release function to call if any threads are waiting when Event is Signaled
	thread_abandon_proc abandon; // Abandon function to call if any threads are waiting when Event is destroyed
	// Internal Properties
	EVENT_ENTRY *prev; // Previous entry in Event table
	EVENT_ENTRY *next; // Next entry in Event table
	// Statistics Properties
};

/* Timer list */
typedef struct _TIMER_ITEM TIMER_ITEM;
typedef struct _TIMER_LIST TIMER_LIST;
struct _TIMER_LIST
{
	// List Properties
	uint32_t count; // Count of items currently in the Timer list
	uint32_t flags; // Timer list Flags (eg LOCK_FLAG_IRQ)
	SPIN_HANDLE lock; // Timer list Lock
	TIMER_ITEM *first; // First item in Timer list
	TIMER_ITEM *last; // Last item in Timer list
	// Internal Properties
	// Statistics Properties
};

/* Timer item */
struct _TIMER_ITEM
{
	int key; // Ordering key for Timer list
	TIMER_HANDLE timer; // The timer referenced by this Timer list item
	TIMER_ITEM *prev; // Previous item in Timer list
	TIMER_ITEM *next; // Next item in Timer list
};

/* Timer entry */
typedef struct _TIMER_ENTRY TIMER_ENTRY;
struct _TIMER_ENTRY
{
	// Timer Properties
	uint32_t signature; // Signature for entry validation
	uint32_t interval; // Interval for timer (Milliseconds)
	uint32_t state; // State of the timer (Enabled/Disabled)
	uint32_t flags; // Timer Flags (eg TIMER_FLAG_RESCHEDULE)
	SPIN_HANDLE lock; // Timer Lock
	timer_event_proc event; // Function to call when timer triggers
	void *data; // Data to pass to function when timer triggers
	// Internal Properties
	TIMER_LIST *timerlist; // The timer list this timer is currently in (or nil)
	TIMER_ITEM timeritem; // Timer list item for this timer when in a Timer list
	TIMER_ENTRY *prev; // Previous entry in Timer table
	TIMER_ENTRY *next; // Next entry in Timer table
	// Statistics Properties
};

/* Worker request */
typedef struct _WORKER_REQUEST WORKER_REQUEST;
struct _WORKER_REQUEST
{
	// Worker Properties
	uint32_t signature; // Signature for entry validation
	uint32_t interval; // Interval for worker (Milliseconds)
	uint32_t flags; // Worker Flags (eg WORKER_FLAG_RESCHEDULE)
	SPIN_HANDLE lock; // Worker Lock (or INVALID_HANDLE_VALUE if Interval is 0 and Flags is not WORKER_FLAG_RESCHEDULE)
	TIMER_HANDLE timer; // Worker Timer (or INVALID_HANDLE_VALUE if Interval is 0)
	worker_task_proc task; // Task to call by worker
	void *data; // Data to pass to task
	worker_cb callback; // Callback when task is completed
};

/* Tasker list */
typedef struct _TASKER_TASK TASKER_TASK;
typedef struct _TASKER_LIST TASKER_LIST;
struct _TASKER_LIST
{
	// List Properties
	uint32_t count; // Count of tasks currently in the Tasker list
	SPIN_HANDLE lock; // Tasker list Lock
	TASKER_TASK *first; // First task in Tasker list
	TASKER_TASK *last; // Last task in Tasker list
	// Internal Properties
	// Statistics Properties
};

/* Tasker task */
struct _TASKER_TASK
{
	uint32_t task; // The task to be performed
	TASKER_TASK *prev; // Previous task in Tasker list
	TASKER_TASK *next; // Next task in Tasker list
};

/* Tasker ThreadSendMessage task */
typedef struct _TASKER_THREAD_SEND_MESSAGE TASKER_THREAD_SEND_MESSAGE;
struct _TASKER_THREAD_SEND_MESSAGE
{
	uint32_t task; // The task to be performed
	TASKER_TASK *prev; // Previous task in Tasker list
	TASKER_TASK *next; // Next task in Tasker list
	// Internal Properties
	THREAD_HANDLE thread; // Handle of the thread to send a message to
	THREAD_MESSAGE message; // Message to send to the thread
};

/* Tasker MessageslotSend task */
typedef struct _TASKER_MESSAGESLOT_SEND TASKER_MESSAGESLOT_SEND;
struct _TASKER_MESSAGESLOT_SEND
{
	uint32_t task; // The task to be performed
	TASKER_TASK *prev; // Previous task in Tasker list
	TASKER_TASK *next; // Next task in Tasker list
	// Internal Properties
	MESSAGESLOT_HANDLE messageslot; // Handle of the message slot to send to
	THREAD_MESSAGE message; // Message to be sent
};

/* Tasker SemaphoreSignal task */
typedef struct _TASKER_SEMAPHORE_SIGNAL TASKER_SEMAPHORE_SIGNAL;
struct _TASKER_SEMAPHORE_SIGNAL
{
	uint32_t task; // The task to be performed
	TASKER_TASK *prev; // Previous task in Tasker list
	TASKER_TASK *next; // Next task in Tasker list
	// Internal Properties
	SEMAPHORE_HANDLE semaphore; // Handle of the semaphore to signal
	uint32_t count; // The count to be signalled
};

/* Tasker CompletionReset task */
typedef struct _TASKER_SEMAPHORE_RESET TASKER_SEMAPHORE_RESET;
struct _TASKER_SEMAPHORE_RESET
{
	uint32_t task; // The task to be performed
	TASKER_TASK *prev; // Previous task in Tasker list
	TASKER_TASK *next; // Next task in Tasker list
	// Internal Properties
	COMPLETION_HANDLE completion; // Handle of the completion to reset
};

/* Tasker CompletionComplete task */
typedef struct _TASKER_SEMAPHORE_COMPLETE TASKER_SEMAPHORE_COMPLETE;
struct _TASKER_SEMAPHORE_COMPLETE
{
	uint32_t task; // The task to be performed
	TASKER_TASK *prev; // Previous task in Tasker list
	TASKER_TASK *next; // Next task in Tasker list
	// Internal Properties
	COMPLETION_HANDLE completion; // Handle of the completion to complete or complete all
	LONGBOOL all; // False for complete, True for complete all
};

/* Prototypes for Thread Start/End Handlers */
typedef ssize_t STDCALL (*thread_start_proc)(void *parameter);
typedef void STDCALL (*thread_end_proc)(uint32_t exitcode);

/* ============================================================================== */
/* Spin Functions */
SPIN_HANDLE STDCALL spin_create(void);
SPIN_HANDLE STDCALL spin_create_ex(BOOL initialowner);
uint32_t STDCALL spin_destroy(SPIN_HANDLE spin);

THREAD_HANDLE STDCALL spin_owner(SPIN_HANDLE spin);

uint32_t STDCALL spin_lock(SPIN_HANDLE spin);
uint32_t STDCALL spin_unlock(SPIN_HANDLE spin);

uint32_t STDCALL spin_lock_irq(SPIN_HANDLE spin);
uint32_t STDCALL spin_unlock_irq(SPIN_HANDLE spin);

uint32_t STDCALL spin_lock_fiq(SPIN_HANDLE spin);
uint32_t STDCALL spin_unlock_fiq(SPIN_HANDLE spin);

uint32_t STDCALL spin_lock_irq_fiq(SPIN_HANDLE spin);
uint32_t STDCALL spin_unlock_irq_fiq(SPIN_HANDLE spin);

uint32_t STDCALL spin_lock_preempt(SPIN_HANDLE spin);
uint32_t STDCALL spin_unlock_preempt(SPIN_HANDLE spin);

BOOL STDCALL spin_check_irq(SPIN_HANDLE spin);
BOOL STDCALL spin_check_fiq(SPIN_HANDLE spin);

uint32_t STDCALL spin_exchange_irq(SPIN_HANDLE spin1, SPIN_HANDLE spin2);
uint32_t STDCALL spin_exchange_fiq(SPIN_HANDLE spin1, SPIN_HANDLE spin2);

/* ============================================================================== */
/* Mutex Functions */
MUTEX_HANDLE STDCALL mutex_create(void);
MUTEX_HANDLE STDCALL mutex_create_ex(BOOL initialowner, uint32_t spincount, uint32_t flags);
uint32_t STDCALL mutex_destroy(MUTEX_HANDLE mutex);

uint32_t STDCALL mutex_flags(MUTEX_HANDLE mutex);
uint32_t STDCALL mutex_count(MUTEX_HANDLE mutex);
THREAD_HANDLE STDCALL mutex_owner(MUTEX_HANDLE mutex);

uint32_t STDCALL mutex_lock(MUTEX_HANDLE mutex);
uint32_t STDCALL mutex_unlock(MUTEX_HANDLE mutex);
uint32_t STDCALL mutex_try_lock(MUTEX_HANDLE mutex);

/* ============================================================================== */
/* Critical Section Functions */
CRITICAL_SECTION_HANDLE STDCALL critical_section_create(void);
CRITICAL_SECTION_HANDLE STDCALL critical_section_create_ex(BOOL initialowner, uint32_t spincount);
uint32_t STDCALL critical_section_destroy(CRITICAL_SECTION_HANDLE criticalsection);

uint32_t STDCALL critical_section_count(CRITICAL_SECTION_HANDLE criticalsection);
THREAD_HANDLE STDCALL critical_section_owner(CRITICAL_SECTION_HANDLE criticalsection);
uint32_t STDCALL critical_section_set_spin_count(CRITICAL_SECTION_HANDLE criticalsection, uint32_t spincount);

uint32_t STDCALL critical_section_lock(CRITICAL_SECTION_HANDLE criticalsection);
uint32_t STDCALL critical_section_lock_ex(CRITICAL_SECTION_HANDLE criticalsection, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL critical_section_unlock(CRITICAL_SECTION_HANDLE criticalsection);
uint32_t STDCALL critical_section_try_lock(CRITICAL_SECTION_HANDLE criticalsection);

/* ============================================================================== */
/* Semaphore Functions */
SEMAPHORE_HANDLE STDCALL semaphore_create(uint32_t count);
SEMAPHORE_HANDLE STDCALL semaphore_create_ex(uint32_t count, uint32_t maximum, uint32_t flags);
uint32_t STDCALL semaphore_destroy(SEMAPHORE_HANDLE semaphore);

uint32_t STDCALL semaphore_count(SEMAPHORE_HANDLE semaphore);

uint32_t STDCALL semaphore_wait(SEMAPHORE_HANDLE semaphore);
uint32_t STDCALL semaphore_wait_ex(SEMAPHORE_HANDLE semaphore, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL semaphore_signal(SEMAPHORE_HANDLE semaphore);
uint32_t STDCALL semaphore_signal_ex(SEMAPHORE_HANDLE semaphore, uint32_t count, uint32_t *previous);

/* ============================================================================== */
/* Synchronizer Functions */
SYNCHRONIZER_HANDLE STDCALL synchronizer_create(void);
SYNCHRONIZER_HANDLE STDCALL synchronizer_create_ex(BOOL initialreader, BOOL initialwriter);
uint32_t STDCALL synchronizer_destroy(SYNCHRONIZER_HANDLE synchronizer);

uint32_t STDCALL synchronizer_reader_count(SYNCHRONIZER_HANDLE synchronizer);
THREAD_HANDLE STDCALL synchronizer_reader_last(SYNCHRONIZER_HANDLE synchronizer);

uint32_t STDCALL synchronizer_reader_lock(SYNCHRONIZER_HANDLE synchronizer);
uint32_t STDCALL synchronizer_reader_lock_ex(SYNCHRONIZER_HANDLE synchronizer, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL synchronizer_reader_unlock(SYNCHRONIZER_HANDLE synchronizer);
uint32_t STDCALL synchronizer_reader_convert(SYNCHRONIZER_HANDLE synchronizer);
uint32_t STDCALL synchronizer_reader_convert_ex(SYNCHRONIZER_HANDLE synchronizer, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

uint32_t STDCALL synchronizer_writer_count(SYNCHRONIZER_HANDLE synchronizer);
THREAD_HANDLE STDCALL synchronizer_writer_owner(SYNCHRONIZER_HANDLE synchronizer);

uint32_t STDCALL synchronizer_writer_lock(SYNCHRONIZER_HANDLE synchronizer);
uint32_t STDCALL synchronizer_writer_lock_ex(SYNCHRONIZER_HANDLE synchronizer, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL synchronizer_writer_unlock(SYNCHRONIZER_HANDLE synchronizer);
uint32_t STDCALL synchronizer_writer_convert(SYNCHRONIZER_HANDLE synchronizer);

/* ============================================================================== */
/* Condition Functions */
CONDITION_HANDLE STDCALL condition_create(void);
uint32_t STDCALL condition_destroy(CONDITION_HANDLE condition);

uint32_t STDCALL condition_wait(CONDITION_HANDLE condition, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL condition_wait_mutex(CONDITION_HANDLE condition, MUTEX_HANDLE mutex, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL condition_wait_synchronizer(CONDITION_HANDLE condition, SYNCHRONIZER_HANDLE synchronizer, uint32_t flags, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL condition_wait_critical_section(CONDITION_HANDLE condition, CRITICAL_SECTION_HANDLE criticalsection, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

uint32_t STDCALL condition_wake(CONDITION_HANDLE condition);
uint32_t STDCALL condition_wake_all(CONDITION_HANDLE condition);

/* ============================================================================== */
/* Completion Functions */
COMPLETION_HANDLE STDCALL completion_create(uint32_t flags);
uint32_t STDCALL completion_destroy(COMPLETION_HANDLE completion);

uint32_t STDCALL completion_state(COMPLETION_HANDLE completion);

uint32_t STDCALL completion_wait(COMPLETION_HANDLE completion, uint32_t timeout);
uint32_t STDCALL completion_try_wait(COMPLETION_HANDLE completion);

uint32_t STDCALL completion_reset(COMPLETION_HANDLE completion);
uint32_t STDCALL completion_complete(COMPLETION_HANDLE completion);
uint32_t STDCALL completion_complete_all(COMPLETION_HANDLE completion);

/* ============================================================================== */
/* List Functions */
LIST_HANDLE STDCALL list_create(void);
LIST_HANDLE STDCALL list_create_ex(uint32_t listtype, uint32_t flags);
uint32_t STDCALL list_destroy(LIST_HANDLE list);

uint32_t STDCALL list_count(LIST_HANDLE list);

uint32_t STDCALL list_add_first(LIST_HANDLE list, LIST_ELEMENT *element);
uint32_t STDCALL list_add_last(LIST_HANDLE list, LIST_ELEMENT *element);

LIST_ELEMENT * STDCALL list_get_thread(LIST_HANDLE list, THREAD_HANDLE thread);

LIST_ELEMENT * STDCALL list_get_first(LIST_HANDLE list);
LIST_ELEMENT * STDCALL list_get_first_ex(LIST_HANDLE list, BOOL remove);
LIST_ELEMENT * STDCALL list_get_last(LIST_HANDLE list);
LIST_ELEMENT * STDCALL list_get_last_ex(LIST_HANDLE list, BOOL remove);

uint32_t STDCALL list_insert(LIST_HANDLE list, LIST_ELEMENT *previous, LIST_ELEMENT *element);
uint32_t STDCALL list_remove(LIST_HANDLE list, LIST_ELEMENT *element);

BOOL STDCALL list_is_empty(LIST_HANDLE list);
BOOL STDCALL list_not_empty(LIST_HANDLE list);

uint32_t STDCALL list_lock(LIST_HANDLE list);
uint32_t STDCALL list_unlock(LIST_HANDLE list);

/* ============================================================================== */
/* Queue Functions */
QUEUE_HANDLE STDCALL queue_create(void);
QUEUE_HANDLE STDCALL queue_create_ex(uint32_t queuetype, uint32_t flags);
uint32_t STDCALL queue_destroy(QUEUE_HANDLE queue);

uint32_t STDCALL queue_count(QUEUE_HANDLE queue);

uint32_t STDCALL queue_enqueue(QUEUE_HANDLE queue, THREAD_HANDLE thread);
THREAD_HANDLE STDCALL queue_dequeue(QUEUE_HANDLE queue);

int STDCALL queue_first_key(QUEUE_HANDLE queue);
int STDCALL queue_last_key(QUEUE_HANDLE queue);

uint32_t STDCALL queue_insert_key(QUEUE_HANDLE queue, THREAD_HANDLE thread, int key);
uint32_t STDCALL queue_delete_key(QUEUE_HANDLE queue, THREAD_HANDLE thread);
int STDCALL queue_increment_key(QUEUE_HANDLE queue);
int STDCALL queue_decrement_key(QUEUE_HANDLE queue);

BOOL STDCALL queue_is_empty(QUEUE_HANDLE queue);
BOOL STDCALL queue_not_empty(QUEUE_HANDLE queue);

uint32_t STDCALL queue_lock(QUEUE_HANDLE queue);
uint32_t STDCALL queue_unlock(QUEUE_HANDLE queue);

/* ============================================================================== */
/* Thread Functions */
THREAD_HANDLE STDCALL thread_create(thread_start_proc startproc, uint32_t stacksize, uint32_t priority, const char *name, void *parameter);
THREAD_HANDLE STDCALL thread_create_ex(thread_start_proc startproc, uint32_t stacksize, uint32_t priority, uint32_t affinity, uint32_t cpu, const char *name, void *parameter);
uint32_t STDCALL thread_destroy(THREAD_HANDLE thread);

THREAD_HANDLE STDCALL thread_get_current(void);
uint32_t STDCALL thread_set_current(THREAD_HANDLE thread);

uint32_t STDCALL thread_get_name(THREAD_HANDLE thread, char *name, uint32_t len);
uint32_t STDCALL thread_set_name(THREAD_HANDLE thread, const char *name);

uint32_t STDCALL thread_get_cpu(THREAD_HANDLE thread);
uint32_t STDCALL thread_set_cpu(THREAD_HANDLE thread, uint32_t cpu);

uint32_t STDCALL thread_get_state(THREAD_HANDLE thread);

uint32_t STDCALL thread_get_flags(THREAD_HANDLE thread);
uint32_t STDCALL thread_set_flags(THREAD_HANDLE thread, uint32_t flags);
uint32_t STDCALL thread_add_flags(THREAD_HANDLE thread, uint32_t flags);
uint32_t STDCALL thread_remove_flags(THREAD_HANDLE thread, uint32_t flags);

LCID STDCALL thread_get_locale(THREAD_HANDLE thread);
uint32_t STDCALL thread_set_locale(THREAD_HANDLE thread, LCID locale);

uint32_t STDCALL thread_get_times(THREAD_HANDLE thread, int64_t *createtime, int64_t *exittime, int64_t *kerneltime);
uint32_t STDCALL thread_get_switch_count(THREAD_HANDLE thread, int64_t *switchcount);

uint32_t STDCALL thread_get_stack_free(void);
uint32_t STDCALL thread_get_stack_size(THREAD_HANDLE thread);
size_t STDCALL thread_get_stack_base(THREAD_HANDLE thread);
uint32_t STDCALL thread_set_stack_base(THREAD_HANDLE thread, size_t stackbase);
size_t STDCALL thread_get_stack_pointer(THREAD_HANDLE thread);

uint32_t STDCALL thread_get_exit_code(THREAD_HANDLE thread);

uint32_t STDCALL thread_get_affinity(THREAD_HANDLE thread);
uint32_t STDCALL thread_set_affinity(THREAD_HANDLE thread, uint32_t affinity);

uint32_t STDCALL thread_get_priority(THREAD_HANDLE thread);
uint32_t STDCALL thread_set_priority(THREAD_HANDLE thread, uint32_t priority);

uint32_t STDCALL thread_get_last_error(void);
void STDCALL thread_set_last_error(uint32_t lasterror);
uint32_t STDCALL thread_set_last_error_ex(uint32_t lasterror);

uint32_t STDCALL thread_get_wait_result(void);
uint32_t STDCALL thread_get_receive_result(void);

uint32_t STDCALL thread_get_tls_index(uint32_t tlsindex);
uint32_t STDCALL thread_alloc_tls_index(void);
uint32_t STDCALL thread_alloc_tls_index_ex(uint32_t flags);
uint32_t STDCALL thread_release_tls_index(uint32_t tlsindex);
void * STDCALL thread_get_tls_value(uint32_t tlsindex);
uint32_t STDCALL thread_set_tls_value(uint32_t tlsindex, void *tlsvalue);

void * STDCALL thread_get_tls_pointer(THREAD_HANDLE thread);
uint32_t STDCALL thread_set_tls_pointer(THREAD_HANDLE thread, void *tlspointer);

uint32_t STDCALL thread_ready(THREAD_HANDLE thread, BOOL reschedule);
uint32_t STDCALL thread_timeout(THREAD_HANDLE thread);
uint32_t STDCALL thread_wake(THREAD_HANDLE thread);

uint32_t STDCALL thread_migrate(THREAD_HANDLE thread, uint32_t cpu);

void STDCALL thread_end(uint32_t exitcode);
uint32_t STDCALL thread_halt(uint32_t exitcode);
uint32_t STDCALL thread_terminate(THREAD_HANDLE thread, uint32_t exitcode);

uint32_t STDCALL thread_yield(void);
uint32_t STDCALL thread_sleep(uint32_t milliseconds);

uint32_t STDCALL thread_wait(LIST_HANDLE list, SPIN_HANDLE lock, uint32_t flags);
uint32_t STDCALL thread_wait_ex(LIST_HANDLE list, SPIN_HANDLE lock, uint32_t flags, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL thread_release(LIST_HANDLE list);
uint32_t STDCALL thread_abandon(LIST_HANDLE list);
uint32_t STDCALL thread_wait_terminate(THREAD_HANDLE thread, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

uint32_t STDCALL thread_suspend(THREAD_HANDLE thread);
uint32_t STDCALL thread_resume(THREAD_HANDLE thread);

uint32_t STDCALL thread_wait_message(void);
uint32_t STDCALL thread_send_message(THREAD_HANDLE thread, THREAD_MESSAGE *message);
uint32_t STDCALL thread_receive_message(THREAD_MESSAGE *message);
uint32_t STDCALL thread_receive_message_ex(THREAD_MESSAGE *message, uint32_t timeout, BOOL remove); // Timeout = 0 then no Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL thread_abandon_message(THREAD_HANDLE thread);

uint32_t STDCALL thread_lock(THREAD_HANDLE thread);
uint32_t STDCALL thread_unlock(THREAD_HANDLE thread);

/* ============================================================================== */
/* Scheduler Functions */
uint32_t STDCALL scheduler_check(uint32_t cpuid);
uint32_t STDCALL scheduler_wakeup(uint32_t cpuid);
uint32_t STDCALL scheduler_expire(uint32_t cpuid);
THREAD_HANDLE STDCALL scheduler_switch(uint32_t cpuid, THREAD_HANDLE thread);
THREAD_HANDLE STDCALL scheduler_select(uint32_t cpuid, THREAD_HANDLE thread, BOOL yield);
uint32_t STDCALL scheduler_reschedule(BOOL yield);

uint32_t STDCALL scheduler_migration_enable(void);
uint32_t STDCALL scheduler_migration_disable(void);

uint32_t STDCALL scheduler_preempt_enable(uint32_t cpuid);
uint32_t STDCALL scheduler_preempt_disable(uint32_t cpuid);

uint32_t STDCALL scheduler_allocation_enable(uint32_t cpuid);
uint32_t STDCALL scheduler_allocation_disable(uint32_t cpuid);

/* ============================================================================== */
/* Messageslot Functions */
MESSAGESLOT_HANDLE STDCALL messageslot_create(void);
MESSAGESLOT_HANDLE STDCALL messageslot_create_ex(uint32_t maximum, uint32_t flags);
uint32_t STDCALL messageslot_destroy(MESSAGESLOT_HANDLE messageslot);

uint32_t STDCALL messageslot_count(MESSAGESLOT_HANDLE messageslot);

uint32_t STDCALL messageslot_send(MESSAGESLOT_HANDLE messageslot, THREAD_MESSAGE *message);
uint32_t STDCALL messageslot_receive(MESSAGESLOT_HANDLE messageslot, THREAD_MESSAGE *message);
uint32_t STDCALL messageslot_receive_ex(MESSAGESLOT_HANDLE messageslot, THREAD_MESSAGE *message, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/* ============================================================================== */
/* Mailslot Functions */
MAILSLOT_HANDLE STDCALL mailslot_create(uint32_t maximum);
uint32_t STDCALL mailslot_destroy(MAILSLOT_HANDLE mailslot);

uint32_t STDCALL mailslot_count(MAILSLOT_HANDLE mailslot);

uint32_t STDCALL mailslot_send(MAILSLOT_HANDLE mailslot, ssize_t data);
uint32_t STDCALL mailslot_send_ex(MAILSLOT_HANDLE mailslot, ssize_t data, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
ssize_t STDCALL mailslot_receive(MAILSLOT_HANDLE mailslot);
ssize_t STDCALL mailslot_receive_ex(MAILSLOT_HANDLE mailslot, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/* ============================================================================== */
/* Buffer Functions */
BUFFER_HANDLE STDCALL buffer_create(uint32_t size, uint32_t count);
BUFFER_HANDLE STDCALL buffer_create_ex(uint32_t size, uint32_t count, uint32_t flags);
uint32_t STDCALL buffer_destroy(BUFFER_HANDLE buffer);

uint32_t STDCALL buffer_count(BUFFER_HANDLE buffer);
uint32_t STDCALL buffer_available(BUFFER_HANDLE buffer);

void * STDCALL buffer_get(BUFFER_HANDLE buffer);
void * STDCALL buffer_get_ex(BUFFER_HANDLE buffer, uint32_t timeout); // Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever
uint32_t STDCALL buffer_free(void *buffer);

void * STDCALL buffer_iterate(BUFFER_HANDLE buffer, void *previous);

/* ============================================================================== */
/* Event Functions */
EVENT_HANDLE STDCALL event_create(BOOL manualreset, BOOL initialstate);
EVENT_HANDLE STDCALL event_create_ex(uint32_t flags);
uint32_t STDCALL event_destroy(EVENT_HANDLE event);

uint32_t STDCALL event_state(EVENT_HANDLE event);

uint32_t STDCALL event_wait(EVENT_HANDLE event);
uint32_t STDCALL event_wait_ex(EVENT_HANDLE event, uint32_t timeout); // Timeout = 0 then no Wait,Timeout = INFINITE then Wait forever

uint32_t STDCALL event_set(EVENT_HANDLE event);
uint32_t STDCALL event_reset(EVENT_HANDLE event);
uint32_t STDCALL event_pulse(EVENT_HANDLE event);

/* ============================================================================== */
/* Timer Functions */
TIMER_HANDLE STDCALL timer_create(uint32_t interval, BOOL enabled, BOOL reschedule, timer_event_proc event, void *data);
TIMER_HANDLE STDCALL timer_create_ex(uint32_t interval, uint32_t state, uint32_t flags, timer_event_proc event, void *data);
uint32_t STDCALL timer_destroy(TIMER_HANDLE timer);

uint32_t STDCALL timer_enable(TIMER_HANDLE timer);
uint32_t STDCALL timer_enable_ex(TIMER_HANDLE timer, uint32_t interval, timer_event_proc event, void *data);
uint32_t STDCALL timer_disable(TIMER_HANDLE timer);

TIMER_HANDLE STDCALL timer_dequeue(void);

int STDCALL timer_first_key(void);
uint32_t STDCALL timer_insert_key(TIMER_HANDLE timer, int key);
uint32_t STDCALL timer_delete_key(TIMER_HANDLE timer);
int STDCALL timer_decrement_key(void);

BOOL STDCALL timer_is_empty(void);
BOOL STDCALL timer_not_empty(void);

uint32_t STDCALL timer_check(void);
uint32_t STDCALL timer_trigger(void);

/* ============================================================================== */
/* Worker Functions */
uint32_t STDCALL worker_schedule(uint32_t interval, worker_task_proc task, void *data, worker_cb callback);
WORKER_HANDLE STDCALL worker_schedule_ex(uint32_t interval, uint32_t flags, worker_task_proc task, void *data, worker_cb callback);
uint32_t STDCALL worker_cancel(WORKER_HANDLE worker);

uint32_t STDCALL worker_schedule_irq(uint32_t affinity, worker_task_proc task, void *data, worker_cb callback);
uint32_t STDCALL worker_schedule_irq_ex(uint32_t affinity, uint32_t flags, worker_task_proc task, void *data, worker_cb callback);

uint32_t STDCALL worker_schedule_fiq(uint32_t affinity, worker_task_proc task, void *data, worker_cb callback);
uint32_t STDCALL worker_schedule_fiq_ex(uint32_t affinity, uint32_t flags, worker_task_proc task, void *data, worker_cb callback);

uint32_t STDCALL worker_increase(uint32_t count);
uint32_t STDCALL worker_increase_ex(uint32_t count, BOOL priority);
uint32_t STDCALL worker_decrease(uint32_t count);
uint32_t STDCALL worker_decrease_ex(uint32_t count, BOOL priority);

/* ============================================================================== */
/* Tasker Functions */
uint32_t STDCALL tasker_thread_send_message(THREAD_HANDLE thread, THREAD_MESSAGE *message);
uint32_t STDCALL tasker_messageslot_send(MESSAGESLOT_HANDLE messageslot, THREAD_MESSAGE *message);
uint32_t STDCALL tasker_semaphore_signal(SEMAPHORE_HANDLE semaphore, uint32_t count);
uint32_t STDCALL tasker_completion_reset(COMPLETION_HANDLE completion);
uint32_t STDCALL tasker_completion_complete(COMPLETION_HANDLE completion, BOOL all);

uint32_t STDCALL tasker_enqueue(TASKER_TASK *task);
TASKER_TASK * STDCALL tasker_dequeue(void);

uint32_t STDCALL tasker_check(void);
uint32_t STDCALL tasker_trigger(void);

/* ============================================================================== */
/* RTL Thread Manager Functions */
/* See: \source\rtl\inc\thread.inc and \source\rtl\inc\threadh.inc */
/* See: \source\rtl\inc\system.inc and \source\rtl\inc\systemh.inc */

THREAD_ID STDCALL begin_thread(void *signalaction, size_t stacksize, thread_func threadfunction, void *threadparameter, uint32_t creationflags, THREAD_ID *threadid);
THREAD_ID STDCALL begin_thread_ex(void *signalaction, size_t stacksize, thread_func threadfunction, void *threadparameter, uint32_t creationflags, uint32_t priority, uint32_t affinity, uint32_t cpu, const char *name, THREAD_ID *threadid);

void STDCALL end_thread(uint32_t exitcode);

/* ============================================================================== */
/* Thread Helper Functions */
uint32_t STDCALL spin_get_count(void);

uint32_t STDCALL mutex_get_count(void);

uint32_t STDCALL critical_section_get_count(void);

uint32_t STDCALL semaphore_get_count(void);

uint32_t STDCALL synchronizer_get_count(void);

uint32_t STDCALL condition_get_count(void);

uint32_t STDCALL completion_get_count(void);

uint32_t STDCALL list_get_count(void);

uint32_t STDCALL queue_get_count(void);

uint32_t STDCALL thread_get_count(void);

uint32_t STDCALL thread_tls_get_count(void);

void * STDCALL thread_allocate_stack(uint32_t stacksize);
void STDCALL thread_release_stack(void *stackbase, uint32_t stacksize);
void * STDCALL thread_setup_stack(void *stackbase, thread_start_proc startproc, thread_end_proc returnproc, void *parameter);

THREAD_SNAPSHOT * STDCALL thread_snapshot_create(void);
uint32_t STDCALL thread_snapshot_destroy(THREAD_SNAPSHOT *snapshot);

uint32_t STDCALL messageslot_get_count(void);

uint32_t STDCALL mailslot_get_count(void);

uint32_t STDCALL buffer_get_count(void);

uint32_t STDCALL event_get_count(void);

uint32_t STDCALL timer_get_count(void);

uint32_t STDCALL worker_get_count(void);
uint32_t STDCALL worker_get_priority_count(void);

uint32_t STDCALL tasker_get_count(void);

uint32_t STDCALL list_type_to_string(uint32_t listtype, char *string, uint32_t len);
uint32_t STDCALL queue_type_to_string(uint32_t queuetype, char *string, uint32_t len);
uint32_t STDCALL thread_type_to_string(uint32_t threadtype, char *string, uint32_t len);
uint32_t STDCALL thread_state_to_string(uint32_t threadstate, char *string, uint32_t len);
uint32_t STDCALL thread_priority_to_string(uint32_t threadpriority, char *string, uint32_t len);

/* ============================================================================== */
/* Scheduler Helper Functions */
uint32_t STDCALL scheduler_get_list_flags(uint32_t listtype);
uint32_t STDCALL scheduler_get_queue_flags(uint32_t queuetype);
QUEUE_HANDLE STDCALL scheduler_get_queue_handle(uint32_t cpuid, uint32_t queuetype);
QUEUE_HANDLE STDCALL scheduler_get_queue_handle_ex(uint32_t cpuid, uint32_t priority);
uint32_t STDCALL scheduler_get_thread_count(uint32_t cpuid);
uint32_t STDCALL scheduler_get_thread_quantum(uint32_t cpuid);
THREAD_HANDLE STDCALL scheduler_get_thread_handle(uint32_t cpuid, uint32_t threadtype);
uint32_t STDCALL scheduler_get_priority_mask(uint32_t cpuid);
uint32_t STDCALL scheduler_get_priority_quantum(uint32_t priority);
uint32_t STDCALL scheduler_set_priority_quantum(uint32_t priority, uint32_t quantum);
uint32_t STDCALL scheduler_get_migration_quantum(void);
uint32_t STDCALL scheduler_get_starvation_quantum(uint32_t cpuid);

uint32_t STDCALL scheduler_get_thread_next(void);
uint32_t STDCALL scheduler_get_thread_migration(void);

uint32_t STDCALL scheduler_get_thread_preempt(uint32_t cpuid);
uint32_t STDCALL scheduler_get_thread_allocation(uint32_t cpuid);

uint32_t STDCALL scheduler_migration_to_string(uint32_t migration, char *string, uint32_t len);
uint32_t STDCALL scheduler_preempt_to_string(uint32_t preempt, char *string, uint32_t len);
uint32_t STDCALL scheduler_allocation_to_string(uint32_t allocation, char *string, uint32_t len);

/* ============================================================================== */
/* Timer Helper Functions */
uint32_t STDCALL timer_get_list_flags(void);
uint32_t STDCALL timer_get_messageslot_flags(void);

/* ============================================================================== */
/* Worker Helper Functions */
uint32_t STDCALL worker_get_messageslot_flags(void);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_THREADS_H