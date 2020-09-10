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

#include "acamera_configuration.h"
#include "acamera_settings.h"


// extern functions for dummy sensor
//extern void sensor_init_dummy( void **, uint8_t location, sensor_control_t *ctrl, const sensor_options_t *const );
//extern int32_t get_calibrations_dummy( uint32_t wdr_mode, void *param );

extern void sensor_init_ar0231_demo( void **, uint8_t location, sensor_control_t *ctrl, const sensor_options_t *const );
extern int32_t get_calibrations_ar0231( uint32_t wdr_mode, void *param );

// Context settings
static acamera_settings settings[FIRMWARE_CONTEXT_NUMBER] = {
#if ( FIRMWARE_CONTEXT_NUMBER >= 1 )
    {
        .sensor_init = sensor_init_ar0231_demo,//sensor_init_dummy,
        .sensor_name = "AR0231_DEMO",

        .sensor_options = {
            .is_remote = 1,
            .preset_mode = 0,
        },

        .get_calibrations = get_calibrations_ar0231,//get_calibrations_dummy,

        .isp_base = 0,
    },
#endif
#if ( FIRMWARE_CONTEXT_NUMBER >= 2 )
    {
        .sensor_init = NULL,//sensor_init_dummy,
        .sensor_name = "DUMMY",

        .sensor_options = {
            .is_remote = 0,
            .preset_mode = 0,
        },

        .get_calibrations = NULL,//get_calibrations_dummy,

        .isp_base = 0,
    },
#endif
#if ( FIRMWARE_CONTEXT_NUMBER >= 3 )
    {
        .sensor_init = NULL,//sensor_init_dummy,
        .sensor_name = "DUMMY",

        .sensor_options = {
            .is_remote = 1,
            .preset_mode = 0,
        },

        .get_calibrations = NULL,//get_calibrations_dummy,

        .isp_base = 0,
    },
#endif
#if ( FIRMWARE_CONTEXT_NUMBER >= 4 )
    {
        .sensor_init = NULL,//sensor_init_dummy,
        .sensor_name = "DUMMY",

        .sensor_options = {
            .is_remote = 1,
            .preset_mode = 0,
        },

        .get_calibrations = NULL,//get_calibrations_dummy,

        .isp_base = 0,
    },
#endif
};
