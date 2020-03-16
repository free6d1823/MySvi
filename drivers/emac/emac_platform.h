#ifndef __EMAC_PLATFORM_H__
#define __EMAC_PLATFORM_H__

/**---------------------------------------------------------------------------
 * @file     emac_platform.h
 *
 * @brief    Header file to abstract platform specific differences
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
#include "hdts_shell.h"
//#include <Library/DebugLib.h>
//#include <Library/TimerLib.h>
#include <com_dtypes.h>
//#include <Library/MemoryAllocationLib.h>
//#include "DALStdErr.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *--------------------------------------------------------------------------*/

/* macro to denote parameters */
#define IN
#define OUT

//extern void shell_msg(char * format,...);


#define EMAC_DEBUG_ENABLE

#undef DEBUG
#define DEBUG(arg)

#ifdef EMAC_DEBUG_ENABLE
#define EMAC_PRINT_0(formatStr)                         shell_msg(formatStr)
#define EMAC_PRINT_1(formatStr, p1)                     shell_msg(formatStr, p1)
#define EMAC_PRINT_2(formatStr, p1, p2)                 shell_msg(formatStr, p1, p2)
#define EMAC_PRINT_3(formatStr, p1, p2, p3)             shell_msg(formatStr, p1, p2, p3)
#define EMAC_PRINT_4(formatStr, p1, p2, p3, p4)         shell_msg(formatStr, p1, p2, p3, p4)
#define EMAC_PRINT_5(formatStr, p1, p2, p3, p4, p5)     shell_msg(formatStr, p1, p2, p3, p4, p5)
#else
#define EMAC_PRINT_0(formatStr)
#define EMAC_PRINT_1(formatStr, p1)
#define EMAC_PRINT_2(formatStr, p1, p2)
#define EMAC_PRINT_3(formatStr, p1, p2, p3)
#define EMAC_PRINT_4(formatStr, p1, p2, p3, p4)
#define EMAC_PRINT_5(formatStr, p1, p2, p3, p4, p5)
#endif


/* EMAC Interrupt sources, switched by core */

#ifdef EMAC1_FOR_IMC

/*	EMAC core1 default interrupt source */
#define EMAC_CORE_INT_SRC           EMAC_CORE1_INT_SRC
/* SGMII core x interrupt source */
#define EMAC_CORE_SGMII_INT_SRC     EMAC_CORE1_SGMII_INT_SRC

#else /* !EMAC1_FOR_IMC */

/*	EMAC core1 default interrupt source */
#define EMAC_CORE_INT_SRC           EMAC_CORE0_INT_SRC
/* SGMII core x interrupt source */
#define EMAC_CORE_SGMII_INT_SRC     EMAC_CORE0_SGMII_INT_SRC

#endif /* EMAC1_FOR_IMC */

/* EMAC Core 0 interrupt sources */
#define EMAC_CORE0_INT_SRC          55
/* EMAC Core 1 interrupt sources */
#define EMAC_CORE1_INT_SRC          57

/* Buffer type for DMA */
typedef struct EMAC_BUFFER_STRUCT {
  uint8  *vaddr;   /* Virtual address */
  uint8  *paddr;   /* Physical address */
  uint32  size;    /* Size in bytes */
} EMAC_BUFFER;

/*----------------------------------------------------------------------------
 * Type Declarations
 *--------------------------------------------------------------------------*/

typedef void (*EMAC_ISR)(uint8 emacIndex, volatile void *user_data);

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 *--------------------------------------------------------------------------*/

/**
 * @brief		Register the ISR core passed.
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
);

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
);

/**
 * @brief           Allocate buffer
 *
 * @param[in,out]   bufData     Buffer data attributes
 * @param[in]       bufSize     Buffer size, in bytes
 * @param[in]       align       Buffer start address alignment, in bytes
 *
 * @return          TRUE if successful, else failed
 */
int Emac_AllocBuffer
(
  IN OUT EMAC_BUFFER *bufData,
  IN uint32 bufSize,
  IN uint16 align
);

/**
 * @brief           Free buffer
 *
 * @param[in]       bufData     Buffer data attributes
 */
void Emac_FreeBuffer
(
  IN EMAC_BUFFER *bufData
);

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
);

#endif /*  __EMAC_PLATFORM_H__  */

