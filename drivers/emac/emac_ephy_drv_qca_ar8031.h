#ifndef __EMAC_EPHY_DRV_QCA_AR8031_H__
#define __EMAC_EPHY_DRV_QCA_AR8031_H__
/**---------------------------------------------------------------------------
 * @file     emac_ephy_drv_qca_ar8031.h
 *
 * @brief    Interface of EMAC external PHY driver for QCA AR8031
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include "emac_ephy.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 *--------------------------------------------------------------------------*/

/**
 * @brief       Initialize driver
 *
 * @param[in]   ephyIndex  external phy index (0, 1, ...)
 * @param[in]   cfg    External PHY Driver configuration
 *
 * @return  TRUE if successful, else failed.
 */
int Emac_EphyInitQcaAR8031
(
  IN uint8 ephyIndex,
  IN const EMAC_EPHY_CFG *cfg
);

/**
 * @brief       Cleanup driver
 */
void Emac_EphyCleanupQcaAR8031
(
  IN uint8 ephyIndex
);

/**
 * @brief       Read an MII register via MDIO
 *
 * @param[in]   devAddr   Device address
 * @param[in]   regAddr   Register address
 * @param[out]  regData   Pointer to register data to be read
 *
 * @return  TRUE if successful, else failed
 */
int Emac_EphyReadMiiRegQcaAR8031
(
  IN uint8   ephyIndex,
  IN uint8   devAddr,
  IN uint8   regAddr,
  OUT uint16 *regData
);

/**
 * @brief       Write an external PHY register via MDIO
 *
 * @param[in]   devAddr   Device address
 * @param[in]   regAddr   Register address
 * @param[in]   regData   Register data to write
 *
 * @return  TRUE if successful, else failed
 */
int Emac_EphyWriteMiiRegQcaAR8031
(
  IN uint8 ephyIndex,
  IN uint8 devAddr,
  IN uint8 regAddr,
  IN uint16 regData
);

/**
 * @brief       Get real-time link status
 *
 * @param[out]  isLinkUp  will be set to TRUE if link is up, FALSE otherwise
 *
 * @return      TRUE if successful, else failed
 */
int Emac_EphyIsLinkUpQcaAR8031
(
  IN uint8 ephyIndex,
  OUT boolean *isLinkUp
);


/**
 * @brief       Get duplex and speed from ephy
 *
 * @param[out]  speed             10/100/1000 Mbps
 * @param[out]  isFullDuplex      set TRUE if is full duplex
 *
 * @return      TRUE if successful, else failed
 */
int Emac_EphyGetSpeedAndDuplexQcaAR8031 (
 IN uint8 ephyIndex,
 OUT uint32  *speed,
 OUT boolean *isFullDuplex
 );

/**
 * @brief   Perform EPHY HW reset
 */
void Emac_EphyHwReset
(
 IN uint8 ephyIndex
);

#endif  /* __EMAC_EPHY_DRV_QCA_AR8031_H__ */

