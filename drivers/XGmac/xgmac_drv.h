#ifndef __XGMAC_DRV_H__
#define __XGMAC_DRV_H__
/**---------------------------------------------------------------------------
 * @file     xgmac_drv.h
 *
 * @brief    Interface of EMAC driver
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include <stdbool.h>
//#include "xgmac_regs.h"

#define XG_QUEUES 128
#define MAGIC_TXOFF 0x112233

enum XG_LB_MODE {
  NO_LB,
  MAC_LB,       /*self loopback*/
  MAC_DUPLEX_LB,/*mac0 and mac1 loopback*/
  PCS_LB,       /*PCS layer*/
  PHY_LP};      /*PHY layer, inner phy,KR*/


typedef struct XGMAC_COMMON_CFG {
  /* MAC settings */
  enum XG_LB_MODE modeLoopback; /* Loopback mode */

  uint32_t      mtu;

  /* TX Queues */
  uint8_t       txQueues;    /* Number of TX queues to use,128 queues max */
  uint32_t      txRingSize; /* Number of descriptors in a TX ring\queues */
  uint32_t      sizeBufTx;  /* Tx buff size */

  /* RX Queues */
  uint8_t       rxQueues;        /* Number of rxQueues */
  uint32_t      rxRingSize;     /* Number of descriptors in a RX ring */
  uint32_t      sizeHdrBufRx;   /* RX buffer size */
  uint32_t      sizePloadBufRx; /* RX buffer size */
} XGMAC_COMMON_CFG_t;

/* Ethernet driver configuration */
typedef struct XGMAC_CFG_STRUCT {

  XGMAC_COMMON_CFG_t defCfg;
  /* TX/RX Disable */
  bool          isTxDisable; /* TRUE= Transmit frames disable */
  bool          isRxDisable; /* TRUE= Receive frames disable */

  /*Features*/
  bool          isPromiscuous;
  bool          isMultEn;
  bool          isBroadEn;
  bool          isManPortEn;
  bool          isRxJumboEn;
  bool          isRx1536Bytes;
  /*uint8 segRx[0]  checksum start*/
  bool          isRxCSEn;   /*Rx checksum offload enable. When set, HW will check bad frame and discard*/
  bool isIPv4;              /*IPv4 or IPv6 tx checksum support*/
  bool isL3CSEn;
  bool isTCP;    /*TCP or UDP checksum offload support*/
  bool isL4CSEn; /*UDP checksum offload support*/
  uint8_t L2HdrLen;
  uint8_t L3HdrLen;
  uint8_t L4HdrLen;
  /*uint8 vlan[0]  segment start*/
  bool          isTCPSegOffloadEn; /*TCP segment offload support*/
  bool          isUDPSegOffloadEn; /*UDP segment offload support*/
  bool isSGEn;                     /*Enable Scatter Gather ability*/
  bool          isHSplitEn; /*Header buffer split*/
  bool          isIOVEn;    /*IOV supported*/
  uint8_t       IOV_vfs;    /*how many VFs*/
  bool          isMSIXEn;
  bool          isRSSEn;
  bool          isVMQEn;
  bool          isTCEn;   /*support traffic class*/
  uint8_t       TC_Num;   /*how many TCs*/
  bool          isPTPEn;  /*1588 driver*/

} XGMAC_CFG_t; /*be careful 4bytes align in the future*/

typedef struct XGMAC_DRV_STRUCT {
  /* MAC settings */
  // uint8_t                    addr[6];               /* MAC address */
  enum XG_LB_MODE modeLoopback; /* Loopback mode, duplicate with CFG, will remove in the future */

  /* TX Queues */
  uintptr_t *txDesc[XG_QUEUES]; /* Tx ring for total 128 queues */
  uintptr_t *txBuf[XG_QUEUES];
  uint16_t  txDesc_index[XG_QUEUES]; /* Tx ring index  */
  uint16_t  txBuf_index[XG_QUEUES];  /* Tx ring buffer index  */

  /* RX Queues */
  uintptr_t *rxDesc[XG_QUEUES];     /* Rx ring  for total 128 queues */
  uintptr_t *rxHdrBuf[XG_QUEUES];   /*Rx header buffer*/
  uintptr_t *rxPloadBuf[XG_QUEUES]; /*Rx payload buffer*/
  uint16_t   rxDesc_index[XG_QUEUES];
  uint16_t   rxBuf_index[XG_QUEUES];

  uintptr_t *rxCompDesc[XG_QUEUES]; /*Rx complete ring*/
  uint16_t   rxCompDesc_index[XG_QUEUES];

} XGMAC_DRV_t; /*be careful 4bytes align in the future*/

/*Tx Rx descriptor, be careful, little endian, big endian*/
struct tx_offload_desc_t {
  union {
    uint32_t word0;
    uint32_t Type : 8; /*offload descriptor type is 1*/
    uint32_t Resv0 : 24;
  };
  union {
    uint32_t word1;
    uint32_t L4HdrLen : 8; /*Layer 4 header length, like udp*/
    uint32_t IPHdrLen : 9;
    uint32_t MacHdrLen : 7;
    uint32_t Resv1 : 8;
  };
  union {
    uint32_t word3;
    uint32_t OVLAN : 16; /*Outer VLAN for Tag Control Information. TPID comes
                            from register*/
    uint32_t IVLAN : 16; /*Inner VLAN for Tag Control Information. TPID comes
                            from register*/
  };
  union {
    uint32_t word4;
    uint32_t MSS : 16; /*Maximum Segment Size 0 - 9.5kb*/
    uint32_t IPV : 2;  /*0:IPV4, 1:IPV6, OR Non-IP type for L3 */
    uint32_t L4T : 2;  /*0:UDP; 1:TCP; or RSV: Type of L4*/
    uint32_t Resv3 : 12;
  };
};

struct tx_desc_t {
  union {
    uint32_t word0;
    uint32_t Type : 4; /*Tx descriptor type is 2*/
    uint32_t RSV0_1 : 3;
    uint32_t EOP : 1; /*End of packet. One packet might include several Descs. This bit indicate the end of the packet*/
    uint32_t RSV0_2 : 1;
    uint32_t
        L4CS : 1; /*L4 checksum enable for offload. If TSO segment enabled, TCP
                     has to do checksum */
    uint32_t L3CS : 1; /*L3 checksum enable for offload. If TSO segment enabled,
                          IPV4 has to do checksum */
    uint32_t IOV : 1;  /*Insert outer vlan enable. */
    uint32_t IIV : 1;  /*Insert inner vlan enable. */
    uint32_t TSO : 1;  /*TCP segmentation offload enable. */
    uint32_t TXBufLen : 16; /*current desc buffer length. */
  };
  union {
    uint32_t word1;
    uint32_t RSV1 : 12;
    uint32_t PyldLen : 20; /*whole packet payload length, no header
                              included(which header, mac, ip, L4 totally)*/
  };
  uint32_t TxBuffAddr_l;
  uint32_t TxBuffAddr_h;
};

struct tx_cont_desc_t {
  union {
    uint32_t word0;
    uint32_t Type : 4; /*Tx descriptor type is 3*/
    uint32_t RSV0_1 : 3;
    uint32_t EOP : 1; /*End of packet. One packet might include several descriptor, 
                        this bit indicate the end of the packet*/
    uint32_t RSV0_2 : 8;
    uint32_t TXBufLen : 16; /*current desc buffer length. */
  };
  uint32_t word1;
  uint32_t TxBuffAddr_l;
  uint32_t TxBuffAddr_h;
};

/*Rx Descriptor*/
struct rx_desc_t {
  uint32_t RxHdrBufAddr_l; /*Low 32bits buffer address for Rx Header buffer*/
  uint32_t RxHdrBufAddr_h; /*high 32bits buffer address for Rx Header buffer*/
  uint32_t RxPktBufAddr_l; /*Low 32bits buffer address for Rx packet buffer,
                            if no split, header buffer is not used*/
  uint32_t RxPktBufAddr_h; /*high 32bits buffer address for Rx packet buffer*/
};

struct rx_comp_desc_t {
  union {
    uint32_t word0;
    uint32_t NOR : 4; /* Number of Rx Descriptor, one packet might need several
                       * rx_desc_t descriptor
                       * For example. If rx_desc_t points to 1k buf size, but
                       * the recevied packet is 1600bytes length
                       * At lease two rx_desc_t descriptors are used. And only
                       * one rx_comp_desc_t is needed
                       */
    uint32_t Rsv0_1 : 4;
    uint32_t RSSTP : 4; /* RSS type: 0->on Hash, 1->HASH_IPV4, 2->HASH_TCP_IPv4... */
    uint32_t PKTTP : 4; /*packet type: 0->non-ip, 1-> IPv4 only, 2->IPv4 TCP,
                           3->IPv4 UDP, 4->IPv6*/
    uint32_t SRI : 16;  /*Start of Rx Descriptor Index. Work with NOR to get
                           whole packet*/
  };
  union {
    uint32_t word1;
    uint32_t RXCKM : 16; /*IP payload checksum result.??? in case of fragment*/
    uint32_t IVLANTAG : 16; /*Vlan ID, CFI and priority, inner vlan if enabled*/
  };
  union {
    uint32_t word2;
    uint32_t OVLANTAG : 16;
    uint32_t PKTLEN : 16; /*WHole packet length if no split. Only payload(no
                             mac, ip, tcp\udp header) length if split*/
  };
  union {
    uint32_t word3;
    uint32_t HDRLEN : 10; /*packet header length when split enabled*/
    uint32_t Rsv3_1 : 6;
    uint32_t HS : 1;  /*Header buffer split enabled*/
    uint32_t BAR : 1; /*Broadcast address received: mac:0xFFFFF....*/
    uint32_t MAR : 1; /*Multicast address received: */
    uint32_t L4F : 1; /*L4 checksum offload, L4 checksum verify failed */
    uint32_t IPF : 1; /*IP checksum verify failed */
    uint32_t ME : 1;  /*MAC error, what is mac error */
    uint32_t OV : 1;  /*Outer VLAN recevied */
    uint32_t TS : 1;  /*Time stamp */
    uint32_t ABT : 1; /*abort ?  */
    uint32_t CRC : 1; /*crc error */
    uint32_t TNC : 1; /*Truncated packet, when packet > MTU */
    uint32_t RNC : 1; /*when packet < 64bytes */
    uint32_t IV : 1;
    uint32_t Rsv3_2 : 2;
    uint32_t POL : 1; /*Polarity. POL change when comp desc receive*/
  };
  uint32_t RxTimeStamp_l;
  uint32_t RxTimeStamp_h;
};

void xgmac_HWReset(int mac_index);
void xgmac_SoftReset(int mac_index);
void xgmac_config_macaddr(int mac_index, uint8_t* mac);
void xgmac_config_loopback(int mac_index, enum XG_LB_MODE lb_mode);
int xgmac_phy_init_from_IP(int index, int loopback_mode);
int xgmac_CoreConfig(int mac_index, XGMAC_CFG_t* self_conf);
int xgmac_CoreInit(int mac_index, XGMAC_CFG_t* mac_cfg);
int xgmac_InitRxRings(int index);
int xgmac_InitTxRings(int index);
int xgmac_RxBufExt(int mac_index); /*Configure Tx Rx buffer*/
struct tx_offload_desc_t * xgmac_GetTxOffloadDesc(uint8_t mac_index, uint8_t queue);
bool xgmac_Send_Tx(uint8_t mac_index, uint8_t queue, uint8_t *buffer,
                   uint32_t length, XGMAC_CFG_t *mac_config);
bool xgmac_Recv(uint8_t mac_index, uint8_t queue,
                uint8_t *buffer,     uint32_t* length);
void xgmac_IntStatusCheck(int mac_index);

#endif