#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <target/heap.h>
#include "../arm_smmu/io-pgtable.h"
#include "gpu2.h"
#include "sim_trigger.h"

void soft_reset(uintptr_t base)
{
	uint32_t clock_ctl = 0x71100;
	writel(clock_ctl, (base + GPU2_AHB_AQHICLOCKCTRL));
	while(readl(base + GPU2_AHB_AQHICLOCKCTRL) & 0x1000);
}

void dump_info(uintptr_t base)
{
	uint32_t chipid = readl((base + GPU2_AHB_GCCHIPID));
	uint32_t chiprev = readl((base + GPU2_AHB_GCCHIPREV));
	uint32_t chipdate = readl((base + GPU2_AHB_GCCHIPDATE));
	printf("CHIP INFO: ID 0x%08x, REV 0x%08x, DATE 0x%08x\n", chipid, chiprev, chipdate);
}

void change_freq(int divider, uintptr_t reg)
{
	writel(BIT(16) | BIT(8) | BIT(divider), reg);
}

void change_freq_polling(uintptr_t base, uintptr_t clk_reg)
{
	uint32_t idle_status = 0;
	int count = 0;
	while(idle_status != 0x7fffffff)
	{
		idle_status = readl((base + GPU2_AHB_AQHIIDLE));

		if (count == 50)
			change_freq(0x4, clk_reg);

		if (count == 100)
			change_freq(0x1, clk_reg);

		if (count == 200)
			change_freq(0x2, clk_reg);

		if (count == 500)
			change_freq(0x3, clk_reg);

		count += 1;
	}
}

void clockgating(uintptr_t rst_reg)
{
	writel(0x1, rst_reg);
}

void polling_idle(uintptr_t base)
{
	uint32_t idle_status = 0;
	while(idle_status != 0x7fffffff)
		idle_status = readl((base + GPU2_AHB_AQHIIDLE));
}

void fetch_cmd_start(uintptr_t base, int cmdlen, u32 cmdaddr, u32 cmdaddrreg, u32 cmdctrlreg)
{
	readl((base + GPU2_AHB_AQINTRACK));
	writel(0xFFFFFFFF,(base + GPU2_AHB_AQINTRENBL));
	writel(cmdaddr, (base + cmdaddrreg));
	writel((((cmdlen>>3) & 0x1FFFF) | BIT(16)), (base + cmdctrlreg));
}

void clockgating_test(uintptr_t base, int cmdlen, uint32_t cmdaddr, u32 cmdaddrreg, u32 cmdctrlreg, u32 rstreg)
{
	soft_reset(base);
	fetch_cmd_start(base, cmdlen, cmdaddr, cmdaddrreg, cmdctrlreg);
	polling_idle(base);
	clockgating(rstreg);
	sim_finish();
}

void change_freq_test(uintptr_t base, int cmdlen, uint32_t cmdaddr, u32 cmdaddrreg, u32 cmdctrlreg, u32 clkreg)
{
	soft_reset(base);
	fetch_cmd_start(base, cmdlen, cmdaddr, cmdaddrreg, cmdctrlreg);
	change_freq_polling(base, clkreg);
	sim_finish();
}

void enable_smmu(phys_addr_t smmu_base)
{
	//sram can't be touched by eth smmu, workaround
	heap_switch_direct(0x60000000, 0x70000000);

	puts("smmu buf init\n");
	if( smmu_buf_init() ) {
		puts("smmu init\n");
		smmu_init(smmu_base, 0);
	}
}



