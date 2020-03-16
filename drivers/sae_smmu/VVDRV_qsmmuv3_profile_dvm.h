#ifndef __VVDRV_QSMMUV3_PROFILE_H__
#define __VVDRV_QSMMUV3_PROFILE_H__

//#include "VVDRV_qsmmuv3_CommonInclude.h"
#include "VVDRV_qsmmuv3_STE_dvm.h"
#include "VVDRV_qsmmuv3_CD_dvm.h"
typedef struct
{
  uint64_t s_cd_alloc_base;
  uint64_t s_cd_alloc_limit;
  uint64_t s_st_alloc_base;
  uint64_t s_st_alloc_limit;
  uint64_t s_queue_alloc_base;
  uint64_t s_queue_alloc_limit;
}smmu_profile;
typedef struct 
{
   uint64_t tt_4k_alloc_base;
   uint64_t tt_4k_alloc_limit;
   uint64_t tt_4k_alloc_ptr;
   uint64_t tt_16k_alloc_base;
   uint64_t tt_16k_alloc_limit;
   uint64_t tt_16k_alloc_ptr;
   uint64_t tt_64k_alloc_base;
   uint64_t tt_64k_alloc_limit;
   uint64_t tt_64k_alloc_ptr;

   uint64_t page_4k_alloc_base;
   uint64_t page_4k_alloc_limit;
   uint64_t page_4k_alloc_ptr;
   uint64_t page_16k_alloc_base;
   uint64_t page_16k_alloc_limit;
   uint64_t page_16k_alloc_ptr;
   uint64_t page_64k_alloc_base;
   uint64_t page_64k_alloc_limit;
   uint64_t page_64k_alloc_ptr;

   uint64_t ns_cd_alloc_base;
   uint64_t ns_cd_alloc_limit;
   uint64_t ns_cd_alloc_ptr;

   uint64_t s_cd_alloc_base;
   uint64_t s_cd_alloc_limit;
   uint64_t s_cd_alloc_ptr;
}vm_profile;

typedef struct 
{
   uint64_t ns_st_alloc_base;
   uint64_t ns_st_alloc_limit;
   uint64_t ns_st_alloc_ptr;
   uint64_t ns_queue_alloc_base;
   uint64_t ns_queue_alloc_limit;
   uint64_t ns_queue_alloc_ptr;

   uint64_t s_st_alloc_base;
   uint64_t s_st_alloc_limit;
   uint64_t s_st_alloc_ptr;
   uint64_t s_queue_alloc_base;
   uint64_t s_queue_alloc_limit;
   uint64_t s_queue_alloc_ptr;

   vm_profile hyper_profile;

   uint32_t CR_E2H;
}system_profile;

typedef enum {
  TT_TG_4K = 0,
  TT_TG_16K = 1,
  TT_TG_64K = 2,
} tt_tgs_e;

typedef enum {
  TT_LVL_0 = 0,
  TT_LVL_1 = 1,
  TT_LVL_2 = 2,
  TT_LVL_3 = 3,
} tt_level_e;

typedef struct ttb
{
  tt_tgs_e tgs;
  CD_TxSZ txsz;
  uint64_t ttb_addr;
  uint32_t stage;

  tt_level_e root_lvl;
  CD_xR tt_ir;
  CD_xR tt_or;
  CD_SHx tt_sh;
  CD_NSCFGx nscfg;
  struct ttb* p_vttb;
  vm_profile *p_vm_profile;
}ttb_profile;

// need a similiar but simpler profile for each VM allocate
// since if stage 2 enabled, STE.S1ContextPtr and all CD are IPA
// so CD allocate should be handled by Guest OS level

//typedef struct mem_node
//{
//   uint64_t mem_base;
//   uint64_t mem_limit;
//   struct mem_node *next;
//} mem_space;

typedef struct 
{
   uint64_t base;
   uint32_t log2_num;
}queue_profile;

typedef struct 
{
   uint64_t addr;
   uint32_t data;
   uint32_t attr;
} msi_cfg;

typedef struct 
{
   queue_profile s_eventq;
   queue_profile ns_eventq;
}eventq_profile;

typedef struct 
{
   queue_profile s_cmdq;
   queue_profile ns_cmdq;
}cmdq_profile;

//struct tt_profile
//{
//};
//struct cd_profile
//{
//};

typedef enum{
  STE_SPLIT_4K = 6,
  STE_SPLIT_16K = 8,
  STE_SPLIT_64K = 10
} STE_SPLIT;

typedef struct 
{
   uint32_t linear;
   STE_SPLIT split;
   uint32_t log2size;
}strtab_cfg;

typedef enum{
   QSMMU_CRYPTO,
   QSMMU_GBE,
   QSMMU_HIDMA,
   QSMMU_IMC,
   QSMMU_PCIE,
   QSMMU_PSS,
   QSMMU_SATA,
   QSMMU_NUM
} qsmmu_ss_e;

typedef enum{
   SW_NS_EL1,
   SW_EL2,
   SW_EL2H,
   SW_S_EL1,
   SW_EL3,
   SW_QAD
} stream_world_e;

typedef struct 
{	// feature defined per instance
   uint32_t qsct_width;
   uint32_t sid_width;
   uint32_t ssid_width;
}feature_set;

typedef struct 
{
   qsmmu_ss_e ss;
   uint32_t inst_idx;	// index of instance inside a subsystem
   system_profile *p_sys_profile;

   feature_set feature;	// point to constant data
   uint64_t s_reg_base;
   uint64_t ns_reg_base;

   // each queue entry is 16 bytes long
   cmdq_profile cmdq;
   eventq_profile eventq;

   uint64_t ns_strtab_base;	// 64 Bytes align, each STE is 64 Bytes
   strtab_cfg ns_strtab_base_cfg;
   uint64_t s_strtab_base;	// 64 Bytes align, each STE is 64 Bytes
   strtab_cfg s_strtab_base_cfg;

   msi_cfg ns_eventq_irq;
   msi_cfg s_eventq_irq;
   msi_cfg ns_error_irq;
   msi_cfg s_error_irq;
}qsmmu_profile;

typedef struct 
{
   qsmmu_profile *p_qsmmu_inst;
   uint32_t sid;
   uint32_t ssid;
   uint32_t qactidx;
   stream_world_e stw;
   STE_Type config;
   uint32_t vmid;
   uint32_t asid;
   //STE_S1Fmt s1fmt;
   //STE_STRW strw;

   //struct as_node *p_as;
   // if config == bypass
   //    both ttb are NULL, won't cover this by now
   // if config == stage1
   //    at least ttb0 is valid, its p_vttb point to same stage2 ttb
   // if config == stage2
   //    stage1 is bypassed, p_ttb0 is stage2 ttb.
   // if config == nested
   //    p_ttb0/1 both valid, their p_vttb point to same stage2 ttb
   ttb_profile * p_ttb0;  
   ttb_profile * p_ttb1;
   uint64_t s1cdptr;
   uint64_t tt_mair;
   // s1cir, s1cor, s1csh
   STE_CxR cir, cor;
   STE_CSH csh;
   // override options
   int mtcfg;
   STE_MemAttr memattr;
   STE_AllocCfg alloccfg;
   STE_ShCfg shcfg;
   STE_NSCfg ste_nscfg;	//ignored when stream is non-secure
   STE_PrivCfg privcfg;
   STE_InstCfg instcfg;

   STE_StallD stalld;
   STE_EATS eats;

   STE_S2S s2s;

   CD_AFFD affd;
   CD_ARS ars;
   CD_ASET aset;
}stream_profile;

//typedef struct vm_node 
//{
//   uint32_t vmid;
//   uint64_t s2ttb;
//   STE_S2TG s2tg;
//   uint64_t s1cdptr;
//   struct as_node *p_as_head;
//   struct vm_node *p_next;
//}vm_profile;

//typedef struct as_node
//{
//   stream_world_e stw;
//   uint32_t asid;
//   uint64_t ttb0;
//   uint64_t ttb1;
//   CD_TG0 cd_tg0;
//   CD_TG1 cd_tg1;
//   struct as_node *p_next;
//   vm_profile *p_vm;
//
//}as_profile;

// how to use vm_profile and as_profile
// there are five stream world
// NS_EL1, as+vm, non-secure
// EL2, none, non-secure, only use TTB0
// EL2-ELH, as, non-secure
// S_EL1, as, secure
// EL3, none, secure, only use TTB0
#endif
