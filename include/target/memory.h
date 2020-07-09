/*
 */
#ifndef __TESTOS_MEMORY_H_INCLUDE__
#define __TESTOS_MEMORY_H_INCLUDE__

#include <asm/memory.h>
#include <asm/cpus.h>
#include <asm/io.h>


#define __HEAD		.section	".head.text","ax"
#define __INIT		.section	".init.text","ax"

#ifndef __ASSEMBLY__
#include <stdint.h>

extern char __stext[];
extern char __etext[];
extern char __sdata[];
extern char __edata[];
extern char __bss_start[];
extern char __bss_end[];

#define TEXT_START	((uintptr_t)__stext)
#define TEXT_END	((uintptr_t)__etext)

#define DATA_START	((uintptr_t)__sdata)
#define DATA_END	((uintptr_t)__edata)

#endif

#ifndef PAGE_SHIFT
#define PAGE_SHIFT			12 /*binding with PAGE_SIZE*/
#endif

/* STACK is for per CPU */
#define STACK_SHIFT		12
#define STACK_SIZE		(1 << STACK_SHIFT)
#define STACK_START(x)	(STACKS_START + (x) * STACK_SIZE)

/* STACKS is for all CPUs */
#define STACKS_START	(STACKS_END - STACKS_SIZE)
#define STACKS_END		SVI_RAM_END
#define STACKS_SIZE		(STACK_SIZE * MAX_CPU_NUM)

#ifndef HEAP_START
#define HEAP_START	DATA_END
#endif
#ifndef HEAP_END
#define HEAP_END	STACKS_START
#endif

#define ALIGN_UP(p, a)	(((p)+((a)-1)) & ~((a)-1))

/* BSS_ALIGN must be a multiple of 16  */
#define BSS_ALIGN	(16 * 4)

#endif /* __TESTOS_MEMORY_H_INCLUDE__ */
