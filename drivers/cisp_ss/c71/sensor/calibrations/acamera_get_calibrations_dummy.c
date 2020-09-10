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

#include "acamera_command_api.h"
#include "acamera_logger.h"

extern int32_t get_calibrations_static_linear_dummy( void *param );
extern int32_t get_calibrations_dynamic_linear_dummy( void *param );

int32_t get_calibrations_dummy( uint32_t wdr_mode, void *param )
{
    int32_t ret = 0;

    switch ( wdr_mode ) {
    case WDR_MODE_LINEAR:
        LOG( LOG_DEBUG, "calibration switching to WDR_MODE_LINEAR %d ", (int)wdr_mode );
        ret += ( get_calibrations_dynamic_linear_dummy( param ) + get_calibrations_static_linear_dummy( param ) );
    }

    return ret;
}
