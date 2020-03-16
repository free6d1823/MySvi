/*
 */
#ifndef __ARM64_SMP_H_INCLUDE__
#define __ARM64_SMP_H_INCLUDE__

#include <target/memory.h>


#ifdef __ASSEMBLY__
#ifndef LINKER_SCRIPT
.macro asm_smp_processor_id _tmp:req, _res=x0
	mov	\_res, sp
	ldr	\_tmp, =STACKS_START
	sub	\_res, \_res, \_tmp
	ubfx	\_res, \_res, #STACK_SHIFT, #(32 - STACK_SHIFT)
.endm
#endif
#else
static inline uint8_t __smp_processor_id(void)
{
	uintptr_t t;

	asm volatile ("mov %0, sp\n\t" : "=r" (t));
	return (uint8_t)((t - STACKS_START) >> 12);
}

static inline uint8_t __hmp_processor_id(void)
{
	uint8_t cpu = __smp_processor_id();

	return cpu >= NR_CPUS ? NR_CPUS : cpu;
}

static inline uintptr_t __smp_processor_stack_top(void)
{
	uintptr_t t;

	asm volatile ("mov %0, sp\n\t" : "=r" (t));
	return ALIGN_UP(t, STACK_SIZE);
}

unsigned int plat_my_core_pos(void);
#endif

#endif /* __ARM64_SMP_H_INCLUDE__ */
