#ifndef __CLK_H_INCLUDE__
#define __CLK_H_INCLUDE__

#ifdef CONFIG_CLK_DRIVER

#include <asm/mach/clk.h>

/* APIs */
/**
 * clk_get_rate() - get current clock rate.
 * @return the rate
 */
ulong clk_get_rate(u32 clk_id);
/**
 * clk_set_rate() - Set current clock rate.
 * @rate:	New clock rate in Hz.
 * @return new rate, or -ve error code.
 */
void clk_set_rate(u32 clk_id, ulong rate);
void clk_disable(u32 clk_id);
/**
 * clk_enable() - enable clk gate
 * @src: support two kinds of clk source, pll divider and fixed osc clk
 * 		1: PLL divider source. for example PLL output clk is 1Ghz
 *    	config divider=5, will get 200Mhz clk output finally
 * 		0: fixed osc clk. for example, fixed 24Mhz clk. can't change
 */
void clk_enable(u32 clk_id, u32 src);
void clk_dump(u32 id);

#else

#define clk_get_rate(a) 0
#define clk_set_rate(a, b)
#define clk_disable(a)
#define clk_enable(a, b)
#define clk_dump(a)

#endif

#endif /* __CLK_H_INCLUDE__ */
