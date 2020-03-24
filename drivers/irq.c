/*
 */
#include <target/irq.h>
#include <target/console.h>
#include <target/spinlock.h>

#ifndef CONFIG_IRQ_POLLING
#ifndef MAX_VECTORS
#define MAX_VECTORS	NR_IRQS
#endif

static irq_handler irq_handlers[MAX_VECTORS];
static irq_t irq_nr_table[MAX_VECTORS];
static uint8_t irq_nr_regs = 0;
static DEFINE_SPINLOCK(irq_lock);

void irq_lock_irq(void)
{
	spin_lock(&irq_lock);
}

void irq_unlock_irq(void)
{
	spin_unlock(&irq_lock);
}

#ifdef CONFIG_NVIC
extern uintptr_t __isr_vector[];    /* vector table is in a fix position - startup.S*/

void irq_register_vector(sirq_t sirq, irq_handler h)
{
	uint32_t *base = (uint32_t *)&(__isr_vector);
	base += 16;
	*(base+sirq) = (uint32_t)h;
}
#else
/* 0 ~ NR_IRQS-1 is allowed. */
void irq_register_vector(sirq_t sirq, irq_handler h)
{
	uint8_t curr;

	BUG_ON(sirq <= 0 || sirq >= NR_IRQS);

	irq_lock_irq();
	curr = irq_nr_regs;
	BUG_ON(curr == MAX_VECTORS);
	irq_handlers[curr] = h;
	irq_nr_table[curr] = sirq;
	irq_nr_regs++;
	irq_unlock_irq();
}
#endif

bool do_IRQ(sirq_t sirq)
{
	uint8_t curr;
	irq_handler handler;

	BUG_ON(sirq >= NR_IRQS || sirq < 0);
	irq_lock_irq();
	for (curr = 0; curr < irq_nr_regs; curr++) {
		if (sirq == irq_nr_table[curr]) {
			handler = irq_handlers[curr];
			irq_unlock_irq();
			if (handler)
				handler();
			else
				printf("BUG: irq %d handler is NULL\n", sirq);
			return true;
		}
	}
	irq_unlock_irq();
	printf("BUG: bad_interrupt %d\n", sirq);
	return false;
}

void irq_init(void)
{
	irq_local_disable();

	irqc_init();

	irq_local_enable();
}

#else
void irq_init(void)
{
}
#endif /* CONFIG_IRQ_POLLING */
