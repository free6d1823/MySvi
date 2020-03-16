/* Centriq IMC_CC (IMC Clock Controller) driver
 */
#ifndef __IMCCC_CENTRIQ_H_INCLUDE__
#define __IMCCC_CENTRIQ_H_INCLUDE__

/* Accepts the clock outputs from GCCMW, generates the clocks
 * and the resets for the IMC hard macro.
 * It maintains 4 clock groups:
 * 1. 500MHz clock group for IMC core.
 * 2. 333MHz clock group for IMC SoC.
 * 3. 100MHz clock group for west cfg SFPB.
 * 4. 250MHz clock group for debug AJU IMC.
 */
#define IMC_CC_BLOCK_SHIFT		16
#define IMC_CC_REG(blk, off)		\
	(IMC_CC_BASE + ((blk) << IMC_CC_BLOCK_SHIFT) + (off))

/* MISC */
#define IMC_CC_IM_SLEEP_CBCR			IMC_CC_REG(IMC_CC_MISC, 0x0000)
#define IMC_CC_IMC_SLEEP_CBCR			IMC_CC_REG(IMC_CC_MISC, 0x0004)
#define IMC_CC_IMC_XO_CBCR			IMC_CC_REG(IMC_CC_MISC, 0x0008)
#define IMC_CC_IMCFAB_BOOT_ROM_FCLK_CBCR	IMC_CC_REG(IMC_CC_MISC, 0x000C)
#define IMC_CC_BOOT_ROM_AHB_CBCR		IMC_CC_REG(IMC_CC_MISC, 0x0010)
#define IMC_CC_IMC_RESETR			IMC_CC_REG(IMC_CC_MISC, 0x0100)
#define IMC_CC_USE_SLEEP_RET_EN			IMC_CC_REG(IMC_CC_MISC, 0x0200)

/* DEBUG */
#define IMC_CC_DEBUG_CLK_CTL		IMC_CC_REG(IMC_CC_DEBUG, 0x0000)
#define IMC_CC_DEBUG_CDIVR		IMC_CC_REG(IMC_CC_DEBUG, 0x0004)

#endif /* __IMCCC_CENTRIQ_H_INCLUDE__ */
