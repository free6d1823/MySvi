#ifndef __EMAC_EPHY_H__
#define __EMAC_EPHY_H__
/**---------------------------------------------------------------------------
 * @file     emac_ephy.h
 *
 * @brief    Implementation of EMAC external PHY driver
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include "emac_framework.h"
#include "asm/mach/hal/msmhwiobase.h"
#include "emac_hwio_mapping.h"


/*----------------------------------------------------------------------------
 * Type Declarations
 *--------------------------------------------------------------------------*/
/**
 * Ethernet driver configuration
 */
typedef struct EMAC_EPHY_CFG_STRUCT 
{
  uint32             speed;             /* Speed in MB: 10/100/1000 */
  EMAC_LB_MODE modeLoopback;            /* Loopback mode */
  boolean            isAutoNeg;         /* Enable/disable auto negotiation */
  boolean            isFullDuplex;      /* Duplex. TRUE = Full, FALSE = Half */
} EMAC_EPHY_CFG;

/** Time out for receiving link up status from EPHY, in milliseconds */
#define EMAC_EPHY_LINK_TIMEOUT    100

/* Time taken for reset and init of EPHY */
#define EMAC_EPHY_LATENCY         200


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
int Emac_EphyReadMiiReg
(
 IN uint8 ephyIndex,
 IN uint8 devAddr,
 IN uint8 regAddr,
 IN OUT uint16 *regData
);

/**
 * @brief       Return true is link is up
 */
int Emac_EphyIsLinkUp
(
 IN uint8 ephyIndex,
 IN OUT boolean *isLinkUp
);

/**
 * @brief   Perform EPHY HW reset
 */
void Emac_EphyHwReset
(
 IN uint8 ephyIndex
);

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
 );

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
);

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
);


/**
 * @brief       Initialize driver
 *
 * @param[in]   cfg    External PHY Driver configuration
 *
 * @return  TRUE if successful, else failed.
 */
int Emac_EphyInit
(
 IN uint32 ephyIndex,
 IN const EMAC_EPHY_CFG *cfg
);


/**
 * @brief       Cleanup driver
 */
void Emac_EphyCleanup
(
 IN uint8 ephyIndex
);

/**
 * @brief       Get speed and duplex from Ephy
 */
int Emac_EphyGetSpeedAndDuplex
(
 IN uint8 ephyIndex,
 OUT uint32  *speed,
 OUT boolean *isFullDuplex
);

#endif

