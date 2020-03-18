/*
 */
#ifndef __ARMV7M_CPUS_H_INCLUDE__
#define __ARMV7M_CPUS_H_INCLUDE__

#include <asm/mach/cpus.h>

#define wait_for_dbg()		asm volatile("b ." : : : "memory")

#endif /* __ARMV7M_CPUS_H_INCLUDE__ */
