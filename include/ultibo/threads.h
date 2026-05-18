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

/** Thread specific constants */

/** Lock constants */
#define LOCK_FLAG_NONE	0x00000000
#define LOCK_FLAG_IRQ	0x00000001
#define LOCK_FLAG_FIQ	0x00000002
#define LOCK_FLAG_IRQFIQ	0x00000004

/** Spin constants */
#define SPIN_SIGNATURE	0x0FEC3B82

/** Spin state constants */
#define SPIN_STATE_UNLOCKED	0
#define SPIN_STATE_LOCKED	1

/** Mutex constants */
#define MUTEX_SIGNATURE	0x1C5D7FA4

/** Mutex state constants */
#define MUTEX_STATE_UNLOCKED	0
#define MUTEX_STATE_LOCKED	1

/** Mutex flags constants */
#define MUTEX_FLAG_NONE	0x00000000
#define MUTEX_FLAG_RECURSIVE	0x00000001 ///< Mutex can be locked multiple times by the same thread if set (Must be unlocked the same number of times)
#define MUTEX_FLAG_ERRORCHECK	0x00000002 ///< Mutex will perform a deadlock check if set, will return with an error if already owned by the same thread (and not recursive)

/** Critical Section constants */
#define CRITICAL_SECTION_SIGNATURE	0x25F3AE01

/** Critical Section state constants */
#define CRITICAL_SECTION_STATE_UNLOCKED	0
#define CRITICAL_SECTION_STATE_LOCKED	1

/** Semaphore constants */
#define SEMAPHORE_SIGNATURE	0x390A1EB4

/** Semaphore flag constants */
#define SEMAPHORE_FLAG_NONE	LOCK_FLAG_NONE
#define SEMAPHORE_FLAG_IRQ	LOCK_FLAG_IRQ
#define SEMAPHORE_FLAG_FIQ	LOCK_FLAG_FIQ
#define SEMAPHORE_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ

/** Synchronizer constants */
#define SYNCHRONIZER_SIGNATURE	0xC5D081FB

/** Synchronizer state constants */
#define SYNCHRONIZER_STATE_UNLOCKED	0
#define SYNCHRONIZER_STATE_READER_LOCKED	1
#define SYNCHRONIZER_STATE_WRITER_LOCKED	2

/** Synchronizer flag constants */
#define SYNCHRONIZER_FLAG_NONE	0x00000000
#define SYNCHRONIZER_FLAG_READ_PRIORITY	0x00000001 ///< Synchronizer prioritises readers over writers
#define SYNCHRONIZER_FLAG_WRITE_PRIORITY	0x00000002 ///< Synchronizer prioritises writers over readers

/** Condition constants */
#define CONDITION_SIGNATURE	0xD14D3C0A

/** Condition flag constants */
#define CONDITION_FLAG_NONE	0x00000000

/** Condition lock flag constants */
#define CONDITION_LOCK_FLAG_NONE	0x00000000
#define CONDITION_LOCK_FLAG_WRITER	0x00000001 ///< Condition should release and acquire the writer lock on a Synchronizer when ConditionWaitSynchronizer is called (otherwise release and acquire the reader lock)

/** Completion constants */
#define COMPLETION_SIGNATURE	0xFCE24CA1

/** Completion state constants */
#define COMPLETION_STATE_RESET	0
#define COMPLETION_STATE_COMPLETE	1

/** Completion flag constants */
#define COMPLETION_FLAG_NONE	LOCK_FLAG_NONE
#define COMPLETION_FLAG_IRQ	LOCK_FLAG_IRQ ///< Disable IRQ during completion operations (Wait/Reset/Complete)
#define COMPLETION_FLAG_FIQ	LOCK_FLAG_FIQ ///< Disable FIQ during completion operations (Wait/Reset/Complete)
#define COMPLETION_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ ///< Disable IRQ and FIQ during completion operations (Wait/Reset/Complete)
#define COMPLETION_FLAG_COUNTED	0x00000008 ///< Use a counted value instead of a single state (Affects behaviour of Wait and Complete)

/** List constants */
#define LIST_SIGNATURE	0x4A98BE2A

/** List type constants */
#define LIST_TYPE_NOT_SPECIFIED	0 ///< A generic thread list without a specific purpose
#define LIST_TYPE_WAIT_SECTION	1 ///< A Critical Section Wait List
#define LIST_TYPE_WAIT_SEMAPHORE	2 ///< A Semaphore Wait List
#define LIST_TYPE_WAIT_SYNCHRONIZER	3 ///< A Synchronizer Wait List
#define LIST_TYPE_WAIT_CONDITION	4 ///< A Condition Wait List
#define LIST_TYPE_WAIT_COMPLETION	5 ///< A Condition Wait List
#define LIST_TYPE_WAIT_EVENT	6 ///< An Event Wait List
#define LIST_TYPE_WAIT_THREAD	7 ///< A Thread Wait List
#define LIST_TYPE_WAIT_MESSAGESLOT	8 ///< A Messageslot Wait List
#define LIST_TYPE_WAIT_OTHER	9 ///< Another type of Wait List (Suitable for passing to ThreadWait/ThreadWaitEx/ThreadWaitMultiple/ThreadRelease)

/** List flag constants */
#define LIST_FLAG_NONE	LOCK_FLAG_NONE
#define LIST_FLAG_IRQ	LOCK_FLAG_IRQ
#define LIST_FLAG_FIQ	LOCK_FLAG_FIQ
#define LIST_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ

/** Queue constants */
#define QUEUE_SIGNATURE	0x57A3BF9E

/** Queue type constants */
#define QUEUE_TYPE_NOT_SPECIFIED	0 ///< A generic thread queue without a specific purpose
#define QUEUE_TYPE_SCHEDULE_SLEEP	1 ///< A Scheduler Sleep Queue
#define QUEUE_TYPE_SCHEDULE_TIMEOUT	2 ///< A Scheduler Timeout Queue
#define QUEUE_TYPE_SCHEDULE_TERMINATION	3 ///< A Scheduler Termination Queue (Threads are placed on termination queue when they exit or are terminated)
#define QUEUE_TYPE_SCHEDULE_NONE	4 ///< A Scheduler No Priority Queue (Only used for IRQ/FIQ threads which are never selected for scheduling)
#define QUEUE_TYPE_SCHEDULE_IDLE	5 ///< A Scheduler Idle Priority Queue
#define QUEUE_TYPE_SCHEDULE_LOWEST	6 ///< A Scheduler Lowest Priority Queue
#define QUEUE_TYPE_SCHEDULE_LOWER	7 ///< A Scheduler Lower Priority Queue
#define QUEUE_TYPE_SCHEDULE_NORMAL	8 ///< A Scheduler Normal Priority Queue
#define QUEUE_TYPE_SCHEDULE_HIGHER	9 ///< A Scheduler Higher Priority Queue
#define QUEUE_TYPE_SCHEDULE_HIGHEST	10 ///< A Scheduler Highest Priority Queue
#define QUEUE_TYPE_SCHEDULE_CRITICAL	11 ///< A Scheduler Critical Priority Queue

/** Queue flag constants */
#define QUEUE_FLAG_NONE	LOCK_FLAG_NONE
#define QUEUE_FLAG_IRQ	LOCK_FLAG_IRQ
#define QUEUE_FLAG_FIQ	LOCK_FLAG_FIQ
#define QUEUE_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ
#define QUEUE_FLAG_DESCENDING	0x00000008
#define QUEUE_FLAG_DELTA	0x00000010

/** Queue key constants */
#define QUEUE_KEY_NONE	(int32_t)0x7FFFFFFF ///< Null key value returned from an empty Queue
#define QUEUE_KEY_MAX	(int32_t)0x7FFFFFFE ///< Max key that can be ordered in a Queue
#define QUEUE_KEY_MIN	(int32_t)0x80000000 ///< Min key that can be ordered in a Queue

/** Thread constants */
#define THREAD_SIGNATURE	0x6C2BA10F

/** Thread type constants */
#define THREAD_TYPE_NORMAL	0 ///< A Normal thread (No special case handling)
#define THREAD_TYPE_IDLE	1 ///< An Idle thread (Used to calculate ultilization and provide an always ready thread)
#define THREAD_TYPE_IRQ	2 ///< An IRQ thread (Used by the IRQ handler during interrupt time)
#define THREAD_TYPE_FIQ	3 ///< An FIQ thread (Used by the FIQ handler during interrupt time)
#define THREAD_TYPE_SWI	4 ///< A Software Interrupt (SWI) thread (Used by the SWI handler during a system call)

/** Thread flag constants */
#define THREAD_FLAG_NONE	0x00000000
#define THREAD_FLAG_PERSIST	0x00000001 ///< If set thread handle will persist until explicitly destroyed (Otherwise destroyed after termination quantum has elapsed)
#define THREAD_FLAG_CANCELLED	0x00000002 ///< Indicates that thread has been cancelled, for support of external thread APIs (eg pThreads)(Not used internally by Ultibo)
#define THREAD_FLAG_CANCEL_DISABLE	0x00000004 ///< Indicates that thread cancellation is disabled for a thread, for support of external thread APIs (eg pThreads)(Not used internally by Ultibo)
#define THREAD_FLAG_CANCEL_ASYNCHRONOUS	0x00000008 ///< Indicates that asynchronous thread cancellation is enabled for a thread, for support of external thread APIs (eg pThreads)(Not used internally by Ultibo)

#define THREAD_FLAG_INTERNAL	THREAD_FLAG_NONE + 0x80000000 ///< Note: Temporary value to avoid warning

/** Thread state constants */
#define THREAD_STATE_RUNNING	1 ///< Thread is currently running
#define THREAD_STATE_READY	2 ///< Thread is on ready queue
#define THREAD_STATE_SLEEP	3 ///< Thread is sleeping
#define THREAD_STATE_SUSPENDED	4 ///< Thread is suspended
#define THREAD_STATE_WAIT	5 ///< Thread is on a wait list
#define THREAD_STATE_WAIT_TIMEOUT	6 ///< Thread is on a wait list with timeout
#define THREAD_STATE_RECEIVE	7 ///< Thread is waiting to receive a message
#define THREAD_STATE_RECEIVE_TIMEOUT	8 ///< Thread is waiting to receive a message with timeout
#define THREAD_STATE_HALTED	9 ///< Thread has been halted (Due to an unhandled exception etc)
#define THREAD_STATE_TERMINATED	10 ///< Thread has been terminated
/// To Do THREAD_STATE_SEND / THREAD_STATE_SEND_TIMEOUT ?  //Who would wake them up ? //Timeout is ok, but what about send only ?

/** Thread priority constants */
#define THREAD_PRIORITY_NONE	0 ///< Only used for IRQ/FIQ threads which are never selected for scheduling
#define THREAD_PRIORITY_IDLE	1
#define THREAD_PRIORITY_LOWEST	2
#define THREAD_PRIORITY_LOWER	3
#define THREAD_PRIORITY_NORMAL	4
#define THREAD_PRIORITY_HIGHER	5
#define THREAD_PRIORITY_HIGHEST	6
#define THREAD_PRIORITY_CRITICAL	7

#define THREAD_PRIORITY_DEFAULT	THREAD_PRIORITY_NORMAL ///< Default thread priority
#define THREAD_PRIORITY_MINIMUM	THREAD_PRIORITY_IDLE ///< Minimum thread priority
#define THREAD_PRIORITY_MAXIMUM	THREAD_PRIORITY_CRITICAL ///< Maximum thread priority
#define THREAD_PRIORITY_COUNT	THREAD_PRIORITY_MAXIMUM + 1 ///< Number of thread priority levels

/** Additional priority aliases for compatibility */
#define THREAD_PRIORITY_BELOW_NORMAL	THREAD_PRIORITY_LOWER
#define THREAD_PRIORITY_ABOVE_NORMAL	THREAD_PRIORITY_HIGHER
#define THREAD_PRIORITY_TIME_CRITICAL	THREAD_PRIORITY_CRITICAL

/** Thread name constants */
#define THREAD_NAME_LENGTH	SIZE_64 ///< Length of thread name

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

/** Thread priority constants */
#define TIMER_THREAD_PRIORITY	THREAD_PRIORITY_NORMAL
#define WORKER_THREAD_PRIORITY	THREAD_PRIORITY_NORMAL
#define TIMER_PRIORITY_THREAD_PRIORITY	THREAD_PRIORITY_HIGHEST
#define WORKER_PRIORITY_THREAD_PRIORITY	THREAD_PRIORITY_HIGHER

/** Thread create constants */
#define THREAD_CREATE_NONE	0x00000000
#define THREAD_CREATE_SUSPENDED	0x00000004

/** Thread TLS constants */
#define THREAD_TLS_FREE	0x00000000
#define THREAD_TLS_USED	0x00000001
#define THREAD_TLS_INVALID	0xFFFFFFFF

#define THREAD_TLS_MAXIMUM	SIZE_64 ///< The maximum number TLS index slots available

/** Thread TLS flag constants */
#define THREAD_TLS_FLAG_NONE	0x00000000
#define THREAD_TLS_FLAG_FREE	0x00000001 ///< If set then pointer in thread TLS index will be freed on ThreadReleaseTlsIndex or ThreadDestroy

/** Thread wait constants */
#define THREAD_LISTS_MAXIMUM	SIZE_64 ///< Maximum number of lists a thread can wait on at the same time

/** Messageslot constants */
#define MESSAGESLOT_SIGNATURE	0xB631CE4B

/** Messageslot flag constants */
#define MESSAGESLOT_FLAG_NONE	LOCK_FLAG_NONE
#define MESSAGESLOT_FLAG_IRQ	LOCK_FLAG_IRQ
#define MESSAGESLOT_FLAG_FIQ	LOCK_FLAG_FIQ
#define MESSAGESLOT_FLAG_IRQFIQ	LOCK_FLAG_IRQFIQ

/** Mailslot constants */
#define MAILSLOT_SIGNATURE	0x7A409BF3

/** Buffer constants */
#define BUFFER_SIGNATURE	0x830BEA71

/** Buffer flag constants */
#define BUFFER_FLAG_NONE	0x00000000
#define BUFFER_FLAG_SHARED	0x00000001 ///< If set the buffer memory (Not the buffer entry itself) is allocated from shared memory

/** Event constants */
#define EVENT_SIGNATURE	0x903BA69D

/** Event state constants */
#define EVENT_STATE_UNSIGNALED	0
#define EVENT_STATE_SIGNALED	1

/** Event flag constants */
#define EVENT_FLAG_NONE	0x00000000
#define EVENT_FLAG_INITIAL_STATE	0x00000001
#define EVENT_FLAG_MANUAL_RESET	0x00000002

/** Timer constants */
#define TIMER_SIGNATURE	0xAB7E07FB

/** Timer state constants */
#define TIMER_STATE_DISABLED	0
#define TIMER_STATE_ENABLED	1

/** Timer flag constants */
#define TIMER_FLAG_NONE	0x00000000
#define TIMER_FLAG_RESCHEDULE	0x00000001 ///< Timer should be rescheduled each time the event completes
#define TIMER_FLAG_IMMEDIATE	0x00000002 ///< Timer event should be executed immediately and then each interval milliseconds
#define TIMER_FLAG_WORKER	0x00000004 ///< Timer event should be executed by a worker thread instead of a timer thread
#define TIMER_FLAG_PRIORITY	0x00000008 ///< Timer event should be executed by a priority timer thread

/** Timer key constants */
#define TIMER_KEY_NONE	(int32_t)0x7FFFFFFF ///< Null key value returned from an empty Timer list
#define TIMER_KEY_MAX	(int32_t)0x7FFFFFFE ///< Max key that can be ordered in a Timer list
#define TIMER_KEY_MIN	(int32_t)0x80000000 ///< Min key that can be ordered in a Timer list

/** Worker constants */
#define WORKER_SIGNATURE	0xEF6A901B

/** Worker flag constants */
#define WORKER_FLAG_NONE	0x00000000
#define WORKER_FLAG_RESCHEDULE	0x00000001 ///< Worker task should be rescheduled each time the task completes
#define WORKER_FLAG_IMMEDIATE	0x00000002 ///< Worker task should be executed immediately and then each interval milliseconds
#define WORKER_FLAG_CANCEL	0x00000004 ///< Internal flag to indicate the worker task should be cancelled next time the interval expires
#define WORKER_FLAG_NOFREE	0x00000008 ///< Internal flag to tell worker execute not to free the worker request when it is completed
#define WORKER_FLAG_TERMINATE	0x00000010 ///< Internal flag to tell worker execute to terminate the worker thread
#define WORKER_FLAG_IRQ	0x00000020 ///< Internal flag to tell worker execute to free IRQ memory when the request is completed
#define WORKER_FLAG_FIQ	0x00000040 ///< Internal flag to tell worker execute to free FIQ memory when the request is completed
#define WORKER_FLAG_PRIORITY	0x00000080 ///< Worker task should be executed by a priority worker thread

#define WORKER_FLAG_INTERNAL	WORKER_FLAG_CANCEL | WORKER_FLAG_NOFREE | WORKER_FLAG_TERMINATE | WORKER_FLAG_IRQ | WORKER_FLAG_FIQ ///< Internal only flags

#define WORKER_FLAG_EXCLUDED_IRQ	WORKER_FLAG_RESCHEDULE | WORKER_FLAG_IMMEDIATE ///< Excluded flags
#define WORKER_FLAG_EXCLUDED_FIQ	WORKER_FLAG_RESCHEDULE | WORKER_FLAG_IMMEDIATE ///< Excluded flags

/** Tasker task constants */
#define TASKER_TASK_THREADSENDMESSAGE	1 ///< Perform a ThreadSendMessage() function using the tasker list
#define TASKER_TASK_MESSAGESLOTSEND	2 ///< Perform a MessageslotSend() function using the tasker list
#define TASKER_TASK_SEMAPHORESIGNAL	3 ///< Perform a SemaphoreSignal() function using the tasker list
#define TASKER_TASK_COMPLETIONRESET	4 ///< Perform a CompletionReset() function using the tasker list
#define TASKER_TASK_COMPLETIONCOMPLETE	5 ///< Perform a CompletionComplete() or CompletionCompleteAll() function using the tasker list

/** Scheduler migration constants */
#define SCHEDULER_MIGRATION_DISABLED	0
#define SCHEDULER_MIGRATION_ENABLED	1

/** Scheduler preempt constants */
#define SCHEDULER_PREEMPT_DISABLED	0
#define SCHEDULER_PREEMPT_ENABLED	1

/** Scheduler allocation constants */
#define SCHEDULER_ALLOCATION_DISABLED	0
#define SCHEDULER_ALLOCATION_ENABLED	1

/** Scheduler mask constants */
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

/** Scheduler quantum constants */
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

/** Thread specific types */

/** See also Handle types in GlobalConst */

/** Spin entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _SPIN_ENTRY SPIN_ENTRY;
struct _SPIN_ENTRY
{
	// Spin Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t state; ///< State of the lock (Locked/Unlocked)
	uint32_t mask; ///< IRQ/FIQ Mask for Save/Restore
	THREAD_HANDLE owner; ///< Currently owning thread (or INVALID_HANDLE_VALUE if not locked)
	// Internal Properties
	SPIN_ENTRY *prev; ///< Previous entry in Spin table
	SPIN_ENTRY *next; ///< Next entry in Spin table
	// Statistics Properties
};

/** Mutex entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _MUTEX_ENTRY MUTEX_ENTRY;
struct _MUTEX_ENTRY
{
	// Mutex Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t state; ///< State of the lock (Locked/Unlocked)
	THREAD_HANDLE owner; ///< Currently owning thread (or INVALID_HANDLE_VALUE if not locked)
	thread_yield_proc yield; ///< Yield function to call while waiting
	uint32_t count; ///< Count of lock recursions (only if Flags includes MUTEX_FLAG_RECURSIVE)
	uint32_t flags; ///< Mutex Flags (eg MUTEX_FLAG_RECURSIVE)
	uint32_t spincount; ///< Number of times to spin wait for lock before Yield is called (Always 0 if SCHEDULER_CPU_COUNT = 1)
	// Internal Properties
	MUTEX_ENTRY *prev; ///< Previous entry in Mutex table
	MUTEX_ENTRY *next; ///< Next entry in Mutex table
	// Statistics Properties
};

/** Critical Section entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _CRITICAL_SECTION_ENTRY CRITICAL_SECTION_ENTRY;
struct _CRITICAL_SECTION_ENTRY
{
	// Critical Section Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t state; ///< State of the lock (Locked/Unlocked)
	uint32_t count; ///< Count of lock recursions
	THREAD_HANDLE owner; ///< Currently owning thread (or INVALID_HANDLE_VALUE if not locked)
	uint32_t spincount; ///< Number of times to spin wait for lock before Wait is called (Always 0 if SCHEDULER_CPU_COUNT = 1)
	SPIN_HANDLE lock; ///< Critical Section Lock
	LIST_HANDLE list; ///< List of threads waiting on this CriticalSection (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; ///< Wait function to call to wait on the CriticalSection if it is already locked
	thread_wait_ex_proc waitex; ///< Wait function to call to wait with timeout on the CriticalSection if it is already locked
	thread_release_proc release; ///< Release function to call if any threads are waiting when CriticalSection is unlocked
	thread_abandon_proc abandon; ///< Abandon function to call if any threads are waiting when CriticalSection is destroyed
	// Internal Properties
	CRITICAL_SECTION_ENTRY *prev; ///< Previous entry in CriticalSection table
	CRITICAL_SECTION_ENTRY *next; ///< Next entry in CriticalSection table
	// Statistics Properties
};

/** Semaphore entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _SEMAPHORE_ENTRY SEMAPHORE_ENTRY;
struct _SEMAPHORE_ENTRY
{
	// Semaphore Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t count; ///< Count for this Semaphore (Can be negative when Threads are waiting)
	uint32_t maximum; ///< Maximum count for this Semaphore
	uint32_t flags; ///< Semaphore Flags (eg SEMAPHORE_FLAG_IRQ)
	SPIN_HANDLE lock; ///< Semaphore Lock
	LIST_HANDLE list; ///< List of threads waiting on this Semaphore (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; ///< Wait function to call to wait on the Semaphore if the count is equal to zero on SemaphoreWait
	thread_wait_ex_proc waitex; ///< Wait function to call to wait with timeout on the Semaphore if the count is equal to zero on SemaphoreWait
	thread_release_proc release; ///< Release function to call if any threads are waiting on SemaphoreSignal
	thread_abandon_proc abandon; ///< Abandon function to call if any threads are waiting when SemaphoreSignal is destroyed
	// Internal Properties
	SEMAPHORE_ENTRY *prev; ///< Previous entry in Semaphore table
	SEMAPHORE_ENTRY *next; ///< Next entry in Semaphore table
	// Statistics Properties
};

/** Synchronizer entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _SYNCHRONIZER_ENTRY SYNCHRONIZER_ENTRY;
struct _SYNCHRONIZER_ENTRY
{
	// Synchronizer Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t state; ///< State of the lock (Locked/Unlocked)
	SPIN_HANDLE lock; ///< Synchronizer Lock
	uint32_t readercount; ///< Count of current reader locks
	uint32_t writercount; ///< Count of current writer lock recursions
	THREAD_HANDLE readerlast; ///< Last thread to acquire reader lock (or INVALID_HANDLE_VALUE if no reader)
	THREAD_HANDLE writerowner; ///< Currently owning writer thread (or INVALID_HANDLE_VALUE if no writer)
	LIST_HANDLE readerlist; ///< List of reader threads waiting on this Synchronizer (or INVALID_HANDLE_VALUE if never used)
	LIST_HANDLE writerlist; ///< List of writer threads waiting on this Synchronizer (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; ///< Wait function to call to wait on the Synchronizer if it is already locked
	thread_wait_ex_proc waitex; ///< Wait function to call to wait with timeout on the Synchronizer if it is already locked
	thread_release_proc release; ///< Release function to call if any threads are waiting when Synchronizer is unlocked
	thread_abandon_proc abandon; ///< Abandon function to call if any threads are waiting when Synchronizer is destroyed
	// Internal Properties
	SYNCHRONIZER_ENTRY *prev; ///< Previous entry in Synchronizer table
	SYNCHRONIZER_ENTRY *next; ///< Next entry in Synchronizer table
	// Statistics Properties
};

/** Condition entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _CONDITION_ENTRY CONDITION_ENTRY;
struct _CONDITION_ENTRY
{
	// Condition Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t flags; ///< Condition Flags (eg CONDITION_FLAG_NONE)
	SPIN_HANDLE lock; ///< Condition Lock
	LIST_HANDLE list; ///< List of threads waiting on this Condition (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; ///< Wait function to call to wait on the Condition
	thread_wait_ex_proc waitex; ///< Wait function to call to wait with timeout on the Condition
	thread_release_proc release; ///< Release function to call if any threads are waiting when Condition is woken
	thread_abandon_proc abandon; ///< Abandon function to call if any threads are waiting when Condition is destroyed
	// Internal Properties
	CONDITION_ENTRY *prev; ///< Previous entry in Condition table
	CONDITION_ENTRY *next; ///< Next entry in Condition table
	// Statistics Properties
};

/** Completion entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _COMPLETION_ENTRY COMPLETION_ENTRY;
struct _COMPLETION_ENTRY
{
	// Completion Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t state; ///< State of the completion (Reset/Complete)
	uint32_t count; ///< Count of the completion (Only applicable if COMPLETION_FLAG_COUNTED)
	uint32_t flags; ///< Completion Flags (eg COMPLETION_FLAG_IRQ)
	SPIN_HANDLE lock; ///< Completion Lock
	LIST_HANDLE list; ///< List of threads waiting on this Completion (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; ///< Wait function to call to wait on the Completion
	thread_wait_ex_proc waitex; ///< Wait function to call to wait with timeout on the Completion
	thread_release_proc release; ///< Release function to call if any threads are waiting when Completion is completed
	thread_abandon_proc abandon; ///< Abandon function to call if any threads are waiting when Completion is destroyed
	// Internal Properties
	COMPLETION_ENTRY *prev; ///< Previous entry in Completion table
	COMPLETION_ENTRY *next; ///< Next entry in Completion table
	// Statistics Properties
};

/** List entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _LIST_ELEMENT LIST_ELEMENT;
typedef struct _LIST_ENTRY LIST_ENTRY;
struct _LIST_ENTRY
{
	// List Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t listtype; ///< Type of this List (eg LIST_TYPE_WAIT_SECTION)
	uint32_t count; ///< Count of items currently in this List
	uint32_t flags; ///< List Flags (eg LIST_FLAG_IRQ)
	SPIN_HANDLE lock; ///< List Lock
	LIST_ELEMENT *first; ///< First element in List
	LIST_ELEMENT *last; ///< Last element in List
	// Internal Properties
	LIST_ENTRY *prev; ///< Previous entry in List table
	LIST_ENTRY *next; ///< Next entry in List table
	// Statistics Properties
};

/** List element */
struct _LIST_ELEMENT
{
	THREAD_HANDLE thread; ///< The thread referenced by this List element
	LIST_ELEMENT *prev; ///< Previous element in List
	LIST_ELEMENT *next; ///< Next element in List
};

/** List handles */
typedef LIST_HANDLE LIST_HANDLES[THREAD_LISTS_MAXIMUM];

/** Queue entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _QUEUE_ELEMENT QUEUE_ELEMENT;
typedef struct _QUEUE_ENTRY QUEUE_ENTRY;
struct _QUEUE_ENTRY
{
	// Queue Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t queuetype; ///< Type of this Queue (eg QUEUE_TYPE_SCHEDULE_IDLE)
	uint32_t count; ///< Count of items currently in this Queue
	uint32_t flags; ///< Queue Flags (eg QUEUE_FLAG_IRQ)
	SPIN_HANDLE lock; ///< Queue Lock
	QUEUE_ELEMENT *first; ///< First element in Queue
	QUEUE_ELEMENT *last; ///< Last element in Queue
	// Internal Properties
	QUEUE_ENTRY *prev; ///< Previous entry in Queue table
	QUEUE_ENTRY *next; ///< Next entry in Queue table
	// Statistics Properties
};

/** Queue element */
struct _QUEUE_ELEMENT
{
	int key; ///< Ordering key for Queue
	THREAD_HANDLE thread; ///< The thread referenced by this Queue element
	QUEUE_ELEMENT *prev; ///< Previous element in Queue
	QUEUE_ELEMENT *next; ///< Next element in Queue
};

/** Message list */
typedef struct _THREAD_MESSAGE THREAD_MESSAGE;
typedef struct _MESSAGE_LIST MESSAGE_LIST;
struct _MESSAGE_LIST
{
	// Header Properties
	uint32_t maximum; ///< Maximum number of messages in list
	uint32_t count; ///< Current number of messages in list
	uint32_t start; ///< First message available in list
	// Internal Properties
	THREAD_MESSAGE *list; ///< Message list
	// Statistics Properties
};

/** Message */
struct _THREAD_MESSAGE
{
	size_t msg;
	size_t wparam;
	ssize_t lparam;
	uint32_t time;
};

/** Thread entry */
/** Note: Changes to this structure need to be accounted for in platform specific handlers */
typedef struct _THREAD_ENTRY THREAD_ENTRY;
struct _THREAD_ENTRY
{
	// Thread Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t state; ///< State of the Thread (eg THREAD_STATE_RUNNING)
	uint32_t flags; ///< Flags of the Thread (eg THREAD_FLAG_PERSIST)
	uint32_t priority; ///< Priority of the Thread (eg THREAD_PRIORITY_NORMAL)
	uint32_t affinity; ///< CPU Affinity mask of the Thread
	void *stackbase; ///< Base (Top) of the thread stack
	uint32_t stacksize; ///< Stack length in bytes
	char name[THREAD_NAME_LENGTH]; ///< The name of the Thread
	SPIN_HANDLE lock; ///< Thread Lock
	THREAD_HANDLE parent; ///< Handle of the parent thread
	MESSAGE_LIST messages; ///< Messages sent to this thread
	void *tlspointer; ///< Thread Local Storage Memory (RTL ThreadVars)
	void *tlstable[THREAD_TLS_MAXIMUM]; ///< Thread Local Storage Index Pointers (for ThreadGetTlsValue/ThreadSetTlsValue) //To Do //Test
	uint32_t tlsflags[THREAD_TLS_MAXIMUM]; ///< Thread Local Storage Index Flags (eg THREAD_TLS_FLAG_FREE)
	uint32_t exitcode; ///< Thread Exit Code
	uint32_t lasterror; ///< Thread Last Error
	LCID locale; ///< Thread Locale
	// Internal Properties
	uint32_t currentcpu; ///< Saved current CPU from last ContextSwitch
	void *stackpointer; ///< Saved current stack pointer from last ContextSwitch
	uint32_t targetcpu; ///< Target CPU of the Thread for next ContextSwitch
	uint32_t targetpriority; ///< Target Priority of the Thread for next ContextSwitch (eg THREAD_PRIORITY_NORMAL)
	LIST_HANDLE list; ///< List of threads waiting on this thread (or INVALID_HANDLE_VALUE if never used)
	LIST_HANDLE waitlist; ///< The wait list this thread is currently in (or INVALID_HANDLE_VALUE)
	LIST_HANDLES *waitlists; ///< The wait lists this thread is currently in if doing a multiple wait (or nil)
	uint32_t waitresult; ///< The result code for the last wait with timeout (eg WAIT_TIMEOUT)
	uint32_t receiveresult; ///< The result code for the last receive with timeout (eg WAIT_TIMEOUT)
	QUEUE_HANDLE schedulequeue; ///< The scheduler queue this thread is currently in  (or INVALID_HANDLE_VALUE)
	LIST_ELEMENT listelement; ///< List element for this thread when in a Wait List
	QUEUE_ELEMENT queueelement; ///< Queue element for this thread when in a Schedule Queue
	THREAD_ENTRY *prev; ///< Previous entry in Thread table
	THREAD_ENTRY *next; ///< Next entry in Thread table
	// Statistics Properties
	int64_t createtime; ///< The time when this thread was created
	int64_t exittime; ///< The time when this thread exited or was terminated
	int64_t kerneltime; ///< The total amount of time this thread has been in the running state (ie CPU time consumed)
	int64_t switchcount; ///< The number of times this thread has been selected to run by a context switch
};

/** Thread snapshot */
typedef struct _THREAD_SNAPSHOT THREAD_SNAPSHOT;
struct _THREAD_SNAPSHOT
{
	// Snapshot Properties
	THREAD_HANDLE handle; ///< Handle of the thread
	uint32_t state; ///< State of the Thread (eg THREAD_STATE_RUNNING)
	uint32_t flags; ///< Flags of the Thread (eg THREAD_FLAG_PERSIST)
	uint32_t cpu; ///< CPU from last ContextSwitch
	uint32_t priority; ///< Priority of the Thread (eg THREAD_PRIORITY_NORMAL)
	uint32_t affinity; ///< CPU Affinity mask of the Thread
	void *stackbase; ///< Base (Top) of the thread stack
	uint32_t stacksize; ///< Stack length in bytes
	void *stackpointer; ///< Stack pointer from last ContextSwitch
	char name[THREAD_NAME_LENGTH]; ///< The name of the Thread
	THREAD_HANDLE parent; ///< Handle of the parent thread
	uint32_t exitcode; ///< Thread Exit Code
	uint32_t lasterror; ///< Thread Last Error
	LCID locale; ///< Thread Locale
	uint32_t targetcpu; ///< Target CPU of the Thread for next ContextSwitch
	uint32_t targetpriority; ///< Target Priority of the Thread for next ContextSwitch (eg THREAD_PRIORITY_NORMAL)
	int64_t createtime; ///< The time when this thread was created
	int64_t exittime; ///< The time when this thread exited or was terminated
	int64_t kerneltime; ///< The total amount of time this thread has been in the running state (ie CPU time consumed)
	int64_t switchcount; ///< The number of times this thread has been selected to run by a context switch
	// Internal Properties
	THREAD_SNAPSHOT *next; ///< Next entry in Thread snapshot
};

/** Messageslot entry */
typedef struct _MESSAGESLOT_ENTRY MESSAGESLOT_ENTRY;
struct _MESSAGESLOT_ENTRY
{
	// Messageslot Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t flags; ///< Messageslot Flags (eg MESSAGESLOT_FLAG_IRQ)
	SPIN_HANDLE lock; ///< Messageslot Lock
	LIST_HANDLE list; ///< List of threads waiting on this Messageslot (or INVALID_HANDLE_VALUE if never used)
	MESSAGE_LIST messages; ///< Messageslot message queue
	thread_wait_proc wait; ///< Wait function to call to wait on the Messageslot if there are no messages
	thread_wait_ex_proc waitex; ///< Wait function to call to wait with timeout on the Messageslot if there are no messages
	thread_release_proc release; ///< Release function to call if any threads are waiting when a message is sent
	thread_abandon_proc abandon; ///< Abandon function to call if any threads are waiting when Messageslot is destroyed
	// Internal Properties
	MESSAGESLOT_ENTRY *prev; ///< Previous entry in Messageslot table
	MESSAGESLOT_ENTRY *next; ///< Next entry in Messageslot table
	// Statistics Properties
};

/** Mailslot entry */
typedef struct _MAILSLOT_ENTRY MAILSLOT_ENTRY;
struct _MAILSLOT_ENTRY
{
	// Mailslot Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t maximum; ///< Maximum number of messages in Mailslot
	uint32_t count; ///< Current number of messages in Mailslot
	uint32_t start; ///< First message available in Mailslot
	SPIN_HANDLE lock; ///< Mailslot Lock
	SEMAPHORE_HANDLE sender; ///< Mailslot send Semaphore
	SEMAPHORE_HANDLE receiver; ///< Mailslot receive Semaphore
	ssize_t *messages; ///< Mailslot message queue
	// Internal Properties
	MAILSLOT_ENTRY *prev; ///< Previous entry in Mailslot table
	MAILSLOT_ENTRY *next; ///< Next entry in Mailslot table
	// Statistics Properties
};

/** Buffer entry */
typedef struct _BUFFER_ITEM BUFFER_ITEM;
typedef struct _BUFFER_ENTRY BUFFER_ENTRY;
struct _BUFFER_ENTRY
{
	// Buffer Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t size; ///< Size of each buffer
	uint32_t count; ///< Number of buffers
	uint32_t flags; ///< Buffer Flags (eg BUFFER_FLAG_SHARED)
	SPIN_HANDLE lock; ///< Buffer Lock
	SEMAPHORE_HANDLE available; ///< Buffer available Semaphore
	BUFFER_ITEM *buffers; ///< Buffer list
	// Internal Properties
	BUFFER_ENTRY *prev; ///< Previous entry in Buffer table
	BUFFER_ENTRY *next; ///< Next entry in Buffer table
	BUFFER_ITEM *first; ///< First available buffer item
	// Statistics Properties
};

/** Buffer item */
struct _BUFFER_ITEM
{
	BUFFER_HANDLE parent; ///< Handle of Buffer owning this item
	BUFFER_ITEM *next; ///< Next item in list
	void *buffer; ///< Pointer to item data
	uint32_t reserved; ///< Align to 16 bytes
};

/** Event entry */
typedef struct _EVENT_ENTRY EVENT_ENTRY;
struct _EVENT_ENTRY
{
	// Event Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t state; ///< State of the event (Signaled/Unsignaled)
	uint32_t flags; ///< Event Flags (eg EVENT_FLAG_MANUAL)
	SPIN_HANDLE lock; ///< Event Lock
	LIST_HANDLE list; ///< List of threads waiting on this Event (or INVALID_HANDLE_VALUE if never used)
	thread_wait_proc wait; ///< Wait function to call to wait on the Event if it is not Signaled
	thread_wait_ex_proc waitex; ///< Wait function to call to wait with timeout on the Event if it is not Signaled
	thread_release_proc release; ///< Release function to call if any threads are waiting when Event is Signaled
	thread_abandon_proc abandon; ///< Abandon function to call if any threads are waiting when Event is destroyed
	// Internal Properties
	EVENT_ENTRY *prev; ///< Previous entry in Event table
	EVENT_ENTRY *next; ///< Next entry in Event table
	// Statistics Properties
};

/** Timer list */
typedef struct _TIMER_ITEM TIMER_ITEM;
typedef struct _TIMER_LIST TIMER_LIST;
struct _TIMER_LIST
{
	// List Properties
	uint32_t count; ///< Count of items currently in the Timer list
	uint32_t flags; ///< Timer list Flags (eg LOCK_FLAG_IRQ)
	SPIN_HANDLE lock; ///< Timer list Lock
	TIMER_ITEM *first; ///< First item in Timer list
	TIMER_ITEM *last; ///< Last item in Timer list
	// Internal Properties
	// Statistics Properties
};

/** Timer item */
struct _TIMER_ITEM
{
	int key; ///< Ordering key for Timer list
	TIMER_HANDLE timer; ///< The timer referenced by this Timer list item
	TIMER_ITEM *prev; ///< Previous item in Timer list
	TIMER_ITEM *next; ///< Next item in Timer list
};

/** Timer entry */
typedef struct _TIMER_ENTRY TIMER_ENTRY;
struct _TIMER_ENTRY
{
	// Timer Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t interval; ///< Interval for timer (Milliseconds)
	uint32_t state; ///< State of the timer (Enabled/Disabled)
	uint32_t flags; ///< Timer Flags (eg TIMER_FLAG_RESCHEDULE)
	SPIN_HANDLE lock; ///< Timer Lock
	timer_event_proc event; ///< Function to call when timer triggers
	void *data; ///< Data to pass to function when timer triggers
	// Internal Properties
	TIMER_LIST *timerlist; ///< The timer list this timer is currently in (or nil)
	TIMER_ITEM timeritem; ///< Timer list item for this timer when in a Timer list
	TIMER_ENTRY *prev; ///< Previous entry in Timer table
	TIMER_ENTRY *next; ///< Next entry in Timer table
	// Statistics Properties
};

/** Worker request */
typedef struct _WORKER_REQUEST WORKER_REQUEST;
struct _WORKER_REQUEST
{
	// Worker Properties
	uint32_t signature; ///< Signature for entry validation
	uint32_t interval; ///< Interval for worker (Milliseconds)
	uint32_t flags; ///< Worker Flags (eg WORKER_FLAG_RESCHEDULE)
	SPIN_HANDLE lock; ///< Worker Lock (or INVALID_HANDLE_VALUE if Interval is 0 and Flags is not WORKER_FLAG_RESCHEDULE)
	TIMER_HANDLE timer; ///< Worker Timer (or INVALID_HANDLE_VALUE if Interval is 0)
	worker_task_proc task; ///< Task to call by worker
	void *data; ///< Data to pass to task
	worker_cb callback; ///< Callback when task is completed
};

/** Tasker list */
typedef struct _TASKER_TASK TASKER_TASK;
typedef struct _TASKER_LIST TASKER_LIST;
struct _TASKER_LIST
{
	// List Properties
	uint32_t count; ///< Count of tasks currently in the Tasker list
	SPIN_HANDLE lock; ///< Tasker list Lock
	TASKER_TASK *first; ///< First task in Tasker list
	TASKER_TASK *last; ///< Last task in Tasker list
	// Internal Properties
	// Statistics Properties
};

/** Tasker task */
struct _TASKER_TASK
{
	uint32_t task; ///< The task to be performed
	TASKER_TASK *prev; ///< Previous task in Tasker list
	TASKER_TASK *next; ///< Next task in Tasker list
};

/** Tasker ThreadSendMessage task */
typedef struct _TASKER_THREAD_SEND_MESSAGE TASKER_THREAD_SEND_MESSAGE;
struct _TASKER_THREAD_SEND_MESSAGE
{
	uint32_t task; ///< The task to be performed
	TASKER_TASK *prev; ///< Previous task in Tasker list
	TASKER_TASK *next; ///< Next task in Tasker list
	// Internal Properties
	THREAD_HANDLE thread; ///< Handle of the thread to send a message to
	THREAD_MESSAGE message; ///< Message to send to the thread
};

/** Tasker MessageslotSend task */
typedef struct _TASKER_MESSAGESLOT_SEND TASKER_MESSAGESLOT_SEND;
struct _TASKER_MESSAGESLOT_SEND
{
	uint32_t task; ///< The task to be performed
	TASKER_TASK *prev; ///< Previous task in Tasker list
	TASKER_TASK *next; ///< Next task in Tasker list
	// Internal Properties
	MESSAGESLOT_HANDLE messageslot; ///< Handle of the message slot to send to
	THREAD_MESSAGE message; ///< Message to be sent
};

/** Tasker SemaphoreSignal task */
typedef struct _TASKER_SEMAPHORE_SIGNAL TASKER_SEMAPHORE_SIGNAL;
struct _TASKER_SEMAPHORE_SIGNAL
{
	uint32_t task; ///< The task to be performed
	TASKER_TASK *prev; ///< Previous task in Tasker list
	TASKER_TASK *next; ///< Next task in Tasker list
	// Internal Properties
	SEMAPHORE_HANDLE semaphore; ///< Handle of the semaphore to signal
	uint32_t count; ///< The count to be signalled
};

/** Tasker CompletionReset task */
typedef struct _TASKER_SEMAPHORE_RESET TASKER_SEMAPHORE_RESET;
struct _TASKER_SEMAPHORE_RESET
{
	uint32_t task; ///< The task to be performed
	TASKER_TASK *prev; ///< Previous task in Tasker list
	TASKER_TASK *next; ///< Next task in Tasker list
	// Internal Properties
	COMPLETION_HANDLE completion; ///< Handle of the completion to reset
};

/** Tasker CompletionComplete task */
typedef struct _TASKER_SEMAPHORE_COMPLETE TASKER_SEMAPHORE_COMPLETE;
struct _TASKER_SEMAPHORE_COMPLETE
{
	uint32_t task; ///< The task to be performed
	TASKER_TASK *prev; ///< Previous task in Tasker list
	TASKER_TASK *next; ///< Next task in Tasker list
	// Internal Properties
	COMPLETION_HANDLE completion; ///< Handle of the completion to complete or complete all
	LONGBOOL all; ///< False for complete, True for complete all
};

/** Prototypes for Thread Start/End Handlers */
typedef ssize_t STDCALL (*thread_start_proc)(void *parameter);
typedef void STDCALL (*thread_end_proc)(uint32_t exitcode);

/** Spin Functions */

/**
 * @brief Create and insert a new Spin entry
 * @return Handle of new Spin entry or INVALID_HANDLE_VALUE if entry could not be created
 */
SPIN_HANDLE STDCALL spin_create(void);

/**
 * @brief Create and insert a new Spin entry
 * @param InitialOwner If true set the state of the spin to locked and the owner to the current thread
 * @return Handle of new Spin entry or INVALID_HANDLE_VALUE if entry could not be created
 */
SPIN_HANDLE STDCALL spin_create_ex(BOOL initialowner);

/**
 * @brief Destroy and remove an existing Spin entry
 * @param Spin Handle of Spin entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_destroy(SPIN_HANDLE spin);

/**
 * @brief Get the current owner of an existing Spin entry
 * @param Spin Handle of Spin entry to get owner for
 * @return Handle of owning thread or INVALID_HANDLE_VALUE if not currently owned
 */
THREAD_HANDLE STDCALL spin_owner(SPIN_HANDLE spin);

/**
 * @brief Lock an existing Spin entry
 * @param Spin Handle of Spin entry to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_lock(SPIN_HANDLE spin);

/**
 * @brief Unlock an existing Spin entry
 * @param Spin Handle of Spin entry to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_unlock(SPIN_HANDLE spin);

/**
 * @brief Lock an existing Spin entry, disable IRQ and save the previous IRQ state
 * @param Spin Handle of Spin entry to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_lock_irq(SPIN_HANDLE spin);

/**
 * @brief Unlock an existing Spin entry and restore the previous IRQ state
 * @param Spin Handle of Spin entry to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_unlock_irq(SPIN_HANDLE spin);

/**
 * @brief Lock an existing Spin entry, disable FIQ and save the previous FIQ state
 * @param Spin Handle of Spin entry to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_lock_fiq(SPIN_HANDLE spin);

/**
 * @brief Unlock an existing Spin entry and restore the previous FIQ state
 * @param Spin Handle of Spin entry to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_unlock_fiq(SPIN_HANDLE spin);

/**
 * @brief Lock an existing Spin entry, disable IRQ and FIQ and save the previous IRQ and FIQ state
 * @param Spin Handle of Spin entry to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_lock_irq_fiq(SPIN_HANDLE spin);

/**
 * @brief Unlock an existing Spin entry and restore the previous IRQ and FIQ state
 * @param Spin Handle of Spin entry to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL spin_unlock_irq_fiq(SPIN_HANDLE spin);

/**
 * @brief Lock an existing Spin entry, disable IRQ or IRQ/FIQ and save the previous IRQ or IRQ/FIQ state
 * @param Spin Handle of Spin entry to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note This is a convenience wrapper which determines the appropriate SpinLock call to disable preemption
 */
uint32_t STDCALL spin_lock_preempt(SPIN_HANDLE spin);

/**
 * @brief Unlock an existing Spin entry and restore the previous IRQ or IRQ/FIQ state
 * @param Spin Handle of Spin entry to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note This is a convenience wrapper which determines the appropriate SpinUnlock call to enable preemption
 */
uint32_t STDCALL spin_unlock_preempt(SPIN_HANDLE spin);

/**
 * @brief Check the mask that stores the previous IRQ state to determine if IRQ is enabled
 * @param Spin Handle of Spin entry to check
 * @return True if the mask would enable IRQ on restore, False if it would not
 * @note The Spin entry must be locked by the current thread
 */
BOOL STDCALL spin_check_irq(SPIN_HANDLE spin);

/**
 * @brief Check the mask that stores the previous FIQ state to determine if FIQ is enabled
 * @param Spin Handle of Spin entry to check
 * @return True if the mask would enable FIQ on restore, False if it would not
 * @note The Spin entry must be locked by the current thread
 */
BOOL STDCALL spin_check_fiq(SPIN_HANDLE spin);

/**
 * @brief Exchange the previous IRQ state between two Spin entries
 * @param Spin1 Handle of first Spin entry
 * @param Spin2 Handle of second Spin entry
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Both Spin entries must be locked by the current thread
 */
uint32_t STDCALL spin_exchange_irq(SPIN_HANDLE spin1, SPIN_HANDLE spin2);

/**
 * @brief Exchange the previous FIQ state between two Spin entries
 * @param Spin1 Handle of first Spin entry
 * @param Spin2 Handle of second Spin entry
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Both Spin entries must be locked by the current thread
 */
uint32_t STDCALL spin_exchange_fiq(SPIN_HANDLE spin1, SPIN_HANDLE spin2);

/** Mutex Functions */

/**
 * @brief Create and insert a new Mutex entry
 * @return Handle of new Mutex entry or INVALID_HANDLE_VALUE if entry could not be created
 */
MUTEX_HANDLE STDCALL mutex_create(void);

/**
 * @brief Create and insert a new Mutex entry
 * @param InitialOwner If true set the state of the mutex to locked and the owner to the current thread
 * @param SpinCount The number of times the mutex will spin before yielding (Always 0 if CPU count equals 1)
 * @param Flags The flags for the Mutex entry (eg MUTEX_FLAG_RECURSIVE)
 * @return Handle of new Mutex entry or INVALID_HANDLE_VALUE if entry could not be created
 */
MUTEX_HANDLE STDCALL mutex_create_ex(BOOL initialowner, uint32_t spincount, uint32_t flags);

/**
 * @brief Destroy and remove an existing Mutex entry
 * @param Mutex Handle of Mutex entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL mutex_destroy(MUTEX_HANDLE mutex);

/**
 * @brief Get the current flags of an existing Mutex entry
 * @param Mutex Handle of Mutex entry to get flags for
 * @return Current flags or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL mutex_flags(MUTEX_HANDLE mutex);

/**
 * @brief Get the current lock count of an existing Mutex entry
 * @param Mutex Mutex to get count for
 * @return Current lock count or INVALID_HANDLE_VALUE on error
 * @note Count is only valid if Flags includes MUTEX_FLAG_RECURSIVE
 */
uint32_t STDCALL mutex_count(MUTEX_HANDLE mutex);

/**
 * @brief Get the current owner of an existing Mutex entry
 * @param Mutex Handle of Mutex entry to get owner for
 * @return Handle of owning thread or INVALID_HANDLE_VALUE if not currently owned
 */
THREAD_HANDLE STDCALL mutex_owner(MUTEX_HANDLE mutex);

/**
 * @brief Lock an existing Mutex entry
 * @param Mutex Handle of Mutex entry to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL mutex_lock(MUTEX_HANDLE mutex);

/**
 * @brief Unlock an existing Mutex entry
 * @param Mutex Handle of Mutex entry to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL mutex_unlock(MUTEX_HANDLE mutex);

/**
 * @brief Try to lock an existing Mutex entry
 *
 *  If the Mutex is not locked then lock it and mark the owner as the current thread
 *
 *  If the Mutex is already locked then return immediately with an error and do not
 *  wait for it to be unlocked
 * @param Mutex Mutex to try to lock
 * @return ERROR_SUCCESS if completed, ERROR_LOCKED if already locked or another error code on failure
 */
uint32_t STDCALL mutex_try_lock(MUTEX_HANDLE mutex);

/** Critical Section Functions */

/**
 * @brief Create and insert a new CriticalSection entry
 * @return Handle of new CriticalSection entry or INVALID_HANDLE_VALUE if entry could not be created
 */
CRITICAL_SECTION_HANDLE STDCALL critical_section_create(void);

/**
 * @brief Create and insert a new CriticalSection entry
 * @param InitialOwner If true set the state of the criticalsection to locked and the owner to the current thread
 * @param SpinCount The number of times the criticalsection will spin before waiting (Always 0 if CPU count equals 1)
 * @return Handle of new CriticalSection entry or INVALID_HANDLE_VALUE if entry could not be created
 */
CRITICAL_SECTION_HANDLE STDCALL critical_section_create_ex(BOOL initialowner, uint32_t spincount);

/**
 * @brief Destroy and remove an existing CriticalSection entry
 * @param CriticalSection Handle of CriticalSection entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL critical_section_destroy(CRITICAL_SECTION_HANDLE criticalsection);

/**
 * @brief Get the current lock count of an existing CriticalSection entry
 * @param CriticalSection CriticalSection to get count for
 * @return Current lock count or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL critical_section_count(CRITICAL_SECTION_HANDLE criticalsection);

/**
 * @brief Get the current owner of an existing CriticalSection entry
 * @param CriticalSection CriticalSection to get owner for
 * @return Handle of owning thread or INVALID_HANDLE_VALUE if not currently owned
 */
THREAD_HANDLE STDCALL critical_section_owner(CRITICAL_SECTION_HANDLE criticalsection);

/**
 * @brief Set the spin count of an existing CriticalSection entry
 * @param CriticalSection CriticalSection to set spin count for
 * @param SpinCount The spin count value to set
 * @return Current spin count or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL critical_section_set_spin_count(CRITICAL_SECTION_HANDLE criticalsection, uint32_t spincount);

/**
 * @brief Lock an existing CriticalSection entry
 *
 *  If the CriticalSection is not locked then lock it, set the count to one and
 *  mark the owner as the current thread
 *
 *  If the CriticalSection is already locked by the current thread then increment
 *  the count and return immediately
 *
 *  If the CriticalSection is already locked by another thread then wait until it
 *  is unlocked
 * @param CriticalSection CriticalSection to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL critical_section_lock(CRITICAL_SECTION_HANDLE criticalsection);

/**
 * @brief Lock an existing CriticalSection entry
 *
 *  If the CriticalSection is not locked then lock it, set the count to one and
 *  mark the owner as the current thread
 *
 *  If the CriticalSection is already locked by the current thread then increment
 *  the count and return immediately
 *
 *  If the CriticalSection is already locked by another thread then wait until it
 *  is unlocked
 * @param CriticalSection CriticalSection to lock
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL critical_section_lock_ex(CRITICAL_SECTION_HANDLE criticalsection, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Unlock an existing CriticalSection entry
 *
 *  If the CriticalSection is locked by the current thread then decrement the count
 *
 *  If the count is greater than zero then return immediately
 *
 *  If the count reaches zero then unlock the CriticalSection and release the first
 *  thread waiting for it to be unlocked
 *
 *  If the CriticalSection is locked by another thread then return an error
 *
 *  If the CriticalSection is not locked then return an error
 * @param CriticalSection CriticalSection to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL critical_section_unlock(CRITICAL_SECTION_HANDLE criticalsection);

/**
 * @brief Try to lock an existing CriticalSection entry
 *
 *  If the CriticalSection is not locked then lock it, set the count to one and
 *  mark the owner as the current thread
 *
 *  If the CriticalSection is already locked by the current thread then increment
 *  the count and return immediately
 *
 *  If the CriticalSection is already locked by another thread then return immediately
 *  with an error and do not wait for it to be unlocked
 * @param CriticalSection CriticalSection to try to lock
 * @return ERROR_SUCCESS if completed, ERROR_LOCKED if locked by another thread or another error code on failure
 */
uint32_t STDCALL critical_section_try_lock(CRITICAL_SECTION_HANDLE criticalsection);

/** Semaphore Functions */

/**
 * @brief Create and insert a new Semaphore entry
 * @param Count The initial count of the Semaphore (Must be greater than or equal to zero)
 * @return Handle of new Semaphore entry or INVALID_HANDLE_VALUE if entry could not be created
 */
SEMAPHORE_HANDLE STDCALL semaphore_create(uint32_t count);

/**
 * @brief Create and insert a new Semaphore entry
 * @param Count The initial count of the Semaphore (Must be greater than or equal to zero)
 * @param Maximum The maximum count of the Semaphore (Must be greater than one)
 * @param Flags The flags for the Semaphore entry (eg SEMAPHORE_FLAG_IRQ)
 * @return Handle of new Semaphore entry or INVALID_HANDLE_VALUE if entry could not be created
 */
SEMAPHORE_HANDLE STDCALL semaphore_create_ex(uint32_t count, uint32_t maximum, uint32_t flags);

/**
 * @brief Destroy and remove an existing Semaphore entry
 * @param Semaphore Handle of Semaphore entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL semaphore_destroy(SEMAPHORE_HANDLE semaphore);

/**
 * @brief Get the current count of an existing Semaphore entry
 * @param Semaphore Semaphore to get count for
 * @return Current count or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL semaphore_count(SEMAPHORE_HANDLE semaphore);

/**
 * @brief Wait on an existing Semaphore entry
 *
 *  If the Semaphore count is greater than zero it will be decremented
 *  and this function will return immediately
 *
 *  If the Semaphore count is zero the current thread will be put on a wait queue
 *  until the Semaphore is signalled by another thread calling SemaphoreSignal()
 *  or SemaphoreSignalEx()
 * @param Semaphore Semaphore to wait on
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL semaphore_wait(SEMAPHORE_HANDLE semaphore);

/**
 * @brief Wait on an existing Semaphore entry
 *
 *  If the Semaphore count is greater than zero it will be decremented
 *  and this function will return immediately
 *
 *  If the Semaphore count is zero the current thread will be put on a wait queue
 *  until the Semaphore is signalled by another thread calling SemaphoreSignal()
 *  or SemaphoreSignalEx()
 * @param Semaphore Semaphore to wait on
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL semaphore_wait_ex(SEMAPHORE_HANDLE semaphore, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Signal an existing Semaphore entry
 *
 *  If any threads are waiting on the Semaphore then one thread will be woken up and
 *  placed on the ready queue
 *
 *  If no threads are waiting then the Semaphore count will be incremented by one
 * @param Semaphore Semaphore to signal
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL semaphore_signal(SEMAPHORE_HANDLE semaphore);

/**
 * @brief Signal an existing Semaphore entry one or more times
 *
 *  If any threads are waiting on the Semaphore then one thread will be woken up and
 *  placed on the ready queue for each iteration of the count passed
 *
 *  If no threads are waiting then the Semaphore count will be incremented once for each
 *  iteration of the count passed
 * @param Semaphore Semaphore to signal
 * @param Count The number is times to signal the Semaphore, must be greater than zero
 * @param Previous A pointer to a value that receives the previous count of the Semaphore
 *            Can be nil if the previous count is not required
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL semaphore_signal_ex(SEMAPHORE_HANDLE semaphore, uint32_t count, uint32_t *previous);

/** Synchronizer Functions */

/**
 * @brief Create and insert a new Synchronizer entry
 * @return Handle of new Synchronizer entry or INVALID_HANDLE_VALUE if entry could not be created
 */
SYNCHRONIZER_HANDLE STDCALL synchronizer_create(void);

/**
 * @brief Create and insert a new Synchronizer entry
 * @param InitialReader If true set the state of the synchronizer to locked and the reader count to 1
 * @param InitialWriter If true set the state of the synchronizer to locked and the writer owner to the current thread
 * @return Handle of new Synchronizer entry or INVALID_HANDLE_VALUE if entry could not be created
 */
SYNCHRONIZER_HANDLE STDCALL synchronizer_create_ex(BOOL initialreader, BOOL initialwriter);

/**
 * @brief Destroy and remove an existing Synchronizer entry
 * @param Synchronizer Handle of Synchronizer entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL synchronizer_destroy(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Get the current reader count of an existing Synchronizer entry
 * @param Synchronizer Synchronizer to get count for
 * @return Current reader count or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL synchronizer_reader_count(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Get the last reader thread of an existing Synchronizer entry
 * @param Synchronizer Synchronizer to last reader for
 * @return Last reader thread or INVALID_HANDLE_VALUE on error
 */
THREAD_HANDLE STDCALL synchronizer_reader_last(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Lock an existing Synchronizer entry for reading
 *
 *  If the Synchronizer is not locked then lock it and set the reader count to one
 *
 *  If the Synchronizer is already locked for reading then increment the reader count
 *  and return immediately
 *
 *  If the Synchronizer is already locked for writing then wait until it is unlocked
 * @param Synchronizer Synchronizer to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL synchronizer_reader_lock(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Lock an existing Synchronizer entry for reading
 *
 *  If the Synchronizer is not locked then lock it and set the reader count to one
 *
 *  If the Synchronizer is already locked for reading then increment the reader count
 *  and return immediately
 *
 *  If the Synchronizer is already locked for writing then wait until it is unlocked
 * @param Synchronizer Synchronizer to lock
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL synchronizer_reader_lock_ex(SYNCHRONIZER_HANDLE synchronizer, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Unlock an existing Synchronizer entry
 *
 *  If the Synchronizer is locked for reading then decrement the count
 *
 *  If the count is greater than zero then return immediately
 *
 *  If the count reaches zero then unlock the Synchronizer and release the first
 *  writer thread waiting for it to be unlocked
 *
 *  If the Synchronizer is locked for writing then return an error
 *
 *  If the Synchronizer is not locked then return an error
 * @param Synchronizer Synchronizer to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL synchronizer_reader_unlock(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Convert a reader lock on an existing Synchronizer entry to a writer lock
 *
 *  If the Synchronizer is locked for reading then decrement the count
 *
 *  If the count is greater than zero then wait to acquire the writer lock
 *
 *  If the count reaches zero then convert to writer lock with the current
 *  thread as the owner
 *
 *  If the Synchronizer is locked for writing then return an error
 *
 *  If the Synchronizer is not locked then return an error
 * @param Synchronizer Synchronizer to convert
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Since reader locks are recursive but do not maintain reader thread ownership,
 *  caller must ensure that one and only one reader lock is held by the current thread
 */
uint32_t STDCALL synchronizer_reader_convert(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Convert a reader lock on an existing Synchronizer entry to a writer lock
 *
 *  If the Synchronizer is locked for reading then decrement the count
 *
 *  If the count is greater than zero then wait to acquire the writer lock
 *
 *  If the count reaches zero then convert to writer lock with the current
 *  thread as the owner
 *
 *  If the Synchronizer is locked for writing then return an error
 *
 *  If the Synchronizer is not locked then return an error
 * @param Synchronizer Synchronizer to convert
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Since reader locks are recursive but do not maintain reader thread ownership,
 *  caller must ensure that one and only one reader lock is held by the current thread
 */
uint32_t STDCALL synchronizer_reader_convert_ex(SYNCHRONIZER_HANDLE synchronizer, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Get the current writer count of an existing Synchronizer entry
 * @param Synchronizer Synchronizer to get count for
 * @return Current writer count or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL synchronizer_writer_count(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Get the current writer owner of an existing Synchronizer entry
 * @param Synchronizer Synchronizer to get owner for
 * @return Handle of owning thread or INVALID_HANDLE_VALUE if not currently owned
 */
THREAD_HANDLE STDCALL synchronizer_writer_owner(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Lock an existing Synchronizer entry for writing
 *
 *  If the Synchronizer is not locked then lock it, set the writer count to one
 *  and mark the owner as the current thread
 *
 *  If the Synchronizer is already locked by the current thread then increment
 *  the writer count and return immediately
 *
 *  If the Synchronizer is already locked for reading then wait until it is unlocked
 * @param Synchronizer Synchronizer to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL synchronizer_writer_lock(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Lock an existing Synchronizer entry for writing
 *
 *  If the Synchronizer is not locked then lock it, set the writer count to one
 *  and mark the owner as the current thread
 *
 *  If the Synchronizer is already locked by the current thread then increment
 *  the writer count and return immediately
 *
 *  If the Synchronizer is already locked for reading then wait until it is unlocked
 * @param Synchronizer Synchronizer to lock
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL synchronizer_writer_lock_ex(SYNCHRONIZER_HANDLE synchronizer, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Unlock an existing Synchronizer entry
 *
 *  If the Synchronizer is locked for writing by the current thread then decrement the count
 *
 *  If the count is greater than zero then return immediately
 *
 *  If the count reaches zero then unlock the Synchronizer and release all reader threads
 *  waiting for it to be unlocked or the first writer thread waiting for it to be unlocked
 *
 *  If the Synchronizer is locked for reading then return an error
 *
 *  If the Synchronizer is locked for writing by another thread then return an error
 *
 *  If the Synchronizer is not locked then return an error
 * @param Synchronizer Synchronizer to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL synchronizer_writer_unlock(SYNCHRONIZER_HANDLE synchronizer);

/**
 * @brief Convert a writer lock on an existing Synchronizer entry to a reader lock
 *
 *  If the Synchronizer is locked for writing by the current thread and the count
 *  is one then decrement the count
 *
 *  If the count is greater than one then return an error
 *
 *  If the count reaches zero then convert to reader lock and release all waiting
 *  reader threads
 *
 *  If the Synchronizer is locked for reading then return an error
 *
 *  If the Synchronizer is not locked then return an error
 * @param Synchronizer Synchronizer to convert
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Since writer locks are recursive, caller must ensure that one and only
 *  one writer lock is held by the current thread
 */
uint32_t STDCALL synchronizer_writer_convert(SYNCHRONIZER_HANDLE synchronizer);

/** Condition Functions */

/**
 * @brief Create and insert a new Condition entry
 * @return Handle of new Condition entry or INVALID_HANDLE_VALUE if entry could not be created
 */
CONDITION_HANDLE STDCALL condition_create(void);

/**
 * @brief Destroy and remove an existing Condition entry
 * @param Condition Handle of Condition entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL condition_destroy(CONDITION_HANDLE condition);

/**
 * @brief Wait on an existing Condition
 * @param Condition Condition to wait on
 * @param Timeout Time in milliseconds to wait to be woken
 *           0 = No Wait
 *           INFINITE = Wait Indefinitely
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL condition_wait(CONDITION_HANDLE condition, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Release a Mutex and Wait on an existing Condition in an atomic operation
 * @param Condition Condition to wait on
 * @param Mutex Mutex to release
 * @param Timeout Time in milliseconds to wait to be woken
 *           0 = No Wait
 *           INFINITE = Wait Indefinitely
 * @return ERROR_SUCCESS if completed or another error code on failure.
 *          Before returning (with either success or failure) the thread will reacquire the Mutex
 * @note Caller must be the owner of the Mutex with a count of one on entry to this function
 */
uint32_t STDCALL condition_wait_mutex(CONDITION_HANDLE condition, MUTEX_HANDLE mutex, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Release a Synchronizer and Wait on an existing Condition in an atomic operation
 * @param Condition Condition to wait on
 * @param Synchronizer Synchronizer to release
 * @param Flags Flags to indicate reader or writer lock for the Synchronizer (eg CONDITION_LOCK_FLAG_WRITER)
 * @param Timeout Time in milliseconds to wait to be woken
 *           0 = No Wait
 *           INFINITE = Wait Indefinitely
 * @return ERROR_SUCCESS if completed or another error code on failure.
 *          Before returning (with either success or failure) the thread will reacquire the Synchronizer
 *          for either reading or writing depending on the flags value
 * @note Caller must be the owner of the Synchronizer with a count of one on entry to this function
 *        and the ownership must match the flags value provided
 */
uint32_t STDCALL condition_wait_synchronizer(CONDITION_HANDLE condition, SYNCHRONIZER_HANDLE synchronizer, uint32_t flags, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Release a Critical Section and Wait on an existing Condition in an atomic operation
 * @param Condition Condition to wait on
 * @param CriticalSection Critical Section to release
 * @param Timeout Time in milliseconds to wait to be woken
 *           0 = No Wait
 *           INFINITE = Wait Indefinitely
 * @return ERROR_SUCCESS if completed or another error code on failure.
 *          Before returning (with either success or failure) the thread will reacquire the Synchronizer
 *          for either reading or writing depending on the flags value
 * @note Caller must be the owner of the Critical Section with a count of one on entry to this function
 */
uint32_t STDCALL condition_wait_critical_section(CONDITION_HANDLE condition, CRITICAL_SECTION_HANDLE criticalsection, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Wake one thread waiting on an existing Condition
 * @param Condition Condition to wake
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL condition_wake(CONDITION_HANDLE condition);

/**
 * @brief Wake all threads waiting on an existing Condition
 * @param Condition Condition to wake
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL condition_wake_all(CONDITION_HANDLE condition);

/** Completion Functions */

/**
 * @brief Create and insert a new Completion entry
 * @param Flags The flags for the Completion entry (eg COMPLETION_FLAG_IRQ)
 * @return Handle of new Completion entry or INVALID_HANDLE_VALUE if entry could not be created
 */
COMPLETION_HANDLE STDCALL completion_create(uint32_t flags);

/**
 * @brief Destroy and remove an existing Completion entry
 * @param Completion Handle of Completion entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL completion_destroy(COMPLETION_HANDLE completion);

/**
 * @brief Get the current state of an existing Completion entry
 * @param Completion Completion to get the state for
 * @return Current state (eg COMPLETION_STATE_COMPLETE) or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL completion_state(COMPLETION_HANDLE completion);

/**
 * @brief Wait on an existing Completion
 *
 *  If the completion is set (complete) then return immediately with success
 *
 *  If the completion is not set then wait for it to be completed before
 *  returning
 *
 *  For counted completions, decrement the count if it is not 0 or -1 after
 *  testing if the completion is set
 * @param Completion Completion to wait on
 * @param Timeout Time in milliseconds to wait to be woken
 *           0 = No Wait
 *           INFINITE = Wait Indefinitely
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL completion_wait(COMPLETION_HANDLE completion, uint32_t timeout);

/**
 * @brief Try an existing Completion to see if it is completed
 *
 *  If the completion is not set (complete) then return immediately with an error
 *  and do not wait for it to be completed
 * @param Completion Completion to try
 * @return ERROR_SUCCESS if completed, ERROR_NOT_READY if not completed or another error code on failure
 */
uint32_t STDCALL completion_try_wait(COMPLETION_HANDLE completion);

/**
 * @brief Reset (uncomplete) the state of an existing Completion entry
 *
 *  If the completion is not set then return with no action
 *
 *  If the completion is set then change the state to not set
 *
 *  For counted completions, reset the counter to 0
 * @param Completion Completion to reset the state for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL completion_reset(COMPLETION_HANDLE completion);

/**
 * @brief Set (complete) the state of an existing Completion entry
 *
 *  If the completion is already set then return with no action
 *
 *  If the completion is not set then release one waiting thread (if any)
 *  and return
 *
 *  For counted completions, release one waiting thread, if there are no
 *  waiting threads increment the count if it is not -1 and return
 * @param Completion Completion to set the state for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL completion_complete(COMPLETION_HANDLE completion);

/**
 * @brief Set (complete) the state of an existing Completion entry
 *
 *  If the completion is already set then return with no action
 *
 *  If the completion is not set then release all waiting threads (if any)
 *  and return
 *
 *  For counted completions, set the count to -1, release all waiting threads
 *  (if any) and return
 * @param Completion Completion to set the state for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL completion_complete_all(COMPLETION_HANDLE completion);

/** List Functions */

/**
 * @brief Create and insert a new List entry
 * @return Handle of new List entry or INVALID_HANDLE_VALUE if entry could not be created
 */
LIST_HANDLE STDCALL list_create(void);

/**
 * @brief Create and insert a new List entry
 * @param ListType Type of list to create (eg LIST_TYPE_WAIT_SEMAPHORE)
 * @param Flags Flags for the new list (eg LIST_FLAG_IRQ)
 * @return Handle of new List entry or INVALID_HANDLE_VALUE if entry could not be created
 */
LIST_HANDLE STDCALL list_create_ex(uint32_t listtype, uint32_t flags);

/**
 * @brief Destroy and remove an existing List entry
 * @param List Handle of List entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
uint32_t STDCALL list_destroy(LIST_HANDLE list);

/**
 * @brief Get the current count from the supplied list
 * @param List Handle of List entry to get from
 * @return List count on success or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL list_count(LIST_HANDLE list);

/**
 * @brief Add the supplied element as the first item in the List
 * @param List Handle of List entry to add to
 * @param Element The list element to be added
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
uint32_t STDCALL list_add_first(LIST_HANDLE list, LIST_ELEMENT *element);

/**
 * @brief Add the supplied element as the last item in the List
 * @param List Handle of List entry to add to
 * @param Element The list element to be added
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
uint32_t STDCALL list_add_last(LIST_HANDLE list, LIST_ELEMENT *element);

/**
 * @brief Find the supplied thread in the List and return its element
 * @param List Handle of List entry to find from
 * @param Thread The thread handle to be found
 * @return List element on success, nil on failure or list empty
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
LIST_ELEMENT * STDCALL list_get_thread(LIST_HANDLE list, THREAD_HANDLE thread);

/**
 * @brief Get the first element from the List
 * @param List Handle of List entry to get from
 * @return List element on success, nil on failure or list empty
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
LIST_ELEMENT * STDCALL list_get_first(LIST_HANDLE list);

/**
 * @brief Get the first element from the List
 * @param List Handle of List entry to get from
 * @param Remove If true then remove the element from the list
 * @return List element on success, nil on failure or list empty
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
LIST_ELEMENT * STDCALL list_get_first_ex(LIST_HANDLE list, BOOL remove);

/**
 * @brief Get the last element from the List
 * @param List Handle of List entry to get from
 * @return List element on success, nil on failure or list empty
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
LIST_ELEMENT * STDCALL list_get_last(LIST_HANDLE list);

/**
 * @brief Get the last element from the List
 * @param List Handle of List entry to get from
 * @param Remove If true then remove the element from the list
 * @return List element on success, nil on failure or list empty
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
LIST_ELEMENT * STDCALL list_get_last_ex(LIST_HANDLE list, BOOL remove);

/**
 * @brief Insert a new element in the List
 * @param List Handle of List entry to insert into
 * @param Previous The element to insert the new element after
 * @param Element The list element to be inserted
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
uint32_t STDCALL list_insert(LIST_HANDLE list, LIST_ELEMENT *previous, LIST_ELEMENT *element);

/**
 * @brief Remove an element from the List
 * @param List Handle of List entry to remove from
 * @param Element The list element to be removed
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
uint32_t STDCALL list_remove(LIST_HANDLE list, LIST_ELEMENT *element);

/**
 * @brief Check if the supplied List is empty
 * @param List Handle of List entry to check
 * @return True if List is empty or does not exist, False if List is not empty
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
BOOL STDCALL list_is_empty(LIST_HANDLE list);

/**
 * @brief Check if the supplied List is empty
 * @param List Handle of List entry to check
 * @return True if List is not empty, False if List is empty or does not exist
 * @note If list is part of a synchronisation object then caller must hold the lock on the object containing the list
 */
BOOL STDCALL list_not_empty(LIST_HANDLE list);

/**
 * @brief Lock the supplied List
 * @param List Handle of List entry to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL list_lock(LIST_HANDLE list);

/**
 * @brief Unlock the supplied List
 * @param List Handle of List entry to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL list_unlock(LIST_HANDLE list);

/** Queue Functions */

/**
 * @brief Create and insert a new Queue entry
 * @return Handle of new Queue entry or INVALID_HANDLE_VALUE if entry could not be created
 */
QUEUE_HANDLE STDCALL queue_create(void);

/**
 * @brief Create and insert a new Queue entry
 * @param QueueType Type of queue to create (eg QUEUE_TYPE_SCHEDULE_SLEEP)
 * @param Flags Flags for the new queue (eg QUEUE_FLAG_DESCENDING)
 * @return Handle of new Queue entry or INVALID_HANDLE_VALUE if entry could not be created
 */
QUEUE_HANDLE STDCALL queue_create_ex(uint32_t queuetype, uint32_t flags);

/**
 * @brief Destroy and remove an existing Queue entry
 * @param Queue Handle of Queue entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL queue_destroy(QUEUE_HANDLE queue);

/**
 * @brief Get the current count from the supplied queue
 * @param List Handle of Queue entry to get from
 * @return Queue count on success or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL queue_count(QUEUE_HANDLE queue);

/**
 * @brief Add the supplied thread as the last item in the Queue
 * @param Queue Handle of Queue entry to add to
 * @param Thread Handle of the Thread to enqueue
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note If queue is a scheduler queue then caller must hold the lock on the thread
 */
uint32_t STDCALL queue_enqueue(QUEUE_HANDLE queue, THREAD_HANDLE thread);

/**
 * @brief Get and remove the first thread from the Queue
 * @param Queue Handle of Queue entry to get from
 * @return Handle of dequeued Thread or INVALID_HANDLE_VALUE on failure
 */
THREAD_HANDLE STDCALL queue_dequeue(QUEUE_HANDLE queue);

/**
 * @brief Get the first Key value from the Queue
 * @param Queue Handle of Queue entry to get from
 * @return First Key value from queue or QUEUE_KEY_NONE on failure
 */
int STDCALL queue_first_key(QUEUE_HANDLE queue);

/**
 * @brief Get the last Key value from the Queue
 * @param Queue Handle of Queue entry to get from
 * @return Last Key value from queue or QUEUE_KEY_NONE on failure
 */
int STDCALL queue_last_key(QUEUE_HANDLE queue);

/**
 * @brief Insert the supplied thread in the Queue ordered based on Key and the flags of the Queue
 * @param Queue Handle of Queue entry to insert into
 * @param Thread Handle of thread to be inserted
 * @param Key The key to order the insertion on
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note If queue is a scheduler queue then caller must hold the lock on the thread
 */
uint32_t STDCALL queue_insert_key(QUEUE_HANDLE queue, THREAD_HANDLE thread, int key);

/**
 * @brief Delete the supplied thread from the Queue based on the flags of the Queue
 * @param Queue Handle of Queue entry to delete from
 * @param Thread Handle of thread to be deleted
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note If queue is a scheduler queue then caller must hold the lock on the thread
 */
uint32_t STDCALL queue_delete_key(QUEUE_HANDLE queue, THREAD_HANDLE thread);

/**
 * @brief Increment the first Key value in the Queue
 * @param Queue Handle of Queue entry to increment in
 * @return First Key value in queue after increment or QUEUE_KEY_NONE on failure
 */
int STDCALL queue_increment_key(QUEUE_HANDLE queue);

/**
 * @brief Decrement the first Key value in the Queue
 * @param Queue Handle of Queue entry to decrement in
 * @return First Key value in queue after decrement or QUEUE_KEY_NONE on failure
 */
int STDCALL queue_decrement_key(QUEUE_HANDLE queue);

/**
 * @brief Check if the supplied Queue is empty
 * @param Queue Handle of Queue entry to check
 * @return True if Queue is empty or does not exist, False if Queue is not empty
 */
BOOL STDCALL queue_is_empty(QUEUE_HANDLE queue);

/**
 * @brief Check if the supplied Queue is not empty
 * @param Queue Handle of Queue entry to check
 * @return True if Queue is not empty, False if Queue is empty or does not exist
 */
BOOL STDCALL queue_not_empty(QUEUE_HANDLE queue);

/**
 * @brief Lock the supplied Queue
 * @param Queue Handle of Queue entry to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL queue_lock(QUEUE_HANDLE queue);

/**
 * @brief Unlock the supplied Queue
 * @param Queue Handle of Queue entry to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL queue_unlock(QUEUE_HANDLE queue);

/** Thread Functions */

/**
 * @brief Create and insert a new Thread entry
 *
 *  The new thread will be created suspended so it will not start running until it is
 *  scheduled with either ThreadReady or ThreadResume
 * @param StartProc Procedure address where the thread will start running
 * @param StackSize Stack size in bytes
 * @param Priority Thread priority (eg THREAD_PRIORITY_NORMAL)
 * @param Name Name of the thread
 * @param Parameter Parameter passed to StartProc of new thread
 * @return Handle of new thread or INVALID_HANDLE_VALUE if a new thread could not be created
 * @note Calls ThreadCreateEx with:
 *          Affinity = SCHEDULER_CPU_MASK (Run on any available CPU)
 *          CPU = SchedulerThreadNext (Assign to next CPU in round robin)
 * @param WARNING ThreadCreate and ThreadCreateEx are only used internally by SysBeginThread and SysBeginThreadEx
 *
 *           These functions do not handle setting up certain RTL functionality such as thread variables,
 *           exceptions and standard input/output handles.
 *
 *           If you need to create a standard thread use either BeginThread (or BeginThreadEx) or use the
 *           TThread class and its descendants. Only use ThreadCreate and ThreadCreateEx if you need to modify
 *           the thread creation behaviour and understand that you also need to handle the additional RTL setup
 */
THREAD_HANDLE STDCALL thread_create(thread_start_proc startproc, uint32_t stacksize, uint32_t priority, const char *name, void *parameter);

/**
 * @brief Create and insert a new Thread entry
 *
 *  The new thread will be created suspended so it will not start running until it is
 *  scheduled with either ThreadReady or ThreadResume
 * @param StartProc Procedure address where the thread will start running
 * @param StackSize Stack size in bytes
 * @param Priority Thread priority (eg THREAD_PRIORITY_NORMAL)
 * @param Affinity Thread affinity (eg CPU_AFFINITY_ALL)
 * @param CPU The CPU to assign new thread to (eg CPU_ID_0)
 * @param Name Name of the thread
 * @param Parameter Parameter passed to StartProc of new thread
 * @return Handle of new thread or INVALID_HANDLE_VALUE if a new thread could not be created
 * @param WARNING ThreadCreate and ThreadCreateEx are only used internally by SysBeginThread and SysBeginThreadEx
 *
 *           These functions do not handle setting up certain RTL functionality such as thread variables,
 *           exceptions and standard input/output handles.
 *
 *           If you need to create a standard thread use either BeginThread (or BeginThreadEx) or use the
 *           TThread class or its descendants. Only use ThreadCreate and ThreadCreateEx if you need to modify
 *           the thread creation behaviour and understand that you also need to handle the additional RTL setup
 */
THREAD_HANDLE STDCALL thread_create_ex(thread_start_proc startproc, uint32_t stacksize, uint32_t priority, uint32_t affinity, uint32_t cpu, const char *name, void *parameter);

/**
 * @brief Destroy and remove an existing Thread entry
 * @param Thread Handle of thread to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_destroy(THREAD_HANDLE thread);

/**
 * @brief Get the Handle of currently executing thread
 * @return Thread handle of the currently running thread
 */
THREAD_HANDLE STDCALL thread_get_current(void);

/**
 * @brief Set the Handle of currently executing thread
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Must not be called except during initialization
 */
uint32_t STDCALL thread_set_current(THREAD_HANDLE thread);

/**
 * @brief Get the name of a Thread
 * @param Thread Handle of thread to get
 * @return Name of thread or empty string on failure
 */
uint32_t STDCALL thread_get_name(THREAD_HANDLE thread, char *name, uint32_t len);

/**
 * @brief Set the name of a Thread
 * @param Thread Handle of thread to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_set_name(THREAD_HANDLE thread, const char *name);

/**
 * @brief Get the current CPU of a thread (eg CPU_ID_0)
 * @param Thread Handle of thread to get
 * @return CPU of the thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_get_cpu(THREAD_HANDLE thread);

/**
 * @brief Set the current CPU of a thread (eg CPU_ID_0)
 *
 *  The new CPU will not take affect until the thread is next rescheduled
 * @param Thread Handle of thread to set
 * @param CPU New thread CPU (eg CPU_ID_0)
 * @return Previous CPU of thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_set_cpu(THREAD_HANDLE thread, uint32_t cpu);

/**
 * @brief Get the current state of a thread (eg THREAD_STATE_SUSPENDED)
 * @param Thread Handle of thread to get
 * @return State of the thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_get_state(THREAD_HANDLE thread);

/**
 * @brief Get the current flags of a thread
 * @param Thread Handle of thread to get
 * @return Flags of the thread (eg THREAD_FLAG_PERSIST) or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_get_flags(THREAD_HANDLE thread);

/**
 * @brief Set the current flags of a thread
 * @param Thread Handle of thread to set
 * @param Flags Flags to set (eg THREAD_FLAG_PERSIST)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_set_flags(THREAD_HANDLE thread, uint32_t flags);

/**
 * @brief Add flags to the current flags of a thread
 * @param Thread Handle of thread to add flags for
 * @param Flags Flags to add (eg THREAD_FLAG_PERSIST)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_add_flags(THREAD_HANDLE thread, uint32_t flags);

/**
 * @brief Remove flags from the current flags of a thread
 * @param Thread Handle of thread to remove flags from
 * @param Flags Flags to remove (eg THREAD_FLAG_PERSIST)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_remove_flags(THREAD_HANDLE thread, uint32_t flags);

/**
 * @brief Get the current locale of a thread
 * @param Thread Handle of thread to get
 * @return Locale of the thread or INVALID_HANDLE_VALUE on failure
 */
LCID STDCALL thread_get_locale(THREAD_HANDLE thread);

/**
 * @brief Set the locale of a thread
 * @param Thread Handle of thread to set
 * @param Locale Locale id to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_set_locale(THREAD_HANDLE thread, LCID locale);

/**
 * @brief Get the current times of a thread
 * @param Thread Handle of thread to get
 * @param CreateTime Buffer to receive the CreateTime value
 * @param ExitTime Buffer to receive the ExitTime value
 * @param KernelTime Buffer to receive the KernelTime value
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_get_times(THREAD_HANDLE thread, int64_t *createtime, int64_t *exittime, int64_t *kerneltime);

/**
 * @brief Get the current context switch count of a thread (How many times the thread has been scheduled)
 * @param Thread Handle of thread to get
 * @param SwitchCount Buffer to receive the SwitchCount value
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_get_switch_count(THREAD_HANDLE thread, int64_t *switchcount);

/**
 * @brief Get the free stack size of the current thread
 * @return Free stack size of the current thread or 0 on error
 * @note No lock required as only ever called by the thread itself
 */
uint32_t STDCALL thread_get_stack_free(void);

/**
 * @brief Get the current stack size of a thread
 * @param Thread Handle of thread to get
 * @return Stack size of the thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_get_stack_size(THREAD_HANDLE thread);

/**
 * @brief Get the current stack base of a thread
 * @param Thread Handle of thread to get
 * @return Stack base of the thread or INVALID_HANDLE_VALUE on failure
 */
size_t STDCALL thread_get_stack_base(THREAD_HANDLE thread);

/**
 * @brief Set the current stack base of a thread
 * @param Thread Handle of thread to set
 * @param StackBase Stack base to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Must not be called except during initialization
 */
uint32_t STDCALL thread_set_stack_base(THREAD_HANDLE thread, size_t stackbase);

/**
 * @brief Get the current stack pointer of a thread
 * @param Thread Handle of thread to get
 * @return Stack pointer of the thread or INVALID_HANDLE_VALUE on failure
 */
size_t STDCALL thread_get_stack_pointer(THREAD_HANDLE thread);

/**
 * @brief Get the exit code of a Thread
 * @param Thread Handle of thread to get
 * @return Exit code of thread, STILL_ACTIVE if the thread has not terminated or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_get_exit_code(THREAD_HANDLE thread);

/**
 * @brief Get the scheduling affinity of a Thread
 * @param Thread Handle of thread to get
 * @return Affinity of thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_get_affinity(THREAD_HANDLE thread);

/**
 * @brief Set the scheduling affinity of a Thread
 *
 *  The new affinity will not take affect until the thread is next rescheduled
 * @param Thread Handle of thread to set
 * @param Affinity New thread affinity (eg CPU_AFFINITY_0)
 * @return Previous affinity of thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_set_affinity(THREAD_HANDLE thread, uint32_t affinity);

/**
 * @brief Get the scheduling priority of a Thread
 * @param Thread Handle of thread to get
 * @return Priority of thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_get_priority(THREAD_HANDLE thread);

/**
 * @brief Set the scheduling priority of a Thread
 *
 *  The new priority will not take affect until the thread is next rescheduled
 * @param Thread Handle of thread to set
 * @param Priority New thread priority (eg THREAD_PRIORITY_NORMAL)
 * @return Previous priority of thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_set_priority(THREAD_HANDLE thread, uint32_t priority);

/**
 * @brief Get the last error value for the current Thread
 * @return Last Error of thread or ERROR_SUCCESS if no error
 * @note No lock required as only ever called by the thread itself
 */
uint32_t STDCALL thread_get_last_error(void);

/**
 * @brief Set the last error value for the current Thread
 * @note No lock required as only ever called by the thread itself
 */
void STDCALL thread_set_last_error(uint32_t lasterror);

/**
 * @brief Set the last error value for the current Thread
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note No lock required as only ever called by the thread itself
 */
uint32_t STDCALL thread_set_last_error_ex(uint32_t lasterror);

/**
 * @brief Get the result of the last wait timeout for the current Thread
 * @return Result of last wait timeout or ERROR_SUCCESS if no error
 * @note No lock required as only ever called by the thread itself
 */
uint32_t STDCALL thread_get_wait_result(void);

/**
 * @brief Get the result of the last receive timeout for the current Thread
 * @return Result of last receive timeout or ERROR_SUCCESS if no error
 * @note No lock required as only ever called by the thread itself
 */
uint32_t STDCALL thread_get_receive_result(void);

/**
 * @brief Get the current status of a TLS index in the TLS index table
 * @param TlsIndex The TLS index to get the status for
 * @return THREAD_TLS_FREE if unused, THREAD_TLS_USED if in use or THREAD_TLS_INVALID on error
 * @note No lock required as only ever reads from the table
 */
uint32_t STDCALL thread_get_tls_index(uint32_t tlsindex);

/**
 * @brief Allocate a TLS index in the TLS index table
 * @return Allocated TLS index or TLS_OUT_OF_INDEXES on failure
 */
uint32_t STDCALL thread_alloc_tls_index(void);

/**
 * @brief Allocate a TLS index in the TLS index table
 * @param Flags The flags to apply to the TLS index entries (eg THREAD_TLS_FLAG_FREE)
 * @return Allocated TLS index or TLS_OUT_OF_INDEXES on failure
 */
uint32_t STDCALL thread_alloc_tls_index_ex(uint32_t flags);

/**
 * @brief Deallocate a TLS index from the TLS index table
 * @param TlsIndex The TLS index to deallocate
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_release_tls_index(uint32_t tlsindex);

/**
 * @brief Get the pointer associated with the TLS index for the current thread
 * @return Pointer for the specified TLS index or nil if not set or on error
 * @note No lock required as only ever called by the thread itself
 */
void * STDCALL thread_get_tls_value(uint32_t tlsindex);

/**
 * @brief Set the pointer associated with the TLS index for the current thread
 * @param TlsIndex The TLS index to get the pointer for
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note No lock required as only ever called by the thread itself
 */
uint32_t STDCALL thread_set_tls_value(uint32_t tlsindex, void *tlsvalue);

/**
 * @brief Get the RTL TLS (Thread Local Storage) pointer of a Thread
 * @param Thread Handle of thread to get
 * @return Pointer to the RTL TLS of thread or nil on failure
 */
void * STDCALL thread_get_tls_pointer(THREAD_HANDLE thread);

/**
 * @brief Set the RTL TLS (Thread Local Storage) pointer of a Thread
 * @param Thread Handle of thread to set
 * @param TlsPointer Pointer value to set (Can be nil to clear the pointer)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_set_tls_pointer(THREAD_HANDLE thread, void *tlspointer);

/**
 * @brief Place the supplied Thread on the ready queue
 * @param Thread Handle of thread to make ready
 * @param Reschedule If True then call SchedulerReschedule
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note When called by the scheduler, thread has already been removed from the sleep queue
 */
uint32_t STDCALL thread_ready(THREAD_HANDLE thread, BOOL reschedule);

/**
 * @brief Place the supplied Thread on the ready queue after a timeout waiting on a resource
 * @param Thread Handle of thread to make ready
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note When called by the scheduler, thread has already been removed from the timeout queue
 */
uint32_t STDCALL thread_timeout(THREAD_HANDLE thread);

/**
 * @brief Remove a thread prematurely from the sleep or timeout queues
 * @param Thread Handle of thread to remove
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note A thread that was sleeping will simply return early
 *        A thread that was waiting or receiving with a timeout will return
 *        with the error WAIT_TIMEOUT
 *        A thread that was waiting or receiving with INFINITE timeout will return
 *        with the error WAIT_ABANDONED
 */
uint32_t STDCALL thread_wake(THREAD_HANDLE thread);

/**
 * @brief Migrate a thread to a new CPU
 * @param Thread Handle of thread to migrate
 * @param CPU New CPU for the thread
 * @return Previous CPU of thread or INVALID_HANDLE_VALUE on failure
 */
uint32_t STDCALL thread_migrate(THREAD_HANDLE thread, uint32_t cpu);

/**
 * @brief Terminate the current Thread
 * @param ExitCode The return code of the thread
 */
void STDCALL thread_end(uint32_t exitcode);

/**
 * @brief Halt the current thread so it will never be rescheduled.
 *
 *  Normally only called due to an unhandled exception etc so that the thread
 *  is put to sleep permanently without being terminated
 * @param ExitCode The return code of the thread
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_halt(uint32_t exitcode);

/**
 * @brief Terminate but do not destroy the supplied Thread
 *
 *  The terminated thread is placed on the termination queue until any threads
 *  waiting on it have been released
 * @param Thread Handle of thread to terminate
 * @param ExitCode The return code of the thread
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Terminating a thread from another thread is not safe unless specific precautions are taken
 *        to prevent deadlocks
 *        It is normally safe for a thread to terminate itself as long as it releases any locks it is
 *        holding that may be required by other threads before terminating
 */
uint32_t STDCALL thread_terminate(THREAD_HANDLE thread, uint32_t exitcode);

/**
 * @brief Make the current thread yield the processor (Same as ThreadSleep(0))
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_yield(void);

/**
 * @brief Place the current thread on the sleep queue for a specified number of milliseconds
 * @param Milliseconds Number of milliseconds to sleep
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_sleep(uint32_t milliseconds);

/**
 * @brief Put the current thread into a wait state on the supplied list
 * @param List Handle of List entry to put thread into
 * @param Lock Handle of Lock to release before going into wait state
 * @param Flags Flag to indicate which unlock method to use
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must hold the lock on the synchronisation object containing the list
 */
uint32_t STDCALL thread_wait(LIST_HANDLE list, SPIN_HANDLE lock, uint32_t flags);

/**
 * @brief Put the current thread into a wait state with timeout on the supplied list
 * @param List Handle of List entry to put thread into
 * @param Lock Handle of Lock to release before going into wait state
 * @param Flags Flag to indicate which unlock method to use
 * @param Timeout Milliseconds to wait before timeout (INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must hold the lock on the synchronisation object containing the list
 */
uint32_t STDCALL thread_wait_ex(LIST_HANDLE list, SPIN_HANDLE lock, uint32_t flags, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Release the first thread waiting on the supplied list
 * @param List Handle of List entry to release thread from
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must hold the lock on the synchronisation object containing the list
 */
uint32_t STDCALL thread_release(LIST_HANDLE list);

/**
 * @brief Release the first thread waiting on the supplied list and return with WAIT_ABANDONED
 * @param List Handle of List entry to release thread from
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must hold the lock on the synchronisation object containing the list
 */
uint32_t STDCALL thread_abandon(LIST_HANDLE list);

/**
 * @brief Make the current thread wait until the specified thread has terminated
 * @param Thread Handle of the thread to wait on
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The wait can be abandoned by calling ThreadWake with the handle of the waiting thread
 */
uint32_t STDCALL thread_wait_terminate(THREAD_HANDLE thread, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Suspend a thread, placing it in hibernation
 * @param Thread Handle of thread to suspend
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Suspending a thread from another thread is not safe unless specific precautions are taken
 *        to prevent deadlocks
 *        It is normally safe for a thread to suspend itself as long as it releases any locks it is
 *        holding that may be required by other threads before suspending
 */
uint32_t STDCALL thread_suspend(THREAD_HANDLE thread);

/**
 * @brief Resume a suspended thread, making it ready
 * @param Thread Handle of thread to resume
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_resume(THREAD_HANDLE thread);

/**
 * @brief Make the current thread wait until a message is received (indefinitely)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The received message is not removed from the message list
 */
uint32_t STDCALL thread_wait_message(void);

/**
 * @brief Send a message to another thread
 * @param Thread Handle of thread to send to
 * @param Message Contents of message to send
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_send_message(THREAD_HANDLE thread, THREAD_MESSAGE *message);

/**
 * @brief Make the current thread wait to receive a message (indefinitely)
 * @param Message The received message if successful, undefined on error
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_receive_message(THREAD_MESSAGE *message);

/**
 * @brief Make the current thread wait to receive a message
 * @param Message The received message if successful, undefined on error
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @param Remove If true then remove the received message from the message list
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL thread_receive_message_ex(THREAD_MESSAGE *message, uint32_t timeout, BOOL remove); ///< Timeout = 0 then no Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Tell another thread to abandon waiting for a message
 * @param Thread Handle of thread to abandon waiting
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The waiting thread will return with ERROR_WAIT_ABANDONED or ERROR_WAIT_TIMEOUT
 */
uint32_t STDCALL thread_abandon_message(THREAD_HANDLE thread);

/**
 * @brief Lock a thread allowing access to internal structures such as the thread stack
 * @param Thread Handle of thread to lock
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Locking a thread will also disable IRQ or FIQ depending on scheduler
 *        settings. The lock should only be held for the briefest time possible
 */
uint32_t STDCALL thread_lock(THREAD_HANDLE thread);

/**
 * @brief Unlok a thread that was locked by ThreadLock
 * @param Thread Handle of thread to unlock
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Locking a thread will also disable IRQ or FIQ depending on scheduler
 *        settings. The lock should only be held for the briefest time possible
 */
uint32_t STDCALL thread_unlock(THREAD_HANDLE thread);

/** Scheduler Functions */

/**
 * @brief Check if the sleep queue is empty, if not then decrement the first key
 *  Then check if the timeout queue is empty, if not then decrement the first key
 *
 *  If either key reaches zero, return success to indicate there are threads to be
 *  woken or threads whose timeout has expired
 *
 *  Finally check if the termination queue is empty, if not then decrement the first
 *  key
 *
 *  Items will be removed from the termination queue by SchedulerReschedule
 * @param CPUID The ID of the current CPU
 * @return ERROR_SUCCESS if either first key is zero, ERROR_NO_MORE_ITEMS if both queues are empty or another error code on failure
 * @note Called by scheduler interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 */
uint32_t STDCALL scheduler_check(uint32_t cpuid);

/**
 * @brief Remove all threads from the sleep queue that have no more time to sleep
 *
 *  Threads will be placed back on the ready queue for rescheduling
 * @param CPUID The ID of the current CPU
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Called by scheduler interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 */
uint32_t STDCALL scheduler_wakeup(uint32_t cpuid);

/**
 * @brief Remove all threads from the timeout queue that have no more time to wait
 *
 *  Threads will be placed back on the ready queue for rescheduling but will
 *  return with an error indicating the timeout expired
 * @param CPUID The ID of the current CPU
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Called by scheduler interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 */
uint32_t STDCALL scheduler_expire(uint32_t cpuid);

/**
 * @brief Perform a preemptive thread switch operation under an interrupt handler
 *
 *  The next thread to run will be selected based on remaining quantum of the current
 *  thread, ready threads at higher priority levels and scheduler priority quantum for
 *  fair scheduling of lower priority threads
 * @param CPUID The ID of the current CPU
 * @param Thread The handle of the currently running thread (Before IRQ or FIQ occurred)
 * @return The handle of the current thread which may be the old thread or a new thread
 * @note Called by scheduler interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 */
THREAD_HANDLE STDCALL scheduler_switch(uint32_t cpuid, THREAD_HANDLE thread);

/**
 * @brief Select the next thread to be run based on state, yield, quantum and priority
 * @param CPUID The ID of the current CPU
 * @param Thread The handle of the currently running thread (Before IRQ or FIQ occurred or when Reschedule was called)
 * @param Yield True if the current thread is giving up its remaining time slice
 * @return The handle of the next thread to run or INVALID_HANDLE_VALUE on no selection or error
 * @note Called either by scheduler interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 *        Or by scheduler reschedule with IRQ or FIQ disabled and running on the current thread
 * @note Caller must either hold a lock on the current thread or have disabled IRQ or FIQ
 */
THREAD_HANDLE STDCALL scheduler_select(uint32_t cpuid, THREAD_HANDLE thread, BOOL yield);

/**
 * @brief Perform a thread switch operation when a thread yields, sleeps or waits
 *
 *  The next thread to run will be selected based on whether the current thread is
 *  yielding or no longer ready, remaining quantum of the current thread, ready
 *  threads at higher priority levels and scheduler priority quantum for fair
 *  scheduling of lower priority threads
 * @param Yield True if the current thread is giving up its remaining time slice
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Called by the currently running thread to force a reschedule before sleeping, waiting etc
 */
uint32_t STDCALL scheduler_reschedule(BOOL yield);

/**
 * @brief Enable scheduler thread migration
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL scheduler_migration_enable(void);

/**
 * @brief Disable scheduler thread migration
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL scheduler_migration_disable(void);

/**
 * @brief Enable thread preemption for the specified CPU
 * @param CPUID The ID of the CPU to enable for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL scheduler_preempt_enable(uint32_t cpuid);

/**
 * @brief Disable thread preemption for the specified CPU
 * @param CPUID The ID of the CPU to disable for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL scheduler_preempt_disable(uint32_t cpuid);

/**
 * @brief Enable thread allocation for the specified CPU
 * @param CPUID The ID of the CPU to enable for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL scheduler_allocation_enable(uint32_t cpuid);

/**
 * @brief Disable thread allocation for the specified CPU
 * @param CPUID The ID of the CPU to disable for
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL scheduler_allocation_disable(uint32_t cpuid);

/** Messageslot Functions */

/**
 * @brief Create and insert a new Messageslot entry
 * @return Handle of new Messageslot entry or INVALID_HANDLE_VALUE if entry could not be created
 */
MESSAGESLOT_HANDLE STDCALL messageslot_create(void);

/**
 * @brief Create and insert a new Messageslot entry
 * @param Maximum Maximum number of messages allowed for the Messageslot (Must be greater than zero)
 * @param Flags The flags for the Messageslot entry (eg MESSAGESLOT_FLAG_IRQ)
 * @return Handle of new Messageslot entry or INVALID_HANDLE_VALUE if entry could not be created
 */
MESSAGESLOT_HANDLE STDCALL messageslot_create_ex(uint32_t maximum, uint32_t flags);

/**
 * @brief Destroy and remove an existing Messageslot entry
 * @param Messageslot Handle of Messageslot entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL messageslot_destroy(MESSAGESLOT_HANDLE messageslot);

/**
 * @brief Get the number of available messages in a Messageslot entry
 * @param Messageslot Messageslot to get from
 * @return Number of messages or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL messageslot_count(MESSAGESLOT_HANDLE messageslot);

/**
 * @brief Send a message to a Messageslot
 * @param Messageslot Messageslot to send to
 * @param Message Contents of message to send
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL messageslot_send(MESSAGESLOT_HANDLE messageslot, THREAD_MESSAGE *message);

/**
 * @brief Receive a message from a Messageslot
 * @param Messageslot Messageslot to receive from
 * @param Message The received message if successful, undefined on error
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL messageslot_receive(MESSAGESLOT_HANDLE messageslot, THREAD_MESSAGE *message);

/**
 * @brief Receive a message from a Messageslot
 * @param Messageslot Messageslot to receive from
 * @param Message The received message if successful, undefined on error
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL messageslot_receive_ex(MESSAGESLOT_HANDLE messageslot, THREAD_MESSAGE *message, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/** Mailslot Functions */

/**
 * @brief Create and insert a new Mailslot entry
 * @param Maximum Maximum number of messages allowed for the Mailslot (Must be greater than zero)
 * @return Handle of new Mailslot entry or INVALID_HANDLE_VALUE if entry could not be created
 */
MAILSLOT_HANDLE STDCALL mailslot_create(uint32_t maximum);

/**
 * @brief Destroy and remove an existing Mailslot entry
 * @param Mailslot Handle of Mailslot entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL mailslot_destroy(MAILSLOT_HANDLE mailslot);

/**
 * @brief Get the number of available messages in a Mailslot entry
 * @param Mailslot Mailslot to get from
 * @return Number of messages or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL mailslot_count(MAILSLOT_HANDLE mailslot);

/**
 * @brief Send a message to a Mailslot
 * @param Mailslot Mailslot to send to
 * @param Data Message to send to mailslot
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL mailslot_send(MAILSLOT_HANDLE mailslot, ssize_t data);

/**
 * @brief Send a message to a Mailslot
 * @param Mailslot Mailslot to send to
 * @param Data Message to send to mailslot
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL mailslot_send_ex(MAILSLOT_HANDLE mailslot, ssize_t data, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Receive a message from a Mailslot
 * @param Mailslot Mailslot to receive from
 * @return Received message or INVALID_HANDLE_VALUE on error
 */
ssize_t STDCALL mailslot_receive(MAILSLOT_HANDLE mailslot);

/**
 * @brief Receive a message from a Mailslot
 * @param Mailslot Mailslot to receive from
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return Received message or INVALID_HANDLE_VALUE on error
 */
ssize_t STDCALL mailslot_receive_ex(MAILSLOT_HANDLE mailslot, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/** Buffer Functions */

/**
 * @brief Create and insert a new Buffer entry
 * @param Size Size of each buffer in bytes
 * @param Count Total number of buffers
 * @return Handle of new Buffer entry or INVALID_HANDLE_VALUE if entry could not be created
 */
BUFFER_HANDLE STDCALL buffer_create(uint32_t size, uint32_t count);

/**
 * @brief Create and insert a new Buffer entry
 * @param Size Size of each buffer in bytes
 * @param Count Total number of buffers
 * @param Flags Flags for buffer (eg BUFFER_FLAG_SHARED)
 * @return Handle of new Buffer entry or INVALID_HANDLE_VALUE if entry could not be created
 */
BUFFER_HANDLE STDCALL buffer_create_ex(uint32_t size, uint32_t count, uint32_t flags);

/**
 * @brief Destroy and remove an existing Buffer entry
 * @param Buffer Handle of Buffer entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL buffer_destroy(BUFFER_HANDLE buffer);

/**
 * @brief Get the total count of buffers in an existing Buffer entry
 * @param Buffer Buffer to get total count for
 * @return Total count or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL buffer_count(BUFFER_HANDLE buffer);

/**
 * @brief Get the available count of buffers in an existing Buffer entry
 * @param Buffer Buffer to get available count for
 * @return Available count or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL buffer_available(BUFFER_HANDLE buffer);

/**
 * @brief Allocate an available buffer from an existing Buffer entry
 * @param Buffer Handle of Buffer entry to allocate from
 * @return A pointer to the allocated buffer or nil on error
 */
void * STDCALL buffer_get(BUFFER_HANDLE buffer);

/**
 * @brief Allocate an available buffer from an existing Buffer entry
 * @param Buffer Handle of Buffer entry to allocate from
 * @param Timeout Milliseconds to wait before timeout (0 equals do not wait, INFINITE equals wait forever)
 * @return A pointer to the allocated buffer or nil on error
 */
void * STDCALL buffer_get_ex(BUFFER_HANDLE buffer, uint32_t timeout); ///< Timeout = 0 then No Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Release a allocated buffer from an existing Buffer entry
 * @param Buffer Pointer to the allocated buffer (As returned by BufferGet/BufferGetEx)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL buffer_free(void *buffer);

/**
 * @brief Iterate through each of the buffers in an existing Buffer entry
 * @param Buffer Handle of Buffer entry to iterate from
 * @param Previous The pointer returned by the previous call or nil on first call
 * @return A pointer to the next buffer or nil on error
 * @note Iterate is intended to allow allocating or initializing buffers after
 *  a Buffer entry is created, or deallocating before a Buffer entry is destroyed.
 *
 *  The function will fail if any buffers are already in use (if the count and
 *  available count are not equal)
 */
void * STDCALL buffer_iterate(BUFFER_HANDLE buffer, void *previous);

/** Event Functions */

/**
 * @brief Create and insert a new Event entry
 * @param ManualReset Create a manual reset event if true or an auto reset event if false
 *               An manual reset event must be reset by calling EventReset
 *               An auto reset event is reset when a single waiting thread is released
 * @param InitialState Set the initial state of the event to signaled if true
 *                or to unsignaled if false
 * @return Handle of new Event entry or INVALID_HANDLE_VALUE if entry could not be created
 */
EVENT_HANDLE STDCALL event_create(BOOL manualreset, BOOL initialstate);

/**
 * @brief Create and insert a new Event entry
 * @param Flags Event flags to use for the new entry (eg EVENT_FLAG_MANUAL_RESET)
 * @return Handle of new Event entry or INVALID_HANDLE_VALUE if entry could not be created
 */
EVENT_HANDLE STDCALL event_create_ex(uint32_t flags);

/**
 * @brief Destroy and remove an existing Event entry
 * @param Event Handle of Event entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL event_destroy(EVENT_HANDLE event);

/**
 * @brief Get the current state of an existing Event entry
 * @param Event Event to get state for
 * @return Current state or INVALID_HANDLE_VALUE on error
 */
uint32_t STDCALL event_state(EVENT_HANDLE event);

/**
 * @brief Wait on an existing Event entry
 *
 *  If the Event is currently signaled then simply return immediately
 *
 *  If the Event is currently unsignaled then wait for it to be signaled
 *  before returning
 * @param Event Event to wait on
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL event_wait(EVENT_HANDLE event);

/**
 * @brief Wait on an existing Event entry
 *
 *  If the Event is currently signaled then simply return immediately
 *
 *  If the Event is currently unsignaled then wait for it to be signaled
 *  before returning
 * @param Event Event to wait on
 * @param Timeout Time in milliseconds to wait for the event to be signaled
 *           0 = No Wait
 *           INFINITE = Wait Indefinitely
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL event_wait_ex(EVENT_HANDLE event, uint32_t timeout); ///< Timeout = 0 then no Wait,Timeout = INFINITE then Wait forever

/**
 * @brief Set (Signal) an existing Event entry
 *
 *  If the event is currently signaled then return with no action
 *
 *  If the event is unsignaled then, if the event is manual reset release
 *  all waiting threads and return. If the event is auto reset release one
 *  waiting thread, unsignal the event and return
 *
 *  If no threads are waiting then simply signal the event and return, if
 *  the event is auto reset then the next thread to wait will unsignal the
 *  event
 * @param Event Event to set
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL event_set(EVENT_HANDLE event);

/**
 * @brief Reset (Unsignal) an existing Event entry
 *
 *  If the event is currently unsignaled then return with no action
 *
 *  If the event is signaled then unsignal the event and return
 * @param Event Event to reset
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL event_reset(EVENT_HANDLE event);

/**
 * @brief Pulse (Set then Reset) an existing Event entry
 *
 *  If the event is currently signaled then unsignal the event and return
 *
 *  If the event is unsignaled then, if the event is manual reset release
 *  all waiting threads, unsignal the event and return. If the event is
 *  auto reset release one waiting thread, unsignal the event and return
 *
 *  If no threads are waiting then simply unsignal the event and return
 * @param Event Event to pulse
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL event_pulse(EVENT_HANDLE event);

/** Timer Functions */

/**
 * @brief Create and insert a new Timer entry
 * @param Interval Number of milliseconds between timer events
 * @param Enabled If true then timer generates events
 * @param Reschedule If true then reschedule timer after each event
 * @param Event The function to call when the timer event is generated
 * @param Data Data to be passed to the function when the timer event is generated (May be nil)
 * @return Handle of new Timer entry or INVALID_HANDLE_VALUE if entry could not be created
 */
TIMER_HANDLE STDCALL timer_create(uint32_t interval, BOOL enabled, BOOL reschedule, timer_event_proc event, void *data);

/**
 * @brief Create and insert a new Timer entry
 * @param Interval Number of milliseconds between timer events
 * @param State State of timer entry (eg TIMER_STATE_ENABLED)
 * @param Flags Flags of timer entry (eg TIMER_FLAG_RESCHEDULE)
 * @param Event The function to call when the timer event is generated
 * @param Data Data to be passed to the function when the timer event is generated (May be nil)
 * @return Handle of new Timer entry or INVALID_HANDLE_VALUE if entry could not be created
 */
TIMER_HANDLE STDCALL timer_create_ex(uint32_t interval, uint32_t state, uint32_t flags, timer_event_proc event, void *data);

/**
 * @brief Destroy and remove an existing Timer entry
 * @param Timer Handle of Timer entry to destroy
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL timer_destroy(TIMER_HANDLE timer);

/**
 * @brief Enable an existing Timer entry (Timer events will be generated)
 * @param Timer Handle of Timer entry to enable
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL timer_enable(TIMER_HANDLE timer);

/**
 * @brief Enable and update an existing Timer entry (Timer events will be generated)
 * @param Timer Handle of Timer entry to enable
 * @param Interval Number of milliseconds between timer events
 * @param Event The function to call when the timer event is generated
 * @param Data Data to be passed to the function when the timer event is generated (May be nil)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL timer_enable_ex(TIMER_HANDLE timer, uint32_t interval, timer_event_proc event, void *data);

/**
 * @brief Disable an existing Timer entry (Timer events will not be generated)
 * @param Timer Handle of Timer entry to disable
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL timer_disable(TIMER_HANDLE timer);

/**
 * @brief Get and remove the first timer from the Timer list
 * @return Handle of dequeued Timer or INVALID_HANDLE_VALUE on failure
 */
TIMER_HANDLE STDCALL timer_dequeue(void);

/**
 * @brief Get the first Key value from the Timer list
 * @return First Key value from timer list or TIMER_KEY_NONE on failure
 */
int STDCALL timer_first_key(void);

/**
 * @brief Insert the supplied timer in the Timer list in delta ascending order based on Key
 * @param Timer Handle of timer to be inserted
 * @param Key The key to order the insertion on
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must hold the lock on the timer
 */
uint32_t STDCALL timer_insert_key(TIMER_HANDLE timer, int key);

/**
 * @brief Delete the supplied timer from the Timer list
 * @param Timer Handle of timer to be deleted
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Caller must hold the lock on the timer
 */
uint32_t STDCALL timer_delete_key(TIMER_HANDLE timer);

/**
 * @brief Decrement the first Key value in the Timer list
 * @return First Key value in timer list after decrement or TIMER_KEY_NONE on failure
 */
int STDCALL timer_decrement_key(void);

/**
 * @brief Check if the Timer list is empty
 * @return True if Timer list is empty or does not exist, False if Timer list is not empty
 */
BOOL STDCALL timer_is_empty(void);

/**
 * @brief Check if the Timer list is not empty
 * @return True if Timer list is not empty, False if Timer list is empty or does not exist
 */
BOOL STDCALL timer_not_empty(void);

/**
 * @brief Check if the timer list is empty, if not then decrement the first key
 *
 *  If the key reaches zero, return success to indicate there are timers to
 *  be triggered
 * @return ERROR_SUCCESS if the first key is zero, ERROR_NO_MORE_ITEMS if list is empty or another error code on failure
 * @note Called by clock interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 */
uint32_t STDCALL timer_check(void);

/**
 * @brief Remove all entries from the timer list that have reached their interval
 *
 *  For each timer a message will be sent to the Timer thread to call the event
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Called by clock interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 */
uint32_t STDCALL timer_trigger(void);

/** Worker Functions */

/**
 * @brief Schedule a task to be performed by a worker thread now or in the future
 * @param Interval The number of milliseconds before the task is to be performed (0 for immediate)
 * @param Task The function to be called by the worker when the interval has elapsed
 * @param Data A pointer to user defined data which will be passed to the task function (Optional)
 * @param Callback The function to be called by the worker when the task has completed (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL worker_schedule(uint32_t interval, worker_task_proc task, void *data, worker_cb callback);

/**
 * @brief Schedule a task to be performed by a worker thread now or in the future
 * @param Interval The number of milliseconds before the task is to be performed (0 for immediate)
 * @param Flags The flags for the task (eg WORKER_FLAG_RESCHEDULE)
 * @param Task The function to be called by the worker when the interval has elapsed
 * @param Data A pointer to user defined data which will be passed to the task function (Optional)
 * @param Callback The function to be called by the worker when the task has completed (Optional)
 * @return Handle of new Worker task or INVALID_HANDLE_VALUE if task could not be created
 * @note If the flags do not contain WORKER_FLAG_RESCHEDULE then return will be ERROR_SUCCESS
 */
WORKER_HANDLE STDCALL worker_schedule_ex(uint32_t interval, uint32_t flags, worker_task_proc task, void *data, worker_cb callback);

/**
 * @brief Cancel a previously scheduled worker thread task
 * @param Worker The handle of the worker task to cancel
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL worker_cancel(WORKER_HANDLE worker);

/**
 * @brief Schedule a task to be performed by a worker thread when the caller is an IRQ handler
 * @param Affinity CPU Affinity for memory allocation (eg CPU_AFFINITY_0 or CPU_AFFINITY_NONE)
 * @param Task The function to be called by the worker
 * @param Data A pointer to user defined data which will be passed to the task function (Optional)
 * @param Callback The function to be called by the worker when the task has completed (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The task will be performed immediately, for delayed tasks etc see WorkerSchedule(Ex)
 */
uint32_t STDCALL worker_schedule_irq(uint32_t affinity, worker_task_proc task, void *data, worker_cb callback);

/**
 * @brief Schedule a task to be performed by a worker thread when the caller is an IRQ handler
 * @param Affinity CPU Affinity for memory allocation (eg CPU_AFFINITY_0 or CPU_AFFINITY_NONE)
 * @param Flags The flags for the task (eg WORKER_FLAG_PRIORITY)
 * @param Task The function to be called by the worker
 * @param Data A pointer to user defined data which will be passed to the task function (Optional)
 * @param Callback The function to be called by the worker when the task has completed (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The task will be performed immediately, for delayed tasks etc see WorkerSchedule(Ex)
 */
uint32_t STDCALL worker_schedule_irq_ex(uint32_t affinity, uint32_t flags, worker_task_proc task, void *data, worker_cb callback);

/**
 * @brief Schedule a task to be performed by a worker thread when the caller is an FIQ handler
 * @param Affinity CPU Affinity for memory allocation (eg CPU_AFFINITY_0 or CPU_AFFINITY_NONE)
 * @param Task The function to be called by the worker
 * @param Data A pointer to user defined data which will be passed to the task function (Optional)
 * @param Callback The function to be called by the worker when the task has completed (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The task will be performed immediately, for delayed tasks etc see WorkerSchedule(Ex)
 */
uint32_t STDCALL worker_schedule_fiq(uint32_t affinity, worker_task_proc task, void *data, worker_cb callback);

/**
 * @brief Schedule a task to be performed by a worker thread when the caller is an FIQ handler
 * @param Affinity CPU Affinity for memory allocation (eg CPU_AFFINITY_0 or CPU_AFFINITY_NONE)
 * @param Flags The flags for the task (eg WORKER_FLAG_PRIORITY)
 * @param Task The function to be called by the worker
 * @param Data A pointer to user defined data which will be passed to the task function (Optional)
 * @param Callback The function to be called by the worker when the task has completed (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The task will be performed immediately, for delayed tasks etc see WorkerSchedule(Ex)
 */
uint32_t STDCALL worker_schedule_fiq_ex(uint32_t affinity, uint32_t flags, worker_task_proc task, void *data, worker_cb callback);

/**
 * @brief Increase the number of worker threads available
 * @param Count Number of worker threads to increase by
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL worker_increase(uint32_t count);

/**
 * @brief Increase the number of worker threads available
 * @param Count Number of worker threads to increase by
 * @param Priority If true increase worker priority threads
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL worker_increase_ex(uint32_t count, BOOL priority);

/**
 * @brief Decrease the number of worker threads available
 * @param Count Number of worker threads to decrease by
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL worker_decrease(uint32_t count);

/**
 * @brief Decrease the number of worker threads available
 * @param Count Number of worker threads to decrease by
 * @param Priority If true decrease worker priority threads
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL worker_decrease_ex(uint32_t count, BOOL priority);

/** Tasker Functions */

/**
 * @brief Perform a ThreadSendMessage() function call using the tasker list
 */
uint32_t STDCALL tasker_thread_send_message(THREAD_HANDLE thread, THREAD_MESSAGE *message);

/**
 * @brief Perform a MessageslotSend() function call using the tasker list
 */
uint32_t STDCALL tasker_messageslot_send(MESSAGESLOT_HANDLE messageslot, THREAD_MESSAGE *message);

/**
 * @brief Perform a SemaphoreSignal() function call using the tasker list
 */
uint32_t STDCALL tasker_semaphore_signal(SEMAPHORE_HANDLE semaphore, uint32_t count);

/**
 * @brief Perform a CompletionReset() function call using the tasker list
 */
uint32_t STDCALL tasker_completion_reset(COMPLETION_HANDLE completion);

/**
 * @brief Perform a CompletionComplete() or CompletionCompleteAll() function call using the tasker list
 */
uint32_t STDCALL tasker_completion_complete(COMPLETION_HANDLE completion, BOOL all);

/**
 * @brief Add the supplied task to the end of the Tasker list
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL tasker_enqueue(TASKER_TASK *task);

/**
 * @brief Get and remove the first task from the Tasker list
 * @return Dequeued Task or nil on failure (or list empty)
 */
TASKER_TASK * STDCALL tasker_dequeue(void);

/**
 * @brief Check if the tasker list is empty or contains tasks
 * @return ERROR_SUCCESS if the list contains tasks, ERROR_NO_MORE_ITEMS if list is empty or another error code on failure
 * @note Called by clock interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 */
uint32_t STDCALL tasker_check(void);

/**
 * @brief Dequeue all tasks in the tasker list and perform the requested task for each
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note Called by clock interrupt with IRQ or FIQ disabled and running on the IRQ or FIQ thread
 */
uint32_t STDCALL tasker_trigger(void);

/** RTL Thread Manager Functions */
/** See: \source\rtl\inc\thread.inc and \source\rtl\inc\threadh.inc */
/** See: \source\rtl\inc\system.inc and \source\rtl\inc\systemh.inc */

/**
 * @brief Start a new thread
 * @param SignalAction Not used by Ultibo
 * @param StackSize The stack size for the new thread
 * @param ThreadFunction The function to be executed by the new thread
 * @param ThreadParameter A pointer to be passed to ThreadFunction (Optional)
 * @param CreationFlags Flags to determine how the new thread is created (eg THREAD_CREATE_SUSPENDED)
 * @param ThreadId Filled with the thread ID of the new thread on return
 * @note SignalAction not used by Ultibo threading
 */
THREAD_ID STDCALL begin_thread(void *signalaction, size_t stacksize, thread_func threadfunction, void *threadparameter, uint32_t creationflags, THREAD_ID *threadid);

/**
 * @brief Start a new thread
 * @param SignalAction Not used by Ultibo
 * @param StackSize The stack size for the new thread
 * @param ThreadFunction The function to be executed by the new thread
 * @param ThreadParameter A pointer to be passed to ThreadFunction (Optional)
 * @param CreationFlags Flags to determine how the new thread is created (eg THREAD_CREATE_SUSPENDED)
 * @param Priority The priority of the new thread (eg THREAD_PRIORITY_NORMAL)
 * @param Affinity The CPU affinity of the new thread (eg CPU_AFFINITY_ALL)
 * @param CPU The CPU to assign new thread to (eg CPU_ID_0)
 * @param Name The name of the new thread
 * @param ThreadId Filled with the thread ID of the new thread on return
 * @note SignalAction not used by Ultibo threading
 */
THREAD_ID STDCALL begin_thread_ex(void *signalaction, size_t stacksize, thread_func threadfunction, void *threadparameter, uint32_t creationflags, uint32_t priority, uint32_t affinity, uint32_t cpu, const char *name, THREAD_ID *threadid);

/**
 * @brief End the current thread
 * @param ExitCode The exit code returned by a call to ThreadGetExitCode
 */
void STDCALL end_thread(uint32_t exitcode);

/** Thread Helper Functions */

/**
 * @brief Get the current spin lock count
 */
uint32_t STDCALL spin_get_count(void);

/**
 * @brief Get the current mutex count
 */
uint32_t STDCALL mutex_get_count(void);

/**
 * @brief Get the current critical section count
 */
uint32_t STDCALL critical_section_get_count(void);

/**
 * @brief Get the current semaphore count
 */
uint32_t STDCALL semaphore_get_count(void);

/**
 * @brief Get the current synchronizer count
 */
uint32_t STDCALL synchronizer_get_count(void);

/**
 * @brief Get the current condition count
 */
uint32_t STDCALL condition_get_count(void);

/**
 * @brief Get the current completion count
 */
uint32_t STDCALL completion_get_count(void);

/**
 * @brief Get the current list count
 */
uint32_t STDCALL list_get_count(void);

/**
 * @brief Get the current queue count
 */
uint32_t STDCALL queue_get_count(void);

/**
 * @brief Get the current thread count
 */
uint32_t STDCALL thread_get_count(void);

/**
 * @brief Get the current thread tls count
 */
uint32_t STDCALL thread_tls_get_count(void);

/**
 * @brief Allocate memory for a new thread stack
 * @param StackSize Number of bytes requested for new thread stack
 * @return nil if StackSize was 0 or if there is not enough memory to satisfy the
 *          request
 *          Otherwise returns a pointer to the top (highest address) of the newly
 *          allocated memory region
 *          This address is the base of the stack which grows down in memory
 */
void * STDCALL thread_allocate_stack(uint32_t stacksize);

/**
 * @brief Release a thread stack allocated with ThreadAllocateStack
 * @param StackBase Pointer to the top (highest address) of the thread stack
 *             (as returned by ThreadAllocateStack
 * @param StackSize Size of the thread stack, in bytes (Same value passed to ThreadAllocateStack)
 */
void STDCALL thread_release_stack(void *stackbase, uint32_t stacksize);
void * STDCALL thread_setup_stack(void *stackbase, thread_start_proc startproc, thread_end_proc returnproc, void *parameter);

THREAD_SNAPSHOT * STDCALL thread_snapshot_create(void);
uint32_t STDCALL thread_snapshot_destroy(THREAD_SNAPSHOT *snapshot);

/**
 * @brief Get the current messageslot count
 */
uint32_t STDCALL messageslot_get_count(void);

/**
 * @brief Get the current mailslot count
 */
uint32_t STDCALL mailslot_get_count(void);

/**
 * @brief Get the current buffer count
 */
uint32_t STDCALL buffer_get_count(void);

/**
 * @brief Get the current event count
 */
uint32_t STDCALL event_get_count(void);

/**
 * @brief Get the current timer count
 */
uint32_t STDCALL timer_get_count(void);

/**
 * @brief Get the current worker thread count
 */
uint32_t STDCALL worker_get_count(void);

/**
 * @brief Get the current worker priority thread count
 */
uint32_t STDCALL worker_get_priority_count(void);

/**
 * @brief Get the current tasker count
 */
uint32_t STDCALL tasker_get_count(void);

uint32_t STDCALL list_type_to_string(uint32_t listtype, char *string, uint32_t len);
uint32_t STDCALL queue_type_to_string(uint32_t queuetype, char *string, uint32_t len);
uint32_t STDCALL thread_type_to_string(uint32_t threadtype, char *string, uint32_t len);
uint32_t STDCALL thread_state_to_string(uint32_t threadstate, char *string, uint32_t len);
uint32_t STDCALL thread_priority_to_string(uint32_t threadpriority, char *string, uint32_t len);

/** Scheduler Helper Functions */

/**
 * @brief Get the list flags for the specified type of list
 */
uint32_t STDCALL scheduler_get_list_flags(uint32_t listtype);

/**
 * @brief Get the queue flags for the specified type of scheduler queue
 */
uint32_t STDCALL scheduler_get_queue_flags(uint32_t queuetype);

/**
 * @brief Get the queue handle for the specified type of scheduler queue on the specified CPU
 */
QUEUE_HANDLE STDCALL scheduler_get_queue_handle(uint32_t cpuid, uint32_t queuetype);

/**
 * @brief Get the queue handle for the specified thread priority on the specified CPU
 */
QUEUE_HANDLE STDCALL scheduler_get_queue_handle_ex(uint32_t cpuid, uint32_t priority);

/**
 * @brief Get the thread count for the specified CPU
 */
uint32_t STDCALL scheduler_get_thread_count(uint32_t cpuid);

/**
 * @brief Get the current thread quantum for the specified CPU
 */
uint32_t STDCALL scheduler_get_thread_quantum(uint32_t cpuid);

/**
 * @brief Get the thread handle for the specified type of thread on the specified CPU
 */
THREAD_HANDLE STDCALL scheduler_get_thread_handle(uint32_t cpuid, uint32_t threadtype);

/**
 * @brief Get the current priority mask for the specified CPU
 */
uint32_t STDCALL scheduler_get_priority_mask(uint32_t cpuid);

/**
 * @brief Get the scheduler quantum for the specified thread priority
 */
uint32_t STDCALL scheduler_get_priority_quantum(uint32_t priority);

/**
 * @brief Set the scheduler quantum for the specified thread priority
 */
uint32_t STDCALL scheduler_set_priority_quantum(uint32_t priority, uint32_t quantum);

/**
 * @brief Get the current migration quantum
 */
uint32_t STDCALL scheduler_get_migration_quantum(void);

/**
 * @brief Get the current starvation quantum for the specified CPU
 */
uint32_t STDCALL scheduler_get_starvation_quantum(uint32_t cpuid);

/**
 * @brief Get the next CPU for thread allocation
 */
uint32_t STDCALL scheduler_get_thread_next(void);

/**
 * @brief Get the current thread migration setting
 */
uint32_t STDCALL scheduler_get_thread_migration(void);

/**
 * @brief Get the current thread preempt setting for the specified CPU
 */
uint32_t STDCALL scheduler_get_thread_preempt(uint32_t cpuid);

/**
 * @brief Get the current thread allocation setting for the specified CPU
 */
uint32_t STDCALL scheduler_get_thread_allocation(uint32_t cpuid);

uint32_t STDCALL scheduler_migration_to_string(uint32_t migration, char *string, uint32_t len);
uint32_t STDCALL scheduler_preempt_to_string(uint32_t preempt, char *string, uint32_t len);
uint32_t STDCALL scheduler_allocation_to_string(uint32_t allocation, char *string, uint32_t len);

/** Timer Helper Functions */

/**
 * @brief Get the lock flags for the timer list
 */
uint32_t STDCALL timer_get_list_flags(void);

/**
 * @brief Get the lock flags for the timer messageslot
 */
uint32_t STDCALL timer_get_messageslot_flags(void);

/** Worker Helper Functions */

/**
 * @brief Get the lock flags for the worker messageslot
 */
uint32_t STDCALL worker_get_messageslot_flags(void);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_THREADS_H