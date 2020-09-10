/**---------------------------------------------------------------------------
 * @file    clk_common.c
 *
 * @brief    clk common file
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <target/cmdline.h>
#include <errno.h>
#include <target/heap.h>
#include <target/utils.h>
#include <target/list.h>
#include <target/delay.h>
#include <target/spinlock.h>
#include <target/timer.h>
#include <target/clk.h>

struct clk {
	u32		flag;
	u32		parent_rate;
	u32		ioclk_addr;
	u32		ioreset_addr;
};

#define MAKE_CLK_DEV(id, flag, p_rate, clk_addr, reset_addr) \
	[id] = {flag, p_rate, clk_addr, reset_addr}

#define CPU_CLK_ADDR(cpu) ((uint64_t)\
	((1 >= cpu)?(0x12004 - 4 * cpu):(0x200C - 4 * (cpu - 2))))
#define CPU_RESET_ADDR(cpu) ((uint64_t)\
	((1 >= cpu)?(0x13004 - 4 * cpu):(0x300C - 4 * (cpu - 2))))
struct clk clks_group[MAX_CLK_DEV] = {
	MAKE_CLK_DEV(CPU0_CLK, 0, 1800000000, CPU_CLK_ADDR(0), CPU_RESET_ADDR(0)),
	MAKE_CLK_DEV(CPU1_CLK, 0, 1800000000, CPU_CLK_ADDR(1), CPU_RESET_ADDR(1)),
	MAKE_CLK_DEV(CPU2_CLK, 0, 2400000000, CPU_CLK_ADDR(2), CPU_RESET_ADDR(2)),
	MAKE_CLK_DEV(CPU3_CLK, 0, 2400000000, CPU_CLK_ADDR(3), CPU_RESET_ADDR(3)),
	MAKE_CLK_DEV(CPU4_CLK, 0, 2400000000, CPU_CLK_ADDR(4), CPU_RESET_ADDR(4)),
	MAKE_CLK_DEV(CPU5_CLK, 0, 2400000000, CPU_CLK_ADDR(5), CPU_RESET_ADDR(5)),
	MAKE_CLK_DEV(SYSNOC_CLK, 0, 0, 0xd2f30, 0),
	MAKE_CLK_DEV(PERI0_UART0_CLK, 0, 400000000,
		RH_PLL_CTRL_REG_BASE + PERI0_SS_APB_CLK, RH_PLL_CTRL_REG_BASE + PERI0_SS_APB_RESET),
	MAKE_CLK_DEV(PERI1_UART0_CLK, 0, 400000000,
		LH_PLL_CTRL_REG_BASE + PERI1_SS_APB_CLK, LH_PLL_CTRL_REG_BASE + PERI1_SS_APB_RESET),
	MAKE_CLK_DEV(PERI1_SS_AHB_CLK, 0, 200000000,
		LH_PLL_CTRL_REG_BASE+ PERI1_SS_AHB_CLK_OFST, LH_PLL_CTRL_REG_BASE+PERI1_SS_AHB_RST_OFST),
	MAKE_CLK_DEV(PERI1_SS_TIM_CLK, 0, 10000000,
		LH_PLL_CTRL_REG_BASE+ PERI1_SS_TIM_CLK_OFST, LH_PLL_CTRL_REG_BASE+PERI1_SS_TIM_RST_OFST),
	MAKE_CLK_DEV(PERI1_SS_REF_CLK, 0, 25000000,
		LH_PLL_CTRL_REG_BASE+ PERI1_SS_REF_CLK_OFST, LH_PLL_CTRL_REG_BASE+PERI1_SS_REF_RST_OFST),

	MAKE_CLK_DEV(NOC_WRAP_MAIN_CLK, 0, 0, 0x52020, 0),
	MAKE_CLK_DEV(NOC_WRAP_GPUNOC_MAIN_CLK, 0, 0, 0x52024, 0),
	MAKE_CLK_DEV(NOC_WRAP_DDR_LINK_CLK, 0, 0, 0x52028, 0),
	MAKE_CLK_DEV(DDR0_SS_DDR_CORE_CLK,  0, 0, 0x52000, 0x53000),
	MAKE_CLK_DEV(DDR0_SS_DDR_CFG_CLK,   0, 0, 0x52008, 0x53004),

	MAKE_CLK_DEV(MDP_SS_D71_AXI0_CLK,   0, 0, 0xc2000, 0xc3000),
	MAKE_CLK_DEV(MDP_SS_PIXEL_CLK,      0, 0, 0xc2014, 0),
	MAKE_CLK_DEV(MDP_SS_APB_CLK,        0, 0, 0xc200c, 0),
};

#define CLK_REG_READ(reg_a) do {	\
		void __iomem*	reg_addr;					\
		reg_addr = (void __iomem*)(CLK_RESET_REG_BASE + (uintptr_t)reg_a);	\
		reg_value = readl(reg_addr);	\
		} while (0)

#define CLK_REG_WRITE(reg_a, value) do {	\
		void __iomem*	reg_addr;				\
		reg_addr = (void __iomem*)(CLK_RESET_REG_BASE + (uintptr_t)reg_a);	\
		writel(value, reg_addr);	\
		} while (0)

#define CLK_REG_MASK_SETL(reg_a, mask, value) do {	\
		void __iomem*	reg_addr;				\
		reg_addr = (void __iomem*)(CLK_RESET_REG_BASE + (uintptr_t)reg_a);	\
		__raw_writel_mask(value, mask, reg_addr);	\
		} while (0)

ulong clk_get_rate(u32 clk_id)
{
	ulong	parent_rate;
	u32		divider, divider_pow, reg_value, i;

	parent_rate = clks_group[clk_id].parent_rate;
	CLK_REG_READ(clks_group[clk_id].ioclk_addr);
	divider_pow = (CLK_DIVIDER_MASK & reg_value);

	divider = 1;
	for (i = 0; i < divider_pow; i++) {
		divider = 2 * divider; /* caution: no safety check here*/
	}

	return parent_rate / divider;
}

/* by default. set_rate will enable pll divider clk*/
void clk_set_rate(u32 clk_id, ulong rate)
{
	ulong	parent_rate;
	u32		divider, divider_pow, i;
	u32		clk_sel, gate_enable;

	if (clks_group[clk_id].flag) {
		printf("warning: clk dev has been configured before\n");
	}

	clks_group[clk_id].flag = 1;
	parent_rate = clks_group[clk_id].parent_rate;
	divider = parent_rate / rate;
	divider_pow = 0;
	for (i = divider; i > 1; i = divider/2)
		divider_pow++;
	printf("expected rate=%d, parent rate=%d, divider_pow =%d\n",
			rate, parent_rate, divider_pow);

	clk_sel = 1 << CLK_SEL_POS;
	gate_enable = 1 << CLK_GATE_POS;
	CLK_REG_WRITE(clks_group[clk_id].ioclk_addr,
				divider_pow | clk_sel | gate_enable);

	/* release the reset signal by default */
	if (clks_group[clk_id].ioreset_addr != 0)
		CLK_REG_WRITE(clks_group[clk_id].ioreset_addr, 0);
}

void clk_disable(u32 clk_id)
{
	u32		gate_enable;

	gate_enable = 0 << CLK_GATE_POS;
	CLK_REG_MASK_SETL(clks_group[clk_id].ioclk_addr,
			~CLK_GATE_MASK, gate_enable);

	/* how to handle reset signal now */
}

/* support two kind of source
 * 1: PLL divider source. for example PLL output clk is 1Ghz
 *    config divider=5, will get 200Mhz clk
 * 0: fixed osc clk. for example, fixed 24Mhz clk
 * */
void clk_enable(u32 clk_id, u32 src)
{
	u32 v;

	if (src > 1) {
		printf("err: wrong clk src selection\n");
		return;
	}

	v = BIT(CLK_GATE_POS) | (src << CLK_SEL_POS);

	CLK_REG_MASK_SETL(clks_group[clk_id].ioclk_addr,
			BIT(CLK_GATE_POS) | BIT(CLK_SEL_POS), v);

	/* release the reset signal by default */
	if (clks_group[clk_id].ioreset_addr != 0)
		CLK_REG_WRITE(clks_group[clk_id].ioreset_addr, 0);
}

void clk_dump(u32 id) {
	ulong rate;
	if (id == 0x555566666) {
		printf("dump all clk dev not supported currenlty\n");
		return;
	}
	rate = clk_get_rate(id);
	printf("clk id %d rate is %d\n", id, rate);
}