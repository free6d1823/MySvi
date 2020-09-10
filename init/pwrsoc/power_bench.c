#include <stdio.h>
#include <string.h>
//#include <target/pmic.h>
#include <target/dsr.h>
#include <target/cmdline.h>
#include <target/mmu.h>
#include <target/percpu.h>
#include <target/smp.h>
//#include <target/clock.h>
#include <target/irq.h>
#include <target/perf.h>
#include <target/memory.h>
//#include <target/dts.h>
//#include <target/gpio.h>
#include <target/launch.h>
#include <target/bench.h>
#include <target/heap.h>
#include <target/console.h>
#include <target/ddr.h>

#ifdef CONFIG_CPU_MASK
#define BENCH_CPU_MASK	CONFIG_CPU_MASK
#else
#define BENCH_CPU_MASK	CPU_ALL
#endif

#ifdef CONFIG_LLC_MASK
#define BENCH_LLC_MASK	CONFIG_LLC_MASK
#else
#define BENCH_LLC_MASK	LLC_ALL
#endif


static void pwrsoc_bench_imc_init(void)
{
#ifdef CONFIG_PWRSOC_BENCH
#ifdef CONFIG_TESTOS_EMU
	//tlmm_config_phase_flags();
#endif
	bench_init();
	bench_vf_init();
	pattern_init();
#endif
}

static void pwrsoc_bench_apc_init(void)
{
#ifdef CONFIG_PWRSOC_BENCH
	if (cpus_mode == CPU_MODE_BENCH)
		apc_do_bench();
	else
#endif
		cpu_local_init();
}

static void mem_info(void)
{
	printf("TEXT %0.10llx - %0.10llx (%dKB)\n",
			TEXT_START, TEXT_END, (TEXT_END - TEXT_START) >> 10);
	printf("DATA %0.10llx - %0.10llx (%dKB)\n",
			DATA_START, DATA_END, (DATA_END - DATA_START) >> 10);
	printf("    bss %0.10llx - %0.10llx (%dKB)\n",
			__bss_start, __bss_end, (__bss_end - __bss_start) >> 10);
	printf("HEAP %0.10llx - %0.10llx (%dKB)\n",
			HEAP_START, HEAP_END, (HEAP_END - HEAP_START) >> 10);
	printf("    PGTABLE %0.10llx - %0.10llx (%dKB)\n",
			HEAP_START, gp_buf, ((uintptr_t)gp_buf - HEAP_START) >> 10);
	printf("STACK %0.10llx - %0.10llx (%dKB)\n",
			STACKS_START, STACKS_END, STACKS_SIZE >> 10);

}

/* soc_early_init will be defined in board.c if any */
__weak int soc_early_init()
{
	return 0;
}
#include "../drivers/gdc/gdc.h"

int do_mem_display(int argc, char *argv[]);
int boot_jump_linux(int argc, char *argv[]);

char *mem_dump1[] = {"md","b", "0x60200000", "16"};
char *mem_dump2[] = {"md","b", "0x60280000", "16"};
char *mem_dump3[] = {"md","b", "0x64000000", "16"};
char *kernel_cmd[] = {"kernel", "0x60280000", "0x60200000"};

void entry(void)
{
	soc_early_init();
	console_early_init();

	puts("\nHello SVI @C");
	printf("%d\n", smp_processor_id());

	ddr_init();
	mmu_init();
	mem_info();
	dsr_init();
	tick_init();
	irq_init();

	do_mem_display(4, mem_dump1);
//if LINUX 
//	boot_jump_linux(3, kernel_cmd);
	
	timer_init();
	perf_init();
	//arch_early_init();
	console_late_init();
#ifndef CONFIG_TESTOS_EMU
	//pmic_init(0, 0);
	//pmbus_init();
#endif
	//arch_late_init(ARCH_CPU_NORM_FREQ,
	//	       ARCH_LLC_NORM_FREQ);
#ifndef CONFIG_TESTOS_EMU
	//qdss_init();
#endif
	//cpu_remote_init();
	//pwrsoc_bench_imc_init();

	percpu_init();
	cmd_init();
	smp_register_cpu();
//if GDC svi test
	gdc_init();

	dsr_loop();
}

void secondary_entry(void)
{
	printf("C[%d] UP\n", smp_processor_id());

	mmu_init();
	dsr_init();
	tick_init();
	irq_init();
	timer_init();
	perf_init();
	/* Mark end of primary boot */
	check_secondary_entry();
	//pwrsoc_bench_apc_init();
	smp_register_cpu();

	dsr_loop();
}
