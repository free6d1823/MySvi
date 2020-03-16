/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "hdts/Base.h"
#include "hdts/hdts_common.h"
#include "hdts/hdts_interrupt.h"
#include "hdts/hdts_misc.h"
#include "hdts/hdts_shell.h"
#include "target/delay.h"

#include "HALsataHWIO.h"
#include "hdts/Target_cust.h"
#include "asm/hal/HALhwio.h"
#include "asm/mach/hal/HALbootHWIO.h"
#include "asm/mach/hal/HALclkHWIO.h"
#include "asm/mach/monaco/common/boot_util.h"
#include "sata_defs.h"
#include "sata_init.h"
#include "sata_regs.h"

#include "asm/irq.h"
#include "target/cmdline.h"
#include "target/irq.h"

/* sata phy init polling time 5s */
#define SATA_PHY_POLL_MAX 5000

// extern
extern volatile UINT32 gSataIntrMaskEn;

// declare
UINTN Sata_Reg_Base[SATA_CONTROLLER_NUMBER] = {
    I0_SATA_REG_BASE, I1_SATA_REG_BASE, I2_SATA_REG_BASE, I3_SATA_REG_BASE,
    I4_SATA_REG_BASE, I5_SATA_REG_BASE, I6_SATA_REG_BASE, I7_SATA_REG_BASE};

UINTN Qserver_Com_Reg_Base[SATA_SP_NUMBER] = {SP0_QSERVER_COM_REG_BASE,
                                              SP1_QSERVER_COM_REG_BASE};

UINTN Qserver_Lane_Reg_Base[SATA_CONTROLLER_NUMBER] = {
    SP0_QSERVER_L0_SATA_LANE_REG_BASE, SP0_QSERVER_L1_SATA_LANE_REG_BASE,
    SP0_QSERVER_L2_SATA_LANE_REG_BASE, SP0_QSERVER_L3_SATA_LANE_REG_BASE,
    SP1_QSERVER_L0_SATA_LANE_REG_BASE, SP1_QSERVER_L1_SATA_LANE_REG_BASE,
    SP1_QSERVER_L2_SATA_LANE_REG_BASE, SP1_QSERVER_L3_SATA_LANE_REG_BASE};

UINTN Sata_Pcs_Lane_Reg_Base[SATA_CONTROLLER_NUMBER] = {
    SP0_SATA_PHY_L0_SATA_PCS_LANE_REG_BASE,
    SP0_SATA_PHY_L1_SATA_PCS_LANE_REG_BASE,
    SP0_SATA_PHY_L2_SATA_PCS_LANE_REG_BASE,
    SP0_SATA_PHY_L3_SATA_PCS_LANE_REG_BASE,
    SP1_SATA_PHY_L0_SATA_PCS_LANE_REG_BASE,
    SP1_SATA_PHY_L1_SATA_PCS_LANE_REG_BASE,
    SP1_SATA_PHY_L2_SATA_PCS_LANE_REG_BASE,
    SP1_SATA_PHY_L3_SATA_PCS_LANE_REG_BASE};

UINTN Sata_Phy_Cmn_Reg_Base[SATA_SP_NUMBER] = {
    SP0_SATA_PHY_CMN_SATA_PCS_CMN_REG_BASE,
    SP1_SATA_PHY_CMN_SATA_PCS_CMN_REG_BASE};

static Sata_Phy_Init_t QserverCommonRegSp0InitTable[] = {
    {HWIO_SP_QSERVER_COM_CMN_CONFIG_OFFS, 0x08},
    {HWIO_SP_QSERVER_COM_CLK_SELECT_OFFS, 0x08},
    {HWIO_SP_QSERVER_COM_SYSCLK_EN_SEL_OFFS, 0xEC},
    {HWIO_SP_QSERVER_COM_SYSCLK_BUF_ENABLE_OFFS, 0x07},
    {HWIO_SP_QSERVER_COM_SYS_CLK_CTRL_OFFS, 0x02},
    {HWIO_SP_QSERVER_COM_BIAS_EN_CLKBUFLR_EN_OFFS, 0x0C},
    {HWIO_SP_QSERVER_COM_CLK_ENABLE1_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_HSCLK_SEL1_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_PLL_IVCO_OFFS, 0xF0},
    {HWIO_SP_QSERVER_COM_BG_CTRL_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_BGT_TRIM_OFFS, 0x0F},
    {HWIO_SP_QSERVER_COM_BGV_TRIM_OFFS, 0x20},
    {HWIO_SP_QSERVER_COM_VREGCLK_DIV1_OFFS, 0x29},
    {HWIO_SP_QSERVER_COM_BG_TIMER_OFFS, 0x0A},
    {HWIO_SP_QSERVER_COM_RESETSM_CNTRL2_OFFS, 0x0C},
    {HWIO_SP_QSERVER_COM_LOCK_CMP_EN_OFFS, 0x04},
    {HWIO_SP_QSERVER_COM_PLL_CCTRL_MODE0_OFFS, 0x34},
    {HWIO_SP_QSERVER_COM_PLL_RCTRL_MODE0_OFFS, 0x16},
    {HWIO_SP_QSERVER_COM_CP_CTRL_MODE0_OFFS, 0x08},
    {HWIO_SP_QSERVER_COM_SSC_EN_CENTER_OFFS, 0x01},
    {HWIO_SP_QSERVER_COM_SSC_PER1_OFFS, 0x40},
    {HWIO_SP_QSERVER_COM_SSC_PER2_OFFS, 0x01},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE1_OFFS, 0x2F},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE2_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE3_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_DEC_START_MODE0_OFFS, 0x95},
    {HWIO_SP_QSERVER_COM_DEC_START_MSB_MODE0_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START1_MODE0_OFFS, 0x1F},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START2_MODE0_OFFS, 0x85},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START3_MODE0_OFFS, 0x0F},
    {HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN0_MODE0_OFFS, 0x3F},
    {HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN1_MODE0_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_VCO_TUNE_MAP_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_LOCK_CMP1_MODE0_OFFS, 0xFF},
    {HWIO_SP_QSERVER_COM_LOCK_CMP2_MODE0_OFFS, 0x3B},
    {HWIO_SP_QSERVER_COM_LOCK_CMP3_MODE0_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_CORECLK_DIV_OFFS, 0x05},
    {HWIO_SP_QSERVER_COM_CORE_CLK_EN_OFFS, 0x70},
    {HWIO_SP_QSERVER_COM_SVS_MODE_CLK_SEL_OFFS, 0x01}};

static Sata_Phy_Init_t QserverCommonRegSp1InitTable[] = {
    {HWIO_SP_QSERVER_COM_CMN_CONFIG_OFFS, 0x08},
    {HWIO_SP_QSERVER_COM_SYSCLK_EN_SEL_OFFS, 0x24},
    {HWIO_SP_QSERVER_COM_SYSCLK_BUF_ENABLE_OFFS, 0x07},
    {HWIO_SP_QSERVER_COM_SYS_CLK_CTRL_OFFS, 0x02},
    {HWIO_SP_QSERVER_COM_BIAS_EN_CLKBUFLR_EN_OFFS, 0x0C},
    {HWIO_SP_QSERVER_COM_CLK_ENABLE1_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_HSCLK_SEL1_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_PLL_IVCO_OFFS, 0xF0},
    {HWIO_SP_QSERVER_COM_BG_CTRL_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_BGT_TRIM_OFFS, 0x0F},
    {HWIO_SP_QSERVER_COM_BGV_TRIM_OFFS, 0x20},
    {HWIO_SP_QSERVER_COM_VREGCLK_DIV1_OFFS, 0x29},
    {HWIO_SP_QSERVER_COM_BG_TIMER_OFFS, 0x0A},
    {HWIO_SP_QSERVER_COM_RESETSM_CNTRL2_OFFS, 0x0C},
    {HWIO_SP_QSERVER_COM_LOCK_CMP_EN_OFFS, 0x04},
    {HWIO_SP_QSERVER_COM_PLL_CCTRL_MODE0_OFFS, 0x34},
    {HWIO_SP_QSERVER_COM_PLL_RCTRL_MODE0_OFFS, 0x16},
    {HWIO_SP_QSERVER_COM_CP_CTRL_MODE0_OFFS, 0x08},
    {HWIO_SP_QSERVER_COM_SSC_EN_CENTER_OFFS, 0x01},
    {HWIO_SP_QSERVER_COM_SSC_PER1_OFFS, 0x40},
    {HWIO_SP_QSERVER_COM_SSC_PER2_OFFS, 0x01},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE1_OFFS, 0x2F},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE2_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE3_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_DEC_START_MODE0_OFFS, 0x95},
    {HWIO_SP_QSERVER_COM_DEC_START_MSB_MODE0_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START1_MODE0_OFFS, 0x1F},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START2_MODE0_OFFS, 0x85},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START3_MODE0_OFFS, 0x0F},
    {HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN0_MODE0_OFFS, 0x3F},
    {HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN1_MODE0_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_VCO_TUNE_MAP_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_LOCK_CMP1_MODE0_OFFS, 0xFF},
    {HWIO_SP_QSERVER_COM_LOCK_CMP2_MODE0_OFFS, 0x3B},
    {HWIO_SP_QSERVER_COM_LOCK_CMP3_MODE0_OFFS, 0x00},
    {HWIO_SP_QSERVER_COM_CORECLK_DIV_OFFS, 0x05},
    {HWIO_SP_QSERVER_COM_CORE_CLK_EN_OFFS, 0x70},
    {HWIO_SP_QSERVER_COM_SVS_MODE_CLK_SEL_OFFS, 0x01}};

static Sata_Phy_Init_t QserverLaneRegInitTable[] = {
    {HWIO_SP_QSERVER_L_RX_EN_SIGNAL_OFFS, 0xC3},
    {HWIO_SP_QSERVER_L_PARALLEL_RATE_OFFS, 0x3F},
    {HWIO_SP_QSERVER_L_DLL_HIGHDATARATE_OFFS, 0x15},
    {HWIO_SP_QSERVER_L_DLL_ENABLE_WAIT_OFFS, 0x08},
    {HWIO_SP_QSERVER_L_DCC_INIT_OFFS, 0x00},
    {HWIO_SP_QSERVER_L_DCC_GAIN_OFFS, 0x00},
    {HWIO_SP_QSERVER_L_UCDR_FO_TO_SO_DELAY_OFFS, 0x00},
    {HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE0_OFFS, 0x0B},
    {HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE0_OFFS, 0x03},
    {HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE1_OFFS, 0x8A},
    {HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE1_OFFS, 0x06},
    {HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE2_OFFS, 0x8A},
    {HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE2_OFFS, 0x06},
    {HWIO_SP_QSERVER_L_UCDR_SO_CONFIG_OFFS, 0x28},
    {HWIO_SP_QSERVER_L_TX_BAND_MODE_OFFS, 0x24},
    {HWIO_SP_QSERVER_L_RX_BAND_OFFS, 0x38},
    {HWIO_SP_QSERVER_L_LANE_MODE_OFFS, 0x1A},
    {HWIO_SP_QSERVER_L_RX_RCVR_PATH0_OFFS, 0x00},
    {HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE0_OFFS, 0x3E},
    {HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE1_OFFS, 0x5E},
    {HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE2_OFFS, 0x7E},
    {HWIO_SP_QSERVER_L_DRVR_CTRL1_OFFS, 0x08},
    {HWIO_SP_QSERVER_L_TX_MARGINING_OFFS, 0x4A},
    {HWIO_SP_QSERVER_L_TX_PRE_OFFS, 0x40},
    {HWIO_SP_QSERVER_L_TX_POST_OFFS, 0x53},
    {HWIO_SP_QSERVER_L_CML_CTRL_MODE0_OFFS, 0x0A},
    {HWIO_SP_QSERVER_L_CML_CTRL_MODE1_OFFS, 0x0A},
    {HWIO_SP_QSERVER_L_CML_CTRL_MODE2_OFFS, 0x0A},
    {HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE0_OFFS, 0x07},
    {HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE1_OFFS, 0x01},
    {HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE2_OFFS, 0x01},
    {HWIO_SP_QSERVER_L_MIXER_CTRL_MODE0_OFFS, 0x03},
    {HWIO_SP_QSERVER_L_MIXER_CTRL_MODE1_OFFS, 0x03},
    {HWIO_SP_QSERVER_L_MIXER_CTRL_MODE2_OFFS, 0x03},
    {HWIO_SP_QSERVER_L_PSM_RX_EN_CAL_OFFS, 0x02},
    {HWIO_SP_QSERVER_L_TS0_TIMER_OFFS, 0x01},
    {HWIO_SP_QSERVER_L_RX_RESECODE_OFFSET_OFFS, 0x0B},
    {HWIO_SP_QSERVER_L_VGA_INITVAL_OFFS, 0x12},
    {HWIO_SP_QSERVER_L_EQ_INITVAL_OFFS, 0x17},
    {HWIO_SP_QSERVER_L_RX_SAMPCAL_TSETTLE_OFFS, 0x40},
    {HWIO_SP_QSERVER_L_RX_SAMPCAL_ENDSAMP1_OFFS, 0x60},
    {HWIO_SP_QSERVER_L_RX_SAMPCAL_MIDPOINT1_OFFS, 0x40},
    {HWIO_SP_QSERVER_L_SIGDET_ENABLES_OFFS, 0x21},
    {HWIO_SP_QSERVER_L_SIGDET_CNTRL_OFFS, 0x8A},
    {HWIO_SP_QSERVER_L_SIGDET_DEGLITCH_CNTRL_OFFS, 0x08},
    {HWIO_SP_QSERVER_L_RSM_START_OFFS, 0x01},
    {HWIO_SP_QSERVER_L_DRVR_LOGIC_CLKDIV_OFFS, 0x14},
    {HWIO_SP_QSERVER_L_DRVR_CTRL0_OFFS, 0x11},
    {HWIO_SP_QSERVER_L_DRVR_TAP_EN_OFFS, 0x05},
    {HWIO_SP_QSERVER_L_RX_MISC_CNTRL0_OFFS, 0x80}};

static Sata_Phy_Init_t SataPcsLaneRegInitTable[] = {
    {HWIO_SP_SATA_PHY_L_SATA_PHY_ALIGNP_OFFS, 0x5F},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_CTRL0_OFFS, 0x20},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_POW_DWN_CTRL0_OFFS, 0x01},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_OFFS, 0x00},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_OOB_DET1_OFFS, 0xDD},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_CDR_CTRL1_OFFS, 0x52},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_CODE_ERR_CFG_OFFS, 0x08}};

static Sata_Phy_Init_t SataPhyCmnRegInitTable[] = {
    {HWIO_SP_SATA_PHY_CMN_SATA_PHY_SERDES_START_OFFS, 0x01},
    {HWIO_SP_SATA_PHY_CMN_SATA_PHY_RESET_CTRL_OFFS, 0x00}};

// function
/**
 * @brief       Sata clocks init.
 *
 * @ret		None
 */
void sata_clocks_set(void) {
#ifndef CONFIG_TESTOS_EMU
  printf("SATA clocks init\r\n");

  /* SATA
   * CSFPB_CMD_RCGR/RXOOB_CMD_RCGR/PMALIVE_CMD_RCGR/Q22_CMD_RCGR/AHB_CMD_RCGR */
  out_dword(HWIO_GCCMW_SATA_SS_CSFPB_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_RXOOB_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_PMALIVE_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_Q22_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_AHB_CMD_RCGR_ADDR, 0x3);

  /* gccmw_sata_ln0_asic_clk  and gccmw_sata_ln0_rx_clk */
  out_dword(HWIO_GCCMW_SATA_LN0_ASIC_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN0_ASIC_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_LN0_RX_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN0_RX_CMD_RCGR_ADDR, 0x3);

  /* gccmw_sata_ln0_asic_clk  and gccmw_sata_ln0_rx_clk */
  out_dword(HWIO_GCCMW_SATA_LN1_ASIC_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN1_ASIC_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_LN1_RX_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN1_RX_CMD_RCGR_ADDR, 0x3);

  /* gccmw_sata_ln0_asic_clk  and gccmw_sata_ln0_rx_clk */
  out_dword(HWIO_GCCMW_SATA_LN2_ASIC_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN2_ASIC_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_LN2_RX_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN2_RX_CMD_RCGR_ADDR, 0x3);

  /* gccmw_sata_ln0_asic_clk  and gccmw_sata_ln0_rx_clk */
  out_dword(HWIO_GCCMW_SATA_LN3_ASIC_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN3_ASIC_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_LN3_RX_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN3_RX_CMD_RCGR_ADDR, 0x3);

  /* gccmw_sata_ln0_asic_clk  and gccmw_sata_ln0_rx_clk */
  out_dword(HWIO_GCCMW_SATA_LN4_ASIC_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN4_ASIC_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_LN4_RX_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN4_RX_CMD_RCGR_ADDR, 0x3);

  /* gccmw_sata_ln0_asic_clk  and gccmw_sata_ln0_rx_clk */
  out_dword(HWIO_GCCMW_SATA_LN5_ASIC_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN5_ASIC_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_LN5_RX_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN5_RX_CMD_RCGR_ADDR, 0x3);

  /* gccmw_sata_ln0_asic_clk  and gccmw_sata_ln0_rx_clk */
  out_dword(HWIO_GCCMW_SATA_LN6_ASIC_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN6_ASIC_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_LN6_RX_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN6_RX_CMD_RCGR_ADDR, 0x3);

  /* gccmw_sata_ln0_asic_clk  and gccmw_sata_ln0_rx_clk */
  out_dword(HWIO_GCCMW_SATA_LN7_ASIC_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN7_ASIC_CMD_RCGR_ADDR, 0x3);
  out_dword(HWIO_GCCMW_SATA_LN7_RX_CFG_RCGR_ADDR, 0x200);
  out_dword(HWIO_GCCMW_SATA_LN7_RX_CMD_RCGR_ADDR, 0x3);
#endif
}

/**
 * @brief       Sata phy qserver common registers init
 *
 */
void sata_init_qserver_common_reg_sp(UINT8 spNum) {
  UINTN Base;
  UINTN TotalItems, i;

  if (spNum == 0) {
    Base = Qserver_Com_Reg_Base[0];

    TotalItems = sizeof(QserverCommonRegSp0InitTable) / sizeof(Sata_Phy_Init_t);

    for (i = 0; i < TotalItems; i++) {
      out_dword(Base + QserverCommonRegSp0InitTable[i].Offset,
                QserverCommonRegSp0InitTable[i].Value);
    }
  } else {
    Base = Qserver_Com_Reg_Base[1];

    TotalItems = sizeof(QserverCommonRegSp1InitTable) / sizeof(Sata_Phy_Init_t);

    for (i = 0; i < TotalItems; i++) {
      out_dword(Base + QserverCommonRegSp1InitTable[i].Offset,
                QserverCommonRegSp1InitTable[i].Value);
    }
  }
}

/**
 * @brief       Sata phy qserver lane registers init
 *
 */
void sata_init_qserver_lane_reg(UINT8 lnNum) {
  UINTN Base;
  UINTN TotalItems, i;

  if (lnNum >= SATA_CONTROLLER_NUMBER)
    return;

  Base = Qserver_Lane_Reg_Base[lnNum];
  TotalItems = sizeof(QserverLaneRegInitTable) / sizeof(Sata_Phy_Init_t);

  for (i = 0; i < TotalItems; i++) {
    out_dword(Base + QserverLaneRegInitTable[i].Offset,
              QserverLaneRegInitTable[i].Value);
  }
}

/**
 * @brief       Sata phy pcs lane registers init
 *
 */
void sata_init_sata_pcs_lane_reg(UINT8 lnNum) {
  UINTN Base;
  UINTN TotalItems, i;

  if (lnNum >= SATA_CONTROLLER_NUMBER)
    return;

  Base = Sata_Pcs_Lane_Reg_Base[lnNum];
  TotalItems = sizeof(SataPcsLaneRegInitTable) / sizeof(Sata_Phy_Init_t);

  for (i = 0; i < TotalItems; i++) {
    out_dword(Base + SataPcsLaneRegInitTable[i].Offset,
              SataPcsLaneRegInitTable[i].Value);
  }
}

/**
 * @brief       Sata phy cmn registers init
 *
 */
void sata_init_phy_cmn_reg(UINT8 spNum) {
  UINTN Base;
  UINTN TotalItems, i;
  if (spNum >= SATA_SP_NUMBER)
    return;

  Base = Sata_Phy_Cmn_Reg_Base[spNum];
  TotalItems = sizeof(SataPhyCmnRegInitTable) / sizeof(Sata_Phy_Init_t);

  for (i = 0; i < TotalItems; i++) {
    out_dword(Base + SataPhyCmnRegInitTable[i].Offset,
              SataPhyCmnRegInitTable[i].Value);
  }
}

/**
 * @brief       Sata phy init
 *
 * @param[in]   spNum   Sata sp number. (0~1)
 *
 * @ret		None
 */
void sata_phy_set(UINT8 spNum) {
  if (spNum == 0) {
    /* Qserver common */
    sata_init_qserver_common_reg_sp(SATA_SP0);

    /* Qserver lane */
    sata_init_qserver_lane_reg(SATA_SP0_LANE0);
    sata_init_qserver_lane_reg(SATA_SP0_LANE1);
    sata_init_qserver_lane_reg(SATA_SP0_LANE2);
    sata_init_qserver_lane_reg(SATA_SP0_LANE3);

    /* SATA PCS */
    sata_init_sata_pcs_lane_reg(SATA_SP0_LANE0);
    sata_init_sata_pcs_lane_reg(SATA_SP0_LANE1);
    sata_init_sata_pcs_lane_reg(SATA_SP0_LANE2);
    sata_init_sata_pcs_lane_reg(SATA_SP0_LANE3);

    /* Phy CMN reg */
    sata_init_phy_cmn_reg(SATA_SP0);
  } else {
    /* Qserver common */
    sata_init_qserver_common_reg_sp(SATA_SP1);

    /* Qserver lane */
    sata_init_qserver_lane_reg(SATA_SP1_LANE0);
    sata_init_qserver_lane_reg(SATA_SP1_LANE1);
    sata_init_qserver_lane_reg(SATA_SP1_LANE2);
    sata_init_qserver_lane_reg(SATA_SP1_LANE3);

    /* SATA PCS */
    sata_init_sata_pcs_lane_reg(SATA_SP1_LANE0);
    sata_init_sata_pcs_lane_reg(SATA_SP1_LANE1);
    sata_init_sata_pcs_lane_reg(SATA_SP1_LANE2);
    sata_init_sata_pcs_lane_reg(SATA_SP1_LANE3);

    /* Phy CMN reg */
    sata_init_phy_cmn_reg(SATA_SP1);
  }
}

/**
 * @brief       Sata get phy C_Ready status
 *
 * @param[in]   spNum   Sata sp number. (0~1)
 *
 * @retval	UINT32 val	phy C_Ready status
 */
UINT32 sata_get_phy_status(UINT8 spNum) {
  UINT32 val = 0;
  UINTN Base;

  if (spNum >= SATA_SP_NUMBER)
    return val;

  Base = Qserver_Com_Reg_Base[spNum];
  val = in_dword(Base + HWIO_SP_QSERVER_COM_C_READY_STATUS_OFFS);
  val &= HWIO_SP_QSERVER_COM_C_READY_STATUS_RMSK;
  return val;
}

/**
 * @brief       Sata get lane C_Ready status
 *
 * @param[in]   spNum   Sata lane number. (0~7)
 *
 * @retval	UINT32 val	lane C_Ready status
 */
UINT32 sata_get_lane_status(UINT8 lnNum) {
  UINT32 val = 0;
  UINTN Base;

  if (lnNum >= SATA_CONTROLLER_NUMBER)
    return val;

  Base = Sata_Pcs_Lane_Reg_Base[lnNum];
  val = in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_STATUS_OFFS);
  val &= HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_STATUS_INT_C_READY_BMSK;
  return val;
}

/**
 * @brief       Sata phy init and C_Ready check
 *
 * @return      None
 */
void sata_phy_set_and_check(void) {
#ifndef CONFIG_TESTOS_EMU
  UINT32 Count = 0;
  UINT32 ln = 0;

  printf("SATA phy set and ready status check\r\n");

  sata_phy_set(SATA_SP0);
  Count = SATA_PHY_POLL_MAX;
  while (Count -= 10) {
    if (sata_get_phy_status(SATA_SP0))
      break;
    udelay(100000);
  }

  if (Count == 0) {
    printf("[ERROR]Failed to start SATA PHY 0\r\n");
  }

  sata_phy_set(SATA_SP1);
  Count = SATA_PHY_POLL_MAX;
  while (Count -= 10) {
    if (sata_get_phy_status(SATA_SP1))
      break;
    udelay(100000);
  }

  if (Count == 0) {
    printf("[ERROR]Failed to start SATA PHY 1\r\n");
  }

  // poll lane init ready
  for (ln = 0; ln < SATA_CONTROLLER_NUMBER; ln++) {
    Count = SATA_PHY_POLL_MAX;
    while (Count -= 10) {
      if (sata_get_lane_status(ln))
        break;
      udelay(100000);
    }

    if (Count == 0) {
      printf("[ERROR]Failed to init SATA lane %d\r\n", ln);
    }
  }
#endif
}

/**
 * @brief       Sata cap sss set
 *
 */
void sata_cap_sss_set(UINT32 ControllerNum, BOOLEAN Enable) {
  UINT32 val = 0;
  val = in_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_CAP_OFFS);
  if (Enable) {
    val &= (~HWIO_SATA_CAP_SSS_BMSK);
    val |= HWIO_SATA_CAP_SSS_BMSK;
  } else {
    val &= (~HWIO_SATA_CAP_SSS_BMSK);
  }
  out_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_CAP_OFFS, val);
}

/**
 * @brief       Sata cap smps set
 *
 */
void sata_cap_smps_set(UINT32 ControllerNum, BOOLEAN Enable) {
  UINT32 val = 0;
  val = in_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_CAP_OFFS);

  if (Enable) {
    val &= (~HWIO_SATA_CAP_SMPS_BMSK);
    val |= HWIO_SATA_CAP_SMPS_BMSK;
  } else {
    val &= (~HWIO_SATA_CAP_SMPS_BMSK);
  }
  out_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_CAP_OFFS, val);
}

/**
 * @brief       Sata pi set
 *
 */
void sata_pi_set(UINT32 ControllerNum) {
  out_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_PI_OFFS,
            HWIO_SATA_PI_PI_BMSK);
}

/**
 * @brief       Sata px cmd hpcp set
 *
 */
void sata_px_cmd_hpcp_set(UINT32 ControllerNum, BOOLEAN Enable) {
  UINT32 val = 0;
  val = in_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_P0CMD_OFFS);
  if (Enable) {
    val &= (~HWIO_SATA_P0CMD_HPCP_BMSK);
    val |= HWIO_SATA_P0CMD_HPCP_BMSK;
  } else {
    val &= (~HWIO_SATA_P0CMD_HPCP_BMSK);
  }
  out_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_P0CMD_OFFS, val);
}

/**
 * @brief       Sata px cmd mpsp set
 *
 */
void sata_px_cmd_mpsp_set(UINT32 ControllerNum, BOOLEAN Enable) {
  UINT32 val = 0;
  val = in_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_P0CMD_OFFS);
  if (Enable) {
    val &= (~HWIO_SATA_P0CMD_MPSP_BMSK);
    val |= HWIO_SATA_P0CMD_MPSP_BMSK;
  } else {
    val &= (~HWIO_SATA_P0CMD_MPSP_BMSK);
  }
  out_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_P0CMD_OFFS, val);
}

/**
 * @brief       Sata px cmd cpd set
 *
 */
void sata_px_cmd_cpd_set(UINT32 ControllerNum, BOOLEAN Enable) {
  UINT32 val = 0;
  val = in_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_P0CMD_OFFS);
  if (Enable) {
    val &= (~HWIO_SATA_P0CMD_CPD_BMSK);
    val |= HWIO_SATA_P0CMD_CPD_BMSK;
  } else {
    val &= (HWIO_SATA_P0CMD_CPD_BMSK);
  }
  out_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_P0CMD_OFFS, val);
}

/**
 * @brief       Sata sdfe set
 *
 */
void sata_set_sdfe_set(UINT32 ControllerNum) {
  UINT32 val = 0;
  val = in_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_BISTCR_OFFS);
  val |= HWIO_SATA_BISTCR_SDFE_BMSK;
  out_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_BISTCR_OFFS, val);
}

/**
 * @brief       Sata errlossen set
 *
 */
void sata_errlossen_set(UINT32 ControllerNum) {
  UINT32 val = 0;
  val = in_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_BISTCR_OFFS);
  val |= HWIO_SATA_BISTCR_ERRLOSSEN_BMSK;
  out_dword(Sata_Reg_Base[ControllerNum] + HWIO_SATA_BISTCR_OFFS, val);
}

/**
 * @brief       Sata caps set
 *
 */
void sata_set_caps(UINT32 ControllerNum) {
  /* CAP.SSS (support for staggered spin-up) - Yes */
  sata_cap_sss_set(ControllerNum, TRUE);

  /* CAP.SMPS (support for mechanical presence switches) */
  sata_cap_smps_set(ControllerNum, FALSE);

  /* PI (ports implemented) - Port 0 */
  sata_pi_set(ControllerNum);

  /* PxCMD.HPCP (whether port is hot plug capable) - No */
  sata_px_cmd_hpcp_set(ControllerNum, FALSE);

  /* PxCMD.MPSP (whether mechanical presence switch is attached
     to the port) - No */
  sata_px_cmd_mpsp_set(ControllerNum, FALSE);

  /* PxCMD.CPD (whether cold presence detect logic is attached
     to the port) - No */
  sata_px_cmd_cpd_set(ControllerNum, FALSE);

  /* Set SDFE bit to force link stable at gen 3 */
  sata_set_sdfe_set(ControllerNum);

  /* Set ERRLOSSEN bit */
  sata_errlossen_set(ControllerNum);
}

/**
 * @brief       Sata common registers init
 *
 * @return      None
 */
void sata_regs_init(void) {
  UINTN i = 0;

  printf("SATA registers init\r\n");
  for (i = 0; i < SATA_CONTROLLER_NUMBER; i++) {
    sata_set_caps(i);
  }
}

/**
 * @brief       CBF power init
 *
 * @return      None
 */
void cbf_init(void) {
  printf("CBF init\r\n");

  /* Assert CLAMP_CBFPD */
  HWIO_APCS_PM_CBF_CBF_PWR_CTL_OUT(
      HWIO_APCS_PM_CBF_CBF_PWR_CTL_CLAMP_CBFPD_BMSK);
  udelay(100);

  /* Deassert CLAMP_CBFPD, assert APC_ON */
  HWIO_APCS_PM_CBF_CBF_PWR_CTL_OUT(
      HWIO_APCS_PM_CBF_CBF_PWR_CTL_PMIC_APC_ON_BMSK);
  udelay(100);
}

/**
 * @brief       Swap
 *
 * @param[in]   buf    char8 pointer, need to swap. Store the result back to buf
 *
 * @param[in]   len    buf len, even number
 *
 * @return      None
 */
void swap_pair_data(CHAR8 *buf, UINT32 len) {
  UINT32 i = 0;
  CHAR8 tmp = 0;

  for (i = 0; i < len; i = i + 2) {
    tmp = buf[i];
    buf[i] = buf[i + 1];
    buf[i + 1] = tmp;
  }
}

// 0:Gen1, 1:Gen2, 2:Gen3
void sata_gen_speed_set(UINT32 spd) {
  UINT32 i = 0;
  UINT32 val = 0;
  UINTN Base;

  printf("Sata set phy speed to Gen%d\r\n", (spd + 1));
  for (i = 0; i < SATA_CONTROLLER_NUMBER; i++) {
    Base = Sata_Pcs_Lane_Reg_Base[i];
    val = in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_SPDNEG_CFG1_OFFS);

    val &= (~HWIO_SP_SATA_PHY_L_SATA_PHY_SPDNEG_CFG1_SPDMODE_BMSK);
    val |= spd;

    out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_SPDNEG_CFG1_OFFS, val);
  }
}

/**
 * @brief       Sata init all phy, clocks, and common registers setting
 *
 * @return      None
 */
void sata_init(UINT32 spd) {
  printf("SATA init start...\r\n");

  cbf_init();

  sata_clocks_set();

  sata_gen_speed_set(spd);

  sata_phy_set_and_check();

  sata_regs_init();

  printf("SATA init end!\r\n");
}

/**
 * @brief       Sata enum hard disk function
 *
 * @param[in]   ControllerNum    Sata lane number. (0~7)
 *
 * @return      None
 */
void sata_enum(UINT32 ControllerNum) {
  UINT32 val = 0;
  UINT32 genspd = 0;
  UINT64 delay = 500;
  UINT32 capability = 0;
  UINTN Base = Sata_Reg_Base[ControllerNum];
  // init address in sys_imem
  SATA_AHCI_COMMAND_LIST_t *cmdListAddr =
      (SATA_AHCI_COMMAND_LIST_t *)SATA_CMD_LIST_SMEM_ADDR;
  SATA_AHCI_RECEIVED_FIS_t *fisRecvAddr =
      (SATA_AHCI_RECEIVED_FIS_t *)SATA_FIS_RECV_SMEM_ADDR;
  //-------------------------------------------------
  // sys imem addr scope: 0xff70000000 ~ 0xff70040000
  // fis receive addr: 0xff70020000
  // cmd list addr: 0xff70020400
  // cmd table addr: 0xff70020800
  // prdt addr: 0xff70020C00
  //-------------------------------------------------

  printf("SATA %d enum hard disk start...\r\n", ControllerNum);

  // Modify sata r/w attribute to non-cacheable
  out_dword(HWIO_IMC_MSA_C_ADDR, 0);
  out_dword(Base + HWIO_SATA_QSMMU_GBPA_OFFS, 0x80001015);
  udelay(10000);

  // Make sure that GHC.AE bit is set before accessing any AHCI registers
  val = in_dword(Base + HWIO_SATA_GHC_OFFS);
  if ((val & HWIO_SATA_GHC_AHCI_ENABLE) == 0) {
    out_dword(Base + HWIO_SATA_GHC_OFFS, val | HWIO_SATA_GHC_AHCI_ENABLE);
  }

  // reset and wait for reset effect
  out_dword(Base + HWIO_SATA_GHC_OFFS, val | HWIO_SATA_GHC_HBA_RESET);
  do {
    val = in_dword(Base + HWIO_SATA_GHC_OFFS);

    if ((val & HWIO_SATA_GHC_HBA_RESET) == 0) {
      break;
    }

    udelay(10000);
    delay--;
  } while (delay > 0);

  if (delay == 0) {
    printf("[ERROR]SATA reset fail!\r\n");
    return;
  }

  // Collect AHCI controller information
  capability = in_dword(Base + HWIO_SATA_CAP_OFFS);

  // Make sure that GHC.AE bit is set before accessing any AHCI registers
  val = in_dword(Base + HWIO_SATA_GHC_OFFS);
  if ((val & HWIO_SATA_GHC_AHCI_ENABLE) == 0) {
    out_dword(Base + HWIO_SATA_GHC_OFFS, val | HWIO_SATA_GHC_AHCI_ENABLE);
  }
  printf("SATA GHC[0x%x] 0x%x\r\n", (Base + HWIO_SATA_GHC_OFFS), val);

  // set SATA_CAP to support 64bit
  out_dword(Base + HWIO_SATA_CAP_OFFS, capability | HWIO_SATA_CAP_S64A);
  capability = in_dword(Base + HWIO_SATA_CAP_OFFS);
  printf("SATA CAP[0x%x] 0x%x\r\n", (Base + HWIO_SATA_CAP_OFFS), capability);

  // set FB/FBU
  out_dword(Base + HWIO_SATA_P0FB_OFFS,
            (UINT32)((UINT64)fisRecvAddr & 0xffffffff));
  out_dword(Base + HWIO_SATA_P0FBU_OFFS,
            (UINT32)(((UINT64)fisRecvAddr >> 32) & 0xffffffff));
  // set CLB/CLBU
  out_dword(Base + HWIO_SATA_P0CLB_OFFS,
            (UINT32)((UINT64)cmdListAddr & 0xffffffff));
  out_dword(Base + HWIO_SATA_P0CLBU_OFFS,
            (UINT32)(((UINT64)cmdListAddr >> 32) & 0xffffffff));
  printf("SATA FB[0x%x] FBU[0x%x], CLB[0x%x] CLBU[0x%x]\r\n",
         in_dword(Base + HWIO_SATA_P0FB_OFFS),
         in_dword(Base + HWIO_SATA_P0FBU_OFFS),
         in_dword(Base + HWIO_SATA_P0CLB_OFFS),
         in_dword(Base + HWIO_SATA_P0CLBU_OFFS));

  // clear SERR
  val = in_dword(Base + HWIO_SATA_P0SERR_OFFS);
  out_dword(Base + HWIO_SATA_P0SERR_OFFS, val);

#ifdef CONFIG_HDTS_SATA
  // Interrupt init
  sata_interrupt_init(ControllerNum, gSataIntrMaskEn);
#endif

  // SATA_P0SCTL 0x300
  val = in_dword(Base + HWIO_SATA_P0SCTL_OFFS);
  out_dword(Base + HWIO_SATA_P0SCTL_OFFS, val | HWIO_SATA_P0SCTL_IPM_INIT);
  val = in_dword(Base + HWIO_SATA_P0SCTL_OFFS);
  printf("SATA P0SCTL[0x%x] 0x%x\r\n", (Base + HWIO_SATA_P0SCTL_OFFS), val);

  // AHCI_SATA_SATA_POWER_MGMT_CTR_OFFS 0x3f
  out_dword(Base + HWIO_SATA_POWER_MGMT_CTR_OFFS, 0x3f);

  // set CMD and start signature
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  if ((val & HWIO_SATA_P0CMD_CPD) != 0) {
    out_dword(Base + HWIO_SATA_P0CMD_OFFS, val | HWIO_SATA_P0CMD_POD);
  }
  if ((capability & HWIO_SATA_CAP_SSS) != 0) {
    out_dword(Base + HWIO_SATA_P0CMD_OFFS, val | HWIO_SATA_P0CMD_SUD);
  }
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  out_dword(Base + HWIO_SATA_P0CMD_OFFS, (val | HWIO_SATA_P0CMD_FRE));
  printf("SATA CMD[0x%x] 0x%x\r\n", (Base + HWIO_SATA_P0CMD_OFFS),
         in_dword(Base + HWIO_SATA_P0CMD_OFFS));

  // check SERR
  delay = 500;
  do {
    val = in_dword(Base + HWIO_SATA_P0SERR_OFFS);

    if (val == 0x4050002) {
      break;
    }

    udelay(10000);
    delay--;
  } while (delay > 0);

  if (delay == 0) {
    printf("[ERROR]SATA check SERR fail! [0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0SERR_OFFS), val);
    return;
  }
  printf("SATA SERR Check Pass [0x%x] 0x%x\r\n", (Base + HWIO_SATA_P0SERR_OFFS),
         val);

  // check SSTS
  delay = 500;
  do {
    val = in_dword(Base + HWIO_SATA_P0SSTS_OFFS);

    if ((val & 0x3) == 0x3) {
      break;
    }

    udelay(10000);
    delay--;
  } while (delay > 0);

  if (delay == 0) {
    printf("[ERROR]SATA check SSTS fail! [0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0SSTS_OFFS), val);
    return;
  }
  printf("SATA SSTS Check Pass [0x%x] 0x%x\r\n", (Base + HWIO_SATA_P0SSTS_OFFS),
         val);
  genspd = (val & 0xf0) >> 4;

  // check TFD
  delay = 500;
  do {
    val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);

    if ((val & BIT7) == 0) {
      break;
    }

    udelay(10000);
    delay--;
  } while (delay > 0);

  if (delay == 0) {
    printf("[ERROR]SATA check TFD fail! [0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0TFD_OFFS), val);
    return;
  }
  printf("SATA TFD Check Pass [0x%x] 0x%x\r\n", (Base + HWIO_SATA_P0TFD_OFFS),
         val);

  // check hard disk signature
  delay = 500;
  do {
    val = in_dword(Base + HWIO_SATA_P0SIG_OFFS);

    if (val == 0x0101) {
      break;
    }

    udelay(1000);
    delay--;
  } while (delay > 0);

  if (delay == 0) {
    printf("[ERROR]SATA find other device! SIG[0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0SIG_OFFS), val);
    return;
  }
  printf("SATA find hard disk! SIG[0x%x] 0x%x. Speed Gen%d\r\n",
         (Base + HWIO_SATA_P0SIG_OFFS), val, genspd);

#ifdef CONFIG_HDTS_SATA
  sata_identify(ControllerNum);

  sata_interrupt_check(ControllerNum, gSataIntrMaskEn);
  sata_interrupt_deinit(ControllerNum);
#endif
}

#ifdef CONFIG_HDTS_SATA
static int do_sata(int argc, char *argv[]) {
  UINT32 val = 0;
  UINT32 val2 = 0;
  UINT32 val3 = 0;
  UINT32 val4 = 0;

  // no param input
  if (argc == 1)
    return -1;

  if (strcmp(argv[1], "init") == 0) {
    if (argc > 3) {
      printf("[ERROR]sata init. Input illegal param cnt %d, expect 2 or 3\n",
             argc);
      return -1;
    }

    if (argc == 2) {
      // default GEN3
      sata_init(2);
      return 0;
    } else if (argc == 3) {
      val = strtoul(argv[2], NULL, 0);
      if ((val > 2) || (val < 0)) {
        printf("[ERROR]sata init. Input illegal speed param %d, expect 0~2\n",
               val);
        return -1;
      }
      sata_init(val);
      return 0;
    }
  } else if (strcmp(argv[1], "enum") == 0) {
    if (argc != 3) {
      printf("[ERROR]sata enum. Input illegal param cnt %d, expect 3\n", argc);
      return -1;
    }

    val = strtoul(argv[2], NULL, 0);
    if ((val > 7) || (val < 0)) {
      printf(
          "[ERROR]sata enum. Input illegal controller param %d, expect 0~7\n",
          val);
      return -1;
    }
    sata_enum(val);
    return 0;
  } else if (strcmp(argv[1], "xfer") == 0) {
    if (argc != 3) {
      printf("[ERROR]sata xfer. Input illegal param cnt %d, expect 3\n", argc);
      return -1;
    }

    val = strtoul(argv[2], NULL, 0);
    if ((val > 2) || (val < 0)) {
      printf("[ERROR]sata xfer. Input illegal xfer mode param %d, expect 0~2\n",
             val);
      return -1;
    }
    sata_xfer_mode(val);
    return 0;
  } else if (strcmp(argv[1], "bread") == 0) {
    if (argc != 4) {
      printf("[ERROR]sata bread. Input illegal param cnt %d, expect 4\n", argc);
      return -1;
    }

    val = strtoul(argv[2], NULL, 0);
    val2 = strtoul(argv[3], NULL, 0);
    printf("sata bread. Input start blk no %d, blk cnt %d\n", val, val2);
    printf("[Note] IMC support max blk cnt 256 for sys imem limit\n");
    sata_bread(val, val2);
    return 0;
  } else if (strcmp(argv[1], "bwrite") == 0) {
    if (argc != 5) {
      printf("[ERROR]sata bwrite. Input illegal param cnt %d, expect 5\n",
             argc);
      return -1;
    }

    val = strtoul(argv[2], NULL, 0);
    val2 = strtoul(argv[3], NULL, 0);
    val3 = strtoul(argv[4], NULL, 0);
    printf("sata bwrite. Input start blk no %d, blk cnt %d, val 0x%x\n", val,
           val2, val3);
    printf("[Note] IMC support max blk cnt 256 for sys imem limit\n");
    sata_bwrite(val, val2, (uint8_t)(val3 & 0xff));
    return 0;
  } else if (strcmp(argv[1], "multicmd") == 0) {
    if (argc != 4) {
      printf("[ERROR]sata multicmd. Input illegal param cnt %d, expect 4\n",
             argc);
      return -1;
    }

    val = strtoul(argv[2], NULL, 0);
    if ((val > 32) || (val <= 0)) {
      printf("[ERROR]sata multicmd. Input illegal multicmd cnt param %d, "
             "expect 1~32\n",
             val);
      return -1;
    }

    val2 = strtoul(argv[3], NULL, 0);
    sata_multi_cmd(val, (uint8_t)(val2 & 0xff));
    return 0;
  } else if (strcmp(argv[1], "reset") == 0) {
    if (argc != 3) {
      printf("[ERROR]sata reset. Input illegal param cnt %d, expect 3\n", argc);
      return -1;
    }

    val = strtoul(argv[2], NULL, 0);
    if ((val > 2) || (val < 0)) {
      printf(
          "[ERROR]sata reset. Input illegal reset mode param %d, expect 0~1\n",
          val);
      return -1;
    }
    sata_reset(val);
    return 0;
  } else if (strcmp(argv[1], "chkreg") == 0) {
    if (argc != 2) {
      printf("[ERROR]sata chkreg. Input illegal param cnt %d, expect 2\n",
             argc);
      return -1;
    }

    sata_reg_default_check();
    return 0;
  } else if (strcmp(argv[1], "intr") == 0) {
    if (argc > 3) {
      printf("[ERROR]sata intr. Input illegal param cnt %d, expect <= 3\n",
             argc);
      return -1;
    }

    if (argc == 2) {
      gSataIntrMaskEn = 0;
    } else {
      val = strtoul(argv[2], NULL, 0);
      gSataIntrMaskEn = val & SATA_INTR_ALL_IN;
    }
    printf("sata intr mask setting 0x%x\n", gSataIntrMaskEn);
    return 0;
  } else if (strcmp(argv[1], "lbnea") == 0) {
    if (argc != 5) {
      printf("[ERROR]sata lbnea. Input illegal param cnt %d, expect 5\n", argc);
      return -1;
    }

    val = strtoul(argv[2], NULL, 0);
    if ((val > 7) || (val < 0)) {
      printf(
          "[ERROR]sata lbnea. Input illegal controller param %d, expect 0~7\n",
          val);
      return -1;
    }

    val2 = strtoul(argv[3], NULL, 0);
    if ((val2 > 8) || (val2 < 0)) {
      printf("[ERROR]sata lbnea. Input illegal pattern param %d, expect 0~8\n",
             val2);
      return -1;
    }

    val3 = strtoul(argv[4], NULL, 0);
    if (val3 < 1) {
      val3 = 1;
      printf("[WARNING]sata lbnea. Input illegal time param %d, expect >=1\n",
             val3);
    }

    sata_loopback_nea(val, val2, val3);
    return 0;
  } else if (strcmp(argv[1], "lbphy") == 0) {
    if (argc != 6) {
      printf("[ERROR]sata lbphy. Input illegal param cnt %d, expect 6\n", argc);
      return -1;
    }

    val = strtoul(argv[2], NULL, 0);
    if ((val > 7) || (val < 0)) {
      printf(
          "[ERROR]sata lbphy. Input illegal controller param %d, expect 0~7\n",
          val);
      return -1;
    }

    val2 = strtoul(argv[3], NULL, 0);
    if (val2 > 1) {
      printf(
          "[ERROR]sata lbphy. Input illegal test mode param %d, expect 0~1\n",
          val2);
      return -1;
    }

    val3 = strtoul(argv[4], NULL, 0);
    if (val3 > 2) {
      printf("[ERROR]sata lbphy. Input illegal loopback speed param %d, expect "
             "0~2\n",
             val3);
      return -1;
    }

    val3 = strtoul(argv[5], NULL, 0);
    if (val4 > 2) {
      printf("[ERROR]sata lbphy. Input illegal loopback prbs param %d, expect "
             "0~2\n",
             val4);
      return -1;
    }

    sata_loopback_phy(val, val2, val3, val4);
    return 0;
  }

  return -1;
}

#ifdef CONFIG_CONSOLE_COMMAND
MK_CMD(sata, do_sata, "sata commands",
       " sata init [speed]\n"
       " sata enum [controller]\n"
       " sata xfer [mode]\n"
       " sata bread [start_block] [block_count]\n"
       " sata bwrite [start_block] [block_count] [value]\n"
       " sata multicmd [command_count] [value]\n"
       " sata reset [mode]\n"
       " sata chkreg\n"
       " sata intr [intrmask]\n"
       " sata lbnea [controller] [pattern] [times]\n"
       " sata lbphy [controller] [test_mode] [speed] [prbs]\n");
#endif
#endif

/*
//sata command usage comments
MK_CMD(sata, do_sata, "sata commands",
    " sata init [speed] \n"
    "           [speed]={0,1,2} for PHY speed GEN1/2/3 \n"
    "           Default is GEN3 for blank speed input \n"
        " sata enum [controller] \n"
    "           [controller]={0~7}, total 8 controllers \n"
        " sata xfer [mode] \n"
    "           [mode]={0,1,2} for DMA/PIO/FPDMA mode \n"
    "           Default is DMA mode for blank mode input \n"
    "           Note: sata multicmd is not actived under PIO mode \n"
        " sata bread [start_block] [block_count] \n"
    "           [start_block]={0, 1, 2...} (less than the real total block
counts of hard disk) \n"
    "           [block_count]={1, 2, 3...} (less than the real total remain
block counts after start_block of hard disk) \n"
    "           Note: Currently, the sata case run on IMC core and use system
memory(256KB), so the block_count should be less than 256(128KB in used). And if
the input block_count > 2, the multi prdt feature will be tested \n"
        " sata bwrite [start_block] [block_count] [value] \n"
    "           [start_block]={0, 1, 2...} (less than the real total block
counts of hard disk) \n"
    "           [block_count]={1, 2, 3...} (less than the real total remain
block counts after start_block of hard disk) \n"
    "           [value]={UINT8 char} (For example: 0x5A or 0xA5) \n"
    "           Note: Currently, the sata case run on IMC core and use system
memory(256KB), so the block_count should be less than 256(128KB in used). And if
the input block_count > 2, the multi prdt feature will be tested. \n"
        " sata multicmd [command_count] [value] \n"
    "           [command_conut]={1, 2, 3..., 32} (Support 1~32 commands, using
sata bwrite commands to set up the case and verify it using sata bread) \n"
    "           [value]={UINT8 char} (For example: 0x5A or 0xA5) \n"
    "           Note: Only support xfer mode = DMA mode & FPDMA mode \n"
        " sata reset [mode] \n"
    "           [value]={0, 1} (0: software reset; 1: port reset) \n"
    "           Note: Do reset after disk enum, and double check to do enum disk
again \n"
        " sata chkreg \n"
    "           Brief: sata check registers default value is expected.Check both
phy and controller registers in used.Include Phy qserver cmn/lane, pcs cmn/lane
registers, and Controller registers, for all lanes and controllers \n"
    "           Note: Do it after power on and before any sata operation \n"
        " sata intr [intrmask] \n"
    "           [intrmask] is the expected interrupt mask, please reference PxIE
register \n"
        " sata lbnea [controller] [pattern] [times] \n"
    "           [controller]={0~7}, total 8 controllers \n"
    "           [pattern]={0, 1, 2, 3, 4, 5, 6, 7, 8} \n"
    "           [times] is the testing time for seconds, expect >= 1 sec \n"
        " sata lbphy [controller] [test_mode] [speed] [prbs] \n"
    "           [controller]={0~7}, total 8 controllers \n"
    "           [test_mode]={0, 1}. 0: phy internal; 1: phy external. [NOTE]
Need to connect TX and RX \n"
    "           [speed]={0, 1, 2} for PHY speed GEN1/2/3 \n"
    "           [prbs]={0, 1, 2} for PRBS 7/9/10 \n"
);
*/


#ifdef CONFIG_PWRSOC_SATA
void sata_enable(void) {
  printf("Enable sata...\n");
  sata_clocks_set();
  sata_phy_set_and_check();
  sata_regs_init();
  printf("Sata init succeed\n");
}

static int do_sata(int argc, char *argv[]) {
  UINT32 val = 0;

  // no param input
  if (argc == 1)
    return -1;

  if (strcmp(argv[1], "enable") == 0) {
    sata_enable();
    return 0;
  } else {
    return -1;
  }
}

#ifdef CONFIG_CONSOLE_COMMAND
MK_CMD(sata, do_sata, "sata enable",
       " sata enable\n");
#endif
#endif
