#include <testos.h>

#define GLOBAL_LOCK_TEST_TIMEOUT	(5 * 1000)

tid_t global_lock_test_timer;
static uint64_t global_lock_llcs = 0;
static uint64_t global_lock_cpus = 0;

static void global_lock_timer_reset(void)
{
	timer_set(global_lock_test_timer,
		  GLOBAL_LOCK_TEST_TIMEOUT, true);
}

static void global_lock_timer_handler(void)
{
	printf("I'm on IMC timer\n");
	global_lock_timer_reset();
}

static int global_lock_test(void)
{
	printf("I'm on APC %d\n", smp_processor_id());
	return 0;
}

static void global_lock_result(uint64_t *results)
{
	testos_dispatch_apcs_smp_async(global_lock_test,
				       global_lock_result);
	printf("I'm on IMC compl\n");
}

int testos_main(void)
{
	printf("Welcome to TestOS - test entry.\n");

	global_lock_cpus = testos_get_apc_pg();
	global_lock_llcs = testos_get_cbf_pg();
	testos_dispatch_apcs_smp_async(global_lock_test,
				       global_lock_result);
	testos_setup_timeout(TESTOS_INFINITE);
	global_lock_test_timer = timer_register(TIMER_DSR,
						global_lock_timer_handler);
	global_lock_timer_reset();
	return 0;
}
