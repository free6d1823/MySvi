#include <asm/psci.h>
#include <target/memory.h>
#include <asm/barrier.h>
#include <target/cache.h>

int psci_cpu_on(uint64_t target_cpu,
                uint64_t entrypoint,
                uint64_t context_id)
{
	uint8_t cpu = target_cpu & 0xff;

	entry_addr = entrypoint;
	flush_dcache_addr(&entry_addr);

	__raw_writel(1, (uint64_t)CPU_HOLD_BASE + (cpu << 3));

	sev();

	return PSCI_E_SUCCESS;
}