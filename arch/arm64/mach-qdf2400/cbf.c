#include <asm/hal/HALhwio.h>
#include <asm/mach/hal/HALbootHWIO.h>
#include <target/cpus.h>
#include <target/delay.h>
#include <target/clock.h>
#include <target/arch.h>
#include <asm/mach/cbf.h>

#define CBF_CLAMP_ASSERT_DELAY_US		1
#define CBF_CLAMP_DEASSERT_DELAY_US		1
#define CBF_CLAMP_CBFPD_ASSERT_DELAY_US		2
#define CBF_CLAMP_CBFPD_DEASSERT_DELAY_US	1
#define CBF_POR_RST_DEASSERT_DELAY_US		1

#define CBF_LOGIC_MASK			(1 << (MAX_L3_BLOCKS + 1))

/* Below is the array of L3 power control registers. */
static const unsigned long
l3_power_control_registers[MAX_L3_BLOCKS] = {
	HWIO_APCS_PM_CBF_L3U00_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U01_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U02_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U03_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U04_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U05_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U06_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U07_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U08_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U09_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U10_PWR_CTL_ADDR,
	HWIO_APCS_PM_CBF_L3U11_PWR_CTL_ADDR,
};
static uint32_t cbf_initialized = 0;

/* This function configures the CBF and is done prior to bringing up any L3
 * blocks.
 */
static void cbf_init(void)
{
	if (cbf_initialized & CBF_LOGIC_MASK)
		return;

	/* CBF power on sequence. */

	/* Assert CLAMP_CBFPD */
	HWIO_APCS_PM_CBF_CBF_PWR_CTL_OUT(
		HWIO_APCS_PM_CBF_CBF_PWR_CTL_CLAMP_CBFPD_BMSK);
	udelay(CBF_CLAMP_CBFPD_ASSERT_DELAY_US);

	/* Deassert CLAMP_CBFPD, assert APC_ON */
	HWIO_APCS_PM_CBF_CBF_PWR_CTL_OUT(
		HWIO_APCS_PM_CBF_CBF_PWR_CTL_PMIC_APC_ON_BMSK);
	udelay(CBF_CLAMP_CBFPD_DEASSERT_DELAY_US);

	cbf_initialized |= CBF_LOGIC_MASK;
}

/* This function configures an L3 block.  It does not include CPR sensor
 * preparations.  This must be done separately.  L3 blocks have an APM
 * switch for memory and a GDHS switch for logic.
 */
void cbf_init_l3_block(uint8_t l3bnr)
{
	cbf_init();

	if (cbf_initialized & (1 << l3bnr))
		return;

	/* Assert all CLAMPs */
	out_dword(l3_power_control_registers[l3bnr],
		  HWIO_APCS_PM_CBF_L3U00_PWR_CTL_CLAMP_APMPD_BMSK);
	udelay(CBF_CLAMP_ASSERT_DELAY_US);

	/* Assert POR_RST and all CLAMPs */
	out_dword(l3_power_control_registers[l3bnr],
		  HWIO_APCS_PM_CBF_L3U00_PWR_CTL_POR_RST_BMSK |
		  HWIO_APCS_PM_CBF_L3U00_PWR_CTL_CLAMP_APMPD_BMSK);
	udelay(CBF_CLAMP_ASSERT_DELAY_US);

	/* Unclamp All Clamps */
	/* Assert POR_RST and all CLAMPs */
	out_dword(l3_power_control_registers[l3bnr],
		  HWIO_APCS_PM_CBF_L3U00_PWR_CTL_POR_RST_BMSK);
	udelay(CBF_CLAMP_DEASSERT_DELAY_US);

	/* Deassert POR_RST */
	out_dword(l3_power_control_registers[l3bnr], 0);
	udelay(CBF_CLAMP_DEASSERT_DELAY_US);

	cbf_initialized |= (1 << l3bnr);
}

int cbf_init_l3_blocks(void)
{
	uint8_t l3bnr;
	uint64_t cbf_mask = get_llc_mask();
	uint64_t l3_block_mask = cbf_get_l3_block_mask(cbf_mask);

	/* Reset initialization inidicators */
	cbf_initialized = 0;

	/* Initialize all valid L3 blocks according to partial goods */
	for (l3bnr = 0; l3bnr < MAX_L3_BLOCKS; l3bnr++) {
		if (l3_block_mask & (1 << l3bnr))
			cbf_init_l3_block(l3bnr);
	}
	return 0;
}
