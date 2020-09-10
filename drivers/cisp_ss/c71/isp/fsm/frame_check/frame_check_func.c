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

#include "acamera_frontend_config.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"

#define MANUAL_TRIGGER_DEFAULT 0
#define FIELD_MODE_DEFAULT 0
#define HBLANK_MIN_DEFAULT 8
#define HBLANK_MAX_DEFAULT 65535
#define VBLANK_MIN_DEFAULT 1
#define VBLANK_MAX_DEFAULT 0xffffffff

#define ISP_HBLANK_MIN_DEFAULT 16
#define ISP_HBLANK_MAX_DEFAULT 65536

#define ISP_VBLANK_MIN_DEFAULT 1
#define ISP_VBLANK_MAX_DEFAULT ACAMERA_ISP_FRAME_CHECK_ISP_VBLANK_MAX_DEFAULT

/**
 * @brief      Fetches a sensor configuration and populates the FSM fields.
 *
 * @param[in]  p_fsm  The FSM pointer
 *
 */
static void fetch_sensor_config( frame_check_fsm_ptr_t p_fsm )
{
    acamera_cmd_sensor_info sensor_info;
    WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ),
                      CMD_ID_SENSOR_INFO,
                      CMD_DIRECTION_GET,
                      NULL, (uint32_t *)&sensor_info );

    p_fsm->active_height = sensor_info.active_height;
    p_fsm->active_width = sensor_info.active_width;
    p_fsm->hblank_max = sensor_info.total_width - sensor_info.active_width;
}


/**
 * @brief      Initializes the FSM and hardware associated.
 *
 * @param[in]  p_fsm  The FSM pointer
 *
 */
void frame_check_init( frame_check_fsm_ptr_t p_fsm )
{
    LOG( LOG_INFO, "Frame Check Front End(frame_check) Init" );

    static int inited = 0;

    p_fsm->manual_trigger = MANUAL_TRIGGER_DEFAULT;
    p_fsm->field_mode = FIELD_MODE_DEFAULT;
    p_fsm->hblank_min = HBLANK_MIN_DEFAULT;
    p_fsm->hblank_max = HBLANK_MAX_DEFAULT;
    p_fsm->vblank_min = VBLANK_MIN_DEFAULT;
    p_fsm->vblank_max = VBLANK_MAX_DEFAULT;

    if ( 0 == inited ) {
        const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
        acamera_frontend_frame_check_sensor_1_manual_trigger_write( PHY_ADDR_ISP, p_fsm->manual_trigger );
        acamera_frontend_frame_check_sensor_1_field_mode_write( PHY_ADDR_ISP, p_fsm->field_mode );
        acamera_frontend_frame_check_sensor_1_hblank_min_write( PHY_ADDR_ISP, p_fsm->hblank_min );
        acamera_frontend_frame_check_sensor_1_hblank_max_write( PHY_ADDR_ISP, p_fsm->hblank_max );
        acamera_frontend_frame_check_sensor_1_vblank_min_write( PHY_ADDR_ISP, p_fsm->vblank_min );
        acamera_frontend_frame_check_sensor_1_vblank_max_write( PHY_ADDR_ISP, p_fsm->vblank_max );
        acamera_frontend_frame_check_sensor_2_manual_trigger_write( PHY_ADDR_ISP, p_fsm->manual_trigger );
        acamera_frontend_frame_check_sensor_2_field_mode_write( PHY_ADDR_ISP, p_fsm->field_mode );
        acamera_frontend_frame_check_sensor_2_hblank_min_write( PHY_ADDR_ISP, p_fsm->hblank_min );
        acamera_frontend_frame_check_sensor_2_hblank_max_write( PHY_ADDR_ISP, p_fsm->hblank_max );
        acamera_frontend_frame_check_sensor_2_vblank_min_write( PHY_ADDR_ISP, p_fsm->vblank_min );
        acamera_frontend_frame_check_sensor_2_vblank_max_write( PHY_ADDR_ISP, p_fsm->vblank_max );
        acamera_frontend_frame_check_sensor_3_manual_trigger_write( PHY_ADDR_ISP, p_fsm->manual_trigger );
        acamera_frontend_frame_check_sensor_3_field_mode_write( PHY_ADDR_ISP, p_fsm->field_mode );
        acamera_frontend_frame_check_sensor_3_hblank_min_write( PHY_ADDR_ISP, p_fsm->hblank_min );
        acamera_frontend_frame_check_sensor_3_hblank_max_write( PHY_ADDR_ISP, p_fsm->hblank_max );
        acamera_frontend_frame_check_sensor_3_vblank_min_write( PHY_ADDR_ISP, p_fsm->vblank_min );
        acamera_frontend_frame_check_sensor_3_vblank_max_write( PHY_ADDR_ISP, p_fsm->vblank_max );
        acamera_frontend_frame_check_sensor_4_manual_trigger_write( PHY_ADDR_ISP, p_fsm->manual_trigger );
        acamera_frontend_frame_check_sensor_4_field_mode_write( PHY_ADDR_ISP, p_fsm->field_mode );
        acamera_frontend_frame_check_sensor_4_hblank_min_write( PHY_ADDR_ISP, p_fsm->hblank_min );
        acamera_frontend_frame_check_sensor_4_hblank_max_write( PHY_ADDR_ISP, p_fsm->hblank_max );
        acamera_frontend_frame_check_sensor_4_vblank_min_write( PHY_ADDR_ISP, p_fsm->vblank_min );
        acamera_frontend_frame_check_sensor_4_vblank_max_write( PHY_ADDR_ISP, p_fsm->vblank_max );
        acamera_isp_frame_check_isp_hblank_min_write( p_ictx->settings.isp_base, ISP_HBLANK_MIN_DEFAULT );
        acamera_isp_frame_check_isp_hblank_max_write( p_ictx->settings.isp_base, ISP_HBLANK_MAX_DEFAULT );
        acamera_isp_frame_check_isp_vblank_min_write( p_ictx->settings.isp_base, ISP_VBLANK_MIN_DEFAULT );
        acamera_isp_frame_check_isp_vblank_max_write( p_ictx->settings.isp_base, ISP_VBLANK_MAX_DEFAULT );
        inited = 1;
    }
}


/**
 * @brief      Configures the FSM and hardware associated.
 *
 * @param[in]  p_fsm  The FSM pointer
 *
 */
void frame_check_config( frame_check_fsm_ptr_t p_fsm )
{
    int input, slot;
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    fetch_sensor_config( p_fsm );

    acamera_isp_frame_check_isp_crop_active_width_write( PHY_ADDR_ISP, p_fsm->active_width );
    acamera_isp_frame_check_isp_crop_active_height_write( PHY_ADDR_ISP, p_fsm->active_height );
    acamera_isp_frame_check_isp_hblank_min_write( p_ictx->settings.isp_base, ISP_HBLANK_MIN_DEFAULT );
    acamera_isp_frame_check_isp_hblank_max_write( p_ictx->settings.isp_base, ISP_HBLANK_MAX_DEFAULT );
    acamera_isp_frame_check_isp_vblank_min_write( p_ictx->settings.isp_base, ISP_VBLANK_MIN_DEFAULT );
    acamera_isp_frame_check_isp_vblank_max_write( p_ictx->settings.isp_base, ISP_VBLANK_MAX_DEFAULT );

    // Verify if this slot uses more than one input.
    for ( input = 0; input < MODULE_MCFE_INPUT_PORT_MAX; ++input ) {

        slot = module_mcfe_get_slot_id_for_input( input, 0 );

        if ( ACAMERA_FSM2ICTX_PTR( p_fsm )->context_id == slot ) {

            switch ( input ) {
            case 0:
                acamera_frontend_frame_check_sensor_1_active_width_write( PHY_ADDR_ISP, p_fsm->active_width );
                acamera_frontend_frame_check_sensor_1_active_height_write( PHY_ADDR_ISP, p_fsm->active_height );
                acamera_frontend_frame_check_sensor_1_hblank_max_write( PHY_ADDR_ISP, p_fsm->hblank_max );
                acamera_isp_frame_check_isp_out_1_active_width_write( PHY_ADDR_ISP, p_fsm->active_width );
                acamera_isp_frame_check_isp_out_1_active_height_write( PHY_ADDR_ISP, p_fsm->active_height );
                break;
            case 1:
                acamera_frontend_frame_check_sensor_2_active_width_write( PHY_ADDR_ISP, p_fsm->active_width );
                acamera_frontend_frame_check_sensor_2_active_height_write( PHY_ADDR_ISP, p_fsm->active_height );
                acamera_frontend_frame_check_sensor_2_hblank_max_write( PHY_ADDR_ISP, p_fsm->hblank_max );
                acamera_isp_frame_check_isp_out_2_active_width_write( PHY_ADDR_ISP, p_fsm->active_width );
                acamera_isp_frame_check_isp_out_2_active_height_write( PHY_ADDR_ISP, p_fsm->active_height );
                break;
            case 2:
                acamera_frontend_frame_check_sensor_3_active_width_write( PHY_ADDR_ISP, p_fsm->active_width );
                acamera_frontend_frame_check_sensor_3_active_height_write( PHY_ADDR_ISP, p_fsm->active_height );
                acamera_frontend_frame_check_sensor_3_hblank_max_write( PHY_ADDR_ISP, p_fsm->hblank_max );
                acamera_isp_frame_check_isp_out_3_active_width_write( PHY_ADDR_ISP, p_fsm->active_width );
                acamera_isp_frame_check_isp_out_3_active_height_write( PHY_ADDR_ISP, p_fsm->active_height );
                break;
            case 3:
                acamera_frontend_frame_check_sensor_4_active_width_write( PHY_ADDR_ISP, p_fsm->active_width );
                acamera_frontend_frame_check_sensor_4_active_height_write( PHY_ADDR_ISP, p_fsm->active_height );
                acamera_frontend_frame_check_sensor_4_hblank_max_write( PHY_ADDR_ISP, p_fsm->hblank_max );
                break;
            }
        }
    }
}
