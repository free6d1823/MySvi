#include <stdio.h>
#include <target/smp.h>
#include <target/percpu.h>
#include <target/cpus.h>

#define get_percpu_addr(var)			\
	(uint64_t)(RELOC_HIDE(&percpu_##var,	\
	percpu_offset(smp_processor_id())))

extern uint64_t asmpercpu_get_percpu_addr(void);
extern uint16_t asmpercpu_smp_processor_id(void);

#define ASMPERCPU_SIZE	1

typedef uint8_t asmpercpu_t[ASMPERCPU_SIZE];
DEFINE_PERCPU(asmpercpu_t, asmpercpu_sym);

static int asmpercpu(caddr_t percpu_area)
{
	uint8_t *p;
	uint8_t i;

	if (smp_processor_id() != asmpercpu_smp_processor_id())
		return 0;
	p = (uint8_t *)get_percpu_addr(asmpercpu_sym);
	if ((uint64_t)p != asmpercpu_get_percpu_addr())
		return 0;

	for (i = 0; i < ASMPERCPU_SIZE; i++)
		p[i] = i;
	for (i = 0; i < ASMPERCPU_SIZE; i++) {
		if (p[i] != i) {
			printf("percpu failure %p on %d\n",
			       p, smp_processor_id());
			return 0;
		}
	}
	printf("percpu success %p on %d\n", p, smp_processor_id());
	return 1;
}
__define_testfn(asmpercpu, 1, 1,
		CPU_EXEC_META, 1, CPU_WAIT_INFINITE);
