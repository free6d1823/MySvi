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


#include <string.h>
#include <assert.h>
#include <math.h>

#include "log.h"
#include "dwc_cinit.h"

/*************************************************************************
 * F U N C T I O N    I M P L E M E N T A T I O N
 *************************************************************************/
void dwc_cinit_get_jedec_clk_speed(SubsysHdlr_t* hdlr)
{
    TRACE();
    ddrSpdData_t* spd = &hdlr->spdData_m;
    for(int p=0; p<UMCTL2_FREQUENCY_NUM; p++) {
        LOG_MESSAGE(hdlr, 0, ("UMCTL2_FREQUENCY_NUM(p)=%d sdram_protocol=%d\n", p, spd->sdram_protocol));
        switch(spd->sdram_protocol) {
#ifdef MEMC_DDR5
            case DWC_DDR5:
              LOG_MESSAGE(hdlr, 0, ("calling ddr5_set_clk_speed"));
              ddr5_set_clk_speed(hdlr,p);
              break;
#endif
#ifdef MEMC_DDR4            
            case DWC_DDR4:
              ddr4_set_clk_speed(hdlr, p);
              break;
#endif
#ifdef MEMC_LPDDR4
            //Only clk_speed for p = 0 is set. For multiple p-states, the frequency will be set by 'set_mem_clks' function in 'dwc_ddrctl_sdram_base_cfg.sv'.
            //In 'set_mem_clks' we can set the discrete frequency as well. But in lpddr4_set_clk_speed or lpddr5_set_clk_speed, only specific speed-grades can be set
            case DWC_LPDDR4:
              lpddr4_set_clk_speed(hdlr, p);
              break; 
            case DWC_LPDDR5:
              lpddr5_set_clk_speed(hdlr, p);
              break;
#endif              
            default:
              ERROR_MESSAGE(("sdram_protocol=%0d not yet supported. ",spd->sdram_protocol));
              break;
        }        
    } // for p
}

void dwc_cinit_ddr_set_timing(SubsysHdlr_t* hdlr)
{
    TRACE();
    for(int p=0; p<UMCTL2_FREQUENCY_NUM; p++) {
        ddrSpdData_t* spd = &hdlr->spdData_m;
        if(hdlr->is_timing_set[p]==1) {	//dont re-do unnecessarily
            //dwc_cinit_print("timing for pstate%0d already set\n",p);
            continue;
        }
#ifdef MEMC_DDR4        
        if (spd->sdram_protocol == DWC_DDR4) {
#if (MEMORYMODELS > 0)
            ddr4_set_default_timing_vip(hdlr, p);
#else
            ddr4_set_default_timing_micron(hdlr, p);
#endif

#ifdef UMCTL2_DDR4_MRAM_EN
            ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);                                
            ddr_setDefaultTiming_mram(timing, spd);
#endif
        } 
#ifdef MEMC_DDR5
        else if (spd->sdram_protocol == DWC_DDR5) {
          ddr5_set_default_timing(hdlr,p);
        }

#endif //MEMC_DDR5
#endif //MEMC_DDR4

#ifdef MEMC_LPDDR4
        if (spd->sdram_protocol == DWC_LPDDR4) {
            lpddr4_set_default_timing(hdlr, p);
        }
        else if (spd->sdram_protocol == DWC_LPDDR5) {
            lpddr5_set_default_timing(hdlr, p);
        }
#endif        
        else {
            ERROR_MESSAGE(("sdram_protocol=%0d not yet supported. ",spd->sdram_protocol));
        }
        //dwc_cinit_print("setting timing for pstate%0d to true\n",p);
        hdlr->is_timing_set[p] = 1;
    } // for p
}





















#ifdef MEMC_DDR5
void dwc_cinit_set_ddr5_workaround (SubsysHdlr_t* hdlr) {
  LOG_MESSAGE(hdlr, 0, ("calling dwc_cinit_set_ddr5_workaround"));
  hdlr->spdData_m.tck_ps[0] = 833;
  hdlr->spdData_m.tck_ps[1] = 833;
  hdlr->spdData_m.tck_ps[2] = 833;
  hdlr->spdData_m.tck_ps[3] = 833;
}
#endif


