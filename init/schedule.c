#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <target/cpus.h>
#include <target/cmdline.h>
#include <target/schedule.h>
#include <target/smp.h>
#include <target/heap.h>

static struct schedule_mailbox mailbox[NR_CPUS];
struct schedule_mailbox* schedule_get_mb(int cpu)
{
	return &mailbox[cpu];
}

void schedule_mailbox_log(const char *format, ...)
{
	va_list arg;

	unsigned int cpu = smp_processor_id();
	struct schedule_mailbox* mb= schedule_get_mb(cpu);

	va_start(arg, format);
	vsnprintf((char*)(mb->log), sizeof(mb->log), format, arg);
	va_end(arg);
}

void schedule_mailbox_check()
{
	int i, flag = 0;

	for (i = 0; i < NR_CPUS; i++) {
		if (mailbox[i].status0 == 1 && mailbox[i].status1 == 1) {
			mailbox[i].status0 = 0;
			mailbox[i].status1 = 0;
			flag = 1;
			printf("[cpu%d] %s", i, mailbox[i].log);
		}
	}

	for (i = 0; i < NR_CPUS; i++) {
		if (mailbox[i].status0 == 1) {
			break;
		}
	}

	if (flag == 1 && i == NR_CPUS) {
		schedule_end_transcation();
	}
}

static struct cpu_exec_test* find_case(int id)
{
	struct cpu_exec_test* test;

	int nr_tests = ((uintptr_t)__testfn_end -
			(uintptr_t)__testfn_start) /
		       sizeof (struct cpu_exec_test);

	if (id < 0 || id > nr_tests) {
		printf("err, id invalid\n");
		return (struct cpu_exec_test*)0;
	}

	return (struct cpu_exec_test*)__testfn_start + id;
}

int exec_case(int id, void *arg)
{
	struct cpu_exec_test* test;

	test = find_case(id);
	if (test == 0) {
		printf("err, id too large\n");
		return -1;
	}

	test->func(arg);

	return  0;
}

static void *_heap;
void schedule_start_transcation()
{
	/* save heap ptr,
	 * will be restored after current dispatch finished
	 */
	_heap = heap_save_current();

	/* clean mailbox */
	for (int i = 0; i < NR_CPUS; i++) {
		mailbox[i].status0 = 0;
		mailbox[i].status1 = 0;
	}
}

void schedule_end_transcation()
{
	heap_restore(_heap);
}

void schedule_notify_taskended()
{
	mailbox[smp_processor_id()].status1 = 1;
	sgi_send(cpus_boot_cpu, IPI_ACK);
}

/*
 * schedule cpumask caseid
 */
int schedule_case(int argc, char *argv[])
{
	void *p;
	int id, i=0;
	uint32_t cpumask;
	struct cpu_exec_test* test;

	if (argc != 3)
		return -1;

	id = strtoul(argv[2], NULL, 0);
	test = find_case(id);
	if (test == 0)
		return -1;

	/* prepare case context */
	schedule_start_transcation();

	cpumask = strtoul(argv[1], NULL, 0);
	printf("     run %s on cpumask 0x%x\n", test->name, cpumask);

	while (cpumask != 0) {
		if (cpumask & 0x1) {
			p = heap_aligned_alloc(test->alloc_align, test->alloc_size);
			mailbox[i].case_id = id;
			mailbox[i].arg = p;
			mailbox[i].status0 = 1;
			sgi_send(i, IPI_SCHEDULE);
		}

		i++;
		cpumask = cpumask >> 1;
	}

	return 0;
}

int case_list(int argc, char *argv[])
{
	int nr_tests = ((uintptr_t)__testfn_end -
			(uintptr_t)__testfn_start) /
		       sizeof (struct cpu_exec_test);
	struct cpu_exec_test *start = __testfn_start;
	int i;

	printf("     [id]    [name]\n");

	for (i = 0; i < nr_tests; i++) {
		printf("      %d%*s%s\n", i, 6, " ", (start + i)->name);
	}
	return 0;
}

MK_CMD(caselist, case_list, "list available test cases",
	"listcase\n"
);

MK_CMD(schedule, schedule_case, "schedule case to cpu",
	"schedule cpumask caseid\n"
	"	 - cpumask: bit_n present cpu_n\n"
	"	 - caseid: 0,1,2...\n"
);

