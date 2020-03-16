#include <stdbool.h>
#include <bits/alltypes.h>
#include <asm/mach/cpus.h>
#include <asm/mach/platform_def.h>

/*partial good	LSB is core 0
 *	1:good	 0:bad				*/
 bool plat_core_is_supported(unsigned int core)
{
	static uint64_t partial_good;

	partial_good = get_cpu_mask();
	if ( core >= PLATFORM_CORE_COUNT)
		return false;

	if (((partial_good >> core ) & 0x1) == 0x1)
		return true;
	else
		return false;
}

bool plat_cluster_is_supported(unsigned int clu)
{
	unsigned int core;

	for (core = CLU_MIN_CPU_IDX(clu); core < CLU_MAX_CPU_IDX(clu); core++)
		if (plat_core_is_supported(core))
			return true;

	return false;
}

 bool plat_rail_is_supported(unsigned int rail)
{
	unsigned int core;

	for (core = RAIL_MIN_CPU_IDX(rail); core < RAIL_MAX_CPU_IDX(rail); core++)
		if (plat_core_is_supported(core))
			return true;

	return false;
}

int plat_core_pos_by_mpidr(uint64_t mpidr)
{
	uint64_t cpu_id = MPIDR_AFFLVL0_VAL(mpidr);
	uint64_t clu_id = MPIDR_AFFLVL1_VAL(mpidr);
	int core;

	// verify range of each afflvl in mpidr
	if (cpu_id >= PLATFORM_MAX_CPUS_PER_CLUSTER)
		return -1;

	if (clu_id >= PLATFORM_CLUSTER_COUNT)
		return -1;

	// calculate core index
	core = (clu_id * PLATFORM_MAX_CPUS_PER_CLUSTER) + cpu_id;

	// return index if core is not masked off
	if (!plat_core_is_supported(core))
		return -1;

	return core;
}
