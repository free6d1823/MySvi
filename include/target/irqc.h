/*
 */
#ifndef __IRQC_DRIVER_H_INCLUDE__
#define __IRQC_DRIVER_H_INCLUDE__

#define MAX_IRQ_CHIPS	2
#define INVALID_IRQC	MAX_IRQ_CHIPS

typedef uint8_t irqc_t;
typedef void (*irq_handler)(irq_t irq, void *ctx);

struct irq_chip {
	irq_t max_irq;
	/* must be SMP safe, must be interrupt safe */
	void (*enable)(irq_t irq);
	/* must be SMP safe, must be interrupt safe */
	void (*disable)(irq_t irq);
	/* must be SMP safe, must be interrupt safe */
	void (*clear)(irq_t irq);
	/* must be SMP safe, must be interrupt safe */
	void (*trigger)(irq_t irq);
	void (*config)(irq_t irq, uint8_t priority, uint8_t trigger);
};

void irqc_register(struct irq_chip *irqc);
void irqc_enable_irq(irq_t irq);
void irqc_disable_irq(irq_t irq);
void irqc_clear_irq(irq_t irq);
void irqc_trigger_irq(irq_t irq);
void irqc_configure_irq(irq_t irq, uint8_t priority, uint8_t trigger);
void irqc_handle_irq(void);
void irqc_init(void);

#endif /* __IRQC_DRIVER_H_INCLUDE__ */
