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

#ifndef _MODULE_MCFE_USECASE_H_
#define _MODULE_MCFE_USECASE_H_

#include "acamera_frame_stream_api.h"
#include "module_mcfe.h"
#include "module_mcfe_service.h"


/* Types and definitions */
typedef enum {
    MODULE_MCFE_USECASE_NONE,
    MODULE_MCFE_USECASE_TDMF,
    MODULE_MCFE_USECASE_MANUAL,
    MODULE_MCFE_USECASE_MAX = MODULE_MCFE_USECASE_MANUAL
} module_mcfe_usecase_type_t;

typedef enum {
    MODULE_MCFE_USECASE_RAW_STREAM_CONFIGURED = ( 1U << 0 ),
    MODULE_MCFE_USECASE_OUT_STREAM_CONFIGURED = ( 1U << 1 ),
    MODULE_MCFE_USECASE_RAW_BUFSET_CONFIGURED = ( 1U << 2 ),
    MODULE_MCFE_USECASE_OUT_BUFSET_CONFIGURED = ( 1U << 3 ),
    MODULE_MCFE_USECASE_SLOT_CONFIGURED = ( 1U << 4 ),
    MODULE_MCFE_USECASE_INPUT_CONFIGURED = ( 1U << 5 ),
} module_mcfe_usecase_config_state_t;

struct _module_mcfe_usecase_config_t;
typedef struct _module_mcfe_usecase_config_t module_mcfe_usecase_config_t;

typedef struct module_mcfe_usecase_config_states_t {
    unsigned char reqd; // Required config state to run use-case
    unsigned char curr; // Current config state
    unsigned char last; // Config state on last check
} module_mcfe_usecase_config_states_t;

typedef struct _module_mcfe_usecase_functbl_t {
    int ( *config )( module_mcfe_usecase_config_t *, module_mcfe_sensor_cfg_t *, module_mcfe_output_cfg_t * );
    int ( *start )( module_mcfe_usecase_config_t * );
    int ( *stop )( module_mcfe_usecase_config_t * );
    int ( *process_event )( module_mcfe_usecase_config_t *, module_mcfe_event_t event );
    int ( *release_resources )( module_mcfe_usecase_config_t * );
} module_mcfe_usecase_functbl_t;

typedef struct _module_mcfe_usecase_config_t {
    int initialized;
    int started;
    module_mcfe_usecase_config_states_t config_states;
    module_mcfe_usecase_type_t type;
    mcfe_slot_id_t slot_id;
    module_mcfe_slot_mode_t slot_mode;
    module_mcfe_usecase_functbl_t functions;
    module_mcfe_sensor_cfg_t sensor_config;
    module_mcfe_output_cfg_t output_config;
    module_mcfe_bufset_t *bufset_raw;
    module_mcfe_bufset_t *bufset_out;
    aframe_t *remote_sensor_frame;
    module_mcfe_input_port_ids_t input_port_ids;
    int video_input_idx;
    uint8_t hist_position_is_be;

} module_mcfe_usecase_config_t;

typedef int ( *module_mcfe_usecase_init_func_t )( module_mcfe_usecase_config_t *, mcfe_slot_id_t, int hist_position_is_be );
typedef int ( *module_mcfe_usecase_deinit_func_t )( module_mcfe_usecase_config_t * );

/* Init, deinit */
int module_mcfe_usecase_init( module_mcfe_usecase_config_t *, module_mcfe_usecase_type_t type, mcfe_slot_id_t slot_id, int hist_position_is_be );
int module_mcfe_usecase_deinit( module_mcfe_usecase_config_t * );

#endif
