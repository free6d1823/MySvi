#ifndef _EMAC_EPHY_DRV_MARVELL_88E1111_H_
#define _EMAC_EPHY_DRV_MARVELL_88E1111_H_
/**---------------------------------------------------------------------------
 * @file     emac_ephy_drv_marvell_88e1111.h
 *
 * @brief    Interface of EMAC external PHY driver for Marvell 88E1111
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
 * Preprocessor Definitions and Constants
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 *--------------------------------------------------------------------------*/

/**
 * @brief       Initialize driver
 *
 * @param[in]   cfg    External PHY Driver configuration
 *
 * @return      TRUE if successful, else failed.
 */
int emac_ephy_init_marvell_88e1111
(
    uint8 ephyIndex, 
    const EMAC_EPHY_CFG *cfg
);

/**
 * @brief       Cleanup driver
 */
void emac_ephy_cleanup_marvell_88e1111
(
    uint8 ephyIndex
);

/**
 * @brief       Read an MII register via MDIO
 *
 * @param[in]   devAddr   Device address
 * @param[in]   regAddr   Register address
 * @param[out]  regData   Pointer to register data to be read
 *
 * @return      TRUE if successful, else failed
 */
int Emac_EphyReadMiiReg_marvell_88e1111
(
    uint8   ephyIndex,
    uint8   devAddr,
    uint8   regAddr,
    uint16 *regData
);

/**
 * @brief       Write an external PHY register via MDIO
 *
 * @param[in]   devAddr   Device address
 * @param[in]   regAddr   Register address
 * @param[in]   regData   Register data to write
 *
 * @return      TRUE if successful, else failed
 */
int Emac_EphyWriteMiiReg_marvell_88e1111
(
    uint8  ephyIndex,
    uint8  devAddr,
    uint8  regAddr,
    uint16 regData
);

/**
 * @brief       Get real-time link status
 *
 * @param[out]  isLinkUp  will be set to TRUE if link is up, FALSE otherwise
 *
 * @return      TRUE if successful, else failed
 */
int emac_ephy_isLinkUp_marvell_88e1111
(
    uint8  ephyIndex,
    boolean *isLinkUp
);

/**
 * @brief       Get EPHY resolved speed and duplex
 *
 * @param[out]  speed           EPHY resolved speed in Mbps (10/100/1000)
 * @param[out]  isFullDuplex    TRUE if resolved full-duplex, else FALSE
 *
 * @return      TRUE if link is up and speed is resolved, else failed
 */
int emac_ephy_getSpeedAndDuplex_marvell_88e1111
(
    uint8  ephyIndex,
    uint32  *speed,
    boolean *isFullDuplex
);

/**
 * @brief       Set EPHY to transmit TP_IDL pattern
 *
 * @param[in]   speed           Speed in MB: 10/100/1000
 * @param[in]   isDataRandom    Indicates if pattern of random or constant data
 *
 * @return  TRUE if pattern configuration succeeded, else failed
 */
int emac_ephy_setTpIdlePattern_marvell_88e1111
(
    uint8  ephyIndex,
    uint32 speed, 
    boolean isDataRandom
);


#endif  /* _EMAC_EPHY_DRV_MARVELL_88E1111_H_ */
