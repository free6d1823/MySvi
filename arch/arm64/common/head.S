/*  */
#include <target/compiler.h>
#include <target/assembler.h>
#include <target/memory.h>
#include <target/timer.h>
#include <asm/reg.h>
#include <asm/asm_macros.S>

	__HEAD
ENTRY(_start)
	/* Enable cache and stack alignment check
	 * Disable MMU, alignment check, write XN
	 * Keep endianness unchanged
	 */
	mov_imm	x0, (SCTLR_EL3_RES1 | SCTLR_I | SCTLR_C | SCTLR_SA)
	msr	SCTLR_EL3, x0
	/* Make sure we throw away anything fetched before the
	 * MMU/Caches were in a known state
	 */
	dsb	sy
	isb

	/* Do not trap WFE/WFI/SMC/HVC
	 * Route SError and External Aborts, IRQ, FIQ
	 * Permit non-secure secure instruction fetch
	 * Lower EL is AARCH64 and non-secure
	 */
	mov_imm	x0, (SCR_EL3_RES1 | SCR_NS | SCR_RW | \
		      SCR_EA | SCR_IRQ| SCR_FIQ | SCR_ST)
	msr	SCR_EL3, x0

	/* No feature trap */
	msr	CPTR_EL3, xzr

	/* Disable VM and VM traps
	 * Lower EL is AARCH64
	 */
	mov_imm	x0, HCR_RW
	msr	HCR_EL2, x0

	ldr	x0, =vectors
	msr	VBAR_EL3, x0

	/* Save CPU id into x19(Callee-saved registers) */
	mrs	x0, mpidr_el1
	and	x1, x0, #0xff
	and	x0, x0, #0xff00
	add	x19, x1, x0, LSR #(8 - CPUS_SHIFT)

	/* Set stack for CPUs */
	add	x0, x19, #1
	mov_imm	x1, STACKS_START
	add	x0, x1, x0, LSL #STACK_SHIFT
	mov	sp, x0

	/* BOOT_CORE should be defined if CPUs wake up simultaneously */
#ifdef BOOT_CORE
	cmp	x19, BOOT_CORE
	beq	out

	lsl	x0, x19, #3
	ldr	x2, =CPU_HOLD_BASE

	/* Wait until we have a go */
	sevl
poll_mailbox:
	wfe
	ldr	x1, [x2, x0]
	cbz	x1, poll_mailbox
	ldr	x0, =secondary_entry
	blr	x0
	b	.

out:
#endif

	/* relocate the code if needed */
	ldr	x0, =_start
	adr	x1, _start
	cmp	x0, x1
	beq	relocate_done
#ifndef CONFIG_BSS_IN_DATA
	adr	x2, __data_end
#else
	adr	x2, __bss_end
#endif
	sub	x2, x2, x1
	bl	memcpy
	ldr	x0, =relocate_done
	br	x0
relocate_done:

	ldr_l	x0, cpus_boot_cpu
	cmp	x0, MAX_CPU_NUM
	beq	cold_boot
	adr_l	x0, secondary_entry
	blr	x0
	b	.

cold_boot:
	/* Save CPU id into cpus_boot_cpu */
	str_l	x19, cpus_boot_cpu, x0

#ifndef CONFIG_BSS_IN_DATA
	/* zero init BSS region */
	adr_l	x0, __bss_start
	adr_l	x1, __bss_end
bss_loop:
.rept (BSS_ALIGN / 16)
	stp	xzr, xzr, [x0], #16
.endr
	cmp	x0, x1
	blt	bss_loop
#endif

	#bl	sysini_wrapper
	adr_l	x0, entry
	blr	x0
	b	.
ENDPIPROC(_start)

ENTRY(smc_psci)
	smc #0
	ret

/*
 * Branch according to exception level
 */
.macro switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, 0xc
	b.eq	\el3_label
	cmp	\xreg, 0x8
	b.eq	\el2_label
	cmp	\xreg, 0x4
	b.eq	\el1_label
.endm

/*
 * Save esr,elr,spsr according to exception level
 */
.macro save_el
3:
	mrs	x1, esr_el3
	mrs	x3, elr_el3
	mrs	x4, spsr_el3
	b	0f
2:
	mrs	x1, esr_el2
	mrs	x3, elr_el2
	mrs	x4, spsr_el2
	b	0f
1:
	mrs	x1, esr_el1
	mrs	x3, elr_el1
	mrs	x4, spsr_el1
0:
	stp	x3, x0, [sp, #-16]!
	stp	x0, x4, [sp, #-16]!
	mov	x0, sp
.endm

/*
 * Enter Exception.
 * This will save the processor state that is ELR/X0~X30
 * to the stack frame.
 */
.macro exception_entry
	stp	x29, x30, [sp, #-16]!
	stp	x27, x28, [sp, #-16]!
	stp	x25, x26, [sp, #-16]!
	stp	x23, x24, [sp, #-16]!
	stp	x21, x22, [sp, #-16]!
	stp	x19, x20, [sp, #-16]!
	stp	x17, x18, [sp, #-16]!
	stp	x15, x16, [sp, #-16]!
	stp	x13, x14, [sp, #-16]!
	stp	x11, x12, [sp, #-16]!
	stp	x9, x10, [sp, #-16]!
	stp	x7, x8, [sp, #-16]!
	stp	x5, x6, [sp, #-16]!
	stp	x3, x4, [sp, #-16]!
	stp	x1, x2, [sp, #-16]!
.endm

_bad_mode:
	/* Could be running at EL3/EL2/EL1 */
	switch_el x11, 3f, 2f, 1f
	save_el
	bl	bad_mode
	b	.

_do_irq:
	/* Could be running at EL3/EL2/EL1 */
	switch_el x11, 3f, 2f, 1f
	save_el
	bl	do_irq
	b	exception_exit

sync_exception_aarch64:
	switch_el x11, 3f, 2f, 1f
	save_el
	bl 	std_svc_handler
	b	exception_exit

exception_exit:
	ldp	x0, x4, [sp],#16
	ldp	x3, x0, [sp],#16
	switch_el x11, 3f, 2f, 1f
3:
	msr	spsr_el3, x4
	msr	elr_el3, x3
	b	0f
2:
	msr	spsr_el2, x4
	msr	elr_el2,  x3
	b	0f
1:
	msr	spsr_el1, x4
	msr	elr_el1,  x3
0:
	ldp	x1, x2, [sp],#16
	ldp	x3, x4, [sp],#16
	ldp	x5, x6, [sp],#16
	ldp	x7, x8, [sp],#16
	ldp	x9, x10, [sp],#16
	ldp	x11, x12, [sp],#16
	ldp	x13, x14, [sp],#16
	ldp	x15, x16, [sp],#16
	ldp	x17, x18, [sp],#16
	ldp	x19, x20, [sp],#16
	ldp	x21, x22, [sp],#16
	ldp	x23, x24, [sp],#16
	ldp	x25, x26, [sp],#16
	ldp	x27, x28, [sp],#16
	ldp	x29, x30, [sp],#16
	eret

/* reason: SYNC=0 IRQ=1 FIQ=2 SError=3 */
.macro ventry, label, reason
.align 7, 0
	exception_entry
	mov	x2, #\reason
	b	\label
.endm

.globl vectors
.align 11, 0
vectors:
	/* -----------------------------------------------------------
	 * Current EL with SP_EL0 : 0x0 - 0x200
	 * ----------------------------------------------------------- */
sync_sp_el0:
	ventry _bad_mode, 0
irq_sp_el0:
	ventry _bad_mode, 1
fiq_sp_el0:
	ventry _bad_mode, 2
serror_sp_el0:
	ventry _bad_mode, 3
	/* -----------------------------------------------------------
	 * Current EL with SP_ELx: 0x200 - 0x400
	 * ----------------------------------------------------------- */
sync_sp_elx:
	ventry sync_exception_aarch64, 0
irq_sp_elx:
	ventry _do_irq,   1
fiq_sp_elx:
	ventry _do_irq,   2
serror_sp_elx:
	ventry _bad_mode, 3
	/* -----------------------------------------------------------
	 * Lower EL using AArch64 : 0x400 - 0x600
	 * ----------------------------------------------------------- */
sync_aarch64:
	ventry sync_exception_aarch64, 0
irq_aarch64:
	ventry _bad_mode, 1
fiq_aarch64:
	ventry _bad_mode, 2
serror_aarch64:
	ventry _bad_mode, 3
	/* -----------------------------------------------------------
	 * Lower EL using AArch32 : 0x600 - 0x800
	 * ----------------------------------------------------------- */
sync_aarch32:
	ventry _bad_mode, 0
irq_aarch32:
	ventry _bad_mode, 1
fiq_aarch32:
	ventry _bad_mode, 2
serror_aarch32:
	ventry _bad_mode, 3


/****************** data section starts here ******************/
.section .data, "aw"
.global cpus_boot_cpu
/* unsigned long cpus_boot_cpu; */
cpus_boot_cpu:  .quad   MAX_CPU_NUM
