#ifndef __HWIO_PCIE_CC_H__
#define __HWIO_PCIE_CC_H__
/*
===========================================================================
*/
/**
  @file hwio_pcie_cc.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r64.0]

  This file contains HWIO register definitions for the following modules:
    PCIE0_PCIE_CC_REG

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

/*----------------------------------------------------------------------------
 * MODULE: PCIE_CC_REG
 *--------------------------------------------------------------------------*/

#define PCIE_CC_REG_REG_BASE                                                          (PCIE0_PCIE_CC_BASE      + 0x00000000)
#define PCIE_CC_REG_REG_BASE_PHYS                                                     (PCIE0_PCIE_CC_BASE_PHYS + 0x00000000)
#define PCIE_CC_REG_REG_BASE_OFFS                                                     0x00000000

#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(x)                                       ((x) + 0x00000000)
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_PHYS(x)                                       ((x) + 0x00000000)
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_OFFS                                          (0x00000000)
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_RMSK                                                 0x3
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_PHY_FULL_ARES_BMSK                                   0x2
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_PHY_FULL_ARES_SHFT                                   0x1
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_PHY_WARM_ARES_BMSK                                   0x1
#define HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_PHY_WARM_ARES_SHFT                                   0x0

#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_ADDR(x)                                 ((x) + 0x00000004)
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_PHYS(x)                                 ((x) + 0x00000004)
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_OFFS                                    (0x00000004)
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_RMSK                                    0x80000001
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_CLK_OFF_BMSK                            0x80000000
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_CLK_OFF_SHFT                                  0x1f
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                          0x1
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_CLK_ENABLE_BMSK                                0x1
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_CLK_ENABLE_SHFT                                0x0
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                        0x0
#define HWIO_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                         0x1

#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_ADDR(x)                                         ((x) + 0x00000008)
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_PHYS(x)                                         ((x) + 0x00000008)
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_OFFS                                            (0x00000008)
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_RMSK                                                   0x1
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AA_MISC_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AA_MISC_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_AA_MISC_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_AA_MISC_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_AA_MISC_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK                                      0x1
#define HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_SHFT                                      0x0

#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(x)                                       ((x) + 0x00010000)
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_PHYS(x)                                       ((x) + 0x00010000)
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_OFFS                                          (0x00010000)
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_RMSK                                                 0x3
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_PHY_FULL_ARES_BMSK                                   0x2
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_PHY_FULL_ARES_SHFT                                   0x1
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_PHY_WARM_ARES_BMSK                                   0x1
#define HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_PHY_WARM_ARES_SHFT                                   0x0

#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_ADDR(x)                                 ((x) + 0x00010004)
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_PHYS(x)                                 ((x) + 0x00010004)
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_OFFS                                    (0x00010004)
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_RMSK                                    0x80000001
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_CLK_OFF_BMSK                            0x80000000
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_CLK_OFF_SHFT                                  0x1f
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                          0x1
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_CLK_ENABLE_BMSK                                0x1
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_CLK_ENABLE_SHFT                                0x0
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                        0x0
#define HWIO_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                         0x1

#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_ADDR(x)                                         ((x) + 0x00010008)
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_PHYS(x)                                         ((x) + 0x00010008)
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_OFFS                                            (0x00010008)
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_RMSK                                                   0x1
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AB_MISC_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_AB_MISC_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_AB_MISC_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_AB_MISC_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_AB_MISC_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_AB_MISC_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_CLK_REBUF_EN_BMSK                                      0x1
#define HWIO_PCIE_CC_PCIE_PHY_AB_MISC_CLK_REBUF_EN_SHFT                                      0x0

#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(x)                                        ((x) + 0x00020000)
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_PHYS(x)                                        ((x) + 0x00020000)
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_OFFS                                           (0x00020000)
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_RMSK                                                  0x3
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_B_RESETR_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_B_RESETR_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_PHY_FULL_ARES_BMSK                                    0x2
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_PHY_FULL_ARES_SHFT                                    0x1
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_PHY_WARM_ARES_BMSK                                    0x1
#define HWIO_PCIE_CC_PCIE_PHY_B_RESETR_PHY_WARM_ARES_SHFT                                    0x0

#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_ADDR(x)                                  ((x) + 0x00020004)
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_PHYS(x)                                  ((x) + 0x00020004)
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_OFFS                                     (0x00020004)
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_RMSK                                     0x80000001
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                            0x0
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                           0x1
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_CLK_ENABLE_SHFT                                 0x0
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                         0x0
#define HWIO_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                          0x1

#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_ADDR(x)                                          ((x) + 0x00020008)
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_PHYS(x)                                          ((x) + 0x00020008)
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_OFFS                                             (0x00020008)
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_RMSK                                                    0x1
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_B_MISC_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_B_MISC_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_B_MISC_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_B_MISC_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_B_MISC_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_B_MISC_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_CLK_REBUF_EN_BMSK                                       0x1
#define HWIO_PCIE_CC_PCIE_PHY_B_MISC_CLK_REBUF_EN_SHFT                                       0x0

#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(x)                                        ((x) + 0x00030000)
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_PHYS(x)                                        ((x) + 0x00030000)
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_OFFS                                           (0x00030000)
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_RMSK                                                  0x3
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_C_RESETR_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_C_RESETR_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_PHY_FULL_ARES_BMSK                                    0x2
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_PHY_FULL_ARES_SHFT                                    0x1
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_PHY_WARM_ARES_BMSK                                    0x1
#define HWIO_PCIE_CC_PCIE_PHY_C_RESETR_PHY_WARM_ARES_SHFT                                    0x0

#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_ADDR(x)                                  ((x) + 0x00030004)
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_PHYS(x)                                  ((x) + 0x00030004)
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_OFFS                                     (0x00030004)
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_RMSK                                     0x80000001
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                            0x0
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                           0x1
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_CLK_ENABLE_SHFT                                 0x0
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                         0x0
#define HWIO_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                          0x1

#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_ADDR(x)                                          ((x) + 0x00030008)
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_PHYS(x)                                          ((x) + 0x00030008)
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_OFFS                                             (0x00030008)
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_RMSK                                                    0x1
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_C_MISC_ADDR(x), HWIO_PCIE_CC_PCIE_PHY_C_MISC_RMSK)
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_PHY_C_MISC_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_PHY_C_MISC_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_PHY_C_MISC_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_PHY_C_MISC_IN(x))
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_CLK_REBUF_EN_BMSK                                       0x1
#define HWIO_PCIE_CC_PCIE_PHY_C_MISC_CLK_REBUF_EN_SHFT                                       0x0

#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(x)                                     ((x) + 0x00040004)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_PHYS(x)                                     ((x) + 0x00040004)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_OFFS                                        (0x00040004)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_RMSK                                        0x80000013
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ROOT_OFF_BMSK                               0x80000000
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ROOT_OFF_SHFT                                     0x1f
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                               0x10
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                0x4
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ROOT_EN_BMSK                                       0x2
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ROOT_EN_SHFT                                       0x1
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ROOT_EN_DISABLE_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ROOT_EN_ENABLE_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_UPDATE_BMSK                                        0x1
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_UPDATE_SHFT                                        0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_UPDATE_DISABLE_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_UPDATE_ENABLE_FVAL                                 0x1

#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(x)                                     ((x) + 0x00040008)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_PHYS(x)                                     ((x) + 0x00040008)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_OFFS                                        (0x00040008)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_RMSK                                             0x71f
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_BMSK                                     0x700
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SHFT                                       0x8
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SRC0_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SRC1_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SRC2_FVAL                                  0x2
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SRC3_FVAL                                  0x3
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SRC4_FVAL                                  0x4
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SRC5_FVAL                                  0x5
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SRC6_FVAL                                  0x6
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_SEL_SRC7_FVAL                                  0x7
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_BMSK                                      0x1f
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_SHFT                                       0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_BYPASS_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV1_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                                0x2
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV2_FVAL                                  0x3
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                                0x4
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV3_FVAL                                  0x5
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                                0x6
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV4_FVAL                                  0x7
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                                0x8
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV5_FVAL                                  0x9
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                                0xa
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV6_FVAL                                  0xb
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                                0xc
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV7_FVAL                                  0xd
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                                0xe
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV8_FVAL                                  0xf
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                               0x10
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV9_FVAL                                 0x11
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                               0x12
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV10_FVAL                                0x13
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                              0x14
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV11_FVAL                                0x15
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                              0x16
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV12_FVAL                                0x17
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                              0x18
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV13_FVAL                                0x19
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                              0x1a
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV14_FVAL                                0x1b
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                              0x1c
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV15_FVAL                                0x1d
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                              0x1e
#define HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_SRC_DIV_DIV16_FVAL                                0x1f

#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_ADDR(x)                                         ((x) + 0x0004000c)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_PHYS(x)                                         ((x) + 0x0004000c)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_OFFS                                            (0x0004000c)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_RMSK                                            0x80000001
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_CLK_OFF_CLOCKON_FVAL                                   0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_CLK_OFF_CLOCKOFF_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_CLK_ENABLE_SHFT                                        0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_CLK_ENABLE_DISABLE_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_A_PCLK_CBCR_CLK_ENABLE_ENABLE_FVAL                                 0x1

#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_ADDR(x)                                           ((x) + 0x00040010)
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_PHYS(x)                                           ((x) + 0x00040010)
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_OFFS                                              (0x00040010)
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_RMSK                                              0x80000001
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PHY_A_AUX_CBCR_ADDR(x), HWIO_PCIE_CC_PHY_A_AUX_CBCR_RMSK)
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PHY_A_AUX_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PHY_A_AUX_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PHY_A_AUX_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PHY_A_AUX_CBCR_IN(x))
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_CLK_OFF_CLOCKON_FVAL                                     0x0
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_CLK_OFF_CLOCKOFF_FVAL                                    0x1
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_CLK_ENABLE_SHFT                                          0x0
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_CLK_ENABLE_DISABLE_FVAL                                  0x0
#define HWIO_PCIE_CC_PHY_A_AUX_CBCR_CLK_ENABLE_ENABLE_FVAL                                   0x1

#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(x)                                     ((x) + 0x00050004)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_PHYS(x)                                     ((x) + 0x00050004)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_OFFS                                        (0x00050004)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_RMSK                                        0x80000013
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ROOT_OFF_BMSK                               0x80000000
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ROOT_OFF_SHFT                                     0x1f
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                               0x10
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                0x4
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ROOT_EN_BMSK                                       0x2
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ROOT_EN_SHFT                                       0x1
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ROOT_EN_DISABLE_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ROOT_EN_ENABLE_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_UPDATE_BMSK                                        0x1
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_UPDATE_SHFT                                        0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_UPDATE_DISABLE_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_UPDATE_ENABLE_FVAL                                 0x1

#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(x)                                     ((x) + 0x00050008)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_PHYS(x)                                     ((x) + 0x00050008)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_OFFS                                        (0x00050008)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_RMSK                                             0x71f
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_BMSK                                     0x700
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SHFT                                       0x8
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SRC0_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SRC1_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SRC2_FVAL                                  0x2
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SRC3_FVAL                                  0x3
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SRC4_FVAL                                  0x4
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SRC5_FVAL                                  0x5
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SRC6_FVAL                                  0x6
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_SEL_SRC7_FVAL                                  0x7
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_BMSK                                      0x1f
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_SHFT                                       0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_BYPASS_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV1_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                                0x2
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV2_FVAL                                  0x3
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                                0x4
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV3_FVAL                                  0x5
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                                0x6
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV4_FVAL                                  0x7
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                                0x8
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV5_FVAL                                  0x9
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                                0xa
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV6_FVAL                                  0xb
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                                0xc
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV7_FVAL                                  0xd
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                                0xe
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV8_FVAL                                  0xf
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                               0x10
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV9_FVAL                                 0x11
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                               0x12
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV10_FVAL                                0x13
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                              0x14
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV11_FVAL                                0x15
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                              0x16
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV12_FVAL                                0x17
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                              0x18
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV13_FVAL                                0x19
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                              0x1a
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV14_FVAL                                0x1b
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                              0x1c
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV15_FVAL                                0x1d
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                              0x1e
#define HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_SRC_DIV_DIV16_FVAL                                0x1f

#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_ADDR(x)                                         ((x) + 0x0005000c)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_PHYS(x)                                         ((x) + 0x0005000c)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_OFFS                                            (0x0005000c)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_RMSK                                            0x80000001
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_CLK_OFF_CLOCKON_FVAL                                   0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_CLK_OFF_CLOCKOFF_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_CLK_ENABLE_SHFT                                        0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_CLK_ENABLE_DISABLE_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_B_PCLK_CBCR_CLK_ENABLE_ENABLE_FVAL                                 0x1

#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_ADDR(x)                                           ((x) + 0x00050010)
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_PHYS(x)                                           ((x) + 0x00050010)
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_OFFS                                              (0x00050010)
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_RMSK                                              0x80000001
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PHY_B_AUX_CBCR_ADDR(x), HWIO_PCIE_CC_PHY_B_AUX_CBCR_RMSK)
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PHY_B_AUX_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PHY_B_AUX_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PHY_B_AUX_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PHY_B_AUX_CBCR_IN(x))
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_CLK_OFF_CLOCKON_FVAL                                     0x0
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_CLK_OFF_CLOCKOFF_FVAL                                    0x1
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_CLK_ENABLE_SHFT                                          0x0
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_CLK_ENABLE_DISABLE_FVAL                                  0x0
#define HWIO_PCIE_CC_PHY_B_AUX_CBCR_CLK_ENABLE_ENABLE_FVAL                                   0x1

#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(x)                                     ((x) + 0x00060004)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_PHYS(x)                                     ((x) + 0x00060004)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_OFFS                                        (0x00060004)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_RMSK                                        0x80000013
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ROOT_OFF_BMSK                               0x80000000
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ROOT_OFF_SHFT                                     0x1f
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                               0x10
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                0x4
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ROOT_EN_BMSK                                       0x2
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ROOT_EN_SHFT                                       0x1
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ROOT_EN_DISABLE_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ROOT_EN_ENABLE_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_UPDATE_BMSK                                        0x1
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_UPDATE_SHFT                                        0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_UPDATE_DISABLE_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_UPDATE_ENABLE_FVAL                                 0x1

#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(x)                                     ((x) + 0x00060008)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_PHYS(x)                                     ((x) + 0x00060008)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_OFFS                                        (0x00060008)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_RMSK                                             0x71f
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_BMSK                                     0x700
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SHFT                                       0x8
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SRC0_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SRC1_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SRC2_FVAL                                  0x2
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SRC3_FVAL                                  0x3
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SRC4_FVAL                                  0x4
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SRC5_FVAL                                  0x5
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SRC6_FVAL                                  0x6
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_SEL_SRC7_FVAL                                  0x7
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_BMSK                                      0x1f
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_SHFT                                       0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_BYPASS_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV1_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                                0x2
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV2_FVAL                                  0x3
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                                0x4
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV3_FVAL                                  0x5
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                                0x6
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV4_FVAL                                  0x7
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                                0x8
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV5_FVAL                                  0x9
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                                0xa
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV6_FVAL                                  0xb
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                                0xc
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV7_FVAL                                  0xd
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                                0xe
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV8_FVAL                                  0xf
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                               0x10
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV9_FVAL                                 0x11
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                               0x12
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV10_FVAL                                0x13
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                              0x14
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV11_FVAL                                0x15
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                              0x16
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV12_FVAL                                0x17
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                              0x18
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV13_FVAL                                0x19
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                              0x1a
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV14_FVAL                                0x1b
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                              0x1c
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV15_FVAL                                0x1d
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                              0x1e
#define HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_SRC_DIV_DIV16_FVAL                                0x1f

#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_ADDR(x)                                         ((x) + 0x0006000c)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_PHYS(x)                                         ((x) + 0x0006000c)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_OFFS                                            (0x0006000c)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_RMSK                                            0x80000001
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_CLK_OFF_CLOCKON_FVAL                                   0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_CLK_OFF_CLOCKOFF_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_CLK_ENABLE_SHFT                                        0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_CLK_ENABLE_DISABLE_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_C_PCLK_CBCR_CLK_ENABLE_ENABLE_FVAL                                 0x1

#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_ADDR(x)                                           ((x) + 0x00060010)
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_PHYS(x)                                           ((x) + 0x00060010)
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_OFFS                                              (0x00060010)
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_RMSK                                              0x80000001
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PHY_C_AUX_CBCR_ADDR(x), HWIO_PCIE_CC_PHY_C_AUX_CBCR_RMSK)
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PHY_C_AUX_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PHY_C_AUX_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PHY_C_AUX_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PHY_C_AUX_CBCR_IN(x))
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_CLK_OFF_CLOCKON_FVAL                                     0x0
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_CLK_OFF_CLOCKOFF_FVAL                                    0x1
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_CLK_ENABLE_SHFT                                          0x0
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_CLK_ENABLE_DISABLE_FVAL                                  0x0
#define HWIO_PCIE_CC_PHY_C_AUX_CBCR_CLK_ENABLE_ENABLE_FVAL                                   0x1

#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ADDR(x)                                       ((x) + 0x00070004)
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_PHYS(x)                                       ((x) + 0x00070004)
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_OFFS                                          (0x00070004)
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_RMSK                                          0x80000013
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ROOT_OFF_BMSK                                 0x80000000
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ROOT_OFF_SHFT                                       0x1f
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                               0x1
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                 0x10
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                  0x4
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ROOT_EN_BMSK                                         0x2
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ROOT_EN_SHFT                                         0x1
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ROOT_EN_DISABLE_FVAL                                 0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_ROOT_EN_ENABLE_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_UPDATE_BMSK                                          0x1
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_UPDATE_SHFT                                          0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_UPDATE_DISABLE_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CMD_RCGR_UPDATE_ENABLE_FVAL                                   0x1

#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_ADDR(x)                                       ((x) + 0x00070008)
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_PHYS(x)                                       ((x) + 0x00070008)
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_OFFS                                          (0x00070008)
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_RMSK                                               0x71f
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_BMSK                                       0x700
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SHFT                                         0x8
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SRC0_FVAL                                    0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SRC1_FVAL                                    0x1
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SRC2_FVAL                                    0x2
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SRC3_FVAL                                    0x3
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SRC4_FVAL                                    0x4
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SRC5_FVAL                                    0x5
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SRC6_FVAL                                    0x6
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_SEL_SRC7_FVAL                                    0x7
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_BMSK                                        0x1f
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_SHFT                                         0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_BYPASS_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV1_FVAL                                    0x1
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                                  0x2
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV2_FVAL                                    0x3
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                                  0x4
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV3_FVAL                                    0x5
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                                  0x6
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV4_FVAL                                    0x7
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                                  0x8
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV5_FVAL                                    0x9
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                                  0xa
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV6_FVAL                                    0xb
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                                  0xc
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV7_FVAL                                    0xd
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                                  0xe
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV8_FVAL                                    0xf
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                                 0x10
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV9_FVAL                                   0x11
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                                 0x12
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV10_FVAL                                  0x13
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                                0x14
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV11_FVAL                                  0x15
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                                0x16
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV12_FVAL                                  0x17
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                                0x18
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV13_FVAL                                  0x19
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                                0x1a
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV14_FVAL                                  0x1b
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                                0x1c
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV15_FVAL                                  0x1d
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                                0x1e
#define HWIO_PCIE_CC_PCIE_SFPB_CFG_RCGR_SRC_DIV_DIV16_FVAL                                  0x1f

#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_ADDR(x)                                 ((x) + 0x0007000c)
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_PHYS(x)                                 ((x) + 0x0007000c)
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_OFFS                                    (0x0007000c)
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_RMSK                                    0x80000001
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_CLK_OFF_BMSK                            0x80000000
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_CLK_OFF_SHFT                                  0x1f
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_CLK_OFF_CLOCKON_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_CLK_OFF_CLOCKOFF_FVAL                          0x1
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_CLK_ENABLE_BMSK                                0x1
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_CLK_ENABLE_SHFT                                0x0
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_CLK_ENABLE_DISABLE_FVAL                        0x0
#define HWIO_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_CLK_ENABLE_ENABLE_FVAL                         0x1

#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_ADDR(x)                                           ((x) + 0x00070010)
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_PHYS(x)                                           ((x) + 0x00070010)
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_OFFS                                              (0x00070010)
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_RMSK                                              0x80000001
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_SFPB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_SFPB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_SFPB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_SFPB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_SFPB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_SFPB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_CLK_OFF_CLOCKON_FVAL                                     0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_CLK_OFF_CLOCKOFF_FVAL                                    0x1
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_CLK_ENABLE_SHFT                                          0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_CLK_ENABLE_DISABLE_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_SFPB_CBCR_CLK_ENABLE_ENABLE_FVAL                                   0x1

#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ADDR(x)                                ((x) + 0x00080004)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_PHYS(x)                                ((x) + 0x00080004)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_OFFS                                   (0x00080004)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_RMSK                                   0x80000013
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ROOT_OFF_BMSK                          0x80000000
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ROOT_OFF_SHFT                                0x1f
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                         0x0
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                        0x1
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                          0x10
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                           0x4
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ROOT_EN_BMSK                                  0x2
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ROOT_EN_SHFT                                  0x1
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ROOT_EN_DISABLE_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_ROOT_EN_ENABLE_FVAL                           0x1
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_UPDATE_BMSK                                   0x1
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_UPDATE_SHFT                                   0x0
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_UPDATE_DISABLE_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CMD_RCGR_UPDATE_ENABLE_FVAL                            0x1

#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_ADDR(x)                                ((x) + 0x00080008)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_PHYS(x)                                ((x) + 0x00080008)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_OFFS                                   (0x00080008)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_RMSK                                        0x71f
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_BMSK                                0x700
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SHFT                                  0x8
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC0_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC1_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC2_FVAL                             0x2
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC3_FVAL                             0x3
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC4_FVAL                             0x4
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC5_FVAL                             0x5
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC6_FVAL                             0x6
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC7_FVAL                             0x7
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_BMSK                                 0x1f
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_SHFT                                  0x0
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_BYPASS_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV1_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                           0x2
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV2_FVAL                             0x3
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                           0x4
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV3_FVAL                             0x5
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                           0x6
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV4_FVAL                             0x7
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                           0x8
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV5_FVAL                             0x9
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                           0xa
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV6_FVAL                             0xb
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                           0xc
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV7_FVAL                             0xd
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                           0xe
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV8_FVAL                             0xf
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                          0x10
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV9_FVAL                            0x11
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                          0x12
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV10_FVAL                           0x13
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                         0x14
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV11_FVAL                           0x15
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                         0x16
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV12_FVAL                           0x17
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                         0x18
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV13_FVAL                           0x19
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                         0x1a
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV14_FVAL                           0x1b
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                         0x1c
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV15_FVAL                           0x1d
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                         0x1e
#define HWIO_PCIE_CC_PCIE_X8_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV16_FVAL                           0x1f

#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ADDR(x)                                 ((x) + 0x00090004)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_PHYS(x)                                 ((x) + 0x00090004)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_OFFS                                    (0x00090004)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_RMSK                                    0x80000013
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ROOT_OFF_BMSK                           0x80000000
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ROOT_OFF_SHFT                                 0x1f
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                         0x1
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                           0x10
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                            0x4
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ROOT_EN_BMSK                                   0x2
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ROOT_EN_SHFT                                   0x1
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ROOT_EN_DISABLE_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_ROOT_EN_ENABLE_FVAL                            0x1
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_UPDATE_BMSK                                    0x1
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_UPDATE_SHFT                                    0x0
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_UPDATE_DISABLE_FVAL                            0x0
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CMD_RCGR_UPDATE_ENABLE_FVAL                             0x1

#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_ADDR(x)                                 ((x) + 0x00090008)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_PHYS(x)                                 ((x) + 0x00090008)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_OFFS                                    (0x00090008)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_RMSK                                         0x71f
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_BMSK                                 0x700
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SHFT                                   0x8
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SRC0_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SRC1_FVAL                              0x1
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SRC2_FVAL                              0x2
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SRC3_FVAL                              0x3
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SRC4_FVAL                              0x4
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SRC5_FVAL                              0x5
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SRC6_FVAL                              0x6
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_SEL_SRC7_FVAL                              0x7
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_BMSK                                  0x1f
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_SHFT                                   0x0
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_BYPASS_FVAL                            0x0
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV1_FVAL                              0x1
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                            0x2
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV2_FVAL                              0x3
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                            0x4
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV3_FVAL                              0x5
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                            0x6
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV4_FVAL                              0x7
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                            0x8
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV5_FVAL                              0x9
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                            0xa
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV6_FVAL                              0xb
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                            0xc
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV7_FVAL                              0xd
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                            0xe
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV8_FVAL                              0xf
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                           0x10
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV9_FVAL                             0x11
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                           0x12
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV10_FVAL                            0x13
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                          0x14
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV11_FVAL                            0x15
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                          0x16
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV12_FVAL                            0x17
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                          0x18
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV13_FVAL                            0x19
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                          0x1a
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV14_FVAL                            0x1b
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                          0x1c
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV15_FVAL                            0x1d
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                          0x1e
#define HWIO_PCIE_CC_PCIE_X8_SLV_Q23_CFG_RCGR_SRC_DIV_DIV16_FVAL                            0x1f

#define HWIO_PCIE_CC_PCIE_X8_0_BCR_ADDR(x)                                            ((x) + 0x00100000)
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_PHYS(x)                                            ((x) + 0x00100000)
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_OFFS                                               (0x00100000)
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_RMSK                                                      0x1
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_BCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_BCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_BCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_BCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_BCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_BCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_BLK_ARES_BMSK                                             0x1
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_BLK_ARES_SHFT                                             0x0
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_BLK_ARES_DISABLE_FVAL                                     0x0
#define HWIO_PCIE_CC_PCIE_X8_0_BCR_BLK_ARES_ENABLE_FVAL                                      0x1

#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_ADDR(x)                                         ((x) + 0x00100004)
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_PHYS(x)                                         ((x) + 0x00100004)
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_OFFS                                            (0x00100004)
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_RMSK                                                  0x7f
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_RESETR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_RESETR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_RESETR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_RESETR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_RESETR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_RESETR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_MMU_BMSK                                              0x40
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_MMU_SHFT                                               0x6
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_LINK_DOWN_BMSK                                        0x20
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_LINK_DOWN_SHFT                                         0x5
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_PWR_BMSK                                              0x10
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_PWR_SHFT                                               0x4
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_CORE_BMSK                                              0x8
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_CORE_SHFT                                              0x3
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_STICKY_BMSK                                            0x4
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_STICKY_SHFT                                            0x2
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_QSB_BMSK                                               0x2
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_QSB_SHFT                                               0x1
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_AHB_BMSK                                               0x1
#define HWIO_PCIE_CC_PCIE_X8_0_RESETR_AHB_SHFT                                               0x0

#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_ADDR(x)                                       ((x) + 0x00100008)
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_PHYS(x)                                       ((x) + 0x00100008)
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_OFFS                                          (0x00100008)
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_RMSK                                          0x80000001
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                                 0x0
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_ENABLE_SHFT                                      0x0
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                               0x1

#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_ADDR(x)                                       ((x) + 0x0010000c)
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_PHYS(x)                                       ((x) + 0x0010000c)
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_OFFS                                          (0x0010000c)
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_RMSK                                          0x80000001
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_OFF_CLOCKON_FVAL                                 0x0
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_OFF_CLOCKOFF_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_ENABLE_SHFT                                      0x0
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_ENABLE_DISABLE_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_ENABLE_ENABLE_FVAL                               0x1

#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_ADDR(x)                                   ((x) + 0x00100010)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_PHYS(x)                                   ((x) + 0x00100010)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_OFFS                                      (0x00100010)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_RMSK                                      0x80000001
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                            0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_ENABLE_SHFT                                  0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                           0x1

#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_ADDR(x)                              ((x) + 0x00100014)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_PHYS(x)                              ((x) + 0x00100014)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_OFFS                                 (0x00100014)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_RMSK                                 0x80000001
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_OFF_BMSK                         0x80000000
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_OFF_SHFT                               0x1f
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                        0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                       0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_ENABLE_BMSK                             0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_ENABLE_SHFT                             0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                     0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                      0x1

#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_ADDR(x)                                  ((x) + 0x00100018)
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_PHYS(x)                                  ((x) + 0x00100018)
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_OFFS                                     (0x00100018)
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_RMSK                                     0x80007ff1
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                            0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                           0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_BMSK                       0x4000
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_SHFT                          0xe
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL            0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL             0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_BMSK                     0x2000
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_SHFT                        0xd
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL          0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL           0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                    0x1000
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                       0xc
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL         0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL          0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_BMSK                                   0xf00
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_SHFT                                     0x8
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK0_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK1_FVAL                              0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK2_FVAL                              0x2
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK3_FVAL                              0x3
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK4_FVAL                              0x4
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK5_FVAL                              0x5
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK6_FVAL                              0x6
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK7_FVAL                              0x7
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK8_FVAL                              0x8
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK9_FVAL                              0x9
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK10_FVAL                             0xa
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK11_FVAL                             0xb
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK12_FVAL                             0xc
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK13_FVAL                             0xd
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK14_FVAL                             0xe
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_WAKEUP_CLOCK15_FVAL                             0xf
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_BMSK                                     0xf0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_SHFT                                      0x4
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK0_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK1_FVAL                               0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK2_FVAL                               0x2
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK3_FVAL                               0x3
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK4_FVAL                               0x4
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK5_FVAL                               0x5
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK6_FVAL                               0x6
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK7_FVAL                               0x7
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK8_FVAL                               0x8
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK9_FVAL                               0x9
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK10_FVAL                              0xa
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK11_FVAL                              0xb
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK12_FVAL                              0xc
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK13_FVAL                              0xd
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK14_FVAL                              0xe
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_SLEEP_CLOCK15_FVAL                              0xf
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_ENABLE_SHFT                                 0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                         0x0
#define HWIO_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                          0x1

#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_ADDR(x)                                   ((x) + 0x0010001c)
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_PHYS(x)                                   ((x) + 0x0010001c)
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_OFFS                                      (0x0010001c)
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_RMSK                                      0x80007ff1
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                            0x1
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL             0x0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL              0x1
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL           0x0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL            0x1
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL          0x0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL           0x1
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK0_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK1_FVAL                               0x1
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK2_FVAL                               0x2
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK3_FVAL                               0x3
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK4_FVAL                               0x4
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK5_FVAL                               0x5
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK6_FVAL                               0x6
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK7_FVAL                               0x7
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK8_FVAL                               0x8
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK9_FVAL                               0x9
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK10_FVAL                              0xa
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK11_FVAL                              0xb
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK12_FVAL                              0xc
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK13_FVAL                              0xd
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK14_FVAL                              0xe
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_WAKEUP_CLOCK15_FVAL                              0xf
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK0_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK1_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK2_FVAL                                0x2
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK3_FVAL                                0x3
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK4_FVAL                                0x4
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK5_FVAL                                0x5
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK6_FVAL                                0x6
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK7_FVAL                                0x7
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK8_FVAL                                0x8
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK9_FVAL                                0x9
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK10_FVAL                               0xa
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK11_FVAL                               0xb
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK12_FVAL                               0xc
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK13_FVAL                               0xd
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK14_FVAL                               0xe
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_SLEEP_CLOCK15_FVAL                               0xf
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_ENABLE_SHFT                                  0x0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                           0x1

#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_ADDR(x)                                      ((x) + 0x00100020)
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_PHYS(x)                                      ((x) + 0x00100020)
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_OFFS                                         (0x00100020)
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_RMSK                                         0x80007ff1
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_OFF_CLOCKON_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_OFF_CLOCKOFF_FVAL                               0x1
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL                0x0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL                 0x1
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL              0x0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL               0x1
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL             0x0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL              0x1
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK0_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK1_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK2_FVAL                                  0x2
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK3_FVAL                                  0x3
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK4_FVAL                                  0x4
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK5_FVAL                                  0x5
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK6_FVAL                                  0x6
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK7_FVAL                                  0x7
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK8_FVAL                                  0x8
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK9_FVAL                                  0x9
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK10_FVAL                                 0xa
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK11_FVAL                                 0xb
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK12_FVAL                                 0xc
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK13_FVAL                                 0xd
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK14_FVAL                                 0xe
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_WAKEUP_CLOCK15_FVAL                                 0xf
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK0_FVAL                                   0x0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK1_FVAL                                   0x1
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK2_FVAL                                   0x2
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK3_FVAL                                   0x3
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK4_FVAL                                   0x4
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK5_FVAL                                   0x5
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK6_FVAL                                   0x6
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK7_FVAL                                   0x7
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK8_FVAL                                   0x8
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK9_FVAL                                   0x9
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK10_FVAL                                  0xa
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK11_FVAL                                  0xb
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK12_FVAL                                  0xc
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK13_FVAL                                  0xd
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK14_FVAL                                  0xe
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_SLEEP_CLOCK15_FVAL                                  0xf
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_ENABLE_SHFT                                     0x0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_ENABLE_DISABLE_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_ENABLE_ENABLE_FVAL                              0x1

#define HWIO_PCIE_CC_PCIE_X8_1_BCR_ADDR(x)                                            ((x) + 0x00110000)
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_PHYS(x)                                            ((x) + 0x00110000)
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_OFFS                                               (0x00110000)
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_RMSK                                                      0x1
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_BCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_BCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_BCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_BCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_BCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_BCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_BLK_ARES_BMSK                                             0x1
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_BLK_ARES_SHFT                                             0x0
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_BLK_ARES_DISABLE_FVAL                                     0x0
#define HWIO_PCIE_CC_PCIE_X8_1_BCR_BLK_ARES_ENABLE_FVAL                                      0x1

#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_ADDR(x)                                         ((x) + 0x00110004)
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_PHYS(x)                                         ((x) + 0x00110004)
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_OFFS                                            (0x00110004)
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_RMSK                                                  0x7f
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_RESETR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_RESETR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_RESETR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_RESETR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_RESETR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_RESETR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_MMU_BMSK                                              0x40
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_MMU_SHFT                                               0x6
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_LINK_DOWN_BMSK                                        0x20
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_LINK_DOWN_SHFT                                         0x5
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_PWR_BMSK                                              0x10
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_PWR_SHFT                                               0x4
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_CORE_BMSK                                              0x8
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_CORE_SHFT                                              0x3
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_STICKY_BMSK                                            0x4
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_STICKY_SHFT                                            0x2
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_QSB_BMSK                                               0x2
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_QSB_SHFT                                               0x1
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_AHB_BMSK                                               0x1
#define HWIO_PCIE_CC_PCIE_X8_1_RESETR_AHB_SHFT                                               0x0

#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_ADDR(x)                                       ((x) + 0x00110008)
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_PHYS(x)                                       ((x) + 0x00110008)
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_OFFS                                          (0x00110008)
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_RMSK                                          0x80000001
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                                 0x0
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_ENABLE_SHFT                                      0x0
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                               0x1

#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_ADDR(x)                                       ((x) + 0x0011000c)
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_PHYS(x)                                       ((x) + 0x0011000c)
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_OFFS                                          (0x0011000c)
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_RMSK                                          0x80000001
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_OFF_CLOCKON_FVAL                                 0x0
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_OFF_CLOCKOFF_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_ENABLE_SHFT                                      0x0
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_ENABLE_DISABLE_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_ENABLE_ENABLE_FVAL                               0x1

#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_ADDR(x)                                   ((x) + 0x00110010)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_PHYS(x)                                   ((x) + 0x00110010)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_OFFS                                      (0x00110010)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_RMSK                                      0x80000001
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                            0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_ENABLE_SHFT                                  0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                           0x1

#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_ADDR(x)                              ((x) + 0x00110014)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_PHYS(x)                              ((x) + 0x00110014)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_OFFS                                 (0x00110014)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_RMSK                                 0x80000001
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_OFF_BMSK                         0x80000000
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_OFF_SHFT                               0x1f
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                        0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                       0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_ENABLE_BMSK                             0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_ENABLE_SHFT                             0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                     0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                      0x1

#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_ADDR(x)                                  ((x) + 0x00110018)
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_PHYS(x)                                  ((x) + 0x00110018)
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_OFFS                                     (0x00110018)
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_RMSK                                     0x80007ff1
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                            0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                           0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_BMSK                       0x4000
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_SHFT                          0xe
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL            0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL             0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_BMSK                     0x2000
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_SHFT                        0xd
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL          0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL           0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                    0x1000
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                       0xc
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL         0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL          0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_BMSK                                   0xf00
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_SHFT                                     0x8
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK0_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK1_FVAL                              0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK2_FVAL                              0x2
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK3_FVAL                              0x3
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK4_FVAL                              0x4
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK5_FVAL                              0x5
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK6_FVAL                              0x6
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK7_FVAL                              0x7
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK8_FVAL                              0x8
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK9_FVAL                              0x9
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK10_FVAL                             0xa
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK11_FVAL                             0xb
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK12_FVAL                             0xc
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK13_FVAL                             0xd
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK14_FVAL                             0xe
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_WAKEUP_CLOCK15_FVAL                             0xf
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_BMSK                                     0xf0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_SHFT                                      0x4
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK0_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK1_FVAL                               0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK2_FVAL                               0x2
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK3_FVAL                               0x3
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK4_FVAL                               0x4
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK5_FVAL                               0x5
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK6_FVAL                               0x6
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK7_FVAL                               0x7
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK8_FVAL                               0x8
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK9_FVAL                               0x9
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK10_FVAL                              0xa
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK11_FVAL                              0xb
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK12_FVAL                              0xc
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK13_FVAL                              0xd
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK14_FVAL                              0xe
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_SLEEP_CLOCK15_FVAL                              0xf
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_ENABLE_SHFT                                 0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                         0x0
#define HWIO_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                          0x1

#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_ADDR(x)                                   ((x) + 0x0011001c)
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_PHYS(x)                                   ((x) + 0x0011001c)
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_OFFS                                      (0x0011001c)
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_RMSK                                      0x80007ff1
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                            0x1
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL             0x0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL              0x1
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL           0x0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL            0x1
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL          0x0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL           0x1
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK0_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK1_FVAL                               0x1
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK2_FVAL                               0x2
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK3_FVAL                               0x3
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK4_FVAL                               0x4
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK5_FVAL                               0x5
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK6_FVAL                               0x6
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK7_FVAL                               0x7
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK8_FVAL                               0x8
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK9_FVAL                               0x9
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK10_FVAL                              0xa
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK11_FVAL                              0xb
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK12_FVAL                              0xc
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK13_FVAL                              0xd
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK14_FVAL                              0xe
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_WAKEUP_CLOCK15_FVAL                              0xf
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK0_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK1_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK2_FVAL                                0x2
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK3_FVAL                                0x3
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK4_FVAL                                0x4
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK5_FVAL                                0x5
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK6_FVAL                                0x6
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK7_FVAL                                0x7
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK8_FVAL                                0x8
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK9_FVAL                                0x9
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK10_FVAL                               0xa
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK11_FVAL                               0xb
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK12_FVAL                               0xc
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK13_FVAL                               0xd
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK14_FVAL                               0xe
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_SLEEP_CLOCK15_FVAL                               0xf
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_ENABLE_SHFT                                  0x0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                           0x1

#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_ADDR(x)                                      ((x) + 0x00110020)
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_PHYS(x)                                      ((x) + 0x00110020)
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_OFFS                                         (0x00110020)
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_RMSK                                         0x80007ff1
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_OFF_CLOCKON_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_OFF_CLOCKOFF_FVAL                               0x1
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL                0x0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL                 0x1
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL              0x0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL               0x1
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL             0x0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL              0x1
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK0_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK1_FVAL                                  0x1
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK2_FVAL                                  0x2
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK3_FVAL                                  0x3
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK4_FVAL                                  0x4
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK5_FVAL                                  0x5
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK6_FVAL                                  0x6
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK7_FVAL                                  0x7
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK8_FVAL                                  0x8
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK9_FVAL                                  0x9
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK10_FVAL                                 0xa
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK11_FVAL                                 0xb
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK12_FVAL                                 0xc
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK13_FVAL                                 0xd
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK14_FVAL                                 0xe
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_WAKEUP_CLOCK15_FVAL                                 0xf
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK0_FVAL                                   0x0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK1_FVAL                                   0x1
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK2_FVAL                                   0x2
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK3_FVAL                                   0x3
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK4_FVAL                                   0x4
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK5_FVAL                                   0x5
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK6_FVAL                                   0x6
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK7_FVAL                                   0x7
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK8_FVAL                                   0x8
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK9_FVAL                                   0x9
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK10_FVAL                                  0xa
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK11_FVAL                                  0xb
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK12_FVAL                                  0xc
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK13_FVAL                                  0xd
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK14_FVAL                                  0xe
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_SLEEP_CLOCK15_FVAL                                  0xf
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_ENABLE_SHFT                                     0x0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_ENABLE_DISABLE_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_ENABLE_ENABLE_FVAL                              0x1

#define HWIO_PCIE_CC_PCIE_X16_BCR_ADDR(x)                                             ((x) + 0x00120000)
#define HWIO_PCIE_CC_PCIE_X16_BCR_PHYS(x)                                             ((x) + 0x00120000)
#define HWIO_PCIE_CC_PCIE_X16_BCR_OFFS                                                (0x00120000)
#define HWIO_PCIE_CC_PCIE_X16_BCR_RMSK                                                       0x1
#define HWIO_PCIE_CC_PCIE_X16_BCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_BCR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_BCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_BCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_BCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_BCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_BCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_BCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_BCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_BCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_BCR_BLK_ARES_BMSK                                              0x1
#define HWIO_PCIE_CC_PCIE_X16_BCR_BLK_ARES_SHFT                                              0x0
#define HWIO_PCIE_CC_PCIE_X16_BCR_BLK_ARES_DISABLE_FVAL                                      0x0
#define HWIO_PCIE_CC_PCIE_X16_BCR_BLK_ARES_ENABLE_FVAL                                       0x1

#define HWIO_PCIE_CC_PCIE_X16_RESETR_ADDR(x)                                          ((x) + 0x00120004)
#define HWIO_PCIE_CC_PCIE_X16_RESETR_PHYS(x)                                          ((x) + 0x00120004)
#define HWIO_PCIE_CC_PCIE_X16_RESETR_OFFS                                             (0x00120004)
#define HWIO_PCIE_CC_PCIE_X16_RESETR_RMSK                                                   0x7f
#define HWIO_PCIE_CC_PCIE_X16_RESETR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_RESETR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_RESETR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_RESETR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_RESETR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_RESETR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_RESETR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_RESETR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_RESETR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_RESETR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_RESETR_MMU_BMSK                                               0x40
#define HWIO_PCIE_CC_PCIE_X16_RESETR_MMU_SHFT                                                0x6
#define HWIO_PCIE_CC_PCIE_X16_RESETR_LINK_DOWN_BMSK                                         0x20
#define HWIO_PCIE_CC_PCIE_X16_RESETR_LINK_DOWN_SHFT                                          0x5
#define HWIO_PCIE_CC_PCIE_X16_RESETR_PWR_BMSK                                               0x10
#define HWIO_PCIE_CC_PCIE_X16_RESETR_PWR_SHFT                                                0x4
#define HWIO_PCIE_CC_PCIE_X16_RESETR_CORE_BMSK                                               0x8
#define HWIO_PCIE_CC_PCIE_X16_RESETR_CORE_SHFT                                               0x3
#define HWIO_PCIE_CC_PCIE_X16_RESETR_STICKY_BMSK                                             0x4
#define HWIO_PCIE_CC_PCIE_X16_RESETR_STICKY_SHFT                                             0x2
#define HWIO_PCIE_CC_PCIE_X16_RESETR_QSB_BMSK                                                0x2
#define HWIO_PCIE_CC_PCIE_X16_RESETR_QSB_SHFT                                                0x1
#define HWIO_PCIE_CC_PCIE_X16_RESETR_AHB_BMSK                                                0x1
#define HWIO_PCIE_CC_PCIE_X16_RESETR_AHB_SHFT                                                0x0

#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ADDR(x)                               ((x) + 0x00120014)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_PHYS(x)                               ((x) + 0x00120014)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_OFFS                                  (0x00120014)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_RMSK                                  0x80000013
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ROOT_OFF_BMSK                         0x80000000
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ROOT_OFF_SHFT                               0x1f
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                        0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                       0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                         0x10
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                          0x4
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ROOT_EN_BMSK                                 0x2
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ROOT_EN_SHFT                                 0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ROOT_EN_DISABLE_FVAL                         0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ROOT_EN_ENABLE_FVAL                          0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_UPDATE_BMSK                                  0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_UPDATE_SHFT                                  0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_UPDATE_DISABLE_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_UPDATE_ENABLE_FVAL                           0x1

#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_ADDR(x)                               ((x) + 0x00120018)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_PHYS(x)                               ((x) + 0x00120018)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_OFFS                                  (0x00120018)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_RMSK                                       0x71f
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_BMSK                               0x700
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SHFT                                 0x8
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC0_FVAL                            0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC1_FVAL                            0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC2_FVAL                            0x2
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC3_FVAL                            0x3
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC4_FVAL                            0x4
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC5_FVAL                            0x5
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC6_FVAL                            0x6
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_SEL_SRC7_FVAL                            0x7
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_BMSK                                0x1f
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_SHFT                                 0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_BYPASS_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV1_FVAL                            0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                          0x2
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV2_FVAL                            0x3
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                          0x4
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV3_FVAL                            0x5
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                          0x6
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV4_FVAL                            0x7
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                          0x8
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV5_FVAL                            0x9
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                          0xa
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV6_FVAL                            0xb
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                          0xc
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV7_FVAL                            0xd
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                          0xe
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV8_FVAL                            0xf
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                         0x10
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV9_FVAL                           0x11
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                         0x12
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV10_FVAL                          0x13
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                        0x14
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV11_FVAL                          0x15
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                        0x16
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV12_FVAL                          0x17
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                        0x18
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV13_FVAL                          0x19
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                        0x1a
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV14_FVAL                          0x1b
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                        0x1c
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV15_FVAL                          0x1d
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                        0x1e
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_SRC_DIV_DIV16_FVAL                          0x1f

#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ADDR(x)                                ((x) + 0x00120024)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_PHYS(x)                                ((x) + 0x00120024)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_OFFS                                   (0x00120024)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_RMSK                                   0x80000013
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ROOT_OFF_BMSK                          0x80000000
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ROOT_OFF_SHFT                                0x1f
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                         0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                        0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                          0x10
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                           0x4
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ROOT_EN_BMSK                                  0x2
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ROOT_EN_SHFT                                  0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ROOT_EN_DISABLE_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ROOT_EN_ENABLE_FVAL                           0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_UPDATE_BMSK                                   0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_UPDATE_SHFT                                   0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_UPDATE_DISABLE_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_UPDATE_ENABLE_FVAL                            0x1

#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_ADDR(x)                                ((x) + 0x00120028)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_PHYS(x)                                ((x) + 0x00120028)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_OFFS                                   (0x00120028)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_RMSK                                        0x71f
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_BMSK                                0x700
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SHFT                                  0x8
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SRC0_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SRC1_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SRC2_FVAL                             0x2
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SRC3_FVAL                             0x3
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SRC4_FVAL                             0x4
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SRC5_FVAL                             0x5
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SRC6_FVAL                             0x6
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_SEL_SRC7_FVAL                             0x7
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_BMSK                                 0x1f
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_SHFT                                  0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_BYPASS_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV1_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                           0x2
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV2_FVAL                             0x3
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                           0x4
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV3_FVAL                             0x5
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                           0x6
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV4_FVAL                             0x7
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                           0x8
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV5_FVAL                             0x9
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                           0xa
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV6_FVAL                             0xb
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                           0xc
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV7_FVAL                             0xd
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                           0xe
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV8_FVAL                             0xf
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                          0x10
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV9_FVAL                            0x11
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                          0x12
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV10_FVAL                           0x13
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                         0x14
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV11_FVAL                           0x15
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                         0x16
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV12_FVAL                           0x17
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                         0x18
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV13_FVAL                           0x19
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                         0x1a
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV14_FVAL                           0x1b
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                         0x1c
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV15_FVAL                           0x1d
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                         0x1e
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_SRC_DIV_DIV16_FVAL                           0x1f

#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_ADDR(x)                                        ((x) + 0x00120038)
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_PHYS(x)                                        ((x) + 0x00120038)
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_OFFS                                           (0x00120038)
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_RMSK                                           0x80000001
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                                 0x1
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_ENABLE_SHFT                                       0x0
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                                0x1

#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_ADDR(x)                                        ((x) + 0x0012003c)
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_PHYS(x)                                        ((x) + 0x0012003c)
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_OFFS                                           (0x0012003c)
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_RMSK                                           0x80000001
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_OFF_CLOCKON_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_OFF_CLOCKOFF_FVAL                                 0x1
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_ENABLE_SHFT                                       0x0
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_ENABLE_DISABLE_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_ENABLE_ENABLE_FVAL                                0x1

#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_ADDR(x)                                    ((x) + 0x00120040)
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_PHYS(x)                                    ((x) + 0x00120040)
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_OFFS                                       (0x00120040)
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_RMSK                                       0x80000001
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_OFF_BMSK                               0x80000000
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_OFF_SHFT                                     0x1f
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_OFF_CLOCKON_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_OFF_CLOCKOFF_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_ENABLE_BMSK                                   0x1
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_ENABLE_SHFT                                   0x0
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_ENABLE_DISABLE_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_ENABLE_ENABLE_FVAL                            0x1

#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_ADDR(x)                               ((x) + 0x00120044)
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_PHYS(x)                               ((x) + 0x00120044)
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_OFFS                                  (0x00120044)
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_RMSK                                  0x80000001
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_OFF_BMSK                          0x80000000
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_OFF_SHFT                                0x1f
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                         0x0
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                        0x1
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_ENABLE_BMSK                              0x1
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_ENABLE_SHFT                              0x0
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                      0x0
#define HWIO_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                       0x1

#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_ADDR(x)                                   ((x) + 0x00120048)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_PHYS(x)                                   ((x) + 0x00120048)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_OFFS                                      (0x00120048)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_RMSK                                      0x80007ff1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                             0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                            0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL             0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL              0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL           0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL            0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL          0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL           0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK0_FVAL                               0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK1_FVAL                               0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK2_FVAL                               0x2
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK3_FVAL                               0x3
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK4_FVAL                               0x4
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK5_FVAL                               0x5
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK6_FVAL                               0x6
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK7_FVAL                               0x7
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK8_FVAL                               0x8
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK9_FVAL                               0x9
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK10_FVAL                              0xa
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK11_FVAL                              0xb
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK12_FVAL                              0xc
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK13_FVAL                              0xd
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK14_FVAL                              0xe
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_WAKEUP_CLOCK15_FVAL                              0xf
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK0_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK1_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK2_FVAL                                0x2
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK3_FVAL                                0x3
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK4_FVAL                                0x4
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK5_FVAL                                0x5
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK6_FVAL                                0x6
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK7_FVAL                                0x7
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK8_FVAL                                0x8
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK9_FVAL                                0x9
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK10_FVAL                               0xa
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK11_FVAL                               0xb
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK12_FVAL                               0xc
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK13_FVAL                               0xd
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK14_FVAL                               0xe
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_SLEEP_CLOCK15_FVAL                               0xf
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_ENABLE_SHFT                                  0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                          0x0
#define HWIO_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                           0x1

#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_ADDR(x)                                    ((x) + 0x0012004c)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_PHYS(x)                                    ((x) + 0x0012004c)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_OFFS                                       (0x0012004c)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_RMSK                                       0x80007ff1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_OFF_BMSK                               0x80000000
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_OFF_SHFT                                     0x1f
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_OFF_CLOCKON_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_OFF_CLOCKOFF_FVAL                             0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_BMSK                         0x4000
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_SHFT                            0xe
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL              0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL               0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_BMSK                       0x2000
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_SHFT                          0xd
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL            0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL             0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                      0x1000
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                         0xc
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL           0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL            0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_BMSK                                     0xf00
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_SHFT                                       0x8
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK0_FVAL                                0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK1_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK2_FVAL                                0x2
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK3_FVAL                                0x3
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK4_FVAL                                0x4
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK5_FVAL                                0x5
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK6_FVAL                                0x6
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK7_FVAL                                0x7
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK8_FVAL                                0x8
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK9_FVAL                                0x9
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK10_FVAL                               0xa
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK11_FVAL                               0xb
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK12_FVAL                               0xc
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK13_FVAL                               0xd
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK14_FVAL                               0xe
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_WAKEUP_CLOCK15_FVAL                               0xf
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_BMSK                                       0xf0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_SHFT                                        0x4
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK0_FVAL                                 0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK1_FVAL                                 0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK2_FVAL                                 0x2
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK3_FVAL                                 0x3
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK4_FVAL                                 0x4
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK5_FVAL                                 0x5
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK6_FVAL                                 0x6
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK7_FVAL                                 0x7
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK8_FVAL                                 0x8
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK9_FVAL                                 0x9
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK10_FVAL                                0xa
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK11_FVAL                                0xb
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK12_FVAL                                0xc
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK13_FVAL                                0xd
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK14_FVAL                                0xe
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_SLEEP_CLOCK15_FVAL                                0xf
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_ENABLE_BMSK                                   0x1
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_ENABLE_SHFT                                   0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_ENABLE_DISABLE_FVAL                           0x0
#define HWIO_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_ENABLE_ENABLE_FVAL                            0x1

#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_ADDR(x)                                       ((x) + 0x00120050)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_PHYS(x)                                       ((x) + 0x00120050)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_OFFS                                          (0x00120050)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_RMSK                                          0x80007ff1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_OFF_CLOCKON_FVAL                                 0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_OFF_CLOCKOFF_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_CORE_ON_BMSK                            0x4000
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_CORE_ON_SHFT                               0xe
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_CORE_ON_FORCE_DISABLE_FVAL                 0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_CORE_ON_FORCE_ENABLE_FVAL                  0x1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_PERIPH_ON_BMSK                          0x2000
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_PERIPH_ON_SHFT                             0xd
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_PERIPH_ON_FORCE_DISABLE_FVAL               0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_PERIPH_ON_FORCE_ENABLE_FVAL                0x1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                         0x1000
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                            0xc
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_DISABLE_FVAL              0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_FORCE_MEM_PERIPH_OFF_FORCE_ENABLE_FVAL               0x1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_BMSK                                        0xf00
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_SHFT                                          0x8
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK0_FVAL                                   0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK1_FVAL                                   0x1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK2_FVAL                                   0x2
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK3_FVAL                                   0x3
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK4_FVAL                                   0x4
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK5_FVAL                                   0x5
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK6_FVAL                                   0x6
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK7_FVAL                                   0x7
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK8_FVAL                                   0x8
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK9_FVAL                                   0x9
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK10_FVAL                                  0xa
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK11_FVAL                                  0xb
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK12_FVAL                                  0xc
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK13_FVAL                                  0xd
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK14_FVAL                                  0xe
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_WAKEUP_CLOCK15_FVAL                                  0xf
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_BMSK                                          0xf0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_SHFT                                           0x4
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK0_FVAL                                    0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK1_FVAL                                    0x1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK2_FVAL                                    0x2
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK3_FVAL                                    0x3
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK4_FVAL                                    0x4
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK5_FVAL                                    0x5
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK6_FVAL                                    0x6
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK7_FVAL                                    0x7
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK8_FVAL                                    0x8
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK9_FVAL                                    0x9
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK10_FVAL                                   0xa
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK11_FVAL                                   0xb
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK12_FVAL                                   0xc
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK13_FVAL                                   0xd
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK14_FVAL                                   0xe
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_SLEEP_CLOCK15_FVAL                                   0xf
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_ENABLE_SHFT                                      0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_ENABLE_DISABLE_FVAL                              0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_ENABLE_ENABLE_FVAL                               0x1

#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(x)                                       ((x) + 0x0012005c)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_PHYS(x)                                       ((x) + 0x0012005c)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_OFFS                                          (0x0012005c)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_RMSK                                                 0x3
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(x), HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_RMSK)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_IN(x))
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_SEL_BMSK                                             0x3
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_SEL_SHFT                                             0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_SEL_A_FVAL                                           0x0
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_SEL_B_FVAL                                           0x1
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_SEL_C_FVAL                                           0x2
#define HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_SEL_D_FVAL                                           0x3

#define HWIO_PCIE_CC_PCIE_VBU_BCR_ADDR(x)                                             ((x) + 0x00130000)
#define HWIO_PCIE_CC_PCIE_VBU_BCR_PHYS(x)                                             ((x) + 0x00130000)
#define HWIO_PCIE_CC_PCIE_VBU_BCR_OFFS                                                (0x00130000)
#define HWIO_PCIE_CC_PCIE_VBU_BCR_RMSK                                                       0x1
#define HWIO_PCIE_CC_PCIE_VBU_BCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_VBU_BCR_ADDR(x), HWIO_PCIE_CC_PCIE_VBU_BCR_RMSK)
#define HWIO_PCIE_CC_PCIE_VBU_BCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_VBU_BCR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_VBU_BCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_VBU_BCR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_VBU_BCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_VBU_BCR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_VBU_BCR_IN(x))
#define HWIO_PCIE_CC_PCIE_VBU_BCR_BLK_ARES_BMSK                                              0x1
#define HWIO_PCIE_CC_PCIE_VBU_BCR_BLK_ARES_SHFT                                              0x0
#define HWIO_PCIE_CC_PCIE_VBU_BCR_BLK_ARES_DISABLE_FVAL                                      0x0
#define HWIO_PCIE_CC_PCIE_VBU_BCR_BLK_ARES_ENABLE_FVAL                                       0x1

#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_ADDR(x)                                         ((x) + 0x00130004)
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_PHYS(x)                                         ((x) + 0x00130004)
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_OFFS                                            (0x00130004)
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_RMSK                                            0x80000001
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_ADDR(x), HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_RMSK)
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_IN(x))
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_CLK_OFF_CLOCKON_FVAL                                   0x0
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_CLK_OFF_CLOCKOFF_FVAL                                  0x1
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_CLK_ENABLE_SHFT                                        0x0
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_CLK_ENABLE_DISABLE_FVAL                                0x0
#define HWIO_PCIE_CC_VBU_AHB_CFG_CBCR_CLK_ENABLE_ENABLE_FVAL                                 0x1

#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ADDR(x)                                        ((x) + 0x00140004)
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_PHYS(x)                                        ((x) + 0x00140004)
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_OFFS                                           (0x00140004)
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_RMSK                                           0x800000f3
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ROOT_OFF_BMSK                                  0x80000000
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ROOT_OFF_SHFT                                        0x1f
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ROOT_OFF_CLOCKON_FVAL                                 0x0
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ROOT_OFF_CLOCKOFF_FVAL                                0x1
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_DIRTY_D_BMSK                                         0x80
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_DIRTY_D_SHFT                                          0x7
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_DIRTY_M_BMSK                                         0x40
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_DIRTY_M_SHFT                                          0x6
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_DIRTY_N_BMSK                                         0x20
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_DIRTY_N_SHFT                                          0x5
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                  0x10
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                   0x4
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ROOT_EN_BMSK                                          0x2
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ROOT_EN_SHFT                                          0x1
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ROOT_EN_DISABLE_FVAL                                  0x0
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_ROOT_EN_ENABLE_FVAL                                   0x1
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_UPDATE_BMSK                                           0x1
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_UPDATE_SHFT                                           0x0
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_UPDATE_DISABLE_FVAL                                   0x0
#define HWIO_PCIE_CC_PCIE_AUX_CMD_RCGR_UPDATE_ENABLE_FVAL                                    0x1

#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_ADDR(x)                                        ((x) + 0x00140008)
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_PHYS(x)                                        ((x) + 0x00140008)
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_OFFS                                           (0x00140008)
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_RMSK                                               0x371f
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_ADDR(x), HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_RMSK)
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_IN(x))
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_MODE_BMSK                                          0x3000
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_MODE_SHFT                                             0xc
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_MODE_BYPASS_FVAL                                      0x0
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_MODE_SWALLOW_FVAL                                     0x1
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_MODE_DUAL_EDGE_FVAL                                   0x2
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_MODE_SINGLE_EDGE_FVAL                                 0x3
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_BMSK                                        0x700
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SHFT                                          0x8
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SRC0_FVAL                                     0x0
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SRC1_FVAL                                     0x1
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SRC2_FVAL                                     0x2
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SRC3_FVAL                                     0x3
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SRC4_FVAL                                     0x4
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SRC5_FVAL                                     0x5
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SRC6_FVAL                                     0x6
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_SEL_SRC7_FVAL                                     0x7
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_BMSK                                         0x1f
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_SHFT                                          0x0
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_BYPASS_FVAL                                   0x0
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV1_FVAL                                     0x1
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                                   0x2
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV2_FVAL                                     0x3
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                                   0x4
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV3_FVAL                                     0x5
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                                   0x6
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV4_FVAL                                     0x7
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                                   0x8
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV5_FVAL                                     0x9
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                                   0xa
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV6_FVAL                                     0xb
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                                   0xc
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV7_FVAL                                     0xd
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                                   0xe
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV8_FVAL                                     0xf
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                                  0x10
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV9_FVAL                                    0x11
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                                  0x12
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV10_FVAL                                   0x13
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                                 0x14
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV11_FVAL                                   0x15
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                                 0x16
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV12_FVAL                                   0x17
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                                 0x18
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV13_FVAL                                   0x19
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                                 0x1a
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV14_FVAL                                   0x1b
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                                 0x1c
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV15_FVAL                                   0x1d
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                                 0x1e
#define HWIO_PCIE_CC_PCIE_AUX_CFG_RCGR_SRC_DIV_DIV16_FVAL                                   0x1f

#define HWIO_PCIE_CC_PCIE_AUX_M_ADDR(x)                                               ((x) + 0x0014000c)
#define HWIO_PCIE_CC_PCIE_AUX_M_PHYS(x)                                               ((x) + 0x0014000c)
#define HWIO_PCIE_CC_PCIE_AUX_M_OFFS                                                  (0x0014000c)
#define HWIO_PCIE_CC_PCIE_AUX_M_RMSK                                                      0xffff
#define HWIO_PCIE_CC_PCIE_AUX_M_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_M_ADDR(x), HWIO_PCIE_CC_PCIE_AUX_M_RMSK)
#define HWIO_PCIE_CC_PCIE_AUX_M_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_M_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_AUX_M_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_AUX_M_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_AUX_M_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_AUX_M_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_AUX_M_IN(x))
#define HWIO_PCIE_CC_PCIE_AUX_M_M_BMSK                                                    0xffff
#define HWIO_PCIE_CC_PCIE_AUX_M_M_SHFT                                                       0x0

#define HWIO_PCIE_CC_PCIE_AUX_N_ADDR(x)                                               ((x) + 0x00140010)
#define HWIO_PCIE_CC_PCIE_AUX_N_PHYS(x)                                               ((x) + 0x00140010)
#define HWIO_PCIE_CC_PCIE_AUX_N_OFFS                                                  (0x00140010)
#define HWIO_PCIE_CC_PCIE_AUX_N_RMSK                                                      0xffff
#define HWIO_PCIE_CC_PCIE_AUX_N_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_N_ADDR(x), HWIO_PCIE_CC_PCIE_AUX_N_RMSK)
#define HWIO_PCIE_CC_PCIE_AUX_N_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_N_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_AUX_N_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_AUX_N_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_AUX_N_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_AUX_N_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_AUX_N_IN(x))
#define HWIO_PCIE_CC_PCIE_AUX_N_N_BMSK                                                    0xffff
#define HWIO_PCIE_CC_PCIE_AUX_N_N_SHFT                                                       0x0

#define HWIO_PCIE_CC_PCIE_AUX_D_ADDR(x)                                               ((x) + 0x00140014)
#define HWIO_PCIE_CC_PCIE_AUX_D_PHYS(x)                                               ((x) + 0x00140014)
#define HWIO_PCIE_CC_PCIE_AUX_D_OFFS                                                  (0x00140014)
#define HWIO_PCIE_CC_PCIE_AUX_D_RMSK                                                      0xffff
#define HWIO_PCIE_CC_PCIE_AUX_D_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_D_ADDR(x), HWIO_PCIE_CC_PCIE_AUX_D_RMSK)
#define HWIO_PCIE_CC_PCIE_AUX_D_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_AUX_D_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_AUX_D_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_AUX_D_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_AUX_D_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_AUX_D_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_AUX_D_IN(x))
#define HWIO_PCIE_CC_PCIE_AUX_D_D_BMSK                                                    0xffff
#define HWIO_PCIE_CC_PCIE_AUX_D_D_SHFT                                                       0x0

#define HWIO_PCIE_CC_IM_SLEEP_CBCR_ADDR(x)                                            ((x) + 0x00150004)
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_PHYS(x)                                            ((x) + 0x00150004)
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_OFFS                                               (0x00150004)
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_RMSK                                               0x80000001
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_IM_SLEEP_CBCR_ADDR(x), HWIO_PCIE_CC_IM_SLEEP_CBCR_RMSK)
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_IM_SLEEP_CBCR_ADDR(x), m)
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_IM_SLEEP_CBCR_ADDR(x),v)
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_IM_SLEEP_CBCR_ADDR(x),m,v,HWIO_PCIE_CC_IM_SLEEP_CBCR_IN(x))
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_CLK_OFF_CLOCKON_FVAL                                      0x0
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_CLK_OFF_CLOCKOFF_FVAL                                     0x1
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_CLK_ENABLE_SHFT                                           0x0
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_CLK_ENABLE_DISABLE_FVAL                                   0x0
#define HWIO_PCIE_CC_IM_SLEEP_CBCR_CLK_ENABLE_ENABLE_FVAL                                    0x1

#define HWIO_PCIE_CC_DEBUG_CLK_CTL_ADDR(x)                                            ((x) + 0x00160000)
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_PHYS(x)                                            ((x) + 0x00160000)
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_OFFS                                               (0x00160000)
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_RMSK                                                   0x3fff
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_DEBUG_CLK_CTL_ADDR(x), HWIO_PCIE_CC_DEBUG_CLK_CTL_RMSK)
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_DEBUG_CLK_CTL_ADDR(x), m)
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_DEBUG_CLK_CTL_ADDR(x),v)
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_DEBUG_CLK_CTL_ADDR(x),m,v,HWIO_PCIE_CC_DEBUG_CLK_CTL_IN(x))
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_ENABLE_BMSK                                            0x2000
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_ENABLE_SHFT                                               0xd
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_PLLTEST_DE_SEL_BMSK                                    0x1000
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_PLLTEST_DE_SEL_SHFT                                       0xc
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_MUX_SEL_BMSK                                            0xfff
#define HWIO_PCIE_CC_DEBUG_CLK_CTL_MUX_SEL_SHFT                                              0x0

#define HWIO_PCIE_CC_DEBUG_CDIVR_ADDR(x)                                              ((x) + 0x00160004)
#define HWIO_PCIE_CC_DEBUG_CDIVR_PHYS(x)                                              ((x) + 0x00160004)
#define HWIO_PCIE_CC_DEBUG_CDIVR_OFFS                                                 (0x00160004)
#define HWIO_PCIE_CC_DEBUG_CDIVR_RMSK                                                    0xf0000
#define HWIO_PCIE_CC_DEBUG_CDIVR_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_DEBUG_CDIVR_ADDR(x), HWIO_PCIE_CC_DEBUG_CDIVR_RMSK)
#define HWIO_PCIE_CC_DEBUG_CDIVR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_DEBUG_CDIVR_ADDR(x), m)
#define HWIO_PCIE_CC_DEBUG_CDIVR_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_DEBUG_CDIVR_ADDR(x),v)
#define HWIO_PCIE_CC_DEBUG_CDIVR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_DEBUG_CDIVR_ADDR(x),m,v,HWIO_PCIE_CC_DEBUG_CDIVR_IN(x))
#define HWIO_PCIE_CC_DEBUG_CDIVR_CLK_DIV_BMSK                                            0xf0000
#define HWIO_PCIE_CC_DEBUG_CDIVR_CLK_DIV_SHFT                                               0x10

#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_ADDR(x)                                         ((x) + 0x00170004)
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_PHYS(x)                                         ((x) + 0x00170004)
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_OFFS                                            (0x00170004)
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_RMSK                                                   0x1
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_CLKGEN_MISC_ADDR(x), HWIO_PCIE_CC_PCIE_CLKGEN_MISC_RMSK)
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_PCIE_CLKGEN_MISC_ADDR(x), m)
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_PCIE_CLKGEN_MISC_ADDR(x),v)
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_PCIE_CLKGEN_MISC_ADDR(x),m,v,HWIO_PCIE_CC_PCIE_CLKGEN_MISC_IN(x))
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_PCIE_CLKGEN_PWRDN_B_BMSK                               0x1
#define HWIO_PCIE_CC_PCIE_CLKGEN_MISC_PCIE_CLKGEN_PWRDN_B_SHFT                               0x0

#define HWIO_PCIE_CC_SPARE_0_ADDR(x)                                                  ((x) + 0x00180000)
#define HWIO_PCIE_CC_SPARE_0_PHYS(x)                                                  ((x) + 0x00180000)
#define HWIO_PCIE_CC_SPARE_0_OFFS                                                     (0x00180000)
#define HWIO_PCIE_CC_SPARE_0_RMSK                                                     0xffffffff
#define HWIO_PCIE_CC_SPARE_0_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_0_ADDR(x), HWIO_PCIE_CC_SPARE_0_RMSK)
#define HWIO_PCIE_CC_SPARE_0_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_0_ADDR(x), m)
#define HWIO_PCIE_CC_SPARE_0_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_SPARE_0_ADDR(x),v)
#define HWIO_PCIE_CC_SPARE_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_SPARE_0_ADDR(x),m,v,HWIO_PCIE_CC_SPARE_0_IN(x))
#define HWIO_PCIE_CC_SPARE_0_SPARE_BITS_BMSK                                          0xffffffff
#define HWIO_PCIE_CC_SPARE_0_SPARE_BITS_SHFT                                                 0x0

#define HWIO_PCIE_CC_SPARE_1_ADDR(x)                                                  ((x) + 0x00180004)
#define HWIO_PCIE_CC_SPARE_1_PHYS(x)                                                  ((x) + 0x00180004)
#define HWIO_PCIE_CC_SPARE_1_OFFS                                                     (0x00180004)
#define HWIO_PCIE_CC_SPARE_1_RMSK                                                     0xffffffff
#define HWIO_PCIE_CC_SPARE_1_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_1_ADDR(x), HWIO_PCIE_CC_SPARE_1_RMSK)
#define HWIO_PCIE_CC_SPARE_1_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_1_ADDR(x), m)
#define HWIO_PCIE_CC_SPARE_1_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_SPARE_1_ADDR(x),v)
#define HWIO_PCIE_CC_SPARE_1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_SPARE_1_ADDR(x),m,v,HWIO_PCIE_CC_SPARE_1_IN(x))
#define HWIO_PCIE_CC_SPARE_1_SPARE_BITS_BMSK                                          0xffffffff
#define HWIO_PCIE_CC_SPARE_1_SPARE_BITS_SHFT                                                 0x0

#define HWIO_PCIE_CC_SPARE_2_ADDR(x)                                                  ((x) + 0x00180008)
#define HWIO_PCIE_CC_SPARE_2_PHYS(x)                                                  ((x) + 0x00180008)
#define HWIO_PCIE_CC_SPARE_2_OFFS                                                     (0x00180008)
#define HWIO_PCIE_CC_SPARE_2_RMSK                                                     0xffffffff
#define HWIO_PCIE_CC_SPARE_2_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_2_ADDR(x), HWIO_PCIE_CC_SPARE_2_RMSK)
#define HWIO_PCIE_CC_SPARE_2_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_2_ADDR(x), m)
#define HWIO_PCIE_CC_SPARE_2_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_SPARE_2_ADDR(x),v)
#define HWIO_PCIE_CC_SPARE_2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_SPARE_2_ADDR(x),m,v,HWIO_PCIE_CC_SPARE_2_IN(x))
#define HWIO_PCIE_CC_SPARE_2_SPARE_BITS_BMSK                                          0xffffffff
#define HWIO_PCIE_CC_SPARE_2_SPARE_BITS_SHFT                                                 0x0

#define HWIO_PCIE_CC_SPARE_3_ADDR(x)                                                  ((x) + 0x0018000c)
#define HWIO_PCIE_CC_SPARE_3_PHYS(x)                                                  ((x) + 0x0018000c)
#define HWIO_PCIE_CC_SPARE_3_OFFS                                                     (0x0018000c)
#define HWIO_PCIE_CC_SPARE_3_RMSK                                                     0xffffffff
#define HWIO_PCIE_CC_SPARE_3_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_3_ADDR(x), HWIO_PCIE_CC_SPARE_3_RMSK)
#define HWIO_PCIE_CC_SPARE_3_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_3_ADDR(x), m)
#define HWIO_PCIE_CC_SPARE_3_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_SPARE_3_ADDR(x),v)
#define HWIO_PCIE_CC_SPARE_3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_SPARE_3_ADDR(x),m,v,HWIO_PCIE_CC_SPARE_3_IN(x))
#define HWIO_PCIE_CC_SPARE_3_SPARE_BITS_BMSK                                          0xffffffff
#define HWIO_PCIE_CC_SPARE_3_SPARE_BITS_SHFT                                                 0x0

#define HWIO_PCIE_CC_SPARE_4_ADDR(x)                                                  ((x) + 0x00190000)
#define HWIO_PCIE_CC_SPARE_4_PHYS(x)                                                  ((x) + 0x00190000)
#define HWIO_PCIE_CC_SPARE_4_OFFS                                                     (0x00190000)
#define HWIO_PCIE_CC_SPARE_4_RMSK                                                     0xffffffff
#define HWIO_PCIE_CC_SPARE_4_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_4_ADDR(x), HWIO_PCIE_CC_SPARE_4_RMSK)
#define HWIO_PCIE_CC_SPARE_4_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_4_ADDR(x), m)
#define HWIO_PCIE_CC_SPARE_4_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_SPARE_4_ADDR(x),v)
#define HWIO_PCIE_CC_SPARE_4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_SPARE_4_ADDR(x),m,v,HWIO_PCIE_CC_SPARE_4_IN(x))
#define HWIO_PCIE_CC_SPARE_4_SPARE_BITS_BMSK                                          0xffffffff
#define HWIO_PCIE_CC_SPARE_4_SPARE_BITS_SHFT                                                 0x0

#define HWIO_PCIE_CC_SPARE_5_ADDR(x)                                                  ((x) + 0x00190004)
#define HWIO_PCIE_CC_SPARE_5_PHYS(x)                                                  ((x) + 0x00190004)
#define HWIO_PCIE_CC_SPARE_5_OFFS                                                     (0x00190004)
#define HWIO_PCIE_CC_SPARE_5_RMSK                                                     0xffffffff
#define HWIO_PCIE_CC_SPARE_5_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_5_ADDR(x), HWIO_PCIE_CC_SPARE_5_RMSK)
#define HWIO_PCIE_CC_SPARE_5_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_5_ADDR(x), m)
#define HWIO_PCIE_CC_SPARE_5_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_SPARE_5_ADDR(x),v)
#define HWIO_PCIE_CC_SPARE_5_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_SPARE_5_ADDR(x),m,v,HWIO_PCIE_CC_SPARE_5_IN(x))
#define HWIO_PCIE_CC_SPARE_5_SPARE_BITS_BMSK                                          0xffffffff
#define HWIO_PCIE_CC_SPARE_5_SPARE_BITS_SHFT                                                 0x0

#define HWIO_PCIE_CC_SPARE_6_ADDR(x)                                                  ((x) + 0x00190008)
#define HWIO_PCIE_CC_SPARE_6_PHYS(x)                                                  ((x) + 0x00190008)
#define HWIO_PCIE_CC_SPARE_6_OFFS                                                     (0x00190008)
#define HWIO_PCIE_CC_SPARE_6_RMSK                                                     0xffffffff
#define HWIO_PCIE_CC_SPARE_6_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_6_ADDR(x), HWIO_PCIE_CC_SPARE_6_RMSK)
#define HWIO_PCIE_CC_SPARE_6_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_6_ADDR(x), m)
#define HWIO_PCIE_CC_SPARE_6_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_SPARE_6_ADDR(x),v)
#define HWIO_PCIE_CC_SPARE_6_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_SPARE_6_ADDR(x),m,v,HWIO_PCIE_CC_SPARE_6_IN(x))
#define HWIO_PCIE_CC_SPARE_6_SPARE_BITS_BMSK                                          0xffffffff
#define HWIO_PCIE_CC_SPARE_6_SPARE_BITS_SHFT                                                 0x0

#define HWIO_PCIE_CC_SPARE_7_ADDR(x)                                                  ((x) + 0x0019000c)
#define HWIO_PCIE_CC_SPARE_7_PHYS(x)                                                  ((x) + 0x0019000c)
#define HWIO_PCIE_CC_SPARE_7_OFFS                                                     (0x0019000c)
#define HWIO_PCIE_CC_SPARE_7_RMSK                                                     0xffffffff
#define HWIO_PCIE_CC_SPARE_7_IN(x)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_7_ADDR(x), HWIO_PCIE_CC_SPARE_7_RMSK)
#define HWIO_PCIE_CC_SPARE_7_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CC_SPARE_7_ADDR(x), m)
#define HWIO_PCIE_CC_SPARE_7_OUT(x, v)      \
        out_dword(HWIO_PCIE_CC_SPARE_7_ADDR(x),v)
#define HWIO_PCIE_CC_SPARE_7_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CC_SPARE_7_ADDR(x),m,v,HWIO_PCIE_CC_SPARE_7_IN(x))
#define HWIO_PCIE_CC_SPARE_7_SPARE_BITS_BMSK                                          0xffffffff
#define HWIO_PCIE_CC_SPARE_7_SPARE_BITS_SHFT                                                 0x0


#endif /* __HWIO_PCIE_CC_H__ */
