/*
 */
#ifndef __QDF2400_TLMM_H_INCLUDE__
#define __QDF2400_TLMM_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>
#include <target/regdef.h>
#include <asm/hal/HALhwio.h>
#include <asm/mach/hal/HALtlmmHWIO.h>

#define TLMM_NR_GPIOS		150

#ifndef __ASSEMBLY__

#define TLMM_GPIO_PULL(pull)					\
	(((pull) << HWIO_TLMM_GPIO_CFGn_GPIO_PULL_SHFT) &	\
		    HWIO_TLMM_GPIO_CFGn_GPIO_PULL_BMSK)
#define TLMM_GPIO_DRIVE(drive)					\
	(((drive) << HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_SHFT) &	\
		     HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_BMSK)
#define TLMM_GPIO_FUNC(func)					\
	(((func) << HWIO_TLMM_GPIO_CFGn_FUNC_SEL_SHFT) &	\
		    HWIO_TLMM_GPIO_CFGn_FUNC_SEL_BMSK)
#define TLMM_GPIO_DIR(dir)					\
	(((dir) << HWIO_TLMM_GPIO_CFGn_GPIO_OE_SHFT) &		\
		   HWIO_TLMM_GPIO_CFGn_GPIO_OE_BMSK)

/* ======================================================================
   The following macro takes the configuration values from the BSP format
   used by the driver and restructures them to fit the format of the
   configuration registers for this target.
   ----------------------------------------------------------------------*/
#define TLMM_GPIO_CFG(cfg)					\
	((uint32_t)(TLMM_GPIO_PULL(GPIO_DECODE_PULL(cfg)) |	\
		    TLMM_GPIO_FUNC(GPIO_DECODE_FUNC(cfg)) |	\
		    TLMM_GPIO_DRIVE(GPIO_DECODE_DRIVE(cfg)) |	\
		    TLMM_GPIO_DIR(GPIO_DECODE_DIR(cfg))))

#define tlmm_write_config(gpio, cfg)				\
	HWIO_OUTI(TLMM_GPIO_CFGn, gpio, cfg)
#define tlmm_read_config(gpio)					\
	HWIO_INI(TLMM_GPIO_CFGn, gpio)

#define tlmm_config_pull(gpio, pull)				\
	do {							\
		uint32_t cfg = tlmm_read_config(gpio);		\
		cfg &= ~HWIO_TLMM_GPIO_CFGn_GPIO_PULL_BMSK;	\
		cfg |= TLMM_GPIO_PULL(pull);			\
		tlmm_write_config(gpio,	cfg);			\
	} while (0)
#define tlmm_config_func(gpio, func)				\
	do {							\
		uint32_t cfg = tlmm_read_config(gpio);		\
		cfg &= ~HWIO_TLMM_GPIO_CFGn_FUNC_SEL_BMSK;	\
		cfg |= TLMM_GPIO_FUNC(func);			\
		tlmm_write_config(gpio, cfg);			\
	} while (0)
#define tlmm_config_drive(gpio, drive)				\
	do {							\
		uint32_t cfg = tlmm_read_config(gpio);		\
		cfg &= ~HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_BMSK;	\
		cfg |= TLMM_GPIO_DRIVE(drive);			\
		tlmm_write_config(gpio, cfg);			\
	} while (0)
#define tlmm_config_dir(gpio, dir)				\
	do {							\
		uint32_t cfg = tlmm_read_config(gpio);		\
                cfg &= ~HWIO_TLMM_GPIO_CFGn_GPIO_OE_SHFT;	\
		cfg |= TLMM_GPIO_DIR(dir);			\
		tlmm_write_config(gpio, cfg);			\
	} while (0)

#define TLMM_GPIO_IN(val)					\
	(((!!val) << HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_SHFT) &	\
		     HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_BMSK)
#define TLMM_GPIO_OUT(val)					\
	(((!!val) << HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT) &	\
		     HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK)

#define tlmm_read_input(gpio)					\
	(!!HWIO_INMI(TLMM_GPIO_IN_OUTn, gpio,			\
		     _BV(HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_SHFT)))
#define tlmm_read_output(gpio, val)				\
	(!!HWIO_INMI(TLMM_GPIO_IN_OUTn, gpio,			\
		     _BV(HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT)))
#define tlmm_write_output(gpio, val)				\
	HWIO_OUTMI(TLMM_GPIO_IN_OUTn, gpio,			\
		   _BV(HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT),	\
		   TLMM_GPIO_OUT(val))

#define tlmm_write_phase_flags(flags)				\
	HWIO_OUT(TLMM_PHASE_FLAGS, flags)


#define tlmm_intr_trigger(gpio)				\
	HWIO_OUTMI(TLMM_GPIO_INTR_STATUSn, gpio,				\
			HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_BMSK,	\
			(1) << HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_SHFT)

#define tlmm_intr_clear(gpio)				\
	HWIO_OUTMI(TLMM_GPIO_INTR_STATUSn, gpio,				\
			HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_BMSK,	\
			(0) << HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_SHFT)

#define tlmm_intr_status(gpio)				\
	HWIO_INMI(TLMM_GPIO_INTR_STATUSn, gpio, 1)

#define tlmm_intr_enable_raw(gpio)				\
	HWIO_OUTMI(TLMM_GPIO_INTR_CFGn, gpio, 				\
			HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_BMSK,	\
			(1) << HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_SHFT)

#define tlmm_intr_enable(gpio)				\
	HWIO_OUTMI(TLMM_GPIO_INTR_CFGn, gpio, 				\
			HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_BMSK,	\
			(1) << HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_SHFT)

#define tlmm_intr_disable(gpio)				\
	HWIO_OUTMI(TLMM_GPIO_INTR_CFGn, gpio, 				\
			HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_BMSK,	\
			(0) << HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_SHFT)

#define tlmm_intr_dect_config(gpio, config)				\
	HWIO_OUTMI(TLMM_GPIO_INTR_CFGn, gpio, 				\
			HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_BMSK,	\
			(config) << HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_SHFT)

#define tlmm_intr_pol_config(gpio, config)                 \
	HWIO_OUTMI(TLMM_GPIO_INTR_CFGn,                        \
			   gpio,                                       \
			   HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_BMSK, \
			   (config) << HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_SHFT)

#define tlmm_intr_proc(gpio, proc)                        \
	HWIO_OUTMI(TLMM_GPIO_INTR_CFGn,                       \
			   gpio,                                      \
			   HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_BMSK, \
			   (proc) << HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_SHFT)

#define tlmm_intr_dir_sel_imc_config(n, gpio)                  \
	HWIO_OUTMI(TLMM_DIR_CONN_INTRn_CFG_IMC,                    \
			   n,                                              \
			   HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_GPIO_SEL_BMSK, \
			   (gpio) << HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_GPIO_SEL_SHFT)

#define tlmm_intr_dir_sel_hmss_config(n, gpio)                  \
	HWIO_OUTMI(TLMM_DIR_CONN_INTRn_CFG_HMSS,                    \
			   n,                                               \
			   HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_GPIO_SEL_BMSK, \
			   (gpio) << HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_GPIO_SEL_SHFT)

#define tlmm_intr_dir_pol_imc_config(n, pol)                   \
	HWIO_OUTMI(TLMM_DIR_CONN_INTRn_CFG_IMC,                    \
			   n,                                              \
			   HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_POLARITY_BMSK, \
			   (pol) << HWIO_TLMM_DIR_CONN_INTRn_CFG_IMC_POLARITY_SHFT)

#define tlmm_intr_dir_pol_hmss_config(n, pol)                   \
	HWIO_OUTMI(TLMM_DIR_CONN_INTRn_CFG_HMSS,                    \
			   n,                                               \
			   HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_POLARITY_BMSK, \
			   (pol) << HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_POLARITY_SHFT)

/*=======================================================================
    Function prototypes that are available to the TLMM driver.
  =======================================================================*/
void tlmm_config_port(uint32_t gpio, uint32_t cfg);

void tlmm_config_phase_flags(void);
void tlmm_output_phase_flags(uint32_t flags);

/* ======================================================================
                     TYPES AVAILABLE TO THE TLMM DRIVER
   ======================================================================*/

typedef enum
{
  HAL_TLMM_USER_1 = 0,
  HAL_TLMM_USER_2,
  HAL_TLMM_OUTPUT_LOW,
  HAL_TLMM_OUTPUT_HIGH,
  HAL_TLMM_OUTPUT_SZ = 0x7FFFFFFF,
}HAL_tlmm_OutputValueType;

#define HAL_RMT_VAL(config)     \
         ((0x20000000&(config))?(((config)&0x1E00000)>>0x15):(((config)&0xF0)>>4))
#define HAL_GPIO_OUTVAL HAL_RMT_VAL

#define ARCH_NR_GPIOS				TLMM_NR_GPIOS
#define arch_gpio_config_port(gpio, cfg)	tlmm_config_port(gpio, cfg)
#define arch_gpio_read_input(gpio)		tlmm_read_input(gpio)
#define arch_gpio_read_output(gpio)		tlmm_read_output(gpio)
#define arch_gpio_write_output(gpio, val)	tlmm_write_output(gpio, val)

#endif /* __ASSEMBLY__ */

/* PIN multiplexer functions, from tlmm_gpio_pinmux_table.xlsx, associated
 * PIN direction is recorded as comments.
 */
#define GPIO0_FUNC_BLSP1_I2C0_SDA			1 /* L */
#define GPIO1_FUNC_BLSP1_I2C0_SCL			1 /* L */
#define GPIO2_FUNC_BLSP1_I2C1_SDA			1 /* L */
#define GPIO3_FUNC_BLSP1_I2C1_SCL			1 /* L */
#define GPIO4_FUNC_BLSP1_I2C2_SDA			1 /* L */
#define GPIO5_FUNC_BLSP1_I2C2_SCL			1 /* L */
#define GPIO6_FUNC_BLSP1_I2C3_SDA			1 /* L */
#define GPIO7_FUNC_BLSP1_I2C3_SCL			1 /* L */
#define GPIO8_FUNC_BLSP2_I2C0_SDA			1 /* L */
#define GPIO9_FUNC_BLSP2_I2C0_SCL			1 /* L */
#define GPIO10_FUNC_BLSP2_I2C1_SDA			1 /* L */
#define GPIO11_FUNC_BLSP2_I2C1_SCL			1 /* L */
#define GPIO12_FUNC_BLSP2_I2C2_SDA			1 /* L */
#define GPIO13_FUNC_BLSP2_I2C2_SCL			1 /* L */
#define GPIO14_FUNC_BLSP2_I2C3_SDA			1 /* L */
#define GPIO15_FUNC_BLSP2_I2C3_SCL			1 /* L */

#define GPIO4_FUNC_I2C_SLV3_SDA				2 /* L */
#define GPIO5_FUNC_I2C_SLV3_SCL				2 /* L */
#define GPIO6_FUNC_I2C_SLV2_SDA				2 /* L */
#define GPIO7_FUNC_I2C_SLV2_SCL				2 /* L */
#define GPIO12_FUNC_I2C_SLV1_SDA			2 /* L */
#define GPIO13_FUNC_I2C_SLV1_SCL			2 /* L */
#define GPIO14_FUNC_I2C_SLV0_SDA			2 /* L */
#define GPIO15_FUNC_I2C_SLV0_SCL			2 /* L */

#define GPIO16_FUNC_BLSP3_AC_UART0_TX			1 /* O */
#define GPIO17_FUNC_BLSP3_AC_UART0_RX			1 /* I */
#define GPIO18_FUNC_BLSP3_AC_UART0_RFR_N		1 /* O */
#define GPIO19_FUNC_BLSP3_AC_UART0_CTS_N		1 /* I */
#define GPIO24_FUNC_BLSP3_AC_UART1_TX			1 /* O */
#define GPIO25_FUNC_BLSP3_AC_UART1_RX			1 /* I */
#define GPIO26_FUNC_BLSP3_AC_UART1_RFR_N		1 /* O */
#define GPIO27_FUNC_BLSP3_AC_UART1_CTS_N		1 /* I */
#define GPIO28_FUNC_BLSP3_AC_UART2_TX			1 /* O */
#define GPIO29_FUNC_BLSP3_AC_UART2_RX			1 /* I */
#define GPIO30_FUNC_BLSP3_AC_UART2_RFR_N		1 /* O */
#define GPIO31_FUNC_BLSP3_AC_UART2_CTS_N		1 /* I */
#define GPIO124_FUNC_BLSP3_AC_UART3_TX			1 /* O */
#define GPIO125_FUNC_BLSP3_AC_UART3_RX			1 /* I */
#define GPIO126_FUNC_BLSP3_AC_UART3_RFR_N		1 /* O */
#define GPIO127_FUNC_BLSP3_AC_UART3_CTS_N		1 /* I */

#define GPIO16_FUNC_BLSP0_Q_UART2_TX			2 /* O */
#define GPIO17_FUNC_BLSP0_Q_UART2_RX			2 /* I */
#define GPIO18_FUNC_BLSP0_Q_UART2_RFR_N			2 /* O */
#define GPIO19_FUNC_BLSP0_Q_UART2_CTS_N			2 /* I */
#define GPIO20_FUNC_BLSP0_Q_UART3_TX			1 /* O */
#define GPIO21_FUNC_BLSP0_Q_UART3_RX			1 /* I */
#define GPIO22_FUNC_BLSP0_Q_UART3_RFR_N			1 /* O */
#define GPIO23_FUNC_BLSP0_Q_UART3_CTS_N			1 /* I */
#define GPIO24_FUNC_BLSP0_Q_UART0_TX			1 /* O */
#define GPIO25_FUNC_BLSP0_Q_UART0_RX			1 /* I */
#define GPIO26_FUNC_BLSP0_Q_UART0_RFR_N			1 /* O */
#define GPIO27_FUNC_BLSP0_Q_UART0_CTS_N			1 /* I */
#define GPIO28_FUNC_BLSP0_Q_UART1_TX			1 /* O */
#define GPIO29_FUNC_BLSP0_Q_UART1_RX			1 /* I */
#define GPIO30_FUNC_BLSP0_Q_UART1_RFR_N			1 /* O */
#define GPIO31_FUNC_BLSP0_Q_UART1_CTS_N			1 /* I */

#define GPIO32_FUNC_BLSP0_SPI0_CS1_N_B			1 /* Z */
#define GPIO33_FUNC_BLSP0_SPI0_CS2_N_B			1 /* Z */
#define GPIO34_FUNC_BLSP0_SPI0_CS3_N_B			1 /* Z */
#define GPIO40_FUNC_BLSP0_SPI0_MISO			1 /* B */
#define GPIO41_FUNC_BLSP0_SPI0_MOSI			1 /* L */
#define GPIO42_FUNC_BLSP0_SPI0_CLK			1 /* L */
#define GPIO43_FUNC_BLSP0_SPI0_CS0_N			1 /* L */
#define GPIO48_FUNC_BLSP0_SPI0_CS1_N_A			2 /* Z */
#define GPIO49_FUNC_BLSP0_SPI0_CS2_N_A			2 /* Z */
#define GPIO50_FUNC_BLSP0_SPI0_CS3_N_A			2 /* Z */
#define GPIO90_FUNC_BLSP0_SPI0_CS1_N_C			1 /* Z */
#define GPIO97_FUNC_BLSP0_SPI0_CS2_N_C			1 /* Z */
#define GPIO98_FUNC_BLSP0_SPI0_CS3_N_C			1 /* Z */

#define GPIO32_FUNC_BLSP3_SPI0_MISO			1 /* B */
#define GPIO33_FUNC_BLSP3_SPI0_MOSI			1 /* L */
#define GPIO34_FUNC_BLSP3_SPI0_CLK			1 /* L */
#define GPIO89_FUNC_BLSP3_SPI0_CS0_N			1 /* L */

#define GPIO36_FUNC_BLSP3_SPI1_MISO			1 /* B */
#define GPIO37_FUNC_BLSP3_SPI1_MOSI			1 /* L */
#define GPIO38_FUNC_BLSP3_SPI1_CLK			1 /* L */
#define GPIO39_FUNC_BLSP3_SPI1_CS0_N			1 /* L */

#define GPIO44_FUNC_BLSP0_SPI1_MISO			1 /* B */
#define GPIO45_FUNC_BLSP0_SPI1_MOSI			1 /* L */
#define GPIO46_FUNC_BLSP0_SPI1_CLK			1 /* L */
#define GPIO47_FUNC_BLSP0_SPI1_CS0_N			1 /* L */
#define GPIO48_FUNC_BLSP0_SPI1_CS1_N			1 /* Z */
#define GPIO49_FUNC_BLSP0_SPI1_CS2_N			1 /* Z */
#define GPIO50_FUNC_BLSP0_SPI1_CS3_N			1 /* Z */

#define GPIO103_FUNC_SPI_SLV_SCLK			1 /* I */
#define GPIO104_FUNC_SPI_SLV_MOSI			1 /* I */
#define GPIO105_FUNC_SPI_SLV_MISO			1 /* O */
#define GPIO106_FUNC_SPI_SLV_CS_N			1 /* I */

#define GPIO51_FUNC_SDC0_CLK				1 /* L */
#define GPIO52_FUNC_SDC0_CMD				1 /* B */
#define GPIO53_FUNC_SDC0_DATA_0				1 /* B */
#define GPIO54_FUNC_SDC0_DATA_1				1 /* B */
#define GPIO55_FUNC_SDC0_DATA_2				1 /* B */
#define GPIO56_FUNC_SDC0_DATA_3				1 /* B */
#define GPIO57_FUNC_SDC0_DATA_4				1 /* B */
#define GPIO58_FUNC_SDC0_DATA_5				1 /* B */
#define GPIO59_FUNC_SDC0_DATA_6				1 /* B */
#define GPIO60_FUNC_SDC0_DATA_7				1 /* B */

#define GPIO57_FUNC_SDC2_DATA_0				2 /* B */
#define GPIO58_FUNC_SDC2_DATA_1				2 /* B */
#define GPIO59_FUNC_SDC2_DATA_2				2 /* B */
#define GPIO60_FUNC_SDC2_DATA_3				2 /* B */
#define GPIO61_FUNC_SDC2_CLK				1 /* L */
#define GPIO62_FUNC_SDC2_CMD				1 /* B */

#define GPIO63_FUNC_SDC1_CLK				1 /* L */
#define GPIO64_FUNC_SDC1_CMD				1 /* B */
#define GPIO65_FUNC_SDC1_DATA_0				1 /* B */
#define GPIO66_FUNC_SDC1_DATA_1				1 /* B */
#define GPIO67_FUNC_SDC1_DATA_2				1 /* B */
#define GPIO68_FUNC_SDC1_DATA_3				1 /* B */
#define GPIO69_FUNC_SDC1_DATA_4				1 /* B */
#define GPIO70_FUNC_SDC1_DATA_5				1 /* B */
#define GPIO71_FUNC_SDC1_DATA_6				1 /* B */
#define GPIO72_FUNC_SDC1_DATA_7				1 /* B */

#define GPIO69_FUNC_SDC3_DATA_0				2 /* B */
#define GPIO70_FUNC_SDC3_DATA_1				2 /* B */
#define GPIO71_FUNC_SDC3_DATA_2				2 /* B */
#define GPIO72_FUNC_SDC3_DATA_3				2 /* B */
#define GPIO73_FUNC_SDC3_CLK				1 /* L */
#define GPIO74_FUNC_SDC3_CMD				1 /* B */

#define GPIO52_FUNC_MDDRX_MNC_GPIO_OUT_0		2 /* O */
#define GPIO53_FUNC_MDDRX_MNC_GPIO_OUT_1		2 /* O */
#define GPIO54_FUNC_MDDRX_MNC_GPIO_OUT_2		2 /* O */
#define GPIO55_FUNC_MDDRX_MNC_GPIO_OUT_3		2 /* O */
#define GPIO56_FUNC_MDDRX_MNC_GPIO_OUT_4		2 /* O */
#define GPIO57_FUNC_MDDRX_MNC_GPIO_OUT_5		3 /* O */
#define GPIO58_FUNC_MDDRX_MNC_GPIO_OUT_6		3 /* O */
#define GPIO59_FUNC_MDDRX_MNC_GPIO_OUT_7		3 /* O */
#define GPIO60_FUNC_MDDRX_MNC_GPIO_OUT_8		3 /* O */
#define GPIO61_FUNC_MDDRX_MNC_GPIO_OUT_9		2 /* O */
#define GPIO62_FUNC_MDDRX_MNC_GPIO_OUT_10		2 /* O */
#define GPIO63_FUNC_MDDRX_MNC_GPIO_OUT_11		2 /* O */
#define GPIO64_FUNC_MDDRX_MNC_GPIO_IN_0			2 /* I */
#define GPIO65_FUNC_MDDRX_MNC_GPIO_IN_1			2 /* I */

#define GPIO65_FUNC_PHASEFLAGS_0			3 /* O */
#define GPIO66_FUNC_PHASEFLAGS_1			2 /* O */
#define GPIO67_FUNC_PHASEFLAGS_2			2 /* O */
#define GPIO68_FUNC_PHASEFLAGS_3			2 /* O */
#define GPIO69_FUNC_PHASEFLAGS_4			3 /* O */
#define GPIO70_FUNC_PHASEFLAGS_5			3 /* O */
#define GPIO71_FUNC_PHASEFLAGS_6			3 /* O */
#define GPIO72_FUNC_PHASEFLAGS_7			3 /* O */
#define GPIO73_FUNC_PHASEFLAGS_8			2 /* O */
#define GPIO74_FUNC_PHASEFLAGS_9			2 /* O */
#define GPIO75_FUNC_PHASEFLAGS_10			2 /* O */
#define GPIO76_FUNC_PHASEFLAGS_11			2 /* O */
#define GPIO77_FUNC_PHASEFLAGS_12			3 /* O */
#define GPIO78_FUNC_PHASEFLAGS_13			3 /* O */
#define GPIO80_FUNC_PHASEFLAGS_14			4 /* O */
#define GPIO81_FUNC_PHASEFLAGS_15			4 /* O */
#define GPIO82_FUNC_PHASEFLAGS_16			4 /* O */
#define GPIO83_FUNC_PHASEFLAGS_17			4 /* O */
#define GPIO84_FUNC_PHASEFLAGS_18			4 /* O */
#define GPIO85_FUNC_PHASEFLAGS_19			5 /* O */
#define GPIO86_FUNC_PHASEFLAGS_20			5 /* O */
#define GPIO87_FUNC_PHASEFLAGS_21			5 /* O */
#define GPIO91_FUNC_PHASEFLAGS_22			2 /* O */
#define GPIO92_FUNC_PHASEFLAGS_23			2 /* O */
#define GPIO93_FUNC_PHASEFLAGS_24			2 /* O */
#define GPIO94_FUNC_PHASEFLAGS_25			2 /* O */
#define GPIO95_FUNC_PHASEFLAGS_26			2 /* O */
#define GPIO96_FUNC_PHASEFLAGS_27			2 /* O */
#define GPIO97_FUNC_PHASEFLAGS_28			3 /* O */
#define GPIO98_FUNC_PHASEFLAGS_29			3 /* O */
#define GPIO99_FUNC_PHASEFLAGS_30			2 /* O */
#define GPIO100_FUNC_PHASEFLAGS_31			2 /* O */

#define GPIO75_FUNC_SGMII_MDC_0				1 /* O */
#define GPIO76_FUNC_SGMII_MDC_1				1 /* O */
#define GPIO77_FUNC_SGMII_MDIO_0			1 /* B */
#define GPIO78_FUNC_SGMII_MDIO_1			1 /* B */

#define GPIO77_FUNC_PLL_BIST_SYNC			2 /* L */
#define GPIO78_FUNC_HF_PLL_AUX				2 /* I */
#define GPIO79_FUNC_CC_TLMM_COMBINED_PLL_LOCK_DET	1 /* O */

#define GPIO35_FUNC_IEEE_1588_PPS_IN			1 /* I */
#define GPIO109_FUNC_IEEE_1588_PPS_OUT_0		1 /* O */
#define GPIO110_FUNC_IEEE_1588_PPS_OUT_1		1 /* O */

#define GPIO6_FUNC_DBG_BUS_OUT_DUP_3			3 /* O */
#define GPIO7_FUNC_DBG_BUS_OUT_DUP_2			3 /* O */
#define GPIO8_FUNC_DBG_BUS_OUT_DUP_1			2 /* O */
#define GPIO8_FUNC_DBG_BUS_OUT_DUP_0			2 /* O */
#define GPIO36_FUNC_DBG_BUS_IN_3			3 /* I */
#define GPIO37_FUNC_DBG_BUS_IN_2			3 /* I */
#define GPIO38_FUNC_DBG_BUS_IN_1			3 /* I */
#define GPIO39_FUNC_DBG_BUS_IN_0			3 /* I */
#define GPIO36_FUNC_DBG_BUS_OUT_3			4 /* O */
#define GPIO37_FUNC_DBG_BUS_OUT_2			4 /* O */
#define GPIO38_FUNC_DBG_BUS_OUT_1			4 /* O */
#define GPIO39_FUNC_DBG_BUS_OUT_0			4 /* O */
#define GPIO50_FUNC_DBG_BUS_IN_4			4 /* I */
#define GPIO50_FUNC_DBG_BUS_OUT_4			5 /* O */
#define GPIO80_FUNC_DBG_BUS_IN_15			2 /* I */
#define GPIO80_FUNC_DBG_BUS_OUT_15			3 /* O */
#define GPIO81_FUNC_DBG_BUS_IN_14			2 /* I */
#define GPIO81_FUNC_DBG_BUS_OUT_14			3 /* O */
#define GPIO82_FUNC_DBG_BUS_IN_13			2 /* I */
#define GPIO82_FUNC_DBG_BUS_OUT_13			3 /* O */
#define GPIO83_FUNC_DBG_BUS_IN_12			2 /* I */
#define GPIO83_FUNC_DBG_BUS_OUT_12			3 /* O */
#define GPIO84_FUNC_DBG_BUS_IN_11			2 /* I */
#define GPIO84_FUNC_DBG_BUS_OUT_11			3 /* O */
#define GPIO85_FUNC_DBG_BUS_IN_10			3 /* I */
#define GPIO85_FUNC_DBG_BUS_OUT_10			4 /* O */
#define GPIO86_FUNC_DBG_BUS_IN_9			3 /* I */
#define GPIO86_FUNC_DBG_BUS_OUT_9			4 /* O */
#define GPIO87_FUNC_DBG_BUS_IN_8			3 /* I */
#define GPIO87_FUNC_DBG_BUS_OUT_8			4 /* O */
#define GPIO88_FUNC_DBG_BUS_IN_7			2 /* I */
#define GPIO88_FUNC_DBG_BUS_OUT_7			3 /* O */
#define GPIO89_FUNC_DBG_BUS_IN_6			3 /* I */
#define GPIO89_FUNC_DBG_BUS_OUT_6			4 /* O */
#define GPIO90_FUNC_DBG_BUS_IN_5			3 /* I */
#define GPIO90_FUNC_DBG_BUS_OUT_5			4 /* O */
#define GPIO101_FUNC_DBG_LS_OUT_CLK_A			2 /* O */
#define GPIO102_FUNC_DBG_HS_OUT_CLK_A			2 /* O */
#define GPIO114_FUNC_DBG_LS_OUT_CLK_B			2 /* O */
#define GPIO115_FUNC_DBG_HS_OUT_CLK_B			2 /* O */
#define GPIO116_FUNC_DBG_BUS_IN_31			2 /* I */
#define GPIO116_FUNC_DBG_BUS_OUT_31			3 /* O */
#define GPIO117_FUNC_DBG_BUS_IN_30			2 /* I */
#define GPIO117_FUNC_DBG_BUS_OUT_30			3 /* O */
#define GPIO118_FUNC_DBG_BUS_IN_29			2 /* I */
#define GPIO118_FUNC_DBG_BUS_OUT_29			3 /* O */
#define GPIO119_FUNC_DBG_BUS_IN_28			2 /* I */
#define GPIO119_FUNC_DBG_BUS_OUT_28			3 /* O */
#define GPIO120_FUNC_DBG_BUS_IN_27			2 /* I */
#define GPIO120_FUNC_DBG_BUS_OUT_27			3 /* O */
#define GPIO121_FUNC_DBG_BUS_IN_26			2 /* I */
#define GPIO121_FUNC_DBG_BUS_OUT_26			3 /* O */
#define GPIO122_FUNC_DBG_BUS_IN_25			2 /* I */
#define GPIO122_FUNC_DBG_BUS_OUT_25			3 /* O */
#define GPIO123_FUNC_DBG_BUS_IN_24			2 /* I */
#define GPIO123_FUNC_DBG_BUS_OUT_24			3 /* O */
#define GPIO124_FUNC_DBG_BUS_IN_23			3 /* I */
#define GPIO124_FUNC_DBG_BUS_OUT_23			4 /* O */
#define GPIO125_FUNC_DBG_BUS_IN_22			3 /* I */
#define GPIO125_FUNC_DBG_BUS_OUT_22			4 /* O */
#define GPIO126_FUNC_DBG_BUS_IN_21			3 /* I */
#define GPIO126_FUNC_DBG_BUS_OUT_21			4 /* O */
#define GPIO127_FUNC_DBG_BUS_IN_20			3 /* I */
#define GPIO127_FUNC_DBG_BUS_OUT_20			4 /* O */
#define GPIO128_FUNC_DBG_BUS_IN_19			2 /* I */
#define GPIO128_FUNC_DBG_BUS_OUT_19			3 /* O */
#define GPIO129_FUNC_DBG_BUS_IN_18			2 /* I */
#define GPIO129_FUNC_DBG_BUS_OUT_18			3 /* O */
#define GPIO130_FUNC_DBG_BUS_IN_17			2 /* I */
#define GPIO130_FUNC_DBG_BUS_OUT_17			3 /* O */
#define GPIO131_FUNC_DBG_BUS_IN_16			2 /* I */
#define GPIO131_FUNC_DBG_BUS_OUT_16			3 /* O */

#define GPIO36_FUNC_QDSS_TRACEDATA_28			2 /* O */
#define GPIO37_FUNC_QDSS_TRACEDATA_29			2 /* O */
#define GPIO38_FUNC_QDSS_TRACEDATA_30			2 /* O */
#define GPIO39_FUNC_QDSS_TRACEDATA_31			2 /* O */
#define GPIO50_FUNC_QDSS_TRACEDATA_27			3 /* O */
#define GPIO79_FUNC_QDSS_CTI_TRIG_IN			2 /* I */
#define GPIO80_FUNC_QDSS_TRACEDATA_16			1 /* O */
#define GPIO81_FUNC_QDSS_TRACEDATA_17			1 /* O */
#define GPIO82_FUNC_QDSS_TRACEDATA_18			1 /* O */
#define GPIO83_FUNC_QDSS_TRACEDATA_19			1 /* O */
#define GPIO84_FUNC_QDSS_TRACEDATA_20			1 /* O */
#define GPIO85_FUNC_QDSS_TRACEDATA_21			2 /* O */
#define GPIO86_FUNC_QDSS_TRACEDATA_22			2 /* O */
#define GPIO87_FUNC_QDSS_TRACEDATA_23			2 /* O */
#define GPIO88_FUNC_QDSS_TRACEDATA_24			1 /* O */
#define GPIO89_FUNC_QDSS_TRACEDATA_25			2 /* O */
#define GPIO90_FUNC_QDSS_TRACEDATA_26			2 /* O */
#define GPIO109_FUNC_QDSS_CTI_TRIG_OUT_0		2 /* O */
#define GPIO110_FUNC_QDSS_CTI_TRIG_OUT_1		3 /* O */
#define GPIO114_FUNC_QDSS_TRACECTL			1 /* O */
#define GPIO115_FUNC_QDSS_TRACECLK			1 /* O */
#define GPIO116_FUNC_QDSS_TRACEDATA_0			1 /* O */
#define GPIO117_FUNC_QDSS_TRACEDATA_1			1 /* O */
#define GPIO118_FUNC_QDSS_TRACEDATA_2			1 /* O */
#define GPIO119_FUNC_QDSS_TRACEDATA_3			1 /* O */
#define GPIO120_FUNC_QDSS_TRACEDATA_4			1 /* O */
#define GPIO121_FUNC_QDSS_TRACEDATA_5			1 /* O */
#define GPIO122_FUNC_QDSS_TRACEDATA_6			1 /* O */
#define GPIO123_FUNC_QDSS_TRACEDATA_7			1 /* O */
#define GPIO124_FUNC_QDSS_TRACEDATA_8			2 /* O */
#define GPIO125_FUNC_QDSS_TRACEDATA_9			2 /* O */
#define GPIO126_FUNC_QDSS_TRACEDATA_10			2 /* O */
#define GPIO127_FUNC_QDSS_TRACEDATA_11			2 /* O */
#define GPIO128_FUNC_QDSS_TRACEDATA_12			1 /* O */
#define GPIO129_FUNC_QDSS_TRACEDATA_13			1 /* O */
#define GPIO130_FUNC_QDSS_TRACEDATA_14			1 /* O */
#define GPIO131_FUNC_QDSS_TRACEDATA_15			1 /* O */

#define GPIO85_FUNC_GP0_CLK				1 /* O */
#define GPIO86_FUNC_GP1_CLK				1 /* O */
#define GPIO87_FUNC_GP2_CLK				1 /* O */

#define GPIO91_FUNC_FAN_PWM_0				1 /* O */
#define GPIO92_FUNC_FAN_TACH_0				1 /* I */
#define GPIO93_FUNC_FAN_PWM_1				1 /* O */
#define GPIO94_FUNC_FAN_TACH_1				1 /* I */
#define GPIO95_FUNC_FAN_PWM_2				1 /* O */
#define GPIO96_FUNC_FAN_TACH_2				1 /* I */
#define GPIO97_FUNC_FAN_PWM_3				2 /* O */
#define GPIO98_FUNC_FAN_TACH_3				2 /* I */
#define GPIO99_FUNC_FAN_PWM_4				1 /* O */
#define GPIO100_FUNC_FAN_TACH_4				1 /* I */
#define GPIO101_FUNC_FAN_PWM_5				1 /* O */
#define GPIO102_FUNC_FAN_TACH_5				1 /* I */
#define GPIO103_FUNC_FAN_PWM_6				2 /* O */
#define GPIO104_FUNC_FAN_TACH_6				2 /* I */
#define GPIO105_FUNC_FAN_PWM_7				2 /* O */
#define GPIO106_FUNC_FAN_TACH_7				2 /* I */

#define GPIO107_FUNC_PMG_ROSC_TEST_OUT_0		1 /* O */
#define GPIO108_FUNC_PMG_ROSC_TEST_OUT_1		1 /* O */
#define GPIO110_FUNC_CRI_TMG_ROSC_SYNC_TEST_OUT_0	2 /* O */
#define GPIO111_FUNC_CRI_TMG_ROSC_SYNC_TEST_OUT_1	1 /* O */
#define GPIO112_FUNC_CRI_TMG_ROSC_DIV_TEST_OUT		1 /* O */

#define GPIO109_FUNC_ATEST_CHAR_STATUS_3		3 /* O */
#define GPIO110_FUNC_ATEST_CHAR_STATUS_2		4 /* O */
#define GPIO111_FUNC_ATEST_CHAR_STATUS_1		2 /* O */
#define GPIO112_FUNC_ATEST_CHAR_STATUS_0		2 /* O */
#define GPIO113_FUNC_ATEST_CHAR_START			2 /* I */

#define GPIO113_FUNC_OBFF_WAKE				1 /* O */

/* GPIO132-GPIO147: Software Reserved */
/* GPIO148: Reserved for PCI hot plug interrupt */
/* GPIO149: Reserved for PCI link up/down interrupt */

#include <asm/mach/tlmm_boot.h>

#endif /* __QDF2400_TLMM_H_INCLUDE__ */
