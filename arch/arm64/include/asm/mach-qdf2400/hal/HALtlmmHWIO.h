#ifndef __HALTLMMHWIO_H__
#define __HALTLMMHWIO_H__
/*
===========================================================================
*/
/**
  @file HALtlmmHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r63.0]

  This file contains HWIO register definitions for the following modules:
    TLMM_CSR

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

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/

#include <asm/mach/hal/msmhwiobase.h>

/*----------------------------------------------------------------------------
 * MODULE: TLMM_CSR
 *--------------------------------------------------------------------------*/

#define TLMM_CSR_REG_BASE                                            (TLMM_BASE      + 0x00010000)
#define TLMM_CSR_REG_BASE_OFFS                                       0x00010000

#define HWIO_TLMM_GPIO_CFGn_ADDR(n)                                  (TLMM_CSR_REG_BASE      + 0x00000000 + 0x10000 * (n))
#define HWIO_TLMM_GPIO_CFGn_OFFS(n)                                  (TLMM_CSR_REG_BASE_OFFS + 0x00000000 + 0x10000 * (n))
#define HWIO_TLMM_GPIO_CFGn_RMSK                                          0x7ff
#define HWIO_TLMM_GPIO_CFGn_MAXn                                            149
#define HWIO_TLMM_GPIO_CFGn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_CFGn_ADDR(n), HWIO_TLMM_GPIO_CFGn_RMSK)
#define HWIO_TLMM_GPIO_CFGn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_CFGn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_CFGn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_CFGn_ADDR(n),val)
#define HWIO_TLMM_GPIO_CFGn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_CFGn_ADDR(n),mask,val,HWIO_TLMM_GPIO_CFGn_INI(n))
#define HWIO_TLMM_GPIO_CFGn_GPIO_HIHYS_EN_BMSK                            0x400
#define HWIO_TLMM_GPIO_CFGn_GPIO_HIHYS_EN_SHFT                              0xa
#define HWIO_TLMM_GPIO_CFGn_GPIO_OE_BMSK                                  0x200
#define HWIO_TLMM_GPIO_CFGn_GPIO_OE_SHFT                                    0x9
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_BMSK                             0x1c0
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_SHFT                               0x6
#define HWIO_TLMM_GPIO_CFGn_FUNC_SEL_BMSK                                  0x3c
#define HWIO_TLMM_GPIO_CFGn_FUNC_SEL_SHFT                                   0x2
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_BMSK                                  0x3
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_SHFT                                  0x0

#define HWIO_TLMM_GPIO_IN_OUTn_ADDR(n)                               (TLMM_CSR_REG_BASE      + 0x00000004 + 0x10000 * (n))
#define HWIO_TLMM_GPIO_IN_OUTn_OFFS(n)                               (TLMM_CSR_REG_BASE_OFFS + 0x00000004 + 0x10000 * (n))
#define HWIO_TLMM_GPIO_IN_OUTn_RMSK                                         0x3
#define HWIO_TLMM_GPIO_IN_OUTn_MAXn                                         149
#define HWIO_TLMM_GPIO_IN_OUTn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n), HWIO_TLMM_GPIO_IN_OUTn_RMSK)
#define HWIO_TLMM_GPIO_IN_OUTn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_IN_OUTn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n),val)
#define HWIO_TLMM_GPIO_IN_OUTn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n),mask,val,HWIO_TLMM_GPIO_IN_OUTn_INI(n))
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK                                0x2
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT                                0x1
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_BMSK                                 0x1
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_SHFT                                 0x0

#define HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n)                             (TLMM_CSR_REG_BASE      + 0x00000008 + 0x10000 * (n))
#define HWIO_TLMM_GPIO_INTR_CFGn_OFFS(n)                             (TLMM_CSR_REG_BASE_OFFS + 0x00000008 + 0x10000 * (n))
#define HWIO_TLMM_GPIO_INTR_CFGn_RMSK                                     0x1ff
#define HWIO_TLMM_GPIO_INTR_CFGn_MAXn                                       149
#define HWIO_TLMM_GPIO_INTR_CFGn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n), HWIO_TLMM_GPIO_INTR_CFGn_RMSK)
#define HWIO_TLMM_GPIO_INTR_CFGn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_INTR_CFGn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n),val)
#define HWIO_TLMM_GPIO_INTR_CFGn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n),mask,val,HWIO_TLMM_GPIO_INTR_CFGn_INI(n))
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_BMSK                         0x100
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_SHFT                           0x8
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_BMSK                          0xe0
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_SHFT                           0x5
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_BMSK                   0x10
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_SHFT                    0x4
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_BMSK                         0xc
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_SHFT                         0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_BMSK                          0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_SHFT                          0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_BMSK                           0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_SHFT                           0x0

#define HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n)                          (TLMM_CSR_REG_BASE      + 0x0000000c + 0x10000 * (n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_OFFS(n)                          (TLMM_CSR_REG_BASE_OFFS + 0x0000000c + 0x10000 * (n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_RMSK                                    0x1
#define HWIO_TLMM_GPIO_INTR_STATUSn_MAXn                                    149
#define HWIO_TLMM_GPIO_INTR_STATUSn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n), HWIO_TLMM_GPIO_INTR_STATUSn_RMSK)
#define HWIO_TLMM_GPIO_INTR_STATUSn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_INTR_STATUSn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n),val)
#define HWIO_TLMM_GPIO_INTR_STATUSn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n),mask,val,HWIO_TLMM_GPIO_INTR_STATUSn_INI(n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_BMSK                        0x1
#define HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_SHFT                        0x0

#define HWIO_TLMM_GPIO_SDC_CTLn_ADDR(n)                              (TLMM_CSR_REG_BASE      + 0x00000010 + 0x10000 * (n))
#define HWIO_TLMM_GPIO_SDC_CTLn_OFFS(n)                              (TLMM_CSR_REG_BASE_OFFS + 0x00000010 + 0x10000 * (n))
#define HWIO_TLMM_GPIO_SDC_CTLn_RMSK                                        0x1
#define HWIO_TLMM_GPIO_SDC_CTLn_MAXn                                         74
#define HWIO_TLMM_GPIO_SDC_CTLn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CTLn_ADDR(n), HWIO_TLMM_GPIO_SDC_CTLn_RMSK)
#define HWIO_TLMM_GPIO_SDC_CTLn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CTLn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_SDC_CTLn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_SDC_CTLn_ADDR(n),val)
#define HWIO_TLMM_GPIO_SDC_CTLn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_SDC_CTLn_ADDR(n),mask,val,HWIO_TLMM_GPIO_SDC_CTLn_INI(n))
#define HWIO_TLMM_GPIO_SDC_CTLn_MODE_18_BMSK                                0x1
#define HWIO_TLMM_GPIO_SDC_CTLn_MODE_18_SHFT                                0x0

#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_ADDR                           (TLMM_CSR_REG_BASE      + 0x00330014)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_OFFS                           (TLMM_CSR_REG_BASE_OFFS + 0x00330014)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_RMSK                                  0x1
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CLK_LOOP51_ADDR, HWIO_TLMM_GPIO_SDC_CLK_LOOP51_RMSK)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CLK_LOOP51_ADDR, m)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_SDC_CLK_LOOP51_ADDR,v)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_SDC_CLK_LOOP51_ADDR,m,v,HWIO_TLMM_GPIO_SDC_CLK_LOOP51_IN)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_LOOP_MODE_BMSK                        0x1
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP51_LOOP_MODE_SHFT                        0x0

#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_ADDR                           (TLMM_CSR_REG_BASE      + 0x003d0014)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_OFFS                           (TLMM_CSR_REG_BASE_OFFS + 0x003d0014)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_RMSK                                  0x1
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CLK_LOOP61_ADDR, HWIO_TLMM_GPIO_SDC_CLK_LOOP61_RMSK)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CLK_LOOP61_ADDR, m)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_SDC_CLK_LOOP61_ADDR,v)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_SDC_CLK_LOOP61_ADDR,m,v,HWIO_TLMM_GPIO_SDC_CLK_LOOP61_IN)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_LOOP_MODE_BMSK                        0x1
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP61_LOOP_MODE_SHFT                        0x0

#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_ADDR                           (TLMM_CSR_REG_BASE      + 0x003f0014)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_OFFS                           (TLMM_CSR_REG_BASE_OFFS + 0x003f0014)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_RMSK                                  0x1
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CLK_LOOP63_ADDR, HWIO_TLMM_GPIO_SDC_CLK_LOOP63_RMSK)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CLK_LOOP63_ADDR, m)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_SDC_CLK_LOOP63_ADDR,v)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_SDC_CLK_LOOP63_ADDR,m,v,HWIO_TLMM_GPIO_SDC_CLK_LOOP63_IN)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_LOOP_MODE_BMSK                        0x1
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP63_LOOP_MODE_SHFT                        0x0

#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_ADDR                           (TLMM_CSR_REG_BASE      + 0x00490014)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_OFFS                           (TLMM_CSR_REG_BASE_OFFS + 0x00490014)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_RMSK                                  0x1
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CLK_LOOP73_ADDR, HWIO_TLMM_GPIO_SDC_CLK_LOOP73_RMSK)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_SDC_CLK_LOOP73_ADDR, m)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_SDC_CLK_LOOP73_ADDR,v)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_SDC_CLK_LOOP73_ADDR,m,v,HWIO_TLMM_GPIO_SDC_CLK_LOOP73_IN)
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_LOOP_MODE_BMSK                        0x1
#define HWIO_TLMM_GPIO_SDC_CLK_LOOP73_LOOP_MODE_SHFT                        0x0

#define HWIO_TLMM_CLK_GATE_EN_ADDR                                   (TLMM_CSR_REG_BASE      + 0x00960000)
#define HWIO_TLMM_CLK_GATE_EN_OFFS                                   (TLMM_CSR_REG_BASE_OFFS + 0x00960000)
#define HWIO_TLMM_CLK_GATE_EN_RMSK                                          0x7
#define HWIO_TLMM_CLK_GATE_EN_IN          \
        in_dword_masked(HWIO_TLMM_CLK_GATE_EN_ADDR, HWIO_TLMM_CLK_GATE_EN_RMSK)
#define HWIO_TLMM_CLK_GATE_EN_INM(m)      \
        in_dword_masked(HWIO_TLMM_CLK_GATE_EN_ADDR, m)
#define HWIO_TLMM_CLK_GATE_EN_OUT(v)      \
        out_dword(HWIO_TLMM_CLK_GATE_EN_ADDR,v)
#define HWIO_TLMM_CLK_GATE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_CLK_GATE_EN_ADDR,m,v,HWIO_TLMM_CLK_GATE_EN_IN)
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_BMSK                              0x4
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_SHFT                              0x2
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_BMSK                          0x2
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_SHFT                          0x1
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_BMSK                             0x1
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_SHFT                             0x0

#define HWIO_TLMM_IE_CTRL_DISABLE_ADDR                               (TLMM_CSR_REG_BASE      + 0x00960004)
#define HWIO_TLMM_IE_CTRL_DISABLE_OFFS                               (TLMM_CSR_REG_BASE_OFFS + 0x00960004)
#define HWIO_TLMM_IE_CTRL_DISABLE_RMSK                                      0x1
#define HWIO_TLMM_IE_CTRL_DISABLE_IN          \
        in_dword_masked(HWIO_TLMM_IE_CTRL_DISABLE_ADDR, HWIO_TLMM_IE_CTRL_DISABLE_RMSK)
#define HWIO_TLMM_IE_CTRL_DISABLE_INM(m)      \
        in_dword_masked(HWIO_TLMM_IE_CTRL_DISABLE_ADDR, m)
#define HWIO_TLMM_IE_CTRL_DISABLE_OUT(v)      \
        out_dword(HWIO_TLMM_IE_CTRL_DISABLE_ADDR,v)
#define HWIO_TLMM_IE_CTRL_DISABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_IE_CTRL_DISABLE_ADDR,m,v,HWIO_TLMM_IE_CTRL_DISABLE_IN)
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_BMSK                      0x1
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_SHFT                      0x0

#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR                           (TLMM_CSR_REG_BASE      + 0x00960008)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OFFS                           (TLMM_CSR_REG_BASE_OFFS + 0x00960008)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_RMSK                             0xffffff
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_IN          \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR, HWIO_TLMM_MPM_WAKEUP_INT_EN_0_RMSK)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_INM(m)      \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR, m)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OUT(v)      \
        out_dword(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR,v)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR,m,v,HWIO_TLMM_MPM_WAKEUP_INT_EN_0_IN)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_131_BMSK                    0x800000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_131_SHFT                        0x17
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_130_BMSK                    0x400000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_130_SHFT                        0x16
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_123_BMSK                    0x200000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_123_SHFT                        0x15
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_122_BMSK                    0x100000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_122_SHFT                        0x14
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_113_BMSK                     0x80000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_113_SHFT                        0x13
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_112_BMSK                     0x40000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_112_SHFT                        0x12
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_111_BMSK                     0x20000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_111_SHFT                        0x11
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_90_BMSK                      0x10000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_90_SHFT                         0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_89_BMSK                       0x8000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_89_SHFT                          0xf
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_88_BMSK                       0x4000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_88_SHFT                          0xe
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_87_BMSK                       0x2000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_87_SHFT                          0xd
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_86_BMSK                       0x1000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_86_SHFT                          0xc
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_85_BMSK                        0x800
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_85_SHFT                          0xb
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_84_BMSK                        0x400
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_84_SHFT                          0xa
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_83_BMSK                        0x200
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_83_SHFT                          0x9
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_72_BMSK                        0x100
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_72_SHFT                          0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_70_BMSK                         0x80
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_70_SHFT                          0x7
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_68_BMSK                         0x40
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_68_SHFT                          0x6
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_BMSK                         0x20
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_SHFT                          0x5
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_60_BMSK                         0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_60_SHFT                          0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_58_BMSK                          0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_58_SHFT                          0x3
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_56_BMSK                          0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_56_SHFT                          0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_BMSK                          0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_SHFT                          0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_BMSK                          0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_SHFT                          0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_ADDR(n)                     (TLMM_CSR_REG_BASE      + 0x00970000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_OFFS(n)                     (TLMM_CSR_REG_BASE_OFFS + 0x00970000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_RMSK                             0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_MAXn                                15
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_POLARITY_BMSK                    0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_POLARITY_SHFT                      0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_GPIO_SEL_BMSK                     0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_GPIO_SEL_SHFT                      0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n)                    (TLMM_CSR_REG_BASE      + 0x00980000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_OFFS(n)                    (TLMM_CSR_REG_BASE_OFFS + 0x00980000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_RMSK                            0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_MAXn                               15
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_POLARITY_BMSK                   0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_POLARITY_SHFT                     0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_GPIO_SEL_BMSK                    0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_GPIO_SEL_SHFT                     0x0

#define HWIO_TLMM_MODE_PULL_CTL_ADDR                                 (TLMM_CSR_REG_BASE      + 0x00990000)
#define HWIO_TLMM_MODE_PULL_CTL_OFFS                                 (TLMM_CSR_REG_BASE_OFFS + 0x00990000)
#define HWIO_TLMM_MODE_PULL_CTL_RMSK                                        0xf
#define HWIO_TLMM_MODE_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_MODE_PULL_CTL_ADDR, HWIO_TLMM_MODE_PULL_CTL_RMSK)
#define HWIO_TLMM_MODE_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_MODE_PULL_CTL_ADDR, m)
#define HWIO_TLMM_MODE_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_MODE_PULL_CTL_ADDR,v)
#define HWIO_TLMM_MODE_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MODE_PULL_CTL_ADDR,m,v,HWIO_TLMM_MODE_PULL_CTL_IN)
#define HWIO_TLMM_MODE_PULL_CTL_MODE_1_PULL_BMSK                            0xc
#define HWIO_TLMM_MODE_PULL_CTL_MODE_1_PULL_SHFT                            0x2
#define HWIO_TLMM_MODE_PULL_CTL_MODE_0_PULL_BMSK                            0x3
#define HWIO_TLMM_MODE_PULL_CTL_MODE_0_PULL_SHFT                            0x0

#define HWIO_TLMM_PMIC_CTL0_ADDR                                     (TLMM_CSR_REG_BASE      + 0x009a0000)
#define HWIO_TLMM_PMIC_CTL0_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x009a0000)
#define HWIO_TLMM_PMIC_CTL0_RMSK                                      0x1ffffc7
#define HWIO_TLMM_PMIC_CTL0_IN          \
        in_dword_masked(HWIO_TLMM_PMIC_CTL0_ADDR, HWIO_TLMM_PMIC_CTL0_RMSK)
#define HWIO_TLMM_PMIC_CTL0_INM(m)      \
        in_dword_masked(HWIO_TLMM_PMIC_CTL0_ADDR, m)
#define HWIO_TLMM_PMIC_CTL0_OUT(v)      \
        out_dword(HWIO_TLMM_PMIC_CTL0_ADDR,v)
#define HWIO_TLMM_PMIC_CTL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_PMIC_CTL0_ADDR,m,v,HWIO_TLMM_PMIC_CTL0_IN)
#define HWIO_TLMM_PMIC_CTL0_PSHOLD_HDRV_BMSK                          0x1c00000
#define HWIO_TLMM_PMIC_CTL0_PSHOLD_HDRV_SHFT                               0x16
#define HWIO_TLMM_PMIC_CTL0_CXO_EN_HDRV_BMSK                           0x380000
#define HWIO_TLMM_PMIC_CTL0_CXO_EN_HDRV_SHFT                               0x13
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_HIHYS_EN_DATA_BMSK               0x40000
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_HIHYS_EN_DATA_SHFT                  0x12
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_HIHYS_EN_CLK_BMSK                0x20000
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_HIHYS_EN_CLK_SHFT                   0x11
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_DATA_SR_CTL_BMSK                 0x18000
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_DATA_SR_CTL_SHFT                     0xf
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_CLK_SR_CTL_BMSK                   0x6000
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_CLK_SR_CTL_SHFT                      0xd
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_DATA_PULL_BMSK                    0x1800
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_DATA_PULL_SHFT                       0xb
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_CLK_PULL_BMSK                      0x600
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_CLK_PULL_SHFT                        0x9
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_DATA_HDRV_BMSK                     0x1c0
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_DATA_HDRV_SHFT                       0x6
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_CLK_HDRV_BMSK                        0x7
#define HWIO_TLMM_PMIC_CTL0_PMIC_SPMI0_CLK_HDRV_SHFT                        0x0

#define HWIO_TLMM_PMIC_CTL1_ADDR                                     (TLMM_CSR_REG_BASE      + 0x009a0004)
#define HWIO_TLMM_PMIC_CTL1_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x009a0004)
#define HWIO_TLMM_PMIC_CTL1_RMSK                                        0x7ffc7
#define HWIO_TLMM_PMIC_CTL1_IN          \
        in_dword_masked(HWIO_TLMM_PMIC_CTL1_ADDR, HWIO_TLMM_PMIC_CTL1_RMSK)
#define HWIO_TLMM_PMIC_CTL1_INM(m)      \
        in_dword_masked(HWIO_TLMM_PMIC_CTL1_ADDR, m)
#define HWIO_TLMM_PMIC_CTL1_OUT(v)      \
        out_dword(HWIO_TLMM_PMIC_CTL1_ADDR,v)
#define HWIO_TLMM_PMIC_CTL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_PMIC_CTL1_ADDR,m,v,HWIO_TLMM_PMIC_CTL1_IN)
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_HIHYS_EN_DATA_BMSK               0x40000
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_HIHYS_EN_DATA_SHFT                  0x12
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_HIHYS_EN_CLK_BMSK                0x20000
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_HIHYS_EN_CLK_SHFT                   0x11
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_DATA_SR_CTL_BMSK                 0x18000
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_DATA_SR_CTL_SHFT                     0xf
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_CLK_SR_CTL_BMSK                   0x6000
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_CLK_SR_CTL_SHFT                      0xd
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_DATA_PULL_BMSK                    0x1800
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_DATA_PULL_SHFT                       0xb
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_CLK_PULL_BMSK                      0x600
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_CLK_PULL_SHFT                        0x9
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_DATA_HDRV_BMSK                     0x1c0
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_DATA_HDRV_SHFT                       0x6
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_CLK_HDRV_BMSK                        0x7
#define HWIO_TLMM_PMIC_CTL1_PMIC_SPMI1_CLK_HDRV_SHFT                        0x0

#define HWIO_TLMM_PMIC_CTL2_ADDR                                     (TLMM_CSR_REG_BASE      + 0x009a0008)
#define HWIO_TLMM_PMIC_CTL2_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x009a0008)
#define HWIO_TLMM_PMIC_CTL2_RMSK                                        0x7ffc7
#define HWIO_TLMM_PMIC_CTL2_IN          \
        in_dword_masked(HWIO_TLMM_PMIC_CTL2_ADDR, HWIO_TLMM_PMIC_CTL2_RMSK)
#define HWIO_TLMM_PMIC_CTL2_INM(m)      \
        in_dword_masked(HWIO_TLMM_PMIC_CTL2_ADDR, m)
#define HWIO_TLMM_PMIC_CTL2_OUT(v)      \
        out_dword(HWIO_TLMM_PMIC_CTL2_ADDR,v)
#define HWIO_TLMM_PMIC_CTL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_PMIC_CTL2_ADDR,m,v,HWIO_TLMM_PMIC_CTL2_IN)
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_HIHYS_EN_DATA_BMSK               0x40000
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_HIHYS_EN_DATA_SHFT                  0x12
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_HIHYS_EN_CLK_BMSK                0x20000
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_HIHYS_EN_CLK_SHFT                   0x11
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_DATA_SR_CTL_BMSK                 0x18000
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_DATA_SR_CTL_SHFT                     0xf
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_CLK_SR_CTL_BMSK                   0x6000
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_CLK_SR_CTL_SHFT                      0xd
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_DATA_PULL_BMSK                    0x1800
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_DATA_PULL_SHFT                       0xb
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_CLK_PULL_BMSK                      0x600
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_CLK_PULL_SHFT                        0x9
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_DATA_HDRV_BMSK                     0x1c0
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_DATA_HDRV_SHFT                       0x6
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_CLK_HDRV_BMSK                        0x7
#define HWIO_TLMM_PMIC_CTL2_PMIC_SPMI2_CLK_HDRV_SHFT                        0x0

#define HWIO_TLMM_THERM_HDRV_CTL_ADDR                                (TLMM_CSR_REG_BASE      + 0x009b0000)
#define HWIO_TLMM_THERM_HDRV_CTL_OFFS                                (TLMM_CSR_REG_BASE_OFFS + 0x009b0000)
#define HWIO_TLMM_THERM_HDRV_CTL_RMSK                                      0x3f
#define HWIO_TLMM_THERM_HDRV_CTL_IN          \
        in_dword_masked(HWIO_TLMM_THERM_HDRV_CTL_ADDR, HWIO_TLMM_THERM_HDRV_CTL_RMSK)
#define HWIO_TLMM_THERM_HDRV_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_THERM_HDRV_CTL_ADDR, m)
#define HWIO_TLMM_THERM_HDRV_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_THERM_HDRV_CTL_ADDR,v)
#define HWIO_TLMM_THERM_HDRV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_THERM_HDRV_CTL_ADDR,m,v,HWIO_TLMM_THERM_HDRV_CTL_IN)
#define HWIO_TLMM_THERM_HDRV_CTL_PROC_HOT_HDRV_BMSK                        0x38
#define HWIO_TLMM_THERM_HDRV_CTL_PROC_HOT_HDRV_SHFT                         0x3
#define HWIO_TLMM_THERM_HDRV_CTL_THERM_TRIP_HDRV_BMSK                       0x7
#define HWIO_TLMM_THERM_HDRV_CTL_THERM_TRIP_HDRV_SHFT                       0x0

#define HWIO_TLMM_JTAG_HDRV_CTL_ADDR                                 (TLMM_CSR_REG_BASE      + 0x009c0000)
#define HWIO_TLMM_JTAG_HDRV_CTL_OFFS                                 (TLMM_CSR_REG_BASE_OFFS + 0x009c0000)
#define HWIO_TLMM_JTAG_HDRV_CTL_RMSK                                      0x3ff
#define HWIO_TLMM_JTAG_HDRV_CTL_IN          \
        in_dword_masked(HWIO_TLMM_JTAG_HDRV_CTL_ADDR, HWIO_TLMM_JTAG_HDRV_CTL_RMSK)
#define HWIO_TLMM_JTAG_HDRV_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_JTAG_HDRV_CTL_ADDR, m)
#define HWIO_TLMM_JTAG_HDRV_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_JTAG_HDRV_CTL_ADDR,v)
#define HWIO_TLMM_JTAG_HDRV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_JTAG_HDRV_CTL_ADDR,m,v,HWIO_TLMM_JTAG_HDRV_CTL_IN)
#define HWIO_TLMM_JTAG_HDRV_CTL_TDI_PULL_BMSK                             0x300
#define HWIO_TLMM_JTAG_HDRV_CTL_TDI_PULL_SHFT                               0x8
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_PULL_BMSK                              0xc0
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_PULL_SHFT                               0x6
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_HDRV_BMSK                              0x38
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_HDRV_SHFT                               0x3
#define HWIO_TLMM_JTAG_HDRV_CTL_TDO_HDRV_BMSK                               0x7
#define HWIO_TLMM_JTAG_HDRV_CTL_TDO_HDRV_SHFT                               0x0

#define HWIO_TLMM_RESOUT_HDRV_CTL_ADDR                               (TLMM_CSR_REG_BASE      + 0x009d0000)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OFFS                               (TLMM_CSR_REG_BASE_OFFS + 0x009d0000)
#define HWIO_TLMM_RESOUT_HDRV_CTL_RMSK                                      0x7
#define HWIO_TLMM_RESOUT_HDRV_CTL_IN          \
        in_dword_masked(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR, HWIO_TLMM_RESOUT_HDRV_CTL_RMSK)
#define HWIO_TLMM_RESOUT_HDRV_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR, m)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR,v)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR,m,v,HWIO_TLMM_RESOUT_HDRV_CTL_IN)
#define HWIO_TLMM_RESOUT_HDRV_CTL_RESOUT_N_HDRV_BMSK                        0x7
#define HWIO_TLMM_RESOUT_HDRV_CTL_RESOUT_N_HDRV_SHFT                        0x0

#define HWIO_TLMM_SPARE_ADDR                                         (TLMM_CSR_REG_BASE      + 0x009e0000)
#define HWIO_TLMM_SPARE_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x009e0000)
#define HWIO_TLMM_SPARE_RMSK                                               0xff
#define HWIO_TLMM_SPARE_IN          \
        in_dword_masked(HWIO_TLMM_SPARE_ADDR, HWIO_TLMM_SPARE_RMSK)
#define HWIO_TLMM_SPARE_INM(m)      \
        in_dword_masked(HWIO_TLMM_SPARE_ADDR, m)
#define HWIO_TLMM_SPARE_OUT(v)      \
        out_dword(HWIO_TLMM_SPARE_ADDR,v)
#define HWIO_TLMM_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SPARE_ADDR,m,v,HWIO_TLMM_SPARE_IN)
#define HWIO_TLMM_SPARE_MISC_BMSK                                          0xff
#define HWIO_TLMM_SPARE_MISC_SHFT                                           0x0

#define HWIO_TLMM_INT_JTAG_CTL_ADDR                                  (TLMM_CSR_REG_BASE      + 0x009f0000)
#define HWIO_TLMM_INT_JTAG_CTL_OFFS                                  (TLMM_CSR_REG_BASE_OFFS + 0x009f0000)
#define HWIO_TLMM_INT_JTAG_CTL_RMSK                                         0xf
#define HWIO_TLMM_INT_JTAG_CTL_IN          \
        in_dword_masked(HWIO_TLMM_INT_JTAG_CTL_ADDR, HWIO_TLMM_INT_JTAG_CTL_RMSK)
#define HWIO_TLMM_INT_JTAG_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_INT_JTAG_CTL_ADDR, m)
#define HWIO_TLMM_INT_JTAG_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_INT_JTAG_CTL_ADDR,v)
#define HWIO_TLMM_INT_JTAG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_INT_JTAG_CTL_ADDR,m,v,HWIO_TLMM_INT_JTAG_CTL_IN)
#define HWIO_TLMM_INT_JTAG_CTL_HMSS_TAP_ENA_BMSK                            0x8
#define HWIO_TLMM_INT_JTAG_CTL_HMSS_TAP_ENA_SHFT                            0x3
#define HWIO_TLMM_INT_JTAG_CTL_QDSS_TAP_ENA_BMSK                            0x4
#define HWIO_TLMM_INT_JTAG_CTL_QDSS_TAP_ENA_SHFT                            0x2
#define HWIO_TLMM_INT_JTAG_CTL_ACC_TAP_ENA_BMSK                             0x2
#define HWIO_TLMM_INT_JTAG_CTL_ACC_TAP_ENA_SHFT                             0x1
#define HWIO_TLMM_INT_JTAG_CTL_QDF_TAP_ENA_BMSK                             0x1
#define HWIO_TLMM_INT_JTAG_CTL_QDF_TAP_ENA_SHFT                             0x0

#define HWIO_TIC_AS_FUNC_MASTER_ADDR                                 (TLMM_CSR_REG_BASE      + 0x00a00000)
#define HWIO_TIC_AS_FUNC_MASTER_OFFS                                 (TLMM_CSR_REG_BASE_OFFS + 0x00a00000)
#define HWIO_TIC_AS_FUNC_MASTER_RMSK                                        0x1
#define HWIO_TIC_AS_FUNC_MASTER_IN          \
        in_dword_masked(HWIO_TIC_AS_FUNC_MASTER_ADDR, HWIO_TIC_AS_FUNC_MASTER_RMSK)
#define HWIO_TIC_AS_FUNC_MASTER_INM(m)      \
        in_dword_masked(HWIO_TIC_AS_FUNC_MASTER_ADDR, m)
#define HWIO_TIC_AS_FUNC_MASTER_OUT(v)      \
        out_dword(HWIO_TIC_AS_FUNC_MASTER_ADDR,v)
#define HWIO_TIC_AS_FUNC_MASTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TIC_AS_FUNC_MASTER_ADDR,m,v,HWIO_TIC_AS_FUNC_MASTER_IN)
#define HWIO_TIC_AS_FUNC_MASTER_TIC_AS_FUNC_MASTER_BMSK                     0x1
#define HWIO_TIC_AS_FUNC_MASTER_TIC_AS_FUNC_MASTER_SHFT                     0x0

#define HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR                               (TLMM_CSR_REG_BASE      + 0x00a10000)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OFFS                               (TLMM_CSR_REG_BASE_OFFS + 0x00a10000)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_RMSK                                      0x3
#define HWIO_TLMM_DBG_BUS_OUT_SEL_IN          \
        in_dword_masked(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR, HWIO_TLMM_DBG_BUS_OUT_SEL_RMSK)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_INM(m)      \
        in_dword_masked(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR, m)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OUT(v)      \
        out_dword(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR,v)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR,m,v,HWIO_TLMM_DBG_BUS_OUT_SEL_IN)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_BMSK                             0x3
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_SHFT                             0x0

#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR                         (TLMM_CSR_REG_BASE      + 0x00a20000)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_OFFS                         (TLMM_CSR_REG_BASE_OFFS + 0x00a20000)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_RMSK                                0x1
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_IN          \
        in_dword_masked(HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR, HWIO_TLMM_PERIPH_CHAR_TEST_MODE_RMSK)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_INM(m)      \
        in_dword_masked(HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR, m)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_OUT(v)      \
        out_dword(HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR,v)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR,m,v,HWIO_TLMM_PERIPH_CHAR_TEST_MODE_IN)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_CHAR_TEST_MODE_BMSK                 0x1
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_CHAR_TEST_MODE_SHFT                 0x0

#define HWIO_TLMM_CHIP_MODE_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00a30000)
#define HWIO_TLMM_CHIP_MODE_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00a30000)
#define HWIO_TLMM_CHIP_MODE_RMSK                                            0x3
#define HWIO_TLMM_CHIP_MODE_IN          \
        in_dword_masked(HWIO_TLMM_CHIP_MODE_ADDR, HWIO_TLMM_CHIP_MODE_RMSK)
#define HWIO_TLMM_CHIP_MODE_INM(m)      \
        in_dword_masked(HWIO_TLMM_CHIP_MODE_ADDR, m)
#define HWIO_TLMM_CHIP_MODE_MODE1_PIN_BMSK                                  0x2
#define HWIO_TLMM_CHIP_MODE_MODE1_PIN_SHFT                                  0x1
#define HWIO_TLMM_CHIP_MODE_MODE0_PIN_BMSK                                  0x1
#define HWIO_TLMM_CHIP_MODE_MODE0_PIN_SHFT                                  0x0

#define HWIO_TLMM_HW_REVISION_NUMBER_ADDR                            (TLMM_CSR_REG_BASE      + 0x00a30004)
#define HWIO_TLMM_HW_REVISION_NUMBER_OFFS                            (TLMM_CSR_REG_BASE_OFFS + 0x00a30004)
#define HWIO_TLMM_HW_REVISION_NUMBER_RMSK                            0xffffffff
#define HWIO_TLMM_HW_REVISION_NUMBER_IN          \
        in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_ADDR, HWIO_TLMM_HW_REVISION_NUMBER_RMSK)
#define HWIO_TLMM_HW_REVISION_NUMBER_INM(m)      \
        in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_BMSK                 0xf0000000
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_SHFT                       0x1c
#define HWIO_TLMM_HW_REVISION_NUMBER_PARTNUM_BMSK                     0xffff000
#define HWIO_TLMM_HW_REVISION_NUMBER_PARTNUM_SHFT                           0xc
#define HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_BMSK                 0xffe
#define HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_SHFT                   0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_START_BIT_BMSK                         0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_START_BIT_SHFT                         0x0

#define HWIO_TLMM_PHASE_FLAGS_ADDR                                   (TLMM_CSR_REG_BASE      + 0x00a30008)
#define HWIO_TLMM_PHASE_FLAGS_OFFS                                   (TLMM_CSR_REG_BASE_OFFS + 0x00a30008)
#define HWIO_TLMM_PHASE_FLAGS_RMSK                                   0xffffffff
#define HWIO_TLMM_PHASE_FLAGS_IN          \
        in_dword_masked(HWIO_TLMM_PHASE_FLAGS_ADDR, HWIO_TLMM_PHASE_FLAGS_RMSK)
#define HWIO_TLMM_PHASE_FLAGS_INM(m)      \
        in_dword_masked(HWIO_TLMM_PHASE_FLAGS_ADDR, m)
#define HWIO_TLMM_PHASE_FLAGS_OUT(v)      \
        out_dword(HWIO_TLMM_PHASE_FLAGS_ADDR,v)
#define HWIO_TLMM_PHASE_FLAGS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_PHASE_FLAGS_ADDR,m,v,HWIO_TLMM_PHASE_FLAGS_IN)
#define HWIO_TLMM_PHASE_FLAGS_PHASE_FLAG_BMSK                        0xffffffff
#define HWIO_TLMM_PHASE_FLAGS_PHASE_FLAG_SHFT                               0x0


#endif /* __HALTLMMHWIO_H__ */
