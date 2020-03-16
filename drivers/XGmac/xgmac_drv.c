/**---------------------------------------------------------------------------
 * @file     xgmac_drv.c
 *
 * @brief    Core xgmac driver routines
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "xgmac_drv.h"
#include "xgmac_platform.h"

/*----------------------------------------------------------------------------
 * Definition Files
 *--------------------------------------------------------------------------*/
#define XGMAC_PRINT(...)      do {                                             \
  printf("Filename %s, Function %s, Line %d >", __FILE__, __FUNCTION__,        \
         __LINE__);                                                            \
  printf(__VA_ARGS__);                                                         \
}while(0)

/*----------------------------------------------------------------------------
 * Local variable
 *--------------------------------------------------------------------------*/
static XGMAC_COMMON_CFG_t xgmac_cfg; //workaroud here, i am lazy to change old code
/*
XGMAC_COMMON_CFG_t xgmac_def_cfg = {
    .modeLoopback   = MAC_LB,
    .mtu            = 1500,
    .txQueues       = 2,
    .txRingSize     = 8,
    .sizeBufTx      = 2048,
    .rxQueues       = 2,
    .rxRingSize     = 16,
    .sizeHdrBufRx   = 128,
    .sizePloadBufRx = 2048,
};
*/
/*Dangerous: using global variable. It needs mutex protection
to access it. For lazy, not protect now. Dangerous!!!
WHen multi-threads are used. You will get troubles*/
XGMAC_DRV_t xgmac_drv[2] = {{0}, {0}};

/*----------------------------------------------------------------------------
 * Function
 *--------------------------------------------------------------------------*/
//////////////////////got from IP
///team////////////////////////////////////////////

int xgmac_phy_init_from_IP(int mac_index, int loopback_mode) {
  /*mac init*/
  XGREG_WRITE(mac_index, NETWORK_CONTROL,
              0x0); // to enable transmit/receive, modify bits[2-3]
  XGREG_WRITE(mac_index, NETWORK_CONFIG, 0x002c0000); // to configure MDC clock,
                                                      // based on pclk=120Mhz.
                                                      // Where is pclk

  /*reset phy, phy init*/
  if (loopback_mode != MAC_LB) {
    // set GCCMW_XG0_PHY_RESET
    // PHY_L00
    /*
    PMA pma_100_pwr_en, macro_pwr_en
    PMA_CFG, XCVR_PLLCLK_EN_LN_0
    PHY_PMA_CMN_CTRL
    .....phy common, and lane register
    link training,
    PCSR
    */
  }

  /*
  #ifdef FAST_SIMULATION_MODE
  ....
  configure creq_spare_preg
  #endif
  */
  return 0;
}

////////////////////////////IP
///end///////////////////////////////////////////////
/**
 * @brief       Perform xgmac SW HW reset
 *
 * @return      TRUE if successful, else failed.
 */
/*TO be done. Use MACRO to replace function HWReset*/
#define XGMAC_GCCE_XGEM0_BCR 0xFF224B0000 //Where to get this value
void xgmac_HWReset(int mac_index)
{
  /*MAC+HOST controller Reset xgmac_mac_host_reset
   set GCCE_XGEM0_BCR[BLK_ARES]*/
  out_dword(XGMAC_GCCE_XGEM0_BCR + (mac_index*4), 1);
  //Do we need to sleep for a while
  xgmac_SleepMS(10);
  out_dword(XGMAC_GCCE_XGEM0_BCR + (mac_index*4), 0);
}

void xgmac_SoftReset(int mac_index)
{
  /*MAC+HOST controller Reset xgmac_mac_host_reset
   set GCCE_XGEM0_BCR[BLK_ARES]*/
  uint32_t temp;

  temp = XGREG_READ(mac_index, CTRL);
  temp = temp | 1; //write PAU, pause all transcation
  XGREG_WRITE(mac_index, CTRL, temp);
  xgmac_SleepMS(10);

  temp = XGREG_READ(mac_index, CTRL);
  while ((temp & 0x2) !=0 ) { //check QSC bit
    xgmac_SleepMS(10);//waiting for current transcation done
    temp = XGREG_READ(mac_index, CTRL);
  }
  out_dword(XGMAC_GCCE_XGEM0_BCR + (mac_index*4), 1);
    //Do we need to sleep for a while
  xgmac_SleepMS(10);
  out_dword(XGMAC_GCCE_XGEM0_BCR + (mac_index*4), 0);
}


uint32_t __xgmac_IntCheck(int mac_index, char* name, int offset)
{
  uint32_t i, bitIndex, bitMask, regValue;

  /*Tx pkt done check*/
  /*INTS0-3 indicate which Tx queue interrupt happens*/
  for (i=0; i<4; i++) {
    regValue = XGREG_READ_I(mac_index, INTS, (i + offset));
    bitMask = 1;
    for(bitIndex = 0; bitIndex<32; bitIndex++) {
      bitMask = bitMask << bitIndex;
      if (regValue & bitMask) {
        printf("%s interrupt happens on queue %d\n", name, bitIndex+32*i);
      }
    }
  }

  return regValue;
}

void xgmac_IntStatusCheck(int mac_index)
{
  /*Only focus on queue TX,Rx interrupt currently
   *Ignoreed INT_status to check LIKE link_fault
   *Also ignored all INT_enable\disable\mask TO enable those interrupts*/

  uint32_t reg_tx, reg_rx;
  /*INTS0-3 indicate which Tx queue interrupt happens*/
  reg_tx = __xgmac_IntCheck(mac_index, "Tx", 0);

  /*INTS4-7 indicate which Rx queue interrupt happens*/
  reg_rx = __xgmac_IntCheck(mac_index, "Rx", 4);

  __xgmac_IntCheck(mac_index, "Tx ur", 8);
  __xgmac_IntCheck(mac_index, "Rx ur", 12);
  __xgmac_IntCheck(mac_index, "Tx dma err", 16);
  __xgmac_IntCheck(mac_index, "Rx dma err", 20);
}

int xgmac_CoreConfig(int mac_index, XGMAC_CFG_t* self_conf)
{
  uint32_t regValue;

  if (NULL == self_conf)
    return false;

  regValue = XGREG_READ(mac_index, NETWORK_CONFIG);
  if (self_conf->isRx1536Bytes) {
    /*network bits[4]=1 means promiscuous*/
    regValue = xgmac_configReg_field(regValue, 8, 1, 1);
    // xgmac_regwrite_field(mac_index, NETWORK_CONFIG, 0, 8, 1, 1);
  } else {
    regValue = xgmac_configReg_field(regValue, 8, 1, 0);
    // xgmac_regwrite_field(mac_index, NETWORK_CONFIG, 0, 8, 1, 0);
  }

  if (self_conf->isPromiscuous) {
    /*network bits[4]=1 means promiscuous*/
    regValue = xgmac_configReg_field(regValue, 4, 1, 1);
    // xgmac_regwrite_field(mac_index, NETWORK_CONFIG, 0, 4, 1, 1);
  } else {
    regValue = xgmac_configReg_field(regValue, 4, 1, 1);
    // xgmac_regwrite_field(mac_index, NETWORK_CONFIG, 0, 4, 1, 0);
  }

  if (self_conf->isRxJumboEn) {
    /*network bits[3]=1 means Rx jumbo frame*/
    regValue = xgmac_configReg_field(regValue, 3, 1, 1);
    // xgmac_regwrite_field(mac_index, NETWORK_CONFIG, 0, 3, 1, 1);
  } else {
    regValue = xgmac_configReg_field(regValue, 3, 1, 1);
    // xgmac_regwrite_field(mac_index, NETWORK_CONFIG, 0, 3, 1, 0);
  }

  if (self_conf->isManPortEn) {
    regValue = xgmac_configReg_field(regValue, 4, 1, 1);
    // xgmac_regwrite_field(mac_index, NETWORK_CONTROL, 0, 4, 1, 1); //Do we
    // need to set control reg here
  }

  if (self_conf->isRxCSEn) { // Rx checksum enable, frame drop when receive bad
                             // checksum
    regValue = xgmac_configReg_field(regValue, 24, 1, 1);
    // xgmac_regwrite_field(mac_index, NETWORK_CONTROL, 0, 24, 1, 1);
  } else {
    regValue = xgmac_configReg_field(regValue, 24, 1, 1);
    // xgmac_regwrite_field(mac_index, NETWORK_CONTROL, 0, 24, 1, 0);
  }
  XGREG_WRITE(mac_index, NETWORK_CONFIG, regValue);

  if (self_conf->isHSplitEn) {                         // Configure RXC here???
    xgmac_regwrite_field(mac_index, RXC, 0, 31, 1, 1); // Enable HSE
  } else {
    xgmac_regwrite_field(mac_index, RXC, 0, 31, 1, 0);
  }

  return true;
}

int xgmac_CoreInit(int mac_index, XGMAC_CFG_t* mac_selfcfg) {

  /*Need to remove global var in the future, I am too lazy now*/
  xgmac_cfg = (XGMAC_COMMON_CFG_t)(*(XGMAC_COMMON_CFG_t*)mac_selfcfg);

  // sequence
  /*
  1.  Mask all interrupts to disable them until config is done
  2. Disable TX and RX until initialization is complete
  3. set the MAC Address
  4. Check for half duplex
  5. Enable status clear-on-read
  6.
  */
  //call xgmac_config_macaddr(), at first, configure the mac address

  /*NETWORK_CONTROL = 0 will disable transmit and receive, when tx/rx is done
   *enable tx/Rx again, NETWORK_CONTROL=0xc*/
  XGREG_WRITE(mac_index, NETWORK_CONTROL, 0);

  /*Based on pllclk, configure the MDC clock division here, since PCLK up to 120Mhz, so divide =3
   *final clock is 120/48 < 2.5Mhz*/
  XGREG_WRITE(mac_index, NETWORK_CONFIG, 0x2c0000);

  /*No need to check NETWORK_STATUS HERE, link interruption detection
   *no for INT_STATUS, ?management_frame_send
   *no for INT_ENABLE, ?management_frame_sent
   *no for INT_DISABLE, ?management_frame_sent
   *no for phy_management, no MDIO currently
   */
  /*
  XGREG_READ(mac_index,NETWORK_STATUS);
  XGREG_READ(mac_index,INT_STATUS);
  XGREG_READ(mac_index,INT_ENABLE);
  XGREG_READ(mac_index,INT_DISABLE);
  XGREG_READ(mac_index,INT_MASK);
  XGREG_READ(mac_index,PHY_MANAGEMENT);
  */
  XGREG_WRITE(mac_index,JUMBO_MAX_LENGTH,xgmac_off_def[JUMBO_MAX_LENGTH].reg_default);
  XGREG_WRITE(mac_index,NETWORK_CONFIG2,xgmac_off_def[NETWORK_CONFIG2].reg_default);

  XGREG_WRITE(mac_index, PCICR2, 1); // Configure PCICR2[BME] bus master enable

  xgmac_CoreConfig(mac_index, mac_selfcfg);//Just for test now, need to use real cfg future.
  /* Initialize and set Rx complete and Rx descriptor rings */
  if (true != xgmac_InitRxRings(mac_index)) {
    XGMAC_PRINT("RX rings initialization failed\r\n");
    return false;
  }

  /* Initialize and set Tx offload, continue rings */
  if (true != xgmac_InitTxRings(mac_index)) {
    XGMAC_PRINT("TX rings initialization failed\r\n");
    return false;
  }
  XGMAC_PRINT("init success with mac %d\n", mac_index);

  /*Everything is done, enable Tx, Rx now*/
  XGREG_WRITE(mac_index, NETWORK_CONTROL, 0xC);

  return true;
}


bool xgmac_update_rxRDPI(uint8_t mac_index, uint8_t queue,
                         uint32_t rx_SRI, uint32_t rx_NOR)
{
  uint32_t rxRDPI, rxRDCI, index;
  rxRDPI = XGREG_READ_I(mac_index, RDPI, queue);
  rxRDCI = XGREG_READ_I(mac_index, RDCI, queue);

  XGMAC_PRINT("queue %d, RDPI=%d, RDCI=%d, SRI=%d, NOR=%d\n",
                queue,rxRDPI,rxRDCI, rx_SRI, rx_NOR);

  for (index=0; index<rx_NOR; index++) {
    rxRDPI++;
    if (xgmac_cfg.rxRingSize == rxRDPI)
      rxRDPI = 0;

    XGREG_WRITE_I(mac_index, RDPI, queue, rxRDPI);
  }
  return true;
}
/**
 * @brief       Receive a single frame based on completion description
 *
 * @param[in]   queue         queue number
 * @param[out]  length        Buffer data length in bytes
 * @param[out]  buffer        Buffer data //Is memcpy allowed to be used here. Performance???
 *
 * @return      TRUE if successful, else failed
 *
 * Description: This is the simplest frame receive situation. no offload...
 *
 */
bool xgmac_Recv(uint8_t mac_index, uint8_t queue,
                uint8_t *buffer,   uint32_t* length)
{
  struct rx_comp_desc_t     *curRxCompDesc;
  struct rx_desc_t          *curRxDesc;
  uintptr_t *curPayloadBuf;
  uintptr_t *curHdrBuf;
  uint8_t   *rxBuf;

  uint32_t    rxCompRingIndex, rxBufIndex;
  uint32_t    index, rxSRI, rxNOR, rxRDCI, rxLength;
  bool        headSplit;

  //WIll use memcpy to copy data from Rx ring to outside buffer
  //It is the simplest way, but performance will be affected

  curRxCompDesc   = (struct rx_comp_desc_t *)xgmac_drv[mac_index].rxCompDesc[queue];
  rxCompRingIndex = xgmac_drv[mac_index].rxCompDesc_index[queue];
  curRxCompDesc   += rxCompRingIndex;

  if (curRxCompDesc->POL != 1) {
    XGMAC_PRINT("no data received at queue=%d\n", queue);
    return false;
  }

  rxCompRingIndex++;
  if (xgmac_cfg.rxRingSize == rxCompRingIndex)
    rxCompRingIndex = 0;
  xgmac_drv[mac_index].rxCompDesc_index[queue] = rxCompRingIndex;

  curPayloadBuf = xgmac_drv[mac_index].rxPloadBuf[queue];
  curHdrBuf     = xgmac_drv[mac_index].rxHdrBuf[queue];

  rxSRI       = curRxCompDesc->SRI;//should equal to RDCI
  rxNOR       = curRxCompDesc->NOR;
  headSplit   = curRxCompDesc->HS;


  rxBufIndex    = rxSRI;//xgmac_drv[mac_index].rxBuf_index[queue];
  curPayloadBuf += rxBufIndex;
  curHdrBuf     += rxBufIndex;

  //suppose SRI, xgmac_drv[mac_index].rxBuf_index[queue], RDCI are equal checking
  rxRDCI = XGREG_READ_I(mac_index, RDCI, queue);
  XGMAC_PRINT("Rx consumer index=%d, %d, %d\n", rxSRI, xgmac_drv[mac_index].rxBuf_index[queue], rxRDCI);

  xgmac_drv[mac_index].rxBuf_index[queue] = rxSRI;
  for (index = 0; index < rxNOR; index) {
    xgmac_drv[mac_index].rxBuf_index[queue]++;
    if (xgmac_drv[mac_index].rxBuf_index[queue] == xgmac_cfg.rxRingSize)
      xgmac_drv[mac_index].rxBuf_index[queue] = 0;
  }

  rxLength = 0;
  rxBuf    = buffer;

  if (headSplit) {
    //I am supossing RXC[HDS] is larger than HDRLEN, dangreous
    if(curRxCompDesc->HDRLEN < *length) {
      memcpy(rxBuf, curHdrBuf, curRxCompDesc->HDRLEN);
      *length   -= curRxCompDesc->HDRLEN;
      rxLength += curRxCompDesc->HDRLEN;
    } else {
      XGMAC_PRINT("Rx recv buffer is too small. less than hdr %d\n", length);
    }
  }

    for (index = 0; index < rxNOR; index) {
      rxBuf = buffer + rxLength;
      if (*length > curRxCompDesc->PKTLEN) {
        memcpy(rxBuf, curPayloadBuf, curRxCompDesc->PKTLEN);
        *length   -= curRxCompDesc->PKTLEN;
        rxLength += curRxCompDesc->PKTLEN;
        curPayloadBuf++;
      } else {
      XGMAC_PRINT("Rx recv buffer is too small. less than payload %d\n", length);
      }
    }
  xgmac_drv[mac_index].rxCompDesc_index[queue]++;

#if (__TARGET_ARCH_ARM >= 7)  || (__ARM_ARCH >= 7)
  __asm("dsb sy");
#endif

  //we are re-using pre-allocated rx buffer, only need to update RDPI,RDCI
  //No need to allocate new memory
  xgmac_update_rxRDPI(mac_index, queue, rxSRI, rxNOR);

  *length = rxLength;
  return true;
}



/**
 * Frame transmit steps:
 * 1: The caller call xgmac_GetTxOffloadDesc( ) and configure tx offload desc based on
 * Mac, IP, L4 header length, IVLAN, OVLAN, L4 type, IP version, and mss
 * 2. The caller call xgmac_Send( ) to transmit the packet.
 *
 */

/**
 * @brief       Get the tx offload desc
 *
 * Description: Dangerous!!! we will suppose caller uses this function to get
 * Tx offload desriptor and configure it.
 */
struct tx_offload_desc_t * xgmac_GetTxOffloadDesc(uint8_t mac_index, uint8_t queue)
{
    struct tx_offload_desc_t *curTxOffloadDesc;
    uint32_t                  txRingIndex; /*based TDPI or based on xgdrv. txDesc_index[Q_Index]*/

    curTxOffloadDesc = (struct tx_offload_desc_t *)xgmac_drv[mac_index].txDesc[queue];
    txRingIndex = xgmac_drv[mac_index].txDesc_index[queue];
    curTxOffloadDesc += txRingIndex;

    memset(curTxOffloadDesc, 0 , sizeof(struct tx_offload_desc_t));
    curTxOffloadDesc->Type = 1;

    txRingIndex++;
    if (txRingIndex == xgmac_cfg.txRingSize)
        txRingIndex = 0;

#if (__TARGET_ARCH_ARM >= 7)  || (__ARM_ARCH >= 7)
  __asm("dsb sy");
#endif

    xgmac_drv[mac_index].txDesc_index[queue] = txRingIndex;
    XGREG_WRITE_I(mac_index, TDPI, queue, txRingIndex);

    return curTxOffloadDesc;
}

void xgmac_ConfigOffload(uint8_t mac_Index, uint8_t queue,
                         XGMAC_CFG_t *mac_selfcfg) {
  struct tx_offload_desc_t *TxOffloadDesc;
  /*Need to find better way to config Tx offload descriptor*/
  TxOffloadDesc = xgmac_GetTxOffloadDesc(mac_Index, queue);
  // configure offload descriptor, not good, need to configure descriptor
  // outside mac_drv.c
  TxOffloadDesc->Type = 1;
  TxOffloadDesc->MacHdrLen = mac_selfcfg->L2HdrLen;
  TxOffloadDesc->IPHdrLen = mac_selfcfg->L2HdrLen;
  TxOffloadDesc->L4HdrLen = mac_selfcfg->L2HdrLen;
  TxOffloadDesc->IPV = 0; // 1 means IPv6

  if (mac_selfcfg->isTCP)
    TxOffloadDesc->L4T = 1; // TCP
  else
    TxOffloadDesc->L4T = 0; // UDP

  TxOffloadDesc->MSS = mac_selfcfg->defCfg.mtu - TxOffloadDesc->IPHdrLen -
                       TxOffloadDesc->L4HdrLen;
}
/**
 * @brief       Transmit a single frame base tx desc or tx_cont desc
 *
 * @param[in]   Type        2 is for Tx desc; 3 is for Tx cont
 * @param[in]   length      Buffer data length in bytes
 *
 * @return      TRUE if successful, else failed
 *
 * Description: This is the simplest frame transmit situation. On offload,
 * only support one buffer, on continue desc
 * In the future, should support several buffers(buf list), offload, cont
 * It supposes that txOffload Desc has been configured by caller, dangerous
 *
 */
bool xgmac_Send_Tx(uint8_t mac_index, uint8_t queue, uint8_t *buffer,
                   uint32_t length, XGMAC_CFG_t *mac_SelfConfig) {
  // Parse the packet  to get mac, ip, l4 header length
  // PacketParse( )
  struct tx_desc_t *curTxDesc;
  uint32_t txRingIndex; /*based TDPI or based on xgdrv. txDesc_index[Q_Index]*/
  uint64_t buff_phy;
  uint32_t headerLen, pyldLen;

  if ((queue > XG_QUEUES) || (NULL == buffer))
    return false;
  if (!xgmac_IsBufAligned(buffer))
    return false;
  xgmac_ConfigOffload(mac_index, queue, mac_SelfConfig);

  // txRingIndex = XGREG_READ_I(mac_index, TDPI, queue);
  txRingIndex = xgmac_drv[mac_index].txDesc_index[queue];

  curTxDesc = (struct tx_desc_t *)xgmac_drv[mac_index].txDesc[queue];
  memset(curTxDesc, 0, sizeof(struct tx_desc_t));

  curTxDesc += txRingIndex;

  buff_phy = xgmac_GetPhyAddr(buffer);

  headerLen = mac_SelfConfig->L2HdrLen + mac_SelfConfig->L3HdrLen +
              mac_SelfConfig->L4HdrLen;
  pyldLen = length - headerLen;

  curTxDesc->Type = 2;
  curTxDesc->EOP = 1;
  curTxDesc->TXBufLen = length;
  curTxDesc->PyldLen = pyldLen;
  curTxDesc->TxBuffAddr_l = (uint32_t)buff_phy;
  curTxDesc->TxBuffAddr_h = (uint32_t)(buff_phy >> 32);

  txRingIndex++;
  if (txRingIndex == xgmac_cfg.txRingSize)
    txRingIndex = 0;

  if (mac_SelfConfig) {
    if (mac_SelfConfig->isL3CSEn)
      curTxDesc->L3CS = 1;
    else
      curTxDesc->L3CS = 0;

    if (mac_SelfConfig->isL4CSEn)
      curTxDesc->L4CS = 1;
    else
      curTxDesc->L4CS = 0;

    if ((mac_SelfConfig->isTCPSegOffloadEn) && (length > xgmac_cfg.mtu)) {
      /*TSO configuration*/
      /*Update previous Tx descriptor, end of packet is not 0 now, payload
       * length update*/
      curTxDesc->TSO = 1;
    } // End of segment TSO feature

    if ((mac_SelfConfig->isSGEn) && (length > xgmac_cfg.mtu)) {
      /*Normally SG feature is not related to buffer size, just use to speed up
       *discrete memory. In this case, just for a function validation. SG should
       *co-work
       *with Rx header buffer split feature*/
      /*Configure Tx Cont Descriptor*/
      uint64_t next_buffphy;
      uint32_t TXBufLen, bufNum, i, lastBUfLen;
      struct tx_cont_desc_t *curContTxDesc;

      bufNum = length / xgmac_cfg.mtu;
      lastBUfLen = length % xgmac_cfg.mtu;
      TXBufLen = xgmac_cfg.mtu;
      /*Update last Tx Descriptor*/
      curTxDesc->EOP = 0;
      curTxDesc->TXBufLen = TXBufLen;

      /*Get the buffer offset for segment*/
      next_buffphy = buff_phy + TXBufLen;
      /*Configure the Tx continue descriptor now
       *Caution: Lazy, not checking if ring descriptor is enough for use?
       **/
      curContTxDesc =
          (struct tx_cont_desc_t *)xgmac_drv[mac_index].txDesc[queue];
      curContTxDesc += txRingIndex;

      for (i = 0; i < (bufNum - 1);
           i++) { // bufNum-1 since Tx desc has consumed 1
        curContTxDesc->Type = 3;
        curContTxDesc->EOP = 0;
        curContTxDesc->TXBufLen = TXBufLen;
        curContTxDesc->TxBuffAddr_l = (uint32_t)next_buffphy;
        curContTxDesc->TxBuffAddr_h = (uint32_t)(next_buffphy >> 32);
        next_buffphy += TXBufLen;
        curContTxDesc++;
        txRingIndex++;
        if (txRingIndex == xgmac_cfg.txRingSize)
          txRingIndex = 0;
      }

      if (lastBUfLen != 0) {
        curContTxDesc->Type = 3;
        curContTxDesc->EOP = 1;
        curContTxDesc->TXBufLen = lastBUfLen;
        curContTxDesc->TxBuffAddr_l = (uint32_t)next_buffphy;
        curContTxDesc->TxBuffAddr_h = (uint32_t)(next_buffphy >> 32);
        txRingIndex++;
        if (txRingIndex == xgmac_cfg.txRingSize)
          txRingIndex = 0;
      } else {
        curContTxDesc->EOP = 1;
      } // End of scatter/gather
    }
  } // ENd of mac_config setting

/*barrior to make sure data configure is done before firing*/
#if (__TARGET_ARCH_ARM >= 7)  || (__ARM_ARCH >= 7)
  __asm("dsb sy");
#endif

    xgmac_drv[mac_index].txDesc_index[queue] = txRingIndex;
    XGREG_WRITE_I(mac_index, TDPI, queue, txRingIndex);

    return true;
}

int xgmac_RxBufExt(int mac_index)
{
    int Q_Index, Ring_Index;

    struct rx_desc_t        *curRxDesc;
    uintptr_t               *hdr_ptr;
    uintptr_t               *payload_ptr;
    uint64_t                hdr_phyaddr, payload_phyaddr;

    uint8_t  Queues       = xgmac_cfg.rxQueues;
    uint32_t RingSize     = xgmac_cfg.rxRingSize;

    for (Q_Index = 0; Q_Index < Queues; Q_Index++) {
        curRxDesc     = (struct rx_desc_t*)xgmac_drv[mac_index].rxDesc[Q_Index];

        hdr_ptr       = xgmac_drv[mac_index].rxHdrBuf[Q_Index];
        hdr_phyaddr   = xgmac_GetPhyAddr(hdr_ptr);
        payload_ptr   = xgmac_drv[mac_index].rxPloadBuf[Q_Index];
        payload_phyaddr = xgmac_GetPhyAddr(payload_ptr);

        for (Ring_Index = 0; Ring_Index<RingSize; Ring_Index++) {
            curRxDesc->RxHdrBufAddr_h = (uint32_t)(hdr_phyaddr>>32);
            curRxDesc->RxHdrBufAddr_l = (uint32_t)hdr_phyaddr;
            curRxDesc->RxPktBufAddr_h = (uint32_t)(payload_phyaddr>>32);
            curRxDesc->RxPktBufAddr_l = (uint32_t)payload_phyaddr;
            #if (__TARGET_ARCH_ARM >= 7)  || (__ARM_ARCH >= 7)
            __asm("dsb sy");
            #endif
            curRxDesc++;
            hdr_phyaddr++;
            payload_phyaddr++;
            XGREG_WRITE_I(mac_index, RDPI, Q_Index, Ring_Index); //??? which value, +1 requried?
        }
    }

    return true;
}

int xgmac_InitRxRings(int mac_index)
{
  int Q_Index, Q_free;

  uint64_t RxDescPhyAddr;
  uint8_t  Queues       = xgmac_cfg.rxQueues;
  uint32_t RingSize     = xgmac_cfg.rxRingSize;
  uint32_t BufSize      = xgmac_cfg.sizePloadBufRx;
  uint32_t HdrBufSize   = xgmac_cfg.sizeHdrBufRx;

  for (Q_Index = 0; Q_Index < Queues; Q_Index++) {
    xgmac_drv[mac_index].rxDesc_index[Q_Index] = 0;

    xgmac_drv[mac_index].rxDesc[Q_Index] = (uintptr_t *)xgmac_AllocBuffer(sizeof(struct rx_desc_t) * RingSize, RX_DESC_ALIGN);
    if (NULL == xgmac_drv[mac_index].rxDesc[Q_Index]) {
      XGMAC_PRINT("10Gmac rx desc allocation failed at queue %d\n", Q_Index);
      goto exit1;
    } else {
      /*Update Rx Descriptor ring address*/
      RxDescPhyAddr = xgmac_GetPhyAddr(xgmac_drv[mac_index].rxDesc[Q_Index]);
      XGREG_WRITE_I(mac_index, RDBAL, Q_Index, (uint32_t)RxDescPhyAddr);
      XGREG_WRITE_I(mac_index, RDBAH, Q_Index, (uint32_t)(RxDescPhyAddr >> 32));
      XGREG_WRITE_I(mac_index, RDLEN, Q_Index, RingSize);
    }

    xgmac_drv[mac_index].rxBuf_index[Q_Index] = 0;
    xgmac_drv[mac_index].rxPloadBuf[Q_Index]  = (uintptr_t *)xgmac_AllocBuffer(BufSize * RingSize, RX_DESC_ALIGN);
    if (NULL == xgmac_drv[mac_index].rxPloadBuf[Q_Index]) {
      XGMAC_PRINT("10Gmac rx buff allocation failed at queue %d\n", Q_Index);
      goto exit2;
    }

    xgmac_drv[mac_index].rxHdrBuf[Q_Index] = (uintptr_t *)xgmac_AllocBuffer(HdrBufSize * RingSize, RX_DESC_ALIGN);
    if (NULL == xgmac_drv[mac_index].rxHdrBuf[Q_Index]) {
      XGMAC_PRINT("10Gmac rx header buff allocation failed at queue %d\n",Q_Index);
      goto exit3;
    }

    xgmac_drv[mac_index].rxCompDesc_index[Q_Index] = 0;
    xgmac_drv[mac_index].rxCompDesc[Q_Index] = (uintptr_t *)xgmac_AllocBuffer(sizeof(struct rx_comp_desc_t) * RingSize, RX_DESC_ALIGN);
    if (NULL == xgmac_drv[mac_index].rxCompDesc[Q_Index]) {
      XGMAC_PRINT("10Gmac rx competion descriptor allocation failed at queue %d\n",Q_Index);
      goto exit4;
    } else {
      /*Update Rx Descriptor ring address*/
      RxDescPhyAddr = xgmac_GetPhyAddr(xgmac_drv[mac_index].rxCompDesc[Q_Index]);
      XGREG_WRITE_I(mac_index, RCBAL, Q_Index, (uint32_t)RxDescPhyAddr);
      XGREG_WRITE_I(mac_index, RCBAH, Q_Index, (uint32_t)(RxDescPhyAddr >> 32));
    }
    }

#if (__TARGET_ARCH_ARM >= 7)  || (__ARM_ARCH >= 7)
  __asm("dsb sy");
  __asm("isb sy");
#endif
#if 0
    {//Configure RXC here???
      uint32_t rxc_value;
      //Disable Header split currently, header=128bytes, buff=2k
      rxc_value = ((1<<4) & 0x10) | 1;
      XGREG_WRITE(mac_index, RXC, rxc_value);
      //Configure RXC[RBS], rx buffer size, default 1 (2k)
      //Configure RXC[HBS], rx header buffer size, default 0
      //Configure RXC[HSE], header split
    }
#endif
  xgmac_RxBufExt(mac_index);

  { // Enable mac receive here?
    uint32_t network_control;
    network_control = XGREG_READ(mac_index, NETWORK_CONTROL);

    network_control = network_control | ((1 << 2) & 0xF);
    XGREG_WRITE(mac_index, NETWORK_CONTROL, network_control);
  }

  return true;
exit4:
  for (Q_free = 0; Q_free < Queues; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxDesc[Q_Index]));
  }
  for (Q_free = 0; Q_free < Queues; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxPloadBuf[Q_Index]));
  }
  for (Q_free = 0; Q_free < Queues; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxHdrBuf[Q_Index]));
  }
  for (Q_free = 0; Q_free < Q_Index; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxCompDesc[Q_Index]));
  }
  return false;
exit3:
  for (Q_free = 0; Q_free < Queues; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxDesc[Q_Index]));
  }
  for (Q_free = 0; Q_free < Queues; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxPloadBuf[Q_Index]));
  }
  for (Q_free = 0; Q_free < Q_Index; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxHdrBuf[Q_Index]));
  }
  return false;

exit2:
  for (Q_free = 0; Q_free < Queues; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxDesc[Q_Index]));
  }
  for (Q_free = 0; Q_free < Q_Index; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxPloadBuf[Q_Index]));
  }
  return false;
exit1:
  for (Q_free = 0; Q_free < Q_Index; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].rxDesc[Q_Index]));
  }
  return false;
}

int xgmac_InitTxRings(int mac_index) {

  int Q_Index, Q_free;
  uint8_t Queues = xgmac_cfg.txQueues;
  uint32_t RingSize = xgmac_cfg.txRingSize;
  uint32_t BufSize = xgmac_cfg.sizeBufTx;
  uint64_t TxDescPhyAddr;

  for (Q_Index = 0; Q_Index < Queues; Q_Index++) {
    xgmac_drv[mac_index].txDesc_index[Q_Index] = 0;

    xgmac_drv[mac_index].txDesc[Q_Index] = (uintptr_t *)xgmac_AllocBuffer(
        sizeof(struct tx_desc_t) * RingSize, TX_DESC_ALIGN);
    if (NULL == xgmac_drv[mac_index].txDesc[Q_Index]) {
      XGMAC_PRINT("10Gmac tx desc allocation failed at queue %d\n", Q_Index);
      goto exit1;
    } else {
      /*Update Tx Descriptor ring address*/
      TxDescPhyAddr = xgmac_GetPhyAddr(xgmac_drv[mac_index].txDesc[Q_Index]);
      XGREG_WRITE_I(mac_index, TDBAL, Q_Index, (uint32_t)TxDescPhyAddr);
      XGREG_WRITE_I(mac_index, TDBAH, Q_Index, (uint32_t)(TxDescPhyAddr >> 32));
      XGREG_WRITE_I(mac_index, TDLEN, Q_Index, RingSize);

      //  XGREG_WRITE_I(mac_index, TDPI, Q_Index, RingSize-1);
      /* Can set TDPI like this way, or need to configure it one by one
       * TDPI + 1 - length = TDCI now, means ring full*/
    }

    // xgmac_drv[mac_index].txBuf_index[Q_Index] = 0;  /*Do we really need Tx
    // buffer allocate here*/
    // xgmac_drv[mac_index].txBuf[Q_Index] =
    // (uintptr_t*)xgmac_AllocBuffer(BufSize * RingSize,TX_DESC_ALIGN);
    // if (NULL == xgmac_drv[mac_index].txBuf[Q_Index]) {
    //     XGMAC_PRINT("10Gmac tx buff allocation failed at queue %d\n",
    //     Q_Index);
    //     goto exit2;
    // }
  }

    {//Enable mac transmit here?
      uint32_t network_control;
      network_control = XGREG_READ(mac_index, NETWORK_CONTROL);

      network_control = network_control | ((1<<3)&0xF);
      XGREG_WRITE(mac_index, NETWORK_CONTROL, network_control);
    }
  return true;

// exit2:
//     for (Q_free=0; Q_free<Queues; Q_free++) {
//         xgmac_free((void*)(xgmac_drv[mac_index].txDesc[Q_Index]));
//     }
//     for (Q_free=0; Q_free<Q_Index; Q_free++) {
//         xgmac_free((void*)(xgmac_drv[mac_index].txBuf[Q_Index]));
//     }
//     return false;
exit1:
  for (Q_free = 0; Q_free < Q_Index; Q_free++) {
    xgmac_free((void *)(xgmac_drv[mac_index].txDesc[Q_Index]));
  }
  return false;
}

void xgmac_config_macaddr(int mac_index, uint8_t* mac)
{
  uint32_t mac_temp;

  mac_temp = 0;
  mac_temp = (mac[0] | (mac[1]<<8) | (mac[2]<<16) | (mac[3]<<24));
  XGREG_WRITE(mac_index, MAL, mac_temp);

  mac_temp = 0;
  mac_temp = (mac[4]) | (mac[5]<<8);
  XGREG_WRITE(mac_index, MAH, mac_temp);
}

void xgmac_config_loopback(int mac_index, enum XG_LB_MODE lb_mode)
{
  uint8_t temp;
  temp = 0;

  if (MAC_DUPLEX_LB == lb_mode) {
    temp = 1<<4;
  } else if (MAC_LB == lb_mode) {
    temp = 1;
  }

  XGREG_WRITE(mac_index, LBCTRL, temp);
}

int xgmac_clock(void) { return true; }

/*----------------------------------------------------------------------------
 * XGmac PHY part
 *--------------------------------------------------------------------------*/
int xgmac_phy_reset(int mac_index) {
  // stub function, will focus on loopback currently 2019.2.22
  /*
  1. reset GCCMW_XG0_PHY_reset
  2. pma config
  3. Config phy common register and lane register
  */
  #define XG_PHY_L00_RESETR (0xFF012D0048 + mac_index*8) //where to get it.
  #define XG_PHY_RESETR  (0xFF012D004c + mac_index*8) //where to get it.
 // #define GCCMW_XG1_PHY_RESETR  0xFF012D0050 //Self define temporarily
  out_dword(XG_PHY_RESETR,1);
  out_dword(XG_PHY_L00_RESETR,1);
  //*********
  //miss phy configuration here pma....
  //*********

  //xgmac_phy_release_check
  out_dword(XG_PHY_RESETR,1);     //0 or 1??
  out_dword(XG_PHY_L00_RESETR,1);
  return true;
}

int xgmac_link(void) { return true; }

int xgmac_PCSR(void) { return true; }

int xgmac_fast_simulation(void) {
  // stub function, will focus on loopback currently 2019.2.22
  /*

  */
  return true;
}

int xgmac_phy_clock(void) { return true; }

/*----------------------------------------------------------------------------
 * external PHY part
 *--------------------------------------------------------------------------*/