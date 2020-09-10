#ifndef __DW_TIMER_H_
#define __DW_TIMER_H_

#include <asm/io.h>
#include <target/utils.h>

#define SUPPORT_TIMER_UNIT_MAX_NUM		0x2
#define SUPPORT_TIMER_INTER_MAX_NUM		0x4

#define DW_TMR_REG_BASE(uid,tid)		(0x0E9450000 + (uid*0x10000)+ (tid-1)*0x14)

#define DW_TMR_ENABLE_MASK			0x1
#define DW_TMR_MODE_MASK			0x2
#define DW_TMR_INT_MASK				0x4

struct tmr_regs {
	u32 tmr_lc;			/* 0x00 TimerNLoadCount*/
	u32 tmr_cv;			/* 0x04 TimerNCurrentValue*/
	u32 tmr_cr;			/* 0x08 TimerNControlReg*/
	u32 tmr_eoi;			/* 0x0c TimerNEOI*/
	u32 tmr_intsta;			/* 0x10 TimerNIntStatus*/
};

typedef struct {
	char *	test_name;		/*!< test case name */
	u16	irq_nr;			/*!< configured dw timer irq num*/
	struct tmr_regs * reg_base;	/*!< configured dw timer register address*/
} auto_tmr_t;

u32 dw_timer_get_count(struct tmr_regs *tmr_base);
int dw_timer_read_int_status(struct tmr_regs *tmr_base);
int dw_timer_read_eoi(struct tmr_regs *tmr_base);
void dw_timer_enable(struct tmr_regs *tmr_base);
void dw_timer_disenable(struct tmr_regs *tmr_base);
int dw_timer_is_enabled(struct tmr_regs *tmr_base);
void dw_timer_user_mode_set(struct tmr_regs *tmr_base);
void dw_timer_free_mode_set(struct tmr_regs *tmr_base);
int dw_timer_get_timer_mode(struct tmr_regs *tmr_base);
void dw_timer_int_masked(struct tmr_regs *tmr_base);
void dw_timer_int_unmasked(struct tmr_regs *tmr_base);
void dw_timer_load_value(struct tmr_regs *tmr_base,u32 count);
int dw_timer_stop(struct tmr_regs *tmr_base);
int dw_timer_irq_init(u8 uid, u8 tid);

#endif /* __DW_TIMER_H_ */

