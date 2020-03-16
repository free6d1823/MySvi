/*
 */
#ifndef __ARM64_PERF_H_INCLUDE__
#define __ARM64_PERF_H_INCLUDE__

#include <asm/pmu.h>

#define PERF_HW_MAX_COUNTERS		31
#define PERF_HW_DEFAULT_EVENT		ARMV8_PMUV3_SW_INCR

#define perf_hw_ctrl_init()		pmu_init()
#define perf_hw_reset_events()		pmu_reset_events()
#define perf_hw_get_counters()		pmu_get_counters()
#define perf_hw_enable_event(event)	pmu_enable_event(event)
#define perf_hw_disable_event(event)	pmu_disable_event(event)
#define perf_hw_configure_event(event)	pmu_configure_event(event)
#define perf_hw_get_event_count(event)	pmu_get_event_count(event)

#endif /* __ARM64_PERF_H_INCLUDE__ */
