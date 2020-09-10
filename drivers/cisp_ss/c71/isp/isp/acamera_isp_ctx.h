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

#if !defined( __ACAMERA_ISP_CTX_H__ )
#define __ACAMERA_ISP_CTX_H__

#include "acamera_calib_mgr.h"
#include "acamera_settings.h"

#include "system_semaphore.h"
#include "system_types.h"

#include "context_params.h"

struct _acamera_isp_ctx_t;
typedef struct _acamera_isp_ctx_t acamera_isp_ctx_t;
typedef struct _acamera_isp_ctx_t *acamera_isp_ctx_ptr_t;

/* Note: this header include should be placed after acamera_isp_ctx_t type definition
         and this creates dependency between isp-ctx and fsm-mgr. */
#include "acamera_fsmgr.h"


#define FW_PAUSE 0
#define FW_RUN 1

#define ACAMERA_FSMGR2ICTX_PTR( p_fsmgr ) \
    ( ( p_fsmgr )->p_ictx )

#define ACAMERA_FSM2FSMGR_PTR( p_fsm ) \
    ( ( p_fsm )->p_fsmgr )

#define ACAMERA_FSM2ICTX_PTR( p_fsm ) \
    ( ( p_fsm )->p_fsmgr->p_ictx )

#define ACAMERA_FSM_GET_FW_ID( p_fsm ) \
    ( ( p_fsm )->p_fsmgr->p_ictx->context_id )

#define ACAMERA_FSMGR2CM_PTR( p_fsmgr ) \
    ( ( p_fsmgr )->p_ictx->calib_mgr_data )

#define ACAMERA_FSM2CM_PTR( p_fsm ) \
    ( ( p_fsm )->p_fsmgr->p_ictx->calib_mgr_data )


struct _acamera_isp_ctx_t {
#if ACAMERA_ISP_PROFILING
    // Profiler variables
    volatile uint32_t binit_profiler;
    volatile uint32_t breport_profiler;
    volatile uint32_t start_profiling;
    volatile uint32_t stop_profiling;
#endif

    // Frame counters
    volatile uint32_t fe_frame_counter;
    volatile uint32_t be_frame_counter;
    volatile uint32_t dfe_frame_counter;
    volatile uint32_t frame_end_counter;
    volatile uint32_t awb_stats_counter;
    volatile uint32_t ae_stats_counter;

    // Context
    uint32_t context_id;

    // Shared semaphore
    semaphore_t sync_sem;

    // Context FSM manager
    acamera_fsmgr_t fsmgr;

    // Context calibration
    acamera_calib_mgr_entry_t *calib_mgr_data;

    // Context settings
    acamera_settings settings;

    // Context specific API params
    context_params params;
};


////////////////////////////////////////////////////
// isp_ctx API functions

int32_t acamera_isp_ctx_init( acamera_isp_ctx_ptr_t p_ictx, acamera_settings *settings );

void acamera_isp_ctx_deinit( acamera_isp_ctx_ptr_t p_ictx );

void acamera_isp_ctx_fsm_config( acamera_isp_ctx_ptr_t p_ictx );

void acamera_isp_ctx_fsm_start( acamera_isp_ctx_ptr_t p_ictx );

void acamera_isp_ctx_fsm_stop( acamera_isp_ctx_ptr_t p_ictx );

void acamera_isp_ctx_fsm_deinit( acamera_isp_ctx_ptr_t p_ictx );

void acamera_isp_ctx_process_interrupt( acamera_isp_ctx_ptr_t p_ictx, uint8_t event );

int32_t acamera_isp_ctx_process_event( acamera_isp_ctx_ptr_t p_ictx );


////////////////////////////////////////////////////
// FSM helper functions

void acamera_isp_ctx_load_custom_settings( acamera_isp_ctx_ptr_t p_ictx );

int32_t acamera_isp_ctx_load_calibrations( acamera_isp_ctx_ptr_t p_ictx, uint32_t wdr_mode );

int32_t acamera_isp_ctx_load_settings( acamera_isp_ctx_ptr_t p_ictx, uint32_t wdr_mode );


////////////////////////////////////////////////////
// Context param handlers

uint32_t get_context_param( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id );

void set_context_param( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id, uint32_t value );

void override_context_param( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id, uint32_t value );

uint8_t handle_context_param( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id, uint8_t direction, uint32_t set_value, uint32_t *get_value );


#endif // __ACAMERA_ISP_CTX_H__
