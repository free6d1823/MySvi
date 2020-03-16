/*
 */
#ifndef __TIMER_H_INCLUDE__
#define __TIMER_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>
#include <target/list.h>

#ifndef __ASSEMBLY__

typedef uint8_t tid_t;
typedef uint64_t ktime_t;

#define time_after(a, b)	((int64_t)((b) - (a)) < 0)
#define time_before(a, b)	time_after(b, a)
#define time_after_eq(a, b)	((int64_t)((a) - (b)) >= 0)
#define time_before_eq(a, b)	time_after_eq(b, a)

#endif /* __ASSEMBLY__ */

#include <asm/timer.h>

#define MAX_TIMERS	5
#define INVALID_TID	MAX_TIMERS

#define TIMER_DSR	0x00
#define TIMER_ISR	0x01

#ifndef TICKS_TO_MICROSECONDS
#define TICKS_TO_MICROSECONDS	(ARCH_TIMER_FREQUENCY / 1000000UL)
#endif
#define MSECS_PER_SEC		1000000

#define TICK_1MS		TICKS_TO_MICROSECONDS*(1000)
#define SYSTICK_LOAD_PRELOADVAL		TICK_1MS*10


#ifndef __ASSEMBLY__

typedef void (*timer_handler)(void);

struct timer_desc {
	uint8_t type;
	bool shot;
	ktime_t match_time;
	timer_handler handler;
	struct list_head timer_list_entry;
};

struct timer_queue {
	struct list_head head;
};

/* =================================================================
 * Time APIs
 * ================================================================= */
ktime_t time_get_current_time(void);

/* =================================================================
 * Timer APIs
 * ================================================================= */
tid_t timer_register(uint8_t type, timer_handler handler);
bool timer_set(tid_t tid, ktime_t time, bool relative);
bool timer_clear(tid_t tid);

void timer_handle_interrupt(void);
bool timer_poll(void);
int timer_init(void);
int tick_init(void);
unsigned long  timer_get_us(void);
unsigned long  get_timer(unsigned long);


#endif /* __ASSEMBLY__ */

#endif /* __TIMER_H_INCLUDE__ */
