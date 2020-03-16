/*
 */
#include <target/timer.h>
#include <target/memory.h>


static inline void __udelay(uint32_t pause_time_us)
{
    ktime_t start_us, end_us;

    start_us = time_get_current_time();
    end_us = start_us + pause_time_us;
    while (time_before(start_us, end_us))
        start_us = time_get_current_time();
}

#ifdef CONFIG_TESTOS_EMU
void udelay(uint32_t pause_time_us)
{
    return __udelay(pause_time_us/1000);
}
#else

void udelay(uint32_t pause_time_us)
{
    return __udelay(pause_time_us);
}
#endif
