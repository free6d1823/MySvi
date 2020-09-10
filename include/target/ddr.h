#ifndef __TARGET_DDR_H_INCLUDE__
#define __TARGET_DDR_H_INCLUDE__

#ifdef CONFIG_QCOM_DDRSS
#include <asm/mach/ddr.h>
#endif

#ifdef CONFIG_DDR
int ddr_init();
#else
int ddr_init()
{
	return 0;
}
#endif

#endif
