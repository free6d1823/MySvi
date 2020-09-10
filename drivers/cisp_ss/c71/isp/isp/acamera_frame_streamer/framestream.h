// #include <stdint.h>

//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2019] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifndef __FRAMESTREAM_H__
#define __FRAMESTREAM_H__

#include "system_semaphore.h"
#include "system_types.h"
#include "acamera_aframe.h"
#include "util_pool.h"
#include "util_queue.h"

#if 0//__KERNEL__
#include "linux/mutex.h"
#endif

#define FRAMESTREAM_MAX_FRAMES 10

typedef struct {
#if 0//__KERNEL__
    struct mutex lock; //Linux kernel lock
#else
    void *lock; //Empty lock
#endif
} framestream_mutex;

typedef struct {
    aqueue empty_queue;                                          // Empty queue
    aframe_t *empty_queue_data[FRAMESTREAM_MAX_FRAMES];          // Empty queue elements
    aqueue filled_queue;                                         // Full queue
    aframe_t *filled_queue_data[FRAMESTREAM_MAX_FRAMES];         // Full queue elements
    apool active_pool;                                           // Active pool
    apool_element active_pool_elements[FRAMESTREAM_MAX_FRAMES];  // Active pool elements
    apool reclaim_pool;                                          // Reclaim pool
    apool_element reclaim_pool_elements[FRAMESTREAM_MAX_FRAMES]; // Reclaim pool elements
    framestream_mutex empty_queue_lock;                          // Empty queue lock
    framestream_mutex filled_queue_lock;                         // Full queue lock
    framestream_mutex active_pool_lock;                          // Active pool lock
    framestream_mutex reclaim_pool_lock;                         // Reclaim pool lock
    uint32_t max_frames;
} framestream;

typedef struct framestream_plane_cfg_t {
    uint32_t width;         // Plane width
    uint32_t height;        // Plane height
    uint32_t line_offset;   // Plane line offset
    uint32_t data_width;    // Data bit width
    aplane_hw_cfg_t hw_cfg; // Hardware specific configuration
} framestream_plane_cfg_t;

typedef struct framestream_cfg_t {
    uint32_t context_id;                               // Context id
    aframe_type_t type;                                // Frame type
    uint32_t num_planes;                               // Number of planes
    uint32_t num_frames;                               // Number of frames requested
    framestream_plane_cfg_t planes[AFRAME_MAX_PLANES]; // Planes information
} framestream_cfg_t;

/**
 * @brief   Initializes framestream data_type
 *
 * @param   hndl handle to framestream data type
 * @param   frame_storage array of frames
 * @param   frame_storage_size size of frame array
 * @param   frm_cfg frame stream configuration
 *
 * @return  0 on success
 *
 * @details This function should be called when initializing a framestream data type
 */
int framestream_create( framestream *hndl, aframe_t *frame_storage, uint32_t frame_storage_size, framestream_cfg_t *frm_cfg );

/**
 * @brief   Destroys framestream data_type
 *
 * @param   hndl handle to framestream data type
 * @param   full_destroy flag that denotes complete frame destruction -
 *          frames would not be moved to reclaim pool.
 *
 * @return  0 on success
 *
 * @details This function should be called when de-initializing a framestream data type
 */
void framestream_destroy( framestream *hndl, uint32_t full_destroy );

/**
 * @brief   Enqueues an empty frame
 *
 * @param   hndl handle to framestream data type
 * @param   data ptr to the frame
 *
 * @return  0 on success
 *
 * @details This function should be called by framestreamer when enqueueing an empty frame
 */
int framestream_enqueue_empty( framestream *hndl, aframe_t *data );

/**
 * @brief   Dequeue an empty frame
 *
 * @param   hndl handle to framestream data type
 *
 * @return  0 on success
 *
 * @details This function should be called by framestreamer when dequeueing an empty frame
 */
aframe_t *framestream_dequeue_empty( framestream *hndl );

/**
 * @brief   Enqueues an filled frame
 *
 * @param   hndl handle to framestream data type
 * @param   data ptr to the frame
 *
 * @return  0 on success
 *
 * @details This function should be called by framestreamer when enqueueing a filled frame
 */
int framestream_enqueue_filled( framestream *hndl, aframe_t *data );

/**
 * @brief   Dequeues an filled frame
 *
 * @param   hndl handle to framestream data type
 *
 * @return  0 on success
 *
 * @details This function should be called by framestreamer when dequeueing a filled frame
 */
aframe_t *framestream_dequeue_filled( framestream *hndl );

/**
 * @brief   Returns size of active pool
 *
 * @param   hndl handle to framestream data type
 *
 * @return  0 on success
 *
 * @details This function should be called by framestreamer when checking active pool size
 */
uint32_t framestream_active_size( framestream *hndl );

/**
 * @brief   Returns size of reclaim pool
 *
 * @param   hndl handle to framestream data type
 *
 * @return  0 on success
 *
 * @details This function should be called by framestreamer when checking reclaim pool size
 */
uint32_t framestream_reclaim_size( framestream *hndl );

#endif // __FRAMESTREAM_H__
