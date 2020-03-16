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


#ifndef DDR_TIMING_H
#define	DDR_TIMING_H

#include <stdint.h>
#include <stdbool.h>

//#include "fwd.h"

#ifdef	__cplusplus
extern "C" {
#endif




	/*************************************************************************
	 * F U N C T I O N    P R O T O T Y P E S
	 *************************************************************************/

	/**
	 * @brief Takes a SubsysHdrl struc pointer and fills in the timing
	 * parameters
	 *@param hdlr Software utility handler
	 */
	void dwc_cinit_ddr_set_timing(SubsysHdlr_t* hdlr);

#ifdef MEMC_DDR4
	void dwc_cinit_set_ddr5_workaround(SubsysHdlr_t* hdlr);
#endif




#ifdef MEMC_DDR4
// --------------------------------------------------------------------------
// Name        : ddr4::set_clk_speed()
// Description : set the sg_tck_ps value in the hdlr->timingParams_m structure
// Params      : hdlr
// Returns     : none
// --------------------------------------------------------------------------
void ddr4_set_clk_speed(SubsysHdlr_t* hdlr, uint32_t p);
// --------------------------------------------------------------------------
// Name        : ddr5::set_clk_speed()
// Description : set the sg_tck_ps value in the hdlr->timingParams_m structure
// Params      : hdlr
// Returns     : none
// --------------------------------------------------------------------------
void ddr5_set_clk_speed(SubsysHdlr_t* hdlr, uint32_t p);

// --------------------------------------------------------------------------
// Name        : ddr4_set_default_timing_micron()
// Description : set all the default values for Micron model
// Returns     : none
// --------------------------------------------------------------------------
void ddr4_set_default_timing_micron(SubsysHdlr_t* hdlr, uint32_t p);

// --------------------------------------------------------------------------
// Name        : ddr4_set_default_timing_vip()
// Description : set all the default values for SNPS VIP
// Returns     : none
// --------------------------------------------------------------------------
void ddr4_set_default_timing_vip(SubsysHdlr_t* hdlr, uint32_t p);

// --------------------------------------------------------------------------
// Name        : ddr5_set_default_timing_vip()
// Description : set all the default values for SNPS VIP
// Returns     : none
// --------------------------------------------------------------------------
void ddr5_set_default_timing(SubsysHdlr_t* hdlr, uint32_t p);
// --------------------------------------------------------------------------
// Name        : ddr4_get_cas_latency()
// Description : depending on the speed grade, pick a CAS latency
// Params      : gd_en, dll_off_mode, sg
// Returns     : CAS Latency value
// --------------------------------------------------------------------------
uint32_t ddr4_get_cas_latency(bool pstate, SubsysHdlr_t* hdlr, bool gd_en, bool dll_off_mode);

//--------------------------------------------------------------------------
// Name        : ddr4_get_CWL_1st_set
// Description : depending on the speed grade and CAS Latency, pick the lower CAS Write Latency value
// Params      : dll_off_init, sg
// Returns     : lower possible CAS Write Latency value
//--------------------------------------------------------------------------
uint32_t ddr4_get_CWL_1st_set (bool pstate, SubsysHdlr_t* hdlr, bool dll_off_init);

// --------------------------------------------------------------------------
// Name        : ddr4_get_CWL_2nd_set
// Description : depending on the speed grade and CAS Latency, pick a the upper CAS Write Latency value
// Params      : dll_off_init, sg
// Returns     : upper possible CAS Write Latency value
// --------------------------------------------------------------------------
uint32_t ddr4_get_CWL_2nd_set(bool pstate, SubsysHdlr_t* hdlr, bool dll_off_init);

// --------------------------------------------------------------------------
// Name        : ddr4_get_cas_latency_rdbi()
// Description : depending on the speed grade, pick a CAS latency
// Params      : gd_en, bool dll_off_mode, dwc_ddr4_speed_grade_e sg
// Returns     : CAS Latency value with Read DBI
// --------------------------------------------------------------------------
uint32_t ddr4_get_cas_latency_rdbi(bool pstate, SubsysHdlr_t* hdlr, bool gd_en, bool dll_off_mode);

// --------------------------------------------------------------------------
// Name        : ddr5_get_cas_latency()
// Description : depending on the speed grade/tck, pick a CAS latency
// Params      : pstate, SubsysHdlr_t* hdlr
// Returns     : CAS Latency value
// --------------------------------------------------------------------------
uint32_t ddr5_get_cas_latency(bool pstate, SubsysHdlr_t* hdlr);

#endif

void dwc_cinit_get_jedec_clk_speed(SubsysHdlr_t* hdlr);


#ifdef MEMC_LPDDR4
void lpddr4_set_clk_speed(SubsysHdlr_t* hdlr, uint32_t p);
void lpddr4_set_default_timing(SubsysHdlr_t* hdlr, uint32_t p);

void lpddr5_set_clk_speed(SubsysHdlr_t* hdlr, uint32_t p);
void lpddr5_set_default_timing(SubsysHdlr_t* hdlr, uint32_t p);
#endif 

#ifdef	__cplusplus
}
#endif
#endif	//DDR_TIMING_H
