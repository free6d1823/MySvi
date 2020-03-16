#ifndef __EMAC_DRV_H__
#define __EMAC_DRV_H__
/**---------------------------------------------------------------------------
 * @file     emac_drv.h
 *
 * @brief    Interface of EMAC driver
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

#include "boot_comdef.h"
#include "emac_framework.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *--------------------------------------------------------------------------*/

/* Length of Ethernet MAC address, in bytes */
#define EMAC_MAC_ADDR_LEN         6

/* Minimal buffer alignment, in bytes */
#define EMAC_BUF_ALIGN_MIN        8

/* Optimal buffer alignment, in bytes */
#define EMAC_BUF_ALIGN_OPT        128

/* Maximal number of TX queues */
#define EMAC_TXQ_NUM              5

/* Maximal number of RX queues supported */
#define EMAC_RXQ_NUM              5

/* Maximal number of RX queues used in VMQ */
#define EMAC_RXQ_MAX_VMQ          5

/* Maximal number of RX queues used in RSS */
#define EMAC_RXQ_MAX_RSS          4

/* Minimal descriptors count in TX rings */
#define EMAC_MIN_TX_RING_SIZE     2

/* Maximal descriptors count in TX rings (See design spec section 2.2.1) */
/* #define EMAC_MAX_TX_RING_SIZE     16383 */
#define EMAC_MAX_TX_RING_SIZE     64

/* Minimal descriptors count in RX rings */
#define EMAC_MIN_RX_RING_SIZE     2

/* Maximal descriptors count in RX rings (See design spec section 2.2.1) */
/* #define EMAC_MAX_RX_RING_SIZE     2047 */
#define EMAC_MAX_RX_RING_SIZE     64

#ifdef EMAC1_FOR_IMC
/* Default size of TX rings in descriptors */
#define EMAC_TX_RING_SIZE         6
/* Default size of RX rings in descriptors */
#define EMAC_RX_RING_SIZE         6
#else
/* Default size of TX rings in descriptors */
#define EMAC_TX_RING_SIZE         6
/* Default size of RX rings in descriptors */
#define EMAC_RX_RING_SIZE         6
#endif

/* Max number of scratchpads in TX descriptor */
#define EMAC_SCRATCH_MAX          4

/* Maximal number of VMQ filters */
#define EMAC_VMQ_FILTER_CNT       8

/*
 * Size of RX (RFD) buffer in bytes.
 * MUST be QWORD aligned.
 * For best performance should be a multiple of EMAC_BUF_ALIGN_OPT
 */
#define EMAC_RX_BUF_SIZE        1536

/* Size of TX (TPD) buffer in bytes. */
#define EMAC_TX_BUF_SIZE        1536

/* Minimal size of an Ethernet frame, in bytes */
#define EMAC_MINIMAL_FRAME_SIZE 64

/* Max wait time for SW reset to de-assert, milliseconds */
#define EMAC_SW_RESET_TIMEOUT   500

/* Computes the offset, in bytes, of a specified field
   in a specific structure or union type. Copied from Utils/comdef.h */
#define FPOS( type, field ) \
  /*lint -e545 */ ( (uintnt) &(( type *) 0)-> field ) /*lint +e545 */

/* EMAC driver struct ID */
#define EMAC_DRV_ID             0xEAC0

/* Time taken for reset and init of EMAC Core */
#define EMAC_CORE_LATENCY         200

/*----------------------------------------------------------------------------
 * Type Declarations
 *--------------------------------------------------------------------------*/

/* System Clock definition */
typedef enum EMAC_STATE_ENUM {
  NOT_INITIALIZED = 0,
  INITIALIZED,
  RUNNING,
  STOPPED
} EMAC_STATE;

/* System Clock definition */
typedef enum LINK_STATE_ENUM {
  EMAC_LINK_UP = 0,
  EMAC_LINK_DOWN
} LINK_STATE;

/* MDIO Clock definitions */
typedef enum EMAC_MDIO_CLK_ENUM {
  EMAC_MDIO_CLK_25M_4   = 0,    /* 25MHz/4   */
  EMAC_MDIO_CLK_25M_6   = 2,    /* 25MHz/6   */
  EMAC_MDIO_CLK_25M_8   = 3,    /* 25MHz/8   */
  EMAC_MDIO_CLK_25M_10  = 4,    /* 25MHz/10  */
  EMAC_MDIO_CLK_25M_32  = 5,    /* 25MHz/32  */
  EMAC_MDIO_CLK_25M_68  = 6,    /* 25MHz/68  */
  EMAC_MDIO_CLK_25M_128 = 7,    /* 25MHz/128 */
} EMAC_MDIO_CLK;

/* Notifier to dispatch when link is up */
typedef void (*EMAC_UP_NOTIFIER)(LINK_STATE isLinkUp);

/* Callback to dispatch when there is a packet ready */
typedef void (*EMAC_READ_CB)(void *user_data);

/* Ethernet MAC address. Note: MSB is index 0 */
typedef uint8 EMAC_ADDR[EMAC_MAC_ADDR_LEN];

/* PTP IEEE1588 Clock mode */
typedef enum EMAC_PTP_CLK_MODE_ENUM {
  EMAC_PTP_CLK_OB_2_STEP = 0,    /* Ordinary/Boundary two-step clock */
  EMAC_PTP_CLK_OB_1_STEP = 1,    /* Ordinary/Boundary one-step clock */
} EMAC_PTP_CLK_MODE;

/* Wake-On-Lan type definitions */
typedef uint32 EMAC_WOL;
#define EMAC_WOL_NONE         0x0 /* No WOL */
#define EMAC_WOL_LINK_STATUS  0x1 /* Link Status Change */
#define EMAC_WOL_MAGIC_PACKET 0x2 /* Magic Packet */
#define EMAC_WOL_WAKEUP_FRAME 0x4 /* Wakeup Frame */

/* Filter definitions for a single RX Virtual Machine Queue (VMQ) */
typedef struct EMAC_VMQ_FLTR_STRUCT {
  uint8   vmqNum;         /* VMQ to receive the frame if current filter
                             is matched */
  boolean isAddressCmpEn; /* TRUE= compare RX destination MAC address */
  boolean isVlanCmpEn;    /* TRUE= compare RX CVLAN comparison */
  uint16  addressHigh16;  /* Top 16 bits of MAC address to compare with */
  uint32  addressLow32;   /* Low 32 bits of MAC address to compare with */
  uint16  vlan;           /* CVLAN value to compare with */
} EMAC_VMQ_FLTR;

/* RX frame address type to perform RSS hash calculation on */
typedef enum EMAC_RSS_ADD_TYPE_ENUM {
  EMAC_RSS_IPV4      = 0x1, /* IPv4 frames only */
  EMAC_RSS_TCP_IPV4  = 0x2, /* TCP over IPv4 frames only */
  EMAC_RSS_IPV6      = 0x4, /* IPv6 frames only */
  EMAC_RSS_TCP_IPV6  = 0x8, /* TCP over IPv6 frames only */
  EMAC_RSS_ALL_TYPES = 0xF, /* IPv4 and IPv6 and TCP frames */
  EMAC_RSS_TYPE_MAX  = EMAC_RSS_ALL_TYPES /* Max allowed value */
} EMAC_RSS_ADD_TYPE;

/* Ethernet driver configuration */
typedef struct EMAC_CFG_STRUCT {
  /* MAC settings */
  EMAC_ADDR               addr;               /* MAC address */
  boolean                 isPromiscuous;      /* Promiscuous mode. TRUE = enabled */
  boolean                 isDebug;            /* Debug mode. TRUE = enabled */
  boolean                 isTxFcEnable;       /* TRUE= Send TX flow control PAUSE */
  boolean                 isRxFcEnable;       /* TRUE= Enable RX flow control */
  boolean                 isEvenPad;          /* TRUE= Pad frame to even length */
  boolean                 isMultEn;           /* TRUE= Enable receiving all multicast frames */
  boolean                 isBroadEn;          /* TRUE= Enable receiving all broadcast frames */
  uint32                  mtuSize;            /* Maximal transmit unit (MTU) size */
  boolean                 isTxOverMtuEn;      /* Allow TX of frames larger than MTU */
  boolean                 isRxOverMtuEn;      /* Allow RX of frames larger than MTU */

  /* EMAC config settings */
  uint32                  speed;              /* Speed in MB: 10/100/1000 */
  boolean                 isFullDuplex;       /* Duplex. TRUE = Full, FALSE = Half */
  boolean                 isAutoNeg;          /* TRUE= Auto negotiation enabled */
  EMAC_CLK                clkSystem;          /* System clock to use */
  EMAC_LB_MODE            modeLoopback;       /* Loopback mode */

  /* TX Queues */
  uint8                   txQueues;           /* Number of TX queues to use */
  uint32                  txRingSize;         /* Number of descriptors in a TX ring */

  /* RX Queues */
  uint8                   rxQueues;           /* Number of rxQueues */
  uint32                  rxRingSize;         /* Number of descriptors in a RX ring */
  uint32                  sizeBufRX;          /* RX buffer size */

  /* PHY Related */
  EMAC_MDIO_CLK     clkMDIO;                 /* MDIO clock to use */

  /* Interrupts moderation */
  uint16                  txIrqModCnt;      /* Moderation time for TX interrupts */
  uint16                  rxIrqModCnt;      /* Moderation time for TX interrupts */

  /* TX/RX Disable */
  boolean                 isTxDisable;      /* TRUE= Transmit frames disable */
  boolean                 isRxDisable;      /* TRUE= Receive frames disable */

  /* VLAN Definitions */
  boolean                 isVlanStripEn;    /* Enable VLAN RX stripping */
  uint16                  sVlanID;          /* SVLAN ID to strip/insert */
  uint16                  cVlanID;          /* CVLAN ID to strip/insert */
  uint16                  sVlanInfoIns;     /* SVLAN info to insert or 0x0 */
  uint16                  cVlanInfoIns;     /* CVLAN info to insert or 0x0 */

  /* Scratchpads - set zero to disable */
  uint32                  rxScratchCnt;     /* RX Scratchpads count */
  uint32                  txScratchCnt;     /* TX Scratchpads count */

  /* Enable/Disable timestamps */
  boolean                 isRxTsEn;         /* TRUE= Enable RX timestamp */
  boolean                 isTxTsEn;         /* TRUE= Enable TX timestamp */

  /* PTP IEEE1588 */
  boolean                 isPtpEnable;      /* TRUE= Enable PTP IEEE1588 */
  EMAC_PTP_CLK_MODE ptpClkMode;             /* PTP Clock mode */

  /* RSS definitions */
  boolean                 isRssEn;          /* TRUE= Enable RSS for RX */
  EMAC_RSS_ADD_TYPE rssHashType;            /* Address type to be hashed */
  const uint8            *rssKey;           /* 40-byte hash function key */
  const uint8            *rssHashTbl;       /* RSS indirection table
                                               (hash value to CPU number) */
  uint32                  rssHashTblSize;   /* RSS indirection table size */

  /* VMQ definitions */
  boolean                isVmqEn;           /* TRUE= Enable VMQ for RX */
  const EMAC_VMQ_FLTR *vmqFilter;           /* VMQ filter definitions */
  uint32                 vmqFilterCnt;      /* Number of VMQ filters */

} EMAC_CFG;

/* RRD type */
typedef enum EMAC_RRD_TYPE_ENUM
{
  EMAC_RRD_0_TS_0_SCRATCH = 0,            /* No timestamp, no scratchpads */
  EMAC_RRD_0_TS_2_SCRATCH,                /* No timestamp,  2 scratchpads */
  EMAC_RRD_0_TS_4_SCRATCH,                /* No timestamp,  4 scratchpads */
  EMAC_RRD_1_TS_0_SCRATCH,                /* Timestamp,    no scratchpads */
  EMAC_RRD_1_TS_2_SCRATCH,                /* Timestamp,     2 scratchpads */
  EMAC_RRD_1_TS_4_SCRATCH                 /* Timestamp,     4 scratchpads */
} EMAC_RRD_TYPE;

/* TPD type */
typedef enum EMAC_TPD_TYPE_ENUM
{
  EMAC_TPD_0_SCRATCH = 0,                 /* No scratchpads in TPD */
  EMAC_TPD_2_SCRATCH,                     /*  2 scratchpads in TPD */
  EMAC_TPD_4_SCRATCH,                     /*  4 scratchpads in TPD */
} EMAC_TPD_TYPE;

/*
 * Transmit Packet Descriptor Type A
 * For further details see design spec document (field names not changed)
 */
typedef struct TPD_TYPE_A_struct
{
  uint32 BUF_LEN          : 16;           /* DWORD 0 */
  uint32 SVLAN_TAG        : 16;

  uint32 RSVD_A8          : 8;            /* DWORD 1 */
  uint32 CSX              : 1;
  uint32 IPX              : 1;
  uint32 TCPX             : 1;
  uint32 UDPX             : 1;
  uint32 LSO              : 1;
  uint32 LSOV             : 1;
  uint32 SVTAG            : 1;
  uint32 INSTS            : 1;
  uint32 RSVD_A14         : 14;
  uint32 EPAD             : 1;
  uint32 LS               : 1;

  uint32 BUFFER_ADDR_L    : 32;         /* DWORD 2 */

  uint32 CVLAN_TAG        : 16;         /* DWORD 3 */
  uint32 CVTAG            : 1;
  uint32 INSTC            : 1;
  uint32 BUFFER_ADDR_H    : 13;
  uint32 Timestamp_save   : 1;
} TPD_TYPE_A;

/**
 * Transmit Packet Descriptor Type B
 * For further details see design spec document (field names not changed)
 */
typedef struct TPD_TYPE_B_struct
{
  uint32 BUF_LEN          : 16;         /* DWORD 0 */
  uint32 SVLAN_TAG        : 16;

  uint32 L4HDR_OFFSET	  : 8;          /* DWORD 1 */
  uint32 CSX              : 1;
  uint32 IPX              : 1;
  uint32 TCPX             : 1;
  uint32 UDPX             : 1;
  uint32 LSO              : 1;
  uint32 LSOV             : 1;
  uint32 SVTAG            : 1;
  uint32 INSTS            : 1;
  uint32 IPV4             : 1;
  uint32 TYP              : 1;
  uint32 RSVD_B12         : 12;
  uint32 EPAD             : 1;
  uint32 LS               : 1;

  uint32 BUFFER_ADDR_L    : 32;         /* DWORD 2 */

  uint32 CVLAN_TAG        : 16;         /* DWORD 3 */
  uint32 CVTAG            : 1;
  uint32 INSTC            : 1;
  uint32 BUFFER_ADDR_H    : 13;
  uint32 Timestamp_save   : 1;
} TPD_TYPE_B;

/**
 * Transmit Packet Descriptor Type C
 * For further details see design spec document (field names not changed)
 */
typedef struct TPD_TYPE_C_struct
{
  uint32 BUF_LEN          : 16;         /* DWORD 0 */
  uint32 SVLAN_TAG        : 16;

  uint32 TCPHDR_OFFSET	  : 8;            /* DWORD 1 */
  uint32 CSX              : 1;
  uint32 IPX              : 1;
  uint32 TCPX             : 1;
  uint32 UDPX             : 1;
  uint32 LSO              : 1;
  uint32 LSOV             : 1;
  uint32 SVTAG            : 1;
  uint32 INSTS            : 1;
  uint32 IPV4             : 1;
  uint32 TYP              : 1;
  uint32 MSS              : 13;
  uint32 LS               : 1;

  uint32 BUFFER_ADDR_L    : 32;         /* DWORD 2 */

  uint32 CVLAN_TAG        : 16;         /* DWORD 3 */
  uint32 CVTAG            : 1;
  uint32 INSTC            : 1;
  uint32 BUFFER_ADDR_H    : 13;
  uint32 Timestamp_save   : 1;
} TPD_TYPE_C;

/**
 * Transmit Packet Descriptor Type D
 * For further details see design spec document (field names not changed)
 */
typedef struct TPD_TYPE_D_struct
{
  uint32 BUF_LEN          : 16;         /* DWORD 0 */
  uint32 SVLAN_TAG        : 16;

  uint32 PAYLOAD_OFFSET   : 8;          /* DWORD 1 */
  uint32 CSX              : 1;
  uint32 IPX              : 1;
  uint32 TCPX             : 1;
  uint32 UDPX             : 1;
  uint32 LSO              : 1;
  uint32 LSOV             : 1;
  uint32 SVTAG            : 1;
  uint32 INSTS            : 1;
  uint32 IPV4             : 1;
  uint32 TYP              : 1;
  uint32 CXSUM_OFFSET     : 8;
  uint32 RSVD_D4          : 4;
  uint32 EPAD             : 1;
  uint32 LS               : 1;

  uint32 BUFFER_ADDR_L    : 32;         /* DWORD 2 */

  uint32 CVLAN_TAG        : 16;         /* DWORD 3 */
  uint32 CVTAG            : 1;
  uint32 INSTC            : 1;
  uint32 BUFFER_ADDR_H    : 13;
  uint32 Timestamp_save   : 1;
} TPD_TYPE_D;

/**
 * Transmit Packet Descriptor
 * For further details see design spec document (field names not changed)
 */
typedef union TPD_struct {
  TPD_TYPE_A TypeA;                     /* TPD Type A */
  TPD_TYPE_B TypeB;                     /* TPD Type B */
  TPD_TYPE_C TypeC;                     /* TPD Type C */
  TPD_TYPE_D TypeD;                     /* TPD Type D */
} TPD;

/** Extended TPD - 2 scratchpads */
typedef struct TPD_SCRATCH_2_struct {
  TPD    tpd;                           /* Default TPD struct */
  uint32 SCRATCH0;                      /* TPD's scratchpad */
  uint32 SCRATCH1;                      /* TPD's scratchpad */
} TPD_SCRATCH_2;

/* Extended TPD - 4 scratchpads */
typedef struct TPD_SCRATCH_4_struct {
  TPD    tpd;                           /* Default TPD struct */
  uint32 SCRATCH0;                      /* TPD's scratchpad */
  uint32 SCRATCH1;                      /* TPD's scratchpad */
  uint32 SCRATCH2;                      /* TPD's scratchpad */
  uint32 SCRATCH3;                      /* TPD's scratchpad */
} TPD_SCRATCH_4;

/**
 * Receive Free Descriptor
 * For further details see design spec document (field names not changed)
 */
typedef struct RFD_struct {
  uint32 BUF_ADDR_LO;                   /* Buffer address 32 LSBits */
  uint32 BUF_ADDR_HI;                   /* Buffer address 32 MSBits */
} RFD;

/*
 * Receive Return Descriptor
 * For further details see design spec document (field names not changed)
 */
typedef struct RRD_TYPE_A_struct {
  uint32 RX_CHKSUM        : 16;         /* DWORD 0 */
  uint32 NOR              : 4;
  uint32 SI               : 12;

  uint32 RSS_HASH         : 32;         /* DWORD 1 */

  uint32 CVLAN_TAG        : 16;         /* DWORD 2 */
  uint32 VMQ_FILTER       : 8;
  uint32 PTP_TIMESTAMP    : 1;
  uint32 CPU_N            : 3;
  uint32 HASH_FLAG        : 4;

  uint32 PKT_SIZE         : 14;         /* DWORD 3 */
  uint32 L4F              : 1;
  uint32 IPF              : 1;
  uint32 CVTAG            : 1;
  uint32 PID              : 3;
  uint32 RES              : 1;
  uint32 CRC              : 1;
  uint32 FAE              : 1;
  uint32 TRUNC            : 1;
  uint32 RUNC             : 1;
  uint32 ICMP             : 1;
  uint32 BAR              : 1;
  uint32 MAR              : 1;
  uint32 TYP              : 1;
  uint32 FOV              : 1;
  uint32 LENE             : 1;
  uint32 UPDT             : 1;
} RRD_TYPE_A;

/* RRD struct with 2 scratchpad fields */
typedef struct RRD_TYPE_B_struct
{
  uint32     scratch0;                  /* RRD's scratchpad */
  uint32     scratch1;                  /* RRD's scratchpad */
  RRD_TYPE_A TypeA;                     /* RRD type A */
} RRD_TYPE_B;

/* RRD struct with 4 scratchpad fields */
typedef struct RRD_TYPE_C_struct {
  uint32     scratch0;                  /* RRD's scratchpad */
  uint32     scratch1;                  /* RRD's scratchpad */
  uint32     scratch2;                  /* RRD's scratchpad */
  uint32     scratch3;                  /* RRD's scratchpad */
  RRD_TYPE_A TypeA;                     /* RRD type A */
} RRD_TYPE_C;

/* RRD struct with timestamp (2 DWORDS) */
typedef struct RRD_TYPE_D_struct {
  uint32     timestampLow;              /* RRD low 32 timestamp bits */
  uint32     timestampHigh;             /* RRD high 32 timestamp bits */
  RRD_TYPE_A TypeA;                     /* RRD type A */
} RRD_TYPE_D;

/* RRD struct with timestamp (2 DWORDS) and 2 scratchpads */
typedef struct RRD_TYPE_E_struct {
  uint32     timestampLow;              /* RRD low 32 timestamp bits */
  uint32     timestampHigh;             /* RRD high 32 timestamp bits */
  RRD_TYPE_B TypeB;                     /* RRD type B */
} RRD_TYPE_E;

/* RRD struct with timestamp (2 DWORDS) and 4 scratchpads */
typedef struct RRD_TYPE_F_struct {
  uint32     timestampLow;              /* RRD low 32 timestamp bits */
  uint32     timestampHigh;             /* RRD high 32 timestamp bits */
  RRD_TYPE_C TypeC;                     /* RRD type C */
} RRD_TYPE_F;

/* EMAC driver data */
typedef struct EMAC_DRV_STRUCT {
  uint32              drvId;                        /* ID used to verify driver struct */

  /* TX Rings */
  EMAC_BUFFER         ringTPD[EMAC_TXQ_NUM];        /* TPD ring memory */
  uint32              indexTPD[EMAC_TXQ_NUM];       /* TPD ring producer index */
  uint32              countTPD;                     /* TPD ring size in descriptors */
  uint32              lastTPDConsInx;
  uint8               txQueuesNum;                  /* Number of TX queues used */
  EMAC_BUFFER         tpdbuffersInt[EMAC_MAX_TX_RING_SIZE];

  /* TPD type */
  EMAC_TPD_TYPE       tpdType;                      /* TPD type */
  uint32              tpdSize;                      /* TPD descriptor size, in bytes */

  boolean             isTxTsEn;                     /* TRUE= Enable TX timestamp */

  uint32              tpdScratch[EMAC_SCRATCH_MAX]; /* TPD scratchpads */
  uint32              tpdScratchSize;               /* Total scratchpad bytes */

  /* RX Rings */
  uint32              countRFD;                     /* RFD ring size in descriptors */
  EMAC_BUFFER         ringRFD[EMAC_RXQ_NUM];        /* RFD rings memory */
  uint32              indexRFD[EMAC_RXQ_NUM];       /* RFD rings producer index */
  uint32              indexProcRFD[EMAC_RXQ_NUM];   /* RFD rind processed index */
  EMAC_BUFFER         rfdbuffer[EMAC_MAX_RX_RING_SIZE];
  EMAC_BUFFER         ringRRD[EMAC_RXQ_NUM];        /* RRD rings memory */
  uint32              indexRRD[EMAC_RXQ_NUM];       /* RRD rings consumer index */
  RRD_TYPE_A          *baseRrdTypeA[EMAC_RXQ_NUM];  /* RRD type A rings base address */
  RRD_TYPE_A          *curRrdTypeA[EMAC_RXQ_NUM];   /* Currently available RRD type A */
  uint32              lastRFD;
  boolean             isrfdFull;

  uint32              rxQueuesNum;                  /* Number of RX queues used */

  boolean             isRssEn;                      /* TRUE= Enable RSS for RX */
  boolean             isVmqEn;                      /* TRUE= Enable VMQ for RX */

  /* RRD type used */
  EMAC_RRD_TYPE       rrdType;                      /* RRD type */
  uint32              rrdSize;                      /* RRD descriptor size, in bytes */

  uint32              sizeBufRX;                    /* Size of RX buffer in bytes */

  /* Even padding definition */
  uint32              isEvenPad;                    /* Enable/Disable even length frame padding */

  /* Checksum offload */
  uint32              IPX;                          /* Enable/Disable IP checksum offloading */
  uint32              TCPX;                         /* Enable/Disable TCP checksum offloading */
  uint32              UDPX;                         /* Enable/Disable UDP checksum offloading */
  uint8               L4HDR_OFFSET;                 /* Layer 4 header offset, in bytes */

  /* Statistics counters */
  volatile uint32     totalTxFrames;                /* Total TX frames transmitted */
  volatile uint32     totalRxFrames;                /* Total good RX frames received */

  /* PTP clock mode */
  EMAC_PTP_CLK_MODE     ptpClkMode;                 /* PTP IEEE1588 Clock mode */

  /* VLAN Definitions */
  uint16              sVlanInfoIns;                 /* SVLAN to insert or 0x0 */
  uint16              cVlanInfoIns;                 /* CVLAN to insert or 0x0 */

  /* EPHY status auto-polling */
  boolean             isAutoPoll;                   /* TRUE= Enable link status auto poll */
  boolean             isLinkUp;                     /* TRUE= Link is up */

  /* Wake-On-Lan */
  EMAC_WOL            wolStatus;                          /* Status for last Wake-On-Lan */

#ifdef EMAC1_FOR_IMC
  /* DAL Device Handle */
  DalDeviceHandle         *hInterruptCtrl;
  EMAC_UP_NOTIFIER        emacUpNtfy;               /* Notifier to dispatch when link is up */
  EMAC_READ_CB            emacRdCbk;                /* Callback to dispatch when there is a packet ready */
#endif /*EMAC1_FOR_IMC*/

  /* Device State */
  EMAC_STATE              emacState;

  /* Core ISR */
  void (*coreIsr)(void*);

} EMAC_DRV;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 *--------------------------------------------------------------------------*/

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
);

/**
 * @brief       Cleanup driver
 */
void Emac_Cleanup
(
  IN uint8 emacIndex
);

/**
 * @brief       Perform EMAC SW reset
 *
 * @return      TRUE if successful, else failed.
 */
int Emac_SwReset
(
  IN uint8 emacIndex
);

/**
 * @brief       Get MAC address
 *
 * @param[out]  addr     If not NULL, will get the current MAC address
 */
void Emac_GetMacAddr
(
  IN uint8 emacIndex,
  IN OUT EMAC_ADDR *addr
);

/**
 * @brief       Set MAC address
 *
 * @param[in]   addr     MAC address to set
 */
void Emac_SetMacAddr
(
 IN uint8 emacIndex,
 IN OUT EMAC_ADDR *addr
);

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
  IN uint8 *buffer
);

/**
 * @brief       Set a all receive frame buffers at default RX queue (#0)
 *
 * @param[in]   buffer    Buffer for frame data
 *
 * @return      TRUE if successful, else failed
 */
int Emac_SetRecvBufferExt
(
  IN uint8 emacIndex,
  IN uint8 queues
);

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
);

/**
 * @brief       Get EPHY status read by HW auto-polling via MDIO. Function will
 *              fail if auto-polling is not enabled
 *
 * @param[out]  isLinkUp  will be set to TRUE if link is up, FALSE otherwise
 *
 * @return      TRUE if successful, else failed
 */
int Emac_IsLinkUp
(
  IN uint8 ephyIndex,
  IN OUT boolean *isLinkUp
);

/**
 * @brief           update emac status
 *
 * @return          None
 */
void Emac_UpdateStatus
(
  IN uint8 emacIndex,
  IN EMAC_STATE status
);

/**
 * @brief           Notify the upper layers that emac is ready
 *
 * @return          None
 */
void Emac_Notify
(
  IN uint8 emacIndex,
  IN LINK_STATE linkStatus
);

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
);

/**
 * @brief       Return the size of the next packet to be ready
 *
 */
int Emac_PeekDataRd
(
  IN uint8 emacIndex
);

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
);

#endif  /* __EMAC_DRV_H__ */



