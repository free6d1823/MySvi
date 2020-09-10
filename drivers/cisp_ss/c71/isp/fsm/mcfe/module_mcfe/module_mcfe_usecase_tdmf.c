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

/**************************************************
 * Headers
 **************************************************/
#include "acamera_configuration.h"
#include "acamera_isp_config.h"
#include "module_mcfe.h"
#include "module_mcfe_service.h" // Types
#include "module_mcfe_usecase.h" // module_mcfe_usecase_functbl_t

#define BUFSET_RAW_FRAME_COUNT ( 2 )
#define BUFSET_OUT_FRAME_COUNT ( 1 )
#define FRAME_STREAM_RAW_FRAME_COUNT ( BUFSET_RAW_FRAME_COUNT )
#define FRAME_STREAM_OUT_FRAME_COUNT ( BUFSET_OUT_FRAME_COUNT + 1 )

static int release_streams_frames_bufsets( module_mcfe_usecase_config_t *config, const int force )
{
    // Check configuration pointer
    if ( !config ) {
        LOG( LOG_ERR, "Failed to release streams, frames and buffer sets. Use-case configuration data pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Deallocating buffer sets and releasing frames
    if ( ( config->config_states.curr & MODULE_MCFE_USECASE_RAW_BUFSET_CONFIGURED ) && config->bufset_raw ) {
        module_mcfe_bufset_frames_t frames = {0};

        if ( module_mcfe_bufset_get_frames( config->bufset_raw, &frames ) != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Failed to get frame description structure from raw buffer set." );
        } else {
            int i;
            for ( i = 0; i < frames.num_frames; i++ ) {
                frames.frame[i]->state = AFRAME_STATE_EMPTY;
                frame_stream_isp_put_frame( frames.frame[i] );
            }
        }

        if ( module_mcfe_bufset_destroy( config->bufset_raw ) != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Failed to destroy buffer raw buffer set." );
        }

        config->bufset_raw = NULL;
        config->config_states.curr &= ( ~MODULE_MCFE_USECASE_RAW_BUFSET_CONFIGURED );
    }

    if ( ( config->config_states.curr & MODULE_MCFE_USECASE_OUT_BUFSET_CONFIGURED ) && config->bufset_out ) {
        module_mcfe_bufset_frames_t frames = {0};

        if ( module_mcfe_bufset_get_frames( config->bufset_out, &frames ) != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Failed to get frame description structure from out buffer set." );
        } else {
            int i;
            for ( i = 0; i < frames.num_frames; i++ ) {
                frames.frame[i]->state = AFRAME_STATE_EMPTY;
                frame_stream_isp_put_frame( frames.frame[i] );
            }
        }

        if ( module_mcfe_bufset_destroy( config->bufset_out ) != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Failed to destroy buffer out buffer set." );
        }

        config->bufset_out = NULL;
        config->config_states.curr &= ( ~MODULE_MCFE_USECASE_OUT_BUFSET_CONFIGURED );
    }

    // Destroy frame streams
    if ( config->config_states.curr & MODULE_MCFE_USECASE_RAW_STREAM_CONFIGURED ) {
        if ( frame_stream_destroy( config->slot_id, AFRAME_TYPE_RAW, force ) ) {
            LOG( LOG_ERR, "Failed to destroy raw frame stream." );
        }

        config->config_states.curr &= ( ~MODULE_MCFE_USECASE_RAW_STREAM_CONFIGURED );
    }

    if ( config->config_states.curr & MODULE_MCFE_USECASE_OUT_STREAM_CONFIGURED ) {
        if ( frame_stream_destroy( config->slot_id, AFRAME_TYPE_OUT, force ) ) {
            LOG( LOG_ERR, "Failed to destroy output frame stream." );
        }

        config->config_states.curr &= ( ~MODULE_MCFE_USECASE_OUT_STREAM_CONFIGURED );
    }

    return MCFE_ERR_NONE;
}

static int module_mcfe_usecase_config_impl( module_mcfe_usecase_config_t *config, module_mcfe_sensor_cfg_t *sensor_config, module_mcfe_output_cfg_t *output_config )
{
    frame_stream_cfg_t frame_stream_cfg = {0};
    module_mcfe_input_cfg_t input_cfg = {0};
    module_mcfe_slot_cfg_t slot_cfg = {0};
    aframe_t *raw_frames[BUFSET_RAW_FRAME_COUNT] = {NULL};
    aframe_t *out_frames[BUFSET_OUT_FRAME_COUNT] = {NULL};

    int rc, i;

    // Check configuration pointers
    if ( !config || !sensor_config || !output_config ) {
        LOG( LOG_ERR, "Failed to configure TDMF use-case. Input parameter pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Check if usecase configuration initialised
    if ( !config->initialized ) {
        LOG( LOG_ERR, "Failed to configure TDMF use-case. Use-case configuration data is not initialised." );
        return MCFE_ERR_NOT_INIT;
    }

    // Check if there is enough MCFE input channels available
    int free_input_count = module_mcfe_slot_get_free_inputs( config->slot_id );
    if ( sensor_config->num_channel > free_input_count ) {
        LOG( LOG_ERR, "Failed to configure TDMF use-case. Not enough free MCFE input channels available (required: %d, available: %d).",
             sensor_config->num_channel,
             free_input_count );

        return MCFE_ERR_GENERAL;
    }

    LOG( LOG_INFO, "Configuring TDMF use-case (context id: %u, channels: %d)", config->slot_id, sensor_config->num_channel );

    // Check if we need to deallocate inputs first.
    // This should be done before raw frame buffer allocation/deallocation
    if ( config->config_states.curr & MODULE_MCFE_USECASE_INPUT_CONFIGURED ) {
        rc = module_mcfe_input_remove_video( config->video_input_idx, &( config->input_port_ids ), &input_cfg );
        if ( rc != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Error, fail to remove video inputs." );
            return rc;
        } else {
            config->config_states.curr &= ( ~MODULE_MCFE_USECASE_INPUT_CONFIGURED );
        }
    }

    // Check if any frames or buffer sets resources were previously allocated and release
    if ( release_streams_frames_bufsets( config, 0 ) != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, failed to release streams, frames and buffer sets." );
        return MCFE_ERR_GENERAL;
    }

    // Output frame stream config header
    frame_stream_cfg.num_planes = output_config->num_planes;
    frame_stream_cfg.context_id = config->slot_id;
    frame_stream_cfg.type = AFRAME_TYPE_OUT;
    frame_stream_cfg.num_frames = FRAME_STREAM_OUT_FRAME_COUNT;

    size_t plane;
    for ( plane = 0; plane < output_config->num_planes; plane++ ) {

        frame_stream_plane_cfg_t *plane_cfg = &( frame_stream_cfg.planes[plane] );

        if ( output_config->plane[plane].h_subsampling == 0 ) {
            output_config->plane[plane].h_subsampling = 1;
        }

        if ( output_config->plane[plane].v_subsampling == 0 ) {
            output_config->plane[plane].v_subsampling = 1;
        }

        plane_cfg->hw_cfg.axi = output_config->plane[plane].axi;
        plane_cfg->hw_cfg.flags = ( output_config->plane[plane].msb_align ) ? ( AFRAME_HW_FLAG_MSB_ALIGN ) : 0;
        plane_cfg->data_width = output_config->plane[plane].data_width;

#ifdef ACAMERA_ISP_OUT_FORMAT_LPF_YUV_ENABLE_VERT_DOWNSAMPLE_DEFAULT
        if ( output_config->crop.enabled ) {
            plane_cfg->width = output_config->crop.width / output_config->plane[plane].h_subsampling;
            plane_cfg->height = output_config->crop.height / output_config->plane[plane].v_subsampling;
        } else {
            plane_cfg->width = sensor_config->width / output_config->plane[plane].h_subsampling;
            plane_cfg->height = sensor_config->height / output_config->plane[plane].v_subsampling;
        }

        /* We don't want to divide line width with subsampling factor because ISP R1 is adding 2 lines. */
        plane_cfg->line_offset = AFRAME_ALIGN_PLANE( plane_cfg->width * plane_cfg->data_width / 8 );
#else
        if ( output_config->crop.enabled ) {
            plane_cfg->width = output_config->crop.width;
            plane_cfg->height = output_config->crop.height / output_config->plane[plane].v_subsampling;
        } else {
            plane_cfg->width = sensor_config->width;
            plane_cfg->height = sensor_config->height / output_config->plane[plane].v_subsampling;
        }
        plane_cfg->line_offset = AFRAME_ALIGN_PLANE( plane_cfg->width * plane_cfg->data_width / output_config->plane[plane].v_subsampling / 8 );
#endif
    }

    if ( frame_stream_create( &frame_stream_cfg ) != 0 ) {
        LOG( LOG_ERR, "Error, failed to create output frame stream." );
        return MCFE_ERR_GENERAL;
    } else {
        config->config_states.curr |= MODULE_MCFE_USECASE_OUT_STREAM_CONFIGURED;
    }

    // Configure inputs.
    config->video_input_idx = sensor_config->video_port_id;
    input_cfg.num_channel = sensor_config->num_channel;
    input_cfg.is_reverse_order = sensor_config->is_reverse_order;
    input_cfg.msb_align = MODULE_MCFE_MSB_ALIGN_INPUT;
    input_cfg.data_width = sensor_config->data_width;
    input_cfg.h_start = sensor_config->h_start;
    input_cfg.h_size = sensor_config->width;
    input_cfg.v_start = sensor_config->v_start;
    input_cfg.v_size = sensor_config->height;
    input_cfg.active_width = sensor_config->width + sensor_config->h_start;
    input_cfg.active_height = sensor_config->height + sensor_config->v_start;
    input_cfg.rggb_start = sensor_config->rggb_start;
    input_cfg.cfa_pattern = sensor_config->cfa_pattern;

    // Raw frame stream config header
    frame_stream_cfg.num_planes = sensor_config->num_channel;
    frame_stream_cfg.context_id = config->slot_id;
    frame_stream_cfg.type = AFRAME_TYPE_RAW;
    frame_stream_cfg.num_frames = FRAME_STREAM_RAW_FRAME_COUNT;

    // Allocate raw-buffers.
    for ( i = 0; i < frame_stream_cfg.num_planes; i++ ) {

        frame_stream_plane_cfg_t *plane_cfg = &( frame_stream_cfg.planes[i] );

        plane_cfg->hw_cfg.flags = AFRAME_HW_FLAG_MSB_ALIGN;
        plane_cfg->data_width = sensor_config->data_width;
        plane_cfg->width = sensor_config->width;
        plane_cfg->height = sensor_config->height;
        plane_cfg->line_offset = AFRAME_ALIGN_PLANE( plane_cfg->width * plane_cfg->data_width / 8 );
    }

    if ( frame_stream_create( &frame_stream_cfg ) != 0 ) {
        LOG( LOG_ERR, "Error, failed to create raw frame stream." );
        return MCFE_ERR_GENERAL;
    } else {
        config->config_states.curr |= MODULE_MCFE_USECASE_RAW_STREAM_CONFIGURED;
    }

    // Get raw frames from the raw frame stream ( 2 raw frames)
    for ( i = 0; i < BUFSET_RAW_FRAME_COUNT; i++ ) {
        if ( frame_stream_isp_get_frame( config->slot_id, AFRAME_TYPE_RAW, &raw_frames[i] ) ) {
            LOG( LOG_ERR, "Error, failed to get frame %d from the raw frame stream.", i );
            return MCFE_ERR_GENERAL;
        }
    }

    // Get output frames from the output frame stream ( 2 output frames )
    for ( i = 0; i < BUFSET_OUT_FRAME_COUNT; i++ ) {
        if ( frame_stream_isp_get_frame( config->slot_id, AFRAME_TYPE_OUT, &out_frames[i] ) ) {
            LOG( LOG_ERR, "Error, failed to get frame %d from the out frame stream.", i );
            return MCFE_ERR_GENERAL;
        }
    }

    // Create raw buffer set
    if ( module_mcfe_bufset_create( raw_frames, &( config->bufset_raw ), BUFSET_RAW_FRAME_COUNT ) ) {
        LOG( LOG_ERR, "Error, failed to create raw buffer set." );
        return MCFE_ERR_GENERAL;
    } else {
        config->config_states.curr |= MODULE_MCFE_USECASE_RAW_BUFSET_CONFIGURED;
    }

    // Create out buffer set
    if ( module_mcfe_bufset_create( out_frames, &( config->bufset_out ), BUFSET_OUT_FRAME_COUNT ) ) {
        LOG( LOG_ERR, "Error, failed to create out buffer set." );
        return MCFE_ERR_GENERAL;
    } else {
        config->config_states.curr |= MODULE_MCFE_USECASE_OUT_BUFSET_CONFIGURED;
    }

    // Add videos to inputs.
    rc = module_mcfe_input_add_video( config->video_input_idx, &( config->input_port_ids ), &input_cfg );
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, fail to add video to input." );
        return rc;
    } else {
        config->config_states.curr |= MODULE_MCFE_USECASE_INPUT_CONFIGURED;
    }

    // Add buffers to inputs.
    rc = module_mcfe_input_config_buffer( &( config->input_port_ids ), config->bufset_raw );
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, fail to configure input's buffers." );
        return rc;
    }

    // Create slot.
    slot_cfg.hist_position_is_be = config->hist_position_is_be;
    slot_cfg.slot_mode = config->slot_mode;
    slot_cfg.is_remote = sensor_config->is_remote;
    slot_cfg.is_reverse_order = sensor_config->is_reverse_order;
    slot_cfg.rggb_start = sensor_config->rggb_start;
    slot_cfg.cfa_pattern = sensor_config->cfa_pattern;
    slot_cfg.num_input = sensor_config->num_channel;
    slot_cfg.cdma_addr = sensor_config->cdma_addr;
    slot_cfg.num_output = output_config->num_planes;
    slot_cfg.slot_bufset_out = config->bufset_out;
    slot_cfg.slot_bufset_raw = config->bufset_raw;

    for ( i = 0; i < config->input_port_ids.count; i++ ) {
        slot_cfg.slot_input_port_id[i] = config->input_port_ids.ids[i];
    }

    slot_cfg.slot_bufset_out = config->bufset_out;

    // Check if slot was previously allocated
    if ( config->config_states.curr & MODULE_MCFE_USECASE_SLOT_CONFIGURED ) {
        rc = module_mcfe_slot_set_config( config->slot_id, &slot_cfg );
        if ( rc != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Error, failed to update slot configuration." );
            return rc;
        }
    } else {
        rc = module_mcfe_slot_create( config->slot_id, &slot_cfg );
        if ( rc != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Error, failed to create slot." );
            return rc;
        } else {
            config->config_states.curr |= MODULE_MCFE_USECASE_SLOT_CONFIGURED;
        }
    }

    config->sensor_config = *sensor_config;
    config->output_config = *output_config;

    config->config_states.last = config->config_states.curr;

    return MCFE_ERR_NONE;
}

static int module_mcfe_usecase_start_impl( module_mcfe_usecase_config_t *config )
{
    int rc = MCFE_ERR_NONE;

    // Check configuration pointer
    if ( !config ) {
        LOG( LOG_ERR, "Failed to start TDMF use-case. Use-case configuration data pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Check if usecase already started
    if ( config->started ) {
        return rc;
    }

    // Check if usecase configured
    if ( config->config_states.curr != config->config_states.reqd ) {
        if ( config->config_states.curr != config->config_states.last ) {
            LOG( LOG_ERR, "Failed to start TDMF use-case (context id: %u, current config: %u, required config: %u). Use-case is not fully configured.",
                 config->slot_id,
                 config->config_states.curr,
                 config->config_states.reqd );
            config->config_states.last = config->config_states.curr;
        }
        return MCFE_ERR_NOT_INIT;
    }

    // Start slot
    rc = module_mcfe_slot_start( config->slot_id );
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, failed to start slot (context id: %u).", config->slot_id );
        return rc;
    }

    // Start input videos.
    rc = module_mcfe_input_start_video( config->video_input_idx );
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, failed to start video %d (context id: %u).", config->video_input_idx, config->slot_id );
    }

    config->started = 1;

    return rc;
}

static int module_mcfe_usecase_stop_impl( module_mcfe_usecase_config_t *config )
{
    int rc = MCFE_ERR_NONE;

    // Check configuration pointer
    if ( !config ) {
        LOG( LOG_ERR, "Failed to stop TDMF use-case. Use-case configuration data pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Check if usecase already stopped
    if ( !config->started ) {
        return rc;
    }

    // Check if usecase configured
    if ( config->config_states.curr != config->config_states.reqd ) {
        if ( config->config_states.curr != config->config_states.last ) {
            LOG( LOG_ERR, "Failed to stop TDMF use-case (context id: %u, current config: %u, required config: %u). Use-case is not fully configured.",
                 config->slot_id,
                 config->config_states.curr,
                 config->config_states.reqd );
            config->config_states.last = config->config_states.curr;
        }
        return MCFE_ERR_NOT_INIT;
    }

    // Stop input videos.
    rc = module_mcfe_input_stop_video( config->video_input_idx );
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, failed to stop video %d (context id: %u).", config->video_input_idx, config->slot_id );
    }

    // Stop slot
    rc = module_mcfe_slot_stop( config->slot_id );
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, failed to stop slot (context id: %u).", config->slot_id );
    }

    config->started = 0;

    return rc;
}

static int module_mcfe_usecase_release_resources_impl( module_mcfe_usecase_config_t *config )
{

    // Check configuration pointer
    if ( !config ) {
        LOG( LOG_ERR, "Failed to release resources of TDMF use-case. Use-case configuration data pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    return release_streams_frames_bufsets( config, 0 );
}

/**************************************************
 * Event processor
 **************************************************/
static int module_mcfe_usecase_process_event( module_mcfe_usecase_config_t *config, module_mcfe_event_t event )
{
    int rc = MCFE_ERR_NONE;

    // Check configuration pointer
    if ( !config ) {
        LOG( LOG_ERR, "Failed process event for TDMF use-case. Use-case configuration data pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Check if usecase already started
    if ( !config->started ) {
        LOG( LOG_ERR, "Failed to process TDMF use-case event (context id: %u). Use-case is not started.", config->slot_id );
        return MCFE_ERR_NOT_RUN;
    }

    // Check if usecase configured
    if ( config->config_states.curr != config->config_states.reqd ) {
        LOG( LOG_ERR, "Failed to process TDMF use-case event (context id: %u, current config: %u, required config: %u). Use-case is not fully configured.",
             config->slot_id,
             config->config_states.curr,
             config->config_states.reqd );
        return MCFE_ERR_NOT_INIT;
    }

    if ( event == MODULE_MCFE_EVENT_OUT_BUFFER_READY ) {

        aframe_t *empty_frame = NULL, *filled_frame = NULL;
        if ( frame_stream_isp_get_frame( config->slot_id, AFRAME_TYPE_OUT, &empty_frame ) ) {
            LOG( LOG_ERR, "Failed to get empty output buffer from the frame streamer (context id: %u). Current buffers will be reused.", config->slot_id );

            if ( module_mcfe_bufset_set_buf_status( config->bufset_out, MCFE_BUFSET_STATUS_EMPTY ) != MCFE_ERR_NONE ) {
                LOG( LOG_ERR, "Failed to set buffers of the buffer set to empty state (context id: %u).", config->slot_id );
            }
        } else {

            if ( module_mcfe_bufset_swap( empty_frame, &filled_frame, config->bufset_out, MCFE_BUFSET_SWAP_EMPTY_IN_FILLED_OUT ) != MCFE_ERR_NONE ) {
                LOG( LOG_ERR, "Failed to swap buffers (context id: %u).", config->slot_id );

                empty_frame->state = AFRAME_STATE_EMPTY;
                frame_stream_isp_put_frame( empty_frame );

                return MCFE_ERR_GENERAL;
            }

            filled_frame->state = AFRAME_STATE_FULL;
            frame_stream_isp_put_frame( filled_frame );
        }
    }

    return rc;
}

/**************************************************
 * Init, deinit
 **************************************************/
int module_mcfe_usecase_init_tdmf( module_mcfe_usecase_config_t *config, mcfe_slot_id_t slot_id, int hist_position_is_be )
{
    // Check configuration pointer
    if ( !config ) {
        LOG( LOG_ERR, "Failed to initialise TDMF use-case. Use-case configuration data pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Initialize use-case instance
    system_memset( config, 0x0, sizeof( *config ) );

    // Initialize MCFE instance.
    config->functions.config = module_mcfe_usecase_config_impl;
    config->functions.start = module_mcfe_usecase_start_impl;
    config->functions.stop = module_mcfe_usecase_stop_impl;
    config->functions.process_event = module_mcfe_usecase_process_event;
    config->functions.release_resources = module_mcfe_usecase_release_resources_impl;

    config->type = MODULE_MCFE_USECASE_TDMF;
    config->slot_mode = MODULE_MCFE_SLOT_MODE_TDMF_FLEX;
    config->slot_id = slot_id;
    config->hist_position_is_be = hist_position_is_be;

    config->config_states.reqd = ( MODULE_MCFE_USECASE_RAW_STREAM_CONFIGURED |
                                   MODULE_MCFE_USECASE_OUT_STREAM_CONFIGURED |
                                   MODULE_MCFE_USECASE_RAW_BUFSET_CONFIGURED |
                                   MODULE_MCFE_USECASE_OUT_BUFSET_CONFIGURED |
                                   MODULE_MCFE_USECASE_SLOT_CONFIGURED |
                                   MODULE_MCFE_USECASE_INPUT_CONFIGURED );

    config->initialized = 1;

    return MCFE_ERR_NONE;
}

int module_mcfe_usecase_deinit_tdmf( module_mcfe_usecase_config_t *config )
{
    // Check configuration pointer
    if ( !config ) {
        LOG( LOG_ERR, "Failed to deinitialize TDMF use-case. Use-case configuration data pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Release frames and buffer sets
    if ( release_streams_frames_bufsets( config, 1 ) != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Failed to release streams, frames and buffer sets of manual use-case (context id: %u).", config->slot_id );
    }

    // Initialize use-case instance
    system_memset( config, 0x0, sizeof( *config ) );

    return MCFE_ERR_NONE;
}
