#ifndef __GCCMW_CENTRIQ_H_INCLUDE__
#define __GCCMW_CENTRIQ_H_INCLUDE__

/* Accepts the clock outputs from pad west_xo, and sleep clk, also
 * accepts SATA/EMAC PHY output clock, generates west side devices'
 * clocks and resets. It also includes a main reset controller,
 * generates source clock for PCC and IMC_CC, and source resets for
 * GCCE, GCCMS, PCC, IMC_CC, PCIE_CC.
 */
#define GCCMW_REG(off)			(GCCMW_BASE + (off))

#define GCCMW_PLL_BLOCK_SHIFT		16
#define GCCMW_PLL_REG(blk, off)		\
	(GCCMW_PLL_BASE + ((blk) << GCCMW_PLL_BLOCK_SHIFT) + (off))

/* West PLLs */
#define GCCMW_WEST_PLL_BASE(blk)	GCCMW_PLL_REG(blk, 0x0000)

#define GCCMW_CC_BLOCK_SHIFT		16
#define GCCMW_CC_REG(blk, off)		\
	(GCCMW_CC_BASE + ((blk) << GCCMW_CC_BLOCK_SHIFT) + (off))

/* CPRC_APCS */
#define GCCMW_CPRC_APCS_BCR		GCCMW_CC_REG(GCCMW_CPRC_APCS, 0x0000)
#define GCCMW_CPRC_APCS_CMD_RCGR	GCCMW_CC_REG(GCCMW_CPRC_APCS, 0x0004)
#define GCCMW_CPRC_APCS_HMSS_CBCR	GCCMW_CC_REG(GCCMW_CPRC_APCS, 0x000C)

/* CTCSR */
#define GCCMW_CTCSR_BCR			GCCMW_CC_REG(GCCMW_CTCSR, 0x0000)
#define GCCMW_CTCSR_AHB_CBCR		GCCMW_CC_REG(GCCMW_CTCSR, 0x0004)

/* MPM */
#define GCCMW_MPM_BCR			GCCMW_CC_REG(GCCMW_MPM, 0x0000)
#define GCCMW_MPM_AHB_CBCR		GCCMW_CC_REG(GCCMW_MPM, 0x0004)

/* MSG_RAM */
#define GCCMW_MSG_RAM_BCR		GCCMW_CC_REG(GCCMW_MSG_RAM, 0x0000)
#define GCCMW_MSG_RAM_CFG_AHB_CBCR	GCCMW_CC_REG(GCCMW_MSG_RAM, 0x0004)
#define GCCMW_MSG_RAM_AXI_CBCR		GCCMW_CC_REG(GCCMW_MSG_RAM, 0x0008)

/* TSENS */
#define GCCMW_TSENS_BCR(blk)		GCCMW_CC_REG(blk, 0x0000)
#define GCCMW_TSENS_AHB_CBCR(blk)	GCCMW_CC_REG(blk, 0x0004)
#define GCCMW_TSENS_EXT_CBCR(blk)	GCCMW_CC_REG(blk, 0x0008)
#define GCCMW_TSENS_SLEEP_CBCR(blk)	GCCMW_CC_REG(blk, 0x000C)

#endif /* __GCCMW_CENTRIQ_H_INCLUDE__ */
