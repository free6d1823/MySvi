#include <stdbool.h>
#include <stdint.h>
#include <target/clock.h>
#include <target/cpus.h>
#include <asm/hal/HALhwio.h>
#include <asm/mach/hal/HALclkHWIO.h>
#include <asm/mach/hal/HALclkapcHWIO.h>

#define EXTRACT_FUSE_VAL(val, fuse) \
	(((val) & HWIO_##fuse##_BMSK) >> HWIO_##fuse##_SHFT)

static struct qdf2400_fuse_clock *qdf2400_fuse_get_clock_settings(void)
{
	static bool qdf2400_fuse_clock_init = false;
	static struct qdf2400_fuse_clock fuse;
	uint32_t fuse_val;

	if (qdf2400_fuse_clock_init)
		return &fuse;

	/* Global settings */
	fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW33_LSB));
	fuse.OvrEn = EXTRACT_FUSE_VAL(fuse_val,
		QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_EN);
	fuse.OvrInvEn = EXTRACT_FUSE_VAL(fuse_val,
		QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_INV_EN);
	fuse.OvrDcaEn = EXTRACT_FUSE_VAL(fuse_val,
		QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_DCA_EN);
	fuse.OvrTdlSel = EXTRACT_FUSE_VAL(fuse_val,
		QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_TDL_SEL);
	fuse.OvrMuxSel = EXTRACT_FUSE_VAL(fuse_val,
		QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_MUX_SEL);
	if (fuse.OvrEn && fuse.OvrDcaEn) {
		/* Per APC settings */
		fuse.OvrDcaVal[0] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC00_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[1] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC01_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[2] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC02_CLK_CFG_OVR_DCA_VAL);

		fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW33_MSB));
		fuse.OvrDcaVal[3] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW33_MSB_APC03_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[4] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW33_MSB_APC04_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[5] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW33_MSB_APC05_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[6] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW33_MSB_APC06_CLK_CFG_OVR_DCA_VAL);
		fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW34_LSB));
		fuse.OvrDcaVal[7] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC07_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[8] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC08_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[9] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC09_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[10] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC10_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[11] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC11_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[12] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC12_CLK_CFG_OVR_DCA_VAL);

		fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW34_MSB));
		fuse.OvrDcaVal[13] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_MSB_APC13_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[14] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_MSB_APC14_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[15] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_MSB_APC15_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[16] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW34_MSB_APC16_CLK_CFG_OVR_DCA_VAL);

		fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW35_LSB));
		fuse.OvrDcaVal[17] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC17_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[18] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC18_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[19] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC19_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[20] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC20_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[21] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC21_CLK_CFG_OVR_DCA_VAL);
		fuse.OvrDcaVal[22] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC22_CLK_CFG_OVR_DCA_VAL);

		fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW35_MSB));
		fuse.OvrDcaVal[23] = EXTRACT_FUSE_VAL(fuse_val,
			QFPROM_CORR_SPARE_REG27_ROW35_MSB_APC23_CLK_CFG_OVR_DCA_VAL);
	}

	qdf2400_fuse_clock_init = true;
	return &fuse;
}

bool qdf2400_fuse_override_clock_mux(uint32_t *p_clk_sel)
{
	struct qdf2400_fuse_clock *fuse = qdf2400_fuse_get_clock_settings();

	if (fuse->OvrEn) {
		(*p_clk_sel) |= fuse->OvrMuxSel;
		(*p_clk_sel) |= fuse->OvrMuxSel << HWIO_APCS_APC00_CLKSEL_ALTPRISRCSEL_1_0_SHFT;
	}
	return fuse->OvrEn;
}

/*
 * Apply fuse overrides:
 * Refer to cm_pll_agera datasheet (80-P4246-2) for more details
 */
void qdf2400_fuse_apply_clock_settings(struct agera_pll_regs *regs,
				       uint32_t apc)
{
	struct qdf2400_fuse_clock *fuse = qdf2400_fuse_get_clock_settings();

	if (fuse->OvrEn) {
		/*
		 * TDL enable for other PLL outputs - pll_config_ctl[55]
		 *  0 - TDL output is not routed to main and aux outputs
		 *  1 - TDL output is output to other PLL outputs
		 */
		regs->config_ctl_hi &= ~(1 << 23);
		if (fuse->OvrTdlSel)
			regs->config_ctl_hi |= (1 << 23);
		/*
		 * Output clock polarity - pll_user_ctl[7]
		 *  0 - Do not invert output
		 *  1 - Invert output
		 */
		regs->user_ctl &= ~(1 << 7);
		if (fuse->OvrInvEn)
			regs->user_ctl |= (1 << 7);
		/* Duty cycle adjust */
		if (fuse->OvrDcaEn) {
			/*
			 * Output duty cycle control enable on lv_early
			 * output - pll_config_ctl[37]
			 *  0 - Duty cycle adjustment is disabled
			 *  1 - Duty cycle adjustment is enabled
			 */
			regs->config_ctl_hi |= 1 << 5;
			/*
			 * Duty cycle control override - pll_config_ctl[44]
			 *  0 - Uses internal duty cycle measurement to
			 *      change duty cycle
			 *  1 - Uses duty cycle control from
			 *       pll_config_ctl[42:38] to adjust duty cycle
			 */
			regs->config_ctl_hi |= 1 << 12;
			/*
			 * Duty cycle adjustment - pll_config_ctl[42:38]
			 */
			regs->config_ctl_hi &= ~0x7C0;
			regs->config_ctl_hi |=
				(fuse->OvrDcaVal[apc] & 0x1F) << 6;
		}
	}
}

uint64_t pseudo_cpu_mask = 0;
uint64_t pseudo_llc_mask = 0;

#ifdef CONFIG_TESTOS_EMU
static inline uint64_t __get_cpu_mask(void)
{
	return CPU_ALL;
}

static inline uint64_t __get_llc_mask(void)
{
	/* It's meaningless to define MAX_LLCS, while LLC_MASK is useful
	 * for testing patterns with destined bad LLC interleaves due to
	 * the reason that number of good LLC interleaves must be ensured
	 * for configuring 32MB TCM memory region.
	 */
	return LLC_ALL;
}
#else
static inline uint64_t __get_cpu_mask(void)
{
	uint64_t cpu_mask_msb;
	uint32_t cpu_mask_lsb;
	uint64_t cpu_mask;

	cpu_mask_msb = ~HWIO_IN(PARTIAL_GOOD_CPU_PORT_MSB);
	cpu_mask_msb &= HWIO_PARTIAL_GOOD_CPU_PORT_MSB_RMSK;
	cpu_mask_lsb = ~HWIO_IN(PARTIAL_GOOD_CPU_PORT_LSB);
	cpu_mask_lsb &= HWIO_PARTIAL_GOOD_CPU_PORT_LSB_RMSK;
	cpu_mask = ((cpu_mask_msb<<32) | cpu_mask_lsb);
	return cpu_mask;
}

static inline uint64_t __get_llc_mask(void)
{
	uint64_t l3_mask = 0;

	l3_mask = ~HWIO_IN(PARTIAL_GOOD_L3_PORT);
	l3_mask &= HWIO_PARTIAL_GOOD_L3_PORT_RMSK;
	return l3_mask;
}
#endif

uint64_t get_cpu_mask(void)
{
	if (pseudo_cpu_mask)
		return pseudo_cpu_mask;
	else
		return __get_cpu_mask();
}

void set_cpu_mask(uint64_t cpu_mask)
{
	if (cpu_mask)
		pseudo_cpu_mask = __get_cpu_mask() & cpu_mask;
	else
		pseudo_cpu_mask = __get_cpu_mask();
}

uint64_t get_llc_mask(void)
{
	if (pseudo_llc_mask)
		return pseudo_llc_mask;
	else
		return __get_llc_mask();
}

void set_llc_mask(uint64_t llc_mask)
{
	if (llc_mask)
		pseudo_llc_mask = __get_llc_mask() & llc_mask;
	else
		pseudo_llc_mask = __get_llc_mask();
}
