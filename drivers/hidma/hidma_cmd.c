/*==============================================================================
  All Rights Reserved.

==============================================================================*/
#include "hdts_shell.h"
#include "stdlib.h"
#include "target/cmdline.h"
#include "target/memory.h"
#include <hidma.h>
//#include "target/heap_generic.h"
#define SUCCESS 0
#define FAIL (-1)
dma_config_t dma_config_para[HI_DMA_INSTANCE_NUM];
UINT32 untrigger_tre_cnt[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM] = {0};
dma_ch_config_t tmp_trch_conf[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM];
dma_config_t backup_dma_para[HI_DMA_INSTANCE_NUM];
dma_ch_config_t TRC_config[HI_DMA_INSTANCE_NUM][HI_DMA_CHANNEL_NUM];
UINT64 TRC_unalign_baseaddr[HI_DMA_INSTANCE_NUM]
                           [HI_DMA_CHANNEL_NUM]; /*not open to user*/
UINT64 EVC_unalign_baseaddr[HI_DMA_INSTANCE_NUM]
                           [HI_DMA_CHANNEL_NUM]; /*not open to user*/
UINT64 TRC_ring_baseaddr[HI_DMA_INSTANCE_NUM]
                        [HI_DMA_CHANNEL_NUM]; /*open to user*/
UINT64 EVC_ring_baseaddr[HI_DMA_INSTANCE_NUM]
                        [HI_DMA_CHANNEL_NUM]; /*open to user*/
UINT32 rr_reg_cnt = 0;
hidma_reg_t *hidma_reg_ptr;
extern unsigned long long strtoull(const char *__restrict, char **__restrict,
                                   int);
int hidma_reg_cmd(int argc, char *argv[]) {
  unsigned long long addr;
  UINT32 ret_val;
  UINT32 data;
  UINT64 in_addr;
  UINT32 i;
  UINT8 dma_id;
  UINT32 table_idx;
  if ((strcmp(argv[2], "rd") != 0) && (strcmp(argv[2], "wr") != 0) &&
      (strcmp(argv[2], "rr") != 0) && (strcmp(argv[2], "rrcpor") != 0)) {
    printf("unknown cmd for hidma reg\n");
    return FAIL;
  }
  if (strcmp(argv[2], "rd") == 0) {
    addr = strtoull(argv[3], 0, 0);
    ret_val = hidma_reg_read(addr, &data, &table_idx);
    if (ret_val == RET_SUCCESS) {
      printf("Addr %p : 0x%08x\n", addr, data);
      return SUCCESS;
    } else {
      if (ret_val == RET_INVALID)
        printf("Addr %p don't exist\n", addr);
      else
        printf("Addr %p is write-only\n", addr);
      return FAIL;
    }
  }
  if (strcmp(argv[2], "wr") == 0) {
    addr = strtoull(argv[3], 0, 0);
    data = strtoull(argv[4], 0, 0);
    ret_val = hidma_reg_write(addr, data);
    if (ret_val == RET_SUCCESS)
      return SUCCESS;
    else {
      if (ret_val == RET_INVALID)
        printf("Addr %p don't exist\n", addr);
      else
        printf("Addr %p is read-only\n", addr);
      return FAIL;
    }
  }
  if ((strcmp(argv[2], "rr") == 0) || (strcmp(argv[2], "rrcpor") == 0)) {
    if ((rr_reg_cnt != 0) && (hidma_reg_ptr != NULL)) /*free pervious buffer*/
    {
      free((void *)hidma_reg_ptr);
      rr_reg_cnt = 0;
      hidma_reg_ptr = NULL;
    }
    if (strcmp(argv[3], "all") == 0) {
      dma_id = strtoull(argv[4], 0, 0);
      if (dma_id >= HI_DMA_INSTANCE_NUM) {
        printf("hidma reg rr/rrcpor input parameter incorrect dma_id =%d\n",
               dma_id);
        return FAIL;
      } else
        rr_reg_cnt = TOTAL_NUM_HIDMA_REG; /*number of all HIDMA registers*/
    } else {
      rr_reg_cnt = strtoull(argv[3], 0, 0);
      if ((rr_reg_cnt == 0) ||
          ((rr_reg_cnt > 0) && (argc != (4 + rr_reg_cnt)))) {
        printf("hidma reg rr/rrcpor illegal parameter reg_cnt =%d, number of "
               "addr = %d\n",
               rr_reg_cnt, argc - 4);
        return FAIL;
      }
    }
    hidma_reg_ptr = (hidma_reg_t *)malloc(sizeof(hidma_reg_t) * rr_reg_cnt);
    memset(hidma_reg_ptr, 0, sizeof(hidma_reg_t) * rr_reg_cnt);
    for (i = 0; i < rr_reg_cnt; i++) {
      if (strcmp(argv[3], "all") == 0)
        addr = hidma_reg_table[i].offest + HIDMA_REG_BASE(dma_id);
      else
        addr = strtoull(argv[4 + i], 0, 0);
      ret_val = hidma_reg_read(addr, &hidma_reg_ptr[i].val, &table_idx);
      if (ret_val == RET_INVALID) {
        printf("hidma reg rr/rrcpor address(%p) is incorrect\n", addr);
        return FAIL;
      } else {
        hidma_reg_ptr[i].addr = addr;
        if (strcmp(argv[2], "rrcpor") == 0) {
          if (validate_addr(addr) == HDTS_FAIL) {
            printf("illegal address for hidma reg rrcpor\n");
            return FAIL;
          }

          if (hidma_get_reg_por(addr) != hidma_reg_ptr[i].val)
            printf("***Diff:%s(%p) val = 0x%x,POR val= 0x%x\n",
                   hidma_reg_table[table_idx].reg_name, addr,
                   hidma_reg_ptr[i].val, hidma_get_reg_por(addr));
          else
            printf("***Match:%s(%p) val = 0x%x\n",
                   hidma_reg_table[table_idx].reg_name, addr,
                   hidma_reg_ptr[i].val, hidma_get_reg_por(addr));
        } else
          printf("Addr %p(%s) : 0x%08x\n", addr,
                 hidma_reg_table[table_idx].reg_name, hidma_reg_ptr[i].val);
      }
    }
    return SUCCESS;
  }
  return SUCCESS;
}

int hidma_dma_cmd(int argc, char *argv[]) {
  UINT8 tr_ev_id;
  UINT8 dma_id;
  UINT32 ret_val;
  dma_config_t tmp_dma_cfg;
  UINT32 para_grp_num;
  UINT32 i;
  if ((strcmp(argv[2], "disable") != 0) && (strcmp(argv[2], "enable") != 0) &&
      (strcmp(argv[2], "rdpara") != 0) && (strcmp(argv[2], "updpara") != 0) &&
      (strcmp(argv[2], "cfgdflt") != 0) && (strcmp(argv[2], "updact") != 0)) {
    printf("unknown cmd for hidma_dma\n");
    return FAIL;
  }
  if (argc < 4) {
    printf("hidma_dma number of input parameter incorrect \n");
    return FAIL;
  }
  dma_id = strtoull(argv[3], 0, 0);
  if (dma_id >= HI_DMA_INSTANCE_NUM) {
    printf("hidma_dma input parameter incorrect dma_id =%d\n", dma_id);
    return FAIL;
  }
  if (strcmp(argv[2], "disable") == 0) {
    out_dword_masked_ns(HIDMA_HI_DMA_CFG_ADDR(dma_id), 0x1, 0x0,
                        in_dword(HIDMA_HI_DMA_CFG_ADDR(dma_id)));
    g_DMA_status[dma_id] = DMA_STATE_DISABLED;
    return SUCCESS;
  }
  if (strcmp(argv[2], "enable") == 0) {
    out_dword_masked_ns(HIDMA_HI_DMA_CFG_ADDR(dma_id), 0x1, 0x1,
                        in_dword(HIDMA_HI_DMA_CFG_ADDR(dma_id)));
    for (i = 0; i < HI_DMA_CHANNEL_NUM; i++) {
      tmp_trch_conf[dma_id][i].upd_flg = 0; /*init TRC para update flag*/
    }
    return SUCCESS;
  }
  if (strcmp(argv[2], "rdpara") == 0) {
    read_dma_para(dma_id, &(dma_config_para[dma_id])); /*dynamic para*/
    display_dma_para(dma_config_para[dma_id]);
    return SUCCESS;
  }
  if ((strcmp(argv[2], "updpara") == 0) || (strcmp(argv[2], "cfgdflt") == 0)) {
    if ((in_dword_masked(HIDMA_HI_DMA_CFG_ADDR(dma_id), 0x1)) ==
        0x1) /*dma enable, can't configure para*/
    {
      printf("cant' execute updpara/cfgdflt cmd due to DMA%d is enabled\n",
             dma_id);
      return FAIL;
    }
  }
  if (strcmp(argv[2], "updpara") == 0) {
    if ((strcmp(argv[4], "memsetjob") != 0) &&
        (strcmp(argv[4], "reqprio") != 0) &&
        (strcmp(argv[4], "wrtiden") != 0) &&
        (strcmp(argv[4], "rdtiden") != 0) &&
        (strcmp(argv[4], "beatiden") != 0) &&
        (strcmp(argv[4], "rdxact") != 0) && (strcmp(argv[4], "wrxact") != 0) &&
        (strcmp(argv[4], "inttyp") != 0) && (strcmp(argv[4], "inten") != 0) &&
        (strcmp(argv[4], "wrlen") != 0) && (strcmp(argv[4], "rdlen") != 0) &&
        (strcmp(argv[4], "msiattr") != 0) &&
        (strcmp(argv[4], "cacheattr") != 0)) {
      printf("hidma_dma updpara name of para is incorrect\n");
      return FAIL;
    }
    if ((strcmp(argv[4], "wrlen") == 0) || ((strcmp(argv[4], "rdlen") == 0))) {
      if ((strtoull(argv[5], 0, 0) != 0x80) &&
          (strtoull(argv[5], 0, 0) != 0x100) &&
          (strtoull(argv[5], 0, 0) != 0x200) &&
          (strtoull(argv[5], 0, 0) != 0x400)) {
        printf("hidma_dma updpara wrlen/rdlen illegal value, only "
               "0x80/0x100/0x200/0x400 is valid value\n");
        return FAIL;
      }
    }
    if (strcmp(argv[4], "inttyp") == 0) {
      if ((strtoull(argv[5], 0, 0) != 0) && (strtoull(argv[5], 0, 0) != 0x1) &&
          (strtoull(argv[5], 0, 0) != 0x9)) {
        printf("hidma dma updpara inttyp illegal value, only 0x0/0x1/0x9 is "
               "valid value\n");
        return FAIL;
      }
    }
    if (backup_dma_para[dma_id].para_upd_flag == 0)
      get_dma_default_conf(
          &backup_dma_para[dma_id]); /*change para base on the default para*/
    if (strcmp(argv[4], "memsetjob") == 0)
      backup_dma_para[dma_id].memset_max_num_jobs = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "reqprio") == 0)
      backup_dma_para[dma_id].client_req_prio = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "wrtiden") == 0)
      backup_dma_para[dma_id].const_wr_tid_en = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "rdtiden") == 0)
      backup_dma_para[dma_id].const_rd_tid_en = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "beatiden") == 0)
      backup_dma_para[dma_id].qsb_beat_index_en = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "rdxact") == 0)
      backup_dma_para[dma_id].max_rd_xactions = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "wrxact") == 0)
      backup_dma_para[dma_id].max_wr_xactions = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "inttyp") == 0)
      backup_dma_para[dma_id].inttype = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "inten") == 0)
      backup_dma_para[dma_id].int_enable = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "wrlen") == 0)
      backup_dma_para[dma_id].max_bus_wr_req_len = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "rdlen") == 0)
      backup_dma_para[dma_id].max_bus_rd_req_len = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "msiattr") == 0)
      backup_dma_para[dma_id].MSI_CACHEATTR = strtoull(argv[5], 0, 0);
    if (strcmp(argv[4], "cacheattr") == 0)
      backup_dma_para[dma_id].cacheattr = strtoull(argv[5], 0, 0);
    backup_dma_para[dma_id].para_upd_flag = 1;
    return SUCCESS;
  }
  if (strcmp(argv[2], "updact") == 0) /*write updated para into DMA register*/
  {
    if (backup_dma_para[dma_id].para_upd_flag == 0)
      printf("hidma dma updact didn't take effect, because no para will be "
             "updated for DMA%d\n",
             dma_id);
    else {
      hidma_config_para(dma_id,
                        backup_dma_para[dma_id]); /*configure to DMA register,
                                                     but don't enable DMA*/
      backup_dma_para[dma_id].para_upd_flag = 0;
    }
    return SUCCESS;
  }
  if (strcmp(argv[2], "cfgdflt") == 0) /*configure DMA with default parameter*/
  {
    get_dma_default_conf(&tmp_dma_cfg); /*change para base on the default para*/
    hidma_config_para(
        dma_id,
        tmp_dma_cfg); /*configure to DMA register, but don't enable DMA*/
    backup_dma_para[dma_id].para_upd_flag = 0;
    return SUCCESS;
  }
  return SUCCESS;
}

int hidma_trc_cmd(int argc, char *argv[]) {
  UINT8 tr_ev_id;
  UINT8 dma_id;
  UINT32 ret_val;
  UINT32 para_grp_num;
  UINT8 i;
  UINT32 tre_num;
  UINT32 ring_size;

  dma_id = strtoull(argv[3], 0, 0);
  tr_ev_id = strtoull(argv[4], 0, 0);
  if ((strcmp(argv[2], "rst") != 0) && (strcmp(argv[2], "rdpara") != 0) &&
      (strcmp(argv[2], "updpara") != 0) && (strcmp(argv[2], "cfgdflt") != 0) &&
      (strcmp(argv[2], "updact") != 0) && (strcmp(argv[2], "rdcntxt") != 0) &&
      (strcmp(argv[2], "upddb") != 0) && (strcmp(argv[2], "cfgcntxt") != 0)) {
    printf("unknown cmd for hidma trc\n");
    return FAIL;
  }
  if ((dma_id >= HI_DMA_INSTANCE_NUM) || (tr_ev_id >= HI_DMA_CHANNEL_NUM)) {
    printf("hidma_trc input parameter dma_id=%d, ch_id =%d\n", dma_id,
           tr_ev_id);
    return FAIL;
  }
  if (strcmp(argv[2], "rst") == 0) {
    if (g_TRCH_status[dma_id][tr_ev_id] == CH_STATE_INITIALIZED)
      free((void *)TRC_unalign_baseaddr[dma_id][tr_ev_id]);
    ret_val = reset_TRCH_by_register(dma_id, tr_ev_id);
    if (ret_val == FAIL) {
      printf("DMA%d TRC%d reset failed\n", dma_id, tr_ev_id);
      return FAIL;
    } else
      g_TRCH_status[dma_id][tr_ev_id] == CH_STATE_RESET;
    return SUCCESS;
  }
  if (strcmp(argv[2], "rdpara") == 0) {
    get_TRC_para(dma_id, tr_ev_id, &(TRC_config[dma_id][tr_ev_id]));
    display_trc_para(TRC_config[dma_id][tr_ev_id]);
    return SUCCESS;
  }
  if ((strcmp(argv[2], "updpara") == 0) || (strcmp(argv[2], "cfgdflt") == 0)) {
    if (((in_dword_masked(HIDMA_TR_CHANNEL_CNTXT0_ADDR(dma_id, tr_ev_id),
                          0xff00)) >>
         8) != 0x0) /*dma ch must in disable status*/
    {
      printf(
          "cant' execute updpara/cfgdflt cmd due to DMA%d TRC%d is enabled\n",
          dma_id, tr_ev_id);
      return FAIL;
    }
    if (strcmp(argv[2], "updpara") == 0) {
      if ((strcmp(argv[5], "lmten") != 0) && (strcmp(argv[5], "lmt") != 0) &&
          (strcmp(argv[5], "chprio") != 0) &&
          (strcmp(argv[5], "weight") != 0) &&
          (strcmp(argv[5], "inttyp") != 0)) {
        printf("hidma trc updpara name of para is incorrect\n");
        return FAIL;
      }

      if (tmp_trch_conf[dma_id][tr_ev_id].upd_flg == 0)
        get_TRC_default_conf(&(tmp_trch_conf[dma_id][tr_ev_id]));
      if (strcmp(argv[5], "lmten") == 0) /*valid value:0, 1*/
      {
        if ((strtoull(argv[6], 0, 0) != 0) && (strtoull(argv[6], 0, 0) != 1)) {
          printf("value of lmten is illegal, it should be 0 or 1\n");
          return FAIL;
        }
        tmp_trch_conf[dma_id][tr_ev_id].treq_limit_en = strtoull(argv[5], 0, 0);
      }
      if (strcmp(argv[5], "lmt") == 0) /*valid value:1~32*/
      {
        if ((strtoull(argv[6], 0, 0) > 32) || (strtoull(argv[6], 0, 0) < 1)) {
          printf("value of lmt is illegal, it should be 1 ~32\n");
          return FAIL;
        }
        tmp_trch_conf[dma_id][tr_ev_id].treq_limit = strtoull(argv[6], 0, 0);
      }
      if (strcmp(argv[5], "chprio") == 0) /*valid value:0, 1*/
      {
        if ((strtoull(argv[6], 0, 0) != 0) && (strtoull(argv[6], 0, 0) != 1)) {
          printf("value of chprio is illegal, it should be 0 or 1\n");
          return FAIL;
        }
        tmp_trch_conf[dma_id][tr_ev_id].ch_prio = strtoull(argv[6], 0, 0);
      }
      if (strcmp(argv[5], "weight") == 0) /*valid value:1~15*/
      {
        if ((strtoull(argv[6], 0, 0) < 1) || (strtoull(argv[6], 0, 0) > 15)) {
          printf("value of wrr_weight is illegal, it should be 1~ 15\n");
          return FAIL;
        }
        tmp_trch_conf[dma_id][tr_ev_id].wrr_weight = strtoull(argv[6], 0, 0);
      }
      if (strcmp(argv[5], "inttyp") == 0) {
        if (strtoull(argv[6], 0, 0) > 3) {
          printf(
              "value of inttyp is illegal, bit0:ALLOW_MSI, bit1: ALLOW_IRQ\n");
          return FAIL;
        }
        tmp_trch_conf[dma_id][tr_ev_id].inttype = strtoull(argv[6], 0, 0);
      }
      tmp_trch_conf[dma_id][tr_ev_id].upd_flg =
          1; /*indicate that some para will be updated*/
    } else   /*cfgdflt, configure TRE with default para and enable TRC*/
    {
      get_TRC_default_conf(&(tmp_trch_conf[dma_id][tr_ev_id]));
      hidma_TRC_config_para(dma_id, tr_ev_id, tmp_trch_conf[dma_id][tr_ev_id]);
      tmp_trch_conf[dma_id][tr_ev_id].upd_flg = 0;
    }
    return SUCCESS;
  }
  if (strcmp(argv[2], "updact") == 0) /*it should used pair with updpara*/
  {
    if (tmp_trch_conf[dma_id][tr_ev_id].upd_flg == 0)
      printf("hidma_trc updact didn't take effect, because no para will be "
             "updated for DMA%d TRC%d\n",
             dma_id, tr_ev_id);
    else /*update with new para and enable TRC*/
    {
      hidma_TRC_config_para(dma_id, tr_ev_id, tmp_trch_conf[dma_id][tr_ev_id]);
      tmp_trch_conf[dma_id][tr_ev_id].upd_flg = 0;
    }
    return SUCCESS;
  }
  if (strcmp(argv[2], "cfgcntxt") == 0) {
    if (g_TRCH_status[dma_id][tr_ev_id] == CH_STATE_INITIALIZED) {
      printf("cant' execute cfgcntxt cmd due to DMA%d TRC%d is initialized\n",
             dma_id, tr_ev_id);
      return FAIL;
    }
    if (strtoull(argv[5], 0, 0) == 0) {
      printf("cant' execute cfgcntxt on DMA%d TRC%d dut to para incorrect, "
             "ring_size = 0\n",
             dma_id, tr_ev_id);
      return FAIL;
    }
    tre_num = strtoull(argv[5], 0, 0);
    TRC_unalign_baseaddr[dma_id][tr_ev_id] =
        (UINT64)malloc(sizeof(hidma_tre_t) * tre_num + sizeof(hidma_tre_t) - 1);
    if (TRC_unalign_baseaddr[dma_id][tr_ev_id] == (UINT64)NULL) {
      printf("Mem allocation Failed when alloc TRC space\n");
      return FAIL;
    }
    TRC_ring_baseaddr[dma_id][tr_ev_id] =
        ALIGN_UP(TRC_unalign_baseaddr[dma_id][tr_ev_id], sizeof(hidma_tre_t));
    TR_space_init(TRC_ring_baseaddr[dma_id][tr_ev_id],
                  tre_num); /*clear buffer*/
    trc_contxt_cfg(dma_id, tr_ev_id, tre_num,
                   TRC_ring_baseaddr[dma_id]
                                    [tr_ev_id]); /*config and enable TRC*/
    g_TRCH_status[dma_id][tr_ev_id] =
        CH_STATE_INITIALIZED; /*only here set TRC initialized*/
    return SUCCESS;
  }
  if (strcmp(argv[2], "rdcntxt") == 0) /*read TRC context*/
  {
    display_TRC_cntxt(dma_id, tr_ev_id);
    return SUCCESS;
  }
  if (strcmp(argv[2], "upddb") == 0) /*update doorbell to start DMA transfer*/
  {
    if (untrigger_tre_cnt[dma_id][tr_ev_id] != 0) {
      ring_size = (in_dword(HIDMA_TR_CHANNEL_CNTXT4_ADDR(dma_id, tr_ev_id))) /
                  sizeof(hidma_tre_t);
      out_dword(HIDMA_TR_CHANNEL_DOORBELL_ADDR(dma_id, tr_ev_id),
                ((in_dword(HIDMA_TR_CHANNEL_CNTXT6_ADDR(dma_id, tr_ev_id))) +
                 untrigger_tre_cnt[dma_id][tr_ev_id] * sizeof(hidma_tre_t)) %
                    (ring_size * sizeof(hidma_tre_t)));
      DO_DSB;
      recycle_evre(dma_id, untrigger_tre_cnt[dma_id][tr_ev_id]);
      untrigger_tre_cnt[dma_id][tr_ev_id] = 0;
    } else
      printf("no TRE is triggered by doorbell\n");
    return SUCCESS;
  }
  return SUCCESS;
}

int hidma_evc_cmd(int argc, char *argv[]) {
  UINT8 evch_id;
  UINT8 dma_id;
  UINT32 ret_val;
  UINT32 evre_num;
  UINT8 evc_force;
  UINT8 evc_inttyp;
  dma_id = strtoull(argv[3], 0, 0);
  evch_id = strtoull(argv[4], 0, 0);
  if ((strcmp(argv[2], "rst") != 0) && (strcmp(argv[2], "cfgcntxt") != 0) &&
      (strcmp(argv[2], "suspend") != 0) && (strcmp(argv[2], "rdcntxt") != 0) &&
      (strcmp(argv[2], "disp") != 0)) {
    printf("unknown para for hidma evc xxx\n");
    return FAIL;
  }
  if ((dma_id >= HI_DMA_INSTANCE_NUM) || (evch_id >= HI_DMA_CHANNEL_NUM)) {
    printf("hidma_evc input parameter dma_id=%d, ch_id =%d\n", dma_id, evch_id);
    return FAIL;
  }
  if (strcmp(argv[2], "rst") == 0) {
    if (g_EVCH_status[dma_id][evch_id] == CH_STATE_INITIALIZED)
      free((void *)EVC_unalign_baseaddr[dma_id][evch_id]);
    ret_val = reset_EVC(dma_id, evch_id);
    if (ret_val == FAIL) {
      printf("DMA%d EVC%d reset failed\n", dma_id, evch_id);
      return FAIL;
    } else
      g_EVCH_status[dma_id][evch_id] = CH_STATE_RESET;
    return SUCCESS;
  }
  if (strcmp(argv[2], "cfgcntxt") == 0) {
    if (g_EVCH_status[dma_id][evch_id] == CH_STATE_INITIALIZED) {
      printf("cant' execute cfgcntxt cmd due to DMA%d EVC%d is initialized\n",
             dma_id, evch_id);
      return FAIL;
    }
    evre_num = strtoull(argv[5], 0, 0);
    if (evre_num == 0) {
      printf("hidma_evc cfgcntxt, ring size can't be 0\n", dma_id, evch_id);
      return FAIL;
    }
    if ((argc != 8) && (argc != 6)) {
      printf("Number of input parameter is incorrect for DMA%d EVC%d-cfgcntxt "
             "it should be 6 or 4, \n",
             dma_id, evch_id, argc - 3);
      return FAIL;
    }
    if (argc == 8) {
      evc_force = strtoull(argv[6], 0, 0);
      evc_inttyp = strtoull(argv[7], 0, 0);
    } else /*if not para, use default para*/
    {
      evc_force = 1;
      evc_inttyp = 0x1;
    }
    EVC_unalign_baseaddr[dma_id][evch_id] = (UINT64)malloc(
        sizeof(hidma_evre_t) * evre_num + sizeof(hidma_evre_t) - 1);
    if (EVC_unalign_baseaddr[dma_id][evch_id] == (UINT64)NULL) {
      printf("Mem allocation Failed when set EVC space\n");
      return FAIL;
    }
    EVC_ring_baseaddr[dma_id][evch_id] =
        ALIGN_UP(EVC_unalign_baseaddr[dma_id][evch_id], sizeof(hidma_evre_t));
    EVR_space_init(EVC_ring_baseaddr[dma_id][evch_id],
                   evre_num); /*clear EVR buffer*/
    evc_contxt_cfg(dma_id, evch_id, evc_inttyp, evc_force, evre_num,
                   (void *)EVC_ring_baseaddr[dma_id][evch_id]);
    g_EVCH_status[dma_id][evch_id] = CH_STATE_INITIALIZED;
    return SUCCESS;
  }
  if (strcmp(argv[2], "suspend") == 0) {
    event_ch_cmd(dma_id, evch_id, CMD_SUSPEND);
    DO_DSB;
    return SUCCESS;
  }
  if (strcmp(argv[2], "rdcntxt") == 0) {
    display_EVC_cntxt(dma_id, evch_id);
    return SUCCESS;
  }
  if (strcmp(argv[2], "disp") == 0) {
    if (tre_num_each_EVC[dma_id][evch_id] == 0)
      printf("no pending TREs on DMA%d EVC%d\n", dma_id, evch_id);
    else
      disp_recd_tres(dma_id, evch_id);
    return SUCCESS;
  }
  return SUCCESS;
}

int hidma_tre_cmd(int argc, char *argv[]) {
  INT32 ret_val;
  UINT8 dma_id;
  UINT8 evch_id;
  UINT8 trch_id;
  tre_type_t tre_type;
  UINT32 tre_len;
  UINT32 ring_size;
  UINT32 tre_add;
  UINT32 i;
  dma_id = strtoull(argv[3], 0, 0);
  trch_id = strtoull(argv[4], 0, 0);
  evch_id = strtoull(argv[5], 0, 0);
  if ((strcmp(argv[2], "addwdb") != 0) && (strcmp(argv[2], "addwodb") != 0)) {
    printf("unknown para for hidma tre xxx\n");
    return FAIL;
  }
  if (argc < 8) {
    printf("hidma tre addwodb/addwdb, the number of parameter is illegal!\n");
    return FAIL;
  }
  if ((dma_id >= HI_DMA_INSTANCE_NUM) || (trch_id >= HI_DMA_CHANNEL_NUM) ||
      (evch_id >= HI_DMA_CHANNEL_NUM)) {
    printf(
        "hidma tre illegal input para, dma_id=%d, trch_id =%d, evch_id =%d\n",
        dma_id, trch_id, evch_id);
    return FAIL;
  }
  if (((in_dword(HIDMA_HI_DMA_CFG_ADDR(dma_id))) & 0x1) == 0x0) {
    printf("DMA%d is not enabled, can't add TREs\n", dma_id);
    return FAIL;
  }
  if ((((in_dword(HIDMA_TR_CHANNEL_CNTXT0_ADDR(dma_id, trch_id))) & 0xff00) >>
       8) != 0x1) {
    printf("DMA%d, TRC%d is not enabled, can't add TREs for it\n", dma_id,
           trch_id);
    return FAIL;
  }
  if ((((in_dword(HIDMA_EV_CHANNEL_CNTXT0_ADDR(dma_id, evch_id))) & 0xff00) >>
       8) != 0x1) {
    printf("DMA%d, EVC%d is not enabled, can't use this EVC for TREs\n", dma_id,
           evch_id);
    return FAIL;
  }
  ring_size = (in_dword(HIDMA_TR_CHANNEL_CNTXT4_ADDR(dma_id, trch_id))) /
              sizeof(hidma_tre_t);
  if (ring_size == 0) /*number of tre be added*/
  {
    printf("hidma tre addwdb/addwodb for DMA%d TRC%d can't be executed, due to "
           "ring_size = 0\n",
           dma_id, trch_id);
    return FAIL;
  }
  if (strtoull(argv[6], 0, 0) == 0) /*number of tre be added*/
  {
    printf("hidma tre addwodb/addwdb for DMA%d TRC%d input parameter is "
           "illegal, tre_add = %d\n",
           dma_id, trch_id, strtoull(argv[6], 0, 0));
    return FAIL;
  }
  tre_add = strtoull(argv[6], 0, 0);
  tre_len = strtoull(argv[8], 0, 0);
  if ((strcmp(argv[7], "memcpy") == 0) || (strcmp(argv[7], "memset") == 0) ||
      (strcmp(argv[7], "imm") == 0)) {
    if (tre_len == 0) {
      printf("hidma_tre addwodb/addwdb for DMA% TRC%d input parameter is "
             "illegal, transfer_len = 0\n",
             dma_id, trch_id);
      return FAIL;
    }
  } else if (strcmp(argv[7], "barrier") == 0) {
    tre_len = 0;
  } else {
    printf("unknown tre type for hidma_tre addwodb/addwdb\n");
    return FAIL;
  }
  if (strcmp(argv[7], "barrier") == 0)
    tre_type = TYPE_BARRIER;
  else if (strcmp(argv[7], "memcpy") == 0)
    tre_type = TYPE_MEMCPY;
  else if (strcmp(argv[7], "memset") == 0)
    tre_type = TYPE_MEMSET;
  else if (strcmp(argv[7], "imm") == 0)
    tre_type = TYPE_IMM;

  if (strcmp(argv[2], "addwdb") == 0) /*add tre with doorbell update*/
    ret_val = hidma_add_tre_with_db(dma_id, trch_id, evch_id, tre_add, tre_type,
                                    tre_len, ring_size);
  if (strcmp(argv[2], "addwodb") == 0) /*add TRE but without doorbell trigger */
    ret_val = hidma_add_tre_without_db(dma_id, trch_id, evch_id, tre_add,
                                       tre_type, tre_len, ring_size);
  return ret_val;
}

int do_hidma(int argc, char *argv[]) {
  int ret_val = FAIL;
  if ((strcmp(argv[1], "reg") != 0) && (strcmp(argv[1], "dma") != 0) &&
      (strcmp(argv[1], "trc") != 0) && (strcmp(argv[1], "evc") != 0) &&
      (strcmp(argv[1], "tre") != 0)) {
    printf("illegal subcmd for hidma, reg/dma/trc/evc/tre is legal\n");
    return FAIL;
  }
  if (strcmp(argv[1], "reg") == 0)
    ret_val = hidma_reg_cmd(argc, argv);
  if (strcmp(argv[1], "dma") == 0)
    ret_val = hidma_dma_cmd(argc, argv);
  if (strcmp(argv[1], "trc") == 0)
    ret_val = hidma_trc_cmd(argc, argv);
  if (strcmp(argv[1], "evc") == 0)
    ret_val = hidma_evc_cmd(argc, argv);
  if (strcmp(argv[1], "tre") == 0)
    ret_val = hidma_tre_cmd(argc, argv);
  return ret_val;
}
#ifdef CONFIG_CONSOLE_COMMAND
MK_CMD(hidma, do_hidma, "hidma REG/DMA/TRC/EVC/TRE cmd",
       " all hidma related commands including reg/dma/trc/tre/evc cmd \n"
       "    - hidma reg rd [addr] \n"
       "    - hidma reg wr [addr] [val] \n"
       "    - hidma reg rr [reg_cnt] [addr] [addr]... \n"
       "    - hidma reg rr all [dma_id]\n"
       "      dma_id:0~3 \n"
       "    - hidma reg rrcpor [reg_cnt] [addr] [addr]... \n"
       "    - hidma reg rrcpor all [dma_id] \n"
       "    - hidma dma disable [dma_id] \n"
       "    - hidma dma enable  [dma_id] \n"
       "    - hidma dma rdpara [dma_id]\n"
       "    - hidma dma updpara [dma_id] [para_name] [val] \n"
       "      para_name: "
       "memsetjob,reqprio,wrtiden,rdtiden,beatiden,rdxact,wrxact,inttyp,inten,"
       "wrlen,rdlen,msiattr,cacheattr \n"
       "    - hidma dma updact [dma_id] \n"
       "    - hidma dma cfgdflt [dma_id] \n"
       "    - hidma trc rst [dma_id] [ch_id] \n"
       "          dma_id:0~3 \n"
       "          ch_id:0~5 \n"
       "    - hidma trc updpara [dma_id] [ch_id] [para_name] [val] \n"
       "          para_name:lmten,lmt,chprio,weight,inttyp \n"
       "    - himda trc rdpara [dma_id] [ch_id] \n"
       "    - hidma trc cfgdflt [dma_id] [ch_id] \n"
       "    - hidma trc cfgcntxt [dma_id] [ch_id] [ring_size] \n"
       "    - hidma trc rdcntxt [dma_id] [ch_id] \n"
       "    - hidma trc upddb [dma_id] [ch_id] \n"
       "    - hidma trc updact [dma_id] [ch_id] \n"
       "    - hidma evc rst [dma_id] [evch_id] \n"
       "          evch_id: 0~5 \n"
       "    - hidma evc suspend [dma id] [evch_id] \n"
       "    - hidma evc cfgcntxt [dma_id] [ch_id] \n"
       "[evre_num][ring_size][forceev(optional)] [inttype(optional)] \n"
       "          forceev: 0,1 \n"
       "          inttype: 0, 1 \n"
       "    - hidma evc rdcntxt [dma_id] [ch_id] \n"
       "    - hidma evc disp [dma_id] [ch_id] \n"
       "    - hidma tre addwdb [dma_id] [trch_id] [evch_id] [num_tre_add] "
       "[tre_type] [len] \n"
       "    - hidma tre addwodb [dma_id] [trch_id] [evch_id] [num_tre_add] "
       "[memset|memcpy|barrier|imm][len] \n");
#endif
