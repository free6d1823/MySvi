/*
 */
#include <target/irq.h>
#include <target/console.h>
#include <target/spinlock.h>

#ifndef CONFIG_IRQ_POLLING
#ifndef MAX_VECTORS
#define MAX_VECTORS    NR_IRQS
#endif

static struct {
    irq_handler handler;
    void* ctx;
} irq_handlers[MAX_VECTORS];
static irq_t irq_nr_table[MAX_VECTORS] = {
    [0 ...  MAX_VECTORS-1] = DEFAULT_NO_IRQ_NUM
    };
static uint16_t irq_nr_regs = 0;
static DEFINE_SPINLOCK(irq_lock);

void irq_lock_irq(void)
{
    spin_lock(&irq_lock);
}

void irq_unlock_irq(void)
{
    spin_unlock(&irq_lock);
}

/* 0 ~ NR_IRQS-1 is allowed, DEFAULT_NO_IRQ_NUM is forbidden! */
void irq_register_vector(sirq_t sirq, irq_handler h, void *ctx)
{
    uint16_t curr = 0;

    BUG_ON(sirq >= NR_IRQS || NULL == h);

    irq_lock_irq();

    /* find empty to fill first */
    for (curr = 0; curr < irq_nr_regs; curr++) {
        if (DEFAULT_NO_IRQ_NUM == irq_nr_table[curr] \
         && NULL == irq_handlers[curr].handler) {
            break;
        }
    }

    BUG_ON(curr == MAX_VECTORS);
    irq_handlers[curr].handler = h;
    irq_handlers[curr].ctx = ctx;
    irq_nr_table[curr] = sirq;

    if (curr >= irq_nr_regs) {
        irq_nr_regs++;
    }

    irq_unlock_irq();

    return;
}

void irq_unregister_vector(sirq_t sirq)
{
    uint16_t    curr = 0;

    BUG_ON(sirq >= NR_IRQS);
    irq_lock_irq();
    for (curr = 0; curr < irq_nr_regs; curr++) {
        if (sirq == irq_nr_table[curr]) {
            irq_nr_table[curr] = DEFAULT_NO_IRQ_NUM;
            irq_handlers[curr].handler = NULL;
            irq_handlers[curr].ctx = NULL;
        }
    }
    irq_unlock_irq();
}

bool do_IRQ(sirq_t sirq)
{
    uint16_t     curr    = 0;
    irq_handler handler = NULL;

    BUG_ON(sirq >= NR_IRQS);
    irq_lock_irq();
    for (curr = 0; curr < irq_nr_regs; curr++) {
        if (sirq == irq_nr_table[curr]) {
            handler = irq_handlers[curr].handler;
            irq_unlock_irq();

            if (handler)
                handler(sirq, irq_handlers[curr].ctx);
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
