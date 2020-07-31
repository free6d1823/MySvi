#include <target/utils.h>
#include <target/clk.h>


//fixme: dont use CONFIG_CLK_DRIVER
#ifdef CONFIG_CLK_DRIVER

#define PINMUX_FUNC(func, ds) \
	((func << 12) | (ds << 8))

#define ADDR(gpio) (0x58200000 + \
            ((gpio >= 94 ? gpio - 94 + 0x2000 : \
             (gpio >= 32 ? gpio - 32 + 0x1000 : gpio)) << 2))

#define pinmux_config(gpio, cfg) writel(cfg, ADDR(gpio))

#else

#define pinmux_config(gpio, cfg)

#endif

int soc_early_init()
{
	//clk_enable(CPU0_CLK, 1);
	//clk_enable(SYSNOC_CLK, 1);

	pinmux_config(57, PINMUX_FUNC(1, 0)); //peri1_uart_1_tx
	pinmux_config(58, PINMUX_FUNC(1, 0)); //peri1_uart_1_rx

	return 0;
}
