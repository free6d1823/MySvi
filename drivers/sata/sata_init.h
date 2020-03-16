/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#ifndef __BM_SATA_INIT_H__
#define __BM_SATA_INIT_H__

#include "sata_defs.h"

void sata_init(UINT32 spd);
void sata_enum(UINT32 ControllerNum);
void sata_loopback_nea(UINT32 ControllerNum, UINT32 pattern, UINT32 seconds);
void sata_loopback_phy(UINT32 ControllerNum, UINT32 TestMode, UINT32 speed,
                       UINT32 prbs);
void sata_blk_read_write(SataDevice_t *device, UINT64 lba, UINT8 *buf,
                         UINT64 buf_len, BOOLEAN is_write);
void sata_identify(UINT32 ControllerNum);
void sata_xfer_mode(UINT32 mode);
void sata_reset(UINT32 reset);
void sata_bread(UINT64 start_lba, UINT64 count);
void sata_bwrite(UINT64 start_lba, UINT64 count, UINT8 val);
void sata_multi_cmd(UINT32 cmd_cnt, UINT8 val);
void sata_reg_default_check(void);
void cbf_init(void);
void sata_clocks_set(void);

void sata_interrupt_init(UINT32 ControllerNum, UINT32 intrmask);
void sata_interrupt_deinit(UINT32 ControllerNum);
void sata_interrupt_check(UINT32 ControllerNum, UINT32 intrmask);

#endif /* __BM_SATA_INIT_H__ */
