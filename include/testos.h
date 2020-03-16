/*
 */
#ifndef __TESTOS_H
#define __TESTOS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <target/cpus.h>
#include <target/gpio.h>
#include <target/memory.h>
#include <target/barrier.h>
#include <target/spinlock.h>
#include <target/cache.h>
#include <target/percpu.h>
#include <target/smp.h>

#define TESTOS_INFINITE		CPU_WAIT_INFINITE
#define TESTOS_TESTFN_SYNC	CPU_EXEC_SYNC
#define TESTOS_TESTFN_RAND	CPU_EXEC_RAND
#define TESTOS_ENDLESS		-1ULL

/* Investigated result, after muting all APC side console outputs, IMC
 * sync mechanism still needs to wait additional 500us before seeing all
 * APC patterns end.
 */
#define TESTOS_IMC_WAIT_OVERHEAD	500
#define TESTOS_BENCH_TIMEOUT	(1 * 1000 * 1000)
#define TESTOS_BENCH_REPEATS	2

#define TESTOS_SETUP_MAGIC	0x00544553544F5300

/* GPIO pass/fail flagging */
#define TESTOS_GPIO_PASS_FAIL_PORT		52
#define TESTOS_GPIO_PASS_FAIL_BITS		MAX_CPU_NUM

/* GPIO phase flagging */
#define TESTOS_GPIO_PHASE_MSG1_PORT		65
#define TESTOS_GPIO_PHASE_MSG1_BITS		14
#define TESTOS_GPIO_PHASE_MSG2_PORT		80
#define TESTOS_GPIO_PHASE_MSG2_BITS		2
#define TESTOS_GPIO_PHASE_MSG_BITS		\
	(TESTOS_GPIO_PHASE_MSG1_BITS +		\
	 TESTOS_GPIO_PHASE_MSG2_BITS)
#define TESTOS_GPIO_PHASE_CPU_PORT		82
#define TESTOS_GPIO_PHASE_CPU_BITS		6
#define TESTOS_GPIO_PHASE_CPU_SHIFT		TESTOS_GPIO_PHASE_MSG_BITS
#define TESTOS_GPIO_PHASE_UNUSED_PORT		91
#define TESTOS_GPIO_PHASE_UNUSED_BITS		9
#define TESTOS_GPIO_PHASE_VALID_PORT		100
#define TESTOS_GPIO_PHASE_VALID_SHIFT		\
	(TESTOS_GPIO_PHASE_MSG_BITS + 		\
	 TESTOS_GPIO_PHASE_CPU_BITS +		\
	 TESTOS_GPIO_PHASE_UNUSED_BITS)

#define TESTOS_PHASE_START	0
#define TESTOS_PHASE_TIMER	1
#define TESTOS_PHASE_EARLY	2
#define TESTOS_PHASE_MMU	3
#define TESTOS_PHASE_LATE	4
#define TESTOS_PHASE_END	5
#define TESTOS_PHASE_ARCH	6

#ifndef __ASSEMBLY__
/* Used as software register to allow ATE to configure test environment */
struct testos_setup {
	uint64_t magic;
	uint64_t timeout;
	uint64_t apc_mask;
	uint64_t apc_freq;
	uint64_t cbf_mask;
	uint64_t cbf_freq;
	uint64_t repeats;
	uint64_t test_entry;
};

typedef int (*testos_entry_cb)(void);

#define TESTOS_GPIO_PASS_FAIL_CFG		\
	GPIO_ENCODE_CONFIG(0, GPIO_DIR_OUTPUT,	\
			   GPIO_PULL_DOWN,	\
			   GPIO_DRIVE_MA(2))

#define testos_get_apc_id()	smp_processor_id()

int testos_main(void);

/* Auto APC test framework:
 * testos_dispatch_apcs_tests: Runs a bunch of tests on APCs. This
 *                             function should be invoked on the APCs.
 * testos_dispatch_apcs_test:  Runs a single tests on APCs.
 * testos_dispatch_apcs_auto:  Automatically runs collected tests in the
 *                             .testfn section.
 * Use TESTOS_INFINITE/TESTOS_TESTFN_SYNC/TESTOS_TESTFN_RAND instead of
 * CPU_XXX macros.
 */
typedef struct cpu_exec_test testos_auto_testfn;

testos_auto_testfn *testos_get_auto_test(const char *name);
int testos_dispatch_apcs_tests(testos_auto_testfn *start,
			       int nr_tests, uint32_t flags,
			       ktime_t timeout);
int testos_dispatch_apcs_test(testos_auto_testfn *fn,
			      uint32_t flags, ktime_t timeout);
int testos_dispatch_apcs_auto(uint32_t flags, ktime_t timeout);
int testos_dispatch_apcs_didt(testos_auto_testfn *fn, ktime_t period,
			      ktime_t interval, int repeats);
int testos_dispatch_apcs_once(testos_auto_testfn *fn, ktime_t period);

int testos_dispatch_apcs_smp(testos_entry_cb entry_point);
int testos_dispatch_apcs_amp(testos_entry_cb *entry_points);
int testos_dispatch_apcs_smp_async(testos_entry_cb entry_point,
                                   cpu_completion completion);
int testos_dispatch_apcs_amp_async(testos_entry_cb *entry_points,
                                   cpu_completion completion);
int testos_boot_apcs(void);
void testos_indicate_pass(uint8_t cpu);
void testos_indicate_fail(uint8_t cpu);
void testos_indicate_phase_flags(uint8_t cpu, uint16_t msg);
void testos_apc_indicate_result(int result);
void testos_imc_indicate_result(uint8_t cpu, uint64_t result);
void testos_imc_indicate_results(uint64_t *results);

/* Only used for inter-connect patterns, might disappear if we moved the
 * test logic to ATE.
 */
void testos_setup_apcs(uint64_t apc_mask);
void testos_setup_cbf(uint64_t cbf_mask);
void testos_setup_timeout(uint64_t timeout);
uint64_t testos_get_apc_pg(void);
uint64_t testos_get_cbf_pg(void);

extern struct testos_setup ate_setup;

#endif /* __ASSEMBLY__ */

#endif /* __TESTOS_H */
