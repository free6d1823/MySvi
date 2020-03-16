#ifndef __ASM_ATOMIC_LSE_H
#define __ASM_ATOMIC_LSE_H

#define __LSE_PREFIX(x) __lse_##x
#define __LL_SC_CLOBBERS "x16", "x17", "x30"

#define ATOMIC_OP(op, asm_op)						\
static inline void									\
__LSE_PREFIX(atomic_##op(int i, atomic_t *v))			\
{									\
	register int w0 asm ("w0") = i;					\
	register atomic_t *x1 asm ("x1") = v;				\
									\
	asm volatile(									\
	"	" #asm_op "	%w[i], %[v]\n"					\
	: [i] "+r" (w0), [v] "+Q" (v->counter)				\
	: "r" (x1)							\
	: __LL_SC_CLOBBERS);						\
}

ATOMIC_OP(andnot, stclr)
ATOMIC_OP(or, stset)
ATOMIC_OP(xor, steor)
ATOMIC_OP(add, stadd)

#undef ATOMIC_OP

static inline void
__LSE_PREFIX(atomic_and(int i, atomic_t *v))
{
	register int w0 asm ("w0") = i;
	register atomic_t *x1 asm ("x1") = v;

	asm volatile(
	"	mvn	%w[i], %w[i]\n"
	"	stclr	%w[i], %[v]"
	: [i] "+r" (w0), [v] "+Q" (v->counter)
	: "r" (x1)
	: __LL_SC_CLOBBERS);
}

static inline void
__LSE_PREFIX(atomic_sub(int i, atomic_t *v))
{
	register int w0 asm ("w0") = i;
	register atomic_t *x1 asm ("x1") = v;

	asm volatile(
	"	neg	%w[i], %w[i]\n"
	"	stadd	%w[i], %[v]"
	: [i] "+r" (w0), [v] "+Q" (v->counter)
	: "r" (x1)
	: __LL_SC_CLOBBERS);
}


#define ATOMIC64_OP(op, asm_op)						\
static inline void					\
__LSE_PREFIX(atomic64_##op(long i, atomic64_t *v))			\
{									\
	register long x0 asm ("x0") = i;				\
	register atomic64_t *x1 asm ("x1") = v;				\
									\
	asm volatile(					\
"	" #asm_op "	%[i], %[v]\n"					\
	: [i] "+r" (x0), [v] "+Q" (v->counter)				\
	: "r" (x1)							\
	: __LL_SC_CLOBBERS);						\
}

ATOMIC64_OP(andnot, stclr)
ATOMIC64_OP(or, stset)
ATOMIC64_OP(xor, steor)
ATOMIC64_OP(add, stadd)

#undef ATOMIC64_OP

static inline void
__LSE_PREFIX(atomic64_and(long i, atomic64_t *v))
{
	register long x0 asm ("x0") = i;
	register atomic64_t *x1 asm ("x1") = v;

	asm volatile(
	"	mvn	%[i], %[i]\n"
	"	stclr	%[i], %[v]"
	: [i] "+r" (x0), [v] "+Q" (v->counter)
	: "r" (x1)
	: __LL_SC_CLOBBERS);
}

static inline void
__LSE_PREFIX(atomic64_sub(long i, atomic64_t *v))
{
	register long x0 asm ("x0") = i;
	register atomic64_t *x1 asm ("x1") = v;

	asm volatile(
	"	neg	%[i], %[i]\n"
	"	stadd	%[i], %[v]"
	: [i] "+r" (x0), [v] "+Q" (v->counter)
	: "r" (x1)
	: __LL_SC_CLOBBERS);
}

static inline long
__LSE_PREFIX(atomic64_dec_if_positive(atomic64_t *v))
{
	register long x0 asm ("x0") = (long)v;

	asm volatile(
	"1:	ldr	x30, %[v]\n"
	"	subs	%[ret], x30, #1\n"
	"	b.lt	2f\n"
	"	casal	x30, %[ret], %[v]\n"
	"	sub	x30, x30, #1\n"
	"	sub	x30, x30, %[ret]\n"
	"	cbnz	x30, 1b\n"
	"2:"
	: [ret] "+&r" (x0), [v] "+Q" (v->counter)
	:
	: __LL_SC_CLOBBERS, "cc", "memory");

	return x0;
}

#endif	/* __ASM_ATOMIC_LSE_H */
