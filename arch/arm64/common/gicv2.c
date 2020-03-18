/*
 */
#include <stdio.h>
#include <target/irq.h>
#include <target/gicv2.h>
#include <target/smp.h>
#include <asm/hal/HALhwio.h>

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

static void gicv2_begin_irq(irq_t *irq, uint8_t *cpu)
{
	uint32_t iar = __raw_readl(GICC_IAR);

	*irq = GICC_GET_IRQ(iar);
	*cpu = GICC_GET_CPU(iar);
}

static void gicv2_end_irq(irq_t irq, uint8_t cpu)
{
	__raw_writel(GICC_SET_IRQ(irq) | GICC_SET_CPU(cpu),
		     GICC_EOIR);
}

void gicv2_handle_irq()
{
	irq_t irq;
	uint8_t cpu;

	gicv2_begin_irq(&irq, &cpu);
	if (!gic_sanitize_acked_irq(irq)) {
		gicv2_end_irq(irq, cpu);
		return;
	}
	if (!do_IRQ(irq))
		irqc_disable_irq(irq);
	gicv2_end_irq(irq, cpu);
}
