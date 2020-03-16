/**---------------------------------------------------------------------------
 * @file     emac_snp.c
 *
 * @brief    externalized emac APIs for SimpleNetworkProtocol
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include "emac_ephy.h"
#include "emac_phy_sgmii.h"
#include "emac_ephy.h"
#include "emac_drv.h"
#include <Uefi.h>
//#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <string.h>
#include "emac_snp.h"

#define LINKUP_RETRY_COUNT 30

extern EMAC_DRV drv[2];

static VOID* TxFreeList[EMAC_TX_RING_SIZE] = {NULL};
static UINTN StartIdx = 0;
static UINTN DoneIdx = 0;
static UINTN EndIdx = 0;

#define CopyMem memcpy
#define ZeroMem(a,b) memset(a,0,b)
#define CompareMem memcmp

STATIC UINT8 MACFrame[] =
{
    0xff,0xff,0xff,0xff,0xff,0xff, /* broadcast address */
    0x5c,0x52,0x82,0x4a,0x46,0x3f, /* source address */
    0x08,0x06, /* ARP diagram type 0x8086 */
    0x00,0x01, /* hardware type: ethernet 0x0001 */
    0x08,0x00, /* Protocol Type: IP layer 0x0800 */
    0x06,      /* Hardware size: 6 */
    0x04,      /* Protocol size: 4 */
    0x00,0x01, /* opcode: arp request 0x0001 */
    0x5c,0x52,0x82,0x4a,0x46,0x3f, /* Sender MAC address */
    0x00,0x00,0x00,0x00,           /*Sender IP address */
    0x00,0x00,0x00,0x00,0x00,0x00, /* Target MAC address */
    0x08,0x08,0x08,0x08            /* Target IP address */
};


extern void fake_emac_isr(uint8 emacIndex);


//@TODO Remove once Joe give clock driver fixes
/**
 * @brief       Wait for clock change update
 *
 * @param[in]   regAddr    Clock register to wait for update change
 *
 * @return      TRUE if clock updated, else failed
 */
  static int Emac_WaitForClockUpdate
(
 IN uint64 regAddr
 )
{
  volatile uint32 wait_cycles = 300;
  do {
    volatile uint32 regVal = in_dword((uintnt)regAddr);
    if (0 == (regVal & 0x1)) {
      return TRUE; /* Success */
    }
  } while (wait_cycles-- > 0);

  return FALSE;
}



/**
  Set clock frequencies

  @retval EFI_SUCCESS           The operation was successfully completed.

  @retval EFI_UNSUPPORTED       Target does not support EMAC

**/
BOOLEAN SetEmacClocksFreq
(
 IN UINT32    emacInst,
 IN UINT64    clkSystem,
 IN UINT32    speed,
 IN INT32     clkMDIO
 )
{
#ifndef CONFIG_TESTOS_EMU
  uint32 freqMode, lpwClkSel, lpwState, macSpeed;

  if (0 == emacInst)
  {
    /* Step 1: Enable all CBC's */
    /* Note: RX clock CBCR (GCC_EMAC_0_RX_CBCR) is not enabled at this point.
     * As a workaournd for CR QCTDD00859345, RX clock is enabled only after
     * drivers init is done.
     */
    HWIO_OUTF(GCCMW_SFVBU_EMAC0_DVM_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC0_AHB_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC0_AXI_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC0_IOMMU_CFG_AHB_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC0_SYS_25M_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_GMII0_TX_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC0_125M_CBCR, CLK_ENABLE, 0x1);
    //HWIO_OUTF(GCCMW_EMAC0_SYS_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC0_RAM_SYS_CBCR, CLK_ENABLE, 0x1);

    /* Step 2: Config RCG for gcc_Emac_0_125m_clk */
    if (EMAC_CLK_19_2_SAFE == clkSystem) {
      /* Use 19.2MHz as safe emac system clock */
      HWIO_OUTF2(GCCMW_EMAC0_125M_CFG_RCGR,
          SRC_SEL, SRC_DIV,
          0x0 /* 19.2MHz */, 0x0 /* BYPASS */);
    } else {
      /* Select 125Mhz coming from SGMII PHY, no divide */
      HWIO_OUTF2(GCCMW_EMAC0_125M_CFG_RCGR,
          SRC_SEL, SRC_DIV,
          0x1 /* 125MHz */, 0x0 /* BYPASS */);
    }

    HWIO_OUTF(GCCMW_EMAC0_125M_CMD_RCGR, UPDATE, 0x1);
    if (FALSE == Emac_WaitForClockUpdate(HWIO_GCCMW_EMAC0_125M_CMD_RCGR_ADDR)) {
      return FALSE; /* Failure */
    }

    /* If safe clock config, we're done */
    if (EMAC_CLK_19_2_SAFE == clkSystem) {
      return TRUE; /* Success */
    }

    /* Step 3: config RCG for gcc_emac_0_tx_clk */
    HWIO_OUTF3(GCCMW_EMAC0_TX_CFG_RCGR,
        MODE, SRC_SEL, SRC_DIV,
        0x0 /* BYPASS */, 0x2 /* emac_0_tx_clk */, 0x0 /* BYPASS */);
    HWIO_OUTF(GCCMW_EMAC0_TX_M, M, 0x0);
    HWIO_OUTF(GCCMW_EMAC0_TX_N, N, 0x0);
    HWIO_OUTF(GCCMW_EMAC0_TX_D, D, 0x0);
    HWIO_OUTF(GCCMW_EMAC0_TX_CMD_RCGR, UPDATE, 0x1);
    if (FALSE == Emac_WaitForClockUpdate(HWIO_GCCMW_EMAC0_TX_CMD_RCGR_ADDR)) {
      return FALSE;
    }

    /* Step4: config RCG for gcc_emac_0_sys_25m_clk */
    if (EMAC_CLK_19_2_DIV_6 == clkSystem) {
      /* Select 19.2MHz source and divide by 6 */
      HWIO_OUTF2(GCCMW_EMAC0_SYS_25M_CFG_RCGR,
          SRC_SEL, SRC_DIV,
          0x0 /* 19.2MHz */, 0xB /* DIV6 */);
    } else {
      /* Select 125Mhz comming from SGMII PHY, divide by 5 */
      HWIO_OUTF2(GCCMW_EMAC0_SYS_25M_CFG_RCGR,
          SRC_SEL, SRC_DIV,
          0x1 /* 125MHz */, 0x9 /* DIV5 */);
    }
    HWIO_OUTF(GCCMW_EMAC0_SYS_25M_CMD_RCGR, UPDATE, 0x1);
    if (FALSE == Emac_WaitForClockUpdate(HWIO_GCCMW_EMAC0_SYS_25M_CMD_RCGR_ADDR)) {
      return FALSE; /* Failure */
    }
  }
  else if (1 == emacInst) {
    /* Step 1: Enable all CBC's */
    /* Note: RX clock CBCR (GCCMW_EMAC0_RX_CBCR) is not enabled at this point.
     * As a workaournd for CR QCTDD00859345, RX clock is enabled only after
     * drivers init is done.
     */
    HWIO_OUTF(GCCMW_SFVBU_EMAC1_DVM_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC1_AHB_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC1_AXI_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC1_IOMMU_CFG_AHB_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC1_SYS_25M_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_GMII1_TX_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC1_125M_CBCR, CLK_ENABLE, 0x1);
    //HWIO_OUTF(GCCMW_EMAC0_SYS_CBCR, CLK_ENABLE, 0x1);
    HWIO_OUTF(GCCMW_EMAC1_RAM_SYS_CBCR, CLK_ENABLE, 0x1);

    /* Step 2: Config RCG for gcc_emac_1_125m_clk */
    if (EMAC_CLK_19_2_SAFE == clkSystem) {
      /* Use 19.2MHz as safe emac system clock */
      HWIO_OUTF2(GCCMW_EMAC1_125M_CFG_RCGR,
          SRC_SEL, SRC_DIV,
          0x0 /* 19.2MHz */, 0x0 /* BYPASS */);
    } else {
      /* Select 125Mhz coming from SGMII PHY, no divide */
      HWIO_OUTF2(GCCMW_EMAC1_125M_CFG_RCGR,
          SRC_SEL, SRC_DIV,
          0x1 /* 125MHz */, 0x0 /* BYPASS */);
    }

    HWIO_OUTF(GCCMW_EMAC1_125M_CMD_RCGR, UPDATE, 0x1);
    if (FALSE == Emac_WaitForClockUpdate(HWIO_GCCMW_EMAC1_125M_CMD_RCGR_ADDR)) {
      return FALSE; /* Failure */
    }

    /* If safe clock config, we're done */
    if (EMAC_CLK_19_2_SAFE == clkSystem) {
      return TRUE; /* Success */
    }

    /* Step 3: config RCG for gcc_Emac_0_tx_clk */
    HWIO_OUTF3(GCCMW_EMAC1_TX_CFG_RCGR,
        MODE, SRC_SEL, SRC_DIV,
        0x0 /* BYPASS */, 0x2 /* emac_1_tx_clk */, 0x0 /* BYPASS */);
    HWIO_OUTF(GCCMW_EMAC1_TX_M, M, 0x0);
    HWIO_OUTF(GCCMW_EMAC1_TX_N, N, 0x0);
    HWIO_OUTF(GCCMW_EMAC1_TX_D, D, 0x0);
    HWIO_OUTF(GCCMW_EMAC1_TX_CMD_RCGR, UPDATE, 0x1);
    if (FALSE == Emac_WaitForClockUpdate(HWIO_GCCMW_EMAC1_TX_CMD_RCGR_ADDR)) {
      return FALSE; /* Failure */
    }

    /* Step4: config RCG for gcc_emac_1_sys_25m_clk */
    if (EMAC_CLK_19_2_DIV_6 == clkSystem) {
      /* Select 19.2MHz source and divide by 6 */
      HWIO_OUTF2(GCCMW_EMAC1_SYS_25M_CFG_RCGR,
          SRC_SEL, SRC_DIV,
          0x0 /* 19.2MHz */, 0xB /* DIV6 */);
    } else {
      /* Select 125Mhz comming from SGMII PHY, divide by 5 */
      HWIO_OUTF2(GCCMW_EMAC1_SYS_25M_CFG_RCGR,
          SRC_SEL, SRC_DIV,
          0x1 /* 125MHz */, 0x9 /* DIV5 */);
    }
    HWIO_OUTF(GCCMW_EMAC1_SYS_25M_CMD_RCGR, UPDATE, 0x1);
    if (FALSE == Emac_WaitForClockUpdate(HWIO_GCCMW_EMAC1_SYS_25M_CMD_RCGR_ADDR)) {
      return FALSE; /* Failure */
    }
  }

  /* System clock configuration */
  if (1000 == speed) {
    freqMode = 0x1;
    macSpeed = 0x2;
  }
  else if ((100 == speed) || (10 == speed)) {
    freqMode = 0x0;
    macSpeed = 0x1;
  }
  else {
    return FALSE;   /* Failure */
  }

  /* Set system clock */
  if (EMAC_CLK_125 == clkSystem) {
    /* Setting below is valid also for EMAC_CLK_19_2_SAFE, but that
     * system clock should never be required by the driver
     */
    lpwClkSel = 0x0;
    lpwState  = 0x0;
  }
  else if (EMAC_CLK_25 == clkSystem) {
    lpwClkSel = 0x0;
    lpwState  = 0x1;
  }
  else if (EMAC_CLK_25_DIV_8 == clkSystem) {
    lpwClkSel = 0x1;
    lpwState  = 0x1;
  }
  else if (EMAC_CLK_19_2_DIV_6 == clkSystem) {
    lpwClkSel = 0x0;
    lpwState  = 0x1;
  }
  else {
    return FALSE;   /* Failure */
  }

  if(emacInst == 0)
    HWIO_OUTF(EMAC_REG_PRE(EMAC_WRAPPER_CSR1), FREQ_MODE, freqMode);
  else
    HWIO_OUTF(EMAC_REG_PRE1(EMAC_WRAPPER_CSR1), FREQ_MODE, freqMode);

  Emac_SleepMS(2000);

  /* Set low-power mode related clocks */
  if(emacInst == 0)
      HWIO_OUTF2(EMAC_REG_PRE(DMA_MAS_CTRL),
          LPW_STATE, LPW_CLK_SEL,
          lpwState,  lpwClkSel);
  else
      HWIO_OUTF2(EMAC_REG_PRE1(DMA_MAS_CTRL),
          LPW_STATE, LPW_CLK_SEL,
          lpwState,  lpwClkSel);

  Emac_SleepMS(2000);

  /* Speed */
  if(emacInst == 0)
   HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), SPEED, macSpeed);
  else
   HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), SPEED, macSpeed);

  Emac_SleepMS(2000);

  /* MDIO clock settings */
  /* Note: For System clocks 125, 25, & 25/8 MHz MDIO clock is (25/X) MHz
   *       For system clock 19.2/6, MDIO clock is ((19.2/6)/X) MHz
   */
  switch (clkMDIO) {
    case EMAC_MDIO_CLK_25M_4:
    case EMAC_MDIO_CLK_25M_6:
    case EMAC_MDIO_CLK_25M_8:
    case EMAC_MDIO_CLK_25M_10:
    case EMAC_MDIO_CLK_25M_32:
    case EMAC_MDIO_CLK_25M_68:
    case EMAC_MDIO_CLK_25M_128:
      /* Valid MDIO clock */
      if(emacInst == 0)
        HWIO_OUTF(EMAC_REG_PRE(MDIO_CTRL), MDIO_CLK_SEL, clkMDIO);
      else
        HWIO_OUTF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_CLK_SEL, clkMDIO);
      break;

    default:
      return FALSE;
  }
  return TRUE;
#else
  if(emacInst == 0)
    HWIO_OUTF(EMAC_REG_PRE(EMAC_WRAPPER_CSR2), PHY_RESET, 0x1);
  else
    HWIO_OUTF(EMAC_REG_PRE1(EMAC_WRAPPER_CSR2), PHY_RESET, 0x1);
  return TRUE;
#endif

}


/**
  Reset EMAC Core
**/
static void ResetEmacCoreBM ( UINT8 emacIndex )
{
  EMAC_PRINT_1("ResetEmacCoreBM emacIndex %d\r\n", emacIndex);

  if(emacIndex == 0){
      HWIO_OUTF(GCCMW_EMAC_AHB2PHY_CFG_AHB_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_SFVBU_EMAC0_DVM_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC0_AXI_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC0_AHB_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC0_125M_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC0_SYS_25M_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_GMII0_TX_CBCR, CLK_ENABLE, 0x0); //TBD - Check this clock reg
      HWIO_OUTF(GCCMW_EMAC0_RX_CBCR, CLK_ENABLE, 0x0);
      //HWIO_OUTF(GCCMW_EMAC0_SYS_CBCR, CLK_ENABLE, 0x0); // TBD - Not mentioned in the HPG but in VI
      HWIO_OUTF(GCCMW_EMAC0_RAM_SYS_CBCR, CLK_ENABLE, 0x0);

      Emac_SleepMS(EMAC_HW_RESET_DELAY_MS);
      HWIO_OUTF(GCCMW_EMAC0_BCR, BLK_ARES, 1); /* Enable EMAC reset */
      Emac_SleepMS(EMAC_HW_RESET_DELAY_MS);
      HWIO_OUTF(GCCMW_EMAC0_BCR, BLK_ARES, 0); /* Disable EAMC_0 reset */
      Emac_SleepMS(EMAC_HW_RESET_DELAY_MS);

      /* Enable all clocks */
      HWIO_OUTF(GCCMW_EMAC_AHB2PHY_CFG_AHB_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_SFVBU_EMAC0_DVM_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC0_AXI_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC0_AHB_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC0_125M_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC0_SYS_25M_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_GMII0_TX_CBCR, CLK_ENABLE, 0x1); //TBD - Check this clock reg
      //HWIO_OUTF(GCCMW_EMAC0_RX_CBCR, CLK_ENABLE, 0x1);
      //HWIO_OUTF(GCCMW_EMAC0_SYS_CBCR, CLK_ENABLE, 0x1); // TBD - Not mentioned in the HPG but in VI
      HWIO_OUTF(GCCMW_EMAC0_RAM_SYS_CBCR, CLK_ENABLE, 0x1);
  }
  else{
      /* Disable all emac1 clocks */
      HWIO_OUTF(GCCMW_SFVBU_EMAC1_DVM_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC1_AXI_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC1_AHB_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC1_125M_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC1_SYS_25M_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_GMII1_TX_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC1_RX_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC1_IOMMU_CFG_AHB_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC1_QSMMUV3_CLIENT_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_SFAB_EMAC1_FCLK_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_SFVBU_EMAC1_DVM_CBCR, CLK_ENABLE, 0x0);
      //HWIO_OUTF(GCCMW_EMAC1_SYS_CBCR, CLK_ENABLE, 0x0);
      HWIO_OUTF(GCCMW_EMAC1_RAM_SYS_CBCR, CLK_ENABLE, 0x0);

      Emac_SleepMS(EMAC_HW_RESET_DELAY_MS);

      HWIO_OUTF(GCCMW_EMAC1_BCR, BLK_ARES, 1); /* Enable EMAC reset */
      Emac_SleepMS(EMAC_HW_RESET_DELAY_MS); /* Sleep to allow HW to reset */
      HWIO_OUTF(GCCMW_EMAC1_BCR, BLK_ARES, 0); /* Disable EAMC_0 reset */

      Emac_SleepMS(EMAC_HW_RESET_DELAY_MS);

      /* Enable all emac1 clocks */
      HWIO_OUTF(GCCMW_SFVBU_EMAC1_DVM_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC1_AXI_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC1_AHB_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC1_125M_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC1_SYS_25M_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_GMII1_TX_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC1_IOMMU_CFG_AHB_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_EMAC1_QSMMUV3_CLIENT_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_SFAB_EMAC1_FCLK_CBCR, CLK_ENABLE, 0x1);
      HWIO_OUTF(GCCMW_SFVBU_EMAC1_DVM_CBCR, CLK_ENABLE, 0x1);
      //HWIO_OUTF(GCCMW_EMAC0_SYS_CBCR, CLK_ENABLE, 0x1);
      /* RX will be enabled only after PHY initialization */
      HWIO_OUTF(GCCMW_EMAC1_RAM_SYS_CBCR, CLK_ENABLE, 0x1);
  }

  Emac_SleepMS(EMAC_HW_RESET_DELAY_MS);
}


BOOLEAN EMAC_ProcessIsr () {

  UINT32 countTx;
  UINTN DoneIdxTemp, EndIdxTemp;

  Emac_SleepMS(0);

  countTx = HWIO_INF(EMAC_REG_PRE(TXMAC_STATC_REG0), TX_OK);
  DoneIdx = (DoneIdx + countTx) % EMAC_TX_RING_SIZE;

  DoneIdxTemp = DoneIdx;
  EndIdxTemp = EndIdx;

  if (DoneIdx < StartIdx) {
    DoneIdxTemp += EMAC_TX_RING_SIZE;
  }
  if (EndIdx < StartIdx) {
    EndIdxTemp += EMAC_TX_RING_SIZE;
  }
  //Transmitted more then we thought we did?
  if (DoneIdxTemp > EndIdxTemp) {
    //ASSERT(EndIdxTemp <= DoneIdxTemp);
    return FALSE;
  }
  return TRUE;

}


VOID  *EMAC_GetTransmittedBuffer ()
{
  VOID *RetBuf = NULL;
  if (StartIdx != DoneIdx) {
    RetBuf = TxFreeList[StartIdx];
    StartIdx = (StartIdx + 1) % EMAC_TX_RING_SIZE;
  }
  return RetBuf;
}


void Emac_SetRxClockPostInitDriver(uint8 emacIndex)
{
  /* Workaournd for CR QCTDD00859345
   * RX clock CBCR is enabled at this point
   * As a workaournd for CR QCTDD00859345, RX clock is not enabled
   * at Emac_initClocks but only after drivers init is done
   */
   if(emacIndex == 0)
     HWIO_OUTF(GCCMW_EMAC0_RX_CBCR, CLK_ENABLE, 0x1);
   else
     HWIO_OUTF(GCCMW_EMAC1_RX_CBCR, CLK_ENABLE, 0x1);

  Emac_SleepMS(20);
}

/**
 * @brief       Reset the phy and ephy
 *
 * @return      TRUE if successful, else failed
 */
BOOLEAN EMAC_Init(
  UINT32        index,
  UINT32        speed,
  BOOLEAN       isFullDuplex,
  EMAC_LB_MODE  modeLoopback,
  UINT8*    extraCfg
)
{
  EMAC_CFG drvCfg       = {{0},0};
  EMAC_PHY_CFG phyCfg   = {0};
  EMAC_EPHY_CFG ephyCfg = {0};

  EMAC_CLK clkSystem = EMAC_CLK_125;

  if (NULL != extraCfg) {
    drvCfg = *(EMAC_CFG*)extraCfg;//don't want to damage existed code too much. So low performance assign directly
  } else {
    drvCfg.rxQueues = 1;
  }
  /* Configure GPIOs for emac */
  Emac_ConfigGPIOs();

  /* Reset the EMAC HW */
  ResetEmacCoreBM(index);
  drv[index].emacState = INITIALIZED;
  EMAC_PRINT_0("EMAC HW Reset Done\r\n");

  Emac_SleepMS(200);

  Emac_PhyHwReset(index);

  Emac_SleepMS(EMAC_PHY_LATENCY);

  if ((EMAC_LB_MAC != modeLoopback) &&
      (EMAC_LB_PHY_DIG != modeLoopback) &&
      (EMAC_LB_PHY_SERDES != modeLoopback))
  {
    ephyCfg.speed = speed;
    ephyCfg.modeLoopback = modeLoopback;
    ephyCfg.isFullDuplex = isFullDuplex;
    ephyCfg.isAutoNeg = TRUE;

    Emac_EphyHwReset(index);
    Emac_SleepMS(EMAC_EPHY_LATENCY);

    if (TRUE != Emac_EphyInit(index, &ephyCfg))
    {
      EMAC_PRINT_0("EPHY init failed\r\n");
      goto cleanup;
    }
  }
  Emac_SleepMS(EMAC_EPHY_LATENCY);

  /* Get Auto-Negotiated speed/duplex for EPHY and use that to configure PHY/DMA */
  UINT32 ephy_speed = speed;
  BOOLEAN ephy_isFullDuplex = isFullDuplex;

  if ((EMAC_LB_MAC != modeLoopback) &&
      (EMAC_LB_PHY_DIG != modeLoopback) &&
      (EMAC_LB_PHY_SERDES != modeLoopback)) {
      UINTN linkup_retry = 0;

      for (linkup_retry = 0; linkup_retry < LINKUP_RETRY_COUNT; linkup_retry++) {
        if (TRUE == EMAC_GetSpeedAndDuplex(index, &ephy_speed, &ephy_isFullDuplex)) {
          EMAC_PRINT_2( "EPHY Speed: %d, isFullDuplex: %d\r\n", ephy_speed, ephy_isFullDuplex);
          break;
        }

        Emac_SleepMS(500);
      }

      if (linkup_retry == LINKUP_RETRY_COUNT)
      {
        EMAC_PRINT_0( "ERROR: No EPHY linkup\r\n" );
        ephy_speed = 1000;
        ephy_isFullDuplex = TRUE;
      }
  }

  /* Initialize SGMII PHY */
  phyCfg.speed = ephy_speed;
  phyCfg.modeLoopback =  modeLoopback; //EMAC_LB_PHY_DIG if we want to test internal loopback.
  phyCfg.isFullDuplex = ephy_isFullDuplex;
  if ((EMAC_LB_MAC != modeLoopback) &&
      (EMAC_LB_PHY_DIG != modeLoopback) &&
      (EMAC_LB_PHY_SERDES != modeLoopback))
  {
    phyCfg.isAutoNeg = TRUE; /* When using EPHY must enable SGMII auto-neg */
  }
  else
    phyCfg.isAutoNeg = FALSE;

  /* Reset SGMII */
#ifndef CONFIG_TESTOS_EMU
  if (TRUE != Emac_PhyHwReset(index))
  {
    EMAC_PRINT_0("PHY driver reset failed\r\n");
    goto cleanup; /* Failure */
  }
  EMAC_PRINT_0("EMAC PHY HW Reset Done\r\n");

  Emac_SleepMS(EMAC_PHY_LATENCY);

  /*
  //TODO: @dgurjar we need to use clock library to enable this in UEFI
  // PMIC clock required for EMAC
  pm_err_flag_type Status = pm_clk_sw_enable(8, PM_CLK_DIFF_1, TRUE);
  if (PM_ERR_FLAG__SUCCESS != Status)
  {
    EMAC_PRINT_0("Failed to enable EFI_PM_CLK_DIFF_1");
  }
  */

  /*Initialize the phy SGMII layer, make sure that ethernet cable is plugged into eth1*/
  if (modeLoopback != EMAC_LB_MAC && TRUE != Emac_PhyHwInit(index, &phyCfg))
  {
    EMAC_PRINT_0("PHY driver init failed\r\n");
    //goto cleanup; /* Failure */
  }
  Emac_SleepMS(EMAC_PHY_LATENCY);
#endif

  Emac_ResetInternalSRAM(index);

  /* Set EMAC driver configuration and init */
  drvCfg.speed = ephy_speed;
  drvCfg.isFullDuplex = ephy_isFullDuplex;
  drvCfg.modeLoopback = modeLoopback;
  drvCfg.isPromiscuous = TRUE;//FALSE;
  drvCfg.clkSystem = clkSystem;
  drvCfg.clkMDIO = EMAC_MDIO_CLK_25M_4;
  drvCfg.txQueues = EMAC_TXQ_NUM;
  drvCfg.sizeBufRX = EMAC_RX_BUF_SIZE;
  drvCfg.txIrqModCnt = 0xFFFF; /* TX Moderation set to max value */
  drvCfg.rxIrqModCnt = 0xFFFF; /* RX Moderation set to max value */
  drvCfg.isTxFcEnable = FALSE; /* if TRUE then send PAUSE frames if RX overflow occurs*/
  drvCfg.rxRingSize = EMAC_RX_RING_SIZE;
  drvCfg.txRingSize = EMAC_TX_RING_SIZE;

  drvCfg.addr[0] = 0x00;
  drvCfg.addr[1] = 0x00;
  drvCfg.addr[2] = 0xAA;
  drvCfg.addr[3] = 0xBB;
  drvCfg.addr[4] = 0xCC;
  drvCfg.addr[5] = 0xDD;

  /* Set Clock Frequency */
  if (TRUE != SetEmacClocksFreq(index, drvCfg.clkSystem, drvCfg.speed, drvCfg.clkMDIO))
  {
    EMAC_PRINT_0("Setting Clock Frequency failed\r\n");
    //goto cleanup; /* Failure */
  }

  return TRUE;

cleanup:
  EMAC_PRINT_0("Failure in EMAC init\r\n");
  EMAC_Shutdown(index, NULL, NULL);
  return FALSE;
}

void EMAC_Mini_Init()
{
  EMAC_Init(0, 1000, TRUE, EMAC_LB_NONE, NULL);
  EMAC_Init(1, 1000, TRUE, EMAC_LB_NONE, NULL);
}

EFI_STATUS EMAC_Transmit (
  IN  UINT8   emacIndex,
  IN  UINT8   *Buffer,
  IN  UINTN   BufferLength
){
  EFI_STATUS Status = EFI_SUCCESS;

  if (BufferLength > EMAC_TX_BUF_SIZE) {
    return EFI_DEVICE_ERROR;
  }

  // Cannot send buffer if our ring is full
  if (((EndIdx + 1) % EMAC_TX_RING_SIZE) == StartIdx) {
   // return EFI_NOT_READY;
  }

  // Set registers for TX
  if (TRUE != Emac_Send( emacIndex, Buffer, BufferLength, TRUE)) {
    EMAC_PRINT_0("Failed to TX\n");
    Status = EFI_DEVICE_ERROR;
    goto cleanup;
  }

  // Insert this buffer to the end of the tx ring
  TxFreeList[EndIdx] = (VOID *)Buffer;
  EndIdx = (EndIdx + 1) % EMAC_TX_RING_SIZE;

  // Sleep to recieve TX interrupts and to ensure operation completes
  UINTN countTx = 0;
//  static UINTN TXCNT = 0;
  Emac_SleepMS(2);

  if(emacIndex == 0)
    countTx = HWIO_INF(EMAC_REG_PRE(TXMAC_STATC_REG0), TX_OK);
  else
    countTx = HWIO_INF(EMAC_REG_PRE1(TXMAC_STATC_REG0), TX_OK);

  // Check TX OK to see if the transfer was successful
  if (1 != countTx) {
      //StartIdx = (StartIdx + 1) % EMAC_TX_RING_SIZE;
      Status = FALSE;
      ///EMAC_PRINT_0("EMAC_Transmit fail\r\n");
      ///EMAC_PRINT_1("countTx %u \r\n", countTx);
  }
  else {
      //Emac_SleepMS(10);
      //StartIdx = (StartIdx + 1) % EMAC_TX_RING_SIZE;
      //countTx = HWIO_INF(EMAC_REG_PRE(TXMAC_STATC_REG0), TX_OK);
      ///EMAC_PRINT_1("countTx %u \r\n", countTx);
  }

cleanup:
  return Status;
}

/**
 * @brief       Receive data
 *
 * @return      TRUE if successful, else failed
 */
BOOLEAN EMAC_Receive (
  IN      UINT8   emacIndex,
  IN      UINT8   queue,
  OUT     UINT8   *Buffer,
  IN OUT  UINTN   *BufferLength,
  OUT     UINT8  *bufRxD_A//currently it seems that only type A descriptor is used, need to confirm it in the future
)
{
  BOOLEAN Status = FALSE;
  UINT32 procIndex,bufIndex;
  UINT32 consIndex;
  UINT32 prodIndex;

#if 0
  // If we didn't install the isr_Core, the system isn't initialized for receive
  if (drv[emacIndex].emacState != RUNNING) {
    EMAC_PRINT_0("EMAC not Running!!\r\n");
    return Status;
  }
#endif

switch (queue) {
case 0:
  if(emacIndex == 0){
    procIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_3), RFD0_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROD_IDX);
  }
  else{
    procIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_0), RFD0_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_3), RFD0_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_0), RFD0_PROD_IDX);
  }
  break;
case 1:
  if(emacIndex == 0){
    procIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_5), RFD1_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_7), RFD1_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_5), RFD1_PROD_IDX);
  }
  else{
    procIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_5), RFD1_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_7), RFD1_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_5), RFD1_PROD_IDX);
  }
  break;
case 2:
  if(emacIndex == 0){
    procIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_6), RFD2_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_7), RFD2_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_6), RFD2_PROD_IDX);
  }
  else{
    procIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_6), RFD2_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_7), RFD2_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_6), RFD2_PROD_IDX);
  }
  break;
case 3:
  if(emacIndex == 0){
    procIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_13), RFD3_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_8), RFD3_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_13), RFD3_PROD_IDX);
  }
  else{
    procIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_13), RFD3_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_8), RFD3_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_13), RFD3_PROD_IDX);
  }
  break;
case 4:
  if(emacIndex == 0){
    procIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_14), RFD4_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_8), RFD4_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_14), RFD4_PROD_IDX);
  }
  else{
    procIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_14), RFD4_PROC_IDX);
    consIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_8), RFD4_CONS_IDX);
    prodIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_14), RFD4_PROD_IDX);
  }
  break;
}


  RRD_TYPE_A *curRrdTypeABase = drv[emacIndex].curRrdTypeA[queue];//should check the queue information, not default 0
  RRD_TYPE_A *curRrdProcPtr = (RRD_TYPE_A *)(curRrdTypeABase+procIndex);

  //TODO @ dgurjar implement later with interrupt status check to see if we ever got an rx
 //uint32 IntUnmasked = HWIO_IN(EMAC_REG_PRE(INT_STATUS));
  //uint32 status = statusUnmasked & maskIgnore;
  EMAC_PRINT_5("Got packets procIndex=%d, consIndex=%d, prodIndex=%d, NOR=%d at queue=%d\r\n",
                procIndex,consIndex,prodIndex,curRrdProcPtr->NOR, queue);
  // Parameter validation
  if (NULL == Buffer || NULL == BufferLength) {
    EMAC_PRINT_0("Parameter invalid!\r\n");
    return FALSE;
  }

  // There are no packets to read from
  if ( (0x0 == curRrdProcPtr->UPDT)) {
    EMAC_PRINT_0("No packets to read!\r\n");
    return FALSE;
  }



  // Buffer is too small
  if (*BufferLength < (UINTN)curRrdProcPtr->PKT_SIZE) {
    *BufferLength = (UINTN)curRrdProcPtr->PKT_SIZE;
    EMAC_PRINT_0("Buffer is too small!\r\n");
    return FALSE;
  }
  // Copy from ring buffer into the memory that was passed in
  else {
    if (bufRxD_A != NULL)
      *(RRD_TYPE_A*)bufRxD_A = *curRrdProcPtr;

    *BufferLength = (UINTN)curRrdProcPtr->PKT_SIZE;

    bufIndex = procIndex + drv[emacIndex].countRFD*queue;
    // EMAC_PRINT_2("RX2 buffer queue buf low=%x, high=%x\r\n",(UINT32)drv[emacIndex].rfdbuffer[bufIndex].vaddr ,
    // (UINT32)((uint64)drv[emacIndex].rfdbuffer[bufIndex].vaddr >> 32) );//compre with buf alloc at emac_drv.c,make sure buf is expected.

    CopyMem(Buffer, drv[emacIndex].rfdbuffer[bufIndex].vaddr, *BufferLength);
    //ZeroMem(drv[emacIndex].rfdbuffer[procIndex].vaddr, (*BufferLength));//junwang, ZeroMem seems can't handle unaligned size, such as 0x222
    Emac_Memset(drv[emacIndex].rfdbuffer[bufIndex].vaddr,0,*BufferLength);
    Status = TRUE;
  }

  //DEBUG((DEBUG_INFO, "RX: %d\n", ++RXCNT));
#if 0
  EMAC_PRINT_0("Packet Received!\r\n");
  EMAC_PRINT_1("NOR: %d\r\n", curRrdProcPtr->NOR);
  EMAC_PRINT_1("LENE: %d\r\n", curRrdProcPtr->LENE);
  EMAC_PRINT_1("ProcIndex: %d\r\n", procIndex);
  EMAC_PRINT_1("ConsIndex: %d\r\n", consIndex);
  EMAC_PRINT_1("ProdIndex: %d\r\n", prodIndex);
#endif
  EMAC_PRINT_0("Pkg Data:");
  for (int i=0; i<*BufferLength; i++){
    if (i%8 == 0){
      EMAC_PRINT_0(" ");
    }
    if (i%16 == 0){
      EMAC_PRINT_0("\r\n");
    }

    EMAC_PRINT_1("%02x ",Buffer[i]);
  }
  EMAC_PRINT_0("\r\n-----------------------------------\r\n");

  /* No use for current RRD anymore - clear UPDT field */
  curRrdProcPtr->UPDT = 0;

  /* update the procIndex */
  procIndex += curRrdProcPtr->NOR;
  if (procIndex >= drv[emacIndex].countRFD) {
    procIndex -= drv[emacIndex].countRFD;
  }

  drv[emacIndex].indexProcRFD[queue] = procIndex;

  switch(queue) {
    case 0:
      if(emacIndex == 0)
        HWIO_OUTF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROC_IDX, procIndex);
      else
        HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_0), RFD0_PROC_IDX, procIndex);
      break;
    case 1:
      if(emacIndex == 0)
        HWIO_OUTF(EMAC_REG_PRE(MAILBOX_5), RFD1_PROC_IDX, procIndex);
      else
        HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_5), RFD1_PROC_IDX, procIndex);
      break;
    case 2:
      if(emacIndex == 0)
        HWIO_OUTF(EMAC_REG_PRE(MAILBOX_6), RFD2_PROC_IDX, procIndex);
      else
        HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_6), RFD2_PROC_IDX, procIndex);
      break;
    case 3:
      if(emacIndex == 0)
        HWIO_OUTF(EMAC_REG_PRE(MAILBOX_13), RFD3_PROC_IDX, procIndex);
      else
        HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_13), RFD3_PROC_IDX, procIndex);
      break;
    case 4:
      if(emacIndex == 0)
        HWIO_OUTF(EMAC_REG_PRE(MAILBOX_14), RFD4_PROC_IDX, procIndex);
      else
        HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_14), RFD4_PROC_IDX,procIndex);
      break;
  }

  Status = Emac_SetRecvBuffer(emacIndex, queue, NULL);
  if (!Status) {
    EMAC_PRINT_0("EMAC Failure in SetRecvBuffer\r\n");
  }

  return Status;
}



/**
 * @brief       Get EMAC phy link
 *
 * @param[in]   addr     Gets the mac address
 */
BOOLEAN EMAC_isLinkUp (
  uint8 phyIndex
)
{
#ifndef CONFIG_TESTOS_EMU
  BOOLEAN isLinkUp = FALSE;
  if (TRUE != Emac_PhyIsLinkUpSgmii(phyIndex, &isLinkUp)) {
      EMAC_PRINT_0("Fail to get link status\r\n");
  }
  return isLinkUp;
#else
  // For presil, there is no SGMII
  return TRUE;
#endif
}


BOOLEAN EMAC_GetSpeedAndDuplex (
  UINT8 phyIndex,
  UINT32 *speed,
  BOOLEAN *isFullDuplex
)
{
  BOOLEAN Result = Emac_EphyGetSpeedAndDuplex(phyIndex, speed, isFullDuplex);
  if (TRUE != Result) {
      EMAC_PRINT_0("Failed to get EPHY speed and duplex status\r\n");

  }

  return Result;
}


/**
 * @brief       Set MAC address
 *
 * @param[in]   addr     Gets the mac address
 */
BOOLEAN EMAC_SetMacAddr(UINT8 emacIndex, EFI_MAC_ADDRESS *addr)
{
  Emac_SetMacAddr(emacIndex, (EMAC_ADDR *)addr);
  return TRUE;
}

/**
 * @brief       Set MAC address
 *
 * @param[in]   addr     Gets the mac address
 */
BOOLEAN EMAC_GetMacAddr(UINT8 emacIndex, EFI_MAC_ADDRESS *addr)
{
  Emac_GetMacAddr(emacIndex,(EMAC_ADDR *)addr);
  return TRUE;
}

/**
 * @brief       Cleanup phy, ephy and emac driver
 *
 */
VOID EMAC_Shutdown(UINT8 emacIndex, EFI_EVENT Event, VOID* Ctx)
{
  Emac_CleanupDrivers(emacIndex);
  ResetEmacCoreBM(emacIndex);
}

static UINT8 testindex=0;

BOOLEAN
EMAC_Loopback_Test (
  UINT8 index
)
{
    UINT8  BufferRx[1600];
    UINTN  LengthTx=sizeof(MACFrame);
    UINTN  LengthRx = 1600;
    UINT8 emacIndex = index;

    // Perform loopback test with a generated frame
    MACFrame[LengthTx-5] = testindex++;
    if (EFI_SUCCESS == EMAC_Transmit(emacIndex, MACFrame, LengthTx)) {
       //EMAC_PRINT_0("packet sent\r\n");
    }
    else {
       EMAC_PRINT_0("fail to send packet\r\n");
    }

    Emac_SleepMS(100);
    fake_emac_isr(emacIndex);//read the isr to acknowledge Tx interrupt
    Emac_Memset(BufferRx, 0, sizeof(BufferRx));

    if (EMAC_Receive(emacIndex, 0, BufferRx, &LengthRx, NULL)) {

    }
    else {
        EMAC_PRINT_0 ("fail to recieve packet\r\n");
        return FALSE;
    }

    // Tx Buffer and Rx Buffer should be the same
    if ((0 == CompareMem(MACFrame, BufferRx, LengthTx))) {
        EMAC_PRINT_0 ("Loopback PASS\r\n");
    }
    else {
        EMAC_PRINT_0 ("Loopback FAIL\r\n");
    }

    return TRUE;
}



BOOLEAN
EMAC_SendArp_Test (
  UINT8 index,
  UINT32 times
)
{
    UINT32 i = 1;
    EFI_STATUS Status;
    UINT8 emacIndex = index;

     while(i <= times){
            EMAC_PRINT_1("[%d]th package ...\r\n", i++);

            Status = EMAC_Transmit(emacIndex, (UINT8 *)MACFrame, sizeof(MACFrame));
            if (!Status) {
                EMAC_PRINT_0("ARP Tx fail\r\n");
            }

            Emac_SleepMS(200);

            fake_emac_isr(emacIndex);
        }

    return TRUE;
}


BOOLEAN
EMAC_RecvPkg_Test (
  UINT8 index
)
{
    UINT8  BufferRx[1600];
    UINTN  LengthRx = 1600;
    UINT8  result;
    UINT8  emacIndex = index;

    Emac_Memset(BufferRx, 0, sizeof(BufferRx));

    result = EMAC_Receive(emacIndex, 0, BufferRx, &LengthRx, NULL);
    if ( !result ) {
        EMAC_PRINT_0 ("Fail to recieve packet\r\n");
        return FALSE;
    }

    return TRUE;
}




#define ETH_ALEN 6
struct ethhdr {
	unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
	unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
	UINT16		h_proto;		/* packet type ID field	*/
} __attribute__((packed));

struct iphdr {
	UINT8	ihl_version;//Don't care little or big endian??
	UINT8	tos;
	UINT16	tot_len;
	UINT16	id;
	UINT16	frag_off;
	UINT8	ttl;
	UINT8	protocol;
	UINT16	check;
	UINT32	saddr;
	UINT32	daddr;
	/*The options start here. */
};

struct udphdr {
	UINT16	source;
	UINT16	dest;
	UINT16	len;
	UINT16	check;
};
//UINT8 MACADDR[ETH_ALEN];
#define DATALEN 30
#define MAC_IP_UDP (14+20+8)
#define TOTLENGTH 1600
STATIC UINT8 IPPackets[TOTLENGTH];//Hope the BSS area is large enough

void InitPacket(UINT8 *PacketBuf)
{
  //Ignores all security check, such as buf==null
  //Lazy way to update the mac
  UINT8* buf;
  UINT16* buf_type;
  UINT16 i;
  struct iphdr iph;
  struct udphdr udph;

  buf = PacketBuf;
  CopyMem(buf,MACFrame,ETH_ALEN*2);
  buf += ETH_ALEN*2;

  buf_type = (UINT16 *)buf;
  *buf_type = 0x0800; //Fixed IP type
  buf += sizeof(UINT16);

  //IP layer
  iph.ihl_version = (4<<4) | 5;
  iph.tos = 0;
  iph.tot_len = 20 + DATALEN; //(IP header = 20, UDP Header = 8, TCP header= 20)
  iph.id = 0;       //identifier
  iph.frag_off = 0; //no fragment
  iph.ttl = 32;
  iph.protocol = 17; //UDP=17, TCP=6??
  iph.saddr = 0x12345678;
  iph.daddr = 0x11223344;
  //how check sum works
  CopyMem(buf,&iph,20);
  buf += 20;

  //udp layer
  udph.source = 80;
  udph.dest = 80;
  udph.len = DATALEN - 8;
  CopyMem(buf,&udph,20);
  buf += 8;

  for (i=0; i<10; i++) {
    buf[i] = i;
  }
  buf += (DATALEN-10);
  testindex++;
  for (i=0; i<10; i++) {
    buf[i] = testindex;
  }
}

#define RSSTblSize 64
#define VMQTestQueue 3
#define VMQ_CNT 1
#define VMQ_RSS_init 0x10
static uint8 rssHashTbl[RSSTblSize];
static UINT8 isRssInit  = VMQ_RSS_init;
static UINT8 isVMQInit  = VMQ_RSS_init;

/**
 * @brief       wrapper for rss vmq packet sent and receive
 *              Only available for loopback test
 *
 * @param[in]     index       Mac device index
 * @param[in]     queue       Which queue is used
 * @param[in]     buf         Data going to send out
 * @param[out]    rxd         Rx description when packet received
 * @param[in out] LengthRx    Data length for sending, received data length when receiving
 *
 */
bool EmacSendRecv(
  UINT8  index,
  UINT8  queue,
  UINT8* buf,
  UINT8* rxd,
  UINTN  LengthRx
  )
{
  bool ret;
  UINTN Length;

  ret = false;
  Length = LengthRx;

  if (EFI_SUCCESS == EMAC_Transmit(index, buf, Length)) {
    ret = true;
    EMAC_PRINT_0("packet sent\r\n");
  }
  else {
      EMAC_PRINT_0("fail to send packet\r\n");
      return ret;
  }

  Emac_SleepMS(100);

  EMAC_PRINT_0("Waiting for the data received\r\n");

  buf = IPPackets;              //not good, should not use global variable
  Emac_Memset(buf,0,TOTLENGTH); //just lazy
  Length = TOTLENGTH;

  fake_emac_isr(index);

  if (EMAC_Receive(index, queue, buf, (UINTN*)&Length, (UINT8*)rxd)) {
    EMAC_PRINT_1("Received packet length is %d\r\n",Length);

    if (Length == (DATALEN+MAC_IP_UDP+4)) {//Rx will get more 4 bytes for ethernet tail
      //buf = IPPackets +DATALEN+MAC_IP_UDP-10;
      // for (i=0;i<10;i++) {               //dump data if you want
      //   EMAC_PRINT_1("%d",buf[i]);
      // }
      ret = true;
      EMAC_PRINT_0("\r\n");
    }
  }
  else {
      EMAC_PRINT_0 ("fail to recieve packet\r\n");
      ret = false;
  }

  return ret;
}


/**
 * @brief       wrapper for rss vmq packet sent and receive
 *
 * @param[in]   index       Mac device index
 * @param[in]   queue       Which queue is used
 * @param[out]   rrd        Rx description when packet received
 *
 */
bool EMAC_comm_rssvmq(
  UINT8 index,
  UINT8 queue,
  UINT8* rrd)
{
  UINT8*      buf;
  UINT32      i;

  UINTN Length = 0;

  EMAC_PRINT_0("RSS VMQ test started\r\n");
  Emac_Memset((void*)IPPackets,0,TOTLENGTH);

  buf = IPPackets;
  InitPacket(buf);

  // Perform loopback test with a generated frame
  Length = DATALEN+MAC_IP_UDP;
  if (EmacSendRecv(index,queue, buf,(UINT8*)rrd,Length)) {
    fake_emac_isr(index);
  } else {
    return FALSE;
  }

return TRUE;
}

bool EMAC_rss(UINT8 index)
{
  bool ret;
  uint16 i;
  EMAC_CFG    extraCfg    = {0};
  RRD_TYPE_A  curRrd      = {0};

  //update RSS related config information
  //send packets with different configuration TUP 4, check if packets are routed into different RSS queues
  extraCfg.isRssEn        = TRUE;
  extraCfg.rssHashType    = EMAC_RSS_IPV4;
  extraCfg.rssHashTblSize = RSSTblSize;
  extraCfg.rssHashTbl     = rssHashTbl;
  extraCfg.rssKey         =  NULL;      //default hash table will be used
  extraCfg.rxQueues       = EMAC_RXQ_MAX_RSS;

  for (i=0; i<64; i++) {
    rssHashTbl[i] = i%EMAC_RXQ_MAX_RSS;//Use fixed queue for test purpose
  }
  if (isRssInit != index) {
    EMAC_Init(index, 1000, TRUE, 1, (UINT8*)&extraCfg);//fixed loopback test configuration
    isRssInit = index;
    isVMQInit = VMQ_RSS_init;
  }

  curRrd.CPU_N = 6; //poison Rx desc for further verification
  //Need to figure out which queue should be used
  ret = EMAC_comm_rssvmq(index,0,(UINT8*)&curRrd);

  if( ret ) {
    EMAC_PRINT_2("Received Hash value=%d, Hash flag=%d\r\n",curRrd.RSS_HASH,curRrd.HASH_FLAG);
    if (EMAC_RSS_IPV4 != curRrd.HASH_FLAG)
      ret = FALSE;
  }
  return ret;
}

bool EMAC_VMQ(UINT8 index)
{
  bool ret;
  EMAC_CFG    extraCfg = {0};

  EMAC_VMQ_FLTR vmqFilter[VMQ_CNT];

  extraCfg.isVmqEn = TRUE;
  extraCfg.vmqFilterCnt = VMQ_CNT;
  //update first filter
  //send packets with different MAC address filter, check if packets are routed into different VMQ queues
  vmqFilter[0].vlan = 0;
  vmqFilter[0].vmqNum = VMQTestQueue;
  vmqFilter[0].isAddressCmpEn = TRUE;
  vmqFilter[0].isVlanCmpEn = FALSE;
  vmqFilter[0].addressLow32 = 0xFFFFFFFF;
  vmqFilter[0].addressHigh16= 0xFFFF;
  extraCfg.vmqFilter = vmqFilter;

  extraCfg.rxQueues = EMAC_RXQ_MAX_VMQ;
  if (isVMQInit != index) {
    EMAC_Init(index, 1000, TRUE, 1, (UINT8*)&extraCfg);//fixed loopback test configuration
    isVMQInit = index;
    isRssInit = VMQ_RSS_init;
  }
  ret = EMAC_comm_rssvmq(index,VMQTestQueue,NULL);

  return ret;

}
