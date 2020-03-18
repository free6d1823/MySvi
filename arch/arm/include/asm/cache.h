/*
  */
#ifndef __ARMV7M_CACHE_H_INCLUDE__
#define __ARMV7M_CACHE_H_INCLUDE__

#include <asm/mach/cache.h>

#ifndef __SMP_CACHE_SHIFT
#define __SMP_CACHE_SHIFT	7
#endif
#define __SMP_CACHE_BYTES	(1 << __SMP_CACHE_SHIFT)

#ifndef __ASSEMBLY__
#include <asm/sysop.h>

 void __flush_dcache_area(void *addr, size_t size);
 void __clean_dcache_area(void *addr, size_t size);
 void __inval_dcache_area(void *addr, size_t size);

#define __flush_dcache_addr(addr)
#define __clean_dcache_addr(addr)
#define __inval_dcache_addr(addr)
#endif

#endif /* __ARMV7M_CACHE_H_INCLUDE__ */

