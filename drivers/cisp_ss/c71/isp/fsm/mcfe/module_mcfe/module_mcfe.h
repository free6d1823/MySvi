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

#ifndef _MODULE_MCFE_H_
#define _MODULE_MCFE_H_

#include "acamera_isp_core_settings.h"
#include "module_mcfe_common.h"

typedef enum {
    MODULE_MCFE_EVENT_RAW_BUFFER_READY = 1,
    MODULE_MCFE_EVENT_OUT_BUFFER_READY,
    MODULE_MCFE_EVENT_MAX = MODULE_MCFE_EVENT_OUT_BUFFER_READY
} module_mcfe_event_t;

// MCFE config data type
typedef struct _module_mcfe_sensor_cfg_t {
    int h_start;
    int v_start;
    int is_remote;
    int num_channel;
    int is_reverse_order;
    int video_port_id;
    int data_width;
    int width;
    int height;
    int rggb_start;
    int cfa_pattern;
    int cdma_addr;
} module_mcfe_sensor_cfg_t;

typedef struct {
    uint8_t data_width;
    uint8_t msb_align;
    uint8_t h_subsampling;
    uint8_t v_subsampling;
    uint8_t axi;
    uint8_t axi_mode;
    uint8_t axi_format;
} module_mcfe_plane_info_t;

typedef struct {
    uint8_t enabled;
    uint32_t startx;
    uint32_t starty;
    uint32_t width;
    uint32_t height;
} output_crop_t;

typedef struct {
    uint8_t format;
    uint8_t num_planes;
    output_crop_t crop;
    module_mcfe_plane_info_t plane[ISP_MCFE_HWIF_MAX_OUTPUTS];
} module_mcfe_output_cfg_t;

typedef struct _module_mcfe_config_t {
    unsigned char initialized;
    unsigned char running;
    int video_input_table[MODULE_MCFE_INPUT_PORT_MAX];

} module_mcfe_config_t;

// Init, deinit
int module_mcfe_init( void );
int module_mcfe_deinit( void );

// Control, config interface
int module_mcfe_start( void );
int module_mcfe_stop( void );

// Resource related functions
/**
 *   Get slot id for specified MCFE input channel
 *   If first_only is set only returns positive result if input is the first slot input
 */
int module_mcfe_get_slot_id_for_input( int input, int first_only );

/**
 *   Get input channel id for specified slot id
 */
int module_mcfe_get_input_for_slot_id( int slot_id );

/**
 *   Updates usage of MCFE input channels
 *
 *   Finds all slots corresponding to MCFE input channels and updates internal input table
 *
 */
int module_mcfe_update_inputs( void );

/**
 *   Get number of free inputs available for specified slot
 *
 *   If slot_id a valid slot id function will return sum of slot inputs and free inputs
 *   If slot_id is not a valid slot id function will return number of free inputs
 *
 */
int module_mcfe_get_free_inputs_for_slot_id( int slot_id );

#endif
