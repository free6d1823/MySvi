/*
 */
#include <asm/sysreg.h>
#include <target/timer.h>
#include <target/irq.h>
#include <target/smp.h>

/*
 * The always-on domain controls:
 * sleep timer, power controller, clock controller, interrupt controller,
 * watchdog timer, global timer, registers, SPMI interface.
 */

uint64_t __systick_read(void)
{
	return read_sysreg(CNTPCT_EL0);
}

void __systick_mask_irq(void)
{
	uint32_t value;

	value = read_sysreg(CNTPS_CTL_EL1);
	value |= CNTX_CTL_IMASK;
	write_sysreg(value, CNTPS_CTL_EL1);
}

void __systick_unmask_irq(void)
{
	uint32_t value;

	value = read_sysreg(CNTPS_CTL_EL1);
	value &= ~CNTX_CTL_IMASK;
	write_sysreg(value, CNTPS_CTL_EL1);
}

static inline void __systick_reset_counter(void)
{
	if (smp_processor_id() >= NR_CPUS)
		write_sysreg(0, CNTVOFF_EL2);
}

void __systick_init_counter(void)
{
	 /*set CNTFRQ_EL0 register equal to the clock frequency of the system counter*/
	write_sysreg(ARCH_TIMER_FREQUENCY, CNTFRQ_EL0);

	/* CNTPCT_EL0 is always accessible from EL3,
	 * Non-secure EL2 and Secure EL1 states.
	 */
	/* allow non-secure EL1: CNTHCTL_EL2=EL1PCTEN
	 * allow     secure EL0: CNTKCTL_EL1=EL0PCTEN
	 * allow non-secure EL0: CNTHCTL_EL2=EL1PCTEN
	 */
	write_sysreg(CNTHCTL_EL1PCTEN, CNTHCTL_EL2);
	write_sysreg(CNTKCTL_EL0PCTEN, CNTKCTL_EL1);
	/* No virtual counter offset */
	__systick_reset_counter();
}


ktime_t tsc_hw_read_counter(void)
{
	ktick_t ticks = read_sysreg(CNTPCT_EL0);

	return (ktime_t)(ticks / TICKS_TO_MICROSECONDS);
}


void __systick_init_timer(void)
{
	write_sysreg(-1, CNTPS_CVAL_EL1);
	/* allow non-secure EL0 and EL1: CNTHCTL_EL2=EL1PCEN */
	write_sysreg(CNTHCTL_EL1PCEN | read_sysreg(CNTHCTL_EL2),
		     CNTHCTL_EL2);
	write_sysreg(CNTX_CTL_ENABLE, CNTPS_CTL_EL1);
}

bool gpt_hw_irq_poll(void)
{
	uint64_t val;

	val = read_sysreg(CNTPS_CTL_EL1);
	if (val & CNTX_CTL_ISTATUS) {
		val &= ~CNTX_CTL_ISTATUS;
		write_sysreg(val, CNTPS_CTL_EL1);
		return true;
	}
	return false;
}

void gpt_hw_oneshot_timeout(ktime_t match_val)
{
	ktick_t match_val_ticks;

	match_val_ticks = match_val * TICKS_TO_MICROSECONDS;
	write_sysreg(match_val_ticks, CNTPS_CVAL_EL1);
	__systick_unmask_irq();
}



void mpm_global_counter_enable(void)
{
	#ifdef ARCH_CENTRIQ
	/*HWIO_OUTF(MPM_CONTROL_CNTCR, EN, 0x1);*/
	#endif
}

void tsc_hw_ctrl_init(void)
{
	if (smp_processor_id() >= NR_CPUS)
		mpm_global_counter_enable();
	__systick_init_counter();
}

static void timer_handle_irq(irq_t irq, void *ctx)
{
	__systick_mask_irq();
	timer_handle_interrupt();
}

#ifndef CONFIG_IRQ_POLLING
void gpt_hw_irq_init(void)
{
	irq_t tirq;
	uint8_t cpu = smp_processor_id();
	tirq = IRQ_PTIMER3;

	if (cpu == cpus_boot_cpu)
		irq_register_vector(tirq, timer_handle_irq, NULL);

	irqc_configure_irq(tirq, 0, IRQ_LEVEL_TRIGGERED);
	irqc_enable_irq(tirq);
}
#endif

void gpt_hw_ctrl_init(void)
{
	__systick_init_timer();
}

