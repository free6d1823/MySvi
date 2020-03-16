#ifndef __ARM64_CPUS_H_INCLUDE__
#define __ARM64_CPUS_H_INCLUDE__

#include <asm/mach/cpus.h>

#define wait_for_dbg()		asm volatile("b ." : : : "memory")

#endif /* __ARM64_CPUS_H_INCLUDE__ */
