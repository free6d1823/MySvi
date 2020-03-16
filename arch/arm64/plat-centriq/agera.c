/*
 */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <target/delay.h>
#include <target/cpus.h>
#include <target/clock.h>
#include <target/arch.h>
#include <target/cmdline.h>
#include <asm/hal/HALhwio.h>
#include <asm/mach/hal/HALclkHWIO.h>
#include <asm/mach/chipinfo.h>

#define CBF_MODE_OFFSET(x)    (HWIO_ADDR(APCS_HPLL_##x) - HWIO_ADDR(APCS_HPLL_PLL_MODE))
#define MODE_OFFSET(x)        (HWIO_ADDR(APCS_APC00_##x) - HWIO_ADDR(APCS_APC00_PLL_MODE))
#define MHZ_TO_LVAL(x)        ((x) / 20)

/* CBF PLL main output */
#define CBF_CLKSEL_MASK       0xF
#define CBF_CLKSEL_VAL        0x1

/* CBF Pulse Swallower safe L val */
#define CBF_PS_SAFE_FREQ_MHZ  600
#define CBF_PS_SAFE_L_VAL     MHZ_TO_LVAL(CBF_PS_SAFE_FREQ_MHZ)

/* PLL main output */
#define APCS_CLKSEL_MASK      0xF0F
#define APCS_CLKSEL_EARLY     0xD0D
#define APCS_CLKSEL_MAIN      0x404
#define APCS_AON_MASK         0x30
#define APCS_AON_VAL          0x30

/* APCS PLL settings */
#define AGERA_CFG_CTL_HI 0x000003D2
#define AGERA_CFG_CTL_LO 0x20000AA8
#define AGERA_TST_CTL_HI 0x00004000
#define AGERA_TST_CTL_LO 0x04000400
#define AGERA_USR_CTL_V1 0x00000009
#define AGERA_USR_CTL_V2 0x00000089

static const uintptr_t nADDR_CLKSEL[24] = {
    HWIO_ADDR(APCS_APC00_CLKSEL),
    HWIO_ADDR(APCS_APC01_CLKSEL),
    HWIO_ADDR(APCS_APC02_CLKSEL),
    HWIO_ADDR(APCS_APC03_CLKSEL),
    HWIO_ADDR(APCS_APC04_CLKSEL),
    HWIO_ADDR(APCS_APC05_CLKSEL),
    HWIO_ADDR(APCS_APC06_CLKSEL),
    HWIO_ADDR(APCS_APC07_CLKSEL),
    HWIO_ADDR(APCS_APC08_CLKSEL),
    HWIO_ADDR(APCS_APC09_CLKSEL),
    HWIO_ADDR(APCS_APC10_CLKSEL),
    HWIO_ADDR(APCS_APC11_CLKSEL),
    HWIO_ADDR(APCS_APC12_CLKSEL),
    HWIO_ADDR(APCS_APC13_CLKSEL),
    HWIO_ADDR(APCS_APC14_CLKSEL),
    HWIO_ADDR(APCS_APC15_CLKSEL),
    HWIO_ADDR(APCS_APC16_CLKSEL),
    HWIO_ADDR(APCS_APC17_CLKSEL),
    HWIO_ADDR(APCS_APC18_CLKSEL),
    HWIO_ADDR(APCS_APC19_CLKSEL),
    HWIO_ADDR(APCS_APC20_CLKSEL),
    HWIO_ADDR(APCS_APC21_CLKSEL),
    HWIO_ADDR(APCS_APC22_CLKSEL),
    HWIO_ADDR(APCS_APC23_CLKSEL),
};

static const uintptr_t nADDR_PLL_MODE[24] = {
    HWIO_ADDR(APCS_APC00_PLL_MODE),
    HWIO_ADDR(APCS_APC01_PLL_MODE),
    HWIO_ADDR(APCS_APC02_PLL_MODE),
    HWIO_ADDR(APCS_APC03_PLL_MODE),
    HWIO_ADDR(APCS_APC04_PLL_MODE),
    HWIO_ADDR(APCS_APC05_PLL_MODE),
    HWIO_ADDR(APCS_APC06_PLL_MODE),
    HWIO_ADDR(APCS_APC07_PLL_MODE),
    HWIO_ADDR(APCS_APC08_PLL_MODE),
    HWIO_ADDR(APCS_APC09_PLL_MODE),
    HWIO_ADDR(APCS_APC10_PLL_MODE),
    HWIO_ADDR(APCS_APC11_PLL_MODE),
    HWIO_ADDR(APCS_APC12_PLL_MODE),
    HWIO_ADDR(APCS_APC13_PLL_MODE),
    HWIO_ADDR(APCS_APC14_PLL_MODE),
    HWIO_ADDR(APCS_APC15_PLL_MODE),
    HWIO_ADDR(APCS_APC16_PLL_MODE),
    HWIO_ADDR(APCS_APC17_PLL_MODE),
    HWIO_ADDR(APCS_APC18_PLL_MODE),
    HWIO_ADDR(APCS_APC19_PLL_MODE),
    HWIO_ADDR(APCS_APC20_PLL_MODE),
    HWIO_ADDR(APCS_APC21_PLL_MODE),
    HWIO_ADDR(APCS_APC22_PLL_MODE),
    HWIO_ADDR(APCS_APC23_PLL_MODE),
};

/*
 * Workaround RUMI issue where the PCFSM locks up when exiting certain
 * low power states.
 */
static void clock_enable_apcs_pll_rumi(uintptr_t mode_addr)
{
    DIEINFO_PROPS DieInfo;

    get_socket_info(&DieInfo, 0);
    if (DieInfo.SocType != SOCINFO_SOCTYPE_SILICON)
    {
        /* UNLOCK_CNT_2 = LOCK_CNT_5 = 1 */
        outp32(mode_addr + MODE_OFFSET(HW_DCVS_CTL), 0x10100);
    }
}

static bool clock_enable_apcs_pll(uintptr_t mode_addr,
				  const struct agera_pll_regs *regs)
{
    uint32_t mode_val, timeout = 0;

    if (regs == NULL || mode_addr == 0)
    {
        return false;
    }

    mode_val = inp32(mode_addr);

    /* The PLL is already enabled, it cannot be reconfigured */
    if ((mode_val & HWIO_FMSK(APCS_APC00_PLL_MODE, OUTCTRL)) != 0)
        return false;

    /* Configure AUX clock */
    outp32(mode_addr + MODE_OFFSET(AUX_CBCR), 0x20002);

    /*
     * Enable ACS and SCS
     * HPSS HPG Section 7.2.2
     */

    /* Enable Soft Stop/Start */
    outp32(mode_addr + MODE_OFFSET(SSSCTL), 0x0007);
    /* Clock Halt Exit Control */
    outp32(mode_addr + MODE_OFFSET(CLKHALT_EXIT_CTL), 0x01F1);
    /* Pulse Swallower Config */
    outp32(mode_addr + MODE_OFFSET(PSCTL), 0x20005);

    /*
     * Configure the PLL.
     */

    /* Updates from HSR  */
    outp32(mode_addr + MODE_OFFSET(PLL_CONFIG_CTL_HI), regs->config_ctl_hi);
    outp32(mode_addr + MODE_OFFSET(PLL_CONFIG_CTL_LO), regs->config_ctl_lo);
    outp32(mode_addr + MODE_OFFSET(PLL_USER_CTL), regs->user_ctl);
    outp32(mode_addr + MODE_OFFSET(PLL_TEST_CTL_HI), regs->test_ctl_hi);
    outp32(mode_addr + MODE_OFFSET(PLL_TEST_CTL_LO), regs->test_ctl_lo);

    /* Program frequency */
    outp32(mode_addr + MODE_OFFSET(PLL_L_VAL), regs->l);
    outp32(mode_addr + MODE_OFFSET(PLL_ALPHA_VAL), regs->alpha);
    while (inp32(mode_addr + MODE_OFFSET(PLL_L_VAL_STATUS)) != regs->l) {
        udelay(1);
        timeout++;
        if (timeout > 300)
            return false;
    }

    /*
     * Bring PLL up in HW mode
     */
    /* BIAS_CNT=7; LOCK_CNT=0; FSM_EN=1 */
    outp32(mode_addr, 0x0011C000);
    clock_enable_apcs_pll_rumi(mode_addr);
    return true;
}

static bool __clock_get_pll_config(struct agera_pll_regs *regs,
                                   uint32_t *nSrcSelect,
                                   uint32_t apc,
                                   uint32_t freq_mhz)
{
    DIEINFO_PROPS DieInfo;

    if (regs == NULL || apc >= MAX_CPU_CLUSTERS || nSrcSelect == NULL)
        return false;

    memset(regs , 0, sizeof(*regs));
    regs->l = MHZ_TO_LVAL(freq_mhz);

    /* Default configuration */
    regs->config_ctl_hi = AGERA_CFG_CTL_HI;
    regs->config_ctl_lo = AGERA_CFG_CTL_LO;
    regs->test_ctl_hi = AGERA_TST_CTL_HI;
    regs->test_ctl_lo = AGERA_TST_CTL_LO;
    get_socket_info(&DieInfo, 0);
    if (DieInfo.MajorVersion == 1) {
        regs->user_ctl = AGERA_USR_CTL_V1;
        *nSrcSelect = APCS_CLKSEL_EARLY;
    } else {
        regs->user_ctl = AGERA_USR_CTL_V2;
        *nSrcSelect = APCS_CLKSEL_MAIN;
    }

    qdf2400_fuse_apply_clock_settings(regs, apc);
    return true;
}

bool clock_config_cluster(uint8_t apc, uint32_t freq_mhz)
{
    struct agera_pll_regs regs = {0};
    uintptr_t nAppsCLKSELAddr;
    uint32_t nAppsCLKSELVal;
    uint32_t nSrcSelect;

    /* Bounds check on the cluster is in the register array */
    if (apc >= sizeof(nADDR_CLKSEL) / sizeof(nADDR_CLKSEL[0]))
        return false;

    nAppsCLKSELAddr = nADDR_CLKSEL[apc];

    /* Get PLL config */
    if (!__clock_get_pll_config(&regs, &nSrcSelect, apc, freq_mhz))
        return false;

    /* Enable the high speed PLL */
    if (!clock_enable_apcs_pll(nADDR_PLL_MODE[apc], &regs))
        return false;

    /* Select the high speed PLL and program AON source */
    nAppsCLKSELVal = inp32(nAppsCLKSELAddr);
    nAppsCLKSELVal &= ~(APCS_CLKSEL_MASK | APCS_AON_MASK);
    if (!qdf2400_fuse_override_clock_mux(&nAppsCLKSELVal))
        nAppsCLKSELVal |= nSrcSelect;
    nAppsCLKSELVal |= APCS_AON_VAL;
    outp32(nAppsCLKSELAddr, nAppsCLKSELVal);
    return true;
}

static bool __clock_configure_cbf_pll(uintptr_t mode_addr, uint16_t L)
{
    uint32_t mode_val;

    if (mode_addr == 0)
        return false;

    mode_val = inp32(mode_addr);

    /*
     * Configure PLL frequency.
     */
    outp32(mode_addr + CBF_MODE_OFFSET(PLL_L_VAL), L);

    /*
     * Enable the PLL output if it hasn't already been. Also assume that
     * PLL config registers need to be programmed here as well.
     */
    if ((mode_val & HWIO_FMSK(APCS_HPLL_PLL_MODE, OUTCTRL)) == 0) {
        /* CBF settings match APCS v1 settings */
        outp32(mode_addr + CBF_MODE_OFFSET(PLL_CONFIG_CTL_HI),
               AGERA_CFG_CTL_HI);
        outp32(mode_addr + CBF_MODE_OFFSET(PLL_CONFIG_CTL_LO),
               AGERA_CFG_CTL_LO);
        outp32(mode_addr + CBF_MODE_OFFSET(PLL_TEST_CTL_HI),
               AGERA_TST_CTL_HI);
        outp32(mode_addr + CBF_MODE_OFFSET(PLL_TEST_CTL_LO),
               AGERA_TST_CTL_LO);

        outp32(mode_addr, 0x2);
        udelay(5);
        outp32(mode_addr, 0x6);
        udelay(50);
        outp32(mode_addr, 0x7);
    }

    return true;
}

bool clock_config_cbf(uint32_t freq_mhz)
{
    uintptr_t nPLLModeAddr;
    uintptr_t nCBFCLKSELAddr;

    /* HWIO_APCS_HPLL_PLL_MODE_ADDR   FF7E800000 */
    nPLLModeAddr = HWIO_ADDR(APCS_HPLL_PLL_MODE);
    /* APCS_HPLL_CBF_GFMUX_CTL */
    nCBFCLKSELAddr = nPLLModeAddr + CBF_MODE_OFFSET(CBF_GFMUX_CTL);

    /*
     * Configure the pulse swallower as per HPG 7.5.
     * The PS is used to to ramp the CBF clock on and off when switching
     * the GFMUX and during idle entry/exit.
     */
    /* HWIO_APCS_HPLL_PSCTL_ADDR
     *   APCS_HPLL_PSCTL 0x30446  0011 0000 0100 0100 0110
     */
    outp32(nPLLModeAddr + CBF_MODE_OFFSET(PSCTL), 0x30446);

    /*
     * First configure the CBF PLL to the max frequency
     * that the PSC can safely swallow.
     */
    if (!__clock_configure_cbf_pll(nPLLModeAddr, CBF_PS_SAFE_L_VAL))
        return false;

    /*
     * Enable SSWEN
     */
    out_dword_masked_ns(nPLLModeAddr + CBF_MODE_OFFSET(SSS_CTL),
                        HWIO_APCS_HPLL_SSS_CTL_SSWEN_BMSK,
                        1 << HWIO_APCS_HPLL_SSS_CTL_SSWEN_SHFT,
                        in_dword(nPLLModeAddr + CBF_MODE_OFFSET(SSS_CTL)));

    /* Select the high speed PLL */
    out_dword_masked_ns(nCBFCLKSELAddr, CBF_CLKSEL_MASK, CBF_CLKSEL_VAL,
                        in_dword(nCBFCLKSELAddr));

    /*
     * Wait 50us for PSC_OFF to set
     */
    udelay(50);

    /*
     * Slew to the final frequency.
     */
    return __clock_configure_cbf_pll(nPLLModeAddr, MHZ_TO_LVAL(freq_mhz));
}

static int do_set_cbf_freq(uint32_t freq)
{
	set_llc_freq(freq);
	if (!clock_config_cbf(freq))
		return -EFAULT;
	printf("The CBF frequency is set to %dMHz\n", freq);
	return 0;
}

static int do_set_apc_freq(uint64_t apc_mask, uint32_t freq)
{
	int i = 0;
	uint64_t clusters = get_apc_mask(get_cpu_mask());

	for (i = 0; i < MAX_CPU_CLUSTERS; i++) {
		if ((clusters & apc_mask) & _BV(i)) {
			__set_cpu_freq(i, freq);
			if (falkor_is_cluster_clocked(i) &&
			    !clock_config_cluster(i, freq))
				return -EFAULT;
		}
	}
	printf("The APC %016llx frequency is set to %dMHz\n",
	       clusters & apc_mask, freq);
	return 0;
}

void err_set_freq(const char *hint)
{
	printf("--ERROR: %s\n", hint);
	(void)cmd_help("setfreq");
}

int cmd_set_freq(int argc, char * argv[])
{
	char *cmd = NULL;
	int freq = 0;
	uint64_t cpu_mask;
	uint32_t cluster;

	if (argc < 3) {
		err_set_freq("Missing command.");
		return -EINVAL;
	}
	cmd = argv[2];

	if (strcmp(cmd, "cbf") == 0) {
		if (argc < 4) {
			err_set_freq("Missing CBF frequency.");
			return -EINVAL;
		}
		cmd = argv[3];
		freq = strtoul(cmd, 0, 0);
		if (freq < 600 || freq > 2800) {
			err_set_freq("Invalid CBF frequency.");
			return -EINVAL;
		}
		if (do_set_cbf_freq(freq)) {
			printf("--ERROR: failed to set CBF frequency.\n");
			return -EFAULT;
		}
		return 0;
	} else if (strcmp(cmd, "apc") == 0) {
		if (argc < 4) {
			err_set_freq("Missing APC masks.");
			return -EINVAL;
		}
		cmd = argv[3];
		cpu_mask = cmd_get_cpu_mask(cmd);
		if (cpu_mask != CMD_INVALID_CPU_MASKS)
			cluster = get_apc_mask(cpu_mask);
		else
			cluster = strtoul(cmd, 0, 0);
		if (cluster == CMD_INVALID_CPU_MASKS) {
			err_set_freq("Invalid APC masks.");
			return -EINVAL;
		}
		if (argc < 5) {
			err_set_freq("Missing frequency.");
			return -EINVAL;
		}
		cmd = argv[4];
		freq = strtoul(cmd, 0, 0);
		if (freq < 600 || freq > 3000) {
			err_set_freq("Invalid APC frequency.");
			return -EINVAL;
		}
		if (do_set_apc_freq(cluster, freq)) {
			printf("--ERROR: failed to set APC frequency.\n");
			return -EFAULT;
		}
		return 0;
	}

	err_set_freq("Invalid command.");
	return -EINVAL;
}

MK_CMD(freq, cmd_set_freq, "Set/get APC/CBF frequencies",
	" freq set apc apc_mask freq\n"
	"    -set the APC frequency (600 <= freq <= 3000)\n"
	" freq set apc N|cN|rN|all freq\n"
	"    -set the APC frequency (600 <= freq <= 3000)\n"
	" freq set cbf freq\n"
	"    -set the CBF frequency (600 <= freq <= 2800)\n"
);
