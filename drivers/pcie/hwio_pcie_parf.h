#ifndef __HWIO_PCIE_PARF_H__
#define __HWIO_PCIE_PARF_H__
/*
===========================================================================
*/
/**
  @file hwio_pcie_parf.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing v2 [amberwing_v2.0_p1r18.0]

  This file contains HWIO register definitions for the following modules:
    PCIE0_PCIE30_PARF

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
 * MODULE: PCIE30_PARF
 *--------------------------------------------------------------------------*/

#define PCIE30_PARF_REG_BASE                                                                            (PCIE0_PCIE30_WRAPPER_AHB_BASE      + 0x00000000)
#define PCIE30_PARF_REG_BASE_PHYS                                                                       (PCIE0_PCIE30_WRAPPER_AHB_BASE_PHYS + 0x00000000)
#define PCIE30_PARF_REG_BASE_OFFS                                                                       0x00000000

#define HWIO_PCIE30_PARF_SYS_CTRL_ADDR(x)                                                               ((x) + 0x00000000)
#define HWIO_PCIE30_PARF_SYS_CTRL_PHYS(x)                                                               ((x) + 0x00000000)
#define HWIO_PCIE30_PARF_SYS_CTRL_OFFS                                                                  (0x00000000)
#define HWIO_PCIE30_PARF_SYS_CTRL_RMSK                                                                  0x7fff7fff
#define HWIO_PCIE30_PARF_SYS_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(x), HWIO_PCIE30_PARF_SYS_CTRL_RMSK)
#define HWIO_PCIE30_PARF_SYS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(x), m)
#define HWIO_PCIE30_PARF_SYS_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(x),v)
#define HWIO_PCIE30_PARF_SYS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(x),m,v,HWIO_PCIE30_PARF_SYS_CTRL_IN(x))
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_RANGE2_BMSK                                           0x40000000
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_RANGE2_SHFT                                                 0x1e
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_RANGE2_DISABLE_ECAM_BLOCKER_RANGE_2_FVAL                     0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_RANGE2_ENABLE_ECAM_BLOCKER_RANGE_2_FVAL                      0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_MAC_PHY_POWERDOWN_IN_P2_D_MUX_EN_BMSK                                 0x20000000
#define HWIO_PCIE30_PARF_SYS_CTRL_MAC_PHY_POWERDOWN_IN_P2_D_MUX_EN_SHFT                                       0x1d
#define HWIO_PCIE30_PARF_SYS_CTRL_MAC_PHY_POWERDOWN_IN_P2_D_MUX_EN_EN_DISABLE_MUX_FVAL                         0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_MAC_PHY_POWERDOWN_IN_P2_D_MUX_EN_EN_ENABLE_MUX_FVAL                          0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_PIPE_MUX_OUTPUT_PIPE_DIS_BMSK                                     0x10000000
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_PIPE_MUX_OUTPUT_PIPE_DIS_SHFT                                           0x1c
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_PIPE_MUX_OUTPUT_PIPE_DIS_ENABLE_SELA_USE_FVAL                            0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_PIPE_MUX_OUTPUT_PIPE_DIS_DISABLE_SELA_USE_FVAL                           0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_REMOVE_OFFSET_EN_BMSK                                             0x8000000
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_REMOVE_OFFSET_EN_SHFT                                                  0x1b
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_REMOVE_OFFSET_EN_DISABLE_REMOVE_OFFSET_FVAL                             0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_REMOVE_OFFSET_EN_ENABLE_REMOVE_OFFSET_FVAL                              0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_BMSK                                                   0x4000000
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_SHFT                                                        0x1a
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_DISABLE_ECAM_BLOCKER_FVAL                                    0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_ENABLE_ECAM_BLOCKER_FVAL                                     0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_HW_EVENT_RESET_BMSK                                                    0x2000000
#define HWIO_PCIE30_PARF_SYS_CTRL_HW_EVENT_RESET_SHFT                                                         0x19
#define HWIO_PCIE30_PARF_SYS_CTRL_HW_EVENT_CGC_OPEN_BMSK                                                 0x1000000
#define HWIO_PCIE30_PARF_SYS_CTRL_HW_EVENT_CGC_OPEN_SHFT                                                      0x18
#define HWIO_PCIE30_PARF_SYS_CTRL_TESTBUS_SELECTOR_BMSK                                                   0xff0000
#define HWIO_PCIE30_PARF_SYS_CTRL_TESTBUS_SELECTOR_SHFT                                                       0x10
#define HWIO_PCIE30_PARF_SYS_CTRL_PHY_P2_IN_L1_DIS_BMSK                                                     0x4000
#define HWIO_PCIE30_PARF_SYS_CTRL_PHY_P2_IN_L1_DIS_SHFT                                                        0xe
#define HWIO_PCIE30_PARF_SYS_CTRL_PHY_P2_IN_L1_DIS_ENABLE_P2_WHEN_IN_L1_FVAL                                   0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_PHY_P2_IN_L1_DIS_DISABLE_P2_WHEN_IN_L1_FVAL                                  0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_MST_WAKEUP_EN_BMSK                                                        0x2000
#define HWIO_PCIE30_PARF_SYS_CTRL_MST_WAKEUP_EN_SHFT                                                           0xd
#define HWIO_PCIE30_PARF_SYS_CTRL_MST_WAKEUP_EN_DISABLE_MASTER_WAKEUP_FVAL                                     0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_MST_WAKEUP_EN_ENABLE_MASTER_WAKEUP_FVAL                                      0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_WAKEUP_EN_BMSK                                                        0x1000
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_WAKEUP_EN_SHFT                                                           0xc
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_WAKEUP_EN_DISABLE_SLV_WAKEUP_FVAL                                        0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_WAKEUP_EN_ENABLE_SLV_WAKEUP_FVAL                                         0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_DBI_WAKE_DIS_BMSK                                                      0x800
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_DBI_WAKE_DIS_SHFT                                                        0xb
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_DBI_WAKE_DIS_DISABLE_WAKE_FVAL                                           0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_DBI_WAKE_DIS_ENABLE_WAKE_FVAL                                            0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_MSTR_ACLK_CGC_DIS_BMSK                                                     0x400
#define HWIO_PCIE30_PARF_SYS_CTRL_MSTR_ACLK_CGC_DIS_SHFT                                                       0xa
#define HWIO_PCIE30_PARF_SYS_CTRL_MSTR_ACLK_CGC_DIS_CGC_ENABLED_FVAL                                           0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_MSTR_ACLK_CGC_DIS_DISABLE_CGC_FVAL                                           0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_ACLK_CGC_DIS_BMSK                                                      0x200
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_ACLK_CGC_DIS_SHFT                                                        0x9
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_ACLK_CGC_DIS_CGC_ENABLED_FVAL                                            0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_SLV_ACLK_CGC_DIS_DISABLE_CGC_FVAL                                            0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_ACLK_REQ_OVERRIDE_BMSK                                                     0x100
#define HWIO_PCIE30_PARF_SYS_CTRL_ACLK_REQ_OVERRIDE_SHFT                                                       0x8
#define HWIO_PCIE30_PARF_SYS_CTRL_ACLK_REQ_OVERRIDE_USE_HW_VALUE_FVAL                                          0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_ACLK_REQ_OVERRIDE_OVERRIDE_HW_VALUE_FVAL                                     0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_ACLK_REQ_BMSK                                                               0x80
#define HWIO_PCIE30_PARF_SYS_CTRL_ACLK_REQ_SHFT                                                                0x7
#define HWIO_PCIE30_PARF_SYS_CTRL_ACLK_REQ_ACLK_NOT_REQUESTED_FVAL                                             0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_ACLK_REQ_ACLK_REQUESTED_FVAL                                                 0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_CORE_CLK_CGC_DIS_BMSK                                                       0x40
#define HWIO_PCIE30_PARF_SYS_CTRL_CORE_CLK_CGC_DIS_SHFT                                                        0x6
#define HWIO_PCIE30_PARF_SYS_CTRL_CORE_CLK_CGC_DIS_CGC_ENABLED_FVAL                                            0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_CORE_CLK_CGC_DIS_DISABLE_CGC_FVAL                                            0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_CLK_MUX_DIS_BMSK                                                        0x20
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_CLK_MUX_DIS_SHFT                                                         0x5
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_CLK_MUX_DIS_MUX_ENABLED_FVAL                                             0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_CLK_MUX_DIS_DISABLE_MUX_FVAL                                             0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_PWR_DET_BMSK                                                            0x10
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_PWR_DET_SHFT                                                             0x4
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_PWR_DET_AUXILIARY_POWER_IS_OFF_FVAL                                      0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_AUX_PWR_DET_AUXILIARY_POWER_IS_ON_FVAL                                       0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_CORE_CLK2AUX_CLK_MUX_DIS_BMSK                                                0x8
#define HWIO_PCIE30_PARF_SYS_CTRL_CORE_CLK2AUX_CLK_MUX_DIS_SHFT                                                0x3
#define HWIO_PCIE30_PARF_SYS_CTRL_CORE_CLK2AUX_CLK_MUX_DIS_ENABLE_CORE_CLK2AUX_CLK_MUX_IN_L1_FVAL              0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_CORE_CLK2AUX_CLK_MUX_DIS_DISABLE_CORE_CLK2AUX_CLK_MUX_IN_L1_FVAL             0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_L23_CLK_RMV_DIS_BMSK                                                         0x4
#define HWIO_PCIE30_PARF_SYS_CTRL_L23_CLK_RMV_DIS_SHFT                                                         0x2
#define HWIO_PCIE30_PARF_SYS_CTRL_L23_CLK_RMV_DIS_ENABLE_CLOCK_REMOVAL_FVAL                                    0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_L23_CLK_RMV_DIS_DISABLE_CLOCK_REMOVAL_FVAL                                   0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_L1_CLK_RMV_DIS_BMSK                                                          0x2
#define HWIO_PCIE30_PARF_SYS_CTRL_L1_CLK_RMV_DIS_SHFT                                                          0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_L1_CLK_RMV_DIS_ENABLE_CLOCK_REMOVAL_FVAL                                     0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_L1_CLK_RMV_DIS_DISABLE_CLOCK_REMOVAL_FVAL                                    0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_CLK_RST_MDL_EN_BMSK                                                          0x1
#define HWIO_PCIE30_PARF_SYS_CTRL_CLK_RST_MDL_EN_SHFT                                                          0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_CLK_RST_MDL_EN_DISABLE_CLOCKS_RESETS_FVAL                                    0x0
#define HWIO_PCIE30_PARF_SYS_CTRL_CLK_RST_MDL_EN_ENABLE_CLOCKS_RESETS_FVAL                                     0x1

#define HWIO_PCIE30_PARF_DB_CTRL_ADDR(x)                                                                ((x) + 0x00000010)
#define HWIO_PCIE30_PARF_DB_CTRL_PHYS(x)                                                                ((x) + 0x00000010)
#define HWIO_PCIE30_PARF_DB_CTRL_OFFS                                                                   (0x00000010)
#define HWIO_PCIE30_PARF_DB_CTRL_RMSK                                                                         0x73
#define HWIO_PCIE30_PARF_DB_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_DB_CTRL_ADDR(x), HWIO_PCIE30_PARF_DB_CTRL_RMSK)
#define HWIO_PCIE30_PARF_DB_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_DB_CTRL_ADDR(x), m)
#define HWIO_PCIE30_PARF_DB_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_DB_CTRL_ADDR(x),v)
#define HWIO_PCIE30_PARF_DB_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_DB_CTRL_ADDR(x),m,v,HWIO_PCIE30_PARF_DB_CTRL_IN(x))
#define HWIO_PCIE30_PARF_DB_CTRL_MST_WKP_BLOCK_BMSK                                                           0x40
#define HWIO_PCIE30_PARF_DB_CTRL_MST_WKP_BLOCK_SHFT                                                            0x6
#define HWIO_PCIE30_PARF_DB_CTRL_MST_WKP_BLOCK_PASSED_FVAL                                                     0x0
#define HWIO_PCIE30_PARF_DB_CTRL_MST_WKP_BLOCK_BLOCKED_FVAL                                                    0x1
#define HWIO_PCIE30_PARF_DB_CTRL_SLV_WKP_BLOCK_BMSK                                                           0x20
#define HWIO_PCIE30_PARF_DB_CTRL_SLV_WKP_BLOCK_SHFT                                                            0x5
#define HWIO_PCIE30_PARF_DB_CTRL_SLV_WKP_BLOCK_PASSED_FVAL                                                     0x0
#define HWIO_PCIE30_PARF_DB_CTRL_SLV_WKP_BLOCK_BLOCKED_FVAL                                                    0x1
#define HWIO_PCIE30_PARF_DB_CTRL_DBI_WKP_BLOCK_BMSK                                                           0x10
#define HWIO_PCIE30_PARF_DB_CTRL_DBI_WKP_BLOCK_SHFT                                                            0x4
#define HWIO_PCIE30_PARF_DB_CTRL_DBI_WKP_BLOCK_PASSED_FVAL                                                     0x0
#define HWIO_PCIE30_PARF_DB_CTRL_DBI_WKP_BLOCK_BLOCKED_FVAL                                                    0x1
#define HWIO_PCIE30_PARF_DB_CTRL_RMVL_DBNCR_BLOCK_BMSK                                                         0x2
#define HWIO_PCIE30_PARF_DB_CTRL_RMVL_DBNCR_BLOCK_SHFT                                                         0x1
#define HWIO_PCIE30_PARF_DB_CTRL_RMVL_DBNCR_BLOCK_PASSED_FVAL                                                  0x0
#define HWIO_PCIE30_PARF_DB_CTRL_RMVL_DBNCR_BLOCK_BLOCKED_FVAL                                                 0x1
#define HWIO_PCIE30_PARF_DB_CTRL_INSR_DBNCR_BLOCK_BMSK                                                         0x1
#define HWIO_PCIE30_PARF_DB_CTRL_INSR_DBNCR_BLOCK_SHFT                                                         0x0
#define HWIO_PCIE30_PARF_DB_CTRL_INSR_DBNCR_BLOCK_PASSED_FVAL                                                  0x0
#define HWIO_PCIE30_PARF_DB_CTRL_INSR_DBNCR_BLOCK_BLOCKED_FVAL                                                 0x1

#define HWIO_PCIE30_PARF_PREDET_DB_INSR_ADDR(x)                                                         ((x) + 0x00000014)
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_PHYS(x)                                                         ((x) + 0x00000014)
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_OFFS                                                            (0x00000014)
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_RMSK                                                            0xffffffff
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PREDET_DB_INSR_ADDR(x), HWIO_PCIE30_PARF_PREDET_DB_INSR_RMSK)
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PREDET_DB_INSR_ADDR(x), m)
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_PREDET_DB_INSR_ADDR(x),v)
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_PREDET_DB_INSR_ADDR(x),m,v,HWIO_PCIE30_PARF_PREDET_DB_INSR_IN(x))
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_INSR_DBNCR_VAL_BMSK                                             0xffffffff
#define HWIO_PCIE30_PARF_PREDET_DB_INSR_INSR_DBNCR_VAL_SHFT                                                    0x0

#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_ADDR(x)                                                         ((x) + 0x00000018)
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_PHYS(x)                                                         ((x) + 0x00000018)
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_OFFS                                                            (0x00000018)
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_RMSK                                                            0xffffffff
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PREDET_DB_RMVL_ADDR(x), HWIO_PCIE30_PARF_PREDET_DB_RMVL_RMSK)
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PREDET_DB_RMVL_ADDR(x), m)
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_PREDET_DB_RMVL_ADDR(x),v)
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_PREDET_DB_RMVL_ADDR(x),m,v,HWIO_PCIE30_PARF_PREDET_DB_RMVL_IN(x))
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_RMVL_DBNCR_VAL_BMSK                                             0xffffffff
#define HWIO_PCIE30_PARF_PREDET_DB_RMVL_RMVL_DBNCR_VAL_SHFT                                                    0x0

#define HWIO_PCIE30_PARF_WKP_DB_RMVL_ADDR(x)                                                            ((x) + 0x0000001c)
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_PHYS(x)                                                            ((x) + 0x0000001c)
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_OFFS                                                               (0x0000001c)
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_RMSK                                                                 0xffffff
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_WKP_DB_RMVL_ADDR(x), HWIO_PCIE30_PARF_WKP_DB_RMVL_RMSK)
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_WKP_DB_RMVL_ADDR(x), m)
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_WKP_DB_RMVL_ADDR(x),v)
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_WKP_DB_RMVL_ADDR(x),m,v,HWIO_PCIE30_PARF_WKP_DB_RMVL_IN(x))
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_MST_DBNCR_VAL_BMSK                                                   0xff0000
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_MST_DBNCR_VAL_SHFT                                                       0x10
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_SLV_DBNCR_VAL_BMSK                                                     0xff00
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_SLV_DBNCR_VAL_SHFT                                                        0x8
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_DBI_DBNCR_VAL_BMSK                                                       0xff
#define HWIO_PCIE30_PARF_WKP_DB_RMVL_DBI_DBNCR_VAL_SHFT                                                        0x0

#define HWIO_PCIE30_PARF_PM_CTRL_ADDR(x)                                                                ((x) + 0x00000020)
#define HWIO_PCIE30_PARF_PM_CTRL_PHYS(x)                                                                ((x) + 0x00000020)
#define HWIO_PCIE30_PARF_PM_CTRL_OFFS                                                                   (0x00000020)
#define HWIO_PCIE30_PARF_PM_CTRL_RMSK                                                                         0x3f
#define HWIO_PCIE30_PARF_PM_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PM_CTRL_ADDR(x), HWIO_PCIE30_PARF_PM_CTRL_RMSK)
#define HWIO_PCIE30_PARF_PM_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PM_CTRL_ADDR(x), m)
#define HWIO_PCIE30_PARF_PM_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_PM_CTRL_ADDR(x),v)
#define HWIO_PCIE30_PARF_PM_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_PM_CTRL_ADDR(x),m,v,HWIO_PCIE30_PARF_PM_CTRL_IN(x))
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_NOT_ENTR_L1_BMSK                                                         0x20
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_NOT_ENTR_L1_SHFT                                                          0x5
#define HWIO_PCIE30_PARF_PM_CTRL_PM_XMT_PME_BMSK                                                              0x10
#define HWIO_PCIE30_PARF_PM_CTRL_PM_XMT_PME_SHFT                                                               0x4
#define HWIO_PCIE30_PARF_PM_CTRL_OUTBAND_PWRUP_CMD_BMSK                                                        0x8
#define HWIO_PCIE30_PARF_PM_CTRL_OUTBAND_PWRUP_CMD_SHFT                                                        0x3
#define HWIO_PCIE30_PARF_PM_CTRL_READY_ENTR_L23_BMSK                                                           0x4
#define HWIO_PCIE30_PARF_PM_CTRL_READY_ENTR_L23_SHFT                                                           0x2
#define HWIO_PCIE30_PARF_PM_CTRL_READY_ENTR_L23_NOT_READY_FVAL                                                 0x0
#define HWIO_PCIE30_PARF_PM_CTRL_READY_ENTR_L23_READY_FVAL                                                     0x1
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_EXIT_L1_BMSK                                                              0x2
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_EXIT_L1_SHFT                                                              0x1
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_EXIT_L1_DEASSERT_EXIT_REQUEST_FVAL                                        0x0
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_EXIT_L1_ASSERT_EXIT_REQUEST_FVAL                                          0x1
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_ENTR_L1_BMSK                                                              0x1
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_ENTR_L1_SHFT                                                              0x0
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_ENTR_L1_DEASSERT_ENTER_REQUEST_FVAL                                       0x0
#define HWIO_PCIE30_PARF_PM_CTRL_REQ_ENTR_L1_ASSERT_ENTER_REQUEST_FVAL                                         0x1

#define HWIO_PCIE30_PARF_PM_STTS_ADDR(x)                                                                ((x) + 0x00000024)
#define HWIO_PCIE30_PARF_PM_STTS_PHYS(x)                                                                ((x) + 0x00000024)
#define HWIO_PCIE30_PARF_PM_STTS_OFFS                                                                   (0x00000024)
#define HWIO_PCIE30_PARF_PM_STTS_RMSK                                                                   0xfffffff1
#define HWIO_PCIE30_PARF_PM_STTS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PM_STTS_ADDR(x), HWIO_PCIE30_PARF_PM_STTS_RMSK)
#define HWIO_PCIE30_PARF_PM_STTS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PM_STTS_ADDR(x), m)
#define HWIO_PCIE30_PARF_PM_STTS_LINK_REQ_RST_NOT_BMSK                                                  0x80000000
#define HWIO_PCIE30_PARF_PM_STTS_LINK_REQ_RST_NOT_SHFT                                                        0x1f
#define HWIO_PCIE30_PARF_PM_STTS_XMLH_LINK_UP_BMSK                                                      0x40000000
#define HWIO_PCIE30_PARF_PM_STTS_XMLH_LINK_UP_SHFT                                                            0x1e
#define HWIO_PCIE30_PARF_PM_STTS_PM_DSTATE_0_BMSK                                                       0x20000000
#define HWIO_PCIE30_PARF_PM_STTS_PM_DSTATE_0_SHFT                                                             0x1d
#define HWIO_PCIE30_PARF_PM_STTS_PM_DSTATE_0_D0_FVAL                                                           0x0
#define HWIO_PCIE30_PARF_PM_STTS_PM_DSTATE_0_D3_FVAL                                                           0x1
#define HWIO_PCIE30_PARF_PM_STTS_PHYSTATUS_BMSK                                                         0x10000000
#define HWIO_PCIE30_PARF_PM_STTS_PHYSTATUS_SHFT                                                               0x1c
#define HWIO_PCIE30_PARF_PM_STTS_PM_DSTATE_BMSK                                                          0xfff0000
#define HWIO_PCIE30_PARF_PM_STTS_PM_DSTATE_SHFT                                                               0x10
#define HWIO_PCIE30_PARF_PM_STTS_PM_PME_EN_BMSK                                                             0xf000
#define HWIO_PCIE30_PARF_PM_STTS_PM_PME_EN_SHFT                                                                0xc
#define HWIO_PCIE30_PARF_PM_STTS_PHYCLK_REQ_N_BMSK                                                           0x800
#define HWIO_PCIE30_PARF_PM_STTS_PHYCLK_REQ_N_SHFT                                                             0xb
#define HWIO_PCIE30_PARF_PM_STTS_L1SS_CLKREQN_OE_BMSK                                                        0x400
#define HWIO_PCIE30_PARF_PM_STTS_L1SS_CLKREQN_OE_SHFT                                                          0xa
#define HWIO_PCIE30_PARF_PM_STTS_L1SS_CLKREQN_IN_BMSK                                                        0x200
#define HWIO_PCIE30_PARF_PM_STTS_L1SS_CLKREQN_IN_SHFT                                                          0x9
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_IN_L1SUB_BMSK                                                     0x100
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_IN_L1SUB_SHFT                                                       0x8
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_IN_L0S_BMSK                                                        0x80
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_IN_L0S_SHFT                                                         0x7
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_L2_EXIT_BMSK                                                       0x40
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_L2_EXIT_SHFT                                                        0x6
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_IN_L2_BMSK                                                         0x20
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_IN_L2_SHFT                                                          0x5
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_IN_L1_BMSK                                                         0x10
#define HWIO_PCIE30_PARF_PM_STTS_PM_LINKST_IN_L1_SHFT                                                          0x4
#define HWIO_PCIE30_PARF_PM_STTS_PM_STATUS_BMSK                                                                0x1
#define HWIO_PCIE30_PARF_PM_STTS_PM_STATUS_SHFT                                                                0x0

#define HWIO_PCIE30_PARF_PM_STTS_1_ADDR(x)                                                              ((x) + 0x00000028)
#define HWIO_PCIE30_PARF_PM_STTS_1_PHYS(x)                                                              ((x) + 0x00000028)
#define HWIO_PCIE30_PARF_PM_STTS_1_OFFS                                                                 (0x00000028)
#define HWIO_PCIE30_PARF_PM_STTS_1_RMSK                                                                     0x3fff
#define HWIO_PCIE30_PARF_PM_STTS_1_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PM_STTS_1_ADDR(x), HWIO_PCIE30_PARF_PM_STTS_1_RMSK)
#define HWIO_PCIE30_PARF_PM_STTS_1_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PM_STTS_1_ADDR(x), m)
#define HWIO_PCIE30_PARF_PM_STTS_1_PM_LINKST_IN_L0_BMSK                                                     0x2000
#define HWIO_PCIE30_PARF_PM_STTS_1_PM_LINKST_IN_L0_SHFT                                                        0xd
#define HWIO_PCIE30_PARF_PM_STTS_1_LINK_TIMEOUT_FLUSH_NOT_BMSK                                              0x1000
#define HWIO_PCIE30_PARF_PM_STTS_1_LINK_TIMEOUT_FLUSH_NOT_SHFT                                                 0xc
#define HWIO_PCIE30_PARF_PM_STTS_1_CFG_BUS_MASTER_EN_BMSK                                                    0x800
#define HWIO_PCIE30_PARF_PM_STTS_1_CFG_BUS_MASTER_EN_SHFT                                                      0xb
#define HWIO_PCIE30_PARF_PM_STTS_1_RADM_PM_TURNOFF_BMSK                                                      0x400
#define HWIO_PCIE30_PARF_PM_STTS_1_RADM_PM_TURNOFF_SHFT                                                        0xa
#define HWIO_PCIE30_PARF_PM_STTS_1_CURNT_STATE_BMSK                                                          0x380
#define HWIO_PCIE30_PARF_PM_STTS_1_CURNT_STATE_SHFT                                                            0x7
#define HWIO_PCIE30_PARF_PM_STTS_1_AUX_PM_EN_BMSK                                                             0x40
#define HWIO_PCIE30_PARF_PM_STTS_1_AUX_PM_EN_SHFT                                                              0x6
#define HWIO_PCIE30_PARF_PM_STTS_1_AUX_CLK_ACTIVE_BMSK                                                        0x20
#define HWIO_PCIE30_PARF_PM_STTS_1_AUX_CLK_ACTIVE_SHFT                                                         0x5
#define HWIO_PCIE30_PARF_PM_STTS_1_MAC_PHY_PCLKREQ_N_BMSK                                                     0x10
#define HWIO_PCIE30_PARF_PM_STTS_1_MAC_PHY_PCLKREQ_N_SHFT                                                      0x4
#define HWIO_PCIE30_PARF_PM_STTS_1_PHY_MAC_PCLKACK_N_BMSK                                                      0x8
#define HWIO_PCIE30_PARF_PM_STTS_1_PHY_MAC_PCLKACK_N_SHFT                                                      0x3
#define HWIO_PCIE30_PARF_PM_STTS_1_MAC_PHY_RXELECIDLE_DIS_BMSK                                                 0x4
#define HWIO_PCIE30_PARF_PM_STTS_1_MAC_PHY_RXELECIDLE_DIS_SHFT                                                 0x2
#define HWIO_PCIE30_PARF_PM_STTS_1_MAC_PHY_POWERDOWN_BMSK                                                      0x3
#define HWIO_PCIE30_PARF_PM_STTS_1_MAC_PHY_POWERDOWN_SHFT                                                      0x0

#define HWIO_PCIE30_PARF_PCS_CTRL_ADDR(x)                                                               ((x) + 0x00000030)
#define HWIO_PCIE30_PARF_PCS_CTRL_PHYS(x)                                                               ((x) + 0x00000030)
#define HWIO_PCIE30_PARF_PCS_CTRL_OFFS                                                                  (0x00000030)
#define HWIO_PCIE30_PARF_PCS_CTRL_RMSK                                                                         0x3
#define HWIO_PCIE30_PARF_PCS_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PCS_CTRL_ADDR(x), HWIO_PCIE30_PARF_PCS_CTRL_RMSK)
#define HWIO_PCIE30_PARF_PCS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PCS_CTRL_ADDR(x), m)
#define HWIO_PCIE30_PARF_PCS_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_PCS_CTRL_ADDR(x),v)
#define HWIO_PCIE30_PARF_PCS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_PCS_CTRL_ADDR(x),m,v,HWIO_PCIE30_PARF_PCS_CTRL_IN(x))
#define HWIO_PCIE30_PARF_PCS_CTRL_TX2RX_LOOPBACK_EN_BMSK                                                       0x2
#define HWIO_PCIE30_PARF_PCS_CTRL_TX2RX_LOOPBACK_EN_SHFT                                                       0x1
#define HWIO_PCIE30_PARF_PCS_CTRL_TX2RX_LOOPBACK_EN_NORMAL_MODE_FVAL                                           0x0
#define HWIO_PCIE30_PARF_PCS_CTRL_TX2RX_LOOPBACK_EN_TX2RX_LOOPBACK_FVAL                                        0x1
#define HWIO_PCIE30_PARF_PCS_CTRL_COMMON_CLOCKS_BMSK                                                           0x1
#define HWIO_PCIE30_PARF_PCS_CTRL_COMMON_CLOCKS_SHFT                                                           0x0

#define HWIO_PCIE30_PARF_PCS_DEEMPH_ADDR(x)                                                             ((x) + 0x00000034)
#define HWIO_PCIE30_PARF_PCS_DEEMPH_PHYS(x)                                                             ((x) + 0x00000034)
#define HWIO_PCIE30_PARF_PCS_DEEMPH_OFFS                                                                (0x00000034)
#define HWIO_PCIE30_PARF_PCS_DEEMPH_RMSK                                                                  0x3f3f3f
#define HWIO_PCIE30_PARF_PCS_DEEMPH_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PCS_DEEMPH_ADDR(x), HWIO_PCIE30_PARF_PCS_DEEMPH_RMSK)
#define HWIO_PCIE30_PARF_PCS_DEEMPH_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PCS_DEEMPH_ADDR(x), m)
#define HWIO_PCIE30_PARF_PCS_DEEMPH_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_PCS_DEEMPH_ADDR(x),v)
#define HWIO_PCIE30_PARF_PCS_DEEMPH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_PCS_DEEMPH_ADDR(x),m,v,HWIO_PCIE30_PARF_PCS_DEEMPH_IN(x))
#define HWIO_PCIE30_PARF_PCS_DEEMPH_TX_DEEMPH_GEN1_BMSK                                                   0x3f0000
#define HWIO_PCIE30_PARF_PCS_DEEMPH_TX_DEEMPH_GEN1_SHFT                                                       0x10
#define HWIO_PCIE30_PARF_PCS_DEEMPH_TX_DEEMPH_GEN2_3_5DB_BMSK                                               0x3f00
#define HWIO_PCIE30_PARF_PCS_DEEMPH_TX_DEEMPH_GEN2_3_5DB_SHFT                                                  0x8
#define HWIO_PCIE30_PARF_PCS_DEEMPH_TX_DEEMPH_GEN2_6DB_BMSK                                                   0x3f
#define HWIO_PCIE30_PARF_PCS_DEEMPH_TX_DEEMPH_GEN2_6DB_SHFT                                                    0x0

#define HWIO_PCIE30_PARF_PCS_SWING_ADDR(x)                                                              ((x) + 0x00000038)
#define HWIO_PCIE30_PARF_PCS_SWING_PHYS(x)                                                              ((x) + 0x00000038)
#define HWIO_PCIE30_PARF_PCS_SWING_OFFS                                                                 (0x00000038)
#define HWIO_PCIE30_PARF_PCS_SWING_RMSK                                                                     0x7f7f
#define HWIO_PCIE30_PARF_PCS_SWING_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PCS_SWING_ADDR(x), HWIO_PCIE30_PARF_PCS_SWING_RMSK)
#define HWIO_PCIE30_PARF_PCS_SWING_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PCS_SWING_ADDR(x), m)
#define HWIO_PCIE30_PARF_PCS_SWING_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_PCS_SWING_ADDR(x),v)
#define HWIO_PCIE30_PARF_PCS_SWING_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_PCS_SWING_ADDR(x),m,v,HWIO_PCIE30_PARF_PCS_SWING_IN(x))
#define HWIO_PCIE30_PARF_PCS_SWING_TX_SWING_FULL_BMSK                                                       0x7f00
#define HWIO_PCIE30_PARF_PCS_SWING_TX_SWING_FULL_SHFT                                                          0x8
#define HWIO_PCIE30_PARF_PCS_SWING_TX_SWING_LOW_BMSK                                                          0x7f
#define HWIO_PCIE30_PARF_PCS_SWING_TX_SWING_LOW_SHFT                                                           0x0

#define HWIO_PCIE30_PARF_PHY_CTRL_ADDR(x)                                                               ((x) + 0x00000040)
#define HWIO_PCIE30_PARF_PHY_CTRL_PHYS(x)                                                               ((x) + 0x00000040)
#define HWIO_PCIE30_PARF_PHY_CTRL_OFFS                                                                  (0x00000040)
#define HWIO_PCIE30_PARF_PHY_CTRL_RMSK                                                                    0x1f1f17
#define HWIO_PCIE30_PARF_PHY_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PHY_CTRL_ADDR(x), HWIO_PCIE30_PARF_PHY_CTRL_RMSK)
#define HWIO_PCIE30_PARF_PHY_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PHY_CTRL_ADDR(x), m)
#define HWIO_PCIE30_PARF_PHY_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_PHY_CTRL_ADDR(x),v)
#define HWIO_PCIE30_PARF_PHY_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_PHY_CTRL_ADDR(x),m,v,HWIO_PCIE30_PARF_PHY_CTRL_IN(x))
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TX0_TERM_OFFST_BMSK                                                 0x1f0000
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TX0_TERM_OFFST_SHFT                                                     0x10
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_LOS_LEVEL_BMSK                                                        0x1f00
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_LOS_LEVEL_SHFT                                                           0x8
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_RTUNE_REQ_BMSK                                                          0x10
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_RTUNE_REQ_SHFT                                                           0x4
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TEST_BURNIN_BMSK                                                         0x4
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TEST_BURNIN_SHFT                                                         0x2
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TEST_BYPASS_BMSK                                                         0x2
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TEST_BYPASS_SHFT                                                         0x1
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TEST_PWR_DOWN_BMSK                                                       0x1
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TEST_PWR_DOWN_SHFT                                                       0x0
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TEST_PWR_DOWN_PHY_POWER_ON_FVAL                                          0x0
#define HWIO_PCIE30_PARF_PHY_CTRL_PHY_TEST_PWR_DOWN_PHY_POWER_DOWN_FVAL                                        0x1

#define HWIO_PCIE30_PARF_PHY_STTS_ADDR(x)                                                               ((x) + 0x00000044)
#define HWIO_PCIE30_PARF_PHY_STTS_PHYS(x)                                                               ((x) + 0x00000044)
#define HWIO_PCIE30_PARF_PHY_STTS_OFFS                                                                  (0x00000044)
#define HWIO_PCIE30_PARF_PHY_STTS_RMSK                                                                        0x10
#define HWIO_PCIE30_PARF_PHY_STTS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PHY_STTS_ADDR(x), HWIO_PCIE30_PARF_PHY_STTS_RMSK)
#define HWIO_PCIE30_PARF_PHY_STTS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PHY_STTS_ADDR(x), m)
#define HWIO_PCIE30_PARF_PHY_STTS_PHY_RTUNE_ACK_BMSK                                                          0x10
#define HWIO_PCIE30_PARF_PHY_STTS_PHY_RTUNE_ACK_SHFT                                                           0x4

#define HWIO_PCIE30_PARF_PHY_REFCLK_ADDR(x)                                                             ((x) + 0x0000004c)
#define HWIO_PCIE30_PARF_PHY_REFCLK_PHYS(x)                                                             ((x) + 0x0000004c)
#define HWIO_PCIE30_PARF_PHY_REFCLK_OFFS                                                                (0x0000004c)
#define HWIO_PCIE30_PARF_PHY_REFCLK_RMSK                                                                   0x1117f
#define HWIO_PCIE30_PARF_PHY_REFCLK_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_PHY_REFCLK_ADDR(x), HWIO_PCIE30_PARF_PHY_REFCLK_RMSK)
#define HWIO_PCIE30_PARF_PHY_REFCLK_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_PHY_REFCLK_ADDR(x), m)
#define HWIO_PCIE30_PARF_PHY_REFCLK_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_PHY_REFCLK_ADDR(x),v)
#define HWIO_PCIE30_PARF_PHY_REFCLK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_PHY_REFCLK_ADDR(x),m,v,HWIO_PCIE30_PARF_PHY_REFCLK_IN(x))
#define HWIO_PCIE30_PARF_PHY_REFCLK_REF_SSP_EN_BMSK                                                        0x10000
#define HWIO_PCIE30_PARF_PHY_REFCLK_REF_SSP_EN_SHFT                                                           0x10
#define HWIO_PCIE30_PARF_PHY_REFCLK_REF_SSP_EN_NO_REFCLK_FVAL                                                  0x0
#define HWIO_PCIE30_PARF_PHY_REFCLK_REF_SSP_EN_REFCLK_STABLE_FVAL                                              0x1
#define HWIO_PCIE30_PARF_PHY_REFCLK_REF_USE_PAD_BMSK                                                        0x1000
#define HWIO_PCIE30_PARF_PHY_REFCLK_REF_USE_PAD_SHFT                                                           0xc
#define HWIO_PCIE30_PARF_PHY_REFCLK_REF_USE_PAD_REFCLK_FROM_ALT_FVAL                                           0x0
#define HWIO_PCIE30_PARF_PHY_REFCLK_REF_USE_PAD_REFCLK_FROM_PAD_FVAL                                           0x1
#define HWIO_PCIE30_PARF_PHY_REFCLK_REFCLK_DIV2_BMSK                                                         0x100
#define HWIO_PCIE30_PARF_PHY_REFCLK_REFCLK_DIV2_SHFT                                                           0x8
#define HWIO_PCIE30_PARF_PHY_REFCLK_REFCLK_DIV2_DON_T_DIVIDE_FVAL                                              0x0
#define HWIO_PCIE30_PARF_PHY_REFCLK_REFCLK_DIV2_DIVIDE_REFCLK_FVAL                                             0x1
#define HWIO_PCIE30_PARF_PHY_REFCLK_MPLL_MULTIPLIER_BMSK                                                      0x7f
#define HWIO_PCIE30_PARF_PHY_REFCLK_MPLL_MULTIPLIER_SHFT                                                       0x0

#define HWIO_PCIE30_PARF_CONFIG_BITS_ADDR(x)                                                            ((x) + 0x00000050)
#define HWIO_PCIE30_PARF_CONFIG_BITS_PHYS(x)                                                            ((x) + 0x00000050)
#define HWIO_PCIE30_PARF_CONFIG_BITS_OFFS                                                               (0x00000050)
#define HWIO_PCIE30_PARF_CONFIG_BITS_RMSK                                                               0xffffffff
#define HWIO_PCIE30_PARF_CONFIG_BITS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_CONFIG_BITS_ADDR(x), HWIO_PCIE30_PARF_CONFIG_BITS_RMSK)
#define HWIO_PCIE30_PARF_CONFIG_BITS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_CONFIG_BITS_ADDR(x), m)
#define HWIO_PCIE30_PARF_CONFIG_BITS_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_CONFIG_BITS_ADDR(x),v)
#define HWIO_PCIE30_PARF_CONFIG_BITS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_CONFIG_BITS_ADDR(x),m,v,HWIO_PCIE30_PARF_CONFIG_BITS_IN(x))
#define HWIO_PCIE30_PARF_CONFIG_BITS_BITS31_27_BMSK                                                     0xf8000000
#define HWIO_PCIE30_PARF_CONFIG_BITS_BITS31_27_SHFT                                                           0x1b
#define HWIO_PCIE30_PARF_CONFIG_BITS_PHY_RX0_EQ_BMSK                                                     0x7000000
#define HWIO_PCIE30_PARF_CONFIG_BITS_PHY_RX0_EQ_SHFT                                                          0x18
#define HWIO_PCIE30_PARF_CONFIG_BITS_BITS23_0_BMSK                                                        0xffffff
#define HWIO_PCIE30_PARF_CONFIG_BITS_BITS23_0_SHFT                                                             0x0

#define HWIO_PCIE30_PARF_AXI_CONFIG_ADDR(x)                                                             ((x) + 0x00000054)
#define HWIO_PCIE30_PARF_AXI_CONFIG_PHYS(x)                                                             ((x) + 0x00000054)
#define HWIO_PCIE30_PARF_AXI_CONFIG_OFFS                                                                (0x00000054)
#define HWIO_PCIE30_PARF_AXI_CONFIG_RMSK                                                                0xffffffff
#define HWIO_PCIE30_PARF_AXI_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_AXI_CONFIG_ADDR(x), HWIO_PCIE30_PARF_AXI_CONFIG_RMSK)
#define HWIO_PCIE30_PARF_AXI_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_AXI_CONFIG_ADDR(x), m)
#define HWIO_PCIE30_PARF_AXI_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_AXI_CONFIG_ADDR(x),v)
#define HWIO_PCIE30_PARF_AXI_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_AXI_CONFIG_ADDR(x),m,v,HWIO_PCIE30_PARF_AXI_CONFIG_IN(x))
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_AWCACHE_BMSK                                                     0xf0000000
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_AWCACHE_SHFT                                                           0x1c
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_ARCACHE_BMSK                                                      0xf000000
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_ARCACHE_SHFT                                                           0x18
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_AWNOALLOCATE_BMSK                                                  0x800000
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_AWNOALLOCATE_SHFT                                                      0x17
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_AWMEMTYPE_BMSK                                                     0x700000
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_AWMEMTYPE_SHFT                                                         0x14
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_ARNOALLOCATE_BMSK                                                   0x80000
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_ARNOALLOCATE_SHFT                                                      0x13
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_ARMEMTYPE_BMSK                                                      0x70000
#define HWIO_PCIE30_PARF_AXI_CONFIG_NS_ARMEMTYPE_SHFT                                                         0x10
#define HWIO_PCIE30_PARF_AXI_CONFIG_AWCACHE_BMSK                                                            0xf000
#define HWIO_PCIE30_PARF_AXI_CONFIG_AWCACHE_SHFT                                                               0xc
#define HWIO_PCIE30_PARF_AXI_CONFIG_ARCACHE_BMSK                                                             0xf00
#define HWIO_PCIE30_PARF_AXI_CONFIG_ARCACHE_SHFT                                                               0x8
#define HWIO_PCIE30_PARF_AXI_CONFIG_AWNOALLOCATE_BMSK                                                         0x80
#define HWIO_PCIE30_PARF_AXI_CONFIG_AWNOALLOCATE_SHFT                                                          0x7
#define HWIO_PCIE30_PARF_AXI_CONFIG_AWMEMTYPE_BMSK                                                            0x70
#define HWIO_PCIE30_PARF_AXI_CONFIG_AWMEMTYPE_SHFT                                                             0x4
#define HWIO_PCIE30_PARF_AXI_CONFIG_ARNOALLOCATE_BMSK                                                          0x8
#define HWIO_PCIE30_PARF_AXI_CONFIG_ARNOALLOCATE_SHFT                                                          0x3
#define HWIO_PCIE30_PARF_AXI_CONFIG_ARMEMTYPE_BMSK                                                             0x7
#define HWIO_PCIE30_PARF_AXI_CONFIG_ARMEMTYPE_SHFT                                                             0x0

#define HWIO_PCIE30_PARF_HW_EV_n_ADDR(base,n)                                                           ((base) + 0x00000058 + 0x4 * (n))
#define HWIO_PCIE30_PARF_HW_EV_n_PHYS(base,n)                                                           ((base) + 0x00000058 + 0x4 * (n))
#define HWIO_PCIE30_PARF_HW_EV_n_OFFS(base,n)                                                           (0x00000058 + 0x4 * (n))
#define HWIO_PCIE30_PARF_HW_EV_n_RMSK                                                                   0x8000007f
#define HWIO_PCIE30_PARF_HW_EV_n_MAXn                                                                           31
#define HWIO_PCIE30_PARF_HW_EV_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_PARF_HW_EV_n_ADDR(base,n), HWIO_PCIE30_PARF_HW_EV_n_RMSK)
#define HWIO_PCIE30_PARF_HW_EV_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_PARF_HW_EV_n_ADDR(base,n), mask)
#define HWIO_PCIE30_PARF_HW_EV_n_OUTI(base,n,val)    \
        out_dword(HWIO_PCIE30_PARF_HW_EV_n_ADDR(base,n),val)
#define HWIO_PCIE30_PARF_HW_EV_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_HW_EV_n_ADDR(base,n),mask,val,HWIO_PCIE30_PARF_HW_EV_n_INI(base,n))
#define HWIO_PCIE30_PARF_HW_EV_n_EN_BMSK                                                                0x80000000
#define HWIO_PCIE30_PARF_HW_EV_n_EN_SHFT                                                                      0x1f
#define HWIO_PCIE30_PARF_HW_EV_n_SEL_BMSK                                                                     0x7f
#define HWIO_PCIE30_PARF_HW_EV_n_SEL_SHFT                                                                      0x0

#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_ADDR(x)                                                        ((x) + 0x000000dc)
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_PHYS(x)                                                        ((x) + 0x000000dc)
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_OFFS                                                           (0x000000dc)
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_RMSK                                                             0x3fffff
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_ADDR(x), HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_RMSK)
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_ADDR(x), m)
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_ADDR(x),v)
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_ADDR(x),m,v,HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_IN(x))
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_AORDEREDWR_RD_WAIT_BMSK                                          0x200000
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_AORDEREDWR_RD_WAIT_SHFT                                              0x15
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_ECAM_BLOCKED_IRQ_MASK_BMSK                                       0x100000
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_ECAM_BLOCKED_IRQ_MASK_SHFT                                           0x14
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_BRESP_TRANS_BYP_BMSK                                              0xff000
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_BRESP_TRANS_BYP_SHFT                                                  0xc
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_WRITE_ID_BMSK                                                       0xf00
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_WRITE_ID_SHFT                                                         0x8
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_AIDO_DIS_BMSK                                                        0x80
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_AIDO_DIS_SHFT                                                         0x7
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_AIDO_VAL_BMSK                                                        0x40
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_AIDO_VAL_SHFT                                                         0x6
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_DBI_WR_STALL_RESET_BMSK                                              0x20
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_DBI_WR_STALL_RESET_SHFT                                               0x5
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_DBI_WR_STALL_BYPASS_BMSK                                             0x10
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_DBI_WR_STALL_BYPASS_SHFT                                              0x4
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_STATUS_BMSK                                                           0xf
#define HWIO_PCIE30_PARF_Q2A_BRIDGE_CTRL_STATUS_SHFT                                                           0x0

#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_ADDR(x)                                                          ((x) + 0x000000e0)
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_PHYS(x)                                                          ((x) + 0x000000e0)
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_OFFS                                                             (0x000000e0)
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_RMSK                                                             0xffffffff
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_BASE_ADDR_ADDR(x), HWIO_PCIE30_PARF_SLV_BASE_ADDR_RMSK)
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_BASE_ADDR_ADDR(x), m)
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SLV_BASE_ADDR_ADDR(x),v)
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SLV_BASE_ADDR_ADDR(x),m,v,HWIO_PCIE30_PARF_SLV_BASE_ADDR_IN(x))
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_SLV_BASE_ADDR_BMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_SLV_BASE_ADDR_SLV_BASE_ADDR_SHFT                                                      0x0

#define HWIO_PCIE30_PARF_TEST_BUS_ADDR(x)                                                               ((x) + 0x000000e4)
#define HWIO_PCIE30_PARF_TEST_BUS_PHYS(x)                                                               ((x) + 0x000000e4)
#define HWIO_PCIE30_PARF_TEST_BUS_OFFS                                                                  (0x000000e4)
#define HWIO_PCIE30_PARF_TEST_BUS_RMSK                                                                  0xffffffff
#define HWIO_PCIE30_PARF_TEST_BUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_TEST_BUS_ADDR(x), HWIO_PCIE30_PARF_TEST_BUS_RMSK)
#define HWIO_PCIE30_PARF_TEST_BUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_TEST_BUS_ADDR(x), m)
#define HWIO_PCIE30_PARF_TEST_BUS_PCIE30_TEST_BUS_BMSK                                                  0xffffffff
#define HWIO_PCIE30_PARF_TEST_BUS_PCIE30_TEST_BUS_SHFT                                                         0x0

#define HWIO_PCIE30_PARF_MSG_ADDR_n_ADDR(base,n)                                                        ((base) + 0x000000e8 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_n_PHYS(base,n)                                                        ((base) + 0x000000e8 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_n_OFFS(base,n)                                                        (0x000000e8 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_n_RMSK                                                                0xffffffff
#define HWIO_PCIE30_PARF_MSG_ADDR_n_MAXn                                                                        15
#define HWIO_PCIE30_PARF_MSG_ADDR_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_ADDR_n_ADDR(base,n), HWIO_PCIE30_PARF_MSG_ADDR_n_RMSK)
#define HWIO_PCIE30_PARF_MSG_ADDR_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_ADDR_n_ADDR(base,n), mask)
#define HWIO_PCIE30_PARF_MSG_ADDR_n_OUTI(base,n,val)    \
        out_dword(HWIO_PCIE30_PARF_MSG_ADDR_n_ADDR(base,n),val)
#define HWIO_PCIE30_PARF_MSG_ADDR_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSG_ADDR_n_ADDR(base,n),mask,val,HWIO_PCIE30_PARF_MSG_ADDR_n_INI(base,n))
#define HWIO_PCIE30_PARF_MSG_ADDR_n_MSG_ADDR_BMSK                                                       0xffffffff
#define HWIO_PCIE30_PARF_MSG_ADDR_n_MSG_ADDR_SHFT                                                              0x0

#define HWIO_PCIE30_PARF_MSG_PARAMS_n_ADDR(base,n)                                                      ((base) + 0x00000128 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_PHYS(base,n)                                                      ((base) + 0x00000128 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_OFFS(base,n)                                                      (0x00000128 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_RMSK                                                              0x81f11fff
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MAXn                                                                      15
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_PARAMS_n_ADDR(base,n), HWIO_PCIE30_PARF_MSG_PARAMS_n_RMSK)
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_PARAMS_n_ADDR(base,n), mask)
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_OUTI(base,n,val)    \
        out_dword(HWIO_PCIE30_PARF_MSG_PARAMS_n_ADDR(base,n),val)
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSG_PARAMS_n_ADDR(base,n),mask,val,HWIO_PCIE30_PARF_MSG_PARAMS_n_INI(base,n))
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_EN_BMSK                                                           0x80000000
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_EN_SHFT                                                                 0x1f
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_MSGDNMSG_BMSK                                                  0x1000000
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_MSGDNMSG_SHFT                                                       0x18
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_ATU_BYPASS_BMSK                                                     0x800000
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_ATU_BYPASS_SHFT                                                         0x17
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_TC_BMSK                                                         0x700000
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_TC_SHFT                                                             0x14
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_EP_BMSK                                                          0x10000
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_EP_SHFT                                                             0x10
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_TYPE_BMSK                                                         0x1f00
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_TYPE_SHFT                                                            0x8
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_CODE_BMSK                                                           0xff
#define HWIO_PCIE30_PARF_MSG_PARAMS_n_MSG_CODE_SHFT                                                            0x0

#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_ADDR(x)                                                          ((x) + 0x00000168)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_PHYS(x)                                                          ((x) + 0x00000168)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_OFFS                                                             (0x00000168)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_RMSK                                                             0xffffffff
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_DBI_BASE_ADDR_ADDR(x), HWIO_PCIE30_PARF_DBI_BASE_ADDR_RMSK)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_DBI_BASE_ADDR_ADDR(x), m)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_DBI_BASE_ADDR_ADDR(x),v)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_DBI_BASE_ADDR_ADDR(x),m,v,HWIO_PCIE30_PARF_DBI_BASE_ADDR_IN(x))
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_DBI_BASE_ADDR_BMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_DBI_BASE_ADDR_SHFT                                                      0x0

#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_ADDR(x)                                                    ((x) + 0x0000016c)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_PHYS(x)                                                    ((x) + 0x0000016c)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_OFFS                                                       (0x0000016c)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_RMSK                                                       0xffffffff
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_ADDR(x), HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_RMSK)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_ADDR(x), m)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_ADDR(x),v)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_ADDR(x),m,v,HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_IN(x))
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_SLV_ADDR_SPACE_SIZE_BMSK                                   0xffffffff
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_SLV_ADDR_SPACE_SIZE_SHFT                                          0x0

#define HWIO_PCIE30_PARF_VERSION_ADDR(x)                                                                ((x) + 0x00000170)
#define HWIO_PCIE30_PARF_VERSION_PHYS(x)                                                                ((x) + 0x00000170)
#define HWIO_PCIE30_PARF_VERSION_OFFS                                                                   (0x00000170)
#define HWIO_PCIE30_PARF_VERSION_RMSK                                                                        0xfff
#define HWIO_PCIE30_PARF_VERSION_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_VERSION_ADDR(x), HWIO_PCIE30_PARF_VERSION_RMSK)
#define HWIO_PCIE30_PARF_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_VERSION_ADDR(x), m)
#define HWIO_PCIE30_PARF_VERSION_IP_CAT_VERSION_BMSK                                                         0xfff
#define HWIO_PCIE30_PARF_VERSION_IP_CAT_VERSION_SHFT                                                           0x0

#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_ADDR(x)                                                   ((x) + 0x00000174)
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_PHYS(x)                                                   ((x) + 0x00000174)
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_OFFS                                                      (0x00000174)
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_RMSK                                                             0xf
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_ADDR(x), HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_RMSK)
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_ADDR(x), m)
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_ADDR(x),v)
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_ADDR(x),m,v,HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_IN(x))
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_MSTR_AXI_LOGIC_RESET_BMSK                                        0x8
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_MSTR_AXI_LOGIC_RESET_SHFT                                        0x3
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_AHB_LOGIC_RESET_BMSK                                             0x4
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_AHB_LOGIC_RESET_SHFT                                             0x2
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_MSTR_AXI_CLK_EN_BMSK                                             0x2
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_MSTR_AXI_CLK_EN_SHFT                                             0x1
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_AHB_CLK_EN_BMSK                                                  0x1
#define HWIO_PCIE30_PARF_MHI_CLOCK_RESET_CTRL_AHB_CLK_EN_SHFT                                                  0x0

#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_ADDR(x)                                                    ((x) + 0x00000178)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_PHYS(x)                                                    ((x) + 0x00000178)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_OFFS                                                       (0x00000178)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_RMSK                                                       0xffffffff
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_ADDR(x), HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_RMSK)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_ADDR(x), m)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_ADDR(x),v)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_ADDR(x),m,v,HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_IN(x))
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_VAL_BMSK                                                   0xffffffff
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_LOWER_VAL_SHFT                                                          0x0

#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_ADDR(x)                                                    ((x) + 0x0000017c)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_PHYS(x)                                                    ((x) + 0x0000017c)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_OFFS                                                       (0x0000017c)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_RMSK                                                       0xffffffff
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_ADDR(x), HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_RMSK)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_ADDR(x), m)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_ADDR(x),v)
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_ADDR(x),m,v,HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_IN(x))
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_VAL_BMSK                                                   0xffffffff
#define HWIO_PCIE30_PARF_MHI_BASE_ADDR_UPPER_VAL_SHFT                                                          0x0

#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_ADDR(x)                                                ((x) + 0x00000180)
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_PHYS(x)                                                ((x) + 0x00000180)
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_OFFS                                                   (0x00000180)
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_RMSK                                                   0xffffffff
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_ADDR(x), HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_RMSK)
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_ADDR(x), m)
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_ADDR(x),v)
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_ADDR(x),m,v,HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_IN(x))
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_RESET_BMSK                                             0x80000000
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_RESET_SHFT                                                   0x1f
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_CNT_MAX_BMSK                                           0x7fffffff
#define HWIO_PCIE30_PARF_L1SUB_AHB_CLK_MAX_TIMER_CNT_MAX_SHFT                                                  0x0

#define HWIO_PCIE30_PARF_LTR_MSG_GEN_ADDR(x)                                                            ((x) + 0x00000184)
#define HWIO_PCIE30_PARF_LTR_MSG_GEN_PHYS(x)                                                            ((x) + 0x00000184)
#define HWIO_PCIE30_PARF_LTR_MSG_GEN_OFFS                                                               (0x00000184)
#define HWIO_PCIE30_PARF_LTR_MSG_GEN_RMSK                                                               0xffffffff
#define HWIO_PCIE30_PARF_LTR_MSG_GEN_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_LTR_MSG_GEN_ADDR(x),v)
#define HWIO_PCIE30_PARF_LTR_MSG_GEN_LATENCY_BMSK                                                       0xffffffff
#define HWIO_PCIE30_PARF_LTR_MSG_GEN_LATENCY_SHFT                                                              0x0

#define HWIO_PCIE30_PARF_MSI_GEN_ADDR(x)                                                                ((x) + 0x00000188)
#define HWIO_PCIE30_PARF_MSI_GEN_PHYS(x)                                                                ((x) + 0x00000188)
#define HWIO_PCIE30_PARF_MSI_GEN_OFFS                                                                   (0x00000188)
#define HWIO_PCIE30_PARF_MSI_GEN_RMSK                                                                         0x1f
#define HWIO_PCIE30_PARF_MSI_GEN_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MSI_GEN_ADDR(x),v)
#define HWIO_PCIE30_PARF_MSI_GEN_VECTOR_BMSK                                                                  0x1f
#define HWIO_PCIE30_PARF_MSI_GEN_VECTOR_SHFT                                                                   0x0

#define HWIO_PCIE30_PARF_DEBUG_INT_EN_ADDR(x)                                                           ((x) + 0x00000190)
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_PHYS(x)                                                           ((x) + 0x00000190)
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_OFFS                                                              (0x00000190)
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_RMSK                                                                    0x3f
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_DEBUG_INT_EN_ADDR(x), HWIO_PCIE30_PARF_DEBUG_INT_EN_RMSK)
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_DEBUG_INT_EN_ADDR(x), m)
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_DEBUG_INT_EN_ADDR(x),v)
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_DEBUG_INT_EN_ADDR(x),m,v,HWIO_PCIE30_PARF_DEBUG_INT_EN_IN(x))
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_ELBI_CS2_ENABLE_BMSK                                                    0x20
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_ELBI_CS2_ENABLE_SHFT                                                     0x5
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_L1SUB_TIMEOUT_SEL_BIT_BMSK                                              0x10
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_L1SUB_TIMEOUT_SEL_BIT_SHFT                                               0x4
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_L1SUB_TIMEOUT_SEL_BIT_NON_L1SUB_TIMEOUT_EN_INT_FVAL                      0x0
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_L1SUB_TIMEOUT_SEL_BIT_L1SUB_TIMEOUT_EN_INT_FVAL                          0x1
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_RADM_PM_TURNOFF_BMSK                                                     0x8
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_RADM_PM_TURNOFF_SHFT                                                     0x3
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_CFG_BUS_MASTER_EN_BMSK                                                   0x4
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_CFG_BUS_MASTER_EN_SHFT                                                   0x2
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_PM_DSTATE_CHANGE_BIT_BMSK                                                0x2
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_PM_DSTATE_CHANGE_BIT_SHFT                                                0x1
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_L1SUB_TIMEOUT_BIT_BMSK                                                   0x1
#define HWIO_PCIE30_PARF_DEBUG_INT_EN_L1SUB_TIMEOUT_BIT_SHFT                                                   0x0

#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_ADDR(x)                                                        ((x) + 0x00000194)
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_PHYS(x)                                                        ((x) + 0x00000194)
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_OFFS                                                           (0x00000194)
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_RMSK                                                           0xffffffff
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_ADDR(x), HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_RMSK)
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_ADDR(x), m)
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_ADDR(x),v)
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_ADDR(x),m,v,HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_IN(x))
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_SIZE_KB_BMSK                                                   0xffffffff
#define HWIO_PCIE30_PARF_MHI_BAR_KB_SIZE_SIZE_KB_SHFT                                                          0x0

#define HWIO_PCIE30_PARF_MHI_IPA_DBS_ADDR(x)                                                            ((x) + 0x00000198)
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_PHYS(x)                                                            ((x) + 0x00000198)
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_OFFS                                                               (0x00000198)
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_RMSK                                                               0xffffffff
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_IPA_DBS_ADDR(x), HWIO_PCIE30_PARF_MHI_IPA_DBS_RMSK)
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_IPA_DBS_ADDR(x), m)
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MHI_IPA_DBS_ADDR(x),v)
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MHI_IPA_DBS_ADDR(x),m,v,HWIO_PCIE30_PARF_MHI_IPA_DBS_IN(x))
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_EDB_END_BMSK                                                       0xff000000
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_EDB_END_SHFT                                                             0x18
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_EDB_BASE_BMSK                                                        0xff0000
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_EDB_BASE_SHFT                                                            0x10
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_CDB_END_BMSK                                                           0xff00
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_CDB_END_SHFT                                                              0x8
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_CDB_BASE_BMSK                                                            0xff
#define HWIO_PCIE30_PARF_MHI_IPA_DBS_CDB_BASE_SHFT                                                             0x0

#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_ADDR(x)                                               ((x) + 0x0000019c)
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_PHYS(x)                                               ((x) + 0x0000019c)
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_OFFS                                                  (0x0000019c)
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_RMSK                                                  0xffffffff
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_ADDR(x), HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_RMSK)
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_ADDR(x), m)
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_ADDR(x),v)
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_ADDR(x),m,v,HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_IN(x))
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_ADDR_LOWER_BMSK                                       0xffffffff
#define HWIO_PCIE30_PARF_MHI_IPA_CDB_TARGET_LOWER_ADDR_LOWER_SHFT                                              0x0

#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_ADDR(x)                                               ((x) + 0x000001a0)
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_PHYS(x)                                               ((x) + 0x000001a0)
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_OFFS                                                  (0x000001a0)
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_RMSK                                                  0xffffffff
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_ADDR(x), HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_RMSK)
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_ADDR(x), m)
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_ADDR(x),v)
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_ADDR(x),m,v,HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_IN(x))
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_ADDR_LOWER_BMSK                                       0xffffffff
#define HWIO_PCIE30_PARF_MHI_IPA_EDB_TARGET_LOWER_ADDR_LOWER_SHFT                                              0x0

#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_ADDR(x)                                             ((x) + 0x000001a4)
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_PHYS(x)                                             ((x) + 0x000001a4)
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_OFFS                                                (0x000001a4)
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_RMSK                                                0xffff003f
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_ADDR(x), HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_RMSK)
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_ADDR(x), m)
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_ADDR(x),v)
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_ADDR(x),m,v,HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_IN(x))
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_PCIE_CONFI6_ADDR_RANGE_BMSK                         0xffff0000
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_PCIE_CONFI6_ADDR_RANGE_SHFT                               0x10
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_CRS_ID_ERROR_BMSK                                         0x20
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_CRS_ID_ERROR_SHFT                                          0x5
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_PCIE_CONFIG_SPACE_CHECK_DISABLE_BMSK                      0x10
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_PCIE_CONFIG_SPACE_CHECK_DISABLE_SHFT                       0x4
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_DISABLE_CRS_VISIBILITY_BMSK                                0x8
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_DISABLE_CRS_VISIBILITY_SHFT                                0x3
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_SBR_FLUSH_COMPLETED_DISABLE_BMSK                           0x4
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_SBR_FLUSH_COMPLETED_DISABLE_SHFT                           0x2
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_DWC_GLITCH_LGC_DISABLE_BMSK                                0x2
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_DWC_GLITCH_LGC_DISABLE_SHFT                                0x1
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_EN_BMSK                                                    0x1
#define HWIO_PCIE30_PARF_AXI_MSTR_RD_HALT_NO_WRITES_EN_SHFT                                                    0x0

#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_ADDR(x)                                                  ((x) + 0x000001a8)
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_PHYS(x)                                                  ((x) + 0x000001a8)
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_OFFS                                                     (0x000001a8)
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_RMSK                                                     0x8000003f
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_ADDR(x), HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_RMSK)
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_ADDR(x), m)
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_ADDR(x),v)
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_ADDR(x),m,v,HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_IN(x))
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_EN_BMSK                                                  0x80000000
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_EN_SHFT                                                        0x1f
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_ADDR_BIT_INDEX_BMSK                                            0x3f
#define HWIO_PCIE30_PARF_AXI_MSTR_WR_ADDR_HALT_ADDR_BIT_INDEX_SHFT                                             0x0

#define HWIO_PCIE30_PARF_LTSSM_ADDR(x)                                                                  ((x) + 0x000001b0)
#define HWIO_PCIE30_PARF_LTSSM_PHYS(x)                                                                  ((x) + 0x000001b0)
#define HWIO_PCIE30_PARF_LTSSM_OFFS                                                                     (0x000001b0)
#define HWIO_PCIE30_PARF_LTSSM_RMSK                                                                          0xf3f
#define HWIO_PCIE30_PARF_LTSSM_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_LTSSM_ADDR(x), HWIO_PCIE30_PARF_LTSSM_RMSK)
#define HWIO_PCIE30_PARF_LTSSM_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_LTSSM_ADDR(x), m)
#define HWIO_PCIE30_PARF_LTSSM_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_LTSSM_ADDR(x),v)
#define HWIO_PCIE30_PARF_LTSSM_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_LTSSM_ADDR(x),m,v,HWIO_PCIE30_PARF_LTSSM_IN(x))
#define HWIO_PCIE30_PARF_LTSSM_FLUSH_MODE_BMSK                                                               0x800
#define HWIO_PCIE30_PARF_LTSSM_FLUSH_MODE_SHFT                                                                 0xb
#define HWIO_PCIE30_PARF_LTSSM_SW_CLR_FLUSH_MODE_BMSK                                                        0x400
#define HWIO_PCIE30_PARF_LTSSM_SW_CLR_FLUSH_MODE_SHFT                                                          0xa
#define HWIO_PCIE30_PARF_LTSSM_LINK_DOWN_AFFECT_LTSSM_DIS_BMSK                                               0x200
#define HWIO_PCIE30_PARF_LTSSM_LINK_DOWN_AFFECT_LTSSM_DIS_SHFT                                                 0x9
#define HWIO_PCIE30_PARF_LTSSM_LTSSM_EN_BMSK                                                                 0x100
#define HWIO_PCIE30_PARF_LTSSM_LTSSM_EN_SHFT                                                                   0x8
#define HWIO_PCIE30_PARF_LTSSM_LTSSM_STATE_BMSK                                                               0x3f
#define HWIO_PCIE30_PARF_LTSSM_LTSSM_STATE_SHFT                                                                0x0

#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_ADDR(x)                                                           ((x) + 0x000001b4)
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_PHYS(x)                                                           ((x) + 0x000001b4)
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_OFFS                                                              (0x000001b4)
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_RMSK                                                                   0xfff
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_DBI_ELBI_ADDR(x), HWIO_PCIE30_PARF_SLV_DBI_ELBI_RMSK)
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_DBI_ELBI_ADDR(x), m)
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SLV_DBI_ELBI_ADDR(x),v)
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SLV_DBI_ELBI_ADDR(x),m,v,HWIO_PCIE30_PARF_SLV_DBI_ELBI_IN(x))
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_ADDR_BASE_BMSK                                                         0xfff
#define HWIO_PCIE30_PARF_SLV_DBI_ELBI_ADDR_BASE_SHFT                                                           0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_ADDR(x)                                                  ((x) + 0x000001b8)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_PHYS(x)                                                  ((x) + 0x000001b8)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_OFFS                                                     (0x000001b8)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_RMSK                                                     0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_ADDR_BASE_BMSK                                           0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_ADDR_BASE_SHFT                                                  0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_ADDR(x)                                                 ((x) + 0x000001bc)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_PHYS(x)                                                 ((x) + 0x000001bc)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_OFFS                                                    (0x000001bc)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_RMSK                                                    0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_ADDR_BASE_BMSK                                          0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_ADDR_BASE_SHFT                                                 0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_ADDR(x)                                                  ((x) + 0x000001c0)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_PHYS(x)                                                  ((x) + 0x000001c0)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_OFFS                                                     (0x000001c0)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_RMSK                                                     0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_ADDR_BASE_BMSK                                           0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_ADDR_BASE_SHFT                                                  0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_ADDR(x)                                                 ((x) + 0x000001c4)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_PHYS(x)                                                 ((x) + 0x000001c4)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_OFFS                                                    (0x000001c4)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_RMSK                                                    0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_ADDR_BASE_BMSK                                          0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_ADDR_BASE_SHFT                                                 0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_ADDR(x)                                                    ((x) + 0x000001c8)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_PHYS(x)                                                    ((x) + 0x000001c8)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_OFFS                                                       (0x000001c8)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_RMSK                                                             0x1f
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_RD_STATE_BMSK                                                    0x18
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_RD_STATE_SHFT                                                     0x3
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_WR_STATE_BMSK                                                     0x7
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_DEBUG_WR_STATE_SHFT                                                     0x0

#define HWIO_PCIE30_PARF_ECAM_BASE_ADDR(x)                                                              ((x) + 0x000001cc)
#define HWIO_PCIE30_PARF_ECAM_BASE_PHYS(x)                                                              ((x) + 0x000001cc)
#define HWIO_PCIE30_PARF_ECAM_BASE_OFFS                                                                 (0x000001cc)
#define HWIO_PCIE30_PARF_ECAM_BASE_RMSK                                                                 0xffffffff
#define HWIO_PCIE30_PARF_ECAM_BASE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_BASE_ADDR(x), HWIO_PCIE30_PARF_ECAM_BASE_RMSK)
#define HWIO_PCIE30_PARF_ECAM_BASE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_BASE_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_BASE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_BASE_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_BASE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_BASE_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_BASE_IN(x))
#define HWIO_PCIE30_PARF_ECAM_BASE_BASE_BMSK                                                            0xffffffff
#define HWIO_PCIE30_PARF_ECAM_BASE_BASE_SHFT                                                                   0x0

#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_ADDR(x)                                               ((x) + 0x000001d0)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_PHYS(x)                                               ((x) + 0x000001d0)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_OFFS                                                  (0x000001d0)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_RMSK                                                  0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_ADDR(x), HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_RMSK)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_IN(x))
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_ADDR_BASE_BMSK                                        0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_ADDR_BASE_SHFT                                               0x0

#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_ADDR(x)                                              ((x) + 0x000001d4)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_PHYS(x)                                              ((x) + 0x000001d4)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_OFFS                                                 (0x000001d4)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_RMSK                                                 0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_ADDR(x), HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_RMSK)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_IN(x))
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_ADDR_LIMIT_BMSK                                      0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_ADDR_LIMIT_SHFT                                             0x0

#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_ADDR(x)                                                         ((x) + 0x000001d8)
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_PHYS(x)                                                         ((x) + 0x000001d8)
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_OFFS                                                            (0x000001d8)
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_RMSK                                                            0xffffffff
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SPARE_0_1_BITS_ADDR(x), HWIO_PCIE30_PARF_SPARE_0_1_BITS_RMSK)
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SPARE_0_1_BITS_ADDR(x), m)
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SPARE_0_1_BITS_ADDR(x),v)
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SPARE_0_1_BITS_ADDR(x),m,v,HWIO_PCIE30_PARF_SPARE_0_1_BITS_IN(x))
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_SPARE_1_BMSK                                                    0xffff0000
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_SPARE_1_SHFT                                                          0x10
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_SPARE_0_BMSK                                                        0xffff
#define HWIO_PCIE30_PARF_SPARE_0_1_BITS_SPARE_0_SHFT                                                           0x0

#define HWIO_PCIE30_PARF_RELEASE_VERSION_ADDR(x)                                                        ((x) + 0x000001dc)
#define HWIO_PCIE30_PARF_RELEASE_VERSION_PHYS(x)                                                        ((x) + 0x000001dc)
#define HWIO_PCIE30_PARF_RELEASE_VERSION_OFFS                                                           (0x000001dc)
#define HWIO_PCIE30_PARF_RELEASE_VERSION_RMSK                                                           0xffffffff
#define HWIO_PCIE30_PARF_RELEASE_VERSION_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_RELEASE_VERSION_ADDR(x), HWIO_PCIE30_PARF_RELEASE_VERSION_RMSK)
#define HWIO_PCIE30_PARF_RELEASE_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_RELEASE_VERSION_ADDR(x), m)
#define HWIO_PCIE30_PARF_RELEASE_VERSION_RELEASE_VER_BMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_RELEASE_VERSION_RELEASE_VER_SHFT                                                      0x0

#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_ADDR(x)                                                    ((x) + 0x00000200)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PHYS(x)                                                    ((x) + 0x00000200)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_OFFS                                                       (0x00000200)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_RMSK                                                            0x7ff
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_ADDR(x), HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_RMSK)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_ADDR(x), m)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_DLL_STATE_CHANGE_BMSK                                           0x400
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_DLL_STATE_CHANGE_SHFT                                             0xa
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_HOT_PLUG_INT_CHANGE_BMSK                                        0x200
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_HOT_PLUG_INT_CHANGE_SHFT                                          0x9
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_COMMAND_COMPLETED_CHANGE_BMSK                                   0x100
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_COMMAND_COMPLETED_CHANGE_SHFT                                     0x8
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PRES_DET_CHANGE_BMSK                                             0x80
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PRES_DET_CHANGE_SHFT                                              0x7
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_MRL_SENSOR_CHANGE_BMSK                                           0x40
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_MRL_SENSOR_CHANGE_SHFT                                            0x6
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PWR_FAULT_DET_CHANGE_BMSK                                        0x20
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PWR_FAULT_DET_CHANGE_SHFT                                         0x5
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_ATTEN_BUTTON_CHANGE_BMSK                                         0x10
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_ATTEN_BUTTON_CHANGE_SHFT                                          0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_EML_CONTROL_CHANGED_BMSK                                          0x8
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_EML_CONTROL_CHANGED_SHFT                                          0x3
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PWR_CTRL_CHANGE_BMSK                                              0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PWR_CTRL_CHANGE_SHFT                                              0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_ATTEN_IND_CHANGE_BMSK                                             0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_ATTEN_IND_CHANGE_SHFT                                             0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PWR_IND_CHANGE_BMSK                                               0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_STATUS_PWR_IND_CHANGE_SHFT                                               0x0

#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ADDR(x)                                                      ((x) + 0x00000204)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PHYS(x)                                                      ((x) + 0x00000204)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_OFFS                                                         (0x00000204)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_RMSK                                                              0x7ff
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ADDR(x), HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_RMSK)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ADDR(x), m)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ADDR(x),v)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ADDR(x),m,v,HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_IN(x))
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_DLL_STATE_CHANGE_BMSK                                             0x400
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_DLL_STATE_CHANGE_SHFT                                               0xa
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_HOT_PLUG_INT_CHANGE_BMSK                                          0x200
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_HOT_PLUG_INT_CHANGE_SHFT                                            0x9
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_COMMAND_COMPLETED_CHANGE_BMSK                                     0x100
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_COMMAND_COMPLETED_CHANGE_SHFT                                       0x8
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PRES_DET_CHANGE_BMSK                                               0x80
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PRES_DET_CHANGE_SHFT                                                0x7
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_MRL_SENSOR_CHANGE_BMSK                                             0x40
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_MRL_SENSOR_CHANGE_SHFT                                              0x6
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PWR_FAULT_DET_CHANGE_BMSK                                          0x20
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PWR_FAULT_DET_CHANGE_SHFT                                           0x5
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ATTEN_BUTTON_CHANGE_BMSK                                           0x10
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ATTEN_BUTTON_CHANGE_SHFT                                            0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_EML_CONTROL_CHANGED_BMSK                                            0x8
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_EML_CONTROL_CHANGED_SHFT                                            0x3
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PWR_CTRL_CHANGE_BMSK                                                0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PWR_CTRL_CHANGE_SHFT                                                0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ATTEN_IND_CHANGE_BMSK                                               0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_ATTEN_IND_CHANGE_SHFT                                               0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PWR_IND_CHANGE_BMSK                                                 0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_MASK_PWR_IND_CHANGE_SHFT                                                 0x0

#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_ADDR(x)                                                     ((x) + 0x00000208)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PHYS(x)                                                     ((x) + 0x00000208)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_OFFS                                                        (0x00000208)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_RMSK                                                             0x7ff
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_ADDR(x),v)
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_DLL_STATE_CHANGE_BMSK                                            0x400
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_DLL_STATE_CHANGE_SHFT                                              0xa
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_HOT_PLUG_INT_CHANGE_BMSK                                         0x200
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_HOT_PLUG_INT_CHANGE_SHFT                                           0x9
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_COMMAND_COMPLETED_CHANGE_BMSK                                    0x100
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_COMMAND_COMPLETED_CHANGE_SHFT                                      0x8
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PRES_DET_CHANGE_BMSK                                              0x80
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PRES_DET_CHANGE_SHFT                                               0x7
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_MRL_SENSOR_CHANGE_BMSK                                            0x40
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_MRL_SENSOR_CHANGE_SHFT                                             0x6
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PWR_FAULT_DET_CHANGE_BMSK                                         0x20
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PWR_FAULT_DET_CHANGE_SHFT                                          0x5
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_ATTEN_BUTTON_CHANGE_BMSK                                          0x10
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_ATTEN_BUTTON_CHANGE_SHFT                                           0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_EML_CONTROL_CHANGED_BMSK                                           0x8
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_EML_CONTROL_CHANGED_SHFT                                           0x3
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PWR_CTRL_CHANGE_BMSK                                               0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PWR_CTRL_CHANGE_SHFT                                               0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_ATTEN_IND_CHANGE_BMSK                                              0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_ATTEN_IND_CHANGE_SHFT                                              0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PWR_IND_CHANGE_BMSK                                                0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_INT_CLEAR_PWR_IND_CHANGE_SHFT                                                0x0

#define HWIO_PCIE30_PARF_HOT_PLUG_ADDR(x)                                                               ((x) + 0x00000210)
#define HWIO_PCIE30_PARF_HOT_PLUG_PHYS(x)                                                               ((x) + 0x00000210)
#define HWIO_PCIE30_PARF_HOT_PLUG_OFFS                                                                  (0x00000210)
#define HWIO_PCIE30_PARF_HOT_PLUG_RMSK                                                                        0xff
#define HWIO_PCIE30_PARF_HOT_PLUG_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_HOT_PLUG_ADDR(x), HWIO_PCIE30_PARF_HOT_PLUG_RMSK)
#define HWIO_PCIE30_PARF_HOT_PLUG_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_HOT_PLUG_ADDR(x), m)
#define HWIO_PCIE30_PARF_HOT_PLUG_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_HOT_PLUG_ADDR(x),v)
#define HWIO_PCIE30_PARF_HOT_PLUG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_HOT_PLUG_ADDR(x),m,v,HWIO_PCIE30_PARF_HOT_PLUG_IN(x))
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_EML_INTERLOCK_ENGAGED_BMSK                                              0x80
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_EML_INTERLOCK_ENGAGED_SHFT                                               0x7
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_CMD_CPLED_INT_BMSK                                                      0x40
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_CMD_CPLED_INT_SHFT                                                       0x6
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_PRE_DET_CHANGED_BMSK                                                    0x20
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_PRE_DET_CHANGED_SHFT                                                     0x5
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_MRL_SENSOR_CHANGED_BMSK                                                 0x10
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_MRL_SENSOR_CHANGED_SHFT                                                  0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_PWR_FAULT_DET_BMSK                                                       0x8
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_PWR_FAULT_DET_SHFT                                                       0x3
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_MRL_SENSOR_STATE_BMSK                                                    0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_MRL_SENSOR_STATE_SHFT                                                    0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_PRE_DET_STATE_BMSK                                                       0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_PRE_DET_STATE_SHFT                                                       0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_ATTEN_PRESS_BMSK                                                         0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_SYS_ATTEN_PRESS_SHFT                                                         0x0

#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_ADDR(x)                                                        ((x) + 0x00000214)
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_PHYS(x)                                                        ((x) + 0x00000214)
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_OFFS                                                           (0x00000214)
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_RMSK                                                                  0xf
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_HOT_PLUG_STATUS_ADDR(x), HWIO_PCIE30_PARF_HOT_PLUG_STATUS_RMSK)
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_HOT_PLUG_STATUS_ADDR(x), m)
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_HOT_PLUG_STATUS_ADDR(x),v)
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_HOT_PLUG_STATUS_ADDR(x),m,v,HWIO_PCIE30_PARF_HOT_PLUG_STATUS_IN(x))
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_HP_MSI_BMSK                                                           0x8
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_HP_MSI_SHFT                                                           0x3
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_HP_PME_BMSK                                                           0x4
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_HP_PME_SHFT                                                           0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_HP_INT_BMSK                                                           0x2
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_HP_INT_SHFT                                                           0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_CFG_EML_CTRL_BMSK                                                     0x1
#define HWIO_PCIE30_PARF_HOT_PLUG_STATUS_CFG_EML_CTRL_SHFT                                                     0x0

#define HWIO_PCIE30_PARF_CFG_BITS_ADDR(x)                                                               ((x) + 0x00000218)
#define HWIO_PCIE30_PARF_CFG_BITS_PHYS(x)                                                               ((x) + 0x00000218)
#define HWIO_PCIE30_PARF_CFG_BITS_OFFS                                                                  (0x00000218)
#define HWIO_PCIE30_PARF_CFG_BITS_RMSK                                                                  0x39ffffff
#define HWIO_PCIE30_PARF_CFG_BITS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_CFG_BITS_ADDR(x), HWIO_PCIE30_PARF_CFG_BITS_RMSK)
#define HWIO_PCIE30_PARF_CFG_BITS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_CFG_BITS_ADDR(x), m)
#define HWIO_PCIE30_PARF_CFG_BITS_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_CFG_BITS_ADDR(x),v)
#define HWIO_PCIE30_PARF_CFG_BITS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_CFG_BITS_ADDR(x),m,v,HWIO_PCIE30_PARF_CFG_BITS_IN(x))
#define HWIO_PCIE30_PARF_CFG_BITS_MSTR_ACLK_GATED_IN_L0_BMSK                                            0x20000000
#define HWIO_PCIE30_PARF_CFG_BITS_MSTR_ACLK_GATED_IN_L0_SHFT                                                  0x1d
#define HWIO_PCIE30_PARF_CFG_BITS_QSMMU_CGC_OPEN_BMSK                                                   0x10000000
#define HWIO_PCIE30_PARF_CFG_BITS_QSMMU_CGC_OPEN_SHFT                                                         0x1c
#define HWIO_PCIE30_PARF_CFG_BITS_AHB_CGC_OPEN_BMSK                                                      0x8000000
#define HWIO_PCIE30_PARF_CFG_BITS_AHB_CGC_OPEN_SHFT                                                           0x1b
#define HWIO_PCIE30_PARF_CFG_BITS_HOT_PLUG_INT_TYPE_BMSK                                                 0x1000000
#define HWIO_PCIE30_PARF_CFG_BITS_HOT_PLUG_INT_TYPE_SHFT                                                      0x18
#define HWIO_PCIE30_PARF_CFG_BITS_NOC_MSTR_AWREADY_FIX2_EN_BMSK                                           0x800000
#define HWIO_PCIE30_PARF_CFG_BITS_NOC_MSTR_AWREADY_FIX2_EN_SHFT                                               0x17
#define HWIO_PCIE30_PARF_CFG_BITS_PARF_SLV_SECOND_CGC_EN_OPTION_BMSK                                      0x400000
#define HWIO_PCIE30_PARF_CFG_BITS_PARF_SLV_SECOND_CGC_EN_OPTION_SHFT                                          0x16
#define HWIO_PCIE30_PARF_CFG_BITS_PARF_MSTR_SECOND_CGC_EN_OPTION_BMSK                                     0x200000
#define HWIO_PCIE30_PARF_CFG_BITS_PARF_MSTR_SECOND_CGC_EN_OPTION_SHFT                                         0x15
#define HWIO_PCIE30_PARF_CFG_BITS_PARF_ADD_APP_REQ_EXIT_L1_BMSK                                           0x100000
#define HWIO_PCIE30_PARF_CFG_BITS_PARF_ADD_APP_REQ_EXIT_L1_SHFT                                               0x14
#define HWIO_PCIE30_PARF_CFG_BITS_PARF_ADD_APP_XFER_PENDING_BMSK                                           0x80000
#define HWIO_PCIE30_PARF_CFG_BITS_PARF_ADD_APP_XFER_PENDING_SHFT                                              0x13
#define HWIO_PCIE30_PARF_CFG_BITS_UPD_MSTR_WR_HALT_ADDR_FIX_EN_BMSK                                        0x40000
#define HWIO_PCIE30_PARF_CFG_BITS_UPD_MSTR_WR_HALT_ADDR_FIX_EN_SHFT                                           0x12
#define HWIO_PCIE30_PARF_CFG_BITS_FIRST_RAM_CLK_MASK_FIX_EN_BMSK                                           0x20000
#define HWIO_PCIE30_PARF_CFG_BITS_FIRST_RAM_CLK_MASK_FIX_EN_SHFT                                              0x11
#define HWIO_PCIE30_PARF_CFG_BITS_NOC_MSTR_AWREADY_FIX_EN_BMSK                                             0x10000
#define HWIO_PCIE30_PARF_CFG_BITS_NOC_MSTR_AWREADY_FIX_EN_SHFT                                                0x10
#define HWIO_PCIE30_PARF_CFG_BITS_SLV_WAKEUP_VALID_FIX_EN_BMSK                                              0x8000
#define HWIO_PCIE30_PARF_CFG_BITS_SLV_WAKEUP_VALID_FIX_EN_SHFT                                                 0xf
#define HWIO_PCIE30_PARF_CFG_BITS_TESTBUS_SWITCH_BMSK                                                       0x4000
#define HWIO_PCIE30_PARF_CFG_BITS_TESTBUS_SWITCH_SHFT                                                          0xe
#define HWIO_PCIE30_PARF_CFG_BITS_BRIDGE_FLUSH_INT_CNT_EN_BMSK                                              0x2000
#define HWIO_PCIE30_PARF_CFG_BITS_BRIDGE_FLUSH_INT_CNT_EN_SHFT                                                 0xd
#define HWIO_PCIE30_PARF_CFG_BITS_MSTR_WR_DMA_NS_BMSK                                                       0x1000
#define HWIO_PCIE30_PARF_CFG_BITS_MSTR_WR_DMA_NS_SHFT                                                          0xc
#define HWIO_PCIE30_PARF_CFG_BITS_MSTR_RD_DMA_NS_BMSK                                                        0x800
#define HWIO_PCIE30_PARF_CFG_BITS_MSTR_RD_DMA_NS_SHFT                                                          0xb
#define HWIO_PCIE30_PARF_CFG_BITS_DEBUG_CNT_CLK_EN_MSTR_BMSK                                                 0x400
#define HWIO_PCIE30_PARF_CFG_BITS_DEBUG_CNT_CLK_EN_MSTR_SHFT                                                   0xa
#define HWIO_PCIE30_PARF_CFG_BITS_DEBUG_CNT_CLK_EN_BMSK                                                      0x200
#define HWIO_PCIE30_PARF_CFG_BITS_DEBUG_CNT_CLK_EN_SHFT                                                        0x9
#define HWIO_PCIE30_PARF_CFG_BITS_SLV_AMISC_INFO_ATU_BYPASS_BMSK                                             0x180
#define HWIO_PCIE30_PARF_CFG_BITS_SLV_AMISC_INFO_ATU_BYPASS_SHFT                                               0x7
#define HWIO_PCIE30_PARF_CFG_BITS_USE_LANE_FLIP_EN_BMSK                                                       0x60
#define HWIO_PCIE30_PARF_CFG_BITS_USE_LANE_FLIP_EN_SHFT                                                        0x5
#define HWIO_PCIE30_PARF_CFG_BITS_SNPS_CLKREQ_SECOND_FIX_BMSK                                                 0x10
#define HWIO_PCIE30_PARF_CFG_BITS_SNPS_CLKREQ_SECOND_FIX_SHFT                                                  0x4
#define HWIO_PCIE30_PARF_CFG_BITS_USE_CFG_L1SUB_EN_BMSK                                                        0x4
#define HWIO_PCIE30_PARF_CFG_BITS_USE_CFG_L1SUB_EN_SHFT                                                        0x2
#define HWIO_PCIE30_PARF_CFG_BITS_REQ_EXIT_L1SS_MSI_LTR_EN_BMSK                                                0x2
#define HWIO_PCIE30_PARF_CFG_BITS_REQ_EXIT_L1SS_MSI_LTR_EN_SHFT                                                0x1
#define HWIO_PCIE30_PARF_CFG_BITS_LTR_MSI_HREADY_LOW_EN_BMSK                                                   0x1
#define HWIO_PCIE30_PARF_CFG_BITS_LTR_MSI_HREADY_LOW_EN_SHFT                                                   0x0

#define HWIO_PCIE30_PARF_INT_MASK_ADDR(x)                                                               ((x) + 0x0000021c)
#define HWIO_PCIE30_PARF_INT_MASK_PHYS(x)                                                               ((x) + 0x0000021c)
#define HWIO_PCIE30_PARF_INT_MASK_OFFS                                                                  (0x0000021c)
#define HWIO_PCIE30_PARF_INT_MASK_RMSK                                                                         0xf
#define HWIO_PCIE30_PARF_INT_MASK_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_INT_MASK_ADDR(x), HWIO_PCIE30_PARF_INT_MASK_RMSK)
#define HWIO_PCIE30_PARF_INT_MASK_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_INT_MASK_ADDR(x), m)
#define HWIO_PCIE30_PARF_INT_MASK_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_INT_MASK_ADDR(x),v)
#define HWIO_PCIE30_PARF_INT_MASK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_INT_MASK_ADDR(x),m,v,HWIO_PCIE30_PARF_INT_MASK_IN(x))
#define HWIO_PCIE30_PARF_INT_MASK_PCIE30_INT_BRIDGE_FLUSH_MASK_BMSK                                            0x8
#define HWIO_PCIE30_PARF_INT_MASK_PCIE30_INT_BRIDGE_FLUSH_MASK_SHFT                                            0x3
#define HWIO_PCIE30_PARF_INT_MASK_AMBA_ORDR_MGR_WDT_MASK_BMSK                                                  0x4
#define HWIO_PCIE30_PARF_INT_MASK_AMBA_ORDR_MGR_WDT_MASK_SHFT                                                  0x2
#define HWIO_PCIE30_PARF_INT_MASK_RADM_QOVERFLOW_MASK_BMSK                                                     0x3
#define HWIO_PCIE30_PARF_INT_MASK_RADM_QOVERFLOW_MASK_SHFT                                                     0x0

#define HWIO_PCIE30_PARF_INT_CLEAR_ADDR(x)                                                              ((x) + 0x00000220)
#define HWIO_PCIE30_PARF_INT_CLEAR_PHYS(x)                                                              ((x) + 0x00000220)
#define HWIO_PCIE30_PARF_INT_CLEAR_OFFS                                                                 (0x00000220)
#define HWIO_PCIE30_PARF_INT_CLEAR_RMSK                                                                        0x7
#define HWIO_PCIE30_PARF_INT_CLEAR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_INT_CLEAR_ADDR(x),v)
#define HWIO_PCIE30_PARF_INT_CLEAR_AMBA_ORDR_MGR_WDT_CLEAR_BMSK                                                0x4
#define HWIO_PCIE30_PARF_INT_CLEAR_AMBA_ORDR_MGR_WDT_CLEAR_SHFT                                                0x2
#define HWIO_PCIE30_PARF_INT_CLEAR_RADM_QOVERFLOW_CLEAR_BMSK                                                   0x3
#define HWIO_PCIE30_PARF_INT_CLEAR_RADM_QOVERFLOW_CLEAR_SHFT                                                   0x0

#define HWIO_PCIE30_PARF_INT_STATUS_ADDR(x)                                                             ((x) + 0x00000224)
#define HWIO_PCIE30_PARF_INT_STATUS_PHYS(x)                                                             ((x) + 0x00000224)
#define HWIO_PCIE30_PARF_INT_STATUS_OFFS                                                                (0x00000224)
#define HWIO_PCIE30_PARF_INT_STATUS_RMSK                                                                       0x7
#define HWIO_PCIE30_PARF_INT_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_INT_STATUS_ADDR(x), HWIO_PCIE30_PARF_INT_STATUS_RMSK)
#define HWIO_PCIE30_PARF_INT_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_INT_STATUS_ADDR(x), m)
#define HWIO_PCIE30_PARF_INT_STATUS_AMBA_ORDR_MGR_WDT_BMSK                                                     0x4
#define HWIO_PCIE30_PARF_INT_STATUS_AMBA_ORDR_MGR_WDT_SHFT                                                     0x2
#define HWIO_PCIE30_PARF_INT_STATUS_RADM_QOVERFLOW_BMSK                                                        0x3
#define HWIO_PCIE30_PARF_INT_STATUS_RADM_QOVERFLOW_SHFT                                                        0x0

#define HWIO_PCIE30_STATUS_ADDR(x)                                                                      ((x) + 0x00000228)
#define HWIO_PCIE30_STATUS_PHYS(x)                                                                      ((x) + 0x00000228)
#define HWIO_PCIE30_STATUS_OFFS                                                                         (0x00000228)
#define HWIO_PCIE30_STATUS_RMSK                                                                              0x3e9
#define HWIO_PCIE30_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_STATUS_ADDR(x), HWIO_PCIE30_STATUS_RMSK)
#define HWIO_PCIE30_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_STATUS_ADDR(x), m)
#define HWIO_PCIE30_STATUS_FLUSH_COMPLETED_BMSK                                                              0x200
#define HWIO_PCIE30_STATUS_FLUSH_COMPLETED_SHFT                                                                0x9
#define HWIO_PCIE30_STATUS_RADM_Q_NOT_EMPTY_BMSK                                                             0x180
#define HWIO_PCIE30_STATUS_RADM_Q_NOT_EMPTY_SHFT                                                               0x7
#define HWIO_PCIE30_STATUS_SMLH_REQ_RST_NOT_BMSK                                                              0x40
#define HWIO_PCIE30_STATUS_SMLH_REQ_RST_NOT_SHFT                                                               0x6
#define HWIO_PCIE30_STATUS_RADM_XFER_PENDING_BMSK                                                             0x20
#define HWIO_PCIE30_STATUS_RADM_XFER_PENDING_SHFT                                                              0x5
#define HWIO_PCIE30_STATUS_BRIDGE_SLV_XFER_PENDING_BMSK                                                        0x8
#define HWIO_PCIE30_STATUS_BRIDGE_SLV_XFER_PENDING_SHFT                                                        0x3
#define HWIO_PCIE30_STATUS_BRIDGE_FLUSH_NOT_BMSK                                                               0x1
#define HWIO_PCIE30_STATUS_BRIDGE_FLUSH_NOT_SHFT                                                               0x0

#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_ADDR(x)                                                       ((x) + 0x0000022c)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_PHYS(x)                                                       ((x) + 0x0000022c)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_OFFS                                                          (0x0000022c)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_RMSK                                                          0xffffffff
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_ADDR(x), HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_RMSK)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_IN(x))
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_DBI_BASE_ADDR_LO_BMSK                                         0xffffffff
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_DBI_BASE_ADDR_LO_SHFT                                                0x0

#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_ADDR(x)                                                       ((x) + 0x00000230)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_PHYS(x)                                                       ((x) + 0x00000230)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_OFFS                                                          (0x00000230)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_RMSK                                                          0xffffffff
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_ADDR(x), HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_RMSK)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_IN(x))
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_DBI_BASE_ADDR_HI_BMSK                                         0xffffffff
#define HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_DBI_BASE_ADDR_HI_SHFT                                                0x0

#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_ADDR(x)                                                 ((x) + 0x00000234)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_PHYS(x)                                                 ((x) + 0x00000234)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_OFFS                                                    (0x00000234)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_RMSK                                                    0xffffffff
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_ADDR(x), HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_RMSK)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_IN(x))
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_SLV_ADDR_SPACE_SIZE_LO_BMSK                             0xffffffff
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_SLV_ADDR_SPACE_SIZE_LO_SHFT                                    0x0

#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_ADDR(x)                                                 ((x) + 0x00000238)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_PHYS(x)                                                 ((x) + 0x00000238)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_OFFS                                                    (0x00000238)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_RMSK                                                    0xffffffff
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_ADDR(x), HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_RMSK)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_IN(x))
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_SLV_ADDR_SPACE_SIZE_HI_BMSK                             0xffffffff
#define HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_SLV_ADDR_SPACE_SIZE_HI_SHFT                                    0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_ADDR(x)                                               ((x) + 0x0000023c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_PHYS(x)                                               ((x) + 0x0000023c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_OFFS                                                  (0x0000023c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_RMSK                                                  0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_ADDR_BASE_LO_BMSK                                     0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_ADDR_BASE_LO_SHFT                                            0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_ADDR(x)                                               ((x) + 0x00000240)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_PHYS(x)                                               ((x) + 0x00000240)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_OFFS                                                  (0x00000240)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_RMSK                                                  0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_ADDR_BASE_HI_BMSK                                     0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_ADDR_BASE_HI_SHFT                                            0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_ADDR(x)                                              ((x) + 0x00000244)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_PHYS(x)                                              ((x) + 0x00000244)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_OFFS                                                 (0x00000244)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_RMSK                                                 0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_ADDR_BASE_LO_BMSK                                    0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_ADDR_BASE_LO_SHFT                                           0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_ADDR(x)                                              ((x) + 0x00000248)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_PHYS(x)                                              ((x) + 0x00000248)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_OFFS                                                 (0x00000248)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_RMSK                                                 0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_ADDR_BASE_HI_BMSK                                    0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_ADDR_BASE_HI_SHFT                                           0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_ADDR(x)                                               ((x) + 0x0000024c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_PHYS(x)                                               ((x) + 0x0000024c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_OFFS                                                  (0x0000024c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_RMSK                                                  0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_ADDR_BASE_LO_BMSK                                     0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_ADDR_BASE_LO_SHFT                                            0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_ADDR(x)                                               ((x) + 0x00000250)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_PHYS(x)                                               ((x) + 0x00000250)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_OFFS                                                  (0x00000250)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_RMSK                                                  0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_ADDR_BASE_HI_BMSK                                     0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_ADDR_BASE_HI_SHFT                                            0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_ADDR(x)                                              ((x) + 0x00000254)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_PHYS(x)                                              ((x) + 0x00000254)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_OFFS                                                 (0x00000254)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_RMSK                                                 0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_ADDR_BASE_LO_BMSK                                    0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_ADDR_BASE_LO_SHFT                                           0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_ADDR(x)                                              ((x) + 0x00000258)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_PHYS(x)                                              ((x) + 0x00000258)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_OFFS                                                 (0x00000258)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_RMSK                                                 0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_ADDR_BASE_HI_BMSK                                    0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_ADDR_BASE_HI_SHFT                                           0x0

#define HWIO_PCIE30_PARF_ECAM_BASE_LO_ADDR(x)                                                           ((x) + 0x0000025c)
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_PHYS(x)                                                           ((x) + 0x0000025c)
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_OFFS                                                              (0x0000025c)
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_RMSK                                                              0xffffffff
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_BASE_LO_ADDR(x), HWIO_PCIE30_PARF_ECAM_BASE_LO_RMSK)
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_BASE_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_BASE_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_BASE_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_BASE_LO_IN(x))
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_BASE_LO_BMSK                                                      0xffffffff
#define HWIO_PCIE30_PARF_ECAM_BASE_LO_BASE_LO_SHFT                                                             0x0

#define HWIO_PCIE30_PARF_ECAM_BASE_HI_ADDR(x)                                                           ((x) + 0x00000260)
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_PHYS(x)                                                           ((x) + 0x00000260)
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_OFFS                                                              (0x00000260)
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_RMSK                                                              0xffffffff
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_BASE_HI_ADDR(x), HWIO_PCIE30_PARF_ECAM_BASE_HI_RMSK)
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_BASE_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_BASE_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_BASE_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_BASE_HI_IN(x))
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_BASE_HI_BMSK                                                      0xffffffff
#define HWIO_PCIE30_PARF_ECAM_BASE_HI_BASE_HI_SHFT                                                             0x0

#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_ADDR(x)                                            ((x) + 0x00000264)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_PHYS(x)                                            ((x) + 0x00000264)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_OFFS                                               (0x00000264)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_RMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_ADDR(x), HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_RMSK)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_IN(x))
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_ADDR_BASE_LO_BMSK                                  0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_ADDR_BASE_LO_SHFT                                         0x0

#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_ADDR(x)                                            ((x) + 0x00000268)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_PHYS(x)                                            ((x) + 0x00000268)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_OFFS                                               (0x00000268)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_RMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_ADDR(x), HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_RMSK)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_IN(x))
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_ADDR_BASE_HI_BMSK                                  0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_ADDR_BASE_HI_SHFT                                         0x0

#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_ADDR(x)                                           ((x) + 0x0000026c)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_PHYS(x)                                           ((x) + 0x0000026c)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_OFFS                                              (0x0000026c)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_RMSK                                              0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_ADDR(x), HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_RMSK)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_IN(x))
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_ADDR_LIMIT_LO_BMSK                                0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_ADDR_LIMIT_LO_SHFT                                       0x0

#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_ADDR(x)                                           ((x) + 0x00000270)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_PHYS(x)                                           ((x) + 0x00000270)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_OFFS                                              (0x00000270)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_RMSK                                              0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_ADDR(x), HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_RMSK)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_IN(x))
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_ADDR_LIMIT_HI_BMSK                                0xffffffff
#define HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_ADDR_LIMIT_HI_SHFT                                       0x0

#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_ADDR(base,n)                                                     ((base) + 0x00000274 + 0x8 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_PHYS(base,n)                                                     ((base) + 0x00000274 + 0x8 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_OFFS(base,n)                                                     (0x00000274 + 0x8 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_RMSK                                                             0xffffffff
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_MAXn                                                                     15
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_ADDR_LO_n_ADDR(base,n), HWIO_PCIE30_PARF_MSG_ADDR_LO_n_RMSK)
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_ADDR_LO_n_ADDR(base,n), mask)
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_OUTI(base,n,val)    \
        out_dword(HWIO_PCIE30_PARF_MSG_ADDR_LO_n_ADDR(base,n),val)
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSG_ADDR_LO_n_ADDR(base,n),mask,val,HWIO_PCIE30_PARF_MSG_ADDR_LO_n_INI(base,n))
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_MSG_ADDR_LO_BMSK                                                 0xffffffff
#define HWIO_PCIE30_PARF_MSG_ADDR_LO_n_MSG_ADDR_LO_SHFT                                                        0x0

#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_ADDR(base,n)                                                     ((base) + 0x00000278 + 0x8 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_PHYS(base,n)                                                     ((base) + 0x00000278 + 0x8 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_OFFS(base,n)                                                     (0x00000278 + 0x8 * (n))
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_RMSK                                                             0xffffffff
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_MAXn                                                                     15
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_ADDR_HI_n_ADDR(base,n), HWIO_PCIE30_PARF_MSG_ADDR_HI_n_RMSK)
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_ADDR_HI_n_ADDR(base,n), mask)
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_OUTI(base,n,val)    \
        out_dword(HWIO_PCIE30_PARF_MSG_ADDR_HI_n_ADDR(base,n),val)
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSG_ADDR_HI_n_ADDR(base,n),mask,val,HWIO_PCIE30_PARF_MSG_ADDR_HI_n_INI(base,n))
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_MSG_ADDR_HI_BMSK                                                 0xffffffff
#define HWIO_PCIE30_PARF_MSG_ADDR_HI_n_MSG_ADDR_HI_SHFT                                                        0x0

#define HWIO_PCIE30_INT_ALL_0_STATUS_ADDR(x)                                                            ((x) + 0x00000300)
#define HWIO_PCIE30_INT_ALL_0_STATUS_PHYS(x)                                                            ((x) + 0x00000300)
#define HWIO_PCIE30_INT_ALL_0_STATUS_OFFS                                                               (0x00000300)
#define HWIO_PCIE30_INT_ALL_0_STATUS_RMSK                                                               0xffffffff
#define HWIO_PCIE30_INT_ALL_0_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_INT_ALL_0_STATUS_ADDR(x), HWIO_PCIE30_INT_ALL_0_STATUS_RMSK)
#define HWIO_PCIE30_INT_ALL_0_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_INT_ALL_0_STATUS_ADDR(x), m)
#define HWIO_PCIE30_INT_ALL_0_STATUS_PCIE30_INT_BMSK                                                    0xffffffff
#define HWIO_PCIE30_INT_ALL_0_STATUS_PCIE30_INT_SHFT                                                           0x0

#define HWIO_PCIE30_INT_ALL_1_STATUS_ADDR(x)                                                            ((x) + 0x00000304)
#define HWIO_PCIE30_INT_ALL_1_STATUS_PHYS(x)                                                            ((x) + 0x00000304)
#define HWIO_PCIE30_INT_ALL_1_STATUS_OFFS                                                               (0x00000304)
#define HWIO_PCIE30_INT_ALL_1_STATUS_RMSK                                                               0xffffffff
#define HWIO_PCIE30_INT_ALL_1_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_INT_ALL_1_STATUS_ADDR(x), HWIO_PCIE30_INT_ALL_1_STATUS_RMSK)
#define HWIO_PCIE30_INT_ALL_1_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_INT_ALL_1_STATUS_ADDR(x), m)
#define HWIO_PCIE30_INT_ALL_1_STATUS_PCIE30_INT_BMSK                                                    0xffffffff
#define HWIO_PCIE30_INT_ALL_1_STATUS_PCIE30_INT_SHFT                                                           0x0

#define HWIO_PCIE30_INT_ALL_0_CLEAR_ADDR(x)                                                             ((x) + 0x00000308)
#define HWIO_PCIE30_INT_ALL_0_CLEAR_PHYS(x)                                                             ((x) + 0x00000308)
#define HWIO_PCIE30_INT_ALL_0_CLEAR_OFFS                                                                (0x00000308)
#define HWIO_PCIE30_INT_ALL_0_CLEAR_RMSK                                                                0xffffffff
#define HWIO_PCIE30_INT_ALL_0_CLEAR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_INT_ALL_0_CLEAR_ADDR(x),v)
#define HWIO_PCIE30_INT_ALL_0_CLEAR_PCIE30_INT_CLEAR_BMSK                                               0xffffffff
#define HWIO_PCIE30_INT_ALL_0_CLEAR_PCIE30_INT_CLEAR_SHFT                                                      0x0

#define HWIO_PCIE30_INT_ALL_1_CLEAR_ADDR(x)                                                             ((x) + 0x0000030c)
#define HWIO_PCIE30_INT_ALL_1_CLEAR_PHYS(x)                                                             ((x) + 0x0000030c)
#define HWIO_PCIE30_INT_ALL_1_CLEAR_OFFS                                                                (0x0000030c)
#define HWIO_PCIE30_INT_ALL_1_CLEAR_RMSK                                                                0xffffffff
#define HWIO_PCIE30_INT_ALL_1_CLEAR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_INT_ALL_1_CLEAR_ADDR(x),v)
#define HWIO_PCIE30_INT_ALL_1_CLEAR_PCIE30_INT_CLEAR_BMSK                                               0xffffffff
#define HWIO_PCIE30_INT_ALL_1_CLEAR_PCIE30_INT_CLEAR_SHFT                                                      0x0

#define HWIO_PCIE30_DBG_CNT_SEL_ADDR(x)                                                                 ((x) + 0x00000310)
#define HWIO_PCIE30_DBG_CNT_SEL_PHYS(x)                                                                 ((x) + 0x00000310)
#define HWIO_PCIE30_DBG_CNT_SEL_OFFS                                                                    (0x00000310)
#define HWIO_PCIE30_DBG_CNT_SEL_RMSK                                                                        0x3f03
#define HWIO_PCIE30_DBG_CNT_SEL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_DBG_CNT_SEL_ADDR(x), HWIO_PCIE30_DBG_CNT_SEL_RMSK)
#define HWIO_PCIE30_DBG_CNT_SEL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_DBG_CNT_SEL_ADDR(x), m)
#define HWIO_PCIE30_DBG_CNT_SEL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_DBG_CNT_SEL_ADDR(x),v)
#define HWIO_PCIE30_DBG_CNT_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_DBG_CNT_SEL_ADDR(x),m,v,HWIO_PCIE30_DBG_CNT_SEL_IN(x))
#define HWIO_PCIE30_DBG_CNT_SEL_DBG_CNT_SEL_BMSK                                                            0x3f00
#define HWIO_PCIE30_DBG_CNT_SEL_DBG_CNT_SEL_SHFT                                                               0x8
#define HWIO_PCIE30_DBG_CNT_SEL_READ_WRITE_N_BMSK                                                              0x2
#define HWIO_PCIE30_DBG_CNT_SEL_READ_WRITE_N_SHFT                                                              0x1
#define HWIO_PCIE30_DBG_CNT_SEL_VALID_BMSK                                                                     0x1
#define HWIO_PCIE30_DBG_CNT_SEL_VALID_SHFT                                                                     0x0

#define HWIO_PCIE30_DBG_CNT_ADDR(x)                                                                     ((x) + 0x00000314)
#define HWIO_PCIE30_DBG_CNT_PHYS(x)                                                                     ((x) + 0x00000314)
#define HWIO_PCIE30_DBG_CNT_OFFS                                                                        (0x00000314)
#define HWIO_PCIE30_DBG_CNT_RMSK                                                                        0xffffffff
#define HWIO_PCIE30_DBG_CNT_IN(x)      \
        in_dword_masked(HWIO_PCIE30_DBG_CNT_ADDR(x), HWIO_PCIE30_DBG_CNT_RMSK)
#define HWIO_PCIE30_DBG_CNT_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_DBG_CNT_ADDR(x), m)
#define HWIO_PCIE30_DBG_CNT_OUT(x, v)      \
        out_dword(HWIO_PCIE30_DBG_CNT_ADDR(x),v)
#define HWIO_PCIE30_DBG_CNT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_DBG_CNT_ADDR(x),m,v,HWIO_PCIE30_DBG_CNT_IN(x))
#define HWIO_PCIE30_DBG_CNT_DBG_CNT_BMSK                                                                0xffffffff
#define HWIO_PCIE30_DBG_CNT_DBG_CNT_SHFT                                                                       0x0

#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_ADDR(x)                                                        ((x) + 0x00000318)
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_PHYS(x)                                                        ((x) + 0x00000318)
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_OFFS                                                           (0x00000318)
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_RMSK                                                           0xffffffff
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_TEST_BUS_BYPASS_ADDR(x), HWIO_PCIE30_PARF_TEST_BUS_BYPASS_RMSK)
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_TEST_BUS_BYPASS_ADDR(x), m)
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_TEST_BUS_BYPASS_ADDR(x),v)
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_TEST_BUS_BYPASS_ADDR(x),m,v,HWIO_PCIE30_PARF_TEST_BUS_BYPASS_IN(x))
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_BYPASS_VALUE_BMSK                                              0xffffffff
#define HWIO_PCIE30_PARF_TEST_BUS_BYPASS_BYPASS_VALUE_SHFT                                                     0x0

#define HWIO_PCIE30_PARF_SEGMENT_ID_ADDR(x)                                                             ((x) + 0x0000031c)
#define HWIO_PCIE30_PARF_SEGMENT_ID_PHYS(x)                                                             ((x) + 0x0000031c)
#define HWIO_PCIE30_PARF_SEGMENT_ID_OFFS                                                                (0x0000031c)
#define HWIO_PCIE30_PARF_SEGMENT_ID_RMSK                                                                    0xffff
#define HWIO_PCIE30_PARF_SEGMENT_ID_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SEGMENT_ID_ADDR(x), HWIO_PCIE30_PARF_SEGMENT_ID_RMSK)
#define HWIO_PCIE30_PARF_SEGMENT_ID_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SEGMENT_ID_ADDR(x), m)
#define HWIO_PCIE30_PARF_SEGMENT_ID_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SEGMENT_ID_ADDR(x),v)
#define HWIO_PCIE30_PARF_SEGMENT_ID_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SEGMENT_ID_ADDR(x),m,v,HWIO_PCIE30_PARF_SEGMENT_ID_IN(x))
#define HWIO_PCIE30_PARF_SEGMENT_ID_SEGMENT_ID_BMSK                                                         0xffff
#define HWIO_PCIE30_PARF_SEGMENT_ID_SEGMENT_ID_SHFT                                                            0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_ADDR(x)                                             ((x) + 0x00000320)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_PHYS(x)                                             ((x) + 0x00000320)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_OFFS                                                (0x00000320)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_RMSK                                                0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_ADDR_BASE_LO_BMSK                                   0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_ADDR_BASE_LO_SHFT                                          0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_ADDR(x)                                             ((x) + 0x00000324)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_PHYS(x)                                             ((x) + 0x00000324)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_OFFS                                                (0x00000324)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_RMSK                                                0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_ADDR_BASE_HI_BMSK                                   0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_ADDR_BASE_HI_SHFT                                          0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_ADDR(x)                                            ((x) + 0x00000328)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_PHYS(x)                                            ((x) + 0x00000328)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_OFFS                                               (0x00000328)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_RMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_ADDR_BASE_LO_BMSK                                  0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_ADDR_BASE_LO_SHFT                                         0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_ADDR(x)                                            ((x) + 0x0000032c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_PHYS(x)                                            ((x) + 0x0000032c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_OFFS                                               (0x0000032c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_RMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_ADDR_BASE_HI_BMSK                                  0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_ADDR_BASE_HI_SHFT                                         0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_ADDR(x)                                             ((x) + 0x00000330)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_PHYS(x)                                             ((x) + 0x00000330)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_OFFS                                                (0x00000330)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_RMSK                                                0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_ADDR_BASE_LO_BMSK                                   0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_ADDR_BASE_LO_SHFT                                          0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_ADDR(x)                                             ((x) + 0x00000334)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_PHYS(x)                                             ((x) + 0x00000334)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_OFFS                                                (0x00000334)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_RMSK                                                0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_ADDR_BASE_HI_BMSK                                   0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_ADDR_BASE_HI_SHFT                                          0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_ADDR(x)                                            ((x) + 0x00000338)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_PHYS(x)                                            ((x) + 0x00000338)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_OFFS                                               (0x00000338)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_RMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_ADDR_BASE_LO_BMSK                                  0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_ADDR_BASE_LO_SHFT                                         0x0

#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_ADDR(x)                                            ((x) + 0x0000033c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_PHYS(x)                                            ((x) + 0x0000033c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_OFFS                                               (0x0000033c)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_RMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_ADDR(x), HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_RMSK)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_ADDR(x), m)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_ADDR(x),v)
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_ADDR(x),m,v,HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_IN(x))
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_ADDR_BASE_HI_BMSK                                  0xffffffff
#define HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_ADDR_BASE_HI_SHFT                                         0x0

#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_ADDR(base,n)                                                    ((base) + 0x00000344 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_PHYS(base,n)                                                    ((base) + 0x00000344 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_OFFS(base,n)                                                    (0x00000344 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_RMSK                                                            0xffffffff
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_MAXn                                                                    15
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_HDR_8_11_n_ADDR(base,n), HWIO_PCIE30_PARF_MSG_HDR_8_11_n_RMSK)
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_HDR_8_11_n_ADDR(base,n), mask)
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_OUTI(base,n,val)    \
        out_dword(HWIO_PCIE30_PARF_MSG_HDR_8_11_n_ADDR(base,n),val)
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSG_HDR_8_11_n_ADDR(base,n),mask,val,HWIO_PCIE30_PARF_MSG_HDR_8_11_n_INI(base,n))
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_MSG_HDR_8_11_BMSK                                               0xffffffff
#define HWIO_PCIE30_PARF_MSG_HDR_8_11_n_MSG_HDR_8_11_SHFT                                                      0x0

#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_ADDR(base,n)                                                   ((base) + 0x00000384 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_PHYS(base,n)                                                   ((base) + 0x00000384 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_OFFS(base,n)                                                   (0x00000384 + 0x4 * (n))
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_RMSK                                                           0xffffffff
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_MAXn                                                                   15
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_HDR_12_15_n_ADDR(base,n), HWIO_PCIE30_PARF_MSG_HDR_12_15_n_RMSK)
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_PARF_MSG_HDR_12_15_n_ADDR(base,n), mask)
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_OUTI(base,n,val)    \
        out_dword(HWIO_PCIE30_PARF_MSG_HDR_12_15_n_ADDR(base,n),val)
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSG_HDR_12_15_n_ADDR(base,n),mask,val,HWIO_PCIE30_PARF_MSG_HDR_12_15_n_INI(base,n))
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_MSG_HDR_12_15_BMSK                                             0xffffffff
#define HWIO_PCIE30_PARF_MSG_HDR_12_15_n_MSG_HDR_12_15_SHFT                                                    0x0

#define HWIO_PCIE30_PARF_OBFF_MSG_ADDR(x)                                                               ((x) + 0x000003c4)
#define HWIO_PCIE30_PARF_OBFF_MSG_PHYS(x)                                                               ((x) + 0x000003c4)
#define HWIO_PCIE30_PARF_OBFF_MSG_OFFS                                                                  (0x000003c4)
#define HWIO_PCIE30_PARF_OBFF_MSG_RMSK                                                                         0x7
#define HWIO_PCIE30_PARF_OBFF_MSG_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_OBFF_MSG_ADDR(x),v)
#define HWIO_PCIE30_PARF_OBFF_MSG_OBFF_CPU_ACTIVE_MSG_REQ_BMSK                                                 0x4
#define HWIO_PCIE30_PARF_OBFF_MSG_OBFF_CPU_ACTIVE_MSG_REQ_SHFT                                                 0x2
#define HWIO_PCIE30_PARF_OBFF_MSG_OBFF_IDLE_MSG_REQ_BMSK                                                       0x2
#define HWIO_PCIE30_PARF_OBFF_MSG_OBFF_IDLE_MSG_REQ_SHFT                                                       0x1
#define HWIO_PCIE30_PARF_OBFF_MSG_OBFF_OBFF_MSG_REQ_BMSK                                                       0x1
#define HWIO_PCIE30_PARF_OBFF_MSG_OBFF_OBFF_MSG_REQ_SHFT                                                       0x0

#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_ADDR(x)                                                 ((x) + 0x000003c8)
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_PHYS(x)                                                 ((x) + 0x000003c8)
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_OFFS                                                    (0x000003c8)
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_RMSK                                                       0x1ffff
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_ADDR(x), HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_RMSK)
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_ADDR(x), m)
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_ADDR(x),v)
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_ADDR(x),m,v,HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_IN(x))
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_BRESP_BMSK                             0x18000
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_BRESP_SHFT                                 0xf
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_BRESP_EN_BMSK                           0x4000
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_BRESP_EN_SHFT                              0xe
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_BRESP_BMSK                         0x3000
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_BRESP_SHFT                            0xc
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_BRESP_EN_BMSK                       0x800
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_BRESP_EN_SHFT                         0xb
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_RDATA_EN_BMSK                            0x400
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_RDATA_EN_SHFT                              0xa
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_RDATA_EN_BMSK                       0x200
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_RDATA_EN_SHFT                         0x9
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_CRS_VALUE_BMSK                                               0x1c0
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_CRS_VALUE_SHFT                                                 0x6
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_RRESP_BMSK                                0x30
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_RRESP_SHFT                                 0x4
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_RRESP_EN_BMSK                              0x8
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_RRESP_EN_SHFT                              0x3
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_RRESP_BMSK                            0x6
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_RRESP_SHFT                            0x1
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_RRESP_EN_BMSK                         0x1
#define HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_RRESP_EN_SHFT                         0x0

#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_ADDR(x)                                                  ((x) + 0x000003cc)
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_PHYS(x)                                                  ((x) + 0x000003cc)
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_OFFS                                                     (0x000003cc)
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_RMSK                                                            0x1
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_ADDR(x), HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_RMSK)
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_ADDR(x), m)
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_ADDR(x),v)
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_ADDR(x),m,v,HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_IN(x))
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_REQ_NOT_ENTR_L1_BMSK                                            0x1
#define HWIO_PCIE30_PARF_MSTR1_REQ_NOT_ENTR_L1_REQ_NOT_ENTR_L1_SHFT                                            0x0

#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_ADDR(x)                                             ((x) + 0x000003e0)
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_PHYS(x)                                             ((x) + 0x000003e0)
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_OFFS                                                (0x000003e0)
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_RMSK                                                0x3fffffff
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_ADDR(x), HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_RMSK)
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_IN(x))
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_ATU_BYPASS_BMSK                                     0x20000000
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_ATU_BYPASS_SHFT                                           0x1d
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_PASID_EXE_BMSK                                      0x10000000
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_PASID_EXE_SHFT                                            0x1c
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_PASID_PRIV_BMSK                                      0x8000000
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_PASID_PRIV_SHFT                                           0x1b
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_PASID_FMT_TYPE_BMSK                                  0x7f80000
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_PASID_FMT_TYPE_SHFT                                       0x13
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_MSG_CODE_BMSK                                          0x7f800
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_MSG_CODE_SHFT                                              0xb
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_TC_BMSK                                                  0x700
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_TC_SHFT                                                    0x8
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_RO_BMSK                                                   0x80
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_RO_SHFT                                                    0x7
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_NS_BMSK                                                   0x40
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_NS_SHFT                                                    0x6
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_EP_BMSK                                                   0x20
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_EP_SHFT                                                    0x5
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_TLP_TYPE_BMSK                                             0x1f
#define HWIO_PCIE30_PARF_ATS_INV_REQ_AXI_ATTRIBUTES_TLP_TYPE_SHFT                                              0x0

#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ADDR(x)                                             ((x) + 0x000003e4)
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_PHYS(x)                                             ((x) + 0x000003e4)
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_OFFS                                                (0x000003e4)
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_RMSK                                                0xffffffff
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ADDR(x), HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_RMSK)
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_IN(x))
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_EARLYWRRESP_BMSK                                    0x80000000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_EARLYWRRESP_SHFT                                          0x1f
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_OOORD_BMSK                                          0x40000000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_OOORD_SHFT                                                0x1e
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_BAR_BMSK                                            0x30000000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_BAR_SHFT                                                  0x1c
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_QAD_BMSK                                             0x8000000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_QAD_SHFT                                                  0x1b
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ORDEREDRD_BMSK                                       0x4000000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ORDEREDRD_SHFT                                            0x1a
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ORDEREDWR_BMSK                                       0x2000000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_ORDEREDWR_SHFT                                            0x19
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_IDO_BMSK                                             0x1000000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_IDO_SHFT                                                  0x18
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERTRANSIENT_BMSK                                   0x800000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERTRANSIENT_SHFT                                       0x17
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERNOALLOCATE_BMSK                                  0x400000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERNOALLOCATE_SHFT                                      0x16
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_DEVICETYPE_BMSK                                       0x300000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_DEVICETYPE_SHFT                                           0x14
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERCACHEABLE_BMSK                                    0x80000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERCACHEABLE_SHFT                                       0x13
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_CACHEABLE_BMSK                                         0x40000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_CACHEABLE_SHFT                                            0x12
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_PRIORITYLVL_BMSK                                       0x30000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_PRIORITYLVL_SHFT                                          0x10
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_EXCLUSIVE_BMSK                                          0x8000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_EXCLUSIVE_SHFT                                             0xf
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_PRIV_BMSK                                               0x4000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_PRIV_SHFT                                                  0xe
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INST_BMSK                                               0x2000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INST_SHFT                                                  0xd
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERWRITETHROUGH_BMSK                                  0x1000
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERWRITETHROUGH_SHFT                                     0xc
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_WRITETHROUGH_BMSK                                        0x800
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_WRITETHROUGH_SHFT                                          0xb
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERSHARED_BMSK                                         0x400
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_INNERSHARED_SHFT                                           0xa
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_SHARED_BMSK                                              0x200
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_SHARED_SHFT                                                0x9
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_TRANSIENT_BMSK                                           0x100
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_TRANSIENT_SHFT                                             0x8
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_PROTNS_BMSK                                               0x80
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_PROTNS_SHFT                                                0x7
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_DEVICE_BMSK                                               0x40
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_DEVICE_SHFT                                                0x6
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_NOALLOCATE_BMSK                                           0x20
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_NOALLOCATE_SHFT                                            0x5
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_REQPRIORITY_BMSK                                          0x18
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_REQPRIORITY_SHFT                                           0x3
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_MMUXLATEALLOCPOLICY_BMSK                                   0x6
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_MMUXLATEALLOCPOLICY_SHFT                                   0x1
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_NOSNOOP_BMSK                                               0x1
#define HWIO_PCIE30_PARF_ATS_BARRIER_QSB_ATTRIBUTES_NOSNOOP_SHFT                                               0x0

#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ADDR(x)                                                    ((x) + 0x000003e8)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_PHYS(x)                                                    ((x) + 0x000003e8)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_OFFS                                                       (0x000003e8)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_RMSK                                                       0xe0ffffff
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ADDR(x), HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_RMSK)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_IN(x))
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ENABLE_BMSK                                                0x80000000
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ENABLE_SHFT                                                      0x1f
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ATS_INV_FLUSH_CLEAR_BMSK                                   0x40000000
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ATS_INV_FLUSH_CLEAR_SHFT                                         0x1e
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ATS_INV_FLUSH_ENABLE_BMSK                                  0x20000000
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ATS_INV_FLUSH_ENABLE_SHFT                                        0x1d
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ONE_MSEC_VALUE_BMSK                                          0xffffff
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ONE_MSEC_VALUE_SHFT                                               0x0

#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_ADDR(x)                                                    ((x) + 0x000003f0)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_PHYS(x)                                                    ((x) + 0x000003f0)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_OFFS                                                       (0x000003f0)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_RMSK                                                          0x3ffff
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_ADDR(x), HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_RMSK)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_IN(x))
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_NINETY_SEC_VALUE_BMSK                                         0x3ffff
#define HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_QSB_NINETY_SEC_VALUE_SHFT                                             0x0

#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_ADDR(x)                                                    ((x) + 0x000003f4)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_PHYS(x)                                                    ((x) + 0x000003f4)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_OFFS                                                       (0x000003f4)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_RMSK                                                             0x1f
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_ADDR(x), HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_RMSK)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_IN(x))
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_WR_PASS_ATS_INV_COMP_EN_BMSK                                     0x10
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_WR_PASS_ATS_INV_COMP_EN_SHFT                                      0x4
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_ATS_INV_COMP_PASS_WR_EN_BMSK                                      0x8
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_ATS_INV_COMP_PASS_WR_EN_SHFT                                      0x3
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_IGNORE_BARRIER_RESP_BMSK                                          0x4
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_IGNORE_BARRIER_RESP_SHFT                                          0x2
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_LINK_DOWN_AUTO_COMPLETE_EN_BMSK                                   0x2
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_LINK_DOWN_AUTO_COMPLETE_EN_SHFT                                   0x1
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_TIMEOUT_AUTO_COMPLETE_EN_BMSK                                     0x1
#define HWIO_PCIE30_PARF_ATS_INV_COMP_CONFIG_TIMEOUT_AUTO_COMPLETE_EN_SHFT                                     0x0

#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_WR_DATA_ADDR(x)                                             ((x) + 0x000003f8)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_WR_DATA_PHYS(x)                                             ((x) + 0x000003f8)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_WR_DATA_OFFS                                                (0x000003f8)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_WR_DATA_RMSK                                                0xffffffff
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_WR_DATA_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_WR_DATA_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_WR_DATA_ATS_INV_TABLE_WR_DATA_BMSK                          0xffffffff
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_WR_DATA_ATS_INV_TABLE_WR_DATA_SHFT                                 0x0

#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_ADDR(x)                                             ((x) + 0x00000400)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_PHYS(x)                                             ((x) + 0x00000400)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_OFFS                                                (0x00000400)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_RMSK                                                0xffffffff
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_ADDR(x), HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_RMSK)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_ATS_INV_TABLE_RD_DATA_BMSK                          0xffffffff
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_RD_DATA_ATS_INV_TABLE_RD_DATA_SHFT                                 0x0

#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_ADDR(x)                                                ((x) + 0x00000404)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_PHYS(x)                                                ((x) + 0x00000404)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_OFFS                                                   (0x00000404)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_RMSK                                                       0xff03
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_ADDR(x), HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_RMSK)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_IN(x))
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_ITAG_SEL_BMSK                                              0xf800
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_ITAG_SEL_SHFT                                                 0xb
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_WORD_SEL_BMSK                                               0x700
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_WORD_SEL_SHFT                                                 0x8
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_READ_WRITE_N_BMSK                                             0x2
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_READ_WRITE_N_SHFT                                             0x1
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_VALID_BMSK                                                    0x1
#define HWIO_PCIE30_PARF_ATS_INV_COMP_TABLE_CTRL_VALID_SHFT                                                    0x0

#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ADDR(x)                                                         ((x) + 0x00000408)
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_PHYS(x)                                                         ((x) + 0x00000408)
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_OFFS                                                            (0x00000408)
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_RMSK                                                                  0x1f
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INT_STATUS_ADDR(x), HWIO_PCIE30_PARF_ATS_INT_STATUS_RMSK)
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INT_STATUS_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_COMPLETED_ITAG_ERR_BMSK                                           0x10
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_COMPLETED_ITAG_ERR_SHFT                                            0x4
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_TIMEOUT_ITAG_ERR_BMSK                                              0x8
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_TIMEOUT_ITAG_ERR_SHFT                                              0x3
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_CC_MISMATCH_ERR_BMSK                                               0x4
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_CC_MISMATCH_ERR_SHFT                                               0x2
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_INVALID_ITAG_ERR_BMSK                                              0x2
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_INVALID_ITAG_ERR_SHFT                                              0x1
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_TIMEOUT_ERR_BMSK                                                   0x1
#define HWIO_PCIE30_PARF_ATS_INT_STATUS_ATS_TIMEOUT_ERR_SHFT                                                   0x0

#define HWIO_PCIE30_PARF_ATS_INT_MASK_ADDR(x)                                                           ((x) + 0x0000040c)
#define HWIO_PCIE30_PARF_ATS_INT_MASK_PHYS(x)                                                           ((x) + 0x0000040c)
#define HWIO_PCIE30_PARF_ATS_INT_MASK_OFFS                                                              (0x0000040c)
#define HWIO_PCIE30_PARF_ATS_INT_MASK_RMSK                                                                    0x1f
#define HWIO_PCIE30_PARF_ATS_INT_MASK_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INT_MASK_ADDR(x), HWIO_PCIE30_PARF_ATS_INT_MASK_RMSK)
#define HWIO_PCIE30_PARF_ATS_INT_MASK_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_INT_MASK_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_INT_MASK_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_INT_MASK_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_INT_MASK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_INT_MASK_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_INT_MASK_IN(x))
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_COMPLETED_ITAG_ERR_BMSK                                             0x10
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_COMPLETED_ITAG_ERR_SHFT                                              0x4
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_TIMEOUT_ITAG_ERR_BMSK                                                0x8
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_TIMEOUT_ITAG_ERR_SHFT                                                0x3
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_CC_MISMATCH_ERR_BMSK                                                 0x4
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_CC_MISMATCH_ERR_SHFT                                                 0x2
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_INVALID_ITAG_ERR_BMSK                                                0x2
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_INVALID_ITAG_ERR_SHFT                                                0x1
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_TIMEOUT_ERR_BMSK                                                     0x1
#define HWIO_PCIE30_PARF_ATS_INT_MASK_ATS_TIMEOUT_ERR_SHFT                                                     0x0

#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ADDR(x)                                                          ((x) + 0x00000410)
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_PHYS(x)                                                          ((x) + 0x00000410)
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_OFFS                                                             (0x00000410)
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_RMSK                                                                   0x1f
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_INT_CLEAR_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_COMPLETED_ITAG_ERR_BMSK                                            0x10
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_COMPLETED_ITAG_ERR_SHFT                                             0x4
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_TIMEOUT_ITAG_ERR_BMSK                                               0x8
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_TIMEOUT_ITAG_ERR_SHFT                                               0x3
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_CC_MISMATCH_ERR_BMSK                                                0x4
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_CC_MISMATCH_ERR_SHFT                                                0x2
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_INVALID_ITAG_ERR_BMSK                                               0x2
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_INVALID_ITAG_ERR_SHFT                                               0x1
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_TIMEOUT_ERR_BMSK                                                    0x1
#define HWIO_PCIE30_PARF_ATS_INT_CLEAR_ATS_TIMEOUT_ERR_SHFT                                                    0x0

#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ADDR(x)                                                 ((x) + 0x00000414)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_PHYS(x)                                                 ((x) + 0x00000414)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_OFFS                                                    (0x00000414)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_RMSK                                                     0x7ffffff
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ADDR(x), HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_RMSK)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ATS_ERR_ACT_CC_BMSK                                      0x7000000
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ATS_ERR_ACT_CC_SHFT                                           0x18
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ATS_ERR_EXP_CC_BMSK                                       0xe00000
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ATS_ERR_EXP_CC_SHFT                                           0x15
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ATS_ERR_ITAG_BMSK                                         0x1f0000
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ATS_ERR_ITAG_SHFT                                             0x10
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ATS_ERR_SID_BMSK                                            0xffff
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_0_ATS_ERR_SID_SHFT                                               0x0

#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ADDR(x)                                                 ((x) + 0x00000418)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_PHYS(x)                                                 ((x) + 0x00000418)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_OFFS                                                    (0x00000418)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_RMSK                                                    0xfffff0ff
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ADDR(x), HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_RMSK)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ATS_ERR_SSID_BMSK                                       0xfffff000
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ATS_ERR_SSID_SHFT                                              0xc
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ATS_ERR_SIZE_BMSK                                             0xfc
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ATS_ERR_SIZE_SHFT                                              0x2
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ATS_ERR_G_BMSK                                                 0x2
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ATS_ERR_G_SHFT                                                 0x1
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ATS_ERR_SSV_BMSK                                               0x1
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_1_ATS_ERR_SSV_SHFT                                               0x0

#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_ADDR(x)                                                 ((x) + 0x0000041c)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_PHYS(x)                                                 ((x) + 0x0000041c)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_OFFS                                                    (0x0000041c)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_RMSK                                                    0xfffff000
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_ADDR(x), HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_RMSK)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_ATS_ERR_ADDR_31_12_BMSK                                 0xfffff000
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_2_ATS_ERR_ADDR_31_12_SHFT                                        0xc

#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_ADDR(x)                                                 ((x) + 0x00000420)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_PHYS(x)                                                 ((x) + 0x00000420)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_OFFS                                                    (0x00000420)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_RMSK                                                    0xffffffff
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_ADDR(x), HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_RMSK)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_ATS_ERR_ADDR_63_32_BMSK                                 0xffffffff
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_3_ATS_ERR_ADDR_63_32_SHFT                                        0x0

#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_ADDR(x)                                                 ((x) + 0x00000424)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_PHYS(x)                                                 ((x) + 0x00000424)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_OFFS                                                    (0x00000424)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_RMSK                                                    0xffffffff
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_ADDR(x), HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_RMSK)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_ATS_ERR_ITAG_VECTOR_BMSK                                0xffffffff
#define HWIO_PCIE30_PARF_ATS_FIRST_ERROR_INFO_4_ATS_ERR_ITAG_VECTOR_SHFT                                       0x0

#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ADDR(x)                                                      ((x) + 0x00000428)
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_PHYS(x)                                                      ((x) + 0x00000428)
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_OFFS                                                         (0x00000428)
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_RMSK                                                             0x7fff
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ADDR(x), HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_RMSK)
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_IN(x))
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_REQ_HANDLE_UNALIGNED_ADDR_ERR_EN_BMSK                        0x4000
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_REQ_HANDLE_UNALIGNED_ADDR_ERR_EN_SHFT                           0xe
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_REQ_HANDLE_SIZE_ERR_EN_BMSK                                  0x2000
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_REQ_HANDLE_SIZE_ERR_EN_SHFT                                     0xd
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_REQ_HANDLE_LEN_ERR_EN_BMSK                                   0x1000
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_REQ_HANDLE_LEN_ERR_EN_SHFT                                      0xc
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_LEN_ERR_RESP_MISC_INFO_BMSK                                   0xc00
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_LEN_ERR_RESP_MISC_INFO_SHFT                                     0xa
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_LEN_ERR_RESP_MSTR_BMSK                                        0x300
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_LEN_ERR_RESP_MSTR_SHFT                                          0x8
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_QSMMU_RESP_MISC_INFO_UR_BMSK                                   0xc0
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_QSMMU_RESP_MISC_INFO_UR_SHFT                                    0x6
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_QSMMU_RESP_MISC_INFO_CA_BMSK                                   0x30
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_QSMMU_RESP_MISC_INFO_CA_SHFT                                    0x4
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_QSMMU_RESP_MISC_INFO_SUCCESS_BMSK                               0xc
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_QSMMU_RESP_MISC_INFO_SUCCESS_SHFT                               0x2
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_QSMMU_RESP_MSTR_BMSK                                            0x3
#define HWIO_PCIE30_PARF_ATS_MAP_RESP_MSTR_ATS_QSMMU_RESP_MSTR_SHFT                                            0x0

#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ADDR(x)                                                   ((x) + 0x0000042c)
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_PHYS(x)                                                   ((x) + 0x0000042c)
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_OFFS                                                      (0x0000042c)
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_RMSK                                                             0xf
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ADDR(x), HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_RMSK)
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_IN(x))
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ATS_PRIORITY_LA_BMSK                                             0x8
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ATS_PRIORITY_LA_SHFT                                             0x3
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ATS_PRIORITY_REQ_BMSK                                            0x4
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ATS_PRIORITY_REQ_SHFT                                            0x2
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ATS_PRIORITY_LEN_ERR_RESP_BMSK                                   0x2
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ATS_PRIORITY_LEN_ERR_RESP_SHFT                                   0x1
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ATS_PRIORITY_QSMMU_RESP_BMSK                                     0x1
#define HWIO_PCIE30_PARF_ATS_ARBITER_PRIORITY_ATS_PRIORITY_QSMMU_RESP_SHFT                                     0x0

#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ADDR(x)                                                          ((x) + 0x00000430)
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_PHYS(x)                                                          ((x) + 0x00000430)
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_OFFS                                                             (0x00000430)
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_RMSK                                                             0xd37f737f
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ADDR(x), HWIO_PCIE30_PARF_ATS_ATTRIBUTE_RMSK)
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ADDR(x), m)
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ADDR(x),v)
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ADDR(x),m,v,HWIO_PCIE30_PARF_ATS_ATTRIBUTE_IN(x))
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_VALID_BMSK                                           0x80000000
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_VALID_SHFT                                                 0x1f
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_VALID_BMSK                                          0x40000000
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_VALID_SHFT                                                0x1e
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_SEC_BMSK                                             0x10000000
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_SEC_SHFT                                                   0x1c
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_SH_BMSK                                               0x3000000
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_SH_SHFT                                                    0x18
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_ALLOC_BMSK                                             0x700000
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_ALLOC_SHFT                                                 0x14
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_MEMTYPE_BMSK                                            0xf0000
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_ATTR_MEMTYPE_SHFT                                               0x10
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_TTYPE_BMSK                                                    0x6000
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_LA_TTYPE_SHFT                                                       0xd
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_SEC_BMSK                                                0x1000
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_SEC_SHFT                                                   0xc
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_SH_BMSK                                                  0x300
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_SH_SHFT                                                    0x8
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_ALLOC_BMSK                                                0x70
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_ALLOC_SHFT                                                 0x4
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_MEMTYPE_BMSK                                               0xf
#define HWIO_PCIE30_PARF_ATS_ATTRIBUTE_ATS_REQ_ATTR_MEMTYPE_SHFT                                               0x0

#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_ADDR(x)                                                    ((x) + 0x00000440)
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_PHYS(x)                                                    ((x) + 0x00000440)
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_OFFS                                                       (0x00000440)
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_RMSK                                                       0xffffffff
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_ADDR(x), HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_RMSK)
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_ADDR(x), m)
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_ADDR(x),v)
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_ADDR(x),m,v,HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_IN(x))
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_PROG_MISC_INFO5_BMSK                                       0xffffffff
#define HWIO_PCIE30_PARF_Q2A_PROG_MISC_INFO5_PROG_MISC_INFO5_SHFT                                              0x0

#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_ADDR(x)                                                         ((x) + 0x00000444)
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_PHYS(x)                                                         ((x) + 0x00000444)
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_OFFS                                                            (0x00000444)
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_RMSK                                                            0xffffffff
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_Q2A_PROG_ORDER_ADDR(x), HWIO_PCIE30_PARF_Q2A_PROG_ORDER_RMSK)
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_Q2A_PROG_ORDER_ADDR(x), m)
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_Q2A_PROG_ORDER_ADDR(x),v)
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_Q2A_PROG_ORDER_ADDR(x),m,v,HWIO_PCIE30_PARF_Q2A_PROG_ORDER_IN(x))
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_PROG_ORDER_BMSK                                                 0xffffffff
#define HWIO_PCIE30_PARF_Q2A_PROG_ORDER_PROG_ORDER_SHFT                                                        0x0

#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_ADDR(x)                                              ((x) + 0x00000450)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_PHYS(x)                                              ((x) + 0x00000450)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_OFFS                                                 (0x00000450)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_RMSK                                                 0xffffffff
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_ADDR(x), HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_RMSK)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_ADDR(x), m)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_ECAM_BLOCKED_TRANS0_BMSK                             0xffffffff
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS0_STATUS_ECAM_BLOCKED_TRANS0_SHFT                                    0x0

#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_ADDR(x)                                              ((x) + 0x00000454)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_PHYS(x)                                              ((x) + 0x00000454)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_OFFS                                                 (0x00000454)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_RMSK                                                 0xffffffff
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_ADDR(x), HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_RMSK)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_ADDR(x), m)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_ECAM_BLOCKED_TRANS1_BMSK                             0xffffffff
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS1_STATUS_ECAM_BLOCKED_TRANS1_SHFT                                    0x0

#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_ADDR(x)                                              ((x) + 0x00000458)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_PHYS(x)                                              ((x) + 0x00000458)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_OFFS                                                 (0x00000458)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_RMSK                                                   0x7fffff
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_ADDR(x), HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_RMSK)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_ADDR(x), m)
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_ECAM_BLOCKED_TRANS2_BMSK                               0x7fffff
#define HWIO_PCIE30_Q2A_ECAM_BLOCKED_TRANS2_STATUS_ECAM_BLOCKED_TRANS2_SHFT                                    0x0

#define HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_ADDR(x)                                                      ((x) + 0x00000460)
#define HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_PHYS(x)                                                      ((x) + 0x00000460)
#define HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_OFFS                                                         (0x00000460)
#define HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_RMSK                                                             0xffff
#define HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_ADDR(x), HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_RMSK)
#define HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_ADDR(x), m)
#define HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_ID2ID_ERROR_BMSK                                                 0xffff
#define HWIO_PCIE30_Q2A_ID2ID_ERROR_STATUS_ID2ID_ERROR_SHFT                                                    0x0

#define HWIO_PCIE30_A2Q_PROG_ORDER_ADDR(x)                                                              ((x) + 0x00000470)
#define HWIO_PCIE30_A2Q_PROG_ORDER_PHYS(x)                                                              ((x) + 0x00000470)
#define HWIO_PCIE30_A2Q_PROG_ORDER_OFFS                                                                 (0x00000470)
#define HWIO_PCIE30_A2Q_PROG_ORDER_RMSK                                                                 0xffffffff
#define HWIO_PCIE30_A2Q_PROG_ORDER_IN(x)      \
        in_dword_masked(HWIO_PCIE30_A2Q_PROG_ORDER_ADDR(x), HWIO_PCIE30_A2Q_PROG_ORDER_RMSK)
#define HWIO_PCIE30_A2Q_PROG_ORDER_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_A2Q_PROG_ORDER_ADDR(x), m)
#define HWIO_PCIE30_A2Q_PROG_ORDER_OUT(x, v)      \
        out_dword(HWIO_PCIE30_A2Q_PROG_ORDER_ADDR(x),v)
#define HWIO_PCIE30_A2Q_PROG_ORDER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_A2Q_PROG_ORDER_ADDR(x),m,v,HWIO_PCIE30_A2Q_PROG_ORDER_IN(x))
#define HWIO_PCIE30_A2Q_PROG_ORDER_A2Q_AOOOWR_BMSK                                                      0xff000000
#define HWIO_PCIE30_A2Q_PROG_ORDER_A2Q_AOOOWR_SHFT                                                            0x18
#define HWIO_PCIE30_A2Q_PROG_ORDER_A2Q_AOOORD_BMSK                                                        0xff0000
#define HWIO_PCIE30_A2Q_PROG_ORDER_A2Q_AOOORD_SHFT                                                            0x10
#define HWIO_PCIE30_A2Q_PROG_ORDER_A2Q_AORDEREDWR_BMSK                                                      0xff00
#define HWIO_PCIE30_A2Q_PROG_ORDER_A2Q_AORDEREDWR_SHFT                                                         0x8
#define HWIO_PCIE30_A2Q_PROG_ORDER_A2Q_AORDEREDRD_BMSK                                                        0xff
#define HWIO_PCIE30_A2Q_PROG_ORDER_A2Q_AORDEREDRD_SHFT                                                         0x0

#define HWIO_PCIE30_A2Q_PROG_AIDO_ADDR(x)                                                               ((x) + 0x00000474)
#define HWIO_PCIE30_A2Q_PROG_AIDO_PHYS(x)                                                               ((x) + 0x00000474)
#define HWIO_PCIE30_A2Q_PROG_AIDO_OFFS                                                                  (0x00000474)
#define HWIO_PCIE30_A2Q_PROG_AIDO_RMSK                                                                        0xff
#define HWIO_PCIE30_A2Q_PROG_AIDO_IN(x)      \
        in_dword_masked(HWIO_PCIE30_A2Q_PROG_AIDO_ADDR(x), HWIO_PCIE30_A2Q_PROG_AIDO_RMSK)
#define HWIO_PCIE30_A2Q_PROG_AIDO_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_A2Q_PROG_AIDO_ADDR(x), m)
#define HWIO_PCIE30_A2Q_PROG_AIDO_OUT(x, v)      \
        out_dword(HWIO_PCIE30_A2Q_PROG_AIDO_ADDR(x),v)
#define HWIO_PCIE30_A2Q_PROG_AIDO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_A2Q_PROG_AIDO_ADDR(x),m,v,HWIO_PCIE30_A2Q_PROG_AIDO_IN(x))
#define HWIO_PCIE30_A2Q_PROG_AIDO_A2Q_AIDO_BMSK                                                               0xff
#define HWIO_PCIE30_A2Q_PROG_AIDO_A2Q_AIDO_SHFT                                                                0x0

#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_ADDR(x)                                                           ((x) + 0x00000478)
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_PHYS(x)                                                           ((x) + 0x00000478)
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_OFFS                                                              (0x00000478)
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_RMSK                                                              0xffffffff
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_IN(x)      \
        in_dword_masked(HWIO_PCIE30_A2Q_RESP_CPL_STAT_ADDR(x), HWIO_PCIE30_A2Q_RESP_CPL_STAT_RMSK)
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_A2Q_RESP_CPL_STAT_ADDR(x), m)
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_OUT(x, v)      \
        out_dword(HWIO_PCIE30_A2Q_RESP_CPL_STAT_ADDR(x),v)
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_A2Q_RESP_CPL_STAT_ADDR(x),m,v,HWIO_PCIE30_A2Q_RESP_CPL_STAT_IN(x))
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_A2Q_RRESP_TRANSLATION_BMSK                                        0xff000000
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_A2Q_RRESP_TRANSLATION_SHFT                                              0x18
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_A2Q_RMISC_INFO_CPL_STAT_BMSK                                        0xff0000
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_A2Q_RMISC_INFO_CPL_STAT_SHFT                                            0x10
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_A2Q_BMISC_INFO_CPL_STAT_BMSK                                          0xff00
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_A2Q_BMISC_INFO_CPL_STAT_SHFT                                             0x8
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_A2Q_BRESP_TRANSLATION_BMSK                                              0xff
#define HWIO_PCIE30_A2Q_RESP_CPL_STAT_A2Q_BRESP_TRANSLATION_SHFT                                               0x0

#define HWIO_PCIE30_PARF_LINK_INT_STATUS_ADDR(x)                                                        ((x) + 0x000004a0)
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_PHYS(x)                                                        ((x) + 0x000004a0)
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_OFFS                                                           (0x000004a0)
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_RMSK                                                                0x3ff
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_LINK_INT_STATUS_ADDR(x), HWIO_PCIE30_PARF_LINK_INT_STATUS_RMSK)
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_LINK_INT_STATUS_ADDR(x), m)
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_CAP_LINK_DIS_SET_LINK_DOWN_BMSK                                     0x200
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_CAP_LINK_DIS_SET_LINK_DOWN_SHFT                                       0x9
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_CAP_LINK_DIS_CLEAR_LINK_DOWN_BMSK                                   0x100
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_CAP_LINK_DIS_CLEAR_LINK_DOWN_SHFT                                     0x8
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_SBR_SET_LINK_DOWN_BMSK                                               0x80
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_SBR_SET_LINK_DOWN_SHFT                                                0x7
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_SBR_CLEAR_LINK_DOWN_BMSK                                             0x40
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_SBR_CLEAR_LINK_DOWN_SHFT                                              0x6
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_CAP_LINK_DIS_SET_LINK_UP_BMSK                                        0x20
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_CAP_LINK_DIS_SET_LINK_UP_SHFT                                         0x5
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_CAP_LINK_DIS_CLEAR_LINK_UP_BMSK                                      0x10
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_CAP_LINK_DIS_CLEAR_LINK_UP_SHFT                                       0x4
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_SBR_SET_LINK_UP_BMSK                                                  0x8
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_SBR_SET_LINK_UP_SHFT                                                  0x3
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_SBR_CLEAR_LINK_UP_BMSK                                                0x4
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_SBR_CLEAR_LINK_UP_SHFT                                                0x2
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_LINK_DOWN_BMSK                                                        0x2
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_LINK_DOWN_SHFT                                                        0x1
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_LINK_UP_BMSK                                                          0x1
#define HWIO_PCIE30_PARF_LINK_INT_STATUS_LINK_UP_SHFT                                                          0x0

#define HWIO_PCIE30_PARF_LINK_INT_MASK_ADDR(x)                                                          ((x) + 0x000004a4)
#define HWIO_PCIE30_PARF_LINK_INT_MASK_PHYS(x)                                                          ((x) + 0x000004a4)
#define HWIO_PCIE30_PARF_LINK_INT_MASK_OFFS                                                             (0x000004a4)
#define HWIO_PCIE30_PARF_LINK_INT_MASK_RMSK                                                                  0x3ff
#define HWIO_PCIE30_PARF_LINK_INT_MASK_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_LINK_INT_MASK_ADDR(x), HWIO_PCIE30_PARF_LINK_INT_MASK_RMSK)
#define HWIO_PCIE30_PARF_LINK_INT_MASK_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_LINK_INT_MASK_ADDR(x), m)
#define HWIO_PCIE30_PARF_LINK_INT_MASK_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_LINK_INT_MASK_ADDR(x),v)
#define HWIO_PCIE30_PARF_LINK_INT_MASK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_LINK_INT_MASK_ADDR(x),m,v,HWIO_PCIE30_PARF_LINK_INT_MASK_IN(x))
#define HWIO_PCIE30_PARF_LINK_INT_MASK_CAP_LINK_DIS_SET_LINK_DOWN_BMSK                                       0x200
#define HWIO_PCIE30_PARF_LINK_INT_MASK_CAP_LINK_DIS_SET_LINK_DOWN_SHFT                                         0x9
#define HWIO_PCIE30_PARF_LINK_INT_MASK_CAP_LINK_DIS_CLEAR_LINK_DOWN_BMSK                                     0x100
#define HWIO_PCIE30_PARF_LINK_INT_MASK_CAP_LINK_DIS_CLEAR_LINK_DOWN_SHFT                                       0x8
#define HWIO_PCIE30_PARF_LINK_INT_MASK_SBR_SET_LINK_DOWN_BMSK                                                 0x80
#define HWIO_PCIE30_PARF_LINK_INT_MASK_SBR_SET_LINK_DOWN_SHFT                                                  0x7
#define HWIO_PCIE30_PARF_LINK_INT_MASK_SBR_CLEAR_LINK_DOWN_BMSK                                               0x40
#define HWIO_PCIE30_PARF_LINK_INT_MASK_SBR_CLEAR_LINK_DOWN_SHFT                                                0x6
#define HWIO_PCIE30_PARF_LINK_INT_MASK_CAP_LINK_DIS_SET_LINK_UP_BMSK                                          0x20
#define HWIO_PCIE30_PARF_LINK_INT_MASK_CAP_LINK_DIS_SET_LINK_UP_SHFT                                           0x5
#define HWIO_PCIE30_PARF_LINK_INT_MASK_CAP_LINK_DIS_CLEAR_LINK_UP_BMSK                                        0x10
#define HWIO_PCIE30_PARF_LINK_INT_MASK_CAP_LINK_DIS_CLEAR_LINK_UP_SHFT                                         0x4
#define HWIO_PCIE30_PARF_LINK_INT_MASK_SBR_SET_LINK_UP_BMSK                                                    0x8
#define HWIO_PCIE30_PARF_LINK_INT_MASK_SBR_SET_LINK_UP_SHFT                                                    0x3
#define HWIO_PCIE30_PARF_LINK_INT_MASK_SBR_CLEAR_LINK_UP_BMSK                                                  0x4
#define HWIO_PCIE30_PARF_LINK_INT_MASK_SBR_CLEAR_LINK_UP_SHFT                                                  0x2
#define HWIO_PCIE30_PARF_LINK_INT_MASK_LINK_DOWN_BMSK                                                          0x2
#define HWIO_PCIE30_PARF_LINK_INT_MASK_LINK_DOWN_SHFT                                                          0x1
#define HWIO_PCIE30_PARF_LINK_INT_MASK_LINK_UP_BMSK                                                            0x1
#define HWIO_PCIE30_PARF_LINK_INT_MASK_LINK_UP_SHFT                                                            0x0

#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_ADDR(x)                                                         ((x) + 0x000004a8)
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_PHYS(x)                                                         ((x) + 0x000004a8)
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_OFFS                                                            (0x000004a8)
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_RMSK                                                                 0x3ff
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_LINK_INT_CLEAR_ADDR(x),v)
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_CAP_LINK_DIS_SET_LINK_DOWN_BMSK                                      0x200
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_CAP_LINK_DIS_SET_LINK_DOWN_SHFT                                        0x9
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_CAP_LINK_DIS_CLEAR_LINK_DOWN_BMSK                                    0x100
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_CAP_LINK_DIS_CLEAR_LINK_DOWN_SHFT                                      0x8
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_SBR_SET_LINK_DOWN_BMSK                                                0x80
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_SBR_SET_LINK_DOWN_SHFT                                                 0x7
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_SBR_CLEAR_LINK_DOWN_BMSK                                              0x40
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_SBR_CLEAR_LINK_DOWN_SHFT                                               0x6
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_CAP_LINK_DIS_SET_LINK_UP_BMSK                                         0x20
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_CAP_LINK_DIS_SET_LINK_UP_SHFT                                          0x5
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_CAP_LINK_DIS_CLEAR_LINK_UP_BMSK                                       0x10
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_CAP_LINK_DIS_CLEAR_LINK_UP_SHFT                                        0x4
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_SBR_SET_LINK_UP_BMSK                                                   0x8
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_SBR_SET_LINK_UP_SHFT                                                   0x3
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_SBR_CLEAR_LINK_UP_BMSK                                                 0x4
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_SBR_CLEAR_LINK_UP_SHFT                                                 0x2
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_LINK_DOWN_BMSK                                                         0x2
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_LINK_DOWN_SHFT                                                         0x1
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_LINK_UP_BMSK                                                           0x1
#define HWIO_PCIE30_PARF_LINK_INT_CLEAR_LINK_UP_SHFT                                                           0x0

#define HWIO_PCIE30_PARF_SLOT_CONTROL_ADDR(x)                                                           ((x) + 0x000004c0)
#define HWIO_PCIE30_PARF_SLOT_CONTROL_PHYS(x)                                                           ((x) + 0x000004c0)
#define HWIO_PCIE30_PARF_SLOT_CONTROL_OFFS                                                              (0x000004c0)
#define HWIO_PCIE30_PARF_SLOT_CONTROL_RMSK                                                                    0x1f
#define HWIO_PCIE30_PARF_SLOT_CONTROL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLOT_CONTROL_ADDR(x), HWIO_PCIE30_PARF_SLOT_CONTROL_RMSK)
#define HWIO_PCIE30_PARF_SLOT_CONTROL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SLOT_CONTROL_ADDR(x), m)
#define HWIO_PCIE30_PARF_SLOT_CONTROL_PWR_CTRL_BMSK                                                           0x10
#define HWIO_PCIE30_PARF_SLOT_CONTROL_PWR_CTRL_SHFT                                                            0x4
#define HWIO_PCIE30_PARF_SLOT_CONTROL_ATTEN_IND_BMSK                                                           0xc
#define HWIO_PCIE30_PARF_SLOT_CONTROL_ATTEN_IND_SHFT                                                           0x2
#define HWIO_PCIE30_PARF_SLOT_CONTROL_PWR_IND_BMSK                                                             0x3
#define HWIO_PCIE30_PARF_SLOT_CONTROL_PWR_IND_SHFT                                                             0x0

#define HWIO_PCIE30_PARF_DEVICE_TYPE_ADDR(x)                                                            ((x) + 0x00010000)
#define HWIO_PCIE30_PARF_DEVICE_TYPE_PHYS(x)                                                            ((x) + 0x00010000)
#define HWIO_PCIE30_PARF_DEVICE_TYPE_OFFS                                                               (0x00010000)
#define HWIO_PCIE30_PARF_DEVICE_TYPE_RMSK                                                                      0xf
#define HWIO_PCIE30_PARF_DEVICE_TYPE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_DEVICE_TYPE_ADDR(x), HWIO_PCIE30_PARF_DEVICE_TYPE_RMSK)
#define HWIO_PCIE30_PARF_DEVICE_TYPE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_DEVICE_TYPE_ADDR(x), m)
#define HWIO_PCIE30_PARF_DEVICE_TYPE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_DEVICE_TYPE_ADDR(x),v)
#define HWIO_PCIE30_PARF_DEVICE_TYPE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_DEVICE_TYPE_ADDR(x),m,v,HWIO_PCIE30_PARF_DEVICE_TYPE_IN(x))
#define HWIO_PCIE30_PARF_DEVICE_TYPE_DEVICE_TYPE_BMSK                                                          0xf
#define HWIO_PCIE30_PARF_DEVICE_TYPE_DEVICE_TYPE_SHFT                                                          0x0
#define HWIO_PCIE30_PARF_DEVICE_TYPE_DEVICE_TYPE_EP_FVAL                                                       0x0
#define HWIO_PCIE30_PARF_DEVICE_TYPE_DEVICE_TYPE_RC_FVAL                                                       0x4

#define HWIO_PCIE30_PARF_DEBUG_CONFIG_ADDR(x)                                                           ((x) + 0x00010004)
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_PHYS(x)                                                           ((x) + 0x00010004)
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_OFFS                                                              (0x00010004)
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_RMSK                                                                   0xf7d
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_DEBUG_CONFIG_ADDR(x), HWIO_PCIE30_PARF_DEBUG_CONFIG_RMSK)
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_DEBUG_CONFIG_ADDR(x), m)
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_DEBUG_CONFIG_ADDR(x),v)
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_DEBUG_CONFIG_ADDR(x),m,v,HWIO_PCIE30_PARF_DEBUG_CONFIG_IN(x))
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_ARI_RWD_DISABLE_ECAM_EN_BMSK                                           0x800
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_ARI_RWD_DISABLE_ECAM_EN_SHFT                                             0xb
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_QSMMU_FLUSH_INT_DISABLE_BMSK                                           0x400
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_QSMMU_FLUSH_INT_DISABLE_SHFT                                             0xa
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_MSI_HALT_DISABLE_BMSK                                                  0x200
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_MSI_HALT_DISABLE_SHFT                                                    0x9
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_MSI_FLUSH_INT_DISABLE_BMSK                                             0x100
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_MSI_FLUSH_INT_DISABLE_SHFT                                               0x8
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_INTERRUPTS_BYPASS_BMSK                                                  0x40
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_INTERRUPTS_BYPASS_SHFT                                                   0x6
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_HW_EVENTS_BUS_BYPASS_BMSK                                               0x20
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_HW_EVENTS_BUS_BYPASS_SHFT                                                0x5
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_TEST_BUS_BYPASS_BMSK                                                    0x10
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_TEST_BUS_BYPASS_SHFT                                                     0x4
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_RD_BLOCKED_BY_WR_DISABLE_BMSK                                            0x8
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_RD_BLOCKED_BY_WR_DISABLE_SHFT                                            0x3
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_IDO_DISABLE_BMSK                                                         0x4
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_IDO_DISABLE_SHFT                                                         0x2
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_RCAT_LA_DISABLE_BMSK                                                     0x1
#define HWIO_PCIE30_PARF_DEBUG_CONFIG_RCAT_LA_DISABLE_SHFT                                                     0x0

#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_ADDR(x)                                                   ((x) + 0x00010008)
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_PHYS(x)                                                   ((x) + 0x00010008)
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_OFFS                                                      (0x00010008)
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_RMSK                                                          0xffff
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_ADDR(x), HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_RMSK)
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_ADDR(x), m)
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_ADDR(x),v)
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_ADDR(x),m,v,HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_IN(x))
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_RD_LIMIT_BMSK                                                 0xff00
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_RD_LIMIT_SHFT                                                    0x8
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_WR_LIMIT_BMSK                                                   0xff
#define HWIO_PCIE30_PARF_AXI_MSTR_OUTST_LIMIT_WR_LIMIT_SHFT                                                    0x0

#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_ADDR(base,n)                                                  ((base) + 0x00010010 + 0x4 * (n))
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_PHYS(base,n)                                                  ((base) + 0x00010010 + 0x4 * (n))
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_OFFS(base,n)                                                  (0x00010010 + 0x4 * (n))
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_RMSK                                                          0x3effffff
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_MAXn                                                                   9
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_ADDR(base,n), HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_RMSK)
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_ADDR(base,n), mask)
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_OUTI(base,n,val)    \
        out_dword(HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_ADDR(base,n),val)
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_ADDR(base,n),mask,val,HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INI(base,n))
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_BAR_BMSK                                                      0x30000000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_BAR_SHFT                                                            0x1c
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_QAD_BMSK                                                       0x8000000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_QAD_SHFT                                                            0x1b
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_EARLYWRRESP_BMSK                                               0x4000000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_EARLYWRRESP_SHFT                                                    0x1a
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_REDIRECT_BMSK                                                  0x2000000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_REDIRECT_SHFT                                                       0x19
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERTRANSIENT_BMSK                                             0x800000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERTRANSIENT_SHFT                                                 0x17
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERNOALLOCATE_BMSK                                            0x400000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERNOALLOCATE_SHFT                                                0x16
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_DEVICETYPE_BMSK                                                 0x300000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_DEVICETYPE_SHFT                                                     0x14
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERCACHEABLE_BMSK                                              0x80000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERCACHEABLE_SHFT                                                 0x13
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_CACHEABLE_BMSK                                                   0x40000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_CACHEABLE_SHFT                                                      0x12
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_PRIORITYLVL_BMSK                                                 0x30000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_PRIORITYLVL_SHFT                                                    0x10
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_EXCLUSIVE_BMSK                                                    0x8000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_EXCLUSIVE_SHFT                                                       0xf
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_PRIV_BMSK                                                         0x4000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_PRIV_SHFT                                                            0xe
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INST_BMSK                                                         0x2000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INST_SHFT                                                            0xd
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERWRITETHROUGH_BMSK                                            0x1000
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERWRITETHROUGH_SHFT                                               0xc
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_WRITETHROUGH_BMSK                                                  0x800
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_WRITETHROUGH_SHFT                                                    0xb
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERSHARED_BMSK                                                   0x400
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_INNERSHARED_SHFT                                                     0xa
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_SHARED_BMSK                                                        0x200
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_SHARED_SHFT                                                          0x9
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_TRANSIENT_BMSK                                                     0x100
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_TRANSIENT_SHFT                                                       0x8
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_PROTNS_BMSK                                                         0x80
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_PROTNS_SHFT                                                          0x7
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_DEVICE_BMSK                                                         0x40
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_DEVICE_SHFT                                                          0x6
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_NOALLOCATE_BMSK                                                     0x20
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_NOALLOCATE_SHFT                                                      0x5
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_REQPRIORITY_BMSK                                                    0x18
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_REQPRIORITY_SHFT                                                     0x3
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_MMUXLATEALLOCPOLICY_BMSK                                             0x6
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_MMUXLATEALLOCPOLICY_SHFT                                             0x1
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_NOSNOOP_BMSK                                                         0x1
#define HWIO_PCIE30_PARF_QSB_ATTRIBUTES_n_NOSNOOP_SHFT                                                         0x0

#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ADDR(x)                                                     ((x) + 0x00010040)
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_PHYS(x)                                                     ((x) + 0x00010040)
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_OFFS                                                        (0x00010040)
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_RMSK                                                        0xefffffff
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ADDR(x), HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_RMSK)
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ADDR(x), m)
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ADDR(x),v)
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ADDR(x),m,v,HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_IN(x))
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ORDEREDWR_BMSK                                              0x80000000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ORDEREDWR_SHFT                                                    0x1f
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ORDEREDRD_BMSK                                              0x40000000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_ORDEREDRD_SHFT                                                    0x1e
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_OOOWR_BMSK                                                  0x20000000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_OOOWR_SHFT                                                        0x1d
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_QAD_BMSK                                                     0x8000000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_QAD_SHFT                                                          0x1b
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_EARLYWRRESP_BMSK                                             0x4000000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_EARLYWRRESP_SHFT                                                  0x1a
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_REDIRECT_BMSK                                                0x2000000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_REDIRECT_SHFT                                                     0x19
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_IDO_BMSK                                                     0x1000000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_IDO_SHFT                                                          0x18
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERTRANSIENT_BMSK                                           0x800000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERTRANSIENT_SHFT                                               0x17
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERNOALLOCATE_BMSK                                          0x400000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERNOALLOCATE_SHFT                                              0x16
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_DEVICETYPE_BMSK                                               0x300000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_DEVICETYPE_SHFT                                                   0x14
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERCACHEABLE_BMSK                                            0x80000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERCACHEABLE_SHFT                                               0x13
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_CACHEABLE_BMSK                                                 0x40000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_CACHEABLE_SHFT                                                    0x12
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_PRIORITYLVL_BMSK                                               0x30000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_PRIORITYLVL_SHFT                                                  0x10
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_EXCLUSIVE_BMSK                                                  0x8000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_EXCLUSIVE_SHFT                                                     0xf
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_PRIV_BMSK                                                       0x4000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_PRIV_SHFT                                                          0xe
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INST_BMSK                                                       0x2000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INST_SHFT                                                          0xd
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERWRITETHROUGH_BMSK                                          0x1000
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERWRITETHROUGH_SHFT                                             0xc
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_WRITETHROUGH_BMSK                                                0x800
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_WRITETHROUGH_SHFT                                                  0xb
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERSHARED_BMSK                                                 0x400
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_INNERSHARED_SHFT                                                   0xa
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_SHARED_BMSK                                                      0x200
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_SHARED_SHFT                                                        0x9
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_TRANSIENT_BMSK                                                   0x100
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_TRANSIENT_SHFT                                                     0x8
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_PROTNS_BMSK                                                       0x80
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_PROTNS_SHFT                                                        0x7
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_DEVICE_BMSK                                                       0x40
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_DEVICE_SHFT                                                        0x6
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_NOALLOCATE_BMSK                                                   0x20
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_NOALLOCATE_SHFT                                                    0x5
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_REQPRIORITY_BMSK                                                  0x18
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_REQPRIORITY_SHFT                                                   0x3
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_MMUXLATEALLOCPOLICY_BMSK                                           0x6
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_MMUXLATEALLOCPOLICY_SHFT                                           0x1
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_NOSNOOP_BMSK                                                       0x1
#define HWIO_PCIE30_PARF_MSI_QSB_ATTRIBUTES_NOSNOOP_SHFT                                                       0x0

#define HWIO_PCIE30_PARF_FW_INT_STATUS_ADDR(x)                                                          ((x) + 0x00010044)
#define HWIO_PCIE30_PARF_FW_INT_STATUS_PHYS(x)                                                          ((x) + 0x00010044)
#define HWIO_PCIE30_PARF_FW_INT_STATUS_OFFS                                                             (0x00010044)
#define HWIO_PCIE30_PARF_FW_INT_STATUS_RMSK                                                                   0x3f
#define HWIO_PCIE30_PARF_FW_INT_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_FW_INT_STATUS_ADDR(x), HWIO_PCIE30_PARF_FW_INT_STATUS_RMSK)
#define HWIO_PCIE30_PARF_FW_INT_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_FW_INT_STATUS_ADDR(x), m)
#define HWIO_PCIE30_PARF_FW_INT_STATUS_AER_MSI_BMSK                                                           0x20
#define HWIO_PCIE30_PARF_FW_INT_STATUS_AER_MSI_SHFT                                                            0x5
#define HWIO_PCIE30_PARF_FW_INT_STATUS_PME_MSI_BMSK                                                           0x10
#define HWIO_PCIE30_PARF_FW_INT_STATUS_PME_MSI_SHFT                                                            0x4
#define HWIO_PCIE30_PARF_FW_INT_STATUS_HP_MSI_BMSK                                                             0x8
#define HWIO_PCIE30_PARF_FW_INT_STATUS_HP_MSI_SHFT                                                             0x3
#define HWIO_PCIE30_PARF_FW_INT_STATUS_AER_INT_BMSK                                                            0x4
#define HWIO_PCIE30_PARF_FW_INT_STATUS_AER_INT_SHFT                                                            0x2
#define HWIO_PCIE30_PARF_FW_INT_STATUS_PME_INT_BMSK                                                            0x2
#define HWIO_PCIE30_PARF_FW_INT_STATUS_PME_INT_SHFT                                                            0x1
#define HWIO_PCIE30_PARF_FW_INT_STATUS_HP_INT_BMSK                                                             0x1
#define HWIO_PCIE30_PARF_FW_INT_STATUS_HP_INT_SHFT                                                             0x0

#define HWIO_PCIE30_PARF_FW_INT_MASK_ADDR(x)                                                            ((x) + 0x00010048)
#define HWIO_PCIE30_PARF_FW_INT_MASK_PHYS(x)                                                            ((x) + 0x00010048)
#define HWIO_PCIE30_PARF_FW_INT_MASK_OFFS                                                               (0x00010048)
#define HWIO_PCIE30_PARF_FW_INT_MASK_RMSK                                                                     0x3f
#define HWIO_PCIE30_PARF_FW_INT_MASK_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_FW_INT_MASK_ADDR(x), HWIO_PCIE30_PARF_FW_INT_MASK_RMSK)
#define HWIO_PCIE30_PARF_FW_INT_MASK_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_FW_INT_MASK_ADDR(x), m)
#define HWIO_PCIE30_PARF_FW_INT_MASK_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_FW_INT_MASK_ADDR(x),v)
#define HWIO_PCIE30_PARF_FW_INT_MASK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_FW_INT_MASK_ADDR(x),m,v,HWIO_PCIE30_PARF_FW_INT_MASK_IN(x))
#define HWIO_PCIE30_PARF_FW_INT_MASK_AER_MSI_BMSK                                                             0x20
#define HWIO_PCIE30_PARF_FW_INT_MASK_AER_MSI_SHFT                                                              0x5
#define HWIO_PCIE30_PARF_FW_INT_MASK_PME_MSI_BMSK                                                             0x10
#define HWIO_PCIE30_PARF_FW_INT_MASK_PME_MSI_SHFT                                                              0x4
#define HWIO_PCIE30_PARF_FW_INT_MASK_HP_MSI_BMSK                                                               0x8
#define HWIO_PCIE30_PARF_FW_INT_MASK_HP_MSI_SHFT                                                               0x3
#define HWIO_PCIE30_PARF_FW_INT_MASK_AER_INT_BMSK                                                              0x4
#define HWIO_PCIE30_PARF_FW_INT_MASK_AER_INT_SHFT                                                              0x2
#define HWIO_PCIE30_PARF_FW_INT_MASK_PME_INT_BMSK                                                              0x2
#define HWIO_PCIE30_PARF_FW_INT_MASK_PME_INT_SHFT                                                              0x1
#define HWIO_PCIE30_PARF_FW_INT_MASK_HP_INT_BMSK                                                               0x1
#define HWIO_PCIE30_PARF_FW_INT_MASK_HP_INT_SHFT                                                               0x0

#define HWIO_PCIE30_PARF_FW_INT_CLEAR_ADDR(x)                                                           ((x) + 0x0001004c)
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_PHYS(x)                                                           ((x) + 0x0001004c)
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_OFFS                                                              (0x0001004c)
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_RMSK                                                                    0x3f
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_FW_INT_CLEAR_ADDR(x),v)
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_AER_MSI_BMSK                                                            0x20
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_AER_MSI_SHFT                                                             0x5
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_PME_MSI_BMSK                                                            0x10
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_PME_MSI_SHFT                                                             0x4
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_HP_MSI_BMSK                                                              0x8
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_HP_MSI_SHFT                                                              0x3
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_AER_INT_BMSK                                                             0x4
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_AER_INT_SHFT                                                             0x2
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_PME_INT_BMSK                                                             0x2
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_PME_INT_SHFT                                                             0x1
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_HP_INT_BMSK                                                              0x1
#define HWIO_PCIE30_PARF_FW_INT_CLEAR_HP_INT_SHFT                                                              0x0

#define HWIO_PCIE30_PARF_INTA_STATUS_ADDR(x)                                                            ((x) + 0x00010050)
#define HWIO_PCIE30_PARF_INTA_STATUS_PHYS(x)                                                            ((x) + 0x00010050)
#define HWIO_PCIE30_PARF_INTA_STATUS_OFFS                                                               (0x00010050)
#define HWIO_PCIE30_PARF_INTA_STATUS_RMSK                                                                      0xf
#define HWIO_PCIE30_PARF_INTA_STATUS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_INTA_STATUS_ADDR(x), HWIO_PCIE30_PARF_INTA_STATUS_RMSK)
#define HWIO_PCIE30_PARF_INTA_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_INTA_STATUS_ADDR(x), m)
#define HWIO_PCIE30_PARF_INTA_STATUS_AER_INT_BMSK                                                              0x8
#define HWIO_PCIE30_PARF_INTA_STATUS_AER_INT_SHFT                                                              0x3
#define HWIO_PCIE30_PARF_INTA_STATUS_PME_INT_BMSK                                                              0x4
#define HWIO_PCIE30_PARF_INTA_STATUS_PME_INT_SHFT                                                              0x2
#define HWIO_PCIE30_PARF_INTA_STATUS_HP_INT_BMSK                                                               0x2
#define HWIO_PCIE30_PARF_INTA_STATUS_HP_INT_SHFT                                                               0x1
#define HWIO_PCIE30_PARF_INTA_STATUS_INTA_BMSK                                                                 0x1
#define HWIO_PCIE30_PARF_INTA_STATUS_INTA_SHFT                                                                 0x0

#define HWIO_PCIE30_PARF_INTA_MASK_ADDR(x)                                                              ((x) + 0x00010054)
#define HWIO_PCIE30_PARF_INTA_MASK_PHYS(x)                                                              ((x) + 0x00010054)
#define HWIO_PCIE30_PARF_INTA_MASK_OFFS                                                                 (0x00010054)
#define HWIO_PCIE30_PARF_INTA_MASK_RMSK                                                                        0xf
#define HWIO_PCIE30_PARF_INTA_MASK_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_INTA_MASK_ADDR(x), HWIO_PCIE30_PARF_INTA_MASK_RMSK)
#define HWIO_PCIE30_PARF_INTA_MASK_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_INTA_MASK_ADDR(x), m)
#define HWIO_PCIE30_PARF_INTA_MASK_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_INTA_MASK_ADDR(x),v)
#define HWIO_PCIE30_PARF_INTA_MASK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_INTA_MASK_ADDR(x),m,v,HWIO_PCIE30_PARF_INTA_MASK_IN(x))
#define HWIO_PCIE30_PARF_INTA_MASK_AER_INT_BMSK                                                                0x8
#define HWIO_PCIE30_PARF_INTA_MASK_AER_INT_SHFT                                                                0x3
#define HWIO_PCIE30_PARF_INTA_MASK_PME_INT_BMSK                                                                0x4
#define HWIO_PCIE30_PARF_INTA_MASK_PME_INT_SHFT                                                                0x2
#define HWIO_PCIE30_PARF_INTA_MASK_HP_INT_BMSK                                                                 0x2
#define HWIO_PCIE30_PARF_INTA_MASK_HP_INT_SHFT                                                                 0x1
#define HWIO_PCIE30_PARF_INTA_MASK_INTA_BMSK                                                                   0x1
#define HWIO_PCIE30_PARF_INTA_MASK_INTA_SHFT                                                                   0x0

#define HWIO_PCIE30_PARF_INTA_CLEAR_ADDR(x)                                                             ((x) + 0x00010058)
#define HWIO_PCIE30_PARF_INTA_CLEAR_PHYS(x)                                                             ((x) + 0x00010058)
#define HWIO_PCIE30_PARF_INTA_CLEAR_OFFS                                                                (0x00010058)
#define HWIO_PCIE30_PARF_INTA_CLEAR_RMSK                                                                       0xf
#define HWIO_PCIE30_PARF_INTA_CLEAR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_INTA_CLEAR_ADDR(x),v)
#define HWIO_PCIE30_PARF_INTA_CLEAR_AER_INT_BMSK                                                               0x8
#define HWIO_PCIE30_PARF_INTA_CLEAR_AER_INT_SHFT                                                               0x3
#define HWIO_PCIE30_PARF_INTA_CLEAR_PME_INT_BMSK                                                               0x4
#define HWIO_PCIE30_PARF_INTA_CLEAR_PME_INT_SHFT                                                               0x2
#define HWIO_PCIE30_PARF_INTA_CLEAR_HP_INT_BMSK                                                                0x2
#define HWIO_PCIE30_PARF_INTA_CLEAR_HP_INT_SHFT                                                                0x1
#define HWIO_PCIE30_PARF_INTA_CLEAR_INTA_BMSK                                                                  0x1
#define HWIO_PCIE30_PARF_INTA_CLEAR_INTA_SHFT                                                                  0x0

#define HWIO_PCIE30_PARF_MSI_GEN_MASK_ADDR(x)                                                           ((x) + 0x0001005c)
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_PHYS(x)                                                           ((x) + 0x0001005c)
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_OFFS                                                              (0x0001005c)
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_RMSK                                                                     0x7
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_MSI_GEN_MASK_ADDR(x), HWIO_PCIE30_PARF_MSI_GEN_MASK_RMSK)
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_MSI_GEN_MASK_ADDR(x), m)
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_MSI_GEN_MASK_ADDR(x),v)
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_MSI_GEN_MASK_ADDR(x),m,v,HWIO_PCIE30_PARF_MSI_GEN_MASK_IN(x))
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_AER_MSI_BMSK                                                             0x4
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_AER_MSI_SHFT                                                             0x2
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_PME_MSI_BMSK                                                             0x2
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_PME_MSI_SHFT                                                             0x1
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_HP_MSI_BMSK                                                              0x1
#define HWIO_PCIE30_PARF_MSI_GEN_MASK_HP_MSI_SHFT                                                              0x0

#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_ADDR(x)                                                      ((x) + 0x00010060)
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_PHYS(x)                                                      ((x) + 0x00010060)
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_OFFS                                                         (0x00010060)
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_RMSK                                                         0xffffffff
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_PARF_SBR_RESET_CONTROL_ADDR(x), HWIO_PCIE30_PARF_SBR_RESET_CONTROL_RMSK)
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_PARF_SBR_RESET_CONTROL_ADDR(x), m)
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_PARF_SBR_RESET_CONTROL_ADDR(x),v)
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_PARF_SBR_RESET_CONTROL_ADDR(x),m,v,HWIO_PCIE30_PARF_SBR_RESET_CONTROL_IN(x))
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_HW_FLUSH_RESET_SEQ_TIMER_BMSK                                0xfffff000
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_HW_FLUSH_RESET_SEQ_TIMER_SHFT                                       0xc
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_RESET_SM_STATE_BMSK                                               0xe00
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_RESET_SM_STATE_SHFT                                                 0x9
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_FLUSH_SM_STATE_BMSK                                               0x180
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_FLUSH_SM_STATE_SHFT                                                 0x7
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_SURPRISE_DN_ERR_RPT_CAP_BMSK                                       0x40
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_SURPRISE_DN_ERR_RPT_CAP_SHFT                                        0x6
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_LINKDOWN_SW_RESET_SEQ_COMPLETED_BMSK                               0x20
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_LINKDOWN_SW_RESET_SEQ_COMPLETED_SHFT                                0x5
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_STICKY_SW_RESET_SEQ_COMPLETED_BMSK                                 0x10
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_STICKY_SW_RESET_SEQ_COMPLETED_SHFT                                  0x4
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_LINKDOWN_HW_RESET_SEQ_COMPLETED_BMSK                                0x8
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_LINKDOWN_HW_RESET_SEQ_COMPLETED_SHFT                                0x3
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_LINKDOWN_SW_RESET_SEQ_BMSK                                          0x4
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_LINKDOWN_SW_RESET_SEQ_SHFT                                          0x2
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_STICKY_SW_RESET_SEQ_BMSK                                            0x2
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_STICKY_SW_RESET_SEQ_SHFT                                            0x1
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_LINKDOWN_HW_RESET_SEQ_DISABLE_BMSK                                  0x1
#define HWIO_PCIE30_PARF_SBR_RESET_CONTROL_LINKDOWN_HW_RESET_SEQ_DISABLE_SHFT                                  0x0


#endif /* __HWIO_PCIE_PARF_H__ */
