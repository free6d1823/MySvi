/**
* @file
* @brief		This is a brief description.
* @details		After configuring necessary infomation, auto test all wdt.
* @author		author
* @date			2020-06-30
* @version		v1.0
* @par Copyright(c):	Siengine
* @par History:
*	version: author, date, desc\n
*/

#include <stdint.h>
#include <std/string.h>
#include <std/stdio.h>

#include <errno.h>
#include <target/irq.h>
#include <target/irqc.h>
#include <target/cmdline.h>
#include <target/dsr.h>
#include "dw_wdt.h"

/// test result
#define OK						(0)
#define WDT_STOP_FAILED			(-1)
#define WDT_RESET_FAILED		(-2)

#define ARRARY_SIZE(x)			(sizeof(x) / (sizeof((x)[0])))
#define DEFAULT_TIMEOUT			(1000u)
#if CONFIG_SUPPORT_SPU_WDT >= 4
/* arm64*/
#define DEFAULT_TIMEOUT_COUNT	(0x01ffffbaU)
#else
/* m4*/
#define DEFAULT_TIMEOUT_COUNT	(0x01fffffaU)
#endif
#define IRQ_CHECK_DEFAULT_TIMES	(3)

typedef enum{
	TEST_NOT_INIT = 0,
	TEST_IDLE = 1,
	TEST_START = 2,
} testbench_status_e;

/**
 * @brief		Configuration of watchdog need to be test
 */
typedef struct {
	char *			test_name;		/*!< test case name */
	irq_t			irq_nr;			/*!< configured watchdog irq num*/
	struct wdt_regs * reg_base;		/*!< configured watchdog register address*/
	int				expect_ret;		/*!< test case expected result*/
	int				test_ret;		/*!< test case execute result*/
} auto_wdt_t;

typedef struct {
	int						cur_test_index;
	int						dsr;
	testbench_status_e		test_status;
} auto_test_manage_t;

auto_wdt_t g_auto_wdt_config[] = 	{
		{"wdt0_test", DW_WDT_TRQ(0), (struct wdt_regs * )0x0E9410000, 0, -EAGAIN},
		{"wdt1_test", DW_WDT_TRQ(1), (struct wdt_regs * )0x0E9420000, 0, -EAGAIN},
		{"wdt2_test", DW_WDT_TRQ(2), (struct wdt_regs * )0x0E9430000, 0, -EAGAIN},
		{"wdt3_test", DW_WDT_TRQ(3), (struct wdt_regs * )0x0E9440000, 0, -EAGAIN},
#if CONFIG_SUPPORT_SPU_WDT >= 4
		{"wdt4_test", DW_WDT_TRQ(4), (struct wdt_regs * )0x040020000, 0, -EAGAIN},
#endif
	};

auto_test_manage_t g_auto_test_man = {0};
static int start_auto_test(auto_test_manage_t *p_test_man);

/**
 * @brief		unregist wdt irq handle.
 * @param[in]	idx watchdog index.
 */
static void unregist_wdt_irq(int idx)
{
	struct wdt_regs *wdt_base 	= NULL;
	irq_t 			dw_wdt_irq	= -1;
	ulong			wdt_ccvr	= -1;

	wdt_base = g_auto_wdt_config[idx].reg_base;
	dw_wdt_stop(wdt_base);

	dw_wdt_irq = g_auto_wdt_config[idx].irq_nr;
	irqc_disable_irq(dw_wdt_irq);
	irqc_clear_irq(dw_wdt_irq);
	irq_unregister_vector(dw_wdt_irq);

	return;
}

static void show_test_result(void)
{
	int idx = 0;

	for (idx=0; idx < ARRARY_SIZE(g_auto_wdt_config); idx++){
		if (g_auto_wdt_config[idx].expect_ret == g_auto_wdt_config[idx].test_ret){
			printf("%s test OK.\n", g_auto_wdt_config[idx].test_name);
		}
		else{
			printf("%s test failed,ret = %d.\n", g_auto_wdt_config[idx].test_name, g_auto_wdt_config[idx].test_ret);
		}
	}
}

/**
 * @brief		polling to test configured watch dogs.
 * @param[in]	ct	auot test wdt manage info.
 */
static void wdt_autotest_handle(void* ctx)
{
	auto_test_manage_t	*p_test_man = (auto_test_manage_t *)ctx;

	if (p_test_man->cur_test_index < ARRARY_SIZE(g_auto_wdt_config) - 1){
		unregist_wdt_irq(p_test_man->cur_test_index);
		p_test_man->cur_test_index++;
		start_auto_test(p_test_man);
	}
	else {
		unregist_wdt_irq(p_test_man->cur_test_index);
		show_test_result();
	}

}

static void wdt_irq_handle(irq_t irq, void *ctx)
{
	static int 			irq_check_time	= 0;
	auto_test_manage_t	*p_test_man		= (auto_test_manage_t *)ctx;
	struct wdt_regs		*wdt_base 		= NULL;
	ulong				wdt_cr		= -1;

	wdt_base = g_auto_wdt_config[p_test_man->cur_test_index].reg_base;
	/* check irq handle*/
	irq_check_time++;
	if (irq_check_time <= IRQ_CHECK_DEFAULT_TIMES){
		printf("dw handle wdt:%d irq.\n", p_test_man->cur_test_index);
		dw_wdt_reset(wdt_base);
		return;
	}

	irq_check_time = 0;
	dw_wdt_disenable(wdt_base);
	wdt_cr = readl(&wdt_base->wdt_cr);
	if (0 != wdt_cr && 1 != wdt_cr){
		printf("wdt:%d, stop failed!\n", p_test_man->cur_test_index);
		g_auto_wdt_config[p_test_man->cur_test_index].test_ret = WDT_STOP_FAILED;
	}
	else {
		g_auto_wdt_config[p_test_man->cur_test_index].test_ret = OK;
	}

	dsr_schedule(g_auto_test_man.dsr);

}

static int start_auto_test(auto_test_manage_t *p_test_man)
{
	struct wdt_regs *wdt_base 	= NULL;
	irq_t 			dw_wdt_irq	= -1;
	ulong			wdt_ccvr	= -1;

	dw_wdt_irq = g_auto_wdt_config[p_test_man->cur_test_index].irq_nr;
	irqc_configure_irq(dw_wdt_irq, 32, IRQ_EDGE_TRIGGERED);
	irq_register_vector(dw_wdt_irq, wdt_irq_handle, p_test_man);
	irqc_enable_irq(dw_wdt_irq);

	wdt_base = g_auto_wdt_config[p_test_man->cur_test_index].reg_base;
	dw_wdt_set_timeout(wdt_base, DEFAULT_TIMEOUT);
	dw_wdt_enable(wdt_base);
	dw_wdt_reset(wdt_base);
	wdt_ccvr = readl(&wdt_base->wdt_ccvr);
	if (DEFAULT_TIMEOUT_COUNT != wdt_ccvr){
		printf("wdt:%d, reset failed!\n", p_test_man->cur_test_index);
		g_auto_wdt_config[p_test_man->cur_test_index].test_ret = WDT_RESET_FAILED;
	}
	else{
		g_auto_wdt_config[p_test_man->cur_test_index].test_ret = OK;
	}

	return 0;
}

int wdt_cmd_handle(int argc, char **argv)
{
	int ret	= -EUSAGE;

	if (argc < 2)
		return ret;

	if (!strcmp("start", argv[1])) {
		if (g_auto_test_man.test_status <= TEST_IDLE){
			if (TEST_NOT_INIT == g_auto_test_man.test_status){
				g_auto_test_man.dsr = dsr_register(wdt_autotest_handle, (void *)&g_auto_test_man);
				if (g_auto_test_man.dsr < 0){
					return ret;
				}
			}
			g_auto_test_man.cur_test_index = 0;
			g_auto_test_man.test_status = TEST_START;
			ret = start_auto_test(&g_auto_test_man);
		}
	}
	else{
		if (!strcmp("stop", argv[1])) {
			unregist_wdt_irq(g_auto_test_man.cur_test_index);
			show_test_result();
			g_auto_test_man.test_status = TEST_IDLE;
		}
	}

	return ret;
}

MK_CMD(auto_wdt, wdt_cmd_handle, "Auto test all Designware watchDog",
	" auto_wdt start \n"
	"		-start auto test watchdog.\n"
	" auto_wdt stop \n"
	"		-stop auto test watchdog.\n"
);

