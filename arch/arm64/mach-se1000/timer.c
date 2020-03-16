#include <target/irq.h>
#include <target/smp.h>

/*
 * The always-on domain controls:
 * sleep timer, power controller, clock controller, interrupt controller,
 * watchdog timer, global timer, registers, SPMI interface.
 */
void mpm_global_counter_enable(void)
{
}

void tsc_hw_ctrl_init(void)
{
	if (smp_processor_id() >= NR_CPUS)
		mpm_global_counter_enable();
	__systick_init_counter();
}

static void tmr_handle_irq(void)
{
	__systick_mask_irq();
	timer_handle_interrupt();
}

#ifndef CONFIG_IRQ_POLLING
void gpt_hw_irq_init(void)
{
	uint8_t cpu = smp_processor_id();

	irq_t tirq = IRQ_PTIMER3;

	if (cpu == cpus_boot_cpu)
		irq_register_vector(tirq, tmr_handle_irq);

	irqc_configure_irq(tirq, 0, IRQ_LEVEL_TRIGGERED);
	irqc_enable_irq(tirq);
}
#endif

void gpt_hw_ctrl_init(void)
{
	__systick_init_timer();
}
