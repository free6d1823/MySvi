#ifndef __EMAC_PHY_SGMII_H__
#define __EMAC_PHY_SGMII_H__

/**---------------------------------------------------------------------------
 * @file     emac_phy_sgmii.h
 *
 * @brief    Routines for ephy reset, setup and cleanup
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Preprocessor defines
 *--------------------------------------------------------------------------*/

/* Time taken for reset and init of EPHY */
#define EMAC_PHY_LATENCY         200

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include "emac_drv.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 *--------------------------------------------------------------------------*/

/**
 * @brief       Reset Phy HW in SGMII mode
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyHwResetSgmii
(
  IN uint8 phyIndex
);

/**
 * @brief       Initialize Phy HW in SGMII mode
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyHwInitSgmii
(
  IN uint8 phyIndex,
  IN const EMAC_PHY_CFG *cfg
);


/**
 * @brief       Phy HW reset
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyHwReset
(
  IN uint8 phyIndex
);

/**
 * @brief       Initialize the phy
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyHwInit
(
  IN uint8 phyIndex,
  IN const EMAC_PHY_CFG *cfg
);


/**
 * @brief       Check if Link is up
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_PhyIsLinkUpSgmii
(
  IN uint8 phyIndex,
  IN OUT boolean *isLinkUp
);

#endif /* __EMAC_PHY_SGMII_H__ */

