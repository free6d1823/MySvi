/*
 */
#ifndef __IRQ_ARM_H_INCLUDE__
#define __IRQ_ARM_H_INCLUDE__

#include <stdint.h>

#include <asm/mach/irq.h>

#ifdef CONFIG_IRQ_POLLING
#define irq_hw_flags_save(x)
#define irq_hw_flags_restore(x)
#define irq_hw_flags_enable()
#define irq_hw_flags_disable()
#else
#define irq_hw_flags_save(x)					\
	__asm__ __volatile__(					\
	"mrs	%0, cpsr		// local_irq_save\n"	\
	"cpsid  i"					\
	"cpsid  f"                  \
	: "=r" (x) : : "memory")
#define irq_hw_flags_restore(x)					\
	__asm__ __volatile__(					\
	"msr	cpsr, %0		// local_irq_restore\n"	\
	: : "r" (x) : "memory")
#define irq_hw_flags_enable()					\
	__asm__ __volatile__(					\
	"cpsie  i		// local_irq_enable\n"	\
	"cpsie  f"                  \
	: : : "memory")
#define irq_hw_flags_disable()					\
	__asm__ __volatile__(					\
	"cpsid  i		// local_irq_disable\n"	\
	"cpsid  f"                  \
	: : : "memory")
#endif

#endif /* __IRQ_ARM_H_INCLUDE__ */
