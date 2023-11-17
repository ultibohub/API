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
#ifndef _ULTIBO_HEAPMANAGER_H
#define _ULTIBO_HEAPMANAGER_H

/* Note: Memory allocated using these functions must not be freed
 * using free() or heap corruption may occur. Allocations obtained
 * from these functions must be freed with free_mem(), free_irq_mem()
 * or free_fiq_mem() only
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/system.h"

/* ============================================================================== */
/* Heap specific constants */
#if defined (__x86_64__) || defined (__arch64__)
#define HEAP_MIN_BLOCK	57 // SizeOf(THeapBlock) + 1
#else
#define HEAP_MIN_BLOCK	33 // SizeOf(THeapBlock) + 1
#endif
#define HEAP_MIN_ALIGN	64 // SizeOf(THeapBlock) * 2

/* Heap Signature */
#define HEAP_SIGNATURE	0xE84DF600
#define HEAP_SIGNATURE_MASK	0xFFFFFF00

/* Heap Block States */
#define HEAP_STATE_FREE	0
#define HEAP_STATE_USED	1

#define HEAP_STATE_MASK	0x000000FF
#define HEAP_STATE_ALL	2 // Only for use by GetHeapBlockCount/GetHeapBlockMin/GetHeapBlockMax

/* Heap Block Flags */
#define HEAP_FLAG_NORMAL	0x00000000 // A normal memory block
#define HEAP_FLAG_SHARED	0x00000001 // A sharable memory block, usually marked as sharable in the page tables of the memory management unit
#define HEAP_FLAG_LOCAL	0x00000002 // A local memory block with an affinity to a specific processor, usually marked as non global in the page tables of the memory management unit
#define HEAP_FLAG_CODE	0x00000004 // A code memory block (with an optional affinity to a specific processor), usually marked as executable in the page tables of the memory management unit
#define HEAP_FLAG_DEVICE	0x00000008 // A device memory block, usually marked as device memory in the page tables of the memory management unit
#define HEAP_FLAG_NOCACHE	0x00000010 // A non cached memory block, usually marked as not cacheable in the page tables of the memory management unit
#define HEAP_FLAG_NONSHARED	0x00000020 // A non shared memory block, usually marked as not shareable in the page tables of the memory management unit
#define HEAP_FLAG_LOCKED	0x00000040 // A locked memory block (Not currently implemented in Ultibo)
#define HEAP_FLAG_IRQ	0x00000080 // An IRQ allocatable memory block
#define HEAP_FLAG_FIQ	0x00000100 // An FIQ allocatable memory block
#define HEAP_FLAG_RECLAIM	0x00000200 // A reclaimable memory block (eg Disk Cache)(with a registered callback to reclaim as required for normal memory)

#define HEAP_FLAG_CUSTOM	0x08000000 // A custom flag reserved for non standard uses

#define HEAP_FLAG_ALL	0xFFFFFFFF // Only for use by GetHeapBlockCount/GetHeapBlockMin/GetHeapBlockMax
#define HEAP_FLAG_INVALID	0xFFFFFFFF // Return value from MemFlags/IRQ/FIQ on invalid

/* Heap Small Blocks */
#if defined (__x86_64__) || defined (__arch64__)
#define HEAP_SMALL_MIN	56 // SizeOf(THeapBlock)
#else
#define HEAP_SMALL_MIN	32 // SizeOf(THeapBlock)
#endif
#define HEAP_SMALL_MAX	SIZE_4K // Maximum size of a small heap block
#define HEAP_SMALL_ALIGN	4 // SizeOf(LongWord);
#define HEAP_SMALL_SHIFT	2 // Size to Index conversion (Divide by 4)

#define HEAP_SMALL_LOW	(HEAP_SMALL_MIN / HEAP_SMALL_ALIGN) // 8 (32-bit) / 14 (64-bit)
#define HEAP_SMALL_HIGH	(HEAP_SMALL_MAX / HEAP_SMALL_ALIGN) // 1024

/* ============================================================================== */
/* Heap specific types */
#ifdef HEAP_STATISTICS_ENABLED
typedef struct _HEAP_STATISTICS HEAP_STATISTICS;
struct _HEAP_STATISTICS
{
	// Get/Alloc/Realloc
	uint32_t getcount;
	uint32_t alloccount;
	uint32_t realloccount;
	uint32_t getalignedcount;
	uint32_t allocalignedcount;
	uint32_t reallocalignedcount;
	uint32_t getsharedcount;
	uint32_t allocsharedcount;
	uint32_t reallocsharedcount;
	uint32_t getlocalcount;
	uint32_t alloclocalcount;
	uint32_t realloclocalcount;
	uint32_t getcodecount;
	uint32_t alloccodecount;
	uint32_t realloccodecount;
	uint32_t getdevicecount;
	uint32_t allocdevicecount;
	uint32_t reallocdevicecount;
	uint32_t getnocachecount;
	uint32_t allocnocachecount;
	uint32_t reallocnocachecount;
	uint32_t getnonsharedcount;
	uint32_t allocnonsharedcount;
	uint32_t reallocnonsharedcount;
	uint32_t getirqcount;
	uint32_t allocirqcount;
	uint32_t reallocirqcount;
	uint32_t getfiqcount;
	uint32_t allocfiqcount;
	uint32_t reallocfiqcount;
	// Free
	uint32_t freecount;
	uint32_t freeirqcount;
	uint32_t freefiqcount;
	uint32_t freesizecount;
	// Size
	uint32_t sizecount;
	uint32_t sizeirqcount;
	uint32_t sizefiqcount;
	// Flags
	uint32_t flagscount;
	uint32_t flagsirqcount;
	uint32_t flagsfiqcount;
	// Register
	uint32_t registercount;
	// Reserve
	uint32_t reservecount;
	// Request
	uint32_t requestcount;
	uint32_t requestsharedcount;
	uint32_t requestlocalcount;
	uint32_t requestcodecount;
	uint32_t requestdevicecount;
	uint32_t requestnocachecount;
	uint32_t requestnonsharedcount;
	uint32_t requestirqcount;
	uint32_t requestfiqcount;
	// Get Internal
	uint32_t getzerocount;
	uint32_t getremaincount;
	uint32_t getinvalidcount;
	uint32_t getunavailablecount;
	uint32_t getaddfailcount;
	uint32_t getsplitfailcount;
	uint32_t getremovefailcount;
	// Realloc Internal
	uint32_t realloczerocount;
	uint32_t reallocsmallercount;
	uint32_t realloclargercount;
	uint32_t reallocreleasecount;
	uint32_t reallocreleasebytes;
	uint32_t reallocaddfailcount;
	uint32_t reallocsplitfailcount;
	uint32_t reallocremovefailcount;
	// GetAligned Internal
	uint32_t getalignedzerocount;
	uint32_t getalignedremaincount;
	uint32_t getalignedinvalidcount;
	uint32_t getalignedundersizecount;
	uint32_t getalignedunavailablecount;
	uint32_t getalignedaddfailcount;
	uint32_t getalignedsplitfailcount;
	uint32_t getalignedremovefailcount;
	uint32_t getalignedreleasecount;
	uint32_t getalignedreleasebytes;
	// Free Internal
	uint32_t freeinvalidcount;
	uint32_t freeaddfailcount;
	uint32_t freemergefailcount;
	uint32_t freeremovefailcount;
	// Size Internal
	uint32_t sizeinvalidcount;
	// Flags Internal
	uint32_t flagsinvalidcount;
	// Register Internal
	uint32_t registerinvalidcount;
	uint32_t registeraddfailcount;
	// Reserve Internal
	uint32_t reserveinvalidcount;
	uint32_t reserveaddfailcount;
	uint32_t reservesplitfailcount;
	uint32_t reserveremovefailcount;
	uint32_t reserveunavailablecount;
	// Request Internal
	uint32_t requestinvalidcount;
	uint32_t requestaddfailcount;
	uint32_t requestsplitfailcount;
	uint32_t requestremovefailcount;
	uint32_t requestunavailablecount;
	// Split Internal
	uint32_t splitcount;
	// Merge Internal
	uint32_t mergeprevcount;
	uint32_t mergenextcount;
	// Block Internal
	uint32_t getsmallcount;
	uint32_t getlargecount;
	uint32_t findfreecount;
	uint32_t addsmallcount;
	uint32_t addlargecount;
	uint32_t removesmallcount;
	uint32_t removelargecount;
	uint32_t smallunavailablecount;
};
#endif

typedef struct _HEAP_SNAPSHOT HEAP_SNAPSHOT;
struct _HEAP_SNAPSHOT
{
	// Snapshot Properties
	size_t address; // Address of the Heap Block
	size_t size; // Size of the Heap Block (including the size of the THeapBlock structure)
	uint32_t state; // State of the Heap Block (eg HEAP_STATE_FREE)
	uint32_t flags; // Flags of the Heap Block (eg HEAP_FLAG_SHARED)
	uint32_t affinity; // CPU Affinity of the Heap Block (eg CPU_AFFINITY_0)
	// Internal Properties
	HEAP_SNAPSHOT *next; // Next entry in Heap snapshot
};

/* ============================================================================== */
/* Heap Functions */
void * STDCALL get_mem(size_t size);
void * STDCALL get_mem_ex(size_t size, uint32_t flags, uint32_t affinity);

void * STDCALL get_aligned_mem(size_t size, size_t alignment);
void * STDCALL get_aligned_mem_ex(size_t size, size_t alignment, uint32_t flags, uint32_t affinity);

void * STDCALL get_shared_mem(size_t size);
void * STDCALL get_shared_aligned_mem(size_t size, size_t alignment);

void * STDCALL get_local_mem(size_t size, uint32_t affinity);
void * STDCALL get_local_aligned_mem(size_t size, size_t alignment, uint32_t affinity);

void * STDCALL get_code_mem(size_t size, uint32_t affinity);
void * STDCALL get_code_aligned_mem(size_t size, size_t alignment, uint32_t affinity);

void * STDCALL get_device_mem(size_t size);
void * STDCALL get_device_aligned_mem(size_t size, size_t alignment);

void * STDCALL get_nocache_mem(size_t size);
void * STDCALL get_nocache_aligned_mem(size_t size, size_t alignment);

void * STDCALL get_nonshared_mem(size_t size);
void * STDCALL get_nonshared_aligned_mem(size_t size, size_t alignment);

void * STDCALL get_irq_mem(size_t size, uint32_t affinity);
void * STDCALL get_irq_aligned_mem(size_t size, size_t alignment, uint32_t affinity);

void * STDCALL get_fiq_mem(size_t size, uint32_t affinity);
void * STDCALL get_fiq_aligned_mem(size_t size, size_t alignment, uint32_t affinity);

size_t STDCALL free_mem(void *addr);
size_t STDCALL free_irq_mem(void *addr);
size_t STDCALL free_fiq_mem(void *addr);

void * STDCALL alloc_mem(size_t size);
void * STDCALL alloc_mem_ex(size_t size, uint32_t flags, uint32_t affinity);
void * STDCALL realloc_mem(void *addr, size_t size);
void * STDCALL realloc_mem_ex(void *addr, size_t size, uint32_t flags, uint32_t affinity);

void * STDCALL alloc_aligned_mem(size_t size, size_t alignment);
void * STDCALL alloc_aligned_mem_ex(size_t size, size_t alignment, uint32_t flags, uint32_t affinity);
void * STDCALL realloc_aligned_mem(void *addr, size_t size, size_t alignment);
void * STDCALL realloc_aligned_mem_ex(void *addr, size_t size, size_t alignment, uint32_t flags, uint32_t affinity);

void * STDCALL alloc_shared_mem(size_t size);
void * STDCALL alloc_shared_aligned_mem(size_t size, size_t alignment);
void * STDCALL realloc_shared_mem(void *addr, size_t size);
void * STDCALL realloc_shared_aligned_mem(void *addr, size_t size, size_t alignment);

void * STDCALL alloc_local_mem(size_t size, uint32_t affinity);
void * STDCALL alloc_local_aligned_mem(size_t size, size_t alignment, uint32_t affinity);
void * STDCALL realloc_local_mem(void *addr, size_t size, uint32_t affinity);
void * STDCALL realloc_local_aligned_mem(void *addr, size_t size, size_t alignment, uint32_t affinity);

void * STDCALL alloc_code_mem(size_t size, uint32_t affinity);
void * STDCALL alloc_code_aligned_mem(size_t size, size_t alignment, uint32_t affinity);
void * STDCALL realloc_code_mem(void *addr, size_t size, uint32_t affinity);
void * STDCALL realloc_code_aligned_mem(void *addr, size_t size, size_t alignment, uint32_t affinity);

void * STDCALL alloc_device_mem(size_t size);
void * STDCALL alloc_device_aligned_mem(size_t size, size_t alignment);
void * STDCALL realloc_device_mem(void *addr, size_t size);
void * STDCALL realloc_device_aligned_mem(void *addr, size_t size, size_t alignment);

void * STDCALL alloc_nocache_mem(size_t size);
void * STDCALL alloc_nocache_aligned_mem(size_t size, size_t alignment);
void * STDCALL realloc_nocache_mem(void *addr, size_t size);
void * STDCALL realloc_nocache_aligned_mem(void *addr, size_t size, size_t alignment);

void * STDCALL alloc_nonshared_mem(size_t size);
void * STDCALL alloc_nonshared_aligned_mem(size_t size, size_t alignment);
void * STDCALL realloc_nonshared_mem(void *addr, size_t size);
void * STDCALL realloc_nonshared_aligned_mem(void *addr, size_t size, size_t alignment);

void * STDCALL alloc_irq_mem(size_t size, uint32_t affinity);
void * STDCALL alloc_irq_aligned_mem(size_t size, size_t alignment, uint32_t affinity);
void * STDCALL realloc_irq_mem(void *addr, size_t size, uint32_t affinity);
void * STDCALL realloc_irq_aligned_mem(void *addr, size_t size, size_t alignment, uint32_t affinity);

void * STDCALL alloc_fiq_mem(size_t size, uint32_t affinity);
void * STDCALL alloc_fiq_aligned_mem(size_t size, size_t alignment, uint32_t affinity);
void * STDCALL realloc_fiq_mem(void *addr, size_t size, uint32_t affinity);
void * STDCALL realloc_fiq_aligned_mem(void *addr, size_t size, size_t alignment, uint32_t affinity);

size_t STDCALL size_mem(void *addr);
size_t STDCALL size_irq_mem(void *addr);
size_t STDCALL size_fiq_mem(void *addr);

uint32_t STDCALL mem_flags(void *addr);
uint32_t STDCALL mem_flags_irq(void *addr);
uint32_t STDCALL mem_flags_fiq(void *addr);

HEAP_STATUS STDCALL get_heap_status(void);
FPC_HEAP_STATUS STDCALL get_fpc_heap_status(void);
#ifdef HEAP_STATISTICS_ENABLED
HEAP_STATISTICS STDCALL get_heap_statistics(void);
#endif
uint32_t STDCALL get_heap_block_count(uint32_t state);
uint32_t STDCALL get_heap_block_count_ex(uint32_t state, uint32_t flags, uint32_t affinity);

uint32_t STDCALL get_heap_block_min(uint32_t state);
uint32_t STDCALL get_heap_block_min_ex(uint32_t state, uint32_t flags, uint32_t affinity);

uint32_t STDCALL get_heap_block_max(uint32_t state);
uint32_t STDCALL get_heap_block_max_ex(uint32_t state, uint32_t flags, uint32_t affinity);

HEAP_SNAPSHOT * STDCALL create_heap_snapshot(uint32_t state);
HEAP_SNAPSHOT * STDCALL create_heap_snapshot_ex(uint32_t state, uint32_t flags, uint32_t affinity);
uint32_t STDCALL destroy_heap_snapshot(HEAP_SNAPSHOT *snapshot);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_HEAPMANAGER_H