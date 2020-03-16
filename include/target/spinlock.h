/*
 */
#ifndef __TESTOS_SPINLOCK_H_INCLUDE__
#define __TESTOS_SPINLOCK_H_INCLUDE__

#include <target/memory.h>
#include <target/barrier.h>

#ifndef __ASSEMBLY__

#define spinlock_t		arch_spinlock_t
#define spin_trylock(lock)	__spin_trylock(lock)

#define DEFINE_SPINLOCK(_lock)		\
	spinlock_t _lock = {		\
		ARCH_SPINLOCK_INIT	\
	};

#include <asm/spinlock.h>

#ifdef CONFIG_SMP
void spin_lock(spinlock_t *lock);
void spin_unlock(spinlock_t *lock);
#else
#define spin_lock(lock)
#define spin_unlock(lock)
#endif

#include <target/irq.h>

#define spin_lock_irqsave(lock, flags)	\
	do {				\
		irq_local_save(flags);	\
		spin_lock(lock);		\
	} while (0)

#define spin_unlock_irqrestore(lock, flags) \
	do {					\
		spin_unlock(lock);		\
		irq_local_restore(flags);	\
	} while (0)

#endif /* __ASSEMBLY__ */

#endif /* __TESTOS_SPINLOCK_H_INCLUDE__ */
