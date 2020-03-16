/*
 */
#ifndef __ARM64_SPINLOCK_H_INCLUDE__
#define __ARM64_SPINLOCK_H_INCLUDE__

#ifndef __ASSEMBLY__
#include <stdint.h>
#include <target/compiler.h>
#include <target/smp.h>

typedef struct __arch_spinlock {
	volatile uint32_t lock __aligned(SMP_CACHE_BYTES);
} arch_spinlock_t;

#define ARCH_SPINLOCK_INIT	\
	.lock = 0

void __spin_lock(spinlock_t *lock);
void __spin_unlock(spinlock_t *lock);
int __spin_trylock(spinlock_t *lock);
#else
/* Spin lock definitions for use in assembly */
#define SPINLOCK_ASM_ALIGN	2

.macro define_asm_spinlock _name:req
	.align	SPINLOCK_ASM_ALIGN
	\_name:
	.long	0
.endm
#endif

#endif /* __ARM64_SPINLOCK_H_INCLUDE__ */
