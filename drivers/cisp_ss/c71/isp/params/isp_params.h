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

#ifndef __ISP_PARAMS_H__
#define __ISP_PARAMS_H__

#include "common_params.h"


// ------------------------------------------------------------------------------ //
//		CONTEXT CLASS PARAMETERS
// ------------------------------------------------------------------------------ //
#define ACTIVE_CONTEXT_PARAM 0x00000080
#define CONTEXT_NUMBER_PARAM 0x00000081
#define FW_REVISION_PARAM 0x00000082
#define SYSTEM_LOGGER_LEVEL_PARAM 0x00000083
#define SYSTEM_LOGGER_MASK_PARAM 0x00000084


// ------------------------------------------------------------------------------ //
//		ISP PARAM TYPE DEFINITION
// ------------------------------------------------------------------------------ //
typedef struct _isp_params {
    common_param params[ISP_PARAM_CLASS_MAX + 1];
} isp_params;


// ------------------------------------------------------------------------------ //
//		PARAM INIT FUNCTION
// ------------------------------------------------------------------------------ //
void init_isp_params( isp_params *params );


#endif //__ISP_PARAMS_H__
