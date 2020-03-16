/*
 * ABSTRACT : Register definition header file for 
 */
#define AXI_block_BaseAddress 0x0

#define AXI_block_BaseAddress 0x0

#define AXI_block_BaseAddress 0x0

#define AXI_block_BaseAddress 0x0

#define REGB_DDRC_CH0_BaseAddress 0x10000

/* Register MSTR0 */
/* Master Register0 */
// #define MSTR0 (REGB_DDRC_CH0_BaseAddress + 0x0)
#define MSTR0_RegisterSize 32
#define MSTR0_RegisterResetValue 0x3040000
#define MSTR0_RegisterResetMask 0xffffffff

/* Register Field information for MSTR0 */

/* Register MSTR0 field lpddr4 */
/* 
 Select LPDDR4 SDRAM
 - 1 - LPDDR4 SDRAM device in use.
 - 0 - non-LPDDR4 device in use
Present only in designs configured to support LPDDR4 SDRAM memories. */
#define MSTR0_lpddr4_BitAddressOffset 1
#define MSTR0_lpddr4_RegisterSize 1

/* Register MSTR0 field lpddr5 */
/* 
 Select LPDDR5 SDRAM
 - 1 - LPDDR5 SDRAM device in use.
 - 0 - non-LPDDR5 device in use
Present only in designs configured to support LPDDR5 SDRAM memories. */
#define MSTR0_lpddr5_BitAddressOffset 3
#define MSTR0_lpddr5_RegisterSize 1

/* Register MSTR0 field en_2t_timing_mode */
/* If 1, then the DDR controller uses 2T timing. Otherwise, uses 1T timing. In 2T timing, all command signals (except chip select) are held for 2 clocks on the SDRAM bus. Chip select is asserted on the second cycle of the command


Note: 
 - 2T timing is not supported in LPDDR4 mode
 - 2T timing is not supported if the configuration parameter MEMC_CMD_RTN2IDLE is set
 - 2T timing is not supported in DDR4 geardown mode.
 - 2T timing is not supported in Shared-AC dual channel mode and the register value is don't care. */
#define MSTR0_en_2t_timing_mode_BitAddressOffset 10
#define MSTR0_en_2t_timing_mode_RegisterSize 1

/* Register MSTR0 field data_bus_width */
/* Selects proportion of DQ bus width that is used by the SDRAM
 - 00 - Full DQ bus width to SDRAM
 - 01 - Half DQ bus width to SDRAM
 - 10 - Quarter DQ bus width to SDRAM
 - 11 - Reserved.
Note that half bus width mode is only supported when the SDRAM bus width is a multiple of 16, and quarter bus width mode is only supported when the SDRAM bus width is a multiple of 32 and the configuration parameter MEMC_QBUS_SUPPORT is set. Bus width refers to DQ bus width (excluding any ECC width). */
#define MSTR0_data_bus_width_BitAddressOffset 12
#define MSTR0_data_bus_width_RegisterSize 2

/* Register MSTR0 field burst_rdwr */
/* SDRAM burst length used:
 - 00100 - Burst length of 8
 - 01000 - Burst length of 16
 - 10000 - Burst length of 32
 All other values are reserved.

 This controls the burst size used to access the SDRAM. This must match the burst length mode register setting in the SDRAM.

 For DDR4, this must be set to 0x00100 (BL8). 

 For LPDDR4/LPDDR5/DDR5, this must be set to 0x01000 (BL16). 

 For DDR5 BL32, this must be set to 0x10000 (BL32). */
#define MSTR0_burst_rdwr_BitAddressOffset 16
#define MSTR0_burst_rdwr_RegisterSize 5

/* Register MSTR0 field active_ranks */
/* Only present for multi-rank configurations.

Each bit represents one rank. For two-rank configurations, only bits[25:24] are present.
 - 1 - populated
 - 0 - unpopulated
LSB is the lowest rank number.

For 2 ranks following combinations are legal:
 - 01 - One rank
 - 11 - Two ranks
 - Others - Reserved.
For 4 ranks following combinations are legal:
 - 0001 - One rank
 - 0011 - Two ranks
 - 1111 - Four ranks
 */
#define MSTR0_active_ranks_BitAddressOffset 24
#define MSTR0_active_ranks_RegisterSize 2

/* End of Register Definition for MSTR0 */

/* Register MSTR4 */
/* Master Register4 */
// #define MSTR4 (REGB_DDRC_CH0_BaseAddress + 0x10)
#define MSTR4_RegisterSize 32
#define MSTR4_RegisterResetValue 0x0
#define MSTR4_RegisterResetMask 0xffffffff

/* Register Field information for MSTR4 */

/* Register MSTR4 field wck_on */
/* WCK always ON mode
  - 0: WCK Always On mode disabled
  - 1: WCK Always On mode enabled
  In case of multi-rank system, the controller issues CAS-WS_FS to all ranks to sets DRAM in sync state simultaneously.

  The PHY might have a limitation at enabling WCK always ON mode.

  Please see the PHY databook. */
#define MSTR4_wck_on_BitAddressOffset 0
#define MSTR4_wck_on_RegisterSize 1

/* End of Register Definition for MSTR4 */

/* Register STAT */
/* Operating Mode Status Register */
// #define STAT (REGB_DDRC_CH0_BaseAddress + 0x14)
#define STAT_RegisterSize 32
#define STAT_RegisterResetValue 0x0
#define STAT_RegisterResetMask 0xffffffff

/* Register Field information for STAT */

/* Register STAT field operating_mode */
/* Operating mode.

DDR4/DDR5 designs:
 - 000 - Init
 - 001 - Normal
 - 010 - Power-down   (For DDR4, this means all ranks are in power-down state. For DDR5, this means at least one rank is in power-down state, check powerdown_state for details)
 - 011 - Self refresh (For DDR4/DDR5, this means all ranks are in self refresh state, check selfref_type for details)
 - 1XX - Maximum Power Saving Mode (For DDR4 only)
LPDDR4/LPDDR5designs:
 - 000 - Init
 - 001 - Normal
 - 010 - Power-down
 - 011 - Self refresh / Self refresh power-down
 */
#define STAT_operating_mode_BitAddressOffset 0
#define STAT_operating_mode_RegisterSize 3

/* Register STAT field selfref_type */
/* Flags if Self Refresh (except LPDDR4/5) or SR-Powerdown (LPDDR4/5) is entered and if it was under Automatic Self Refresh control only or not.    
 - 00 - SDRAM is not in Self Refresh (except LPDDR4/5) or SR-Powerdown (LPDDR4/5). If retry is enabled by CRCPARCTRL1.crc_parity_retry_enable, this also indicates SRE command is still in parity error window or retry is in-progress.
 - 11 - SDRAM is in Self Refresh (except LPDDR4/5) or SR-Powerdown (LPDDR4/5), which was caused by Automatic Self Refresh only. If retry is enabled, this guarantees SRE command is executed correctly without parity error.
 - 10 - SDRAM is in Self Refresh (except LPDDR4/5) or SR-Powerdown (LPDDR4/5), which was not caused solely under Automatic Self Refresh control. It could have been caused by Hardware Low Power Interface and/or Software (PWRCTL.selfref_sw). If retry is enabled, this guarantees SRE command is executed correctly without parity error.
 - 01 - SDRAM is in Self Refresh, which was caused by PHY Master Request.
 
For LPDDR54 and DDR4, only bit[5:4] are used.

 For DDR5, self-refresh per rank control is supported.
  - bit[5:4]   - rank 0 selfref_type
  - bit[7:6]   - rank 1 selfref_type
  - bit[9:8]   - rank 2 selfref_type
  - bit[11:10] - rank 3 selfref_type
 */
#define STAT_selfref_type_BitAddressOffset 4
#define STAT_selfref_type_RegisterSize 2

/* Register STAT field selfref_state */
/* Self refresh state. This indicates self refresh or self refresh power down state or Deep Sleep Mode (LPDDR5 only).

This register is used for frequency change and MRR/MRW access during self refresh.
 - 000 - SDRAM is not in Self Refresh.
 - 001 - Self refresh 1
 - 010 - Self refresh power down
 - 011 - Self refresh 2
 - 100 - Deep Sleep Mode (LPDDR5 only) */
#define STAT_selfref_state_BitAddressOffset 12
#define STAT_selfref_state_RegisterSize 3

/* Register STAT field selfref_cam_not_empty */
/* Self refresh with CAMs not empty.

Set to 1 when Self Refresh is entered but CAMs are not drained. Cleared after exiting Self Refresh. */
#define STAT_selfref_cam_not_empty_BitAddressOffset 16
#define STAT_selfref_cam_not_empty_RegisterSize 1

/* End of Register Definition for STAT */

/* Register MRCTRL0 */
/* Mode Register Read/Write Control Register 0. */
// #define MRCTRL0 (REGB_DDRC_CH0_BaseAddress + 0x80)
#define MRCTRL0_RegisterSize 32
#define MRCTRL0_RegisterResetValue 0x30
#define MRCTRL0_RegisterResetMask 0xffffffff

/* Register Field information for MRCTRL0 */

/* Register MRCTRL0 field mr_type */
/* Indicates whether the mode register operation is read or write.
 - 0 - Write
 - 1 - Read

Only used for LPDDR4/LPDDR5/DDR4. */
#define MRCTRL0_mr_type_BitAddressOffset 0
#define MRCTRL0_mr_type_RegisterSize 1

/* Register MRCTRL0 field sw_init_int */
/* Indicates whether Software intervention is allowed via MRCTRL0/MRCTRL1 before automatic SDRAM initialization routine or not.

For DDR4, this bit can be used to initialize the DDR4 RCD (MR7) before automatic SDRAM initialization.

For LPDDR4/5, this bit can be used to program additional mode registers before automatic SDRAM initialization if necessary.

In LPDDR4 dual channel mode, note that this must be programmed to both channels beforehand.

Note that this must be cleared to 0 after completing Software operation. Otherwise, SDRAM initialization routine will not re-start.
 - 0 - Software intervention is not allowed
 - 1 - Software intervention is allowed

Don't Care for DDR5. */
#define MRCTRL0_sw_init_int_BitAddressOffset 3
#define MRCTRL0_sw_init_int_RegisterSize 1

/* Register MRCTRL0 field mr_rank */
/* Controls which rank is accessed by MRCTRL0.mr_wr. Normally, it is desired to access all ranks, so all bits must be set to 1. However, for multi-rank UDIMMs/RDIMMs/LRDIMMs which implement address mirroring, it may be necessary to access ranks individually.

Examples (assume DDRCTL is configured for 4 ranks):
    - 0x1 - select rank 0 only
    - 0x2 - select rank 1 only
    - 0x5 - select ranks 0 and 2
    - 0xA - select ranks 1 and 3
    - 0xF - select ranks 0, 1, 2 and 3

Don't Care for DDR5. */
#define MRCTRL0_mr_rank_BitAddressOffset 4
#define MRCTRL0_mr_rank_RegisterSize 2

/* Register MRCTRL0 field mr_addr */
/* Address of the mode register that is to be written to.
 - 0000 - MR0
 - 0001 - MR1
 - 0010 - MR2
 - 0011 - MR3
 - 0100 - MR4
 - 0101 - MR5
 - 0110 - MR6
 - 0111 - MR7
This signal is also used for writing to control words of the register chip on RDIMMs/LRDIMMs. In that case, it corresponds to the bank address bits sent to the RDIMM/LRDIMM.

In case of DDR4, the bit[3:2] corresponds to the bank group bits. Therefore, the bit[3] as well as the bit[2:0] must be set to an appropriate value which is considered both the Address Mirroring of UDIMMs/RDIMMs/LRDIMMs and the Output Inversion of RDIMMs/LRDIMMs.

Don't Care for LPDDR4/5 (see MRCTRL1.mr_data for mode register addressing in LPDDR4/5).

Don't Care for DDR5 (see CMDCTL.cmd_ctrl for MRW/MRR access in DDR5). */
#define MRCTRL0_mr_addr_BitAddressOffset 12
#define MRCTRL0_mr_addr_RegisterSize 4

/* Register MRCTRL0 field mrr_done_clr */
/* If this bit is set, mrr_done will be cleared by the controller. */
#define MRCTRL0_mrr_done_clr_BitAddressOffset 24
#define MRCTRL0_mrr_done_clr_RegisterSize 1

/* Register MRCTRL0 field mr_wr */
/* Setting this register bit to 1 triggers a mode register read or write operation.

When the MR operation is complete, the DDRCTL automatically clears this bit.
 The other register fields of this register must be written in a separate APB transaction, before setting this mr_wr bit. It is recommended NOT to set this signal if in Init, Deep power-down or MPSM operating modes. */
#define MRCTRL0_mr_wr_BitAddressOffset 31
#define MRCTRL0_mr_wr_RegisterSize 1

/* End of Register Definition for MRCTRL0 */

/* Register MRCTRL1 */
/* Mode Register Read/Write Control Register 1 */
// #define MRCTRL1 (REGB_DDRC_CH0_BaseAddress + 0x84)
#define MRCTRL1_RegisterSize 32
#define MRCTRL1_RegisterResetValue 0x0
#define MRCTRL1_RegisterResetMask 0xffffffff

/* Register Field information for MRCTRL1 */

/* Register MRCTRL1 field mr_data */
/* Mode register write data for DDR4 mode.

For LPDDR4/5, MRCTRL1[15:0] are interpreted as
 - [15:8] MR Address
 - [7:0] MR data for writes, don't care for read
This is 18-bit wide in configurations with DDR4 support and 16-bits for the LPDDR5/4 controller.

Don't Care for DDR5 (see CMDCTL.cmd_ctrl for MRW access in DDR5). */
#define MRCTRL1_mr_data_BitAddressOffset 0
#define MRCTRL1_mr_data_RegisterSize 18

/* End of Register Definition for MRCTRL1 */

/* Register MRSTAT */
/* Mode Register Read/Write Status Register */
// #define MRSTAT (REGB_DDRC_CH0_BaseAddress + 0x90)
#define MRSTAT_RegisterSize 32
#define MRSTAT_RegisterResetValue 0x0
#define MRSTAT_RegisterResetMask 0xffffffff

/* Register Field information for MRSTAT */

/* Register MRSTAT field mr_wr_busy */
/* The SoC core may initiate a MR write operation only if this signal is low. This signal goes high in the clock after the DDRCTL accepts the MRW/MRR request. It goes low when the MRW/MRR command is issued to the SDRAM. It is recommended not to perform MRW/MRR commands when 'MRSTAT.mr_wr_busy' is high.
 - 0 - Indicates that the SoC core can initiate a mode register write operation
 - 1 - Indicates that mode register write operation is in progress */
#define MRSTAT_mr_wr_busy_BitAddressOffset 0
#define MRSTAT_mr_wr_busy_RegisterSize 1

/* Register MRSTAT field mrr_done */
/* This signal goes high when the controller received MRR data which is triggered by MRCTRL0.mr_wr.
  This signal is cleared by mrr_done_clr */
#define MRSTAT_mrr_done_BitAddressOffset 16
#define MRSTAT_mrr_done_RegisterSize 1

/* End of Register Definition for MRSTAT */

/* Register MRRDATA0 */
/* Mode Register Read Data 0 */
// #define MRRDATA0 (REGB_DDRC_CH0_BaseAddress + 0x94)
#define MRRDATA0_RegisterSize 32
#define MRRDATA0_RegisterResetValue 0x0
#define MRRDATA0_RegisterResetMask 0xffffffff

/* Register Field information for MRRDATA0 */

/* Register MRRDATA0 field mrr_data_lwr */
/* MRR data for DQ[31:0] 

  This register is updated when the controller issued MRR command triggered by MRCTRL register. */
#define MRRDATA0_mrr_data_lwr_BitAddressOffset 0
#define MRRDATA0_mrr_data_lwr_RegisterSize 32

/* End of Register Definition for MRRDATA0 */

/* Register MRRDATA1 */
/* Mode Register Read Data 1 */
// #define MRRDATA1 (REGB_DDRC_CH0_BaseAddress + 0x98)
#define MRRDATA1_RegisterSize 32
#define MRRDATA1_RegisterResetValue 0x0
#define MRRDATA1_RegisterResetMask 0xffffffff

/* Register Field information for MRRDATA1 */

/* Register MRRDATA1 field mrr_data_upr */
/* MRR data for DQ[63:32] 

  This register is updated when the controller issued MRR command triggered by MRCTRL register. */
#define MRRDATA1_mrr_data_upr_BitAddressOffset 0
#define MRRDATA1_mrr_data_upr_RegisterSize 32

/* End of Register Definition for MRRDATA1 */

/* Register DERATECTL0 */
/* Temperature Derate Control Register 0 */
// #define DERATECTL0 (REGB_DDRC_CH0_BaseAddress + 0x100)
#define DERATECTL0_RegisterSize 32
#define DERATECTL0_RegisterResetValue 0x8
#define DERATECTL0_RegisterResetMask 0xffffffff

/* Register Field information for DERATECTL0 */

/* Register DERATECTL0 field derate_enable */
/* Enables derating
 - 0 - Timing parameter derating is disabled
 - 1 - Timing parameter derating is enabled using MR4 read value.
 */
#define DERATECTL0_derate_enable_BitAddressOffset 0
#define DERATECTL0_derate_enable_RegisterSize 1

/* Register DERATECTL0 field lpddr4_refresh_mode */
/* Selects the LPDDR4 refresh mode
 - 0 - Legacy refresh mode
 - 1 - Modified refresh mode
 */
#define DERATECTL0_lpddr4_refresh_mode_BitAddressOffset 1
#define DERATECTL0_lpddr4_refresh_mode_RegisterSize 1

/* Register DERATECTL0 field derate_mr4_pause_fc */
/* Pauses MR4 reads. Must only be set to 1 as part of Frequency Change procedures, if DERATECTL0.derate_enable=1 */
#define DERATECTL0_derate_mr4_pause_fc_BitAddressOffset 2
#define DERATECTL0_derate_mr4_pause_fc_RegisterSize 1

/* Register DERATECTL0 field dis_trefi_x6x8 */
/* Disables 8x tREFI and 6x tREFI refresh rate for derating.When this register filed is set to 1, controller behaves like 4x tREFI refresh rate mode even though in 8x tREFI and 6x tREFI mode.
 - 0 - Enable 6x tREFI and 8x tREFI refresh rate
 - 1 - Disable 6x tREFI and 8x tREFI refresh rate
Note: This register field is only applicable for designs supporting LPDDR5 SDRAM. 
 */
#define DERATECTL0_dis_trefi_x6x8_BitAddressOffset 3
#define DERATECTL0_dis_trefi_x6x8_RegisterSize 1

/* End of Register Definition for DERATECTL0 */

/* Register DERATECTL1 */
/* Temperature Derate Control Register 1 */
// #define DERATECTL1 (REGB_DDRC_CH0_BaseAddress + 0x104)
#define DERATECTL1_RegisterSize 32
#define DERATECTL1_RegisterResetValue 0x0
#define DERATECTL1_RegisterResetMask 0xffffffff

/* Register Field information for DERATECTL1 */

/* Register DERATECTL1 field active_derate_byte_rank0 */
/* Indicates which byte of the MRR data is used for derating in rank0. The each bit corresponds each byte. All "0"s is invalid, if DERATECTL0.derate_enable=1. This register only supports LPDDR4, LPDDR5 and DDR5.

For LPDDR4 and LPDDR5 : Valid width is MEMC_DRAM_DATA_WIDTH/8. This bit[n]=1 means that DQ[8*n+:8] is valid MRR data.

For DDR5 : Valid width is MEMC_DRAM_TOTAL_DATA_WIDTH/device DQ width. Device DQ width is based on dram_dq_width register value.

      - 2'h0 - x4 DQ DRAM device
      - 2'h1 - x8 DQ DRAM device
      - 2'h2 - x16 DQ DRAM device */
#define DERATECTL1_active_derate_byte_rank0_BitAddressOffset 0
#define DERATECTL1_active_derate_byte_rank0_RegisterSize 8

/* End of Register Definition for DERATECTL1 */

/* Register DERATECTL2 */
/* Temperature Derate Control Register 2 */
// #define DERATECTL2 (REGB_DDRC_CH0_BaseAddress + 0x108)
#define DERATECTL2_RegisterSize 32
#define DERATECTL2_RegisterResetValue 0x0
#define DERATECTL2_RegisterResetMask 0xffffffff

/* Register Field information for DERATECTL2 */

/* Register DERATECTL2 field active_derate_byte_rank1 */
/* Indicates which byte of the MRR data is used for derating in rank1. The each bit corresponds each byte. All "0"s is invalid, if DERATECTL0.derate_enable=1. This register only supports LPDDR4, LPDDR5 and DDR5.
 
For LPDDR4 and LPDDR5 : Valid width is MEMC_DRAM_DATA_WIDTH/8. This bit[n]=1 means that DQ[8*n+:8] is valid MRR data.

For DDR5 : Valid width is MEMC_DRAM_TOTAL_DATA_WIDTH/device DQ width. Device DQ width is based on dram_dq_width register value.

      - 2'h0 - x4 DQ DRAM device
      - 2'h1 - x8 DQ DRAM device
      - 2'h2 - x16 DQ DRAM device */
#define DERATECTL2_active_derate_byte_rank1_BitAddressOffset 0
#define DERATECTL2_active_derate_byte_rank1_RegisterSize 8

/* End of Register Definition for DERATECTL2 */

/* Register DERATECTL5 */
/* Temperature Derate Control Register 5 */
// #define DERATECTL5 (REGB_DDRC_CH0_BaseAddress + 0x114)
#define DERATECTL5_RegisterSize 32
#define DERATECTL5_RegisterResetValue 0x1
#define DERATECTL5_RegisterResetMask 0xffffffff

/* Register Field information for DERATECTL5 */

/* Register DERATECTL5 field derate_temp_limit_intr_en */
/* Interrupt enable bit for derate_temp_limit_intr output pin.
  -  1 Enabled
  -  0 Disabled
 */
#define DERATECTL5_derate_temp_limit_intr_en_BitAddressOffset 0
#define DERATECTL5_derate_temp_limit_intr_en_RegisterSize 1

/* Register DERATECTL5 field derate_temp_limit_intr_clr */
/* Interrupt clear bit for derate_temp_limit_intr.
  At the end of the interrupt clear operation, the DDRCTL automatically clears this bit. */
#define DERATECTL5_derate_temp_limit_intr_clr_BitAddressOffset 1
#define DERATECTL5_derate_temp_limit_intr_clr_RegisterSize 1

/* Register DERATECTL5 field derate_temp_limit_intr_force */
/* Interrupt force bit for derate_temp_limit_intr. 
  Setting this register to 1 will cause the derate_temp_limit_intr output pin to be asserted.
  At the end of the interrupt force operation, the DDRCTL automatically clears this bit. */
#define DERATECTL5_derate_temp_limit_intr_force_BitAddressOffset 2
#define DERATECTL5_derate_temp_limit_intr_force_RegisterSize 1

/* End of Register Definition for DERATECTL5 */

/* Register DERATECTL6 */
/* Temperature Derate Control Register 6 */
// #define DERATECTL6 (REGB_DDRC_CH0_BaseAddress + 0x118)
#define DERATECTL6_RegisterSize 32
#define DERATECTL6_RegisterResetValue 0x0
#define DERATECTL6_RegisterResetMask 0xffffffff

/* Register Field information for DERATECTL6 */

/* Register DERATECTL6 field derate_mr4_tuf_dis */
/* Disable use of MR4 TUF flag (MR4[7]) bit.
 - 0 - Use MR4 TUF flag (MR4[7])
 - 1 - Do not use MR4 TUF Flag (MR4[7])
It is recommended to set this register to 1.
This affects both the periodic derate logic (DERATECTL0.derate_enable) and the derate_temp_limit_intr.

 */
#define DERATECTL6_derate_mr4_tuf_dis_BitAddressOffset 0
#define DERATECTL6_derate_mr4_tuf_dis_RegisterSize 1

/* End of Register Definition for DERATECTL6 */

/* Register DERATESTAT0 */
/* Temperature Derate Status Register 0 */
// #define DERATESTAT0 (REGB_DDRC_CH0_BaseAddress + 0x11c)
#define DERATESTAT0_RegisterSize 32
#define DERATESTAT0_RegisterResetValue 0x0
#define DERATESTAT0_RegisterResetMask 0xffffffff

/* Register Field information for DERATESTAT0 */

/* Register DERATESTAT0 field derate_temp_limit_intr */
/* Derate temperature interrupt indicating SDRAM temperature operating limit is exceeded.

  In LPDDR4, this register field is set to 1 when the value read from MR4[2:0] is 3'b000 or 3'b111.

  In LPDDR5, this register field is set to 1 when the value read from MR4[4:0] is 5'b00000 or 5'b11111 or invalid value.

  In DDR5, this register field is set to 1 when the value read from MR4[2:0] is the thresholds programmed by DERATECTL2.derate_low_temp_limit and DERATECTL2.derate_high_temp_limit.

  Cleared by register DERATECTL1.derate_temp_limit_intr_clr. */
#define DERATESTAT0_derate_temp_limit_intr_BitAddressOffset 0
#define DERATESTAT0_derate_temp_limit_intr_RegisterSize 1

/* End of Register Definition for DERATESTAT0 */

/* Register DERATEDBGCTL */
/* Temperature Derate Debug Contrl Register */
// #define DERATEDBGCTL (REGB_DDRC_CH0_BaseAddress + 0x124)
#define DERATEDBGCTL_RegisterSize 32
#define DERATEDBGCTL_RegisterResetValue 0x0
#define DERATEDBGCTL_RegisterResetMask 0xffffffff

/* Register Field information for DERATEDBGCTL */

/* Register DERATEDBGCTL field dbg_mr4_grp_sel */
/* MR4 data group select based on 4 device MRR read data */
#define DERATEDBGCTL_dbg_mr4_grp_sel_BitAddressOffset 0
#define DERATEDBGCTL_dbg_mr4_grp_sel_RegisterSize 3

/* Register DERATEDBGCTL field dbg_mr4_rank_sel */
/* MR4 rank select in case of multi ranks */
#define DERATEDBGCTL_dbg_mr4_rank_sel_BitAddressOffset 4
#define DERATEDBGCTL_dbg_mr4_rank_sel_RegisterSize 2

/* End of Register Definition for DERATEDBGCTL */

/* Register DERATEDBGSTAT */
/* Temperature Derate Debug Status Register */
// #define DERATEDBGSTAT (REGB_DDRC_CH0_BaseAddress + 0x128)
#define DERATEDBGSTAT_RegisterSize 32
#define DERATEDBGSTAT_RegisterResetValue 0x0
#define DERATEDBGSTAT_RegisterResetMask 0xffffffff

/* Register Field information for DERATEDBGSTAT */

/* Register DERATEDBGSTAT field dbg_mr4_byte0 */
/* Byte 0 of selected 32 bits MR4 data. LPDDR4/LPDDR5 use 5 bits and DDR5 uses 8 bits.
  This register is updated when the controller issues MRR for MR4 automatically. It is occurred only if derating is enabled. (DERATECTL0.derate_enable=1) */
#define DERATEDBGSTAT_dbg_mr4_byte0_BitAddressOffset 0
#define DERATEDBGSTAT_dbg_mr4_byte0_RegisterSize 8

/* Register DERATEDBGSTAT field dbg_mr4_byte1 */
/* Byte 1 of selected 32 bits MR4 data. LPDDR4/LPDDR5 use 5 bits and DDR5 uses 8 bits.
  This register is updated when the controller issues MRR for MR4 automatically. It is occurred only if derating is enabled. (DERATECTL0.derate_enable=1) */
#define DERATEDBGSTAT_dbg_mr4_byte1_BitAddressOffset 8
#define DERATEDBGSTAT_dbg_mr4_byte1_RegisterSize 8

/* Register DERATEDBGSTAT field dbg_mr4_byte2 */
/* Byte 2 of selected 32 bits MR4 data. LPDDR4/LPDDR5 use 5 bits and DDR5 uses 8 bits.
  This register is updated when the controller issues MRR for MR4 automatically. It is occurred only if derating is enabled. (DERATECTL0.derate_enable=1) */
#define DERATEDBGSTAT_dbg_mr4_byte2_BitAddressOffset 16
#define DERATEDBGSTAT_dbg_mr4_byte2_RegisterSize 8

/* Register DERATEDBGSTAT field dbg_mr4_byte3 */
/* Byte 3 of selected 32 bits MR4 data. LPDDR4/LPDDR5 use 5 bits and DDR5 uses 8 bits.
  This register is updated when the controller issues MRR for MR4 automatically. It is occurred only if derating is enabled. (DERATECTL0.derate_enable=1) */
#define DERATEDBGSTAT_dbg_mr4_byte3_BitAddressOffset 24
#define DERATEDBGSTAT_dbg_mr4_byte3_RegisterSize 8

/* End of Register Definition for DERATEDBGSTAT */

/* Register PWRCTL */
/* Low Power Control Register */
// #define PWRCTL (REGB_DDRC_CH0_BaseAddress + 0x180)
#define PWRCTL_RegisterSize 32
#define PWRCTL_RegisterResetValue 0x0
#define PWRCTL_RegisterResetMask 0xffffffff

/* Register Field information for PWRCTL */

/* Register PWRCTL field selfref_en */
/* If true then the DDRCTL puts the SDRAM per rank into Self Refresh after a programmable number of cycles "maximum idle clocks before Self Refresh (PWRTMG.selfref_to_x32)". This register bit may be re-programmed during the course of normal operation.

For LPDDR4/5 and DDR4, only bit[0] is used.

For DDR5, self-refresh per rank enable is provided. Current self-refresh need to be enabled for all ranks.

For DDR5 RDIMM, self-refresh need to be enabled for all ranks of both channels.
  - bit[0] - rank 0 selfref_en
  - bit[1] - rank 1 selfref_en
  - bit[2] - rank 2 selfref_en
  - bit[3] - rank 3 selfref_en
 */
#define PWRCTL_selfref_en_BitAddressOffset 0
#define PWRCTL_selfref_en_RegisterSize 1

/* Register PWRCTL field powerdown_en */
/* If true then the DDRCTL goes into power-down after a programmable number of cycles "maximum idle clocks before power down" (PWRTMG.powerdown_to_x32).

This register bit may be re-programmed during the course of normal operation.

For LPDDR4/5 and DDR4, only bit[4] is used.

For DDR5, powerdown per rank enable is supported.
  - bit[4] - rank 0 powerdown_en
  - bit[5] - rank 1 powerdown_en
  - bit[6] - rank 2 powerdown_en
  - bit[7] - rank 3 powerdown_en
 */
#define PWRCTL_powerdown_en_BitAddressOffset 4
#define PWRCTL_powerdown_en_RegisterSize 1

/* Register PWRCTL field en_dfi_dram_clk_disable */
/* Enable the assertion of dfi_dram_clk_disable whenever a clock is not required by the SDRAM.

If set to 0, dfi_dram_clk_disable is never asserted.

Assertion of dfi_dram_clk_disable is as follows:

In DDR4, can be asserted in following:
  - in Self Refresh
  - in Maximum Power Saving Mode
In LPDDR4, can be asserted in following:
  - in Self Refresh Power Down
  - in Power Down
  - during Normal operation (Clock Stop)
In DDR5, can be asserted in following:
  - in Self Refresh
In DDR5 RDIMM, the value of this field need to be same as DIMMCTL.dimm_selfref_clock_stop_mode.

 */
#define PWRCTL_en_dfi_dram_clk_disable_BitAddressOffset 9
#define PWRCTL_en_dfi_dram_clk_disable_RegisterSize 1

/* Register PWRCTL field selfref_sw */
/* A value of 1 to this register causes system to move to Self Refresh state immediately, as long as it is not in INIT or DPD/MPSM operating mode. This is referred to as Software Entry/Exit to Self Refresh.
  - 1 - Software Entry to Self Refresh
  - 0 - Software Exit from Self Refresh
 */
#define PWRCTL_selfref_sw_BitAddressOffset 11
#define PWRCTL_selfref_sw_RegisterSize 1

/* Register PWRCTL field stay_in_selfref */
/* Self refresh state is an intermediate state to enter to Self refresh power down state or exit Self refresh power down state for LPDDR4/5.

This register controls transition from the Self refresh state.
  - 1 - Prohibit transition from Self refresh state
  - 0 - Allow transition from Self refresh state
 */
#define PWRCTL_stay_in_selfref_BitAddressOffset 15
#define PWRCTL_stay_in_selfref_RegisterSize 1

/* Register PWRCTL field dis_cam_drain_selfref */
/* Indicates whether skipping CAM draining is allowed when entering Self-Refresh.

This register field cannot be modified while PWRCTL.selfref_sw==1.
  - 0 - CAMs must be empty before entering SR
  - 1 - CAMs are not emptied before entering SR (unsupported)
  Note, PWRCTL.dis_cam_drain_selfref=1 is unsupported in this release. PWRCTL.dis_cam_drain_selfref=0 is required.
 */
#define PWRCTL_dis_cam_drain_selfref_BitAddressOffset 16
#define PWRCTL_dis_cam_drain_selfref_RegisterSize 1

/* Register PWRCTL field lpddr4_sr_allowed */
/* Indicates whether transition from SR-PD to SR and back to SR-PD is allowed. 

This register field cannot be modified while PWRCTL.selfref_sw==1.
  - 0 - SR-PD -> SR -> SR-PD not allowed
  - 1 - SR-PD -> SR -> SR-PD allowed
 */
#define PWRCTL_lpddr4_sr_allowed_BitAddressOffset 17
#define PWRCTL_lpddr4_sr_allowed_RegisterSize 1

/* Register PWRCTL field dsm_en */
/* A value of 1 to this register causes system to move to Deep Sleep Mode state immediately.
  - 1 - Entry to Deep Sleep Mode
  - 0 - Exit from Deep Sleep Mode
 */
#define PWRCTL_dsm_en_BitAddressOffset 18
#define PWRCTL_dsm_en_RegisterSize 1

/* Register PWRCTL field srpd_en */
/* When this is 1, the DDRCTL puts the SDRAM into SR-Powerdown mode. */
#define PWRCTL_srpd_en_BitAddressOffset 19
#define PWRCTL_srpd_en_RegisterSize 1

/* End of Register Definition for PWRCTL */

/* Register HWLPCTL */
/* Hardware Low Power Control Register */
// #define HWLPCTL (REGB_DDRC_CH0_BaseAddress + 0x184)
#define HWLPCTL_RegisterSize 32
#define HWLPCTL_RegisterResetValue 0x3
#define HWLPCTL_RegisterResetMask 0xffffffff

/* Register Field information for HWLPCTL */

/* Register HWLPCTL field hw_lp_en */
/* Enable for Hardware Low Power Interface.
 */
#define HWLPCTL_hw_lp_en_BitAddressOffset 0
#define HWLPCTL_hw_lp_en_RegisterSize 1

/* Register HWLPCTL field hw_lp_exit_idle_en */
/* When this bit is programmed to 1 the cactive_in_ddrc pin of the DDRC can be used to exit from the automatic clock stop, automatic power down or automatic self-refresh modes. Note, it will not cause exit of Self-Refresh that was caused by Hardware Low Power Interface and/or Software (PWRCTL.selfref_sw). */
#define HWLPCTL_hw_lp_exit_idle_en_BitAddressOffset 1
#define HWLPCTL_hw_lp_exit_idle_en_RegisterSize 1

/* End of Register Definition for HWLPCTL */

/* Register RFSHMOD0 */
/* Refresh Mode Register 0 */
// #define RFSHMOD0 (REGB_DDRC_CH0_BaseAddress + 0x200)
#define RFSHMOD0_RegisterSize 32
#define RFSHMOD0_RegisterResetValue 0x0
#define RFSHMOD0_RegisterResetMask 0xffffffff

/* Register Field information for RFSHMOD0 */

/* Register RFSHMOD0 field refresh_burst */
/* The programmed value + 1 is the number of refresh timeouts that is allowed to accumulate before traffic is blocked and the refreshes are forced to execute. Closing pages to perform a refresh is a one-time penalty that must be paid for each group of refreshes. Therefore, performing refreshes in a burst reduces the per-refresh penalty of these page closings. Higher numbers for RFSHCTL.refresh_burst slightly increases utilization; lower numbers decreases the worst-case latency associated with refreshes.
 - 0 - single refresh
 - 1 - burst-of-2 refresh
 - 7 - burst-of-8 refresh
In DDR4 mode, according to Fine Granularity feature, 8 refreshes can be postponed in 1X mode, 16 refreshes in 2X mode and 32 refreshes in 4X mode.

In DDR5 mode, according to Fine Granularity feature, 4 refreshes can be postponed in 1X mode and 8 refreshes can be postponed in 2X mode.

In per-bank refresh mode of LPDDR4/5 (RFSHMOD0.per_bank_refresh = 1), 64 refreshes can be postponed.

If using PHY-initiated updates, care must be taken in the setting of RFSHMOD0.refresh_burst, to ensure that tRFCmax is not violated due to a PHY-initiated update occurring shortly before a refresh burst was due. In this situation, the refresh burst will be delayed until the PHY-initiated update is complete.

 */
#define RFSHMOD0_refresh_burst_BitAddressOffset 0
#define RFSHMOD0_refresh_burst_RegisterSize 6

/* Register RFSHMOD0 field per_bank_refresh */
/* 
 - 1 - Per bank refresh
 - 0 - All bank refresh
Per bank refresh allows traffic to flow to other banks. */
#define RFSHMOD0_per_bank_refresh_BitAddressOffset 8
#define RFSHMOD0_per_bank_refresh_RegisterSize 1

/* End of Register Definition for RFSHMOD0 */

/* Register RFSHCTL0 */
/* Refresh Control Register 0 */
// #define RFSHCTL0 (REGB_DDRC_CH0_BaseAddress + 0x208)
#define RFSHCTL0_RegisterSize 32
#define RFSHCTL0_RegisterResetValue 0x0
#define RFSHCTL0_RegisterResetMask 0xffffffff

/* Register Field information for RFSHCTL0 */

/* Register RFSHCTL0 field dis_auto_refresh */
/* When '1', disable auto-refresh generated by the DDRCTL. When auto-refresh is disabled, the SoC core must generate refreshes using the registers OPCTRLCMD.rankn_refresh.

When dis_auto_refresh transitions from 0 to 1, any pending refreshes are immediately scheduled by the DDRCTL.

If DDR4 CRC/parity retry is enabled (CRCPARCTL1.crc_parity_retry_enable = 1), disable auto-refresh is not supported, and this bit must be set to '0'.

If FGR mode is enabled (RFSHMOD1.fgr_mode > 0), disable auto-refresh is not supported, and this bit must be set to '0'.

This register field is changeable on the fly in non-DDR5 mode, and changeable during INIT/DBG/BIST state or self-refresh mode and MPSM during OPS state in DDR5 mode. */
#define RFSHCTL0_dis_auto_refresh_BitAddressOffset 0
#define RFSHCTL0_dis_auto_refresh_RegisterSize 1

/* Register RFSHCTL0 field refresh_update_level */
/* Toggle this signal (either from 0 to 1 or from 1 to 0) to indicate that the refresh register(s) have been updated.

refresh_update_level must not be toggled when the DDRC is in reset (core_ddrc_rstn = 0).

In DDR5 mode, this can be toggled during self-refresh mode and MPSM in OPS state.

The refresh register(s) are automatically updated when exiting reset. */
#define RFSHCTL0_refresh_update_level_BitAddressOffset 4
#define RFSHCTL0_refresh_update_level_RegisterSize 1

/* End of Register Definition for RFSHCTL0 */

/* Register ZQCTL0 */
/* ZQ Control Register 0 */
// #define ZQCTL0 (REGB_DDRC_CH0_BaseAddress + 0x280)
#define ZQCTL0_RegisterSize 32
#define ZQCTL0_RegisterResetValue 0x0
#define ZQCTL0_RegisterResetMask 0xffffffff

/* Register Field information for ZQCTL0 */

/* Register ZQCTL0 field zq_resistor_shared */
/* 
 - 1 - Denotes that ZQ resistor is shared between ranks. Means ZQinit/ZQCL/ZQCS/MPC(ZQ calibration) commands are sent to one rank at a time with tZQinit/tZQCL/tZQCS/tZQCAL/tZQLAT timing met between commands so that commands to different ranks do not overlap. 
 - 0 - ZQ resistor is not shared.

If LPDDR5 is used, this register needs to be set to "0".
 */
#define ZQCTL0_zq_resistor_shared_BitAddressOffset 29
#define ZQCTL0_zq_resistor_shared_RegisterSize 1

/* Register ZQCTL0 field dis_auto_zq */
/* 
 - 1 - Disable DDRCTL generation of ZQCS/MPC(ZQ calibration) command.  Register OPCTRLCMD.zq_calib_short can be used instead to issue ZQ calibration request from APB module.
 - 0 - Internally generate ZQCS/MPC(ZQ calibration) commands based on ZQSET1TMG1.t_zq_short_interval_x1024.
 This register field only applys to DDR4, LPDDR4, and LPDDR5. For DDR5, see PASCTL7~PASCTL10 registers
 */
#define ZQCTL0_dis_auto_zq_BitAddressOffset 31
#define ZQCTL0_dis_auto_zq_RegisterSize 1

/* End of Register Definition for ZQCTL0 */

/* Register ZQCTL1 */
/* ZQ Control Register 1 */
// #define ZQCTL1 (REGB_DDRC_CH0_BaseAddress + 0x284)
#define ZQCTL1_RegisterSize 32
#define ZQCTL1_RegisterResetValue 0x0
#define ZQCTL1_RegisterResetMask 0xffffffff

/* Register Field information for ZQCTL1 */

/* Register ZQCTL1 field zq_reset */
/* 
Setting this register bit to 1 triggers a ZQ Reset operation. When the ZQ Reset operation is complete, the DDRCTL automatically clears this bit. It is recommended NOT to set this register bit if in Init, in SR-Powerdown or Deep Sleep Modes.

For SR-Powerdown it will be scheduled after SRPD has been exited.

For Deep Sleep Mode, it will be scheduled after DSM and/or SRPD has been exited.

 */
#define ZQCTL1_zq_reset_BitAddressOffset 0
#define ZQCTL1_zq_reset_RegisterSize 1

/* End of Register Definition for ZQCTL1 */

/* Register ZQCTL2 */
/* ZQ Control Register 2 */
// #define ZQCTL2 (REGB_DDRC_CH0_BaseAddress + 0x288)
#define ZQCTL2_RegisterSize 32
#define ZQCTL2_RegisterResetValue 0x0
#define ZQCTL2_RegisterResetMask 0xffffffff

/* Register Field information for ZQCTL2 */

/* Register ZQCTL2 field dis_srx_zqcl */
/* 
 - 1 - Disable issuing of ZQCL/MPC(ZQ calibration) command at Self-Refresh/SR-Powerdown exit.
 - 0 - Enable issuing of ZQCL/MPC(ZQ calibration) command at Self-Refresh/SR-Powerdown exit.
This is only present for designs supporting DDR4 or DDR5 or LPDDR4 or LPDDR5 devices. */
#define ZQCTL2_dis_srx_zqcl_BitAddressOffset 0
#define ZQCTL2_dis_srx_zqcl_RegisterSize 1

/* End of Register Definition for ZQCTL2 */

/* Register ZQSTAT */
/* ZQ Status Register */
// #define ZQSTAT (REGB_DDRC_CH0_BaseAddress + 0x28c)
#define ZQSTAT_RegisterSize 32
#define ZQSTAT_RegisterResetValue 0x0
#define ZQSTAT_RegisterResetMask 0xffffffff

/* Register Field information for ZQSTAT */

/* Register ZQSTAT field zq_reset_busy */
/* SoC core may initiate a ZQ Reset operation only if this signal is low.

This signal goes high in the clock after the DDRCTL accepts the ZQ Reset request.

It goes low when the ZQ Reset command is issued to the SDRAM and the associated NOP period is over.

It is recommended not to perform ZQ Reset commands when this signal is high.
 - 0 - Indicates that the SoC core can initiate a ZQ Reset operation
 - 1 - Indicates that ZQ Reset operation is in progress */
#define ZQSTAT_zq_reset_busy_BitAddressOffset 0
#define ZQSTAT_zq_reset_busy_RegisterSize 1

/* End of Register Definition for ZQSTAT */

/* Register DQSOSCRUNTIME */
/* DQS/WCK Oscillator Runtime Register */
// #define DQSOSCRUNTIME (REGB_DDRC_CH0_BaseAddress + 0x300)
#define DQSOSCRUNTIME_RegisterSize 32
#define DQSOSCRUNTIME_RegisterResetValue 0x400040
#define DQSOSCRUNTIME_RegisterResetMask 0xffffffff

/* Register Field information for DQSOSCRUNTIME */

/* Register DQSOSCRUNTIME field dqsosc_runtime */
/* DQS interval timer run time setting as programmed in MR23 for LPDDR4; WCK2DQI interval timer run time setting as programmed in MR37 for LPDDR5. This field must be non zero.

  - 0x0 - Interval timer stop via MPC command (not supported)
  - 0x1 - Interval timer stops automatically at 16th clocks after timer start
  - 0x2 - Interval timer stops automatically at 32nd clocks after timer start
  - 0x3 - Interval timer stops automatically at 48th clocks after timer start
  - 0x4 - Interval timer stops automatically at 64th clocks after timer start
  - ----- Thru ----------
  - 0x3F - Interval timer stops automatically at (63x16)th clocks after timer start
  - 0x40 to 0x7F - Interval timer stops automatically at 2048th clocks after timer start
  - 0x80 to 0xBF - Interval timer stops automatically at 4096th clocks after timer start 
  - 0xC0 to 0xFF - Interval timer stops automatically at 8192nd clocks after timer start
Unit: DRAM clock cycles. */
#define DQSOSCRUNTIME_dqsosc_runtime_BitAddressOffset 0
#define DQSOSCRUNTIME_dqsosc_runtime_RegisterSize 8

/* Register DQSOSCRUNTIME field wck2dqo_runtime */
/* WCK2DQO interval timer run time setting as programmed in MR40 for LPDDR5.This field must be non zero.

  - 0x0 - Interval timer stop via MPC command (not supported)
  - 0x1 - Interval timer stops automatically at 16th clocks after timer start
  - 0x2 - Interval timer stops automatically at 32nd clocks after timer start
  - 0x3 - Interval timer stops automatically at 48th clocks after timer start
  - 0x4 - Interval timer stops automatically at 64th clocks after timer start
  - ----- Thru ----------
  - 0x3F - Interval timer stops automatically at (63x16)th clocks after timer start
  - 0x40 to 0x7F - Interval timer stops automatically at 2048th clocks after timer start
  - 0x80 to 0xBF - Interval timer stops automatically at 4096th clocks after timer start 
  - 0xC0 to 0xFF - Interval timer stops automatically at 8192nd clocks after timer start
This register field is only applicable for designs supporting LPDDR5 SDRAM memories.

It is don't care for LPDDR4 SDRAM memories. 

Unit: DRAM clock cycles. */
#define DQSOSCRUNTIME_wck2dqo_runtime_BitAddressOffset 16
#define DQSOSCRUNTIME_wck2dqo_runtime_RegisterSize 8

/* End of Register Definition for DQSOSCRUNTIME */

/* Register DQSOSCSTAT0 */
/* DQS/WCK Oscillator Status Register 0 */
// #define DQSOSCSTAT0 (REGB_DDRC_CH0_BaseAddress + 0x304)
#define DQSOSCSTAT0_RegisterSize 32
#define DQSOSCSTAT0_RegisterResetValue 0x0
#define DQSOSCSTAT0_RegisterResetMask 0xffffffff

/* Register Field information for DQSOSCSTAT0 */

/* Register DQSOSCSTAT0 field dqsosc_state */
/* DQS/WCK Oscillator Control State Status.   
  - 000 - DQSOSC_IDLE 
  - 001 - DQSOSC_START: Sending MPC 
  - 010 - DQSOSC_RUNTIME: Waiting for runtime passed 
  - 011 - DQSOSC_GET_RESULT1: Sending first MRR 
  - 100 - DQSOSC_WAIT1: Waiting for tMRR for sending next MRR 
  - 101 - DQSOSC_GET_RESULT2: Sending second MRR 
  - 110 - DQSOSC_WAIT2: Waiting for tMRR or rank gap 
  
The value 0 indicates nothing is being done for DQS Oscillator. Otherwise, DQS Oscillator is running and reflects the current state of DQSOSC. It can be used for debug only to ascertain the current state of DQSOSC controller if it is stuck to one particular state. */
#define DQSOSCSTAT0_dqsosc_state_BitAddressOffset 0
#define DQSOSCSTAT0_dqsosc_state_RegisterSize 3

/* Register DQSOSCSTAT0 field dqsosc_per_rank_stat */
/* DQS/WCK Oscillator per rank status. 

  This bit is set to 0 when DQSOSCCTL0.dqsosc_enable is set to 1, and set to 1 when the DQS Oscillator command sequence is started for the corresponding active rank. */
#define DQSOSCSTAT0_dqsosc_per_rank_stat_BitAddressOffset 4
#define DQSOSCSTAT0_dqsosc_per_rank_stat_RegisterSize 2

/* End of Register Definition for DQSOSCSTAT0 */

/* Register DQSOSCCFG0 */
/* DQSOSC Config Register 0 */
// #define DQSOSCCFG0 (REGB_DDRC_CH0_BaseAddress + 0x308)
#define DQSOSCCFG0_RegisterSize 32
#define DQSOSCCFG0_RegisterResetValue 0x0
#define DQSOSCCFG0_RegisterResetMask 0xffffffff

/* Register Field information for DQSOSCCFG0 */

/* Register DQSOSCCFG0 field dis_dqsosc_srx */
/* 
 - 1 - Disable issuing of DQSOSC command sequences at Self-Refresh/SR-Powerdown exit.
 - 0 - Enable issuing of  DQSOSC command sequences at Self-Refresh/SR-Powerdown exit.
This is only present for designs supporting LPDDR4 or LPDDR5 devices. */
#define DQSOSCCFG0_dis_dqsosc_srx_BitAddressOffset 0
#define DQSOSCCFG0_dis_dqsosc_srx_RegisterSize 1

/* End of Register Definition for DQSOSCCFG0 */

/* Register SCHED0 */
/* Scheduler Control Register 0 */
// #define SCHED0 (REGB_DDRC_CH0_BaseAddress + 0x380)
#define SCHED0_RegisterSize 32
#define SCHED0_RegisterResetValue 0x201d
#define SCHED0_RegisterResetMask 0xffffffff

/* Register Field information for SCHED0 */

/* Register SCHED0 field dis_opt_wrecc_collision_flush */
/* In this release, this register bit is required to set to 1 in software unless otherwise advised by Synopsys. */
#define SCHED0_dis_opt_wrecc_collision_flush_BitAddressOffset 0
#define SCHED0_dis_opt_wrecc_collision_flush_RegisterSize 1

/* Register SCHED0 field prefer_write */
/* If set then the bank selector prefers writes over reads.

FOR DEBUG ONLY. */
#define SCHED0_prefer_write_BitAddressOffset 1
#define SCHED0_prefer_write_RegisterSize 1

/* Register SCHED0 field pageclose */
/* If true, bank is kept open only while there are page hit transactions available in the CAM to that bank. The last read or write command in the CAM with a bank and page hit will be executed with auto-precharge if SCHEDTMG0.pageclose_timer=0. Even if this register set to 1 and SCHEDTMG0.pageclose_timer is set to 0, explicit precharge (and not auto-precharge) may be issued in some cases where there is a mode switch between Write and Read or between LPR and HPR. The Read and Write commands that are executed as part of the ECC scrub requests are also executed without auto-precharge.

If false, the bank remains open until there is a need to close it (to open a different page, or for page timeout or refresh timeout) - also known as open page policy. The open page policy can be overridden by setting the per-command-autopre bit on the HIF interface (hif_cmd_autopre).

The pageclose feature provids a midway between Open and Close page policies.

FOR PERFORMANCE ONLY. */
#define SCHED0_pageclose_BitAddressOffset 2
#define SCHED0_pageclose_RegisterSize 1

/* Register SCHED0 field rdwr_switch_policy_sel */
/* Select read write switching policy.
   - 1: select "enhanced" read write switching policy
   - 0: select "original" read write switching policy
 */
#define SCHED0_rdwr_switch_policy_sel_BitAddressOffset 3
#define SCHED0_rdwr_switch_policy_sel_RegisterSize 1

/* Register SCHED0 field opt_wrcam_fill_level */
/* Enable the feature of optimized write CAM fill level by switching to write when write CAM reaches certain fill level set in SCHED3.wrcam_highthresh.
 - 1: enabled
 - 0: disabled
   When it is enabled, write starvation timer (register) and write transaction counter automatically are not used. They will be only active when the feature is disabled.

   If MEMC_RDWR_SWITCH_POL_SEL==1 && rdwr_switch_policy_sel==0, this register will be ignored.
 */
#define SCHED0_opt_wrcam_fill_level_BitAddressOffset 4
#define SCHED0_opt_wrcam_fill_level_RegisterSize 1

/* Register SCHED0 field dis_opt_ntt_by_act */
/* Disable optimized NTT update by Activate command. This register is debug purpose only. For normal operation, This register must be set to 0.
 - 1: disabled
 - 0: enabled
 */
#define SCHED0_dis_opt_ntt_by_act_BitAddressOffset 5
#define SCHED0_dis_opt_ntt_by_act_RegisterSize 1

/* Register SCHED0 field dis_opt_ntt_by_pre */
/* Disable optimized NTT update by Precharge command. This register is debug purpose only. For normal operation, This register must be set to 0.
 - 1: disabled
 - 0: enabled
 */
#define SCHED0_dis_opt_ntt_by_pre_BitAddressOffset 6
#define SCHED0_dis_opt_ntt_by_pre_RegisterSize 1

/* Register SCHED0 field autopre_rmw */
/* Select behavior of hif_cmd_autopre if a RMW is received on HIF with hif_cmd_autopre=1
 - 1: Apply Autopre only for write part of RMW
 - 0: Apply Autopre for both read and write parts of RMW
 */
#define SCHED0_autopre_rmw_BitAddressOffset 7
#define SCHED0_autopre_rmw_RegisterSize 1

/* Register SCHED0 field lpr_num_entries */
/* Number of entries in the low priority transaction store is this value + 1.
(MEMC_NO_OF_ENTRY - (SCHED.lpr_num_entries + 1)) is the number of entries available for the high priority transaction store.

Setting this to maximum value allocates all entries to low priority transaction store.

Setting this to 0 allocates 1 entry to low priority transaction store and the rest to high priority transaction store.
Note: In ECC configurations, the numbers of write and low priority read credits issued is one less than in the non-ECC case.  One entry each is reserved in the write and low-priority read CAMs for storing the RMW requests arising out of single bit error correction RMW operation. */
#define SCHED0_lpr_num_entries_BitAddressOffset 8
#define SCHED0_lpr_num_entries_RegisterSize 6

/* Register SCHED0 field lpddr4_opt_act_timing */
/* Optimized ACT timing control for LPDDR4.
In LPDDR4, RD/WR/ACT takes 4 cycle. To stream Read/Write, there are only 4 cycle space between Reads/Writes.
If ACT is scheduled-out after RD/WR with 1, 2 or 3 cycle gap, next RD/WR may be pushed by 1, 2 or 3 cycle and create a gap on DQ. 
When this register is set, ACT is not scheduled-out with the gap = 1, 2 and 3 cycle. 
If enabled, there could be performance impact especially for random traffic. (Latency/Utilization)
 - 1 - Enable this feature
 - 0 - Disable this feature
This register is ignored when MSTR0.lpddr4==0.
This register field is only applicable for LPDDR4 mode.
 */
#define SCHED0_lpddr4_opt_act_timing_BitAddressOffset 15
#define SCHED0_lpddr4_opt_act_timing_RegisterSize 1

/* Register SCHED0 field opt_vprw_sch */
/* Optimize exVPR/exVPW scheduling.

 - 0 - When any exVPR/exVPW are pending on CAM, read/write command of all other traffic class are masked to be scheduled
 - 1 - When any exVPR/exVPW are pending as page-hit, read/write command of  all other traffic class are masked to be scheduled

 Program to 1 can improve utilization as other traffic class can utilize bandwidth while pages for exVPR/exVPW are being prepared or ranks/banks for exVPR/exVPW are being refreshed, but it can delay execution of exVPR/exVPW due to delay of Activate by read/write command of other traffic class.
 */
#define SCHED0_opt_vprw_sch_BitAddressOffset 31
#define SCHED0_opt_vprw_sch_RegisterSize 1

/* End of Register Definition for SCHED0 */

/* Register SCHED1 */
/* Scheduler Control Register 1 */
// #define SCHED1 (REGB_DDRC_CH0_BaseAddress + 0x384)
#define SCHED1_RegisterSize 32
#define SCHED1_RegisterResetValue 0x2000
#define SCHED1_RegisterResetMask 0xffffffff

/* Register Field information for SCHED1 */

/* Register SCHED1 field delay_switch_write */
/* delay_switch_write indicates number of cycles to delay switching read to write mode when write page-hit request is there and no read page-hit request is there.
   Setting higher value may reduce number of read to write switching but increase read to write turn-around time.

   The register indicates the number of cycles:
   - 0: no delay
   - 1: 2 cycles delay
   - 2: 4 cycles delay
   - 3: 6 cycles delay
   - 4: 8 cycles delay
   - ... 
   - 15:30 cycles delay
   If MEMC_RDWR_SWITCH_POL_SEL==1 && rdwr_switch_policy_sel==0, this register will be ignored.

   Unit: DFI clock
 */
#define SCHED1_delay_switch_write_BitAddressOffset 12
#define SCHED1_delay_switch_write_RegisterSize 4

/* Register SCHED1 field visible_window_limit_wr */
/* Visible window limiter for write.

This is to prevent extreme starvation against other entries within a CAM.
Each write CAM entry has a counter, it is counted-up when newer write CAM entry is scheduled-out.
The counter represent starvation within WR CAM in terms of number of commands to be over taken. 
When the counter reaches to certain number, the entry becomes expired-VPW to eliminate more starvation.


  - 0 - Disable this feature
  - 1 - 31 commands
  - 2 - 63 commands
  - 3 - 127 commands
  - 4 - 255 commands
  - else reserved
 */
#define SCHED1_visible_window_limit_wr_BitAddressOffset 16
#define SCHED1_visible_window_limit_wr_RegisterSize 3

/* Register SCHED1 field visible_window_limit_rd */
/* Visible window limiter for read.

This is to prevent extreme starvation against other entries within a CAM.
Each read CAM entry has a counter, it is counted-up when newer read CAM entry is scheduled-out.
The counter represent starvation within RD CAM in terms of number of commands to be over taken. 
When the counter reaches to certain number, the entry becomes expired-VPR to eliminate more starvation.

  - 0 - Disable this feature
  - 1 - 31 commands
  - 2 - 63 commands
  - 3 - 127 commands
  - 4 - 255 commands
  - else reserved
 */
#define SCHED1_visible_window_limit_rd_BitAddressOffset 20
#define SCHED1_visible_window_limit_rd_RegisterSize 3

/* Register SCHED1 field page_hit_limit_wr */
/* Page-Hit limiter for write.

  When certain number of write commands are scheduled out without ACT for a bank (schedule page-hit commands), all entries belonging to the bank priority are increased equal to page-hit entry even if these are page-miss so that oldest entry belonging to the bank can be served regardless of page-hit/page-miss.

The priority is reset once any ACT/PRE/AP is served to the bank.


  - 0 - Disable this feature
  - 1 - 4 commands
  - 2 - 8 commands
  - 3 - 16 commands
  - 4 - 32 commands
  - else reserved
 */
#define SCHED1_page_hit_limit_wr_BitAddressOffset 24
#define SCHED1_page_hit_limit_wr_RegisterSize 3

/* Register SCHED1 field page_hit_limit_rd */
/* Page-Hit limiter for read.

  When certain number of read commands are scheduled out without ACT for a bank (schedule page-hit commands), all entries belonging to the bank priority are increased equal to page-hit entry even if these are page-miss so that oldest entry belonging to the bank can be served regardless of page-hit/page-miss.

The priority is reset once any ACT/PRE/AP is served to the bank.


  - 0 - Disable this feature
  - 1 - 4 commands
  - 2 - 8 commands
  - 3 - 16 commands
  - 4 - 32 commands
  - else reserved
 */
#define SCHED1_page_hit_limit_rd_BitAddressOffset 28
#define SCHED1_page_hit_limit_rd_RegisterSize 3

/* End of Register Definition for SCHED1 */

/* Register SCHED3 */
/* Scheduler Control Register 3 */
// #define SCHED3 (REGB_DDRC_CH0_BaseAddress + 0x38c)
#define SCHED3_RegisterSize 32
#define SCHED3_RegisterResetValue 0x4040208
#define SCHED3_RegisterResetMask 0xffffffff

/* Register Field information for SCHED3 */

/* Register SCHED3 field wrcam_lowthresh */
/* 
   The low threshold used in optimized write CAM fill level.

   When (MEMC_NO_OF_ENTRY - (number of loaded entries) < wrcam_lowthresh), keep to write mode and stop to prepare banks for read direction if no Exp-VPR or read collision is there.

   Note: In sideband ECC configuration, the number of write entries is (MEMC_NO_OF_ENRY-1).

   This feature is enabled when opt_wrcam_fill_level is 1.

 */
#define SCHED3_wrcam_lowthresh_BitAddressOffset 0
#define SCHED3_wrcam_lowthresh_RegisterSize 6

/* Register SCHED3 field wrcam_highthresh */
/* 
   The high threshold used in optimized write CAM fill level.

   When (MEMC_NO_OF_ENTRY - (number of loaded entries) < wrcam_highthresh), switch to write mode and prepare banks for write direction if no Exp-VPR or read collision is there.

   wrcam_highthresh must be set to a smaller value than wrcam_lowthresh.

   Note: In sideband ECC configuration, the number of write entries is (MEMC_NO_OF_ENRY-1).

   This feature is enabled when opt_wrcam_fill_level is 1.

 */
#define SCHED3_wrcam_highthresh_BitAddressOffset 8
#define SCHED3_wrcam_highthresh_RegisterSize 6

/* Register SCHED3 field wr_pghit_num_thresh */
/* 
   Switch to write mode once number of write page-hit request exceeds threshold set in this register during waiting delay_switch_write timeout.
   Set to 0 will disable the feature.

   If MEMC_RDWR_SWITCH_POL_SEL==1 && rdwr_switch_policy_sel==0, this register will be ignored.
 */
#define SCHED3_wr_pghit_num_thresh_BitAddressOffset 16
#define SCHED3_wr_pghit_num_thresh_RegisterSize 6

/* Register SCHED3 field rd_pghit_num_thresh */
/* 
   Switch to read mode once number of read page-hit request exceeds the threshold set in the register during waiting tW2R.
   Set to 0 will disable the feature.

   If MEMC_RDWR_SWITCH_POL_SEL==1 && rdwr_switch_policy_sel==0, this register will be ignored.
 */
#define SCHED3_rd_pghit_num_thresh_BitAddressOffset 24
#define SCHED3_rd_pghit_num_thresh_RegisterSize 6

/* End of Register Definition for SCHED3 */

/* Register SCHED4 */
/* Scheduler Control Register 4 */
// #define SCHED4 (REGB_DDRC_CH0_BaseAddress + 0x390)
#define SCHED4_RegisterSize 32
#define SCHED4_RegisterResetValue 0x8400810
#define SCHED4_RegisterResetMask 0xffffffff

/* Register Field information for SCHED4 */

/* Register SCHED4 field rd_act_idle_gap */
/* 
   rd_act_idle_gap indicates number of cycles when read direction has no request to start preparing bank for write direction.

   The register indicates the number of cycle.

   If MEMC_RDWR_SWITCH_POL_SEL==1 && rdwr_switch_policy_sel==0, this register will be ignored.
 */
#define SCHED4_rd_act_idle_gap_BitAddressOffset 0
#define SCHED4_rd_act_idle_gap_RegisterSize 8

/* Register SCHED4 field wr_act_idle_gap */
/* 
   wr_act_idle_gap indicates number of cycles when write direction has no request to start preparing bank for read direction.

   The register indicates the number of cycle.

   If MEMC_RDWR_SWITCH_POL_SEL==1 && rdwr_switch_policy_sel==0, this register will be ignored.
 */
#define SCHED4_wr_act_idle_gap_BitAddressOffset 8
#define SCHED4_wr_act_idle_gap_RegisterSize 8

/* Register SCHED4 field rd_page_exp_cycles */
/* 
   rd_page_exp_cycles indicates number of cycles to keep the bank opened for read direction in write mode when both directions has request to the bank.

   The register indicates the number of cycle.

   If MEMC_RDWR_SWITCH_POL_SEL==1 && rdwr_switch_policy_sel==0, this register will be ignored.
 */
#define SCHED4_rd_page_exp_cycles_BitAddressOffset 16
#define SCHED4_rd_page_exp_cycles_RegisterSize 8

/* Register SCHED4 field wr_page_exp_cycles */
/* 
   wr_page_exp_cycles indicates number of cycles to keep the bank opened for write direction in read mode when both directions has request to the bank.

   The register indicates the number of cycle.

   If MEMC_RDWR_SWITCH_POL_SEL==1 && rdwr_switch_policy_sel==0, this register will be ignored.
 */
#define SCHED4_wr_page_exp_cycles_BitAddressOffset 24
#define SCHED4_wr_page_exp_cycles_RegisterSize 8

/* End of Register Definition for SCHED4 */

/* Register SCHED5 */
/* Scheduler Control Register 5. */
// #define SCHED5 (REGB_DDRC_CH0_BaseAddress + 0x394)
#define SCHED5_RegisterSize 32
#define SCHED5_RegisterResetValue 0x10000204
#define SCHED5_RegisterResetMask 0xffffffff

/* Register Field information for SCHED5 */

/* Register SCHED5 field wrecc_cam_lowthresh */
/* The low threshold used in optimize write ECC CAM fill level.
When (MEMC_NO_OF_ENTRY/2 - (number of loaded entries) < wrecc_cam_lowthresh), keep to write mode and stop to prepare banks for read direction if no Exp-VPR or read collision is there.
This feature is enabled when opt_wrcam_fill_level is 1. */
#define SCHED5_wrecc_cam_lowthresh_BitAddressOffset 0
#define SCHED5_wrecc_cam_lowthresh_RegisterSize 5

/* Register SCHED5 field wrecc_cam_highthresh */
/* The high threshold used in optimized write ECC CAM fill level.
When (MEMC_NO_OF_ENTRY/2 - (number of loaded entries) < wrecc_cam_highthresh), switch to write mode and prepare banks for write direction if no Exp-VPR or read collision is there.
This feature is enabled when opt_wrcam_fill_level is 1. */
#define SCHED5_wrecc_cam_highthresh_BitAddressOffset 8
#define SCHED5_wrecc_cam_highthresh_RegisterSize 5

/* Register SCHED5 field dis_opt_loaded_wrecc_cam_fill_level */
/* In this release, this register bit, dis_opt_loaded_wrecc_cam_fill_level, is required to set to 0 in software unless otherwise advised by Synopsys. */
#define SCHED5_dis_opt_loaded_wrecc_cam_fill_level_BitAddressOffset 28
#define SCHED5_dis_opt_loaded_wrecc_cam_fill_level_RegisterSize 1

/* Register SCHED5 field dis_opt_valid_wrecc_cam_fill_level */
/* In this release, this register bit, dis_opt_valid_wrecc_cam_fill_level, is required to set to 0 in software unless otherwise advised by Synopsys. */
#define SCHED5_dis_opt_valid_wrecc_cam_fill_level_BitAddressOffset 29
#define SCHED5_dis_opt_valid_wrecc_cam_fill_level_RegisterSize 1

/* End of Register Definition for SCHED5 */

/* Register DFILPCFG0 */
/* DFI Low Power Configuration Register 0 */
// #define DFILPCFG0 (REGB_DDRC_CH0_BaseAddress + 0x500)
#define DFILPCFG0_RegisterSize 32
#define DFILPCFG0_RegisterResetValue 0x100000
#define DFILPCFG0_RegisterResetMask 0xffffffff

/* Register Field information for DFILPCFG0 */

/* Register DFILPCFG0 field dfi_lp_en_pd */
/* Enables DFI Low Power interface handshaking during Power Down Entry/Exit.
  - 0 - Disabled 
  - 1 - Enabled */
#define DFILPCFG0_dfi_lp_en_pd_BitAddressOffset 0
#define DFILPCFG0_dfi_lp_en_pd_RegisterSize 1

/* Register DFILPCFG0 field dfi_lp_en_sr */
/* Enables DFI Low Power interface handshaking during Self Refresh Entry/Exit.
  - 0 - Disabled 
  - 1 - Enabled */
#define DFILPCFG0_dfi_lp_en_sr_BitAddressOffset 4
#define DFILPCFG0_dfi_lp_en_sr_RegisterSize 1

/* Register DFILPCFG0 field dfi_lp_en_dsm */
/* Enables DFI Low Power interface handshaking during Deep Sleep Mode Entry/Exit.
  - 0 - Disabled 
  - 1 - Enabled
This is only present for designs supporting LPDDR5 devices. */
#define DFILPCFG0_dfi_lp_en_dsm_BitAddressOffset 8
#define DFILPCFG0_dfi_lp_en_dsm_RegisterSize 1

/* Register DFILPCFG0 field dfi_lp_en_data */
/* Enables DFI Data Low Power interface handshaking during data bus idle.
  - 0 - Disabled 
  - 1 - Enabled */
#define DFILPCFG0_dfi_lp_en_data_BitAddressOffset 16
#define DFILPCFG0_dfi_lp_en_data_RegisterSize 1

/* Register DFILPCFG0 field dfi_lp_data_req_en */
/* Enables DFI Data Low Power interface.
  - 0 - Disabled. dfi_lp_data_req is not asserted.
  - 1 - Enabled */
#define DFILPCFG0_dfi_lp_data_req_en_BitAddressOffset 20
#define DFILPCFG0_dfi_lp_data_req_en_RegisterSize 1

/* End of Register Definition for DFILPCFG0 */

/* Register DFIUPD0 */
/* DFI Update Register 0 */
// #define DFIUPD0 (REGB_DDRC_CH0_BaseAddress + 0x508)
#define DFIUPD0_RegisterSize 32
#define DFIUPD0_RegisterResetValue 0x8000
#define DFIUPD0_RegisterResetMask 0xffffffff

/* Register Field information for DFIUPD0 */

/* Register DFIUPD0 field dfi_phyupd_en */
/* Enables the support for acknowledging PHY-initiated updates:
    - 0 - Disabled
    - 1 - Enabled */
#define DFIUPD0_dfi_phyupd_en_BitAddressOffset 15
#define DFIUPD0_dfi_phyupd_en_RegisterSize 1

/* Register DFIUPD0 field ctrlupd_pre_srx */
/* Selects dfi_ctrlupd_req requirements at SRX:
  - 0 : send ctrlupd after SRX
  - 1 : send ctrlupd before SRX
  If DFIUPD0.dis_auto_ctrlupd_srx=1, this register has no impact, because no dfi_ctrlupd_req will be issued when SRX.
 */
#define DFIUPD0_ctrlupd_pre_srx_BitAddressOffset 29
#define DFIUPD0_ctrlupd_pre_srx_RegisterSize 1

/* Register DFIUPD0 field dis_auto_ctrlupd_srx */
/* 
 - 0 - DDRCTL issues a dfi_ctrlupd_req before or after exiting self-refresh,  depending on DFIUPD0.ctrlupd_pre_srx.
 - 1 - Disable the automatic dfi_ctrlupd_req generation by the DDRCTL at self-refresh exit. */
#define DFIUPD0_dis_auto_ctrlupd_srx_BitAddressOffset 30
#define DFIUPD0_dis_auto_ctrlupd_srx_RegisterSize 1

/* Register DFIUPD0 field dis_auto_ctrlupd */
/* 
  - 0 - DDRCTL issues dfi_ctrlupd_req periodically.
  - 1 - Disable the automatic dfi_ctrlupd_req generation by the DDRCTL. The core must issue the dfi_ctrlupd_req signal using register OPCTRLCMD.ctrlupd. */
#define DFIUPD0_dis_auto_ctrlupd_BitAddressOffset 31
#define DFIUPD0_dis_auto_ctrlupd_RegisterSize 1

/* End of Register Definition for DFIUPD0 */

/* Register DFIMISC */
/* DFI Miscellaneous Control Register */
// #define DFIMISC (REGB_DDRC_CH0_BaseAddress + 0x510)
#define DFIMISC_RegisterSize 32
#define DFIMISC_RegisterResetValue 0x1
#define DFIMISC_RegisterResetMask 0xffffffff

/* Register Field information for DFIMISC */

/* Register DFIMISC field dfi_init_complete_en */
/* PHY initialization complete enable signal.

When asserted the dfi_init_complete signal can be used to trigger SDRAM initialisation */
#define DFIMISC_dfi_init_complete_en_BitAddressOffset 0
#define DFIMISC_dfi_init_complete_en_RegisterSize 1

/* Register DFIMISC field phy_dbi_mode */
/* DBI implemented in DDRC or PHY.
  - 0 - DDRC implements DBI functionality.
  - 1 - PHY implements DBI functionality.
  Present only in designs configured to support DDR4 and LPDDR4. */
#define DFIMISC_phy_dbi_mode_BitAddressOffset 1
#define DFIMISC_phy_dbi_mode_RegisterSize 1

/* Register DFIMISC field dfi_data_cs_polarity */
/* Defines polarity of dfi_wrdata_cs and dfi_rddata_cs signals.
   - 0: Signals are active low
   - 1: Signals are active high
 */
#define DFIMISC_dfi_data_cs_polarity_BitAddressOffset 2
#define DFIMISC_dfi_data_cs_polarity_RegisterSize 1

/* Register DFIMISC field dfi_init_start */
/* PHY init start request signal.When asserted it triggers the PHY init start request */
#define DFIMISC_dfi_init_start_BitAddressOffset 5
#define DFIMISC_dfi_init_start_RegisterSize 1

/* Register DFIMISC field lp_optimized_write */
/* If this bit is 1, LPDDR4 write DQ is set to 8'hF8 if masked write with enabling DBI; otherwise, that value is set to 8'hFF */
#define DFIMISC_lp_optimized_write_BitAddressOffset 7
#define DFIMISC_lp_optimized_write_RegisterSize 1

/* Register DFIMISC field dfi_frequency */
/* Indicates the operating frequency of the system. The number of supported frequencies and the mapping of signal values to clock frequencies are defined by the PHY. */
#define DFIMISC_dfi_frequency_BitAddressOffset 8
#define DFIMISC_dfi_frequency_RegisterSize 5

/* Register DFIMISC field dfi_channel_mode */
/* This field controls how internal DFI data is connected to dfi0_*data* and dfi1_*data*. Under the following conditions, this must be set to 2'b01:
 - When using a Synopsys DWC LPDDR54 PHY
 - The PHY has 2 DFI channels(dfi0, dfi1)
 - Data width of each DFI channel is 16
 - Each DFI channel corresponds to 16-bit LPDDR5/4 channel (32-bit in total)
Otherwise, this must be set to 2'b00. */
#define DFIMISC_dfi_channel_mode_BitAddressOffset 16
#define DFIMISC_dfi_channel_mode_RegisterSize 2

/* End of Register Definition for DFIMISC */

/* Register DFISTAT */
/* DFI Status Register */
// #define DFISTAT (REGB_DDRC_CH0_BaseAddress + 0x514)
#define DFISTAT_RegisterSize 32
#define DFISTAT_RegisterResetValue 0x0
#define DFISTAT_RegisterResetMask 0xffffffff

/* Register Field information for DFISTAT */

/* Register DFISTAT field dfi_init_complete */
/* The status flag register which announces when the DFI initialization has been completed. The DFI INIT triggered by dfi_init_start signal and then the dfi_init_complete flag is polled to know when the initialization is done. */
#define DFISTAT_dfi_init_complete_BitAddressOffset 0
#define DFISTAT_dfi_init_complete_RegisterSize 1

/* Register DFISTAT field dfi_lp_ctrl_ack_stat */
/* Stores the value of the dfi_lp_ctrl_ack input to the controller. */
#define DFISTAT_dfi_lp_ctrl_ack_stat_BitAddressOffset 1
#define DFISTAT_dfi_lp_ctrl_ack_stat_RegisterSize 1

/* Register DFISTAT field dfi_lp_data_ack_stat */
/* Stores the value of the dfi_lp_data_ack input to the controller. */
#define DFISTAT_dfi_lp_data_ack_stat_BitAddressOffset 2
#define DFISTAT_dfi_lp_data_ack_stat_RegisterSize 1

/* End of Register Definition for DFISTAT */

/* Register DFIPHYMSTR */
/* DFI PHY Master */
// #define DFIPHYMSTR (REGB_DDRC_CH0_BaseAddress + 0x518)
#define DFIPHYMSTR_RegisterSize 32
#define DFIPHYMSTR_RegisterResetValue 0x1
#define DFIPHYMSTR_RegisterResetMask 0xffffffff

/* Register Field information for DFIPHYMSTR */

/* Register DFIPHYMSTR field dfi_phymstr_en */
/* Enables the PHY Master Interface:
    - 0 - Disabled
    - 1 - Enabled */
#define DFIPHYMSTR_dfi_phymstr_en_BitAddressOffset 0
#define DFIPHYMSTR_dfi_phymstr_en_RegisterSize 1

/* End of Register Definition for DFIPHYMSTR */

/* Register DFI0MSGCTL0 */
/* DFI0 Message Control Register 0. */
// #define DFI0MSGCTL0 (REGB_DDRC_CH0_BaseAddress + 0x520)
#define DFI0MSGCTL0_RegisterSize 32
#define DFI0MSGCTL0_RegisterResetValue 0x0
#define DFI0MSGCTL0_RegisterResetMask 0xffffffff

/* Register Field information for DFI0MSGCTL0 */

/* Register DFI0MSGCTL0 field dfi0_ctrlmsg_data */
/* DFI0 controller message data. */
#define DFI0MSGCTL0_dfi0_ctrlmsg_data_BitAddressOffset 0
#define DFI0MSGCTL0_dfi0_ctrlmsg_data_RegisterSize 16

/* Register DFI0MSGCTL0 field dfi0_ctrlmsg_cmd */
/* DFI0 controller message command. */
#define DFI0MSGCTL0_dfi0_ctrlmsg_cmd_BitAddressOffset 16
#define DFI0MSGCTL0_dfi0_ctrlmsg_cmd_RegisterSize 8

/* Register DFI0MSGCTL0 field dfi0_ctrlmsg_tout_clr */
/* If this bit is set, DFI0MSGSTAT0.dfi0_ctrlmsg_resp_tout is cleared by the controller. */
#define DFI0MSGCTL0_dfi0_ctrlmsg_tout_clr_BitAddressOffset 24
#define DFI0MSGCTL0_dfi0_ctrlmsg_tout_clr_RegisterSize 1

/* Register DFI0MSGCTL0 field dfi0_ctrlmsg_req */
/* Setting this register bit to 1 triggers a DFI controller message transmission operation. DDRCTL automatically clear this bit when the  DFI controller message request (dfi0_ctrlmsg_req) is asserted at the DFI MC to PHY Message port interface . This bit must be programmed separately after programming other register fields appropriately of this register.

Note: 
 - DFI controller message request can be issued only if DFIPHYMSTR.dfi_phymstr_en = 1
 - DFI controller message request must not be set during DFI LP mode due to software controlled low power entry.
 */
#define DFI0MSGCTL0_dfi0_ctrlmsg_req_BitAddressOffset 31
#define DFI0MSGCTL0_dfi0_ctrlmsg_req_RegisterSize 1

/* End of Register Definition for DFI0MSGCTL0 */

/* Register DFI0MSGSTAT0 */
/* DFI0 Message Status Register 0 */
// #define DFI0MSGSTAT0 (REGB_DDRC_CH0_BaseAddress + 0x524)
#define DFI0MSGSTAT0_RegisterSize 32
#define DFI0MSGSTAT0_RegisterResetValue 0x0
#define DFI0MSGSTAT0_RegisterResetMask 0xffffffff

/* Register Field information for DFI0MSGSTAT0 */

/* Register DFI0MSGSTAT0 field dfi0_ctrlmsg_req_busy */
/* The SoC must trigger DFI controller message request only if this signal is low. This signal goes high in the clock after the DDRCTL accepts software triggered DFI controller message request by writing into DFI0MSGCTRL0.dfi0_ctrlmsg_req. It goes low when PHY deasserts dfi0_ctrlmsg_ack or dfi0_ctrlmsg_resp_tout event has triggered.
 - 0 - Indicates that the SoC core can initiate a DFI controller message request operation
 - 1 - Indicates that DFI controller message request operation is in progress
 */
#define DFI0MSGSTAT0_dfi0_ctrlmsg_req_busy_BitAddressOffset 0
#define DFI0MSGSTAT0_dfi0_ctrlmsg_req_busy_RegisterSize 1

/* Register DFI0MSGSTAT0 field dfi0_ctrlmsg_resp_tout */
/* This bit is set if dfi0_ctrlmsg_ack is not asserted by PHY within dfi_t_ctrlmsg_resp after asserting dfi0_ctrlmsg_req */
#define DFI0MSGSTAT0_dfi0_ctrlmsg_resp_tout_BitAddressOffset 16
#define DFI0MSGSTAT0_dfi0_ctrlmsg_resp_tout_RegisterSize 1

/* End of Register Definition for DFI0MSGSTAT0 */

/* Register POISONCFG */
/* AXI Poison Configuration Register. Common for all AXI ports */
// #define POISONCFG (REGB_DDRC_CH0_BaseAddress + 0x580)
#define POISONCFG_RegisterSize 32
#define POISONCFG_RegisterResetValue 0x110011
#define POISONCFG_RegisterResetMask 0xffffffff

/* Register Field information for POISONCFG */

/* Register POISONCFG field wr_poison_slverr_en */
/* If set to 1, enables SLVERR response for write transaction poisoning */
#define POISONCFG_wr_poison_slverr_en_BitAddressOffset 0
#define POISONCFG_wr_poison_slverr_en_RegisterSize 1

/* Register POISONCFG field wr_poison_intr_en */
/* If set to 1, enables interrupts for write transaction poisoning */
#define POISONCFG_wr_poison_intr_en_BitAddressOffset 4
#define POISONCFG_wr_poison_intr_en_RegisterSize 1

/* Register POISONCFG field wr_poison_intr_clr */
/* Interrupt clear for write transaction poisoning. Allow 2/3 clock cycles for correct value to propagate to core logic and clear the interrupts. DDRCTL automatically clears this bit. */
#define POISONCFG_wr_poison_intr_clr_BitAddressOffset 8
#define POISONCFG_wr_poison_intr_clr_RegisterSize 1

/* Register POISONCFG field rd_poison_slverr_en */
/* If set to 1, enables SLVERR response for read transaction poisoning */
#define POISONCFG_rd_poison_slverr_en_BitAddressOffset 16
#define POISONCFG_rd_poison_slverr_en_RegisterSize 1

/* Register POISONCFG field rd_poison_intr_en */
/* If set to 1, enables interrupts for read transaction poisoning */
#define POISONCFG_rd_poison_intr_en_BitAddressOffset 20
#define POISONCFG_rd_poison_intr_en_RegisterSize 1

/* Register POISONCFG field rd_poison_intr_clr */
/* Interrupt clear for read transaction poisoning.  Allow 2/3 clock cycles for correct value to propagate to core logic and clear the interrupts. DDRCTL automatically clears this bit. */
#define POISONCFG_rd_poison_intr_clr_BitAddressOffset 24
#define POISONCFG_rd_poison_intr_clr_RegisterSize 1

/* End of Register Definition for POISONCFG */

/* Register POISONSTAT */
/* AXI Poison Status Register */
// #define POISONSTAT (REGB_DDRC_CH0_BaseAddress + 0x584)
#define POISONSTAT_RegisterSize 32
#define POISONSTAT_RegisterResetValue 0x0
#define POISONSTAT_RegisterResetMask 0xffffffff

/* Register Field information for POISONSTAT */

/* Register POISONSTAT field wr_poison_intr_0 */
/* Write transaction poisoning error interrupt for port 0. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock. */
#define POISONSTAT_wr_poison_intr_0_BitAddressOffset 0
#define POISONSTAT_wr_poison_intr_0_RegisterSize 1

/* Register POISONSTAT field wr_poison_intr_1 */
/* Write transaction poisoning error interrupt for port 1. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock. */
#define POISONSTAT_wr_poison_intr_1_BitAddressOffset 1
#define POISONSTAT_wr_poison_intr_1_RegisterSize 1

/* Register POISONSTAT field wr_poison_intr_2 */
/* Write transaction poisoning error interrupt for port 2. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock. */
#define POISONSTAT_wr_poison_intr_2_BitAddressOffset 2
#define POISONSTAT_wr_poison_intr_2_RegisterSize 1

/* Register POISONSTAT field wr_poison_intr_3 */
/* Write transaction poisoning error interrupt for port 3. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's write address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock. */
#define POISONSTAT_wr_poison_intr_3_BitAddressOffset 3
#define POISONSTAT_wr_poison_intr_3_RegisterSize 1

/* Register POISONSTAT field rd_poison_intr_0 */
/* Read transaction poisoning error interrupt for port 0. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock. */
#define POISONSTAT_rd_poison_intr_0_BitAddressOffset 16
#define POISONSTAT_rd_poison_intr_0_RegisterSize 1

/* Register POISONSTAT field rd_poison_intr_1 */
/* Read transaction poisoning error interrupt for port 1. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock. */
#define POISONSTAT_rd_poison_intr_1_BitAddressOffset 17
#define POISONSTAT_rd_poison_intr_1_RegisterSize 1

/* Register POISONSTAT field rd_poison_intr_2 */
/* Read transaction poisoning error interrupt for port 2. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock. */
#define POISONSTAT_rd_poison_intr_2_BitAddressOffset 18
#define POISONSTAT_rd_poison_intr_2_RegisterSize 1

/* Register POISONSTAT field rd_poison_intr_3 */
/* Read transaction poisoning error interrupt for port 3. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port's read address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock. */
#define POISONSTAT_rd_poison_intr_3_BitAddressOffset 19
#define POISONSTAT_rd_poison_intr_3_RegisterSize 1

/* End of Register Definition for POISONSTAT */

/* Register ECCCFG0 */
/* ECC Configuration Register 0 */
// #define ECCCFG0 (REGB_DDRC_CH0_BaseAddress + 0x600)
#define ECCCFG0_RegisterSize 32
#define ECCCFG0_RegisterResetValue 0x33f7f40
#define ECCCFG0_RegisterResetMask 0xffffffff

/* Register Field information for ECCCFG0 */

/* Register ECCCFG0 field ecc_mode */
/* ECC mode indicator
 - 000 - ECC disabled
 - 100 - ECC enabled - SEC/DED over 1 beat
 - 101 - ECC enabled - Advanced ECC X4/X8 (Illegal value when MEMC_INLINE_ECC=1)
 - all other settings are reserved for future use */
#define ECCCFG0_ecc_mode_BitAddressOffset 0
#define ECCCFG0_ecc_mode_RegisterSize 3

/* Register ECCCFG0 field dis_scrub */
/* Disable ECC scrubs. Valid only when ECCCFG0.ecc_mode = 3'b100 or 3'b101 and MEMC_USE_RMW is defined.

  Note: Scrub is not supported in inline ECC mode and the register value is don't care.
 */
#define ECCCFG0_dis_scrub_BitAddressOffset 4
#define ECCCFG0_dis_scrub_RegisterSize 1

/* Register ECCCFG0 field ecc_ap_en */
/* Enable address protection feature. Only supported when inline ECC is enabled.
      - 0: disable
      - 1: enable */
#define ECCCFG0_ecc_ap_en_BitAddressOffset 6
#define ECCCFG0_ecc_ap_en_RegisterSize 1

/* Register ECCCFG0 field ecc_region_remap_en */
/* Enables remapping ECC region feature.
Only supported when inline ECC is enabled.
 - 0 - Disable
 - 1 - Enable */
#define ECCCFG0_ecc_region_remap_en_BitAddressOffset 7
#define ECCCFG0_ecc_region_remap_en_RegisterSize 1

/* Register ECCCFG0 field ecc_region_map */
/* 
Selectable Protected Region setting.
Memory space is divided to 8/16/32/64 regions which is determined by ECCCFG0.ecc_region_map_granu.

Note: Highest 1/8 memory space is always ECC region.

Lowest 7 regions are Selectable Protected Regions. The Selectable Protected Regions can be protected/non-protected selectively by ECCCFG0.ecc_region_map[6:0]. Other upper regions are non-protected region if any. Each bit of ECCCFG0.ecc_region_map[6:0] correspond to each of lowest 7 regions respectively. 

In order to protect a region with ECC, set the corresponding bit to 1, otherwise set to 0.  All "0"s is invalid - there must be at least one protected region if inline ECC is enabled via ECCCFG0.ecc_mode register.

All regions are protected with the following setting.
 - ecc_region_map=7'b1111111
 - ecc_region_map_granu=0
Only first 1/64 region is protected with the following setting.
 - ecc_region_map=7'b0000001
 - ecc_region_map_granu=3
 */
#define ECCCFG0_ecc_region_map_BitAddressOffset 8
#define ECCCFG0_ecc_region_map_RegisterSize 7

/* Register ECCCFG0 field blk_channel_idle_time_x32 */
/* Indicates the number of cycles on HIF interface with no access to protected regions which will cause flush of all the block channels. In order to flush block channel, DDRCTL injects write ECC command (when there is no incoming HIF command) if there is any write in the block and then stop tracking the block address.
   - 0 indicates no timeout (feature is disabled, not supported with this version)
   - 1 indicates 32 cycles
   - 2 indicates 2*32 cycles, etc.
 Unit: Multiples of 32 DRAM clock cycles.

 Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define ECCCFG0_blk_channel_idle_time_x32_BitAddressOffset 16
#define ECCCFG0_blk_channel_idle_time_x32_RegisterSize 6

/* Register ECCCFG0 field ecc_ap_err_threshold */
/* 
Set threshold for address parity error.

ECCAPSTAT.ecc_ap_err is asserted if number of ECC errors (correctable/uncorrectable) within one burst exceeds this threshold.

This register value must be less than "Total number of ECC checks within one burst"  when this feature is used,

"Total number of ECC check within one burst" is calculated by (DRAM Data width) x (DRAM BL) / 64. 
 */
#define ECCCFG0_ecc_ap_err_threshold_BitAddressOffset 24
#define ECCCFG0_ecc_ap_err_threshold_RegisterSize 3

/* Register ECCCFG0 field ecc_region_map_other */
/* When ECCCFG0.ecc_region_map_granu>0, there is a region which is not controlled by ecc_region_map.
This register defines the region to be protected or non-protected for Inline ECC.
 - 0 - Non-Protected
 - 1 - Protected
This register is valid only when ECCCFG0.ecc_region_map_granu>0 && ECCCFG0.ecc_mode=4.
 */
#define ECCCFG0_ecc_region_map_other_BitAddressOffset 29
#define ECCCFG0_ecc_region_map_other_RegisterSize 1

/* Register ECCCFG0 field ecc_region_map_granu */
/* 
Granularity of Selectable Protected Region.

Define one region size for ECCCFG0.ecc_region_map
 - 0 - 1/8 of memory spaces 
 - 1 - 1/16 of memory spaces 
 - 2 - 1/32 of memory spaces 
 - 3 - 1/64 of memory spaces 
 */
#define ECCCFG0_ecc_region_map_granu_BitAddressOffset 30
#define ECCCFG0_ecc_region_map_granu_RegisterSize 2

/* End of Register Definition for ECCCFG0 */

/* Register ECCCFG1 */
/* ECC Configuration Register 1 */
// #define ECCCFG1 (REGB_DDRC_CH0_BaseAddress + 0x604)
#define ECCCFG1_RegisterSize 32
#define ECCCFG1_RegisterResetValue 0x7b0
#define ECCCFG1_RegisterResetMask 0xffffffff

/* Register Field information for ECCCFG1 */

/* Register ECCCFG1 field data_poison_en */
/* Enable ECC data poisoning - introduces ECC errors on writes to address specified by the ECCPOISONADDR0/1 registers
This field must be set to 0 if ECC is disabled (ECCCFG0.ecc_mode = 0). */
#define ECCCFG1_data_poison_en_BitAddressOffset 0
#define ECCCFG1_data_poison_en_RegisterSize 1

/* Register ECCCFG1 field data_poison_bit */
/* Selects whether to poison 1 or 2 bits - if 0 -> 2-bit (uncorrectable) data poisoning, if 1 -> 1-bit (correctable) data poisoning, if ECCCFG1.data_poison_en=1.
Valid only when MEMC_ECC_SUPPORT==1 (SECDED ECC mode) */
#define ECCCFG1_data_poison_bit_BitAddressOffset 1
#define ECCCFG1_data_poison_bit_RegisterSize 1

/* Register ECCCFG1 field ecc_region_parity_lock */
/* Locks the parity section of the ECC region (hole) which is the highest system address part of the memory that stores ECC parity for protected region.
   - 1: Locked; if this region is accessed, error response is generated.
   - 0: Unlocked; this region can be accessed normally, similar to non-ECC protected region. */
#define ECCCFG1_ecc_region_parity_lock_BitAddressOffset 4
#define ECCCFG1_ecc_region_parity_lock_RegisterSize 1

/* Register ECCCFG1 field ecc_region_waste_lock */
/* Locks the remaining waste parts of the ECC region (hole) that are not locked by ecc_region_parity_lock.
   - 1: Locked; if this region is accessed, error response is generated.
   - 0: Unlocked; this region can be accessed normally, similar to non-ECC protected region. */
#define ECCCFG1_ecc_region_waste_lock_BitAddressOffset 5
#define ECCCFG1_ecc_region_waste_lock_RegisterSize 1

/* Register ECCCFG1 field blk_channel_active_term */
/* 
Block Channel active terminate enable.

If enabled, block channel is terminated when full block write or full block read is performed (all address within block are written or read)
 - 0 - Disable (only for debug purpose)
 - 1 - Enable  (default)
This is debug register, and this must be set to 1 for normal operation.
 */
#define ECCCFG1_blk_channel_active_term_BitAddressOffset 7
#define ECCCFG1_blk_channel_active_term_RegisterSize 1

/* Register ECCCFG1 field active_blk_channel */
/* Number of active block channels. Total number of ECC block channels are defined by MEMC_NO_OF_BLK_CHANNEL hardware parameter. This register can limit the number of available channels. For example, if set to 0, only one channel is active and therefore block interleaving is disabled.

The valid range is from 0 to MEMC_NO_OF_BLK_CHANNEL-1.
 */
#define ECCCFG1_active_blk_channel_BitAddressOffset 8
#define ECCCFG1_active_blk_channel_RegisterSize 4

/* End of Register Definition for ECCCFG1 */

/* Register ECCSTAT */
/* SECDED ECC Status Register */
// #define ECCSTAT (REGB_DDRC_CH0_BaseAddress + 0x608)
#define ECCSTAT_RegisterSize 32
#define ECCSTAT_RegisterResetValue 0x0
#define ECCSTAT_RegisterResetMask 0xffffffff

/* Register Field information for ECCSTAT */

/* Register ECCSTAT field ecc_corrected_bit_num */
/* Bit number corrected by single-bit ECC error. See ECC section of architecture chapter for encoding of this field. If more than one data lane has an error, the lower data lane is selected. This register is 7 bits wide in order to handle 72 bits of the data present in a single lane. */
#define ECCSTAT_ecc_corrected_bit_num_BitAddressOffset 0
#define ECCSTAT_ecc_corrected_bit_num_RegisterSize 7

/* Register ECCSTAT field ecc_corrected_err */
/* Single-bit error indicator.

  In sideband ECC mode, 1 bit per ECC lane.

  In inline ECC mode, the register always is 1 bit to indicate correctable error on any lane. */
#define ECCSTAT_ecc_corrected_err_BitAddressOffset 8
#define ECCSTAT_ecc_corrected_err_RegisterSize 1

/* Register ECCSTAT field ecc_uncorrected_err */
/* Double-bit error indicator.

  In sideband ECC mode, 1 bit per ECC lane.

  In inline ECC mode, the register always is 1 bit to indicate uncorrectable error on any lane. */
#define ECCSTAT_ecc_uncorrected_err_BitAddressOffset 16
#define ECCSTAT_ecc_uncorrected_err_RegisterSize 1

/* End of Register Definition for ECCSTAT */

/* Register ECCCTL */
/* ECC Clear Register */
// #define ECCCTL (REGB_DDRC_CH0_BaseAddress + 0x60c)
#define ECCCTL_RegisterSize 32
#define ECCCTL_RegisterResetValue 0x700
#define ECCCTL_RegisterResetMask 0xffffffff

/* Register Field information for ECCCTL */

/* Register ECCCTL field ecc_corrected_err_clr */
/* Setting this register bit to 1 clears the currently stored corrected ECC error. 
 The following registers are cleared:
 - ECCSTAT.ecc_corrected_err
 - ADVECCSTAT.advecc_corrected_err
 - ADVECCSTAT.advecc_num_err_symbol
 - ADVECCSTAT.advecc_err_symbol_pos
 - ADVECCSTAT.advecc_err_symbol_bits
 - ECCCSYN0
 - ECCCSYN1
 - ECCCSYN2
 - ECCBITMASK0
 - ECCBITMASK1
 - ECCBITMASK2
DDRCTL automatically clears this bit. */
#define ECCCTL_ecc_corrected_err_clr_BitAddressOffset 0
#define ECCCTL_ecc_corrected_err_clr_RegisterSize 1

/* Register ECCCTL field ecc_uncorrected_err_clr */
/* Setting this register bit to 1 clears the currently stored uncorrected ECC error.

The following registers are cleared:
 - ECCSTAT.ecc_uncorrected_err
 - ADVECCSTAT.advecc_uncorrected_err
 - ECCUSYN0
 - ECCUSYN1
 - ECCUSYN2
DDRCTL automatically clears this bit. */
#define ECCCTL_ecc_uncorrected_err_clr_BitAddressOffset 1
#define ECCCTL_ecc_uncorrected_err_clr_RegisterSize 1

/* Register ECCCTL field ecc_corr_err_cnt_clr */
/* Setting this register bit to 1 clears the currently stored corrected ECC error count. The ECCERRCNT.ecc_corr_err_cnt register is cleared by this operation. DDRCTL automatically clears this bit. */
#define ECCCTL_ecc_corr_err_cnt_clr_BitAddressOffset 2
#define ECCCTL_ecc_corr_err_cnt_clr_RegisterSize 1

/* Register ECCCTL field ecc_uncorr_err_cnt_clr */
/* Setting this register bit to 1 clears the currently stored uncorrected ECC error count. The ECCERRCNT.ecc_uncorr_err_cnt register is cleared by this operation. DDRCTL automatically clears this bit. */
#define ECCCTL_ecc_uncorr_err_cnt_clr_BitAddressOffset 3
#define ECCCTL_ecc_uncorr_err_cnt_clr_RegisterSize 1

/* Register ECCCTL field ecc_ap_err_intr_clr */
/* Interrupt clear bit for ecc_ap_err. If this bit is set, the ECCAPSTAT.ecc_ap_err/ecc_ap_err_intr will be cleared. DDRCTL automatically clears this bit. */
#define ECCCTL_ecc_ap_err_intr_clr_BitAddressOffset 4
#define ECCCTL_ecc_ap_err_intr_clr_RegisterSize 1

/* Register ECCCTL field ecc_corrected_err_intr_en */
/* Interrupt enable bit for ecc_corrected_err_intr.
   - 1 Enabled
   - 0 Disabled
 */
#define ECCCTL_ecc_corrected_err_intr_en_BitAddressOffset 8
#define ECCCTL_ecc_corrected_err_intr_en_RegisterSize 1

/* Register ECCCTL field ecc_uncorrected_err_intr_en */
/* Interrupt enable bit for ecc_uncorrected_err_intr.
   - 1: Enabled
   - 0: Disabled
 */
#define ECCCTL_ecc_uncorrected_err_intr_en_BitAddressOffset 9
#define ECCCTL_ecc_uncorrected_err_intr_en_RegisterSize 1

/* Register ECCCTL field ecc_ap_err_intr_en */
/* Interrupt enable bit for ecc_ap_err_intr.
   - 1: Enabled
   - 0: Disabled
 */
#define ECCCTL_ecc_ap_err_intr_en_BitAddressOffset 10
#define ECCCTL_ecc_ap_err_intr_en_RegisterSize 1

/* Register ECCCTL field ecc_corrected_err_intr_force */
/* Interrupt force bit for ecc_corrected_err_intr. Setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define ECCCTL_ecc_corrected_err_intr_force_BitAddressOffset 16
#define ECCCTL_ecc_corrected_err_intr_force_RegisterSize 1

/* Register ECCCTL field ecc_uncorrected_err_intr_force */
/* Interrupt force bit for ecc_uncorrected_err_intr. Setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define ECCCTL_ecc_uncorrected_err_intr_force_BitAddressOffset 17
#define ECCCTL_ecc_uncorrected_err_intr_force_RegisterSize 1

/* Register ECCCTL field ecc_ap_err_intr_force */
/* Interrupt force bit for ecc_ap_err_intr. Setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define ECCCTL_ecc_ap_err_intr_force_BitAddressOffset 18
#define ECCCTL_ecc_ap_err_intr_force_RegisterSize 1

/* End of Register Definition for ECCCTL */

/* Register ECCERRCNT */
/* ECC Error Counter Register */
// #define ECCERRCNT (REGB_DDRC_CH0_BaseAddress + 0x610)
#define ECCERRCNT_RegisterSize 32
#define ECCERRCNT_RegisterResetValue 0x0
#define ECCERRCNT_RegisterResetMask 0xffffffff

/* Register Field information for ECCERRCNT */

/* Register ECCERRCNT field ecc_corr_err_cnt */
/* Number of correctable ECC errors detected.

Note that the saturation behavior of this register is different, depending on the type of ECC.  For advanced ECC or Inline ECC, it saturates at 0xFFFF, while for Side-band ECC with SECDED ECC, it saturates at 0xFFFC or above. */
#define ECCERRCNT_ecc_corr_err_cnt_BitAddressOffset 0
#define ECCERRCNT_ecc_corr_err_cnt_RegisterSize 16

/* Register ECCERRCNT field ecc_uncorr_err_cnt */
/* Number of uncorrectable ECC errors detected.

Note that the saturation behavior of this register is different, depending on the type of ECC.  For advanced ECC or Inline ECC, it saturates at 0xFFFF, while for Side-band ECC with SECDED ECC, it saturates at 0xFFFC or above. */
#define ECCERRCNT_ecc_uncorr_err_cnt_BitAddressOffset 16
#define ECCERRCNT_ecc_uncorr_err_cnt_RegisterSize 16

/* End of Register Definition for ECCERRCNT */

/* Register ECCCADDR0 */
/* ECC Corrected Error Address Register 0 */
// #define ECCCADDR0 (REGB_DDRC_CH0_BaseAddress + 0x614)
#define ECCCADDR0_RegisterSize 32
#define ECCCADDR0_RegisterResetValue 0x0
#define ECCCADDR0_RegisterResetMask 0xffffffff

/* Register Field information for ECCCADDR0 */

/* Register ECCCADDR0 field ecc_corr_row */
/* Indicates the page/row number of a read resulting in a corrected ECC error. This is 18-bits wide in configurations with DDR4 support and 16-bits in all other configurations. */
#define ECCCADDR0_ecc_corr_row_BitAddressOffset 0
#define ECCCADDR0_ecc_corr_row_RegisterSize 18

/* Register ECCCADDR0 field ecc_corr_rank */
/* Indicates the rank number of a read resulting in a corrected ECC error */
#define ECCCADDR0_ecc_corr_rank_BitAddressOffset 24
#define ECCCADDR0_ecc_corr_rank_RegisterSize 1

/* End of Register Definition for ECCCADDR0 */

/* Register ECCCADDR1 */
/* ECC Corrected Error Address Register 1 */
// #define ECCCADDR1 (REGB_DDRC_CH0_BaseAddress + 0x618)
#define ECCCADDR1_RegisterSize 32
#define ECCCADDR1_RegisterResetValue 0x0
#define ECCCADDR1_RegisterResetMask 0xffffffff

/* Register Field information for ECCCADDR1 */

/* Register ECCCADDR1 field ecc_corr_col */
/* Block number of a read resulting in a corrected ECC error (lowest bit not assigned here) */
#define ECCCADDR1_ecc_corr_col_BitAddressOffset 0
#define ECCCADDR1_ecc_corr_col_RegisterSize 11

/* Register ECCCADDR1 field ecc_corr_bank */
/* Bank number of a read resulting in a corrected ECC error */
#define ECCCADDR1_ecc_corr_bank_BitAddressOffset 16
#define ECCCADDR1_ecc_corr_bank_RegisterSize 3

/* Register ECCCADDR1 field ecc_corr_bg */
/* Bank Group number of a read resulting in a corrected ECC error */
#define ECCCADDR1_ecc_corr_bg_BitAddressOffset 24
#define ECCCADDR1_ecc_corr_bg_RegisterSize 2

/* End of Register Definition for ECCCADDR1 */

/* Register ECCCSYN0 */
/* ECC Corrected Syndrome Register 0 */
// #define ECCCSYN0 (REGB_DDRC_CH0_BaseAddress + 0x61c)
#define ECCCSYN0_RegisterSize 32
#define ECCCSYN0_RegisterResetValue 0x0
#define ECCCSYN0_RegisterResetMask 0xffffffff

/* Register Field information for ECCCSYN0 */

/* Register ECCCSYN0 field ecc_corr_syndromes_31_0 */
/* Data pattern that resulted in a corrected error. For 16-bit ECC, only bits [15:0] are used */
#define ECCCSYN0_ecc_corr_syndromes_31_0_BitAddressOffset 0
#define ECCCSYN0_ecc_corr_syndromes_31_0_RegisterSize 32

/* End of Register Definition for ECCCSYN0 */

/* Register ECCCSYN1 */
/* ECC Corrected Syndrome Register 1 */
// #define ECCCSYN1 (REGB_DDRC_CH0_BaseAddress + 0x620)
#define ECCCSYN1_RegisterSize 32
#define ECCCSYN1_RegisterResetValue 0x0
#define ECCCSYN1_RegisterResetMask 0xffffffff

/* Register Field information for ECCCSYN1 */

/* Register ECCCSYN1 field ecc_corr_syndromes_63_32 */
/* Data pattern that resulted in a corrected error. For 32-bit ECC and 16-bit ECC, this register is not used */
#define ECCCSYN1_ecc_corr_syndromes_63_32_BitAddressOffset 0
#define ECCCSYN1_ecc_corr_syndromes_63_32_RegisterSize 32

/* End of Register Definition for ECCCSYN1 */

/* Register ECCCSYN2 */
/* ECC Corrected Syndrome Register 2 */
// #define ECCCSYN2 (REGB_DDRC_CH0_BaseAddress + 0x624)
#define ECCCSYN2_RegisterSize 32
#define ECCCSYN2_RegisterResetValue 0x0
#define ECCCSYN2_RegisterResetMask 0xffffffff

/* Register Field information for ECCCSYN2 */

/* Register ECCCSYN2 field ecc_corr_syndromes_71_64 */
/* Data pattern that resulted in a corrected error one for each ECC lane, all concatenated together
This register refers to the ECC byte, which is bits [71:64] for 64-bit ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC */
#define ECCCSYN2_ecc_corr_syndromes_71_64_BitAddressOffset 0
#define ECCCSYN2_ecc_corr_syndromes_71_64_RegisterSize 8

/* End of Register Definition for ECCCSYN2 */

/* Register ECCBITMASK0 */
/* ECC Corrected Data Bit Mask Register 0 */
// #define ECCBITMASK0 (REGB_DDRC_CH0_BaseAddress + 0x628)
#define ECCBITMASK0_RegisterSize 32
#define ECCBITMASK0_RegisterResetValue 0x0
#define ECCBITMASK0_RegisterResetMask 0xffffffff

/* Register Field information for ECCBITMASK0 */

/* Register ECCBITMASK0 field ecc_corr_bit_mask_31_0 */
/* Mask for the corrected data portion
    - 1 on any bit indicates that the bit has been corrected by the ECC logic
    - 0 on any bit indicates that the bit has not been corrected by the ECC logic
This register accumulates data over multiple ECC errors, to give an overall indication of which bits are being fixed. It is cleared by writing a 1 to ECCCTL.ecc_corrected_err_clr.
For 16-bit ECC, only bits [15:0] are used */
#define ECCBITMASK0_ecc_corr_bit_mask_31_0_BitAddressOffset 0
#define ECCBITMASK0_ecc_corr_bit_mask_31_0_RegisterSize 32

/* End of Register Definition for ECCBITMASK0 */

/* Register ECCBITMASK1 */
/* ECC Corrected Data Bit Mask Register 1 */
// #define ECCBITMASK1 (REGB_DDRC_CH0_BaseAddress + 0x62c)
#define ECCBITMASK1_RegisterSize 32
#define ECCBITMASK1_RegisterResetValue 0x0
#define ECCBITMASK1_RegisterResetMask 0xffffffff

/* Register Field information for ECCBITMASK1 */

/* Register ECCBITMASK1 field ecc_corr_bit_mask_63_32 */
/* Mask for the corrected data portion
    - 1 on any bit indicates that the bit has been corrected by the ECC logic
    - 0 on any bit indicates that the bit has not been corrected by the ECC logic
This register accumulates data over multiple ECC errors, to give an overall indication of which bits are being fixed. It is cleared by writing a 1 to ECCCTL.ecc_corrected_err_clr.
For 32-bit ECC and 16-bit ECC, this register is not used */
#define ECCBITMASK1_ecc_corr_bit_mask_63_32_BitAddressOffset 0
#define ECCBITMASK1_ecc_corr_bit_mask_63_32_RegisterSize 32

/* End of Register Definition for ECCBITMASK1 */

/* Register ECCBITMASK2 */
/* ECC Corrected Data Bit Mask Register 2 */
// #define ECCBITMASK2 (REGB_DDRC_CH0_BaseAddress + 0x630)
#define ECCBITMASK2_RegisterSize 32
#define ECCBITMASK2_RegisterResetValue 0x0
#define ECCBITMASK2_RegisterResetMask 0xffffffff

/* Register Field information for ECCBITMASK2 */

/* Register ECCBITMASK2 field ecc_corr_bit_mask_71_64 */
/* Mask for the corrected data portion
    - 1 on any bit indicates that the bit has been corrected by the ECC logic
    - 0 on any bit indicates that the bit has not been corrected by the ECC logic
This register accumulates data over multiple ECC errors, to give an overall indication of which bits are being fixed. It is cleared by writing a 1 to ECCCTL.ecc_corrected_err_clr.
This register refers to the ECC byte, which is bits [71:64] for 64-bit ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC */
#define ECCBITMASK2_ecc_corr_bit_mask_71_64_BitAddressOffset 0
#define ECCBITMASK2_ecc_corr_bit_mask_71_64_RegisterSize 8

/* End of Register Definition for ECCBITMASK2 */

/* Register ECCUADDR0 */
/* ECC Uncorrected Error Address Register 0 */
// #define ECCUADDR0 (REGB_DDRC_CH0_BaseAddress + 0x634)
#define ECCUADDR0_RegisterSize 32
#define ECCUADDR0_RegisterResetValue 0x0
#define ECCUADDR0_RegisterResetMask 0xffffffff

/* Register Field information for ECCUADDR0 */

/* Register ECCUADDR0 field ecc_uncorr_row */
/* Page/row number of a read resulting in an uncorrected ECC error. This is 18-bits wide in configurations with DDR4 support and 16-bits in all other configurations. */
#define ECCUADDR0_ecc_uncorr_row_BitAddressOffset 0
#define ECCUADDR0_ecc_uncorr_row_RegisterSize 18

/* Register ECCUADDR0 field ecc_uncorr_rank */
/* Rank number of a read resulting in an uncorrected ECC error */
#define ECCUADDR0_ecc_uncorr_rank_BitAddressOffset 24
#define ECCUADDR0_ecc_uncorr_rank_RegisterSize 1

/* End of Register Definition for ECCUADDR0 */

/* Register ECCUADDR1 */
/* ECC Uncorrected Error Address Register 1 */
// #define ECCUADDR1 (REGB_DDRC_CH0_BaseAddress + 0x638)
#define ECCUADDR1_RegisterSize 32
#define ECCUADDR1_RegisterResetValue 0x0
#define ECCUADDR1_RegisterResetMask 0xffffffff

/* Register Field information for ECCUADDR1 */

/* Register ECCUADDR1 field ecc_uncorr_col */
/* Block number of a read resulting in an uncorrected ECC error (lowest bit not assigned here) */
#define ECCUADDR1_ecc_uncorr_col_BitAddressOffset 0
#define ECCUADDR1_ecc_uncorr_col_RegisterSize 11

/* Register ECCUADDR1 field ecc_uncorr_bank */
/* Bank number of a read resulting in an uncorrected ECC error */
#define ECCUADDR1_ecc_uncorr_bank_BitAddressOffset 16
#define ECCUADDR1_ecc_uncorr_bank_RegisterSize 3

/* Register ECCUADDR1 field ecc_uncorr_bg */
/* Bank Group number of a read resulting in an uncorrected ECC error */
#define ECCUADDR1_ecc_uncorr_bg_BitAddressOffset 24
#define ECCUADDR1_ecc_uncorr_bg_RegisterSize 2

/* End of Register Definition for ECCUADDR1 */

/* Register ECCUSYN0 */
/* ECC Uncorrected Syndrome Register 0 */
// #define ECCUSYN0 (REGB_DDRC_CH0_BaseAddress + 0x63c)
#define ECCUSYN0_RegisterSize 32
#define ECCUSYN0_RegisterResetValue 0x0
#define ECCUSYN0_RegisterResetMask 0xffffffff

/* Register Field information for ECCUSYN0 */

/* Register ECCUSYN0 field ecc_uncorr_syndromes_31_0 */
/* Data pattern that resulted in an uncorrected error, one for each ECC lane, all concatenated together. For 16-bit ECC, only bits [15:0] are used */
#define ECCUSYN0_ecc_uncorr_syndromes_31_0_BitAddressOffset 0
#define ECCUSYN0_ecc_uncorr_syndromes_31_0_RegisterSize 32

/* End of Register Definition for ECCUSYN0 */

/* Register ECCUSYN1 */
/* ECC Uncorrected Syndrome Register 1 */
// #define ECCUSYN1 (REGB_DDRC_CH0_BaseAddress + 0x640)
#define ECCUSYN1_RegisterSize 32
#define ECCUSYN1_RegisterResetValue 0x0
#define ECCUSYN1_RegisterResetMask 0xffffffff

/* Register Field information for ECCUSYN1 */

/* Register ECCUSYN1 field ecc_uncorr_syndromes_63_32 */
/* Data pattern that resulted in an uncorrected error, one for each ECC lane, all concatenated together. For 32-bit ECC and 16-bit ECC, this register is not used */
#define ECCUSYN1_ecc_uncorr_syndromes_63_32_BitAddressOffset 0
#define ECCUSYN1_ecc_uncorr_syndromes_63_32_RegisterSize 32

/* End of Register Definition for ECCUSYN1 */

/* Register ECCUSYN2 */
/* ECC Uncorrected Syndrome Register 2 */
// #define ECCUSYN2 (REGB_DDRC_CH0_BaseAddress + 0x644)
#define ECCUSYN2_RegisterSize 32
#define ECCUSYN2_RegisterResetValue 0x0
#define ECCUSYN2_RegisterResetMask 0xffffffff

/* Register Field information for ECCUSYN2 */

/* Register ECCUSYN2 field ecc_uncorr_syndromes_71_64 */
/* Data pattern that resulted in an uncorrected error one for each ECC lane, all concatenated together.
This register refers to the ECC byte, which is bits [71:64] for 64-bit ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC */
#define ECCUSYN2_ecc_uncorr_syndromes_71_64_BitAddressOffset 0
#define ECCUSYN2_ecc_uncorr_syndromes_71_64_RegisterSize 8

/* End of Register Definition for ECCUSYN2 */

/* Register ECCPOISONADDR0 */
/* ECC Data Poisoning Address Register 0. */
// #define ECCPOISONADDR0 (REGB_DDRC_CH0_BaseAddress + 0x648)
#define ECCPOISONADDR0_RegisterSize 32
#define ECCPOISONADDR0_RegisterResetValue 0x0
#define ECCPOISONADDR0_RegisterResetMask 0xffffffff

/* Register Field information for ECCPOISONADDR0 */

/* Register ECCPOISONADDR0 field ecc_poison_col */
/* Indicates the column address for ECC poisoning. Note that this column address must be burst aligned:
 - In full bus width mode, ecc_poison_col[2:0] must be set to 0
 - In half bus width mode, ecc_poison_col[3:0] must be set to 0
 - In quarter bus width mode, ecc_poison_col[4:0] must be set to 0 */
#define ECCPOISONADDR0_ecc_poison_col_BitAddressOffset 0
#define ECCPOISONADDR0_ecc_poison_col_RegisterSize 12

/* Register ECCPOISONADDR0 field ecc_poison_rank */
/* Rank address for ECC poisoning */
#define ECCPOISONADDR0_ecc_poison_rank_BitAddressOffset 24
#define ECCPOISONADDR0_ecc_poison_rank_RegisterSize 1

/* End of Register Definition for ECCPOISONADDR0 */

/* Register ECCPOISONADDR1 */
/* ECC Data Poisoning Address Register 1. */
// #define ECCPOISONADDR1 (REGB_DDRC_CH0_BaseAddress + 0x64c)
#define ECCPOISONADDR1_RegisterSize 32
#define ECCPOISONADDR1_RegisterResetValue 0x0
#define ECCPOISONADDR1_RegisterResetMask 0xffffffff

/* Register Field information for ECCPOISONADDR1 */

/* Register ECCPOISONADDR1 field ecc_poison_row */
/* Row address for ECC poisoning. This is 18-bits wide in configurations with DDR4 support and 16-bits in all other configurations. */
#define ECCPOISONADDR1_ecc_poison_row_BitAddressOffset 0
#define ECCPOISONADDR1_ecc_poison_row_RegisterSize 18

/* Register ECCPOISONADDR1 field ecc_poison_bank */
/* Bank address for ECC poisoning */
#define ECCPOISONADDR1_ecc_poison_bank_BitAddressOffset 24
#define ECCPOISONADDR1_ecc_poison_bank_RegisterSize 3

/* Register ECCPOISONADDR1 field ecc_poison_bg */
/* Bank Group address for ECC poisoning */
#define ECCPOISONADDR1_ecc_poison_bg_BitAddressOffset 28
#define ECCPOISONADDR1_ecc_poison_bg_RegisterSize 2

/* End of Register Definition for ECCPOISONADDR1 */

/* Register ADVECCINDEX */
/* Advanced ECC Index Register */
// #define ADVECCINDEX (REGB_DDRC_CH0_BaseAddress + 0x650)
#define ADVECCINDEX_RegisterSize 32
#define ADVECCINDEX_RegisterResetValue 0x0
#define ADVECCINDEX_RegisterResetMask 0xffffffff

/* Register Field information for ADVECCINDEX */

/* Register ADVECCINDEX field ecc_syndrome_sel */
/* Selector of which DRAM beat data output to ECCCSYN0/1/2 as well as ECCUCSYN.

  In Advanced ECC, the syndrome consist of number of DRAM beats. This register select which beats of data will be output to ECCCSYN0/1/2 and ECCUCSYN0/1/2 registers. */
#define ADVECCINDEX_ecc_syndrome_sel_BitAddressOffset 0
#define ADVECCINDEX_ecc_syndrome_sel_RegisterSize 3

/* Register ADVECCINDEX field ecc_err_symbol_sel */
/* Selector of which error symbol's status output to ADVECCSTAT.advecc_err_symbol_pos and advecc_err_symbol_bits. The default is first error symbol.

  The value must be less than ADVECCSTAT.advecc_num_err_symbol. */
#define ADVECCINDEX_ecc_err_symbol_sel_BitAddressOffset 3
#define ADVECCINDEX_ecc_err_symbol_sel_RegisterSize 2

/* Register ADVECCINDEX field ecc_poison_beats_sel */
/* Selector of which DRAM beat's poison pattern will be set by ECCPOISONPAT0/1/2 registers. 
 
  For frequency ratio 1:2 mode, 4 DRAM beats can be poisoned. Set ecc_poison_beats_sel from 0~3 to set 1st to 4th beat's poison pattern.

  The other value is reserved. */
#define ADVECCINDEX_ecc_poison_beats_sel_BitAddressOffset 5
#define ADVECCINDEX_ecc_poison_beats_sel_RegisterSize 4

/* End of Register Definition for ADVECCINDEX */

/* Register ECCPOISONPAT0 */
/* ECC Poison Pattern 0 Register */
// #define ECCPOISONPAT0 (REGB_DDRC_CH0_BaseAddress + 0x658)
#define ECCPOISONPAT0_RegisterSize 32
#define ECCPOISONPAT0_RegisterResetValue 0x0
#define ECCPOISONPAT0_RegisterResetMask 0xffffffff

/* Register Field information for ECCPOISONPAT0 */

/* Register ECCPOISONPAT0 field ecc_poison_data_31_0 */
/* Indicates the poison pattern for DRAM data[31:0].
  Settings this bit to 1 indicate poison (invert) corresponding DRAM bit.

  It is indirect register. Selector is ADVECCINDEX.ecc_poison_beats_sel. */
#define ECCPOISONPAT0_ecc_poison_data_31_0_BitAddressOffset 0
#define ECCPOISONPAT0_ecc_poison_data_31_0_RegisterSize 32

/* End of Register Definition for ECCPOISONPAT0 */

/* Register ECCPOISONPAT2 */
/* ECC Poison Pattern 2 Register */
// #define ECCPOISONPAT2 (REGB_DDRC_CH0_BaseAddress + 0x660)
#define ECCPOISONPAT2_RegisterSize 32
#define ECCPOISONPAT2_RegisterResetValue 0x0
#define ECCPOISONPAT2_RegisterResetMask 0xffffffff

/* Register Field information for ECCPOISONPAT2 */

/* Register ECCPOISONPAT2 field ecc_poison_data_71_64 */
/* Indicates the poison pattern for DRAM data[71:64].
 
  Setting this bit to 1 indicates poison (invert) corresponding DRAM bit.

  It is indirect register. Selector is ADVECCINDEX.ecc_poison_beats_sel. */
#define ECCPOISONPAT2_ecc_poison_data_71_64_BitAddressOffset 0
#define ECCPOISONPAT2_ecc_poison_data_71_64_RegisterSize 8

/* End of Register Definition for ECCPOISONPAT2 */

/* Register ECCAPSTAT */
/* Address protection within ECC Status Register */
// #define ECCAPSTAT (REGB_DDRC_CH0_BaseAddress + 0x664)
#define ECCAPSTAT_RegisterSize 32
#define ECCAPSTAT_RegisterResetValue 0x0
#define ECCAPSTAT_RegisterResetMask 0xffffffff

/* Register Field information for ECCAPSTAT */

/* Register ECCAPSTAT field ecc_ap_err */
/* Indicates the number of ECC errors (correctable/uncorrectable) within one burst exceeded the threshold.(ECCCFG0.ecc_ap_err_threshold) */
#define ECCAPSTAT_ecc_ap_err_BitAddressOffset 0
#define ECCAPSTAT_ecc_ap_err_RegisterSize 1

/* End of Register Definition for ECCAPSTAT */

/* Register OCPARCFG0 */
/* On-Chip Parity Configuration Register 0 */
// #define OCPARCFG0 (REGB_DDRC_CH0_BaseAddress + 0x680)
#define OCPARCFG0_RegisterSize 32
#define OCPARCFG0_RegisterResetValue 0xb03032
#define OCPARCFG0_RegisterResetMask 0xffffffff

/* Register Field information for OCPARCFG0 */

/* Register OCPARCFG0 field oc_parity_en */
/* Parity enable register. Enables On-Chip parity for all interfaces. */
#define OCPARCFG0_oc_parity_en_BitAddressOffset 0
#define OCPARCFG0_oc_parity_en_RegisterSize 1

/* Register OCPARCFG0 field oc_parity_type */
/* Parity type:  
  - 0: Even parity
  - 1: Odd parity */
#define OCPARCFG0_oc_parity_type_BitAddressOffset 1
#define OCPARCFG0_oc_parity_type_RegisterSize 1

/* Register OCPARCFG0 field par_wdata_err_intr_en */
/* Enables write data interrupt generation (par_wdata_err_intr) upon detection of parity error at the AXI or DFI interface. */
#define OCPARCFG0_par_wdata_err_intr_en_BitAddressOffset 4
#define OCPARCFG0_par_wdata_err_intr_en_RegisterSize 1

/* Register OCPARCFG0 field par_wdata_slverr_en */
/* Enables SLVERR generation on write response when write data parity error is detected at the AXI interface. */
#define OCPARCFG0_par_wdata_slverr_en_BitAddressOffset 5
#define OCPARCFG0_par_wdata_slverr_en_RegisterSize 1

/* Register OCPARCFG0 field par_wdata_err_intr_clr */
/* Interrupt clear bit for par_wdata_err_intr. DDRCTL automatically clears this bit. */
#define OCPARCFG0_par_wdata_err_intr_clr_BitAddressOffset 6
#define OCPARCFG0_par_wdata_err_intr_clr_RegisterSize 1

/* Register OCPARCFG0 field par_wdata_err_intr_force */
/* Interrupt force bit for par_wdata_err_intr. DDRCTL automatically clears this bit. */
#define OCPARCFG0_par_wdata_err_intr_force_BitAddressOffset 7
#define OCPARCFG0_par_wdata_err_intr_force_RegisterSize 1

/* Register OCPARCFG0 field par_rdata_slverr_en */
/* Enables SLVERR generation on read response when read data parity error is detected at the AXI interface. */
#define OCPARCFG0_par_rdata_slverr_en_BitAddressOffset 12
#define OCPARCFG0_par_rdata_slverr_en_RegisterSize 1

/* Register OCPARCFG0 field par_rdata_err_intr_en */
/* Enables interrupt generation, if set to 1, for all ports, on signal par_rdata_err_intr_n upon detection of parity error at the AXI interface. */
#define OCPARCFG0_par_rdata_err_intr_en_BitAddressOffset 13
#define OCPARCFG0_par_rdata_err_intr_en_RegisterSize 1

/* Register OCPARCFG0 field par_rdata_err_intr_clr */
/* Interrupt clear bit for par_rdata_err_intr. DDRCTL automatically clears this bit. */
#define OCPARCFG0_par_rdata_err_intr_clr_BitAddressOffset 14
#define OCPARCFG0_par_rdata_err_intr_clr_RegisterSize 1

/* Register OCPARCFG0 field par_rdata_err_intr_force */
/* Interrupt force bit for all par_rdata_err_intr_n and par_rdata_in_err_ecc_intr (Inline-ECC only). DDRCTL automatically clears this bit. */
#define OCPARCFG0_par_rdata_err_intr_force_BitAddressOffset 15
#define OCPARCFG0_par_rdata_err_intr_force_RegisterSize 1

/* Register OCPARCFG0 field par_addr_slverr_en */
/* Enables SLVERR generation on read response or write response when address parity error is detected at the AXI interface. */
#define OCPARCFG0_par_addr_slverr_en_BitAddressOffset 20
#define OCPARCFG0_par_addr_slverr_en_RegisterSize 1

/* Register OCPARCFG0 field par_waddr_err_intr_en */
/* Enables interrupt generation, if set to 1, for all ports, on signal par_waddr_err_intr_n upon detection of parity error on the AXI interface. */
#define OCPARCFG0_par_waddr_err_intr_en_BitAddressOffset 21
#define OCPARCFG0_par_waddr_err_intr_en_RegisterSize 1

/* Register OCPARCFG0 field par_waddr_err_intr_clr */
/* Interrupt clear bit for all par_waddr_err_intr. DDRCTL automatically clears this bit. */
#define OCPARCFG0_par_waddr_err_intr_clr_BitAddressOffset 22
#define OCPARCFG0_par_waddr_err_intr_clr_RegisterSize 1

/* Register OCPARCFG0 field par_raddr_err_intr_en */
/* Enables interrupt generation, if set to 1, for all ports, on signal par_raddr_err_intr_n upon detection of parity error on the AXI interface. */
#define OCPARCFG0_par_raddr_err_intr_en_BitAddressOffset 23
#define OCPARCFG0_par_raddr_err_intr_en_RegisterSize 1

/* Register OCPARCFG0 field par_raddr_err_intr_clr */
/* Interrupt clear bit for all par_raddr_err_intr. DDRCTL automatically clears this bit. */
#define OCPARCFG0_par_raddr_err_intr_clr_BitAddressOffset 24
#define OCPARCFG0_par_raddr_err_intr_clr_RegisterSize 1

/* Register OCPARCFG0 field par_waddr_err_intr_force */
/* Interrupt force bit for all par_waddr_err_intr. DDRCTL automatically clears this bit. */
#define OCPARCFG0_par_waddr_err_intr_force_BitAddressOffset 25
#define OCPARCFG0_par_waddr_err_intr_force_RegisterSize 1

/* Register OCPARCFG0 field par_raddr_err_intr_force */
/* Interrupt force bit for all par_raddr_err_intr. DDRCTL automatically clears this bit. */
#define OCPARCFG0_par_raddr_err_intr_force_BitAddressOffset 26
#define OCPARCFG0_par_raddr_err_intr_force_RegisterSize 1

/* End of Register Definition for OCPARCFG0 */

/* Register OCPARCFG1 */
/* On-Chip Parity Configuration Register 1 */
// #define OCPARCFG1 (REGB_DDRC_CH0_BaseAddress + 0x684)
#define OCPARCFG1_RegisterSize 32
#define OCPARCFG1_RegisterResetValue 0x0
#define OCPARCFG1_RegisterResetMask 0xffffffff

/* Register Field information for OCPARCFG1 */

/* Register OCPARCFG1 field par_poison_en */
/* Enables on-chip parity poisoning on the data interfaces. */
#define OCPARCFG1_par_poison_en_BitAddressOffset 0
#define OCPARCFG1_par_poison_en_RegisterSize 1

/* Register OCPARCFG1 field par_poison_loc_rd_dfi */
/* Enables parity poisoning on read data at the DFI interface after the parity generation logic, and when MEMC_INLINE_ECC=1 enables poisoning of ECC word after the ECC encoder at the write data interface at the DFI. */
#define OCPARCFG1_par_poison_loc_rd_dfi_BitAddressOffset 2
#define OCPARCFG1_par_poison_loc_rd_dfi_RegisterSize 1

/* Register OCPARCFG1 field par_poison_loc_rd_iecc_type */
/* Selects which parity to poison at the DFI when inline ECC is enabled. If this register is set to 0, parity error is injected on the first read data going through the ECC path; if this register is set to 1, parity error is injected on the first read data going through the data path. */
#define OCPARCFG1_par_poison_loc_rd_iecc_type_BitAddressOffset 3
#define OCPARCFG1_par_poison_loc_rd_iecc_type_RegisterSize 1

/* Register OCPARCFG1 field par_poison_loc_rd_port */
/* Enables parity poisoning on read data at the AXI interface after the parity check logic. The value specifies the binary encoded port number of the AXI interface to be injected with parity error. Error can be injected to one port at a time. An error injected here is not logged and does not trigger SLVERR or interrupt by the controller. */
#define OCPARCFG1_par_poison_loc_rd_port_BitAddressOffset 4
#define OCPARCFG1_par_poison_loc_rd_port_RegisterSize 4

/* Register OCPARCFG1 field par_poison_loc_wr_port */
/* Enables parity poisoning on write data at the AXI interface before the input parity check logic. The value specifies the binary encoded port number of the AXI interface to be injected with parity error. */
#define OCPARCFG1_par_poison_loc_wr_port_BitAddressOffset 8
#define OCPARCFG1_par_poison_loc_wr_port_RegisterSize 4

/* End of Register Definition for OCPARCFG1 */

/* Register OCPARSTAT0 */
/* On-Chip Parity Status Register 0 */
// #define OCPARSTAT0 (REGB_DDRC_CH0_BaseAddress + 0x688)
#define OCPARSTAT0_RegisterSize 32
#define OCPARSTAT0_RegisterResetValue 0x0
#define OCPARSTAT0_RegisterResetMask 0xffffffff

/* Register Field information for OCPARSTAT0 */

/* Register OCPARSTAT0 field par_waddr_err_intr_0 */
/* Write address parity error interrupt for port 0. This interrupt is asserted when an on-chip write address parity error occurred on the corresponding AXI port's write address channel. */
#define OCPARSTAT0_par_waddr_err_intr_0_BitAddressOffset 0
#define OCPARSTAT0_par_waddr_err_intr_0_RegisterSize 1

/* Register OCPARSTAT0 field par_waddr_err_intr_1 */
/* Write address parity error interrupt for port 1. This interrupt is asserted when an on-chip write address parity error occurred on the corresponding AXI port's write address channel. */
#define OCPARSTAT0_par_waddr_err_intr_1_BitAddressOffset 1
#define OCPARSTAT0_par_waddr_err_intr_1_RegisterSize 1

/* Register OCPARSTAT0 field par_waddr_err_intr_2 */
/* Write address parity error interrupt for port 2. This interrupt is asserted when an on-chip write address parity error occurred on the corresponding AXI port's write address channel. */
#define OCPARSTAT0_par_waddr_err_intr_2_BitAddressOffset 2
#define OCPARSTAT0_par_waddr_err_intr_2_RegisterSize 1

/* Register OCPARSTAT0 field par_waddr_err_intr_3 */
/* Write address parity error interrupt for port 3. This interrupt is asserted when an on-chip write address parity error occurred on the corresponding AXI port's write address channel. */
#define OCPARSTAT0_par_waddr_err_intr_3_BitAddressOffset 3
#define OCPARSTAT0_par_waddr_err_intr_3_RegisterSize 1

/* Register OCPARSTAT0 field par_raddr_err_intr_0 */
/* Read address parity error interrupt for port 0. This interrupt is asserted when an on-chip read address parity error occurred on the corresponding AXI port's read address channel. */
#define OCPARSTAT0_par_raddr_err_intr_0_BitAddressOffset 16
#define OCPARSTAT0_par_raddr_err_intr_0_RegisterSize 1

/* Register OCPARSTAT0 field par_raddr_err_intr_1 */
/* Read address parity error interrupt for port 1. This interrupt is asserted when an on-chip read address parity error occurred on the corresponding AXI port's read address channel. */
#define OCPARSTAT0_par_raddr_err_intr_1_BitAddressOffset 17
#define OCPARSTAT0_par_raddr_err_intr_1_RegisterSize 1

/* Register OCPARSTAT0 field par_raddr_err_intr_2 */
/* Read address parity error interrupt for port 2. This interrupt is asserted when an on-chip read address parity error occurred on the corresponding AXI port's read address channel. */
#define OCPARSTAT0_par_raddr_err_intr_2_BitAddressOffset 18
#define OCPARSTAT0_par_raddr_err_intr_2_RegisterSize 1

/* Register OCPARSTAT0 field par_raddr_err_intr_3 */
/* Read address parity error interrupt for port 3. This interrupt is asserted when an on-chip read address parity error occurred on the corresponding AXI port's read address channel. */
#define OCPARSTAT0_par_raddr_err_intr_3_BitAddressOffset 19
#define OCPARSTAT0_par_raddr_err_intr_3_RegisterSize 1

/* End of Register Definition for OCPARSTAT0 */

/* Register OCPARSTAT1 */
/* On-Chip Parity Status Register 1 */
// #define OCPARSTAT1 (REGB_DDRC_CH0_BaseAddress + 0x68c)
#define OCPARSTAT1_RegisterSize 32
#define OCPARSTAT1_RegisterResetValue 0x0
#define OCPARSTAT1_RegisterResetMask 0xffffffff

/* Register Field information for OCPARSTAT1 */

/* Register OCPARSTAT1 field par_wdata_in_err_intr_0 */
/* Write data parity error interrupt on input for port 0. This interrupt is asserted when an on-chip write data parity error occurred on the corresponding AXI port's write data channel. Bit 0 corresponds to Port 0, and so on. Cleared by register par_wdata_err_intr_clr. */
#define OCPARSTAT1_par_wdata_in_err_intr_0_BitAddressOffset 0
#define OCPARSTAT1_par_wdata_in_err_intr_0_RegisterSize 1

/* Register OCPARSTAT1 field par_wdata_in_err_intr_1 */
/* Write data parity error interrupt on input for port 1. This interrupt is asserted when an on-chip write data parity error occurred on the corresponding AXI port's write data channel. Bit 0 corresponds to Port 0, and so on. Cleared by register par_wdata_err_intr_clr. */
#define OCPARSTAT1_par_wdata_in_err_intr_1_BitAddressOffset 1
#define OCPARSTAT1_par_wdata_in_err_intr_1_RegisterSize 1

/* Register OCPARSTAT1 field par_wdata_in_err_intr_2 */
/* Write data parity error interrupt on input for port 2. This interrupt is asserted when an on-chip write data parity error occurred on the corresponding AXI port's write data channel. Bit 0 corresponds to Port 0, and so on. Cleared by register par_wdata_err_intr_clr. */
#define OCPARSTAT1_par_wdata_in_err_intr_2_BitAddressOffset 2
#define OCPARSTAT1_par_wdata_in_err_intr_2_RegisterSize 1

/* Register OCPARSTAT1 field par_wdata_in_err_intr_3 */
/* Write data parity error interrupt on input for port 3. This interrupt is asserted when an on-chip write data parity error occurred on the corresponding AXI port's write data channel. Bit 0 corresponds to Port 0, and so on. Cleared by register par_wdata_err_intr_clr. */
#define OCPARSTAT1_par_wdata_in_err_intr_3_BitAddressOffset 3
#define OCPARSTAT1_par_wdata_in_err_intr_3_RegisterSize 1

/* Register OCPARSTAT1 field par_rdata_err_intr_0 */
/* Read data parity error interrupt for port 0. This interrupt is asserted when an on-chip read data parity error occurred on the corresponding AXI port's read data channel. Bit 0 corresponds to Port 0, and so on. Cleared by register par_rdata_err_intr_clr. */
#define OCPARSTAT1_par_rdata_err_intr_0_BitAddressOffset 16
#define OCPARSTAT1_par_rdata_err_intr_0_RegisterSize 1

/* Register OCPARSTAT1 field par_rdata_err_intr_1 */
/* Read data parity error interrupt for port 1. This interrupt is asserted when an on-chip read data parity error occurred on the corresponding AXI port's read data channel. Bit 0 corresponds to Port 0, and so on. Cleared by register par_rdata_err_intr_clr. */
#define OCPARSTAT1_par_rdata_err_intr_1_BitAddressOffset 17
#define OCPARSTAT1_par_rdata_err_intr_1_RegisterSize 1

/* Register OCPARSTAT1 field par_rdata_err_intr_2 */
/* Read data parity error interrupt for port 2. This interrupt is asserted when an on-chip read data parity error occurred on the corresponding AXI port's read data channel. Bit 0 corresponds to Port 0, and so on. Cleared by register par_rdata_err_intr_clr. */
#define OCPARSTAT1_par_rdata_err_intr_2_BitAddressOffset 18
#define OCPARSTAT1_par_rdata_err_intr_2_RegisterSize 1

/* Register OCPARSTAT1 field par_rdata_err_intr_3 */
/* Read data parity error interrupt for port 3. This interrupt is asserted when an on-chip read data parity error occurred on the corresponding AXI port's read data channel. Bit 0 corresponds to Port 0, and so on. Cleared by register par_rdata_err_intr_clr. */
#define OCPARSTAT1_par_rdata_err_intr_3_BitAddressOffset 19
#define OCPARSTAT1_par_rdata_err_intr_3_RegisterSize 1

/* End of Register Definition for OCPARSTAT1 */

/* Register OCPARSTAT2 */
/* On-Chip Parity Status Register 2 */
// #define OCPARSTAT2 (REGB_DDRC_CH0_BaseAddress + 0x690)
#define OCPARSTAT2_RegisterSize 32
#define OCPARSTAT2_RegisterResetValue 0x0
#define OCPARSTAT2_RegisterResetMask 0xffffffff

/* Register Field information for OCPARSTAT2 */

/* Register OCPARSTAT2 field par_wdata_out_err_intr */
/* Write data parity error interrupt on output. Cleared by register par_wdata_err_intr_clr. */
#define OCPARSTAT2_par_wdata_out_err_intr_BitAddressOffset 0
#define OCPARSTAT2_par_wdata_out_err_intr_RegisterSize 2

/* Register OCPARSTAT2 field par_rdata_in_err_ecc_intr */
/* Interrupt on ECC data going into inline ECC decoder. Cleared by par_rdata_err_intr_clr. */
#define OCPARSTAT2_par_rdata_in_err_ecc_intr_BitAddressOffset 4
#define OCPARSTAT2_par_rdata_in_err_ecc_intr_RegisterSize 1

/* End of Register Definition for OCPARSTAT2 */

/* Register OCSAPCFG0 */
/* On-Chip external SRAM Address Protection Configuration Register 0 */
// #define OCSAPCFG0 (REGB_DDRC_CH0_BaseAddress + 0x6b0)
#define OCSAPCFG0_RegisterSize 32
#define OCSAPCFG0_RegisterResetValue 0x0
#define OCSAPCFG0_RegisterResetMask 0xffffffff

/* Register Field information for OCSAPCFG0 */

/* Register OCSAPCFG0 field ocsap_par_en */
/* Enables On-Chip external SRAM address parity. */
#define OCSAPCFG0_ocsap_par_en_BitAddressOffset 0
#define OCSAPCFG0_ocsap_par_en_RegisterSize 1

/* Register OCSAPCFG0 field ocsap_poison_en */
/* Enables On-Chip external SRAM address poisoning. */
#define OCSAPCFG0_ocsap_poison_en_BitAddressOffset 8
#define OCSAPCFG0_ocsap_poison_en_RegisterSize 1

/* Register OCSAPCFG0 field wdataram_addr_poison_loc */
/* Selects wdataram address poisoning either for write address or read address.
 - 0 - Poison SRAM write address 
 - 1 - Poison SRAM read address */
#define OCSAPCFG0_wdataram_addr_poison_loc_BitAddressOffset 12
#define OCSAPCFG0_wdataram_addr_poison_loc_RegisterSize 1

/* Register OCSAPCFG0 field rdataram_addr_poison_loc */
/* Selects rdataram address poisoning either for write address or read address.
 - 0 - Poison SRAM write address 
 - 1 - Poison SRAM read address */
#define OCSAPCFG0_rdataram_addr_poison_loc_BitAddressOffset 13
#define OCSAPCFG0_rdataram_addr_poison_loc_RegisterSize 1

/* Register OCSAPCFG0 field wdataram_addr_poison_ctl */
/* Selects wdataram address bit position (binary encoded) for poisoning. 

  Note: The selected wdataram address bit position (binary encoded) shall be less than parameter value UMCTL2_WDATARAM_AW. 
 */
#define OCSAPCFG0_wdataram_addr_poison_ctl_BitAddressOffset 16
#define OCSAPCFG0_wdataram_addr_poison_ctl_RegisterSize 3

/* Register OCSAPCFG0 field rdataram_addr_poison_ctl */
/* Selects rdataram address bit position (binary encoded) for poisoning.

  Note: The selected rdataram address bit position (binary encoded) shall be less than parameter value UMCTL2_RDATARAM_AW.
 */
#define OCSAPCFG0_rdataram_addr_poison_ctl_BitAddressOffset 24
#define OCSAPCFG0_rdataram_addr_poison_ctl_RegisterSize 3

/* Register OCSAPCFG0 field rdataram_addr_poison_port */
/* The value specifies the binary encoded port number of the AXI interface for poisoning the associated RDATARAM address. Error can be injected to one port at a time. */
#define OCSAPCFG0_rdataram_addr_poison_port_BitAddressOffset 28
#define OCSAPCFG0_rdataram_addr_poison_port_RegisterSize 4

/* End of Register Definition for OCSAPCFG0 */

/* Register OCCAPCFG */
/* On-Chip command/Address Protection Configuration Register */
// #define OCCAPCFG (REGB_DDRC_CH0_BaseAddress + 0x780)
#define OCCAPCFG_RegisterSize 32
#define OCCAPCFG_RegisterResetValue 0x10000
#define OCCAPCFG_RegisterResetMask 0xffffffff

/* Register Field information for OCCAPCFG */

/* Register OCCAPCFG field occap_en */
/* On Chip Command/Address Path Protection (OCCAP) enable register. */
#define OCCAPCFG_occap_en_BitAddressOffset 0
#define OCCAPCFG_occap_en_RegisterSize 1

/* Register OCCAPCFG field occap_arb_intr_en */
/* Enables interrupt generation upon detection of OCCAP Arbiter errors. */
#define OCCAPCFG_occap_arb_intr_en_BitAddressOffset 16
#define OCCAPCFG_occap_arb_intr_en_RegisterSize 1

/* Register OCCAPCFG field occap_arb_intr_clr */
/* Interrupt clear bit for occap_arb_err_intr and occap_arb_cmp_poison_complete. DDRCTL automatically clears this bit. */
#define OCCAPCFG_occap_arb_intr_clr_BitAddressOffset 17
#define OCCAPCFG_occap_arb_intr_clr_RegisterSize 1

/* Register OCCAPCFG field occap_arb_intr_force */
/* Interrupt force bit for occap_arb_err_intr, setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define OCCAPCFG_occap_arb_intr_force_BitAddressOffset 18
#define OCCAPCFG_occap_arb_intr_force_RegisterSize 1

/* Register OCCAPCFG field occap_arb_cmp_poison_seq */
/* Enables poisoning for compare logic inside XPI. Poisoning inverts all bits coming from the duplicated modules before the XOR comparators one output at the time per each comparator. DDRCTL automatically clears this bit. */
#define OCCAPCFG_occap_arb_cmp_poison_seq_BitAddressOffset 24
#define OCCAPCFG_occap_arb_cmp_poison_seq_RegisterSize 1

/* Register OCCAPCFG field occap_arb_cmp_poison_parallel */
/* Enables full poisoning for compare logic inside XPI. Poisoning inverts all bits of all outputs coming from the duplicated modules before the XOR comparators together. DDRCTL automatically clears this bit. */
#define OCCAPCFG_occap_arb_cmp_poison_parallel_BitAddressOffset 25
#define OCCAPCFG_occap_arb_cmp_poison_parallel_RegisterSize 1

/* Register OCCAPCFG field occap_arb_cmp_poison_err_inj */
/* Enable error injection in the poisoning of OCCAP Arbiter logic

Injects error into poisoning logic (either parallel or seq) such that XOR logic for one signal is not poisoned when expected.

If set, it allows ability to corrupt the following register fields.
 - 1'b0: OCCAPSTAT.occap_arb_cmp_poison_parallel/seq_err=0
 - 1'b1: OCCAPSTAT.occap_arb_cmp_poison_parallel/seq_err=1

Do not change value in same APB write as setting of occap_arb_cmp_poison_parallel/_seq
 */
#define OCCAPCFG_occap_arb_cmp_poison_err_inj_BitAddressOffset 26
#define OCCAPCFG_occap_arb_cmp_poison_err_inj_RegisterSize 1

/* Register OCCAPCFG field occap_arb_raq_poison_en */
/* Enables poisoning for the Read Address Queues (RAQ) inside each XPI. Poisoning inverts all parity bits generated by the parity generator. Error will be flagged as soon as the first RAQ is read. This register is not cleared automatically and must be reprogrammed to 0 at the end of the operation. */
#define OCCAPCFG_occap_arb_raq_poison_en_BitAddressOffset 27
#define OCCAPCFG_occap_arb_raq_poison_en_RegisterSize 1

/* End of Register Definition for OCCAPCFG */

/* Register OCCAPSTAT */
/* On-Chip command/Address Protection Status Register */
// #define OCCAPSTAT (REGB_DDRC_CH0_BaseAddress + 0x784)
#define OCCAPSTAT_RegisterSize 32
#define OCCAPSTAT_RegisterResetValue 0x0
#define OCCAPSTAT_RegisterResetMask 0xffffffff

/* Register Field information for OCCAPSTAT */

/* Register OCCAPSTAT field occap_arb_err_intr */
/* OCCAP Arbiter error interrupt status. Register cleared by OCCAPCFG.occap_arb_intr_clr. */
#define OCCAPSTAT_occap_arb_err_intr_BitAddressOffset 16
#define OCCAPSTAT_occap_arb_err_intr_RegisterSize 1

/* Register OCCAPSTAT field occap_arb_cmp_poison_complete */
/* OCCAP ARB comparator poisoning complete interrupt status. Register cleared by OCCAPCFG.occap_arb_intr_clr. */
#define OCCAPSTAT_occap_arb_cmp_poison_complete_BitAddressOffset 17
#define OCCAPSTAT_occap_arb_cmp_poison_complete_RegisterSize 1

/* Register OCCAPSTAT field occap_arb_cmp_poison_seq_err */
/* Error when occap_arb_cmp_poison_en was active due to incorrect no. of errors being occurring. Internal logic checks that the correct number of errors detected while poisoning one output at the time occurred for occap_arb_cmp_poison_en. It checks for error on one output at the time. Register is valid when occap_arb_cmp_poison_complete=1. */
#define OCCAPSTAT_occap_arb_cmp_poison_seq_err_BitAddressOffset 24
#define OCCAPSTAT_occap_arb_cmp_poison_seq_err_RegisterSize 1

/* Register OCCAPSTAT field occap_arb_cmp_poison_parallel_err */
/* Error when occap_arb_cmp_poison_full_en was active due to incorrect no. of errors being occurring. Internal logic checks the number of errors detected while poisoning occurred for occap_arb_cmp_poison_full_en. It checks for error on all of the the corresponding XOR outputs. If multi-bit, checks also that all XOR bits are set. Register is valid when occap_arb_cmp_poison_complete=1. */
#define OCCAPSTAT_occap_arb_cmp_poison_parallel_err_BitAddressOffset 25
#define OCCAPSTAT_occap_arb_cmp_poison_parallel_err_RegisterSize 1

/* End of Register Definition for OCCAPSTAT */

/* Register OCCAPCFG1 */
/* On-Chip command/Address Protection Configuration Register 1 */
// #define OCCAPCFG1 (REGB_DDRC_CH0_BaseAddress + 0x788)
#define OCCAPCFG1_RegisterSize 32
#define OCCAPCFG1_RegisterResetValue 0x10001
#define OCCAPCFG1_RegisterResetMask 0xffffffff

/* Register Field information for OCCAPCFG1 */

/* Register OCCAPCFG1 field occap_ddrc_data_intr_en */
/* Enables interrupt generation on signal occap_ddrc_data_err_intr upon detection of OCCAP DDRC DATA errors. */
#define OCCAPCFG1_occap_ddrc_data_intr_en_BitAddressOffset 0
#define OCCAPCFG1_occap_ddrc_data_intr_en_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_data_intr_clr */
/* Interrupt clear bit for occap_ddrc_data_err_intr. DDRCTL automatically clears this bit. */
#define OCCAPCFG1_occap_ddrc_data_intr_clr_BitAddressOffset 1
#define OCCAPCFG1_occap_ddrc_data_intr_clr_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_data_intr_force */
/* Interrupt force bit for occap_ddrc_data_err_intr, setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define OCCAPCFG1_occap_ddrc_data_intr_force_BitAddressOffset 2
#define OCCAPCFG1_occap_ddrc_data_intr_force_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_data_poison_seq */
/* Enables poisoning of OCCAP DDRC DATA logic for all parts of comparison logic, in sequence.

  Poisons comparison logic for one core_ddrc_core_clk cycle by inverting all bits of a signal to XOR logic. All signals of instance[0] of the duplicated modules are poisoned in parallel and checks if all signals were poisoned correctly.

  If this is not the case, this is flagged by OCCAPSTAT1.occap_ddrc_data_poison_seq_err=1.

  DDRCTL automatically clears this bit. */
#define OCCAPCFG1_occap_ddrc_data_poison_seq_BitAddressOffset 8
#define OCCAPCFG1_occap_ddrc_data_poison_seq_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_data_poison_parallel */
/* Enables poisoning of OCCAP DDRC DATA logic for all parts of comparison logic, in parallel.

  Poisons comparison logic for one core_ddrc_core_clk cycle by inverting all bits of a signal to XOR logic. All signals of instance[0] of the duplicated modules are poisoned in parallel and checks if all signals were poisoned correctly.

  If this is not the case, this is flagged by OCCAPSTAT1.occap_ddrc_data_poison_parallel_err=1.
 
  DDRCTL automatically clears this bit. */
#define OCCAPCFG1_occap_ddrc_data_poison_parallel_BitAddressOffset 9
#define OCCAPCFG1_occap_ddrc_data_poison_parallel_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_data_poison_err_inj */
/* Enable error injection in the poisoning of OCCAP DDRC DATA logic

Injects error into poisoning logic (either parallel or seq) such that XOR logic for one signal is not poisoned when expected.

If set, it allows ability to corrupt the following register fields.
 - 1'b0: OCCAPSTAT1.occap_ddrc_data_poison_parallel/seq_err=0
 - 1'b1: OCCAPSTAT1.occap_ddrc_data_poison_parallel/seq_err=1

Do not change value in same APB write as setting of occap_ddrc_data_poison_parallel/_seq
 */
#define OCCAPCFG1_occap_ddrc_data_poison_err_inj_BitAddressOffset 10
#define OCCAPCFG1_occap_ddrc_data_poison_err_inj_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_ctrl_intr_en */
/* Enables interrupt generation on signal occap_ddrc_ctrl_err_intr upon detection of OCCAP DDRC CTRL errors. */
#define OCCAPCFG1_occap_ddrc_ctrl_intr_en_BitAddressOffset 16
#define OCCAPCFG1_occap_ddrc_ctrl_intr_en_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_ctrl_intr_clr */
/* Interrupt clear bit for occap_ddrc_ctrl_err_intr. DDRCTL automatically clears this bit. */
#define OCCAPCFG1_occap_ddrc_ctrl_intr_clr_BitAddressOffset 17
#define OCCAPCFG1_occap_ddrc_ctrl_intr_clr_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_ctrl_intr_force */
/* Interrupt force bit for occap_ddrc_ctrl_err_intr, setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define OCCAPCFG1_occap_ddrc_ctrl_intr_force_BitAddressOffset 18
#define OCCAPCFG1_occap_ddrc_ctrl_intr_force_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_ctrl_poison_seq */
/* Enables poisoning of OCCAP DDRC CTRL logic for all parts of comparison logic, in sequence. Poisons comparison logic for one core_ddrc_core_clk cycle by inverting a ddrc_ctrl[0]'s signal to XOR logic. ddrc_ctrl[1] related signals are never poisoned. Each signal from ddrc_ctrl[0] is poisoned in series and checks in turn, that each signal was poisoned correctly. 

  If this is not the case, this is flagged by OCCAPSTAT1.occap_ddrc_ctrl_poison_seq_err=1. 

  DDRCTL automatically clears this bit. */
#define OCCAPCFG1_occap_ddrc_ctrl_poison_seq_BitAddressOffset 24
#define OCCAPCFG1_occap_ddrc_ctrl_poison_seq_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_ctrl_poison_parallel */
/* Enables poisoning of OCCAP DDRC CTRL logic for all parts of comparison logic, in parallel. Poisons comparison logic for one core_ddrc_core_clk cycle by inverting a ddrc_ctrl[0]'s signal to XOR logic. ddrc_ctrl[1] related signals are never poisoned. All signals are poisoned in parallel and checks if all signals were poisoned correctly. 

  If this is not the case, this is flagged by OCCAPSTAT1.occap_ddrc_ctrl_poison_parallel_err=1. 

  DDRCTL automatically clears this bit. */
#define OCCAPCFG1_occap_ddrc_ctrl_poison_parallel_BitAddressOffset 25
#define OCCAPCFG1_occap_ddrc_ctrl_poison_parallel_RegisterSize 1

/* Register OCCAPCFG1 field occap_ddrc_ctrl_poison_err_inj */
/* Enable error injection in the poisoning of OCCAP DDRC CTRL logic

Injects error into poisoning logic (either parallel or seq) such that XOR logic for one signal is not poisoned when expected.

If set, it allows ability to corrupt the following register fields.
 - 1'b0: OCCAPSTAT1.occap_ddrc_ctrl_poison_parallel/seq_err=0
 - 1'b1: OCCAPSTAT1.occap_ddrc_ctrl_poison_parallel/seq_err=1
 Do not change value in same APB write as setting of occap_ddrc_ctrl_poison_parallel/_seq
 */
#define OCCAPCFG1_occap_ddrc_ctrl_poison_err_inj_BitAddressOffset 26
#define OCCAPCFG1_occap_ddrc_ctrl_poison_err_inj_RegisterSize 1

/* End of Register Definition for OCCAPCFG1 */

/* Register OCCAPSTAT1 */
/* On-Chip command/Address Protection Status Register 1 */
// #define OCCAPSTAT1 (REGB_DDRC_CH0_BaseAddress + 0x78c)
#define OCCAPSTAT1_RegisterSize 32
#define OCCAPSTAT1_RegisterResetValue 0x0
#define OCCAPSTAT1_RegisterResetMask 0xffffffff

/* Register Field information for OCCAPSTAT1 */

/* Register OCCAPSTAT1 field occap_ddrc_data_err_intr */
/* OCCAP DDRC DATA error interrupt status. 

 Register cleared by OCCAPCFG1.occap_ddrc_data_err_intr_clr. */
#define OCCAPSTAT1_occap_ddrc_data_err_intr_BitAddressOffset 0
#define OCCAPSTAT1_occap_ddrc_data_err_intr_RegisterSize 1

/* Register OCCAPSTAT1 field occap_ddrc_data_poison_complete */
/* OCCAP DDRC DATA poisoning complete interrupt status. 

 Register cleared by OCCAPCFG1.occap_ddrc_data_err_intr_clr. */
#define OCCAPSTAT1_occap_ddrc_data_poison_complete_BitAddressOffset 1
#define OCCAPSTAT1_occap_ddrc_data_poison_complete_RegisterSize 1

/* Register OCCAPSTAT1 field occap_ddrc_data_poison_seq_err */
/* Error when occap_ddrc_data_poison_seq was active due to incorrect no. of errors being occurring. Internal logic checks the number of errors detected while poisoning occurred for occap_ddrc_data_poison_seq. It checks for error on all of the corresponding XOR outputs. It checks each XOR sequentially. This is cleared when OCCAPCFG1.occap_ddrc_data_poison_seq=0 occurs. */
#define OCCAPSTAT1_occap_ddrc_data_poison_seq_err_BitAddressOffset 8
#define OCCAPSTAT1_occap_ddrc_data_poison_seq_err_RegisterSize 1

/* Register OCCAPSTAT1 field occap_ddrc_data_poison_parallel_err */
/* Error when occap_ddrc_data_poison_parallel was active due to incorrect no. of errors being occurring. Internal logic checks the number of errors detected while poisoning occurred for occap_ddrc_data_poison_parallel. It checks for error on all of the the corresponding XOR outputs. If multi-bit, checks also that all XOR bits are set. It checks all XOR in parallel. This is cleared when OCCAPCFG1.occap_ddrc_data_poison_parallel=0 occurs. */
#define OCCAPSTAT1_occap_ddrc_data_poison_parallel_err_BitAddressOffset 9
#define OCCAPSTAT1_occap_ddrc_data_poison_parallel_err_RegisterSize 1

/* Register OCCAPSTAT1 field occap_ddrc_ctrl_err_intr */
/* OCCAP DDRC CTRL error interrupt status. 

 Register cleared by OCCAPCFG1.occap_ddrc_ctrl_err_intr_clr. */
#define OCCAPSTAT1_occap_ddrc_ctrl_err_intr_BitAddressOffset 16
#define OCCAPSTAT1_occap_ddrc_ctrl_err_intr_RegisterSize 1

/* Register OCCAPSTAT1 field occap_ddrc_ctrl_poison_complete */
/* OCCAP DDRC CTRL poisoning complete interrupt status. 

 Register cleared by OCCAPCFG1.occap_ddrc_ctrl_err_intr_clr. */
#define OCCAPSTAT1_occap_ddrc_ctrl_poison_complete_BitAddressOffset 17
#define OCCAPSTAT1_occap_ddrc_ctrl_poison_complete_RegisterSize 1

/* Register OCCAPSTAT1 field occap_ddrc_ctrl_poison_seq_err */
/* Error when occap_ddrc_ctrl_poison_seq was active due to incorrect no. of errors being occurring. Internal logic checks the number of errors detected while poisoning occurred for occap_ddrc_ctrl_poison_seq. It checks for error on all of the corresponding XOR outputs. It checks each XOR sequentially. 

 Register is valid only when occap_ddrc_ctrl_cmp_poison_complete=1. */
#define OCCAPSTAT1_occap_ddrc_ctrl_poison_seq_err_BitAddressOffset 24
#define OCCAPSTAT1_occap_ddrc_ctrl_poison_seq_err_RegisterSize 1

/* Register OCCAPSTAT1 field occap_ddrc_ctrl_poison_parallel_err */
/* Error when occap_ddrc_ctrl_poison_parallel was active due to incorrect no. of errors being occurring. Internal logic checks the number of errors detected while poisoning occurred for occap_ddrc_ctrl_poison_parallel. It checks for error on all of the the corresponding XOR outputs. If multi-bit, checks also that all XOR bits are set. It checks all XOR in parallel. 

 Register is valid only when occap_ddrc_ctrl_cmp_poison_complete=1. */
#define OCCAPSTAT1_occap_ddrc_ctrl_poison_parallel_err_BitAddressOffset 25
#define OCCAPSTAT1_occap_ddrc_ctrl_poison_parallel_err_RegisterSize 1

/* End of Register Definition for OCCAPSTAT1 */

/* Register CRCPARCTL0 */
/* CRC Parity Control Register0 */
// #define CRCPARCTL0 (REGB_DDRC_CH0_BaseAddress + 0x800)
#define CRCPARCTL0_RegisterSize 32
#define CRCPARCTL0_RegisterResetValue 0x0
#define CRCPARCTL0_RegisterResetMask 0xffffffff

/* Register Field information for CRCPARCTL0 */

/* Register CRCPARCTL0 field dfi_alert_err_int_en */
/* Interrupt enable bit for DFI alert error. If this bit is set, any parity/CRC error detected on the dfi_alert_n input will result in an interrupt being set on CRCPARSTAT.dfi_alert_err_int. */
#define CRCPARCTL0_dfi_alert_err_int_en_BitAddressOffset 0
#define CRCPARCTL0_dfi_alert_err_int_en_RegisterSize 1

/* Register CRCPARCTL0 field dfi_alert_err_int_clr */
/* Interrupt clear bit for DFI alert error. If this bit is set, the alert error interrupt on CRCPARSTAT.dfi_alert_err_int will be cleared. DDRCTL automatically clears this bit. */
#define CRCPARCTL0_dfi_alert_err_int_clr_BitAddressOffset 1
#define CRCPARCTL0_dfi_alert_err_int_clr_RegisterSize 1

/* Register CRCPARCTL0 field dfi_alert_err_cnt_clr */
/* DFI alert error count clear. Clear bit for DFI alert error counter. Asserting this bit will clear the DFI alert error counter, CRCPARSTAT.dfi_alert_err_cnt. DDRCTL automatically clears this bit. */
#define CRCPARCTL0_dfi_alert_err_cnt_clr_BitAddressOffset 2
#define CRCPARCTL0_dfi_alert_err_cnt_clr_RegisterSize 1

/* Register CRCPARCTL0 field rd_crc_err_max_reached_int_en */
/* Interrupt enable bit for Read CRC error. If this bit is set. */
#define CRCPARCTL0_rd_crc_err_max_reached_int_en_BitAddressOffset 20
#define CRCPARCTL0_rd_crc_err_max_reached_int_en_RegisterSize 1

/* Register CRCPARCTL0 field rd_crc_err_max_reached_int_clr */
/* Interrupt clear bit for RDCRCERRSTAT0.rd_crc_err_max_reached_int_nibble. If this bit set, Read CRC error interrupt will be cleared. DDRCTL automatically clears this bit.
 It is recommended to clear CRCSTAT.rd_crc_err_cnt_nibble by CRCPARCTL0.rd_crc_err_cnt_clr before clearing rd_crc_err_max_reached_int_nibble otherwise the interrupt is asserted again immediately. */
#define CRCPARCTL0_rd_crc_err_max_reached_int_clr_BitAddressOffset 21
#define CRCPARCTL0_rd_crc_err_max_reached_int_clr_RegisterSize 1

/* Register CRCPARCTL0 field rd_crc_err_cnt_clr */
/* Read CRC error count clear. If this bit set, Read CRC error count will be cleared. DDRCTL automatically clears this bit. */
#define CRCPARCTL0_rd_crc_err_cnt_clr_BitAddressOffset 22
#define CRCPARCTL0_rd_crc_err_cnt_clr_RegisterSize 1

/* End of Register Definition for CRCPARCTL0 */

/* Register CRCPARSTAT */
/* CRC Parity Status Register */
// #define CRCPARSTAT (REGB_DDRC_CH0_BaseAddress + 0x80c)
#define CRCPARSTAT_RegisterSize 32
#define CRCPARSTAT_RegisterResetValue 0x0
#define CRCPARSTAT_RegisterResetMask 0xffffffff

/* Register Field information for CRCPARSTAT */

/* Register CRCPARSTAT field dfi_alert_err_cnt */
/* DFI alert error count.
  If a parity/CRC error is detected on dfi_alert_n, this counter be incremented.  This is independent of the setting of CRCPARCTL0.dfi_alert_err_int_en.  It will saturate at 0xFFFF, and can be cleared by asserting CRCPARCTL0.dfi_alert_err_cnt_clr. */
#define CRCPARSTAT_dfi_alert_err_cnt_BitAddressOffset 0
#define CRCPARSTAT_dfi_alert_err_cnt_RegisterSize 16

/* Register CRCPARSTAT field dfi_alert_err_int */
/* DFI alert error interrupt.
  If a parity/CRC error is detected on dfi_alert_n, and the interrupt is enabled by CRCPARCTL0.dfi_alert_err_int_en, this interrupt bit will be set.  It will remain set until cleared by CRCPARCTL0.dfi_alert_err_int_clr */
#define CRCPARSTAT_dfi_alert_err_int_BitAddressOffset 16
#define CRCPARSTAT_dfi_alert_err_int_RegisterSize 1

/* End of Register Definition for CRCPARSTAT */

/* Register REGPARCFG */
/* Register Parity Configuration Register */
// #define REGPARCFG (REGB_DDRC_CH0_BaseAddress + 0x880)
#define REGPARCFG_RegisterSize 32
#define REGPARCFG_RegisterResetValue 0x2
#define REGPARCFG_RegisterResetMask 0xffffffff

/* Register Field information for REGPARCFG */

/* Register REGPARCFG field reg_par_en */
/* Register Parity enable register. */
#define REGPARCFG_reg_par_en_BitAddressOffset 0
#define REGPARCFG_reg_par_en_RegisterSize 1

/* Register REGPARCFG field reg_par_err_intr_en */
/* Enables interrupt generation, if set to 1, on signal reg_par_err_intr upon detection of register parity error. */
#define REGPARCFG_reg_par_err_intr_en_BitAddressOffset 1
#define REGPARCFG_reg_par_err_intr_en_RegisterSize 1

/* Register REGPARCFG field reg_par_err_intr_clr */
/* Interupt clear bit for reg_par_err_intr. DDRCTL automatically clears this bit. */
#define REGPARCFG_reg_par_err_intr_clr_BitAddressOffset 2
#define REGPARCFG_reg_par_err_intr_clr_RegisterSize 1

/* Register REGPARCFG field reg_par_err_intr_force */
/* Interrupt force bit for reg_par_err_intr, setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define REGPARCFG_reg_par_err_intr_force_BitAddressOffset 3
#define REGPARCFG_reg_par_err_intr_force_RegisterSize 1

/* Register REGPARCFG field reg_par_poison_en */
/* Enable Register Parity poisoning. */
#define REGPARCFG_reg_par_poison_en_BitAddressOffset 8
#define REGPARCFG_reg_par_poison_en_RegisterSize 1

/* End of Register Definition for REGPARCFG */

/* Register REGPARSTAT */
/* Register Parity Status Register */
// #define REGPARSTAT (REGB_DDRC_CH0_BaseAddress + 0x884)
#define REGPARSTAT_RegisterSize 32
#define REGPARSTAT_RegisterResetValue 0x0
#define REGPARSTAT_RegisterResetMask 0xffffffff

/* Register Field information for REGPARSTAT */

/* Register REGPARSTAT field reg_par_err_intr */
/* Interrupt asserted when Register Parity error is detected. Cleared by setting REGPARCFG.reg_par_err_intr_clr to 1. */
#define REGPARSTAT_reg_par_err_intr_BitAddressOffset 0
#define REGPARSTAT_reg_par_err_intr_RegisterSize 1

/* End of Register Definition for REGPARSTAT */

/* Register LNKECCCTL0 */
/* Link-ECC Control Register 0 */
// #define LNKECCCTL0 (REGB_DDRC_CH0_BaseAddress + 0x980)
#define LNKECCCTL0_RegisterSize 32
#define LNKECCCTL0_RegisterResetValue 0x0
#define LNKECCCTL0_RegisterResetMask 0xffffffff

/* Register Field information for LNKECCCTL0 */

/* Register LNKECCCTL0 field wr_link_ecc_enable */
/* Enable LPDDR5 Write Link ECC feature.
 - 0 - Disabel LPDDR5 Write Link ECC 
 - 1 - Enable LPDDR5 Write Link ECC 
 When non-LPDDR5 devices are used, this register must be set to 0. */
#define LNKECCCTL0_wr_link_ecc_enable_BitAddressOffset 0
#define LNKECCCTL0_wr_link_ecc_enable_RegisterSize 1

/* Register LNKECCCTL0 field rd_link_ecc_enable */
/* Enable LPDDR5 Read Link ECC feature.
 - 0 - Disabel LPDDR5 Read Link ECC 
 - 1 - Enable LPDDR5 Read Link ECC 
 When non-LPDDR5 devices are used, this register must be set to 0. */
#define LNKECCCTL0_rd_link_ecc_enable_BitAddressOffset 1
#define LNKECCCTL0_rd_link_ecc_enable_RegisterSize 1

/* End of Register Definition for LNKECCCTL0 */

/* Register LNKECCCTL1 */
/* Link-ECC Control Register 1 */
// #define LNKECCCTL1 (REGB_DDRC_CH0_BaseAddress + 0x984)
#define LNKECCCTL1_RegisterSize 32
#define LNKECCCTL1_RegisterResetValue 0x0
#define LNKECCCTL1_RegisterResetMask 0xffffffff

/* Register Field information for LNKECCCTL1 */

/* Register LNKECCCTL1 field rd_link_ecc_corr_intr_en */
/* Interrupt enable bit for Read Link-ECC correctable error. */
#define LNKECCCTL1_rd_link_ecc_corr_intr_en_BitAddressOffset 0
#define LNKECCCTL1_rd_link_ecc_corr_intr_en_RegisterSize 1

/* Register LNKECCCTL1 field rd_link_ecc_corr_intr_clr */
/* Clear Read Link-ECC correctable error interrupt.
 If this bit set, rd_linkecc_corr_err_intr will be cleared. LPDDRCTL automatically clears this bit. */
#define LNKECCCTL1_rd_link_ecc_corr_intr_clr_BitAddressOffset 1
#define LNKECCCTL1_rd_link_ecc_corr_intr_clr_RegisterSize 1

/* Register LNKECCCTL1 field rd_link_ecc_corr_cnt_clr */
/* Clear all Read Link-ECC correctable error count.
 If this bit set,LNKECCERRCNT0.rd_link_ecc_corr_cnt will be cleared. LPDDRCTL automatically clears this bit. */
#define LNKECCCTL1_rd_link_ecc_corr_cnt_clr_BitAddressOffset 2
#define LNKECCCTL1_rd_link_ecc_corr_cnt_clr_RegisterSize 1

/* Register LNKECCCTL1 field rd_link_ecc_corr_intr_force */
/* Interrupt force bit for rd_linkecc_corr_err_intr. Setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define LNKECCCTL1_rd_link_ecc_corr_intr_force_BitAddressOffset 3
#define LNKECCCTL1_rd_link_ecc_corr_intr_force_RegisterSize 1

/* Register LNKECCCTL1 field rd_link_ecc_uncorr_intr_en */
/* Interrupt enable bit for Read Link-ECC uncorrectable error. */
#define LNKECCCTL1_rd_link_ecc_uncorr_intr_en_BitAddressOffset 4
#define LNKECCCTL1_rd_link_ecc_uncorr_intr_en_RegisterSize 1

/* Register LNKECCCTL1 field rd_link_ecc_uncorr_intr_clr */
/* Clear Read Link-ECC uncorrectable error interrupt.
 If this bit set, rd_linkecc_uncorr_err_intr will be cleared. LPDDRCTL automatically clears this bit. */
#define LNKECCCTL1_rd_link_ecc_uncorr_intr_clr_BitAddressOffset 5
#define LNKECCCTL1_rd_link_ecc_uncorr_intr_clr_RegisterSize 1

/* Register LNKECCCTL1 field rd_link_ecc_uncorr_cnt_clr */
/* Clear all Read Link-ECC uncorrectable error count.
 If this bit set,LNKECCERRCNT0.rd_link_ecc_uncorr_cnt will be cleared. LPDDRCTL automatically clears this bit. */
#define LNKECCCTL1_rd_link_ecc_uncorr_cnt_clr_BitAddressOffset 6
#define LNKECCCTL1_rd_link_ecc_uncorr_cnt_clr_RegisterSize 1

/* Register LNKECCCTL1 field rd_link_ecc_uncorr_intr_force */
/* Interrupt force bit for rd_linkecc_uncorr_err_intr. Setting this register will cause the output interrupt to be asserted. DDRCTL automatically clears this bit. There is no interaction between functionally triggering an interrupt and forcing an interrupt (they are mutually exclusive). */
#define LNKECCCTL1_rd_link_ecc_uncorr_intr_force_BitAddressOffset 7
#define LNKECCCTL1_rd_link_ecc_uncorr_intr_force_RegisterSize 1

/* End of Register Definition for LNKECCCTL1 */

/* Register LNKECCPOISONCTL0 */
/* Link-ECC Poison Control Register 0 */
// #define LNKECCPOISONCTL0 (REGB_DDRC_CH0_BaseAddress + 0x988)
#define LNKECCPOISONCTL0_RegisterSize 32
#define LNKECCPOISONCTL0_RegisterResetValue 0x0
#define LNKECCPOISONCTL0_RegisterResetMask 0xffffffff

/* Register Field information for LNKECCPOISONCTL0 */

/* Register LNKECCPOISONCTL0 field linkecc_poison_inject_en */
/* Setting this register bit to 1 triggers the Link-ECC poisoning. Once Link-ECC is poisoned to a ECC code, the ECC poisoning is completed automatically and LNKECCPOISONSTAT.linkecc_poison_complete becomes 1.
  Please make sure that LNKECCPOISONSTAT.linkecc_poison_complete==0 before writing this register to 1. */
#define LNKECCPOISONCTL0_linkecc_poison_inject_en_BitAddressOffset 0
#define LNKECCPOISONCTL0_linkecc_poison_inject_en_RegisterSize 1

/* Register LNKECCPOISONCTL0 field linkecc_poison_type */
/* Indicates whether the Link-ECC poisoning operation is Single-bit error or Double bit error.
 - 0 - Single bit Error
 - 1 - Double bit Error */
#define LNKECCPOISONCTL0_linkecc_poison_type_BitAddressOffset 1
#define LNKECCPOISONCTL0_linkecc_poison_type_RegisterSize 1

/* Register LNKECCPOISONCTL0 field linkecc_poison_rw */
/* Indicates whether the Link-ECC poisoning operation is Read or Write.
 - 0 - Write
 - 1 - Read */
#define LNKECCPOISONCTL0_linkecc_poison_rw_BitAddressOffset 2
#define LNKECCPOISONCTL0_linkecc_poison_rw_RegisterSize 1

/* Register LNKECCPOISONCTL0 field linkecc_poison_dmi_sel */
/* Select target DMI(s) of Data for Write Link ECC poisoning. This is bit map indicator. Bit N corresponding to DMI[N]. */
#define LNKECCPOISONCTL0_linkecc_poison_dmi_sel_BitAddressOffset 16
#define LNKECCPOISONCTL0_linkecc_poison_dmi_sel_RegisterSize 4

/* Register LNKECCPOISONCTL0 field linkecc_poison_byte_sel */
/* Select target byte(s) of Data for Write Link ECC poisoning. This is bit map indicator. Bit N corresponding to Data[N*8+:8]. */
#define LNKECCPOISONCTL0_linkecc_poison_byte_sel_BitAddressOffset 24
#define LNKECCPOISONCTL0_linkecc_poison_byte_sel_RegisterSize 4

/* End of Register Definition for LNKECCPOISONCTL0 */

/* Register LNKECCPOISONSTAT */
/* Link-ECC Poison Status Register */
// #define LNKECCPOISONSTAT (REGB_DDRC_CH0_BaseAddress + 0x98c)
#define LNKECCPOISONSTAT_RegisterSize 32
#define LNKECCPOISONSTAT_RegisterResetValue 0x0
#define LNKECCPOISONSTAT_RegisterResetMask 0xffffffff

/* Register Field information for LNKECCPOISONSTAT */

/* Register LNKECCPOISONSTAT field linkecc_poison_complete */
/* Indicates Link-ECC poisoning operation is done.
 - 0 - Link-ECC poisoning is not completed
 - 1 - Link-ECC poisoning is completed */
#define LNKECCPOISONSTAT_linkecc_poison_complete_BitAddressOffset 0
#define LNKECCPOISONSTAT_linkecc_poison_complete_RegisterSize 1

/* End of Register Definition for LNKECCPOISONSTAT */

/* Register LNKECCINDEX */
/* Link-ECC Index Register */
// #define LNKECCINDEX (REGB_DDRC_CH0_BaseAddress + 0x990)
#define LNKECCINDEX_RegisterSize 32
#define LNKECCINDEX_RegisterResetValue 0x0
#define LNKECCINDEX_RegisterResetMask 0xffffffff

/* Register Field information for LNKECCINDEX */

/* Register LNKECCINDEX field rd_link_ecc_err_byte_sel */
/* Select of which data byte status output to LNKECCERRCNT.rd_link_ecc_uncorr_cnt, rd_link_ecc_corr_cnt and rd_link_ecc_err_syndrome.
  The value must be less than MEMC_DRAM_DATA_WIDTH/8. */
#define LNKECCINDEX_rd_link_ecc_err_byte_sel_BitAddressOffset 0
#define LNKECCINDEX_rd_link_ecc_err_byte_sel_RegisterSize 3

/* Register LNKECCINDEX field rd_link_ecc_err_rank_sel */
/* Select of which rank status output to LNKECCERRCNT.rd_link_ecc_uncorr_cnt, rd_link_ecc_corr_cnt and rd_link_ecc_err_syndrome.
  The value must be less than MEMC_NUM_RANKS. */
#define LNKECCINDEX_rd_link_ecc_err_rank_sel_BitAddressOffset 4
#define LNKECCINDEX_rd_link_ecc_err_rank_sel_RegisterSize 2

/* End of Register Definition for LNKECCINDEX */

/* Register LNKECCERRCNT0 */
/* Link-ECC Error Status Register 0 */
// #define LNKECCERRCNT0 (REGB_DDRC_CH0_BaseAddress + 0x994)
#define LNKECCERRCNT0_RegisterSize 32
#define LNKECCERRCNT0_RegisterResetValue 0x0
#define LNKECCERRCNT0_RegisterResetMask 0xffffffff

/* Register Field information for LNKECCERRCNT0 */

/* Register LNKECCERRCNT0 field rd_link_ecc_err_syndrome */
/* Indicates ECC syndrome from most recent single bit error. */
#define LNKECCERRCNT0_rd_link_ecc_err_syndrome_BitAddressOffset 0
#define LNKECCERRCNT0_rd_link_ecc_err_syndrome_RegisterSize 9

/* Register LNKECCERRCNT0 field rd_link_ecc_corr_cnt */
/* Indicates single bit error count. */
#define LNKECCERRCNT0_rd_link_ecc_corr_cnt_BitAddressOffset 16
#define LNKECCERRCNT0_rd_link_ecc_corr_cnt_RegisterSize 8

/* Register LNKECCERRCNT0 field rd_link_ecc_uncorr_cnt */
/* Indicates double bit error count. */
#define LNKECCERRCNT0_rd_link_ecc_uncorr_cnt_BitAddressOffset 24
#define LNKECCERRCNT0_rd_link_ecc_uncorr_cnt_RegisterSize 8

/* End of Register Definition for LNKECCERRCNT0 */

/* Register LNKECCERRSTAT */
/* Link-ECC Error Status Register 1 */
// #define LNKECCERRSTAT (REGB_DDRC_CH0_BaseAddress + 0x998)
#define LNKECCERRSTAT_RegisterSize 32
#define LNKECCERRSTAT_RegisterResetValue 0x0
#define LNKECCERRSTAT_RegisterResetMask 0xffffffff

/* Register Field information for LNKECCERRSTAT */

/* Register LNKECCERRSTAT field rd_link_ecc_corr_err_int */
/* Indicates single bit error for Read Link-ECC. If signle bit error happens, this interrupt bit is set. It remains set until cleared by LNKECCCTL1.rd_link_ecc_corr_intr_clr. Each bit represents one rank. (LSB is the lowest rank number.) */
#define LNKECCERRSTAT_rd_link_ecc_corr_err_int_BitAddressOffset 0
#define LNKECCERRSTAT_rd_link_ecc_corr_err_int_RegisterSize 4

/* Register LNKECCERRSTAT field rd_link_ecc_uncorr_err_int */
/* Indicates double bit error for Read Link-ECC. If double bit error happens, this interrupt bit is set. It remains set until cleared by LNKECCCTL1.rd_link_ecc_uncorr_intr_clr. Each bit represents one rank. (LSB is the lowest rank number.) */
#define LNKECCERRSTAT_rd_link_ecc_uncorr_err_int_BitAddressOffset 8
#define LNKECCERRSTAT_rd_link_ecc_uncorr_err_int_RegisterSize 4

/* End of Register Definition for LNKECCERRSTAT */

/* Register OPCTRL0 */
/* Operation Control Register 0 */
// #define OPCTRL0 (REGB_DDRC_CH0_BaseAddress + 0xb80)
#define OPCTRL0_RegisterSize 32
#define OPCTRL0_RegisterResetValue 0x0
#define OPCTRL0_RegisterResetMask 0xffffffff

/* Register Field information for OPCTRL0 */

/* Register OPCTRL0 field dis_wc */
/* When 1, disable write combine.

FOR DEBUG ONLY */
#define OPCTRL0_dis_wc_BitAddressOffset 0
#define OPCTRL0_dis_wc_RegisterSize 1

/* Register OPCTRL0 field dis_collision_page_opt */
/* When this is set to '0', auto-precharge is disabled for the flushed command in a collision case. Collision cases are write followed by read to same address, read followed by write to same address, or write followed by write to same address with OPCTRL0.dis_wc bit = 1 (where same address comparisons exclude the two address bits representing critical word).

FOR DEBUG ONLY. */
#define OPCTRL0_dis_collision_page_opt_BitAddressOffset 4
#define OPCTRL0_dis_collision_page_opt_RegisterSize 1

/* Register OPCTRL0 field dis_max_rank_rd_opt */
/* Disable optimized max_rank_rd and max_logical_rank_rd feature. This register is debug purpose only. For normal operation, This register must be set to 0. */
#define OPCTRL0_dis_max_rank_rd_opt_BitAddressOffset 6
#define OPCTRL0_dis_max_rank_rd_opt_RegisterSize 1

/* Register OPCTRL0 field dis_max_rank_wr_opt */
/* Disable optimized max_rank_wr and max_logical_rank_wr feature. This register is debug purpose only. For normal operation, This register must be set to 0. */
#define OPCTRL0_dis_max_rank_wr_opt_BitAddressOffset 7
#define OPCTRL0_dis_max_rank_wr_opt_RegisterSize 1

/* End of Register Definition for OPCTRL0 */

/* Register OPCTRL1 */
/* Operation Control Register 1 */
// #define OPCTRL1 (REGB_DDRC_CH0_BaseAddress + 0xb84)
#define OPCTRL1_RegisterSize 32
#define OPCTRL1_RegisterResetValue 0x0
#define OPCTRL1_RegisterResetMask 0xffffffff

/* Register Field information for OPCTRL1 */

/* Register OPCTRL1 field dis_dq */
/* When 1, DDRCTL will not de-queue any transactions from the CAM. Bypass is also disabled. All transactions are queued in the CAM. No reads or writes are issued to SDRAM as long as this is asserted.

This bit may be used to prevent reads or writes being issued by the DDRCTL, which makes it safe to modify certain register fields associated with reads and writes (see Programming Chapter for details).  After setting this bit, it is strongly recommended to poll OPCTRLCAM.wr_data_pipeline_empty and OPCTRLCAM.rd_data_pipeline_empty, before making changes to any registers which affect reads and writes.  This will ensure that the relevant logic in the DDRC is idle.

This bit is intended to be switched on-the-fly. */
#define OPCTRL1_dis_dq_BitAddressOffset 0
#define OPCTRL1_dis_dq_RegisterSize 1

/* Register OPCTRL1 field dis_hif */
/* When 1, DDRCTL asserts the HIF command signal hif_cmd_stall. DDRCTL will ignore the hif_cmd_valid and all other associated request signals.

This bit is intended to be switched on-the-fly. */
#define OPCTRL1_dis_hif_BitAddressOffset 1
#define OPCTRL1_dis_hif_RegisterSize 1

/* End of Register Definition for OPCTRL1 */

/* Register OPCTRLCAM */
/* CAM Operation Control Register */
// #define OPCTRLCAM (REGB_DDRC_CH0_BaseAddress + 0xb88)
#define OPCTRLCAM_RegisterSize 32
#define OPCTRLCAM_RegisterResetValue 0x0
#define OPCTRLCAM_RegisterResetMask 0xffffffff

/* Register Field information for OPCTRLCAM */

/* Register OPCTRLCAM field dbg_hpr_q_depth */
/* High priority read queue depth

 */
#define OPCTRLCAM_dbg_hpr_q_depth_BitAddressOffset 0
#define OPCTRLCAM_dbg_hpr_q_depth_RegisterSize 7

/* Register OPCTRLCAM field dbg_lpr_q_depth */
/* Low priority read queue depth

The last entry of Lpr queue is reserved for ECC SCRUB operation. This entry is not included in the calculation of the queue depth.

 */
#define OPCTRLCAM_dbg_lpr_q_depth_BitAddressOffset 8
#define OPCTRLCAM_dbg_lpr_q_depth_RegisterSize 7

/* Register OPCTRLCAM field dbg_w_q_depth */
/* Write queue depth

The last entry of WR queue is reserved for ECC SCRUB operation. This entry is not included in the calculation of the queue depth.

 */
#define OPCTRLCAM_dbg_w_q_depth_BitAddressOffset 16
#define OPCTRLCAM_dbg_w_q_depth_RegisterSize 7

/* Register OPCTRLCAM field dbg_stall */
/* Stall

FOR DEBUG ONLY */
#define OPCTRLCAM_dbg_stall_BitAddressOffset 24
#define OPCTRLCAM_dbg_stall_RegisterSize 1

/* Register OPCTRLCAM field dbg_rd_q_empty */
/* When 1, all the Read command queues and Read data buffers inside DDRC are empty. This register is to be used for debug purpose. 

An example use-case scenario: When Controller enters Self-Refresh using the Low-Power entry sequence, Controller is expected to have executed all the commands in its queues and the write and read data drained. Hence this register must be 1 at that time.

 */
#define OPCTRLCAM_dbg_rd_q_empty_BitAddressOffset 25
#define OPCTRLCAM_dbg_rd_q_empty_RegisterSize 1

/* Register OPCTRLCAM field dbg_wr_q_empty */
/* When 1, all the Write command queues and Write data buffers inside DDRC are empty. This register is to be used for debug purpose. 

An example use-case scenario: When Controller enters Self-Refresh using the Low-Power entry sequence, Controller is expected to have executed all the commands in its queues and the write and read data drained. Hence this register must be 1 at that time.

 */
#define OPCTRLCAM_dbg_wr_q_empty_BitAddressOffset 26
#define OPCTRLCAM_dbg_wr_q_empty_RegisterSize 1

/* Register OPCTRLCAM field rd_data_pipeline_empty */
/* This bit indicates that the read data pipeline on the DFI interface is empty.  This register is intended to be polled at least twice after setting OPCTRL1.dis_dq, to ensure that all remaining commands/data have completed. */
#define OPCTRLCAM_rd_data_pipeline_empty_BitAddressOffset 28
#define OPCTRLCAM_rd_data_pipeline_empty_RegisterSize 1

/* Register OPCTRLCAM field wr_data_pipeline_empty */
/* This bit indicates that the write data pipeline on the DFI interface is empty.  This register is intended to be polled at least twice after setting OPCTRL1.dis_dq, to ensure that all remaining commands/data have completed. */
#define OPCTRLCAM_wr_data_pipeline_empty_BitAddressOffset 29
#define OPCTRLCAM_wr_data_pipeline_empty_RegisterSize 1

/* End of Register Definition for OPCTRLCAM */

/* Register OPCTRLCMD */
/* Command Operation Control Register */
// #define OPCTRLCMD (REGB_DDRC_CH0_BaseAddress + 0xb8c)
#define OPCTRLCMD_RegisterSize 32
#define OPCTRLCMD_RegisterResetValue 0x0
#define OPCTRLCMD_RegisterResetMask 0xffffffff

/* Register Field information for OPCTRLCMD */

/* Register OPCTRLCMD field rank0_refresh */
/* SoC might initiate a rank0_refresh operation (refresh operation to rank 0) only if this signal is low.
This signal goes high in the clock after OPCTRLCMD.rank0_refresh is set to one.
It goes low when the rank0_refresh operation is stored in the DDRCTL.
It is recommended not to perform rank0_refresh operations when this signal is high.
 - 0 Indicates that the SoC can initiate a rank0_refresh operation
 - 1 Indicates that rank0_refresh operation has not been stored yet in the DDRCTL */
#define OPCTRLCMD_rank0_refresh_BitAddressOffset 0
#define OPCTRLCMD_rank0_refresh_RegisterSize 1

/* Register OPCTRLCMD field rank1_refresh */
/* SoC might initiate a rank1_refresh operation (refresh operation to rank 1) only if this signal is low.
This signal goes high in the clock after OPCTRLCMD.rank1_refresh is set to one.
It goes low when the rank1_refresh operation is stored in the DDRCTL.
It is recommended not to perform rank1_refresh operations when this signal is high.
 - 0 Indicates that the SoC can initiate a rank1_refresh operation
 - 1 Indicates that rank1_refresh operation has not been stored yet in the DDRCTL */
#define OPCTRLCMD_rank1_refresh_BitAddressOffset 1
#define OPCTRLCMD_rank1_refresh_RegisterSize 1

/* Register OPCTRLCMD field zq_calib_short */
/* 
Setting this register bit to 1 indicates to the DDRCTL to issue a ZQCS (ZQ calibration short)/MPC(ZQ calibration) command to the SDRAM.  When this request is stored in the DDRCTL, the bit is automatically cleared. This operation can be performed only when ZQCTL0.dis_auto_zq=1. It is recommended NOT to set this register bit if in Init, in Self-Refresh(except LPDDR4/5) or SR-Powerdown(LPDDR4/5) or Deep Sleep Mode or Maximum Power Saving Mode. 

For Self-Refresh(except LPDDR4/5) or SR-Powerdown(LPDDR4/5) it will be scheduled after SR(except LPDDR4/5) or SRPD(LPDDR4/5) has been exited.

For Deep Sleep Mode, it will be scheduled after DSM and/or SRPD has been exited.

For Maximum Power Saving Mode, it will not be scheduled, although OPCTRLSTAT.zq_calib_short_busy will be de-asserted. */
#define OPCTRLCMD_zq_calib_short_BitAddressOffset 16
#define OPCTRLCMD_zq_calib_short_RegisterSize 1

/* Register OPCTRLCMD field ctrlupd */
/* 
Setting this register bit to 1 indicates to the DDRCTL to issue a dfi_ctrlupd_req to the PHY.  When this request is stored in the DDRCTL, the bit is automatically cleared. This operation must only be performed when DFIUPD0.dis_auto_ctrlupd=1. */
#define OPCTRLCMD_ctrlupd_BitAddressOffset 17
#define OPCTRLCMD_ctrlupd_RegisterSize 1

/* End of Register Definition for OPCTRLCMD */

/* Register OPCTRLSTAT */
/* Status Operation Control Register */
// #define OPCTRLSTAT (REGB_DDRC_CH0_BaseAddress + 0xb90)
#define OPCTRLSTAT_RegisterSize 32
#define OPCTRLSTAT_RegisterResetValue 0x0
#define OPCTRLSTAT_RegisterResetMask 0xffffffff

/* Register Field information for OPCTRLSTAT */

/* Register OPCTRLSTAT field rank0_refresh_busy */
/* SoC core may initiate a rank0_refresh operation (refresh operation to rank 0) only if this signal is low. This signal goes high in the clock after OPCTRLCMD.rank0_refresh is set to one.
 It goes low when the rank0_refresh operation is stored in the DDRCTL.
 It is recommended not to perform rank0_refresh operations when this signal is high.  - 0 - Indicates that the SoC core can initiate a rank0_refresh operation
 - 1 - Indicates that rank0_refresh operation has not been stored yet in the DDRCTL */
#define OPCTRLSTAT_rank0_refresh_busy_BitAddressOffset 0
#define OPCTRLSTAT_rank0_refresh_busy_RegisterSize 1

/* Register OPCTRLSTAT field rank1_refresh_busy */
/* SoC core may initiate a rank1_refresh operation (refresh operation to rank 1) only if this signal is low. This signal goes high in the clock after OPCTRLCMD.rank1_refresh is set to one.
 It goes low when the rank1_refresh operation is stored in the DDRCTL.
 It is recommended not to perform rank1_refresh operations when this signal is high.  - 0 - Indicates that the SoC core can initiate a rank1_refresh operation
 - 1 - Indicates that rank1_refresh operation has not been stored yet in the DDRCTL */
#define OPCTRLSTAT_rank1_refresh_busy_BitAddressOffset 1
#define OPCTRLSTAT_rank1_refresh_busy_RegisterSize 1

/* Register OPCTRLSTAT field zq_calib_short_busy */
/* SoC core may initiate a ZQCS (ZQ calibration short) operation only if this signal is low. This signal goes high in the clock after the DDRCTL accepts the ZQCS request. It goes low when the ZQCS operation is initiated in the DDRCTL. It is recommended not to perform ZQCS operations when this signal is high.
 - 0 - Indicates that the SoC core can initiate a ZQCS operation
 - 1 - Indicates that ZQCS operation has not been initiated yet in the DDRCTL */
#define OPCTRLSTAT_zq_calib_short_busy_BitAddressOffset 16
#define OPCTRLSTAT_zq_calib_short_busy_RegisterSize 1

/* Register OPCTRLSTAT field ctrlupd_busy */
/* SoC core may initiate a ctrlupd operation only if this signal is low.
 This signal goes high in the clock after the DDRCTL accepts the ctrlupd request. It goes low when the ctrlupd operation is initiated in the DDRCTL.
 It is recommended not to perform ctrlupd operations when this signal is high.
 - 0 - Indicates that the SoC core can initiate a ctrlupd operation
 - 1 - Indicates that ctrlupd operation has not been initiated yet in the DDRCTL */
#define OPCTRLSTAT_ctrlupd_busy_BitAddressOffset 17
#define OPCTRLSTAT_ctrlupd_busy_RegisterSize 1

/* End of Register Definition for OPCTRLSTAT */

/* Register OPCTRLCAM1 */
/* CAM Operation Control Register 1 */
// #define OPCTRLCAM1 (REGB_DDRC_CH0_BaseAddress + 0xb94)
#define OPCTRLCAM1_RegisterSize 32
#define OPCTRLCAM1_RegisterResetValue 0x0
#define OPCTRLCAM1_RegisterResetMask 0xffffffff

/* Register Field information for OPCTRLCAM1 */

/* Register OPCTRLCAM1 field dbg_wrecc_q_depth */
/* Write ECC queue depth

FOR DEBUG ONLY */
#define OPCTRLCAM1_dbg_wrecc_q_depth_BitAddressOffset 0
#define OPCTRLCAM1_dbg_wrecc_q_depth_RegisterSize 7

/* End of Register Definition for OPCTRLCAM1 */

/* Register SWCTL */
/* Software Register Programming Control Enable */
// #define SWCTL (REGB_DDRC_CH0_BaseAddress + 0xc80)
#define SWCTL_RegisterSize 32
#define SWCTL_RegisterResetValue 0x1
#define SWCTL_RegisterResetMask 0xffffffff

/* Register Field information for SWCTL */

/* Register SWCTL field sw_done */
/* Enable quasi-dynamic register programming outside reset. Program register to 0 to enable quasi-dynamic programming. Set back register to 1 once programming is done. */
#define SWCTL_sw_done_BitAddressOffset 0
#define SWCTL_sw_done_RegisterSize 1

/* End of Register Definition for SWCTL */

/* Register SWSTAT */
/* Software Register Programming Control Status */
// #define SWSTAT (REGB_DDRC_CH0_BaseAddress + 0xc84)
#define SWSTAT_RegisterSize 32
#define SWSTAT_RegisterResetValue 0x1
#define SWSTAT_RegisterResetMask 0xffffffff

/* Register Field information for SWSTAT */

/* Register SWSTAT field sw_done_ack */
/* Register programming done. This register is the echo of SWCTL.sw_done. Wait for sw_done value 1 to propagate to sw_done_ack at the end of the programming sequence to ensure that the correct registers values are propagated to the destination clock domains. */
#define SWSTAT_sw_done_ack_BitAddressOffset 0
#define SWSTAT_sw_done_ack_RegisterSize 1

/* End of Register Definition for SWSTAT */

/* Register DIMMCTL */
/* DIMM Control Register */
// #define DIMMCTL (REGB_DDRC_CH0_BaseAddress + 0xc88)
#define DIMMCTL_RegisterSize 32
#define DIMMCTL_RegisterResetValue 0x0
#define DIMMCTL_RegisterResetMask 0xffffffff

/* Register Field information for DIMMCTL */

/* Register DIMMCTL field dimm_stagger_cs_en */
/* Staggering enable for multi-rank accesses (for multi-rank UDIMM, RDIMM and LRDIMM implementations only).

Note: Even if this bit is set it does not take care of software driven MR commands (via MRCTRL0/MRCTRL1), where software is responsible to send them to seperate ranks as appropriate.
    - 1 - (DDR4) Send MRS commands to each ranks seperately
    - 1 - (non-DDR4) Send all commands to even and odd ranks seperately
    - 1 - (DDR5) DRAMSET1TMG30.t_selfref_exit_stagger is used for staggering Self Refresh exit timing between subchannel A and B
    - 0 - Do not stagger accesses

LPDDR4/LPDDR5: Not supported. */
#define DIMMCTL_dimm_stagger_cs_en_BitAddressOffset 0
#define DIMMCTL_dimm_stagger_cs_en_RegisterSize 1

/* Register DIMMCTL field dimm_addr_mirr_en */
/* Address Mirroring Enable (for multi-rank UDIMM implementations and multi-rank DDR4 RDIMM/LRDIMM implementations).

Some UDIMMs and DDR4 RDIMMs/LRDIMMs implement address mirroring for odd ranks, which means that the following address, bank address and bank group bits are swapped: (A3, A4), (A5, A6), (A7, A8), (BA0, BA1) and also (A11, A13), (BG0, BG1) for the DDR4. Setting this bit ensures that, for mode register accesses during the automatic initialization routine, these bits are swapped within the DDRCTL to compensate for this UDIMM/RDIMM/LRDIMM swapping. In addition to the automatic initialization routine, in case of DDR4 UDIMM/RDIMM/LRDIMM, they are swapped during the automatic MRS access to enable/disable of a particular DDR4 feature.

Note: This has no effect on the address of any other memory accesses, or of software-driven mode register accesses.

Note: In case of x16 DDR4 DIMMs, BG1 output of MRS for the odd ranks is same as BG0 because BG1 is invalid, hence dimm_dis_bg_mirroring register must be set to 1.
    - 1 - For odd ranks, implement address mirroring for MRS commands to during initialization and for any automatic DDR4 MRS commands (to be used if UDIMM/RDIMM/LRDIMM implements address mirroring)
    - 0 - Do not implement address mirroring

DDR5/LPDDR4/LPDDR5: Not supported. */
#define DIMMCTL_dimm_addr_mirr_en_BitAddressOffset 1
#define DIMMCTL_dimm_addr_mirr_en_RegisterSize 1

/* End of Register Definition for DIMMCTL */

/* Register RANKCTL */
/* Rank Control Register */
// #define RANKCTL (REGB_DDRC_CH0_BaseAddress + 0xc90)
#define RANKCTL_RegisterSize 32
#define RANKCTL_RegisterResetValue 0xf
#define RANKCTL_RegisterResetMask 0xffffffff

/* Register Field information for RANKCTL */

/* Register RANKCTL field max_rank_rd */
/* Only present for multi-rank configurations.

Background: Reads to the same rank can be performed back-to-back. Reads to different ranks require additional gap dictated by the register RANKCTL.diff_rank_rd_gap. This is to avoid possible data bus contention as well as to give PHY enough time to switch the delay when changing ranks. The DDRCTL arbitrates for bus access on a cycle-by-cycle basis; therefore after a read is scheduled, there are few clock cycles (determined by the value on RANKCTL.diff_rank_rd_gap register) in which only reads from the same rank are eligible to be scheduled. This prevents reads from other ranks from having fair access to the data bus.

This parameter represents the maximum number of reads that can be scheduled consecutively to the same rank. After this number is reached, a delay equal to RANKCTL.diff_rank_rd_gap is inserted by the scheduler to allow all ranks a fair opportunity to be scheduled. Higher numbers increase bandwidth utilization, lower numbers increase fairness.

This feature can be DISABLED by setting this register to 0. When set to 0, the Controller will stay on the same rank as long as commands are available for it.

Minimum programmable value is 0 (feature disabled) and maximum programmable value is 0xF.

FOR PERFORMANCE ONLY. */
#define RANKCTL_max_rank_rd_BitAddressOffset 0
#define RANKCTL_max_rank_rd_RegisterSize 4

/* Register RANKCTL field max_rank_wr */
/* Only present for multi-rank configurations.

Background: Writes to the same rank can be performed back-to-back. Writes to different ranks require additional gap dictated by the register RANKCTL.diff_rank_wr_gap. This is to avoid possible data bus contention as well as to give PHY enough time to switch the delay when changing ranks. The DDRCTL arbitrates for bus access on a cycle-by-cycle basis; therefore after a write is scheduled, there are few clock cycles (determined by the value on RANKCTL.diff_rank_wr_gap register) in which only writes from the same rank are eligible to be scheduled. This prevents writes from other ranks from having fair access to the data bus.

This parameter represents the maximum number of writes that can be scheduled consecutively to the same rank. After this number is reached, a delay equal to RANKCTL.diff_rank_wr_gap is inserted by the scheduler to allow all ranks a fair opportunity to be scheduled. Higher numbers increase bandwidth utilization, lower numbers increase fairness.

This feature can be DISABLED by setting this register to 0. When set to 0, the Controller will stay on the same rank as long as commands are available for it.

Minimum programmable value is 0 (feature disabled) and maximum programmable value is 0xF.

FOR PERFORMANCE ONLY. */
#define RANKCTL_max_rank_wr_BitAddressOffset 12
#define RANKCTL_max_rank_wr_RegisterSize 4

/* End of Register Definition for RANKCTL */

/* Register DBICTL */
/* DM/DBI Control Register */
// #define DBICTL (REGB_DDRC_CH0_BaseAddress + 0xc94)
#define DBICTL_RegisterSize 32
#define DBICTL_RegisterResetValue 0x1
#define DBICTL_RegisterResetMask 0xffffffff

/* Register Field information for DBICTL */

/* Register DBICTL field dm_en */
/* DM enable signal in DDRC.
  - 0 - DM is disabled.
  - 1 - DM is enabled.
This signal must be set the same logical value as DRAM's mode register.
  - DDR4:   Set this to same value as MR5 bit A10. When x4 devices are used, this signal must be set to 0.
  - DDR5:   Set this to same value as MR5[5]. When x4 devices are used, this signal must be set to 0.
  - LPDDR4/LPDDR5: Set this to inverted value of MR13[5] which is opposite polarity from this signal. */
#define DBICTL_dm_en_BitAddressOffset 0
#define DBICTL_dm_en_RegisterSize 1

/* Register DBICTL field wr_dbi_en */
/* Write DBI enable signal in DDRC.
  - 0 - Write DBI is disabled.
  - 1 - Write DBI is enabled.
This signal must be set the same value as DRAM's mode register.
  - DDR4:   MR5 bit A11. When x4 devices are used, this signal must be set to 0.
  - DDR5:   This signal must be set to 0.
  - LPDDR4/LPDDR5: MR3[7]. */
#define DBICTL_wr_dbi_en_BitAddressOffset 1
#define DBICTL_wr_dbi_en_RegisterSize 1

/* Register DBICTL field rd_dbi_en */
/* Read DBI enable signal in DDRC.
  - 0 - Read DBI is disabled.
  - 1 - Read DBI is enabled.
This signal must be set the same value as DRAM's mode register.
  - DDR4:   MR5 bit A12. When x4 devices are used, this signal must be set to 0.
  - DDR5:   This signal must be set to 0.
  - LPDDR4/LPDDR5: MR3[6]. */
#define DBICTL_rd_dbi_en_BitAddressOffset 2
#define DBICTL_rd_dbi_en_RegisterSize 1

/* End of Register Definition for DBICTL */

/* Register ODTMAP */
/* ODT/Rank Map Register */
// #define ODTMAP (REGB_DDRC_CH0_BaseAddress + 0xc9c)
#define ODTMAP_RegisterSize 32
#define ODTMAP_RegisterResetValue 0x2211
#define ODTMAP_RegisterResetMask 0xffffffff

/* Register Field information for ODTMAP */

/* Register ODTMAP field rank0_wr_odt */
/* Indicates which remote ODTs must be turned on during a write to rank 0.

Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.

Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, etc.

For each rank, set its bit to 1 to enable its ODT. */
#define ODTMAP_rank0_wr_odt_BitAddressOffset 0
#define ODTMAP_rank0_wr_odt_RegisterSize 2

/* Register ODTMAP field rank0_rd_odt */
/* Indicates which remote ODTs must be turned on during a read from rank 0.

Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.

Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, etc.

For each rank, set its bit to 1 to enable its ODT. */
#define ODTMAP_rank0_rd_odt_BitAddressOffset 4
#define ODTMAP_rank0_rd_odt_RegisterSize 2

/* Register ODTMAP field rank1_wr_odt */
/* Indicates which remote ODTs must be turned on during a write to rank 1.

Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.

Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, etc.

For each rank, set its bit to 1 to enable its ODT.

Present only in configurations that have 2 or more ranks */
#define ODTMAP_rank1_wr_odt_BitAddressOffset 8
#define ODTMAP_rank1_wr_odt_RegisterSize 2

/* Register ODTMAP field rank1_rd_odt */
/* Indicates which remote ODTs must be turned on during a read from rank 1.

Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.

Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, etc.

For each rank, set its bit to 1 to enable its ODT.

Present only in configurations that have 2 or more ranks */
#define ODTMAP_rank1_rd_odt_BitAddressOffset 12
#define ODTMAP_rank1_rd_odt_RegisterSize 2

/* End of Register Definition for ODTMAP */

/* Register DATACTL0 */
/* Data Control register 0 */
// #define DATACTL0 (REGB_DDRC_CH0_BaseAddress + 0xca0)
#define DATACTL0_RegisterSize 32
#define DATACTL0_RegisterResetValue 0x0
#define DATACTL0_RegisterResetMask 0xffffffff

/* Register Field information for DATACTL0 */

/* Register DATACTL0 field rd_data_copy_en */
/* Read Data Copy 

  1: Enable Read Data Copy X 

  0: Disable Read Data Copy X */
#define DATACTL0_rd_data_copy_en_BitAddressOffset 16
#define DATACTL0_rd_data_copy_en_RegisterSize 1

/* Register DATACTL0 field wr_data_copy_en */
/* Write Data Copy 

  1: Enable Write Data Copy X 

  0: Disable Write Data Copy X */
#define DATACTL0_wr_data_copy_en_BitAddressOffset 17
#define DATACTL0_wr_data_copy_en_RegisterSize 1

/* Register DATACTL0 field wr_data_x_en */
/* Write Data X 

  1: Enable Write X 

  0: Write X */
#define DATACTL0_wr_data_x_en_BitAddressOffset 18
#define DATACTL0_wr_data_x_en_RegisterSize 1

/* End of Register Definition for DATACTL0 */

/* Register SWCTLSTATIC */
/* Static Registers Write Enable */
// #define SWCTLSTATIC (REGB_DDRC_CH0_BaseAddress + 0xca4)
#define SWCTLSTATIC_RegisterSize 32
#define SWCTLSTATIC_RegisterResetValue 0x0
#define SWCTLSTATIC_RegisterResetMask 0xffffffff

/* Register Field information for SWCTLSTATIC */

/* Register SWCTLSTATIC field sw_static_unlock */
/* Enables static register programming outside reset.
Program this register to 1 to enable static register programming.
Set register back to 0 once programming is done. */
#define SWCTLSTATIC_sw_static_unlock_BitAddressOffset 0
#define SWCTLSTATIC_sw_static_unlock_RegisterSize 1

/* End of Register Definition for SWCTLSTATIC */

/* Register INITTMG0 */
/* SDRAM Initialization Timing Register 0 */
// #define INITTMG0 (REGB_DDRC_CH0_BaseAddress + 0xd00)
#define INITTMG0_RegisterSize 32
#define INITTMG0_RegisterResetValue 0x2004e
#define INITTMG0_RegisterResetMask 0xffffffff

/* Register Field information for INITTMG0 */

/* Register INITTMG0 field pre_cke_x1024 */
/* Cycles to wait after reset before driving CKE (CS in DDR5) high to start the SDRAM initialization sequence.

DDR5: tINIT3 of 4 ms (min) - simulation only.
 
LPDDR4: tINIT3 of 2 ms (min) 
 
For DDR4 RDIMMs, this must include the time needed to satisfy tSTAB.

Unit: Multiples of 1024 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define INITTMG0_pre_cke_x1024_BitAddressOffset 0
#define INITTMG0_pre_cke_x1024_RegisterSize 13

/* Register INITTMG0 field post_cke_x1024 */
/* Cycles to wait after driving CKE (CS in DDR5) high to start the SDRAM initialization sequence.

DDR5: tINIT4 of 2 us (min) - simulation only.

LPDDR4 typically requires this to be programmed for a delay of 2 us.

Unit: Multiples of 1024 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define INITTMG0_post_cke_x1024_BitAddressOffset 16
#define INITTMG0_post_cke_x1024_RegisterSize 10

/* Register INITTMG0 field skip_dram_init */
/* If lower bit is enabled the SDRAM initialization routine is skipped. The upper bit decides what state the controller starts up in when reset is removed  
 - 00 - SDRAM Initialization routine is run after power-up
 - 01 - SDRAM Initialization routine is skipped after power-up. Controller starts up in Normal Mode
 - 11 - SDRAM Initialization routine is skipped after power-up. Controller starts up in Self-refresh Mode
 - 10 - Reserved. */
#define INITTMG0_skip_dram_init_BitAddressOffset 30
#define INITTMG0_skip_dram_init_RegisterSize 2

/* End of Register Definition for INITTMG0 */

/* Register INITTMG1 */
/* SDRAM Initialization Timing Register 1 */
// #define INITTMG1 (REGB_DDRC_CH0_BaseAddress + 0xd04)
#define INITTMG1_RegisterSize 32
#define INITTMG1_RegisterResetValue 0x0
#define INITTMG1_RegisterResetMask 0xffffffff

/* Register Field information for INITTMG1 */

/* Register INITTMG1 field dram_rstn_x1024 */
/* Number of cycles to assert SDRAM reset signal during init sequence.

For use with a Synopsys DDR PHY, this must be set to a minimum of 1.

Unit: Multiples of 1024 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define INITTMG1_dram_rstn_x1024_BitAddressOffset 16
#define INITTMG1_dram_rstn_x1024_RegisterSize 10

/* End of Register Definition for INITTMG1 */

/* Register DDRCTL_VER_NUMBER */
/* DDRCTL Version Number Register */
// #define DDRCTL_VER_NUMBER (REGB_DDRC_CH0_BaseAddress + 0xff8)
#define DDRCTL_VER_NUMBER_RegisterSize 32
#define DDRCTL_VER_NUMBER_RegisterResetValue 0x3130302a
#define DDRCTL_VER_NUMBER_RegisterResetMask 0xffffffff

/* Register Field information for DDRCTL_VER_NUMBER */

/* Register DDRCTL_VER_NUMBER field ver_number */
/* Indicates the Device Version Number value. */
#define DDRCTL_VER_NUMBER_ver_number_BitAddressOffset 0
#define DDRCTL_VER_NUMBER_ver_number_RegisterSize 32

/* End of Register Definition for DDRCTL_VER_NUMBER */

/* Register DDRCTL_VER_TYPE */
/* DDRCTL Version Type Register */
// #define DDRCTL_VER_TYPE (REGB_DDRC_CH0_BaseAddress + 0xffc)
#define DDRCTL_VER_TYPE_RegisterSize 32
#define DDRCTL_VER_TYPE_RegisterResetValue 0x65613036
#define DDRCTL_VER_TYPE_RegisterResetMask 0xffffffff

/* Register Field information for DDRCTL_VER_TYPE */

/* Register DDRCTL_VER_TYPE field ver_type */
/* Indicates the Device Version Type value. */
#define DDRCTL_VER_TYPE_ver_type_BitAddressOffset 0
#define DDRCTL_VER_TYPE_ver_type_RegisterSize 32

/* End of Register Definition for DDRCTL_VER_TYPE */

#define REGB_ADDR_MAP0_BaseAddress 0x30000

/* Register ADDRMAP1 */
/* Address Map Register 1 */
// #define ADDRMAP1 (REGB_ADDR_MAP0_BaseAddress + 0x4)
#define ADDRMAP1_RegisterSize 32
#define ADDRMAP1_RegisterResetValue 0x0
#define ADDRMAP1_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP1 */

/* Register ADDRMAP1 field addrmap_cs_bit0 */
/* Selects the HIF address bit used as rank address bit 0.

Valid Range: 0 to 32, and 63

Internal Base: 6

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 63 and then rank address bit 0 is set to 0. */
#define ADDRMAP1_addrmap_cs_bit0_BitAddressOffset 0
#define ADDRMAP1_addrmap_cs_bit0_RegisterSize 6

/* End of Register Definition for ADDRMAP1 */

/* Register ADDRMAP3 */
/* Address Map Register 3 */
// #define ADDRMAP3 (REGB_ADDR_MAP0_BaseAddress + 0xc)
#define ADDRMAP3_RegisterSize 32
#define ADDRMAP3_RegisterResetValue 0x0
#define ADDRMAP3_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP3 */

/* Register ADDRMAP3 field addrmap_bank_b0 */
/* Selects the HIF address bits used as bank address bit 0.

Valid Range: 0 to 35, and 63

Internal Base: 3

The selected HIF address bit for each of the bank address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP3_addrmap_bank_b0_BitAddressOffset 0
#define ADDRMAP3_addrmap_bank_b0_RegisterSize 6

/* Register ADDRMAP3 field addrmap_bank_b1 */
/* Selects the HIF address bits used as bank address bit 1.

Valid Range: 0 to 34, and 63

Internal Base: 4

The selected HIF address bit for each of the bank address bits is determined by adding the internal base to the value of this field.

  If unused, set to 63 and then bank address bit 1 is set to 0. */
#define ADDRMAP3_addrmap_bank_b1_BitAddressOffset 8
#define ADDRMAP3_addrmap_bank_b1_RegisterSize 6

/* Register ADDRMAP3 field addrmap_bank_b2 */
/* Selects the HIF address bit used as bank address bit 2.

Valid Range: 0 to 33, and 63

Internal Base: 5

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 63 and then bank address bit 2 is set to 0. */
#define ADDRMAP3_addrmap_bank_b2_BitAddressOffset 16
#define ADDRMAP3_addrmap_bank_b2_RegisterSize 6

/* End of Register Definition for ADDRMAP3 */

/* Register ADDRMAP4 */
/* Address Map Register 4 */
// #define ADDRMAP4 (REGB_ADDR_MAP0_BaseAddress + 0x10)
#define ADDRMAP4_RegisterSize 32
#define ADDRMAP4_RegisterResetValue 0x0
#define ADDRMAP4_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP4 */

/* Register ADDRMAP4 field addrmap_bg_b0 */
/* Selects the HIF address bits used as bank group address bit 0.

Valid Range: 0 to 35, and 63

Internal Base: 3

The selected HIF address bit for each of the bank group address bits is determined by adding the internal base to the value of this field.

  If unused, set to 63 and then bank group address bit 0 is set to 0. */
#define ADDRMAP4_addrmap_bg_b0_BitAddressOffset 0
#define ADDRMAP4_addrmap_bg_b0_RegisterSize 6

/* Register ADDRMAP4 field addrmap_bg_b1 */
/* Selects the HIF address bits used as bank group address bit 1.

Valid Range: 0 to 34, and 63

Internal Base: 4

The selected HIF address bit for each of the bank group address bits is determined by adding the internal base to the value of this field.

  If unused, set to 63 and then bank group address bit 1 is set to 0. */
#define ADDRMAP4_addrmap_bg_b1_BitAddressOffset 8
#define ADDRMAP4_addrmap_bg_b1_RegisterSize 6

/* End of Register Definition for ADDRMAP4 */

/* Register ADDRMAP5 */
/* Address Map Register 5 */
// #define ADDRMAP5 (REGB_ADDR_MAP0_BaseAddress + 0x14)
#define ADDRMAP5_RegisterSize 32
#define ADDRMAP5_RegisterResetValue 0x0
#define ADDRMAP5_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP5 */

/* Register ADDRMAP5 field addrmap_col_b7 */
/* 
Selects the HIF address bit used as column address bit 7.

Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline ECC configuration.

Internal Base: 7 

The selected HIF address bit is determined by adding the internal base to the value of this field. 

  In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the highest 3 valid HIF address bits.

  If column bit 7 is the third highest column address bit, it must map to the third highest valid HIF address bit. (x = the highest valid HIF address bit - 2 - internal base)

  If unused, set to 31 and then this column address bit is set to 0. */
#define ADDRMAP5_addrmap_col_b7_BitAddressOffset 0
#define ADDRMAP5_addrmap_col_b7_RegisterSize 5

/* Register ADDRMAP5 field addrmap_col_b8 */
/* 
Selects the HIF address bit used as column address bit 8.

Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline ECC configuration.

Internal Base: 8

The selected HIF address bit is determined by adding the internal base to the value of this field.

Note: In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the highest 3 valid HIF address bits.

  If column bit 8 is the second highest column address bit, it must map to the second highest valid HIF address bit. (x = the highest valid HIF address bit - 1 - internal base)

  If column bit 8 is the third highest column address bit, it must map to the third highest valid HIF address bit. (x = the highest valid HIF address bit - 2 - internal base)

  If unused, set to 31 and then this column address bit is set to 0. */
#define ADDRMAP5_addrmap_col_b8_BitAddressOffset 8
#define ADDRMAP5_addrmap_col_b8_RegisterSize 5

/* Register ADDRMAP5 field addrmap_col_b9 */
/* 
Selects the HIF address bit used as column address bit 9.

Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline ECC configuration.

Internal Base: 9

The selected HIF address bit is determined by adding the internal base to the value of this field.

Note: In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the highest 3 valid HIF address bits.

  If column bit 9 is the highest column address bit, it must map to the highest valid HIF address bit. (x = the highest valid HIF address bit - internal base)

  If column bit 9 is the second highest column address bit, it must map to the second highest valid HIF address bit. (x = the highest valid HIF address bit - 1 - internal base)

  If column bit 9 is the third highest column address bit, it must map to the third highest valid HIF address bit. (x = the highest valid HIF address bit - 2 - internal base)

  If unused, set to 31 and then this column address bit is set to 0. */
#define ADDRMAP5_addrmap_col_b9_BitAddressOffset 16
#define ADDRMAP5_addrmap_col_b9_RegisterSize 5

/* Register ADDRMAP5 field addrmap_col_b10 */
/* 
Selects the HIF address bit used as column address bit 10.

Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline ECC configuration.

Internal Base: 10

The selected HIF address bit is determined by adding the internal base to the value of this field.

Note: In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the highest 3 valid HIF address bits.

  If column bit 10 is the highest column address bit, it must map to the highest valid HIF address bit. (x = the highest valid HIF address bit - internal base)

  If column bit 10 is the second highest column address bit, it must map to the second highest valid HIF address bit. (x = the highest valid HIF address bit - 1 - internal base)

  If column bit 10 is the third highest column address bit, it must map to the third highest valid HIF address bit. (x = the highest valid HIF address bit - 2 - internal base)

  If unused, set to 31 and then this column address bit is set to 0. */
#define ADDRMAP5_addrmap_col_b10_BitAddressOffset 24
#define ADDRMAP5_addrmap_col_b10_RegisterSize 5

/* End of Register Definition for ADDRMAP5 */

/* Register ADDRMAP6 */
/* Address Map Register 6 */
// #define ADDRMAP6 (REGB_ADDR_MAP0_BaseAddress + 0x18)
#define ADDRMAP6_RegisterSize 32
#define ADDRMAP6_RegisterResetValue 0x0
#define ADDRMAP6_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP6 */

/* Register ADDRMAP6 field addrmap_col_b3 */
/* 
Selects the HIF address bit used as column address bit 3.

Valid Range: 0 to 7. 

Internal Base: 3

The selected HIF address bit is determined by adding the internal base to the value of this field.


Note : In LPDDR4/5 or DDR5, it is required to program this to 0. */
#define ADDRMAP6_addrmap_col_b3_BitAddressOffset 0
#define ADDRMAP6_addrmap_col_b3_RegisterSize 4

/* Register ADDRMAP6 field addrmap_col_b4 */
/* 
  - Full bus width mode: Selects the HIF address bit used as column address bit 4.
  - Half bus width mode: Selects the HIF address bit used as column address bit 5.
  - Quarter bus width mode: Selects the HIF address bit used as column address bit 6.
Valid Range: 0 to 7, and 15

Internal Base: 4

The selected HIF address bit is determined by adding the internal base to the value of this field.
 
  If unused, set to 15 and then this column address bit is set to 0. */
#define ADDRMAP6_addrmap_col_b4_BitAddressOffset 8
#define ADDRMAP6_addrmap_col_b4_RegisterSize 4

/* Register ADDRMAP6 field addrmap_col_b5 */
/* 
Selects the HIF address bit used as column address bit 5.

Valid Range: 0 to 7, and 15

Internal Base: 5

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 15 and then this column address bit is set to 0. */
#define ADDRMAP6_addrmap_col_b5_BitAddressOffset 16
#define ADDRMAP6_addrmap_col_b5_RegisterSize 4

/* Register ADDRMAP6 field addrmap_col_b6 */
/* 
Selects the HIF address bit used as column address bit 6.

Valid Range: 0 to 7, x and 15. x indicates a valid value in the inline ECC configuration.

Internal Base: 6

The selected HIF address bit is determined by adding the internal base to the value of this field.

If unused, set to 15 and then this column address bit is set to 0.

 */
#define ADDRMAP6_addrmap_col_b6_BitAddressOffset 24
#define ADDRMAP6_addrmap_col_b6_RegisterSize 4

/* End of Register Definition for ADDRMAP6 */

/* Register ADDRMAP7 */
/* Address Map Register 7 */
// #define ADDRMAP7 (REGB_ADDR_MAP0_BaseAddress + 0x1c)
#define ADDRMAP7_RegisterSize 32
#define ADDRMAP7_RegisterResetValue 0x0
#define ADDRMAP7_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP7 */

/* Register ADDRMAP7 field addrmap_row_b14 */
/* Selects the HIF address bit used as row address bit 14.

Valid Range: 0 to 15, and 31

Internal Base: 20

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 31 and then row address bit 14 is set to 0. */
#define ADDRMAP7_addrmap_row_b14_BitAddressOffset 0
#define ADDRMAP7_addrmap_row_b14_RegisterSize 5

/* Register ADDRMAP7 field addrmap_row_b15 */
/* Selects the HIF address bit used as row address bit 15.

Valid Range: 0 to 15, and 31

Internal Base: 21

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 31 and then row address bit 15 is set to 0. */
#define ADDRMAP7_addrmap_row_b15_BitAddressOffset 8
#define ADDRMAP7_addrmap_row_b15_RegisterSize 5

/* Register ADDRMAP7 field addrmap_row_b16 */
/* Selects the HIF address bit used as row address bit 16.

Valid Range: 0 to 15, and 31

Internal Base: 22

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 31 and then row address bit 16 is set to 0. */
#define ADDRMAP7_addrmap_row_b16_BitAddressOffset 16
#define ADDRMAP7_addrmap_row_b16_RegisterSize 5

/* Register ADDRMAP7 field addrmap_row_b17 */
/* Selects the HIF address bit used as row address bit 17.

Valid Range: 0 to 15, and 31

Internal Base: 23

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 31 and then row address bit 17 is set to 0. */
#define ADDRMAP7_addrmap_row_b17_BitAddressOffset 24
#define ADDRMAP7_addrmap_row_b17_RegisterSize 5

/* End of Register Definition for ADDRMAP7 */

/* Register ADDRMAP8 */
/* Address Map Register 8 */
// #define ADDRMAP8 (REGB_ADDR_MAP0_BaseAddress + 0x20)
#define ADDRMAP8_RegisterSize 32
#define ADDRMAP8_RegisterResetValue 0x0
#define ADDRMAP8_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP8 */

/* Register ADDRMAP8 field addrmap_row_b10 */
/* Selects the HIF address bits used as row address bit 10.

Valid Range: 0 to 15

Internal Base: 16

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP8_addrmap_row_b10_BitAddressOffset 0
#define ADDRMAP8_addrmap_row_b10_RegisterSize 5

/* Register ADDRMAP8 field addrmap_row_b11 */
/* Selects the HIF address bit used as row address bit 11.

Valid Range: 0 to 15

Internal Base: 17

The selected HIF address bit is determined by adding the internal base to the value of this field.

 */
#define ADDRMAP8_addrmap_row_b11_BitAddressOffset 8
#define ADDRMAP8_addrmap_row_b11_RegisterSize 5

/* Register ADDRMAP8 field addrmap_row_b12 */
/* Selects the HIF address bit used as row address bit 12.

Valid Range: 0 to 15, and 31

Internal Base: 18

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 31 and then row address bit 12 is set to 0. */
#define ADDRMAP8_addrmap_row_b12_BitAddressOffset 16
#define ADDRMAP8_addrmap_row_b12_RegisterSize 5

/* Register ADDRMAP8 field addrmap_row_b13 */
/* Selects the HIF address bit used as row address bit 13.

Valid Range: 0 to 15, and 31

Internal Base: 19

The selected HIF address bit is determined by adding the internal base to the value of this field.

  If unused, set to 31 and then row address bit 13 is set to 0. */
#define ADDRMAP8_addrmap_row_b13_BitAddressOffset 24
#define ADDRMAP8_addrmap_row_b13_RegisterSize 5

/* End of Register Definition for ADDRMAP8 */

/* Register ADDRMAP9 */
/* Address Map Register 9 */
// #define ADDRMAP9 (REGB_ADDR_MAP0_BaseAddress + 0x24)
#define ADDRMAP9_RegisterSize 32
#define ADDRMAP9_RegisterResetValue 0x0
#define ADDRMAP9_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP9 */

/* Register ADDRMAP9 field addrmap_row_b6 */
/* Selects the HIF address bits used as row address bit 6.

Valid Range: 0 to 11

Internal Base: 12

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP9_addrmap_row_b6_BitAddressOffset 0
#define ADDRMAP9_addrmap_row_b6_RegisterSize 5

/* Register ADDRMAP9 field addrmap_row_b7 */
/* Selects the HIF address bits used as row address bit 7.

Valid Range: 0 to 11

Internal Base: 13

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP9_addrmap_row_b7_BitAddressOffset 8
#define ADDRMAP9_addrmap_row_b7_RegisterSize 5

/* Register ADDRMAP9 field addrmap_row_b8 */
/* Selects the HIF address bits used as row address bit 8.

Valid Range: 0 to 11

Internal Base: 14

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP9_addrmap_row_b8_BitAddressOffset 16
#define ADDRMAP9_addrmap_row_b8_RegisterSize 5

/* Register ADDRMAP9 field addrmap_row_b9 */
/* Selects the HIF address bits used as row address bit 9.

Valid Range: 0 to 11

Internal Base: 15

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP9_addrmap_row_b9_BitAddressOffset 24
#define ADDRMAP9_addrmap_row_b9_RegisterSize 5

/* End of Register Definition for ADDRMAP9 */

/* Register ADDRMAP10 */
/* Address Map Register 10 */
// #define ADDRMAP10 (REGB_ADDR_MAP0_BaseAddress + 0x28)
#define ADDRMAP10_RegisterSize 32
#define ADDRMAP10_RegisterResetValue 0x0
#define ADDRMAP10_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP10 */

/* Register ADDRMAP10 field addrmap_row_b2 */
/* Selects the HIF address bits used as row address bit 2.

Valid Range: 0 to 15

Internal Base: 8

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP10_addrmap_row_b2_BitAddressOffset 0
#define ADDRMAP10_addrmap_row_b2_RegisterSize 5

/* Register ADDRMAP10 field addrmap_row_b3 */
/* Selects the HIF address bits used as row address bit 3.

Valid Range: 0 to 15

Internal Base: 9

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP10_addrmap_row_b3_BitAddressOffset 8
#define ADDRMAP10_addrmap_row_b3_RegisterSize 5

/* Register ADDRMAP10 field addrmap_row_b4 */
/* Selects the HIF address bits used as row address bit 4.

Valid Range: 0 to 15

Internal Base: 10

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP10_addrmap_row_b4_BitAddressOffset 16
#define ADDRMAP10_addrmap_row_b4_RegisterSize 5

/* Register ADDRMAP10 field addrmap_row_b5 */
/* Selects the HIF address bits used as row address bit 5.

Valid Range: 0 to 15

Internal Base: 11

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP10_addrmap_row_b5_BitAddressOffset 24
#define ADDRMAP10_addrmap_row_b5_RegisterSize 5

/* End of Register Definition for ADDRMAP10 */

/* Register ADDRMAP11 */
/* Address Map Register 11 */
// #define ADDRMAP11 (REGB_ADDR_MAP0_BaseAddress + 0x2c)
#define ADDRMAP11_RegisterSize 32
#define ADDRMAP11_RegisterResetValue 0x0
#define ADDRMAP11_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP11 */

/* Register ADDRMAP11 field addrmap_row_b0 */
/* Selects the HIF address bits used as row address bit 0.

Valid Range: 0 to 15

Internal Base: 6

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP11_addrmap_row_b0_BitAddressOffset 0
#define ADDRMAP11_addrmap_row_b0_RegisterSize 5

/* Register ADDRMAP11 field addrmap_row_b1 */
/* Selects the HIF address bits used as row address bit 1.

Valid Range: 0 to 15

Internal Base: 7

The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field. */
#define ADDRMAP11_addrmap_row_b1_BitAddressOffset 8
#define ADDRMAP11_addrmap_row_b1_RegisterSize 5

/* End of Register Definition for ADDRMAP11 */

/* Register ADDRMAP12 */
/* Address Map Register 12 */
// #define ADDRMAP12 (REGB_ADDR_MAP0_BaseAddress + 0x30)
#define ADDRMAP12_RegisterSize 32
#define ADDRMAP12_RegisterResetValue 0x0
#define ADDRMAP12_RegisterResetMask 0xffffffff

/* Register Field information for ADDRMAP12 */

/* Register ADDRMAP12 field nonbinary_device_density */
/* 
 Indicates what type of SDRAM device is in use.
 
 - 3'b000: All addresses are valid
 - 3'b001: Every address having row[13:12]==2'b11 is considered as invalid

 - 3'b010: Every address having row[14:13]==2'b11 is considered as invalid

 - 3'b011: Every address having row[15:14]==2'b11 is considered as invalid

 - 3'b100: Every address having row[16:15]==2'b11 is considered as invalid

 - 3'b101: Every address having row[17:16]==2'b11 is considered as invalid

 */
#define ADDRMAP12_nonbinary_device_density_BitAddressOffset 0
#define ADDRMAP12_nonbinary_device_density_RegisterSize 3

/* End of Register Definition for ADDRMAP12 */

#define REGB_ARB_PORT0_BaseAddress 0x20000

/* Register PCCFG */
/* Port Common Configuration Register. */
// #define PCCFG (REGB_ARB_PORT0_BaseAddress + 0x0)
#define PCCFG_RegisterSize 32
#define PCCFG_RegisterResetValue 0x0
#define PCCFG_RegisterResetMask 0xffffffff

/* Register Field information for PCCFG */

/* Register PCCFG field go2critical_en */
/* If set to 1 (enabled), sets co_gs_go2critical_wr and co_gs_go2critical_lpr/co_gs_go2critical_hpr signals going to DDRC based on urgent input (awurgent, arurgent) coming from AXI master. If set to 0 (disabled), co_gs_go2critical_wr and co_gs_go2critical_lpr/co_gs_go2critical_hpr signals at DDRC are driven to 1b'0. */
#define PCCFG_go2critical_en_BitAddressOffset 0
#define PCCFG_go2critical_en_RegisterSize 1

/* Register PCCFG field pagematch_limit */
/* Page match four limit. If set to 1, limits the number of consecutive same page DDRC transactions that can be granted by the Port Arbiter to four when Page Match feature is enabled.       If set to 0, there is no limit imposed on number of consecutive same page DDRC transactions. */
#define PCCFG_pagematch_limit_BitAddressOffset 4
#define PCCFG_pagematch_limit_RegisterSize 1

/* End of Register Definition for PCCFG */

/* Register PCFGR */
/* Configuration Read Register */
// #define PCFGR (REGB_ARB_PORT0_BaseAddress + 0x4)
#define PCFGR_RegisterSize 32
#define PCFGR_RegisterResetValue 0x4000
#define PCFGR_RegisterResetMask 0xffffffff

/* Register Field information for PCFGR */

/* Register PCFGR field rd_port_priority */
/* Determines the initial load value of read aging counters. 	 These counters will be parallel loaded after reset, or after each grant to the corresponding port. 	 The aging counters down-count every clock cycle where the port is requesting but not 
	 granted. The higher significant 5-bits of the read aging counter sets the priority of the 
         read channel of a given port.	 Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. 	 When the aging counter becomes 0, the corresponding port channel will have the highest priority level (timeout condition - Priority0).	 For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority 	 inputs (arqos) are enabled (timeout is still applicable).  	 For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.	 In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority 
	 (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis. 	 

Note: The two LSBs of this register field are tied internally to 2'b00. */
#define PCFGR_rd_port_priority_BitAddressOffset 0
#define PCFGR_rd_port_priority_RegisterSize 10

/* Register PCFGR field read_reorder_bypass_en */
/* If set to 1, read transactions with ID not covered by any of the virtual channel ID mapping registers are not reordered. */
#define PCFGR_read_reorder_bypass_en_BitAddressOffset 11
#define PCFGR_read_reorder_bypass_en_RegisterSize 1

/* Register PCFGR field rd_port_aging_en */
/* If set to 1, enables aging function for the read channel of the port. */
#define PCFGR_rd_port_aging_en_BitAddressOffset 12
#define PCFGR_rd_port_aging_en_RegisterSize 1

/* Register PCFGR field rd_port_urgent_en */
/* If set to 1, enables the AXI urgent sideband signal (arurgent). When enabled and arurgent 	 is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to 	 DDRC is asserted if enabled in PCCFG.go2critical_en register. Note that arurgent signal can be 	 asserted anytime and as long as required which is independent of address handshaking (it is not 	 associated with any particular command). */
#define PCFGR_rd_port_urgent_en_BitAddressOffset 13
#define PCFGR_rd_port_urgent_en_RegisterSize 1

/* Register PCFGR field rd_port_pagematch_en */
/* If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, 	 the port is continued to be granted if the following immediate commands are to the same 	 memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define PCFGR_rd_port_pagematch_en_BitAddressOffset 14
#define PCFGR_rd_port_pagematch_en_RegisterSize 1

/* End of Register Definition for PCFGR */

/* Register PCFGW */
/* Configuration Write Register */
// #define PCFGW (REGB_ARB_PORT0_BaseAddress + 0x8)
#define PCFGW_RegisterSize 32
#define PCFGW_RegisterResetValue 0x4000
#define PCFGW_RegisterResetMask 0xffffffff

/* Register Field information for PCFGW */

/* Register PCFGW field wr_port_priority */
/* Determines the initial load value of write aging counters.	 These counters will be parallel loaded after reset, or after each grant to the corresponding port. 	 The aging counters down-count every clock cycle where the port is requesting but not 	 granted. The higher significant 5-bits of the write aging counter sets the initial priority of the 
         write channel of a given port.	 Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel will have the highest priority level.	 

For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority 	 inputs (awqos) are enabled (timeout is still applicable). 	 

For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching. 	 

Note: The two LSBs of this register field are tied internally to 2'b00. */
#define PCFGW_wr_port_priority_BitAddressOffset 0
#define PCFGW_wr_port_priority_RegisterSize 10

/* Register PCFGW field wr_port_aging_en */
/* If set to 1, enables aging function for the write channel of the port. */
#define PCFGW_wr_port_aging_en_BitAddressOffset 12
#define PCFGW_wr_port_aging_en_RegisterSize 1

/* Register PCFGW field wr_port_urgent_en */
/* If set to 1, enables the AXI urgent sideband signal (awurgent). When enabled and awurgent 	 is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to 	 DDRC is asserted if enabled in PCCFG.go2critical_en register.
 Note that awurgent signal can be 	 asserted anytime and as long as required which is independent of address handshaking (it is not 	 associated with any particular command). */
#define PCFGW_wr_port_urgent_en_BitAddressOffset 13
#define PCFGW_wr_port_urgent_en_RegisterSize 1

/* Register PCFGW field wr_port_pagematch_en */
/* If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, 	 the port is continued to be granted if the following immediate commands are to the same 	 memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define PCFGW_wr_port_pagematch_en_BitAddressOffset 14
#define PCFGW_wr_port_pagematch_en_RegisterSize 1

/* End of Register Definition for PCFGW */

/* Register PCFGIDMASKCH0 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH0 (REGB_ARB_PORT0_BaseAddress + 0x10)
#define PCFGIDMASKCH0_RegisterSize 32
#define PCFGIDMASKCH0_RegisterResetValue 0x0
#define PCFGIDMASKCH0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH0 */

/* Register PCFGIDMASKCH0 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH0_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH0_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH0 */

/* Register PCFGIDVALUECH0 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH0 (REGB_ARB_PORT0_BaseAddress + 0x14)
#define PCFGIDVALUECH0_RegisterSize 32
#define PCFGIDVALUECH0_RegisterResetValue 0x0
#define PCFGIDVALUECH0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH0 */

/* Register PCFGIDVALUECH0 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH0_id_value_BitAddressOffset 0
#define PCFGIDVALUECH0_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH0 */

/* Register PCFGIDMASKCH1 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH1 (REGB_ARB_PORT0_BaseAddress + 0x18)
#define PCFGIDMASKCH1_RegisterSize 32
#define PCFGIDMASKCH1_RegisterResetValue 0x0
#define PCFGIDMASKCH1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH1 */

/* Register PCFGIDMASKCH1 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH1_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH1_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH1 */

/* Register PCFGIDVALUECH1 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH1 (REGB_ARB_PORT0_BaseAddress + 0x1c)
#define PCFGIDVALUECH1_RegisterSize 32
#define PCFGIDVALUECH1_RegisterResetValue 0x0
#define PCFGIDVALUECH1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH1 */

/* Register PCFGIDVALUECH1 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH1_id_value_BitAddressOffset 0
#define PCFGIDVALUECH1_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH1 */

/* Register PCFGIDMASKCH2 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH2 (REGB_ARB_PORT0_BaseAddress + 0x20)
#define PCFGIDMASKCH2_RegisterSize 32
#define PCFGIDMASKCH2_RegisterResetValue 0x0
#define PCFGIDMASKCH2_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH2 */

/* Register PCFGIDMASKCH2 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH2_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH2_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH2 */

/* Register PCFGIDVALUECH2 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH2 (REGB_ARB_PORT0_BaseAddress + 0x24)
#define PCFGIDVALUECH2_RegisterSize 32
#define PCFGIDVALUECH2_RegisterResetValue 0x0
#define PCFGIDVALUECH2_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH2 */

/* Register PCFGIDVALUECH2 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH2_id_value_BitAddressOffset 0
#define PCFGIDVALUECH2_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH2 */

/* Register PCFGIDMASKCH3 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH3 (REGB_ARB_PORT0_BaseAddress + 0x28)
#define PCFGIDMASKCH3_RegisterSize 32
#define PCFGIDMASKCH3_RegisterResetValue 0x0
#define PCFGIDMASKCH3_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH3 */

/* Register PCFGIDMASKCH3 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH3_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH3_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH3 */

/* Register PCFGIDVALUECH3 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH3 (REGB_ARB_PORT0_BaseAddress + 0x2c)
#define PCFGIDVALUECH3_RegisterSize 32
#define PCFGIDVALUECH3_RegisterResetValue 0x0
#define PCFGIDVALUECH3_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH3 */

/* Register PCFGIDVALUECH3 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH3_id_value_BitAddressOffset 0
#define PCFGIDVALUECH3_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH3 */

/* Register PCFGIDMASKCH4 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH4 (REGB_ARB_PORT0_BaseAddress + 0x30)
#define PCFGIDMASKCH4_RegisterSize 32
#define PCFGIDMASKCH4_RegisterResetValue 0x0
#define PCFGIDMASKCH4_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH4 */

/* Register PCFGIDMASKCH4 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH4_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH4_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH4 */

/* Register PCFGIDVALUECH4 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH4 (REGB_ARB_PORT0_BaseAddress + 0x34)
#define PCFGIDVALUECH4_RegisterSize 32
#define PCFGIDVALUECH4_RegisterResetValue 0x0
#define PCFGIDVALUECH4_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH4 */

/* Register PCFGIDVALUECH4 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH4_id_value_BitAddressOffset 0
#define PCFGIDVALUECH4_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH4 */

/* Register PCFGIDMASKCH5 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH5 (REGB_ARB_PORT0_BaseAddress + 0x38)
#define PCFGIDMASKCH5_RegisterSize 32
#define PCFGIDMASKCH5_RegisterResetValue 0x0
#define PCFGIDMASKCH5_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH5 */

/* Register PCFGIDMASKCH5 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH5_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH5_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH5 */

/* Register PCFGIDVALUECH5 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH5 (REGB_ARB_PORT0_BaseAddress + 0x3c)
#define PCFGIDVALUECH5_RegisterSize 32
#define PCFGIDVALUECH5_RegisterResetValue 0x0
#define PCFGIDVALUECH5_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH5 */

/* Register PCFGIDVALUECH5 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH5_id_value_BitAddressOffset 0
#define PCFGIDVALUECH5_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH5 */

/* Register PCFGIDMASKCH6 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH6 (REGB_ARB_PORT0_BaseAddress + 0x40)
#define PCFGIDMASKCH6_RegisterSize 32
#define PCFGIDMASKCH6_RegisterResetValue 0x0
#define PCFGIDMASKCH6_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH6 */

/* Register PCFGIDMASKCH6 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH6_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH6_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH6 */

/* Register PCFGIDVALUECH6 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH6 (REGB_ARB_PORT0_BaseAddress + 0x44)
#define PCFGIDVALUECH6_RegisterSize 32
#define PCFGIDVALUECH6_RegisterResetValue 0x0
#define PCFGIDVALUECH6_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH6 */

/* Register PCFGIDVALUECH6 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH6_id_value_BitAddressOffset 0
#define PCFGIDVALUECH6_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH6 */

/* Register PCFGIDMASKCH7 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH7 (REGB_ARB_PORT0_BaseAddress + 0x48)
#define PCFGIDMASKCH7_RegisterSize 32
#define PCFGIDMASKCH7_RegisterResetValue 0x0
#define PCFGIDMASKCH7_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH7 */

/* Register PCFGIDMASKCH7 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH7_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH7_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH7 */

/* Register PCFGIDVALUECH7 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH7 (REGB_ARB_PORT0_BaseAddress + 0x4c)
#define PCFGIDVALUECH7_RegisterSize 32
#define PCFGIDVALUECH7_RegisterResetValue 0x0
#define PCFGIDVALUECH7_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH7 */

/* Register PCFGIDVALUECH7 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH7_id_value_BitAddressOffset 0
#define PCFGIDVALUECH7_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH7 */

/* Register PCFGIDMASKCH8 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH8 (REGB_ARB_PORT0_BaseAddress + 0x50)
#define PCFGIDMASKCH8_RegisterSize 32
#define PCFGIDMASKCH8_RegisterResetValue 0x0
#define PCFGIDMASKCH8_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH8 */

/* Register PCFGIDMASKCH8 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH8_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH8_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH8 */

/* Register PCFGIDVALUECH8 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH8 (REGB_ARB_PORT0_BaseAddress + 0x54)
#define PCFGIDVALUECH8_RegisterSize 32
#define PCFGIDVALUECH8_RegisterResetValue 0x0
#define PCFGIDVALUECH8_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH8 */

/* Register PCFGIDVALUECH8 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH8_id_value_BitAddressOffset 0
#define PCFGIDVALUECH8_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH8 */

/* Register PCFGIDMASKCH9 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH9 (REGB_ARB_PORT0_BaseAddress + 0x58)
#define PCFGIDMASKCH9_RegisterSize 32
#define PCFGIDMASKCH9_RegisterResetValue 0x0
#define PCFGIDMASKCH9_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH9 */

/* Register PCFGIDMASKCH9 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH9_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH9_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH9 */

/* Register PCFGIDVALUECH9 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH9 (REGB_ARB_PORT0_BaseAddress + 0x5c)
#define PCFGIDVALUECH9_RegisterSize 32
#define PCFGIDVALUECH9_RegisterResetValue 0x0
#define PCFGIDVALUECH9_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH9 */

/* Register PCFGIDVALUECH9 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH9_id_value_BitAddressOffset 0
#define PCFGIDVALUECH9_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH9 */

/* Register PCFGIDMASKCH10 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH10 (REGB_ARB_PORT0_BaseAddress + 0x60)
#define PCFGIDMASKCH10_RegisterSize 32
#define PCFGIDMASKCH10_RegisterResetValue 0x0
#define PCFGIDMASKCH10_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH10 */

/* Register PCFGIDMASKCH10 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH10_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH10_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH10 */

/* Register PCFGIDVALUECH10 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH10 (REGB_ARB_PORT0_BaseAddress + 0x64)
#define PCFGIDVALUECH10_RegisterSize 32
#define PCFGIDVALUECH10_RegisterResetValue 0x0
#define PCFGIDVALUECH10_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH10 */

/* Register PCFGIDVALUECH10 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH10_id_value_BitAddressOffset 0
#define PCFGIDVALUECH10_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH10 */

/* Register PCFGIDMASKCH11 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH11 (REGB_ARB_PORT0_BaseAddress + 0x68)
#define PCFGIDMASKCH11_RegisterSize 32
#define PCFGIDMASKCH11_RegisterResetValue 0x0
#define PCFGIDMASKCH11_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH11 */

/* Register PCFGIDMASKCH11 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH11_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH11_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH11 */

/* Register PCFGIDVALUECH11 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH11 (REGB_ARB_PORT0_BaseAddress + 0x6c)
#define PCFGIDVALUECH11_RegisterSize 32
#define PCFGIDVALUECH11_RegisterResetValue 0x0
#define PCFGIDVALUECH11_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH11 */

/* Register PCFGIDVALUECH11 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH11_id_value_BitAddressOffset 0
#define PCFGIDVALUECH11_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH11 */

/* Register PCFGIDMASKCH12 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH12 (REGB_ARB_PORT0_BaseAddress + 0x70)
#define PCFGIDMASKCH12_RegisterSize 32
#define PCFGIDMASKCH12_RegisterResetValue 0x0
#define PCFGIDMASKCH12_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH12 */

/* Register PCFGIDMASKCH12 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH12_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH12_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH12 */

/* Register PCFGIDVALUECH12 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH12 (REGB_ARB_PORT0_BaseAddress + 0x74)
#define PCFGIDVALUECH12_RegisterSize 32
#define PCFGIDVALUECH12_RegisterResetValue 0x0
#define PCFGIDVALUECH12_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH12 */

/* Register PCFGIDVALUECH12 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH12_id_value_BitAddressOffset 0
#define PCFGIDVALUECH12_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH12 */

/* Register PCFGIDMASKCH13 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH13 (REGB_ARB_PORT0_BaseAddress + 0x78)
#define PCFGIDMASKCH13_RegisterSize 32
#define PCFGIDMASKCH13_RegisterResetValue 0x0
#define PCFGIDMASKCH13_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH13 */

/* Register PCFGIDMASKCH13 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH13_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH13_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH13 */

/* Register PCFGIDVALUECH13 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH13 (REGB_ARB_PORT0_BaseAddress + 0x7c)
#define PCFGIDVALUECH13_RegisterSize 32
#define PCFGIDVALUECH13_RegisterResetValue 0x0
#define PCFGIDVALUECH13_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH13 */

/* Register PCFGIDVALUECH13 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH13_id_value_BitAddressOffset 0
#define PCFGIDVALUECH13_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH13 */

/* Register PCFGIDMASKCH14 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH14 (REGB_ARB_PORT0_BaseAddress + 0x80)
#define PCFGIDMASKCH14_RegisterSize 32
#define PCFGIDMASKCH14_RegisterResetValue 0x0
#define PCFGIDMASKCH14_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH14 */

/* Register PCFGIDMASKCH14 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH14_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH14_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH14 */

/* Register PCFGIDVALUECH14 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH14 (REGB_ARB_PORT0_BaseAddress + 0x84)
#define PCFGIDVALUECH14_RegisterSize 32
#define PCFGIDVALUECH14_RegisterResetValue 0x0
#define PCFGIDVALUECH14_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH14 */

/* Register PCFGIDVALUECH14 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH14_id_value_BitAddressOffset 0
#define PCFGIDVALUECH14_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH14 */

/* Register PCFGIDMASKCH15 */
/* Channel c Configuration ID mask register */
// #define PCFGIDMASKCH15 (REGB_ARB_PORT0_BaseAddress + 0x88)
#define PCFGIDMASKCH15_RegisterSize 32
#define PCFGIDMASKCH15_RegisterResetValue 0x0
#define PCFGIDMASKCH15_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDMASKCH15 */

/* Register PCFGIDMASKCH15 field id_mask */
/* Determines the mask used in the ID mapping function for virtual channel m. */
#define PCFGIDMASKCH15_id_mask_BitAddressOffset 0
#define PCFGIDMASKCH15_id_mask_RegisterSize 6

/* End of Register Definition for PCFGIDMASKCH15 */

/* Register PCFGIDVALUECH15 */
/* Channel c Configuration ID value register */
// #define PCFGIDVALUECH15 (REGB_ARB_PORT0_BaseAddress + 0x8c)
#define PCFGIDVALUECH15_RegisterSize 32
#define PCFGIDVALUECH15_RegisterResetValue 0x0
#define PCFGIDVALUECH15_RegisterResetMask 0xffffffff

/* Register Field information for PCFGIDVALUECH15 */

/* Register PCFGIDVALUECH15 field id_value */
/* Determines the value used in the ID mapping function for virtual channel m. */
#define PCFGIDVALUECH15_id_value_BitAddressOffset 0
#define PCFGIDVALUECH15_id_value_RegisterSize 6

/* End of Register Definition for PCFGIDVALUECH15 */

/* Register PCTRL */
/* Port  Control Register */
// #define PCTRL (REGB_ARB_PORT0_BaseAddress + 0x90)
#define PCTRL_RegisterSize 32
#define PCTRL_RegisterResetValue 0x0
#define PCTRL_RegisterResetMask 0xffffffff

/* Register Field information for PCTRL */

/* Register PCTRL field port_en */
/* Enables AXI port n. */
#define PCTRL_port_en_BitAddressOffset 0
#define PCTRL_port_en_RegisterSize 1

/* End of Register Definition for PCTRL */

/* Register PCFGQOS0 */
/* Port n Read QoS Configuration Register 0 */
// #define PCFGQOS0 (REGB_ARB_PORT0_BaseAddress + 0x94)
#define PCFGQOS0_RegisterSize 32
#define PCFGQOS0_RegisterResetValue 0x2000e00
#define PCFGQOS0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGQOS0 */

/* Register PCFGQOS0 field rqos_map_level1 */
/* Separation level1 indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.          

Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGQOS0_rqos_map_level1_BitAddressOffset 0
#define PCFGQOS0_rqos_map_level1_RegisterSize 4

/* Register PCFGQOS0 field rqos_map_level2 */
/* Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to arqos.
	 Region2 starts from (level2 + 1) up to 15.
 Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGQOS0_rqos_map_level2_BitAddressOffset 8
#define PCFGQOS0_rqos_map_level2_RegisterSize 4

/* Register PCFGQOS0 field rqos_map_region0 */
/* This bitfield indicates the traffic class of region 0.
 Valid values are:
 - 0: LPR
 - 1: VPR
 - 2: HPR
For dual address queue configurations, region 0 maps to the blue address queue.
 In this case, valid values are: 

0: LPR and 1: VPR only.
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region0_BitAddressOffset 16
#define PCFGQOS0_rqos_map_region0_RegisterSize 2

/* Register PCFGQOS0 field rqos_map_region1 */
/* This bitfield indicates the traffic class of region 1.
 Valid values are:
 - 0 : LPR
 - 1: VPR
 - 2: HPR
 For dual address queue configurations, region1 maps to the blue address queue.
 In this case, valid values are 
 - 0: LPR
 - 1: VPR only
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region1_BitAddressOffset 20
#define PCFGQOS0_rqos_map_region1_RegisterSize 2

/* Register PCFGQOS0 field rqos_map_region2 */
/* This bitfield indicates the traffic class of region2.
 For dual address queue configurations, region2 maps to the red address queue.
 Valid values are 1: VPR and 2: HPR only.
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region2 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region2_BitAddressOffset 24
#define PCFGQOS0_rqos_map_region2_RegisterSize 2

/* End of Register Definition for PCFGQOS0 */

/* Register PCFGQOS1 */
/* Port n Read QoS Configuration Register 1 */
// #define PCFGQOS1 (REGB_ARB_PORT0_BaseAddress + 0x98)
#define PCFGQOS1_RegisterSize 32
#define PCFGQOS1_RegisterResetValue 0x0
#define PCFGQOS1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGQOS1 */

/* Register PCFGQOS1 field rqos_map_timeoutb */
/* Specifies the timeout value for transactions mapped to the blue address queue. */
#define PCFGQOS1_rqos_map_timeoutb_BitAddressOffset 0
#define PCFGQOS1_rqos_map_timeoutb_RegisterSize 11

/* Register PCFGQOS1 field rqos_map_timeoutr */
/* Specifies the timeout value for transactions mapped to the red address queue. */
#define PCFGQOS1_rqos_map_timeoutr_BitAddressOffset 16
#define PCFGQOS1_rqos_map_timeoutr_RegisterSize 11

/* End of Register Definition for PCFGQOS1 */

/* Register PCFGWQOS0 */
/* Port n Write QoS Configuration Register 0 */
// #define PCFGWQOS0 (REGB_ARB_PORT0_BaseAddress + 0x9c)
#define PCFGWQOS0_RegisterSize 32
#define PCFGWQOS0_RegisterResetValue 0xe00
#define PCFGWQOS0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGWQOS0 */

/* Register PCFGWQOS0 field wqos_map_level1 */
/* Separation level indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 which corresponds to awqos.
 Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGWQOS0_wqos_map_level1_BitAddressOffset 0
#define PCFGWQOS0_wqos_map_level1_RegisterSize 4

/* Register PCFGWQOS0 field wqos_map_level2 */
/* Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to awqos.
 Region2 starts from (level2 + 1) up to 15.
 Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGWQOS0_wqos_map_level2_BitAddressOffset 8
#define PCFGWQOS0_wqos_map_level2_RegisterSize 4

/* Register PCFGWQOS0 field wqos_map_region0 */
/* This bitfield indicates the traffic class of region 0.

	  Valid values are: 

	  0: NPW, 1: VPW. 

     When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 0 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region0_BitAddressOffset 16
#define PCFGWQOS0_wqos_map_region0_RegisterSize 2

/* Register PCFGWQOS0 field wqos_map_region1 */
/* This bitfield indicates the traffic class of region 1.
 Valid values are:
 0: NPW, 1: VPW.
 When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 1 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region1_BitAddressOffset 20
#define PCFGWQOS0_wqos_map_region1_RegisterSize 2

/* Register PCFGWQOS0 field wqos_map_region2 */
/* This bitfield indicates the traffic class of region 2.
 Valid values are:
 0: NPW, 1: VPW.
 When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 2 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region2_BitAddressOffset 24
#define PCFGWQOS0_wqos_map_region2_RegisterSize 2

/* End of Register Definition for PCFGWQOS0 */

/* Register PCFGWQOS1 */
/* Port n Write QoS Configuration Register 1 */
// #define PCFGWQOS1 (REGB_ARB_PORT0_BaseAddress + 0xa0)
#define PCFGWQOS1_RegisterSize 32
#define PCFGWQOS1_RegisterResetValue 0x0
#define PCFGWQOS1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGWQOS1 */

/* Register PCFGWQOS1 field wqos_map_timeout1 */
/* Specifies the timeout value for write transactions in region 0 and 1. */
#define PCFGWQOS1_wqos_map_timeout1_BitAddressOffset 0
#define PCFGWQOS1_wqos_map_timeout1_RegisterSize 11

/* Register PCFGWQOS1 field wqos_map_timeout2 */
/* Specifies the timeout value for write transactions in region 2. */
#define PCFGWQOS1_wqos_map_timeout2_BitAddressOffset 16
#define PCFGWQOS1_wqos_map_timeout2_RegisterSize 11

/* End of Register Definition for PCFGWQOS1 */

/* Register SARBASE0 */
/* SAR Base Address Register s. */
// #define SARBASE0 (REGB_ARB_PORT0_BaseAddress + 0xc0)
#define SARBASE0_RegisterSize 32
#define SARBASE0_RegisterResetValue 0x0
#define SARBASE0_RegisterResetMask 0xffffffff

/* Register Field information for SARBASE0 */

/* Register SARBASE0 field base_addr */
/* Base address for address region n specified as awaddr[UMCTL2_A_ADDRW-1:x] and araddr[UMCTL2_A_ADDRW-1:x] 

where x is determined by the minimum block size parameter UMCTL2_SARMINSIZE: (x=log2(block size)). */
#define SARBASE0_base_addr_BitAddressOffset 0
#define SARBASE0_base_addr_RegisterSize 6

/* End of Register Definition for SARBASE0 */

/* Register SARSIZE0 */
/* SAR Size Register s. */
// #define SARSIZE0 (REGB_ARB_PORT0_BaseAddress + 0xc4)
#define SARSIZE0_RegisterSize 32
#define SARSIZE0_RegisterResetValue 0x0
#define SARSIZE0_RegisterResetMask 0xffffffff

/* Register Field information for SARSIZE0 */

/* Register SARSIZE0 field nblocks */
/* Number of blocks for address region n.
 This register determines the total size of the region in multiples of minimum block size as specified by the hardware parameter UMCTL2_SARMINSIZE.     The register value is encoded as number of blocks = nblocks + 1. For example, if register is programmed to 0, region will have 1 block. */
#define SARSIZE0_nblocks_BitAddressOffset 0
#define SARSIZE0_nblocks_RegisterSize 8

/* End of Register Definition for SARSIZE0 */

/* Register SBRCTL */
/* Scrubber Control Register */
// #define SBRCTL (REGB_ARB_PORT0_BaseAddress + 0xe0)
#define SBRCTL_RegisterSize 32
#define SBRCTL_RegisterResetValue 0x1100ff10
#define SBRCTL_RegisterResetMask 0xffffffff

/* Register Field information for SBRCTL */

/* Register SBRCTL field scrub_en */
/* Enable ECC scrubber. 

If set to 1, enables the scrubber to generate background read commands after the memories are initialized.
 If set to 0, disables the scrubber, resets the address generator to 0 
     and clears the scrubber status.
 This bitfield must be accessed separately from the other bitfields in this register. */
#define SBRCTL_scrub_en_BitAddressOffset 0
#define SBRCTL_scrub_en_RegisterSize 1

/* Register SBRCTL field scrub_during_lowpower */
/* Continue scrubbing during low power.
 If set to 1, burst of scrubs will be issued in HW controlled low power modes. There are two such modes: automatically initiated by idleness or initiated by Hardware low power interface.
 If set to 0, the scrubber will not attempt to send commands while the DDRC is in HW controlled low power modes. In this case, the scrubber will remember the last address issued and will automatically continue from there when the DDRC exits the LP mode. */
#define SBRCTL_scrub_during_lowpower_BitAddressOffset 1
#define SBRCTL_scrub_during_lowpower_RegisterSize 1

/* Register SBRCTL field scrub_burst_length_normal */
/* Scrub burst length in normal mode.
?Determines the number of back-to-back scrub read commands that can be issued together when the controller is in normal operation in Inline ECC & Sideband ECC.
?The period of the scrub burst becomes "scrub_burst_length_normal*scrub_interval" cycles.
During normal operation mode of the controller with Sideband ECC (not in power-down or self refresh), scrub_burst_length_normal is ignored and only one scrub command is generated.

Valid values are 

(Sideband ECC): 1: 1 read 

(Inline ECC): 1: 8 reads, 2: 16 reads, 3: 32 reads. 

In Sideband ECC, software must ensure that the scrub_burst_length_normal is programmed to the value of 1.  Other values are not supported.

To program a new value to this register field, first disable Scrubber by setting SBRCTL.scrub_en = 0. Program the new value.Enable Scrubber by setting SBRCTL.scrub_en = 1.

Please note that both scrub_burst_length_normal & SBRCTL.scrub_burst_length_lp must be programmed to the same value. */
#define SBRCTL_scrub_burst_length_normal_BitAddressOffset 4
#define SBRCTL_scrub_burst_length_normal_RegisterSize 3

/* Register SBRCTL field scrub_interval */
/* Scrub interval. (512 x scrub_interval) number of clock cycles between two scrub read commands. If set to 0, scrub commands are issued back-to-back. This mode of operation (scrub_interval=0) can typically be used for scrubbing the full range of memory at once before or after SW controlled low power operations. After completing the full range of scrub while scrub_interval=0, scrub_done register is set and sbr_done_intr interrupt signal is asserted. 
     This mode can't be used with Inline ECC: If MEMC_INLINE_ECC is 1 and scrub_interval is programme to 0, then RMW logic inside scrubber is disabled.
     New programmed value will take effect only after scrubber is disabled by programming scrub_en to 0.

Unit: Multiples of 512 sbr_clk cycles. */
#define SBRCTL_scrub_interval_BitAddressOffset 8
#define SBRCTL_scrub_interval_RegisterSize 13

/* Register SBRCTL field scrub_cmd_type */
/* scrub_cmd_type:0 ECC scrubber will perform reads 
 scrub_cmd_type:1 ECC scrubber will perform writes */
#define SBRCTL_scrub_cmd_type_BitAddressOffset 24
#define SBRCTL_scrub_cmd_type_RegisterSize 2

/* Register SBRCTL field scrub_burst_length_lp */
/* Scrub burst length in Low Power mode

?Determines the number of back-to-back scrub read commands that can be issued together when the controller is in one of the HW controlled low power modes with Sideband ECC and Inline ECC. 

?During these modes, the period of the scrub burst becomes "scrub_burst_length_lp*scrub_interval" cycles. 

Valid values are 

(Sideband ECC): 1: 1 read, 2: 4 reads, 3: 16 reads, 4: 64 reads, 5: 256 reads, 6: 1024 reads.
 
(Inline ECC): 1: 8 reads, 2: 16 reads, 3: 32 reads.

To program a new value to this register field, first disable Scrubber by setting SBRCTL.scrub_en = 0. Program the new value.Enable Scrubber by setting SBRCTL.scrub_en = 1. */
#define SBRCTL_scrub_burst_length_lp_BitAddressOffset 28
#define SBRCTL_scrub_burst_length_lp_RegisterSize 3

/* End of Register Definition for SBRCTL */

/* Register SBRSTAT */
/* Scrubber Status Register */
// #define SBRSTAT (REGB_ARB_PORT0_BaseAddress + 0xe4)
#define SBRSTAT_RegisterSize 32
#define SBRSTAT_RegisterResetValue 0x0
#define SBRSTAT_RegisterResetMask 0xffffffff

/* Register Field information for SBRSTAT */

/* Register SBRSTAT field scrub_busy */
/* Scrubber busy. Controller sets this bit to 1 when the scrubber logic has outstanding read commands being executed. Cleared when there are no active outstanding scrub reads in the system. */
#define SBRSTAT_scrub_busy_BitAddressOffset 0
#define SBRSTAT_scrub_busy_RegisterSize 1

/* Register SBRSTAT field scrub_done */
/* Scrubber done. Controller sets this bit to 1, after full range of addresses are scrubbed once while scrub_interval is set to 0. Cleared if scrub_en is set to 0 (scrubber disabled) or scrub_interval is set to a non-zero value for normal scrub operation. The interrupt signal, sbr_done_intr, is equivalent to this status bitfield. */
#define SBRSTAT_scrub_done_BitAddressOffset 1
#define SBRSTAT_scrub_done_RegisterSize 1

/* End of Register Definition for SBRSTAT */

/* Register SBRWDATA0 */
/* Scrubber Write Data Pattern0 */
// #define SBRWDATA0 (REGB_ARB_PORT0_BaseAddress + 0xe8)
#define SBRWDATA0_RegisterSize 32
#define SBRWDATA0_RegisterResetValue 0x0
#define SBRWDATA0_RegisterResetMask 0xffffffff

/* Register Field information for SBRWDATA0 */

/* Register SBRWDATA0 field scrub_pattern0 */
/* ECC Scrubber write data pattern for data bus[31:0] */
#define SBRWDATA0_scrub_pattern0_BitAddressOffset 0
#define SBRWDATA0_scrub_pattern0_RegisterSize 32

/* End of Register Definition for SBRWDATA0 */

/* Register SBRSTART0 */
/* Scrubber Start Address Mask Register 0 */
// #define SBRSTART0 (REGB_ARB_PORT0_BaseAddress + 0xf0)
#define SBRSTART0_RegisterSize 32
#define SBRSTART0_RegisterResetValue 0x0
#define SBRSTART0_RegisterResetMask 0xffffffff

/* Register Field information for SBRSTART0 */

/* Register SBRSTART0 field sbr_address_start_mask_0 */
/* sbr_address_start_mask_0 holds the bits [31:0] of the starting address the ECC scrubber generates. The register must be programmed as explained in Address Configuration in ECC Scrub and Scrubber. The scrubber address registers are changed only when the scrubber is disabled (SBRCTL.scrub_en = 0) and there are no scrubber commands in progress (SBRSTAT.scrub_busy = 0). */
#define SBRSTART0_sbr_address_start_mask_0_BitAddressOffset 0
#define SBRSTART0_sbr_address_start_mask_0_RegisterSize 32

/* End of Register Definition for SBRSTART0 */

/* Register SBRSTART1 */
/* Scrubber Start Address Mask Register 1 */
// #define SBRSTART1 (REGB_ARB_PORT0_BaseAddress + 0xf4)
#define SBRSTART1_RegisterSize 32
#define SBRSTART1_RegisterResetValue 0x0
#define SBRSTART1_RegisterResetMask 0xffffffff

/* Register Field information for SBRSTART1 */

/* Register SBRSTART1 field sbr_address_start_mask_1 */
/* sbr_address_start_mask_1 holds bits [MEMC_HIF_ADDR_WIDTH_MAX-1:32] of the starting address the ECC scrubber generates.The register must be programmed as explained in Address Configuration in ECC Scrub and Scrubber. The scrubber address registers are changed only when the scrubber is disabled (SBRCTL.scrub_en = 0) and there are no scrubber commands in progress (SBRSTAT.scrub_busy = 0). */
#define SBRSTART1_sbr_address_start_mask_1_BitAddressOffset 0
#define SBRSTART1_sbr_address_start_mask_1_RegisterSize 7

/* End of Register Definition for SBRSTART1 */

/* Register SBRRANGE0 */
/* Scrubber Address Range Mask Register 0 */
// #define SBRRANGE0 (REGB_ARB_PORT0_BaseAddress + 0xf8)
#define SBRRANGE0_RegisterSize 32
#define SBRRANGE0_RegisterResetValue 0x0
#define SBRRANGE0_RegisterResetMask 0xffffffff

/* Register Field information for SBRRANGE0 */

/* Register SBRRANGE0 field sbr_address_range_mask_0 */
/* sbr_address_range_mask_0 holds the bits [31:0] of the scrubber address range mask. The scrubber address range mask limits the address range that the ECC scrubber can generate.The register must be programmed as explained in Address Configuration in ECC Scrub and Scrubber. The scrubber address registers are changed only when the scrubber is disabled (SBRCTL.scrub_en = 0) and there are no scrubber commands in progress (SBRSTAT.scrub_busy = 0). */
#define SBRRANGE0_sbr_address_range_mask_0_BitAddressOffset 0
#define SBRRANGE0_sbr_address_range_mask_0_RegisterSize 32

/* End of Register Definition for SBRRANGE0 */

/* Register SBRRANGE1 */
/* Scrubber Address Range Mask Register 1 */
// #define SBRRANGE1 (REGB_ARB_PORT0_BaseAddress + 0xfc)
#define SBRRANGE1_RegisterSize 32
#define SBRRANGE1_RegisterResetValue 0x0
#define SBRRANGE1_RegisterResetMask 0xffffffff

/* Register Field information for SBRRANGE1 */

/* Register SBRRANGE1 field sbr_address_range_mask_1 */
/* sbr_address_range_mask_1 holds the bits [MEMC_HIF_ADDR_WIDTH_MAX-1:32] of the scrubber address range mask. The scrubber address range mask limits the address range that the ECC scrubber can generate.The register must be programmed as explained in Address Configuration in ECC Scrub and Scrubber. The scrubber address registers are changed only when the scrubber is disabled (SBRCTL.scrub_en = 0) and there are no scrubber commands in progress (SBRSTAT.scrub_busy = 0). */
#define SBRRANGE1_sbr_address_range_mask_1_BitAddressOffset 0
#define SBRRANGE1_sbr_address_range_mask_1_RegisterSize 7

/* End of Register Definition for SBRRANGE1 */

/* Register PSTAT */
/* Port Status Register */
// #define PSTAT (REGB_ARB_PORT0_BaseAddress + 0x114)
#define PSTAT_RegisterSize 32
#define PSTAT_RegisterResetValue 0x0
#define PSTAT_RegisterResetMask 0xffffffff

/* Register Field information for PSTAT */

/* Register PSTAT field rd_port_busy_0 */
/* Indicates if there are outstanding reads for AXI port 0. */
#define PSTAT_rd_port_busy_0_BitAddressOffset 0
#define PSTAT_rd_port_busy_0_RegisterSize 1

/* Register PSTAT field rd_port_busy_1 */
/* Indicates if there are outstanding reads for AXI port 1. */
#define PSTAT_rd_port_busy_1_BitAddressOffset 1
#define PSTAT_rd_port_busy_1_RegisterSize 1

/* Register PSTAT field rd_port_busy_2 */
/* Indicates if there are outstanding reads for AXI port 2. */
#define PSTAT_rd_port_busy_2_BitAddressOffset 2
#define PSTAT_rd_port_busy_2_RegisterSize 1

/* Register PSTAT field rd_port_busy_3 */
/* Indicates if there are outstanding reads for AXI port 3. */
#define PSTAT_rd_port_busy_3_BitAddressOffset 3
#define PSTAT_rd_port_busy_3_RegisterSize 1

/* Register PSTAT field wr_port_busy_0 */
/* Indicates if there are outstanding writes for AXI port 0. */
#define PSTAT_wr_port_busy_0_BitAddressOffset 16
#define PSTAT_wr_port_busy_0_RegisterSize 1

/* Register PSTAT field wr_port_busy_1 */
/* Indicates if there are outstanding writes for AXI port 1. */
#define PSTAT_wr_port_busy_1_BitAddressOffset 17
#define PSTAT_wr_port_busy_1_RegisterSize 1

/* Register PSTAT field wr_port_busy_2 */
/* Indicates if there are outstanding writes for AXI port 2. */
#define PSTAT_wr_port_busy_2_BitAddressOffset 18
#define PSTAT_wr_port_busy_2_RegisterSize 1

/* Register PSTAT field wr_port_busy_3 */
/* Indicates if there are outstanding writes for AXI port 3. */
#define PSTAT_wr_port_busy_3_BitAddressOffset 19
#define PSTAT_wr_port_busy_3_RegisterSize 1

/* End of Register Definition for PSTAT */

#define REGB_ARB_PORT1_BaseAddress 0x21000

#if 0
/* Register PCFGR */
/* Configuration Read Register */
// #define PCFGR (REGB_ARB_PORT1_BaseAddress + 0x4)
#define PCFGR_RegisterSize 32
#define PCFGR_RegisterResetValue 0x4000
#define PCFGR_RegisterResetMask 0xffffffff

/* Register Field information for PCFGR */

/* Register PCFGR field rd_port_priority */
/* Determines the initial load value of read aging counters. 	 These counters will be parallel loaded after reset, or after each grant to the corresponding port. 	 The aging counters down-count every clock cycle where the port is requesting but not 
	 granted. The higher significant 5-bits of the read aging counter sets the priority of the 
         read channel of a given port.	 Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. 	 When the aging counter becomes 0, the corresponding port channel will have the highest priority level (timeout condition - Priority0).	 For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority 	 inputs (arqos) are enabled (timeout is still applicable).  	 For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.	 In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority 
	 (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis. 	 

Note: The two LSBs of this register field are tied internally to 2'b00. */
#define PCFGR_rd_port_priority_BitAddressOffset 0
#define PCFGR_rd_port_priority_RegisterSize 10

/* Register PCFGR field rd_port_aging_en */
/* If set to 1, enables aging function for the read channel of the port. */
#define PCFGR_rd_port_aging_en_BitAddressOffset 12
#define PCFGR_rd_port_aging_en_RegisterSize 1

/* Register PCFGR field rd_port_urgent_en */
/* If set to 1, enables the AXI urgent sideband signal (arurgent). When enabled and arurgent 	 is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to 	 DDRC is asserted if enabled in PCCFG.go2critical_en register. Note that arurgent signal can be 	 asserted anytime and as long as required which is independent of address handshaking (it is not 	 associated with any particular command). */
#define PCFGR_rd_port_urgent_en_BitAddressOffset 13
#define PCFGR_rd_port_urgent_en_RegisterSize 1

/* Register PCFGR field rd_port_pagematch_en */
/* If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, 	 the port is continued to be granted if the following immediate commands are to the same 	 memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define PCFGR_rd_port_pagematch_en_BitAddressOffset 14
#define PCFGR_rd_port_pagematch_en_RegisterSize 1

/* End of Register Definition for PCFGR */

/* Register PCFGW */
/* Configuration Write Register */
// #define PCFGW (REGB_ARB_PORT1_BaseAddress + 0x8)
#define PCFGW_RegisterSize 32
#define PCFGW_RegisterResetValue 0x4000
#define PCFGW_RegisterResetMask 0xffffffff

/* Register Field information for PCFGW */

/* Register PCFGW field wr_port_priority */
/* Determines the initial load value of write aging counters.	 These counters will be parallel loaded after reset, or after each grant to the corresponding port. 	 The aging counters down-count every clock cycle where the port is requesting but not 	 granted. The higher significant 5-bits of the write aging counter sets the initial priority of the 
         write channel of a given port.	 Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel will have the highest priority level.	 

For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority 	 inputs (awqos) are enabled (timeout is still applicable). 	 

For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching. 	 

Note: The two LSBs of this register field are tied internally to 2'b00. */
#define PCFGW_wr_port_priority_BitAddressOffset 0
#define PCFGW_wr_port_priority_RegisterSize 10

/* Register PCFGW field wr_port_aging_en */
/* If set to 1, enables aging function for the write channel of the port. */
#define PCFGW_wr_port_aging_en_BitAddressOffset 12
#define PCFGW_wr_port_aging_en_RegisterSize 1

/* Register PCFGW field wr_port_urgent_en */
/* If set to 1, enables the AXI urgent sideband signal (awurgent). When enabled and awurgent 	 is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to 	 DDRC is asserted if enabled in PCCFG.go2critical_en register.
 Note that awurgent signal can be 	 asserted anytime and as long as required which is independent of address handshaking (it is not 	 associated with any particular command). */
#define PCFGW_wr_port_urgent_en_BitAddressOffset 13
#define PCFGW_wr_port_urgent_en_RegisterSize 1

/* Register PCFGW field wr_port_pagematch_en */
/* If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, 	 the port is continued to be granted if the following immediate commands are to the same 	 memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define PCFGW_wr_port_pagematch_en_BitAddressOffset 14
#define PCFGW_wr_port_pagematch_en_RegisterSize 1

/* End of Register Definition for PCFGW */

/* Register PCTRL */
/* Port  Control Register */
// #define PCTRL (REGB_ARB_PORT1_BaseAddress + 0x90)
#define PCTRL_RegisterSize 32
#define PCTRL_RegisterResetValue 0x0
#define PCTRL_RegisterResetMask 0xffffffff

/* Register Field information for PCTRL */

/* Register PCTRL field port_en */
/* Enables AXI port n. */
#define PCTRL_port_en_BitAddressOffset 0
#define PCTRL_port_en_RegisterSize 1

/* End of Register Definition for PCTRL */

/* Register PCFGQOS0 */
/* Port n Read QoS Configuration Register 0 */
// #define PCFGQOS0 (REGB_ARB_PORT1_BaseAddress + 0x94)
#define PCFGQOS0_RegisterSize 32
#define PCFGQOS0_RegisterResetValue 0x0
#define PCFGQOS0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGQOS0 */

/* Register PCFGQOS0 field rqos_map_level1 */
/* Separation level1 indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.          

Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGQOS0_rqos_map_level1_BitAddressOffset 0
#define PCFGQOS0_rqos_map_level1_RegisterSize 4

/* Register PCFGQOS0 field rqos_map_region0 */
/* This bitfield indicates the traffic class of region 0.
 Valid values are:
 - 0: LPR
 - 1: VPR
 - 2: HPR
For dual address queue configurations, region 0 maps to the blue address queue.
 In this case, valid values are: 

0: LPR and 1: VPR only.
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region0_BitAddressOffset 16
#define PCFGQOS0_rqos_map_region0_RegisterSize 2

/* Register PCFGQOS0 field rqos_map_region1 */
/* This bitfield indicates the traffic class of region 1.
 Valid values are:
 - 0 : LPR
 - 1: VPR
 - 2: HPR
 For dual address queue configurations, region1 maps to the blue address queue.
 In this case, valid values are 
 - 0: LPR
 - 1: VPR only
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region1_BitAddressOffset 20
#define PCFGQOS0_rqos_map_region1_RegisterSize 2

/* End of Register Definition for PCFGQOS0 */

/* Register PCFGQOS1 */
/* Port n Read QoS Configuration Register 1 */
// #define PCFGQOS1 (REGB_ARB_PORT1_BaseAddress + 0x98)
#define PCFGQOS1_RegisterSize 32
#define PCFGQOS1_RegisterResetValue 0x0
#define PCFGQOS1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGQOS1 */

/* Register PCFGQOS1 field rqos_map_timeoutb */
/* Specifies the timeout value for transactions mapped to the blue address queue. */
#define PCFGQOS1_rqos_map_timeoutb_BitAddressOffset 0
#define PCFGQOS1_rqos_map_timeoutb_RegisterSize 11

/* Register PCFGQOS1 field rqos_map_timeoutr */
/* Specifies the timeout value for transactions mapped to the red address queue. */
#define PCFGQOS1_rqos_map_timeoutr_BitAddressOffset 16
#define PCFGQOS1_rqos_map_timeoutr_RegisterSize 11

/* End of Register Definition for PCFGQOS1 */

/* Register PCFGWQOS0 */
/* Port n Write QoS Configuration Register 0 */
// #define PCFGWQOS0 (REGB_ARB_PORT1_BaseAddress + 0x9c)
#define PCFGWQOS0_RegisterSize 32
#define PCFGWQOS0_RegisterResetValue 0xe00
#define PCFGWQOS0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGWQOS0 */

/* Register PCFGWQOS0 field wqos_map_level1 */
/* Separation level indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 which corresponds to awqos.
 Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGWQOS0_wqos_map_level1_BitAddressOffset 0
#define PCFGWQOS0_wqos_map_level1_RegisterSize 4

/* Register PCFGWQOS0 field wqos_map_level2 */
/* Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to awqos.
 Region2 starts from (level2 + 1) up to 15.
 Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGWQOS0_wqos_map_level2_BitAddressOffset 8
#define PCFGWQOS0_wqos_map_level2_RegisterSize 4

/* Register PCFGWQOS0 field wqos_map_region0 */
/* This bitfield indicates the traffic class of region 0.

	  Valid values are: 

	  0: NPW, 1: VPW. 

     When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 0 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region0_BitAddressOffset 16
#define PCFGWQOS0_wqos_map_region0_RegisterSize 2

/* Register PCFGWQOS0 field wqos_map_region1 */
/* This bitfield indicates the traffic class of region 1.
 Valid values are:
 0: NPW, 1: VPW.
 When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 1 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region1_BitAddressOffset 20
#define PCFGWQOS0_wqos_map_region1_RegisterSize 2

/* Register PCFGWQOS0 field wqos_map_region2 */
/* This bitfield indicates the traffic class of region 2.
 Valid values are:
 0: NPW, 1: VPW.
 When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 2 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region2_BitAddressOffset 24
#define PCFGWQOS0_wqos_map_region2_RegisterSize 2

/* End of Register Definition for PCFGWQOS0 */

/* Register PCFGWQOS1 */
/* Port n Write QoS Configuration Register 1 */
// #define PCFGWQOS1 (REGB_ARB_PORT1_BaseAddress + 0xa0)
#define PCFGWQOS1_RegisterSize 32
#define PCFGWQOS1_RegisterResetValue 0x0
#define PCFGWQOS1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGWQOS1 */

/* Register PCFGWQOS1 field wqos_map_timeout1 */
/* Specifies the timeout value for write transactions in region 0 and 1. */
#define PCFGWQOS1_wqos_map_timeout1_BitAddressOffset 0
#define PCFGWQOS1_wqos_map_timeout1_RegisterSize 11

/* Register PCFGWQOS1 field wqos_map_timeout2 */
/* Specifies the timeout value for write transactions in region 2. */
#define PCFGWQOS1_wqos_map_timeout2_BitAddressOffset 16
#define PCFGWQOS1_wqos_map_timeout2_RegisterSize 11

/* End of Register Definition for PCFGWQOS1 */
#endif

#define REGB_ARB_PORT2_BaseAddress 0x22000

#if 0
/* Register PCFGR */
/* Configuration Read Register */
// #define PCFGR (REGB_ARB_PORT2_BaseAddress + 0x4)
#define PCFGR_RegisterSize 32
#define PCFGR_RegisterResetValue 0x4000
#define PCFGR_RegisterResetMask 0xffffffff

/* Register Field information for PCFGR */

/* Register PCFGR field rd_port_priority */
/* Determines the initial load value of read aging counters. 	 These counters will be parallel loaded after reset, or after each grant to the corresponding port. 	 The aging counters down-count every clock cycle where the port is requesting but not 
	 granted. The higher significant 5-bits of the read aging counter sets the priority of the 
         read channel of a given port.	 Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. 	 When the aging counter becomes 0, the corresponding port channel will have the highest priority level (timeout condition - Priority0).	 For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority 	 inputs (arqos) are enabled (timeout is still applicable).  	 For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.	 In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority 
	 (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis. 	 

Note: The two LSBs of this register field are tied internally to 2'b00. */
#define PCFGR_rd_port_priority_BitAddressOffset 0
#define PCFGR_rd_port_priority_RegisterSize 10

/* Register PCFGR field rd_port_aging_en */
/* If set to 1, enables aging function for the read channel of the port. */
#define PCFGR_rd_port_aging_en_BitAddressOffset 12
#define PCFGR_rd_port_aging_en_RegisterSize 1

/* Register PCFGR field rd_port_urgent_en */
/* If set to 1, enables the AXI urgent sideband signal (arurgent). When enabled and arurgent 	 is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to 	 DDRC is asserted if enabled in PCCFG.go2critical_en register. Note that arurgent signal can be 	 asserted anytime and as long as required which is independent of address handshaking (it is not 	 associated with any particular command). */
#define PCFGR_rd_port_urgent_en_BitAddressOffset 13
#define PCFGR_rd_port_urgent_en_RegisterSize 1

/* Register PCFGR field rd_port_pagematch_en */
/* If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, 	 the port is continued to be granted if the following immediate commands are to the same 	 memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define PCFGR_rd_port_pagematch_en_BitAddressOffset 14
#define PCFGR_rd_port_pagematch_en_RegisterSize 1

/* End of Register Definition for PCFGR */

/* Register PCFGW */
/* Configuration Write Register */
// #define PCFGW (REGB_ARB_PORT2_BaseAddress + 0x8)
#define PCFGW_RegisterSize 32
#define PCFGW_RegisterResetValue 0x4000
#define PCFGW_RegisterResetMask 0xffffffff

/* Register Field information for PCFGW */

/* Register PCFGW field wr_port_priority */
/* Determines the initial load value of write aging counters.	 These counters will be parallel loaded after reset, or after each grant to the corresponding port. 	 The aging counters down-count every clock cycle where the port is requesting but not 	 granted. The higher significant 5-bits of the write aging counter sets the initial priority of the 
         write channel of a given port.	 Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel will have the highest priority level.	 

For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority 	 inputs (awqos) are enabled (timeout is still applicable). 	 

For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching. 	 

Note: The two LSBs of this register field are tied internally to 2'b00. */
#define PCFGW_wr_port_priority_BitAddressOffset 0
#define PCFGW_wr_port_priority_RegisterSize 10

/* Register PCFGW field wr_port_aging_en */
/* If set to 1, enables aging function for the write channel of the port. */
#define PCFGW_wr_port_aging_en_BitAddressOffset 12
#define PCFGW_wr_port_aging_en_RegisterSize 1

/* Register PCFGW field wr_port_urgent_en */
/* If set to 1, enables the AXI urgent sideband signal (awurgent). When enabled and awurgent 	 is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to 	 DDRC is asserted if enabled in PCCFG.go2critical_en register.
 Note that awurgent signal can be 	 asserted anytime and as long as required which is independent of address handshaking (it is not 	 associated with any particular command). */
#define PCFGW_wr_port_urgent_en_BitAddressOffset 13
#define PCFGW_wr_port_urgent_en_RegisterSize 1

/* Register PCFGW field wr_port_pagematch_en */
/* If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, 	 the port is continued to be granted if the following immediate commands are to the same 	 memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define PCFGW_wr_port_pagematch_en_BitAddressOffset 14
#define PCFGW_wr_port_pagematch_en_RegisterSize 1

/* End of Register Definition for PCFGW */

/* Register PCTRL */
/* Port  Control Register */
// #define PCTRL (REGB_ARB_PORT2_BaseAddress + 0x90)
#define PCTRL_RegisterSize 32
#define PCTRL_RegisterResetValue 0x0
#define PCTRL_RegisterResetMask 0xffffffff

/* Register Field information for PCTRL */

/* Register PCTRL field port_en */
/* Enables AXI port n. */
#define PCTRL_port_en_BitAddressOffset 0
#define PCTRL_port_en_RegisterSize 1

/* End of Register Definition for PCTRL */

/* Register PCFGQOS0 */
/* Port n Read QoS Configuration Register 0 */
// #define PCFGQOS0 (REGB_ARB_PORT2_BaseAddress + 0x94)
#define PCFGQOS0_RegisterSize 32
#define PCFGQOS0_RegisterResetValue 0x0
#define PCFGQOS0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGQOS0 */

/* Register PCFGQOS0 field rqos_map_level1 */
/* Separation level1 indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.          

Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGQOS0_rqos_map_level1_BitAddressOffset 0
#define PCFGQOS0_rqos_map_level1_RegisterSize 4

/* Register PCFGQOS0 field rqos_map_region0 */
/* This bitfield indicates the traffic class of region 0.
 Valid values are:
 - 0: LPR
 - 1: VPR
 - 2: HPR
For dual address queue configurations, region 0 maps to the blue address queue.
 In this case, valid values are: 

0: LPR and 1: VPR only.
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region0_BitAddressOffset 16
#define PCFGQOS0_rqos_map_region0_RegisterSize 2

/* Register PCFGQOS0 field rqos_map_region1 */
/* This bitfield indicates the traffic class of region 1.
 Valid values are:
 - 0 : LPR
 - 1: VPR
 - 2: HPR
 For dual address queue configurations, region1 maps to the blue address queue.
 In this case, valid values are 
 - 0: LPR
 - 1: VPR only
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region1_BitAddressOffset 20
#define PCFGQOS0_rqos_map_region1_RegisterSize 2

/* End of Register Definition for PCFGQOS0 */

/* Register PCFGQOS1 */
/* Port n Read QoS Configuration Register 1 */
// #define PCFGQOS1 (REGB_ARB_PORT2_BaseAddress + 0x98)
#define PCFGQOS1_RegisterSize 32
#define PCFGQOS1_RegisterResetValue 0x0
#define PCFGQOS1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGQOS1 */

/* Register PCFGQOS1 field rqos_map_timeoutb */
/* Specifies the timeout value for transactions mapped to the blue address queue. */
#define PCFGQOS1_rqos_map_timeoutb_BitAddressOffset 0
#define PCFGQOS1_rqos_map_timeoutb_RegisterSize 11

/* Register PCFGQOS1 field rqos_map_timeoutr */
/* Specifies the timeout value for transactions mapped to the red address queue. */
#define PCFGQOS1_rqos_map_timeoutr_BitAddressOffset 16
#define PCFGQOS1_rqos_map_timeoutr_RegisterSize 11

/* End of Register Definition for PCFGQOS1 */

/* Register PCFGWQOS0 */
/* Port n Write QoS Configuration Register 0 */
// #define PCFGWQOS0 (REGB_ARB_PORT2_BaseAddress + 0x9c)
#define PCFGWQOS0_RegisterSize 32
#define PCFGWQOS0_RegisterResetValue 0xe00
#define PCFGWQOS0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGWQOS0 */

/* Register PCFGWQOS0 field wqos_map_level1 */
/* Separation level indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 which corresponds to awqos.
 Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGWQOS0_wqos_map_level1_BitAddressOffset 0
#define PCFGWQOS0_wqos_map_level1_RegisterSize 4

/* Register PCFGWQOS0 field wqos_map_level2 */
/* Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to awqos.
 Region2 starts from (level2 + 1) up to 15.
 Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGWQOS0_wqos_map_level2_BitAddressOffset 8
#define PCFGWQOS0_wqos_map_level2_RegisterSize 4

/* Register PCFGWQOS0 field wqos_map_region0 */
/* This bitfield indicates the traffic class of region 0.

	  Valid values are: 

	  0: NPW, 1: VPW. 

     When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 0 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region0_BitAddressOffset 16
#define PCFGWQOS0_wqos_map_region0_RegisterSize 2

/* Register PCFGWQOS0 field wqos_map_region1 */
/* This bitfield indicates the traffic class of region 1.
 Valid values are:
 0: NPW, 1: VPW.
 When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 1 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region1_BitAddressOffset 20
#define PCFGWQOS0_wqos_map_region1_RegisterSize 2

/* Register PCFGWQOS0 field wqos_map_region2 */
/* This bitfield indicates the traffic class of region 2.
 Valid values are:
 0: NPW, 1: VPW.
 When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 2 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region2_BitAddressOffset 24
#define PCFGWQOS0_wqos_map_region2_RegisterSize 2

/* End of Register Definition for PCFGWQOS0 */

/* Register PCFGWQOS1 */
/* Port n Write QoS Configuration Register 1 */
// #define PCFGWQOS1 (REGB_ARB_PORT2_BaseAddress + 0xa0)
#define PCFGWQOS1_RegisterSize 32
#define PCFGWQOS1_RegisterResetValue 0x0
#define PCFGWQOS1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGWQOS1 */

/* Register PCFGWQOS1 field wqos_map_timeout1 */
/* Specifies the timeout value for write transactions in region 0 and 1. */
#define PCFGWQOS1_wqos_map_timeout1_BitAddressOffset 0
#define PCFGWQOS1_wqos_map_timeout1_RegisterSize 11

/* Register PCFGWQOS1 field wqos_map_timeout2 */
/* Specifies the timeout value for write transactions in region 2. */
#define PCFGWQOS1_wqos_map_timeout2_BitAddressOffset 16
#define PCFGWQOS1_wqos_map_timeout2_RegisterSize 11

/* End of Register Definition for PCFGWQOS1 */
#endif

#define REGB_ARB_PORT3_BaseAddress 0x23000

#if 0
/* Register PCFGR */
/* Configuration Read Register */
// #define PCFGR (REGB_ARB_PORT3_BaseAddress + 0x4)
#define PCFGR_RegisterSize 32
#define PCFGR_RegisterResetValue 0x4000
#define PCFGR_RegisterResetMask 0xffffffff

/* Register Field information for PCFGR */

/* Register PCFGR field rd_port_priority */
/* Determines the initial load value of read aging counters. 	 These counters will be parallel loaded after reset, or after each grant to the corresponding port. 	 The aging counters down-count every clock cycle where the port is requesting but not 
	 granted. The higher significant 5-bits of the read aging counter sets the priority of the 
         read channel of a given port.	 Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. 	 When the aging counter becomes 0, the corresponding port channel will have the highest priority level (timeout condition - Priority0).	 For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority 	 inputs (arqos) are enabled (timeout is still applicable).  	 For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching.	 In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority 
	 (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis. 	 

Note: The two LSBs of this register field are tied internally to 2'b00. */
#define PCFGR_rd_port_priority_BitAddressOffset 0
#define PCFGR_rd_port_priority_RegisterSize 10

/* Register PCFGR field rd_port_aging_en */
/* If set to 1, enables aging function for the read channel of the port. */
#define PCFGR_rd_port_aging_en_BitAddressOffset 12
#define PCFGR_rd_port_aging_en_RegisterSize 1

/* Register PCFGR field rd_port_urgent_en */
/* If set to 1, enables the AXI urgent sideband signal (arurgent). When enabled and arurgent 	 is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to 	 DDRC is asserted if enabled in PCCFG.go2critical_en register. Note that arurgent signal can be 	 asserted anytime and as long as required which is independent of address handshaking (it is not 	 associated with any particular command). */
#define PCFGR_rd_port_urgent_en_BitAddressOffset 13
#define PCFGR_rd_port_urgent_en_RegisterSize 1

/* Register PCFGR field rd_port_pagematch_en */
/* If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, 	 the port is continued to be granted if the following immediate commands are to the same 	 memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define PCFGR_rd_port_pagematch_en_BitAddressOffset 14
#define PCFGR_rd_port_pagematch_en_RegisterSize 1

/* End of Register Definition for PCFGR */

/* Register PCFGW */
/* Configuration Write Register */
// #define PCFGW (REGB_ARB_PORT3_BaseAddress + 0x8)
#define PCFGW_RegisterSize 32
#define PCFGW_RegisterResetValue 0x4000
#define PCFGW_RegisterResetMask 0xffffffff

/* Register Field information for PCFGW */

/* Register PCFGW field wr_port_priority */
/* Determines the initial load value of write aging counters.	 These counters will be parallel loaded after reset, or after each grant to the corresponding port. 	 The aging counters down-count every clock cycle where the port is requesting but not 	 granted. The higher significant 5-bits of the write aging counter sets the initial priority of the 
         write channel of a given port.	 Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel will have the highest priority level.	 

For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority 	 inputs (awqos) are enabled (timeout is still applicable). 	 

For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching. 	 

Note: The two LSBs of this register field are tied internally to 2'b00. */
#define PCFGW_wr_port_priority_BitAddressOffset 0
#define PCFGW_wr_port_priority_RegisterSize 10

/* Register PCFGW field wr_port_aging_en */
/* If set to 1, enables aging function for the write channel of the port. */
#define PCFGW_wr_port_aging_en_BitAddressOffset 12
#define PCFGW_wr_port_aging_en_RegisterSize 1

/* Register PCFGW field wr_port_urgent_en */
/* If set to 1, enables the AXI urgent sideband signal (awurgent). When enabled and awurgent 	 is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to 	 DDRC is asserted if enabled in PCCFG.go2critical_en register.
 Note that awurgent signal can be 	 asserted anytime and as long as required which is independent of address handshaking (it is not 	 associated with any particular command). */
#define PCFGW_wr_port_urgent_en_BitAddressOffset 13
#define PCFGW_wr_port_urgent_en_RegisterSize 1

/* Register PCFGW field wr_port_pagematch_en */
/* If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, 	 the port is continued to be granted if the following immediate commands are to the same 	 memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define PCFGW_wr_port_pagematch_en_BitAddressOffset 14
#define PCFGW_wr_port_pagematch_en_RegisterSize 1

/* End of Register Definition for PCFGW */

/* Register PCTRL */
/* Port  Control Register */
// #define PCTRL (REGB_ARB_PORT3_BaseAddress + 0x90)
#define PCTRL_RegisterSize 32
#define PCTRL_RegisterResetValue 0x0
#define PCTRL_RegisterResetMask 0xffffffff

/* Register Field information for PCTRL */

/* Register PCTRL field port_en */
/* Enables AXI port n. */
#define PCTRL_port_en_BitAddressOffset 0
#define PCTRL_port_en_RegisterSize 1

/* End of Register Definition for PCTRL */

/* Register PCFGQOS0 */
/* Port n Read QoS Configuration Register 0 */
// #define PCFGQOS0 (REGB_ARB_PORT3_BaseAddress + 0x94)
#define PCFGQOS0_RegisterSize 32
#define PCFGQOS0_RegisterResetValue 0x0
#define PCFGQOS0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGQOS0 */

/* Register PCFGQOS0 field rqos_map_level1 */
/* Separation level1 indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos.          

Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGQOS0_rqos_map_level1_BitAddressOffset 0
#define PCFGQOS0_rqos_map_level1_RegisterSize 4

/* Register PCFGQOS0 field rqos_map_region0 */
/* This bitfield indicates the traffic class of region 0.
 Valid values are:
 - 0: LPR
 - 1: VPR
 - 2: HPR
For dual address queue configurations, region 0 maps to the blue address queue.
 In this case, valid values are: 

0: LPR and 1: VPR only.
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region0_BitAddressOffset 16
#define PCFGQOS0_rqos_map_region0_RegisterSize 2

/* Register PCFGQOS0 field rqos_map_region1 */
/* This bitfield indicates the traffic class of region 1.
 Valid values are:
 - 0 : LPR
 - 1: VPR
 - 2: HPR
 For dual address queue configurations, region1 maps to the blue address queue.
 In this case, valid values are 
 - 0: LPR
 - 1: VPR only
 When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic. */
#define PCFGQOS0_rqos_map_region1_BitAddressOffset 20
#define PCFGQOS0_rqos_map_region1_RegisterSize 2

/* End of Register Definition for PCFGQOS0 */

/* Register PCFGQOS1 */
/* Port n Read QoS Configuration Register 1 */
// #define PCFGQOS1 (REGB_ARB_PORT3_BaseAddress + 0x98)
#define PCFGQOS1_RegisterSize 32
#define PCFGQOS1_RegisterResetValue 0x0
#define PCFGQOS1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGQOS1 */

/* Register PCFGQOS1 field rqos_map_timeoutb */
/* Specifies the timeout value for transactions mapped to the blue address queue. */
#define PCFGQOS1_rqos_map_timeoutb_BitAddressOffset 0
#define PCFGQOS1_rqos_map_timeoutb_RegisterSize 11

/* Register PCFGQOS1 field rqos_map_timeoutr */
/* Specifies the timeout value for transactions mapped to the red address queue. */
#define PCFGQOS1_rqos_map_timeoutr_BitAddressOffset 16
#define PCFGQOS1_rqos_map_timeoutr_RegisterSize 11

/* End of Register Definition for PCFGQOS1 */

/* Register PCFGWQOS0 */
/* Port n Write QoS Configuration Register 0 */
// #define PCFGWQOS0 (REGB_ARB_PORT3_BaseAddress + 0x9c)
#define PCFGWQOS0_RegisterSize 32
#define PCFGWQOS0_RegisterResetValue 0xe00
#define PCFGWQOS0_RegisterResetMask 0xffffffff

/* Register Field information for PCFGWQOS0 */

/* Register PCFGWQOS0 field wqos_map_level1 */
/* Separation level indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 which corresponds to awqos.
 Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGWQOS0_wqos_map_level1_BitAddressOffset 0
#define PCFGWQOS0_wqos_map_level1_RegisterSize 4

/* Register PCFGWQOS0 field wqos_map_level2 */
/* Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to awqos.
 Region2 starts from (level2 + 1) up to 15.
 Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 All of the map_level* registers must be set to distinct values. */
#define PCFGWQOS0_wqos_map_level2_BitAddressOffset 8
#define PCFGWQOS0_wqos_map_level2_RegisterSize 4

/* Register PCFGWQOS0 field wqos_map_region0 */
/* This bitfield indicates the traffic class of region 0.

	  Valid values are: 

	  0: NPW, 1: VPW. 

     When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 0 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region0_BitAddressOffset 16
#define PCFGWQOS0_wqos_map_region0_RegisterSize 2

/* Register PCFGWQOS0 field wqos_map_region1 */
/* This bitfield indicates the traffic class of region 1.
 Valid values are:
 0: NPW, 1: VPW.
 When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 1 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region1_BitAddressOffset 20
#define PCFGWQOS0_wqos_map_region1_RegisterSize 2

/* Register PCFGWQOS0 field wqos_map_region2 */
/* This bitfield indicates the traffic class of region 2.
 Valid values are:
 0: NPW, 1: VPW.
 When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 2 is set to 1 (VPW), VPW traffic is aliased to NPW traffic. */
#define PCFGWQOS0_wqos_map_region2_BitAddressOffset 24
#define PCFGWQOS0_wqos_map_region2_RegisterSize 2

/* End of Register Definition for PCFGWQOS0 */

/* Register PCFGWQOS1 */
/* Port n Write QoS Configuration Register 1 */
// #define PCFGWQOS1 (REGB_ARB_PORT3_BaseAddress + 0xa0)
#define PCFGWQOS1_RegisterSize 32
#define PCFGWQOS1_RegisterResetValue 0x0
#define PCFGWQOS1_RegisterResetMask 0xffffffff

/* Register Field information for PCFGWQOS1 */

/* Register PCFGWQOS1 field wqos_map_timeout1 */
/* Specifies the timeout value for write transactions in region 0 and 1. */
#define PCFGWQOS1_wqos_map_timeout1_BitAddressOffset 0
#define PCFGWQOS1_wqos_map_timeout1_RegisterSize 11

/* Register PCFGWQOS1 field wqos_map_timeout2 */
/* Specifies the timeout value for write transactions in region 2. */
#define PCFGWQOS1_wqos_map_timeout2_BitAddressOffset 16
#define PCFGWQOS1_wqos_map_timeout2_RegisterSize 11

/* End of Register Definition for PCFGWQOS1 */
#endif

#define REGB_FREQ0_CH0_BaseAddress 0x0

/* Register DRAMSET1TMG0 */
/* SDRAM Timing Register 0 belonging to Timing Set 1 */
// #define DRAMSET1TMG0 (REGB_FREQ0_CH0_BaseAddress + 0x0)
#define DRAMSET1TMG0_RegisterSize 32
#define DRAMSET1TMG0_RegisterResetValue 0xf101b0f
#define DRAMSET1TMG0_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG0 */

/* Register DRAMSET1TMG0 field t_ras_min */
/* tRAS(min):  Minimum time between activate and precharge to the same bank.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG0_t_ras_min_BitAddressOffset 0
#define DRAMSET1TMG0_t_ras_min_RegisterSize 8

/* Register DRAMSET1TMG0 field t_ras_max */
/* tRAS(max):  Maximum time between activate and precharge to same bank. This is the maximum time that a page can be kept open

 t_ras_max must be set to RoundDown(tRAS(max)/tCK/1024).

 Unit: 1024 DRAM clock cycles. */
#define DRAMSET1TMG0_t_ras_max_BitAddressOffset 8
#define DRAMSET1TMG0_t_ras_max_RegisterSize 8

/* Register DRAMSET1TMG0 field t_faw */
/* tFAW:
 At most 4 banks must be activated in a rolling window of tFAW cycles.

 Unit: DRAM clock cycles. */
#define DRAMSET1TMG0_t_faw_BitAddressOffset 16
#define DRAMSET1TMG0_t_faw_RegisterSize 8

/* Register DRAMSET1TMG0 field wr2pre */
/* 
Minimum time between write and precharge to same bank.

Specifications: WL + BL/2 + tWR

where:
 - WL = write latency
 - BL = burst length. This must match the value programmed in the BL bit of the mode register to the SDRAM. BST (burst terminate) is not supported at present.
 - tWR = Write recovery time. This comes directly from the SDRAM specification. 
Add one extra cycle for LPDDR4/5 for this parameter.

Note that, depending on the PHY, if using LRDIMM, it may be necessary to adjust the value of this parameter to compensate for the extra cycle of latency through the LRDIMM.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG0_wr2pre_BitAddressOffset 24
#define DRAMSET1TMG0_wr2pre_RegisterSize 8

/* End of Register Definition for DRAMSET1TMG0 */

/* Register DRAMSET1TMG1 */
/* SDRAM Timing Register 1 belonging to Timing Set 1 */
// #define DRAMSET1TMG1 (REGB_FREQ0_CH0_BaseAddress + 0x4)
#define DRAMSET1TMG1_RegisterSize 32
#define DRAMSET1TMG1_RegisterResetValue 0x80414
#define DRAMSET1TMG1_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG1 */

/* Register DRAMSET1TMG1 field t_rc */
/* tRC:  Minimum time between activates to same bank.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG1_t_rc_BitAddressOffset 0
#define DRAMSET1TMG1_t_rc_RegisterSize 8

/* Register DRAMSET1TMG1 field rd2pre */
/* tRTP:  Minimum time from read to precharge of same bank.
 - DDR4: Max of following two equations:
           tAL + max (tRTP, 4) or, 
           RL + BL/2 - tRP (*).
 - DDR5: tRTP 
 - LPDDR4: BL/2 + max(tRTP,8) - 8
 - LPDDR5(BG mode): BL/n_min + RU(tRBTP/tCK)
 - LPDDR5(16B mode): BL/n + RU(tRBTP/tCK)
(*) When both DDR4 SDRAM and ST-MRAM are used simultaneously, use SDRAM's tRP value for calculation.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG1_rd2pre_BitAddressOffset 8
#define DRAMSET1TMG1_rd2pre_RegisterSize 8

/* Register DRAMSET1TMG1 field t_xp */
/* tXP: Minimum time after power-down exit to any operation.
 - DDR4 (C/A parity not enabled): tXP
 - DDR4 (C/A parity enabled): (tXP+PL)
 - DDR5: tXP
 - LPDDR4 (tCKELPD is defined in spec): larger of tXP and tCKELPD instead.
 - LPDDR4 (tCKELPD is not defined in spec): tXP.
 - LPDDR5: tXP
Unit: DRAM clock cycles. */
#define DRAMSET1TMG1_t_xp_BitAddressOffset 16
#define DRAMSET1TMG1_t_xp_RegisterSize 6

/* End of Register Definition for DRAMSET1TMG1 */

/* Register DRAMSET1TMG2 */
/* SDRAM Timing Register 2 belonging to Timing Set 1 */
// #define DRAMSET1TMG2 (REGB_FREQ0_CH0_BaseAddress + 0x8)
#define DRAMSET1TMG2_RegisterSize 32
#define DRAMSET1TMG2_RegisterResetValue 0x305060d
#define DRAMSET1TMG2_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG2 */

/* Register DRAMSET1TMG2 field wr2rd */
/* 
 - DDR4: CWL + PL + BL/2 + tWTR_L
 - DDR5: CWL  + BL/2 + tWTR_L
 - LPDDR4: WL + BL/2 + tWTR + 1
 - LPDDR5(BG mode): WL + BL/n_max + RU(tWTR_L/tCK)
 - LPDDR5(16B mode): WL + BL/n + RU(tWTR/tCK)
In DDR4, minimum time from write command to read command for same bank group. In others, minimum time from write command to read command. Includes time for bus turnaround, recovery times, and all per-bank, per-rank, and global constraints.

Please see the relevant PHY databook for details of what must be included here.

Where:
 - CWL = CAS write latency
 - WL = Write latency
 - PL = Parity latency
 - BL = burst length. This must match the value programmed in the BL bit of the mode register to the SDRAM
 - tWTR_L = internal write to read command delay for same bank group. This comes directly from the SDRAM specification. 
 - tWTR = internal write to read command delay. This comes directly from the SDRAM specification. 
After PHY has completed training the value programmed may need to be increased. Refer to relevant PHY documentation.

Add one extra cycle for LPDDR4 operation. 

WTR_L must be increased by one if DDR4 2tCK write preamble is used.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG2_wr2rd_BitAddressOffset 0
#define DRAMSET1TMG2_wr2rd_RegisterSize 8

/* Register DRAMSET1TMG2 field rd2wr */
/* 
 - DDR4: RL + BL/2 + 1 + WR_PREAMBLE - WL
 - DDR5: CL - CWL + BL/2 + 2 - (Read DQS offset) + (RD_POSTAMBLE-0.5) + WR_PREAMBLE
 - LPDDR4(DQ ODT is Disabled): RL + BL/2 + RU(tDQSCKmax/tCK) + WR_PREAMBLE + RD_POSTAMBLE - WL
 - LPDDR4(DQ ODT is Enabled) : RL + BL/2 + RU(tDQSCKmax/tCK) + RD_POSTAMBLE - ODTLon - RU(tODTon(min)/tCK) + 1
 - LPDDR5(DQ ODT is Disabled): RL + BL/n_max + RU(tWCKDQO(max)/tCK) - WL
 - LPDDR5(DQ ODT is Enabled) : RL + BL/n_max + RU(tWCKDQO(max)/tCK) + RU(tRPST/tCK) - ODTLon - RU(tODTon(min)/tCK) + 1
Minimum time from read command to write command. Include time for bus turnaround and all per-bank, per-rank, and global constraints.

Please see the relevant PHY databook for details of what must be included here.

Where:
 - WL = write latency
 - BL = burst length. This must match the value programmed in the BL bit of the mode register to the SDRAM
 - RL = read latency = CAS latency
 - WR_PREAMBLE = 1 (1tCK write preamble), 2 (2tCK write preamble).
 - RD_POSTAMBLE = 0.5 (0.5tCK read postamble), 1.5 (1.5tCK read postamble).
After PHY has completed training the value programmed may need to be increased. Refer to relevant PHY documentation.

For LPDDR4, if derating is enabled (DERATECTL0.derate_enable=1), derated tDQSCKmax must be used.

Note that, depending on the PHY, if using LRDIMM, it may be necessary to adjust the value of this parameter to compensate for the extra cycle of latency through the LRDIMM.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG2_rd2wr_BitAddressOffset 8
#define DRAMSET1TMG2_rd2wr_RegisterSize 8

/* Register DRAMSET1TMG2 field read_latency */
/* Set to RL

Time from read command to read data on SDRAM interface. This must be set to RL.

Note that, depending on the PHY, if using RDIMM/LRDIMM, it may be necessary to adjust the value of RL to compensate for the extra cycle of latency through the RDIMM/LRDIMM.

In addition to programming this register field, it is necessary to program DFITMG0 and DFITMG1 to control the read and write latencies

Unit: DRAM clock cycles. */
#define DRAMSET1TMG2_read_latency_BitAddressOffset 16
#define DRAMSET1TMG2_read_latency_RegisterSize 7

/* Register DRAMSET1TMG2 field write_latency */
/* Set to WL

Time from write command to write data on SDRAM interface. This must be set to WL.

Note that, depending on the PHY, if using RDIMM/LRDIMM, it may be necessary to adjust the value of WL to compensate for the extra cycle of latency through the RDIMM/LRDIMM.

For all protocols, in addition to programming this register field, it is necessary to program DFITMG0 and DFITMG1 to control the read and write latencies

Unit: DRAM clock cycles. */
#define DRAMSET1TMG2_write_latency_BitAddressOffset 24
#define DRAMSET1TMG2_write_latency_RegisterSize 7

/* End of Register Definition for DRAMSET1TMG2 */

/* Register DRAMSET1TMG3 */
/* SDRAM Timing Register 3 belonging to Timing Set 1 */
// #define DRAMSET1TMG3 (REGB_FREQ0_CH0_BaseAddress + 0xc)
#define DRAMSET1TMG3_RegisterSize 32
#define DRAMSET1TMG3_RegisterResetValue 0x40404
#define DRAMSET1TMG3_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG3 */

/* Register DRAMSET1TMG3 field wr2mr */
/* Time from Write to MRW/MRR command.
 - LPDDR4: WL + 1 + BL/2 + max(RU(7.5ns/tCK),8nCK) + nWR
 - LPDDR5: WL + BL/n_max + MAX[RU(7.5ns/tCK),4nCK] + nWR
Unit: DRAM clock cycles. */
#define DRAMSET1TMG3_wr2mr_BitAddressOffset 0
#define DRAMSET1TMG3_wr2mr_RegisterSize 8

/* Register DRAMSET1TMG3 field rd2mr */
/* Time from Read to MRW/MRR command.
 - LPDDR4: RL + BL/2 + RU(tDQSCKmax/tCK) + RD(tRPST) + max(RU(7.5ns/tCK),8nCK) + nRTP - 8
 - LPDDR5: RL + RU(tWCKDQO(max)/tCK)) + BL/n_max + MAX[RU(7.5ns/tCK),4nCK] + nRBTP
Unit: DRAM clock cycles. */
#define DRAMSET1TMG3_rd2mr_BitAddressOffset 8
#define DRAMSET1TMG3_rd2mr_RegisterSize 8

/* Register DRAMSET1TMG3 field t_mr */
/* Time from MRW/MRS to valid command
 - DDR4: Set this to the larger of tMOD + AL and tMRD. If C/A parity is enabled, tMOD_PAR(tMOD+PL) + AL and tMRD_PAR(tMOD+PL) and used instead. If CAL mode is enabled, tCAL must be added to the above. Note that if using RDIMM/LRDIMM, depending on the PHY, it may be necessary to adjust the value of this parameter to compensate for the extra cycle of latency applied to mode register writes by the RDIMM/LRDIMM chip. Also note that if using LRDIMM, the minimum value of this register is tMRD_L2.
 - DDR5: Set this to the larger of tMRR, tMRW, tMRWPD and tMRD.
 - LPDDR4:Set this to the larger of tMRR, tMRW, tMRWCKEL and tMRD.
 - LPDDR5:Set this to the larger of tMRR, tMRW, tMRWPD and tMRD.
Unit: DRAM clock cycles. */
#define DRAMSET1TMG3_t_mr_BitAddressOffset 16
#define DRAMSET1TMG3_t_mr_RegisterSize 7

/* End of Register Definition for DRAMSET1TMG3 */

/* Register DRAMSET1TMG4 */
/* SDRAM Timing Register 4 belonging to Timing Set 1 */
// #define DRAMSET1TMG4 (REGB_FREQ0_CH0_BaseAddress + 0x10)
#define DRAMSET1TMG4_RegisterSize 32
#define DRAMSET1TMG4_RegisterResetValue 0x5040405
#define DRAMSET1TMG4_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG4 */

/* Register DRAMSET1TMG4 field t_rp */
/* tRP:  Minimum time from single-bank precharge to activate of same bank.

    t_rp must be set to RoundUp(tRP/tCK).

    Unit: DRAM clock cycles. */
#define DRAMSET1TMG4_t_rp_BitAddressOffset 0
#define DRAMSET1TMG4_t_rp_RegisterSize 7

/* Register DRAMSET1TMG4 field t_rrd */
/* For DDR4/DDR5/LPDDR5(BG mode): Minimum time between activates from bank "a" to bank "b" for same bank group.

For LPDDR4/LPDDR5(16B mode): Minimum time between activates from bank "a" to bank "b".
 - DDR4/5: tRRD_L
 - LPDDR4: RU(tRRD/tCK)
 - LPDDR5(BG mode): RU(tRRD_L/tCK)
 - LPDDR5(16B mode): RU(tRRD/tCK)
Unit: DRAM clock cycles. */
#define DRAMSET1TMG4_t_rrd_BitAddressOffset 8
#define DRAMSET1TMG4_t_rrd_RegisterSize 6

/* Register DRAMSET1TMG4 field t_ccd */
/* This is the minimum time between two reads or two writes.
 - DDR4: tCCD_L
 - LPDDR4: tCCD
 - LPDDR5: BL/n
Don't Care for DDR5 (see DRAMSET1TMG26.t_ccd_r/t_ccd_w in DDR5).

Unit: DRAM clock cycles. */
#define DRAMSET1TMG4_t_ccd_BitAddressOffset 16
#define DRAMSET1TMG4_t_ccd_RegisterSize 6

/* Register DRAMSET1TMG4 field t_rcd */
/* tRCD - tAL: Minimum time from activate to read or write command to same bank.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG4_t_rcd_BitAddressOffset 24
#define DRAMSET1TMG4_t_rcd_RegisterSize 8

/* End of Register Definition for DRAMSET1TMG4 */

/* Register DRAMSET1TMG5 */
/* SDRAM Timing Register 5 belonging to Timing Set 1 */
// #define DRAMSET1TMG5 (REGB_FREQ0_CH0_BaseAddress + 0x14)
#define DRAMSET1TMG5_RegisterSize 32
#define DRAMSET1TMG5_RegisterResetValue 0x5050403
#define DRAMSET1TMG5_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG5 */

/* Register DRAMSET1TMG5 field t_cke */
/* Delay time between PDE and PDX.
 - LPDDR4: tCKE
 - LPDDR5: tCSPD
 - DDR4: tPD (+ PL(parity latency)(*)) 
 - DDR5: Don't care 
(*)Only if CRCPARCTL1.caparity_disable_before_sr=0, this register must be increased by PL.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG5_t_cke_BitAddressOffset 0
#define DRAMSET1TMG5_t_cke_RegisterSize 6

/* Register DRAMSET1TMG5 field t_ckesr */
/* Minimum CKE low width for Self refresh or Self refresh power down entry to exit timing in memory clock cycles. 

Recommended settings:
    - LPDDR4: max(tCKE, tSR)
    - LPDDR5: tSR
    - DDR4: tCKESR (+ PL(parity latency)(*)) 
    - DDR5: Don't care 
(*)Only if CRCPARCTL1.caparity_disable_before_sr=0, this register must be increased by PL.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG5_t_ckesr_BitAddressOffset 8
#define DRAMSET1TMG5_t_ckesr_RegisterSize 7

/* Register DRAMSET1TMG5 field t_cksre */
/* This is the time after Self Refresh Down Entry/Power Down Entry that CK is maintained as a valid clock. Specifies the clock disable delay after SRE/PDE. 

   Recommended settings:
    - LPDDR4: tCKELCK
    - LPDDR5: tCSLCK
    - DDR4: tCKSRE (+ PL(parity latency)(*))
    - DDR5: tCKLCS 
(*)Only if CRCPARCTL1.caparity_disable_before_sr=0, this register must be increased by PL.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG5_t_cksre_BitAddressOffset 16
#define DRAMSET1TMG5_t_cksre_RegisterSize 6

/* Register DRAMSET1TMG5 field t_cksrx */
/* This is the time before Self Refresh Exit that CK is maintained as a valid clock before issuing SRX. Specifies the clock stable time before SRX. 

    Recommended settings:
    - LPDDR4: tCKCKEH
    - LPDDR5: tCKCSH
    - DDR4: tCKSRX 
    - DDR5: tCKSRX 
Unit: DRAM clock cycles. */
#define DRAMSET1TMG5_t_cksrx_BitAddressOffset 24
#define DRAMSET1TMG5_t_cksrx_RegisterSize 6

/* End of Register Definition for DRAMSET1TMG5 */

/* Register DRAMSET1TMG6 */
/* SDRAM Timing Register 6 belonging to Timing Set 1 */
// #define DRAMSET1TMG6 (REGB_FREQ0_CH0_BaseAddress + 0x18)
#define DRAMSET1TMG6_RegisterSize 32
#define DRAMSET1TMG6_RegisterResetValue 0x5
#define DRAMSET1TMG6_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG6 */

/* Register DRAMSET1TMG6 field t_ckcsx */
/* This is the time before Clock Stop Exit that CK is maintained as a valid clock before issuing Clock Stop Exit. Specifies the clock stable time before next command after Clock Stop Exit. 

    Recommended settings:
    - LPDDR4/5: tXP + 2
This is only present for designs supporting LPDDR devices.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG6_t_ckcsx_BitAddressOffset 0
#define DRAMSET1TMG6_t_ckcsx_RegisterSize 6

/* End of Register Definition for DRAMSET1TMG6 */

/* Register DRAMSET1TMG7 */
/* SDRAM Timing Register 7 belonging to Timing Set 1 */
// #define DRAMSET1TMG7 (REGB_FREQ0_CH0_BaseAddress + 0x1c)
#define DRAMSET1TMG7_RegisterSize 32
#define DRAMSET1TMG7_RegisterResetValue 0x0
#define DRAMSET1TMG7_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG7 */

/* Register DRAMSET1TMG7 field t_csh */
/* CS High Pulse width at PDX

    - LPDDR5: tCSH
Unit: DRAM clock cycles. */
#define DRAMSET1TMG7_t_csh_BitAddressOffset 0
#define DRAMSET1TMG7_t_csh_RegisterSize 4

/* End of Register Definition for DRAMSET1TMG7 */

/* Register DRAMSET1TMG8 */
/* SDRAM Timing Register 8 belonging to Timing Set 1 */
// #define DRAMSET1TMG8 (REGB_FREQ0_CH0_BaseAddress + 0x20)
#define DRAMSET1TMG8_RegisterSize 32
#define DRAMSET1TMG8_RegisterResetValue 0x4405
#define DRAMSET1TMG8_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG8 */

/* Register DRAMSET1TMG8 field t_xs_x32 */
/* tXS: Exit Self Refresh to commands not requiring a locked DLL.

Note: Used only for DDR4 and DDR5 SDRAMs.

Unit: Multiples of 32 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define DRAMSET1TMG8_t_xs_x32_BitAddressOffset 0
#define DRAMSET1TMG8_t_xs_x32_RegisterSize 7

/* Register DRAMSET1TMG8 field t_xs_dll_x32 */
/* tXSDLL: Exit Self Refresh to commands requiring a locked DLL.

Note: Used only for DDR4 and DDR5 SDRAMs.

Unit: Multiples of 32 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define DRAMSET1TMG8_t_xs_dll_x32_BitAddressOffset 8
#define DRAMSET1TMG8_t_xs_dll_x32_RegisterSize 7

/* End of Register Definition for DRAMSET1TMG8 */

/* Register DRAMSET1TMG9 */
/* SDRAM Timing Register 9 belonging to Timing Set 1 */
// #define DRAMSET1TMG9 (REGB_FREQ0_CH0_BaseAddress + 0x24)
#define DRAMSET1TMG9_RegisterSize 32
#define DRAMSET1TMG9_RegisterResetValue 0x4040d
#define DRAMSET1TMG9_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG9 */

/* Register DRAMSET1TMG9 field wr2rd_s */
/* 
Minimum time from write command to read command for different bank group. Includes time for bus turnaround, recovery times, and all per-bank, per-rank, and global constraints.

Applicable only in designs configured to support DDR SDRAM memories or LPDDR5 SDRAM memories.

DDR4/DDR5 designs:
CWL + PL + BL/2 + tWTR_S

Minimum time from write command to read command for different bank group. Includes time for bus turnaround, recovery times, and all per-bank, per-rank, and global constraints.

Where:
 - CWL = CAS write latency
 - PL = Parity latency
 - BL = burst length. This must match the value programmed in the BL bit of the mode register to the SDRAM
 - tWTR_S = internal write to read command delay for different bank group. This comes directly from the SDRAM specification.
WTR_S must be increased by one if DDR4 2tCK write preamble is used.

LPDDR5 designs:
WL + BL/n_min +RU(tWTR_S/tCK)

Where:
 - WL = Write Latency
 - BL/n_min = Effective Burst Length
 - tWTR_S = internal write to read command delay for different bank group.
Unit: DRAM clock cycles. */
#define DRAMSET1TMG9_wr2rd_s_BitAddressOffset 0
#define DRAMSET1TMG9_wr2rd_s_RegisterSize 8

/* Register DRAMSET1TMG9 field t_rrd_s */
/* tRRD_S: Minimum time between activates from bank "a" to bank "b" for different bank group.

Note: This register field is only applicable for designs supporting DDR4/DDR5/LPDDR5 SDRAM memories.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG9_t_rrd_s_BitAddressOffset 8
#define DRAMSET1TMG9_t_rrd_s_RegisterSize 6

/* Register DRAMSET1TMG9 field t_ccd_s */
/* tCCD_S: This is the minimum time between two reads or two writes for different bank group. For bank switching (from bank "a" to bank "b"), the minimum time is this value + 1.

Note: This register field is only applicable for designs supporting DDR4/LPDDR5 SDRAM memories.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG9_t_ccd_s_BitAddressOffset 16
#define DRAMSET1TMG9_t_ccd_s_RegisterSize 5

/* End of Register Definition for DRAMSET1TMG9 */

/* Register DRAMSET1TMG12 */
/* SDRAM Timing Register 12 belonging to Timing Set 1 */
// #define DRAMSET1TMG12 (REGB_FREQ0_CH0_BaseAddress + 0x30)
#define DRAMSET1TMG12_RegisterSize 32
#define DRAMSET1TMG12_RegisterResetValue 0x20000
#define DRAMSET1TMG12_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG12 */

/* Register DRAMSET1TMG12 field t_cmdcke */
/* tCMDCKE: Delay from valid command to PDE
 - LPDDR4: max(tESCKE, tCMDCKE)
 - LPDDR5: max(tESPD, tCMDPD)
Unit: DRAM clock cycles. */
#define DRAMSET1TMG12_t_cmdcke_BitAddressOffset 16
#define DRAMSET1TMG12_t_cmdcke_RegisterSize 4

/* End of Register Definition for DRAMSET1TMG12 */

/* Register DRAMSET1TMG13 */
/* SDRAM Timing Register 13 belonging to Timing Set 1 */
// #define DRAMSET1TMG13 (REGB_FREQ0_CH0_BaseAddress + 0x34)
#define DRAMSET1TMG13_RegisterSize 32
#define DRAMSET1TMG13_RegisterResetValue 0x1c200004
#define DRAMSET1TMG13_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG13 */

/* Register DRAMSET1TMG13 field t_ppd */
/* LPDDR4/5 and DDR5: tPPD: This is the minimum time from precharge to precharge command.

Note: This register is not applicable for DDR4 SDRAM memories.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG13_t_ppd_BitAddressOffset 0
#define DRAMSET1TMG13_t_ppd_RegisterSize 4

/* Register DRAMSET1TMG13 field t_ccd_mw */
/* This is the minimum time from write or masked write to masked write command for same bank.

 - LPDDR4: tCCDMW
 - LPDDR5(BG mode): 4*BL/n_max
 - LPDDR5(16B mode): 4*BL/n
Note: This register field is only applicable for designs supporting LPDDR4/LPDDR5 SDRAM memories.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG13_t_ccd_mw_BitAddressOffset 16
#define DRAMSET1TMG13_t_ccd_mw_RegisterSize 7

/* Register DRAMSET1TMG13 field odtloff */
/* LPDDR4: ODTLoff: This is the latency from CAS-2 command to ODToff reference.

Note: This register field is only applicable for designs supporting LPDDR4 SDRAM memories.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG13_odtloff_BitAddressOffset 24
#define DRAMSET1TMG13_odtloff_RegisterSize 7

/* End of Register Definition for DRAMSET1TMG13 */

/* Register DRAMSET1TMG14 */
/* SDRAM Timing Register 14 belonging to Timing Set 1 */
// #define DRAMSET1TMG14 (REGB_FREQ0_CH0_BaseAddress + 0x38)
#define DRAMSET1TMG14_RegisterSize 32
#define DRAMSET1TMG14_RegisterResetValue 0x800a0
#define DRAMSET1TMG14_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG14 */

/* Register DRAMSET1TMG14 field t_xsr */
/* tXSR: Exit Self Refresh to any command.

The value 0xfff is illegal for this register field. 

Unit: DRAM clock cycles. */
#define DRAMSET1TMG14_t_xsr_BitAddressOffset 0
#define DRAMSET1TMG14_t_xsr_RegisterSize 12

/* Register DRAMSET1TMG14 field t_osco */
/* tosco: Minimum time from DQS Oscillator stop to Mode register readout.

  LPDDR4 : max(40ns,8nck) 

  #LPDDR5 : TBD 

Unit: DRAM clock cycles. */
#define DRAMSET1TMG14_t_osco_BitAddressOffset 16
#define DRAMSET1TMG14_t_osco_RegisterSize 9

/* End of Register Definition for DRAMSET1TMG14 */

/* Register DRAMSET1TMG23 */
/* SDRAM Timing Register 23 belonging to Timing Set 1 */
// #define DRAMSET1TMG23 (REGB_FREQ0_CH0_BaseAddress + 0x5c)
#define DRAMSET1TMG23_RegisterSize 32
#define DRAMSET1TMG23_RegisterResetValue 0x0
#define DRAMSET1TMG23_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG23 */

/* Register DRAMSET1TMG23 field t_pdn */
/* Minimum interval between Deep Sleep Mode Entry and Exit.

  Unit: DRAM clock cycles. */
#define DRAMSET1TMG23_t_pdn_BitAddressOffset 0
#define DRAMSET1TMG23_t_pdn_RegisterSize 12

/* Register DRAMSET1TMG23 field t_pdn_dsm_x1024 */
/* Minimum Deep Sleep Mode duration time for DRAM compliance with IDDTBD power specification.

  Unit: Multiples of 1024 DRAM clock cycles. */
#define DRAMSET1TMG23_t_pdn_dsm_x1024_BitAddressOffset 12
#define DRAMSET1TMG23_t_pdn_dsm_x1024_RegisterSize 12

/* Register DRAMSET1TMG23 field t_xsr_dsm_x1024 */
/* Delay from Deep Sleep Mode Exit to SRX.

Unit: Multiples of 1024 DRAM clock cycles.

Please refer to "Note 1" from "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define DRAMSET1TMG23_t_xsr_dsm_x1024_BitAddressOffset 24
#define DRAMSET1TMG23_t_xsr_dsm_x1024_RegisterSize 8

/* End of Register Definition for DRAMSET1TMG23 */

/* Register DRAMSET1TMG24 */
/* SDRAM Timing Register 24 belonging to Timing Set 1 */
// #define DRAMSET1TMG24 (REGB_FREQ0_CH0_BaseAddress + 0x60)
#define DRAMSET1TMG24_RegisterSize 32
#define DRAMSET1TMG24_RegisterResetValue 0xf0f0f
#define DRAMSET1TMG24_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG24 */

/* Register DRAMSET1TMG24 field max_wr_sync */
/* Minimum time from write command to WCK2CK sync OFF.

  WL + BL/n_max 
 
  Unit: DRAM clock cycles. */
#define DRAMSET1TMG24_max_wr_sync_BitAddressOffset 0
#define DRAMSET1TMG24_max_wr_sync_RegisterSize 8

/* Register DRAMSET1TMG24 field max_rd_sync */
/* Minimum time from read command to WCK2CK sync OFF.

  RL + BL/n_max + RU(tRPST/tCK) 
 
  Unit: DRAM clock cycles. */
#define DRAMSET1TMG24_max_rd_sync_BitAddressOffset 8
#define DRAMSET1TMG24_max_rd_sync_RegisterSize 8

/* Register DRAMSET1TMG24 field rd2wr_s */
/* Minimum time from read command to write command for different bank group.

  Includes time for bus turnaround, recovery times and all per-bank, per-rank and global constraints.
  - LPDDR5(DQ ODT is disabled): RL + BL/n_min + RU(tWCKDQO(max)/tCK) - WL  
  - LPDDR5(DQ ODT is enabled): RL + BL/n_min + RU(tWCKDQO(max)/tCK) - RD(tRPST/tCK) - ODTLon - RD(tODTon(min)/tCK)  
  Unit: DRAM clock cycles. */
#define DRAMSET1TMG24_rd2wr_s_BitAddressOffset 16
#define DRAMSET1TMG24_rd2wr_s_RegisterSize 8

/* Register DRAMSET1TMG24 field bank_org */
/* Select Bank/ Bank group organization:
  - 00: 4 Banks/ 4 Bank groups  
  - 01: 8 Banks (Reserved)  
  - 10: 16 Banks 
  - 11: Reserved */
#define DRAMSET1TMG24_bank_org_BitAddressOffset 24
#define DRAMSET1TMG24_bank_org_RegisterSize 2

/* End of Register Definition for DRAMSET1TMG24 */

/* Register DRAMSET1TMG25 */
/* SDRAM Timing Register 25 belonging to Timing Set 1 */
// #define DRAMSET1TMG25 (REGB_FREQ0_CH0_BaseAddress + 0x64)
#define DRAMSET1TMG25_RegisterSize 32
#define DRAMSET1TMG25_RegisterResetValue 0x0
#define DRAMSET1TMG25_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG25 */

/* Register DRAMSET1TMG25 field rda2pre */
/* Time between read with AP and precharge to same bank.
  - LPDDR4: nRTP  
  - LPDDR5: BL/n_min + nRBTP  
  - DDR4: RTP  

Don't care for DDR5.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG25_rda2pre_BitAddressOffset 0
#define DRAMSET1TMG25_rda2pre_RegisterSize 8

/* Register DRAMSET1TMG25 field wra2pre */
/* Time between write with AP and precharge to same bank.
  - LPDDR4: WL + BL/2 + nWR + 1  
  - LPDDR5: WL + BL/n_min + nWR + 1  
  - DDR4: WL + BL/2 + WR  

Don't care for DDR5.

Unit: DRAM clock cycles. */
#define DRAMSET1TMG25_wra2pre_BitAddressOffset 8
#define DRAMSET1TMG25_wra2pre_RegisterSize 8

/* Register DRAMSET1TMG25 field lpddr4_diff_bank_rwa2pre */
/* 
  Set the timing constraint between different bank RD/WR/MWR/ACT and PRE in LPDDR4.

 - LPDDR4 JESD209-4A requires 4 cycles
 - LPDDR4 JESD209-4B requires 2 cycles
 Value of 1, 3, 5, 6, and 7 are illegal.
 
 Don't care for LPDDR5.
 */
#define DRAMSET1TMG25_lpddr4_diff_bank_rwa2pre_BitAddressOffset 16
#define DRAMSET1TMG25_lpddr4_diff_bank_rwa2pre_RegisterSize 3

/* End of Register Definition for DRAMSET1TMG25 */

/* Register DRAMSET1TMG30 */
/* SDRAM Timing Register 30 belonging to Timing Set 1 */
// #define DRAMSET1TMG30 (REGB_FREQ0_CH0_BaseAddress + 0x78)
#define DRAMSET1TMG30_RegisterSize 32
#define DRAMSET1TMG30_RegisterResetValue 0x0
#define DRAMSET1TMG30_RegisterResetMask 0xffffffff

/* Register Field information for DRAMSET1TMG30 */

/* Register DRAMSET1TMG30 field mrr2rd */
/* MRR to RD delay

  Unit: DRAM clock cycles. */
#define DRAMSET1TMG30_mrr2rd_BitAddressOffset 0
#define DRAMSET1TMG30_mrr2rd_RegisterSize 8

/* Register DRAMSET1TMG30 field mrr2wr */
/* MRR to WR delay

  Unit: DRAM clock cycles. */
#define DRAMSET1TMG30_mrr2wr_BitAddressOffset 8
#define DRAMSET1TMG30_mrr2wr_RegisterSize 8

/* Register DRAMSET1TMG30 field mrr2mrw */
/* MRR to MRW delay

  Unit: DRAM clock cycles. */
#define DRAMSET1TMG30_mrr2mrw_BitAddressOffset 16
#define DRAMSET1TMG30_mrr2mrw_RegisterSize 8

/* End of Register Definition for DRAMSET1TMG30 */

/* Register INITMR0 */
/* SDRAM Initialization MR Setting Register 0 */
// #define INITMR0 (REGB_FREQ0_CH0_BaseAddress + 0x500)
#define INITMR0_RegisterSize 32
#define INITMR0_RegisterResetValue 0x510
#define INITMR0_RegisterResetMask 0xffffffff

/* Register Field information for INITMR0 */

/* Register INITMR0 field emr */
/* 
 - DDR4: Value to write to MR1 register  Set bit 7 to 0.
 - DDR5: Don't care
 - LPDDR4 - Value to write to MR2 register */
#define INITMR0_emr_BitAddressOffset 0
#define INITMR0_emr_RegisterSize 16

/* Register INITMR0 field mr */
/* 
 - DDR4: Value loaded into MR0 register.
 - DDR5: Don't care
 - LPDDR4: Value to write to MR1 register
 */
#define INITMR0_mr_BitAddressOffset 16
#define INITMR0_mr_RegisterSize 16

/* End of Register Definition for INITMR0 */

/* Register INITMR1 */
/* SDRAM Initialization MR Setting Register 1 */
// #define INITMR1 (REGB_FREQ0_CH0_BaseAddress + 0x504)
#define INITMR1_RegisterSize 32
#define INITMR1_RegisterResetValue 0x0
#define INITMR1_RegisterResetMask 0xffffffff

/* Register Field information for INITMR1 */

/* Register INITMR1 field emr3 */
/* 
 - DDR4: Value to write to MR3 register
 - DDR5: Don't care
 - LPDDR4: Value to write to MR13 register */
#define INITMR1_emr3_BitAddressOffset 0
#define INITMR1_emr3_RegisterSize 16

/* Register INITMR1 field emr2 */
/* 
 - DDR4: Value to write to MR2 register
 - DDR5: Don't care
 - LPDDR4: Value to write to MR3 register
 */
#define INITMR1_emr2_BitAddressOffset 16
#define INITMR1_emr2_RegisterSize 16

/* End of Register Definition for INITMR1 */

/* Register INITMR2 */
/* SDRAM Initialization MR Setting Register 2 */
// #define INITMR2 (REGB_FREQ0_CH0_BaseAddress + 0x508)
#define INITMR2_RegisterSize 32
#define INITMR2_RegisterResetValue 0x0
#define INITMR2_RegisterResetMask 0xffffffff

/* Register Field information for INITMR2 */

/* Register INITMR2 field mr5 */
/* 
 - DDR4: Value to be loaded into SDRAM MR5 registers.
 - DDR5: Don't care
 - LPDDR4: Value to be loaded into SDRAM MR12 registers. */
#define INITMR2_mr5_BitAddressOffset 0
#define INITMR2_mr5_RegisterSize 16

/* Register INITMR2 field mr4 */
/* 
 - DDR4: Value to be loaded into SDRAM MR4 registers.
 - DDR5: Don't care
 - LPDDR4: Value to be loaded into SDRAM MR11 registers. */
#define INITMR2_mr4_BitAddressOffset 16
#define INITMR2_mr4_RegisterSize 16

/* End of Register Definition for INITMR2 */

/* Register INITMR3 */
/* SDRAM Initialization MR Setting Register 3 */
// #define INITMR3 (REGB_FREQ0_CH0_BaseAddress + 0x50c)
#define INITMR3_RegisterSize 32
#define INITMR3_RegisterResetValue 0x0
#define INITMR3_RegisterResetMask 0xffffffff

/* Register Field information for INITMR3 */

/* Register INITMR3 field mr6 */
/* 
 - DDR4 Value to be loaded into SDRAM MR6 registers.
 - DDR5: Don't care
 - LPDDR4 Value to be loaded into SDRAM MR14 registers. */
#define INITMR3_mr6_BitAddressOffset 0
#define INITMR3_mr6_RegisterSize 16

/* Register INITMR3 field mr22 */
/* 
 - LPDDR4 Value to be loaded into SDRAM MR22 registers.
 */
#define INITMR3_mr22_BitAddressOffset 16
#define INITMR3_mr22_RegisterSize 16

/* End of Register Definition for INITMR3 */

/* Register DFITMG0 */
/* DFI Timing Register 0 */
// #define DFITMG0 (REGB_FREQ0_CH0_BaseAddress + 0x580)
#define DFITMG0_RegisterSize 32
#define DFITMG0_RegisterResetValue 0x7020002
#define DFITMG0_RegisterResetMask 0xffffffff

/* Register Field information for DFITMG0 */

/* Register DFITMG0 field dfi_tphy_wrlat */
/* Write latency

Number of clocks from the write command to write data enable (dfi_wrdata_en).  This corresponds to the DFI timing parameter tphy_wrlat.

Refer to PHY specification for correct value.Note that, depending on the PHY, if using RDIMM/LRDIMM, it may be necessary to use the adjusted value of CL in the calculation of tphy_wrlat. This is to compensate for the extra cycle(s) of latency through the RDIMM/LRDIMM.

For LPDDR4, dfi_tphy_wrlat>60 is not supported.

Unit: DFI PHY clock cycles. */
#define DFITMG0_dfi_tphy_wrlat_BitAddressOffset 0
#define DFITMG0_dfi_tphy_wrlat_RegisterSize 6

/* Register DFITMG0 field dfi_tphy_wrdata */
/* Specifies the number of clock cycles between when dfi_wrdata_en is asserted to when the associated write data is driven on the dfi_wrdata signal.  This corresponds to the DFI timing parameter tphy_wrdata.  Refer to PHY specification for correct value. Note, max supported value is 8.

Unit: DFI PHY clock cycles. */
#define DFITMG0_dfi_tphy_wrdata_BitAddressOffset 8
#define DFITMG0_dfi_tphy_wrdata_RegisterSize 6

/* Register DFITMG0 field dfi_t_rddata_en */
/* Time from the assertion of a read command on the DFI interface to the assertion of the dfi_rddata_en signal.

Refer to PHY specification for correct value.

This corresponds to the DFI parameter trddata_en. Note that, depending on the PHY, if using RDIMM/LRDIMM, it may be necessary to use the adjusted value of CL in the calculation of trddata_en. This is to compensate for the extra cycle(s) of latency through the RDIMM/LRDIMM.

Unit: DFI PHY clock cycles. */
#define DFITMG0_dfi_t_rddata_en_BitAddressOffset 16
#define DFITMG0_dfi_t_rddata_en_RegisterSize 7

/* Register DFITMG0 field dfi_t_ctrl_delay */
/* Specifies the number of DFI clock cycles after an assertion or de-assertion of the DFI control signals that the control signals at the PHY-DRAM interface reflect the assertion or de-assertion. If the DRAM clock and the memory clock are not phase-aligned, this timing parameter must be rounded up to the next integer value. Note that if using RDIMM/LRDIMM, it is necessary to increment this parameter by RDIMM's/LRDIMM's extra cycle of latency in terms of DFI clock.

Unit: DFI clock cycles. */
#define DFITMG0_dfi_t_ctrl_delay_BitAddressOffset 24
#define DFITMG0_dfi_t_ctrl_delay_RegisterSize 5

/* End of Register Definition for DFITMG0 */

/* Register DFITMG1 */
/* DFI Timing Register 1 */
// #define DFITMG1 (REGB_FREQ0_CH0_BaseAddress + 0x584)
#define DFITMG1_RegisterSize 32
#define DFITMG1_RegisterResetValue 0x404
#define DFITMG1_RegisterResetMask 0xffffffff

/* Register Field information for DFITMG1 */

/* Register DFITMG1 field dfi_t_dram_clk_enable */
/* Specifies the number of DFI clock cycles from the de-assertion of the dfi_dram_clk_disable signal on the DFI until the first valid rising edge of the clock to the DRAM memory devices, at the PHY-DRAM boundary. If the DRAM clock and the memory clock are not phase aligned, this timing parameter must be rounded up to the next integer value.

Unit: DFI clock cycles. */
#define DFITMG1_dfi_t_dram_clk_enable_BitAddressOffset 0
#define DFITMG1_dfi_t_dram_clk_enable_RegisterSize 5

/* Register DFITMG1 field dfi_t_dram_clk_disable */
/* Specifies the number of DFI clock cycles from the assertion of the dfi_dram_clk_disable signal on the DFI until the clock to the DRAM memory devices, at the PHY-DRAM boundary, maintains a low value. If the DRAM clock and the memory clock are not phase aligned, this timing parameter must be rounded up to the next integer value.

Unit: DFI clock cycles. */
#define DFITMG1_dfi_t_dram_clk_disable_BitAddressOffset 8
#define DFITMG1_dfi_t_dram_clk_disable_RegisterSize 5

/* Register DFITMG1 field dfi_t_wrdata_delay */
/* Specifies the number of DFI clock cycles between when the dfi_wrdata_en signal is asserted and when the corresponding write data transfer is completed on the DRAM bus.

This corresponds to the DFI timing parameter twrdata_delay.

Refer to PHY specification for correct value.

Unit: DFI clock cycles. */
#define DFITMG1_dfi_t_wrdata_delay_BitAddressOffset 16
#define DFITMG1_dfi_t_wrdata_delay_RegisterSize 5

/* End of Register Definition for DFITMG1 */

/* Register DFITMG2 */
/* DFI Timing Register 2 */
// #define DFITMG2 (REGB_FREQ0_CH0_BaseAddress + 0x588)
#define DFITMG2_RegisterSize 32
#define DFITMG2_RegisterResetValue 0x202
#define DFITMG2_RegisterResetMask 0xffffffff

/* Register Field information for DFITMG2 */

/* Register DFITMG2 field dfi_tphy_wrcslat */
/* Number of DFI PHY clock cycles between when a write command is sent on the DFI control interface and when the associated dfi_wrdata_cs signal is asserted. This corresponds to the DFI timing parameter tphy_wrcslat.
 Refer to PHY specification for correct value.

Unit: DFI PHY clock cycles. */
#define DFITMG2_dfi_tphy_wrcslat_BitAddressOffset 0
#define DFITMG2_dfi_tphy_wrcslat_RegisterSize 6

/* Register DFITMG2 field dfi_tphy_rdcslat */
/* Number of DFI PHY clock cycles between when a read command is sent on the DFI control interface 
and when the associated dfi_rddata_cs signal is asserted. This corresponds to the DFI timing parameter tphy_rdcslat.
Refer to PHY specification for correct value.

Unit: DFI PHY clock cycles. */
#define DFITMG2_dfi_tphy_rdcslat_BitAddressOffset 8
#define DFITMG2_dfi_tphy_rdcslat_RegisterSize 7

/* End of Register Definition for DFITMG2 */

/* Register DFITMG4 */
/* DFI Timing Register 4 */
// #define DFITMG4 (REGB_FREQ0_CH0_BaseAddress + 0x590)
#define DFITMG4_RegisterSize 32
#define DFITMG4_RegisterResetValue 0x0
#define DFITMG4_RegisterResetMask 0xffffffff

/* Register Field information for DFITMG4 */

/* Register DFITMG4 field dfi_twck_dis */
/* WCK Off Timing.

  Defines the timing from the last command opportunity to the deassertion of dfi_wck_en and dfi_wck_toggle_en assuming that no command is being sent.

  Unit: WCK cycles */
#define DFITMG4_dfi_twck_dis_BitAddressOffset 0
#define DFITMG4_dfi_twck_dis_RegisterSize 8

/* Register DFITMG4 field dfi_twck_en_fs */
/* WCK Enable Fast Sync Timing.  Defines the timing from the CAS-WS_FS command to driving of the dfi_wck_en=ENABLED.

  Unit: WCK cycles */
#define DFITMG4_dfi_twck_en_fs_BitAddressOffset 8
#define DFITMG4_dfi_twck_en_fs_RegisterSize 8

/* Register DFITMG4 field dfi_twck_en_wr */
/* WCK Enable Read Timing.  Defines the timing from the CAS-WS_WR command to driving of the dfi_wck_en=ENABLED.

  Unit: WCK cycles */
#define DFITMG4_dfi_twck_en_wr_BitAddressOffset 16
#define DFITMG4_dfi_twck_en_wr_RegisterSize 8

/* Register DFITMG4 field dfi_twck_en_rd */
/* WCK Enable Read Timing.  Defines the timing from the CAS-WS_RD command to driving of the dfi_wck_en=ENABLED.

  Unit: WCK cycles */
#define DFITMG4_dfi_twck_en_rd_BitAddressOffset 24
#define DFITMG4_dfi_twck_en_rd_RegisterSize 8

/* End of Register Definition for DFITMG4 */

/* Register DFITMG5 */
/* DFI Timing Register 5 */
// #define DFITMG5 (REGB_FREQ0_CH0_BaseAddress + 0x594)
#define DFITMG5_RegisterSize 32
#define DFITMG5_RegisterResetValue 0x0
#define DFITMG5_RegisterResetMask 0xffffffff

/* Register Field information for DFITMG5 */

/* Register DFITMG5 field dfi_twck_toggle_post */
/* Defines the number of clock cycles after a read or write command data burst completion during which the WCK must remain in the current toggle state.

  Unit: WCK cycles */
#define DFITMG5_dfi_twck_toggle_post_BitAddressOffset 0
#define DFITMG5_dfi_twck_toggle_post_RegisterSize 8

/* Register DFITMG5 field dfi_twck_toggle_cs */
/* Defines the number of clock cycles between a read or write command to when the dfi_wck_cs signal must be stable.

  Unit: WCK cycles */
#define DFITMG5_dfi_twck_toggle_cs_BitAddressOffset 8
#define DFITMG5_dfi_twck_toggle_cs_RegisterSize 8

/* Register DFITMG5 field dfi_twck_toggle */
/* WCK Toggle Enable Timing. Defines the timing from dfi_wck_en assertion to dfi_wck_toggle_en assertion.

  Unit: WCK cycles */
#define DFITMG5_dfi_twck_toggle_BitAddressOffset 16
#define DFITMG5_dfi_twck_toggle_RegisterSize 8

/* Register DFITMG5 field dfi_twck_fast_toggle */
/* Defines the number of clock cycles between the dfi_wck_signal being driven to TOGGLE to when the dfi_wck_signal is driven to FAST_TOGGLE.

  This timing is only applicable when the WCK transitions from the slow to fast toggle. Otherwise, this timing parameter must be set to 0x0. 

  Unit: WCK cycles */
#define DFITMG5_dfi_twck_fast_toggle_BitAddressOffset 24
#define DFITMG5_dfi_twck_fast_toggle_RegisterSize 8

/* End of Register Definition for DFITMG5 */

/* Register DFILPTMG0 */
/* DFI Low Power Timing Register 0 */
// #define DFILPTMG0 (REGB_FREQ0_CH0_BaseAddress + 0x5a0)
#define DFILPTMG0_RegisterSize 32
#define DFILPTMG0_RegisterResetValue 0x0
#define DFILPTMG0_RegisterResetMask 0xffffffff

/* Register Field information for DFILPTMG0 */

/* Register DFILPTMG0 field dfi_lp_wakeup_pd */
/* Indicates the value in DFI clock cycles to drive on dfi_lp_ctrl_wakeup and dfi_lp_data_wakeup signals when Power Down mode is entered. 

Determines the DFI's tlp_wakeup time:
  - 0x00 - 1 cycle
  - 0x01 - 2 cycles
  - 0x02 - 4 cycles
  - 0x03 - 8 cycles
  - 0x04 - 16 cycles
  - 0x05 - 32 cycles
  - 0x06 - 64 cycles
  - 0x07 - 128 cycles
  - 0x08 - 256 cycles
  - 0x09 - 512 cycles
  - 0x0A - 1024 cycles
  - 0x0B - 2048 cycles
  - 0x0C - 4096 cycles
  - 0x0D - 8192 cycles
  - 0x0E - 16384 cycles
  - 0x0F - 32768 cycles
  - 0x10 - 65536 cycles
  - 0x11 - 131072 cycles
  - 0x12 - 262144 cycles
  - 0x13 - Unlimited
Unit: DFI clock cycles. */
#define DFILPTMG0_dfi_lp_wakeup_pd_BitAddressOffset 0
#define DFILPTMG0_dfi_lp_wakeup_pd_RegisterSize 5

/* Register DFILPTMG0 field dfi_lp_wakeup_sr */
/* Indicates the value in DFI clock cycles to drive on dfi_lp_ctrl_wakeup and dfi_lp_data_wakeup signals when Self Refresh mode is entered. 

Determines the DFI's tlp_wakeup time:
  - 0x00 - 1 cycle
  - 0x01 - 2 cycles
  - 0x02 - 4 cycles
  - 0x03 - 8 cycles
  - 0x04 - 16 cycles
  - 0x05 - 32 cycles
  - 0x06 - 64 cycles
  - 0x07 - 128 cycles
  - 0x08 - 256 cycles
  - 0x09 - 512 cycles
  - 0x0A - 1024 cycles
  - 0x0B - 2048 cycles
  - 0x0C - 4096 cycles
  - 0x0D - 8192 cycles
  - 0x0E - 16384 cycles
  - 0x0F - 32768 cycles
  - 0x10 - 65536 cycles
  - 0x11 - 131072 cycles
  - 0x12 - 262144 cycles
  - 0x13 - Unlimited
Unit: DFI clock cycles. */
#define DFILPTMG0_dfi_lp_wakeup_sr_BitAddressOffset 8
#define DFILPTMG0_dfi_lp_wakeup_sr_RegisterSize 5

/* Register DFILPTMG0 field dfi_lp_wakeup_dsm */
/* Indicates the value in DFI clock cycles to drive on dfi_lp_ctrl_wakeup and dfi_lp_data_wakeup signals when Deep Sleep Mode is entered. 

Determines the DFI's tlp_wakeup time:
  - 0x00 - 1 cycle
  - 0x01 - 2 cycles
  - 0x02 - 4 cycles
  - 0x03 - 8 cycles
  - 0x04 - 16 cycles
  - 0x05 - 32 cycles
  - 0x06 - 64 cycles
  - 0x07 - 128 cycles
  - 0x08 - 256 cycles
  - 0x09 - 512 cycles
  - 0x0A - 1024 cycles
  - 0x0B - 2048 cycles
  - 0x0C - 4096 cycles
  - 0x0D - 8192 cycles
  - 0x0E - 16384 cycles
  - 0x0F - 32768 cycles
  - 0x10 - 65536 cycles
  - 0x11 - 131072 cycles
  - 0x12 - 262144 cycles
  - 0x13 - Unlimited
This is only present for designs supporting LPDDR5 devices.

Unit: DFI clock cycles. */
#define DFILPTMG0_dfi_lp_wakeup_dsm_BitAddressOffset 16
#define DFILPTMG0_dfi_lp_wakeup_dsm_RegisterSize 5

/* End of Register Definition for DFILPTMG0 */

/* Register DFILPTMG1 */
/* DFI Low Power Timing Register 1 */
// #define DFILPTMG1 (REGB_FREQ0_CH0_BaseAddress + 0x5a4)
#define DFILPTMG1_RegisterSize 32
#define DFILPTMG1_RegisterResetValue 0x700
#define DFILPTMG1_RegisterResetMask 0xffffffff

/* Register Field information for DFILPTMG1 */

/* Register DFILPTMG1 field dfi_lp_wakeup_data */
/* Indicates the value in DFI clock cycles to drive on dfi_lp_data_wakeup signal when data bus is idle. 

Determines the DFI's tlp_wakeup time:
  - 0x00 - 1 cycle
  - 0x01 - 2 cycles
  - 0x02 - 4 cycles
  - 0x03 - 8 cycles
  - 0x04 - 16 cycles
  - 0x05 - 32 cycles
  - 0x06 - 64 cycles
  - 0x07 - 128 cycles
  - 0x08 - 256 cycles
  - 0x09 - 512 cycles
  - 0x0A - 1024 cycles
  - 0x0B - 2048 cycles
  - 0x0C - 4096 cycles
  - 0x0D - 8192 cycles
  - 0x0E - 16384 cycles
  - 0x0F - 32768 cycles
  - 0x10 - 65536 cycles
  - 0x11 - 131072 cycles
  - 0x12 - 262144 cycles
  - 0x13 - Unlimited
Unit: DFI clock cycles. */
#define DFILPTMG1_dfi_lp_wakeup_data_BitAddressOffset 0
#define DFILPTMG1_dfi_lp_wakeup_data_RegisterSize 5

/* Register DFILPTMG1 field dfi_tlp_resp */
/* Setting in DFI clock cycles for DFI's tlp_resp time. 

Same value is used for both Power Down, Self Refresh, Deep Sleep Mode and Maximum Power Saving modes. 

Refer to PHY databook for recommended values

Unit: DFI clock cycles. */
#define DFILPTMG1_dfi_tlp_resp_BitAddressOffset 8
#define DFILPTMG1_dfi_tlp_resp_RegisterSize 5

/* End of Register Definition for DFILPTMG1 */

/* Register DFIUPDTMG0 */
/* DFI Update Timing Register 0 */
// #define DFIUPDTMG0 (REGB_FREQ0_CH0_BaseAddress + 0x5a8)
#define DFIUPDTMG0_RegisterSize 32
#define DFIUPDTMG0_RegisterResetValue 0x400003
#define DFIUPDTMG0_RegisterResetMask 0xffffffff

/* Register Field information for DFIUPDTMG0 */

/* Register DFIUPDTMG0 field dfi_t_ctrlup_min */
/* Specifies the minimum number of DFI clock cycles that the dfi_ctrlupd_req signal must be asserted. The DDRCTL expects the PHY to respond within this time.  If the PHY does not respond, the DDRCTL will de-assert dfi_ctrlupd_req after dfi_t_ctrlup_min + 2 cycles.  Lowest value to assign to this variable is 0x1.

Unit: DFI clock cycles. */
#define DFIUPDTMG0_dfi_t_ctrlup_min_BitAddressOffset 0
#define DFIUPDTMG0_dfi_t_ctrlup_min_RegisterSize 10

/* Register DFIUPDTMG0 field dfi_t_ctrlup_max */
/* Specifies the maximum number of DFI clock cycles that the dfi_ctrlupd_req signal can assert. Lowest value to assign to this variable is 0x40.

Unit: DFI clock cycles. */
#define DFIUPDTMG0_dfi_t_ctrlup_max_BitAddressOffset 16
#define DFIUPDTMG0_dfi_t_ctrlup_max_RegisterSize 10

/* End of Register Definition for DFIUPDTMG0 */

/* Register DFIUPDTMG1 */
/* DFI Update Timing Register 1 */
// #define DFIUPDTMG1 (REGB_FREQ0_CH0_BaseAddress + 0x5ac)
#define DFIUPDTMG1_RegisterSize 32
#define DFIUPDTMG1_RegisterResetValue 0x10001
#define DFIUPDTMG1_RegisterResetMask 0xffffffff

/* Register Field information for DFIUPDTMG1 */

/* Register DFIUPDTMG1 field dfi_t_ctrlupd_interval_max_x1024 */
/* This is the maximum amount of time between DDRCTL initiated DFI update requests. This timer resets with each update request; when the timer expires dfi_ctrlupd_req is sent and traffic is blocked until the dfi_ctrlupd_ackx is received. PHY can use this idle time to recalibrate the delay lines to the DLLs. The DFI controller update is also used to reset PHY FIFO pointers in case of data capture errors. Updates are required to maintain calibration over PVT, but frequent updates may impact performance. Minimum allowed value for this field is 1.

Note: Value programmed for DFIUPD1.dfi_t_ctrlupd_interval_max_x1024 must be greater than DFIUPD1.dfi_t_ctrlupd_interval_min_x1024.

Unit: Multiples of 1024 DFI clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define DFIUPDTMG1_dfi_t_ctrlupd_interval_max_x1024_BitAddressOffset 0
#define DFIUPDTMG1_dfi_t_ctrlupd_interval_max_x1024_RegisterSize 8

/* Register DFIUPDTMG1 field dfi_t_ctrlupd_interval_min_x1024 */
/* This is the minimum amount of time between DDRCTL initiated DFI update requests (which is executed whenever the DDRCTL is idle). Set this number higher to reduce the frequency of update requests, which can have a small impact on the latency of the first read request when the DDRCTL is idle. Minimum allowed value for this field is 1.

Unit: Multiples of 1024 DFI clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define DFIUPDTMG1_dfi_t_ctrlupd_interval_min_x1024_BitAddressOffset 16
#define DFIUPDTMG1_dfi_t_ctrlupd_interval_min_x1024_RegisterSize 8

/* End of Register Definition for DFIUPDTMG1 */

/* Register DFIMSGTMG0 */
/* DFI MC-PHY Message Timing Register 0 */
// #define DFIMSGTMG0 (REGB_FREQ0_CH0_BaseAddress + 0x5b0)
#define DFIMSGTMG0_RegisterSize 32
#define DFIMSGTMG0_RegisterResetValue 0x4
#define DFIMSGTMG0_RegisterResetMask 0xffffffff

/* Register Field information for DFIMSGTMG0 */

/* Register DFIMSGTMG0 field dfi_t_ctrlmsg_resp */
/* This is the maximum amount in DFI clock cycles between the assertion of the dfi{0/1}_ctrlmsg_req signal to the assertion of the dfi{0/1}_ctrlmsg_ack signal. If the PHY does not acknowledge the request within dfi_t_ctrlmsg_resp cycles, the PHY must not acknowledge the request at all. In this case, the controller should de-assert the corresponding dfi{0/1}_ctrlmsg_req signal.

The timing values might vary based on the frequency ratio and user must reprogram if there is any change in the frequency ratio. Refer to PHY databook for recommended values
  
Unit: DFI clock cycles.
 */
#define DFIMSGTMG0_dfi_t_ctrlmsg_resp_BitAddressOffset 0
#define DFIMSGTMG0_dfi_t_ctrlmsg_resp_RegisterSize 8

/* End of Register Definition for DFIMSGTMG0 */

/* Register RFSHSET1TMG0 */
/* Refresh Timing Register 0 belonging to Timing Set 1 */
// #define RFSHSET1TMG0 (REGB_FREQ0_CH0_BaseAddress + 0x600)
#define RFSHSET1TMG0_RegisterSize 32
#define RFSHSET1TMG0_RegisterResetValue 0x2100062
#define RFSHSET1TMG0_RegisterResetMask 0xffffffff

/* Register Field information for RFSHSET1TMG0 */

/* Register RFSHSET1TMG0 field t_refi_x1_x32 */
/* Average time interval between refreshes per rank (Specification: 7.8us for DDR4, 3.9us for DDR5. See JEDEC specification for LPDDR4).

  set this register to RoundDown(tREFI/tCK)

  if RFSHSET1TMG0.t_refi_x1_sel = 0, divide the above result by 32 and round down.

  For LPDDR controller:
  - if using all-bank refreshes (RFSHMOD0.per_bank_refresh = 0), use tREFIab in the above calculations
  - if using per-bank refreshes (RFSHMOD0.per_bank_refresh = 1), use tREFIpb in the above calculations

For DDR controller, tREFI value is different depending on FGR mode.
  - In DDR4 mode, if using FGR 1x mode (RFSHMOD1.fgr_mode = 000), use tREFI1 in the above calculations
  - In DDR4 mode, if using FGR 2x mode (RFSHMOD1.fgr_mode = 001), use tREFI2 in the above calculations
  - In DDR4 mode, if using FGR 4x mode (RFSHMOD1.fgr_mode = 010), use tREFI4 in the above calculations
  - In DDR5 mode, always use tREFI1 in the above calculations
Note that:
  - RFSHSET1TMG0.t_refi_x1_x32 must be greater than 0x1.
  - if RFSHSET1TMG0.t_refi_x1_sel == 1, RFSHSET1TMG0.t_refi_x1_x32 must be greater than RFSHSET1TMG1.t_rfc_min
  - if RFSHSET1TMG0.t_refi_x1_sel == 0, RFSHSET1TMG0.t_refi_x1_x32 * 32 must be greater than RFSHSET1TMG1.t_rfc_min
  - In non-DDR4 or DDR4 Fixed 1x mode: RFSHSET1TMG0.t_refi_x1_x32 must be less than or equal to 0xFFE.
  - In DDR4 Fixed 2x mode: RFSHSET1TMG0.t_refi_x1_x32 must be less than or equal to 0x7FF.
  - In DDR4 Fixed 4x mode: RFSHSET1TMG0.t_refi_x1_x32 must be less than or equal to 0x3FF.
Unit: DRAM clock cycles or multiples of 32 DRAM clock cycles, depending on RFSHSET1TMG0.t_refi_x1_sel.
Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define RFSHSET1TMG0_t_refi_x1_x32_BitAddressOffset 0
#define RFSHSET1TMG0_t_refi_x1_x32_RegisterSize 12

/* Register RFSHSET1TMG0 field refresh_to_x1_x32 */
/* If the refresh timer (tRFCnom, also known as tREFI) has expired at least once, then a speculative refresh may be performed. A speculative refresh is a refresh performed at a time when refresh would be useful. When the SDRAM bus is idle for a period of time determined by this RFSHCTL0.refresh_to_x1_x32 and the refresh timer has expired at least once since the last refresh, then a speculative refresh is performed. Speculative refreshes continues successively until there are no refreshes pending or until new reads or writes are issued to the DDRCTL.

FOR PERFORMANCE ONLY. 

Unit: DRAM clock cycles or multiples of 32 DRAM clock cycles, depending on RFSHSET1TMG0.t_refi_x1_sel.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define RFSHSET1TMG0_refresh_to_x1_x32_BitAddressOffset 16
#define RFSHSET1TMG0_refresh_to_x1_x32_RegisterSize 6

/* Register RFSHSET1TMG0 field refresh_margin */
/* Threshold value in number of DRAM clock cycles before the critical refresh or page timer expires. A critical refresh is to be issued before this threshold is reached. It is recommended that this not be changed from the default value, currently shown as 0x2. It must always be less than internally used t_refi/32.
 Note that internally used t_refi is equal to RFSHSET1TMG0.t_refi_x1_x32 * 32 if RFSHSET1TMG0.t_refi_x1_sel=0. If RFSHSET1TMG0.t_refi_x1_sel=1 (for LPDDR4 per-bank refresh only), internally used t_refi is equal to RFSHSET1TMG0.t_refi_x1_x32. Note that, in LPDDR4, internally used t_refi may be divided by four if derating is enabled (DERATECTL0.derate_enable=1).

Unit: Multiples of 32 DRAM clock cycles. */
#define RFSHSET1TMG0_refresh_margin_BitAddressOffset 24
#define RFSHSET1TMG0_refresh_margin_RegisterSize 4

/* Register RFSHSET1TMG0 field t_refi_x1_sel */
/* Specifies whether the RFSHSET1TMG0.t_refi_x1_x32 and RFSHCTL0.refresh_to_x1_x32 register values are x1 or x32.
   - 0 - x32 register values are used
   - 1 - x1 register values are used.
This applies only when per-bank refresh is enabled (RFSHMOD0.per_bank_refresh=1); if per-bank refresh is not enabled, the x32 register values are used and this register field is ignored */
#define RFSHSET1TMG0_t_refi_x1_sel_BitAddressOffset 31
#define RFSHSET1TMG0_t_refi_x1_sel_RegisterSize 1

/* End of Register Definition for RFSHSET1TMG0 */

/* Register RFSHSET1TMG1 */
/* Refresh Timing Register 1 belonging to Timing Set 1 */
// #define RFSHSET1TMG1 (REGB_FREQ0_CH0_BaseAddress + 0x604)
#define RFSHSET1TMG1_RegisterSize 32
#define RFSHSET1TMG1_RegisterResetValue 0x8c
#define RFSHSET1TMG1_RegisterResetMask 0xffffffff

/* Register Field information for RFSHSET1TMG1 */

/* Register RFSHSET1TMG1 field t_rfc_min */
/* tRFC (min): Minimum time from refresh to refresh or activate.

t_rfc_min must be set to RoundUp(tRFCmin/tCK).

In LPDDR controller:
  - if using all-bank refreshes, the tRFCmin value in the above equations is equal to tRFCab
  - if using per-bank refreshes, the tRFCmin value in the above equations is equal to tRFCpb
In DDR4/DDR5 mode, the tRFCmin value in the above equations is different depending on the refresh mode (fixed 1X,2X,4X) and the device density. The user must program the appropriate value from the spec based on the 'fgr_mode' and the device density that is used.

Unit: DRAM clock cycles. */
#define RFSHSET1TMG1_t_rfc_min_BitAddressOffset 0
#define RFSHSET1TMG1_t_rfc_min_RegisterSize 12

/* End of Register Definition for RFSHSET1TMG1 */

/* Register RFSHSET1TMG2 */
/* Refresh Timing Register 2 belonging to Timing Set 1 */
// #define RFSHSET1TMG2 (REGB_FREQ0_CH0_BaseAddress + 0x608)
#define RFSHSET1TMG2_RegisterSize 32
#define RFSHSET1TMG2_RegisterResetValue 0x8c8c0000
#define RFSHSET1TMG2_RegisterResetMask 0xffffffff

/* Register Field information for RFSHSET1TMG2 */

/* Register RFSHSET1TMG2 field t_pbr2pbr */
/* 
  LPDDR4: tpbR2pbR

  Per-bank Refresh to Per-bank refresh different bank Time.

  Program this to RoundUp(tpbR2pbR/tCK).

  The tpbR2pbR value in the above equations is different depending on the device density. The user must program the appropriate value from the spec.

  Register is valid only in LPDDR4 per-bank refresh mode (RFSHMOD0.per_bank_refresh == 1).
 */
#define RFSHSET1TMG2_t_pbr2pbr_BitAddressOffset 16
#define RFSHSET1TMG2_t_pbr2pbr_RegisterSize 8

/* Register RFSHSET1TMG2 field t_pbr2act */
/* 
  Time from REFpb to activate command to different bank than REFpb.

  LPDDR5: tpbr2act
 */
#define RFSHSET1TMG2_t_pbr2act_BitAddressOffset 24
#define RFSHSET1TMG2_t_pbr2act_RegisterSize 8

/* End of Register Definition for RFSHSET1TMG2 */

/* Register RFSHSET1TMG4 */
/* Refresh Timing Register 4 belonging to Timing Set 1 */
// #define RFSHSET1TMG4 (REGB_FREQ0_CH0_BaseAddress + 0x610)
#define RFSHSET1TMG4_RegisterSize 32
#define RFSHSET1TMG4_RegisterResetValue 0x0
#define RFSHSET1TMG4_RegisterResetMask 0xffffffff

/* Register Field information for RFSHSET1TMG4 */

/* Register RFSHSET1TMG4 field refresh_timer0_start_value_x32 */
/* Refresh timer start for rank 0 (only present in multi-rank configurations). This is useful in staggering the refreshes to multiple ranks to help traffic to proceed. This is explained in Refresh Controls section of architecture chapter.

FOR PERFORMANCE ONLY.

Unit: Multiples of 32 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define RFSHSET1TMG4_refresh_timer0_start_value_x32_BitAddressOffset 0
#define RFSHSET1TMG4_refresh_timer0_start_value_x32_RegisterSize 12

/* Register RFSHSET1TMG4 field refresh_timer1_start_value_x32 */
/* Refresh timer start for rank 1 (only present in multi-rank configurations). This is useful in staggering the refreshes to multiple ranks to help traffic to proceed. This is explained in Refresh Controls section of architecture chapter.

FOR PERFORMANCE ONLY.

Unit: Multiples of 32 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define RFSHSET1TMG4_refresh_timer1_start_value_x32_BitAddressOffset 16
#define RFSHSET1TMG4_refresh_timer1_start_value_x32_RegisterSize 12

/* End of Register Definition for RFSHSET1TMG4 */

/* Register ZQSET1TMG0 */
/* ZQ Timing Register 0 belonging to DRAM ZQ timing set 1 */
// #define ZQSET1TMG0 (REGB_FREQ0_CH0_BaseAddress + 0x800)
#define ZQSET1TMG0_RegisterSize 32
#define ZQSET1TMG0_RegisterResetValue 0x400200
#define ZQSET1TMG0_RegisterResetMask 0xffffffff

/* Register Field information for ZQSET1TMG0 */

/* Register ZQSET1TMG0 field t_zq_long_nop */
/* tZQoper for DDR4, tZQCAL for DDR5/LPDDR4/LPDDR5: Number of DRAM clock cycles of NOP required after a ZQCL (ZQ calibration long)/MPC(ZQ Start) command is issued to SDRAM. If using LPDDR5, this register needs to be programmed to tZQCAL + 10 cycles.

Unit: DRAM clock cycles. */
#define ZQSET1TMG0_t_zq_long_nop_BitAddressOffset 0
#define ZQSET1TMG0_t_zq_long_nop_RegisterSize 14

/* Register ZQSET1TMG0 field t_zq_short_nop */
/* tZQCS for DD4, tZQLAT for DDR5/LPDDR4/LPDDR5: Number of DRAM clock cycles of NOP required after a ZQCS (ZQ calibration short)/MPC(ZQ Latch) command is issued to SDRAM.

Unit: DRAM clock cycles. */
#define ZQSET1TMG0_t_zq_short_nop_BitAddressOffset 16
#define ZQSET1TMG0_t_zq_short_nop_RegisterSize 10

/* End of Register Definition for ZQSET1TMG0 */

/* Register ZQSET1TMG1 */
/* ZQ Timing Register 1 belonging to DRAM ZQ timing set 1 */
// #define ZQSET1TMG1 (REGB_FREQ0_CH0_BaseAddress + 0x804)
#define ZQSET1TMG1_RegisterSize 32
#define ZQSET1TMG1_RegisterResetValue 0x2000100
#define ZQSET1TMG1_RegisterResetMask 0xffffffff

/* Register Field information for ZQSET1TMG1 */

/* Register ZQSET1TMG1 field t_zq_short_interval_x1024 */
/* Average interval to wait between automatically issuing ZQCS (ZQ calibration short)/MPC(ZQ calibration) commands to DDR4/LPDDR4 devices.

  Meaningless, if ZQCTL0.dis_auto_zq=1.

  Unit: Multiples of 1024 DRAM clock cycles.

  Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define ZQSET1TMG1_t_zq_short_interval_x1024_BitAddressOffset 0
#define ZQSET1TMG1_t_zq_short_interval_x1024_RegisterSize 20

/* Register ZQSET1TMG1 field t_zq_reset_nop */
/* tZQReset: Number of DRAM clock cycles of NOP required after a ZQReset (ZQ calibration Reset) command is issued to SDRAM.

  Unit: DRAM clock cycles. */
#define ZQSET1TMG1_t_zq_reset_nop_BitAddressOffset 20
#define ZQSET1TMG1_t_zq_reset_nop_RegisterSize 10

/* End of Register Definition for ZQSET1TMG1 */

/* Register DQSOSCCTL0 */
/* DQS/WCK Oscillator Control Register 0 */
// #define DQSOSCCTL0 (REGB_FREQ0_CH0_BaseAddress + 0xa80)
#define DQSOSCCTL0_RegisterSize 32
#define DQSOSCCTL0_RegisterResetValue 0x70
#define DQSOSCCTL0_RegisterResetMask 0xffffffff

/* Register Field information for DQSOSCCTL0 */

/* Register DQSOSCCTL0 field dqsosc_enable */
/* DQS/WCK Oscillator Enable 

  1: Enable DQS Oscillator 

  0: Disable DQS Oscillator */
#define DQSOSCCTL0_dqsosc_enable_BitAddressOffset 0
#define DQSOSCCTL0_dqsosc_enable_RegisterSize 1

/* Register DQSOSCCTL0 field dqsosc_interval_unit */
/* DQS/WCK Oscillator Interval unit. Specifies the unit for counting DQS oscillator interval.The value can be changed while DQSOSCCTL0.dqsosc_enable=0 

  1: x2K DFI clock cycles 

  0: x32K DFI clock cycles */
#define DQSOSCCTL0_dqsosc_interval_unit_BitAddressOffset 2
#define DQSOSCCTL0_dqsosc_interval_unit_RegisterSize 1

/* Register DQSOSCCTL0 field dqsosc_interval */
/* DQS Oscillator interval, specifies the time between two DQS oscillator sequences. Minimum programmable value is 1. The value can be changed while DQSOSCCTL0.dqsosc_enable=0 

  Unit: DFI clock cycles */
#define DQSOSCCTL0_dqsosc_interval_BitAddressOffset 4
#define DQSOSCCTL0_dqsosc_interval_RegisterSize 12

/* End of Register Definition for DQSOSCCTL0 */

/* Register DERATEINT */
/* Temperature Derate Interval Register */
// #define DERATEINT (REGB_FREQ0_CH0_BaseAddress + 0xb00)
#define DERATEINT_RegisterSize 32
#define DERATEINT_RegisterResetValue 0x800000
#define DERATEINT_RegisterResetMask 0xffffffff

/* Register Field information for DERATEINT */

/* Register DERATEINT field mr4_read_interval */
/* Interval between two MR4 reads, used to derate the timing parameters.

  This register must not be set to zero.

  Unit: DRAM clock cycles. */
#define DERATEINT_mr4_read_interval_BitAddressOffset 0
#define DERATEINT_mr4_read_interval_RegisterSize 32

/* End of Register Definition for DERATEINT */

/* Register DERATEVAL0 */
/* Temperature Derate Timing Register 0 */
// #define DERATEVAL0 (REGB_FREQ0_CH0_BaseAddress + 0xb04)
#define DERATEVAL0_RegisterSize 32
#define DERATEVAL0_RegisterResetValue 0x50f0504
#define DERATEVAL0_RegisterResetMask 0xffffffff

/* Register Field information for DERATEVAL0 */

/* Register DERATEVAL0 field derated_t_rrd */
/* Derated value for tRRD.

  For LPDDR4, the required period with derating is tRRD + 1.875ns

  For LPDDR5, the required period with derating is tRRD + TBD ns

  Unit:DRAM clock cycles. */
#define DERATEVAL0_derated_t_rrd_BitAddressOffset 0
#define DERATEVAL0_derated_t_rrd_RegisterSize 6

/* Register DERATEVAL0 field derated_t_rp */
/* Derated value for tRP.

  For LPDDR4, the required period with derating is tRP + 1.875ns

  For LPDDR5, the required period with derating is tRP + TBD ns

  Unit:DRAM clock cycles. */
#define DERATEVAL0_derated_t_rp_BitAddressOffset 8
#define DERATEVAL0_derated_t_rp_RegisterSize 7

/* Register DERATEVAL0 field derated_t_ras_min */
/* Derated value for tRAS.

  For LPDDR4, the required period with derating is tRAS + 1.875ns

  For LPDDR5, the required period with derating is tRAS + TBD ns

  Unit:DRAM clock cycles. */
#define DERATEVAL0_derated_t_ras_min_BitAddressOffset 16
#define DERATEVAL0_derated_t_ras_min_RegisterSize 8

/* Register DERATEVAL0 field derated_t_rcd */
/* Derated value for tRCD.

  For LPDDR4, the required period with derating is tRCD + 1.875ns

  For LPDDR5, the required period with derating is tRCD + TBD ns

  Unit:DRAM clock cycles. */
#define DERATEVAL0_derated_t_rcd_BitAddressOffset 24
#define DERATEVAL0_derated_t_rcd_RegisterSize 8

/* End of Register Definition for DERATEVAL0 */

/* Register DERATEVAL1 */
/* Temperature Derate Timing Register 1 */
// #define DERATEVAL1 (REGB_FREQ0_CH0_BaseAddress + 0xb08)
#define DERATEVAL1_RegisterSize 32
#define DERATEVAL1_RegisterResetValue 0x14
#define DERATEVAL1_RegisterResetMask 0xffffffff

/* Register Field information for DERATEVAL1 */

/* Register DERATEVAL1 field derated_t_rc */
/* Derated value for tRC.

  For LPDDR4, the required period with derating is tRC + 3.75ns

  For LPDDR5, the required period with derating is tRC + TBD ns

  Unit:DRAM clock cycles. */
#define DERATEVAL1_derated_t_rc_BitAddressOffset 0
#define DERATEVAL1_derated_t_rc_RegisterSize 8

/* End of Register Definition for DERATEVAL1 */

/* Register HWLPTMG0 */
/* Hardware Low Power Control Register */
// #define HWLPTMG0 (REGB_FREQ0_CH0_BaseAddress + 0xb80)
#define HWLPTMG0_RegisterSize 32
#define HWLPTMG0_RegisterResetValue 0x0
#define HWLPTMG0_RegisterResetMask 0xffffffff

/* Register Field information for HWLPTMG0 */

/* Register HWLPTMG0 field hw_lp_idle_x32 */
/* Hardware idle period. The cactive_ddrc output is driven low if the DDRC command channel is idle for hw_lp_idle * 32 cycles if not in INIT or DPD/MPSM operating_mode. The DDRC command channel is considered idle when there are no HIF commands outstanding. The hardware idle function is disabled when hw_lp_idle_x32=0. hw_lp_idle_x32=1 is an illegal value.

FOR PERFORMANCE ONLY.

Unit: Multiples of 32 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define HWLPTMG0_hw_lp_idle_x32_BitAddressOffset 16
#define HWLPTMG0_hw_lp_idle_x32_RegisterSize 12

/* End of Register Definition for HWLPTMG0 */

/* Register SCHEDTMG0 */
/* Scheduler Control Register */
// #define SCHEDTMG0 (REGB_FREQ0_CH0_BaseAddress + 0xc00)
#define SCHEDTMG0_RegisterSize 32
#define SCHEDTMG0_RegisterResetValue 0x0
#define SCHEDTMG0_RegisterResetMask 0xffffffff

/* Register Field information for SCHEDTMG0 */

/* Register SCHEDTMG0 field pageclose_timer */
/* This field works in conjunction with SCHED.pageclose.
It only has meaning if SCHED.pageclose==1.

If SCHED.pageclose==1 and pageclose_timer==0, then an auto-precharge may be scheduled for last read 
or write command in the CAM with a bank and page hit. 
Note, sometimes an explicit precharge is scheduled instead of the auto-precharge. See SCHED.pageclose for details of when this may happen.
If SCHED.pageclose==1 and pageclose_timer>0, then an auto-precharge is not scheduled for last read
or write command in the CAM with a bank and page hit.
Instead, a timer is started, with pageclose_timer as the initial value.
There is a timer on a per bank basis.
The timer decrements unless the next read or write in the CAM to a bank is a page hit.
It gets reset to pageclose_timer value if the next read or write in the CAM to a bank is a page hit.
Once the timer has reached zero, an explcit precharge will be attempted to be scheduled.

Unit: DRAM clock cycles. */
#define SCHEDTMG0_pageclose_timer_BitAddressOffset 0
#define SCHEDTMG0_pageclose_timer_RegisterSize 8

/* Register SCHEDTMG0 field rdwr_idle_gap */
/* When the preferred transaction store is empty for these many clock cycles, switch to the alternate transaction store if it is non-empty.

The read transaction store (both high and low priority) is the default preferred transaction store and the write transaction store is the alternative store.

When prefer write over read is set this is reversed.

0x0 is a legal value for this register. When set to 0x0, the transaction store switching will happen immediately when the switching conditions become true.

FOR PERFORMANCE ONLY.

Unit: DRAM clock cycles. */
#define SCHEDTMG0_rdwr_idle_gap_BitAddressOffset 8
#define SCHEDTMG0_rdwr_idle_gap_RegisterSize 7

/* End of Register Definition for SCHEDTMG0 */

/* Register PERFHPR1 */
/* High Priority Read CAM Register 1 */
// #define PERFHPR1 (REGB_FREQ0_CH0_BaseAddress + 0xc80)
#define PERFHPR1_RegisterSize 32
#define PERFHPR1_RegisterResetValue 0xf000001
#define PERFHPR1_RegisterResetMask 0xffffffff

/* Register Field information for PERFHPR1 */

/* Register PERFHPR1 field hpr_max_starve */
/* Number of DRAM clocks that the HPR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 will disable the starvation functionality; during normal operation, this function must not be disabled as it will cause excessive latencies.

FOR PERFORMANCE ONLY.

Unit: DRAM clock cycles. */
#define PERFHPR1_hpr_max_starve_BitAddressOffset 0
#define PERFHPR1_hpr_max_starve_RegisterSize 16

/* Register PERFHPR1 field hpr_xact_run_length */
/* 
Number of transactions that are serviced once the HPR queue goes critical is the smaller of:
 - (a) This number
 - (b) Number of transactions available.  
 Unit: Transaction.

FOR PERFORMANCE ONLY. */
#define PERFHPR1_hpr_xact_run_length_BitAddressOffset 24
#define PERFHPR1_hpr_xact_run_length_RegisterSize 8

/* End of Register Definition for PERFHPR1 */

/* Register PERFLPR1 */
/* Low Priority Read CAM Register 1 */
// #define PERFLPR1 (REGB_FREQ0_CH0_BaseAddress + 0xc84)
#define PERFLPR1_RegisterSize 32
#define PERFLPR1_RegisterResetValue 0xf00007f
#define PERFLPR1_RegisterResetMask 0xffffffff

/* Register Field information for PERFLPR1 */

/* Register PERFLPR1 field lpr_max_starve */
/* Number of DRAM clocks that the LPR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 will disable the starvation functionality; during normal operation, this function must not be disabled as it will cause excessive latencies.

FOR PERFORMANCE ONLY.

Unit: DRAM clock cycles. */
#define PERFLPR1_lpr_max_starve_BitAddressOffset 0
#define PERFLPR1_lpr_max_starve_RegisterSize 16

/* Register PERFLPR1 field lpr_xact_run_length */
/* 
Number of transactions that are serviced once the LPR queue goes critical is the smaller of:
 - (a) This number
 - (b) Number of transactions available.
Unit: Transaction.

FOR PERFORMANCE ONLY. */
#define PERFLPR1_lpr_xact_run_length_BitAddressOffset 24
#define PERFLPR1_lpr_xact_run_length_RegisterSize 8

/* End of Register Definition for PERFLPR1 */

/* Register PERFWR1 */
/* Write CAM Register 1 */
// #define PERFWR1 (REGB_FREQ0_CH0_BaseAddress + 0xc88)
#define PERFWR1_RegisterSize 32
#define PERFWR1_RegisterResetValue 0xf00007f
#define PERFWR1_RegisterResetMask 0xffffffff

/* Register Field information for PERFWR1 */

/* Register PERFWR1 field w_max_starve */
/* Number of DRAM clocks that the WR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 will disable the starvation functionality; during normal operation, this function must not be disabled as it will cause excessive latencies.

FOR PERFORMANCE ONLY.

Unit: DRAM clock cycles. */
#define PERFWR1_w_max_starve_BitAddressOffset 0
#define PERFWR1_w_max_starve_RegisterSize 16

/* Register PERFWR1 field w_xact_run_length */
/* 
Number of transactions that are serviced once the WR queue goes critical is the smaller of:
 - (a) This number 
 - (b) Number of transactions available.
Unit: Transaction.

FOR PERFORMANCE ONLY. */
#define PERFWR1_w_xact_run_length_BitAddressOffset 24
#define PERFWR1_w_xact_run_length_RegisterSize 8

/* End of Register Definition for PERFWR1 */

/* Register TMGCFG */
/* Timing Configuration Register */
// #define TMGCFG (REGB_FREQ0_CH0_BaseAddress + 0xd00)
#define TMGCFG_RegisterSize 32
#define TMGCFG_RegisterResetValue 0x0
#define TMGCFG_RegisterResetMask 0xffffffff

/* Register Field information for TMGCFG */

/* Register TMGCFG field frequency_ratio */
/* Selects the Frequency Ratio
For DDR4/DDR5/LPDDR4:
 
 - 0: 1:2 Mode
 - 1: 1:4 Mode
For LPDDR5:
 
 - 0: 1:1:2 Mode
 - 1: 1:1:4 Mode */
#define TMGCFG_frequency_ratio_BitAddressOffset 0
#define TMGCFG_frequency_ratio_RegisterSize 1

/* Register TMGCFG field dfi_freq_fsp */
/* This register value propergates to dfi_freq_fsp pin directly. */
#define TMGCFG_dfi_freq_fsp_BitAddressOffset 8
#define TMGCFG_dfi_freq_fsp_RegisterSize 2

/* End of Register Definition for TMGCFG */

/* Register RANKTMG0 */
/* Rank Control Timing 0 */
// #define RANKTMG0 (REGB_FREQ0_CH0_BaseAddress + 0xd04)
#define RANKTMG0_RegisterSize 32
#define RANKTMG0_RegisterResetValue 0x606
#define RANKTMG0_RegisterResetMask 0xffffffff

/* Register Field information for RANKTMG0 */

/* Register RANKTMG0 field diff_rank_rd_gap */
/* Only present for multi-rank configurations.

Indicates the number of clocks of gap in data responses when performing consecutive reads to different ranks.

This is used to switch the delays in the PHY to match the rank requirements.

This value must consider both PHY requirement and ODT requirement.
    - PHY requirement:
      tphy_rdcsgap (see PHY databook for value of tphy_rdcsgap)

      If read preamble is set to 2tCK(DDR4 only), must be increased by 1.

      If read postamble is set to 1.5tCK(LPDDR4 only), must be increased by 1.
    - ODT requirement:
      The value programmed in this register takes care of the ODT switch off timing requirement when switching ranks during reads:

     diff_rank_rd_gap must be a minimum of ODTCFG.rd_odt_hold - BL/2

Program this to the larger of PHY requirement or ODT requirement.

After PHY has completed training the value programmed may need to be increased. Refer to relevant PHY documentation.

Note that, if using DDR4-LRDIMM, refer to TRDRD timing requirements in JEDEC DDR4 Data Buffer (DDR4DB01) Specification.

For LPDDR5, Please set to "JEDEC formula + tphy_wckcsgap + board delay"

Please see PHY databook for the value of tphy_wckcsgap

Unit: DRAM clock cycles. */
#define RANKTMG0_diff_rank_rd_gap_BitAddressOffset 0
#define RANKTMG0_diff_rank_rd_gap_RegisterSize 8

/* Register RANKTMG0 field diff_rank_wr_gap */
/* Only present for multi-rank configurations.

Indicates the number of clocks of gap in data responses when performing consecutive writes to different ranks.

This is used to switch the delays in the PHY to match the rank requirements.
    This value must consider both PHY requirement and ODT requirement.
    - PHY requirement:
    tphy_wrcsgap (see PHY databook for value of tphy_wrcsgap)

 If CRC feature is enabled, must be increased by 1.

 If write preamble is set to 2tCK(DDR4 only), must be increased by 1.

 Write preamble is always set to 2tCK for LPDDR4, refer to PHY databook to see if this is already factored into tphy_wrcsgap value or if it needs to be increased by 1.

 If write postamble is set to 1.5tCK(LPDDR4 only), must be increased by 1.
    - ODT requirement:
 The value programmed in this register takes care of the ODT switch off timing requirement when switching ranks during writes.

 For LPDDR4, with DQ ODT enabled, diff_rank_wr_gap must be a minimum of ODTLoff - ODTLon - BL/2 + 1

 For other cases, diff_rank_wr_gap must be a minimum of ODTCFG.wr_odt_hold - BL/2

Program this to the larger of PHY requirement or ODT requirement.

After PHY has completed training the value programmed may need to be increased. Refer to relevant PHY documentation.

Note that, if using DDR4-LRDIMM, refer to TWRWR timing requirements in JEDEC DDR4 Data Buffer (DDR4DB01) Specification.

For LPDDR5, Please set to "JEDEC formula + tphy_wckcsgap + board delay"

Please see PHY databook for the value of tphy_wckcsgap

Unit: DRAM clock cycles. */
#define RANKTMG0_diff_rank_wr_gap_BitAddressOffset 8
#define RANKTMG0_diff_rank_wr_gap_RegisterSize 8

/* End of Register Definition for RANKTMG0 */

/* Register RANKTMG1 */
/* Rank Timing Register 1 */
// #define RANKTMG1 (REGB_FREQ0_CH0_BaseAddress + 0xd08)
#define RANKTMG1_RegisterSize 32
#define RANKTMG1_RegisterResetValue 0xf0f
#define RANKTMG1_RegisterResetMask 0xffffffff

/* Register Field information for RANKTMG1 */

/* Register RANKTMG1 field wr2rd_dr */
/* Minimum time from write command to read command for different rank. Includes time for bus turnaround, recovery times, and all per-bank, per-rank, and global constraints.

For LPDDR5, Please set to "JEDEC formula + tphy_wckcsgap + board delay"

Please see PHY databook for the value of tphy_wckcsgap

  Unit: DRAM clock cycles */
#define RANKTMG1_wr2rd_dr_BitAddressOffset 0
#define RANKTMG1_wr2rd_dr_RegisterSize 8

/* Register RANKTMG1 field rd2wr_dr */
/* Minimum time from read command to write command for different rank. Includes time for bus turnaround, recovery times, and all per-bank, per-rank, and global constraints.

For LPDDR5, Please set to "JEDEC formula + tphy_wckcsgap + board delay"

Please see PHY databook for the value of tphy_wckcsgap
  Unit: DRAM clock cycles */
#define RANKTMG1_rd2wr_dr_BitAddressOffset 8
#define RANKTMG1_rd2wr_dr_RegisterSize 8

/* End of Register Definition for RANKTMG1 */

/* Register PWRTMG */
/* Low Power Timing Register */
// #define PWRTMG (REGB_FREQ0_CH0_BaseAddress + 0xd0c)
#define PWRTMG_RegisterSize 32
#define PWRTMG_RegisterResetValue 0x400010
#define PWRTMG_RegisterResetMask 0xffffffff

/* Register Field information for PWRTMG */

/* Register PWRTMG field powerdown_to_x32 */
/* After this many clocks of the DDRC command channel being idle the DDRCTL automatically puts the SDRAM into power-down. The DDRC command channel is considered idle when there are no HIF commands outstanding. This must be enabled in the PWRCTL.powerdown_en.

FOR PERFORMANCE ONLY.

Unit: Multiples of 32 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define PWRTMG_powerdown_to_x32_BitAddressOffset 0
#define PWRTMG_powerdown_to_x32_RegisterSize 5

/* Register PWRTMG field selfref_to_x32 */
/* After this many clocks of the DDRC command channel being idle the DDRCTL automatically puts the SDRAM into Self Refresh.

The DDRC command channel is considered idle when there are no HIF commands outstanding. This must be enabled in the PWRCTL.selfref_en.

FOR PERFORMANCE ONLY.

Unit: Multiples of 32 DRAM clock cycles.

Please refer to "Note 1" from  "Notes on Timing Registers" at the start of "Register Descriptions" chapter for details on how to program this register field. */
#define PWRTMG_selfref_to_x32_BitAddressOffset 16
#define PWRTMG_selfref_to_x32_RegisterSize 8

/* End of Register Definition for PWRTMG */


