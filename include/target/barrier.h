/*
 */
#ifndef __TESTOS_BARRIER_H_INCLUDE__
#define __TESTOS_BARRIER_H_INCLUDE__

#include <target/compiler.h>

#define barrier()	__barrier()

#include <asm/barrier.h>

#ifndef mb
#define mb()		__mb()
#endif

#ifndef rmb
#define rmb()		__rmb()
#endif

#ifndef wmb
#define wmb()		__wmb()
#endif

#ifndef __smp_mb
#define __smp_mb()	mb()
#endif

#ifndef __smp_rmb
#define __smp_rmb()	rmb()
#endif

#ifndef __smp_wmb
#define __smp_wmb()	wmb()
#endif

#ifndef dma_rmb
#define dma_rmb()	__dma_rmb()
#endif

#ifndef dma_wmb
#define dma_wmb()	__dma_wmb()
#endif

#ifdef CONFIG_SMP

#ifndef smp_mb
#define smp_mb()	__smp_mb()
#endif

#ifndef smp_rmb
#define smp_rmb()	__smp_rmb()
#endif

#ifndef smp_wmb
#define smp_wmb()	__smp_wmb()
#endif

#else	/* !CONFIG_SMP */

#ifndef smp_mb
#define smp_mb()	barrier()
#endif

#ifndef smp_rmb
#define smp_rmb()	barrier()
#endif

#ifndef smp_wmb
#define smp_wmb()	barrier()
#endif

#endif	/* CONFIG_SMP */

#endif /* __TESTOS_BARRIER_H_INCLUDE__ */
