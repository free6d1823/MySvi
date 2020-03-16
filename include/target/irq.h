/*
 */
#ifndef __IRQ_H_INCLUDE__
#define __IRQ_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>
#include <asm/irq.h>

#define IRQ_LEVEL_TRIGGERED	0
#define IRQ_EDGE_TRIGGERED	1

#define MAX_VECTORS		16

#if NR_IRQS <= 256
typedef uint8_t irq_t;
#elif NR_IRQS < 65536
typedef uint16_t irq_t;
#endif

typedef uint32_t sirq_t;

#include <target/irqc.h>

#define irq_local_enable()		irq_hw_flags_enable()
#define irq_local_disable()		irq_hw_flags_disable()
#define irq_local_save(__flags__)	irq_hw_flags_save(__flags__)
#define irq_local_restore(__flags__)	irq_hw_flags_restore(__flags__)

#ifdef CONFIG_IRQ_POLLING
#define irq_register_vector(__sirq, __isr)
#define do_IRQ(__sirq)			false
#define irq_lock_irq()
#define irq_unlock_irq()
#else
void irq_lock_irq(void);
void irq_unlock_irq(void);
void irq_register_vector(sirq_t sirq, irq_handler isr);
bool do_IRQ(sirq_t sirq);
#endif
void irq_init(void);

#endif /* __IRQ_H_INCLUDE__ */
