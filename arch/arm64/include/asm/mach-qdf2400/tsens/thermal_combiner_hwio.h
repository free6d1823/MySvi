/*
 * =====================================================================================
 *
 *       Filename:  thermal_combiner_hwio.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  09/26/2018 04:34:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *
 * =====================================================================================
 */
#ifndef __THERMAL_COMBINER_HWIO_H__
#define __THERMAL_COMBINER_HWIO_H__
/*
===========================================================================
*/
/**
  @file thermal_combiner_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r63.0]

  This file contains HWIO register definitions for the following modules:
    THERM_COMBINER

  'Include' filters applied:
  'Exclude' filters applied: RESERVED DUMMY
*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

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
#include <asm/mach-qdf2400/hal/HALtsens.h>
#include <asm/mach-qdf2400/hal/HALhwioTsens.h>

/*----------------------------------------------------------------------------
 * MODULE: THERM_COMBINER
 *--------------------------------------------------------------------------*/

#define THERM_COMBINER_REG_BASE                                            (TLMM_BASE      + 0x00af0000)

#define HWIO_TLMM_THERM_COMBINER_CFG1_ADDR                                 (THERM_COMBINER_REG_BASE      + 0x00000000)
#define HWIO_TLMM_THERM_COMBINER_CFG1_RMSK                                     0x3fff
#define HWIO_TLMM_THERM_COMBINER_CFG1_IN          \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_CFG1_ADDR, HWIO_TLMM_THERM_COMBINER_CFG1_RMSK)
#define HWIO_TLMM_THERM_COMBINER_CFG1_INM(m)      \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_CFG1_ADDR, m)
#define HWIO_TLMM_THERM_COMBINER_CFG1_OUT(v)      \
        out_dword(HWIO_TLMM_THERM_COMBINER_CFG1_ADDR,v)
#define HWIO_TLMM_THERM_COMBINER_CFG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_THERM_COMBINER_CFG1_ADDR,m,v,HWIO_TLMM_THERM_COMBINER_CFG1_IN)
#define HWIO_TLMM_THERM_COMBINER_CFG1_THERM_VALID_SEL_PWM_BMSK                 0x2000
#define HWIO_TLMM_THERM_COMBINER_CFG1_THERM_VALID_SEL_PWM_SHFT                    0xd
#define HWIO_TLMM_THERM_COMBINER_CFG1_PWMDIV16_BMSK                            0x1000
#define HWIO_TLMM_THERM_COMBINER_CFG1_PWMDIV16_SHFT                               0xc
#define HWIO_TLMM_THERM_COMBINER_CFG1_RAW_DATA_BMSK                             0x800
#define HWIO_TLMM_THERM_COMBINER_CFG1_RAW_DATA_SHFT                               0xb
#define HWIO_TLMM_THERM_COMBINER_CFG1_HOLD_BMSK                                 0x7fe
#define HWIO_TLMM_THERM_COMBINER_CFG1_HOLD_SHFT                                   0x1
#define HWIO_TLMM_THERM_COMBINER_CFG1_OUTSEL_BMSK                                 0x1
#define HWIO_TLMM_THERM_COMBINER_CFG1_OUTSEL_SHFT                                 0x0

#define HWIO_TLMM_THERM_COMBINER_CFG2_ADDR                                 (THERM_COMBINER_REG_BASE      + 0x00000004)
#define HWIO_TLMM_THERM_COMBINER_CFG2_RMSK                                      0x1ff
#define HWIO_TLMM_THERM_COMBINER_CFG2_IN          \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_CFG2_ADDR, HWIO_TLMM_THERM_COMBINER_CFG2_RMSK)
#define HWIO_TLMM_THERM_COMBINER_CFG2_INM(m)      \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_CFG2_ADDR, m)
#define HWIO_TLMM_THERM_COMBINER_CFG2_OUT(v)      \
        out_dword(HWIO_TLMM_THERM_COMBINER_CFG2_ADDR,v)
#define HWIO_TLMM_THERM_COMBINER_CFG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_THERM_COMBINER_CFG2_ADDR,m,v,HWIO_TLMM_THERM_COMBINER_CFG2_IN)
#define HWIO_TLMM_THERM_COMBINER_CFG2_GATE_THERM_CLK_BMSK                       0x100
#define HWIO_TLMM_THERM_COMBINER_CFG2_GATE_THERM_CLK_SHFT                         0x8
#define HWIO_TLMM_THERM_COMBINER_CFG2_RESET_BMSK                                 0x80
#define HWIO_TLMM_THERM_COMBINER_CFG2_RESET_SHFT                                  0x7
#define HWIO_TLMM_THERM_COMBINER_CFG2_CLKSEL_BMSK                                0x78
#define HWIO_TLMM_THERM_COMBINER_CFG2_CLKSEL_SHFT                                 0x3
#define HWIO_TLMM_THERM_COMBINER_CFG2_SPL_COND_BMSK                               0x7
#define HWIO_TLMM_THERM_COMBINER_CFG2_SPL_COND_SHFT                               0x0

#define HWIO_TLMM_THERM_COMBINER_CFG3_ADDR                                 (THERM_COMBINER_REG_BASE      + 0x00000008)
#define HWIO_TLMM_THERM_COMBINER_CFG3_RMSK                                  0x7ff03ff
#define HWIO_TLMM_THERM_COMBINER_CFG3_IN          \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_CFG3_ADDR, HWIO_TLMM_THERM_COMBINER_CFG3_RMSK)
#define HWIO_TLMM_THERM_COMBINER_CFG3_INM(m)      \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_CFG3_ADDR, m)
#define HWIO_TLMM_THERM_COMBINER_CFG3_OUT(v)      \
        out_dword(HWIO_TLMM_THERM_COMBINER_CFG3_ADDR,v)
#define HWIO_TLMM_THERM_COMBINER_CFG3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_THERM_COMBINER_CFG3_ADDR,m,v,HWIO_TLMM_THERM_COMBINER_CFG3_IN)
#define HWIO_TLMM_THERM_COMBINER_CFG3_PWM_DIVISOR_BMSK                      0x7ff0000
#define HWIO_TLMM_THERM_COMBINER_CFG3_PWM_DIVISOR_SHFT                           0x10
#define HWIO_TLMM_THERM_COMBINER_CFG3_PWM_SIGNED_OFFSET_BMSK                    0x3ff
#define HWIO_TLMM_THERM_COMBINER_CFG3_PWM_SIGNED_OFFSET_SHFT                      0x0

#define HWIO_TLMM_THERM_COMBINER_MAX_STATUS_ADDR                           (THERM_COMBINER_REG_BASE      + 0x0000000c)
#define HWIO_TLMM_THERM_COMBINER_MAX_STATUS_RMSK                                0xfff
#define HWIO_TLMM_THERM_COMBINER_MAX_STATUS_IN          \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_MAX_STATUS_ADDR, HWIO_TLMM_THERM_COMBINER_MAX_STATUS_RMSK)
#define HWIO_TLMM_THERM_COMBINER_MAX_STATUS_INM(m)      \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_MAX_STATUS_ADDR, m)
#define HWIO_TLMM_THERM_COMBINER_MAX_STATUS_MAX_BMSK                            0xfff
#define HWIO_TLMM_THERM_COMBINER_MAX_STATUS_MAX_SHFT                              0x0

#define HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_ADDR                 (THERM_COMBINER_REG_BASE      + 0x00000010)
#define HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_RMSK                        0x1
#define HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_IN          \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_ADDR, HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_RMSK)
#define HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_INM(m)      \
        in_dword_masked(HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_ADDR, m)
#define HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_BYPASS_BMSK                 0x1
#define HWIO_TLMM_THERM_COMBINER_CLKSEL_BYPASS_STATUS_BYPASS_SHFT                 0x0


#endif /* __THERMAL_COMBINER_HWIO_H__ */
