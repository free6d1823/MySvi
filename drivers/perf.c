/*
 */
#include <target/perf.h>
#include <target/smp.h>

struct perf_event {
	perf_evt_t hw_event_id;
	perf_cnt_t hw_counter;
};

struct perf_desc {
	struct perf_event events[NR_PERF_EVTS];
	perf_evt_t max_counters;
	perf_evt_t next_event;
} __cache_aligned;

struct perf_desc perf_descs[NR_CPUS];

int perf_event_id(perf_evt_t event)
{
	uint8_t cpu = hmp_processor_id();
	int evt;

	for (evt = 0; evt < perf_descs[cpu].next_event; evt++) {
		if (perf_descs[cpu].events[evt].hw_event_id == event)
			return evt;
	}
	return INVALID_PERF_EVT;
}

void perf_unregister_all_events(void)
{
	uint8_t cpu = hmp_processor_id();
	perf_evt_t event;
	int evt;

	for (evt = 0; evt < perf_descs[cpu].next_event; evt++) {
		event = perf_descs[cpu].events[evt].hw_event_id;
		perf_hw_disable_event(event);
		perf_hw_configure_event(PERF_HW_DEFAULT_EVENT);
		perf_descs[cpu].events[evt].hw_event_id = INVALID_PERF_EVT;
		perf_descs[cpu].events[evt].hw_counter = 0;
	}
}

int perf_register_event(perf_evt_t event)
{
	uint8_t cpu = hmp_processor_id();
	int evt;

	if (perf_descs[cpu].next_event >= perf_descs[cpu].max_counters)
		return INVALID_PERF_EVT;

	evt = perf_descs[cpu].next_event;
	perf_descs[cpu].events[evt].hw_event_id = event;
	perf_descs[cpu].next_event++;
	perf_hw_configure_event(event);
	perf_hw_enable_event(event);
	return evt;
}

int perf_init(void)
{
	uint8_t cpu = hmp_processor_id();

	if (cpu >= MAX_CPU_NUM || cpu == cpus_boot_cpu) {
		perf_unregister_all_events();
		perf_hw_ctrl_init();
	}
	perf_descs[cpu].max_counters = perf_hw_get_counters();
	return 0;
}
