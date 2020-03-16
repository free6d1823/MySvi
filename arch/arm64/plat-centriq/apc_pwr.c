#include <asm/mach/spm/spm.h>
#include <asm/mach/plat_topology.h>
#include <asm/mach/platform_def.h>
#include <asm/psci.h>

#include <asm/mach/spm/spm_target.h>
#include "apcpwr.h"
#include <asm/io.h>
#include <target/cpus.h>
#include <target/delay.h>
#include <target/smp.h>
#include <stdio.h>

/* save the partial goods since it won't change */
static uint64_t partial_good;

/*
 * Assert is used to catch errors sooner with debug builds, but runtime
 * logging is used for release builds when assert is compiled out.
 */
#define SPM_RESULT_CHECK(res, func)     {if ((res) != SPM_SUCCESS) puts( func); }

/*
 * Initialize APR SAW registers other than SPM
 *
 * This initialization is required by IMC for hardware DCVS but is done
 * here since it must be performed along with the SPM initialization. It
 * does not warrant its own driver since it is one-time only config.
 */
 static void apcpwr_apr_saw_init(unsigned int rail)
 {
     /* Initialize AVS */
     APCS_HWIO_OUTR(rail, SAW4_2_0_AVS, SAW4_AVS_CTL,   0x0101C151);
     APCS_HWIO_OUTR(rail, SAW4_2_0_AVS, SAW4_AVS_DLY,   0x00000004);
     APCS_HWIO_OUTR(rail, SAW4_2_0_AVS, SAW4_AVS_LIMIT, 0x00AE00A9);

     /* Initialize CVS */
     APCS_HWIO_OUTR(rail, SAW4_2_0_AVS, SAW4_CVS_CTL,   0x00020001);
     APCS_HWIO_OUTR(rail, SAW4_2_0_AVS, SAW4_CVS_DLY,   0x3FF0C80A);

     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_PMIC_DATA, 0,  0x000000C8);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_PMIC_DATA, 1,  0x0000008C);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_PMIC_DATA, 2,  0x000000AA);

     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 0,  0x1B10C830);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 1,  0x0F0FE8DB);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 2,  0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 3,  0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 4,  0x8B70B050);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 5,  0xDBDAF89B);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 6,  0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 7,  0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 8,  0x2182118B);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 9,  0xF2019B92);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 10, 0xC2D2D0A2);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 11, 0x0F0FCBAB);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 12, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 13, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 14, 0xF2A2C28B);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 15, 0xABCBD2D0);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 16, 0x119B9221);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 17, 0x0F0F0182);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 18, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 19, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 20, 0x050A151A);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 21, 0x0F0F151A);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 22, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 23, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 24, 0x454A555A);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 25, 0x0F0F555A);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 26, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 27, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 28, 0x858A959A);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 29, 0x0F0F959A);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 30, 0x0F0F0F0F);
     APCS_HWIO_OUTRI(rail, SAW4_2_0_AVS, SAW4_CVS_SEQ_ENTRY, 31, 0x0F0F0F0F);
 }

	/* -----------------------------------------------------
	 *  void set_os_lock(unsigned long locked);
	 *
	 * Helper to set the calling core's OS Lock.
	 * -----------------------------------------------------
	 */

void set_os_lock(unsigned long locked)
{
    asm volatile (
      "isb \n\t" \
      "msr OSLAR_EL1, %0 \n\t" \
      ::"r" (locked)
    );
    asm volatile(
      "isb \n\t"
    );
}


void qcom_wfi_wrapper()
{
    asm volatile (
            "dsb sy \n\t" \
            "wfi" \
    );
}

void platform_wfi()
{
    //set_os_lock(1);
    qcom_wfi_wrapper();
    //set_os_lock(0);
}

 /*
  * Wait for spm to be asleep with timeout
  */
static bool spm_wait_asleep(spm_handle spm)
{
    unsigned int poll_cnt = 0;
    bool asleep = false;
    spm_result_t res;

    do {
        if (poll_cnt > 0)
            udelay(SPM_WAIT_POLL_PERIOD_US);

        res = spm_sleep_state(spm, &asleep);
        SPM_RESULT_CHECK(res, "spm_sleep_state failed \n");

        ++poll_cnt;
    } while (!asleep && (poll_cnt < SPM_WAIT_POLL_COUNT));

    return asleep;
}

/*
 * Wait for spm to finish its current operation
 */
static bool spm_wait_busy(spm_handle spm)
{
    unsigned int poll_cnt = 0;
    bool busy = true;
    spm_result_t res;

    do {
        if (poll_cnt > 0)
            udelay(SPM_WAIT_POLL_PERIOD_US);

        res = spm_busy(spm, &busy);
        SPM_RESULT_CHECK(res, "spm_busy");

        ++poll_cnt;
    } while (busy && (poll_cnt < SPM_WAIT_POLL_COUNT));

    return busy;
}

/*
 * Initialize SPM driver and instances
 */
static void apcpwr_spm_init(void)
{
    spm_result_t res;
    spm_handle spm;      //g_spms struct point
    int i;

    /*
     * On non-Si platforms the partial goods indicate which HW blocks are
     * not present and thus the associated SPMs need to be skipped. On Si
     * initialize all SPMs and set each masked CPU's PWR_STATE_IDX to 0x7
     * to mimic C5. When Both CPUs in a duplex are masked, the L2 state out
     * of reset is such that it mimics D5. TODO: What about the APR if all
     * children are masked out?
     */
    spm_driver_init();  //init the spm struct

    for (i = 0; i < PLATFORM_RAIL_COUNT; i++)
    {
        if (!plat_rail_is_supported(i))
            continue;

        res = spm_init(spm_get_handle(SPM_TYPE_APR, i));
        SPM_RESULT_CHECK(res, "APR spm_init failed\n");

        //apcpwr_apr_saw_init(i);
    }

    for (i = 0; i < PLATFORM_CLUSTER_COUNT; i++)
    {
        if (!plat_cluster_is_supported(i))
            continue;

        res = spm_init(spm_get_handle(SPM_TYPE_L2, i));
        SPM_RESULT_CHECK(res, "L2 spm_init failed\n");
    }

    for (i = 0; i < PLATFORM_CORE_COUNT; i++)
    {
        if (!plat_core_is_supported(i))
            continue;

        spm = spm_get_handle(SPM_TYPE_CPU, i);

        res = spm_init(spm);
        SPM_RESULT_CHECK(res, "CPU spm_init failed\n");

        if (!plat_core_is_supported(i))
        {
            res = spm_mimic_low_power_mode(spm, SPM_MODE_C5_PC);
            SPM_RESULT_CHECK(res, "Set cpu into c5 failed \n");
        }
    }
}

/*
 * HPSS Register Initialization
 *
 * The rails have been physically powered on already by XBL Loader. This
 * function performs the initialization required for SPM mode switches.
 */
static void apcpwr_hpss_init(void)
{
    unsigned int rail, clu, cpu;

    /* Iterate over all supported rails */
    for (rail = 0; rail < PLATFORM_RAIL_COUNT; rail++)
    {
        if (!plat_rail_is_supported(rail))
            continue;

        /*
         * APR init for SPM mode switches
         *  - Commented default values out
         */
        //APCS_HWIO_OUTR(rail, APR_CFG,  PWR_GATE_DLY0,    0x01030000);
        //APCS_HWIO_OUTR(rail, APR_CFG,  PWR_GATE_DLY1,    0x00000003);
        //APCS_HWIO_OUTR(rail, APR_CFG,  MAS_DLY0,         0x00000000);
        //APCS_HWIO_OUTR(rail, APR_CFG,  MAS_DLY1,         0x00040400);
        //APCS_HWIO_OUTR(rail, APR_CFG,  APM_MODE_DLY0,    0x00000001);
        //APCS_HWIO_OUTR(rail, APR_CFG,  APM_MODE_DLY1,    0x0000000A);
        //APCS_HWIO_OUTR(rail, APR_CFG,  SER_DLY,          0x140C0700);
        //APCS_HWIO_OUTR(rail, APR_CFG,  SER_DLY_SEL0,     0x09090909);
        //APCS_HWIO_OUTR(rail, APR_CFG,  SER_DLY_SEL1,     0x09090909);
        //APCS_HWIO_OUTR(rail, APR_CFG,  SER_DLY_SEL2,     0x00000009);
        //APCS_HWIO_OUTR(rail, DCVS_APR, ACC_CTL_DLY,      0x04040104);
        //APCS_HWIO_OUTR(rail, APR_CFG,  SLP_REQ_DLY,      0x00000004);

        APCS_HWIO_OUTR(rail, APR_DBG,  EMU_DBG_MODE_MSK, 0x00000085);
        //APCS_HWIO_OUTR(rail, DCVS_APR, DCVS_CHKN_APR,    0x00000002);
        //APCS_HWIO_OUTR(rail, DCVS_APR, DCVS_CHKN_FSM,    0x00000001);

        APCS_HWIO_OUTH(rail, HPSS_CFG, LDO_CFG,          0x89F3E471);
        //APCS_HWIO_OUTH(rail, HPSS_CFG, APM_CFG,          0x00000000);
        APCS_HWIO_OUTH(rail, HPSS_CFG, ODCM_CFG,         0xE04214F7);
        APCS_HWIO_OUTH(rail, HPSS_CFG, MEM_RET_VREF,     0x00000029);   //SRAM RET value in VREF -- Array Retention Voltage
        APCS_HWIO_OUTH(rail, HPSS_CFG, MEM_VMIN_VREF,    0x00000057);   //SRAM VMIN value in VREF

        APCS_HWIO_OUTR(rail, APR_CFG,  SER_EN,           0x00000001);   //When set this bit enables the falling edge serializer

        APCS_HWIO_OUTH(rail, HPSS_CFG, AHB_CBCR,         0x00000002);   //1 HW_CTL RW if 1'b1, HW clock gating is enabled.
        APCS_HWIO_OUTH(rail, HPSS_CFG, REF_CBCR,         0x00000002);   //1 HW_CTL RW if 1'b1, HW clock gating is enabled
        APCS_HWIO_OUTH(rail, HPSS_DBG, WDOG_DIAG_EN,     0x03C00073);

        /* Iterate over supported clusters in the rail */
        for (clu = RAIL_MIN_CLU_IDX(rail); clu < RAIL_MAX_CLU_IDX(rail); clu++)
        {
            if (!plat_cluster_is_supported(clu))
                continue;

            /*APC init for SPM mode switches*/
            APCS_HWIO_OUTD(clu, APC_CFG,  APC_PWR_GATE_MODE_DLY, 0x00000000);	  //APC CFG Registers
            //APCS_HWIO_OUTD(clu, DCVS_APC, APC_LDO_VREF_FUNC,     0x0000004D);     //APC DCVS Registers
            //APCS_HWIO_OUTD(clu, DCVS_APC, APC_LDO_VREF_RET,      0x0000001F);	  //APC DCVS Registers

            APCS_HWIO_OUTDF(clu, APC_TZ, APC_TZ_VOTE, L2_PC, 0);

            /* Iterate over supported cores in the cluster */
            for (cpu = CLU_MIN_CPU_IDX(clu); cpu < CLU_MAX_CPU_IDX(clu); cpu++)
            {
                if (!plat_core_is_supported(cpu))
                    continue;

                APCS_HWIO_OUTC(cpu, CPU_DBG, EMU_DBG_MODE_MSK,   0x0007E117);
            }
        }
    }
}

/*
 * Place all secondary cores and clusters under SPM control
 *
 * This function can be called after HPSS initialization before any secondary
 * cores or clusters have been brought online. It places all available CPUs in
 * C5 and L2s in D5 such that all CPU_ON calls can utilize SPM wakeup.
 */
void apcpwr_enter_spm_control(void)
{
    unsigned int clu, cpu;
    unsigned int pri_cpu = plat_my_core_pos();
    unsigned int pri_clu = CPU_TO_CLU_IDX(pri_cpu);
    spm_result_t res;
    spm_handle clu_spm, cpu_spm;
    bool asleep;

    /* Iterate over all supported clusters */
    for (clu = 0; clu < PLATFORM_CLUSTER_COUNT; clu++)
    {
        if (!plat_cluster_is_supported(clu))
            continue;

        /* put secondary clusters in D5 */
        if (clu != pri_clu)
        {
            clu_spm = spm_get_handle(SPM_TYPE_L2, clu);
            res = spm_start_low_power_mode(clu_spm, SPM_MODE_D5_PC);
            SPM_RESULT_CHECK(res, "spm_start_lpm l2 error\n");
        }

        /* Iterate over supported cores in the cluster */
        for (cpu = CLU_MIN_CPU_IDX(clu); cpu < CLU_MAX_CPU_IDX(clu); cpu++)
        {
            if (!plat_core_is_supported(cpu) || (cpu == pri_cpu))
                continue;

#ifdef CONFIG_TESTOS_EMU
            /* workaround emulation PWR_CTL[POR_RST] issue */
            APCS_HWIO_OUTCF(cpu, CPU_PWR_CTL, PWR_CTL, DISABLE_SPM_WAKEUP, 1);
#endif

            /* put secondary cores in C5 */
            cpu_spm = spm_get_handle(SPM_TYPE_CPU, cpu);
            res = spm_start_low_power_mode(cpu_spm, SPM_MODE_C5_PC);
            SPM_RESULT_CHECK(res, "spm_start_lpm cpu error\n");

            asleep = spm_wait_asleep(cpu_spm);
            if (!asleep)
            {
                puts("Core failed to enter C5\n");
                continue;
            }

            APCS_HWIO_OUTC(cpu, CPU_PWR_CTL, PWR_CTL, 0x00000100);
        }

        /* wait for cluster to enter D5 */
        if (clu != pri_clu)
        {
            asleep = spm_wait_asleep(clu_spm);
            if (!asleep)
            {
                puts("L2 failed to enter D5\n");
                continue;
            }

            APCS_HWIO_OUTD(clu, L2_PWR_CTL, L2_PWR_CTL, 0x00000100);
        }
    }
}

/*
 * Set default APR low power mode
 *
 * Rail idle will be enabled by IMC after HWDCVS initialization. This sets
 * the default mode which will be entered when all CPU/L2s enter any LPM
 * without explicitly requesting a rail LPM.
 */
static void apcpwr_set_default_apr_lpm(void)
{
    int rail;

    /* Iterate over all supported rails */
    for (rail = 0; rail < PLATFORM_RAIL_COUNT; rail++)
    {
        if (!plat_rail_is_supported(rail))
            continue;

        /* Set default rail mode */
        apcpwr_apr_enter_lpm(rail, SPM_MODE_G1_LIGHT_SLEEP);

        /* IMC votes for APR idle when HWDCVS init is complete */
    }
}

int apcpwr_cpu_wakeup(unsigned long cpu)
{
    unsigned long clu = CPU_TO_CLU_IDX(cpu);
    spm_result_t res;
    spm_handle cpu_spm = spm_get_handle(SPM_TYPE_CPU, cpu);
    bool busy = true;

    /* Ensure the APR and L2 are awake while waking the CPU */
    APCS_HWIO_OUTDF(clu, L2_SW_EVENT,  L2_SW_SPM_EVENT, SPM_WAKEUP, 1);
    APCS_HWIO_OUTCF(cpu, CPU_SW_EVENT, SW_SPM_EVENT,    SPM_WAKEUP, 1);

    res = spm_wakeup(cpu_spm);
    //SPM_RESULT_CHECK(res, "spm_wakeup");

    /* wait for CPU SPM to wake */
    busy = spm_wait_busy(cpu_spm);
    if (busy)
    {
        puts("APCPWR: Core failed to wake up\n");
    }
   printf("power on \n");
    /* Clear APR and L2 SPM wakeup events */
    APCS_HWIO_OUTCF(cpu, CPU_SW_EVENT, SW_SPM_EVENT,    SPM_WAKEUP, 0);
    APCS_HWIO_OUTDF(clu, L2_SW_EVENT,  L2_SW_SPM_EVENT, SPM_WAKEUP, 0);

    return !busy;
}

void apcpwr_cpu_enter_lpm(unsigned long cpu, unsigned int lpm)
{
    spm_result_t res;
    spm_handle cpu_spm = spm_get_handle(SPM_TYPE_CPU, cpu);

    /* No CPU power controller state specific settings */

    res = spm_set_low_power_mode(cpu_spm, lpm);
    SPM_RESULT_CHECK(res, "spm_set_low_power_mode cpu");
}

void apcpwr_cpu_exit_lpm(unsigned long cpu, unsigned int lpm)
{
    spm_result_t res;
    spm_handle cpu_spm = spm_get_handle(SPM_TYPE_CPU, cpu);

    /* Set the SPM for C1 to control clock gating when wfi is issed outside
     * the context of PSCI. */
    res = spm_set_low_power_mode(cpu_spm, SPM_MODE_C1_CLK_GATE);
    SPM_RESULT_CHECK(res, "spm_enable cpu");
}

void apcpwr_clu_enter_lpm(unsigned long clu, unsigned int lpm)
{
    spm_result_t res;
    spm_handle l2_spm = spm_get_handle(SPM_TYPE_L2, clu);

    /* Program L2 power controller state specific settings */
    switch (lpm)
    {
        case SPM_MODE_D4_FASTPC_INV:
        case SPM_MODE_D5_PC:
            APCS_HWIO_OUTDF(clu, L2_DATA_PUSH, L2_DATA_PUSH, REQ, 1);
            break;
    }

    res = spm_set_low_power_mode(l2_spm, lpm);
    SPM_RESULT_CHECK(res, "spm_set_low_power_mode l2");
}

void apcpwr_clu_exit_lpm(unsigned long clu, unsigned int lpm)
{
    spm_result_t res;
    spm_handle l2_spm = spm_get_handle(SPM_TYPE_L2, clu);

    /* Simply disable the SPM now, will be automatically re-enabled
     * next time an LPM is set. */
    res = spm_enable(l2_spm, false);
    SPM_RESULT_CHECK(res, "spm_enable l2");

    /* Unconfigure L2 power controller state specific settings */
    switch (lpm)
    {
        case SPM_MODE_C0_RUN: // Didn't enter an LPM - nothing to do
            return;

        case SPM_MODE_D4_FASTPC_INV:
        case SPM_MODE_D5_PC:
            APCS_HWIO_OUTDF(clu, L2_DATA_PUSH, L2_DATA_PUSH, REQ, 0);
            break;
    }
}

void apcpwr_apr_enter_lpm(unsigned long apr, unsigned int lpm)
{
    spm_result_t res;
    spm_handle apr_spm = spm_get_handle(SPM_TYPE_APR, apr);

    /* No APR power controller state specific settings */

    res = spm_set_low_power_mode(apr_spm, lpm);
    SPM_RESULT_CHECK(res, "spm_set_low_power_mode apr");
}

void apcpwr_apr_exit_lpm(unsigned long apr, unsigned int lpm)
{
    spm_result_t res;
    spm_handle apr_spm = spm_get_handle(SPM_TYPE_APR, apr);

    /* Hide G1 from OSPM by setting as default state */
    res = spm_set_low_power_mode(apr_spm, SPM_MODE_G1_LIGHT_SLEEP);
    SPM_RESULT_CHECK(res, "spm_set_low_power_mode apr failed.");
}

/*******************************************************************************
 * Platform handler called when a CPU is about to enter standby.
 ******************************************************************************/
void QDF2400_cpu_standby(uint8_t cpu_state)
{
    unsigned long cpu = plat_my_core_pos();

    /* program chosen C-state */
    //tf_printf_pcpu("STANDBY: C%u\n", cpu_state);
    apcpwr_cpu_enter_lpm(cpu, cpu_state);

    platform_wfi();

    //SWEVENT(SLEEP_EXIT, cpu_state);

    /* clean up */
    //tf_printf_pcpu("WAKEUP: C%u\n", cpu_state);
    apcpwr_cpu_exit_lpm(cpu, cpu_state);
}

void core_entry_lowpower(unsigned int power_state)
{
    /* Fast path for CPU standby.*/
    /*
    * Set the state of the CPU power domain to the platform
    * specific retention state and enter the standby state.
    */
    //cpu_pd_state = state_info.pwr_domain_state[PSCI_CPU_PWR_LVL];
    //psci_set_cpu_local_state(cpu_pd_state);   //_cpu_data()->psci_svc_cpu_data.local_state = cpu_pd_state

    QDF2400_cpu_standby(power_state);

    /* Upon exit from standby, set the state back to RUN. */

    //psci_set_cpu_local_state(PSCI_LOCAL_STATE_RUN);
}

int pwr_domain_on(uint64_t mpidr)
{
    unsigned long cpu_pos = plat_core_pos_by_mpidr(mpidr);
    char cpu_awake;

    /* Wake up core and higher levels if neccessary */
    cpu_awake = apcpwr_cpu_wakeup(cpu_pos);
    if (cpu_awake)
        return PSCI_E_SUCCESS;
    else
        return PSCI_E_INTERN_FAIL;
}

void pwr_domain_on_finish(void)
{
    //const plat_local_state_t *local_state = target_state->pwr_domain_state;
    unsigned long cpu = plat_my_core_pos();
    unsigned long clu = CPU_TO_CLU_IDX(cpu);
    unsigned long apr = CLU_TO_RAIL_IDX(clu);

    /* Clean up the APR SPM. It may be in any LPM due to all its cores
    * being off or suspended while this one was off. */
    apcpwr_apr_exit_lpm(apr, 0);

    /* Clean up the L2 SPM. It may be in any LPM due to both cores being
     * off or the other core entering suspend while this one was off. */
    apcpwr_clu_exit_lpm(clu, SPM_MODE_D5_PC);

    /* Clean up the CPU SPM */
    apcpwr_cpu_exit_lpm(cpu, 0);
}


/*Power related initiation*/
void apcpwr_init(void)
{
    partial_good = get_cpu_mask();

    /* Init all SPMs */
    apcpwr_spm_init();

    /* Init required for SPM mode switches */
    apcpwr_hpss_init();

    /* Place secondary cores/clusters under SPM control */
    apcpwr_enter_spm_control();

    /* Allow rails to enter LPM without explicit request via PSCI */
    apcpwr_set_default_apr_lpm();

    /* Setup SPM managed clock gating on wfi for the primary core */
    apcpwr_cpu_exit_lpm(plat_my_core_pos(), SPM_MODE_C0_RUN);

}

/*******************************************************************************
 * Simple routine to determine whether a mpidr is valid or not.
 ******************************************************************************/
static int psci_validate_mpidr(uint64_t mpidr)
{
    if (plat_core_pos_by_mpidr(mpidr) < 0)
        return PSCI_E_INVALID_PARAMS;

    return PSCI_E_SUCCESS;
}

int psci_cpu_on(uint64_t target_cpu,
                uint64_t entrypoint,
                uint64_t context_id)
{
    int rc;
    uint64_t target_idx;

    entry_addr = entrypoint;  //save the entry point addr

    /* Determine if the cpu exists of not */
    rc = psci_validate_mpidr(target_cpu);
    if(rc != PSCI_E_SUCCESS)
        return rc;

    target_idx = plat_core_pos_by_mpidr(target_cpu);
    printf("target idx: %d \n", target_idx);


    rc = pwr_domain_on(target_cpu);

exit:
    return rc;
}

