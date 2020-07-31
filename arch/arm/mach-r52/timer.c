/*
 */
/*#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
*/
#include <target/timer.h>
#include <asm/reg.h>
#include <asm/sysreg.h>
#include <target/irq.h>
#include <target/smp.h>

//#include <asm/mach/memory.h>



void __arch_counter_init(void)
{
	/*set the CNTFRQ equal to the clock freqency of the system counter*/
	//write_sysreg(ARCH_TIMER_FREQUENCY, CNTFRQ); The code is moved to head.S

	/*
	 * Physical counter is always accessible from secure
	 * PL1 modes and from Non-secure Hyp mode.
	*/

	 /*enable the access to physical counter from Non-secure EL1 modes */
	 //write_sysreg(CNTHCTL_PL1PCTEN, CNTHCTL); The code is moved to head.S .

	/*enable  the access to physical counter from secure user mode. */
	 write_sysreg(CNTKCTL_PL0PCTEN | read_sysreg(CNTKCTL), CNTKCTL);

	 /*Both the above two are enabled, the physical counter can be accessed
	*from Non-secure User mode
	*/
	/*
	*The virtual counter is always accesslble from Secure PL1 modes and from
	*Non-secure EL1 and EL2modes.
	*/

	/*enable the access to the virtual counter from EL0*/
	 write_sysreg(CNTKCTL_PL0VCTEN | read_sysreg(CNTKCTL), CNTKCTL);


}

void __arch_timer_init(void)
{
	/*Init the compare-value of L1 physical timer. -1 means the maximum postive value
	 * to make the timer will not generate the interrupt until the right setting.
	 */
	/*do we need to mask the timer interrupt to disable the interrupt*/
	write_sysreg(-1, CNTP_CVAL);

	/*Enable the access to the non-secure EL1 physical timer
	 *from Non-secure EL1 mode and and EL0 mode.
	 */
	write_sysreg(CNTKCTL_PL0PTEN | read_sysreg(CNTKCTL), CNTKCTL);
	write_sysreg(0x01 | read_sysreg(CNTPCTL), CNTPCTL);
}

void __arch_timer_mask_ptimer_irq(void)
{
	uint32_t val = 0;

	val = read_sysreg(CNTP_CTL);
	val |= CNTX_CTL_IMASK;
	write_sysreg(val, CNTP_CTL);
}

void __arch_timer_unmask_ptimer_irq(void)
{
	uint32_t val = 0;

	val = read_sysreg(CNTP_CTL);
	val &= ~CNTX_CTL_IMASK;
	write_sysreg(val, CNTP_CTL);
}

bool gpt_hw_irq_poll(void)
{
	uint32_t val;
	/* read the value and check the istatus of whether the interrupt has been
	* triggered.
	*/
	val = read_sysreg(CNTP_CTL);
	if(val & CNTX_CTL_ISTATUS)
	{
		val &= ~CNTX_CTL_ISTATUS;
		write_sysreg(val, CNTP_CTL);
		return true;
	}

	return false;
}

/*arch_timer_comparevalue_set()*/
void gpt_hw_oneshot_timeout(ktime_t match_val)
{
	ktick_t match_val_ticks;

	match_val_ticks = match_val * TICKS_TO_MICROSECONDS;
	write_sysreg(match_val_ticks, CNTP_CVAL);
	__arch_timer_unmask_ptimer_irq();

}

ktime_t tsc_hw_read_counter(void)
{
	ktick_t ticks = read_sysreg(CNTPCT);
	return (ktime_t)(ticks / TICKS_TO_MICROSECONDS);
}

/*arch_counter_ctrl_init*/
void tsc_hw_ctrl_init(void)
{
	__arch_counter_init();
}

void timer_handle_irq(irq_t irq, void* ctx)
{
  __arch_timer_mask_ptimer_irq();
  timer_handle_interrupt();
}

#ifndef CONFIG_IRQ_POLLING
void gpt_hw_irq_init(void)
{
	irq_t irqid;
	uint8_t cpuid = smp_processor_id();
	irqid = 30/* IRQ_PTIMER3*/;

	/*For the interrupt handler, all cores use the same one*/
	if(cpuid == cpus_boot_cpu)
		irq_register_vector(irqid, timer_handle_irq, NULL);

	irqc_configure_irq(irqid, 0, IRQ_LEVEL_TRIGGERED);
	irqc_enable_irq(irqid);
}
#endif

/*arch_timer_ctrl_init*/
void gpt_hw_ctrl_init(void)
{
	__arch_timer_init();

}

