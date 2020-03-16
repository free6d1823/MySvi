/**
 * @file:  voltplan_target_defs.h
 * @brief:
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 * Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 *
 */
#ifndef _VOLTPLAN_TARGET_DEFS_H
#define _VOLTPLAN_TARGET_DEFS_H

#define IS_GLOBAL_CPR_RAIL(rail) ((VOLTPLAN_RAIL_MX<=rail && rail<VOLTPLAN_RAIL_MISC_MAX) \
                                || (VOLTPLAN_RAIL_CBF<=rail && rail<VOLTPLAN_RAIL_MAX))

#define IS_LOCAL_CPR_RAIL(rail) (VOLTPLAN_RAIL_APR0<=rail && rail<VOLTPLAN_RAIL_APR_MAX)

#define VOLTPLAN_MAX_RAILS ((VOLTPLAN_RAIL_MISC_MAX-VOLTPLAN_RAIL_MX) +\
                            (VOLTPLAN_RAIL_APR_MAX - VOLTPLAN_RAIL_APR0) +\
                            (VOLTPLAN_RAIL_MAX - VOLTPLAN_RAIL_CBF))

#define IS_RAIL_SUPPORTED(rail) ((VOLTPLAN_RAIL_MX<=rail && rail<VOLTPLAN_RAIL_MISC_MAX) \
                                || (VOLTPLAN_RAIL_APR0<=rail && rail<VOLTPLAN_RAIL_APR_MAX)\
                                || (VOLTPLAN_RAIL_CBF<=rail && rail<VOLTPLAN_RAIL_MAX))


#define IS_APC_RAIL(rail) (VOLTPLAN_RAIL_CVR<=rail && rail<VOLTPLAN_RAIL_APR_MAX)
#define IS_CBF_RAIL(rail) (VOLTPLAN_RAIL_CBF==rail)


/** CAUTION ** closely examin the macro definitions in this file before
 * changing the order of enums below */
typedef enum
{
    // Core rails
    VOLTPLAN_RAIL_MX     = 0x100,
    VOLTPLAN_RAIL_CX,
    VOLTPLAN_RAIL_VDN,
    VOLTPLAN_RAIL_VDS,
    VOLTPLAN_RAIL_MISC_MAX,

    // APC rails
    VOLTPLAN_RAIL_CVR   = 0x200,
    VOLTPLAN_RAIL_APR0   = VOLTPLAN_RAIL_CVR,
    VOLTPLAN_RAIL_APR1,
    VOLTPLAN_RAIL_APR2,
    VOLTPLAN_RAIL_APR3,
    VOLTPLAN_RAIL_APR4,
    VOLTPLAN_RAIL_APR5,
    VOLTPLAN_RAIL_APR6,
    VOLTPLAN_RAIL_APR7,
    VOLTPLAN_RAIL_APR_MAX,

    VOLTPLAN_RAIL_CBF,
    VOLTPLAN_RAIL_MAX

} voltplan_domain_id;

/**** AVM Definition *****/

/**
 * Target specific Constants - will not change ever for AW
 */
#define VOLTPLAN_AVM_SUPPORTED         (1)
#define VOLTPLAN_AVM_NUM_CORNERS       (4)
#define VOLTPLAN_AVM_NUM_FREQ_STEPS    (30)
#define VOLTPLAN_AVM_FIXED_CEIL_uV     (1200 * 1000)
/* each step is 5mV */
#define VOLTPLAN_AVM_VOLTAGE_STEP_SIZE (5000)
/* each step is 20MHz */
#define VOLTPLAN_AVM_FREQ_STEP_SIZE    (20)

/**
 * Target Specific Defaults - Should be override-able by boot variable
 */

/* This is the adder(to V_avm)to get the initial voltage */
#define VOLTPLAN_AVM_DEFAULT_PMIC_OFFSET_uV (10 * VOLTPLAN_AVM_VOLTAGE_STEP_SIZE)
/* This is adder(to V_avm) to get the lowest */
#define VOLTPLAN_AVM_DEFAULT_VMIN_OFFSET_uV (0 * VOLTPLAN_AVM_VOLTAGE_STEP_SIZE)


#endif //VOLTPLAN_TARGET_DEFS_H
