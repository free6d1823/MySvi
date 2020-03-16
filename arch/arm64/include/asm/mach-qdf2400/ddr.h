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

#endif
