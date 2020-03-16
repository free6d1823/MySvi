#ifndef __TCSR_SPARE_HWIO_H__
#define __TCSR_SPARE_HWIO_H__
/*
===========================================================================
*/
/**
  @file tcsr_spare_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r63.0]

  This file contains HWIO register definitions for the following modules:
    TCSR_REGS

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
 * MODULE: TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_REGS_REG_BASE                                                (CORE_TOP_CSR_BASE      + 0x00010000)
#define TCSR_REGS_REG_BASE_OFFS                                           0x00010000

#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_ADDR                            (TCSR_REGS_REG_BASE      + 0x00000000)
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_OFFS                            (TCSR_REGS_REG_BASE_OFFS + 0x00000000)
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_RMSK                            0xfffffdff
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_IN          \
        in_dword_masked(HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_ADDR, HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_RMSK)
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_ADDR, m)
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_EC_XPU2_BMSK                    0x80000000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_EC_XPU2_SHFT                          0x1f
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_IMEM_BMSK                       0x40000000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_IMEM_SHFT                             0x1e
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_QDSS_BMSK                       0x20000000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_QDSS_SHFT                             0x1d
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MPM_BMSK                        0x10000000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MPM_SHFT                              0x1c
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MESSAGE_RAM_BMSK                 0x8000000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MESSAGE_RAM_SHFT                      0x1b
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PMIC_ARB_2_BMSK                  0x4000000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PMIC_ARB_2_SHFT                       0x1a
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PMIC_ARB_1_BMSK                  0x2000000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PMIC_ARB_1_SHFT                       0x19
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PMIC_ARB_0_BMSK                  0x1000000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PMIC_ARB_0_SHFT                       0x18
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_FAN_TACH_BMSK                     0x800000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_FAN_TACH_SHFT                         0x17
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_SECURITY_CONTROL_BMSK             0x400000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_SECURITY_CONTROL_SHFT                 0x16
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_TLMM_BMSK                         0x200000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_TLMM_SHFT                             0x15
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_CORE_TOP_CSR_BMSK                 0x100000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_CORE_TOP_CSR_SHFT                     0x14
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_GCCMW_BMSK                         0x80000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_GCCMW_SHFT                            0x13
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_GCCE_BMSK                          0x40000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_GCCE_SHFT                             0x12
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_GCC_MS_S_BMSK                      0x20000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_GCC_MS_S_SHFT                         0x11
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_GCC_MS_N_BMSK                      0x10000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_GCC_MS_N_SHFT                         0x10
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_EMAC_SS_BMSK                        0x8000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_EMAC_SS_SHFT                           0xf
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_HM_SS_BMSK                          0x4000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_HM_SS_SHFT                             0xe
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_IMC_SS_BMSK                         0x2000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_IMC_SS_SHFT                            0xd
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PERIPH_SS_BMSK                      0x1000
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PERIPH_SS_SHFT                         0xc
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_HDMA_SS_BMSK                         0x800
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_HDMA_SS_SHFT                           0xb
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_CRYPTO_SS_BMSK                       0x400
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_CRYPTO_SS_SHFT                         0xa
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_5_BMSK                       0x100
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_5_SHFT                         0x8
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_4_BMSK                        0x80
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_4_SHFT                         0x7
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_3_BMSK                        0x40
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_3_SHFT                         0x6
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_2_BMSK                        0x20
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_2_SHFT                         0x5
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_1_BMSK                        0x10
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_1_SHFT                         0x4
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_0_BMSK                         0x8
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_MDDR_SS_0_SHFT                         0x3
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PCIE_SS_1_BMSK                         0x4
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PCIE_SS_1_SHFT                         0x2
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PCIE_SS_0_BMSK                         0x2
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_PCIE_SS_0_SHFT                         0x1
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_SATA_SS_BMSK                           0x1
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP0_REG_SATA_SS_SHFT                           0x0

#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_ADDR                            (TCSR_REGS_REG_BASE      + 0x00000004)
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_OFFS                            (TCSR_REGS_REG_BASE_OFFS + 0x00000004)
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_RMSK                                 0x1ff
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_IN          \
        in_dword_masked(HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_ADDR, HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_RMSK)
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_ADDR, m)
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_SPARE0_BMSK                          0x100
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_SPARE0_SHFT                            0x8
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_SPARE1_BMSK                           0x80
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_SPARE1_SHFT                            0x7
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_SPHY1_XPU2_MPU_BMSK                   0x40
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_SPHY1_XPU2_MPU_SHFT                    0x6
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_SPHY0_XPU2_MPU_BMSK                   0x20
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_SPHY0_XPU2_MPU_SHFT                    0x5
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_NSFPB_XPU2_MPU_BMSK                   0x10
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_NSFPB_XPU2_MPU_SHFT                    0x4
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_NSFPB_XPU2_APU_BMSK                    0x8
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_NSFPB_XPU2_APU_SHFT                    0x3
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_WSFPB_XPU2_MPU_BMSK                    0x4
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_WSFPB_XPU2_MPU_SHFT                    0x2
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_WSFPB_XPU2_APU_BMSK                    0x2
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_WSFPB_XPU2_APU_SHFT                    0x1
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_CFG_XPU2_BMSK                          0x1
#define HWIO_TCSR_XPU2_NSEC_INTR_MAP1_REG_CFG_XPU2_SHFT                          0x0

#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_ADDR                        (TCSR_REGS_REG_BASE      + 0x00000008)
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_OFFS                        (TCSR_REGS_REG_BASE_OFFS + 0x00000008)
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_RMSK                              0xff
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_ADDR, HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_SPARE0_BMSK                       0x80
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_SPARE0_SHFT                        0x7
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_SPARE1_BMSK                       0x40
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_SPARE1_SHFT                        0x6
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_QDSS_TRACE_BMSK                   0x20
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_QDSS_TRACE_SHFT                    0x5
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_QDSS_DAP_BMSK                     0x10
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_QDSS_DAP_SHFT                      0x4
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_QDSS_BAM_BMSK                      0x8
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_QDSS_BAM_SHFT                      0x3
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_CRYPTO_SS_BMSK                     0x4
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_CRYPTO_SS_SHFT                     0x2
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_EMAC_SS_BMSK                       0x2
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_EMAC_SS_SHFT                       0x1
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_PERIPH_SS_BMSK                     0x1
#define HWIO_TCSR_VMIDMT_NSECCFG_INTR_MAP_REG_PERIPH_SS_SHFT                     0x0

#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_ADDR                         (TCSR_REGS_REG_BASE      + 0x0000000c)
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_OFFS                         (TCSR_REGS_REG_BASE_OFFS + 0x0000000c)
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_RMSK                               0xff
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_ADDR, HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_SPARE0_BMSK                        0x80
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_SPARE0_SHFT                         0x7
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_SPARE1_BMSK                        0x40
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_SPARE1_SHFT                         0x6
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_QDSS_TRACE_BMSK                    0x20
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_QDSS_TRACE_SHFT                     0x5
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_QDSS_DAP_BMSK                      0x10
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_QDSS_DAP_SHFT                       0x4
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_QDSS_BAM_BMSK                       0x8
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_QDSS_BAM_SHFT                       0x3
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_CRYPTO_SS_BMSK                      0x4
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_CRYPTO_SS_SHFT                      0x2
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_EMAC_SS_BMSK                        0x2
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_EMAC_SS_SHFT                        0x1
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_PERIPH_SS_BMSK                      0x1
#define HWIO_TCSR_VMIDMT_NSECCL_INTR_MAP_REG_PERIPH_SS_SHFT                      0x0

#define HWIO_TCSR_TPDA_INTR_MAP_REG_ADDR                                  (TCSR_REGS_REG_BASE      + 0x00000010)
#define HWIO_TCSR_TPDA_INTR_MAP_REG_OFFS                                  (TCSR_REGS_REG_BASE_OFFS + 0x00000010)
#define HWIO_TCSR_TPDA_INTR_MAP_REG_RMSK                                    0x1fffff
#define HWIO_TCSR_TPDA_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_TPDA_INTR_MAP_REG_ADDR, HWIO_TCSR_TPDA_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_TPDA_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_TPDA_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_TPDA_INTR_MAP_REG_SPARE0_BMSK                             0x100000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_SPARE0_SHFT                                 0x14
#define HWIO_TCSR_TPDA_INTR_MAP_REG_SPARE1_BMSK                              0x80000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_SPARE1_SHFT                                 0x13
#define HWIO_TCSR_TPDA_INTR_MAP_REG_PERIPH_SS_BMSK                           0x40000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_PERIPH_SS_SHFT                              0x12
#define HWIO_TCSR_TPDA_INTR_MAP_REG_EMAC_SS_BMSK                             0x20000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_EMAC_SS_SHFT                                0x11
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_CPU_EVENTS_SE_BMSK             0x10000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_CPU_EVENTS_SE_SHFT                0x10
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_CPU_EVENTS_SW_BMSK              0x8000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_CPU_EVENTS_SW_SHFT                 0xf
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_CPU_EVENTS_NE_BMSK              0x4000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_CPU_EVENTS_NE_SHFT                 0xe
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_CPU_EVENTS_NW_BMSK              0x2000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_CPU_EVENTS_NW_SHFT                 0xd
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_5_BMSK                      0x1000
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_5_SHFT                         0xc
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_4_BMSK                       0x800
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_4_SHFT                         0xb
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_3_BMSK                       0x400
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_3_SHFT                         0xa
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_2_BMSK                       0x200
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_2_SHFT                         0x9
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_1_BMSK                       0x100
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_1_SHFT                         0x8
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_0_BMSK                        0x80
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_DDR_0_SHFT                         0x7
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_WEST_1_BMSK                       0x40
#define HWIO_TCSR_TPDA_INTR_MAP_REG_DEBUG_AJU_WEST_1_SHFT                        0x6
#define HWIO_TCSR_TPDA_INTR_MAP_REG_CRYPTO_SS_BMSK                              0x20
#define HWIO_TCSR_TPDA_INTR_MAP_REG_CRYPTO_SS_SHFT                               0x5
#define HWIO_TCSR_TPDA_INTR_MAP_REG_HDMA_SS_BMSK                                0x10
#define HWIO_TCSR_TPDA_INTR_MAP_REG_HDMA_SS_SHFT                                 0x4
#define HWIO_TCSR_TPDA_INTR_MAP_REG_IMC_SS_BMSK                                  0x8
#define HWIO_TCSR_TPDA_INTR_MAP_REG_IMC_SS_SHFT                                  0x3
#define HWIO_TCSR_TPDA_INTR_MAP_REG_SATA_SS_BMSK                                 0x4
#define HWIO_TCSR_TPDA_INTR_MAP_REG_SATA_SS_SHFT                                 0x2
#define HWIO_TCSR_TPDA_INTR_MAP_REG_PCIE_SS_1_BMSK                               0x2
#define HWIO_TCSR_TPDA_INTR_MAP_REG_PCIE_SS_1_SHFT                               0x1
#define HWIO_TCSR_TPDA_INTR_MAP_REG_PCIE_SS_0_BMSK                               0x1
#define HWIO_TCSR_TPDA_INTR_MAP_REG_PCIE_SS_0_SHFT                               0x0

#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_ADDR                          (TCSR_REGS_REG_BASE      + 0x00000018)
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_OFFS                          (TCSR_REGS_REG_BASE_OFFS + 0x00000018)
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_RMSK                          0x9fffffff
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_ADDR, HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_SPARE0_BMSK                   0x80000000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_SPARE0_SHFT                         0x1f
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_5_BMSK                   0x10000000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_5_SHFT                         0x1c
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_4_BMSK                    0x8000000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_4_SHFT                         0x1b
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_3_BMSK                    0x4000000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_3_SHFT                         0x1a
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_2_BMSK                    0x2000000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_2_SHFT                         0x19
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_1_BMSK                    0x1000000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_1_SHFT                         0x18
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_0_BMSK                     0x800000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MCSU_0_SHFT                         0x17
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_11_BMSK                    0x400000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_11_SHFT                        0x16
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_10_BMSK                    0x200000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_10_SHFT                        0x15
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_9_BMSK                     0x100000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_9_SHFT                         0x14
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_8_BMSK                      0x80000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_8_SHFT                         0x13
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_7_BMSK                      0x40000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_7_SHFT                         0x12
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_6_BMSK                      0x20000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_6_SHFT                         0x11
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_5_BMSK                      0x10000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_5_SHFT                         0x10
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_4_BMSK                       0x8000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_4_SHFT                          0xf
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_3_BMSK                       0x4000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_3_SHFT                          0xe
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_2_BMSK                       0x2000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_2_SHFT                          0xd
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_1_BMSK                       0x1000
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_1_SHFT                          0xc
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_0_BMSK                        0x800
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_MBSU_0_SHFT                          0xb
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_5_BMSK                        0x400
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_5_SHFT                          0xa
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_4_BMSK                        0x200
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_4_SHFT                          0x9
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_3_BMSK                        0x100
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_3_SHFT                          0x8
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_2_BMSK                         0x80
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_2_SHFT                          0x7
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_1_BMSK                         0x40
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_1_SHFT                          0x6
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_0_BMSK                         0x20
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_DMSU_0_SHFT                          0x5
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_4_BMSK                         0x10
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_4_SHFT                          0x4
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_3_BMSK                          0x8
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_3_SHFT                          0x3
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_2_BMSK                          0x4
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_2_SHFT                          0x2
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_1_BMSK                          0x2
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_1_SHFT                          0x1
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_0_BMSK                          0x1
#define HWIO_TCSR_HMSS_SU_PMON_INTR_MAP_REG_PBSU_0_SHFT                          0x0

#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_ADDR                         (TCSR_REGS_REG_BASE      + 0x0000001c)
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_OFFS                         (TCSR_REGS_REG_BASE_OFFS + 0x0000001c)
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_RMSK                         0xffffffff
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_ADDR, HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_SPARE0_BMSK                  0x80000000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_SPARE0_SHFT                        0x1f
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_TRSU_1_BMSK                  0x40000000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_TRSU_1_SHFT                        0x1e
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_TRSU_0_BMSK                  0x20000000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_TRSU_0_SHFT                        0x1d
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_5_BMSK                  0x10000000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_5_SHFT                        0x1c
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_4_BMSK                   0x8000000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_4_SHFT                        0x1b
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_3_BMSK                   0x4000000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_3_SHFT                        0x1a
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_2_BMSK                   0x2000000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_2_SHFT                        0x19
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_1_BMSK                   0x1000000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_1_SHFT                        0x18
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_0_BMSK                    0x800000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MCSU_0_SHFT                        0x17
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_11_BMSK                   0x400000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_11_SHFT                       0x16
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_10_BMSK                   0x200000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_10_SHFT                       0x15
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_9_BMSK                    0x100000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_9_SHFT                        0x14
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_8_BMSK                     0x80000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_8_SHFT                        0x13
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_7_BMSK                     0x40000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_7_SHFT                        0x12
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_6_BMSK                     0x20000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_6_SHFT                        0x11
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_5_BMSK                     0x10000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_5_SHFT                        0x10
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_4_BMSK                      0x8000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_4_SHFT                         0xf
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_3_BMSK                      0x4000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_3_SHFT                         0xe
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_2_BMSK                      0x2000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_2_SHFT                         0xd
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_1_BMSK                      0x1000
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_1_SHFT                         0xc
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_0_BMSK                       0x800
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_MBSU_0_SHFT                         0xb
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_5_BMSK                       0x400
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_5_SHFT                         0xa
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_4_BMSK                       0x200
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_4_SHFT                         0x9
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_3_BMSK                       0x100
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_3_SHFT                         0x8
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_2_BMSK                        0x80
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_2_SHFT                         0x7
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_1_BMSK                        0x40
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_1_SHFT                         0x6
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_0_BMSK                        0x20
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_DMSU_0_SHFT                         0x5
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_4_BMSK                        0x10
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_4_SHFT                         0x4
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_3_BMSK                         0x8
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_3_SHFT                         0x3
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_2_BMSK                         0x4
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_2_SHFT                         0x2
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_1_BMSK                         0x2
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_1_SHFT                         0x1
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_0_BMSK                         0x1
#define HWIO_TCSR_HMSS_SU_ERROR_INTR_MAP_REG_PBSU_0_SHFT                         0x0

#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_ADDR                          (TCSR_REGS_REG_BASE      + 0x00000020)
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_OFFS                          (TCSR_REGS_REG_BASE_OFFS + 0x00000020)
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_RMSK                              0x3fff
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_ADDR, HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_SPARE0_BMSK                       0x2000
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_SPARE0_SHFT                          0xd
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_SPARE1_BMSK                       0x1000
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_SPARE1_SHFT                          0xc
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_11_BMSK                        0x800
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_11_SHFT                          0xb
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_10_BMSK                        0x400
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_10_SHFT                          0xa
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_9_BMSK                         0x200
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_9_SHFT                           0x9
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_8_BMSK                         0x100
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_8_SHFT                           0x8
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_7_BMSK                          0x80
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_7_SHFT                           0x7
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_6_BMSK                          0x40
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_6_SHFT                           0x6
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_5_BMSK                          0x20
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_5_SHFT                           0x5
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_4_BMSK                          0x10
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_4_SHFT                           0x4
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_3_BMSK                           0x8
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_3_SHFT                           0x3
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_2_BMSK                           0x4
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_2_SHFT                           0x2
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_1_BMSK                           0x2
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_1_SHFT                           0x1
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_0_BMSK                           0x1
#define HWIO_TCSR_HMSS_L3_INFO_INTR_MAP_REG_L3U_0_SHFT                           0x0

#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_ADDR                          (TCSR_REGS_REG_BASE      + 0x00000024)
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_OFFS                          (TCSR_REGS_REG_BASE_OFFS + 0x00000024)
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_RMSK                              0x3fff
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_ADDR, HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_SPARE0_BMSK                       0x2000
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_SPARE0_SHFT                          0xd
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_SPARE1_BMSK                       0x1000
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_SPARE1_SHFT                          0xc
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_11_BMSK                        0x800
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_11_SHFT                          0xb
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_10_BMSK                        0x400
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_10_SHFT                          0xa
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_9_BMSK                         0x200
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_9_SHFT                           0x9
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_8_BMSK                         0x100
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_8_SHFT                           0x8
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_7_BMSK                          0x80
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_7_SHFT                           0x7
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_6_BMSK                          0x40
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_6_SHFT                           0x6
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_5_BMSK                          0x20
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_5_SHFT                           0x5
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_4_BMSK                          0x10
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_4_SHFT                           0x4
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_3_BMSK                           0x8
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_3_SHFT                           0x3
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_2_BMSK                           0x4
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_2_SHFT                           0x2
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_1_BMSK                           0x2
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_1_SHFT                           0x1
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_0_BMSK                           0x1
#define HWIO_TCSR_HMSS_L3_PMON_INTR_MAP_REG_L3U_0_SHFT                           0x0

#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_ADDR                         (TCSR_REGS_REG_BASE      + 0x00000028)
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_OFFS                         (TCSR_REGS_REG_BASE_OFFS + 0x00000028)
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_RMSK                             0x3fff
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_ADDR, HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_SPARE0_BMSK                      0x2000
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_SPARE0_SHFT                         0xd
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_SPARE1_BMSK                      0x1000
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_SPARE1_SHFT                         0xc
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_11_BMSK                       0x800
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_11_SHFT                         0xb
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_10_BMSK                       0x400
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_10_SHFT                         0xa
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_9_BMSK                        0x200
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_9_SHFT                          0x9
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_8_BMSK                        0x100
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_8_SHFT                          0x8
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_7_BMSK                         0x80
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_7_SHFT                          0x7
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_6_BMSK                         0x40
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_6_SHFT                          0x6
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_5_BMSK                         0x20
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_5_SHFT                          0x5
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_4_BMSK                         0x10
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_4_SHFT                          0x4
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_3_BMSK                          0x8
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_3_SHFT                          0x3
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_2_BMSK                          0x4
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_2_SHFT                          0x2
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_1_BMSK                          0x2
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_1_SHFT                          0x1
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_0_BMSK                          0x1
#define HWIO_TCSR_HMSS_L3_ERROR_INTR_MAP_REG_L3U_0_SHFT                          0x0

#define HWIO_TCSR_SFPB_INTR_MAP_REG_ADDR                                  (TCSR_REGS_REG_BASE      + 0x0000002c)
#define HWIO_TCSR_SFPB_INTR_MAP_REG_OFFS                                  (TCSR_REGS_REG_BASE_OFFS + 0x0000002c)
#define HWIO_TCSR_SFPB_INTR_MAP_REG_RMSK                                     0x3fff8
#define HWIO_TCSR_SFPB_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_SFPB_INTR_MAP_REG_ADDR, HWIO_TCSR_SFPB_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_SFPB_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_SFPB_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SPARE0_BMSK                              0x20000
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SPARE0_SHFT                                 0x11
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SPARE1_BMSK                              0x10000
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SPARE1_SHFT                                 0x10
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_WEST_BMSK                            0x8000
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_WEST_SHFT                               0xf
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_SW_BMSK                              0x4000
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_SW_SHFT                                 0xe
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_SE_BMSK                              0x2000
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_SE_SHFT                                 0xd
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_NW_BMSK                              0x1000
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_NW_SHFT                                 0xc
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_NE_BMSK                               0x800
#define HWIO_TCSR_SFPB_INTR_MAP_REG_HMSS_NE_SHFT                                 0xb
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_SOUTHEAST_BMSK                        0x400
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_SOUTHEAST_SHFT                          0xa
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_WEST_BMSK                             0x200
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_WEST_SHFT                               0x9
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_SOUTH_2_BMSK                          0x100
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_SOUTH_2_SHFT                            0x8
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_SOUTH_1_BMSK                           0x80
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_SOUTH_1_SHFT                            0x7
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_NORTH_2_BMSK                           0x40
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_NORTH_2_SHFT                            0x6
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_NORTH_1_BMSK                           0x20
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_NORTH_1_SHFT                            0x5
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_PCIE_SS_1_BMSK                         0x10
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_PCIE_SS_1_SHFT                          0x4
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_PCIE_SS_0_BMSK                          0x8
#define HWIO_TCSR_SFPB_INTR_MAP_REG_SFPB_PCIE_SS_0_SHFT                          0x3

#define HWIO_TCSR_VBU_INTR_MAP_REG_ADDR                                   (TCSR_REGS_REG_BASE      + 0x00000030)
#define HWIO_TCSR_VBU_INTR_MAP_REG_OFFS                                   (TCSR_REGS_REG_BASE_OFFS + 0x00000030)
#define HWIO_TCSR_VBU_INTR_MAP_REG_RMSK                                         0xfe
#define HWIO_TCSR_VBU_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_VBU_INTR_MAP_REG_ADDR, HWIO_TCSR_VBU_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_VBU_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_VBU_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_VBU_INTR_MAP_REG_SPARE0_BMSK                                  0x80
#define HWIO_TCSR_VBU_INTR_MAP_REG_SPARE0_SHFT                                   0x7
#define HWIO_TCSR_VBU_INTR_MAP_REG_SPARE1_BMSK                                  0x40
#define HWIO_TCSR_VBU_INTR_MAP_REG_SPARE1_SHFT                                   0x6
#define HWIO_TCSR_VBU_INTR_MAP_REG_CHIP_TOP_BMSK                                0x20
#define HWIO_TCSR_VBU_INTR_MAP_REG_CHIP_TOP_SHFT                                 0x5
#define HWIO_TCSR_VBU_INTR_MAP_REG_VBU_PCIE_SS_1_BMSK                           0x10
#define HWIO_TCSR_VBU_INTR_MAP_REG_VBU_PCIE_SS_1_SHFT                            0x4
#define HWIO_TCSR_VBU_INTR_MAP_REG_VBU_PCIE_SS_0_BMSK                            0x8
#define HWIO_TCSR_VBU_INTR_MAP_REG_VBU_PCIE_SS_0_SHFT                            0x3
#define HWIO_TCSR_VBU_INTR_MAP_REG_VBU_SATA_SS_BMSK                              0x4
#define HWIO_TCSR_VBU_INTR_MAP_REG_VBU_SATA_SS_SHFT                              0x2
#define HWIO_TCSR_VBU_INTR_MAP_REG_VBU_HDMA_SS_BMSK                              0x2
#define HWIO_TCSR_VBU_INTR_MAP_REG_VBU_HDMA_SS_SHFT                              0x1

#define HWIO_TCSR_FABRIC_INTR_MAP_REG_ADDR                                (TCSR_REGS_REG_BASE      + 0x00000034)
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_OFFS                                (TCSR_REGS_REG_BASE_OFFS + 0x00000034)
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_RMSK                                      0x3f
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_FABRIC_INTR_MAP_REG_ADDR, HWIO_TCSR_FABRIC_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_FABRIC_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_SPARE0_BMSK                               0x20
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_SPARE0_SHFT                                0x5
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_SPARE1_BMSK                               0x10
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_SPARE1_SHFT                                0x4
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_IMC_FABRIC_BMSK                            0x8
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_IMC_FABRIC_SHFT                            0x3
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_PERIPH_FABRIC_BMSK                         0x4
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_PERIPH_FABRIC_SHFT                         0x2
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_CONFIG_FABRIC_BMSK                         0x2
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_CONFIG_FABRIC_SHFT                         0x1
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_SYSTEM_FABRIC_BMSK                         0x1
#define HWIO_TCSR_FABRIC_INTR_MAP_REG_SYSTEM_FABRIC_SHFT                         0x0

#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_ADDR                               (TCSR_REGS_REG_BASE      + 0x00000038)
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_OFFS                               (TCSR_REGS_REG_BASE_OFFS + 0x00000038)
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_RMSK                                  0x3fe17
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_TPDM_TC_INTR_MAP_REG_ADDR, HWIO_TCSR_TPDM_TC_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_TPDM_TC_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_SPARE0_BMSK                           0x20000
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_SPARE0_SHFT                              0x11
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_SPARE1_BMSK                           0x10000
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_SPARE1_SHFT                              0x10
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_5_BMSK                   0x8000
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_5_SHFT                      0xf
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_4_BMSK                   0x4000
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_4_SHFT                      0xe
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_3_BMSK                   0x2000
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_3_SHFT                      0xd
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_2_BMSK                   0x1000
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_2_SHFT                      0xc
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_1_BMSK                    0x800
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_1_SHFT                      0xb
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_0_BMSK                    0x400
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_DEBUG_AJU_DDR_0_SHFT                      0xa
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_VBU_BMSK                                0x200
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_VBU_SHFT                                  0x9
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_HDMA_SS_BMSK                             0x10
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_HDMA_SS_SHFT                              0x4
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_SATA_SS_BMSK                              0x4
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_SATA_SS_SHFT                              0x2
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_PCIE_SS_1_BMSK                            0x2
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_PCIE_SS_1_SHFT                            0x1
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_PCIE_SS_0_BMSK                            0x1
#define HWIO_TCSR_TPDM_TC_INTR_MAP_REG_PCIE_SS_0_SHFT                            0x0

#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_ADDR                               (TCSR_REGS_REG_BASE      + 0x0000003c)
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_OFFS                               (TCSR_REGS_REG_BASE_OFFS + 0x0000003c)
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_RMSK                                  0xffe57
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_TPDM_BC_INTR_MAP_REG_ADDR, HWIO_TCSR_TPDM_BC_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_TPDM_BC_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_SPARE0_BMSK                           0x80000
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_SPARE0_SHFT                              0x13
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_SPARE1_BMSK                           0x40000
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_SPARE1_SHFT                              0x12
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_AJU_W_BMSK                            0x20000
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_AJU_W_SHFT                               0x11
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_IMC_SS_DEBUG_AJU_BMSK                 0x10000
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_IMC_SS_DEBUG_AJU_SHFT                    0x10
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_5_BMSK                   0x8000
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_5_SHFT                      0xf
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_4_BMSK                   0x4000
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_4_SHFT                      0xe
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_3_BMSK                   0x2000
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_3_SHFT                      0xd
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_2_BMSK                   0x1000
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_2_SHFT                      0xc
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_1_BMSK                    0x800
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_1_SHFT                      0xb
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_0_BMSK                    0x400
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_DEBUG_AJU_DDR_0_SHFT                      0xa
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_VBU_BMSK                                0x200
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_VBU_SHFT                                  0x9
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_PERIPH_SS_BMSK                           0x40
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_PERIPH_SS_SHFT                            0x6
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_HDMA_SS_BMSK                             0x10
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_HDMA_SS_SHFT                              0x4
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_SATA_SS_BMSK                              0x4
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_SATA_SS_SHFT                              0x2
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_PCIE_SS_1_BMSK                            0x2
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_PCIE_SS_1_SHFT                            0x1
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_PCIE_SS_0_BMSK                            0x1
#define HWIO_TCSR_TPDM_BC_INTR_MAP_REG_PCIE_SS_0_SHFT                            0x0

#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_ADDR                             (TCSR_REGS_REG_BASE      + 0x00010000)
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_OFFS                             (TCSR_REGS_REG_BASE_OFFS + 0x00010000)
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_RMSK                             0xfffffdff
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_IN          \
        in_dword_masked(HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_ADDR, HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_RMSK)
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_ADDR, m)
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_EC_XPU2_BMSK                     0x80000000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_EC_XPU2_SHFT                           0x1f
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_IMEM_BMSK                        0x40000000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_IMEM_SHFT                              0x1e
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_QDSS_BMSK                        0x20000000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_QDSS_SHFT                              0x1d
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MPM_BMSK                         0x10000000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MPM_SHFT                               0x1c
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MESSAGE_RAM_BMSK                  0x8000000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MESSAGE_RAM_SHFT                       0x1b
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PMIC_ARB_2_BMSK                   0x4000000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PMIC_ARB_2_SHFT                        0x1a
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PMIC_ARB_1_BMSK                   0x2000000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PMIC_ARB_1_SHFT                        0x19
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PMIC_ARB_0_BMSK                   0x1000000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PMIC_ARB_0_SHFT                        0x18
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_FAN_TACH_BMSK                      0x800000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_FAN_TACH_SHFT                          0x17
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_SECURITY_CONTROL_BMSK              0x400000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_SECURITY_CONTROL_SHFT                  0x16
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_TLMM_BMSK                          0x200000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_TLMM_SHFT                              0x15
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_CORE_TOP_CSR_BMSK                  0x100000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_CORE_TOP_CSR_SHFT                      0x14
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_GCCMW_BMSK                          0x80000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_GCCMW_SHFT                             0x13
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_GCCE_BMSK                           0x40000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_GCCE_SHFT                              0x12
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_GCC_MS_S_BMSK                       0x20000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_GCC_MS_S_SHFT                          0x11
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_GCC_MS_N_BMSK                       0x10000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_GCC_MS_N_SHFT                          0x10
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_EMAC_SS_BMSK                         0x8000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_EMAC_SS_SHFT                            0xf
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_HM_SS_BMSK                           0x4000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_HM_SS_SHFT                              0xe
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_IMC_SS_BMSK                          0x2000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_IMC_SS_SHFT                             0xd
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PERIPH_SS_BMSK                       0x1000
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PERIPH_SS_SHFT                          0xc
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_HDMA_SS_BMSK                          0x800
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_HDMA_SS_SHFT                            0xb
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_CRYPTO_SS_BMSK                        0x400
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_CRYPTO_SS_SHFT                          0xa
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_5_BMSK                        0x100
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_5_SHFT                          0x8
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_4_BMSK                         0x80
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_4_SHFT                          0x7
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_3_BMSK                         0x40
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_3_SHFT                          0x6
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_2_BMSK                         0x20
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_2_SHFT                          0x5
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_1_BMSK                         0x10
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_1_SHFT                          0x4
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_0_BMSK                          0x8
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_MDDR_SS_0_SHFT                          0x3
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PCIE_SS_1_BMSK                          0x4
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PCIE_SS_1_SHFT                          0x2
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PCIE_SS_0_BMSK                          0x2
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_PCIE_SS_0_SHFT                          0x1
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_SATA_SS_BMSK                            0x1
#define HWIO_TCSR_XPU2_MSA_INTR_MAP0_REG_SATA_SS_SHFT                            0x0

#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_ADDR                             (TCSR_REGS_REG_BASE      + 0x00010004)
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_OFFS                             (TCSR_REGS_REG_BASE_OFFS + 0x00010004)
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_RMSK                                  0x1ff
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_IN          \
        in_dword_masked(HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_ADDR, HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_RMSK)
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_ADDR, m)
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_SPARE0_BMSK                           0x100
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_SPARE0_SHFT                             0x8
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_SPARE1_BMSK                            0x80
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_SPARE1_SHFT                             0x7
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_SPHY1_XPU2_MPU_BMSK                    0x40
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_SPHY1_XPU2_MPU_SHFT                     0x6
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_SPHY0_XPU2_MPU_BMSK                    0x20
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_SPHY0_XPU2_MPU_SHFT                     0x5
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_NSFPB_XPU2_MPU_BMSK                    0x10
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_NSFPB_XPU2_MPU_SHFT                     0x4
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_NSFPB_XPU2_APU_BMSK                     0x8
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_NSFPB_XPU2_APU_SHFT                     0x3
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_WSFPB_XPU2_MPU_BMSK                     0x4
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_WSFPB_XPU2_MPU_SHFT                     0x2
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_WSFPB_XPU2_APU_BMSK                     0x2
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_WSFPB_XPU2_APU_SHFT                     0x1
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_CFG_XPU2_BMSK                           0x1
#define HWIO_TCSR_XPU2_MSA_INTR_MAP1_REG_CFG_XPU2_SHFT                           0x0

#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_ADDR                             (TCSR_REGS_REG_BASE      + 0x00020000)
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_OFFS                             (TCSR_REGS_REG_BASE_OFFS + 0x00020000)
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_RMSK                             0xfffffdff
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_IN          \
        in_dword_masked(HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_ADDR, HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_RMSK)
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_ADDR, m)
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_EC_XPU2_BMSK                     0x80000000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_EC_XPU2_SHFT                           0x1f
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_IMEM_BMSK                        0x40000000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_IMEM_SHFT                              0x1e
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_QDSS_BMSK                        0x20000000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_QDSS_SHFT                              0x1d
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MPM_BMSK                         0x10000000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MPM_SHFT                               0x1c
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MESSAGE_RAM_BMSK                  0x8000000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MESSAGE_RAM_SHFT                       0x1b
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PMIC_ARB_2_BMSK                   0x4000000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PMIC_ARB_2_SHFT                        0x1a
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PMIC_ARB_1_BMSK                   0x2000000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PMIC_ARB_1_SHFT                        0x19
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PMIC_ARB_0_BMSK                   0x1000000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PMIC_ARB_0_SHFT                        0x18
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_FAN_TACH_BMSK                      0x800000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_FAN_TACH_SHFT                          0x17
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_SECURITY_CONTROL_BMSK              0x400000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_SECURITY_CONTROL_SHFT                  0x16
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_TLMM_BMSK                          0x200000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_TLMM_SHFT                              0x15
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_CORE_TOP_CSR_BMSK                  0x100000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_CORE_TOP_CSR_SHFT                      0x14
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_GCCMW_BMSK                          0x80000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_GCCMW_SHFT                             0x13
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_GCCE_BMSK                           0x40000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_GCCE_SHFT                              0x12
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_GCC_MS_S_BMSK                       0x20000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_GCC_MS_S_SHFT                          0x11
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_GCC_MS_N_BMSK                       0x10000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_GCC_MS_N_SHFT                          0x10
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_EMAC_SS_BMSK                         0x8000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_EMAC_SS_SHFT                            0xf
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_HM_SS_BMSK                           0x4000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_HM_SS_SHFT                              0xe
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_IMC_SS_BMSK                          0x2000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_IMC_SS_SHFT                             0xd
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PERIPH_SS_BMSK                       0x1000
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PERIPH_SS_SHFT                          0xc
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_HDMA_SS_BMSK                          0x800
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_HDMA_SS_SHFT                            0xb
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_CRYPTO_SS_BMSK                        0x400
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_CRYPTO_SS_SHFT                          0xa
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_5_BMSK                        0x100
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_5_SHFT                          0x8
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_4_BMSK                         0x80
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_4_SHFT                          0x7
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_3_BMSK                         0x40
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_3_SHFT                          0x6
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_2_BMSK                         0x20
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_2_SHFT                          0x5
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_1_BMSK                         0x10
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_1_SHFT                          0x4
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_0_BMSK                          0x8
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_MDDR_SS_0_SHFT                          0x3
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PCIE_SS_1_BMSK                          0x4
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PCIE_SS_1_SHFT                          0x2
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PCIE_SS_0_BMSK                          0x2
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_PCIE_SS_0_SHFT                          0x1
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_SATA_SS_BMSK                            0x1
#define HWIO_TCSR_XPU2_SEC_INTR_MAP0_REG_SATA_SS_SHFT                            0x0

#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_ADDR                             (TCSR_REGS_REG_BASE      + 0x00020004)
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_OFFS                             (TCSR_REGS_REG_BASE_OFFS + 0x00020004)
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_RMSK                                  0x1ff
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_IN          \
        in_dword_masked(HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_ADDR, HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_RMSK)
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_ADDR, m)
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_SPARE0_BMSK                           0x100
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_SPARE0_SHFT                             0x8
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_SPARE1_BMSK                            0x80
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_SPARE1_SHFT                             0x7
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_SPHY1_XPU2_MPU_BMSK                    0x40
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_SPHY1_XPU2_MPU_SHFT                     0x6
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_SPHY0_XPU2_MPU_BMSK                    0x20
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_SPHY0_XPU2_MPU_SHFT                     0x5
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_NSFPB_XPU2_MPU_BMSK                    0x10
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_NSFPB_XPU2_MPU_SHFT                     0x4
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_NSFPB_XPU2_APU_BMSK                     0x8
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_NSFPB_XPU2_APU_SHFT                     0x3
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_WSFPB_XPU2_MPU_BMSK                     0x4
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_WSFPB_XPU2_MPU_SHFT                     0x2
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_WSFPB_XPU2_APU_BMSK                     0x2
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_WSFPB_XPU2_APU_SHFT                     0x1
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_CFG_XPU2_BMSK                           0x1
#define HWIO_TCSR_XPU2_SEC_INTR_MAP1_REG_CFG_XPU2_SHFT                           0x0

#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_ADDR                         (TCSR_REGS_REG_BASE      + 0x00020008)
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_OFFS                         (TCSR_REGS_REG_BASE_OFFS + 0x00020008)
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_RMSK                               0xff
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_ADDR, HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_SPARE0_BMSK                        0x80
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_SPARE0_SHFT                         0x7
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_SPARE1_BMSK                        0x40
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_SPARE1_SHFT                         0x6
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_QDSS_TRACE_BMSK                    0x20
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_QDSS_TRACE_SHFT                     0x5
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_QDSS_DAP_BMSK                      0x10
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_QDSS_DAP_SHFT                       0x4
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_QDSS_BAM_BMSK                       0x8
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_QDSS_BAM_SHFT                       0x3
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_CRYPTO_SS_BMSK                      0x4
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_CRYPTO_SS_SHFT                      0x2
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_EMAC_SS_BMSK                        0x2
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_EMAC_SS_SHFT                        0x1
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_PERIPH_SS_BMSK                      0x1
#define HWIO_TCSR_VMIDMT_SECCFG_INTR_MAP_REG_PERIPH_SS_SHFT                      0x0

#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_ADDR                          (TCSR_REGS_REG_BASE      + 0x0002000c)
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_OFFS                          (TCSR_REGS_REG_BASE_OFFS + 0x0002000c)
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_RMSK                                0xff
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_IN          \
        in_dword_masked(HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_ADDR, HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_RMSK)
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_ADDR, m)
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_SPARE0_BMSK                         0x80
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_SPARE0_SHFT                          0x7
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_SPARE1_BMSK                         0x40
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_SPARE1_SHFT                          0x6
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_QDSS_TRACE_BMSK                     0x20
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_QDSS_TRACE_SHFT                      0x5
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_QDSS_DAP_BMSK                       0x10
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_QDSS_DAP_SHFT                        0x4
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_QDSS_BAM_BMSK                        0x8
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_QDSS_BAM_SHFT                        0x3
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_CRYPTO_SS_BMSK                       0x4
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_CRYPTO_SS_SHFT                       0x2
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_EMAC_SS_BMSK                         0x2
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_EMAC_SS_SHFT                         0x1
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_PERIPH_SS_BMSK                       0x1
#define HWIO_TCSR_VMIDMT_SECCL_INTR_MAP_REG_PERIPH_SS_SHFT                       0x0

#define HWIO_TCSR_SOC_HW_VERSION_ADDR                                     (TCSR_REGS_REG_BASE      + 0x00030000)
#define HWIO_TCSR_SOC_HW_VERSION_OFFS                                     (TCSR_REGS_REG_BASE_OFFS + 0x00030000)
#define HWIO_TCSR_SOC_HW_VERSION_RMSK                                     0xffffffff
#define HWIO_TCSR_SOC_HW_VERSION_IN          \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, HWIO_TCSR_SOC_HW_VERSION_RMSK)
#define HWIO_TCSR_SOC_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, m)
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_MEMBER_BMSK                       0xf0000000
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_MEMBER_SHFT                             0x1c
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_MEMBER_BMSK                        0xfff0000
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_MEMBER_SHFT                             0x10
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK                           0xff00
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT                              0x8
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK                             0xff
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT                              0x0

#define HWIO_MEM_SVS_SEL_DIG_CX1_ADDR                                     (TCSR_REGS_REG_BASE      + 0x00040000)
#define HWIO_MEM_SVS_SEL_DIG_CX1_OFFS                                     (TCSR_REGS_REG_BASE_OFFS + 0x00040000)
#define HWIO_MEM_SVS_SEL_DIG_CX1_RMSK                                            0x1
#define HWIO_MEM_SVS_SEL_DIG_CX1_IN          \
        in_dword_masked(HWIO_MEM_SVS_SEL_DIG_CX1_ADDR, HWIO_MEM_SVS_SEL_DIG_CX1_RMSK)
#define HWIO_MEM_SVS_SEL_DIG_CX1_INM(m)      \
        in_dword_masked(HWIO_MEM_SVS_SEL_DIG_CX1_ADDR, m)
#define HWIO_MEM_SVS_SEL_DIG_CX1_OUT(v)      \
        out_dword(HWIO_MEM_SVS_SEL_DIG_CX1_ADDR,v)
#define HWIO_MEM_SVS_SEL_DIG_CX1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MEM_SVS_SEL_DIG_CX1_ADDR,m,v,HWIO_MEM_SVS_SEL_DIG_CX1_IN)
#define HWIO_MEM_SVS_SEL_DIG_CX1_MEM_SVS_SEL_DIG_CX1_BMSK                        0x1
#define HWIO_MEM_SVS_SEL_DIG_CX1_MEM_SVS_SEL_DIG_CX1_SHFT                        0x0

#define HWIO_MEM_SVS_SEL_CBF_CX2_ADDR                                     (TCSR_REGS_REG_BASE      + 0x00050000)
#define HWIO_MEM_SVS_SEL_CBF_CX2_OFFS                                     (TCSR_REGS_REG_BASE_OFFS + 0x00050000)
#define HWIO_MEM_SVS_SEL_CBF_CX2_RMSK                                            0x1
#define HWIO_MEM_SVS_SEL_CBF_CX2_IN          \
        in_dword_masked(HWIO_MEM_SVS_SEL_CBF_CX2_ADDR, HWIO_MEM_SVS_SEL_CBF_CX2_RMSK)
#define HWIO_MEM_SVS_SEL_CBF_CX2_INM(m)      \
        in_dword_masked(HWIO_MEM_SVS_SEL_CBF_CX2_ADDR, m)
#define HWIO_MEM_SVS_SEL_CBF_CX2_OUT(v)      \
        out_dword(HWIO_MEM_SVS_SEL_CBF_CX2_ADDR,v)
#define HWIO_MEM_SVS_SEL_CBF_CX2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MEM_SVS_SEL_CBF_CX2_ADDR,m,v,HWIO_MEM_SVS_SEL_CBF_CX2_IN)
#define HWIO_MEM_SVS_SEL_CBF_CX2_MEM_SVS_SEL_CBF_CX2_BMSK                        0x1
#define HWIO_MEM_SVS_SEL_CBF_CX2_MEM_SVS_SEL_CBF_CX2_SHFT                        0x0

#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_ADDR                                 (TCSR_REGS_REG_BASE      + 0x00060000)
#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_OFFS                                 (TCSR_REGS_REG_BASE_OFFS + 0x00060000)
#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_RMSK                                        0x3
#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_IN          \
        in_dword_masked(HWIO_TIC_AHB2AHB_TESTBUS_SEL_ADDR, HWIO_TIC_AHB2AHB_TESTBUS_SEL_RMSK)
#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TIC_AHB2AHB_TESTBUS_SEL_ADDR, m)
#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_OUT(v)      \
        out_dword(HWIO_TIC_AHB2AHB_TESTBUS_SEL_ADDR,v)
#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TIC_AHB2AHB_TESTBUS_SEL_ADDR,m,v,HWIO_TIC_AHB2AHB_TESTBUS_SEL_IN)
#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_TESTBUS_SEL_BMSK                            0x3
#define HWIO_TIC_AHB2AHB_TESTBUS_SEL_TESTBUS_SEL_SHFT                            0x0

#define HWIO_SPARE1_ADDR                                                  (TCSR_REGS_REG_BASE      + 0x00070000)
#define HWIO_SPARE1_OFFS                                                  (TCSR_REGS_REG_BASE_OFFS + 0x00070000)
#define HWIO_SPARE1_RMSK                                                      0xffff
#define HWIO_SPARE1_IN          \
        in_dword_masked(HWIO_SPARE1_ADDR, HWIO_SPARE1_RMSK)
#define HWIO_SPARE1_INM(m)      \
        in_dword_masked(HWIO_SPARE1_ADDR, m)
#define HWIO_SPARE1_OUT(v)      \
        out_dword(HWIO_SPARE1_ADDR,v)
#define HWIO_SPARE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SPARE1_ADDR,m,v,HWIO_SPARE1_IN)
#define HWIO_SPARE1_SPARE1_OUTPUT_BMSK                                        0xff00
#define HWIO_SPARE1_SPARE1_OUTPUT_SHFT                                           0x8
#define HWIO_SPARE1_SPARE1_INPUT_BMSK                                           0xff
#define HWIO_SPARE1_SPARE1_INPUT_SHFT                                            0x0

#define HWIO_SPARE2_ADDR                                                  (TCSR_REGS_REG_BASE      + 0x00080000)
#define HWIO_SPARE2_OFFS                                                  (TCSR_REGS_REG_BASE_OFFS + 0x00080000)
#define HWIO_SPARE2_RMSK                                                      0xffff
#define HWIO_SPARE2_IN          \
        in_dword_masked(HWIO_SPARE2_ADDR, HWIO_SPARE2_RMSK)
#define HWIO_SPARE2_INM(m)      \
        in_dword_masked(HWIO_SPARE2_ADDR, m)
#define HWIO_SPARE2_OUT(v)      \
        out_dword(HWIO_SPARE2_ADDR,v)
#define HWIO_SPARE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SPARE2_ADDR,m,v,HWIO_SPARE2_IN)
#define HWIO_SPARE2_SPARE2_OUTPUT_BMSK                                        0xff00
#define HWIO_SPARE2_SPARE2_OUTPUT_SHFT                                           0x8
#define HWIO_SPARE2_SPARE2_INPUT_BMSK                                           0xff
#define HWIO_SPARE2_SPARE2_INPUT_SHFT                                            0x0

#define HWIO_SPARE3_ADDR                                                  (TCSR_REGS_REG_BASE      + 0x00090000)
#define HWIO_SPARE3_OFFS                                                  (TCSR_REGS_REG_BASE_OFFS + 0x00090000)
#define HWIO_SPARE3_RMSK                                                      0xffff
#define HWIO_SPARE3_IN          \
        in_dword_masked(HWIO_SPARE3_ADDR, HWIO_SPARE3_RMSK)
#define HWIO_SPARE3_INM(m)      \
        in_dword_masked(HWIO_SPARE3_ADDR, m)
#define HWIO_SPARE3_OUT(v)      \
        out_dword(HWIO_SPARE3_ADDR,v)
#define HWIO_SPARE3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SPARE3_ADDR,m,v,HWIO_SPARE3_IN)
#define HWIO_SPARE3_SPARE3_OUTPUT_BMSK                                        0xff00
#define HWIO_SPARE3_SPARE3_OUTPUT_SHFT                                           0x8
#define HWIO_SPARE3_SPARE3_INPUT_BMSK                                           0xff
#define HWIO_SPARE3_SPARE3_INPUT_SHFT                                            0x0

#define HWIO_RG10_SPARE1_ADDR                                             (TCSR_REGS_REG_BASE      + 0x000a0000)
#define HWIO_RG10_SPARE1_OFFS                                             (TCSR_REGS_REG_BASE_OFFS + 0x000a0000)
#define HWIO_RG10_SPARE1_RMSK                                             0xffffffff
#define HWIO_RG10_SPARE1_IN          \
        in_dword_masked(HWIO_RG10_SPARE1_ADDR, HWIO_RG10_SPARE1_RMSK)
#define HWIO_RG10_SPARE1_INM(m)      \
        in_dword_masked(HWIO_RG10_SPARE1_ADDR, m)
#define HWIO_RG10_SPARE1_OUT(v)      \
        out_dword(HWIO_RG10_SPARE1_ADDR,v)
#define HWIO_RG10_SPARE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RG10_SPARE1_ADDR,m,v,HWIO_RG10_SPARE1_IN)
#define HWIO_RG10_SPARE1_SPARE_BMSK                                       0xffffffff
#define HWIO_RG10_SPARE1_SPARE_SHFT                                              0x0

#define HWIO_RG10_SPARE2_ADDR                                             (TCSR_REGS_REG_BASE      + 0x000a0004)
#define HWIO_RG10_SPARE2_OFFS                                             (TCSR_REGS_REG_BASE_OFFS + 0x000a0004)
#define HWIO_RG10_SPARE2_RMSK                                             0xffffffff
#define HWIO_RG10_SPARE2_IN          \
        in_dword_masked(HWIO_RG10_SPARE2_ADDR, HWIO_RG10_SPARE2_RMSK)
#define HWIO_RG10_SPARE2_INM(m)      \
        in_dword_masked(HWIO_RG10_SPARE2_ADDR, m)
#define HWIO_RG10_SPARE2_OUT(v)      \
        out_dword(HWIO_RG10_SPARE2_ADDR,v)
#define HWIO_RG10_SPARE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RG10_SPARE2_ADDR,m,v,HWIO_RG10_SPARE2_IN)
#define HWIO_RG10_SPARE2_SPARE_BMSK                                       0xffffffff
#define HWIO_RG10_SPARE2_SPARE_SHFT                                              0x0


#endif /* __TCSR_SPARE_HWIO_H__ */
