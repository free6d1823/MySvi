#ifndef __ASM_ATOMIC_LL_SC_H
#define __ASM_ATOMIC_LL_SC_H

typedef struct {
	int counter;
}atomic_t;

typedef struct {
	long long counter;
}atomic64_t;

#define ATOMIC_INIT(i)    { (i) }

#define WRITE_ONCE(x, val)              (*(volatile typeof(x) *)&(x) = val)

#define atomic_read(v)                  ACCESS_ONCE((v)->counter)
#define atomic_set(v, i)                WRITE_ONCE(((v)->counter), (i))

#define __LL_SC_INLINE static inline
#define __LL_SC_PREFIX(x) __ll_sc_##x


#define ATOMIC_OP(op, asm_op)						\
__LL_SC_INLINE void							\
__LL_SC_PREFIX(atomic_##op(int i, atomic_t *v))				\
{									\
	unsigned long tmp;						\
	int result;							\
									\
	asm volatile("// atomic_" #op "\n"				\
"	prfm	pstl1strm, %2\n"					\
"1:	ldxr	%w0, %2\n"						\
"	" #asm_op "	%w0, %w0, %w3\n"				\
"	stxr	%w1, %w0, %2\n"						\
"	cbnz	%w1, 1b"						\
	: "=&r" (result), "=&r" (tmp), "+Q" (v->counter)		\
	: "Ir" (i));							\
}									\

ATOMIC_OP(add, add)
ATOMIC_OP(sub, sub)
ATOMIC_OP(and, and)
ATOMIC_OP(andnot, bic)
ATOMIC_OP(or, orr)
ATOMIC_OP(xor, eor)

#undef ATOMIC_OP

#define ATOMIC64_OP(op, asm_op)						\
__LL_SC_INLINE void							\
__LL_SC_PREFIX(atomic64_##op(long i, atomic64_t *v))			\
{									\
	long result;							\
	unsigned long tmp;						\
									\
	asm volatile("// atomic64_" #op "\n"				\
"	prfm	pstl1strm, %2\n"					\
"1:	ldxr	%0, %2\n"						\
"	" #asm_op "	%0, %0, %3\n"					\
"	stxr	%w1, %0, %2\n"						\
"	cbnz	%w1, 1b"						\
	: "=&r" (result), "=&r" (tmp), "+Q" (v->counter)		\
	: "Ir" (i));							\
}									\

ATOMIC64_OP(add, add)
ATOMIC64_OP(sub, sub)
ATOMIC64_OP(and, and)
ATOMIC64_OP(andnot, bic)
ATOMIC64_OP(or, orr)
ATOMIC64_OP(xor, eor)

#undef ATOMIC64_OP

#endif	/* __ASM_ATOMIC_LL_SC_H */
