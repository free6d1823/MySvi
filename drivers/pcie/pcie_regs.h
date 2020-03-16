/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#ifndef __PCIE_REGS_H__
#define __PCIE_REGS_H__

#define HWIO_PCIE0_PCIE_CC_PCIE_X16_MSTR_AXI_CBCR_ADDR                                (PCIE0_PCIE_CC_REG_REG_BASE      + 0x00120060)
#define HWIO_PCIE0_PCIE_CC_PCIE_X16_SLV_AXI_CBCR_ADDR                                 (PCIE0_PCIE_CC_REG_REG_BASE      + 0x00120064)
#define HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MSTR_AXI_CBCR_ADDR                               (PCIE0_PCIE_CC_REG_REG_BASE      + 0x00100024)
#define HWIO_PCIE0_PCIE_CC_PCIE_X8_0_SLV_AXI_CBCR_ADDR                                (PCIE0_PCIE_CC_REG_REG_BASE      + 0x00100028)
#define HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MSTR_AXI_CBCR_ADDR                               (PCIE0_PCIE_CC_REG_REG_BASE      + 0x00110024)
#define HWIO_PCIE0_PCIE_CC_PCIE_X8_1_SLV_AXI_CBCR_ADDR                                (PCIE0_PCIE_CC_REG_REG_BASE      + 0x00110028)

#define HWIO_PCIE1_PCIE_CC_PCIE_X16_MSTR_AXI_CBCR_ADDR                                (PCIE1_PCIE_CC_REG_REG_BASE      + 0x00120060)
#define HWIO_PCIE1_PCIE_CC_PCIE_X16_SLV_AXI_CBCR_ADDR                                 (PCIE1_PCIE_CC_REG_REG_BASE      + 0x00120064)
#define HWIO_PCIE1_PCIE_CC_PCIE_X8_0_MSTR_AXI_CBCR_ADDR                               (PCIE1_PCIE_CC_REG_REG_BASE      + 0x00100024)
#define HWIO_PCIE1_PCIE_CC_PCIE_X8_0_SLV_AXI_CBCR_ADDR                                (PCIE1_PCIE_CC_REG_REG_BASE      + 0x00100028)
#define HWIO_PCIE1_PCIE_CC_PCIE_X8_1_MSTR_AXI_CBCR_ADDR                               (PCIE1_PCIE_CC_REG_REG_BASE      + 0x00110024)
#define HWIO_PCIE1_PCIE_CC_PCIE_X8_1_SLV_AXI_CBCR_ADDR                                (PCIE1_PCIE_CC_REG_REG_BASE      + 0x00110028)

#define TLMM_PCIESS0_LINK_MODE_2                                                      0xFF02A90000
#define TLMM_PCIESS0_LINK_MODE_1                                                      0xFF02AA0000
#define TLMM_PCIESS0_LINK_MODE_0                                                      0xFF02AB0000
#define TLMM_PCIESS1_LINK_MODE_2                                                      0xFF02AC0000
#define TLMM_PCIESS1_LINK_MODE_1                                                      0xFF02AD0000
#define TLMM_PCIESS1_LINK_MODE_0                                                      0xFF02AE0000

#define PCIE_LANE_REG_BASE_OFFSET                                                     PSP0_QSERVER_L1_QSERVER_L1_PCIE_LANE_REG_BASE_OFFS - PSP0_QSERVER_L0_QSERVER_L0_PCIE_LANE_REG_BASE_OFFS

#endif //__PCIE_REGS_H__
