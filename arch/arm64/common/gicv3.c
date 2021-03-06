/*
 */
#include <stdio.h>
#include <target/irq.h>
#include <target/smp.h>
#include <target/gicv3.h>
#include <asm/reg.h>

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
	uint32_t iar = read_sysreg(ICC_IAR0_EL1);

	*irq = ICC_GET_IRQ(iar);
	*cpu = smp_processor_id();
}

void gicv3_end_irq(irq_t irq, uint8_t cpu)
{
	write_sysreg(ICC_SET_IRQ(irq), ICC_EOIR0_EL1);
}

void gicv3_handle_irq()
{
	irq_t irq;
	uint8_t cpu;

	gicv3_begin_irq(&irq, &cpu);

	if (!gic_sanitize_acked_irq(irq))
		return;

	if (irq >= IRQ_PPI_BASE) {
		if (!do_IRQ(irq))
			irqc_disable_irq(irq);
	} else {
		handle_IPI(irq);
	}

	gicv3_end_irq(irq, cpu);
}

void gicv3_init_gits(irq_t max_irq)
{
}

void gicc_enable_priority_mask(uint8_t priority)
{
	write_sysreg(ICC_PMHE, ICC_CTLR_EL3);
	write_sysreg(priority, ICC_PMR_EL1);
}

void gicc_disable_priority_mask(void)
{
	write_sysreg(GIC_PRIORITY_IDLE, ICC_PMR_EL1);
	write_sysreg(read_sysreg(ICC_CTLR_EL3) & ~ICC_PMHE,
		     ICC_CTLR_EL3);
}

void gicv3_init_gicc(irq_t max_irq, uint8_t max_prio)
{
	unsigned int scr;
	unsigned int icc_sre;

	/* Disable the legacy interrupt bypass and enable system register
	 * access for EL3 and allow lower exception levels.
	 */
	icc_sre = ICC_DIB | ICC_DFB;
	icc_sre |= (ICC_SRE_ENABLE | ICC_SRE_SRE);
	write_sysreg(read_sysreg(ICC_SRE_EL3) | icc_sre, ICC_SRE_EL3);

	/* 1. Switch to non-secure state;
	 * 2. Write non-secure ICC_SRE_EL1 and ICC_SRE_EL2 registers;
	 * 3. Switch to secure state.
	 */
	scr = read_sysreg(SCR_EL3);
	write_sysreg(scr | SCR_NS, SCR_EL3);
	isb();
	write_sysreg(read_sysreg(ICC_SRE_EL2) | icc_sre, ICC_SRE_EL2);
	write_sysreg(ICC_SRE_SRE, ICC_SRE_EL1);
	isb();
	write_sysreg(scr & (~SCR_NS), SCR_EL3);
	isb();

	gicc_enable_priority_mask(max_prio);

	write_sysreg(ICC_ENABLE_GRP, ICC_IGRPEN0_EL1);
	write_sysreg(read_sysreg(ICC_IGRPEN1_EL3) |
		     ICC_ENABLE_GRP1_S, ICC_IGRPEN1_EL3);

	/* Write the secure ICC_SRE_EL1 register */
	write_sysreg(ICC_SRE_SRE, ICC_SRE_EL1);
	isb();
}

#define MPIDR_TO_SGI_RS(mpidr)	(MPIDR_RS(mpidr) << ICC_RS_OFFSET)
#define MPIDR_TO_SGI_CLUSTER_ID(mpidr)	((mpidr) & ~0xFUL)

#define MPIDR_TO_SGI_AFFINITY(cluster_id, level) \
	(MPIDR_AFFINITY_LEVEL(cluster_id, level) \
		<< ICC_AFF## level ##_OFFSET)

void gicv3_trigger_sgi(uint8_t irqnr, uint16_t cpu)
{
	uint64_t cluster_id, val;
	uint16_t target;

	cluster_id = get_mpidr(cpu);
	target = 1 << (cluster_id & 0xf);

	cluster_id = MPIDR_TO_SGI_CLUSTER_ID(cluster_id);

	val = (MPIDR_TO_SGI_AFFINITY(cluster_id, 3)	|
	       MPIDR_TO_SGI_AFFINITY(cluster_id, 2)	|
	       irqnr << ICC_INTID_OFFSET		    |
	       MPIDR_TO_SGI_AFFINITY(cluster_id, 1)	|
	       MPIDR_TO_SGI_RS(cluster_id)		    |
	       (target << ICC_TARGET_LIST_OFFSET));

	write_sysreg(val, ICC_SGI0R_EL1);
	asm volatile("isb" : : : "memory");
}
