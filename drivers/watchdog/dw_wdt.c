#include <std/string.h>
#include <std/stdlib.h>
#include <std/stdio.h>
#include <asm/memory.h>
#include <errno.h>
#include <target/irq.h>
#include <target/irqc.h>
#include <target/cmdline.h>
#include "dw_wdt.h"

static int dw_wdt_index;
struct wdt_regs *dw_wdt_bases[DW_WDT_NUM];

static inline int log_2_n_round_up(u32 n)
{
	int log2n = -1;
	u32 temp = n;

	while (temp) {
		log2n++;
		temp >>= 1;
	}

	if (n & (n - 1))
		return log2n + 1; /* not power of 2 - round up */
	else
		return log2n; /* power of 2 */
}

static void dw_wdt_enable(struct wdt_regs *wdt_base)
{
	writel(0x3, &wdt_base->wdt_cr);
}

static void dw_wdt_disenable(struct wdt_regs *wdt_base)
{
	writel(0x0, &wdt_base->wdt_cr);
}

static int dw_wdt_is_enabled(struct wdt_regs *wdt_base)
{
	ulong val;
	val = readl(&wdt_base->wdt_cr);
	return val & 0x1;
}

static int dw_wdt_set_timeout(struct wdt_regs *wdt_base, u32 timeout_ms)
{
	signed int i;

	/* calculate the timeout range value */
	i = log_2_n_round_up(timeout_ms * CONFIG_DW_WDT_CLOCK_KHZ) - 16;
	if (i > 15)
		i = 15;
	if (i < 0)
		i = 0;

	writel((i | (i << 4)), &wdt_base->wdt_torr);
	return 0;
}

static int dw_wdt_reset(struct wdt_regs *wdt_base)
{
	if (dw_wdt_is_enabled(wdt_base))
		/* restart the watchdog counter */
		writel(DW_WDT_CRR_RESTART_VAL, &wdt_base->wdt_crr);
	return 0;
}

static void dw_handle_wdt_irq(irq_t irq, void *ctx)
{
	printf("dw handle wdt irq.\n");
	dw_wdt_reset(dw_wdt_bases[dw_wdt_index]);
}

static int dw_wdt_irq_init(int index)
{
	irq_t dw_wdt_irq = DW_WDT_TRQ(index);
	dw_wdt_bases[index] = (struct wdt_regs *)(uintptr_t)(DW_WDT_REG_BASE(index));
	irqc_configure_irq(dw_wdt_irq, 32, IRQ_EDGE_TRIGGERED);
	irq_register_vector(dw_wdt_irq, dw_handle_wdt_irq, NULL);
	irqc_enable_irq(dw_wdt_irq);
	return 0;
}

static int dw_wdt_start(struct wdt_regs *wdt_base, uint timeout_ms)
{
	dw_wdt_set_timeout(wdt_base, timeout_ms);
	dw_wdt_enable(wdt_base);
	dw_wdt_reset(wdt_base);
	return 0;
}

static int dw_wdt_stop(struct wdt_regs *wdt_base)
{
	dw_wdt_disenable(wdt_base);
	return 0;
}

int do_cmd_wdt(int argc, char **argv)
{
	int ret = 0;
	int timeout_ms = 10000;

	if (argc < 2)
		return -EUSAGE;

	if (!strcmp("init", argv[1])) {
		dw_wdt_index = strtoul(argv[2], NULL, 0);
		if ((dw_wdt_index > -1) && (dw_wdt_index < 3)) {
			ret = dw_wdt_irq_init(dw_wdt_index);
		}
	}

	if (!strcmp("start", argv[1])) {
		timeout_ms = strtoul(argv[2], NULL, 0);
		ret = dw_wdt_start(dw_wdt_bases[dw_wdt_index], timeout_ms);
	}

	if (!strcmp("stop", argv[1])) {
		ret = dw_wdt_stop(dw_wdt_bases[dw_wdt_index]);
	}

	if (!strcmp("reset", argv[1])) {
		ret = dw_wdt_reset(dw_wdt_bases[dw_wdt_index]);
	}

	return ret;
}

MK_CMD(wdt, do_cmd_wdt, "Designware WDT cmd",
	" wdt init index \n"
	"		-the index of wdt controller initialization.\n"
	" wdt start timeout\n"
	"		-start watchdog timer\n"
	" wdt stop\n"
	"		-stop watchdog timer\n"
	" wdt reset\n"
	"		-reset watchdog timer\n"
);



