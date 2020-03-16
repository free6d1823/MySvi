
//-----------------------------------------------------------------------------
// Qualcomm Technologies, Inc. Proprietary
// Copyright (c) 2012-2016, Qualcomm Technologies, Inc. All rights reserved.
//
// All data and information contained in or disclosed by this document are
// confidential and proprietary information of Qualcomm Technologies, Inc. or
// its Affiliates, or their licensors, and all rights therein are expressly
// reserved. By accepting this material, the recipient agrees that this
// material and the information contained therein are held in confidence and
// in trust and will not be used, copied, reproduced in whole or in part, nor
// its contents revealed in any manner to others, without the express written
// permission of Qualcomm Technologies, Inc., or to the extent expressly
// permitted by the Technology License Agreement between Qualcomm Technologies,

//
// This technology was exported from the United States in accordance with the
// approval from the U.S. Department of Commerce, Bureau of Industry and
// Security, Export Administration Regulations (EAR).  Any re-export or
// in-country transfers of this technology is subject to U.S. Laws and
// regulations. Diversion contrary to U.S. law prohibited.
//-----------------------------------------------------------------------------

#ifndef __MSMHWIOBASE_H__
#define __MSMHWIOBASE_H__

#define MSG_IMEM_RAM_SIZE_BASE                                      0x00010000
#define MSG_IMEM_RAM_SIZE_BASE_SIZE                                 0x100000000
#define MSG_IMEM_RAM_SIZE_BASE_PHYS                                 0x00010000

#define SYS_IMEM_RAM_SIZE_BASE                                      0x00040000
#define SYS_IMEM_RAM_SIZE_BASE_SIZE                                 0x100000000
#define SYS_IMEM_RAM_SIZE_BASE_PHYS                                 0x00040000

#define MPU_NFPB_MPU1032_42_M27L12_AHB_BASE                         0xff00900000uLL
#define MPU_NFPB_MPU1032_42_M27L12_AHB_BASE_SIZE                    0x100000000
#define MPU_NFPB_MPU1032_42_M27L12_AHB_BASE_PHYS                    0xff00900000uLL

#define MPU_WFPB_MPU1032_84_M29L12_AHB_BASE                         0xff00a00000uLL
#define MPU_WFPB_MPU1032_84_M29L12_AHB_BASE_SIZE                    0x100000000
#define MPU_WFPB_MPU1032_84_M29L12_AHB_BASE_PHYS                    0xff00a00000uLL

#define APU_CFG_APU1032_5_BASE                                      0xff00c00000uLL
#define APU_CFG_APU1032_5_BASE_SIZE                                 0x100000000
#define APU_CFG_APU1032_5_BASE_PHYS                                 0xff00c00000uLL

#define FAN_TACH_BASE                                               0xff00d00000uLL
#define FAN_TACH_BASE_SIZE                                          0x100000000
#define FAN_TACH_BASE_PHYS                                          0xff00d00000uLL

#define APU_NFPB_APU1132_1_BASE                                     0xff00e00000uLL
#define APU_NFPB_APU1132_1_BASE_SIZE                                0x100000000
#define APU_NFPB_APU1132_1_BASE_PHYS                                0xff00e00000uLL

#define APU_WFPB_APU1132_1_BASE                                     0xff00f00000uLL
#define APU_WFPB_APU1132_1_BASE_SIZE                                0x100000000
#define APU_WFPB_APU1132_1_BASE_PHYS                                0xff00f00000uLL

#define GCCMW_BASE                                                  0xff01000000uLL
#define GCCMW_BASE_SIZE                                             0x100000000
#define GCCMW_BASE_PHYS                                             0xff01000000uLL

#define TLMM_BASE                                                   0xff02000000uLL
#define TLMM_BASE_SIZE                                              0x100000000
#define TLMM_BASE_PHYS                                              0xff02000000uLL

#define CORE_TOP_CSR_BASE                                           0xff02e00000uLL
#define CORE_TOP_CSR_BASE_SIZE                                      0x100000000
#define CORE_TOP_CSR_BASE_PHYS                                      0xff02e00000uLL

#define HDMA_VBU_HWK0_DMA_REGS_BASE                                 0xff03100000uLL
#define HDMA_VBU_HWK0_DMA_REGS_BASE_SIZE                            0x100000000
#define HDMA_VBU_HWK0_DMA_REGS_BASE_PHYS                            0xff03100000uLL

#define SP0_CM_SERVER_SATA_SW_BASE                                  0xff03600000uLL
#define SP0_CM_SERVER_SATA_SW_BASE_SIZE                             0x100000000
#define SP0_CM_SERVER_SATA_SW_BASE_PHYS                             0xff03600000uLL

#define SP0_A2P_AHB2PHY_SWMAN_BASE                                  0xff03700000uLL
#define SP0_A2P_AHB2PHY_SWMAN_BASE_SIZE                             0x100000000
#define SP0_A2P_AHB2PHY_SWMAN_BASE_PHYS                             0xff03700000uLL

#define SP1_CM_SERVER_SATA_SW_BASE                                  0xff03800000uLL
#define SP1_CM_SERVER_SATA_SW_BASE_SIZE                             0x100000000
#define SP1_CM_SERVER_SATA_SW_BASE_PHYS                             0xff03800000uLL

#define SP1_A2P_AHB2PHY_SWMAN_BASE                                  0xff03900000uLL
#define SP1_A2P_AHB2PHY_SWMAN_BASE_SIZE                             0x100000000
#define SP1_A2P_AHB2PHY_SWMAN_BASE_PHYS                             0xff03900000uLL

#define MPU_SPHY0_MPU1132_7_M20L16_AHB_BASE                         0xff03a00000uLL
#define MPU_SPHY0_MPU1132_7_M20L16_AHB_BASE_SIZE                    0x100000000
#define MPU_SPHY0_MPU1132_7_M20L16_AHB_BASE_PHYS                    0xff03a00000uLL

#define MPU_SPHY1_MPU1132_7_M20L16_AHB_BASE                         0xff03b00000uLL
#define MPU_SPHY1_MPU1132_7_M20L16_AHB_BASE_SIZE                    0x100000000
#define MPU_SPHY1_MPU1132_7_M20L16_AHB_BASE_PHYS                    0xff03b00000uLL

#define SFPB_NORTH1_CFG_BASE                                        0xff03f00000uLL
#define SFPB_NORTH1_CFG_BASE_SIZE                                   0x100000000
#define SFPB_NORTH1_CFG_BASE_PHYS                                   0xff03f00000uLL

#define D2_DDRSS_BASE                                               0xff04000000uLL
#define D2_DDRSS_BASE_SIZE                                          0x100000000
#define D2_DDRSS_BASE_PHYS                                          0xff04000000uLL

#define D3_DDRSS_BASE                                               0xff06000000uLL
#define D3_DDRSS_BASE_SIZE                                          0x100000000
#define D3_DDRSS_BASE_PHYS                                          0xff06000000uLL

#define TS3_TSENS_TOP_BASE                                          0xff08000000uLL
#define TS3_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS3_TSENS_TOP_BASE_PHYS                                     0xff08000000uLL

#define TS4_TSENS_TOP_BASE                                          0xff08100000uLL
#define TS4_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS4_TSENS_TOP_BASE_PHYS                                     0xff08100000uLL

#define N_GCCMS_BASE                                                0xff08200000uLL
#define N_GCCMS_BASE_SIZE                                           0x100000000
#define N_GCCMS_BASE_PHYS                                           0xff08200000uLL

#define VDN_CPR3_BASE                                               0xff08400000uLL
#define VDN_CPR3_BASE_SIZE                                          0x100000000
#define VDN_CPR3_BASE_PHYS                                          0xff08400000uLL

#define TS2_TSENS_TOP_BASE                                          0xff08500000uLL
#define TS2_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS2_TSENS_TOP_BASE_PHYS                                     0xff08500000uLL

#define SATA_VBU_HWK0_SATA_REGS_BASE                                0xff08600000uLL
#define SATA_VBU_HWK0_SATA_REGS_BASE_SIZE                           0x100000000
#define SATA_VBU_HWK0_SATA_REGS_BASE_PHYS                           0xff08600000uLL

#define SFPB_NORTH2_CFG_BASE                                        0xff09f00000uLL
#define SFPB_NORTH2_CFG_BASE_SIZE                                   0x100000000
#define SFPB_NORTH2_CFG_BASE_PHYS                                   0xff09f00000uLL

#define D4_DDRSS_BASE                                               0xff0a000000uLL
#define D4_DDRSS_BASE_SIZE                                          0x100000000
#define D4_DDRSS_BASE_PHYS                                          0xff0a000000uLL

#define TS5_TSENS_TOP_BASE                                          0xff0c100000uLL
#define TS5_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS5_TSENS_TOP_BASE_PHYS                                     0xff0c100000uLL

#define SFPB_WEST_CFG_BASE                                          0xff0c400000uLL
#define SFPB_WEST_CFG_BASE_SIZE                                     0x100000000
#define SFPB_WEST_CFG_BASE_PHYS                                     0xff0c400000uLL

#define SYS_IMEM_BASE                                               0xff0c500000uLL
#define SYS_IMEM_BASE_SIZE                                          0x100000000
#define SYS_IMEM_BASE_PHYS                                          0xff0c500000uLL

#define MSG_IMEM_BASE                                               0xff0c600000uLL
#define MSG_IMEM_BASE_SIZE                                          0x100000000
#define MSG_IMEM_BASE_PHYS                                          0xff0c600000uLL

#define SECURITY_CONTROL_BASE                                       0xff0c700000uLL
#define SECURITY_CONTROL_BASE_SIZE                                  0x100000000
#define SECURITY_CONTROL_BASE_PHYS                                  0xff0c700000uLL

#define QDSS_AMBERWING_BASE                                         0xff10000000uLL
#define QDSS_AMBERWING_BASE_SIZE                                    0x100000000
#define QDSS_AMBERWING_BASE_PHYS                                    0xff10000000uLL

#define SYS_VBU_HWK0_SYSFAB_REGS_BASE                               0xff18a00000uLL
#define SYS_VBU_HWK0_SYSFAB_REGS_BASE_SIZE                          0x100000000
#define SYS_VBU_HWK0_SYSFAB_REGS_BASE_PHYS                          0xff18a00000uLL

#define IMC_QSMMUV3_STS2_1_3_QAD10100_V64P44D64_C16S_F3_BASE        0xff18b00000uLL
#define IMC_QSMMUV3_STS2_1_3_QAD10100_V64P44D64_C16S_F3_BASE_SIZE   0x100000000
#define IMC_QSMMUV3_STS2_1_3_QAD10100_V64P44D64_C16S_F3_BASE_PHYS   0xff18b00000uLL

#define TS1_TSENS_TOP_BASE                                          0xff18c00000uLL
#define TS1_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS1_TSENS_TOP_BASE_PHYS                                     0xff18c00000uLL

#define CM_SGMII_2PORT_SW_BASE                                      0xff18d00000uLL
#define CM_SGMII_2PORT_SW_BASE_SIZE                                 0x100000000
#define CM_SGMII_2PORT_SW_BASE_PHYS                                 0xff18d00000uLL

#define SGMII_A2P_AHB2PHY_SWMAN_BASE                                0xff18d80000uLL
#define SGMII_A2P_AHB2PHY_SWMAN_BASE_SIZE                           0x100000000
#define SGMII_A2P_AHB2PHY_SWMAN_BASE_PHYS                           0xff18d80000uLL

#define SFPB_SOUTH1_CFG_BASE                                        0xff19f00000uLL
#define SFPB_SOUTH1_CFG_BASE_SIZE                                   0x100000000
#define SFPB_SOUTH1_CFG_BASE_PHYS                                   0xff19f00000uLL

#define D1_DDRSS_BASE                                               0xff1a000000uLL
#define D1_DDRSS_BASE_SIZE                                          0x100000000
#define D1_DDRSS_BASE_PHYS                                          0xff1a000000uLL

#define D0_DDRSS_BASE                                               0xff1c000000uLL
#define D0_DDRSS_BASE_SIZE                                          0x100000000
#define D0_DDRSS_BASE_PHYS                                          0xff1c000000uLL

#define TS10_TSENS_TOP_BASE                                         0xff1e000000uLL
#define TS10_TSENS_TOP_BASE_SIZE                                    0x100000000
#define TS10_TSENS_TOP_BASE_PHYS                                    0xff1e000000uLL

#define TS9_TSENS_TOP_BASE                                          0xff1e100000uLL
#define TS9_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS9_TSENS_TOP_BASE_PHYS                                     0xff1e100000uLL

#define VDS_CPR3_BASE                                               0xff1e200000uLL
#define VDS_CPR3_BASE_SIZE                                          0x100000000
#define VDS_CPR3_BASE_PHYS                                          0xff1e200000uLL

#define S_GCCMS_BASE                                                0xff1e400000uLL
#define S_GCCMS_BASE_SIZE                                           0x100000000
#define S_GCCMS_BASE_PHYS                                           0xff1e400000uLL

#define SFPB_SOUTH2_CFG_BASE                                        0xff1ff00000uLL
#define SFPB_SOUTH2_CFG_BASE_SIZE                                   0x100000000
#define SFPB_SOUTH2_CFG_BASE_PHYS                                   0xff1ff00000uLL

#define D5_DDRSS_BASE                                               0xff20000000uLL
#define D5_DDRSS_BASE_SIZE                                          0x100000000
#define D5_DDRSS_BASE_PHYS                                          0xff20000000uLL

#define TS8_TSENS_TOP_BASE                                          0xff22200000uLL
#define TS8_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS8_TSENS_TOP_BASE_PHYS                                     0xff22200000uLL

#define SFPB_SOUTHEAST_CFG_BASE                                     0xff22300000uLL
#define SFPB_SOUTHEAST_CFG_BASE_SIZE                                0x100000000
#define SFPB_SOUTHEAST_CFG_BASE_PHYS                                0xff22300000uLL

#define GCCE_BASE                                                   0xff22400000uLL
#define GCCE_BASE_SIZE                                              0x100000000
#define GCCE_BASE_PHYS                                              0xff22400000uLL

#define TS7_TSENS_TOP_BASE                                          0xff22800000uLL
#define TS7_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS7_TSENS_TOP_BASE_PHYS                                     0xff22800000uLL

#define TS6_TSENS_TOP_BASE                                          0xff22900000uLL
#define TS6_TSENS_TOP_BASE_SIZE                                     0x100000000
#define TS6_TSENS_TOP_BASE_PHYS                                     0xff22900000uLL

#define PCIE0_SFPB_PCIE_SS_BASE                                     0xff22a00000uLL
#define PCIE0_SFPB_PCIE_SS_BASE_SIZE                                0x100000000
#define PCIE0_SFPB_PCIE_SS_BASE_PHYS                                0xff22a00000uLL

#define PCIE0_VBU_HWK0_PCIE_REGS_BASE                               0xff22b00000uLL
#define PCIE0_VBU_HWK0_PCIE_REGS_BASE_SIZE                          0x100000000
#define PCIE0_VBU_HWK0_PCIE_REGS_BASE_PHYS                          0xff22b00000uLL

#define PCIE0_PCIE30_WRAPPER_AHB_BASE                               0xff22c00000uLL
#define PCIE0_PCIE30_WRAPPER_AHB_BASE_SIZE                          0x100000000
#define PCIE0_PCIE30_WRAPPER_AHB_BASE_PHYS                          0xff22c00000uLL

#define PCIE1_PCIE30_WRAPPER_AHB_BASE                               0xff23000000uLL
#define PCIE1_PCIE30_WRAPPER_AHB_BASE_SIZE                          0x100000000
#define PCIE1_PCIE30_WRAPPER_AHB_BASE_PHYS                          0xff23000000uLL

#define PCIE2_PCIE30_WRAPPER_AHB_BASE                               0xff23400000uLL
#define PCIE2_PCIE30_WRAPPER_AHB_BASE_SIZE                          0x100000000
#define PCIE2_PCIE30_WRAPPER_AHB_BASE_PHYS                          0xff23400000uLL

#define PCIE0_PCIE_CC_BASE                                          0xff23800000uLL
#define PCIE0_PCIE_CC_BASE_SIZE                                     0x100000000
#define PCIE0_PCIE_CC_BASE_PHYS                                     0xff23800000uLL

#define PSP0_CM_SERVER_PCIE_SW_BASE                                 0xff23c00000uLL
#define PSP0_CM_SERVER_PCIE_SW_BASE_SIZE                            0x100000000
#define PSP0_CM_SERVER_PCIE_SW_BASE_PHYS                            0xff23c00000uLL

#define PSP0_A2P_AHB2PHY_SWMAN_BASE                                 0xff23c08000uLL
#define PSP0_A2P_AHB2PHY_SWMAN_BASE_SIZE                            0x100000000
#define PSP0_A2P_AHB2PHY_SWMAN_BASE_PHYS                            0xff23c08000uLL

#define PSP1_CM_SERVER_PCIE_SW_BASE                                 0xff23d00000uLL
#define PSP1_CM_SERVER_PCIE_SW_BASE_SIZE                            0x100000000
#define PSP1_CM_SERVER_PCIE_SW_BASE_PHYS                            0xff23d00000uLL

#define PSP1_A2P_AHB2PHY_SWMAN_BASE                                 0xff23d08000uLL
#define PSP1_A2P_AHB2PHY_SWMAN_BASE_SIZE                            0x100000000
#define PSP1_A2P_AHB2PHY_SWMAN_BASE_PHYS                            0xff23d08000uLL

#define PSP2_CM_SERVER_PCIE_SW_BASE                                 0xff23e00000uLL
#define PSP2_CM_SERVER_PCIE_SW_BASE_SIZE                            0x100000000
#define PSP2_CM_SERVER_PCIE_SW_BASE_PHYS                            0xff23e00000uLL

#define PSP2_A2P_AHB2PHY_SWMAN_BASE                                 0xff23e08000uLL
#define PSP2_A2P_AHB2PHY_SWMAN_BASE_SIZE                            0x100000000
#define PSP2_A2P_AHB2PHY_SWMAN_BASE_PHYS                            0xff23e08000uLL

#define PSP3_CM_SERVER_PCIE_SW_BASE                                 0xff23f00000uLL
#define PSP3_CM_SERVER_PCIE_SW_BASE_SIZE                            0x100000000
#define PSP3_CM_SERVER_PCIE_SW_BASE_PHYS                            0xff23f00000uLL

#define PSP3_A2P_AHB2PHY_SWMAN_BASE                                 0xff23f08000uLL
#define PSP3_A2P_AHB2PHY_SWMAN_BASE_SIZE                            0x100000000
#define PSP3_A2P_AHB2PHY_SWMAN_BASE_PHYS                            0xff23f08000uLL

#define PCIE1_VBU_HWK0_PCIE_REGS_BASE                               0xff24300000uLL
#define PCIE1_VBU_HWK0_PCIE_REGS_BASE_SIZE                          0x100000000
#define PCIE1_VBU_HWK0_PCIE_REGS_BASE_PHYS                          0xff24300000uLL

#define PCIE3_PCIE30_WRAPPER_AHB_BASE                               0xff24400000uLL
#define PCIE3_PCIE30_WRAPPER_AHB_BASE_SIZE                          0x100000000
#define PCIE3_PCIE30_WRAPPER_AHB_BASE_PHYS                          0xff24400000uLL

#define PCIE4_PCIE30_WRAPPER_AHB_BASE                               0xff24800000uLL
#define PCIE4_PCIE30_WRAPPER_AHB_BASE_SIZE                          0x100000000
#define PCIE4_PCIE30_WRAPPER_AHB_BASE_PHYS                          0xff24800000uLL

#define PCIE5_PCIE30_WRAPPER_AHB_BASE                               0xff24c00000uLL
#define PCIE5_PCIE30_WRAPPER_AHB_BASE_SIZE                          0x100000000
#define PCIE5_PCIE30_WRAPPER_AHB_BASE_PHYS                          0xff24c00000uLL

#define PCIE1_PCIE_CC_BASE                                          0xff25000000uLL
#define PCIE1_PCIE_CC_BASE_SIZE                                     0x100000000
#define PCIE1_PCIE_CC_BASE_PHYS                                     0xff25000000uLL

#define PSP4_CM_SERVER_PCIE_SW_BASE                                 0xff25400000uLL
#define PSP4_CM_SERVER_PCIE_SW_BASE_SIZE                            0x100000000
#define PSP4_CM_SERVER_PCIE_SW_BASE_PHYS                            0xff25400000uLL

#define PSP4_A2P_AHB2PHY_SWMAN_BASE                                 0xff25408000uLL
#define PSP4_A2P_AHB2PHY_SWMAN_BASE_SIZE                            0x100000000
#define PSP4_A2P_AHB2PHY_SWMAN_BASE_PHYS                            0xff25408000uLL

#define PSP5_CM_SERVER_PCIE_SW_BASE                                 0xff25500000uLL
#define PSP5_CM_SERVER_PCIE_SW_BASE_SIZE                            0x100000000
#define PSP5_CM_SERVER_PCIE_SW_BASE_PHYS                            0xff25500000uLL

#define PSP5_A2P_AHB2PHY_SWMAN_BASE                                 0xff25508000uLL
#define PSP5_A2P_AHB2PHY_SWMAN_BASE_SIZE                            0x100000000
#define PSP5_A2P_AHB2PHY_SWMAN_BASE_PHYS                            0xff25508000uLL

#define PSP6_CM_SERVER_PCIE_SW_BASE                                 0xff25600000uLL
#define PSP6_CM_SERVER_PCIE_SW_BASE_SIZE                            0x100000000
#define PSP6_CM_SERVER_PCIE_SW_BASE_PHYS                            0xff25600000uLL

#define PSP6_A2P_AHB2PHY_SWMAN_BASE                                 0xff25608000uLL
#define PSP6_A2P_AHB2PHY_SWMAN_BASE_SIZE                            0x100000000
#define PSP6_A2P_AHB2PHY_SWMAN_BASE_PHYS                            0xff25608000uLL

#define PSP7_CM_SERVER_PCIE_SW_BASE                                 0xff25700000uLL
#define PSP7_CM_SERVER_PCIE_SW_BASE_SIZE                            0x100000000
#define PSP7_CM_SERVER_PCIE_SW_BASE_PHYS                            0xff25700000uLL

#define PSP7_A2P_AHB2PHY_SWMAN_BASE                                 0xff25708000uLL
#define PSP7_A2P_AHB2PHY_SWMAN_BASE_SIZE                            0x100000000
#define PSP7_A2P_AHB2PHY_SWMAN_BASE_PHYS                            0xff25708000uLL

#define PCIE1_SFPB_PCIE_SS_BASE                                     0xff25b00000uLL
#define PCIE1_SFPB_PCIE_SS_BASE_SIZE                                0x100000000
#define PCIE1_SFPB_PCIE_SS_BASE_PHYS                                0xff25b00000uLL

#define PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_BASE                      0xff25c00000uLL
#define PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_BASE_SIZE                 0x100000000
#define PCIE_CLKGEN_QSERVER_SERDES_CLKGEN_BASE_PHYS                 0xff25c00000uLL

#define PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_BASE                          0xff25c1f000uLL
#define PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_BASE_SIZE                     0x100000000
#define PCIE_CLKGEN_A2P_AHB2PHY_SWMAN_BASE_PHYS                     0xff25c1f000uLL

#define CFG_FABRIC_CFG_AMBERWING_BASE                               0xff26600000uLL
#define CFG_FABRIC_CFG_AMBERWING_BASE_SIZE                          0x100000000
#define CFG_FABRIC_CFG_AMBERWING_BASE_PHYS                          0xff26600000uLL

#define SYS_FABRIC_SYS_AMBERWING_BASE                               0xff26700000uLL
#define SYS_FABRIC_SYS_AMBERWING_BASE_SIZE                          0x100000000
#define SYS_FABRIC_SYS_AMBERWING_BASE_PHYS                          0xff26700000uLL

#define DIG_CPR3_BASE                                               0xff26800000uLL
#define DIG_CPR3_BASE_SIZE                                          0x100000000
#define DIG_CPR3_BASE_PHYS                                          0xff26800000uLL

#define MEM_CPR3_BASE                                               0xff26900000uLL
#define MEM_CPR3_BASE_SIZE                                          0x100000000
#define MEM_CPR3_BASE_PHYS                                          0xff26900000uLL

#define MPM_BASE                                                    0xff26a00000uLL
#define MPM_BASE_SIZE                                               0x100000000
#define MPM_BASE_PHYS                                               0xff26a00000uLL

#define I0_PMIC_ARB_BASE                                            0xff30000000uLL
#define I0_PMIC_ARB_BASE_SIZE                                       0x100000000
#define I0_PMIC_ARB_BASE_PHYS                                       0xff30000000uLL

#define I1_PMIC_ARB_BASE                                            0xff40000000uLL
#define I1_PMIC_ARB_BASE_SIZE                                       0x100000000
#define I1_PMIC_ARB_BASE_PHYS                                       0xff40000000uLL

#define I2_PMIC_ARB_BASE                                            0xff50000000uLL
#define I2_PMIC_ARB_BASE_SIZE                                       0x100000000
#define I2_PMIC_ARB_BASE_PHYS                                       0xff50000000uLL

#define I0_CRYPTO_TOP_BASE                                          0xff60000000uLL
#define I0_CRYPTO_TOP_BASE_SIZE                                     0x100000000
#define I0_CRYPTO_TOP_BASE_PHYS                                     0xff60000000uLL

#define CE0_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F0_BASE     0xff60400000uLL
#define CE0_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F0_BASE_SIZE 0x100000000
#define CE0_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F0_BASE_PHYS 0xff60400000uLL

#define I1_CRYPTO_TOP_BASE                                          0xff60800000uLL
#define I1_CRYPTO_TOP_BASE_SIZE                                     0x100000000
#define I1_CRYPTO_TOP_BASE_PHYS                                     0xff60800000uLL

#define CE1_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F0_BASE     0xff60c00000uLL
#define CE1_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F0_BASE_SIZE 0x100000000
#define CE1_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F0_BASE_PHYS 0xff60c00000uLL

#define I0_EMAC_WRAPPER_BASE                                        0xff61000000uLL
#define I0_EMAC_WRAPPER_BASE_SIZE                                   0x100000000
#define I0_EMAC_WRAPPER_BASE_PHYS                                   0xff61000000uLL

#define GBE0_QSMMUV3_STQS2_1_1_QAD11100_V64P44D64_C16UA_F1_BASE     0xff61400000uLL
#define GBE0_QSMMUV3_STQS2_1_1_QAD11100_V64P44D64_C16UA_F1_BASE_SIZE 0x100000000
#define GBE0_QSMMUV3_STQS2_1_1_QAD11100_V64P44D64_C16UA_F1_BASE_PHYS 0xff61400000uLL

#define I1_EMAC_WRAPPER_BASE                                        0xff61800000uLL
#define I1_EMAC_WRAPPER_BASE_SIZE                                   0x100000000
#define I1_EMAC_WRAPPER_BASE_PHYS                                   0xff61800000uLL

#define GBE1_QSMMUV3_STQS2_1_1_QAD11100_V64P44D64_C16UA_F1_BASE     0xff61c00000uLL
#define GBE1_QSMMUV3_STQS2_1_1_QAD11100_V64P44D64_C16UA_F1_BASE_SIZE 0x100000000
#define GBE1_QSMMUV3_STQS2_1_1_QAD11100_V64P44D64_C16UA_F1_BASE_PHYS 0xff61c00000uLL

#define IMC_BASE                                                    0xff6f800000uLL
#define IMC_BASE_SIZE                                               0x100000000
#define IMC_BASE_PHYS                                               0xff6f800000uLL

#define SYS_IMEM_RAM_START_ADDRESS_BASE                             0xff70000000uLL
#define SYS_IMEM_RAM_START_ADDRESS_BASE_SIZE                        0x100000000
#define SYS_IMEM_RAM_START_ADDRESS_BASE_PHYS                        0xff70000000uLL

#define SYS_IMEM_RAM_END_ADDRESS_BASE                               0xff7003ffffuLL
#define SYS_IMEM_RAM_END_ADDRESS_BASE_SIZE                          0x100000000
#define SYS_IMEM_RAM_END_ADDRESS_BASE_PHYS                          0xff7003ffffuLL

#define MSG_IMEM_RAM_START_ADDRESS_BASE                             0xff70400000uLL
#define MSG_IMEM_RAM_START_ADDRESS_BASE_SIZE                        0x100000000
#define MSG_IMEM_RAM_START_ADDRESS_BASE_PHYS                        0xff70400000uLL

#define MSG_IMEM_RAM_END_ADDRESS_BASE                               0xff7040ffffuLL
#define MSG_IMEM_RAM_END_ADDRESS_BASE_SIZE                          0x100000000
#define MSG_IMEM_RAM_END_ADDRESS_BASE_PHYS                          0xff7040ffffuLL

#define PERIPH_SS_BASE                                              0xff78000000uLL
#define PERIPH_SS_BASE_SIZE                                         0x100000000
#define PERIPH_SS_BASE_PHYS                                         0xff78000000uLL

#define HMSS_PERIPH_BASE                                            0xff7e000000uLL
#define HMSS_PERIPH_BASE_SIZE                                       0x100000000
#define HMSS_PERIPH_BASE_PHYS                                       0xff7e000000uLL

#define HMSS_QGIC_BASE                                              0xff7ef00000uLL
#define HMSS_QGIC_BASE_SIZE                                         0x100000000
#define HMSS_QGIC_BASE_PHYS                                         0xff7ef00000uLL

#define HMSS_QLL_BASE                                               0xff80000000uLL
#define HMSS_QLL_BASE_SIZE                                          0x100000000
#define HMSS_QLL_BASE_PHYS                                          0xff80000000uLL

#define SATA_SS_VBU_TN_BASE                                         0xff88000000uLL
#define SATA_SS_VBU_TN_BASE_SIZE                                    0x100000000
#define SATA_SS_VBU_TN_BASE_PHYS                                    0xff88000000uLL

#define HDMA_SS_VBU_TN_BASE                                         0xff98000000uLL
#define HDMA_SS_VBU_TN_BASE_SIZE                                    0x100000000
#define HDMA_SS_VBU_TN_BASE_PHYS                                    0xff98000000uLL

#define PCIE_B_SIZE_BASE                                            0x40000000000uLL
#define PCIE_B_SIZE_BASE_SIZE                                       0x100000000
#define PCIE_B_SIZE_BASE_PHYS                                       0x40000000000uLL

#define PCIE_A_SIZE_BASE                                            0x40000000000uLL
#define PCIE_A_SIZE_BASE_SIZE                                       0x100000000
#define PCIE_A_SIZE_BASE_PHYS                                       0x40000000000uLL

#define PCIE_A_BASE                                                 0x80000000000uLL
#define PCIE_A_BASE_SIZE                                            0x100000000
#define PCIE_A_BASE_PHYS                                            0x80000000000uLL

#define PCIE_SS_VBU_TN_BASE                                         0x80000000000uLL
#define PCIE_SS_VBU_TN_BASE_SIZE                                    0x100000000
#define PCIE_SS_VBU_TN_BASE_PHYS                                    0x80000000000uLL

#define PCIE_A_END_BASE                                             0xbffffffffffuLL
#define PCIE_A_END_BASE_SIZE                                        0x100000000
#define PCIE_A_END_BASE_PHYS                                        0xbffffffffffuLL

#define PCIE_B_BASE                                                 0xc0000000000uLL
#define PCIE_B_BASE_SIZE                                            0x100000000
#define PCIE_B_BASE_PHYS                                            0xc0000000000uLL

#define PCIE_B_END_BASE                                             0xfffffffffffuLL
#define PCIE_B_END_BASE_SIZE                                        0x100000000
#define PCIE_B_END_BASE_PHYS                                        0xfffffffffffuLL

#endif