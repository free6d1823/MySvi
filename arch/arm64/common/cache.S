/*
 */
#include <target/compiler.h>
#include <target/assembler.h>

       .macro  dcache_line_size, reg, tmp
       mrs     \tmp, ctr_el0
       ubfm    \tmp, \tmp, #16, #19
       mov     \reg, #4
       lsl     \reg, \reg, \tmp
       .endm

       .macro  dcache_by_line_op op, domain, kaddr, size, tmp1, tmp2
       dcache_line_size \tmp1, \tmp2
       add     \size, \kaddr, \size
       sub     \tmp2, \tmp1, #1
       bic     \kaddr, \kaddr, \tmp2
loop_\op:
       dc      \op, \kaddr
       add     \kaddr, \kaddr, \tmp1
       cmp     \kaddr, \size
       b.lo    loop_\op
       dsb     \domain
       .endm

/*
 * __flush_dcache_area(addr, size)
 * Ensure that any D-cache lines for the interval [addr, addr+size)
 * are cleaned and invalidated to the PoC.
 * - addr    - address
 * - size    - size in question
 */
ENTRY(__flush_dcache_area)
	dcache_by_line_op civac, sy, x0, x1, x2, x3
	ret
ENDPIPROC(__flush_dcache_area)

/*
 * __clean_dcache_area(addr, size)
 * Ensure that any D-cache lines for the interval [addr, addr+size)
 * are cleaned to the PoC.
 * - addr    - address
 * - size    - size in question
 */
ENTRY(__clean_dcache_area)
	dcache_by_line_op cvac, sy, x0, x1, x2, x3
	ret
ENDPIPROC(__clean_dcache_area)

/*
 * __inval_dcache_area(addr, size)
 * Ensure that any D-cache lines for the interval [addr, addr+size)
 * are invalidated to the PoC.
 * - addr    - address
 * - size    - size in question
 */
ENTRY(__inval_dcache_area)
	dcache_by_line_op ivac, sy, x0, x1, x2, x3
	ret
ENDPIPROC(__inval_dcache_area)
