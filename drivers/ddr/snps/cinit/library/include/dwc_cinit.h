//  ------------------------------------------------------------------------
//
//                    (C) COPYRIGHT 2019 SYNOPSYS, INC.
//                            ALL RIGHTS RESERVED
//
//  This software and the associated documentation are confidential and
//  proprietary to Synopsys, Inc.  Your use or disclosure of this
//  software is subject to the terms and conditions of a written
//  license agreement between you, or your company, and Synopsys, Inc.
//
// The entire notice above must be reproduced on all authorized copies.
//
// Component Name   : DWC_ddrctl
// Component Version: 1.00a-ea00
// Release Type     : EA
//  ------------------------------------------------------------------------

#ifndef __CINIT_H__
#define __CINIT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <libgen.h>
#include "fwd.h"


#ifdef SIM_MODE
// imported DPI function to exit the simulation gracefully.
extern void abort_simulation(char msg[50]); 
#endif

// From coreconsultant generate_views command
#include "DWC_ddrctl.h"

// generate_views -views [list  {Component Register Headers} ]
#include "DWC_ddrctl_header.h"

// To align more closely with PHYININT include the structure
// to setup PHYINT software
//#include "dwc_ddrphy_phyinit_struct.h"
#include "dwc_ddrphy_phyinit_userCustom.h"


/* uint32_rnd_t will be declared "rand unsigned int" in Systemverilog world. */
typedef uint32_t uint32_rnd_t;
typedef uint16_t uint16_rnd_t;
typedef uint8_t uint8_rnd_t;
typedef bool bool_rnd_t;
#include "dwc_cinit_types.h"
//
// the following files are automated from corebuilder and generateRegisterInfo.tcl
#include "dwc_cinit_reg_struct.h"
#include "dwc_cinit_regs.h"
#include "dwc_cinit_macros.h"
#include "dwc_cinit_dyn_struct.h" 
#include "dwc_cinit_qdyn_struct.h" 
#include "dwc_cinit_static_struct.h" 
#include "dwc_cinit_cfg.h"

#include "log.h"
#include "ddr_timing.h"

// Function prototypes
extern void dwc_cinit_setup(SubsysHdlr_t *hdlr);
extern void dwc_cinit_set_operational_clk_period(SubsysHdlr_t *hdlr);
extern void dwc_cinit_reg_defaults(SubsysHdlr_t *hdlr);
extern void dwc_cinit_phyinit_setuserinput(SubsysHdlr_t *hdlr );
extern void dwc_cinit_setup_mmap(SubsysHdlr_t *hdlr);
extern void dwc_cinit_print_initial_msg(SubsysHdlr_t *hdlr);
extern void dwc_cinit_dump_init_mmap(SubsysHdlr_t *hdlr);
extern void dwc_cinit_log_timing(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_pre_cfg(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch );
extern void cinit_cal_cwlx(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_cal_rd2wr(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_cal_wr2rd(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern uint32_t cinit_ps_to_tck(uint32_t param_ps, uint32_t tck_ps);
extern uint8_t get_cal_cycles(uint8_t cal_mode);
extern void cinit_cal_lpddr4x_multiphy_dfi_timings(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_cal_lpddr54_dfi_timings(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_cal_ddr43_dfi_timings(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_cal_ddr54_dfi_timings(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern uint32_t cal_lpddr5_odton(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);

extern void cinit_encode_wr_recovery(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_encode_rl_wl(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_encode_lpddr5_rl_wl(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_encode_cas_latency(SubsysHdlr_t *hdlr,uint32_t p);
extern void cinit_encode_cas_write_latency(SubsysHdlr_t *hdlr,uint32_t p);
extern void cinit_encode_write_cmd_latency(SubsysHdlr_t *hdlr,uint32_t p);
extern void cinit_encode_tccd_l_latency(SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch);
extern uint32_t cinit_get_nrtp(uint8_t row);
extern uint32_t cinit_get_rl_row(uint8_t rl, uint8_t x16, uint8_t dbi);
extern uint32_t cinit_get_wl_row(uint8_t wl, uint8_t x16, uint8_t wls);
extern uint32_t dwc_cinit_get_min_t_xsr( SubsysHdlr_t *hdlr, uint32_t tck_ps);
extern uint32_t dwc_cinit_get_lpddr4_trfcab(SubsysHdlr_t* hdlr);
extern uint32_t dwc_cinit_get_lpddr5_trfcab(SubsysHdlr_t* hdlr);
extern uint32_t dwc_cinit_get_lpddr5_trfcpb(SubsysHdlr_t* hdlr);
extern uint32_t dwc_cinit_get_lpddr5_tpbr2pbr(SubsysHdlr_t* hdlr);
extern void dwc_cinit_map_tck_ps_to_data_rate(SubsysHdlr_t* hdlr);
extern dwc_lpddr4_data_rate_e map_tck_ps_to_l_lpddr4_data_rate(SubsysHdlr_t* hdlr);
extern dwc_lpddr5_data_rate_e map_tck_ps_to_l_lpddr5_data_rate(SubsysHdlr_t* hdlr);
extern uint32_t cinit_cal_ddr5_rd_min_gap(SubsysHdlr_t *hdlr);
extern uint32_t cinit_cal_ddr5_wr_min_gap(SubsysHdlr_t *hdlr);
extern uint32_t cinit_get_ddr5_twpre(SubsysHdlr_t *hdlr,uint32_t p);
extern uint32_t cinit_get_ddr5_t_rd_dqs_offset(SubsysHdlr_t *hdlr, uint32_t p);
extern void cinit_encode_ddr5_trtp_latency(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern float cinit_get_lpddr5_tras_max(SubsysHdlr_t *hdlr, uint32_t trefi, uint32_t refesh_rate,uint32_t p);
extern void cinit_set_rcd(SubsysHdlr_t *hdlr);

extern void break_b4_exit();

extern void cinit_prgm_ddrc_regs(SubsysHdlr_t *hdlr);
extern void cinit_prgm_freq_regs(SubsysHdlr_t *hdlr);
extern void cinit_prgm_amap_regs(SubsysHdlr_t *hdlr);

extern void cinit_prgm_regs(SubsysHdlr_t *hdlr);
extern void cinit_prgm_MSTR0(SubsysHdlr_t *hdlr);
extern void cinit_prgm_MSTR1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_MSTR2(SubsysHdlr_t *hdlr);
extern void cinit_prgm_MSTR3(SubsysHdlr_t *hdlr,uint32_t ch);
extern void cinit_prgm_PASCTL1(SubsysHdlr_t *hdlr,uint32_t ch);
extern void cinit_prgm_PASCTL3(SubsysHdlr_t *hdlr,uint32_t ch);
extern void cinit_prgm_MRCTRL0(SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_DERATECTL0(SubsysHdlr_t *hdlr);
extern void cinit_prgm_DERATECTL5(SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_DERATECTL6 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DERATEVAL0(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_prgm_DERATEVAL1(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_prgm_DERATEINT(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_prgm_PWRCTL(SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PWRTMG(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_prgm_HWLPCTL (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_HWFFCCTL (SubsysHdlr_t *hdlr);
extern void cinit_prgm_RFSHCTL0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_RFSHMOD0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_RFSHMOD1 (SubsysHdlr_t *hdlr);

extern void cinit_prgm_RFSHSET1TMG0 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET1TMG1 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET1TMG2 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET1TMG3 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET1TMG4 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET1TMG5 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET1TMG6 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET2TMG0 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET2TMG1 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_RFSHSET2TMG2 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch );
extern void cinit_prgm_INITTMG0 (SubsysHdlr_t *hdlr,uint32_t dch);
extern void cinit_prgm_INITTMG1 (SubsysHdlr_t *hdlr,uint32_t dch);
extern void cinit_prgm_INITTMG2 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_INITMR0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_INITMR1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_INITMR2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_INITMR3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DIMMCTL (SubsysHdlr_t *hdlr);
extern void cinit_prgm_RANKCTL (SubsysHdlr_t *hdlr);
extern void cinit_prgm_RANKTMG0(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG4 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG5 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG6 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG7 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG8 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG9 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG10 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG12 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG13 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG14 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG16 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG17 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG18 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG19 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG20 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG21 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG22 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG24 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG25 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG26 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RANK_SWITCH_TIMING_CONTROL0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RANK_SWITCH_TIMING_CONTROL1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RANK_SWITCH_TIMING_CONTROL2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RANK_SWITCH_TIMING_CONTROL3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RANK_SWITCH_TIMING_CONTROL4 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RANK_SWITCH_TIMING_CONTROL5 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_TMGCFG(SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);

extern void cinit_prgm_ADDRMAP0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ADDRMAP1 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP2 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP3 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP4 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP5 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP6 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP7 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP8 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP9 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP10 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP11 (SubsysHdlr_t *hdlr, uint32_t amap);
extern void cinit_prgm_ADDRMAP12 (SubsysHdlr_t *hdlr);

extern void cinit_prgm_ECCCFG0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ECCCFG1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ECCCTL (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_ECCPOISONADDR0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ECCPOISONADDR1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ECCPOISONPAT0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ECCPOISONPAT1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ECCPOISONPAT2 (SubsysHdlr_t *hdlr);

extern void cinit_prgm_ZQCTL0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ZQCTL2 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ZQSET1TMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_ZQSET1TMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DFITMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DFITMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DFITMG2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DFITMG4 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch);
extern void cinit_prgm_DFITMG5 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch);
extern void cinit_prgm_DFITMG6 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch);
extern void cinit_prgm_DFIUPDTMG0 (SubsysHdlr_t *hdlr,uint32_t dch);
extern void cinit_prgm_DFIUPD0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DFIMISC (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DFIPHYMSTR (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DBICTL (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_OPCTRL0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_OPCTRL1 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_SCHED0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_SCHEDTMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_PERFLPR1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_HWLPTMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);

extern void cinit_prgm_ADVECCINDEX (SubsysHdlr_t *hdlr);
extern void cinit_prgm_OCSAPCFG0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_OCPARCFG1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DQSOSCRUNTIME (SubsysHdlr_t *hdlr);
extern void cinit_prgm_SCHED1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_SCHED2 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_SCHED3 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_SCHED4 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_SCHED5 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DFILPCFG0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DFILPCFG1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DFIUPD1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_CRCPARCTL1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_CRCPARCTL2 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DATACTL0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_ODTMAPK (SubsysHdlr_t *hdlr);
extern void cinit_prgm_SWCTL (SubsysHdlr_t *hdlr);
extern void cinit_prgm_SWCTLSTATIC (SubsysHdlr_t *hdlr);
extern void cinit_prgm_CHCTL (SubsysHdlr_t *hdlr);
extern void cinit_prgm_OCECCCFG0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_OCECCCFG1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_OCCAPCFG (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DQMAP0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DQMAP1 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DQMAP2 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DQMAP3 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DQMAP4 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_DQMAP5 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_REGPARCFG (SubsysHdlr_t *hdlr);
extern void cinit_prgm_POISONCFG (SubsysHdlr_t *hdlr);
extern void cinit_prgm_MSTR4 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_MRCTRL1 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_MRCTRL2 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_MRCTRL3 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_OCPARCFG0 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_ZQCTL1 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_CRCPARCTL0 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_CRCPOISONCTL (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_CAPARPOISONCTL (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL0 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL2 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL4 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_CMDCFG (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_CMDCTL (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_CMDEXTCTL (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_ODTMAP (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_OCCAPCFG1 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_OPCTRLCMD (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_DQSOSCCFG0 (SubsysHdlr_t *hdlr);
extern void cinit_prgm_PASCTL5 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL6 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL7 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL8 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL9 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL10 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL11 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL12 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL13 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL14 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL15 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL16 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL17 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL18 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL20 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL21 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL22 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL23 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL24 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL25 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL26 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL27 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL28 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL29 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL30 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL31 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL32 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL33 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL34 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_PASCTL35 (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_DU_CMDBUF_CTRL (SubsysHdlr_t *hdlr, uint32_t dch);
extern void cinit_prgm_LP_CMDBUF_CTRL (SubsysHdlr_t *hdlr, uint32_t dch);

extern void cinit_prgm_DFILPTMG0 (SubsysHdlr_t *hdlr,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG11 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG15 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG23 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG4 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG5 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG6 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG7 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG8 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG9 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG10 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_MRAMTMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_MRAMTMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_MRAMTMG2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_MRAMTMG3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DFITMG3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DFIUPDTMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RCDINIT1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RCDINIT2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RCDINIT3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RCDINIT4 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DQSOSCCTL0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RANKTMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_ODTCFG (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_CRCPARTMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_PERFHPR1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_PERFWR1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET1TMG27 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DRAMSET2TMG11 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_DFITMG7 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RFSHSET1TMG7 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RFSHSET1TMG8 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_RFSHSET2TMG3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_ZQSET1TMG2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);
extern void cinit_prgm_ZQSET2TMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch);

#ifdef UMCTL2_INCL_ARB 
extern void cinit_prgm_arb_regs(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PCCFG(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PCFGR(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PCFGW(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PCFGIDMASKCH(SubsysHdlr_t *hdlr,uint32_t port);
extern void cinit_prgm_PCFGIDVALUECH(SubsysHdlr_t *hdlr,uint32_t port);
extern void cinit_prgm_PCFGQOS0(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PCFGQOS1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PCFGWQOS0(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PCFGWQOS1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRCTL(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRWDATA0(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRWDATA1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PDCH(SubsysHdlr_t *hdlr);
extern void cinit_prgm_PCTRL(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SARBASE(SubsysHdlr_t *hdlr,uint32_t n); 
extern void cinit_prgm_SARSIZE(SubsysHdlr_t *hdlr,uint32_t n); 
extern void cinit_prgm_SBRSTART0(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRSTART1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRRANGE0(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRRANGE1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRSTART0DCH1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRSTART1DCH1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRRANGE0DCH1(SubsysHdlr_t *hdlr);
extern void cinit_prgm_SBRRANGE1DCH1(SubsysHdlr_t *hdlr);
#endif // UMCTL2_INCL_ARB


#endif // __CINIT_H__

