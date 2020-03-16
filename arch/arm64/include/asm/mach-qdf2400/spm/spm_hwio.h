#ifndef _SPM_HWIO_H_
#define _SPM_HWIO_H_

/*==============================================================================
  FILE:         spm_hwio.h

  OVERVIEW:     This file contains the HWIO wrapper macros for SPM.

  DEPENDENCIES: None

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <asm/hal/HALhwio.h>
#include <asm/mach/spm/spm_hal_hwio.h>

/*===========================================================================
 *                                MACROS
 *==========================================================================*/

/**
 * @brief Default SPM prefix for SAW version 3. It can be overridden from build
 *        files.
 */
#ifndef SPM_HWIO_PREFIX
#define SPM_HWIO_PREFIX SAW3
#endif

/*
 * These macros are used to defer register name - build script can provide
 * the necessary parameters to construct actual register name.
 *
 * @Note
 * This list does not cover all HWIO macros. Only those macros used by
 * SPM HAL layer are defined here. If required, new wrapper macros can
 * be added here.
 */

#define _SPM_HWIO_CONCAT_NAME(prefix, name)                prefix##_##name
#define _SPM_HWIO_CONCAT_BMSK(prefix, reg, field)          HWIO_##prefix##_##reg##_##field##_BMSK
#define SPM_HWIO_CONCAT_NAME(prefix, name)                 _SPM_HWIO_CONCAT_NAME(prefix, name)
#define SPM_HWIO_CONCAT_BMSK(prefix, reg, field)           _SPM_HWIO_CONCAT_BMSK(prefix, reg, field)
#define SPM_HWIO_EXPAND_NAME(name)                         SPM_HWIO_CONCAT_NAME(SPM_HWIO_PREFIX, name)
#define SPM_HWIO_EXPAND_BMSK(reg, field)                   SPM_HWIO_CONCAT_BMSK(SPM_HWIO_PREFIX, reg, field)

#define SPM_HWIO_RMSK(name)                                HWIO_RMSK(SPM_HWIO_EXPAND_NAME(name))
#define SPM_HWIO_RMSKI(name, index)                        HWIO_RMSKI(SPM_HWIO_EXPAND_NAME(name), index)
#define SPM_HWIO_SHFT(name, field)                         HWIO_SHFT(SPM_HWIO_EXPAND_NAME(name), field)
#define SPM_HWIO_FMSK(name, field)                         HWIO_FMSK(SPM_HWIO_EXPAND_NAME(name), field)
#define SPM_HWIO_VAL(name, field, val)                     HWIO_VAL(SPM_HWIO_EXPAND_NAME(name), field, val)
#define SPM_HWIO_FVAL(name, field, val)                    HWIO_FVAL(SPM_HWIO_EXPAND_NAME(name), field, val)
#define SPM_HWIO_FVALV(name, field, val)                   HWIO_FVALV(SPM_HWIO_EXPAND_NAME(name), field, val)

#define SPM_HWIO_ADDRX(base, name)                         HWIO_ADDRX(base, SPM_HWIO_EXPAND_NAME(name))
#define SPM_HWIO_ADDRXI(base, name, index)                 HWIO_ADDRXI(base, SPM_HWIO_EXPAND_NAME(name), index)

#define SPM_HWIO_INX(base, name)                           HWIO_INX(base, SPM_HWIO_EXPAND_NAME(name))
#define SPM_HWIO_INXI(base, name, index)                   HWIO_INXI(base, SPM_HWIO_EXPAND_NAME(name), index)
#define SPM_HWIO_INXM(base, name, mask)                    HWIO_INXM(base, SPM_HWIO_EXPAND_NAME(name), mask)
#define SPM_HWIO_INXMI(base, name, index, mask)            HWIO_INXMI(base, SPM_HWIO_EXPAND_NAME(name), index, mask)
#define SPM_HWIO_INXF(base, name, field)                   HWIO_INXF(base, SPM_HWIO_EXPAND_NAME(name), field)
#define SPM_HWIO_INXFI(base, name, field, index)           HWIO_INXFI(base, SPM_HWIO_EXPAND_NAME(name), field, index)

#define SPM_HWIO_OUTX(base, name, val)                     HWIO_OUTX(base, SPM_HWIO_EXPAND_NAME(name), val)
#define SPM_HWIO_OUTXI(base, name, index, val)             HWIO_OUTXI(base, SPM_HWIO_EXPAND_NAME(name), index, val)
#define SPM_HWIO_OUTXM(base, name, mask, val)              HWIO_OUTXM(base, SPM_HWIO_EXPAND_NAME(name), mask, val)
#define SPM_HWIO_OUTXMI(base, name, index, mask, val)      HWIO_OUTXMI(base, SPM_HWIO_EXPAND_NAME(name), index, mask, val)
#define SPM_HWIO_OUTXF(base, name, field, val)             HWIO_OUTXF(base, SPM_HWIO_EXPAND_NAME(name), field, val)
#define SPM_HWIO_OUTXFI(base, name, index, field, val)     HWIO_OUTXFI(base, SPM_HWIO_EXPAND_NAME(name), index, field, val)

#ifdef __cplusplus
}
#endif

#endif
