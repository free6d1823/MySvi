#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <target/irq.h>
#include <target/irqc.h>
#include <target/cmdline.h>
#include <target/utils.h>
#include <target/clk_se1000.h>
#include "gpu2.h"
#include "sim_trigger.h"

#define CMDBUFDEFAULT	0x60000000
#define CMDLENDEFAULT	65536

void handle_gc620_irq(irq_t irq, void *ctx)
{
	uint32_t irq_ack_value = 0;
	irq_ack_value = readl(GC620_AHB_REG_BASE + GPU2_AHB_AQINTRACK);
	if (irq_ack_value & 0x1000000)
	{
		sim_finish();
	}
}

void gc620_irq_init()
{
	irq_t gc620_intr = GC620_IRQ;
	irqc_configure_irq(gc620_intr, 32, IRQ_LEVEL_TRIGGERED);
	irq_register_vector(gc620_intr, handle_gc620_irq, NULL);
	irqc_enable_irq(gc620_intr);
}

void gc620_normal_test(int cmdlen, uint32_t cmdaddr)
{
	gc620_irq_init();
	soft_reset(GC620_AHB_REG_BASE);
	fetch_cmd_start(GC620_AHB_REG_BASE, cmdlen, cmdaddr, GC620_AHB_AQCMDBUFADDR, GC620_AHB_AQCMDBUFCTRL);
}

void gc620_mmu_test(uint32_t cmdaddr, uint32_t cmdaddr1)
{
	soft_reset(GC620_AHB_REG_BASE);
	fetch_cmd_start(GC620_AHB_REG_BASE, 1024, cmdaddr1, GC620_AHB_AQCMDBUFADDR, GC620_AHB_AQCMDBUFCTRL);
	polling_idle(GC620_AHB_REG_BASE);
	writel(0x1, (GC620_AHB_REG_BASE + GC620_AHB_MMUCONTROL));
	fetch_cmd_start(GC620_AHB_REG_BASE, 1024, cmdaddr, GC620_AHB_AQCMDBUFADDR, GC620_AHB_AQCMDBUFCTRL);
	polling_idle(GC620_AHB_REG_BASE);
	sim_finish();
}

void gc620_ramclockgating_test(uint32_t cmdaddr)
{
	writel(0x70500, (GC620_AHB_REG_BASE + GPU2_AHB_AQHICLOCKCTRL));
	fetch_cmd_start(GC620_AHB_REG_BASE, 65536, cmdaddr, GC620_AHB_AQCMDBUFADDR, GC620_AHB_AQCMDBUFCTRL);
	polling_idle(GC620_AHB_REG_BASE);
	writel(0x70100, (GC620_AHB_REG_BASE + GPU2_AHB_AQHICLOCKCTRL));
	sim_finish();
}

void gc620_change_freq_test(int cmdlen, uint32_t cmdaddr)
{
	soft_reset(GC620_AHB_REG_BASE);
	fetch_cmd_start(GC620_AHB_REG_BASE, cmdlen, cmdaddr, GC620_AHB_AQCMDBUFADDR, GC620_AHB_AQCMDBUFCTRL);
	change_freq_polling(GC620_AHB_REG_BASE, CLK_RESET_REG_BASE + GPU2_PLL_REG_BASE + GC620_MST_ACLK);
	sim_finish();
}

void gc620_clockgating_test(int cmdlen, uint32_t cmdaddr)
{
	clockgating_test(GC620_AHB_REG_BASE, cmdlen, cmdaddr, GC620_AHB_AQCMDBUFADDR,
				GC620_AHB_AQCMDBUFCTRL, CLK_RESET_REG_BASE + GPU2_PLL_REG_BASE + GC620_RSTN);
}


int cmd_gc620(int argc, char * argv[])
{
	uint32_t cmdaddr = CMDBUFDEFAULT;
	uint32_t cmdaddr1 = CMDBUFDEFAULT;
	uint32_t cmdlen = CMDLENDEFAULT;

	if(argc < 2)
		return -EUSAGE;

	if (argv[1][0] == 'd') {
		dump_info(GC620_AHB_REG_BASE);
	}

	if (argv[1][0] == 'm') {
		if(argc >= 3)
			cmdaddr = strtoul(argv[2], 0, 0);

		if(argc >= 4)
			cmdaddr1 = strtoul(argv[3], 0, 0);

		gc620_mmu_test(cmdaddr, cmdaddr1);
	}

	if (argv[1][0] == 'r') {
		if(argc == 3)
			cmdaddr = strtoul(argv[2], 0, 0);
		gc620_ramclockgating_test(cmdaddr);
	}

	if (argv[1][0] == 'n') {
		if(argc >= 3)
			cmdaddr = strtoul(argv[2], 0, 0);

		if(argc >= 4)
			cmdlen = strtoul(argv[3], 0, 0);
		gc620_normal_test(cmdlen, cmdaddr);
	}

	if (argv[1][0] == 'e') {
		enable_smmu(GC620_TCU_REG_BASE);
	}

	return 0;
}


MK_CMD(gc620, cmd_gc620, "GC620 2D test cases",
	"gc620 dump \n"
	"	-dump info\n"
	"gc620 normal [cmdbuf] [cmdlen]\n"
	"	-normal test\n"
	"gc620 mmu [cmdbuf] [cmdbuf1]\n"
	"	-mmu test\n"
	"gc620 ramclockgating [cmdbuf] \n"
	"	-ramclockgating test\n"
	"gc620 clockgating [cmdbuf] [cmdlen]\n"
	"	-clockgating test\n"
	"gc620 freq [cmdbuf] [cmdlen]\n"
	"	-change frequency test\n"
	"gc620 enable smmu\n"
	"	-enable smmu\n"
);

