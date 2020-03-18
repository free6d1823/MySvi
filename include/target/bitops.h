#ifndef __TESTOS_BITOPS_H_INCLUDE__
#define __TESTOS_BITOPS_H_INCLUDE__

#include <stdint.h>

#ifndef min
#define min(x, y)       ((x)<(y)?(x):(y))
#endif
#ifndef max
#define max(x, y)       ((x)>(y)?(x):(y))
#endif
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(__array)	\
	(sizeof (__array) / sizeof ((__array)[0]))
#endif

#define ilog2(x) __ilog2(x)
#define set_bit(nr, addr) __set_bit(nr, addr)
#define find_first_zero_bit(addr, size) \
	find_next_zero_bit((addr), (size), 0)

uint32_t gcd32u(uint32_t n, uint32_t m);
uint32_t __roundup32(uint32_t n);
uint8_t hweight64(uint64_t w);

/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
static inline int generic_fls(int x)
{
	int r = 32;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}
	return r;
}
static inline int __ilog2(unsigned int x)
{
	return generic_fls(x) - 1;
}
/*
 * fls: find last (most-significant) bit set.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 *
 * On powerpc, __ilog2(0) returns -1, but this is not safe in general
 */
static __inline__ int fls(unsigned int x)
{
	return __ilog2(x) + 1;
}
#define PLATFORM_FLS

/**
 * fls64 - find last set bit in a 64-bit word
 * @x: the word to search
 *
 * This is defined in a similar way as the libc and compiler builtin
 * ffsll, but returns the position of the most significant set bit.
 *
 * fls64(value) returns 0 if value is 0 or the position of the last
 * set bit if value is nonzero. The last (most significant) bit is
 * at position 64.
 */
#define _BITS_PER_LONG_ 64
#if _BITS_PER_LONG_ == 32
static inline int fls64(uint64_t x)
{
	__u32 h = x >> 32;
	if (h)
		return fls(h) + 32;
	return fls(x);
}
#elif _BITS_PER_LONG_ == 64
static inline int fls64(uint64_t x)
{
	if (x == 0)
		return 0;
	return __ilog2(x) + 1;
}
#else
#error _BITS_PER_LONG_ not 32 or 64
#endif

static inline void __set_bit(int nr, volatile void *addr)
{
	int	* a = (int *) addr;
	int	mask;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	*a |= mask;
}

static inline int ffs (int x)
{
	int r = 1;

	if (!x)
		return 0;
	if (!(x & 0xffff)) {
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}
	if (!(x & 1)) {
		x >>= 1;
		r += 1;
	}
	return r;
}

/*
 * ffz = Find First Zero in word. Undefined if no zero exists,
 * so code should check against ~0UL first..
 */
static inline unsigned long ffz(unsigned long word)
{
	unsigned long result = 0;

	while(word & 1) {
		result++;
		word >>= 1;
	}
	return result;
}

static inline void clear_bit(int nr, volatile void *addr)
{
	int	* a = (int *) addr;
	int	mask;
	unsigned long flags;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	*a &= ~mask;
}

static inline int find_next_zero_bit(void *addr, int size, int offset)
{
	unsigned long *p = ((unsigned long *) addr) + (offset >> 5);
	unsigned long result = offset & ~31UL;
	unsigned long tmp;

	if (offset >= size)
		return size;
	size -= result;
	offset &= 31UL;
	if (offset) {
		tmp = *(p++);
		tmp |= ~0UL >> (32-offset);
		if (size < 32)
			goto found_first;
		if (~tmp)
			goto found_middle;
		size -= 32;
		result += 32;
	}
	while (size & ~31UL) {
		if (~(tmp = *(p++)))
			goto found_middle;
		result += 32;
		size -= 32;
	}
	if (!size)
		return result;
	tmp = *p;

found_first:
	tmp |= ~0UL >> size;
found_middle:
	return result + ffz(tmp);
}
#endif /* __TESTOS_BITOPS_H_INCLUDE__ */
