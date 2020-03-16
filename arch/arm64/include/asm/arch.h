#ifndef __ARM64_ARCH_H_INCLUDE__
#define __ARM64_ARCH_H_INCLUDE__

#include <asm/sysop.h>
#include <asm/falkor.h>

#ifndef __ASSEMBLY__
static inline void cpu_relax(void)
{
	yield();
}

int arch_early_init(void);
int arch_late_init(uint64_t cpu_freq, uint64_t llc_freq);

uint64_t get_cpu_freq(void);
uint64_t get_llc_freq(void);
void set_cpu_freq(uint64_t freq);
void set_llc_freq(uint64_t freq);

uint64_t __get_cpu_freq(uint8_t cluster);
void __set_cpu_freq(uint8_t cluster, uint64_t freq);
#endif

#endif /* __ARM64_ARCH_H_INCLUDE__ */
