	.macro def_fn f p2align=0
	.text
	.p2align \p2align
	.global \f
	.type \f, %function
\f:
	.endm

def_fn powervirus p2align=6
	stp     q8, q9, [sp,#-64]!
	stp     q10, q11, [sp,#-64]!
	stp     q12, q13, [sp,#-64]!
	stp     q14, q15, [sp,#-64]!
	mov     x6, x2
	mov     x7, x3
	mov     x3, x1
	mov     x1, x0
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

def_fn stress_cbf p2align=6
        stp     x29, x30, [sp,#-96]!
        stp     x19, x20, [sp,#16]
        stp     x21, x22, [sp,#32]
        stp     x23, x24, [sp,#48]
        stp     x25, x26, [sp,#64]
        stp     x27, x28, [sp,#80]
        stp     x7, x8, [sp,#-64]!
        stp     x16, x17, [sp,#-64]!
        stp     x18, x19, [sp,#-64]!
        add     x28, x0, #0x0
        mov     x27, #0x0                       // #0
        add     x26, x2, #0x0

data_copy_loop:
        ldr     w4, [x0]
        ldr     w5, [x0,#128]
        ldr     w6, [x0,#256]
        ldr     w7, [x0,#384]
        ldr     w8, [x0,#512]
        ldr     w9, [x0,#640]
        ldr     w10, [x0,#768]
        ldr     w11, [x0,#896]
        ldr     w12, [x0,#1024]
        ldr     w13, [x0,#1152]
        ldr     w14, [x0,#1280]
        ldr     w19, [x0,#1408]
        ldr     w20, [x0,#1536]
        ldr     w21, [x0,#1664]
        ldr     w22, [x0,#1792]
        ldr     w23, [x0,#1920]

        str     w4, [x2]
        str     w5, [x2,#128]
        str     w6, [x2,#256]
        str     w7, [x2,#384]
        str     w8, [x2,#512]
        str     w9, [x2,#640]
        str     w10, [x2,#768]
        str     w11, [x2,#896]
        str     w12, [x2,#1024]
        str     w13, [x2,#1152]
        str     w14, [x2,#1280]
        str     w19, [x2,#1408]
        str     w20, [x2,#1536]
        str     w21, [x2,#1664]
        str     w22, [x2,#1792]
        str     w23, [x2,#1920]

        ldr     w4, [x0,#2048]
        ldr     w5, [x0,#2176]
        ldr     w6, [x0,#2304]
        ldr     w7, [x0,#2432]
        ldr     w8, [x0,#2560]
        ldr     w9, [x0,#2688]
        ldr     w10, [x0,#2816]
        ldr     w11, [x0,#2944]
        ldr     w12, [x0,#3072]
        ldr     w13, [x0,#3200]
        ldr     w14, [x0,#3328]
        ldr     w19, [x0,#3456]
        ldr     w20, [x0,#3584]
        ldr     w21, [x0,#3712]
        ldr     w22, [x0,#3840]
        ldr     w23, [x0,#3968]

        str     w4, [x2,#2048]
        str     w5, [x2,#2176]
        str     w6, [x2,#2304]
        str     w7, [x2,#2432]
        str     w8, [x2,#2560]
        str     w9, [x2,#2688]
        str     w10, [x2,#2816]
        str     w11, [x2,#2944]
        str     w12, [x2,#3072]
        str     w13, [x2,#3200]
        str     w14, [x2,#3328]
        str     w19, [x2,#3456]
        str     w20, [x2,#3584]
        str     w21, [x2,#3712]
        str     w22, [x2,#3840]
        str     w23, [x2,#3968]

        add     x0, x0, #0x1, lsl #12
        add     x2, x2, #0x1, lsl #12
        cmp     x0, x1
        b.lt    data_copy_loop

        add     x0, x28, #0x0
        add     x2, x26, #0x0
        add     x27, x27, #0x1
        cmp     x27, x3
        b.lt    data_copy_loop

        ldp     x18, x19, [sp],#64
        ldp     x16, x17, [sp],#64
        ldp     x7, x8, [sp],#64
        ldp     x19, x20, [sp,#16]
        ldp     x21, x22, [sp,#32]
        ldp     x23, x24, [sp,#48]
        ldp     x25, x26, [sp,#64]
        ldp     x27, x28, [sp,#80]
        ldp     x29, x30, [sp],#96
        ret
        nop

def_fn aw_powervirus2 p2align=6
    stp     q8, q9, [sp,#-64]!
        stp     q10, q11, [sp,#-64]!
        stp     q12, q13, [sp,#-64]!
        stp     q14, q15, [sp,#-64]!
        mov     x7, x0
        mov     x4, x2
        movi    v0.2d, #0x0
        movi    v1.2d, #0x0
        movi    v2.2d, #0x0
        movi    v3.2d, #0x0
        movi    v4.2d, #0x0
        movi    v5.2d, #0x0
        movi    v6.2d, #0x0
        movi    v7.2d, #0x0
        movi    v8.2d, #0x0
        mov     x0, x1
        ldr     q9, [x0],#16
        ldr     q10, [x0],#16
        ldr     q11, [x0],#16
        ldr     q12, [x0],#16
        ldr     q16, [x0],#16
        ldr     q17, [x0],#16
        ldr     q18, [x0],#16
        ldr     q19, [x0],#16
        ldr     q20, [x0],#16
        ldr     q21, [x0],#16
        ldr     q22, [x0],#16
        ldr     q23, [x0],#16
        ldr     q24, [x0],#16
        mov     x0, x7
        b       VIRUS
        nop

VIRUS:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        mov     x1, #0x200                      // #512
        mov     x3, x4

LOOP_AW2:
    ldr     q18, [x3],#64
        fmla    v0.2d, v9.2d, v16.2d
        ldr     q19, [x3],#32
        fmla    v1.2d, v10.2d, v17.2d
        fmla    v2.2d, v11.2d, v16.2d
        subs    x1, x1, #0x1
        ldr     q20, [x3],#32
        fmla    v3.2d, v12.2d, v17.2d
        b.ne    LOOP_AW2
        subs    x0, x0, #0x1
        mov     x1, #0x200                      // #512
        mov     x3, x4
        b.ne    LOOP_AW2
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
