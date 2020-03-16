/**---------------------------------------------------------------------------
 * @file     emac_ephy.c
 *
 * @brief    Implementation of EMAC external PHY driver
 *
 * Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include "boot_comdef.h"

#include "emac_framework.h"
#include "emac_ephy_drv_qca_ar8031.h"
#include "emac_ephy_drv_marvell_88e1111.h"
#include "emac_platform.h"
#include "emac_drv.h"

/*----------------------------------------------------------------------------
 * Extern defines
 *--------------------------------------------------------------------------*/

extern EMAC_DRV drv[2];
uint8 ephyAddr[2] = {EMAC0_EPHY_ADDRESS, EMAC1_EPHY_ADDRESS};

#define EMACEphyMaxAddr       32
#define EMACEphyRetryCount   100


/**
 * @brief       Write an external PHY register via MDIO
 *
 * @param[in]   devAddr   Device address
 * @param[in]   regAddr   Register address
 * @param[in]   regData   Register data to write
 *
 * @return  TRUE if successful, else failed
 */
int Emac_EphyWriteMiiReg
(
 IN uint8 ephyIndex,
 IN uint8 devAddr,
 IN uint8 regAddr,
 IN uint16 regData
)
{
#ifndef HDTS_EMAC_MARVELLPHY
  return Emac_EphyWriteMiiRegQcaAR8031(ephyIndex, devAddr, regAddr, regData);
#else
  return Emac_EphyWriteMiiReg_marvell_88e1111(ephyIndex, devAddr, regAddr, regData);
#endif
}

/**
 * @brief       Read an MII register via MDIO
 *
 * @param[in]   devAddr   Device address
 * @param[in]   regAddr   Register address
 * @param[out]  regData   Pointer to register data to be read
 *
 * @return  TRUE if successful, else failed
 */
int Emac_EphyReadMiiReg
(
 IN uint8 ephyIndex,
 IN uint8 devAddr,
 IN uint8 regAddr,
 IN OUT uint16 *regData
)
{  
#ifndef HDTS_EMAC_MARVELLPHY
  return Emac_EphyReadMiiRegQcaAR8031(ephyIndex, devAddr, regAddr, regData);
#else
  return Emac_EphyReadMiiReg_marvell_88e1111(ephyIndex, devAddr, regAddr, regData);
#endif
}

/**
 * @brief       Return true is link is up
 */
int Emac_EphyIsLinkUp
(
 IN uint8 ephyIndex,
 IN OUT boolean *isLinkUp
)
{
#ifndef HDTS_EMAC_MARVELLPHY
  return Emac_EphyIsLinkUpQcaAR8031(ephyIndex, isLinkUp);
#else
  return emac_ephy_isLinkUp_marvell_88e1111(ephyIndex, isLinkUp);
#endif
}

int GetValidEphyAddress 
(
  uint8 ephyIndex
) 
{
#if  0
  uint16 valReg2;
  uint32 id = 0;

  for (uint8 i = 0; i < EMACEphyMaxAddr; i++) {
    if (!Emac_EphyReadMiiReg(ephyIndex, i, 2, &valReg2)){
        continue;
    }

    id = valReg2 << 16;
    if (!Emac_EphyReadMiiReg(ephyIndex, i, 3, &valReg2)){
        continue;
    }

    id |= valReg2;
    if (id != 0xffffffff) {
        EMAC_PRINT_1("HXT: Ephy Address 0x%x\r\n", i);
        return i;
    }
  }
#endif
  if(ephyIndex == 0)
    return EMAC0_EPHY_ADDRESS;
  else
    return EMAC1_EPHY_ADDRESS;
}

/**
 * @brief   Perform EPHY HW reset
 */
void Emac_EphyHwReset
(
  IN uint8 ephyIndex
)
{
  uint16 valReg0 = 0;
  uint32 retryCount = EMACEphyRetryCount;

  EMAC_PRINT_1("Emac_EphyHwReset ephyIndex %d\r\n", ephyIndex);

  ephyAddr[ephyIndex] = GetValidEphyAddress(ephyIndex);

  Emac_EphyReadMiiReg(ephyIndex, ephyAddr[ephyIndex], 0, &valReg0);
  valReg0 |= 0x8000;
  Emac_EphyWriteMiiReg(ephyIndex, ephyAddr[ephyIndex], 0, valReg0);

  // wait for reset to be done
  valReg0 = 0x8000;

  while (valReg0 == 0x8000 && retryCount > 0) {
    Emac_EphyReadMiiReg(ephyIndex, ephyAddr[ephyIndex], 0, &valReg0);
    valReg0 &= 0x8000;
    retryCount--;
    Emac_SleepMS(10);
  }

  if(retryCount == 0)
    EMAC_PRINT_0("HXT: EPHY reset fail\r\n");
  else
    EMAC_PRINT_0("HXT: EPHY reset success\r\n");

  Emac_SleepMS(10);
}

/**
 * @brief      Setup Ephy Auto Polling
 *
 * @param[in]  devAddr          Device Address
 * @param[in]  isEnable         is Autopoll enabled
 *
 * @return     TRUE if successful, else failed.
 */
int Emac_SetEphyStatusAutoPoll
(
 IN uint8 ephyIndex,
 IN uint8 devAddr,
 IN boolean isEnable
)
{
  uint32 val = (TRUE == isEnable ? 1 : 0);

  /* Something changed? */
  if (isEnable == drv[ephyIndex].isAutoPoll) {
    return TRUE;
  }

  drv[ephyIndex].isLinkUp = FALSE; /* Mark link as down by default */

  if (TRUE == isEnable) {
    uint16 regData = 0;

    /* Read status reg 1 before starting auto-poll as work around (see HPG).
     * Set device address and start read
     */
    if(ephyIndex == 0){
        HWIO_OUTF(EMAC_REG_PRE(PHY_STS), PHY_ADDR, devAddr);
        HWIO_OUTF3(EMAC_REG_PRE(MDIO_CTRL),
            MDIO_RD_NWR, MDIO_REG_ADDR, MDIO_START,
            1,           1,             1);
    }
    else{
        HWIO_OUTF(EMAC_REG_PRE1(PHY_STS), PHY_ADDR, devAddr);
        HWIO_OUTF3(EMAC_REG_PRE1(MDIO_CTRL),
            MDIO_RD_NWR, MDIO_REG_ADDR, MDIO_START,
            1,           1,             1);
    }

    /* Wait and check if until done.
     * With slowest clock should take less than 0.17ms
     */
    Emac_SleepMS(100);

    if(ephyIndex == 0){
        if (0 != HWIO_INF(EMAC_REG_PRE(MDIO_CTRL), MDIO_BUSY)) {
          EMAC_PRINT_0("EPHY read failed to read MDIO_CTRL, MDIO busy\n");
          return FALSE;   /* Failure */
        }
    }
    else{
        if (0 != HWIO_INF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_BUSY)) {
          EMAC_PRINT_0("EPHY read failed to read MDIO_CTRL, MDIO busy\n");
          return FALSE;   /* Failure */
        }
    }

    /* Done, read data */
    if(ephyIndex == 0){
        regData = HWIO_INF(EMAC_REG_PRE(MDIO_CTRL), MDIO_DATA);
    }
    else{
        regData = HWIO_INF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_DATA);
    }

    /* Check bit 2 for link status */
    if (0 == (regData & 0x0004)) {
      drv[ephyIndex].isLinkUp = FALSE;
    }
    else {
      drv[ephyIndex].isLinkUp = TRUE;
    }
  }

  /* Enable/Disable auto-polling */
  if(ephyIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(MDIO_CTRL), MDIO_AP_EN, val);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_AP_EN, val);
  }

  /* Set status only after HW is enabled/disabled */
  drv[ephyIndex].isAutoPoll = isEnable;

  return TRUE;   /* Success */
}


/**
 * @brief       Get EPHY status read by HW auto-polling via MDIO. Function will
 *              fail if auto-polling is not enabled
 *
 * @param[out]  isLinkUp  will be set to TRUE if link is up, FALSE otherwise
 *
 * @return      TRUE if successful, else failed
 */
int Emac_IsLinkUp
(
 IN uint8 ephyIndex,
 IN OUT boolean *isLinkUp
)
{
  if (NULL == isLinkUp) {
    EMAC_PRINT_0("ivald param\r\n");
    return FALSE;   /* Failure */
  }

  if (TRUE != drv[ephyIndex].isAutoPoll) {
    EMAC_PRINT_0("auto-polling disabled\r\n");
    *isLinkUp = FALSE;
    return FALSE;   /* Failure */
  }

  *isLinkUp = drv[ephyIndex].isLinkUp;

  return TRUE;   /* Success */
}


/**
 * @brief       Wait until EMAC detects by HW auto-polling specific link status
 *              Function will fail if auto-polling is not enabled
 *
 * @param[in]   isLinkUp  Set TRUE to wait for link up, FALSE for link down
 * @param[in]   delayMS   Maximal delay to wait, milliseconds
 *
 * @return      TRUE if succeeded, else failed
 */

int Emac_WaitForAutoPollLinkStatus
(
 IN uint8 ephyIndex,
 IN boolean isLinkUp,
 IN uint32 delayMS
)
{
  boolean isLinkUpStatus;

  do {
    if (TRUE != Emac_IsLinkUp( ephyIndex, &isLinkUpStatus)) {
      EMAC_PRINT_0("Failed to get EMAC auto-polling link status\n");
      return FALSE;   /* Failure */
    }

    if (isLinkUpStatus == isLinkUp) {
      return TRUE;   /* Success */
    }

    Emac_SleepMS(1);
  } while (0 < (delayMS--));

  EMAC_PRINT_0("Timeout waiting for link status\n");

  return FALSE;   /* Failure */
}


/**
 * @brief       Initialize driver
 *
 * @param[in]   ephyIndex External PHY device index
 * @param[in]   cfg    External PHY Driver configuration
 *
 * @return  TRUE if successful, else failed.
 */
int Emac_EphyInit
(
 IN uint32 ephyIndex,
 IN const EMAC_EPHY_CFG *cfg
)
{
#ifndef HDTS_EMAC_MARVELLPHY
  return Emac_EphyInitQcaAR8031(ephyIndex, cfg);
#else
  return emac_ephy_init_marvell_88e1111(ephyIndex, cfg);
#endif
}

/**
 * @brief       Cleanup driver
 */
void Emac_EphyCleanup
(
 IN uint8 ephyIndex
)
{
#ifndef HDTS_EMAC_MARVELLPHY
  Emac_EphyCleanupQcaAR8031(ephyIndex);
#else
  emac_ephy_cleanup_marvell_88e1111(ephyIndex);
#endif
}

/**
 * @brief get autonegotiated speed/duplex from EPHY
 */
int Emac_EphyGetSpeedAndDuplex
(
 IN uint8 ephyIndex,
 OUT uint32  *speed,
 OUT boolean *isFullDuplex
 )
{
#ifndef HDTS_EMAC_MARVELLPHY
  return Emac_EphyGetSpeedAndDuplexQcaAR8031(ephyIndex, speed, isFullDuplex);
#else
  return emac_ephy_getSpeedAndDuplex_marvell_88e1111(ephyIndex, speed, isFullDuplex);
#endif
}

