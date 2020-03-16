/**---------------------------------------------------------------------------
 * @file     emac_phy_sgmii.c
 *
 * @brief    Routines for ephy reset, setup and cleanup
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include <stdio.h>
#include <Uefi.h>
#include <string.h>
 #include <Library/BaseLib.h>

#include "boot_comdef.h"
#include "asm/mach/hal/msmhwiobase.h"
#include "emac_hwio_mapping.h"
#include "emac_framework.h"
#include "emac_phy_sgmii.h"

#ifdef EMAC0_FOR_UEFI
//#include <Library/EMACTargetLib.h>
#endif

BOOLEAN IsPhyInitialized[2] = {FALSE, FALSE}; // Ensure that PHY only gets initialized once


/**
  Set Emac SGMII Reference clocks

  @retval EFI_SUCCESS           The operation was successfully completed.

  @retval EFI_UNSUPPORTED       Target does not support EMAC

**/
VOID SetEmacSgmiiRefClks
(
 VOID
){
  /* Sysclk/Refclk Settings (selection and termination) */
  HWIO_OUT(QSERVER_COM_SYSCLK_EN_SEL, 0x08);
  HWIO_OUT(QSERVER_COM_SYS_CLK_CTRL, 0x06);
  HWIO_OUT(QSERVER_COM_BIAS_EN_CLKBUFLR_EN, 0x0C);
  HWIO_OUT(QSERVER_COM_CLK_ENABLE1, 0x00);
  HWIO_OUT(QSERVER_COM_HSCLK_SEL1, 0x08);
  HWIO_OUT(QSERVER_COM_PLL_IVCO, 0xf0);
  HWIO_OUT(QSERVER_COM_BGV_TRIM, 0x20);
  HWIO_OUT(QSERVER_COM_BGT_TRIM, 0x0f);
  HWIO_OUT(QSERVER_COM_VREGCLK_DIV1, 0x01);
  HWIO_OUT(QSERVER_COM_VREGCLK_DIV2, 0x05);
  HWIO_OUT(QSERVER_COM_CORE_CLK_EN, 0x00);
}


static VOID SetEmacSgmiiTxRxRegisters
(
 uint8 phyIndex
)
{
  /* TX/RX Settings */
  if(phyIndex == 0){
      HWIO_OUT(QSERVER_L0_RX_EN_SIGNAL, 0xC0);
      HWIO_OUT(QSERVER_L0_DRVR_CTRL0, 0x11);
      HWIO_OUT(QSERVER_L0_DRVR_TAP_EN, 0x01);
      HWIO_OUT(QSERVER_L0_TX_MARGINING, 0x59);
      HWIO_OUT(QSERVER_L0_TX_PRE, 0x40);
      HWIO_OUT(QSERVER_L0_TX_POST, 0x40);
      HWIO_OUT(QSERVER_L0_CML_CTRL_MODE0, 0x09);
      HWIO_OUT(QSERVER_L0_MIXER_CTRL_MODE0, 0x31);
      HWIO_OUT(QSERVER_L0_VGA_INITVAL, 0x1F);
      HWIO_OUT(QSERVER_L0_SIGDET_ENABLES, 0x21);
      HWIO_OUT(QSERVER_L0_SIGDET_CNTRL, 0x80);
      HWIO_OUT(QSERVER_L0_SIGDET_DEGLITCH_CNTRL, 0x08);
      HWIO_OUT(QSERVER_L0_RX_MISC_CNTRL0, 0x80);
      HWIO_OUT(QSERVER_L0_DRVR_LOGIC_CLKDIV, 0x14);
      HWIO_OUT(QSERVER_L0_PARALLEL_RATE, 0x01);
      HWIO_OUT(QSERVER_L0_TX_BAND_MODE, 0x01);
      HWIO_OUT(QSERVER_L0_RX_BAND, 0x02);
      HWIO_OUT(QSERVER_L0_LANE_MODE, 0x1A);
      HWIO_OUT(QSERVER_L0_RX_RCVR_PATH1_MODE0, 0x5C);
  }
  else{
      HWIO_OUT(QSERVER_L1_RX_EN_SIGNAL, 0xC0);
      HWIO_OUT(QSERVER_L1_DRVR_CTRL0, 0x11);
      HWIO_OUT(QSERVER_L1_DRVR_TAP_EN, 0x01);
      HWIO_OUT(QSERVER_L1_TX_MARGINING, 0x59);
      HWIO_OUT(QSERVER_L1_TX_PRE, 0x40);
      HWIO_OUT(QSERVER_L1_TX_POST, 0x40);
      HWIO_OUT(QSERVER_L1_CML_CTRL_MODE0, 0x09);
      HWIO_OUT(QSERVER_L1_MIXER_CTRL_MODE0, 0x31);
      HWIO_OUT(QSERVER_L1_VGA_INITVAL, 0x1F);
      HWIO_OUT(QSERVER_L1_SIGDET_ENABLES, 0x21);
      HWIO_OUT(QSERVER_L1_SIGDET_CNTRL, 0x80);
      HWIO_OUT(QSERVER_L1_SIGDET_DEGLITCH_CNTRL, 0x08);
      HWIO_OUT(QSERVER_L1_RX_MISC_CNTRL0, 0x80);
      HWIO_OUT(QSERVER_L1_DRVR_LOGIC_CLKDIV, 0x14);
      HWIO_OUT(QSERVER_L1_PARALLEL_RATE, 0x01);
      HWIO_OUT(QSERVER_L1_TX_BAND_MODE, 0x01);
      HWIO_OUT(QSERVER_L1_RX_BAND, 0x02);
      HWIO_OUT(QSERVER_L1_LANE_MODE, 0x1A);
      HWIO_OUT(QSERVER_L1_RX_RCVR_PATH1_MODE0, 0x5C);
  }
}


/**
 * @brief       Check SGMII PHY status
 *
 * @return      TRUE if initialized and operational, else failed.
 */

boolean Emac_PhyCheckStatusSgmii
(
  uint8 phyIndex
)
{
  uint32 value = 0;
  EMAC_PRINT_0("SGMII PHY check status:\r\n");

  /* Report auto-neg and speed settings */
  if(phyIndex == 0)
    value = HWIO_IN(PHY_REG_PRE(SGMII_PHY_AUTONEG_CFG2));
  else
    value = HWIO_IN(PHY_REG_PRE1(SGMII_PHY_AUTONEG_CFG2));

  if (0x0 == value) {
    EMAC_PRINT_0("    SGMII Auto-Neg off, ");

    if(phyIndex == 0)
        value = HWIO_IN(PHY_REG_PRE(SGMII_PHY_SPEED_CFG1));
    else
        value = HWIO_IN(PHY_REG_PRE1(SGMII_PHY_SPEED_CFG1));
    if (0x12 == value) {
      EMAC_PRINT_0("speed 1000Mbps\r\n");
    }
    else if (0x11 == value) {
      EMAC_PRINT_0("speed 100Mbps\r\n");
    }
    else if (0x10 == value) {
      EMAC_PRINT_0("speed 10Mbps\r\n");
    }
    else {
      EMAC_PRINT_0("speed UNKNOWN\r\n");
      return FALSE;   /* Failure */
    }
  }
  else {
    EMAC_PRINT_0("    SGMII Auto-Neg ON\r\n");
  }
  Emac_SleepMS(10);

  /* Check if CDR locked */
  if(phyIndex == 0)
    value = HWIO_INF(PHY_REG_PRE(SGMII_PHY_RX_CHK_STATUS), CDR_ALIGN_DET);
  else
    value = HWIO_INF(PHY_REG_PRE1(SGMII_PHY_RX_CHK_STATUS), CDR_ALIGN_DET);

  if (0x1 != value) {
    EMAC_PRINT_1("    SGMII CDR NOT locked 0x%x\r\n", value);
    return FALSE;   // Failure
  }

  EMAC_PRINT_1("    SGMII CDR locked 0x%x\r\n", value);

  /* Check for mis-aligned status */
  EMAC_PRINT_0("    SGMII wait to check mis-align...\r\n");
  Emac_SleepMS(10);
  if(phyIndex == 0)
    value = HWIO_INF(PHY_REG_PRE(SGMII_PHY_RX_CHK_STATUS), MIS_ALIGN_STATUS);
  else
    value = HWIO_INF(PHY_REG_PRE1(SGMII_PHY_RX_CHK_STATUS), MIS_ALIGN_STATUS);
  if (0x1 == value) {
    EMAC_PRINT_0("    SGMII MIS-ALIGN detected, clear and retry...\r\n");

    /* Clearing the status */
    if(phyIndex == 0)
        HWIO_OUTF(PHY_REG_PRE(SGMII_PHY_ALIGNP), MIS_ALIGN_STATUS_CLEAR, 0x1);
    else
        HWIO_OUTF(PHY_REG_PRE1(SGMII_PHY_ALIGNP), MIS_ALIGN_STATUS_CLEAR, 0x1);
    Emac_SleepMS(10);

    /*Zero the clear bit*/
    if(phyIndex == 0)
        HWIO_OUTF(PHY_REG_PRE(SGMII_PHY_ALIGNP), MIS_ALIGN_STATUS_CLEAR, 0x0);
    else
        HWIO_OUTF(PHY_REG_PRE1(SGMII_PHY_ALIGNP), MIS_ALIGN_STATUS_CLEAR, 0x0);
    Emac_SleepMS(10);

    if(phyIndex == 0)
        value = HWIO_INF(PHY_REG_PRE(SGMII_PHY_RX_CHK_STATUS), MIS_ALIGN_STATUS);
    else
        value = HWIO_INF(PHY_REG_PRE1(SGMII_PHY_RX_CHK_STATUS), MIS_ALIGN_STATUS);
    if (0x1 == value) {
      EMAC_PRINT_0("    SGMII MIS-ALIGN detected 2nd time, failed\r\n");
      if(phyIndex == 0)
        value = HWIO_IN(PHY_REG_PRE(SGMII_PHY_INTERRUPT_STATUS));
      else
        value = HWIO_IN(PHY_REG_PRE1(SGMII_PHY_INTERRUPT_STATUS));
      EMAC_PRINT_1("    SGMII INT status: 0x%08X\r\n", value);
      return FALSE;
    }
  }

  if(phyIndex == 0)
    value = HWIO_IN(PHY_REG_PRE(SGMII_PHY_INTERRUPT_STATUS));
  else
    value = HWIO_IN(PHY_REG_PRE1(SGMII_PHY_INTERRUPT_STATUS));
  EMAC_PRINT_1("    SGMII INT status: 0x%08X\r\n", value);
  EMAC_PRINT_0("    SGMII status ok.\r\n");

  return TRUE;
}

/**
 * @brief       Reset Phy HW in SGMII mode
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyHwResetSgmii
(
 IN uint8 phyIndex
)
{
  int32 timeOut;

  EMAC_PRINT_1("Emac_PhyHwResetSgmii phyIndex %d\r\n", phyIndex);
  if(phyIndex == 0){
      /* Reset SGMII */
      HWIO_OUT(PHY_REG_PRE(SGMII_PHY_RESET_CTRL), 0x01);
      Emac_SleepMS(1);
      /* Get it out of reset */
      HWIO_OUT(PHY_REG_PRE(SGMII_PHY_RESET_CTRL), 0x00);
  }
  else{
      /* Reset SGMII */
      HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_RESET_CTRL), 0x01);
      Emac_SleepMS(1);
      /* Get it out of reset */
      HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_RESET_CTRL), 0x00);
  }

  /* Wait for c_ready assertion */
  timeOut = EMAC_C_READY_SIGNAL_TIMEOUT / 20;
  do{
    Emac_SleepMS(20);

    if(phyIndex == 0){
        if (((HWIO_IN(PHY_REG_PRE(SGMII_PHY_LANE_STATUS))) & (1 << 1)) != 0)
            break;
    }
    else{
        if (((HWIO_IN(PHY_REG_PRE1(SGMII_PHY_LANE_STATUS))) & (1 << 1)) != 0)
            break;
    }
  } while (0 < --timeOut);

  if(timeOut == 0) {
    EMAC_PRINT_0("HXT: SGMII PHY reset timeout\r\n");  
  }

  return TRUE;
}

/**
 * @brief       Initialize Phy HW in SGMII mode
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyHwInitSgmii
(
 IN uint8 phyIndex,
 IN const EMAC_PHY_CFG *cfg
)
{
  uint32 timeOut;

 // if( !IsPhyInitialized[phyIndex] ) {
 if(1){
      /* Make sure SGMII PHY is not in reset */
      EMAC_PRINT_1("reset sgmii phy%d\r\n", phyIndex);
      if(phyIndex == 0){
          HWIO_OUTF(EMAC_REG_PRE(EMAC_WRAPPER_CSR2), PHY_RESET, 0x0);
          HWIO_OUT(SGMII_PHY_CMN_SGMII_PHY_RESET_CTRL, 0x00);
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_RESET_CTRL), 0x00);
      }
      else{
          HWIO_OUTF(EMAC_REG_PRE1(EMAC_WRAPPER_CSR2), PHY_RESET, 0x0);
          //HWIO_OUT(SGMII_PHY_CMN_SGMII_PHY_RESET_CTRL, 0x00);
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_RESET_CTRL), 0x00);
      }

      /* AN is enabled by default. Disabling AN should be done before
       * auto-negotiation starts, so best time to disable AN is even before
       * initialization sequence.
       * Additionally, auto-negotiation has to be off for all loopbacks
       */
      if ((TRUE != cfg->isAutoNeg) ||
          (EMAC_LB_PHY_DIG    == cfg->modeLoopback) ||
          (EMAC_LB_PHY_SERDES == cfg->modeLoopback)) {
        if(phyIndex == 0){
            HWIO_OUT(PHY_REG_PRE(SGMII_PHY_AUTONEG_CFG2), 0x0); /* Disable Auto-neg */
            HWIO_OUTF(PHY_REG_PRE(SGMII_PHY_AUTONEG_CFG2), ALIGNP_IDLE, 0x1);
        }
        else{
            HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_AUTONEG_CFG2), 0x0); /* Disable Auto-neg */
            HWIO_OUTF(PHY_REG_PRE1(SGMII_PHY_AUTONEG_CFG2), ALIGNP_IDLE, 0x1);
        }

        switch (cfg->speed) {
          case 1000:
            if(phyIndex == 0){
                if((EMAC_LB_PHY_DIG == cfg->modeLoopback) ||
                    (EMAC_LB_PHY_SERDES == cfg->modeLoopback))
                    HWIO_OUT(PHY_REG_PRE(SGMII_PHY_SPEED_CFG1), 0x32); /* 1000Mbps */
                else
                    HWIO_OUT(PHY_REG_PRE(SGMII_PHY_SPEED_CFG1), 0x12); /* 1000Mbps */
            }
            else {
                if((EMAC_LB_PHY_DIG == cfg->modeLoopback) ||
                    (EMAC_LB_PHY_SERDES == cfg->modeLoopback))
                    HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_SPEED_CFG1), 0x32); /* 1000Mbps */
                else
                    HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_SPEED_CFG1), 0x12); /* 1000Mbps */
            }
            break;
          case 100:
            if(phyIndex == 0)
                HWIO_OUT(PHY_REG_PRE(SGMII_PHY_SPEED_CFG1), 0x11); /* 100Mbps */
            else
                HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_SPEED_CFG1), 0x11); /* 100Mbps */
            break;
          case 10:
            if(phyIndex == 0)
                HWIO_OUT(PHY_REG_PRE(SGMII_PHY_SPEED_CFG1), 0x10); /* 10Mbps */
            else
                HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_SPEED_CFG1), 0x10); /* 10Mbps */
            break;
          default:
            EMAC_PRINT_1("Invalid speed specified (%u) Failed\n", cfg->speed);
            return FALSE;
        }
      }

      /* PCS Programing */
      HWIO_OUT(SGMII_PHY_CMN_SGMII_PHY_CMN_CTRL, 0x04);
      if(phyIndex == 0){
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_POW_DWN_CTRL0), 0x01);
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_CDR_CTRL0), 0x0F);
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_TX_PWR_CTRL), 0x00);
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_LANE_CTRL1), 0x40);
      }
      else{
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_POW_DWN_CTRL0), 0x01);
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_CDR_CTRL0), 0x0F);
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_TX_PWR_CTRL), 0x00);
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_LANE_CTRL1), 0x40);
      }

      /* Sysclk/Refclk Settings (selection and termination) */
      HWIO_OUT(QSERVER_COM_SYSCLK_EN_SEL, 0x08);
      HWIO_OUT(QSERVER_COM_SYS_CLK_CTRL, 0x06);
      HWIO_OUT(QSERVER_COM_BIAS_EN_CLKBUFLR_EN, 0x0C);
      HWIO_OUT(QSERVER_COM_CLK_ENABLE1, 0x00);
      HWIO_OUT(QSERVER_COM_HSCLK_SEL1, 0x08);
      HWIO_OUT(QSERVER_COM_PLL_IVCO, 0xf0);
      HWIO_OUT(QSERVER_COM_BGV_TRIM, 0x20);
      HWIO_OUT(QSERVER_COM_BGT_TRIM, 0x0f);
      HWIO_OUT(QSERVER_COM_VREGCLK_DIV1, 0x01);
      HWIO_OUT(QSERVER_COM_VREGCLK_DIV2, 0x05);
      HWIO_OUT(QSERVER_COM_CORE_CLK_EN, 0x00);

      /*PLL Settings */
      HWIO_OUT(QSERVER_COM_PLL_CCTRL_MODE0, 0x34);
      HWIO_OUT(QSERVER_COM_PLL_RCTRL_MODE0, 0x16);
      HWIO_OUT(QSERVER_COM_CP_CTRL_MODE0, 0x08);
      HWIO_OUT(QSERVER_COM_DEC_START_MODE0, 0x7D);
      HWIO_OUT(QSERVER_COM_DIV_FRAC_START1_MODE0, 0x00);
      HWIO_OUT(QSERVER_COM_DIV_FRAC_START2_MODE0, 0x00);
      HWIO_OUT(QSERVER_COM_DIV_FRAC_START3_MODE0, 0x00);
      HWIO_OUT(QSERVER_COM_LOCK_CMP1_MODE0, 0x00);
      HWIO_OUT(QSERVER_COM_LOCK_CMP2_MODE0, 0x32);
      HWIO_OUT(QSERVER_COM_LOCK_CMP3_MODE0, 0x00);
      HWIO_OUT(QSERVER_COM_INTEGLOOP_GAIN0_MODE0, 0x3F);
      HWIO_OUT(QSERVER_COM_INTEGLOOP_GAIN1_MODE0, 0x00);
      HWIO_OUT(QSERVER_COM_VCO_TUNE_MAP, 0x00);
      HWIO_OUT(QSERVER_COM_SVS_MODE_CLK_SEL, 0x01);
      HWIO_OUT(QSERVER_COM_LOCK_CMP_EN, 0x00);
      HWIO_OUT(QSERVER_COM_RESETSM_CNTRL2, 0x08);
      HWIO_OUT(QSERVER_COM_CORECLK_DIV, 0x05);

      /* CDR Settings */
      if(phyIndex == 0){
          HWIO_OUT(QSERVER_REG_PRE(UCDR_FO_GAIN_MODE0), 0x8A);
          HWIO_OUT(QSERVER_REG_PRE(UCDR_SO_GAIN_MODE0), 0x00);
          HWIO_OUT(QSERVER_REG_PRE(UCDR_SO_CONFIG), 0x4C);
      }
      else{
          HWIO_OUT(QSERVER_REG_PRE1(UCDR_FO_GAIN_MODE0), 0x8A);
          HWIO_OUT(QSERVER_REG_PRE1(UCDR_SO_GAIN_MODE0), 0x00);
          HWIO_OUT(QSERVER_REG_PRE1(UCDR_SO_CONFIG), 0x4C);
      }

      /* TX/RX Settings */
      SetEmacSgmiiTxRxRegisters(phyIndex);

      if(phyIndex == 0){
          HWIO_OUT(QSERVER_REG_PRE(RSM_CONFIG), 0x03);
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_RESET_CTRL), 0x00);
          HWIO_OUT(QSERVER_REG_PRE(RSM_START), 0x01);
      }
      else{
          HWIO_OUT(QSERVER_REG_PRE1(RSM_CONFIG), 0x03);
          HWIO_OUT(SGMII_PHY_CMN_SGMII_PHY_RESET_CTRL, 0x00);
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_RESET_CTRL), 0x00);
          HWIO_OUT(QSERVER_REG_PRE1(RSM_START), 0x01);
      }

      /* Wait for c_ready assertion */
      timeOut = EMAC_C_READY_SIGNAL_TIMEOUT;
      do{
        if(phyIndex == 0){
            if (((HWIO_IN(PHY_REG_PRE(SGMII_PHY_LANE_STATUS))) & (1 << 1)) != 0) {
              break;
            }
        }
        else{
            if (((HWIO_IN(PHY_REG_PRE1(SGMII_PHY_LANE_STATUS))) & (1 << 1)) != 0) {
              break;
            }
        }

        Emac_SleepMS(1);
      } while (0 < --timeOut);

      if (0 >= timeOut) {
        EMAC_PRINT_0("SGMII PHY init failed\r\n");
        return FALSE;
      }

    // Ensure PHY is never initialized twice
    IsPhyInitialized[phyIndex] = TRUE;
  }

  /* Configuring loopback mode */
  switch (cfg->modeLoopback) {
    case EMAC_LB_PHY_DIG:     /* Digital loopback from PCS (Parallel loopback bypassing QMP Serdes) */
      if(phyIndex == 0){
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_BIST_GEN2), 0x0);      /* Disable SERDES loopback */
          HWIO_OUT(QSERVER_REG_PRE(LPB_EN), 0x00);
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_BIST_GEN0), 0x02);   /* Set Digital Loopback bit */
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_CDR_CTRL1), 0x01);   /* CDR closed loop is required */
      }
      else{
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_BIST_GEN2), 0x0);      /* Disable SERDES loopback */
          HWIO_OUT(QSERVER_REG_PRE1(LPB_EN), 0x00);
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_BIST_GEN0), 0x02);   /* Set Digital Loopback bit */
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_CDR_CTRL1), 0x01);   /* CDR closed loop is required */
      }
      EMAC_PRINT_0("PHY DIGITAL loopback mode activated\r\n");
      break;

    case EMAC_LB_PHY_SERDES:  /* PHY SERDES loopback (Serial Loopback from QMP Serdes) */
      if(phyIndex == 0){
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_BIST_GEN0), 0x0);    /* Disable digital loopback */
          HWIO_OUT(QSERVER_REG_PRE(LPB_EN), 0x30);
          Emac_SleepMS(1);
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_CDR_CTRL1), 0x01);   /* CDR closed loop is required */
          Emac_SleepMS(1);
      }
      else{
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_BIST_GEN0), 0x0);    /* Disable digital loopback */
          HWIO_OUT(QSERVER_REG_PRE1(LPB_EN), 0x30);
          Emac_SleepMS(1);
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_CDR_CTRL1), 0x01);   /* CDR closed loop is required */
          Emac_SleepMS(1);
      }

      EMAC_PRINT_0("PHY SERDES loopback mode activated\r\n");
      break;

    default:                        /* Either no loopback or non-PHY loopback */
      if(phyIndex == 0){
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_BIST_GEN0), 0x0);    /* Disable digital loopback */
          HWIO_OUT(QSERVER_REG_PRE(LPB_EN), 0x00);
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_BIST_GEN2), 0x0);      /* Disable SERDES loopback */
          HWIO_OUT(PHY_REG_PRE(SGMII_PHY_CDR_CTRL1), 0x0);    /* No CDR closed loop */
      }
      else{
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_BIST_GEN0), 0x0);    /* Disable digital loopback */
          HWIO_OUT(QSERVER_REG_PRE1(LPB_EN), 0x00);
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_BIST_GEN2), 0x0);      /* Disable SERDES loopback */
          HWIO_OUT(PHY_REG_PRE1(SGMII_PHY_CDR_CTRL1), 0x0);    /* No CDR closed loop */
      }
      break;
  }

  return Emac_PhyCheckStatusSgmii(phyIndex);
}


/**
 * @brief       Initialize the phy hw
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyHwInit
(
 IN uint8 phyIndex,
 IN const EMAC_PHY_CFG *cfg
 )
{
  return Emac_PhyHwInitSgmii(phyIndex, cfg);
}

/**
 * @brief       reset phy
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyHwReset(uint8 phyIndex)
{
  return Emac_PhyHwResetSgmii(phyIndex);
}

/**
 * @brief       Clean up after Phy HW
 *
 * @return      TRUE if successful, else failed
 */
void Emac_PhyCleanupSgmii(void)
{
  EMAC_PRINT_0("SGMII will not be reset, only cleanup if any\r\n");
  uint8 phyIndex = 0;
  Emac_PhyHwReset(phyIndex);
}

/**
 * @brief       Check if Link is up
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyIsLinkUpSgmii
(
 IN uint8 phyIndex,
 IN boolean *isLinkUp
)
{
  uint32 value = 0;

  if (NULL == isLinkUp) {
    EMAC_PRINT_0("NULL parameter\r\n");
    return FALSE;
  }

  /* If auto-neg enabled, check if completed */
  if(phyIndex == 0)
    value = HWIO_INF(PHY_REG_PRE(SGMII_PHY_AUTONEG_CFG2), AN_ENABLE);
  else
    value = HWIO_INF(PHY_REG_PRE1(SGMII_PHY_AUTONEG_CFG2), AN_ENABLE);
  if (0x1 == value) {
    /* Verify Auto Neg completed */
    if(phyIndex == 0){
        if (0x0 == HWIO_INF(PHY_REG_PRE(SGMII_PHY_INTERRUPT_STATUS), AN_END)) {
          EMAC_PRINT_0("Auto-neg not complete\r\n");
          *isLinkUp = FALSE;
          return TRUE;
        }
    }
    else{
        if (0x0 == HWIO_INF(PHY_REG_PRE1(SGMII_PHY_INTERRUPT_STATUS), AN_END)) {
          EMAC_PRINT_0("Auto-neg not complete\r\n");
          *isLinkUp = FALSE;
          return TRUE;
        }
    }

    /* Check if auto-neg illegal termination occurred */
    if(phyIndex == 0){
        if (0x1 == HWIO_INF(PHY_REG_PRE(SGMII_PHY_INTERRUPT_STATUS), AN_ILLEGAL_TERM)) {
          EMAC_PRINT_0("Auto-neg illegal term\r\n");
          *isLinkUp = FALSE;
          return FALSE;
        }
    }
    else{
        if (0x1 == HWIO_INF(PHY_REG_PRE1(SGMII_PHY_INTERRUPT_STATUS), AN_ILLEGAL_TERM)) {
          EMAC_PRINT_0("Auto-neg illegal term\r\n");
          *isLinkUp = FALSE;
          return FALSE;
        }
    }
  }

  /* Link up/down, speed and duplex information about copper Link can be read from
   * SGMII_PHY_AUTONEG1_STATUS and SGMII_PHY_AUTONEG0_STATUS registers on completion
   * of Auto-negotiation, each contains 8 bits of the total 16 bits sent from the EPHY
   * SGMII_PHY_AUTONEG1_STATUS contains MSB 8-bit from data, so bit 7 in this value
   * is bit 15 of the total value. This bit is '1' for link-up, see SGMII specification
   */
  if(phyIndex == 0)
    value = HWIO_IN(PHY_REG_PRE(SGMII_PHY_AUTONEG1_STATUS));
  else
    value = HWIO_IN(PHY_REG_PRE1(SGMII_PHY_AUTONEG1_STATUS));
  /* Check bit 7 for link status */
  if (0 == (value & (1 << 7))) {
    *isLinkUp = FALSE;
  }
  else {
    *isLinkUp = TRUE;
  }

  return TRUE;
}

