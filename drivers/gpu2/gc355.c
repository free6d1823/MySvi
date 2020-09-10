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

void handle_gc355_irq(irq_t irq, void *ctx)
{
	uint32_t irq_ack_value = 0;
	irq_ack_value = readl(GC355_AHB_REG_BASE + GPU2_AHB_AQINTRACK);
	if (irq_ack_value & 0x1000000)
	{
		sim_finish();
	}
}

void gc355_irq_init()
{
	irq_t gc355_intr = GC355_IRQ;
	irqc_configure_irq(gc355_intr, 32, IRQ_EDGE_TRIGGERED);
	irq_register_vector(gc355_intr, handle_gc355_irq, NULL);
	irqc_enable_irq(gc355_intr);
}


void gc355_normal_test(int cmdlen, uint32_t cmdaddr)
{
	soft_reset(GC355_AHB_REG_BASE);
	fetch_cmd_start(GC355_AHB_REG_BASE, cmdlen, cmdaddr, GC355_AHB_GCREGFETCHADDR, GC355_AHB_GCREGFETCHCTRL);
	polling_idle(GC355_AHB_REG_BASE);
	sim_finish();
}

void gc355_clockgating_test(int cmdlen, uint32_t cmdaddr)
{
	clockgating_test(GC355_AHB_REG_BASE, cmdlen, cmdaddr, GC355_AHB_GCREGFETCHADDR,
				GC355_AHB_GCREGFETCHCTRL, CLK_RESET_REG_BASE + GPU2_PLL_REG_BASE + GC355_RSTN);
}

void gc355_change_freq_test(int cmdlen, uint32_t cmdaddr)
{
	soft_reset(GC355_AHB_REG_BASE);
	fetch_cmd_start(GC355_AHB_REG_BASE, cmdlen, cmdaddr, GC355_AHB_GCREGFETCHADDR, GC355_AHB_GCREGFETCHCTRL);
	change_freq_polling(GC355_AHB_REG_BASE, CLK_RESET_REG_BASE + GPU2_PLL_REG_BASE + GC355_MST_ACLK);
	sim_finish();
}

int cmd_gc355(int argc, char * argv[])
{
	uint32_t cmdaddr = CMDBUFDEFAULT;
	uint32_t cmdlen = CMDLENDEFAULT;

	if(argc < 2)
		return -EUSAGE;

	if (argv[1][0] == 'd') {
		dump_info(GC355_AHB_REG_BASE);
	}

	if(argc >= 3)
		cmdaddr = strtoul(argv[2], 0, 0);

	if(argc >= 4)
		cmdlen = strtoul(argv[3], 0, 0);

	if (argv[1][0] == 'n') {
		gc355_normal_test(cmdlen, cmdaddr);
	}

	if (argv[1][0] == 'c') {
		gc355_clockgating_test(cmdlen, cmdaddr);
	}

	if (argv[1][0] == 'f') {
		gc355_change_freq_test(cmdlen, cmdaddr);
	}

	if (argv[1][0] == 'e') {
		enable_smmu(GC355_TCU_REG_BASE);
	}

	return 0;
}


MK_CMD(gc355, cmd_gc355, "GC355 2.5D test cases",
	"gc355 dump \n"
	"	-dump info\n"
	"gc355 normal [cmdbuf] [cmdlen]\n"
	"	-normal test\n"
	"gc355 clockgating [cmdbuf] [cmdlen]\n"
	"	-clockgating test\n"
	"gc355 freq [cmdbuf] [cmdlen]\n"
	"	-change frequency test\n"
	"gc355 enable smmu\n"
	"	-enable smmu\n"
);

