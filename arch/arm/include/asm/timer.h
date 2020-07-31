/*
 */
#ifndef __TIMER_ARMV7M_H_INCLUDE__
#define __ARMV7M_SYSOP_H_INCLUDE__

#include <stdint.h>

#ifndef __ASSEMBLY__

typedef uint64_t ktime_t;
typedef uint64_t ktick_t;


ktime_t tsc_hw_read_counter(void);
void gpt_hw_oneshot_timeout(ktime_t match_val);
bool gpt_hw_irq_poll(void);

void tsc_hw_ctrl_init(void);
void gpt_hw_ctrl_init(void);
void gpt_hw_irq_init(void);

#endif /* __ASSEMBLY__ */

#endif /* __ARMV7M_SYSOP_H_INCLUDE__ */
