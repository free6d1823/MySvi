#ifndef __TESTOS_CLOCK_H_INCLUDE__
#define __TESTOS_CLOCK_H_INCLUDE__

#include <asm/clock.h>

#define CLK_BITS_OR(val, mask)		((val) & (mask))
#define CLK_BITS_NOR(val, mask)		(((val) & (mask)) == 0)
#define CLK_BITS_AND(val, mask)		(((val) & (mask)) == (mask))
#define CLK_BITS_NAND(val, mask)	(((val) & (mask)) != (mask))

#endif /* __TESTOS_CLOCK_H_INCLUDE__ */
