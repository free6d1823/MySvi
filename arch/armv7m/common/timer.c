/*
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <target/timer.h>
#include <asm/mach/memory.h>
#include <asm/reg.h>

#define     SYSTICK_CTRL_ENA             (1<<0)
#define     SYSTICK_CTRL_TINT            (1<<1)
#define     SYSTICK_CTRL_COUNTFLAG       (1<<16)

#define     SYSTICK_LOAD_PRELOADMASK     0xFFFFFF
#define     SYSTICK_LOAD_RDVALMASK       0xFFFFFF

#define     tmr_handle_irq               SysTick_Handler
#define     MAXNUM                       10
#define     RUNNING                      true
#define     STOP                         false

uint64_t    systick_count;                //free run tick count used to record time in 10ms ticks

typedef struct
{
   uint64_t matchval;
   bool     timerstate; //running or stop
} Matchtimer;

Matchtimer Totaltimers[MAXNUM];

uint32_t systick_read(void)
{
	return ((uint32_t)(SysTick->VAL)&SYSTICK_LOAD_RDVALMASK);
}

void systick_enable_irq(void)
{
	uint32_t value;

	value = (uint32_t)(SysTick->CTRL);
	value |= SYSTICK_CTRL_TINT;
	(SysTick->CTRL) = (uint32_t)value;
}

void systick_disable_irq(void)
{
	uint32_t value;

	value = (uint32_t)(SysTick->CTRL);
	value &= ~(uint32_t)0x2;
	(SysTick->CTRL) = (uint32_t)value;
}

static inline void systick_set_preloadcnt(uint32_t value)
{
	(SysTick->LOAD) = value;
}

static inline void systick_enable_counter(void)
{
	uint32_t value;

	value = (uint32_t)(SysTick->CTRL);
	value |= SYSTICK_CTRL_ENA;
	(SysTick->CTRL) = (uint32_t)value;
}

static inline void systick_disable_counter(void)
{
	uint32_t value;

	value = (uint32_t)(SysTick->CTRL);
	value &= ~(uint32_t)SYSTICK_CTRL_ENA;
	(SysTick->CTRL) = (uint32_t)value;
}


void systick_init_counter(void)
{
	systick_set_preloadcnt(SYSTICK_LOAD_PRELOADVAL);
	systick_enable_counter();
}


ktime_t tsc_hw_read_counter(void)
{

	return (ktime_t)(systick_count / TICKS_TO_MICROSECONDS);
}


bool gpt_hw_irq_poll(void)
{
	uint32_t val;

	val = (uint32_t)(SysTick->CTRL);
	if (val & SYSTICK_CTRL_COUNTFLAG) {
		return true;
	}
	return false;
}


void gpt_hw_oneshot_timeout(ktime_t match_val)
{
	uint8_t  timecnt;
	for(timecnt=0; timecnt<MAXNUM; timecnt++)
		if (Totaltimers[timecnt].timerstate == STOP) {
				Totaltimers[timecnt].matchval = match_val;
				Totaltimers[timecnt].timerstate = RUNNING;
				systick_enable_irq();
				systick_enable_counter();
				return;
		}
	printf("no sucessing to set oneshot timeout");
}


void tsc_hw_ctrl_init(void)
{
	systick_init_counter();
}


void gpt_hw_irq_init(void)
{
	systick_enable_irq();
}


void tmr_handle_irq(void)
{
	uint8_t  timecnt;

	systick_disable_irq();
	systick_count++;
	for(timecnt=0; timecnt<MAXNUM; timecnt++)
		if (Totaltimers[timecnt].timerstate == RUNNING) {
			if(time_get_current_time() >= Totaltimers[timecnt].matchval) {
				timer_handle_interrupt();
				Totaltimers[timecnt].timerstate = STOP;
			}
		}
	systick_enable_irq();
}

void gpt_hw_ctrl_init(void)
{
	uint8_t  timecnt;

	systick_count = 0;

	for(timecnt=0; timecnt<MAXNUM; timecnt++) {
		Totaltimers[timecnt].timerstate = STOP;
		Totaltimers[timecnt].matchval = 0;
	}
}

