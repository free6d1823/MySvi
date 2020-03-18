#include <stdio.h>
#include <target/utils.h>
#include <target/irq.h>
#include <target/smp.h>
#include <asm/ptrace.h>

static void show_regs(struct pt_regs *regs)
{
	int i;

	printf("SPSR: %04lx\n", regs->ARM_cpsr);
	printf("ELR:  %04lx\n", regs->ARM_pc);

	for (i = 0; i < 15; i+= 2)
		printf("r%-2d: %08x r%-2d: %08x\n",
			   i, regs->uregs[i], i+1, regs->uregs[i+1]);
	printf("\n");
}

static const char *handler[]= {
	"prefetch abort",
	"data abort",
	"address exception",
	"interrupt",
	"undefined instruction",
};

void bad_mode(struct pt_regs *regs, unsigned int esr, int reason)
{
	printf("Bad mode in %s handler detected on CPU%d\n",
		handler[reason], smp_processor_id());

	show_regs(regs);

	for (;;);
}

#ifdef CONFIG_IRQ_POLLING
void do_irq(struct pt_regs *pt_regs)
{
}
#else
void do_irq(struct pt_regs *pt_regs)
{
	irqc_handle_irq();
}
#endif
