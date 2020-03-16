/*
 */
#ifndef __QDF2400_CLOCK_H_INCLUDE__
#define __QDF2400_CLOCK_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>

struct agera_pll_regs {
	uint32_t config_ctl_hi;
	uint32_t config_ctl_lo;
	/* uint32_t user_ctl_u; */
	uint32_t user_ctl;
	uint32_t test_ctl_hi;
	uint32_t test_ctl_lo;
	uint16_t l;
	uint16_t alpha;
};

#define CPU_BOOT_FREQ_MHZ	600
#define CBF_BOOT_FREQ_MHZ	600
#define CPU_NORM_FREQ_MHZ	2600
#define CBF_NORM_FREQ_MHZ	2100

#define ARCH_CPU_BOOT_FREQ	CPU_BOOT_FREQ_MHZ
#define ARCH_LLC_BOOT_FREQ	CBF_BOOT_FREQ_MHZ
#define ARCH_CPU_NORM_FREQ	CPU_NORM_FREQ_MHZ
#define ARCH_LLC_NORM_FREQ	CBF_NORM_FREQ_MHZ

bool clock_config_cbf(uint32_t freq_mhz);
bool clock_config_cluster(uint8_t cluster, uint32_t freq_mhz);

bool fabia_config_plls(uint32_t *freq_mhz, bool allow_wait);

#include <asm/mach/fuse.h>

#endif /* __QDF2400_CLOCK_H_INCLUDE__ */
