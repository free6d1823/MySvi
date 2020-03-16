#include <target/clock.h>
#include <target/clk.h>
#include <asm/plat-centriq/freqplan.h>

uint32_t Qdf2400V10PLLCfg[]  = {
	[GCCMW_WEST_PLL0] = 200,
	[GCCMW_WEST_PLL1] = 800,
	[GCCE_EAST_PLL0] = 2000,
	[GCCE_EAST_PLL1] = 1960,
};

const uint64_t Qdf2400V10CBCRs[] = {
	GCCMW_CE_AHB_CBCR(GCCMW_CE1),
	GCCMW_CE_AXI_CBCR(GCCMW_CE1),
	GCCMW_CE_IOMMU_CFG_AHB_CBCR(GCCMW_CE1),
	GCCMW_CE_QSMMUV3_CLIENT_CBCR(GCCMW_CE1),
	GCCMW_EMAC_AXI_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_QSMMUV3_CLIENT_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_AXI_CBCR(GCCMW_EMAC1),
	GCCMW_EMAC_QSMMUV3_CLIENT_CBCR(GCCMW_EMAC1),
	GCCMW_QDSS_FCLK_CBCR,
	GCCMW_QDSS_STM_CBCR,
	GCCMW_SFAB_CE1_FCLK_CBCR,
	GCCMW_SFAB_EMAC0_FCLK_CBCR,
	GCCMW_SFAB_EMAC1_FCLK_CBCR,
	GCCMW_SFAB_VBU_FCLK_CBCR,
	GCCMW_CE_SFVBU_DVM_CBCR(GCCMW_CE1),
	GCCMW_EMAC_SFVBU_DVM_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_SFVBU_DVM_CBCR(GCCMW_EMAC1),
	GCCMW_SFAB_VBU_Q22M_CBCR,
	GCCMW_SFAB_VBU_Q22S_CBCR,
	GCCMW_CE_CBCR(GCCMW_CE1),
	GCCMW_N1_CSFPB_CFAB_FCLK_CBCR,
	GCCMW_HDMA_SFPB_AHB_CBCR,
	GCCMW_FAN_TACH_AHB_CBCR,
	GCCMW_N_CSFPB_XPU_CFG_AHB_CBCR,
	GCCMW_CPRC_APCS_HMSS_CBCR,
	GCCMW_CPRC_DIG_CBCR,
	GCCMW_CPRC_MEM_CBCR,
	GCCMW_CPRC_VDDA_CBCR(GCCMW_CPRC_NVDDA),
	GCCMW_MDDR2_AHB_CBCR,
	GCCMW_MDDR3_AHB_CBCR,
	GCCMW_TSENS_AHB_CBCR(GCCMW_TSENS2),
	GCCMW_TSENS_AHB_CBCR(GCCMW_TSENS3),
	GCCMW_TSENS_AHB_CBCR(GCCMW_TSENS4),
	GCCMW_CPRC_VDDA_CBCR(GCCMW_CPRC_SVDDA),
	GCCMW_MDDR0_AHB_CBCR,
	GCCMW_MDDR1_AHB_CBCR,
	GCCMW_TSENS_AHB_CBCR(GCCMW_TSENS10),
	GCCMW_TSENS_AHB_CBCR(GCCMW_TSENS9),
	GCCMW_EMAC_125M_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_AHB_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_IOMMU_CFG_AHB_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_SYS_25M_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_GMII_TX_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_125M_CBCR(GCCMW_EMAC1),
	GCCMW_EMAC_AHB_CBCR(GCCMW_EMAC1),
	GCCMW_EMAC_IOMMU_CFG_AHB_CBCR(GCCMW_EMAC1),
	GCCMW_EMAC_SYS_25M_CBCR(GCCMW_EMAC1),
	GCCMW_EMAC_GMII_TX_CBCR(GCCMW_EMAC1),
	GCCMW_FAN_TACH_PWM_CBCR,
	GCCMW_FAN_TACH_SLEEP_CBCR,
	GCCMW_GP_CBCR(GCCMW_GP0),
	GCCMW_GP_CBCR(GCCMW_GP1),
	GCCMW_GP_CBCR(GCCMW_GP2),
	GCCMW_HDMA_AHB_CBCR(GCCMW_HDMA0),
	GCCMW_HDMA_AHB_CBCR(GCCMW_HDMA1),
	GCCMW_HDMA_AHB_CBCR(GCCMW_HDMA2),
	GCCMW_HDMA_AHB_CBCR(GCCMW_HDMA3),
	GCCMW_HDMA_SFPB_ALWAYS_ON_CBCR,
	GCCMW_HDMA_SFPB_CBCR,
	GCCMW_HDMA_VBU_CFG_AHB_CBCR,
	GCCMW_HDMA_QSMMUV3_CLIENT_CBCR(GCCMW_HDMA0),
	GCCMW_HDMA_SYS_CBCR(GCCMW_HDMA0),
	GCCMW_HDMA_QSMMUV3_CLIENT_CBCR(GCCMW_HDMA1),
	GCCMW_HDMA_SYS_CBCR(GCCMW_HDMA1),
	GCCMW_HDMA_QSMMUV3_CLIENT_CBCR(GCCMW_HDMA2),
	GCCMW_HDMA_SYS_CBCR(GCCMW_HDMA2),
	GCCMW_HDMA_QSMMUV3_CLIENT_CBCR(GCCMW_HDMA3),
	GCCMW_HDMA_SYS_CBCR(GCCMW_HDMA3),
	GCCMW_HDMA_VBU_CORE_CBCR,
	GCCMW_HMSS_AXI_CBCR,
	GCCMW_HMSS_W_AHB_CBCR,
	GCCMW_HMSS_NW_AHB_CBCR,
	GCCMW_HMSS_SW_AHB_CBCR,
	GCCMW_AT_W2_CBCR,
	GCCMW_AT_W3_CBCR,
	GCCMW_AT_W5_CBCR,
	GCCMW_AT_W7_CBCR,
	GCCMW_AT_W9_CBCR,
	GCCMW_AT_W1_CBCR,
	GCCMW_HMSS_AT_W_CBCR,
	GCCMW_SATA_VBU_CORE_CBCR,
	GCCMW_SFAB_VBU_CORE_CBCR,
	GCCMW_EMAC_AHB2PHY_CFG_AHB_CBCR,
	GCCMW_QDSS_CFG_AHB_CBCR,
	GCCMW_QDSS_DAP_AHB_CBCR,
	GCCMW_QDSS_RBCPR_XPU_AHB_CBCR,
	GCCMW_SFAB_VBU_CFG_CBCR,
	GCCMW_TSENS_AHB_CBCR(GCCMW_TSENS1),
	GCCMW_QDSS_TRACECLKIN_CBCR,
	GCCMW_SATA0_LN_AHB_CBCR,
	GCCMW_SATA_LN_AHB_CBCR(GCCMW_SATA1),
	GCCMW_SATA_LN_AHB_CBCR(GCCMW_SATA2),
	GCCMW_SATA_LN_AHB_CBCR(GCCMW_SATA3),
	GCCMW_SATA_LN_AHB_CBCR(GCCMW_SATA4),
	GCCMW_SATA_LN_AHB_CBCR(GCCMW_SATA5),
	GCCMW_SATA_LN_AHB_CBCR(GCCMW_SATA6),
	GCCMW_SATA_LN_AHB_CBCR(GCCMW_SATA7),
	GCCMW_SATA0_LN_ASIC_CBCR,
	GCCMW_SATA0_LN_RX_CBCR,
	GCCMW_SATA0_LN_PMALIVE_CBCR,
	GCCMW_SATA_LN_PMALIVE_CBCR(GCCMW_SATA1),
	GCCMW_SATA_LN_PMALIVE_CBCR(GCCMW_SATA2),
	GCCMW_SATA_LN_PMALIVE_CBCR(GCCMW_SATA3),
	GCCMW_SATA_LN_PMALIVE_CBCR(GCCMW_SATA4),
	GCCMW_SATA_LN_PMALIVE_CBCR(GCCMW_SATA5),
	GCCMW_SATA_LN_PMALIVE_CBCR(GCCMW_SATA6),
	GCCMW_SATA_LN_PMALIVE_CBCR(GCCMW_SATA7),
	GCCMW_SATA0_LN_AXI_CBCR,
	GCCMW_SATA0_LN_QSMMUV3_CLIENT_CBCR,
	GCCMW_SATA_LN_AXI_CBCR(GCCMW_SATA1),
	GCCMW_SATA_LN_QSMMUV3_CLIENT_CBCR(GCCMW_SATA1),
	GCCMW_SATA_LN_AXI_CBCR(GCCMW_SATA2),
	GCCMW_SATA_LN_QSMMUV3_CLIENT_CBCR(GCCMW_SATA2),
	GCCMW_SATA_LN_AXI_CBCR(GCCMW_SATA3),
	GCCMW_SATA_LN_QSMMUV3_CLIENT_CBCR(GCCMW_SATA3),
	GCCMW_SATA4_LN_AXI_CBCR,
	GCCMW_SATA4_LN_QSMMUV3_CLIENT_CBCR,
	GCCMW_SATA_LN_AXI_CBCR(GCCMW_SATA5),
	GCCMW_SATA_LN_QSMMUV3_CLIENT_CBCR(GCCMW_SATA5),
	GCCMW_SATA_LN_AXI_CBCR(GCCMW_SATA6),
	GCCMW_SATA_LN_QSMMUV3_CLIENT_CBCR(GCCMW_SATA6),
	GCCMW_SATA_LN_AXI_CBCR(GCCMW_SATA7),
	GCCMW_SATA_LN_QSMMUV3_CLIENT_CBCR(GCCMW_SATA7),
	GCCMW_SATA0_LN_RXOOB_CBCR,
	GCCMW_SATA_LN_RXOOB_CBCR(GCCMW_SATA1),
	GCCMW_SATA_LN_RXOOB_CBCR(GCCMW_SATA2),
	GCCMW_SATA_LN_RXOOB_CBCR(GCCMW_SATA3),
	GCCMW_SATA4_LN_RXOOB_CBCR,
	GCCMW_SATA_LN_RXOOB_CBCR(GCCMW_SATA5),
	GCCMW_SATA_LN_RXOOB_CBCR(GCCMW_SATA6),
	GCCMW_SATA_LN_RXOOB_CBCR(GCCMW_SATA7),
	GCCMW_SATA_PHY0_RXOOB_CBCR,
	GCCMW_SATA_PHY1_RXOOB_CBCR,
	GCCMW_SATA_LN_ASIC_CBCR(GCCMW_SATA1),
	GCCMW_SATA_LN_RX_CBCR(GCCMW_SATA1),
	GCCMW_SATA_LN_ASIC_CBCR(GCCMW_SATA2),
	GCCMW_SATA_LN_RX_CBCR(GCCMW_SATA2),
	GCCMW_SATA_LN_ASIC_CBCR(GCCMW_SATA3),
	GCCMW_SATA_LN_RX_CBCR(GCCMW_SATA3),
	GCCMW_SATA_LN_ASIC_CBCR(GCCMW_SATA4),
	GCCMW_SATA_LN_RX_CBCR(GCCMW_SATA4),
	GCCMW_SATA_LN_ASIC_CBCR(GCCMW_SATA5),
	GCCMW_SATA_LN_RX_CBCR(GCCMW_SATA5),
	GCCMW_SATA_LN_ASIC_CBCR(GCCMW_SATA6),
	GCCMW_SATA_LN_RX_CBCR(GCCMW_SATA6),
	GCCMW_SATA_LN_ASIC_CBCR(GCCMW_SATA7),
	GCCMW_SATA_LN_RX_CBCR(GCCMW_SATA7),
	GCCMW_SATA_VBU_AHB_CFG_CBCR,
	GCCMW_EMAC_RAM_SYS_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_RX_CBCR(GCCMW_EMAC0),
	GCCMW_EMAC_RAM_SYS_CBCR(GCCMW_EMAC1),
	GCCMW_EMAC_RX_CBCR(GCCMW_EMAC1),
	GCCMW_TIC_CBCR,
	GCCE_PCIE_SS_SECSFPB_AHB_CBCR(GCCE_PCIE_SS_0),
	GCCE_PCIE_SS_SECSFPB_AHB_CBCR(GCCE_PCIE_SS_1),
	GCCE_PSCLKGEN_CFG_AHB_CBCR,
	GCCE_TSENS_AHB_CBCR(GCCE_TSENS6),
	GCCE_TSENS_AHB_CBCR(GCCE_TSENS7),
	GCCE_MDDR5_AHB_CBCR,
	GCCE_TSENS_AHB_CBCR(GCCE_TSENS8),
	GCCE_MDDR4_AHB_CBCR,
	GCCE_TSENS_AHB_CBCR(GCCE_TSENS5),
	GCCE_HMSS_NE_AHB_CBCR,
	GCCE_HMSS_SE_AHB_CBCR,
	GCCE_AT_E2_CBCR,
	GCCE_AT_E3_CBCR,
	GCCE_AT_E5_CBCR,
	GCCE_AT_E7_CBCR,
	GCCE_AT_E9_CBCR,
	GCCE_HMSS_AT_E_CBCR,
	GCCE_PCIE_SS_VBU_CORE_CBCR(GCCE_PCIE_SS_0),
	GCCE_PCIE_SS_VBU_CORE_CBCR(GCCE_PCIE_SS_1),
	GCCE_XO_CBCR,
	GCCE_TSENS_EXT_CBCR(GCCE_TSENS5),
	GCCE_TSENS_EXT_CBCR(GCCE_TSENS6),
	GCCE_TSENS_EXT_CBCR(GCCE_TSENS7),
	GCCE_TSENS_EXT_CBCR(GCCE_TSENS8),
	GCCE_XO_DIV4_CBCR,
	PCC_I2C_APPS_CBCR(PCC_BLSP1_QUP0),
	PCC_I2C_APPS_CBCR(PCC_BLSP1_QUP1),
	PCC_I2C_APPS_CBCR(PCC_BLSP1_QUP2),
	PCC_I2C_APPS_CBCR(PCC_BLSP1_QUP3),
	PCC_I2C_APPS_CBCR(PCC_BLSP2_QUP0),
	PCC_I2C_APPS_CBCR(PCC_BLSP2_QUP1),
	PCC_I2C_APPS_CBCR(PCC_BLSP2_QUP2),
	PCC_I2C_APPS_CBCR(PCC_BLSP2_QUP3),
	PCC_UART_APPS_CBCR(PCC_BLSP3_UART0),
	PCC_UART_APPS_CBCR(PCC_BLSP3_UART1),
	PCC_UART_APPS_CBCR(PCC_BLSP3_UART2),
	PCC_UART_APPS_CBCR(PCC_BLSP3_UART3),
	PCC_PDM2_CBCR,
	PCC_PERIPH_SPI_CORE_CBCR,
	PCC_SFAB_PFAB_QSMMUV3_CLIENT_CBCR,
	PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR(0, PCIE_CC_PCIE_PHY_AA),
	PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR(0, PCIE_CC_PCIE_PHY_AB),
	PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR(0, PCIE_CC_PCIE_PHY_B),
	PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR(0, PCIE_CC_PCIE_PHY_C),
	PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR(0),
	PCIE_CC_PCIE_X16_MSTR_Q23_CBCR(0),
	PCIE_CC_PCIE_X16_SLV_Q23_CBCR(0),
	PCIE_CC_PCIE_X8_MMU_MSTR_Q23_CBCR(0, PCIE_CC_X8_0),
	PCIE_CC_PCIE_X8_MSTR_Q23_CBCR(0, PCIE_CC_X8_0),
	PCIE_CC_PCIE_X8_MMU_MSTR_Q23_CBCR(0, PCIE_CC_X8_1),
	PCIE_CC_PCIE_X8_MSTR_Q23_CBCR(0, PCIE_CC_X8_1),
	PCIE_CC_PCIE_X8_SLV_Q23_CBCR(0, PCIE_CC_X8_0),
	PCIE_CC_PCIE_X8_SLV_Q23_CBCR(0, PCIE_CC_X8_1),
	PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR(1, PCIE_CC_PCIE_PHY_AA),
	PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR(1, PCIE_CC_PCIE_PHY_AB),
	PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR(1, PCIE_CC_PCIE_PHY_B),
	PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR(1, PCIE_CC_PCIE_PHY_C),
	PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR(1),
	PCIE_CC_PCIE_X16_MSTR_Q23_CBCR(1),
	PCIE_CC_PCIE_X16_SLV_Q23_CBCR(1),
	PCIE_CC_PCIE_X8_MMU_MSTR_Q23_CBCR(1, PCIE_CC_X8_0),
	PCIE_CC_PCIE_X8_MSTR_Q23_CBCR(1, PCIE_CC_X8_0),
	PCIE_CC_PCIE_X8_MMU_MSTR_Q23_CBCR(1, PCIE_CC_X8_1),
	PCIE_CC_PCIE_X8_MSTR_Q23_CBCR(1, PCIE_CC_X8_1),
	PCIE_CC_PCIE_X8_SLV_Q23_CBCR(1, PCIE_CC_X8_0),
	PCIE_CC_PCIE_X8_SLV_Q23_CBCR(1, PCIE_CC_X8_1),
	0,
};

const struct ClockCfg Qdf2400V10CdivCfg[] = {
    /* parb_pre_div [ 100.000MHz] */
    {
        .nAddr = 0xFF010F0700,
        .nVal  =        65536, /* Div 2 */
    },
    { 0 }
};

const clk_ctl_cfg Qdf2400V10RcgCfg[] = {
	/* imc_clk_src                 [ 100.000MHz] */
	{
		.src_sel = 2, /* sys_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = IMC_CC_IMC_CMD_RCGR,
	},
	/* imc_proc_clk_src            [ 400.000MHz] */
	{
		.src_sel = 4, /* sys_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 400000000,
		.cmd_rcgr = IMC_CC_IMC_PROC_CMD_RCGR,
	},
	/* ce0_clk_src                 [ 200.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_CE_CMD_RCGR(GCCMW_CE0),
	},
	/* system_fab_clk_src          [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_SFAB_CMD_RCGR,
	},
	/* ce1_clk_src                 [ 200.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_CE_CMD_RCGR(GCCMW_CE1),
	},
	/* config_fab_clk_src          [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_CFAB_CMD_RCGR,
	},
	/* cprc_apcs_clk_src           [ 100.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_CPRC_APCS_CMD_RCGR,
	},
	/* cprc_dig_clk_src            [ 100.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_CPRC_DIG_CMD_RCGR,
	},
	/* cprc_mem_clk_src            [  66.667MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 66666666,
		.cmd_rcgr = GCCMW_CPRC_MEM_CMD_RCGR,
	},
	/* cprc_nvdda_clk_src          [ 100.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_CPRC_VDDA_CMD_RCGR(GCCMW_CPRC_NVDDA),
	},
	/* n1_csfpb_clk_src            [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_N1_CSFPB_CMD_RCGR,
	},
	/* cprc_svdda_clk_src          [ 100.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_CPRC_VDDA_CMD_RCGR(GCCMW_CPRC_SVDDA),
	},
	/* s1_csfpb_clk_src            [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_S1_CSFPB_CMD_RCGR,
	},
	/* emac0_ahb_clk_src           [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_EMAC_AHB_CMD_RCGR(GCCMW_EMAC0),
	},
	/* emac1_ahb_clk_src           [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_EMAC_AHB_CMD_RCGR(GCCMW_EMAC1),
	},
	/* fan_tach_clk_src            [  20.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div10 */
		.input_hz = 200000000/10,
		.output_hz = 20000000,
		.cmd_rcgr = GCCMW_FAN_TACH_CMD_RCGR,
	},
	/* gccmw_xo_clk_src            [  20.000MHz] */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 20000000,
		.cmd_rcgr = GCCMW_XO_CMD_RCGR,
	},
	/* gp0_clk_src                 [ 100.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_GP_CMD_RCGR(GCCMW_GP0),
		.flags = CLK_MND_MASK(GCCMW_GP_MND_MASK),
	},
	/* gp1_clk_src                 [ 100.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_GP_CMD_RCGR(GCCMW_GP1),
		.flags = CLK_MND_MASK(GCCMW_GP_MND_MASK),
	},
	/* gp2_clk_src                 [ 100.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_GP_CMD_RCGR(GCCMW_GP2),
		.flags = CLK_MND_MASK(GCCMW_GP_MND_MASK),
	},
	/* hdma_ahb_clk_src            [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_HDMA_AHB_CMD_RCGR,
	},
	/* hdma_sfpb_clk_src           [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_HDMA_SFPB_CMD_RCGR,
	},
	/* hdma_sys_clk_src            [ 200.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_HDMA_SYS_CMD_RCGR,
	},
	/* hdma_vbu_clk_src            [ 800.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 800000000,
		.cmd_rcgr = GCCMW_HDMA_VBU_CMD_RCGR,
	},
	/* hmss_bus_clk_src            [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCE_HMSS_BUS_CMD_RCGR,
	},
	/* qdss_at_clk_src             [ 200.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_QDSS_ATB_CMD_RCGR,
	},
	/* sata_vbu_clk_src            [ 200.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_SATA_VBU_CMD_RCGR,
	},
	/* sys_fab_vbu_clk_src         [ 200.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_SFAB_VBU_CMD_RCGR,
	},
	/* wcsfpb_clk_src              [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_W_CSFPB_CMD_RCGR,
	},
	/* parb0_ser_clk_src           [  25.000MHz] */
	{
		.src_sel = 3, /* parb_pre_div */
		.input_hz = 100000000,
		.output_hz = 25000000,
		.cmd_rcgr = GCCMW_PARB_SER_CMD_RCGR(GCCMW_PARB0),
	},
	/* parb1_ser_clk_src           [  25.000MHz] */
	{
		.src_sel = 3, /* parb_pre_div */
		.input_hz = 100000000,
		.output_hz = 25000000,
		.cmd_rcgr = GCCMW_PARB_SER_CMD_RCGR(GCCMW_PARB1),
	},
	/* parb2_ser_clk_src           [  25.000MHz] */
	{
		.src_sel = 3, /* parb_pre_div */
		.input_hz = 100000000,
		.output_hz = 25000000,
		.cmd_rcgr = GCCMW_PARB_SER_CMD_RCGR(GCCMW_PARB2),
	},
	/* qdss_traceclkin_clk_src     [ 200.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_QDSS_TRACE_CMD_RCGR,
	},
	/* sata_ahb_clk_src            [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_SATA0_AHB_CMD_RCGR,
	},
	/* sata_pmalive_clk_src        [ 100.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_SATA_PMALIVE_CMD_RCGR,
	},
	/* sata_q22_clk_src            [ 200.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_SATA_Q22_CMD_RCGR,
	},
	/* sata_rxoob_clk_src          [ 100.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_SATA_RXOOB_CMD_RCGR,
	},
	/* sata_csfpb_clk_src          [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCMW_SATA_SS_CSFPB_CMD_RCGR,
	},
	/* acc_clk_src                 [ 200.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 200000000,
		.cmd_rcgr = GCCMW_ACC_CMD_RCGR,
	},
	/* sec_ctrl_clk_src            [  20.000MHz] */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 20000000,
		.cmd_rcgr = GCCMW_SEC_CTRL_CMD_RCGR,
	},
	/* secsfpb_clk_src             [ 100.000MHz] */
	{
		.src_sel = 1, /* east_pll0_out_even */
		.input_hz = 2000000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCE_SECSFPB_CMD_RCGR,
	},
	/* s2_csfpb_clk_src            [ 100.000MHz] */
	{
		.src_sel = 1, /* east_pll0_out_even */
		.input_hz = 2000000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCE_S2_CSFPB_CMD_RCGR,
	},
	/* n2_csfpb_clk_src            [ 100.000MHz] */
	{
		.src_sel = 1, /* east_pll0_out_even */
		.input_hz = 2000000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCE_N2_CSFPB_CMD_RCGR,
	},
	/* hmss_bus_clk_src            [ 100.000MHz] */
	{
		.src_sel = 1, /* east_pll0_out_even */
		.input_hz = 2000000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = GCCE_HMSS_BUS_CMD_RCGR,
	},
	/* qdss_at_clk_src             [ 250.000MHz] */
	{
		.src_sel = 1, /* east_pll0_out_even */
		.input_hz = 2000000000/2,
		.output_hz = 250000000,
		.cmd_rcgr = GCCE_QDSS_ATB_CMD_RCGR,
	},
	/* pcie_ss_0_vbu_clk_src       [ 980.000MHz] */
	{
		.src_sel = 5, /* east_pll1_out_even */
		.input_hz = 1960000000/2,
		.output_hz = 980000000,
		.cmd_rcgr = GCCE_PCIE_SS_VBU_CMD_RCGR(GCCE_PCIE_SS_0),
	},
	/* pcie_ss_1_vbu_clk_src       [ 980.000MHz] */
	{
		.src_sel = 5, /* east_pll1_out_even */
		.input_hz = 1960000000/2,
		.output_hz = 980000000,
		.cmd_rcgr = GCCE_PCIE_SS_VBU_CMD_RCGR(GCCE_PCIE_SS_1),
	},
	/* gcce_xo_clk_src             [  20.000MHz] */
	{
		.src_sel = 0, /* east_xo */
		.input_hz = FREQ_EAST_XO,
		.output_hz = 20000000,
		.cmd_rcgr = GCCE_XO_CMD_RCGR,
	},
	/* blsp0_qup0_spi_apps_clk_src [  20.000MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 20000000,
		.cmd_rcgr = PCC_SPI_CMD_RCGR(PCC_BLSP0_QUP0),
		.flags = CLK_MND_MASK(PCC_SPI_MND_MASK),
	},
	/* blsp0_qup1_spi_apps_clk_src [  25.806MHz] (OVERRIDE) */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 25806000,
		.cmd_rcgr = PCC_SPI_CMD_RCGR(PCC_BLSP0_QUP1),
		.flags = CLK_MND_MASK(PCC_SPI_MND_MASK),
	},
	/* blsp0_uart0_apps_clk_src    [   1.840MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 1840000,
		.cmd_rcgr = PCC_UART_CMD_RCGR(PCC_BLSP0_UART0),
		.flags = CLK_MND_MASK(PCC_UART_MND_MASK),
	},
	/* blsp0_uart1_apps_clk_src    [   1.840MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 1840000,
		.cmd_rcgr = PCC_UART_CMD_RCGR(PCC_BLSP0_UART1),
		.flags = CLK_MND_MASK(PCC_UART_MND_MASK),
	},
	/* blsp0_uart2_apps_clk_src    [   1.840MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 1840000,
		.cmd_rcgr = PCC_UART_CMD_RCGR(PCC_BLSP0_UART2),
		.flags = CLK_MND_MASK(PCC_UART_MND_MASK),
	},
	/* blsp0_uart3_apps_clk_src    [   1.840MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 1840000,
		.cmd_rcgr = PCC_UART_CMD_RCGR(PCC_BLSP0_UART3),
		.flags = CLK_MND_MASK(PCC_UART_MND_MASK),
	},
	/* periph_fab_clk_src          [ 100.000MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 100000000,
		.cmd_rcgr = PCC_PFAB_CMD_RCGR,
	},
	/* blsp1_qup0_i2c_apps_clk_src [  50.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 50000000,
		.cmd_rcgr = PCC_I2C_CMD_RCGR(PCC_BLSP1_QUP0),
	},
	/* blsp1_qup1_i2c_apps_clk_src [  50.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 50000000,
		.cmd_rcgr = PCC_I2C_CMD_RCGR(PCC_BLSP1_QUP1),
	},
	/* blsp1_qup2_i2c_apps_clk_src [  50.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 50000000,
		.cmd_rcgr = PCC_I2C_CMD_RCGR(PCC_BLSP1_QUP2),
	},
	/* blsp1_qup3_i2c_apps_clk_src [  50.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 50000000,
		.cmd_rcgr = PCC_I2C_CMD_RCGR(PCC_BLSP1_QUP3),
	},
	/* blsp2_qup0_i2c_apps_clk_src [  50.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 50000000,
		.cmd_rcgr = PCC_I2C_CMD_RCGR(PCC_BLSP2_QUP0),
	},
	/* blsp2_qup1_i2c_apps_clk_src [  50.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 50000000,
		.cmd_rcgr = PCC_I2C_CMD_RCGR(PCC_BLSP2_QUP1),
	},
	/* blsp2_qup2_i2c_apps_clk_src [  50.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 50000000,
		.cmd_rcgr = PCC_I2C_CMD_RCGR(PCC_BLSP2_QUP2),
	},
	/* blsp2_qup3_i2c_apps_clk_src [  50.000MHz] */
	{
		.src_sel = 4, /* west_pll1_out_main */
		.input_hz = 800000000,
		.output_hz = 50000000,
		.cmd_rcgr = PCC_I2C_CMD_RCGR(PCC_BLSP2_QUP3),
	},
	/* blsp3_uart0_apps_clk_src    [   1.840MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 1840000,
		.cmd_rcgr = PCC_UART_CMD_RCGR(PCC_BLSP3_UART0),
		.flags = CLK_MND_MASK(PCC_UART_MND_MASK),
	},
	/* blsp3_uart1_apps_clk_src    [   1.840MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 1840000,
		.cmd_rcgr = PCC_UART_CMD_RCGR(PCC_BLSP3_UART1),
		.flags = CLK_MND_MASK(PCC_UART_MND_MASK),
	},
	/* blsp3_uart2_apps_clk_src    [   1.840MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 1840000,
		.cmd_rcgr = PCC_UART_CMD_RCGR(PCC_BLSP3_UART2),
		.flags = CLK_MND_MASK(PCC_UART_MND_MASK),
	},
	/* blsp3_uart3_apps_clk_src    [   1.840MHz] (OVERRIDE) */
	{
		.src_sel = 0, /* west_xo */
		.input_hz = FREQ_WEST_XO,
		.output_hz = 1840000,
		.cmd_rcgr = PCC_UART_CMD_RCGR(PCC_BLSP3_UART3),
		.flags = CLK_MND_MASK(PCC_UART_MND_MASK),
	},
	/* pdm2_clk_src                [  57.143MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 57143000,
		.cmd_rcgr = PCC_PDM2_CMD_RCGR,
	},
	/* usb2_mstr_clk_src           [  66.667MHz] */
	{
		.src_sel = 1, /* west_pll0_out_main */
		.input_hz = 200000000,
		.output_hz = 666666666,
		.cmd_rcgr = PCC_USB2_MSTR_CMD_RCGR,
	},
	/* periph_spi_clk_src          [ 100.000MHz] */
	{
		.src_sel = 2, /* west_pll0_out_main_div2 */
		.input_hz = 200000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = PCC_PERIPH_SPI_CMD_RCGR,
	},
	/* pcie_sfpb_clk_src           [ 100.000MHz] */
	{
		.src_sel = 2, /* east_pll0_out_even */
		.input_hz = 2000000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = PCIE_CC_PCIE_SFPB_CMD_RCGR(0),
	},
	/* pcie_aux_clk_src            [   1.000MHz] */
	{
		.src_sel = 0, /* east_xo */
		.input_hz = FREQ_EAST_XO,
		.output_hz = 1000000,
		.cmd_rcgr = PCIE_CC_PCIE_AUX_CMD_RCGR(0),
		.flags = CLK_MND_MASK(PCIE_CC_PCIE_AUX_MND_MASK),
	},
	/* pcie_sfpb_clk_src           [ 100.000MHz] */
	{
		.src_sel = 2, /* east_pll0_out_even */
		.input_hz = 2000000000/2,
		.output_hz = 100000000,
		.cmd_rcgr = PCIE_CC_PCIE_SFPB_CMD_RCGR(1),
	},
	/* pcie_aux_clk_src            [   1.000MHz] */
	{
		.src_sel = 0, /* east_xo */
		.input_hz = FREQ_EAST_XO,
		.output_hz = 1000000,
		.cmd_rcgr = PCIE_CC_PCIE_AUX_CMD_RCGR(1),
		.flags = CLK_MND_MASK(PCIE_CC_PCIE_AUX_MND_MASK),
	},
	{ 0 },
};
