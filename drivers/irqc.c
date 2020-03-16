/*
 */
#include <target/irq.h>
#include <target/console.h>
#ifdef CONFIG_GICv3
#include <asm/gic3.h>
#endif
#ifdef CONFIG_GICv2
#include <asm/mach/qgic2.h>
#endif
#ifdef CONFIG_NVIC
#include <asm/mach/nvic.h>
#endif

struct irq_chip *g_irqc;

void irqc_register(struct irq_chip *irqc)
{
	irq_lock_irq();
	g_irqc = irqc;
	irq_unlock_irq();

	return;
}

void irqc_enable_irq(irq_t irq)
{
	g_irqc->enable(irq);
}

void irqc_disable_irq(irq_t irq)
{
	g_irqc->disable(irq);
}

void irqc_clear_irq(irq_t irq)
{
	g_irqc->clear(irq);
}

void irqc_trigger_irq(irq_t irq)
{
	g_irqc->trigger(irq);
}

void irqc_configure_irq(irq_t irq, uint8_t priority, uint8_t trigger)
{
	irq_lock_irq();
	g_irqc->config(irq, priority, trigger);
	irq_unlock_irq();
}

void irqc_handle_irq()
{
#ifdef CONFIG_GICv3
	gic3_handle_irq();
#endif
#ifdef CONFIG_GICv2
	qgic2_handle_irq();
#endif
#ifdef CONFIG_NVIC
	nvic_handle_irq();
#endif
	return;
}

void irqc_init()
{
#ifdef CONFIG_GICv3
	gic3_init((void*)GICD_gic3_BASE, (void*)GICR_gic3_BASE);
#endif

#ifdef CONFIG_GICv2
	qgic2_init((void*)GICD_qgic2_BASE);;
#endif

#ifdef CONFIG_NVIC
	nvic_init();
#endif

	return;
}
