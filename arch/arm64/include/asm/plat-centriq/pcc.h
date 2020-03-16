/* Centriq PCC (Peripheral Clock Controller) driver
 */
#ifndef __PCC_CENTRIQ_H_INCLUDE__
#define __PCC_CENTRIQ_H_INCLUDE__

/* Accepts the clock outputs from GCCMW, generates the clocks
 * and the resets for the peripheral wrap hard macro.
 */
#define PCC_BLOCK_SHIFT			16
#define PCC_REG(blk, off)		\
	(PCC_BASE + ((blk) << PCC_BLOCK_SHIFT) + (off))

/* ============================================================
 * BLSP
 * ============================================================ */
#define PCC_BLSP_REG(blsp, offset)	\
	PCC_REG(PCC_BLSP##blsp, (offset))

/* BLSP generic */
#define PCC_BLSP0_BCR			PCC_BLSP_REG(0, 0x0000)
#define PCC_BLSP0_PFAB_FCLK_CBCR	PCC_BLSP_REG(0, 0x001C)
#define PCC_BLSP0_AHB_CBCR		PCC_BLSP_REG(0, 0x0020)
#define PCC_BLSP0_SLEEP_CBCR		PCC_BLSP_REG(0, 0x0024)
#define PCC_BLSP1_BCR			PCC_BLSP_REG(1, 0x0000)
#define PCC_BLSP1_PFAB_FCLK_CBCR	PCC_BLSP_REG(1, 0x0014)
#define PCC_BLSP1_AHB_CBCR		PCC_BLSP_REG(1, 0x0018)
#define PCC_BLSP1_SLEEP_CBCR		PCC_BLSP_REG(1, 0x0024)
#define PCC_BLSP2_BCR			PCC_BLSP_REG(2, 0x0000)
#define PCC_BLSP2_PFAB_FCLK_CBCR	PCC_BLSP_REG(2, 0x0014)
#define PCC_BLSP2_AHB_CBCR		PCC_BLSP_REG(2, 0x0018)
#define PCC_BLSP2_SLEEP_CBCR		PCC_BLSP_REG(2, 0x0024)
#define PCC_BLSP3_BCR			PCC_BLSP_REG(3, 0x0000)
#define PCC_BLSP3_PFAB_FCLK_CBCR	PCC_BLSP_REG(3, 0x001C)
#define PCC_BLSP3_AHB_CBCR		PCC_BLSP_REG(3, 0x0020)
#define PCC_BLSP3_SLEEP_CBCR		PCC_BLSP_REG(3, 0x0024)

/* UART */
#define PCC_UART_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_UART_CMD_RCGR(blk)		PCC_REG(blk, 0x0004) /* MND */
#define PCC_UART_MND_MASK		0xFFFF
#define PCC_UART_APPS_CBCR(blk)		PCC_REG(blk, 0x0018)

/* SPI */
#define PCC_SPI_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_SPI_CMD_RCGR(blk)		PCC_REG(blk, 0x0004) /* MND */
#define PCC_SPI_MND_MASK		0xFF
#define PCC_SPI_APPS_CBCR(blk)		PCC_REG(blk, 0x0018)

/* I2C */
#define PCC_I2C_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_I2C_CMD_RCGR(blk)		PCC_REG(blk, 0x0004)
#define PCC_I2C_APPS_CBCR(blk)		PCC_REG(blk, 0x000C)

/* ============================================================
 * Non-BLSP
 * ============================================================ */
/* I2C_SLAVE */
#define PCC_I2C_SLAVE_BCR		PCC_REG(PCC_I2C_SLAVE, 0x0000)
#define PCC_I2C0_SLV_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x0004)
#define PCC_I2C1_SLV_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x0008)
#define PCC_I2C2_SLV_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x000C)
#define PCC_I2C3_SLV_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x0010)
#define PCC_I2CSPI_PFAB_FCLK_CBCR	PCC_REG(PCC_I2C_SLAVE, 0x0014)
#define PCC_I2CSPI_S_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x001C)

/* PDM */
#define PCC_PDM_BCR			PCC_REG(PCC_PDM, 0x0000)
#define PCC_PDM2_CMD_RCGR		PCC_REG(PCC_PDM, 0x0004)
#define PCC_PDM2_CBCR			PCC_REG(PCC_PDM, 0x000C)
#define PCC_PDM_AHB_CBCR		PCC_REG(PCC_PDM, 0x0010)
#define PCC_PDM_XO4_CDIVR		PCC_REG(PCC_PDM, 0x0014)
#define PCC_PDM_XO4_CBCR		PCC_REG(PCC_PDM, 0x0018)

/* SPI_SLAVE */
#define PCC_PERIPH_SPI_BCR		PCC_REG(PCC_SPI_SLAVE, 0x0000)
/* SPI_SLAVE */
#define PCC_SPI_SLAVE_BCR		PCC_REG(PCC_SPI_SLAVE2, 0x0000)
#define PCC_PERIPH_SPI_CMD_RCGR		PCC_REG(PCC_SPI_SLAVE2, 0x0004)
#define PCC_PERIPH_SPI_CORE_CBCR	PCC_REG(PCC_SPI_SLAVE2, 0x000C)
#define PCC_SPI_AHB_M_CBCR		PCC_REG(PCC_SPI_SLAVE2, 0x0010)
#define PCC_SPI_SLV_AHB_CBCR		PCC_REG(PCC_SPI_SLAVE2, 0x0014)

/* PRNG */
#define PCC_PRNG0_BCR(blk)		PCC_REG(PCC_PRNG0, 0x0000)
#define PCC_PRNG0_AHB_CBCR(blk)		PCC_REG(PCC_PRNG0, 0x0004)
#define PCC_PRNG1_BCR(blk)		PCC_REG(PCC_PRNG1, 0x0000)
#define PCC_PRNG1_AHB_CBCR(blk)		PCC_REG(PCC_PRNG1, 0x0004)
#define PCC_PRNG_AHB_CBCR		PCC_REG(PCC_PRNG1, 0x0044)
#define PCC_PRNG_PFAB_FCLK_CBCR		PCC_REG(PCC_PRNG1, 0x0048)

/* PERIPH_FAB */
#define PCC_PFAB_BCR				PCC_REG(PCC_PFAB, 0x0000)
#define PCC_PFAB_CMD_RCGR			PCC_REG(PCC_PFAB, 0x0004)
#define PCC_PFAB_CORE_CBCR			PCC_REG(PCC_PFAB, 0x0010)
#define PCC_PFAB_SFAB_FCLK_CBCR			PCC_REG(PCC_PFAB, 0x0028)
#define PCC_PFAB_SFAB_M_AXI_CBCR		PCC_REG(PCC_PFAB, 0x002C)
#define PCC_PFAB_UPHY_XPU_AHB_FCLK_CBCR		PCC_REG(PCC_PFAB, 0x0030)
#define PCC_PFAB_CFG_AHB_CBCR			PCC_REG(PCC_PFAB, 0x0050)
#define PCC_SFAB_PFAB_QSMMUV3_CLIENT_CBCR	PCC_REG(PCC_PFAB, 0x0054)

/* SDCC */
#define PCC_SDCC_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_SDCC_APPS_CMD_RCGR(blk)	PCC_REG(blk, 0x0004) /* MND */
#define PCC_SDCC_APPS_MND_MASK		0xFF
#define PCC_SDCC_AXI_CBCR(blk)		PCC_REG(blk, 0x0018)
#define PCC_SDCC_AHB_CBCR(blk)		PCC_REG(blk, 0x001C)
#define PCC_SDCC_APPS_CBCR(blk)		PCC_REG(blk, 0x0020)
#define PCC_SDCC_PFAB_FCLK_CBCR(blk)	PCC_REG(blk, 0x0030)

/* USB2 */
#define PCC_USB2_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_USB2_PHY_AHB_CBCR(blk)	PCC_REG(blk, 0x0008)
#define PCC_USB2_MSTR_CBCR(blk)		PCC_REG(blk, 0x000C)
#define PCC_USB2_SLEEP_CBCR(blk)	PCC_REG(blk, 0x0010)
#define PCC_USB2_MOCK_UTMI_CBCR(blk)	PCC_REG(blk, 0x0014)
#define PCC_USB2_PHY_RESET(blk)		PCC_REG(blk, 0x0100)
#define PCC_USB2_PHY_SLEEP_CBCR(blk)	PCC_REG(blk, 0x0104)

/* USB2 special */
#define PCC_USB2_MSTR_CMD_RCGR		PCC_REG(PCC_USB2_MSTR, 0x0000)
#define PCC_USB2_MSTR_AHB_CBCR		PCC_REG(PCC_USB2_MSTR, 0x0008)
#define PCC_USB2_PFAB_FCLK_CBCR		PCC_REG(PCC_USB2_PFAB, 0x0000)

/* MISC */
#define PCC_ABH2MSM_PFAB_CFG_AHB_CBCR	PCC_REG(PCC_MISC, 0x0008)
#define PCC_I2C_XO_CBCR			PCC_REG(PCC_MISC, 0x001C)
#define PCC_IM_SLEEP_CBCR		PCC_REG(PCC_MISC, 0x0020)
#define PCC_USB2_1_SLEEP_CBCR		PCC_REG(PCC_MISC, 0x0060)
#define PCC_XO_CBCR			PCC_REG(PCC_MISC, 0x0074)

#endif /* __PCC_CENTRIQ_H_INCLUDE__ */