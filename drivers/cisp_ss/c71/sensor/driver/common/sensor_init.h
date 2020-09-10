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

#ifndef __SENSOR_INIT_H__
#define __SENSOR_INIT_H__

#include "acamera_configuration.h" //For SENSOR_SEQ_BINARY_AND_EXTERNAL
#include "acamera_sbus_api.h"


#if SENSOR_SEQ_BINARY_AND_EXTERNAL == 1
#define sensor_load_sequence sensor_load_binary_sequence
#else
#define sensor_load_sequence sensor_load_array_sequence
#endif

typedef struct sensor_reg_t {
    uint16_t address;
    uint16_t value;
} sensor_reg_t;

void sensor_load_binary_sequence( acamera_sbus_ptr_t p_sbus, char size, const char *sequence, int group );
void sensor_load_array_sequence( acamera_sbus_ptr_t p_sbus, char size, const sensor_reg_t *sequence, int group_start_idx );

#endif /* __SENSOR_INIT_H__ */
