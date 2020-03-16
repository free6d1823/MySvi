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


#ifndef __CINIT_MACROS_h__
#define __CINIT_MACROS_h__

#ifndef max
#define max(a,b)	(((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#define CEIL(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))

#define DIVIDE_ROUNDDOWN(a,b) ( (a) / (b) )

#ifndef SIM_MODE
#define ASSERT(n)	\
	do {			\
		(void)(n);	\
		assert(n);	\
	} while(0)

#else
// When simulating over DPI use a custom ASSERT macro.
// instead of calling abort() we call an imported DPI function
// abort_simulation() to exit the simulation gracefully.
// The error is printed to stdout so that it appears in the 
// simulation log file.
#define stringize(s) #s
#define XSTR(s) stringize(s)
#if !defined NDEBUG
void abort (void);
# define ASSERT(a) \
do { \
if (0 == (a)) { char str[50]; \
sprintf(str,\
"Assertion failed: %s, " \
"%s(), %d at \'%s\'\n", \
__FILE__, \
__func__, \
__LINE__, \
XSTR(a)); \
abort_simulation(str); \
} \
} while (0)
#else
# define ASSERT(a) (void)0
#endif



#endif


#define CONSTRAIN_INSIDE(var,minVal,maxVal)					\
	do {													\
		uint32_t local_min = (uint32_t)minVal;						\
		uint32_t local_max = (uint32_t)maxVal;						\
		if (local_min > local_max) {						\
			uint32_t tmpVal = local_min	;					\
			local_min = local_max;							\
			local_max = tmpVal;								\
		}													\
		if (hdlr->is_constraint_assert_set) {					\
			ASSERT((var>=local_min) && (var<=local_max));	\
		} else { 											\
			if(var<local_min) {								\
				var = local_min;							\
			} else if((var>local_max)) {					\
				var = local_max;							\
			}												\
		}													\
	} while (0)



#define CONSTRAIN_MIN(var, val)				\
	do {									\
		if (hdlr->is_constraint_assert_set) {	\
			ASSERT(var >= val);				\
		} else if (var < val) {				\
			var = val;						\
		}									\
	} while (0)

#define CONSTRAIN_MAX(var, val)				\
	do {									\
		if (hdlr->is_constraint_assert_set) {	\
			ASSERT(var <= val);				\
		} else if (var > val) {				\
			var = val;						\
		}									\
	} while (0)

#define CONSTRAIN_NE(var, val)			\
	do {								\
		if (hdlr->is_constraint_assert_set) {	\
			ASSERT(var != val);				\
		} 					\
	} while (0)

#define CONSTRAIN_EQ(var, val)			\
	do {								\
		if (hdlr->is_constraint_assert_set) {	\
			ASSERT(var == val);				\
		} else if (var != val) {				\
			var = val;						\
		}									\
	} while (0)

#define DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(_regbase,  _regn)\
  DWC_DDRCTL_DECLARE_DCHC_REG_PTR(0, _regbase, _regn, reg, _MAP)\
  DWC_DDRCTL_DECLARE_DCHC_REG_PTR(1, _regbase, _regn, reg, _MAP) \
  
//DWC_DDRCTL_DECLARE_DCHC_REG_PTR(2, _regbase, _regn, reg, _MAP)
//DWC_DDRCTL_DECLARE_DCHC_REG_PTR(3, _regbase, _regn, reg, _MAP)


#define DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(_regbase,  _regn)\
  DWC_DDRCTL_DECLARE_DCHC_REG_PTR(0, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_DCHC_REG_PTR(1, _regbase, _regn, reg, _CH)

#define DWC_DDRCTL_CAST_REG_DCHC_MUX(_chn, _regbase,  _regn, _regname, _chprefix)\
  _regname##_ch##_chn=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_DCHC_REG_EL(_chn,_regbase, _regn, _chprefix);\
  reg=(DWC_DDRCTL_DCHC_REG_STRUCT(0,_regbase, _regn, _chprefix) *) _regname##_ch##_chn;\

#define DWC_DDRCTL_DCHC_REG_STRUCT(_chn, _regbase, _regn, _chprefix)\
  _regbase####_chprefix####_chn##_##_regn##_struct_t

#define DWC_DDRCTL_DCHC_REG_EL(_chn, _regbase, _regn, _chprefix)\
  _regbase####_chprefix####_chn##_##_regn##_reg

#define DWC_DDRCTL_DECLARE_DCHC_REG_PTR(_chn, _regbase, _regn, _regvar, _chprefix)\
    DWC_DDRCTL_DCHC_REG_STRUCT(_chn,_regbase,_regn, _chprefix) * _regvar##_ch##_chn;

#define DWC_DDRCTL_FREQ_REG_STRUCT(_p, _chn, _regbase, _regn, _chprefix)\
  _regbase####_p####_chprefix####_chn##_##_regn##_struct_t

#define DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(_p, _chn, _regbase, _regn, _regvar, _chprefix)\
    DWC_DDRCTL_FREQ_REG_STRUCT(_p,_chn,_regbase,_regn, _chprefix) * _regvar##_ps##_p##_ch##_chn;

#define DWC_DDRCTL_CAST_REG_DCHC(_chn, _regbase,  _regn, _regname, _suffix)\
  if(_chn==0) {\
    DWC_DDRCTL_CAST_REG_DCHC_MUX(0, _regbase,  _regn, _regname, _suffix)\
  }\
  else if (_chn==1) {\
    DWC_DDRCTL_CAST_REG_DCHC_MUX(1, _regbase,  _regn, _regname, _suffix)\
  }

#define DWC_DDRCTL_CAST_REG_AMAP(_amap, _regbase,  _regn, _regname, _suffix)\
  if(_amap==0) {\
    DWC_DDRCTL_CAST_REG_DCHC_MUX(0, _regbase,  _regn, _regname, _suffix)\
  }\
  else if (_amap==1) {\
    DWC_DDRCTL_CAST_REG_DCHC_MUX(1, _regbase,  _regn, _regname, _suffix)\
  }

/*
  else if (_amap==2) {\
    DWC_DDRCTL_CAST_REG_DCHC_MUX(2, _regbase,  _regn, _regname, _suffix, _C##_suffix)\
  }\
  else if (_amap==3) {\
    DWC_DDRCTL_CAST_REG_DCHC_MUX(3, _regbase,  _regn, _regname, _suffix, _C##_suffix)\
  }
*/

#define DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(_chn, _regbase,  _regn)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(0, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(1, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(2, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(3, _chn, _regbase, _regn, reg, _CH)\
  
/*  
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(4, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(5, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(6, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(7, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(8, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(9, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(10, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(11, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(12, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(13, _chn, _regbase, _regn, reg, _CH)\
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(14, _chn, _regbase, _regn, reg, _CH)
*/

#define DWC_DDRCTL_FREQ_REG_EL(_p, _chn, _regbase, _regn, _chprefix)\
  _regbase####_p####_chprefix####_chn##_##_regn##_reg

#define DWC_DDRCTL_CAST_REG_FREQP_DCHC(_p, _chn, _regbase,  _regn, _regname, _chprefix)\
  _regname##_ps##_p##_ch##_chn=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_FREQ_REG_EL(_p,_chn,_regbase, _regn, _chprefix);\
  reg=(DWC_DDRCTL_FREQ_REG_STRUCT(0,0,_regbase, _regn, _CH) *) _regname##_ps##_p##_ch##_chn;\

#define DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(_p, _chn, _regbase,  _regn)\
  if(_p==0) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(0, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==1) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(1, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==2) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(2, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==3) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(3, _chn, _regbase, _regn, reg, _CH)\
  }\
    
/*
  else if(_p==4) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(4, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==5) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(5, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==6) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(6, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==7) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(7, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==8) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(8, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==9) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(9, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==10) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(10, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==11) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(11, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==12) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(12, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==13) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(13, _chn, _regbase, _regn, reg, _CH)\
  }\
  else if(_p==14) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(14, _chn, _regbase, _regn, reg, _CH)\
  }
*/

#define DWC_DDRCTL_CAST_REG_FREQP(_p, _chn, _regbase,  _regn)\
  if(_chn==0) {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(_p, 0, _regbase,  _regn)\
  }\
  else {\
    DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(_p, 1, _regbase,  _regn)\
  }

#define DWC_DDRCTL_DECLARE_DCHC_DDRC_REG_PTRS( _regn)\
  REGB_DDRC_CH0_##_regn##_struct_t *reg;\
  REGB_DDRC_CH1_##_regn##_struct_t *reg1;\

#define DWC_DDRCTL_CAST_DDRC_REG_DCH(ch,_regn)\
  if(ch==1) {\
    reg1=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH1_##_regn##_reg;\
    reg=(REGB_DDRC_CH0_##_regn##_struct_t *)reg1;\
  }


#define IS_DDR3 (0)
#define IS_DDR4 (hdlr->spdData_m.sdram_protocol == DWC_DDR4)
#define IS_DDR5 (hdlr->spdData_m.sdram_protocol == DWC_DDR5)
#define MEMORYMODELS (1)
#define IS_LPDDR2 (0)
#define IS_LPDDR3 (0)
#define IS_LPDDR23 (0 )
#define IS_LPDDR4 (hdlr->spdData_m.sdram_protocol == DWC_LPDDR4 )
#define IS_LPDDR5 (hdlr->spdData_m.sdram_protocol == DWC_LPDDR5 )

#define IS_mDDR (0)

#define IS_NODIMM (hdlr->spdData_m.module_type == DWC_NODIMM)
#define IS_UDIMM (hdlr->spdData_m.module_type == DWC_UDIMM)
#define IS_RDIMM (hdlr->spdData_m.module_type == DWC_RDIMM)
#define IS_VIP_RDIMM ((hdlr->spdData_m.module_type == DWC_RDIMM) || (hdlr->spdData_m.module_type == DWC_LRDIMM))

#define IS_LRDIMM (hdlr->spdData_m.module_type == DWC_LRDIMM)

#define DLL_OFF_MODE(i) (hdlr->memCtrlr_m.qdyn_cfg.dll_off_mode)

#define IS_HALF_BUS_WIDTH (MEMC_DRAM_DATA_WIDTH / hdlr->spdData_m.module_width_bits == DDR_BUSWIDTH_HALF)
#define IS_FULL_BUS_WIDTH (MEMC_DRAM_DATA_WIDTH / hdlr->spdData_m.module_width_bits == DDR_BUSWIDTH_FULL)
#define TRFC_MIN(i) \
     (hdlr->spdData_m.sdram_protocol==DWC_DDR4) ?		\
      (hdlr->timingParams_m[i].ddr4_trfc_min_ps) : 0

#define DRAM_RAW (hdlr->spdData_m.dram_raw)
#define DRAM_CAW (hdlr->spdData_m.dram_caw)
#define DRAM_BAW (hdlr->spdData_m.dram_baw)
#define DRAM_BGW (hdlr->spdData_m.dram_bgw)

#define MRAM_RAW (hdlr->spdData_m.mram_raw)
#define MRAM_CAW (hdlr->spdData_m.mram_caw)
#define MRAM_BAW (hdlr->spdData_m.mram_baw)
#define MRAM_BGW (hdlr->spdData_m.mram_bgw)

#define MEM_RAW ((DRAM_RAW >= MRAM_RAW) ? DRAM_RAW : MRAM_RAW)
#define MEM_CAW ((DRAM_CAW >= MRAM_CAW) ? DRAM_CAW : MRAM_CAW)
#define MEM_BAW ((DRAM_BAW >= MRAM_BAW) ? DRAM_BAW : MRAM_BAW)
#define MEM_BGW ((DRAM_BGW >= MRAM_BGW) ? DRAM_BGW : MRAM_BGW)


#define USE_RCD (IS_RDIMM)
#define IS_X4 (DEV_DQ_WIDTH==4)
#define IS_X8 (DEV_DQ_WIDTH==8)
#define IS_X16 (DEV_DQ_WIDTH==16)
#define USE_TI_RCD (hdlr->spdData_m.use_ti_rcd)
#define DEV_DQ_WIDTH (hdlr->spdData_m.sdram_width_bits)
#define IS_DENS_512MBIT (hdlr->spdData_m.sdram_capacity_mbits==512)
#define IS_DENS_1GBIT (hdlr->spdData_m.sdram_capacity_mbits==1024)
#define IS_DENS_2GBIT (hdlr->spdData_m.sdram_capacity_mbits==2048)
#define IS_DENS_4GBIT (hdlr->spdData_m.sdram_capacity_mbits==4096)
#define IS_DENS_8GBIT (hdlr->spdData_m.sdram_capacity_mbits==8192)
#define IS_DENS_16GBIT (hdlr->spdData_m.sdram_capacity_mbits==16384)
#define MR7_BY_PHY (hdlr->mr7_by_phy)
#define GET_TCK(i) (hdlr->spdData_m.tck_ps[i])

#ifdef UMCTL2_CID_EN
  #define IS_CID_EN ((IS_DDR4 && (hdlr->spdData_m.ddr4_sg >= DWC_DDR4_1600J_3DS2B) && (hdlr->spdData_m.ddr4_sg <= DWC_DDR4_3200AC_3DS4A)) || IS_DDR5)
  #define GET_CID_WIDTH (hdlr->spdData_m.cid_width)
  #define DRAM_NUM_3DS_LRANKS ((uint32_t)pow(2, GET_CID_WIDTH))
#else
  #define IS_CID_EN 0
  #define GET_CID_WIDTH 0
  #define DRAM_NUM_3DS_LRANKS 1
#endif

#ifdef DWC_DDRCTL_MEM_DDR5_ON
  #ifdef DWC_DDRCTL_MEM_MODULE_TYPE_RDIMM_ON
    #define IS_DDR5_RDIMM
  #endif
#endif

#define IS_DUAL_CHAN (UMCTL2_DUAL_CHANNEL_EN)

#define UMCTL2_PUB_TRAINING ((hdlr->option_m.pub_firmware_en == 1) && (hdlr->option_m.pub_training_en == 1))
#define UMCTL2_PUB_FIRMWARE (hdlr->option_m.pub_firmware_en == 1)

#define DWC_DDRCTL_ARB_REG_STRUCT(_port, _regbase, _regn, _portprefix)\
   _regbase##_##_portprefix####_port##_##_regn##_struct_t

#define DWC_DDRCTL_ARB_REG_EL( _port, _regbase, _regn, _portprefix)\
   _regbase##_##_portprefix####_port##_##_regn##_reg\


#define DWC_DDRCTL_GET_MP_REG_PTR( _n, _regn, _portprefix)\
  DWC_DDRCTL_ARB_REG_STRUCT(_n, REGB_ARB, _regn, _portprefix) *_regn##reg##_n ; \
  _regn##reg##_n =&hdlr->memCtrlr_m.regs.DWC_DDRCTL_ARB_REG_EL(_n, REGB_ARB, _regn, _portprefix);\
  reg=(DWC_DDRCTL_ARB_REG_STRUCT(0, REGB_ARB, _regn, PORT) *)_regn##reg##_n ;\

#endif
