//------------------------------------------------------------------------------
//
// Copyright 2019 Synopsys, INC.
//
// This Synopsys IP and all associated documentation are proprietary to
// Synopsys, Inc. and may only be used pursuant to the terms and conditions of a
// written license agreement with Synopsys, Inc. All other use, reproduction,
// modification, or distribution of the Synopsys IP or the associated
// documentation is strictly prohibited.
//
// Component Name   : DWC_ddrctl
// Component Version: 1.00a-ea06
// Release Type     : EA
//------------------------------------------------------------------------------


/**
 *
 * @detail The purpose of the functions in this file are to take the setting passed in structures in SubsysHdlr_t
 * and apply them to each of the registers in the controller memory map.
 * After each function is called a 32-bit value is ready to be written into the controller register map.
 * No APB bus cycles are actually executed by calling this methods.
 *
 */
#include <assert.h>
#include "dwc_cinit.h"
#include "bit_macros.h"
#include "dwc_cinit_macros.h"
#include "dwc_cinit_arb_macros.h"
#ifdef UMCTL2_INCL_ARB  



/** @brief iterate through all DDRC registers setting up a 32-bit value to
 * be programmed into each writable register. 
 */
void cinit_prgm_arb_regs(SubsysHdlr_t *hdlr) {
  TRACE();
  cinit_prgm_PCCFG(hdlr);
  cinit_prgm_PCFGR(hdlr);
  cinit_prgm_PCFGW(hdlr);
  cinit_prgm_PCFGQOS0(hdlr);
  cinit_prgm_PCFGQOS1(hdlr);
  cinit_prgm_PCFGWQOS0(hdlr);
  cinit_prgm_PCFGWQOS1(hdlr);
  cinit_prgm_SBRCTL(hdlr);
  cinit_prgm_SBRWDATA0(hdlr);
  cinit_prgm_SBRWDATA1(hdlr);
  cinit_prgm_PDCH(hdlr);
  cinit_prgm_PCTRL(hdlr);
  cinit_prgm_SBRSTART0(hdlr);
  cinit_prgm_SBRSTART1(hdlr);
  cinit_prgm_SBRRANGE0(hdlr);
  cinit_prgm_SBRRANGE1(hdlr);
  cinit_prgm_SBRSTART0DCH1(hdlr);
  cinit_prgm_SBRSTART1DCH1(hdlr);
  cinit_prgm_SBRRANGE0DCH1(hdlr);
  cinit_prgm_SBRRANGE1DCH1(hdlr);

  for(uint32_t n=0;n<UMCTL2_A_NSAR;n++) {
    cinit_prgm_SARBASE(hdlr,n);
    cinit_prgm_SARSIZE(hdlr,n);
  }

  for(uint32_t port=0;port<UMCTL2_A_NPORTS;port++) {
     cinit_prgm_PCFGIDMASKCH(hdlr,port);
     cinit_prgm_PCFGIDVALUECH(hdlr,port);
  }
}

void cinit_prgm_PCCFG(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_A_AXI_0
#ifdef UMCTL2_INCL_ARB
TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  REGB_ARB_PORT0_PCCFG_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_PCCFG_reg;
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  uint8_t x16=(hdlr->spdData_m.sdram_width_bits==16) ? 1 : 0;
  uint8_t density_mbits=hdlr->spdData_m.sdram_capacity_mbits;

#ifdef DDRCTL_HET_INTERLEAVE_EN_1
  APPLY_CFG_TO_REGFIELD(cfg,PCCFG,dch_density_ratio);
#ifdef DDRCTL_DDR 
  if (x16) {
    if (density_mbits==2048) {
      CONSTRAIN_EQ(reg->dch_density_ratio,0);
    } else if (density_mbits==4096) {
      CONSTRAIN_INSIDE(reg->dch_density_ratio,0,1);
    } else {
      CONSTRAIN_INSIDE(reg->dch_density_ratio,0,2);
    }
  } else {
    CONSTRAIN_EQ(reg->dch_density_ratio,0);
  }     
#else // LPDDR controller
  CONSTRAIN_EQ(reg->dch_density_ratio,0);
#endif // DDRCTL_DDR
#endif // DDRCTL_HET_INTERLEAVE_EN_1

  APPLY_CFG_TO_REGFIELD(cfg,PCCFG,pagematch_limit);
  APPLY_CFG_TO_REGFIELD(cfg,PCCFG,go2critical_en);
#endif
#endif  
 }

  

void cinit_prgm_PCFGR(SubsysHdlr_t *hdlr) {
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  TRACE();
  DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCFGR, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCFGR, PORT); 

  #ifdef UMCTL2_PORT_0 
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGR,PORT);
#ifdef UMCTL2_A_RDWR_ORDERED_0
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,0);
#endif // UMCTL2_A_RDWR_ORDERED_0
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,0);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,0);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,0);
#ifdef UMCTL2_PORT_CH0_0
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,0);
#endif // UMCTL2_PORT_CH0_0
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,0);
#endif // UMCTL2_PORT0  

#ifdef UMCTL2_PORT_1 
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_1
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,1);
#endif // UMCTL2_A_RDWR_ORDERED_1
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,1);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,1);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,1);
#ifdef UMCTL2_PORT_CH0_1
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,1);
#endif // UMCTL2_PORT_CH0_1
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,1);
#endif  // UMCTL2_PORT1  


#ifdef UMCTL2_PORT_2 
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_2
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,2);
#endif // UMCTL2_A_RDWR_ORDERED_2
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,2);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,2);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,2);
#ifdef UMCTL2_PORT_CH0_2
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,2);
#endif // UMCTL2_PORT_CH0_2
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,2);
#endif  // UMCTL2_PORT2  

#ifdef UMCTL2_PORT_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_3
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,3);
#endif // UMCTL2_A_RDWR_ORDERED_3
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,3);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,3);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,3);
#ifdef UMCTL2_PORT_CH0_3
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,3);
#endif // UMCTL2_PORT_CH0_3
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,3);
#endif  // UMCTL2_PORT3

#ifdef UMCTL2_PORT_4 
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_4
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,4);
#endif // UMCTL2_A_RDWR_ORDERED_4
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,4);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,4);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,4);
#ifdef UMCTL2_PORT_CH0_4
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,4);
#endif // UMCTL2_PORT_CH0_4
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,4);
#endif  // UMCTL2_PORT4

#ifdef UMCTL2_PORT_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_5
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,5);
#endif // UMCTL2_A_RDWR_ORDERED_5
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,5);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,5);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,5);
#ifdef UMCTL2_PORT_CH0_5
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,5);
#endif // UMCTL2_PORT_CH0_5
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,5);
#endif   // UMCTL2_PORT5

#ifdef UMCTL2_PORT_6 
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_6
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,6);
#endif // UMCTL2_A_RDWR_ORDERED_6
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,6);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,6);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,6);
#ifdef UMCTL2_PORT_CH0_6
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,6);
#endif // UMCTL2_PORT_CH0_6
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,6);
#endif  // UMCTL2_PORT6

#ifdef UMCTL2_PORT_7 
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_7
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,7);
#endif // UMCTL2_A_RDWR_ORDERED_7
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,7);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,7);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,7);
#ifdef UMCTL2_PORT_CH0_7
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,7);
#endif // UMCTL2_PORT_CH0_7
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,7);
#endif  // UMCTL2_PORT7

 #ifdef UMCTL2_PORT_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_8
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,8);
#endif // UMCTL2_A_RDWR_ORDERED_8
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,8);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,8);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,8);
#ifdef UMCTL2_PORT_CH0_8
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,8);
#endif // UMCTL2_PORT_CH0_8
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,8);
#endif  // UMCTL2_PORT8

#ifdef UMCTL2_PORT_9 
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_9
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,9);
#endif // UMCTL2_A_RDWR_ORDERED_9
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,9);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,9);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,9);
#ifdef UMCTL2_PORT_CH0_9
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,0);
#endif // UMCTL2_PORT_CH0_9
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,9);
#endif  // UMCTL2_PORT9

#ifdef UMCTL2_PORT_10 
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGR,PORT);
#ifdef UMCTL2_A_RDWR_ORDERED_10
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,10);
#endif // UMCTL2_A_RDWR_ORDERED_10
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,10);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,10);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,10);
#ifdef UMCTL2_PORT_CH0_10
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,10);
#endif // UMCTL2_PORT_CH0_10
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,10);
#endif  // UMCTL2_PORT10

#ifdef UMCTL2_PORT_11 
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_11
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,11);
#endif // UMCTL2_A_RDWR_ORDERED_11
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,11);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,11);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,11);
#ifdef UMCTL2_PORT_CH0_11
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,11);
#endif // UMCTL2_PORT_CH0_11
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,11);
#endif  // UMCTL2_PORT11

#ifdef UMCTL2_PORT_12 
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_12
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,12);
#endif // UMCTL2_A_RDWR_ORDERED_12
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,12);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,12);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,12);
#ifdef UMCTL2_PORT_CH0_12
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,12);
#endif // UMCTL2_PORT_CH0_12
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,12);
#endif  // UMCTL2_PORT12

#ifdef UMCTL2_PORT_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_13
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,13);
#endif // UMCTL2_A_RDWR_ORDERED_13
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,13);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,13);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,13);
#ifdef UMCTL2_PORT_CH0_13
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,13);
#endif // UMCTL2_PORT_CH0_13
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,13);
#endif   // UMCTL2_PORT13

#ifdef UMCTL2_PORT_14 
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_14
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,14);
#endif // UMCTL2_A_RDWR_ORDERED_14
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,14);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,14);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,14);
#ifdef UMCTL2_PORT_CH0_14
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,14);
#endif // UMCTL2_PORT_CH0_14
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,14);
#endif  // UMCTL2_PORT14  

#ifdef UMCTL2_PORT_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGR,PORT); 
#ifdef UMCTL2_A_RDWR_ORDERED_15
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,rdwr_ordered_en,15);
#endif // UMCTL2_A_RDWR_ORDERED_15
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_pagematch_en,15);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_urgent_en,15);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_aging_en,15);
#ifdef UMCTL2_PORT_CH0_15
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGR,read_reorder_bypass_en,15);
#endif // UMCTL2_PORT_CH0_15
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGR,rd_port_priority,15);
#endif  // UMCTL2_PORT15



}

void cinit_prgm_PCFGW(SubsysHdlr_t *hdlr) {
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  TRACE();
  DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCFGW, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCFGW, PORT); 


#ifdef UMCTL2_PORT_0 
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,0);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,0);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,0);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,0);
#endif // UMCTL2_PORT0  

#ifdef UMCTL2_PORT_1 
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,1);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,1);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,1);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,1);
#endif // UMCTL2_PORT1  

#ifdef UMCTL2_PORT_2 
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,2);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,2);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,2);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,2);
#endif // UMCTL2_PORT2  

#ifdef UMCTL2_PORT_3 
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,3);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,3);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,3);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,3);
#endif // UMCTL2_PORT3  

#ifdef UMCTL2_PORT_4 
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,4);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,4);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,4);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,4);
#endif // UMCTL2_PORT4  

#ifdef UMCTL2_PORT_5 
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,5);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,5);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,5);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,5);
#endif // UMCTL2_PORT5  

#ifdef UMCTL2_PORT_6 
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,6);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,6);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,6);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,6);
#endif // UMCTL2_PORT6  

#ifdef UMCTL2_PORT_7 
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,7);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,7);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,7);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,7);
#endif // UMCTL2_PORT7    

#ifdef UMCTL2_PORT_8 
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,8);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,8);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,8);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,8);
#endif // UMCTL2_PORT8  

#ifdef UMCTL2_PORT_9 
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,9);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,9);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,9);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,9);
#endif // UMCTL2_PORT9  

#ifdef UMCTL2_PORT_10 
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,10);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,10);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,10);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,10);
#endif // UMCTL2_PORT10

#ifdef UMCTL2_PORT_11 
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,11);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,11);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,11);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,11);
#endif // UMCTL2_PORT11

#ifdef UMCTL2_PORT_12 
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,12);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,12);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,12);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,12);
#endif // UMCTL2_PORT12    

#ifdef UMCTL2_PORT_13 
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,13);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,13);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,13);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,13);
#endif // UMCTL2_PORT13  

#ifdef UMCTL2_PORT_14 
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,14);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,14);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,14);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,14);
#endif // UMCTL2_PORT14
 
#ifdef UMCTL2_PORT_15 
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGW,PORT);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_pagematch_en,15);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_urgent_en,15);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_aging_en,15);
  APPLY_CFG_TO_REGFIELD_P(cfg,PCFGW,wr_port_priority,15);
#endif // UMCTL2_PORT15    


}

void cinit_prgm_PCFGQOS0(SubsysHdlr_t *hdlr) {
   mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); 
  TRACE();
  DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCFGQOS0, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCFGQOS0, PORT); 

#ifdef UMCTL2_A_AXI_0
   DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_0
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,0);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,0);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,0);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,0);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,0);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_1
   DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_1
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,1);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,1);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,1);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,1);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,1);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_2
   DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_2
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,2);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,2);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,2);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_3
   DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_3
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,3);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,3);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,3);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,3);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,3);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

 #ifdef UMCTL2_A_AXI_4
   DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_4
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,4);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,4);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,4);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,4);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,4);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_5
   DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_5
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,5);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,5);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,5);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,5);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,5);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_6
   DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_6
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,6);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,6);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,6);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,6);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,6);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_7
   DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_7
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,7);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,7);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,7);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,7);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,7);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_8
   DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_8
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,8);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,8);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,8);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,8);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,8);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

 #ifdef UMCTL2_A_AXI_9
   DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_9
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,9);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,9);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,9);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,9);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,9);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_10
   DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_10
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,10);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,10);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,10);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,10);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,10);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

 #ifdef UMCTL2_A_AXI_11
   DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_11
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,11);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,11);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,11);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,11);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,11);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_12
   DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_12
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,12);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,12);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,12);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,12);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,12);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

#ifdef UMCTL2_A_AXI_13
   DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_13
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,13);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,13);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,13);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,13);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,13);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif
  
#ifdef UMCTL2_A_AXI_14
   DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_14
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,14);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,14);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,14);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,14);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif
  
#ifdef UMCTL2_A_AXI_15
   DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGQOS0,PORT);
#ifdef UMCTL2_A_USE2RAQ_15
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region2,15);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level2,15);
  CONSTRAIN_INSIDE(reg->rqos_map_region2,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_level2,1,14);
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,13);
#else
  CONSTRAIN_INSIDE(reg->rqos_map_level1,0,14);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region1,15);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_region0,15);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS0,rqos_map_level1,15);
  CONSTRAIN_INSIDE(reg->rqos_map_region1,0,2);
  CONSTRAIN_INSIDE(reg->rqos_map_region0,0,2);
#endif

}  

void cinit_prgm_PCFGQOS1(SubsysHdlr_t *hdlr) {
   mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); 
  TRACE();
   #ifdef UMCTL2_A_AXI_0
  #ifdef UMCTL2_XPI_VPR_0

  DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCFGQOS1, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCFGQOS1, PORT); 

    DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,0);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,0);
  
  #ifdef UMCTL2_A_AXI_1
  #ifdef UMCTL2_XPI_VPR_1
   DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,1);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,1);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_2
  #ifdef UMCTL2_XPI_VPR_2
   DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,2);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,2);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_3
  #ifdef UMCTL2_XPI_VPR_3
   DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,3);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,3);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_4
  #ifdef UMCTL2_XPI_VPR_4
   DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,4);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,4);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_5
  #ifdef UMCTL2_XPI_VPR_5
   DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,5);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,5);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_6
  #ifdef UMCTL2_XPI_VPR_6
   DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,6);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,6);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_7
  #ifdef UMCTL2_XPI_VPR_7
   DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,7);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,7);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_8
  #ifdef UMCTL2_XPI_VPR_8
   DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,8);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,8);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_9
  #ifdef UMCTL2_XPI_VPR_9
   DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,9);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,9);
  #endif
  #endif

 #ifdef UMCTL2_A_AXI_10
  #ifdef UMCTL2_XPI_VPR_10
   DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,10);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,10);
  #endif
  #endif

 #ifdef UMCTL2_A_AXI_11
  #ifdef UMCTL2_XPI_VPR_11
   DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,11);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,11);
  #endif
  #endif

 #ifdef UMCTL2_A_AXI_12
  #ifdef UMCTL2_XPI_VPR_12
   DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,12);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,12);
  #endif
  #endif

 #ifdef UMCTL2_A_AXI_13
  #ifdef UMCTL2_XPI_VPR_13
   DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,13);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,13);
  #endif
  #endif

 #ifdef UMCTL2_A_AXI_14
  #ifdef UMCTL2_XPI_VPR_14
   DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,14);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,14);
  #endif
  #endif

  #ifdef UMCTL2_A_AXI_15
  #ifdef UMCTL2_XPI_VPR_15
   DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGQOS1,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutr,15);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGQOS1,rqos_map_timeoutb,15);
  #endif
  #endif
  #endif
  #endif

}

void cinit_prgm_PCFGWQOS0(SubsysHdlr_t *hdlr) {
   mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); 
  TRACE();
   #ifdef UMCTL2_A_AXI_0
  #ifdef UMCTL2_XPI_VPW_0
 DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCFGWQOS0, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCFGWQOS0, PORT); 


   DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,0);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,0);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,0);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,0);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,0);

   #ifdef UMCTL2_A_AXI_1
  #ifdef UMCTL2_XPI_VPW_1
   DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,1);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,1);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,1);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,1);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,1);
  #endif
  #endif

 #ifdef UMCTL2_A_AXI_2
  #ifdef UMCTL2_XPI_VPW_2
   DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,2);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,2);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,2);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,2);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,2);
  #endif
  #endif

 #ifdef UMCTL2_A_AXI_3
  #ifdef UMCTL2_XPI_VPW_3
   DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,3);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,3);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,3);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,3);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,3);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_4
  #ifdef UMCTL2_XPI_VPW_4
   DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,4);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,4);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,4);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,4);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,4);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_5
  #ifdef UMCTL2_XPI_VPW_5
   DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,5);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,5);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,5);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,5);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,5);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_6
  #ifdef UMCTL2_XPI_VPW_6
   DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,6);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,6);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,6);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,6);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,6);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_7
  #ifdef UMCTL2_XPI_VPW_7
   DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,7);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,7);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,7);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,7);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,7);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_8
  #ifdef UMCTL2_XPI_VPW_8
   DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,8);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,8);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,8);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,8);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,8);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_9
  #ifdef UMCTL2_XPI_VPW_9
   DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,9);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,9);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,9);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,9);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,9);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_10
  #ifdef UMCTL2_XPI_VPW_10
   DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,10);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,10);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,10);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,10);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,10);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_11
  #ifdef UMCTL2_XPI_VPW_11
   DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,11);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,11);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,11);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,11);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,11);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_12
  #ifdef UMCTL2_XPI_VPW_12
   DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,12);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,12);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,12);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,12);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,12);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_13
  #ifdef UMCTL2_XPI_VPW_13
   DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,13);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,13);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,13);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,13);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,13);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_14
  #ifdef UMCTL2_XPI_VPW_14
   DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,14);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,14);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,14);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,14);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,14);
  #endif
  #endif

#ifdef UMCTL2_A_AXI_15
  #ifdef UMCTL2_XPI_VPW_15
   DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGWQOS0,PORT);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region2,15);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level2,15);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region1,15);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_region0,15);
   APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS0,wqos_map_level1,15);
  #endif
  #endif
  #endif
  #endif
}

void cinit_prgm_PCFGWQOS1(SubsysHdlr_t *hdlr) {
   mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); 
  TRACE();

  #ifdef UMCTL2_A_AXI_0
  #ifdef UMCTL2_XPI_VPW_0
 DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCFGWQOS1, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCFGWQOS1, PORT); 

  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGWQOS1,PORT);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,0);
  APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,0);

  #ifdef UMCTL2_A_AXI_1
 #ifdef UMCTL2_XPI_VPW_1
 DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,1);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,1);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_2
 #ifdef UMCTL2_XPI_VPW_2
 DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,2);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,2);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_3
 #ifdef UMCTL2_XPI_VPW_3
 DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,3);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,3);
 #endif
 #endif


 #ifdef UMCTL2_A_AXI_4
 #ifdef UMCTL2_XPI_VPW_4
 DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,4);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,4);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_5
 #ifdef UMCTL2_XPI_VPW_5
 DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,5);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,5);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_6
 #ifdef UMCTL2_XPI_VPW_6
 DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,6);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,6);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_7
 #ifdef UMCTL2_XPI_VPW_7
 DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,7);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,7);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_8
 #ifdef UMCTL2_XPI_VPW_8
 DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,8);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,8);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_9
 #ifdef UMCTL2_XPI_VPW_9
 DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,9);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,9);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_10
 #ifdef UMCTL2_XPI_VPW_10
 DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,10);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,10);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_11
 #ifdef UMCTL2_XPI_VPW_11
 DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,11);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,11);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_12
 #ifdef UMCTL2_XPI_VPW_12
 DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,12);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,12);
 #endif
 #endif

#ifdef UMCTL2_A_AXI_13
 #ifdef UMCTL2_XPI_VPW_13
 DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,13);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,13);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_14
 #ifdef UMCTL2_XPI_VPW_14
 DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,14);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,14);
 #endif
 #endif

 #ifdef UMCTL2_A_AXI_15
 #ifdef UMCTL2_XPI_VPW_15
 DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGWQOS1,PORT);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout2,15);
 APPLY_CFG_TO_REGFIELD_P(qdyn,PCFGWQOS1,wqos_map_timeout1,15);
 #endif
 #endif
#endif
#endif

}
 
void cinit_prgm_SARBASE (SubsysHdlr_t *hdlr,uint32_t n) {
#ifdef UMCTL2_INCL_ARB
#ifdef UMCTL2_A_SAR_0  
  TRACE();
  CONSTRAIN_INSIDE(n, 0, 3);  
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.

  REGB_ARB_PORT0_SARBASE0_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARBASE0_reg;

 
  // casting pointer is ok as register struct is identical 
  if(n==0) { reg= &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARBASE0_reg;}
#ifdef UMCTL2_A_SAR_1  
   REGB_ARB_PORT0_SARBASE1_struct_t *reg1;
  if(n==1) { 
      reg1=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARBASE1_reg;
      reg=( REGB_ARB_PORT0_SARBASE0_struct_t *)reg1;
  }
#endif
#ifdef UMCTL2_A_SAR_2  
   REGB_ARB_PORT0_SARBASE2_struct_t *reg2;  
  if(n==2) { 
      reg2=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARBASE2_reg;
      reg=( REGB_ARB_PORT0_SARBASE0_struct_t *)reg2;
  }
#endif

#ifdef UMCTL2_A_SAR_3
   REGB_ARB_PORT0_SARBASE3_struct_t *reg3; 
  if(n==3) { 
      reg3=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARBASE3_reg;
      reg=( REGB_ARB_PORT0_SARBASE0_struct_t *)reg3;
  }
#endif

  APPLY_CFG_TO_REGFIELD_P(cfg,SARBASE0,base_addr,n);
 #endif // UMCTL2_A_SAR_0
#endif //UMCTL2_INC_ARB
}

void cinit_prgm_SARSIZE (SubsysHdlr_t *hdlr,uint32_t n) {
#ifdef UMCTL2_INCL_ARB
#ifdef UMCTL2_A_SAR_0  
  TRACE();
  CONSTRAIN_INSIDE(n, 0, 3);  
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.

   REGB_ARB_PORT0_SARSIZE0_struct_t *reg;
  if(n==0) { reg=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARSIZE0_reg;}

  // casting pointer is ok as register struct is identical 
#ifdef UMCTL2_A_SAR_1  
   REGB_ARB_PORT0_SARSIZE1_struct_t *reg1;
  if(n==1) { 
      reg1=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARSIZE1_reg;
      reg=(REGB_ARB_PORT0_SARSIZE0_struct_t *)reg1;
  }
#endif

#ifdef UMCTL2_A_SAR_2
   REGB_ARB_PORT0_SARSIZE2_struct_t *reg2;
  if(n==2) { 
      reg2=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARSIZE2_reg;
      reg=(REGB_ARB_PORT0_SARSIZE0_struct_t *)reg2;
  }

#endif

#ifdef UMCTL2_A_SAR_3
   REGB_ARB_PORT0_SARSIZE3_struct_t *reg3;
  if(n==3) { 
      reg3=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SARSIZE3_reg;
      reg=(REGB_ARB_PORT0_SARSIZE0_struct_t *)reg3;
  }
#endif 

  APPLY_CFG_TO_REGFIELD_P(cfg,SARSIZE0,nblocks,n);
#endif // UMCTL2_A_SAR_0
#endif //UMCTL2_AINCL_ARB

}

void cinit_prgm_SBRCTL(SubsysHdlr_t *hdlr){
   mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  #ifdef UMCTL2_SBR_EN_1
  REGB_ARB_PORT0_SBRCTL_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRCTL_reg;
  TRACE();
 APPLY_CFG_TO_REGFIELD(dyn,SBRCTL,scrub_interval);
 APPLY_CFG_TO_REGFIELD(dyn,SBRCTL,scrub_burst_length_normal);
 APPLY_CFG_TO_REGFIELD(dyn,SBRCTL,scrub_burst_length_lp);
 CONSTRAIN_INSIDE(reg->scrub_burst_length_normal,1,6);
 CONSTRAIN_INSIDE(reg->scrub_burst_length_lp,1,6);

#ifdef UMCTL2_DUAL_CHANNEL
 APPLY_CFG_TO_REGFIELD(dyn,SBRCTL,scrub_en_dch1);
 CONSTRAIN_INSIDE(reg->scrub_en_dch1,0,1);
#endif
 APPLY_CFG_TO_REGFIELD(dyn,SBRCTL,scrub_cmd_type);
 CONSTRAIN_INSIDE(reg->scrub_cmd_type,0,1);
 APPLY_CFG_TO_REGFIELD(dyn,SBRCTL,scrub_during_lowpower);
 CONSTRAIN_INSIDE(reg->scrub_during_lowpower,0,1);
 APPLY_CFG_TO_REGFIELD(dyn,SBRCTL,scrub_en);
 CONSTRAIN_INSIDE(reg->scrub_en,0,1);
#endif
}

void cinit_prgm_SBRWDATA0(SubsysHdlr_t *hdlr){
  #ifdef UMCTL2_SBR_EN_1
   TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRWDATA0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRWDATA0_reg;
  APPLY_CFG_TO_REGFIELD(dyn,SBRWDATA0,scrub_pattern0);
#endif
}

void cinit_prgm_SBRWDATA1(SubsysHdlr_t *hdlr){
 #ifdef UMCTL2_SBR_EN_1
 #ifdef MEMC_DRAM_DATA_WIDTH_64
   TRACE();

  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  REGB_ARB_PORT0_SBRWDATA1_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRWDATA1_reg;
  APPLY_CFG_TO_REGFIELD(dyn,SBRWDATA1,scrub_pattern1);
#endif
#endif
}

void cinit_prgm_PDCH(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_DUAL_DATA_CHANNEL
#ifndef UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
#ifdef UMCTL2_INCL_ARB
   TRACE();

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  
 REGB_ARB_PORT0_PDCH_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_PDCH_reg;
 
#ifdef UMCTL2_PORT_0
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_0);
#endif

#ifdef UMCTL2_PORT_1
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_1);
#endif

#ifdef UMCTL2_PORT_2
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_2);
#endif

#ifdef UMCTL2_PORT_3
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_3);
#endif

#ifdef UMCTL2_PORT_4
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_4);
#endif

#ifdef UMCTL2_PORT_5
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_5);
#endif

#ifdef UMCTL2_PORT_6
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_6);
#endif

#ifdef UMCTL2_PORT_7
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_7);
#endif

#ifdef UMCTL2_PORT_8
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_8);
#endif

#ifdef UMCTL2_PORT_9
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_9);
#endif

#ifdef UMCTL2_PORT_10
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_10);
#endif

#ifdef UMCTL2_PORT_11
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_11);
#endif

#ifdef UMCTL2_PORT_12
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_12);
#endif

#ifdef UMCTL2_PORT_13
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_13);
#endif

#ifdef UMCTL2_PORT_14
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_14);
#endif

#ifdef UMCTL2_PORT_15
 APPLY_CFG_TO_REGFIELD(cfg,PDCH,port_data_channel_15);
#endif

#endif
#endif
#endif

}  

void cinit_prgm_PCTRL(SubsysHdlr_t *hdlr) {
   #ifdef UMCTL2_INCL_ARB
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
   

  DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCTRL, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCTRL, PORT); 

  #ifdef UMCTL2_PORT_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,0);
 #endif
 
  #ifdef UMCTL2_PORT_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,1);
  #endif
 
  #ifdef UMCTL2_PORT_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,2);
  #endif

 #ifdef UMCTL2_PORT_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,3);
 #endif

 #ifdef UMCTL2_PORT_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,4);
 #endif

 #ifdef UMCTL2_PORT_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,5);
  #endif

 #ifdef UMCTL2_PORT_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,6);
  #endif

 #ifdef UMCTL2_PORT_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,7);
  #endif

 #ifdef UMCTL2_PORT_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,8);
  #endif

 #ifdef UMCTL2_PORT_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,9);
  #endif

 #ifdef UMCTL2_PORT_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,10);
  #endif

 #ifdef UMCTL2_PORT_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,11);
  #endif

 #ifdef UMCTL2_PORT_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,12);
  #endif

 #ifdef UMCTL2_PORT_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,13);
  #endif

  #ifdef UMCTL2_PORT_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,14);
  #endif

 #ifdef UMCTL2_PORT_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCTRL,PORT);
  APPLY_CFG_TO_REGFIELD_P(dyn,PCTRL,port_en,15);
  #endif
#endif 
}

void cinit_prgm_PCFGIDMASKCH(SubsysHdlr_t *hdlr,uint32_t port) {
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  TRACE();
#ifdef UMCTL2_PORT_CH0_0
  DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCFGIDMASKCH0, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCFGIDMASKCH0, PORT); 
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,0,0);

#ifdef UMCTL2_PORT_CH1_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,0,1);
#endif // UMCTL2_PORT_CH1_0

#ifdef UMCTL2_PORT_CH2_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,0,2);
#endif // UMCTL2_PORT_CH2_0
 
#ifdef UMCTL2_PORT_CH3_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,0,3);
#endif // UMCTL2_PORT_CH3_0

#ifdef UMCTL2_PORT_CH4_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,0,4);
#endif // UMCTL2_PORT_CH4_0

#ifdef UMCTL2_PORT_CH5_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,0,5);
#endif // UMCTL2_PORT_CH5_0

#ifdef UMCTL2_PORT_CH6_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,0,6);
#endif // UMCTL2_PORT_CH6_0

#ifdef UMCTL2_PORT_CH7_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,0,7);
#endif // UMCTL2_PORT_CH7_0

#ifdef UMCTL2_PORT_CH8_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,0,8);
#endif // UMCTL2_PORT_CH8_0

#ifdef UMCTL2_PORT_CH9_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,0,9);
#endif // UMCTL2_PORT_CH9_0

#ifdef UMCTL2_PORT_CH10_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,0,10);
#endif // UMCTL2_PORT_CH10_0

#ifdef UMCTL2_PORT_CH11_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,0,11);
#endif // UMCTL2_PORT_CH11_0

#ifdef UMCTL2_PORT_CH12_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,0,12);
#endif // UMCTL2_PORT_CH12_0
  
#ifdef UMCTL2_PORT_CH13_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,0,13);
#endif // UMCTL2_PORT_CH13_0


#ifdef UMCTL2_PORT_CH14_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,0,14);
#endif // UMCTL2_PORT_CH14_0
#ifdef UMCTL2_PORT_CH15_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,0,15);
#endif // UMCTL2_PORT_CH15_0


////////////PORT_1//////////////////////////////

#ifdef UMCTL2_PORT_CH0_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,1,0);
#endif // UMCTL2_PORT_CH0_1

 #ifdef UMCTL2_PORT_CH1_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,1,1);
#endif // UMCTL2_PORT_CH1_1

#ifdef UMCTL2_PORT_CH2_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,1,2);
#endif // UMCTL2_PORT_CH2_1
 
#ifdef UMCTL2_PORT_CH3_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,1,3);
#endif // UMCTL2_PORT_CH3_1

#ifdef UMCTL2_PORT_CH4_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,1,4);
#endif // UMCTL2_PORT_CH4_1

#ifdef UMCTL2_PORT_CH5_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,1,5);
#endif // UMCTL2_PORT_CH5_1

#ifdef UMCTL2_PORT_CH6_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,1,6);
#endif // UMCTL2_PORT_CH6_1

#ifdef UMCTL2_PORT_CH7_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,1,7);
#endif // UMCTL2_PORT_CH7_1

#ifdef UMCTL2_PORT_CH8_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,1,8);
#endif // UMCTL2_PORT_CH8_1

#ifdef UMCTL2_PORT_CH9_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,1,9);
#endif // UMCTL2_PORT_CH9_1

#ifdef UMCTL2_PORT_CH10_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,1,10);
#endif // UMCTL2_PORT_CH10_1

#ifdef UMCTL2_PORT_CH11_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,1,11);
#endif // UMCTL2_PORT_CH11_1

#ifdef UMCTL2_PORT_CH12_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,1,12);
#endif // UMCTL2_PORT_CH12_1
  
#ifdef UMCTL2_PORT_CH13_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,1,13);
#endif // UMCTL2_PORT_CH13_1


#ifdef UMCTL2_PORT_CH14_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,1,14);
#endif // UMCTL2_PORT_CH14_1
#ifdef UMCTL2_PORT_CH15_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,1,15);
#endif // UMCTL2_PORT_CH15_1


///////////////PORT_2//////////////////////

  #ifdef UMCTL2_PORT_CH0_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,2,0);
#endif // UMCTL2_PORT_CH0_2

 #ifdef UMCTL2_PORT_CH1_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,2,1);
#endif // UMCTL2_PORT_CH1_2

#ifdef UMCTL2_PORT_CH2_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,2,2);
#endif // UMCTL2_PORT_CH2_2
 
#ifdef UMCTL2_PORT_CH3_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,2,3);
#endif // UMCTL2_PORT_CH3_2

#ifdef UMCTL2_PORT_CH4_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,2,4);
#endif // UMCTL2_PORT_CH4_2

#ifdef UMCTL2_PORT_CH5_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,2,5);
#endif // UMCTL2_PORT_CH5_2

#ifdef UMCTL2_PORT_CH6_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,2,6);
#endif // UMCTL2_PORT_CH6_2

#ifdef UMCTL2_PORT_CH7_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,2,7);
#endif // UMCTL2_PORT_CH7_2

#ifdef UMCTL2_PORT_CH8_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,2,8);
#endif // UMCTL2_PORT_CH8_2

#ifdef UMCTL2_PORT_CH9_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,2,9);
#endif // UMCTL2_PORT_CH9_2

#ifdef UMCTL2_PORT_CH10_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,2,10);
#endif // UMCTL2_PORT_CH10_2

#ifdef UMCTL2_PORT_CH11_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,2,11);
#endif // UMCTL2_PORT_CH11_2

#ifdef UMCTL2_PORT_CH12_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,2,12);
#endif // UMCTL2_PORT_CH12_2
  
#ifdef UMCTL2_PORT_CH13_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,2,13);
#endif // UMCTL2_PORT_CH13_2


#ifdef UMCTL2_PORT_CH14_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,2,14);
#endif // UMCTL2_PORT_CH14_2
#ifdef UMCTL2_PORT_CH15_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,2,15);
#endif // UMCTL2_PORT_CH15_2

/////PORT3//////////////////

 #ifdef UMCTL2_PORT_CH0_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,3,0);
#endif // UMCTL2_PORT_CH0_3

 #ifdef UMCTL2_PORT_CH1_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,3,1);
#endif // UMCTL2_PORT_CH1_3

#ifdef UMCTL2_PORT_CH2_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,3,2);
#endif // UMCTL2_PORT_CH2_3
 
#ifdef UMCTL2_PORT_CH3_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,3,3);
#endif // UMCTL2_PORT_CH3_3

#ifdef UMCTL2_PORT_CH4_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,3,4);
#endif // UMCTL2_PORT_CH4_3

#ifdef UMCTL2_PORT_CH5_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,3,5);
#endif // UMCTL2_PORT_CH5_3

#ifdef UMCTL2_PORT_CH6_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,3,6);
#endif // UMCTL2_PORT_CH6_3

#ifdef UMCTL2_PORT_CH7_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,3,7);
#endif // UMCTL2_PORT_CH7_3

#ifdef UMCTL2_PORT_CH8_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,3,8);
#endif // UMCTL2_PORT_CH8_3

#ifdef UMCTL2_PORT_CH9_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,3,9);
#endif // UMCTL2_PORT_CH9_3

#ifdef UMCTL2_PORT_CH10_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,3,10);
#endif // UMCTL2_PORT_CH10_3

#ifdef UMCTL2_PORT_CH11_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,3,11);
#endif // UMCTL2_PORT_CH11_3

#ifdef UMCTL2_PORT_CH12_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,3,12);
#endif // UMCTL2_PORT_CH12_3
  
#ifdef UMCTL2_PORT_CH13_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,3,13);
#endif // UMCTL2_PORT_CH13_3


#ifdef UMCTL2_PORT_CH14_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,3,14);
#endif // UMCTL2_PORT_CH14_3
#ifdef UMCTL2_PORT_CH15_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,3,15);
#endif // UMCTL2_PORT_CH15_3


///////PORT_4/////////

 #ifdef UMCTL2_PORT_CH0_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,4,0);
#endif // UMCTL2_PORT_CH0_4

 #ifdef UMCTL2_PORT_CH1_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,4,1);
#endif // UMCTL2_PORT_CH1_4

#ifdef UMCTL2_PORT_CH2_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,4,2);
#endif // UMCTL2_PORT_CH2_4
 
#ifdef UMCTL2_PORT_CH3_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,4,3);
#endif // UMCTL2_PORT_CH3_4

#ifdef UMCTL2_PORT_CH4_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,4,4);
#endif // UMCTL2_PORT_CH4_4

#ifdef UMCTL2_PORT_CH5_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,4,5);
#endif // UMCTL2_PORT_CH5_4

#ifdef UMCTL2_PORT_CH6_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,4,6);
#endif // UMCTL2_PORT_CH6_4

#ifdef UMCTL2_PORT_CH7_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,4,7);
#endif // UMCTL2_PORT_CH7_4

#ifdef UMCTL2_PORT_CH8_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,4,8);
#endif // UMCTL2_PORT_CH8_4

#ifdef UMCTL2_PORT_CH9_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,4,9);
#endif // UMCTL2_PORT_CH9_4

#ifdef UMCTL2_PORT_CH10_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,4,10);
#endif // UMCTL2_PORT_CH10_4

#ifdef UMCTL2_PORT_CH11_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,4,11);
#endif // UMCTL2_PORT_CH11_4

#ifdef UMCTL2_PORT_CH12_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,4,12);
#endif // UMCTL2_PORT_CH12_4
  
#ifdef UMCTL2_PORT_CH13_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,4,13);
#endif // UMCTL2_PORT_CH13_4


#ifdef UMCTL2_PORT_CH14_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,4,14);
#endif // UMCTL2_PORT_CH14_4
#ifdef UMCTL2_PORT_CH15_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,4,15);
#endif // UMCTL2_PORT_CH15_4


////////PORT_5/////////

 #ifdef UMCTL2_PORT_CH0_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,5,0);
#endif // UMCTL2_PORT_CH0_5

 #ifdef UMCTL2_PORT_CH1_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,5,1);
#endif // UMCTL2_PORT_CH1_5

#ifdef UMCTL2_PORT_CH2_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,5,2);
#endif // UMCTL2_PORT_CH2_5
 
#ifdef UMCTL2_PORT_CH3_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,5,3);
#endif // UMCTL2_PORT_CH3_5

#ifdef UMCTL2_PORT_CH4_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,5,4);
#endif // UMCTL2_PORT_CH4_5

#ifdef UMCTL2_PORT_CH5_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,5,5);
#endif // UMCTL2_PORT_CH5_5

#ifdef UMCTL2_PORT_CH6_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,5,6);
#endif // UMCTL2_PORT_CH6_5

#ifdef UMCTL2_PORT_CH7_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,5,7);
#endif // UMCTL2_PORT_CH7_5

#ifdef UMCTL2_PORT_CH8_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,5,8);
#endif // UMCTL2_PORT_CH8_5

#ifdef UMCTL2_PORT_CH9_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,5,9);
#endif // UMCTL2_PORT_CH9_5

#ifdef UMCTL2_PORT_CH10_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,5,10);
#endif // UMCTL2_PORT_CH10_5

#ifdef UMCTL2_PORT_CH11_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,5,11);
#endif // UMCTL2_PORT_CH11_5

#ifdef UMCTL2_PORT_CH12_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,5,12);
#endif // UMCTL2_PORT_CH12_5
  
#ifdef UMCTL2_PORT_CH13_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,5,13);
#endif // UMCTL2_PORT_CH13_5


#ifdef UMCTL2_PORT_CH14_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,5,14);
#endif // UMCTL2_PORT_CH14_5
#ifdef UMCTL2_PORT_CH15_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,5,15);
#endif // UMCTL2_PORT_CH15_5


/////PORT_6////////////////////////

 #ifdef UMCTL2_PORT_CH0_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,6,0);
#endif // UMCTL2_PORT_CH0_6

 #ifdef UMCTL2_PORT_CH1_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,6,1);
#endif // UMCTL2_PORT_CH1_6

#ifdef UMCTL2_PORT_CH2_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,6,2);
#endif // UMCTL2_PORT_CH2_6
 
#ifdef UMCTL2_PORT_CH3_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,6,3);
#endif // UMCTL2_PORT_CH3_6

#ifdef UMCTL2_PORT_CH4_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,6,4);
#endif // UMCTL2_PORT_CH4_6

#ifdef UMCTL2_PORT_CH5_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,6,5);
#endif // UMCTL2_PORT_CH5_6

#ifdef UMCTL2_PORT_CH6_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,6,6);
#endif // UMCTL2_PORT_CH6_6

#ifdef UMCTL2_PORT_CH7_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,6,7);
#endif // UMCTL2_PORT_CH7_6

#ifdef UMCTL2_PORT_CH8_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,6,8);
#endif // UMCTL2_PORT_CH8_6

#ifdef UMCTL2_PORT_CH9_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,6,9);
#endif // UMCTL2_PORT_CH9_6

#ifdef UMCTL2_PORT_CH10_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,6,10);
#endif // UMCTL2_PORT_CH10_6

#ifdef UMCTL2_PORT_CH11_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,6,11);
#endif // UMCTL2_PORT_CH11_6

#ifdef UMCTL2_PORT_CH12_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,6,12);
#endif // UMCTL2_PORT_CH12_6
  
#ifdef UMCTL2_PORT_CH13_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,6,13);
#endif // UMCTL2_PORT_CH13_6


#ifdef UMCTL2_PORT_CH14_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,6,14);
#endif // UMCTL2_PORT_CH14_6
#ifdef UMCTL2_PORT_CH15_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,6,15);
#endif // UMCTL2_PORT_CH15_6

/////PORT_7////////////////////////

 #ifdef UMCTL2_PORT_CH0_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,7,0);
#endif // UMCTL2_PORT_CH0_7

 #ifdef UMCTL2_PORT_CH1_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,7,1);
#endif // UMCTL2_PORT_CH1_7

#ifdef UMCTL2_PORT_CH2_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,7,2);
#endif // UMCTL2_PORT_CH2_7
 
#ifdef UMCTL2_PORT_CH3_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,7,3);
#endif // UMCTL2_PORT_CH3_7

#ifdef UMCTL2_PORT_CH4_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,7,4);
#endif // UMCTL2_PORT_CH4_7

#ifdef UMCTL2_PORT_CH5_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,7,5);
#endif // UMCTL2_PORT_CH5_7

#ifdef UMCTL2_PORT_CH6_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,7,6);
#endif // UMCTL2_PORT_CH6_7

#ifdef UMCTL2_PORT_CH7_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,7,7);
#endif // UMCTL2_PORT_CH7_7

#ifdef UMCTL2_PORT_CH8_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,7,8);
#endif // UMCTL2_PORT_CH8_7

#ifdef UMCTL2_PORT_CH9_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,7,9);
#endif // UMCTL2_PORT_CH9_7

#ifdef UMCTL2_PORT_CH10_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,7,10);
#endif // UMCTL2_PORT_CH10_7

#ifdef UMCTL2_PORT_CH11_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,7,11);
#endif // UMCTL2_PORT_CH11_7

#ifdef UMCTL2_PORT_CH12_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,7,12);
#endif // UMCTL2_PORT_CH12_7
  
#ifdef UMCTL2_PORT_CH13_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,7,13);
#endif // UMCTL2_PORT_CH13_7


#ifdef UMCTL2_PORT_CH14_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,7,14);
#endif // UMCTL2_PORT_CH14_7
#ifdef UMCTL2_PORT_CH15_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,7,15);
#endif // UMCTL2_PORT_CH15_7

  ////PORT_8

 #ifdef UMCTL2_PORT_CH0_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,8,0);
#endif // UMCTL2_PORT_CH0_8

 #ifdef UMCTL2_PORT_CH1_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,8,1);
#endif // UMCTL2_PORT_CH1_8

#ifdef UMCTL2_PORT_CH2_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,8,2);
#endif // UMCTL2_PORT_CH2_8
 
#ifdef UMCTL2_PORT_CH3_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,8,3);
#endif // UMCTL2_PORT_CH3_8

#ifdef UMCTL2_PORT_CH4_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,8,4);
#endif // UMCTL2_PORT_CH4_8

#ifdef UMCTL2_PORT_CH5_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,8,5);
#endif // UMCTL2_PORT_CH5_8

#ifdef UMCTL2_PORT_CH6_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,8,6);
#endif // UMCTL2_PORT_CH6_8

#ifdef UMCTL2_PORT_CH7_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,8,7);
#endif // UMCTL2_PORT_CH7_8

#ifdef UMCTL2_PORT_CH8_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,8,8);
#endif // UMCTL2_PORT_CH8_8

#ifdef UMCTL2_PORT_CH9_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,8,9);
#endif // UMCTL2_PORT_CH9_8

#ifdef UMCTL2_PORT_CH10_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,8,10);
#endif // UMCTL2_PORT_CH10_8

#ifdef UMCTL2_PORT_CH11_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,8,11);
#endif // UMCTL2_PORT_CH11_8

#ifdef UMCTL2_PORT_CH12_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,8,12);
#endif // UMCTL2_PORT_CH12_8
  
#ifdef UMCTL2_PORT_CH13_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,8,13);
#endif // UMCTL2_PORT_CH13_8


#ifdef UMCTL2_PORT_CH14_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,8,14);
#endif // UMCTL2_PORT_CH14_8
#ifdef UMCTL2_PORT_CH15_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,8,15);
#endif // UMCTL2_PORT_CH15_8

//PORT_9///

 #ifdef UMCTL2_PORT_CH0_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,9,0);
#endif // UMCTL2_PORT_CH0_9

 #ifdef UMCTL2_PORT_CH1_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,9,1);
#endif // UMCTL2_PORT_CH1_9

#ifdef UMCTL2_PORT_CH2_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,9,2);
#endif // UMCTL2_PORT_CH2_9
 
#ifdef UMCTL2_PORT_CH3_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,9,3);
#endif // UMCTL2_PORT_CH3_9

#ifdef UMCTL2_PORT_CH4_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,9,4);
#endif // UMCTL2_PORT_CH4_9

#ifdef UMCTL2_PORT_CH5_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,9,5);
#endif // UMCTL2_PORT_CH5_9

#ifdef UMCTL2_PORT_CH6_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,9,6);
#endif // UMCTL2_PORT_CH6_9

#ifdef UMCTL2_PORT_CH7_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,9,7);
#endif // UMCTL2_PORT_CH7_9

#ifdef UMCTL2_PORT_CH8_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,9,8);
#endif // UMCTL2_PORT_CH8_9

#ifdef UMCTL2_PORT_CH9_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,9,9);
#endif // UMCTL2_PORT_CH9_9

#ifdef UMCTL2_PORT_CH10_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,9,10);
#endif // UMCTL2_PORT_CH10_9

#ifdef UMCTL2_PORT_CH11_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,9,11);
#endif // UMCTL2_PORT_CH11_9

#ifdef UMCTL2_PORT_CH12_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,9,12);
#endif // UMCTL2_PORT_CH12_9
  
#ifdef UMCTL2_PORT_CH13_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,9,13);
#endif // UMCTL2_PORT_CH13_9


#ifdef UMCTL2_PORT_CH14_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,9,14);
#endif // UMCTL2_PORT_CH14_9
#ifdef UMCTL2_PORT_CH15_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,9,15);
#endif // UMCTL2_PORT_CH15_9

////PORT_10/////
  
 #ifdef UMCTL2_PORT_CH0_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,10,0);
#endif // UMCTL2_PORT_CH0_10

 #ifdef UMCTL2_PORT_CH1_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,10,1);
#endif // UMCTL2_PORT_CH1_10

#ifdef UMCTL2_PORT_CH2_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,10,2);
#endif // UMCTL2_PORT_CH2_10
 
#ifdef UMCTL2_PORT_CH3_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,10,3);
#endif // UMCTL2_PORT_CH3_10

#ifdef UMCTL2_PORT_CH4_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,10,4);
#endif // UMCTL2_PORT_CH4_10

#ifdef UMCTL2_PORT_CH5_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,10,5);
#endif // UMCTL2_PORT_CH5_10

#ifdef UMCTL2_PORT_CH6_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,10,6);
#endif // UMCTL2_PORT_CH6_10

#ifdef UMCTL2_PORT_CH7_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,10,7);
#endif // UMCTL2_PORT_CH7_10

#ifdef UMCTL2_PORT_CH8_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,10,8);
#endif // UMCTL2_PORT_CH8_10

#ifdef UMCTL2_PORT_CH9_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,10,9);
#endif // UMCTL2_PORT_CH9_10

#ifdef UMCTL2_PORT_CH10_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,10,10);
#endif // UMCTL2_PORT_CH10_10

#ifdef UMCTL2_PORT_CH11_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,10,11);
#endif // UMCTL2_PORT_CH11_10

#ifdef UMCTL2_PORT_CH12_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,10,12);
#endif // UMCTL2_PORT_CH12_10
  
#ifdef UMCTL2_PORT_CH13_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,10,13);
#endif // UMCTL2_PORT_CH13_10


#ifdef UMCTL2_PORT_CH14_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,10,14);
#endif // UMCTL2_PORT_CH14_10
#ifdef UMCTL2_PORT_CH15_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,10,15);
#endif // UMCTL2_PORT_CH15_10

 //PORT_11// 

 #ifdef UMCTL2_PORT_CH0_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,11,0);
#endif // UMCTL2_PORT_CH0_11

 #ifdef UMCTL2_PORT_CH1_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,11,1);
#endif // UMCTL2_PORT_CH1_11

#ifdef UMCTL2_PORT_CH2_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,11,2);
#endif // UMCTL2_PORT_CH2_11
 
#ifdef UMCTL2_PORT_CH3_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,11,3);
#endif // UMCTL2_PORT_CH3_11

#ifdef UMCTL2_PORT_CH4_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,11,4);
#endif // UMCTL2_PORT_CH4_11

#ifdef UMCTL2_PORT_CH5_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,11,5);
#endif // UMCTL2_PORT_CH5_11

#ifdef UMCTL2_PORT_CH6_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,11,6);
#endif // UMCTL2_PORT_CH6_11

#ifdef UMCTL2_PORT_CH7_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,11,7);
#endif // UMCTL2_PORT_CH7_11

#ifdef UMCTL2_PORT_CH8_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,11,8);
#endif // UMCTL2_PORT_CH8_11

#ifdef UMCTL2_PORT_CH9_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,11,9);
#endif // UMCTL2_PORT_CH9_11

#ifdef UMCTL2_PORT_CH10_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,11,10);
#endif // UMCTL2_PORT_CH10_11

#ifdef UMCTL2_PORT_CH11_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,11,11);
#endif // UMCTL2_PORT_CH11_11

#ifdef UMCTL2_PORT_CH12_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,11,12);
#endif // UMCTL2_PORT_CH12_11
  
#ifdef UMCTL2_PORT_CH13_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,11,13);
#endif // UMCTL2_PORT_CH13_11


#ifdef UMCTL2_PORT_CH14_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,11,14);
#endif // UMCTL2_PORT_CH14_11
#ifdef UMCTL2_PORT_CH15_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,11,15);
#endif // UMCTL2_PORT_CH15_11

////PORT_12/////

 #ifdef UMCTL2_PORT_CH0_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,12,0);
#endif // UMCTL2_PORT_CH0_12

 #ifdef UMCTL2_PORT_CH1_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,12,1);
#endif // UMCTL2_PORT_CH1_12

#ifdef UMCTL2_PORT_CH2_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,12,2);
#endif // UMCTL2_PORT_CH2_12
 
#ifdef UMCTL2_PORT_CH3_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,12,3);
#endif // UMCTL2_PORT_CH3_12

#ifdef UMCTL2_PORT_CH4_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,12,4);
#endif // UMCTL2_PORT_CH4_12

#ifdef UMCTL2_PORT_CH5_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,12,5);
#endif // UMCTL2_PORT_CH5_12

#ifdef UMCTL2_PORT_CH6_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,12,6);
#endif // UMCTL2_PORT_CH6_12

#ifdef UMCTL2_PORT_CH7_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,12,7);
#endif // UMCTL2_PORT_CH7_12

#ifdef UMCTL2_PORT_CH8_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,12,8);
#endif // UMCTL2_PORT_CH8_12

#ifdef UMCTL2_PORT_CH9_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,12,9);
#endif // UMCTL2_PORT_CH9_12

#ifdef UMCTL2_PORT_CH10_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,12,10);
#endif // UMCTL2_PORT_CH10_12

#ifdef UMCTL2_PORT_CH11_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,12,11);
#endif // UMCTL2_PORT_CH11_12

#ifdef UMCTL2_PORT_CH12_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,12,12);
#endif // UMCTL2_PORT_CH12_12
  
#ifdef UMCTL2_PORT_CH13_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,12,13);
#endif // UMCTL2_PORT_CH13_12


#ifdef UMCTL2_PORT_CH14_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,12,14);
#endif // UMCTL2_PORT_CH14_12
#ifdef UMCTL2_PORT_CH15_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,12,15);
#endif // UMCTL2_PORT_CH15_12

 ////PORT_13 

 #ifdef UMCTL2_PORT_CH0_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,13,0);
#endif // UMCTL2_PORT_CH0_13

 #ifdef UMCTL2_PORT_CH1_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,13,1);
#endif // UMCTL2_PORT_CH1_13

#ifdef UMCTL2_PORT_CH2_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,13,2);
#endif // UMCTL2_PORT_CH2_13
 
#ifdef UMCTL2_PORT_CH3_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,13,3);
#endif // UMCTL2_PORT_CH3_13

#ifdef UMCTL2_PORT_CH4_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,13,4);
#endif // UMCTL2_PORT_CH4_13

#ifdef UMCTL2_PORT_CH5_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,13,5);
#endif // UMCTL2_PORT_CH5_13

#ifdef UMCTL2_PORT_CH6_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,13,6);
#endif // UMCTL2_PORT_CH6_13

#ifdef UMCTL2_PORT_CH7_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,13,7);
#endif // UMCTL2_PORT_CH7_13

#ifdef UMCTL2_PORT_CH8_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,13,8);
#endif // UMCTL2_PORT_CH8_13

#ifdef UMCTL2_PORT_CH9_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,13,9);
#endif // UMCTL2_PORT_CH9_13

#ifdef UMCTL2_PORT_CH10_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,13,10);
#endif // UMCTL2_PORT_CH10_13

#ifdef UMCTL2_PORT_CH11_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,13,11);
#endif // UMCTL2_PORT_CH11_13

#ifdef UMCTL2_PORT_CH12_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,13,12);
#endif // UMCTL2_PORT_CH12_13
  
#ifdef UMCTL2_PORT_CH13_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,13,13);
#endif // UMCTL2_PORT_CH13_13


#ifdef UMCTL2_PORT_CH14_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,13,14);
#endif // UMCTL2_PORT_CH14_13
#ifdef UMCTL2_PORT_CH15_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,13,15);
#endif // UMCTL2_PORT_CH15_13

////PORT_14/////  

 #ifdef UMCTL2_PORT_CH0_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,14,0);
#endif // UMCTL2_PORT_CH0_14

 #ifdef UMCTL2_PORT_CH1_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,14,1);
#endif // UMCTL2_PORT_CH1_14

#ifdef UMCTL2_PORT_CH2_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,14,2);
#endif // UMCTL2_PORT_CH2_14
 
#ifdef UMCTL2_PORT_CH3_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,14,3);
#endif // UMCTL2_PORT_CH3_14

#ifdef UMCTL2_PORT_CH4_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,14,4);
#endif // UMCTL2_PORT_CH4_14

#ifdef UMCTL2_PORT_CH5_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,14,5);
#endif // UMCTL2_PORT_CH5_14

#ifdef UMCTL2_PORT_CH6_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,14,6);
#endif // UMCTL2_PORT_CH6_14

#ifdef UMCTL2_PORT_CH7_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,14,7);
#endif // UMCTL2_PORT_CH7_14

#ifdef UMCTL2_PORT_CH8_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,14,8);
#endif // UMCTL2_PORT_CH8_14

#ifdef UMCTL2_PORT_CH9_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,14,9);
#endif // UMCTL2_PORT_CH9_14

#ifdef UMCTL2_PORT_CH10_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,14,10);
#endif // UMCTL2_PORT_CH10_14

#ifdef UMCTL2_PORT_CH11_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,14,11);
#endif // UMCTL2_PORT_CH11_14

#ifdef UMCTL2_PORT_CH12_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,14,12);
#endif // UMCTL2_PORT_CH12_14
  
#ifdef UMCTL2_PORT_CH13_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,14,13);
#endif // UMCTL2_PORT_CH13_14


#ifdef UMCTL2_PORT_CH14_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,14,14);
#endif // UMCTL2_PORT_CH14_14
#ifdef UMCTL2_PORT_CH15_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,14,15);
#endif // UMCTL2_PORT_CH15_14

////PORT_15///////

   #ifdef UMCTL2_PORT_CH0_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH0,id_mask,15,0);
#endif // UMCTL2_PORT_CH0_15

 #ifdef UMCTL2_PORT_CH1_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH1,id_mask,15,1);
#endif // UMCTL2_PORT_CH1_15

#ifdef UMCTL2_PORT_CH2_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH2,id_mask,15,2);
#endif // UMCTL2_PORT_CH2_15
 
#ifdef UMCTL2_PORT_CH3_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH3,id_mask,15,3);
#endif // UMCTL2_PORT_CH3_15

#ifdef UMCTL2_PORT_CH4_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH4,id_mask,15,4);
#endif // UMCTL2_PORT_CH4_15

#ifdef UMCTL2_PORT_CH5_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH5,id_mask,15,5);
#endif // UMCTL2_PORT_CH5_15

#ifdef UMCTL2_PORT_CH6_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH6,id_mask,15,6);
#endif // UMCTL2_PORT_CH6_15

#ifdef UMCTL2_PORT_CH7_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH7,id_mask,15,7);
#endif // UMCTL2_PORT_CH7_15

#ifdef UMCTL2_PORT_CH8_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH8,id_mask,15,8);
#endif // UMCTL2_PORT_CH8_15

#ifdef UMCTL2_PORT_CH9_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH9,id_mask,15,9);
#endif // UMCTL2_PORT_CH9_15

#ifdef UMCTL2_PORT_CH10_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH10,id_mask,15,10);
#endif // UMCTL2_PORT_CH10_15

#ifdef UMCTL2_PORT_CH11_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH11,id_mask,15,11);
#endif // UMCTL2_PORT_CH11_15

#ifdef UMCTL2_PORT_CH12_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH12,id_mask,15,12);
#endif // UMCTL2_PORT_CH12_15
  
#ifdef UMCTL2_PORT_CH13_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH13,id_mask,15,13);
#endif // UMCTL2_PORT_CH13_15


#ifdef UMCTL2_PORT_CH14_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH14,id_mask,15,14);
#endif // UMCTL2_PORT_CH14_15
#ifdef UMCTL2_PORT_CH15_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDMASKCH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDMASKCH15,id_mask,15,15);
#endif // UMCTL2_PORT_CH15_15
#endif // UMCTL2_PORT_CH0_0
}

void cinit_prgm_PCFGIDVALUECH(SubsysHdlr_t *hdlr,uint32_t port) {
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  TRACE();

#ifdef UMCTL2_PORT_CH0_0
  DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, PCFGIDVALUECH0, PORT) *reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(0, REGB_ARB, PCFGIDVALUECH0, PORT); 
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,0,0);

#ifdef UMCTL2_PORT_CH1_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,0,1);
#endif // UMCTL2_PORT_CH1_0

#ifdef UMCTL2_PORT_CH2_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,0,2);
#endif // UMCTL2_PORT_CH2_0
 
#ifdef UMCTL2_PORT_CH3_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,0,3);
#endif // UMCTL2_PORT_CH3_0

#ifdef UMCTL2_PORT_CH4_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,0,4);
#endif // UMCTL2_PORT_CH4_0

#ifdef UMCTL2_PORT_CH5_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,0,5);
#endif // UMCTL2_PORT_CH5_0

#ifdef UMCTL2_PORT_CH6_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,0,6);
#endif // UMCTL2_PORT_CH6_0

#ifdef UMCTL2_PORT_CH7_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,0,7);
#endif // UMCTL2_PORT_CH7_0

#ifdef UMCTL2_PORT_CH8_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,0,8);
#endif // UMCTL2_PORT_CH8_0

#ifdef UMCTL2_PORT_CH9_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,0,9);
#endif // UMCTL2_PORT_CH9_0

#ifdef UMCTL2_PORT_CH10_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,0,10);
#endif // UMCTL2_PORT_CH10_0

#ifdef UMCTL2_PORT_CH11_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,0,11);
#endif // UMCTL2_PORT_CH11_0

#ifdef UMCTL2_PORT_CH12_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,0,12);
#endif // UMCTL2_PORT_CH12_0
  
#ifdef UMCTL2_PORT_CH13_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,0,13);
#endif // UMCTL2_PORT_CH13_0


#ifdef UMCTL2_PORT_CH14_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,0,14);
#endif // UMCTL2_PORT_CH14_0
#ifdef UMCTL2_PORT_CH15_0
  DWC_DDRCTL_GET_MP_REG_PTR(0,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,0,15);
#endif // UMCTL2_PORT_CH15_0


////////////PORT_1//////////////////////////////

#ifdef UMCTL2_PORT_CH0_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,1,0);
#endif // UMCTL2_PORT_CH0_1

 #ifdef UMCTL2_PORT_CH1_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,1,1);
#endif // UMCTL2_PORT_CH1_1

#ifdef UMCTL2_PORT_CH2_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,1,2);
#endif // UMCTL2_PORT_CH2_1
 
#ifdef UMCTL2_PORT_CH3_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,1,3);
#endif // UMCTL2_PORT_CH3_1

#ifdef UMCTL2_PORT_CH4_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,1,4);
#endif // UMCTL2_PORT_CH4_1

#ifdef UMCTL2_PORT_CH5_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,1,5);
#endif // UMCTL2_PORT_CH5_1

#ifdef UMCTL2_PORT_CH6_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,1,6);
#endif // UMCTL2_PORT_CH6_1

#ifdef UMCTL2_PORT_CH7_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,1,7);
#endif // UMCTL2_PORT_CH7_1

#ifdef UMCTL2_PORT_CH8_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,1,8);
#endif // UMCTL2_PORT_CH8_1

#ifdef UMCTL2_PORT_CH9_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,1,9);
#endif // UMCTL2_PORT_CH9_1

#ifdef UMCTL2_PORT_CH10_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,1,10);
#endif // UMCTL2_PORT_CH10_1

#ifdef UMCTL2_PORT_CH11_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,1,11);
#endif // UMCTL2_PORT_CH11_1

#ifdef UMCTL2_PORT_CH12_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,1,12);
#endif // UMCTL2_PORT_CH12_1
  
#ifdef UMCTL2_PORT_CH13_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,1,13);
#endif // UMCTL2_PORT_CH13_1


#ifdef UMCTL2_PORT_CH14_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,1,14);
#endif // UMCTL2_PORT_CH14_1
#ifdef UMCTL2_PORT_CH15_1
  DWC_DDRCTL_GET_MP_REG_PTR(1,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,1,15);
#endif // UMCTL2_PORT_CH15_1


///////////////PORT_2//////////////////////

  #ifdef UMCTL2_PORT_CH0_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,2,0);
#endif // UMCTL2_PORT_CH0_2

 #ifdef UMCTL2_PORT_CH1_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,2,1);
#endif // UMCTL2_PORT_CH1_2

#ifdef UMCTL2_PORT_CH2_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,2,2);
#endif // UMCTL2_PORT_CH2_2
 
#ifdef UMCTL2_PORT_CH3_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,2,3);
#endif // UMCTL2_PORT_CH3_2

#ifdef UMCTL2_PORT_CH4_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,2,4);
#endif // UMCTL2_PORT_CH4_2

#ifdef UMCTL2_PORT_CH5_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,2,5);
#endif // UMCTL2_PORT_CH5_2

#ifdef UMCTL2_PORT_CH6_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,2,6);
#endif // UMCTL2_PORT_CH6_2

#ifdef UMCTL2_PORT_CH7_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,2,7);
#endif // UMCTL2_PORT_CH7_2

#ifdef UMCTL2_PORT_CH8_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,2,8);
#endif // UMCTL2_PORT_CH8_2

#ifdef UMCTL2_PORT_CH9_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,2,9);
#endif // UMCTL2_PORT_CH9_2

#ifdef UMCTL2_PORT_CH10_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,2,10);
#endif // UMCTL2_PORT_CH10_2

#ifdef UMCTL2_PORT_CH11_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,2,11);
#endif // UMCTL2_PORT_CH11_2

#ifdef UMCTL2_PORT_CH12_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,2,12);
#endif // UMCTL2_PORT_CH12_2
  
#ifdef UMCTL2_PORT_CH13_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,2,13);
#endif // UMCTL2_PORT_CH13_2


#ifdef UMCTL2_PORT_CH14_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,2,14);
#endif // UMCTL2_PORT_CH14_2
#ifdef UMCTL2_PORT_CH15_2
  DWC_DDRCTL_GET_MP_REG_PTR(2,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,2,15);
#endif // UMCTL2_PORT_CH15_2

/////PORT3//////////////////

 #ifdef UMCTL2_PORT_CH0_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,3,0);
#endif // UMCTL2_PORT_CH0_3

 #ifdef UMCTL2_PORT_CH1_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,3,1);
#endif // UMCTL2_PORT_CH1_3

#ifdef UMCTL2_PORT_CH2_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,3,2);
#endif // UMCTL2_PORT_CH2_3
 
#ifdef UMCTL2_PORT_CH3_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,3,3);
#endif // UMCTL2_PORT_CH3_3

#ifdef UMCTL2_PORT_CH4_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,3,4);
#endif // UMCTL2_PORT_CH4_3

#ifdef UMCTL2_PORT_CH5_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,3,5);
#endif // UMCTL2_PORT_CH5_3

#ifdef UMCTL2_PORT_CH6_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,3,6);
#endif // UMCTL2_PORT_CH6_3

#ifdef UMCTL2_PORT_CH7_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,3,7);
#endif // UMCTL2_PORT_CH7_3

#ifdef UMCTL2_PORT_CH8_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,3,8);
#endif // UMCTL2_PORT_CH8_3

#ifdef UMCTL2_PORT_CH9_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,3,9);
#endif // UMCTL2_PORT_CH9_3

#ifdef UMCTL2_PORT_CH10_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,3,10);
#endif // UMCTL2_PORT_CH10_3

#ifdef UMCTL2_PORT_CH11_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,3,11);
#endif // UMCTL2_PORT_CH11_3

#ifdef UMCTL2_PORT_CH12_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,3,12);
#endif // UMCTL2_PORT_CH12_3
  
#ifdef UMCTL2_PORT_CH13_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,3,13);
#endif // UMCTL2_PORT_CH13_3


#ifdef UMCTL2_PORT_CH14_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,3,14);
#endif // UMCTL2_PORT_CH14_3
#ifdef UMCTL2_PORT_CH15_3
  DWC_DDRCTL_GET_MP_REG_PTR(3,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,3,15);
#endif // UMCTL2_PORT_CH15_3


///////PORT_4/////////

 #ifdef UMCTL2_PORT_CH0_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,4,0);
#endif // UMCTL2_PORT_CH0_4

 #ifdef UMCTL2_PORT_CH1_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,4,1);
#endif // UMCTL2_PORT_CH1_4

#ifdef UMCTL2_PORT_CH2_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,4,2);
#endif // UMCTL2_PORT_CH2_4
 
#ifdef UMCTL2_PORT_CH3_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,4,3);
#endif // UMCTL2_PORT_CH3_4

#ifdef UMCTL2_PORT_CH4_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,4,4);
#endif // UMCTL2_PORT_CH4_4

#ifdef UMCTL2_PORT_CH5_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,4,5);
#endif // UMCTL2_PORT_CH5_4

#ifdef UMCTL2_PORT_CH6_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,4,6);
#endif // UMCTL2_PORT_CH6_4

#ifdef UMCTL2_PORT_CH7_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,4,7);
#endif // UMCTL2_PORT_CH7_4

#ifdef UMCTL2_PORT_CH8_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,4,8);
#endif // UMCTL2_PORT_CH8_4

#ifdef UMCTL2_PORT_CH9_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,4,9);
#endif // UMCTL2_PORT_CH9_4

#ifdef UMCTL2_PORT_CH10_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,4,10);
#endif // UMCTL2_PORT_CH10_4

#ifdef UMCTL2_PORT_CH11_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,4,11);
#endif // UMCTL2_PORT_CH11_4

#ifdef UMCTL2_PORT_CH12_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,4,12);
#endif // UMCTL2_PORT_CH12_4
  
#ifdef UMCTL2_PORT_CH13_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,4,13);
#endif // UMCTL2_PORT_CH13_4


#ifdef UMCTL2_PORT_CH14_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,4,14);
#endif // UMCTL2_PORT_CH14_4
#ifdef UMCTL2_PORT_CH15_4
  DWC_DDRCTL_GET_MP_REG_PTR(4,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,4,15);
#endif // UMCTL2_PORT_CH15_4


////////PORT_5/////////

 #ifdef UMCTL2_PORT_CH0_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,5,0);
#endif // UMCTL2_PORT_CH0_5

 #ifdef UMCTL2_PORT_CH1_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,5,1);
#endif // UMCTL2_PORT_CH1_5

#ifdef UMCTL2_PORT_CH2_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,5,2);
#endif // UMCTL2_PORT_CH2_5
 
#ifdef UMCTL2_PORT_CH3_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,5,3);
#endif // UMCTL2_PORT_CH3_5

#ifdef UMCTL2_PORT_CH4_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,5,4);
#endif // UMCTL2_PORT_CH4_5

#ifdef UMCTL2_PORT_CH5_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,5,5);
#endif // UMCTL2_PORT_CH5_5

#ifdef UMCTL2_PORT_CH6_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,5,6);
#endif // UMCTL2_PORT_CH6_5

#ifdef UMCTL2_PORT_CH7_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,5,7);
#endif // UMCTL2_PORT_CH7_5

#ifdef UMCTL2_PORT_CH8_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,5,8);
#endif // UMCTL2_PORT_CH8_5

#ifdef UMCTL2_PORT_CH9_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,5,9);
#endif // UMCTL2_PORT_CH9_5

#ifdef UMCTL2_PORT_CH10_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,5,10);
#endif // UMCTL2_PORT_CH10_5

#ifdef UMCTL2_PORT_CH11_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,5,11);
#endif // UMCTL2_PORT_CH11_5

#ifdef UMCTL2_PORT_CH12_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,5,12);
#endif // UMCTL2_PORT_CH12_5
  
#ifdef UMCTL2_PORT_CH13_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,5,13);
#endif // UMCTL2_PORT_CH13_5


#ifdef UMCTL2_PORT_CH14_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,5,14);
#endif // UMCTL2_PORT_CH14_5
#ifdef UMCTL2_PORT_CH15_5
  DWC_DDRCTL_GET_MP_REG_PTR(5,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,5,15);
#endif // UMCTL2_PORT_CH15_5


/////PORT_6////////////////////////

 #ifdef UMCTL2_PORT_CH0_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,6,0);
#endif // UMCTL2_PORT_CH0_6

 #ifdef UMCTL2_PORT_CH1_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,6,1);
#endif // UMCTL2_PORT_CH1_6

#ifdef UMCTL2_PORT_CH2_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,6,2);
#endif // UMCTL2_PORT_CH2_6
 
#ifdef UMCTL2_PORT_CH3_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,6,3);
#endif // UMCTL2_PORT_CH3_6

#ifdef UMCTL2_PORT_CH4_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,6,4);
#endif // UMCTL2_PORT_CH4_6

#ifdef UMCTL2_PORT_CH5_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,6,5);
#endif // UMCTL2_PORT_CH5_6

#ifdef UMCTL2_PORT_CH6_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,6,6);
#endif // UMCTL2_PORT_CH6_6

#ifdef UMCTL2_PORT_CH7_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,6,7);
#endif // UMCTL2_PORT_CH7_6

#ifdef UMCTL2_PORT_CH8_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,6,8);
#endif // UMCTL2_PORT_CH8_6

#ifdef UMCTL2_PORT_CH9_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,6,9);
#endif // UMCTL2_PORT_CH9_6

#ifdef UMCTL2_PORT_CH10_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,6,10);
#endif // UMCTL2_PORT_CH10_6

#ifdef UMCTL2_PORT_CH11_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,6,11);
#endif // UMCTL2_PORT_CH11_6

#ifdef UMCTL2_PORT_CH12_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,6,12);
#endif // UMCTL2_PORT_CH12_6
  
#ifdef UMCTL2_PORT_CH13_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,6,13);
#endif // UMCTL2_PORT_CH13_6


#ifdef UMCTL2_PORT_CH14_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,6,14);
#endif // UMCTL2_PORT_CH14_6
#ifdef UMCTL2_PORT_CH15_6
  DWC_DDRCTL_GET_MP_REG_PTR(6,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,6,15);
#endif // UMCTL2_PORT_CH15_6

////PORT_7///////

 #ifdef UMCTL2_PORT_CH0_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,7,0);
#endif // UMCTL2_PORT_CH0_7

 #ifdef UMCTL2_PORT_CH1_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,7,1);
#endif // UMCTL2_PORT_CH1_7

#ifdef UMCTL2_PORT_CH2_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,7,2);
#endif // UMCTL2_PORT_CH2_7
 
#ifdef UMCTL2_PORT_CH3_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,7,3);
#endif // UMCTL2_PORT_CH3_7

#ifdef UMCTL2_PORT_CH4_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,7,4);
#endif // UMCTL2_PORT_CH4_7

#ifdef UMCTL2_PORT_CH5_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,7,5);
#endif // UMCTL2_PORT_CH5_7

#ifdef UMCTL2_PORT_CH6_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,7,6);
#endif // UMCTL2_PORT_CH6_7

#ifdef UMCTL2_PORT_CH7_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,7,7);
#endif // UMCTL2_PORT_CH7_7

#ifdef UMCTL2_PORT_CH8_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,7,8);
#endif // UMCTL2_PORT_CH8_7

#ifdef UMCTL2_PORT_CH9_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,7,9);
#endif // UMCTL2_PORT_CH9_7

#ifdef UMCTL2_PORT_CH10_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,7,10);
#endif // UMCTL2_PORT_CH10_7

#ifdef UMCTL2_PORT_CH11_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,7,11);
#endif // UMCTL2_PORT_CH11_7

#ifdef UMCTL2_PORT_CH12_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,7,12);
#endif // UMCTL2_PORT_CH12_7
  
#ifdef UMCTL2_PORT_CH13_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,7,13);
#endif // UMCTL2_PORT_CH13_7


#ifdef UMCTL2_PORT_CH14_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,7,14);
#endif // UMCTL2_PORT_CH14_7
#ifdef UMCTL2_PORT_CH15_7
  DWC_DDRCTL_GET_MP_REG_PTR(7,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,7,15);
#endif // UMCTL2_PORT_CH15_7

  ////PORT_8

 #ifdef UMCTL2_PORT_CH0_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,8,0);
#endif // UMCTL2_PORT_CH0_8

 #ifdef UMCTL2_PORT_CH1_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,8,1);
#endif // UMCTL2_PORT_CH1_8

#ifdef UMCTL2_PORT_CH2_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,8,2);
#endif // UMCTL2_PORT_CH2_8
 
#ifdef UMCTL2_PORT_CH3_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,8,3);
#endif // UMCTL2_PORT_CH3_8

#ifdef UMCTL2_PORT_CH4_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,8,4);
#endif // UMCTL2_PORT_CH4_8

#ifdef UMCTL2_PORT_CH5_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,8,5);
#endif // UMCTL2_PORT_CH5_8

#ifdef UMCTL2_PORT_CH6_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,8,6);
#endif // UMCTL2_PORT_CH6_8

#ifdef UMCTL2_PORT_CH7_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,8,7);
#endif // UMCTL2_PORT_CH7_8

#ifdef UMCTL2_PORT_CH8_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,8,8);
#endif // UMCTL2_PORT_CH8_8

#ifdef UMCTL2_PORT_CH9_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,8,9);
#endif // UMCTL2_PORT_CH9_8

#ifdef UMCTL2_PORT_CH10_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,8,10);
#endif // UMCTL2_PORT_CH10_8

#ifdef UMCTL2_PORT_CH11_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,8,11);
#endif // UMCTL2_PORT_CH11_8

#ifdef UMCTL2_PORT_CH12_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,8,12);
#endif // UMCTL2_PORT_CH12_8
  
#ifdef UMCTL2_PORT_CH13_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,8,13);
#endif // UMCTL2_PORT_CH13_8


#ifdef UMCTL2_PORT_CH14_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,8,14);
#endif // UMCTL2_PORT_CH14_8
#ifdef UMCTL2_PORT_CH15_8
  DWC_DDRCTL_GET_MP_REG_PTR(8,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,8,15);
#endif // UMCTL2_PORT_CH15_8

//PORT_9///

 #ifdef UMCTL2_PORT_CH0_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,9,0);
#endif // UMCTL2_PORT_CH0_9

 #ifdef UMCTL2_PORT_CH1_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,9,1);
#endif // UMCTL2_PORT_CH1_9

#ifdef UMCTL2_PORT_CH2_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,9,2);
#endif // UMCTL2_PORT_CH2_9
 
#ifdef UMCTL2_PORT_CH3_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,9,3);
#endif // UMCTL2_PORT_CH3_9

#ifdef UMCTL2_PORT_CH4_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,9,4);
#endif // UMCTL2_PORT_CH4_9

#ifdef UMCTL2_PORT_CH5_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,9,5);
#endif // UMCTL2_PORT_CH5_9

#ifdef UMCTL2_PORT_CH6_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,9,6);
#endif // UMCTL2_PORT_CH6_9

#ifdef UMCTL2_PORT_CH7_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,9,7);
#endif // UMCTL2_PORT_CH7_9

#ifdef UMCTL2_PORT_CH8_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,9,8);
#endif // UMCTL2_PORT_CH8_9

#ifdef UMCTL2_PORT_CH9_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,9,9);
#endif // UMCTL2_PORT_CH9_9

#ifdef UMCTL2_PORT_CH10_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,9,10);
#endif // UMCTL2_PORT_CH10_9

#ifdef UMCTL2_PORT_CH11_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,9,11);
#endif // UMCTL2_PORT_CH11_9

#ifdef UMCTL2_PORT_CH12_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,9,12);
#endif // UMCTL2_PORT_CH12_9
  
#ifdef UMCTL2_PORT_CH13_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,9,13);
#endif // UMCTL2_PORT_CH13_9


#ifdef UMCTL2_PORT_CH14_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,9,14);
#endif // UMCTL2_PORT_CH14_9
#ifdef UMCTL2_PORT_CH15_9
  DWC_DDRCTL_GET_MP_REG_PTR(9,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,9,15);
#endif // UMCTL2_PORT_CH15_9

  ////PORT_10/////
  
 #ifdef UMCTL2_PORT_CH0_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,10,0);
#endif // UMCTL2_PORT_CH0_10

 #ifdef UMCTL2_PORT_CH1_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,10,1);
#endif // UMCTL2_PORT_CH1_10

#ifdef UMCTL2_PORT_CH2_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,10,2);
#endif // UMCTL2_PORT_CH2_10
 
#ifdef UMCTL2_PORT_CH3_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,10,3);
#endif // UMCTL2_PORT_CH3_10

#ifdef UMCTL2_PORT_CH4_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,10,4);
#endif // UMCTL2_PORT_CH4_10

#ifdef UMCTL2_PORT_CH5_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,10,5);
#endif // UMCTL2_PORT_CH5_10

#ifdef UMCTL2_PORT_CH6_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,10,6);
#endif // UMCTL2_PORT_CH6_10

#ifdef UMCTL2_PORT_CH7_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,10,7);
#endif // UMCTL2_PORT_CH7_10

#ifdef UMCTL2_PORT_CH8_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,10,8);
#endif // UMCTL2_PORT_CH8_10

#ifdef UMCTL2_PORT_CH9_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,10,9);
#endif // UMCTL2_PORT_CH9_10

#ifdef UMCTL2_PORT_CH10_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,10,10);
#endif // UMCTL2_PORT_CH10_10

#ifdef UMCTL2_PORT_CH11_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,10,11);
#endif // UMCTL2_PORT_CH11_10

#ifdef UMCTL2_PORT_CH12_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,10,12);
#endif // UMCTL2_PORT_CH12_10
  
#ifdef UMCTL2_PORT_CH13_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,10,13);
#endif // UMCTL2_PORT_CH13_10


#ifdef UMCTL2_PORT_CH14_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,10,14);
#endif // UMCTL2_PORT_CH14_10
#ifdef UMCTL2_PORT_CH15_10
  DWC_DDRCTL_GET_MP_REG_PTR(10,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,10,15);
#endif // UMCTL2_PORT_CH15_10

 //PORT_11// 

 #ifdef UMCTL2_PORT_CH0_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,11,0);
#endif // UMCTL2_PORT_CH0_11

 #ifdef UMCTL2_PORT_CH1_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,11,1);
#endif // UMCTL2_PORT_CH1_11

#ifdef UMCTL2_PORT_CH2_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,11,2);
#endif // UMCTL2_PORT_CH2_11
 
#ifdef UMCTL2_PORT_CH3_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,11,3);
#endif // UMCTL2_PORT_CH3_11

#ifdef UMCTL2_PORT_CH4_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,11,4);
#endif // UMCTL2_PORT_CH4_11

#ifdef UMCTL2_PORT_CH5_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,11,5);
#endif // UMCTL2_PORT_CH5_11

#ifdef UMCTL2_PORT_CH6_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,11,6);
#endif // UMCTL2_PORT_CH6_11

#ifdef UMCTL2_PORT_CH7_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,11,7);
#endif // UMCTL2_PORT_CH7_11

#ifdef UMCTL2_PORT_CH8_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,11,8);
#endif // UMCTL2_PORT_CH8_11

#ifdef UMCTL2_PORT_CH9_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,11,9);
#endif // UMCTL2_PORT_CH9_11

#ifdef UMCTL2_PORT_CH10_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,11,10);
#endif // UMCTL2_PORT_CH10_11

#ifdef UMCTL2_PORT_CH11_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,11,11);
#endif // UMCTL2_PORT_CH11_11

#ifdef UMCTL2_PORT_CH12_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,11,12);
#endif // UMCTL2_PORT_CH12_11
  
#ifdef UMCTL2_PORT_CH13_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,11,13);
#endif // UMCTL2_PORT_CH13_11


#ifdef UMCTL2_PORT_CH14_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,11,14);
#endif // UMCTL2_PORT_CH14_11
#ifdef UMCTL2_PORT_CH15_11
  DWC_DDRCTL_GET_MP_REG_PTR(11,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,11,15);
#endif // UMCTL2_PORT_CH15_11

////PORT_12/////

 #ifdef UMCTL2_PORT_CH0_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,12,0);
#endif // UMCTL2_PORT_CH0_12

 #ifdef UMCTL2_PORT_CH1_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,12,1);
#endif // UMCTL2_PORT_CH1_12

#ifdef UMCTL2_PORT_CH2_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,12,2);
#endif // UMCTL2_PORT_CH2_12
 
#ifdef UMCTL2_PORT_CH3_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,12,3);
#endif // UMCTL2_PORT_CH3_12

#ifdef UMCTL2_PORT_CH4_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,12,4);
#endif // UMCTL2_PORT_CH4_12

#ifdef UMCTL2_PORT_CH5_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,12,5);
#endif // UMCTL2_PORT_CH5_12

#ifdef UMCTL2_PORT_CH6_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,12,6);
#endif // UMCTL2_PORT_CH6_12

#ifdef UMCTL2_PORT_CH7_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,12,7);
#endif // UMCTL2_PORT_CH7_12

#ifdef UMCTL2_PORT_CH8_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,12,8);
#endif // UMCTL2_PORT_CH8_12

#ifdef UMCTL2_PORT_CH9_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,12,9);
#endif // UMCTL2_PORT_CH9_12

#ifdef UMCTL2_PORT_CH10_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,12,10);
#endif // UMCTL2_PORT_CH10_12

#ifdef UMCTL2_PORT_CH11_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,12,11);
#endif // UMCTL2_PORT_CH11_12

#ifdef UMCTL2_PORT_CH12_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,12,12);
#endif // UMCTL2_PORT_CH12_12
  
#ifdef UMCTL2_PORT_CH13_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,12,13);
#endif // UMCTL2_PORT_CH13_12


#ifdef UMCTL2_PORT_CH14_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,12,14);
#endif // UMCTL2_PORT_CH14_12
#ifdef UMCTL2_PORT_CH15_12
  DWC_DDRCTL_GET_MP_REG_PTR(12,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,12,15);
#endif // UMCTL2_PORT_CH15_12

 ////PORT_13 

 #ifdef UMCTL2_PORT_CH0_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,13,0);
#endif // UMCTL2_PORT_CH0_13

 #ifdef UMCTL2_PORT_CH1_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,13,1);
#endif // UMCTL2_PORT_CH1_13

#ifdef UMCTL2_PORT_CH2_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,13,2);
#endif // UMCTL2_PORT_CH2_13
 
#ifdef UMCTL2_PORT_CH3_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,13,3);
#endif // UMCTL2_PORT_CH3_13

#ifdef UMCTL2_PORT_CH4_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,13,4);
#endif // UMCTL2_PORT_CH4_13

#ifdef UMCTL2_PORT_CH5_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,13,5);
#endif // UMCTL2_PORT_CH5_13

#ifdef UMCTL2_PORT_CH6_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,13,6);
#endif // UMCTL2_PORT_CH6_13

#ifdef UMCTL2_PORT_CH7_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,13,7);
#endif // UMCTL2_PORT_CH7_13

#ifdef UMCTL2_PORT_CH8_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,13,8);
#endif // UMCTL2_PORT_CH8_13

#ifdef UMCTL2_PORT_CH9_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,13,9);
#endif // UMCTL2_PORT_CH9_13

#ifdef UMCTL2_PORT_CH10_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,13,10);
#endif // UMCTL2_PORT_CH10_13

#ifdef UMCTL2_PORT_CH11_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,13,11);
#endif // UMCTL2_PORT_CH11_13

#ifdef UMCTL2_PORT_CH12_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,13,12);
#endif // UMCTL2_PORT_CH12_13
  
#ifdef UMCTL2_PORT_CH13_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,13,13);
#endif // UMCTL2_PORT_CH13_13


#ifdef UMCTL2_PORT_CH14_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,13,14);
#endif // UMCTL2_PORT_CH14_13
#ifdef UMCTL2_PORT_CH15_13
  DWC_DDRCTL_GET_MP_REG_PTR(13,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,13,15);
#endif // UMCTL2_PORT_CH15_13

////PORT_14/////  

 #ifdef UMCTL2_PORT_CH0_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,14,0);
#endif // UMCTL2_PORT_CH0_14

 #ifdef UMCTL2_PORT_CH1_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,14,1);
#endif // UMCTL2_PORT_CH1_14

#ifdef UMCTL2_PORT_CH2_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,14,2);
#endif // UMCTL2_PORT_CH2_14
 
#ifdef UMCTL2_PORT_CH3_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,14,3);
#endif // UMCTL2_PORT_CH3_14

#ifdef UMCTL2_PORT_CH4_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,14,4);
#endif // UMCTL2_PORT_CH4_14

#ifdef UMCTL2_PORT_CH5_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,14,5);
#endif // UMCTL2_PORT_CH5_14

#ifdef UMCTL2_PORT_CH6_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,14,6);
#endif // UMCTL2_PORT_CH6_14

#ifdef UMCTL2_PORT_CH7_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,14,7);
#endif // UMCTL2_PORT_CH7_14

#ifdef UMCTL2_PORT_CH8_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,14,8);
#endif // UMCTL2_PORT_CH8_14

#ifdef UMCTL2_PORT_CH9_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,14,9);
#endif // UMCTL2_PORT_CH9_14

#ifdef UMCTL2_PORT_CH10_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,14,10);
#endif // UMCTL2_PORT_CH10_14

#ifdef UMCTL2_PORT_CH11_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,14,11);
#endif // UMCTL2_PORT_CH11_14

#ifdef UMCTL2_PORT_CH12_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,14,12);
#endif // UMCTL2_PORT_CH12_14
  
#ifdef UMCTL2_PORT_CH13_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,14,13);
#endif // UMCTL2_PORT_CH13_14


#ifdef UMCTL2_PORT_CH14_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,14,14);
#endif // UMCTL2_PORT_CH14_14
#ifdef UMCTL2_PORT_CH15_14
  DWC_DDRCTL_GET_MP_REG_PTR(14,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,14,15);
#endif // UMCTL2_PORT_CH15_14

////PORT_15///////

   #ifdef UMCTL2_PORT_CH0_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH0,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH0,id_value,15,0);
#endif // UMCTL2_PORT_CH0_15

 #ifdef UMCTL2_PORT_CH1_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH1,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH1,id_value,15,1);
#endif // UMCTL2_PORT_CH1_15

#ifdef UMCTL2_PORT_CH2_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH2,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH2,id_value,15,2);
#endif // UMCTL2_PORT_CH2_15
 
#ifdef UMCTL2_PORT_CH3_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH3,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH3,id_value,15,3);
#endif // UMCTL2_PORT_CH3_15

#ifdef UMCTL2_PORT_CH4_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH4,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH4,id_value,15,4);
#endif // UMCTL2_PORT_CH4_15

#ifdef UMCTL2_PORT_CH5_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH5,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH5,id_value,15,5);
#endif // UMCTL2_PORT_CH5_15

#ifdef UMCTL2_PORT_CH6_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH6,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH6,id_value,15,6);
#endif // UMCTL2_PORT_CH6_15

#ifdef UMCTL2_PORT_CH7_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH7,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH7,id_value,15,7);
#endif // UMCTL2_PORT_CH7_15

#ifdef UMCTL2_PORT_CH8_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH8,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH8,id_value,15,8);
#endif // UMCTL2_PORT_CH8_15

#ifdef UMCTL2_PORT_CH9_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH9,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH9,id_value,15,9);
#endif // UMCTL2_PORT_CH9_15

#ifdef UMCTL2_PORT_CH10_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH10,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH10,id_value,15,10);
#endif // UMCTL2_PORT_CH10_15

#ifdef UMCTL2_PORT_CH11_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH11,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH11,id_value,15,11);
#endif // UMCTL2_PORT_CH11_15

#ifdef UMCTL2_PORT_CH12_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH12,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH12,id_value,15,12);
#endif // UMCTL2_PORT_CH12_15
  
#ifdef UMCTL2_PORT_CH13_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH13,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH13,id_value,15,13);
#endif // UMCTL2_PORT_CH13_15


#ifdef UMCTL2_PORT_CH14_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH14,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH14,id_value,15,14);
#endif // UMCTL2_PORT_CH14_15
#ifdef UMCTL2_PORT_CH15_15
  DWC_DDRCTL_GET_MP_REG_PTR(15,PCFGIDVALUECH15,PORT);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PCFGIDVALUECH15,id_value,15,15);
#endif // UMCTL2_PORT_CH15_15
#endif // UMCTL2_PORT_CH0_0
}

void cinit_prgm_SBRSTART0(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_SBR_EN_1
  TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRSTART0_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRSTART0_reg;
 
  APPLY_CFG_TO_REGFIELD(dyn,SBRSTART0,sbr_address_start_mask_0);
  LOG_MESSAGE(hdlr, 1, ("SBRSTART0= 0x%x\n",reg->value));
#endif  
}

void cinit_prgm_SBRSTART1(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_SBR_EN_1
  TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRSTART1_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRSTART1_reg;
 
  APPLY_CFG_TO_REGFIELD(dyn,SBRSTART1,sbr_address_start_mask_1);
  LOG_MESSAGE(hdlr, 1, ("SBRSTART1= 0x%x\n",reg->value));
#endif  
}

void cinit_prgm_SBRRANGE0(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_SBR_EN_1
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRRANGE0_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRRANGE0_reg;
 
  APPLY_CFG_TO_REGFIELD(dyn,SBRRANGE0,sbr_address_range_mask_0);

  LOG_MESSAGE(hdlr, 1, ("SBRRANGE0= 0x%x\n",reg->value));
#endif  
}

void cinit_prgm_SBRRANGE1(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_SBR_EN_1
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRRANGE1_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRRANGE1_reg;
 
  APPLY_CFG_TO_REGFIELD(dyn,SBRRANGE1,sbr_address_range_mask_1);

  LOG_MESSAGE(hdlr, 1, ("SBRRANGE1= 0x%x\n",reg->value));
#endif  
}

void cinit_prgm_SBRSTART0DCH1(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_SBR_EN_1 
#ifdef UMCTL2_DUAL_DATA_CHANNEL
  TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRSTART0DCH1_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRSTART0DCH1_reg;

  APPLY_CFG_TO_REGFIELD(dyn,SBRSTART0DCH1,sbr_address_start_mask_dch1_0);
  LOG_MESSAGE(hdlr, 1, ("SBRSTART0DCH1= 0x%x\n",reg->value));
#endif  
#endif  
}

void cinit_prgm_SBRSTART1DCH1(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_SBR_EN_1 
#ifdef UMCTL2_DUAL_DATA_CHANNEL
  TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRSTART1DCH1_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRSTART1DCH1_reg;
 
  APPLY_CFG_TO_REGFIELD(dyn,SBRSTART1DCH1,sbr_address_start_mask_dch1_1);
  LOG_MESSAGE(hdlr, 1, ("SBRSTART1DCH1= 0x%x\n",reg->value));
#endif  
#endif  
}

void cinit_prgm_SBRRANGE0DCH1(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_SBR_EN_1 
#ifdef UMCTL2_DUAL_DATA_CHANNEL
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRRANGE0DCH1_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRRANGE0DCH1_reg;
 
  APPLY_CFG_TO_REGFIELD(dyn,SBRRANGE0DCH1,sbr_address_range_mask_dch1_0);

  LOG_MESSAGE(hdlr, 1, ("SBRRANGE0DCH1= 0x%x\n",reg->value));
#endif  
#endif  
}

void cinit_prgm_SBRRANGE1DCH1(SubsysHdlr_t *hdlr){
#ifdef UMCTL2_SBR_EN_1 
#ifdef UMCTL2_DUAL_DATA_CHANNEL
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_ARB_PORT0_SBRRANGE1DCH1_struct_t *reg = &hdlr->memCtrlr_m.regs.REGB_ARB_PORT0_SBRRANGE1DCH1_reg;
 
  APPLY_CFG_TO_REGFIELD(dyn,SBRRANGE1DCH1,sbr_address_range_mask_dch1_1);

  LOG_MESSAGE(hdlr, 1, ("SBRRANGE1DCH1= 0x%x\n",reg->value));
#endif  
#endif  
}

#endif // UMCTL2_INCL_ARB  

