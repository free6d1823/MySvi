#include "VVDRV_qsmmuv3_program_dvm.h"
#include "VVDRV_qsmmuv3_TT_dvm.h"
//#include "VVDRV_qsmmuv3_imc_spi.h"
#include "VVDRV_qsmmuv3_irpt_dvm.h"
#include "qsmmuv3_hwioreg.h"
#include "asm/hal/HALhwio.h"
#include "msmhwioreg.h"
#include "hdts_shell.h"
#include "hdts_common.h"

//#define outp64(port, val) (*((volatile uint64_t *) (port)) = ((uint64_t) (val)))

#define IMC_MSA_CTRL                              (0xFF6FBC0300)
#define vv_msg_FILE_NUMBER 200
#define MAX_QSMMU_INST_SS 8
system_profile *p_sys_profile_global;
qsmmu_profile *qsmmu_inst_list[QSMMU_NUM][MAX_QSMMU_INST_SS];
//void smmu_default_interrupt_isr(void);
#define IMC_QGIC2_MSI_SETSPI_NS_ADDR	0xFF6FA80040
#define APC_QGICDR_SETSPI_NS_ADDR	0xFF7EFD0040
#define APC_QGICDR_SETSPI_S_ADDR	0xFF7EFD0050
#define TCSR_FABRIC_INTR                256

#define CE0_QSMMU_CMD_SIRQ_IMC     357
#define CE0_QSMMU_CMD_NSIRQ_IMC    358
#define CE0_EXPECT_MSI             1
#define EMAC0_QSMMU_CMD_SIRQ_IMC     371
#define EMAC0_QSMMU_CMD_NSIRQ_IMC    372
#define EMAC0_EXPECT_MSI             0
#define EMAC1_QSMMU_CMD_SIRQ_IMC     378
#define EMAC1_QSMMU_CMD_NSIRQ_IMC    379
#define EMAC1_EXPECT_MSI             0
#define HDMA0_QSMMU_CMD_SIRQ_IMC     385
#define HDMA0_QSMMU_CMD_NSIRQ_IMC    386
#define HDMA0_EXPECT_MSI             1
#define HDMA1_QSMMU_CMD_SIRQ_IMC     392
#define HDMA1_QSMMU_CMD_NSIRQ_IMC    393
#define HDMA1_EXPECT_MSI             1
#define HDMA2_QSMMU_CMD_SIRQ_IMC     399
#define HDMA2_QSMMU_CMD_NSIRQ_IMC    400
#define HDMA2_EXPECT_MSI             1
#define HDMA3_QSMMU_CMD_SIRQ_IMC     406
#define HDMA3_QSMMU_CMD_NSIRQ_IMC    407
#define HDMA3_EXPECT_MSI             1
#define IMCSS_QSMMU_CMD_SIRQ_IMC     413
#define IMCSS_QSMMU_CMD_NSIRQ_IMC    414
#define IMCSS_EXPECT_MSI             0
#define PCIE0_QSMMU_CMD_SIRQ_IMC     420
#define PCIE0_QSMMU_CMD_NSIRQ_IMC    421
#define PCIE0_EXPECT_MSI             1
#define PCIE1_QSMMU_CMD_SIRQ_IMC     427
#define PCIE1_QSMMU_CMD_NSIRQ_IMC    428
#define PCIE1_EXPECT_MSI             1
#define PCIE2QSMMU_CMD_SIRQ_IMC     434
#define PCIE2QSMMU_CMD_NSIRQ_IMC    435
#define PCIE2EXPECT_MSI             1
#define PCIE3_QSMMU_CMD_SIRQ_IMC     452
#define PCIE3_QSMMU_CMD_NSIRQ_IMC    453
#define PCIE3_EXPECT_MSI             1
#define PCIE4_QSMMU_CMD_SIRQ_IMC     460
#define PCIE4_QSMMU_CMD_NSIRQ_IMC    461
#define PCIE4_EXPECT_MSI             1
#define PCIE5_QSMMU_CMD_SIRQ_IMC     468
#define PCIE5_QSMMU_CMD_NSIRQ_IMC    469
#define PCIE5_EXPECT_MSI             1
#define PSS_QSMMU_CMD_SIRQ_IMC     484
#define PSS_QSMMU_CMD_NSIRQ_IMC    485
#define PSS_EXPECT_MSI             1
#define SATA0_QSMMU_CMD_SIRQ_IMC     491
#define SATA0_QSMMU_CMD_NSIRQ_IMC    492
#define SATA0_EXPECT_MSI             1
#define SATA1_QSMMU_CMD_SIRQ_IMC     498
#define SATA1_QSMMU_CMD_NSIRQ_IMC    499
#define SATA1_EXPECT_MSI             1
#define SATA2_QSMMU_CMD_SIRQ_IMC     505
#define SATA2_QSMMU_CMD_NSIRQ_IMC    506
#define SATA2_EXPECT_MSI             1
#define SATA3_QSMMU_CMD_SIRQ_IMC     512
#define SATA3_QSMMU_CMD_NSIRQ_IMC    513
#define SATA3_EXPECT_MSI             1
#define SATA4_QSMMU_CMD_SIRQ_IMC     519
#define SATA4_QSMMU_CMD_NSIRQ_IMC    520
#define SATA4_EXPECT_MSI             1
#define SATA5_QSMMU_CMD_SIRQ_IMC     526
#define SATA5_QSMMU_CMD_NSIRQ_IMC    527
#define SATA5_EXPECT_MSI             1
#define SATA6_QSMMU_CMD_SIRQ_IMC     533
#define SATA6_QSMMU_CMD_NSIRQ_IMC    534
#define SATA6_EXPECT_MSI             1
#define SATA7_QSMMU_CMD_SIRQ_IMC     540
#define SATA7_QSMMU_CMD_NSIRQ_IMC    541
#define SATA7_EXPECT_MSI             1

#define GERROR_MSI_SPI
#define EVENTQ_MSI_SPI
extern void VVDRV_qsmmuv3_TableQueueAttributes(uint64_t reg_base, SH_ATTR table_sh, CH_ATTR table_oc, CH_ATTR table_ic, SH_ATTR queue_sh, CH_ATTR queue_oc, CH_ATTR queue_ic, uint32_t secure);
void VVDRV_qsmmuv3_api_init(system_profile *p_sys_profile, uint32_t inIMEM,smmu_profile profile)
{
  shell_msg( "calling VVDRV_qsmmuv3_api_init\n");
  p_sys_profile_global = p_sys_profile;
  for (int i=0; i<QSMMU_NUM; i++)
  {
    for (int j=0; j<MAX_QSMMU_INST_SS; j++)
    {
      qsmmu_inst_list[i][j] = NULL;
      //shell_msg( "init qsmmu_inst_list[%0d][%0d] = 0x%x", i, j, qsmmu_inst_list[i][j]);
    }
  }
  VVDRV_qsmmuv3_sys_profile_default(p_sys_profile_global, inIMEM,profile);
}

void VVDRV_qsmmuv3_vm_profile_default(vm_profile *p_vm_profile, uint32_t inIMEM,smmu_profile profile)
{
  if (p_vm_profile == NULL)
  {
    // report error
    //vv_msg(SEV_ERROR, ST_FUNCTION, "p_sys_profile NULL in VVDRV_qsmmuv3_sys_profile_default\n");
    return;
  }
  if (inIMEM)
  {
    p_vm_profile->tt_4k_alloc_base = 0xFF70036000;//0x0FF7000D000;
    p_vm_profile->tt_4k_alloc_limit = 0xFF70039FFF;//0x0FF7001CFFF;
    p_vm_profile->tt_16k_alloc_base = 0;
    p_vm_profile->tt_16k_alloc_limit = 0;
    p_vm_profile->tt_64k_alloc_base = 0x0FF70030000;   // one 64KB page, reserved for IMC TT
    p_vm_profile->tt_64k_alloc_limit = 0x0FF7003FFFF;

    p_vm_profile->page_4k_alloc_base = 0xFF7003B000;//0x0FF7001D000;
    p_vm_profile->page_4k_alloc_limit = 0xFF7003FFFF;//0x0FF7002FFFF;
    p_vm_profile->page_16k_alloc_base = 0;
    p_vm_profile->page_16k_alloc_limit = 0;
    p_vm_profile->page_64k_alloc_base = 0;
    p_vm_profile->page_64k_alloc_limit = 0;
    // for CD, only PCIE support SSID, will no support this case in IMEM
    // for other subsystem, multiple STE can point to same CD, 
    // so CD number is no more than STE
    p_vm_profile->ns_cd_alloc_base = 0xFF7003A000;//0x0FF70004000;
    p_vm_profile->ns_cd_alloc_limit = 0xFF7003AFFF;//0x0FF70004FFF;
    p_vm_profile->s_cd_alloc_base = 0xFF7003A000;//0x0FF7000B000;
    p_vm_profile->s_cd_alloc_limit = 0xFF7003AFFF;//0x0FF7000BFFF;
  }
  else {      
    p_vm_profile->tt_4k_alloc_base =  0x18036000;//0x11000000;//0x0900000000;
    p_vm_profile->tt_4k_alloc_limit = 0x18046000;//0x11003FFF;//0x093FFFFFFF;
    p_vm_profile->tt_16k_alloc_base = 0;//0x0940000000;
    p_vm_profile->tt_16k_alloc_limit = 0;//0x095FFFFFFF;
    p_vm_profile->tt_64k_alloc_base = 0x18030000;//0x12000000;//0x0960000000;
    p_vm_profile->tt_64k_alloc_limit = 0x1803FFFF;//0x1200FFFF;//0x097FFFFFFF;

    p_vm_profile->page_4k_alloc_base =    0x1A000000;//0x11005000;//0x0100000000;
    p_vm_profile->page_4k_alloc_limit =   0x1B000000;//0x11009FFF;//0x04FFFFFFFF;
    p_vm_profile->page_16k_alloc_base =   0;//0x0500000000;
    p_vm_profile->page_16k_alloc_limit =  0;//0x06FFFFFFFF;
    p_vm_profile->page_64k_alloc_base =   0;//0x0700000000;
    p_vm_profile->page_64k_alloc_limit =  0;//0x08FFFFFFFF;

    p_vm_profile->ns_cd_alloc_base =  0x1803A000;//0x1100a000;//0x1000800000;
    p_vm_profile->ns_cd_alloc_limit = 0x1803AFFF;//0x1100aFFF;//0x1000FFFFFF;

    p_vm_profile->s_cd_alloc_base = profile.s_cd_alloc_base;//  0x101c4000;//0x18046000;//0x1100a000;//0x1010800000;
    p_vm_profile->s_cd_alloc_limit = profile.s_cd_alloc_limit;// 0x101cd000;//0x1804FFFF;//0x1100aFFF;//0x1010FFFFFF;     
  }
  p_vm_profile->tt_4k_alloc_ptr = p_vm_profile->tt_4k_alloc_base;
  p_vm_profile->tt_16k_alloc_ptr = p_vm_profile->tt_16k_alloc_base;
  p_vm_profile->tt_64k_alloc_ptr = p_vm_profile->tt_64k_alloc_base;
  p_vm_profile->page_4k_alloc_ptr = p_vm_profile->page_4k_alloc_base;
  p_vm_profile->page_16k_alloc_ptr = p_vm_profile->page_16k_alloc_base;
  p_vm_profile->page_64k_alloc_ptr = p_vm_profile->page_64k_alloc_base;
  p_vm_profile->ns_cd_alloc_ptr = p_vm_profile->ns_cd_alloc_base;
  p_vm_profile->s_cd_alloc_ptr = p_vm_profile->s_cd_alloc_base;
}

void VVDRV_qsmmuv3_sys_profile_default(system_profile *p_sys_profile, uint32_t inIMEM,smmu_profile profile)
{
  shell_msg( "VVDRV_qsmmuv3_sys_profile_default p_sys_profile = ");
  uint32_t addr_low, addr_high;
  addr_low = (uint64_t)p_sys_profile & 0xffffffff;
  addr_high = ((uint64_t)p_sys_profile >> 32) & 0xffffffff;
  shell_msg( "0x%0x_%8x\n", addr_high, addr_low);

  if (p_sys_profile == NULL)
  {
    // report error
    //vv_msg(SEV_ERROR, ST_FUNCTION, "p_sys_profile NULL in VVDRV_qsmmuv3_sys_profile_default\n");
    return;
  }
  // how much space is enough?
  // single	STE	CD	CMD	Event	PTE
  // size(B)	64	64	16	32	8
  if (inIMEM)
  {
    // IMEM only use sys IMEM, which is 256KB, 
    // start from 0x0FF_7000_0000
    // end to     0x0FF_7003_FFFF
    // Only plan to cover single QSMMU instance when using IMEM
    // Only plan to cover 4K basic TG when using IMEM

    // for STE, 
    // max SID size is 64K for PCIE, consume 4MB for single secure world linear.
    // max SID size is 256 for HDMA, consume 16KB for single secure world linear.
    // other subsystem SID size is no more than 32, no need to worry.
    // IMEM support STE up to full HDMA, or limited PCIE of max sid_width = 8.
    //
    p_sys_profile->ns_st_alloc_base = 0xFF70030000;//0x0FF70000000;
    p_sys_profile->ns_st_alloc_limit = 0xFF70033FFF;//0x0FF70003FFF;
    // queue size 32 will be enough
    p_sys_profile->ns_queue_alloc_base = 0xFF70035000;//0x0FF70005000;
    p_sys_profile->ns_queue_alloc_limit = 0xFF70035FFF;//0x0FF70005FFF;

    p_sys_profile->s_st_alloc_base = 0xFF70030000;//0x0FF70007000;
    p_sys_profile->s_st_alloc_limit = 0xFF70033FFF;//0x0FF7000AFFF;
    p_sys_profile->s_queue_alloc_base = 0xFF70035000;//0x0FF7000C000;
    p_sys_profile->s_queue_alloc_limit = 0xFF70035FFF;//0x0FF7000CFFF;

  } else 
  {
    // DDR 
    // start from 0x00_0000_0000
    // end to     0xBF_FFFF_FFFF
    // expect to support fully enabled QSMMU
    // but simulation DDR model capacity is limitted
    // 8GBx12 or 32GBx12, minimum address space is
    // 0 - 0x18_0000_0000
    p_sys_profile->ns_st_alloc_base = 	0x18030000;//0x10000000;//0x1000000000;
    p_sys_profile->ns_st_alloc_limit = 	0x18033FFF;//0x107FFFFF;//0x10007FFFFF;
    p_sys_profile->ns_queue_alloc_base = 	0x18035000;//0x10010000;//0x1001000000;
    p_sys_profile->ns_queue_alloc_limit = 0x18035FFF;//0x1001FFFF;//0x1001FFFFFF;

    p_sys_profile->s_st_alloc_base = 		profile.s_st_alloc_base;//0x101be000;//0x18030000;//0x10100000;//0x1010000000;
    p_sys_profile->s_st_alloc_limit = 	profile.s_st_alloc_limit;//0x101c1fff;//0x18033FFF;//0x10107FFF;//0x10107FFFFF;
    p_sys_profile->s_queue_alloc_base = profile.s_queue_alloc_base;//0x101c2000; 	//0x18034000;//0x10110000;//0x1011000000;
    p_sys_profile->s_queue_alloc_limit =profile.s_queue_alloc_limit;//0x101c3fff; 	//0x18035FFF;//0x1011FFFF;//0x1011FFFFFF;

  }
  p_sys_profile->ns_st_alloc_ptr = p_sys_profile->ns_st_alloc_base;
  p_sys_profile->ns_queue_alloc_ptr = p_sys_profile->ns_queue_alloc_base;
  p_sys_profile->s_st_alloc_ptr = p_sys_profile->s_st_alloc_base;
  p_sys_profile->s_queue_alloc_ptr = p_sys_profile->s_queue_alloc_base;

  VVDRV_qsmmuv3_vm_profile_default(&(p_sys_profile->hyper_profile), inIMEM,profile);
}

uint64_t VVDRV_qsmmuv3_alloc_page(tt_tgs_e tgs, vm_profile* p_vm, int b_tt)
{
  uint64_t page_addr_base=0;
  if (b_tt) // allocate for tt
  {
    if (TT_TG_4K == tgs)
    {
      if (p_vm->tt_4k_alloc_ptr > p_vm->tt_4k_alloc_limit)
      {
        shell_msg("VVDRV_qsmmuv3_alloc_page: tt_4k_alloc empty");
        return 0;
      }
      page_addr_base = p_vm->tt_4k_alloc_ptr;
      p_vm->tt_4k_alloc_ptr = p_vm->tt_4k_alloc_ptr + 0x1000;
    }
    if (TT_TG_16K == tgs)
    {
      if (p_vm->tt_16k_alloc_ptr > p_vm->tt_16k_alloc_limit)
      {
        return 0;
      }
      page_addr_base = p_vm->tt_16k_alloc_ptr;
      p_vm->tt_16k_alloc_ptr = p_vm->tt_16k_alloc_ptr + 0x4000;
    }
    if (TT_TG_64K == tgs)
    {
      if (p_vm->tt_64k_alloc_ptr > p_vm->tt_64k_alloc_limit)
      {
        //report error
        //vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_alloc_page: tt_64k_alloc empty");
        return 0;
      }
      page_addr_base = p_vm->tt_64k_alloc_ptr;
      p_vm->tt_64k_alloc_ptr = p_vm->tt_64k_alloc_ptr + 0x10000;
    }
  }
  else  // allocate for data page
  {
    if (TT_TG_4K == tgs)
    {
      if (p_vm->page_4k_alloc_ptr > p_vm->page_4k_alloc_limit)
      {
        shell_msg("VVDRV_qsmmuv3_alloc_page: page_4k_alloc empty");
        return 0;
      }
      page_addr_base = p_vm->page_4k_alloc_ptr;
      p_vm->page_4k_alloc_ptr = p_vm->page_4k_alloc_ptr + 0x1000;
    }
    if (TT_TG_16K == tgs)
    {
      if (p_vm->page_16k_alloc_ptr > p_vm->page_16k_alloc_limit)
      {
        //report error
        //vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_alloc_page: page_16k_alloc empty");
        return 0;
      }
      page_addr_base = p_vm->page_16k_alloc_ptr;
      p_vm->page_16k_alloc_ptr = p_vm->page_16k_alloc_ptr + 0x4000;
    }
    if (TT_TG_64K == tgs)
    {
      if (p_vm->page_64k_alloc_ptr > p_vm->page_64k_alloc_limit)
      {
        //report error
        //vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_alloc_page: page_64k_alloc empty");
        return 0;
      }
      page_addr_base = p_vm->page_64k_alloc_ptr;
      p_vm->page_64k_alloc_ptr = p_vm->page_64k_alloc_ptr + 0x10000;
    }
  }
  //shell_msg( "allocate a new page: page_addr_base = 0x%0x_%8x, tgs = 0x%0x", (page_addr_base >> 32), page_addr_base, tgs);
  //shell_msg( "page_addr_base = 0x%0x_%0x, tgs = 0x%0x", (page_addr_base >> 32), page_addr_base, tgs);
  return page_addr_base;
}

system_profile *VVDRV_qsmmuv3_get_sys_profile(uint32_t inIMEM)
{
  if (p_sys_profile_global == NULL)
  {
    //vv_msg(SEV_ERROR, ST_FUNCTION, "p_sys_profile_global NULL in VVDRV_qsmmuv3_get_sys_profile\n");
  }
  return p_sys_profile_global;
}

qsmmu_profile * VVDRV_qsmmuv3_get_qsmmu(qsmmu_ss_e ss_e, uint32_t idx)
{
  return qsmmu_inst_list[ss_e][idx];
}

void VVDRV_qsmmuv3_set_qsmmu(qsmmu_profile *p_qsmmu_inst, qsmmu_ss_e ss_e, uint32_t idx)
{
  shell_msg( "VVDRV_qsmmuv3_set_qsmmu for p_qsmmu[%0d][%0d] = 0x%x\n", ss_e, idx, qsmmu_inst_list[ss_e][idx]);
  if (p_sys_profile_global == NULL)
  {
    //vv_msg(SEV_ERROR, ST_FUNCTION, "p_sys_profile_global NULL in VVDRV_qsmmuv3_set_qsmmu\n");
    return;
  }
  if (qsmmu_inst_list[ss_e][idx] == NULL)
  {
    // this part should work out
    p_qsmmu_inst->p_sys_profile = p_sys_profile_global;

    p_qsmmu_inst->ss = ss_e;
    p_qsmmu_inst->inst_idx = idx;
    qsmmu_inst_list[ss_e][idx] = p_qsmmu_inst;
    shell_msg( "VVDRV_qsmmuv3_set_qsmmu fill list[%0d][%0d]\n", ss_e, idx);
    VVDRV_qsmmuv3_init_qsmmu_profile(p_qsmmu_inst);
  }
}

void VVDRV_qsmmuv3_init_stream(stream_profile *p_stream, qsmmu_ss_e ss_e, uint32_t idx)
{
  if (p_stream == NULL) {
    //vv_msg(SEV_ERROR, ST_FUNCTION, "p_stream NULL in VVDRV_qsmmuv3_init_stream\n");
    return;
  }
  p_stream->p_qsmmu_inst = VVDRV_qsmmuv3_get_qsmmu(ss_e, idx);
  p_stream->p_ttb0 = NULL;
  p_stream->p_ttb1 = NULL;
  p_stream->s1cdptr = 0;
  p_stream->ssid = 0; // must be 0 for non-pcie, init as 0 for pcie
  p_stream->vmid = 0;
  p_stream->asid = 0;
  p_stream->tt_mair = (uint64_t)CD_MAIR_NORMAL_WBNT_RAWA + ((uint64_t)CD_MAIR_DEVICE_nGnRE << 8) + ((uint64_t)CD_MAIR_DEVICE_nGRE << 16) + ((uint64_t)CD_MAIR_DEVICE_GRE << 24) + ((uint64_t)CD_MAIR_NORMAL_NC << 32) + ((uint64_t)CD_MAIR_NORMAL_WTNT_RAWA << 40) + ((uint64_t)CD_MAIR_NORMAL_WBNT_RA << 48) + ((uint64_t)CD_MAIR_DEVICE_nGnRnE << 56);
  p_stream->cir = STE_CxR_NC;
  p_stream->cor = STE_CxR_NC;
  p_stream->csh = STE_CSH_INNER;//STE_CSH_OUTER; inner-shareable domain for DVM
  p_stream->stalld = STE_STALLD_STALL;
  p_stream->eats = STE_EATS_TERMINATE;	// will enable for PCIE
  p_stream->mtcfg = 0;
  p_stream->memattr = STE_MEMATTR_NORMAL_WB ; //STE_MEMATTR_NORMAL_WB STE_MEMATTR_DEVICE_nGnRnE
  p_stream->alloccfg = STE_ALLOCCFG_INCOMING;
  p_stream->shcfg = STE_SHCFG_INCOMING;//STE_CSH_INNER
  p_stream->privcfg = STE_PRIVCFG_INCOMING;
  p_stream->instcfg = STE_INSTCFG_INCOMING;
  p_stream->ste_nscfg = STE_NSCFG_SECURE;//STE_NSCFG_INCOMING;
  p_stream->s2s = STE_S2S_OFF;
  p_stream->affd = CD_AFFD_DISABLE;  // QSMMU don't support HTTU, we don't test software Access Flag by now. 
  p_stream->ars = CD_ARS_ABORT_RECORD;
  p_stream->aset = CD_ASET_SHARED;
}

void VVDRV_qsmmuv3_program_stream(stream_profile *p_stream,uint64_t pt_base)
{
  if (p_stream == NULL) {
    //vv_msg(SEV_ERROR, ST_FUNCTION, "p_stream NULL in VVDRV_qsmmuv3_program_stream\n");
    return;
  }
  stream_world_e stw = p_stream->stw;
  ttb_profile * p_ttb0 = p_stream->p_ttb0;
  ttb_profile * p_ttb1 = p_stream->p_ttb1;
  ttb_profile * p_vttb = NULL;
  STE_Type config = p_stream->config;
  int en_stage1 = config & 0x1;
  int en_stage2 = config & 0x2;
  //int valid = config & 0x4;
  // first program CD
  if (en_stage1 )
  {
    shell_msg( "VVDRV_qsmmuv3_program_stream CD\n");
    // define CD api parameters
    uint64_t cd_base;
    int cd_index;
    CD_TxSZ t0sz, t1sz;
    CD_TG0 tg0;
    CD_xR ir0, ir1, or0, or1;
    CD_SHx sh0, sh1;
    CD_EPDx epd0, epd1;
    CD_ENDI endi;
    CD_TG1 tg1;
    CD_V cd_v;
    CD_IPS ips;
    CD_AFFD affd;
    CD_WXN wxn;
    CD_UWXN uwxn;
    CD_TBI tbi0, tbi1;
    int pan;
    CD_AA64 aa64;
    CD_HD hd;
    CD_HA ha;
    CD_ARS ars;
    CD_ASET aset;
    int asid;
    CD_NSCFGx nscfg0, nscfg1;
    CD_HADx had0, had1;
    uint64_t ttb0, ttb1;
    CD_MAIR mair0, mair1, mair2, mair3, mair4, mair5, mair6, mair7;

    // set default value
    cd_v = CD_VALID;
    aa64 = CD_AA64_64;	// QSMMU only support AA64
    endi = CD_ENDI_LITTLE;
    ips = CD_IPS_44;
    hd = CD_HD_OFF;
    ha = CD_HA_OFF;
    wxn = CD_WXN_OFF;
    uwxn = CD_UWXN_OFF;
    pan = 0;  // privileged access never
    had0 = CD_HAD_ENABLED;
    had1 = CD_HAD_DISABLED;  // APTable, PXNTable, XNTable/UXNTable ignored

    cd_index = p_stream->ssid; // normally 0 for non-pcie instance
    asid = p_stream->asid;
    affd = p_stream->affd;
    ars = p_stream->ars;
    aset = p_stream->aset;
    uint64_t tt_mair = p_stream->tt_mair;
    mair0 = tt_mair &0xff;
    tt_mair = tt_mair >> 8;
    mair1 = tt_mair &0xff;
    tt_mair = tt_mair >> 8;
    mair2 = tt_mair &0xff;
    tt_mair = tt_mair >> 8;
    mair3 = tt_mair &0xff;
    tt_mair = tt_mair >> 8;
    mair4 = tt_mair &0xff;
    tt_mair = tt_mair >> 8;
    mair5 = tt_mair &0xff;
    tt_mair = tt_mair >> 8;
    mair6 = tt_mair &0xff;
    tt_mair = tt_mair >> 8;
    mair7 = tt_mair &0xff;

    if (NULL == p_ttb0)
      epd0 = CD_EPDx_DISABLE;
    else {
      epd0 = CD_EPDx_ENABLE;
      p_vttb = p_ttb0->p_vttb;
    }

    // stream world
    //    SW_EL2, SW_EL3:  EPD are ignored, None ASID nor VMID, TTD permit priviledged only TTB0
    //    SW_NS_EL1: stage 1 and stage 2 both can be valid, TTD permit all, TTB0, TTB1
    //    SW_S_EL1, SW_EL2H: only stage 1 is valid, and with ASID, TTD permit all, TTB0, TTB1
    if ((SW_EL2 == stw) || (SW_EL3 == stw))
      epd1 = CD_EPDx_DISABLE;
    else
    {
      if (NULL == p_ttb1)
        epd1 = CD_EPDx_DISABLE;
      else {
        epd1 = CD_EPDx_ENABLE;
        p_vttb = p_ttb1->p_vttb;
      }
    }

    if (CD_EPDx_ENABLE == epd0)
    {
      tt_tgs_e tb_tgs = p_ttb0->tgs;
      tg0 = (tb_tgs == TT_TG_4K) ? CD_TG0_4K :(tb_tgs == TT_TG_64K) ? CD_TG0_64K : CD_TG0_16K;
      ir0 = p_ttb0->tt_ir;
      or0 = p_ttb0->tt_or;
      sh0 = p_ttb0->tt_sh;
      tbi0 = CD_TBI_ON;
      ttb0 = p_ttb0->ttb_addr;
      nscfg0 = p_ttb0->nscfg;
      t0sz = p_ttb0->txsz;
    }
    else // related field ignored
    {
      tg0 = CD_TG0_4K;
      ir0 = CD_xR_NC;
      or0 = CD_xR_NC;
      sh0 = CD_SHx_OUTER;
      tbi0 = CD_TBI_OFF;
      ttb0 = 0;
      nscfg0 = CD_NSCFG_SECURE;
      t0sz = CD_TxSZ_48;
    }
    if (CD_EPDx_ENABLE == epd1)
    {
      tt_tgs_e tb_tgs = p_ttb1->tgs;
      tg1 = (tb_tgs == TT_TG_4K) ? CD_TG1_4K :(tb_tgs == TT_TG_64K) ? CD_TG1_64K : CD_TG1_16K;
      ir1 = p_ttb1->tt_ir;
      or1 = p_ttb1->tt_or;
      sh1 = p_ttb1->tt_sh;
      tbi1 = CD_TBI_ON;
      ttb1 = p_ttb1->ttb_addr;
      nscfg1 = p_ttb1->nscfg;
      t1sz = p_ttb1->txsz;
    }
    else // related field ignored or RES0
    {
      t1sz = 0;
      tg1 = 0;
      ir1 = 0;
      or1 = 0;
      sh1 = 0;
      tbi1 = 0;
      ttb1 = 0;
      nscfg1 = CD_NSCFG_SECURE;
      t1sz = CD_TxSZ_48;
    }

    if (0 == p_stream->s1cdptr) {
      shell_msg( "s1cdptr NULL in VVDRV_qsmmuv3_program_stream, create\n");
      cd_base = VVDRV_qsmmuv3_alloc_CD(p_stream);
    }
    else {
      //  set programmable value
      if (en_stage2)
      {
        cd_base = do_table_walk(p_stream->s1cdptr, p_vttb->ttb_addr, p_vttb->root_lvl, p_vttb->tgs, p_vttb->stage, 0, NULL, NULL);
      }
      else
        cd_base = p_stream->s1cdptr;
    }

    if(pt_base!=0)
    {
      shell_msg("pt_base for mmu & smmu is 0x%02x_%02x.\n",pt_base>>32,pt_base);
      ttb0 = pt_base;
    }
    VVDRV_qsmmuv3_writeCD_full(cd_base, cd_index, t0sz, tg0, ir0, or0, sh0, epd0, endi, t1sz, tg1, ir1, or1, sh1, epd1, cd_v, ips, affd, wxn, uwxn, tbi0, tbi1, pan, aa64, hd, ha, ars, aset, asid, nscfg0, had0, ttb0, nscfg1, had1, ttb1, mair0, mair1, mair2, mair3, mair4, mair5, mair6, mair7);
  }

  // program STE
  //if(p_stream->p_ttb0->p_vm_profile.tt_4k_alloc_base==0x18086000){
  //  shell_msg("Don't program STE.\n");
  //  return;
  //}
  shell_msg( "VVDRV_qsmmuv3_program_stream STE\n");
  qsmmu_profile* p_qsmmu_inst = p_stream->p_qsmmu_inst; 
  uint64_t ste_base;
  int ste_index;
  STE_V ste_v;
  STE_S1Fmt s1fmt;
  uint64_t s1contextptr;
  int cdmax;
  STE_DSS dss;
  STE_CxR cir, cor;
  STE_CSH csh;
  int cont;
  STE_PPAR ppar;
  STE_MEV mev;
  STE_StallD stalld;
  STE_EATS eats;
  STE_STRW strw;
  STE_MemAttr memattr;
  int mtcfg;
  STE_AllocCfg alloccfg;
  STE_ShCfg shcfg;
  STE_NSCfg ste_nscfg;
  STE_PrivCfg privcfg;
  STE_InstCfg instcfg;
  int s2vmid;
  STE_S2T0SZ s2t0sz;
  STE_S2SL0 s2sl0;
  STE_S2IR0 s2ir0;
  STE_S2OR0 s2or0;
  STE_S2SH0 s2sh0;
  STE_S2TG s2tg;
  STE_S2PS s2ps;
  STE_S2AA64 s2aa64;
  STE_S2ENDI s2endi;
  STE_S2AFFD s2affd;
  STE_S2PTW s2ptw;
  STE_S2HD s2hd;
  STE_S2HA s2ha;
  STE_S2S s2s;
  STE_S2R s2r;
  uint64_t s2ttb;

  // default config
  ste_v = STE_VALID;
  cdmax = 0;
  dss = STE_DSS_DISABLED;
  cont = 0;
  ppar = STE_PPAR_NO_PASID_TLP;  // PRI not supported
  mev = STE_MEV_OFF;
  s2ps = STE_S2PS_44BITS;
  s2aa64 = STE_S2AA64_AARCH64;
  s2endi = STE_S2ENDI_LITTLE;
  s2hd = STE_S2HD_DISABLE;
  s2ha = STE_S2HA_DISABLE;
  s2r = STE_S2R_ON;

  // possible to change
  s1fmt = STE_S1FMT_LINEAR;
  s2t0sz = STE_S2T0SZ_44;
  s2sl0 = STE_S2SL0_4KL0_L1;
  s2ir0 = STE_S2IR0_NC;
  s2or0 = STE_S2OR0_NC;
  s2sh0 = STE_S2SH0_OS;
  s2tg = STE_S2TG_4K;
  s2affd = STE_S2AFFD_NOFAULT;
  s2ptw = STE_S2PTW_PROTECT_OFF;


  ste_base = (p_stream->stw >= SW_S_EL1) ? p_qsmmu_inst->s_strtab_base : p_qsmmu_inst->ns_strtab_base;
  ste_index = p_stream->sid;
  s1contextptr = p_stream->s1cdptr;
  cir = p_stream->cir;
  cor = p_stream->cor;
  csh = p_stream->csh;
  stalld = p_stream->stalld;
  eats = p_stream->eats;
  if (SW_NS_EL1 == stw)
    strw = STE_STRW_NS_EL1;
  else if ((SW_EL2 == stw) || (SW_EL2H == stw))
    strw = STE_STRW_EL2;
  else if (SW_S_EL1 == stw)
    strw = STE_STRW_SECURE;
  else // SW_EL3
    strw = STE_STRW_EL3;
  // don't remember why config mtcfg as following before
  //mtcfg = (config == STE_TYPE_STAGE2) ? 1 : 0;
  //ste_nscfg = (config == STE_TYPE_STAGE2) ? STE_NSCFG_NONSECURE : STE_NSCFG_INCOMING;
  mtcfg = p_stream->mtcfg;
  memattr = p_stream->memattr;
  alloccfg = p_stream->alloccfg;
  shcfg = p_stream->shcfg;
  privcfg = p_stream->privcfg;
  instcfg = p_stream->instcfg;
  ste_nscfg = p_stream->ste_nscfg;

  s2s = 0;

  s2vmid = p_stream->vmid;

  if (en_stage2)
  {
    ttb_profile * p_s2ttb;
    if (en_stage1) {
      p_s2ttb = p_vttb;
    }
    else { // p_ttb0 is the vttb
      p_s2ttb = p_ttb0;
    }
    s2s = p_stream->s2s;
    s2ttb = p_s2ttb->ttb_addr;
    s2t0sz = (STE_S2T0SZ)p_s2ttb->txsz;
    s2tg = (p_s2ttb->tgs == TT_TG_4K) ? STE_S2TG_4K : (p_s2ttb->tgs == TT_TG_64K) ? STE_S2TG_64K : STE_S2TG_16K;
    if (p_s2ttb->tgs == TT_TG_4K) {
      s2tg = STE_S2TG_4K;
      s2sl0 = 2 - p_s2ttb->root_lvl;
    }
    else {
      s2sl0 = 3 - p_s2ttb->root_lvl;
      if (p_s2ttb->tgs == TT_TG_64K) {
        s2tg = STE_S2TG_64K;
      }
      else {
        s2tg = STE_S2TG_16K;
      }
    }
    s2ir0 = (STE_S2IR0)p_s2ttb->tt_ir;
    s2or0 = (STE_S2OR0)p_s2ttb->tt_or;
    s2sh0 = (STE_S2SH0)p_s2ttb->tt_sh;
  }
  else
  {
    s2ttb = 0;
  }
  shell_msg("VVDRV_qsmmuv3_writeSTE_full.\n");
  shell_msg("ste_base = 0x%02x_%02x\n",(uint32_t)(ste_base>>32),(uint32_t)ste_base);
  VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, ste_v, config, s1fmt, s1contextptr, cdmax, dss, cir, cor, csh, cont, ppar, mev, stalld, eats, strw, memattr, mtcfg, alloccfg, shcfg, ste_nscfg, privcfg, instcfg, s2vmid, s2t0sz, s2sl0, s2ir0, s2or0, s2sh0, s2tg, s2ps, s2aa64, s2endi, s2affd, s2ptw, s2hd, s2ha, s2s, s2r , s2ttb);
}

//mem_space *create_mem(uint64_t mem_base, uint64_t mem_limit)
//{
//   mem_space *p_mem;
//   p_mem = create(mem_space);
//   if (p_mem == NULL) {
//      return NULL;
//   }
//   p_mem->mem_base = mem_base;
//   p_mem->mem_limit = mem_limit;
//   p_mem->next = NULL;
//   return p_mem;
//}
//
//void VVDRV_qsmmuv3_mem_add(stream_profile *p_stream, uint64_t mem_base, uint64_t mem_limit)
//{
//  mem_space *p_mem = create_mem(mem_base, mem_limit);
//  mem_space *cur_head = p_stream->mem_head;
//  p_stream->mem_head = p_mem;
//  p_mem->next = cur_head;
//}

uint64_t VVDRV_qsmmuv3_alloc_CD(stream_profile * p_stream)
{
  uint64_t cdptr;
  vm_profile *p_vm;
  ttb_profile * p_ttb;  
  p_ttb = p_stream->p_ttb0;
  if (NULL == p_ttb) {
    p_ttb = p_stream->p_ttb1;
    if (NULL == p_ttb) {
      //vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_alloc_CD both ttb0 and ttb1 are NULL");
      return 0xffffffffffffffff;
    }
  }
  p_vm = p_ttb->p_vm_profile;
  if (p_stream->stw >= SW_S_EL1)  // secure
  {
    cdptr = p_vm->s_cd_alloc_ptr;
    p_vm->s_cd_alloc_ptr +=  64;
  }
  else
  {
    cdptr = p_vm->ns_cd_alloc_ptr;
    p_vm->ns_cd_alloc_ptr += 64;
  }
  p_stream->s1cdptr = cdptr;
  shell_msg( "VVDRV_qsmmuv3_alloc_CD create s1cdptr = 0x%0x_%8x\n", cdptr >>32, cdptr);
  if (p_ttb->p_vttb) {
    cdptr = VVDRV_qsmmuv3_create_page(p_ttb->p_vttb, cdptr);
    shell_msg( "VVDRV_qsmmuv3_alloc_CD PA of s1cdptr = 0x%0x_%8x\n", cdptr >>32, cdptr);
  }
  return cdptr;
}

void VVDRV_qsmmuv3_program_QACT(qsmmu_profile * p_qsmmu_inst, uint32_t qactidx, uint32_t qact_s)
{
  uint64_t secure_base, nonsecure_base;
  //uint32_t addr_lower32bits		  = 0;
  //uint32_t addr_upper32bits		  = 0;
  uint64_t s_qact_addr	  = 0;
  uint64_t ns_qact_addr	  = 0;
  uint32_t bit_mask = 0;

  secure_base = p_qsmmu_inst->s_reg_base;
  nonsecure_base = p_qsmmu_inst->ns_reg_base;
  s_qact_addr  = secure_base + QSMMU_QSMMUV3_QSCT_REG_BASE;
  ns_qact_addr  = nonsecure_base + QSMMU_QSMMUV3_QSCT_REG_BASE;
  bit_mask = 1 << qactidx;

  if (qact_s == 2)  // QAD
  {
    shell_msg( "Setting stream 0x%x QAD in QACT\n", qactidx);
    //HWIO_OUT(IMC_MSA_CTRL,0x3);
    *((uint32_t*)IMC_MSA_CTRL) = 0x3;
    HWIO_OUTXI( s_qact_addr, ALLOC_QACTn, 0, bit_mask);
    //HWIO_OUT(IMC_MSA_CTRL,0x0);
    *((uint32_t*)IMC_MSA_CTRL) = 0x0;
  } else if (qact_s == 1)  // secure
  {
    shell_msg( "Setting stream 0x%x secure in QACT\n", qactidx);
    HWIO_OUTXI( s_qact_addr, ALLOC_QACTn, 0, bit_mask);
  } else // non-secure
  {
    shell_msg( "Setting stream 0x%x non-secure in QACT,ns_qact_addr=0x%8x_%8x\n", qactidx,ns_qact_addr>>32,ns_qact_addr);
    HWIO_OUTXI( s_qact_addr, FREE_QACTn, 0, bit_mask);
    HWIO_OUTXI( ns_qact_addr, ALLOC_QACTn, 0, bit_mask);
  }
}

void VVDRV_qsmmuv3_free_QACT(qsmmu_profile * p_qsmmu_inst, uint32_t qactidx, uint32_t qact_s)
{
  uint64_t secure_base, nonsecure_base;
  //uint32_t addr_lower32bits		  = 0;
  //uint32_t addr_upper32bits		  = 0;
  uint64_t s_qact_addr	  = 0;
  uint64_t ns_qact_addr	  = 0;
  uint32_t bit_mask = 0;

  secure_base = p_qsmmu_inst->s_reg_base;
  nonsecure_base = p_qsmmu_inst->ns_reg_base;
  s_qact_addr  = secure_base + QSMMU_QSMMUV3_QSCT_REG_BASE;
  ns_qact_addr  = nonsecure_base + QSMMU_QSMMUV3_QSCT_REG_BASE;
  bit_mask = 1 << qactidx;

  if (qact_s == 2)  // QAD
  {
    shell_msg( "Free stream 0x%x QAD in QACT\n", qactidx);
    //HWIO_OUT(IMC_MSA_CTRL,0x3);
    *((uint32_t*)IMC_MSA_CTRL) = 0x3;
    HWIO_OUTXI( s_qact_addr, FREE_QACTn, 0, bit_mask);
    //HWIO_OUT(IMC_MSA_CTRL,0x0);
    *((uint32_t*)IMC_MSA_CTRL) = 0x0;
  } else if (qact_s == 1)  // secure
  {
    shell_msg( "Free stream 0x%x secure in QACT\n", qactidx);
    HWIO_OUTXI( s_qact_addr, FREE_QACTn, 0, bit_mask);
  } else // non-secure
  {
    shell_msg( "Free stream 0x%x non-secure in QACT\n", qactidx);
    HWIO_OUTXI( ns_qact_addr, FREE_QACTn, 0, bit_mask);
  }
}

void VVDRV_qsmmuv3_program_qact(stream_profile *p_stream)
{
  uint32_t qact_s;
  if(p_stream->stw == SW_QAD)
    qact_s = 2;
  else
    qact_s = p_stream->stw >= SW_S_EL1;
  VVDRV_qsmmuv3_program_QACT(p_stream->p_qsmmu_inst, p_stream->qactidx, qact_s);
}

void VVDRV_qsmmuv3_free_qact(stream_profile *p_stream)
{
  uint32_t qact_s;
  if(p_stream->stw == SW_QAD)
    qact_s = 2;
  else
    qact_s = p_stream->stw >= SW_S_EL1;
  VVDRV_qsmmuv3_free_QACT(p_stream->p_qsmmu_inst, p_stream->qactidx, qact_s);
}

void VVDRV_qsmmuv3_program_enables(qsmmu_profile * p_qsmmu_inst)
{
  uint64_t reg_base;
  reg_base = p_qsmmu_inst->s_reg_base;
  shell_msg("default enables.\n");
  VVDRV_qsmmuv3_default_enables(reg_base,1);
  shell_msg( "Enabling TLB and config cache\n");
  VVDRV_qsmmuv3_enable_TLB(reg_base);
  VVDRV_qsmmuv3_enable_cfgcache(reg_base);

  shell_msg( "Enabling secure and non-secure SMMU\n");
  VVDRV_qsmmuv3_enable(reg_base, 1);
  VVDRV_qsmmuv3_enable(reg_base, 0);
}

void VVDRV_qsmmuv3_program_MSI(qsmmu_profile *p_qsmmu_inst)
{
  //uint64_t reg_base;
  //reg_base = p_qsmmu_inst->s_reg_base;
  // program eventq MSI
  // program cmdq MSI
  // program GERROR MSI
  // program Fault IRQ MSI
}

void VVDRV_qsmmuv3_init_qsmmu_profile(qsmmu_profile *p_qsmmu_inst)
{
  shell_msg( "enter VVDRV_qsmmuv3_init_qsmmu_profile\n");
  switch (p_qsmmu_inst->ss) {
    case QSMMU_CRYPTO:
      p_qsmmu_inst->feature.qsct_width = 5;
      p_qsmmu_inst->feature.sid_width = 5;
      p_qsmmu_inst->feature.ssid_width = 0;
      if (p_qsmmu_inst->inst_idx == 0) {
        p_qsmmu_inst->s_reg_base = CRYPTO0_QSMMU_BASE;
        p_qsmmu_inst->ns_reg_base = CRYPTO0_QSMMU_BASE; //- AW_NS_SUBTRACT_OFFSET;
      } else {
        //vv_msg(SEV_ERROR, ST_FUNCTION, "Invalidate qsmmu_profile instance index");
        return;
      }
      break;

    case QSMMU_IMC:
      p_qsmmu_inst->feature.qsct_width = 1;
      p_qsmmu_inst->feature.sid_width = 3;
      p_qsmmu_inst->feature.ssid_width = 0;
      p_qsmmu_inst->s_reg_base = IMC_QSMMU_BASE;
      p_qsmmu_inst->ns_reg_base = IMC_QSMMU_BASE - AW_NS_SUBTRACT_OFFSET;
      break;
    case QSMMU_PCIE:
      p_qsmmu_inst->feature.qsct_width = 8;
      p_qsmmu_inst->feature.sid_width = 16;
      p_qsmmu_inst->feature.ssid_width = 20;
      switch (p_qsmmu_inst->inst_idx) {
        case 0:
          p_qsmmu_inst->s_reg_base =  QSMMU_S_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET0;
          p_qsmmu_inst->ns_reg_base = QSMMU_NS_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET0;
          break;
        case 1:
          p_qsmmu_inst->s_reg_base =  QSMMU_S_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET1;
          p_qsmmu_inst->ns_reg_base = QSMMU_NS_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET1;
          break;
        case 2:
          p_qsmmu_inst->s_reg_base =  QSMMU_S_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET2;
          p_qsmmu_inst->ns_reg_base = QSMMU_NS_OFFSET_PCIE_0 + QSMMU_PCIE_OFFSET2;
          break;
        case 3:
          p_qsmmu_inst->s_reg_base =  QSMMU_S_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET0;
          p_qsmmu_inst->ns_reg_base = QSMMU_NS_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET0;
          break;
        case 4:
          p_qsmmu_inst->s_reg_base =  QSMMU_S_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET1;
          p_qsmmu_inst->ns_reg_base = QSMMU_NS_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET1;
          break;
        case 5:
          p_qsmmu_inst->s_reg_base =  QSMMU_S_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET2;
          p_qsmmu_inst->ns_reg_base = QSMMU_NS_OFFSET_PCIE_1 + QSMMU_PCIE_OFFSET2;
          break;
        default:
          //vv_msg(SEV_ERROR, ST_FUNCTION, "Invalidate qsmmu_profile instance index");
          return;
      }
      break;


    default:
      //vv_msg(SEV_ERROR, ST_FUNCTION, "Invalidate qsmmu_profile instance");
      return;
  }

  // program default strtab configure
  p_qsmmu_inst->s_strtab_base_cfg.log2size = p_qsmmu_inst->feature.sid_width;
  p_qsmmu_inst->s_strtab_base_cfg.linear = 1;
  p_qsmmu_inst->s_strtab_base_cfg.split = STE_SPLIT_4K;

  p_qsmmu_inst->ns_strtab_base_cfg.log2size = p_qsmmu_inst->feature.sid_width;
  p_qsmmu_inst->ns_strtab_base_cfg.linear = 1;
  p_qsmmu_inst->ns_strtab_base_cfg.split = STE_SPLIT_4K;

  // program default event/cmd queue configure
  p_qsmmu_inst->eventq.s_eventq.log2_num = 2;
  p_qsmmu_inst->cmdq.s_cmdq.log2_num = 4;
  p_qsmmu_inst->eventq.ns_eventq.log2_num = 2;
  p_qsmmu_inst->cmdq.ns_cmdq.log2_num = 4;

  // clear non allocated mem ptr as 0
  p_qsmmu_inst->s_strtab_base = 0;
  p_qsmmu_inst->ns_strtab_base = 0;

  p_qsmmu_inst->ns_eventq_irq.addr = 0;
  p_qsmmu_inst->ns_eventq_irq.data = 0;
  p_qsmmu_inst->ns_eventq_irq.attr = 0;
  p_qsmmu_inst->s_eventq_irq.addr = 0;
  p_qsmmu_inst->s_eventq_irq.data = 0;
  p_qsmmu_inst->s_eventq_irq.attr = 0;
  p_qsmmu_inst->ns_error_irq.addr = 0;
  p_qsmmu_inst->ns_error_irq.data = 0;
  p_qsmmu_inst->ns_error_irq.attr = 0;
  p_qsmmu_inst->s_error_irq.addr = 0;
  p_qsmmu_inst->s_error_irq.data = 0;
  p_qsmmu_inst->s_error_irq.attr = 0;
  shell_msg( "exit VVDRV_qsmmuv3_init_qsmmu_profile\n");
}

void VVDRV_qsmmuv3_alloc_qsmmu_queues(qsmmu_profile *p_qsmmu_inst)
{
  uint32_t queue_size, queue_bytes;
  system_profile *p_sys_profile;
  p_sys_profile = p_qsmmu_inst->p_sys_profile;
  // each event is 32 bytes, each cmd is 16 bytes
  // allocate secure event queue
  queue_size = 1 << (p_qsmmu_inst->eventq.s_eventq.log2_num);
  queue_bytes = queue_size * 32;
  p_qsmmu_inst->eventq.s_eventq.base = p_sys_profile->s_queue_alloc_ptr;
  p_sys_profile->s_queue_alloc_ptr += queue_bytes;
  if (p_sys_profile->s_queue_alloc_ptr > p_sys_profile->s_queue_alloc_limit)
  {
    //vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_alloc_qsmmu_queues s_queue alloc fail");
  }
  // allocate secure cmd queue
  queue_size = 1 << (p_qsmmu_inst->cmdq.s_cmdq.log2_num);
  queue_bytes = queue_size * 16;
  p_qsmmu_inst->cmdq.s_cmdq.base = p_sys_profile->s_queue_alloc_ptr;
  p_sys_profile->s_queue_alloc_ptr += queue_bytes;
  if (p_sys_profile->s_queue_alloc_ptr > p_sys_profile->s_queue_alloc_limit)
  {
    //vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_alloc_qsmmu_queues s_queue alloc fail");
  }
  // allocate non-secure event queue
  queue_size = 1 << (p_qsmmu_inst->eventq.ns_eventq.log2_num);
  queue_bytes = queue_size * 32;
  p_qsmmu_inst->eventq.ns_eventq.base = p_sys_profile->ns_queue_alloc_ptr;
  p_sys_profile->ns_queue_alloc_ptr += queue_bytes;
  if (p_sys_profile->ns_queue_alloc_ptr > p_sys_profile->ns_queue_alloc_limit)
  {
    //vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_alloc_qsmmu_queues ns_queue alloc fail");
  }
  // allocate non-secure cmd queue
  queue_size = 1 << (p_qsmmu_inst->cmdq.ns_cmdq.log2_num);
  queue_bytes = queue_size * 16;
  p_qsmmu_inst->cmdq.ns_cmdq.base = p_sys_profile->ns_queue_alloc_ptr;
  p_sys_profile->ns_queue_alloc_ptr += queue_bytes;
  if (p_sys_profile->ns_queue_alloc_ptr > p_sys_profile->ns_queue_alloc_limit)
  {
    //vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_alloc_qsmmu_queues ns_queue alloc fail");
  }

  return;
}

void VVDRV_qsmmuv3_programCMDQ(qsmmu_profile *p_qsmmu_inst)
{
  uint64_t reg_base;
  reg_base = p_qsmmu_inst->s_reg_base;

  VVDRV_qsmmuv3_configureCommandQueue(reg_base, p_qsmmu_inst->cmdq.s_cmdq.base, p_qsmmu_inst->cmdq.s_cmdq.log2_num, 1);
  VVDRV_qsmmuv3_configureCommandQueue(reg_base, p_qsmmu_inst->cmdq.ns_cmdq.base, p_qsmmu_inst->cmdq.ns_cmdq.log2_num, 0);
}

void VVDRV_qsmmuv3_programEventQ(qsmmu_profile *p_qsmmu_inst)
{
  uint64_t reg_base;
  reg_base = p_qsmmu_inst->s_reg_base;

  VVDRV_qsmmuv3_configureEventQueue(reg_base, p_qsmmu_inst->eventq.s_eventq.base, p_qsmmu_inst->eventq.s_eventq.log2_num, 1);
  //VVDRV_qsmmuv3_configureEventQueue(reg_base, p_qsmmu_inst->eventq.ns_eventq.base, p_qsmmu_inst->eventq.ns_eventq.log2_num, 0);
  uint64_t msi_addr = p_qsmmu_inst->ns_eventq_irq.addr;
  HWIO_OUTX(reg_base, EVENTQ_IRQ_CFG0_L, msi_addr & 0xffffffff);
  HWIO_OUTX(reg_base, EVENTQ_IRQ_CFG0_H, msi_addr >> 32);
  HWIO_OUTX(reg_base, EVENTQ_IRQ_CFG1, p_qsmmu_inst->ns_eventq_irq.data);
  HWIO_OUTX(reg_base, EVENTQ_IRQ_CFG2, p_qsmmu_inst->ns_eventq_irq.attr);
  msi_addr = p_qsmmu_inst->s_eventq_irq.addr;
  HWIO_OUTX(reg_base, S_EVENTQ_IRQ_CFG0_L, msi_addr & 0xffffffff);
  HWIO_OUTX(reg_base, S_EVENTQ_IRQ_CFG0_H, msi_addr >> 32);
  HWIO_OUTX(reg_base, S_EVENTQ_IRQ_CFG1, p_qsmmu_inst->s_eventq_irq.data);
  HWIO_OUTX(reg_base, S_EVENTQ_IRQ_CFG2, p_qsmmu_inst->s_eventq_irq.attr);
}

void VVDRV_qsmmuv3_programGERROR_IRQ(qsmmu_profile *p_qsmmu_inst)
{
  uint64_t reg_base;
  reg_base = p_qsmmu_inst->s_reg_base;

  uint64_t msi_addr = p_qsmmu_inst->ns_error_irq.addr;
  HWIO_OUTX(reg_base, GERROR_IRQ_CFG0_L, msi_addr & 0xffffffff);
  HWIO_OUTX(reg_base, GERROR_IRQ_CFG0_H, msi_addr >> 32);
  HWIO_OUTX(reg_base, GERROR_IRQ_CFG1, p_qsmmu_inst->ns_error_irq.data);
  HWIO_OUTX(reg_base, GERROR_IRQ_CFG2, p_qsmmu_inst->ns_error_irq.attr);
  msi_addr = p_qsmmu_inst->s_error_irq.addr;
  HWIO_OUTX(reg_base, S_GERROR_IRQ_CFG0_L, msi_addr & 0xffffffff);
  HWIO_OUTX(reg_base, S_GERROR_IRQ_CFG0_H, msi_addr >> 32);
  HWIO_OUTX(reg_base, S_GERROR_IRQ_CFG1, p_qsmmu_inst->s_error_irq.data);
  HWIO_OUTX(reg_base, S_GERROR_IRQ_CFG2, p_qsmmu_inst->s_error_irq.attr);

  uint32_t rdata_ack;
  //for secure IRQ
  HWIO_OUTXF(reg_base, S_IRQ_CTRL, GERROR_IRQEN, 1);
    do
    {
    rdata_ack = HWIO_INXF(reg_base, S_IRQ_CTRLACK, GERROR_IRQEN);
    } while  (!rdata_ack);
    shell_msg( "S_GERROR_IRQEN update_complete : %d", rdata_ack);
   // for non-secure IRQ
  /*HWIO_OUTXF(reg_base, IRQ_CTRL, GERROR_IRQEN, 1);
  do
  {
    rdata_ack = HWIO_INXF(reg_base, IRQ_CTRLACK, GERROR_IRQEN);
  } while  (!rdata_ack);
  shell_msg( "GERROR_IRQEN update_complete : %d", rdata_ack);*/
}

void VVDRV_qsmmuv3_alloc_qsmmu_st(qsmmu_profile *p_qsmmu_inst)
{
  uint32_t st_size, st_bytes;
  uint64_t ste_addr;
  uint64_t alloc_ptr_low;
  system_profile *p_sys_profile;
  p_sys_profile = p_qsmmu_inst->p_sys_profile;

  // stream table is aligned with sid as index
  // ste_base[log2size + 6 - 1: 0] = 0
  // ste_addr[log2size + 6 - 1: 6] = sid

  // allocate secure stream table
  st_size = 1 << (p_qsmmu_inst->s_strtab_base_cfg.log2size);
  shell_msg( "st_size= 0x%8x\n", st_size);

  st_bytes = st_size * 64;

  alloc_ptr_low = p_sys_profile->s_st_alloc_ptr & ((uint64_t)st_bytes - 1);
  shell_msg( "VVDRV_qsmmuv3_alloc_qsmmu_st s st_bytes = 0x%8x, alloc_ptr_low = 0x%0x_%8x\n", st_bytes, (alloc_ptr_low >> 32), alloc_ptr_low );
  if (alloc_ptr_low) {
    // not aligned, make aligned
    p_sys_profile->s_st_alloc_ptr = (p_sys_profile->s_st_alloc_ptr - alloc_ptr_low) + st_bytes;
    shell_msg( "VVDRV_qsmmuv3_alloc_qsmmu_st align s_st_alloc_ptr\n ");
  }
  p_qsmmu_inst->s_strtab_base = p_sys_profile->s_st_alloc_ptr;
  p_sys_profile->s_st_alloc_ptr += st_bytes;

  // initial each STE as all zero of 64 Bytes
  ste_addr = p_qsmmu_inst->s_strtab_base;
  shell_msg( "VVDRV_qsmmuv3_alloc_qsmmu_st init secure ste 0x%0x_%8x\n", (ste_addr >> 32), ste_addr);
  VVDRV_qsmmuv3_zero_mem(ste_addr, st_bytes);

  // allocate non-secure stream table
  st_size = 1 << (p_qsmmu_inst->ns_strtab_base_cfg.log2size);
  st_bytes = st_size * 64;

  alloc_ptr_low = p_sys_profile->ns_st_alloc_ptr & (st_bytes - 1);
  shell_msg( "VVDRV_qsmmuv3_alloc_qsmmu_st ns st_bytes = 0x%8x, alloc_ptr_low = 0x%0x_%8x\n", st_bytes, (alloc_ptr_low >> 32), alloc_ptr_low );
  if (alloc_ptr_low) {
    // not aligned, make aligned
    p_sys_profile->ns_st_alloc_ptr = (p_sys_profile->ns_st_alloc_ptr - alloc_ptr_low) + st_bytes;
    shell_msg( "VVDRV_qsmmuv3_alloc_qsmmu_st align ns_st_alloc_ptr\n ");
  }
  p_qsmmu_inst->ns_strtab_base = p_sys_profile->ns_st_alloc_ptr;
  p_sys_profile->ns_st_alloc_ptr += st_bytes;

  ste_addr = p_qsmmu_inst->ns_strtab_base;
  shell_msg( "VVDRV_qsmmuv3_alloc_qsmmu_st init ns ste 0x%0x_%8x\n", (ste_addr >> 32), ste_addr);
  VVDRV_qsmmuv3_zero_mem(ste_addr, st_bytes);
}

void VVDRV_qsmmuv3_programStreamTable(qsmmu_profile *p_qsmmu_inst)
{
  uint64_t strtab_base;
  uint32_t log2_numste;
  uint64_t reg_base;
  reg_base = p_qsmmu_inst->s_reg_base;

  strtab_base = p_qsmmu_inst->s_strtab_base;
  log2_numste = p_qsmmu_inst->s_strtab_base_cfg.log2size;
  VVDRV_qsmmuv3_configureStreamTable(reg_base, strtab_base, log2_numste, 1);

  strtab_base = p_qsmmu_inst->ns_strtab_base;
  log2_numste = p_qsmmu_inst->ns_strtab_base_cfg.log2size;
  VVDRV_qsmmuv3_configureStreamTable(reg_base, strtab_base, log2_numste, 0);

  return;
}

void VVDRV_qsmmuv3_init_qsmmu(qsmmu_profile *p_qsmmu_inst)
{
  uint64_t reg_base;

  reg_base = p_qsmmu_inst->s_reg_base;

  uint32_t addr_low, addr_high;
  addr_low = reg_base & 0xffffffff;
  addr_high = (reg_base >> 32) & 0xffffffff;
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu reg_base is 0x%0x_%8x\n", addr_high, addr_low);

  // Step 1, program QACT, will shift to stream init
  //VVDRV_qsmmuv3_program_qact(p_qsmmu_inst, qactidx, qact_s);
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 1\n");
  // Step 2, Allocate Stream Table
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 2\n");
  if (p_qsmmu_inst->s_strtab_base == 0) {
    VVDRV_qsmmuv3_alloc_qsmmu_st(p_qsmmu_inst);
  }

  // Step 3, Program memory attr into CR1: table and queue SH/OC/IC
  // default as NSH after reset
  // if program to Shareable, ring and L3 need to be enabled.
  // so skip this by now to simplify init process
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 3\n");
  VVDRV_qsmmuv3_TableQueueAttributes(reg_base, SH_ATTR_ISH, CH_ATTR_WB, CH_ATTR_WB, SH_ATTR_ISH, CH_ATTR_WB, CH_ATTR_WB, 1);
  //VVDRV_qsmmuv3_TableQueueAttributes(reg_base, SH_ATTR_ISH, CH_ATTR_WB, CH_ATTR_WB, SH_ATTR_ISH, CH_ATTR_WB, CH_ATTR_WB, 0);

  // Step 4, Program STRTAB
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 4\n");
  VVDRV_qsmmuv3_programStreamTable(p_qsmmu_inst);

  // Step 5, Allocate queues
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 5\n");
  VVDRV_qsmmuv3_alloc_qsmmu_queues(p_qsmmu_inst);

  // Step 6, program cmd queue
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 6\n");
  VVDRV_qsmmuv3_programCMDQ(p_qsmmu_inst);

  // Step 7, enable cmd queue
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 7\n");
  VVDRV_qsmmuv3_enable_cmdq(reg_base, 1);
  VVDRV_qsmmuv3_enable_cmdq(reg_base, 0);

  // Step 8, program event queue
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 8\n");
  VVDRV_qsmmuv3_programEventQ(p_qsmmu_inst);

  // Step 9, enable event queue
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 9\n");
  VVDRV_qsmmuv3_enable_eventq(reg_base, 1);
  VVDRV_qsmmuv3_enable_eventq(reg_base, 0);

  // Step 10, enable GERROR_IRQ
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 10\n");
  VVDRV_qsmmuv3_programGERROR_IRQ(p_qsmmu_inst);

  // Step 11, enable SMMU
  shell_msg( "VVDRV_qsmmuv3_init_qsmmu step 11\n");
  VVDRV_qsmmuv3_program_enables(p_qsmmu_inst);
}

void VVDRV_qsmmuv3_zero_mem(uint64_t addr, uint32_t size_B)
{
#ifdef SMMU_BACKDOOR
  uint64_t data = SMMU_BACKDOOR_JOB;
  data = (data << 32) + size_B;
  shell_msg( "VVDRV_qsmmuv3_zero_mem new job: addr = 0x%0x_%8x, size = 0x%x", addr >> 32, addr, size_B);
  outp64(SMMU_BACKDOOR_ADDR + 0x8, addr);
  // add barrier to make sure addr paramter is updated when job code received.
  __asm( "DSB SY \n\t" ); 
  __asm( "ISB SY \n\t" ); 
  outp64(SMMU_BACKDOOR_ADDR, data);
  __asm( "DSB SY \n\t" ); 
  __asm( "ISB SY \n\t" ); 
  uint32_t cnt;
  for (cnt = 0; cnt < 50; cnt ++)
  {
    data = inp64(SMMU_BACKDOOR_ADDR);
    data = data >> 32;
    shell_msg( "VVDRV_qsmmuv3_zero_mem pull data = 0x%8x, expect 0x%8x, cnt = %d", data, SMMU_BACKDOOR_DONE, cnt);
    if (SMMU_BACKDOOR_DONE == data)
      break;
  }
  if (50 == cnt) {
    ////vv_msg(SEV_ERROR, ST_FUNCTION, "VVDRV_qsmmuv3_zero_mem backdoor error");
  }
  else {
    shell_msg( "VVDRV_qsmmuv3_zero_mem job done");
  }
#else  //SMMU_BACKDOOR
  uint32_t size_8B = size_B >> 3;
  for (uint32_t cnt = 0; cnt < size_8B; cnt++)
  {

    //shell_msg( "VVDRV_qsmmuv3_zero_mem SMMU_BACKDOOR addr = 0x%16x", addr);
    outp64(addr, 0x0000000000000000);
    addr += 0x08;
  }
#endif  //SMMU_BACKDOOR
}

void VVDRV_qsmmuv3_program_IMC()
{
  /////////////////////////////////////////////////////////////////
  // IMC SMMU programm guide:
  // IMC has 2 stream ID
  // QDT api VVDRV_qsmmuv3_setup_pcie_xlationc onfigured both stream as secure world, stage 1, shared CD
  // stream world as S_EL1, TxSZ 40 bits, 64KB TG, start level will be level 2, all entry as block. 

  qsmmu_profile qsmmu_imc;
  VVDRV_qsmmuv3_set_qsmmu(&qsmmu_imc, QSMMU_IMC, 0);
  VVDRV_qsmmuv3_alloc_qsmmu_st(&qsmmu_imc);

  ttb_profile ttb_imc;
  VVDRV_qsmmuv3_init_ttb(&ttb_imc, TT_TG_64K, CD_TxSZ_40, 1, NULL, NULL);
  VVDRV_qsmmuv3_create_IMC_tt(&ttb_imc);

  stream_profile stream_imc;
  VVDRV_qsmmuv3_init_stream(&stream_imc, qsmmu_imc.ss, qsmmu_imc.inst_idx);
  stream_imc.sid = 0;
  stream_imc.qactidx = 0;
  stream_imc.stw = SW_S_EL1;
  stream_imc.config = STE_TYPE_STAGE1;
  stream_imc.asid = 0;
  stream_imc.p_ttb0 = &ttb_imc;
  stream_imc.p_ttb1 = &ttb_imc;
  VVDRV_qsmmuv3_program_qact(&stream_imc);
  VVDRV_qsmmuv3_program_stream(&stream_imc,0);

  stream_imc.sid = 1;
  stream_imc.qactidx = 1;
  VVDRV_qsmmuv3_program_qact(&stream_imc);
  VVDRV_qsmmuv3_program_stream(&stream_imc,0);

  //qsmmu_imc.eventq.s_eventq.log2_num = 2;
  //qsmmu_imc.cmdq.s_cmdq.log2_num = 2;
  //qsmmu_imc.eventq.ns_eventq.log2_num = 2;
  //qsmmu_imc.cmdq.ns_cmdq.log2_num = 2;
  VVDRV_qsmmuv3_init_qsmmu(&qsmmu_imc);
}

/* void VVDRV_qsmmuv3_program_Intr(vi_int_isr_func_type p_imc_irs)
   {
   shell_msg( "VVDRV_qsmmuv3_program_Intr Configuring QGIC2 in IMC");
   VVDRV_qsmmuv3_qgic_cfg();

// Register ISR
if (p_imc_irs == NULL) {
vi_int_set_vector(P_IRQ_VECT, smmu_default_interrupt_isr);
shell_msg( "VVDRV_qsmmuv3_program_Intr register default ISR function in IMC");
} else {
vi_int_set_vector(P_IRQ_VECT, p_imc_irs );
shell_msg( "VVDRV_qsmmuv3_program_Intr register customized ISR function in IMC");
}
} */

void VVDRV_qsmmuv3_process_event(qsmmu_profile *p_qsmmu_inst, event_struct* event_ptr) {
  shell_msg( "VVDRV_qsmmuv3_process_event: type = 0x%0x", event_ptr->type);
  shell_msg( "VVDRV_qsmmuv3_process_event: data[0] = 0x%0x", event_ptr->data[0]);
  shell_msg( "VVDRV_qsmmuv3_process_event: data[1] = 0x%0x", event_ptr->data[1]);
  shell_msg( "VVDRV_qsmmuv3_process_event: data[2] = 0x%0x", event_ptr->data[2]);
  shell_msg( "VVDRV_qsmmuv3_process_event: data[3] = 0x%0x", event_ptr->data[3]);
  shell_msg( "VVDRV_qsmmuv3_process_event: data[4] = 0x%0x", event_ptr->data[4]);
  shell_msg( "VVDRV_qsmmuv3_process_event: data[5] = 0x%0x", event_ptr->data[5]);
  shell_msg( "VVDRV_qsmmuv3_process_event: data[6] = 0x%0x", event_ptr->data[6]);
  shell_msg( "VVDRV_qsmmuv3_process_event: data[7] = 0x%0x", event_ptr->data[7]);
  uint32_t RIP;
  uint32_t RnW;	// The read/write nature of the incoming transaction that led to event
  //  uint32_t InD;	// Instruction/Data (post-STE override)
  //uint32_t PnU;	// Privileged/Unprivileged (post-STE override)
  uint64_t InputAddr;
  uint32_t ssv;	// substreamID validity flag
  uint32_t ssid;	// substreamID
  uint32_t sid;
  uint32_t s2;	// stage of fault. 0: stage 1; 1: stage 2
  EVENT_CLASS ec;
  ssv = (event_ptr->data[0] >> 11 ) & 0x1;
  ssid = event_ptr->data[0] >> 12;
  sid = event_ptr->data[1];
  RIP = (event_ptr->data[3] >> 1 ) & 0x7;
  RnW = (RIP >> 2 ) & 0x1;
  // InD = (RIP >> 1 ) & 0x1;
  //PnU = RIP & 0x1;
  InputAddr = event_ptr->data[5];
  InputAddr = (InputAddr << 32) + event_ptr->data[4];
  ec = (event_ptr->data[3] >> 8) & 0x3;
  s2 = (event_ptr->data[3] >> 7) & 0x1;
  uint64_t FA_IPA;
  uint32_t reason_stag;
  FA_IPA = event_ptr->data[7];
  FA_IPA = (FA_IPA << 32) + event_ptr->data[6];
  reason_stag = event_ptr->data[2] & 0xffff;
  uint32_t stall;
  stall = event_ptr->data[2] >> 31;
  uint32_t span;
  uint32_t rwxp;	// read/write/ececute/privilege
  span = event_ptr->data[2] & 0xf;
  rwxp = event_ptr->data[2] >> 28;
  uint32_t TTRnW;
  TTRnW = (event_ptr->data[3] >> 12) & 0x1;
  switch (event_ptr->type) {
    case EVENT_F_UUT:			// unsupported upstream transaction
      shell_msg( "Get EVENT_UUT: InputAddr = 0x%0x_%8x, RIP = 0x%0x, reason = 0x%0x", event_ptr->data[5], event_ptr->data[4], RIP, reason_stag);
      break;
    case EVENT_C_BAD_STREAMID:
      shell_msg( "Get EVENT_C_BAD_STREAMID: ");
      break;
    case EVENT_F_STE_FETCH:
      shell_msg( "Get EVENT_F_STE_FETCH: FetchAddr = 0x%0x_%8x, reason = 0x%0x", event_ptr->data[7], event_ptr->data[6], reason_stag);
      break;
    case EVENT_F_CD_FETCH:
      shell_msg( "Get EVENT_F_CD_FETCH: FetchAddr = 0x%0x_%8x, reason = 0x%0x", event_ptr->data[7], event_ptr->data[6], reason_stag);
      break;
    case EVENT_C_BAD_STE:
      shell_msg( "Get EVENT_C_BAD_STE: ");
      break;
    case EVENT_F_BAD_ATS_TREQ:
      shell_msg( "Get EVENT_F_BAD_ATS_TREQ: InputAddr = 0x%0x_%8x, span = 0x%0x, rwxp = 0x%0x", event_ptr->data[5], event_ptr->data[4], span, rwxp);
      break;
    case EVENT_F_STREAM_DISABLED:
      shell_msg( "Get EVENT_F_STREAM_DISABLED: ");
      break;
    case EVENT_F_TRANSL_FORBIDDEN:
      shell_msg( "Get EVENT_F_TRANSL_FORBIDDEN: InputAddr = 0x%0x_%8x, RnW = 0x%0x", event_ptr->data[5], event_ptr->data[4], RnW);
      break;
    case EVENT_C_BAD_SUBSTREAMID:
      shell_msg( "Get EVENT_C_BAD_SUBSTREAMID: ");
      break;
    case EVENT_F_BAD_CD:
      shell_msg( "Get EVENT_C_BAD_STE: ");
      break;
    case EVENT_F_WALK_EABT:	// external abort when fetching a TTD
      shell_msg( "Get EVENT_F_WALK_EABT: FetchAddr = 0x%0x_%8x, reason = 0x%0x, class = 0x%0x", event_ptr->data[7], event_ptr->data[6], reason_stag, ec);
      shell_msg( "InputAddr = 0x%0x_%8x, RIP = 0x%0x, s2 = 0x%0x", event_ptr->data[5], event_ptr->data[4], RIP, s2);
      break;
    case EVENT_F_TRANSLATION:
      shell_msg( "Get EVENT_F_TRANSLATION: InputAddr = 0x%0x_%8x, RIP = 0x%0x, s2 = 0x%0x", event_ptr->data[5], event_ptr->data[4], RIP, s2);
      shell_msg( "IPA = 0x%0x_%8x, stag = 0x%0x, class = 0x%0x", event_ptr->data[7], event_ptr->data[6], reason_stag, ec);
      shell_msg( "stall = %0d", stall);
      break;
    case EVENT_F_ADDR_SIZE:	// out put address caused address size fault
      shell_msg( "Get EVENT_F_ADDR_SIZE: InputAddr = 0x%0x_%8x, RIP = 0x%0x, s2 = 0x%0x", event_ptr->data[5], event_ptr->data[4], RIP, s2);
      shell_msg( "IPA = 0x%0x_%8x, stag = 0x%0x, class = 0x%0x", event_ptr->data[7], event_ptr->data[6], reason_stag, ec);
      shell_msg( "stall = %0d", stall);
      break;
    case EVENT_F_ACCESS:
      shell_msg( "Get EVENT_F_ACCESS: InputAddr = 0x%0x_%8x, RIP = 0x%0x, s2 = 0x%0x", event_ptr->data[5], event_ptr->data[4], RIP, s2);
      shell_msg( "IPA = 0x%0x_%8x, stag = 0x%0x, class = 0x%0x", event_ptr->data[7], event_ptr->data[6], reason_stag, ec);
      shell_msg( "stall = %0d", stall);
      break;
    case EVENT_F_PERMISSION:
      shell_msg( "Get EVENT_F_PERMISSION: InputAddr = 0x%0x_%8x, RIP = 0x%0x, s2 = 0x%0x", event_ptr->data[5], event_ptr->data[4], RIP, s2);
      shell_msg( "IPA = 0x%0x_%8x, stag = 0x%0x, class = 0x%0x", event_ptr->data[7], event_ptr->data[6], reason_stag, ec);
      shell_msg( "stall = %0d, TTRnW = %0d", stall, TTRnW);
      break;
    case EVENT_F_TLB_CONFLICT:
      shell_msg( "Get EVENT_C_BAD_STE: ");
      break;
    case EVENT_F_CFG_CONFLICT:
      shell_msg( "Get EVENT_C_BAD_STE: ");
      break;
    case EVENT_E_PAGE_REQUEST:
      shell_msg( "Get EVENT_C_BAD_STE: ");
      break;
  }
  shell_msg( "sid = 0x%0x, ssv = 0x%0x, ssid = 0x%0x", sid, ssv, ssid);
}

void VVDRV_qsmmuv3_check_eventq(qsmmu_profile *p_qsmmu_inst)
{
  uint64_t reg_base;
  int empty;
  reg_base = p_qsmmu_inst->s_reg_base;
  empty = VVDRV_qsmmuv3_isEventQueueEmpty(reg_base, 1);
  if (empty) {
    shell_msg( "VVDRV_qsmmuv3_check_eventq secure empty.\n");
  } else {
    shell_msg( "VVDRV_qsmmuv3_check_eventq secure not empty.\n");
    while (1) {
      event_struct event;
      VVDRV_qsmmuv3_consume_next_event(reg_base, 1, &event);
      VVDRV_qsmmuv3_process_event(p_qsmmu_inst, &event);
      if (VVDRV_qsmmuv3_isEventQueueEmpty(reg_base, 1))
        break;
    }
  }
  empty = VVDRV_qsmmuv3_isEventQueueEmpty(reg_base, 0);
  if (empty) {
    shell_msg( "VVDRV_qsmmuv3_check_eventq non-secure empty\n");
  } else {
    shell_msg( "VVDRV_qsmmuv3_check_eventq non-secure not empty\n");
    while (1) {
      event_struct event;
      VVDRV_qsmmuv3_consume_next_event(reg_base, 0, &event);
      VVDRV_qsmmuv3_process_event(p_qsmmu_inst, &event);
      if (VVDRV_qsmmuv3_isEventQueueEmpty(reg_base, 0))
        break;
    }
  }
}

/*void smmu_default_interrupt_isr(void) {
  uint32_t iar;

  shell_msg( "Inside SMMU default IRQ Handler");
  iar = HWIO_IN(IMC_GICC_IAR);
  shell_msg( "IMC_GICC_IAR = 0x%x", iar);
  HWIO_OUT(IMC_GICC_EOIR,iar);

  return ;
  }*/

