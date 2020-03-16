/*
 */
#include <target/spinlock.h>
#include <target/smp.h>
#include <target/cpus.h>

#ifdef CONFIG_MINI_EXCLUSIVE_ACCESS

#include <asm/sysreg.h>
#define spin_lock_check() do {\
		if (read_sysreg(currentel) != 0xc) return;\
		if (!(read_sysreg(SCTLR_EL3) & SCTLR_M)) return;\
	} while (0)

#else

#define spin_lock_check()

#endif

#ifdef CONFIG_SMP
void spin_lock(spinlock_t *lock)
{
	spin_lock_check();

	__spin_lock(lock);
}

void spin_unlock(spinlock_t *lock)
{
	spin_lock_check();

	__spin_unlock(lock);
}
#endif
