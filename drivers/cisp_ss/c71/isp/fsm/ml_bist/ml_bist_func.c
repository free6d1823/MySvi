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

#include "system_isp_io.h"
#include "acamera_faults_cfg_config.h"
#include "acamera_frontend_config.h"
#include "acamera_isp_config.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "bitop.h" //Bit Field macros.

// ******************* Module Level BIST(Built-In Self-Test) ***********************

typedef enum {
    RAW_FRONTEND,
    FRAME_STITCH,
    SINTER,
    RADIAL_SHADING,
    IRIDIX,
    DEMOSAIC,
    DEMOSAIC_RGBIR,
    DEMOSAIC_RCCC,
    OUTFORMAT,
} test_block_t;

/** tests ran by this FSM in sequence. */
typedef enum {
    ML_BIST_TEST0 = 0,
    ML_BIST_TEST1,
    ML_BIST_TEST2,
    ML_BIST_TEST3,
    ML_BIST_TEST4,
    ML_BIST_TEST5,
    ML_BIST_TEST6,
    ML_BIST_TEST7,

    ML_BIST_TEST_MAX,
} ml_bist_test_t;

static const char *ml_bist_get_test_name( const ml_bist_test_t test )
{
    switch ( test ) {
    case ML_BIST_TEST0:
        return "ML_BIST_TEST0";
    case ML_BIST_TEST1:
        return "ML_BIST_TEST1";
    case ML_BIST_TEST2:
        return "ML_BIST_TEST2";
    case ML_BIST_TEST3:
        return "ML_BIST_TEST3";
    case ML_BIST_TEST4:
        return "ML_BIST_TEST4";
    case ML_BIST_TEST5:
        return "ML_BIST_TEST5";
    case ML_BIST_TEST6:
        return "ML_BIST_TEST6";
    case ML_BIST_TEST7:
        return "ML_BIST_TEST7";
    default:
        return "ML_BIST_ERROR";
    }
}

static void ml_bist_clear_crc_faults( void );
static void ml_bist_reset_crc_faults( const test_block_t isp_block );
static void ml_bist_check_for_crc_faults( const ml_bist_test_t current_test_number );

void ml_bist_fsm_process_interrupt( ml_bist_fsm_const_ptr_t p_fsm, uint8_t irq_event )
{
    switch ( irq_event ) {
    case ACAMERA_IRQ_BE_FRAME_END:
        ml_bist_frame_end( (ml_bist_fsm_ptr_t)p_fsm );
        break;
    }
}

void ml_bist_init( ml_bist_fsm_ptr_t p_fsm )
{
    // Called once at boot up
    p_fsm->repeat_irq_mask = BIT( ACAMERA_IRQ_BE_FRAME_END );

    ml_bist_clear_crc_faults();

    // Finally request interrupts
    ml_bist_request_interrupt( p_fsm, p_fsm->repeat_irq_mask );
}

void ml_bist_frame_end( ml_bist_fsm_ptr_t p_fsm )
{
    /* ISP blocks to configure.
	 * 1. Raw Frontend
	 * 2. Frame Stitch
	 * 3. Sinter
	 * 4. Iridix
	 * 5. Gamma FeDI (Ignored)
	 * 6. Gamma BeDI (Ignored)
	 * 7. Radial Shading
	 * 8. Demosaic
	 * 9. Demosaic RGBIr
	 * 10. Demosaic RGCCC
	 * 11. Out Format
     */
    const uint32_t base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

    /** Helper structure to manage tests. Each test is a bitfield where each bit
     * corresponds to a test. To enable test 0 for exampel set bit 0 etc. */
    struct
    {
        uint8_t sinter;
        uint16_t frame_stich;
        uint8_t raw_frontend;
        uint8_t iridix;
        uint8_t radial_shading;
        uint8_t out_fmt;
        uint8_t demosaic_rccc;
        uint8_t demosaic_rgbir;
        uint8_t demosaic;
    } test_modes = {0};


    switch ( p_fsm->current_test_number ) {
    case ML_BIST_TEST0:
        test_modes.sinter = BIT( 3 );
        test_modes.frame_stich = BIT( 3 );
        test_modes.raw_frontend = BIT( 2 );
        test_modes.radial_shading = BIT( 3 );
        test_modes.out_fmt = BIT( 3 );
        test_modes.demosaic_rccc = BIT( 3 );
        test_modes.demosaic_rgbir = BIT( 3 );
        test_modes.demosaic = BIT( 3 );
        break;
    case ML_BIST_TEST1:
        // Run test 2 for iridix
        test_modes.iridix = BIT( 2 );
        break;

    case ML_BIST_TEST2:
        test_modes.sinter = BIT( 4 );
        test_modes.frame_stich = BIT( 4 );
        test_modes.raw_frontend = BIT( 2 );
        test_modes.radial_shading = BIT( 4 );
        test_modes.out_fmt = BIT( 4 );
        test_modes.demosaic_rccc = BIT( 4 );
        test_modes.demosaic_rgbir = BIT( 4 );
        test_modes.demosaic = BIT( 4 );
        break;

    case ML_BIST_TEST3:
        // Iridix test 3
        test_modes.iridix = BIT( 3 );
        break;

    case ML_BIST_TEST4:
        test_modes.sinter = BIT( 5 );
        test_modes.frame_stich = BIT( 5 ) | BIT( 2 );
        test_modes.raw_frontend = BIT( 5 );
        test_modes.radial_shading = BIT( 5 );
        test_modes.out_fmt = BIT( 5 );
        test_modes.demosaic_rccc = BIT( 5 );
        test_modes.demosaic_rgbir = BIT( 5 );
        test_modes.demosaic = BIT( 5 );
        break;

    case ML_BIST_TEST5:
        test_modes.iridix = BIT( 4 );
        break;

    case ML_BIST_TEST6:
        test_modes.sinter = BIT( 2 );
        test_modes.frame_stich = BIT( 6 ) | BIT( 7 ) | BIT( 8 );
        test_modes.raw_frontend = BIT( 3 ) | BIT( 4 );
        test_modes.radial_shading = BIT( 2 );
        test_modes.out_fmt = BIT( 2 );
        test_modes.demosaic_rccc = BIT( 2 );
        test_modes.demosaic_rgbir = BIT( 2 );
        test_modes.demosaic = BIT( 2 );
        break;
    case ML_BIST_TEST7:
        test_modes.iridix = BIT( 5 );
        break;

    default:
        /*Invalid test number. Reset and return. */
        p_fsm->current_test_number = ML_BIST_TEST0;
        return;
    }

    ml_bist_check_for_crc_faults( p_fsm->current_test_number );
    ml_bist_clear_crc_faults();

    acamera_isp_test_mode_raw_frontend_write( base, test_modes.raw_frontend );
    acamera_isp_test_mode_frame_stitch_write( base, test_modes.frame_stich );
    acamera_isp_test_mode_sinter_write( base, test_modes.sinter );
    acamera_isp_test_mode_radial_shading_write( base, test_modes.radial_shading );
    acamera_isp_test_mode_iridix_write( base, test_modes.iridix );
    acamera_isp_test_mode_demosaic_write( base, test_modes.demosaic );
    acamera_isp_test_mode_demosaic_rgbir_write( base, test_modes.demosaic_rgbir );
    acamera_isp_test_mode_demosaic_rccc_write( base, test_modes.demosaic_rccc );
    acamera_isp_test_mode_out_format_write( base, test_modes.out_fmt );

    if ( ( ++p_fsm->current_test_number ) >= ML_BIST_TEST_MAX )
        p_fsm->current_test_number = ML_BIST_TEST0;
}

static void ml_bist_clear_crc_faults( void )
{
    // To do: Remove these API calls and reset the registers directly.
    acamera_faults_cfg_faults_cfg_status_mcfe_error_fifo_in_crc1_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcfe_error_fifo_in_crc2_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcfe_error_fifo_in_crc3_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcfe_error_fifo_in_crc4_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcfe_error_fifo_out_crc1_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcfe_error_fifo_out_crc2_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcfe_error_fifo_out_crc3_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcfe_error_fifo_out_crc4_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcfe_error_buffer_config_config_crc_mismatch_write( PHY_ADDR_ISP, 0 );

    acamera_faults_cfg_faults_cfg_status_mcbe_error_fifo_in_crc1_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcbe_error_fifo_in_crc2_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcbe_error_fifo_in_crc3_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcbe_error_fifo_in_crc4_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_mcbe_error_buffer_config_config_crc_mismatch_write( PHY_ADDR_ISP, 0 );

#if IS_MALI_C71
    acamera_faults_cfg_faults_cfg_status_exp_fifo_error_fifo_in_crc_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
#endif

    ml_bist_reset_crc_faults( RAW_FRONTEND );
    ml_bist_reset_crc_faults( FRAME_STITCH );
    ml_bist_reset_crc_faults( SINTER );
    ml_bist_reset_crc_faults( RADIAL_SHADING );
    ml_bist_reset_crc_faults( IRIDIX );
    ml_bist_reset_crc_faults( DEMOSAIC );
    ml_bist_reset_crc_faults( DEMOSAIC_RGBIR );
    ml_bist_reset_crc_faults( DEMOSAIC_RCCC );
    ml_bist_reset_crc_faults( OUTFORMAT );

    acamera_faults_cfg_faults_cfg_status_crc_check_1_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_crc_check_2_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_crc_check_3_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_crc_check_a1_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_crc_check_a2_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_crc_check_a3_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
    acamera_faults_cfg_faults_cfg_status_pc_fifo_error_fifo_in_crc2_fifo_crc_mismatch_write( PHY_ADDR_ISP, 0 );
}

#ifndef ACAMERA_FAULTS_CFG_FAULTS_CFG_STATUS_FRAME_STITCH_CRC_DATA_O_FAULT_CRC_MISMATCH_OFFSET
/**
 * @brief      Resets fauls for given block.
 *
 * @param[in]  isp_block  The isp block
 *
 */
static void ml_bist_reset_crc_faults( const test_block_t isp_block )
{
    switch ( isp_block ) {
    case RAW_FRONTEND:
        acamera_faults_cfg_faults_cfg_status_raw_frontend_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case FRAME_STITCH:
        acamera_faults_cfg_faults_cfg_status_frame_stitch_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case SINTER:
        acamera_faults_cfg_faults_cfg_status_sinter_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case RADIAL_SHADING:
        acamera_faults_cfg_faults_cfg_status_radial_shading_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case IRIDIX:
        acamera_faults_cfg_faults_cfg_status_iridix_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case DEMOSAIC:
        acamera_faults_cfg_faults_cfg_status_demosaic_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case DEMOSAIC_RGBIR:
        acamera_faults_cfg_faults_cfg_status_demosaic_rgbir_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case DEMOSAIC_RCCC:
        acamera_faults_cfg_faults_cfg_status_demosaic_rccc_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case OUTFORMAT:
        acamera_faults_cfg_faults_cfg_status_out_format_crc_data_bist_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    default:
        break;
    }
}

/**
 * @brief      Checks for Module level BIST faults in ISP registers
 *
 * @param[in]  current_test_number  The test run number
 *
 */
static void ml_bist_check_for_crc_faults( const ml_bist_test_t test )
{
    const char *test_name = ml_bist_get_test_name( test );
    uint32_t err;

    err = acamera_faults_cfg_faults_cfg_status_raw_frontend_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Raw Frontend, test: %s", err, test_name );
    }
    err = acamera_faults_cfg_faults_cfg_status_frame_stitch_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Frame Stitch, test: %s", err, test_name );
    }
    err = acamera_faults_cfg_faults_cfg_status_sinter_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Sinter, test: %s", err, test_name );
    }
    err = acamera_faults_cfg_faults_cfg_status_radial_shading_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Radial Shading, test: %s", err, test_name );
    }
    err = acamera_faults_cfg_faults_cfg_status_iridix_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Iridix, test: %s", err, test_name );
    }
    err = acamera_faults_cfg_faults_cfg_status_demosaic_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Demosaic, test: %s", err, test_name );
    }
    err = acamera_faults_cfg_faults_cfg_status_demosaic_rgbir_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Demosaic RGBIr, test: %s", err, test_name );
    }
    err = acamera_faults_cfg_faults_cfg_status_demosaic_rccc_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Demosaic RCCC, test: %s", err, test_name );
    }
    err = acamera_faults_cfg_faults_cfg_status_out_format_crc_data_bist_o_fault_crc_mismatch_read( PHY_ADDR_ISP );
    if ( err ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Output Format, test: %s", err, test_name );
    }
}

#else

/**
 * @brief      Resets fauls for given block.
 *
 * @param[in]  isp_block  The isp block
 *
 */
static void ml_bist_reset_crc_faults( const test_block_t isp_block )
{
    switch ( isp_block ) {
    case RAW_FRONTEND:
        acamera_faults_cfg_faults_cfg_status_raw_frontend_crc_data_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_raw_frontend_crc_hp_median_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_raw_frontend_crc_hotpixel_marker_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case FRAME_STITCH:
        acamera_faults_cfg_faults_cfg_status_frame_stitch_crc_data_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
#if IS_MALI_C71
        acamera_faults_cfg_faults_cfg_status_frame_stitch_crc_exp_mask_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
#endif
        break;
    case SINTER:
        acamera_faults_cfg_faults_cfg_status_sinter_crc_vdata_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case RADIAL_SHADING:
        acamera_faults_cfg_faults_cfg_status_radial_shading_crc_data_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case IRIDIX:
        acamera_faults_cfg_faults_cfg_status_iridix_crc_data_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case DEMOSAIC:
        acamera_faults_cfg_faults_cfg_status_demosaic_crc_red_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_demosaic_crc_grn_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_demosaic_crc_blu_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_demosaic_crc_mask_sad_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case DEMOSAIC_RGBIR:
#if IS_MALI_C71
        acamera_faults_cfg_faults_cfg_status_demosaic_rgbir_crc_irmask_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
#endif
        acamera_faults_cfg_faults_cfg_status_demosaic_rgbir_crc_rplane_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_demosaic_rgbir_crc_gplane_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_demosaic_rgbir_crc_bplane_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_demosaic_rgbir_crc_iplane_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_demosaic_rgbir_crc_declip_data_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case DEMOSAIC_RCCC:
        acamera_faults_cfg_faults_cfg_status_demosaic_rccc_crc_vdata1_rc_r_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_demosaic_rccc_crc_vdata2_rc_c_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    case OUTFORMAT:
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata1_rgb_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata2_rgb_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata3_rgb_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata1_cm_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata2_cm_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata3_cm_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata1_ir_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata2_yuv_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata3_yuv_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
#if IS_MALI_C71
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata1_yuv_y_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
#endif
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata2_luv_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata3_luv_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata1_luv_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata1_hs_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata2_hs_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        acamera_faults_cfg_faults_cfg_status_out_format_crc_vdata1_s_o_fault_crc_mismatch_write( PHY_ADDR_ISP, 0 );
        break;
    default:
        break;
    }
}

/**
 * @brief      Checks for Module level BIST faults in ISP registers
 *
 * @param[in]  current_test_number  The test run number
 *
 * @note       While the api exists to read invididual bits in the registers for
 *             all of the faults here we cannot use it since the overhead of
 *             calling so many register access functions is too much for this FSM.
 *             For this reason we hardcode the values here.
 *
 */
static void ml_bist_check_for_crc_faults( const ml_bist_test_t test )
{
    const char *test_name = ml_bist_get_test_name( test );

    /* The number in the name is the address offset. For example: reg60 is PHY_ADDR_ISP + 0x01C00 + 0x60*/
    const uint32_t reg60 = system_isp_read_32( PHY_ADDR_ISP + ACAMERA_FAULTS_CFG_BASE_ADDR + ACAMERA_FAULTS_CFG_FAULTS_CFG_STATUS_FRAME_STITCH_CRC_DATA_O_FAULT_CRC_MISMATCH_OFFSET );
    const uint32_t reg64 = system_isp_read_32( PHY_ADDR_ISP + ACAMERA_FAULTS_CFG_BASE_ADDR + ACAMERA_FAULTS_CFG_FAULTS_CFG_STATUS_RAW_FRONTEND_CRC_DATA_O_FAULT_CRC_MISMATCH_OFFSET );
    const uint32_t reg68 = system_isp_read_32( PHY_ADDR_ISP + ACAMERA_FAULTS_CFG_BASE_ADDR + ACAMERA_FAULTS_CFG_FAULTS_CFG_STATUS_RADIAL_SHADING_CRC_DATA_O_FAULT_CRC_MISMATCH_OFFSET );
    const uint32_t reg6c = system_isp_read_32( PHY_ADDR_ISP + ACAMERA_FAULTS_CFG_BASE_ADDR + ACAMERA_FAULTS_CFG_FAULTS_CFG_STATUS_DEMOSAIC_CRC_GRN_O_FAULT_CRC_MISMATCH_OFFSET );
    const uint32_t reg70 = system_isp_read_32( PHY_ADDR_ISP + ACAMERA_FAULTS_CFG_BASE_ADDR + ACAMERA_FAULTS_CFG_FAULTS_CFG_STATUS_OUT_FORMAT_CRC_VDATA2_HS_O_FAULT_CRC_MISMATCH_OFFSET );

    const uint32_t err_frame_stich = BF_GET( reg60, 29, 2 );   //frame stich error register 0x60, 2 bits, starting at offset 29.
    const uint32_t err_fe = BF_GET( reg64, 18, 3 );            //front end error register 0x64, 3 bits, starting at offset 18
    const uint32_t err_sinter = BF_GET( reg64, 31, 1 );        //sinter error register 0x64, 1 bit, starting at offset 31
    const uint32_t err_radial = BF_GET( reg68, 9, 1 );         //radial shading erorr, register 0x68, 1 bit, starting at offset 9
    const uint32_t err_iridix = BF_GET( reg68, 18, 1 );        //iridix error, register 0x68, 1 bit, starting at offset 18
    const uint32_t err_demosaic_rccc = BF_GET( reg68, 26, 2 ); //demosaic rccc error, register 0x68, 2 bits, starting at offset 26
    const uint32_t err_demosaic1 = BF_GET( reg68, 31, 1 );     //demosaic error, register 0x68, 1 bit, starting at offset 31
    const uint32_t err_demosaic2 = BF_GET( reg6c, 0, 3 );      //demosaic error, register 0x6C, 3 bits, starting at offset 0
    const uint32_t err_demo_rgbir = BF_GET( reg6c, 8, 6 );     //demosaic rgbir error, register 0x6C, 6 bits, starting at offset 8
    const uint32_t err_out_fmt1 = BF_GET( reg6c, 18, 14 );     //out formatter error, register 0x6C, 14 bits, starting at offset 18
    const uint32_t err_out_fmt2 = BF_GET( reg70, 0, 2 );       //out formatter error, register 0x70, 2 bits, starting at offset 0

    if ( err_fe ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Raw FrontEnd, test: %s", err_fe, test_name );
    }

    if ( err_frame_stich ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) Frame Stich, test: %s", err_frame_stich, test_name );
    }

    if ( err_sinter ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Sinter, test: %s", err_sinter, test_name );
    }

    if ( err_radial ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Radial Shading, test: %s", err_radial, test_name );
    }

    if ( err_iridix ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Iridix, test: %s", err_iridix, test_name );
    }

    if ( err_demosaic_rccc ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Demosaic RCCC, test: %s", err_demosaic_rccc, test_name );
    }

    if ( err_demosaic1 || err_demosaic2 ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x, 0x%x) in Demosaic, test: %s", err_demosaic1, err_demosaic2, test_name );
    }

    if ( err_demo_rgbir ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x) in Demosaic RGBIr, test: %s", err_demo_rgbir, test_name );
    }

    if ( err_out_fmt1 || err_out_fmt2 ) {
        LOG( LOG_ERR, "ML_BIST Error(0x%x, 0x%x) in Out Format, test: %s", err_out_fmt1,
             err_out_fmt2, test_name );
    }
}

#endif
