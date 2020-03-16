/*
 */
#ifndef __ARM64_BARRIER_H_INCLUDE__
#define __ARM64_BARRIER_H_INCLUDE__

#define __nops(n)	".rept	" #n "\nnop\n.endr\n"
#define nops(n)		asm volatile(__nops(n))

#define sev()		asm volatile("sev" : : : "memory")
#define wfe()		asm volatile("wfe" : : : "memory")
#define wfi()		asm volatile("wfi" : : : "memory")

#define isb()		asm volatile("isb" : : : "memory")
#define dmb(opt)	asm volatile("dmb " #opt : : : "memory")
#define dsb(opt)	asm volatile("dsb " #opt : : : "memory")

#define __mb()		dsb(sy)
#define __rmb()		dsb(ld)
#define __wmb()		dsb(st)

#define __dma_rmb()	dmb(oshld)
#define __dma_wmb()	dmb(oshst)

#define __smp_mb()	dmb(ish)
#define __smp_rmb()	dmb(ishld)
#define __smp_wmb()	dmb(ishst)

#endif /* __ARM64_BARRIER_H_INCLUDE__ */
