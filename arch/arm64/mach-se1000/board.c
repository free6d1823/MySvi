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

//#define SPI_MASTER_CONN_SLAVE

int soc_early_init()
{
	//clk_enable(CPU0_CLK, 1);
	//clk_enable(SYSNOC_CLK, 1);

	clk_enable(DDR0_SS_DDR_CORE_CLK, 0);
	clk_enable(DDR0_SS_DDR_CFG_CLK, 0);

	pinmux_config(52, PINMUX_FUNC(1, 0)); //peri1_uart_0_tx
	pinmux_config(53, PINMUX_FUNC(1, 0)); //peri1_uart_0_rx

	#ifdef SPI_MASTER_CONN_SLAVE
	pinmux_config(56, PINMUX_FUNC(1, 0));//peri1_spi_mst_0_clk
	pinmux_config(57, PINMUX_FUNC(1, 0));//peri1_spi_mst_0_ss0
	pinmux_config(59, PINMUX_FUNC(1, 0));//peri1_spi_mst_0_tx
	pinmux_config(58, PINMUX_FUNC(1, 0));//peri1_spi_mst_0_rx

	pinmux_config(65, PINMUX_FUNC(2, 0));//peri1_spi_slv_0_clk
	pinmux_config(66, PINMUX_FUNC(2, 0));//peri1_spi_slv_0_ss_in
	pinmux_config(68, PINMUX_FUNC(3, 0));//peri1_spi_slv_0_tx
	pinmux_config(67, PINMUX_FUNC(3, 0));//peri1_spi_slv_0_rx
	#endif

    	#ifdef PWM_CONN
    	pinmux_config(60, PINMUX_FUNC(2, 0));//peri1_dw_pw0
    	pinmux_config(87, PINMUX_FUNC(2, 0));//peri1_dw_pw1
    	#endif

	return 0;
}
