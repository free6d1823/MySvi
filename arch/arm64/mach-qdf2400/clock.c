#include "clock.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <target/delay.h>
#include <target/cpus.h>
#include <testos.h>
#include <asm/mach/chipinfo.h>
#include <target/clk.h>

/*=========================================================================
      Macro Definitions
==========================================================================*/

/* ---------- */
/*   Server   */
/* ---------- */
#if defined HWIO_GCCMW_WEST_PLL0_MODE_ADDR

  /* Map MSM register names to the corresponding server names. */
  #define GCC_SDCC2_APPS_CMD_RCGR              PCC_SDCC2_APPS_CMD_RCGR
  #define GCC_SDCC2_APPS_CFG_RCGR              PCC_SDCC2_APPS_CFG_RCGR
  #define GCC_SDCC2_APPS_M                     PCC_SDCC2_APPS_M
  #define GCC_SDCC2_APPS_N                     PCC_SDCC2_APPS_N
  #define GCC_SDCC2_APPS_D                     PCC_SDCC2_APPS_D

#endif

static ClockFrequencyPlanType qdf2400_freq_plans[] = {
    // 1.0
    {
        .nChipMajorVersion   = 1,
        .nChipMinorVersion   = 0,
        .pPLLCfg             = &Qdf2400V10PLLCfg[0],
        .pClockBranches      = &Qdf2400V10CBCRs[0],
        .pCdivCfg            = &Qdf2400V10CdivCfg[0],
        .pMuxCfg             = NULL,
        .pRcgCfg             = &Qdf2400V10RcgCfg[0],
    },
    // 1.1
    {
        .nChipMajorVersion   = 1,
        .nChipMinorVersion   = 1,
        .pPLLCfg             = &Qdf2400V11PLLCfg[0],
        .pClockBranches      = &Qdf2400V10CBCRs[0],    // Use 1.0 CBC list
        .pCdivCfg            = &Qdf2400V11CdivCfg[0],
        .pMuxCfg             = NULL,
        .pRcgCfg             = &Qdf2400V11RcgCfg[0],
    },
    // 2.0
    {
        .nChipMajorVersion   = 2,
        .nChipMinorVersion   = 0,
        .pPLLCfg             = &Qdf2400V20PLLCfg[0],
        .pClockBranches      = &Qdf2400V20CBCRs[0],
        .pCdivCfg            = &Qdf2400V20CdivCfg[0],
        .pMuxCfg             = NULL,
        .pRcgCfg             = &Qdf2400V20RcgCfg[0],
    },
};

#define TESTOS_PHASE_PLL(x)	(TESTOS_PHASE_ARCH+(x))
#define TESTOS_PHASE_CLOCK	(TESTOS_PHASE_ARCH+NR_PLLS)
#define TESTOS_PHASE_RCG	(TESTOS_PHASE_CLOCK+1)

bool clock_config_mux(const clk_ctl_cfg *cfg)
{
	if (cfg->flags) {
		__clk_generate_mnd((caddr_t)cfg->cmd_rcgr,
				   cfg->src_sel,
				   cfg->input_hz,
				   cfg->output_hz,
				   RCG_MODE_DUAL_EDGE,
				   _GET_FV(CLK_MND_MASK, cfg->flags));
	} else {
		__clk_generate_hid((caddr_t)cfg->cmd_rcgr,
				   cfg->src_sel,
				   cfg->input_hz,
				   cfg->output_hz,
				   RCG_MODE_BYPASS);
	}
	__clk_update_root(cfg->cmd_rcgr);
	return true;
}

static void __clock_enable_branches(uintptr_t *pCbcrAddrs)
{
    while (pCbcrAddrs && *pCbcrAddrs != 0) {
        outp32(*pCbcrAddrs, 0x1);
        pCbcrAddrs++;
    }
}

static void __clock_config_register(ClockCfgType *pClkCfg)
{
    while (pClkCfg && pClkCfg->nAddr != 0) {
        outp32(pClkCfg->nAddr, pClkCfg->nVal);
        pClkCfg++;
    }
}

static bool __clock_config_rcgs(clk_ctl_cfg *pRcgCfg)
{
	bool success = true;

	while (pRcgCfg && pRcgCfg->cmd_rcgr)
	{
		if (!clock_config_mux(pRcgCfg))
		{
			success = false;
		}
		pRcgCfg++;
	}

	return true;
}


static ClockFrequencyPlanType *
clock_qdf2400_get_frequencies(uint8_t major, uint8_t minor)
{
    int i;
    uint32_t nr_plans;
    ClockFrequencyPlanType *freq_plan = NULL;

    nr_plans = sizeof(qdf2400_freq_plans) / sizeof(qdf2400_freq_plans[0]);
    for (i = 0; i < nr_plans; i++) {
        freq_plan = &qdf2400_freq_plans[i];
        if (major == freq_plan->nChipMajorVersion &&
            minor == freq_plan->nChipMinorVersion)
            return freq_plan;
    }
    return NULL;
}

bool freqplan_apply(uint8_t major, uint8_t minor)
{
#if defined(CONFIG_TESTOS_EMU) || defined(CONFIG_TESTOS_ATE_NOWAIT)
	bool allow_wait = false;
#else
	bool allow_wait = true;
#endif
    ClockFrequencyPlanType *pFreqPlan =
        clock_qdf2400_get_frequencies(major, minor);

    if (!pFreqPlan)
        return false;

    /*
     * Configure clocks in the following order:
     *   1) Configure PLLs
     *   2) Enable clock branches to drive RCG outputs
     *   3) Configure misc
     *   4) Configure RCGs
     */
    if (!fabia_config_plls(pFreqPlan->pPLLCfg, allow_wait))
        return false;
    __clock_enable_branches(pFreqPlan->pClockBranches);
    __clock_config_register(pFreqPlan->pCdivCfg);
    __clock_config_register(pFreqPlan->pMuxCfg);
    if (__clock_config_rcgs(pFreqPlan->pRcgCfg))
        return true;
    else
        return false;
}

void early_clock(void)
{
    /* clock_config_mux should not refer to bss. */
    clock_config_mux(Qdf2400V20RcgCfg + 0); /*IMC CPU*/
    clock_config_mux(Qdf2400V20RcgCfg + 1); /*IMC Fabric & IMEM*/
}
