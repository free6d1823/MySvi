/**---------------------------------------------------------------------------
 * @file     emac_framework.c
 *
 * @brief    Implementation of EMAC framework services
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include "emac_platform.h"
#include "asm/mach/hal/msmhwiobase.h"
#include "emac_hwio_mapping.h"
#include "emac_phy_sgmii.h"
#include "emac_ephy.h"

/*----------------------------------------------------------------------------
 * Global Data Definitions
 *--------------------------------------------------------------------------*/
extern EMAC_ISR gEmacISRCore; /* EMAC default core ISR */

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 *--------------------------------------------------------------------------*/

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
  volatile uint32 wait_cycles = EMAC_GCC_UPDATE_WAIT_CYCLES;
  do {
    volatile uint32 regVal = in_dword((uintnt)regAddr);
    if (0 == (regVal & 0x1)) {
      return TRUE; /* Success */
    }
  } while (wait_cycles-- > 0);

  EMAC_PRINT_1("Clock register 0x%08X not updated\r\n", regAddr);
  return FALSE;
}

/**
 * @brief           EMAC core ISR trampoline: clear interrupt call user ISR
 *
 * @param[in]       intSource  The interrupt source
 * @param[in,out]   userData   If non-null, user data
 */
  static void Emac_IsrCoreTramp
(
 IN void* userData
 )
{
  if (NULL != gEmacISRCore) {
    gEmacISRCore(0, userData);
  }
}

/**
 * @brief           Register EMAC core ISR (for Apps0)
 *
 * @param[in]       isrCore     ISR function
 * @param[in,out]   userData    If non-null, user data
 *
 * @return          TRUE if successful, else failed
 */
boolean Emac_RegisterCoreIsr(EMAC_ISR isrCore, void *userData)
{
  /* update the core isr ptr */
  ((EMAC_DRV *)userData)->coreIsr = Emac_IsrCoreTramp;

  /* Check if already registered */
  if (NULL != gEmacISRCore) {
    EMAC_PRINT_0("Core ISR re-registration\r\n");
  }

  /* Set user ISR */
  gEmacISRCore = isrCore;
#if 0
  if( TRUE != Emac_PlatformRegisterCoreIsr(isrCore, userData)) {
    EMAC_PRINT_0("Core ISR registration failed \n");
    gEmacISRCore = NULL;
  }
#endif

  return TRUE;
}

/**
 * @brief           Unregister EMAC core ISR (for Apps0)
 */
void Emac_UnregisterCoreIsr(void)
{
  gEmacISRCore = NULL;
}

/**
 * @brief   Reset the EMAC internal SRAM memory (set to 0's).
 */
void Emac_ResetInternalSRAM(uint8 emacIndex)
{
  uint32 cnt;
  volatile uint64 *sram;

  if(emacIndex == 0)
    sram = (uint64 *) (HWIO_ADDR(EMAC_REG_PRE(EMAC_RAMn))(0));
  else
    sram = (uint64 *) (HWIO_ADDR(EMAC_REG_PRE1(EMAC_RAMn))(0));

  for (cnt = 0; cnt < (EMAC_INTER_SRAM_SIZE / sizeof (*sram)); cnt++) {
    sram[cnt] = 0;
  }
}



/**
 * @brief       Check driver instance corresponds to build option
 *
 * @param[in]   instance    Core instance to run test on
 */
  int Emac_CheckDriverInst
(
 IN uint32 instance
 )
{
  /* Check driver instance correspondes to build option */
#ifdef EMAC0_FOR_UEFI
  if (0 != instance)
  {
    EMAC_PRINT_1("Invalid instance: specified %u compiled 0\n", instance);
    return FALSE;
  }
#else /* !EMAC0_FOR_UEFI */
  if (1 != instance) {
    EMAC_PRINT_1("Invalid instance: specified %u compiled 1\n", instance);
    return FALSE;
  }
#endif /* EMAC_INST_0 */

  return TRUE;
}

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
 )
{
  uint8 *dst1 = (uint8 *) dst;
  const uint8 *src1 = (const uint8 *) src;

  while (size-- > 0) {
    *(dst1++) = *(src1++);
  }
}

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
 )
{
  const uint8 *buf1 = (const uint8 *) buffer1;
  const uint8 *buf2 = (const uint8 *) buffer2;

  while (count-- > 0) {
    if (*buf1 != *buf2) {
      return *buf1 - *buf2;
    }

    buf1++;
    buf2++;
  }

  return 0;
}

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
 IN void *dst,
 IN int val,
 IN uint32 size
 )
{
  uint8 *dst1 = (uint8 *) dst;

  while (size-- > 0) {
    *(dst1++) = (uint8) val;
  }
}

/**
 * @brief       Config GPIOs
 */
void Emac_ConfigGPIOs(void)
{
  /* Set MDIO GPIOs
   * GPIOs: 123, 124, 125, 126
   * Value = 0x1C7:
   *      GPIO_PULL    = 3 (PULL_UP)  bits[0:1]
   *      FUNC_SEL     = 1            bits[2:5]
   *      DRV_STRENGTH = 7            bits[6:8]
   */
  uint32 val = 0x1C7;

  // EMAC0
  HWIO_OUTI(TLMM_GPIO_CFGn, 75, val);
  HWIO_OUTI(TLMM_GPIO_CFGn, 77, val);
  // EMAC1
  HWIO_OUTI(TLMM_GPIO_CFGn, 76, val);
  HWIO_OUTI(TLMM_GPIO_CFGn, 78, val);
}

/**
 * @brief       Reset Phy HW
 *
 * @return      TRUE if successful, else failed
 */
void Emac_CleanupDrivers(uint8 Index)
{
  uint8 ephyIndex = Index;

  Emac_UnregisterCoreIsr();

  Emac_Cleanup(ephyIndex);

  Emac_PhyHwResetSgmii(ephyIndex);

  Emac_EphyCleanup(ephyIndex);  /* Clean external phy driver */
}

