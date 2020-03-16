#ifndef __TARGET_DDR_H_INCLUDE__
#define __TARGET_DDR_H_INCLUDE__
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <target/cpus.h>
#include <target/ddr/ddr_common.h>
#include <target/ddr/DDRCommonLib.h>
#include <target/ddr/spd_block.h>
#include <target/ddr/SPDConfig.h>
#include <asm/mach/ddr.h>

#ifdef CONFIG_QCOM_DDRSS
int ddr_init(void);
#endif

int do_ddr_enable(int argc, char *argv[]);
extern void boot_init_boot_variables(void);
extern int ddr_initialize_common(uint64_t cpu_pg, uint64_t l3_pg, uint64_t ddr_fw_base, bool cold_boot);
extern unsigned char ddrfw_bin[];
extern unsigned char ddrsi_bin[];
extern unsigned int ddrsi_bin_len;
extern unsigned char default_variables_bin[];
extern unsigned char shared_variables_bin[];
#endif
