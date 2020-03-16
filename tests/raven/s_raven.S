#include <target/raven.h>

ENTRY(GetCPUID)
#if defined(RTL_SIM) || defined(TESTOS)
    mrs  x0, MPIDR_EL1
    LSR  w1,w0,#8              // get aff1 level1 & others
    BFI  w0,w1,#1,#8           // merge aff0 level0 and aff1 level1 & others
    AND  w0,w0,#0x1ff          // clear other bits except the cpu id
    ret
#else
    mrs x0, MIDR_EL1
    ubfx    x0, x0, #4, #12 // extract PartNum
// Could decide what to do next depending on part number
    mrs x0, MPIDR_EL1
    ubfx    x0, x0, #MPIDR_EL1_AFF0_LSB, #MPIDR_EL1_AFF_WIDTH
    ret
#endif
ENDPROC(GetCPUID)
