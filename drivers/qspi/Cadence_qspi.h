#ifndef __CADENCE_QSPI_H__
#define __CADENCE_QSPI_H__

#include <target/utils.h>
#include <stdbool.h>
#include <asm/io.h>

#define CQSPI_IS_ADDR(cmd_len)		(cmd_len > 1 ? 1 : 0)

#define CQSPI_NO_DECODER_MAX_CS		4
#define CQSPI_DECODER_MAX_CS		16
#define CQSPI_READ_CAPTURE_MAX_DELAY	16

#define ARCH_DMA_MINALIGN 16
#define malloc(s) heap_aligned_alloc(ARCH_DMA_MINALIGN, s)
#define free {}


#define CQSPI_REG_POLL_US			1 /* 1us */
#define CQSPI_REG_RETRY				10000
#define CQSPI_POLL_IDLE_RETRY			3

/* Transfer mode */
#define CQSPI_INST_TYPE_SINGLE			0
#define CQSPI_INST_TYPE_DUAL			1
#define CQSPI_INST_TYPE_QUAD			2

#define CQSPI_STIG_DATA_LEN_MAX			8

#define CQSPI_DUMMY_CLKS_PER_BYTE		8
#define CQSPI_DUMMY_BYTES_MAX			4

/****************************************************************************
 * Controller's configuration and status register (offset from QSPI_BASE)
 ****************************************************************************/
#define	CQSPI_REG_CONFIG			0x00
#define	CQSPI_REG_CONFIG_ENABLE			BIT(0)
#define	CQSPI_REG_CONFIG_CLK_POL		BIT(1)
#define	CQSPI_REG_CONFIG_CLK_PHA		BIT(2)
#define	CQSPI_REG_CONFIG_DIRECT			BIT(7)
#define	CQSPI_REG_CONFIG_DECODE			BIT(9)
#define	CQSPI_REG_CONFIG_DMA			BIT(15)
#define	CQSPI_REG_CONFIG_XIP_IMM		BIT(18)
#define	CQSPI_REG_CONFIG_CHIPSELECT_LSB		10
#define	CQSPI_REG_CONFIG_BAUD_LSB		19
#define	CQSPI_REG_CONFIG_IDLE_LSB		31
#define	CQSPI_REG_CONFIG_CHIPSELECT_MASK	0xF
#define	CQSPI_REG_CONFIG_BAUD_MASK		0xF

#define	CQSPI_REG_RD_INSTR			0x04
#define	CQSPI_REG_RD_INSTR_OPCODE_LSB		0
#define	CQSPI_REG_RD_INSTR_TYPE_INSTR_LSB	8
#define	CQSPI_REG_RD_INSTR_TYPE_ADDR_LSB	12
#define	CQSPI_REG_RD_INSTR_TYPE_DATA_LSB	16
#define	CQSPI_REG_RD_INSTR_MODE_EN_LSB		20
#define	CQSPI_REG_RD_INSTR_DUMMY_LSB		24
#define	CQSPI_REG_RD_INSTR_TYPE_INSTR_MASK	0x3
#define	CQSPI_REG_RD_INSTR_TYPE_ADDR_MASK	0x3
#define	CQSPI_REG_RD_INSTR_TYPE_DATA_MASK	0x3
#define	CQSPI_REG_RD_INSTR_DUMMY_MASK		0x1F

#define	CQSPI_REG_WR_INSTR			0x08
#define	CQSPI_REG_WR_INSTR_OPCODE_LSB		0

#define	CQSPI_REG_DELAY				0x0C
#define	CQSPI_REG_DELAY_TSLCH_LSB		0
#define	CQSPI_REG_DELAY_TCHSH_LSB		8
#define	CQSPI_REG_DELAY_TSD2D_LSB		16
#define	CQSPI_REG_DELAY_TSHSL_LSB		24
#define	CQSPI_REG_DELAY_TSLCH_MASK		0xFF
#define	CQSPI_REG_DELAY_TCHSH_MASK		0xFF
#define	CQSPI_REG_DELAY_TSD2D_MASK		0xFF
#define	CQSPI_REG_DELAY_TSHSL_MASK		0xFF

#define	CQSPI_REG_RD_DATA_CAPTURE		0x10
#define	CQSPI_REG_RD_DATA_CAPTURE_BYPASS	BIT(0)
#define	CQSPI_REG_RD_DATA_CAPTURE_DELAY_LSB	1
#define	CQSPI_REG_RD_DATA_CAPTURE_DELAY_MASK	0xF

#define	CQSPI_REG_SIZE				0x14
#define	CQSPI_REG_SIZE_ADDRESS_LSB		0
#define	CQSPI_REG_SIZE_PAGE_LSB			4
#define	CQSPI_REG_SIZE_BLOCK_LSB		16
#define	CQSPI_REG_SIZE_ADDRESS_MASK		0xF
#define	CQSPI_REG_SIZE_PAGE_MASK		0xFFF
#define	CQSPI_REG_SIZE_BLOCK_MASK		0x3F

#define	CQSPI_REG_SRAMPARTITION			0x18
#define	CQSPI_REG_INDIRECTTRIGGER		0x1C

#define CQSPI_DMA_CONFIG			0x20
#define CQSPI_DMA_CONFIG_SINGLE		0
#define CQSPI_DMA_CONFIG_BUST		8

#define	CQSPI_REG_REMAP				0x24
#define	CQSPI_REG_MODE_BIT			0x28

#define	CQSPI_REG_SDRAMLEVEL			0x2C
#define	CQSPI_REG_SDRAMLEVEL_RD_LSB		0
#define	CQSPI_REG_SDRAMLEVEL_WR_LSB		16
#define	CQSPI_REG_SDRAMLEVEL_RD_MASK		0xFFFF
#define	CQSPI_REG_SDRAMLEVEL_WR_MASK		0xFFFF

#define	CQSPI_REG_IRQSTATUS			0x40
#define	CQSPI_REG_IRQMASK			0x44

#define	CQSPI_REG_INDIRECTRD			0x60
#define	CQSPI_REG_INDIRECTRD_START		BIT(0)
#define	CQSPI_REG_INDIRECTRD_CANCEL		BIT(1)
#define	CQSPI_REG_INDIRECTRD_INPROGRESS		BIT(2)
#define	CQSPI_REG_INDIRECTRD_DONE		BIT(5)

#define	CQSPI_REG_INDIRECTRDWATERMARK		0x64
#define	CQSPI_REG_INDIRECTRDSTARTADDR		0x68
#define	CQSPI_REG_INDIRECTRDBYTES		0x6C

#define	CQSPI_REG_CMDCTRL			0x90
#define	CQSPI_REG_CMDCTRL_EXECUTE		BIT(0)
#define	CQSPI_REG_CMDCTRL_INPROGRESS		BIT(1)
#define	CQSPI_REG_CMDCTRL_DUMMY_LSB		7
#define	CQSPI_REG_CMDCTRL_WR_BYTES_LSB		12
#define	CQSPI_REG_CMDCTRL_WR_EN_LSB		15
#define	CQSPI_REG_CMDCTRL_ADD_BYTES_LSB		16
#define	CQSPI_REG_CMDCTRL_ADDR_EN_LSB		19
#define	CQSPI_REG_CMDCTRL_RD_BYTES_LSB		20
#define	CQSPI_REG_CMDCTRL_RD_EN_LSB		23
#define	CQSPI_REG_CMDCTRL_OPCODE_LSB		24
#define	CQSPI_REG_CMDCTRL_DUMMY_MASK		0x1F
#define	CQSPI_REG_CMDCTRL_WR_BYTES_MASK		0x7
#define	CQSPI_REG_CMDCTRL_ADD_BYTES_MASK	0x3
#define	CQSPI_REG_CMDCTRL_RD_BYTES_MASK		0x7
#define	CQSPI_REG_CMDCTRL_OPCODE_MASK		0xFF

#define	CQSPI_REG_INDIRECTWR			0x70
#define	CQSPI_REG_INDIRECTWR_START		BIT(0)
#define	CQSPI_REG_INDIRECTWR_CANCEL		BIT(1)
#define	CQSPI_REG_INDIRECTWR_INPROGRESS		BIT(2)
#define	CQSPI_REG_INDIRECTWR_DONE		BIT(5)

#define	CQSPI_REG_INDIRECTWRWATERMARK		0x74
#define	CQSPI_REG_INDIRECTWRSTARTADDR		0x78
#define	CQSPI_REG_INDIRECTWRBYTES		0x7C

#define	CQSPI_REG_CMDADDRESS			0x94
#define	CQSPI_REG_CMDREADDATALOWER		0xA0
#define	CQSPI_REG_CMDREADDATAUPPER		0xA4
#define	CQSPI_REG_CMDWRITEDATALOWER		0xA8
#define	CQSPI_REG_CMDWRITEDATAUPPER		0xAC

#define	CQSPI_REG_MODULE_ID			0xFC

#define CQSPI_REG_IS_IDLE(base)					\
	((readl(base + CQSPI_REG_CONFIG) >>		\
		CQSPI_REG_CONFIG_IDLE_LSB) & 0x1)

#define CQSPI_GET_RD_SRAM_LEVEL(reg_base)			\
	(((readl(reg_base + CQSPI_REG_SDRAMLEVEL)) >>	\
	CQSPI_REG_SDRAMLEVEL_RD_LSB) & CQSPI_REG_SDRAMLEVEL_RD_MASK)

#define CQSPI_GET_WR_SRAM_LEVEL(reg_base)			\
	(((readl(reg_base + CQSPI_REG_SDRAMLEVEL)) >>	\
	CQSPI_REG_SDRAMLEVEL_WR_LSB) & CQSPI_REG_SDRAMLEVEL_WR_MASK)


struct cadence_spi_platdata {
	unsigned int	max_hz;
	void		*regbase;
	void		*ahbbase;
	bool		is_decoded_cs;
	bool		dma_enable;
	u32		fifo_depth;
	u32		fifo_width;
	u32		trigger_address;

	/* Flash parameters */
	u32		page_size;
	u32		block_size;
	u32		tshsl_ns;
	u32		tsd2d_ns;
	u32		tchsh_ns;
	u32		tslch_ns;
};

struct cadence_spi_priv {
	void		*regbase;
	void		*ahbbase;
	size_t		cmd_len;
	u8		cmd_buf[32];
	size_t		data_len;

	int		qspi_is_init;
	unsigned int	qspi_calibrated_hz;
	unsigned int	qspi_calibrated_cs;
	unsigned int	previous_hz;
};

/* Functions call declaration */
void cadence_qspi_apb_controller_init(struct cadence_spi_platdata *plat);
void cadence_qspi_apb_controller_enable(void *reg_base_addr);
void cadence_qspi_apb_controller_disable(void *reg_base_addr);

int cadence_qspi_apb_command_read(void *reg_base_addr,
	unsigned int cmdlen, const u8 *cmdbuf, unsigned int rxlen, u8 *rxbuf);
int cadence_qspi_apb_command_write(void *reg_base_addr,
	unsigned int cmdlen, const u8 *cmdbuf,
	unsigned int txlen,  const u8 *txbuf);

int cadence_qspi_apb_indirect_read_setup(struct cadence_spi_platdata *plat,
	unsigned int cmdlen, unsigned int rx_width, const u8 *cmdbuf);
int cadence_qspi_apb_indirect_read_execute(struct cadence_spi_platdata *plat,
	unsigned int rxlen, u8 *rxbuf);
int cadence_qspi_apb_indirect_write_setup(struct cadence_spi_platdata *plat,
	unsigned int cmdlen, unsigned int tx_width, const u8 *cmdbuf);
int cadence_qspi_apb_indirect_write_execute(struct cadence_spi_platdata *plat,
	unsigned int txlen, const u8 *txbuf);
int cadence_qspi_apb_dma_setup(struct cadence_spi_platdata *plat,
	uint singleBytes, uint burstBytes);
int cadence_qspi_apb_dma_disable(struct cadence_spi_platdata *plat);

void cadence_qspi_apb_chipselect(void *reg_base,
	unsigned int chip_select, unsigned int decoder_enable);
void cadence_qspi_apb_set_clk_mode(void *reg_base, uint mode);
void cadence_qspi_apb_config_baudrate_div(void *reg_base,
	unsigned int ref_clk_hz, unsigned int sclk_hz);
void cadence_qspi_apb_delay(void *reg_base,
	unsigned int ref_clk, unsigned int sclk_hz,
	unsigned int tshsl_ns, unsigned int tsd2d_ns,
	unsigned int tchsh_ns, unsigned int tslch_ns);
void cadence_qspi_apb_enter_xip(void *reg_base, char xip_dummy);
void cadence_qspi_apb_readdata_capture(void *reg_base,
	unsigned int bypass, unsigned int delay);

#endif /* __CADENCE_QSPI_H__ */



