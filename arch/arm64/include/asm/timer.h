/*
 */
#ifndef __TIMER_ARM64_H_INCLUDE__
#define __TIMER_ARM64_H_INCLUDE__

#include <stdint.h>
#include <asm/io.h>
#include <asm/reg.h>

#ifndef __ASSEMBLY__

typedef uint64_t ktick_t;

void __systick_mask_irq(void);
void __systick_unmask_irq(void);
void __systick_init_counter(void);
void __systick_init_timer(void);

ktime_t tsc_hw_read_counter(void);
void gpt_hw_oneshot_timeout(ktime_t match_val);
bool gpt_hw_irq_poll(void);

void tsc_hw_ctrl_init(void);
void gpt_hw_ctrl_init(void);
void gpt_hw_irq_init(void);

#endif /* __ASSEMBLY__ */

#endif /* __TIMER_ARM64_H_INCLUDE__ */
