#ifndef __QDF2400_DDR_H_INCLUDE__
#define __QDF2400_DDR_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>
#include <asm/plat-centriq/ddr.h>
#include <asm/mach/ddr/ddr_func_tbl.h>
#include <asm/mach/ddr/ddr_reg_logging.h>
#include <asm/mach/ddr/ddr_target.h>

#include <asm/mach/hal/HALmemoryHWIO.h>
#include <asm/mach/hal/HALddrphyHWIO.h>
#include <asm/mach/monaco/memory/mddr_ca_eyemeasure.h>
#include <asm/mach/monaco/memory/mddr_phy_init.h>
#include <asm/mach/monaco/memory/mddr_phy_loader.h>
#include <asm/mach/monaco/memory/mddr_phy_train.h>
#include <asm/mach/monaco/memory/mddr_si.h>
#include <asm/mach/monaco/memory/spd.h>
#include <asm/mach/monaco/memory/spd_simm.h>
#include <asm/mach/monaco/memory/spd_smbus.h>
#include <asm/mach/monaco/memory/spd_smbus_impl.h>
#include <asm/mach/monaco/common/boot_util.h>
#include <asm/mach/monaco/common/common_defs.h>
#include <asm/mach/monaco/common/DDRTargetLib.h>
#include <asm/mach/monaco/common/io.h>
#include <asm/mach/monaco/common/monaco_defs.h>
#include <asm/mach/monaco/common/monaco_extra_defs.h>
#include <asm/mach/monaco/common/monaco_init.h>
#include <asm/mach/monaco/common/monaco_logger.h>
#include <asm/mach/monaco/common/SharedVariables.h>
#include <asm/mach/monaco/common/XBLSharedVar.h>

#include <target/cpus.h>
#include <target/ddr/ddr_common.h>
#include <target/ddr/DDRCommonLib.h>
#include <target/ddr/spd_block.h>
#include <target/ddr/SPDConfig.h>

int ddr_init(void);
int do_ddr_enable(int argc, char *argv[]);
extern void boot_init_boot_variables(void);
extern int ddr_initialize_common(uint64_t cpu_pg, uint64_t l3_pg, uint64_t ddr_fw_base, bool cold_boot);
extern unsigned char ddrfw_bin[];
extern unsigned char ddrsi_bin[];
extern unsigned int ddrsi_bin_len;
extern unsigned char default_variables_bin[];
extern unsigned char shared_variables_bin[];

#endif
