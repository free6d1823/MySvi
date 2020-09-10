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

#ifndef _MODULE_MCFE_COMMON_H_
#define _MODULE_MCFE_COMMON_H_

#include "system_stdlib.h"
#include "acamera_configuration.h"
#include "acamera_isp_config.h"
#include "acamera_logger.h"

/* MCFE errors */
#define MCFE_ERR_NONE ( 0 )
#define MCFE_ERR_GENERAL ( -1 )
#define MCFE_ERR_INV_PARM ( -2 )
#define MCFE_ERR_NOT_INIT ( -3 )
#define MCFE_ERR_NOT_RUN ( -4 )
#define MCFE_ERR_BUSY ( -5 )
#define MCFE_ERR_NO_RES ( -6 )

/* Default values */
#define MODULE_MCFE_DEFAULT_WIDTH 1920
#define MODULE_MCFE_DEFAULT_HEIGHT 1080
#define MODULE_MCFE_DEFAULT_HC_START 0
#define MODULE_MCFE_DEFAULT_VC_START 0

/* Max capability information */
#define MODULE_MCFE_SLOT_ARRAY_SIZE 16
#define MODULE_MCFE_INPUT_PORT_MAX 4

#define MODULE_MCFE_MSB_ALIGN_INPUT 0x1

#define MODULE_MCFE_SLOT_INPUT_FIRST_ONLY 1
#define MODULE_MCFE_SLOT_INPUT_ALL_INPUTS 0

#define MODULE_MCFE_BUFSET_MAX_FRAMES 2

#endif
