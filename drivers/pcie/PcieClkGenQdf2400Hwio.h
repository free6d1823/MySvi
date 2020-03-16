#ifndef __PCIECLKGENQDF2400HWIO_H__
#define __PCIECLKGENQDF2400HWIO_H__
/*
===========================================================================
*/
/**
  @file PcieClkGenQdf2400Hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r64.0]

  This file contains HWIO register definitions for the following modules:
    PCIE_CLKGEN_A2P_AHB2PHY_SWMAN
    PCIE_CLKGEN_QSERVER_SERDES_CLKGEN

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
 * MODULE: PCIE_CLKGEN_A2P_AHB2PHY_SWMAN
 *--------------------------------------------------------------------------*/

#define PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE                                               (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_BASE      + 0x00000000)
#define PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE_OFFS                                          0x00000000

#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_ADDR                                                 (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE      + 0x00000000)
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_OFFS                                                 (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE_OFFS + 0x00000000)
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_RMSK                                                   0xffffff
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_HW_VERSION_ADDR, HWIO_PCIE_CLKGEN_A2P_HW_VERSION_RMSK)
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_HW_VERSION_ADDR, m)
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_MAJOR_BMSK                                             0xff0000
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_MAJOR_SHFT                                                 0x10
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_MINOR_BMSK                                               0xff00
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_MINOR_SHFT                                                  0x8
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_STEP_BMSK                                                  0xff
#define HWIO_PCIE_CLKGEN_A2P_HW_VERSION_STEP_SHFT                                                   0x0

#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_ADDR                                                    (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE      + 0x00000004)
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_OFFS                                                    (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE_OFFS + 0x00000004)
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_RMSK                                                    0xffffffff
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_HW_INFO_ADDR, HWIO_PCIE_CLKGEN_A2P_HW_INFO_RMSK)
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_HW_INFO_ADDR, m)
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_HW_MAJOR_BMSK                                           0xff000000
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_HW_MAJOR_SHFT                                                 0x18
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_HW_BRANCH_BMSK                                            0xff0000
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_HW_BRANCH_SHFT                                                0x10
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_HW_MINOR_BMSK                                               0xff00
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_HW_MINOR_SHFT                                                  0x8
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_HW_ECO_BMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_A2P_HW_INFO_HW_ECO_SHFT                                                    0x0

#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR                             (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE      + 0x00000008)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_OFFS                             (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE_OFFS + 0x00000008)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_RMSK                             0xffffffff
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR, HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_RMSK)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR, m)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR,v)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR,m,v,HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_IN)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_BROADCAST_EN_LOWER_BMSK          0xffffffff
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_BROADCAST_EN_LOWER_SHFT                 0x0

#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR                             (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE      + 0x0000000c)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_OFFS                             (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE_OFFS + 0x0000000c)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_RMSK                             0x3fffffff
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR, HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_RMSK)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR, m)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR,v)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR,m,v,HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_IN)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_BROADCAST_EN_UPPER_BMSK          0x3fffffff
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_BROADCAST_EN_UPPER_SHFT                 0x0

#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_ADDR                                            (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE      + 0x00000010)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_OFFS                                            (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE_OFFS + 0x00000010)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_RMSK                                                  0x33
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_ADDR, HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_RMSK)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_ADDR, m)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_ADDR,v)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_ADDR,m,v,HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_IN)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_BMSK                                0x30
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_SHFT                                 0x4
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_NO_WAIT_STATES_FVAL                  0x0
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_ONE_WAIT_STATE_FVAL                  0x1
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_TWO_WAIT_STATES_FVAL                 0x2
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_THREE_WAIT_STATES_FVAL               0x3
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_BMSK                                  0x3
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_SHFT                                  0x0
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_NO_WAIT_STATES_FVAL                   0x0
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_ONE_WAIT_STATE_FVAL                   0x1
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_TWO_WAIT_STATES_FVAL                  0x2
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_THREE_WAIT_STATES_FVAL                0x3

#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR                                      (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE      + 0x00000014)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_OFFS                                      (PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_REG_BASE_OFFS + 0x00000014)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_RMSK                                             0x3
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR, HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_RMSK)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR, m)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR,v)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR,m,v,HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_IN)
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_BMSK                               0x3
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SHFT                               0x0
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_NONE_OUTPUT_ZERO_FVAL              0x0
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SELECT_DEBUG_OUTPUT_ONE_FVAL        0x1
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SELECT_DEBUG_OUTPUT_TWO_FVAL        0x2
#define HWIO_PCIE_CLKGEN_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SELECT_DEBUG_OUTPUT_THREE_FVAL        0x3

/*----------------------------------------------------------------------------
 * MODULE: PCIE_CLKGEN_QSERVER_SERDES_CLKGEN
 *--------------------------------------------------------------------------*/

#define PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_BASE      + 0x00000000)
#define PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS                                     0x00000000

#define HWIO_PCIE_CLKGEN_ATB_SEL1_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000000)
#define HWIO_PCIE_CLKGEN_ATB_SEL1_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000000)
#define HWIO_PCIE_CLKGEN_ATB_SEL1_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_ATB_SEL1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_ATB_SEL1_ADDR, HWIO_PCIE_CLKGEN_ATB_SEL1_RMSK)
#define HWIO_PCIE_CLKGEN_ATB_SEL1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_ATB_SEL1_ADDR, m)
#define HWIO_PCIE_CLKGEN_ATB_SEL1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_ATB_SEL1_ADDR,v)
#define HWIO_PCIE_CLKGEN_ATB_SEL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_ATB_SEL1_ADDR,m,v,HWIO_PCIE_CLKGEN_ATB_SEL1_IN)
#define HWIO_PCIE_CLKGEN_ATB_SEL1_ATB_SEL_7_0_BMSK                                                0xff
#define HWIO_PCIE_CLKGEN_ATB_SEL1_ATB_SEL_7_0_SHFT                                                 0x0

#define HWIO_PCIE_CLKGEN_ATB_SEL2_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000004)
#define HWIO_PCIE_CLKGEN_ATB_SEL2_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000004)
#define HWIO_PCIE_CLKGEN_ATB_SEL2_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_ATB_SEL2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_ATB_SEL2_ADDR, HWIO_PCIE_CLKGEN_ATB_SEL2_RMSK)
#define HWIO_PCIE_CLKGEN_ATB_SEL2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_ATB_SEL2_ADDR, m)
#define HWIO_PCIE_CLKGEN_ATB_SEL2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_ATB_SEL2_ADDR,v)
#define HWIO_PCIE_CLKGEN_ATB_SEL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_ATB_SEL2_ADDR,m,v,HWIO_PCIE_CLKGEN_ATB_SEL2_IN)
#define HWIO_PCIE_CLKGEN_ATB_SEL2_ATB_SEL_15_8_BMSK                                               0xff
#define HWIO_PCIE_CLKGEN_ATB_SEL2_ATB_SEL_15_8_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_ATB_SEL3_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000008)
#define HWIO_PCIE_CLKGEN_ATB_SEL3_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000008)
#define HWIO_PCIE_CLKGEN_ATB_SEL3_RMSK                                                             0x7
#define HWIO_PCIE_CLKGEN_ATB_SEL3_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_ATB_SEL3_ADDR, HWIO_PCIE_CLKGEN_ATB_SEL3_RMSK)
#define HWIO_PCIE_CLKGEN_ATB_SEL3_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_ATB_SEL3_ADDR, m)
#define HWIO_PCIE_CLKGEN_ATB_SEL3_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_ATB_SEL3_ADDR,v)
#define HWIO_PCIE_CLKGEN_ATB_SEL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_ATB_SEL3_ADDR,m,v,HWIO_PCIE_CLKGEN_ATB_SEL3_IN)
#define HWIO_PCIE_CLKGEN_ATB_SEL3_ATB_SEL_18_16_BMSK                                               0x7
#define HWIO_PCIE_CLKGEN_ATB_SEL3_ATB_SEL_18_16_SHFT                                               0x0

#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_ADDR                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000000c)
#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_OFFS                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000000c)
#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_RMSK                                                          0x1
#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_FREQ_UPDATE_ADDR, HWIO_PCIE_CLKGEN_FREQ_UPDATE_RMSK)
#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_FREQ_UPDATE_ADDR, m)
#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_FREQ_UPDATE_ADDR,v)
#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_FREQ_UPDATE_ADDR,m,v,HWIO_PCIE_CLKGEN_FREQ_UPDATE_IN)
#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_PLL_FREQ_UPDATE_BMSK                                          0x1
#define HWIO_PCIE_CLKGEN_FREQ_UPDATE_PLL_FREQ_UPDATE_SHFT                                          0x0

#define HWIO_PCIE_CLKGEN_BG_TIMER_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000010)
#define HWIO_PCIE_CLKGEN_BG_TIMER_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000010)
#define HWIO_PCIE_CLKGEN_BG_TIMER_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_BG_TIMER_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_BG_TIMER_ADDR, HWIO_PCIE_CLKGEN_BG_TIMER_RMSK)
#define HWIO_PCIE_CLKGEN_BG_TIMER_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_BG_TIMER_ADDR, m)
#define HWIO_PCIE_CLKGEN_BG_TIMER_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_BG_TIMER_ADDR,v)
#define HWIO_PCIE_CLKGEN_BG_TIMER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_BG_TIMER_ADDR,m,v,HWIO_PCIE_CLKGEN_BG_TIMER_IN)
#define HWIO_PCIE_CLKGEN_BG_TIMER_SYSCLK_WAKE_BYPASS_BMSK                                         0x80
#define HWIO_PCIE_CLKGEN_BG_TIMER_SYSCLK_WAKE_BYPASS_SHFT                                          0x7
#define HWIO_PCIE_CLKGEN_BG_TIMER_SYSCLK_WAKE_TIME_BMSK                                           0x70
#define HWIO_PCIE_CLKGEN_BG_TIMER_SYSCLK_WAKE_TIME_SHFT                                            0x4
#define HWIO_PCIE_CLKGEN_BG_TIMER_REFCLK_FREQ_SEL_BMSK                                             0x8
#define HWIO_PCIE_CLKGEN_BG_TIMER_REFCLK_FREQ_SEL_SHFT                                             0x3
#define HWIO_PCIE_CLKGEN_BG_TIMER_BG_WAIT_TIME_BMSK                                                0x7
#define HWIO_PCIE_CLKGEN_BG_TIMER_BG_WAIT_TIME_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000014)
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000014)
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_RMSK                                                        0x3
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_EN_CENTER_ADDR, HWIO_PCIE_CLKGEN_SSC_EN_CENTER_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_EN_CENTER_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_EN_CENTER_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_EN_CENTER_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_EN_CENTER_IN)
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_SSC_CENTER_BMSK                                             0x2
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_SSC_CENTER_SHFT                                             0x1
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_SSC_EN_BMSK                                                 0x1
#define HWIO_PCIE_CLKGEN_SSC_EN_CENTER_SSC_EN_SHFT                                                 0x0

#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000018)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000018)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_RMSK                                                        0xff
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_ADDR, HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_IN)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_SSC_ADJPER_7_0_BMSK                                         0xff
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER1_SSC_ADJPER_7_0_SHFT                                          0x0

#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000001c)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000001c)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_RMSK                                                         0x3
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_ADDR, HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_IN)
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_SSC_ADJPER_9_8_BMSK                                          0x3
#define HWIO_PCIE_CLKGEN_SSC_ADJ_PER2_SSC_ADJPER_9_8_SHFT                                          0x0

#define HWIO_PCIE_CLKGEN_SSC_PER1_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000020)
#define HWIO_PCIE_CLKGEN_SSC_PER1_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000020)
#define HWIO_PCIE_CLKGEN_SSC_PER1_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_SSC_PER1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_PER1_ADDR, HWIO_PCIE_CLKGEN_SSC_PER1_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_PER1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_PER1_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_PER1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_PER1_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_PER1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_PER1_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_PER1_IN)
#define HWIO_PCIE_CLKGEN_SSC_PER1_SSC_PER_7_0_BMSK                                                0xff
#define HWIO_PCIE_CLKGEN_SSC_PER1_SSC_PER_7_0_SHFT                                                 0x0

#define HWIO_PCIE_CLKGEN_SSC_PER2_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000024)
#define HWIO_PCIE_CLKGEN_SSC_PER2_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000024)
#define HWIO_PCIE_CLKGEN_SSC_PER2_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_SSC_PER2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_PER2_ADDR, HWIO_PCIE_CLKGEN_SSC_PER2_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_PER2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_PER2_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_PER2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_PER2_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_PER2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_PER2_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_PER2_IN)
#define HWIO_PCIE_CLKGEN_SSC_PER2_SSC_PER_15_8_BMSK                                               0xff
#define HWIO_PCIE_CLKGEN_SSC_PER2_SSC_PER_15_8_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_ADDR                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000028)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_OFFS                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000028)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_RMSK                                                      0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_SSC_STEPSIZE_7_0_BMSK                                     0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_SSC_STEPSIZE_7_0_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_ADDR                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000002c)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_OFFS                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000002c)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_RMSK                                                      0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_SSC_STEPSIZE_15_8_BMSK                                    0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_SSC_STEPSIZE_15_8_SHFT                                     0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_ADDR                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000030)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_OFFS                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000030)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_RMSK                                                       0x1
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_SSC_STEPSIZE_16_16_BMSK                                    0x1
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_SSC_STEPSIZE_16_16_SHFT                                    0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000034)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000034)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_RMSK                                                0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_SSC_STEPSIZE_MODE1_7_0_BMSK                         0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE1_SSC_STEPSIZE_MODE1_7_0_SHFT                          0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000038)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000038)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_RMSK                                                0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_SSC_STEPSIZE_MODE1_15_8_BMSK                        0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE1_SSC_STEPSIZE_MODE1_15_8_SHFT                         0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000003c)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000003c)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_RMSK                                                 0x1
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_SSC_STEPSIZE_MODE1_16_16_BMSK                        0x1
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE1_SSC_STEPSIZE_MODE1_16_16_SHFT                        0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000040)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000040)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_RMSK                                                0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_SSC_STEPSIZE_MODE2_7_0_BMSK                         0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_MODE2_SSC_STEPSIZE_MODE2_7_0_SHFT                          0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000044)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000044)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_RMSK                                                0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_SSC_STEPSIZE_MODE2_15_8_BMSK                        0xff
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_MODE2_SSC_STEPSIZE_MODE2_15_8_SHFT                         0x0

#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000048)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000048)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_RMSK                                                 0x1
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_ADDR, HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_IN)
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_SSC_STEPSIZE_MODE2_16_16_BMSK                        0x1
#define HWIO_PCIE_CLKGEN_SSC_STEP_SIZE3_MODE2_SSC_STEPSIZE_MODE2_16_16_SHFT                        0x0

#define HWIO_PCIE_CLKGEN_POST_DIV_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000004c)
#define HWIO_PCIE_CLKGEN_POST_DIV_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000004c)
#define HWIO_PCIE_CLKGEN_POST_DIV_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_POST_DIV_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_POST_DIV_ADDR, HWIO_PCIE_CLKGEN_POST_DIV_RMSK)
#define HWIO_PCIE_CLKGEN_POST_DIV_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_POST_DIV_ADDR, m)
#define HWIO_PCIE_CLKGEN_POST_DIV_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_POST_DIV_ADDR,v)
#define HWIO_PCIE_CLKGEN_POST_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_POST_DIV_ADDR,m,v,HWIO_PCIE_CLKGEN_POST_DIV_IN)
#define HWIO_PCIE_CLKGEN_POST_DIV_PLL_POSTDIV_7_0_BMSK                                            0xff
#define HWIO_PCIE_CLKGEN_POST_DIV_PLL_POSTDIV_7_0_SHFT                                             0x0

#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000050)
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000050)
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_RMSK                                                         0x3
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_POST_DIV_MUX_ADDR, HWIO_PCIE_CLKGEN_POST_DIV_MUX_RMSK)
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_POST_DIV_MUX_ADDR, m)
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_POST_DIV_MUX_ADDR,v)
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_POST_DIV_MUX_ADDR,m,v,HWIO_PCIE_CLKGEN_POST_DIV_MUX_IN)
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_PLL_POSTDIV_MUX_BMSK                                         0x2
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_PLL_POSTDIV_MUX_SHFT                                         0x1
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_PLL_POSTDIV_8_8_BMSK                                         0x1
#define HWIO_PCIE_CLKGEN_POST_DIV_MUX_PLL_POSTDIV_8_8_SHFT                                         0x0

#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_ADDR                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000054)
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_OFFS                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000054)
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_RMSK                                                 0x7f
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_ADDR, HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_RMSK)
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_ADDR, m)
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_ADDR,v)
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_ADDR,m,v,HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_IN)
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_CLKBUF_RX_DRIVE_R_BMSK                               0x40
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_CLKBUF_RX_DRIVE_R_SHFT                                0x6
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_CLKBUF_RX_DRIVE_L_BMSK                               0x20
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_CLKBUF_RX_DRIVE_L_SHFT                                0x5
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_EN_SYSCLK_TX_SEL_BMSK                                0x10
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_EN_SYSCLK_TX_SEL_SHFT                                 0x4
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_CLKBUF_L_EN_BMSK                                      0x8
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_CLKBUF_L_EN_SHFT                                      0x3
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_CLKBUF_R_EN_BMSK                                      0x4
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_CLKBUF_R_EN_SHFT                                      0x2
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_BIAS_EN_MUX_BMSK                                      0x2
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_BIAS_EN_MUX_SHFT                                      0x1
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_BIAS_EN_BMSK                                          0x1
#define HWIO_PCIE_CLKGEN_BIAS_EN_CLKBUFLR_EN_BIAS_EN_SHFT                                          0x0

#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000058)
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_OFFS                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000058)
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_RMSK                                                         0xff
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR, HWIO_PCIE_CLKGEN_CLK_ENABLE1_RMSK)
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR,m,v,HWIO_PCIE_CLKGEN_CLK_ENABLE1_IN)
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_CLKDRVIDLE_EN_BMSK                                           0x80
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_CLKDRVIDLE_EN_SHFT                                            0x7
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_EN_SYSCLK_TX_PS3PS4_BMSK                                     0x40
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_EN_SYSCLK_TX_PS3PS4_SHFT                                      0x6
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_EN_SYSCLK_TX_PS0PS1PS2_BMSK                                  0x20
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_EN_SYSCLK_TX_PS0PS1PS2_SHFT                                   0x5
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_CLK_EP_EN_BMSK                                               0x10
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_CLK_EP_EN_SHFT                                                0x4
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_PLL_TXCLK_EN_MUX_BMSK                                         0x8
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_PLL_TXCLK_EN_MUX_SHFT                                         0x3
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_PLL_TXCLK_EN_BMSK                                             0x4
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_PLL_TXCLK_EN_SHFT                                             0x2
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_PLL_RXCLK_EN_MUX_BMSK                                         0x2
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_PLL_RXCLK_EN_MUX_SHFT                                         0x1
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_PLL_RXCLK_EN_BMSK                                             0x1
#define HWIO_PCIE_CLKGEN_CLK_ENABLE1_PLL_RXCLK_EN_SHFT                                             0x0

#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000005c)
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000005c)
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_RMSK                                                         0xf
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_ADDR, HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_RMSK)
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_IN)
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_SYSCLK_DIV2_SEL_BMSK                                         0x8
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_SYSCLK_DIV2_SEL_SHFT                                         0x3
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_SYSCLK_CM_BMSK                                               0x4
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_SYSCLK_CM_SHFT                                               0x2
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_SYSCLK_AC_COUPLE_BMSK                                        0x2
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_SYSCLK_AC_COUPLE_SHFT                                        0x1
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_SYSCLK_GNDTERM_BMSK                                          0x1
#define HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_SYSCLK_GNDTERM_SHFT                                          0x0

#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_ADDR                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000060)
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_OFFS                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000060)
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_RMSK                                                    0x7
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_ADDR, HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_RMSK)
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_ADDR, m)
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_ADDR,v)
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_ADDR,m,v,HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_IN)
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_SYSCLK_EN_PS3PS4_BMSK                                   0x4
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_SYSCLK_EN_PS3PS4_SHFT                                   0x2
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_SYSCLK_BUF_EN_MUX_BMSK                                  0x2
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_SYSCLK_BUF_EN_MUX_SHFT                                  0x1
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_SW_SYSCLK_BUF_EN_BMSK                                   0x1
#define HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_SW_SYSCLK_BUF_EN_SHFT                                   0x0

#define HWIO_PCIE_CLKGEN_PLL_EN_ADDR                                                        (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000064)
#define HWIO_PCIE_CLKGEN_PLL_EN_OFFS                                                        (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000064)
#define HWIO_PCIE_CLKGEN_PLL_EN_RMSK                                                               0x3
#define HWIO_PCIE_CLKGEN_PLL_EN_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_EN_ADDR, HWIO_PCIE_CLKGEN_PLL_EN_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_EN_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_EN_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_EN_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_EN_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_EN_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_EN_IN)
#define HWIO_PCIE_CLKGEN_PLL_EN_PLL_EN_MUX_BMSK                                                    0x2
#define HWIO_PCIE_CLKGEN_PLL_EN_PLL_EN_MUX_SHFT                                                    0x1
#define HWIO_PCIE_CLKGEN_PLL_EN_PLL_EN_BMSK                                                        0x1
#define HWIO_PCIE_CLKGEN_PLL_EN_PLL_EN_SHFT                                                        0x0

#define HWIO_PCIE_CLKGEN_PLL_IVCO_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000068)
#define HWIO_PCIE_CLKGEN_PLL_IVCO_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000068)
#define HWIO_PCIE_CLKGEN_PLL_IVCO_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_PLL_IVCO_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_IVCO_ADDR, HWIO_PCIE_CLKGEN_PLL_IVCO_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_IVCO_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_IVCO_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_IVCO_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_IVCO_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_IVCO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_IVCO_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_IVCO_IN)
#define HWIO_PCIE_CLKGEN_PLL_IVCO_PLL_IVCO_BMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_PLL_IVCO_PLL_IVCO_SHFT                                                    0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000006c)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000006c)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_PLLLOCK_CMP_MODE0_7_0_BMSK                               0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_PLLLOCK_CMP_MODE0_7_0_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000070)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000070)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_PLLLOCK_CMP_MODE0_15_8_BMSK                              0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_PLLLOCK_CMP_MODE0_15_8_SHFT                               0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000074)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000074)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_RMSK                                                      0x3
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_PLLLOCK_CMP_MODE0_17_16_BMSK                              0x3
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_PLLLOCK_CMP_MODE0_17_16_SHFT                              0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000078)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000078)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_PLLLOCK_CMP_MODE1_7_0_BMSK                               0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE1_PLLLOCK_CMP_MODE1_7_0_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000007c)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000007c)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_PLLLOCK_CMP_MODE1_15_8_BMSK                              0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE1_PLLLOCK_CMP_MODE1_15_8_SHFT                               0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000080)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000080)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_RMSK                                                      0x3
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_PLLLOCK_CMP_MODE1_17_16_BMSK                              0x3
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE1_PLLLOCK_CMP_MODE1_17_16_SHFT                              0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000084)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000084)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_PLLLOCK_CMP_MODE2_7_0_BMSK                               0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE2_PLLLOCK_CMP_MODE2_7_0_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000088)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000088)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_PLLLOCK_CMP_MODE2_15_8_BMSK                              0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE2_PLLLOCK_CMP_MODE2_15_8_SHFT                               0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000008c)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000008c)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_RMSK                                                      0x3
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_PLLLOCK_CMP_MODE2_17_16_BMSK                              0x3
#define HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE2_PLLLOCK_CMP_MODE2_17_16_SHFT                              0x0

#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000090)
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000090)
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_RMSK                                                0x3f
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_ADDR, HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_RMSK)
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_IN)
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_DIVSEL_MUX_BMSK                       0x20
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_DIVSEL_MUX_SHFT                        0x5
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_DIVSEL_BMSK                           0x18
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_DIVSEL_SHFT                            0x3
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_FORCE_BMSK                             0x4
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_FORCE_SHFT                             0x2
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_EN_MUX_BMSK                            0x2
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_EN_MUX_SHFT                            0x1
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_EN_BMSK                                0x1
#define HWIO_PCIE_CLKGEN_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_EN_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_ADDR                                        (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000094)
#define HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_OFFS                                        (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000094)
#define HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_RMSK                                               0x1
#define HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_ADDR, HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_SYSCLK_CLKDET_COMP_BMSK                            0x1
#define HWIO_PCIE_CLKGEN_SYSCLK_DET_COMP_STATUS_SYSCLK_CLKDET_COMP_SHFT                            0x0

#define HWIO_PCIE_CLKGEN_BGV_TRIM_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000098)
#define HWIO_PCIE_CLKGEN_BGV_TRIM_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000098)
#define HWIO_PCIE_CLKGEN_BGV_TRIM_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_BGV_TRIM_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_BGV_TRIM_ADDR, HWIO_PCIE_CLKGEN_BGV_TRIM_RMSK)
#define HWIO_PCIE_CLKGEN_BGV_TRIM_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_BGV_TRIM_ADDR, m)
#define HWIO_PCIE_CLKGEN_BGV_TRIM_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_BGV_TRIM_ADDR,v)
#define HWIO_PCIE_CLKGEN_BGV_TRIM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_BGV_TRIM_ADDR,m,v,HWIO_PCIE_CLKGEN_BGV_TRIM_IN)
#define HWIO_PCIE_CLKGEN_BGV_TRIM_BGV_TRIM_BMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_BGV_TRIM_BGV_TRIM_SHFT                                                    0x0

#define HWIO_PCIE_CLKGEN_BGT_TRIM_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000009c)
#define HWIO_PCIE_CLKGEN_BGT_TRIM_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000009c)
#define HWIO_PCIE_CLKGEN_BGT_TRIM_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_BGT_TRIM_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_BGT_TRIM_ADDR, HWIO_PCIE_CLKGEN_BGT_TRIM_RMSK)
#define HWIO_PCIE_CLKGEN_BGT_TRIM_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_BGT_TRIM_ADDR, m)
#define HWIO_PCIE_CLKGEN_BGT_TRIM_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_BGT_TRIM_ADDR,v)
#define HWIO_PCIE_CLKGEN_BGT_TRIM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_BGT_TRIM_ADDR,m,v,HWIO_PCIE_CLKGEN_BGT_TRIM_IN)
#define HWIO_PCIE_CLKGEN_BGT_TRIM_BGT_TRIM_BMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_BGT_TRIM_BGT_TRIM_SHFT                                                    0x0

#define HWIO_PCIE_CLKGEN_CLK_IETRIM_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000a0)
#define HWIO_PCIE_CLKGEN_CLK_IETRIM_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000a0)
#define HWIO_PCIE_CLKGEN_CLK_IETRIM_RMSK                                                          0x3f
#define HWIO_PCIE_CLKGEN_CLK_IETRIM_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_IETRIM_ADDR, HWIO_PCIE_CLKGEN_CLK_IETRIM_RMSK)
#define HWIO_PCIE_CLKGEN_CLK_IETRIM_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_IETRIM_ADDR, m)
#define HWIO_PCIE_CLKGEN_CLK_IETRIM_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CLK_IETRIM_ADDR,v)
#define HWIO_PCIE_CLKGEN_CLK_IETRIM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CLK_IETRIM_ADDR,m,v,HWIO_PCIE_CLKGEN_CLK_IETRIM_IN)
#define HWIO_PCIE_CLKGEN_CLK_IETRIM_CLK_IETRIM_BMSK                                               0x3f
#define HWIO_PCIE_CLKGEN_CLK_IETRIM_CLK_IETRIM_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000a4)
#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000a4)
#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_RMSK                                                          0x3f
#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_IPTRIM_ADDR, HWIO_PCIE_CLKGEN_CLK_IPTRIM_RMSK)
#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_IPTRIM_ADDR, m)
#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CLK_IPTRIM_ADDR,v)
#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CLK_IPTRIM_ADDR,m,v,HWIO_PCIE_CLKGEN_CLK_IPTRIM_IN)
#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_CLK_IPTRIM_BMSK                                               0x3f
#define HWIO_PCIE_CLKGEN_CLK_IPTRIM_CLK_IPTRIM_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000a8)
#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000a8)
#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_RMSK                                                          0xff
#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_EP_DIV_ADDR, HWIO_PCIE_CLKGEN_CLK_EP_DIV_RMSK)
#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_EP_DIV_ADDR, m)
#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CLK_EP_DIV_ADDR,v)
#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CLK_EP_DIV_ADDR,m,v,HWIO_PCIE_CLKGEN_CLK_EP_DIV_IN)
#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_CLK_EP_DIV_BMSK                                               0xff
#define HWIO_PCIE_CLKGEN_CLK_EP_DIV_CLK_EP_DIV_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000ac)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000ac)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_RMSK                                                       0x3f
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_ADDR, HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_IN)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_PLL_CPCTRL_MODE0_BMSK                                      0x3f
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_PLL_CPCTRL_MODE0_SHFT                                       0x0

#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000b0)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000b0)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_RMSK                                                       0x3f
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_ADDR, HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_IN)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_PLL_CPCTRL_MODE1_BMSK                                      0x3f
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE1_PLL_CPCTRL_MODE1_SHFT                                       0x0

#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000b4)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000b4)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_RMSK                                                       0x3f
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_ADDR, HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_IN)
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_PLL_CPCTRL_MODE2_BMSK                                      0x3f
#define HWIO_PCIE_CLKGEN_CP_CTRL_MODE2_PLL_CPCTRL_MODE2_SHFT                                       0x0

#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000b8)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000b8)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_RMSK                                                     0x1f
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_ADDR, HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_IN)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_PLL_RCTRL_MODE0_BMSK                                     0x1f
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_PLL_RCTRL_MODE0_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000bc)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000bc)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_RMSK                                                     0x1f
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_ADDR, HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_IN)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_PLL_RCTRL_MODE1_BMSK                                     0x1f
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE1_PLL_RCTRL_MODE1_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000c0)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000c0)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_RMSK                                                     0x1f
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_ADDR, HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_IN)
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_PLL_RCTRL_MODE2_BMSK                                     0x1f
#define HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE2_PLL_RCTRL_MODE2_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000c4)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000c4)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_RMSK                                                     0x3f
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_ADDR, HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_IN)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_PLL_CCTRL_MODE0_BMSK                                     0x3f
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_PLL_CCTRL_MODE0_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000c8)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000c8)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_RMSK                                                     0x3f
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_ADDR, HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_IN)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_PLL_CCTRL_MODE1_BMSK                                     0x3f
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE1_PLL_CCTRL_MODE1_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000cc)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000cc)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_RMSK                                                     0x3f
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_ADDR, HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_IN)
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_PLL_CCTRL_MODE2_BMSK                                     0x3f
#define HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE2_PLL_CCTRL_MODE2_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_PLL_CNTRL_ADDR                                                     (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000d0)
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_OFFS                                                     (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000d0)
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_RMSK                                                           0x7f
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_CNTRL_ADDR, HWIO_PCIE_CLKGEN_PLL_CNTRL_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_CNTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_CNTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_CNTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_CNTRL_IN)
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_PLL_STABLE_TIME_BMSK                                           0x60
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_PLL_STABLE_TIME_SHFT                                            0x5
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_MASH_RESET_MUX_BMSK                                            0x10
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_MASH_RESET_MUX_SHFT                                             0x4
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_MASH_RESET_BMSK                                                 0x8
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_MASH_RESET_SHFT                                                 0x3
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_PLL_CPLIN_BMSK                                                  0x4
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_PLL_CPLIN_SHFT                                                  0x2
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_PLL_DIV_FFEN_BMSK                                               0x2
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_PLL_DIV_FFEN_SHFT                                               0x1
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_PLL_DIV_ORD_BMSK                                                0x1
#define HWIO_PCIE_CLKGEN_PLL_CNTRL_PLL_DIV_ORD_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000d4)
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000d4)
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_RMSK                                                       0xff
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_ADDR, HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_RMSK)
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_ADDR, m)
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_ADDR,v)
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_ADDR,m,v,HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_IN)
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_CML_SYSCLK_SEL_BMSK                                        0xe0
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_CML_SYSCLK_SEL_SHFT                                         0x5
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_SYSCLK_TERM_SEL_BMSK                                       0x10
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_SYSCLK_TERM_SEL_SHFT                                        0x4
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_SYSCLK_SEL_BMSK                                             0xc
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_SYSCLK_SEL_SHFT                                             0x2
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_SYSCLK_EN_MUX_BMSK                                          0x2
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_SYSCLK_EN_MUX_SHFT                                          0x1
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_SYSCLK_EN_BMSK                                              0x1
#define HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_SYSCLK_EN_SHFT                                              0x0

#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_ADDR                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000d8)
#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_OFFS                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000d8)
#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_RMSK                                                       0x1
#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_ADDR, HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_RMSK)
#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_ADDR, m)
#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_ADDR,v)
#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_ADDR,m,v,HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_IN)
#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_CML_SYSCLK_SEL_MUX_BMSK                                    0x1
#define HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_CML_SYSCLK_SEL_MUX_SHFT                                    0x0

#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000dc)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000dc)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_RMSK                                                       0x7f
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR, HWIO_PCIE_CLKGEN_RESETSM_CNTRL_RMSK)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_RESETSM_CNTRL_IN)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_FORCE_C_READY_BMSK                                         0x40
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_FORCE_C_READY_SHFT                                          0x6
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_TSYNC_SEL_BMSK                                             0x20
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_TSYNC_SEL_SHFT                                              0x5
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_DISABLE_CLKGATE_BMSK                                       0x10
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_DISABLE_CLKGATE_SHFT                                        0x4
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_PLL_UNLOCK_DISABLE_BMSK                                     0x8
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_PLL_UNLOCK_DISABLE_SHFT                                     0x3
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_RSM_START_MUX_BMSK                                          0x4
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_RSM_START_MUX_SHFT                                          0x2
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_RSM_START_BMSK                                              0x2
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_RSM_START_SHFT                                              0x1
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_FORCE_PLLLOCK_BMSK                                          0x1
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL_FORCE_PLLLOCK_SHFT                                          0x0

#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_ADDR                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000e0)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_OFFS                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000e0)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_RMSK                                                      0x7f
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_ADDR, HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_RMSK)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_ADDR, m)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_ADDR,v)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_ADDR,m,v,HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_IN)
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_BYPASS_RSM_INTEGLOOP_CAL_BMSK                             0x40
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_BYPASS_RSM_INTEGLOOP_CAL_SHFT                              0x6
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_BYPASS_RSM_RESTRIM_BMSK                                   0x20
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_BYPASS_RSM_RESTRIM_SHFT                                    0x5
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_BYPASS_RSM_BANDGAP_BMSK                                   0x10
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_BYPASS_RSM_BANDGAP_SHFT                                    0x4
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_TSYNC_PULSE_WIDTH_BMSK                                     0xc
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_TSYNC_PULSE_WIDTH_SHFT                                     0x2
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_TSYNC_MUX_BMSK                                             0x2
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_TSYNC_MUX_SHFT                                             0x1
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_TSYNC_BMSK                                                 0x1
#define HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_TSYNC_SHFT                                                 0x0

#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000e4)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000e4)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_RMSK                                                        0xff
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESTRIM_CTRL_ADDR, HWIO_PCIE_CLKGEN_RESTRIM_CTRL_RMSK)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESTRIM_CTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_RESTRIM_CTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_RESTRIM_CTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_RESTRIM_CTRL_IN)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_RESTRIM_CMN_BYPASS_CODE_BMSK                                0xfe
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_RESTRIM_CMN_BYPASS_CODE_SHFT                                 0x1
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_BYPASS_CMN_RESTRIM_BMSK                                      0x1
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL_BYPASS_CMN_RESTRIM_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000e8)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000e8)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_RMSK                                                       0x7f
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_ADDR, HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_RMSK)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_ADDR, m)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_ADDR,v)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_ADDR,m,v,HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_IN)
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_RESTRIM_OFFSET_CODE_BMSK                                   0x7f
#define HWIO_PCIE_CLKGEN_RESTRIM_CTRL2_RESTRIM_OFFSET_CODE_SHFT                                    0x0

#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000ec)
#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000ec)
#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_RMSK                                                     0x7f
#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_ADDR, HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_RMSK)
#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_ADDR, m)
#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_ADDR,v)
#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_ADDR,m,v,HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_IN)
#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_RESCODE_DIV_NUMERATOR_BMSK                               0x7f
#define HWIO_PCIE_CLKGEN_RESCODE_DIV_NUM_RESCODE_DIV_NUMERATOR_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_ADDR                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000f0)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_OFFS                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000f0)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_RMSK                                                         0xff
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP_EN_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP_EN_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP_EN_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP_EN_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP_EN_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP_EN_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_RNG_2_BMSK                                           0x80
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_RNG_2_SHFT                                            0x7
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_CNT_2_BMSK                                           0x40
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_CNT_2_SHFT                                            0x6
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_EN_MUX_BMSK                                          0x20
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_EN_MUX_SHFT                                           0x5
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_EN_BMSK                                              0x10
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_EN_SHFT                                               0x4
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_RNG_BMSK                                              0xc
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_RNG_SHFT                                              0x2
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_CNT_BMSK                                              0x3
#define HWIO_PCIE_CLKGEN_LOCK_CMP_EN_PLLLOCK_CNT_SHFT                                              0x0

#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000f4)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000f4)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_RMSK                                                         0x3
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_ADDR, HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_RMSK)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_ADDR, m)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_ADDR,v)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_ADDR,m,v,HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_IN)
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_PLLLOCK_STOP_COUNT_BMSK                                      0x2
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_PLLLOCK_STOP_COUNT_SHFT                                      0x1
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_BYP_PLLLOCK_BMSK                                             0x1
#define HWIO_PCIE_CLKGEN_LOCK_CMP_CFG_BYP_PLLLOCK_SHFT                                             0x0

#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000f8)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000f8)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MODE0_ADDR, HWIO_PCIE_CLKGEN_DEC_START_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DEC_START_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DEC_START_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_DEC_START_MODE0_IN)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_DEC_START_MODE0_7_0_BMSK                                 0xff
#define HWIO_PCIE_CLKGEN_DEC_START_MODE0_DEC_START_MODE0_7_0_SHFT                                  0x0

#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_ADDR                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000000fc)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_OFFS                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000000fc)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_RMSK                                                  0x1
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_ADDR, HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_IN)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_DEC_START_MODE0_8_8_BMSK                              0x1
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE0_DEC_START_MODE0_8_8_SHFT                              0x0

#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000100)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000100)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MODE1_ADDR, HWIO_PCIE_CLKGEN_DEC_START_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DEC_START_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DEC_START_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_DEC_START_MODE1_IN)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_DEC_START_MODE1_7_0_BMSK                                 0xff
#define HWIO_PCIE_CLKGEN_DEC_START_MODE1_DEC_START_MODE1_7_0_SHFT                                  0x0

#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_ADDR                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000104)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_OFFS                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000104)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_RMSK                                                  0x1
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_ADDR, HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_IN)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_DEC_START_MODE1_8_8_BMSK                              0x1
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE1_DEC_START_MODE1_8_8_SHFT                              0x0

#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000108)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000108)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MODE2_ADDR, HWIO_PCIE_CLKGEN_DEC_START_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DEC_START_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DEC_START_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_DEC_START_MODE2_IN)
#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_DEC_START_MODE2_7_0_BMSK                                 0xff
#define HWIO_PCIE_CLKGEN_DEC_START_MODE2_DEC_START_MODE2_7_0_SHFT                                  0x0

#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_ADDR                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000010c)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_OFFS                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000010c)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_RMSK                                                  0x1
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_ADDR, HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_IN)
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_DEC_START_MODE2_8_8_BMSK                              0x1
#define HWIO_PCIE_CLKGEN_DEC_START_MSB_MODE2_DEC_START_MODE2_8_8_SHFT                              0x0

#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_ADDR                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000110)
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_OFFS                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000110)
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_RMSK                                                 0x1f
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_ADDR, HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_RMSK)
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_IN)
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_FBCLK_TOO_SLOW_CNTSEL_BMSK                           0x18
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_FBCLK_TOO_SLOW_CNTSEL_SHFT                            0x3
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_FORCE_CORRECT_POL_BMSK                                0x4
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_FORCE_CORRECT_POL_SHFT                                0x2
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_FBCLK_DEAD_CORRECT_EN_BMSK                            0x2
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_FBCLK_DEAD_CORRECT_EN_SHFT                            0x1
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_FBCLK_DEAD_TIME_BMSK                                  0x1
#define HWIO_PCIE_CLKGEN_VCOCAL_DEADMAN_CTRL_FBCLK_DEAD_TIME_SHFT                                  0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000114)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000114)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_DIV_FRAC_START_MODE0_7_0_BMSK                      0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_DIV_FRAC_START_MODE0_7_0_SHFT                       0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000118)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000118)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_DIV_FRAC_START_MODE0_15_8_BMSK                     0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_DIV_FRAC_START_MODE0_15_8_SHFT                      0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000011c)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000011c)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_RMSK                                                0xf
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_DIV_FRAC_START_MODE0_19_16_BMSK                     0xf
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_DIV_FRAC_START_MODE0_19_16_SHFT                     0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000120)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000120)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_DIV_FRAC_START_MODE1_7_0_BMSK                      0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE1_DIV_FRAC_START_MODE1_7_0_SHFT                       0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000124)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000124)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_DIV_FRAC_START_MODE1_15_8_BMSK                     0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE1_DIV_FRAC_START_MODE1_15_8_SHFT                      0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000128)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000128)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_RMSK                                                0xf
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_DIV_FRAC_START_MODE1_19_16_BMSK                     0xf
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE1_DIV_FRAC_START_MODE1_19_16_SHFT                     0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000012c)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000012c)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_DIV_FRAC_START_MODE2_7_0_BMSK                      0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE2_DIV_FRAC_START_MODE2_7_0_SHFT                       0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000130)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000130)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_DIV_FRAC_START_MODE2_15_8_BMSK                     0xff
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE2_DIV_FRAC_START_MODE2_15_8_SHFT                      0x0

#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000134)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000134)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_RMSK                                                0xf
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_ADDR, HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_IN)
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_DIV_FRAC_START_MODE2_19_16_BMSK                     0xf
#define HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE2_DIV_FRAC_START_MODE2_19_16_SHFT                     0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_ADDR                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000138)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_OFFS                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000138)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_RMSK                                                    0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_VCO_TUNE_MINVAL_7_0_BMSK                                0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL1_VCO_TUNE_MINVAL_7_0_SHFT                                 0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_ADDR                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000013c)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_OFFS                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000013c)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_RMSK                                                     0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_VCO_TUNE_MINVAL_9_8_BMSK                                 0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MINVAL2_VCO_TUNE_MINVAL_9_8_SHFT                                 0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_ADDR                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000140)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_OFFS                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000140)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_RMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_ADDR,v)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_ADDR,m,v,HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_IN)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_INTEGLOOP_INITVAL_BMSK                                 0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_INITVAL_INTEGLOOP_INITVAL_SHFT                                  0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000144)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000144)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_RMSK                                                         0x7
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_EN_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_EN_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_EN_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_INTEGLOOP_EN_ADDR,v)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_INTEGLOOP_EN_ADDR,m,v,HWIO_PCIE_CLKGEN_INTEGLOOP_EN_IN)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_INTEGLOOP_CODE_BYPASS_BMSK                                   0x4
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_INTEGLOOP_CODE_BYPASS_SHFT                                   0x2
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_INTEGLOOP_EN_MUX_BMSK                                        0x2
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_INTEGLOOP_EN_MUX_SHFT                                        0x1
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_INTEGLOOP_EN_BMSK                                            0x1
#define HWIO_PCIE_CLKGEN_INTEGLOOP_EN_INTEGLOOP_EN_SHFT                                            0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000148)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000148)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_IN)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_INTEGLOOP_GAIN_MODE0_7_0_BMSK                      0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_INTEGLOOP_GAIN_MODE0_7_0_SHFT                       0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000014c)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000014c)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_RMSK                                                0xf
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_IN)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_INTEGLOOP_GAIN_MODE0_11_8_BMSK                      0xf
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_INTEGLOOP_GAIN_MODE0_11_8_SHFT                      0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000150)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000150)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_IN)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_INTEGLOOP_GAIN_MODE1_7_0_BMSK                      0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE1_INTEGLOOP_GAIN_MODE1_7_0_SHFT                       0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000154)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000154)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_RMSK                                                0xf
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_IN)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_INTEGLOOP_GAIN_MODE1_11_8_BMSK                      0xf
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE1_INTEGLOOP_GAIN_MODE1_11_8_SHFT                      0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000158)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000158)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_RMSK                                               0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_IN)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_INTEGLOOP_GAIN_MODE2_7_0_BMSK                      0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE2_INTEGLOOP_GAIN_MODE2_7_0_SHFT                       0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_ADDR                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000015c)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_OFFS                                         (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000015c)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_RMSK                                                0xf
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_IN)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_INTEGLOOP_GAIN_MODE2_11_8_BMSK                      0xf
#define HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE2_INTEGLOOP_GAIN_MODE2_11_8_SHFT                      0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_ADDR                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000160)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_OFFS                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000160)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_RMSK                                                    0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_VCO_TUNE_MAXVAL_7_0_BMSK                                0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL1_VCO_TUNE_MAXVAL_7_0_SHFT                                 0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_ADDR                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000164)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_OFFS                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000164)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_RMSK                                                     0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_VCO_TUNE_MAXVAL_9_8_BMSK                                 0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAXVAL2_VCO_TUNE_MAXVAL_9_8_SHFT                                 0x0

#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_ADDR                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000168)
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_OFFS                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000168)
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_RMSK                                                    0x3
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_ADDR, HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_RMSK)
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_ADDR, m)
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_ADDR,v)
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_ADDR,m,v,HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_IN)
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_RESTRIM_EN_MUX_BMSK                                     0x2
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_RESTRIM_EN_MUX_SHFT                                     0x1
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_RESTRIM_EN_BMSK                                         0x1
#define HWIO_PCIE_CLKGEN_RES_TRIM_CONTROL2_RESTRIM_EN_SHFT                                         0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000016c)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000016c)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_RMSK                                                       0x3f
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_VCOCAL_POS_SLOPE_BMSK                                      0x20
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_VCOCAL_POS_SLOPE_SHFT                                       0x5
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_BYP_VCOCAL_MODE2_BMSK                                      0x10
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_BYP_VCOCAL_MODE2_SHFT                                       0x4
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_BYP_VCOCAL_MODE1_BMSK                                       0x8
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_BYP_VCOCAL_MODE1_SHFT                                       0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_BYP_VCOCAL_MODE0_BMSK                                       0x4
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_BYP_VCOCAL_MODE0_SHFT                                       0x2
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_VCO_TUNE_EN_MUX_BMSK                                        0x2
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_VCO_TUNE_EN_MUX_SHFT                                        0x1
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_VCO_TUNE_EN_BMSK                                            0x1
#define HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_VCO_TUNE_EN_SHFT                                            0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000170)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000170)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_RMSK                                                        0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_VCO_DEFAULT_FREQ_BMSK                                       0xc0
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_VCO_DEFAULT_FREQ_SHFT                                        0x6
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_MAP_LANE_PS0C_BMSK                                          0x30
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_MAP_LANE_PS0C_SHFT                                           0x4
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_MAP_LANE_PS0B_BMSK                                           0xc
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_MAP_LANE_PS0B_SHFT                                           0x2
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_MAP_LANE_PS0A_BMSK                                           0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_MAP_LANE_PS0A_SHFT                                           0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000174)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000174)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_PLL_VCOTUNE_MODE0_7_0_BMSK                               0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE0_PLL_VCOTUNE_MODE0_7_0_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000178)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000178)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_RMSK                                                      0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_PLL_VCOTUNE_MODE0_9_8_BMSK                                0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE0_PLL_VCOTUNE_MODE0_9_8_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000017c)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000017c)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_PLL_VCOTUNE_MODE1_7_0_BMSK                               0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE1_PLL_VCOTUNE_MODE1_7_0_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000180)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000180)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_RMSK                                                      0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_PLL_VCOTUNE_MODE1_9_8_BMSK                                0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE1_PLL_VCOTUNE_MODE1_9_8_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000184)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000184)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_PLL_VCOTUNE_MODE2_7_0_BMSK                               0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE1_MODE2_PLL_VCOTUNE_MODE2_7_0_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000188)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000188)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_RMSK                                                      0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_PLL_VCOTUNE_MODE2_9_8_BMSK                                0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE2_MODE2_PLL_VCOTUNE_MODE2_9_8_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_ADDR                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000018c)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_OFFS                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000018c)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_RMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_VCO_TUNE_INITVAL_7_0_BMSK                              0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL1_VCO_TUNE_INITVAL_7_0_SHFT                               0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_ADDR                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000190)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_OFFS                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000190)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_RMSK                                                    0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_VCO_TUNE_INITVAL_9_8_BMSK                               0x3
#define HWIO_PCIE_CLKGEN_VCO_TUNE_INITVAL2_VCO_TUNE_INITVAL_9_8_SHFT                               0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000194)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000194)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_PLL_VCOTUNE_TIMER_7_0_BMSK                               0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER1_PLL_VCOTUNE_TIMER_7_0_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000198)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000198)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_ADDR, HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_ADDR,v)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_ADDR,m,v,HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_IN)
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_PLL_VCOTUNE_TIMER_15_8_BMSK                              0xff
#define HWIO_PCIE_CLKGEN_VCO_TUNE_TIMER2_PLL_VCOTUNE_TIMER_15_8_SHFT                               0x0

#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000019c)
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000019c)
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_RMSK                                                     0x1f
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADDR, HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_RMSK)
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_IN)
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_FREEZE_CODE_BMSK                                         0x10
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_FREEZE_CODE_SHFT                                          0x4
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADC_FROM_ATB_BMSK                                         0x8
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADC_FROM_ATB_SHFT                                         0x3
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADC_ATB_MUXSEL_BMSK                                       0x4
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADC_ATB_MUXSEL_SHFT                                       0x2
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADC_SIGN_POL_FLIP_BMSK                                    0x2
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADC_SIGN_POL_FLIP_SHFT                                    0x1
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADC_EN_BMSK                                               0x1
#define HWIO_PCIE_CLKGEN_ADC_FILTER_CTRL_ADC_EN_SHFT                                               0x0

#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_ADDR                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001a0)
#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_OFFS                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001a0)
#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_RMSK                                                         0x1f
#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_ADC_CLK_DIV_ADDR, HWIO_PCIE_CLKGEN_ADC_CLK_DIV_RMSK)
#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_ADC_CLK_DIV_ADDR, m)
#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_ADC_CLK_DIV_ADDR,v)
#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_ADC_CLK_DIV_ADDR,m,v,HWIO_PCIE_CLKGEN_ADC_CLK_DIV_IN)
#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_ADC_CLK_DIV_BMSK                                             0x1f
#define HWIO_PCIE_CLKGEN_ADC_CLK_DIV_ADC_CLK_DIV_SHFT                                              0x0

#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001a4)
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001a4)
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_RMSK                                                0xff
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_ADDR, HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_ADC_CODE_OUT_7_0_BMSK                               0xff
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT1_STATUS_ADC_CODE_OUT_7_0_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_ADDR                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001a8)
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_OFFS                                          (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001a8)
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_RMSK                                                 0x3
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_ADDR, HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_ADC_CODE_OUT_9_8_BMSK                                0x3
#define HWIO_PCIE_CLKGEN_ADC_CODE_OUT2_STATUS_ADC_CODE_OUT_9_8_SHFT                                0x0

#define HWIO_PCIE_CLKGEN_CMN_STATUS_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001ac)
#define HWIO_PCIE_CLKGEN_CMN_STATUS_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001ac)
#define HWIO_PCIE_CLKGEN_CMN_STATUS_RMSK                                                          0x7f
#define HWIO_PCIE_CLKGEN_CMN_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_STATUS_ADDR, HWIO_PCIE_CLKGEN_CMN_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_CMN_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_CMN_STATUS_FREEZEIO_D_BMSK                                               0x40
#define HWIO_PCIE_CLKGEN_CMN_STATUS_FREEZEIO_D_SHFT                                                0x6
#define HWIO_PCIE_CLKGEN_CMN_STATUS_SWITCH_TO_REFCLK_DONE_BMSK                                    0x20
#define HWIO_PCIE_CLKGEN_CMN_STATUS_SWITCH_TO_REFCLK_DONE_SHFT                                     0x5
#define HWIO_PCIE_CLKGEN_CMN_STATUS_SWITCH_TO_CORECLK_DONE_BMSK                                   0x10
#define HWIO_PCIE_CLKGEN_CMN_STATUS_SWITCH_TO_CORECLK_DONE_SHFT                                    0x4
#define HWIO_PCIE_CLKGEN_CMN_STATUS_SWITCH_TO_AUXCLK_DONE_BMSK                                     0x8
#define HWIO_PCIE_CLKGEN_CMN_STATUS_SWITCH_TO_AUXCLK_DONE_SHFT                                     0x3
#define HWIO_PCIE_CLKGEN_CMN_STATUS_PLL_UNLOCKED_BMSK                                              0x4
#define HWIO_PCIE_CLKGEN_CMN_STATUS_PLL_UNLOCKED_SHFT                                              0x2
#define HWIO_PCIE_CLKGEN_CMN_STATUS_PLL_LOCKED_BMSK                                                0x2
#define HWIO_PCIE_CLKGEN_CMN_STATUS_PLL_LOCKED_SHFT                                                0x1
#define HWIO_PCIE_CLKGEN_CMN_STATUS_PLL_FREQ_DONE_BMSK                                             0x1
#define HWIO_PCIE_CLKGEN_CMN_STATUS_PLL_FREQ_DONE_SHFT                                             0x0

#define HWIO_PCIE_CLKGEN_RESET_SM_STATUS_ADDR                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001b0)
#define HWIO_PCIE_CLKGEN_RESET_SM_STATUS_OFFS                                               (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001b0)
#define HWIO_PCIE_CLKGEN_RESET_SM_STATUS_RMSK                                                     0xff
#define HWIO_PCIE_CLKGEN_RESET_SM_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESET_SM_STATUS_ADDR, HWIO_PCIE_CLKGEN_RESET_SM_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_RESET_SM_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESET_SM_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_RESET_SM_STATUS_RESETSM_BMSK                                             0xff
#define HWIO_PCIE_CLKGEN_RESET_SM_STATUS_RESETSM_SHFT                                              0x0

#define HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_ADDR                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001b4)
#define HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_OFFS                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001b4)
#define HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_RMSK                                                 0x7f
#define HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_ADDR, HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_RESTRIM_CODE_BMSK                                    0x7f
#define HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_RESTRIM_CODE_SHFT                                     0x0

#define HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_ADDR                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001b8)
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_OFFS                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001b8)
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_RMSK                                                 0xff
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_ADDR, HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_VCO_CTUNE_BINCODE_7_0_BMSK                           0xff
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE1_STATUS_VCO_CTUNE_BINCODE_7_0_SHFT                            0x0

#define HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_ADDR                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001bc)
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_OFFS                                           (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001bc)
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_RMSK                                                  0x3
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_ADDR, HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_VCO_CTUNE_BINCODE_9_8_BMSK                            0x3
#define HWIO_PCIE_CLKGEN_PLLCAL_CODE2_STATUS_VCO_CTUNE_BINCODE_9_8_SHFT                            0x0

#define HWIO_PCIE_CLKGEN_BG_CTRL_ADDR                                                       (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001c0)
#define HWIO_PCIE_CLKGEN_BG_CTRL_OFFS                                                       (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001c0)
#define HWIO_PCIE_CLKGEN_BG_CTRL_RMSK                                                              0x7
#define HWIO_PCIE_CLKGEN_BG_CTRL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_BG_CTRL_ADDR, HWIO_PCIE_CLKGEN_BG_CTRL_RMSK)
#define HWIO_PCIE_CLKGEN_BG_CTRL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_BG_CTRL_ADDR, m)
#define HWIO_PCIE_CLKGEN_BG_CTRL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_BG_CTRL_ADDR,v)
#define HWIO_PCIE_CLKGEN_BG_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_BG_CTRL_ADDR,m,v,HWIO_PCIE_CLKGEN_BG_CTRL_IN)
#define HWIO_PCIE_CLKGEN_BG_CTRL_BANDGAP_EN_MUX_BMSK                                               0x4
#define HWIO_PCIE_CLKGEN_BG_CTRL_BANDGAP_EN_MUX_SHFT                                               0x2
#define HWIO_PCIE_CLKGEN_BG_CTRL_BANDGAP_EN_BMSK                                                   0x2
#define HWIO_PCIE_CLKGEN_BG_CTRL_BANDGAP_EN_SHFT                                                   0x1
#define HWIO_PCIE_CLKGEN_BG_CTRL_BANDGAP_BYPASS_BMSK                                               0x1
#define HWIO_PCIE_CLKGEN_BG_CTRL_BANDGAP_BYPASS_SHFT                                               0x0

#define HWIO_PCIE_CLKGEN_CLK_SELECT_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001c4)
#define HWIO_PCIE_CLKGEN_CLK_SELECT_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001c4)
#define HWIO_PCIE_CLKGEN_CLK_SELECT_RMSK                                                          0x7f
#define HWIO_PCIE_CLKGEN_CLK_SELECT_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_SELECT_ADDR, HWIO_PCIE_CLKGEN_CLK_SELECT_RMSK)
#define HWIO_PCIE_CLKGEN_CLK_SELECT_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CLK_SELECT_ADDR, m)
#define HWIO_PCIE_CLKGEN_CLK_SELECT_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CLK_SELECT_ADDR,v)
#define HWIO_PCIE_CLKGEN_CLK_SELECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CLK_SELECT_ADDR,m,v,HWIO_PCIE_CLKGEN_CLK_SELECT_IN)
#define HWIO_PCIE_CLKGEN_CLK_SELECT_VREG_CLK_SRC_SEL_BMSK                                         0x40
#define HWIO_PCIE_CLKGEN_CLK_SELECT_VREG_CLK_SRC_SEL_SHFT                                          0x6
#define HWIO_PCIE_CLKGEN_CLK_SELECT_TSYNC_EN_MUX_BMSK                                             0x20
#define HWIO_PCIE_CLKGEN_CLK_SELECT_TSYNC_EN_MUX_SHFT                                              0x5
#define HWIO_PCIE_CLKGEN_CLK_SELECT_TSYNC_EN_BMSK                                                 0x10
#define HWIO_PCIE_CLKGEN_CLK_SELECT_TSYNC_EN_SHFT                                                  0x4
#define HWIO_PCIE_CLKGEN_CLK_SELECT_SYSCLK_CMOS_PAD_SEL_BMSK                                       0x8
#define HWIO_PCIE_CLKGEN_CLK_SELECT_SYSCLK_CMOS_PAD_SEL_SHFT                                       0x3
#define HWIO_PCIE_CLKGEN_CLK_SELECT_SYSCLK_TX_SWINGSEL_BMSK                                        0x6
#define HWIO_PCIE_CLKGEN_CLK_SELECT_SYSCLK_TX_SWINGSEL_SHFT                                        0x1
#define HWIO_PCIE_CLKGEN_CLK_SELECT_SYSCLK_TX_SYSCLKSEL_BMSK                                       0x1
#define HWIO_PCIE_CLKGEN_CLK_SELECT_SYSCLK_TX_SYSCLKSEL_SHFT                                       0x0

#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001c8)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001c8)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_RMSK                                                          0xff
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_HSCLK_SEL1_ADDR, HWIO_PCIE_CLKGEN_HSCLK_SEL1_RMSK)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_HSCLK_SEL1_ADDR, m)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_HSCLK_SEL1_ADDR,v)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_HSCLK_SEL1_ADDR,m,v,HWIO_PCIE_CLKGEN_HSCLK_SEL1_IN)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_HSCLK_DIVSEL_MODE1_BMSK                                       0xf0
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_HSCLK_DIVSEL_MODE1_SHFT                                        0x4
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_HSCLK_DIVSEL_MODE0_BMSK                                        0xf
#define HWIO_PCIE_CLKGEN_HSCLK_SEL1_HSCLK_DIVSEL_MODE0_SHFT                                        0x0

#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001cc)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001cc)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_RMSK                                                           0xf
#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_HSCLK_SEL2_ADDR, HWIO_PCIE_CLKGEN_HSCLK_SEL2_RMSK)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_HSCLK_SEL2_ADDR, m)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_HSCLK_SEL2_ADDR,v)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_HSCLK_SEL2_ADDR,m,v,HWIO_PCIE_CLKGEN_HSCLK_SEL2_IN)
#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_HSCLK_DIVSEL_MODE2_BMSK                                        0xf
#define HWIO_PCIE_CLKGEN_HSCLK_SEL2_HSCLK_DIVSEL_MODE2_SHFT                                        0x0

#define HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_ADDR                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001d0)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_OFFS                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001d0)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_RMSK                                            0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_ADDR, HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_INTEGLOOP_BINCODE_BMSK                          0xff
#define HWIO_PCIE_CLKGEN_INTEGLOOP_BINCODE_STATUS_INTEGLOOP_BINCODE_SHFT                           0x0

#define HWIO_PCIE_CLKGEN_PLL_ANALOG_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001d4)
#define HWIO_PCIE_CLKGEN_PLL_ANALOG_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001d4)
#define HWIO_PCIE_CLKGEN_PLL_ANALOG_RMSK                                                           0x1
#define HWIO_PCIE_CLKGEN_PLL_ANALOG_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_ANALOG_ADDR, HWIO_PCIE_CLKGEN_PLL_ANALOG_RMSK)
#define HWIO_PCIE_CLKGEN_PLL_ANALOG_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_PLL_ANALOG_ADDR, m)
#define HWIO_PCIE_CLKGEN_PLL_ANALOG_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_PLL_ANALOG_ADDR,v)
#define HWIO_PCIE_CLKGEN_PLL_ANALOG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_PLL_ANALOG_ADDR,m,v,HWIO_PCIE_CLKGEN_PLL_ANALOG_IN)
#define HWIO_PCIE_CLKGEN_PLL_ANALOG_PLL_ANALOG_BMSK                                                0x1
#define HWIO_PCIE_CLKGEN_PLL_ANALOG_PLL_ANALOG_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_CORECLK_DIV_ADDR                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001d8)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_OFFS                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001d8)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_RMSK                                                         0xff
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CORECLK_DIV_ADDR, HWIO_PCIE_CLKGEN_CORECLK_DIV_RMSK)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CORECLK_DIV_ADDR, m)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CORECLK_DIV_ADDR,v)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CORECLK_DIV_ADDR,m,v,HWIO_PCIE_CLKGEN_CORECLK_DIV_IN)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_CORE_CLK_DIV_BMSK                                            0xff
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_CORE_CLK_DIV_SHFT                                             0x0

#define HWIO_PCIE_CLKGEN_SW_RESET_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001dc)
#define HWIO_PCIE_CLKGEN_SW_RESET_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001dc)
#define HWIO_PCIE_CLKGEN_SW_RESET_RMSK                                                             0x1
#define HWIO_PCIE_CLKGEN_SW_RESET_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SW_RESET_ADDR, HWIO_PCIE_CLKGEN_SW_RESET_RMSK)
#define HWIO_PCIE_CLKGEN_SW_RESET_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SW_RESET_ADDR, m)
#define HWIO_PCIE_CLKGEN_SW_RESET_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SW_RESET_ADDR,v)
#define HWIO_PCIE_CLKGEN_SW_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SW_RESET_ADDR,m,v,HWIO_PCIE_CLKGEN_SW_RESET_IN)
#define HWIO_PCIE_CLKGEN_SW_RESET_SW_RESET_BMSK                                                    0x1
#define HWIO_PCIE_CLKGEN_SW_RESET_SW_RESET_SHFT                                                    0x0

#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001e0)
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_OFFS                                                   (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001e0)
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_RMSK                                                         0x7f
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR, HWIO_PCIE_CLKGEN_CORE_CLK_EN_RMSK)
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR, m)
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR,v)
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR,m,v,HWIO_PCIE_CLKGEN_CORE_CLK_EN_IN)
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE2_BMSK                                   0x40
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE2_SHFT                                    0x6
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE1_BMSK                                   0x20
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE1_SHFT                                    0x5
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE0_BMSK                                   0x10
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE0_SHFT                                    0x4
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CORECLK_EN_MUX_BMSK                                           0x8
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CORECLK_EN_MUX_SHFT                                           0x3
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CORECLK_EN_BMSK                                               0x4
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_CORECLK_EN_SHFT                                               0x2
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_AUXCLK_EN_MUX_BMSK                                            0x2
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_AUXCLK_EN_MUX_SHFT                                            0x1
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_AUXCLK_EN_BMSK                                                0x1
#define HWIO_PCIE_CLKGEN_CORE_CLK_EN_AUXCLK_EN_SHFT                                                0x0

#define HWIO_PCIE_CLKGEN_C_READY_STATUS_ADDR                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001e4)
#define HWIO_PCIE_CLKGEN_C_READY_STATUS_OFFS                                                (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001e4)
#define HWIO_PCIE_CLKGEN_C_READY_STATUS_RMSK                                                       0x1
#define HWIO_PCIE_CLKGEN_C_READY_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_C_READY_STATUS_ADDR, HWIO_PCIE_CLKGEN_C_READY_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_C_READY_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_C_READY_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_C_READY_STATUS_C_READY_BMSK                                               0x1
#define HWIO_PCIE_CLKGEN_C_READY_STATUS_C_READY_SHFT                                               0x0

#define HWIO_PCIE_CLKGEN_CMN_CONFIG_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001e8)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001e8)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_RMSK                                                          0x1f
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_CONFIG_ADDR, HWIO_PCIE_CLKGEN_CMN_CONFIG_RMSK)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_CONFIG_ADDR, m)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CMN_CONFIG_ADDR,v)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CMN_CONFIG_ADDR,m,v,HWIO_PCIE_CLKGEN_CMN_CONFIG_IN)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_LANE_SYNC_MODE_BMSK                                           0x10
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_LANE_SYNC_MODE_SHFT                                            0x4
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_PSM_SWITCH_CORECLK_BMSK                                        0x8
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_PSM_SWITCH_CORECLK_SHFT                                        0x3
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_PSM_SWITCH_AUXCLK_BMSK                                         0x4
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_PSM_SWITCH_AUXCLK_SHFT                                         0x2
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_CLKGEN_MODE_BMSK                                               0x3
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_CLKGEN_MODE_SHFT                                               0x0

#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001ec)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001ec)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_RMSK                                                        0x1f
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_CONFIG_2_ADDR, HWIO_PCIE_CLKGEN_CMN_CONFIG_2_RMSK)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_CONFIG_2_ADDR, m)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CMN_CONFIG_2_ADDR,v)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CMN_CONFIG_2_ADDR,m,v,HWIO_PCIE_CLKGEN_CMN_CONFIG_2_IN)
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_CMN_VREG_SEL_BMSK                                           0x1c
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_CMN_VREG_SEL_SHFT                                            0x2
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_PLL_FBCLK_SEL_BMSK                                           0x2
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_PLL_FBCLK_SEL_SHFT                                           0x1
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_CLK_BIAS_REFSEL_BMSK                                         0x1
#define HWIO_PCIE_CLKGEN_CMN_CONFIG_2_CLK_BIAS_REFSEL_SHFT                                         0x0

#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_ADDR                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001f0)
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_OFFS                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001f0)
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_RMSK                                                    0xf
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_ADDR, HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_RMSK)
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_ADDR, m)
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_ADDR,v)
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_ADDR,m,v,HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_IN)
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_CMN_RATE_SW_UPDATE_BMSK                                 0x8
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_CMN_RATE_SW_UPDATE_SHFT                                 0x3
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_CMN_RATE_SW_SEL_BMSK                                    0x4
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_CMN_RATE_SW_SEL_SHFT                                    0x2
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_CMN_RATE_CODE_BMSK                                      0x3
#define HWIO_PCIE_CLKGEN_CMN_RATE_OVERRIDE_CMN_RATE_CODE_SHFT                                      0x0

#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_ADDR                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001f4)
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_OFFS                                              (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001f4)
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_RMSK                                                    0x3f
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_ADDR, HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_RMSK)
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_ADDR, m)
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_ADDR,v)
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_ADDR,m,v,HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_IN)
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE2_BMSK                            0x30
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE2_SHFT                             0x4
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE1_BMSK                             0xc
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE1_SHFT                             0x2
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE0_BMSK                             0x3
#define HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE0_SHFT                             0x0

#define HWIO_PCIE_CLKGEN_DEBUG_BUS0_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001f8)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS0_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001f8)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS0_RMSK                                                          0xff
#define HWIO_PCIE_CLKGEN_DEBUG_BUS0_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS0_ADDR, HWIO_PCIE_CLKGEN_DEBUG_BUS0_RMSK)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS0_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS0_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                            0xff
#define HWIO_PCIE_CLKGEN_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                             0x0

#define HWIO_PCIE_CLKGEN_DEBUG_BUS1_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x000001fc)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS1_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x000001fc)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS1_RMSK                                                          0xff
#define HWIO_PCIE_CLKGEN_DEBUG_BUS1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS1_ADDR, HWIO_PCIE_CLKGEN_DEBUG_BUS1_RMSK)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS1_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                           0xff
#define HWIO_PCIE_CLKGEN_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                            0x0

#define HWIO_PCIE_CLKGEN_DEBUG_BUS2_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000200)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS2_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000200)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS2_RMSK                                                          0xff
#define HWIO_PCIE_CLKGEN_DEBUG_BUS2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS2_ADDR, HWIO_PCIE_CLKGEN_DEBUG_BUS2_RMSK)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS2_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS2_DEBUG_BUS_23_16_BMSK                                          0xff
#define HWIO_PCIE_CLKGEN_DEBUG_BUS2_DEBUG_BUS_23_16_SHFT                                           0x0

#define HWIO_PCIE_CLKGEN_DEBUG_BUS3_ADDR                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000204)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS3_OFFS                                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000204)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS3_RMSK                                                          0xff
#define HWIO_PCIE_CLKGEN_DEBUG_BUS3_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS3_ADDR, HWIO_PCIE_CLKGEN_DEBUG_BUS3_RMSK)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS3_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS3_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS3_DEBUG_BUS_31_24_BMSK                                          0xff
#define HWIO_PCIE_CLKGEN_DEBUG_BUS3_DEBUG_BUS_31_24_SHFT                                           0x0

#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_ADDR                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000208)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_OFFS                                                 (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000208)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_RMSK                                                        0xf
#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_ADDR, HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_RMSK)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_ADDR, m)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_ADDR,v)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_ADDR,m,v,HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_IN)
#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                          0xf
#define HWIO_PCIE_CLKGEN_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                          0x0

#define HWIO_PCIE_CLKGEN_CMN_MISC1_ADDR                                                     (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000020c)
#define HWIO_PCIE_CLKGEN_CMN_MISC1_OFFS                                                     (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000020c)
#define HWIO_PCIE_CLKGEN_CMN_MISC1_RMSK                                                           0x7f
#define HWIO_PCIE_CLKGEN_CMN_MISC1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_MISC1_ADDR, HWIO_PCIE_CLKGEN_CMN_MISC1_RMSK)
#define HWIO_PCIE_CLKGEN_CMN_MISC1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_MISC1_ADDR, m)
#define HWIO_PCIE_CLKGEN_CMN_MISC1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CMN_MISC1_ADDR,v)
#define HWIO_PCIE_CLKGEN_CMN_MISC1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CMN_MISC1_ADDR,m,v,HWIO_PCIE_CLKGEN_CMN_MISC1_IN)
#define HWIO_PCIE_CLKGEN_CMN_MISC1_DIS_CG_RATE_CHANGE_BMSK                                        0x40
#define HWIO_PCIE_CLKGEN_CMN_MISC1_DIS_CG_RATE_CHANGE_SHFT                                         0x6
#define HWIO_PCIE_CLKGEN_CMN_MISC1_DIS_CG_SYSGLITCH_BMSK                                          0x20
#define HWIO_PCIE_CLKGEN_CMN_MISC1_DIS_CG_SYSGLITCH_SHFT                                           0x5
#define HWIO_PCIE_CLKGEN_CMN_MISC1_PLL_RESET_MUX_BMSK                                             0x10
#define HWIO_PCIE_CLKGEN_CMN_MISC1_PLL_RESET_MUX_SHFT                                              0x4
#define HWIO_PCIE_CLKGEN_CMN_MISC1_PLL_RESET_BMSK                                                  0x8
#define HWIO_PCIE_CLKGEN_CMN_MISC1_PLL_RESET_SHFT                                                  0x3
#define HWIO_PCIE_CLKGEN_CMN_MISC1_PLL_VREG_READY_MUX_BMSK                                         0x4
#define HWIO_PCIE_CLKGEN_CMN_MISC1_PLL_VREG_READY_MUX_SHFT                                         0x2
#define HWIO_PCIE_CLKGEN_CMN_MISC1_PLL_VREG_READY_BMSK                                             0x2
#define HWIO_PCIE_CLKGEN_CMN_MISC1_PLL_VREG_READY_SHFT                                             0x1
#define HWIO_PCIE_CLKGEN_CMN_MISC1_DISABLE_B2T_INTEGLOOP_CLKGATE_BMSK                              0x1
#define HWIO_PCIE_CLKGEN_CMN_MISC1_DISABLE_B2T_INTEGLOOP_CLKGATE_SHFT                              0x0

#define HWIO_PCIE_CLKGEN_CMN_MISC2_ADDR                                                     (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000210)
#define HWIO_PCIE_CLKGEN_CMN_MISC2_OFFS                                                     (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000210)
#define HWIO_PCIE_CLKGEN_CMN_MISC2_RMSK                                                           0xff
#define HWIO_PCIE_CLKGEN_CMN_MISC2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_MISC2_ADDR, HWIO_PCIE_CLKGEN_CMN_MISC2_RMSK)
#define HWIO_PCIE_CLKGEN_CMN_MISC2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_MISC2_ADDR, m)
#define HWIO_PCIE_CLKGEN_CMN_MISC2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CMN_MISC2_ADDR,v)
#define HWIO_PCIE_CLKGEN_CMN_MISC2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CMN_MISC2_ADDR,m,v,HWIO_PCIE_CLKGEN_CMN_MISC2_IN)
#define HWIO_PCIE_CLKGEN_CMN_MISC2_RSVD_BMSK                                                      0x80
#define HWIO_PCIE_CLKGEN_CMN_MISC2_RSVD_SHFT                                                       0x7
#define HWIO_PCIE_CLKGEN_CMN_MISC2_RESCODE_MAX_CAP_BMSK                                           0x7f
#define HWIO_PCIE_CLKGEN_CMN_MISC2_RESCODE_MAX_CAP_SHFT                                            0x0

#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_ADDR                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000214)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_OFFS                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000214)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_RMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_ADDR, HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_RMSK)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_ADDR, m)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_ADDR,v)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_ADDR,m,v,HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_IN)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_CORE_CLK_DIV_MODE1_BMSK                                0xff
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE1_CORE_CLK_DIV_MODE1_SHFT                                 0x0

#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_ADDR                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000218)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_OFFS                                             (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000218)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_RMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_ADDR, HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_RMSK)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_ADDR, m)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_ADDR,v)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_ADDR,m,v,HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_IN)
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_CORE_CLK_DIV_MODE2_BMSK                                0xff
#define HWIO_PCIE_CLKGEN_CORECLK_DIV_MODE2_CORE_CLK_DIV_MODE2_SHFT                                 0x0

#define HWIO_PCIE_CLKGEN_CMN_MODE_ADDR                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000021c)
#define HWIO_PCIE_CLKGEN_CMN_MODE_OFFS                                                      (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000021c)
#define HWIO_PCIE_CLKGEN_CMN_MODE_RMSK                                                            0xff
#define HWIO_PCIE_CLKGEN_CMN_MODE_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_MODE_ADDR, HWIO_PCIE_CLKGEN_CMN_MODE_RMSK)
#define HWIO_PCIE_CLKGEN_CMN_MODE_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_CMN_MODE_ADDR, m)
#define HWIO_PCIE_CLKGEN_CMN_MODE_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_CMN_MODE_ADDR,v)
#define HWIO_PCIE_CLKGEN_CMN_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_CMN_MODE_ADDR,m,v,HWIO_PCIE_CLKGEN_CMN_MODE_IN)
#define HWIO_PCIE_CLKGEN_CMN_MODE_CMN_MODE_BMSK                                                   0xff
#define HWIO_PCIE_CLKGEN_CMN_MODE_CMN_MODE_SHFT                                                    0x0

#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000220)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000220)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_RMSK                                                        0x3f
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VREGCLK_DIV1_ADDR, HWIO_PCIE_CLKGEN_VREGCLK_DIV1_RMSK)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VREGCLK_DIV1_ADDR, m)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VREGCLK_DIV1_ADDR,v)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VREGCLK_DIV1_ADDR,m,v,HWIO_PCIE_CLKGEN_VREGCLK_DIV1_IN)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_VREGCLK_DIV_MODE1_BMSK                                      0x38
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_VREGCLK_DIV_MODE1_SHFT                                       0x3
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_VREGCLK_DIV_MODE0_BMSK                                       0x7
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV1_VREGCLK_DIV_MODE0_SHFT                                       0x0

#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_ADDR                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000224)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_OFFS                                                  (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000224)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_RMSK                                                         0x7
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VREGCLK_DIV2_ADDR, HWIO_PCIE_CLKGEN_VREGCLK_DIV2_RMSK)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VREGCLK_DIV2_ADDR, m)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_OUT(v)      \
        out_dword(HWIO_PCIE_CLKGEN_VREGCLK_DIV2_ADDR,v)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PCIE_CLKGEN_VREGCLK_DIV2_ADDR,m,v,HWIO_PCIE_CLKGEN_VREGCLK_DIV2_IN)
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_VREGCLK_DIV_MODE2_BMSK                                       0x7
#define HWIO_PCIE_CLKGEN_VREGCLK_DIV2_VREGCLK_DIV_MODE2_SHFT                                       0x0

#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_ADDR                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000228)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_OFFS                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000228)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_RMSK                                          0xff
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_ADDR, HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_PSM_VCOCAL_CODE_MODE0_7_0_BMSK                0xff
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE0_STATUS_PSM_VCOCAL_CODE_MODE0_7_0_SHFT                 0x0

#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_ADDR                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000022c)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_OFFS                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000022c)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_RMSK                                           0x3
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_ADDR, HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_PSM_VCOCAL_CODE_MODE0_9_8_BMSK                 0x3
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE0_STATUS_PSM_VCOCAL_CODE_MODE0_9_8_SHFT                 0x0

#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_ADDR                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000230)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_OFFS                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000230)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_RMSK                                          0xff
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_ADDR, HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_PSM_VCOCAL_CODE_MODE1_7_0_BMSK                0xff
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE1_STATUS_PSM_VCOCAL_CODE_MODE1_7_0_SHFT                 0x0

#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_ADDR                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000234)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_OFFS                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000234)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_RMSK                                           0x3
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_ADDR, HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_PSM_VCOCAL_CODE_MODE1_9_8_BMSK                 0x3
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE1_STATUS_PSM_VCOCAL_CODE_MODE1_9_8_SHFT                 0x0

#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_ADDR                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x00000238)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_OFFS                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x00000238)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_RMSK                                          0xff
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_ADDR, HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_PSM_VCOCAL_CODE_MODE2_7_0_BMSK                0xff
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE1_MODE2_STATUS_PSM_VCOCAL_CODE_MODE2_7_0_SHFT                 0x0

#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_ADDR                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE      + 0x0000023c)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_OFFS                                    (PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_REG_BASE_OFFS + 0x0000023c)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_RMSK                                           0x3
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_IN          \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_ADDR, HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_RMSK)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_INM(m)      \
        in_dword_masked(HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_ADDR, m)
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_PSM_VCOCAL_CODE_MODE2_9_8_BMSK                 0x3
#define HWIO_PCIE_CLKGEN_VCO_CAL_CODE2_MODE2_STATUS_PSM_VCOCAL_CODE_MODE2_9_8_SHFT                 0x0


#endif /* __PCIECLKGENQDF2400HWIO_H__ */
