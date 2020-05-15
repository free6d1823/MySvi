/*
 */
#include <target/irq.h>
#include <target/gic.h>
#include <asm/mach/qgic2.h>
#include <asm/io.h>

static void *dist_base;

static inline void gicd_enable_irq(irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICD_ISENABLER(dist_base, irq));
}
static inline void gicd_disable_irq(irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICD_ICENABLER(dist_base, irq));
}
static inline void gicd_enable_all_irqs(irq_t max_irq)
{
	irq_t irq;
	for (irq = 0; irq <= max_irq; irq += 32) {
		__raw_writel(0xFFFFFFFF, GICD_ISENABLER(dist_base, irq));
	}
}
static inline void gicd_disable_all_irqs(irq_t max_irq)
{
	irq_t irq;
	for (irq = 0; irq <= max_irq; irq += 32) {
		__raw_writel(0xFFFFFFFF, GICD_ICENABLER(dist_base, irq));
	}
}
static inline void gicd_trigger_irq(irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICD_ISPENDR(dist_base, irq));
}
static inline void gicd_clear_irq(irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICD_ICPENDR(dist_base, irq));
}
static inline void gicd_configure_irq(irq_t irq, uint8_t priority, uint8_t trigger)
{
	uint32_t cfg;
	__raw_writel_mask(GIC_PRIORITY(qgic2, irq, priority),
					  GIC_PRIORITY(qgic2, irq, GIC_PRIORITY_MASK),
					  GICD_IPRIORITYR(dist_base, irq));
	if (trigger == IRQ_LEVEL_TRIGGERED)
		cfg = GIC_TRIGGER(GIC_TRIGGER_LEVEL);
	else
		cfg = GIC_TRIGGER(GIC_TRIGGER_EDGE);
	__raw_writel_mask(
		GIC_INT_CONFIG(irq, cfg), GIC_INT_CONFIG(irq, GIC_INT_CONFIG_MASK), GICD_ICFGR(dist_base, irq));
}

void gicv2_init_gicd(irq_t max_irq)
{
	irq_t irq;
	__raw_writel(GICD_ENABLE_GRP0 | GICD_ENABLE_GRP1, GICD_CTLR(dist_base));
	gicd_disable_all_irqs(max_irq);
	for (irq = 0; irq <= max_irq; irq++) {
		__raw_setl(GICD_MODEL(GICD_MODEL_1_N), GICD_ICFGR(dist_base, irq));
	}
}
void gicv2_init_gicc(irq_t max_irq, uint8_t max_prio)
{
	__raw_setl(GICC_ENABLE_GRP1, GICC_CTLR);
	__raw_writel(GICC_PRIORITY(qgic2, max_prio), GICC_PMR);
	__raw_writel(GICC_BINARY_POINT(2), GICC_BPR);
}

struct irq_chip qgic2 = {
	.max_irq = NR_QGIC2_IRQS - 1,
	.enable = gicd_enable_irq,
	.disable = gicd_disable_irq,
	.clear = gicd_clear_irq,
	.trigger = gicd_trigger_irq,
	.config = gicd_configure_irq,
};

void qgic2_handle_irq(void)
{
	gicv2_handle_irq();
}

void qgic2_init(void* dist)
{
	irq_t irq;
	irq_t max_irq = NR_QGIC2_IRQS - 1;
	uint8_t max_pri = GIC_PRIORITY_MAX(GIC2);

	dist_base = dist;

	gicv2_init_gicd(max_irq);
	gicv2_init_gicc(max_irq, max_pri);

	for (irq = 0; irq < NR_QGIC2_IRQS; irq += 32)
		__raw_writel(0xFFFFFFFF, GICD_ISR(dist_base, irq));
	/* Allow NS access to GICD_CGCR via GICD_ANSACR */
	__raw_writel(GICD_GICD_CGCR, GICD_ANSACR(dist_base));
	__raw_setl(GICC_ENABLE_GRP1_NS, GICC_CTLR);
	irqc_register(&qgic2);
}
