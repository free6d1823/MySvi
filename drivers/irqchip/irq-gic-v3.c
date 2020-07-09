#include <target/irq.h>
#include <asm/io.h>
#include <target/gic3.h>
#include <target/smp.h>
#include <target/spinlock.h>
#include <stdio.h>

#include "target/gic.h"
#include "target/gicv3.h"

struct gic_chip_data {
	void *dist_base;
	void *rdist_base;
};

static struct gic_chip_data gic_data;

static inline void gicd_enable_irq(irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICD_ISENABLER(gic_data.dist_base, irq));
}

static inline void gicd_disable_irq(irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICD_ICENABLER(gic_data.dist_base, irq));
}

static inline void gicd_enable_all_irqs(irq_t max_irq)
{
	irq_t irq;
	for (irq = 0; irq <= max_irq; irq += 32) {
		__raw_writel(0xFFFFFFFF, GICD_ISENABLER(gic_data.dist_base, irq));
	}
}

static inline void gicd_disable_all_irqs(irq_t max_irq)
{
	irq_t irq;
	for (irq = 0; irq <= max_irq; irq += 32) {
		__raw_writel(0xFFFFFFFF, GICD_ICENABLER(gic_data.dist_base, irq));
	}
}

void gicd_trigger_irq(irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICD_ISPENDR(gic_data.dist_base, irq));
}

void gicr_trigger_irq(irq_t irq, uint8_t cpu) {
	__raw_writel(GIC_INTERRUPT_ID(irq), GICR_ISPENDR0(gic_data.rdist_base, cpu));
}

void gicd_clear_irq(irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICD_ICPENDR(gic_data.dist_base, irq));
}

static inline void gicd_configure_irq(irq_t irq, uint8_t priority, uint8_t trigger)
{
	uint32_t cfg;
	__raw_writel_mask(GIC_PRIORITY(GIC3, irq, priority),
					  GIC_PRIORITY(GIC3, irq, GIC_PRIORITY_MASK),
					  GICD_IPRIORITYR(gic_data.dist_base, irq));
	if (trigger == IRQ_LEVEL_TRIGGERED)
		cfg = GIC_TRIGGER(GIC_TRIGGER_LEVEL);
	else
		cfg = GIC_TRIGGER(GIC_TRIGGER_EDGE);
	__raw_writel_mask(
		GIC_INT_CONFIG(irq, cfg), GIC_INT_CONFIG(irq, GIC_INT_CONFIG_MASK), GICD_ICFGR(gic_data.dist_base, irq));
}

static inline void gicd_wait_rwp(void)
{
	while (__raw_readl(GICD_CTLR(gic_data.dist_base)) & GICD_RWP)
		;
}

static inline void gicd_clear_ctlr(uint32_t value)
{
	__raw_clearl(value, GICD_CTLR(gic_data.dist_base));
	/* RWP tracks GICD_CTLR[2:0, 7:4] */
	gicd_wait_rwp();
}

static inline void gicd_set_ctlr(uint32_t value)
{
	__raw_setl(value, GICD_CTLR(gic_data.dist_base));
	/* RWP tracks GICD_CTLR[2:0, 7:4] */
	gicd_wait_rwp();
}

static inline void gicd_set_spi(irq_t irq, bool secure)
{
	if (secure)
		__raw_writel(GICD_SPI(irq), GICD_SETSPI_SR(gic_data.dist_base));
	else
		__raw_writel(GICD_SPI(irq), GICD_SETSPI_NSR(gic_data.dist_base));
}

static inline void gicd_clear_spi(irq_t irq, bool secure)
{
	if (secure)
		__raw_writel(GICD_SPI(irq), GICD_CLRSPI_SR(gic_data.dist_base));
	else
		__raw_writel(GICD_SPI(irq), GICD_CLRSPI_NSR(gic_data.dist_base));
}

static inline void gicd_configure_group(irq_t irq, uint8_t group)
{
	if (group == GIC_GROUP1NS)
		__raw_setl(GIC_GROUP1(irq), GICD_IGROUPR(gic_data.dist_base, irq));
	else {
		__raw_clearl(GIC_GROUP1(irq), GICD_IGROUPR(gic_data.dist_base, irq));
		if (group == GIC_GROUP1S)
			__raw_setl(GIC_GROUP1(irq), GICD_IGRPMODR(gic_data.dist_base, irq));
		else
			__raw_clearl(GIC_GROUP1(irq), GICD_IGRPMODR(gic_data.dist_base, irq));
	}
}

static inline void gicv3_init_gicd(irq_t max_irq, uint8_t max_prio)
{
	irq_t irq;
	uint8_t ns_prio = GIC_PRIORITY_NS_HIGH(max_prio);

	/* Change ARE_NS=0->1 only when ENABLE_GRP1_NS=0 */
	/* Change ARE_S=0->1 only when ENABLE_GRP0/1_S/NS=0 */
	gicd_clear_ctlr(GICD_ENABLE_GRP0 | GICD_ENABLE_GRP1_S | GICD_ENABLE_GRP1_NS);
	/* Enable affinity routing */
	gicd_set_ctlr(GICD_ARE_S | GICD_ARE_NS);

	/* SPIs default to group1, NS, level triggerred */
#if 0
	for (irq = IRQ_SPI_BASE; irq <= max_irq; irq++) {
		gicd_configure_group(irq, GIC_GROUP1NS);
		gicd_configure_irq(irq, ns_prio, IRQ_LEVEL_TRIGGERED);
	}
#else
	for (irq = IRQ_SPI_BASE; irq <= max_irq; irq += 32) {
		/* Configure SPIs as non-secure Group-1. */
		__raw_writel(~0, GICD_IGROUPR(gic_data.dist_base, irq));
		/* Disable all SPIs */
		__raw_writel(~0, GICD_ICENABLER(gic_data.dist_base, irq));

		/* No need to initialize the following registers */
		/* Set all global interrupts to be level triggered */
		/* Set priority on all global interrupts. */
		/* Deactivate all SPIs */
		/*
		__raw_writel(~0, GICD_ICACTIVER(gic_data.dist_base, irq));
		__raw_writel(~0, GICD_ICPENDR(gic_data.dist_base, irq));
		*/
	}
#endif

	/* Always enable GRP0 and GRP1_S SPIs */
	gicd_set_ctlr(GICD_ENABLE_GRP0 | GICD_ENABLE_GRP1_S | GICD_ENABLE_GRP1_NS);
}

static inline void gicv3_init_gicd_ns(irq_t max_irq, uint8_t max_pri)
{
	/* GRP0 & GRP1 are all GRP1_NS aliases */
	if (__raw_readl(GICD_CTLR(gic_data.dist_base)) & GICD_ARE_NS)
		gicd_set_ctlr(GICD_ENABLE_GRP1);
	else
		gicd_set_ctlr(GICD_ENABLE_GRP0);
}

static inline void gicr_wait_uwp(uint8_t cpu)
{
	/* UWP tracks communication (SGI gen) to GICD */
	while (__raw_readl(GICR_CTLR(gic_data.rdist_base, cpu)) & GICR_UWP)
		;
}

static inline void gicr_wait_rwp(uint8_t cpu)
{
	while (__raw_readl(GICR_CTLR(gic_data.rdist_base, cpu)) & GICR_RWP)
		;
}

static inline void gicr_clear_ctlr(uint8_t cpu, uint32_t value)
{
	__raw_clearl(value, GICR_CTLR(gic_data.rdist_base, cpu));
	/* RWP tracks GICR_CTLR[26:24, 0] clears */
	gicr_wait_rwp(cpu);
}

static inline void gicr_set_ctlr(uint8_t cpu, uint32_t value)
{
	__raw_setl(value, GICR_CTLR(gic_data.rdist_base, cpu));
	/* RWP tracks GICR_CTLR[26:24] sets */
	gicr_wait_rwp(cpu);
}

static inline void gicr_configure_group(uint8_t cpu, irq_t irq, uint8_t group)
{
	if (group == GIC_GROUP1NS)
		__raw_setl(GIC_GROUP1(irq), GICR_IGROUPR0(gic_data.rdist_base, cpu));
	else {
		__raw_clearl(GIC_GROUP1(irq), GICR_IGROUPR0(gic_data.rdist_base, cpu));
		if (group == GIC_GROUP1S)
			__raw_setl(GIC_GROUP1(irq), GICR_IGRPMODR0(gic_data.rdist_base, cpu));
		else
			__raw_clearl(GIC_GROUP1(irq), GICR_IGRPMODR0(gic_data.rdist_base, cpu));
	}
}

static inline void gicr_enable_lpis(uint8_t cpu)
{
	__raw_setl(GICR_ENABLE_LPIS, GICR_CTLR(gic_data.rdist_base, cpu));
}

static inline bool gicr_is_asleep(uint8_t cpu)
{
	return !!(__raw_readl(GICR_WAKER(gic_data.rdist_base, cpu)) & GICR_CHILDREN_ASLEEP);
}

static inline void gicr_enable_irq(uint8_t cpu, irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICR_ISENABLER0(gic_data.rdist_base, cpu));
}

static inline void gicr_disable_irq(uint8_t cpu, irq_t irq)
{
	__raw_writel(GIC_INTERRUPT_ID(irq), GICR_ICENABLER0(gic_data.rdist_base, cpu));
	/* RWP tracks GICR_ICENABLER0 */
	gicr_wait_rwp(cpu);
}

static inline void gicr_enable_all_irqs(uint8_t cpu)
{
	__raw_writel(~0, GICR_ISENABLER0(gic_data.rdist_base, cpu));
}

void gicr_disable_all_irqs(uint8_t cpu)
{
	__raw_writel(~0, GICR_ICENABLER0(gic_data.rdist_base, cpu));
	/* RWP tracks GICR_ICENABLER0 */
	gicr_wait_rwp(cpu);
}

static inline void gicr_mark_awake(uint8_t cpu)
{
	if (gicr_is_asleep(cpu)) {
		__raw_clearl(GICR_PROCESSOR_SLEEP, GICR_WAKER(gic_data.rdist_base, cpu));
		while (gicr_is_asleep(cpu))
			;
	}
}

static inline void gicr_mark_asleep(uint8_t cpu)
{
	__raw_setl(GICR_PROCESSOR_SLEEP, GICR_WAKER(gic_data.rdist_base, cpu));
	while (!gicr_is_asleep(cpu))
		;
}

static inline void gicr_configure_irq(uint8_t cpu, irq_t irq, uint8_t priority, uint8_t trigger)
{
	uint32_t cfg;
	__raw_writel_mask(GIC_PRIORITY(GIC3, irq, priority),
					  GIC_PRIORITY(GIC3, irq, GIC_PRIORITY_MASK),
					  GICR_IPRIORITYR(gic_data.rdist_base, cpu, irq));
	cfg = GIC_TRIGGER(GIC_TRIGGER_EDGE);
	/* Only PPI can be configured as level triggered */
	if (trigger == IRQ_LEVEL_TRIGGERED && irq >= IRQ_PPI_BASE)
		cfg = GIC_TRIGGER(GIC_TRIGGER_LEVEL);
	__raw_writel_mask(GIC_INT_CONFIG(irq, cfg),
					  GIC_INT_CONFIG(irq, GIC_INT_CONFIG_MASK),
					  GICR_ICFGR(gic_data.rdist_base, cpu, irq));
}

static inline void gicv3_init_gicr(uint8_t cpu, irq_t max_irq, uint8_t max_prio)
{
	irq_t irq;
	uint8_t ns_prio = GIC_PRIORITY_NS_HIGH(max_prio);

	gicr_disable_all_irqs(cpu);

	/* SGIs default to group1, NS, edge triggerred */
	/* PPIs default to group1, NS, level triggerred	*/
#if 0
	for (irq = 0; irq < IRQ_SPI_BASE; irq++) {
		gicr_configure_group(cpu, irq, GIC_GROUP1NS);
		gicr_configure_irq(cpu, irq, ns_prio, IRQ_LEVEL_TRIGGERED);
	}
#else
	/* Configure SGIs/PPIs as non-secure Group-1. */
	__raw_writel(~0, GICR_IGROUPR0(gic_data.rdist_base, cpu));
	/* Disable all SGIs/PPIs */
	__raw_writel(~0, GICR_ICENABLER0(gic_data.rdist_base, cpu));

	/* No need to initialize the following registers */
	/* Set priority on SGIs/PPIs. */
	/* Deactivate all SGIs/PPIs */
	/*
	__raw_writel(~0, GICR_ICACTIVER0(gic_data.rdist_base, cpu));
	__raw_writel(~0, GICR_ICPENDR0(gic_data.rdist_base, cpu));
	*/
#endif
	gicr_mark_awake(cpu);
}

void gicv3_enable_irq(irq_t irq) {
	if (irq < IRQ_SPI_BASE)
		gicr_enable_irq(smp_processor_id(), irq);
	else
		gicd_enable_irq(irq);
}

void gicv3_disable_irq(irq_t irq)
{
	if (irq < IRQ_SPI_BASE)
		gicr_disable_irq(smp_processor_id(), irq);
	else
		gicd_disable_irq(irq);
}

static inline void gicv3_configure_irq(irq_t irq, uint8_t priority, uint8_t trigger)
{
	uint8_t cpu = smp_processor_id();
	uint64_t affinity = 0xff;

	if (irq < IRQ_SPI_BASE) {
		gicr_configure_group(cpu, irq, GIC_GROUP0);
		gicr_configure_irq(cpu, irq, priority, trigger);
	} else {
		#ifdef CONFIG_CPU_CORTEX_R52
		gicd_configure_group(irq, GIC_GROUP1NS);
		#else
		gicd_configure_group(irq, GIC_GROUP0);
		#endif
		gicd_configure_irq(irq, priority, trigger);

		/*
		 * Set affinity to the calling CPU. ARE must be enabled.
		 */
		#ifdef CONFIG_CPU_CORTEX_R52
		affinity = cpu & ~(affinity << 24);
		#else
		affinity = read_sysreg(MPIDR_EL1) & ~(affinity << 24);
		__raw_writeq(affinity, GICD_IROUTER(gic_data.dist_base, irq));
		#endif
	}
}

static struct irq_chip gic3_chip = {
	.max_irq = NR_QGIC3_IRQS - 1,
	.enable = gicv3_enable_irq,
	.disable = gicv3_disable_irq,
	.clear = gicd_clear_irq,
	.trigger = gicd_trigger_irq,
	.config = gicv3_configure_irq,
};

void gic3_handle_irq(void)
{
	gicv3_handle_irq();
}

void gic3_early_init(void)
{
	uint8_t cpu = smp_processor_id();
	irq_t max_irq;
	uint8_t max_pri = GIC_PRIORITY_MAX(GIC3);

	max_irq = GICD_TYPER_IRQS(__raw_readl(GICD_TYPER(gic_data.dist_base)));

	if (max_irq >= IRQ_ACK_SEL1)
		max_irq = IRQ_ACK_SEL1 - 1;

	gic3_chip.max_irq = max_irq;

	if (cpus_boot_cpu == cpu) {
		printf("GICv%d w/ max_irq %d\n",
			GICD_PIDR2_ArchRev(__raw_readl(GICD_PIDR2(gic_data.dist_base))),
			max_irq);

		gicv3_init_gicd(max_irq, max_pri);
		gicv3_init_gits(max_irq);
	}

/* if GIC600, power on the redistributor first */
#ifdef CONFIG_GIC600
	gic600_pwr_on((void*)GIC600_GICR_BASE(cpu));
#endif

	gicv3_init_gicr(cpu, max_irq, max_pri);
	gicv3_init_gicc(max_irq, max_pri);
}

void gic3_init(void *dist_base, 	void *rdist_base)
{
	uint8_t cpu = smp_processor_id();
	gic_data.dist_base = dist_base;
	gic_data.rdist_base = rdist_base;

	gic3_early_init();
	if (cpus_boot_cpu == cpu) {
		irqc_register(&gic3_chip);
	}
}

void* gicv3_get_rdist_base(void)
{
	return gic_data.rdist_base;
}
