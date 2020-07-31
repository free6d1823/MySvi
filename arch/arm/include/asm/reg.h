/*
 */
#ifndef __REG_ARM32_H_INCLUDE__
#define __REG_ARM32_H_INCLUDE__

#include <target/regdef.h>
#include <asm/sysreg.h>

/*
 *The register setting values
 */

/**/
#define CNTHCTL_PL1PCTEN           _BV(0)
#define CNTHCTL_PL1PCEN            _BV(1)
#define CNTPCTL_ENABLE		   _BV(1)


#define CNTKCTL_PL0PCTEN           _BV(0)
#define CNTKCTL_PL0VCTEN           _BV(1)
#define CNTKCTL_PL0PTEN            _BV(9)



#define CNTX_CTL_IMASK             _BV(1)
#define CNTX_CTL_ISTATUS           _BV(2)


/*
 *Define the arm32 system registers through CP15 
 */

/*armv8-32 timer-counter registers*/
#define CNTPCT			__ACCESS_CP15_64(0, c14) /*physical counter*/
#define CNTVCT			__ACCESS_CP15_64(1, c14) /*virtual counter*/
#define CNTVOFF			__ACCESS_CP15_64(4, c14) /*virtual counter offset*/

#define CNTFRQ			__ACCESS_CP15(c14, 0, c0, 0) /*counter frequency*/
#define CNTHCTL			__ACCESS_CP15(c14, 4, c1, 0) /*counter hypervisor control register*/
#define CNTKCTL			__ACCESS_CP15(c14, 0, c1, 0) /*counter kernel control register*/
#define CNTPCTL			__ACCESS_CP15(c14, 0, c2, 1) /*counter physical control register*/

#define CNTP_CVAL		__ACCESS_CP15_64(2, c14) /*compare-value of L1 timer*/
#define CNTP_CTL		__ACCESS_CP15(c14, 0, c2, 1) /*the control register of physical timer*/

#endif
