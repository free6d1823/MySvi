
//-----------------------------------------------------------------------------
// Qualcomm Technologies, Inc. Proprietary
// Copyright (c) 2012-2016, Qualcomm Technologies, Inc. All rights reserved.
//
// All data and information contained in or disclosed by this document are
// confidential and proprietary information of Qualcomm Technologies, Inc. or
// its Affiliates, or their licensors, and all rights therein are expressly
// reserved. By accepting this material, the recipient agrees that this
// material and the information contained therein are held in confidence and
// in trust and will not be used, copied, reproduced in whole or in part, nor
// its contents revealed in any manner to others, without the express written
// permission of Qualcomm Technologies, Inc., or to the extent expressly
// permitted by the Technology License Agreement between Qualcomm Technologies,

//
// This technology was exported from the United States in accordance with the
// approval from the U.S. Department of Commerce, Bureau of Industry and
// Security, Export Administration Regulations (EAR).  Any re-export or
// in-country transfers of this technology is subject to U.S. Laws and
// regulations. Diversion contrary to U.S. law prohibited.
//-----------------------------------------------------------------------------


#include "VVDRV_qsmmuv3_common_dvm.h"
//#include <HALhwio.h>
#include "asm/hal/HALhwio.h"
//#include <QIOMMUHwio.h>
//#include "qsmmuv3_hwiobase.h"
#include "qsmmuv3_hwioreg.h"
#include "msmhwioreg.h"
#include "hdts_shell.h"
#include "hdts_common.h"

#define VV_MSG_FILE_NUMBER DRV_QSMMUV3_FILE_NUM_8
//#include "shell_msg_smmu.h"

void VVDRV_qsmmuv3_full_system_barrier(void) {
#ifndef CDVI_SVTB 
 __asm( "DSB SY \n\t" ); 
 __asm( "ISB SY \n\t" ); 
#endif 
}

void VVDRV_initIMEM(volatile uint64_t *imem_p, int32_t count) {
   for( ; count >=0; count--)
      *imem_p++ = 0;
}
//SOW2 MERGE: sow1 have, sow2 remove
void VVDRV_qsmmuv3_enableClocks(uint64_t reg_base) {

  return;
}

void VVDRV_qsmmuv3_enableAllClocks() {

  return;
}
//SOW2_MERGE end 
int VVDRV_qsmmuv3_compare_data(uint32_t data_actual, uint32_t data_expect) {
  int error = 0;

  if(data_actual != data_expect) {
    shell_msg( "Error  Expected = %x; Actual = %x\n", data_expect, data_actual);
    error++;
  } else {
    shell_msg( "Match  Expected = %x; Actual = %x\n", data_expect, data_actual);
  }

  return error;
}

 void VVDRV_qsmmuv3_TableQueueAttributes(uint64_t reg_base, SH_ATTR table_sh, CH_ATTR table_oc, CH_ATTR table_ic, SH_ATTR queue_sh, CH_ATTR queue_oc, CH_ATTR queue_ic, uint32_t secure) 
 {
  uint32_t wdata;
  uint32_t rdata;

  rdata = HWIO_INX(reg_base, IDR0);
  shell_msg( "VVDRV_qsmmuv3_TableQueueAttributes IDR0 = 0x%8x\n", rdata);
  if (!(rdata & 0x00000010)) {
    shell_msg( "SMMU does not support coherent access to translation structures - IDR0.COHACC\n");
  }

  wdata = ( table_sh << 10 ) + ( table_oc << 8) + ( table_ic << 6 ) + ( queue_sh << 4 ) + ( queue_oc << 2 ) + ( queue_ic );
  shell_msg( "VVDRV_qsmmuv3_TableQueueAttributes write CR1 = 0x%8x\n", wdata);
  if (secure) {
    HWIO_OUTX(reg_base, S_CR1, wdata);
  } else {
    HWIO_OUTX(reg_base, CR1, wdata);
  }

  return;
} 

void VVDRV_qsmmuv3_configureStreamTable(uint64_t reg_base, uint64_t strtab_base, uint32_t log2_numste, uint32_t secure) {
  uint32_t addr_l;
  uint32_t addr_h;
  //uint32_t rdata;

  addr_l = (reg_base & 0xffffffff);
  addr_h = ((reg_base >> 32) & 0xffffffff);
  shell_msg( "QSMMU REG BASE = 0x%0x_%8x\n", addr_h, addr_l);

  addr_l = (strtab_base & 0xffffffff);
  addr_h = ((strtab_base >> 32) & 0xffffffff);
  shell_msg( "strtab_base = 0x%0x_%8x\n", addr_h, addr_l);

  if (secure) {
    shell_msg( "doing hwio writes, secure = %x\n", secure);
    HWIO_OUTX(reg_base, S_STRTAB_BASE_L, addr_l);
    HWIO_OUTX(reg_base, S_STRTAB_BASE_H, addr_h);
    HWIO_OUTX(reg_base, S_STRTAB_BASE_CFG, log2_numste);
  } else {
    shell_msg( "doing hwio writes, non-secure = %x", secure);	
    HWIO_OUTX(reg_base, STRTAB_BASE_L, addr_l);
    HWIO_OUTX(reg_base, STRTAB_BASE_H, addr_h);
    HWIO_OUTX(reg_base, STRTAB_BASE_CFG, log2_numste);
  }
  shell_msg( "done hwio writes, addr_l = 0x%x, addr_h = 0x%x, log2size = 0x%x\n", addr_l, addr_h, log2_numste);

  return;
}
//SOW2_MERGE sow1 have sow2 remove, add back for compile error
void VVDRV_qsmmuv3_configureVMTable(uint64_t reg_base, uint64_t vmtab_base, uint32_t log2_numvmte) {
  uint32_t vmtab_base_l;
  //uint32_t vmtab_base_h;

  vmtab_base_l = (vmtab_base & 0xffffffe0);
  //vmtab_base_h = (((uint64_t)vmtab_base >> 32) & 0xffffffff);

  vmtab_base_l += log2_numvmte;

  return;
}
//SOW2_MERGE

void VVDRV_qsmmuv3_configureCommandQueue(uint64_t reg_base, uint64_t cmdq_base, uint32_t log2_numcmd, uint32_t secure) {
  uint32_t cmdq_base_l;
  uint32_t cmdq_base_h;
  cmdq_base_l = (cmdq_base & 0xffffffe0);
  cmdq_base_h = (((uint64_t)cmdq_base >> 32) & 0xffffffff) | 0x40000000 ;

  cmdq_base_l += log2_numcmd;

  shell_msg( "VVDRV_qsmmuv3_configureCommandQueues secure = %0d, cmdq_base = 0x%0x_%8x\n", secure, cmdq_base_h, cmdq_base_l);
  if (secure) {
    HWIO_OUTX(reg_base, S_CMDQ_BASE_L, cmdq_base_l);
    HWIO_OUTX(reg_base, S_CMDQ_BASE_H, cmdq_base_h);
    HWIO_OUTX(reg_base, S_CMDQ_CONS, 0x00000000);
    HWIO_OUTX(reg_base, S_CMDQ_PROD, 0x00000000);
  } else {
    HWIO_OUTX(reg_base, CMDQ_BASE_L, cmdq_base_l);
    HWIO_OUTX(reg_base, CMDQ_BASE_H, cmdq_base_h);
    HWIO_OUTX(reg_base, CMDQ_CONS, 0x00000000);
    HWIO_OUTX(reg_base, CMDQ_PROD, 0x00000000);
  }

  return;
}

void VVDRV_qsmmuv3_configureEventQueue(uint64_t reg_base, uint64_t eventq_base, uint32_t log2_numcmd, uint32_t secure) {
  uint32_t eventq_base_l;
  uint32_t eventq_base_h;
  //uint32_t rdata_ack;
  eventq_base_l = (eventq_base & 0xffffffe0);
  eventq_base_h = (((uint64_t)eventq_base >> 32) & 0xffffffff);

  eventq_base_l += log2_numcmd;

  shell_msg( "VVDRV_qsmmuv3_configureEventQueue secure = %0d, eventq_base = 0x%0x_%8x, eventq_log2num = %0d\n", secure, eventq_base_h, eventq_base_l, log2_numcmd);
  if (secure) {
    HWIO_OUTX(reg_base, S_EVENTQ_BASE_L, eventq_base_l);
    HWIO_OUTX(reg_base, S_EVENTQ_BASE_H, eventq_base_h);
    HWIO_OUTX(reg_base, S_EVENTQ_CONS, 0x00000000);
    HWIO_OUTX(reg_base, S_EVENTQ_PROD, 0x00000000);
  } else {
    HWIO_OUTX(reg_base, EVENTQ_BASE_L, eventq_base_l);
    HWIO_OUTX(reg_base, EVENTQ_BASE_H, eventq_base_h);
    HWIO_OUTX(reg_base, EVENTQ_CONS, 0x00000000);
    HWIO_OUTX(reg_base, EVENTQ_PROD, 0x00000000);
  }
  //////////////////////////////////////////
  // following part is done in VVDRV_qsmmuv3_enable_eventq
  //if (secure) {
  //	HWIO_OUTXF(reg_base, S_IRQ_CTRL, EVENTQ_IRQEN, 1);
  //	do
  //	{
  //  		rdata_ack = HWIO_INXF(reg_base, S_IRQ_CTRLACK, EVENTQ_IRQEN);
  //	} while  (!rdata_ack);
  //	shell_msg( "S_EVENTQ_IRQEN update_complete : %d", rdata_ack);
  //} else {
  //	HWIO_OUTXF(reg_base, IRQ_CTRL, EVENTQ_IRQEN, 1);
  //	do
  //	{
  //  		rdata_ack = HWIO_INXF(reg_base, IRQ_CTRLACK, EVENTQ_IRQEN);
  //	} while  (!rdata_ack);
  //	shell_msg( "EVENTQ_IRQEN update_complete : %d", rdata_ack);
  //}	
  return;
}

uint64_t VVDRV_qsmmuv3_readEventQueueBase( uint64_t reg_base, uint32_t secure) {
  uint64_t eventq_base;
  uint32_t eventq_base_l;
  uint32_t eventq_base_h;
  if ( secure )  {
    eventq_base_h = HWIO_INX( reg_base, S_EVENTQ_BASE_H );
    eventq_base_l = HWIO_INX( reg_base, S_EVENTQ_BASE_L );
  } else {
    eventq_base_h = HWIO_INX( reg_base, EVENTQ_BASE_H );
    eventq_base_l = HWIO_INX( reg_base, EVENTQ_BASE_L );
  }
  eventq_base = eventq_base_h;
  eventq_base <<= 32;
  eventq_base += eventq_base_l;
  eventq_base >>= 4;
  eventq_base <<= 4;

  return eventq_base;
}

uint32_t VVDRV_qsmmuv3_readEventQueueProdPtr( uint64_t reg_base, uint32_t secure) {
  uint32_t eventq_ptr;
  if ( secure ) {
    eventq_ptr = HWIO_INX( reg_base, S_EVENTQ_PROD );
  } else {
    eventq_ptr = HWIO_INX( (reg_base + QSMMU_QSMMUV3_GLOBALREG_SPACE1_REG_BASE), EVENTQ_PROD );
  } 
  return eventq_ptr;
}

uint32_t VVDRV_qsmmuv3_readEventQueueConsPtr( uint64_t reg_base, uint32_t secure) {
  uint32_t eventq_ptr;
  if ( secure ) {
    eventq_ptr = HWIO_INX( reg_base, S_EVENTQ_CONS );
  } else {
    eventq_ptr = HWIO_INX( (reg_base + QSMMU_QSMMUV3_GLOBALREG_SPACE1_REG_BASE), EVENTQ_CONS );
  } 
  return eventq_ptr;
}

uint32_t VVDRV_qsmmuv3_isEventQueueEmpty( uint64_t reg_base, uint32_t secure ) {
  if ( VVDRV_qsmmuv3_readEventQueueProdPtr(reg_base, secure) == VVDRV_qsmmuv3_readEventQueueConsPtr(reg_base, secure) ) {
    return 1;
  } else {
    return 0;
  }
}

void VVDRV_qsmmuv3_consume_next_event( uint64_t reg_base, uint32_t secure, event_struct* out_event_ptr ) {
  uint32_t rc = 99;
  uint32_t eventq_base_l;
  uint32_t eventq_base_h;
  uint64_t eventq_base;
  uint32_t cons_value;
  uint32_t num_events;
  uint32_t num_events_log2;
  uint32_t eventq_wrap;
  uint32_t eventq_index;
  //uint64_t event_addr;

  if (secure) {
    eventq_base_l = HWIO_INX(reg_base, S_EVENTQ_BASE_L);
    eventq_base_h = HWIO_INX(reg_base, S_EVENTQ_BASE_H);
    cons_value = HWIO_INX(reg_base, S_EVENTQ_CONS);
  } else {
    eventq_base_l = HWIO_INX(reg_base, EVENTQ_BASE_L);
    eventq_base_h = HWIO_INX(reg_base, EVENTQ_BASE_H);
    cons_value = HWIO_INX(reg_base, EVENTQ_CONS);
  }
  eventq_base = ((uint64_t)(eventq_base_h & 0xffff) << 32) + (eventq_base_l & 0xffffffe0);
  num_events_log2 = eventq_base_l & 0x1f;
  num_events = 1 << num_events_log2;
  eventq_wrap = (cons_value & num_events) >> num_events_log2;
  eventq_index = cons_value & (num_events - 1);
  shell_msg( "Calling read_event: event_addr = %X", eventq_base);
  rc = VVDRV_qsmmuv3_read_event( eventq_base, eventq_index, out_event_ptr );

  if ( rc==0 ) {
    shell_msg( "Retrive event, clear");
    if ( eventq_index == (num_events-1) ) {
      eventq_index = 0;
      if ( eventq_wrap == 0 ) {
        eventq_index += num_events;
      }
    }
    else {
      eventq_index += 1;
    }

    if ( secure ) {
      HWIO_OUTX(reg_base, S_EVENTQ_CONS, eventq_index);
    } else {
      HWIO_OUTX(reg_base, EVENTQ_CONS, eventq_index);
    }

  }
  return;

}

uint32_t VVDRV_qsmmuv3_read_event ( uint64_t eventq_base, uint32_t index, event_struct* out_event_ptr ) {
  uint64_t read_addr, event_base_addr;
  uint64_t read_data=0;
  //uint32_t store_data;
  int event_word_offset;

  if ( eventq_base == 0 ) {
    shell_msg( "Invalid eventq_base, exit");
    return 1; 
  }
  event_base_addr = eventq_base + (index * EVENT_BYTES);
  for ( event_word_offset=0; event_word_offset<(EVENT_BYTES/4); event_word_offset++ ) {

    if ( (event_word_offset%2) == 0 ) {
      read_addr = event_base_addr + (event_word_offset*4);
      read_data = inp64(read_addr);
      if ( event_word_offset == 0 ) {
        out_event_ptr->type = (EVENT_TYPE) (read_data & 0x00ff);
      }
      out_event_ptr->data[event_word_offset] = (uint32_t) (read_data & 0x00000000FFFFFFFF) ;
    }
    else {
     out_event_ptr->data[event_word_offset] = (uint32_t) (read_data>>32);
    }
  }
  return 0;
}

void VVDRV_qsmmuv3_enable_TLB(uint64_t reg_base) {
  uint32_t rdata;

  rdata = HWIO_INX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR);
  rdata |= 0x181;
  HWIO_OUTX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR, rdata);

  return;
}

void VVDRV_qsmmuv3_disable_TLB_int_caching(uint64_t reg_base) {
  uint32_t rdata;

  rdata = HWIO_INX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR);
  rdata &= 0xFFFFFFF7;
  HWIO_OUTX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR, rdata);

  return;
}

void VVDRV_qsmmuv3_enable_TLB_int_caching(uint64_t reg_base) {
  uint32_t rdata;

  rdata = HWIO_INX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR);
  rdata |= 0x08;
  HWIO_OUTX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR, rdata);

  return;
}

void VVDRV_qsmmuv3_disable_TLB(uint64_t reg_base) {
  uint32_t rdata;

  rdata = HWIO_INX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR);
  rdata |= 0x180;
  rdata &= ~(0x00000001);
  HWIO_OUTX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR, rdata);

  return;
}

void VVDRV_qsmmuv3_enable_TLB_set_TLB_LEVEL_CACHE_EN (uint64_t reg_base) {
  uint32_t rdata;

  rdata = HWIO_INX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR);
  rdata |= 0x189;
  HWIO_OUTX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR, rdata);

  return;
}

void VVDRV_qsmmuv3_enable_TLB_clear_TLB_LEVEL_CACHE_EN (uint64_t reg_base) {
  uint32_t rdata;

  rdata = HWIO_INX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR);
  rdata |= 0x181;
  rdata &= ~(0x00000008);
  HWIO_OUTX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QTLBCR, rdata);

  return;
}

void VVDRV_qsmmuv3_enable_cfgcache(uint64_t reg_base) {
  uint32_t rdata;

  rdata = HWIO_INX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QCFG_CACHE_CR);
  rdata |= 0x1;
  HWIO_OUTX((reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE), QCFG_CACHE_CR, rdata);

  return;
}

void VVDRV_qsmmuv3_enable_cmdq(uint64_t reg_base, uint32_t secure) {
  volatile uint32_t rdata_ack = 0;
  if (secure) {
     HWIO_OUTXF(reg_base, S_CR0, CMDQEN, 1);
  } else {
     HWIO_OUTXF(reg_base, CR0, CMDQEN, 1);
  }
  if (secure) {
    do {
       rdata_ack = HWIO_INXF(reg_base, S_CR0ACK, CMDQEN);
    } while (!rdata_ack);
    shell_msg( "S_CMDQEN update_complete : %d\n", rdata_ack);
  } else {
    do {
      rdata_ack = HWIO_INXF(reg_base, CR0ACK, CMDQEN);
      shell_msg( "CMDQEN update_complete : %d\n", rdata_ack);

    } while (!rdata_ack);
    shell_msg( "CMDQEN update_complete : %d\n", rdata_ack);
  }
  return;
}

void VVDRV_qsmmuv3_enable_eventq(uint64_t reg_base, uint32_t secure) {
  volatile uint32_t rdata_ack = 0;
  if (secure) {
     HWIO_OUTXF(reg_base, S_CR0, EVENTQEN, 1);
  } else {
     HWIO_OUTXF(reg_base, CR0, EVENTQEN, 1);
  }
  if (secure) {
    do {
       rdata_ack = HWIO_INXF(reg_base, S_CR0ACK, EVENTQEN);
    } while (!rdata_ack);
    shell_msg( "S_EVENTQEN update_complete : %d\n", rdata_ack);

  } else {
    do {
      rdata_ack = HWIO_INXF(reg_base, CR0ACK, EVENTQEN);
      shell_msg( "EVENTQEN update_complete : %d\n", rdata_ack);

    } while (!rdata_ack);
    shell_msg( "EVENTQEN update_complete : %d\n", rdata_ack);
  }
  if (secure) {
  	HWIO_OUTXF(reg_base, S_IRQ_CTRL, EVENTQ_IRQEN, 1);
  	do
  	{
    		rdata_ack = HWIO_INXF(reg_base, S_IRQ_CTRLACK, EVENTQ_IRQEN);
  	} while  (!rdata_ack);
  	shell_msg( "S_EVENTQ_IRQEN update_complete : %d\n", rdata_ack);
  } else {
  	HWIO_OUTXF(reg_base, IRQ_CTRL, EVENTQ_IRQEN, 1);
  	do
  	{
    		rdata_ack = HWIO_INXF(reg_base, IRQ_CTRLACK, EVENTQ_IRQEN);
            shell_msg( "CEVENTQ_IRQEN update_complete : %d\n", rdata_ack);

  	} while  (!rdata_ack);
  	shell_msg( "EVENTQ_IRQEN update_complete : %d\n", rdata_ack);
  }	
  return;
}

void VVDRV_qsmmuv3_default_enables(uint64_t reg_base, uint32_t secure)  
{
  if (secure) {
	HWIO_OUTXF(reg_base, S_CR1, 		QUEUE_SH,	3);
	HWIO_OUTXF(reg_base, S_CR1, 		QUEUE_OC,	1);
	HWIO_OUTXF(reg_base, S_CR1, 		QUEUE_IC,	1);
	HWIO_OUTXF(reg_base, S_CR2, 		PTM,		0);
	HWIO_OUTXF(reg_base, S_QTABLE_ACR1, 	REQPRIORITY,	3);
  } else {
	HWIO_OUTXF(reg_base, CR1,		QUEUE_SH,	3);
	HWIO_OUTXF(reg_base, CR1,		QUEUE_OC,	1);
	HWIO_OUTXF(reg_base, CR1,		QUEUE_IC,	1);
	HWIO_OUTXF(reg_base, CR2,		PTM,		0);
	HWIO_OUTXF(reg_base, QTABLE_ACR1, 	REQPRIORITY,	3);
  }

  VVDRV_qsmmuv3_enable_RESP_TID_REPL_DIS(reg_base);
  HWIO_OUTXF (reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE, QGLOBAL_CR0, SYNC_MODE, 2);
}

void VVDRV_qsmmuv3_set_httu_override( uint64_t reg_base)  
{
  HWIO_OUTXF(reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE, QGLOBAL_CR0, HTTU_OVERRIDE, 2);
}

void VVDRV_qsmmuv3_clear_httu_override( uint64_t reg_base)  
{
  HWIO_OUTXF(reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE, QGLOBAL_CR0, HTTU_OVERRIDE, 0);
}

void VVDRV_qsmmuv3_enable_dispatcher(uint64_t reg_base)
{
    HWIO_OUTXF(reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE, QGLOBAL_CR1, DISPATCHER_EN, 1);
}

void VVDRV_qsmmuv3_disable_dispatcher(uint64_t reg_base)
{
    HWIO_OUTXF(reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE, QGLOBAL_CR1, DISPATCHER_EN, 0);
}

void VVDRV_qsmmuv3_enable_RESP_TID_REPL_DIS(uint64_t reg_base)
{
    HWIO_OUTXF(reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE, QGLOBAL_CR1, RESP_TID_REPL_DIS, 1);
    HWIO_OUTXF(reg_base + QSMMU_QSMMUV3_IMPDEF_REG_BASE, QGLOBAL_CR3, RESP_SRT_TID_DIS_FEAT_EN, 0);
}

void VVDRV_qsmmuv3_enable(uint64_t reg_base, uint32_t secure) {
  volatile uint32_t rdata_ack = 0;

  if (secure) {
     HWIO_OUTXF(reg_base, S_CR0, SMMUEN, 1);
  } else {
     HWIO_OUTXF(reg_base, CR0, SMMUEN, 1);
  }
  if (secure) {
    do {
       rdata_ack = HWIO_INXF(reg_base, S_CR0ACK, SMMUEN);
    } while (!rdata_ack);
    shell_msg( "S_SMMUEN update_complete : %d\n", rdata_ack);

  } else {
    do {
      rdata_ack = HWIO_INXF(reg_base, CR0ACK, SMMUEN);
    } while (!rdata_ack);
    shell_msg( "SMMUEN update_complete : %d\n", rdata_ack);
  }

  return;
}

void VVDRV_qsmmuv3_disable(uint64_t reg_base, uint32_t secure) {
  volatile uint32_t rdata_ack = 0;
  if (secure) {
     HWIO_OUTXF(reg_base, S_CR0, SMMUEN, 0);
  } else {
     HWIO_OUTXF(reg_base, CR0, SMMUEN, 0);
  }
  if (secure) {
    do {
       rdata_ack = HWIO_INXF(reg_base, S_CR0ACK, SMMUEN);
    } while (rdata_ack);
    shell_msg( "S_SMMUEN update_complete : %d", rdata_ack);

  } else {
    do {
      rdata_ack = HWIO_INXF(reg_base, CR0ACK, SMMUEN);
    } while (rdata_ack);
    shell_msg( "SMMUEN update_complete : %d", rdata_ack);
  }

  return;
}

void VVDRV_qsmmuv3_enable_atschk(uint64_t reg_base) {

    uint32_t rdata_ack;

  	HWIO_OUTXF(reg_base, CR0, ATSCHK, 1);
    	do {
      		rdata_ack = HWIO_INXF(reg_base, CR0ACK, ATSCHK);
	} while (!rdata_ack);
}

void VVDRV_qsmmuv3_disable_atschk(uint64_t reg_base) {

    uint32_t rdata_ack;

  	HWIO_OUTXF(reg_base, CR0, ATSCHK, 0);
    	do {
      		rdata_ack = HWIO_INXF(reg_base, CR0ACK, ATSCHK);
	} while (rdata_ack != 0);
}

//SOW2_MERGE sow1 have
void VVDRV_qsmmuv3_enable_imc_msa_bypass_check() {
  volatile uint32_t rdata;

  rdata = HWIO_IN(QSMMU_MSA_TRANS_CHECK);
  rdata |= (HWIO_QSMMU_MSA_TRANS_CHECK_IMC_CHECK_BMSK);
  HWIO_OUT(QSMMU_MSA_TRANS_CHECK, rdata);

  return;
}

void VVDRV_qsmmuv3_disable_imc_msa_bypass_check() {
  volatile uint32_t rdata;

  rdata = HWIO_IN(QSMMU_MSA_TRANS_CHECK);
  rdata &= ~(HWIO_QSMMU_MSA_TRANS_CHECK_IMC_CHECK_BMSK);
  HWIO_OUT(QSMMU_MSA_TRANS_CHECK, rdata);

  return;
}

void VVDRV_qsmmuv3_enable_pss_msa_bypass_check() {
  volatile uint32_t rdata;

  rdata = HWIO_IN(QSMMU_MSA_TRANS_CHECK);
  rdata |= (HWIO_QSMMU_MSA_TRANS_CHECK_PERPH_CHECK_BMSK);
  HWIO_OUT(QSMMU_MSA_TRANS_CHECK, rdata);

  return;
}

void VVDRV_qsmmuv3_disable_pss_msa_bypass_check() {
  volatile uint32_t rdata;

  rdata = HWIO_IN(QSMMU_MSA_TRANS_CHECK);
  rdata &= ~(HWIO_QSMMU_MSA_TRANS_CHECK_PERPH_CHECK_BMSK);
  HWIO_OUT(QSMMU_MSA_TRANS_CHECK, rdata);

  return;
}
//SOW2_MERGE end

void VVDRV_qsmmuv3_enable_A53_protns_passthrough() {
#ifndef CDVI_SVTB
  HWIO_OUTF(IMC_PROTNS_CTRL,PROTNS_EXTERNAL_ENA,1);
  HWIO_OUTF(IMC_MSA_CTRL,MSA_INTERNAL_ENA,0);
  HWIO_OUTF(IMC_MSA_CTRL,MSA_EXTERNAL_ENA,0);
#endif
  return;
}

void VVDRV_qsmmuv3_intr_undef_addr(uint64_t reg_base, uint32_t secure) {

  if (secure) {
    HWIO_OUTXF(reg_base,S_QCR0,AHB_ERROR_REPORT_EN,0);
  } else {
    HWIO_OUTXF(reg_base,QCR0,AHB_ERROR_REPORT_EN,0);
  }
  OUTP32((reg_base + 0x60000), 0x0badc0de);

  return;
}
void VVDRV_qsmmuv3_submit_CMD(uint64_t reg_base, uint32_t secure, uint32_t cmd_word[4]) {

  uint32_t cmdq_base_l;
  uint32_t cmdq_base_h;
  uint64_t cmdq_base;
  uint32_t prod_value;
  uint32_t log2_numcmd;
  uint32_t wr_wrap;
  uint32_t wr_wrap_mask;
  uint32_t wr_index;
  uint32_t wr_index_mask;
  uint32_t cmd_idx;
  uint32_t max_index;
  uint64_t cmd_addr;

  if (secure) {
    cmdq_base_l = HWIO_INX(reg_base, S_CMDQ_BASE_L);
    cmdq_base_h = HWIO_INX(reg_base, S_CMDQ_BASE_H);
    prod_value = HWIO_INX(reg_base, S_CMDQ_PROD);
  } else {
    cmdq_base_l = HWIO_INX(reg_base, CMDQ_BASE_L);
    cmdq_base_h = HWIO_INX(reg_base, CMDQ_BASE_H);
    prod_value = HWIO_INX(reg_base, CMDQ_PROD);
  }
  cmdq_base = ((uint64_t)(cmdq_base_h & 0xffff) << 32) + (cmdq_base_l & 0xffffffe0);
  log2_numcmd = (cmdq_base_l & 0x1f);
  wr_wrap_mask  = 0x1 << log2_numcmd;
  wr_index_mask = wr_wrap_mask - 1;
  wr_wrap = ((prod_value & wr_wrap_mask) >> log2_numcmd);
  wr_index = (prod_value & wr_index_mask);
  cmd_addr = (cmdq_base + (wr_index << 4));

  VVDRV_qsmmuv3_full_system_barrier();
  for (cmd_idx = 0 ; cmd_idx < 4; cmd_idx++) {
        OUTP32((cmd_addr + (0x04 * cmd_idx)), cmd_word[cmd_idx]);
  }

  VVDRV_qsmmuv3_full_system_barrier();
  wr_index++;
  max_index = (0x1 << log2_numcmd) - 1;

  if (wr_index > max_index) {
    wr_index = wr_index - (max_index + 1);
    wr_wrap ^= 0x1;
  }

  prod_value = (wr_wrap << log2_numcmd) + wr_index;

  VVDRV_qsmmuv3_full_system_barrier();

  if (secure) {
    HWIO_OUTX(reg_base, S_CMDQ_PROD, prod_value);
  } else {
    HWIO_OUTX(reg_base, CMDQ_PROD, prod_value);
  }

}
void VVDRV_qsmmuv3_CMD_RESUME(uint64_t reg_base, uint32_t action, uint32_t abort, uint32_t stream_id, uint32_t stag, uint32_t secure) {

  uint32_t cmd_word[4];

  cmd_word[0]= (abort << 13) + (action << 12) + (secure << 10) + CMD_RESUME;
  cmd_word[1] = stream_id;
  cmd_word[2] = stag;
  cmd_word[3] = 0;

  VVDRV_qsmmuv3_submit_CMD(reg_base, secure, cmd_word); 

  return;

}

void VVDRV_qsmmuv3_CMD_SYNC(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t secure) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);
  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;

  VVDRV_qsmmuv3_submit_CMD(reg_base, secure, cmd_word); 

  return;
}

void VVDRV_qsmmuv3_CMD_TLBI_NH_ALL(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t vmid) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  cmd_word[0] = CMD_TLBI_NH_ALL;
  cmd_word[1] = vmid & 0xffff;
  cmd_word[2] = 0x0;
  cmd_word[3] = 0x0;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);

  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);

  return;
}

void VVDRV_qsmmuv3_CMD_TLBI_NH_ASID(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t vmid, uint32_t asid) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  cmd_word[0] = CMD_TLBI_NH_ASID;
  cmd_word[1] = (vmid & 0xffff) + (asid << 16);
  cmd_word[2] = 0x0;
  cmd_word[3] = 0x0;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);

  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);

  return;
}

void VVDRV_qsmmuv3_CMD_TLBI_NH_VAA(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t vmid, uint64_t addr, uint32_t leaf) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  cmd_word[0] = CMD_TLBI_NH_VAA;
  cmd_word[1] = vmid & 0xffff;
  cmd_word[2] = (addr & 0xfffff000) + (leaf & 0x1);
  cmd_word[3] = addr >> 32;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);

  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);

  return;
}

void VVDRV_qsmmuv3_CMD_TLBI_NH_VA(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t vmid, uint32_t asid, uint64_t addr, uint32_t leaf) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  cmd_word[0] = CMD_TLBI_NH_VA;
  cmd_word[1] = (vmid & 0xffff) + (asid << 16);
  cmd_word[2] = (addr & 0xfffff000) + (leaf & 0x1);
  cmd_word[3] = addr >> 32;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);

  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);

  return;
}

void VVDRV_qsmmuv3_CMD_TLBI_EL3_ALL(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  cmd_word[0] = CMD_TLBI_EL3_ALL;
  cmd_word[1] = 0x0;
  cmd_word[2] = 0x0;
  cmd_word[3] = 0x0;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);

  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);

  return;
}

void VVDRV_qsmmuv3_CMD_TLBI_EL3_VA(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint64_t va) {
  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;

  cmd_word[0] = CMD_TLBI_EL3_VA;
  cmd_word[1] = 0x0;
  cmd_word[2] = (uint32_t) ( (va & 0xfffff000) + 1 );
  cmd_word[3] = (uint32_t) (  va >> 32);
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);
  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);

  return;
}

void VVDRV_qsmmuv3_CMD_CFGI_STE(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t ssec, uint32_t sid) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;

  cmd_word[0] = ((ssec<<10) | CMD_CFGI_STE);
  cmd_word[1] = sid;
  cmd_word[2] = 1;
  cmd_word[3] = 0;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);
  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  return;
}

void VVDRV_qsmmuv3_CMD_CFGI_CD(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t ssec, uint32_t sid) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;

  cmd_word[0] = ((ssec<<10) | CMD_CFGI_CD_ALL);
  cmd_word[1] = sid;
  cmd_word[2] = 0;
  cmd_word[3] = 0;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);
  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  return;
}

void VVDRV_qsmmuv3_CMD_PREFETCH_CONFIG(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t sid, uint32_t ssec, int ssid) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  cmd_word[0] = ((ssec<<10) | CMD_PREFETCH_CONFIG);
  if (ssid >= 0) 
    cmd_word[0] |= ((ssid<<12) | (1<<11));
  cmd_word[1] = sid;
  cmd_word[2] = 0;
  cmd_word[3] = 0;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);
  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);

  return;
}

void VVDRV_qsmmuv3_CMD_PREFETCH_ADDR(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t sid, uint32_t ssec, int ssid, uint64_t va, uint32_t size) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  cmd_word[0] = ((ssec<<10) | CMD_PREFETCH_ADDR);
  if (ssid >= 0) 
    cmd_word[0] |= ((ssid<<12) | (1<<11));
  cmd_word[1] = sid;
  cmd_word[2] = (va & 0xFFFFF000) + size ;
  cmd_word[3] = (va >> 32) ;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);
  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, 1, cmd_word);  

  return;
}
void VVDRV_qsmmuv3_DVM_CMDQ(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t secure) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  if (secure) {

    cmd_word[0] = CMD_TLBI_EL3_ALL;
    cmd_word[1] = 0x0;
    cmd_word[2] = 0x0;
    cmd_word[3] = 0x0;
  } else {

    cmd_word[0] = CMD_TLBI_EL2_ALL;
    cmd_word[1] = 0x0;
    cmd_word[2] = 0x0;
    cmd_word[3] = 0x0;
  }
  VVDRV_qsmmuv3_submit_CMD(reg_base, secure, cmd_word); 
  if (secure) {
    cmd_word[0] = CMD_TLBI_NH_ALL;
    cmd_word[1] = 0x0;
    cmd_word[2] = 0x0;
    cmd_word[3] = 0x0;
  } else {

    cmd_word[0] = CMD_TLBI_NSNH_ALL;
    cmd_word[1] = 0x0;
    cmd_word[2] = 0x0;
    cmd_word[3] = 0x0;
  }
  VVDRV_qsmmuv3_submit_CMD(reg_base, secure, cmd_word);
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);
  cmd_word[0] = (msi_attr << 24) + (cs << 12) + CMD_SYNC;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, secure, cmd_word);

  return;
}

void VVDRV_qsmmuv3_CMD_ATC_INV(uint64_t reg_base, uint32_t global, uint32_t ssv, uint32_t substreamid, uint32_t streamid, uint32_t size, uint64_t address, uint32_t secure) {

  uint32_t cmd_word[4];
  cmd_word[0] = CMD_ATC_INV + (global << 9) + (ssv << 11) + (substreamid << 12);  
  cmd_word[1] = streamid;
  cmd_word[2] = size + (address & 0xFFFFF000);
  cmd_word[3] = (address >> 32) ;
  VVDRV_qsmmuv3_submit_CMD(reg_base, secure, cmd_word);

  return;
}

uint32_t VVDRV_qsmmuv3_readCommandQueueProdPtr( uint64_t reg_base, uint32_t secure) {
  uint32_t cmdq_ptr;
  if ( secure ) {
    cmdq_ptr = HWIO_INX( reg_base, S_CMDQ_PROD );
  } else {
    cmdq_ptr = HWIO_INX(reg_base, CMDQ_PROD);
  } 
  return cmdq_ptr;
}

uint32_t VVDRV_qsmmuv3_readCommandQueueConsPtr( uint64_t reg_base, uint32_t secure) {
  uint32_t cmdq_ptr;
  if ( secure ) {
    cmdq_ptr = HWIO_INX( reg_base, S_CMDQ_CONS );
  } else {
    cmdq_ptr = HWIO_INX(reg_base, CMDQ_CONS );
  } 
  return cmdq_ptr;
}

uint32_t VVDRV_qsmmuv3_isCommandQueueEmpty( uint64_t reg_base, uint32_t secure ) {
  if ( VVDRV_qsmmuv3_readCommandQueueProdPtr(reg_base, secure) == VVDRV_qsmmuv3_readCommandQueueConsPtr(reg_base, secure) ) {
    return 1;
  } else {
    return 0;
  }
}

void VVDRV_qsmmuv3_CMD_ILL(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t secure) {

  uint32_t cmd_word[4];
  uint32_t msi_addr_l;
  uint32_t msi_addr_h;
  msi_addr_l = (msi_addr & 0xfffffffc);
  msi_addr_h = (((uint64_t)msi_addr >> 32) & 0x0000ffff);
  cmd_word[0] = (msi_attr << 24) + (cs << 12) + 0x0ff;
  cmd_word[1] = msi_data;
  cmd_word[2] = msi_addr_l;
  cmd_word[3] = msi_addr_h;
  VVDRV_qsmmuv3_submit_CMD(reg_base, secure, cmd_word);

  return;
}

void VVDRV_qsmmuv3_base_addr(uint64_t *secure, uint64_t *nonsecure) {
  #if defined (PCIE0) 
  *secure	= QSMMU_S_OFFSET_PCIE_0	 + QSMMU_PCIE_OFFSET0;
  *nonsecure	= QSMMU_NS_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET0;

  #elif defined (PCIE1) 
  *secure	= QSMMU_S_OFFSET_PCIE_0	 + QSMMU_PCIE_OFFSET1;
  *nonsecure	= QSMMU_NS_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET1;

  #elif defined (PCIE2) 
  *secure	= QSMMU_S_OFFSET_PCIE_0	 + QSMMU_PCIE_OFFSET2;
  *nonsecure	= QSMMU_NS_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET2;

  #elif defined (PCIE3) 
  *secure	= QSMMU_S_OFFSET_PCIE_1	 + QSMMU_PCIE_OFFSET0;
  *nonsecure	= QSMMU_NS_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET0;

  #elif defined (PCIE4) 
  *secure	= QSMMU_S_OFFSET_PCIE_1	 + QSMMU_PCIE_OFFSET1;
  *nonsecure	= QSMMU_NS_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET1;

  #elif defined (PCIE5) 
  *secure	= QSMMU_S_OFFSET_PCIE_1	 + QSMMU_PCIE_OFFSET2;
  *nonsecure	= QSMMU_NS_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET2;

  #elif defined (CRYPTO0) || defined (CRYPTO1) || defined (EMAC0) || defined (EMAC1) || defined (HDMA0) || defined (HDMA1) || defined (HDMA2) || defined (HDMA3) || defined (IMCSS) || defined (PCIE0) || defined (PCIE1) || defined (PCIE2) || defined (PCIE3) || defined (PCIE4) || defined (PCIE5) || defined (PSS) || defined (SATA0) || defined (SATA1) || defined (SATA2) || defined (SATA3) || defined (SATA4) || defined (SATA5) || defined (SATA6) || defined (SATA7)
  *secure	= QSMMU_BASE;
  *nonsecure	= QSMMU_BASE - AW_NS_SUBTRACT_OFFSET;

  #endif
  return;
}
void VVDRV_qsmmuv3_setup_pcie_xlation(uint64_t desc_base, uint64_t cd_base, uint64_t s_strtab_base) {
  #if defined (PCIE0) || defined (PCIE1) || defined (PCIE2) || defined (PCIE3) || defined (PCIE4) || defined (PCIE5)
  VVDRV_qsmmuv3_configImcTranslate_PcieEven(desc_base, cd_base, s_strtab_base);
  #endif
  return;
}

#ifndef CDVI_SVTB
#ifdef ARM_VERSION_6

void VVDRV_DVM_TLB_I(void) {
  #ifdef HYDRA_64
   __asm(
   "TLBI ALLE3IS \n\t"
   "DSB  ISH \n\t"
   "ISB \n\t "
   "RET \n\t"
   );
  #endif
}

void VVDRV_DVM_TLB_I_VA(uint64_t myaddr) {
  #ifdef HYDRA_64

  __asm(
  "TLBI VAE3IS, %0 \n\t"
  "DSB ISH \n\t"
  "ISB \n\t "
  "RET \n\t"
  :
  : "r" (myaddr)
  );
  #endif
}

void VVDRV_DVM_TLB_I_ASIDE1IS(uint64_t myasid) {
  #ifdef HYDRA_64

  myasid <<= 48;
  __asm(
  "MRS      x1, SCR_EL3  \n\t"
  "ORR      x1, x1, #(0x1)  \n\t"
  "MSR      SCR_EL3, x1  \n\t"
  "TLBI ASIDE1IS, %0 \n\t"
  "DSB ISH \n\t"
  "ISB \n\t"
  "RET \n\t"
  :
  : "r" (myasid)
  );
  #endif
}

void VVDRV_DVM_TLB_I_Multi(uint64_t myaddr) {
  #ifdef HYDRA_64

  __asm(
  "TLBI VAE3IS, %0 \n\t"
  "TLBI ALLE3IS \n\t"
  "DSB ISH \n\t"
  "ISB \n\t "
  "RET \n\t"
  :
  : "r" (myaddr)
  );
  #endif
}

#else

/* __asm void VVDRV_DVM_TLB_I(void) {
  #ifdef HYDRA_64
   TLBI ALLE3IS
   DSB  ISH
   ISB
   RET

  #endif
}
*/
#endif

#endif
