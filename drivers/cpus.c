/*
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <target/exception.h>
#include <target/cpus.h>
#include <target/cache.h>
#include <target/barrier.h>
#include <target/dsr.h>
#include <target/delay.h>
#include <target/memory.h>
#include <target/mmu.h>
#include <target/arch.h>
#include <target/smp.h>
#include <target/spinlock.h>
#include <target/cmdline.h>
#include <target/percpu.h>
#include <target/timer.h>
#include <target/irq.h>
#include <target/bitops.h>
#include <target/heap.h>

#define CPU_OFF         0
#define CPU_ON          1
#define CPU_RUN         2

/* CPU control states */
#define CPU_STATE_NONE		0
#define CPU_STATE_WAIT_IDLE	1
#define CPU_STATE_WAIT_BUSY	2
#define CPU_STATE_HALT		3
#define CPU_STATE_WAIT_ARCH	4
#define CPU_STATE_DIDT		5

/* CPU control events */
#define CPU_EVENT_START		(1<<0)
#define CPU_EVENT_TIME		(1<<1)
#define CPU_EVENT_SYNC		(1<<2)
#define CPU_EVENT_POLL		(1<<3)
#define CPU_EVENT_STOP		(1<<4)

typedef unsigned char boolean;
typedef unsigned char uint8;
#ifndef TRUE
#define FALSE			((boolean)(1 == 0))
#define TRUE			(!FALSE)
#endif


#define smp_flush_cache(addr)	flush_dcache_addr(addr)
#define smp_inval_cache(addr)	inval_dcache_addr(addr)


#define dcache_write(addr, value)	\
	do {				\
		*addr = value;		\
		smp_flush_cache(addr);	\
		smp_wmb();		\
	} while (0)
#define dcache_read(addr)		\
	({				\
		typeof(*addr) __rc;	\
		smp_rmb();		\
		smp_inval_cache(addr);	\
		__rc = *addr;		\
		__rc;			\
	})
#define barrier_write(addr, value)	\
	do {				\
		*addr = value;		\
		smp_wmb();		\
	} while (0)
#define barrier_read(addr)		\
	({				\
		typeof(*addr) __rc;	\
		smp_rmb();		\
		__rc = *addr;		\
		__rc;			\
	})
#define dcache_wait(addr, value)			\
	do {						\
		while (dcache_read(addr) != value)	\
			cpu_relax();			\
	} while (0)

#define cpu_busy_read(id)				\
	dcache_read(&cpu_busy[id])
#define cpu_busy_write(id, value)			\
	dcache_write(&cpu_busy[id], value)
#define cpu_busy_wait(id, value)			\
	do {						\
		while (cpu_busy_read(id) != value)	\
			cpu_relax();			\
	} while (0)
#define cpu_result_write(id, result)			\
	dcache_write(&cpu_results[id], (uint64_t)(result));

#define __printf
#ifdef CONFIG_TEST_VERBOSE
#define do_printf	printf
#else
#define do_printf	__printf
#endif

struct cpu_context {
	uint8_t async_state;
	uint8_t async_event;
	ktime_t async_timeout;
	ktime_t async_exec_period;
	ktime_t async_wait_interval;
	struct cpu_exec_test *didt_entry;
	int didt_result;
	int didt_repeats;
	tid_t timer;
	int dsr;
} __cache_aligned;

static uint64_t cpu_powered;
static struct cpu_context cpu_ctxs[NR_CPUS];
static bool cpu_do_reset;
static bool cpu_do_poweroff;

uint64_t cpu_results[MAX_CPU_NUM] ;	/* W: APCs, R: IMC */
uint64_t cpu_busy[MAX_CPU_NUM] ;	/* W: APCs, R: IMC */
cpu_entry cpu_entries[MAX_CPU_NUM];			/* W: IMC, R: APCs */
uint64_t cpu_states[MAX_CPU_NUM];			/* W: IMC, R: APCs */

/*
 * Variables for testos_cpu_state:
 * closed: all CPUs have no synchronous pattern running on them
 * opened: all CPUs are about to execute the synchronous pattern
 */
#define CPU_EXEC_CLOSED	0
#define CPU_EXEC_OPENED	1

/* The following global variables are not good parallel programming
 * examples, should be tuned to gain maximum performance.
 */
static unsigned long cpu_exec_state;
static uint8_t cpu_exec_refcnt;
static DEFINE_SPINLOCK(cpu_exec_lock);
static uint64_t cpu_exec_sync;
static unsigned long cpu_exec_good;
static int cpu_exec_test_id;
static caddr_t cpu_didt_area;
static uint8_t cpu_didt_refcnt;
static unsigned long cpu_didt_cpu_mask;

static void cpu_remote_dsr_handler(void* ctx);
static void cpu_local_dsr_handler(void* ctx);
static void cpu_remote_timer_handler(void*);
static bool cpu_remote_power_on_async(void);

static cpu_completion cpu_async_completion;

static void cpu_raise_event(uint8_t event)
{
	uint8_t cpu = hmp_processor_id();

	cpu_ctxs[cpu].async_event |= event;
	dsr_schedule(cpu_ctxs[cpu].dsr);
}

static void cpu_reset_timeout(void)
{
	uint8_t cpu = hmp_processor_id();

	timer_set(cpu_ctxs[cpu].timer,
		  cpu_ctxs[cpu].async_timeout, false);
}

static void cpu_remote_start_timer(void)
{
	uint8_t cpu = hmp_processor_id();

	if (cpu_ctxs[cpu].async_wait_interval != CPU_WAIT_INFINITE) {
		ktime_t current_time = time_get_current_time();

		cpu_ctxs[cpu].async_timeout =
			current_time + cpu_ctxs[cpu].async_wait_interval;
		cpu_reset_timeout();
	}
}

static void cpu_remote_enter_state(uint8_t state)
{
	uint8_t cpu = hmp_processor_id();
	cpu_completion completion;

	cpu_ctxs[cpu].async_state = state;
	switch (cpu_ctxs[cpu].async_state) {
	case CPU_STATE_WAIT_BUSY:
	case CPU_STATE_WAIT_IDLE:
		cpu_remote_start_timer();
		cpu_raise_event(CPU_EVENT_POLL);
		break;
	case CPU_STATE_WAIT_ARCH:
		cpu_raise_event(CPU_EVENT_POLL);
		break;
	case CPU_STATE_HALT:
		timer_clear(cpu_ctxs[cpu].timer);
		completion = cpu_async_completion;
		cpu_async_completion = NULL;
		if (completion)
			completion(cpu_results);
		break;
	case CPU_STATE_NONE:
		completion = cpu_async_completion;
		cpu_async_completion = NULL;
		if (completion)
			completion(cpu_results);
		break;
	default:
		break;
	}
}

static bool cpu_remote_async_busy(void)
{
	uint8_t cpu = hmp_processor_id();
	int id;
	uint8_t value;

	if (cpu_ctxs[cpu].async_state == CPU_STATE_WAIT_BUSY)
		value = TRUE;
	else
		value = FALSE;

	for (id = 0; id < MAX_CPU_NUM; id++) {
		if (cpu_entries[id]) {
			if (cpu_busy_read(id) != value)
				return false;
		}
	}
	return true;
}

static bool __cpu_local_poll(uint8_t cpu)
{
	return !!(dcache_read(&cpu_states[cpu]) == CPU_ON);
}

static void __cpu_local_init(uint8_t cpu)
{
	int result;
	cpu_entry entry;

	dcache_wait(&cpu_states[cpu], CPU_ON);
	cpu_busy_write(cpu, TRUE);
	dcache_wait(&cpu_states[cpu], CPU_RUN);

	/* Making sure entries are set before CPU_ON:
	 * Not very useful between control CPU and work CPUs, but anyway
	 * indicates the order.
	 */
	smp_rmb();
	entry = dcache_read(&cpu_entries[cpu]);
	if (entry) {
		result = entry();
		cpu_result_write(cpu, result);
	}

	cpu_busy_write(cpu, FALSE);
	dcache_wait(&cpu_states[cpu], CPU_OFF);
	cpu_raise_event(CPU_EVENT_POLL);
}

void cpu_local_poll(uint8_t cpu)
{
	if (__cpu_local_poll(cpu))
		cpu_raise_event(CPU_EVENT_POLL);
	else
		__cpu_local_init(cpu);
}

static void cpu_local_timer_handler(void* tid)
{
	cpu_raise_event(CPU_EVENT_TIME);
}

static void cpu_local_didt_start(void)
{
	uint8_t cpu = smp_processor_id();
	ktime_t current_s = time_get_current_time();

	cpu_ctxs[cpu].async_timeout =
		ALIGN_UP(current_s + ULL(65536), ULL(65536));
	cpu_reset_timeout();
}

static void cpu_local_didt_stop(void)
{
	bool locked = false;
	void *ptr;

	spin_lock(&cpu_exec_lock);
	cpu_didt_refcnt--;
	if (!cpu_didt_refcnt) {
		locked = true;
		ptr = cpu_didt_area;
		cpu_didt_cpu_mask = 0;
		cpu_didt_area = NULL;
	}
	spin_unlock(&cpu_exec_lock);
	if (locked)
		heap_free(ptr);
}

static void cpu_local_enter_state(uint8_t cpu, uint8_t state)
{
	cpu_ctxs[cpu].async_state = state;
	switch (cpu_ctxs[cpu].async_state) {
	case CPU_STATE_NONE:
		cpu_raise_event(CPU_EVENT_POLL);
		break;
	case CPU_STATE_DIDT:
		cpu_local_didt_start();
		break;
	default:
		break;
	}
}

static caddr_t cpu_get_percpu_area(uint8_t cpu)
{
	if (!cpu_ctxs[cpu].didt_entry)
		return (caddr_t)0;
	return (caddr_t)((uint64_t)cpu_didt_area +
			 (cpu_ctxs[cpu].didt_entry->alloc_size *
			  (hweight64(cpu_didt_cpu_mask) -
			   hweight64(cpu_didt_cpu_mask >> cpu))));
}

static void cpu_local_didt_exec(uint8_t cpu)
{
	struct cpu_exec_test *fn;
	ktime_t end_time;
	bool is_endless;

	if (!cpu_ctxs[cpu].didt_entry) {
		cpu_ctxs[cpu].didt_result = -EEXIST;
		cpu_raise_event(CPU_EVENT_STOP);
		return;
	} else
		fn = cpu_ctxs[cpu].didt_entry;

	end_time = cpu_ctxs[cpu].async_timeout +
		   cpu_ctxs[cpu].async_exec_period;
	is_endless = !!(cpu_ctxs[cpu].async_exec_period ==
			CPU_WAIT_INFINITE);
	while (is_endless ||
	       time_before(time_get_current_time(), end_time)) {
		do_printf("%02d(%020lld): %s count down %d before %020lld\n",
		       cpu, time_get_current_time(), fn->name, cpu_ctxs[cpu].didt_repeats, end_time);
		if (!fn->func(cpu_get_percpu_area(cpu))) {
			cpu_ctxs[cpu].didt_result = -EFAULT;
			cpu_raise_event(CPU_EVENT_STOP);
			break;
		}
	}
	cpu_ctxs[cpu].didt_repeats--;
	if (cpu_ctxs[cpu].didt_repeats &&
	    cpu_ctxs[cpu].async_wait_interval != CPU_WAIT_INFINITE) {
		cpu_ctxs[cpu].async_timeout +=
			cpu_ctxs[cpu].async_wait_interval;
		ktime_t current_time = time_get_current_time();
		if (time_before(current_time, cpu_ctxs[cpu].async_timeout)) {
			/* Effectively avoid dIdT mode */
			cpu_ctxs[cpu].async_timeout = current_time;
			cpu_raise_event(CPU_EVENT_TIME);
		} else
			cpu_reset_timeout();
	} else
		cpu_raise_event(CPU_EVENT_STOP);
}

static void cpu_local_dsr_handler(void* ctx)
{
	uint8_t cpu = hmp_processor_id();
	uint8_t event = cpu_ctxs[cpu].async_event;

	cpu_ctxs[cpu].async_event = 0;
	switch (cpu_ctxs[cpu].async_state) {
	case CPU_STATE_NONE:
		/* FIXME: Idle Power Efficiency
		 *
		 * We should use IRQs raised by the remote controlling CPU
		 * (for example, GPIO IRQs) to eliminate this busy polling
		 * in order to be more idle power efficient.
		 */
		if (event & CPU_EVENT_POLL)
			cpu_local_poll(cpu);
		if (event & CPU_EVENT_START)
			cpu_local_enter_state(cpu, CPU_STATE_DIDT);
		break;
	case CPU_STATE_DIDT:
		if (event & CPU_EVENT_TIME)
			cpu_local_didt_exec(cpu);
		if (event & CPU_EVENT_STOP) {
			cpu_local_didt_stop();
			cpu_local_enter_state(cpu, CPU_STATE_NONE);
		}
		break;
	default:
		break;
	}
}

int cpu_local_init(void)
{
	uint8_t cpu = smp_processor_id();

	cpu_ctxs[cpu].dsr = dsr_register(cpu_local_dsr_handler, NULL);
	cpu_ctxs[cpu].timer = timer_register(TIMER_DSR,
					     cpu_local_timer_handler);
	register_exception_handler(0);
	__cpu_local_init(cpu);
	return 0;
}

static void cpu_remote_close(void)
{
	int id;

	for (id = 0; id < MAX_CPU_NUM; id ++)
		dcache_write(&cpu_states[id], CPU_OFF);
}

uint64_t _get_cpu_mask(void)
{
	return 0;
}

static bool cpu_remote_config(struct cpu_table *table,
                              bool do_reset, bool do_poweroff)
{
	int id;
	uint8_t cpus = 0;

	/* Making sure entries are set before CPU_ON:
	 * Not very useful between control CPU and work CPUs, but anyway
	 * indicates the order.
	 */
	for (id = 0; id < MAX_CPU_NUM; id++) {
		if (table->entries[id] && (_get_cpu_mask() & C(id))) {
			dcache_write(&cpu_entries[id], table->entries[id]);
			cpu_results[id] = -ETIME;
			cpus++;
		} else {
			dcache_write(&cpu_entries[id], NULL);
			cpu_results[id] = 0;
		}
	}
	if (cpus) {
		cpu_do_reset = do_reset;
		cpu_do_poweroff = do_poweroff;
	}
	smp_wmb();
	return !!(cpus > 0);
}

#if 0
static void cpu_remote_power_off(void)
{
	int id;

	for (id = 0; id < MAX_CPU_NUM; id ++) {
		if (cpu_powered & C(id)) {
			falkor_power_off_core(id);
			cpu_powered &= ~C(id);
		}
		dcache_write(&cpu_states[id], CPU_OFF);
	}
	for (id = 0; id < MAX_CPU_NUM; id ++) {
		if (!(cpu_powered & C(id)))
			dcache_write(&cpu_busy[id], FALSE);
	}
}
#endif

static bool cpu_remote_power_cycle(bool sync)
{
	int id;

	for (id = 0; id < MAX_CPU_NUM; id ++) {
		if (cpu_do_reset ||
		    (cpu_do_poweroff && (cpu_powered & C(id)))) {
			//falkor_power_off_core(id);
			cpu_powered &= ~C(id);
		}
	}

	/* udelay(2 * 1000 * 1000); */

	cpus_config_entry_point(CPU_POWER_ON_ENTRY_POINT);
	/* TODO: WAIT INTO C5 read register */
	if (sync) {
		while (!cpu_remote_power_on_async());
		return true;
	}
	return cpu_remote_power_on_async();
}

static void cpu_remote_open(void)
{
	int id;

	for (id = 0; id < MAX_CPU_NUM; id ++) {
		if (cpu_states[id] == CPU_ON)
			dcache_write(&cpu_states[id], CPU_RUN);
	}
}

void cpu_remote_boot(struct cpu_table *table,
                     bool do_reset, bool do_poweroff,
		     ktime_t timeout, cpu_completion completion)
{
	uint8_t cpu = hmp_processor_id();
	int dsr = INVALID_DSR;

	cpu_remote_boot_async(table, do_reset, do_poweroff,
			      timeout, completion);

	while (cpu_ctxs[cpu].async_event ||
	       (cpu_ctxs[cpu].async_state != CPU_STATE_NONE &&
		cpu_ctxs[cpu].async_state != CPU_STATE_HALT)) {
		irq_local_enable();
		dsr = dsr_run_once(dsr);
		irq_local_disable();
	}
}

int cpu_remote_boot_async(struct cpu_table *table,
                          bool do_reset, bool do_poweroff,
                          ktime_t timeout, cpu_completion completion)
{
	uint8_t cpu = hmp_processor_id();

	if (cpu_async_completion ||
	    cpu_ctxs[cpu].async_state != CPU_STATE_NONE)
		return -EBUSY;

	if (cpu_remote_config(table, do_reset, do_poweroff)) {
		cpu_ctxs[cpu].async_wait_interval = timeout;
		cpu_async_completion = completion;
		cpu_raise_event(CPU_EVENT_START);
		return 0;
	}
	return -ENODEV;
}

int cpu_get_remote_result(int cpu_id)
{
	return (int)cpu_results[cpu_id];
}

static void cpu_remote_poll(void)
{
	if (cpu_remote_async_busy())
		cpu_raise_event(CPU_EVENT_SYNC);
	else
		cpu_raise_event(CPU_EVENT_POLL);
}

static bool cpu_remote_power_on_async(void)
{
	int id;
	bool completed = true;

	for (id = 0; id < MAX_CPU_NUM; id++) {
		if (cpu_entries[id]) {
			if (!(cpu_powered & C(id))) {
				if (cpus_deassert_reset_async(id))
					cpu_powered |= C(id);
				else
					completed = false;
			}
			dcache_write(&cpu_states[id], CPU_ON);
		}
	}
	return completed;
}

static void cpu_arch_poll(void)
{
	if (cpu_remote_power_on_async())
		cpu_raise_event(CPU_EVENT_SYNC);
	else
		cpu_raise_event(CPU_EVENT_POLL);
}

static void cpu_remote_timer_handler(void* tid)
{
	uint8_t cpu = hmp_processor_id();
	ktime_t current_time = time_get_current_time();

	if (cpu_ctxs[cpu].async_timeout == CPU_WAIT_INFINITE ||
	    time_before(current_time, cpu_ctxs[cpu].async_timeout))
		cpu_reset_timeout();
	else
		cpu_raise_event(CPU_EVENT_TIME);
}

static void cpu_remote_dsr_handler(void* ctx)
{
	uint8_t cpu = hmp_processor_id();
	uint8_t event = cpu_ctxs[cpu].async_event;

	cpu_ctxs[cpu].async_event = 0;
	switch (cpu_ctxs[cpu].async_state) {
	case CPU_STATE_NONE:
		if (event & CPU_EVENT_START) {
			cpu_remote_enter_state(CPU_STATE_WAIT_ARCH);
			if (cpu_remote_power_cycle(false))
				cpu_remote_enter_state(CPU_STATE_WAIT_BUSY);
		}
		break;
	case CPU_STATE_WAIT_BUSY:
		if (event & CPU_EVENT_SYNC) {
			cpu_remote_open();
			cpu_remote_enter_state(CPU_STATE_WAIT_IDLE);
		} else if (event & CPU_EVENT_TIME)
			cpu_remote_enter_state(CPU_STATE_HALT);
		else if (event & CPU_EVENT_POLL)
			cpu_remote_poll();
		break;
	case CPU_STATE_WAIT_IDLE:
		if (event & CPU_EVENT_SYNC) {
			cpu_remote_close();
			cpu_remote_enter_state(CPU_STATE_NONE);
		} else if (event & CPU_EVENT_TIME)
			cpu_remote_enter_state(CPU_STATE_HALT);
		else if (event & CPU_EVENT_POLL)
			cpu_remote_poll();
		break;
	case CPU_STATE_WAIT_ARCH:
		if (event & CPU_EVENT_SYNC)
			cpu_remote_enter_state(CPU_STATE_WAIT_BUSY);
		else if (event & CPU_EVENT_POLL)
			cpu_arch_poll();
		break;
	case CPU_STATE_HALT:
		break;
	default:
		break;
	}
}

bool cpu_remote_cold_boot_async(uint64_t cpu_mask)
{
	int i;
	bool completed = true;

	for (i = 0; i < MAX_CPU_NUM; i++) {
		if (((uint64_t)1 << i) & (cpu_mask))
			cpus_config_entry_point(CPU_POWER_ON_ENTRY_POINT);
		if (!cpus_deassert_reset_async(i))
			completed = false;
	}
	return completed;
}

int cpu_remote_cold_boot(uint64_t cpu_mask)
{
	while (!cpu_remote_cold_boot_async(cpu_mask));
	return 0;
}

static void __cpus_sync(unsigned long sync_state,
		        uint64_t this_cpu_mask, bool entry_or_exit,
		        uint32_t flags, bool wait, ktime_t timeout)
{
	uint64_t all_cpu_mask;

	if (sync_state == CPU_EXEC_OPENED) {
		all_cpu_mask = cpu_exec_good;
		cpu_exec_sync |= this_cpu_mask;
	} else {
		all_cpu_mask = 0;
		cpu_exec_sync &= ~this_cpu_mask;
	}

	while (cpu_exec_state != sync_state) {
		spin_unlock(&cpu_exec_lock);
		if (wait &&
		    time_after(time_get_current_time(), timeout)) {
			printf("%d: timeout\n", smp_processor_id());
			spin_lock(&cpu_exec_lock);
			if (sync_state == CPU_EXEC_OPENED)
				cpu_exec_good &= cpu_exec_sync;
			else
				cpu_exec_good &= ~cpu_exec_sync;
			spin_unlock(&cpu_exec_lock);
		}
		cpu_relax();
		spin_lock(&cpu_exec_lock);
		if (all_cpu_mask == cpu_exec_sync &&
		    cpu_exec_state != sync_state) {
			cpu_exec_state = sync_state;
			/* SYNC+RAND mode solution 2:
			 * The last CPU will reset the global test id
			 * here.
			 */
			if (sync_state == CPU_EXEC_OPENED &&
			    entry_or_exit)
				cpu_exec_test_id = -1;
		}
	}
}

static void inline cpu_exec_open(uint64_t cpu_mask, bool is_entry,
				 uint32_t flags, bool wait,
				 ktime_t timeout)
{
	__cpus_sync(CPU_EXEC_OPENED, cpu_mask, is_entry,
		    flags,  wait, timeout);
}

static void inline cpu_exec_close(uint64_t cpu_mask, bool is_exit,
				  uint32_t flags, bool wait,
				  ktime_t timeout)
{
	__cpus_sync(CPU_EXEC_CLOSED, cpu_mask, is_exit,
		    flags, wait, timeout);
}

static inline ktime_t __get_testfn_timeout(struct cpu_exec_test *fn,
					   ktime_t timeout)
{
	if (fn->timeout != CPU_WAIT_INFINITE) {
		ktime_t test_timeout = time_get_current_time() +
				       fn->timeout;
		if (time_after(timeout, test_timeout))
			return test_timeout;
	}
	return timeout;
}

static int __do_one_testfn(struct cpu_exec_test *start,
			   int nr_tests, int *local_test_id,
			   uint64_t cpu_mask, uint32_t flags,
			   bool wait, ktime_t timeout,
			   void (*notify)(bool))
{
	int i = 0, test_id;
	int ret = 1;
	ktime_t expected_time = timeout;
	struct cpu_exec_test *fn;
	bool sync = false;
	uint8_t cpu = smp_processor_id();
	bool owned = false;

again:
	test_id = *local_test_id;
	if (cpu_exec_test_id == -1) {
		if (flags & CPU_EXEC_RAND)
			test_id = (rand() % nr_tests);
		else
			test_id++;
		if (flags & CPU_EXEC_SYNC)
			owned = true;
	} else {
		/* This implies CPU_EXEC_SYNC mode as the global test
		 * id is only reset in SYNC mode.
		 */
		test_id = cpu_exec_test_id;
	}
	if (test_id >= nr_tests)
		return -EEXIST;
	*local_test_id = test_id;
	fn = (struct cpu_exec_test *)((uintptr_t)start +
	     (test_id * sizeof (struct cpu_exec_test)));
	if (fn->flags & CPU_EXEC_META)
		goto again;
	if (owned)
		cpu_exec_test_id = test_id;

	if (!(flags & CPU_EXEC_SYNC)) {
		if (flags & CPU_EXEC_RAND) {
			/* SYNC+RAND mode solution 1/2 switches here:
			 * Choose to reset global test id after all CPUs
			 * seeing the selected test id.
			 * In order to have all CPUs to see the selected
			 * test id, all CPUs need to wait for each other.
			 */
			sync = true;
		} else
			sync = fn->flags & CPU_EXEC_SYNC ? true : false;
	} else
		sync = true;

	do_printf("%s %.3d/%.3d on %d\n", fn->name,
	       test_id, nr_tests, smp_processor_id());

repeat:
	if (!(cpu_exec_good & cpu_mask)) {
		ret = 0;
		goto end;
	}
	if (sync) {
		expected_time = __get_testfn_timeout(fn, timeout);
		cpu_exec_open(cpu_mask,
			      i == 0 ? true : false,
			      flags, wait, expected_time);
	}
	if (cpu_exec_test_id != -1 &&
	    flags & CPU_EXEC_SYNC) {
		/* SYNC+RAND mode solution 2:
		 * The first CPU will reset the global test id here.
		 */
		cpu_exec_test_id = -1;
	}
	spin_unlock(&cpu_exec_lock);
	if (notify)
		notify(false);
	/* TODO: The percpu area is not working for raven cases, and
	 *       raven cases are now the only pattern running with
	 *       cpu_local_exec().
	 */
	ret = fn->func(cpu_get_percpu_area(cpu));
	if (!ret) {
		printf("%s failure on %d\n",
		       fn->name, smp_processor_id());
		spin_lock(&cpu_exec_lock);
		cpu_exec_good &= ~cpu_mask;
		goto end;
	}
	if (notify)
		notify(true);
	do_printf("%s success on %d\n",
	       fn->name, smp_processor_id());
	spin_lock(&cpu_exec_lock);
	if (sync)
		cpu_exec_close(cpu_mask,
			       (i + 1) == fn->repeat ? true : false,
			       flags, wait, expected_time);
	if (++i < fn->repeat)
		goto repeat;
end:
	return ret;
}

static int do_one_testfn(struct cpu_exec_test *start, int nr_tests,
			 int *local_test_id, uint64_t cpu_mask,
			 uint32_t flags, bool wait, ktime_t timeout,
			 void (*notify)(bool))
{
	return __do_one_testfn(start, nr_tests, local_test_id, cpu_mask,
			       flags, wait, timeout, notify);
}

/* There are several implementations for SYNC+RAND mode:
 * 1. The global test id is cleared after the last CPU having seen the
 *    selected test id.
 *    To achieve this, cpu_exec_open() need to be invoked with sync mode.
 *    Merit:  all CPUs will execute the cases with SYNC flag cleared.
 *    Demrit: cases with SYNC flag cleared will be executed in SYNC mode
 *            even if the RAND mode is also specified.
 * 2. The global test id is cleared by the first CPU seeing the selected
 *    test id.
 *    To achieve this, cpu_exec_open() need to be invoked without sync
 *    mode.
 *    Merit:  CPUs have chance to use a different order than the other
 *            CPUs to execute cases with SYNC flag cleared.
 *    Demrit: cases with SYNC flag cleared might not be executed by the
 *            CPUs if the first CPU reset the global test id too early.
 *            This is also OK as in RAND mode, only cases with SYNC flag
 *            set need to be executed altogether.
 * 3. The most complicated implementation is to ensure cases executed on
 *    all CPUs are executed in the same order with respect to the case
 *    specific SYNC flag to achieve maximum performance. There could be
 *    tow possible approaches:
 *    3.1. The first one is invoking cpu_exec_open() without sync mode, and
 *         not resetting global test is but queueing the 2nd+ test ids up.
 *    3.2. The second one is using percpu PRNG to make sure case numbers
 *         generated seperately by the different CPUs are in the same
 *         order.
 */
int cpu_local_exec(struct cpu_exec_test *start, int nr_tests,
		   uint64_t init_cpu_mask, uint32_t flags,
		   ktime_t timeout, void (*notify)(bool))
{
	int ret;
	ktime_t expected_time = timeout;
	uint64_t cpu_mask = UINT64_C(1) << smp_processor_id();
	bool wait = false;
	int local_test_id;

	if (timeout != CPU_WAIT_INFINITE) {
		expected_time += time_get_current_time();
		wait = true;
	}

	srand(time(NULL));
	spin_lock(&cpu_exec_lock);
	if (!cpu_exec_refcnt) {
		cpu_exec_good = init_cpu_mask;
		cpu_exec_test_id = -1;
	}
	local_test_id = -1;
	cpu_exec_refcnt++;
	while (!wait ||
	       time_before(time_get_current_time(), expected_time)) {
		ret = do_one_testfn(start, nr_tests, &local_test_id,
				    cpu_mask, flags, wait,
				    expected_time, notify);
		if (ret == -EEXIST)
			break;
		if (!ret && !cpu_exec_good) {
			ret = -EFAULT;
			goto end;
		}
	}
	ret = cpu_exec_good & cpu_mask ? 0 : -EFAULT;
end:
	cpu_exec_refcnt--;
	if (!cpu_exec_refcnt)
		cpu_exec_good = 0;
	spin_unlock(&cpu_exec_lock);
	return ret;
}

struct cpu_exec_test *cpu_exec_find(const char *name)
{
	int nr_tests = ((uintptr_t)__testfn_end -
			(uintptr_t)__testfn_start) /
		       sizeof (struct cpu_exec_test);
	struct cpu_exec_test *start = __testfn_start;
	int i;

	for (i = 0; i < nr_tests; i++) {
		if (strcmp((start + i)->name, name) == 0)
			return start + i;
	}
	return NULL;
}

uint64_t cpu_local_get_cpu_mask(void)
{
	return cpu_didt_cpu_mask;
}

int cpu_local_didt(uint64_t init_cpu_mask, struct cpu_exec_test *fn,
		   ktime_t interval, ktime_t period, int repeats)
{
	uint8_t cpu = smp_processor_id();
	int dsr = INVALID_DSR;
	bool locked = false;

	spin_lock(&cpu_exec_lock);
	cpu_didt_refcnt++;
	if (cpu_didt_refcnt == 1) {
		cpu_didt_cpu_mask = init_cpu_mask;
		locked = true;
	}
	if (!locked) {
		while (!cpu_didt_area) {
			spin_unlock(&cpu_exec_lock);
			cpu_relax();
			spin_lock(&cpu_exec_lock);
		}
	}
	spin_unlock(&cpu_exec_lock);
	if (locked) {
		cpu_didt_area = heap_aligned_alloc(fn->alloc_align,
			fn->alloc_size * hweight64(init_cpu_mask));
		printf("alloc: cpuexec: %016llx(%d)\n",
		       (uint64_t)cpu_didt_area,
		       fn->alloc_size * hweight64(init_cpu_mask));
		locked = false;
	}

	cpu_ctxs[cpu].async_wait_interval = interval;
	cpu_ctxs[cpu].async_exec_period = period;
	cpu_ctxs[cpu].didt_entry = fn;
	cpu_ctxs[cpu].didt_repeats = repeats;
	cpu_ctxs[cpu].didt_result = 0;
	cpu_raise_event(CPU_EVENT_START);

	while (cpu_ctxs[cpu].async_event != CPU_EVENT_POLL ||
	       cpu_ctxs[cpu].async_state != CPU_STATE_NONE) {
		irq_local_enable();
		dsr = dsr_run_once(dsr);
		irq_local_disable();
	}
	return cpu_ctxs[cpu].didt_result;
}

uint64_t cpus_mode = CPU_MODE_BENCH;

static int err_cpus(const char *hint)
{
	printf("--ERROR: %s\n", hint);
	(void)cmd_help("cpus");
	return -EINVAL;
}

static uint64_t cmd_cpus_cpu_mask = 0;
static int cmd_cpus_repeats = 0;
static struct cpu_exec_test *cmd_cpus_test_set = NULL;
static ktime_t cmd_cpus_timeout = CPU_WAIT_INFINITE;
static ktime_t cmd_cpus_interval = CPU_WAIT_INFINITE;

static void cmd_cpus_run_complete(uint64_t *results)
{
	int id;

	if (!results)
		return;

	printf("cpus completed.\n");
	for (id = 0; id < MAX_CPU_NUM; id++) {
		if (cmd_cpus_cpu_mask & C(id)) {
			printf("%d result: %s(%lld)\n", id,
			       results[id] == 0 ? "success" : "failure",
			       results[id]);
		}
	}
}

#if 0
static int cmd_dummy_success_test(void)
{
	return 1;
}

static int cmd_dummy_failure_test(void)
{
	return 0;
}
#endif

static int cmd_cpus_run_remote(void)
{
#if 0
	if (smp_processor_id() == 0)
		wait_for_dbg();
#endif
	return cpu_local_didt(cmd_cpus_cpu_mask, cmd_cpus_test_set,
			      cmd_cpus_interval, cmd_cpus_timeout,
			      cmd_cpus_repeats);
}

static int cmd_cpus_didt(uint64_t cpu_mask, struct cpu_exec_test *fn,
			 ktime_t period, ktime_t interval,
			 int repeats, ktime_t timeout, bool sync)
{
	struct cpu_table table;
	int i;

	cmd_cpus_cpu_mask = (cpu_mask & get_cpu_mask());
	cmd_cpus_test_set = fn;
	cmd_cpus_interval = interval;
	cmd_cpus_timeout = period;
	cmd_cpus_repeats = repeats;

	cpus_mode = CPU_MODE_TESTOS;
	for (i = 0; i < MAX_CPU_NUM; i++) {
		if (C(i) & cpu_mask)
			table.entries[i] = cmd_cpus_run_remote;
		else
			table.entries[i] = NULL;
	}
	if (sync)
		cpu_remote_boot(&table, false, false, timeout,
				cmd_cpus_run_complete);
	else
		cpu_remote_boot_async(&table, false, false, timeout,
				      cmd_cpus_run_complete);
	printf("cpus didt completed.\n");
	return 0;
}
#if 0
static int cmd_cpus(int argc, char **argv)
{
	int nr_tests = ((uintptr_t)__testfn_end -
			(uintptr_t)__testfn_start) /
		       sizeof (struct cpu_exec_test);
	struct cpu_exec_test *start = __testfn_start, *fn;
	uint64_t cpu_mask;
	int i, ret;
	ktime_t timeout, period, interval;
	int repeats;

	if (argc < 2)
		return err_cpus("Missing sub-command.\n");
	if (strcmp(argv[1], "show") == 0) {
		for (i = 0; i < nr_tests; i++) {
			if ((start + i)->flags & CPU_EXEC_META)
				printf("%20s: %4s %4s 0x%016llx\n",
				       (start + i)->name,
				       (start + i)->flags & CPU_EXEC_SYNC ? "sync" : "",
				       (start + i)->flags & CPU_EXEC_DDR ? "ddr" : "",
				       (uint64_t)((start + i)->func));
		}
	} else if (strcmp(argv[1], "help") == 0) {
		(void)cmd_help("cpus");
	} else if (strcmp(argv[1], "sync") == 0 ||
		   strcmp(argv[1], "async") == 0) {
		if (argc < 7)
			return err_cpus("Missing parameters.\n");
		cpu_mask = cmd_get_cpu_mask(argv[2]);
		if (cpu_mask == CMD_INVALID_CPU_MASKS)
			return err_cpus("Invalid CPU mask.\n");
		fn = cpu_exec_find(argv[3]);
		if (!fn || !(fn->flags & CPU_EXEC_META))
			return err_cpus("Invalid test function.\n");
		period = strtoull(argv[4], 0, 0);
		interval = strtoull(argv[5], 0, 0);
		repeats = strtoull(argv[6], 0, 0);
		if (period == CPU_WAIT_INFINITE ||
		    period * MSECS_PER_SEC < period)
			return err_cpus("Invalid period.\n");
		period *= MSECS_PER_SEC;
		if (interval == CPU_WAIT_INFINITE ||
		    interval * MSECS_PER_SEC < interval)
			return err_cpus("Invalid interval.\n");
		interval *= MSECS_PER_SEC;
		if (repeats < 0)
			return err_cpus("Invalid repeat times.\n");
		if (argc > 7) {
			timeout = strtoull(argv[7], 0, 0);
			if (timeout * MSECS_PER_SEC < timeout)
				return err_cpus("Invalid timeout.\n");
			timeout *= MSECS_PER_SEC;
		} else
			timeout = CPU_WAIT_INFINITE;
		/* Try to avoid dIdT mode */
		if (period >= interval) {
			printf("Switch to the non-didt mode.\n");
			interval = 0;
		}
		ret = cmd_cpus_didt(cpu_mask, fn, period, interval,
				    repeats, timeout,
				    !!strcmp(argv[1], "sync") == 0);
		if (ret) {
			printf("--ERROR: failed to run %s\n", argv[3]);
			return -EFAULT;
		}
	} else
		return err_cpus("Invalid sub-command.\n");
	return 0;
}

MK_CMD(cpus, cmd_cpus, "Run pre-registered patterns on CPUs",
	" show\n"
	"    -List the pre-registered patterns\n"
	" async/sync N|cN|rN|all pattern period interval repeats [timeout]\n"
	"    -(A)synchronously run pre-registered pattern\n"
	"     Run pattern specified \"repeats\" until \"timeout\".\n"
	"     Each run starts simultaneously on specified CPUs.\n"
	"     Each run repeatedly executing the pattern during \"period\".\n"
	"     Next run starts \"interval\" later than the previous run.\n"
);
#endif
#if 0
	/* size of help message is limitted */
	"     CPU specifications (N|cN|rN|all):\n"
	"        N: CPU N, N starts from 0.\n"
	"       cN: Cluster N, N starts from 0.\n"
	"       rN: Rail N, N starts from 0.\n"
	"      all: All CPUs.\n"
	"     dIdT mode: When interval > period, after running pattern for a\n"
	"                while (period), CPU will enter idle state for a\n"
	"                while (interval - period).\n"
	"     norm mode: When interval <= period, CPU won't enter idle state.\n"
#endif

int cpu_remote_init(void)
{
	uint8_t cpu = hmp_processor_id();

	cpu_ctxs[cpu].dsr = dsr_register(cpu_remote_dsr_handler, NULL);
	cpu_ctxs[cpu].timer = timer_register(TIMER_DSR,
					     cpu_remote_timer_handler);

	return 0;
}
