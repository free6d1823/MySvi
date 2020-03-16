#ifndef __PCIEPSPLANEQDF2400_H__
#define __PCIEPSPLANEQDF2400_H__
/*
===========================================================================
*/
/**
  @file PciePspLaneQdf2400.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r64.0]

  This file contains HWIO register definitions for the following modules:
    PSP0_QSERVER_L0_QSERVER_L0_PCIE_LANE

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
 * MODULE: QSERVER_L0_PCIE_LANE
 *--------------------------------------------------------------------------*/

#define QSERVER_L0_PCIE_LANE_REG_BASE                                                               (PSP0_CM_SERVER_PCIE_SW_BASE      + 0x00000800)

#define HWIO_ATB_SEL1_ADDR(x)                                                                       ((x) + 0x00000000)
#define HWIO_ATB_SEL1_RMSK                                                                                0xff
#define HWIO_ATB_SEL1_IN(x)      \
        in_dword_masked(HWIO_ATB_SEL1_ADDR(x), HWIO_ATB_SEL1_RMSK)
#define HWIO_ATB_SEL1_INM(x, m)      \
        in_dword_masked(HWIO_ATB_SEL1_ADDR(x), m)
#define HWIO_ATB_SEL1_OUT(x, v)      \
        out_dword(HWIO_ATB_SEL1_ADDR(x),v)
#define HWIO_ATB_SEL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ATB_SEL1_ADDR(x),m,v,HWIO_ATB_SEL1_IN(x))
#define HWIO_ATB_SEL1_ATB_SEL_7_0_BMSK                                                                    0xff
#define HWIO_ATB_SEL1_ATB_SEL_7_0_SHFT                                                                     0x0

#define HWIO_ATB_SEL2_ADDR(x)                                                                       ((x) + 0x00000004)
#define HWIO_ATB_SEL2_RMSK                                                                                0xff
#define HWIO_ATB_SEL2_IN(x)      \
        in_dword_masked(HWIO_ATB_SEL2_ADDR(x), HWIO_ATB_SEL2_RMSK)
#define HWIO_ATB_SEL2_INM(x, m)      \
        in_dword_masked(HWIO_ATB_SEL2_ADDR(x), m)
#define HWIO_ATB_SEL2_OUT(x, v)      \
        out_dword(HWIO_ATB_SEL2_ADDR(x),v)
#define HWIO_ATB_SEL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ATB_SEL2_ADDR(x),m,v,HWIO_ATB_SEL2_IN(x))
#define HWIO_ATB_SEL2_ATB_SEL_15_8_BMSK                                                                   0xff
#define HWIO_ATB_SEL2_ATB_SEL_15_8_SHFT                                                                    0x0

#define HWIO_ATB_SEL3_ADDR(x)                                                                       ((x) + 0x00000008)
#define HWIO_ATB_SEL3_RMSK                                                                                 0x1
#define HWIO_ATB_SEL3_IN(x)      \
        in_dword_masked(HWIO_ATB_SEL3_ADDR(x), HWIO_ATB_SEL3_RMSK)
#define HWIO_ATB_SEL3_INM(x, m)      \
        in_dword_masked(HWIO_ATB_SEL3_ADDR(x), m)
#define HWIO_ATB_SEL3_OUT(x, v)      \
        out_dword(HWIO_ATB_SEL3_ADDR(x),v)
#define HWIO_ATB_SEL3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ATB_SEL3_ADDR(x),m,v,HWIO_ATB_SEL3_IN(x))
#define HWIO_ATB_SEL3_ATB_SEL_16_16_BMSK                                                                   0x1
#define HWIO_ATB_SEL3_ATB_SEL_16_16_SHFT                                                                   0x0

#define HWIO_DRVR_CTRL0_ADDR(x)                                                                     ((x) + 0x0000000c)
#define HWIO_DRVR_CTRL0_RMSK                                                                              0x3f
#define HWIO_DRVR_CTRL0_IN(x)      \
        in_dword_masked(HWIO_DRVR_CTRL0_ADDR(x), HWIO_DRVR_CTRL0_RMSK)
#define HWIO_DRVR_CTRL0_INM(x, m)      \
        in_dword_masked(HWIO_DRVR_CTRL0_ADDR(x), m)
#define HWIO_DRVR_CTRL0_OUT(x, v)      \
        out_dword(HWIO_DRVR_CTRL0_ADDR(x),v)
#define HWIO_DRVR_CTRL0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DRVR_CTRL0_ADDR(x),m,v,HWIO_DRVR_CTRL0_IN(x))
#define HWIO_DRVR_CTRL0_UFS_MODE_BMSK                                                                     0x20
#define HWIO_DRVR_CTRL0_UFS_MODE_SHFT                                                                      0x5
#define HWIO_DRVR_CTRL0_TXVAL_VALID_INIT_BMSK                                                             0x10
#define HWIO_DRVR_CTRL0_TXVAL_VALID_INIT_SHFT                                                              0x4
#define HWIO_DRVR_CTRL0_TXVAL_VALID_MUX_BMSK                                                               0x8
#define HWIO_DRVR_CTRL0_TXVAL_VALID_MUX_SHFT                                                               0x3
#define HWIO_DRVR_CTRL0_TXVAL_VALID_BMSK                                                                   0x4
#define HWIO_DRVR_CTRL0_TXVAL_VALID_SHFT                                                                   0x2
#define HWIO_DRVR_CTRL0_USB3P1_MODE_BMSK                                                                   0x2
#define HWIO_DRVR_CTRL0_USB3P1_MODE_SHFT                                                                   0x1
#define HWIO_DRVR_CTRL0_KR_PCIGEN3_MODE_BMSK                                                               0x1
#define HWIO_DRVR_CTRL0_KR_PCIGEN3_MODE_SHFT                                                               0x0

#define HWIO_DRVR_CTRL1_ADDR(x)                                                                     ((x) + 0x00000010)
#define HWIO_DRVR_CTRL1_RMSK                                                                              0x1f
#define HWIO_DRVR_CTRL1_IN(x)      \
        in_dword_masked(HWIO_DRVR_CTRL1_ADDR(x), HWIO_DRVR_CTRL1_RMSK)
#define HWIO_DRVR_CTRL1_INM(x, m)      \
        in_dword_masked(HWIO_DRVR_CTRL1_ADDR(x), m)
#define HWIO_DRVR_CTRL1_OUT(x, v)      \
        out_dword(HWIO_DRVR_CTRL1_ADDR(x),v)
#define HWIO_DRVR_CTRL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DRVR_CTRL1_ADDR(x),m,v,HWIO_DRVR_CTRL1_IN(x))
#define HWIO_DRVR_CTRL1_TX_RESCODE_OFFSET_BMSK                                                            0x1f
#define HWIO_DRVR_CTRL1_TX_RESCODE_OFFSET_SHFT                                                             0x0

#define HWIO_DRVR_CTRL2_ADDR(x)                                                                     ((x) + 0x00000014)
#define HWIO_DRVR_CTRL2_RMSK                                                                              0x1f
#define HWIO_DRVR_CTRL2_IN(x)      \
        in_dword_masked(HWIO_DRVR_CTRL2_ADDR(x), HWIO_DRVR_CTRL2_RMSK)
#define HWIO_DRVR_CTRL2_INM(x, m)      \
        in_dword_masked(HWIO_DRVR_CTRL2_ADDR(x), m)
#define HWIO_DRVR_CTRL2_OUT(x, v)      \
        out_dword(HWIO_DRVR_CTRL2_ADDR(x),v)
#define HWIO_DRVR_CTRL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DRVR_CTRL2_ADDR(x),m,v,HWIO_DRVR_CTRL2_IN(x))
#define HWIO_DRVR_CTRL2_EQ_BYPASS_BMSK                                                                    0x10
#define HWIO_DRVR_CTRL2_EQ_BYPASS_SHFT                                                                     0x4
#define HWIO_DRVR_CTRL2_TX_DRVR_BOOST_EN_BMSK                                                              0x8
#define HWIO_DRVR_CTRL2_TX_DRVR_BOOST_EN_SHFT                                                              0x3
#define HWIO_DRVR_CTRL2_TX_DRVR_BOOST_GEAR_BMSK                                                            0x7
#define HWIO_DRVR_CTRL2_TX_DRVR_BOOST_GEAR_SHFT                                                            0x0

#define HWIO_DRVR_TAP_EN_ADDR(x)                                                                    ((x) + 0x00000018)
#define HWIO_DRVR_TAP_EN_RMSK                                                                              0xf
#define HWIO_DRVR_TAP_EN_IN(x)      \
        in_dword_masked(HWIO_DRVR_TAP_EN_ADDR(x), HWIO_DRVR_TAP_EN_RMSK)
#define HWIO_DRVR_TAP_EN_INM(x, m)      \
        in_dword_masked(HWIO_DRVR_TAP_EN_ADDR(x), m)
#define HWIO_DRVR_TAP_EN_OUT(x, v)      \
        out_dword(HWIO_DRVR_TAP_EN_ADDR(x),v)
#define HWIO_DRVR_TAP_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DRVR_TAP_EN_ADDR(x),m,v,HWIO_DRVR_TAP_EN_IN(x))
#define HWIO_DRVR_TAP_EN_PRE_EN_BMSK                                                                       0x8
#define HWIO_DRVR_TAP_EN_PRE_EN_SHFT                                                                       0x3
#define HWIO_DRVR_TAP_EN_POST_EN_BMSK                                                                      0x4
#define HWIO_DRVR_TAP_EN_POST_EN_SHFT                                                                      0x2
#define HWIO_DRVR_TAP_EN_MAIN_EN_MUX_BMSK                                                                  0x2
#define HWIO_DRVR_TAP_EN_MAIN_EN_MUX_SHFT                                                                  0x1
#define HWIO_DRVR_TAP_EN_MAIN_EN_BMSK                                                                      0x1
#define HWIO_DRVR_TAP_EN_MAIN_EN_SHFT                                                                      0x0

#define HWIO_TX_MARGINING_ADDR(x)                                                                   ((x) + 0x0000001c)
#define HWIO_TX_MARGINING_RMSK                                                                            0x7f
#define HWIO_TX_MARGINING_IN(x)      \
        in_dword_masked(HWIO_TX_MARGINING_ADDR(x), HWIO_TX_MARGINING_RMSK)
#define HWIO_TX_MARGINING_INM(x, m)      \
        in_dword_masked(HWIO_TX_MARGINING_ADDR(x), m)
#define HWIO_TX_MARGINING_OUT(x, v)      \
        out_dword(HWIO_TX_MARGINING_ADDR(x),v)
#define HWIO_TX_MARGINING_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TX_MARGINING_ADDR(x),m,v,HWIO_TX_MARGINING_IN(x))
#define HWIO_TX_MARGINING_TX_MARGINING_MUX_BMSK                                                           0x40
#define HWIO_TX_MARGINING_TX_MARGINING_MUX_SHFT                                                            0x6
#define HWIO_TX_MARGINING_TX_MARGINING_BMSK                                                               0x3f
#define HWIO_TX_MARGINING_TX_MARGINING_SHFT                                                                0x0

#define HWIO_TX_PRE_ADDR(x)                                                                         ((x) + 0x00000020)
#define HWIO_TX_PRE_RMSK                                                                                  0x7f
#define HWIO_TX_PRE_IN(x)      \
        in_dword_masked(HWIO_TX_PRE_ADDR(x), HWIO_TX_PRE_RMSK)
#define HWIO_TX_PRE_INM(x, m)      \
        in_dword_masked(HWIO_TX_PRE_ADDR(x), m)
#define HWIO_TX_PRE_OUT(x, v)      \
        out_dword(HWIO_TX_PRE_ADDR(x),v)
#define HWIO_TX_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TX_PRE_ADDR(x),m,v,HWIO_TX_PRE_IN(x))
#define HWIO_TX_PRE_TX_PRE_MUX_BMSK                                                                       0x40
#define HWIO_TX_PRE_TX_PRE_MUX_SHFT                                                                        0x6
#define HWIO_TX_PRE_TX_PRE_BMSK                                                                           0x3f
#define HWIO_TX_PRE_TX_PRE_SHFT                                                                            0x0

#define HWIO_TX_POST_ADDR(x)                                                                        ((x) + 0x00000024)
#define HWIO_TX_POST_RMSK                                                                                 0x7f
#define HWIO_TX_POST_IN(x)      \
        in_dword_masked(HWIO_TX_POST_ADDR(x), HWIO_TX_POST_RMSK)
#define HWIO_TX_POST_INM(x, m)      \
        in_dword_masked(HWIO_TX_POST_ADDR(x), m)
#define HWIO_TX_POST_OUT(x, v)      \
        out_dword(HWIO_TX_POST_ADDR(x),v)
#define HWIO_TX_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TX_POST_ADDR(x),m,v,HWIO_TX_POST_IN(x))
#define HWIO_TX_POST_TX_POST_MUX_BMSK                                                                     0x40
#define HWIO_TX_POST_TX_POST_MUX_SHFT                                                                      0x6
#define HWIO_TX_POST_TX_POST_BMSK                                                                         0x3f
#define HWIO_TX_POST_TX_POST_SHFT                                                                          0x0

#define HWIO_BIST_PATTERN1_ADDR(x)                                                                  ((x) + 0x00000028)
#define HWIO_BIST_PATTERN1_RMSK                                                                           0xff
#define HWIO_BIST_PATTERN1_IN(x)      \
        in_dword_masked(HWIO_BIST_PATTERN1_ADDR(x), HWIO_BIST_PATTERN1_RMSK)
#define HWIO_BIST_PATTERN1_INM(x, m)      \
        in_dword_masked(HWIO_BIST_PATTERN1_ADDR(x), m)
#define HWIO_BIST_PATTERN1_OUT(x, v)      \
        out_dword(HWIO_BIST_PATTERN1_ADDR(x),v)
#define HWIO_BIST_PATTERN1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BIST_PATTERN1_ADDR(x),m,v,HWIO_BIST_PATTERN1_IN(x))
#define HWIO_BIST_PATTERN1_BIST_PATTERN_7_0_BMSK                                                          0xff
#define HWIO_BIST_PATTERN1_BIST_PATTERN_7_0_SHFT                                                           0x0

#define HWIO_BIST_PATTERN2_ADDR(x)                                                                  ((x) + 0x0000002c)
#define HWIO_BIST_PATTERN2_RMSK                                                                           0xff
#define HWIO_BIST_PATTERN2_IN(x)      \
        in_dword_masked(HWIO_BIST_PATTERN2_ADDR(x), HWIO_BIST_PATTERN2_RMSK)
#define HWIO_BIST_PATTERN2_INM(x, m)      \
        in_dword_masked(HWIO_BIST_PATTERN2_ADDR(x), m)
#define HWIO_BIST_PATTERN2_OUT(x, v)      \
        out_dword(HWIO_BIST_PATTERN2_ADDR(x),v)
#define HWIO_BIST_PATTERN2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BIST_PATTERN2_ADDR(x),m,v,HWIO_BIST_PATTERN2_IN(x))
#define HWIO_BIST_PATTERN2_BIST_PATTERN_15_8_BMSK                                                         0xff
#define HWIO_BIST_PATTERN2_BIST_PATTERN_15_8_SHFT                                                          0x0

#define HWIO_BIST_PATTERN3_ADDR(x)                                                                  ((x) + 0x00000030)
#define HWIO_BIST_PATTERN3_RMSK                                                                           0xff
#define HWIO_BIST_PATTERN3_IN(x)      \
        in_dword_masked(HWIO_BIST_PATTERN3_ADDR(x), HWIO_BIST_PATTERN3_RMSK)
#define HWIO_BIST_PATTERN3_INM(x, m)      \
        in_dword_masked(HWIO_BIST_PATTERN3_ADDR(x), m)
#define HWIO_BIST_PATTERN3_OUT(x, v)      \
        out_dword(HWIO_BIST_PATTERN3_ADDR(x),v)
#define HWIO_BIST_PATTERN3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BIST_PATTERN3_ADDR(x),m,v,HWIO_BIST_PATTERN3_IN(x))
#define HWIO_BIST_PATTERN3_BIST_PATTERN_23_16_BMSK                                                        0xff
#define HWIO_BIST_PATTERN3_BIST_PATTERN_23_16_SHFT                                                         0x0

#define HWIO_BIST_PATTERN4_ADDR(x)                                                                  ((x) + 0x00000034)
#define HWIO_BIST_PATTERN4_RMSK                                                                           0xff
#define HWIO_BIST_PATTERN4_IN(x)      \
        in_dword_masked(HWIO_BIST_PATTERN4_ADDR(x), HWIO_BIST_PATTERN4_RMSK)
#define HWIO_BIST_PATTERN4_INM(x, m)      \
        in_dword_masked(HWIO_BIST_PATTERN4_ADDR(x), m)
#define HWIO_BIST_PATTERN4_OUT(x, v)      \
        out_dword(HWIO_BIST_PATTERN4_ADDR(x),v)
#define HWIO_BIST_PATTERN4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BIST_PATTERN4_ADDR(x),m,v,HWIO_BIST_PATTERN4_IN(x))
#define HWIO_BIST_PATTERN4_BIST_PATTERN_31_24_BMSK                                                        0xff
#define HWIO_BIST_PATTERN4_BIST_PATTERN_31_24_SHFT                                                         0x0

#define HWIO_BIST_PATTERN5_ADDR(x)                                                                  ((x) + 0x00000038)
#define HWIO_BIST_PATTERN5_RMSK                                                                           0xff
#define HWIO_BIST_PATTERN5_IN(x)      \
        in_dword_masked(HWIO_BIST_PATTERN5_ADDR(x), HWIO_BIST_PATTERN5_RMSK)
#define HWIO_BIST_PATTERN5_INM(x, m)      \
        in_dword_masked(HWIO_BIST_PATTERN5_ADDR(x), m)
#define HWIO_BIST_PATTERN5_OUT(x, v)      \
        out_dword(HWIO_BIST_PATTERN5_ADDR(x),v)
#define HWIO_BIST_PATTERN5_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BIST_PATTERN5_ADDR(x),m,v,HWIO_BIST_PATTERN5_IN(x))
#define HWIO_BIST_PATTERN5_BIST_PATTERN_39_32_BMSK                                                        0xff
#define HWIO_BIST_PATTERN5_BIST_PATTERN_39_32_SHFT                                                         0x0

#define HWIO_BIST_MODE_LANENO_SWAP_ADDR(x)                                                          ((x) + 0x0000003c)
#define HWIO_BIST_MODE_LANENO_SWAP_RMSK                                                                   0xff
#define HWIO_BIST_MODE_LANENO_SWAP_IN(x)      \
        in_dword_masked(HWIO_BIST_MODE_LANENO_SWAP_ADDR(x), HWIO_BIST_MODE_LANENO_SWAP_RMSK)
#define HWIO_BIST_MODE_LANENO_SWAP_INM(x, m)      \
        in_dword_masked(HWIO_BIST_MODE_LANENO_SWAP_ADDR(x), m)
#define HWIO_BIST_MODE_LANENO_SWAP_OUT(x, v)      \
        out_dword(HWIO_BIST_MODE_LANENO_SWAP_ADDR(x),v)
#define HWIO_BIST_MODE_LANENO_SWAP_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BIST_MODE_LANENO_SWAP_ADDR(x),m,v,HWIO_BIST_MODE_LANENO_SWAP_IN(x))
#define HWIO_BIST_MODE_LANENO_SWAP_BIST_RX_PRBS_SWAP_BMSK                                                 0x80
#define HWIO_BIST_MODE_LANENO_SWAP_BIST_RX_PRBS_SWAP_SHFT                                                  0x7
#define HWIO_BIST_MODE_LANENO_SWAP_BIST_TX_PRBS_SWAP_BMSK                                                 0x40
#define HWIO_BIST_MODE_LANENO_SWAP_BIST_TX_PRBS_SWAP_SHFT                                                  0x6
#define HWIO_BIST_MODE_LANENO_SWAP_BIST_LANE_NUMBER_BMSK                                                  0x30
#define HWIO_BIST_MODE_LANENO_SWAP_BIST_LANE_NUMBER_SHFT                                                   0x4
#define HWIO_BIST_MODE_LANENO_SWAP_BISTMODE_BMSK                                                           0xf
#define HWIO_BIST_MODE_LANENO_SWAP_BISTMODE_SHFT                                                           0x0

#define HWIO_BIST_INV_ERR_INJ_AUXMODE_ADDR(x)                                                       ((x) + 0x00000040)
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_RMSK                                                                 0xf
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_IN(x)      \
        in_dword_masked(HWIO_BIST_INV_ERR_INJ_AUXMODE_ADDR(x), HWIO_BIST_INV_ERR_INJ_AUXMODE_RMSK)
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_INM(x, m)      \
        in_dword_masked(HWIO_BIST_INV_ERR_INJ_AUXMODE_ADDR(x), m)
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_OUT(x, v)      \
        out_dword(HWIO_BIST_INV_ERR_INJ_AUXMODE_ADDR(x),v)
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BIST_INV_ERR_INJ_AUXMODE_ADDR(x),m,v,HWIO_BIST_INV_ERR_INJ_AUXMODE_IN(x))
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_BIST_AUXMODE_BMSK                                                    0x8
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_BIST_AUXMODE_SHFT                                                    0x3
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_BIST_ERR_INJECT_BMSK                                                 0x4
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_BIST_ERR_INJECT_SHFT                                                 0x2
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_BIST_INVERT_TX_BMSK                                                  0x2
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_BIST_INVERT_TX_SHFT                                                  0x1
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_BIST_INVERT_RX_BMSK                                                  0x1
#define HWIO_BIST_INV_ERR_INJ_AUXMODE_BIST_INVERT_RX_SHFT                                                  0x0

#define HWIO_PRBS_SEED1_ADDR(x)                                                                     ((x) + 0x00000044)
#define HWIO_PRBS_SEED1_RMSK                                                                              0xff
#define HWIO_PRBS_SEED1_IN(x)      \
        in_dword_masked(HWIO_PRBS_SEED1_ADDR(x), HWIO_PRBS_SEED1_RMSK)
#define HWIO_PRBS_SEED1_INM(x, m)      \
        in_dword_masked(HWIO_PRBS_SEED1_ADDR(x), m)
#define HWIO_PRBS_SEED1_OUT(x, v)      \
        out_dword(HWIO_PRBS_SEED1_ADDR(x),v)
#define HWIO_PRBS_SEED1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PRBS_SEED1_ADDR(x),m,v,HWIO_PRBS_SEED1_IN(x))
#define HWIO_PRBS_SEED1_PRBS_SEED_7_0_BMSK                                                                0xff
#define HWIO_PRBS_SEED1_PRBS_SEED_7_0_SHFT                                                                 0x0

#define HWIO_PRBS_SEED2_ADDR(x)                                                                     ((x) + 0x00000048)
#define HWIO_PRBS_SEED2_RMSK                                                                              0xff
#define HWIO_PRBS_SEED2_IN(x)      \
        in_dword_masked(HWIO_PRBS_SEED2_ADDR(x), HWIO_PRBS_SEED2_RMSK)
#define HWIO_PRBS_SEED2_INM(x, m)      \
        in_dword_masked(HWIO_PRBS_SEED2_ADDR(x), m)
#define HWIO_PRBS_SEED2_OUT(x, v)      \
        out_dword(HWIO_PRBS_SEED2_ADDR(x),v)
#define HWIO_PRBS_SEED2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PRBS_SEED2_ADDR(x),m,v,HWIO_PRBS_SEED2_IN(x))
#define HWIO_PRBS_SEED2_PRBS_SEED_15_8_BMSK                                                               0xff
#define HWIO_PRBS_SEED2_PRBS_SEED_15_8_SHFT                                                                0x0

#define HWIO_PRBS_SEED3_ADDR(x)                                                                     ((x) + 0x0000004c)
#define HWIO_PRBS_SEED3_RMSK                                                                              0xff
#define HWIO_PRBS_SEED3_IN(x)      \
        in_dword_masked(HWIO_PRBS_SEED3_ADDR(x), HWIO_PRBS_SEED3_RMSK)
#define HWIO_PRBS_SEED3_INM(x, m)      \
        in_dword_masked(HWIO_PRBS_SEED3_ADDR(x), m)
#define HWIO_PRBS_SEED3_OUT(x, v)      \
        out_dword(HWIO_PRBS_SEED3_ADDR(x),v)
#define HWIO_PRBS_SEED3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PRBS_SEED3_ADDR(x),m,v,HWIO_PRBS_SEED3_IN(x))
#define HWIO_PRBS_SEED3_PRBS_SEED_23_16_BMSK                                                              0xff
#define HWIO_PRBS_SEED3_PRBS_SEED_23_16_SHFT                                                               0x0

#define HWIO_PRBS_SEED4_ADDR(x)                                                                     ((x) + 0x00000050)
#define HWIO_PRBS_SEED4_RMSK                                                                              0xff
#define HWIO_PRBS_SEED4_IN(x)      \
        in_dword_masked(HWIO_PRBS_SEED4_ADDR(x), HWIO_PRBS_SEED4_RMSK)
#define HWIO_PRBS_SEED4_INM(x, m)      \
        in_dword_masked(HWIO_PRBS_SEED4_ADDR(x), m)
#define HWIO_PRBS_SEED4_OUT(x, v)      \
        out_dword(HWIO_PRBS_SEED4_ADDR(x),v)
#define HWIO_PRBS_SEED4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PRBS_SEED4_ADDR(x),m,v,HWIO_PRBS_SEED4_IN(x))
#define HWIO_PRBS_SEED4_PRBS_SEED_31_24_BMSK                                                              0xff
#define HWIO_PRBS_SEED4_PRBS_SEED_31_24_SHFT                                                               0x0

#define HWIO_PERL_LENGTH1_ADDR(x)                                                                   ((x) + 0x00000054)
#define HWIO_PERL_LENGTH1_RMSK                                                                            0xff
#define HWIO_PERL_LENGTH1_IN(x)      \
        in_dword_masked(HWIO_PERL_LENGTH1_ADDR(x), HWIO_PERL_LENGTH1_RMSK)
#define HWIO_PERL_LENGTH1_INM(x, m)      \
        in_dword_masked(HWIO_PERL_LENGTH1_ADDR(x), m)
#define HWIO_PERL_LENGTH1_OUT(x, v)      \
        out_dword(HWIO_PERL_LENGTH1_ADDR(x),v)
#define HWIO_PERL_LENGTH1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PERL_LENGTH1_ADDR(x),m,v,HWIO_PERL_LENGTH1_IN(x))
#define HWIO_PERL_LENGTH1_PERL_LENGTH_7_0_BMSK                                                            0xff
#define HWIO_PERL_LENGTH1_PERL_LENGTH_7_0_SHFT                                                             0x0

#define HWIO_PERL_LENGTH2_ADDR(x)                                                                   ((x) + 0x00000058)
#define HWIO_PERL_LENGTH2_RMSK                                                                            0xff
#define HWIO_PERL_LENGTH2_IN(x)      \
        in_dword_masked(HWIO_PERL_LENGTH2_ADDR(x), HWIO_PERL_LENGTH2_RMSK)
#define HWIO_PERL_LENGTH2_INM(x, m)      \
        in_dword_masked(HWIO_PERL_LENGTH2_ADDR(x), m)
#define HWIO_PERL_LENGTH2_OUT(x, v)      \
        out_dword(HWIO_PERL_LENGTH2_ADDR(x),v)
#define HWIO_PERL_LENGTH2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PERL_LENGTH2_ADDR(x),m,v,HWIO_PERL_LENGTH2_IN(x))
#define HWIO_PERL_LENGTH2_PERL_LENGTH_15_8_BMSK                                                           0xff
#define HWIO_PERL_LENGTH2_PERL_LENGTH_15_8_SHFT                                                            0x0

#define HWIO_RCV_DETECT_LVL_ADDR(x)                                                                 ((x) + 0x0000005c)
#define HWIO_RCV_DETECT_LVL_RMSK                                                                           0x7
#define HWIO_RCV_DETECT_LVL_IN(x)      \
        in_dword_masked(HWIO_RCV_DETECT_LVL_ADDR(x), HWIO_RCV_DETECT_LVL_RMSK)
#define HWIO_RCV_DETECT_LVL_INM(x, m)      \
        in_dword_masked(HWIO_RCV_DETECT_LVL_ADDR(x), m)
#define HWIO_RCV_DETECT_LVL_OUT(x, v)      \
        out_dword(HWIO_RCV_DETECT_LVL_ADDR(x),v)
#define HWIO_RCV_DETECT_LVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RCV_DETECT_LVL_ADDR(x),m,v,HWIO_RCV_DETECT_LVL_IN(x))
#define HWIO_RCV_DETECT_LVL_RECDETECT_LVL_BMSK                                                             0x7
#define HWIO_RCV_DETECT_LVL_RECDETECT_LVL_SHFT                                                             0x0

#define HWIO_TX_BAND_MODE_ADDR(x)                                                                   ((x) + 0x00000060)
#define HWIO_TX_BAND_MODE_RMSK                                                                            0x3f
#define HWIO_TX_BAND_MODE_IN(x)      \
        in_dword_masked(HWIO_TX_BAND_MODE_ADDR(x), HWIO_TX_BAND_MODE_RMSK)
#define HWIO_TX_BAND_MODE_INM(x, m)      \
        in_dword_masked(HWIO_TX_BAND_MODE_ADDR(x), m)
#define HWIO_TX_BAND_MODE_OUT(x, v)      \
        out_dword(HWIO_TX_BAND_MODE_ADDR(x),v)
#define HWIO_TX_BAND_MODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TX_BAND_MODE_ADDR(x),m,v,HWIO_TX_BAND_MODE_IN(x))
#define HWIO_TX_BAND_MODE_TX_BAND_MODE2_BMSK                                                              0x30
#define HWIO_TX_BAND_MODE_TX_BAND_MODE2_SHFT                                                               0x4
#define HWIO_TX_BAND_MODE_TX_BAND_MODE1_BMSK                                                               0xc
#define HWIO_TX_BAND_MODE_TX_BAND_MODE1_SHFT                                                               0x2
#define HWIO_TX_BAND_MODE_TX_BAND_MODE0_BMSK                                                               0x3
#define HWIO_TX_BAND_MODE_TX_BAND_MODE0_SHFT                                                               0x0

#define HWIO_LANE_MODE_ADDR(x)                                                                      ((x) + 0x00000064)
#define HWIO_LANE_MODE_RMSK                                                                               0x7f
#define HWIO_LANE_MODE_IN(x)      \
        in_dword_masked(HWIO_LANE_MODE_ADDR(x), HWIO_LANE_MODE_RMSK)
#define HWIO_LANE_MODE_INM(x, m)      \
        in_dword_masked(HWIO_LANE_MODE_ADDR(x), m)
#define HWIO_LANE_MODE_OUT(x, v)      \
        out_dword(HWIO_LANE_MODE_ADDR(x),v)
#define HWIO_LANE_MODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LANE_MODE_ADDR(x),m,v,HWIO_LANE_MODE_IN(x))
#define HWIO_LANE_MODE_SERDES_MODE_BMSK                                                                   0x40
#define HWIO_LANE_MODE_SERDES_MODE_SHFT                                                                    0x6
#define HWIO_LANE_MODE_LANE_SYNC_MODE_BMSK                                                                0x20
#define HWIO_LANE_MODE_LANE_SYNC_MODE_SHFT                                                                 0x5
#define HWIO_LANE_MODE_LANE_MODE_4_0_BMSK                                                                 0x1f
#define HWIO_LANE_MODE_LANE_MODE_4_0_SHFT                                                                  0x0

#define HWIO_LANE_MODE_2_ADDR(x)                                                                    ((x) + 0x00000068)
#define HWIO_LANE_MODE_2_RMSK                                                                             0x1f
#define HWIO_LANE_MODE_2_IN(x)      \
        in_dword_masked(HWIO_LANE_MODE_2_ADDR(x), HWIO_LANE_MODE_2_RMSK)
#define HWIO_LANE_MODE_2_INM(x, m)      \
        in_dword_masked(HWIO_LANE_MODE_2_ADDR(x), m)
#define HWIO_LANE_MODE_2_OUT(x, v)      \
        out_dword(HWIO_LANE_MODE_2_ADDR(x),v)
#define HWIO_LANE_MODE_2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LANE_MODE_2_ADDR(x),m,v,HWIO_LANE_MODE_2_IN(x))
#define HWIO_LANE_MODE_2_LANE_MODE_9_5_BMSK                                                               0x1f
#define HWIO_LANE_MODE_2_LANE_MODE_9_5_SHFT                                                                0x0

#define HWIO_LPB_EN_ADDR(x)                                                                         ((x) + 0x0000006c)
#define HWIO_LPB_EN_RMSK                                                                                  0xff
#define HWIO_LPB_EN_IN(x)      \
        in_dword_masked(HWIO_LPB_EN_ADDR(x), HWIO_LPB_EN_RMSK)
#define HWIO_LPB_EN_INM(x, m)      \
        in_dword_masked(HWIO_LPB_EN_ADDR(x), m)
#define HWIO_LPB_EN_OUT(x, v)      \
        out_dword(HWIO_LPB_EN_ADDR(x),v)
#define HWIO_LPB_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPB_EN_ADDR(x),m,v,HWIO_LPB_EN_IN(x))
#define HWIO_LPB_EN_TX_RCLK_LPB_EN_MUX_BMSK                                                               0x80
#define HWIO_LPB_EN_TX_RCLK_LPB_EN_MUX_SHFT                                                                0x7
#define HWIO_LPB_EN_TX_RCLK_LPB_EN_BMSK                                                                   0x40
#define HWIO_LPB_EN_TX_RCLK_LPB_EN_SHFT                                                                    0x6
#define HWIO_LPB_EN_EN_SERLPB_MUX_BMSK                                                                    0x20
#define HWIO_LPB_EN_EN_SERLPB_MUX_SHFT                                                                     0x5
#define HWIO_LPB_EN_EN_SERLPB_BMSK                                                                        0x10
#define HWIO_LPB_EN_EN_SERLPB_SHFT                                                                         0x4
#define HWIO_LPB_EN_PAR_LPB_EN_MUX_BMSK                                                                    0x8
#define HWIO_LPB_EN_PAR_LPB_EN_MUX_SHFT                                                                    0x3
#define HWIO_LPB_EN_PAR_LPB_EN_BMSK                                                                        0x4
#define HWIO_LPB_EN_PAR_LPB_EN_SHFT                                                                        0x2
#define HWIO_LPB_EN_EN_RCLK_LPB_MUX_BMSK                                                                   0x2
#define HWIO_LPB_EN_EN_RCLK_LPB_MUX_SHFT                                                                   0x1
#define HWIO_LPB_EN_EN_RCLK_LPB_BMSK                                                                       0x1
#define HWIO_LPB_EN_EN_RCLK_LPB_SHFT                                                                       0x0

#define HWIO_LPB_EN1_ADDR(x)                                                                        ((x) + 0x00000070)
#define HWIO_LPB_EN1_RMSK                                                                                  0x3
#define HWIO_LPB_EN1_IN(x)      \
        in_dword_masked(HWIO_LPB_EN1_ADDR(x), HWIO_LPB_EN1_RMSK)
#define HWIO_LPB_EN1_INM(x, m)      \
        in_dword_masked(HWIO_LPB_EN1_ADDR(x), m)
#define HWIO_LPB_EN1_OUT(x, v)      \
        out_dword(HWIO_LPB_EN1_ADDR(x),v)
#define HWIO_LPB_EN1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPB_EN1_ADDR(x),m,v,HWIO_LPB_EN1_IN(x))
#define HWIO_LPB_EN1_EN_LINELPB_MUX_BMSK                                                                   0x2
#define HWIO_LPB_EN1_EN_LINELPB_MUX_SHFT                                                                   0x1
#define HWIO_LPB_EN1_EN_LINELPB_BMSK                                                                       0x1
#define HWIO_LPB_EN1_EN_LINELPB_SHFT                                                                       0x0

#define HWIO_LPB_SEL_ADDR(x)                                                                        ((x) + 0x00000074)
#define HWIO_LPB_SEL_RMSK                                                                                  0xf
#define HWIO_LPB_SEL_IN(x)      \
        in_dword_masked(HWIO_LPB_SEL_ADDR(x), HWIO_LPB_SEL_RMSK)
#define HWIO_LPB_SEL_INM(x, m)      \
        in_dword_masked(HWIO_LPB_SEL_ADDR(x), m)
#define HWIO_LPB_SEL_OUT(x, v)      \
        out_dword(HWIO_LPB_SEL_ADDR(x),v)
#define HWIO_LPB_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPB_SEL_ADDR(x),m,v,HWIO_LPB_SEL_IN(x))
#define HWIO_LPB_SEL_LINE_LPB_MAPTO_PAR_OR_LINE_BMSK                                                       0x8
#define HWIO_LPB_SEL_LINE_LPB_MAPTO_PAR_OR_LINE_SHFT                                                       0x3
#define HWIO_LPB_SEL_RCLK_LPB_SEL_BMSK                                                                     0x7
#define HWIO_LPB_SEL_RCLK_LPB_SEL_SHFT                                                                     0x0

#define HWIO_PARRATE_REC_DETECT_IDLE_EN_ADDR(x)                                                     ((x) + 0x00000078)
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_RMSK                                                               0xf
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_IN(x)      \
        in_dword_masked(HWIO_PARRATE_REC_DETECT_IDLE_EN_ADDR(x), HWIO_PARRATE_REC_DETECT_IDLE_EN_RMSK)
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_INM(x, m)      \
        in_dword_masked(HWIO_PARRATE_REC_DETECT_IDLE_EN_ADDR(x), m)
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_OUT(x, v)      \
        out_dword(HWIO_PARRATE_REC_DETECT_IDLE_EN_ADDR(x),v)
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PARRATE_REC_DETECT_IDLE_EN_ADDR(x),m,v,HWIO_PARRATE_REC_DETECT_IDLE_EN_IN(x))
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_MUX_BMSK                                                   0x8
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_MUX_SHFT                                                   0x3
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_BMSK                                                       0x4
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_SHFT                                                       0x2
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_EN_RECDETECT_MUX_BMSK                                              0x2
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_EN_RECDETECT_MUX_SHFT                                              0x1
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_EN_RECDETECT_BMSK                                                  0x1
#define HWIO_PARRATE_REC_DETECT_IDLE_EN_EN_RECDETECT_SHFT                                                  0x0

#define HWIO_PARALLEL_RATE_ADDR(x)                                                                  ((x) + 0x0000007c)
#define HWIO_PARALLEL_RATE_RMSK                                                                           0x3f
#define HWIO_PARALLEL_RATE_IN(x)      \
        in_dword_masked(HWIO_PARALLEL_RATE_ADDR(x), HWIO_PARALLEL_RATE_RMSK)
#define HWIO_PARALLEL_RATE_INM(x, m)      \
        in_dword_masked(HWIO_PARALLEL_RATE_ADDR(x), m)
#define HWIO_PARALLEL_RATE_OUT(x, v)      \
        out_dword(HWIO_PARALLEL_RATE_ADDR(x),v)
#define HWIO_PARALLEL_RATE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PARALLEL_RATE_ADDR(x),m,v,HWIO_PARALLEL_RATE_IN(x))
#define HWIO_PARALLEL_RATE_PARALLEL_RATE_MODE2_BMSK                                                       0x30
#define HWIO_PARALLEL_RATE_PARALLEL_RATE_MODE2_SHFT                                                        0x4
#define HWIO_PARALLEL_RATE_PARALLEL_RATE_MODE1_BMSK                                                        0xc
#define HWIO_PARALLEL_RATE_PARALLEL_RATE_MODE1_SHFT                                                        0x2
#define HWIO_PARALLEL_RATE_PARALLEL_RATE_MODE0_BMSK                                                        0x3
#define HWIO_PARALLEL_RATE_PARALLEL_RATE_MODE0_SHFT                                                        0x0

#define HWIO_CLKBUF_ENABLE_ADDR(x)                                                                  ((x) + 0x00000080)
#define HWIO_CLKBUF_ENABLE_RMSK                                                                           0x1f
#define HWIO_CLKBUF_ENABLE_IN(x)      \
        in_dword_masked(HWIO_CLKBUF_ENABLE_ADDR(x), HWIO_CLKBUF_ENABLE_RMSK)
#define HWIO_CLKBUF_ENABLE_INM(x, m)      \
        in_dword_masked(HWIO_CLKBUF_ENABLE_ADDR(x), m)
#define HWIO_CLKBUF_ENABLE_OUT(x, v)      \
        out_dword(HWIO_CLKBUF_ENABLE_ADDR(x),v)
#define HWIO_CLKBUF_ENABLE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CLKBUF_ENABLE_ADDR(x),m,v,HWIO_CLKBUF_ENABLE_IN(x))
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_SW_MUX_BMSK                                                          0x10
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_SW_MUX_SHFT                                                           0x4
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_SW_BMSK                                                               0x8
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_SW_SHFT                                                               0x3
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_PS2_BMSK                                                              0x4
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_PS2_SHFT                                                              0x2
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_PS1B_BMSK                                                             0x2
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_PS1B_SHFT                                                             0x1
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_PS1A_BMSK                                                             0x1
#define HWIO_CLKBUF_ENABLE_CLKBUF_EN_PS1A_SHFT                                                             0x0

#define HWIO_RESET_TSYNC_EN_ADDR(x)                                                                 ((x) + 0x00000084)
#define HWIO_RESET_TSYNC_EN_RMSK                                                                           0x3
#define HWIO_RESET_TSYNC_EN_IN(x)      \
        in_dword_masked(HWIO_RESET_TSYNC_EN_ADDR(x), HWIO_RESET_TSYNC_EN_RMSK)
#define HWIO_RESET_TSYNC_EN_INM(x, m)      \
        in_dword_masked(HWIO_RESET_TSYNC_EN_ADDR(x), m)
#define HWIO_RESET_TSYNC_EN_OUT(x, v)      \
        out_dword(HWIO_RESET_TSYNC_EN_ADDR(x),v)
#define HWIO_RESET_TSYNC_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RESET_TSYNC_EN_ADDR(x),m,v,HWIO_RESET_TSYNC_EN_IN(x))
#define HWIO_RESET_TSYNC_EN_RESET_TSYNC_EN_MUX_BMSK                                                        0x2
#define HWIO_RESET_TSYNC_EN_RESET_TSYNC_EN_MUX_SHFT                                                        0x1
#define HWIO_RESET_TSYNC_EN_RESET_TSYNC_EN_BMSK                                                            0x1
#define HWIO_RESET_TSYNC_EN_RESET_TSYNC_EN_SHFT                                                            0x0

#define HWIO_SERDES_BYP_EN_OUT_ADDR(x)                                                              ((x) + 0x00000088)
#define HWIO_SERDES_BYP_EN_OUT_RMSK                                                                        0xf
#define HWIO_SERDES_BYP_EN_OUT_IN(x)      \
        in_dword_masked(HWIO_SERDES_BYP_EN_OUT_ADDR(x), HWIO_SERDES_BYP_EN_OUT_RMSK)
#define HWIO_SERDES_BYP_EN_OUT_INM(x, m)      \
        in_dword_masked(HWIO_SERDES_BYP_EN_OUT_ADDR(x), m)
#define HWIO_SERDES_BYP_EN_OUT_OUT(x, v)      \
        out_dword(HWIO_SERDES_BYP_EN_OUT_ADDR(x),v)
#define HWIO_SERDES_BYP_EN_OUT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SERDES_BYP_EN_OUT_ADDR(x),m,v,HWIO_SERDES_BYP_EN_OUT_IN(x))
#define HWIO_SERDES_BYP_EN_OUT_SERDES_BYP_IN_MUX_BMSK                                                      0x8
#define HWIO_SERDES_BYP_EN_OUT_SERDES_BYP_IN_MUX_SHFT                                                      0x3
#define HWIO_SERDES_BYP_EN_OUT_SERDES_BYP_IN_BMSK                                                          0x4
#define HWIO_SERDES_BYP_EN_OUT_SERDES_BYP_IN_SHFT                                                          0x2
#define HWIO_SERDES_BYP_EN_OUT_SERDES_BYP_EN_MUX_BMSK                                                      0x2
#define HWIO_SERDES_BYP_EN_OUT_SERDES_BYP_EN_MUX_SHFT                                                      0x1
#define HWIO_SERDES_BYP_EN_OUT_SERDES_BYP_EN_BMSK                                                          0x1
#define HWIO_SERDES_BYP_EN_OUT_SERDES_BYP_EN_SHFT                                                          0x0

#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_ADDR(x)                                               ((x) + 0x0000008c)
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_RMSK                                                        0xff
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_IN(x)      \
        in_dword_masked(HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_ADDR(x), HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_RMSK)
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_INM(x, m)      \
        in_dword_masked(HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_ADDR(x), m)
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_OUT(x, v)      \
        out_dword(HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_ADDR(x),v)
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_ADDR(x),m,v,HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_IN(x))
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TCLK_EN_MUX_BMSK                                            0x80
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TCLK_EN_MUX_SHFT                                             0x7
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TCLK_EN_BMSK                                                0x40
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TCLK_EN_SHFT                                                 0x6
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TX_HIGHZ_MUX_BMSK                                           0x20
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TX_HIGHZ_MUX_SHFT                                            0x5
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TX_HIGHZ_BMSK                                               0x10
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TX_HIGHZ_SHFT                                                0x4
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TRANSCEIVER_BIAS_EN_MUX_BMSK                                 0x8
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TRANSCEIVER_BIAS_EN_MUX_SHFT                                 0x3
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TRANSCEIVER_BIAS_EN_BMSK                                     0x4
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TRANSCEIVER_BIAS_EN_SHFT                                     0x2
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TX_EN_MUX_BMSK                                               0x2
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TX_EN_MUX_SHFT                                               0x1
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TX_EN_BMSK                                                   0x1
#define HWIO_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_TX_EN_SHFT                                                   0x0

#define HWIO_RESET_GEN_ADDR(x)                                                                      ((x) + 0x00000090)
#define HWIO_RESET_GEN_RMSK                                                                               0x7f
#define HWIO_RESET_GEN_IN(x)      \
        in_dword_masked(HWIO_RESET_GEN_ADDR(x), HWIO_RESET_GEN_RMSK)
#define HWIO_RESET_GEN_INM(x, m)      \
        in_dword_masked(HWIO_RESET_GEN_ADDR(x), m)
#define HWIO_RESET_GEN_OUT(x, v)      \
        out_dword(HWIO_RESET_GEN_ADDR(x),v)
#define HWIO_RESET_GEN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RESET_GEN_ADDR(x),m,v,HWIO_RESET_GEN_IN(x))
#define HWIO_RESET_GEN_RX_RESET_MUX_BMSK                                                                  0x40
#define HWIO_RESET_GEN_RX_RESET_MUX_SHFT                                                                   0x6
#define HWIO_RESET_GEN_RX_RESET_BMSK                                                                      0x20
#define HWIO_RESET_GEN_RX_RESET_SHFT                                                                       0x5
#define HWIO_RESET_GEN_JITTERGEN_RESET_BMSK                                                               0x10
#define HWIO_RESET_GEN_JITTERGEN_RESET_SHFT                                                                0x4
#define HWIO_RESET_GEN_CDR_RESET_BMSK                                                                      0x8
#define HWIO_RESET_GEN_CDR_RESET_SHFT                                                                      0x3
#define HWIO_RESET_GEN_TXBIST_RESET_BMSK                                                                   0x4
#define HWIO_RESET_GEN_TXBIST_RESET_SHFT                                                                   0x2
#define HWIO_RESET_GEN_RXBIST_RESET_BMSK                                                                   0x2
#define HWIO_RESET_GEN_RXBIST_RESET_SHFT                                                                   0x1
#define HWIO_RESET_GEN_SW_RESET_BMSK                                                                       0x1
#define HWIO_RESET_GEN_SW_RESET_SHFT                                                                       0x0

#define HWIO_DEBUGBUS_SEL_ADDR(x)                                                                   ((x) + 0x00000094)
#define HWIO_DEBUGBUS_SEL_RMSK                                                                            0x7f
#define HWIO_DEBUGBUS_SEL_IN(x)      \
        in_dword_masked(HWIO_DEBUGBUS_SEL_ADDR(x), HWIO_DEBUGBUS_SEL_RMSK)
#define HWIO_DEBUGBUS_SEL_INM(x, m)      \
        in_dword_masked(HWIO_DEBUGBUS_SEL_ADDR(x), m)
#define HWIO_DEBUGBUS_SEL_OUT(x, v)      \
        out_dword(HWIO_DEBUGBUS_SEL_ADDR(x),v)
#define HWIO_DEBUGBUS_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DEBUGBUS_SEL_ADDR(x),m,v,HWIO_DEBUGBUS_SEL_IN(x))
#define HWIO_DEBUGBUS_SEL_DEBUG_CLK_SEL_BMSK                                                              0x60
#define HWIO_DEBUGBUS_SEL_DEBUG_CLK_SEL_SHFT                                                               0x5
#define HWIO_DEBUGBUS_SEL_DEBUGBUS_SEL_BMSK                                                               0x1f
#define HWIO_DEBUGBUS_SEL_DEBUGBUS_SEL_SHFT                                                                0x0

#define HWIO_DISABLE_CLK_GATING_ADDR(x)                                                             ((x) + 0x00000098)
#define HWIO_DISABLE_CLK_GATING_RMSK                                                                       0x7
#define HWIO_DISABLE_CLK_GATING_IN(x)      \
        in_dword_masked(HWIO_DISABLE_CLK_GATING_ADDR(x), HWIO_DISABLE_CLK_GATING_RMSK)
#define HWIO_DISABLE_CLK_GATING_INM(x, m)      \
        in_dword_masked(HWIO_DISABLE_CLK_GATING_ADDR(x), m)
#define HWIO_DISABLE_CLK_GATING_OUT(x, v)      \
        out_dword(HWIO_DISABLE_CLK_GATING_ADDR(x),v)
#define HWIO_DISABLE_CLK_GATING_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DISABLE_CLK_GATING_ADDR(x),m,v,HWIO_DISABLE_CLK_GATING_IN(x))
#define HWIO_DISABLE_CLK_GATING_DISABLE_CLKGATE_FUNCTIONAL_BMSK                                            0x4
#define HWIO_DISABLE_CLK_GATING_DISABLE_CLKGATE_FUNCTIONAL_SHFT                                            0x2
#define HWIO_DISABLE_CLK_GATING_DISABLE_B2T_CLKGATE_BMSK                                                   0x2
#define HWIO_DISABLE_CLK_GATING_DISABLE_B2T_CLKGATE_SHFT                                                   0x1
#define HWIO_DISABLE_CLK_GATING_DISABLE_CLKGATE_BMSK                                                       0x1
#define HWIO_DISABLE_CLK_GATING_DISABLE_CLKGATE_SHFT                                                       0x0

#define HWIO_CTRL_OUT_OVRD0_ADDR(x)                                                                 ((x) + 0x0000009c)
#define HWIO_CTRL_OUT_OVRD0_RMSK                                                                          0xff
#define HWIO_CTRL_OUT_OVRD0_IN(x)      \
        in_dword_masked(HWIO_CTRL_OUT_OVRD0_ADDR(x), HWIO_CTRL_OUT_OVRD0_RMSK)
#define HWIO_CTRL_OUT_OVRD0_INM(x, m)      \
        in_dword_masked(HWIO_CTRL_OUT_OVRD0_ADDR(x), m)
#define HWIO_CTRL_OUT_OVRD0_OUT(x, v)      \
        out_dword(HWIO_CTRL_OUT_OVRD0_ADDR(x),v)
#define HWIO_CTRL_OUT_OVRD0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CTRL_OUT_OVRD0_ADDR(x),m,v,HWIO_CTRL_OUT_OVRD0_IN(x))
#define HWIO_CTRL_OUT_OVRD0_TSYNC_REQ_BMSK                                                                0x80
#define HWIO_CTRL_OUT_OVRD0_TSYNC_REQ_SHFT                                                                 0x7
#define HWIO_CTRL_OUT_OVRD0_CMN_RXCLK_EN_BMSK                                                             0x40
#define HWIO_CTRL_OUT_OVRD0_CMN_RXCLK_EN_SHFT                                                              0x6
#define HWIO_CTRL_OUT_OVRD0_CMN_TXCLK_EN_BMSK                                                             0x20
#define HWIO_CTRL_OUT_OVRD0_CMN_TXCLK_EN_SHFT                                                              0x5
#define HWIO_CTRL_OUT_OVRD0_LANE_READY_BMSK                                                               0x10
#define HWIO_CTRL_OUT_OVRD0_LANE_READY_SHFT                                                                0x4
#define HWIO_CTRL_OUT_OVRD0_CMN_RATE_BMSK                                                                  0xc
#define HWIO_CTRL_OUT_OVRD0_CMN_RATE_SHFT                                                                  0x2
#define HWIO_CTRL_OUT_OVRD0_CMN_EN_BMSK                                                                    0x2
#define HWIO_CTRL_OUT_OVRD0_CMN_EN_SHFT                                                                    0x1
#define HWIO_CTRL_OUT_OVRD0_CMN_START_BMSK                                                                 0x1
#define HWIO_CTRL_OUT_OVRD0_CMN_START_SHFT                                                                 0x0

#define HWIO_CTRL_OUT_OVRD1_ADDR(x)                                                                 ((x) + 0x000000a0)
#define HWIO_CTRL_OUT_OVRD1_RMSK                                                                          0xff
#define HWIO_CTRL_OUT_OVRD1_IN(x)      \
        in_dword_masked(HWIO_CTRL_OUT_OVRD1_ADDR(x), HWIO_CTRL_OUT_OVRD1_RMSK)
#define HWIO_CTRL_OUT_OVRD1_INM(x, m)      \
        in_dword_masked(HWIO_CTRL_OUT_OVRD1_ADDR(x), m)
#define HWIO_CTRL_OUT_OVRD1_OUT(x, v)      \
        out_dword(HWIO_CTRL_OUT_OVRD1_ADDR(x),v)
#define HWIO_CTRL_OUT_OVRD1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CTRL_OUT_OVRD1_ADDR(x),m,v,HWIO_CTRL_OUT_OVRD1_IN(x))
#define HWIO_CTRL_OUT_OVRD1_PWR_STATE_UPDATE_MUX_BMSK                                                     0x80
#define HWIO_CTRL_OUT_OVRD1_PWR_STATE_UPDATE_MUX_SHFT                                                      0x7
#define HWIO_CTRL_OUT_OVRD1_PWR_STATE_UPDATE_BMSK                                                         0x40
#define HWIO_CTRL_OUT_OVRD1_PWR_STATE_UPDATE_SHFT                                                          0x6
#define HWIO_CTRL_OUT_OVRD1_PWR_STATE_BMSK                                                                0x3c
#define HWIO_CTRL_OUT_OVRD1_PWR_STATE_SHFT                                                                 0x2
#define HWIO_CTRL_OUT_OVRD1_CMN_RATE_UPDATE_BMSK                                                           0x2
#define HWIO_CTRL_OUT_OVRD1_CMN_RATE_UPDATE_SHFT                                                           0x1
#define HWIO_CTRL_OUT_OVRD1_CTRL_OUT_MUX_BMSK                                                              0x1
#define HWIO_CTRL_OUT_OVRD1_CTRL_OUT_MUX_SHFT                                                              0x0

#define HWIO_BIST_STATUS_ADDR(x)                                                                    ((x) + 0x000000a4)
#define HWIO_BIST_STATUS_RMSK                                                                              0xf
#define HWIO_BIST_STATUS_IN(x)      \
        in_dword_masked(HWIO_BIST_STATUS_ADDR(x), HWIO_BIST_STATUS_RMSK)
#define HWIO_BIST_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_BIST_STATUS_ADDR(x), m)
#define HWIO_BIST_STATUS_BIST_TOGGLE_STATUS_BMSK                                                           0x8
#define HWIO_BIST_STATUS_BIST_TOGGLE_STATUS_SHFT                                                           0x3
#define HWIO_BIST_STATUS_BIST_SYNC_STATUS_BMSK                                                             0x4
#define HWIO_BIST_STATUS_BIST_SYNC_STATUS_SHFT                                                             0x2
#define HWIO_BIST_STATUS_BIST_MATCH_STATUS_BMSK                                                            0x2
#define HWIO_BIST_STATUS_BIST_MATCH_STATUS_SHFT                                                            0x1
#define HWIO_BIST_STATUS_BIST_ERR_STATUS_BMSK                                                              0x1
#define HWIO_BIST_STATUS_BIST_ERR_STATUS_SHFT                                                              0x0

#define HWIO_BIST_ERR_CNT1_STATUS_ADDR(x)                                                           ((x) + 0x000000a8)
#define HWIO_BIST_ERR_CNT1_STATUS_RMSK                                                                    0xff
#define HWIO_BIST_ERR_CNT1_STATUS_IN(x)      \
        in_dword_masked(HWIO_BIST_ERR_CNT1_STATUS_ADDR(x), HWIO_BIST_ERR_CNT1_STATUS_RMSK)
#define HWIO_BIST_ERR_CNT1_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_BIST_ERR_CNT1_STATUS_ADDR(x), m)
#define HWIO_BIST_ERR_CNT1_STATUS_BIST_ERR_CNT_7_0_BMSK                                                   0xff
#define HWIO_BIST_ERR_CNT1_STATUS_BIST_ERR_CNT_7_0_SHFT                                                    0x0

#define HWIO_BIST_ERR_CNT2_STATUS_ADDR(x)                                                           ((x) + 0x000000ac)
#define HWIO_BIST_ERR_CNT2_STATUS_RMSK                                                                    0xff
#define HWIO_BIST_ERR_CNT2_STATUS_IN(x)      \
        in_dword_masked(HWIO_BIST_ERR_CNT2_STATUS_ADDR(x), HWIO_BIST_ERR_CNT2_STATUS_RMSK)
#define HWIO_BIST_ERR_CNT2_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_BIST_ERR_CNT2_STATUS_ADDR(x), m)
#define HWIO_BIST_ERR_CNT2_STATUS_BIST_ERR_CNT_15_8_BMSK                                                  0xff
#define HWIO_BIST_ERR_CNT2_STATUS_BIST_ERR_CNT_15_8_SHFT                                                   0x0

#define HWIO_DEBUG_BUS_STATUS1_ADDR(x)                                                              ((x) + 0x000000b0)
#define HWIO_DEBUG_BUS_STATUS1_RMSK                                                                       0xff
#define HWIO_DEBUG_BUS_STATUS1_IN(x)      \
        in_dword_masked(HWIO_DEBUG_BUS_STATUS1_ADDR(x), HWIO_DEBUG_BUS_STATUS1_RMSK)
#define HWIO_DEBUG_BUS_STATUS1_INM(x, m)      \
        in_dword_masked(HWIO_DEBUG_BUS_STATUS1_ADDR(x), m)
#define HWIO_DEBUG_BUS_STATUS1_DEBUG_BUS_7_0_BMSK                                                         0xff
#define HWIO_DEBUG_BUS_STATUS1_DEBUG_BUS_7_0_SHFT                                                          0x0

#define HWIO_DEBUG_BUS_STATUS2_ADDR(x)                                                              ((x) + 0x000000b4)
#define HWIO_DEBUG_BUS_STATUS2_RMSK                                                                       0xff
#define HWIO_DEBUG_BUS_STATUS2_IN(x)      \
        in_dword_masked(HWIO_DEBUG_BUS_STATUS2_ADDR(x), HWIO_DEBUG_BUS_STATUS2_RMSK)
#define HWIO_DEBUG_BUS_STATUS2_INM(x, m)      \
        in_dword_masked(HWIO_DEBUG_BUS_STATUS2_ADDR(x), m)
#define HWIO_DEBUG_BUS_STATUS2_DEBUG_BUS_15_8_BMSK                                                        0xff
#define HWIO_DEBUG_BUS_STATUS2_DEBUG_BUS_15_8_SHFT                                                         0x0

#define HWIO_DEBUG_BUS_STATUS3_ADDR(x)                                                              ((x) + 0x000000b8)
#define HWIO_DEBUG_BUS_STATUS3_RMSK                                                                       0xff
#define HWIO_DEBUG_BUS_STATUS3_IN(x)      \
        in_dword_masked(HWIO_DEBUG_BUS_STATUS3_ADDR(x), HWIO_DEBUG_BUS_STATUS3_RMSK)
#define HWIO_DEBUG_BUS_STATUS3_INM(x, m)      \
        in_dword_masked(HWIO_DEBUG_BUS_STATUS3_ADDR(x), m)
#define HWIO_DEBUG_BUS_STATUS3_DEBUG_BUS_23_16_BMSK                                                       0xff
#define HWIO_DEBUG_BUS_STATUS3_DEBUG_BUS_23_16_SHFT                                                        0x0

#define HWIO_DEBUG_BUS_STATUS4_ADDR(x)                                                              ((x) + 0x000000bc)
#define HWIO_DEBUG_BUS_STATUS4_RMSK                                                                       0xff
#define HWIO_DEBUG_BUS_STATUS4_IN(x)      \
        in_dword_masked(HWIO_DEBUG_BUS_STATUS4_ADDR(x), HWIO_DEBUG_BUS_STATUS4_RMSK)
#define HWIO_DEBUG_BUS_STATUS4_INM(x, m)      \
        in_dword_masked(HWIO_DEBUG_BUS_STATUS4_ADDR(x), m)
#define HWIO_DEBUG_BUS_STATUS4_DEBUG_BUS_31_24_BMSK                                                       0xff
#define HWIO_DEBUG_BUS_STATUS4_DEBUG_BUS_31_24_SHFT                                                        0x0

#define HWIO_CML_CTRL_MODE0_ADDR(x)                                                                 ((x) + 0x000000c0)
#define HWIO_CML_CTRL_MODE0_RMSK                                                                          0x3f
#define HWIO_CML_CTRL_MODE0_IN(x)      \
        in_dword_masked(HWIO_CML_CTRL_MODE0_ADDR(x), HWIO_CML_CTRL_MODE0_RMSK)
#define HWIO_CML_CTRL_MODE0_INM(x, m)      \
        in_dword_masked(HWIO_CML_CTRL_MODE0_ADDR(x), m)
#define HWIO_CML_CTRL_MODE0_OUT(x, v)      \
        out_dword(HWIO_CML_CTRL_MODE0_ADDR(x),v)
#define HWIO_CML_CTRL_MODE0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CML_CTRL_MODE0_ADDR(x),m,v,HWIO_CML_CTRL_MODE0_IN(x))
#define HWIO_CML_CTRL_MODE0_CML_GEAR_MODE0_BMSK                                                           0x38
#define HWIO_CML_CTRL_MODE0_CML_GEAR_MODE0_SHFT                                                            0x3
#define HWIO_CML_CTRL_MODE0_CML2CMOS_IBOOST_MODE0_BMSK                                                     0x7
#define HWIO_CML_CTRL_MODE0_CML2CMOS_IBOOST_MODE0_SHFT                                                     0x0

#define HWIO_CML_CTRL_MODE1_ADDR(x)                                                                 ((x) + 0x000000c4)
#define HWIO_CML_CTRL_MODE1_RMSK                                                                          0x3f
#define HWIO_CML_CTRL_MODE1_IN(x)      \
        in_dword_masked(HWIO_CML_CTRL_MODE1_ADDR(x), HWIO_CML_CTRL_MODE1_RMSK)
#define HWIO_CML_CTRL_MODE1_INM(x, m)      \
        in_dword_masked(HWIO_CML_CTRL_MODE1_ADDR(x), m)
#define HWIO_CML_CTRL_MODE1_OUT(x, v)      \
        out_dword(HWIO_CML_CTRL_MODE1_ADDR(x),v)
#define HWIO_CML_CTRL_MODE1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CML_CTRL_MODE1_ADDR(x),m,v,HWIO_CML_CTRL_MODE1_IN(x))
#define HWIO_CML_CTRL_MODE1_CML_GEAR_MODE1_BMSK                                                           0x38
#define HWIO_CML_CTRL_MODE1_CML_GEAR_MODE1_SHFT                                                            0x3
#define HWIO_CML_CTRL_MODE1_CML2CMOS_IBOOST_MODE1_BMSK                                                     0x7
#define HWIO_CML_CTRL_MODE1_CML2CMOS_IBOOST_MODE1_SHFT                                                     0x0

#define HWIO_CML_CTRL_MODE2_ADDR(x)                                                                 ((x) + 0x000000c8)
#define HWIO_CML_CTRL_MODE2_RMSK                                                                          0x3f
#define HWIO_CML_CTRL_MODE2_IN(x)      \
        in_dword_masked(HWIO_CML_CTRL_MODE2_ADDR(x), HWIO_CML_CTRL_MODE2_RMSK)
#define HWIO_CML_CTRL_MODE2_INM(x, m)      \
        in_dword_masked(HWIO_CML_CTRL_MODE2_ADDR(x), m)
#define HWIO_CML_CTRL_MODE2_OUT(x, v)      \
        out_dword(HWIO_CML_CTRL_MODE2_ADDR(x),v)
#define HWIO_CML_CTRL_MODE2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CML_CTRL_MODE2_ADDR(x),m,v,HWIO_CML_CTRL_MODE2_IN(x))
#define HWIO_CML_CTRL_MODE2_CML_GEAR_MODE2_BMSK                                                           0x38
#define HWIO_CML_CTRL_MODE2_CML_GEAR_MODE2_SHFT                                                            0x3
#define HWIO_CML_CTRL_MODE2_CML2CMOS_IBOOST_MODE2_BMSK                                                     0x7
#define HWIO_CML_CTRL_MODE2_CML2CMOS_IBOOST_MODE2_SHFT                                                     0x0

#define HWIO_PREAMP_CTRL_MODE0_ADDR(x)                                                              ((x) + 0x000000cc)
#define HWIO_PREAMP_CTRL_MODE0_RMSK                                                                        0x7
#define HWIO_PREAMP_CTRL_MODE0_IN(x)      \
        in_dword_masked(HWIO_PREAMP_CTRL_MODE0_ADDR(x), HWIO_PREAMP_CTRL_MODE0_RMSK)
#define HWIO_PREAMP_CTRL_MODE0_INM(x, m)      \
        in_dword_masked(HWIO_PREAMP_CTRL_MODE0_ADDR(x), m)
#define HWIO_PREAMP_CTRL_MODE0_OUT(x, v)      \
        out_dword(HWIO_PREAMP_CTRL_MODE0_ADDR(x),v)
#define HWIO_PREAMP_CTRL_MODE0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PREAMP_CTRL_MODE0_ADDR(x),m,v,HWIO_PREAMP_CTRL_MODE0_IN(x))
#define HWIO_PREAMP_CTRL_MODE0_PREAMPGEAR_MODE0_BMSK                                                       0x7
#define HWIO_PREAMP_CTRL_MODE0_PREAMPGEAR_MODE0_SHFT                                                       0x0

#define HWIO_PREAMP_CTRL_MODE1_ADDR(x)                                                              ((x) + 0x000000d0)
#define HWIO_PREAMP_CTRL_MODE1_RMSK                                                                        0x7
#define HWIO_PREAMP_CTRL_MODE1_IN(x)      \
        in_dword_masked(HWIO_PREAMP_CTRL_MODE1_ADDR(x), HWIO_PREAMP_CTRL_MODE1_RMSK)
#define HWIO_PREAMP_CTRL_MODE1_INM(x, m)      \
        in_dword_masked(HWIO_PREAMP_CTRL_MODE1_ADDR(x), m)
#define HWIO_PREAMP_CTRL_MODE1_OUT(x, v)      \
        out_dword(HWIO_PREAMP_CTRL_MODE1_ADDR(x),v)
#define HWIO_PREAMP_CTRL_MODE1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PREAMP_CTRL_MODE1_ADDR(x),m,v,HWIO_PREAMP_CTRL_MODE1_IN(x))
#define HWIO_PREAMP_CTRL_MODE1_PREAMPGEAR_MODE1_BMSK                                                       0x7
#define HWIO_PREAMP_CTRL_MODE1_PREAMPGEAR_MODE1_SHFT                                                       0x0

#define HWIO_PREAMP_CTRL_MODE2_ADDR(x)                                                              ((x) + 0x000000d4)
#define HWIO_PREAMP_CTRL_MODE2_RMSK                                                                        0x7
#define HWIO_PREAMP_CTRL_MODE2_IN(x)      \
        in_dword_masked(HWIO_PREAMP_CTRL_MODE2_ADDR(x), HWIO_PREAMP_CTRL_MODE2_RMSK)
#define HWIO_PREAMP_CTRL_MODE2_INM(x, m)      \
        in_dword_masked(HWIO_PREAMP_CTRL_MODE2_ADDR(x), m)
#define HWIO_PREAMP_CTRL_MODE2_OUT(x, v)      \
        out_dword(HWIO_PREAMP_CTRL_MODE2_ADDR(x),v)
#define HWIO_PREAMP_CTRL_MODE2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PREAMP_CTRL_MODE2_ADDR(x),m,v,HWIO_PREAMP_CTRL_MODE2_IN(x))
#define HWIO_PREAMP_CTRL_MODE2_PREAMPGEAR_MODE2_BMSK                                                       0x7
#define HWIO_PREAMP_CTRL_MODE2_PREAMPGEAR_MODE2_SHFT                                                       0x0

#define HWIO_MIXER_CTRL_MODE0_ADDR(x)                                                               ((x) + 0x000000d8)
#define HWIO_MIXER_CTRL_MODE0_RMSK                                                                        0x3f
#define HWIO_MIXER_CTRL_MODE0_IN(x)      \
        in_dword_masked(HWIO_MIXER_CTRL_MODE0_ADDR(x), HWIO_MIXER_CTRL_MODE0_RMSK)
#define HWIO_MIXER_CTRL_MODE0_INM(x, m)      \
        in_dword_masked(HWIO_MIXER_CTRL_MODE0_ADDR(x), m)
#define HWIO_MIXER_CTRL_MODE0_OUT(x, v)      \
        out_dword(HWIO_MIXER_CTRL_MODE0_ADDR(x),v)
#define HWIO_MIXER_CTRL_MODE0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MIXER_CTRL_MODE0_ADDR(x),m,v,HWIO_MIXER_CTRL_MODE0_IN(x))
#define HWIO_MIXER_CTRL_MODE0_MIXER_LOADB_MODE0_BMSK                                                      0x3c
#define HWIO_MIXER_CTRL_MODE0_MIXER_LOADB_MODE0_SHFT                                                       0x2
#define HWIO_MIXER_CTRL_MODE0_MIXER_DATARATE_MODE0_BMSK                                                    0x3
#define HWIO_MIXER_CTRL_MODE0_MIXER_DATARATE_MODE0_SHFT                                                    0x0

#define HWIO_MIXER_CTRL_MODE1_ADDR(x)                                                               ((x) + 0x000000dc)
#define HWIO_MIXER_CTRL_MODE1_RMSK                                                                        0x3f
#define HWIO_MIXER_CTRL_MODE1_IN(x)      \
        in_dword_masked(HWIO_MIXER_CTRL_MODE1_ADDR(x), HWIO_MIXER_CTRL_MODE1_RMSK)
#define HWIO_MIXER_CTRL_MODE1_INM(x, m)      \
        in_dword_masked(HWIO_MIXER_CTRL_MODE1_ADDR(x), m)
#define HWIO_MIXER_CTRL_MODE1_OUT(x, v)      \
        out_dword(HWIO_MIXER_CTRL_MODE1_ADDR(x),v)
#define HWIO_MIXER_CTRL_MODE1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MIXER_CTRL_MODE1_ADDR(x),m,v,HWIO_MIXER_CTRL_MODE1_IN(x))
#define HWIO_MIXER_CTRL_MODE1_MIXER_LOADB_MODE1_BMSK                                                      0x3c
#define HWIO_MIXER_CTRL_MODE1_MIXER_LOADB_MODE1_SHFT                                                       0x2
#define HWIO_MIXER_CTRL_MODE1_MIXER_DATARATE_MODE1_BMSK                                                    0x3
#define HWIO_MIXER_CTRL_MODE1_MIXER_DATARATE_MODE1_SHFT                                                    0x0

#define HWIO_MIXER_CTRL_MODE2_ADDR(x)                                                               ((x) + 0x000000e0)
#define HWIO_MIXER_CTRL_MODE2_RMSK                                                                        0x3f
#define HWIO_MIXER_CTRL_MODE2_IN(x)      \
        in_dword_masked(HWIO_MIXER_CTRL_MODE2_ADDR(x), HWIO_MIXER_CTRL_MODE2_RMSK)
#define HWIO_MIXER_CTRL_MODE2_INM(x, m)      \
        in_dword_masked(HWIO_MIXER_CTRL_MODE2_ADDR(x), m)
#define HWIO_MIXER_CTRL_MODE2_OUT(x, v)      \
        out_dword(HWIO_MIXER_CTRL_MODE2_ADDR(x),v)
#define HWIO_MIXER_CTRL_MODE2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MIXER_CTRL_MODE2_ADDR(x),m,v,HWIO_MIXER_CTRL_MODE2_IN(x))
#define HWIO_MIXER_CTRL_MODE2_MIXER_LOADB_MODE2_BMSK                                                      0x3c
#define HWIO_MIXER_CTRL_MODE2_MIXER_LOADB_MODE2_SHFT                                                       0x2
#define HWIO_MIXER_CTRL_MODE2_MIXER_DATARATE_MODE2_BMSK                                                    0x3
#define HWIO_MIXER_CTRL_MODE2_MIXER_DATARATE_MODE2_SHFT                                                    0x0

#define HWIO_MAIN_THRESH1_ADDR(x)                                                                   ((x) + 0x000000e4)
#define HWIO_MAIN_THRESH1_RMSK                                                                            0x1f
#define HWIO_MAIN_THRESH1_IN(x)      \
        in_dword_masked(HWIO_MAIN_THRESH1_ADDR(x), HWIO_MAIN_THRESH1_RMSK)
#define HWIO_MAIN_THRESH1_INM(x, m)      \
        in_dword_masked(HWIO_MAIN_THRESH1_ADDR(x), m)
#define HWIO_MAIN_THRESH1_OUT(x, v)      \
        out_dword(HWIO_MAIN_THRESH1_ADDR(x),v)
#define HWIO_MAIN_THRESH1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MAIN_THRESH1_ADDR(x),m,v,HWIO_MAIN_THRESH1_IN(x))
#define HWIO_MAIN_THRESH1_MAIN_THRESH1_BMSK                                                               0x1f
#define HWIO_MAIN_THRESH1_MAIN_THRESH1_SHFT                                                                0x0

#define HWIO_MAIN_THRESH2_ADDR(x)                                                                   ((x) + 0x000000e8)
#define HWIO_MAIN_THRESH2_RMSK                                                                            0x1f
#define HWIO_MAIN_THRESH2_IN(x)      \
        in_dword_masked(HWIO_MAIN_THRESH2_ADDR(x), HWIO_MAIN_THRESH2_RMSK)
#define HWIO_MAIN_THRESH2_INM(x, m)      \
        in_dword_masked(HWIO_MAIN_THRESH2_ADDR(x), m)
#define HWIO_MAIN_THRESH2_OUT(x, v)      \
        out_dword(HWIO_MAIN_THRESH2_ADDR(x),v)
#define HWIO_MAIN_THRESH2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MAIN_THRESH2_ADDR(x),m,v,HWIO_MAIN_THRESH2_IN(x))
#define HWIO_MAIN_THRESH2_MAIN_THRESH2_BMSK                                                               0x1f
#define HWIO_MAIN_THRESH2_MAIN_THRESH2_SHFT                                                                0x0

#define HWIO_POST_THRESH1_ADDR(x)                                                                   ((x) + 0x000000ec)
#define HWIO_POST_THRESH1_RMSK                                                                            0x1f
#define HWIO_POST_THRESH1_IN(x)      \
        in_dword_masked(HWIO_POST_THRESH1_ADDR(x), HWIO_POST_THRESH1_RMSK)
#define HWIO_POST_THRESH1_INM(x, m)      \
        in_dword_masked(HWIO_POST_THRESH1_ADDR(x), m)
#define HWIO_POST_THRESH1_OUT(x, v)      \
        out_dword(HWIO_POST_THRESH1_ADDR(x),v)
#define HWIO_POST_THRESH1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_POST_THRESH1_ADDR(x),m,v,HWIO_POST_THRESH1_IN(x))
#define HWIO_POST_THRESH1_POST_THRESH1_BMSK                                                               0x1f
#define HWIO_POST_THRESH1_POST_THRESH1_SHFT                                                                0x0

#define HWIO_POST_THRESH2_ADDR(x)                                                                   ((x) + 0x000000f0)
#define HWIO_POST_THRESH2_RMSK                                                                            0x1f
#define HWIO_POST_THRESH2_IN(x)      \
        in_dword_masked(HWIO_POST_THRESH2_ADDR(x), HWIO_POST_THRESH2_RMSK)
#define HWIO_POST_THRESH2_INM(x, m)      \
        in_dword_masked(HWIO_POST_THRESH2_ADDR(x), m)
#define HWIO_POST_THRESH2_OUT(x, v)      \
        out_dword(HWIO_POST_THRESH2_ADDR(x),v)
#define HWIO_POST_THRESH2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_POST_THRESH2_ADDR(x),m,v,HWIO_POST_THRESH2_IN(x))
#define HWIO_POST_THRESH2_POST_THRESH2_BMSK                                                               0x1f
#define HWIO_POST_THRESH2_POST_THRESH2_SHFT                                                                0x0

#define HWIO_PRE_THRESH1_ADDR(x)                                                                    ((x) + 0x000000f4)
#define HWIO_PRE_THRESH1_RMSK                                                                             0x3f
#define HWIO_PRE_THRESH1_IN(x)      \
        in_dword_masked(HWIO_PRE_THRESH1_ADDR(x), HWIO_PRE_THRESH1_RMSK)
#define HWIO_PRE_THRESH1_INM(x, m)      \
        in_dword_masked(HWIO_PRE_THRESH1_ADDR(x), m)
#define HWIO_PRE_THRESH1_OUT(x, v)      \
        out_dword(HWIO_PRE_THRESH1_ADDR(x),v)
#define HWIO_PRE_THRESH1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PRE_THRESH1_ADDR(x),m,v,HWIO_PRE_THRESH1_IN(x))
#define HWIO_PRE_THRESH1_PRE_THRESH1_BMSK                                                                 0x3f
#define HWIO_PRE_THRESH1_PRE_THRESH1_SHFT                                                                  0x0

#define HWIO_PRE_THRESH2_ADDR(x)                                                                    ((x) + 0x000000f8)
#define HWIO_PRE_THRESH2_RMSK                                                                             0x3f
#define HWIO_PRE_THRESH2_IN(x)      \
        in_dword_masked(HWIO_PRE_THRESH2_ADDR(x), HWIO_PRE_THRESH2_RMSK)
#define HWIO_PRE_THRESH2_INM(x, m)      \
        in_dword_masked(HWIO_PRE_THRESH2_ADDR(x), m)
#define HWIO_PRE_THRESH2_OUT(x, v)      \
        out_dword(HWIO_PRE_THRESH2_ADDR(x),v)
#define HWIO_PRE_THRESH2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PRE_THRESH2_ADDR(x),m,v,HWIO_PRE_THRESH2_IN(x))
#define HWIO_PRE_THRESH2_PRE_THRESH2_BMSK                                                                 0x3f
#define HWIO_PRE_THRESH2_PRE_THRESH2_SHFT                                                                  0x0

#define HWIO_CTLE_THRESH_DFE_ADDR(x)                                                                ((x) + 0x000000fc)
#define HWIO_CTLE_THRESH_DFE_RMSK                                                                         0x3f
#define HWIO_CTLE_THRESH_DFE_IN(x)      \
        in_dword_masked(HWIO_CTLE_THRESH_DFE_ADDR(x), HWIO_CTLE_THRESH_DFE_RMSK)
#define HWIO_CTLE_THRESH_DFE_INM(x, m)      \
        in_dword_masked(HWIO_CTLE_THRESH_DFE_ADDR(x), m)
#define HWIO_CTLE_THRESH_DFE_OUT(x, v)      \
        out_dword(HWIO_CTLE_THRESH_DFE_ADDR(x),v)
#define HWIO_CTLE_THRESH_DFE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CTLE_THRESH_DFE_ADDR(x),m,v,HWIO_CTLE_THRESH_DFE_IN(x))
#define HWIO_CTLE_THRESH_DFE_CTLE_THRESH_DFE_BMSK                                                         0x3f
#define HWIO_CTLE_THRESH_DFE_CTLE_THRESH_DFE_SHFT                                                          0x0

#define HWIO_VGA_THRESH_DFE_ADDR(x)                                                                 ((x) + 0x00000100)
#define HWIO_VGA_THRESH_DFE_RMSK                                                                          0x3f
#define HWIO_VGA_THRESH_DFE_IN(x)      \
        in_dword_masked(HWIO_VGA_THRESH_DFE_ADDR(x), HWIO_VGA_THRESH_DFE_RMSK)
#define HWIO_VGA_THRESH_DFE_INM(x, m)      \
        in_dword_masked(HWIO_VGA_THRESH_DFE_ADDR(x), m)
#define HWIO_VGA_THRESH_DFE_OUT(x, v)      \
        out_dword(HWIO_VGA_THRESH_DFE_ADDR(x),v)
#define HWIO_VGA_THRESH_DFE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VGA_THRESH_DFE_ADDR(x),m,v,HWIO_VGA_THRESH_DFE_IN(x))
#define HWIO_VGA_THRESH_DFE_VGA_THRESH_DFE_BMSK                                                           0x3f
#define HWIO_VGA_THRESH_DFE_VGA_THRESH_DFE_SHFT                                                            0x0

#define HWIO_CTLE_THRESH_ADDR(x)                                                                    ((x) + 0x00000104)
#define HWIO_CTLE_THRESH_RMSK                                                                             0xff
#define HWIO_CTLE_THRESH_IN(x)      \
        in_dword_masked(HWIO_CTLE_THRESH_ADDR(x), HWIO_CTLE_THRESH_RMSK)
#define HWIO_CTLE_THRESH_INM(x, m)      \
        in_dword_masked(HWIO_CTLE_THRESH_ADDR(x), m)
#define HWIO_CTLE_THRESH_OUT(x, v)      \
        out_dword(HWIO_CTLE_THRESH_ADDR(x),v)
#define HWIO_CTLE_THRESH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CTLE_THRESH_ADDR(x),m,v,HWIO_CTLE_THRESH_IN(x))
#define HWIO_CTLE_THRESH_CTLE_MODE_BMSK                                                                   0xc0
#define HWIO_CTLE_THRESH_CTLE_MODE_SHFT                                                                    0x6
#define HWIO_CTLE_THRESH_CTLE_THRESH_BMSK                                                                 0x3f
#define HWIO_CTLE_THRESH_CTLE_THRESH_SHFT                                                                  0x0

#define HWIO_RXENGINE_EN0_ADDR(x)                                                                   ((x) + 0x00000108)
#define HWIO_RXENGINE_EN0_RMSK                                                                            0xff
#define HWIO_RXENGINE_EN0_IN(x)      \
        in_dword_masked(HWIO_RXENGINE_EN0_ADDR(x), HWIO_RXENGINE_EN0_RMSK)
#define HWIO_RXENGINE_EN0_INM(x, m)      \
        in_dword_masked(HWIO_RXENGINE_EN0_ADDR(x), m)
#define HWIO_RXENGINE_EN0_OUT(x, v)      \
        out_dword(HWIO_RXENGINE_EN0_ADDR(x),v)
#define HWIO_RXENGINE_EN0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RXENGINE_EN0_ADDR(x),m,v,HWIO_RXENGINE_EN0_IN(x))
#define HWIO_RXENGINE_EN0_DFE_FREEZE_EN_MUX_BMSK                                                          0x80
#define HWIO_RXENGINE_EN0_DFE_FREEZE_EN_MUX_SHFT                                                           0x7
#define HWIO_RXENGINE_EN0_FREEZE_DFE_BMSK                                                                 0x40
#define HWIO_RXENGINE_EN0_FREEZE_DFE_SHFT                                                                  0x6
#define HWIO_RXENGINE_EN0_TXADAPTSW_EN_BMSK                                                               0x20
#define HWIO_RXENGINE_EN0_TXADAPTSW_EN_SHFT                                                                0x5
#define HWIO_RXENGINE_EN0_DFE_EN_MODE2_BMSK                                                               0x10
#define HWIO_RXENGINE_EN0_DFE_EN_MODE2_SHFT                                                                0x4
#define HWIO_RXENGINE_EN0_DFE_EN_MODE1_BMSK                                                                0x8
#define HWIO_RXENGINE_EN0_DFE_EN_MODE1_SHFT                                                                0x3
#define HWIO_RXENGINE_EN0_DFE_EN_MODE0_BMSK                                                                0x4
#define HWIO_RXENGINE_EN0_DFE_EN_MODE0_SHFT                                                                0x2
#define HWIO_RXENGINE_EN0_RXEQ_GLB_ADAPT_MODE_BMSK                                                         0x3
#define HWIO_RXENGINE_EN0_RXEQ_GLB_ADAPT_MODE_SHFT                                                         0x0

#define HWIO_RXENGINE_EN1_ADDR(x)                                                                   ((x) + 0x0000010c)
#define HWIO_RXENGINE_EN1_RMSK                                                                            0x7f
#define HWIO_RXENGINE_EN1_IN(x)      \
        in_dword_masked(HWIO_RXENGINE_EN1_ADDR(x), HWIO_RXENGINE_EN1_RMSK)
#define HWIO_RXENGINE_EN1_INM(x, m)      \
        in_dword_masked(HWIO_RXENGINE_EN1_ADDR(x), m)
#define HWIO_RXENGINE_EN1_OUT(x, v)      \
        out_dword(HWIO_RXENGINE_EN1_ADDR(x),v)
#define HWIO_RXENGINE_EN1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RXENGINE_EN1_ADDR(x),m,v,HWIO_RXENGINE_EN1_IN(x))
#define HWIO_RXENGINE_EN1_DFE_TRACKING_EN_MUX_BMSK                                                        0x40
#define HWIO_RXENGINE_EN1_DFE_TRACKING_EN_MUX_SHFT                                                         0x6
#define HWIO_RXENGINE_EN1_DFE_TAP5_EN_BMSK                                                                0x20
#define HWIO_RXENGINE_EN1_DFE_TAP5_EN_SHFT                                                                 0x5
#define HWIO_RXENGINE_EN1_DFE_TAP4_EN_BMSK                                                                0x10
#define HWIO_RXENGINE_EN1_DFE_TAP4_EN_SHFT                                                                 0x4
#define HWIO_RXENGINE_EN1_DFE_TAP3_EN_BMSK                                                                 0x8
#define HWIO_RXENGINE_EN1_DFE_TAP3_EN_SHFT                                                                 0x3
#define HWIO_RXENGINE_EN1_DFE_TAP2_EN_BMSK                                                                 0x4
#define HWIO_RXENGINE_EN1_DFE_TAP2_EN_SHFT                                                                 0x2
#define HWIO_RXENGINE_EN1_DFE_TAP1_EN_BMSK                                                                 0x2
#define HWIO_RXENGINE_EN1_DFE_TAP1_EN_SHFT                                                                 0x1
#define HWIO_RXENGINE_EN1_VGA_ADAPT_EN_BMSK                                                                0x1
#define HWIO_RXENGINE_EN1_VGA_ADAPT_EN_SHFT                                                                0x0

#define HWIO_RXENGINE_EN2_ADDR(x)                                                                   ((x) + 0x00000110)
#define HWIO_RXENGINE_EN2_RMSK                                                                            0xff
#define HWIO_RXENGINE_EN2_IN(x)      \
        in_dword_masked(HWIO_RXENGINE_EN2_ADDR(x), HWIO_RXENGINE_EN2_RMSK)
#define HWIO_RXENGINE_EN2_INM(x, m)      \
        in_dword_masked(HWIO_RXENGINE_EN2_ADDR(x), m)
#define HWIO_RXENGINE_EN2_OUT(x, v)      \
        out_dword(HWIO_RXENGINE_EN2_ADDR(x),v)
#define HWIO_RXENGINE_EN2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RXENGINE_EN2_ADDR(x),m,v,HWIO_RXENGINE_EN2_IN(x))
#define HWIO_RXENGINE_EN2_FORCE_DFE_TAP_EN_BMSK                                                           0x80
#define HWIO_RXENGINE_EN2_FORCE_DFE_TAP_EN_SHFT                                                            0x7
#define HWIO_RXENGINE_EN2_DFE_TRAIN_EN_MUX_BMSK                                                           0x40
#define HWIO_RXENGINE_EN2_DFE_TRAIN_EN_MUX_SHFT                                                            0x6
#define HWIO_RXENGINE_EN2_DFE_TRAIN_EN_BMSK                                                               0x20
#define HWIO_RXENGINE_EN2_DFE_TRAIN_EN_SHFT                                                                0x5
#define HWIO_RXENGINE_EN2_EDAC_ADAPT_EN_BMSK                                                              0x10
#define HWIO_RXENGINE_EN2_EDAC_ADAPT_EN_SHFT                                                               0x4
#define HWIO_RXENGINE_EN2_PHPRE_ADAPT_EN_BMSK                                                              0x8
#define HWIO_RXENGINE_EN2_PHPRE_ADAPT_EN_SHFT                                                              0x3
#define HWIO_RXENGINE_EN2_AMPPRE_ADAPT_EN_BMSK                                                             0x4
#define HWIO_RXENGINE_EN2_AMPPRE_ADAPT_EN_SHFT                                                             0x2
#define HWIO_RXENGINE_EN2_OFFSET_ADAPT_EN_BMSK                                                             0x2
#define HWIO_RXENGINE_EN2_OFFSET_ADAPT_EN_SHFT                                                             0x1
#define HWIO_RXENGINE_EN2_EQ_ADAPT_EN_BMSK                                                                 0x1
#define HWIO_RXENGINE_EN2_EQ_ADAPT_EN_SHFT                                                                 0x0

#define HWIO_CTLE_TRAIN_TIME_ADDR(x)                                                                ((x) + 0x00000114)
#define HWIO_CTLE_TRAIN_TIME_RMSK                                                                         0x7f
#define HWIO_CTLE_TRAIN_TIME_IN(x)      \
        in_dword_masked(HWIO_CTLE_TRAIN_TIME_ADDR(x), HWIO_CTLE_TRAIN_TIME_RMSK)
#define HWIO_CTLE_TRAIN_TIME_INM(x, m)      \
        in_dword_masked(HWIO_CTLE_TRAIN_TIME_ADDR(x), m)
#define HWIO_CTLE_TRAIN_TIME_OUT(x, v)      \
        out_dword(HWIO_CTLE_TRAIN_TIME_ADDR(x),v)
#define HWIO_CTLE_TRAIN_TIME_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CTLE_TRAIN_TIME_ADDR(x),m,v,HWIO_CTLE_TRAIN_TIME_IN(x))
#define HWIO_CTLE_TRAIN_TIME_CTLE_TRAIN_TIME_BMSK                                                         0x7f
#define HWIO_CTLE_TRAIN_TIME_CTLE_TRAIN_TIME_SHFT                                                          0x0

#define HWIO_CTLE_DFE_OVRLP_TIME_ADDR(x)                                                            ((x) + 0x00000118)
#define HWIO_CTLE_DFE_OVRLP_TIME_RMSK                                                                     0xff
#define HWIO_CTLE_DFE_OVRLP_TIME_IN(x)      \
        in_dword_masked(HWIO_CTLE_DFE_OVRLP_TIME_ADDR(x), HWIO_CTLE_DFE_OVRLP_TIME_RMSK)
#define HWIO_CTLE_DFE_OVRLP_TIME_INM(x, m)      \
        in_dword_masked(HWIO_CTLE_DFE_OVRLP_TIME_ADDR(x), m)
#define HWIO_CTLE_DFE_OVRLP_TIME_OUT(x, v)      \
        out_dword(HWIO_CTLE_DFE_OVRLP_TIME_ADDR(x),v)
#define HWIO_CTLE_DFE_OVRLP_TIME_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CTLE_DFE_OVRLP_TIME_ADDR(x),m,v,HWIO_CTLE_DFE_OVRLP_TIME_IN(x))
#define HWIO_CTLE_DFE_OVRLP_TIME_CTLE_DFE_OVRLP_TIME_BMSK                                                 0xff
#define HWIO_CTLE_DFE_OVRLP_TIME_CTLE_DFE_OVRLP_TIME_SHFT                                                  0x0

#define HWIO_DFE_REFRESH_TIME_ADDR(x)                                                               ((x) + 0x0000011c)
#define HWIO_DFE_REFRESH_TIME_RMSK                                                                         0xf
#define HWIO_DFE_REFRESH_TIME_IN(x)      \
        in_dword_masked(HWIO_DFE_REFRESH_TIME_ADDR(x), HWIO_DFE_REFRESH_TIME_RMSK)
#define HWIO_DFE_REFRESH_TIME_INM(x, m)      \
        in_dword_masked(HWIO_DFE_REFRESH_TIME_ADDR(x), m)
#define HWIO_DFE_REFRESH_TIME_OUT(x, v)      \
        out_dword(HWIO_DFE_REFRESH_TIME_ADDR(x),v)
#define HWIO_DFE_REFRESH_TIME_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_REFRESH_TIME_ADDR(x),m,v,HWIO_DFE_REFRESH_TIME_IN(x))
#define HWIO_DFE_REFRESH_TIME_DFE_REFRESH_TIME_BMSK                                                        0xf
#define HWIO_DFE_REFRESH_TIME_DFE_REFRESH_TIME_SHFT                                                        0x0

#define HWIO_DFE_ENABLE_TIME_ADDR(x)                                                                ((x) + 0x00000120)
#define HWIO_DFE_ENABLE_TIME_RMSK                                                                         0xff
#define HWIO_DFE_ENABLE_TIME_IN(x)      \
        in_dword_masked(HWIO_DFE_ENABLE_TIME_ADDR(x), HWIO_DFE_ENABLE_TIME_RMSK)
#define HWIO_DFE_ENABLE_TIME_INM(x, m)      \
        in_dword_masked(HWIO_DFE_ENABLE_TIME_ADDR(x), m)
#define HWIO_DFE_ENABLE_TIME_OUT(x, v)      \
        out_dword(HWIO_DFE_ENABLE_TIME_ADDR(x),v)
#define HWIO_DFE_ENABLE_TIME_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_ENABLE_TIME_ADDR(x),m,v,HWIO_DFE_ENABLE_TIME_IN(x))
#define HWIO_DFE_ENABLE_TIME_DFE_ENABLE_TIME_BMSK                                                         0xff
#define HWIO_DFE_ENABLE_TIME_DFE_ENABLE_TIME_SHFT                                                          0x0

#define HWIO_VGA_GAIN_ADDR(x)                                                                       ((x) + 0x00000124)
#define HWIO_VGA_GAIN_RMSK                                                                                0xff
#define HWIO_VGA_GAIN_IN(x)      \
        in_dword_masked(HWIO_VGA_GAIN_ADDR(x), HWIO_VGA_GAIN_RMSK)
#define HWIO_VGA_GAIN_INM(x, m)      \
        in_dword_masked(HWIO_VGA_GAIN_ADDR(x), m)
#define HWIO_VGA_GAIN_OUT(x, v)      \
        out_dword(HWIO_VGA_GAIN_ADDR(x),v)
#define HWIO_VGA_GAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VGA_GAIN_ADDR(x),m,v,HWIO_VGA_GAIN_IN(x))
#define HWIO_VGA_GAIN_VGA_GAIN_TRACKING_BMSK                                                              0xf0
#define HWIO_VGA_GAIN_VGA_GAIN_TRACKING_SHFT                                                               0x4
#define HWIO_VGA_GAIN_VGA_GAIN_TRAINING_BMSK                                                               0xf
#define HWIO_VGA_GAIN_VGA_GAIN_TRAINING_SHFT                                                               0x0

#define HWIO_DFE_GAIN_ADDR(x)                                                                       ((x) + 0x00000128)
#define HWIO_DFE_GAIN_RMSK                                                                                0xff
#define HWIO_DFE_GAIN_IN(x)      \
        in_dword_masked(HWIO_DFE_GAIN_ADDR(x), HWIO_DFE_GAIN_RMSK)
#define HWIO_DFE_GAIN_INM(x, m)      \
        in_dword_masked(HWIO_DFE_GAIN_ADDR(x), m)
#define HWIO_DFE_GAIN_OUT(x, v)      \
        out_dword(HWIO_DFE_GAIN_ADDR(x),v)
#define HWIO_DFE_GAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_GAIN_ADDR(x),m,v,HWIO_DFE_GAIN_IN(x))
#define HWIO_DFE_GAIN_DFE_GAIN_TRACKING_BMSK                                                              0xf0
#define HWIO_DFE_GAIN_DFE_GAIN_TRACKING_SHFT                                                               0x4
#define HWIO_DFE_GAIN_DFE_GAIN_TRAINING_BMSK                                                               0xf
#define HWIO_DFE_GAIN_DFE_GAIN_TRAINING_SHFT                                                               0x0

#define HWIO_DFE_GAIN_SIGN_ADDR(x)                                                                  ((x) + 0x0000012c)
#define HWIO_DFE_GAIN_SIGN_RMSK                                                                           0x3f
#define HWIO_DFE_GAIN_SIGN_IN(x)      \
        in_dword_masked(HWIO_DFE_GAIN_SIGN_ADDR(x), HWIO_DFE_GAIN_SIGN_RMSK)
#define HWIO_DFE_GAIN_SIGN_INM(x, m)      \
        in_dword_masked(HWIO_DFE_GAIN_SIGN_ADDR(x), m)
#define HWIO_DFE_GAIN_SIGN_OUT(x, v)      \
        out_dword(HWIO_DFE_GAIN_SIGN_ADDR(x),v)
#define HWIO_DFE_GAIN_SIGN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_GAIN_SIGN_ADDR(x),m,v,HWIO_DFE_GAIN_SIGN_IN(x))
#define HWIO_DFE_GAIN_SIGN_VGA_GAIN_SIGN_BMSK                                                             0x20
#define HWIO_DFE_GAIN_SIGN_VGA_GAIN_SIGN_SHFT                                                              0x5
#define HWIO_DFE_GAIN_SIGN_DFE_TAP5_GAIN_SIGN_BMSK                                                        0x10
#define HWIO_DFE_GAIN_SIGN_DFE_TAP5_GAIN_SIGN_SHFT                                                         0x4
#define HWIO_DFE_GAIN_SIGN_DFE_TAP4_GAIN_SIGN_BMSK                                                         0x8
#define HWIO_DFE_GAIN_SIGN_DFE_TAP4_GAIN_SIGN_SHFT                                                         0x3
#define HWIO_DFE_GAIN_SIGN_DFE_TAP3_GAIN_SIGN_BMSK                                                         0x4
#define HWIO_DFE_GAIN_SIGN_DFE_TAP3_GAIN_SIGN_SHFT                                                         0x2
#define HWIO_DFE_GAIN_SIGN_DFE_TAP2_GAIN_SIGN_BMSK                                                         0x2
#define HWIO_DFE_GAIN_SIGN_DFE_TAP2_GAIN_SIGN_SHFT                                                         0x1
#define HWIO_DFE_GAIN_SIGN_DFE_TAP1_GAIN_SIGN_BMSK                                                         0x1
#define HWIO_DFE_GAIN_SIGN_DFE_TAP1_GAIN_SIGN_SHFT                                                         0x0

#define HWIO_EQ_GAIN_ADDR(x)                                                                        ((x) + 0x00000130)
#define HWIO_EQ_GAIN_RMSK                                                                                 0x1f
#define HWIO_EQ_GAIN_IN(x)      \
        in_dword_masked(HWIO_EQ_GAIN_ADDR(x), HWIO_EQ_GAIN_RMSK)
#define HWIO_EQ_GAIN_INM(x, m)      \
        in_dword_masked(HWIO_EQ_GAIN_ADDR(x), m)
#define HWIO_EQ_GAIN_OUT(x, v)      \
        out_dword(HWIO_EQ_GAIN_ADDR(x),v)
#define HWIO_EQ_GAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EQ_GAIN_ADDR(x),m,v,HWIO_EQ_GAIN_IN(x))
#define HWIO_EQ_GAIN_EQ_GAIN_SIGN_BMSK                                                                    0x10
#define HWIO_EQ_GAIN_EQ_GAIN_SIGN_SHFT                                                                     0x4
#define HWIO_EQ_GAIN_EQ_GAIN_BMSK                                                                          0xf
#define HWIO_EQ_GAIN_EQ_GAIN_SHFT                                                                          0x0

#define HWIO_OFFSET_GAIN_ADDR(x)                                                                    ((x) + 0x00000134)
#define HWIO_OFFSET_GAIN_RMSK                                                                             0x1f
#define HWIO_OFFSET_GAIN_IN(x)      \
        in_dword_masked(HWIO_OFFSET_GAIN_ADDR(x), HWIO_OFFSET_GAIN_RMSK)
#define HWIO_OFFSET_GAIN_INM(x, m)      \
        in_dword_masked(HWIO_OFFSET_GAIN_ADDR(x), m)
#define HWIO_OFFSET_GAIN_OUT(x, v)      \
        out_dword(HWIO_OFFSET_GAIN_ADDR(x),v)
#define HWIO_OFFSET_GAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_OFFSET_GAIN_ADDR(x),m,v,HWIO_OFFSET_GAIN_IN(x))
#define HWIO_OFFSET_GAIN_OFFSET_GAIN_SIGN_BMSK                                                            0x10
#define HWIO_OFFSET_GAIN_OFFSET_GAIN_SIGN_SHFT                                                             0x4
#define HWIO_OFFSET_GAIN_OFFSET_GAIN_BMSK                                                                  0xf
#define HWIO_OFFSET_GAIN_OFFSET_GAIN_SHFT                                                                  0x0

#define HWIO_PRE_GAIN_ADDR(x)                                                                       ((x) + 0x00000138)
#define HWIO_PRE_GAIN_RMSK                                                                                0x1f
#define HWIO_PRE_GAIN_IN(x)      \
        in_dword_masked(HWIO_PRE_GAIN_ADDR(x), HWIO_PRE_GAIN_RMSK)
#define HWIO_PRE_GAIN_INM(x, m)      \
        in_dword_masked(HWIO_PRE_GAIN_ADDR(x), m)
#define HWIO_PRE_GAIN_OUT(x, v)      \
        out_dword(HWIO_PRE_GAIN_ADDR(x),v)
#define HWIO_PRE_GAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PRE_GAIN_ADDR(x),m,v,HWIO_PRE_GAIN_IN(x))
#define HWIO_PRE_GAIN_PRE_GAIN_SIGN_BMSK                                                                  0x10
#define HWIO_PRE_GAIN_PRE_GAIN_SIGN_SHFT                                                                   0x4
#define HWIO_PRE_GAIN_PRE_GAIN_BMSK                                                                        0xf
#define HWIO_PRE_GAIN_PRE_GAIN_SHFT                                                                        0x0

#define HWIO_VGA_INITVAL_ADDR(x)                                                                    ((x) + 0x0000013c)
#define HWIO_VGA_INITVAL_RMSK                                                                             0x3f
#define HWIO_VGA_INITVAL_IN(x)      \
        in_dword_masked(HWIO_VGA_INITVAL_ADDR(x), HWIO_VGA_INITVAL_RMSK)
#define HWIO_VGA_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_VGA_INITVAL_ADDR(x), m)
#define HWIO_VGA_INITVAL_OUT(x, v)      \
        out_dword(HWIO_VGA_INITVAL_ADDR(x),v)
#define HWIO_VGA_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VGA_INITVAL_ADDR(x),m,v,HWIO_VGA_INITVAL_IN(x))
#define HWIO_VGA_INITVAL_VGA_INITVAL_BMSK                                                                 0x3f
#define HWIO_VGA_INITVAL_VGA_INITVAL_SHFT                                                                  0x0

#define HWIO_DFE_TAP1_INITVAL_ADDR(x)                                                               ((x) + 0x00000140)
#define HWIO_DFE_TAP1_INITVAL_RMSK                                                                        0x7f
#define HWIO_DFE_TAP1_INITVAL_IN(x)      \
        in_dword_masked(HWIO_DFE_TAP1_INITVAL_ADDR(x), HWIO_DFE_TAP1_INITVAL_RMSK)
#define HWIO_DFE_TAP1_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_DFE_TAP1_INITVAL_ADDR(x), m)
#define HWIO_DFE_TAP1_INITVAL_OUT(x, v)      \
        out_dword(HWIO_DFE_TAP1_INITVAL_ADDR(x),v)
#define HWIO_DFE_TAP1_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_TAP1_INITVAL_ADDR(x),m,v,HWIO_DFE_TAP1_INITVAL_IN(x))
#define HWIO_DFE_TAP1_INITVAL_DFE_TAP1_INITVAL_BMSK                                                       0x7f
#define HWIO_DFE_TAP1_INITVAL_DFE_TAP1_INITVAL_SHFT                                                        0x0

#define HWIO_DFE_TAP2_INITVAL_ADDR(x)                                                               ((x) + 0x00000144)
#define HWIO_DFE_TAP2_INITVAL_RMSK                                                                        0x3f
#define HWIO_DFE_TAP2_INITVAL_IN(x)      \
        in_dword_masked(HWIO_DFE_TAP2_INITVAL_ADDR(x), HWIO_DFE_TAP2_INITVAL_RMSK)
#define HWIO_DFE_TAP2_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_DFE_TAP2_INITVAL_ADDR(x), m)
#define HWIO_DFE_TAP2_INITVAL_OUT(x, v)      \
        out_dword(HWIO_DFE_TAP2_INITVAL_ADDR(x),v)
#define HWIO_DFE_TAP2_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_TAP2_INITVAL_ADDR(x),m,v,HWIO_DFE_TAP2_INITVAL_IN(x))
#define HWIO_DFE_TAP2_INITVAL_DFE_TAP2_INITVAL_BMSK                                                       0x3f
#define HWIO_DFE_TAP2_INITVAL_DFE_TAP2_INITVAL_SHFT                                                        0x0

#define HWIO_DFE_TAP3_INITVAL_ADDR(x)                                                               ((x) + 0x00000148)
#define HWIO_DFE_TAP3_INITVAL_RMSK                                                                        0x3f
#define HWIO_DFE_TAP3_INITVAL_IN(x)      \
        in_dword_masked(HWIO_DFE_TAP3_INITVAL_ADDR(x), HWIO_DFE_TAP3_INITVAL_RMSK)
#define HWIO_DFE_TAP3_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_DFE_TAP3_INITVAL_ADDR(x), m)
#define HWIO_DFE_TAP3_INITVAL_OUT(x, v)      \
        out_dword(HWIO_DFE_TAP3_INITVAL_ADDR(x),v)
#define HWIO_DFE_TAP3_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_TAP3_INITVAL_ADDR(x),m,v,HWIO_DFE_TAP3_INITVAL_IN(x))
#define HWIO_DFE_TAP3_INITVAL_DFE_TAP3_INITVAL_BMSK                                                       0x3f
#define HWIO_DFE_TAP3_INITVAL_DFE_TAP3_INITVAL_SHFT                                                        0x0

#define HWIO_DFE_TAP4_INITVAL_ADDR(x)                                                               ((x) + 0x0000014c)
#define HWIO_DFE_TAP4_INITVAL_RMSK                                                                        0x3f
#define HWIO_DFE_TAP4_INITVAL_IN(x)      \
        in_dword_masked(HWIO_DFE_TAP4_INITVAL_ADDR(x), HWIO_DFE_TAP4_INITVAL_RMSK)
#define HWIO_DFE_TAP4_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_DFE_TAP4_INITVAL_ADDR(x), m)
#define HWIO_DFE_TAP4_INITVAL_OUT(x, v)      \
        out_dword(HWIO_DFE_TAP4_INITVAL_ADDR(x),v)
#define HWIO_DFE_TAP4_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_TAP4_INITVAL_ADDR(x),m,v,HWIO_DFE_TAP4_INITVAL_IN(x))
#define HWIO_DFE_TAP4_INITVAL_DFE_TAP4_INITVAL_BMSK                                                       0x3f
#define HWIO_DFE_TAP4_INITVAL_DFE_TAP4_INITVAL_SHFT                                                        0x0

#define HWIO_DFE_TAP5_INITVAL_ADDR(x)                                                               ((x) + 0x00000150)
#define HWIO_DFE_TAP5_INITVAL_RMSK                                                                        0x3f
#define HWIO_DFE_TAP5_INITVAL_IN(x)      \
        in_dword_masked(HWIO_DFE_TAP5_INITVAL_ADDR(x), HWIO_DFE_TAP5_INITVAL_RMSK)
#define HWIO_DFE_TAP5_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_DFE_TAP5_INITVAL_ADDR(x), m)
#define HWIO_DFE_TAP5_INITVAL_OUT(x, v)      \
        out_dword(HWIO_DFE_TAP5_INITVAL_ADDR(x),v)
#define HWIO_DFE_TAP5_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DFE_TAP5_INITVAL_ADDR(x),m,v,HWIO_DFE_TAP5_INITVAL_IN(x))
#define HWIO_DFE_TAP5_INITVAL_DFE_TAP5_INITVAL_BMSK                                                       0x3f
#define HWIO_DFE_TAP5_INITVAL_DFE_TAP5_INITVAL_SHFT                                                        0x0

#define HWIO_EQ_INITVAL_ADDR(x)                                                                     ((x) + 0x00000154)
#define HWIO_EQ_INITVAL_RMSK                                                                              0x3f
#define HWIO_EQ_INITVAL_IN(x)      \
        in_dword_masked(HWIO_EQ_INITVAL_ADDR(x), HWIO_EQ_INITVAL_RMSK)
#define HWIO_EQ_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_EQ_INITVAL_ADDR(x), m)
#define HWIO_EQ_INITVAL_OUT(x, v)      \
        out_dword(HWIO_EQ_INITVAL_ADDR(x),v)
#define HWIO_EQ_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EQ_INITVAL_ADDR(x),m,v,HWIO_EQ_INITVAL_IN(x))
#define HWIO_EQ_INITVAL_EQ_INITVAL_BMSK                                                                   0x3f
#define HWIO_EQ_INITVAL_EQ_INITVAL_SHFT                                                                    0x0

#define HWIO_OFFSET_INITVAL_ADDR(x)                                                                 ((x) + 0x00000158)
#define HWIO_OFFSET_INITVAL_RMSK                                                                          0x3f
#define HWIO_OFFSET_INITVAL_IN(x)      \
        in_dword_masked(HWIO_OFFSET_INITVAL_ADDR(x), HWIO_OFFSET_INITVAL_RMSK)
#define HWIO_OFFSET_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_OFFSET_INITVAL_ADDR(x), m)
#define HWIO_OFFSET_INITVAL_OUT(x, v)      \
        out_dword(HWIO_OFFSET_INITVAL_ADDR(x),v)
#define HWIO_OFFSET_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_OFFSET_INITVAL_ADDR(x),m,v,HWIO_OFFSET_INITVAL_IN(x))
#define HWIO_OFFSET_INITVAL_OFFSET_INITVAL_BMSK                                                           0x3f
#define HWIO_OFFSET_INITVAL_OFFSET_INITVAL_SHFT                                                            0x0

#define HWIO_PRE_INITVAL_ADDR(x)                                                                    ((x) + 0x0000015c)
#define HWIO_PRE_INITVAL_RMSK                                                                             0x3f
#define HWIO_PRE_INITVAL_IN(x)      \
        in_dword_masked(HWIO_PRE_INITVAL_ADDR(x), HWIO_PRE_INITVAL_RMSK)
#define HWIO_PRE_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_PRE_INITVAL_ADDR(x), m)
#define HWIO_PRE_INITVAL_OUT(x, v)      \
        out_dword(HWIO_PRE_INITVAL_ADDR(x),v)
#define HWIO_PRE_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PRE_INITVAL_ADDR(x),m,v,HWIO_PRE_INITVAL_IN(x))
#define HWIO_PRE_INITVAL_PRE_INITVAL_BMSK                                                                 0x3f
#define HWIO_PRE_INITVAL_PRE_INITVAL_SHFT                                                                  0x0

#define HWIO_EDAC_INITVAL_ADDR(x)                                                                   ((x) + 0x00000160)
#define HWIO_EDAC_INITVAL_RMSK                                                                            0x7f
#define HWIO_EDAC_INITVAL_IN(x)      \
        in_dword_masked(HWIO_EDAC_INITVAL_ADDR(x), HWIO_EDAC_INITVAL_RMSK)
#define HWIO_EDAC_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_EDAC_INITVAL_ADDR(x), m)
#define HWIO_EDAC_INITVAL_OUT(x, v)      \
        out_dword(HWIO_EDAC_INITVAL_ADDR(x),v)
#define HWIO_EDAC_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EDAC_INITVAL_ADDR(x),m,v,HWIO_EDAC_INITVAL_IN(x))
#define HWIO_EDAC_INITVAL_EDAC_INITVAL_BMSK                                                               0x7f
#define HWIO_EDAC_INITVAL_EDAC_INITVAL_SHFT                                                                0x0

#define HWIO_CTLE_SATVAL_ADDR(x)                                                                    ((x) + 0x00000164)
#define HWIO_CTLE_SATVAL_RMSK                                                                             0x3f
#define HWIO_CTLE_SATVAL_IN(x)      \
        in_dword_masked(HWIO_CTLE_SATVAL_ADDR(x), HWIO_CTLE_SATVAL_RMSK)
#define HWIO_CTLE_SATVAL_INM(x, m)      \
        in_dword_masked(HWIO_CTLE_SATVAL_ADDR(x), m)
#define HWIO_CTLE_SATVAL_OUT(x, v)      \
        out_dword(HWIO_CTLE_SATVAL_ADDR(x),v)
#define HWIO_CTLE_SATVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CTLE_SATVAL_ADDR(x),m,v,HWIO_CTLE_SATVAL_IN(x))
#define HWIO_CTLE_SATVAL_SATVAL_EQ_BMSK                                                                   0x3f
#define HWIO_CTLE_SATVAL_SATVAL_EQ_SHFT                                                                    0x0

#define HWIO_RXEQ_INITB0_ADDR(x)                                                                    ((x) + 0x00000168)
#define HWIO_RXEQ_INITB0_RMSK                                                                             0x7f
#define HWIO_RXEQ_INITB0_IN(x)      \
        in_dword_masked(HWIO_RXEQ_INITB0_ADDR(x), HWIO_RXEQ_INITB0_RMSK)
#define HWIO_RXEQ_INITB0_INM(x, m)      \
        in_dword_masked(HWIO_RXEQ_INITB0_ADDR(x), m)
#define HWIO_RXEQ_INITB0_OUT(x, v)      \
        out_dword(HWIO_RXEQ_INITB0_ADDR(x),v)
#define HWIO_RXEQ_INITB0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RXEQ_INITB0_ADDR(x),m,v,HWIO_RXEQ_INITB0_IN(x))
#define HWIO_RXEQ_INITB0_OFFSET_INITB_BMSK                                                                0x40
#define HWIO_RXEQ_INITB0_OFFSET_INITB_SHFT                                                                 0x6
#define HWIO_RXEQ_INITB0_EQ_INITB_BMSK                                                                    0x20
#define HWIO_RXEQ_INITB0_EQ_INITB_SHFT                                                                     0x5
#define HWIO_RXEQ_INITB0_DFE_TAP5_INITB_BMSK                                                              0x10
#define HWIO_RXEQ_INITB0_DFE_TAP5_INITB_SHFT                                                               0x4
#define HWIO_RXEQ_INITB0_DFE_TAP4_INITB_BMSK                                                               0x8
#define HWIO_RXEQ_INITB0_DFE_TAP4_INITB_SHFT                                                               0x3
#define HWIO_RXEQ_INITB0_DFE_TAP3_INITB_BMSK                                                               0x4
#define HWIO_RXEQ_INITB0_DFE_TAP3_INITB_SHFT                                                               0x2
#define HWIO_RXEQ_INITB0_DFE_TAP2_INITB_BMSK                                                               0x2
#define HWIO_RXEQ_INITB0_DFE_TAP2_INITB_SHFT                                                               0x1
#define HWIO_RXEQ_INITB0_DFE_TAP1_INITB_BMSK                                                               0x1
#define HWIO_RXEQ_INITB0_DFE_TAP1_INITB_SHFT                                                               0x0

#define HWIO_RXEQ_INITB1_ADDR(x)                                                                    ((x) + 0x0000016c)
#define HWIO_RXEQ_INITB1_RMSK                                                                             0xff
#define HWIO_RXEQ_INITB1_IN(x)      \
        in_dword_masked(HWIO_RXEQ_INITB1_ADDR(x), HWIO_RXEQ_INITB1_RMSK)
#define HWIO_RXEQ_INITB1_INM(x, m)      \
        in_dword_masked(HWIO_RXEQ_INITB1_ADDR(x), m)
#define HWIO_RXEQ_INITB1_OUT(x, v)      \
        out_dword(HWIO_RXEQ_INITB1_ADDR(x),v)
#define HWIO_RXEQ_INITB1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RXEQ_INITB1_ADDR(x),m,v,HWIO_RXEQ_INITB1_IN(x))
#define HWIO_RXEQ_INITB1_RXEQ_CTRL_MODE_BMSK                                                              0xf0
#define HWIO_RXEQ_INITB1_RXEQ_CTRL_MODE_SHFT                                                               0x4
#define HWIO_RXEQ_INITB1_INITB_VGA_CTLE_EDAC_MUX_BMSK                                                      0x8
#define HWIO_RXEQ_INITB1_INITB_VGA_CTLE_EDAC_MUX_SHFT                                                      0x3
#define HWIO_RXEQ_INITB1_INITB_VGA_CTLE_EDAC_BMSK                                                          0x4
#define HWIO_RXEQ_INITB1_INITB_VGA_CTLE_EDAC_SHFT                                                          0x2
#define HWIO_RXEQ_INITB1_PHPRE_INITB_BMSK                                                                  0x2
#define HWIO_RXEQ_INITB1_PHPRE_INITB_SHFT                                                                  0x1
#define HWIO_RXEQ_INITB1_AMPPRE_INITB_BMSK                                                                 0x1
#define HWIO_RXEQ_INITB1_AMPPRE_INITB_SHFT                                                                 0x0

#define HWIO_RXEQ_CLK_DIV1_ADDR(x)                                                                  ((x) + 0x00000170)
#define HWIO_RXEQ_CLK_DIV1_RMSK                                                                           0xff
#define HWIO_RXEQ_CLK_DIV1_IN(x)      \
        in_dword_masked(HWIO_RXEQ_CLK_DIV1_ADDR(x), HWIO_RXEQ_CLK_DIV1_RMSK)
#define HWIO_RXEQ_CLK_DIV1_INM(x, m)      \
        in_dword_masked(HWIO_RXEQ_CLK_DIV1_ADDR(x), m)
#define HWIO_RXEQ_CLK_DIV1_OUT(x, v)      \
        out_dword(HWIO_RXEQ_CLK_DIV1_ADDR(x),v)
#define HWIO_RXEQ_CLK_DIV1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RXEQ_CLK_DIV1_ADDR(x),m,v,HWIO_RXEQ_CLK_DIV1_IN(x))
#define HWIO_RXEQ_CLK_DIV1_RXEQ_CLK_DIV_7_0_BMSK                                                          0xff
#define HWIO_RXEQ_CLK_DIV1_RXEQ_CLK_DIV_7_0_SHFT                                                           0x0

#define HWIO_RXEQ_CLK_DIV2_ADDR(x)                                                                  ((x) + 0x00000174)
#define HWIO_RXEQ_CLK_DIV2_RMSK                                                                            0x3
#define HWIO_RXEQ_CLK_DIV2_IN(x)      \
        in_dword_masked(HWIO_RXEQ_CLK_DIV2_ADDR(x), HWIO_RXEQ_CLK_DIV2_RMSK)
#define HWIO_RXEQ_CLK_DIV2_INM(x, m)      \
        in_dword_masked(HWIO_RXEQ_CLK_DIV2_ADDR(x), m)
#define HWIO_RXEQ_CLK_DIV2_OUT(x, v)      \
        out_dword(HWIO_RXEQ_CLK_DIV2_ADDR(x),v)
#define HWIO_RXEQ_CLK_DIV2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RXEQ_CLK_DIV2_ADDR(x),m,v,HWIO_RXEQ_CLK_DIV2_IN(x))
#define HWIO_RXEQ_CLK_DIV2_RXEQ_CLK_DIV_9_8_BMSK                                                           0x3
#define HWIO_RXEQ_CLK_DIV2_RXEQ_CLK_DIV_9_8_SHFT                                                           0x0

#define HWIO_RCVRDONE_THRESH1_ADDR(x)                                                               ((x) + 0x00000178)
#define HWIO_RCVRDONE_THRESH1_RMSK                                                                        0xff
#define HWIO_RCVRDONE_THRESH1_IN(x)      \
        in_dword_masked(HWIO_RCVRDONE_THRESH1_ADDR(x), HWIO_RCVRDONE_THRESH1_RMSK)
#define HWIO_RCVRDONE_THRESH1_INM(x, m)      \
        in_dword_masked(HWIO_RCVRDONE_THRESH1_ADDR(x), m)
#define HWIO_RCVRDONE_THRESH1_OUT(x, v)      \
        out_dword(HWIO_RCVRDONE_THRESH1_ADDR(x),v)
#define HWIO_RCVRDONE_THRESH1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RCVRDONE_THRESH1_ADDR(x),m,v,HWIO_RCVRDONE_THRESH1_IN(x))
#define HWIO_RCVRDONE_THRESH1_RCVRDONE_THRESH_7_0_BMSK                                                    0xff
#define HWIO_RCVRDONE_THRESH1_RCVRDONE_THRESH_7_0_SHFT                                                     0x0

#define HWIO_RCVRDONE_THRESH2_ADDR(x)                                                               ((x) + 0x0000017c)
#define HWIO_RCVRDONE_THRESH2_RMSK                                                                        0x7f
#define HWIO_RCVRDONE_THRESH2_IN(x)      \
        in_dword_masked(HWIO_RCVRDONE_THRESH2_ADDR(x), HWIO_RCVRDONE_THRESH2_RMSK)
#define HWIO_RCVRDONE_THRESH2_INM(x, m)      \
        in_dword_masked(HWIO_RCVRDONE_THRESH2_ADDR(x), m)
#define HWIO_RCVRDONE_THRESH2_OUT(x, v)      \
        out_dword(HWIO_RCVRDONE_THRESH2_ADDR(x),v)
#define HWIO_RCVRDONE_THRESH2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RCVRDONE_THRESH2_ADDR(x),m,v,HWIO_RCVRDONE_THRESH2_IN(x))
#define HWIO_RCVRDONE_THRESH2_RCVRDONE_THRESH_14_8_BMSK                                                   0x7f
#define HWIO_RCVRDONE_THRESH2_RCVRDONE_THRESH_14_8_SHFT                                                    0x0

#define HWIO_RXEQ_CTRL_ADDR(x)                                                                      ((x) + 0x00000180)
#define HWIO_RXEQ_CTRL_RMSK                                                                               0xff
#define HWIO_RXEQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_RXEQ_CTRL_ADDR(x), HWIO_RXEQ_CTRL_RMSK)
#define HWIO_RXEQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_RXEQ_CTRL_ADDR(x), m)
#define HWIO_RXEQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_RXEQ_CTRL_ADDR(x),v)
#define HWIO_RXEQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RXEQ_CTRL_ADDR(x),m,v,HWIO_RXEQ_CTRL_IN(x))
#define HWIO_RXEQ_CTRL_DISABLE_OFFSET_TRACKING_BMSK                                                       0x80
#define HWIO_RXEQ_CTRL_DISABLE_OFFSET_TRACKING_SHFT                                                        0x7
#define HWIO_RXEQ_CTRL_VGA_TRACKING_EN_BMSK                                                               0x40
#define HWIO_RXEQ_CTRL_VGA_TRACKING_EN_SHFT                                                                0x6
#define HWIO_RXEQ_CTRL_SEQ_TRACK_DFE_BMSK                                                                 0x20
#define HWIO_RXEQ_CTRL_SEQ_TRACK_DFE_SHFT                                                                  0x5
#define HWIO_RXEQ_CTRL_RCVRDONE_DISABLE_BMSK                                                              0x10
#define HWIO_RXEQ_CTRL_RCVRDONE_DISABLE_SHFT                                                               0x4
#define HWIO_RXEQ_CTRL_RCVRDONE_FORCEBIT_BMSK                                                              0x8
#define HWIO_RXEQ_CTRL_RCVRDONE_FORCEBIT_SHFT                                                              0x3
#define HWIO_RXEQ_CTRL_BYPASS_ADAPTATION_DONE_BMSK                                                         0x4
#define HWIO_RXEQ_CTRL_BYPASS_ADAPTATION_DONE_SHFT                                                         0x2
#define HWIO_RXEQ_CTRL_EQ_SEL_BMSK                                                                         0x2
#define HWIO_RXEQ_CTRL_EQ_SEL_SHFT                                                                         0x1
#define HWIO_RXEQ_CTRL_PRE_SEL_BMSK                                                                        0x1
#define HWIO_RXEQ_CTRL_PRE_SEL_SHFT                                                                        0x0

#define HWIO_UCDR_FO_GAIN_MODE0_ADDR(x)                                                             ((x) + 0x00000184)
#define HWIO_UCDR_FO_GAIN_MODE0_RMSK                                                                      0xff
#define HWIO_UCDR_FO_GAIN_MODE0_IN(x)      \
        in_dword_masked(HWIO_UCDR_FO_GAIN_MODE0_ADDR(x), HWIO_UCDR_FO_GAIN_MODE0_RMSK)
#define HWIO_UCDR_FO_GAIN_MODE0_INM(x, m)      \
        in_dword_masked(HWIO_UCDR_FO_GAIN_MODE0_ADDR(x), m)
#define HWIO_UCDR_FO_GAIN_MODE0_OUT(x, v)      \
        out_dword(HWIO_UCDR_FO_GAIN_MODE0_ADDR(x),v)
#define HWIO_UCDR_FO_GAIN_MODE0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UCDR_FO_GAIN_MODE0_ADDR(x),m,v,HWIO_UCDR_FO_GAIN_MODE0_IN(x))
#define HWIO_UCDR_FO_GAIN_MODE0_UCDR_STEP_BY_TWO_MODE0_BMSK                                               0x80
#define HWIO_UCDR_FO_GAIN_MODE0_UCDR_STEP_BY_TWO_MODE0_SHFT                                                0x7
#define HWIO_UCDR_FO_GAIN_MODE0_UCDR_FO_GAIN_MODE0_BMSK                                                   0x7f
#define HWIO_UCDR_FO_GAIN_MODE0_UCDR_FO_GAIN_MODE0_SHFT                                                    0x0

#define HWIO_UCDR_FO_GAIN_MODE1_ADDR(x)                                                             ((x) + 0x00000188)
#define HWIO_UCDR_FO_GAIN_MODE1_RMSK                                                                      0xff
#define HWIO_UCDR_FO_GAIN_MODE1_IN(x)      \
        in_dword_masked(HWIO_UCDR_FO_GAIN_MODE1_ADDR(x), HWIO_UCDR_FO_GAIN_MODE1_RMSK)
#define HWIO_UCDR_FO_GAIN_MODE1_INM(x, m)      \
        in_dword_masked(HWIO_UCDR_FO_GAIN_MODE1_ADDR(x), m)
#define HWIO_UCDR_FO_GAIN_MODE1_OUT(x, v)      \
        out_dword(HWIO_UCDR_FO_GAIN_MODE1_ADDR(x),v)
#define HWIO_UCDR_FO_GAIN_MODE1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UCDR_FO_GAIN_MODE1_ADDR(x),m,v,HWIO_UCDR_FO_GAIN_MODE1_IN(x))
#define HWIO_UCDR_FO_GAIN_MODE1_UCDR_STEP_BY_TWO_MODE1_BMSK                                               0x80
#define HWIO_UCDR_FO_GAIN_MODE1_UCDR_STEP_BY_TWO_MODE1_SHFT                                                0x7
#define HWIO_UCDR_FO_GAIN_MODE1_UCDR_FO_GAIN_MODE1_BMSK                                                   0x7f
#define HWIO_UCDR_FO_GAIN_MODE1_UCDR_FO_GAIN_MODE1_SHFT                                                    0x0

#define HWIO_UCDR_FO_GAIN_MODE2_ADDR(x)                                                             ((x) + 0x0000018c)
#define HWIO_UCDR_FO_GAIN_MODE2_RMSK                                                                      0xff
#define HWIO_UCDR_FO_GAIN_MODE2_IN(x)      \
        in_dword_masked(HWIO_UCDR_FO_GAIN_MODE2_ADDR(x), HWIO_UCDR_FO_GAIN_MODE2_RMSK)
#define HWIO_UCDR_FO_GAIN_MODE2_INM(x, m)      \
        in_dword_masked(HWIO_UCDR_FO_GAIN_MODE2_ADDR(x), m)
#define HWIO_UCDR_FO_GAIN_MODE2_OUT(x, v)      \
        out_dword(HWIO_UCDR_FO_GAIN_MODE2_ADDR(x),v)
#define HWIO_UCDR_FO_GAIN_MODE2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UCDR_FO_GAIN_MODE2_ADDR(x),m,v,HWIO_UCDR_FO_GAIN_MODE2_IN(x))
#define HWIO_UCDR_FO_GAIN_MODE2_UCDR_STEP_BY_TWO_MODE2_BMSK                                               0x80
#define HWIO_UCDR_FO_GAIN_MODE2_UCDR_STEP_BY_TWO_MODE2_SHFT                                                0x7
#define HWIO_UCDR_FO_GAIN_MODE2_UCDR_FO_GAIN_MODE2_BMSK                                                   0x7f
#define HWIO_UCDR_FO_GAIN_MODE2_UCDR_FO_GAIN_MODE2_SHFT                                                    0x0

#define HWIO_UCDR_SO_GAIN_MODE0_ADDR(x)                                                             ((x) + 0x00000190)
#define HWIO_UCDR_SO_GAIN_MODE0_RMSK                                                                      0x7f
#define HWIO_UCDR_SO_GAIN_MODE0_IN(x)      \
        in_dword_masked(HWIO_UCDR_SO_GAIN_MODE0_ADDR(x), HWIO_UCDR_SO_GAIN_MODE0_RMSK)
#define HWIO_UCDR_SO_GAIN_MODE0_INM(x, m)      \
        in_dword_masked(HWIO_UCDR_SO_GAIN_MODE0_ADDR(x), m)
#define HWIO_UCDR_SO_GAIN_MODE0_OUT(x, v)      \
        out_dword(HWIO_UCDR_SO_GAIN_MODE0_ADDR(x),v)
#define HWIO_UCDR_SO_GAIN_MODE0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UCDR_SO_GAIN_MODE0_ADDR(x),m,v,HWIO_UCDR_SO_GAIN_MODE0_IN(x))
#define HWIO_UCDR_SO_GAIN_MODE0_UCDR_SO_GAIN_MODE0_BMSK                                                   0x7f
#define HWIO_UCDR_SO_GAIN_MODE0_UCDR_SO_GAIN_MODE0_SHFT                                                    0x0

#define HWIO_UCDR_SO_GAIN_MODE1_ADDR(x)                                                             ((x) + 0x00000194)
#define HWIO_UCDR_SO_GAIN_MODE1_RMSK                                                                      0x7f
#define HWIO_UCDR_SO_GAIN_MODE1_IN(x)      \
        in_dword_masked(HWIO_UCDR_SO_GAIN_MODE1_ADDR(x), HWIO_UCDR_SO_GAIN_MODE1_RMSK)
#define HWIO_UCDR_SO_GAIN_MODE1_INM(x, m)      \
        in_dword_masked(HWIO_UCDR_SO_GAIN_MODE1_ADDR(x), m)
#define HWIO_UCDR_SO_GAIN_MODE1_OUT(x, v)      \
        out_dword(HWIO_UCDR_SO_GAIN_MODE1_ADDR(x),v)
#define HWIO_UCDR_SO_GAIN_MODE1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UCDR_SO_GAIN_MODE1_ADDR(x),m,v,HWIO_UCDR_SO_GAIN_MODE1_IN(x))
#define HWIO_UCDR_SO_GAIN_MODE1_UCDR_SO_GAIN_MODE1_BMSK                                                   0x7f
#define HWIO_UCDR_SO_GAIN_MODE1_UCDR_SO_GAIN_MODE1_SHFT                                                    0x0

#define HWIO_UCDR_SO_GAIN_MODE2_ADDR(x)                                                             ((x) + 0x00000198)
#define HWIO_UCDR_SO_GAIN_MODE2_RMSK                                                                      0x7f
#define HWIO_UCDR_SO_GAIN_MODE2_IN(x)      \
        in_dword_masked(HWIO_UCDR_SO_GAIN_MODE2_ADDR(x), HWIO_UCDR_SO_GAIN_MODE2_RMSK)
#define HWIO_UCDR_SO_GAIN_MODE2_INM(x, m)      \
        in_dword_masked(HWIO_UCDR_SO_GAIN_MODE2_ADDR(x), m)
#define HWIO_UCDR_SO_GAIN_MODE2_OUT(x, v)      \
        out_dword(HWIO_UCDR_SO_GAIN_MODE2_ADDR(x),v)
#define HWIO_UCDR_SO_GAIN_MODE2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UCDR_SO_GAIN_MODE2_ADDR(x),m,v,HWIO_UCDR_SO_GAIN_MODE2_IN(x))
#define HWIO_UCDR_SO_GAIN_MODE2_UCDR_SO_GAIN_MODE2_BMSK                                                   0x7f
#define HWIO_UCDR_SO_GAIN_MODE2_UCDR_SO_GAIN_MODE2_SHFT                                                    0x0

#define HWIO_UCDR_SO_CONFIG_ADDR(x)                                                                 ((x) + 0x0000019c)
#define HWIO_UCDR_SO_CONFIG_RMSK                                                                          0xff
#define HWIO_UCDR_SO_CONFIG_IN(x)      \
        in_dword_masked(HWIO_UCDR_SO_CONFIG_ADDR(x), HWIO_UCDR_SO_CONFIG_RMSK)
#define HWIO_UCDR_SO_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_UCDR_SO_CONFIG_ADDR(x), m)
#define HWIO_UCDR_SO_CONFIG_OUT(x, v)      \
        out_dword(HWIO_UCDR_SO_CONFIG_ADDR(x),v)
#define HWIO_UCDR_SO_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UCDR_SO_CONFIG_ADDR(x),m,v,HWIO_UCDR_SO_CONFIG_IN(x))
#define HWIO_UCDR_SO_CONFIG_UCDR_ENABLE_MUX_BMSK                                                          0x80
#define HWIO_UCDR_SO_CONFIG_UCDR_ENABLE_MUX_SHFT                                                           0x7
#define HWIO_UCDR_SO_CONFIG_UCDR_ENABLE_BMSK                                                              0x40
#define HWIO_UCDR_SO_CONFIG_UCDR_ENABLE_SHFT                                                               0x6
#define HWIO_UCDR_SO_CONFIG_UCDR_SO_SATURATION_BMSK                                                       0x3f
#define HWIO_UCDR_SO_CONFIG_UCDR_SO_SATURATION_SHFT                                                        0x0

#define HWIO_UCDR_FO_TO_SO_DELAY_ADDR(x)                                                            ((x) + 0x000001a0)
#define HWIO_UCDR_FO_TO_SO_DELAY_RMSK                                                                     0xff
#define HWIO_UCDR_FO_TO_SO_DELAY_IN(x)      \
        in_dword_masked(HWIO_UCDR_FO_TO_SO_DELAY_ADDR(x), HWIO_UCDR_FO_TO_SO_DELAY_RMSK)
#define HWIO_UCDR_FO_TO_SO_DELAY_INM(x, m)      \
        in_dword_masked(HWIO_UCDR_FO_TO_SO_DELAY_ADDR(x), m)
#define HWIO_UCDR_FO_TO_SO_DELAY_OUT(x, v)      \
        out_dword(HWIO_UCDR_FO_TO_SO_DELAY_ADDR(x),v)
#define HWIO_UCDR_FO_TO_SO_DELAY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UCDR_FO_TO_SO_DELAY_ADDR(x),m,v,HWIO_UCDR_FO_TO_SO_DELAY_IN(x))
#define HWIO_UCDR_FO_TO_SO_DELAY_UCDR_FO_TO_SO_DELAY_BMSK                                                 0xff
#define HWIO_UCDR_FO_TO_SO_DELAY_UCDR_FO_TO_SO_DELAY_SHFT                                                  0x0

#define HWIO_RX_BAND_ADDR(x)                                                                        ((x) + 0x000001a4)
#define HWIO_RX_BAND_RMSK                                                                                 0x3f
#define HWIO_RX_BAND_IN(x)      \
        in_dword_masked(HWIO_RX_BAND_ADDR(x), HWIO_RX_BAND_RMSK)
#define HWIO_RX_BAND_INM(x, m)      \
        in_dword_masked(HWIO_RX_BAND_ADDR(x), m)
#define HWIO_RX_BAND_OUT(x, v)      \
        out_dword(HWIO_RX_BAND_ADDR(x),v)
#define HWIO_RX_BAND_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_BAND_ADDR(x),m,v,HWIO_RX_BAND_IN(x))
#define HWIO_RX_BAND_RX_BAND_MODE2_BMSK                                                                   0x30
#define HWIO_RX_BAND_RX_BAND_MODE2_SHFT                                                                    0x4
#define HWIO_RX_BAND_RX_BAND_MODE1_BMSK                                                                    0xc
#define HWIO_RX_BAND_RX_BAND_MODE1_SHFT                                                                    0x2
#define HWIO_RX_BAND_RX_BAND_MODE0_BMSK                                                                    0x3
#define HWIO_RX_BAND_RX_BAND_MODE0_SHFT                                                                    0x0

#define HWIO_AUX_ENABLE_ADDR(x)                                                                     ((x) + 0x000001a8)
#define HWIO_AUX_ENABLE_RMSK                                                                               0x3
#define HWIO_AUX_ENABLE_IN(x)      \
        in_dword_masked(HWIO_AUX_ENABLE_ADDR(x), HWIO_AUX_ENABLE_RMSK)
#define HWIO_AUX_ENABLE_INM(x, m)      \
        in_dword_masked(HWIO_AUX_ENABLE_ADDR(x), m)
#define HWIO_AUX_ENABLE_OUT(x, v)      \
        out_dword(HWIO_AUX_ENABLE_ADDR(x),v)
#define HWIO_AUX_ENABLE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AUX_ENABLE_ADDR(x),m,v,HWIO_AUX_ENABLE_IN(x))
#define HWIO_AUX_ENABLE_EN_APATH_BMSK                                                                      0x2
#define HWIO_AUX_ENABLE_EN_APATH_SHFT                                                                      0x1
#define HWIO_AUX_ENABLE_EN_AUXPI_BMSK                                                                      0x1
#define HWIO_AUX_ENABLE_EN_AUXPI_SHFT                                                                      0x0

#define HWIO_AUX_CONTROL_ADDR(x)                                                                    ((x) + 0x000001ac)
#define HWIO_AUX_CONTROL_RMSK                                                                             0x3f
#define HWIO_AUX_CONTROL_IN(x)      \
        in_dword_masked(HWIO_AUX_CONTROL_ADDR(x), HWIO_AUX_CONTROL_RMSK)
#define HWIO_AUX_CONTROL_INM(x, m)      \
        in_dword_masked(HWIO_AUX_CONTROL_ADDR(x), m)
#define HWIO_AUX_CONTROL_OUT(x, v)      \
        out_dword(HWIO_AUX_CONTROL_ADDR(x),v)
#define HWIO_AUX_CONTROL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AUX_CONTROL_ADDR(x),m,v,HWIO_AUX_CONTROL_IN(x))
#define HWIO_AUX_CONTROL_AUX_OFFSET_BMSK                                                                  0x3f
#define HWIO_AUX_CONTROL_AUX_OFFSET_SHFT                                                                   0x0

#define HWIO_AUX_DAC_ADDR(x)                                                                        ((x) + 0x000001b0)
#define HWIO_AUX_DAC_RMSK                                                                                 0x7f
#define HWIO_AUX_DAC_IN(x)      \
        in_dword_masked(HWIO_AUX_DAC_ADDR(x), HWIO_AUX_DAC_RMSK)
#define HWIO_AUX_DAC_INM(x, m)      \
        in_dword_masked(HWIO_AUX_DAC_ADDR(x), m)
#define HWIO_AUX_DAC_OUT(x, v)      \
        out_dword(HWIO_AUX_DAC_ADDR(x),v)
#define HWIO_AUX_DAC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AUX_DAC_ADDR(x),m,v,HWIO_AUX_DAC_IN(x))
#define HWIO_AUX_DAC_AUX_SIGN_BMSK                                                                        0x40
#define HWIO_AUX_DAC_AUX_SIGN_SHFT                                                                         0x6
#define HWIO_AUX_DAC_AUX_DAC_BMSK                                                                         0x3f
#define HWIO_AUX_DAC_AUX_DAC_SHFT                                                                          0x0

#define HWIO_AC_JTAG_CTRL_ADDR(x)                                                                   ((x) + 0x000001b4)
#define HWIO_AC_JTAG_CTRL_RMSK                                                                            0xff
#define HWIO_AC_JTAG_CTRL_IN(x)      \
        in_dword_masked(HWIO_AC_JTAG_CTRL_ADDR(x), HWIO_AC_JTAG_CTRL_RMSK)
#define HWIO_AC_JTAG_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_AC_JTAG_CTRL_ADDR(x), m)
#define HWIO_AC_JTAG_CTRL_OUT(x, v)      \
        out_dword(HWIO_AC_JTAG_CTRL_ADDR(x),v)
#define HWIO_AC_JTAG_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AC_JTAG_CTRL_ADDR(x),m,v,HWIO_AC_JTAG_CTRL_IN(x))
#define HWIO_AC_JTAG_CTRL_AC_JTAG_RESET_BMSK                                                              0x80
#define HWIO_AC_JTAG_CTRL_AC_JTAG_RESET_SHFT                                                               0x7
#define HWIO_AC_JTAG_CTRL_AC_JTAG_MODE_BMSK                                                               0x40
#define HWIO_AC_JTAG_CTRL_AC_JTAG_MODE_SHFT                                                                0x6
#define HWIO_AC_JTAG_CTRL_AC_JTAG_LVL_BMSK                                                                0x20
#define HWIO_AC_JTAG_CTRL_AC_JTAG_LVL_SHFT                                                                 0x5
#define HWIO_AC_JTAG_CTRL_AC_JTAG_INITN_MUX_BMSK                                                          0x10
#define HWIO_AC_JTAG_CTRL_AC_JTAG_INITN_MUX_SHFT                                                           0x4
#define HWIO_AC_JTAG_CTRL_AC_JTAG_INITN_BMSK                                                               0x8
#define HWIO_AC_JTAG_CTRL_AC_JTAG_INITN_SHFT                                                               0x3
#define HWIO_AC_JTAG_CTRL_AC_JTAG_INITP_MUX_BMSK                                                           0x4
#define HWIO_AC_JTAG_CTRL_AC_JTAG_INITP_MUX_SHFT                                                           0x2
#define HWIO_AC_JTAG_CTRL_AC_JTAG_INITP_BMSK                                                               0x2
#define HWIO_AC_JTAG_CTRL_AC_JTAG_INITP_SHFT                                                               0x1
#define HWIO_AC_JTAG_CTRL_AC_JTAG_EN_BMSK                                                                  0x1
#define HWIO_AC_JTAG_CTRL_AC_JTAG_EN_SHFT                                                                  0x0

#define HWIO_RX_RCVR_PATH0_ADDR(x)                                                                  ((x) + 0x000001b8)
#define HWIO_RX_RCVR_PATH0_RMSK                                                                           0xff
#define HWIO_RX_RCVR_PATH0_IN(x)      \
        in_dword_masked(HWIO_RX_RCVR_PATH0_ADDR(x), HWIO_RX_RCVR_PATH0_RMSK)
#define HWIO_RX_RCVR_PATH0_INM(x, m)      \
        in_dword_masked(HWIO_RX_RCVR_PATH0_ADDR(x), m)
#define HWIO_RX_RCVR_PATH0_OUT(x, v)      \
        out_dword(HWIO_RX_RCVR_PATH0_ADDR(x),v)
#define HWIO_RX_RCVR_PATH0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_RCVR_PATH0_ADDR(x),m,v,HWIO_RX_RCVR_PATH0_IN(x))
#define HWIO_RX_RCVR_PATH0_EN_IQ_PI_MUX_BMSK                                                              0x80
#define HWIO_RX_RCVR_PATH0_EN_IQ_PI_MUX_SHFT                                                               0x7
#define HWIO_RX_RCVR_PATH0_EN_IQ_PI_BMSK                                                                  0x40
#define HWIO_RX_RCVR_PATH0_EN_IQ_PI_SHFT                                                                   0x6
#define HWIO_RX_RCVR_PATH0_EN_SAMPCAL_IPATH_MUX_BMSK                                                      0x20
#define HWIO_RX_RCVR_PATH0_EN_SAMPCAL_IPATH_MUX_SHFT                                                       0x5
#define HWIO_RX_RCVR_PATH0_EN_SAMPCAL_IPATH_BMSK                                                          0x10
#define HWIO_RX_RCVR_PATH0_EN_SAMPCAL_IPATH_SHFT                                                           0x4
#define HWIO_RX_RCVR_PATH0_EN_RCVR_MUX_BMSK                                                                0x8
#define HWIO_RX_RCVR_PATH0_EN_RCVR_MUX_SHFT                                                                0x3
#define HWIO_RX_RCVR_PATH0_EN_RCVR_BMSK                                                                    0x4
#define HWIO_RX_RCVR_PATH0_EN_RCVR_SHFT                                                                    0x2
#define HWIO_RX_RCVR_PATH0_EN_DESERIALIZER_MUX_BMSK                                                        0x2
#define HWIO_RX_RCVR_PATH0_EN_DESERIALIZER_MUX_SHFT                                                        0x1
#define HWIO_RX_RCVR_PATH0_EN_DESERIALIZER_BMSK                                                            0x1
#define HWIO_RX_RCVR_PATH0_EN_DESERIALIZER_SHFT                                                            0x0

#define HWIO_RX_RCVR_PATH1_ADDR(x)                                                                  ((x) + 0x000001bc)
#define HWIO_RX_RCVR_PATH1_RMSK                                                                           0xff
#define HWIO_RX_RCVR_PATH1_IN(x)      \
        in_dword_masked(HWIO_RX_RCVR_PATH1_ADDR(x), HWIO_RX_RCVR_PATH1_RMSK)
#define HWIO_RX_RCVR_PATH1_INM(x, m)      \
        in_dword_masked(HWIO_RX_RCVR_PATH1_ADDR(x), m)
#define HWIO_RX_RCVR_PATH1_OUT(x, v)      \
        out_dword(HWIO_RX_RCVR_PATH1_ADDR(x),v)
#define HWIO_RX_RCVR_PATH1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_RCVR_PATH1_ADDR(x),m,v,HWIO_RX_RCVR_PATH1_IN(x))
#define HWIO_RX_RCVR_PATH1_SAMPCAL_DEBUG_MODE_MOVE_BMSK                                                   0x80
#define HWIO_RX_RCVR_PATH1_SAMPCAL_DEBUG_MODE_MOVE_SHFT                                                    0x7
#define HWIO_RX_RCVR_PATH1_SAMPCAL_DEBUG_MODE_BMSK                                                        0x40
#define HWIO_RX_RCVR_PATH1_SAMPCAL_DEBUG_MODE_SHFT                                                         0x6
#define HWIO_RX_RCVR_PATH1_RCLK_EN_MUX_BMSK                                                               0x20
#define HWIO_RX_RCVR_PATH1_RCLK_EN_MUX_SHFT                                                                0x5
#define HWIO_RX_RCVR_PATH1_RCLK_EN_BMSK                                                                   0x10
#define HWIO_RX_RCVR_PATH1_RCLK_EN_SHFT                                                                    0x4
#define HWIO_RX_RCVR_PATH1_EN_SAMPCAL_EPATH_MUX_BMSK                                                       0x8
#define HWIO_RX_RCVR_PATH1_EN_SAMPCAL_EPATH_MUX_SHFT                                                       0x3
#define HWIO_RX_RCVR_PATH1_EN_SAMPCAL_EPATH_BMSK                                                           0x4
#define HWIO_RX_RCVR_PATH1_EN_SAMPCAL_EPATH_SHFT                                                           0x2
#define HWIO_RX_RCVR_PATH1_EN_SAMPCAL_QPATH_MUX_BMSK                                                       0x2
#define HWIO_RX_RCVR_PATH1_EN_SAMPCAL_QPATH_MUX_SHFT                                                       0x1
#define HWIO_RX_RCVR_PATH1_EN_SAMPCAL_QPATH_BMSK                                                           0x1
#define HWIO_RX_RCVR_PATH1_EN_SAMPCAL_QPATH_SHFT                                                           0x0

#define HWIO_RX_RCVR_PATH1_MODE0_ADDR(x)                                                            ((x) + 0x000001c0)
#define HWIO_RX_RCVR_PATH1_MODE0_RMSK                                                                     0x7f
#define HWIO_RX_RCVR_PATH1_MODE0_IN(x)      \
        in_dword_masked(HWIO_RX_RCVR_PATH1_MODE0_ADDR(x), HWIO_RX_RCVR_PATH1_MODE0_RMSK)
#define HWIO_RX_RCVR_PATH1_MODE0_INM(x, m)      \
        in_dword_masked(HWIO_RX_RCVR_PATH1_MODE0_ADDR(x), m)
#define HWIO_RX_RCVR_PATH1_MODE0_OUT(x, v)      \
        out_dword(HWIO_RX_RCVR_PATH1_MODE0_ADDR(x),v)
#define HWIO_RX_RCVR_PATH1_MODE0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_RCVR_PATH1_MODE0_ADDR(x),m,v,HWIO_RX_RCVR_PATH1_MODE0_IN(x))
#define HWIO_RX_RCVR_PATH1_MODE0_CDR_PD_SEL_MODE0_BMSK                                                    0x60
#define HWIO_RX_RCVR_PATH1_MODE0_CDR_PD_SEL_MODE0_SHFT                                                     0x5
#define HWIO_RX_RCVR_PATH1_MODE0_EN_DLL_MODE0_BMSK                                                        0x10
#define HWIO_RX_RCVR_PATH1_MODE0_EN_DLL_MODE0_SHFT                                                         0x4
#define HWIO_RX_RCVR_PATH1_MODE0_EN_IQ_DCC_MODE0_BMSK                                                      0x8
#define HWIO_RX_RCVR_PATH1_MODE0_EN_IQ_DCC_MODE0_SHFT                                                      0x3
#define HWIO_RX_RCVR_PATH1_MODE0_EN_IQCAL_MODE0_BMSK                                                       0x4
#define HWIO_RX_RCVR_PATH1_MODE0_EN_IQCAL_MODE0_SHFT                                                       0x2
#define HWIO_RX_RCVR_PATH1_MODE0_EN_QPATH_MODE0_BMSK                                                       0x2
#define HWIO_RX_RCVR_PATH1_MODE0_EN_QPATH_MODE0_SHFT                                                       0x1
#define HWIO_RX_RCVR_PATH1_MODE0_EN_EPATH_MODE0_BMSK                                                       0x1
#define HWIO_RX_RCVR_PATH1_MODE0_EN_EPATH_MODE0_SHFT                                                       0x0

#define HWIO_RX_RCVR_PATH1_MODE1_ADDR(x)                                                            ((x) + 0x000001c4)
#define HWIO_RX_RCVR_PATH1_MODE1_RMSK                                                                     0x7f
#define HWIO_RX_RCVR_PATH1_MODE1_IN(x)      \
        in_dword_masked(HWIO_RX_RCVR_PATH1_MODE1_ADDR(x), HWIO_RX_RCVR_PATH1_MODE1_RMSK)
#define HWIO_RX_RCVR_PATH1_MODE1_INM(x, m)      \
        in_dword_masked(HWIO_RX_RCVR_PATH1_MODE1_ADDR(x), m)
#define HWIO_RX_RCVR_PATH1_MODE1_OUT(x, v)      \
        out_dword(HWIO_RX_RCVR_PATH1_MODE1_ADDR(x),v)
#define HWIO_RX_RCVR_PATH1_MODE1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_RCVR_PATH1_MODE1_ADDR(x),m,v,HWIO_RX_RCVR_PATH1_MODE1_IN(x))
#define HWIO_RX_RCVR_PATH1_MODE1_CDR_PD_SEL_MODE1_BMSK                                                    0x60
#define HWIO_RX_RCVR_PATH1_MODE1_CDR_PD_SEL_MODE1_SHFT                                                     0x5
#define HWIO_RX_RCVR_PATH1_MODE1_EN_DLL_MODE1_BMSK                                                        0x10
#define HWIO_RX_RCVR_PATH1_MODE1_EN_DLL_MODE1_SHFT                                                         0x4
#define HWIO_RX_RCVR_PATH1_MODE1_EN_IQ_DCC_MODE1_BMSK                                                      0x8
#define HWIO_RX_RCVR_PATH1_MODE1_EN_IQ_DCC_MODE1_SHFT                                                      0x3
#define HWIO_RX_RCVR_PATH1_MODE1_EN_IQCAL_MODE1_BMSK                                                       0x4
#define HWIO_RX_RCVR_PATH1_MODE1_EN_IQCAL_MODE1_SHFT                                                       0x2
#define HWIO_RX_RCVR_PATH1_MODE1_EN_QPATH_MODE1_BMSK                                                       0x2
#define HWIO_RX_RCVR_PATH1_MODE1_EN_QPATH_MODE1_SHFT                                                       0x1
#define HWIO_RX_RCVR_PATH1_MODE1_EN_EPATH_MODE1_BMSK                                                       0x1
#define HWIO_RX_RCVR_PATH1_MODE1_EN_EPATH_MODE1_SHFT                                                       0x0

#define HWIO_RX_RCVR_PATH1_MODE2_ADDR(x)                                                            ((x) + 0x000001c8)
#define HWIO_RX_RCVR_PATH1_MODE2_RMSK                                                                     0x7f
#define HWIO_RX_RCVR_PATH1_MODE2_IN(x)      \
        in_dword_masked(HWIO_RX_RCVR_PATH1_MODE2_ADDR(x), HWIO_RX_RCVR_PATH1_MODE2_RMSK)
#define HWIO_RX_RCVR_PATH1_MODE2_INM(x, m)      \
        in_dword_masked(HWIO_RX_RCVR_PATH1_MODE2_ADDR(x), m)
#define HWIO_RX_RCVR_PATH1_MODE2_OUT(x, v)      \
        out_dword(HWIO_RX_RCVR_PATH1_MODE2_ADDR(x),v)
#define HWIO_RX_RCVR_PATH1_MODE2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_RCVR_PATH1_MODE2_ADDR(x),m,v,HWIO_RX_RCVR_PATH1_MODE2_IN(x))
#define HWIO_RX_RCVR_PATH1_MODE2_CDR_PD_SEL_MODE2_BMSK                                                    0x60
#define HWIO_RX_RCVR_PATH1_MODE2_CDR_PD_SEL_MODE2_SHFT                                                     0x5
#define HWIO_RX_RCVR_PATH1_MODE2_EN_DLL_MODE2_BMSK                                                        0x10
#define HWIO_RX_RCVR_PATH1_MODE2_EN_DLL_MODE2_SHFT                                                         0x4
#define HWIO_RX_RCVR_PATH1_MODE2_EN_IQ_DCC_MODE2_BMSK                                                      0x8
#define HWIO_RX_RCVR_PATH1_MODE2_EN_IQ_DCC_MODE2_SHFT                                                      0x3
#define HWIO_RX_RCVR_PATH1_MODE2_EN_IQCAL_MODE2_BMSK                                                       0x4
#define HWIO_RX_RCVR_PATH1_MODE2_EN_IQCAL_MODE2_SHFT                                                       0x2
#define HWIO_RX_RCVR_PATH1_MODE2_EN_QPATH_MODE2_BMSK                                                       0x2
#define HWIO_RX_RCVR_PATH1_MODE2_EN_QPATH_MODE2_SHFT                                                       0x1
#define HWIO_RX_RCVR_PATH1_MODE2_EN_EPATH_MODE2_BMSK                                                       0x1
#define HWIO_RX_RCVR_PATH1_MODE2_EN_EPATH_MODE2_SHFT                                                       0x0

#define HWIO_SAMPCAL_BYP_CODE_I0_ADDR(x)                                                            ((x) + 0x000001cc)
#define HWIO_SAMPCAL_BYP_CODE_I0_RMSK                                                                     0x1f
#define HWIO_SAMPCAL_BYP_CODE_I0_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_I0_ADDR(x), HWIO_SAMPCAL_BYP_CODE_I0_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_I0_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_I0_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_I0_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_I0_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_I0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_I0_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_I0_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_I0_CAL_ISAMP0_MUX_BMSK                                                      0x10
#define HWIO_SAMPCAL_BYP_CODE_I0_CAL_ISAMP0_MUX_SHFT                                                       0x4
#define HWIO_SAMPCAL_BYP_CODE_I0_CAL_ISAMP0_BMSK                                                           0xf
#define HWIO_SAMPCAL_BYP_CODE_I0_CAL_ISAMP0_SHFT                                                           0x0

#define HWIO_SAMPCAL_BYP_CODE_I0B_ADDR(x)                                                           ((x) + 0x000001d0)
#define HWIO_SAMPCAL_BYP_CODE_I0B_RMSK                                                                    0x1f
#define HWIO_SAMPCAL_BYP_CODE_I0B_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_I0B_ADDR(x), HWIO_SAMPCAL_BYP_CODE_I0B_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_I0B_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_I0B_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_I0B_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_I0B_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_I0B_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_I0B_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_I0B_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_I0B_CAL_IBSAMP0_MUX_BMSK                                                    0x10
#define HWIO_SAMPCAL_BYP_CODE_I0B_CAL_IBSAMP0_MUX_SHFT                                                     0x4
#define HWIO_SAMPCAL_BYP_CODE_I0B_CAL_IBSAMP0_BMSK                                                         0xf
#define HWIO_SAMPCAL_BYP_CODE_I0B_CAL_IBSAMP0_SHFT                                                         0x0

#define HWIO_SAMPCAL_BYP_CODE_I1_ADDR(x)                                                            ((x) + 0x000001d4)
#define HWIO_SAMPCAL_BYP_CODE_I1_RMSK                                                                     0x1f
#define HWIO_SAMPCAL_BYP_CODE_I1_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_I1_ADDR(x), HWIO_SAMPCAL_BYP_CODE_I1_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_I1_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_I1_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_I1_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_I1_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_I1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_I1_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_I1_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_I1_CAL_ISAMP1_MUX_BMSK                                                      0x10
#define HWIO_SAMPCAL_BYP_CODE_I1_CAL_ISAMP1_MUX_SHFT                                                       0x4
#define HWIO_SAMPCAL_BYP_CODE_I1_CAL_ISAMP1_BMSK                                                           0xf
#define HWIO_SAMPCAL_BYP_CODE_I1_CAL_ISAMP1_SHFT                                                           0x0

#define HWIO_SAMPCAL_BYP_CODE_I1B_ADDR(x)                                                           ((x) + 0x000001d8)
#define HWIO_SAMPCAL_BYP_CODE_I1B_RMSK                                                                    0x1f
#define HWIO_SAMPCAL_BYP_CODE_I1B_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_I1B_ADDR(x), HWIO_SAMPCAL_BYP_CODE_I1B_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_I1B_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_I1B_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_I1B_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_I1B_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_I1B_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_I1B_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_I1B_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_I1B_CAL_IBSAMP1_MUX_BMSK                                                    0x10
#define HWIO_SAMPCAL_BYP_CODE_I1B_CAL_IBSAMP1_MUX_SHFT                                                     0x4
#define HWIO_SAMPCAL_BYP_CODE_I1B_CAL_IBSAMP1_BMSK                                                         0xf
#define HWIO_SAMPCAL_BYP_CODE_I1B_CAL_IBSAMP1_SHFT                                                         0x0

#define HWIO_SAMPCAL_BYP_CODE_Q_ADDR(x)                                                             ((x) + 0x000001dc)
#define HWIO_SAMPCAL_BYP_CODE_Q_RMSK                                                                      0x1f
#define HWIO_SAMPCAL_BYP_CODE_Q_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_Q_ADDR(x), HWIO_SAMPCAL_BYP_CODE_Q_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_Q_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_Q_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_Q_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_Q_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_Q_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_Q_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_Q_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_Q_CAL_QSAMP0_MUX_BMSK                                                       0x10
#define HWIO_SAMPCAL_BYP_CODE_Q_CAL_QSAMP0_MUX_SHFT                                                        0x4
#define HWIO_SAMPCAL_BYP_CODE_Q_CAL_QSAMP0_BMSK                                                            0xf
#define HWIO_SAMPCAL_BYP_CODE_Q_CAL_QSAMP0_SHFT                                                            0x0

#define HWIO_SAMPCAL_BYP_CODE_QB_ADDR(x)                                                            ((x) + 0x000001e0)
#define HWIO_SAMPCAL_BYP_CODE_QB_RMSK                                                                     0x1f
#define HWIO_SAMPCAL_BYP_CODE_QB_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_QB_ADDR(x), HWIO_SAMPCAL_BYP_CODE_QB_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_QB_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_QB_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_QB_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_QB_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_QB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_QB_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_QB_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_QB_CAL_QBSAMP0_MUX_BMSK                                                     0x10
#define HWIO_SAMPCAL_BYP_CODE_QB_CAL_QBSAMP0_MUX_SHFT                                                      0x4
#define HWIO_SAMPCAL_BYP_CODE_QB_CAL_QBSAMP0_BMSK                                                          0xf
#define HWIO_SAMPCAL_BYP_CODE_QB_CAL_QBSAMP0_SHFT                                                          0x0

#define HWIO_SAMPCAL_BYP_CODE_A_ADDR(x)                                                             ((x) + 0x000001e4)
#define HWIO_SAMPCAL_BYP_CODE_A_RMSK                                                                      0x1f
#define HWIO_SAMPCAL_BYP_CODE_A_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_A_ADDR(x), HWIO_SAMPCAL_BYP_CODE_A_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_A_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_A_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_A_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_A_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_A_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_A_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_A_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_A_CAL_ASAMP0_MUX_BMSK                                                       0x10
#define HWIO_SAMPCAL_BYP_CODE_A_CAL_ASAMP0_MUX_SHFT                                                        0x4
#define HWIO_SAMPCAL_BYP_CODE_A_CAL_ASAMP0_BMSK                                                            0xf
#define HWIO_SAMPCAL_BYP_CODE_A_CAL_ASAMP0_SHFT                                                            0x0

#define HWIO_SAMPCAL_BYP_CODE_AB_ADDR(x)                                                            ((x) + 0x000001e8)
#define HWIO_SAMPCAL_BYP_CODE_AB_RMSK                                                                     0x1f
#define HWIO_SAMPCAL_BYP_CODE_AB_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_AB_ADDR(x), HWIO_SAMPCAL_BYP_CODE_AB_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_AB_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_AB_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_AB_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_AB_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_AB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_AB_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_AB_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_AB_CAL_ABSAMP0_MUX_BMSK                                                     0x10
#define HWIO_SAMPCAL_BYP_CODE_AB_CAL_ABSAMP0_MUX_SHFT                                                      0x4
#define HWIO_SAMPCAL_BYP_CODE_AB_CAL_ABSAMP0_BMSK                                                          0xf
#define HWIO_SAMPCAL_BYP_CODE_AB_CAL_ABSAMP0_SHFT                                                          0x0

#define HWIO_SAMPCAL_BYP_CODE_E_ADDR(x)                                                             ((x) + 0x000001ec)
#define HWIO_SAMPCAL_BYP_CODE_E_RMSK                                                                      0x3f
#define HWIO_SAMPCAL_BYP_CODE_E_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_E_ADDR(x), HWIO_SAMPCAL_BYP_CODE_E_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_E_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_E_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_E_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_E_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_E_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_E_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_E_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_E_CAL_ESAMP0_MUX_BMSK                                                       0x20
#define HWIO_SAMPCAL_BYP_CODE_E_CAL_ESAMP0_MUX_SHFT                                                        0x5
#define HWIO_SAMPCAL_BYP_CODE_E_CAL_ESAMP0_BMSK                                                           0x1f
#define HWIO_SAMPCAL_BYP_CODE_E_CAL_ESAMP0_SHFT                                                            0x0

#define HWIO_SAMPCAL_BYP_CODE_EB_ADDR(x)                                                            ((x) + 0x000001f0)
#define HWIO_SAMPCAL_BYP_CODE_EB_RMSK                                                                     0x3f
#define HWIO_SAMPCAL_BYP_CODE_EB_IN(x)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_EB_ADDR(x), HWIO_SAMPCAL_BYP_CODE_EB_RMSK)
#define HWIO_SAMPCAL_BYP_CODE_EB_INM(x, m)      \
        in_dword_masked(HWIO_SAMPCAL_BYP_CODE_EB_ADDR(x), m)
#define HWIO_SAMPCAL_BYP_CODE_EB_OUT(x, v)      \
        out_dword(HWIO_SAMPCAL_BYP_CODE_EB_ADDR(x),v)
#define HWIO_SAMPCAL_BYP_CODE_EB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SAMPCAL_BYP_CODE_EB_ADDR(x),m,v,HWIO_SAMPCAL_BYP_CODE_EB_IN(x))
#define HWIO_SAMPCAL_BYP_CODE_EB_CAL_EBSAMP0_MUX_BMSK                                                     0x20
#define HWIO_SAMPCAL_BYP_CODE_EB_CAL_EBSAMP0_MUX_SHFT                                                      0x5
#define HWIO_SAMPCAL_BYP_CODE_EB_CAL_EBSAMP0_BMSK                                                         0x1f
#define HWIO_SAMPCAL_BYP_CODE_EB_CAL_EBSAMP0_SHFT                                                          0x0

#define HWIO_RX_EOM_START_ADDR(x)                                                                   ((x) + 0x000001f4)
#define HWIO_RX_EOM_START_RMSK                                                                             0x1
#define HWIO_RX_EOM_START_IN(x)      \
        in_dword_masked(HWIO_RX_EOM_START_ADDR(x), HWIO_RX_EOM_START_RMSK)
#define HWIO_RX_EOM_START_INM(x, m)      \
        in_dword_masked(HWIO_RX_EOM_START_ADDR(x), m)
#define HWIO_RX_EOM_START_OUT(x, v)      \
        out_dword(HWIO_RX_EOM_START_ADDR(x),v)
#define HWIO_RX_EOM_START_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_EOM_START_ADDR(x),m,v,HWIO_RX_EOM_START_IN(x))
#define HWIO_RX_EOM_START_EOM_START_BMSK                                                                   0x1
#define HWIO_RX_EOM_START_EOM_START_SHFT                                                                   0x0

#define HWIO_RSM_CONFIG_ADDR(x)                                                                     ((x) + 0x000001f8)
#define HWIO_RSM_CONFIG_RMSK                                                                              0xff
#define HWIO_RSM_CONFIG_IN(x)      \
        in_dword_masked(HWIO_RSM_CONFIG_ADDR(x), HWIO_RSM_CONFIG_RMSK)
#define HWIO_RSM_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_RSM_CONFIG_ADDR(x), m)
#define HWIO_RSM_CONFIG_OUT(x, v)      \
        out_dword(HWIO_RSM_CONFIG_ADDR(x),v)
#define HWIO_RSM_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RSM_CONFIG_ADDR(x),m,v,HWIO_RSM_CONFIG_IN(x))
#define HWIO_RSM_CONFIG_FORCE_TSYNC_ACK_BMSK                                                              0x80
#define HWIO_RSM_CONFIG_FORCE_TSYNC_ACK_SHFT                                                               0x7
#define HWIO_RSM_CONFIG_FORCE_CMN_ACK_BMSK                                                                0x40
#define HWIO_RSM_CONFIG_FORCE_CMN_ACK_SHFT                                                                 0x6
#define HWIO_RSM_CONFIG_FORCE_CMN_READY_BMSK                                                              0x20
#define HWIO_RSM_CONFIG_FORCE_CMN_READY_SHFT                                                               0x5
#define HWIO_RSM_CONFIG_EN_RCLK_DEGLITCH_BMSK                                                             0x10
#define HWIO_RSM_CONFIG_EN_RCLK_DEGLITCH_SHFT                                                              0x4
#define HWIO_RSM_CONFIG_BYPASS_RSM_CDR_RESET_BMSK                                                          0x8
#define HWIO_RSM_CONFIG_BYPASS_RSM_CDR_RESET_SHFT                                                          0x3
#define HWIO_RSM_CONFIG_BYPASS_RSM_TSYNC_BMSK                                                              0x4
#define HWIO_RSM_CONFIG_BYPASS_RSM_TSYNC_SHFT                                                              0x2
#define HWIO_RSM_CONFIG_BYPASS_RSM_SAMP_CAL_BMSK                                                           0x2
#define HWIO_RSM_CONFIG_BYPASS_RSM_SAMP_CAL_SHFT                                                           0x1
#define HWIO_RSM_CONFIG_BYPASS_RSM_DLL_CAL_BMSK                                                            0x1
#define HWIO_RSM_CONFIG_BYPASS_RSM_DLL_CAL_SHFT                                                            0x0

#define HWIO_RX_EOM_MEAS_TIME0_ADDR(x)                                                              ((x) + 0x000001fc)
#define HWIO_RX_EOM_MEAS_TIME0_RMSK                                                                       0xff
#define HWIO_RX_EOM_MEAS_TIME0_IN(x)      \
        in_dword_masked(HWIO_RX_EOM_MEAS_TIME0_ADDR(x), HWIO_RX_EOM_MEAS_TIME0_RMSK)
#define HWIO_RX_EOM_MEAS_TIME0_INM(x, m)      \
        in_dword_masked(HWIO_RX_EOM_MEAS_TIME0_ADDR(x), m)
#define HWIO_RX_EOM_MEAS_TIME0_OUT(x, v)      \
        out_dword(HWIO_RX_EOM_MEAS_TIME0_ADDR(x),v)
#define HWIO_RX_EOM_MEAS_TIME0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_EOM_MEAS_TIME0_ADDR(x),m,v,HWIO_RX_EOM_MEAS_TIME0_IN(x))
#define HWIO_RX_EOM_MEAS_TIME0_EOM_MEAS_TIME_7_0_BMSK                                                     0xff
#define HWIO_RX_EOM_MEAS_TIME0_EOM_MEAS_TIME_7_0_SHFT                                                      0x0

#define HWIO_RX_EOM_MEAS_TIME1_ADDR(x)                                                              ((x) + 0x00000200)
#define HWIO_RX_EOM_MEAS_TIME1_RMSK                                                                       0xff
#define HWIO_RX_EOM_MEAS_TIME1_IN(x)      \
        in_dword_masked(HWIO_RX_EOM_MEAS_TIME1_ADDR(x), HWIO_RX_EOM_MEAS_TIME1_RMSK)
#define HWIO_RX_EOM_MEAS_TIME1_INM(x, m)      \
        in_dword_masked(HWIO_RX_EOM_MEAS_TIME1_ADDR(x), m)
#define HWIO_RX_EOM_MEAS_TIME1_OUT(x, v)      \
        out_dword(HWIO_RX_EOM_MEAS_TIME1_ADDR(x),v)
#define HWIO_RX_EOM_MEAS_TIME1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_EOM_MEAS_TIME1_ADDR(x),m,v,HWIO_RX_EOM_MEAS_TIME1_IN(x))
#define HWIO_RX_EOM_MEAS_TIME1_EOM_MEAS_TIME_15_8_BMSK                                                    0xff
#define HWIO_RX_EOM_MEAS_TIME1_EOM_MEAS_TIME_15_8_SHFT                                                     0x0

#define HWIO_RX_EOM_CTRL_ADDR(x)                                                                    ((x) + 0x00000204)
#define HWIO_RX_EOM_CTRL_RMSK                                                                             0x1f
#define HWIO_RX_EOM_CTRL_IN(x)      \
        in_dword_masked(HWIO_RX_EOM_CTRL_ADDR(x), HWIO_RX_EOM_CTRL_RMSK)
#define HWIO_RX_EOM_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_RX_EOM_CTRL_ADDR(x), m)
#define HWIO_RX_EOM_CTRL_OUT(x, v)      \
        out_dword(HWIO_RX_EOM_CTRL_ADDR(x),v)
#define HWIO_RX_EOM_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_EOM_CTRL_ADDR(x),m,v,HWIO_RX_EOM_CTRL_IN(x))
#define HWIO_RX_EOM_CTRL_EOM_WAIT_TIME_BMSK                                                               0x18
#define HWIO_RX_EOM_CTRL_EOM_WAIT_TIME_SHFT                                                                0x3
#define HWIO_RX_EOM_CTRL_EOM_ERR_COMP_CTRL_BMSK                                                            0x7
#define HWIO_RX_EOM_CTRL_EOM_ERR_COMP_CTRL_SHFT                                                            0x0

#define HWIO_RX_HIGHZ_HIGHRATE_ADDR(x)                                                              ((x) + 0x00000208)
#define HWIO_RX_HIGHZ_HIGHRATE_RMSK                                                                        0x3
#define HWIO_RX_HIGHZ_HIGHRATE_IN(x)      \
        in_dword_masked(HWIO_RX_HIGHZ_HIGHRATE_ADDR(x), HWIO_RX_HIGHZ_HIGHRATE_RMSK)
#define HWIO_RX_HIGHZ_HIGHRATE_INM(x, m)      \
        in_dword_masked(HWIO_RX_HIGHZ_HIGHRATE_ADDR(x), m)
#define HWIO_RX_HIGHZ_HIGHRATE_OUT(x, v)      \
        out_dword(HWIO_RX_HIGHZ_HIGHRATE_ADDR(x),v)
#define HWIO_RX_HIGHZ_HIGHRATE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_HIGHZ_HIGHRATE_ADDR(x),m,v,HWIO_RX_HIGHZ_HIGHRATE_IN(x))
#define HWIO_RX_HIGHZ_HIGHRATE_RXTERM_HIGHZ_MUX_BMSK                                                       0x2
#define HWIO_RX_HIGHZ_HIGHRATE_RXTERM_HIGHZ_MUX_SHFT                                                       0x1
#define HWIO_RX_HIGHZ_HIGHRATE_RXTERM_HIGHZ_BMSK                                                           0x1
#define HWIO_RX_HIGHZ_HIGHRATE_RXTERM_HIGHZ_SHFT                                                           0x0

#define HWIO_RX_SAMPCAL_IDAC_SIGN1_ADDR(x)                                                          ((x) + 0x0000020c)
#define HWIO_RX_SAMPCAL_IDAC_SIGN1_RMSK                                                                   0xff
#define HWIO_RX_SAMPCAL_IDAC_SIGN1_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_IDAC_SIGN1_ADDR(x), HWIO_RX_SAMPCAL_IDAC_SIGN1_RMSK)
#define HWIO_RX_SAMPCAL_IDAC_SIGN1_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_IDAC_SIGN1_ADDR(x), m)
#define HWIO_RX_SAMPCAL_IDAC_SIGN1_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_IDAC_SIGN1_ADDR(x),v)
#define HWIO_RX_SAMPCAL_IDAC_SIGN1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_IDAC_SIGN1_ADDR(x),m,v,HWIO_RX_SAMPCAL_IDAC_SIGN1_IN(x))
#define HWIO_RX_SAMPCAL_IDAC_SIGN1_IDAC_SIGN_7_0_BMSK                                                     0xff
#define HWIO_RX_SAMPCAL_IDAC_SIGN1_IDAC_SIGN_7_0_SHFT                                                      0x0

#define HWIO_RX_SAMPCAL_IDAC_SIGN2_ADDR(x)                                                          ((x) + 0x00000210)
#define HWIO_RX_SAMPCAL_IDAC_SIGN2_RMSK                                                                    0x3
#define HWIO_RX_SAMPCAL_IDAC_SIGN2_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_IDAC_SIGN2_ADDR(x), HWIO_RX_SAMPCAL_IDAC_SIGN2_RMSK)
#define HWIO_RX_SAMPCAL_IDAC_SIGN2_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_IDAC_SIGN2_ADDR(x), m)
#define HWIO_RX_SAMPCAL_IDAC_SIGN2_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_IDAC_SIGN2_ADDR(x),v)
#define HWIO_RX_SAMPCAL_IDAC_SIGN2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_IDAC_SIGN2_ADDR(x),m,v,HWIO_RX_SAMPCAL_IDAC_SIGN2_IN(x))
#define HWIO_RX_SAMPCAL_IDAC_SIGN2_IDAC_SIGN_9_8_BMSK                                                      0x3
#define HWIO_RX_SAMPCAL_IDAC_SIGN2_IDAC_SIGN_9_8_SHFT                                                      0x0

#define HWIO_RX_SAMPCAL_CONFIG_ADDR(x)                                                              ((x) + 0x00000214)
#define HWIO_RX_SAMPCAL_CONFIG_RMSK                                                                       0xff
#define HWIO_RX_SAMPCAL_CONFIG_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_CONFIG_ADDR(x), HWIO_RX_SAMPCAL_CONFIG_RMSK)
#define HWIO_RX_SAMPCAL_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_CONFIG_ADDR(x), m)
#define HWIO_RX_SAMPCAL_CONFIG_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_CONFIG_ADDR(x),v)
#define HWIO_RX_SAMPCAL_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_CONFIG_ADDR(x),m,v,HWIO_RX_SAMPCAL_CONFIG_IN(x))
#define HWIO_RX_SAMPCAL_CONFIG_SAMPCAL_EDAC_SIGN_DIG_BMSK                                                 0x80
#define HWIO_RX_SAMPCAL_CONFIG_SAMPCAL_EDAC_SIGN_DIG_SHFT                                                  0x7
#define HWIO_RX_SAMPCAL_CONFIG_EN_SAMPCAL_I1_MUX_BMSK                                                     0x40
#define HWIO_RX_SAMPCAL_CONFIG_EN_SAMPCAL_I1_MUX_SHFT                                                      0x6
#define HWIO_RX_SAMPCAL_CONFIG_EN_SAMPCAL_I1_BMSK                                                         0x20
#define HWIO_RX_SAMPCAL_CONFIG_EN_SAMPCAL_I1_SHFT                                                          0x5
#define HWIO_RX_SAMPCAL_CONFIG_EN_SAMPCAL_I0_MUX_BMSK                                                     0x10
#define HWIO_RX_SAMPCAL_CONFIG_EN_SAMPCAL_I0_MUX_SHFT                                                      0x4
#define HWIO_RX_SAMPCAL_CONFIG_EN_SAMPCAL_I0_BMSK                                                          0x8
#define HWIO_RX_SAMPCAL_CONFIG_EN_SAMPCAL_I0_SHFT                                                          0x3
#define HWIO_RX_SAMPCAL_CONFIG_SAMPCAL_EN_MUX_BMSK                                                         0x4
#define HWIO_RX_SAMPCAL_CONFIG_SAMPCAL_EN_MUX_SHFT                                                         0x2
#define HWIO_RX_SAMPCAL_CONFIG_SAMPCAL_EN_BMSK                                                             0x2
#define HWIO_RX_SAMPCAL_CONFIG_SAMPCAL_EN_SHFT                                                             0x1
#define HWIO_RX_SAMPCAL_CONFIG_FORCE_SAMPCAL_DONE_BMSK                                                     0x1
#define HWIO_RX_SAMPCAL_CONFIG_FORCE_SAMPCAL_DONE_SHFT                                                     0x0

#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_ADDR(x)                                                     ((x) + 0x00000218)
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_RMSK                                                               0x3
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_ADDR(x), HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_RMSK)
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_ADDR(x), m)
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_ADDR(x),v)
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_ADDR(x),m,v,HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_IN(x))
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_SAMPCAL_TAP1_OVERWRITE_B_BMSK                                      0x2
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_SAMPCAL_TAP1_OVERWRITE_B_SHFT                                      0x1
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_SAMPCAL_EDAC_OVERWRITE_B_BMSK                                      0x1
#define HWIO_RX_SAMPCAL_EDAC_TAP1_INITB_SAMPCAL_EDAC_OVERWRITE_B_SHFT                                      0x0

#define HWIO_RX_SAMPCAL_TSETTLE_ADDR(x)                                                             ((x) + 0x0000021c)
#define HWIO_RX_SAMPCAL_TSETTLE_RMSK                                                                      0xff
#define HWIO_RX_SAMPCAL_TSETTLE_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_TSETTLE_ADDR(x), HWIO_RX_SAMPCAL_TSETTLE_RMSK)
#define HWIO_RX_SAMPCAL_TSETTLE_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_TSETTLE_ADDR(x), m)
#define HWIO_RX_SAMPCAL_TSETTLE_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_TSETTLE_ADDR(x),v)
#define HWIO_RX_SAMPCAL_TSETTLE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_TSETTLE_ADDR(x),m,v,HWIO_RX_SAMPCAL_TSETTLE_IN(x))
#define HWIO_RX_SAMPCAL_TSETTLE_SAMPCAL_TSETTLE_BMSK                                                      0xff
#define HWIO_RX_SAMPCAL_TSETTLE_SAMPCAL_TSETTLE_SHFT                                                       0x0

#define HWIO_RX_SAMPCAL_ENDSAMP1_ADDR(x)                                                            ((x) + 0x00000220)
#define HWIO_RX_SAMPCAL_ENDSAMP1_RMSK                                                                     0xff
#define HWIO_RX_SAMPCAL_ENDSAMP1_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_ENDSAMP1_ADDR(x), HWIO_RX_SAMPCAL_ENDSAMP1_RMSK)
#define HWIO_RX_SAMPCAL_ENDSAMP1_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_ENDSAMP1_ADDR(x), m)
#define HWIO_RX_SAMPCAL_ENDSAMP1_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_ENDSAMP1_ADDR(x),v)
#define HWIO_RX_SAMPCAL_ENDSAMP1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_ENDSAMP1_ADDR(x),m,v,HWIO_RX_SAMPCAL_ENDSAMP1_IN(x))
#define HWIO_RX_SAMPCAL_ENDSAMP1_ENDSAMP_7_0_BMSK                                                         0xff
#define HWIO_RX_SAMPCAL_ENDSAMP1_ENDSAMP_7_0_SHFT                                                          0x0

#define HWIO_RX_SAMPCAL_ENDSAMP2_ADDR(x)                                                            ((x) + 0x00000224)
#define HWIO_RX_SAMPCAL_ENDSAMP2_RMSK                                                                      0x3
#define HWIO_RX_SAMPCAL_ENDSAMP2_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_ENDSAMP2_ADDR(x), HWIO_RX_SAMPCAL_ENDSAMP2_RMSK)
#define HWIO_RX_SAMPCAL_ENDSAMP2_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_ENDSAMP2_ADDR(x), m)
#define HWIO_RX_SAMPCAL_ENDSAMP2_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_ENDSAMP2_ADDR(x),v)
#define HWIO_RX_SAMPCAL_ENDSAMP2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_ENDSAMP2_ADDR(x),m,v,HWIO_RX_SAMPCAL_ENDSAMP2_IN(x))
#define HWIO_RX_SAMPCAL_ENDSAMP2_ENDSAMP_9_8_BMSK                                                          0x3
#define HWIO_RX_SAMPCAL_ENDSAMP2_ENDSAMP_9_8_SHFT                                                          0x0

#define HWIO_RX_SAMPCAL_MIDPOINT1_ADDR(x)                                                           ((x) + 0x00000228)
#define HWIO_RX_SAMPCAL_MIDPOINT1_RMSK                                                                    0xff
#define HWIO_RX_SAMPCAL_MIDPOINT1_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_MIDPOINT1_ADDR(x), HWIO_RX_SAMPCAL_MIDPOINT1_RMSK)
#define HWIO_RX_SAMPCAL_MIDPOINT1_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_MIDPOINT1_ADDR(x), m)
#define HWIO_RX_SAMPCAL_MIDPOINT1_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_MIDPOINT1_ADDR(x),v)
#define HWIO_RX_SAMPCAL_MIDPOINT1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_MIDPOINT1_ADDR(x),m,v,HWIO_RX_SAMPCAL_MIDPOINT1_IN(x))
#define HWIO_RX_SAMPCAL_MIDPOINT1_MIDPOINT_7_0_BMSK                                                       0xff
#define HWIO_RX_SAMPCAL_MIDPOINT1_MIDPOINT_7_0_SHFT                                                        0x0

#define HWIO_RX_SAMPCAL_MIDPOINT2_ADDR(x)                                                           ((x) + 0x0000022c)
#define HWIO_RX_SAMPCAL_MIDPOINT2_RMSK                                                                     0x3
#define HWIO_RX_SAMPCAL_MIDPOINT2_IN(x)      \
        in_dword_masked(HWIO_RX_SAMPCAL_MIDPOINT2_ADDR(x), HWIO_RX_SAMPCAL_MIDPOINT2_RMSK)
#define HWIO_RX_SAMPCAL_MIDPOINT2_INM(x, m)      \
        in_dword_masked(HWIO_RX_SAMPCAL_MIDPOINT2_ADDR(x), m)
#define HWIO_RX_SAMPCAL_MIDPOINT2_OUT(x, v)      \
        out_dword(HWIO_RX_SAMPCAL_MIDPOINT2_ADDR(x),v)
#define HWIO_RX_SAMPCAL_MIDPOINT2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_SAMPCAL_MIDPOINT2_ADDR(x),m,v,HWIO_RX_SAMPCAL_MIDPOINT2_IN(x))
#define HWIO_RX_SAMPCAL_MIDPOINT2_MIDPOINT_9_8_BMSK                                                        0x3
#define HWIO_RX_SAMPCAL_MIDPOINT2_MIDPOINT_9_8_SHFT                                                        0x0

#define HWIO_SIGDET_ENABLES_ADDR(x)                                                                 ((x) + 0x00000230)
#define HWIO_SIGDET_ENABLES_RMSK                                                                          0x3f
#define HWIO_SIGDET_ENABLES_IN(x)      \
        in_dword_masked(HWIO_SIGDET_ENABLES_ADDR(x), HWIO_SIGDET_ENABLES_RMSK)
#define HWIO_SIGDET_ENABLES_INM(x, m)      \
        in_dword_masked(HWIO_SIGDET_ENABLES_ADDR(x), m)
#define HWIO_SIGDET_ENABLES_OUT(x, v)      \
        out_dword(HWIO_SIGDET_ENABLES_ADDR(x),v)
#define HWIO_SIGDET_ENABLES_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SIGDET_ENABLES_ADDR(x),m,v,HWIO_SIGDET_ENABLES_IN(x))
#define HWIO_SIGDET_ENABLES_SIGDET_LP_BYP_PS0_TO_PS2_BMSK                                                 0x20
#define HWIO_SIGDET_ENABLES_SIGDET_LP_BYP_PS0_TO_PS2_SHFT                                                  0x5
#define HWIO_SIGDET_ENABLES_SIGDET_LP_BYP_MUX_BMSK                                                        0x10
#define HWIO_SIGDET_ENABLES_SIGDET_LP_BYP_MUX_SHFT                                                         0x4
#define HWIO_SIGDET_ENABLES_SIGDET_LP_BYP_BMSK                                                             0x8
#define HWIO_SIGDET_ENABLES_SIGDET_LP_BYP_SHFT                                                             0x3
#define HWIO_SIGDET_ENABLES_SIGDET_EN_MUX_BMSK                                                             0x4
#define HWIO_SIGDET_ENABLES_SIGDET_EN_MUX_SHFT                                                             0x2
#define HWIO_SIGDET_ENABLES_SIGDET_EN_BMSK                                                                 0x2
#define HWIO_SIGDET_ENABLES_SIGDET_EN_SHFT                                                                 0x1
#define HWIO_SIGDET_ENABLES_SIGDET_FLT_BYP_BMSK                                                            0x1
#define HWIO_SIGDET_ENABLES_SIGDET_FLT_BYP_SHFT                                                            0x0

#define HWIO_SIGDET_CNTRL_ADDR(x)                                                                   ((x) + 0x00000234)
#define HWIO_SIGDET_CNTRL_RMSK                                                                            0xff
#define HWIO_SIGDET_CNTRL_IN(x)      \
        in_dword_masked(HWIO_SIGDET_CNTRL_ADDR(x), HWIO_SIGDET_CNTRL_RMSK)
#define HWIO_SIGDET_CNTRL_INM(x, m)      \
        in_dword_masked(HWIO_SIGDET_CNTRL_ADDR(x), m)
#define HWIO_SIGDET_CNTRL_OUT(x, v)      \
        out_dword(HWIO_SIGDET_CNTRL_ADDR(x),v)
#define HWIO_SIGDET_CNTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SIGDET_CNTRL_ADDR(x),m,v,HWIO_SIGDET_CNTRL_IN(x))
#define HWIO_SIGDET_CNTRL_SIGDET_LVL_BMSK                                                                 0xf0
#define HWIO_SIGDET_CNTRL_SIGDET_LVL_SHFT                                                                  0x4
#define HWIO_SIGDET_CNTRL_SIGDET_BW_CTRL_BMSK                                                              0xf
#define HWIO_SIGDET_CNTRL_SIGDET_BW_CTRL_SHFT                                                              0x0

#define HWIO_SIGDET_DEGLITCH_CNTRL_ADDR(x)                                                          ((x) + 0x00000238)
#define HWIO_SIGDET_DEGLITCH_CNTRL_RMSK                                                                   0x1f
#define HWIO_SIGDET_DEGLITCH_CNTRL_IN(x)      \
        in_dword_masked(HWIO_SIGDET_DEGLITCH_CNTRL_ADDR(x), HWIO_SIGDET_DEGLITCH_CNTRL_RMSK)
#define HWIO_SIGDET_DEGLITCH_CNTRL_INM(x, m)      \
        in_dword_masked(HWIO_SIGDET_DEGLITCH_CNTRL_ADDR(x), m)
#define HWIO_SIGDET_DEGLITCH_CNTRL_OUT(x, v)      \
        out_dword(HWIO_SIGDET_DEGLITCH_CNTRL_ADDR(x),v)
#define HWIO_SIGDET_DEGLITCH_CNTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SIGDET_DEGLITCH_CNTRL_ADDR(x),m,v,HWIO_SIGDET_DEGLITCH_CNTRL_IN(x))
#define HWIO_SIGDET_DEGLITCH_CNTRL_SIGDET_DEGLITCH_CTRL_BMSK                                              0x1e
#define HWIO_SIGDET_DEGLITCH_CNTRL_SIGDET_DEGLITCH_CTRL_SHFT                                               0x1
#define HWIO_SIGDET_DEGLITCH_CNTRL_SIGDET_DEGLITCH_BYP_BMSK                                                0x1
#define HWIO_SIGDET_DEGLITCH_CNTRL_SIGDET_DEGLITCH_BYP_SHFT                                                0x0

#define HWIO_CDR_FREEZE_UP_DN_ADDR(x)                                                               ((x) + 0x0000023c)
#define HWIO_CDR_FREEZE_UP_DN_RMSK                                                                         0x1
#define HWIO_CDR_FREEZE_UP_DN_IN(x)      \
        in_dword_masked(HWIO_CDR_FREEZE_UP_DN_ADDR(x), HWIO_CDR_FREEZE_UP_DN_RMSK)
#define HWIO_CDR_FREEZE_UP_DN_INM(x, m)      \
        in_dword_masked(HWIO_CDR_FREEZE_UP_DN_ADDR(x), m)
#define HWIO_CDR_FREEZE_UP_DN_OUT(x, v)      \
        out_dword(HWIO_CDR_FREEZE_UP_DN_ADDR(x),v)
#define HWIO_CDR_FREEZE_UP_DN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CDR_FREEZE_UP_DN_ADDR(x),m,v,HWIO_CDR_FREEZE_UP_DN_IN(x))
#define HWIO_CDR_FREEZE_UP_DN_CDR_FREEZE_BMSK                                                              0x1
#define HWIO_CDR_FREEZE_UP_DN_CDR_FREEZE_SHFT                                                              0x0

#define HWIO_JITTER_GEN_MODE_ADDR(x)                                                                ((x) + 0x00000244)
#define HWIO_JITTER_GEN_MODE_RMSK                                                                         0xff
#define HWIO_JITTER_GEN_MODE_IN(x)      \
        in_dword_masked(HWIO_JITTER_GEN_MODE_ADDR(x), HWIO_JITTER_GEN_MODE_RMSK)
#define HWIO_JITTER_GEN_MODE_INM(x, m)      \
        in_dword_masked(HWIO_JITTER_GEN_MODE_ADDR(x), m)
#define HWIO_JITTER_GEN_MODE_OUT(x, v)      \
        out_dword(HWIO_JITTER_GEN_MODE_ADDR(x),v)
#define HWIO_JITTER_GEN_MODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_JITTER_GEN_MODE_ADDR(x),m,v,HWIO_JITTER_GEN_MODE_IN(x))
#define HWIO_JITTER_GEN_MODE_PPM_CENTER_BMSK                                                              0x80
#define HWIO_JITTER_GEN_MODE_PPM_CENTER_SHFT                                                               0x7
#define HWIO_JITTER_GEN_MODE_BUJ_POLY_BMSK                                                                0x70
#define HWIO_JITTER_GEN_MODE_BUJ_POLY_SHFT                                                                 0x4
#define HWIO_JITTER_GEN_MODE_BUJ_ON_BMSK                                                                   0x8
#define HWIO_JITTER_GEN_MODE_BUJ_ON_SHFT                                                                   0x3
#define HWIO_JITTER_GEN_MODE_SJ_CENTER_BMSK                                                                0x4
#define HWIO_JITTER_GEN_MODE_SJ_CENTER_SHFT                                                                0x2
#define HWIO_JITTER_GEN_MODE_SJ_ON_BMSK                                                                    0x2
#define HWIO_JITTER_GEN_MODE_SJ_ON_SHFT                                                                    0x1
#define HWIO_JITTER_GEN_MODE_PPM_OFFSET_ON_BMSK                                                            0x1
#define HWIO_JITTER_GEN_MODE_PPM_OFFSET_ON_SHFT                                                            0x0

#define HWIO_BUJ_AMP_ADDR(x)                                                                        ((x) + 0x00000248)
#define HWIO_BUJ_AMP_RMSK                                                                                 0x1f
#define HWIO_BUJ_AMP_IN(x)      \
        in_dword_masked(HWIO_BUJ_AMP_ADDR(x), HWIO_BUJ_AMP_RMSK)
#define HWIO_BUJ_AMP_INM(x, m)      \
        in_dword_masked(HWIO_BUJ_AMP_ADDR(x), m)
#define HWIO_BUJ_AMP_OUT(x, v)      \
        out_dword(HWIO_BUJ_AMP_ADDR(x),v)
#define HWIO_BUJ_AMP_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BUJ_AMP_ADDR(x),m,v,HWIO_BUJ_AMP_IN(x))
#define HWIO_BUJ_AMP_BUJ_AMPLITUDE_BMSK                                                                   0x1f
#define HWIO_BUJ_AMP_BUJ_AMPLITUDE_SHFT                                                                    0x0

#define HWIO_SJ_AMP1_ADDR(x)                                                                        ((x) + 0x0000024c)
#define HWIO_SJ_AMP1_RMSK                                                                                 0xff
#define HWIO_SJ_AMP1_IN(x)      \
        in_dword_masked(HWIO_SJ_AMP1_ADDR(x), HWIO_SJ_AMP1_RMSK)
#define HWIO_SJ_AMP1_INM(x, m)      \
        in_dword_masked(HWIO_SJ_AMP1_ADDR(x), m)
#define HWIO_SJ_AMP1_OUT(x, v)      \
        out_dword(HWIO_SJ_AMP1_ADDR(x),v)
#define HWIO_SJ_AMP1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SJ_AMP1_ADDR(x),m,v,HWIO_SJ_AMP1_IN(x))
#define HWIO_SJ_AMP1_SJ_AMPLITUDE_7_0_BMSK                                                                0xff
#define HWIO_SJ_AMP1_SJ_AMPLITUDE_7_0_SHFT                                                                 0x0

#define HWIO_SJ_AMP2_ADDR(x)                                                                        ((x) + 0x00000250)
#define HWIO_SJ_AMP2_RMSK                                                                                 0xff
#define HWIO_SJ_AMP2_IN(x)      \
        in_dword_masked(HWIO_SJ_AMP2_ADDR(x), HWIO_SJ_AMP2_RMSK)
#define HWIO_SJ_AMP2_INM(x, m)      \
        in_dword_masked(HWIO_SJ_AMP2_ADDR(x), m)
#define HWIO_SJ_AMP2_OUT(x, v)      \
        out_dword(HWIO_SJ_AMP2_ADDR(x),v)
#define HWIO_SJ_AMP2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SJ_AMP2_ADDR(x),m,v,HWIO_SJ_AMP2_IN(x))
#define HWIO_SJ_AMP2_SJ_AMPLITUDE_15_8_BMSK                                                               0xff
#define HWIO_SJ_AMP2_SJ_AMPLITUDE_15_8_SHFT                                                                0x0

#define HWIO_SJ_PER1_ADDR(x)                                                                        ((x) + 0x00000254)
#define HWIO_SJ_PER1_RMSK                                                                                 0xff
#define HWIO_SJ_PER1_IN(x)      \
        in_dword_masked(HWIO_SJ_PER1_ADDR(x), HWIO_SJ_PER1_RMSK)
#define HWIO_SJ_PER1_INM(x, m)      \
        in_dword_masked(HWIO_SJ_PER1_ADDR(x), m)
#define HWIO_SJ_PER1_OUT(x, v)      \
        out_dword(HWIO_SJ_PER1_ADDR(x),v)
#define HWIO_SJ_PER1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SJ_PER1_ADDR(x),m,v,HWIO_SJ_PER1_IN(x))
#define HWIO_SJ_PER1_SJ_PERIOD_7_0_BMSK                                                                   0xff
#define HWIO_SJ_PER1_SJ_PERIOD_7_0_SHFT                                                                    0x0

#define HWIO_SJ_PER2_ADDR(x)                                                                        ((x) + 0x00000258)
#define HWIO_SJ_PER2_RMSK                                                                                 0xff
#define HWIO_SJ_PER2_IN(x)      \
        in_dword_masked(HWIO_SJ_PER2_ADDR(x), HWIO_SJ_PER2_RMSK)
#define HWIO_SJ_PER2_INM(x, m)      \
        in_dword_masked(HWIO_SJ_PER2_ADDR(x), m)
#define HWIO_SJ_PER2_OUT(x, v)      \
        out_dword(HWIO_SJ_PER2_ADDR(x),v)
#define HWIO_SJ_PER2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SJ_PER2_ADDR(x),m,v,HWIO_SJ_PER2_IN(x))
#define HWIO_SJ_PER2_SJ_PERIOD_15_8_BMSK                                                                  0xff
#define HWIO_SJ_PER2_SJ_PERIOD_15_8_SHFT                                                                   0x0

#define HWIO_BUJ_STEP_FREQ1_ADDR(x)                                                                 ((x) + 0x0000025c)
#define HWIO_BUJ_STEP_FREQ1_RMSK                                                                          0xff
#define HWIO_BUJ_STEP_FREQ1_IN(x)      \
        in_dword_masked(HWIO_BUJ_STEP_FREQ1_ADDR(x), HWIO_BUJ_STEP_FREQ1_RMSK)
#define HWIO_BUJ_STEP_FREQ1_INM(x, m)      \
        in_dword_masked(HWIO_BUJ_STEP_FREQ1_ADDR(x), m)
#define HWIO_BUJ_STEP_FREQ1_OUT(x, v)      \
        out_dword(HWIO_BUJ_STEP_FREQ1_ADDR(x),v)
#define HWIO_BUJ_STEP_FREQ1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BUJ_STEP_FREQ1_ADDR(x),m,v,HWIO_BUJ_STEP_FREQ1_IN(x))
#define HWIO_BUJ_STEP_FREQ1_BUJ_STEPFREQ_7_0_BMSK                                                         0xff
#define HWIO_BUJ_STEP_FREQ1_BUJ_STEPFREQ_7_0_SHFT                                                          0x0

#define HWIO_BUJ_STEP_FREQ2_ADDR(x)                                                                 ((x) + 0x00000260)
#define HWIO_BUJ_STEP_FREQ2_RMSK                                                                          0xff
#define HWIO_BUJ_STEP_FREQ2_IN(x)      \
        in_dword_masked(HWIO_BUJ_STEP_FREQ2_ADDR(x), HWIO_BUJ_STEP_FREQ2_RMSK)
#define HWIO_BUJ_STEP_FREQ2_INM(x, m)      \
        in_dword_masked(HWIO_BUJ_STEP_FREQ2_ADDR(x), m)
#define HWIO_BUJ_STEP_FREQ2_OUT(x, v)      \
        out_dword(HWIO_BUJ_STEP_FREQ2_ADDR(x),v)
#define HWIO_BUJ_STEP_FREQ2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BUJ_STEP_FREQ2_ADDR(x),m,v,HWIO_BUJ_STEP_FREQ2_IN(x))
#define HWIO_BUJ_STEP_FREQ2_BUJ_STEPFREQ_15_8_BMSK                                                        0xff
#define HWIO_BUJ_STEP_FREQ2_BUJ_STEPFREQ_15_8_SHFT                                                         0x0

#define HWIO_PPM_OFFSET1_ADDR(x)                                                                    ((x) + 0x00000264)
#define HWIO_PPM_OFFSET1_RMSK                                                                             0xff
#define HWIO_PPM_OFFSET1_IN(x)      \
        in_dword_masked(HWIO_PPM_OFFSET1_ADDR(x), HWIO_PPM_OFFSET1_RMSK)
#define HWIO_PPM_OFFSET1_INM(x, m)      \
        in_dword_masked(HWIO_PPM_OFFSET1_ADDR(x), m)
#define HWIO_PPM_OFFSET1_OUT(x, v)      \
        out_dword(HWIO_PPM_OFFSET1_ADDR(x),v)
#define HWIO_PPM_OFFSET1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PPM_OFFSET1_ADDR(x),m,v,HWIO_PPM_OFFSET1_IN(x))
#define HWIO_PPM_OFFSET1_PPM_OFFSET_7_0_BMSK                                                              0xff
#define HWIO_PPM_OFFSET1_PPM_OFFSET_7_0_SHFT                                                               0x0

#define HWIO_PPM_OFFSET2_ADDR(x)                                                                    ((x) + 0x00000268)
#define HWIO_PPM_OFFSET2_RMSK                                                                             0xff
#define HWIO_PPM_OFFSET2_IN(x)      \
        in_dword_masked(HWIO_PPM_OFFSET2_ADDR(x), HWIO_PPM_OFFSET2_RMSK)
#define HWIO_PPM_OFFSET2_INM(x, m)      \
        in_dword_masked(HWIO_PPM_OFFSET2_ADDR(x), m)
#define HWIO_PPM_OFFSET2_OUT(x, v)      \
        out_dword(HWIO_PPM_OFFSET2_ADDR(x),v)
#define HWIO_PPM_OFFSET2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PPM_OFFSET2_ADDR(x),m,v,HWIO_PPM_OFFSET2_IN(x))
#define HWIO_PPM_OFFSET2_PPM_OFFSET_15_8_BMSK                                                             0xff
#define HWIO_PPM_OFFSET2_PPM_OFFSET_15_8_SHFT                                                              0x0

#define HWIO_SIGN_PPM_PERIOD1_ADDR(x)                                                               ((x) + 0x0000026c)
#define HWIO_SIGN_PPM_PERIOD1_RMSK                                                                        0xff
#define HWIO_SIGN_PPM_PERIOD1_IN(x)      \
        in_dword_masked(HWIO_SIGN_PPM_PERIOD1_ADDR(x), HWIO_SIGN_PPM_PERIOD1_RMSK)
#define HWIO_SIGN_PPM_PERIOD1_INM(x, m)      \
        in_dword_masked(HWIO_SIGN_PPM_PERIOD1_ADDR(x), m)
#define HWIO_SIGN_PPM_PERIOD1_OUT(x, v)      \
        out_dword(HWIO_SIGN_PPM_PERIOD1_ADDR(x),v)
#define HWIO_SIGN_PPM_PERIOD1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SIGN_PPM_PERIOD1_ADDR(x),m,v,HWIO_SIGN_PPM_PERIOD1_IN(x))
#define HWIO_SIGN_PPM_PERIOD1_SIGN_PPM_PERIOD_7_0_BMSK                                                    0xff
#define HWIO_SIGN_PPM_PERIOD1_SIGN_PPM_PERIOD_7_0_SHFT                                                     0x0

#define HWIO_SIGN_PPM_PERIOD2_ADDR(x)                                                               ((x) + 0x00000270)
#define HWIO_SIGN_PPM_PERIOD2_RMSK                                                                        0xff
#define HWIO_SIGN_PPM_PERIOD2_IN(x)      \
        in_dword_masked(HWIO_SIGN_PPM_PERIOD2_ADDR(x), HWIO_SIGN_PPM_PERIOD2_RMSK)
#define HWIO_SIGN_PPM_PERIOD2_INM(x, m)      \
        in_dword_masked(HWIO_SIGN_PPM_PERIOD2_ADDR(x), m)
#define HWIO_SIGN_PPM_PERIOD2_OUT(x, v)      \
        out_dword(HWIO_SIGN_PPM_PERIOD2_ADDR(x),v)
#define HWIO_SIGN_PPM_PERIOD2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SIGN_PPM_PERIOD2_ADDR(x),m,v,HWIO_SIGN_PPM_PERIOD2_IN(x))
#define HWIO_SIGN_PPM_PERIOD2_SIGN_PPM_PERIOD_15_8_BMSK                                                   0xff
#define HWIO_SIGN_PPM_PERIOD2_SIGN_PPM_PERIOD_15_8_SHFT                                                    0x0

#define HWIO_PS1B_EXIT_LAT_MODE0_ADDR(x)                                                            ((x) + 0x00000274)
#define HWIO_PS1B_EXIT_LAT_MODE0_RMSK                                                                     0xff
#define HWIO_PS1B_EXIT_LAT_MODE0_IN(x)      \
        in_dword_masked(HWIO_PS1B_EXIT_LAT_MODE0_ADDR(x), HWIO_PS1B_EXIT_LAT_MODE0_RMSK)
#define HWIO_PS1B_EXIT_LAT_MODE0_INM(x, m)      \
        in_dword_masked(HWIO_PS1B_EXIT_LAT_MODE0_ADDR(x), m)
#define HWIO_PS1B_EXIT_LAT_MODE0_OUT(x, v)      \
        out_dword(HWIO_PS1B_EXIT_LAT_MODE0_ADDR(x),v)
#define HWIO_PS1B_EXIT_LAT_MODE0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PS1B_EXIT_LAT_MODE0_ADDR(x),m,v,HWIO_PS1B_EXIT_LAT_MODE0_IN(x))
#define HWIO_PS1B_EXIT_LAT_MODE0_PS1B_WAIT_MODE0_BMSK                                                     0xff
#define HWIO_PS1B_EXIT_LAT_MODE0_PS1B_WAIT_MODE0_SHFT                                                      0x0

#define HWIO_PS1B_EXIT_LAT_MODE1_ADDR(x)                                                            ((x) + 0x00000278)
#define HWIO_PS1B_EXIT_LAT_MODE1_RMSK                                                                     0xff
#define HWIO_PS1B_EXIT_LAT_MODE1_IN(x)      \
        in_dword_masked(HWIO_PS1B_EXIT_LAT_MODE1_ADDR(x), HWIO_PS1B_EXIT_LAT_MODE1_RMSK)
#define HWIO_PS1B_EXIT_LAT_MODE1_INM(x, m)      \
        in_dword_masked(HWIO_PS1B_EXIT_LAT_MODE1_ADDR(x), m)
#define HWIO_PS1B_EXIT_LAT_MODE1_OUT(x, v)      \
        out_dword(HWIO_PS1B_EXIT_LAT_MODE1_ADDR(x),v)
#define HWIO_PS1B_EXIT_LAT_MODE1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PS1B_EXIT_LAT_MODE1_ADDR(x),m,v,HWIO_PS1B_EXIT_LAT_MODE1_IN(x))
#define HWIO_PS1B_EXIT_LAT_MODE1_PS1B_WAIT_MODE1_BMSK                                                     0xff
#define HWIO_PS1B_EXIT_LAT_MODE1_PS1B_WAIT_MODE1_SHFT                                                      0x0

#define HWIO_PS1B_EXIT_LAT_MODE2_ADDR(x)                                                            ((x) + 0x0000027c)
#define HWIO_PS1B_EXIT_LAT_MODE2_RMSK                                                                     0xff
#define HWIO_PS1B_EXIT_LAT_MODE2_IN(x)      \
        in_dword_masked(HWIO_PS1B_EXIT_LAT_MODE2_ADDR(x), HWIO_PS1B_EXIT_LAT_MODE2_RMSK)
#define HWIO_PS1B_EXIT_LAT_MODE2_INM(x, m)      \
        in_dword_masked(HWIO_PS1B_EXIT_LAT_MODE2_ADDR(x), m)
#define HWIO_PS1B_EXIT_LAT_MODE2_OUT(x, v)      \
        out_dword(HWIO_PS1B_EXIT_LAT_MODE2_ADDR(x),v)
#define HWIO_PS1B_EXIT_LAT_MODE2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PS1B_EXIT_LAT_MODE2_ADDR(x),m,v,HWIO_PS1B_EXIT_LAT_MODE2_IN(x))
#define HWIO_PS1B_EXIT_LAT_MODE2_PS1B_WAIT_MODE2_BMSK                                                     0xff
#define HWIO_PS1B_EXIT_LAT_MODE2_PS1B_WAIT_MODE2_SHFT                                                      0x0

#define HWIO_DLL_CTUNE_OVRWRT_ADDR(x)                                                               ((x) + 0x00000280)
#define HWIO_DLL_CTUNE_OVRWRT_RMSK                                                                        0x3f
#define HWIO_DLL_CTUNE_OVRWRT_IN(x)      \
        in_dword_masked(HWIO_DLL_CTUNE_OVRWRT_ADDR(x), HWIO_DLL_CTUNE_OVRWRT_RMSK)
#define HWIO_DLL_CTUNE_OVRWRT_INM(x, m)      \
        in_dword_masked(HWIO_DLL_CTUNE_OVRWRT_ADDR(x), m)
#define HWIO_DLL_CTUNE_OVRWRT_OUT(x, v)      \
        out_dword(HWIO_DLL_CTUNE_OVRWRT_ADDR(x),v)
#define HWIO_DLL_CTUNE_OVRWRT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL_CTUNE_OVRWRT_ADDR(x),m,v,HWIO_DLL_CTUNE_OVRWRT_IN(x))
#define HWIO_DLL_CTUNE_OVRWRT_DLL_CTUNE_OVRWRT_BMSK                                                       0x20
#define HWIO_DLL_CTUNE_OVRWRT_DLL_CTUNE_OVRWRT_SHFT                                                        0x5
#define HWIO_DLL_CTUNE_OVRWRT_DLL_CTUNE_OVRWRT_VAL_BMSK                                                   0x1f
#define HWIO_DLL_CTUNE_OVRWRT_DLL_CTUNE_OVRWRT_VAL_SHFT                                                    0x0

#define HWIO_DLL0_FTUNE_INITVAL_ADDR(x)                                                             ((x) + 0x00000284)
#define HWIO_DLL0_FTUNE_INITVAL_RMSK                                                                      0x7f
#define HWIO_DLL0_FTUNE_INITVAL_IN(x)      \
        in_dword_masked(HWIO_DLL0_FTUNE_INITVAL_ADDR(x), HWIO_DLL0_FTUNE_INITVAL_RMSK)
#define HWIO_DLL0_FTUNE_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_DLL0_FTUNE_INITVAL_ADDR(x), m)
#define HWIO_DLL0_FTUNE_INITVAL_OUT(x, v)      \
        out_dword(HWIO_DLL0_FTUNE_INITVAL_ADDR(x),v)
#define HWIO_DLL0_FTUNE_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL0_FTUNE_INITVAL_ADDR(x),m,v,HWIO_DLL0_FTUNE_INITVAL_IN(x))
#define HWIO_DLL0_FTUNE_INITVAL_DLL0_FTUNE_INITB_MUX_BMSK                                                 0x40
#define HWIO_DLL0_FTUNE_INITVAL_DLL0_FTUNE_INITB_MUX_SHFT                                                  0x6
#define HWIO_DLL0_FTUNE_INITVAL_DLL0_FTUNE_INITB_BMSK                                                     0x20
#define HWIO_DLL0_FTUNE_INITVAL_DLL0_FTUNE_INITB_SHFT                                                      0x5
#define HWIO_DLL0_FTUNE_INITVAL_DLL0_FTUNE_INITVAL_BMSK                                                   0x1f
#define HWIO_DLL0_FTUNE_INITVAL_DLL0_FTUNE_INITVAL_SHFT                                                    0x0

#define HWIO_DLL1_FTUNE_INITVAL_ADDR(x)                                                             ((x) + 0x00000288)
#define HWIO_DLL1_FTUNE_INITVAL_RMSK                                                                      0x7f
#define HWIO_DLL1_FTUNE_INITVAL_IN(x)      \
        in_dword_masked(HWIO_DLL1_FTUNE_INITVAL_ADDR(x), HWIO_DLL1_FTUNE_INITVAL_RMSK)
#define HWIO_DLL1_FTUNE_INITVAL_INM(x, m)      \
        in_dword_masked(HWIO_DLL1_FTUNE_INITVAL_ADDR(x), m)
#define HWIO_DLL1_FTUNE_INITVAL_OUT(x, v)      \
        out_dword(HWIO_DLL1_FTUNE_INITVAL_ADDR(x),v)
#define HWIO_DLL1_FTUNE_INITVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL1_FTUNE_INITVAL_ADDR(x),m,v,HWIO_DLL1_FTUNE_INITVAL_IN(x))
#define HWIO_DLL1_FTUNE_INITVAL_DLL1_FTUNE_INITB_MUX_BMSK                                                 0x40
#define HWIO_DLL1_FTUNE_INITVAL_DLL1_FTUNE_INITB_MUX_SHFT                                                  0x6
#define HWIO_DLL1_FTUNE_INITVAL_DLL1_FTUNE_INITB_BMSK                                                     0x20
#define HWIO_DLL1_FTUNE_INITVAL_DLL1_FTUNE_INITB_SHFT                                                      0x5
#define HWIO_DLL1_FTUNE_INITVAL_DLL1_FTUNE_INITVAL_BMSK                                                   0x1f
#define HWIO_DLL1_FTUNE_INITVAL_DLL1_FTUNE_INITVAL_SHFT                                                    0x0

#define HWIO_DLL0_FTUNE_GAIN_ADDR(x)                                                                ((x) + 0x0000028c)
#define HWIO_DLL0_FTUNE_GAIN_RMSK                                                                         0x1f
#define HWIO_DLL0_FTUNE_GAIN_IN(x)      \
        in_dword_masked(HWIO_DLL0_FTUNE_GAIN_ADDR(x), HWIO_DLL0_FTUNE_GAIN_RMSK)
#define HWIO_DLL0_FTUNE_GAIN_INM(x, m)      \
        in_dword_masked(HWIO_DLL0_FTUNE_GAIN_ADDR(x), m)
#define HWIO_DLL0_FTUNE_GAIN_OUT(x, v)      \
        out_dword(HWIO_DLL0_FTUNE_GAIN_ADDR(x),v)
#define HWIO_DLL0_FTUNE_GAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL0_FTUNE_GAIN_ADDR(x),m,v,HWIO_DLL0_FTUNE_GAIN_IN(x))
#define HWIO_DLL0_FTUNE_GAIN_DLL0_FTUNE_GAIN_BMSK                                                         0x1f
#define HWIO_DLL0_FTUNE_GAIN_DLL0_FTUNE_GAIN_SHFT                                                          0x0

#define HWIO_DLL1_FTUNE_GAIN_ADDR(x)                                                                ((x) + 0x00000290)
#define HWIO_DLL1_FTUNE_GAIN_RMSK                                                                         0x1f
#define HWIO_DLL1_FTUNE_GAIN_IN(x)      \
        in_dword_masked(HWIO_DLL1_FTUNE_GAIN_ADDR(x), HWIO_DLL1_FTUNE_GAIN_RMSK)
#define HWIO_DLL1_FTUNE_GAIN_INM(x, m)      \
        in_dword_masked(HWIO_DLL1_FTUNE_GAIN_ADDR(x), m)
#define HWIO_DLL1_FTUNE_GAIN_OUT(x, v)      \
        out_dword(HWIO_DLL1_FTUNE_GAIN_ADDR(x),v)
#define HWIO_DLL1_FTUNE_GAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL1_FTUNE_GAIN_ADDR(x),m,v,HWIO_DLL1_FTUNE_GAIN_IN(x))
#define HWIO_DLL1_FTUNE_GAIN_DLL1_FTUNE_GAIN_BMSK                                                         0x1f
#define HWIO_DLL1_FTUNE_GAIN_DLL1_FTUNE_GAIN_SHFT                                                          0x0

#define HWIO_DLL_ENABLE_WAIT_ADDR(x)                                                                ((x) + 0x00000294)
#define HWIO_DLL_ENABLE_WAIT_RMSK                                                                         0x1f
#define HWIO_DLL_ENABLE_WAIT_IN(x)      \
        in_dword_masked(HWIO_DLL_ENABLE_WAIT_ADDR(x), HWIO_DLL_ENABLE_WAIT_RMSK)
#define HWIO_DLL_ENABLE_WAIT_INM(x, m)      \
        in_dword_masked(HWIO_DLL_ENABLE_WAIT_ADDR(x), m)
#define HWIO_DLL_ENABLE_WAIT_OUT(x, v)      \
        out_dword(HWIO_DLL_ENABLE_WAIT_ADDR(x),v)
#define HWIO_DLL_ENABLE_WAIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL_ENABLE_WAIT_ADDR(x),m,v,HWIO_DLL_ENABLE_WAIT_IN(x))
#define HWIO_DLL_ENABLE_WAIT_TRAN_EN_DLL_BMSK                                                             0x10
#define HWIO_DLL_ENABLE_WAIT_TRAN_EN_DLL_SHFT                                                              0x4
#define HWIO_DLL_ENABLE_WAIT_DLL_CAL_WAITTIME_BMSK                                                         0xc
#define HWIO_DLL_ENABLE_WAIT_DLL_CAL_WAITTIME_SHFT                                                         0x2
#define HWIO_DLL_ENABLE_WAIT_DLL_CTUNE_EN_MUX_BMSK                                                         0x2
#define HWIO_DLL_ENABLE_WAIT_DLL_CTUNE_EN_MUX_SHFT                                                         0x1
#define HWIO_DLL_ENABLE_WAIT_DLL_CTUNE_EN_BMSK                                                             0x1
#define HWIO_DLL_ENABLE_WAIT_DLL_CTUNE_EN_SHFT                                                             0x0

#define HWIO_DLL_CTUNE_OFFSET_ADDR(x)                                                               ((x) + 0x00000298)
#define HWIO_DLL_CTUNE_OFFSET_RMSK                                                                        0x1f
#define HWIO_DLL_CTUNE_OFFSET_IN(x)      \
        in_dword_masked(HWIO_DLL_CTUNE_OFFSET_ADDR(x), HWIO_DLL_CTUNE_OFFSET_RMSK)
#define HWIO_DLL_CTUNE_OFFSET_INM(x, m)      \
        in_dword_masked(HWIO_DLL_CTUNE_OFFSET_ADDR(x), m)
#define HWIO_DLL_CTUNE_OFFSET_OUT(x, v)      \
        out_dword(HWIO_DLL_CTUNE_OFFSET_ADDR(x),v)
#define HWIO_DLL_CTUNE_OFFSET_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL_CTUNE_OFFSET_ADDR(x),m,v,HWIO_DLL_CTUNE_OFFSET_IN(x))
#define HWIO_DLL_CTUNE_OFFSET_DLL_CTUNE_OFFSET_BMSK                                                       0x1f
#define HWIO_DLL_CTUNE_OFFSET_DLL_CTUNE_OFFSET_SHFT                                                        0x0

#define HWIO_DLL_CTUNE_CTRL_ADDR(x)                                                                 ((x) + 0x0000029c)
#define HWIO_DLL_CTUNE_CTRL_RMSK                                                                           0x3
#define HWIO_DLL_CTUNE_CTRL_IN(x)      \
        in_dword_masked(HWIO_DLL_CTUNE_CTRL_ADDR(x), HWIO_DLL_CTUNE_CTRL_RMSK)
#define HWIO_DLL_CTUNE_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_DLL_CTUNE_CTRL_ADDR(x), m)
#define HWIO_DLL_CTUNE_CTRL_OUT(x, v)      \
        out_dword(HWIO_DLL_CTUNE_CTRL_ADDR(x),v)
#define HWIO_DLL_CTUNE_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL_CTUNE_CTRL_ADDR(x),m,v,HWIO_DLL_CTUNE_CTRL_IN(x))
#define HWIO_DLL_CTUNE_CTRL_CTUNE_FORCE_CAL_DONE_BMSK                                                      0x2
#define HWIO_DLL_CTUNE_CTRL_CTUNE_FORCE_CAL_DONE_SHFT                                                      0x1
#define HWIO_DLL_CTUNE_CTRL_CTUNE_SIGERR_POL_BMSK                                                          0x1
#define HWIO_DLL_CTUNE_CTRL_CTUNE_SIGERR_POL_SHFT                                                          0x0

#define HWIO_DCC_INIT_ADDR(x)                                                                       ((x) + 0x000002a0)
#define HWIO_DCC_INIT_RMSK                                                                                0x7f
#define HWIO_DCC_INIT_IN(x)      \
        in_dword_masked(HWIO_DCC_INIT_ADDR(x), HWIO_DCC_INIT_RMSK)
#define HWIO_DCC_INIT_INM(x, m)      \
        in_dword_masked(HWIO_DCC_INIT_ADDR(x), m)
#define HWIO_DCC_INIT_OUT(x, v)      \
        out_dword(HWIO_DCC_INIT_ADDR(x),v)
#define HWIO_DCC_INIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DCC_INIT_ADDR(x),m,v,HWIO_DCC_INIT_IN(x))
#define HWIO_DCC_INIT_DCC_INITB_MUX_BMSK                                                                  0x40
#define HWIO_DCC_INIT_DCC_INITB_MUX_SHFT                                                                   0x6
#define HWIO_DCC_INIT_DCC_INITB_BMSK                                                                      0x20
#define HWIO_DCC_INIT_DCC_INITB_SHFT                                                                       0x5
#define HWIO_DCC_INIT_DCC_INITVAL_BMSK                                                                    0x1f
#define HWIO_DCC_INIT_DCC_INITVAL_SHFT                                                                     0x0

#define HWIO_DCC_GAIN_ADDR(x)                                                                       ((x) + 0x000002a4)
#define HWIO_DCC_GAIN_RMSK                                                                                0x1f
#define HWIO_DCC_GAIN_IN(x)      \
        in_dword_masked(HWIO_DCC_GAIN_ADDR(x), HWIO_DCC_GAIN_RMSK)
#define HWIO_DCC_GAIN_INM(x, m)      \
        in_dword_masked(HWIO_DCC_GAIN_ADDR(x), m)
#define HWIO_DCC_GAIN_OUT(x, v)      \
        out_dword(HWIO_DCC_GAIN_ADDR(x),v)
#define HWIO_DCC_GAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DCC_GAIN_ADDR(x),m,v,HWIO_DCC_GAIN_IN(x))
#define HWIO_DCC_GAIN_DCC_GAIN_BMSK                                                                       0x1f
#define HWIO_DCC_GAIN_DCC_GAIN_SHFT                                                                        0x0

#define HWIO_RSM_START_ADDR(x)                                                                      ((x) + 0x000002a8)
#define HWIO_RSM_START_RMSK                                                                                0x1
#define HWIO_RSM_START_IN(x)      \
        in_dword_masked(HWIO_RSM_START_ADDR(x), HWIO_RSM_START_RMSK)
#define HWIO_RSM_START_INM(x, m)      \
        in_dword_masked(HWIO_RSM_START_ADDR(x), m)
#define HWIO_RSM_START_OUT(x, v)      \
        out_dword(HWIO_RSM_START_ADDR(x),v)
#define HWIO_RSM_START_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RSM_START_ADDR(x),m,v,HWIO_RSM_START_IN(x))
#define HWIO_RSM_START_RSM_START_BMSK                                                                      0x1
#define HWIO_RSM_START_RSM_START_SHFT                                                                      0x0

#define HWIO_RX_EN_SIGNAL_ADDR(x)                                                                   ((x) + 0x000002ac)
#define HWIO_RX_EN_SIGNAL_RMSK                                                                            0xff
#define HWIO_RX_EN_SIGNAL_IN(x)      \
        in_dword_masked(HWIO_RX_EN_SIGNAL_ADDR(x), HWIO_RX_EN_SIGNAL_RMSK)
#define HWIO_RX_EN_SIGNAL_INM(x, m)      \
        in_dword_masked(HWIO_RX_EN_SIGNAL_ADDR(x), m)
#define HWIO_RX_EN_SIGNAL_OUT(x, v)      \
        out_dword(HWIO_RX_EN_SIGNAL_ADDR(x),v)
#define HWIO_RX_EN_SIGNAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_EN_SIGNAL_ADDR(x),m,v,HWIO_RX_EN_SIGNAL_IN(x))
#define HWIO_RX_EN_SIGNAL_SIGDET_LP_BYP_PS4_BMSK                                                          0x80
#define HWIO_RX_EN_SIGNAL_SIGDET_LP_BYP_PS4_SHFT                                                           0x7
#define HWIO_RX_EN_SIGNAL_SIGDET_EN_PS0_TO_PS2_BMSK                                                       0x40
#define HWIO_RX_EN_SIGNAL_SIGDET_EN_PS0_TO_PS2_SHFT                                                        0x6
#define HWIO_RX_EN_SIGNAL_EN_ACCOUPLEVCM_SW_MUX_BMSK                                                      0x20
#define HWIO_RX_EN_SIGNAL_EN_ACCOUPLEVCM_SW_MUX_SHFT                                                       0x5
#define HWIO_RX_EN_SIGNAL_EN_ACCOUPLEVCM_SW_BMSK                                                          0x10
#define HWIO_RX_EN_SIGNAL_EN_ACCOUPLEVCM_SW_SHFT                                                           0x4
#define HWIO_RX_EN_SIGNAL_RX_SYNC_EN_BMSK                                                                  0x8
#define HWIO_RX_EN_SIGNAL_RX_SYNC_EN_SHFT                                                                  0x3
#define HWIO_RX_EN_SIGNAL_RXTERM_HIGHZ_PS5_BMSK                                                            0x4
#define HWIO_RX_EN_SIGNAL_RXTERM_HIGHZ_PS5_SHFT                                                            0x2
#define HWIO_RX_EN_SIGNAL_SIGDET_EN_PS3_BMSK                                                               0x2
#define HWIO_RX_EN_SIGNAL_SIGDET_EN_PS3_SHFT                                                               0x1
#define HWIO_RX_EN_SIGNAL_EN_ACCOUPLE_VCM_PS3_BMSK                                                         0x1
#define HWIO_RX_EN_SIGNAL_EN_ACCOUPLE_VCM_PS3_SHFT                                                         0x0

#define HWIO_PSM_RX_EN_CAL_ADDR(x)                                                                  ((x) + 0x000002b0)
#define HWIO_PSM_RX_EN_CAL_RMSK                                                                           0x1f
#define HWIO_PSM_RX_EN_CAL_IN(x)      \
        in_dword_masked(HWIO_PSM_RX_EN_CAL_ADDR(x), HWIO_PSM_RX_EN_CAL_RMSK)
#define HWIO_PSM_RX_EN_CAL_INM(x, m)      \
        in_dword_masked(HWIO_PSM_RX_EN_CAL_ADDR(x), m)
#define HWIO_PSM_RX_EN_CAL_OUT(x, v)      \
        out_dword(HWIO_PSM_RX_EN_CAL_ADDR(x),v)
#define HWIO_PSM_RX_EN_CAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSM_RX_EN_CAL_ADDR(x),m,v,HWIO_PSM_RX_EN_CAL_IN(x))
#define HWIO_PSM_RX_EN_CAL_RUN_SAMP_CAL_TS0A_BMSK                                                         0x10
#define HWIO_PSM_RX_EN_CAL_RUN_SAMP_CAL_TS0A_SHFT                                                          0x4
#define HWIO_PSM_RX_EN_CAL_RUN_DLL_CAL_TS1UP_BMSK                                                          0x8
#define HWIO_PSM_RX_EN_CAL_RUN_DLL_CAL_TS1UP_SHFT                                                          0x3
#define HWIO_PSM_RX_EN_CAL_RUN_DLL_CAL_TS1DN_BMSK                                                          0x4
#define HWIO_PSM_RX_EN_CAL_RUN_DLL_CAL_TS1DN_SHFT                                                          0x2
#define HWIO_PSM_RX_EN_CAL_RUN_SAMP_CAL_TS1UP_BMSK                                                         0x2
#define HWIO_PSM_RX_EN_CAL_RUN_SAMP_CAL_TS1UP_SHFT                                                         0x1
#define HWIO_PSM_RX_EN_CAL_RUN_SAMP_CAL_TS1DN_BMSK                                                         0x1
#define HWIO_PSM_RX_EN_CAL_RUN_SAMP_CAL_TS1DN_SHFT                                                         0x0

#define HWIO_CLK_SHIFT_ADDR(x)                                                                      ((x) + 0x000002b4)
#define HWIO_CLK_SHIFT_RMSK                                                                               0x7f
#define HWIO_CLK_SHIFT_IN(x)      \
        in_dword_masked(HWIO_CLK_SHIFT_ADDR(x), HWIO_CLK_SHIFT_RMSK)
#define HWIO_CLK_SHIFT_INM(x, m)      \
        in_dword_masked(HWIO_CLK_SHIFT_ADDR(x), m)
#define HWIO_CLK_SHIFT_OUT(x, v)      \
        out_dword(HWIO_CLK_SHIFT_ADDR(x),v)
#define HWIO_CLK_SHIFT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CLK_SHIFT_ADDR(x),m,v,HWIO_CLK_SHIFT_IN(x))
#define HWIO_CLK_SHIFT_EN_SHIFT13_BMSK                                                                    0x40
#define HWIO_CLK_SHIFT_EN_SHIFT13_SHFT                                                                     0x6
#define HWIO_CLK_SHIFT_EN_SHIFT02_BMSK                                                                    0x20
#define HWIO_CLK_SHIFT_EN_SHIFT02_SHFT                                                                     0x5
#define HWIO_CLK_SHIFT_CLKSHIFT_IGEAR_BMSK                                                                0x1f
#define HWIO_CLK_SHIFT_CLKSHIFT_IGEAR_SHFT                                                                 0x0

#define HWIO_RX_MISC_CNTRL0_ADDR(x)                                                                 ((x) + 0x000002b8)
#define HWIO_RX_MISC_CNTRL0_RMSK                                                                          0xff
#define HWIO_RX_MISC_CNTRL0_IN(x)      \
        in_dword_masked(HWIO_RX_MISC_CNTRL0_ADDR(x), HWIO_RX_MISC_CNTRL0_RMSK)
#define HWIO_RX_MISC_CNTRL0_INM(x, m)      \
        in_dword_masked(HWIO_RX_MISC_CNTRL0_ADDR(x), m)
#define HWIO_RX_MISC_CNTRL0_OUT(x, v)      \
        out_dword(HWIO_RX_MISC_CNTRL0_ADDR(x),v)
#define HWIO_RX_MISC_CNTRL0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_MISC_CNTRL0_ADDR(x),m,v,HWIO_RX_MISC_CNTRL0_IN(x))
#define HWIO_RX_MISC_CNTRL0_INVERT_PCS_RX_CLK_BMSK                                                        0x80
#define HWIO_RX_MISC_CNTRL0_INVERT_PCS_RX_CLK_SHFT                                                         0x7
#define HWIO_RX_MISC_CNTRL0_PWM_EN_BMSK                                                                   0x40
#define HWIO_RX_MISC_CNTRL0_PWM_EN_SHFT                                                                    0x6
#define HWIO_RX_MISC_CNTRL0_RXBIAS_SEL_BMSK                                                               0x30
#define HWIO_RX_MISC_CNTRL0_RXBIAS_SEL_SHFT                                                                0x4
#define HWIO_RX_MISC_CNTRL0_EBDAC_SIGN_BMSK                                                                0x8
#define HWIO_RX_MISC_CNTRL0_EBDAC_SIGN_SHFT                                                                0x3
#define HWIO_RX_MISC_CNTRL0_EDAC_SIGN_BMSK                                                                 0x4
#define HWIO_RX_MISC_CNTRL0_EDAC_SIGN_SHFT                                                                 0x2
#define HWIO_RX_MISC_CNTRL0_EN_AUXTAP1SIGN_INVERT_BMSK                                                     0x2
#define HWIO_RX_MISC_CNTRL0_EN_AUXTAP1SIGN_INVERT_SHFT                                                     0x1
#define HWIO_RX_MISC_CNTRL0_EN_DAC_CHOPPING_BMSK                                                           0x1
#define HWIO_RX_MISC_CNTRL0_EN_DAC_CHOPPING_SHFT                                                           0x0

#define HWIO_RX_MISC_CNTRL1_ADDR(x)                                                                 ((x) + 0x000002bc)
#define HWIO_RX_MISC_CNTRL1_RMSK                                                                          0xff
#define HWIO_RX_MISC_CNTRL1_IN(x)      \
        in_dword_masked(HWIO_RX_MISC_CNTRL1_ADDR(x), HWIO_RX_MISC_CNTRL1_RMSK)
#define HWIO_RX_MISC_CNTRL1_INM(x, m)      \
        in_dword_masked(HWIO_RX_MISC_CNTRL1_ADDR(x), m)
#define HWIO_RX_MISC_CNTRL1_OUT(x, v)      \
        out_dword(HWIO_RX_MISC_CNTRL1_ADDR(x),v)
#define HWIO_RX_MISC_CNTRL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_MISC_CNTRL1_ADDR(x),m,v,HWIO_RX_MISC_CNTRL1_IN(x))
#define HWIO_RX_MISC_CNTRL1_RX_CTRL_BMSK                                                                  0xff
#define HWIO_RX_MISC_CNTRL1_RX_CTRL_SHFT                                                                   0x0

#define HWIO_TS0_TIMER_ADDR(x)                                                                      ((x) + 0x000002c0)
#define HWIO_TS0_TIMER_RMSK                                                                               0xff
#define HWIO_TS0_TIMER_IN(x)      \
        in_dword_masked(HWIO_TS0_TIMER_ADDR(x), HWIO_TS0_TIMER_RMSK)
#define HWIO_TS0_TIMER_INM(x, m)      \
        in_dword_masked(HWIO_TS0_TIMER_ADDR(x), m)
#define HWIO_TS0_TIMER_OUT(x, v)      \
        out_dword(HWIO_TS0_TIMER_ADDR(x),v)
#define HWIO_TS0_TIMER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TS0_TIMER_ADDR(x),m,v,HWIO_TS0_TIMER_IN(x))
#define HWIO_TS0_TIMER_TS0A_DLL_WAIT_BMSK                                                                 0xff
#define HWIO_TS0_TIMER_TS0A_DLL_WAIT_SHFT                                                                  0x0

#define HWIO_DLL_HIGHDATARATE_ADDR(x)                                                               ((x) + 0x000002c4)
#define HWIO_DLL_HIGHDATARATE_RMSK                                                                        0x3f
#define HWIO_DLL_HIGHDATARATE_IN(x)      \
        in_dword_masked(HWIO_DLL_HIGHDATARATE_ADDR(x), HWIO_DLL_HIGHDATARATE_RMSK)
#define HWIO_DLL_HIGHDATARATE_INM(x, m)      \
        in_dword_masked(HWIO_DLL_HIGHDATARATE_ADDR(x), m)
#define HWIO_DLL_HIGHDATARATE_OUT(x, v)      \
        out_dword(HWIO_DLL_HIGHDATARATE_ADDR(x),v)
#define HWIO_DLL_HIGHDATARATE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DLL_HIGHDATARATE_ADDR(x),m,v,HWIO_DLL_HIGHDATARATE_IN(x))
#define HWIO_DLL_HIGHDATARATE_DLL_HIGHDATARATE_SEL_MODE2_BMSK                                             0x30
#define HWIO_DLL_HIGHDATARATE_DLL_HIGHDATARATE_SEL_MODE2_SHFT                                              0x4
#define HWIO_DLL_HIGHDATARATE_DLL_HIGHDATARATE_SEL_MODE1_BMSK                                              0xc
#define HWIO_DLL_HIGHDATARATE_DLL_HIGHDATARATE_SEL_MODE1_SHFT                                              0x2
#define HWIO_DLL_HIGHDATARATE_DLL_HIGHDATARATE_SEL_MODE0_BMSK                                              0x3
#define HWIO_DLL_HIGHDATARATE_DLL_HIGHDATARATE_SEL_MODE0_SHFT                                              0x0

#define HWIO_DRVR_LOGIC_CLKDIV_ADDR(x)                                                              ((x) + 0x000002c8)
#define HWIO_DRVR_LOGIC_CLKDIV_RMSK                                                                       0x1f
#define HWIO_DRVR_LOGIC_CLKDIV_IN(x)      \
        in_dword_masked(HWIO_DRVR_LOGIC_CLKDIV_ADDR(x), HWIO_DRVR_LOGIC_CLKDIV_RMSK)
#define HWIO_DRVR_LOGIC_CLKDIV_INM(x, m)      \
        in_dword_masked(HWIO_DRVR_LOGIC_CLKDIV_ADDR(x), m)
#define HWIO_DRVR_LOGIC_CLKDIV_OUT(x, v)      \
        out_dword(HWIO_DRVR_LOGIC_CLKDIV_ADDR(x),v)
#define HWIO_DRVR_LOGIC_CLKDIV_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DRVR_LOGIC_CLKDIV_ADDR(x),m,v,HWIO_DRVR_LOGIC_CLKDIV_IN(x))
#define HWIO_DRVR_LOGIC_CLKDIV_DRVR_LOGIC_CLK_EN_BMSK                                                     0x10
#define HWIO_DRVR_LOGIC_CLKDIV_DRVR_LOGIC_CLK_EN_SHFT                                                      0x4
#define HWIO_DRVR_LOGIC_CLKDIV_DRVR_LOGIC_CLK_DIV_BMSK                                                     0xf
#define HWIO_DRVR_LOGIC_CLKDIV_DRVR_LOGIC_CLK_DIV_SHFT                                                     0x0

#define HWIO_RX_RESECODE_OFFSET_ADDR(x)                                                             ((x) + 0x000002cc)
#define HWIO_RX_RESECODE_OFFSET_RMSK                                                                      0x1f
#define HWIO_RX_RESECODE_OFFSET_IN(x)      \
        in_dword_masked(HWIO_RX_RESECODE_OFFSET_ADDR(x), HWIO_RX_RESECODE_OFFSET_RMSK)
#define HWIO_RX_RESECODE_OFFSET_INM(x, m)      \
        in_dword_masked(HWIO_RX_RESECODE_OFFSET_ADDR(x), m)
#define HWIO_RX_RESECODE_OFFSET_OUT(x, v)      \
        out_dword(HWIO_RX_RESECODE_OFFSET_ADDR(x),v)
#define HWIO_RX_RESECODE_OFFSET_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RX_RESECODE_OFFSET_ADDR(x),m,v,HWIO_RX_RESECODE_OFFSET_IN(x))
#define HWIO_RX_RESECODE_OFFSET_RX_RESCODE_OFFSET_BMSK                                                    0x1f
#define HWIO_RX_RESECODE_OFFSET_RX_RESCODE_OFFSET_SHFT                                                     0x0

#define HWIO_VREG_CTRL_ADDR(x)                                                                      ((x) + 0x000002d0)
#define HWIO_VREG_CTRL_RMSK                                                                                0x7
#define HWIO_VREG_CTRL_IN(x)      \
        in_dword_masked(HWIO_VREG_CTRL_ADDR(x), HWIO_VREG_CTRL_RMSK)
#define HWIO_VREG_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_VREG_CTRL_ADDR(x), m)
#define HWIO_VREG_CTRL_OUT(x, v)      \
        out_dword(HWIO_VREG_CTRL_ADDR(x),v)
#define HWIO_VREG_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VREG_CTRL_ADDR(x),m,v,HWIO_VREG_CTRL_IN(x))
#define HWIO_VREG_CTRL_EN_VREG_PS2_BMSK                                                                    0x4
#define HWIO_VREG_CTRL_EN_VREG_PS2_SHFT                                                                    0x2
#define HWIO_VREG_CTRL_EN_VREG_MUX_BMSK                                                                    0x2
#define HWIO_VREG_CTRL_EN_VREG_MUX_SHFT                                                                    0x1
#define HWIO_VREG_CTRL_EN_VREG_BMSK                                                                        0x1
#define HWIO_VREG_CTRL_EN_VREG_SHFT                                                                        0x0

#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_ADDR(x)                                                     ((x) + 0x000002d4)
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_RMSK                                                              0xff
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_IN(x)      \
        in_dword_masked(HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_ADDR(x), HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_RMSK)
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_INM(x, m)      \
        in_dword_masked(HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_ADDR(x), m)
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_OUT(x, v)      \
        out_dword(HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_ADDR(x),v)
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_ADDR(x),m,v,HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_IN(x))
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_EXIT_WAIT_PS3_PS4_BMSK                                            0xfe
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_EXIT_WAIT_PS3_PS4_SHFT                                             0x1
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_EN_ACCOUPLE_VCM_PS4_BMSK                                           0x1
#define HWIO_ACCOUPLE_VCM_EXIT_WAIT_PS4_EN_ACCOUPLE_VCM_PS4_SHFT                                           0x0

#define HWIO_TX_ADAPTOR_STATUS_ADDR(x)                                                              ((x) + 0x000002d8)
#define HWIO_TX_ADAPTOR_STATUS_RMSK                                                                       0x3f
#define HWIO_TX_ADAPTOR_STATUS_IN(x)      \
        in_dword_masked(HWIO_TX_ADAPTOR_STATUS_ADDR(x), HWIO_TX_ADAPTOR_STATUS_RMSK)
#define HWIO_TX_ADAPTOR_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_TX_ADAPTOR_STATUS_ADDR(x), m)
#define HWIO_TX_ADAPTOR_STATUS_DEC_MAIN_BMSK                                                              0x20
#define HWIO_TX_ADAPTOR_STATUS_DEC_MAIN_SHFT                                                               0x5
#define HWIO_TX_ADAPTOR_STATUS_INC_MAIN_BMSK                                                              0x10
#define HWIO_TX_ADAPTOR_STATUS_INC_MAIN_SHFT                                                               0x4
#define HWIO_TX_ADAPTOR_STATUS_DEC_POST_BMSK                                                               0x8
#define HWIO_TX_ADAPTOR_STATUS_DEC_POST_SHFT                                                               0x3
#define HWIO_TX_ADAPTOR_STATUS_INC_POST_BMSK                                                               0x4
#define HWIO_TX_ADAPTOR_STATUS_INC_POST_SHFT                                                               0x2
#define HWIO_TX_ADAPTOR_STATUS_DEC_PRE_BMSK                                                                0x2
#define HWIO_TX_ADAPTOR_STATUS_DEC_PRE_SHFT                                                                0x1
#define HWIO_TX_ADAPTOR_STATUS_INC_PRE_BMSK                                                                0x1
#define HWIO_TX_ADAPTOR_STATUS_INC_PRE_SHFT                                                                0x0

#define HWIO_CAL_STATUS_ADDR(x)                                                                     ((x) + 0x000002dc)
#define HWIO_CAL_STATUS_RMSK                                                                              0x1f
#define HWIO_CAL_STATUS_IN(x)      \
        in_dword_masked(HWIO_CAL_STATUS_ADDR(x), HWIO_CAL_STATUS_RMSK)
#define HWIO_CAL_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_CAL_STATUS_ADDR(x), m)
#define HWIO_CAL_STATUS_ADAPTATION_DONE_BMSK                                                              0x10
#define HWIO_CAL_STATUS_ADAPTATION_DONE_SHFT                                                               0x4
#define HWIO_CAL_STATUS_PWR_STATE_ACK_BMSK                                                                 0x8
#define HWIO_CAL_STATUS_PWR_STATE_ACK_SHFT                                                                 0x3
#define HWIO_CAL_STATUS_LANE_READY_BMSK                                                                    0x4
#define HWIO_CAL_STATUS_LANE_READY_SHFT                                                                    0x2
#define HWIO_CAL_STATUS_SAMPCAL_DONE_BMSK                                                                  0x2
#define HWIO_CAL_STATUS_SAMPCAL_DONE_SHFT                                                                  0x1
#define HWIO_CAL_STATUS_CTUNE_CAL_DONE_BMSK                                                                0x1
#define HWIO_CAL_STATUS_CTUNE_CAL_DONE_SHFT                                                                0x0

#define HWIO_AC_JTAG_OUT_STATUS_ADDR(x)                                                             ((x) + 0x000002e0)
#define HWIO_AC_JTAG_OUT_STATUS_RMSK                                                                      0xff
#define HWIO_AC_JTAG_OUT_STATUS_IN(x)      \
        in_dword_masked(HWIO_AC_JTAG_OUT_STATUS_ADDR(x), HWIO_AC_JTAG_OUT_STATUS_RMSK)
#define HWIO_AC_JTAG_OUT_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_AC_JTAG_OUT_STATUS_ADDR(x), m)
#define HWIO_AC_JTAG_OUT_STATUS_RSVD_BMSK                                                                 0xfc
#define HWIO_AC_JTAG_OUT_STATUS_RSVD_SHFT                                                                  0x2
#define HWIO_AC_JTAG_OUT_STATUS_AC_JTAG_OUTN_STATUS_BMSK                                                   0x2
#define HWIO_AC_JTAG_OUT_STATUS_AC_JTAG_OUTN_STATUS_SHFT                                                   0x1
#define HWIO_AC_JTAG_OUT_STATUS_AC_JTAG_OUTP_STATUS_BMSK                                                   0x1
#define HWIO_AC_JTAG_OUT_STATUS_AC_JTAG_OUTP_STATUS_SHFT                                                   0x0

#define HWIO_EOM_STATUS_ADDR(x)                                                                     ((x) + 0x000002e4)
#define HWIO_EOM_STATUS_RMSK                                                                               0xf
#define HWIO_EOM_STATUS_IN(x)      \
        in_dword_masked(HWIO_EOM_STATUS_ADDR(x), HWIO_EOM_STATUS_RMSK)
#define HWIO_EOM_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_EOM_STATUS_ADDR(x), m)
#define HWIO_EOM_STATUS_EOM_DEBUG_BMSK                                                                     0xe
#define HWIO_EOM_STATUS_EOM_DEBUG_SHFT                                                                     0x1
#define HWIO_EOM_STATUS_EOM_DONE_BMSK                                                                      0x1
#define HWIO_EOM_STATUS_EOM_DONE_SHFT                                                                      0x0

#define HWIO_EOM_ERR_CNT0_STATUS_ADDR(x)                                                            ((x) + 0x000002e8)
#define HWIO_EOM_ERR_CNT0_STATUS_RMSK                                                                     0xff
#define HWIO_EOM_ERR_CNT0_STATUS_IN(x)      \
        in_dword_masked(HWIO_EOM_ERR_CNT0_STATUS_ADDR(x), HWIO_EOM_ERR_CNT0_STATUS_RMSK)
#define HWIO_EOM_ERR_CNT0_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_EOM_ERR_CNT0_STATUS_ADDR(x), m)
#define HWIO_EOM_ERR_CNT0_STATUS_EOM_ERR_CNT_7_0_BMSK                                                     0xff
#define HWIO_EOM_ERR_CNT0_STATUS_EOM_ERR_CNT_7_0_SHFT                                                      0x0

#define HWIO_EOM_ERR_CNT1_STATUS_ADDR(x)                                                            ((x) + 0x000002ec)
#define HWIO_EOM_ERR_CNT1_STATUS_RMSK                                                                     0xff
#define HWIO_EOM_ERR_CNT1_STATUS_IN(x)      \
        in_dword_masked(HWIO_EOM_ERR_CNT1_STATUS_ADDR(x), HWIO_EOM_ERR_CNT1_STATUS_RMSK)
#define HWIO_EOM_ERR_CNT1_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_EOM_ERR_CNT1_STATUS_ADDR(x), m)
#define HWIO_EOM_ERR_CNT1_STATUS_EOM_ERR_CNT_15_8_BMSK                                                    0xff
#define HWIO_EOM_ERR_CNT1_STATUS_EOM_ERR_CNT_15_8_SHFT                                                     0x0


#endif /* __PCIEPSPLANEQDF2400_H__ */
