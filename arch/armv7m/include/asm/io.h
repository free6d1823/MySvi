/*
 */
#ifndef __IO_ARMV7M_H_INCLUDE__
#define __IO_ARMV7M_H_INCLUDE__

#include <stddef.h>
#include <stdint.h>

#define __raw_writeb(v,a)	(*(volatile uint8_t  *)(caddr_t)(a) = (v))
#define __raw_writew(v,a)	(*(volatile uint16_t *)(caddr_t)(a) = (v))
#define __raw_writel(v,a)	(*(volatile uint32_t *)(caddr_t)(a) = (v))

#define __raw_readb(a)		(*(volatile uint8_t  *)(caddr_t)(a))
#define __raw_readw(a)		(*(volatile uint16_t *)(caddr_t)(a))
#define __raw_readl(a)		(*(volatile uint32_t *)(caddr_t)(a))

/* XXX: Atomic Register Access
 *
 * Be aware that no atomic assurance is made for the following macros.
 * Please use __raw_xxxbwl_atomic versions for atomic register access.
 */
#define __raw_setb(v,a)					\
	do {						\
		uint8_t __v = __raw_readb(a);		\
		__v |= (v);				\
		__raw_writeb(__v, (a));			\
	} while (0)
#define __raw_setw(v, a)				\
	do {						\
		uint16_t __v = __raw_readw(a);		\
		__v |= (v);				\
		__raw_writew(__v, (a));			\
	} while (0)
#define __raw_setl(v,a)					\
	do {						\
		uint32_t __v = __raw_readl(a);		\
		__v |= (v);				\
		__raw_writel(__v, (a));			\
	} while (0)
#define __raw_clearb(v,a)				\
	do {						\
		uint8_t __v = __raw_readb(a);		\
		__v &= ~(v);				\
		__raw_writeb(__v, (a));			\
	} while(0)
#define __raw_clearw(v,a)				\
	do {						\
		uint16_t __v = __raw_readw(a);		\
		__v &= ~(v);				\
		__raw_writew(__v, (a));			\
	} while(0)
#define __raw_clearl(v,a)				\
	do {						\
		uint32_t __v = __raw_readl(a);		\
		__v &= ~(v);				\
		__raw_writel(__v, (a));			\
	} while (0)
#define __raw_writeb_mask(v,m,a)			\
	do {						\
		uint8_t __v = __raw_readb(a);		\
		__v &= ~(m);				\
		__v |= (v);				\
		__raw_writeb(__v, (a));			\
	} while (0)
#define __raw_writew_mask(v,m,a)			\
	do {						\
		uint16_t __v = __raw_readw(a);		\
		__v &= ~(m);				\
		__v |= (v);				\
		__raw_writew(__v, (a));			\
	} while (0)
#define __raw_writel_mask(v,m,a)			\
	do {						\
		uint32_t __v = __raw_readl(a);		\
		__v &= ~(m);				\
		__v |= (v);				\
		__raw_writel(__v, (a));			\
	} while (0)
#define __raw_testb(v, a)				\
	(__raw_readb(a) & (v))
#define __raw_testw(v, a)				\
	(__raw_readw(a) & (v))
#define __raw_testl(v, a)				\
	(__raw_readl(a) & (v))


#endif /* __IO_ARMV7M_H_INCLUDE__ */

