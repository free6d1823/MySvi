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

#ifndef __COMMON_PARAMS_H__
#define __COMMON_PARAMS_H__

#include "system_types.h"


// ------------------------------------------------------------------------------ //
//		ISP PARAMETERS CLASS
// ------------------------------------------------------------------------------ //
#define ISP_PARAM_CLASS_MASK 0x00000080
#define ISP_PARAM_CLASS_MAX 0x00000004


// ------------------------------------------------------------------------------ //
//		CONTEXT PARAMETERS CLASS
// ------------------------------------------------------------------------------ //
#define CONTEXT_PARAM_CLASS_MASK 0x00000100
#define CONTEXT_PARAM_CLASS_MAX 0x0000004E


// ------------------------------------------------------------------------------ //
//		PARAM FLAGS
// ------------------------------------------------------------------------------ //
#define PARAM_FLAG_READ 0x00000001
#define PARAM_FLAG_WRITE 0x00000002
#define PARAM_FLAG_RECONFIG 0x00000004
#define PARAM_FLAG_RECONFIG_ON_LIST_VALUE 0x00000008
#define PARAM_FLAG_RECONFIG_ON_TRUE_DEFAULT_RESET 0x00000010
#define PARAM_FLAG_REGISTER_REQUEST 0x00000020
#define PARAM_FLAG_STOP_ON_FALSE 0x00000040
#define PARAM_FLAG_START_ON_TRUE 0x00000080
#define PARAM_FLAG_HANDLER_FUNCTION 0x00000100


// ------------------------------------------------------------------------------ //
//		PARAM TYPE AND HANDLER FUNCTION DEFINITION
// ------------------------------------------------------------------------------ //
typedef struct _param_list_value {
    uint32_t value;
    uint32_t flags;
} param_list_value;

typedef uint8_t ( *param_handler_t )( void *instance, uint32_t set_value, uint8_t direction, uint32_t *get_value );

typedef struct _common_param {
    uint32_t value;
    uint32_t default_value;
    uint32_t min;
    uint32_t max;
    uint32_t flags;
    param_list_value *values_list;
    param_handler_t param_handler;
} common_param;

#endif //__COMMON_PARAMS_H__
