/**---------------------------------------------------------------------------
 * @file     emac_snp.h
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
#include "emac_types.h"

BOOLEAN EMAC_ProcessIsr () ;

VOID  *EMAC_GetTransmittedBuffer();

  /**
 * @brief       Reset the phy and ephy
 *
 * @return      TRUE if successful, else failed
 */
BOOLEAN EMAC_Init (
  UINT32        index,
  UINT32        speed,
  BOOLEAN       isFullDuplex,
  EMAC_LB_MODE  modeLoopback,
  UINT8*     extraCfg
);

/**
 * @brief       Transmit data
 *
 * @return      TRUE if successful, else failed
 */
EFI_STATUS EMAC_Transmit (
  IN  UINT8   emacIndex,
  IN  UINT8   *Buffer,
  IN  UINTN   BufferLength
);

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
  OUT     UINT8  *bufRxD_A
);

/**
 * @brief       Set MAC Address for the device
 *
 * @return      TRUE if successful, else failed
 */
BOOLEAN EMAC_SetMacAddr (
  IN UINT8 emacIndex,
  IN EFI_MAC_ADDRESS *addr
);

/**
 * @brief       Get MAC Address for the device
 *
 * @return      TRUE if successful, else failed
 */
BOOLEAN EMAC_GetMacAddr (
  IN UINT8 emacIndex,
  OUT EFI_MAC_ADDRESS *addr
);

/**
 * @brief       Cleanup phy, ephy and emac driver
 *
 */
VOID EMAC_Shutdown(
  IN UINT8 emacIndex,
  IN EFI_EVENT Event, 
  IN VOID* Ctx
);

/**
 * @brief       Get EMAC phy link
 *
 * @param[in]   addr     Gets the mac address
 */
BOOLEAN EMAC_isLinkUp (
 IN UINT8 phyIndex
);

/**
 * @brief       Get EMAC ephy autonegotiated speed/duplex
 *
 * @param[in]   speed     speed, either 10, 100, or 1000
 * @param[in]   duplex    duplex either full or half
 */
BOOLEAN EMAC_GetSpeedAndDuplex (
  UINT8 phyIndex,
  UINT32 *speed,
  BOOLEAN *isFullDuplex
);


BOOLEAN EMAC_Loopback_Test (
  UINT8 index
);

BOOLEAN EMAC_SendArp_Test (
  UINT8 index,
  UINT32 times 
);

BOOLEAN EMAC_RecvPkg_Test( 
  UINT8 index 
);


  /**
 * @brief       emac RSS & VMQ feature test
 *
 * @return      TRUE if successful, else failed
 */
bool EMAC_rss (
  UINT8        index
);
bool EMAC_VMQ (
  UINT8        index
);
bool EMAC_comm_rssvmq(
  UINT8 index,
  UINT8 queue,
  UINT8* extraCfg
);