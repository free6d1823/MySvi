/*
 */
#ifndef __TESTOS_SMP_H_INCLUDE__
#define __TESTOS_SMP_H_INCLUDE__

#include <target/cache.h>

#define NR_CPUS		MAX_CPU_NUM

#include <asm/cpus.h>

#include <asm/smp.h>

#define smp_processor_id()	__smp_processor_id()
#define hmp_processor_id()	__hmp_processor_id()

#define SMP_CACHE_BYTES		__SMP_CACHE_BYTES
#define __cache_aligned		__aligned(SMP_CACHE_BYTES)

#ifndef __ASSEMBLY__

extern unsigned long cpus_boot_cpu;

unsigned int plat_my_core_pos(void);
#endif

#endif /* __TESTOS_SMP_H_INCLUDE__ */
