/*
 */
#ifndef __GIC3_H__
#define __GIC3_H__

#include <asm/gicv3.h>

#ifdef CONFIG_GICv3
extern irqc_t gicv3_irqc;

void gic3_early_init(void);
void gic3_handle_irq(void);
void gic3_init(void *dist_base,  void *rdist_base);
void gic600_pwr_on(void *base);
#else
#define gicv3_irqc			INVALID_IRQC

static inline void gic3_early_init(void)
{
}

static inline void gic3_handle_irq(void)
{
}

static inline void gic3_init(void)
{
}
#endif

#endif /* __GIC3_H__ */

