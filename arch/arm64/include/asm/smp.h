/*
 */
#ifndef __ARM64_SMP_H_INCLUDE__
#define __ARM64_SMP_H_INCLUDE__

#include <target/memory.h>

#define CORTEXA76_MIDR_PARTNUM   0xd0b
#define CORTEXA55_MIDR_PARTNUM   0xd05

#define MIDR_PARTNUM_SHIFT  4
#define MIDR_PARTNUM_MASK   0xfff

#define INVALID_MPIDR		0xffffffffffffffff

#define MPIDR_UP_BITMASK	(0x1 << 30)
#define MPIDR_MT_BITMASK	(0x1 << 24)
#define MPIDR_HWID_BITMASK	UL(0xff00ffffff)

#define MPIDR_LEVEL_BITS_SHIFT	3
#define MPIDR_LEVEL_BITS	(1 << MPIDR_LEVEL_BITS_SHIFT)
#define MPIDR_LEVEL_MASK	((1 << MPIDR_LEVEL_BITS) - 1)

#define MPIDR_LEVEL_SHIFT(level) \
	(((1 << level) >> 1) << MPIDR_LEVEL_BITS_SHIFT)

#define MPIDR_AFFINITY_LEVEL(mpidr, level) \
	((mpidr >> MPIDR_LEVEL_SHIFT(level)) & MPIDR_LEVEL_MASK)

#define MPIDR_RS(mpidr)			(((mpidr) & 0xF0UL) >> 4)

#ifdef __ASSEMBLY__
#ifndef LINKER_SCRIPT
.macro asm_smp_processor_id _tmp:req, _res=x0
	mov	\_res, sp
	ldr	\_tmp, =STACKS_START
	sub	\_res, \_res, \_tmp
	ubfx	\_res, \_res, #STACK_SHIFT, #(32 - STACK_SHIFT)
.endm
#endif
#else

enum ipi_msg_type {
	IPI_SCHEDULE = 0,
	IPI_ACK,
	IPI_END
};

static inline uint8_t __smp_processor_id(void)
{
	uintptr_t t;

	asm volatile ("mov %0, sp\n\t" : "=r" (t));
	return (uint8_t)((t - STACKS_START) >> 12);
}

static inline uint8_t __hmp_processor_id(void)
{
	uint8_t cpu = __smp_processor_id();

	return cpu >= NR_CPUS ? NR_CPUS : cpu;
}

static inline uintptr_t __smp_processor_stack_top(void)
{
	uintptr_t t;

	asm volatile ("mov %0, sp\n\t" : "=r" (t));
	return ALIGN_UP(t, STACK_SIZE);
}

unsigned int plat_my_core_pos(void);
uint64_t get_mpidr(int cpu);
void smp_register_cpu();
void handle_IPI(int ipinr);
void sgi_send(int cpu, int irq);
#endif

#endif /* __ARM64_SMP_H_INCLUDE__ */
