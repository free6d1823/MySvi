#include <std/string.h>
#include <std/stdlib.h>
#include <std/stdio.h>
#include <asm/memory.h>
#include <errno.h>
#include <target/irq.h>
#include <target/irqc.h>
#include <target/cmdline.h>
#include "dw_timer.h"

static int dw_timer_uid;
static int dw_timer_tid;
static u32 dw_timer_load_count;
static int dw_timer_index;

struct tmr_regs *dw_timer_bases[SUPPORT_TIMER_UNIT_MAX_NUM*SUPPORT_TIMER_INTER_MAX_NUM];
auto_tmr_t dw_timer_config[SUPPORT_TIMER_UNIT_MAX_NUM*SUPPORT_TIMER_INTER_MAX_NUM]= {
	{"Timer0_t1", DW_TMR_TRQ(0,1),  (struct tmr_regs * )0x0E9450000},
	{"Timer0_t2", DW_TMR_TRQ(0,2),  (struct tmr_regs * )0x0E9450014},
	{"Timer0_t3", DW_TMR_TRQ(0,3),  (struct tmr_regs * )0x0E9450028},
	{"Timer0_t4", DW_TMR_TRQ(0,4),  (struct tmr_regs * )0x0E945003C},
	{"Timer1_t1", DW_TMR_TRQ(1,1),  (struct tmr_regs * )0x0E9460000},
	{"Timer1_t2", DW_TMR_TRQ(1,2),  (struct tmr_regs * )0x0E9460014},
	{"Timer1_t3", DW_TMR_TRQ(1,3),  (struct tmr_regs * )0x0E9460028},
	{"Timer1_t4", DW_TMR_TRQ(1,4),  (struct tmr_regs * )0x0E946003C},
};

// dw_timer current value
u32 dw_timer_get_count(struct tmr_regs *tmr_base)
{
	return readl(&tmr_base->tmr_cv);
}

int dw_timer_read_int_status(struct tmr_regs *tmr_base)
{
	return readl(&tmr_base->tmr_intsta);
}

int dw_timer_read_eoi(struct tmr_regs *tmr_base)
{
	return readl(&tmr_base->tmr_eoi);
}

// dw_timer enable/disable
void dw_timer_enable(struct tmr_regs *tmr_base)
{
	__raw_setl(DW_TMR_ENABLE_MASK, &tmr_base->tmr_cr);
}

void dw_timer_disenable(struct tmr_regs *tmr_base)
{
	__raw_clearl(DW_TMR_ENABLE_MASK, &tmr_base->tmr_cr);
}

int dw_timer_is_enabled(struct tmr_regs *tmr_base)
{
	ulong val;
	val = readl(&tmr_base->tmr_cr);
	return val & 0x1;
}

// dw_timer mode set：free running/user defined
void dw_timer_user_mode_set(struct tmr_regs *tmr_base)
{
	__raw_setl(DW_TMR_MODE_MASK, &tmr_base->tmr_cr);
}

void dw_timer_free_mode_set(struct tmr_regs *tmr_base)
{
	__raw_clearl(DW_TMR_MODE_MASK, &tmr_base->tmr_cr);
}

int dw_timer_get_timer_mode(struct tmr_regs *tmr_base)
{
	ulong val;
	val = readl(&tmr_base->tmr_cr);
	return (val & DW_TMR_MODE_MASK)>>1;
}

// dw_timer interrupt mask
void dw_timer_int_masked(struct tmr_regs *tmr_base)
{
	__raw_setl(DW_TMR_INT_MASK, &tmr_base->tmr_cr);
}

void dw_timer_int_unmasked(struct tmr_regs *tmr_base)
{
	__raw_clearl(DW_TMR_INT_MASK, &tmr_base->tmr_cr);
}

void dw_timer_load_value(struct tmr_regs *tmr_base,u32 count)
{
	writel(count, &tmr_base->tmr_lc);
}

int dw_timer_start(struct tmr_regs *tmr_base ,u32 count)
{
	dw_timer_disenable(tmr_base);
	dw_timer_user_mode_set(tmr_base);
	dw_timer_int_unmasked(tmr_base);
	dw_timer_load_value(tmr_base, count);
	dw_timer_enable(tmr_base);
	return 0;
}

int dw_timer_stop(struct tmr_regs *tmr_base)
{
	dw_timer_disenable(tmr_base);
	return 0;
}

static void dw_timer_irq_handle(irq_t irq, void *ctx)
{
	dw_timer_read_eoi(dw_timer_config[irq-DW_TMR_TRQ(0,1)].reg_base);
}

int dw_timer_irq_init(u8 uid, u8 tid)
{
	irq_t dw_timer_irq = DW_TMR_TRQ(uid,tid);
	dw_timer_index = uid*SUPPORT_TIMER_INTER_MAX_NUM+tid-1;
	dw_timer_bases[dw_timer_index] = (struct tmr_regs *)(uintptr_t)(DW_TMR_REG_BASE(uid,tid));
	irqc_configure_irq(dw_timer_irq, 20, IRQ_LEVEL_TRIGGERED);
	irq_register_vector(dw_timer_irq, dw_timer_irq_handle, NULL);
	irqc_enable_irq(dw_timer_irq);
	return 0;
}

int dw_timer_handler(int argc, char **argv)
{
	int ret = -EUSAGE;
	u32 load_value = 10000;

	if (argc < 2)
		return -EUSAGE;

	if (!strcmp("init", argv[1])) {
		dw_timer_uid = strtoul(argv[2], NULL, 0);
		dw_timer_tid = strtoul(argv[3], NULL, 0);
		if ((dw_timer_uid >= 0) && (dw_timer_uid < SUPPORT_TIMER_UNIT_MAX_NUM)) {
			if ((dw_timer_tid >= 1) && (dw_timer_tid <= SUPPORT_TIMER_INTER_MAX_NUM)){
				ret = dw_timer_irq_init(dw_timer_uid,dw_timer_tid);
			}
			else{
				puts("the dw_timer internal id is out of range");
			}
		}
		else{
			puts("the dw_timer unit id is out of range");
		}
	}
	if (!strcmp("start", argv[1])) {
		load_value = strtoul(argv[2], NULL, 0);
		ret = dw_timer_start(dw_timer_bases[dw_timer_index], load_value);
	}

	if (!strcmp("stop", argv[1])) {
		ret = dw_timer_stop(dw_timer_bases[dw_timer_index]);
	}
	return ret;
}

#ifdef DW_TIMER_TEST
void se1000_dw_timer_init()
{
	dw_timer_uid = 0x0;
	dw_timer_tid = 0x1;

	dw_timer_irq_init(dw_timer_uid, dw_timer_tid);
	dw_timer_start((struct tmr_regs *)(uintptr_t)DW_TMR_REG_BASE(dw_timer_uid,dw_timer_tid),5000);
}
#endif

MK_CMD(dw_timer, dw_timer_handler, "Designware apb timer cmd",
	" dw_timer init uid tid \n"
	"		-uid[0, SUPPORT_TIMER_UNIT_MAX_NUM) of controller init.\n"
	"		-tid[1, SUPPORT_TIMER_INTER_MAX_NUM] of timers init.\n"
	" dw_timer start loadvalue\n"
	"		-start dw_timer\n"
	" dw_timer stop\n"
	"		-stop dw_timer\n"
);
