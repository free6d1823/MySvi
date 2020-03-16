/*
 */
#include <testos.h>
#include <target/dsr.h>
#include <target/irq.h>
#include <target/timer.h>
#include <target/cpus.h>
#include <target/console.h>
#include <target/clock.h>
#include <target/arch.h>
#include <target/mmu.h>
#include <target/smp.h>
#include <target/power.h>
#include <target/percpu.h>
#include <target/irq.h>
#include <target/perf.h>

#ifdef CONFIG_CPU_MASK
#define TESTOS_CPUMASK		CONFIG_CPU_MASK
#else
#define TESTOS_CPUMASK		CPU_ALL
#endif
#ifdef CONFIG_LLC_MASK
#define TESTOS_LLCMASK		CONFIG_LLC_MASK
#else
#define TESTOS_LLCMASK		LLC_ALL
#endif

static int testos_dummy(void) { return 0; }

struct testos_setup ate_setup = {
	.magic = 0,
	.timeout = TESTOS_INFINITE,
	.apc_mask = CPU_ALL,
	.apc_freq = ARCH_CPU_BOOT_FREQ,
	.cbf_mask = LLC_ALL,
	.cbf_freq = ARCH_LLC_BOOT_FREQ,
	.repeats = TESTOS_BENCH_REPEATS,
	.test_entry = (uint64_t)testos_dummy,
};

static void testos_init_default(void)
{
	ate_setup.apc_mask = get_cpu_mask();
	ate_setup.cbf_mask = get_llc_mask();
	ate_setup.apc_mask &= TESTOS_CPUMASK;
	ate_setup.cbf_mask &= TESTOS_LLCMASK;
	set_cpu_mask(ate_setup.apc_mask);
	set_llc_mask(ate_setup.cbf_mask);

	ate_setup.apc_freq = ARCH_CPU_NORM_FREQ;
	ate_setup.cbf_freq = ARCH_LLC_NORM_FREQ;

	ate_setup.repeats = TESTOS_BENCH_REPEATS;
	ate_setup.timeout = TESTOS_INFINITE;
}

uint64_t testos_get_apc_pg(void)
{
	return get_cpu_mask();
}

uint64_t testos_get_cbf_pg(void)
{
	return get_llc_mask();
}

static void testos_config_phase_flags(void)
{
	tlmm_config_phase_flags();
}

void testos_indicate_phase_flags(uint8_t cpu, uint16_t msg)
{
	tlmm_output_phase_flags(msg |
				(cpu << TESTOS_GPIO_PHASE_CPU_SHIFT) |
				(1UL << TESTOS_GPIO_PHASE_VALID_SHIFT));
}

#ifdef CONFIG_TESTOS_EMU
/* Phase flags functionality is extreamly useful in the palladium Z1
 * emulation environment and the  pass/fail can be obtained via the virtual
 * serial console. So stop using CPU pass fail flags in that environment.
 */
static void testos_config_pass_fail(void)
{
}

void testos_indicate_pass(uint8_t cpu)
{
}

void testos_indicate_fail(uint8_t cpu)
{
}
#else
static void testos_config_pass_fail(void)
{
	uint32_t i;

	for (i = 0; i < MAX_CPU_NUM; i++) {
		gpio_config_port(i + TESTOS_GPIO_PASS_FAIL_PORT,
				 TESTOS_GPIO_PASS_FAIL_CFG);
	}
	gpio_write_output(TESTOS_GPIO_PHASE_VALID_PORT, false);
}

void testos_indicate_pass(uint8_t cpu)
{
	gpio_write_output(((uint32_t)cpu + TESTOS_GPIO_PASS_FAIL_PORT),
			  false);
}

void testos_indicate_fail(uint8_t cpu)
{
	gpio_write_output(((uint32_t)cpu + TESTOS_GPIO_PASS_FAIL_PORT),
			  true);
}
#endif

static inline int testos_init_early(void)
{
	if (ate_setup.magic == TESTOS_SETUP_MAGIC) {
		set_cpu_mask(ate_setup.apc_mask);
		set_llc_mask(ate_setup.cbf_mask);
	} else
		testos_init_default();

	testos_config_phase_flags();
	return 0;
}

cpu_completion testos_completion = NULL;

void testos_apc_indicate_result(int result)
{
	if (result == 0)
		testos_indicate_pass(smp_processor_id());
	else
		testos_indicate_fail(smp_processor_id());
}

void testos_imc_indicate_result(uint8_t cpu, uint64_t result)
{
	if (result == 0)
		testos_indicate_pass(cpu);
#ifndef CONFIG_TESTOS_STRICT_FAILURE
	else
		testos_indicate_fail(cpu);
#endif
}

void testos_imc_indicate_results(uint64_t *results)
{
	int i;

	for (i = 0; i < MAX_CPU_NUM; i++) {
		if (((uint64_t)1 << i) & (ate_setup.apc_mask))
			testos_imc_indicate_result(i, results[i]);
	}
}

void testos_internal_completion(uint64_t *results)
{
	cpu_completion completion;

	testos_imc_indicate_results(results);
	completion = testos_completion;
	testos_completion = NULL;
	if (completion)
		completion(results);
}

static bool set_cbf_freq(uint32_t freq)
{
	set_llc_freq(freq);
	return clock_config_cbf(freq);
}

static bool set_apc_freq(uint32_t freq)
{
	int i;
	uint64_t apc_mask = get_apc_mask(ate_setup.apc_mask);

	for (i = 0; i < MAX_CPU_CLUSTERS; i++) {
		if (apc_mask & _BV(i)) {
			if (!falkor_is_cluster_clocked(i))
				set_cpu_freq(freq);
			else if (!clock_config_cluster(i, freq))
				return false;
		}
	}
	return true;
}

/* ATE Update Frequency
 *
 * By running another tests via TIC, ATE has chances to tune APC/CBF
 * frequencies. This brings efficiencies to the Vmin/Fmax calibration.
 */
static bool testos_update_freqs(void)
{
	static uint64_t last_apc_freq = 0;
	static uint64_t last_cbf_freq = 0;

	testos_config_phase_flags();
	testos_indicate_phase_flags(smp_processor_id(),
				    TESTOS_PHASE_START);
	if (!last_apc_freq)
		last_apc_freq = ate_setup.apc_freq;
	else if (last_apc_freq != ate_setup.apc_freq) {
		last_apc_freq = ate_setup.apc_freq;
		if (!set_apc_freq(last_apc_freq))
			return false;
	}
	if (!last_cbf_freq)
		last_cbf_freq = ate_setup.cbf_freq;
	else if (last_cbf_freq != ate_setup.cbf_freq) {
		last_cbf_freq = ate_setup.cbf_freq;
		if (!set_cbf_freq(last_cbf_freq))
			return false;
	}
	testos_indicate_phase_flags(smp_processor_id(),
				    TESTOS_PHASE_END);
	testos_config_pass_fail();
	return true;
}

int testos_dispatch_apcs_smp_async(testos_entry_cb entry_point,
                                   cpu_completion completion)
{
	struct cpu_table table;
	int i;
	ktime_t timeout = (ktime_t)ate_setup.timeout;

	if (testos_completion)
		return -EBUSY;
	if (!testos_update_freqs())
		return -EFAULT;
	testos_completion = completion;

	for (i = 0; i < MAX_CPU_NUM; i++) {
		if (((uint64_t)1 << i) & (ate_setup.apc_mask)) {
			table.entries[i] = entry_point;
			testos_indicate_fail(i);
		} else {
			table.entries[i] = NULL;
			testos_indicate_pass(i);
		}
	}
	cpu_remote_boot_async(&table, false, false, timeout,
			      testos_internal_completion);
	return 0;
}

int testos_dispatch_apcs_amp_async(testos_entry_cb *entry_points,
                                   cpu_completion completion)
{
	struct cpu_table table;
	int i;
	ktime_t timeout = (ktime_t)ate_setup.timeout;

	if (testos_completion)
		return -EBUSY;
	if (!testos_update_freqs())
		return -EFAULT;
	testos_completion = completion;

	for (i = 0; i < MAX_CPU_NUM; i++) {
		if (((uint64_t)1 << i) & (ate_setup.apc_mask)) {
			table.entries[i] = entry_points[i];
			testos_indicate_fail(i);
		} else {
			table.entries[i] = NULL;
			testos_indicate_pass(i);
		}
	}
	cpu_remote_boot_async(&table, false, false, timeout,
			      testos_internal_completion);
	return 0;
}

int testos_dispatch_apcs_smp(testos_entry_cb entry_point)
{
	struct cpu_table table;
	int i;

	if (!testos_update_freqs())
		return -EFAULT;
	for (i = 0; i < MAX_CPU_NUM; i++) {
		if (((uint64_t)1 << i) & (ate_setup.apc_mask)) {
			table.entries[i] = entry_point;
			testos_indicate_fail(i);
		} else {
			table.entries[i] = NULL;
			testos_indicate_pass(i);
		}
	}
	cpu_remote_boot(&table, false, false, TESTOS_INFINITE, NULL);
	return 0;
}

int testos_dispatch_apcs_amp(testos_entry_cb *entry_points)
{
	struct cpu_table table;
	int i;

	if (!testos_update_freqs())
		return -EFAULT;
	for (i = 0; i < MAX_CPU_NUM; i++) {
		if (((uint64_t)1 << i) & (ate_setup.apc_mask)) {
			table.entries[i] = entry_points[i];
			testos_indicate_fail(i);
		} else {
			table.entries[i] = NULL;
			testos_indicate_pass(i);
		}
	}
	cpu_remote_boot(&table, false, false, TESTOS_INFINITE, NULL);
	return 0;
}

void testos_setup_apcs(uint64_t apc_mask)
{
	ate_setup.apc_mask = apc_mask;
}

void testos_setup_cbf(uint64_t cbf_mask)
{
	ate_setup.cbf_mask = cbf_mask;
}

void testos_setup_timeout(uint64_t timeout)
{
	ate_setup.timeout = timeout;
}

static void __testos_notify(bool result)
{
	uint8_t cpu = smp_processor_id();

	if (result)
		testos_indicate_pass(cpu);
	else
		testos_indicate_fail(cpu);
}

int testos_dispatch_apcs_didt(testos_auto_testfn *fn, ktime_t period,
			      ktime_t interval, int repeats)
{
	return cpu_local_didt(ate_setup.apc_mask, fn,
			      interval, period, repeats);
}

int testos_dispatch_apcs_once(testos_auto_testfn *fn, ktime_t period)
{
	return testos_dispatch_apcs_didt(fn, period,
					 CPU_WAIT_INFINITE, 1);
}

int testos_dispatch_apcs_tests(testos_auto_testfn *start,
			       int nr_tests, uint32_t flags,
			       ktime_t timeout)
{
	return cpu_local_exec(start, nr_tests, ate_setup.apc_mask,
			      flags, timeout, __testos_notify);
}

int testos_dispatch_apcs_test(testos_auto_testfn *fn,
			      uint32_t flags, ktime_t timeout)
{
	return testos_dispatch_apcs_tests(fn, 1, flags, timeout);
}

int testos_dispatch_apcs_auto(uint32_t flags, ktime_t timeout)
{
	int nr_tests = ((uintptr_t)__testfn_end - (uintptr_t)__testfn_start) /
		       sizeof (testos_auto_testfn);

	return testos_dispatch_apcs_tests(__testfn_start, nr_tests,
					  flags, timeout);
}

testos_auto_testfn *testos_get_auto_test(const char *name)
{
	return cpu_exec_find(name);
}

#ifdef CONFIG_TESTOS_ATE_INIT
static int testos_init_late(void)
{
	while (1);
	return 0;
}
#else
static int testos_init_late(void)
{
	int i;

	testos_config_pass_fail();
	for (i = 0; i < MAX_CPU_NUM; i++) {
		if (((uint64_t)1 << i) & (ate_setup.apc_mask))
			testos_indicate_fail(i);
		else
			testos_indicate_pass(i);
	}
	return 0;
}
#endif

void entry(void)
{
	testos_init_early();
	testos_indicate_phase_flags(smp_processor_id(),
				    TESTOS_PHASE_START);

	dsr_init();
	tick_init();
	/* Must be done before enabling MMU */
	irq_init();
	timer_init();
	perf_init();
	testos_indicate_phase_flags(smp_processor_id(),
				    TESTOS_PHASE_TIMER);

	arch_early_init();
	console_early_init();
	printf("\nWelcome to TestOS - core entry.\n");
	testos_indicate_phase_flags(smp_processor_id(),
				    TESTOS_PHASE_EARLY);

	mmu_init();
	testos_indicate_phase_flags(smp_processor_id(),
				    TESTOS_PHASE_MMU);

	console_late_init();
	power_init();
	arch_late_init(ate_setup.apc_freq, ate_setup.cbf_freq);
	testos_indicate_phase_flags(smp_processor_id(),
				    TESTOS_PHASE_LATE);

	cpu_remote_init();
	testos_indicate_phase_flags(smp_processor_id(),
				    TESTOS_PHASE_END);

	testos_init_late();
	testos_main();
	dsr_loop();
}

void secondary_entry(void)
{
	printf("%d UP\n", testos_get_apc_id());
	dsr_init();
	tick_init();
	irq_init();
	timer_init();
	perf_init();
	mmu_init();
	percpu_init();
	cpu_local_init();
	dsr_loop();
}
