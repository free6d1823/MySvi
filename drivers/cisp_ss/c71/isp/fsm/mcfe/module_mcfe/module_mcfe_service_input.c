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
#include "system_timer.h"
#include "acamera_math.h"
#include "module_mcfe_common.h"
#include "module_mcfe_hwif.h"
#include "module_mcfe_service.h"
#include "util/math/acamera_math.h"
/**************************************************
 * Static types and globals
 **************************************************/
typedef struct _module_mcfe_video_input_t {
    unsigned char enabled;
    unsigned char started;
    module_mcfe_input_port_ids_t input_port_ids;
    module_mcfe_input_cfg_t input_cfg;
} module_mcfe_video_input_t;

typedef struct _module_mcfe_input_port_t {
    unsigned char enabled;
    unsigned char video_input_idx;
    const module_mcfe_bufset_t *input_bufset;
} module_mcfe_input_port_t;

static module_mcfe_video_input_t mcfe_video_input[MODULE_MCFE_INPUT_PORT_MAX];
static module_mcfe_input_port_t mcfe_input_port[MODULE_MCFE_INPUT_PORT_MAX];

/**************************************************
 * Input control interface
 **************************************************/
int module_mcfe_input_init( void )
{
    int i;
    int tries = 100;

    // Reset software information.
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        // Reset input video.
        mcfe_video_input[i].enabled = 0;
        mcfe_video_input[i].started = 0;
        mcfe_video_input[i].input_port_ids.count = 0;
        mcfe_video_input[i].input_cfg.num_channel = 0;

        // Reset input.
        mcfe_input_port[i].enabled = 0;
        mcfe_input_port[i].video_input_idx = 0;
        mcfe_input_port[i].input_bufset = NULL;
    }

    // Stop input port.
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        mcfe_hwif_input_port_set_mode( i, MODULE_MCFE_HWIF_VIDEOINPUT_MODE_SAFE_STOP );
    }

    // Sleep 10 fps frametime.
    system_timer_usleep( 100000 );

    // Wait input port to stop for max 100ms.
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        // Wait for input port to stop.
        while ( mcfe_hwif_input_port_get_status( i ) ) {
            system_timer_usleep( 1000 );
            if ( 0 == tries ) {
                break;
            }
            tries--;
        }
    }

    // Reset hardware information.
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        // Reset MCFE input configuration.
        mcfe_hwif_input_config( i, 0, 1, 12 ); // Input, mode, msb_align, data_width
        mcfe_hwif_input_wrbuf_set( i, 0xff, 0xff );

        // Reset input port & crossbar configuration.
        mcfe_hwif_input_port_config( i, 0,                                                     // Input, aclg_window2
                                     MODULE_MCFE_DEFAULT_HC_START, MODULE_MCFE_DEFAULT_WIDTH,  // hc_start1, hc_size0
                                     MODULE_MCFE_DEFAULT_HC_START, MODULE_MCFE_DEFAULT_WIDTH,  // hc_start1, hc_size1
                                     MODULE_MCFE_DEFAULT_VC_START, MODULE_MCFE_DEFAULT_HEIGHT, // vc_start, vc_size
                                     0, i );                                                   // stream_select, xbar_id
    }

    // Init fifo configuration.
    mcfe_hwif_input_fifos_config_init();

    // Initialize input stats CDMA.
    mcfe_hwif_input_cdma_init();

    return MCFE_ERR_NONE;
}

int module_mcfe_input_add_video( int video_input_idx, module_mcfe_input_port_ids_t *input_port_ids, module_mcfe_input_cfg_t *input_cfg )
{
    int i;

    // Error handler
    if ( input_port_ids == NULL ) {
        LOG( LOG_ERR, "Error. Input port pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Initialize input port ids
    input_port_ids->count = 0;

    // Error handler
    if ( input_cfg == NULL ) {
        LOG( LOG_ERR, "Error. Input configuration pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( ( video_input_idx < 0 ) || ( video_input_idx >= MODULE_MCFE_INPUT_PORT_MAX ) ) {
        LOG( LOG_ERR, "Error. Video input index is out of range. (video_input_idx = %d)", video_input_idx );
        return MCFE_ERR_INV_PARM;
    } else if ( input_cfg->num_channel > MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error. Number of input channels is out of range. (num_channel = %d)", input_cfg->num_channel );
        return MCFE_ERR_INV_PARM;
    }

    // Find free input ports
    for ( i = 0, input_port_ids->count = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        if ( !mcfe_input_port[i].enabled ) {
            input_port_ids->ids[input_port_ids->count] = i;
            input_port_ids->count++;
        }
    }

    // Check if we have enough free input ports
    if ( input_port_ids->count >= input_cfg->num_channel ) {
        // Adjusting input port count to number of channels
        input_port_ids->count = input_cfg->num_channel;
    } else {
        LOG( LOG_ERR, "Error. Out of free input ports (requested = %d, available = %d).", input_cfg->num_channel, input_port_ids->count );
        input_port_ids->count = 0;
        return MCFE_ERR_NO_RES;
    }

    // Allocate input ports to video input.
    mcfe_video_input[video_input_idx].enabled = 1;
    mcfe_video_input[video_input_idx].started = 0;
    mcfe_video_input[video_input_idx].input_port_ids = *input_port_ids;
    mcfe_video_input[video_input_idx].input_cfg = *input_cfg;

    for ( i = 0; i < input_port_ids->count; i++ ) {
        mcfe_input_port[input_port_ids->ids[i]].enabled = 1;
        mcfe_input_port[input_port_ids->ids[i]].video_input_idx = video_input_idx;
    }

    // Update histogram regs.
    mcfe_hwif_input_hist_config( video_input_idx, input_cfg->rggb_start, input_cfg->cfa_pattern );

    // Update hw registers.
    for ( i = 0; i < input_port_ids->count; i++ ) {
        const int input_idx = input_port_ids->ids[i];
        const int xbar_idx = input_cfg->is_reverse_order ? input_port_ids->ids[( input_port_ids->count - 1 ) - i] : input_idx;

        // Input port configuration.
        mcfe_hwif_input_port_config( input_idx,                                                                                                   // Input
                                     ( ( input_cfg->h_size < input_cfg->active_width || input_cfg->v_size < input_cfg->active_height ) ? 1 : 0 ), // aclg_window2
                                     input_cfg->h_start, input_cfg->h_size,                                                                       // hc_start1, hc_size0
                                     input_cfg->h_start, input_cfg->h_size,                                                                       // hc_start1, hc_size1
                                     input_cfg->v_start, input_cfg->v_size,                                                                       // vc_start, vc_size
                                     1,                                                                                                           // stream_select
                                     xbar_idx );                                                                                                  // crossbar_id
        // MCFE input configuration.
        mcfe_hwif_input_config( input_idx, 3, input_cfg->msb_align, input_cfg->data_width );
        mcfe_hwif_input_wrbuf_set( input_idx, 0xff, 0xff );
        mcfe_hwif_input_fifo_config( input_idx, input_cfg->data_width, input_cfg->h_size );
    }

    return MCFE_ERR_NONE;
}

int module_mcfe_input_remove_video( int video_input_idx, module_mcfe_input_port_ids_t *const input_port_ids, module_mcfe_input_cfg_t *input_cfg )
{
    int i;

    // Error handler
    if ( input_port_ids == NULL ) {
        LOG( LOG_ERR, "Error. Input port pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( input_cfg == NULL ) {
        LOG( LOG_ERR, "Error. Input configuration pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( ( video_input_idx < 0 ) || ( video_input_idx >= MODULE_MCFE_INPUT_PORT_MAX ) ) {
        LOG( LOG_ERR, "Error. Video input index is out of range. (video_input_idx = %d)", video_input_idx );
        return MCFE_ERR_INV_PARM;
    } else if ( input_cfg->num_channel > MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error. Number of input channels is out of range. (num_channel = %d)", input_cfg->num_channel );
        return MCFE_ERR_INV_PARM;
    }

    // Deallocate video input input ports.
    system_memset( &( mcfe_video_input[video_input_idx] ), 0x0, sizeof( mcfe_video_input[video_input_idx] ) );

    for ( i = 0; i < input_port_ids->count; i++ ) {
        mcfe_input_port[input_port_ids->ids[i]].enabled = 0;
        mcfe_input_port[input_port_ids->ids[i]].video_input_idx = 0;
    }

    // Update hw registers.
    for ( i = 0; i < input_port_ids->count; i++ ) {
        const int input_idx = input_port_ids->ids[i];
        const int xbar_idx = input_cfg->is_reverse_order ? input_port_ids->ids[( input_port_ids->count - 1 ) - i] : input_idx;

        // Input port configuration.
        mcfe_hwif_input_port_config( input_idx,                                                // Input
                                     0,                                                        // aclg_window2
                                     MODULE_MCFE_DEFAULT_HC_START, MODULE_MCFE_DEFAULT_WIDTH,  // hc_start1, hc_size0
                                     MODULE_MCFE_DEFAULT_HC_START, MODULE_MCFE_DEFAULT_WIDTH,  // hc_start1, hc_size1
                                     MODULE_MCFE_DEFAULT_VC_START, MODULE_MCFE_DEFAULT_HEIGHT, // vc_start, vc_size
                                     0,                                                        // stream_select
                                     xbar_idx );                                               // crossbar_id
        // MCFE input configuration.
        mcfe_hwif_input_wrbuf_set( input_idx, 0xff, 0xff );
        mcfe_hwif_input_fifo_config_init( input_idx );
    }

    return MCFE_ERR_NONE;
}

int module_mcfe_input_mode_manual( module_mcfe_input_cfg_t *input_cfg )
{
    int i;

    if ( input_cfg->num_channel > MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error, invalid param! (num_channel = %d), expected [1;%d]", input_cfg->num_channel, MODULE_MCFE_INPUT_PORT_MAX );
        return MCFE_ERR_INV_PARM;
    }

    // Update hw registers.
    for ( i = 0; i < input_cfg->num_channel; i++ ) {

        // MCFE input configuration.
        mcfe_hwif_input_config( i, 3, input_cfg->msb_align, input_cfg->data_width );
        mcfe_hwif_input_fifo_config( i, input_cfg->data_width, input_cfg->h_size );
    }
    //Add MCBE output fifo wartermark by 10000058
    for (i = 1; i < 4; i++)
       mcbe_hwif_output_fifo_config(i, 0xf0);
    mcbe_hwif_output_fifo_config(4, 0x70);
    //Enable mcfe & mcbe flow control by 10000058
    mcfe_hwif_flow_control_enable(1);
    return MCFE_ERR_NONE;

}

int module_mcfe_input_get_input_cfg( int input_port_id, module_mcfe_input_cfg_t *input_cfg )
{
    int video_input_idx;
    int rc = MCFE_ERR_NONE;

    // Error handler
    if ( input_port_id >= MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error, input_port_id (%d) is too big.", input_port_id );
        return MCFE_ERR_INV_PARM;
    } else if ( input_cfg == NULL ) {
        LOG( LOG_ERR, "Error, NULL param passed." );
        return MCFE_ERR_INV_PARM;
    } else if ( mcfe_input_port[input_port_id].enabled != 1 ) {
        LOG( LOG_ERR, "Error, input_port[%d] is not initialized.", input_port_id );
        return MCFE_ERR_NOT_INIT;
    }

    video_input_idx = mcfe_input_port[input_port_id].video_input_idx;

    if ( mcfe_video_input[video_input_idx].enabled != 1 ) {
        LOG( LOG_ERR, "Error, video_input[%d] is not configured.", video_input_idx );
        return MCFE_ERR_NOT_INIT;
    }

    *input_cfg = mcfe_video_input[video_input_idx].input_cfg;

    return rc;
}

int module_mcfe_input_config_buffer( const module_mcfe_input_port_ids_t *const input_port_ids, const module_mcfe_bufset_t *const input_bufset )
{
    size_t i, frame_index;
    uint8_t input_buffers[MODULE_MCFE_INPUT_PORT_MAX][2];

    // Error handler
    if ( input_port_ids == NULL ) {
        LOG( LOG_ERR, "input_port_ids pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( input_port_ids->count > MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error, input_port_id count (%d) is out of range (0-%d).",
             input_port_ids->count, ( MODULE_MCFE_INPUT_PORT_MAX ) ? ( MODULE_MCFE_INPUT_PORT_MAX - 1 ) : 0 );
        return MCFE_ERR_INV_PARM;
    } else if ( input_bufset == NULL ) {
        LOG( LOG_ERR, "Buffer set pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    for ( i = 0; i < input_port_ids->count; i++ ) {
        if ( input_port_ids->ids[i] > MODULE_MCFE_INPUT_PORT_MAX ) {
            LOG( LOG_ERR, "Error, input_port_id (id = %d, index = %lu) is out of range (0-%d).",
                 input_port_ids->ids[i],
                 i,
                 ( MODULE_MCFE_INPUT_PORT_MAX ) ? ( MODULE_MCFE_INPUT_PORT_MAX - 1 ) : 0 );
            return MCFE_ERR_INV_PARM;
        }

        // Init input buffer indexes with default value
        input_buffers[i][0] = 0xFF;
        input_buffers[i][1] = 0xFF;
    }

    // Gather all required buffer IDs
    for ( i = 0; i < input_port_ids->count; i++ ) {

        for ( frame_index = 0; frame_index < MIN( input_bufset->frames.num_frames, array2d_columns( input_buffers ) ); frame_index++ ) {
            if ( module_mcfe_bufset_get_buf_id( input_bufset, frame_index, i, MCFE_BUFSET_STATUS_EMPTY, &input_buffers[i][frame_index] ) != MCFE_ERR_NONE ) {
                LOG( LOG_ERR, "Failed to get empty buffer index from bufset (type: %d, index: %d, plane: %lu).",
                     input_bufset->type, input_bufset->index, i );
                return MCFE_ERR_NO_RES;
            }
            LOG( LOG_DEBUG, "Got empty input buffer index: (buf_idx[%lu] = %d)", frame_index, input_buffers[i][frame_index] );
        }
    }

    // Everything is OK, update registers and data structures
    for ( i = 0; i < input_port_ids->count; i++ ) {

        const int input_port_id = input_port_ids->ids[i];

        // Update software variable.
        mcfe_input_port[input_port_id].input_bufset = input_bufset;

        // Update hardware registers.
        LOG( LOG_INFO, "Config input %d - write buffer1 = %d, write buffer2 = %d.",
             input_port_id,
             input_buffers[i][0],
             input_buffers[i][1] );

        mcfe_hwif_input_wrbuf_set( input_port_id, input_buffers[i][0], input_buffers[i][1] );
    }

    return MCFE_ERR_NONE;
}

int module_mcfe_input_get_input_bufset( int input_port_id, const module_mcfe_bufset_t **input_bufset )
{
    // Error handler
    if ( input_port_id >= MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error, input_port_id (%d) is too big.", input_port_id );
        return MCFE_ERR_INV_PARM;
    } else if ( mcfe_input_port[input_port_id].enabled != 1 ) {
        LOG( LOG_ERR, "Error, input_port[%d] is not initialized.", input_port_id );
        return MCFE_ERR_NOT_INIT;
    } else if ( input_bufset == NULL ) {
        LOG( LOG_ERR, "Buffer set pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    *input_bufset = mcfe_input_port[input_port_id].input_bufset;

    return MCFE_ERR_NONE;
}

int module_mcfe_input_start_video( int video_input_idx )
{
    int i;
    int rc = MCFE_ERR_NONE;

    // Error handler
    if ( video_input_idx >= MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error, invalid video_input_idx. (id = %d)", video_input_idx );
        return MCFE_ERR_INV_PARM;
    } else if ( mcfe_video_input[video_input_idx].enabled == 0 ) {
        LOG( LOG_ERR, "Error, video input %d is not enabled.", video_input_idx );
        return MCFE_ERR_NOT_INIT;
    } else if ( mcfe_video_input[video_input_idx].started == 1 ) {
        LOG( LOG_ERR, "Error, video input %d is already started.", video_input_idx );
        return MCFE_ERR_BUSY;
    }

    // Turning all required ports on.
    int input_port_status[MODULE_MCFE_INPUT_PORT_MAX];
    for ( i = 0; i < mcfe_video_input[video_input_idx].input_port_ids.count; i++ ) {
        mcfe_hwif_input_port_set_mode( mcfe_video_input[video_input_idx].input_port_ids.ids[i], MODULE_MCFE_HWIF_VIDEOINPUT_MODE_SAFE_START );
        input_port_status[i] = 0;
        LOG( LOG_INFO, "Turning input port %d on.", mcfe_video_input[video_input_idx].input_port_ids.ids[i] );
    }

    // Wait until all input ports actually turned on
    int iterations = 0;
    while ( iterations < 100 ) {

        int ports_status = 1;

        for ( i = 0; i < mcfe_video_input[video_input_idx].input_port_ids.count; i++ ) {
            if ( input_port_status[i] ) {
                continue;
            }
            if ( ( input_port_status[i] = mcfe_hwif_input_port_get_status( mcfe_video_input[video_input_idx].input_port_ids.ids[i] ) ) ) {
                LOG( LOG_INFO, "Input port %d turned on after %d ms.", mcfe_video_input[video_input_idx].input_port_ids.ids[i], iterations );
            }

            ports_status &= input_port_status[i];
        }

        // All ports turned on
        if ( ports_status ) {
            break;
        }

        system_timer_usleep( 1000 );
        iterations++;
    }

    if ( iterations >= 100 ) {
        for ( i = 0; i < mcfe_video_input[video_input_idx].input_port_ids.count; i++ ) {
            if ( !input_port_status[i] ) {
                LOG( LOG_ERR, "Failed to turn on input port %d after %d ms.", mcfe_video_input[video_input_idx].input_port_ids.ids[i], iterations );
            }
        }

        return MCFE_ERR_GENERAL;
    }

    mcfe_video_input[video_input_idx].started = 1;

    return rc;
}

int module_mcfe_input_stop_video( int video_input_idx )
{
    int i;
    int rc = MCFE_ERR_NONE;

    // Error handling
    if ( video_input_idx >= MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error, invalid video_input_idx. (id = %d)", video_input_idx );
        return MCFE_ERR_INV_PARM;
    } else if ( mcfe_video_input[video_input_idx].enabled == 0 ) {
        LOG( LOG_ERR, "Error, video input %d is not enabled.", video_input_idx );
        return MCFE_ERR_NOT_INIT;
    } else if ( mcfe_video_input[video_input_idx].started == 0 ) {
        LOG( LOG_ERR, "Error, video input %d is not started.", video_input_idx );
        return MCFE_ERR_NOT_RUN;
    }

    // Turning all used ports off.
    int input_port_status[MODULE_MCFE_INPUT_PORT_MAX];
    for ( i = 0; i < mcfe_video_input[video_input_idx].input_port_ids.count; i++ ) {
        mcfe_hwif_input_port_set_mode( mcfe_video_input[video_input_idx].input_port_ids.ids[i], MODULE_MCFE_HWIF_VIDEOINPUT_MODE_SAFE_STOP );
        input_port_status[i] = 1;
        LOG( LOG_INFO, "Turning input port %d off.", mcfe_video_input[video_input_idx].input_port_ids.ids[i] );
    }

    // Wait until all input ports actually turned off
    int iterations = 0;
    while ( iterations < 100 ) {

        int ports_status = 0;

        for ( i = 0; i < mcfe_video_input[video_input_idx].input_port_ids.count; i++ ) {
            if ( !input_port_status[i] ) {
                continue;
            }
            if ( !( input_port_status[i] = mcfe_hwif_input_port_get_status( mcfe_video_input[video_input_idx].input_port_ids.ids[i] ) ) ) {
                LOG( LOG_INFO, "Input port %d turned off after %d ms.", mcfe_video_input[video_input_idx].input_port_ids.ids[i], iterations );
            }

            ports_status |= input_port_status[i];
        }

        // All ports turned off
        if ( !ports_status ) {
            break;
        }

        system_timer_usleep( 1000 );
        iterations++;
    }

    if ( iterations >= 100 ) {
        for ( i = 0; i < mcfe_video_input[video_input_idx].input_port_ids.count; i++ ) {
            if ( input_port_status[i] ) {
                LOG( LOG_ERR, "Failed to turn off input port %d after %d ms.", mcfe_video_input[video_input_idx].input_port_ids.ids[i], iterations );
            }
        }

        return MCFE_ERR_GENERAL;
    }

    mcfe_video_input[video_input_idx].started = 0;

    return rc;
}
