/*
 */
#ifndef __SYSREG_GICV3_ARM_H_INCLUDE__
#define __SYSREG_GICV3_ARM_H_INCLUDE__

#include <asm/sysreg.h>

/* ARM Generic Interrupt Controller Architecture Specification
 * GIC architecture version 3.0 and version 4.0
 */

/* 8.2 AArch64 System register descriptions */
#define ICC_EOIR1			__ACCESS_CP15(c12, 0, c12, 1)
#define ICC_DIR				__ACCESS_CP15(c12, 0, c11, 1)
#define ICC_IAR1			__ACCESS_CP15(c12, 0, c12, 0)
#define ICC_SGI1R			__ACCESS_CP15_64(0, c12)
#define ICC_PMR				__ACCESS_CP15(c4, 0, c6, 0)
#define ICC_CTLR			__ACCESS_CP15(c12, 0, c12, 4)
#define ICC_SRE				__ACCESS_CP15(c12, 0, c12, 5)
#define ICC_IGRPEN0			__ACCESS_CP15(c12, 0, c12, 6)
#define ICC_IGRPEN1			__ACCESS_CP15(c12, 0, c12, 7)
#define ICC_BPR1			__ACCESS_CP15(c12, 0, c12, 3)
#define ICC_RPR				__ACCESS_CP15(c12, 0, c11, 3)

#define __ICC_AP0Rx(x)		__ACCESS_CP15(c12, 0, c8, 4 | x)
#define ICC_AP0R0			__ICC_AP0Rx(0)
#define ICC_AP0R1			__ICC_AP0Rx(1)
#define ICC_AP0R2			__ICC_AP0Rx(2)
#define ICC_AP0R3			__ICC_AP0Rx(3)

#define __ICC_AP1Rx(x)		__ACCESS_CP15(c12, 0, c9, x)
#define ICC_AP1R0			__ICC_AP1Rx(0)
#define ICC_AP1R1			__ICC_AP1Rx(1)
#define ICC_AP1R2			__ICC_AP1Rx(2)
#define ICC_AP1R3			__ICC_AP1Rx(3)

#define ICC_HSRE			__ACCESS_CP15(c12, 4, c9, 5)

/* 8.3 AArch64 System register descriptions of the virtual registers
 *
 * The ICV_* registers are only accessible at Non-secure EL1. Whether an
 * access encoding maps to an ICC_* register or the equivalent ICV_*
 * register is determined by HCR_EL2.
 */

/* 8.4 AArch64 virtualization control System registers */

#endif /* __ASM_ARCH_GICV3_H */
