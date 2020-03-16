/*==============================================================================
  All Rights Reserved.

==============================================================================*/
#include "hidma.h"
#include "Base.h"
#include "hdts_shell.h"
#include "stdlib.h"
//#include "target/heap_generic.h"
UINT32 tmp_tre_space_idx = 0;
UINT32 tre_num_each_EVC[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM] = {0};
record_tre_info_t *tre_info_evrc_ptr[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM];
UINT32 evc_recd_size[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM];
UINT32 reg_dump_data[59] = {0};
dma_reg_info_t hidma_reg_table[59] = {
    {0x0, 0x1000, 0xFFFFFFFF, R, "HIDMA_HI_DMA_MHIREGLEN"},
    {0x8, 0x1000000, 0xFFFFFFFF, R, "HIDMA_HI_DMA_MHIVER"},
    {0x10, 0x60006, 0xFFFFFFFF, R, "HIDMA_HI_DMA_MHICFG"},
    {0x30, 0x1000, 0xFFFFFFFF, R, "HIDMA_HI_DMA_DEBUGOFF"},
    {0x58, 0x10000, 0xFFFFFFFF, R, "HIDMA_HI_DMA_CCABAP_LSB"},
    {0x5c, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_CCABAP_MSB"},
    {0x60, 0x70000, 0xFFFFFFFF, R, "HIDMA_HI_DMA_ECABAP_LSB"},
    {0x64, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_ECABAP_MSB"},
    {0x400, 0x0, 0x1, RW, "HIDMA_HI_DMA_CFG"},
    {0x408, 0xa2020, 0xFFFFFF, R, "HIDMA_HI_DMA_HW_PARAM"},
    {0x410, 0, 0x3F, W, "HIDMA_HI_DMA_TR_CHRESET"},
    {0x418, 0x500, 0xFFFFF, RW, "HIDMA_HI_DMA_CHRESET_TIMEOUT"},
    {0x41C, 0x4000400, 0xFFFFFFFF, RW, "HIDMA_HI_DMA_MAX_BUS_REQ_LEN"},
    {0x420, 0x7FFF7FFF, 0x7FFF7FFF, RW, "HIDMA_HI_DMA_MAX_XACTIONS"},
    {0x430, 0x1040219, 0xF0402FF, RW, "HIDMA_HI_DMA_MOQA_CFG_ADDR"},
    {0x448, 0x3F, 0x3F, RW, "HIDMA_HI_DMA_CACHEATTR"},
    {0x458, 0xF, 0x1F, RW, "HIDMA_HI_DMA_CGC_CTRL"},
    {0x500, 0x0, 0x1, R, "HIDMA_HI_DMA_IRQ_STTS"},
    {0x508, 0x0, 0x1, W, "HIDMA_HI_DMA_IRQ_CLR"},
    {0x510, 0x0, 0x1, RW, "HIDMA_HI_DMA_IRQ_EN"},
    {0x518, 0x0, 0xFFFF, RW, "HIDMA_HI_DMA_MSI_INT_ID_BASE"},
    {0x520, 0x0, 0xFFFFFFFF, RW, "HIDMA_HI_DMA_MSI_BASE_LSB"},
    {0x524, 0x0, 0xFFFFFFFF, RW, "HIDMA_HI_DMA_MSI_BASE_MSB"},
    {0x528, 0x0, 0xFFFF, RW, "HIDMA_HI_DMA_MSI_RID_GLOBAL"},
    {0x52c, 0x0, 0xFFE0, RW, "HIDMA_HI_DMA_MSI_RID_LOCAL"},
    {0x530, 0xb, 0xFFFF, RW, "HIDMA_HI_DMA_MSI_CACHEATTR"},
    {0x534, 0x1, 0xF, RW, "HIDMA_HI_DMA_INTSET"},
    {0x540, 0x3, 0x3, RW, "HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_0"},
    {0x544, 0x3, 0x3, RW, "HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_1"},
    {0x548, 0x3, 0x3, RW, "HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_2"},
    {0x54C, 0x3, 0x3, RW, "HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_3"},
    {0x550, 0x3, 0x3, RW, "HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_4"},
    {0x554, 0x3, 0x3, RW, "HIDMA_HI_DMA_MANAGEMENT_CH_INTSET_5"},
    {0x600, 0x8, 0x3F, RW, "HIDMA_HI_DMA_MEMSET_LIMIT"},
    {0x700, 0x100, 0x1FFFF01, RW, "HIDMA_HI_DMA_TRCH_QOS_0"},
    {0x704, 0x100, 0x1FFFF01, RW, "HIDMA_HI_DMA_TRCH_QOS_1"},
    {0x708, 0x100, 0x1FFFF01, RW, "HIDMA_HI_DMA_TRCH_QOS_2"},
    {0x70c, 0x100, 0x1FFFF01, RW, "HIDMA_HI_DMA_TRCH_QOS_3"},
    {0x710, 0x100, 0x1FFFF01, RW, "HIDMA_HI_DMA_TRCH_QOS_4"},
    {0x714, 0x100, 0x1FFFF01, RW, "HIDMA_HI_DMA_TRCH_QOS_5"},
    {0x1020, 0x0, 0xFFFF, R, "HIDMA_HI_DMA_MHID_CLNT_BUS_ERR_LOG_0"},
    {0x1024, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_MHID_CLNT_BUS_ERR_LOG_1"},
    {0x102C, 0x0, 0x1, W, "HIDMA_HI_DMA_MHID_CLNT_BUS_ERR_LOG_CLR"},
    {0x1030, 0x0, 0xFFFF, R, "HIDMA_HI_DMA_EVNT_CLNT_BUS_ERR_LOG_0"},
    {0x1034, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_EVNT_CLNT_BUS_ERR_LOG_1"},
    {0x103C, 0x0, 0x1, W, "HIDMA_HI_DMA_EVNT_CLNT_BUS_ERR_LOG_CLR"},
    {0x1040, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_IDE_CLNT_BUS_ERR_LOG_0"},
    {0x1044, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_IDE_CLNT_BUS_ERR_LOG_1"},
    {0x1048, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_IDE_CLNT_BUS_ERR_LOG_2"},
    {0x104c, 0x0, 0x1, W, "HIDMA_HI_DMA_IDE_CLNT_BUS_ERR_LOG_CLR"},
    {0x1050, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_ODE_CLNT_BUS_ERR_LOG_0"},
    {0x1054, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_ODE_CLNT_BUS_ERR_LOG_1"},
    {0x1058, 0x0, 0xFFFFFFFF, R, "HIDMA_HI_DMA_ODE_CLNT_BUS_ERR_LOG_2"},
    {0x105c, 0x0, 0x1, W, "HIDMA_HI_DMA_ODE_CLNT_BUS_ERR_LOG_CLR"},
    {0x1060, 0x0, 0xFFFF, R, "HIDMA_HI_DMA_MSI_CLNT_BUS_ERR_LOG_0"},
    {0x106c, 0x0, 0x1, W, "HIDMA_HI_DMA_MSI_CLNT_BUS_ERR_LOG_CLR"},
    {0x1070, 0x0, 0xFFF1FFFF, R, "HIDMA_HI_DMA_INVALID_TRE_ERR_LOG_0"},
    {0x107c, 0x0, 0x1, W, "HIDMA_HI_DMA_INVALID_TRE_ERR_LOG_CLR"},
    {0x1080, 0x0, 0x1FF, RW, "HIDMA_HI_DMA_HW_EVENTS_CFG_ADDR"}};
const UINT32 hidma_reg_offset[59] = {
    0x0,    0x8,    0x10,   0x30,   0x58,   0x5c,   0x60,   0x64,   0x400,
    0x408,  0x410,  0x418,  0x41c,  0x420,  0x430,  0x448,  0x458,  0x500,
    0x508,  0x510,  0x518,  0x520,  0x524,  0x528,  0x52c,  0x530,  0x534,
    0x540,  0x544,  0x548,  0x54c,  0x550,  0x554,  0x600,  0x700,  0x704,
    0x708,  0x70c,  0x710,  0x714,  0x1020, 0x1024, 0x102c, 0x1030, 0x1034,
    0x103c, 0x1040, 0x1044, 0x1048, 0x104c, 0x1050, 0x1054, 0x1058, 0x105c,
    0x1060, 0x106c, 0x1070, 0x107c, 0x1080};
const UINT32 hidma_reg_por_val[59] = {
    0x1000, 0x1000000, 0x60006, 0x1000, 0x10000,   0x0,        0x70000,   0x0,
    0x0,    0xa2020,   0x0,     0x500,  0x4000400, 0x7fff7fff, 0x1040219, 0x3f,
    0xf,    0x0,       0x0,     0x0,    0x0,       0x0,        0x0,       0x0,
    0x0,    0xb,       0x1,     0x3,    0x3,       0x3,        0x3,       0x3,
    0x3,    0x8,       0x100,   0x100,  0x100,     0x100,      0x100,     0x100,
    0x0,    0x0,       0x0,     0x0,    0x0,       0x0,        0x0,       0x0,
    0x0,    0x0,       0x0,     0x0,    0x0,       0x0,        0x0,       0x0,
    0x0,    0x0,       0x0};

void event_ch_cmd(UINT8 dma_id, UINT8 ch_id, channel_cmd_t cmd) {
  out_dword_masked_ns(HIDMA_EV_CHANNEL_CNTXT0_ADDR(dma_id, ch_id), 0xff0000,
                      (cmd << 16),
                      in_dword(HIDMA_EV_CHANNEL_CNTXT0_ADDR(dma_id, ch_id)));
}

UINT32 hidma_reg_read(UINT64 addr, UINT32 *val, UINT32 *idx_ptr) {
  UINT32 j = 0;
  UINT32 i = 0;
  for (j = 0; j < HI_DMA_INSTANCE_NUM; j++) {
    if ((addr >> 24) == ((HIDMA_REG_BASE(j)) >> 24)) {
      for (i = 0; i < (sizeof(hidma_reg_table) / sizeof(dma_reg_info_t)); i++) {
        if (addr == (UINT64)(hidma_reg_table[i].offest + HIDMA_REG_BASE(j))) {
          *idx_ptr = i;
          if (hidma_reg_table[i].w_r_property != W) {
            *val = in_dword_masked(addr, hidma_reg_table[i].bit_mask);
            return RET_SUCCESS;
          } else
            return RET_WO; /*return Write only */
        }
      }
    }
  }
  return RET_INVALID; /*invalid address*/
}

void hidma_dump_register(UINT8 dma_id) {
  UINT32 j = 0;
  UINT64 reg_addr;
  UINT32 num_of_reg = 0;

  num_of_reg = sizeof(hidma_reg_table) / sizeof(dma_reg_info_t);
  for (j = 0; j < num_of_reg; j++) {
    reg_addr = hidma_reg_table[j].offest + HIDMA_REG_BASE(dma_id);
    reg_dump_data[j] = in_dword(reg_addr);
  }
}

UINT32 hidma_reg_write(UINT64 addr, UINT32 data) {
  UINT32 j;
  UINT32 i;
  for (j = 0; j < HI_DMA_INSTANCE_NUM; j++) {
    if ((addr >> 24) == ((HIDMA_REG_BASE(j)) >> 24)) {
      for (i = 0; i < (sizeof(hidma_reg_table) / sizeof(dma_reg_info_t)); i++) {
        if (addr == (hidma_reg_table[i].offest +
                     HIDMA_REG_BASE(
                         j))) /*search the register which need to be written*/
        {
          if (hidma_reg_table[i].w_r_property != R) {
            out_dword_masked_ns(addr, hidma_reg_table[i].bit_mask, data,
                                in_dword(addr));
            return RET_SUCCESS;
          } else
            return RET_RO; /*return readonly */
        }
      }
    }
  }
  return RET_INVALID; /*invalid address*/
}

UINT32 validate_addr(UINT64 addr) {
  UINT32 j;
  UINT32 i;
  for (j = 0; j < HI_DMA_INSTANCE_NUM; j++) {
    if (((addr - HIDMA_REG_BASE(j)) >> 24) == 0) {
      for (i = 0; i < (sizeof(hidma_reg_table) / sizeof(dma_reg_info_t)); i++) {
        if ((addr - HIDMA_REG_BASE(j)) ==
            hidma_reg_table[i]
                .offest) /*search the register which need to be written*/
        {
          return HDTS_SUCCESS;
        }
      }
    }
  }
  return HDTS_FAIL;
}

/*get register POR value*/
UINT32 hidma_get_reg_por(UINT64 addr) {
  UINT32 j;
  UINT32 i;
  for (j = 0; j < HI_DMA_INSTANCE_NUM; j++) {
    if (((addr - HIDMA_REG_BASE(j)) >> 24) == 0) {
      for (i = 0; i < (sizeof(hidma_reg_table) / sizeof(dma_reg_info_t)); i++) {
        if ((addr - HIDMA_REG_BASE(j)) ==
            hidma_reg_table[i]
                .offest) /*search the register which need to be written*/
        {
          return hidma_reg_table[i].por_val;
        }
      }
    }
  }
  return HDTS_FAIL;
}

/*reset EV channel*/
UINT32 reset_EVC(UINT8 dma_id, UINT8 ev_ch_id) {
  event_ch_cmd(dma_id, ev_ch_id, CMD_CH_RESET);
  while (((in_dword(HIDMA_EV_TR_CH_IRQ_STTS_ADDR(dma_id, ev_ch_id))) & 0x30) ==
         0) /*both bit4 and bit5 are not be set*/
  {
  }
  if (((in_dword(HIDMA_EV_TR_CH_IRQ_STTS_ADDR(dma_id, ev_ch_id))) & 0x10) ==
      0x10) /*bit4 EV channel reset success*/
  {
    g_EVCH_status[dma_id][ev_ch_id] = CH_STATE_RESET;
    /*clear STTS*/
    out_dword(HIDMA_EV_TR_CH_IRQ_CLR_ADDR(dma_id, ev_ch_id), 0x7f33);
    return HDTS_SUCCESS;
  } else /*bit5, EV channel reset failed*/
  {
    printf("DMA%d EVENT channel%d reset FAIL, ch status = %d\n", dma_id,
           ev_ch_id, in_dword(HIDMA_EV_TR_CH_IRQ_STTS_ADDR(dma_id, ev_ch_id)));
    /*clear STTS*/
    out_dword(HIDMA_EV_TR_CH_IRQ_CLR_ADDR(dma_id, ev_ch_id), 0x7f33);
    return HDTS_FAIL;
  }
}

/*suspend EV channel*/
UINT8 suspend_EVC(UINT8 dma_id, UINT8 ev_ch_id) {
  event_ch_cmd(dma_id, ev_ch_id, CMD_SUSPEND);
  DO_DSB;
  return HDTS_SUCCESS;
}

/*get the number of produced EVRE on EV channel*/
UINT32 produced_evre_num(UINT8 dma_id, UINT8 evch_id) {
  UINT32 ev_wr_ptr;
  UINT32 ev_doorbell_rd_ptr;
  UINT32 evre_ready = 0;
  /*compare EV write pointer and EV doorbell read ptr*/
  ev_wr_ptr = in_dword(HIDMA_EV_CHANNEL_CNTXT8_ADDR(dma_id, evch_id));
  ev_doorbell_rd_ptr =
      in_dword(HIDMA_EV_CHANNEL_DOORBELL_ADDR(dma_id, evch_id));
  if (ev_wr_ptr >= ev_doorbell_rd_ptr)
    evre_ready = (ev_wr_ptr - ev_doorbell_rd_ptr) /
                 sizeof(hidma_evre_t); /*EVRE size =16B*/
  else
    evre_ready = ((in_dword(HIDMA_EV_CHANNEL_CNTXT4_ADDR(dma_id, evch_id))) +
                  ev_wr_ptr - ev_doorbell_rd_ptr) /
                 sizeof(hidma_evre_t);
  return evre_ready;
}

/*update EV channel Consumer pointer(Read ptr)*/
void update_evc_doorbell(UINT8 dma_id, UINT8 evch_id, UINT32 num_evre_consum) {
  UINT32 ev_doorbell_rd_ptr;
  UINT32 evre_num_ring;
  evre_num_ring = (in_dword(HIDMA_EV_CHANNEL_CNTXT4_ADDR(dma_id, evch_id))) /
                  sizeof(hidma_evre_t);
  ev_doorbell_rd_ptr = in_dword(HIDMA_EV_CHANNEL_CNTXT6_ADDR(dma_id, evch_id));
  /*Update EV consumer pointer*/
  out_dword(HIDMA_EV_CHANNEL_DOORBELL_ADDR(dma_id, evch_id),
            ((ev_doorbell_rd_ptr + num_evre_consum * sizeof(hidma_evre_t)) %
             (evre_num_ring * sizeof(hidma_evre_t))));
}

/*verfiy TRE transfer result, and update EV channel Consume pointer*/
void verify_tre_evre(UINT8 dma_id, UINT8 evch_id, hidma_evre_t *evre_ptr) {
  UINT32 i, j;
  record_tre_info_t *record_ptr;
  UINT8 *src_ptr;
  UINT8 *dst_ptr;
  UINT8 memset_val;
  UINT8 diff_flag = 0;
  for (i = 0; i < evc_recd_size[dma_id][evch_id];
       i++) /*search matched TREs record*/
  {
    record_ptr = (tre_info_evrc_ptr[dma_id][evch_id]) + i;
    if (record_ptr->valid_flag == 1) /*valid tre record*/
    {
      if (record_ptr->trch_id == evre_ptr->ever_1st_word.trchid) {
        if (evre_ptr->ever_1st_word.type == 0x23) /*DMA Completion event*/
        {
          if (evre_ptr->len != 0) /*memset, memcpy*/
          {
            if (evre_ptr->ptr == record_ptr->destaddr) {
              if (evre_ptr->ever_1st_word.code == 0x1) /*Success code*/
              {
                if (record_ptr->tre_type == TYPE_MEMSET) {
                  memset_val = record_ptr->srcaddr_setval.memset_const.memsetc;
                  /*compare data*/
                  dst_ptr = (UINT8 *)evre_ptr->ptr;
                  for (j = 0; j < evre_ptr->len; j++) {
                    if ((*(dst_ptr + j)) != memset_val) {
                      printf("Data Comparision Fail for memset\n");
                      break;
                    }
                  }
                  record_ptr->valid_flag = 0; /*clear the node*/
                  update_evc_doorbell(dma_id, evch_id, 1);
                  free((void *)record_ptr->destaddr);
                  (tre_num_each_EVC[dma_id]
                                   [evch_id])--; /*find the matched TREs*/
                  break;
                } else if ((record_ptr->tre_type == TYPE_MEMCPY) &&
                           (record_ptr->srcaddr_setval.srcaddr !=
                            (UINT64)NULL)) {
                  /*compare data*/
                  dst_ptr = (UINT8 *)evre_ptr->ptr;
                  src_ptr = (UINT8 *)record_ptr->srcaddr_setval.srcaddr;
                  for (j = 0; j < evre_ptr->len; j++) {
                    if ((*(dst_ptr + j)) != (*(src_ptr + j))) {
                      printf("Data Comparision Fail for memcpy\n");
                      break;
                    }
                  }
                  record_ptr->valid_flag = 0; /*clear the node*/
                  update_evc_doorbell(dma_id, evch_id, 1);
                  free((void *)record_ptr->destaddr);
                  free((void *)record_ptr->srcaddr_setval.srcaddr);
                  tre_num_each_EVC[dma_id][evch_id]--;
                  break;
                }
              } else /*error*/
              {
                printf(
                    "ERRINFO =%x, for TRE_TYPE =%d, dst_addr=0x%p, len = %d\n",
                    evre_ptr->ever_1st_word.errinfo, record_ptr->tre_type,
                    evre_ptr->ptr, evre_ptr->len);
                if (record_ptr->tre_type == TYPE_MEMCPY) {
                  free((void *)record_ptr->destaddr);
                  free((void *)record_ptr->srcaddr_setval.srcaddr);
                } else if (record_ptr->tre_type == TYPE_MEMSET)
                  free((void *)record_ptr->destaddr);
                record_ptr->valid_flag = 0; /*clear the node*/
                update_evc_doorbell(dma_id, evch_id, 1);
                tre_num_each_EVC[dma_id][evch_id]--;
                break;
              }
            }
          } else if ((record_ptr->tre_type == TYPE_BARRIER) &&
                     (record_ptr->srcaddr_setval.srcaddr == (UINT64)NULL) &&
                     (record_ptr->destaddr == (UINT64)NULL)) /*barrier*/
          {
            record_ptr->valid_flag = 0; /*clear the node*/
            update_evc_doorbell(dma_id, evch_id, 1);
            tre_num_each_EVC[dma_id][evch_id]--;
            break;
          }
        } else if (evre_ptr->ever_1st_word.type ==
                   0x24) /*DMA immediate data event*/
        {
          if ((record_ptr->tre_type == TYPE_IMM) &&
              (record_ptr->srcaddr_setval.srcaddr == evre_ptr->ptr) &&
              (record_ptr->trans_len == evre_ptr->len)) {
            /*find the matched TREs*/
            free((void *)record_ptr->srcaddr_setval.srcaddr);
            record_ptr->valid_flag = 0; /*clear the node*/
            update_evc_doorbell(dma_id, evch_id, 1);
            tre_num_each_EVC[dma_id][evch_id]--;
            break;
          }
        }
      }
    }
  }
}

/*recycle evre, include verfiy TRE transfer result*/
void recycle_evre(UINT8 dma_id, UINT32 num_tre_dispatch) {
  UINT32 evre_cnt;
  UINT32 total_evre_consume = 0;
  UINT32 evc_wr_ptr;
  UINT32 evc_rd_idx;
  hidma_evre_t *evc_baseaddr;
  hidma_evre_t *evre_rd_ptr;
  UINT32 i, j;
  while (total_evre_consume != num_tre_dispatch) {
    for (j = 0; j < HI_DMA_CHANNEL_NUM; j++) {
      evre_cnt =
          produced_evre_num(dma_id, j); /*get the number of produced EVREs*/
      if (evre_cnt != 0)                /*consume EVRE*/
      {
        for (i = 0; i < evre_cnt; i++) {
          evc_rd_idx = in_dword(HIDMA_EV_CHANNEL_CNTXT6_ADDR(dma_id, j)) /
                       sizeof(hidma_evre_t);
          evc_baseaddr = (hidma_evre_t *)EVC_ring_baseaddr[dma_id][j];
          evre_rd_ptr = evc_baseaddr + evc_rd_idx;
          verify_tre_evre(dma_id, j, evre_rd_ptr); /*doorbell is updated*/
        }
      }
      total_evre_consume += evre_cnt;
    }
  }
}

/*classify TREs according to its evchid, and record it for future verfiy*/
UINT32 classify_tre_by_evch(UINT8 dma_id, UINT8 trch_id, UINT8 evch_id,
                            hidma_tre_t *ptr) {
  UINT32 i;
  UINT32 rsize_trc = 0;
  UINT32 rsize_evc = 0;
  UINT64 recd_idx;
  rsize_trc = (in_dword(HIDMA_TR_CHANNEL_CNTXT4_ADDR(dma_id, trch_id))) /
              sizeof(hidma_tre_t);
  rsize_evc = (in_dword(HIDMA_EV_CHANNEL_CNTXT4_ADDR(dma_id, trch_id))) /
              sizeof(hidma_evre_t);
  if ((tre_num_each_EVC[dma_id][evch_id] == 0) &&
      (evc_recd_size[dma_id][evch_id] == 0)) /*free it when???*/
  {
    evc_recd_size[dma_id][evch_id] =
        MAX(rsize_trc * HI_DMA_CHANNEL_NUM, rsize_evc);
    tre_info_evrc_ptr[dma_id][evch_id] = (record_tre_info_t *)malloc(
        evc_recd_size[dma_id][evch_id] *
        sizeof(record_tre_info_t)); /*alloc memory for record TREs*/
    if (tre_info_evrc_ptr[dma_id][evch_id] == NULL) {
      printf(
          "Memeory allocation Failed when allocate memory for TRE recording\n");
      return HDTS_FAIL;
    }
  }
  /*special scenario*/
  if (tre_num_each_EVC[dma_id][evch_id] ==
      evc_recd_size[dma_id][evch_id]) /*no space to record TREs, usually hope
                                         the ring size for each TRc are the
                                         same!!!*/
  {
    printf("no space to record TREs when classify TRE by EVCH, !!!Here require "
           "Ringsize of each TRCs are the same or EVC ringsize larger than sum "
           "of all TRCs' ring size\n");
    return HDTS_FAIL;
  }
  recd_idx = tre_num_each_EVC[dma_id][evch_id];
  /*record TREs infor on this EVC*/
  (tre_info_evrc_ptr[dma_id][evch_id] + recd_idx)->valid_flag = 1;
  (tre_info_evrc_ptr[dma_id][evch_id] + recd_idx)->trch_id = trch_id;
  (tre_info_evrc_ptr[dma_id][evch_id] + recd_idx)->tre_type =
      ptr->tre_1st_word.type;
  (tre_info_evrc_ptr[dma_id][evch_id] + recd_idx)->trans_len = ptr->len;
  (tre_info_evrc_ptr[dma_id][evch_id] + recd_idx)->destaddr = ptr->destaddr;
  if (ptr->tre_1st_word.type == TYPE_MEMSET)
    (tre_info_evrc_ptr[dma_id][evch_id] + recd_idx)
        ->srcaddr_setval.memset_const.memsetc =
        ptr->srcaddr_memsetc.memset_const.memsetc;
  else
    (tre_info_evrc_ptr[dma_id][evch_id] + recd_idx)->srcaddr_setval.srcaddr =
        ptr->srcaddr_memsetc.srcaddr;
  tre_num_each_EVC[dma_id][evch_id]++;
  return HDTS_SUCCESS;
}
// int test_src_space[0x80][0x100];
// int test_dst_space[0x80][0x100];
UINT32 add_oneTRE(UINT8 dma_id, UINT8 tr_ch_id, UINT8 ev_ch_id,
                  tre_type_t tre_type, UINT32 len, UINT32 tre_idx) {
  UINT64 src_ptr;
  UINT64 dest_ptr;
  hidma_tre_t *ring_ptr;
  UINT32 tre_wr_ptr;
  UINT32 tre_rd_ptr;
  UINT32 ring_size;
  ring_size = in_dword(HIDMA_TR_CHANNEL_CNTXT4_ADDR(dma_id, tr_ch_id)) /
              sizeof(hidma_tre_t);
  tre_wr_ptr = in_dword(HIDMA_TR_CHANNEL_CNTXT8_ADDR(dma_id, tr_ch_id));
  tre_rd_ptr = in_dword(HIDMA_TR_CHANNEL_CNTXT6_ADDR(dma_id, tr_ch_id));
  ring_ptr = (hidma_tre_t *)TRC_ring_baseaddr[dma_id][tr_ch_id];
  if ((tre_type == TYPE_MEMCPY) || (tre_type == TYPE_IMM)) {

    src_ptr = (UINT64)malloc(len);
    if (src_ptr == (UINT64)NULL) {
      printf("Mem allocation Failed when setup TRE for src addr\n");
      return HDTS_FAIL;
    }

    // src_ptr  =(UINT64)test_src_space[tmp_tre_space_idx];
  }
  if ((tre_type == TYPE_MEMSET) || (tre_type == TYPE_MEMCPY)) {

    dest_ptr = (UINT64)malloc(len);
    if (dest_ptr == (UINT64)NULL) {
      printf("Mem allocation Failed when setup TRE for dest addr\n");
      return HDTS_FAIL;
    }

    // dest_ptr  =(UINT64)test_dst_space[tmp_tre_space_idx];;
  }
  /*setup TRE*/
  ring_ptr[tre_idx].tre_1st_word.bei = 0;
  ring_ptr[tre_idx].tre_1st_word.ieob = 1;
  ring_ptr[tre_idx].tre_1st_word.evridx = ev_ch_id;
  ring_ptr[tre_idx].tre_1st_word.type =
      tre_type; /*0x3-MemCopy, 0x4-MemSet,0x5-Barrier,0x6-Immediate Message*/
  ring_ptr[tre_idx].len = len;
  if (ring_ptr[tre_idx].tre_1st_word.type == TYPE_MEMSET) /*memset*/
  {
    ring_ptr[tre_idx].srcaddr_memsetc.memset_const.memsetc = MEMSET_PATTERN;
    ring_ptr[tre_idx].destaddr = (UINT64)dest_ptr;
  } else if (tre_type == TYPE_MEMCPY) {
    ring_ptr[tre_idx].srcaddr_memsetc.srcaddr = (UINT64)src_ptr;
    ring_ptr[tre_idx].destaddr = (UINT64)dest_ptr;
  } else if (tre_type == TYPE_IMM) {
    ring_ptr[tre_idx].srcaddr_memsetc.srcaddr = (UINT64)src_ptr;
    ring_ptr[tre_idx].destaddr = (UINT64)NULL;
    ring_ptr[tre_idx].tre_1st_word.ieob =
        1; /*TRE constraints for immediate type*/
  } else if (tre_type == TYPE_BARRIER) {
    ring_ptr[tre_idx].len = 0; /*TRE constraints for barrier type*/
    ring_ptr[tre_idx].srcaddr_memsetc.srcaddr = (UINT64)NULL;
    ring_ptr[tre_idx].destaddr = (UINT64)NULL;
  }
  ring_ptr[tre_idx].tre_7th_word.mmuadst = 0;      /*Normal address*/
  ring_ptr[tre_idx].tre_7th_word.ptda = 0;         /*0-IO mmu enabled*/
  ring_ptr[tre_idx].tre_7th_word.cacheattrd = 0xb; /*this value come from POR*/
  ring_ptr[tre_idx].tre_7th_word.mmuasrc = 0;      /*Normal address*/
  ring_ptr[tre_idx].tre_7th_word.ptsa = 0;         /*0-IO mmu enabled*/
  ring_ptr[tre_idx].tre_7th_word.cacheattrs = 0xb; /*this value come from POR*/
  return HDTS_SUCCESS;
}

/*get the number of spare TREs*/
UINT32 get_availabe_TRE_num(UINT8 dma_id, UINT8 trch_id) {
  UINT32 rd_ptr;
  UINT32 wr_ptr;
  UINT32 ring_size;
  UINT32 availabe_num;
  ring_size = in_dword(HIDMA_TR_CHANNEL_CNTXT4_ADDR(dma_id, trch_id)) /
              sizeof(hidma_tre_t);
  rd_ptr = (in_dword(HIDMA_TR_CHANNEL_CNTXT6_ADDR(dma_id, trch_id))) /
           sizeof(hidma_tre_t);
  wr_ptr = (in_dword(HIDMA_TR_CHANNEL_CNTXT8_ADDR(dma_id, trch_id))) /
           sizeof(hidma_tre_t);
  if (rd_ptr == wr_ptr) /*empty*/
    availabe_num = ring_size - 1;
  else
    availabe_num = ((rd_ptr - wr_ptr + ring_size) % ring_size) - 1;
  return availabe_num;
}

void display_dma_para(dma_config_t info) {
  printf("memsetjob = 0x%x\n", info.memset_max_num_jobs);
  printf("reqprio = 0x%x\n", info.client_req_prio);
  printf("wrtiden = 0x%x\n", info.const_wr_tid_en);
  printf("rdtiden = 0x%x\n", info.const_rd_tid_en);
  printf("beatiden = 0x%x\n", info.qsb_beat_index_en);
  printf("rdxact = 0x%x\n", info.max_rd_xactions);
  printf("wrxact = 0x%x\n", info.max_wr_xactions);
  printf("inttyp = 0x%x\n", info.inttype);
  printf("inten = 0x%x\n", info.int_enable);
  printf("wrlen = 0x%x\n", info.max_bus_wr_req_len);
  printf("rdlen = 0x%x\n", info.max_bus_rd_req_len);
  printf("msiattr = 0x%x\n", info.MSI_CACHEATTR);
  printf("cacheattr = 0x%x\n", info.cacheattr);
  printf("dmaenable = 0x%x\n", info.dma_enable);
}

void display_trc_para(dma_ch_config_t info) {
  printf("treq_limit_en = 0x%x\n", info.treq_limit_en);
  printf("treq_limit = 0x%x\n", info.treq_limit);
  printf("ch_prio = 0x%x\n", info.ch_prio);
  printf("wrr_weight = 0x%x\n", info.wrr_weight);
  printf("inttype = 0x%x\n", info.inttype);
  printf("int_en = 0x%x\n", info.int_en);
}

void display_TRC_cntxt(UINT8 dma_id, UINT8 ch_id) {
  printf("DMA%d TRC%d, CNTXT_0 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_TR_CHANNEL_CNTXT0_ADDR(dma_id, ch_id)));
  printf("DMA%d TRC%d, CNTXT_2 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_TR_CHANNEL_CNTXT2_ADDR(dma_id, ch_id)));
  printf("DMA%d TRC%d, CNTXT_3 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_TR_CHANNEL_CNTXT3_ADDR(dma_id, ch_id)));
  printf("DMA%d TRC%d, CNTXT_4 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_TR_CHANNEL_CNTXT4_ADDR(dma_id, ch_id)));
  printf("DMA%d TRC%d, CNTXT_6 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_TR_CHANNEL_CNTXT6_ADDR(dma_id, ch_id)));
  printf("DMA%d TRC%d, CNTXT_8 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_TR_CHANNEL_CNTXT8_ADDR(dma_id, ch_id)));
  printf("DMA%d TRC%d, CNTXT_10 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_TR_CHANNEL_CNTXT10_ADDR(dma_id, ch_id)));
}

void display_EVC_cntxt(UINT8 dma_id, UINT8 ch_id) {
  printf("DMA%d EVC%d, CNTXT_0 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_EV_CHANNEL_CNTXT0_ADDR(dma_id, ch_id)));
  printf("DMA%d EVC%d, CNTXT_1 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_EV_CHANNEL_CNTXT1_ADDR(dma_id, ch_id)));
  printf("DMA%d EVC%d, CNTXT_2 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_EV_CHANNEL_CNTXT2_ADDR(dma_id, ch_id)));
  printf("DMA%d EVC%d, CNTXT_3 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_EV_CHANNEL_CNTXT3_ADDR(dma_id, ch_id)));
  printf("DMA%d EVC%d, CNTXT_4 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_EV_CHANNEL_CNTXT4_ADDR(dma_id, ch_id)));
  printf("DMA%d EVC%d, CNTXT_6 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_EV_CHANNEL_CNTXT6_ADDR(dma_id, ch_id)));
  printf("DMA%d EVC%d, CNTXT_8 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_EV_CHANNEL_CNTXT8_ADDR(dma_id, ch_id)));
  printf("DMA%d EVC%d, CNTXT_12 = 0x%x\n", dma_id, ch_id,
         in_dword(HIDMA_EV_CHANNEL_CNTXT12_ADDR(dma_id, ch_id)));
}

/*disp EV channel's unfinished TRE*/
void disp_recd_tres(UINT8 dma_id, UINT8 evch_id) {
  record_tre_info_t *recd_baseaddr;
  UINT32 i;
  UINT32 cnt = 0;
  recd_baseaddr = tre_info_evrc_ptr[dma_id][evch_id];
  for (i = 0; i < evc_recd_size[dma_id][evch_id]; i++) {
    if ((recd_baseaddr + i)->valid_flag == 1) {
      printf("location(%d)valid_flag = %d, trch_id = %d, tre_type=%d, len = "
             "%d, destaddr=%p, saddr = %p\n",
             i, (recd_baseaddr + i)->valid_flag, (recd_baseaddr + i)->trch_id,
             (recd_baseaddr + i)->tre_type, (recd_baseaddr + i)->trans_len,
             (recd_baseaddr + i)->destaddr,
             (recd_baseaddr + i)->srcaddr_setval.srcaddr);
      cnt++;
    }
  }
  if (cnt != tre_num_each_EVC[dma_id][evch_id])
    printf("the untrigged tre number don't match with EVC TREs record, actual "
           "number=%d, record_cnt=%d\n",
           cnt, tre_num_each_EVC[dma_id][evch_id]);
}

UINT32 hidma_add_tre_with_db(UINT8 dma_id, UINT8 trch_id, UINT8 evch_id,
                             UINT32 num_tre_add, tre_type_t tre_type,
                             UINT32 len, UINT32 ring_size) {
  UINT32 i;
  UINT32 free_tre_num;
  UINT32 left_tre_num;
  UINT32 cur_dispatch_num;
  hidma_tre_t *trc_ring_ptr;
  UINT32 start_w_idx;
  UINT32 ret_val;
  left_tre_num = num_tre_add;
  while (left_tre_num != 0) {
    free_tre_num = get_availabe_TRE_num(dma_id, trch_id);
    while (free_tre_num == 0) /*wait for there is spara TREs*/
    {
    }
    if (free_tre_num >= left_tre_num) /*one-time dispatch TREs*/
      cur_dispatch_num = left_tre_num;
    else
      cur_dispatch_num = free_tre_num;
    start_w_idx = (in_dword(HIDMA_TR_CHANNEL_CNTXT8_ADDR(dma_id, trch_id))) /
                  sizeof(hidma_tre_t); /*get the w_ptr*/
    for (i = 0; i < cur_dispatch_num; i++) {
      tmp_tre_space_idx = i;
      ret_val = add_oneTRE(dma_id, trch_id, evch_id, tre_type, len,
                           (start_w_idx + i) % ring_size);
      if (ret_val == HDTS_FAIL)
        return HDTS_FAIL;
      trc_ring_ptr = (hidma_tre_t *)TRC_ring_baseaddr[dma_id][trch_id];
      ret_val = classify_tre_by_evch(
          dma_id, trch_id, evch_id,
          trc_ring_ptr + ((start_w_idx + i) %
                          ring_size)); /*record TREs for future verify*/
      if (ret_val == HDTS_FAIL)
        return HDTS_FAIL;
    }
    left_tre_num -= cur_dispatch_num;
    out_dword(HIDMA_TR_CHANNEL_DOORBELL_ADDR(dma_id, trch_id),
              ((in_dword(HIDMA_TR_CHANNEL_CNTXT6_ADDR(dma_id, trch_id))) +
               cur_dispatch_num * sizeof(hidma_tre_t)) %
                  (ring_size * sizeof(hidma_tre_t)));
    DO_DSB;
    recycle_evre(dma_id, cur_dispatch_num);
  }
  return HDTS_SUCCESS;
}

UINT32 hidma_add_tre_without_db(UINT8 dma_id, UINT8 trch_id, UINT8 evch_id,
                                UINT32 num_tre_add, tre_type_t tre_type,
                                UINT32 len, UINT32 ring_size) {
  UINT32 empty_tre_num;
  UINT32 start_w_idx;
  UINT32 i;
  UINT32 ret_val;
  hidma_tre_t *trc_ring_ptr;
  empty_tre_num = get_availabe_TRE_num(dma_id, trch_id) -
                  untrigger_tre_cnt[dma_id][trch_id];
  if (empty_tre_num < num_tre_add) /*no enough empty TREs*/
  {
    printf("hidma_tre addwodb free TREs(%d) is less than added TREs(%d), "
           "suggest to increase ring size or reduce tre numbers\n",
           empty_tre_num, num_tre_add);
    return HDTS_FAIL;
  }
  start_w_idx = ((in_dword(HIDMA_TR_CHANNEL_CNTXT8_ADDR(dma_id, trch_id))) /
                     sizeof(hidma_tre_t) +
                 untrigger_tre_cnt[dma_id][trch_id]) %
                ring_size;
  for (i = 0; i < num_tre_add; i++) {
    ret_val = add_oneTRE(dma_id, trch_id, evch_id, tre_type, len,
                         (start_w_idx + i) % ring_size);
    if (ret_val == HDTS_FAIL)
      return HDTS_FAIL;
    trc_ring_ptr = (hidma_tre_t *)TRC_ring_baseaddr[dma_id][trch_id];
    ret_val = classify_tre_by_evch(
        dma_id, trch_id, evch_id,
        trc_ring_ptr +
            ((start_w_idx + i) % ring_size)); /*record TREs for future verify*/
    if (ret_val == HDTS_FAIL)
      return HDTS_FAIL;
  }
  untrigger_tre_cnt[dma_id][trch_id] += num_tre_add;
  if (empty_tre_num == num_tre_add) /*special scenario: TR is full, need to
                                       trigger DMA transfer right now*/
  {
    out_dword(HIDMA_TR_CHANNEL_DOORBELL_ADDR(dma_id, trch_id),
              ((in_dword(HIDMA_TR_CHANNEL_CNTXT8_ADDR(dma_id, trch_id))) +
               untrigger_tre_cnt[dma_id][trch_id] * sizeof(hidma_tre_t)) %
                  (ring_size * sizeof(hidma_tre_t)));
    DO_DSB;
    recycle_evre(dma_id, untrigger_tre_cnt[dma_id][trch_id]); /*waiting untill
                                                                 recycle all
                                                                 dispatched
                                                                 TREs*/
    untrigger_tre_cnt[dma_id][trch_id] = 0;
  }
  return HDTS_SUCCESS;
}
