@ Bad Abort numbers
@ -----------------
@
#define BAD_PREFETCH	0
#define BAD_DATA	1
#define BAD_ADDREXCPTN	2
#define BAD_IRQ		3
#define BAD_UNDEFINSTR	4
/* 
 * The SWI code relies on the fact that R0 is at the bottom of the stack
 * (due to slow/fast restore user regs).
 */
#if S_R0 != 0
#error "Please fix"
#endif

	.macro	zero_fp
#ifdef CONFIG_FRAME_POINTER
	mov	fp, #0
#endif
	.endm
	.macro	svc_exit, rpsr, irq = 0
	.if	\irq != 0
	@ IRQs already off
	.else
	@ IRQs off again before pulling preserved data off the stack
	.endif

#ifndef CONFIG_THUMB2_KERNEL
	@ ARM mode SVC restore
	msr	spsr_cxsf, \rpsr
#if defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_32v6K)
	@ We must avoid clrex due to Cortex-A15 erratum #830321
	sub	r0, sp, #4			@ uninhabited address
	strex	r1, r2, [r0]			@ clear the exclusive monitor
#endif
	ldmia	sp, {r0 - pc}^			@ load r0 - pc, cpsr
#else
	@ Thumb mode SVC restore
	ldr	lr, [sp, #S_SP]			@ top of the stack
	ldrd	r0, r1, [sp, #S_LR]		@ calling lr and pc

	@ We must avoid clrex due to Cortex-A15 erratum #830321
	strex	r2, r1, [sp, #S_LR]		@ clear the exclusive monitor

	stmdb	lr!, {r0, r1, \rpsr}		@ calling lr and rfe context
	ldmia	sp, {r0 - r12}
	mov	sp, lr
	ldr	lr, [sp], #4
	rfeia	sp!
#endif
	.endm
