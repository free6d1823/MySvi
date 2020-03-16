/*
 */
#ifndef __QDF2400_FALKOR_H_INCLUDE__
#define __QDF2400_FALKOR_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>
#include <asm/mach/cpus.h>

#define CPU_CLUSTER_MASK	((1ULL << CPUS_PER_CLUSTER) - 1)
#define CPU_TO_CLUSTER(cpu)	((cpu) / CPUS_PER_CLUSTER)
#define CLUSTER_TO_CPU_MASK(duplex)	\
        (CPU_CLUSTER_MASK << ((duplex) * CPUS_PER_CLUSTER))

#define CPU_RAIL_MASK		((1ULL << CPUS_PER_RAIL) - 1)
#define CPU_TO_RAIL(cpu)	((cpu) / CPUS_PER_RAIL)
#define RAIL_TO_CPU_MASK(cluster)	\
        (CPU_RAIL_MASK << ((cluster) * CPUS_PER_RAIL))

#define CMD_INVALID_CPU_MASKS	0

#ifndef __ASSEMBLY__
static inline uint32_t get_apc_mask(uint64_t cpu_mask)
{
	uint64_t apc_mask = cpu_mask;

	apc_mask = (((apc_mask) & ULL(0xaaaaaaaaaaaaaaaa)) >> 1) |
		    ((apc_mask) & ULL(0x5555555555555555));
	apc_mask = (((apc_mask) & ULL(0x4444444444444444)) >> 1) |
		    ((apc_mask) & ULL(0x1111111111111111));
	apc_mask = (((apc_mask) & ULL(0x3030303030303030)) >> 2) |
		    ((apc_mask) & ULL(0x0303030303030303));
	apc_mask = (((apc_mask) & ULL(0x0f000f000f000f00)) >> 4) |
		    ((apc_mask) & ULL(0x000f000f000f000f));
	apc_mask = (((apc_mask) & ULL(0x00ff000000ff0000)) >> 8) |
		    ((apc_mask) & ULL(0x000000ff000000ff));
	apc_mask = (((apc_mask) & ULL(0x0000ffff00000000)) >> 16) |
		    ((apc_mask) & ULL(0x000000000000ffff));
	return (uint32_t)apc_mask;
}

static inline uint16_t get_apr_mask(uint32_t apc_mask)
{
	uint32_t apr_mask = apc_mask;

	apr_mask = ( (apr_mask) & 0x49249249) |
		   (((apr_mask) & 0x92492492) >> 1) |
		   (((apr_mask) & 0x24924924) >> 2);
	apr_mask = ( (apr_mask) & 0x41041041) |
		   (((apr_mask) & 0x08208208) >> 2);
	apr_mask = ( (apr_mask) & 0x03003003) |
		   (((apr_mask) & 0x400C00C0) >> 4);
	apr_mask = ( (apr_mask) & 0x0700000F) |
		   (((apr_mask) & 0x0000F000) >> 8);
	apr_mask = ( (apr_mask) & 0x000000FF) |
		   (((apr_mask) & 0x07000000) >> 16);
	return (uint16_t)apr_mask;
}

void falkor_power_off_core(uint8_t core_number);

void falkor_configure_entry_point(uint64_t entry_point);
void falkor_deassert_reset(uint8_t cpu, bool allow_wait);
bool falkor_deassert_reset_async(uint8_t cpu, bool allow_wait);
void falkor_configure_clock(uint8_t cpu, bool allow_wait);
bool falkor_configure_clock_async(uint8_t cpu, bool allow_wait);
bool falkor_is_cluster_clocked(uint16_t cluster);

uint64_t cmd_get_cpu_mask(char *cmd_str);
#endif /* _ASSEMBLY__ */

#endif /* __QDF2400_FALKOR_H_INCLUDE__ */
