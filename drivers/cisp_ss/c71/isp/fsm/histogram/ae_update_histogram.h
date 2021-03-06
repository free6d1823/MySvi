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

#include "acamera_isp_ctx.h"

void ae_histogram_dgain_compensation( histogram_fsm_ptr_t p_fsm );
void ae_histogram_pipeline_update( histogram_fsm_const_ptr_t p_fsm );
void configure_histogram_neq_lut( histogram_fsm_const_ptr_t p_fsm );
void histogram_configure_position( histogram_fsm_const_ptr_t p_fsm );
