#ifndef __EMAC_FRAMEWORK_H__
#define __EMAC_FRAMEWORK_H__
/**---------------------------------------------------------------------------
 * @file     emac_framework.h
 *
 * @brief    Header file for EMAC framework
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include "boot_comdef.h"
//#include "DALDeviceId.h"
#include "HALhwio_ext.h"

#include "emac_platform.h"
#include "emac_types.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *--------------------------------------------------------------------------*/

/* uintnt definition */
#ifndef uintnt
#define uintnt unsigned long
#endif

/* Maximum read cycles to wait for GCC registers to update */
#define EMAC_GCC_UPDATE_WAIT_CYCLES 300

/* Test console definitions */
#define EMAC_MAX_TEST_ARGUMENTS     16  /* Maximum number of arguments for test */
#define EMAC_MAX_TEST_RESULT_LEN    12  /* Maximum test result length, in dwords */

#define EMAC_HW_RESET_DELAY_MS      10  /* EMAC HW reset delay, milliseconds */

/* SGMII PHY interrupt sources */
#define EMAC_CORE0_SGMII_INT_SRC    286 /* SGMII core 0 interrupt source */
#define EMAC_CORE1_SGMII_INT_SRC    287 /* SGMII core 1 interrupt source */

/* EMAC WOL IRQ to RPM. Not supported on Trahira */
#define EMAC0_WOL_INT_SRC            297 /* EMAC WOL interrupt source */
#define EMAC1_WOL_INT_SRC            292 /* EMAC WOL interrupt source */

/* EMAC Internal SRAM , in bytes */
#define EMAC_INTER_SRAM_SIZE        (32 * 1024)

/* c_ready assertion timeout for SGMII PHY initialization, in milliseconds */
#define EMAC_C_READY_SIGNAL_TIMEOUT     2000

/* CDR align detect timeout for digital/serdes phy loopback modes, in  milliseconds */
#define EMAC_CDR_ALIGN_DET_TIMEOUT      1000

/* EPHY Device Addresses */
#ifdef HDTS_EMAC_MARVELLPHY
#define EMAC0_EPHY_ADDRESS               0x0    
#define EMAC1_EPHY_ADDRESS               0x1    
#else
#define EMAC0_EPHY_ADDRESS               0x4    /* QCA EPHY address is 4 on QCT SDP and REP boards */
#define EMAC1_EPHY_ADDRESS               0x5    /* QCA EPHY address is 5 on QCT SDP and REP boards */
#endif

/* EMAC Registers Addresses Prefix and Core Base */

#define EMAC_REG_PRE(reg)       I0_EMAC_##reg           /* Registers prefix */
#define PHY_REG_PRE(reg)        SGMII_PHY_L0_##reg      /* Phy register prefix */
#define QSERVER_REG_PRE(reg)    QSERVER_L0_##reg        /* QSERVER register prefix */

#define EMAC_REG_PRE1(reg)      I1_EMAC_##reg           /* Registers prefix */
#define PHY_REG_PRE1(reg)       SGMII_PHY_L1_##reg      /* Phy register prefix */
#define QSERVER_REG_PRE1(reg)   QSERVER_L1_##reg        /* QSERVER register prefix */


#define EMAC_CORE_BASE          EMAC_REG_PRE(REG_BASE)   /* Register base address */
#define EMAC_CORE_BASE_PHYS     EMAC_CORE_BASE           /* Physical base address */

/* Define if IEEE Std 1588 supported */
#define EMAC_1588_SUPPORTED 0

/* EMAC Register offset, from core base */
/** Macro to create register address offset */
#define EMAC_REG_OFF(regName) (HWIO_ADDR(regName) - EMAC_CORE_BASE)

/* PHY driver configuration */
typedef struct EMAC_PHY_CFG_STRUCT {
  uint32             speed;         /* Speed in MB: 10/100/1000 */
  EMAC_LB_MODE modeLoopback;        /* Loopback mode */
  boolean            isAutoNeg;     /* Enable/disable auto negotiation */
  boolean            isFullDuplex;  /* Duplex. TRUE = Full, FALSE = Half */
} EMAC_PHY_CFG;

/* System Clock definitions */
typedef enum EMAC_CLK_ENUM {
  EMAC_CLK_19_2_DIV_6 = 3200,       /* TCXO 19.2MHz clock divided by 6 */
  EMAC_CLK_25_DIV_8   = 3125,       /* 25MHz clock divided by 8 */
  EMAC_CLK_19_2_SAFE  = 19200,      /* 19.2MHz clock, safe configuration */
  EMAC_CLK_25         = 25000,      /* 25MHz clock */
  EMAC_CLK_125        = 125000      /* 125MHz clock */
} EMAC_CLK;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 *--------------------------------------------------------------------------*/

/**
 * @brief   Perform EMAC HW reset
 *          Note: EMAC HW reset drives SGMII phy reset as well
 */
void Emac_EmacHwReset(void);

/**
 * @brief   Reset the EMAC internal SRAM memory (set to 0's).
 */
void Emac_ResetInternalSRAM(uint8 emacIndex);

/**
 * @brief   Output the frequencies of EMAC clocks
 */
void Emac_OutputClocksFreq(void);

/**
 * @brief       Config GPIOs
 */
void Emac_ConfigGPIOs(void);

/**
 * @brief       Enable RX clock after drivers init
 */
void Emac_SetRxClockPostInitDriver(uint8 emacIndex);

/**
 * @brief           Register EMAC core ISR (for Apps0)
 *
 * @param[in]       isrCore     ISR function
 * @param[in,out]   userData    If non-null, user data
 *
 * @return          TRUE if successful, else failed
 */
boolean Emac_RegisterCoreIsr
(
  IN EMAC_ISR isrCore,
  IN void *userData
);

/**
 * @brief           Unregister EMAC core ISR (for Apps0)
 */
void Emac_UnregisterCoreIsr(void);


/**
 * @brief       Check driver instance corresponds to build option
 *
 * @param[in]   instance    Core instance to run test on
 */
int Emac_CheckDriverInst
(
  IN uint32 instance
);

/**
 * @brief       Safe drop-in replacement of memcpy
 *
 * @param[in]   dst     Destination address
 * @param[in]   src     Source address
 * @param[out]  size    Number of bytes to copy
 *
 */
void Emac_Memcpy
(
  IN void *dst,
  IN const void *src,
  IN uint32 size
);

/**
 * @brief       Safe drop-in replacement of memcmp
 *
 * @param[in]   buffer1     First  buffer to compare
 * @param[in]   buffer2     Second buffer to compare
 * @param[in]   count       Number of bytes to compare
 *
 * @retval      <0          buffer1 less than buffer2
 * @retval      0           buffer1 identical to buffer2
 * @retval      >0          buffer1 greater than buffer2
 */
int Emac_Memcmp
(
  IN const void *buffer1,
  IN const void *buffer2,
  IN uint32 count
);

/**
 * @brief       Safe drop-in replacement of memset
 *
 * @param[in]   dst     Destination address
 * @param[in]   val     Value to set for each byte
 * @param[out]  size    Number of bytes to set
 *
 */
void Emac_Memset
(
  IN OUT void *dst,
  IN int val,
  IN uint32 size
);

/**
 * @brief       Set clock frequencies using shared code GCC driver
 *
 * @param[in]   emacInst        EMAC instance
 * @param[in]   clkSystem       System clock to use
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_SetClocksFreq
(
  IN uint32 emacInst,
  IN EMAC_CLK clkSystem,
  IN uint32 speed,
  IN int modeLoopback
);

/**
 * @brief       Reset Phy HW
 *
 * @return      TRUE if successful, else failed
 */
void Emac_CleanupDrivers(uint8 Index);

#endif  /* __EMAC_FRAMEWORK_H__ */

