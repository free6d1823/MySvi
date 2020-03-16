#include <asm/psci.h>
#include <target/memory.h>
#include <asm/barrier.h>
#include <target/cache.h>

#define RESET_CTRL(cpu)	((uint64_t)SYSREG_BASE + 0x10 * (cpu > 4 ? (cpu - 1) : cpu))
#define RVBAR_L(cpu)	(RESET_CTRL(cpu) + 4)

#ifdef BOOT_CORE
uint64_t CPU_HOLD_BASE[MAX_CPU_NUM];
#endif

int psci_cpu_on(uint64_t target_cpu,
                uint64_t entrypoint,
                uint64_t context_id)
{
	uint8_t cpu = (target_cpu >> 8) & 0xff;

	if (cpu == 4 && cpu >= 8)
		return PSCI_E_INVALID_PARAMS;

	entry_addr = entrypoint;
	flush_dcache_addr(&entry_addr);

#ifdef BOOT_CORE
	__raw_writel(1, (uint64_t)(CPU_HOLD_BASE + cpu));
	flush_dcache_addr(CPU_HOLD_BASE + cpu);
	sev();
#endif

	__raw_writel((uint64_t)_start, RVBAR_L(cpu));
	__raw_writel(1, RESET_CTRL(cpu));

	return PSCI_E_SUCCESS;
}