#include <std/string.h>
#include <std/stdlib.h>
#include <std/stdio.h>
#include <asm/memory.h>
#include <errno.h>
#include <target/irq.h>
#include <target/irqc.h>
#include <target/cmdline.h>
#include "dw_pwm.h"

static double_t dw_pwm_duty;
static u32 dw_pwm_load_count;
static u32 dw_pwm_load_count2;

auto_pwm_t dw_pwm_config[SUPPORT_PWM_UNIT_MAX_NUM]= {
	{"pwm0", DW_PWM_TRQ(0), CONFIG_DW_PWM0_CLK, (struct pwm_regs * )0x0E9470000},
	{"pwm1", DW_PWM_TRQ(1), CONFIG_DW_PWM1_CLK, (struct pwm_regs * )0x0E9480000},
};

int dw_pwm_timer_read_eoi(struct pwm_regs *pwm_base)
{
	return readl(&pwm_base->pwm_eoi);
}

// dw_timer enable/disable
void dw_pwm_timer_enable(struct pwm_regs *pwm_base)
{
	__raw_setl(DW_PWM_TMR_ENABLE_MASK, &pwm_base->pwm_cr);
}

void dw_pwm_timer_disenable(struct pwm_regs *pwm_base)
{
	__raw_clearl(DW_PWM_TMR_ENABLE_MASK, &pwm_base->pwm_cr);
}

int dw_pwm_timer_is_enabled(struct pwm_regs *pwm_base)
{
	ulong val;
	val = readl(&pwm_base->pwm_cr);
	return val & 0x1;
}

// dw_timer mode set：free running/user defined
void dw_pwm_user_mode_set(struct pwm_regs *pwm_base)
{
	__raw_setl(DW_PWM_USER_MODE_MASK, &pwm_base->pwm_cr);
}

// dw_timer interrupt mask
void dw_pwm_int_masked(struct pwm_regs *pwm_base)
{
	__raw_setl(DW_PWM_TMR_INT_MASK, &pwm_base->pwm_cr);
}

void dw_pwm_int_unmasked(struct pwm_regs *pwm_base)
{
	__raw_clearl(DW_PWM_TMR_INT_MASK, &pwm_base->pwm_cr);
}

//===================pwm enabele/disable======================//
void dw_pwm_mode_enable(struct pwm_regs *pwm_base)
{
	__raw_setl(DW_PWM_MODE_MASK, &pwm_base->pwm_cr);
}

void dw_pwm_mode_disenable(struct pwm_regs *pwm_base)
{
	__raw_clearl(DW_PWM_MODE_MASK, &pwm_base->pwm_cr);
}

int dw_pwm_mode_is_enabled(struct pwm_regs *pwm_base)
{
	ulong val;
	val = readl(&pwm_base->pwm_cr);
	return (val & DW_PWM_MODE_MASK)>>3;
}

//===================duty 0% and 100% enabele/disable======================//
void dw_pwm_duty0n100_enable(struct pwm_regs *pwm_base)
{
	__raw_setl(DW_PWM_0N100_DUTY_MASK, &pwm_base->pwm_cr);
}

void dw_pwm_duty0n100_disenable(struct pwm_regs *pwm_base)
{
	__raw_clearl(DW_PWM_0N100_DUTY_MASK, &pwm_base->pwm_cr);
}

int dw_pwm_duty0n100_is_enabled(struct pwm_regs *pwm_base)
{
	ulong val;
	val = readl(&pwm_base->pwm_cr);
	return (val & DW_PWM_0N100_DUTY_MASK)>>4;
}

void dw_pwm_load_count_set(struct pwm_regs *pwm_base,u32 count)
{
	writel(count, &pwm_base->pwm_lc);
}

void dw_pwm_load_count2_set(struct pwm_regs *pwm_base,u32 count)
{
	writel(count, &pwm_base->pwm_lc2);
}

void dw_pwm_duty_set(u32 timer_clk,u32 pwm_clk,double_t duty)
{
	if(duty == DW_PWM_0_duty_cycle){
		dw_pwm_load_count2 = 0x0;
	}
	else if(duty == DW_PWM_100_duty_cycle){
		dw_pwm_load_count = 0x0;
	}
	else{
		dw_pwm_load_count2 = (timer_clk*duty)/pwm_clk;
		dw_pwm_load_count = (timer_clk*(1-duty))/pwm_clk;
	}
}

static void dw_pwm_irq_handle(irq_t irq, void *ctx)
{
	dw_pwm_timer_read_eoi(dw_pwm_config[irq-DW_PWM_TRQ(0)].reg_base); 
}

int dw_pwm_irq_init(u8 uid)
{
	irq_t dw_pwm_irq = DW_PWM_TRQ(uid);
	irqc_configure_irq(dw_pwm_irq, 25, IRQ_LEVEL_TRIGGERED);
	irq_register_vector(dw_pwm_irq, dw_pwm_irq_handle, NULL);
	irqc_enable_irq(dw_pwm_irq);
	return 0;
}

#ifdef DW_PWM_TEST
int dw_pwm_start(u8 uid,u32 pwm_clk,double_t duty)
{
	dw_pwm_timer_disenable(dw_pwm_config[uid].reg_base);
	dw_pwm_user_mode_set(dw_pwm_config[uid].reg_base);
	dw_pwm_int_unmasked(dw_pwm_config[uid].reg_base);
	dw_pwm_mode_enable(dw_pwm_config[uid].reg_base);
	dw_pwm_duty_set(dw_pwm_config[uid].time_clk,pwm_clk,duty);
	dw_pwm_duty0n100_enable(dw_pwm_config[uid].reg_base);
	dw_pwm_load_count2_set(dw_pwm_config[uid].reg_base, dw_pwm_load_count2);
	dw_pwm_load_count_set(dw_pwm_config[uid].reg_base, dw_pwm_load_count);
	dw_pwm_timer_enable(dw_pwm_config[uid].reg_base);
	return 0;
}

void se1000_dw_pwm_init()
{
	u8 dw_pwm_uid = 0x0;
	dw_pwm_irq_init(dw_pwm_uid);
	dw_pwm_start(dw_pwm_uid,500000,0.6);
}
#endif