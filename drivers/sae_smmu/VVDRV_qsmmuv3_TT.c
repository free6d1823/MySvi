#include "VVDRV_qsmmuv3_TT_dvm.h"
#include "VVDRV_qsmmuv3_program_dvm.h"
#include "VVDRV_qsmmuv3_common_dvm.h"
//#include <HALhwio.h>
#include "asm/hal/HALhwio.h"
#include "hdts_shell.h"
#include "hdts_common.h"

#define VV_MSG_FILE_NUMBER 199
//#include "shell_msg_smmu.h"
//#define DEBUG_SMMU
//extern void shell_msg(const char *fmt, ...);
void tt_write(uint64_t addr, uint64_t data, ttb_profile* p_vttb)
{
#ifdef DEBUG_SMMU
  shell_msg( "tt_write tte_addr = 0x%0x_%8x", (addr >> 32), addr);
  shell_msg( "tt_write tte = 0x%8x_%8x, p_vttb = 0x%0x", (data >> 32), data, p_vttb);
#endif
  if (p_vttb) // with nest stage
  {
    uint64_t addr_pa;
    addr_pa = do_table_walk(addr, p_vttb->ttb_addr, p_vttb->root_lvl, p_vttb->tgs, 2, 0, NULL, NULL);
    shell_msg( "tt_write tte_addr_pa = 0x%0x_%8x", (addr_pa >> 32), addr_pa);
    outp64(addr_pa, data);
  }
  else // without nest stage
  {
    outp64(addr, data);
  }
}

uint64_t tt_read(uint64_t addr, ttb_profile* p_vttb)
{
  uint64_t tte;
  if (p_vttb) // with nest stage
  {
    uint64_t addr_pa;
    addr_pa = do_table_walk(addr, p_vttb->ttb_addr, p_vttb->root_lvl, p_vttb->tgs, 2, 0, NULL, NULL);
#ifdef DEBUG_SMMU
    shell_msg( "tt_read tte_addr_pa = 0x%0x_%8x", (addr_pa >> 32), addr_pa);
#endif
    tte = inp64(addr_pa);
  }
  else // without nest stage
  {
    tte = inp64(addr);
  }
#ifdef DEBUG_SMMU
  shell_msg( "tt_read tte_addr = 0x%0x_%8x", (addr >> 32), addr);
  shell_msg( "tt_read tte = 0x%8x_%8x, p_vttb = 0x%0x", (tte >> 32), tte, p_vttb);
#endif
  return tte;
}

void VVDRV_qsmmuv3_init_ttb(ttb_profile* p_ttb, tt_tgs_e tgs, CD_TxSZ txsz, uint32_t stage, vm_profile* p_vm, ttb_profile* p_vttb)
{
  uint32_t u_txsz;
  uint32_t u_offset=0;
  uint32_t u_lvlsz=0;
  shell_msg( "VVDRV_qsmmuv3_init_ttb\n");
  p_ttb->tgs = tgs;
  p_ttb->txsz = txsz;
  p_ttb->stage = stage;
  p_ttb->p_vttb = p_vttb;

  u_txsz = 64 - txsz;
  switch (tgs) {
    case TT_TG_64K:
      u_offset = 16;
      u_lvlsz = 13;
      break;
    case TT_TG_16K:
      u_offset = 14;
      u_lvlsz = 11;
      break;
    case TT_TG_4K:
      u_offset = 12;
      u_lvlsz = 9;
      break;
  }
  p_ttb->root_lvl = 3 - ((u_txsz - u_offset - 1)/u_lvlsz);
  p_ttb->tt_ir = CD_xR_WB;//CD_xR_NC;
  p_ttb->tt_or = CD_xR_WB;//CD_xR_NC;
  p_ttb->tt_sh = CD_SHx_INNER;//CD_SHx_OUTER;
  p_ttb->nscfg = CD_NSCFG_SECURE;
  if (p_vm == NULL) {
    system_profile *p_sys_profile = VVDRV_qsmmuv3_get_sys_profile(0);
    p_ttb->p_vm_profile = &(p_sys_profile->hyper_profile);
    shell_msg("page_4k_alloc_base=%02x,tt_4k_alloc_base=%02x.\n",p_sys_profile->hyper_profile.page_4k_alloc_base,p_sys_profile->hyper_profile.tt_4k_alloc_base);
    shell_msg("s_cd_alloc_base=%02x,s_st_alloc_base=%02x.\n",p_sys_profile->hyper_profile.s_cd_alloc_base,p_sys_profile->s_st_alloc_base);
  }
  else {
    p_ttb->p_vm_profile = p_vm;
  }
  // ttb_addr should be IPA if nested
  //p_ttb->ttb_addr = alloc_pg(tgs, p_ttb->p_vm_profile, p_vttb, 1);
  print_ttb_profile(p_ttb);
}

void print_ttb_profile(ttb_profile* p_ttb)
{
#ifdef DEBUG_SMMU
  shell_msg( "ttb_profile: tgs = 0x%0x, root_lvl = 0x%0x, ttb_addr = 0x%0x_%8x", p_ttb->tgs, p_ttb->root_lvl, (p_ttb->ttb_addr >> 32), p_ttb->ttb_addr);
  shell_msg( "ttb_profile: txsz = %d, p_vttb = 0x%0x, stage = %d\n", 64 - p_ttb->txsz, p_ttb->p_vttb, p_ttb->stage);
#endif
  if (p_ttb->p_vttb)
  {
    shell_msg( "its nested stage 2 ttb is ");
    print_ttb_profile(p_ttb->p_vttb);
  }
}

// this return PA even if nested
uint64_t VVDRV_qsmmuv3_create_page(ttb_profile* p_ttb, uint64_t va)
{  
  uint64_t page_addr_base;
  shell_msg( "VVDRV_qsmmuv3_create_page va = 0x%0x_%0x for.\n", va >> 32, va);
  print_ttb_profile(p_ttb);

  uint64_t tt_base = p_ttb->ttb_addr; 
  tt_level_e root_lvl = p_ttb->root_lvl; 
  tt_tgs_e tgs = p_ttb->tgs;
  uint32_t stage = p_ttb->stage;
  ttb_profile* p_vttb = p_ttb->p_vttb;
  vm_profile* p_vm = p_ttb->p_vm_profile;
  page_addr_base = do_table_walk(va, tt_base, root_lvl, tgs, stage, 1, p_vm, p_vttb);

  // this assum do_table_walk return IPA when nested 
  if (p_vttb)
  {
    page_addr_base = do_table_walk(page_addr_base, p_vttb->ttb_addr, p_vttb->root_lvl, p_vttb->tgs, p_vttb->stage, 1, p_vttb->p_vm_profile, NULL);
  }

  return page_addr_base;
}

uint64_t VVDRV_qsmmuv3_lookup(ttb_profile* p_ttb, uint64_t va, int b_ipa)
{
  uint64_t pa;

  shell_msg( "VVDRV_qsmmuv3_lookup va = 0x%0x_%8x for ", va >> 32, va);
  print_ttb_profile(p_ttb);

  uint64_t tt_base = p_ttb->ttb_addr; 
  tt_level_e root_lvl = p_ttb->root_lvl; 
  tt_tgs_e tgs = p_ttb->tgs;
  uint32_t stage = p_ttb->stage;
  ttb_profile* p_vttb = p_ttb->p_vttb;
  vm_profile* p_vm = p_ttb->p_vm_profile;
  pa = do_table_walk(va, tt_base, root_lvl, tgs, stage, 0, p_vm, p_vttb);

  if (p_vttb && (b_ipa == 0))
  {
    pa = do_table_walk(pa, p_vttb->ttb_addr, p_vttb->root_lvl, p_vttb->tgs, p_vttb->stage, 0, NULL, NULL);
  }

  return pa;
}

// this return IPA if nested
uint64_t do_table_walk(uint64_t va, uint64_t tt_base, tt_level_e current_lvl, tt_tgs_e tgs, uint32_t stage, int b_create, vm_profile* p_vm, ttb_profile* p_vttb)
{
#ifdef DEBUG_SMMU
  shell_msg( "do_table_walk: va = 0x%0x_%8x, level = 0x%0x, ", va >> 32, va, current_lvl);
  shell_msg( "do_table_walk: tt_base = 0x%0x_%8x", tt_base >> 32, tt_base);
  shell_msg( "do_table_walk: tgs = 0x%0x, create = 0x%0x", tgs, b_create);
#endif
  if (p_vttb)
  {
    shell_msg( "do_table_walk with nested ");
    print_ttb_profile(p_vttb);
  }

  // read tte
  uint32_t lvl_shift = 12+(2*tgs) + (9+(2*tgs))*(3-current_lvl);
  uint64_t lvl_mask = (TT_TG_4K == tgs) ? 0x1FF : (TT_TG_16K == tgs) ? 0x7FF : 0x1FFF;
  uint64_t lvl_idx = (va >> lvl_shift) & lvl_mask;
  uint64_t tte_addr = tt_base + (lvl_idx << 3);
  uint64_t tte = tt_read(tte_addr, p_vttb);

  // decode tte
  uint64_t output_addr;
  uint32_t lower_attr;
  uint32_t upper_attr;
  uint32_t b_valid;
  uint32_t b_not_block;

  b_valid = tte & 0x1;
  b_not_block = (tte >> 1) & 0x1;
  if (b_valid)
  {
    output_addr = tte & 0xfffffffff000;
    lower_attr = (tte >> 2) & 0x3ff;
    upper_attr = (tte >> 52) & 0xfff;

    uint32_t b_is_block = (0 == b_not_block) && (TT_LVL_3 > current_lvl);
#ifdef DEBUG_SMMU
    shell_msg( "do_table_walk: tte valid. output_addr = 0x%0x_%8x, current_lvl = 0x%0x\n", output_addr >> 32, output_addr, current_lvl);
    shell_msg( "do_table_walk: tte valid. lower_attr = 0x%0x, upper_attr = 0x%0x", lower_attr, upper_attr);
#endif
    if (b_is_block || (TT_LVL_3 == current_lvl))  // last level
    {
      uint64_t offset_mask = (1 << lvl_shift) - 1;
      uint64_t pa = output_addr + (va & offset_mask);
      shell_msg( "tte valid,do_table_walk: va = 0x%0x_%8x, pa = 0x%0x_%8x\n", va >> 32, va, pa >> 32, pa);
      return pa;
      //if (p_vttb)  // nested
      //{
      //  uint64_t nest_pa = do_table_walk(pa, p_vttb->ttb_addr, p_vttb->root_lvl, p_vttb->tgs, p_vttb->stage, b_create, p_vttb->p_vm_profile, NULL);
      //  return nest_pa;
      //}
      //else // final
      //{
      //  return pa;
      //}
    }
    else // not last level, output_addr is next-level table address
    {
#ifdef DEBUG_SMMU
      shell_msg( "do_table_walk: go to next level\n");
#endif
      return do_table_walk(va, output_addr, current_lvl + 1, tgs, stage, b_create, p_vm, p_vttb);
    }
  }
  else // not valid
  {
    if (b_create)  // if create when invalid
    {
      if (TT_LVL_3 == current_lvl)  // last level, create data page
      {
        output_addr = alloc_pg(tgs, p_vm, p_vttb, 0);
        // AP[2:1] Data Access Permissions bits, does not define an AP[0] bit
        // AP[1] is valid only for a stage 1 translation that supports two VA ranges.
        // It is RES0 for stage 1 translations that support only one VA range.
        // set AP = 01  lower_attr[7:6]
        //
        // for stage 2, it's S2AP
        //     S2AP	Access from NS_EL1/0
        //     00		None
        //     01		R
        //     10		W
        //     11		R/W
        //
        // nG need be set to 1, otherwise ASID will not be put as tag for TLB lookup
        // future implment need to add these as input paramter for customization.
        uint32_t AP_21;
        if (stage == 2)
          AP_21 = 3;
        else
          AP_21 = 1;
        lower_attr = 0x200 | (AP_21 << 4) ;  // nG=1, AF, SH[1:0], AP[2:1], NS, AttrIndx[2:0]
        upper_attr = 0;  // ignored, UXN, PXN, contiguous. stage 1 only.
        tte = 3 + (lower_attr << 2) + output_addr + (((uint64_t)upper_attr) << 52);
        shell_msg( "do_table_walk: create new data page, page_addr_base = 0x%02x_%02x, tte_addr = 0x%02x_%02x,tte = 0x%02x_%02x\n", output_addr >> 32, output_addr,tte_addr>>32,tte_addr, tte >> 32, tte);
        tt_write(tte_addr, tte, p_vttb);

        uint64_t offset_mask = (1 << lvl_shift) - 1;
        uint64_t pa = output_addr + (va & offset_mask);
        shell_msg( "tte not valid,do_table_walk: va = 0x%02x_%02x, pa = 0x%02x_%02x\n", va >> 32, va, pa >> 32, pa);
        return pa;
      }
      else // not last level, create table page
      {
        output_addr = alloc_pg(tgs, p_vm, p_vttb, 1);

        lower_attr = 0;  // ignored
        upper_attr = 0;  // NS,AP[1:0],XN,PXN, ignored. stage 1 only.
        tte = 3 + (lower_attr << 2) + output_addr + (((uint64_t)upper_attr) << 52);
#ifdef DEBUG_SMMU
        shell_msg( "do_table_walk: create new table page, page_addr_base = 0x%0x_%8x, tte = 0x%8x_%8x\n", output_addr >> 32, output_addr, tte >> 32, tte);
#endif
        tt_write(tte_addr, tte, p_vttb);

        return do_table_walk(va, output_addr, current_lvl + 1, tgs, stage, b_create, p_vm, p_vttb);
      }
    }
    else  // then report miss
    {
      //vv_msg(SEV_ERROR, ST_FUNCTION, "table walk miss");
      return 0xffffffffffffffff;
    }
  }
}

void VVDRV_qsmmuv3_create_IMC_tt(ttb_profile* p_ttb)
{
  uint64_t desc_addr;
  uint64_t desc_base;
  desc_base = p_ttb->ttb_addr;

  desc_addr = desc_base;
  outp64(desc_addr, 0x0000000000000641);
  desc_addr += 0x08;
  outp64(desc_addr, 0x0000000020000661);
  desc_addr += 0x08;
  outp64(desc_addr, 0x0000000040000661);
  desc_addr += 0x08;
  outp64(desc_addr, 0x0000000060000661);
  desc_addr += 0x08;
  outp64(desc_addr, 0x0000080000000661);
  desc_addr += 0x08;
  outp64(desc_addr, 0x00000A0000000641);
  desc_addr += 0x08;
  outp64(desc_addr, 0x00000C0000000641);
  desc_addr += 0x08;
  outp64(desc_addr, 0x00000E0000000641);
  desc_addr += 0x08;

  desc_addr = desc_base + (2040 * 8);
  outp64(desc_addr, 0x000000FF00000641);
  desc_addr += 0x08;
  outp64(desc_addr, 0x000000FF20000641);
  desc_addr += 0x08;
  outp64(desc_addr, 0x000000FF40000641);
  desc_addr += 0x08;
  outp64(desc_addr, 0x000000FF60000641);
  desc_addr += 0x08;
  outp64(desc_addr, 0x000000FF80000641);


  desc_addr = desc_base + (1800 * 8);
  outp64(desc_addr, 0x00000BFFC0000641);

  desc_addr = desc_base + (1801 * 8);
  outp64(desc_addr, 0x00000BFFE0000641);

  desc_addr = desc_base + (1808 * 8);
  outp64(desc_addr, 0x00000BFFC0000661);

  desc_addr = desc_base + (1809 * 8);
  outp64(desc_addr, 0x00000BFFE0000661);
  desc_addr = desc_base + (1816 * 8);
  outp64(desc_addr, 0x00000FFFC0000641);

  desc_addr = desc_base + (1817 * 8);
  outp64(desc_addr, 0x00000FFFE0000641);

  desc_addr = desc_base + (1824 * 8);
  outp64(desc_addr, 0x00000FFFC0000661);

  desc_addr = desc_base + (1825 * 8);
  outp64(desc_addr, 0x00000FFFE0000661);

  return;
}

// return ipa if nested
uint64_t alloc_pg(tt_tgs_e tgs, vm_profile* p_vm, ttb_profile* p_vttb, int b_tt)
{
  uint64_t tt_addr;
  uint64_t tt_addr_pa;
  tt_addr = VVDRV_qsmmuv3_alloc_page(tgs, p_vm, b_tt);
  if (p_vttb) // with nest stage
  {
    tt_addr_pa = VVDRV_qsmmuv3_create_page(p_vttb, tt_addr);
  }
  else {
    tt_addr_pa = tt_addr;
  }
  if (b_tt) {
    // zero page content
    int size_B;
    if (TT_TG_4K == tgs)
      size_B = 0x1000;
    if (TT_TG_64K == tgs)
      size_B = 0x10000;
    if (TT_TG_16K == tgs)
      size_B = 0x4000;
    VVDRV_qsmmuv3_zero_mem(tt_addr_pa, size_B);
  }
  return tt_addr;
}

