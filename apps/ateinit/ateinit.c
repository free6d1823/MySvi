#include <testos.h>
#include <target/timer.h>
#include <target/dsr.h>

#ifdef CONFIG_TEST_TIMEOUT
#define ATE_TIMEOUT		CONFIG_TEST_TIMEOUT
#else
#define ATE_TIMEOUT		TESTOS_INFINITE
#endif

static int ate_test_good(void)
{
	int id = testos_get_apc_id();

	printf("ATE %d\n", id);
	return 0;
}

static int ate_test_bad(void)
{
	int id = testos_get_apc_id();

	printf("ATE %d\n", id);
	if (id % 3 == 0)
		return 0;
	if (id % 3 == 1)
		return -EFAULT;
	while (1);
	return -ETIME;
}

static uint64_t ate_cpus;
static uint64_t ate_llcs;
static bool ate_running;

void ate_test_step(uint64_t *results)
{
	int id;

	if (!results)
		return;

	for (id = 0; id < MAX_CPU_NUM; id++) {
		if (ate_cpus & C(id)) {
			printf("%d result: %s(%d)\n", id,
			       results[id] == 0 ? "success" : "failure",
			       results[id]);
			if (results[id] != 0)
				ate_running = false;
		}
	}
	printf("End at %llu\n", time_get_current_time());
}

static int ate_dsr;

static void ate_dsr_handler(void* ctx)
{
	testos_entry_cb entry;

	if (ate_running) {
		if (ate_setup.test_entry) {
			entry = (testos_entry_cb)ate_setup.test_entry;
			ate_setup.test_entry = (uint64_t)NULL;
			testos_setup_apcs(ate_cpus);
			testos_dispatch_apcs_smp_async(entry,
						       ate_test_step);
		}
		/* Waiting for aother test entry -
		 * ATE is not idle capable
		 */
		dsr_schedule(ate_dsr);
	}
}

int testos_main(void)
{
	printf("Welcome to TestOS - test entry.\n");
	ate_cpus = testos_get_apc_pg();
	ate_llcs = testos_get_cbf_pg();
	testos_setup_timeout(ATE_TIMEOUT);

	ate_setup.test_entry = (uint64_t)ate_test_bad;
	ate_setup.test_entry = (uint64_t)ate_test_good;
	ate_dsr = dsr_register(ate_dsr_handler, NULL);
	ate_running = true;
	dsr_schedule(ate_dsr);
	return 0;
}
