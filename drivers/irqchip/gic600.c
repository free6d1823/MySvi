#include <asm/io.h>

/* GIC600-specific register offsets */
#define GICR_PWRR	0x24

/* GICR_PWRR fields */
#define PWRR_RDPD_SHIFT		0
#define PWRR_RDGPD_SHIFT	2
#define PWRR_RDGPO_SHIFT	3

#define PWRR_RDGPD	(1 << PWRR_RDGPD_SHIFT)
#define PWRR_RDGPO	(1 << PWRR_RDGPO_SHIFT)

/* Values to write to GICR_PWRR register to power redistributor */
#define PWRR_ON		(0 << PWRR_RDPD_SHIFT)
#define PWRR_OFF	(1 << PWRR_RDPD_SHIFT)

void gic600_pwr_on(void *base)
{
	/* Power on redistributor */
	__raw_writel(PWRR_ON, base+GICR_PWRR);

	/* Wait until the power on state is reflected */
	while (__raw_readl(base + GICR_PWRR) & PWRR_RDGPO);
}

