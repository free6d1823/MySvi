#ifndef __HWDCVS_HWIO_H__
#define __HWDCVS_HWIO_H__
/*
===========================================================================
*/
/**
  @file hwdcvs_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r65.0]

  This file contains HWIO register definitions for the following modules:
    APCS_APR0_SAW4_2_0_AVS
    APCS_APR0_DCVS_APR
    APCS_APR0_APR_STS
    APCS_APR0_CORE_TM
    APCS_APC00_CPM
    APCS_APC00_DCVS_APC

  'Include' filters applied:
  'Exclude' filters applied: RESERVED DUMMY
*/
/*
  ===========================================================================

  Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

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

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * INCLUDES
 *--------------------------------------------------------------------------*/

#include <asm/hal/HALhwio.h>


/*----------------------------------------------------------------------------
 * BASE ADDRESSES
 *--------------------------------------------------------------------------*/

#define HMSS_PERIPH_BASE                                                     0xFF7E000000
#define HMSS_QLL_BASE                                                        0xFF80000000

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_SAW4_2_0_AVS
 *--------------------------------------------------------------------------*/

#define APCS_APR0_SAW4_2_0_AVS_REG_BASE                                 (HMSS_PERIPH_BASE      + 0x00246000)
#define APCS_APR0_SAW4_2_0_AVS_REG_BASE_OFFS                            0x00246000

#define HWIO_APCS_APR0_SAW4_VCTL_ADDR(x)                                ((x) + 0x00000100)
#define HWIO_APCS_APR0_SAW4_VCTL_OFFS                                   (0x00000100)
#define HWIO_APCS_APR0_SAW4_VCTL_RMSK                                     0x1700ff
#define HWIO_APCS_APR0_SAW4_VCTL_IN(x)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_VCTL_ADDR(x), HWIO_APCS_APR0_SAW4_VCTL_RMSK)
#define HWIO_APCS_APR0_SAW4_VCTL_INM(x, m)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_VCTL_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_VCTL_OUT(x, v)      \
                out_dword(HWIO_APCS_APR0_SAW4_VCTL_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_VCTL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_VCTL_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_VCTL_IN(x))
#define HWIO_APCS_APR0_SAW4_VCTL_SIZE_BMSK                                0x100000
#define HWIO_APCS_APR0_SAW4_VCTL_SIZE_SHFT                                    0x14
#define HWIO_APCS_APR0_SAW4_VCTL_ADR_IDX_BMSK                              0x70000
#define HWIO_APCS_APR0_SAW4_VCTL_ADR_IDX_SHFT                                 0x10
#define HWIO_APCS_APR0_SAW4_VCTL_PMIC_DATA_BMSK                               0xff
#define HWIO_APCS_APR0_SAW4_VCTL_PMIC_DATA_SHFT                                0x0

#define HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x)                             ((x) + 0x00000104)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_OFFS                                (0x00000104)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_RMSK                                0xffffdf7f
#define HWIO_APCS_APR0_SAW4_AVS_CTL_IN(x)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x), HWIO_APCS_APR0_SAW4_AVS_CTL_RMSK)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_INM(x, m)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_OUT(x, v)      \
                out_dword(HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_AVS_CTL_IN(x))
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_STEP_DN_BMSK                   0xff000000
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_STEP_DN_SHFT                         0x18
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_STEP_UP_BMSK                     0xff0000
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_STEP_UP_SHFT                         0x10
#define HWIO_APCS_APR0_SAW4_AVS_CTL_CPR_RAMP_EN_BMSK                        0x8000
#define HWIO_APCS_APR0_SAW4_AVS_CTL_CPR_RAMP_EN_SHFT                           0xf
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VCTL_RAMP_EN_BMSK                       0x4000
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VCTL_RAMP_EN_SHFT                          0xe
#define HWIO_APCS_APR0_SAW4_AVS_CTL_TMR_CLK_DIV_BMSK                        0x1f00
#define HWIO_APCS_APR0_SAW4_AVS_CTL_TMR_CLK_DIV_SHFT                           0x8
#define HWIO_APCS_APR0_SAW4_AVS_CTL_ILCPR_BMSK                                0x40
#define HWIO_APCS_APR0_SAW4_AVS_CTL_ILCPR_SHFT                                 0x6
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_WIDTH_BMSK                           0x20
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_WIDTH_SHFT                            0x5
#define HWIO_APCS_APR0_SAW4_AVS_CTL_CTL_SEL_BMSK                              0x10
#define HWIO_APCS_APR0_SAW4_AVS_CTL_CTL_SEL_SHFT                               0x4
#define HWIO_APCS_APR0_SAW4_AVS_CTL_SW_DONE_INT_EN_BMSK                        0x8
#define HWIO_APCS_APR0_SAW4_AVS_CTL_SW_DONE_INT_EN_SHFT                        0x3
#define HWIO_APCS_APR0_SAW4_AVS_CTL_MAX_INT_EN_BMSK                            0x4
#define HWIO_APCS_APR0_SAW4_AVS_CTL_MAX_INT_EN_SHFT                            0x2
#define HWIO_APCS_APR0_SAW4_AVS_CTL_MIN_INT_EN_BMSK                            0x2
#define HWIO_APCS_APR0_SAW4_AVS_CTL_MIN_INT_EN_SHFT                            0x1
#define HWIO_APCS_APR0_SAW4_AVS_CTL_EN_BMSK                                    0x1
#define HWIO_APCS_APR0_SAW4_AVS_CTL_EN_SHFT                                    0x0

#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x)                           ((x) + 0x00000108)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_OFFS                              (0x00000108)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_RMSK                                0xff00ff
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_IN(x)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x), HWIO_APCS_APR0_SAW4_AVS_LIMIT_RMSK)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_INM(x, m)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_OUT(x, v)      \
                out_dword(HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_AVS_LIMIT_IN(x))
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_MAX_VLVL_BMSK                       0xff0000
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_MAX_VLVL_SHFT                           0x10
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_MIN_VLVL_BMSK                           0xff
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_MIN_VLVL_SHFT                            0x0

#define HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x)                             ((x) + 0x0000010c)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_OFFS                                (0x0000010c)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_RMSK                                     0x3ff
#define HWIO_APCS_APR0_SAW4_AVS_DLY_IN(x)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x), HWIO_APCS_APR0_SAW4_AVS_DLY_RMSK)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_INM(x, m)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_OUT(x, v)      \
                out_dword(HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_AVS_DLY_IN(x))
#define HWIO_APCS_APR0_SAW4_AVS_DLY_AVS_DELAY_BMSK                           0x3ff
#define HWIO_APCS_APR0_SAW4_AVS_DLY_AVS_DELAY_SHFT                             0x0

#define HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x)                            ((x) + 0x00000110)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_OFFS                               (0x00000110)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_RMSK                                    0x3ff
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_IN(x)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x), HWIO_APCS_APR0_SAW4_VCTL_DLY_RMSK)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_INM(x, m)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_OUT(x, v)      \
                out_dword(HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_VCTL_DLY_IN(x))
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_VCTL_DELAY_BMSK                         0x3ff
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_VCTL_DELAY_SHFT                           0x0

#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_ADDR(x)                         ((x) + 0x00000114)
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_OFFS                            (0x00000114)
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_RMSK                                   0x1
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_OUT(x, v)      \
                out_dword(HWIO_APCS_APR0_SAW4_AVS_CLR_STS_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_CLR_CMD_BMSK                           0x1
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_CLR_CMD_SHFT                           0x0

#define HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x)                             ((x) + 0x00000120)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_OFFS                                (0x00000120)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_RMSK                                  0x7e1ff9
#define HWIO_APCS_APR0_SAW4_CVS_CTL_IN(x)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x), HWIO_APCS_APR0_SAW4_CVS_CTL_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_INM(x, m)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_OUT(x, v)      \
                out_dword(HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_CVS_CTL_IN(x))
#define HWIO_APCS_APR0_SAW4_CVS_CTL_SEQ_IDX_BMSK                          0x700000
#define HWIO_APCS_APR0_SAW4_CVS_CTL_SEQ_IDX_SHFT                              0x14
#define HWIO_APCS_APR0_SAW4_CVS_CTL_REQ_BMSK                               0x80000
#define HWIO_APCS_APR0_SAW4_CVS_CTL_REQ_SHFT                                  0x13
#define HWIO_APCS_APR0_SAW4_CVS_CTL_HALT_DONE_BMSK                         0x40000
#define HWIO_APCS_APR0_SAW4_CVS_CTL_HALT_DONE_SHFT                            0x12
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CTL_SEL_BMSK                           0x20000
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CTL_SEL_SHFT                              0x11
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CVS_START_ADR_BMSK                      0x1ff0
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CVS_START_ADR_SHFT                         0x4
#define HWIO_APCS_APR0_SAW4_CVS_CTL_ISAR_BMSK                                  0x8
#define HWIO_APCS_APR0_SAW4_CVS_CTL_ISAR_SHFT                                  0x3
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CVS_EN_BMSK                                0x1
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CVS_EN_SHFT                                0x0

#define HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x)                             ((x) + 0x00000124)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_OFFS                                (0x00000124)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_RMSK                                0x3fffffff
#define HWIO_APCS_APR0_SAW4_CVS_DLY_IN(x)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x), HWIO_APCS_APR0_SAW4_CVS_DLY_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_INM(x, m)      \
                in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_OUT(x, v)      \
                out_dword(HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_CVS_DLY_IN(x))
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY3_BMSK                           0x3ff00000
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY3_SHFT                                 0x14
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY2_BMSK                              0xffc00
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY2_SHFT                                  0xa
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY1_BMSK                                0x3ff
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY1_SHFT                                  0x0

#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n)                ((base) + 0x00000140 + 0x4 * (n))
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_OFFS(base,n)                (0x00000140 + 0x4 * (n))
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_RMSK                        0x801700ff
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_MAXn                                 3
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_INI(base,n)        \
                in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n), HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_INMI(base,n,mask)    \
                in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n), mask)
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_OUTI(base,n,val)    \
                out_dword(HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n),val)
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n),mask,val,HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_INI(base,n))
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_PMIC_CMD_MASK_BMSK          0x80000000
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_PMIC_CMD_MASK_SHFT                0x1f
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_SIZE_BMSK                     0x100000
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_SIZE_SHFT                         0x14
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADR_IDX_BMSK                   0x70000
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADR_IDX_SHFT                      0x10
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_DATA_BMSK                         0xff
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_DATA_SHFT                          0x0

#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n)                ((base) + 0x00000200 + 0x4 * (n))
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_OFFS(base,n)                (0x00000200 + 0x4 * (n))
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_RMSK                        0xffffffff
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_MAXn                                31
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_INI(base,n)        \
                in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n), HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_INMI(base,n,mask)    \
                in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n), mask)
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_OUTI(base,n,val)    \
                out_dword(HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n),val)
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n),mask,val,HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_INI(base,n))
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD3_BMSK                   0xff000000
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD3_SHFT                         0x18
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD2_BMSK                     0xff0000
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD2_SHFT                         0x10
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD1_BMSK                       0xff00
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD1_SHFT                          0x8
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD0_BMSK                         0xff
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD0_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_DCVS_APR
 *--------------------------------------------------------------------------*/

#define APCS_APR0_DCVS_APR_REG_BASE                                                (HMSS_PERIPH_BASE      + 0x00246600)
#define APCS_APR0_DCVS_APR_REG_BASE_OFFS                                           0x00246600

#define HWIO_APCS_APR0_DCVS_CTL_ADDR(x)                                            ((x) + 0x00000000)
#define HWIO_APCS_APR0_DCVS_CTL_OFFS                                               (0x00000000)
#define HWIO_APCS_APR0_DCVS_CTL_RMSK                                               0x80030001
#define HWIO_APCS_APR0_DCVS_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CTL_ADDR(x), HWIO_APCS_APR0_DCVS_CTL_RMSK)
#define HWIO_APCS_APR0_DCVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CTL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CTL_IN(x))
#define HWIO_APCS_APR0_DCVS_CTL_BUSY_BMSK                                          0x80000000
#define HWIO_APCS_APR0_DCVS_CTL_BUSY_SHFT                                                0x1f
#define HWIO_APCS_APR0_DCVS_CTL_IRQ_EN_BMSK                                           0x20000
#define HWIO_APCS_APR0_DCVS_CTL_IRQ_EN_SHFT                                              0x11
#define HWIO_APCS_APR0_DCVS_CTL_CSM_EN_BMSK                                           0x10000
#define HWIO_APCS_APR0_DCVS_CTL_CSM_EN_SHFT                                              0x10
#define HWIO_APCS_APR0_DCVS_CTL_REQ_BMSK                                                  0x1
#define HWIO_APCS_APR0_DCVS_CTL_REQ_SHFT                                                  0x0

#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x)                                  ((x) + 0x00000004)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_OFFS                                     (0x00000004)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_RMSK                                     0x80000001
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x), HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_RMSK)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_IN(x))
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_IRQ_STS_BMSK                             0x80000000
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_IRQ_STS_SHFT                                   0x1f
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_DONE_BMSK                                       0x1
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_DONE_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_ADDR(x)                               ((x) + 0x00000008)
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_OFFS                                  (0x00000008)
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_RMSK                                         0x7
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_ADDR(x), HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_RMSK)
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_CPR_MODE_STS_BMSK                            0x7
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_CPR_MODE_STS_SHFT                            0x0

#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x)                                  ((x) + 0x00000010)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_OFFS                                     (0x00000010)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_RMSK                                           0xff
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_VLVL_BMSK                                      0xff
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_VLVL_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x)                                  ((x) + 0x00000014)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_OFFS                                     (0x00000014)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_RMSK                                           0xff
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_VLVL_BMSK                                      0xff
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_VLVL_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x)                                  ((x) + 0x00000018)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_OFFS                                     (0x00000018)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_RMSK                                           0xff
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_VLVL_BMSK                                      0xff
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_VLVL_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x)                                   ((x) + 0x0000001c)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_OFFS                                      (0x0000001c)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_RMSK                                            0xff
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_VLVL_BMSK                                       0xff
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_VLVL_SHFT                                        0x0

#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x)                                  ((x) + 0x00000020)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_OFFS                                     (0x00000020)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_RMSK                                           0xff
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_VLVL_BMSK                                      0xff
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_VLVL_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x)                              ((x) + 0x00000030)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_OFFS                                 (0x00000030)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_RMSK                                      0x1ff
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_START_ADDR_BMSK                           0x1ff
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_START_ADDR_SHFT                             0x0

#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x)                              ((x) + 0x00000034)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_OFFS                                 (0x00000034)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_RMSK                                      0x1ff
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_START_ADDR_BMSK                           0x1ff
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_START_ADDR_SHFT                             0x0

#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x)                             ((x) + 0x00000038)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_OFFS                                (0x00000038)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_RMSK                                     0x1ff
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_START_ADDR_BMSK                          0x1ff
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_START_ADDR_SHFT                            0x0

#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x)                            ((x) + 0x0000003c)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_OFFS                               (0x0000003c)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_RMSK                                    0x1ff
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_START_ADDR_BMSK                         0x1ff
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_START_ADDR_SHFT                           0x0

#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x)                            ((x) + 0x00000040)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_OFFS                               (0x00000040)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_RMSK                                    0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_START_ADDR_BMSK                         0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_START_ADDR_SHFT                           0x0

#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x)                            ((x) + 0x00000044)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_OFFS                               (0x00000044)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_RMSK                                    0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_START_ADDR_BMSK                         0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_START_ADDR_SHFT                           0x0

#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x)                            ((x) + 0x00000048)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_OFFS                               (0x00000048)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_RMSK                                    0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_START_ADDR_BMSK                         0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_START_ADDR_SHFT                           0x0

#define HWIO_APCS_APR0_DCVS_CFG_ADDR(x)                                            ((x) + 0x00000050)
#define HWIO_APCS_APR0_DCVS_CFG_OFFS                                               (0x00000050)
#define HWIO_APCS_APR0_DCVS_CFG_RMSK                                                     0x71
#define HWIO_APCS_APR0_DCVS_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CFG_ADDR(x), HWIO_APCS_APR0_DCVS_CFG_RMSK)
#define HWIO_APCS_APR0_DCVS_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CFG_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CFG_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CFG_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CFG_IN(x))
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC2_BMSK                               0x40
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC2_SHFT                                0x6
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC1_BMSK                               0x20
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC1_SHFT                                0x5
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC0_BMSK                               0x10
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC0_SHFT                                0x4
#define HWIO_APCS_APR0_DCVS_CFG_CPR_FEATURE_EN_BMSK                                       0x1
#define HWIO_APCS_APR0_DCVS_CFG_CPR_FEATURE_EN_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x)                                ((x) + 0x00000054)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_OFFS                                   (0x00000054)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_RMSK                                   0xffffffff
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x), HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_RMSK)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_IN(x))
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_CVS_DLY_BMSK                           0xff000000
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_CVS_DLY_SHFT                                 0x18
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_AVS_DLY_BMSK                             0xff0000
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_AVS_DLY_SHFT                                 0x10
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_CPR_DLY_BMSK                               0xff00
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_CPR_DLY_SHFT                                  0x8
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_APM_DLY_BMSK                                 0xff
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_APM_DLY_SHFT                                  0x0

#define HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x)                                       ((x) + 0x00000058)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_OFFS                                          (0x00000058)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_RMSK                                           0x7ff07ff
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x), HWIO_APCS_APR0_DCVS_CHKN_FSM_RMSK)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CHKN_FSM_IN(x))
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_FORCE_SKIP_BMSK                                0x7ff0000
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_FORCE_SKIP_SHFT                                     0x10
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_NO_SKIP_BMSK                                       0x7ff
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_NO_SKIP_SHFT                                         0x0

#define HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x)                                       ((x) + 0x0000005c)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_OFFS                                          (0x0000005c)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_RMSK                                                0xff
#define HWIO_APCS_APR0_DCVS_CHKN_APR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x), HWIO_APCS_APR0_DCVS_CHKN_APR_RMSK)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CHKN_APR_IN(x))
#define HWIO_APCS_APR0_DCVS_CHKN_APR_DSBL_FUSED_APC_HS_BMSK                              0x80
#define HWIO_APCS_APR0_DCVS_CHKN_APR_DSBL_FUSED_APC_HS_SHFT                               0x7
#define HWIO_APCS_APR0_DCVS_CHKN_APR_DSBL_ALWAYS_SMT_CLR_BMSK                            0x40
#define HWIO_APCS_APR0_DCVS_CHKN_APR_DSBL_ALWAYS_SMT_CLR_SHFT                             0x6
#define HWIO_APCS_APR0_DCVS_CHKN_APR_GLB_SWITCH_CLK_ALL_BMSK                             0x20
#define HWIO_APCS_APR0_DCVS_CHKN_APR_GLB_SWITCH_CLK_ALL_SHFT                              0x5
#define HWIO_APCS_APR0_DCVS_CHKN_APR_IGNORE_LDO_DSBL_MASK_BMSK                           0x10
#define HWIO_APCS_APR0_DCVS_CHKN_APR_IGNORE_LDO_DSBL_MASK_SHFT                            0x4
#define HWIO_APCS_APR0_DCVS_CHKN_APR_FORCE_L2_ACC_SEL_TO_0_BMSK                           0x8
#define HWIO_APCS_APR0_DCVS_CHKN_APR_FORCE_L2_ACC_SEL_TO_0_SHFT                           0x3
#define HWIO_APCS_APR0_DCVS_CHKN_APR_FORCE_CPU_ACC_SEL_TO_0_BMSK                          0x4
#define HWIO_APCS_APR0_DCVS_CHKN_APR_FORCE_CPU_ACC_SEL_TO_0_SHFT                          0x2
#define HWIO_APCS_APR0_DCVS_CHKN_APR_DSBL_SMT_SET_ON_LDO_EXIT_BMSK                        0x2
#define HWIO_APCS_APR0_DCVS_CHKN_APR_DSBL_SMT_SET_ON_LDO_EXIT_SHFT                        0x1
#define HWIO_APCS_APR0_DCVS_CHKN_APR_DSBL_AVS_HS_RAMP_DLY_BMSK                            0x1
#define HWIO_APCS_APR0_DCVS_CHKN_APR_DSBL_AVS_HS_RAMP_DLY_SHFT                            0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x)                                    ((x) + 0x00000060)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_OFFS                                       (0x00000060)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_RMSK                                              0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ENABLE_BMSK                                       0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ENABLE_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x)                               ((x) + 0x00000064)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_OFFS                                  (0x00000064)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RMSK                                   0x7ffffff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_PGS_RET_DIS_BMSK                       0x4000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_PGS_RET_DIS_SHFT                            0x1a
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_APM_MODE_BMSK                          0x2000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_APM_MODE_SHFT                               0x19
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ACC_SEL_BMSK                           0x1000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ACC_SEL_SHFT                                0x18
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_SAFE_LVAL_BMSK                     0xff0000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_SAFE_LVAL_SHFT                         0x10
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_FLOOR_VLVL_BMSK                      0xff00
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_FLOOR_VLVL_SHFT                         0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_CEILING_VLVL_BMSK                      0xff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_CEILING_VLVL_SHFT                       0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x)                                ((x) + 0x00000068)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_OFFS                                   (0x00000068)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_RMSK                                   0x7777f773
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_ACC_SEL_BMSK                       0x70000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_ACC_SEL_SHFT                             0x1c
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_CPR_MODE_BMSK                           0x7000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_CPR_MODE_SHFT                                0x18
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_LDO_MODE_BMSK                            0x700000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_LDO_MODE_SHFT                                0x14
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_LDO_DSBL_MASK_BMSK                        0x70000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_LDO_DSBL_MASK_SHFT                           0x10
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_PMIC_CMD_MASK_BMSK                         0xf000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_PMIC_CMD_MASK_SHFT                            0xc
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_PERF_DN_BMSK                            0x700
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_PERF_DN_SHFT                              0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_PERF_UP_BMSK                             0x70
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_PERF_UP_SHFT                              0x4
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_VOLTAGE_DN_BMSK                               0x2
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_VOLTAGE_DN_SHFT                               0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_VOLTAGE_UP_BMSK                               0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_VOLTAGE_UP_SHFT                               0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x)                               ((x) + 0x0000006c)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_OFFS                                  (0x0000006c)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_RMSK                                       0x7ff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_CPR_POST_BMSK                         0x400
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_CPR_POST_SHFT                           0xa
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_POST_CHANGE_BMSK                  0x200
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_POST_CHANGE_SHFT                    0x9
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_FREQ_UP_BMSK               0x100
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_FREQ_UP_SHFT                 0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_VOLTAGE_BMSK                0x80
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_VOLTAGE_SHFT                 0x7
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_FREQ_DN_BMSK                0x40
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_FREQ_DN_SHFT                 0x6
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_PRE_CHANGE_BMSK                    0x20
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_PRE_CHANGE_SHFT                     0x5
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_FLOOR_BMSK                      0x10
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_FLOOR_SHFT                       0x4
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_CEILING_BMSK                     0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_CEILING_SHFT                     0x3
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_RAIL_BMSK                        0x4
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_RAIL_SHFT                        0x2
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_CPR_PRE_BMSK                            0x2
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_CPR_PRE_SHFT                            0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_ALL_SEQ_BMSK                            0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_ALL_SEQ_SHFT                            0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x)                              ((x) + 0x00000070)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_OFFS                                 (0x00000070)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_RMSK                                   0xffffff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC2_SAFE_LVAL_BMSK                    0xff0000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC2_SAFE_LVAL_SHFT                        0x10
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC1_SAFE_LVAL_BMSK                      0xff00
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC1_SAFE_LVAL_SHFT                         0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC0_SAFE_LVAL_BMSK                        0xff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC0_SAFE_LVAL_SHFT                         0x0

#define HWIO_APCS_APR0_DCVS_AGG_STS_ADDR(x)                                        ((x) + 0x00000074)
#define HWIO_APCS_APR0_DCVS_AGG_STS_OFFS                                           (0x00000074)
#define HWIO_APCS_APR0_DCVS_AGG_STS_RMSK                                           0xffffffff
#define HWIO_APCS_APR0_DCVS_AGG_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_STS_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_STS_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_STS_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_STS_STATUS_BMSK                                    0xffffffff
#define HWIO_APCS_APR0_DCVS_AGG_STS_STATUS_SHFT                                           0x0

#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x)                                    ((x) + 0x00000080)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_OFFS                                       (0x00000080)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_RMSK                                              0x1
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x), HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_RMSK)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_IN(x))
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_CVS_EVENT_BMSK                                    0x1
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_CVS_EVENT_SHFT                                    0x0

#define HWIO_APCS_APR0_DCVS_CVS_WAR_ADDR(x)                                        ((x) + 0x00000084)
#define HWIO_APCS_APR0_DCVS_CVS_WAR_OFFS                                           (0x00000084)
#define HWIO_APCS_APR0_DCVS_CVS_WAR_RMSK                                           0xffffffff
#define HWIO_APCS_APR0_DCVS_CVS_WAR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_WAR_ADDR(x), HWIO_APCS_APR0_DCVS_CVS_WAR_RMSK)
#define HWIO_APCS_APR0_DCVS_CVS_WAR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_WAR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CVS_WAR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CVS_WAR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CVS_WAR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CVS_WAR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CVS_WAR_IN(x))
#define HWIO_APCS_APR0_DCVS_CVS_WAR_WAR_BMSK                                       0xffffffff
#define HWIO_APCS_APR0_DCVS_CVS_WAR_WAR_SHFT                                              0x0

#define HWIO_APCS_APR0_DCVS_CVS_MASK_ADDR(x)                                       ((x) + 0x00000088)
#define HWIO_APCS_APR0_DCVS_CVS_MASK_OFFS                                          (0x00000088)
#define HWIO_APCS_APR0_DCVS_CVS_MASK_RMSK                                          0xffffffff
#define HWIO_APCS_APR0_DCVS_CVS_MASK_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_MASK_ADDR(x), HWIO_APCS_APR0_DCVS_CVS_MASK_RMSK)
#define HWIO_APCS_APR0_DCVS_CVS_MASK_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_MASK_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CVS_MASK_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CVS_MASK_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CVS_MASK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CVS_MASK_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CVS_MASK_IN(x))
#define HWIO_APCS_APR0_DCVS_CVS_MASK_MASK_BMSK                                     0xffffffff
#define HWIO_APCS_APR0_DCVS_CVS_MASK_MASK_SHFT                                            0x0

#define HWIO_APCS_APR0_APM_MODE_ADDR(x)                                            ((x) + 0x000000a0)
#define HWIO_APCS_APR0_APM_MODE_OFFS                                               (0x000000a0)
#define HWIO_APCS_APR0_APM_MODE_RMSK                                                 0x117111
#define HWIO_APCS_APR0_APM_MODE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_APM_MODE_ADDR(x), HWIO_APCS_APR0_APM_MODE_RMSK)
#define HWIO_APCS_APR0_APM_MODE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_APM_MODE_ADDR(x), m)
#define HWIO_APCS_APR0_APM_MODE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_APM_MODE_ADDR(x),v)
#define HWIO_APCS_APR0_APM_MODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_APM_MODE_ADDR(x),m,v,HWIO_APCS_APR0_APM_MODE_IN(x))
#define HWIO_APCS_APR0_APM_MODE_SPARE_BMSK                                           0x100000
#define HWIO_APCS_APR0_APM_MODE_SPARE_SHFT                                               0x14
#define HWIO_APCS_APR0_APM_MODE_DISABLE_FORCE_CLK_BMSK                                0x10000
#define HWIO_APCS_APR0_APM_MODE_DISABLE_FORCE_CLK_SHFT                                   0x10
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC2_EN_BMSK                               0x4000
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC2_EN_SHFT                                  0xe
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC1_EN_BMSK                               0x2000
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC1_EN_SHFT                                  0xd
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC0_EN_BMSK                               0x1000
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC0_EN_SHFT                                  0xc
#define HWIO_APCS_APR0_APM_MODE_APM_VCMP_SEL_BMSK                                       0x100
#define HWIO_APCS_APR0_APM_MODE_APM_VCMP_SEL_SHFT                                         0x8
#define HWIO_APCS_APR0_APM_MODE_SW_PWR_MUX_APCC_SEL_BMSK                                 0x10
#define HWIO_APCS_APR0_APM_MODE_SW_PWR_MUX_APCC_SEL_SHFT                                  0x4
#define HWIO_APCS_APR0_APM_MODE_SW_HW_MODE_SEL_BMSK                                       0x1
#define HWIO_APCS_APR0_APM_MODE_SW_HW_MODE_SEL_SHFT                                       0x0

#define HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x)                                        ((x) + 0x000000a4)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_OFFS                                           (0x000000a4)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_RMSK                                                  0x1
#define HWIO_APCS_APR0_RAIL_ACC_SEL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x), HWIO_APCS_APR0_RAIL_ACC_SEL_RMSK)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x), m)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x),v)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x),m,v,HWIO_APCS_APR0_RAIL_ACC_SEL_IN(x))
#define HWIO_APCS_APR0_RAIL_ACC_SEL_RAIL_ACC_SEL_BMSK                                     0x1
#define HWIO_APCS_APR0_RAIL_ACC_SEL_RAIL_ACC_SEL_SHFT                                     0x0

#define HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x)                                       ((x) + 0x000000a8)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_OFFS                                          (0x000000a8)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RMSK                                          0xffffff01
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x), HWIO_APCS_APR0_MEGA_RAIL_CTL_RMSK)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x),m,v,HWIO_APCS_APR0_MEGA_RAIL_CTL_IN(x))
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_SAFE_LVAL_BMSK                           0xff000000
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_SAFE_LVAL_SHFT                                 0x18
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_FLOOR_VLVL_BMSK                            0xff0000
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_FLOOR_VLVL_SHFT                                0x10
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_CEIL_VLVL_BMSK                               0xff00
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_CEIL_VLVL_SHFT                                  0x8
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_MEGA_RAIL_MODE_BMSK                                  0x1
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_MEGA_RAIL_MODE_SHFT                                  0x0

#define HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x)                                        ((x) + 0x000000ac)
#define HWIO_APCS_APR0_LDO_VREF_ACC_OFFS                                           (0x000000ac)
#define HWIO_APCS_APR0_LDO_VREF_ACC_RMSK                                                 0x7f
#define HWIO_APCS_APR0_LDO_VREF_ACC_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x), HWIO_APCS_APR0_LDO_VREF_ACC_RMSK)
#define HWIO_APCS_APR0_LDO_VREF_ACC_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x), m)
#define HWIO_APCS_APR0_LDO_VREF_ACC_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x),v)
#define HWIO_APCS_APR0_LDO_VREF_ACC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x),m,v,HWIO_APCS_APR0_LDO_VREF_ACC_IN(x))
#define HWIO_APCS_APR0_LDO_VREF_ACC_VREF_ACC_BMSK                                        0x7f
#define HWIO_APCS_APR0_LDO_VREF_ACC_VREF_ACC_SHFT                                         0x0

#define HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x)                                          ((x) + 0x000000b0)
#define HWIO_APCS_APR0_ACC_CTL_EN_OFFS                                             (0x000000b0)
#define HWIO_APCS_APR0_ACC_CTL_EN_RMSK                                                    0x1
#define HWIO_APCS_APR0_ACC_CTL_EN_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x), HWIO_APCS_APR0_ACC_CTL_EN_RMSK)
#define HWIO_APCS_APR0_ACC_CTL_EN_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x), m)
#define HWIO_APCS_APR0_ACC_CTL_EN_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x),v)
#define HWIO_APCS_APR0_ACC_CTL_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x),m,v,HWIO_APCS_APR0_ACC_CTL_EN_IN(x))
#define HWIO_APCS_APR0_ACC_CTL_EN_ENABLE_BMSK                                             0x1
#define HWIO_APCS_APR0_ACC_CTL_EN_ENABLE_SHFT                                             0x0

#define HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x)                                         ((x) + 0x000000b4)
#define HWIO_APCS_APR0_ACC_CTL_DLY_OFFS                                            (0x000000b4)
#define HWIO_APCS_APR0_ACC_CTL_DLY_RMSK                                            0xffffffff
#define HWIO_APCS_APR0_ACC_CTL_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x), HWIO_APCS_APR0_ACC_CTL_DLY_RMSK)
#define HWIO_APCS_APR0_ACC_CTL_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_ACC_CTL_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_ACC_CTL_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x),m,v,HWIO_APCS_APR0_ACC_CTL_DLY_IN(x))
#define HWIO_APCS_APR0_ACC_CTL_DLY_VREF_TGT_DLY_BMSK                               0xff000000
#define HWIO_APCS_APR0_ACC_CTL_DLY_VREF_TGT_DLY_SHFT                                     0x18
#define HWIO_APCS_APR0_ACC_CTL_DLY_ACC_SEL_DLY_BMSK                                  0xff0000
#define HWIO_APCS_APR0_ACC_CTL_DLY_ACC_SEL_DLY_SHFT                                      0x10
#define HWIO_APCS_APR0_ACC_CTL_DLY_SWITCH_DLY_BMSK                                     0xff00
#define HWIO_APCS_APR0_ACC_CTL_DLY_SWITCH_DLY_SHFT                                        0x8
#define HWIO_APCS_APR0_ACC_CTL_DLY_VREF_ACC_DLY_BMSK                                     0xff
#define HWIO_APCS_APR0_ACC_CTL_DLY_VREF_ACC_DLY_SHFT                                      0x0

#define HWIO_APCS_APR0_ACC_CTL_STS_ADDR(x)                                         ((x) + 0x000000b8)
#define HWIO_APCS_APR0_ACC_CTL_STS_OFFS                                            (0x000000b8)
#define HWIO_APCS_APR0_ACC_CTL_STS_RMSK                                            0xffffffff
#define HWIO_APCS_APR0_ACC_CTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_STS_ADDR(x), HWIO_APCS_APR0_ACC_CTL_STS_RMSK)
#define HWIO_APCS_APR0_ACC_CTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_STS_ADDR(x), m)
#define HWIO_APCS_APR0_ACC_CTL_STS_STATUS_BMSK                                     0xffffffff
#define HWIO_APCS_APR0_ACC_CTL_STS_STATUS_SHFT                                            0x0

#define HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x)                                         ((x) + 0x000000c0)
#define HWIO_APCS_APR0_AVM_AGG_CTL_OFFS                                            (0x000000c0)
#define HWIO_APCS_APR0_AVM_AGG_CTL_RMSK                                            0xffff00ff
#define HWIO_APCS_APR0_AVM_AGG_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x), HWIO_APCS_APR0_AVM_AGG_CTL_RMSK)
#define HWIO_APCS_APR0_AVM_AGG_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_AGG_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x),m,v,HWIO_APCS_APR0_AVM_AGG_CTL_IN(x))
#define HWIO_APCS_APR0_AVM_AGG_CTL_DN_STEP_SIZE_BMSK                               0xff000000
#define HWIO_APCS_APR0_AVM_AGG_CTL_DN_STEP_SIZE_SHFT                                     0x18
#define HWIO_APCS_APR0_AVM_AGG_CTL_UP_STEP_SIZE_BMSK                                 0xff0000
#define HWIO_APCS_APR0_AVM_AGG_CTL_UP_STEP_SIZE_SHFT                                     0x10
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_DN_IRPT_EN_BMSK                                  0x80
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_DN_IRPT_EN_SHFT                                   0x7
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_UP_IRPT_EN_BMSK                                  0x40
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_UP_IRPT_EN_SHFT                                   0x6
#define HWIO_APCS_APR0_AVM_AGG_CTL_LDO_DN_IRPT_EN_BMSK                                   0x20
#define HWIO_APCS_APR0_AVM_AGG_CTL_LDO_DN_IRPT_EN_SHFT                                    0x5
#define HWIO_APCS_APR0_AVM_AGG_CTL_LDO_UP_IRPT_EN_BMSK                                   0x10
#define HWIO_APCS_APR0_AVM_AGG_CTL_LDO_UP_IRPT_EN_SHFT                                    0x4
#define HWIO_APCS_APR0_AVM_AGG_CTL_DN_ERR_IRPT_EN_BMSK                                    0x8
#define HWIO_APCS_APR0_AVM_AGG_CTL_DN_ERR_IRPT_EN_SHFT                                    0x3
#define HWIO_APCS_APR0_AVM_AGG_CTL_UP_ERR_IRPT_EN_BMSK                                    0x4
#define HWIO_APCS_APR0_AVM_AGG_CTL_UP_ERR_IRPT_EN_SHFT                                    0x2
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_MODE_BMSK                                         0x2
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_MODE_SHFT                                         0x1
#define HWIO_APCS_APR0_AVM_AGG_CTL_EN_BMSK                                                0x1
#define HWIO_APCS_APR0_AVM_AGG_CTL_EN_SHFT                                                0x0

#define HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x)                                         ((x) + 0x000000c4)
#define HWIO_APCS_APR0_AVM_AGG_DLY_OFFS                                            (0x000000c4)
#define HWIO_APCS_APR0_AVM_AGG_DLY_RMSK                                               0x3ff1f
#define HWIO_APCS_APR0_AVM_AGG_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x), HWIO_APCS_APR0_AVM_AGG_DLY_RMSK)
#define HWIO_APCS_APR0_AVM_AGG_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_AGG_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x),m,v,HWIO_APCS_APR0_AVM_AGG_DLY_IN(x))
#define HWIO_APCS_APR0_AVM_AGG_DLY_DLY_BMSK                                           0x3ff00
#define HWIO_APCS_APR0_AVM_AGG_DLY_DLY_SHFT                                               0x8
#define HWIO_APCS_APR0_AVM_AGG_DLY_CLK_DIV_BMSK                                          0x1f
#define HWIO_APCS_APR0_AVM_AGG_DLY_CLK_DIV_SHFT                                           0x0

#define HWIO_APCS_APR0_AVM_AGG_STS_ADDR(x)                                         ((x) + 0x000000c8)
#define HWIO_APCS_APR0_AVM_AGG_STS_OFFS                                            (0x000000c8)
#define HWIO_APCS_APR0_AVM_AGG_STS_RMSK                                            0xffffffff
#define HWIO_APCS_APR0_AVM_AGG_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_STS_ADDR(x), HWIO_APCS_APR0_AVM_AGG_STS_RMSK)
#define HWIO_APCS_APR0_AVM_AGG_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_STS_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_AGG_STS_STATUS_BMSK                                     0xffffffff
#define HWIO_APCS_APR0_AVM_AGG_STS_STATUS_SHFT                                            0x0

#define HWIO_APCS_APR0_AVM_EVENT_STS_ADDR(x)                                       ((x) + 0x000000cc)
#define HWIO_APCS_APR0_AVM_EVENT_STS_OFFS                                          (0x000000cc)
#define HWIO_APCS_APR0_AVM_EVENT_STS_RMSK                                             0x7777f
#define HWIO_APCS_APR0_AVM_EVENT_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_EVENT_STS_ADDR(x), HWIO_APCS_APR0_AVM_EVENT_STS_RMSK)
#define HWIO_APCS_APR0_AVM_EVENT_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_EVENT_STS_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_DN_EVENT_BMSK                               0x40000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_DN_EVENT_SHFT                                  0x12
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_DN_EVENT_BMSK                               0x20000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_DN_EVENT_SHFT                                  0x11
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_DN_EVENT_BMSK                               0x10000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_DN_EVENT_SHFT                                  0x10
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_UP_EVENT_BMSK                                0x4000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_UP_EVENT_SHFT                                   0xe
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_UP_EVENT_BMSK                                0x2000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_UP_EVENT_SHFT                                   0xd
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_UP_EVENT_BMSK                                0x1000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_UP_EVENT_SHFT                                   0xc
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_LDO_DN_EVENT_BMSK                             0x400
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_LDO_DN_EVENT_SHFT                               0xa
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_LDO_DN_EVENT_BMSK                             0x200
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_LDO_DN_EVENT_SHFT                               0x9
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_LDO_DN_EVENT_BMSK                             0x100
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_LDO_DN_EVENT_SHFT                               0x8
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_LDO_UP_EVENT_BMSK                              0x40
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_LDO_UP_EVENT_SHFT                               0x6
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_LDO_UP_EVENT_BMSK                              0x20
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_LDO_UP_EVENT_SHFT                               0x5
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_LDO_UP_EVENT_BMSK                              0x10
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_LDO_UP_EVENT_SHFT                               0x4
#define HWIO_APCS_APR0_AVM_EVENT_STS_RAIL_DN_EVENT_BMSK                                   0x8
#define HWIO_APCS_APR0_AVM_EVENT_STS_RAIL_DN_EVENT_SHFT                                   0x3
#define HWIO_APCS_APR0_AVM_EVENT_STS_RAIL_UP_EVENT_BMSK                                   0x4
#define HWIO_APCS_APR0_AVM_EVENT_STS_RAIL_UP_EVENT_SHFT                                   0x2
#define HWIO_APCS_APR0_AVM_EVENT_STS_DN_ERR_EVENT_BMSK                                    0x2
#define HWIO_APCS_APR0_AVM_EVENT_STS_DN_ERR_EVENT_SHFT                                    0x1
#define HWIO_APCS_APR0_AVM_EVENT_STS_UP_ERR_EVENT_BMSK                                    0x1
#define HWIO_APCS_APR0_AVM_EVENT_STS_UP_ERR_EVENT_SHFT                                    0x0

#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_ADDR(x)                              ((x) + 0x000000d0)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_OFFS                                 (0x000000d0)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_RMSK                                        0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_ACK_BMSK                                    0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_ACK_SHFT                                    0x0

#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_ADDR(x)                             ((x) + 0x000000d4)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_OFFS                                (0x000000d4)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_RMSK                                       0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_DONE_BMSK                                  0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_DONE_SHFT                                  0x0

#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_ADDR(x)                              ((x) + 0x000000d8)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_OFFS                                 (0x000000d8)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_RMSK                                        0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_ACK_BMSK                                    0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_ACK_SHFT                                    0x0

#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_ADDR(x)                             ((x) + 0x000000dc)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_OFFS                                (0x000000dc)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_RMSK                                       0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_DONE_BMSK                                  0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_DONE_SHFT                                  0x0

#define HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x)                                       ((x) + 0x000000e0)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_OFFS                                          (0x000000e0)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_RMSK                                                0x73
#define HWIO_APCS_APR0_AVM_APC0_VOTE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x), HWIO_APCS_APR0_AVM_APC0_VOTE_RMSK)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x),m,v,HWIO_APCS_APR0_AVM_APC0_VOTE_IN(x))
#define HWIO_APCS_APR0_AVM_APC0_VOTE_PWR_STATE_THRESHOLD_BMSK                            0x70
#define HWIO_APCS_APR0_AVM_APC0_VOTE_PWR_STATE_THRESHOLD_SHFT                             0x4
#define HWIO_APCS_APR0_AVM_APC0_VOTE_VOTE_SLP_EN_BMSK                                     0x2
#define HWIO_APCS_APR0_AVM_APC0_VOTE_VOTE_SLP_EN_SHFT                                     0x1
#define HWIO_APCS_APR0_AVM_APC0_VOTE_VOTE_EN_BMSK                                         0x1
#define HWIO_APCS_APR0_AVM_APC0_VOTE_VOTE_EN_SHFT                                         0x0

#define HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x)                                       ((x) + 0x000000e4)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_OFFS                                          (0x000000e4)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_RMSK                                                0x73
#define HWIO_APCS_APR0_AVM_APC1_VOTE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x), HWIO_APCS_APR0_AVM_APC1_VOTE_RMSK)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x),m,v,HWIO_APCS_APR0_AVM_APC1_VOTE_IN(x))
#define HWIO_APCS_APR0_AVM_APC1_VOTE_PWR_STATE_THRESHOLD_BMSK                            0x70
#define HWIO_APCS_APR0_AVM_APC1_VOTE_PWR_STATE_THRESHOLD_SHFT                             0x4
#define HWIO_APCS_APR0_AVM_APC1_VOTE_VOTE_SLP_EN_BMSK                                     0x2
#define HWIO_APCS_APR0_AVM_APC1_VOTE_VOTE_SLP_EN_SHFT                                     0x1
#define HWIO_APCS_APR0_AVM_APC1_VOTE_VOTE_EN_BMSK                                         0x1
#define HWIO_APCS_APR0_AVM_APC1_VOTE_VOTE_EN_SHFT                                         0x0

#define HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x)                                       ((x) + 0x000000e8)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_OFFS                                          (0x000000e8)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_RMSK                                                0x73
#define HWIO_APCS_APR0_AVM_APC2_VOTE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x), HWIO_APCS_APR0_AVM_APC2_VOTE_RMSK)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x),m,v,HWIO_APCS_APR0_AVM_APC2_VOTE_IN(x))
#define HWIO_APCS_APR0_AVM_APC2_VOTE_PWR_STATE_THRESHOLD_BMSK                            0x70
#define HWIO_APCS_APR0_AVM_APC2_VOTE_PWR_STATE_THRESHOLD_SHFT                             0x4
#define HWIO_APCS_APR0_AVM_APC2_VOTE_VOTE_SLP_EN_BMSK                                     0x2
#define HWIO_APCS_APR0_AVM_APC2_VOTE_VOTE_SLP_EN_SHFT                                     0x1
#define HWIO_APCS_APR0_AVM_APC2_VOTE_VOTE_EN_BMSK                                         0x1
#define HWIO_APCS_APR0_AVM_APC2_VOTE_VOTE_EN_SHFT                                         0x0

#define HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x)                                         ((x) + 0x000000f0)
#define HWIO_APCS_APR0_AVM_IRQ_STS_OFFS                                            (0x000000f0)
#define HWIO_APCS_APR0_AVM_IRQ_STS_RMSK                                                 0x77f
#define HWIO_APCS_APR0_AVM_IRQ_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x), HWIO_APCS_APR0_AVM_IRQ_STS_RMSK)
#define HWIO_APCS_APR0_AVM_IRQ_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_IRQ_STS_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_IRQ_STS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x),m,v,HWIO_APCS_APR0_AVM_IRQ_STS_IN(x))
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC2_LDO_DN_EVENT_BMSK                               0x400
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC2_LDO_DN_EVENT_SHFT                                 0xa
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC1_LDO_DN_EVENT_BMSK                               0x200
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC1_LDO_DN_EVENT_SHFT                                 0x9
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC0_LDO_DN_EVENT_BMSK                               0x100
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC0_LDO_DN_EVENT_SHFT                                 0x8
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC2_LDO_UP_EVENT_BMSK                                0x40
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC2_LDO_UP_EVENT_SHFT                                 0x6
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC1_LDO_UP_EVENT_BMSK                                0x20
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC1_LDO_UP_EVENT_SHFT                                 0x5
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC0_LDO_UP_EVENT_BMSK                                0x10
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC0_LDO_UP_EVENT_SHFT                                 0x4
#define HWIO_APCS_APR0_AVM_IRQ_STS_RAIL_DN_EVENT_BMSK                                     0x8
#define HWIO_APCS_APR0_AVM_IRQ_STS_RAIL_DN_EVENT_SHFT                                     0x3
#define HWIO_APCS_APR0_AVM_IRQ_STS_RAIL_UP_EVENT_BMSK                                     0x4
#define HWIO_APCS_APR0_AVM_IRQ_STS_RAIL_UP_EVENT_SHFT                                     0x2
#define HWIO_APCS_APR0_AVM_IRQ_STS_DN_ERR_EVENT_BMSK                                      0x2
#define HWIO_APCS_APR0_AVM_IRQ_STS_DN_ERR_EVENT_SHFT                                      0x1
#define HWIO_APCS_APR0_AVM_IRQ_STS_UP_ERR_EVENT_BMSK                                      0x1
#define HWIO_APCS_APR0_AVM_IRQ_STS_UP_ERR_EVENT_SHFT                                      0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_APR_STS
 *--------------------------------------------------------------------------*/

#define APCS_APR0_APR_STS_REG_BASE                                         (HMSS_PERIPH_BASE      + 0x002c6400)
#define APCS_APR0_APR_STS_REG_BASE_OFFS                                    0x002c6400

#define HWIO_APCS_APR0_STS_PGS_RET_STS_ADDR(x)                                 ((x) + 0x00000000)
#define HWIO_APCS_APR0_STS_PGS_RET_STS_OFFS                                    (0x00000000)
#define HWIO_APCS_APR0_STS_PGS_RET_STS_RMSK                                         0x1ff
#define HWIO_APCS_APR0_STS_PGS_RET_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_PGS_RET_STS_ADDR(x), HWIO_APCS_APR0_STS_PGS_RET_STS_RMSK)
#define HWIO_APCS_APR0_STS_PGS_RET_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_PGS_RET_STS_ADDR(x), m)
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC2_L2_PGS_RET_SLP_BMSK                     0x100
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC2_L2_PGS_RET_SLP_SHFT                       0x8
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC2_CPU1_PGS_RET_SLP_BMSK                    0x80
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC2_CPU1_PGS_RET_SLP_SHFT                     0x7
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC2_CPU0_PGS_RET_SLP_BMSK                    0x40
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC2_CPU0_PGS_RET_SLP_SHFT                     0x6
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC1_L2_PGS_RET_SLP_BMSK                      0x20
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC1_L2_PGS_RET_SLP_SHFT                       0x5
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC1_CPU1_PGS_RET_SLP_BMSK                    0x10
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC1_CPU1_PGS_RET_SLP_SHFT                     0x4
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC1_CPU0_PGS_RET_SLP_BMSK                     0x8
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC1_CPU0_PGS_RET_SLP_SHFT                     0x3
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC0_L2_PGS_RET_SLP_BMSK                       0x4
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC0_L2_PGS_RET_SLP_SHFT                       0x2
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC0_CPU1_PGS_RET_SLP_BMSK                     0x2
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC0_CPU1_PGS_RET_SLP_SHFT                     0x1
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC0_CPU0_PGS_RET_SLP_BMSK                     0x1
#define HWIO_APCS_APR0_STS_PGS_RET_STS_APC0_CPU0_PGS_RET_SLP_SHFT                     0x0

#define HWIO_APCS_APR0_STS_APM_CTL_STS_ADDR(x)                                 ((x) + 0x00000040)
#define HWIO_APCS_APR0_STS_APM_CTL_STS_OFFS                                    (0x00000040)
#define HWIO_APCS_APR0_STS_APM_CTL_STS_RMSK                                    0xffffffff
#define HWIO_APCS_APR0_STS_APM_CTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_APM_CTL_STS_ADDR(x), HWIO_APCS_APR0_STS_APM_CTL_STS_RMSK)
#define HWIO_APCS_APR0_STS_APM_CTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_APM_CTL_STS_ADDR(x), m)
#define HWIO_APCS_APR0_STS_APM_CTL_STS_PWR_MUX_MODE_BMSK                       0xff000000
#define HWIO_APCS_APR0_STS_APM_CTL_STS_PWR_MUX_MODE_SHFT                             0x18
#define HWIO_APCS_APR0_STS_APM_CTL_STS_TIMER_BMSK                                0xff0000
#define HWIO_APCS_APR0_STS_APM_CTL_STS_TIMER_SHFT                                    0x10
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC2_APC_GT_MEM_CELL_VMIN_BMSK              0x8000
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC2_APC_GT_MEM_CELL_VMIN_SHFT                 0xf
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC1_APC_GT_MEM_CELL_VMIN_BMSK              0x4000
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC1_APC_GT_MEM_CELL_VMIN_SHFT                 0xe
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC0_APC_GT_MEM_CELL_VMIN_BMSK              0x2000
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC0_APC_GT_MEM_CELL_VMIN_SHFT                 0xd
#define HWIO_APCS_APR0_STS_APM_CTL_STS_FORCE_CLK_OFF_BMSK                          0x1c00
#define HWIO_APCS_APR0_STS_APM_CTL_STS_FORCE_CLK_OFF_SHFT                             0xa
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC2_APC_GT_MX_BMSK                          0x200
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC2_APC_GT_MX_SHFT                            0x9
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC1_APC_GT_MX_BMSK                          0x100
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC1_APC_GT_MX_SHFT                            0x8
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC0_APC_GT_MX_BMSK                           0x80
#define HWIO_APCS_APR0_STS_APM_CTL_STS_APC0_APC_GT_MX_SHFT                            0x7
#define HWIO_APCS_APR0_STS_APM_CTL_STS_FREEZE_BMSK                                   0x40
#define HWIO_APCS_APR0_STS_APM_CTL_STS_FREEZE_SHFT                                    0x6
#define HWIO_APCS_APR0_STS_APM_CTL_STS_FORCE_CLK_OFF_BIT0_BMSK                       0x20
#define HWIO_APCS_APR0_STS_APM_CTL_STS_FORCE_CLK_OFF_BIT0_SHFT                        0x5
#define HWIO_APCS_APR0_STS_APM_CTL_STS_CUR_FSM_BMSK                                  0x1c
#define HWIO_APCS_APR0_STS_APM_CTL_STS_CUR_FSM_SHFT                                   0x2
#define HWIO_APCS_APR0_STS_APM_CTL_STS_PWR_MUX_SEL_SYNC_D1_BMSK                       0x2
#define HWIO_APCS_APR0_STS_APM_CTL_STS_PWR_MUX_SEL_SYNC_D1_SHFT                       0x1
#define HWIO_APCS_APR0_STS_APM_CTL_STS_PWR_MUX_SEL_SYNC_BMSK                          0x1
#define HWIO_APCS_APR0_STS_APM_CTL_STS_PWR_MUX_SEL_SYNC_SHFT                          0x0

#define HWIO_APCS_APR0_STS_MAS_RET_STS_ADDR(x)                                 ((x) + 0x00000044)
#define HWIO_APCS_APR0_STS_MAS_RET_STS_OFFS                                    (0x00000044)
#define HWIO_APCS_APR0_STS_MAS_RET_STS_RMSK                                         0x1ff
#define HWIO_APCS_APR0_STS_MAS_RET_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_MAS_RET_STS_ADDR(x), HWIO_APCS_APR0_STS_MAS_RET_STS_RMSK)
#define HWIO_APCS_APR0_STS_MAS_RET_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_MAS_RET_STS_ADDR(x), m)
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC2_L2_MAS_RET_SLP_BMSK                     0x100
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC2_L2_MAS_RET_SLP_SHFT                       0x8
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC2_CPU1_MAS_RET_SLP_BMSK                    0x80
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC2_CPU1_MAS_RET_SLP_SHFT                     0x7
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC2_CPU0_MAS_RET_SLP_BMSK                    0x40
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC2_CPU0_MAS_RET_SLP_SHFT                     0x6
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC1_L2_MAS_RET_SLP_BMSK                      0x20
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC1_L2_MAS_RET_SLP_SHFT                       0x5
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC1_CPU1_MAS_RET_SLP_BMSK                    0x10
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC1_CPU1_MAS_RET_SLP_SHFT                     0x4
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC1_CPU0_MAS_RET_SLP_BMSK                     0x8
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC1_CPU0_MAS_RET_SLP_SHFT                     0x3
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC0_L2_MAS_RET_SLP_BMSK                       0x4
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC0_L2_MAS_RET_SLP_SHFT                       0x2
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC0_CPU1_MAS_RET_SLP_BMSK                     0x2
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC0_CPU1_MAS_RET_SLP_SHFT                     0x1
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC0_CPU0_MAS_RET_SLP_BMSK                     0x1
#define HWIO_APCS_APR0_STS_MAS_RET_STS_APC0_CPU0_MAS_RET_SLP_SHFT                     0x0

#define HWIO_APCS_APR0_STS_PWR_CTL_STS_ADDR(x)                                 ((x) + 0x00000080)
#define HWIO_APCS_APR0_STS_PWR_CTL_STS_OFFS                                    (0x00000080)
#define HWIO_APCS_APR0_STS_PWR_CTL_STS_RMSK                                    0xffffffff
#define HWIO_APCS_APR0_STS_PWR_CTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_PWR_CTL_STS_ADDR(x), HWIO_APCS_APR0_STS_PWR_CTL_STS_RMSK)
#define HWIO_APCS_APR0_STS_PWR_CTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_PWR_CTL_STS_ADDR(x), m)
#define HWIO_APCS_APR0_STS_PWR_CTL_STS_TBD_BMSK                                0xffffffff
#define HWIO_APCS_APR0_STS_PWR_CTL_STS_TBD_SHFT                                       0x0

#define HWIO_APCS_APR0_STS_SER_STS_ADDR(x)                                     ((x) + 0x00000090)
#define HWIO_APCS_APR0_STS_SER_STS_OFFS                                        (0x00000090)
#define HWIO_APCS_APR0_STS_SER_STS_RMSK                                        0xffffffff
#define HWIO_APCS_APR0_STS_SER_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SER_STS_ADDR(x), HWIO_APCS_APR0_STS_SER_STS_RMSK)
#define HWIO_APCS_APR0_STS_SER_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SER_STS_ADDR(x), m)
#define HWIO_APCS_APR0_STS_SER_STS_RSV_1_BMSK                                  0xffff0000
#define HWIO_APCS_APR0_STS_SER_STS_RSV_1_SHFT                                        0x10
#define HWIO_APCS_APR0_STS_SER_STS_COUNTER_BMSK                                    0xff00
#define HWIO_APCS_APR0_STS_SER_STS_COUNTER_SHFT                                       0x8
#define HWIO_APCS_APR0_STS_SER_STS_RSV_0_BMSK                                        0xfc
#define HWIO_APCS_APR0_STS_SER_STS_RSV_0_SHFT                                         0x2
#define HWIO_APCS_APR0_STS_SER_STS_ANY_4_CLR_BMSK                                     0x2
#define HWIO_APCS_APR0_STS_SER_STS_ANY_4_CLR_SHFT                                     0x1
#define HWIO_APCS_APR0_STS_SER_STS_EN_DLY1_BMSK                                       0x1
#define HWIO_APCS_APR0_STS_SER_STS_EN_DLY1_SHFT                                       0x0

#define HWIO_APCS_APR0_STS_SER_INPUT_STS_ADDR(x)                               ((x) + 0x00000094)
#define HWIO_APCS_APR0_STS_SER_INPUT_STS_OFFS                                  (0x00000094)
#define HWIO_APCS_APR0_STS_SER_INPUT_STS_RMSK                                  0xffffffff
#define HWIO_APCS_APR0_STS_SER_INPUT_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SER_INPUT_STS_ADDR(x), HWIO_APCS_APR0_STS_SER_INPUT_STS_RMSK)
#define HWIO_APCS_APR0_STS_SER_INPUT_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SER_INPUT_STS_ADDR(x), m)
#define HWIO_APCS_APR0_STS_SER_INPUT_STS_IN_SIG_BMSK                           0xffffffff
#define HWIO_APCS_APR0_STS_SER_INPUT_STS_IN_SIG_SHFT                                  0x0

#define HWIO_APCS_APR0_STS_SER_OUTPUT_STS_ADDR(x)                              ((x) + 0x00000098)
#define HWIO_APCS_APR0_STS_SER_OUTPUT_STS_OFFS                                 (0x00000098)
#define HWIO_APCS_APR0_STS_SER_OUTPUT_STS_RMSK                                 0xffffffff
#define HWIO_APCS_APR0_STS_SER_OUTPUT_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SER_OUTPUT_STS_ADDR(x), HWIO_APCS_APR0_STS_SER_OUTPUT_STS_RMSK)
#define HWIO_APCS_APR0_STS_SER_OUTPUT_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SER_OUTPUT_STS_ADDR(x), m)
#define HWIO_APCS_APR0_STS_SER_OUTPUT_STS_OUT_SIG_BMSK                         0xffffffff
#define HWIO_APCS_APR0_STS_SER_OUTPUT_STS_OUT_SIG_SHFT                                0x0

#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_ADDR(x)                             ((x) + 0x000000c0)
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_OFFS                                (0x000000c0)
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_RMSK                                       0x7
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_ADDR(x), HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_RMSK)
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_ADDR(x), m)
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_APR_G2_BMSK                                0x4
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_APR_G2_SHFT                                0x2
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_APR_G1_BMSK                                0x2
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_APR_G1_SHFT                                0x1
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_APR_G0_BMSK                                0x1
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_APR_G0_SHFT                                0x0

#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_ADDR(x)                         ((x) + 0x000000c4)
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_OFFS                            (0x000000c4)
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_RMSK                                 0x1ff
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_ADDR(x), HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_RMSK)
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_ADDR(x), m)
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_APR_SPM_CMD_BMSK                     0x1ff
#define HWIO_APCS_APR0_STS_SYSRST_DIAG_STS_SPM_APR_SPM_CMD_SHFT                       0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_CORE_TM
 *--------------------------------------------------------------------------*/

#define APCS_APR0_CORE_TM_REG_BASE                                  (HMSS_PERIPH_BASE      + 0x00204400)
#define APCS_APR0_CORE_TM_REG_BASE_OFFS                             0x00204400

#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_ADDR(x)                       ((x) + 0x00000000)
#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_OFFS                          (0x00000000)
#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_RMSK                                 0x1
#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CORE_ADJ_EN_ADDR(x), HWIO_APCS_APR0_TM_CORE_ADJ_EN_RMSK)
#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CORE_ADJ_EN_ADDR(x), m)
#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_CORE_ADJ_EN_ADDR(x),v)
#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_CORE_ADJ_EN_ADDR(x),m,v,HWIO_APCS_APR0_TM_CORE_ADJ_EN_IN(x))
#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_ENABLE_BMSK                          0x1
#define HWIO_APCS_APR0_TM_CORE_ADJ_EN_ENABLE_SHFT                          0x0

#define HWIO_APCS_APR0_TM_CFG_ADDR(x)                               ((x) + 0x00000008)
#define HWIO_APCS_APR0_TM_CFG_OFFS                                  (0x00000008)
#define HWIO_APCS_APR0_TM_CFG_RMSK                                  0xffffff73
#define HWIO_APCS_APR0_TM_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CFG_ADDR(x), HWIO_APCS_APR0_TM_CFG_RMSK)
#define HWIO_APCS_APR0_TM_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CFG_ADDR(x), m)
#define HWIO_APCS_APR0_TM_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_CFG_ADDR(x),v)
#define HWIO_APCS_APR0_TM_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_CFG_ADDR(x),m,v,HWIO_APCS_APR0_TM_CFG_IN(x))
#define HWIO_APCS_APR0_TM_CFG_HYSTERESIS_DN_DLY_BMSK                0xff000000
#define HWIO_APCS_APR0_TM_CFG_HYSTERESIS_DN_DLY_SHFT                      0x18
#define HWIO_APCS_APR0_TM_CFG_HYSTERESIS_UP_DLY_BMSK                  0xff0000
#define HWIO_APCS_APR0_TM_CFG_HYSTERESIS_UP_DLY_SHFT                      0x10
#define HWIO_APCS_APR0_TM_CFG_FORCE_THROTTLE_DLY_BMSK                   0xff00
#define HWIO_APCS_APR0_TM_CFG_FORCE_THROTTLE_DLY_SHFT                      0x8
#define HWIO_APCS_APR0_TM_CFG_FORCE_THROTTLE_4_BOOST_BMSK                 0x40
#define HWIO_APCS_APR0_TM_CFG_FORCE_THROTTLE_4_BOOST_SHFT                  0x6
#define HWIO_APCS_APR0_TM_CFG_FORCE_THROTTLE_4_MARGIN_BMSK                0x20
#define HWIO_APCS_APR0_TM_CFG_FORCE_THROTTLE_4_MARGIN_SHFT                 0x5
#define HWIO_APCS_APR0_TM_CFG_FORCE_WAIT_4_VOLTAGE_BMSK                   0x10
#define HWIO_APCS_APR0_TM_CFG_FORCE_WAIT_4_VOLTAGE_SHFT                    0x4
#define HWIO_APCS_APR0_TM_CFG_MODE_BMSK                                    0x3
#define HWIO_APCS_APR0_TM_CFG_MODE_SHFT                                    0x0

#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_ADDR(x)                       ((x) + 0x00000010)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_OFFS                          (0x00000010)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_RMSK                          0xffffffff
#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_PD_WEIGHT_0_ADDR(x), HWIO_APCS_APR0_TM_PD_WEIGHT_0_RMSK)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_PD_WEIGHT_0_ADDR(x), m)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_PD_WEIGHT_0_ADDR(x),v)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_PD_WEIGHT_0_ADDR(x),m,v,HWIO_APCS_APR0_TM_PD_WEIGHT_0_IN(x))
#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_WEIGHT_BMSK                   0xffffffff
#define HWIO_APCS_APR0_TM_PD_WEIGHT_0_WEIGHT_SHFT                          0x0

#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_ADDR(x)                       ((x) + 0x00000014)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_OFFS                          (0x00000014)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_RMSK                          0xffffffff
#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_PD_WEIGHT_1_ADDR(x), HWIO_APCS_APR0_TM_PD_WEIGHT_1_RMSK)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_PD_WEIGHT_1_ADDR(x), m)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_PD_WEIGHT_1_ADDR(x),v)
#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_PD_WEIGHT_1_ADDR(x),m,v,HWIO_APCS_APR0_TM_PD_WEIGHT_1_IN(x))
#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_WEIGHT_BMSK                   0xffffffff
#define HWIO_APCS_APR0_TM_PD_WEIGHT_1_WEIGHT_SHFT                          0x0

#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_ADDR(x)                    ((x) + 0x00000020)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_OFFS                       (0x00000020)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_RMSK                        0xfffff01
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CAPACITY_LVL_0_ADDR(x), HWIO_APCS_APR0_TM_CAPACITY_LVL_0_RMSK)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CAPACITY_LVL_0_ADDR(x), m)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_CAPACITY_LVL_0_ADDR(x),v)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_CAPACITY_LVL_0_ADDR(x),m,v,HWIO_APCS_APR0_TM_CAPACITY_LVL_0_IN(x))
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_NUM_CORES_BMSK              0xf000000
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_NUM_CORES_SHFT                   0x18
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_MAX_WEIGHT_BMSK              0xff0000
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_MAX_WEIGHT_SHFT                  0x10
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_MIN_WEIGHT_BMSK                0xff00
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_MIN_WEIGHT_SHFT                   0x8
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_VALID_BMSK                        0x1
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_0_VALID_SHFT                        0x0

#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_ADDR(x)                    ((x) + 0x00000024)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_OFFS                       (0x00000024)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_RMSK                        0xfffff01
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CAPACITY_LVL_1_ADDR(x), HWIO_APCS_APR0_TM_CAPACITY_LVL_1_RMSK)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CAPACITY_LVL_1_ADDR(x), m)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_CAPACITY_LVL_1_ADDR(x),v)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_CAPACITY_LVL_1_ADDR(x),m,v,HWIO_APCS_APR0_TM_CAPACITY_LVL_1_IN(x))
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_NUM_CORES_BMSK              0xf000000
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_NUM_CORES_SHFT                   0x18
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_MAX_WEIGHT_BMSK              0xff0000
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_MAX_WEIGHT_SHFT                  0x10
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_MIN_WEIGHT_BMSK                0xff00
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_MIN_WEIGHT_SHFT                   0x8
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_VALID_BMSK                        0x1
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_1_VALID_SHFT                        0x0

#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_ADDR(x)                    ((x) + 0x00000028)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_OFFS                       (0x00000028)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_RMSK                        0xfffff01
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CAPACITY_LVL_2_ADDR(x), HWIO_APCS_APR0_TM_CAPACITY_LVL_2_RMSK)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CAPACITY_LVL_2_ADDR(x), m)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_CAPACITY_LVL_2_ADDR(x),v)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_CAPACITY_LVL_2_ADDR(x),m,v,HWIO_APCS_APR0_TM_CAPACITY_LVL_2_IN(x))
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_NUM_CORES_BMSK              0xf000000
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_NUM_CORES_SHFT                   0x18
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_MAX_WEIGHT_BMSK              0xff0000
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_MAX_WEIGHT_SHFT                  0x10
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_MIN_WEIGHT_BMSK                0xff00
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_MIN_WEIGHT_SHFT                   0x8
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_VALID_BMSK                        0x1
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_2_VALID_SHFT                        0x0

#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_ADDR(x)                    ((x) + 0x0000002c)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_OFFS                       (0x0000002c)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_RMSK                        0xfffff01
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CAPACITY_LVL_3_ADDR(x), HWIO_APCS_APR0_TM_CAPACITY_LVL_3_RMSK)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_CAPACITY_LVL_3_ADDR(x), m)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_CAPACITY_LVL_3_ADDR(x),v)
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_CAPACITY_LVL_3_ADDR(x),m,v,HWIO_APCS_APR0_TM_CAPACITY_LVL_3_IN(x))
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_NUM_CORES_BMSK              0xf000000
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_NUM_CORES_SHFT                   0x18
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_MAX_WEIGHT_BMSK              0xff0000
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_MAX_WEIGHT_SHFT                  0x10
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_MIN_WEIGHT_BMSK                0xff00
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_MIN_WEIGHT_SHFT                   0x8
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_VALID_BMSK                        0x1
#define HWIO_APCS_APR0_TM_CAPACITY_LVL_3_VALID_SHFT                        0x0

#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_ADDR(x)                   ((x) + 0x00000030)
#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_OFFS                      (0x00000030)
#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_RMSK                            0xff
#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_BOOST_THRESHOLD_ADDR(x), HWIO_APCS_APR0_TM_BOOST_THRESHOLD_RMSK)
#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_BOOST_THRESHOLD_ADDR(x), m)
#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_BOOST_THRESHOLD_ADDR(x),v)
#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_BOOST_THRESHOLD_ADDR(x),m,v,HWIO_APCS_APR0_TM_BOOST_THRESHOLD_IN(x))
#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_THRESHOLD_BMSK                  0xff
#define HWIO_APCS_APR0_TM_BOOST_THRESHOLD_THRESHOLD_SHFT                   0x0

#define HWIO_APCS_APR0_TM_THROTTLE_EN_ADDR(x)                       ((x) + 0x00000040)
#define HWIO_APCS_APR0_TM_THROTTLE_EN_OFFS                          (0x00000040)
#define HWIO_APCS_APR0_TM_THROTTLE_EN_RMSK                               0x1ff
#define HWIO_APCS_APR0_TM_THROTTLE_EN_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_THROTTLE_EN_ADDR(x), HWIO_APCS_APR0_TM_THROTTLE_EN_RMSK)
#define HWIO_APCS_APR0_TM_THROTTLE_EN_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_THROTTLE_EN_ADDR(x), m)
#define HWIO_APCS_APR0_TM_THROTTLE_EN_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_THROTTLE_EN_ADDR(x),v)
#define HWIO_APCS_APR0_TM_THROTTLE_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_THROTTLE_EN_ADDR(x),m,v,HWIO_APCS_APR0_TM_THROTTLE_EN_IN(x))
#define HWIO_APCS_APR0_TM_THROTTLE_EN_PD_THROTTLE_EN_BMSK                0x1ff
#define HWIO_APCS_APR0_TM_THROTTLE_EN_PD_THROTTLE_EN_SHFT                  0x0

#define HWIO_APCS_APR0_TM_MARGIN_STS_ADDR(x)                        ((x) + 0x00000080)
#define HWIO_APCS_APR0_TM_MARGIN_STS_OFFS                           (0x00000080)
#define HWIO_APCS_APR0_TM_MARGIN_STS_RMSK                           0xffffffff
#define HWIO_APCS_APR0_TM_MARGIN_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_MARGIN_STS_ADDR(x), HWIO_APCS_APR0_TM_MARGIN_STS_RMSK)
#define HWIO_APCS_APR0_TM_MARGIN_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_MARGIN_STS_ADDR(x), m)
#define HWIO_APCS_APR0_TM_MARGIN_STS_STATUS_BMSK                    0xffffffff
#define HWIO_APCS_APR0_TM_MARGIN_STS_STATUS_SHFT                           0x0

#define HWIO_APCS_APR0_TM_THROTTLE_STS_ADDR(x)                      ((x) + 0x00000088)
#define HWIO_APCS_APR0_TM_THROTTLE_STS_OFFS                         (0x00000088)
#define HWIO_APCS_APR0_TM_THROTTLE_STS_RMSK                         0xffffffff
#define HWIO_APCS_APR0_TM_THROTTLE_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_THROTTLE_STS_ADDR(x), HWIO_APCS_APR0_TM_THROTTLE_STS_RMSK)
#define HWIO_APCS_APR0_TM_THROTTLE_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_THROTTLE_STS_ADDR(x), m)
#define HWIO_APCS_APR0_TM_THROTTLE_STS_STATUS_BMSK                  0xffffffff
#define HWIO_APCS_APR0_TM_THROTTLE_STS_STATUS_SHFT                         0x0

#define HWIO_APCS_APR0_TM_WAR_ADDR(x)                               ((x) + 0x000000c0)
#define HWIO_APCS_APR0_TM_WAR_OFFS                                  (0x000000c0)
#define HWIO_APCS_APR0_TM_WAR_RMSK                                       0x771
#define HWIO_APCS_APR0_TM_WAR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_TM_WAR_ADDR(x), HWIO_APCS_APR0_TM_WAR_RMSK)
#define HWIO_APCS_APR0_TM_WAR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_TM_WAR_ADDR(x), m)
#define HWIO_APCS_APR0_TM_WAR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_TM_WAR_ADDR(x),v)
#define HWIO_APCS_APR0_TM_WAR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_TM_WAR_ADDR(x),m,v,HWIO_APCS_APR0_TM_WAR_IN(x))
#define HWIO_APCS_APR0_TM_WAR_BOOST_FREQ_CLR_BMSK                        0x400
#define HWIO_APCS_APR0_TM_WAR_BOOST_FREQ_CLR_SHFT                          0xa
#define HWIO_APCS_APR0_TM_WAR_MARGIN_FREQ_CLR_BMSK                       0x200
#define HWIO_APCS_APR0_TM_WAR_MARGIN_FREQ_CLR_SHFT                         0x9
#define HWIO_APCS_APR0_TM_WAR_THROTTLE_FREQ_CLR_BMSK                     0x100
#define HWIO_APCS_APR0_TM_WAR_THROTTLE_FREQ_CLR_SHFT                       0x8
#define HWIO_APCS_APR0_TM_WAR_BOOST_FREQ_SET_BMSK                         0x40
#define HWIO_APCS_APR0_TM_WAR_BOOST_FREQ_SET_SHFT                          0x6
#define HWIO_APCS_APR0_TM_WAR_MARGIN_FREQ_SET_BMSK                        0x20
#define HWIO_APCS_APR0_TM_WAR_MARGIN_FREQ_SET_SHFT                         0x5
#define HWIO_APCS_APR0_TM_WAR_THROTTLE_FREQ_SET_BMSK                      0x10
#define HWIO_APCS_APR0_TM_WAR_THROTTLE_FREQ_SET_SHFT                       0x4
#define HWIO_APCS_APR0_TM_WAR_NMM_HW_DISABLE_BMSK                          0x1
#define HWIO_APCS_APR0_TM_WAR_NMM_HW_DISABLE_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_CPM
 *--------------------------------------------------------------------------*/

#define APCS_APC00_CPM_REG_BASE                                             (HMSS_QLL_BASE      + 0x00540000)
#define APCS_APC00_CPM_REG_BASE_OFFS                                        0x00540000

#define HWIO_APCS_APC00_CPM_ACDCR_ADDR(x)                                       ((x) + 0x00000140)
#define HWIO_APCS_APC00_CPM_ACDCR_OFFS                                          (0x00000140)
#define HWIO_APCS_APC00_CPM_ACDCR_RMSK                                          0xffffffff
#define HWIO_APCS_APC00_CPM_ACDCR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ACDCR_ADDR(x), HWIO_APCS_APC00_CPM_ACDCR_RMSK)
#define HWIO_APCS_APC00_CPM_ACDCR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ACDCR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_ACDCR_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_ACDCR_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_ACDCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_ACDCR_ADDR(x),m,v,HWIO_APCS_APC00_CPM_ACDCR_IN(x))
#define HWIO_APCS_APC00_CPM_ACDCR_RES0_0_BMSK                                   0xf8000000
#define HWIO_APCS_APC00_CPM_ACDCR_RES0_0_SHFT                                         0x1b
#define HWIO_APCS_APC00_CPM_ACDCR_CHARMODE_BMSK                                  0x4000000
#define HWIO_APCS_APC00_CPM_ACDCR_CHARMODE_SHFT                                       0x1a
#define HWIO_APCS_APC00_CPM_ACDCR_AUTOCALMGNSIGN_BMSK                            0x2000000
#define HWIO_APCS_APC00_CPM_ACDCR_AUTOCALMGNSIGN_SHFT                                 0x19
#define HWIO_APCS_APC00_CPM_ACDCR_UPDATEAUTOCAL_BMSK                             0x1000000
#define HWIO_APCS_APC00_CPM_ACDCR_UPDATEAUTOCAL_SHFT                                  0x18
#define HWIO_APCS_APC00_CPM_ACDCR_AUTOCALDLY_3_0_BMSK                             0xf00000
#define HWIO_APCS_APC00_CPM_ACDCR_AUTOCALDLY_3_0_SHFT                                 0x14
#define HWIO_APCS_APC00_CPM_ACDCR_HWAUTOCALEN_BMSK                                 0x80000
#define HWIO_APCS_APC00_CPM_ACDCR_HWAUTOCALEN_SHFT                                    0x13
#define HWIO_APCS_APC00_CPM_ACDCR_AUTOCALMGN_2_0_BMSK                              0x70000
#define HWIO_APCS_APC00_CPM_ACDCR_AUTOCALMGN_2_0_SHFT                                 0x10
#define HWIO_APCS_APC00_CPM_ACDCR_PATHTYPESEL_BMSK                                  0x8000
#define HWIO_APCS_APC00_CPM_ACDCR_PATHTYPESEL_SHFT                                     0xf
#define HWIO_APCS_APC00_CPM_ACDCR_DVMEN_BMSK                                        0x4000
#define HWIO_APCS_APC00_CPM_ACDCR_DVMEN_SHFT                                           0xe
#define HWIO_APCS_APC00_CPM_ACDCR_DVMAUTOC_BMSK                                     0x2000
#define HWIO_APCS_APC00_CPM_ACDCR_DVMAUTOC_SHFT                                        0xd
#define HWIO_APCS_APC00_CPM_ACDCR_ACUCNTRST_BMSK                                    0x1000
#define HWIO_APCS_APC00_CPM_ACDCR_ACUCNTRST_SHFT                                       0xc
#define HWIO_APCS_APC00_CPM_ACDCR_ACUTMRCNT_7_0_BMSK                                 0xff0
#define HWIO_APCS_APC00_CPM_ACDCR_ACUTMRCNT_7_0_SHFT                                   0x4
#define HWIO_APCS_APC00_CPM_ACDCR_ACUMODE_1_0_BMSK                                     0xc
#define HWIO_APCS_APC00_CPM_ACDCR_ACUMODE_1_0_SHFT                                     0x2
#define HWIO_APCS_APC00_CPM_ACDCR_ACDOFFLINE_BMSK                                      0x2
#define HWIO_APCS_APC00_CPM_ACDCR_ACDOFFLINE_SHFT                                      0x1
#define HWIO_APCS_APC00_CPM_ACDCR_ACDEN_BMSK                                           0x1
#define HWIO_APCS_APC00_CPM_ACDCR_ACDEN_SHFT                                           0x0

#define HWIO_APCS_APC00_CPM_ACDDVMRC_ADDR(x)                                    ((x) + 0x00000148)
#define HWIO_APCS_APC00_CPM_ACDDVMRC_OFFS                                       (0x00000148)
#define HWIO_APCS_APC00_CPM_ACDDVMRC_RMSK                                       0xffffffff
#define HWIO_APCS_APC00_CPM_ACDDVMRC_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ACDDVMRC_ADDR(x), HWIO_APCS_APC00_CPM_ACDDVMRC_RMSK)
#define HWIO_APCS_APC00_CPM_ACDDVMRC_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ACDDVMRC_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_ACDDVMRC_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_ACDDVMRC_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_ACDDVMRC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_ACDDVMRC_ADDR(x),m,v,HWIO_APCS_APC00_CPM_ACDDVMRC_IN(x))
#define HWIO_APCS_APC00_CPM_ACDDVMRC_RES0_0_BMSK                                0xffe00000
#define HWIO_APCS_APC00_CPM_ACDDVMRC_RES0_0_SHFT                                      0x15
#define HWIO_APCS_APC00_CPM_ACDDVMRC_TDECFG_20_0_BMSK                             0x1fffff
#define HWIO_APCS_APC00_CPM_ACDDVMRC_TDECFG_20_0_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_ACDSSCR_ADDR(x)                                     ((x) + 0x0000014c)
#define HWIO_APCS_APC00_CPM_ACDSSCR_OFFS                                        (0x0000014c)
#define HWIO_APCS_APC00_CPM_ACDSSCR_RMSK                                        0xffffffff
#define HWIO_APCS_APC00_CPM_ACDSSCR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ACDSSCR_ADDR(x), HWIO_APCS_APC00_CPM_ACDSSCR_RMSK)
#define HWIO_APCS_APC00_CPM_ACDSSCR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ACDSSCR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_ACDSSCR_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_ACDSSCR_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_ACDSSCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_ACDSSCR_ADDR(x),m,v,HWIO_APCS_APC00_CPM_ACDSSCR_IN(x))
#define HWIO_APCS_APC00_CPM_ACDSSCR_RES0_0_BMSK                                 0xff000000
#define HWIO_APCS_APC00_CPM_ACDSSCR_RES0_0_SHFT                                       0x18
#define HWIO_APCS_APC00_CPM_ACDSSCR_DIV2TRIPCNT_BMSK                              0xff0000
#define HWIO_APCS_APC00_CPM_ACDSSCR_DIV2TRIPCNT_SHFT                                  0x10
#define HWIO_APCS_APC00_CPM_ACDSSCR_ACUTMRTRIPCNT_BMSK                              0xff00
#define HWIO_APCS_APC00_CPM_ACDSSCR_ACUTMRTRIPCNT_SHFT                                 0x8
#define HWIO_APCS_APC00_CPM_ACDSSCR_RES0_1_BMSK                                       0xfc
#define HWIO_APCS_APC00_CPM_ACDSSCR_RES0_1_SHFT                                        0x2
#define HWIO_APCS_APC00_CPM_ACDSSCR_MODE_BMSK                                          0x3
#define HWIO_APCS_APC00_CPM_ACDSSCR_MODE_SHFT                                          0x0

#define HWIO_APCS_APC00_CPM_ACDTD_ADDR(x)                                       ((x) + 0x00000144)
#define HWIO_APCS_APC00_CPM_ACDTD_OFFS                                          (0x00000144)
#define HWIO_APCS_APC00_CPM_ACDTD_RMSK                                          0xffffffff
#define HWIO_APCS_APC00_CPM_ACDTD_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ACDTD_ADDR(x), HWIO_APCS_APC00_CPM_ACDTD_RMSK)
#define HWIO_APCS_APC00_CPM_ACDTD_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ACDTD_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_ACDTD_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_ACDTD_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_ACDTD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_ACDTD_ADDR(x),m,v,HWIO_APCS_APC00_CPM_ACDTD_IN(x))
#define HWIO_APCS_APC00_CPM_ACDTD_RES0_0_BMSK                                   0xff800000
#define HWIO_APCS_APC00_CPM_ACDTD_RES0_0_SHFT                                         0x17
#define HWIO_APCS_APC00_CPM_ACDTD_RC2TDECFG_2_0_BMSK                              0x700000
#define HWIO_APCS_APC00_CPM_ACDTD_RC2TDECFG_2_0_SHFT                                  0x14
#define HWIO_APCS_APC00_CPM_ACDTD_RES0_1_BMSK                                      0x80000
#define HWIO_APCS_APC00_CPM_ACDTD_RES0_1_SHFT                                         0x13
#define HWIO_APCS_APC00_CPM_ACDTD_RC1TDECFG_2_0_BMSK                               0x70000
#define HWIO_APCS_APC00_CPM_ACDTD_RC1TDECFG_2_0_SHFT                                  0x10
#define HWIO_APCS_APC00_CPM_ACDTD_XTRTDECFG_7_0_BMSK                                0xff00
#define HWIO_APCS_APC00_CPM_ACDTD_XTRTDECFG_7_0_SHFT                                   0x8
#define HWIO_APCS_APC00_CPM_ACDTD_RES0_2_BMSK                                         0xe0
#define HWIO_APCS_APC00_CPM_ACDTD_RES0_2_SHFT                                          0x5
#define HWIO_APCS_APC00_CPM_ACDTD_XTRTDEEN_BMSK                                       0x10
#define HWIO_APCS_APC00_CPM_ACDTD_XTRTDEEN_SHFT                                        0x4
#define HWIO_APCS_APC00_CPM_ACDTD_RC2TDEEN_BMSK                                        0x8
#define HWIO_APCS_APC00_CPM_ACDTD_RC2TDEEN_SHFT                                        0x3
#define HWIO_APCS_APC00_CPM_ACDTD_RC1TDEEN_BMSK                                        0x4
#define HWIO_APCS_APC00_CPM_ACDTD_RC1TDEEN_SHFT                                        0x2
#define HWIO_APCS_APC00_CPM_ACDTD_MODE_1_0_BMSK                                        0x3
#define HWIO_APCS_APC00_CPM_ACDTD_MODE_1_0_SHFT                                        0x0

#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_ADDR(x)                                 ((x) + 0x00000100)
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_OFFS                                    (0x00000100)
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_RMSK                                    0xffffffff
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ALT_CLK_CTL_ADDR(x), HWIO_APCS_APC00_CPM_ALT_CLK_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_ALT_CLK_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_ALT_CLK_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_ALT_CLK_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_ALT_CLK_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_RES0_0_BMSK                             0xfc000000
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_RES0_0_SHFT                                   0x1a
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_OSC_PROG_BMSK                            0x3ff0000
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_OSC_PROG_SHFT                                 0x10
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_RES0_1_BMSK                                 0xffc0
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_RES0_1_SHFT                                    0x6
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_AVAIL_DLY_BMSK                                0x30
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_AVAIL_DLY_SHFT                                 0x4
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_RES0_2_BMSK                                    0xe
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_RES0_2_SHFT                                    0x1
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_ALTCLKEN_BMSK                                  0x1
#define HWIO_APCS_APC00_CPM_ALT_CLK_CTL_ALTCLKEN_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_AUX_CBCR_ADDR(x)                                    ((x) + 0x0000004c)
#define HWIO_APCS_APC00_CPM_AUX_CBCR_OFFS                                       (0x0000004c)
#define HWIO_APCS_APC00_CPM_AUX_CBCR_RMSK                                       0xffffffff
#define HWIO_APCS_APC00_CPM_AUX_CBCR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AUX_CBCR_ADDR(x), HWIO_APCS_APC00_CPM_AUX_CBCR_RMSK)
#define HWIO_APCS_APC00_CPM_AUX_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AUX_CBCR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_AUX_CBCR_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_AUX_CBCR_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_AUX_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_AUX_CBCR_ADDR(x),m,v,HWIO_APCS_APC00_CPM_AUX_CBCR_IN(x))
#define HWIO_APCS_APC00_CPM_AUX_CBCR_RES0_0_BMSK                                0xfffc0000
#define HWIO_APCS_APC00_CPM_AUX_CBCR_RES0_0_SHFT                                      0x12
#define HWIO_APCS_APC00_CPM_AUX_CBCR_CLK_DIV_1_0_BMSK                              0x30000
#define HWIO_APCS_APC00_CPM_AUX_CBCR_CLK_DIV_1_0_SHFT                                 0x10
#define HWIO_APCS_APC00_CPM_AUX_CBCR_RES0_1_BMSK                                    0xfffc
#define HWIO_APCS_APC00_CPM_AUX_CBCR_RES0_1_SHFT                                       0x2
#define HWIO_APCS_APC00_CPM_AUX_CBCR_HW_CTL_BMSK                                       0x2
#define HWIO_APCS_APC00_CPM_AUX_CBCR_HW_CTL_SHFT                                       0x1
#define HWIO_APCS_APC00_CPM_AUX_CBCR_SW_CTL_BMSK                                       0x1
#define HWIO_APCS_APC00_CPM_AUX_CBCR_SW_CTL_SHFT                                       0x0

#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_ADDR(x)                                 ((x) + 0x0000034c)
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_OFFS                                    (0x0000034c)
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_RMSK                                    0xffffffff
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_BNC_LMT_ADDR(x), HWIO_APCS_APC00_CPM_AVM_BNC_LMT_RMSK)
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_BNC_LMT_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_AVM_BNC_LMT_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_AVM_BNC_LMT_ADDR(x),m,v,HWIO_APCS_APC00_CPM_AVM_BNC_LMT_IN(x))
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_VTM_BOUNCE_BMSK                         0x80000000
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_VTM_BOUNCE_SHFT                               0x1f
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_RES0_0_BMSK                             0x7fffff00
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_RES0_0_SHFT                                    0x8
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_BOUNCE_LIMIT_BMSK                             0xff
#define HWIO_APCS_APC00_CPM_AVM_BNC_LMT_BOUNCE_LIMIT_SHFT                              0x0

#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_ADDR(x)                                 ((x) + 0x00000350)
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_OFFS                                    (0x00000350)
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_RMSK                                    0xffffffff
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_CNT0_TR_ADDR(x), HWIO_APCS_APC00_CPM_AVM_CNT0_TR_RMSK)
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_CNT0_TR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_AVM_CNT0_TR_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_AVM_CNT0_TR_ADDR(x),m,v,HWIO_APCS_APC00_CPM_AVM_CNT0_TR_IN(x))
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_THCNT_DN_BMSK                           0xffff0000
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_THCNT_DN_SHFT                                 0x10
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_THCNT_UP_BMSK                               0xffff
#define HWIO_APCS_APC00_CPM_AVM_CNT0_TR_THCNT_UP_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_ADDR(x)                                 ((x) + 0x00000354)
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_OFFS                                    (0x00000354)
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_RMSK                                    0xffffffff
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_CNT1_TR_ADDR(x), HWIO_APCS_APC00_CPM_AVM_CNT1_TR_RMSK)
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_CNT1_TR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_AVM_CNT1_TR_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_AVM_CNT1_TR_ADDR(x),m,v,HWIO_APCS_APC00_CPM_AVM_CNT1_TR_IN(x))
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_THCNT_DN_BMSK                           0xffff0000
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_THCNT_DN_SHFT                                 0x10
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_THCNT_UP_BMSK                               0xffff
#define HWIO_APCS_APC00_CPM_AVM_CNT1_TR_THCNT_UP_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_AVM_CTL_ADDR(x)                                     ((x) + 0x00000340)
#define HWIO_APCS_APC00_CPM_AVM_CTL_OFFS                                        (0x00000340)
#define HWIO_APCS_APC00_CPM_AVM_CTL_RMSK                                        0xffffffff
#define HWIO_APCS_APC00_CPM_AVM_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_CTL_ADDR(x), HWIO_APCS_APC00_CPM_AVM_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_AVM_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_AVM_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_AVM_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_AVM_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_AVM_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_AVM_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_AVM_CTL_AVM_TMR_CNT_BMSK                            0xff000000
#define HWIO_APCS_APC00_CPM_AVM_CTL_AVM_TMR_CNT_SHFT                                  0x18
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT1_PRD_BMSK                                 0xff0000
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT1_PRD_SHFT                                     0x10
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT0_PRD_BMSK                                   0xff00
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT0_PRD_SHFT                                      0x8
#define HWIO_APCS_APC00_CPM_AVM_CTL_RES0_0_BMSK                                       0x80
#define HWIO_APCS_APC00_CPM_AVM_CTL_RES0_0_SHFT                                        0x7
#define HWIO_APCS_APC00_CPM_AVM_CTL_VADJ_ONLY_MODE_BMSK                               0x40
#define HWIO_APCS_APC00_CPM_AVM_CTL_VADJ_ONLY_MODE_SHFT                                0x6
#define HWIO_APCS_APC00_CPM_AVM_CTL_VTM_EN_BMSK                                       0x20
#define HWIO_APCS_APC00_CPM_AVM_CTL_VTM_EN_SHFT                                        0x5
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT1_DNTH_EN_BMSK                                 0x10
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT1_DNTH_EN_SHFT                                  0x4
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT1_UPTH_EN_BMSK                                  0x8
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT1_UPTH_EN_SHFT                                  0x3
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT0_DNTH_EN_BMSK                                  0x4
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT0_DNTH_EN_SHFT                                  0x2
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT0_UPTH_EN_BMSK                                  0x2
#define HWIO_APCS_APC00_CPM_AVM_CTL_CNT0_UPTH_EN_SHFT                                  0x1
#define HWIO_APCS_APC00_CPM_AVM_CTL_AVM_EN_BMSK                                        0x1
#define HWIO_APCS_APC00_CPM_AVM_CTL_AVM_EN_SHFT                                        0x0

#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_ADDR(x)                                 ((x) + 0x00000348)
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_OFFS                                    (0x00000348)
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_RMSK                                    0xffffffff
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_DRP_LMT_ADDR(x), HWIO_APCS_APC00_CPM_AVM_DRP_LMT_RMSK)
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_DRP_LMT_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_AVM_DRP_LMT_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_AVM_DRP_LMT_ADDR(x),m,v,HWIO_APCS_APC00_CPM_AVM_DRP_LMT_IN(x))
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_RES0_0_BMSK                             0xffffff00
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_RES0_0_SHFT                                    0x8
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_DROOP_LIMIT_BMSK                              0xff
#define HWIO_APCS_APC00_CPM_AVM_DRP_LMT_DROOP_LIMIT_SHFT                               0x0

#define HWIO_APCS_APC00_CPM_AVM_TRM_ADDR(x)                                     ((x) + 0x00000344)
#define HWIO_APCS_APC00_CPM_AVM_TRM_OFFS                                        (0x00000344)
#define HWIO_APCS_APC00_CPM_AVM_TRM_RMSK                                        0xffffffff
#define HWIO_APCS_APC00_CPM_AVM_TRM_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_TRM_ADDR(x), HWIO_APCS_APC00_CPM_AVM_TRM_RMSK)
#define HWIO_APCS_APC00_CPM_AVM_TRM_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_TRM_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_AVM_TRM_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_AVM_TRM_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_AVM_TRM_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_AVM_TRM_ADDR(x),m,v,HWIO_APCS_APC00_CPM_AVM_TRM_IN(x))
#define HWIO_APCS_APC00_CPM_AVM_TRM_RES0_0_BMSK                                 0xfffff000
#define HWIO_APCS_APC00_CPM_AVM_TRM_RES0_0_SHFT                                        0xc
#define HWIO_APCS_APC00_CPM_AVM_TRM_BNC_DAC_TRM_BMSK                                 0xf00
#define HWIO_APCS_APC00_CPM_AVM_TRM_BNC_DAC_TRM_SHFT                                   0x8
#define HWIO_APCS_APC00_CPM_AVM_TRM_RES0_1_BMSK                                       0xf0
#define HWIO_APCS_APC00_CPM_AVM_TRM_RES0_1_SHFT                                        0x4
#define HWIO_APCS_APC00_CPM_AVM_TRM_DRP_DAC_TRM_BMSK                                   0xf
#define HWIO_APCS_APC00_CPM_AVM_TRM_DRP_DAC_TRM_SHFT                                   0x0

#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ADDR(x)                                 ((x) + 0x00000358)
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_OFFS                                    (0x00000358)
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_RMSK                                    0xffffffff
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ADDR(x), HWIO_APCS_APC00_CPM_AVM_VTM_CFG_RMSK)
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ADDR(x),m,v,HWIO_APCS_APC00_CPM_AVM_VTM_CFG_IN(x))
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ATEST_SEL_BMSK                          0xf0000000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ATEST_SEL_SHFT                                0x1c
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_VHYST_BMSK                               0xf000000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_VHYST_SHFT                                    0x18
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ATEST1EN_BMSK                             0x800000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ATEST1EN_SHFT                                 0x17
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ATEST0EN_BMSK                             0x400000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_ATEST0EN_SHFT                                 0x16
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BYPBNCCAP_BMSK                            0x200000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BYPBNCCAP_SHFT                                0x15
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_CFGBNCLPF_BMSK                            0x1c0000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_CFGBNCLPF_SHFT                                0x12
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASBNC_BMSK                               0x30000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASBNC_SHFT                                  0x10
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BYPL2DRPCAP_BMSK                            0x8000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BYPL2DRPCAP_SHFT                               0xf
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_CFGL2DRPLPF_BMSK                            0x7000
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_CFGL2DRPLPF_SHFT                               0xc
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BYPCPUDRPCAP_BMSK                            0x800
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BYPCPUDRPCAP_SHFT                              0xb
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_CFGCPUDRPLPF_BMSK                            0x700
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_CFGCPUDRPLPF_SHFT                              0x8
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_DRPCMPSEL_BMSK                                0x80
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_DRPCMPSEL_SHFT                                 0x7
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_DRPCMPHYSTEN_BMSK                             0x40
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_DRPCMPHYSTEN_SHFT                              0x6
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASENDRPH_BMSK                               0x20
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASENDRPH_SHFT                                0x5
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASDRPH_BMSK                                 0x18
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASDRPH_SHFT                                  0x3
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASENDRPL_BMSK                                0x4
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASENDRPL_SHFT                                0x2
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASDRPL_BMSK                                  0x3
#define HWIO_APCS_APC00_CPM_AVM_VTM_CFG_BIASDRPL_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_CLKCR_ADDR(x)                                       ((x) + 0x00000044)
#define HWIO_APCS_APC00_CPM_CLKCR_OFFS                                          (0x00000044)
#define HWIO_APCS_APC00_CPM_CLKCR_RMSK                                          0xffffffff
#define HWIO_APCS_APC00_CPM_CLKCR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CLKCR_ADDR(x), HWIO_APCS_APC00_CPM_CLKCR_RMSK)
#define HWIO_APCS_APC00_CPM_CLKCR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CLKCR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_CLKCR_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_CLKCR_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_CLKCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_CLKCR_ADDR(x),m,v,HWIO_APCS_APC00_CPM_CLKCR_IN(x))
#define HWIO_APCS_APC00_CPM_CLKCR_RES0_0_BMSK                                   0xfff80000
#define HWIO_APCS_APC00_CPM_CLKCR_RES0_0_SHFT                                         0x13
#define HWIO_APCS_APC00_CPM_CLKCR_QSBTXWUDLY_2_0_BMSK                              0x70000
#define HWIO_APCS_APC00_CPM_CLKCR_QSBTXWUDLY_2_0_SHFT                                 0x10
#define HWIO_APCS_APC00_CPM_CLKCR_QSBTXSLPDLY_1_0_BMSK                              0xc000
#define HWIO_APCS_APC00_CPM_CLKCR_QSBTXSLPDLY_1_0_SHFT                                 0xe
#define HWIO_APCS_APC00_CPM_CLKCR_QSBACGDLY_1_0_BMSK                                0x3000
#define HWIO_APCS_APC00_CPM_CLKCR_QSBACGDLY_1_0_SHFT                                   0xc
#define HWIO_APCS_APC00_CPM_CLKCR_SRBRDADJ_BMSK                                      0xc00
#define HWIO_APCS_APC00_CPM_CLKCR_SRBRDADJ_SHFT                                        0xa
#define HWIO_APCS_APC00_CPM_CLKCR_TBD_0_BMSK                                         0x200
#define HWIO_APCS_APC00_CPM_CLKCR_TBD_0_SHFT                                           0x9
#define HWIO_APCS_APC00_CPM_CLKCR_ACLKSELEN_BMSK                                     0x100
#define HWIO_APCS_APC00_CPM_CLKCR_ACLKSELEN_SHFT                                       0x8
#define HWIO_APCS_APC00_CPM_CLKCR_RES0_1_BMSK                                         0x80
#define HWIO_APCS_APC00_CPM_CLKCR_RES0_1_SHFT                                          0x7
#define HWIO_APCS_APC00_CPM_CLKCR_EL2CLKAG_BMSK                                       0x40
#define HWIO_APCS_APC00_CPM_CLKCR_EL2CLKAG_SHFT                                        0x6
#define HWIO_APCS_APC00_CPM_CLKCR_ECPU1CLKAG_BMSK                                     0x20
#define HWIO_APCS_APC00_CPM_CLKCR_ECPU1CLKAG_SHFT                                      0x5
#define HWIO_APCS_APC00_CPM_CLKCR_ECPU0CLKAG_BMSK                                     0x10
#define HWIO_APCS_APC00_CPM_CLKCR_ECPU0CLKAG_SHFT                                      0x4
#define HWIO_APCS_APC00_CPM_CLKCR_RES0_2_BMSK                                          0xc
#define HWIO_APCS_APC00_CPM_CLKCR_RES0_2_SHFT                                          0x2
#define HWIO_APCS_APC00_CPM_CLKCR_EQSBACG_BMSK                                         0x2
#define HWIO_APCS_APC00_CPM_CLKCR_EQSBACG_SHFT                                         0x1
#define HWIO_APCS_APC00_CPM_CLKCR_EPRICLKAG_BMSK                                       0x1
#define HWIO_APCS_APC00_CPM_CLKCR_EPRICLKAG_SHFT                                       0x0

#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_ADDR(x)                            ((x) + 0x00000168)
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_OFFS                               (0x00000168)
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_RMSK                               0xffffffff
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_ADDR(x), HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_RES0_0_BMSK                        0xfffffe00
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_RES0_0_SHFT                               0x9
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_FAIC_CLKHALT_EN_BMSK                    0x100
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_FAIC_CLKHALT_EN_SHFT                      0x8
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_FAIC_CTR_3_0_BMSK                        0xf0
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_FAIC_CTR_3_0_SHFT                         0x4
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_RES0_1_BMSK                               0xc
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_RES0_1_SHFT                               0x2
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_FAIC_CLK_MULT_1_0_BMSK                    0x3
#define HWIO_APCS_APC00_CPM_CLKHALT_EXIT_CTL_FAIC_CLK_MULT_1_0_SHFT                    0x0

#define HWIO_APCS_APC00_CPM_CLKSEL_ADDR(x)                                      ((x) + 0x00000040)
#define HWIO_APCS_APC00_CPM_CLKSEL_OFFS                                         (0x00000040)
#define HWIO_APCS_APC00_CPM_CLKSEL_RMSK                                         0xffffffff
#define HWIO_APCS_APC00_CPM_CLKSEL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CLKSEL_ADDR(x), HWIO_APCS_APC00_CPM_CLKSEL_RMSK)
#define HWIO_APCS_APC00_CPM_CLKSEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CLKSEL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_CLKSEL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_CLKSEL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_CLKSEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_CLKSEL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_CLKSEL_IN(x))
#define HWIO_APCS_APC00_CPM_CLKSEL_RES0_0_BMSK                                  0xfffff000
#define HWIO_APCS_APC00_CPM_CLKSEL_RES0_0_SHFT                                         0xc
#define HWIO_APCS_APC00_CPM_CLKSEL_ALTSECSRCSEL_1_0_BMSK                             0xc00
#define HWIO_APCS_APC00_CPM_CLKSEL_ALTSECSRCSEL_1_0_SHFT                               0xa
#define HWIO_APCS_APC00_CPM_CLKSEL_ALTPRISRCSEL_1_0_BMSK                             0x300
#define HWIO_APCS_APC00_CPM_CLKSEL_ALTPRISRCSEL_1_0_SHFT                               0x8
#define HWIO_APCS_APC00_CPM_CLKSEL_TBD_0_BMSK                                         0x80
#define HWIO_APCS_APC00_CPM_CLKSEL_TBD_0_SHFT                                          0x7
#define HWIO_APCS_APC00_CPM_CLKSEL_REDUCEFREQ_BMSK                                    0x40
#define HWIO_APCS_APC00_CPM_CLKSEL_REDUCEFREQ_SHFT                                     0x6
#define HWIO_APCS_APC00_CPM_CLKSEL_ACLKSELAONCLK_1_0_BMSK                             0x30
#define HWIO_APCS_APC00_CPM_CLKSEL_ACLKSELAONCLK_1_0_SHFT                              0x4
#define HWIO_APCS_APC00_CPM_CLKSEL_SECSRCSEL_1_0_BMSK                                  0xc
#define HWIO_APCS_APC00_CPM_CLKSEL_SECSRCSEL_1_0_SHFT                                  0x2
#define HWIO_APCS_APC00_CPM_CLKSEL_PRISRCSEL_1_0_BMSK                                  0x3
#define HWIO_APCS_APC00_CPM_CLKSEL_PRISRCSEL_1_0_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_CLKSR_ADDR(x)                                       ((x) + 0x00000068)
#define HWIO_APCS_APC00_CPM_CLKSR_OFFS                                          (0x00000068)
#define HWIO_APCS_APC00_CPM_CLKSR_RMSK                                          0xffffffff
#define HWIO_APCS_APC00_CPM_CLKSR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CLKSR_ADDR(x), HWIO_APCS_APC00_CPM_CLKSR_RMSK)
#define HWIO_APCS_APC00_CPM_CLKSR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CLKSR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_CLKSR_ACSSGFMS_BMSK                                 0xc0000000
#define HWIO_APCS_APC00_CPM_CLKSR_ACSSGFMS_SHFT                                       0x1e
#define HWIO_APCS_APC00_CPM_CLKSR_ACSPGFMS_BMSK                                 0x30000000
#define HWIO_APCS_APC00_CPM_CLKSR_ACSPGFMS_SHFT                                       0x1c
#define HWIO_APCS_APC00_CPM_CLKSR_RES0_0_BMSK                                    0xc000000
#define HWIO_APCS_APC00_CPM_CLKSR_RES0_0_SHFT                                         0x1a
#define HWIO_APCS_APC00_CPM_CLKSR_CLK_SW_IDLE_BMSK                               0x2000000
#define HWIO_APCS_APC00_CPM_CLKSR_CLK_SW_IDLE_SHFT                                    0x19
#define HWIO_APCS_APC00_CPM_CLKSR_ALT_CLK_AVAIL_BMSK                             0x1000000
#define HWIO_APCS_APC00_CPM_CLKSR_ALT_CLK_AVAIL_SHFT                                  0x18
#define HWIO_APCS_APC00_CPM_CLKSR_SGFMOS_BMSK                                     0xc00000
#define HWIO_APCS_APC00_CPM_CLKSR_SGFMOS_SHFT                                         0x16
#define HWIO_APCS_APC00_CPM_CLKSR_PGFMOS_BMSK                                     0x300000
#define HWIO_APCS_APC00_CPM_CLKSR_PGFMOS_SHFT                                         0x14
#define HWIO_APCS_APC00_CPM_CLKSR_SGFMIS_BMSK                                      0xc0000
#define HWIO_APCS_APC00_CPM_CLKSR_SGFMIS_SHFT                                         0x12
#define HWIO_APCS_APC00_CPM_CLKSR_PGFMIS_BMSK                                      0x30000
#define HWIO_APCS_APC00_CPM_CLKSR_PGFMIS_SHFT                                         0x10
#define HWIO_APCS_APC00_CPM_CLKSR_PCSMSGFMS_BMSK                                    0xc000
#define HWIO_APCS_APC00_CPM_CLKSR_PCSMSGFMS_SHFT                                       0xe
#define HWIO_APCS_APC00_CPM_CLKSR_PCSMPGFMS_BMSK                                    0x3000
#define HWIO_APCS_APC00_CPM_CLKSR_PCSMPGFMS_SHFT                                       0xc
#define HWIO_APCS_APC00_CPM_CLKSR_RES0_1_BMSK                                        0xfff
#define HWIO_APCS_APC00_CPM_CLKSR_RES0_1_SHFT                                          0x0

#define HWIO_APCS_APC00_CPM_CPM_SPARE0_ADDR(x)                                  ((x) + 0x00000078)
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_OFFS                                     (0x00000078)
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_RMSK                                     0xffffffff
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CPM_SPARE0_ADDR(x), HWIO_APCS_APC00_CPM_CPM_SPARE0_RMSK)
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CPM_SPARE0_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_CPM_SPARE0_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_CPM_SPARE0_ADDR(x),m,v,HWIO_APCS_APC00_CPM_CPM_SPARE0_IN(x))
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_RES0_0_BMSK                              0xffffff00
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_RES0_0_SHFT                                     0x8
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_TBD_0_BMSK                                     0xff
#define HWIO_APCS_APC00_CPM_CPM_SPARE0_TBD_0_SHFT                                      0x0

#define HWIO_APCS_APC00_CPM_CPM_SPARE1_ADDR(x)                                  ((x) + 0x0000007c)
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_OFFS                                     (0x0000007c)
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_RMSK                                     0xffffffff
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CPM_SPARE1_ADDR(x), HWIO_APCS_APC00_CPM_CPM_SPARE1_RMSK)
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CPM_SPARE1_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_CPM_SPARE1_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_CPM_SPARE1_ADDR(x),m,v,HWIO_APCS_APC00_CPM_CPM_SPARE1_IN(x))
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_RES0_0_BMSK                              0xffffff00
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_RES0_0_SHFT                                     0x8
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_TBD_0_BMSK                                     0xff
#define HWIO_APCS_APC00_CPM_CPM_SPARE1_TBD_0_SHFT                                      0x0

#define HWIO_APCS_APC00_CPM_CPM_SPARE2_ADDR(x)                                  ((x) + 0x00000210)
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_OFFS                                     (0x00000210)
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_RMSK                                     0xffffffff
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CPM_SPARE2_ADDR(x), HWIO_APCS_APC00_CPM_CPM_SPARE2_RMSK)
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_CPM_SPARE2_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_CPM_SPARE2_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_CPM_SPARE2_ADDR(x),m,v,HWIO_APCS_APC00_CPM_CPM_SPARE2_IN(x))
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_RES0_0_BMSK                              0xffffff00
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_RES0_0_SHFT                                     0x8
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_TBD_0_BMSK                                     0xff
#define HWIO_APCS_APC00_CPM_CPM_SPARE2_TBD_0_SHFT                                      0x0

#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_ADDR(x)                               ((x) + 0x00000300)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_OFFS                                  (0x00000300)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_RMSK                                  0xffffffff
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_ADDR(x), HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_RES0_0_BMSK                           0xfff80000
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_RES0_0_SHFT                                 0x13
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_PRD_CNT_BMSK                             0x70000
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_PRD_CNT_SHFT                                0x10
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_EC1_SEL_BMSK                              0xf000
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_EC1_SEL_SHFT                                 0xc
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_EC0_SEL_BMSK                               0xf00
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_EC0_SEL_SHFT                                 0x8
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_RES0_1_BMSK                                 0x80
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_RES0_1_SHFT                                  0x7
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_FCC_SEL_BMSK                                0x70
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_FCC_SEL_SHFT                                 0x4
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_RES0_2_BMSK                                  0xc
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_RES0_2_SHFT                                  0x2
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_EC1_EN_BMSK                                  0x2
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_EC1_EN_SHFT                                  0x1
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_EC0_EN_BMSK                                  0x1
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_CTL_EC0_EN_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_ADDR(x)                        ((x) + 0x00000308)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_OFFS                           (0x00000308)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_RMSK                           0xffffffff
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_ADDR(x), HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_RMSK)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_EVNT_CNT_BMSK                  0xffffffff
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR0_EVNT_CNT_SHFT                         0x0

#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_ADDR(x)                        ((x) + 0x0000030c)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_OFFS                           (0x0000030c)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_RMSK                           0xffffffff
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_ADDR(x), HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_RMSK)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_EVNT_CNT_BMSK                  0xffffffff
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_EVNT_CNTR1_EVNT_CNT_SHFT                         0x0

#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_ADDR(x)                          ((x) + 0x00000304)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_OFFS                             (0x00000304)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_RMSK                             0xffffffff
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_ADDR(x), HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_RMSK)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_ADDR(x),m,v,HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_IN(x))
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_RES0_0_BMSK                      0xfffffffe
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_RES0_0_SHFT                             0x1
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_START_BMSK                              0x1
#define HWIO_APCS_APC00_CPM_DIAG_CNTR_STRT_CMD_START_SHFT                              0x0

#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_ADDR(x)                             ((x) + 0x00000048)
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_OFFS                                (0x00000048)
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_RMSK                                0xffffffff
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_ADDR(x), HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_RES0_0_BMSK                         0xfffff000
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_RES0_0_SHFT                                0xc
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TBD_0_BMSK                               0x800
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TBD_0_SHFT                                 0xb
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TBD_1_BMSK                               0x400
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TBD_1_SHFT                                 0xa
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TBD_2_BMSK                               0x200
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TBD_2_SHFT                                 0x9
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_LEAFCLKEN_BMSK                           0x100
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_LEAFCLKEN_SHFT                             0x8
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_RES0_1_BMSK                               0x80
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_RES0_1_SHFT                                0x7
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TESTCLK_SEL_2_0_BMSK                      0x70
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TESTCLK_SEL_2_0_SHFT                       0x4
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_DTEST_SEL_1_0_BMSK                         0xc
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_DTEST_SEL_1_0_SHFT                         0x2
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TESTBUS_SEL_1_0_BMSK                       0x3
#define HWIO_APCS_APC00_CPM_DIAG_OUTPUT_CTL_TESTBUS_SEL_1_0_SHFT                       0x0

#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_ADDR(x)                                 ((x) + 0x00000058)
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_OFFS                                    (0x00000058)
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_RMSK                                    0xffffffff
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_HW_DCVS_CTL_ADDR(x), HWIO_APCS_APC00_CPM_HW_DCVS_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_HW_DCVS_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_HW_DCVS_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_HW_DCVS_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_HW_DCVS_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_RES0_0_BMSK                             0xfff80000
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_RES0_0_SHFT                                   0x13
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_UNLOCK_CNT_2_0_BMSK                        0x70000
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_UNLOCK_CNT_2_0_SHFT                           0x10
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_RES0_1_BMSK                                 0xc000
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_RES0_1_SHFT                                    0xe
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_LOCK_CNT_5_0_BMSK                           0x3f00
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_LOCK_CNT_5_0_SHFT                              0x8
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_RES0_2_BMSK                                   0xf0
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_RES0_2_SHFT                                    0x4
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_PLLDYNPROGDIS_BMSK                             0x8
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_PLLDYNPROGDIS_SHFT                             0x3
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_FRC_CPM_ARACK_BMSK                             0x4
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_FRC_CPM_ARACK_SHFT                             0x2
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_FRC_LVAL_UPDATE_BMSK                           0x2
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_FRC_LVAL_UPDATE_SHFT                           0x1
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_HWDCVSEN_BMSK                                  0x1
#define HWIO_APCS_APC00_CPM_HW_DCVS_CTL_HWDCVSEN_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_ADDR(x)                               ((x) + 0x00000178)
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_OFFS                                  (0x00000178)
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_RMSK                                  0xffffffff
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_ADDR(x), HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_L4TR_3_0_BMSK                         0xf0000000
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_L4TR_3_0_SHFT                               0x1c
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_L3TR_3_0_BMSK                          0xf000000
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_L3TR_3_0_SHFT                               0x18
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_L2TR_3_0_BMSK                           0xf00000
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_L2TR_3_0_SHFT                               0x14
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_L1TR_3_0_BMSK                            0xf0000
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_L1TR_3_0_SHFT                               0x10
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_RES0_0_BMSK                               0xfffe
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_RES0_0_SHFT                                  0x1
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_TEN_BMSK                                     0x1
#define HWIO_APCS_APC00_CPM_LM_THRTTL_CTL_TEN_SHFT                                     0x0

#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_ADDR(x)                                  ((x) + 0x00000050)
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OFFS                                     (0x00000050)
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_RMSK                                     0xffffffff
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_OVR_CLKSEL_ADDR(x), HWIO_APCS_APC00_CPM_OVR_CLKSEL_RMSK)
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_OVR_CLKSEL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_OVR_CLKSEL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_OVR_CLKSEL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_OVR_CLKSEL_IN(x))
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_RES0_0_BMSK                              0xffffff00
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_RES0_0_SHFT                                     0x8
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OVRSEL_BMSK                                    0x80
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OVRSEL_SHFT                                     0x7
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_RES0_1_BMSK                                    0x70
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_RES0_1_SHFT                                     0x4
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OVRSECSRCSEL_BMSK                               0xc
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OVRSECSRCSEL_SHFT                               0x2
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OVRPRISRCSEL_BMSK                               0x3
#define HWIO_APCS_APC00_CPM_OVR_CLKSEL_OVRPRISRCSEL_SHFT                               0x0

#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_ADDR(x)                               ((x) + 0x00000008)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_OFFS                                  (0x00000008)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_RMSK                                  0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_ADDR(x), HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_RES0_0_BMSK                           0xffff0000
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_RES0_0_SHFT                                 0x10
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_ALPHA_VAL_15_0_BMSK                       0xffff
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_ALPHA_VAL_15_0_SHFT                          0x0

#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_ADDR(x)                        ((x) + 0x00000108)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_OFFS                           (0x00000108)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_RMSK                           0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_ADDR(x), HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_RES0_0_BMSK                    0xffff0000
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_RES0_0_SHFT                          0x10
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_ALPHA_VAL_15_0_BMSK                0xffff
#define HWIO_APCS_APC00_CPM_PLL_ALPHA_VAL_STATUS_ALPHA_VAL_15_0_SHFT                   0x0

#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_ADDR(x)                                ((x) + 0x00000054)
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_OFFS                                   (0x00000054)
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_RMSK                                   0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_BIST_CTL_ADDR(x), HWIO_APCS_APC00_CPM_PLL_BIST_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_BIST_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_BIST_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_BIST_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_BIST_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_RES0_0_BMSK                            0xfffff000
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_RES0_0_SHFT                                   0xc
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_BIST_CTL_11_0_BMSK                          0xfff
#define HWIO_APCS_APC00_CPM_PLL_BIST_CTL_BIST_CTL_11_0_SHFT                            0x0

#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_ADDR(x)                           ((x) + 0x0000001c)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_OFFS                              (0x0000001c)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_RMSK                              0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_ADDR(x), HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_CFG_CTL_HI_31_0_BMSK              0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_HI_CFG_CTL_HI_31_0_SHFT                     0x0

#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_ADDR(x)                           ((x) + 0x00000018)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_OFFS                              (0x00000018)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_RMSK                              0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_ADDR(x), HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_CFG_CTL_LO_31_0_BMSK              0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_CONFIG_CTL_LO_CFG_CTL_LO_31_0_SHFT                     0x0

#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_ADDR(x)                              ((x) + 0x00000064)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_OFFS                                 (0x00000064)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_RMSK                                 0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_ADDR(x), HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_RES0_0_BMSK                          0xffffff00
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_RES0_0_SHFT                                 0x8
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_L_VAL_BMSK                                 0xff
#define HWIO_APCS_APC00_CPM_PLL_LVAL_BOOST_L_VAL_SHFT                                  0x0

#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_ADDR(x)                           ((x) + 0x00000060)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_OFFS                              (0x00000060)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_RMSK                              0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_ADDR(x), HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_RES0_0_BMSK                       0xffffff00
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_RES0_0_SHFT                              0x8
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_L_VAL_BMSK                              0xff
#define HWIO_APCS_APC00_CPM_PLL_LVAL_DECREASE_L_VAL_SHFT                               0x0

#define HWIO_APCS_APC00_CPM_PLL_L_VAL_ADDR(x)                                   ((x) + 0x00000004)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_OFFS                                      (0x00000004)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_RMSK                                      0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_L_VAL_ADDR(x), HWIO_APCS_APC00_CPM_PLL_L_VAL_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_L_VAL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_L_VAL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_L_VAL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_L_VAL_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_RES0_0_BMSK                               0xffffff00
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_RES0_0_SHFT                                      0x8
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_L_VAL_7_0_BMSK                                  0xff
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_L_VAL_7_0_SHFT                                   0x0

#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_ADDR(x)                            ((x) + 0x00000104)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_OFFS                               (0x00000104)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_RMSK                               0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_ADDR(x), HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_RES0_0_BMSK                        0xffffff00
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_RES0_0_SHFT                               0x8
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_L_VAL_7_0_BMSK                           0xff
#define HWIO_APCS_APC00_CPM_PLL_L_VAL_STATUS_L_VAL_7_0_SHFT                            0x0

#define HWIO_APCS_APC00_CPM_PLL_MODE_ADDR(x)                                    ((x) + 0x00000000)
#define HWIO_APCS_APC00_CPM_PLL_MODE_OFFS                                       (0x00000000)
#define HWIO_APCS_APC00_CPM_PLL_MODE_RMSK                                       0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_MODE_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_MODE_ADDR(x), HWIO_APCS_APC00_CPM_PLL_MODE_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_MODE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_MODE_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_MODE_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_MODE_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_MODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_MODE_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_MODE_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_MODE_LOCK_DET_BMSK                              0x80000000
#define HWIO_APCS_APC00_CPM_PLL_MODE_LOCK_DET_SHFT                                    0x1f
#define HWIO_APCS_APC00_CPM_PLL_MODE_ACTIVE_FLAG_BMSK                           0x40000000
#define HWIO_APCS_APC00_CPM_PLL_MODE_ACTIVE_FLAG_SHFT                                 0x1e
#define HWIO_APCS_APC00_CPM_PLL_MODE_RES0_0_BMSK                                0x38000000
#define HWIO_APCS_APC00_CPM_PLL_MODE_RES0_0_SHFT                                      0x1b
#define HWIO_APCS_APC00_CPM_PLL_MODE_LCKINTR_BMSK                                0x4000000
#define HWIO_APCS_APC00_CPM_PLL_MODE_LCKINTR_SHFT                                     0x1a
#define HWIO_APCS_APC00_CPM_PLL_MODE_TBD_0_BMSK                                  0x2000000
#define HWIO_APCS_APC00_CPM_PLL_MODE_TBD_0_SHFT                                       0x19
#define HWIO_APCS_APC00_CPM_PLL_MODE_TBD_1_BMSK                                  0x1000000
#define HWIO_APCS_APC00_CPM_PLL_MODE_TBD_1_SHFT                                       0x18
#define HWIO_APCS_APC00_CPM_PLL_MODE_RES0_1_BMSK                                  0xe00000
#define HWIO_APCS_APC00_CPM_PLL_MODE_RES0_1_SHFT                                      0x15
#define HWIO_APCS_APC00_CPM_PLL_MODE_FSM_EN_BMSK                                  0x100000
#define HWIO_APCS_APC00_CPM_PLL_MODE_FSM_EN_SHFT                                      0x14
#define HWIO_APCS_APC00_CPM_PLL_MODE_BIAS_CNT_5_0_BMSK                             0xfc000
#define HWIO_APCS_APC00_CPM_PLL_MODE_BIAS_CNT_5_0_SHFT                                 0xe
#define HWIO_APCS_APC00_CPM_PLL_MODE_LOCK_CNT_5_0_BMSK                              0x3f00
#define HWIO_APCS_APC00_CPM_PLL_MODE_LOCK_CNT_5_0_SHFT                                 0x8
#define HWIO_APCS_APC00_CPM_PLL_MODE_RES0_2_BMSK                                      0xf0
#define HWIO_APCS_APC00_CPM_PLL_MODE_RES0_2_SHFT                                       0x4
#define HWIO_APCS_APC00_CPM_PLL_MODE_PLLTEST_BMSK                                      0x8
#define HWIO_APCS_APC00_CPM_PLL_MODE_PLLTEST_SHFT                                      0x3
#define HWIO_APCS_APC00_CPM_PLL_MODE_RESET_N_BMSK                                      0x4
#define HWIO_APCS_APC00_CPM_PLL_MODE_RESET_N_SHFT                                      0x2
#define HWIO_APCS_APC00_CPM_PLL_MODE_BYPASSNL_BMSK                                     0x2
#define HWIO_APCS_APC00_CPM_PLL_MODE_BYPASSNL_SHFT                                     0x1
#define HWIO_APCS_APC00_CPM_PLL_MODE_OUTCTRL_BMSK                                      0x1
#define HWIO_APCS_APC00_CPM_PLL_MODE_OUTCTRL_SHFT                                      0x0

#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_ADDR(x)                         ((x) + 0x00000030)
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_OFFS                            (0x00000030)
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_RMSK                            0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_ADDR(x), HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_RES0_0_BMSK                     0xffffff00
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_RES0_0_SHFT                            0x8
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_SSC_DELTA_7_0_BMSK                    0xff
#define HWIO_APCS_APC00_CPM_PLL_SSC_DELTA_ALPHA_SSC_DELTA_7_0_SHFT                     0x0

#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_ADDR(x)                         ((x) + 0x00000034)
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_OFFS                            (0x00000034)
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_RMSK                            0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_ADDR(x), HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_RES0_0_BMSK                     0xffffff00
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_RES0_0_SHFT                            0x8
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_SSC_UPDT_RATE_7_0_BMSK                0xff
#define HWIO_APCS_APC00_CPM_PLL_SSC_UPDATE_RATE_SSC_UPDT_RATE_7_0_SHFT                 0x0

#define HWIO_APCS_APC00_CPM_PLL_STATUS_ADDR(x)                                  ((x) + 0x00000028)
#define HWIO_APCS_APC00_CPM_PLL_STATUS_OFFS                                     (0x00000028)
#define HWIO_APCS_APC00_CPM_PLL_STATUS_RMSK                                     0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_STATUS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_STATUS_ADDR(x), HWIO_APCS_APC00_CPM_PLL_STATUS_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_STATUS_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_STATUS_STATUS_31_0_BMSK                         0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_STATUS_STATUS_31_0_SHFT                                0x0

#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_ADDR(x)                             ((x) + 0x00000024)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_OFFS                                (0x00000024)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_RMSK                                0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_ADDR(x), HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_TST_CTL_HI_31_0_BMSK                0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_HI_TST_CTL_HI_31_0_SHFT                       0x0

#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_ADDR(x)                             ((x) + 0x00000020)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_OFFS                                (0x00000020)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_RMSK                                0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_ADDR(x), HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_TST_CTL_LO_31_0_BMSK                0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_TEST_CTL_LO_TST_CTL_LO_31_0_SHFT                       0x0

#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_ADDR(x)                                ((x) + 0x00000010)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_OFFS                                   (0x00000010)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_RMSK                                   0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_USER_CTL_ADDR(x), HWIO_APCS_APC00_CPM_PLL_USER_CTL_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_USER_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PLL_USER_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PLL_USER_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PLL_USER_CTL_IN(x))
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_USR_CTL_31_0_BMSK                      0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_USR_CTL_31_0_SHFT                             0x0

#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_ADDR(x)                         ((x) + 0x00000110)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_OFFS                            (0x00000110)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_RMSK                            0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_ADDR(x), HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_RMSK)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_USR_CTL_31_0_BMSK               0xffffffff
#define HWIO_APCS_APC00_CPM_PLL_USER_CTL_STATUS_USR_CTL_31_0_SHFT                      0x0

#define HWIO_APCS_APC00_CPM_PSCTL_ADDR(x)                                       ((x) + 0x00000164)
#define HWIO_APCS_APC00_CPM_PSCTL_OFFS                                          (0x00000164)
#define HWIO_APCS_APC00_CPM_PSCTL_RMSK                                          0xffffffff
#define HWIO_APCS_APC00_CPM_PSCTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PSCTL_ADDR(x), HWIO_APCS_APC00_CPM_PSCTL_RMSK)
#define HWIO_APCS_APC00_CPM_PSCTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_PSCTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_PSCTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_PSCTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_PSCTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_PSCTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_PSCTL_IN(x))
#define HWIO_APCS_APC00_CPM_PSCTL_RES0_0_BMSK                                   0xfffc0000
#define HWIO_APCS_APC00_CPM_PSCTL_RES0_0_SHFT                                         0x12
#define HWIO_APCS_APC00_CPM_PSCTL_SSTRTGEN_BMSK                                    0x20000
#define HWIO_APCS_APC00_CPM_PSCTL_SSTRTGEN_SHFT                                       0x11
#define HWIO_APCS_APC00_CPM_PSCTL_SSTPGEN_BMSK                                     0x10000
#define HWIO_APCS_APC00_CPM_PSCTL_SSTPGEN_SHFT                                        0x10
#define HWIO_APCS_APC00_CPM_PSCTL_RES0_1_BMSK                                       0xf000
#define HWIO_APCS_APC00_CPM_PSCTL_RES0_1_SHFT                                          0xc
#define HWIO_APCS_APC00_CPM_PSCTL_START_STEP_DLY_3_0_BMSK                            0xf00
#define HWIO_APCS_APC00_CPM_PSCTL_START_STEP_DLY_3_0_SHFT                              0x8
#define HWIO_APCS_APC00_CPM_PSCTL_STOP_STEP_DLY_3_0_BMSK                              0xf0
#define HWIO_APCS_APC00_CPM_PSCTL_STOP_STEP_DLY_3_0_SHFT                               0x4
#define HWIO_APCS_APC00_CPM_PSCTL_RES0_2_BMSK                                          0x8
#define HWIO_APCS_APC00_CPM_PSCTL_RES0_2_SHFT                                          0x3
#define HWIO_APCS_APC00_CPM_PSCTL_STEP_CLK_MODE_BMSK                                   0x4
#define HWIO_APCS_APC00_CPM_PSCTL_STEP_CLK_MODE_SHFT                                   0x2
#define HWIO_APCS_APC00_CPM_PSCTL_STEP_CLK_MULT_1_0_BMSK                               0x3
#define HWIO_APCS_APC00_CPM_PSCTL_STEP_CLK_MULT_1_0_SHFT                               0x0

#define HWIO_APCS_APC00_CPM_QLL_EAR_ADDR(x)                                     ((x) + 0x00000200)
#define HWIO_APCS_APC00_CPM_QLL_EAR_OFFS                                        (0x00000200)
#define HWIO_APCS_APC00_CPM_QLL_EAR_RMSK                                        0xffffffff
#define HWIO_APCS_APC00_CPM_QLL_EAR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_QLL_EAR_ADDR(x), HWIO_APCS_APC00_CPM_QLL_EAR_RMSK)
#define HWIO_APCS_APC00_CPM_QLL_EAR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_QLL_EAR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_QLL_EAR_NS_BMSK                                     0x80000000
#define HWIO_APCS_APC00_CPM_QLL_EAR_NS_SHFT                                           0x1f
#define HWIO_APCS_APC00_CPM_QLL_EAR_RES0_0_BMSK                                 0x7ffc0000
#define HWIO_APCS_APC00_CPM_QLL_EAR_RES0_0_SHFT                                       0x12
#define HWIO_APCS_APC00_CPM_QLL_EAR_PA_17_2_BMSK                                   0x3fffc
#define HWIO_APCS_APC00_CPM_QLL_EAR_PA_17_2_SHFT                                       0x2
#define HWIO_APCS_APC00_CPM_QLL_EAR_RES0_1_BMSK                                        0x3
#define HWIO_APCS_APC00_CPM_QLL_EAR_RES0_1_SHFT                                        0x0

#define HWIO_APCS_APC00_CPM_QLL_ESR_ADDR(x)                                     ((x) + 0x00000204)
#define HWIO_APCS_APC00_CPM_QLL_ESR_OFFS                                        (0x00000204)
#define HWIO_APCS_APC00_CPM_QLL_ESR_RMSK                                        0xffffffff
#define HWIO_APCS_APC00_CPM_QLL_ESR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_QLL_ESR_ADDR(x), HWIO_APCS_APC00_CPM_QLL_ESR_RMSK)
#define HWIO_APCS_APC00_CPM_QLL_ESR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_QLL_ESR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_QLL_ESR_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_QLL_ESR_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_QLL_ESR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_QLL_ESR_ADDR(x),m,v,HWIO_APCS_APC00_CPM_QLL_ESR_IN(x))
#define HWIO_APCS_APC00_CPM_QLL_ESR_ME_BMSK                                     0x80000000
#define HWIO_APCS_APC00_CPM_QLL_ESR_ME_SHFT                                           0x1f
#define HWIO_APCS_APC00_CPM_QLL_ESR_RES0_0_BMSK                                 0x7ffffff0
#define HWIO_APCS_APC00_CPM_QLL_ESR_RES0_0_SHFT                                        0x4
#define HWIO_APCS_APC00_CPM_QLL_ESR_WDRE_BMSK                                          0x8
#define HWIO_APCS_APC00_CPM_QLL_ESR_WDRE_SHFT                                          0x3
#define HWIO_APCS_APC00_CPM_QLL_ESR_WIBS_BMSK                                          0x4
#define HWIO_APCS_APC00_CPM_QLL_ESR_WIBS_SHFT                                          0x2
#define HWIO_APCS_APC00_CPM_QLL_ESR_WRO_BMSK                                           0x2
#define HWIO_APCS_APC00_CPM_QLL_ESR_WRO_SHFT                                           0x1
#define HWIO_APCS_APC00_CPM_QLL_ESR_NR_BMSK                                            0x1
#define HWIO_APCS_APC00_CPM_QLL_ESR_NR_SHFT                                            0x0

#define HWIO_APCS_APC00_CPM_QLL_ESRS_ADDR(x)                                    ((x) + 0x00000208)
#define HWIO_APCS_APC00_CPM_QLL_ESRS_OFFS                                       (0x00000208)
#define HWIO_APCS_APC00_CPM_QLL_ESRS_RMSK                                       0xffffffff
#define HWIO_APCS_APC00_CPM_QLL_ESRS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_QLL_ESRS_ADDR(x), HWIO_APCS_APC00_CPM_QLL_ESRS_RMSK)
#define HWIO_APCS_APC00_CPM_QLL_ESRS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_QLL_ESRS_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_QLL_ESRS_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_QLL_ESRS_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_QLL_ESRS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_QLL_ESRS_ADDR(x),m,v,HWIO_APCS_APC00_CPM_QLL_ESRS_IN(x))
#define HWIO_APCS_APC00_CPM_QLL_ESRS_ME_BMSK                                    0x80000000
#define HWIO_APCS_APC00_CPM_QLL_ESRS_ME_SHFT                                          0x1f
#define HWIO_APCS_APC00_CPM_QLL_ESRS_RES0_0_BMSK                                0x7ffffff0
#define HWIO_APCS_APC00_CPM_QLL_ESRS_RES0_0_SHFT                                       0x4
#define HWIO_APCS_APC00_CPM_QLL_ESRS_WDRE_BMSK                                         0x8
#define HWIO_APCS_APC00_CPM_QLL_ESRS_WDRE_SHFT                                         0x3
#define HWIO_APCS_APC00_CPM_QLL_ESRS_WIBS_BMSK                                         0x4
#define HWIO_APCS_APC00_CPM_QLL_ESRS_WIBS_SHFT                                         0x2
#define HWIO_APCS_APC00_CPM_QLL_ESRS_WRO_BMSK                                          0x2
#define HWIO_APCS_APC00_CPM_QLL_ESRS_WRO_SHFT                                          0x1
#define HWIO_APCS_APC00_CPM_QLL_ESRS_NR_BMSK                                           0x1
#define HWIO_APCS_APC00_CPM_QLL_ESRS_NR_SHFT                                           0x0

#define HWIO_APCS_APC00_CPM_QLL_ESYNR_ADDR(x)                                   ((x) + 0x0000020c)
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_OFFS                                      (0x0000020c)
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_RMSK                                      0xffffffff
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_QLL_ESYNR_ADDR(x), HWIO_APCS_APC00_CPM_QLL_ESYNR_RMSK)
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_QLL_ESYNR_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_RES0_0_BMSK                               0x80000000
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_RES0_0_SHFT                                     0x1f
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_ESYNTYPE_2_0_BMSK                         0x70000000
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_ESYNTYPE_2_0_SHFT                               0x1c
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_RES0_1_BMSK                                0xfc00000
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_RES0_1_SHFT                                     0x16
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_RNW_BMSK                                    0x200000
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_RNW_SHFT                                        0x15
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_BTT_1_0_BMSK                                0x180000
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_BTT_1_0_SHFT                                    0x13
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_BID_2_0_BMSK                                 0x70000
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_BID_2_0_SHFT                                    0x10
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_PID_5_0_BMSK                                  0xfc00
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_PID_5_0_SHFT                                     0xa
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_MID_4_0_BMSK                                   0x3e0
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_MID_4_0_SHFT                                     0x5
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_TID_4_0_BMSK                                    0x1f
#define HWIO_APCS_APC00_CPM_QLL_ESYNR_TID_4_0_SHFT                                     0x0

#define HWIO_APCS_APC00_CPM_SSSCTL_ADDR(x)                                      ((x) + 0x00000160)
#define HWIO_APCS_APC00_CPM_SSSCTL_OFFS                                         (0x00000160)
#define HWIO_APCS_APC00_CPM_SSSCTL_RMSK                                         0xffffffff
#define HWIO_APCS_APC00_CPM_SSSCTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_SSSCTL_ADDR(x), HWIO_APCS_APC00_CPM_SSSCTL_RMSK)
#define HWIO_APCS_APC00_CPM_SSSCTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_SSSCTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_SSSCTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_SSSCTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_SSSCTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_SSSCTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_SSSCTL_IN(x))
#define HWIO_APCS_APC00_CPM_SSSCTL_RES0_0_BMSK                                  0xfffffff0
#define HWIO_APCS_APC00_CPM_SSSCTL_RES0_0_SHFT                                         0x4
#define HWIO_APCS_APC00_CPM_SSSCTL_TBD_0_BMSK                                          0x8
#define HWIO_APCS_APC00_CPM_SSSCTL_TBD_0_SHFT                                          0x3
#define HWIO_APCS_APC00_CPM_SSSCTL_SSWEN_BMSK                                          0x4
#define HWIO_APCS_APC00_CPM_SSSCTL_SSWEN_SHFT                                          0x2
#define HWIO_APCS_APC00_CPM_SSSCTL_SSTRTEN_BMSK                                        0x2
#define HWIO_APCS_APC00_CPM_SSSCTL_SSTRTEN_SHFT                                        0x1
#define HWIO_APCS_APC00_CPM_SSSCTL_SSTPAPMSWEN_BMSK                                    0x1
#define HWIO_APCS_APC00_CPM_SSSCTL_SSTPAPMSWEN_SHFT                                    0x0

#define HWIO_APCS_APC00_CPM_STCTL_ADDR(x)                                       ((x) + 0x00000170)
#define HWIO_APCS_APC00_CPM_STCTL_OFFS                                          (0x00000170)
#define HWIO_APCS_APC00_CPM_STCTL_RMSK                                          0xffffffff
#define HWIO_APCS_APC00_CPM_STCTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_STCTL_ADDR(x), HWIO_APCS_APC00_CPM_STCTL_RMSK)
#define HWIO_APCS_APC00_CPM_STCTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPM_STCTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPM_STCTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPM_STCTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPM_STCTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPM_STCTL_ADDR(x),m,v,HWIO_APCS_APC00_CPM_STCTL_IN(x))
#define HWIO_APCS_APC00_CPM_STCTL_RES0_0_BMSK                                   0xfffff000
#define HWIO_APCS_APC00_CPM_STCTL_RES0_0_SHFT                                          0xc
#define HWIO_APCS_APC00_CPM_STCTL_SWTR_3_0_BMSK                                      0xf00
#define HWIO_APCS_APC00_CPM_STCTL_SWTR_3_0_SHFT                                        0x8
#define HWIO_APCS_APC00_CPM_STCTL_RES0_1_BMSK                                         0xfe
#define HWIO_APCS_APC00_CPM_STCTL_RES0_1_SHFT                                          0x1
#define HWIO_APCS_APC00_CPM_STCTL_SWTREQ_BMSK                                          0x1
#define HWIO_APCS_APC00_CPM_STCTL_SWTREQ_SHFT                                          0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_DCVS_APC
 *--------------------------------------------------------------------------*/

#define APCS_APC00_DCVS_APC_REG_BASE                                       (HMSS_PERIPH_BASE      + 0x00244600)
#define APCS_APC00_DCVS_APC_REG_BASE_OFFS                                  0x00244600

#define HWIO_APCS_APC00_DCVS_CTL_ADDR(x)                                   ((x) + 0x00000000)
#define HWIO_APCS_APC00_DCVS_CTL_OFFS                                      (0x00000000)
#define HWIO_APCS_APC00_DCVS_CTL_RMSK                                      0x80030001
#define HWIO_APCS_APC00_DCVS_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_CTL_ADDR(x), HWIO_APCS_APC00_DCVS_CTL_RMSK)
#define HWIO_APCS_APC00_DCVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_CTL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_CTL_IN(x))
#define HWIO_APCS_APC00_DCVS_CTL_BUSY_BMSK                                 0x80000000
#define HWIO_APCS_APC00_DCVS_CTL_BUSY_SHFT                                       0x1f
#define HWIO_APCS_APC00_DCVS_CTL_IRQ_EN_BMSK                                  0x20000
#define HWIO_APCS_APC00_DCVS_CTL_IRQ_EN_SHFT                                     0x11
#define HWIO_APCS_APC00_DCVS_CTL_CSM_EN_BMSK                                  0x10000
#define HWIO_APCS_APC00_DCVS_CTL_CSM_EN_SHFT                                     0x10
#define HWIO_APCS_APC00_DCVS_CTL_REQ_BMSK                                         0x1
#define HWIO_APCS_APC00_DCVS_CTL_REQ_SHFT                                         0x0

#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x)                             ((x) + 0x00000004)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_OFFS                                (0x00000004)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_RMSK                                      0xff
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x), HWIO_APCS_APC00_DCVS_CEIL_VLVL_RMSK)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_CEIL_VLVL_IN(x))
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_CEILING_VLVL_BMSK                         0xff
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_CEILING_VLVL_SHFT                          0x0

#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x)                            ((x) + 0x00000008)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_OFFS                               (0x00000008)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_RMSK                                     0xff
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x), HWIO_APCS_APC00_DCVS_FLOOR_VLVL_RMSK)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_FLOOR_VLVL_IN(x))
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_FLOOR_VLVL_BMSK                          0xff
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_FLOOR_VLVL_SHFT                           0x0

#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x)                             ((x) + 0x0000000c)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_OFFS                                (0x0000000c)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_RMSK                                      0xff
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x), HWIO_APCS_APC00_DCVS_SAFE_LVAL_RMSK)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_SAFE_LVAL_IN(x))
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_SAFE_LVAL_BMSK                            0xff
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_SAFE_LVAL_SHFT                             0x0

#define HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x)                              ((x) + 0x00000010)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_OFFS                                 (0x00000010)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_RMSK                                 0xffff0073
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x), HWIO_APCS_APC00_DCVS_VOTE_CTL_RMSK)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_VOTE_CTL_IN(x))
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_HYST_DLY_BMSK                        0xffff0000
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_HYST_DLY_SHFT                              0x10
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_PWR_STATE_THRESHOLD_BMSK                   0x70
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_PWR_STATE_THRESHOLD_SHFT                    0x4
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_SW_VOTE_VAL_BMSK                            0x2
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_SW_VOTE_VAL_SHFT                            0x1
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_VOTE_EN_BMSK                                0x1
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_VOTE_EN_SHFT                                0x0

#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x)                          ((x) + 0x00000020)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_OFFS                             (0x00000020)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_RMSK                                    0x1
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x), HWIO_APCS_APC00_APC_PWR_GATE_MODE_RMSK)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x), m)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x),v)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x),m,v,HWIO_APCS_APC00_APC_PWR_GATE_MODE_IN(x))
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_MODE_BMSK                               0x1
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_MODE_SHFT                               0x0

#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x)                          ((x) + 0x00000024)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_OFFS                             (0x00000024)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_RMSK                                   0x7f
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x), HWIO_APCS_APC00_APC_LDO_VREF_FUNC_RMSK)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x), m)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x),v)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x),m,v,HWIO_APCS_APC00_APC_LDO_VREF_FUNC_IN(x))
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_VREF_LDO_BMSK                          0x7f
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_VREF_LDO_SHFT                           0x0

#define HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x)                           ((x) + 0x00000028)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_OFFS                              (0x00000028)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_RMSK                                    0x7f
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x), HWIO_APCS_APC00_APC_LDO_VREF_RET_RMSK)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x), m)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x),v)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x),m,v,HWIO_APCS_APC00_APC_LDO_VREF_RET_IN(x))
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_VREF_RET_BMSK                           0x7f
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_VREF_RET_SHFT                            0x0

#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x)                            ((x) + 0x00000030)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_OFFS                               (0x00000030)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_RMSK                                     0x13
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x), HWIO_APCS_APC00_APC_LDO_ACC_SEL_RMSK)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x), m)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x),v)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x),m,v,HWIO_APCS_APC00_APC_LDO_ACC_SEL_IN(x))
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_PERF_MUX_SEL_BMSK                        0x10
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_PERF_MUX_SEL_SHFT                         0x4
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_L2_MODE_BMSK                              0x2
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_L2_MODE_SHFT                              0x1
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_CPU_MODE_BMSK                             0x1
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_CPU_MODE_SHFT                             0x0

#define HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x)                            ((x) + 0x00000034)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_OFFS                               (0x00000034)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_RMSK                                      0x7
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x), HWIO_APCS_APC00_APC_PGS_RET_DIS_RMSK)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x), m)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x),v)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x),m,v,HWIO_APCS_APC00_APC_PGS_RET_DIS_IN(x))
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_L2_PGS_RET_SLP_DIS_BMSK                   0x4
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_L2_PGS_RET_SLP_DIS_SHFT                   0x2
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_CPU1_PGS_RET_SLP_DIS_BMSK                 0x2
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_CPU1_PGS_RET_SLP_DIS_SHFT                 0x1
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_CPU0_PGS_RET_SLP_DIS_BMSK                 0x1
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_CPU0_PGS_RET_SLP_DIS_SHFT                 0x0

#define HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x)                            ((x) + 0x00000038)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_OFFS                               (0x00000038)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_RMSK                                      0x7
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x), HWIO_APCS_APC00_APC_MAS_RET_DIS_RMSK)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x), m)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x),v)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x),m,v,HWIO_APCS_APC00_APC_MAS_RET_DIS_IN(x))
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_L2_MAS_RET_SLP_DIS_BMSK                   0x4
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_L2_MAS_RET_SLP_DIS_SHFT                   0x2
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_CPU1_MAS_RET_SLP_DIS_BMSK                 0x2
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_CPU1_MAS_RET_SLP_DIS_SHFT                 0x1
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_CPU0_MAS_RET_SLP_DIS_BMSK                 0x1
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_CPU0_MAS_RET_SLP_DIS_SHFT                 0x0


#endif /* __HWDCVS_HWIO_H__ */
