#include <stdio.h>
#include <time.h>
#include <target/smp.h>
#include <target/bench.h>
#include "atomic_ll_sc.h"
#include "atomic_lse.h"

#define ADD_LOOP 10000000

typedef void (*atomic_add_impl)(int i, atomic_t *v);

atomic_t sum = ATOMIC_INIT(0);
atomic_t finished = ATOMIC_INIT(0);

uint32_t raw_sum = 0;

int raw_add_test(void *p)
{
	int i;
	uint64_t duration;
	apc_task_t *ctx = (apc_task_t*)p;

	duration = utime();
	printf("CPU[%d] raw_add_test b\n", smp_processor_id());

	for (i=0; i<ADD_LOOP; i++) {
		raw_sum++;
	}

	duration = utime()-duration;
	printf("CPU[%d] raw_add_test e - [%llu]\n", smp_processor_id(), duration);

	__ll_sc_atomic_add(1, &finished);

	if (atomic_read(&finished) == ctx->cpus) {
		printf("CPU[%d] raw_add_test return: %u\n", smp_processor_id(), raw_sum);

		/* clear the global var */
		raw_sum = 0;
		atomic_set(&finished, 0);
	}

	return 0;
}

int atomic_add_test(void *p, atomic_add_impl f)
{
	int i;
	uint64_t duration;
	apc_task_t *ctx = (apc_task_t*)p;

	duration = utime();
	printf("CPU[%d] raw_add_test b\n", smp_processor_id());

	for (i=0; i<ADD_LOOP; i++) {
		f(1, &sum);
	}

	duration = utime()-duration;
	printf("CPU[%d] raw_add_test e - [%llu] \n", smp_processor_id(), duration);

	f(1, &finished);

	if (atomic_read(&finished) == ctx->cpus) {
		printf("CPU[%d] atomic_add_test return: %u\n", smp_processor_id(), atomic_read(&sum));

		/* clear the global var */
		atomic_set(&sum, 0);
		atomic_set(&finished, 0);
	}

	return 0;
}

int ll_sc_atomic_add_test(void *ctx)
{
	atomic_add_test(ctx, __ll_sc_atomic_add);
	return 0;
}

int lse_atomic_add_test(void *ctx)
{
#ifdef CONFIG_CPU_v81A
	atomic_add_test(ctx, __lse_atomic_add);
#else
	printf("lse atomic is not supported");
#endif
	return 0;
}

int atomic_test_init()
{
	pattern_vf_register("rawadd",  raw_add_test, 2);
	pattern_vf_register("llscadd", ll_sc_atomic_add_test, 2);
	pattern_vf_register("lseadd",  lse_atomic_add_test, 2);
    return 0;
}
