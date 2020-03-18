/*
 */
#ifndef __TESTOS_REGDEF_H_INCLUDE__
#define __TESTOS_REGDEF_H_INCLUDE__

#include <stdint.h>

#define _BV(x)			(U(1) << (x))
#define _BV_UL(x)		(UL(1) << (x))
#define _BV_ULL(x)		(ULL(1) << (x))
#define _FV(name, value)	_SET_FV(name, value)
#define _SET_FV(name, value)	\
	(((value) & (name##_MASK)) << (name##_OFFSET))
#define _GET_FV(name, value)	\
	(((value) >> (name##_OFFSET)) & (name##_MASK))

#define BIT _BV
#define BIT_UL _BV_UL

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

#define REG_1BIT_MASK		0x001
#define REG_2BIT_MASK		0x003
#define REG_3BIT_MASK		0x007
#define REG_4BIT_MASK		0x00F
#define REG_5BIT_MASK		0x01F
#define REG_6BIT_MASK		0x03F
#define REG_7BIT_MASK		0x07F
#define REG_8BIT_MASK		0x0FF
#define REG_9BIT_MASK		0x1FF
#define REG_10BIT_MASK		0x3FF
#define REG_11BIT_MASK		0x7FF
#define REG_12BIT_MASK		0xFFF
#define REG_13BIT_MASK		0x1FFF
#define REG_16BIT_MASK		0xFFFF
#define REG_17BIT_MASK		0x1FFFF
#define REG_20BIT_MASK		0xFFFFF
#define REG_24BIT_MASK		0xFFFFFF

#ifndef __ASSEMBLY__
extern uint8_t ____ilog2_NaN(void);
#define ilog2_const(n)			\
(					\
	(n) < 1 ? ____ilog2_NaN() :	\
	(n) & (ULL(1) << 63) ? 63 :	\
	(n) & (ULL(1) << 62) ? 62 :	\
	(n) & (ULL(1) << 61) ? 61 :	\
	(n) & (ULL(1) << 60) ? 60 :	\
	(n) & (ULL(1) << 59) ? 59 :	\
	(n) & (ULL(1) << 58) ? 58 :	\
	(n) & (ULL(1) << 57) ? 57 :	\
	(n) & (ULL(1) << 56) ? 56 :	\
	(n) & (ULL(1) << 55) ? 55 :	\
	(n) & (ULL(1) << 54) ? 54 :	\
	(n) & (ULL(1) << 53) ? 53 :	\
	(n) & (ULL(1) << 52) ? 52 :	\
	(n) & (ULL(1) << 51) ? 51 :	\
	(n) & (ULL(1) << 50) ? 50 :	\
	(n) & (ULL(1) << 49) ? 49 :	\
	(n) & (ULL(1) << 48) ? 48 :	\
	(n) & (ULL(1) << 47) ? 47 :	\
	(n) & (ULL(1) << 46) ? 46 :	\
	(n) & (ULL(1) << 45) ? 45 :	\
	(n) & (ULL(1) << 44) ? 44 :	\
	(n) & (ULL(1) << 43) ? 43 :	\
	(n) & (ULL(1) << 42) ? 42 :	\
	(n) & (ULL(1) << 41) ? 41 :	\
	(n) & (ULL(1) << 40) ? 40 :	\
	(n) & (ULL(1) << 39) ? 39 :	\
	(n) & (ULL(1) << 38) ? 38 :	\
	(n) & (ULL(1) << 37) ? 37 :	\
	(n) & (ULL(1) << 36) ? 36 :	\
	(n) & (ULL(1) << 35) ? 35 :	\
	(n) & (ULL(1) << 34) ? 34 :	\
	(n) & (ULL(1) << 33) ? 33 :	\
	(n) & (ULL(1) << 32) ? 32 :	\
	(n) & (ULL(1) << 31) ? 31 :	\
	(n) & (ULL(1) << 30) ? 30 :	\
	(n) & (ULL(1) << 29) ? 29 :	\
	(n) & (ULL(1) << 28) ? 28 :	\
	(n) & (ULL(1) << 27) ? 27 :	\
	(n) & (ULL(1) << 26) ? 26 :	\
	(n) & (ULL(1) << 25) ? 25 :	\
	(n) & (ULL(1) << 24) ? 24 :	\
	(n) & (ULL(1) << 23) ? 23 :	\
	(n) & (ULL(1) << 22) ? 22 :	\
	(n) & (ULL(1) << 21) ? 21 :	\
	(n) & (ULL(1) << 20) ? 20 :	\
	(n) & (ULL(1) << 19) ? 19 :	\
	(n) & (ULL(1) << 18) ? 18 :	\
	(n) & (ULL(1) << 17) ? 17 :	\
	(n) & (ULL(1) << 16) ? 16 :	\
	(n) & (ULL(1) << 15) ? 15 :	\
	(n) & (ULL(1) << 14) ? 14 :	\
	(n) & (ULL(1) << 13) ? 13 :	\
	(n) & (ULL(1) << 12) ? 12 :	\
	(n) & (ULL(1) << 11) ? 11 :	\
	(n) & (ULL(1) << 10) ? 10 :	\
	(n) & (ULL(1) <<  9) ?  9 :	\
	(n) & (ULL(1) <<  8) ?  8 :	\
	(n) & (ULL(1) <<  7) ?  7 :	\
	(n) & (ULL(1) <<  6) ?  6 :	\
	(n) & (ULL(1) <<  5) ?  5 :	\
	(n) & (ULL(1) <<  4) ?  4 :	\
	(n) & (ULL(1) <<  3) ?  3 :	\
	(n) & (ULL(1) <<  2) ?  2 :	\
	(n) & (ULL(1) <<  1) ?  1 :	\
	(n) & (ULL(1) <<  0) ?  0 :	\
	____ilog2_NaN()			\
 )
#endif

#define LOHALF(b)			(b & 0x0F)
#define HIHALF(b)			(b >> 4)
#ifndef LOBYTE
#define LOBYTE(w)			((uint8_t)w)
#endif
#ifndef HIBYTE
#define HIBYTE(w)			((uint8_t)((w)>>8))
#endif
#ifndef LOWORD
#define LOWORD(w)			((uint16_t)w)
#endif
#ifndef HIWORD
#define HIWORD(w)			((uint16_t)((w)>>16))
#endif
#ifndef LODWORD
#define LODWORD(w)			((uint32_t)w)
#endif
#ifndef HIDWORD
#define HIDWORD(w)			((uint32_t)((w)>>32))
#endif
#define MAKEBYTE(a, b)			((uint8_t)(((a) & 0x0F) | (((b) & 0x0F) << 4)))
#ifndef MAKEWORD
#define MAKEWORD(a, b)			((uint16_t)(((uint16_t)(a)) | \
						    ((uint16_t)(b)) << 8))
#endif
#ifndef MAKELONG
#define MAKELONG(a, b)			((uint32_t)(((uint32_t)(a)) | \
						    ((uint32_t)(b)) << 16))
#endif
#ifndef MAKELLONG
#define MAKELLONG(a, b)			((uint64_t)(((uint64_t)(a)) | \
						    ((uint64_t)(b)) << 32))
#endif

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

#ifndef __ASSEMBLY__
#define ALIGN(x,a)		__ALIGN_MASK(x,(a)-1)
#define __ALIGN_MASK(x,mask)	(((x)+(mask))&~(mask))
#endif

#endif /* __TESTOS_REGDEF_H_INCLUDE__ */
