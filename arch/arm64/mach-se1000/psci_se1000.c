#include <stdio.h>
#include <asm/psci.h>
#include <target/memory.h>
#include <asm/barrier.h>
#include <target/cache.h>
#include <target/smp.h>
#include <target/utils.h>
#include <target/clk.h>
/* defined in head.S */
void _start(void);

#define RVBAR_L(cpu)	((uint64_t)SYSREG_BASE + \
	0x2020 + 4 * cpu)

#define AP0_PWR_ADDR(cpu) ((uint64_t)PMU_PWR_REG_BASE + \
	0x1000 + 0x400 * cpu)

#define PMU_PWR_POS		2

static uint16_t CPU_CLK_index[MAX_CPU_NUM] = {
#ifdef CONFIG_CLK_DRIVER
	CPU0_CLK, CPU1_CLK, CPU2_CLK, CPU3_CLK, CPU4_CLK, CPU5_CLK
#endif
};
#ifdef BOOT_CORE
uint64_t CPU_HOLD_BASE[MAX_CPU_NUM];
#endif

int psci_cpu_on(uint64_t target_cpu,
                uint64_t entrypoint,
                uint64_t context_id)
{
	uint32_t v;
	uint8_t cpu = (target_cpu >> 8) & 0xff;
	uint64_t local_entry = (uint64_t)_start;

	if (smp_processor_id() == cpu || cpu >= MAX_CPU_NUM) {
		printf("target CPU is running %lx\n", target_cpu);
		return PSCI_E_INVALID_PARAMS;
	}

	entry_addr = entrypoint;
	flush_dcache_addr(&entry_addr);

#ifdef BOOT_CORE
	__raw_writel(1, (uint64_t)(CPU_HOLD_BASE + cpu));
	flush_dcache_addr(CPU_HOLD_BASE + cpu);
	sev();
#endif

	/* Configure the reset address */
	__raw_writel(local_entry >> 2, RVBAR_L(cpu));

	/* Configure AP clock and release reset */
	clk_enable(CPU_CLK_index[cpu], 1);

	/* Configure PMU AP power on */
	v = (1 << PMU_PWR_POS);
	__raw_writel_mask(v, BIT(PMU_PWR_POS + 1) | BIT(PMU_PWR_POS),
			AP0_PWR_ADDR(cpu));

	isb();
	return PSCI_E_SUCCESS;
}
