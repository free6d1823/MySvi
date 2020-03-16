/**
 * @file:  voltage_plan_types.h
 * @brief:
 *
 * Copyright (c) 2016 by Qualcomm Technologies, Inc. All Rights Reserved. Confidential and Proprietary - Qualcomm Technologies, Inc..
 *
 * Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 */
#ifndef _VOLTAGE_PLAN_TYPES_H
#define _VOLTAGE_PLAN_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include "voltage_plan_target_defs.h"

typedef enum
{
    VOLTPLAN_FOUNDRY_TSMC,
    VOLTPLAN_FOUNDRY_GF,
    VOLTPLAN_FOUNDRY_SS,
    VOLTPLAN_FOUNDRY_IBM,
    VOLTPLAN_FOUNDRY_UMC,
    VOLTPLAN_FOUNDRY_ANY
} voltplan_foundry_id;

typedef enum
{
    VOLTPLAN_VOLTAGE_MODE_OFF,
    VOLTPLAN_VOLTAGE_MODE_RETENTION,
    VOLTPLAN_VOLTAGE_MODE_MIN_SVS,
    VOLTPLAN_VOLTAGE_MODE_LOW_SVS,
    VOLTPLAN_VOLTAGE_MODE_SVS,
    VOLTPLAN_VOLTAGE_MODE_NOMINAL,
    VOLTPLAN_VOLTAGE_MODE_TURBO,
    VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO,
    VOLTPLAN_VOLTAGE_MODE_INVALID = 0xFF,
} voltplan_voltage_mode;


typedef enum {
    VOLTPLAN_DOMAIN_TYPE_MODE_BASED,
    VOLTPLAN_DOMAIN_TYPE_FREQ_BASED
} voltplan_domain_type;

struct raw_fuse_data {
    uintptr_t address;
    uint32_t  offset;
    uint32_t  mask;
};

typedef struct
{
    uint16_t count;
    uint16_t redun_count;
    struct raw_fuse_data *data;
    struct raw_fuse_data *redun_data;
} voltplan_fuse;

typedef struct
{
    voltplan_fuse* volt;
    voltplan_fuse* quot;
    voltplan_fuse* rosel;
    voltplan_fuse* quotOffset;
    voltplan_fuse* voltOffset;
    voltplan_fuse* cpuBaseVolt;
    voltplan_fuse* cpuFreq;
    voltplan_fuse* avmVminTh;
}voltplan_fuse_data;

typedef struct
{
    voltplan_foundry_id foundry;
    uint32_t min;
    uint32_t max;
    uint8_t  cprrev;
} voltplan_version;

typedef struct
{
    voltplan_version* versions;
    uint8_t count;
} voltplan_version_range;

typedef struct
{
    uint16_t ro;
    uint32_t quotient;
} cpr_quotient;

typedef struct
{
    cpr_quotient *quots;
    uint32_t *kvs;
    uint16_t count;
} cpr_quotient_cfg;

typedef struct
{
    uint8_t cprRevMin;
    uint8_t cprRevMax;
    int32_t openLoop;
    int32_t closedLoop;
    int32_t maxFloorToCeil;
} cpr_margin_data;

typedef struct
{
    uint8_t count;
    cpr_margin_data *data;
} cpr_margin_cfg;

typedef uint32_t(*voltplan_idx_func)(voltplan_voltage_mode mode);

typedef struct
{
    uint8_t modesCount;
    voltplan_voltage_mode* supportedModes;
    voltplan_idx_func idxLookupFunc;

    struct voltplan_voltage_data* minMode; // Used for interpolation only

    struct voltplan_voltage_data
    {
        uint32_t fref;
        cpr_margin_cfg* margins;
        voltplan_fuse_data* fuses;
        uint32_t freqDelta;
        cpr_quotient_cfg* quotients;
        uint8_t subModesCount;
        struct voltplan_freq_data {
            uint32_t freq;
            uint32_t ceiling;
            uint32_t floor;
        } *subModes;
    } *modes;
    struct voltplan_freq_data *allSubModes;
    uint8_t allSubModesCount;
} voltplan_voltage_plan;

typedef struct voltplan_freq_data voltplan_freq_data;

typedef struct
{
    voltplan_domain_id rail;
    struct voltage_plan_list {
        voltplan_version version;
        voltplan_voltage_plan* cfg;
    } *list;
    uint8_t count;
} voltplan_versioned_voltage_plan;

voltplan_versioned_voltage_plan* voltplan_get_versioned_voltage_plan(voltplan_domain_id railId);

#endif
