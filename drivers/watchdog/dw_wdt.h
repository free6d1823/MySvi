#ifndef __DW_WDT_H_
#define __DW_WDT_H_

#include <asm/io.h>
#include <target/utils.h>

#define DW_WDT_NUM	3
#define DW_WDT_CRR_RESTART_VAL	0x76

#define CONFIG_DW_WDT_CLOCK_KHZ	25000

struct wdt_regs {
	u32 wdt_cr;			/* 0x00 */
	u32 wdt_torr;		/* 0x04 */
	u32 wdt_ccvr;		/* 0x08 */
	u32 wdt_crr;		/* 0x0c */
	u32 wdt_stat;		/* 0x10 */
	u32 wdt_eoi;		/* 0x14 */
	u32 wdt_plevel;		/* 0x14 */
};

#endif /* __DW_WDT_H_ */

