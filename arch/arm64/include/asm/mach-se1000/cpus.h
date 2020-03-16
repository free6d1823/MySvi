/*
 */
#ifndef __SE1000_CPUS_H_INCLUDE__
#define __SE1000_CPUS_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>

#define MAX_CPU_NUM		8
#define MAX_LLC_NUM		(MAX_CPU_NUM/2)

#define CPUS_SHIFT		0

#define CPUS_PER_CLUSTER	(1 << CPUS_SHIFT)
#define CPUS_PER_RAIL		6
#define CLUSTERS_PER_RAIL	3

#define MAX_CPU_RAILS	(MAX_CPU_NUM / CPUS_PER_RAIL)
#define MAX_CPU_CLUSTERS	(MAX_CPU_NUM / CPUS_PER_CLUSTER)

#ifndef __ASSEMBLY__
void set_cpu_mask(uint64_t cpu_mask);
uint64_t get_cpu_mask(void);
void set_llc_mask(uint64_t llc_mask);
uint64_t get_llc_mask(void);

void cpus_config_entry_point(uint64_t entry);
bool cpus_deassert_reset_async(int id);
#endif /* __ASSEMBLY__ */

#endif /* __SE1000_CPUS_H_INCLUDE__ */

