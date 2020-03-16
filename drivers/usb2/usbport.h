#ifndef __USBPORT_H__
#define __USBPORT_H__

#include <stdint.h>
#include <stdbool.h>

#include <target/regdef.h>
#include <target/compiler.h>
#include <target/utils.h>

#define get_unaligned(p) *(p)
#define put_unaligned(v,p) *p=v

#define ARCH_DMA_MINALIGN 16
#define CONFIG_SYS_CACHELINE_SIZE 128

#define CONFIG_IS_ENABLED(c) 0

struct udevice;

#if 0
#define debug printf
#else
#define debug
#endif

#define ROUND(a,b)		(((a) + (b) - 1) & ~((b) - 1))

#include <target/delay.h>
#define mdelay(m) udelay(m * 1000)

#include <target/heap.h>
#include <string.h>
#define memalign heap_aligned_alloc
#define malloc(s) heap_aligned_alloc(ARCH_DMA_MINALIGN, s)
static inline void *_calloc(size_t nmemb, size_t size){
	void *p = malloc(nmemb * size);
	if (p) memset(p, 0, nmemb * size);
	return p;
}
#define calloc _calloc
#define free {}

#define env_get(n) NULL

#define simple_strtol strtol

/* Returns time in milliseconds */
static inline unsigned long get_timer(unsigned long base)
{
	uint64_t tsc_hw_read_counter(void);
	return (ulong)tsc_hw_read_counter() / 1000 - base;
}

#include <target/bitops.h>

#define BUG() do { \
	printf("BUG at %s:%d/%s()!\n", __FILE__, __LINE__, __func__); \
	for (;;); \
} while (0)

#define BUG_ON(condition) do { if (unlikely(condition)) BUG(); } while (0)

#include <target/cache.h>

static inline void flush_dcache_range(unsigned long start, unsigned long stop)
{
	flush_dcache_area(((void *)start), stop - start);
}

static inline void invalidate_dcache_range(unsigned long start, unsigned long stop)
{
	inval_dcache_area(((void *)start), stop - start);
}


/* for ehci-hcd */
struct phy;

#define CONFIG_SYS_MALLOC_LEN	(256 * 1024)


#define WATCHDOG_RESET() BUG()

#endif
