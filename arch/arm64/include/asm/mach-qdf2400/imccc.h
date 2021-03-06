/* QDF2400 IMC_CC (IMC Clock Controller) driver
 */
#ifndef __IMCCC_QDF2400_H_INCLUDE__
#define __IMCCC_QDF2400_H_INCLUDE__

#define IMC_CC_BASE			ULL(0x0FF6FC40000)

/* SYS */
#define IMC_CC_SYS			0
#define IMC_CC_IMC_POSTDIV_CDIVR	IMC_CC_REG(IMC_CC_SYS, 0x0000)
#define IMC_CC_IMC_CMD_RCGR		IMC_CC_REG(IMC_CC_SYS, 0x0004)
#define IMC_CC_IMC_PROC_CMD_RCGR	IMC_CC_REG(IMC_CC_SYS, 0x000C)
#define IMC_CC_IMC_AXI_BRDG_PROC_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0014)
#define IMC_CC_IMC_DBG_BRDG_PROC_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0018)
#define IMC_CC_IMC_PROC_AXI_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x001C)
#define IMC_CC_IMC_S0_AHB_CBCR		IMC_CC_REG(IMC_CC_SYS, 0x0020)
#define IMC_CC_IMC_S1_AHB_CBCR		IMC_CC_REG(IMC_CC_SYS, 0x0024)
#define IMC_CC_IMCFAB_SFAB_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0028)
#define IMC_CC_IMCFAB_RAM0_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x002C)
#define IMC_CC_IMCFAB_RAM1_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0030)
#define IMC_CC_IMCFAB_CORE_CBCR		IMC_CC_REG(IMC_CC_SYS, 0x0034)
#define IMC_CC_IMCFAB_RAM2_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0038)
#define IMC_CC_IMCFAB_S0_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x003C)
#define IMC_CC_IMCFAB_S1_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0040)
#define IMC_CC_SFVBU_IMC_DVM_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0044)
#define IMC_CC_IMC_RAM0_AXI_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0048)
#define IMC_CC_IMC_RAM1_AXI_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x004C)
#define IMC_CC_IMC_RAM2_AXI_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0050)
#define IMC_CC_IMC_IOMMU_AXI_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0054)
#define IMC_CC_IMC_PROC_CBCR		IMC_CC_REG(IMC_CC_SYS, 0x0058)
#define IMC_CC_IMCFAB_RAM3_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x005C)
#define IMC_CC_IMCFAB_RAM4_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0060)
#define IMC_CC_IMCFAB_RAM5_FCLK_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0064)
#define IMC_CC_IMC_RAM3_AXI_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0068)
#define IMC_CC_IMC_RAM4_AXI_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x006C)
#define IMC_CC_IMC_RAM5_AXI_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0070)
#define IMC_CC_IMC_QSMMUV3_CLIENT_CBCR	IMC_CC_REG(IMC_CC_SYS, 0x0074)
#define IMC_CC_IMC_WARM_RESET_STATUS	IMC_CC_REG(IMC_CC_SYS, 0x0200)

/* MISC */
#define IMC_CC_MISC			1
/* DEBUG */
#define IMC_CC_DEBUG			2

#include <asm/plat-centriq/imccc.h>

#endif /* __IMCCC_QDF2400_H_INCLUDE__ */
