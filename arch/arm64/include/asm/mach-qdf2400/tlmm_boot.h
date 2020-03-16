/* Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
   All Rights Reserved.
   Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc. */

//#include "boot_sbl_shared.h"

#define EFI_GPIO_INTR_CFG(gpio, dir_conn, target, raw_status, detect, pol, en) \
         (((gpio)       & 0x3FF) << 16 | \
          ((dir_conn)   & 0x1)   << 8  | \
          ((target)     & 0x7)   << 5  | \
          ((raw_status) & 0x1)   << 4  | \
          ((detect)     & 0x3)   << 2  | \
          ((pol)        & 0x1)   << 1  | \
          ((en)         & 0x1))

#define EFI_GPIO_INTR_DIR_CFG(dir, pol, gpio) \
         (((dir)  & 0xF) << 16 | \
          ((pol)  & 0x1) << 8  | \
          ((gpio) & 0xFF))

typedef enum { DIR_CONN_DIS = 0, DIR_CONN_EN } eDirConn;
typedef enum { TARGET_IMC = 0, TARGET_HMSS, TARGET_TZ } eTargetProc;
typedef enum { INTR_RAW_STATUS_DIS = 0, INTR_RAW_STATUS_EN } eIntrRawStatus;
typedef enum {
  INTR_DETECT_LEVEL = 0,
  INTR_DETECT_POS,
  INTR_DETECT_NEG,
  INTR_DETECT_DUAL
} eIntrDetect;
typedef enum { INTR_POL_0 = 0, INTR_POL_1 } eIntrPolCtl;
typedef enum { INTR_DIS = 0, INTR_EN } eIntrEn;

void boot_tlmm_init( void );

