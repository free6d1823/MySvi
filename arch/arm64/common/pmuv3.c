#include <stdio.h>
#include <target/perf.h>
#include <target/irq.h>
#include <asm/reg.h>

#ifndef CONFIG_IRQ_POLLING
void pmu_handle_irq(irq_t irq, void *ctx)
{
	uint32_t ovs = read_sysreg(PMOVSCLR_EL0);
	int evt;

	for (evt = 0; evt < PERF_HW_MAX_COUNTERS; evt++) {
		if (ovs & PMOVS_P(evt))
			printf("Event %d counter overflow\n", evt);
	}
	write_sysreg(ovs, PMOVSCLR_EL0);
}

int pmu_irq_init(void)
{
	irq_t pmu_irq = IRQ_PMU;

	irqc_configure_irq(pmu_irq, 0, IRQ_LEVEL_TRIGGERED);
	irq_register_vector(pmu_irq, pmu_handle_irq, NULL);
	irqc_enable_irq(pmu_irq);
	return 0;
}
#else
static inline int pmu_irq_init(void)
{
	return 0;
}
#endif

void pmu_reset(void)
{
	perf_hw_reset_events();
}

int pmu_init(void)
{
	uint32_t reg;

	write_sysreg(read_sysreg(PMUSERENR_EL0) | PMUSERENR_EN,
		     PMUSERENR_EL0);
	reg = read_sysreg(PMCR_EL0);
	reg &= ~(PMCR_LC | PMCR_DP | PMCR_D);
	write_sysreg(reg | PMCR_E | PMCR_X, PMCR_EL0);
	write_sysreg(read_sysreg(MDCR_EL3) | MDCR_SPME, MDCR_EL3);
	write_sysreg(read_sysreg(MDCR_EL3) | ~MDCR_TPM, MDCR_EL3);
	write_sysreg(read_sysreg(MDCR_EL2) | ~MDCR_TPM, MDCR_EL2);

	pmu_irq_init();
	return 0;
}
