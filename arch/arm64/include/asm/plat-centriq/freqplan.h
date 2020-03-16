/*
 */
#ifndef __FREQPLAN_CENTRIQ_H_INCLUDE__
#define __FREQPLAN_CENTRIQ_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>
#include <target/compiler.h>

typedef struct clk_pll {
	uintptr_t base;
	uint32_t output_hz;
} __packed clk_pll_cfg;

#define CLK_MND_MASK_OFFSET	0
#define CLK_MND_MASK_MASK	0xFFFF
#define CLK_MND_MASK(value)	_SET_FV(CLK_MND_MASK, value)
#define CLK_MND_MODE_OFFSET	16
#define CLK_MND_MODE_MASK	0xFF
#define CLK_MND_MODE(value)	_SET_FV(CLK_MND_MODE, value)

typedef struct clk_ctl {
	uint8_t src_sel;
	uint32_t input_hz;
	uint32_t output_hz;
	uint64_t cmd_rcgr;
	uint32_t flags;
} __packed clk_ctl_cfg;

typedef struct ClockCfg {
	uintptr_t nAddr;
	uint32_t   nVal;
} __packed ClockCfgType;

typedef struct ClockPLLReg {
	uint32_t nConfigCtlU;
	uint32_t nConfigCtl;
	uint32_t nUserCtlU;
	uint32_t nUserCtl;
	uint32_t nTestCtlU;
	uint32_t nTestCtl;
} __packed ClockPLLRegType;

/* Parameters used for configuring a source that is a PLL.
 * addr  - The address of the PLL MODE register.
 * L     - The L value for the PLL.  The PLL output frequency is deriv
 *         as out_freq = ((in_freq / nPreDiv) * (L + M/N)) / nPostDiv.
 * alpha - The Alpha(prog) value. For the 20nm PLLs, the output freque
 *         derived as :
 *         out_freq = ((in_freq / nPreDiv) * (L + ALPHAfrac)) / nPostD
 *         ALPHAprog = 2^b x ALPHAfrac where 'b' is 40 for Prius and 4
 */
typedef struct ClockConfigPLL {
	uintptr_t nPLLModeAddr;
	uint16_t  nL;
	uint16_t  nAlpha;
	ClockPLLRegType PLLRegs;
} __packed ClockConfigPLLType;

typedef struct ClockFrequencyPlan {
	uint8_t nChipMajorVersion;
	uint8_t nChipMinorVersion;
	uint32_t *pPLLCfg;
	uintptr_t *pClockBranches;
	ClockCfgType *pCdivCfg;
	ClockCfgType *pMuxCfg;
	clk_ctl_cfg *pRcgCfg;
} __packed ClockFrequencyPlanType;

bool freqplan_apply(uint8_t major, uint8_t minor);

#endif /* __FREQPLAN_CENTRIQ_H_INCLUDE__ */
