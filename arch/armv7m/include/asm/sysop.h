/*
 */
#ifndef __ARMV7M_SYSOP_H_INCLUDE__
#define __ARMV7M_SYSOP_H_INCLUDE__

#include <stdint.h>

/* Define function for simple system instruction */
#define SYSOP_FUNC(_op)					\
static inline void _op(void)				\
{							\
	__asm__ (#_op);					\
}

/* Define function for system instruction with type specifier */
#define SYSOP_FUNC_TYPE(_op, _type)			\
static inline void _op ## _ ## _type(void)		\
{							\
	__asm__ (#_op " " #_type);			\
}

/* Define function for system instruction with register parameter */
#define SYSOP_FUNC_TYPE_PARAM(_op, _type)		\
static inline void _op ## _ ## _type(uint64_t v)	\
{							\
	 __asm__ (#_op " " #_type ", %0" : : "r" (v));	\
}

#ifndef __ASSEMBLY__

SYSOP_FUNC(yield)
SYSOP_FUNC(nop)

#endif /* __ASSEMBLY__ */

#endif /* __ARMV7M_SYSOP_H_INCLUDE__ */
