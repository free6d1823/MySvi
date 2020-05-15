#include <target/irq.h>
#include <asm/nvic.h>
#include <target/spinlock.h>
#include <stdio.h>

#define INTLINESNUM(ICTR) ((ICTR) & 0xf)

#define VECTACTIVE(ICSR) ((ICSR) & 0x1ff)

static inline void nvic_enable_irq(irq_t irq)
{
	NVIC_EnableIRQ(irq);
}
static inline void nvic_disable_irq(irq_t irq)
{
	NVIC_DisableIRQ(irq);
}
static inline void nvic_enable_all_irqs(irq_t max_irq)
{
	irq_t irq;
	for (irq = 0; irq <= max_irq; irq += 32) {
		NVIC_EnableIRQ(irq);
	}
}
static inline void nvic_disable_all_irqs(irq_t max_irq)
{
	irq_t irq;
	for (irq = 0; irq <= max_irq; irq += 32) {
		NVIC_DisableIRQ(irq);
	}
}
static inline void nvic_trigger_irq(irq_t irq)
{
	NVIC_SetPendingIRQ(irq);
}
static inline void nvic_clear_irq(irq_t irq)
{
	NVIC_ClearPendingIRQ(irq);
}
static inline void nvic_configure_irq(irq_t irq, uint8_t priority, uint8_t trigger)
{
	trigger = trigger;
	NVIC_SetPriority(irq, priority);
}

struct irq_chip nvic = {
	.max_irq = 256 - 1,
	.enable = nvic_enable_irq,
	.disable = nvic_disable_irq,
	.clear = nvic_clear_irq,
	.trigger = nvic_trigger_irq,
	.config = nvic_configure_irq,
};

void nvic_init()
{
	printf("NVIC irq number %d\n", 32 * (INTLINESNUM(SCnSCB->ICTR) + 1));
	irqc_register(&nvic);
}


void nvic_handle_irq(void)
{
	irq_t irq = VECTACTIVE(SCB->ICSR);

	if (irq < 16) {
		printf("bug on nvic_handle_irq\n");
		return;
	}

	irq -= 16;

	if (!do_IRQ(irq))
		nvic_disable_irq(irq);
}
