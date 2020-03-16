/*
 */
#ifndef __ARMV7M_SMP_H_INCLUDE__
#define __ARMV7M_SMP_H_INCLUDE__

#include <target/memory.h>


#ifdef __ASSEMBLY__
#else

#define __smp_processor_id()	0
#define __hmp_processor_id()	0

#endif

#endif /* __ARMV7M_SMP_H_INCLUDE__ */
