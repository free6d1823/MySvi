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

/** @brief function to first call cinit_pre_cfg to preform some pre
 * configuration calculations and then to call cinit_prgm_regs to
 * program all the register values.
 * @note no registers are actually programmed at this point.
 */
void dwc_cinit_setup_mmap(SubsysHdlr_t *hdlr) {
  TRACE();
  for(int i=0; i<hdlr->num_pstates; i++) {
    for(int j=0; j<hdlr->num_dch; j++) {
      cinit_pre_cfg(hdlr,i,j);
      dwc_cinit_log_timing(hdlr,i,j);
    }
  }
  cinit_prgm_regs(hdlr);
  LOG_MESSAGE(hdlr, 0, ("[dwc_cinit_setup_mmap] End\n"));

}

/** @brief iterate through all the registers setting up a 32-bit value to
 * be programmed into each writable register. 
 */
void cinit_prgm_regs(SubsysHdlr_t *hdlr) {

  TRACE();

  cinit_prgm_ddrc_regs(hdlr);
  cinit_prgm_freq_regs(hdlr);

#ifdef UMCTL2_INCL_ARB  
  cinit_prgm_arb_regs(hdlr);
#endif // UMCTL2_INCL_ARB

  cinit_prgm_amap_regs(hdlr);

  if(hdlr->logLevel_m>0) {
    dwc_cinit_dump_init_mmap(hdlr);
  }
}

void dwc_cinit_dump_init_mmap(SubsysHdlr_t *hdlr) {
#include "dwc_cinit_dump_mmap.h" 
}



