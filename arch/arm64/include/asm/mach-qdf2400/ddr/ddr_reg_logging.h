#ifndef __DDR_REG_LOGGING_H__
#define __DDR_REG_LOGGING_H__

/**
 * @file ddr_reg_logging.h
 * @brief
 * Header file for the memory subsystem register logging

 Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc

 Copyright (c) 2016 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.

==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <target/ddr/ddr_common.h>
#include <asm/mach/ddr/ddr_target.h>
#include <asm/mach/hal/HALmemoryHWIO.h>

/*==========================================================================
                             DEFINED CONSTANTS
===========================================================================*/

/*===========================================================================
                                 DATA
===========================================================================*/ 

/*==============================================================================
                                  STRUCTURE
==============================================================================*/

typedef union _memory_controller_register_values {
    struct mc_values_by_name
    {
        uint32_t D_ERR_STATUS;
    } mc_values;
    uint32_t values_array[1];
} memory_controller_register_values;

typedef union _l3_cache_register_values {
    struct l3_values_by_name
    {
        uint32_t APCS_MBSU_L3_HML3_FIRA;
    } l3_values;
    uint32_t values_array[1];
} l3_cache_register_values;

typedef struct _other_register_values {
    struct other_values_by_name
    {
        uint32_t SPARE3;
    } other_values;
    uint32_t values_array[1];
} other_register_values;

typedef struct _register_snapshot {
    memory_controller_register_values mc_vals[NUM_MEMORY_CONTROLLERS];
    l3_cache_register_values l3_vals[NUM_L3_CACHES];
    other_register_values other_vals;
} register_snapshot;

/*===========================================================================
                         FUNCTION DECLARATIONS
===========================================================================*/ 
int log_registers_init(uint64_t l3_pg, uint64_t mc_pg);
int log_memory_status_registers(register_snapshot* reg_snapshot);

#endif
