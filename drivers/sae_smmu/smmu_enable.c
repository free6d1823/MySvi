#include "VVDRV_qsmmuv3_profile_dvm.h"
#include "msmhwiobase.h"
//#include <HALhwio.h>
#include "VVDRV_qsmmuv3_program_dvm.h"
#include "VVDRV_qsmmuv3_TT_dvm.h"
#include "VVDRV_qsmmuv3_common_dvm.h"
#include "hdts_shell.h"
#include "hdts_common.h"
//#define SMMU_SMX0_NS
//#define ACCESS_DDR
#define IMC_MSA_CTRL       0xFF6FBC0300
//extern void shell_msg(const char *fmt, ...);
stream_profile smx0_stream_rddt;
stream_profile smx0_stream_rdata;
stream_profile smx0_stream_wdata;
ttb_profile  smx0_ttb_profile;
void smmu_test(uint64_t smx0_dma_ddt_src_va,uint64_t smx0_dma_ddt_dst_va,uint64_t smx0_dma_data_src_va,
    uint64_t smx0_dma_data_dst_va,uint64_t* pa_addr,int imem)
{	
  uint32_t smx0_proc_len = 32;//0x1000;//0x1000000;//0x100000;//0x4000;//32;
  uint32_t smx0_dma_ddt_src_offset   = smx0_dma_ddt_src_va  & 0xFFF;
  uint32_t smx0_dma_ddt_dst_offset   = smx0_dma_ddt_dst_va  & 0xFFF;
  uint32_t smx0_dma_data_src_offset  = smx0_dma_data_src_va & 0xFFF;
  uint32_t smx0_dma_data_dst_offset  = smx0_dma_data_dst_va & 0xFFF;
  uint64_t smx0_dma_ddt_base_va      = smx0_dma_ddt_src_va  & 0xffffffff000;
  uint64_t smx0_dma_ddt_base_pa;
  uint64_t smx0_dma_ddt_src_pa; uint64_t smx0_dma_ddt_dst_pa;

  uint64_t smx0_dma_data_src_base_va = smx0_dma_data_src_va & 0xffffffff000; 
  uint64_t smx0_dma_data_dst_base_va = smx0_dma_data_dst_va & 0xffffffff000;
  uint64_t smx0_dma_data_src_pa;
  uint64_t smx0_dma_data_dst_pa;
  shell_msg( "start of smmu program\n");
  VVDRV_qsmmuv3_enable_A53_protns_passthrough();
  *((unsigned int*)IMC_MSA_CTRL) = 0x3;
  shell_msg( "ring bringup & boot addr");
  // init system profile
  system_profile sys_profile;
  uint32_t inIMEM = imem;
  VVDRV_qsmmuv3_api_init(&sys_profile, inIMEM);
  if(inIMEM==1)
  {
    sys_profile.hyper_profile.tt_4k_alloc_base =  0xFF70036000;//0x0FF7000D000;
    sys_profile.hyper_profile.tt_4k_alloc_limit = 0xFF70039FFF;//0x0FF7002FFFF;
    sys_profile.hyper_profile.tt_4k_alloc_ptr =   0xFF70036000;//0x0FF7000D000;
    sys_profile.hyper_profile.tt_64k_alloc_base = 0;
    sys_profile.hyper_profile.tt_64k_alloc_limit = 0;
    sys_profile.hyper_profile.tt_64k_alloc_ptr = 0;
    sys_profile.hyper_profile.page_4k_alloc_base = 0xFF7003B000;//0x0FF70030000;
    sys_profile.hyper_profile.page_4k_alloc_limit = 0xFF7003FFFF;//0x0FF7003FFFF ;
    sys_profile.hyper_profile.page_4k_alloc_ptr =  0xFF7003B000;//0x0FF70030000;
  }
  // init qsmmu profile and instance
  qsmmu_ss_e ss_e = QSMMU_CRYPTO;
  uint32_t inst_idx = 0;
  qsmmu_profile qsmmu_inst;
  shell_msg( "VVDRV_qsmmuv3_set_qsmmu\n");
  VVDRV_qsmmuv3_set_qsmmu(&qsmmu_inst, ss_e, inst_idx);
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu\n");
  VVDRV_qsmmuv3_init_qsmmu(&qsmmu_inst);
  int smx0_stage = 0;
  int smx0_stw = 0;
  int smx0_ste_type = 0;
  smx0_stage = 1;
#ifdef SMMU_SMX0_QAD
  smx0_stw = SW_QAD;
#else
#ifdef SMMU_SMX0_NS
  smx0_stw = SW_NS_EL1;
#else
  smx0_stw = SW_S_EL1;
#endif
#endif
  smx0_ste_type = STE_TYPE_STAGE1;

  //stream_profile smx0_stream_rddt;
  //stream_profile smx0_stream_rdata;
  //stream_profile smx0_stream_wdata;

  shell_msg( "VVDRV_qsmmuv3_init_stream\n");

  VVDRV_qsmmuv3_init_stream(&smx0_stream_rddt , ss_e, inst_idx);
  VVDRV_qsmmuv3_init_stream(&smx0_stream_rdata, ss_e, inst_idx);
  VVDRV_qsmmuv3_init_stream(&smx0_stream_wdata, ss_e, inst_idx);

  smx0_stream_rddt.sid = 5; //CES0_SMX
  smx0_stream_rddt.qactidx = 5; //CES0_SMX
  smx0_stream_rddt.stw    = smx0_stw;
  smx0_stream_rddt.config = smx0_ste_type;
  VVDRV_qsmmuv3_program_qact(&smx0_stream_rddt);
  smx0_stream_rdata.sid = 4; //CES0_SMX
  smx0_stream_rdata.qactidx = 4; //CES0_SMX
  smx0_stream_rdata.stw    = smx0_stw;
  smx0_stream_rdata.config = smx0_ste_type;
  VVDRV_qsmmuv3_program_qact( &smx0_stream_rdata);
  smx0_stream_wdata.sid = 6; //CES0_SMX
  smx0_stream_wdata.qactidx = 6; //CES0_SMX
  smx0_stream_wdata.stw    = smx0_stw;
  smx0_stream_wdata.config = smx0_ste_type;
  VVDRV_qsmmuv3_program_qact( &smx0_stream_wdata);
  //ttb_profile  smx0_ttb_profile;
  ttb_profile  smx0_vttb;
  vm_profile   smx0_vm;
  ttb_profile* smx0_p_vttb = 0;
  vm_profile*  smx0_p_vm = 0;
  uint32_t SMMU_EN = 1;
  if (SMMU_EN == 3) {
    smx0_p_vm   = &smx0_vm;
    smx0_p_vttb = &smx0_vttb;
    VVDRV_qsmmuv3_vm_profile_default(smx0_p_vm, 0);
    VVDRV_qsmmuv3_init_ttb(smx0_p_vttb, TT_TG_4K, CD_TxSZ_44, 2, NULL, NULL);
    smx0_stream_rddt.vmid  = 1;
    smx0_stream_rdata.vmid = 1;
    smx0_stream_wdata.vmid = 1;
  }
  else if (SMMU_EN == 1) {
    smx0_stream_rddt.asid  = 5;
    smx0_stream_rdata.asid = 5;
    smx0_stream_wdata.asid = 5;
    smx0_stream_rddt.p_ttb0  = &smx0_ttb_profile;
    smx0_stream_rdata.p_ttb0 = &smx0_ttb_profile;
    smx0_stream_wdata.p_ttb0 = &smx0_ttb_profile;
  }

  VVDRV_qsmmuv3_init_ttb(&smx0_ttb_profile, TT_TG_4K, CD_TxSZ_44, smx0_stage, smx0_p_vm, smx0_p_vttb);
  // add VA space that client want to access
  shell_msg( "VVDRV_qsmmuv3_createpage\n");
  smx0_dma_ddt_base_pa = VVDRV_qsmmuv3_create_page(&smx0_ttb_profile, smx0_dma_ddt_base_va);
  smx0_dma_ddt_src_pa  = smx0_dma_ddt_base_pa + smx0_dma_ddt_src_offset;
  smx0_dma_ddt_dst_pa  = smx0_dma_ddt_base_pa + smx0_dma_ddt_dst_offset;
  smx0_dma_data_src_pa = VVDRV_qsmmuv3_create_page(&smx0_ttb_profile, smx0_dma_data_src_base_va) + smx0_dma_data_src_offset;
  // if cross 4KB boundary, alllocated PA of two pages are continuous for stage 1 or stage 2 only
  // but for nested, they are value likely gapped, which may cause problem for their checking
  int n=0;
  int offset_len = smx0_proc_len+smx0_dma_data_src_offset;
  while(1){
    offset_len = offset_len-4096;
    if(offset_len> 0) {
      VVDRV_qsmmuv3_create_page(&smx0_ttb_profile, smx0_dma_data_src_va + 4096*(n+1));
      n=n+1;
    }
    else
      break;
  }
  smx0_dma_data_dst_pa = VVDRV_qsmmuv3_create_page(&smx0_ttb_profile, smx0_dma_data_dst_base_va) + smx0_dma_data_dst_offset;
  if ((smx0_dma_data_dst_offset + 32) >= 4096)
    VVDRV_qsmmuv3_create_page(&smx0_ttb_profile, smx0_dma_data_dst_va + 4096);
  shell_msg( "VVDRV_qsmmuv3_program_stream\n");
  VVDRV_qsmmuv3_program_stream(&smx0_stream_rddt,0);
  VVDRV_qsmmuv3_program_stream(&smx0_stream_rdata,0);
  VVDRV_qsmmuv3_program_stream(&smx0_stream_wdata,0);
  shell_msg( "[SMX0] smx0_dma_data_src_va = 0x%0x_%0x\n",(smx0_dma_data_src_va>>32),smx0_dma_data_src_va );
  shell_msg( "[SMX0] smx0_dma_data_dst_va = 0x%0x_%0x\n",(smx0_dma_data_dst_va>>32),smx0_dma_data_dst_va );
  shell_msg( "[SMX0] smx0_dma_data_src_pa = 0x%0x_%0x\n",(smx0_dma_data_src_pa>>32),smx0_dma_data_src_pa );
  shell_msg( "[SMX0] smx0_dma_data_dst_pa = 0x%0x_%0x\n",(smx0_dma_data_dst_pa>>32),smx0_dma_data_dst_pa );
  shell_msg( "[SMX0] smx0_dma_ddt_src_va= 0x%0x_%0x\n",(smx0_dma_ddt_src_va>>32),smx0_dma_ddt_src_va);
  shell_msg( "[SMX0] smx0_dma_ddt_src_pa= 0x%0x_%0x\n",(smx0_dma_ddt_src_pa>>32),smx0_dma_ddt_src_pa);
  shell_msg( "[SMX0] smx0_dma_ddt_dst_va= 0x%0x_%0x\n",(smx0_dma_ddt_dst_va>>32),smx0_dma_ddt_dst_va);
  shell_msg( "[SMX0] smx0_dma_ddt_dst_pa= 0x%0x_%0x\n",(smx0_dma_ddt_dst_pa>>32),smx0_dma_ddt_dst_pa);
  shell_msg( "[SMX0] smx0_dma_ddt_src_offset= 0x%0x\n",smx0_dma_ddt_src_offset);
  shell_msg( "[SMX0] smx0_dma_ddt_dst_offset= 0x%0x\n",smx0_dma_ddt_dst_offset);

  pa_addr[0] = (uint64_t)smx0_dma_ddt_src_pa;
  pa_addr[1] = (uint64_t)smx0_dma_ddt_dst_pa;
  pa_addr[2] = (uint64_t)smx0_dma_data_src_pa;
  pa_addr[3] = (uint64_t)smx0_dma_data_dst_pa;
  //read SMMU_S_IDR0
  uint32_t idr0 = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x0));
  uint32_t idr0_s = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x8000));
  uint32_t idr1 = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x4));
  uint32_t idr1_s = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x8004));
  uint32_t idr2 = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x8));
  uint32_t idr2_s = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x8008));
  uint32_t idr3 = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0xC));
  uint32_t idr3_s = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x800C));
  uint32_t idr4 = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x10));
  uint32_t idr4_s = *((volatile unsigned int*)(CRYPTO0_QSMMU_BASE+0x8010));
  shell_msg("idr0,1,2,3,4=%0x2,%02x,%02x,%0x2,%02x.\n",idr0,idr1,idr2,idr3,idr4);
  shell_msg("idr0_s,1,2,3,4=%0x2,%02x,%02x,%0x2,%02x.\n",idr0_s,idr1_s,idr2_s,idr3_s,idr4_s);
  return ;
}

void smmu_ste_invalid()
{
  uint64_t ste_base;
  uint64_t ste_index;
  stream_profile *p_stream;
  p_stream = &smx0_stream_rdata;
  qsmmu_profile* p_qsmmu_inst = p_stream->p_qsmmu_inst;
  ste_base = (p_stream->stw >= SW_S_EL1) ? p_qsmmu_inst->s_strtab_base : p_qsmmu_inst->ns_strtab_base;
  ste_index = p_stream->sid;
  VVDRV_qsmmuv3_writeSTE_invalid(ste_base,ste_index);
}

uint64_t smmu_pagetable_invalid(uint64_t smx0_dma_data_dst_va)
{
  uint64_t smx0_dma_data_dst_pa;
  uint32_t smx0_dma_data_dst_offset  = smx0_dma_data_dst_va & 0xFFF;
  uint64_t smx0_dma_data_dst_base_va = smx0_dma_data_dst_va & 0xffffffff000;
  //system_profile* sys_profile = VVDRV_qsmmuv3_get_sys_profile(0);
  //shell_msg("page_4k_alloc_base=%02x,tt_4k_alloc_base=%02x.\n",sys_profile->hyper_profile.page_4k_alloc_base,sys_profile->hyper_profile.tt_4k_alloc_base);
  //sys_profile->hyper_profile.page_4k_alloc_base = 0x1b000000;
  //sys_profile->hyper_profile.page_4k_alloc_limit = 0x1c000000;
  //sys_profile->hyper_profile.page_4k_alloc_ptr = 0x1b000000;
  //smx0_ttb_profile.p_vm_profile = &(sys_profile->hyper_profile);

  uint64_t page_4k_alloc_base = smx0_ttb_profile.p_vm_profile->page_4k_alloc_base;
  uint64_t tt_4k_alloc_base = smx0_ttb_profile.p_vm_profile->tt_4k_alloc_base;
  shell_msg("page_4k_alloc_base=0x%02x_%02x,tt_4k_alloc_base=0x%02x_%02x.\n",(uint32_t)(page_4k_alloc_base>>32),(uint32_t)page_4k_alloc_base,(uint32_t)(tt_4k_alloc_base>>32),(uint32_t)tt_4k_alloc_base);
  shell_msg("tt_base=%02x,stage=%02x.\n",smx0_ttb_profile.ttb_addr,smx0_ttb_profile.stage);

  //init stream
  //stream_profile smx0_stream_wdata_1;
  //VVDRV_qsmmuv3_init_stream(&smx0_stream_wdata_1, ss_e, inst_idx);
  //smx0_stream_wdata_1.sid = 6; //CES0_SMX
  //smx0_stream_wdata_1.qactidx = 6; //CES0_SMX
  //smx0_stream_wdata_1.stw    = smx0_stw;
  //smx0_stream_wdata_1.config = smx0_ste_type;
  //VVDRV_qsmmuv3_program_qact( &smx0_stream_wdata_1);
  //smx0_stream_wdata_1.asid = 5;
  //init ttb
  ttb_profile  smx0_ttb_profile_1;
  system_profile sys_profile;
  VVDRV_qsmmuv3_api_init(&sys_profile, 0);
  sys_profile.hyper_profile.tt_4k_alloc_base = 0x18086000;
  sys_profile.hyper_profile.tt_4k_alloc_limit = 0x18096000;
  sys_profile.hyper_profile.tt_4k_alloc_ptr = 0x18086000;
  sys_profile.hyper_profile.page_4k_alloc_base = 0x1b000000;
  sys_profile.hyper_profile.page_4k_alloc_limit = 0x1c000000;
  sys_profile.hyper_profile.page_4k_alloc_ptr = 0x1b000000;
  int smx0_stage = 1;
  ttb_profile* smx0_p_vttb = 0;
  vm_profile*  smx0_p_vm = 0;
  VVDRV_qsmmuv3_init_ttb(&smx0_ttb_profile_1, TT_TG_4K, CD_TxSZ_44, smx0_stage, smx0_p_vm, smx0_p_vttb);
  //print ttb
  page_4k_alloc_base = smx0_ttb_profile_1.p_vm_profile->page_4k_alloc_base;
  tt_4k_alloc_base = smx0_ttb_profile_1.p_vm_profile->tt_4k_alloc_base;
  shell_msg("page_4k_alloc_base=0x%02x_%02x,tt_4k_alloc_base=0x%02x_%02x.\n",(uint32_t)(page_4k_alloc_base>>32),(uint32_t)page_4k_alloc_base,(uint32_t)(tt_4k_alloc_base>>32),(uint32_t)tt_4k_alloc_base);

  smx0_dma_data_dst_pa = VVDRV_qsmmuv3_create_page(&smx0_ttb_profile_1, smx0_dma_data_dst_base_va) + smx0_dma_data_dst_offset;
  shell_msg("smx0_dma_data_dst_pa=0x%02x_%02x.\n",(uint32_t)(smx0_dma_data_dst_pa>>32),(uint32_t)smx0_dma_data_dst_pa);
  smx0_stream_wdata.p_ttb0 = &smx0_ttb_profile_1;
  VVDRV_qsmmuv3_program_stream(&smx0_stream_wdata,0);
  return smx0_dma_data_dst_pa;
}

void smmu_invalid_TLB()
{
  stream_profile *p_stream;
  p_stream = &smx0_stream_rdata;
  qsmmu_profile* p_qsmmu_inst = p_stream->p_qsmmu_inst;
  uint64_t reg_base;
  reg_base = p_qsmmu_inst->s_reg_base;
  VVDRV_qsmmuv3_DVM_CMDQ(reg_base,2,0,0,0,1);
}

void smmu_check_event()
{
  stream_profile *p_stream;
  p_stream = &smx0_stream_rdata;
  qsmmu_profile* p_qsmmu_inst = p_stream->p_qsmmu_inst;
  VVDRV_qsmmuv3_check_eventq(p_qsmmu_inst);
}
