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

#ifndef __ACAMERA_FRAME_STREAM_API_H__
#define __ACAMERA_FRAME_STREAM_API_H__

#include "acamera_aframe.h"

typedef struct frame_stream_plane_cfg_t {
    uint32_t width;         // Plane width
    uint32_t height;        // Plane height
    uint32_t line_offset;   // Plane line offset
    uint32_t data_width;    // Data bit width
    aplane_hw_cfg_t hw_cfg; // Hardware specific configuration
} frame_stream_plane_cfg_t;

typedef struct frame_stream_cfg_t {
    uint32_t context_id;                                // Context id
    aframe_type_t type;                                 // Frame type
    uint32_t num_planes;                                // Number of planes
    uint32_t num_frames;                                // Number of frames
    frame_stream_plane_cfg_t planes[AFRAME_MAX_PLANES]; // Planes information
} frame_stream_cfg_t;

/**
 * @brief   Type definition for frame stream API notify callback
 *
 * @param   ctx_id context id that has generated notification event
 * @param   type frame stream type that has generated notification event
 *
 * @details Function of this type should be implemented by frame consumer application and
 *          registered via register_notify_callback()
 */
typedef void ( *frame_stream_notify_callback )( const int ctx_id, const aframe_type_t type );

/**
 * @brief   Gets filled output buffer
 *
 * @param   ctx_id context id to query
 * @param   type frame type to get
 * @param   pointer to pointer to the aframe_t structure to be returned
 *
 * @return  0 on success
 *
 * @details This function should be called by a frame consumer application
 *          to get new filled output/raw buffer.
 */
int frame_stream_app_get_frame( const int ctx_id, const aframe_type_t type, aframe_t **frame );

/**
 * @brief   Puts (releases) processed (empty) output/raw buffer
 *
 * @param   frame pointer to aframe_t structure to be put
 *
 * @return  0 on success
 *
 * @details This function should be called by a frame consumer application
 *          to release previously acquired output/raw buffer.
 */
int frame_stream_app_put_frame( aframe_t *frame );

/**
 * @brief   Gets empty buffer
 *
 * @param   ctx_id context id to query
 * @param   type frame type to get
 * @param   pointer to pointer to the aframe_t structure to be returned
 *
 * @return  0 on success
 *
 * @details This function should be called by the ISP driver
 *          to get empty buffer
 */
int frame_stream_isp_get_frame( const int ctx_id, const aframe_type_t type, aframe_t **frame );

/**
 * @brief   Puts processed buffer
 *
 * @param   frame pointer to configured aframe_t structure
 *
 * @return  0 on success
 *
 * @details This function should be called by the ISP driver
 *          to put processed buffer
 */
int frame_stream_isp_put_frame( aframe_t *frame );

/**
 * @brief   Registers filled buffer notification callback
 *
 * @param   callback pointer to frame_stream_notify_callback function
 *
 * @return  0 on success
 *
 * @details This function should be called by frame consumer application
 *          to register filled buffer notification callback. Callback is called
 *          every time when there is a new filled output/raw buffer ready
 */
int frame_stream_register_notify_callback( frame_stream_notify_callback callback );

/**
 * @brief   Creates frame stream based on configuration
 *
 * @param   stream_cfg stream configuration for the new steam to be created

 * @return  0 on success
 *
 * @details This function should be called by ISP driver to create frame stream before
 *          calling functions *_get|put_frame()
 */
int frame_stream_create( const frame_stream_cfg_t *stream_cfg );

/**
 * @brief   Destroys specified frame stream
 *
 * @param   ctx_id context id to destroy stream of
 * @param   type frame stream type to destroy
 * @param   force will destroy buffers without keeping used buffers to delayed reclaim if set to non-zero
 *
 * @return  0 on success
 *
 * @details This function should be called by ISP driver to destroy frame stream
 *          when frame stream parameters changes or as a part of the deinitialization
 */
int frame_stream_destroy( const int ctx_id, const aframe_type_t type, const int force );

#endif // __ACAMERA_FRAME_STREAM_API_H__