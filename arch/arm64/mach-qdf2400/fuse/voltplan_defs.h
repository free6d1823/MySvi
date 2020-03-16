/**
 * @file:  voltplan_defs.h
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
#ifndef VOLTPLAN_DEFS_H
#define VOLTPLAN_DEFS_H

#define CHIPINFO_VERSION(major, minor)  (((major) << 16) | (minor))

#include <asm/hal/HALhwio.h>

//HWIO Macros
#define VOLTPLAN_HWIO_IN(a) (__inpdw(a))
#define VOLTPLAN_HWIO_IN_MASK(a, m) (__inpdw(a) & (m))

#define VOLTPLAN_CHIPINFO_VERSION CHIPINFO_VERSION
#define VOLTPLAN_CPRREV(cprrev)	cprrev

#define VOLTPLAN_FUSE_MAPPING(base_register, field) { \
    .address = HWIO_##base_register##_ADDR, \
    .offset  = HWIO_##base_register##_##field##_SHFT, \
    .mask    = HWIO_##base_register##_##field##_BMSK }

#endif //VOLTPLAN_DEFS_H
