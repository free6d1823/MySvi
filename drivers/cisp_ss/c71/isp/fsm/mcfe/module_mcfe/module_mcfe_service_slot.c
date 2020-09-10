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
#include "module_mcfe_common.h"
#include "module_mcfe_hwif.h"
#include "module_mcfe_service.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_MCFE


/**************************************************
 * Static types and globals
 **************************************************/
typedef struct _module_mcfe_slot_t {
    unsigned char occupied;
    module_mcfe_slot_cfg_t slot_cfg;
} module_mcfe_slot_t;

static module_mcfe_slot_t mcfe_slots[MODULE_MCFE_SLOT_ARRAY_SIZE];


/**************************************************
 * Slot control interface
 **************************************************/
int module_mcfe_slot_init( void )
{
    int i;

    mcfe_hwif_slot_all_init();
    for ( i = 0; i < ISP_MCFE_MAX_SLOT; i++ ) {
        mcfe_slots[i].occupied = 0;
    }

    return MCFE_ERR_NONE;
}

int module_mcfe_slot_create( mcfe_slot_id_t slot_id, module_mcfe_slot_cfg_t *slot_cfg )
{
    int rc = MCFE_ERR_NO_RES;
#if 0 // DYNAMIC_SLOT_ALLOCATION
    int i;

    *slot_id = -1;

    // Find empty slot and return id.
    for( i = 0; i < ISP_MCFE_MAX_SLOT; i++ ) {
        if( mcfe_slots[i].occupied == 0 ) {
            mcfe_slots[i].occupied = 1;
            rc = module_mcfe_slot_set_config( i, slot_cfg );
            if( rc != MCFE_ERR_NONE ) {
                LOG( LOG_ERR, "Error, failed to configure slot %d!", i );
                mcfe_slots[i].occupied = 0;

                return rc;
            }
            *slot_id = i;

            return MCFE_ERR_NONE;
        }
    }

    LOG( LOG_ERR, "Error, could not find empty slot to create." );
#else
    if ( mcfe_slots[slot_id].occupied == 0 ) {
        mcfe_slots[slot_id].occupied = 1;
        rc = module_mcfe_slot_set_config( slot_id, slot_cfg );
        if ( rc != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Error, failed to configure slot %d!", slot_id );
            mcfe_slots[slot_id].occupied = 0;

            return rc;
        }
    } else {
        LOG( LOG_ERR, "Error, slot %d is already created.", slot_id );
        return MCFE_ERR_INV_PARM;
    }
#endif

    return rc;
}

int module_mcfe_slot_set_config( mcfe_slot_id_t slot_id, module_mcfe_slot_cfg_t *slot_cfg )
{
    uint8_t buf_id_raw[MODULE_MCFE_INPUT_PORT_MAX];
    int rc = MCFE_ERR_NONE;
    int i;

    // Error handler
    if ( slot_id >= ISP_MCFE_MAX_SLOT ) {
        LOG( LOG_ERR, "Error, slot id (%d) is too big.", slot_id );
        return MCFE_ERR_INV_PARM;
    } else if ( mcfe_slots[slot_id].occupied != 1 ) {
        LOG( LOG_ERR, "Error, slot #%d is not yet occupied.", slot_id );
        return MCFE_ERR_INV_PARM;
    } else if ( slot_cfg->slot_mode >= MODULE_MCFE_SLOT_MODE_MAX ) {
        LOG( LOG_ERR, "Error, invalid slot mode. (mode = %d)", slot_cfg->slot_mode );
        return MCFE_ERR_INV_PARM;
    } else if ( slot_cfg->slot_bufset_out == NULL ) {
        LOG( LOG_ERR, "Error, slot output buffer set pointer is NULL" );
        return MCFE_ERR_INV_PARM;
    } else if ( slot_cfg->slot_bufset_raw == NULL ) {
        LOG( LOG_ERR, "Error, slot raw buffer set pointer is NULL" );
        return MCFE_ERR_INV_PARM;
    } else if ( slot_cfg->num_output != slot_cfg->slot_bufset_out->buffs.num_planes ) {
        LOG( LOG_ERR, "Error, slot number of outputs (%d) and buffer set number of planes (%d) don't match.",
             slot_cfg->num_output, slot_cfg->slot_bufset_out->buffs.num_planes );
        return MCFE_ERR_INV_PARM;
    } else if ( slot_cfg->num_input != slot_cfg->slot_bufset_raw->buffs.num_planes ) {
        LOG( LOG_ERR, "Error, slot number of inputs (%d) and buffer set number of planes (%d) don't match.",
             slot_cfg->num_input, slot_cfg->slot_bufset_raw->buffs.num_planes );
        return MCFE_ERR_INV_PARM;
    } else if ( slot_cfg->slot_bufset_out->frames.num_frames > 2 ) {
        LOG( LOG_ERR, "Output buffer count of %d is not supported.", slot_cfg->slot_bufset_out->frames.num_frames );
        return MCFE_ERR_INV_PARM;
    } else {
        for ( i = 0; i < MODULE_MCFE_BUFSET_MAX_FRAMES; i++ ) {
            if ( ( slot_cfg->slot_bufset_raw->frames.frame[i] == NULL ) && ( i < slot_cfg->slot_bufset_raw->frames.num_frames ) ) {
                LOG( LOG_ERR, "Error, raw buffer set associated frame %d pointer is NULL.", i );
                return MCFE_ERR_INV_PARM;
            }

            if ( ( slot_cfg->slot_bufset_out->frames.frame[i] == NULL ) && ( i < slot_cfg->slot_bufset_out->frames.num_frames ) ) {
                LOG( LOG_ERR, "Error, out buffer set associated frame %d pointer is NULL.", i );
                return MCFE_ERR_INV_PARM;
            }
        }
    }

    // Prepare buffer ids and flag slt.
    if ( slot_cfg->slot_mode == MODULE_MCFE_SLOT_MODE_MANUAL ) {
        if ( slot_cfg->num_input > MODULE_MCFE_INPUT_PORT_MAX ) {
            LOG( LOG_ERR, "Number of slot inputs (%d) exceeds maximum value (%d).", slot_cfg->num_input, MODULE_MCFE_INPUT_PORT_MAX );
            return MCFE_ERR_INV_PARM;
        }

        // Check if all configured buffer queues have buffers and get their ids
        for ( i = 0; i < slot_cfg->num_input; i++ ) {
            // Handle sensor channel ordering
            const int index = ( slot_cfg->is_reverse_order ) ? ( ( slot_cfg->num_input - 1 ) - i ) : i;

            if ( module_mcfe_bufset_get_buf_id( slot_cfg->slot_bufset_raw, -1, index, MCFE_BUFSET_STATUS_EMPTY, &buf_id_raw[i] ) != MCFE_ERR_NONE ) {
                LOG( LOG_ERR, "Slot %d failed to get empty buffer index from buffer set (type = %d, index = %d, plane = %d)",
                     slot_id, slot_cfg->slot_bufset_raw->type, slot_cfg->slot_bufset_raw->index, index );
                return MCFE_ERR_NO_RES;
            }

            LOG( LOG_DEBUG, "Slot = %d, plane = %d raw buffer index = %d", slot_id, index, buf_id_raw[i] );
        }
    } else {
        for ( i = 0; i < slot_cfg->num_input; i++ ) {
            if ( slot_cfg->slot_input_port_id[i] >= MODULE_MCFE_INPUT_PORT_MAX ) {
                LOG( LOG_ERR, "Error, invalid input port id (port id = %d), channel %d.", slot_cfg->slot_input_port_id[i], i );
                return MCFE_ERR_INV_PARM;
            }
        }
    }

    mcfe_hwif_slot_out_buf_cfg_t hwif_out_buf_cfg = {0};
    hwif_out_buf_cfg.slot_output_num = slot_cfg->num_output;

    for ( i = 0; i < slot_cfg->num_output; i++ ) {

        hwif_out_buf_cfg.slot_output_buffers[i] = slot_cfg->slot_bufset_out->frames.frame[0]->planes[i].hw_cfg.axi;

        if ( module_mcfe_bufset_get_buf_id( slot_cfg->slot_bufset_out, 0, i, MCFE_BUFSET_STATUS_EMPTY, &hwif_out_buf_cfg.first[i] ) != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Slot %d failed to get empty buffer index from buffer set (type = %d, index = %d, plane = %d)",
                 slot_id, slot_cfg->slot_bufset_raw->type, slot_cfg->slot_bufset_raw->index, i );
            return MCFE_ERR_NO_RES;
        }

        if ( slot_cfg->slot_bufset_out->frames.num_frames == 2 ) {
            if ( module_mcfe_bufset_get_buf_id( slot_cfg->slot_bufset_out, 1, i, MCFE_BUFSET_STATUS_EMPTY, &hwif_out_buf_cfg.second[i] ) != MCFE_ERR_NONE ) {
                LOG( LOG_ERR, "Slot %d failed to get empty buffer index from buffer set (type = %d, index = %d, plane = %d)",
                     slot_id, slot_cfg->slot_bufset_raw->type, slot_cfg->slot_bufset_raw->index, i );
                return MCFE_ERR_NO_RES;
            }
        } else {
            hwif_out_buf_cfg.second[i] = 0xFF;
        }
    }

    mcfe_hwif_slot_output_config( slot_id, &hwif_out_buf_cfg );

    // Update variable.
    mcfe_slots[slot_id].slot_cfg = *slot_cfg;


    // Check slot mode and configure buffers/inputs
    if ( slot_cfg->slot_mode == MODULE_MCFE_SLOT_MODE_MANUAL ) {
        mcfe_hwif_slot_inputs_config( slot_id, slot_cfg->num_input, buf_id_raw );
    } else {
        mcfe_hwif_slot_inputs_config( slot_id, slot_cfg->num_input, slot_cfg->slot_input_port_id );
    }

    mcfe_hwif_disable_hist_on_slot_and_input( slot_id, slot_cfg->slot_input_port_id[0] );
    mcfe_hwif_slot_cfg_CDMA_config( slot_id, slot_cfg->cdma_addr, slot_cfg->hist_position_is_be );
    LOG( LOG_DEBUG, "slot remoter %x.", slot_cfg->is_remote );
    if ( slot_cfg->is_remote == 0 ) {
        mcfe_hwif_slot_stat_CDMA_config( slot_cfg->slot_input_port_id[0], slot_cfg->cdma_addr, slot_cfg->hist_position_is_be );
    }

    // Update hardware registers for [Top].
    int width, height;
    if ( slot_cfg->slot_mode == MODULE_MCFE_SLOT_MODE_MANUAL ) {
        width = slot_cfg->slot_bufset_raw->frames.frame[0]->planes[0].width;
        height = slot_cfg->slot_bufset_raw->frames.frame[0]->planes[0].height;
    } else {
        module_mcfe_input_cfg_t input_cfg;
        rc = module_mcfe_input_get_input_cfg( slot_cfg->slot_input_port_id[0], &input_cfg );
        if ( rc != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Error, failed to find out buffer from bufq (bufq_id = 0x%04x).", slot_cfg->slot_input_port_id[0] );
            return rc;
        }

        width = input_cfg.h_size;
        height = input_cfg.v_size;
    }

    int rggb_start = slot_cfg->rggb_start;
    int cfa_pattern = slot_cfg->cfa_pattern;
    LOG( LOG_DEBUG, "Top configuration [width = %d, height = %d, rggb_start = %d, cfa_pattern = %d].", width, height, rggb_start, cfa_pattern );
    isp_hwif_top_config( slot_cfg->cdma_addr, width, height, rggb_start, cfa_pattern );

    return rc;
}

int module_mcfe_slot_get_config( mcfe_slot_id_t slot_id, module_mcfe_slot_cfg_t *slot_cfg )
{
    int rc = MCFE_ERR_NONE;

    // Error handler
    if ( slot_id >= ISP_MCFE_MAX_SLOT ) {
        LOG( LOG_ERR, "Error, slot id (%d) is too big.", slot_id );
        return MCFE_ERR_INV_PARM;
    } else if ( slot_cfg == NULL ) {
        LOG( LOG_ERR, "Error, NULL param passed." );
        return MCFE_ERR_INV_PARM;
    } else if ( mcfe_slots[slot_id].occupied != 1 ) {
        LOG( LOG_ERR, "Error, slot #%d is not yet occupied.", slot_id );
        return MCFE_ERR_INV_PARM;
    }

    // Get config.
    *slot_cfg = mcfe_slots[slot_id].slot_cfg;

    return rc;
}

int module_mcfe_slot_get_slot_id_with_input_id( mcfe_slot_id_t *slot_id, unsigned char input_id )
{
    int i, j, rc = MCFE_ERR_NO_RES;

    // Error handler
    if ( input_id >= MODULE_MCFE_INPUT_PORT_MAX ) {
        LOG( LOG_ERR, "Error, invalid input id (%d).", input_id );
        return MCFE_ERR_INV_PARM;
    }

    // Search the slot that possesses this input port.
    *slot_id = MODULE_MCFE_SLOT_ARRAY_SIZE;
    for ( i = 0; i < MODULE_MCFE_SLOT_ARRAY_SIZE; i++ ) {
        module_mcfe_slot_t *pslot = &mcfe_slots[i];

        if ( ( pslot->occupied != 0 ) && ( pslot->slot_cfg.slot_mode != MODULE_MCFE_SLOT_MODE_MANUAL ) ) {
            for ( j = 0; j < pslot->slot_cfg.num_input; j++ ) {
                if ( input_id == pslot->slot_cfg.slot_input_port_id[j] ) {
                    if ( *slot_id == MODULE_MCFE_SLOT_ARRAY_SIZE ) {
                        LOG( LOG_DEBUG, "Found input %d on slot %d (oc=%d, md=%d, id=%d, nm=%d).",
                             input_id,
                             i,
                             pslot->occupied,
                             pslot->slot_cfg.slot_mode,
                             pslot->slot_cfg.slot_input_port_id[j],
                             pslot->slot_cfg.num_input );
                        *slot_id = i;
                        rc = MCFE_ERR_NONE;
                    } else {
                        LOG( LOG_ERR, "Error, duplicated input %d on slot %d and %d.", input_id, *slot_id, i );
                        return MCFE_ERR_GENERAL;
                    }
                }
            }
        }
    }

    return rc;
}

int module_mcfe_slot_start( mcfe_slot_id_t slot_id )
{
    int rc = MCFE_ERR_NONE;

    // Error handler
    if ( slot_id >= ISP_MCFE_MAX_SLOT ||
         mcfe_slots[slot_id].occupied == 0 ) {
        LOG( LOG_ERR, "Error, invalid slot id (%d).", slot_id );
        return MCFE_ERR_INV_PARM;
    }

    // Update hardware register.
    mcfe_hwif_set_slot_mode( slot_id, mcfe_slots[slot_id].slot_cfg.slot_mode );

    return rc;
}

int module_mcfe_slot_trigger_manual( mcfe_slot_id_t slot_id )
{
    unsigned int i;
    uint8_t buffer_ids[ISP_MCFE_MAX_INPUT];
    module_mcfe_slot_cfg_t *slot_cfg;

    // Error handlers
    if ( slot_id >= ISP_MCFE_MAX_SLOT || mcfe_slots[slot_id].occupied == 0 ) {
        LOG( LOG_ERR, "Error, invalid slot id (%d).", slot_id );
        return MCFE_ERR_INV_PARM;
    }

    slot_cfg = &( mcfe_slots[slot_id].slot_cfg );

    if ( slot_cfg->slot_bufset_raw->buffs.num_planes > ISP_MCFE_MAX_INPUT ) {
        LOG( LOG_ERR, "Error, number of buffers (%d) exceeds maximum allowed number (%d).",
             slot_cfg->slot_bufset_raw->buffs.num_planes, ISP_MCFE_MAX_INPUT );
        return MCFE_ERR_INV_PARM;
    }

    for ( i = 0; i < slot_cfg->slot_bufset_raw->buffs.num_planes; i++ ) {

        // Handling reverse order of sensor channels
        const int index = ( slot_cfg->is_reverse_order ) ? ( ( slot_cfg->slot_bufset_raw->buffs.num_planes - 1 ) - i ) : i;

        if ( module_mcfe_bufset_get_buf_id( slot_cfg->slot_bufset_raw, -1, index, MCFE_BUFSET_STATUS_FILLED, &buffer_ids[i] ) != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Slot %d failed to get filled buffer index from buffer set (type = %d, index = %d, plane = %d)",
                 slot_id, slot_cfg->slot_bufset_raw->type, slot_cfg->slot_bufset_raw->index, index );
            return MCFE_ERR_NO_RES;
        }
    }

    // Configure slot input buffers
    mcfe_hwif_slot_input_config( slot_id, buffer_ids, slot_cfg->slot_bufset_raw->buffs.num_planes );

    // Update hardware register.
    mcfe_hwif_slot_trigger( slot_id, 1 );

    return MCFE_ERR_NONE;
}

int module_mcfe_slot_cdma_address_update( unsigned short slot_id, unsigned int addr_cfg_cdma, unsigned int addr_stats_cdma )
{
    int rc = MCFE_ERR_NONE;

    // Error handler
    if ( slot_id >= ISP_MCFE_MAX_SLOT ||
         mcfe_slots[slot_id].occupied == 0 ) {
        LOG( LOG_ERR, "Error, invalid slot id (%d).", slot_id );
        return MCFE_ERR_INV_PARM;
    }

    // Update hardware register.
    mcfe_hwif_slot_cfg_CDMA_config( slot_id, addr_cfg_cdma, mcfe_slots[slot_id].slot_cfg.hist_position_is_be ); // Slot
    if ( mcfe_slots[slot_id].slot_cfg.is_remote == 0 )
        mcfe_hwif_slot_stat_CDMA_config( slot_id, addr_stats_cdma, mcfe_slots[slot_id].slot_cfg.hist_position_is_be ); // Input

    return rc;
}

int module_mcfe_slot_stop( mcfe_slot_id_t slot_id )
{
    int rc = MCFE_ERR_NONE;

    // Error handler
    if ( slot_id >= ISP_MCFE_MAX_SLOT ||
         mcfe_slots[slot_id].occupied == 0 ) {
        LOG( LOG_ERR, "Error, invalid slot id (%d).", slot_id );
        return MCFE_ERR_INV_PARM;
    }

    // Update hardware register.
    mcfe_hwif_set_slot_mode( slot_id, 0 );

    return rc;
}

int module_mcfe_slot_destroy( mcfe_slot_id_t slot_id )
{
    int rc = MCFE_ERR_NONE;

    // Error handler
    if ( slot_id >= ISP_MCFE_MAX_SLOT ) {
        LOG( LOG_ERR, "Error, invalid slot id (%d).", slot_id );
        return MCFE_ERR_INV_PARM;
    }

    // Stop and destroy slot.
    module_mcfe_slot_stop( slot_id );
    mcfe_slots[slot_id].occupied = 0;

    return rc;
}


int module_mcfe_slot_get_free_inputs( mcfe_slot_id_t slot_id )
{
    mcfe_slot_id_t input_slot_id;
    int i, retval = 0;

    // Look for slots on all inputs.
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        int rc = module_mcfe_slot_get_slot_id_with_input_id( &input_slot_id, i );
        if ( rc == MCFE_ERR_NO_RES ) {
            retval++;
            continue;
        } else if ( rc != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Error, failed to get slot id for input %d (rc = %d)\n", i, rc );
            return 0;
        } else if ( input_slot_id == slot_id ) {
            retval++;
        }
    }

    return retval;
}