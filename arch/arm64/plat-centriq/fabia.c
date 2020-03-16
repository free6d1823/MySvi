/*
 */
#include <asm/mach/hal/HALclkHWIO.h>
#include <stdbool.h>
#include <target/delay.h>
#include <target/clock.h>
#include <target/clk.h>
#include <asm/hal/HALhwio.h>

/* PLL lock timeout (2x max locking time) */
#define CLOCK_PLL_LOCK_TIMEOUT_US	200

/* Warm-up time in microseconds after turning on the PLL */
#define CLOCK_PLL_WARMUP_TIME_US	25

/* Definitions for configuring the PLL in FSM Mode */
#define CLOCK_PLL_BIAS_COUNT_VAL	\
	(0x6 << HWIO_SHFT(GCC_GPLL0_MODE, PLL_BIAS_COUNT))
#define CLOCK_PLL_LOCK_COUNT_VAL	\
	(0x0 << HWIO_SHFT(GCC_GPLL0_MODE, PLL_LOCK_COUNT))

#define GCC_INPUT_FREQ_MHZ		20
#define GCC_IS_EAST_PLL(pll)		((pll) & 0x02)

/* Fabia PLL definitions (GPLL0 is Fabia type in 8998). */
#define FABIA_REG_BASE(pll)		fabia_plls[pll].base
#define FABIA_REG_OFFSET(reg)		\
	(HWIO_ADDR(GCCMW_WEST_PLL0_##reg) - GCCMW_BASE)
#define FABIA_REG_PLL_MODE(pll)		\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(MODE))
#define FABIA_REG_PLL_USER_CTL(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(USER_CTL))
#define FABIA_REG_PLL_USER_CTL_U(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(USER_CTL_U))
#define FABIA_REG_PLL_CONFIG_CTL(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(CONFIG_CTL))
#define FABIA_REG_PLL_CONFIG_CTL_U(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(CONFIG_CTL_U))
#define FABIA_REG_PLL_TEST_CTL(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(TEST_CTL))
#define FABIA_REG_PLL_TEST_CTL_U(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(TEST_CTL_U))
#define FABIA_REG_PLL_OPMODE(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(OPMODE))
#define FABIA_REG_PLL_CAL_L_VAL(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(CAL_L_VAL))
#define FABIA_REG_PLL_L_VAL(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(L_VAL))
#define FABIA_REG_PLL_FRAC_VAL(pll)	\
	(FABIA_REG_BASE(pll) + FABIA_REG_OFFSET(FRAC_VAL))

#define FABIA_PLL_OPMODE_STANDBY	0x0
#define FABIA_PLL_OPMODE_RUN		0x1
#define FABIA_PLL_OPMODE_FREEZE		0x3

#define FABIA_PLL_CALIB_MODE_ALWAYS	0x0
#define FABIA_PLL_CALIB_MODE_NEVER	0x1
#define FABIA_PLL_CALIB_MODE_AUTOMATIC	0x2

#define FABIA_PLL_FRAC_MODE_ALPHA	0x0
#define FABIA_PLL_FRAC_MODE_M_OVER_N	0x1

#define FABIA_PLL_M_N_FRAC(nM, nN)	\
	((((uint8_t)(nM)) << 8) | ((uint8_t)(nN)))

#define FABIA_PLL_MODE_ENABLED		\
	(HWIO_FMSK(GCCMW_WEST_PLL0_MODE, PLL_OUTCTRL) | \
	 HWIO_FMSK(GCCMW_WEST_PLL0_MODE, PLL_RESET_N))

#define FABIA_PLL_IS_ENABLED(nModeVal)	\
	CLK_BITS_AND(nModeVal, FABIA_PLL_MODE_ENABLED)

/*  nPreDiv  - The pre-divider value (generally 1 or 2).
 *  nPostDiv - The post-divider value (TODO: split into eve/odd for Fabia).
 *  nL       - The L value for the PLL.  The PLL output frequency is
 *             derived as:
 *             out_freq = ((in_freq / nPreDiv) * (L + M/N)) / nPostDiv
 *  nM       - The M value (see above).
 *  nN       - The N value (see above).
 *  nAlpha   - The Alpha(prog) value. For the 20nm PLLs, the output
 *             frequency is derived as :
 *             out_freq = ((in_freq / nPreDiv) * (L + ALPHAfrac)) / nPostDiv
 *             ALPHAprog = 2^b x ALPHAfrac
 *             where 'b' is 40 for Prius and 40 for Tesla.
 */
struct fabia_pll {
	uint64_t base;
	uint32_t mhz;
	int refcnt;
};

struct fabia_pll fabia_plls[NR_PLLS] = {
	/* west_pll0        [1000.000MHz] */
	{
		.base        = HWIO_GCCMW_WEST_PLL0_MODE_ADDR,
		.mhz         = 1000,
	},
	/* west_pll1        [ 800.000MHz] */
	{
		.base        = HWIO_GCCMW_WEST_PLL1_MODE_ADDR,
		.mhz         = 800,
	},
	/* east_pll0        [2000.000MHz] */
	{
		.base        = HWIO_GCCE_EAST_PLL0_MODE_ADDR,
		.mhz         = 2000,
	},
	/* east_pll1        [2000.000MHz] */
	{
		.base        = HWIO_GCCE_EAST_PLL1_MODE_ADDR,
		.mhz         = 2000,
	},
};

static bool fabia_enable_pll(int pll, uint32_t mhz, bool allow_wait)
{
	uint64_t nModeAddr;
	uint32_t nModeVal, nUserCtlVal;
	uint16_t L;
	uint32_t nTimeout = 0;

	nModeAddr = FABIA_REG_PLL_MODE(pll);
	nModeVal  = inp32(nModeAddr);

	/* Return if the PLL is manually enabled. */
	if (FABIA_PLL_IS_ENABLED(nModeVal))
		return true;

	/* Update PLL configuration */
	outp32(FABIA_REG_PLL_CONFIG_CTL_U(pll),0x2067);
	outp32(FABIA_REG_PLL_CONFIG_CTL(pll), 0x20485699);
	if (GCC_IS_EAST_PLL(pll)) {
		outp32(FABIA_REG_PLL_TEST_CTL_U(pll), 0x10000018);
		outp32(FABIA_REG_PLL_USER_CTL(pll), 0x3117);
	} else {
		outp32(FABIA_REG_PLL_TEST_CTL_U(pll), 0x0);
		outp32(FABIA_REG_PLL_USER_CTL(pll), 0x17);
	}
	outp32(FABIA_REG_PLL_TEST_CTL(pll), 0x40000000);
	outp32(FABIA_REG_PLL_USER_CTL_U(pll), 0x6804);

	/* Configure the PLL (if not in FSM mode). */
	if (0 ==
	    (nModeVal & HWIO_FMSK(GCCMW_WEST_PLL0_MODE, PLL_VOTE_FSM_ENA))) {
		/* Program L and CAL_L. */
		L = mhz / GCC_INPUT_FREQ_MHZ;
		outp32(FABIA_REG_PLL_L_VAL(pll), L);
		outp32(FABIA_REG_PLL_CAL_L_VAL(pll), L);
	}

	/* No voting register--follow the manual PLL enable sequence. */
	outp32(FABIA_REG_PLL_OPMODE(pll), 0);

	/* Assert the reset_n field to put the PLL in standby state. */
	nModeVal = (inp32(nModeAddr) |
		   HWIO_FMSK(GCCMW_WEST_PLL0_MODE, PLL_RESET_N));
	outp32(nModeAddr, nModeVal);

	/* Set OPMODE to run state. */
	outp32(FABIA_REG_PLL_OPMODE(pll), FABIA_PLL_OPMODE_RUN);
	udelay(CLOCK_PLL_WARMUP_TIME_US);

	/* Wait for the PLL to lock within the given timeout
	 * period.
	 */
	if (allow_wait) {
		while (CLK_BITS_NOR(inp32(nModeAddr),
				    HWIO_FMSK(GCCMW_WEST_PLL0_MODE, PLL_LOCK_DET))) {
			if (nTimeout++ >= CLOCK_PLL_LOCK_TIMEOUT_US)
				return false;
			udelay(1);
		}
	} else {
		udelay(CLOCK_PLL_LOCK_TIMEOUT_US);
	}

	/* Enable PLLOUT_MAIN. */
	nUserCtlVal = inp32(FABIA_REG_PLL_USER_CTL(pll));
	nUserCtlVal |= HWIO_FMSK(GCCMW_WEST_PLL0_USER_CTL, PLLOUT_MAIN);
	outp32(FABIA_REG_PLL_USER_CTL(pll), nUserCtlVal);

	/* Assert the PLL Output control bit. */
	nModeVal |= HWIO_FMSK(GCCMW_WEST_PLL0_MODE, PLL_OUTCTRL);
	outp32(nModeAddr, nModeVal);

	return true;
}

#if 0
static bool fabia_disable_pll(int pll)
{
	uint64_t nModeAddr;
	uint32_t nModeVal;

	/* Read current mode value. */
	nModeAddr = FABIA_REG_PLL_MODE(pll);
	nModeVal  = inp32(nModeAddr);

	/* De-assert the OUTCTL field. */
	nModeVal &= ~HWIO_FMSK(GCCMW_WEST_PLL0_MODE, PLL_OUTCTRL);
	outp32(nModeAddr, nModeVal);

	/* Wait 2 ticks of the output main clock. */
	udelay(1);

	/* Put the PLL in reset mode. */
	nModeVal &= ~HWIO_FMSK(GCCMW_WEST_PLL0_MODE, PLL_RESET_N);
	outp32(nModeAddr, nModeVal);

	/* Set OPMODE to standby state. */
	outp32(FABIA_REG_PLL_OPMODE(pll), FABIA_PLL_OPMODE_STANDBY);
	return true;
}
#endif

bool fabia_config_plls(uint32_t *freq_mhz, bool allow_wait)
{
	bool success = true;
	int i = 0;

	for (i = 0; i < NR_PLLS; i++) {
		if (!fabia_enable_pll(i, freq_mhz[i], allow_wait))
			success = false;
	}
	return success;
}
