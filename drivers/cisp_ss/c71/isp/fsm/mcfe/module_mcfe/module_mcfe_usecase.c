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

/**************************************************
 * Headers
 **************************************************/
#include "module_mcfe_usecase.h"
#include "module_mcfe.h"
#include "module_mcfe_common.h"
#include "module_mcfe_service.h"

extern int module_mcfe_usecase_init_tdmf( module_mcfe_usecase_config_t *, mcfe_slot_id_t, int );
extern int module_mcfe_usecase_init_manual( module_mcfe_usecase_config_t *, mcfe_slot_id_t, int );
module_mcfe_usecase_init_func_t usecase_type_init_funcs[MODULE_MCFE_USECASE_MAX] = {
    module_mcfe_usecase_init_tdmf,
    module_mcfe_usecase_init_manual,
};

extern int module_mcfe_usecase_deinit_tdmf( module_mcfe_usecase_config_t * );
extern int module_mcfe_usecase_deinit_manual( module_mcfe_usecase_config_t * );
module_mcfe_usecase_deinit_func_t usecase_type_deinit_funcs[MODULE_MCFE_USECASE_MAX] = {
    module_mcfe_usecase_deinit_tdmf,
    module_mcfe_usecase_deinit_manual,
};

/**************************************************
 * Init, deinit
 **************************************************/
int module_mcfe_usecase_init( module_mcfe_usecase_config_t *config, module_mcfe_usecase_type_t type, mcfe_slot_id_t slot_id, int hist_position_is_be )
{
    // Check input parameters.
    if ( config == NULL ) {
        LOG( LOG_ERR, "Error. Invalid parameter. Instance pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    if ( ( type <= MODULE_MCFE_USECASE_NONE ) || ( type > MODULE_MCFE_USECASE_MAX ) ) {
        LOG( LOG_ERR, "Error. Invalid parameter. Type value is out of range: %d.", type );
        return MCFE_ERR_INV_PARM;
    }

    if ( slot_id >= MODULE_MCFE_SLOT_ARRAY_SIZE ) {
        LOG( LOG_ERR, "Error. Invalid parameter. Slot id value is out of range: %u.", slot_id );
        return MCFE_ERR_INV_PARM;
    }

    if ( hist_position_is_be != 0 && hist_position_is_be != 1 ) {
        LOG( LOG_ERR, "Error. Invalid parameter. Histogram position value is out of range: %d.", hist_position_is_be );
        return MCFE_ERR_INV_PARM;
    }

    return usecase_type_init_funcs[type - 1]( config, slot_id, hist_position_is_be );
}

int module_mcfe_usecase_deinit( module_mcfe_usecase_config_t *config )
{
    // Check input parameters.
    if ( config == NULL ) {
        LOG( LOG_ERR, "Error. Invalid parameter. Instance pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    if ( ( config->type <= MODULE_MCFE_USECASE_NONE ) || ( config->type > MODULE_MCFE_USECASE_MAX ) ) {
        LOG( LOG_ERR, "Error. Invalid parameter. Type value is out of range: %d.", config->type );
        return MCFE_ERR_INV_PARM;
    }

    return usecase_type_deinit_funcs[config->type - 1]( config );
}
