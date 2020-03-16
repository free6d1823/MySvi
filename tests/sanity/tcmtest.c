#include <stdio.h>
#include <target/cpus.h>
#include <target/memory.h>
#include <target/smp.h>

uint64_t *sanity_tcm_start(caddr_t percpu_area)
{
	uint64_t possible_safe_tcm_start = (uint64_t)percpu_area;

	if (possible_safe_tcm_start > TCM_START &&
	    possible_safe_tcm_start <= TCM_END)
		return (uint64_t *)ALIGN_UP(possible_safe_tcm_start, 8);
	return (uint64_t *)TCM_START;
}

static int sanity_tcm64(caddr_t percpu_area)
{
	uint64_t *p;
	uint64_t i;

	i = 0;
	p = (uint64_t *)sanity_tcm_start(percpu_area);
	while ((uint64_t)p < TCM_END)
		*p++ = i++;
	printf("tcm64 success write on %d\n", smp_processor_id());

	i = 0;
	p = (uint64_t *)sanity_tcm_start(percpu_area);
	while ((uint64_t)p < TCM_END) {
		if (*p++ != i++) {
			printf("tcm64 failure %p(%d) on %d\n",
			       p, i, smp_processor_id());
			return 0;
		}
	}
	printf("tcm64 success read on %d\n", smp_processor_id());
	return 1;
}

static int sanity_tcm32(caddr_t percpu_area)
{
	uint32_t *p;
	uint32_t i;

	i = 0;
	p = (uint32_t *)sanity_tcm_start(percpu_area);
	while ((uint64_t)p < TCM_END)
		*p++ = i++;
	printf("tcm32 success write on %d\n", smp_processor_id());

	i = 0;
	p = (uint32_t *)sanity_tcm_start(percpu_area);
	while ((uint64_t)p < TCM_END) {
		if (*p++ != i++) {
			printf("tcm32 failure %p(%d) on %d\n",
			       p, i, smp_processor_id());
			return 0;
		}
	}
	printf("tcm32 success read on %d\n", smp_processor_id());
	return 1;
}

static int sanity_tcm16(caddr_t percpu_area)
{
	uint16_t *p;
	uint16_t i;

	i = 0;
	p = (uint16_t *)sanity_tcm_start(percpu_area);
	while ((uint64_t)p < TCM_END)
		*p++ = i++;
	printf("tcm16 success write on %d\n", smp_processor_id());

	i = 0;
	p = (uint16_t *)sanity_tcm_start(percpu_area);
	while ((uint64_t)p < TCM_END) {
		if (*p++ != i++) {
			printf("tcm16 failure %p(%d) on %d\n",
			       p, i, smp_processor_id());
			return 0;
		}
	}
	printf("tcm16 success read on %d\n", smp_processor_id());
	return 1;
}

static int sanity_tcm8(caddr_t percpu_area)
{
	uint8_t *p;
	uint8_t i;

	i = 0;
	p = (uint8_t *)sanity_tcm_start(percpu_area);
	while ((uint64_t)p < TCM_END)
		*p++ = i++;
	printf("tcm8 success write on %d\n", smp_processor_id());

	i = 0;
	p = (uint8_t *)sanity_tcm_start(percpu_area);
	while ((uint64_t)p < TCM_END) {
		if (*p++ != i++) {
			printf("tcm8 failure %p(%d) on %d\n",
			       p, i, smp_processor_id());
			return 0;
		}
	}
	printf("tcm8 success read on %d\n", smp_processor_id());
	return 1;
}

static int tcmtest(caddr_t percpu_area)
{
	if (!sanity_tcm8(percpu_area))
		return 0;
	if (!sanity_tcm16(percpu_area))
		return 0;
	if (!sanity_tcm32(percpu_area))
		return 0;
	if (!sanity_tcm64(percpu_area))
		return 0;
	return 1;
}
__define_testfn(tcmtest, 8, SMP_CACHE_BYTES,
		CPU_EXEC_SHARE | CPU_EXEC_META, 1, CPU_WAIT_INFINITE);
