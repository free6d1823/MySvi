#ifndef __COMMON_UTILS_H_INCLUDE__
#define __COMMON_UTILS_H_INCLUDE__
#include <stdint.h>
#include <target/barrier.h>
#include <asm/io.h>

typedef uint8_t  __u8;
typedef uint32_t __u32;


typedef uint16_t __le16;
typedef uint32_t __le32;
typedef uint64_t __le64;

typedef unsigned int __be32;

typedef unsigned int uint;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef unsigned char unchar;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef volatile unsigned long vu_long;
typedef __signed__ char __s8;

#include <endian.h>
#define __le16_to_cpu(x) le16toh(x)
#define le16_to_cpu(x)   le16toh(x)
#define le32_to_cpu(x)   le32toh(x)
#define le64_to_cpu(x)   le64toh(x)

#define cpu_to_le16(x)   htole16(x)
#define cpu_to_le32(x)   htole32(x)
#define cpu_to_le64(x)   htole64(x)

#define le16_to_cpus(x)  do { (void)(x); } while (0)

#define readl __raw_readl
#define writel __raw_writel

typedef u64 dma_addr_t;/*ONLY support 64bits*/

typedef u64 phys_addr_t;
typedef u64 phys_size_t;

#define DECLARE_BITMAP(name, bits) \
	unsigned long name[BITS_TO_LONGS(bits)]

#define SZ_1				0x00000001
#define SZ_2				0x00000002
#define SZ_4				0x00000004
#define SZ_8				0x00000008
#define SZ_16				0x00000010
#define SZ_32				0x00000020
#define SZ_64				0x00000040
#define SZ_128				0x00000080
#define SZ_256				0x00000100
#define SZ_512				0x00000200

#define SZ_1K				0x00000400
#define SZ_2K				0x00000800
#define SZ_4K				0x00001000
#define SZ_8K				0x00002000
#define SZ_16K				0x00004000
#define SZ_32K				0x00008000
#define SZ_64K				0x00010000
#define SZ_128K				0x00020000
#define SZ_256K				0x00040000
#define SZ_512K				0x00080000

#define SZ_1M				0x00100000
#define SZ_2M				0x00200000
#define SZ_4M				0x00400000
#define SZ_8M				0x00800000
#define SZ_16M				0x01000000
#define SZ_32M				0x02000000
#define SZ_64M				0x04000000
#define SZ_128M				0x08000000
#define SZ_256M				0x10000000
#define SZ_512M				0x20000000

#define SZ_1G				0x40000000
#define SZ_2G				0x80000000

#define min3(x, y, z) min((typeof(x))min(x, y), z)
#define max3(x, y, z) max((typeof(x))max(x, y), z)

#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1: __min2; })

#define max_t(type, x, y) ({			\
	type __max1 = (x);			\
	type __max2 = (y);			\
	__max1 > __max2 ? __max1: __max2; })

#define upper_32_bits(n) ((u32)(((n) >> 16) >> 16))
#define lower_32_bits(n) ((u32)(n))
#define clamp_t(type, val, lo, hi) min_t(type, max_t(type, val, lo), hi)
#define clamp_val(val, lo, hi) clamp_t(typeof(val), val, lo, hi)

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

/* The `const' in roundup() prevents gcc-3.3 from calling __divdi3 */
#define roundup(x, y) (					\
{							\
	const typeof(y) __y = y;			\
	(((x) + (__y - 1)) / __y) * __y;		\
}							\
)
#define rounddown(x, y) (				\
{							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
}							\
)

/*
 * Divide positive or negative dividend by positive divisor and round
 * to closest integer. Result is undefined for negative divisors and
 * for negative dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor)(			\
{							\
	typeof(x) __x = x;				\
	typeof(divisor) __d = divisor;			\
	(((typeof(x))-1) > 0 ||				\
	 ((typeof(divisor))-1) > 0 || (__x) > 0) ?	\
		(((__x) + ((__d) / 2)) / (__d)) :	\
		(((__x) - ((__d) / 2)) / (__d));	\
}							\
)
/*
 * Same as above but for u64 dividends. divisor must be a 32-bit
 * number.
 */
#define DIV_ROUND_CLOSEST_ULL(x, divisor)(		\
{							\
	typeof(divisor) __d = divisor;			\
	unsigned long long _tmp = (x) + (__d) / 2;	\
	do_div(_tmp, __d);				\
	_tmp;						\
}							\
)

static inline unsigned long virt_to_phys(void *vaddr)
{
	return (unsigned long)vaddr;
}
static inline void *phys_to_virt(unsigned long address)
{
	return (void *)(address);
}

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define WARN_ON(condition) ({						\
	int __ret_warn_on = !!(condition);				\
	if (unlikely(__ret_warn_on))					\
		printf("WARNING at %s:%d/%s()!\n", __FILE__, __LINE__, __func__); \
	unlikely(__ret_warn_on);					\
})
#endif
