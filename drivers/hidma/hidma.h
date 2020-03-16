/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#ifndef _HDTS_HIDMA_H_
#define _HDTS_HIDMA_H_

#include <asm/hal/HALhwio.h>
#include <asm/mach-qdf2400/monaco/common/common_defs.h>
//#include <com_dtypes.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <target/irq.h>
#include <target/irqc.h>

#define HI_DMA_INSTANCE_NUM 4
#define HI_DMA_CHANNEL_NUM 6
#define EV_INTTYPE_MSI 0
#define EV_INTTYPE_IRQ 1
#define DMA_GIC3_GLOBAL_IRQ_INDEX(dma_id) (370 + dma_id * 7 + 32)
#define DMA_GIC3_TR_EV_IRQ_INDEX(dma_id, ch_id)                                \
  (370 + dma_id * 7 + ch_id + 1 + 32)
#define MEMSET_PATTERN (0x5a)
#define TOTAL_NUM_HIDMA_REG (sizeof(hidma_reg_table) / sizeof(dma_reg_info_t))
#define HIDMA_REG_BASE(dma_id)                                                 \
  ((unsigned long)(0xFF98000000 + (dma_id)*0x2000000))

/*HIDMA Transfer Ring Context array register (TRCA)*/
#define HIDMA_TR_CHANNEL_CNTXT0_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98010000 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_TR_CHANNEL_CNTXT2_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98010008 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_TR_CHANNEL_CNTXT3_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF9801000C + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_TR_CHANNEL_CNTXT4_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98010010 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_TR_CHANNEL_CNTXT6_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98010018 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_TR_CHANNEL_CNTXT8_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98010020 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_TR_CHANNEL_CNTXT10_ADDR(dma_id, channel_id)                      \
  ((unsigned long)(0xFF98010028 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*Transfer channel Doorbell register*/
#define HIDMA_TR_CHANNEL_DOORBELL_ADDR(dma_id, channel_id)                     \
  ((unsigned long)(0xFF98010400 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*internal TRE decode read pointer*/
#define HIDMA_TR_CHANNEL_TRE_DECODE_READ_PTR_ADDR(dma_id, channel_id)          \
  ((unsigned long)(0xFF98010808 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*internal TRE fetch read pointer*/
#define HIDMA_TR_CHANNEL_TRE_FETCH_READ_PTR_ADDR(dma_id, channel_id)           \
  ((unsigned long)(0xFF98010800 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*HIDMA Event channel Context array register (EVCA)*/
#define HIDMA_EV_CHANNEL_CNTXT0_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98070000 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_EV_CHANNEL_CNTXT1_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98070004 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_EV_CHANNEL_CNTXT2_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98070008 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_EV_CHANNEL_CNTXT3_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF9807000C + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_EV_CHANNEL_CNTXT4_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98070010 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_EV_CHANNEL_CNTXT6_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98070018 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_EV_CHANNEL_CNTXT8_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98070020 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_EV_CHANNEL_CNTXT12_ADDR(dma_id, channel_id)                      \
  ((unsigned long)(0xFF98070030 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*Event channel Doorbell register*/
#define HIDMA_EV_CHANNEL_DOORBELL_ADDR(dma_id, channel_id)                     \
  ((unsigned long)(0xFF98070400 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*internal EVRE Write pointer*/
#define HIDMA_EV_CHANNEL_EVENT_ENG_WRITE_PTR_ADDR(dma_id, channel_id)          \
  ((unsigned long)(0xFF98070800 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*interrupt status registe, read only*/
#define HIDMA_EV_TR_CH_IRQ_STTS_ADDR(dma_id, channel_id)                       \
  ((unsigned long)(0xFF98070100 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*interrupt clear regsiter, w1c*/
#define HIDMA_EV_TR_CH_IRQ_CLR_ADDR(dma_id, channel_id)                        \
  ((unsigned long)(0xFF98070108 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*interrupt enable register*/
#define HIDMA_EV_TR_CH_IRQ_EN_ADDR(dma_id, channel_id)                         \
  ((unsigned long)(0xFF98070110 + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*MSI Controller address register*/
#define HIDMA_EV_TR_CH_MSI_BASE_LSB_ADDR(dma_id, channel_id)                   \
  ((unsigned long)(0xFF98070118 + (dma_id)*0x2000000 + (channel_id)*0x10000))
#define HIDMA_EV_TR_CH_MSI_BASE_MSB_ADDR(dma_id, channel_id)                   \
  ((unsigned long)(0xFF9807011C + (dma_id)*0x2000000 + (channel_id)*0x10000))
/*TR_EV IRQ ID*/
#define HIDMA_EV_TR_CH_MSI_INT_ID_BASE_ADDR(dma_id, channel_id)                \
  ((unsigned long)(0xFF98070120 + (dma_id)*0x2000000 + (channel_id)*0x10000))

/*HIDMA register*/
#define HIDMA_HI_DMA_MHIREGLEN_ADDR(dma_id)                                    \
  ((unsigned long)(0xFF98000000 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_MHIVER_ADDR(dma_id)                                       \
  ((unsigned long)(0xFF98000008 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_MHICFG_ADDR(dma_id)                                       \
  ((unsigned long)(0xFF98000010 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_DEBUGOFF_ADDR(dma_id)                                     \
  ((unsigned long)(0xFF98000030 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_CCABAP_LSB_ADDR(dma_id)                                   \
  ((unsigned long)(0xFF98000058 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_CCABAP_MSB_ADDR(dma_id)                                   \
  ((unsigned long)(0xFF9800005C + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_ECABAP_LSB_ADDR(dma_id)                                   \
  ((unsigned long)(0xFF98000060 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_ECABAP_MSB_ADDR(dma_id)                                   \
  ((unsigned long)(0xFF98000064 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_CFG_ADDR(dma_id)                                          \
  ((unsigned long)(0xFF98000400 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_HW_PARAM_ADDR(dma_id)                                     \
  ((unsigned long)(0xFF98000408 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_TR_CHRESET_ADDR(dma_id)                                   \
  ((unsigned long)(0xFF98000410 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_CHRESET_TIMEOUT_ADDR(dma_id)                              \
  ((unsigned long)(0xFF98000418 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MAX_BUS_REQ_LEN_ADDR(dma_id)                              \
  ((unsigned long)(0xFF9800041C + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MAX_XACTIONS_ADDR(dma_id)                                 \
  ((unsigned long)(0xFF98000420 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MOQA_CFG_ADDR(dma_id)                                     \
  ((unsigned long)(0xFF98000430 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_CACHEATTR_ADDR(dma_id)                                    \
  ((unsigned long)(0xFF98000448 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_CGC_CTRL_ADDR(dma_id)                                     \
  ((unsigned long)(0xFF98000458 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_IRQ_STTS_ADDR(dma_id)                                     \
  ((unsigned long)(0xFF98000500 + (dma_id)*0x2000000)) /*read-only*/
#define HIDMA_HI_DMA_IRQ_CLR_ADDR(dma_id)                                      \
  ((unsigned long)(0xFF98000508 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_IRQ_EN_ADDR(dma_id)                                       \
  ((unsigned long)(0xFF98000510 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MSI_INT_ID_BASE_ADDR(dma_id)                              \
  ((unsigned long)(0xFF98000518 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MSI_BASE_LSB_ADDR(dma_id)                                 \
  ((unsigned long)(0xFF98000520 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MSI_BASE_MSB_ADDR(dma_id)                                 \
  ((unsigned long)(0xFF98000524 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MSI_RID_GLOBAL_ADDR(dma_id)                               \
  ((unsigned long)(0xFF98000528 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MSI_RID_LOCAL_ADDR(dma_id)                                \
  ((unsigned long)(0xFF9800052C + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MSI_CACHEATTR_ADDR(dma_id)                                \
  ((unsigned long)(0xFF98000530 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_INTSET_ADDR(dma_id)                                       \
  ((unsigned long)(0xFF98000534 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_ADDR(dma_id, channel_id)             \
  ((unsigned long)(0xFF98000540 + (dma_id)*0x2000000 + (channel_id)*0x4))
#define HIDMA_HI_DMA_MEMSET_LIMIT_ADDR(dma_id)                                 \
  ((unsigned long)(0xFF98000600 + (dma_id)*0x2000000))
#define HIDMA_HI_DMA_TRCH_QOS_ADDR(dma_id, channel_id)                         \
  ((unsigned long)(0xFF98000700 + (dma_id)*0x2000000 + (channel_id)*0x4))
#define HIDMA_HI_DMA_MHID_CLNT_BUS_ERR_LOG_0_ADDR(dma_id)                      \
  ((unsigned long)(0xFF98001020 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_MHID_CLNT_BUS_ERR_LOG_1_ADDR(dma_id)                      \
  ((unsigned long)(0xFF98001024 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_MHID_CLNT_BUS_ERR_LOG_CLR_ADDR(dma_id)                    \
  ((unsigned long)(0xFF9800102C + (dma_id)*0x2000000)) /*W1C*/
#define HIDMA_HI_DMA_EVNT_CLNT_BUS_ERR_LOG_0_ADDR(dma_id)                      \
  ((unsigned long)(0xFF98001030 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_EVNT_CLNT_BUS_ERR_LOG_1_ADDR(dma_id)                      \
  ((unsigned long)(0xFF98001034 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_EVNT_CLNT_BUS_ERR_LOG_CLR_ADDR(dma_id)                    \
  ((unsigned long)(0xFF9800103C + (dma_id)*0x2000000)) /*W1C*/
#define HIDMA_HI_DMA_IDE_CLNT_BUS_ERR_LOG_0_ADDR(dma_id)                       \
  ((unsigned long)(0xFF98001040 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_IDE_CLNT_BUS_ERR_LOG_1_ADDR(dma_id)                       \
  ((unsigned long)(0xFF98001044 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_IDE_CLNT_BUS_ERR_LOG_2_ADDR(dma_id)                       \
  ((unsigned long)(0xFF98001048 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_IDE_CLNT_BUS_ERR_LOG_CLR_ADDR(dma_id)                     \
  ((unsigned long)(0xFF9800104C + (dma_id)*0x2000000)) /*W1C*/
#define HIDMA_HI_DMA_ODE_CLNT_BUS_ERR_LOG_0_ADDR(dma_id)                       \
  ((unsigned long)(0xFF98001050 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_ODE_CLNT_BUS_ERR_LOG_1_ADDR(dma_id)                       \
  ((unsigned long)(0xFF98001054 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_ODE_CLNT_BUS_ERR_LOG_2_ADDR(dma_id)                       \
  ((unsigned long)(0xFF98001058 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_ODE_CLNT_BUS_ERR_LOG_CLR_ADDR(dma_id)                     \
  ((unsigned long)(0xFF9800105C + (dma_id)*0x2000000)) /*W1C*/
#define HIDMA_HI_DMA_MSI_CLNT_BUS_ERR_LOG_0_ADDR(dma_id)                       \
  ((unsigned long)(0xFF98001060 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_MSI_CLNT_BUS_ERR_LOG_CLR_ADDR(dma_id)                     \
  ((unsigned long)(0xFF9800106C + (dma_id)*0x2000000)) /*W1C*/
#define HIDMA_HI_DMA_INVALID_TRE_ERR_LOG_0_ADDR(dma_id)                        \
  ((unsigned long)(0xFF98001070 + (dma_id)*0x2000000)) /*Read-only*/
#define HIDMA_HI_DMA_INVALID_TRE_ERR_LOG_CLR_ADDR(dma_id)                      \
  ((unsigned long)(0xFF9800107C + (dma_id)*0x2000000)) /*W1C*/
#define HIDMA_HI_DMA_HW_EVENTS_CFG_ADDR(dma_id)                                \
  ((unsigned long)(0xFF98001080 + (dma_id)*0x2000000))

typedef struct TRE_STRUC_MEMSETC {
  UINT64 memsetc : 8; /*for memoryset, 8-bit constant to filled*/
  UINT64 unused : 56; /*MSB not used*/
} tre_memsetc_t;

union tre_3_4th_word_t {
  tre_memsetc_t memset_const;
  UINT64 srcaddr;
};

typedef struct CACHEATTR_STRUC {
  UINT16 acacheable : 1;
  UINT16 ainnercacheable : 1;
  UINT16 ashared : 1;
  UINT16 ainnershared : 1;
  UINT16 anoallocate : 1;
  UINT16 ainnernoallocate : 1;
  UINT16 atransient : 1;
  UINT16 ainnertransient : 1;
  UINT16 awritethrough : 1;
  UINT16 ainnerwritethrough : 1;
  UINT16 adevice : 1;
  UINT16 adevicetype : 2;
  UINT16 resev : 3;
} cacheattr_t;

typedef struct TRE_STRUC_7TH_WORD {
  UINT32 cacheattrs : 13; /*source buffer cache attributes*/
  UINT32 ptsa : 1;        /*IOMMU translation is required or not*/
  UINT32 mmuasrc : 2;     /*IOMMU TLB allocation policy for source buffer*/
  UINT32 cacheattrd : 13; /*destination buffer cache attributes*/
  UINT32 ptda : 1;        /*pretranslated destination address*/
  UINT32 mmuadst : 2;     /*IOMMU TLB allocation policy for destination buffer*/
} tre_7th_word_t;

typedef struct TRE_STRUC_1ST_WORD {
  UINT32 type : 8;   /*allow DMA types, 3:memcopy, 4:memset, 5:barrier,
                        6:immediate message*/
  UINT32 evridx : 8; /*index of event channel to generate event interrupt*/
  UINT32 ieob : 1;   /*interrupt at end of block*/
  UINT32 ieot : 1;   /*ignored in DMA*/
  UINT32 bei : 1;    /*block evnt interrupt*/
  UINT32 chain : 1;  /*ignored by DMA*/
  UINT32 trci : 1;   /*ignored by DMA*/
  UINT32 resev1 : 11;
} tre_1st_word_t;

typedef struct TRE_STRUCT {
  tre_1st_word_t tre_1st_word; /*1st Word for TRE*/
  UINT32 len; /*2nd word for TRE,length of transfer, in bytes, valid
                 value:0~0xFFFF FFFF* */
  union tre_3_4th_word_t
      srcaddr_memsetc; /*3rd and 4th word for TRE, if type = memcopy, 64bit
                          source address, if type = memset, 8-bit constant*/
  UINT64 destaddr;     /*5th and 6th word for TRE*/
  tre_7th_word_t tre_7th_word; /*7th word for TRE*/
  UINT32 resv;                 /*8th word for TRE, it is reserved field*/
} hidma_tre_t;

typedef struct EVRE_1ST_WORD_STRUCT {
  UINT32 type : 8;   /*DMA completion event, DMA immediate data event*/
  UINT32 trchid : 8; /*transfer channel*/
  UINT32 rsvd : 8;
  UINT32 errinfo : 4; /*RRESP field*/
  UINT32 code : 4;    /*completion code, success or bus error*/
} evre_1st_word_t;

typedef struct EVRE_STRUCT {
  evre_1st_word_t ever_1st_word;
  UINT32 len; /*2n word, the lenght of data transferd, in bytes*/
  UINT64 ptr; /*3rd&4th word, pointer to data buffer, TRE[DSTADDR]*/
} hidma_evre_t;
typedef struct RECORD_TRE_INFO {
  UINT64 destaddr;
  union tre_3_4th_word_t srcaddr_setval;
  UINT32 trans_len;
  UINT8 tre_type;
  UINT8 trch_id;
  UINT16 valid_flag;
} record_tre_info_t;

typedef struct DMA_CONFIG_STRUCT {
  UINT8 memset_max_num_jobs;
  UINT8 client_req_prio; /*1-high, 0-low, bit mapping: bit0:MHID manager,
                            bit1:IDE, bit2:ODE, bit3:event Eng, bit4: MSI eng*/
  UINT8 const_wr_tid_en;
  UINT8 const_rd_tid_en;
  UINT8 qsb_beat_index_en;
  UINT8 max_rd_xactions;
  UINT8 max_wr_xactions;
  UINT8 inttype;    /*0-MSI, 1-IRQ, 9-NON*/
  UINT8 int_enable; /*1-enable, 0-disable*/
  UINT8 dma_enable;
  UINT16 max_bus_wr_req_len; /*max bus request length, in bytes, valid value:
                                0x400, 0x200, 0x100, 0x080*/
  UINT16 max_bus_rd_req_len; /*max bus request length, in bytes, valid value:
                                0x400, 0x200, 0x100, 0x080*/
  UINT16 MSI_CACHEATTR;      /*16bit*/
  UINT8 cacheattr;
  UINT8 para_upd_flag;
  UINT8 pad[2];
} dma_config_t;

typedef struct DMA_CH_CONFIG_STRUCT {
  UINT8 treq_limit_en;
  UINT8 treq_limit; /*valid value: 1~32*/
  UINT8 ch_prio;    /*1:high, 0:low*/
  UINT8 wrr_weight; /*valid values:1~15*/
  UINT8 inttype;    /*bit0-ALLOW_MSI, bit1-ALLOW_IRQ*/
  UINT16 int_en;
  UINT8 upd_flg;
} dma_ch_config_t;

typedef struct TRE_INPUT_PARA_STRUCT {
  UINT64 src_addr;
  UINT64 dest_addr;
  UINT8 tre_type;
  UINT32 trans_size;
  UINT8 pad[3];
} tre_input_para_t;

typedef enum {
  CMD_DISABLE = 0,
  CMD_ENABLE = 1,
  CMD_SUSPEND = 2,
  CMD_CH_RESET = 0x9
} channel_cmd_t;

typedef enum {
  TYPE_MEMCPY = 3,
  TYPE_MEMSET = 4,
  TYPE_BARRIER = 5,
  TYPE_IMM = 0x6 /*immdidate message*/
} tre_type_t;

typedef enum {
  CH_STATE_POWERON = 0,
  CH_STATE_INITIALIZED = 1,
  CH_STATE_RESET = 2,
} channel_status_t;

typedef enum {
  DMA_STATE_POWERON = 0,
  DMA_STATE_INITIALIZED = 1,
  DMA_STATE_DISABLED = 2, /*not used*/
} dma_status_t;

typedef enum {
  R = 0,
  RW = 1,
  W = 2,
} reg_wr_property_t;

typedef enum {
  RET_SUCCESS = 0,
  RET_RO = 1,
  RET_WO = 2,
  RET_INVALID = 3,
} ret_type_t;

typedef struct REG_INFO_TABLE {
  UINT32 offest;
  UINT32 por_val;
  UINT32 bit_mask;
  UINT32 w_r_property;
  char reg_name[64];
} dma_reg_info_t;

typedef struct hidma_reg_struct {
  UINT64 addr;
  UINT32 val;
} hidma_reg_t;

extern UINT64 TRC_ring_baseaddr[HI_DMA_INSTANCE_NUM]
                               [HI_DMA_CHANNEL_NUM]; /*open to user*/
extern UINT64 EVC_ring_baseaddr[HI_DMA_INSTANCE_NUM]
                               [HI_DMA_CHANNEL_NUM]; /*open to user*/
extern channel_status_t g_TRCH_status[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM];
extern channel_status_t g_EVCH_status[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM];
extern UINT32 tre_num_each_EVC[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM];
extern dma_status_t g_DMA_status[HI_DMA_INSTANCE_NUM];
extern dma_reg_info_t hidma_reg_table[59];
extern UINT32 untrigger_tre_cnt[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM];
void hidma_gic3_irq_config(UINT32 irq_id, UINT8 trigger_mode,
                           irq_handler hidma_irq_handler);
extern UINT32 hidma_reg_read(UINT64 addr, UINT32 *val, UINT32 *idx_ptr);
extern UINT32 get_availabe_TRE_num(UINT8 dma_id, UINT8 trch_id);
extern void event_ch_cmd(UINT8 dma_id, UINT8 ch_id, channel_cmd_t cmd);
extern UINT32 reset_TRCH_by_register(UINT8 dma_id, UINT8 trch_id);
extern UINT32 reset_EVC(UINT8 dma_id, UINT8 ev_ch_id);
extern void evc_contxt_cfg(UINT8 dma_id, UINT8 ev_ch_id, UINT8 ev_inttype,
                           UINT8 forceev, UINT32 evre_num,
                           void *evre_space_ptr);
extern UINT32 produced_evre_num(UINT8 dma_id, UINT8 evch_id);
extern UINT32 add_oneTRE(UINT8 dma_id, UINT8 tr_ch_id, UINT8 ev_ch_id,
                         tre_type_t tre_type, UINT32 len, UINT32 tre_idx);
extern UINT32 hidma_add_tre_with_db(UINT8 dma_id, UINT8 trch_id, UINT8 evch_id,
                                    UINT32 num_tre_add, tre_type_t tre_type,
                                    UINT32 len, UINT32 ring_size);
extern UINT32 hidma_add_tre_without_db(UINT8 dma_id, UINT8 trch_id,
                                       UINT8 evch_id, UINT32 num_tre_add,
                                       tre_type_t tre_type, UINT32 len,
                                       UINT32 ring_size);
extern void disp_recd_tres(UINT8 dma_id, UINT8 evch_id);
extern void display_EVC_cntxt(UINT8 dma_id, UINT8 ch_id);
extern void EVR_space_init(UINT64 evre_space_ptr, UINT32 evre_num);
extern void recycle_evre(UINT8 dma_id, UINT32 num_tre_dispatch);
extern void display_TRC_cntxt(UINT8 dma_id, UINT8 ch_id);
extern void trc_contxt_cfg(UINT8 dma_id, UINT8 ch_id, UINT32 tre_num,
                           UINT64 tre_space_ptr);
extern void TR_space_init(UINT64 tre_space_ptr, UINT32 tre_num);
extern void hidma_TRC_config_para(UINT8 dma_id, UINT8 ch_id,
                                  dma_ch_config_t dma_ch_config);
extern void get_TRC_default_conf(dma_ch_config_t *default_dma_ch_ptr);
extern UINT32 hidma_reg_write(UINT64 addr, UINT32 data);
extern UINT32 validate_addr(UINT64 addr);
extern UINT32 hidma_get_reg_por(UINT64 addr);
extern void read_dma_para(UINT8 dma_id, dma_config_t *dma_config_ptr);
extern void display_dma_para(dma_config_t info);
extern void get_dma_default_conf(dma_config_t *default_dma_ptr);
extern void hidma_config_para(UINT8 dma_id, dma_config_t dma_config);
extern void get_TRC_para(UINT8 dma_id, UINT8 trch_id,
                         dma_ch_config_t *dma_ch_config);
extern void display_trc_para(dma_ch_config_t info);
#endif