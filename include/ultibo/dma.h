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
#ifndef _ULTIBO_DMA_H
#define _ULTIBO_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/system.h"
#include "ultibo/devices.h"

/** DMA specific constants */
#define DMA_NAME_PREFIX	"DMA" ///< Name prefix for DMA Hosts

/** DMA Host Types */
#define DMA_TYPE_NONE	0

/** DMA Host States */
#define DMA_STATE_DISABLED	0
#define DMA_STATE_ENABLED	1

/** DMA Host Flags */
#define DMA_FLAG_NONE	0x00000000
#define DMA_FLAG_SHARED	0x00000001 ///< Host requires data buffers in shared memory
#define DMA_FLAG_NOCACHE	0x00000002 ///< Host requires data buffers in non cached memory
#define DMA_FLAG_COHERENT	0x00000004 ///< Data buffers are cache coherent if allocated according to host configuration
#define DMA_FLAG_STRIDE	0x00000008 ///< Host supports 2D stride on source and/or dest address
#define DMA_FLAG_DREQ	0x00000010 ///< Host supports data request gating (DREQ) on source and/or dest address
#define DMA_FLAG_NOINCREMENT	0x00000020 ///< Host supports no increment on source and/or dest address
#define DMA_FLAG_NOREAD	0x00000040 ///< Host supports no read from source address (write to dest address only) (Zero fill the destination)
#define DMA_FLAG_NOWRITE	0x00000080 ///< Host supports no write to dest address (read from source address only) (Cache fill from the source)
#define DMA_FLAG_WIDE	0x00000100 ///< Host supports wide read and/or write
#define DMA_FLAG_BULK	0x00000200 ///< Host supports bulk transfer
#define DMA_FLAG_LITE	0x00000400 ///< Host supports "lite" transfer
#define DMA_FLAG_40BIT	0x00000800 ///< Host supports 40-bit address transfer

/** DMA Data Flags */
/** See: Platform DMA_DATA_FLAG_* */

/** DMA Request Flags */
#define DMA_REQUEST_FLAG_NONE	0x00000000
#define DMA_REQUEST_FLAG_RELEASE	0x00000001 ///< If set then release the request automatically after completion
#define DMA_REQUEST_FLAG_CYCLIC	0x00000002 ///< This is a cyclic request which loops around from tail to head
#define DMA_REQUEST_FLAG_COMPATIBLE	0x00000004 ///< If set then all buffers supplied are host configuration compatible (Sizing, Alignment, Flags)

/** DMA specific types */

/** DMA Properties */
typedef struct _DMA_PROPERTIES DMA_PROPERTIES;
struct _DMA_PROPERTIES
{
	uint32_t flags; ///< Host flags (eg DMA_FLAG_STRIDE)
	uint32_t alignment; ///< Host data buffer alignment
	uint32_t multiplier; ///< Host data buffer multiplier
	uint32_t channels; ///< Total number of host channels
	uint32_t maxsize; ///< Maximum transfer size
	uint32_t maxcount; ///< Maximum Y count for 2D stride
	uint32_t maxlength; ///< Maximum X length for 2D stride
	int32_t minstride; ///< Minimum stride value (Increment between rows)(May be negative)
	uint32_t maxstride; ///< Maximum stride value (Increment between rows)
};

/** DMA Host */
typedef struct _DMA_HOST DMA_HOST;
typedef struct _DMA_REQUEST DMA_REQUEST; ///< Forward declared to satisfy DMAHost

/** DMA Enumeration Callback */
typedef uint32_t STDCALL (*dma_enumerate_cb)(DMA_HOST *dma, void *data);
/** DMA Notification Callback */
typedef uint32_t STDCALL (*dma_notification_cb)(DEVICE *device, void *data, uint32_t notification);

/** DMA Host Methods */
typedef uint32_t STDCALL (*dma_host_start_proc)(DMA_HOST *dma);
typedef uint32_t STDCALL (*dma_host_stop_proc)(DMA_HOST *dma);
typedef uint32_t STDCALL (*dma_host_reset_proc)(DMA_HOST *dma);
typedef uint32_t STDCALL (*dma_host_submit_proc)(DMA_HOST *dma, DMA_REQUEST *request);
typedef uint32_t STDCALL (*dma_host_cancel_proc)(DMA_HOST *dma, DMA_REQUEST *request);
typedef uint32_t STDCALL (*dma_host_properties_proc)(DMA_HOST *dma, DMA_PROPERTIES *properties);

struct _DMA_HOST
{
	// Device Properties
	DEVICE device; ///< The Device entry for this DMA host
	// DMA Properties
	uint32_t dmaid; ///< Unique Id of this DMA host in the DMA host table
	uint32_t dmastate; ///< DMA state (eg DMA_STATE_ENABLED)
	dma_host_start_proc hoststart; ///< A Host specific HostStart method implementing the standard DMA host interface (Mandatory)
	dma_host_stop_proc hoststop; ///< A Host specific HostStop method implementing the standard DMA host interface (Mandatory)
	dma_host_reset_proc hostreset; ///< A Host specific HostReset method implementing the standard DMA host interface (Or nil if the default method is suitable)
	dma_host_submit_proc hostsubmit; ///< A Host specific HostSubmit method implementing the standard DMA host interface (Mandatory)
	dma_host_cancel_proc hostcancel; ///< A Host specific HostCancel method implementing the standard DMA host interface (Mandatory)
	dma_host_properties_proc hostproperties; ///< A Host specific HostProperties method implementing the standard DMA host interface (Or nil if the default method is suitable)
	// Driver Properties
	MUTEX_HANDLE lock; ///< Host lock
	uint32_t alignment; ///< Host data buffer alignment
	uint32_t multiplier; ///< Host data buffer multiplier
	DMA_PROPERTIES properties; ///< Host properties
	uint32_t lasterror; ///< Last error to occur on this host
	uint32_t pendingcount; ///< Number of DMA requests pending for this host
	THREAD_ID waiterthread; ///< Thread waiting for pending requests to complete
	// Statistics Properties
	uint32_t requestcount; ///< Number of DMA requests that have been submitted to this host
	uint32_t requesterrors; ///< Number of DMA requests that have failed on this host
	// Internal Properties
	DMA_HOST *prev; ///< Previous entry in DMA host table
	DMA_HOST *next; ///< Next entry in DMA host table
};

/** DMA Request */

/** DMA Request Methods */
typedef void STDCALL (*dma_request_completed_cb)(DMA_REQUEST *request);

struct _DMA_REQUEST
{
	// Request Properties
	DMA_HOST *host;
	DMA_DATA *data; ///< List of data blocks for this request
	uint32_t flags; ///< Flags for the request (eg DMA_REQUEST_FLAG_RELEASE)
	uint32_t direction; ///< The direction of the DMA request (eg DMA_DIR_MEM_TO_MEM)
	uint32_t peripheral; ///< The peripheral ID for data request gating (eg DMA_DREQ_ID_NONE)
	dma_request_completed_cb callback; ///< Callback function that will be called when this DMA request has been successfully completed or has failed
	void *driverdata; ///< Private data for the completion callback (Optional)
	// Result Properties
	uint32_t status; ///< Status of the request (ERROR_SUCCESS if successful, or another error code if the request failed)
	// Driver Properties
	void *controlblocks;
};

/** DMA Host Functions */

uint32_t STDCALL dma_host_start(DMA_HOST *dma);
uint32_t STDCALL dma_host_stop(DMA_HOST *dma);
uint32_t STDCALL dma_host_reset(DMA_HOST *dma);
uint32_t STDCALL dma_host_properties(DMA_HOST *dma, DMA_PROPERTIES *properties);

/**
 * @brief Create a new DMA entry
 * @return Pointer to new DMA entry or nil if DMA could not be created
 */
DMA_HOST * STDCALL dma_host_create(void);

/**
 * @brief Create a new DMA entry
 * @param Size Size in bytes to allocate for new DMA (Including the DMA entry)
 * @return Pointer to new DMA entry or nil if DMA could not be created
 */
DMA_HOST * STDCALL dma_host_create_ex(uint32_t size);

/**
 * @brief Destroy an existing DMA entry
 */
uint32_t STDCALL dma_host_destroy(DMA_HOST *dma);

/**
 * @brief Register a new DMA in the DMA host table
 */
uint32_t STDCALL dma_host_register(DMA_HOST *dma);

/**
 * @brief Deregister a DMA from the DMA host table
 */
uint32_t STDCALL dma_host_deregister(DMA_HOST *dma);

DMA_HOST * STDCALL dma_host_find(uint32_t dmaid);
uint32_t STDCALL dma_host_enumerate(dma_enumerate_cb callback, void *data);

uint32_t STDCALL dma_host_notification(DMA_HOST *dma, dma_notification_cb callback, void *data, uint32_t notification, uint32_t flags);

/** DMA Data Functions */

/**
 * @brief Return the total number of data blocks in the linked list
 */
uint32_t STDCALL dma_data_count(DMA_DATA *data);

/**
 * @brief Return the combined flags of the data blocks in the linked list
 */
uint32_t STDCALL dma_data_flags(DMA_DATA *data);

/**
 * @brief Return the size of the largest data block in the linked list
 */
uint32_t STDCALL dma_data_maximum(DMA_DATA *data);

/** DMA Buffer Functions */

/**
 * @brief Allocate a data buffer for a DMA request
 * @param DMA The DMA host that the request will be sent to
 * @param Size The size of the data buffer to allocate
 * @return The newly allocated buffer or nil on failure
 */
void * STDCALL dma_buffer_allocate(DMA_HOST *dma, uint32_t size);

/**
 * @brief Allocate a data buffer for a DMA request
 * @param DMA The DMA host that the request will be sent to
 * @param Size The size of the data buffer to allocate (Updated on return to actual size)
 * @return The newly allocated buffer or nil on failure
 * @note This differs from DMABufferAllocate in that it updates the size value to reflect
 *        the actual size of the buffer allocated which may be required for some uses
 */
void * STDCALL dma_buffer_allocate_ex(DMA_HOST *dma, uint32_t *size);

/**
 * @brief Validate a data buffer for a DMA request against the DMA host requirements
 * @param DMA The DMA host that the request will be sent to
 * @param Buffer The data buffer to validate
 * @param Size The size of the data buffer
 * @return ERROR_SUCCESS on success or another error code on failure (ERROR_NOT_COMPATIBLE if not compatible with host)
 * @note Does not check for cache coherency requirements (Shared, Non Cached) only alignment and size.
 *        Buffers used as the source of a DMA request do not necessarily need to meet alignment and size
 *        requirements, however buffers used as a destination must meet these requirements or the caller
 *        must take appropriate actions to prevent undesirable side effects from cache invalidation.
 */
uint32_t STDCALL dma_buffer_validate(DMA_HOST *dma, void *buffer, uint32_t size);

/**
 * @brief Release a data buffer from a DMA request
 * @param Data The buffer to be released
 * @return ERROR_SUCCESS on success or another error code on failure
 */
uint32_t STDCALL dma_buffer_release(void *buffer);

/** DMA Request Functions */

/**
 * @brief Allocate a new DMA request
 * @param DMA The DMA host this request will be sent to
 * @param Data A linked list of DMA data blocks for the transfer (Optional)
 * @param Callback The callback function to be called on completion of the request
 * @param DriverData Driver private data for the callback (Optional)
 * @param Direction The direction of the DMA request (eg DMA_DIR_MEM_TO_MEM)
 * @param Peripheral The peripheral ID for data request gating (eg DMA_DREQ_ID_NONE)
 * @param Flags Additional flags for this request (eg DMA_REQUEST_FLAG_CYCLIC)
 * @return The newly allocated request or nil on failure
 */
DMA_REQUEST * STDCALL dma_request_allocate(DMA_HOST *dma, DMA_DATA *data, dma_request_completed_cb callback, void *driverdata, uint32_t direction, uint32_t peripheral, uint32_t flags);

/**
 * @brief Release and destroy a DMA request
 * @param Request The request to be released
 * @return ERROR_SUCCESS on success or another error code on failure
 */
uint32_t STDCALL dma_request_release(DMA_REQUEST *request);

/**
 * @brief Submit a DMA request to a DMA host
 * @param Request The request to be submitted
 * @return ERROR_SUCCESS if completed or another error code on failure
 * @note The request will be completed asynchronously by the DMA host and the
 *  completion callback will be called when the request has either succeeded or failed
 */
uint32_t STDCALL dma_request_submit(DMA_REQUEST *request);

/**
 * @brief Cancel a DMA request previously submitted to a DMA host
 * @param Request The request to be cancelled
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL dma_request_cancel(DMA_REQUEST *request);

/**
 * @brief Called by a DMA host when a DMA request completes
 * @param Request The DMA request which has completed
 * @note DMA host drivers may call this on a worker thread
 */
void STDCALL dma_request_complete(DMA_REQUEST *request);

/** DMA Transfer Functions */

/**
 * @brief Perform a DMA transfer request with the supplied data blocks on the supplied host
 * @param DMA The DMA host to execute the request on
 * @param Data A linked list of DMA data blocks for the transfer
 * @param Direction The direction of the DMA request (eg DMA_DIR_MEM_TO_MEM)
 * @param Peripheral The peripheral ID for data request gating (eg DMA_DREQ_ID_NONE)
 * @param Flags Additional flags for this transfer request (eg DMA_REQUEST_FLAG_CYCLIC)
 * @param Timeout Milliseconds to wait for request to complete (INFINITE to wait forever)
 * @note An internal callback will be specified and the function will wait for the transfer to complete
 */
uint32_t STDCALL dma_transfer_request(DMA_HOST *dma, DMA_DATA *data, uint32_t direction, uint32_t peripheral, uint32_t flags, uint32_t timeout);

/**
 * @brief Perform a DMA transfer request with the supplied data blocks on the supplied host
 * @param DMA The DMA host to execute the request on
 * @param Data A linked list of DMA data blocks for the transfer
 * @param Callback The callback function to be called on completion of the request
 * @param DriverData Driver private data for the callback (Optional)
 * @param Direction The direction of the DMA request (eg DMA_DIR_MEM_TO_MEM)
 * @param Peripheral The peripheral ID for data request gating (eg DMA_DREQ_ID_NONE)
 * @param Flags Additional flags for this transfer request (eg DMA_REQUEST_FLAG_CYCLIC)
 * @note The request will be passed to the callback with the DriverData field set to the DriverData passed to this function.
 *        On completion of the callback the request will automatically be released by the internal callback handler
 */
uint32_t STDCALL dma_transfer_request_ex(DMA_HOST *dma, DMA_DATA *data, dma_request_completed_cb callback, void *driverdata, uint32_t direction, uint32_t peripheral, uint32_t flags);

/**
 * @brief Called when a DMA transfer request completes
 * @param Request The DMA request which has completed
 * @note This is the internal callback for DMATransferRequest
 */
void STDCALL dma_transfer_request_complete(DMA_REQUEST *request);

/** DMA Helper Functions */

/**
 * @brief Get the current DMA host count
 */
uint32_t STDCALL dma_get_count(void);

/**
 * @brief Get the current default DMA host
 */
DMA_HOST * STDCALL dma_host_get_default(void);

/**
 * @brief Set the current default DMA device
 */
uint32_t STDCALL dma_host_set_default(DMA_HOST *dma);

/**
 * @brief Check if the supplied DMA is in the DMA host table
 */
DMA_HOST * STDCALL dma_host_check(DMA_HOST *dma);

/**
 * @brief Convert a DMA type value to a string
 */
uint32_t STDCALL dma_type_to_string(uint32_t dmatype, char *string, uint32_t len);

/**
 * @brief Convert a DMA state value to a string
 */
uint32_t STDCALL dma_state_to_string(uint32_t dmastate, char *string, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_DMA_H