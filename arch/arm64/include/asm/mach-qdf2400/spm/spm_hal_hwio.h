#ifndef __SPM_HAL_HWIO_H__
#define __SPM_HAL_HWIO_H__
/*
===========================================================================
*/
/**
  @file spm_hal_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r59.0]

  This file contains HWIO register definitions for the following modules:
    APCS_APR0_SAW4_2_0_AVS
    APCS_APR0_SAW4_2_0_SPM
    APCS_APR0_SAW4_2_0_STS

  'Include' filters applied:
  'Exclude' filters applied: RESERVED DUMMY
*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * Offsets from the SPM base to the AVS and STS bases (manual additions)
 *--------------------------------------------------------------------------*/
#define SAW4_AVS_REG_BASE_OFFS                                          0x240000
#define SAW4_STS_REG_BASE_OFFS                                          0x2c0000

/*----------------------------------------------------------------------------
 * MODULE: SAW4_2_0_AVS
 *--------------------------------------------------------------------------*/

#define SAW4_2_0_AVS_REG_BASE                                           (HMSS_PERIPH_BASE      + 0x00246000)
#define SAW4_2_0_AVS_REG_BASE_OFFS                                      0x00246000

#define HWIO_SAW4_VCTL_ADDR(x)                                          ((x) + 0x00000100)
#define HWIO_SAW4_VCTL_OFFS                                             (0x00000100)
#define HWIO_SAW4_VCTL_RMSK                                               0x1700ff
#define HWIO_SAW4_VCTL_IN(x)      \
        in_dword_masked(HWIO_SAW4_VCTL_ADDR(x), HWIO_SAW4_VCTL_RMSK)
#define HWIO_SAW4_VCTL_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_VCTL_ADDR(x), m)
#define HWIO_SAW4_VCTL_OUT(x, v)      \
        out_dword(HWIO_SAW4_VCTL_ADDR(x),v)
#define HWIO_SAW4_VCTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_VCTL_ADDR(x),m,v,HWIO_SAW4_VCTL_IN(x))
#define HWIO_SAW4_VCTL_SIZE_BMSK                                          0x100000
#define HWIO_SAW4_VCTL_SIZE_SHFT                                              0x14
#define HWIO_SAW4_VCTL_ADR_IDX_BMSK                                        0x70000
#define HWIO_SAW4_VCTL_ADR_IDX_SHFT                                           0x10
#define HWIO_SAW4_VCTL_PMIC_DATA_BMSK                                         0xff
#define HWIO_SAW4_VCTL_PMIC_DATA_SHFT                                          0x0

#define HWIO_SAW4_AVS_CTL_ADDR(x)                                       ((x) + 0x00000104)
#define HWIO_SAW4_AVS_CTL_OFFS                                          (0x00000104)
#define HWIO_SAW4_AVS_CTL_RMSK                                          0xffffdf7f
#define HWIO_SAW4_AVS_CTL_IN(x)      \
        in_dword_masked(HWIO_SAW4_AVS_CTL_ADDR(x), HWIO_SAW4_AVS_CTL_RMSK)
#define HWIO_SAW4_AVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_AVS_CTL_ADDR(x), m)
#define HWIO_SAW4_AVS_CTL_OUT(x, v)      \
        out_dword(HWIO_SAW4_AVS_CTL_ADDR(x),v)
#define HWIO_SAW4_AVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_AVS_CTL_ADDR(x),m,v,HWIO_SAW4_AVS_CTL_IN(x))
#define HWIO_SAW4_AVS_CTL_VLVL_STEP_DN_BMSK                             0xff000000
#define HWIO_SAW4_AVS_CTL_VLVL_STEP_DN_SHFT                                   0x18
#define HWIO_SAW4_AVS_CTL_VLVL_STEP_UP_BMSK                               0xff0000
#define HWIO_SAW4_AVS_CTL_VLVL_STEP_UP_SHFT                                   0x10
#define HWIO_SAW4_AVS_CTL_CPR_RAMP_EN_BMSK                                  0x8000
#define HWIO_SAW4_AVS_CTL_CPR_RAMP_EN_SHFT                                     0xf
#define HWIO_SAW4_AVS_CTL_VCTL_RAMP_EN_BMSK                                 0x4000
#define HWIO_SAW4_AVS_CTL_VCTL_RAMP_EN_SHFT                                    0xe
#define HWIO_SAW4_AVS_CTL_TMR_CLK_DIV_BMSK                                  0x1f00
#define HWIO_SAW4_AVS_CTL_TMR_CLK_DIV_SHFT                                     0x8
#define HWIO_SAW4_AVS_CTL_ILCPR_BMSK                                          0x40
#define HWIO_SAW4_AVS_CTL_ILCPR_SHFT                                           0x6
#define HWIO_SAW4_AVS_CTL_VLVL_WIDTH_BMSK                                     0x20
#define HWIO_SAW4_AVS_CTL_VLVL_WIDTH_SHFT                                      0x5
#define HWIO_SAW4_AVS_CTL_CTL_SEL_BMSK                                        0x10
#define HWIO_SAW4_AVS_CTL_CTL_SEL_SHFT                                         0x4
#define HWIO_SAW4_AVS_CTL_SW_DONE_INT_EN_BMSK                                  0x8
#define HWIO_SAW4_AVS_CTL_SW_DONE_INT_EN_SHFT                                  0x3
#define HWIO_SAW4_AVS_CTL_MAX_INT_EN_BMSK                                      0x4
#define HWIO_SAW4_AVS_CTL_MAX_INT_EN_SHFT                                      0x2
#define HWIO_SAW4_AVS_CTL_MIN_INT_EN_BMSK                                      0x2
#define HWIO_SAW4_AVS_CTL_MIN_INT_EN_SHFT                                      0x1
#define HWIO_SAW4_AVS_CTL_EN_BMSK                                              0x1
#define HWIO_SAW4_AVS_CTL_EN_SHFT                                              0x0

#define HWIO_SAW4_AVS_LIMIT_ADDR(x)                                     ((x) + 0x00000108)
#define HWIO_SAW4_AVS_LIMIT_OFFS                                        (0x00000108)
#define HWIO_SAW4_AVS_LIMIT_RMSK                                          0xff00ff
#define HWIO_SAW4_AVS_LIMIT_IN(x)      \
        in_dword_masked(HWIO_SAW4_AVS_LIMIT_ADDR(x), HWIO_SAW4_AVS_LIMIT_RMSK)
#define HWIO_SAW4_AVS_LIMIT_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_AVS_LIMIT_ADDR(x), m)
#define HWIO_SAW4_AVS_LIMIT_OUT(x, v)      \
        out_dword(HWIO_SAW4_AVS_LIMIT_ADDR(x),v)
#define HWIO_SAW4_AVS_LIMIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_AVS_LIMIT_ADDR(x),m,v,HWIO_SAW4_AVS_LIMIT_IN(x))
#define HWIO_SAW4_AVS_LIMIT_MAX_VLVL_BMSK                                 0xff0000
#define HWIO_SAW4_AVS_LIMIT_MAX_VLVL_SHFT                                     0x10
#define HWIO_SAW4_AVS_LIMIT_MIN_VLVL_BMSK                                     0xff
#define HWIO_SAW4_AVS_LIMIT_MIN_VLVL_SHFT                                      0x0

#define HWIO_SAW4_AVS_DLY_ADDR(x)                                       ((x) + 0x0000010c)
#define HWIO_SAW4_AVS_DLY_OFFS                                          (0x0000010c)
#define HWIO_SAW4_AVS_DLY_RMSK                                               0x3ff
#define HWIO_SAW4_AVS_DLY_IN(x)      \
        in_dword_masked(HWIO_SAW4_AVS_DLY_ADDR(x), HWIO_SAW4_AVS_DLY_RMSK)
#define HWIO_SAW4_AVS_DLY_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_AVS_DLY_ADDR(x), m)
#define HWIO_SAW4_AVS_DLY_OUT(x, v)      \
        out_dword(HWIO_SAW4_AVS_DLY_ADDR(x),v)
#define HWIO_SAW4_AVS_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_AVS_DLY_ADDR(x),m,v,HWIO_SAW4_AVS_DLY_IN(x))
#define HWIO_SAW4_AVS_DLY_AVS_DELAY_BMSK                                     0x3ff
#define HWIO_SAW4_AVS_DLY_AVS_DELAY_SHFT                                       0x0

#define HWIO_SAW4_VCTL_DLY_ADDR(x)                                      ((x) + 0x00000110)
#define HWIO_SAW4_VCTL_DLY_OFFS                                         (0x00000110)
#define HWIO_SAW4_VCTL_DLY_RMSK                                              0x3ff
#define HWIO_SAW4_VCTL_DLY_IN(x)      \
        in_dword_masked(HWIO_SAW4_VCTL_DLY_ADDR(x), HWIO_SAW4_VCTL_DLY_RMSK)
#define HWIO_SAW4_VCTL_DLY_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_VCTL_DLY_ADDR(x), m)
#define HWIO_SAW4_VCTL_DLY_OUT(x, v)      \
        out_dword(HWIO_SAW4_VCTL_DLY_ADDR(x),v)
#define HWIO_SAW4_VCTL_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_VCTL_DLY_ADDR(x),m,v,HWIO_SAW4_VCTL_DLY_IN(x))
#define HWIO_SAW4_VCTL_DLY_VCTL_DELAY_BMSK                                   0x3ff
#define HWIO_SAW4_VCTL_DLY_VCTL_DELAY_SHFT                                     0x0

#define HWIO_SAW4_AVS_CLR_STS_ADDR(x)                                   ((x) + 0x00000114)
#define HWIO_SAW4_AVS_CLR_STS_OFFS                                      (0x00000114)
#define HWIO_SAW4_AVS_CLR_STS_RMSK                                             0x1
#define HWIO_SAW4_AVS_CLR_STS_OUT(x, v)      \
        out_dword(HWIO_SAW4_AVS_CLR_STS_ADDR(x),v)
#define HWIO_SAW4_AVS_CLR_STS_CLR_CMD_BMSK                                     0x1
#define HWIO_SAW4_AVS_CLR_STS_CLR_CMD_SHFT                                     0x0

#define HWIO_SAW4_CVS_CTL_ADDR(x)                                       ((x) + 0x00000120)
#define HWIO_SAW4_CVS_CTL_OFFS                                          (0x00000120)
#define HWIO_SAW4_CVS_CTL_RMSK                                            0x7e1ff9
#define HWIO_SAW4_CVS_CTL_IN(x)      \
        in_dword_masked(HWIO_SAW4_CVS_CTL_ADDR(x), HWIO_SAW4_CVS_CTL_RMSK)
#define HWIO_SAW4_CVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_CVS_CTL_ADDR(x), m)
#define HWIO_SAW4_CVS_CTL_OUT(x, v)      \
        out_dword(HWIO_SAW4_CVS_CTL_ADDR(x),v)
#define HWIO_SAW4_CVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_CVS_CTL_ADDR(x),m,v,HWIO_SAW4_CVS_CTL_IN(x))
#define HWIO_SAW4_CVS_CTL_SEQ_IDX_BMSK                                    0x700000
#define HWIO_SAW4_CVS_CTL_SEQ_IDX_SHFT                                        0x14
#define HWIO_SAW4_CVS_CTL_REQ_BMSK                                         0x80000
#define HWIO_SAW4_CVS_CTL_REQ_SHFT                                            0x13
#define HWIO_SAW4_CVS_CTL_HALT_DONE_BMSK                                   0x40000
#define HWIO_SAW4_CVS_CTL_HALT_DONE_SHFT                                      0x12
#define HWIO_SAW4_CVS_CTL_CTL_SEL_BMSK                                     0x20000
#define HWIO_SAW4_CVS_CTL_CTL_SEL_SHFT                                        0x11
#define HWIO_SAW4_CVS_CTL_CVS_START_ADR_BMSK                                0x1ff0
#define HWIO_SAW4_CVS_CTL_CVS_START_ADR_SHFT                                   0x4
#define HWIO_SAW4_CVS_CTL_ISAR_BMSK                                            0x8
#define HWIO_SAW4_CVS_CTL_ISAR_SHFT                                            0x3
#define HWIO_SAW4_CVS_CTL_CVS_EN_BMSK                                          0x1
#define HWIO_SAW4_CVS_CTL_CVS_EN_SHFT                                          0x0

#define HWIO_SAW4_CVS_DLY_ADDR(x)                                       ((x) + 0x00000124)
#define HWIO_SAW4_CVS_DLY_OFFS                                          (0x00000124)
#define HWIO_SAW4_CVS_DLY_RMSK                                          0x3fffffff
#define HWIO_SAW4_CVS_DLY_IN(x)      \
        in_dword_masked(HWIO_SAW4_CVS_DLY_ADDR(x), HWIO_SAW4_CVS_DLY_RMSK)
#define HWIO_SAW4_CVS_DLY_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_CVS_DLY_ADDR(x), m)
#define HWIO_SAW4_CVS_DLY_OUT(x, v)      \
        out_dword(HWIO_SAW4_CVS_DLY_ADDR(x),v)
#define HWIO_SAW4_CVS_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_CVS_DLY_ADDR(x),m,v,HWIO_SAW4_CVS_DLY_IN(x))
#define HWIO_SAW4_CVS_DLY_DLY3_BMSK                                     0x3ff00000
#define HWIO_SAW4_CVS_DLY_DLY3_SHFT                                           0x14
#define HWIO_SAW4_CVS_DLY_DLY2_BMSK                                        0xffc00
#define HWIO_SAW4_CVS_DLY_DLY2_SHFT                                            0xa
#define HWIO_SAW4_CVS_DLY_DLY1_BMSK                                          0x3ff
#define HWIO_SAW4_CVS_DLY_DLY1_SHFT                                            0x0

#define HWIO_SAW4_CVS_PMIC_DATA_n_ADDR(base,n)                          ((base) + 0x00000140 + 0x4 * (n))
#define HWIO_SAW4_CVS_PMIC_DATA_n_OFFS(base,n)                          (0x00000140 + 0x4 * (n))
#define HWIO_SAW4_CVS_PMIC_DATA_n_RMSK                                  0x801700ff
#define HWIO_SAW4_CVS_PMIC_DATA_n_MAXn                                           3
#define HWIO_SAW4_CVS_PMIC_DATA_n_INI(base,n)        \
        in_dword_masked(HWIO_SAW4_CVS_PMIC_DATA_n_ADDR(base,n), HWIO_SAW4_CVS_PMIC_DATA_n_RMSK)
#define HWIO_SAW4_CVS_PMIC_DATA_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_SAW4_CVS_PMIC_DATA_n_ADDR(base,n), mask)
#define HWIO_SAW4_CVS_PMIC_DATA_n_OUTI(base,n,val)    \
        out_dword(HWIO_SAW4_CVS_PMIC_DATA_n_ADDR(base,n),val)
#define HWIO_SAW4_CVS_PMIC_DATA_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_SAW4_CVS_PMIC_DATA_n_ADDR(base,n),mask,val,HWIO_SAW4_CVS_PMIC_DATA_n_INI(base,n))
#define HWIO_SAW4_CVS_PMIC_DATA_n_PMIC_CMD_MASK_BMSK                    0x80000000
#define HWIO_SAW4_CVS_PMIC_DATA_n_PMIC_CMD_MASK_SHFT                          0x1f
#define HWIO_SAW4_CVS_PMIC_DATA_n_SIZE_BMSK                               0x100000
#define HWIO_SAW4_CVS_PMIC_DATA_n_SIZE_SHFT                                   0x14
#define HWIO_SAW4_CVS_PMIC_DATA_n_ADR_IDX_BMSK                             0x70000
#define HWIO_SAW4_CVS_PMIC_DATA_n_ADR_IDX_SHFT                                0x10
#define HWIO_SAW4_CVS_PMIC_DATA_n_DATA_BMSK                                   0xff
#define HWIO_SAW4_CVS_PMIC_DATA_n_DATA_SHFT                                    0x0

#define HWIO_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n)                          ((base) + 0x00000200 + 0x4 * (n))
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_OFFS(base,n)                          (0x00000200 + 0x4 * (n))
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_RMSK                                  0xffffffff
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_MAXn                                          31
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_INI(base,n)        \
        in_dword_masked(HWIO_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n), HWIO_SAW4_CVS_SEQ_ENTRY_n_RMSK)
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n), mask)
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_OUTI(base,n,val)    \
        out_dword(HWIO_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n),val)
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n),mask,val,HWIO_SAW4_CVS_SEQ_ENTRY_n_INI(base,n))
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_CMD3_BMSK                             0xff000000
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_CMD3_SHFT                                   0x18
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_CMD2_BMSK                               0xff0000
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_CMD2_SHFT                                   0x10
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_CMD1_BMSK                                 0xff00
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_CMD1_SHFT                                    0x8
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_CMD0_BMSK                                   0xff
#define HWIO_SAW4_CVS_SEQ_ENTRY_n_CMD0_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: SAW4_2_0_SPM
 *--------------------------------------------------------------------------*/

#define SAW4_2_0_SPM_REG_BASE                                      (HMSS_PERIPH_BASE      + 0x00006000)
#define SAW4_2_0_SPM_REG_BASE_OFFS                                 0x00006000

#define HWIO_SAW4_SPM_CTL_ADDR(x)                                  ((x) + 0x00000000)
#define HWIO_SAW4_SPM_CTL_OFFS                                     (0x00000000)
#define HWIO_SAW4_SPM_CTL_RMSK                                     0xff7e1fff
#define HWIO_SAW4_SPM_CTL_IN(x)      \
        in_dword_masked(HWIO_SAW4_SPM_CTL_ADDR(x), HWIO_SAW4_SPM_CTL_RMSK)
#define HWIO_SAW4_SPM_CTL_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_SPM_CTL_ADDR(x), m)
#define HWIO_SAW4_SPM_CTL_OUT(x, v)      \
        out_dword(HWIO_SAW4_SPM_CTL_ADDR(x),v)
#define HWIO_SAW4_SPM_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_SPM_CTL_ADDR(x),m,v,HWIO_SAW4_SPM_CTL_IN(x))
#define HWIO_SAW4_SPM_CTL_EVENT_SYNC_BMSK                          0xff000000
#define HWIO_SAW4_SPM_CTL_EVENT_SYNC_SHFT                                0x18
#define HWIO_SAW4_SPM_CTL_PWR_STATE_IDX_BMSK                         0x700000
#define HWIO_SAW4_SPM_CTL_PWR_STATE_IDX_SHFT                             0x14
#define HWIO_SAW4_SPM_CTL_SLEEP_REQ_BMSK                              0x80000
#define HWIO_SAW4_SPM_CTL_SLEEP_REQ_SHFT                                 0x13
#define HWIO_SAW4_SPM_CTL_WAKEUP_REQ_BMSK                             0x40000
#define HWIO_SAW4_SPM_CTL_WAKEUP_REQ_SHFT                                0x12
#define HWIO_SAW4_SPM_CTL_SLP_CMD_MODE_BMSK                           0x20000
#define HWIO_SAW4_SPM_CTL_SLP_CMD_MODE_SHFT                              0x11
#define HWIO_SAW4_SPM_CTL_SPM_START_ADR_BMSK                           0x1ff0
#define HWIO_SAW4_SPM_CTL_SPM_START_ADR_SHFT                              0x4
#define HWIO_SAW4_SPM_CTL_ISAR_BMSK                                       0x8
#define HWIO_SAW4_SPM_CTL_ISAR_SHFT                                       0x3
#define HWIO_SAW4_SPM_CTL_WAKEUP_CONFIG_BMSK                              0x6
#define HWIO_SAW4_SPM_CTL_WAKEUP_CONFIG_SHFT                              0x1
#define HWIO_SAW4_SPM_CTL_SPM_EN_BMSK                                     0x1
#define HWIO_SAW4_SPM_CTL_SPM_EN_SHFT                                     0x0

#define HWIO_SAW4_SPM_DLY_ADDR(x)                                  ((x) + 0x00000004)
#define HWIO_SAW4_SPM_DLY_OFFS                                     (0x00000004)
#define HWIO_SAW4_SPM_DLY_RMSK                                     0x3fffffff
#define HWIO_SAW4_SPM_DLY_IN(x)      \
        in_dword_masked(HWIO_SAW4_SPM_DLY_ADDR(x), HWIO_SAW4_SPM_DLY_RMSK)
#define HWIO_SAW4_SPM_DLY_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_SPM_DLY_ADDR(x), m)
#define HWIO_SAW4_SPM_DLY_OUT(x, v)      \
        out_dword(HWIO_SAW4_SPM_DLY_ADDR(x),v)
#define HWIO_SAW4_SPM_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_SPM_DLY_ADDR(x),m,v,HWIO_SAW4_SPM_DLY_IN(x))
#define HWIO_SAW4_SPM_DLY_DLY3_BMSK                                0x3ff00000
#define HWIO_SAW4_SPM_DLY_DLY3_SHFT                                      0x14
#define HWIO_SAW4_SPM_DLY_DLY2_BMSK                                   0xffc00
#define HWIO_SAW4_SPM_DLY_DLY2_SHFT                                       0xa
#define HWIO_SAW4_SPM_DLY_DLY1_BMSK                                     0x3ff
#define HWIO_SAW4_SPM_DLY_DLY1_SHFT                                       0x0

#define HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(x)                           ((x) + 0x00000008)
#define HWIO_SAW4_SPM_WAKEUP_CNT_OFFS                              (0x00000008)
#define HWIO_SAW4_SPM_WAKEUP_CNT_RMSK                              0xffffffff
#define HWIO_SAW4_SPM_WAKEUP_CNT_IN(x)      \
        in_dword_masked(HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(x), HWIO_SAW4_SPM_WAKEUP_CNT_RMSK)
#define HWIO_SAW4_SPM_WAKEUP_CNT_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(x), m)
#define HWIO_SAW4_SPM_WAKEUP_CNT_OUT(x, v)      \
        out_dword(HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(x),v)
#define HWIO_SAW4_SPM_WAKEUP_CNT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(x),m,v,HWIO_SAW4_SPM_WAKEUP_CNT_IN(x))
#define HWIO_SAW4_SPM_WAKEUP_CNT_CNT_BMSK                          0xffffffff
#define HWIO_SAW4_SPM_WAKEUP_CNT_CNT_SHFT                                 0x0

#define HWIO_SAW4_CFG_ADDR(x)                                      ((x) + 0x0000000c)
#define HWIO_SAW4_CFG_OFFS                                         (0x0000000c)
#define HWIO_SAW4_CFG_RMSK                                              0xf1f
#define HWIO_SAW4_CFG_IN(x)      \
        in_dword_masked(HWIO_SAW4_CFG_ADDR(x), HWIO_SAW4_CFG_RMSK)
#define HWIO_SAW4_CFG_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_CFG_ADDR(x), m)
#define HWIO_SAW4_CFG_OUT(x, v)      \
        out_dword(HWIO_SAW4_CFG_ADDR(x),v)
#define HWIO_SAW4_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_CFG_ADDR(x),m,v,HWIO_SAW4_CFG_IN(x))
#define HWIO_SAW4_CFG_TEST_BUS_SEL_BMSK                                 0xe00
#define HWIO_SAW4_CFG_TEST_BUS_SEL_SHFT                                   0x9
#define HWIO_SAW4_CFG_FRC_REF_CLK_ON_BMSK                               0x100
#define HWIO_SAW4_CFG_FRC_REF_CLK_ON_SHFT                                 0x8
#define HWIO_SAW4_CFG_CLK_DIV_BMSK                                       0x1f
#define HWIO_SAW4_CFG_CLK_DIV_SHFT                                        0x0

#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(base,n)                 ((base) + 0x00000400 + 0x4 * (n))
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_OFFS(base,n)                 (0x00000400 + 0x4 * (n))
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_RMSK                         0xffffffff
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_MAXn                                 15
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_INI(base,n)        \
        in_dword_masked(HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(base,n), HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(base,n), mask)
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_OUTI(base,n,val)    \
        out_dword(HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(base,n),val)
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(base,n),mask,val,HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_INI(base,n))
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK                    0xff000000
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                          0x18
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK                      0xff0000
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                          0x10
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK                        0xff00
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                           0x8
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                          0xff
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                           0x0

#define HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(base,n)                     ((base) + 0x00000040 + 0x4 * (n))
#define HWIO_SAW4_SPM_PMIC_DATA_n_OFFS(base,n)                     (0x00000040 + 0x4 * (n))
#define HWIO_SAW4_SPM_PMIC_DATA_n_RMSK                              0x71700ff
#define HWIO_SAW4_SPM_PMIC_DATA_n_MAXn                                      5
#define HWIO_SAW4_SPM_PMIC_DATA_n_INI(base,n)        \
        in_dword_masked(HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(base,n), HWIO_SAW4_SPM_PMIC_DATA_n_RMSK)
#define HWIO_SAW4_SPM_PMIC_DATA_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(base,n), mask)
#define HWIO_SAW4_SPM_PMIC_DATA_n_OUTI(base,n,val)    \
        out_dword(HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(base,n),val)
#define HWIO_SAW4_SPM_PMIC_DATA_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(base,n),mask,val,HWIO_SAW4_SPM_PMIC_DATA_n_INI(base,n))
#define HWIO_SAW4_SPM_PMIC_DATA_n_DLY_BMSK                          0x7000000
#define HWIO_SAW4_SPM_PMIC_DATA_n_DLY_SHFT                               0x18
#define HWIO_SAW4_SPM_PMIC_DATA_n_SIZE_BMSK                          0x100000
#define HWIO_SAW4_SPM_PMIC_DATA_n_SIZE_SHFT                              0x14
#define HWIO_SAW4_SPM_PMIC_DATA_n_ADR_IDX_BMSK                        0x70000
#define HWIO_SAW4_SPM_PMIC_DATA_n_ADR_IDX_SHFT                           0x10
#define HWIO_SAW4_SPM_PMIC_DATA_n_DATA_BMSK                              0xff
#define HWIO_SAW4_SPM_PMIC_DATA_n_DATA_SHFT                               0x0

/*----------------------------------------------------------------------------
 * MODULE: SAW4_2_0_STS
 *--------------------------------------------------------------------------*/

#define SAW4_2_0_STS_REG_BASE                                         (HMSS_PERIPH_BASE      + 0x002c6000)
#define SAW4_2_0_STS_REG_BASE_OFFS                                    0x002c6000

#define HWIO_SAW4_SECURE_ADDR(x)                                      ((x) + 0x00000000)
#define HWIO_SAW4_SECURE_OFFS                                         (0x00000000)
#define HWIO_SAW4_SECURE_RMSK                                                0x7
#define HWIO_SAW4_SECURE_IN(x)      \
        in_dword_masked(HWIO_SAW4_SECURE_ADDR(x), HWIO_SAW4_SECURE_RMSK)
#define HWIO_SAW4_SECURE_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_SECURE_ADDR(x), m)
#define HWIO_SAW4_SECURE_OUT(x, v)      \
        out_dword(HWIO_SAW4_SECURE_ADDR(x),v)
#define HWIO_SAW4_SECURE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_SECURE_ADDR(x),m,v,HWIO_SAW4_SECURE_IN(x))
#define HWIO_SAW4_SECURE_SAW_CTL_BMSK                                        0x4
#define HWIO_SAW4_SECURE_SAW_CTL_SHFT                                        0x2
#define HWIO_SAW4_SECURE_PWR_CTL_BMSK                                        0x2
#define HWIO_SAW4_SECURE_PWR_CTL_SHFT                                        0x1
#define HWIO_SAW4_SECURE_VLT_CTL_BMSK                                        0x1
#define HWIO_SAW4_SECURE_VLT_CTL_SHFT                                        0x0

#define HWIO_SAW4_ID_ADDR(x)                                          ((x) + 0x00000004)
#define HWIO_SAW4_ID_OFFS                                             (0x00000004)
#define HWIO_SAW4_ID_RMSK                                             0xff3f1f7f
#define HWIO_SAW4_ID_IN(x)      \
        in_dword_masked(HWIO_SAW4_ID_ADDR(x), HWIO_SAW4_ID_RMSK)
#define HWIO_SAW4_ID_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_ID_ADDR(x), m)
#define HWIO_SAW4_ID_NUM_SPM_ENTRY_BMSK                               0xff000000
#define HWIO_SAW4_ID_NUM_SPM_ENTRY_SHFT                                     0x18
#define HWIO_SAW4_ID_NUM_PWR_CTL_BMSK                                   0x3f0000
#define HWIO_SAW4_ID_NUM_PWR_CTL_SHFT                                       0x10
#define HWIO_SAW4_ID_NUM_CVS_PMIC_DATA_BMSK                               0x1c00
#define HWIO_SAW4_ID_NUM_CVS_PMIC_DATA_SHFT                                  0xa
#define HWIO_SAW4_ID_CVS_PRESENT_BMSK                                      0x200
#define HWIO_SAW4_ID_CVS_PRESENT_SHFT                                        0x9
#define HWIO_SAW4_ID_PMIC_DATA_WIDTH_BMSK                                  0x100
#define HWIO_SAW4_ID_PMIC_DATA_WIDTH_SHFT                                    0x8
#define HWIO_SAW4_ID_NUM_SPM_PMIC_DATA_BMSK                                 0x70
#define HWIO_SAW4_ID_NUM_SPM_PMIC_DATA_SHFT                                  0x4
#define HWIO_SAW4_ID_CFG_NS_ACCESS_BMSK                                      0x8
#define HWIO_SAW4_ID_CFG_NS_ACCESS_SHFT                                      0x3
#define HWIO_SAW4_ID_PMIC_ARB_INTF_BMSK                                      0x4
#define HWIO_SAW4_ID_PMIC_ARB_INTF_SHFT                                      0x2
#define HWIO_SAW4_ID_AVS_PRESENT_BMSK                                        0x2
#define HWIO_SAW4_ID_AVS_PRESENT_SHFT                                        0x1
#define HWIO_SAW4_ID_SPM_PRESENT_BMSK                                        0x1
#define HWIO_SAW4_ID_SPM_PRESENT_SHFT                                        0x0

#define HWIO_SAW4_SPM_STS_ADDR(x)                                     ((x) + 0x0000000c)
#define HWIO_SAW4_SPM_STS_OFFS                                        (0x0000000c)
#define HWIO_SAW4_SPM_STS_RMSK                                        0xffffffff
#define HWIO_SAW4_SPM_STS_IN(x)      \
        in_dword_masked(HWIO_SAW4_SPM_STS_ADDR(x), HWIO_SAW4_SPM_STS_RMSK)
#define HWIO_SAW4_SPM_STS_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_SPM_STS_ADDR(x), m)
#define HWIO_SAW4_SPM_STS_SPM_EVENT_BMSK                              0xffff0000
#define HWIO_SAW4_SPM_STS_SPM_EVENT_SHFT                                    0x10
#define HWIO_SAW4_SPM_STS_SHTDWN_REQ_BMSK                                 0x8000
#define HWIO_SAW4_SPM_STS_SHTDWN_REQ_SHFT                                    0xf
#define HWIO_SAW4_SPM_STS_SHTDWN_ACK_BMSK                                 0x4000
#define HWIO_SAW4_SPM_STS_SHTDWN_ACK_SHFT                                    0xe
#define HWIO_SAW4_SPM_STS_BRNGUP_REQ_BMSK                                 0x2000
#define HWIO_SAW4_SPM_STS_BRNGUP_REQ_SHFT                                    0xd
#define HWIO_SAW4_SPM_STS_BRNGUP_ACK_BMSK                                 0x1000
#define HWIO_SAW4_SPM_STS_BRNGUP_ACK_SHFT                                    0xc
#define HWIO_SAW4_SPM_STS_RPM_STATE_BMSK                                   0xc00
#define HWIO_SAW4_SPM_STS_RPM_STATE_SHFT                                     0xa
#define HWIO_SAW4_SPM_STS_SPM_BUSY_BMSK                                    0x200
#define HWIO_SAW4_SPM_STS_SPM_BUSY_SHFT                                      0x9
#define HWIO_SAW4_SPM_STS_SPM_CMD_ADDR_BMSK                                0x1ff
#define HWIO_SAW4_SPM_STS_SPM_CMD_ADDR_SHFT                                  0x0

#define HWIO_SAW4_SPM_STS2_ADDR(x)                                    ((x) + 0x00000010)
#define HWIO_SAW4_SPM_STS2_OFFS                                       (0x00000010)
#define HWIO_SAW4_SPM_STS2_RMSK                                         0xffffff
#define HWIO_SAW4_SPM_STS2_IN(x)      \
        in_dword_masked(HWIO_SAW4_SPM_STS2_ADDR(x), HWIO_SAW4_SPM_STS2_RMSK)
#define HWIO_SAW4_SPM_STS2_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_SPM_STS2_ADDR(x), m)
#define HWIO_SAW4_SPM_STS2_CURR_PWR_CTL_BMSK                            0xffffff
#define HWIO_SAW4_SPM_STS2_CURR_PWR_CTL_SHFT                                 0x0

#define HWIO_SAW4_AVS_STS_ADDR(x)                                     ((x) + 0x00000014)
#define HWIO_SAW4_AVS_STS_OFFS                                        (0x00000014)
#define HWIO_SAW4_AVS_STS_RMSK                                        0x3ff7ffff
#define HWIO_SAW4_AVS_STS_IN(x)      \
        in_dword_masked(HWIO_SAW4_AVS_STS_ADDR(x), HWIO_SAW4_AVS_STS_RMSK)
#define HWIO_SAW4_AVS_STS_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_AVS_STS_ADDR(x), m)
#define HWIO_SAW4_AVS_STS_AVS_CURR_DLY_BMSK                           0x3ff00000
#define HWIO_SAW4_AVS_STS_AVS_CURR_DLY_SHFT                                 0x14
#define HWIO_SAW4_AVS_STS_AVS_FLOOR_REQ_BMSK                             0x40000
#define HWIO_SAW4_AVS_STS_AVS_FLOOR_REQ_SHFT                                0x12
#define HWIO_SAW4_AVS_STS_AVS_LDCEIL_REQ_BMSK                            0x20000
#define HWIO_SAW4_AVS_STS_AVS_LDCEIL_REQ_SHFT                               0x11
#define HWIO_SAW4_AVS_STS_AVS_LD_REQ_BMSK                                0x10000
#define HWIO_SAW4_AVS_STS_AVS_LD_REQ_SHFT                                   0x10
#define HWIO_SAW4_AVS_STS_MAX_ERR_STKY_BMSK                               0x8000
#define HWIO_SAW4_AVS_STS_MAX_ERR_STKY_SHFT                                  0xf
#define HWIO_SAW4_AVS_STS_MIN_ERR_STKY_BMSK                               0x4000
#define HWIO_SAW4_AVS_STS_MIN_ERR_STKY_SHFT                                  0xe
#define HWIO_SAW4_AVS_STS_MAX_LMT_STKY_BMSK                               0x2000
#define HWIO_SAW4_AVS_STS_MAX_LMT_STKY_SHFT                                  0xd
#define HWIO_SAW4_AVS_STS_MIN_LMT_STKY_BMSK                               0x1000
#define HWIO_SAW4_AVS_STS_MIN_LMT_STKY_SHFT                                  0xc
#define HWIO_SAW4_AVS_STS_SIC_SW_DONE_IRQ_BMSK                             0x800
#define HWIO_SAW4_AVS_STS_SIC_SW_DONE_IRQ_SHFT                               0xb
#define HWIO_SAW4_AVS_STS_SIC_IRQ_BMSK                                     0x400
#define HWIO_SAW4_AVS_STS_SIC_IRQ_SHFT                                       0xa
#define HWIO_SAW4_AVS_STS_AVS_ERR_BMSK                                     0x200
#define HWIO_SAW4_AVS_STS_AVS_ERR_SHFT                                       0x9
#define HWIO_SAW4_AVS_STS_AVS_ACK_BMSK                                     0x100
#define HWIO_SAW4_AVS_STS_AVS_ACK_SHFT                                       0x8
#define HWIO_SAW4_AVS_STS_VOLTAGE_RAMP_BMSK                                 0x80
#define HWIO_SAW4_AVS_STS_VOLTAGE_RAMP_SHFT                                  0x7
#define HWIO_SAW4_AVS_STS_SW_WR_PEND_BMSK                                   0x40
#define HWIO_SAW4_AVS_STS_SW_WR_PEND_SHFT                                    0x6
#define HWIO_SAW4_AVS_STS_MAX_INT_BMSK                                      0x20
#define HWIO_SAW4_AVS_STS_MAX_INT_SHFT                                       0x5
#define HWIO_SAW4_AVS_STS_MIN_INT_BMSK                                      0x10
#define HWIO_SAW4_AVS_STS_MIN_INT_SHFT                                       0x4
#define HWIO_SAW4_AVS_STS_AVS_UP_REQ_BMSK                                    0x8
#define HWIO_SAW4_AVS_STS_AVS_UP_REQ_SHFT                                    0x3
#define HWIO_SAW4_AVS_STS_AVS_DN_REQ_BMSK                                    0x4
#define HWIO_SAW4_AVS_STS_AVS_DN_REQ_SHFT                                    0x2
#define HWIO_SAW4_AVS_STS_AVS_FSM_STATE_BMSK                                 0x3
#define HWIO_SAW4_AVS_STS_AVS_FSM_STATE_SHFT                                 0x0

#define HWIO_SAW4_PMIC_STS_ADDR(x)                                    ((x) + 0x00000018)
#define HWIO_SAW4_PMIC_STS_OFFS                                       (0x00000018)
#define HWIO_SAW4_PMIC_STS_RMSK                                         0xff00ff
#define HWIO_SAW4_PMIC_STS_IN(x)      \
        in_dword_masked(HWIO_SAW4_PMIC_STS_ADDR(x), HWIO_SAW4_PMIC_STS_RMSK)
#define HWIO_SAW4_PMIC_STS_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_PMIC_STS_ADDR(x), m)
#define HWIO_SAW4_PMIC_STS_PMIC_DONE_BMSK                               0x800000
#define HWIO_SAW4_PMIC_STS_PMIC_DONE_SHFT                                   0x17
#define HWIO_SAW4_PMIC_STS_PMIC_REQ_BMSK                                0x400000
#define HWIO_SAW4_PMIC_STS_PMIC_REQ_SHFT                                    0x16
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_ADDR_IDX_BMSK                      0x380000
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_ADDR_IDX_SHFT                          0x13
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_SIZE_BMSK                           0x40000
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_SIZE_SHFT                              0x12
#define HWIO_SAW4_PMIC_STS_PMIC_STATE_BMSK                               0x30000
#define HWIO_SAW4_PMIC_STS_PMIC_STATE_SHFT                                  0x10
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_DATA_BMSK                              0xff
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_DATA_SHFT                               0x0

#define HWIO_SAW4_RST_ADDR(x)                                         ((x) + 0x0000001c)
#define HWIO_SAW4_RST_OFFS                                            (0x0000001c)
#define HWIO_SAW4_RST_RMSK                                                   0x1
#define HWIO_SAW4_RST_IN(x)      \
        in_dword_masked(HWIO_SAW4_RST_ADDR(x), HWIO_SAW4_RST_RMSK)
#define HWIO_SAW4_RST_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_RST_ADDR(x), m)
#define HWIO_SAW4_RST_OUT(x, v)      \
        out_dword(HWIO_SAW4_RST_ADDR(x),v)
#define HWIO_SAW4_RST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAW4_RST_ADDR(x),m,v,HWIO_SAW4_RST_IN(x))
#define HWIO_SAW4_RST_RST_BMSK                                               0x1
#define HWIO_SAW4_RST_RST_SHFT                                               0x0

#define HWIO_SAW4_SPM_STS3_ADDR(x)                                    ((x) + 0x00000020)
#define HWIO_SAW4_SPM_STS3_OFFS                                       (0x00000020)
#define HWIO_SAW4_SPM_STS3_RMSK                                       0x7fffffff
#define HWIO_SAW4_SPM_STS3_IN(x)      \
        in_dword_masked(HWIO_SAW4_SPM_STS3_ADDR(x), HWIO_SAW4_SPM_STS3_RMSK)
#define HWIO_SAW4_SPM_STS3_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_SPM_STS3_ADDR(x), m)
#define HWIO_SAW4_SPM_STS3_SPM_CURR_DLY_BMSK                          0x7fe00000
#define HWIO_SAW4_SPM_STS3_SPM_CURR_DLY_SHFT                                0x15
#define HWIO_SAW4_SPM_STS3_SPM_EVENT2_BMSK                              0x1fffe0
#define HWIO_SAW4_SPM_STS3_SPM_EVENT2_SHFT                                   0x5
#define HWIO_SAW4_SPM_STS3_DBG_STAY_AWAKE_BMSK                              0x10
#define HWIO_SAW4_SPM_STS3_DBG_STAY_AWAKE_SHFT                               0x4
#define HWIO_SAW4_SPM_STS3_SLEEP_STATE_BMSK                                  0x8
#define HWIO_SAW4_SPM_STS3_SLEEP_STATE_SHFT                                  0x3
#define HWIO_SAW4_SPM_STS3_WAKEUP_BMSK                                       0x4
#define HWIO_SAW4_SPM_STS3_WAKEUP_SHFT                                       0x2
#define HWIO_SAW4_SPM_STS3_WAIT_ACK_BMSK                                     0x2
#define HWIO_SAW4_SPM_STS3_WAIT_ACK_SHFT                                     0x1
#define HWIO_SAW4_SPM_STS3_WAIT_REQ_BMSK                                     0x1
#define HWIO_SAW4_SPM_STS3_WAIT_REQ_SHFT                                     0x0

#define HWIO_SAW4_CVS_STS_ADDR(x)                                     ((x) + 0x00000040)
#define HWIO_SAW4_CVS_STS_OFFS                                        (0x00000040)
#define HWIO_SAW4_CVS_STS_RMSK                                        0xffff03ff
#define HWIO_SAW4_CVS_STS_IN(x)      \
        in_dword_masked(HWIO_SAW4_CVS_STS_ADDR(x), HWIO_SAW4_CVS_STS_RMSK)
#define HWIO_SAW4_CVS_STS_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_CVS_STS_ADDR(x), m)
#define HWIO_SAW4_CVS_STS_CVS_EVENT_BMSK                              0xffff0000
#define HWIO_SAW4_CVS_STS_CVS_EVENT_SHFT                                    0x10
#define HWIO_SAW4_CVS_STS_CVS_BUSY_BMSK                                    0x200
#define HWIO_SAW4_CVS_STS_CVS_BUSY_SHFT                                      0x9
#define HWIO_SAW4_CVS_STS_CVS_CMD_ADDR_BMSK                                0x1ff
#define HWIO_SAW4_CVS_STS_CVS_CMD_ADDR_SHFT                                  0x0

#define HWIO_SAW4_CVS_STS2_ADDR(x)                                    ((x) + 0x00000044)
#define HWIO_SAW4_CVS_STS2_OFFS                                       (0x00000044)
#define HWIO_SAW4_CVS_STS2_RMSK                                       0xffffffff
#define HWIO_SAW4_CVS_STS2_IN(x)      \
        in_dword_masked(HWIO_SAW4_CVS_STS2_ADDR(x), HWIO_SAW4_CVS_STS2_RMSK)
#define HWIO_SAW4_CVS_STS2_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_CVS_STS2_ADDR(x), m)
#define HWIO_SAW4_CVS_STS2_CVS_PWR_CTL_BMSK                           0xffffffff
#define HWIO_SAW4_CVS_STS2_CVS_PWR_CTL_SHFT                                  0x0

#define HWIO_SAW4_CVS_STS3_ADDR(x)                                    ((x) + 0x00000048)
#define HWIO_SAW4_CVS_STS3_OFFS                                       (0x00000048)
#define HWIO_SAW4_CVS_STS3_RMSK                                         0xf0ffff
#define HWIO_SAW4_CVS_STS3_IN(x)      \
        in_dword_masked(HWIO_SAW4_CVS_STS3_ADDR(x), HWIO_SAW4_CVS_STS3_RMSK)
#define HWIO_SAW4_CVS_STS3_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_CVS_STS3_ADDR(x), m)
#define HWIO_SAW4_CVS_STS3_HALT_STATE_BMSK                              0x800000
#define HWIO_SAW4_CVS_STS3_HALT_STATE_SHFT                                  0x17
#define HWIO_SAW4_CVS_STS3_HALT_DONE_BMSK                               0x400000
#define HWIO_SAW4_CVS_STS3_HALT_DONE_SHFT                                   0x16
#define HWIO_SAW4_CVS_STS3_CVS_ACK_BMSK                                 0x200000
#define HWIO_SAW4_CVS_STS3_CVS_ACK_SHFT                                     0x15
#define HWIO_SAW4_CVS_STS3_CVS_REQ_BMSK                                 0x100000
#define HWIO_SAW4_CVS_STS3_CVS_REQ_SHFT                                     0x14
#define HWIO_SAW4_CVS_STS3_CVS_EVENT2_BMSK                                0xffff
#define HWIO_SAW4_CVS_STS3_CVS_EVENT2_SHFT                                   0x0

#define HWIO_SAW4_VERSION_ADDR(x)                                     ((x) + 0x000003d0)
#define HWIO_SAW4_VERSION_OFFS                                        (0x000003d0)
#define HWIO_SAW4_VERSION_RMSK                                        0xffffffff
#define HWIO_SAW4_VERSION_IN(x)      \
        in_dword_masked(HWIO_SAW4_VERSION_ADDR(x), HWIO_SAW4_VERSION_RMSK)
#define HWIO_SAW4_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_SAW4_VERSION_ADDR(x), m)
#define HWIO_SAW4_VERSION_MAJOR_BMSK                                  0xf0000000
#define HWIO_SAW4_VERSION_MAJOR_SHFT                                        0x1c
#define HWIO_SAW4_VERSION_MINOR_BMSK                                   0xfff0000
#define HWIO_SAW4_VERSION_MINOR_SHFT                                        0x10
#define HWIO_SAW4_VERSION_STEP_BMSK                                       0xffff
#define HWIO_SAW4_VERSION_STEP_SHFT                                          0x0


#endif /* __SPM_HAL_HWIO_H__ */
