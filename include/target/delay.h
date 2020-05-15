#ifndef __TESTOS_DELAY_H_INCLUDE__
#define __TESTOS_DELAY_H_INCLUDE__

#include <stdint.h>

void udelay(uint32_t pause_time_us);
#define mdelay(m) udelay(m * 1000)


#endif /* __TESTOS_DELAY_H_INCLUDE__ */
