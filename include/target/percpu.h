/*
 */
#ifndef __TESTOS_PERCPU_H_INCLUDE__
#define __TESTOS_PERCPU_H_INCLUDE__

#include <stddef.h>
#include <stdint.h>
#include <target/compiler.h>
#include <target/smp.h>

#define PERCPU_INPUT(cacheline)	\
	. = ALIGN(cacheline);	\
	__percpu_start = .;	\
	*(.sysdata..percpu)	\
	. = ALIGN(cacheline);	\
	__percpu_end = .;

#ifdef __ASSEMBLY__
#ifndef LINKER_SCRIPT
.macro asm_get_percpu_addr _var:req, _tmp:req, _res=x0
	asm_smp_processor_id \_tmp, \_res
	ldr	\_tmp, =__percpu_offset
	ldr	\_tmp, [\_tmp, \_res, lsl #3]
	ldr     \_res, =percpu_\_var
	add     \_res, \_res, \_tmp
.endm
#endif
#else
extern uintptr_t __percpu_start[];
extern uintptr_t __percpu_end[];

#define PERCPU_START		((uint64_t)&__percpu_start)
#define PERCPU_END		((uint64_t)&__percpu_end)

#ifdef CONFIG_SMP
#ifdef CONFIG_PERCPU_INTERLEAVE
#define DEFINE_PERCPU(type, name)	\
	__attribute__((__section__(".sysdata..percpu"))) \
	__typeof__(type) percpu_##name[NR_CPUS]
#define get_percpu(var)		(percpu_##var[smp_processor_id()])
#define get_percpu_hmp(var)	get_percpu(var)
#else
#define DEFINE_PERCPU(type, name)	\
	__attribute__((__section__(".sysdata..percpu"))) \
	__typeof__(type) percpu_##name

extern uint64_t __percpu_offset[NR_CPUS];
#define percpu_offset(x)	(__percpu_offset[x])
#define thiscpu_offset		percpu_offset(smp_processor_id())

#define percpu_reloc(var, cpu)	(*RELOC_HIDE(&percpu_##var, percpu_offset(cpu)))
#define get_percpu(var)		percpu_reloc(var, smp_processor_id())
#define get_percpu_hmp(var)	percpu_reloc(var, hmp_processor_id())
#endif
#else
#define DEFINE_PERCPU(type, name)	\
	__typeof__(type) percpu_##name

#define get_percpu(var)		percpu_##var
#define get_percpu_hmp(var)	get_percpu(var)
#endif

caddr_t percpu_get_free_area(uint8_t cpu);
int percpu_init(void);
#endif /* __ASSEMBLY__ */

#endif /* __TESTOS_PERCPU_H_INCLUDE__ */
