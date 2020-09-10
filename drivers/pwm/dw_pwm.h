#ifndef __DW_PWM_H_
#define __DW_PWM_H_

#include <asm/io.h>
#include <target/utils.h>

#define SUPPORT_PWM_UNIT_MAX_NUM	0x2

#define DW_PWM_REG_BASE(uid)		(0x0E9470000 + (uid*0x10000))

#define DW_PWM_TMR_ENABLE_MASK		0x1
#define DW_PWM_USER_MODE_MASK		0x2
#define DW_PWM_TMR_INT_MASK		0x4
#define DW_PWM_MODE_MASK		0x8
#define DW_PWM_0N100_DUTY_MASK		0x10

#define DW_PWM_0_duty_cycle		0x0
#define DW_PWM_100_duty_cycle		0x1

#define CONFIG_DW_PWM0_CLK		100000000
#define CONFIG_DW_PWM1_CLK		100000000


struct pwm_regs {
	u32 pwm_lc;		/* 0x00 TimerNLoadCount*/
	u32 pwm_cv;		/* 0x04 TimerNCurrentValue*/
	u32 pwm_cr;		/* 0x08 TimerNControlReg*/
	u32 pwm_eoi;		/* 0x0c TimerNEOI*/
	u32 pwm_intsta;		/* 0x10 TimerNIntStatus*/
	u32 pwm_reserve[39];	/* reserved */
	u32 pwm_lc2;		/* 0xb0 TimerNLoadCount2*/
};

typedef struct {
	char *			test_name;	/*!< test case name */
	u16			irq_nr;		/*!< configured dw pwm irq num*/
	u32             	time_clk;	/*!< the pwm clk to generate*/
	struct pwm_regs *	reg_base;	/*!< configured dw pwm register address*/
} auto_pwm_t;


int dw_pwm_timer_read_eoi(struct pwm_regs *pwm_base);
void dw_pwm_timer_enable(struct pwm_regs *pwm_base);
void dw_pwm_timer_disenable(struct pwm_regs *pwm_base);
int dw_pwm_timer_is_enabled(struct pwm_regs *pwm_base);
void dw_pwm_user_mode_set(struct pwm_regs *pwm_base);
void dw_pwm_int_masked(struct pwm_regs *pwm_base);
void dw_pwm_int_unmasked(struct pwm_regs *pwm_base);
void dw_pwm_mode_enable(struct pwm_regs *pwm_base);
void dw_pwm_mode_disenable(struct pwm_regs *pwm_base);
int dw_pwm_mode_is_enabled(struct pwm_regs *pwm_base);
void dw_pwm_duty0n100_enable(struct pwm_regs *pwm_base);
void dw_pwm_duty0n100_disenable(struct pwm_regs *pwm_base);
int dw_pwm_duty0n100_is_enabled(struct pwm_regs *pwm_base);
void dw_pwm_load_count_set(struct pwm_regs *pwm_base,u32 count);
void dw_pwm_load_count2_set(struct pwm_regs *pwm_base,u32 count);
void dw_pwm_duty_set(u32 timer_clk,u32 pwm_clk,double_t duty);
#endif /* __DW_PWM_H_ */

