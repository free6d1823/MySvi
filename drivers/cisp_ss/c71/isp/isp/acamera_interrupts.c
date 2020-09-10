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

/**
 @file acamera_interrupts.c
 @todo       Figure out how how to better enable/disable interrupts used for the
             given use case.
 @addtogroup acamera_interrupts ISP Interrupts
 @{
*/

#include "acamera_interrupts.h"
#include "system_assert.h"
#include "acamera.h" // acamera_process_interrupt()
#include "acamera_configuration.h"
#include "acamera_frontend_config.h"   // Interrupt register access.
#include "acamera_interrupt_numbers.h" // IRQ numbers
#include "acamera_isp_ctx.h"           // Need it to get context pointer.
#include "acamera_logger.h"            // For logging.

#if DEBUG_FRAME_COUNT
#include "system_timer.h" // Used to get system ticks for counters.
#endif

#if defined( ISP_HAS_MCFE_FSM )
#include "module_mcfe_common.h" // Needed for module_mcfe_get_slot_id_for_input
#endif

#ifdef CMD_QUEUE_DEBUG
#include "acamera_cmd_queues_config.h" // Microblaze only. Used for logging.
#endif

#if ISP_HAS_HISTOGRAM_FSM
#include "histogram_fsm.h" //Required for interrupt sources based on histogram tap points.
#endif


/** For MALI-C71 only. Allows the choice of using CDMA as the BE EOF event.  */
#define CDMA_AS_BE_EOF ( 1 )

/**@addtogroup interrupt_bits Interrupt Bits
 * @{*/

/**@addtogroup interrupt_stats_bits Interrupt Bits: Frame Stats
 * @{*/

/** metering_aexp_module_busy */
#define FRAME_STATS_INTERRUPT_AE_BITMASK ( 1u << 0 )
/** metering_awb_module_busy */
#define FRAME_STATS_INTERRUPT_AWB_BITMASK ( 1u << 1 )
/** metering_hist_1_module_busy */
#define FRAME_STATS_INTERRUPT_METERING_HIST1_BITMASK ( 1u << 2 )
/** metering_hist_2_module_busy */
#define FRAME_STATS_INTERRUPT_METERING_HIST2_BITMASK ( 1u << 3 )
/** metering_hist_3_module_busy */
#define FRAME_STATS_INTERRUPT_METERING_HIST3_BITMASK ( 1u << 4 )
/** metering_hist_4_module_busy */
#define FRAME_STATS_INTERRUPT_METERING_HIST4_BITMASK ( 1u << 5 )
/** metering hist any module busy */
#define FRAME_STATS_INTERRUPT_METERING_HIST_BITS ( FRAME_STATS_INTERRUPT_METERING_HIST1_BITMASK | \
                                                   FRAME_STATS_INTERRUPT_METERING_HIST2_BITMASK | \
                                                   FRAME_STATS_INTERRUPT_METERING_HIST3_BITMASK | \
                                                   FRAME_STATS_INTERRUPT_METERING_HIST4_BITMASK )

/** antifog_hist_module_busy */
#define FRAME_STATS_INTERRUPT_ANTIFOG_HIST_BITMASK ( 1u << 6 )
/** roi_hist_1_module_busy */
#define FRAME_STATS_INTERRUPT_ROI_HIST1_BITMASK ( 1u << 7 )
/** roi_hist_2_module_busy */
#define FRAME_STATS_INTERRUPT_ROI_HIST2_BITMASK ( 1u << 8 )
/** roi_hist_3_module_busy */
#define FRAME_STATS_INTERRUPT_ROI_HIST3_BITMASK ( 1u << 9 )
/** roi_hist_4_module_busy */
#define FRAME_STATS_INTERRUPT_ROI_HIST4_BITMASK ( 1u << 10 )
/** uroi_module_busy */
#define FRAME_STATS_INTERRUPT_UROI_BITMASK ( 1u << 11 )
/** iridix_dut_or_bist_busy */
#define FRAME_STATS_INTERRUPT_IRIDIX_BITMASK ( 1u << 12 )
/** defect_pixel_module_busy */
#define FRAME_STATS_INTERRUPT_DEFECT_PIX_BITMASK ( 1u << 13 )
/**@}*/


/**@addtogroup interrupt_frame_bits Interrupt Bits: Frame Start/End
 * @{*/

/** input_port_1_sensor_field_o */
#define FRAME_INTERRUPT_XBAR1_SOFEOF_BIT ( 1u << 0 )
/** input_port_2_sensor_field_o */
#define FRAME_INTERRUPT_XBAR2_SOFEOF_BIT ( 1u << 1 )
/** input_port_3_sensor_field_o */
#define FRAME_INTERRUPT_XBAR3_SOFEOF_BIT ( 1u << 2 )
/** input_port_4_sensor_field_o */
#define FRAME_INTERRUPT_XBAR4_SOFEOF_BIT ( 1u << 3 )
#define FRAME_INTERRUPT_XBAR_START_END_BITS ( FRAME_INTERRUPT_XBAR1_SOFEOF_BIT | \
                                              FRAME_INTERRUPT_XBAR2_SOFEOF_BIT | \
                                              FRAME_INTERRUPT_XBAR3_SOFEOF_BIT | \
                                              FRAME_INTERRUPT_XBAR4_SOFEOF_BIT )

/** video_test_gen_position1_1_mux_field */
#define FRAME_INTERRUPT_INPUTPORT1_SOFEOF_BIT ( 1u << 4 )
/** video_test_gen_position2_1_mux_field */
#define FRAME_INTERRUPT_INPUTPORT2_SOFEOF_BIT ( 1u << 5 )
/** video_test_gen_position3_1_mux_field */
#define FRAME_INTERRUPT_INPUTPORT3_SOFEOF_BIT ( 1u << 6 )
/** video_test_gen_position4_1_mux_field */
#define FRAME_INTERRUPT_INPUTPORT4_SOFEOF_BIT ( 1u << 7 )
/** Any video_test_gen_position_1_mux_field */
#define FRAME_INTERRUPT_INPUTPORT_START_END_BITS ( FRAME_INTERRUPT_INPUTPORT1_SOFEOF_BIT | \
                                                   FRAME_INTERRUPT_INPUTPORT2_SOFEOF_BIT | \
                                                   FRAME_INTERRUPT_INPUTPORT3_SOFEOF_BIT | \
                                                   FRAME_INTERRUPT_INPUTPORT4_SOFEOF_BIT )

/** retime_bypass_mcfe_mux_out_field */
#define FRAME_INTERRUPT_MCFE_SOFEOF_BIT ( 1u << 8 )
/** linear_data_source_mux_field */
#define FRAME_INTERRUPT_FRAME_STITCH_SOFEOF_BIT ( 1u << 9 )
/** bypass_frame_stitch_out_field */
#define FRAME_INTERRUPT_DEFECT_PIXEL_SOFEOF_BIT ( 1u << 10 )
/** bypass_sinter_out_field */
#define FRAME_INTERRUPT_SINTER_SOFEOF_BIT ( 1u << 11 )
/** bypass_mesh_shading_out_field */
#define FRAME_INTERRUPT_MESH_SHADING_SOFEOF_BIT ( 1u << 12 )
/** bypass_iridix_out_field */
#define FRAME_INTERRUPT_IRIDIX_SOFEOF_BIT ( 1u << 13 )
/** bypass_demosaic_out_field */
#define FRAME_INTERRUPT_DEMOSAIC_SOFEOF_BIT ( 1u << 14 )
/** bypass_out_format_out_field */
#define FRAME_INTERRUPT_OUTPUT_FORMATTER_SOFEOF_BIT ( 1u << 15 )

/** Mask of MCFE slot interrupt bits. */
#define FRAME_INTERRUPT_MCFE_SLOT_MASK ( 0xFFFF0 )
/**@}*/
/**@}*/


/*----------  IRQ MASK FRAME START  ----------*/
/** Bit mask of sof interrupts in use */
#define IRQ_MASK_FRAME_START ( FRAME_INTERRUPT_INPUTPORT_START_END_BITS | \
                               FRAME_INTERRUPT_OUTPUT_FORMATTER_SOFEOF_BIT )

/*----------  IRQ MASK FRAME END  ----------*/
/** Bit mask of eof interrupts in use */
#define IRQ_MASK_FRAME_END ( FRAME_INTERRUPT_INPUTPORT_START_END_BITS | \
                             FRAME_INTERRUPT_OUTPUT_FORMATTER_SOFEOF_BIT )

/*----------  IRQ MASK STATS  ----------*/
/** Bit mask of stats interrupts in use */
#define IRQ_MASK_STATS ( FRAME_STATS_INTERRUPT_AWB_BITMASK |          \
                         FRAME_STATS_INTERRUPT_ANTIFOG_HIST_BITMASK | \
                         FRAME_STATS_INTERRUPT_METERING_HIST_BITS )

/*----------  MCFE ----------*/
/** Bit mask of mcfe interrupts in use */
#define IRQ_MASK_MCFE ( FRAME_INTERRUPT_MCFE_SLOT_MASK )

/** Number of slots that MCFE can handle */
#define MAX_SLOT_NUM 16

/** Maximum number of sensors attached to the front end. */
#define MAX_FE_SLOT 4


/**
 * @brief      Reads the interrupt registers.
 *
 * @return     Returns the mask of interrupts which have been triggered.
 *
 */
static inline acamera_interrupt_regs_t acamera_read_masked_status( void )
{
    acamera_interrupt_regs_t mask = {0};

    mask.sof = acamera_frontend_interrupts_frame_start_status_read( PHY_ADDR_ISP ) & acamera_frontend_interrupts_frame_start_mask_read( PHY_ADDR_ISP );
    mask.eof = acamera_frontend_interrupts_frame_end_status_read( PHY_ADDR_ISP ) & acamera_frontend_interrupts_frame_end_mask_read( PHY_ADDR_ISP );
    mask.stats = acamera_frontend_interrupts_stats_status_read( PHY_ADDR_ISP ) & acamera_frontend_interrupts_stats_mask_read( PHY_ADDR_ISP );
#if IS_MALI_C71
    mask.mcfe = acamera_frontend_interrupts_mcfe_status_read( PHY_ADDR_ISP ) & acamera_frontend_interrupts_mcfe_mask_read( PHY_ADDR_ISP );
#else
    mask.mcfe = 0;
#endif
    return mask;
}

/**
 * @brief      Reads the interrupt mask.
 *
 * @return     Interrupt mask structure
 */
static inline acamera_interrupt_regs_t acamera_read_interrupt_mask( void )
{
    acamera_interrupt_regs_t mask;
    mask.sof = acamera_frontend_interrupts_frame_start_mask_read( PHY_ADDR_ISP );
    mask.eof = acamera_frontend_interrupts_frame_end_mask_read( PHY_ADDR_ISP );
    mask.stats = acamera_frontend_interrupts_stats_mask_read( PHY_ADDR_ISP );
#if IS_MALI_C71
    mask.mcfe = acamera_frontend_interrupts_mcfe_mask_read( PHY_ADDR_ISP );
#else
    mask.mcfe = 0;
#endif
    return mask;
}

/**
 * @brief      Reads level0 registers for all sources.
 *
 * @return     Interrupt mask structure
 */
static inline acamera_interrupt_regs_t acamera_read_level0( void )
{
    acamera_interrupt_regs_t mask;
    mask.sof = acamera_frontend_interrupts_frame_start_level0_read( PHY_ADDR_ISP );
    mask.eof = acamera_frontend_interrupts_frame_end_level0_read( PHY_ADDR_ISP );
    mask.stats = acamera_frontend_interrupts_stats_level0_read( PHY_ADDR_ISP );
#if IS_MALI_C71
    mask.mcfe = acamera_frontend_interrupts_mcfe_level0_read( PHY_ADDR_ISP );
#else
    mask.mcfe = 0;
#endif
    return mask;
}

/**
 * @brief      Reads level1 registers for all sources.
 *
 * @return     Interrupt mask structure
 *
 */
static inline acamera_interrupt_regs_t acamera_read_level1( void )
{
    acamera_interrupt_regs_t mask;
    mask.sof = acamera_frontend_interrupts_frame_start_level1_read( PHY_ADDR_ISP );
    mask.eof = acamera_frontend_interrupts_frame_end_level1_read( PHY_ADDR_ISP );
    mask.stats = acamera_frontend_interrupts_stats_level1_read( PHY_ADDR_ISP );
#if IS_MALI_C71
    mask.mcfe = acamera_frontend_interrupts_mcfe_level1_read( PHY_ADDR_ISP );
#else
    mask.mcfe = 0;
#endif
    return mask;
}

/**
 * @brief      Writes to level0 registers.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_write_level0( const acamera_interrupt_regs_t mask )
{
    acamera_frontend_interrupts_frame_start_level0_write( PHY_ADDR_ISP, mask.sof );
    acamera_frontend_interrupts_frame_end_level0_write( PHY_ADDR_ISP, mask.eof );
    acamera_frontend_interrupts_stats_level0_write( PHY_ADDR_ISP, mask.stats );
#if IS_MALI_C71
    acamera_frontend_interrupts_mcfe_level0_write( PHY_ADDR_ISP, mask.mcfe );
#endif
}

/**
 * @brief      Writes to level1 registers.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_write_level1( const acamera_interrupt_regs_t mask )
{
    acamera_frontend_interrupts_frame_start_level1_write( PHY_ADDR_ISP, mask.sof );
    acamera_frontend_interrupts_frame_end_level1_write( PHY_ADDR_ISP, mask.eof );
    acamera_frontend_interrupts_stats_level1_write( PHY_ADDR_ISP, mask.stats );
#if IS_MALI_C71
    acamera_frontend_interrupts_mcfe_level1_write( PHY_ADDR_ISP, mask.mcfe );
#endif
}


/**
 * @brief      Writes to the masks registers to enable/disable interrupts.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_write_interrupt_mask( const acamera_interrupt_regs_t mask )
{
    acamera_frontend_interrupts_frame_start_mask_write( PHY_ADDR_ISP, mask.sof );
    acamera_frontend_interrupts_frame_end_mask_write( PHY_ADDR_ISP, mask.eof );
    acamera_frontend_interrupts_stats_mask_write( PHY_ADDR_ISP, mask.stats );
#if IS_MALI_C71
    acamera_frontend_interrupts_mcfe_mask_write( PHY_ADDR_ISP, mask.mcfe );
#endif
}


/**
 * @brief      Writes to the status registers to clear the interrupt.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_clear_interrupt( const acamera_interrupt_regs_t mask )
{
    acamera_frontend_interrupts_frame_start_clear_write( PHY_ADDR_ISP, mask.sof );
    acamera_frontend_interrupts_frame_end_clear_write( PHY_ADDR_ISP, mask.eof );
    acamera_frontend_interrupts_stats_clear_write( PHY_ADDR_ISP, mask.stats );
#if IS_MALI_C71
    acamera_frontend_interrupts_mcfe_clear_write( PHY_ADDR_ISP, mask.mcfe );
#endif
}


/**
 * @brief      Enables the interrupts specified by mask without clearing existing values.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_enable_interrupts( const acamera_interrupt_regs_t mask )
{
    acamera_interrupt_regs_t current_mask = acamera_read_interrupt_mask();
    current_mask.sof |= mask.sof;
    current_mask.eof |= mask.eof;
    current_mask.stats |= mask.stats;
    current_mask.mcfe |= mask.mcfe;
    acamera_write_interrupt_mask( current_mask );
}

/**
 * @brief      Clears given interrupts from the mask, disabling them.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_disable_interrupts( const acamera_interrupt_regs_t mask )
{
    acamera_interrupt_regs_t current_mask = acamera_read_interrupt_mask();
    current_mask.sof &= ~mask.sof;
    current_mask.eof &= ~mask.eof;
    current_mask.stats &= ~mask.stats;
    current_mask.mcfe &= ~mask.mcfe;
    acamera_write_interrupt_mask( current_mask );
}

/**
 * @brief      Sets given level0 bits.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_set_level0( const acamera_interrupt_regs_t mask )
{
    acamera_interrupt_regs_t current_mask = acamera_read_level0();
    current_mask.sof |= mask.sof;
    current_mask.eof |= mask.eof;
    current_mask.stats |= mask.stats;
    current_mask.mcfe |= mask.mcfe;
    acamera_write_level0( current_mask );
}

/**
 * @brief      Clears given level0 bits.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_clear_level0( const acamera_interrupt_regs_t mask )
{
    acamera_interrupt_regs_t current_mask = acamera_read_level0();
    current_mask.sof &= ~mask.sof;
    current_mask.eof &= ~mask.eof;
    current_mask.stats &= ~mask.stats;
    current_mask.mcfe &= ~mask.mcfe;
    acamera_write_level0( current_mask );
}

/**
 * @brief      Sets given level1 bits.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_set_level1( const acamera_interrupt_regs_t mask )
{
    acamera_interrupt_regs_t current_mask = acamera_read_level1();
    current_mask.sof |= mask.sof;
    current_mask.eof |= mask.eof;
    current_mask.stats |= mask.stats;
    current_mask.mcfe |= mask.mcfe;
    acamera_write_level1( current_mask );
}

/**
 * @brief      Clears given level1 bits.
 *
 * @param[in]  mask  Interrupt mask structure
 *
 */
static inline void acamera_clear_level1( const acamera_interrupt_regs_t mask )
{
    acamera_interrupt_regs_t current_mask = acamera_read_level1();
    current_mask.sof &= ~mask.sof;
    current_mask.eof &= ~mask.eof;
    current_mask.stats &= ~mask.stats;
    current_mask.mcfe &= ~mask.mcfe;
    acamera_write_level1( current_mask );
}

/**
 * @brief      Writes to the manual trigger register.
 *
 * @param[in]  trigger  The trigger
 *
 */
static inline void acamera_write_manual_trigger( const uint32_t trigger )
{
    acamera_frontend_interrupts_interrupt_trigger_write( PHY_ADDR_ISP, trigger );
}

acamera_interrupt_regs_t acamera_interrupt_read_acknoledge( void )
{
    const acamera_interrupt_regs_t mask = acamera_read_masked_status();

    /* Here we are assuming that all triggered interrupts will be serviced.
     * This is to clear the status so that the IRQ line is not kept asserted.
     * If there is a possibility that the handler fails to service an interrupt,
     * then perhaps we need to return a mask of interrupts that have been
     * serviced. */
    acamera_clear_interrupt( mask );

    return mask;
}

uint8_t acamera_interrupt_read_current_slot( void )
{
    return acamera_frontend_mcfe_current_slot_read( PHY_ADDR_ISP );
}


#ifdef CMD_QUEUE_DEBUG
static inline void acamera_cmd_queues_debug( const size_t index )
{
    /* Since the function is marked inline, this should be optimized out when
     * CMD_QUEUE_DEBUG is not defined */
    const uint32_t dbg_num = acamera_cmd_queues_array_data_read( PHY_ADDR_ISP, index );
    acamera_cmd_queues_array_data_write( PHY_ADDR_ISP, index, dbg_num + 1 );
}

static inline void acamera_cmd_queues_debug_with_ctx( const size_t index, const size_t ctx )
{
    /* Since the function is marked inline, this should be optimized out when
     * CMD_QUEUE_DEBUG is not defined */
    const uint32_t dbg_num = acamera_cmd_queues_array_data_read( PHY_ADDR_ISP, index );
    acamera_cmd_queues_array_data_write( PHY_ADDR_ISP, index, dbg_num + 1 );
    acamera_cmd_queues_array_data_write( PHY_ADDR_ISP, ( index + 1 ), ctx );
}


static void acamera_cmd_queues_debug_mask( const size_t slot, const size_t mask )
{
    if ( BIT( ACAMERA_IRQ_BE_FRAME_END ) & mask ) {
        acamera_cmd_queues_debug_with_ctx( 2, slot );
    }
    if ( BIT( ACAMERA_IRQ_FE_FRAME_END ) & mask ) {
        acamera_cmd_queues_debug( 6 + ( slot % 4 ) );
    }
    if ( BIT( ACAMERA_IRQ_BE_FRAME_START ) & mask ) {
        acamera_cmd_queues_debug_with_ctx( 10, slot );
    }
    if ( BIT( ACAMERA_IRQ_FE_FRAME_START ) & mask ) {
        acamera_cmd_queues_debug( 12 + ( slot % 4 ) );
    }
}

#endif


#if IS_MALI_C71

/**
 * @brief      Determines if power of two.
 *
 * @param[in]  mask  The mask
 *
 * @return     True if power of two, False otherwise.
 *
 * @details    Used to check if any MCFE interrupts have been missed. If so,
 *             something seriously wrong is going on with ISR handling.
 */
static int is_power_of_two( const uint32_t mask )
{
    return ( mask && !( mask & ( mask - 1 ) ) ) ? 1 : 0;
}
#endif /* IS_MALI_C71 */


#if DEBUG_FRAME_COUNT
static void count_frame_end( const uint32_t slot )
{
    static size_t last_stamps[MAX_SLOT_NUM] = {0};
    static size_t counters[MAX_SLOT_NUM] = {0};
    const size_t fps = 30;


    if ( slot >= MAX_SLOT_NUM ) return;

    if ( ( ++counters[slot] % fps ) == 0 ) {
        const size_t this_stamp = system_timer_timestamp();
        const size_t elapsed_stamp = this_stamp - last_stamps[slot];
        const size_t elapsed_ms = ( elapsed_stamp * 1000 ) / system_timer_frequency();
        const size_t current_fps = ( fps * system_timer_frequency() ) / elapsed_stamp;
        const size_t average_frame_time = elapsed_ms / fps;

        last_stamps[slot] = this_stamp;

        LOG( LOG_NOTICE, "frame end irq, slot %d, count %zu, ftime %zums, fps: %zu",
             slot,
             counters[slot],
             average_frame_time,
             current_fps );
    }
}
#endif

/**
 *
 * @details    This function is responsible for mapping between hard interrupt
 *             bits as set in the registers and logical IRQs (#acamera_irq_t).
 *             The function determines what IRQs to set to which context. There
 *             are a few possibilities:
 *             - Hardcoded slot id in the register, example includes
 *               #FRAME_INTERRUPT_INPUTPORT1_SOFEOF_BIT. These interrupts may
 *               need to be remapped with #module_mcfe_get_slot_id_for_input
 *             - Current slot id. The current active slot can be read with
 *               #acamera_frontend_mcfe_current_slot_read. These interrupts
 *               correspond to the backend.
 *             - Last slot id, because of timing when we detect a new frame
 *               enters the backend we store that information in the
 *               #last_isp_slot variable so that end of frame interrupts for
 *               that context can be processed without worrying about current
 *               active slot.
 *
 *             Here is an example on how to map an interrupt should you wish to
 *             add more functionality:
 *
 * @code
 * void acamera_interrupt_handler( void *param )
 * {
 *      const acamera_interrupt_regs_t mask = ( *( (isr_data_t *)param ) ).regs;
 *      const uint8_t curr_slot = ( *( (isr_data_t *)param ) ).slot;
 *      static uint8_t last_isp_slot = MAX_SLOT_NUM;
 *
 *      uint32_t irq_masks[MAX_SLOT_NUM] = {0};
 *
 *      if( mask.<register> & DESIRED_BIT ) {
 *          irq_masks[<desired_slot>] |= BIT( <IRQ_NUMBER> );
 *      }
 * }
 * @endcode
 * @details    The IRQ bitmask together with slot id will then be passed to
 *             #acamera_process_interrupt
 */
void acamera_interrupt_handler( void *param )
{
	LOG(LOG_LEVEL_CRIT, "%s E ", __FUNCTION__);
	uint32_t curr = system_isp_read_32(0xe80c0000 + 0x80);
	printf("0x80:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0x88);
	printf("0x88:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0x9c);
	printf("0x9c:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0xac);
	printf("0xac:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0xb4);
	printf("0xb4:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0xc4);
	printf("0xc4:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0xcc);
	printf("0xcc:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0xe720);
	printf("0xe720:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0xe724);
	printf("0xe724:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0xe728);
	printf("0xe728:0x%2x\n",curr);
	curr = system_isp_read_32(0xe80c0000 + 0xe72c);
	printf("0xe72c:0x%2x\n",curr);
	const acamera_interrupt_regs_t mask = acamera_interrupt_read_acknoledge();
	return;
#if 0
    assert( param ); // This function should *not* be called with NULL parameters.

	const acamera_interrupt_regs_t mask = acamera_interrupt_read_acknoledge();
	const uint8_t curr_slot =  acamera_interrupt_read_current_slot();
    /* Extract IRQ information, these are the inputs to the handler. */
    //const acamera_interrupt_regs_t mask = ( (isr_data_t *)param )->regs;
    //const uint8_t curr_slot = ( (isr_data_t *)param )->slot;

    static uint8_t last_isp_slot = MAX_SLOT_NUM;
    uint32_t irq_masks[MAX_SLOT_NUM] = {0}; // Stores the IRQ mask for each of the slots. This should be
                                            // relativively low, since max slot number is 16 so stack size
                                            // shouldn't be a problem.


#ifdef CMD_QUEUE_DEBUG
    static int cnt = 0;
    acamera_cmd_queues_array_data_write( PHY_ADDR_ISP, 0, ++cnt );
    acamera_cmd_queues_debug( 1 );
#endif


/*
 * ########### BACK END : FRAME END ###########
 *
 *  - For MALI_C71 if CDMA_AS_BE_EOF is set we use the MCFE slot done interrupt
 *    to trigger the back end-end of frame. We check which slot is set in the
 *    MCFE register and set the #ACAMERA_IRQ_BE_FRAME_END IRQ for that slot.
 *  - For MALI_C71 if CDMA_AS_BE_EOF is not set and for non MALI_C71 builds we
 *    use the #FRAME_INTERRUPT_OUTPUT_FORMATTER_SOFEOF_BIT in the EoF register.
 *    We rely on the logical flow of frames and make the assumption that the
 *    last read active slot to trigger SoF will also be the slot id to trigger
 *    EoF.
 */
#if IS_MALI_C71
    if ( CDMA_AS_BE_EOF ) {
        // ----------- ISP MCFE CDMA out ------------
        if ( mask.mcfe & FRAME_INTERRUPT_MCFE_SLOT_MASK ) {
            const uint32_t mcfe_slot_mask = mask.mcfe >> 4;

            if ( !is_power_of_two( mcfe_slot_mask ) ) {
                LOG( LOG_ERR, "More than one MCFE slot done, failed to proccess previous slot (MCFE:0x%x).", mcfe_slot_mask );
            }

            uint8_t slot;
            /* coverity[same_on_both_sides] */
            for ( slot = 0; slot < MIN( MAX_SLOT_NUM, FIRMWARE_CONTEXT_NUMBER ); ++slot ) {
                if ( mcfe_slot_mask & ( 1u << slot ) ) {
                    if ( slot != last_isp_slot ) {
                        LOG( LOG_ERR, "FS slot %u doesn't match CDMA out slot %u!!!", last_isp_slot, slot );
                    }
                    // No need for range check, it has to be correct due to
                    // loop constraint.
                    irq_masks[slot] |= BIT( ACAMERA_IRQ_BE_FRAME_END );
#if DEBUG_FRAME_COUNT
                    count_frame_end( slot );
#endif
                }
            }
        }
    } else
#endif /* IS_MALI_C71 */
    {
        // ----------- ISP FRAME END --------------
        if ( mask.eof & FRAME_INTERRUPT_OUTPUT_FORMATTER_SOFEOF_BIT ) {
            // Skip processing when prev_slot is not valid.
            if ( last_isp_slot < MAX_SLOT_NUM ) {
                irq_masks[last_isp_slot] |= BIT( ACAMERA_IRQ_BE_FRAME_END );
            } else {
                LOG( LOG_ERR, "Frame end received before frame start on first processing!!!" );
            }
        }
    }


    /*
     * ########### FRONT END: FRAME START/END ###########
     *
     * Loop over #MAX_FE_SLOT slots corresponding to the register bits and
     * figure out the interrupt mask for SoF and EoF (shared bit layout). Since
     * this is a front end hard slot id it may be remapped in the  firmware. We
     * can look up the correct slot id with #module_mcfe_get_slot_id_for_input
     *
     * 1. If EoF is set for the slot then trigger #ACAMERA_IRQ_FE_FRAME_END.
     * 2. If SoF is set for the slot then trigger #ACAMERA_IRQ_FE_FRAME_START
     */
    {
        uint8_t slot;
        for ( slot = 0; slot < MAX_FE_SLOT; ++slot ) {
#if defined( ISP_HAS_MCFE_FSM )
            const int remapped_slot_id = module_mcfe_get_slot_id_for_input( slot, MODULE_MCFE_SLOT_INPUT_FIRST_ONLY );
            // If this is -1 then it has not been mapped. If it is larger than
            // MAX_SLOT_NUM then something is horribly wrong.
            if ( remapped_slot_id < 0 || remapped_slot_id >= MAX_SLOT_NUM ) continue;
#endif

            /* SOF and EOF share the same bitmask so we can calculate it once. */
            const uint16_t sofeof_mask = FRAME_INTERRUPT_INPUTPORT1_SOFEOF_BIT << slot;
            uint32_t irq_mask = 0; // Stores IRQ events for this slot.

            if ( mask.eof & sofeof_mask )
                irq_mask |= BIT( ACAMERA_IRQ_FE_FRAME_END );

            if ( mask.sof & sofeof_mask ) {
                irq_mask |= BIT( ACAMERA_IRQ_FE_FRAME_START );

#if !ISP_HISTOGRAM_POSITION_IS_BE
                if ( last_isp_slot < MAX_SLOT_NUM ) irq_masks[last_isp_slot] |= BIT( ACAMERA_IRQ_AE_STATS );
#endif
            }

            // By this point we know the index is correct so we do not need to check.

#if defined( ISP_HAS_MCFE_FSM )
            irq_masks[remapped_slot_id] |= irq_mask;
#else
            irq_masks[slot] |= irq_mask;
#endif
        }
    }

    /*
     * ########### BACK END : FRAME START ###########
     * 1. Frame enters back end, trigger #ACAMERA_IRQ_BE_FRAME_START for the new frame slot id.
     * 2. By *implication* the stats for previous slot id must be ready so trigger stat IRQs.
     */
    if ( mask.sof & FRAME_INTERRUPT_OUTPUT_FORMATTER_SOFEOF_BIT ) {
        if ( last_isp_slot < MAX_SLOT_NUM ) {
            irq_masks[last_isp_slot] |= BIT( ACAMERA_IRQ_ANTIFOG_HIST ) |
                                        BIT( ACAMERA_IRQ_AWB_STATS ) |
                                        BIT( ACAMERA_IRQ_AE_METERING_STATS );

#if ISP_HISTOGRAM_POSITION_IS_BE
            irq_masks[last_isp_slot] |= BIT( ACAMERA_IRQ_AE_STATS );
#endif
        }

        irq_masks[curr_slot] |= BIT( ACAMERA_IRQ_BE_FRAME_START );
        last_isp_slot = curr_slot;
    }

    /*
     * ########### Per context logical IRQ handler ###########
     */
    {
        uint8_t slot;
        for ( slot = 0; slot < MAX_SLOT_NUM; ++slot ) {
            if ( irq_masks[slot] )
                acamera_process_interrupt( slot, irq_masks[slot] );
        }
    }
#endif
}


void acamera_interrupt_init( void )
{
    const acamera_interrupt_regs_t mask = {.sof = IRQ_MASK_FRAME_START,
                                           .eof = IRQ_MASK_FRAME_END,
                                           .stats = IRQ_MASK_STATS,
                                           .mcfe = IRQ_MASK_MCFE};
    /* Ensure all interrupts are off. */
    acamera_interrupt_disable();
    acamera_write_manual_trigger( 0 );

    acamera_clear_interrupt( mask );

    /* Set up register values. */
    acamera_clear_level0( mask );
    acamera_clear_level1( mask );
}


void acamera_interrupt_enable( void )
{
    const acamera_interrupt_regs_t mask = {.sof = IRQ_MASK_FRAME_START,
                                           .eof = IRQ_MASK_FRAME_END,
                                           .stats = IRQ_MASK_STATS,
                                           .mcfe = IRQ_MASK_MCFE};
    //const acamera_interrupt_regs_t mask = {.sof = 0,
    //                                       .eof = 0,
    //                                       .stats = 0,
    //                                       .mcfe = 0x10};
    acamera_enable_interrupts( mask );
}


void acamera_interrupt_disable( void )
{
    const acamera_interrupt_regs_t mask = {.sof = -1,
                                           .eof = -1,
                                           .stats = -1,
                                           .mcfe = -1};
    acamera_disable_interrupts( mask );
}
void acamera_interrupt_deinit( void )
{
    const acamera_interrupt_regs_t mask = {.sof = -1,
                                           .eof = -1,
                                           .stats = -1,
                                           .mcfe = -1};
    acamera_interrupt_disable();
    acamera_clear_interrupt( mask );
}

/** @} */
