/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#ifndef __BM_SATA_REGS_H__
#define __BM_SATA_REGS_H__

/* SATA HBA controller base address*/
#define I0_SATA_REG_BASE (SATA_SS_VBU_TN_BASE + 0x00000000)
#define I1_SATA_REG_BASE (SATA_SS_VBU_TN_BASE + 0x01000000)
#define I2_SATA_REG_BASE (SATA_SS_VBU_TN_BASE + 0x02000000)
#define I3_SATA_REG_BASE (SATA_SS_VBU_TN_BASE + 0x03000000)
#define I4_SATA_REG_BASE (SATA_SS_VBU_TN_BASE + 0x04000000)
#define I5_SATA_REG_BASE (SATA_SS_VBU_TN_BASE + 0x05000000)
#define I6_SATA_REG_BASE (SATA_SS_VBU_TN_BASE + 0x06000000)
#define I7_SATA_REG_BASE (SATA_SS_VBU_TN_BASE + 0x07000000)

/* SATA qserver common base address */
#define SP0_QSERVER_COM_REG_BASE (SP0_CM_SERVER_SATA_SW_BASE + 0x00000000)
#define SP1_QSERVER_COM_REG_BASE (SP1_CM_SERVER_SATA_SW_BASE + 0x00000000)

/* SATA qserver lane base address*/
#define SP0_QSERVER_L0_SATA_LANE_REG_BASE                                      \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00010000)
#define SP0_QSERVER_L1_SATA_LANE_REG_BASE                                      \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00020000)
#define SP0_QSERVER_L2_SATA_LANE_REG_BASE                                      \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00030000)
#define SP0_QSERVER_L3_SATA_LANE_REG_BASE                                      \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00040000)
#define SP1_QSERVER_L0_SATA_LANE_REG_BASE                                      \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00010000)
#define SP1_QSERVER_L1_SATA_LANE_REG_BASE                                      \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00020000)
#define SP1_QSERVER_L2_SATA_LANE_REG_BASE                                      \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00030000)
#define SP1_QSERVER_L3_SATA_LANE_REG_BASE                                      \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00040000)

/* SATA PCS base address*/
#define SP0_SATA_PHY_L0_SATA_PCS_LANE_REG_BASE                                 \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00010400)
#define SP0_SATA_PHY_L1_SATA_PCS_LANE_REG_BASE                                 \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00020400)
#define SP0_SATA_PHY_L2_SATA_PCS_LANE_REG_BASE                                 \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00030400)
#define SP0_SATA_PHY_L3_SATA_PCS_LANE_REG_BASE                                 \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00040400)
#define SP1_SATA_PHY_L0_SATA_PCS_LANE_REG_BASE                                 \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00010400)
#define SP1_SATA_PHY_L1_SATA_PCS_LANE_REG_BASE                                 \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00020400)
#define SP1_SATA_PHY_L2_SATA_PCS_LANE_REG_BASE                                 \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00030400)
#define SP1_SATA_PHY_L3_SATA_PCS_LANE_REG_BASE                                 \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00040400)

/* SATA qserver common defines */
#define HWIO_SP_QSERVER_COM_CMN_CONFIG_OFFS (0x000001e8)
#define HWIO_SP_QSERVER_COM_CMN_CONFIG_RMSK 0x1f
#define HWIO_SP_QSERVER_COM_CLK_SELECT_OFFS (0x000001c4)
#define HWIO_SP_QSERVER_COM_CLK_SELECT_RMSK 0x7f
#define HWIO_SP_QSERVER_COM_SYSCLK_EN_SEL_OFFS (0x000000d4)
#define HWIO_SP_QSERVER_COM_SYSCLK_EN_SEL_RMSK 0xff
#define HWIO_SP_QSERVER_COM_SYS_CLK_CTRL_OFFS (0x0000005c)
#define HWIO_SP_QSERVER_COM_SYS_CLK_CTRL_RMSK 0xf
#define HWIO_SP_QSERVER_COM_HSCLK_SEL1_OFFS (0x000001c8)
#define HWIO_SP_QSERVER_COM_HSCLK_SEL1_RMSK 0xff
#define HWIO_SP_QSERVER_COM_BIAS_EN_CLKBUFLR_EN_OFFS (0x00000054)
#define HWIO_SP_QSERVER_COM_BIAS_EN_CLKBUFLR_EN_RMSK 0x7f
#define HWIO_SP_QSERVER_COM_CLK_ENABLE1_OFFS (0x00000058)
#define HWIO_SP_QSERVER_COM_CLK_ENABLE1_RMSK 0xff
#define HWIO_SP_QSERVER_COM_BG_CTRL_OFFS (0x000001c0)
#define HWIO_SP_QSERVER_COM_BG_CTRL_RMSK 0x7
#define HWIO_SP_QSERVER_COM_BGT_TRIM_OFFS (0x0000009c)
#define HWIO_SP_QSERVER_COM_BGT_TRIM_RMSK 0xff
#define HWIO_SP_QSERVER_COM_BGV_TRIM_OFFS (0x00000098)
#define HWIO_SP_QSERVER_COM_BGV_TRIM_RMSK 0xff
#define HWIO_SP_QSERVER_COM_VREGCLK_DIV1_OFFS (0x00000220)
#define HWIO_SP_QSERVER_COM_VREGCLK_DIV1_RMSK 0x3f
#define HWIO_SP_QSERVER_COM_RESTRIM_CTRL_OFFS (0x000000e4)
#define HWIO_SP_QSERVER_COM_RESTRIM_CTRL_RMSK 0xff
#define HWIO_SP_QSERVER_COM_LOCK_CMP_EN_OFFS (0x000000f0)
#define HWIO_SP_QSERVER_COM_LOCK_CMP_EN_RMSK 0xff
#define HWIO_SP_QSERVER_COM_PLL_CCTRL_MODE0_OFFS (0x000000c4)
#define HWIO_SP_QSERVER_COM_PLL_CCTRL_MODE0_RMSK 0x3f
#define HWIO_SP_QSERVER_COM_PLL_RCTRL_MODE0_OFFS (0x000000b8)
#define HWIO_SP_QSERVER_COM_PLL_RCTRL_MODE0_RMSK 0x1f
#define HWIO_SP_QSERVER_COM_CP_CTRL_MODE0_OFFS (0x000000ac)
#define HWIO_SP_QSERVER_COM_CP_CTRL_MODE0_RMSK 0x3f
#define HWIO_SP_QSERVER_COM_SSC_EN_CENTER_OFFS (0x00000014)
#define HWIO_SP_QSERVER_COM_SSC_EN_CENTER_RMSK 0x3
#define HWIO_SP_QSERVER_COM_SSC_PER1_OFFS (0x00000020)
#define HWIO_SP_QSERVER_COM_SSC_PER1_RMSK 0xff
#define HWIO_SP_QSERVER_COM_SSC_PER2_OFFS (0x00000024)
#define HWIO_SP_QSERVER_COM_SSC_PER2_RMSK 0xff
#define HWIO_SP_QSERVER_COM_SSC_STEP_SIZE1_OFFS (0x00000028)
#define HWIO_SP_QSERVER_COM_SSC_STEP_SIZE1_RMSK 0xff
#define HWIO_SP_QSERVER_COM_SSC_STEP_SIZE2_OFFS (0x0000002c)
#define HWIO_SP_QSERVER_COM_SSC_STEP_SIZE2_RMSK 0xff
#define HWIO_SP_QSERVER_COM_SSC_STEP_SIZE3_OFFS (0x00000030)
#define HWIO_SP_QSERVER_COM_SSC_STEP_SIZE3_RMSK 0x1
#define HWIO_SP_QSERVER_COM_DEC_START_MODE0_OFFS (0x000000f8)
#define HWIO_SP_QSERVER_COM_DEC_START_MODE0_RMSK 0xff
#define HWIO_SP_QSERVER_COM_DEC_START_MSB_MODE0_OFFS (0x000000fc)
#define HWIO_SP_QSERVER_COM_DEC_START_MSB_MODE0_RMSK 0x1
#define HWIO_SP_QSERVER_COM_DIV_FRAC_START1_MODE0_OFFS (0x00000114)
#define HWIO_SP_QSERVER_COM_DIV_FRAC_START1_MODE0_RMSK 0xff
#define HWIO_SP_QSERVER_COM_DIV_FRAC_START2_MODE0_OFFS (0x00000118)
#define HWIO_SP_QSERVER_COM_DIV_FRAC_START2_MODE0_RMSK 0xff
#define HWIO_SP_QSERVER_COM_DIV_FRAC_START3_MODE0_OFFS (0x0000011c)
#define HWIO_SP_QSERVER_COM_DIV_FRAC_START3_MODE0_RMSK 0xf
#define HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN0_MODE0_OFFS (0x00000148)
#define HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN0_MODE0_RMSK 0xff
#define HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN1_MODE0_OFFS (0x0000014c)
#define HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN1_MODE0_RMSK 0xf
#define HWIO_SP_QSERVER_COM_VCO_TUNE_MAP_OFFS (0x00000170)
#define HWIO_SP_QSERVER_COM_VCO_TUNE_MAP_RMSK 0xff
#define HWIO_SP_QSERVER_COM_VCO_TUNE1_MODE0_OFFS (0x00000174)
#define HWIO_SP_QSERVER_COM_VCO_TUNE1_MODE0_RMSK 0xff
#define HWIO_SP_QSERVER_COM_VCO_TUNE2_MODE0_OFFS (0x00000178)
#define HWIO_SP_QSERVER_COM_VCO_TUNE2_MODE0_RMSK 0x3
#define HWIO_SP_QSERVER_COM_VCO_TUNE_CTRL_OFFS (0x0000016c)
#define HWIO_SP_QSERVER_COM_VCO_TUNE_CTRL_RMSK 0x3f
#define HWIO_SP_QSERVER_COM_RESETSM_CNTRL_OFFS (0x000000dc)
#define HWIO_SP_QSERVER_COM_RESETSM_CNTRL_RMSK 0x7f
#define HWIO_SP_QSERVER_COM_RESETSM_CNTRL2_OFFS (0x000000e0)
#define HWIO_SP_QSERVER_COM_RESETSM_CNTRL2_RMSK 0x7f
#define HWIO_SP_QSERVER_COM_PLL_EN_OFFS (0x00000064)
#define HWIO_SP_QSERVER_COM_PLL_EN_RMSK 0x3
#define HWIO_SP_QSERVER_COM_LOCK_CMP_CFG_OFFS (0x000000f4)
#define HWIO_SP_QSERVER_COM_LOCK_CMP_CFG_RMSK 0x3
#define HWIO_SP_QSERVER_COM_LOCK_CMP1_MODE0_OFFS (0x0000006c)
#define HWIO_SP_QSERVER_COM_LOCK_CMP1_MODE0_RMSK 0xff
#define HWIO_SP_QSERVER_COM_LOCK_CMP2_MODE0_OFFS (0x00000070)
#define HWIO_SP_QSERVER_COM_LOCK_CMP2_MODE0_RMSK 0xff
#define HWIO_SP_QSERVER_COM_LOCK_CMP3_MODE0_OFFS (0x00000074)
#define HWIO_SP_QSERVER_COM_LOCK_CMP3_MODE0_RMSK 0x3
#define HWIO_SP_QSERVER_COM_CORECLK_DIV_OFFS (0x000001d8)
#define HWIO_SP_QSERVER_COM_CORECLK_DIV_RMSK 0xff
#define HWIO_SP_QSERVER_COM_CORE_CLK_EN_OFFS (0x000001e0)
#define HWIO_SP_QSERVER_COM_CORE_CLK_EN_RMSK 0x7f
#define HWIO_SP_QSERVER_COM_SVS_MODE_CLK_SEL_OFFS (0x000001f4)
#define HWIO_SP_QSERVER_COM_SVS_MODE_CLK_SEL_RMSK 0x3f
#define HWIO_SP_QSERVER_COM_SYSCLK_BUF_ENABLE_OFFS (0x00000060)
#define HWIO_SP_QSERVER_COM_SYSCLK_BUF_ENABLE_RMSK 0x7
#define HWIO_SP_QSERVER_COM_PLL_IVCO_OFFS (0x00000068)
#define HWIO_SP_QSERVER_COM_PLL_IVCO_RMSK 0xff
#define HWIO_SP_QSERVER_COM_BG_TIMER_OFFS (0x00000010)
#define HWIO_SP_QSERVER_COM_BG_TIMER_RMSK 0xff
#define HWIO_SP_QSERVER_COM_C_READY_STATUS_OFFS (0x000001e4)
#define HWIO_SP_QSERVER_COM_C_READY_STATUS_RMSK 0x1
#define HWIO_SP_QSERVER_COM_INTEGLOOP_INITVAL_OFFS (0x00000140)
#define HWIO_SP_QSERVER_COM_INTEGLOOP_INITVAL_RMSK 0xff

/* SATA qserver lane defines */
#define HWIO_SP_QSERVER_L_RX_EN_SIGNAL_OFFS (0x000002ac)
#define HWIO_SP_QSERVER_L_RX_EN_SIGNAL_RMSK 0xff
#define HWIO_SP_QSERVER_L_PARALLEL_RATE_OFFS (0x0000007c)
#define HWIO_SP_QSERVER_L_PARALLEL_RATE_RMSK 0x3f
#define HWIO_SP_QSERVER_L_DLL_HIGHDATARATE_OFFS (0x000002c4)
#define HWIO_SP_QSERVER_L_DLL_HIGHDATARATE_RMSK 0x3f
#define HWIO_SP_QSERVER_L_DLL_ENABLE_WAIT_OFFS (0x00000294)
#define HWIO_SP_QSERVER_L_DLL_ENABLE_WAIT_RMSK 0x1f
#define HWIO_SP_QSERVER_L_DCC_INIT_OFFS (0x000002a0)
#define HWIO_SP_QSERVER_L_DCC_INIT_RMSK 0x7f
#define HWIO_SP_QSERVER_L_DCC_GAIN_OFFS (0x000002a4)
#define HWIO_SP_QSERVER_L_DCC_GAIN_RMSK 0x1f
#define HWIO_SP_QSERVER_L_UCDR_FO_TO_SO_DELAY_OFFS (0x000001a0)
#define HWIO_SP_QSERVER_L_UCDR_FO_TO_SO_DELAY_RMSK 0xff
#define HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE0_OFFS (0x00000184)
#define HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE0_RMSK 0xff
#define HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE0_OFFS (0x00000190)
#define HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE0_RMSK 0x7f
#define HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE1_OFFS (0x00000188)
#define HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE1_RMSK 0xff
#define HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE1_OFFS (0x00000194)
#define HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE1_RMSK 0x7f
#define HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE2_OFFS (0x0000018c)
#define HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE2_RMSK 0xff
#define HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE2_OFFS (0x00000198)
#define HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE2_RMSK 0x7f
#define HWIO_SP_QSERVER_L_UCDR_SO_CONFIG_OFFS (0x0000019c)
#define HWIO_SP_QSERVER_L_UCDR_SO_CONFIG_RMSK 0xff
#define HWIO_SP_QSERVER_L_TX_BAND_MODE_OFFS (0x00000060)
#define HWIO_SP_QSERVER_L_TX_BAND_MODE_RMSK 0x3f
#define HWIO_SP_QSERVER_L_RX_BAND_OFFS (0x000001a4)
#define HWIO_SP_QSERVER_L_RX_BAND_RMSK 0x3f
#define HWIO_SP_QSERVER_L_LANE_MODE_OFFS (0x00000064)
#define HWIO_SP_QSERVER_L_LANE_MODE_RMSK 0x7f
#define HWIO_SP_QSERVER_L_RX_RCVR_PATH0_OFFS (0x000001b8)
#define HWIO_SP_QSERVER_L_RX_RCVR_PATH0_RMSK 0xff
#define HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE0_OFFS (0x000001c0)
#define HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE0_RMSK 0x7f
#define HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE1_OFFS (0x000001c4)
#define HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE1_RMSK 0x7f
#define HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE2_OFFS (0x000001c8)
#define HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE2_RMSK 0x7f
#define HWIO_SP_QSERVER_L_TX_MARGINING_OFFS (0x0000001c)
#define HWIO_SP_QSERVER_L_TX_MARGINING_RMSK 0x7f
#define HWIO_SP_QSERVER_L_TX_PRE_OFFS (0x00000020)
#define HWIO_SP_QSERVER_L_TX_PRE_RMSK 0x7f
#define HWIO_SP_QSERVER_L_TX_POST_OFFS (0x00000024)
#define HWIO_SP_QSERVER_L_TX_POST_RMSK 0x7f
#define HWIO_SP_QSERVER_L_CML_CTRL_MODE0_OFFS (0x000000c0)
#define HWIO_SP_QSERVER_L_CML_CTRL_MODE0_RMSK 0x3f
#define HWIO_SP_QSERVER_L_CML_CTRL_MODE1_OFFS (0x000000c4)
#define HWIO_SP_QSERVER_L_CML_CTRL_MODE1_RMSK 0x3f
#define HWIO_SP_QSERVER_L_CML_CTRL_MODE2_OFFS (0x000000c8)
#define HWIO_SP_QSERVER_L_CML_CTRL_MODE2_RMSK 0x3f
#define HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE0_OFFS (0x000000cc)
#define HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE0_RMSK 0x7
#define HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE1_OFFS (0x000000d0)
#define HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE1_RMSK 0x7
#define HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE2_OFFS (0x000000d4)
#define HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE2_RMSK 0x7
#define HWIO_SP_QSERVER_L_MIXER_CTRL_MODE0_OFFS (0x000000d8)
#define HWIO_SP_QSERVER_L_MIXER_CTRL_MODE0_RMSK 0x3f
#define HWIO_SP_QSERVER_L_MIXER_CTRL_MODE1_OFFS (0x000000dc)
#define HWIO_SP_QSERVER_L_MIXER_CTRL_MODE1_RMSK 0x3f
#define HWIO_SP_QSERVER_L_MIXER_CTRL_MODE2_OFFS (0x000000e0)
#define HWIO_SP_QSERVER_L_MIXER_CTRL_MODE2_RMSK 0x3f
#define HWIO_SP_QSERVER_L_PSM_RX_EN_CAL_OFFS (0x000002b0)
#define HWIO_SP_QSERVER_L_PSM_RX_EN_CAL_RMSK 0x1f
#define HWIO_SP_QSERVER_L_TS0_TIMER_OFFS (0x000002c0)
#define HWIO_SP_QSERVER_L_TS0_TIMER_RMSK 0x3f
#define HWIO_SP_QSERVER_L_EQ_INITVAL_OFFS (0x00000154)
#define HWIO_SP_QSERVER_L_EQ_INITVAL_RMSK 0x3f
#define HWIO_SP_QSERVER_L_RX_SAMPCAL_TSETTLE_OFFS (0x0000021c)
#define HWIO_SP_QSERVER_L_RX_SAMPCAL_TSETTLE_RMSK 0xff
#define HWIO_SP_QSERVER_L_RX_SAMPCAL_ENDSAMP1_OFFS (0x00000220)
#define HWIO_SP_QSERVER_L_RX_SAMPCAL_ENDSAMP1_RMSK 0xff
#define HWIO_SP_QSERVER_L_RX_SAMPCAL_MIDPOINT1_OFFS (0x00000228)
#define HWIO_SP_QSERVER_L_RX_SAMPCAL_MIDPOINT1_RMSK 0xff
#define HWIO_SP_QSERVER_L_SIGDET_ENABLES_OFFS (0x00000230)
#define HWIO_SP_QSERVER_L_SIGDET_ENABLES_RMSK 0x3f
#define HWIO_SP_QSERVER_L_SIGDET_CNTRL_OFFS (0x00000234)
#define HWIO_SP_QSERVER_L_SIGDET_CNTRL_RMSK 0xff
#define HWIO_SP_QSERVER_L_SIGDET_DEGLITCH_CNTRL_OFFS (0x00000238)
#define HWIO_SP_QSERVER_L_SIGDET_DEGLITCH_CNTRL_RMSK 0x1f
#define HWIO_SP_QSERVER_L_RSM_START_OFFS (0x000002a8)
#define HWIO_SP_QSERVER_L_RSM_START_RMSK 0x1
#define HWIO_SP_QSERVER_L_DRVR_LOGIC_CLKDIV_OFFS (0x000002c8)
#define HWIO_SP_QSERVER_L_DRVR_LOGIC_CLKDIV_RMSK 0x1f
#define HWIO_SP_QSERVER_L_DRVR_CTRL0_OFFS (0x0000000c)
#define HWIO_SP_QSERVER_L_DRVR_CTRL0_RMSK 0x3f
#define HWIO_SP_QSERVER_L_DRVR_TAP_EN_OFFS (0x00000018)
#define HWIO_SP_QSERVER_L_DRVR_TAP_EN_RMSK 0xf
#define HWIO_SP_QSERVER_L_RX_MISC_CNTRL0_OFFS (0x000002b8)
#define HWIO_SP_QSERVER_L_RX_MISC_CNTRL0_RMSK 0xff
#define HWIO_SP_QSERVER_L_DRVR_CTRL1_OFFS (0x00000010)
#define HWIO_SP_QSERVER_L_DRVR_CTRL1_RMSK 0x1f
#define HWIO_SP_QSERVER_L_DRVR_CTRL2_OFFS (0x00000014)
#define HWIO_SP_QSERVER_L_DRVR_CTRL2_RMSK 0x1f
#define HWIO_SP_QSERVER_L_RX_RESECODE_OFFSET_OFFS (0x000002cc)
#define HWIO_SP_QSERVER_L_RX_RESECODE_OFFSET_RMSK 0x1f
#define HWIO_SP_QSERVER_L_VGA_INITVAL_OFFS (0x0000013c)
#define HWIO_SP_QSERVER_L_VGA_INITVAL_RMSK 0x3f
#define HWIO_SP_QSERVER_L_AUX_ENABLE_OFFS (0x000001a8)
#define HWIO_SP_QSERVER_L_AUX_ENABLE_RMSK 0x3
#define HWIO_SP_QSERVER_L_DLL_CTUNE_OVRWRT_OFFS (0x00000280)
#define HWIO_SP_QSERVER_L_DLL_CTUNE_OVRWRT_RMSK 0x3f
#define HWIO_SP_QSERVER_L_BIST_MODE_LANENO_SWAP_OFFS (0x0000003c)
#define HWIO_SP_QSERVER_L_BIST_MODE_LANENO_SWAP_RMSK 0xff
#define HWIO_SP_QSERVER_L_RESET_GEN_OFFS (0x00000090)
#define HWIO_SP_QSERVER_L_RESET_GEN_RMSK 0x7f
#define HWIO_SP_QSERVER_L_BIST_STATUS_OFFS (0x000000a4)
#define HWIO_SP_QSERVER_L_BIST_STATUS_RMSK 0xf
#define HWIO_SP_QSERVER_L_BIST_ERR_CNT1_STATUS_OFFS (0x000000a8)
#define HWIO_SP_QSERVER_L_BIST_ERR_CNT1_STATUS_RMSK 0xff
#define HWIO_SP_QSERVER_L_BIST_ERR_CNT2_STATUS_OFFS (0x000000ac)
#define HWIO_SP_QSERVER_L_BIST_ERR_CNT2_STATUS_RMSK 0xff

/* SATA PCS lane defines */
#define HWIO_SP_SATA_PHY_L_SATA_PHY_ALIGNP_OFFS (0x000000a4)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_ALIGNP_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_CTRL0_OFFS (0x00000014)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_CTRL0_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_POW_DWN_CTRL0_OFFS (0x00000080)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_POW_DWN_CTRL0_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_OFFS (0x000000bc)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_RMSK 0xe7
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_SW_RESET_BMSK 0x01
#define HWIO_SP_SATA_PHY_L_SATA_PHY_OOB_DET1_OFFS (0x00000068)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_OOB_DET1_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_CDR_CTRL1_OFFS (0x0000005c)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_CDR_CTRL1_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_CODE_ERR_CFG_OFFS (0x00000010)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_CODE_ERR_CFG_RMSK 0x3f
#define HWIO_SP_SATA_PHY_L_SATA_PHY_SPDNEG_CFG1_OFFS (0x00000074)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_SPDNEG_CFG1_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_SPDNEG_CFG1_SPDMODE_BMSK 0x03
#define HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_STATUS_OFFS (0x000000ec)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_STATUS_RMSK 0xef
#define HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_STATUS_INT_C_READY_BMSK 0x2
#define HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_CTRL1_OFFS (0x00000018)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_CTRL1_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_OFFLINE_OFFS (0x000000c0)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_OFFLINE_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG0_OFFS (0x0000001c)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG0_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG4_OFFS (0x0000002c)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG4_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG5_OFFS (0x00000030)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG5_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG6_OFFS (0x00000034)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG6_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_TX_DATA_CTRL_OFFS (0x00000088)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_TX_DATA_CTRL_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS (0x000000e0)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_CHECK_DONE_BMSK 0x1
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT0_STATUS_OFFS (0x000000d8)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT0_STATUS_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT1_STATUS_OFFS (0x000000dc)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT1_STATUS_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN0_OFFS (0x0000008c)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN0_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN1_OFFS (0x00000090)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN1_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN2_OFFS (0x00000094)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN2_RMSK 0xff
#define HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS (0x00000098)
#define HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_RMSK 0xff

/**/
#define SP0_SATA_PHY_CMN_SATA_PCS_CMN_REG_BASE                                 \
  (SP0_CM_SERVER_SATA_SW_BASE + 0x00000400)
#define SP1_SATA_PHY_CMN_SATA_PCS_CMN_REG_BASE                                 \
  (SP1_CM_SERVER_SATA_SW_BASE + 0x00000400)

#define HWIO_SP_SATA_PHY_CMN_SATA_PHY_SERDES_START_OFFS (0x00000000)
#define HWIO_SP_SATA_PHY_CMN_SATA_PHY_SERDES_START_RMSK 0x1
#define HWIO_SP_SATA_PHY_CMN_SATA_PHY_RESET_CTRL_OFFS (0x00000010)
#define HWIO_SP_SATA_PHY_CMN_SATA_PHY_RESET_CTRL_RMSK 0x1
#define HWIO_SP_SATA_PHY_CMN_SATA_PHY_TEST_DEBUG_CTRL_OFFS (0x0000000c)
#define HWIO_SP_SATA_PHY_CMN_SATA_PHY_TEST_DEBUG_CTRL_RMSK 0xff

/*
 * Custom Define
 */

#define HWIO_IMC_MSA_C_ADDR 0xFF6FBC0300
#define HWIO_SATA_QSMMU_GBPA_OFFS 0x00800044

#define HWIO_SATA_CAP_SSS BIT27
#define HWIO_SATA_CAP_S64A BIT31
#define HWIO_SATA_GHC_AHCI_ENABLE 0x80000000
#define HWIO_SATA_GHC_HBA_RESET 0x1
#define HWIO_SATA_P0SCTL_IPM_INIT 0x00000300
#define HWIO_SATA_P0CMD_START BIT0
#define HWIO_SATA_P0CMD_SUD BIT1
#define HWIO_SATA_P0CMD_POD BIT2
#define HWIO_SATA_P0CMD_FRE BIT4
#define HWIO_SATA_P0CMD_FR BIT14
#define HWIO_SATA_P0CMD_CR BIT15
#define HWIO_SATA_P0CMD_CPD BIT20
#define HWIO_SATA_P0CMD_ATAPI BIT24
#define HWIO_SATA_P0CMD_DLAE BIT25
#define HWIO_SATA_P0CMD_ALPE BIT26
#define HWIO_SATA_P0CMD_ICC_RMSK (BIT28 | BIT29 | BIT30 | BIT31)
#define HWIO_SATA_P0CMD_ICC_ACTIVE BIT28
#define HWIO_SATA_P0TFD_BSY BIT7
#define HWIO_SATA_P0TFD_DRQ BIT3

#define HWIO_SATA_POWER_MGMT_CTR_OFFS 0x00000C80

#endif /* __BM_SATA_REGS_H__ */
