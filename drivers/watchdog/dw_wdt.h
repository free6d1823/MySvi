#ifndef __DW_WDT_H_
#define __DW_WDT_H_

#include <asm/io.h>
#include <target/utils.h>

#if CONFIG_SUPPORT_SPU_WDT >= 4
#define SUPPORT_WDT_MAX_NUM		5
#else
#define SUPPORT_WDT_MAX_NUM		4
#endif

#define DW_WDT_CRR_RESTART_VAL		0x76

#define DW_WDT_CTR_ENABLE_RESET		0x01
#define DW_WDT_CTR_ENABLE_INT		0x03
#define CONFIG_DW_WDT_CLOCK_KHZ		25000

struct wdt_regs {
	u32 wdt_cr;			/* 0x00 */
	u32 wdt_torr;		/* 0x04 */
	u32 wdt_ccvr;		/* 0x08 */
	u32 wdt_crr;		/* 0x0c */
	u32 wdt_stat;		/* 0x10 */
	u32 wdt_eoi;		/* 0x14 */
	u32 wdt_plevel;		/* 0x14 */
};

void dw_wdt_enable(struct wdt_regs *wdt_base);
void dw_wdt_disenable(struct wdt_regs *wdt_base);
int dw_wdt_set_timeout(struct wdt_regs *wdt_base, u32 timeout_ms);
int dw_wdt_reset(struct wdt_regs *wdt_base);
int dw_wdt_irq_init(int index);
int dw_wdt_start(struct wdt_regs *wdt_base, uint timeout_ms);
int dw_wdt_stop(struct wdt_regs *wdt_base);

#endif /* __DW_WDT_H_ */

