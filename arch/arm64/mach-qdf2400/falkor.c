/*
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <asm/hal/HALhwio.h>
#include <asm/mach/hal/HALclkHWIO.h>
#include <asm/mach/hal/HALbootHWIO.h>
#include <target/cpus.h>
#include <target/delay.h>
#include <target/clock.h>
#include <target/arch.h>
#include <target/timer.h>
#include <target/barrier.h>

#define FALKOR_INIT_APR				0
#define FALKOR_APR_BEGIN_COLD_BOOT		(FALKOR_INIT_APR+0)
#define FALKOR_APR_ASSERT_POR_CLAMP		(FALKOR_INIT_APR+1)
#define FALKOR_APR_DEASSERT_CLAMP		(FALKOR_INIT_APR+2)
#define FALKOR_APR_DEASSERT_POR			(FALKOR_INIT_APR+3)
#define FALKOR_APR_END_COLD_BOOT		(FALKOR_INIT_APR+4)
#define FALKOR_FINI_APR				FALKOR_APR_END_COLD_BOOT

#define FALKOR_INIT_APC				FALKOR_FINI_APR
#define FALKOR_INIT_QLL				FALKOR_INIT_APC
#define FALKOR_APC_BEGIN_QLL_INIT		(FALKOR_INIT_QLL+0)
#define FALKOR_APC_INIT_QLL_REGISTER		(FALKOR_INIT_QLL+1)
#define FALKOR_APC_CLEAR_QLL_ERROR		(FALKOR_INIT_QLL+2)
#define FALKOR_APC_END_QLL_INIT			(FALKOR_INIT_QLL+3)
#define FALKOR_FINI_QLL				FALKOR_APC_END_QLL_INIT

#define FALKOR_INIT_FREQ			FALKOR_FINI_QLL
#define FALKOR_FINI_FREQ			(FALKOR_INIT_FREQ+1)

#define FALKOR_INIT_L2				FALKOR_FINI_FREQ
#define FALKOR_APC_BEGIN_L2_COLD_BOOT		(FALKOR_INIT_L2+0)
#define FALKOR_APC_ASSERT_L2_SPM_WAKEUP		(FALKOR_INIT_L2+1)
#define FALKOR_APC_ASSERT_L2_POR_CLAMP_GFMUX	(FALKOR_INIT_L2+2)
#define FALKOR_APC_DEASSERT_L2_GFMUX		(FALKOR_INIT_L2+3)
#define FALKOR_APC_DEASSERT_L2_CLAMP		(FALKOR_INIT_L2+4)
#define FALKOR_APC_DEASSERT_L2_POR		(FALKOR_INIT_L2+5)
#define FALKOR_APC_DEASSERT_L2_SPM_WAKEUP	(FALKOR_INIT_L2+6)
#define FALKOR_APC_END_L2_COLD_BOOT		(FALKOR_INIT_L2+7)
#define FALKOR_FINI_L2				FALKOR_APC_END_L2_COLD_BOOT

#define FALKOR_INIT_CPU				FALKOR_FINI_L2
#define FALKOR_APC_BEGIN_CPU_COLD_BOOT		(FALKOR_INIT_CPU+0)
#define FALKOR_APC_ASSERT_CPU_SPM_WAKEUP	(FALKOR_INIT_CPU+1)
#define FALKOR_APC_ASSERT_CPU_POR_CLAMP		(FALKOR_INIT_CPU+2)
#define FALKOR_APC_DEASSERT_CPU_CLAMP		(FALKOR_INIT_CPU+3)
#define FALKOR_APC_DEASSERT_CPU_POR		(FALKOR_INIT_CPU+4)
#define FALKOR_APC_ASSERT_CPU_POWERED_ON	(FALKOR_INIT_CPU+5)
#define FALKOR_APC_DEASSERT_CPU_SPM_WAKEUP	(FALKOR_INIT_CPU+6)
#define FALKOR_APC_END_CPU_COLD_BOOT		(FALKOR_INIT_CPU+7)
#define FALKOR_FINI_CPU				FALKOR_APC_END_CPU_COLD_BOOT
#define FALKOR_FINI_APC				FALKOR_FINI_CPU

static uint64_t falkor_init_mask = 0;
static uint8_t falkor_async_state[MAX_CPU_NUM];
static ktime_t falkor_async_timeout;

static inline uint8_t falkor_get_rail_state(uint8_t rail)
{
	return falkor_async_state[rail * CPUS_PER_RAIL];
}

static inline void falkor_set_rail_state(uint8_t rail, uint8_t state)
{
	uint8_t cpu;

	for (cpu = 0; cpu < CPUS_PER_RAIL; cpu++)
		falkor_async_state[rail * CPUS_PER_RAIL + cpu] = state;
}

static inline uint8_t falkor_get_cluster_state(uint8_t cluster)
{
	return falkor_async_state[cluster * CPUS_PER_CLUSTER];
}

static inline void falkor_set_cluster_state(uint8_t cluster, uint8_t state)
{
	uint8_t cpu;

	for (cpu = 0; cpu < CPUS_PER_CLUSTER; cpu++)
		falkor_async_state[cluster * CPUS_PER_CLUSTER + cpu] = state;
}

static inline uint8_t falkor_get_cpu_state(uint8_t cpu)
{
	return falkor_async_state[cpu];
}

static inline void falkor_set_cpu_state(uint8_t cpu, uint8_t state)
{
	falkor_async_state[cpu] = state;
}

static inline void falkor_set_async_timeout(unsigned long us)
{
#ifdef CONFIG_TESTOS_EMU
	us /= 1000;
#endif
	falkor_async_timeout = time_get_current_time() + us;
}

static inline bool falkor_is_async_timeout(void)
{
	return !!time_after(time_get_current_time(), falkor_async_timeout);
}

#ifdef CONFIG_QDF2400_PM_AVM
static inline bool avm_is_enabled(void)
{
	return false;
}
#else
static inline bool avm_is_enabled(void)
{
	return true;
}
#endif

const unsigned long l2_power_control_registers[MAX_CPU_CLUSTERS] = {
	HWIO_APCS_APC00_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC01_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC02_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC03_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC04_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC05_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC06_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC07_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC08_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC09_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC10_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC11_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC12_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC13_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC14_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC15_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC16_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC17_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC18_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC19_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC20_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC21_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC22_L2_PWR_CTL_ADDR,
	HWIO_APCS_APC23_L2_PWR_CTL_ADDR,
};

const unsigned long core_power_control_registers[MAX_CPU_NUM] = {
	HWIO_APCS_APC00_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC00_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC01_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC01_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC02_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC02_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC03_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC03_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC04_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC04_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC05_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC05_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC06_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC06_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC07_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC07_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC08_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC08_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC09_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC09_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC10_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC10_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC11_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC11_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC12_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC12_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC13_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC13_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC14_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC14_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC15_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC15_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC16_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC16_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC17_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC17_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC18_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC18_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC19_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC19_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC20_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC20_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC21_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC21_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC22_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC22_CPU1_PWR_CTL_ADDR,
	HWIO_APCS_APC23_CPU0_PWR_CTL_ADDR,
	HWIO_APCS_APC23_CPU1_PWR_CTL_ADDR,
};

#ifdef CONFIG_PM_SLEEP
#define FALKOR_L2_SPM_EVENT_DELAY_US			10000
#define FALKOR_CPU_SPM_EVENT_DELAY_US			10000

#define FALKOR_L2_SW_SPM_EVENT_SPM_WAKEUP_BITMASK	0x2
#define FALKOR_CPU_SW_SPM_EVENT_SPM_WAKEUP_BITMASK	0x2

const unsigned long l2_spm_event_registers[MAX_CPU_CLUSTERS] = {
	HWIO_APCS_APC00_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC01_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC02_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC03_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC04_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC05_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC06_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC07_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC08_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC09_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC10_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC11_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC12_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC13_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC14_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC15_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC16_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC17_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC18_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC19_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC20_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC21_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC22_L2_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC23_L2_SW_SPM_EVENT_ADDR,
};

/* Two cores per APC, two APC's per SPM. */
const unsigned long core_spm_event_registers[MAX_CPU_NUM] = {
	HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC00_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC01_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC01_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC02_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC02_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC03_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC03_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC04_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC04_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC05_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC05_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC06_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC06_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC07_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC07_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC08_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC08_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC09_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC09_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC10_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC10_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC11_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC11_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC12_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC12_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC13_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC13_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC14_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC14_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC15_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC15_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC16_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC16_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC17_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC17_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC18_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC18_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC19_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC19_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC20_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC20_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC21_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC21_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC22_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC22_CPU1_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC23_CPU0_SW_SPM_EVENT_ADDR,
	HWIO_APCS_APC23_CPU1_SW_SPM_EVENT_ADDR,
};

static inline void falkor_l2_assert_spm_wakeup(uint8_t cluster,
					       bool allow_wait)
{
	/* Assert APR SPM wakeup. */
	out_dword_masked_ns(l2_spm_event_registers[cluster],
			    FALKOR_L2_SW_SPM_EVENT_SPM_WAKEUP_BITMASK,
			    FALKOR_L2_SW_SPM_EVENT_SPM_WAKEUP_BITMASK,
			    in_dword(l2_spm_event_registers[cluster]));
	if (!allow_wait)
		falkor_set_async_timeout(FALKOR_L2_SPM_EVENT_DELAY_US);
}

static inline bool falkor_l2_is_spm_wakeup_asserted(uint8_t cluster,
						    bool allow_wait)
{
	if (allow_wait) {
		return ((HWIO_APCS_APC00_L2_PWR_CTL_CBF_ACTIVE_BMSK |
			 HWIO_APCS_APC00_L2_PWR_CTL_APR_ACTIVE_BMSK) ==
			in_dword_masked(l2_power_control_registers[cluster],
					HWIO_APCS_APC00_L2_PWR_CTL_CBF_ACTIVE_BMSK |
					HWIO_APCS_APC00_L2_PWR_CTL_APR_ACTIVE_BMSK));
	} else {
		return falkor_is_async_timeout();
	}
}

static inline void falkor_l2_deassert_spm_wakeup(uint8_t cluster,
						 bool allow_wait)
{
	/* De-assert Assert APR SPM wakeup. */
	out_dword_masked_ns(l2_spm_event_registers[cluster],
			    FALKOR_L2_SW_SPM_EVENT_SPM_WAKEUP_BITMASK,
			    0x0,
			    in_dword(l2_spm_event_registers[cluster]));
	falkor_set_async_timeout(FALKOR_L2_SPM_EVENT_DELAY_US);
}

static inline bool falkor_l2_is_spm_wakeup_deasserted(uint8_t cluster,
						      bool allow_wait)
{
	return falkor_is_async_timeout();
}

static inline void falkor_cpu_assert_spm_wakeup(uint8_t cpu,
						bool allow_wait)
{
	/* Assert APR SPM wakeup. */
	out_dword_masked_ns(core_spm_event_registers[cpu],
			    FALKOR_CPU_SW_SPM_EVENT_SPM_WAKEUP_BITMASK,
			    FALKOR_CPU_SW_SPM_EVENT_SPM_WAKEUP_BITMASK,
			    in_dword(core_spm_event_registers[cpu]));
	if (!allow_wait)
		falkor_set_async_timeout(FALKOR_CPU_SPM_EVENT_DELAY_US);
}

static inline bool falkor_cpu_is_spm_wakeup_asserted(uint8_t cpu,
						     bool allow_wait)
{
	if (allow_wait) {
		return (HWIO_APCS_APC00_CPU0_PWR_CTL_L2_ACTIVE_BMSK ==
			in_dword_masked(core_power_control_registers[cpu],
					HWIO_APCS_APC00_CPU0_PWR_CTL_L2_ACTIVE_BMSK));
	} else {
		return falkor_is_async_timeout();
	}
}

static inline void falkor_cpu_deassert_spm_wakeup(uint8_t cpu,
						  bool allow_wait)
{
	/* Assert APR SPM wakeup. */
	out_dword_masked_ns(core_spm_event_registers[cpu],
			    FALKOR_CPU_SW_SPM_EVENT_SPM_WAKEUP_BITMASK,
			    0x0,
			    in_dword(core_spm_event_registers[cpu]));
	falkor_set_async_timeout(FALKOR_CPU_SPM_EVENT_DELAY_US);
}

static inline bool falkor_cpu_is_spm_wakeup_deasserted(uint8_t cpu,
						       bool allow_wait)
{
	return falkor_is_async_timeout();
}
#else
static inline void falkor_l2_assert_spm_wakeup(uint8_t cluster,
					       bool allow_wait)
{
}

static inline bool falkor_l2_is_spm_wakeup_asserted(uint8_t cluster,
						    bool allow_wait)
{
	return true;
}

static inline void falkor_l2_deassert_spm_wakeup(uint8_t cluster,
						 bool allow_wait)
{
}

static inline bool falkor_l2_is_spm_wakeup_deasserted(uint8_t cluster,
						      bool allow_wait)
{
	return true;
}

static inline void falkor_cpu_assert_spm_wakeup(uint8_t cpu,
						bool allow_wait)
{
}

static inline bool falkor_cpu_is_spm_wakeup_asserted(uint8_t cpu,
						     bool allow_wait)
{
	return true;
}

static inline void falkor_cpu_deassert_spm_wakeup(uint8_t cpu,
						  bool allow_wait)
{
}

static inline bool falkor_cpu_is_spm_wakeup_deasserted(uint8_t cpu,
						       bool allow_wait)
{
	return true;
}
#endif

/*======================================================================
 *  Function :  falkor_apc_l2_cold_boot_async
 * =====================================================================
 *
 * Refer to <<QDF2400 Programming Manual>>
 * 39 Falkor Processor Subsystem
 * 39.4.1.1 L2 cold boot sequences
 * Table 39-10 L2 cold boot sequence for APCy_L2
 */
/* No delay seems to be required for APCS_APCy_L2_PWR_CTL  */
#define FALKOR_APCS_APC_L2_PWR_CTL_DELAY_US		0 /* 10000 */

bool falkor_apc_l2_cold_boot_async(uint8_t cluster, bool allow_wait)
{
	switch (falkor_get_cluster_state(cluster)) {
	case FALKOR_APC_BEGIN_L2_COLD_BOOT:
		wmb();
		falkor_l2_assert_spm_wakeup(cluster, allow_wait);
		falkor_set_cluster_state(cluster,
					 FALKOR_APC_ASSERT_L2_SPM_WAKEUP);
		break;
	case FALKOR_APC_ASSERT_L2_SPM_WAKEUP:
		if (!falkor_l2_is_spm_wakeup_asserted(cluster, allow_wait))
			break;
		/* Assert POR and GFMX Reset, Clamp, Close L2 APM HS and L2
		 * logic BHS
		 */
		wmb();
		out_dword(l2_power_control_registers[cluster],
			  (HWIO_APCS_APC00_L2_PWR_CTL_GF_MUX_RST_BMSK |
			   HWIO_APCS_APC00_L2_PWR_CTL_CLAMP_APMPD_BMSK |
			   HWIO_APCS_APC00_L2_PWR_CTL_POR_RST_BMSK |
			   HWIO_APCS_APC00_L2_PWR_CTL_CLAMP_L2PD_BMSK));
		if (!allow_wait)
			falkor_set_async_timeout(FALKOR_APCS_APC_L2_PWR_CTL_DELAY_US);
		falkor_set_cluster_state(cluster,
					 FALKOR_APC_ASSERT_L2_POR_CLAMP_GFMUX);
		break;
	case FALKOR_APC_ASSERT_L2_POR_CLAMP_GFMUX:
		if (allow_wait) {
			if (HWIO_APCS_APC00_L2_PWR_CTL_GF_MUX_RST_STATUS_BMSK !=
			    in_dword_masked(l2_power_control_registers[cluster],
					    HWIO_APCS_APC00_L2_PWR_CTL_GF_MUX_RST_STATUS_BMSK))
				break;
		} else if (!falkor_is_async_timeout())
			break;
		/* De-assert GFMUX_Reset */
		wmb();
		out_dword(l2_power_control_registers[cluster],
			  (HWIO_APCS_APC00_L2_PWR_CTL_CLAMP_APMPD_BMSK |
			   HWIO_APCS_APC00_L2_PWR_CTL_POR_RST_BMSK |
			   HWIO_APCS_APC00_L2_PWR_CTL_CLAMP_L2PD_BMSK));
		if (!allow_wait)
			falkor_set_async_timeout(FALKOR_APCS_APC_L2_PWR_CTL_DELAY_US);
		falkor_set_cluster_state(cluster, FALKOR_APC_DEASSERT_L2_GFMUX);
		break;
	case FALKOR_APC_DEASSERT_L2_GFMUX:
		if (allow_wait) {
			if (HWIO_APCS_APC00_L2_PWR_CTL_HY_RST_COMP_REQ_BMSK !=
			    in_dword_masked(l2_power_control_registers[cluster],
					    HWIO_APCS_APC00_L2_PWR_CTL_HY_RST_COMP_REQ_BMSK))
				break;
		} else if (!falkor_is_async_timeout())
			break;
		/* De-assert Clamp; Assert RST_CMPLT_ACK */
		wmb();
		out_dword(l2_power_control_registers[cluster],
			  (HWIO_APCS_APC00_L2_PWR_CTL_POR_RST_BMSK |
			   HWIO_APCS_APC00_L2_PWR_CTL_RST_COMP_ACK_BMSK));
		if (!allow_wait)
			falkor_set_async_timeout(FALKOR_APCS_APC_L2_PWR_CTL_DELAY_US);
		falkor_set_cluster_state(cluster, FALKOR_APC_DEASSERT_L2_CLAMP);
		break;
	case FALKOR_APC_DEASSERT_L2_CLAMP:
		if (allow_wait) {
			if (in_dword_masked(l2_power_control_registers[cluster],
					    HWIO_APCS_APC00_L2_PWR_CTL_HY_RST_COMP_REQ_BMSK))
				break;
		} else if (!falkor_is_async_timeout())
			break;
		/* De-assert POR Reset */
		wmb();
		out_dword(l2_power_control_registers[cluster],
			  HWIO_APCS_APC00_L2_PWR_CTL_L2_PWRD_UP_BMSK);
		falkor_set_async_timeout(FALKOR_APCS_APC_L2_PWR_CTL_DELAY_US);
		falkor_set_cluster_state(cluster, FALKOR_APC_DEASSERT_L2_POR);
		break;
	case FALKOR_APC_DEASSERT_L2_POR:
		if (!falkor_is_async_timeout())
			break;
		wmb();
		falkor_l2_deassert_spm_wakeup(cluster, allow_wait);
		falkor_set_cluster_state(cluster,
					 FALKOR_APC_DEASSERT_L2_SPM_WAKEUP);
		break;
	case FALKOR_APC_DEASSERT_L2_SPM_WAKEUP:
		if (!falkor_l2_is_spm_wakeup_deasserted(cluster, allow_wait))
			break;
		wmb();
		falkor_set_cluster_state(cluster, FALKOR_APC_END_L2_COLD_BOOT);
	default:
		return true;
	}
	return false;
}

/*======================================================================
 *  Function :  falkor_apc_cpu_cold_boot_async
 * =====================================================================
 *
 * Refer to <<QDF2400 Programming Manual>>
 * 39 Falkor Processor Subsystem
 * 39.4.1.1 L2 cold boot sequences
 * Table 39-10 L2 cold boot sequence for APCy_L2
 */
/* No delay seems to be required for APCS_APCy_L2_PWR_CTL  */
#define FALKOR_APCS_APC_CPU_PWR_CTL_DELAY_US		0 /* 10000 */

bool falkor_apc_cpu_cold_boot_async(uint8_t cpu, bool allow_wait)
{
	switch (falkor_get_cpu_state(cpu)) {
	case FALKOR_APC_BEGIN_CPU_COLD_BOOT:
		wmb();
		falkor_cpu_assert_spm_wakeup(cpu, allow_wait);
		falkor_set_cpu_state(cpu, FALKOR_APC_ASSERT_CPU_SPM_WAKEUP);
		break;
	case FALKOR_APC_ASSERT_CPU_SPM_WAKEUP:
		if (!falkor_cpu_is_spm_wakeup_asserted(cpu, allow_wait))
			break;
		/* Assert POR Reset, Clamp, Close CPU APM HS and CPU logic
		 * BHS
		 */
		wmb();
		out_dword(core_power_control_registers[cpu],
			  (HWIO_APCS_APC00_CPU0_PWR_CTL_CLAMP_APMPD_BMSK |
			   HWIO_APCS_APC00_CPU0_PWR_CTL_POR_RST_BMSK |
			   HWIO_APCS_APC00_CPU0_PWR_CTL_CLAMP_CPUPD_BMSK));
		if (!allow_wait)
			falkor_set_async_timeout(FALKOR_APCS_APC_CPU_PWR_CTL_DELAY_US);
		falkor_set_cpu_state(cpu, FALKOR_APC_ASSERT_CPU_POR_CLAMP);
		break;
	case FALKOR_APC_ASSERT_CPU_POR_CLAMP:
		if (allow_wait) {
			if (HWIO_APCS_APC00_CPU0_PWR_CTL_HY_RST_COMP_REQ_BMSK !=
			    in_dword_masked(core_power_control_registers[cpu],
					    HWIO_APCS_APC00_CPU0_PWR_CTL_HY_RST_COMP_REQ_BMSK))
				break;
		} else if (!falkor_is_async_timeout())
			break;
		/* De-assert Clamp; Assert RST_CMPLT_ACK */
		wmb();
		out_dword(core_power_control_registers[cpu],
			  (HWIO_APCS_APC00_CPU0_PWR_CTL_RST_COMP_ACK_BMSK |
			   HWIO_APCS_APC00_CPU0_PWR_CTL_POR_RST_BMSK));
		if (!allow_wait)
			falkor_set_async_timeout(FALKOR_APCS_APC_CPU_PWR_CTL_DELAY_US);
		falkor_set_cpu_state(cpu, FALKOR_APC_DEASSERT_CPU_CLAMP);
		break;
	case FALKOR_APC_DEASSERT_CPU_CLAMP:
		if (allow_wait) {
			if (in_dword_masked(core_power_control_registers[cpu],
					    HWIO_APCS_APC00_CPU0_PWR_CTL_HY_RST_COMP_REQ_BMSK))
				break;
		} else if (!falkor_is_async_timeout())
			break;
		/* De-assert POR reset */
		wmb();
		out_dword(core_power_control_registers[cpu], 0x0);
		falkor_set_async_timeout(FALKOR_APCS_APC_CPU_PWR_CTL_DELAY_US);
		falkor_set_cpu_state(cpu, FALKOR_APC_DEASSERT_CPU_POR);
		break;
	case FALKOR_APC_DEASSERT_CPU_POR:
		if (!falkor_is_async_timeout())
			break;
		/* Assert PWRDUP */
		wmb();
		out_dword(core_power_control_registers[cpu],
			  HWIO_APCS_APC00_CPU0_PWR_CTL_CORE_PWRD_UP_BMSK);
		falkor_set_async_timeout(FALKOR_APCS_APC_CPU_PWR_CTL_DELAY_US);
		falkor_set_cpu_state(cpu, FALKOR_APC_ASSERT_CPU_POWERED_ON);
		break;
	case FALKOR_APC_ASSERT_CPU_POWERED_ON:
		if (!falkor_is_async_timeout())
			break;
		wmb();
		falkor_cpu_deassert_spm_wakeup(cpu, allow_wait);
		falkor_set_cpu_state(cpu, FALKOR_APC_DEASSERT_CPU_SPM_WAKEUP);
		break;
	case FALKOR_APC_DEASSERT_CPU_SPM_WAKEUP:
		if (!falkor_cpu_is_spm_wakeup_deasserted(cpu, allow_wait))
			break;
		wmb();
		falkor_set_cpu_state(cpu, FALKOR_APC_END_CPU_COLD_BOOT);
	default:
		return true;
	}
	return false;
}

/*======================================================================
 *  Function :  falkor_apr_cold_boot_async
 * =====================================================================
 *
 * Refer to <<QDF2400 Programming Manual>>
 * 39 Falkor Processor Subsystem
 * 39.4.1 Cold boot sequences
 * Table 39-8 APR cold boot sequence
 */
#if 0
/* PMIC/CVR sequences are different. Uses CVR sequence to meet test
 * requirements.
 */
#define FALKOR_APR_SAW4_CTRL_APC_ENABLE		0xAE

const unsigned long apr_saw4_control_registers[MAX_CPU_RAILS] = {
	HWIO_APCS_APR0_SAW4_VCTL_ADDR,
	HWIO_APCS_APR1_SAW4_VCTL_ADDR,
	HWIO_APCS_APR2_SAW4_VCTL_ADDR,
	HWIO_APCS_APR3_SAW4_VCTL_ADDR,
	HWIO_APCS_APR4_SAW4_VCTL_ADDR,
	HWIO_APCS_APR5_SAW4_VCTL_ADDR,
	HWIO_APCS_APR6_SAW4_VCTL_ADDR,
	HWIO_APCS_APR7_SAW4_VCTL_ADDR,
};

const unsigned long apr_saw4_status_registers[MAX_CPU_RAILS] = {
	HWIO_APCS_APR0_SAW4_AVS_STS_ADDR,
	HWIO_APCS_APR1_SAW4_AVS_STS_ADDR,
	HWIO_APCS_APR2_SAW4_AVS_STS_ADDR,
	HWIO_APCS_APR3_SAW4_AVS_STS_ADDR,
	HWIO_APCS_APR4_SAW4_AVS_STS_ADDR,
	HWIO_APCS_APR5_SAW4_AVS_STS_ADDR,
	HWIO_APCS_APR6_SAW4_AVS_STS_ADDR,
	HWIO_APCS_APR7_SAW4_AVS_STS_ADDR,
};
#endif

const unsigned long apr_power_control_registers[MAX_CPU_RAILS] = {
	HWIO_APCS_APR0_PWR_CTL_ADDR,
	HWIO_APCS_APR1_PWR_CTL_ADDR,
	HWIO_APCS_APR2_PWR_CTL_ADDR,
	HWIO_APCS_APR3_PWR_CTL_ADDR,
	HWIO_APCS_APR4_PWR_CTL_ADDR,
	HWIO_APCS_APR5_PWR_CTL_ADDR,
	HWIO_APCS_APR6_PWR_CTL_ADDR,
	HWIO_APCS_APR7_PWR_CTL_ADDR,
};

/* No delay seems to be required for APCS_APRx_PWR_CTL  */
#define FALKOR_APCS_APR_PWR_CTL_DELAY_US		0 /* 10000 */

bool falkor_apr_cold_boot_async(uint8_t rail)
{
	switch (falkor_get_rail_state(rail)) {
	case FALKOR_APR_BEGIN_COLD_BOOT:
		/* Assert APCpd POR Reset, Clamp */
		wmb();
		out_dword(apr_power_control_registers[rail],
			  HWIO_APCS_APR0_PWR_CTL_POR_RST_BMSK |
			  HWIO_APCS_APR0_PWR_CTL_CLAMP_APCPD_BMSK);
		falkor_set_async_timeout(FALKOR_APCS_APR_PWR_CTL_DELAY_US);
		falkor_set_rail_state(rail, FALKOR_APR_ASSERT_POR_CLAMP);
		break;
	case FALKOR_APR_ASSERT_POR_CLAMP:
		if (!falkor_is_async_timeout())
			break;
		/* De-assert APCpd Clamp */
		wmb();
		out_dword(apr_power_control_registers[rail],
			  HWIO_APCS_APR0_PWR_CTL_POR_RST_BMSK);
		falkor_set_async_timeout(FALKOR_APCS_APR_PWR_CTL_DELAY_US);
		falkor_set_rail_state(rail, FALKOR_APR_DEASSERT_CLAMP);
		break;
	case FALKOR_APR_DEASSERT_CLAMP:
		if (!falkor_is_async_timeout())
			break;
		/* De-assert APCpd POR reset and assert APCCPwrCtlPmicOn */
		wmb();
		out_dword(apr_power_control_registers[rail],
			  HWIO_APCS_APR0_PWR_CTL_PMIC_APC_ON_BMSK);
		falkor_set_async_timeout(FALKOR_APCS_APR_PWR_CTL_DELAY_US);
		falkor_set_rail_state(rail, FALKOR_APR_DEASSERT_POR);
		break;
	case FALKOR_APR_DEASSERT_POR:
		if (!falkor_is_async_timeout())
			break;
		wmb();
		falkor_set_rail_state(rail, FALKOR_APR_END_COLD_BOOT);
	default:
		return true;
	}
	return false;
}

/*======================================================================
 *  Function :  falkor_apc_init_qll_register_async
 * =====================================================================
 *
 * Refer to <<QDF2400 Programming Manual>>
 * 39 Falkor Processor Subsystem
 * 39.4.1.1 L2 cold boot sequences
 * Table 39-9 Falkor duplex QLL register initialization sequence
 */
/* No delay seems to be required for APCS_APCx_CLKCR/APCS_APC_QLL_ESR  */
#define FALKOR_APCS_APC_QLL_DELAY_US		0 /* 10000 */

#define HWIO_APCS_APC_CLKCR_RESET_BMSK			\
	(HWIO_APCS_APC00_CLKCR_QSBTXWUDLY_2_0_BMSK |	\
	 HWIO_APCS_APC00_CLKCR_QSBTXSLPDLY_1_0_BMSK |	\
	 HWIO_APCS_APC00_CLKCR_ACLKSELEN_BMSK |		\
	 HWIO_APCS_APC00_CLKCR_EL2CLKAG_BMSK |		\
	 HWIO_APCS_APC00_CLKCR_ECPU1CLKAG_BMSK |	\
	 HWIO_APCS_APC00_CLKCR_ECPU0CLKAG_BMSK |	\
	 HWIO_APCS_APC00_CLKCR_EQSBACG_BMSK |		\
	 HWIO_APCS_APC00_CLKCR_EPRICLKAG_BMSK)

#define HWIO_APCS_APC_QLL_ESR_RESET_BMSK		\
	(HWIO_APCS_APC00_QLL_ESR_ME_BMSK |		\
	 HWIO_APCS_APC00_QLL_ESR_RES0_0_BMSK |		\
	 HWIO_APCS_APC00_QLL_ESR_WDRE_BMSK |		\
	 HWIO_APCS_APC00_QLL_ESR_WIBS_BMSK |		\
	 HWIO_APCS_APC00_QLL_ESR_WRO_BMSK |		\
	 HWIO_APCS_APC00_QLL_ESR_NR_BMSK)

const unsigned long qll_clkcr_registers[MAX_CPU_CLUSTERS] = {
	HWIO_APCS_APC00_CLKCR_ADDR,
	HWIO_APCS_APC01_CLKCR_ADDR,
	HWIO_APCS_APC02_CLKCR_ADDR,
	HWIO_APCS_APC03_CLKCR_ADDR,
	HWIO_APCS_APC04_CLKCR_ADDR,
	HWIO_APCS_APC05_CLKCR_ADDR,
	HWIO_APCS_APC06_CLKCR_ADDR,
	HWIO_APCS_APC07_CLKCR_ADDR,
	HWIO_APCS_APC08_CLKCR_ADDR,
	HWIO_APCS_APC09_CLKCR_ADDR,
	HWIO_APCS_APC10_CLKCR_ADDR,
	HWIO_APCS_APC11_CLKCR_ADDR,
	HWIO_APCS_APC12_CLKCR_ADDR,
	HWIO_APCS_APC13_CLKCR_ADDR,
	HWIO_APCS_APC14_CLKCR_ADDR,
	HWIO_APCS_APC15_CLKCR_ADDR,
	HWIO_APCS_APC16_CLKCR_ADDR,
	HWIO_APCS_APC17_CLKCR_ADDR,
	HWIO_APCS_APC18_CLKCR_ADDR,
	HWIO_APCS_APC19_CLKCR_ADDR,
	HWIO_APCS_APC20_CLKCR_ADDR,
	HWIO_APCS_APC21_CLKCR_ADDR,
	HWIO_APCS_APC22_CLKCR_ADDR,
	HWIO_APCS_APC23_CLKCR_ADDR,
};

const unsigned long qll_esr_registers[MAX_CPU_CLUSTERS] = {
	HWIO_APCS_APC00_QLL_ESR_ADDR,
	HWIO_APCS_APC01_QLL_ESR_ADDR,
	HWIO_APCS_APC02_QLL_ESR_ADDR,
	HWIO_APCS_APC03_QLL_ESR_ADDR,
	HWIO_APCS_APC04_QLL_ESR_ADDR,
	HWIO_APCS_APC05_QLL_ESR_ADDR,
	HWIO_APCS_APC06_QLL_ESR_ADDR,
	HWIO_APCS_APC07_QLL_ESR_ADDR,
	HWIO_APCS_APC08_QLL_ESR_ADDR,
	HWIO_APCS_APC09_QLL_ESR_ADDR,
	HWIO_APCS_APC10_QLL_ESR_ADDR,
	HWIO_APCS_APC11_QLL_ESR_ADDR,
	HWIO_APCS_APC12_QLL_ESR_ADDR,
	HWIO_APCS_APC13_QLL_ESR_ADDR,
	HWIO_APCS_APC14_QLL_ESR_ADDR,
	HWIO_APCS_APC15_QLL_ESR_ADDR,
	HWIO_APCS_APC16_QLL_ESR_ADDR,
	HWIO_APCS_APC17_QLL_ESR_ADDR,
	HWIO_APCS_APC18_QLL_ESR_ADDR,
	HWIO_APCS_APC19_QLL_ESR_ADDR,
	HWIO_APCS_APC20_QLL_ESR_ADDR,
	HWIO_APCS_APC21_QLL_ESR_ADDR,
	HWIO_APCS_APC22_QLL_ESR_ADDR,
	HWIO_APCS_APC23_QLL_ESR_ADDR,
};

bool falkor_apc_init_qll_register_async(uint8_t cluster)
{
	uint32_t data;

	switch (falkor_get_cluster_state(cluster)) {
	case FALKOR_APC_BEGIN_QLL_INIT:
		data = HWIO_APCS_APC_CLKCR_RESET_BMSK;
		/* Disable primary GFMUX dynamic clock gating if AVM is
		 * enabled.
		 */
		if (avm_is_enabled())
			data &= ~HWIO_APCS_APC00_CLKCR_EPRICLKAG_BMSK;
		/* Enable GFMUX clock gating, Enable autoclock select. */
		wmb();
		out_dword(qll_clkcr_registers[cluster], data);
		falkor_set_async_timeout(FALKOR_APCS_APC_QLL_DELAY_US);
		falkor_set_cluster_state(cluster, FALKOR_APC_INIT_QLL_REGISTER);
		break;
	case FALKOR_APC_INIT_QLL_REGISTER:
		if (!falkor_is_async_timeout())
			break;
		wmb();
		out_dword(qll_esr_registers[cluster],
			  HWIO_APCS_APC_QLL_ESR_RESET_BMSK);
		falkor_set_async_timeout(FALKOR_APCS_APC_QLL_DELAY_US);
		falkor_set_cluster_state(cluster, FALKOR_APC_CLEAR_QLL_ERROR);
		break;
	case FALKOR_APC_CLEAR_QLL_ERROR:
		if (!falkor_is_async_timeout())
			break;
		wmb();
		falkor_set_cluster_state(cluster, FALKOR_APC_END_QLL_INIT);
	default:
		return true;
	}
	return false;
}

/***************************************************************
 * The flow code is not Qualcomm's
 **************************************************************/
void falkor_configure_entry_point(uint64_t entry_point)
{
	uint64_t entry_point_mask;

	/* ACPS register only supports a 44 bit entry point with lower 5
	 * bits 0.
	 */
	entry_point_mask = ((uint64_t)
		(HWIO_APCS_BOOT_CFG_START_ADDR_HI_ADDR_BMSK) << 32);
	entry_point_mask |= HWIO_APCS_BOOT_CFG_START_ADDR_LO_ADDR_BMSK;
	entry_point_mask = ~entry_point_mask;

	if ((entry_point & entry_point_mask) != 0)
		printf("Invalid APCS boot start address - 0x%llu\n",
		       entry_point);

	/* Load the register with final value. */
	HWIO_APCS_BOOT_CFG_START_ADDR_LO_OUT((uint32_t)entry_point);
	HWIO_APCS_BOOT_CFG_START_ADDR_HI_OUT((uint32_t)(entry_point >> 32));
}

void falkor_power_off_core(uint8_t core_number)
{
	out_dword(core_power_control_registers[core_number],
		  (HWIO_APCS_APC00_CPU0_PWR_CTL_CLAMP_APMPD_BMSK |
		   HWIO_APCS_APC00_CPU0_PWR_CTL_CLAMP_CPUPD_BMSK |
		   HWIO_APCS_APC00_CPU0_PWR_CTL_MA_DSBL_BMSK |
		   HWIO_APCS_APC00_CPU0_PWR_CTL_HS_DSBL_BMSK));
	udelay(FALKOR_APCS_APC_CPU_PWR_CTL_DELAY_US);
}

bool falkor_configure_clock_async(uint8_t cpu, bool allow_wait)
{
	uint8_t rail = CPU_TO_RAIL(cpu);
	uint8_t cluster = CPU_TO_CLUSTER(cpu);
	uint8_t state = 0;

	if (falkor_init_mask & CPU_TO_MASK(cpu))
		return true;

	if (!(falkor_init_mask &
	      RAIL_TO_CPU_MASK(rail))) {
		/* Configure PMIC APC Rail. */
		state = falkor_get_rail_state(rail);
		if (state < FALKOR_FINI_APR) {
			if (!falkor_apr_cold_boot_async(rail))
				return false;
		}
	}

	if (!(falkor_init_mask &
	      CLUSTER_TO_CPU_MASK(cluster))) {
		/* Configure QLL MBSU/DMSU. */
		state = falkor_get_cluster_state(cluster);
		if (state < FALKOR_FINI_QLL) {
			if (!falkor_apc_init_qll_register_async(cluster))
				return false;
		}
		state = falkor_get_cluster_state(cluster);
		if (state < FALKOR_FINI_FREQ) {
			clock_config_cluster(cluster,
					     __get_cpu_freq(cluster));
			falkor_set_cluster_state(cluster, FALKOR_FINI_FREQ);
		}
	}
	return true;
}

bool falkor_deassert_reset_async(uint8_t cpu, bool allow_wait)
{
	uint8_t cluster = CPU_TO_CLUSTER(cpu);
	uint8_t state = 0;

	if (falkor_init_mask & CPU_TO_MASK(cpu))
		return true;

	if (!falkor_configure_clock_async(cpu, allow_wait))
		return false;

	if (!(falkor_init_mask &
	      CLUSTER_TO_CPU_MASK(cluster))) {
		state = falkor_get_cluster_state(cluster);
		if (state < FALKOR_FINI_L2) {
			if (!falkor_apc_l2_cold_boot_async(cluster,
							   allow_wait))
				return false;
		}
	}

	state = falkor_get_cpu_state(cpu);
	if (state < FALKOR_FINI_CPU) {
		if (!falkor_apc_cpu_cold_boot_async(cpu, allow_wait))
			return false;
	}
	falkor_init_mask |= CPU_TO_MASK(cpu);
	return true;
}

bool falkor_is_cluster_clocked(uint16_t cluster)
{
	return !!(falkor_get_cluster_state(cluster) >= FALKOR_FINI_FREQ);
}

void falkor_configure_clock(uint8_t cpu, bool allow_wait)
{
	while (!falkor_configure_clock_async(cpu, allow_wait));
}

void falkor_deassert_reset(uint8_t cpu, bool allow_wait)
{
	while (!falkor_deassert_reset_async(cpu, allow_wait));
}

void cpus_config_entry_point(uint64_t entry)
{
	falkor_configure_entry_point(entry);
}

bool cpus_deassert_reset_async(int cpu)
{
	bool allow_wait = true;

#if defined(CONFIG_TESTOS_EMU) || defined(CONFIG_TESTOS_ATE_NOWAIT)
	allow_wait = false;
#endif
	return falkor_deassert_reset_async(cpu, allow_wait);
}

static uint64_t cmd_get_cpu_mask_field(char *str, int len)
{
	uint64_t cpu_mask = CMD_INVALID_CPU_MASKS;
	int x;

	if (isdigit(str[0])) {
		if (len < 1)
			return CMD_INVALID_CPU_MASKS;
		x = strtoul(str, 0, 0);
		if (x >= MAX_CPU_NUM)
			return CMD_INVALID_CPU_MASKS;
		cpu_mask = CPU_TO_MASK(x);
	} else if (str[0] == 'c') {
		if (len < 2 || !isdigit(str[1]))
			return CMD_INVALID_CPU_MASKS;
		x = strtoul((str + 1), 0, 0);
		if (x >= MAX_CPU_CLUSTERS)
			return CMD_INVALID_CPU_MASKS;
		cpu_mask = CLUSTER_TO_CPU_MASK(x);
	} else if (str[0] == 'r') {
		if (len < 2 || !isdigit(str[1]))
			return CMD_INVALID_CPU_MASKS;
		x = strtoul((str + 1), 0, 0);
		if (x >= MAX_CPU_RAILS)
			return CMD_INVALID_CPU_MASKS;
		cpu_mask = RAIL_TO_CPU_MASK(x);
	} else if (strncmp(str, "all", 3) == 0) {
		cpu_mask = CPU_ALL;
	} else {
		return CMD_INVALID_CPU_MASKS;
	}
	return cpu_mask;
}

/* Decdoe a CPU mask string.
 *
 * Parameters:
 *   str: CPU mask string, formatted as XX|cXX|rXX.
 *        Where:
 *          XX indicates a CPU;
 *          cXX indicates a CPU cluster and
 *          rXX indicates a CPU rail.
          For example, "0|c1|r2".
 */
uint64_t cmd_get_cpu_mask(char *str)
{
	int i = -1;
	int j = 0;
	uint64_t cpu_mask = CMD_INVALID_CPU_MASKS;
	uint64_t mask;
	char sub_str[3];

	memset(sub_str, 0, sizeof(sub_str));
	do {
		i++;
		if (str[i] != '|' && str[i] != '\0') {
			switch (j) {
			case 0:
				if (!isdigit(str[i]) &&
				    str[i] != 'c' &&
				    str[i] != 'r' &&
				    str[i] != 'a')
					return CMD_INVALID_CPU_MASKS;
				break;
			case 1:
				if (sub_str[0] == 'a' && str[i] != 'l')
					return CMD_INVALID_CPU_MASKS;
				if (sub_str[0] != 'a' && !isdigit(str[i]))
					return CMD_INVALID_CPU_MASKS;
				break;
			case 2:
				if (isdigit(sub_str[0]))
					return CMD_INVALID_CPU_MASKS;
				if (sub_str[0] == 'a' && str[i] != 'l')
					return CMD_INVALID_CPU_MASKS;
				if (sub_str[0] != 'a' && !isdigit(str[i]))
					return CMD_INVALID_CPU_MASKS;
				break;
			default:
				return CMD_INVALID_CPU_MASKS;
			}
			sub_str[j++] = str[i];
		} else {
			mask = cmd_get_cpu_mask_field(sub_str, j);
			if (mask == CMD_INVALID_CPU_MASKS)
				return CMD_INVALID_CPU_MASKS;
			cpu_mask |= mask;
			j = 0;
			memset(sub_str, 0, sizeof(sub_str));
		}
	} while (str[i] != '\0');
	return cpu_mask;
}
