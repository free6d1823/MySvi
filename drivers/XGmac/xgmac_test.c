/**---------------------------------------------------------------------------
 * @file    xgmac_test.c
 *
 * @brief    test cases fro xgmac driver
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//#include "xgmac0.h" /*So huge, terrible*/

#include "xgmac_drv.h"
#include "xgmac_util.h"
#include "xgmac_platform.h"

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

/*----------------------------------------------------------------------------
 * Global Data Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * functions
 *--------------------------------------------------------------------------*/

/**
 * @brief       Perform EMAC SW reset test
 *
 * @ mac_index  index for the xgmac
 *
 * @return      TRUE if successful, else failed.
 */
bool xgmac_por_test(int mac_index)
{
  uint32_t index;
  bool ret;

  uint32_t xgmac_size = sizeof(xgmac_off_def) / sizeof(xgmac_off_def[0]);
  ret = true;

  for (index = 0; index < xgmac_size; index++) {
    if (in_dword(xgmac_base[mac_index] + xgmac_off_def[index].reg_offset) !=
        xgmac_off_def[index].reg_default) {
      printf("XGmac reg Power reset failure at index %d, offset=%d\n", index,
             xgmac_off_def[index].reg_offset);
      ret = false;
      break;
    }
  }
  return ret;
}

#define PKTLENGTH 1024
#define PKTTOTAL  1600
static uint8_t packetBuf[PKTTOTAL]; //HOPE bss is large enough

#if 0
void xgmac_ConfigOffload(uint8_t mac_Index, uint8_t queue, XGMAC_CFG_t* mac_selfcfg)
{
    bool ret;
    struct tx_offload_desc_t* TxOffloadDesc;
   /*Need to find better way to config Tx offload descriptor*/
	TxOffloadDesc = xgmac_GetTxOffloadDesc(mac_Index, queue);
	// configure offload descriptor, not good, need to configure descriptor outside mac_drv.c
	TxOffloadDesc->Type = 1;
    TxOffloadDesc->MacHdrLen = GetMacHdr();
    TxOffloadDesc->IPHdrLen = GetIPHdr();
    TxOffloadDesc->L4HdrLen = GetTCPHdr();
    TxOffloadDesc->IPV = 0;
    TxOffloadDesc->L4T = 0; // UDP

    if (mac_selfcfg->isIpv4CSEn)
	    TxOffloadDesc->IPV = 0; // IPV4
    if (mac_selfcfg->isIpV6CSEn)
        TxOffloadDesc->IPV = 1; // IPV6

    if (mac_selfcfg->isTCPCSEn)
	    TxOffloadDesc->L4T = 1; // TCP
    if (mac_selfcfg->isUDPCSEn)
        TxOffloadDesc->L4T = 0; // UDP
}
#endif

/**
 * @brief       simple function to send/recv one buf
 *
 * @param[in]      sendBuf   buffer needs to send out
 * @param[in\out]  length   [in]length for sendbuf, [out]recv length
 *
 * @Return       receive buffer pointer
 *
 * Limitation: One one buffer is supported
 */
bool xgmac_simSendRecv(uint8_t mac_Index, uint8_t queue,
                        uint8_t* sendBuf, uint8_t* recvBuf,
                        uint32_t* length, XGMAC_CFG_t* mac_config )
{
    bool tx_ret;
    uint32_t sendLength;

    sendLength = *length;
    tx_ret = true;

    if((sendBuf == NULL) || (NULL == recvBuf))
        return false;

    init_macConfig(mac_config);
    xgmac_CoreConfig(mac_Index, mac_config);
    /*Param: 1.buf,2.total length, 3. isIP 4. isTCP, or UDP 5. bad checksum*/
    if (mac_config->isTCP)
      InitPacket(sendBuf, *length, 1, 1, mac_config->isRxCSEn);
    else
      InitPacket(sendBuf, *length, 1, 0, mac_config->isRxCSEn);

    //    xgmac_ConfigOffload(mac_Index, queue, mac_config);//ip/tcp test
    /*Param: 1. macIndex, 2. Queue.*/
    tx_ret = xgmac_Send_Tx(mac_Index, queue, sendBuf, *length, mac_config);
    if (!tx_ret) {
        printf("%s: tx failed\n",__func__);
    }
    //Sleep for while
    xgmac_SleepMS(100);
    //interrupt check
    xgmac_IntStatusCheck(0);
    *length = 0;
    //check the int status now

    tx_ret = xgmac_Recv(0, 0, recvBuf, length);
    if (tx_ret && (*length == (sendLength + 4))) {
      printf("%s: rx data received\n", __func__);
      printf("Pkg Data:");
      for (int i = 0; i < *length; i++) {
        if (i % 8 == 0) {
          printf(" ");
        }
        if (i % 16 == 0) {
          printf("\r\n");
        }

        printf("%02x ", recvBuf[i]);
      }
      printf("\r\n-----------------------------------\r\n");
    }
    if (mac_config->isTCPSegOffloadEn) {
      uint32_t totalLength, recvTimes;
      totalLength = *length;
      recvTimes = 0;
      memset(recvBuf, 0, *length);
      while (xgmac_Recv(0, 0, recvBuf, length)) {
        totalLength += *length;
        memset(recvBuf, 0, *length);
        recvTimes++;
      }
      *length = totalLength;
      if (recvTimes == 0) {
        tx_ret = false;
        printf("%s: Tx TSO test failed\n", __func__);
      }
    }
    return tx_ret;
}
/*
1. TSO test: send a huge package by a Tx Descriptor. On Rx, check if several
packets received
2. SG and HS: scatter/gatther, header buffer split test together
             SG: Joint several discrete buffer by Tx cont descriptor, and send
out together
             Current case is the simplest test. Use a huge buffer and split it
by the MTU value
             on Rx, based on HS, check if a huge packet received
*/
bool xgmac_TSO_SG_HS_test(void) {
#define PKTHUGE 4800
#define PKTTSOLEN 4560 // any number you like, hope memory is ready
  // lazy, allow some duplicate code currently
  bool tx_ret;
  XGMAC_CFG_t mac_selfcfg;

  uint8_t *pktRecvBuf;
  uint8_t *pktSendBuf;
  uint32_t recvLength;

  pktSendBuf = (uint8_t *)xgmac_AllocBuffer(PKTHUGE, 16);
  ;
  pktRecvBuf = (uint8_t *)xgmac_AllocBuffer(PKTHUGE, 16);
  /*init mac configuration*/
  memcpy(&mac_selfcfg, &xgmac_def_cfg, sizeof(xgmac_def_cfg));
  mac_selfcfg.isTCPSegOffloadEn = true;
  mac_selfcfg.isTCP = true;
  // mac_selfcfg.isHSplitEn = true;

  tx_ret = xgmac_CoreInit(0, &mac_selfcfg);
  if (!tx_ret) {
    printf("%s: xgmac init failed\n", __func__);
  }
  recvLength = PKTTSOLEN;
  memset(pktSendBuf, 0, PKTHUGE);
  memset(pktRecvBuf, 0, PKTHUGE);
  tx_ret = xgmac_simSendRecv(0, 0, pktSendBuf, pktRecvBuf, &recvLength,
                             &mac_selfcfg);

  if (tx_ret && (PKTTSOLEN == (recvLength - 4))) {
    printf("%s: xgmac TSO test passed\n", __func__);
  } else {
    printf("%s: xgmac TSO test failed\n", __func__);
    tx_ret = false;
  }

  mac_selfcfg.isSGEn = true;
  mac_selfcfg.isTCPSegOffloadEn = false;
  mac_selfcfg.isTCP = true;
  mac_selfcfg.isHSplitEn = true;

  if (!tx_ret) {
    printf("%s: xgmac init failed\n", __func__);
  }
  recvLength = PKTTSOLEN;
  memset(pktSendBuf, 0, PKTHUGE);
  memset(pktRecvBuf, 0, PKTHUGE);
  tx_ret = xgmac_simSendRecv(0, 0, pktSendBuf, pktRecvBuf, &recvLength,
                             &mac_selfcfg);

  if (tx_ret && (PKTTSOLEN == (recvLength - 4))) {
    printf("%s: xgmac SG and HS test passed\n", __func__);
  } else {
    printf("%s: xgmac SG and HS test failed\n", __func__);
    tx_ret = false;
  }

  if (pktSendBuf)
    xgmac_free(pktSendBuf);
  if (pktRecvBuf)
    xgmac_free(pktRecvBuf);
  return tx_ret;
}

bool xgmac_TxRxChecksum_test(void)
{
    bool tx_ret;
    XGMAC_CFG_t     mac_selfcfg;

    uint8_t* pktRecvBuf;
    uint8_t* pktSendBuf;
    uint32_t recvLength;

    pktSendBuf = packetBuf;
    pktRecvBuf =(uint8_t*)xgmac_AllocBuffer(PKTTOTAL, 16);
    /*init mac configuration*/
    memcpy(&mac_selfcfg, &xgmac_def_cfg,sizeof(xgmac_def_cfg));
    tx_ret = xgmac_CoreInit(0, &mac_selfcfg);
    if (!tx_ret) {
        printf("%s: xgmac init failed\n",__func__);
    }

    //1. init IPV4, tcp, checksum
    mac_selfcfg.isTCP = true;
    mac_selfcfg.isL4CSEn = true;

    recvLength = PKTLENGTH;
    memset(pktSendBuf, 0, PKTTOTAL);
    memset(pktRecvBuf, 0, PKTTOTAL);
    tx_ret = xgmac_simSendRecv(0,0,pktSendBuf, pktRecvBuf, &recvLength, &mac_selfcfg);
    if (recvLength != 0)
    {
        //checksum check
        struct tcphdr   *pHdr;
        pHdr = (struct tcphdr*)(pktRecvBuf + MAC_IP_L4);
        if (pHdr->checkSum != 0) {
            tx_ret = true;
            printf("%s: TCP/IP Tx checksum offload test passed\n",__func__);
        } else {
            tx_ret = false;
            printf("%s: TCP/IP Tx checksum offload test failed\n",__func__);
        }
    }

    //2. IPV4 UDP checksum
    mac_selfcfg.isTCP = false;
    mac_selfcfg.isL4CSEn = true;

    recvLength = PKTLENGTH;
    memset(pktSendBuf, 0, PKTTOTAL);
    memset(pktRecvBuf, 0, PKTTOTAL);
    tx_ret = xgmac_simSendRecv(0,0,pktSendBuf, pktRecvBuf, &recvLength, &mac_selfcfg);

    if (recvLength != 0)
    {
        //checksum check
        struct udphdr   *pHdr;
        pHdr = (struct udphdr*)(pktRecvBuf + MAC_IP_L4);
        if (pHdr->check != 0) {
            tx_ret = true;
            printf("%s: UDP/IP Tx checksum offload test passed\n",__func__);
        } else {
            tx_ret = false;
            printf("%s:  UDP/IP Tx checksum offload test failed\n",__func__);
        }
    }

    //3. IPv4 UDP, Rx checksum
    mac_selfcfg.isTCP = false;
    mac_selfcfg.isL3CSEn = false;
    mac_selfcfg.isL4CSEn = false;
    mac_selfcfg.isRxCSEn = true;

    recvLength = PKTLENGTH;
    memset(pktSendBuf, 0, PKTTOTAL);
    memset(pktRecvBuf, 0, PKTTOTAL);
    tx_ret = xgmac_simSendRecv(0,0,pktSendBuf, pktRecvBuf, &recvLength, &mac_selfcfg);

    /*How to know packet has been dropped due to bad checksum*/
    xgmac_IntStatusCheck(0);//To be done

    if (pktRecvBuf != NULL)
        xgmac_free(pktRecvBuf);

    return tx_ret;
    //IPv4 UDP checksum
}

/* still keep this code for reference
bool xgmac_basic_sendrecv_test(void)
{

    bool tx_ret;
    XGMAC_CFG_t     mac_selfcfg;
	struct tx_offload_desc_t* TxOffloadDesc;
	uint8_t pktBuf[1600]; //HOPE stack is large enough
    uint8_t* pktRecvBuf;
    uint32_t recvLength;

	InitIPPacket(pktBuf, PKTLENGTH);

    memcpy(&mac_selfcfg, &xgmac_def_cfg,sizeof(xgmac_def_cfg));

    tx_ret = xgmac_CoreInit(0, &mac_selfcfg);
    if (!tx_ret) {
        printf("%s: xgmac init failed\n",__func__);
    }
	// Mac init should be done before sending
	TxOffloadDesc = xgmac_GetTxOffloadDesc(0, 0); // only test mac_index 0 and queue 0
	// configure offload descriptor, not good, need to configure descriptor outside mac_drv.c
	TxOffloadDesc->Type = 1;
	TxOffloadDesc->MacHdrLen = GetMacHdr();
	TxOffloadDesc->IPHdrLen = GetIPHdr();
	TxOffloadDesc->L4HdrLen = GetUDPHdr();
	TxOffloadDesc->IPV = 0; // IPV4
	TxOffloadDesc->L4T = 0; // UDP
	// no VLAN, MSS currently
	// bool xgmac_Send_Tx(uint8_t mac_index, uint8_t queue,   uint8_t LastOne,
	//               uint8_t type,      uint8_t *buffer, uint32_t length)
	tx_ret = xgmac_Send_Tx(0, 0, 1, 2, pktBuf,PKTLENGTH);
    if (!tx_ret) {
        printf("%s: tx failed\n",__func__);
    }
    //Sleep for while
    xgmac_SleepMS(100);
    //interrupt check
    xgmac_IntStatusCheck(0);
    //check the int status now
    pktRecvBuf =(uint8_t*)xgmac_AllocBuffer(PKTTOTAL, 16);
    recvLength = PKTTOTAL;
    tx_ret = xgmac_Recv(0, 0, pktRecvBuf, &recvLength);
    if(tx_ret && (recvLength == (PKTLENGTH+4))) {
        printf("%s: rx data received\n",__func__);
        printf("Pkg Data:");
        for (int i=0; i<recvLength; i++){
            if (i%8 == 0){
            printf(" ");
            }
            if (i%16 == 0){
            printf("\r\n");
            }

            printf("%02x ",pktRecvBuf[i]);
        }
        printf("\r\n-----------------------------------\r\n");
    }

    if (memcmp(pktRecvBuf, pktBuf, PKTLENGTH) == 0) {
        printf("%s: send receive test passed\n",__func__);
    }

    return tx_ret;
}
*/