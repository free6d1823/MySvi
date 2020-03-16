/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#ifndef __HDTS_TIMER_H__
#define __HDTS_TIMER_H__

#include "stdbool.h"
#include "stdint.h"

void imc_timers_init(void);
void imc_clear_timer_interrupts(void);
void imc_mask_timer_interrupts(void);
void imc_unmask_timer_interrupts(void);
void imc_set_timer(UINT64 match_val);

void Hdts_waitForMicroSecs(uint32_t pause_us);

#endif /* __HDTS_TIMER_H__ */
