#ifndef __VVDRV_QSMMUV3_TT_H__
#define __VVDRV_QSMMUV3_TT_H__

#include "VVDRV_qsmmuv3_profile_dvm.h"

void tt_write(uint64_t addr, uint64_t data, ttb_profile* p_vttb);
uint64_t tt_read(uint64_t addr, ttb_profile* p_vttb);

///////////////////////////////////////////////////////////////////////////////
// Name: VVDRV_qsmmuv3_init_ttb
// Desc: create initial translation table
//       with root level table memory allocated and all entry invalidated.
//       if nested with p_vttb valid, ttb_addr is IPA
//       use default root level
///////////////////////////////////////////////////////////////////////////////
void VVDRV_qsmmuv3_init_ttb(ttb_profile* p_ttb, tt_tgs_e tgs, CD_TxSZ txsz, uint32_t stage, vm_profile* p_vm, ttb_profile* p_vttb);

///////////////////////////////////////////////////////////////////////////////
// Name: VVDRV_qsmmuv3_create_page
// Desc: create a date page in translation table
//       returned addr is PA even nested.
///////////////////////////////////////////////////////////////////////////////
uint64_t VVDRV_qsmmuv3_create_page(ttb_profile* p_ttb, uint64_t va);

///////////////////////////////////////////////////////////////////////////////
// Name: alloc_pg
// Desc: allocate a new page
//       if nested with p_vttb valid, ttb_addr is IPA
//       this function will handle nested case
//       if tt page, will zero mem
///////////////////////////////////////////////////////////////////////////////
uint64_t alloc_pg(tt_tgs_e tgs, vm_profile* p_vm, ttb_profile* p_vttb, int b_tt);

uint64_t do_table_walk(uint64_t va, uint64_t tt_base, tt_level_e current_lvl, tt_tgs_e tgs, uint32_t stage, int b_create, vm_profile* p_vm, ttb_profile* p_vttb);

void print_ttb_profile(ttb_profile* p_ttb);
void VVDRV_qsmmuv3_create_IMC_tt(ttb_profile* p_ttb);
uint64_t VVDRV_qsmmuv3_lookup(ttb_profile* p_ttb, uint64_t va, int b_ipa);
#endif
