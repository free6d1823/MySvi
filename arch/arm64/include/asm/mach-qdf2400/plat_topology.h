#ifndef PLAT_TOPOLGY_H
#define PLAT_TOPOLGY_H

bool plat_core_is_supported(unsigned int core);
bool plat_cluster_is_supported(unsigned int clu);
bool plat_rail_is_supported(unsigned int rail);
int plat_core_pos_by_mpidr(uint64_t mpidr);

#endif
