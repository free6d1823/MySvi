/*
 */
#ifndef __TESTOS_CACHE_H_INCLUDE__
#define __TESTOS_CACHE_H_INCLUDE__

#include <asm/cache.h>

#define flush_dcache_area(addr, size)	__flush_dcache_area(addr, size)
#define clean_dcache_area(addr, size)	__clean_dcache_area(addr, size)
#define inval_dcache_area(addr, size)	__inval_dcache_area(addr, size)

#define flush_dcache_addr(addr)		__flush_dcache_addr(addr)
#define clean_dcache_addr(addr)		__clean_dcache_addr(addr)
#define inval_dcache_addr(addr)		__inval_dcache_addr(addr)

#endif /* __TESTOS_CACHE_H_INCLUDE__ */
