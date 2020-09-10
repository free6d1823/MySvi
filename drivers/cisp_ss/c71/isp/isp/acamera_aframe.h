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

#ifndef __ACAMERA_AFRAME_H__
#define __ACAMERA_AFRAME_H__

#include "system_types.h"

#define AFRAME_MAX_PLANES ( 4 )

// Frame plane alignment requirements due to DMA engine access
#define AFRAME_PLANE_ALIGNMENT ( 32 )

#define AFRAME_ALIGN_PLANE( val )                \
    ( ( ( val ) + AFRAME_PLANE_ALIGNMENT - 1 ) - \
      ( ( ( val ) + AFRAME_PLANE_ALIGNMENT - 1 ) % AFRAME_PLANE_ALIGNMENT ) )

typedef enum aframe_hw_flags_t {
    AFRAME_HW_FLAG_MSB_ALIGN = ( 1 << 0 ), // HW specific flag MSB_ALIGN
    AFRAME_HW_FLAG_POOL = ( 1 << 1 ),      // HW specific flag POOL
    AFRAME_HW_FLAG_CLONE = ( 1 << 2 ),     // HW specific flag CLONE
    AFRAME_HW_FLAG_INFINITE = ( 1 << 3 )   // HW specific flag INFINITE
} aframe_hw_flags_t;

typedef enum {
    AFRAME_TYPE_UNKNOWN, // Default value, unknown type
    AFRAME_TYPE_RAW,     // Raw frame type
    AFRAME_TYPE_OUT,     // Output frame type
    AFRAME_TYPE_MAX      // Max type value
} aframe_type_t;

typedef enum {
    AFRAME_STATE_UNKNOWN, // Default value, unknown state
    AFRAME_STATE_EMPTY,   // Frame is empty
    AFRAME_STATE_FULL,    // Frame is full
    AFRAME_STATE_MAX      // Max state value
} aframe_state_t;

typedef struct aplane_hw_cfg_t {
    uint32_t axi;   // AXI output used
    uint32_t flags; // HW buffer flags
} aplane_hw_cfg_t;

typedef struct aplane_t {
    void *private;          // Embedded plane private data
    uint32_t width;         // Plane width
    uint32_t height;        // Plane height
    uint32_t line_offset;   // Plane line offset
    uint32_t data_width;    // Plane data width
    uint32_t length;        // Total plane size in bytes (not payload)
    uint32_t bytes_used;    // Number of bytes used
    uint32_t data_offset;   // Offset in the plane to the start of data
    uint32_t address;       // Start of memory block
    void *virt_addr;        // Virtual memory address if present
    aplane_hw_cfg_t hw_cfg; // Hardware specific configuration
} aplane_t;

typedef struct aframe_t {
    void *private;                      // embedded frame private data
    uint32_t context_id;                // context id
    aframe_type_t type;                 // frame type
    uint32_t format;                    // frame format
    aframe_state_t state;               // frame state
    uint32_t frame_id;                  // frame id (sequence)
    uint32_t num_planes;                // number of planes
    aplane_t planes[AFRAME_MAX_PLANES]; // planes information
} aframe_t;

#endif // __ACAMERA_AFRAME_H__