/*
 */
#ifndef __SYSREG_ARM_H_INCLUDE__
#define __SYSREG_ARM_H_INCLUDE__

#include <stdint.h>
#include <target/regdef.h>

/* Unlike read_cpuid, calls to read_sysreg are never expected to be
 * optimized away or replaced with synthetic values.
 */
#define __ACCESS_CP15(CRn, Op1, CRm, Op2)	\
		"mrc", "mcr", __stringify(p15, Op1, %0, CRn, CRm, Op2), uint32_t
#define __ACCESS_CP15_64(Op1, CRm)		\
		"mrrc", "mcrr", __stringify(p15, Op1, %Q0, %R0, CRm), uint64_t

#define __read_sysreg(r, w, c, t) ({				\
		t __val;						\
		asm volatile(r " " c : "=r" (__val));			\
		__val;							\
	})
#define read_sysreg(...)		__read_sysreg(__VA_ARGS__)

#define __write_sysreg(v, r, w, c, t)	asm volatile(w " " c : : "r" ((t)(v)))
#define write_sysreg(v, ...)		__write_sysreg(v, __VA_ARGS__)

#endif /* __SYSREG_ARM_H_INCLUDE__ */
