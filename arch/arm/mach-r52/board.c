#include <stdio.h>

#include <target/cp15.h>
#include <target/memory.h>
#include <target/utils.h>
#include <target/mpu.h>

unsigned int cfgperiphbase;

static int pmsav8_setup_ram(unsigned int number, phys_addr_t start,phys_addr_t end)
{
	u32 bar, lar;

	bar = start;
	lar = (end - 1) & ~(PMSAv8_MINALIGN - 1);

	bar |= PMSAv8_AP_PL1RW_PL0RW | PMSAv8_RGN_SHARED | PMSAv8_BAR_XN;
	lar |= PMSAv8_LAR_IDX(PMSAv8_RGN_NORMAL) | PMSAv8_LAR_EN;

	prsel_write(number);
	prbar_write(bar);
	prlar_write(lar);

	return 0;
}

static int pmsav8_setup_io(unsigned int number, phys_addr_t start,phys_addr_t end)
{
	u32 bar, lar;

	bar = start;
	lar = (end - 1) & ~(PMSAv8_MINALIGN - 1);

	bar |= PMSAv8_AP_PL1RW_PL0RW | PMSAv8_BAR_XN;
	lar |= PMSAv8_LAR_IDX(PMSAv8_RGN_DEVICE_nGnRnE) | PMSAv8_LAR_EN;

	prsel_write(number);
	prbar_write(bar);
	prlar_write(lar);

	return 0;
}

static int pmsav8_setup_code(unsigned int number, phys_addr_t start,phys_addr_t end)
{
	u32 bar, lar;

	bar = start;
	lar = (end - 1) & ~(PMSAv8_MINALIGN - 1);

	bar |= PMSAv8_AP_PL1RO_PL0RO | PMSAv8_RGN_SHARED;
	lar |= PMSAv8_LAR_IDX(PMSAv8_RGN_NORMAL) | PMSAv8_LAR_EN;

	prsel_write(number);
	prbar_write(bar);
	prlar_write(lar);

	return 0;
}


static int mpu_init()
{
	/* ARM Cortex-R52 Processor TRM: 7.3 Level-1 caches
	 * The write behavior for the data cache is always Write-Through caching.
	 * Locations that are marked as Write-Back Cacheable are treated as Write-Through.
	 */
	u32 mair0 = PMSAv8_MAIR(0x00, PMSAv8_RGN_DEVICE_nGnRnE) | \
		     PMSAv8_MAIR(0xff, PMSAv8_RGN_NORMAL); /* can be 0xbb for R52 */

	#define IMP_CBAR __ACCESS_CP15(c15, 1, c3, 0)
	cfgperiphbase = read_sysreg(IMP_CBAR);

#ifndef CONFIG_CPU_V7M
	#define MAIR0	__ACCESS_CP15(c10, 0, c2, 0)
	write_sysreg(mair0, MAIR0);
#else
	writel_relaxed(mair0, BASEADDR_V7M_SCB + PMSAv8_MAIR0);
#endif

	pmsav8_setup_code(0, SVI_TEXT_BASE, TEXT_END);
	pmsav8_setup_ram(1, DATA_START, SVI_RAM_END);
	pmsav8_setup_io(2, 0x030000000, 0x033000000);
	pmsav8_setup_io(3, 0x033800000, 0x038000000);
	pmsav8_setup_io(4, 0x058000000, 0x058250000);
	pmsav8_setup_io(5, 0x0E9000000, 0x0EA000000);
	pmsav8_setup_io(6, cfgperiphbase, cfgperiphbase + 0x400000);

	set_cr(get_cr() | CR_M | CR_C | CR_I);

	return 0;
}


int soc_early_init()
{
	mpu_init();

	return 0;
}

