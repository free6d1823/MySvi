#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <target/memory.h>
#include <target/delay.h>
#include <target/uart.h>
#include <target/cache.h>
#include <target/launch.h>
#include <asm/falkor.h>
#include <asm/mach/plat_topology.h>

extern volatile uint64_t ddr_real_size;
int boot_kernel = 0 ;

/* DSDT platform information address, STA() method depend on it */
#define plti_pa 0x3083000ULL

typedef struct {
	uint32_t pf_type;
	uint32_t pf_version;
	uint32_t pf_subtype;
	uint32_t usbdevmask;
	uint64_t pgcpu;
	uint64_t pgl3;
	uint64_t power_features_bm;
	uint64_t console_address;
} plti;

int get_cpu_logical_no(uint64_t phy_no)
{
    return 1;
}

/* prepare platform information for DSDT */
void prepare_plti()
{
	plti *p = (plti*)plti_pa;
	memset((void*)p, 0, sizeof(plti));

	p->pgcpu = get_cpu_mask();
}

void kernel_launch()
{
    uint64_t cpu_partial_good = get_cpu_mask();
    uint64_t l3_partial_good = get_llc_mask();
    unsigned int i = 0;
    int primary_assigned = 0;
    uint8_t cpu;

    prepare_plti();

    /* generate the APIC according to the cpu partial good */
    apic_generate(cpu_partial_good);

    /* generate the PPTT according to the cpu and l3 partial good */
    pptt_generate(cpu_partial_good, l3_partial_good);

    /* generate the MEMMAP according to the real dimm size */
    memmap_generate(ddr_real_size);

    boot_kernel = 1;
#if !defined(CONFIG_IRQ_POLLING) && (UART_CON_ID >= QUART_ACUART_BASE)
    pl01x_irq_exit();
#endif

    falkor_configure_entry_point(CPU_POWER_ON_ENTRY_POINT);

#ifdef CONFIG_PSCI
    for (i = 0; i < MAX_CPU_NUM; i++) {
        if(plat_core_is_supported(i))
            falkor_configure_clock(i, false);
    }

    for(cpu = 0; cpu < MAX_CPU_NUM; cpu++) {
        if(cpu_partial_good & ((uint64_t)1 << cpu))
            break;
    }

    falkor_deassert_reset(cpu, false);
#else
    for (i=0; i < MAX_CPU_NUM/2; i++) {
        if ( cpu_partial_good & (0x1ULL<<(i*2))) {
            falkor_deassert_reset(i*2, false);
        }
    }

    for (i=0; i < MAX_CPU_NUM/2; i++) {
        if ( cpu_partial_good & (0x1ULL<<(i*2+1))) {
            //wake up odd secondary cpus, spin_table mode
            falkor_deassert_reset(i*2+1, false);
        }
    }
#endif
}

int do_kernel_launch(int argc, char *argv[])
{
    if (argc != 2) {
        printf("--ERROR: The parameters not compatible \n");
        return -1;
    }

    if (strcmp(argv[1], "launch") == 0) {
        kernel_launch();
    }
    else {
        printf("Unknown command\n\n");
        return -1;
    }

    return 0;

}

/* legacy code, only for reference */
static void enableos_boot_jump(void)
{
	uint8_t cpu = smp_processor_id();
	uint64_t addr;

	gic3_early_init();

	if (cpus_boot_cpu == cpu) {
		/* entrance for primary_cpu */
#ifdef CONFIG_PCIE_QCOM
		/* pcie controller init only in primary cpu. */
		pcie_init();
		pcie_link();
#endif
#ifdef  CONFIG_EMAC
	extern void EMAC_Mini_Init();
	EMAC_Mini_Init();
#endif
#if (UART_CON_ID != QUART_ACUART_BASE)
		/* prepare acuart for the kernel only in primary cpu */
		__uart_dm_ctrl_init(QUART_ACUART_BASE);
#endif

		/* prepare the spm in primary_cpu */
		apcpwr_init();
		boot_jump_linux();
	} else {
		/* entrance for secondary_cpus */
#ifdef CONFIG_PSCI
		pwr_domain_on_finish();
		addr = entry_addr;
#else
		addr =(uint64_t)spin_table;
#endif
		secondary_cpu_switch_to_el2((uint64_t)addr, 1);
	}

	/* unreached */
	return;
}

