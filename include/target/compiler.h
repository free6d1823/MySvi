#ifndef __COMPILER_H_INCLUDE__
#define __COMPILER_H_INCLUDE__

#define __dead2		__attribute__((__noreturn__))
#define __aligned(x)	__attribute__((aligned(x)))
#define __used		__attribute__((__used__))
#define __maybe_unused	__attribute__((unused))
#define __barrier()	__asm__ __volatile__("": : :"memory")
#define __section(S)	__attribute__((__section__(#S)))
#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)

#define ACCESS_ONCE(x)	(*(volatile typeof(x) *)&(x))
#define RELOC_HIDE(ptr, off)						\
({									\
	unsigned long __ptr;						\
	__asm__ ("" : "=r"(__ptr) : "0"(ptr));				\
	(typeof(ptr)) (__ptr + (off));					\
})

#include <target/compiler_gcc.h>

#endif /* __COMPILER_H_INCLUDE__ */
