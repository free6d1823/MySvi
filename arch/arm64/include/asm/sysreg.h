/*
 */
#ifndef __SYSREG_ARM64_H_INCLUDE__
#define __SYSREG_ARM64_H_INCLUDE__

#include <stdint.h>
#include <target/regdef.h>

/* Unlike read_cpuid, calls to read_sysreg are never expected to be
 * optimized away or replaced with synthetic values.
 */
#define read_sysreg(r) ({						\
	uint64_t __val;							\
	asm volatile("mrs %0, " __stringify(r) : "=r" (__val));		\
	__val;								\
})

/* "Z" normally means zero immediate, it means XZR when it is combined with
 * "%x0" template.
 */
#define write_sysreg(v, r) do {						\
	uint64_t __val = (uint64_t)v;					\
	asm volatile("msr " __stringify(r) ", %x0" : : "rZ" (__val));	\
} while (0)

#endif /* __SYSREG_ARM64_H_INCLUDE__ */
