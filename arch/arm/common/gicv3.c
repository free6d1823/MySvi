/*
 */
#include <stdio.h>
#include <target/irq.h>
#include <target/smp.h>
#include <target/gicv3.h>

static inline bool gic_sanitize_acked_irq(irq_t irq)
{
	if (irq == IRQ_ACK_SEL1) {
		printf("IRQ should be handled in "
		       "Secure EL1\n");
		return false;
	}
	if (irq == IRQ_ACK_NSEL1) {
		printf("IRQ should be handled in "
		       "Non-secure EL1\n");
		return false;
	}
	if (irq == IRQ_ACK_NONE) {
		printf("No pending IRQ with sufficient "
		       "priority or the highest pending IRQ "
		       "is appropriate for the current secure "
		       "state or the associated IRQ group\n");
		return false;
	}
	return true;
}

void gicv3_begin_irq(irq_t* irq, uint8_t* cpu)
{
	uint32_t iar = read_sysreg(ICC_IAR1);

	*irq = iar;
	*cpu = smp_processor_id();
}

void gicv3_end_irq(irq_t irq, uint8_t cpu)
{
	write_sysreg(irq, ICC_EOIR1);
}

void gicv3_handle_irq()
{
	irq_t irq;
	uint8_t cpu;

	gicv3_begin_irq(&irq, &cpu);
	if (!gic_sanitize_acked_irq(irq))
		return;

	if (!do_IRQ(irq))
		irqc_disable_irq(irq);
	gicv3_end_irq(irq, cpu);
}

void gicv3_init_gits(irq_t max_irq)
{
}

void gicc_enable_priority_mask(uint8_t priority)
{
	write_sysreg(priority, ICC_PMR);
}

void gicc_disable_priority_mask(void)
{
	write_sysreg(GIC_PRIORITY_IDLE, ICC_PMR);
}

void gicv3_init_gicc(irq_t max_irq, uint8_t max_prio)
{
	/* Disable the legacy interrupt bypass and enable system register
	 * access for EL3 and allow lower exception levels.
	 */
	write_sysreg(ICC_DIB | ICC_DFB | ICC_SRE_SRE, ICC_SRE);

	gicc_enable_priority_mask(max_prio);

	write_sysreg(ICC_ENABLE_GRP, ICC_IGRPEN0);
	write_sysreg(ICC_ENABLE_GRP, ICC_IGRPEN1);

	isb();
}
