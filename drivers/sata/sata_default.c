/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
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

// extern
extern UINTN Qserver_Com_Reg_Base[SATA_SP_NUMBER];
extern UINTN Qserver_Lane_Reg_Base[SATA_CONTROLLER_NUMBER];
extern UINTN Sata_Pcs_Lane_Reg_Base[SATA_CONTROLLER_NUMBER];
extern UINTN Sata_Phy_Cmn_Reg_Base[SATA_SP_NUMBER];
extern UINTN Sata_Reg_Base[SATA_CONTROLLER_NUMBER];

typedef struct SATA_REG_DEFAULT_ITEM {
  UINTN Offset;
  UINT32 Value;
} Sata_Reg_Default_Item;

static Sata_Reg_Default_Item QserverCommonRegSp0DefaultTable[] = {
    {HWIO_SP_QSERVER_COM_CMN_CONFIG_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_CLK_SELECT_OFFS, 0x00000008},
    {HWIO_SP_QSERVER_COM_SYSCLK_EN_SEL_OFFS, 0x00000018},
    {HWIO_SP_QSERVER_COM_SYSCLK_BUF_ENABLE_OFFS, 0x00000007},
    {HWIO_SP_QSERVER_COM_SYS_CLK_CTRL_OFFS, 0x00000006},
    {HWIO_SP_QSERVER_COM_BIAS_EN_CLKBUFLR_EN_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_CLK_ENABLE1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_HSCLK_SEL1_OFFS, 0x00000020},
    {HWIO_SP_QSERVER_COM_PLL_IVCO_OFFS, 0x0000000f},
    {HWIO_SP_QSERVER_COM_BG_CTRL_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_BGT_TRIM_OFFS, 0x0000000f},
    {HWIO_SP_QSERVER_COM_BGV_TRIM_OFFS, 0x00000020},
    {HWIO_SP_QSERVER_COM_VREGCLK_DIV1_OFFS, 0x0000002d},
    {HWIO_SP_QSERVER_COM_BG_TIMER_OFFS, 0x0000000a},
    {HWIO_SP_QSERVER_COM_RESETSM_CNTRL2_OFFS, 0x00000008},
    {HWIO_SP_QSERVER_COM_LOCK_CMP_EN_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_PLL_CCTRL_MODE0_OFFS, 0x00000001},
    {HWIO_SP_QSERVER_COM_PLL_RCTRL_MODE0_OFFS, 0x00000010},
    {HWIO_SP_QSERVER_COM_CP_CTRL_MODE0_OFFS, 0x0000001b},
    {HWIO_SP_QSERVER_COM_SSC_EN_CENTER_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_PER1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_PER2_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE2_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE3_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_DEC_START_MODE0_OFFS, 0x000000ff},
    {HWIO_SP_QSERVER_COM_DEC_START_MSB_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START1_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START2_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START3_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN0_MODE0_OFFS, 0x00000008},
    {HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN1_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_VCO_TUNE_MAP_OFFS, 0x00000004},
    {HWIO_SP_QSERVER_COM_LOCK_CMP1_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_LOCK_CMP2_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_LOCK_CMP3_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_CORECLK_DIV_OFFS, 0x0000000a},
    {HWIO_SP_QSERVER_COM_CORE_CLK_EN_OFFS, 0x00000070},
    {HWIO_SP_QSERVER_COM_SVS_MODE_CLK_SEL_OFFS, 0x00000000}};

static Sata_Reg_Default_Item QserverCommonRegSp1DefaultTable[] = {
    {HWIO_SP_QSERVER_COM_CMN_CONFIG_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SYSCLK_EN_SEL_OFFS, 0x00000018},
    {HWIO_SP_QSERVER_COM_SYSCLK_BUF_ENABLE_OFFS, 0x00000007},
    {HWIO_SP_QSERVER_COM_SYS_CLK_CTRL_OFFS, 0x00000006},
    {HWIO_SP_QSERVER_COM_BIAS_EN_CLKBUFLR_EN_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_CLK_ENABLE1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_HSCLK_SEL1_OFFS, 0x00000020},
    {HWIO_SP_QSERVER_COM_PLL_IVCO_OFFS, 0x0000000f},
    {HWIO_SP_QSERVER_COM_BG_CTRL_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_BGT_TRIM_OFFS, 0x0000000f},
    {HWIO_SP_QSERVER_COM_BGV_TRIM_OFFS, 0x00000020},
    {HWIO_SP_QSERVER_COM_VREGCLK_DIV1_OFFS, 0x0000002d},
    {HWIO_SP_QSERVER_COM_BG_TIMER_OFFS, 0x0000000a},
    {HWIO_SP_QSERVER_COM_RESETSM_CNTRL2_OFFS, 0x00000008},
    {HWIO_SP_QSERVER_COM_LOCK_CMP_EN_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_PLL_CCTRL_MODE0_OFFS, 0x00000001},
    {HWIO_SP_QSERVER_COM_PLL_RCTRL_MODE0_OFFS, 0x00000010},
    {HWIO_SP_QSERVER_COM_CP_CTRL_MODE0_OFFS, 0x0000001b},
    {HWIO_SP_QSERVER_COM_SSC_EN_CENTER_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_PER1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_PER2_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE2_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_SSC_STEP_SIZE3_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_DEC_START_MODE0_OFFS, 0x000000ff},
    {HWIO_SP_QSERVER_COM_DEC_START_MSB_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START1_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START2_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_DIV_FRAC_START3_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN0_MODE0_OFFS, 0x00000008},
    {HWIO_SP_QSERVER_COM_INTEGLOOP_GAIN1_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_VCO_TUNE_MAP_OFFS, 0x00000004},
    {HWIO_SP_QSERVER_COM_LOCK_CMP1_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_LOCK_CMP2_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_LOCK_CMP3_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_COM_CORECLK_DIV_OFFS, 0x0000000a},
    {HWIO_SP_QSERVER_COM_CORE_CLK_EN_OFFS, 0x00000070},
    {HWIO_SP_QSERVER_COM_SVS_MODE_CLK_SEL_OFFS, 0x00000000}};

static Sata_Reg_Default_Item QserverLaneRegDefaultTable[] = {
    {HWIO_SP_QSERVER_L_RX_EN_SIGNAL_OFFS, 0x000000cb},
    {HWIO_SP_QSERVER_L_PARALLEL_RATE_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_DLL_HIGHDATARATE_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_DLL_ENABLE_WAIT_OFFS, 0x00000008},
    {HWIO_SP_QSERVER_L_DCC_INIT_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_DCC_GAIN_OFFS, 0x00000002},
    {HWIO_SP_QSERVER_L_UCDR_FO_TO_SO_DELAY_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE0_OFFS, 0x0000000a},
    {HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE0_OFFS, 0x00000006},
    {HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE1_OFFS, 0x0000000a},
    {HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE1_OFFS, 0x00000006},
    {HWIO_SP_QSERVER_L_UCDR_FO_GAIN_MODE2_OFFS, 0x0000000a},
    {HWIO_SP_QSERVER_L_UCDR_SO_GAIN_MODE2_OFFS, 0x00000006},
    {HWIO_SP_QSERVER_L_UCDR_SO_CONFIG_OFFS, 0x00000035},
    {HWIO_SP_QSERVER_L_TX_BAND_MODE_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_RX_BAND_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_LANE_MODE_OFFS, 0x00000012},
    {HWIO_SP_QSERVER_L_RX_RCVR_PATH0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_RX_RCVR_PATH1_MODE2_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_DRVR_CTRL1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_TX_MARGINING_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_TX_PRE_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_TX_POST_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_CML_CTRL_MODE0_OFFS, 0x00000002},
    {HWIO_SP_QSERVER_L_CML_CTRL_MODE1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_CML_CTRL_MODE2_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_PREAMP_CTRL_MODE2_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_MIXER_CTRL_MODE0_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_MIXER_CTRL_MODE1_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_MIXER_CTRL_MODE2_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_PSM_RX_EN_CAL_OFFS, 0x00000005},
    {HWIO_SP_QSERVER_L_TS0_TIMER_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_RX_RESECODE_OFFSET_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_VGA_INITVAL_OFFS, 0x0000001c},
    {HWIO_SP_QSERVER_L_EQ_INITVAL_OFFS, 0x00000004},
    {HWIO_SP_QSERVER_L_RX_SAMPCAL_TSETTLE_OFFS, 0x00000080},
    {HWIO_SP_QSERVER_L_RX_SAMPCAL_ENDSAMP1_OFFS, 0x000000c0},
    {HWIO_SP_QSERVER_L_RX_SAMPCAL_MIDPOINT1_OFFS, 0x00000080},
    {HWIO_SP_QSERVER_L_SIGDET_ENABLES_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_SIGDET_CNTRL_OFFS, 0x00000040},
    {HWIO_SP_QSERVER_L_SIGDET_DEGLITCH_CNTRL_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_RSM_START_OFFS, 0x00000000},
    {HWIO_SP_QSERVER_L_DRVR_LOGIC_CLKDIV_OFFS, 0x00000014},
    {HWIO_SP_QSERVER_L_DRVR_CTRL0_OFFS, 0x00000010},
    {HWIO_SP_QSERVER_L_DRVR_TAP_EN_OFFS, 0x00000001},
    {HWIO_SP_QSERVER_L_RX_MISC_CNTRL0_OFFS, 0x00000000}};

static Sata_Reg_Default_Item SataPcsLaneRegDefaultTable[] = {
    {HWIO_SP_SATA_PHY_L_SATA_PHY_ALIGNP_OFFS, 0x0000004f},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_CTRL0_OFFS, 0x00000028},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_POW_DWN_CTRL0_OFFS, 0x00000000},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_OFFS, 0x00000001},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_OOB_DET1_OFFS, 0x000000c1},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_CDR_CTRL1_OFFS, 0x00000042},
    {HWIO_SP_SATA_PHY_L_SATA_PHY_CODE_ERR_CFG_OFFS, 0x0000000c}};

static Sata_Reg_Default_Item SataPhyCmnRegDefaultTable[] = {
    {HWIO_SP_SATA_PHY_CMN_SATA_PHY_SERDES_START_OFFS, 0x00000000},
    {HWIO_SP_SATA_PHY_CMN_SATA_PHY_RESET_CTRL_OFFS, 0x00000001}};

static Sata_Reg_Default_Item SataControllerRegDefaultTable[] = {
    {HWIO_SATA_CAP_OFFS, 0xe736ff80},
    {HWIO_SATA_GHC_OFFS, 0x80000000},
    {HWIO_SATA_IS_OFFS, 0x00000000},
    {HWIO_SATA_PI_OFFS, 0x00000000},
    {HWIO_SATA_VS_OFFS, 0x00010301},
    {HWIO_SATA_CCC_CTL_OFFS, 0x00010108},
    {HWIO_SATA_CCC_PORTS_OFFS, 0x00000000},
    {HWIO_SATA_CAP2_OFFS, 0x0000001c},
    {HWIO_SATA_BISTAFR_OFFS, 0x00000000},
    {HWIO_SATA_BISTCR_OFFS, 0x00000700},
    {HWIO_SATA_BISTFCTR_OFFS, 0x00000000},
    {HWIO_SATA_BISTSR_OFFS, 0x00000000},
    {HWIO_SATA_BISTDECR_OFFS, 0x00000000},
    {HWIO_SATA_DIAGNR_OFFS, 0x0003e000},
    {HWIO_SATA_DIAGNR1_OFFS, 0x00000000},
    {HWIO_SATA_OOBR_OFFS, 0x070e182b},
    {HWIO_GPCR_OFFS, 0x000033aa},
    {HWIO_GPSR_OFFS, 0x10040000},
    {HWIO_SATA_TIMER1MS_OFFS, 0x00030d40},
    {HWIO_SATA_GPARAM1R_OFFS, 0x5c100449},
    {HWIO_SATA_GPARAM2R_OFFS, 0x00081e64},
    {HWIO_SATA_PPARAMR_OFFS, 0x00000a88},
    {HWIO_SATA_TESTR_OFFS, 0x00000000},
    {HWIO_SATA_VERSIONR_OFFS, 0x3431302a},
    {HWIO_SATA_IDR_OFFS, 0x0000008c},
    {HWIO_SATA_P0CLB_OFFS, 0x00000000},
    {HWIO_SATA_P0CLBU_OFFS, 0x00000000},
    {HWIO_SATA_P0FB_OFFS, 0x00000000},
    {HWIO_SATA_P0FBU_OFFS, 0x00000000},
    {HWIO_SATA_P0IS_OFFS, 0x00000000},
    {HWIO_SATA_P0IE_OFFS, 0x00000000},
    {HWIO_SATA_P0CMD_OFFS, 0x00000004},
    {HWIO_SATA_P0TFD_OFFS, 0x0000007f},
    {HWIO_SATA_P0SIG_OFFS, 0xffffffff},
    {HWIO_SATA_P0SSTS_OFFS, 0x00000000},
    {HWIO_SATA_P0SCTL_OFFS, 0x00000000},
    {HWIO_SATA_P0SERR_OFFS, 0x00000000},
    {HWIO_SATA_P0SACT_OFFS, 0x00000000},
    {HWIO_SATA_P0CI_OFFS, 0x00000000},
    {HWIO_SATA_P0SNTF_OFFS, 0x00000000}};

static BOOLEAN g_doSataInitCbfAndClk = TRUE;

BOOLEAN sata_qserver_cmn_reg_default_check(void) {
  UINTN Base;
  UINTN TotalItems, i;
  UINT8 val = 0;
  UINT32 err = 0;

  // check sp0
  Base = Qserver_Com_Reg_Base[0];
  TotalItems =
      sizeof(QserverCommonRegSp0DefaultTable) / sizeof(Sata_Reg_Default_Item);
  for (i = 0; i < TotalItems; i++) {
    val = (UINT8)(in_dword(Base + QserverCommonRegSp0DefaultTable[i].Offset) &
                  0xff);
    if (val != (UINT8)(QserverCommonRegSp0DefaultTable[i].Value & 0xff)) {
      printf("[ERROR]Qserver cmn sp0 chk, offs[%d, 0x%x]=0x%x, expect=0x%x\r\n",
             i, QserverCommonRegSp0DefaultTable[i].Offset, val,
             (UINT8)(QserverCommonRegSp0DefaultTable[i].Value & 0xff));
      err++;
    }
  }

  // check sp1
  Base = Qserver_Com_Reg_Base[1];
  TotalItems =
      sizeof(QserverCommonRegSp1DefaultTable) / sizeof(Sata_Reg_Default_Item);
  for (i = 0; i < TotalItems; i++) {
    val = (UINT8)(in_dword(Base + QserverCommonRegSp1DefaultTable[i].Offset) &
                  0xff);
    if (val != (UINT8)(QserverCommonRegSp1DefaultTable[i].Value & 0xff)) {
      printf("[ERROR]Qserver cmn sp1 chk, offs[%d, 0x%x]=0x%x, expect=0x%x\r\n",
             i, QserverCommonRegSp1DefaultTable[i].Offset, val,
             (UINT8)(QserverCommonRegSp1DefaultTable[i].Value & 0xff));
      err++;
    }
  }

  if (err)
    return FALSE;

  return TRUE;
}

BOOLEAN sata_qserver_lane_reg_default_check(void) {
  UINTN Base;
  UINTN TotalItems, i, j;
  UINT8 val = 0;
  UINT32 err = 0;

  // check lane 0~7
  for (j = 0; j < SATA_CONTROLLER_NUMBER; j++) {
    Base = Qserver_Lane_Reg_Base[j];
    TotalItems =
        sizeof(QserverLaneRegDefaultTable) / sizeof(Sata_Reg_Default_Item);
    for (i = 0; i < TotalItems; i++) {
      val =
          (UINT8)(in_dword(Base + QserverLaneRegDefaultTable[i].Offset) & 0xff);
      if (val != (UINT8)(QserverLaneRegDefaultTable[i].Value & 0xff)) {
        printf(
            "[ERROR]Qserver lane %d chk, offs[%d, 0x%x]=0x%x, expect=0x%x\r\n",
            j, i, QserverLaneRegDefaultTable[i].Offset, val,
            (UINT8)(QserverLaneRegDefaultTable[i].Value & 0xff));
        err++;
      }
    }
  }

  if (err)
    return FALSE;

  return TRUE;
}

BOOLEAN sata_pcs_lane_reg_default_check(void) {
  UINTN Base;
  UINTN TotalItems, i, j;
  UINT8 val = 0;
  UINT32 err = 0;

  // check lane 0~7
  for (j = 0; j < SATA_CONTROLLER_NUMBER; j++) {
    Base = Sata_Pcs_Lane_Reg_Base[j];
    TotalItems =
        sizeof(SataPcsLaneRegDefaultTable) / sizeof(Sata_Reg_Default_Item);
    for (i = 0; i < TotalItems; i++) {
      val =
          (UINT8)(in_dword(Base + SataPcsLaneRegDefaultTable[i].Offset) & 0xff);
      if (val != (UINT8)(SataPcsLaneRegDefaultTable[i].Value & 0xff)) {
        printf("[ERROR]Pcs lane %d chk, offs[%d, 0x%x]=0x%x, expect=0x%x\r\n",
               j, i, SataPcsLaneRegDefaultTable[i].Offset, val,
               (UINT8)(SataPcsLaneRegDefaultTable[i].Value & 0xff));
        err++;
      }
    }
  }

  if (err)
    return FALSE;

  return TRUE;
}

BOOLEAN sata_pcs_cmn_reg_default_check(void) {
  UINTN Base;
  UINTN TotalItems, i;
  UINT8 val = 0;
  UINT32 err = 0;

  // check sp0
  Base = Sata_Phy_Cmn_Reg_Base[0];
  TotalItems =
      sizeof(SataPhyCmnRegDefaultTable) / sizeof(Sata_Reg_Default_Item);
  for (i = 0; i < TotalItems; i++) {
    val = (UINT8)(in_dword(Base + SataPhyCmnRegDefaultTable[i].Offset) & 0xff);
    if (val != (UINT8)(SataPhyCmnRegDefaultTable[i].Value & 0xff)) {
      printf("[ERROR]Pcs cmn sp0 chk, offs[%d, 0x%x]=0x%x, expect=0x%x\r\n", i,
             SataPhyCmnRegDefaultTable[i].Offset, val,
             (UINT8)(SataPhyCmnRegDefaultTable[i].Value & 0xff));
      err++;
    }
  }

  // check sp1
  Base = Sata_Phy_Cmn_Reg_Base[1];
  TotalItems =
      sizeof(SataPhyCmnRegDefaultTable) / sizeof(Sata_Reg_Default_Item);
  for (i = 0; i < TotalItems; i++) {
    val = (UINT8)(in_dword(Base + SataPhyCmnRegDefaultTable[i].Offset) & 0xff);
    if (val != (UINT8)(SataPhyCmnRegDefaultTable[i].Value & 0xff)) {
      printf("[ERROR]Pcs cmn sp1 chk, offs[%d, 0x%x]=0x%x, expect=0x%x\r\n", i,
             SataPhyCmnRegDefaultTable[i].Offset, val,
             (UINT8)(SataPhyCmnRegDefaultTable[i].Value & 0xff));
      err++;
    }
  }

  if (err)
    return FALSE;

  return TRUE;
}

BOOLEAN sata_controller_reg_default_check(void) {
  UINTN Base;
  UINTN TotalItems, i, j;
  UINT32 val = 0;
  UINT32 err = 0;

  // check controller 0~7
  for (j = 0; j < SATA_CONTROLLER_NUMBER; j++) {
    Base = Sata_Reg_Base[j];
    TotalItems =
        sizeof(SataControllerRegDefaultTable) / sizeof(Sata_Reg_Default_Item);
    for (i = 0; i < TotalItems; i++) {
      val = in_dword(Base + SataControllerRegDefaultTable[i].Offset);
      if (val != SataControllerRegDefaultTable[i].Value) {
        printf("[ERROR]Controller %d chk, offs[%d, 0x%x]=0x%x, expect=0x%x\r\n",
               j, i, SataControllerRegDefaultTable[i].Offset, val,
               SataControllerRegDefaultTable[i].Value);
        err++;
      }
    }
  }

  if (err)
    return FALSE;

  return TRUE;
}

void sata_reg_default_check(void) {
  UINT32 err = 0;

  printf("Sata reg default value check...\r\n");
  printf("Check Phy and Controller reg\r\n");

  if (g_doSataInitCbfAndClk) {
    cbf_init();
    sata_clocks_set();
    g_doSataInitCbfAndClk = FALSE;
    printf("[Note]Before check reg, do cbf and clk init. Only once!\r\n");
  }

  if (!sata_qserver_cmn_reg_default_check()) {
    printf("[ERROR]Qserver cmn reg check fail.\r\n");
    err++;
  }

  if (!sata_qserver_lane_reg_default_check()) {
    printf("[ERROR]Qserver lane reg check fail.\r\n");
    err++;
  }

  if (!sata_pcs_lane_reg_default_check()) {
    printf("[ERROR]Pcs lane reg check fail.\r\n");
    err++;
  }

  if (!sata_pcs_cmn_reg_default_check()) {
    printf("[ERROR]Pcs cmn reg check fail.\r\n");
    err++;
  }

  if (!sata_controller_reg_default_check()) {
    printf("[ERROR]Controller reg check fail.\r\n");
    err++;
  }

  if (err)
    printf("[FAIL] Sata reg default value check fail!\r\n");
  else
    printf("[PASS] Sata reg default value check pass!\r\n");
}
