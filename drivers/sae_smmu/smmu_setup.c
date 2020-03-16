#include "VVDRV_qsmmuv3_profile_dvm.h"
#include "msmhwiobase.h"
#include "asm/hal/HALhwio.h"
#include "VVDRV_qsmmuv3_program_dvm.h"
#include "VVDRV_qsmmuv3_TT_dvm.h"
#include "VVDRV_qsmmuv3_common_dvm.h"
#include "hdts_shell.h"
#include "hdts_common.h"
//#include <target/mmu.h>
//#include <target/mmu_port.h>
static stream_profile smx0_stream_rddt;
static stream_profile smx0_stream_rdata;
static stream_profile smx0_stream_wdata;
static ttb_profile  smx0_ttb_profile;
static system_profile sys_profile;
static qsmmu_profile qsmmu_inst;
void smmu_initialize(uint64_t ste_base,uint64_t ste_size,uint64_t queue_base,uint64_t queue_size,uint64_t cd_base,uint64_t cd_size)
{
  // init qsmmu profile and instance
  qsmmu_ss_e ss_e = QSMMU_CRYPTO;
  uint32_t inst_idx = 0;
  int smx0_stage = 1;
  int smx0_stw = SW_EL3;
  int smx0_ste_type = STE_TYPE_STAGE1;
  shell_msg("VVDRV_qsmmuv3_api_init.\n");
  smmu_profile s_profile;
  s_profile.s_cd_alloc_base = cd_base;
  s_profile.s_cd_alloc_limit = cd_base + cd_size;
  s_profile.s_st_alloc_base = ste_base;
  s_profile.s_st_alloc_limit = ste_base + ste_size;
  s_profile.s_queue_alloc_base = queue_base;
  s_profile.s_queue_alloc_limit = queue_base + queue_size;
  VVDRV_qsmmuv3_api_init(&sys_profile,0,s_profile);
  shell_msg( "VVDRV_qsmmuv3_set_qsmmu\n");
  VVDRV_qsmmuv3_set_qsmmu(&qsmmu_inst, ss_e, inst_idx);
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu\n");
  VVDRV_qsmmuv3_init_qsmmu(&qsmmu_inst);

  shell_msg( "VVDRV_qsmmuv3_init_stream\n");
  VVDRV_qsmmuv3_init_stream(&smx0_stream_rddt , ss_e, inst_idx);
  VVDRV_qsmmuv3_init_stream(&smx0_stream_rdata, ss_e, inst_idx);
  VVDRV_qsmmuv3_init_stream(&smx0_stream_wdata, ss_e, inst_idx);

  shell_msg("for test:\n");
  uint64_t stptr;
  qsmmu_profile *profile;
  profile = smx0_stream_rddt.p_qsmmu_inst;
  stptr = profile->s_strtab_base;
  shell_msg("s_strtab_base=0x%02x_%02x\n",stptr>>32,stptr);

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

  smx0_stream_rddt.asid  = 5;
  smx0_stream_rdata.asid = 5;
  smx0_stream_wdata.asid = 5;
  smx0_stream_rddt.p_ttb0  = &smx0_ttb_profile;
  smx0_stream_rdata.p_ttb0 = &smx0_ttb_profile;
  smx0_stream_wdata.p_ttb0 = &smx0_ttb_profile;

  VVDRV_qsmmuv3_init_ttb(&smx0_ttb_profile, TT_TG_4K, CD_TxSZ_44, smx0_stage, NULL, NULL);
}
void smmu_switch_tables(uint64_t pt_base)
{
  //stream_profile smx0_stream_rddt;
  //stream_profile smx0_stream_rdata;
  //stream_profile smx0_stream_wdata;
  uint64_t cdptr,stptr;
  vm_profile *p_vm;
  ttb_profile * p_ttb;
  p_ttb = smx0_stream_rddt.p_ttb0;
  p_vm = p_ttb->p_vm_profile;
  cdptr = p_vm->s_cd_alloc_ptr;
  qsmmu_profile *profile;
  profile = smx0_stream_rddt.p_qsmmu_inst;
  stptr = profile->s_strtab_base;
  shell_msg("s_cd_alloc_ptr=0x%02x_%02x,s_strtab_base=0x%02x_%02x\n",cdptr>>32,cdptr,stptr>>32,stptr);
  VVDRV_qsmmuv3_program_stream(&smx0_stream_rddt,pt_base);
  VVDRV_qsmmuv3_program_stream(&smx0_stream_rdata,pt_base);
  VVDRV_qsmmuv3_program_stream(&smx0_stream_wdata,pt_base);
}
