/*==============================================================================
  All Rights Reserved.

==============================================================================*/
#include "hidma.h"
#include "ProcessorBind.h"
#include "hdts_shell.h"
#include <target/smp.h>

channel_status_t g_TRCH_status[HI_DMA_INSTANCE_NUM]
                              [HI_DMA_CHANNEL_NUM] = {CH_STATE_POWERON};
channel_status_t g_EVCH_status[HI_DMA_INSTANCE_NUM]
                              [HI_DMA_CHANNEL_NUM] = {CH_STATE_POWERON};
dma_status_t g_DMA_status[HI_DMA_INSTANCE_NUM] = {DMA_STATE_POWERON};

UINT32 reset_TRCH_by_register(UINT8 dma_id, UINT8 trch_id) {
  out_dword_masked_ns(HIDMA_HI_DMA_TR_CHRESET_ADDR(dma_id), (0x1 << trch_id),
                      (0x1 << trch_id),
                      in_dword(HIDMA_HI_DMA_TR_CHRESET_ADDR(dma_id)));
  while (((in_dword(HIDMA_EV_TR_CH_IRQ_STTS_ADDR(dma_id, trch_id))) & 0x3000) ==
         0) /*both bit12 and bit13 are not be set*/
  {
  }
  if (((in_dword(HIDMA_EV_TR_CH_IRQ_STTS_ADDR(dma_id, trch_id))) & 0x1000) ==
      0x1000) /*bit12, TR reset successfully*/
  {
    g_TRCH_status[dma_id][trch_id] = CH_STATE_RESET;
    return HDTS_SUCCESS;
  } else {
    return HDTS_FAIL;
  }
}

void read_dma_para(UINT8 dma_id, dma_config_t *dma_config_ptr) {
  dma_config_ptr->MSI_CACHEATTR =
      in_dword_masked(HIDMA_HI_DMA_MSI_CACHEATTR_ADDR(dma_id), 0xffff);
  dma_config_ptr->memset_max_num_jobs =
      in_dword_masked(HIDMA_HI_DMA_MEMSET_LIMIT_ADDR(dma_id), 0x3f);
  dma_config_ptr->client_req_prio =
      in_dword_masked(HIDMA_HI_DMA_MOQA_CFG_ADDR(dma_id), 0xff);
  dma_config_ptr->const_rd_tid_en =
      in_dword_masked(HIDMA_HI_DMA_MOQA_CFG_ADDR(dma_id), 0x2000000) >> 25;
  dma_config_ptr->const_wr_tid_en =
      in_dword_masked(HIDMA_HI_DMA_MOQA_CFG_ADDR(dma_id), 0x4000000) >> 26;
  dma_config_ptr->qsb_beat_index_en =
      in_dword_masked(HIDMA_HI_DMA_MOQA_CFG_ADDR(dma_id), 0x1000000) >> 24;
  dma_config_ptr->max_rd_xactions =
      in_dword_masked(HIDMA_HI_DMA_MAX_XACTIONS_ADDR(dma_id), 0x1f);
  dma_config_ptr->max_wr_xactions =
      in_dword_masked(HIDMA_HI_DMA_MAX_XACTIONS_ADDR(dma_id), 0x1f0000) >> 16;
  dma_config_ptr->max_bus_rd_req_len =
      in_dword_masked(HIDMA_HI_DMA_MAX_BUS_REQ_LEN_ADDR(dma_id), 0xffff);
  dma_config_ptr->max_bus_wr_req_len =
      in_dword_masked(HIDMA_HI_DMA_MAX_BUS_REQ_LEN_ADDR(dma_id), 0xffff0000) >>
      16;
  dma_config_ptr->cacheattr =
      in_dword_masked(HIDMA_HI_DMA_CACHEATTR_ADDR(dma_id), 0x3f);
  dma_config_ptr->inttype =
      in_dword_masked(HIDMA_HI_DMA_INTSET_ADDR(dma_id), 0xf);
  dma_config_ptr->int_enable =
      in_dword_masked(HIDMA_HI_DMA_IRQ_EN_ADDR(dma_id), 0x1);
  dma_config_ptr->dma_enable =
      in_dword_masked(HIDMA_HI_DMA_CFG_ADDR(dma_id), 0x1);
}

void get_dma_default_conf(dma_config_t *default_dma_ptr) {
  default_dma_ptr->memset_max_num_jobs = 8;
  default_dma_ptr->client_req_prio = 0x19; /*1-high, 0-low, bit mapping:
                                              bit0:MHID manager, bit1:IDE,
                                              bit2:ODE, bit3:event Eng, bit4:
                                              MSI eng*/
  default_dma_ptr->const_wr_tid_en = 0;
  default_dma_ptr->const_rd_tid_en = 0;
  default_dma_ptr->qsb_beat_index_en = 1;
  default_dma_ptr->max_rd_xactions = 0x1f;
  default_dma_ptr->max_wr_xactions = 0x1f;
  default_dma_ptr->inttype = 1;    /*0-MSI, 1-IRQ, 9-NON*/
  default_dma_ptr->int_enable = 1; /*1-enable, 0-disable*/
  default_dma_ptr->dma_enable = 1;
  default_dma_ptr->max_bus_wr_req_len = 0x400; /*max bus request length, in
                                                  bytes, valid value: 0x400,
                                                  0x200, 0x100, 0x080*/
  default_dma_ptr->max_bus_rd_req_len = 0x400; /*max bus request length, in
                                                  bytes, valid value: 0x400,
                                                  0x200, 0x100, 0x080*/
  default_dma_ptr->MSI_CACHEATTR = 0xB;        /*16bit*/
  default_dma_ptr->cacheattr = 0x3f;           // ll modify, 0x3f->0
}

void get_TRC_default_conf(dma_ch_config_t *default_dma_ch_ptr) {
  /*below most of parameters comes from POR value*/
  default_dma_ch_ptr->treq_limit_en = 0;
  default_dma_ch_ptr->treq_limit = 0; /*valid value: 1~32*/
  default_dma_ch_ptr->ch_prio = 0;    /*1:high, 0:low*/
  default_dma_ch_ptr->wrr_weight = 1; /*valid values:1~15*/
  default_dma_ch_ptr->inttype = 2;    /*bit0-ALLOW_MSI, bit1-ALLOW_IRQ*/
  default_dma_ch_ptr->int_en = 0x733; /*irq en*/
}

void hidma_config_para(UINT8 dma_id, dma_config_t dma_config) {
  UINT32 tmp_reg_val = 0;
  out_dword_masked_ns(HIDMA_HI_DMA_MSI_CACHEATTR_ADDR(dma_id), 0xffff,
                      dma_config.MSI_CACHEATTR,
                      in_dword(HIDMA_HI_DMA_MSI_CACHEATTR_ADDR(dma_id)));
  out_dword_masked_ns(HIDMA_HI_DMA_MEMSET_LIMIT_ADDR(dma_id), 0x3f,
                      dma_config.memset_max_num_jobs,
                      in_dword(HIDMA_HI_DMA_MEMSET_LIMIT_ADDR(dma_id)));
  tmp_reg_val = (dma_config.client_req_prio & 0xff) |
                ((dma_config.const_rd_tid_en & 0x1) << 25) |
                ((dma_config.const_wr_tid_en & 0x1) << 26) |
                ((dma_config.qsb_beat_index_en & 0x1) << 24);
  out_dword_masked_ns(HIDMA_HI_DMA_MOQA_CFG_ADDR(dma_id), 0x70000ff,
                      tmp_reg_val,
                      in_dword(HIDMA_HI_DMA_MOQA_CFG_ADDR(dma_id)));
  tmp_reg_val = (dma_config.max_rd_xactions & 0x1f) |
                ((dma_config.max_wr_xactions & 0x1f) << 16);
  out_dword_masked_ns(HIDMA_HI_DMA_MAX_XACTIONS_ADDR(dma_id), 0x001f001f,
                      tmp_reg_val,
                      in_dword(HIDMA_HI_DMA_MAX_XACTIONS_ADDR(dma_id)));
  tmp_reg_val = (dma_config.max_bus_rd_req_len & 0xffff) |
                ((dma_config.max_bus_wr_req_len & 0xffff) << 16);
  out_dword_masked_ns(HIDMA_HI_DMA_MAX_BUS_REQ_LEN_ADDR(dma_id), 0xffffffff,
                      tmp_reg_val,
                      in_dword(HIDMA_HI_DMA_MAX_BUS_REQ_LEN_ADDR(dma_id)));
  out_dword_masked_ns(HIDMA_HI_DMA_CACHEATTR_ADDR(dma_id), 0x3f,
                      dma_config.cacheattr,
                      in_dword(HIDMA_HI_DMA_CACHEATTR_ADDR(
                          dma_id))); /*3f-all channel cache attribute used*/
  out_dword_masked_ns(
      HIDMA_HI_DMA_INTSET_ADDR(dma_id), 0xf, dma_config.inttype,
      in_dword(HIDMA_HI_DMA_INTSET_ADDR(dma_id))); /*config int type*/
  out_dword_masked_ns(
      HIDMA_HI_DMA_IRQ_EN_ADDR(dma_id), 0x1, dma_config.int_enable,
      in_dword(HIDMA_HI_DMA_IRQ_EN_ADDR(dma_id))); /*enable interrupt*/
}

void hidma_TRC_config_para(UINT8 dma_id, UINT8 ch_id,
                           dma_ch_config_t dma_ch_config) {
  UINT32 tmp_reg_val = 0;
  tmp_reg_val = ((dma_ch_config.treq_limit_en & 0x1) << 23) |
                ((dma_ch_config.treq_limit & 0x7f) << 16) |
                ((dma_ch_config.ch_prio & 0x1) << 15) |
                ((dma_ch_config.wrr_weight & 0x7f) << 8);
  out_dword_masked_ns(HIDMA_HI_DMA_TRCH_QOS_ADDR(dma_id, ch_id), 0x00ffff00,
                      tmp_reg_val,
                      in_dword(HIDMA_HI_DMA_TRCH_QOS_ADDR(dma_id, ch_id)));
  out_dword(HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_ADDR(dma_id, ch_id),
            dma_ch_config.inttype & 0x3);
  /*all interrupt enable*/
  out_dword_masked_ns(HIDMA_EV_TR_CH_IRQ_EN_ADDR(dma_id, ch_id), 0x733,
                      (dma_ch_config.int_en & 0x733),
                      in_dword(HIDMA_EV_TR_CH_IRQ_EN_ADDR(dma_id, ch_id)));
}

void get_TRC_para(UINT8 dma_id, UINT8 trch_id, dma_ch_config_t *dma_ch_config) {
  dma_ch_config->treq_limit_en =
      (in_dword_masked(HIDMA_HI_DMA_TRCH_QOS_ADDR(dma_id, trch_id),
                       0x800000)) >>
      23;
  dma_ch_config->treq_limit =
      (in_dword_masked(HIDMA_HI_DMA_TRCH_QOS_ADDR(dma_id, trch_id),
                       0x7f0000)) >>
      16;
  dma_ch_config->ch_prio =
      (in_dword_masked(HIDMA_HI_DMA_TRCH_QOS_ADDR(dma_id, trch_id), 0x8000)) >>
      15;
  dma_ch_config->wrr_weight =
      (in_dword_masked(HIDMA_HI_DMA_TRCH_QOS_ADDR(dma_id, trch_id), 0x7f00)) >>
      8;
  dma_ch_config->inttype = in_dword_masked(
      HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_ADDR(dma_id, trch_id), 0x3);
  dma_ch_config->int_en =
      in_dword_masked(HIDMA_EV_TR_CH_IRQ_EN_ADDR(dma_id, trch_id), 0x733);
}

void trc_contxt_cfg(UINT8 dma_id, UINT8 ch_id, UINT32 tre_num,
                    UINT64 tre_space_ptr) {
  UINT64 transfer_ring_baseaddr;
  UINT32 tmp_val;
  transfer_ring_baseaddr = (UINT64)tre_space_ptr;
  tmp_val = (UINT32)transfer_ring_baseaddr; /*get the LSB of 64bit address*/
  out_dword(HIDMA_TR_CHANNEL_CNTXT2_ADDR(dma_id, ch_id), tmp_val);
  tmp_val =
      (UINT32)(transfer_ring_baseaddr >> 32); /*get the LSB of 64bit address*/
  out_dword(HIDMA_TR_CHANNEL_CNTXT3_ADDR(dma_id, ch_id), tmp_val); // MSB
  out_dword(HIDMA_TR_CHANNEL_CNTXT4_ADDR(dma_id, ch_id),
            tre_num * sizeof(hidma_tre_t));
  out_dword(HIDMA_TR_CHANNEL_CNTXT10_ADDR(dma_id, ch_id), (0xb & 0x3fff));
  /*enable this TR channel*/
  out_dword_masked_ns(HIDMA_TR_CHANNEL_CNTXT0_ADDR(dma_id, ch_id), 0xff0000,
                      0x10000,
                      in_dword(HIDMA_TR_CHANNEL_CNTXT0_ADDR(dma_id, ch_id)));
}

void evc_contxt_cfg(UINT8 dma_id, UINT8 ev_ch_id, UINT8 ev_inttype,
                    UINT8 forceev, UINT32 evre_num, void *evre_space_ptr) {
  UINT32 tmp_val;
  UINT64 ev_ring_baseaddr;
  ev_ring_baseaddr = (UINT64)evre_space_ptr;
  tmp_val = (UINT32)ev_ring_baseaddr; /*get the LSB of 64bit address*/
  out_dword(HIDMA_EV_CHANNEL_CNTXT2_ADDR(dma_id, ev_ch_id), tmp_val);
  tmp_val = (UINT32)(ev_ring_baseaddr >> 32); /*get the MSB of 64bit address*/
  out_dword(HIDMA_EV_CHANNEL_CNTXT3_ADDR(dma_id, ev_ch_id), tmp_val);
  tmp_val = ((forceev & 0x1) << 4) | (ev_inttype & 0xf);
  out_dword_masked_ns(HIDMA_EV_CHANNEL_CNTXT1_ADDR(dma_id, ev_ch_id), 0x1f,
                      tmp_val,
                      in_dword(HIDMA_EV_CHANNEL_CNTXT1_ADDR(dma_id, ev_ch_id)));
  out_dword(HIDMA_EV_CHANNEL_CNTXT4_ADDR(dma_id, ev_ch_id),
            evre_num * sizeof(hidma_evre_t));
  out_dword(HIDMA_EV_CHANNEL_CNTXT12_ADDR(dma_id, ev_ch_id), (0xb & 0x3fff));
  /*enable this EV channel*/
  out_dword_masked_ns(HIDMA_EV_CHANNEL_CNTXT0_ADDR(dma_id, ev_ch_id), 0xff0000,
                      0x10000,
                      in_dword(HIDMA_EV_CHANNEL_CNTXT0_ADDR(dma_id, ev_ch_id)));
  /*the context_10 field no defied, I need more infor,,,,,,,,*/
}

void TR_space_init(UINT64 tre_space_ptr, UINT32 tre_num) {
  UINT32 i = 0;
  UINT8 *ptr;
  /*clear all TRE memory before configuration*/
  ptr = (UINT8 *)tre_space_ptr;
  for (i = 0; i < (sizeof(hidma_tre_t) * tre_num); i++) {
    *(ptr + i) = 0;
  }
}

void EVR_space_init(UINT64 evre_space_ptr, UINT32 evre_num) {
  UINT32 i = 0;
  UINT8 *ptr;
  /*clear all TRE memory before configuration*/
  ptr = (UINT8 *)evre_space_ptr;
  for (i = 0; i < (sizeof(hidma_evre_t) * evre_num); i++) {
    *(ptr + i) = 0;
  }
}
