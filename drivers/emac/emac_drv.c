/**---------------------------------------------------------------------------
 * @file     emac_drv.c
 *
 * @brief    Core emac driver routines
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include <stdio.h>
#include <Uefi.h>
#include <string.h>
 #include <Library/BaseLib.h>

#include "emac_drv.h"
#include "asm/mach/hal/msmhwiobase.h"
#include "emac_hwio_mapping.h"
#include "emac_phy_sgmii.h"
#include "emac_ephy.h"
#include "emac_platform.h"


#ifdef EMAC1_FOR_IMC
#include "pm_err_flags.h"
#include "pm_clk.h"

#else

extern EFI_GUID gSharedVariablesPartitionGuid;

#endif

/*----------------------------------------------------------------------------
 * Global Data Definitions
 *--------------------------------------------------------------------------*/

/* EMAC driver configuration struct */
EMAC_DRV drv[2]  = {{0}, {0}};

#ifdef EMAC1_FOR_IMC

/* Memory counter for IMC dynamic memory allocations */
//int Emac_mem_counter = 0;

/* Notifier to dispatch when link is up */
EMAC_UP_NOTIFIER    gEmacUpNtfy;

/* Callback to dispatch when there is a packet ready */
EMAC_READ_CB        gEmacRdCbk;

#endif /*EMAC1_FOR_IMC*/

EMAC_ISR gEmacISRCore = NULL;

/**
 * @brief       Perform EMAC SW reset
 *
 * @return      TRUE if successful, else failed.
 */
int Emac_SwReset
(
  uint8 emacIndex
)
{
  int32 resetTo = EMAC_SW_RESET_TIMEOUT;

  /* Set EMAC soft reset, poll until auto-cleared */
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(DMA_MAS_CTRL), SOFT_RST, 0x1);
  else
    HWIO_OUTF(EMAC_REG_PRE1(DMA_MAS_CTRL), SOFT_RST, 0x1);

  do {
    if(emacIndex == 0){
        if (0x0 == HWIO_INF(EMAC_REG_PRE(DMA_MAS_CTRL), SOFT_RST)) {
          return TRUE;
        }
    }
    else{
        if (0x0 == HWIO_INF(EMAC_REG_PRE1(DMA_MAS_CTRL), SOFT_RST)) {
          return TRUE;
        }
    }

    Emac_SleepMS(1);
  } while (0 < --resetTo);

  return FALSE;
}

void Emac_GetMacAddr
(
 IN uint8 emacIndex,
 IN OUT EMAC_ADDR *addr
)
{
  uint64 addrHi;
  uint64 addrLow;

  /* Read MAC address registers */
  if(emacIndex == 0){
      addrHi  = HWIO_IN(EMAC_REG_PRE(MAC_STA_ADDR1));
      addrLow = HWIO_IN(EMAC_REG_PRE(MAC_STA_ADDR0));
  }
  else{
      addrHi  = HWIO_IN(EMAC_REG_PRE1(MAC_STA_ADDR1));
      addrLow = HWIO_IN(EMAC_REG_PRE1(MAC_STA_ADDR0));
  }

  /* Set address to be returned */
  (*addr)[0] = (addrHi >> 8) & 0xFF;
  (*addr)[1] = addrHi & 0xFF;
  (*addr)[2] = (addrLow >> 24) & 0xFF;
  (*addr)[3] = (addrLow >> 16) & 0xFF;
  (*addr)[4] = (addrLow >> 8) & 0xFF;
  (*addr)[5] = addrLow & 0xFF;

}

/**
 * @brief       Set MAC address
 *
 * @param[in]   addr     MAC address to set
 */
void Emac_SetMacAddr
(
 IN uint8 emacIndex,
 IN OUT EMAC_ADDR *addr
 )
{
  uint64 addrHi;
  uint64 addrLow;

#ifdef EMAC1_FOR_IMC
  // For IMC, we need to always read the MAC address from the fuses.
  // For UEFI, we can get it from the UEFI variable
  addrHi  =  HWIO_ADDR(QFPROM_RAW_SPARE_REG29_ROWn_MSB)(3);
  addrLow =  HWIO_ADDR(QFPROM_RAW_SPARE_REG29_ROWn_LSB)(3);

  /* Prepare MSB 2 bytes and LSB 4 bytes */
  *((uint8 *)addr + 0) = (*(uint32 *)(uint64)addrHi >> 8) & 0xFF;
  *((uint8 *)addr + 1) = *(uint32 *)(uint64)addrHi & 0xFF;
  *((uint8 *)addr + 2) = (*(uint32 *)(uint64)addrLow >> 24) & 0xFF;
  *((uint8 *)addr + 3) = (*(uint32 *)(uint64)addrLow >> 16) & 0xFF;
  *((uint8 *)addr + 4) = (*(uint32 *)(uint64)addrLow >> 8) & 0xFF;
  *((uint8 *)addr + 5) = *(uint32 *)(uint64)addrLow & 0xFF;
#endif

  /* Prepare MSB 2 bytes and LSB 4 bytes */
  addrHi  = ((*addr)[0] << 8) | (*addr)[1];
  addrLow = ((*addr)[2] << 24) | ((*addr)[3] << 16) | ((*addr)[4] << 8) | (*addr)[5];

  /* Write MAC address registers */
  if(emacIndex == 0){
      HWIO_OUT(EMAC_REG_PRE(MAC_STA_ADDR1), addrHi);
      HWIO_OUT(EMAC_REG_PRE(MAC_STA_ADDR0), addrLow);
  }
  else{
      HWIO_OUT(EMAC_REG_PRE1(MAC_STA_ADDR1), addrHi);
      HWIO_OUT(EMAC_REG_PRE1(MAC_STA_ADDR0), addrLow);
  }
}


/**
 * @brief       Initialize and set TPD rings
 *
 * @param[in]   cfg     Driver configuration
 *
 * @return      TRUE if successful, else failed
 */
int Emac_InitTxRings
(
 IN uint8 emacIndex,
 IN const EMAC_CFG *cfg
)
{
  uint32 val, cnt;
  uint32 sizeAllocRingTPD = 0; /* Size to allocate, in bytes */

  /* Set number of RX queues to 1 (default) if no value specified */
  if (0 == cfg->txQueues) {
    drv[emacIndex].txQueuesNum = 1;
  }
  else if (cfg->txQueues > EMAC_TXQ_NUM) {
    EMAC_PRINT_2("Invalid TX queue number %u, max %u\n",
        cfg->txQueues, EMAC_TXQ_NUM);
    return FALSE;   /* Failure */
  }
  else {
    drv[emacIndex].txQueuesNum = cfg->txQueues;
  }

  /* Set TPD ring size to default if no value specified */
  if (0 == cfg->txRingSize) {
    drv[emacIndex].countTPD = EMAC_TX_RING_SIZE;
  }
  else {
    /* Check specified value */
    if ((cfg->txRingSize < EMAC_MIN_TX_RING_SIZE) ||
        (cfg->txRingSize > EMAC_MAX_TX_RING_SIZE)) {
      EMAC_PRINT_3("Illegal TX ring size %u (min %u, max %u)\n",
          cfg->txRingSize, EMAC_MIN_TX_RING_SIZE,
          EMAC_MAX_TX_RING_SIZE);
      return FALSE;   /* Failure */
    }

    /* Set specified value */
    drv[emacIndex].countTPD = cfg->txRingSize;
  }

  for (cnt = 0; cnt < drv[emacIndex].txQueuesNum; cnt++) {
    if (0 == cfg->txScratchCnt)
    {
      drv[emacIndex].tpdType = EMAC_TPD_0_SCRATCH;
      drv[emacIndex].tpdSize = sizeof(TPD);
      drv[emacIndex].tpdScratchSize = 0;
      val = 0x0;
    }
    else if (2 == cfg->txScratchCnt) {
      drv[emacIndex].tpdType = EMAC_TPD_2_SCRATCH;
      drv[emacIndex].tpdSize = sizeof(TPD_SCRATCH_2);
      drv[emacIndex].tpdScratchSize = 2;
      val = 0x1;
    }
    else if (4 == cfg->txScratchCnt) {
      drv[emacIndex].tpdType = EMAC_TPD_4_SCRATCH;
      drv[emacIndex].tpdSize = sizeof(TPD_SCRATCH_4);
      drv[emacIndex].tpdScratchSize = 4;
      val = 0x2;
    }
    else {
      EMAC_PRINT_0("Invalid TPD type\n");
      return FALSE;   /* Failure */
    }

    /* Set scratchpad option */
    if(emacIndex == 0)
      HWIO_OUTF(EMAC_REG_PRE(EMAC_WRAPPER_CSR1), TPD_SCRATCH_NUM, val);
    else
      HWIO_OUTF(EMAC_REG_PRE1(EMAC_WRAPPER_CSR1), TPD_SCRATCH_NUM, val);

    /* Calculate TPD ring size and allocate ring */
    sizeAllocRingTPD = drv[emacIndex].countTPD * drv[emacIndex].tpdSize;
    if ((0 != Emac_AllocBuffer(&(drv[emacIndex].ringTPD[cnt]), sizeAllocRingTPD,
            EMAC_BUF_ALIGN_MIN))) {
      EMAC_PRINT_1("Failed to allocate TPD ring no %u\n", cnt);
      return FALSE;   /* Failure */
    }
  }

  /* Allocating TPD buffers to store the packets sent */
  for(cnt = 0; cnt < drv[emacIndex].countTPD; cnt++) {
    if(0 != Emac_AllocBuffer(&drv[emacIndex].tpdbuffersInt[cnt], EMAC_RX_BUF_SIZE,
          EMAC_BUF_ALIGN_MIN)) {
      EMAC_PRINT_1("Failed to allocate tpd buffer %d\n", cnt);
      return FALSE;   /* Failure */
    }
    drv[emacIndex].tpdbuffersInt[cnt].size = 0;
  }

  /* Set parameters shared by all TX rings */
#ifdef EMAC1_FOR_IMC
  HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_1),  0x0);          /* TPD ring base 32 MSBits */
#else
  if(emacIndex == 0)
    HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_1), (uint32)((uint64)drv[emacIndex].ringTPD[0].paddr >> 32)); /* TPD ring base 32 MSBits */
  else
    HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_1), (uint32)((uint64)drv[emacIndex].ringTPD[0].paddr >> 32)); /* TPD ring base 32 MSBits */
#endif

  if(emacIndex == 0){
      HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_9),  drv[emacIndex].countTPD); /* TPD ring size in descriptors */
      HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_11), 0x0);          /* TX data 18 MSBits */
  }
  else{
      HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_9),  drv[emacIndex].countTPD); /* TPD ring size in descriptors */
      HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_11), 0x0);          /* TX data 18 MSBits */
  }

  /* Set TPD rings base addresses - 32 LSBits */
  switch (drv[emacIndex].txQueuesNum) {
    case 5: /* Ring #4 */
      if(emacIndex == 0)
        HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_7), (uint32)(uint64)drv[emacIndex].ringTPD[4].paddr);
      else
        HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_7), (uint32)(uint64)drv[emacIndex].ringTPD[4].paddr);
      /* FALL-THROUGH */
    case 4: /* Ring #3 */
      if(emacIndex == 0)
        HWIO_OUT(EMAC_REG_PRE(H3TPD_BASE_ADDR_LO), (uint32)(uint64)drv[emacIndex].ringTPD[3].paddr);
      else
        HWIO_OUT(EMAC_REG_PRE1(H3TPD_BASE_ADDR_LO), (uint32)(uint64)drv[emacIndex].ringTPD[3].paddr);
      /* FALL-THROUGH */
    case 3: /* Ring #2 */
      if(emacIndex == 0)
        HWIO_OUT(EMAC_REG_PRE(H2TPD_BASE_ADDR_LO), (uint32)(uint64)drv[emacIndex].ringTPD[2].paddr);
      else
        HWIO_OUT(EMAC_REG_PRE1(H2TPD_BASE_ADDR_LO), (uint32)(uint64)drv[emacIndex].ringTPD[2].paddr);
      /* FALL-THROUGH */
    case 2: /* Ring #1 */
      if(emacIndex == 0)
        HWIO_OUT(EMAC_REG_PRE(H1TPD_BASE_ADDR_LO), (uint32)(uint64)drv[emacIndex].ringTPD[1].paddr);
      else
        HWIO_OUT(EMAC_REG_PRE1(H1TPD_BASE_ADDR_LO), (uint32)(uint64)drv[emacIndex].ringTPD[1].paddr);
      /* FALL-THROUGH */
    case 1: /* Ring #0 */
      if(emacIndex == 0)
        HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_8), (uint32)(uint64)drv[emacIndex].ringTPD[0].paddr);
      else
        HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_8), (uint32)(uint64)drv[emacIndex].ringTPD[0].paddr);
      break;
    default:
      /* Number of queues checked above, so should not reach here */
      break;
  }

  return TRUE;   /* Success */
}

/**
 * @brief       Initialize and set RFD and RRD rings
 *
 * @param[in]   cfg     Driver configuration
 *
 * @return      TRUE if successful, else failed
 */
static int Emac_InitRxRings
(
 IN uint8 emacIndex,
 IN const EMAC_CFG *cfg
)
{
  uint32 cnt,cntQ,index, val, val2, offsetTypeA;

  /* Set number of RX queues to 1 (default) if no value specified */
  if (0 == cfg->rxQueues) {
    drv[emacIndex].rxQueuesNum = 1;
  }
  else {
    drv[emacIndex].rxQueuesNum = cfg->rxQueues;
  }

  /* Check for valid number of RX queues */
  if ((TRUE == cfg->isRssEn) && (EMAC_RXQ_MAX_RSS < drv[emacIndex].rxQueuesNum)) {
    EMAC_PRINT_2("Invalid RSS RX queues number %u, max %u\r\n",
        drv[emacIndex].rxQueuesNum, EMAC_RXQ_MAX_RSS);
    return FALSE;   /* Failure */
  }
  else if ((TRUE == cfg->isVmqEn) && (EMAC_RXQ_MAX_VMQ < drv[emacIndex].rxQueuesNum)) {
    EMAC_PRINT_2("Invalid VMQ RX queues number %u, max %u\r\n",
        drv[emacIndex].rxQueuesNum, EMAC_RXQ_MAX_VMQ);
    return FALSE;   /* Failure */
  }
  else if ((FALSE == cfg->isRssEn) && (FALSE == cfg->isVmqEn) &&
      (1 < drv[emacIndex].rxQueuesNum)) {
    EMAC_PRINT_1("Invalid RX queues number %u, max 1 (no RSS/VMQ)\r\n",
        drv[emacIndex].rxQueuesNum);
    return FALSE;   /* Failure */
  }

  /* Set RFD ring to default size if no value specified.
   * (Note that RRD size in descriptors equals RFD size in descriptors)
   */
  if (0 == cfg->rxRingSize) {
    drv[emacIndex].countRFD = EMAC_RX_RING_SIZE;
  }
  else {
    drv[emacIndex].countRFD = cfg->rxRingSize;
  }

  /* Check specified value */
  if ((EMAC_MIN_RX_RING_SIZE > drv[emacIndex].countRFD) ||
      (EMAC_MAX_RX_RING_SIZE < drv[emacIndex].countRFD)) {
    EMAC_PRINT_3("Illegal RX ring size %u (min %u, max %u)\r\n",
        cfg->rxRingSize, EMAC_MIN_RX_RING_SIZE,
        EMAC_MAX_RX_RING_SIZE);
    return FALSE;   /* Failure */
  }

  /* Verify correct RX buffer size */
  if ((0 == cfg->sizeBufRX) ||
      (0 != (cfg->sizeBufRX % EMAC_BUF_ALIGN_MIN))) {
    EMAC_PRINT_2("Invalid RX buffer size %u (should be multiple of %u)\n",
        cfg->sizeBufRX, EMAC_BUF_ALIGN_MIN);
    return FALSE;   /* Failure */
  }

  drv[emacIndex].sizeBufRX = cfg->sizeBufRX;

  /* Initialize RRD type definitions and RX rings */
  if ((FALSE == cfg->isRxTsEn) && (0 == cfg->rxScratchCnt)) {
    drv[emacIndex].rrdType = EMAC_RRD_0_TS_0_SCRATCH;
    drv[emacIndex].rrdSize = sizeof(RRD_TYPE_A);
    offsetTypeA = 0; /* Type A is contained within itself from the start */
    val  = 0x0;
    val2 = 0x0;
  }
  else if ((FALSE == cfg->isRxTsEn) && (2 == cfg->rxScratchCnt)) {
    drv[emacIndex].rrdType = EMAC_RRD_0_TS_2_SCRATCH;
    drv[emacIndex].rrdSize = sizeof(RRD_TYPE_B);
    offsetTypeA = FPOS(RRD_TYPE_B, TypeA);
    val  = 0x0;
    val2 = 0x1;
  }
  else if ((FALSE == cfg->isRxTsEn) && (4 == cfg->rxScratchCnt)) {
    drv[emacIndex].rrdType = EMAC_RRD_0_TS_4_SCRATCH;
    drv[emacIndex].rrdSize = sizeof(RRD_TYPE_C);
    offsetTypeA = FPOS(RRD_TYPE_C, TypeA);
    val  = 0x0;
    val2 = 0x2;
  }
  else if ((TRUE == cfg->isRxTsEn) && (0 == cfg->rxScratchCnt)) {
    drv[emacIndex].rrdType = EMAC_RRD_1_TS_0_SCRATCH;
    drv[emacIndex].rrdSize = sizeof(RRD_TYPE_D);
    offsetTypeA = FPOS(RRD_TYPE_D, TypeA);
    val  = 0x1;
    val2 = 0x0;
  }
  else if ((TRUE == cfg->isRxTsEn) && (2 == cfg->rxScratchCnt)) {
    drv[emacIndex].rrdType = EMAC_RRD_1_TS_2_SCRATCH;
    drv[emacIndex].rrdSize = sizeof(RRD_TYPE_E);
    offsetTypeA = FPOS(RRD_TYPE_E, TypeB) + FPOS(RRD_TYPE_B, TypeA);
    val  = 0x1;
    val2 = 0x1;
  }
  else if ((TRUE == cfg->isRxTsEn) && (4 == cfg->rxScratchCnt)) {
    drv[emacIndex].rrdType = EMAC_RRD_1_TS_4_SCRATCH;
    drv[emacIndex].rrdSize = sizeof(RRD_TYPE_F);
    offsetTypeA = FPOS(RRD_TYPE_F, TypeC) + FPOS(RRD_TYPE_C, TypeA);
    val  = 0x1;
    val2 = 0x2;
  }
  else {
    EMAC_PRINT_0("Invalid RRD type\r\n");
    return FALSE;   /* Failure */
  }

  /* Set timestamp and scratchpad options */
  if(emacIndex == 0)
      HWIO_OUTF2(EMAC_REG_PRE(EMAC_WRAPPER_CSR1),
          ENABLE_RRD_TIMESTAMP, RRD_SCRATCH_NUM,
          val,                  val2);
  else
      HWIO_OUTF2(EMAC_REG_PRE1(EMAC_WRAPPER_CSR1),
          ENABLE_RRD_TIMESTAMP, RRD_SCRATCH_NUM,
          val,                  val2);

  /* Initialize RX rings (RRD and RFD) */
  for (cnt = 0; cnt < drv[emacIndex].rxQueuesNum; cnt++) {
    /* Calculate RFD and RRD ring sizes and allocate rings */
    const uint32 sizeRingAllocRFD = drv[emacIndex].countRFD * sizeof(RFD);
    const uint32 sizeRingAllocRRD = drv[emacIndex].countRFD * drv[emacIndex].rrdSize;
    //EMAC_PRINT_2("sizeRingAllocRFD %d, sizeRingAllocRRD %d\r\n",
       //     sizeRingAllocRFD, sizeRingAllocRRD);
    if ((0 != Emac_AllocBuffer(&(drv[emacIndex].ringRFD[cnt]), sizeRingAllocRFD,
            EMAC_BUF_ALIGN_MIN)) ||
        (0 != Emac_AllocBuffer(&(drv[emacIndex].ringRRD[cnt]), sizeRingAllocRRD,
                                         EMAC_BUF_ALIGN_MIN))) {
      EMAC_PRINT_0("Failed to allocate rings memory\r\n");
      return FALSE;   /* Failure */
    }

    /* Set base and current addresses of RRD type A descriptor */
    drv[emacIndex].baseRrdTypeA[cnt] = (RRD_TYPE_A *)(drv[emacIndex].ringRRD[cnt].vaddr + offsetTypeA);
    drv[emacIndex].curRrdTypeA[cnt]  = drv[emacIndex].baseRrdTypeA[cnt];

    /* Set indexes to start of queue */
    drv[emacIndex].indexRFD[cnt]     = 0;
    drv[emacIndex].indexProcRFD[cnt] = 0;
    drv[emacIndex].indexRRD[cnt]     = 0;
  }

 for (cntQ = 0; cntQ < drv[emacIndex].rxQueuesNum; cntQ++) {
  for(cnt = 0; cnt < drv[emacIndex].countRFD; cnt++) {
    index = cnt + cntQ*drv[emacIndex].countRFD;
    if(0 != Emac_AllocBuffer(&drv[emacIndex].rfdbuffer[index], EMAC_RX_BUF_SIZE,
          EMAC_BUF_ALIGN_MIN)) {
      EMAC_PRINT_0("Failed to allocate rfd buffers\r\n");
      return FALSE;   /* Failure */
    }
  }
 }

  /* Set parameters shared by all RX rings */

#ifdef EMAC1_FOR_IMC
  /* RFD and RRD rings base 32 MSBits */
  HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_0), 0x0);
#else
  /* RFD and RRD rings base 32 MSBits */
  if(emacIndex == 0)
    HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_0), (uint32)((uint64)drv[emacIndex].ringRRD[0].vaddr >> 32));
  else
    HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_0), (uint32)((uint64)drv[emacIndex].ringRRD[0].vaddr >> 32));
#endif
  if(emacIndex == 0){
      HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_3), drv[emacIndex].countRFD);  /* RFD ring size in descriptors */
      HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_4), drv[emacIndex].sizeBufRX); /* RFD buffer size in bytes */
      HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_6), drv[emacIndex].countRFD);  /* RRD ring size in descriptors */
  }
  else{
      HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_3), drv[emacIndex].countRFD);  /* RFD ring size in descriptors */
      HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_4), drv[emacIndex].sizeBufRX); /* RFD buffer size in bytes */
      HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_6), drv[emacIndex].countRFD);  /* RRD ring size in descriptors */
  }

  /* Set RFD and RRD rings base addresses - 32 LSBits */
  switch (drv[emacIndex].rxQueuesNum) {
    case 5: /* Ring #4 */
      if(emacIndex == 0){
          HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_17), (uint32)(uint64)drv[emacIndex].ringRFD[4].paddr);
          HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_18), (uint32)(uint64)drv[emacIndex].ringRRD[4].paddr);
      }
      else{
          HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_17), (uint32)(uint64)drv[emacIndex].ringRFD[4].paddr);
          HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_18), (uint32)(uint64)drv[emacIndex].ringRRD[4].paddr);
      }
      /* FALL-THROUGH */
    case 4: /* Ring #3 */
      if(emacIndex == 0){
          HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_13), (uint32)(uint64)drv[emacIndex].ringRFD[3].paddr);
          HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_16), (uint32)(uint64)drv[emacIndex].ringRRD[3].paddr);
      }
      else{
          HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_13), (uint32)(uint64)drv[emacIndex].ringRFD[3].paddr);
          HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_16), (uint32)(uint64)drv[emacIndex].ringRRD[3].paddr);
      }
      /* FALL-THROUGH */
    case 3: /* Ring #2 */
      if(emacIndex == 0){
          HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_12), (uint32)(uint64)drv[emacIndex].ringRFD[2].paddr);
          HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_15), (uint32)(uint64)drv[emacIndex].ringRRD[2].paddr);
      }
      else{
          HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_12), (uint32)(uint64)drv[emacIndex].ringRFD[2].paddr);
          HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_15), (uint32)(uint64)drv[emacIndex].ringRRD[2].paddr);
      }
      /* FALL-THROUGH */
    case 2: /* Ring #1 */
      if(emacIndex == 0){
      HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_10), (uint32)(uint64)drv[emacIndex].ringRFD[1].paddr);
      HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_14), (uint32)(uint64)drv[emacIndex].ringRRD[1].paddr);
      }
      else{
      HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_10), (uint32)(uint64)drv[emacIndex].ringRFD[1].paddr);
      HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_14), (uint32)(uint64)drv[emacIndex].ringRRD[1].paddr);
      }
      /* FALL-THROUGH */
    case 1: /* Ring #0 */
      if(emacIndex == 0){
          HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_2),  (uint32)(uint64)drv[emacIndex].ringRFD[0].paddr);
          HWIO_OUT(EMAC_REG_PRE(DESC_CTRL_5),  (uint32)(uint64)drv[emacIndex].ringRRD[0].paddr);
      }
      else{
          HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_2),  (uint32)(uint64)drv[emacIndex].ringRFD[0].paddr);
          HWIO_OUT(EMAC_REG_PRE1(DESC_CTRL_5),  (uint32)(uint64)drv[emacIndex].ringRRD[0].paddr);
      }
      break;
    default:
      /* Number of queues checked above, so should not reach here */
      break;
  }

  return TRUE;   /* Success */
}

/**
 * @brief       Initialize VMQ definitions
 *
 * @param[in]   cfg     Driver configuration
 *
 * @return      TRUE if successful, else failed
 */
static int Emac_InitVmq
(
 IN uint8 emacIndex,
 IN const EMAC_CFG *cfg
)
{
  uint32 cnt, regVal = 0;
  uint8 filtersVmq1 = 0, filtersVmq2 = 0,
        filtersVmq3 = 0, filtersVmq4 = 0;

  /* Store definition in driver struct */
  drv[emacIndex].isVmqEn = TRUE;

  /* Enable VMQ mode and disable RSS mode */
  if(emacIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), VMQ_EN, 0x1);
      HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), RSS_HASH_EN, 0x0);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), VMQ_EN, 0x1);
      HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), RSS_HASH_EN, 0x0);
  }

  /* Enable/Disable VMQ address/VLAN filters */
  if (EMAC_VMQ_FILTER_CNT < cfg->vmqFilterCnt) {
    EMAC_PRINT_2("Invalid VMQ filters count (%u). Possible up to %u\n",
        cfg->vmqFilterCnt, EMAC_VMQ_FILTER_CNT);
    return FALSE;
  }

  for (cnt = 0; cnt < cfg->vmqFilterCnt; cnt++) {
    boolean isVlanCmpEn    = cfg->vmqFilter[cnt].isVlanCmpEn;
    boolean isAddressCmpEn = cfg->vmqFilter[cnt].isAddressCmpEn;
    uint32  curFilterDef   = isVlanCmpEn | (isAddressCmpEn << 1);

    /* Each filter definition in reg is 4 bits higher than the previous one */
    regVal |= curFilterDef << (4 * cnt);
  }

  if(emacIndex == 0)
    HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER_EN_CTRL), regVal);
  else
    HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER_EN_CTRL), regVal);

  /* Configure filter to queue mapping */
  for (cnt = 0; cnt < cfg->vmqFilterCnt; cnt++) {
    uint8 vmqNum = cfg->vmqFilter[cnt].vmqNum;

    /* If current filter not configured proceed to next filter */
    if (0 == vmqNum) {
      continue;
    }

    /* Filters redirect to VMQ queues (#1-#4) not to default queue (#0) */
    if (vmqNum > cfg->rxQueues) {
      EMAC_PRINT_3("Invalid VMQ mapping (%u) for filter %u."
          " VMQ num should be between 1 and %u\n",
          vmqNum, (cnt+1), cfg->rxQueues);
      return FALSE;
    }

    /* For each filter update relevant queue mapping bits
     * by mapping current filter to this queue number
     */
    switch (vmqNum) {
      case 1:
        filtersVmq1 |= (1 << cnt);
        break;
      case 2:
        filtersVmq2 |= (1 << cnt);
        break;
      case 3:
        filtersVmq3 |= (1 << cnt);
        break;
      case 4:
        filtersVmq4 |= (1 << cnt);
        break;
      default:
        /* VMQ count was checked above, so this should not  happen */
        break;
    }
  }

  if(emacIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER_MAP), VMQ1_FILTER, filtersVmq1);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER_MAP), VMQ2_FILTER, filtersVmq2);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER_MAP), VMQ3_FILTER, filtersVmq3);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER_MAP), VMQ4_FILTER, filtersVmq4);

      /* Initialize VM queue filters definitions values - address and VLAN */
      HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER0_LO), cfg->vmqFilter[0].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER0_HI), VF0_VLAN, cfg->vmqFilter[0].vlan);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER0_HI), VF0_MAC_ADDR, cfg->vmqFilter[0].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER1_LO), cfg->vmqFilter[1].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER1_HI), VF1_VLAN, cfg->vmqFilter[1].vlan);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER1_HI), VF1_MAC_ADDR, cfg->vmqFilter[1].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER2_LO), cfg->vmqFilter[2].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER2_HI), VF2_VLAN, cfg->vmqFilter[2].vlan);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER2_HI), VF2_MAC_ADDR, cfg->vmqFilter[2].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER3_LO), cfg->vmqFilter[3].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER3_HI), VF3_VLAN, cfg->vmqFilter[3].vlan);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER3_HI), VF3_MAC_ADDR, cfg->vmqFilter[3].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER4_LO), cfg->vmqFilter[4].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER4_HI), VF4_VLAN, cfg->vmqFilter[4].vlan);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER4_HI), VF4_MAC_ADDR, cfg->vmqFilter[4].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER5_LO), cfg->vmqFilter[5].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER5_HI), VF5_VLAN, cfg->vmqFilter[5].vlan);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER5_HI), VF5_MAC_ADDR, cfg->vmqFilter[5].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER6_LO), cfg->vmqFilter[6].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER6_HI), VF6_VLAN, cfg->vmqFilter[6].vlan);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER6_HI), VF6_MAC_ADDR, cfg->vmqFilter[6].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE(VMQ_FILTER7_LO), cfg->vmqFilter[7].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER7_HI), VF7_VLAN, cfg->vmqFilter[7].vlan);
      HWIO_OUTF(EMAC_REG_PRE(VMQ_FILTER7_HI), VF7_MAC_ADDR, cfg->vmqFilter[7].addressHigh16);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER_MAP), VMQ1_FILTER, filtersVmq1);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER_MAP), VMQ2_FILTER, filtersVmq2);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER_MAP), VMQ3_FILTER, filtersVmq3);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER_MAP), VMQ4_FILTER, filtersVmq4);

      /* Initialize VM queue filters definitions values - address and VLAN */
      HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER0_LO), cfg->vmqFilter[0].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER0_HI), VF0_VLAN, cfg->vmqFilter[0].vlan);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER0_HI), VF0_MAC_ADDR, cfg->vmqFilter[0].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER1_LO), cfg->vmqFilter[1].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER1_HI), VF1_VLAN, cfg->vmqFilter[1].vlan);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER1_HI), VF1_MAC_ADDR, cfg->vmqFilter[1].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER2_LO), cfg->vmqFilter[2].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER2_HI), VF2_VLAN, cfg->vmqFilter[2].vlan);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER2_HI), VF2_MAC_ADDR, cfg->vmqFilter[2].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER3_LO), cfg->vmqFilter[3].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER3_HI), VF3_VLAN, cfg->vmqFilter[3].vlan);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER3_HI), VF3_MAC_ADDR, cfg->vmqFilter[3].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER4_LO), cfg->vmqFilter[4].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER4_HI), VF4_VLAN, cfg->vmqFilter[4].vlan);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER4_HI), VF4_MAC_ADDR, cfg->vmqFilter[4].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER5_LO), cfg->vmqFilter[5].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER5_HI), VF5_VLAN, cfg->vmqFilter[5].vlan);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER5_HI), VF5_MAC_ADDR, cfg->vmqFilter[5].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER6_LO), cfg->vmqFilter[6].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER6_HI), VF6_VLAN, cfg->vmqFilter[6].vlan);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER6_HI), VF6_MAC_ADDR, cfg->vmqFilter[6].addressHigh16);

      HWIO_OUT(EMAC_REG_PRE1(VMQ_FILTER7_LO), cfg->vmqFilter[7].addressLow32);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER7_HI), VF7_VLAN, cfg->vmqFilter[7].vlan);
      HWIO_OUTF(EMAC_REG_PRE1(VMQ_FILTER7_HI), VF7_MAC_ADDR, cfg->vmqFilter[7].addressHigh16);
  }

  return TRUE;
}

/**
 * @brief       Initialize RSS definitions
 *
 * @param[in]   cfg     Driver configuration
 *
 * @return      TRUE if successful, else failed
 */
static int Emac_InitRss
(
 IN uint8 emacIndex,
 IN const EMAC_CFG *cfg
)
{
  uint32 val = 0, cnt = 0, offset = 0;
  uint32 key0, key1, key2, key3, key4, key5, key6, key7, key8, key9;

  /* Store definitions in driver struct */
  drv[emacIndex].isRssEn = TRUE;

  /* Enable RSS mode and disable VMQ mode */
  if(emacIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), RSS_HASH_EN, 0x1);
      HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), VMQ_EN, 0x0);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), RSS_HASH_EN, 0x1);
      HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), VMQ_EN, 0x0);
  }

  /* Verify RX frame address type for RSS hash is valid and set value */
  if (cfg->rssHashType > EMAC_RSS_TYPE_MAX) {
    EMAC_PRINT_1("Invalid RSS hash type (%u), legal values are:\n"
        "0x1 (IPv4), 0x2 (TCP with IPv4), 0x4 (IPv6), 0x8 (TCP with IPv6)"
        "or a combination of them\n",
        cfg->rssHashType);
    return FALSE;
  }

  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), RSS_HASH_TYPE, cfg->rssHashType);
  else
    HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), RSS_HASH_TYPE, cfg->rssHashType);

  /* Hash indirection table (hash value to cpu number) */
  if (cfg->rssHashTblSize > 256) {
    EMAC_PRINT_1("Invalid RSS indirection table size (%u), legal values are"
        "64, 128, 256\n", cfg->rssHashTblSize);
    return FALSE;
  }

  val = (cfg->rssHashTblSize <= 64) ? 64 :
    ((cfg->rssHashTblSize <= 128) ? 128 : 256);

  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), IDT_TABLE_SIZE, val);
  else
    HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), IDT_TABLE_SIZE, val);

  /* Set 320-bit RSS key for hash function (use default if not specified) */
  if (NULL == cfg->rssKey) {
    key9 = 0x6d5a56da;
    key8 = 0x255b0ec2;
    key7 = 0x4167253d;
    key6 = 0x43a38fb0;
    key5 = 0xd0ca2bcb;
    key4 = 0xae7b30b4;
    key3 = 0x77cb2da3;
    key2 = 0x8030f20c;
    key1 = 0x6a42b73b;
    key0 = 0xbeac01fa;
  }
  else {
    key9 = ((cfg->rssKey[0] << 24)  | (cfg->rssKey[1] << 16)  |
        (cfg->rssKey[2] << 8)   | (cfg->rssKey[3]));
    key8 = ((cfg->rssKey[4] << 24)  | (cfg->rssKey[5] << 16)  |
        (cfg->rssKey[6] << 8)   | (cfg->rssKey[7]));
    key7 = ((cfg->rssKey[8] << 24)  | (cfg->rssKey[9] << 16)  |
        (cfg->rssKey[10] << 8)  | (cfg->rssKey[11]));
    key6 = ((cfg->rssKey[12] << 24) | (cfg->rssKey[13] << 16) |
        (cfg->rssKey[14] << 8)  | (cfg->rssKey[15]));
    key5 = ((cfg->rssKey[16] << 24) | (cfg->rssKey[17] << 16) |
        (cfg->rssKey[18] << 8)  | (cfg->rssKey[19]));
    key4 = ((cfg->rssKey[20] << 24) | (cfg->rssKey[21] << 16) |
        (cfg->rssKey[22] << 8)  | (cfg->rssKey[23]));
    key3 = ((cfg->rssKey[24] << 24) | (cfg->rssKey[25] << 16) |
        (cfg->rssKey[26] << 8)  | (cfg->rssKey[27]));
    key2 = ((cfg->rssKey[28] << 24) | (cfg->rssKey[29] << 16) |
        (cfg->rssKey[30] << 8)  | (cfg->rssKey[31]));
    key1 = ((cfg->rssKey[32] << 24) | (cfg->rssKey[33] << 16) |
        (cfg->rssKey[34] << 8)  | (cfg->rssKey[35]));
    key0 = ((cfg->rssKey[36] << 24) | (cfg->rssKey[37] << 16) |
        (cfg->rssKey[38] << 8)  | (cfg->rssKey[39]));
  }

  if(emacIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY9), RSS_KEY9, key9);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY8), RSS_KEY8, key8);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY7), RSS_KEY7, key7);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY6), RSS_KEY6, key6);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY5), RSS_KEY5, key5);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY4), RSS_KEY4, key4);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY3), RSS_KEY3, key3);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY2), RSS_KEY2, key2);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY1), RSS_KEY1, key1);
      HWIO_OUTF(EMAC_REG_PRE(RSS_KEY0), RSS_KEY0, key0);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY9), RSS_KEY9, key9);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY8), RSS_KEY8, key8);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY7), RSS_KEY7, key7);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY6), RSS_KEY6, key6);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY5), RSS_KEY5, key5);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY4), RSS_KEY4, key4);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY3), RSS_KEY3, key3);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY2), RSS_KEY2, key2);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY1), RSS_KEY1, key1);
      HWIO_OUTF(EMAC_REG_PRE1(RSS_KEY0), RSS_KEY0, key0);
  }

  /* Initialize redirection table */
  while (cnt < cfg->rssHashTblSize) {
    uint32 value = 0;
    int nibbleLoc;
    uint64 base;

    if(emacIndex == 0)
      base = HWIO_ADDR(EMAC_REG_PRE(IDT_TABLE0));
    else
      base = HWIO_ADDR(EMAC_REG_PRE1(IDT_TABLE0));

    if (cfg->rssHashTbl[cnt] > (EMAC_RXQ_MAX_RSS - 1)) {
      EMAC_PRINT_2("Invalid cpu count for RSS indirection table (%u)\n"
          "legal values are 0-%u\n", cfg->rssHashTbl[cnt],
          (EMAC_RXQ_MAX_RSS - 1));
      return FALSE;
    }

    /* Each entry in indirection table is a single nibble (4 bits).
     * Hence, each register of indirection table consists of 4 "table entries" (4 nibbles).
     * Loop sets current 8 entires (8 nibbles) in a single dword and then
     * register write is performed
     */
    for (nibbleLoc = 0; ((nibbleLoc <8) && (cnt < cfg->rssHashTblSize)); nibbleLoc++, cnt++) {
      value |= (cfg->rssHashTbl[cnt] << (4 * nibbleLoc));
    }

    out_dword(base + offset * sizeof(uint32), value);
    offset++;
  }

  return TRUE;
}

/**
 * @brief       TX specific ISR code will be invoked by the default ISR
 *
 *
 * @param[in]   userData    driver specific data pointer
 *
 * @param[in]   ringIndex   Index of the ring to service the descriptors
 */

void Emac_ISRTx
(
    IN uint8 emacIndex,
    IN volatile void *userData,
    IN int ringIndex
    )
{
  uint32 curTPDConsIdx = 0; /* TPD Consumer Index */
  uint32 lastTPDConsIdx = ((EMAC_DRV *)userData)->lastTPDConsInx;
  int idx;

  /* Get current TPD consumer index */
  switch (ringIndex) {
    case 0:
      if(emacIndex == 0)
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_2), NTPD_CONS_IDX);
      else
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_2), NTPD_CONS_IDX);
      break;
    case 1:
      if(emacIndex == 0)
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_10), H1TPD_CONS_IDX);
      else
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_10), H1TPD_CONS_IDX);
      break;
    case 2:
      if(emacIndex == 0)
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_10), H2TPD_CONS_IDX);
      else
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_10), H2TPD_CONS_IDX);
      break;
    case 3:
      if(emacIndex == 0)
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_12), H3TPD_CONS_IDX);
      else
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_12), H3TPD_CONS_IDX);
      break;
    case 4:
      if(emacIndex == 0)
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_2), HTPD_CONS_IDX);
      else
        curTPDConsIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_2), HTPD_CONS_IDX);
      break;
    default:
      EMAC_PRINT_0("Invalid Ring Index");
      break;
  }

  /* Release descriptors here, take care of buffers in the circular queue*/
  if (lastTPDConsIdx < curTPDConsIdx)
  {
    for(idx=lastTPDConsIdx; idx < curTPDConsIdx; idx++)
    {
      Emac_Memset(drv[emacIndex].tpdbuffersInt[idx].vaddr, 0, EMAC_RX_BUF_SIZE);
      drv[emacIndex].tpdbuffersInt[idx].size = 0;
    }
  }
  else
  {
    for(idx=lastTPDConsIdx; idx < drv[emacIndex].countTPD; idx++)
    {
      Emac_Memset(drv[emacIndex].tpdbuffersInt[idx].vaddr, 0, EMAC_RX_BUF_SIZE);
      drv[emacIndex].tpdbuffersInt[idx].size = 0;
    }
    for(idx=0; idx < curTPDConsIdx; idx++)
    {
      Emac_Memset(drv[emacIndex].tpdbuffersInt[idx].vaddr, 0, EMAC_RX_BUF_SIZE);
      drv[emacIndex].tpdbuffersInt[idx].size = 0;
    }
  }

  /* Keep track of hte last tpd consumer index */
  ((EMAC_DRV *)userData)->lastTPDConsInx = curTPDConsIdx;
}

/**
 * @brief       RX specific ISR code will be invoked by the default ISR
 *
 *
 * @param[in]   userData    driver specific data pointer
 *
 * @param[in]   ringIndex   Index of the ring to service the descriptors
 */
void Emac_ISRRx
(
 IN uint8 emacIndex,
 IN volatile void *userData,
 IN int ringIndex
 )
{
#ifdef EMAC1_FOR_IMC
  uint32 procIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROC_IDX);

  RRD_TYPE_A *curRrdTypeABase = drv[emacIndex].curRrdTypeA[0];
  RRD_TYPE_A *curRrdProcPtr = (RRD_TYPE_A *)(curRrdTypeABase+procIndex);

  /* UPDT is updated only for new packets */
  if ( (0x0 == curRrdProcPtr->UPDT)) {
    return;
  }

  /* Invoke read callback to notify the upper layers */
  if (NULL != drv[emacIndex].emacRdCbk) {
    drv[emacIndex].emacRdCbk(NULL);
  }

  /* clear UPDT field */
  curRrdProcPtr->UPDT = 0;

  /* update the procIndex */
  procIndex += curRrdProcPtr->NOR;
  if (procIndex >= drv[emacIndex].countRFD)
    procIndex -= drv[emacIndex].countRFD;

  /* Keep track of the proc Index for use later on*/
  drv[emacIndex].indexProcRFD[emacIndex] = procIndex;

  /* update the RFD0_PROC_IDX with the processed index */
  HWIO_OUTF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROC_IDX, procIndex);

  /* Set recv buffer with NULL ptr, will set the next buffer in the circular queue */
  Emac_SetRecvBuffer(NULL);
#endif
}

/**
 * @brief       Default driver ISR. Prints names of interrupts received
 *              subject to a predefined mask.
 *
 * @param[in]   userData    If non-null, user data
 */

static void Emac_IsrCore
(
 IN uint8 emacIndex,
 IN volatile void *userData
)
{
  /* Get interrupt status */
  uint32 statusUnmasked;
  uint32 status;
  EMAC_DRV *drvIns = (EMAC_DRV *)userData;

  if(emacIndex == 0)
    statusUnmasked = HWIO_IN(EMAC_REG_PRE(INT_STATUS));
  else
    statusUnmasked = HWIO_IN(EMAC_REG_PRE1(INT_STATUS));
  EMAC_PRINT_1("Core ISR: Status 0x%X ", statusUnmasked);

  status = statusUnmasked;

  if ((NULL == drvIns) || (EMAC_DRV_ID != drvIns->drvId)) {
    EMAC_PRINT_0("Error: EMAC ISR invalid driver instance");
    return;
  }

  if(emacIndex == 0){
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), TX_PKT_INT) & status) {
        EMAC_PRINT_0(", TX_PKT_INT");
        Emac_ISRTx(emacIndex, userData, 0);
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), TX_PKT_INT1) & status) {
        EMAC_PRINT_0(", TX_PKT_INT1");
        Emac_ISRTx(emacIndex, userData, 1);
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), TX_PKT_INT2) & status) {
        EMAC_PRINT_0(", TX_PKT_INT2");
        Emac_ISRTx(emacIndex, userData, 2);
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), TX_PKT_INT3) & status) {
        EMAC_PRINT_0(", TX_PKT_INT3");
        Emac_ISRTx(emacIndex, userData, 3);
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), TX_PKT_INT4) & status) {
        EMAC_PRINT_0(", TX_PKT_INT4");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), MAC_TX_INT) & status) {
        EMAC_PRINT_0(", MAC_TX_INT");
      }

      /* RX related interrupts */
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), MAC_RX_INT) & status) {
        EMAC_PRINT_0(", MAC_RX_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RX_PKT_INT0) & status) {
        EMAC_PRINT_0(", RX_PKT_INT");
        Emac_ISRRx(emacIndex, userData, 0);
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RX_PKT_INT1) & status) {
        EMAC_PRINT_0(", RX_PKT_INT1");
        Emac_ISRRx(emacIndex, userData, 1);
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RX_PKT_INT2) & status) {
        EMAC_PRINT_0(", RX_PKT_INT2");
        Emac_ISRRx(emacIndex, userData, 2);
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RX_PKT_INT3) & status) {
        EMAC_PRINT_0(", RX_PKT_INT3");
        Emac_ISRRx(emacIndex, userData, 3);
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RX_PKT_INT4) & status) {
        EMAC_PRINT_0(", RX_PKT_INT4");
        Emac_ISRRx(emacIndex, userData, 4);
      }

      /* Error-related interrupts */
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), TIMER_INT) & status) {
        EMAC_PRINT_0(", TIMER_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), SW_MAN_INT) & status) {
        EMAC_PRINT_0(", SW_MAN_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RXF_OF_INT) & status) {
        EMAC_PRINT_0(", RXF_OF_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RFD0_UR_INT) & status) {
        EMAC_PRINT_0(", RFD0_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RFD1_UR_INT) & status) {
        EMAC_PRINT_0(", RFD1_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RFD2_UR_INT) & status) {
        EMAC_PRINT_0(", RFD2_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RFD3_UR_INT) & status) {
        EMAC_PRINT_0(", RFD3_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), RFD4_UR_INT) & status) {
        EMAC_PRINT_0(", RFD4_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), TXF_UR_INT) & status) {
        EMAC_PRINT_0(", TXF_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), DMAR_TO_INT) & status) {
        EMAC_PRINT_0(", DMAR_TO_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), DMAW_TO_INT) & status) {
        EMAC_PRINT_0(", DMAW_TO_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), TXQ_TO_INT) & status) {
        EMAC_PRINT_0(", TXQ_TO_INT");
      }

      /* Link Up/Down interrupts */
      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), GPHY_LINK_UP_INT) & status) {
        EMAC_PRINT_0(", GPHY_LINK_UP_INT");
        drvIns->isLinkUp = TRUE;
        if(drv[emacIndex].emacState == RUNNING) {
          Emac_Notify(emacIndex, EMAC_LINK_UP);
        }
      }

      if (HWIO_FMSK(EMAC_REG_PRE(INT_STATUS), GPHY_LINK_DOWN_INT) & status) {
        EMAC_PRINT_0(", GPHY_LINK_DOWN_INT");
        drvIns->isLinkUp = FALSE;
        Emac_Notify(emacIndex, EMAC_LINK_DOWN);
      }
  }
  else{
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), TX_PKT_INT) & status) {
        EMAC_PRINT_0(", TX_PKT_INT");
        Emac_ISRTx(emacIndex, userData, 0);
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), TX_PKT_INT1) & status) {
        EMAC_PRINT_0(", TX_PKT_INT1");
        Emac_ISRTx(emacIndex, userData, 1);
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), TX_PKT_INT2) & status) {
        EMAC_PRINT_0(", TX_PKT_INT2");
        Emac_ISRTx(emacIndex, userData, 2);
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), TX_PKT_INT3) & status) {
        EMAC_PRINT_0(", TX_PKT_INT3");
        Emac_ISRTx(emacIndex, userData, 3);
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), TX_PKT_INT4) & status) {
        EMAC_PRINT_0(", TX_PKT_INT4");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), MAC_TX_INT) & status) {
        EMAC_PRINT_0(", MAC_TX_INT");
      }

      /* RX related interrupts */
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), MAC_RX_INT) & status) {
        EMAC_PRINT_0(", MAC_RX_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RX_PKT_INT0) & status) {
        EMAC_PRINT_0(", RX_PKT_INT");
        Emac_ISRRx(emacIndex, userData, 0);
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RX_PKT_INT1) & status) {
        EMAC_PRINT_0(", RX_PKT_INT1");
        Emac_ISRRx(emacIndex, userData, 1);
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RX_PKT_INT2) & status) {
        EMAC_PRINT_0(", RX_PKT_INT2");
        Emac_ISRRx(emacIndex, userData, 2);
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RX_PKT_INT3) & status) {
        EMAC_PRINT_0(", RX_PKT_INT3");
        Emac_ISRRx(emacIndex, userData, 3);
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RX_PKT_INT4) & status) {
        EMAC_PRINT_0(", RX_PKT_INT4");
        Emac_ISRRx(emacIndex, userData, 4);
      }

      /* Error-related interrupts */
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), TIMER_INT) & status) {
        EMAC_PRINT_0(", TIMER_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), SW_MAN_INT) & status) {
        EMAC_PRINT_0(", SW_MAN_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RXF_OF_INT) & status) {
        EMAC_PRINT_0(", RXF_OF_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RFD0_UR_INT) & status) {
        EMAC_PRINT_0(", RFD0_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RFD1_UR_INT) & status) {
        EMAC_PRINT_0(", RFD1_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RFD2_UR_INT) & status) {
        EMAC_PRINT_0(", RFD2_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RFD3_UR_INT) & status) {
        EMAC_PRINT_0(", RFD3_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), RFD4_UR_INT) & status) {
        EMAC_PRINT_0(", RFD4_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), TXF_UR_INT) & status) {
        EMAC_PRINT_0(", TXF_UR_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), DMAR_TO_INT) & status) {
        EMAC_PRINT_0(", DMAR_TO_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), DMAW_TO_INT) & status) {
        EMAC_PRINT_0(", DMAW_TO_INT");
      }
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), TXQ_TO_INT) & status) {
        EMAC_PRINT_0(", TXQ_TO_INT");
      }

      /* Link Up/Down interrupts */
      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), GPHY_LINK_UP_INT) & status) {
        EMAC_PRINT_0(", GPHY_LINK_UP_INT");
        drvIns->isLinkUp = TRUE;
        if(drv[emacIndex].emacState == RUNNING) {
          Emac_Notify(emacIndex, EMAC_LINK_UP);
        }
      }

      if (HWIO_FMSK(EMAC_REG_PRE1(INT_STATUS), GPHY_LINK_DOWN_INT) & status) {
        EMAC_PRINT_0(", GPHY_LINK_DOWN_INT");
        drvIns->isLinkUp = FALSE;
        Emac_Notify(emacIndex, EMAC_LINK_DOWN);
      }
  }

  EMAC_PRINT_0("\r\n");
  /*
   * ==== After this point put debugging code only ====
   */

  /* Check if anything left that is not ignored */
  if (0 == status) {
    return;
  }
}

void fake_emac_isr(uint8 emacIndex)
{
    Emac_IsrCore(emacIndex, &drv[emacIndex]);
}
/**
 * @brief       Initialize driver
 *
 * @param[in]   cfg     Driver configuration
 *
 * @return      TRUE if successful, else failed.
 */
  int Emac_CoreInit
(
 IN uint8 emacIndex,
 IN EMAC_CFG *cfg
 )
{
  uint32 val;

  if (NULL == cfg) {
    EMAC_PRINT_0("NULL param\r\n");
    return FALSE;   /* Failure */
  }

#if 0
  /* Rings have to be initialized before this. */
  if ((NULL != drv[emacIndex].ringTPD[0].vaddr) || (NULL != drv[emacIndex].ringRFD[0].vaddr)) {
    EMAC_PRINT_0("Driver already initialized\r\n");
    return FALSE;   /* Failure */
  }
#endif

  /* Clear driver struct, zero statistics counters */
  Emac_Memset(&drv[emacIndex], 0, sizeof(drv[emacIndex]));
  drv[emacIndex].drvId = EMAC_DRV_ID;

  /* Mask all interrupts to disable them until config is done */
  if(emacIndex == 0)
    HWIO_OUT(EMAC_REG_PRE(INT_MASK), 0x0);
  else
    HWIO_OUT(EMAC_REG_PRE1(INT_MASK), 0x0);

  /* Disable TX and RX until initialization is complete */
  if(emacIndex == 0)
    HWIO_OUTF2(EMAC_REG_PRE(MAC_CTRL), TXEN, RXEN,
                                        0x0,  0x0);
  else
    HWIO_OUTF2(EMAC_REG_PRE1(MAC_CTRL), TXEN, RXEN,
                                        0x0,  0x0);

  /* set the MAC Address */
  Emac_SetMacAddr(emacIndex, &cfg->addr);

  if(emacIndex == 0)
      HWIO_OUTF4(EMAC_REG_PRE(MAC_IPGIFG_CTRL),
          IPGT, MIFG, IPGR1, IPGR2,
          0x60, 0x50, 0x40,  0x60);
  else
      HWIO_OUTF4(EMAC_REG_PRE1(MAC_IPGIFG_CTRL),
          IPGT, MIFG, IPGR1, IPGR2,
          0x60, 0x50, 0x40,  0x60);

  /* Check for half duplex */
  if (cfg->isFullDuplex == FALSE) {
    /* No support for half-duplex 1000Mb/s */
    if (1000 == cfg->speed) {
      EMAC_PRINT_0("Half-duplex 1000Mbps not supported\r\n");
      return FALSE;   /* Failure */
    }

    if(emacIndex == 0){
        HWIO_OUTF6(EMAC_REG_PRE(MAC_HALF_DPLX_CTRL),
            LCOL, RETRY, EDXSDFR, NOBO, ABEBT, ABEBE,
            0x37, 0xF,   0x1,     0x0,  0xa,   0x0);
        HWIO_OUTF2(EMAC_REG_PRE(MAC_HALF_DPLX_CTRL),
            JAM_IPG, BPNB,
            0x7,     0x0);
    }
    else{
        HWIO_OUTF6(EMAC_REG_PRE1(MAC_HALF_DPLX_CTRL),
            LCOL, RETRY, EDXSDFR, NOBO, ABEBT, ABEBE,
            0x37, 0xF,   0x1,     0x0,  0xa,   0x0);
        HWIO_OUTF2(EMAC_REG_PRE1(MAC_HALF_DPLX_CTRL),
            JAM_IPG, BPNB,
            0x7,     0x0);
    }
  }

  /* Enable status clear-on-read */
  if(emacIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(DMA_MAS_CTRL), INT_RD_CLR_EN, 0x1);

      HWIO_OUTF3(EMAC_REG_PRE(DMA_MAS_CTRL),
          SW_MAN_INT_EN, TIMER_EN, SA_TIMER_EN,
          0x0,           0x0,      0x0);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(DMA_MAS_CTRL), INT_RD_CLR_EN, 0x1);

      HWIO_OUTF3(EMAC_REG_PRE1(DMA_MAS_CTRL),
          SW_MAN_INT_EN, TIMER_EN, SA_TIMER_EN,
          0x0,           0x0,      0x0);
  }

  /* Disable low-power mode */
  if(emacIndex == 0)
      HWIO_OUTF4(EMAC_REG_PRE(DMA_MAS_CTRL),
          LPW_MODE, LPW_CLK_SEL, LPW_STATE, AUTO_PME_ENABLE,
          0x0,      0x0,         0x0,       0x1);
  else
      HWIO_OUTF4(EMAC_REG_PRE1(DMA_MAS_CTRL),
      LPW_MODE, LPW_CLK_SEL, LPW_STATE, AUTO_PME_ENABLE,
      0x0,      0x0,         0x0,       0x1);

  /* TX interrupt moderation */
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(DMA_MAS_CTRL), IRQ_MODERATOR_EN, 0);
  else
    HWIO_OUTF(EMAC_REG_PRE1(DMA_MAS_CTRL), IRQ_MODERATOR_EN, 0);

  /* RX interrupt moderation */
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(DMA_MAS_CTRL), IRQ_MODERATOR2_EN, 0);
  else
    HWIO_OUTF(EMAC_REG_PRE1(DMA_MAS_CTRL), IRQ_MODERATOR2_EN, 0);

  /* MDIO clause 22, no auto polling */
  if(emacIndex == 0)
      HWIO_OUTF4(EMAC_REG_PRE(MDIO_CTRL),
          MDIO_MODE, MDIO_PR, MDIO_AP_EN, SUP_PREAMBLE,
          0,         0,       0,          1);
  else
      HWIO_OUTF4(EMAC_REG_PRE1(MDIO_CTRL),
          MDIO_MODE, MDIO_PR, MDIO_AP_EN, SUP_PREAMBLE,
          0,         0,       0,          1);

  /* EMAC_MAC_CTRL */
  if(emacIndex == 0)
      HWIO_OUTF2(EMAC_REG_PRE(MAC_CTRL),
          CRCE, PCRCE,
          0x1,  0x1);
  else
      HWIO_OUTF2(EMAC_REG_PRE1(MAC_CTRL),
          CRCE, PCRCE,
          0x1,  0x1);

  /* Send PAUSE frames */
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), TXFC, 1);
  else
    HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), TXFC, 1);

  /* RX Flow control */
  if(emacIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), RXFC, 1);

      HWIO_OUTF4(EMAC_REG_PRE(MAC_CTRL),
          FLCHK, PRLEN, TPAUSE, SSTCT,
          0x1,   0x7,   0x0,    0x0);

      HWIO_OUTF3(EMAC_REG_PRE(MAC_CTRL),
          SIMR, MBOF, RX_CHKSUM_EN,
          0x0,  0x0,  0x1);

      HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), HUGE, 0);

      HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), HUGEN, 0);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), RXFC, 1);

      HWIO_OUTF4(EMAC_REG_PRE1(MAC_CTRL),
          FLCHK, PRLEN, TPAUSE, SSTCT,
          0x1,   0x7,   0x0,    0x0);

      HWIO_OUTF3(EMAC_REG_PRE1(MAC_CTRL),
          SIMR, MBOF, RX_CHKSUM_EN,
          0x0,  0x0,  0x1);

      HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), HUGE, 0);

      HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), HUGEN, 0);
  }

  /* Debug mode */
  val = 0x0;
  if (TRUE == cfg->isDebug)
  {
    val = 0x1;
    EMAC_PRINT_0("WARNING: EMAC DEBUG mode enabled\r\n");
  }

  if(emacIndex == 0)
      HWIO_OUTF2(EMAC_REG_PRE(MAC_CTRL),
          DEBUG_MODE, SINGLE_PAUSE_MODE,
          val,        0x0);
  else
      HWIO_OUTF2(EMAC_REG_PRE1(MAC_CTRL),
          DEBUG_MODE, SINGLE_PAUSE_MODE,
          val,        0x0);

  val = 0x0;
  if (EMAC_LB_MAC == cfg->modeLoopback)
  {
    EMAC_PRINT_0("EMAC loopback mode activated\r\n");
    val = 0x1;
  }

  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), MAC_LP_EN, val);
  else
    HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), MAC_LP_EN, val);

  /* Full/Half duplex */
  val = (TRUE == cfg->isFullDuplex) ? 0x1 : 0x0;
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), FULLD, val);
  else
    HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), FULLD, val);

  /* Promiscuous mode */
  val = (TRUE == cfg->isPromiscuous) ? 0x1 : 0x0;
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), PROM_MODE, 1);
  else
    HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), PROM_MODE, 1);

  /* Don't support Athr header */
  if(emacIndex == 0)
      HWIO_OUTF2(EMAC_REG_PRE(ATHR_HEADER_CTRL),
          HEADER_ENABLE, HEADER_CNT_EN,
          0x0,           0x0);
  else
      HWIO_OUTF2(EMAC_REG_PRE1(ATHR_HEADER_CTRL),
          HEADER_ENABLE, HEADER_CNT_EN,
          0x0,           0x0);

  /* Multicast mode */
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), MULTI_ALL, 0);
  else
    HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), MULTI_ALL, 0);

  /* Broadcast mode */
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), BROAD_EN, 0);
  else
    HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), BROAD_EN, 0);

  /* TX timestamp */
  drv[emacIndex].isTxTsEn = cfg->isTxTsEn;
  val = (TRUE == drv[emacIndex].isTxTsEn) ? 0x1 : 0x0;
  if(emacIndex)
    HWIO_OUTF(EMAC_REG_PRE(EMAC_WRAPPER_CSR1), TX_TS_ENABLE, val);
  else
    HWIO_OUTF(EMAC_REG_PRE1(EMAC_WRAPPER_CSR1), TX_TS_ENABLE, val);

  /* Select QCT RMON counters */
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(EMAC_WRAPPER_CSR1), ENABLE_RMON_CNTR, 0x1);
  else
    HWIO_OUTF(EMAC_REG_PRE1(EMAC_WRAPPER_CSR1), ENABLE_RMON_CNTR, 0x1);

  /* Descriptor rings initialization */

  /* Initialize and set RFD and RRD rings */
  if (TRUE != Emac_InitRxRings(emacIndex, cfg)) {
    EMAC_PRINT_0("RX rings initialization failed\r\n");
    return FALSE;
  }

  /* Initialize and set TPD rings */
  if (TRUE != Emac_InitTxRings(emacIndex, cfg)) {
    EMAC_PRINT_0("TX rings initialization failed\r\n");
    return FALSE;
  }

  /* VMQ/RSS initialization */
  if ((TRUE == cfg->isRssEn) && (TRUE == cfg->isVmqEn)) {
    EMAC_PRINT_0("Invalid configuration. Can't set both RSS and VMQ\r\n");
    return FALSE;
  }

  /* VMQ initialization */
  if (TRUE == cfg->isVmqEn){
    if (TRUE != Emac_InitVmq(emacIndex, cfg)) {
      EMAC_PRINT_0("VMQ initialization failed\r\n");
      return FALSE;
    }
  }
  else {
    /* Disable VMQ mode */
    if(emacIndex == 0)
      HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), VMQ_EN, 0x0);
    else
      HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), VMQ_EN, 0x0);
  }

  /* RSS initialization */
  if (TRUE == cfg->isRssEn) {
    if (TRUE != Emac_InitRss(emacIndex, cfg)) {
      EMAC_PRINT_0("RSS initialization failed\r\n");
      return FALSE;
    }
  }
  else {
    /* Disable VMQ mode */
    if(emacIndex == 0)
      HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), RSS_HASH_EN, 0x0);
    else
      HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), RSS_HASH_EN, 0x0);
  }

  /* MTU initialization */
  if (0 != cfg->mtuSize) {
    if(emacIndex == 0)
      HWIO_OUTF(EMAC_REG_PRE(MAX_FRAM_LEN_CTRL), MTU, cfg->mtuSize);
    else
      HWIO_OUTF(EMAC_REG_PRE1(MAX_FRAM_LEN_CTRL), MTU, cfg->mtuSize);
  }

  /* Init even padding option */
  if (TRUE == cfg->isEvenPad) {
    drv[emacIndex].isEvenPad = TRUE;
  }

  /* Init TPD type B definitions */
  drv[emacIndex].L4HDR_OFFSET = 0;
  drv[emacIndex].IPX = 0;
  drv[emacIndex].TCPX = 0;
  drv[emacIndex].UDPX = 0;

  if(emacIndex == 0){
      /* Disable 1588 IP clocks */
      HWIO_OUTF(EMAC_REG_PRE(EMAC_WRAPPER_CSR1), DIS_1588_CLKS, 0x1);

      /* Disable 1588 operation */
      HWIO_OUTF(EMAC_REG_PRE(EMAC_WRAPPER_CSR10), DIS_1588, 0x1);
      HWIO_OUTF(EMAC_REG_PRE(P1588_CTRL_REG), BYPASS_O, 0x1);

      /* Mask (disable) all PTP interrupts (whole register, specifically) */
      HWIO_OUT(EMAC_REG_PRE(P1588_PTP_EXPANDED_INT_MASK), 0x0);
  }
  else{
      /* Disable 1588 IP clocks */
      HWIO_OUTF(EMAC_REG_PRE1(EMAC_WRAPPER_CSR1), DIS_1588_CLKS, 0x1);

      /* Disable 1588 operation */
      HWIO_OUTF(EMAC_REG_PRE1(EMAC_WRAPPER_CSR10), DIS_1588, 0x1);
      HWIO_OUTF(EMAC_REG_PRE1(P1588_CTRL_REG), BYPASS_O, 0x1);

      /* Mask (disable) all PTP interrupts (whole register, specifically) */
      HWIO_OUT(EMAC_REG_PRE1(P1588_PTP_EXPANDED_INT_MASK), 0x0);
  }

  /* VLAN Definitions */
  /* Enable/Disable VLAN insertion offload for TX packets (0 means no offload) */
  drv[emacIndex].sVlanInfoIns = cfg->sVlanInfoIns;
  drv[emacIndex].cVlanInfoIns = cfg->cVlanInfoIns;

  /* Enable/Disable VLAN strip option */
  val = (TRUE == cfg->isVlanStripEn)? 0x1: 0x0;
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), VLAN_STRIP, val);
  else
    HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), VLAN_STRIP, val);

  /* Set VLAN tag identifiers */
  if (0 != cfg->sVlanID) {
    if(emacIndex == 0)
      HWIO_OUTF(EMAC_REG_PRE(VLAN_TPD_CFIG), SVLAN_TPID_CFG, cfg->sVlanID);
    else
      HWIO_OUTF(EMAC_REG_PRE1(VLAN_TPD_CFIG), SVLAN_TPID_CFG, cfg->sVlanID);
  }

  if (0 != cfg->cVlanID) {
    if(emacIndex == 0)
      HWIO_OUTF(EMAC_REG_PRE(VLAN_TPD_CFIG), CVLAN_TPID_CFG, cfg->cVlanID);
    else
      HWIO_OUTF(EMAC_REG_PRE1(VLAN_TPD_CFIG), SVLAN_TPID_CFG, cfg->sVlanID);
  }

  /* DMA initialization */

  /* Jumbo offload */
  if(emacIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(TXQ_CTRL_1), JUMBO_TASK_OFFLOAD_THRESHOLD, 0x480);

      HWIO_OUTF2(EMAC_REG_PRE(TXQ_CTRL_2),
          TXF_HWM, TXF_LWM,
          0x0,     0x0);

      HWIO_OUTF4(EMAC_REG_PRE(DMA_CTRL),
          IN_ORDER_MODE, ENH_ORDER_MODE, OUT_ORDER_MODE, PENDING_CNT_EN,
          0x0,           0x0,            0x1,            0x1);

      HWIO_OUTF5(EMAC_REG_PRE(DMA_CTRL),
          REGRDBLEN, REGWRBLEN, DMAR_REQ_PRI, DMAR_DLY_CNT, DMAW_DLY_CNT,
          0x5,       0x0,       0x1,          0xF,          0x4);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(TXQ_CTRL_1), JUMBO_TASK_OFFLOAD_THRESHOLD, 0x480);

      HWIO_OUTF2(EMAC_REG_PRE1(TXQ_CTRL_2),
          TXF_HWM, TXF_LWM,
          0x0,     0x0);

      HWIO_OUTF4(EMAC_REG_PRE1(DMA_CTRL),
          IN_ORDER_MODE, ENH_ORDER_MODE, OUT_ORDER_MODE, PENDING_CNT_EN,
          0x0,           0x0,            0x1,            0x1);

      HWIO_OUTF5(EMAC_REG_PRE1(DMA_CTRL),
          REGRDBLEN, REGWRBLEN, DMAR_REQ_PRI, DMAR_DLY_CNT, DMAW_DLY_CNT,
          0x5,       0x0,       0x1,          0xF,          0x4);
  }

  /* ! Load base pointers ! */
  if(emacIndex == 0){
      HWIO_OUTF(EMAC_REG_PRE(INTER_SRAM_PART9), LOAD_PTR, 0x1);

      HWIO_OUTF6(EMAC_REG_PRE(TXQ_CTRL_0),
          NUM_TPD_BURST_PREF, IP_OP_SP, TXQ_EN, TXQ_MODE, LS_8023_SP, NUM_TXF_BURST_PREF,
          0x5,                0x0,      0x1,    0x1,      0x1,        0x100);

      HWIO_OUTF2(EMAC_REG_PRE(RXQ_CTRL_0),
          SP_IPV6, NIP_QUEUE_SEL,
          0x1,     0x0);

      HWIO_OUTF(EMAC_REG_PRE(RXQ_CTRL_0), RSS_HASH_TYPE, 0);

      HWIO_OUTF3(EMAC_REG_PRE(RXQ_CTRL_0),
          CUT_THRU_EN, RXQ_EN, NUM_RFD_BURST_PREF,
          0x1,         0x1,    0x8);

      HWIO_OUTF3(EMAC_REG_PRE(RXQ_CTRL_1),
          JUMBO_1KAH, RFD_PREF_LOW_THRESHOLD, RFD_PREF_UP_THRESHOLD,
          0x1,        0x8,                    0x10);

      HWIO_OUTF2(EMAC_REG_PRE(RXQ_CTRL_2),
          RXF_UOF_THRESHOLD, RXF_DOF_THRESHOLD,
          0xBE,              0x1A0);

      HWIO_OUTF2(EMAC_REG_PRE(RXQ_CTRL_3),
          RXD_THRESHOLD, RXD_TIMER,
          0x100,         0x0);
  }
  else{
      HWIO_OUTF(EMAC_REG_PRE1(INTER_SRAM_PART9), LOAD_PTR, 0x1);

      HWIO_OUTF6(EMAC_REG_PRE1(TXQ_CTRL_0),
          NUM_TPD_BURST_PREF, IP_OP_SP, TXQ_EN, TXQ_MODE, LS_8023_SP, NUM_TXF_BURST_PREF,
          0x5,                0x0,      0x1,    0x1,      0x1,        0x100);

      HWIO_OUTF2(EMAC_REG_PRE1(RXQ_CTRL_0),
          SP_IPV6, NIP_QUEUE_SEL,
          0x1,     0x0);

      HWIO_OUTF(EMAC_REG_PRE1(RXQ_CTRL_0), RSS_HASH_TYPE, 0);

      HWIO_OUTF3(EMAC_REG_PRE1(RXQ_CTRL_0),
          CUT_THRU_EN, RXQ_EN, NUM_RFD_BURST_PREF,
          0x1,         0x1,    0x8);

      HWIO_OUTF3(EMAC_REG_PRE1(RXQ_CTRL_1),
          JUMBO_1KAH, RFD_PREF_LOW_THRESHOLD, RFD_PREF_UP_THRESHOLD,
          0x1,        0x8,                    0x10);

      HWIO_OUTF2(EMAC_REG_PRE1(RXQ_CTRL_2),
          RXF_UOF_THRESHOLD, RXF_DOF_THRESHOLD,
          0xBE,              0x1A0);

      HWIO_OUTF2(EMAC_REG_PRE1(RXQ_CTRL_3),
          RXD_THRESHOLD, RXD_TIMER,
          0x100,         0x0);
  }

  if(emacIndex == 0){
      /* AXI master settings - little endian data */
      HWIO_OUTF3(EMAC_REG_PRE(AXI_MAST_CTRL),
          MAX_BTYPE, MAX_BOUND, DATA_BYTE_SWAP,
          0x1,       0x0,       0x0);

      /* Disable all clocks gating */
      HWIO_OUT(EMAC_REG_PRE(CLK_GATE_CTRL), 0x0);
  }
  else{
      /* AXI master settings - little endian data */
      HWIO_OUTF3(EMAC_REG_PRE1(AXI_MAST_CTRL),
          MAX_BTYPE, MAX_BOUND, DATA_BYTE_SWAP,
          0x1,       0x0,       0x0);

      /* Disable all clocks gating */
      HWIO_OUT(EMAC_REG_PRE1(CLK_GATE_CTRL), 0x0);
  }


  /* EPHY status auto-polling */
  drv[emacIndex].isAutoPoll = FALSE;
  drv[emacIndex].isLinkUp   = FALSE;

  /* Wake-On-Lan */
  if(emacIndex == 0)
    HWIO_OUT(EMAC_REG_PRE(WOL_CTRL0), 0x0); /* Disable all WOL options */
  else
    HWIO_OUT(EMAC_REG_PRE1(WOL_CTRL0), 0x0); /* Disable all WOL options */
  drv[emacIndex].wolStatus = EMAC_WOL_NONE;

  if(emacIndex == 0)
      HWIO_OUTF2(EMAC_REG_PRE(WOL_CTRL0),
          LK_CHG_EN, LK_CHG_PME,
          0x1,       0x1);
  else
      HWIO_OUTF2(EMAC_REG_PRE1(WOL_CTRL0),
          LK_CHG_EN, LK_CHG_PME,
          0x1,       0x1);

  if(emacIndex == 0){
      /* Link status option requires AUTO_PME_ENABLE */
      HWIO_OUTF(EMAC_REG_PRE(DMA_MAS_CTRL), AUTO_PME_ENABLE, 0x1);

      /* Interrupt handling*/

      /* Enable int for unfinished RX */
      HWIO_OUTF(EMAC_REG_PRE(MISC_CTRL), RX_UNCPL_INT_EN, 0x1);

      /* Disable interrupt re-trigger */
      HWIO_OUTF(EMAC_REG_PRE(INT_RETRIG_INIT), INT_RETRIG_TIME, 0x0);

      /* Read interrupt status register to clear it before we register */
      (void)HWIO_IN(EMAC_REG_PRE(INT_STATUS));
  }
  else{
      /* Link status option requires AUTO_PME_ENABLE */
      HWIO_OUTF(EMAC_REG_PRE1(DMA_MAS_CTRL), AUTO_PME_ENABLE, 0x1);

      /* Interrupt handling*/

      /* Enable int for unfinished RX */
      HWIO_OUTF(EMAC_REG_PRE1(MISC_CTRL), RX_UNCPL_INT_EN, 0x1);

      /* Disable interrupt re-trigger */
      HWIO_OUTF(EMAC_REG_PRE1(INT_RETRIG_INIT), INT_RETRIG_TIME, 0x0);

      /* Read interrupt status register to clear it before we register */
      (void)HWIO_IN(EMAC_REG_PRE1(INT_STATUS));
  }

  /* Register the core ISR */
  if (TRUE != Emac_RegisterCoreIsr(Emac_IsrCore, &drv[emacIndex])) {
    EMAC_PRINT_0("Failed to register core ISR\n");
    return FALSE;       /* Failure */
  }

  /* Enable all interrupts */
  if(emacIndex == 0)
    HWIO_OUT(EMAC_REG_PRE(INT_MASK), 0xFFFFFFFF);
  else
    HWIO_OUT(EMAC_REG_PRE1(INT_MASK), 0xFFFFFFFF);

  /* Enable TX/RX
   * Enable RX and TX only after all configuration is done
   * (disabled at start of init process) */
  if (FALSE == cfg->isTxDisable) {
    if(emacIndex == 0)
      HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), TXEN, 0x1);
    else
      HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), TXEN, 0x1);
  }

  if (FALSE == cfg->isRxDisable) {
    if(emacIndex == 0)
      HWIO_OUTF(EMAC_REG_PRE(MAC_CTRL), RXEN, 0x1);
    else
      HWIO_OUTF(EMAC_REG_PRE1(MAC_CTRL), RXEN, 0x1);
  }

  /* Attach notifiers */
  drv[emacIndex].emacState = INITIALIZED;

#ifdef EMAC1_FOR_IMC
  Emac_AttachDrv(gEmacUpNtfy, gEmacRdCbk);
#endif

  return TRUE;   /* Success */
}

/**
 * @brief       Transmit a single frame
 *
 * @param[in]   buffer      Buffer of frame data
 * @param[in]   length      Buffer data length in bytes
 * @param[in]   isLastSeg   Marks if buffer is last segment of frame
 *
 * @return      TRUE if successful, else failed
 */
boolean Emac_Send
(
 IN uint8 emacIndex,
 IN uint8 *buffer,
 IN uint32 length,
 IN boolean isLastSeg
)
{
  TPD    *ringTPD    = (TPD *)(void *)drv[emacIndex].ringTPD[0].vaddr;
  uint32  indexTPD   = drv[emacIndex].indexTPD[0];
  TPD    *currentTPD = &(ringTPD[indexTPD]);

  if ((NULL == buffer) || (0 == length)) {
    EMAC_PRINT_0("Invalid TX buffer param\r\n");
    return FALSE;   /* Failure */
  }

  /* Check if ring full */
  if(drv[emacIndex].tpdbuffersInt[indexTPD].size) {
    EMAC_PRINT_0("TPD Ring Full\r\n");
    return FALSE;
  }

  /* Copy the buffer to the tpd ring */
  Emac_Memcpy(drv[emacIndex].tpdbuffersInt[indexTPD].paddr, buffer, length);
  drv[emacIndex].tpdbuffersInt[indexTPD].size = length;

  /* Set buffer address and size */
  currentTPD->TypeA.BUFFER_ADDR_L = (uint32)(uint64)drv[emacIndex].tpdbuffersInt[indexTPD].paddr;
#ifdef EMAC1_FOR_IMC
  currentTPD->TypeA.BUFFER_ADDR_H = 0;
#else
  currentTPD->TypeA.BUFFER_ADDR_H = (uint32)((uint64)drv[emacIndex].tpdbuffersInt[indexTPD].paddr >> 32);
#endif
  currentTPD->TypeA.BUF_LEN       = length;

  /* Check if buffer is last segment of frame */
  currentTPD->TypeA.LS = (TRUE == isLastSeg) ? 1 : 0;

  /* Advance TPD index */
  ++indexTPD;
  if (indexTPD >= drv[emacIndex].countTPD) {
    indexTPD = 0;
  }

  /* adding a barrier to make sure the RFD is updated before emac reads it */
#if (__TARGET_ARCH_ARM >= 7)  || (__ARM_ARCH >= 7)
  __asm("dsb sy");
#endif
  //Emac_SleepMS(10);

  /* Supports single TX queue */
  /* TPD producer index is set to one index after the last produced index */

  /* Since NTPD_PROD_IDX is the only field in register EMAC_MAILBOX_15,
   * instead using HWIO_OUTF for read-modify-write, we can use HWIO_OUT to
   * perform write only and save a register access, which is considerable
   * (e.g. in emulation)
   */
  if(emacIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(MAILBOX_15), NTPD_PROD_IDX, indexTPD);
  else
    HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_15), NTPD_PROD_IDX, indexTPD);

#if (__TARGET_ARCH_ARM >= 7)  || (__ARM_ARCH >= 7)
  __asm("dsb sy");
#endif
  //Emac_SleepMS(10);

  drv[emacIndex].indexTPD[0] = indexTPD;

  return TRUE;       /* Success */
}

/**
 * @brief       Set a all receive frame buffers at default RX queue (#0)
 *
 * @param[in]   buffer    Buffer for frame data
 *
 * @return      TRUE if successful, else failed
 */

int Emac_SetRecvBufferExt
(
  uint8 emacIndex,
  uint8 queues
)
{
  int cnt;
  int queue;
  int index;
  for (queue =0; queue<queues; queue++) { //// be caution, currently all queues use same RFD buffer, dangerous
    for(cnt=0;cnt< drv[emacIndex].countRFD;cnt++) {
      /* Set each buffer one at at time into the rfd ring*/
      index = cnt + drv[emacIndex].countRFD*queue;
      if (Emac_SetRecvBuffer( emacIndex, queue,drv[emacIndex].rfdbuffer[index].vaddr) != TRUE) {
        EMAC_PRINT_2("Failed to set Receive buffer %d at queue %d\n", cnt,queue);
        return FALSE;
      }
    }
  }
  return TRUE;
}

/**
 * @brief       Set a single receive frame buffer at default RX queue (#0)
 *
 * @param[in]   buffer    Buffer for frame data
 *
 * @return      TRUE if successful, else failed
 */
int Emac_SetRecvBuffer
(
 IN uint8 emacIndex,
 IN uint8 queue,
 IN OUT uint8 *buffer
)
{
  uint32 rfdProdIdx;
  uint32 rfdConsInx;

  switch(queue) { // bad code here, just lazy. Need to write macro with parater base address
    case 0:
      if(emacIndex == 0){
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE(MAILBOX_3), RFD0_CONS_IDX);
      }
      else{
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_0), RFD0_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_3), RFD0_CONS_IDX);
      }
      break;
    case 1:
      if(emacIndex == 0){
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_5), RFD1_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE(MAILBOX_7), RFD1_CONS_IDX);
      }
      else{
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_5), RFD1_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_7), RFD1_CONS_IDX);
      }
      break;
    case 2:
      if(emacIndex == 0){
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_6), RFD2_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE(MAILBOX_7), RFD2_CONS_IDX);
      }
      else{
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_6), RFD2_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_7), RFD2_CONS_IDX);
      }
      break;
    case 3:
      if(emacIndex == 0){
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_13), RFD3_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE(MAILBOX_8), RFD3_CONS_IDX);
      }
      else{
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_13), RFD3_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_8), RFD3_CONS_IDX);
      }
      break;
    case 4:
      if(emacIndex == 0){
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE(MAILBOX_14), RFD4_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE(MAILBOX_8), RFD4_CONS_IDX);
      }
      else{
        rfdProdIdx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_14), RFD4_PROD_IDX);
        rfdConsInx = HWIO_INF(EMAC_REG_PRE1(MAILBOX_8), RFD4_CONS_IDX);
      }
      break;
  }

  if(rfdProdIdx == rfdConsInx) {
    EMAC_PRINT_2("RFD is empty idx=%d at queue=%d\r\n",rfdProdIdx,queue);
  }
  else if (drv[emacIndex].indexRFD[queue] == rfdConsInx) {
    EMAC_PRINT_1("RFD is Full, ConIDx=%d\r\n",rfdConsInx);
    return FALSE;
  }

  drv[emacIndex].isrfdFull = FALSE;

  if(NULL != buffer) {
    /* Get RFD ring base */
    RFD *ringRFD    = (RFD *)(void *)drv[emacIndex].ringRFD[queue].vaddr;
    RFD *currentRFD = &(ringRFD[drv[emacIndex].indexRFD[queue]]);



    if (NULL == buffer) {
      EMAC_PRINT_0("NULL RX buffer\r\n");
      return FALSE;   /* Failure */
    }

    /* Set buffer address. Size is always drv.sizeBufRX */
    currentRFD->BUF_ADDR_LO = (uint32)(uint64)buffer;
#ifdef EMAC1_FOR_IMC
    currentRFD->BUF_ADDR_HI = 0;
#else
    currentRFD->BUF_ADDR_HI = (uint32)((uint64)buffer >> 32);
#endif

    // {//debug output to check the consistent between allocated buf and received buf(at emac_snp.c)
    //   EMAC_PRINT_2("RX buffer queue buf low=%x, high=%x\r\n",currentRFD->BUF_ADDR_LO ,currentRFD->BUF_ADDR_HI );
    //   EMAC_PRINT_1("value = %d\r\n",*((uint8*)buffer));
    // }
  }//====>only update the producer when we get new buffer

 ++drv[emacIndex].indexRFD[queue];
    /* This API always uses RFD0 */
    /* RFD producer index is set to one index after the last produced index */
    switch(queue) {
      case 0:
        if(emacIndex == 0)
          HWIO_OUTF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        else
          HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_0), RFD0_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        break;
      case 1:
        if(emacIndex == 0)
          HWIO_OUTF(EMAC_REG_PRE(MAILBOX_5), RFD1_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        else
          HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_5), RFD1_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        break;
      case 2:
        if(emacIndex == 0)
          HWIO_OUTF(EMAC_REG_PRE(MAILBOX_6), RFD2_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        else
          HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_6), RFD2_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        break;
      case 3:
        if(emacIndex == 0)
          HWIO_OUTF(EMAC_REG_PRE(MAILBOX_13), RFD3_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        else
          HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_13), RFD3_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        break;
      case 4:
        if(emacIndex == 0)
          HWIO_OUTF(EMAC_REG_PRE(MAILBOX_14), RFD4_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        else
          HWIO_OUTF(EMAC_REG_PRE1(MAILBOX_14), RFD4_PROD_IDX, drv[emacIndex].indexRFD[queue]);
        break;
    }
 // }

  /* Advance RFD index */
  //++drv[emacIndex].indexRFD[queue];
  if (drv[emacIndex].indexRFD[queue] >= drv[emacIndex].countRFD) {
    drv[emacIndex].indexRFD[queue] = 0;
  }

  if(drv[emacIndex].indexRFD[queue] == rfdConsInx) {
    drv[emacIndex].isrfdFull = TRUE;
  }

  // adding a barrier to make sure the RFD is updated before emac reads it.
#if (__TARGET_ARCH_ARM >= 7)  || (__ARM_ARCH >= 7)
  __asm("dsb sy");
#endif

  return TRUE;       /* Success */
}

/**
 * @brief       Cleanup driver
 */
void Emac_Cleanup
(
  uint8 emacIndex
)
{
  uint32 cnt;

  /* Stop interrupts */
  if(emacIndex == 0){
    HWIO_OUT(EMAC_REG_PRE(INT_MASK), 0x0);   /* Mask default core interrupts */
    (void)HWIO_IN(EMAC_REG_PRE(INT_STATUS));/* Clear default core int status */
  }
  else{
    HWIO_OUT(EMAC_REG_PRE1(INT_MASK), 0x0);   /* Mask default core interrupts */
    (void)HWIO_IN(EMAC_REG_PRE1(INT_STATUS));/* Clear default core int status */
  }

  Emac_UnregisterCoreIsr();

  Emac_SleepMS(100);  /* In case ISR is running, allow some time to finish */

  /* Reset the core */
  if (TRUE != Emac_SwReset(emacIndex)) {
    /* SW reset failed. Force HW reset to make sure we stop HW */
    EMAC_PRINT_0("SW reset failed during cleanup, forcing HW reset\n");
  }

  /* Free TX rings allocated memory */
  for (cnt = 0; cnt < drv[emacIndex].txQueuesNum; cnt++) {
    Emac_FreeBuffer(&(drv[emacIndex].ringTPD[cnt]));
  }

  /* Free RX rings allocated memory */
  for (cnt = 0; cnt < drv[emacIndex].rxQueuesNum; cnt++) {
    Emac_FreeBuffer(&(drv[emacIndex].ringRFD[cnt]));
    Emac_FreeBuffer(&(drv[emacIndex].ringRRD[cnt]));
  }

  /* Free TPD buffers */
  for(cnt = 0; cnt < drv[emacIndex].countTPD; cnt++) {
    drv[emacIndex].tpdbuffersInt[cnt].size = EMAC_TX_BUF_SIZE;
    Emac_FreeBuffer(&(drv[emacIndex].tpdbuffersInt[cnt]));
  }

  /* Free RFD buffers */
  for(cnt = 0; cnt < drv[emacIndex].countRFD; cnt++) {
    Emac_FreeBuffer(&(drv[emacIndex].rfdbuffer[cnt]));
  }

  /* Clear driver struct */
  Emac_Memset(&drv[emacIndex], 0, sizeof(drv[emacIndex]));
}


/**
 * @brief           update emac status
 *
 * @return          None
 */

void Emac_UpdateStatus
(
 IN uint8 emacIndex,
 IN EMAC_STATE state
)
{
  boolean isLinkUp = FALSE;
  uint8 ephyaddr;

  drv[emacIndex].emacState = state;

  if(TRUE != Emac_PhyIsLinkUpSgmii(emacIndex, &isLinkUp)) {
    EMAC_PRINT_0("SGMII link check failed\r\n");
    return;
  }

  /*Setting the default value to FALSE*/
  drv[emacIndex].isLinkUp = FALSE;

  /* Enable auto polling */

  if(emacIndex == 0)
    ephyaddr = EMAC0_EPHY_ADDRESS;
  else
    ephyaddr = EMAC1_EPHY_ADDRESS;

  if (TRUE != Emac_SetEphyStatusAutoPoll(emacIndex, ephyaddr, TRUE))
  {
    EMAC_PRINT_0("Failed to enable auto-polling\r\n");
  }

  /*Notify the upper layer that link is up*/
  if( (drv[emacIndex].emacState == RUNNING) && (drv[emacIndex].isLinkUp)) {
    Emac_Notify(emacIndex, EMAC_LINK_UP);
  }
}

/**
 * @brief           Notify the upper layers that emac is ready
 *
 * @return          None
 */
  void Emac_Notify
(
 IN uint8 emacIndex,
 IN LINK_STATE linkStatus
 )
{
#ifdef EMAC1_FOR_IMC
  if (NULL != drv[emacIndex].emacUpNtfy){
    drv[emacIndex].emacUpNtfy(linkStatus);
  }
#endif
}

/**
 * @brief           Store the notifiers in globals until the drv is ready
 * 					Add it to drv if drv is up.
 *
 * @return          None
 */
  void Emac_AttachDrv
(
 IN uint8 emacIndex,
 IN EMAC_UP_NOTIFIER pEmacUpNtfy,
 IN EMAC_READ_CB pEmacRdCbk
 )
{
#ifdef EMAC1_FOR_IMC
  /* Update global notifiers in case drv is not up yet*/
  gEmacUpNtfy = pEmacUpNtfy;
  gEmacRdCbk = pEmacRdCbk;

  if(drv[emacIndex].emacState != NOT_INITIALIZED) {
    drv[emacIndex].emacUpNtfy = pEmacUpNtfy;
    drv[emacIndex].emacRdCbk = pEmacRdCbk;
  }

  if( (drv[emacIndex].emacState == RUNNING) && (drv[emacIndex].isLinkUp)) {
    Emac_Notify(emacIndex, EMAC_LINK_UP);
  }
#endif
}

/**
 * @brief       Return the size of the next packet to be ready
 *
 */
int Emac_PeekDataRd
(
 uint8 emacIndex
)
{
  uint32 procIndex;

  if(emacIndex == 0)
    procIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROC_IDX);
  else
    procIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_0), RFD0_PROC_IDX);

  RRD_TYPE_A *curRrdTypeABase = drv[emacIndex].curRrdTypeA[0];
  RRD_TYPE_A *curRrdProcPtr = (RRD_TYPE_A *)(curRrdTypeABase+procIndex);

  return  curRrdProcPtr->PKT_SIZE;
}

/**
 * @brief       Read packets from the mac internal buffers
 *
 * @param[in]   buffer    pointer to the buffer to read into
 * @param[in]   size      size of buffer
 *
 */
int Emac_Receive
(
 IN uint8 emacIndex,
 IN OUT uint8* buffer,
 IN int size
)
{
  uint32 procIndex;

  if(emacIndex == 0)
    procIndex = HWIO_INF(EMAC_REG_PRE(MAILBOX_0), RFD0_PROC_IDX);
  else
    procIndex = HWIO_INF(EMAC_REG_PRE1(MAILBOX_0), RFD0_PROC_IDX);

  Emac_Memcpy(buffer, drv[emacIndex].rfdbuffer[procIndex].vaddr, size);

  Emac_Memset(drv[emacIndex].rfdbuffer[procIndex].vaddr, 0, drv[emacIndex].rfdbuffer[procIndex].size);

  return size;
}
