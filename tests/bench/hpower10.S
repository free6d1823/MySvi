// ------------------------------------------------------------
// ARMv8-A separate core program
//
// Description: Test case
// ------------------------------------------------------------

#ifdef TESTOS
#include <target/raven.h>
#include <target/cache.h>
#else
#include "test_defines.h"
#endif

#define HPOWER10_CORE_REPEATS		10000
#define HPOWER10_CORE_AREA_SIZE		2*L1_CACHE_SIZE
#define HPOWER10_CORE_AREA_ALIGN	L2_CACHE_SIZE
#define HPOWER10_CORE_DATA_SIZE		4

	.pushsection .rodata
#ifdef TESTOS
ENTRY(hpower10_data)
#endif
	.long 0x49249249
	.long 0x3ff29249
	.long 0x49249249
	.long 0x3ff29249
	.long 0x92492492
	.long 0x3ff24924
	.long 0x92492492
	.long 0x3ff24924
	.long 0x49249249
	.long 0x3ff29249
	.long 0x49249249
	.long 0x3ff29249
	.long 0x92492492
	.long 0x3ff24924
	.long 0x92492492
	.long 0x3ff24924
	.long 0xffffffff
	.long 0x3fffffff
	.long 0xffffffff
	.long 0x3fffffff
	.long 0x10000000
	.long 0x44000000
	.long 0x10000000
	.long 0x44000000
	.long 0xffffffff
	.long 0x3fffffff
	.long 0xffffffff
	.long 0x3fffffff
	.long 0x10000000
	.long 0x44000000
	.long 0x10000000
	.long 0x44000000
	.long 0xffffffff
	.long 0x3fffffff
	.long 0xffffffff
	.long 0x3fffffff
	.long 0x10000000
	.long 0x44000000
	.long 0x10000000
	.long 0x44000000
	.long 0xffffffff
	.long 0x3fffffff
	.long 0xffffffff
	.long 0x3fffffff
	.long 0x10000000
	.long 0x44000000
	.long 0x10000000
	.long 0x44000000
#ifdef TESTOS
ENDOBJ(hpower10_data)
#endif

#ifdef TESTOS
ENTRY(hpower10_mem)
#endif
	.long 0xffffffff
	.long 0x3fffffff
	.long 0xffffffff
	.long 0x3fffffff
	.long 0x00000000
	.long 0x44000000
	.long 0x00000000
	.long 0x44000000
	.long 0xffffffff
	.long 0x3fffffff
	.long 0xffffffff
	.long 0x3fffffff
	.long 0x00000000
	.long 0x44000000
	.long 0x00000000
	.long 0x44000000
#ifdef TESTOS
ENDOBJ(hpower10_mem)
#endif
	.popsection

#ifdef TESTOS
ENTRY(hpower10_core)
#else
	.global hpower10_core
	.type hpower10_core, "function"
	.cfi_startproc
#endif
	// The original powervirus prototype is as follows:
	// void powervirus(int loop, void *data, void *pb, void *pe);
	//
	// In cpus test pattern mode:
	// loop: can be handled by the external framework, and have a
	//       configurable value here for a single step run.
	// data: pointing to the fixed test data of hpower10_data.
	// pb=x0: start of the percpu test area, need to copy hpower10_mem
	//        to fill this area.
	// pe=x0+0x2000: end of the percpu area

	// Prepare the percpu test area
	ldr	x1, =hpower10_mem
	mov	x2, x0
	mov	x3, #0x10
	mov	x19, #(HPOWER10_CORE_AREA_SIZE/HPOWER10_CORE_DATA_SIZE)
1:
	mov	x20, #0x0	// Counter 0-0x10
2:
	ldr	w21, [x1], #4
	str	w21, [x2], #4
	add	x20, x20, #0x1
	cmp	x20, x3
	blt	2b
	subs	x19, x19, x20
	cmp	x19, xzr
	bgt	1b

	// Prepare the original powervirus parameters
	// - x1, the loop counter
	// - x3, hpower10_data
	// - x6, *pb
	// - x7, *pe
	mov	x6, x0
	add	x7, x0, HPOWER10_CORE_AREA_SIZE
	mov	x1, #HPOWER10_CORE_REPEATS
	ldr	x3, =hpower10_data

	// Execute powervirus
	stp     q8, q9, [sp,#-64]!
	stp     q10, q11, [sp,#-64]!
	stp     q12, q13, [sp,#-64]!
	stp     q14, q15, [sp,#-64]!
	movi    v0.2d, #0x0
	movi    v1.2d, #0x0
	movi    v2.2d, #0x0
	movi    v3.2d, #0x0
	movi    v4.2d, #0x0
	movi    v5.2d, #0x0
	movi    v6.2d, #0x0
	movi    v7.2d, #0x0
	movi    v8.2d, #0x0
	ldr     q9, [x3],#16
	ldr     q10, [x3],#16
	ldr     q11, [x3],#16
	ldr     q12, [x3],#16
	ldr     q16, [x3],#16
	ldr     q17, [x3],#16
	ldr     q18, [x3],#16
	ldr     q19, [x3],#16
	ldr     q20, [x3],#16
	ldr     q21, [x3],#16
	ldr     q22, [x3],#16
	ldr     q23, [x3],#16
	ldr     q24, [x3],#16
	mov     x5, x6
	mov     x4, x7

PRELOAD_L2:
	prfm    pldl2keep, [x5]
	add     x5, x5, #0x80
	prfm    pldl2keep, [x5]
	add     x5, x5, #0x80
	prfm    pldl2keep, [x5]
	add     x5, x5, #0x80
	prfm    pldl2keep, [x5]
	add     x5, x5, #0x80
	cmp     x5, x4
	b.lt    PRELOAD_L2
	dsb     ish
	isb
	mov     x4, #0xff

WAIT:
	subs    x4, x4, #0x1
	b.ne    WAIT
	mov     x0, #0x20                       // #32
	mov     x5, x6
	b       DGEMMSTART
DGEMMSTART:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
LOOP:
	ld1     {v18.2d}, [x5], #16
	fmla    v0.2d, v9.2d, v16.2d
	ld1     {v19.2d}, [x5], #16
	fmla    v1.2d, v10.2d, v17.2d
	fmla    v2.2d, v11.2d, v16.2d
	subs    x0, x0, #0x1
	ld1     {v20.2d}, [x5], #16
	fmla    v3.2d, v12.2d, v17.2d
	b.ne    LOOP
	fmla    v0.2d, v9.2d, v16.2d
	mov     x5, x6
	fmla    v1.2d, v10.2d, v17.2d
	mov     x0, #0x20                       // #32
	fmla    v2.2d, v11.2d, v16.2d
	subs    x1, x1, #0x1
	ld1     {v20.2d}, [x5], #16
	fmla    v3.2d, v12.2d, v17.2d
	b.ne    LOOP
	ldp     q14, q15, [sp],#64
	ldp     q12, q13, [sp],#64
	ldp     q10, q11, [sp],#64
	ldp     q8, q9, [sp],#64
	ret
	nop
	nop
	nop
	nop
	nop
	nop
	nop

pass:
	mov	w9, 1
_skip_pass:
#ifdef TESTOS
	mov	w0, w9
#else
#ifdef RTL_SIM
	movk	x8, #0xFFC0
	movk	x8, #0x7003, lsl #16
	movk	x8, #0x10FF, lsl #32
	movk	x8, #0x1000, lsl #48
#else
	movk	x8, #0xFFC0
	movk	x8, #0x8003, lsl #16
	movk	x8, #0x1000, lsl #32
	movk	x8, #0x1000, lsl #48
#endif
	str	x30, [sp, #-0x8]	// x30 is lr
	bl	GetCPUID		// 0-47
	add	x8, x8, x1
	strb	w9, [x8, #0]
	nop
	dsb	ish
	ldr	x30, [sp, #-0x8]
#endif
	ret
#ifdef TESTOS
ENDPROC(hpower10_core)
define_asm_testfn hpower10_core HPOWER10_CORE_AREA_SIZE \
		  HPOWER10_CORE_AREA_ALIGN 1 CPU_EXEC_META
#else
	.cfi_endproc
#endif
