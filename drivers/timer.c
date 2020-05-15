/*
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <target/timer.h>
#include <target/dsr.h>
#include <target/smp.h>
#include <target/cmdline.h>

#define TIMER_EVENT_POLL	0x01
#define TIMER_EVENT_TIMEOUT	0x02

typedef struct timer_desc timer_table[MAX_TIMERS];

struct clkevt_desc {
	struct timer_queue timer_list;
	timer_table timer_obj_caches;
	int next_tid;
	int dsr;
	uint8_t events;
} __cache_aligned;

static struct clkevt_desc cpu_clkevts[NR_CPUS];

static void timer_handle_timeout(void);

void timer_raise_event(uint8_t event)
{
	uint8_t cpu = hmp_processor_id();

	cpu_clkevts[cpu].events |= event;
	dsr_schedule(cpu_clkevts[cpu].dsr);
}

void timer_dsr_handler(void* ctx)
{
	uint8_t cpu = hmp_processor_id();
	uint8_t events = cpu_clkevts[cpu].events;

	cpu_clkevts[cpu].events = 0;
	if (events & TIMER_EVENT_POLL) {
		timer_poll();
		timer_raise_event(TIMER_EVENT_POLL);
	}
	if (events & TIMER_EVENT_TIMEOUT)
		timer_handle_timeout();
}

int tick_init(void)
{
	tsc_hw_ctrl_init();
	return 0;
}

unsigned long get_timer(unsigned long base)
{
  return ((unsigned long)tsc_hw_read_counter())/1000 - base;
}

unsigned long  timer_get_us(void)
{
	return (unsigned long)tsc_hw_read_counter();
}

ktime_t time_get_current_time(void)
{
	return tsc_hw_read_counter();
}

tid_t timer_register(uint8_t type, timer_handler handler)
{
	tid_t tid;
	struct timer_desc *timer;
	uint8_t cpu = hmp_processor_id();

	if (cpu_clkevts[cpu].next_tid >= MAX_TIMERS)
		return INVALID_TID;

	tid = cpu_clkevts[cpu].next_tid;
	timer = &cpu_clkevts[cpu].timer_obj_caches[tid];
	cpu_clkevts[cpu].next_tid++;
	INIT_LIST_HEAD(&timer->timer_list_entry);
	timer->handler = handler;
	timer->type = type;
	return tid;
}

static void timer_trigger(struct timer_desc *timer)
{
	uint8_t cpu = hmp_processor_id();
	tid_t timer_id = (timer - &cpu_clkevts[cpu].timer_obj_caches[0]);

	timer->shot = false;
	if (timer->handler)
		timer->handler(&timer_id);
}

static void timer_start_poll(void)
{
}

static void timer_stop_poll(void)
{
}

static bool __timer_clear(uint8_t cpu, struct timer_desc *timer)
{
	if (list_empty(&timer->timer_list_entry))
		return false;

	/* See if this is the next timer to fire */
	if (list_is_first(&timer->timer_list_entry,
			  &cpu_clkevts[cpu].timer_list.head)) {
		list_del_init(&timer->timer_list_entry);
		timer = list_first_entry(&cpu_clkevts[cpu].timer_list.head,
					 struct timer_desc,
					 timer_list_entry);
		if (!timer)
			timer_stop_poll();
		else
			gpt_hw_oneshot_timeout(timer->match_time);
	} else
		list_del_init(&timer->timer_list_entry);
	return true;
}

bool timer_set(tid_t tid, ktime_t time, bool relative)
{
	uint8_t cpu = hmp_processor_id();
	struct timer_queue *timer_list = &cpu_clkevts[cpu].timer_list;
	struct timer_desc *timer = &cpu_clkevts[cpu].timer_obj_caches[tid];
	ktime_t current_time = time_get_current_time();
	tid_t timer_id;

	if (relative) {
		/* Sanity check overflow if relative time */
		if (time_before(current_time+time,
				timer->match_time))
			return false;
		timer->match_time = current_time + time;
	} else
		timer->match_time = time;

#if 0
	{
	ktick_t ticks;
	/* check overflow of ticks */
	ticks = timer->match_time * TICKS_TO_MICROSECONDS;
	if (time_before(ticks, (ktick_t)0))
		return false;
	}
#endif

	if (!list_empty(&timer->timer_list_entry)) {
		if (!__timer_clear(cpu, timer))
			return false;
	}

	/* If match_time < current_time, trigger event.
	 *
	 * Note that the timer interrupt is marked as edge triggered at the
	 * GIC, so the timer interrupt must be go from inactive to active
	 * in order to generate an interrupt. To ensure that we make sure
	 * to only set the timer in the future which guarantees a period of
	 * time where the interrupt from the timer is low.
	 */
	if (time_before_eq(timer->match_time, current_time)) {
		/* Trigger the timer event */
		timer_trigger(timer);
		return true;
	}

	if (list_empty(&cpu_clkevts[cpu].timer_list.head)) {
		list_add_tail(&timer->timer_list_entry,
			      &timer_list->head);
		gpt_hw_oneshot_timeout(timer->match_time);
		timer_start_poll();
	} else {
		struct timer_desc *current_timer;

		list_for_each_entry(struct timer_desc, current_timer,
			      	    &timer_list->head,
				    timer_list_entry) {
			if (time_after(current_timer->match_time,
				       timer->match_time)) {
				list_add_tail(&timer->timer_list_entry,
					      &current_timer->timer_list_entry);
				if (list_is_first(&timer->timer_list_entry,
						  &timer_list->head))
					gpt_hw_oneshot_timeout(timer->match_time);
				break;
			}
		}
		if (list_empty(&timer->timer_list_entry))
			list_add_tail(&timer->timer_list_entry,
				      &timer_list->head);
	}
	return true;
}

bool timer_clear(tid_t tid)
{
	uint8_t cpu = hmp_processor_id();
	struct timer_desc *timer = &cpu_clkevts[cpu].timer_obj_caches[tid];

	return __timer_clear(cpu, timer);
}

void timer_handle_interrupt(void)
{
	struct timer_desc *timer;
	uint8_t cpu = hmp_processor_id();
	struct timer_queue *timer_list = &cpu_clkevts[cpu].timer_list;
	uint64_t current_time = time_get_current_time();
	tid_t timer_id;

	timer = list_first_entry(&timer_list->head, struct timer_desc,
				 timer_list_entry);
	while (timer != NULL && !timer->shot &&
	       time_after_eq(current_time, timer->match_time)) {
		if (timer->type == TIMER_ISR) {
			__timer_clear(cpu, timer);
			timer_trigger(timer);

		        /* See if the next timer has also fired */
		        timer = list_first_entry(&timer_list->head,
					         struct timer_desc,
					         timer_list_entry);
                } else {

						timer->shot = true;
						timer_raise_event(TIMER_EVENT_TIMEOUT);

                        /* See if the next timer has also fired
		        		timer = list_first_entry(&timer->timer_list_entry,
					         		struct timer_desc,
					         		timer_list_entry); */

						/*find the next if the next is not the last one*/
						if(!list_is_last(&timer->timer_list_entry, &timer_list->head)){
							timer = list_entry(timer->timer_list_entry.next,
								struct timer_desc, timer_list_entry);
						}else{
							timer = NULL;
						}
		}

		/* See if the next timer has also fired
		timer = list_first_entry(&timer_list->head,
					 struct timer_desc,
					 timer_list_entry); */
	}
}

static void timer_handle_timeout(void)
{
	struct timer_desc *timer, *next_timer = NULL;
	uint8_t cpu = hmp_processor_id();
	struct timer_queue *timer_list = &cpu_clkevts[cpu].timer_list;
	tid_t timer_id;

	timer = list_first_entry(&timer_list->head, struct timer_desc,
				 timer_list_entry);
	while (timer != NULL) {

		if(!list_is_last(&timer->timer_list_entry, &timer_list->head)){
			next_timer = list_entry(timer->timer_list_entry.next,
								struct timer_desc, timer_list_entry);
		}else{
			next_timer = NULL;
		}

		if(timer->type == TIMER_DSR && timer->shot){
			list_del_init(&timer->timer_list_entry);
			/*__timer_clear(cpu, timer); */
			timer_trigger(timer);
		}

		timer = next_timer;

		/* See if the next timer has also fired
		timer = list_first_entry(&timer_list->head,
					 struct timer_desc,
					 timer_list_entry); */
	}

	/*After all the timer in the list has been checked, find the
	 *youngest timer to set the hardware timer.
	 */
	timer = list_first_entry(&timer_list->head, struct timer_desc,
				 timer_list_entry);
	if(timer != NULL){
		gpt_hw_oneshot_timeout(timer->match_time);
	}
}

bool timer_poll(void)
{
	if (gpt_hw_irq_poll()) {
		timer_handle_interrupt();
		return true;
	}
	return false;
}

int timer_init(void)
{
	uint8_t cpu = hmp_processor_id();

	INIT_LIST_HEAD(&cpu_clkevts[cpu].timer_list.head);
	cpu_clkevts[cpu].dsr = dsr_register(timer_dsr_handler, NULL);
	gpt_hw_ctrl_init();
#ifdef CONFIG_IRQ_POLLING
	timer_raise_event(TIMER_EVENT_POLL);
#else
	gpt_hw_irq_init();
#endif
	return 0;
}

#include <string.h>
#include <stdlib.h>

#define GLOBAL_LOCK_TEST_TIMEOUT	(1000000) /*default value */
/*save all the timer ids which have been used*/
typedef struct test_timer_tids{
	uint8_t max_timers_used;
	tid_t ids[MAX_TIMERS];
	ktime_t periodic_times[MAX_TIMERS];
} test_timer_tids;

static test_timer_tids register_tids;

#if 0
static void test_timer_reset(void)
{
	timer_set(test_timer_id,
		GLOBAL_LOCK_TEST_TIMEOUT, true);
}
#endif

static void test_timer_handler(void* tid)
{
	tid_t timer_id = *((tid_t*)tid);
	printf("I am a dsr timer #%d\n",timer_id);
	/*set the timer for the next time*/;
	timer_set(timer_id, register_tids.periodic_times[timer_id], true);
}

static bool __test_timer_do_register(uint8_t type, timer_handler handler, ktime_t periodic_time, tid_t *tid)
{
	tid_t timer_id = 0;
	bool ret = false;
	ktime_t set_time = 0;

	timer_id = timer_register(TIMER_DSR, test_timer_handler);
	if(periodic_time == 0){
		set_time = GLOBAL_LOCK_TEST_TIMEOUT;
	}else{
		set_time = periodic_time;
	}

	if(timer_id != INVALID_TID){
		ret = true;
		*tid = timer_id;
		timer_set(timer_id, set_time, true);
	}else{
		ret = false;
		*tid = 0;
		printf("out of timers\n");
	}

	return ret;
}

//test_timer_id

static int test_timer(int argc, char * argv[])
{
	uint32_t i = 0;

	if(argc == 1){
		if(true == __test_timer_do_register(TIMER_DSR,
			test_timer_handler, 0,
			&register_tids.ids[register_tids.max_timers_used]) ){

			register_tids.periodic_times[register_tids.max_timers_used] =
				GLOBAL_LOCK_TEST_TIMEOUT;
			register_tids.max_timers_used++;
		}
	}else{
		if(!strcmp(argv[1], "off")){
			/*clear all the timers*/
			for(i = 0; i < register_tids.max_timers_used; i++) {
				if(register_tids.periodic_times[i] != 0){
					timer_clear(register_tids.ids[i]);
					register_tids.periodic_times[i] = 0;
				}

			}
		}else if(!strcmp(argv[1], "ptime")){
			if(argc >= 3){
				ktime_t ptime = strtoul(argv[2], 0, 0);
				if(ptime > 0 && __test_timer_do_register(TIMER_DSR,
					test_timer_handler, ptime,
					&register_tids.ids[register_tids.max_timers_used])){

					register_tids.periodic_times[register_tids.max_timers_used] = ptime;
					register_tids.max_timers_used++;

				}

			}else{
				printf("command wrong parameter\n");
			}

		}else{
			printf("command wrong parameter\n");
		}

	}
	/*if timer-off, call timer_clear function*/
	return 0;
}


MK_CMD(timer, test_timer, "dsr timer test",
		"timer "
		"--create dsr timer with default periodic time\n"
		"timer ptime [n]"
		"--create dsr timer with the specific periodic time\n"
		"timer off"
		"--clear all the timer actived\n"
);
