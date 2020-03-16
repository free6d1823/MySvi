/**---------------------------------------------------------------------------
 * @file     emac_platform.c
 *
 * @brief    Platform specific helper functions for emac.
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * include files
 *--------------------------------------------------------------------------*/

#include "stdbool.h"
#include "emac_platform.h"
#include "emac_drv.h"

#include "busywait.h"
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include "hdts_dmm.h"

/*----------------------------------------------------------------------------
 * Externs from emac driver
 *--------------------------------------------------------------------------*/

extern EMAC_ISR               gEmacISRCore;
extern EMAC_DRV               drv[2];

#define XBL_CORE_IMEM_EMAC_BASE       0xFF70000000
#define XBL_CORE_IMEM_EMAC_BASE_SIZE  0x20000

/* Memory counter for IMC dynamic memory allocations */
int Emac_mem_counter = 0;

/**
 * @brief           Allocate buffer
 *
 * @param[in,out]   bufData     Buffer data attributes
 * @param[in]       bufSize     Buffer size, in bytes
 * @param[in]       align       Buffer start address alignment, in bytes
 *
 * @return          TRUE if successful, else failed
 */
#if 0
int Emac_AllocBuffer
(
 IN OUT EMAC_BUFFER *bufData,
 IN uint32 bufSize,
 IN uint16 align
 )
{
  void *pMem;

  pMem = dmalloc((size_t) bufSize);
  if(pMem == NULL)
  {
    return -1;
  }

  bufData->paddr = (uint8  *)pMem;
  bufData->vaddr = (uint8  *)pMem;
  bufData->size = bufSize;

  EMAC_PRINT_2("AllocBuffer: pMem 0x%x, size %d\r\n", pMem, bufSize);

  return 0;
}
#endif

int Emac_AllocBuffer
(
 IN OUT EMAC_BUFFER *bufData,
 IN uint32 bufSize,
 IN uint16 align
 )
{
  int  nErr;
  UINT64 ptr = 0;

  ptr = (UINT64)(XBL_CORE_IMEM_EMAC_BASE + Emac_mem_counter);
  if( (ptr + bufSize) < (XBL_CORE_IMEM_EMAC_BASE + XBL_CORE_IMEM_EMAC_BASE_SIZE)) {
    Emac_mem_counter += bufSize;

    bufData->vaddr = (UINT8 *)ptr;
    bufData->paddr = (UINT8 *)ptr;
    bufData->size = bufSize;
    nErr = 0;
    Emac_Memset(bufData->vaddr, 0, bufSize);
    //EMAC_PRINT_2("AllocBuffer: ptr 0x%x, size %d\r\n", ptr, bufSize);
  }
  else {
    ptr = 0;
    nErr = -1;
    EMAC_PRINT_0("AllocBuffer fail!!!\r\n");
  }

  return nErr;
}


/**
 * @brief           Free buffer
 *
 * @param[in]       bufData     Buffer data attributes
 */
#if 0
void Emac_FreeBuffer
(
 IN EMAC_BUFFER *bufData
)
{
  dfree((void *)bufData->paddr);
  EMAC_PRINT_1("FreeBuffer: pMem 0x%x\r\n", bufData->paddr);
}
#endif

void Emac_FreeBuffer
(
 IN EMAC_BUFFER *bufData
)
{
   /* set the ring to 0 */
  Emac_Memset(bufData->vaddr, 0, bufData->size);
  //EMAC_PRINT_1("FreeBuffer: addr 0x%x\r\n", bufData->paddr);
  /* decrement the memory counter */
  Emac_mem_counter -= bufData->size;
}


/**
 * @brief		Register the core isr that is passed
 *
 * @param[in]   isrCore		isr to register
 * @param[in]   userData	userdata that will be passed on to the interrupt
 *
 * @return      TRUE if successful, else failed.
 */
int Emac_PlatformRegisterCoreIsr
(
 IN EMAC_ISR isrCore,
 IN void *userData
 )
{
  return TRUE;
}

/**
 * @brief		Un Register the ISR core passed.
 *
 * @param[in]   userData	userdata that will be passed on
 *
 * @return      none
 */
void Emac_PlatformUnregisterCoreIsr
(
 IN void *drv
 )
{
  return;
}


/**
 * @brief		Support sleeping for specified number of Milli seconds
 *
 * @param[in]   sleepPeriod in Micor seconds to sleep
 *
 * @return      none
 */
void Emac_SleepMS
(
 IN uint32 sleepPeriod
 )
{
  udelay(sleepPeriod * 1000);
}
