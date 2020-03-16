#include <testos.h>

#ifndef PATTERN_TIMEOUT
#define PATTERN_TIMEOUT		TESTOS_INFINITE
#endif

static uint64_t pattern_cpus = 0;
static uint64_t pattern_llcs = 0;
static testos_auto_testfn *pattern_test = NULL;

static int pattern_main(void)
{
	uint8_t cpu = smp_processor_id();
	int ret;

	ret = testos_dispatch_apcs_once(pattern_test, PATTERN_TIMEOUT);
	testos_apc_indicate_result(ret);
	return ret;
}

static void pattern_result(uint64_t *results)
{
	int id;

	if (!results)
		return;

	for (id = 0; id < MAX_CPU_NUM; id++) {
		if (pattern_cpus & C(id)) {
			printf("%d result: %s(%lld)\n", id,
			       results[id] == 0 ? "success" : "failure",
			       results[id]);
		}
	}
	printf("End at %llu\n", time_get_current_time());
}

int testos_main(void)
{
	printf("Welcome to TestOS - test(%s) entry.\n", PATTERN_NAME);
#ifdef PATTERN_SINGLE
	testos_setup_apcs(C(0));
	pattern_cpus = C(0);
#else
	pattern_cpus = testos_get_apc_pg();
#endif
	pattern_llcs = testos_get_cbf_pg();
	pattern_test = testos_get_auto_test(PATTERN_NAME);
	testos_dispatch_apcs_smp_async(pattern_main, pattern_result);
	return 0;
}
