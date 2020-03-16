/*
 */
#ifndef __ARM64_SYSOP_H_INCLUDE__
#define __ARM64_SYSOP_H_INCLUDE__

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

/*
 * System instructions for cache maintenance
 */
SYSOP_FUNC_TYPE_PARAM(dc, cisw)
SYSOP_FUNC_TYPE_PARAM(dc, civac)
SYSOP_FUNC_TYPE_PARAM(dc, csw)
SYSOP_FUNC_TYPE_PARAM(dc, cvac)
SYSOP_FUNC_TYPE_PARAM(dc, cvau)
SYSOP_FUNC_TYPE_PARAM(dc, isw)
SYSOP_FUNC_TYPE_PARAM(dc, ivac)
SYSOP_FUNC_TYPE_PARAM(dc, zva)
SYSOP_FUNC_TYPE_PARAM(ic, iallu)
SYSOP_FUNC_TYPE_PARAM(ic, ialluis)
SYSOP_FUNC_TYPE_PARAM(ic, ivau)

/*
 * System instructions for address translation
 */
SYSOP_FUNC_TYPE_PARAM(at, s12e0r)
SYSOP_FUNC_TYPE_PARAM(at, s12e0w)
SYSOP_FUNC_TYPE_PARAM(at, s12e1r)
SYSOP_FUNC_TYPE_PARAM(at, s12e1w)
SYSOP_FUNC_TYPE_PARAM(at, s1e0r)
SYSOP_FUNC_TYPE_PARAM(at, s1e0w)
SYSOP_FUNC_TYPE_PARAM(at, s1e1r)
SYSOP_FUNC_TYPE_PARAM(at, s1e1w)
SYSOP_FUNC_TYPE_PARAM(at, s1e2r)
SYSOP_FUNC_TYPE_PARAM(at, s1e2w)
SYSOP_FUNC_TYPE_PARAM(at, s1e3r)
SYSOP_FUNC_TYPE_PARAM(at, s1e3w)

#endif /* __ASSEMBLY__ */

#endif /* __ARM64_SYSOP_H_INCLUDE__ */
