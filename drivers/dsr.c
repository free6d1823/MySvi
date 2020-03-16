/*
 */
#include <target/dsr.h>
#include <target/irq.h>
#include <target/percpu.h>
#include <target/smp.h>
#include <target/console.h>

typedef struct dsr dsr_table[MAX_DSRS];

struct dsr_desc {
	dsr_table entries;
	int next_dsr;
} __cache_aligned;

struct dsr_desc dsr_descs[NR_CPUS];

static void dsr_run(uint8_t cpu, int dsr)
{
	dsr_descs[cpu].entries[dsr].handler();
}

void dsr_schedule(int dsr)
{
	uint8_t cpu = hmp_processor_id();

	dsr_descs[cpu].entries[dsr].scheduled = true;
}

static int dsr_signalled(uint8_t cpu, int last_dsr)
{
	int dsr;

	for (dsr = (last_dsr >= dsr_descs[cpu].next_dsr-1 ?
	     0 : last_dsr+1); dsr < dsr_descs[cpu].next_dsr;
	     dsr++) {
		if (dsr_descs[cpu].entries[dsr].scheduled)
			return dsr;
	}
	return INVALID_DSR;
}

int dsr_register(dsr_handler handler)
{
	uint8_t cpu = hmp_processor_id();
	int dsr;

	dsr = dsr_descs[cpu].next_dsr;
	if (dsr >= MAX_DSRS)
		return -1;

	dsr_descs[cpu].entries[dsr].handler = handler;
	dsr_descs[cpu].entries[dsr].scheduled = false;
	dsr_descs[cpu].next_dsr++;
	return dsr;
}

int dsr_run_once(int dsr)
{
	uint8_t cpu = hmp_processor_id();

	for (;;) {
		dsr = dsr_signalled(cpu, dsr);
		if (dsr != INVALID_DSR)
			break;
		do_idle();
	}

	BUG_ON(!dsr_descs[cpu].entries[dsr].scheduled);
	dsr_descs[cpu].entries[dsr].scheduled = false;

	dsr_run(cpu, dsr);

	return dsr;
}

void dsr_loop(void)
{
	int dsr = INVALID_DSR;

	while (1)
		dsr = dsr_run_once(dsr);
}
