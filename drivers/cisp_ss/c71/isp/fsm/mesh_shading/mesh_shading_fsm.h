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

#if !defined( __MESH_SHADING_FSM_H__ )
#define __MESH_SHADING_FSM_H__


typedef struct _mesh_shading_fsm_t mesh_shading_fsm_t;
typedef struct _mesh_shading_fsm_t *mesh_shading_fsm_ptr_t;
typedef const struct _mesh_shading_fsm_t *mesh_shading_fsm_const_ptr_t;

enum _mesh_shading_state_t {
    mesh_shading_state_initialized,
    mesh_shading_state_configured,
    mesh_shading_state_reload_calibration,
    mesh_shading_state_ready,
    mesh_shading_state_stopped,
    mesh_shading_state_deinit,
    mesh_shading_state_update_hw,
    mesh_shading_state_invalid
};

typedef enum _mesh_shading_state_t mesh_shading_state_t;

#include "acamera_fsmgr_general_router.h"

void mesh_shading_init( mesh_shading_fsm_ptr_t p_fsm );
void mesh_shading_reload_calibration( mesh_shading_fsm_ptr_t p_fsm );
void mesh_shading_update_hw( mesh_shading_fsm_ptr_t p_fsm );
void mesh_shading_deinit( mesh_shading_fsm_ptr_t p_fsm );

struct _mesh_shading_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    mesh_shading_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    int16_t shading_alpha;
    int32_t temperature_threshold[8];
};


void mesh_shading_fsm_clear( mesh_shading_fsm_ptr_t p_fsm );
void mesh_shading_fsm_switch_state( mesh_shading_fsm_ptr_t p_fsm, mesh_shading_state_t state );
void mesh_shading_fsm_process_state( mesh_shading_fsm_ptr_t p_fsm );
uint8_t mesh_shading_fsm_process_event( mesh_shading_fsm_ptr_t p_fsm, event_id_t event_id );

void mesh_shading_fsm_process_interrupt( mesh_shading_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void mesh_shading_request_interrupt( mesh_shading_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __MESH_SHADING_FSM_H__ */
