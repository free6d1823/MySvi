#ifndef CONTEXT_H
#define CONTEXT_H

#include <target/compiler.h>
/*******************************************************************************
  * Constants that allow assembler code to access members of and the 'gp_regs'
  * structure at their correct offsets.
  ******************************************************************************/
#define CTX_GPREGS_OFFSET   (0x0)
#define CTX_GPREG_X0        (0x0)
#define CTX_GPREG_X1        (0x8)
#define CTX_GPREG_X2        (0x10)
#define CTX_GPREG_X3        (0x18)
#define CTX_GPREG_X4        (0x20)
#define CTX_GPREG_X5        (0x28)
#define CTX_GPREG_X6        (0x30)
#define CTX_GPREG_X7        (0x38)
#define CTX_GPREG_X8        (0x40)
#define CTX_GPREG_X9        (0x48)
#define CTX_GPREG_X10       (0x50)
#define CTX_GPREG_X11       (0x58)
#define CTX_GPREG_X12       (0x60)
#define CTX_GPREG_X13       (0x68)
#define CTX_GPREG_X14       (0x70)
#define CTX_GPREG_X15       (0x78)
#define CTX_GPREG_X16       (0x80)
#define CTX_GPREG_X17       (0x88)
#define CTX_GPREG_X18       (0x90)
#define CTX_GPREG_X19       (0x98)
#define CTX_GPREG_X20       (0xa0)
#define CTX_GPREG_X21       (0xa8)
#define CTX_GPREG_X22       (0xb0)
#define CTX_GPREG_X23       (0xb8)
#define CTX_GPREG_X24       (0xc0)
#define CTX_GPREG_X25       (0xc8)
#define CTX_GPREG_X26       (0xd0)
#define CTX_GPREG_X27       (0xd8)
#define CTX_GPREG_X28       (0xe0)
#define CTX_GPREG_X29       (0xe8)
#define CTX_GPREG_LR        (0xf0)
#define CTX_GPREG_SP_EL0    (0xf8)
#define CTX_GPREGS_END      (0x100)

/*******************************************************************************
 * Constants that allow assembler code to access members of and the 'el3_state'
 * structure at their correct offsets. Note that some of the registers are only
 * 32-bits wide but are stored as 64-bit values for convenience
 ******************************************************************************/
#define CTX_EL3STATE_OFFSET (CTX_GPREGS_OFFSET + CTX_GPREGS_END)
#define CTX_SCR_EL3     0x0
#define CTX_RUNTIME_SP      0x8
#define CTX_SPSR_EL3        0x10
#define CTX_ELR_EL3     0x18
#define CTX_EL3STATE_END    0x20

#ifndef __ASSEMBLY__
#define DWORD_SHIFT		3
#define DEFINE_REG_STRUCT(name, num_regs)	\
	typedef struct name {			\
		uint64_t _regs[num_regs];	\
	}   name##_t

/* Constants to determine the size of individual context structures */
#define CTX_GPREG_ALL		(CTX_GPREGS_END >> DWORD_SHIFT)

/*
 * AArch64 general purpose register context structure. Usually x0-x18,
 * lr are saved as the compiler is expected to preserve the remaining
 * callee saved registers if used by the C runtime and the assembler
 * does not touch the remaining. But in case of world switch during
 * exception handling, we need to save the callee registers too.
 */
//DEFINE_REG_STRUCT(gp_regs, CTX_GPREG_ALL);

typedef struct gp_regs {
    uint64_t _regs[32];
} gp_regs_t;


/*
 * Macros to access members of any of the above structures using their
 * offsets
 */
#define write_ctx_reg(ctx, offset, val) (((ctx)->_regs[offset >> DWORD_SHIFT]) \
                             = val)
#define get_gpregs_ctx(h)   (&((cpu_context_t *) h)->gpregs_ctx)


typedef struct cpu_context {
	gp_regs_t gpregs_ctx;
} cpu_context_t;

#endif

#endif

