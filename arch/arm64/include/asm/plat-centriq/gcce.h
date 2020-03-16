#ifndef __GCCE_CENTRIQ_H_INCLUDE__
#define __GCCE_CENTRIQ_H_INCLUDE__

/* Accepts the clock outputs from pad west_xo, and sleep clk, also
 * accepts SATA/EMAC PHY output clock, generates west side devices'
 * clocks and resets. It also includes a main reset controller,
 * generates source clock for PCC and IMC_CC, and source resets for
 * GCCE, GCCMS, PCC, IMC_CC, PCIE_CC.
*/

#define GCCE_REG(off)			(GCCE_BASE + (off))

#define GCCE_PLL_BLOCK_SHIFT		16
#define GCCE_PLL_REG(blk, off)		\
	(GCCE_PLL_BASE + ((blk) << GCCE_PLL_BLOCK_SHIFT) + (off))

/* East PLLs */
#define GCCE_EAST_PLL_BASE(blk)		GCCE_PLL_REG(blk, 0x0000)

#define GCCE_CC_BLOCK_SHIFT		16
#define GCCE_CC_REG(blk, off)		\
	(GCCE_CC_BASE + ((blk) << GCCE_CC_BLOCK_SHIFT) + (off))

/* TSENS */
#define GCCE_TSENS_BCR(blk)		GCCE_CC_REG(blk, 0x0000)
#define GCCE_TSENS_AHB_CBCR(blk)	GCCE_CC_REG(blk, 0x0004)
#define GCCE_TSENS_EXT_CBCR(blk)	GCCE_CC_REG(blk, 0x0008)
#define GCCE_TSENS_SLEEP_CBCR(blk)	GCCE_CC_REG(blk, 0x000C)

#endif /*__GCCE_CENTRIQ_H_INCLUDE__ */
