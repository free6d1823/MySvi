#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <target/clock.h>
#include <target/arch.h>
#include <target/memory.h>
#include <target/cpus.h>
#include <target/smp.h>
#include <target/ring.h>
#include <target/l3.h>
#include <target/ddr.h>
#include <asm/mach/chipinfo.h>
#include <asm/mach/tlmm_boot.h>
#include <asm/plat-centriq/freqplan.h>
#include <asm/mach/cbf.h>

static uint64_t qdf2400_cbf_freq = ARCH_LLC_BOOT_FREQ;
static uint64_t qdf2400_apc_freqs[MAX_CPU_CLUSTERS] = {
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
	ARCH_CPU_BOOT_FREQ,
};

int arch_early_init(void)
{
    DIEINFO_PROPS DieInfo;
    uint8_t minor = 0;
    init_socket_info(0);
    get_socket_info(&DieInfo, 0);
    if (DieInfo.SocType != SOCINFO_SOCTYPE_SILICON) {
        // Clocks are only supported on silicon
        // return TRUE;
    }
    if (DieInfo.MajorVersion == 1) {
        if (DieInfo.MinorVersion > 1)
            minor = 1;
    }
#ifndef CONFIG_PRE_HAPS
    /*On haps needn't config the pll*/
    freqplan_apply(DieInfo.MajorVersion, minor);
#endif
    return 0;
}

//fatcm_size is only for 0MB, 4MB, 8MB, 16MB, 32MB
//0MB means that disable fatcm function
static int l3_tcm_init(unsigned int fatcm_size)
{
    monaco_init_t init_parms;
    memset(&init_parms, 0, sizeof(monaco_init_t));
    init_parms.log_level = HIGH;
    init_parms.soc_hw_version.major_version = 1;
    init_parms.soc_hw_version.minor_version = 1;
    init_parms.soc_hw_version.aux_version = 1 ;

#ifdef CONFIG_QCOM_DDRSS
    init_parms.mode = get_platform_id();
#else
    init_parms.mode = SILICON;
#endif

    init_parms.goods.l3_interleaves =get_llc_mask();
    init_parms.goods.hydra_cores =get_cpu_mask();

    init_parms.l3_settings.snoop_fltr_en = true;
    init_parms.l3_settings.LL_query_en = true;
    init_parms.l3_settings.affinity = false;
    init_parms.l3_settings.LL_breaker_en = true;
    init_parms.l3_settings.auto_gate_idle_clk_cyc_cnt = 27391;
    init_parms.l3_settings.rplcmnt_policy = LRU;
    init_parms.l3_settings.addr_hash_en = true;
    init_parms.l3_settings.cache_cap_mon_en = true;
    init_parms.l3_settings.trace_settings.trace_interleaves = 0;
    init_parms.l3_settings.trace_settings.allocation = ALLOCATE_0_PERCENT;
    init_parms.l3_settings.auto_gate_clk_en = true;

    if(( fatcm_size == 4 ) || ( fatcm_size == 8 ) || ( fatcm_size == 16 ) || ( fatcm_size == 32 ))
    {
        init_parms.l3_settings.fatcm = true;
        init_parms.l3_settings.size_in_mb = fatcm_size ;
    }
    else
    {
        init_parms.l3_settings.fatcm = false;
    }

    init_parms.mddr_settings.ddr_granule= DDR_DIST_GRANULE_256B ;
    init_parms.rs_settings.rs_dlbu_ena = true;
    init_parms.rs_settings.rs_sbrce_ena = true;
    init_parms.rs_settings.rs_sbrlvl = RS_SBRLVL_0;
    init_parms.rs_settings.rs_sbrmsk = 0x0;
    init_parms.rs_settings.rs_lfsr_ena = true;
    init_parms.rs_settings.rs_clkon_req_ena = true;
    init_parms.rs_settings.rs_clkon_delay = 0x5;
    init_parms.rs_settings.rs_clkon_hysteresis = 0x3FF;

#ifdef CONFIG_QCOM_DDRSS
    {
        static uint64_t spd_data[4096];
        extern void get_smbus_configuration(monaco_init_t* init_parms, uint64_t spd_base);

        boot_tlmm_init();
        get_smbus_configuration(&init_parms, (uint64_t)spd_data);
    }
#endif
    rs_init(&init_parms);
    l3_init(init_parms.mode, init_parms.goods.l3_interleaves, &(init_parms.l3_settings));

    return 0;
}

int arch_late_init(uint64_t apc_freq, uint64_t cbf_freq)
{
    int chip_ver = get_version();
    int chip_sn = get_serialnum();

    printf("Chip version: %d.%d \n",
           chip_ver >> 16 , chip_ver & 0xffff);
    printf("Chip  serial: %x \n", chip_sn);

    set_cpu_freq(apc_freq);
    set_llc_freq(cbf_freq);

    cbf_init_l3_blocks();
    /* Configure core frequency. */
    clock_config_cbf(get_llc_freq());

#ifdef CONFIG_TCM
    l3_tcm_init(32);
#else
    l3_tcm_init(0);
#endif
#ifdef CONFIG_DDR_INIT_DEFAULT
    ddr_init();
#endif
    return 0;
}

void* apc_my_imemheap(void)
{
    unsigned long cpu = plat_my_core_pos();

    return (void*)STACK_START(cpu);
}

void* apc_my_tcmheap(void)
{
    unsigned long cpu = plat_my_core_pos();

    return (void*)PERCPU_TCM_SLOT_START(cpu);
}

uint64_t __get_cpu_freq(uint8_t cluster)
{
	if (cluster >= MAX_CPU_CLUSTERS)
		return 0;
	return qdf2400_apc_freqs[cluster];
}

void __set_cpu_freq(uint8_t cluster, uint64_t freq)
{
	if (cluster < MAX_CPU_CLUSTERS)
		qdf2400_apc_freqs[cluster] = freq;
}

uint64_t get_cpu_freq(void)
{
	uint8_t i;

	for (i = 0; i < MAX_CPU_CLUSTERS; i++) {
		if (qdf2400_apc_freqs[i])
			return qdf2400_apc_freqs[i];
	}
	return 0;
}

void set_cpu_freq(uint64_t freq)
{
	uint8_t i;

	for (i = 0; i < MAX_CPU_CLUSTERS; i++)
		qdf2400_apc_freqs[i] = freq;
}

uint64_t get_llc_freq(void)
{
	return qdf2400_cbf_freq;
}

void set_llc_freq(uint64_t freq)
{
	qdf2400_cbf_freq = freq;
}
