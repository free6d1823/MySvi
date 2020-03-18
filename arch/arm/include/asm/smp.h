/*
 */
#ifndef __ARMV7M_SMP_H_INCLUDE__
#define __ARMV7M_SMP_H_INCLUDE__

#include <target/memory.h>


#ifdef __ASSEMBLY__
#else

static inline uint8_t __smp_processor_id(void)
{
	uintptr_t t;

	asm volatile ("MRC p15, 0, %0, c0, c0, 5\n\t" : "=r" (t));
	return (uint8_t)(t & 0xf);
}

#define __hmp_processor_id()	0

#endif

#endif /* __ARMV7M_SMP_H_INCLUDE__ */
