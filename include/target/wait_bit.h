/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Wait for bit with timeout and ctrlc
 *
 * (C) Copyright 2015 Mateusz Kulikowski <mateusz.kulikowski@gmail.com>
 */

#ifndef __WAIT_BIT_H
#define __WAIT_BIT_H

#include <asm-generic/errno.h>
#include <target/utils.h>
#include <target/delay.h>
#include <stdbool.h>
#include <asm/io.h>
#include <target/utils.h>
/**
 * wait_for_bit_x()	waits for bit set/cleared in register
 *
 * Function polls register waiting for specific bit(s) change
 * (either 0->1 or 1->0). It can fail under two conditions:
 * - Timeout
 * - User interaction (CTRL-C)
 * Function succeeds only if all bits of masked register are set/cleared
 * (depending on set option).
 *
 * @param reg		Register that will be read (using read_x())
 * @param mask		Bit(s) of register that must be active
 * @param set		Selects wait condition (bit set or clear)
 * @param timeout_ms	Timeout (in milliseconds)
 * @param breakable	Enables CTRL-C interruption
 * @return		0 on success, -ETIMEDOUT or -EINTR on failure
 */

#define WATCHDOG_RESET()	{}

static inline unsigned long get_timer(unsigned long base)
{
	uint64_t tsc_hw_read_counter(void);
	return (ulong)tsc_hw_read_counter() / 1000 - base;
}


#define BUILD_WAIT_FOR_BIT(sfx, type, read)				\
									\
static inline int wait_for_bit_##sfx(const void *reg,			\
				     const type mask,			\
				     const bool set,			\
				     const unsigned int timeout_ms,	\
				     const bool breakable)		\
{									\
	type val;							\
	unsigned long start = get_timer(0);				\
									\
	while (1) {							\
		val = read(reg);					\
									\
		if (!set)						\
			val = ~val;					\
									\
		if ((val & mask) == mask)				\
			return 0;					\
									\
		if (get_timer(start) > timeout_ms)			\
			break;						\
		udelay(1);						\
		WATCHDOG_RESET();					\
	}								\
	return -ETIMEDOUT;						\
}

BUILD_WAIT_FOR_BIT(8, u8, readb)
BUILD_WAIT_FOR_BIT(le16, u16, readw)
#ifdef readw_be
BUILD_WAIT_FOR_BIT(be16, u16, readw_be)
#endif
BUILD_WAIT_FOR_BIT(le32, u32, readl)
#ifdef readl_be
BUILD_WAIT_FOR_BIT(be32, u32, readl_be)
#endif

#endif

