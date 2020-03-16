/*
 */
#ifndef __TESTOS_PERF_H_INCLUDE__
#define __TESTOS_PERF_H_INCLUDE__

#include <errno.h>
#include <stdint.h>
#include <asm/perf.h>

#define NR_PERF_EVTS		PERF_HW_MAX_COUNTERS
#define INVALID_PERF_EVT	NR_PERF_EVTS

#if NR_PERF_COUNTERS < 256
typedef uint8_t perf_evt_t;
#endif
typedef uint64_t perf_cnt_t;

#ifdef CONFIG_PERF
#define perf_event_count(event)	\
	perf_hw_get_event_count(event)

int perf_event_id(perf_evt_t event);
int perf_register_event(perf_evt_t event);
void perf_unregister_all_events(void);
int perf_init(void);
#else
static inline int perf_event_count(perf_evt_t event)
{
	return 0;
}

static inline int perf_event_id(perf_evt_t event)
{
	return -1;
}

static inline int perf_register_event(perf_evt_t event)
{
	return -ENODEV;
}

static inline void perf_unregister_all_events(void)
{
}

static inline int perf_init(void)
{
	return 0;
}
#endif

#endif /* __TESTOS_PERF_H_INCLUDE__ */
