#ifndef __PCIEPHYPCSQDF2400HWIO_H__
#define __PCIEPHYPCSQDF2400HWIO_H__
/*
===========================================================================
*/
/**
  @file PciePhyPcsQdf2400Hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r64.0]

  This file contains HWIO register definitions for the following modules:
    PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS

  'Include' filters applied: 
  'Exclude' filters applied: DUMMY RESERVED 
*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ===========================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS
 *--------------------------------------------------------------------------*/

#define PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE                                                  (PSP0_CM_SERVER_PCIE_SW_BASE      + 0x00002800)
#define PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS                                             0x00002800

#define HWIO_PSP_PCIE_PHY_SW_RESET_ADDR(x)                                                       ((x) + 0x00000000)
#define HWIO_PSP_PCIE_PHY_SW_RESET_OFFS                                                          (0x00000000)
#define HWIO_PSP_PCIE_PHY_SW_RESET_RMSK                                                                 0x1
#define HWIO_PSP_PCIE_PHY_SW_RESET_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_SW_RESET_ADDR(x), HWIO_PSP_PCIE_PHY_SW_RESET_RMSK)
#define HWIO_PSP_PCIE_PHY_SW_RESET_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_SW_RESET_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_SW_RESET_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_SW_RESET_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_SW_RESET_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_SW_RESET_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_SW_RESET_IN(x))
#define HWIO_PSP_PCIE_PHY_SW_RESET_SW_RESET_BMSK                                                        0x1
#define HWIO_PSP_PCIE_PHY_SW_RESET_SW_RESET_SHFT                                                        0x0

#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_ADDR(x)                                             ((x) + 0x00000004)
#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_OFFS                                                (0x00000004)
#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_RMSK                                                       0x1
#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_ADDR(x), HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_RMSK)
#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_IN(x))
#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_SW_PWRDN_B_BMSK                                            0x1
#define HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_SW_PWRDN_B_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_START_CONTROL_ADDR(x)                                                  ((x) + 0x00000008)
#define HWIO_PSP_PCIE_PHY_START_CONTROL_OFFS                                                     (0x00000008)
#define HWIO_PSP_PCIE_PHY_START_CONTROL_RMSK                                                            0x1
#define HWIO_PSP_PCIE_PHY_START_CONTROL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_START_CONTROL_ADDR(x), HWIO_PSP_PCIE_PHY_START_CONTROL_RMSK)
#define HWIO_PSP_PCIE_PHY_START_CONTROL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_START_CONTROL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_START_CONTROL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_START_CONTROL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_START_CONTROL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_START_CONTROL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_START_CONTROL_IN(x))
#define HWIO_PSP_PCIE_PHY_START_CONTROL_PCS_START_BMSK                                                  0x1
#define HWIO_PSP_PCIE_PHY_START_CONTROL_PCS_START_SHFT                                                  0x0

#define HWIO_PSP_PCIE_PHY_LOCAL_FS_ADDR(x)                                                       ((x) + 0x0000000c)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_OFFS                                                          (0x0000000c)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RMSK                                                                0x3f
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCAL_FS_ADDR(x), HWIO_PSP_PCIE_PHY_LOCAL_FS_RMSK)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCAL_FS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_LOCAL_FS_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_LOCAL_FS_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_LOCAL_FS_IN(x))
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_LOCAL_FS_BMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_LOCAL_FS_SHFT                                                        0x0

#define HWIO_PSP_PCIE_PHY_LOCAL_LF_ADDR(x)                                                       ((x) + 0x00000010)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_OFFS                                                          (0x00000010)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RMSK                                                                0x3f
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCAL_LF_ADDR(x), HWIO_PSP_PCIE_PHY_LOCAL_LF_RMSK)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCAL_LF_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_LOCAL_LF_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_LOCAL_LF_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_LOCAL_LF_IN(x))
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_LOCAL_LF_BMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_LOCAL_LF_SHFT                                                        0x0

#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_ADDR(x)                                                    ((x) + 0x00000014)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_OFFS                                                       (0x00000014)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_RMSK                                                             0x3f
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_ADDR(x), HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_RMSK)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_IN(x))
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_LOCAL_FS_RS_BMSK                                                 0x3f
#define HWIO_PSP_PCIE_PHY_LOCAL_FS_RS_LOCAL_FS_RS_SHFT                                                  0x0

#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_ADDR(x)                                                    ((x) + 0x00000018)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_OFFS                                                       (0x00000018)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_RMSK                                                             0x3f
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_ADDR(x), HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_RMSK)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_IN(x))
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_LOCAL_LF_RS_BMSK                                                 0x3f
#define HWIO_PSP_PCIE_PHY_LOCAL_LF_RS_LOCAL_LF_RS_SHFT                                                  0x0

#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_ADDR(x)                                                     ((x) + 0x0000001c)
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_OFFS                                                        (0x0000001c)
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_RMSK                                                              0xff
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_MGN_ADJUST_ADDR(x), HWIO_PSP_PCIE_PHY_MGN_ADJUST_RMSK)
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_MGN_ADJUST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_MGN_ADJUST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_MGN_ADJUST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_MGN_ADJUST_IN(x))
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_GEN3_MGN_ADJUST_RS_BMSK                                           0xf0
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_GEN3_MGN_ADJUST_RS_SHFT                                            0x4
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_MGN_ADJUST_BMSK                                                    0xf
#define HWIO_PSP_PCIE_PHY_MGN_ADJUST_MGN_ADJUST_SHFT                                                    0x0

#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_ADDR(x)                                                     ((x) + 0x00000020)
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_OFFS                                                        (0x00000020)
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_RMSK                                                              0xff
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_MGN_CONFIG_ADDR(x), HWIO_PSP_PCIE_PHY_MGN_CONFIG_RMSK)
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_MGN_CONFIG_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_MGN_CONFIG_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_MGN_CONFIG_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_MGN_CONFIG_IN(x))
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_GEN3_TXSWING_SEL_BMSK                                             0x80
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_GEN3_TXSWING_SEL_SHFT                                              0x7
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_GEN3_TXSWING_SOURCE_BMSK                                          0x40
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_GEN3_TXSWING_SOURCE_SHFT                                           0x6
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_EQ_SCALER_BMSK                                                    0x30
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_EQ_SCALER_SHFT                                                     0x4
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_TXDEEMPH_0DB_EN_BMSK                                               0x8
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_TXDEEMPH_0DB_EN_SHFT                                               0x3
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_RSVD_BMSK                                                          0x4
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_RSVD_SHFT                                                          0x2
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_TXMGN_ACK_MASK_BMSK                                                0x2
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_TXMGN_ACK_MASK_SHFT                                                0x1
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_TXMGN_UPDATE_BMSK                                                  0x1
#define HWIO_PSP_PCIE_PHY_MGN_CONFIG_TXMGN_UPDATE_SHFT                                                  0x0

#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_ADDR(x)                                                      ((x) + 0x00000024)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_OFFS                                                         (0x00000024)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_RMSK                                                               0xff
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_EQ_CONFIG_ADDR(x), HWIO_PSP_PCIE_PHY_EQ_CONFIG_RMSK)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_EQ_CONFIG_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_EQ_CONFIG_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_EQ_CONFIG_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_EQ_CONFIG_IN(x))
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_RXEQ_GEN3_RX_ACTIVE_SEL_BMSK                                       0x80
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_RXEQ_GEN3_RX_ACTIVE_SEL_SHFT                                        0x7
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_GEN3_LOCK_WDT_RXEQ_DSBL_BMSK                                       0x40
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_GEN3_LOCK_WDT_RXEQ_DSBL_SHFT                                        0x6
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_SW_DFE_RESET_BMSK                                                  0x20
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_SW_DFE_RESET_SHFT                                                   0x5
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_DFE_RESET_ON_ABORT_EN_BMSK                                         0x10
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_DFE_RESET_ON_ABORT_EN_SHFT                                          0x4
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_DFE_TRAIN_EN_OFF_SYNCH_EN_BMSK                                      0x8
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_DFE_TRAIN_EN_OFF_SYNCH_EN_SHFT                                      0x3
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_RXEQEVAL_MASK_EN_BMSK                                               0x4
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_RXEQEVAL_MASK_EN_SHFT                                               0x2
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_POST_INCDEC_MAP_BMSK                                                0x2
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_POST_INCDEC_MAP_SHFT                                                0x1
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_PRE_INCDEC_MAP_BMSK                                                 0x1
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG_PRE_INCDEC_MAP_SHFT                                                 0x0

#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_ADDR(x)                                                     ((x) + 0x00000028)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_OFFS                                                        (0x00000028)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_RMSK                                                               0xf
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_EQ_CONFIG2_ADDR(x), HWIO_PSP_PCIE_PHY_EQ_CONFIG2_RMSK)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_EQ_CONFIG2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_EQ_CONFIG2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_EQ_CONFIG2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_EQ_CONFIG2_IN(x))
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_DFE_RESET_ON_RETRAIN_EN_BMSK                                       0x8
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_DFE_RESET_ON_RETRAIN_EN_SHFT                                       0x3
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_DFE_RESET_ON_PHASE3_START_EN_BMSK                                  0x4
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_DFE_RESET_ON_PHASE3_START_EN_SHFT                                  0x2
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_USE_RXEQINPHASE0123_BMSK                                           0x2
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_USE_RXEQINPHASE0123_SHFT                                           0x1
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_EARLY_TRAINING_EN_BMSK                                             0x1
#define HWIO_PSP_PCIE_PHY_EQ_CONFIG2_EARLY_TRAINING_EN_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_ADDR(x)                                           ((x) + 0x0000002c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_OFFS                                              (0x0000002c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_TXMGN_MAIN_V0_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_TXMGN_MAIN_V0_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_ADDR(x)                                           ((x) + 0x00000030)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_OFFS                                              (0x00000030)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_TXMGN_MAIN_V1_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M3P5DB_TXMGN_MAIN_V1_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_ADDR(x)                                           ((x) + 0x00000034)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_OFFS                                              (0x00000034)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_TXMGN_MAIN_V2_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M3P5DB_TXMGN_MAIN_V2_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_ADDR(x)                                           ((x) + 0x00000038)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_OFFS                                              (0x00000038)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_TXMGN_MAIN_V3_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M3P5DB_TXMGN_MAIN_V3_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_ADDR(x)                                           ((x) + 0x0000003c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_OFFS                                              (0x0000003c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_TXMGN_MAIN_V4_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M3P5DB_TXMGN_MAIN_V4_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_ADDR(x)                                           ((x) + 0x00000040)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_OFFS                                              (0x00000040)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_TXMGN_POST_V0_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_TXMGN_POST_V0_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_ADDR(x)                                           ((x) + 0x00000044)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_OFFS                                              (0x00000044)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_TXMGN_POST_V1_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M3P5DB_TXMGN_POST_V1_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_ADDR(x)                                           ((x) + 0x00000048)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_OFFS                                              (0x00000048)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_TXMGN_POST_V2_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M3P5DB_TXMGN_POST_V2_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_ADDR(x)                                           ((x) + 0x0000004c)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_OFFS                                              (0x0000004c)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_TXMGN_POST_V3_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M3P5DB_TXMGN_POST_V3_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_ADDR(x)                                           ((x) + 0x00000050)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_OFFS                                              (0x00000050)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_RMSK                                                    0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_TXMGN_POST_V4_M3P5DB_BMSK                               0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M3P5DB_TXMGN_POST_V4_M3P5DB_SHFT                                0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_ADDR(x)                                             ((x) + 0x00000054)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_OFFS                                                (0x00000054)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_TXMGN_MAIN_V0_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_TXMGN_MAIN_V0_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_ADDR(x)                                             ((x) + 0x00000058)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_OFFS                                                (0x00000058)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_TXMGN_MAIN_V1_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_M6DB_TXMGN_MAIN_V1_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_ADDR(x)                                             ((x) + 0x0000005c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_OFFS                                                (0x0000005c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_TXMGN_MAIN_V2_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_M6DB_TXMGN_MAIN_V2_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_ADDR(x)                                             ((x) + 0x00000060)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_OFFS                                                (0x00000060)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_TXMGN_MAIN_V3_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_M6DB_TXMGN_MAIN_V3_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_ADDR(x)                                             ((x) + 0x00000064)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_OFFS                                                (0x00000064)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_TXMGN_MAIN_V4_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_M6DB_TXMGN_MAIN_V4_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_ADDR(x)                                             ((x) + 0x00000068)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_OFFS                                                (0x00000068)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_TXMGN_POST_V0_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_TXMGN_POST_V0_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_ADDR(x)                                             ((x) + 0x0000006c)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_OFFS                                                (0x0000006c)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_TXMGN_POST_V1_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V1_M6DB_TXMGN_POST_V1_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_ADDR(x)                                             ((x) + 0x00000070)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_OFFS                                                (0x00000070)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_TXMGN_POST_V2_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V2_M6DB_TXMGN_POST_V2_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_ADDR(x)                                             ((x) + 0x00000074)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_OFFS                                                (0x00000074)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_TXMGN_POST_V3_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V3_M6DB_TXMGN_POST_V3_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_ADDR(x)                                             ((x) + 0x00000078)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_OFFS                                                (0x00000078)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_RMSK                                                      0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_TXMGN_POST_V4_M6DB_BMSK                                   0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_POST_V4_M6DB_TXMGN_POST_V4_M6DB_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_ADDR(x)                                              ((x) + 0x0000007c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_OFFS                                                 (0x0000007c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_TXMGN_MAIN_V0_0DB_BMSK                                     0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_0DB_TXMGN_MAIN_V0_0DB_SHFT                                      0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_ADDR(x)                                              ((x) + 0x00000080)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_OFFS                                                 (0x00000080)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_TXMGN_MAIN_V1_0DB_BMSK                                     0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_0DB_TXMGN_MAIN_V1_0DB_SHFT                                      0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_ADDR(x)                                              ((x) + 0x00000084)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_OFFS                                                 (0x00000084)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_TXMGN_MAIN_V2_0DB_BMSK                                     0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_0DB_TXMGN_MAIN_V2_0DB_SHFT                                      0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_ADDR(x)                                              ((x) + 0x00000088)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_OFFS                                                 (0x00000088)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_TXMGN_MAIN_V3_0DB_BMSK                                     0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_0DB_TXMGN_MAIN_V3_0DB_SHFT                                      0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_ADDR(x)                                              ((x) + 0x0000008c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_OFFS                                                 (0x0000008c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_TXMGN_MAIN_V4_0DB_BMSK                                     0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_0DB_TXMGN_MAIN_V4_0DB_SHFT                                      0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_ADDR(x)                                               ((x) + 0x00000090)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_OFFS                                                  (0x00000090)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_RMSK                                                        0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_TXMGN_MAIN_V0_RS_BMSK                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_RS_TXMGN_MAIN_V0_RS_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_ADDR(x)                                               ((x) + 0x00000094)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_OFFS                                                  (0x00000094)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_RMSK                                                        0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_TXMGN_MAIN_V1_RS_BMSK                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V1_RS_TXMGN_MAIN_V1_RS_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_ADDR(x)                                               ((x) + 0x00000098)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_OFFS                                                  (0x00000098)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_RMSK                                                        0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_TXMGN_MAIN_V2_RS_BMSK                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V2_RS_TXMGN_MAIN_V2_RS_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_ADDR(x)                                               ((x) + 0x0000009c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_OFFS                                                  (0x0000009c)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_RMSK                                                        0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_TXMGN_MAIN_V3_RS_BMSK                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V3_RS_TXMGN_MAIN_V3_RS_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_ADDR(x)                                               ((x) + 0x000000a0)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_OFFS                                                  (0x000000a0)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_RMSK                                                        0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_ADDR(x), HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_RMSK)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_IN(x))
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_TXMGN_MAIN_V4_RS_BMSK                                       0x3f
#define HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V4_RS_TXMGN_MAIN_V4_RS_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_ADDR(x)                                                 ((x) + 0x000000a4)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_OFFS                                                    (0x000000a4)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_PRESET_P0_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P0_MAIN_PRESET_P0_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_ADDR(x)                                                 ((x) + 0x000000a8)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_OFFS                                                    (0x000000a8)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_PRESET_P1_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P1_MAIN_PRESET_P1_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_ADDR(x)                                                 ((x) + 0x000000ac)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_OFFS                                                    (0x000000ac)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_PRESET_P2_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P2_MAIN_PRESET_P2_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_ADDR(x)                                                 ((x) + 0x000000b0)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_OFFS                                                    (0x000000b0)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_PRESET_P3_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P3_MAIN_PRESET_P3_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_ADDR(x)                                                 ((x) + 0x000000b4)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_OFFS                                                    (0x000000b4)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_PRESET_P4_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P4_MAIN_PRESET_P4_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_ADDR(x)                                                 ((x) + 0x000000b8)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_OFFS                                                    (0x000000b8)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_PRESET_P5_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P5_MAIN_PRESET_P5_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_ADDR(x)                                                 ((x) + 0x000000bc)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_OFFS                                                    (0x000000bc)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_PRESET_P6_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P6_MAIN_PRESET_P6_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_ADDR(x)                                                 ((x) + 0x000000c0)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_OFFS                                                    (0x000000c0)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_PRESET_P7_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P7_MAIN_PRESET_P7_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_ADDR(x)                                                 ((x) + 0x000000c4)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_OFFS                                                    (0x000000c4)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_PRESET_P8_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P8_MAIN_PRESET_P8_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_ADDR(x)                                                 ((x) + 0x000000c8)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_OFFS                                                    (0x000000c8)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_RMSK                                                          0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_PRESET_P9_MAIN_BMSK                                           0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P9_MAIN_PRESET_P9_MAIN_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_ADDR(x)                                                ((x) + 0x000000cc)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_OFFS                                                   (0x000000cc)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_RMSK                                                         0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_PRESET_P10_MAIN_BMSK                                         0x3f
#define HWIO_PSP_PCIE_PHY_PRESET_P10_MAIN_PRESET_P10_MAIN_SHFT                                          0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_ADDR(x)                                                  ((x) + 0x000000d0)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_OFFS                                                     (0x000000d0)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_PRESET_P0_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P0_PRE_PRESET_P0_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_ADDR(x)                                                  ((x) + 0x000000d4)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_OFFS                                                     (0x000000d4)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_PRESET_P1_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P1_PRE_PRESET_P1_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_ADDR(x)                                                  ((x) + 0x000000d8)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_OFFS                                                     (0x000000d8)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_PRESET_P2_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P2_PRE_PRESET_P2_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_ADDR(x)                                                  ((x) + 0x000000dc)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_OFFS                                                     (0x000000dc)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_PRESET_P3_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P3_PRE_PRESET_P3_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_ADDR(x)                                                  ((x) + 0x000000e0)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_OFFS                                                     (0x000000e0)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_PRESET_P4_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P4_PRE_PRESET_P4_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_ADDR(x)                                                  ((x) + 0x000000e4)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_OFFS                                                     (0x000000e4)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_PRESET_P5_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P5_PRE_PRESET_P5_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_ADDR(x)                                                  ((x) + 0x000000e8)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_OFFS                                                     (0x000000e8)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_PRESET_P6_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P6_PRE_PRESET_P6_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_ADDR(x)                                                  ((x) + 0x000000ec)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_OFFS                                                     (0x000000ec)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_PRESET_P7_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P7_PRE_PRESET_P7_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_ADDR(x)                                                  ((x) + 0x000000f0)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_OFFS                                                     (0x000000f0)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_PRESET_P8_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P8_PRE_PRESET_P8_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_ADDR(x)                                                  ((x) + 0x000000f4)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_OFFS                                                     (0x000000f4)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_PRESET_P9_PRE_BMSK                                             0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P9_PRE_PRESET_P9_PRE_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_ADDR(x)                                                 ((x) + 0x000000f8)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_OFFS                                                    (0x000000f8)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_PRESET_P10_PRE_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_PRESET_P10_PRE_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_ADDR(x)                                                 ((x) + 0x000000fc)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_OFFS                                                    (0x000000fc)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P0_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P0_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P0_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P0_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P0_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P0_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_PRESET_P0_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P0_POST_PRESET_P0_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_ADDR(x)                                                 ((x) + 0x00000100)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_OFFS                                                    (0x00000100)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P1_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P1_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P1_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P1_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P1_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P1_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_PRESET_P1_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P1_POST_PRESET_P1_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_ADDR(x)                                                 ((x) + 0x00000104)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_OFFS                                                    (0x00000104)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P2_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P2_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P2_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P2_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P2_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P2_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_PRESET_P2_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P2_POST_PRESET_P2_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_ADDR(x)                                                 ((x) + 0x00000108)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_OFFS                                                    (0x00000108)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P3_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P3_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P3_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P3_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P3_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P3_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_PRESET_P3_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P3_POST_PRESET_P3_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_ADDR(x)                                                 ((x) + 0x0000010c)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_OFFS                                                    (0x0000010c)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P4_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P4_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P4_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P4_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P4_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P4_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_PRESET_P4_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P4_POST_PRESET_P4_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_ADDR(x)                                                 ((x) + 0x00000110)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_OFFS                                                    (0x00000110)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P5_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P5_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P5_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P5_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P5_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P5_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_PRESET_P5_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P5_POST_PRESET_P5_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_ADDR(x)                                                 ((x) + 0x00000114)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_OFFS                                                    (0x00000114)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P6_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P6_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P6_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P6_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P6_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P6_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_PRESET_P6_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P6_POST_PRESET_P6_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_ADDR(x)                                                 ((x) + 0x00000118)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_OFFS                                                    (0x00000118)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P7_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P7_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P7_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P7_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P7_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P7_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_PRESET_P7_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P7_POST_PRESET_P7_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_ADDR(x)                                                 ((x) + 0x0000011c)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_OFFS                                                    (0x0000011c)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P8_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P8_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P8_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P8_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P8_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P8_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_PRESET_P8_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P8_POST_PRESET_P8_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_ADDR(x)                                                 ((x) + 0x00000120)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_OFFS                                                    (0x00000120)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P9_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P9_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P9_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P9_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P9_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P9_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_PRESET_P9_POST_BMSK                                           0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P9_POST_PRESET_P9_POST_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_ADDR(x)                                                ((x) + 0x00000124)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_OFFS                                                   (0x00000124)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_RMSK                                                         0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P10_POST_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_P10_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_P10_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_P10_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_P10_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_P10_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_PRESET_P10_POST_BMSK                                         0x1f
#define HWIO_PSP_PCIE_PHY_PRESET_P10_POST_PRESET_P10_POST_SHFT                                          0x0

#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_ADDR(x)                                        ((x) + 0x00000128)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_OFFS                                           (0x00000128)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_RMSK                                                 0x3f
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_L0_PRESET_OVERRIDE_MAIN_BMSK                         0x3f
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_MAIN_L0_PRESET_OVERRIDE_MAIN_SHFT                          0x0

#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_ADDR(x)                                         ((x) + 0x0000012c)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_OFFS                                            (0x0000012c)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_RMSK                                                  0x1f
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_L0_PRESET_OVERRIDE_PRE_BMSK                           0x1f
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_PRE_L0_PRESET_OVERRIDE_PRE_SHFT                            0x0

#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_ADDR(x)                                        ((x) + 0x00000130)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_OFFS                                           (0x00000130)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_RMSK                                                 0x1f
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_ADDR(x), HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_L0_PRESET_OVERRIDE_POST_BMSK                         0x1f
#define HWIO_PSP_PCIE_PHY_L0_PRESET_OVERRIDE_POST_L0_PRESET_OVERRIDE_POST_SHFT                          0x0

#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_ADDR(x)                                        ((x) + 0x00000134)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_OFFS                                           (0x00000134)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_RMSK                                                 0x3f
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_L1_PRESET_OVERRIDE_MAIN_BMSK                         0x3f
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_MAIN_L1_PRESET_OVERRIDE_MAIN_SHFT                          0x0

#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_ADDR(x)                                         ((x) + 0x00000138)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_OFFS                                            (0x00000138)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_RMSK                                                  0x1f
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_L1_PRESET_OVERRIDE_PRE_BMSK                           0x1f
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_PRE_L1_PRESET_OVERRIDE_PRE_SHFT                            0x0

#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_ADDR(x)                                        ((x) + 0x0000013c)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_OFFS                                           (0x0000013c)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_RMSK                                                 0x1f
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_ADDR(x), HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_L1_PRESET_OVERRIDE_POST_BMSK                         0x1f
#define HWIO_PSP_PCIE_PHY_L1_PRESET_OVERRIDE_POST_L1_PRESET_OVERRIDE_POST_SHFT                          0x0

#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_ADDR(x)                                        ((x) + 0x00000140)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_OFFS                                           (0x00000140)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_RMSK                                                 0x3f
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_L2_PRESET_OVERRIDE_MAIN_BMSK                         0x3f
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_MAIN_L2_PRESET_OVERRIDE_MAIN_SHFT                          0x0

#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_ADDR(x)                                         ((x) + 0x00000144)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_OFFS                                            (0x00000144)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_RMSK                                                  0x1f
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_L2_PRESET_OVERRIDE_PRE_BMSK                           0x1f
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_PRE_L2_PRESET_OVERRIDE_PRE_SHFT                            0x0

#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_ADDR(x)                                        ((x) + 0x00000148)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_OFFS                                           (0x00000148)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_RMSK                                                 0x1f
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_ADDR(x), HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_L2_PRESET_OVERRIDE_POST_BMSK                         0x1f
#define HWIO_PSP_PCIE_PHY_L2_PRESET_OVERRIDE_POST_L2_PRESET_OVERRIDE_POST_SHFT                          0x0

#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_ADDR(x)                                        ((x) + 0x0000014c)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_OFFS                                           (0x0000014c)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_RMSK                                                 0x3f
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_ADDR(x), HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_L3_PRESET_OVERRIDE_MAIN_BMSK                         0x3f
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_MAIN_L3_PRESET_OVERRIDE_MAIN_SHFT                          0x0

#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_ADDR(x)                                         ((x) + 0x00000150)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_OFFS                                            (0x00000150)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_RMSK                                                  0x1f
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_ADDR(x), HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_L3_PRESET_OVERRIDE_PRE_BMSK                           0x1f
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_PRE_L3_PRESET_OVERRIDE_PRE_SHFT                            0x0

#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_ADDR(x)                                        ((x) + 0x00000154)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_OFFS                                           (0x00000154)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_RMSK                                                 0x1f
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_ADDR(x), HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_L3_PRESET_OVERRIDE_POST_BMSK                         0x1f
#define HWIO_PSP_PCIE_PHY_L3_PRESET_OVERRIDE_POST_L3_PRESET_OVERRIDE_POST_SHFT                          0x0

#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_ADDR(x)                                             ((x) + 0x00000158)
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_OFFS                                                (0x00000158)
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_RMSK                                                       0xf
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_ADDR(x), HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_RMSK)
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_IN(x))
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_L3_PRESET_OVERRIDE_EN_BMSK                                 0x8
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_L3_PRESET_OVERRIDE_EN_SHFT                                 0x3
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_L2_PRESET_OVERRIDE_EN_BMSK                                 0x4
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_L2_PRESET_OVERRIDE_EN_SHFT                                 0x2
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_L1_PRESET_OVERRIDE_EN_BMSK                                 0x2
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_L1_PRESET_OVERRIDE_EN_SHFT                                 0x1
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_L0_PRESET_OVERRIDE_EN_BMSK                                 0x1
#define HWIO_PSP_PCIE_PHY_PRESET_OVERRIDE_EN_L0_PRESET_OVERRIDE_EN_SHFT                                 0x0

#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_ADDR(x)                                               ((x) + 0x0000015c)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_OFFS                                                  (0x0000015c)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_RMSK                                                        0xff
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_ADDR(x), HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_L0_PRESET_DSBL_L_BMSK                                       0xff
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_L0_PRESET_DSBL_L_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_ADDR(x)                                               ((x) + 0x00000160)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_OFFS                                                  (0x00000160)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_RMSK                                                         0x7
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_ADDR(x), HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_L0_PRESET_DSBL_H_BMSK                                        0x7
#define HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_L0_PRESET_DSBL_H_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_ADDR(x)                                               ((x) + 0x00000164)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_OFFS                                                  (0x00000164)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_RMSK                                                        0xff
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_ADDR(x), HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_L1_PRESET_DSBL_L_BMSK                                       0xff
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_L1_PRESET_DSBL_L_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_ADDR(x)                                               ((x) + 0x00000168)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_OFFS                                                  (0x00000168)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_RMSK                                                         0x7
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_ADDR(x), HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_L1_PRESET_DSBL_H_BMSK                                        0x7
#define HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_L1_PRESET_DSBL_H_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_ADDR(x)                                               ((x) + 0x0000016c)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_OFFS                                                  (0x0000016c)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_RMSK                                                        0xff
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_ADDR(x), HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_L2_PRESET_DSBL_L_BMSK                                       0xff
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_L2_PRESET_DSBL_L_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_ADDR(x)                                               ((x) + 0x00000170)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_OFFS                                                  (0x00000170)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_RMSK                                                         0x7
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_ADDR(x), HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_L2_PRESET_DSBL_H_BMSK                                        0x7
#define HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_L2_PRESET_DSBL_H_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_ADDR(x)                                               ((x) + 0x00000174)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_OFFS                                                  (0x00000174)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_RMSK                                                        0xff
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_ADDR(x), HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_L3_PRESET_DSBL_L_BMSK                                       0xff
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_L3_PRESET_DSBL_L_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_ADDR(x)                                               ((x) + 0x00000178)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_OFFS                                                  (0x00000178)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_RMSK                                                         0x7
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_ADDR(x), HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_L3_PRESET_DSBL_H_BMSK                                        0x7
#define HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_L3_PRESET_DSBL_H_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_ADDR(x)                                             ((x) + 0x0000017c)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_OFFS                                                (0x0000017c)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RMSK                                                      0xff
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_ADDR(x), HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RMSK)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_IN(x))
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RX_IDLE_LOW_COUNT_VAL_BMSK                                0xf0
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RX_IDLE_LOW_COUNT_VAL_SHFT                                 0x4
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_EIOS_DTCT_CFG_BMSK                                         0x8
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_EIOS_DTCT_CFG_SHFT                                         0x3
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RX_IDLE_ON_EIOS_EN_BMSK                                    0x4
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RX_IDLE_ON_EIOS_EN_SHFT                                    0x2
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RX_IDLE_DTCT_G2S_EN_BMSK                                   0x2
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RX_IDLE_DTCT_G2S_EN_SHFT                                   0x1
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RX_IDLE_DTCT_G1S_EN_BMSK                                   0x1
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL_RX_IDLE_DTCT_G1S_EN_SHFT                                   0x0

#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_ADDR(x)                                            ((x) + 0x00000180)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_OFFS                                               (0x00000180)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_RMSK                                                     0xff
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_ADDR(x), HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_RMSK)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_IN(x))
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_SIGDET_MASK_AFTER_EIOS_TIME_BMSK                         0xf0
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_SIGDET_MASK_AFTER_EIOS_TIME_SHFT                          0x4
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_SIGDET_MASK_AFTER_EIOS_EN_BMSK                            0x8
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_SIGDET_MASK_AFTER_EIOS_EN_SHFT                            0x3
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_RSVD_BMSK                                                 0x4
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_RSVD_SHFT                                                 0x2
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_GEN3_EIOS_DTCT_CFG_BMSK                                   0x2
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_GEN3_EIOS_DTCT_CFG_SHFT                                   0x1
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_GEN3_RX_IDLE_ON_EIOS_EN_BMSK                              0x1
#define HWIO_PSP_PCIE_PHY_RX_IDLE_DTCT_CNTRL2_GEN3_RX_IDLE_ON_EIOS_EN_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_ADDR(x)                                             ((x) + 0x00000184)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_OFFS                                                (0x00000184)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_RMSK                                                      0xff
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_ADDR(x), HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_RMSK)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_IN(x))
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_P0_TXELECIDLE_HIGH_LANE_OFF_EN_BMSK                       0x80
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_P0_TXELECIDLE_HIGH_LANE_OFF_EN_SHFT                        0x7
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_RXELECIDLE_DSBL_CAPTURE_EN_BMSK                           0x40
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_RXELECIDLE_DSBL_CAPTURE_EN_SHFT                            0x6
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_GEN1_DIV_SEL_BMSK                                         0x20
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_GEN1_DIV_SEL_SHFT                                          0x5
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_AUXCLK_USED_IN_P2_EN_BMSK                                 0x10
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_AUXCLK_USED_IN_P2_EN_SHFT                                  0x4
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_AUXCLK_USED_IN_L1SS_EN_BMSK                                0x8
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_AUXCLK_USED_IN_L1SS_EN_SHFT                                0x3
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_RXELECIDLE_LOW_ON_L1SS_EXIT_EN_BMSK                        0x4
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_RXELECIDLE_LOW_ON_L1SS_EXIT_EN_SHFT                        0x2
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_P2_CM_CTRL_BMSK                                            0x2
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_P2_CM_CTRL_SHFT                                            0x1
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_FORCE_OTHERS_INVLD_EN_BMSK                                 0x1
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_FORCE_OTHERS_INVLD_EN_SHFT                                 0x0

#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_ADDR(x)                                            ((x) + 0x00000188)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_OFFS                                               (0x00000188)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_RMSK                                                     0xff
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_ADDR(x), HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_RMSK)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_IN(x))
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_P2_MASK_SIGDET_EN_BMSK                                   0x80
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_P2_MASK_SIGDET_EN_SHFT                                    0x7
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_PRE_P2_MASK_SIGDET_EN_BMSK                               0x40
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_PRE_P2_MASK_SIGDET_EN_SHFT                                0x6
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_GEN3_P0_SPS_STATE_BMSK                                   0x30
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_GEN3_P0_SPS_STATE_SHFT                                    0x4
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_GEN2_P0_SPS_STATE_BMSK                                    0xc
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_GEN2_P0_SPS_STATE_SHFT                                    0x2
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_GEN1_P0_SPS_STATE_BMSK                                    0x3
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG2_GEN1_P0_SPS_STATE_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_ADDR(x)                                            ((x) + 0x0000018c)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_OFFS                                               (0x0000018c)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_RMSK                                                     0x77
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_ADDR(x), HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_RMSK)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_IN(x))
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_P2_SPS_STATE_BMSK                                        0x70
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_P2_SPS_STATE_SHFT                                         0x4
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_P1_SPS_STATE_BMSK                                         0x7
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG3_P1_SPS_STATE_SHFT                                         0x0

#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_ADDR(x)                                            ((x) + 0x00000190)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_OFFS                                               (0x00000190)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_RMSK                                                     0x77
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_ADDR(x), HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_RMSK)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_IN(x))
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_P0S_RX_OFF_SPS_STATE_BMSK                                0x70
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_P0S_RX_OFF_SPS_STATE_SHFT                                 0x4
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_P0S_RX_ACT_SPS_STATE_BMSK                                 0x7
#define HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG4_P0S_RX_ACT_SPS_STATE_SHFT                                 0x0

#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_ADDR(x)                                               ((x) + 0x00000194)
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_OFFS                                                  (0x00000194)
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_RMSK                                                        0xf7
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_ADDR(x), HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_RMSK)
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_IN(x))
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_RSVD_BMSK                                                   0x80
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_RSVD_SHFT                                                    0x7
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_RX_ACTIVE_ON_P1_TO_P0_EN_BMSK                               0x40
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_RX_ACTIVE_ON_P1_TO_P0_EN_SHFT                                0x6
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN3_EBUF_DEPTH_SEL_BMSK                                    0x20
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN3_EBUF_DEPTH_SEL_SHFT                                     0x5
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN12_EBUF_DEPTH_SEL_BMSK                                   0x10
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN12_EBUF_DEPTH_SEL_SHFT                                    0x4
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN3_RTB_SYNC_MODE_BMSK                                      0x4
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN3_RTB_SYNC_MODE_SHFT                                      0x2
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN12_RTB_SYNC_MODE_BMSK                                     0x2
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN12_RTB_SYNC_MODE_SHFT                                     0x1
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN12_RXVALID_ALIGN_EN_BMSK                                  0x1
#define HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_GEN12_RXVALID_ALIGN_EN_SHFT                                  0x0

#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_ADDR(x)                                            ((x) + 0x00000198)
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_OFFS                                               (0x00000198)
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_RMSK                                                     0xff
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_ADDR(x), HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_RMSK)
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_IN(x))
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_RX_LANE_OFF_STATE_BMSK                                   0x80
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_RX_LANE_OFF_STATE_SHFT                                    0x7
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_LANE_TRANS_OFF_SPS_STATE_BMSK                            0x70
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_LANE_TRANS_OFF_SPS_STATE_SHFT                             0x4
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_TX_LANE_OFF_STATE_BMSK                                    0x8
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_TX_LANE_OFF_STATE_SHFT                                    0x3
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_LANE_OFF_SPS_STATE_BMSK                                   0x7
#define HWIO_PSP_PCIE_PHY_PCS_LANE_OFF_CONFIG_LANE_OFF_SPS_STATE_SHFT                                   0x0

#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_ADDR(x)                                                ((x) + 0x0000019c)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_OFFS                                                   (0x0000019c)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_RMSK                                                         0xff
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_ADDR(x), HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_RMSK)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_IN(x))
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_RCVR_DTCT_DLY_L_BMSK                                         0xff
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_L_RCVR_DTCT_DLY_L_SHFT                                          0x0

#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_ADDR(x)                                                ((x) + 0x000001a0)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_OFFS                                                   (0x000001a0)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_RMSK                                                          0xf
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_ADDR(x), HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_RMSK)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_IN(x))
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_RCVR_DTCT_DLY_H_BMSK                                          0xf
#define HWIO_PSP_PCIE_PHY_RCVR_DTCT_DLY_H_RCVR_DTCT_DLY_H_SHFT                                          0x0

#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_ADDR(x)                                            ((x) + 0x000001a4)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_OFFS                                               (0x000001a4)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_RMSK                                                     0xff
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_ADDR(x), HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_RMSK)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_IN(x))
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_LOCK_HOLDOFF_TIME_BMSK                                   0xff
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG1_LOCK_HOLDOFF_TIME_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_ADDR(x)                                            ((x) + 0x000001a8)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_OFFS                                               (0x000001a8)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_RMSK                                                     0xff
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_ADDR(x), HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_RMSK)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_IN(x))
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_LOCK_KEEP_VAL_BMSK                                       0xc0
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_LOCK_KEEP_VAL_SHFT                                        0x6
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_LOCK_COUNT_VAL_BMSK                                      0x3f
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG2_LOCK_COUNT_VAL_SHFT                                       0x0

#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_ADDR(x)                                            ((x) + 0x000001ac)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_OFFS                                               (0x000001ac)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_RMSK                                                     0xff
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_ADDR(x), HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_RMSK)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_IN(x))
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN2_LOCK_WDT_COUNT_INCR_BMSK                            0x80
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN2_LOCK_WDT_COUNT_INCR_SHFT                             0x7
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN1_LOCK_WDT_COUNT_INCR_BMSK                            0x40
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN1_LOCK_WDT_COUNT_INCR_SHFT                             0x6
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN2_LOCK_WDT_EN_BMSK                                    0x20
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN2_LOCK_WDT_EN_SHFT                                     0x5
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN1_LOCK_WDT_EN_BMSK                                    0x10
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN1_LOCK_WDT_EN_SHFT                                     0x4
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN12_LOCK_WDT_VAL_BMSK                                   0xf
#define HWIO_PSP_PCIE_PHY_LOCK_DETECT_CONFIG3_GEN12_LOCK_WDT_VAL_SHFT                                   0x0

#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_ADDR(x)                                           ((x) + 0x000001b0)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_OFFS                                              (0x000001b0)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_RMSK                                                    0xff
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_ADDR(x), HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_RMSK)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_IN(x))
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_GEN3_ALIGN_HOLDOFF_TIME_L_BMSK                          0xff
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG1_GEN3_ALIGN_HOLDOFF_TIME_L_SHFT                           0x0

#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_ADDR(x)                                           ((x) + 0x000001b4)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_OFFS                                              (0x000001b4)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_RMSK                                                    0xff
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_ADDR(x), HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_RMSK)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_IN(x))
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_GEN3_EIEOS_DTCT_VAL_BMSK                                0xf0
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_GEN3_EIEOS_DTCT_VAL_SHFT                                 0x4
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_GEN3_DROP_VLD_ON_UNALIGNED_EIEOS_EN_BMSK                 0x8
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_GEN3_DROP_VLD_ON_UNALIGNED_EIEOS_EN_SHFT                 0x3
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_GEN3_KEEP_VLD_IN_LPBK_EN_BMSK                            0x4
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_GEN3_KEEP_VLD_IN_LPBK_EN_SHFT                            0x2
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_GEN3_ALIGN_HOLDOFF_TIME_H_BMSK                           0x3
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG2_GEN3_ALIGN_HOLDOFF_TIME_H_SHFT                           0x0

#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_ADDR(x)                                           ((x) + 0x000001b8)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_OFFS                                              (0x000001b8)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_RMSK                                                    0xff
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_ADDR(x), HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_RMSK)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_IN(x))
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_LOCK_WDT_VAL_BMSK                                  0xf0
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_LOCK_WDT_VAL_SHFT                                   0x4
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_LOCK_WDT_EN_BMSK                                    0x8
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_LOCK_WDT_EN_SHFT                                    0x3
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_BLK_ALIGN_CTRL_EN_BMSK                              0x4
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_BLK_ALIGN_CTRL_EN_SHFT                              0x2
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_DROP_VLD_ON_INVLD_HDR_EN2_BMSK                      0x2
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_DROP_VLD_ON_INVLD_HDR_EN2_SHFT                      0x1
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_DROP_VLD_ON_INVLD_HDR_EN1_BMSK                      0x1
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG3_GEN3_DROP_VLD_ON_INVLD_HDR_EN1_SHFT                      0x0

#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_ADDR(x)                                           ((x) + 0x000001bc)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_OFFS                                              (0x000001bc)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_RMSK                                                     0x3
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_ADDR(x), HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_RMSK)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_IN(x))
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_GEN3_LOCK_WDT_COUNT_INCR_BMSK                            0x3
#define HWIO_PSP_PCIE_PHY_ALIGN_DETECT_CONFIG4_GEN3_LOCK_WDT_COUNT_INCR_SHFT                            0x0

#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_ADDR(x)                                         ((x) + 0x000001c0)
#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_OFFS                                            (0x000001c0)
#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_RMSK                                                  0xff
#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_ADDR(x), HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_RMSK)
#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_IN(x))
#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_SIGDET_LOW_2_IDLE_TIME_BMSK                           0xff
#define HWIO_PSP_PCIE_PHY_SIGDET_LOW_2_IDLE_TIME_SIGDET_LOW_2_IDLE_TIME_SHFT                            0x0

#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_ADDR(x)                                              ((x) + 0x000001c4)
#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_OFFS                                                 (0x000001c4)
#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_RMSK                                                       0xff
#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_ADDR(x), HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_RMSK)
#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_IN(x))
#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_GEN3_RXEQ_STARTUP_TIME_BMSK                                0xff
#define HWIO_PSP_PCIE_PHY_RXEQ_STARTUP_TIME_GEN3_RXEQ_STARTUP_TIME_SHFT                                 0x0

#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_ADDR(x)                                                  ((x) + 0x000001c8)
#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_OFFS                                                     (0x000001c8)
#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_RMSK                                                           0x3f
#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_ADDR(x), HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_RMSK)
#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_IN(x))
#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_GEN3_RXEQEVAL_TIME_BMSK                                        0x3f
#define HWIO_PSP_PCIE_PHY_RXEQEVAL_TIME_GEN3_RXEQEVAL_TIME_SHFT                                         0x0

#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_ADDR(x)                                          ((x) + 0x000001cc)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_OFFS                                             (0x000001cc)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_RMSK                                                   0x7f
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_ADDR(x), HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_RMSK)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_IN(x))
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_EXT_TSYNC_PULSE_WIDTH_BMSK                             0x7f
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_PULSE_WIDTH_EXT_TSYNC_PULSE_WIDTH_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_ADDR(x)                                             ((x) + 0x000001d0)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_OFFS                                                (0x000001d0)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_RMSK                                                      0x7f
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_ADDR(x), HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_RMSK)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_IN(x))
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_EXT_TSYNC_DURATION_BMSK                                   0x7f
#define HWIO_PSP_PCIE_PHY_EXT_TSYNC_DURATION_EXT_TSYNC_DURATION_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_ADDR(x)                                    ((x) + 0x000001d4)
#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_OFFS                                       (0x000001d4)
#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_RMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_ADDR(x), HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_RMSK)
#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_IN(x))
#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_PWRUP_RESET_DLY_TIME_SYSCLK_BMSK                 0xff
#define HWIO_PSP_PCIE_PHY_PWRUP_RESET_DLY_TIME_SYSCLK_PWRUP_RESET_DLY_TIME_SYSCLK_SHFT                  0x0

#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_ADDR(x)                                         ((x) + 0x000001d8)
#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_OFFS                                            (0x000001d8)
#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_RMSK                                                  0xff
#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_ADDR(x), HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_RMSK)
#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_IN(x))
#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_WAKEUP_DLY_TIME_AUXCLK_BMSK                           0xff
#define HWIO_PSP_PCIE_PHY_WAKEUP_DLY_TIME_AUXCLK_WAKEUP_DLY_TIME_AUXCLK_SHFT                            0x0

#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_ADDR(x)                                                 ((x) + 0x000001dc)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_OFFS                                                    (0x000001dc)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_SW_TXSWING_BMSK                                               0x80
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_SW_TXSWING_SHFT                                                0x7
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_SW_TXMARGIN_BMSK                                              0x70
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_SW_TXMARGIN_SHFT                                               0x4
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_SW_RATE_BMSK                                                   0xc
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_SW_RATE_SHFT                                                   0x2
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_SW_POWERDOWN_BMSK                                              0x3
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL1_SW_POWERDOWN_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_ADDR(x)                                                 ((x) + 0x000001e0)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_OFFS                                                    (0x000001e0)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_SW_TXCOMPLIANCE_BMSK                                          0xf0
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_SW_TXCOMPLIANCE_SHFT                                           0x4
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_SW_TXELECIDLE_BMSK                                             0xf
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL2_SW_TXELECIDLE_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_ADDR(x)                                                 ((x) + 0x000001e4)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_OFFS                                                    (0x000001e4)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_SW_RXPOLARITY_BMSK                                            0xf0
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_SW_RXPOLARITY_SHFT                                             0x4
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_SW_TXDETECTRX_LOOPBACK_BMSK                                    0xf
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL3_SW_TXDETECTRX_LOOPBACK_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_ADDR(x)                                                 ((x) + 0x000001e8)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_OFFS                                                    (0x000001e8)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_X16MODE_BMSK                                               0x10
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_X16MODE_SHFT                                                0x4
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_X8MODE_BMSK                                                 0x8
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_X8MODE_SHFT                                                 0x3
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_TXCM_DISABLE_BMSK                                           0x4
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_TXCM_DISABLE_SHFT                                           0x2
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_RXELECIDLE_DISABLE_BMSK                                     0x2
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_RXELECIDLE_DISABLE_SHFT                                     0x1
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_PCLKREQ_N_BMSK                                              0x1
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL4_SW_PCLKREQ_N_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_ADDR(x)                                                 ((x) + 0x000001ec)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_OFFS                                                    (0x000001ec)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_RXEQINPROGRESS_BMSK                                        0x80
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_RXEQINPROGRESS_SHFT                                         0x7
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_INVALIDREQUEST_BMSK                                        0x40
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_INVALIDREQUEST_SHFT                                         0x6
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_RXEQEVAL_BMSK                                              0x20
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_RXEQEVAL_SHFT                                               0x5
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_BLOCKALIGNCONTROL_BMSK                                     0x10
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_BLOCKALIGNCONTROL_SHFT                                      0x4
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_TXDATAVALID_BMSK                                            0x8
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_TXDATAVALID_SHFT                                            0x3
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_TXSYNCHEADER_BMSK                                           0x6
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_TXSYNCHEADER_SHFT                                           0x1
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_TXSTARTBLOCK_BMSK                                           0x1
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL5_SW_TXSTARTBLOCK_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_ADDR(x)                                                 ((x) + 0x000001f0)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_OFFS                                                    (0x000001f0)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_SW_TXDEEMPH_L_BMSK                                            0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL6_SW_TXDEEMPH_L_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_ADDR(x)                                                 ((x) + 0x000001f4)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_OFFS                                                    (0x000001f4)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_SW_TXDEEMPH_M_BMSK                                            0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL7_SW_TXDEEMPH_M_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_ADDR(x)                                                 ((x) + 0x000001f8)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_OFFS                                                    (0x000001f8)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_SW_LOCALPSETINDEX_BMSK                                        0xf0
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_SW_LOCALPSETINDEX_SHFT                                         0x4
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_SW_GETLOCALPSETCOEF_BMSK                                       0x8
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_SW_GETLOCALPSETCOEF_SHFT                                       0x3
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_SW_RXEQINPHASE0123_BMSK                                        0x4
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_SW_RXEQINPHASE0123_SHFT                                        0x2
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_SW_TXDEEMPH_H_BMSK                                             0x3
#define HWIO_PSP_PCIE_PHY_INSIG_SW_CTRL8_SW_TXDEEMPH_H_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_ADDR(x)                                                 ((x) + 0x000001fc)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_OFFS                                                    (0x000001fc)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_RMSK                                                          0x95
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_SW_TXSWING_MX_BMSK                                            0x80
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_SW_TXSWING_MX_SHFT                                             0x7
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_SW_TXMGN_MX_BMSK                                              0x10
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_SW_TXMGN_MX_SHFT                                               0x4
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_SW_RATE_MX_BMSK                                                0x4
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_SW_RATE_MX_SHFT                                                0x2
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_SW_POWERDOWN_MX_BMSK                                           0x1
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL1_SW_POWERDOWN_MX_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_ADDR(x)                                                 ((x) + 0x00000200)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_OFFS                                                    (0x00000200)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_SW_TXCOMPLIANCE_MX_BMSK                                       0xf0
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_SW_TXCOMPLIANCE_MX_SHFT                                        0x4
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_SW_TXELECIDLE_MX_BMSK                                          0xf
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL2_SW_TXELECIDLE_MX_SHFT                                          0x0

#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_ADDR(x)                                                 ((x) + 0x00000204)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_OFFS                                                    (0x00000204)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_RMSK                                                          0xff
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_SW_RXPOLARITY_MX_BMSK                                         0xf0
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_SW_RXPOLARITY_MX_SHFT                                          0x4
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_SW_TXDTCTRX_LPB_MX_BMSK                                        0xf
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL3_SW_TXDTCTRX_LPB_MX_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_ADDR(x)                                                 ((x) + 0x00000208)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_OFFS                                                    (0x00000208)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_RMSK                                                          0x1f
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_X16MODE_MX_BMSK                                            0x10
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_X16MODE_MX_SHFT                                             0x4
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_X8MODE_MX_BMSK                                              0x8
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_X8MODE_MX_SHFT                                              0x3
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_TXCM_DISABLE_MX_BMSK                                        0x4
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_TXCM_DISABLE_MX_SHFT                                        0x2
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_RXELECIDLE_DISABLE_MX_BMSK                                  0x2
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_RXELECIDLE_DISABLE_MX_SHFT                                  0x1
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_PCLKREQ_N_MX_BMSK                                           0x1
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL4_SW_PCLKREQ_N_MX_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_ADDR(x)                                                 ((x) + 0x0000020c)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_OFFS                                                    (0x0000020c)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_RMSK                                                          0xfb
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_RXEQINPROGRESS_MX_BMSK                                     0x80
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_RXEQINPROGRESS_MX_SHFT                                      0x7
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_INVALIDREQUEST_MX_BMSK                                     0x40
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_INVALIDREQUEST_MX_SHFT                                      0x6
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_RXEQEVAL_MX_BMSK                                           0x20
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_RXEQEVAL_MX_SHFT                                            0x5
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_BLOCKALIGNCONTROL_MX_BMSK                                  0x10
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_BLOCKALIGNCONTROL_MX_SHFT                                   0x4
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_TXDATAVALID_MX_BMSK                                         0x8
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_TXDATAVALID_MX_SHFT                                         0x3
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_TXSYNCHEADER_MX_BMSK                                        0x2
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_TXSYNCHEADER_MX_SHFT                                        0x1
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_TXSTARTBLOCK_MX_BMSK                                        0x1
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL5_SW_TXSTARTBLOCK_MX_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_ADDR(x)                                                 ((x) + 0x00000210)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_OFFS                                                    (0x00000210)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_RMSK                                                           0x1
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_SW_TXDEEMPH_MX_BMSK                                            0x1
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL6_SW_TXDEEMPH_MX_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_ADDR(x)                                                 ((x) + 0x00000214)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_OFFS                                                    (0x00000214)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_RMSK                                                          0x8c
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_ADDR(x), HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_RMSK)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_IN(x))
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_SW_LOCALPSETINDEX_MX_BMSK                                     0x80
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_SW_LOCALPSETINDEX_MX_SHFT                                      0x7
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_SW_GETLOCALPSETCOEF_MX_BMSK                                    0x8
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_SW_GETLOCALPSETCOEF_MX_SHFT                                    0x3
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_SW_RXEQINPHASE0123_MX_BMSK                                     0x4
#define HWIO_PSP_PCIE_PHY_INSIG_MX_CTRL8_SW_RXEQINPHASE0123_MX_SHFT                                     0x2

#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_ADDR(x)                                                   ((x) + 0x00000218)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_OFFS                                                      (0x00000218)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_RMSK                                                            0xff
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL_ADDR(x), HWIO_PSP_PCIE_PHY_TEST_CONTROL_RMSK)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TEST_CONTROL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TEST_CONTROL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TEST_CONTROL_IN(x))
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PCLK_ON_IN_L1SS_EN_BMSK                                         0x80
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PCLK_ON_IN_L1SS_EN_SHFT                                          0x7
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PLL_ON_IN_L1SS_EN_BMSK                                          0x40
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PLL_ON_IN_L1SS_EN_SHFT                                           0x6
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PCLK_ON_IN_P2_EN_BMSK                                           0x20
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PCLK_ON_IN_P2_EN_SHFT                                            0x5
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PLL_ON_IN_P2_EN_BMSK                                            0x10
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PLL_ON_IN_P2_EN_SHFT                                             0x4
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_FORCE_REC_DETECTED_BMSK                                          0x8
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_FORCE_REC_DETECTED_SHFT                                          0x3
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PCS_PCLK_SEL_BMSK                                                0x4
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_PCS_PCLK_SEL_SHFT                                                0x2
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_BIST_MODE_BMSK                                                   0x2
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_BIST_MODE_SHFT                                                   0x1
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_FORCE_RX_SIGDET_BMSK                                             0x1
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL_FORCE_RX_SIGDET_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_ADDR(x)                                                  ((x) + 0x0000021c)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_OFFS                                                     (0x0000021c)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL2_ADDR(x), HWIO_PSP_PCIE_PHY_TEST_CONTROL2_RMSK)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TEST_CONTROL2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TEST_CONTROL2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TEST_CONTROL2_IN(x))
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_PRE_DEBUG_BUS_IDX10_BMSK                                       0x1f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL2_PRE_DEBUG_BUS_IDX10_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_ADDR(x)                                                  ((x) + 0x00000220)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_OFFS                                                     (0x00000220)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_RMSK                                                           0x1f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL3_ADDR(x), HWIO_PSP_PCIE_PHY_TEST_CONTROL3_RMSK)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TEST_CONTROL3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TEST_CONTROL3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TEST_CONTROL3_IN(x))
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_PRE_DEBUG_BUS_IDX32_BMSK                                       0x1f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL3_PRE_DEBUG_BUS_IDX32_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_ADDR(x)                                                  ((x) + 0x00000224)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_OFFS                                                     (0x00000224)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_RMSK                                                           0x3f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL4_ADDR(x), HWIO_PSP_PCIE_PHY_TEST_CONTROL4_RMSK)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL4_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TEST_CONTROL4_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TEST_CONTROL4_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TEST_CONTROL4_IN(x))
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_DEBUG_BUS_IDX0_BMSK                                            0x3f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL4_DEBUG_BUS_IDX0_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_ADDR(x)                                                  ((x) + 0x00000228)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_OFFS                                                     (0x00000228)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_RMSK                                                           0x3f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL5_ADDR(x), HWIO_PSP_PCIE_PHY_TEST_CONTROL5_RMSK)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL5_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TEST_CONTROL5_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TEST_CONTROL5_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TEST_CONTROL5_IN(x))
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_DEBUG_BUS_IDX1_BMSK                                            0x3f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL5_DEBUG_BUS_IDX1_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_ADDR(x)                                                  ((x) + 0x0000022c)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_OFFS                                                     (0x0000022c)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_RMSK                                                           0x3f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL6_ADDR(x), HWIO_PSP_PCIE_PHY_TEST_CONTROL6_RMSK)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL6_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TEST_CONTROL6_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TEST_CONTROL6_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TEST_CONTROL6_IN(x))
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_DEBUG_BUS_IDX2_BMSK                                            0x3f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL6_DEBUG_BUS_IDX2_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_ADDR(x)                                                  ((x) + 0x00000230)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_OFFS                                                     (0x00000230)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_RMSK                                                           0x3f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL7_ADDR(x), HWIO_PSP_PCIE_PHY_TEST_CONTROL7_RMSK)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL7_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TEST_CONTROL7_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TEST_CONTROL7_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TEST_CONTROL7_IN(x))
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_DEBUG_BUS_IDX3_BMSK                                            0x3f
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL7_DEBUG_BUS_IDX3_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_ADDR(x)                                                  ((x) + 0x00000234)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_OFFS                                                     (0x00000234)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL8_ADDR(x), HWIO_PSP_PCIE_PHY_TEST_CONTROL8_RMSK)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_TEST_CONTROL8_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_TEST_CONTROL8_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_TEST_CONTROL8_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_TEST_CONTROL8_IN(x))
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_CLK_ON_TX_SEL_BMSK                                             0xe0
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_CLK_ON_TX_SEL_SHFT                                              0x5
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_CLK_ON_TX_EN_BMSK                                              0x10
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_CLK_ON_TX_EN_SHFT                                               0x4
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_USE_CLK_DEBUG_BUS1_BMSK                                         0x8
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_USE_CLK_DEBUG_BUS1_SHFT                                         0x3
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_USE_CLK_DEBUG_BUS0_BMSK                                         0x4
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_USE_CLK_DEBUG_BUS0_SHFT                                         0x2
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_DEBUG_CLK_IDX1_BMSK                                             0x2
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_DEBUG_CLK_IDX1_SHFT                                             0x1
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_DEBUG_CLK_IDX0_BMSK                                             0x1
#define HWIO_PSP_PCIE_PHY_TEST_CONTROL8_DEBUG_CLK_IDX0_SHFT                                             0x0

#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_ADDR(x)                                                ((x) + 0x00000238)
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_OFFS                                                   (0x00000238)
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_RMSK                                                         0xff
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_BIST_START_CTRL_ADDR(x), HWIO_PSP_PCIE_PHY_BIST_START_CTRL_RMSK)
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_BIST_START_CTRL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_BIST_START_CTRL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_BIST_START_CTRL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_BIST_START_CTRL_IN(x))
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L3_BIST_TX_EN_BMSK                                           0x80
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L3_BIST_TX_EN_SHFT                                            0x7
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L2_BIST_TX_EN_BMSK                                           0x40
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L2_BIST_TX_EN_SHFT                                            0x6
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L1_BIST_TX_EN_BMSK                                           0x20
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L1_BIST_TX_EN_SHFT                                            0x5
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L0_BIST_TX_EN_BMSK                                           0x10
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L0_BIST_TX_EN_SHFT                                            0x4
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L3_BIST_TXRX_EN_BMSK                                          0x8
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L3_BIST_TXRX_EN_SHFT                                          0x3
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L2_BIST_TXRX_EN_BMSK                                          0x4
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L2_BIST_TXRX_EN_SHFT                                          0x2
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L1_BIST_TXRX_EN_BMSK                                          0x2
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L1_BIST_TXRX_EN_SHFT                                          0x1
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L0_BIST_TXRX_EN_BMSK                                          0x1
#define HWIO_PSP_PCIE_PHY_BIST_START_CTRL_L0_BIST_TXRX_EN_SHFT                                          0x0

#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_ADDR(x)                                                  ((x) + 0x0000023c)
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_OFFS                                                     (0x0000023c)
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_ADDR(x), HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_RMSK)
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_IN(x))
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L1_BIST_CHK_ERR_CNT_CLR_BMSK                                   0x80
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L1_BIST_CHK_ERR_CNT_CLR_SHFT                                    0x7
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L1_BIST_RX_ERR_EN_BMSK                                         0x40
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L1_BIST_RX_ERR_EN_SHFT                                          0x6
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L1_BIST_GEN_SHORT_PATTERN_BMSK                                 0x20
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L1_BIST_GEN_SHORT_PATTERN_SHFT                                  0x5
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L1_BIST_PAT_SEL_BMSK                                           0x10
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L1_BIST_PAT_SEL_SHFT                                            0x4
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L0_BIST_CHK_ERR_CNT_CLR_BMSK                                    0x8
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L0_BIST_CHK_ERR_CNT_CLR_SHFT                                    0x3
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L0_BIST_RX_ERR_EN_BMSK                                          0x4
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L0_BIST_RX_ERR_EN_SHFT                                          0x2
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L0_BIST_GEN_SHORT_PATTERN_BMSK                                  0x2
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L0_BIST_GEN_SHORT_PATTERN_SHFT                                  0x1
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L0_BIST_PAT_SEL_BMSK                                            0x1
#define HWIO_PSP_PCIE_PHY_L10_BIST_CTRL_L0_BIST_PAT_SEL_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_ADDR(x)                                                  ((x) + 0x00000240)
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_OFFS                                                     (0x00000240)
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_ADDR(x), HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_RMSK)
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_IN(x))
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L3_BIST_CHK_ERR_CNT_CLR_BMSK                                   0x80
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L3_BIST_CHK_ERR_CNT_CLR_SHFT                                    0x7
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L3_BIST_RX_ERR_EN_BMSK                                         0x40
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L3_BIST_RX_ERR_EN_SHFT                                          0x6
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L3_BIST_GEN_SHORT_PATTERN_BMSK                                 0x20
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L3_BIST_GEN_SHORT_PATTERN_SHFT                                  0x5
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L3_BIST_PAT_SEL_BMSK                                           0x10
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L3_BIST_PAT_SEL_SHFT                                            0x4
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L2_BIST_CHK_ERR_CNT_CLR_BMSK                                    0x8
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L2_BIST_CHK_ERR_CNT_CLR_SHFT                                    0x3
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L2_BIST_RX_ERR_EN_BMSK                                          0x4
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L2_BIST_RX_ERR_EN_SHFT                                          0x2
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L2_BIST_GEN_SHORT_PATTERN_BMSK                                  0x2
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L2_BIST_GEN_SHORT_PATTERN_SHFT                                  0x1
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L2_BIST_PAT_SEL_BMSK                                            0x1
#define HWIO_PSP_PCIE_PHY_L32_BIST_CTRL_L2_BIST_PAT_SEL_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_ADDR(x)                                                     ((x) + 0x00000244)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_OFFS                                                        (0x00000244)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_RMSK                                                              0xff
#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRBS_POLY0_ADDR(x), HWIO_PSP_PCIE_PHY_PRBS_POLY0_RMSK)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRBS_POLY0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRBS_POLY0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRBS_POLY0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRBS_POLY0_IN(x))
#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_PRBS_POLY0_BMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_PRBS_POLY0_PRBS_POLY0_SHFT                                                    0x0

#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_ADDR(x)                                                     ((x) + 0x00000248)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_OFFS                                                        (0x00000248)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_RMSK                                                              0xff
#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRBS_POLY1_ADDR(x), HWIO_PSP_PCIE_PHY_PRBS_POLY1_RMSK)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PRBS_POLY1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_PRBS_POLY1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_PRBS_POLY1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_PRBS_POLY1_IN(x))
#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_PRBS_POLY1_BMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_PRBS_POLY1_PRBS_POLY1_SHFT                                                    0x0

#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_ADDR(x)                                                  ((x) + 0x0000024c)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_OFFS                                                     (0x0000024c)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_ADDR(x), HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_L0_PRBS_SEED0_BMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED0_L0_PRBS_SEED0_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_ADDR(x)                                                  ((x) + 0x00000250)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_OFFS                                                     (0x00000250)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_ADDR(x), HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_L0_PRBS_SEED1_BMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_L0_PRBS_SEED1_L0_PRBS_SEED1_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_ADDR(x)                                                  ((x) + 0x00000254)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_OFFS                                                     (0x00000254)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_ADDR(x), HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_L1_PRBS_SEED0_BMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED0_L1_PRBS_SEED0_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_ADDR(x)                                                  ((x) + 0x00000258)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_OFFS                                                     (0x00000258)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_ADDR(x), HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_L1_PRBS_SEED1_BMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_L1_PRBS_SEED1_L1_PRBS_SEED1_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_ADDR(x)                                                  ((x) + 0x0000025c)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_OFFS                                                     (0x0000025c)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_ADDR(x), HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_L2_PRBS_SEED0_BMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED0_L2_PRBS_SEED0_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_ADDR(x)                                                  ((x) + 0x00000260)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_OFFS                                                     (0x00000260)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_ADDR(x), HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_L2_PRBS_SEED1_BMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_L2_PRBS_SEED1_L2_PRBS_SEED1_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_ADDR(x)                                                  ((x) + 0x00000264)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_OFFS                                                     (0x00000264)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_ADDR(x), HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_L3_PRBS_SEED0_BMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED0_L3_PRBS_SEED0_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_ADDR(x)                                                  ((x) + 0x00000268)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_OFFS                                                     (0x00000268)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_ADDR(x), HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_L3_PRBS_SEED1_BMSK                                             0xff
#define HWIO_PSP_PCIE_PHY_L3_PRBS_SEED1_L3_PRBS_SEED1_SHFT                                              0x0

#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_ADDR(x)                                              ((x) + 0x0000026c)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_OFFS                                                 (0x0000026c)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_ADDR(x), HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT_SYNC_HDR_BMSK                                 0x30
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT_SYNC_HDR_SHFT                                  0x4
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT3_K_BMSK                                        0x8
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT3_K_SHFT                                        0x3
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT2_K_BMSK                                        0x4
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT2_K_SHFT                                        0x2
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT1_K_BMSK                                        0x2
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT1_K_SHFT                                        0x1
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT0_K_BMSK                                        0x1
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT_CTRL_L0_FIXED_PAT0_K_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_ADDR(x)                                                  ((x) + 0x00000270)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_OFFS                                                     (0x00000270)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_ADDR(x), HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_L0_FIXED_PAT0_0_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT0_L0_FIXED_PAT0_0_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_ADDR(x)                                                  ((x) + 0x00000274)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_OFFS                                                     (0x00000274)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_ADDR(x), HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_L0_FIXED_PAT1_1_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT1_L0_FIXED_PAT1_1_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_ADDR(x)                                                  ((x) + 0x00000278)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_OFFS                                                     (0x00000278)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_ADDR(x), HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_L0_FIXED_PAT2_2_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT2_L0_FIXED_PAT2_2_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_ADDR(x)                                                  ((x) + 0x0000027c)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_OFFS                                                     (0x0000027c)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_ADDR(x), HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_IN(x))
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_L0_FIXED_PAT3_3_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L0_FIXED_PAT3_L0_FIXED_PAT3_3_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_ADDR(x)                                              ((x) + 0x00000280)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_OFFS                                                 (0x00000280)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_ADDR(x), HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT_SYNC_HDR_BMSK                                 0x30
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT_SYNC_HDR_SHFT                                  0x4
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT3_K_BMSK                                        0x8
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT3_K_SHFT                                        0x3
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT2_K_BMSK                                        0x4
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT2_K_SHFT                                        0x2
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT1_K_BMSK                                        0x2
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT1_K_SHFT                                        0x1
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT0_K_BMSK                                        0x1
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT_CTRL_L1_FIXED_PAT0_K_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_ADDR(x)                                                  ((x) + 0x00000284)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_OFFS                                                     (0x00000284)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_ADDR(x), HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_L1_FIXED_PAT0_4_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT0_L1_FIXED_PAT0_4_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_ADDR(x)                                                  ((x) + 0x00000288)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_OFFS                                                     (0x00000288)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_ADDR(x), HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_L1_FIXED_PAT1_5_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT1_L1_FIXED_PAT1_5_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_ADDR(x)                                                  ((x) + 0x0000028c)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_OFFS                                                     (0x0000028c)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_ADDR(x), HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_L1_FIXED_PAT2_6_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT2_L1_FIXED_PAT2_6_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_ADDR(x)                                                  ((x) + 0x00000290)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_OFFS                                                     (0x00000290)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_ADDR(x), HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_IN(x))
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_L1_FIXED_PAT3_7_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L1_FIXED_PAT3_L1_FIXED_PAT3_7_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_ADDR(x)                                              ((x) + 0x00000294)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_OFFS                                                 (0x00000294)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_ADDR(x), HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT_SYNC_HDR_BMSK                                 0x30
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT_SYNC_HDR_SHFT                                  0x4
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT3_K_BMSK                                        0x8
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT3_K_SHFT                                        0x3
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT2_K_BMSK                                        0x4
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT2_K_SHFT                                        0x2
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT1_K_BMSK                                        0x2
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT1_K_SHFT                                        0x1
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT0_K_BMSK                                        0x1
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT_CTRL_L2_FIXED_PAT0_K_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_ADDR(x)                                                  ((x) + 0x00000298)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_OFFS                                                     (0x00000298)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_ADDR(x), HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_L2_FIXED_PAT0_8_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT0_L2_FIXED_PAT0_8_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_ADDR(x)                                                  ((x) + 0x0000029c)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_OFFS                                                     (0x0000029c)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_ADDR(x), HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_L2_FIXED_PAT1_9_BMSK                                           0xff
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT1_L2_FIXED_PAT1_9_SHFT                                            0x0

#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_ADDR(x)                                                  ((x) + 0x000002a0)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_OFFS                                                     (0x000002a0)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_ADDR(x), HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_L2_FIXED_PAT2_10_BMSK                                          0xff
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT2_L2_FIXED_PAT2_10_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_ADDR(x)                                                  ((x) + 0x000002a4)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_OFFS                                                     (0x000002a4)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_ADDR(x), HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_IN(x))
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_L2_FIXED_PAT3_11_BMSK                                          0xff
#define HWIO_PSP_PCIE_PHY_L2_FIXED_PAT3_L2_FIXED_PAT3_11_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_ADDR(x)                                              ((x) + 0x000002a8)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_OFFS                                                 (0x000002a8)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_RMSK                                                       0x3f
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_ADDR(x), HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT_SYNC_HDR_BMSK                                 0x30
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT_SYNC_HDR_SHFT                                  0x4
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT3_K_BMSK                                        0x8
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT3_K_SHFT                                        0x3
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT2_K_BMSK                                        0x4
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT2_K_SHFT                                        0x2
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT1_K_BMSK                                        0x2
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT1_K_SHFT                                        0x1
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT0_K_BMSK                                        0x1
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT_CTRL_L3_FIXED_PAT0_K_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_ADDR(x)                                                  ((x) + 0x000002ac)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_OFFS                                                     (0x000002ac)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_ADDR(x), HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_L3_FIXED_PAT0_12_BMSK                                          0xff
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT0_L3_FIXED_PAT0_12_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_ADDR(x)                                                  ((x) + 0x000002b0)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_OFFS                                                     (0x000002b0)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_ADDR(x), HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_L3_FIXED_PAT1_13_BMSK                                          0xff
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT1_L3_FIXED_PAT1_13_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_ADDR(x)                                                  ((x) + 0x000002b4)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_OFFS                                                     (0x000002b4)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_ADDR(x), HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_L3_FIXED_PAT2_14_BMSK                                          0xff
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT2_L3_FIXED_PAT2_14_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_ADDR(x)                                                  ((x) + 0x000002b8)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_OFFS                                                     (0x000002b8)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_RMSK                                                           0xff
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_ADDR(x), HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_OUT(x, v)      \
        out_dword(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_ADDR(x),v)
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_ADDR(x),m,v,HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_IN(x))
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_L3_FIXED_PAT3_15_BMSK                                          0xff
#define HWIO_PSP_PCIE_PHY_L3_FIXED_PAT3_L3_FIXED_PAT3_15_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_ADDR(x)                                          ((x) + 0x000002bc)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_OFFS                                             (0x000002bc)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_RMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_ADDR(x), HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_L0_BIST_CHK_ERR_CNT_L_BMSK                             0xff
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_L_L0_BIST_CHK_ERR_CNT_L_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_ADDR(x)                                          ((x) + 0x000002c0)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_OFFS                                             (0x000002c0)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_RMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_ADDR(x), HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_L0_BIST_CHK_ERR_CNT_H_BMSK                             0xff
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_ERR_CNT_H_L0_BIST_CHK_ERR_CNT_H_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_ADDR(x)                                          ((x) + 0x000002c4)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_OFFS                                             (0x000002c4)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_RMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_ADDR(x), HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_L1_BIST_CHK_ERR_CNT_L_BMSK                             0xff
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_L_L1_BIST_CHK_ERR_CNT_L_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_ADDR(x)                                          ((x) + 0x000002c8)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_OFFS                                             (0x000002c8)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_RMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_ADDR(x), HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_L1_BIST_CHK_ERR_CNT_H_BMSK                             0xff
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_ERR_CNT_H_L1_BIST_CHK_ERR_CNT_H_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_ADDR(x)                                          ((x) + 0x000002cc)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_OFFS                                             (0x000002cc)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_RMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_ADDR(x), HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_L2_BIST_CHK_ERR_CNT_L_BMSK                             0xff
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_L_L2_BIST_CHK_ERR_CNT_L_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_ADDR(x)                                          ((x) + 0x000002d0)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_OFFS                                             (0x000002d0)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_RMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_ADDR(x), HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_L2_BIST_CHK_ERR_CNT_H_BMSK                             0xff
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_ERR_CNT_H_L2_BIST_CHK_ERR_CNT_H_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_ADDR(x)                                          ((x) + 0x000002d4)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_OFFS                                             (0x000002d4)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_RMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_ADDR(x), HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_L3_BIST_CHK_ERR_CNT_L_BMSK                             0xff
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_L_L3_BIST_CHK_ERR_CNT_L_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_ADDR(x)                                          ((x) + 0x000002d8)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_OFFS                                             (0x000002d8)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_RMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_ADDR(x), HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_L3_BIST_CHK_ERR_CNT_H_BMSK                             0xff
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_ERR_CNT_H_L3_BIST_CHK_ERR_CNT_H_SHFT                              0x0

#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_ADDR(x)                                             ((x) + 0x000002dc)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_OFFS                                                (0x000002dc)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_RMSK                                                       0xf
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_L0_BIST_CHK_HEADER_SEL_BMSK                                0x8
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_L0_BIST_CHK_HEADER_SEL_SHFT                                0x3
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_L0_BIST_HEADER_NOT_FOUND_BMSK                              0x4
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_L0_BIST_HEADER_NOT_FOUND_SHFT                              0x2
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_L0_BIST_PAT_DATA_NOT_FOUND_BMSK                            0x2
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_L0_BIST_PAT_DATA_NOT_FOUND_SHFT                            0x1
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_L0_BIST_CHECK_DONE_BMSK                                    0x1
#define HWIO_PSP_PCIE_PHY_L0_BIST_CHK_STATUS_L0_BIST_CHECK_DONE_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_ADDR(x)                                             ((x) + 0x000002e0)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_OFFS                                                (0x000002e0)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_RMSK                                                       0xf
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_L1_BIST_CHK_HEADER_SEL_BMSK                                0x8
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_L1_BIST_CHK_HEADER_SEL_SHFT                                0x3
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_L1_BIST_HEADER_NOT_FOUND_BMSK                              0x4
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_L1_BIST_HEADER_NOT_FOUND_SHFT                              0x2
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_L1_BIST_PAT_DATA_NOT_FOUND_BMSK                            0x2
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_L1_BIST_PAT_DATA_NOT_FOUND_SHFT                            0x1
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_L1_BIST_CHECK_DONE_BMSK                                    0x1
#define HWIO_PSP_PCIE_PHY_L1_BIST_CHK_STATUS_L1_BIST_CHECK_DONE_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_ADDR(x)                                             ((x) + 0x000002e4)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_OFFS                                                (0x000002e4)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_RMSK                                                       0xf
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_L2_BIST_CHK_HEADER_SEL_BMSK                                0x8
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_L2_BIST_CHK_HEADER_SEL_SHFT                                0x3
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_L2_BIST_HEADER_NOT_FOUND_BMSK                              0x4
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_L2_BIST_HEADER_NOT_FOUND_SHFT                              0x2
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_L2_BIST_PAT_DATA_NOT_FOUND_BMSK                            0x2
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_L2_BIST_PAT_DATA_NOT_FOUND_SHFT                            0x1
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_L2_BIST_CHECK_DONE_BMSK                                    0x1
#define HWIO_PSP_PCIE_PHY_L2_BIST_CHK_STATUS_L2_BIST_CHECK_DONE_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_ADDR(x)                                             ((x) + 0x000002e8)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_OFFS                                                (0x000002e8)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_RMSK                                                       0xf
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_L3_BIST_CHK_HEADER_SEL_BMSK                                0x8
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_L3_BIST_CHK_HEADER_SEL_SHFT                                0x3
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_L3_BIST_HEADER_NOT_FOUND_BMSK                              0x4
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_L3_BIST_HEADER_NOT_FOUND_SHFT                              0x2
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_L3_BIST_PAT_DATA_NOT_FOUND_BMSK                            0x2
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_L3_BIST_PAT_DATA_NOT_FOUND_SHFT                            0x1
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_L3_BIST_CHECK_DONE_BMSK                                    0x1
#define HWIO_PSP_PCIE_PHY_L3_BIST_CHK_STATUS_L3_BIST_CHECK_DONE_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_PCS_STATUS_ADDR(x)                                                     ((x) + 0x000002ec)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_OFFS                                                        (0x000002ec)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_RMSK                                                              0xff
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_PCS_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_ACTIVE_STATE_STATUS_BMSK                                          0x80
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_ACTIVE_STATE_STATUS_SHFT                                           0x7
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_PHYSTATUS_BMSK                                                    0x40
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_PHYSTATUS_SHFT                                                     0x6
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_PCS_POWERDOWN_BMSK                                                0x30
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_PCS_POWERDOWN_SHFT                                                 0x4
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_FREEZE_POWERDOWN_BMSK                                              0x8
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_FREEZE_POWERDOWN_SHFT                                              0x3
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_POWER_STATE_BMSK                                                   0x7
#define HWIO_PSP_PCIE_PHY_PCS_STATUS_POWER_STATE_SHFT                                                   0x0

#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_ADDR(x)                                                    ((x) + 0x000002f0)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_OFFS                                                       (0x000002f0)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_RMSK                                                             0xff
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_STATUS2_ADDR(x), HWIO_PSP_PCIE_PHY_PCS_STATUS2_RMSK)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_STATUS2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_PCIEPHY_WIDTH_BMSK                                               0xc0
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_PCIEPHY_WIDTH_SHFT                                                0x6
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_DFE_TRAIN_EN_OR_BMSK                                             0x20
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_DFE_TRAIN_EN_OR_SHFT                                              0x5
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_REC_DETECT_DONE_BMSK                                             0x10
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_REC_DETECT_DONE_SHFT                                              0x4
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_REC_DETECT_OUTCOME_BMSK                                           0xf
#define HWIO_PSP_PCIE_PHY_PCS_STATUS2_REC_DETECT_OUTCOME_SHFT                                           0x0

#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_ADDR(x)                                                    ((x) + 0x000002f4)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_OFFS                                                       (0x000002f4)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_RMSK                                                             0xff
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_STATUS3_ADDR(x), HWIO_PSP_PCIE_PHY_PCS_STATUS3_RMSK)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_STATUS3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_PCLK_GATING_STATE_BMSK                                           0x80
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_PCLK_GATING_STATE_SHFT                                            0x7
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_PCS_CLOCK_SOURCE_BMSK                                            0x60
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_PCS_CLOCK_SOURCE_SHFT                                             0x5
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_QSERVER_PWR_ST_REQ_ACTV_BMSK                                     0x10
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_QSERVER_PWR_ST_REQ_ACTV_SHFT                                      0x4
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_QSERVER_PWR_STATE_REQ_BMSK                                        0xf
#define HWIO_PSP_PCIE_PHY_PCS_STATUS3_QSERVER_PWR_STATE_REQ_SHFT                                        0x0

#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_ADDR(x)                                                    ((x) + 0x000002f8)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_OFFS                                                       (0x000002f8)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_RMSK                                                             0xff
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_STATUS4_ADDR(x), HWIO_PSP_PCIE_PHY_PCS_STATUS4_RMSK)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_PCS_STATUS4_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_PCS_TX_ACTIVE_OR_BMSK                                            0x80
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_PCS_TX_ACTIVE_OR_SHFT                                             0x7
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_PCS_RX_ACTIVE_OR_BMSK                                            0x40
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_PCS_RX_ACTIVE_OR_SHFT                                             0x6
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_RXVALID_OR_BMSK                                                  0x20
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_RXVALID_OR_SHFT                                                   0x5
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_RXPOLARITY_OR_BMSK                                               0x10
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_RXPOLARITY_OR_SHFT                                                0x4
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_PCS_LANE_OFF_BMSK                                                 0xf
#define HWIO_PSP_PCIE_PHY_PCS_STATUS4_PCS_LANE_OFF_SHFT                                                 0x0

#define HWIO_PSP_PCIE_PHY_REVISION_ID0_ADDR(x)                                                   ((x) + 0x000002fc)
#define HWIO_PSP_PCIE_PHY_REVISION_ID0_OFFS                                                      (0x000002fc)
#define HWIO_PSP_PCIE_PHY_REVISION_ID0_RMSK                                                            0xff
#define HWIO_PSP_PCIE_PHY_REVISION_ID0_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_REVISION_ID0_ADDR(x), HWIO_PSP_PCIE_PHY_REVISION_ID0_RMSK)
#define HWIO_PSP_PCIE_PHY_REVISION_ID0_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_REVISION_ID0_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_REVISION_ID0_STEP_7_0_BMSK                                                   0xff
#define HWIO_PSP_PCIE_PHY_REVISION_ID0_STEP_7_0_SHFT                                                    0x0

#define HWIO_PSP_PCIE_PHY_REVISION_ID1_ADDR(x)                                                   ((x) + 0x00000300)
#define HWIO_PSP_PCIE_PHY_REVISION_ID1_OFFS                                                      (0x00000300)
#define HWIO_PSP_PCIE_PHY_REVISION_ID1_RMSK                                                            0xff
#define HWIO_PSP_PCIE_PHY_REVISION_ID1_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_REVISION_ID1_ADDR(x), HWIO_PSP_PCIE_PHY_REVISION_ID1_RMSK)
#define HWIO_PSP_PCIE_PHY_REVISION_ID1_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_REVISION_ID1_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_REVISION_ID1_STEP_15_8_BMSK                                                  0xff
#define HWIO_PSP_PCIE_PHY_REVISION_ID1_STEP_15_8_SHFT                                                   0x0

#define HWIO_PSP_PCIE_PHY_REVISION_ID2_ADDR(x)                                                   ((x) + 0x00000304)
#define HWIO_PSP_PCIE_PHY_REVISION_ID2_OFFS                                                      (0x00000304)
#define HWIO_PSP_PCIE_PHY_REVISION_ID2_RMSK                                                            0xff
#define HWIO_PSP_PCIE_PHY_REVISION_ID2_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_REVISION_ID2_ADDR(x), HWIO_PSP_PCIE_PHY_REVISION_ID2_RMSK)
#define HWIO_PSP_PCIE_PHY_REVISION_ID2_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_REVISION_ID2_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_REVISION_ID2_MINOR_7_0_BMSK                                                  0xff
#define HWIO_PSP_PCIE_PHY_REVISION_ID2_MINOR_7_0_SHFT                                                   0x0

#define HWIO_PSP_PCIE_PHY_REVISION_ID3_ADDR(x)                                                   ((x) + 0x00000308)
#define HWIO_PSP_PCIE_PHY_REVISION_ID3_OFFS                                                      (0x00000308)
#define HWIO_PSP_PCIE_PHY_REVISION_ID3_RMSK                                                            0xff
#define HWIO_PSP_PCIE_PHY_REVISION_ID3_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_REVISION_ID3_ADDR(x), HWIO_PSP_PCIE_PHY_REVISION_ID3_RMSK)
#define HWIO_PSP_PCIE_PHY_REVISION_ID3_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_REVISION_ID3_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_REVISION_ID3_MAJOR_BMSK                                                      0xf0
#define HWIO_PSP_PCIE_PHY_REVISION_ID3_MAJOR_SHFT                                                       0x4
#define HWIO_PSP_PCIE_PHY_REVISION_ID3_MINOR_11_8_BMSK                                                  0xf
#define HWIO_PSP_PCIE_PHY_REVISION_ID3_MINOR_11_8_SHFT                                                  0x0

#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_ADDR(x)                                             ((x) + 0x0000030c)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_OFFS                                                (0x0000030c)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_RMSK                                                      0xff
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_DEBUG_BUS_0_STATUS_BMSK                                   0xff
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_0_STATUS_DEBUG_BUS_0_STATUS_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_ADDR(x)                                             ((x) + 0x00000310)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_OFFS                                                (0x00000310)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_RMSK                                                      0xff
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_DEBUG_BUS_1_STATUS_BMSK                                   0xff
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_1_STATUS_DEBUG_BUS_1_STATUS_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_ADDR(x)                                             ((x) + 0x00000314)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_OFFS                                                (0x00000314)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_RMSK                                                      0xff
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_DEBUG_BUS_2_STATUS_BMSK                                   0xff
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_2_STATUS_DEBUG_BUS_2_STATUS_SHFT                                    0x0

#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_ADDR(x)                                             ((x) + 0x00000318)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_OFFS                                                (0x00000318)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_RMSK                                                      0xff
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_IN(x)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_ADDR(x), HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_RMSK)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_ADDR(x), m)
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_DEBUG_BUS_3_STATUS_BMSK                                   0xff
#define HWIO_PSP_PCIE_PHY_DEBUG_BUS_3_STATUS_DEBUG_BUS_3_STATUS_SHFT                                    0x0


#endif /* __PCIEPHYPCSQDF2400HWIO_H__ */
