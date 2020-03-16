/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2018 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file mddr_defs.h
*
* @par Description:
*   Sets up the globals for the memory controller registers.
*
*   Notes: From RTL p3r51 release
*   Only updated offsets, have not updated shift/mask per register.
*
******************************************************************************/

// MDDR_GLOBALS_RTL32

#define MDDR_INT0_CNTL_OFFSET                          0x00000040
#define MDDR_INT1_CNTL_OFFSET                          0x00000050
#define MDDR_DIMM_TECH_OFFSET                          0x00000104
#define MDDR_ADDR_DECODE_CNTL_OFFSET                   0x00000108
#define MDDR_RANK_EN_CNTL_OFFSET                       0x0000010C
#define MDDR_TN_TOKEN_CNT_OFFSET                       0x00000110
#define MDDR_DIMM_SLOT0_CONFIG_OFFSET                  0x00000120
#define MDDR_DIMM_SLOT0_ADDR_OFFSET                    0x00000124
#define MDDR_DIMM_SLOT1_CONFIG_OFFSET                  0x00000140
#define MDDR_DIMM_SLOT1_ADDR_OFFSET                    0x00000144
#define MDDR_DDR_DFI_CMD_0_OFFSET                      0x00000240
#define MDDR_DDR_DFI_CMD_1_OFFSET                      0x00000244
#define MDDR_DDR_DFI_CMD_OPT_OFFSET                    0x00000248
#define MDDR_CMD_WDB_ACCESS_OFFSET                     0x00000250
#define MDDR_DDR_DFI_STATUS_0_OFFSET                   0x00000314
#define MDDR_DDR_DFI_STATUS_1_OFFSET                   0x00000318
#define MDDR_DDR_DFI_STATUS_2_OFFSET                   0x0000031C
#define MDDR_DDR_PHY_STATUS_0_OFFSET                   0x00000320
#define MDDR_DDR_PHY_STATUS_1_OFFSET                   0x00000324
#define MDDR_DDR_PHY_STATUS_2_OFFSET                   0x00000328
#define MDDR_CMD_RD_DATA_WORD00_OFFSET                 0x00000330
#define MDDR_CMD_RD_DATA_WORD01_OFFSET                 0x00000334
#define MDDR_CMD_RD_DATA_WORD02_OFFSET                 0x00000338
#define MDDR_CMD_RD_DATA_WORD03_OFFSET                 0x0000033C
#define MDDR_CMD_RD_DATA_WORD04_OFFSET                 0x00000340
#define MDDR_CMD_RD_DATA_WORD05_OFFSET                 0x00000344
#define MDDR_CMD_RD_DATA_WORD06_OFFSET                 0x00000348
#define MDDR_CMD_RD_DATA_WORD07_OFFSET                 0x0000034C
#define MDDR_CMD_RD_DATA_WORD08_OFFSET                 0x00000350
#define MDDR_CMD_RD_DATA_WORD09_OFFSET                 0x00000354
#define MDDR_CMD_RD_DATA_WORD10_OFFSET                 0x00000358
#define MDDR_CMD_RD_DATA_WORD11_OFFSET                 0x0000035C
#define MDDR_CMD_RD_DATA_WORD12_OFFSET                 0x00000360
#define MDDR_CMD_RD_DATA_WORD13_OFFSET                 0x00000364
#define MDDR_CMD_RD_DATA_WORD14_OFFSET                 0x00000368
#define MDDR_CMD_RD_DATA_WORD15_OFFSET                 0x0000036C
#define MDDR_CMD_RD_DATA_WORD16_OFFSET                 0x00000370
#define MDDR_CMD_RD_DATA_WORD17_OFFSET                 0x00000374
#define MDDR_CMD_WR_DATA_WORD00_OFFSET                 0x00000380
#define MDDR_CMD_WR_DATA_WORD01_OFFSET                 0x00000384
#define MDDR_CMD_WR_DATA_WORD02_OFFSET                 0x00000388
#define MDDR_CMD_WR_DATA_WORD03_OFFSET                 0x0000038C
#define MDDR_CMD_WR_DATA_WORD04_OFFSET                 0x00000390
#define MDDR_CMD_WR_DATA_WORD05_OFFSET                 0x00000394
#define MDDR_CMD_WR_DATA_WORD06_OFFSET                 0x00000398
#define MDDR_CMD_WR_DATA_WORD07_OFFSET                 0x0000039C
#define MDDR_CMD_WR_DATA_WORD08_OFFSET                 0x000003A0
#define MDDR_CMD_WR_DATA_WORD09_OFFSET                 0x000003A4
#define MDDR_CMD_EXEC_CNTL_6_OFFSET                    0x000003F8
#define MDDR_CMD_EXEC_CNTL_7_OFFSET                    0x000003FC
#define MDDR_CMD_EXEC_CNTL_0_OFFSET                    0x00000400
#define MDDR_CMD_EXEC_CNTL_1_OFFSET                    0x00000404
#define MDDR_CMD_EXEC_CNTL_2_OFFSET                    0x00000408
#define MDDR_CMD_EXEC_CNTL_3_OFFSET                    0x0000040C
#define MDDR_CMD_EXEC_CNTL_4_OFFSET                    0x00000410
#define MDDR_CMD_EXEC_CNTL_5_OFFSET                    0x00000414
#define MDDR_DATAFLOW_CNTL_OFFSET                      0x00000418
#define MDDR_DDR_CA_BUS_CNTL_OFFSET                    0x00000438
#define MDDR_DDR_DQ_BUS_CNTL_OFFSET                    0x0000043C
#define MDDR_DDR_AUTO_REF_EN_OFFSET                    0x00000440
#define MDDR_DDR_PWR_DOWN_CNTL_OFFSET                  0x00000448
#define MDDR_DDR_SELF_REF_CNTL_OFFSET                  0x0000044C
#define MDDR_DDR_ZQCAL_EN_OFFSET                       0x00000450
#define MDDR_DDR_ZQCAL_CNTL_OFFSET                     0x00000454
#define MDDR_DDR_ODT_WR_CNTL_OFFSET                    0x00000458
#define MDDR_DDR_ODT_RD_CNTL_OFFSET                    0x0000045C
#define MDDR_RD_WR_PREF_CNTL_OFFSET                    0x00000474
#define MDDR_DDR_DFI_CNTL_OFFSET                       0x00000480
#define MDDR_DDR_PHY_CNTL_OFFSET                       0x00000484
#define MDDR_DDR_DFI_CNTL_1_OFFSET                     0x00000488
#define MDDR_DDR_SELF_REF_CMD_0_OFFSET                 0x00000490
#define MDDR_DDR_SELF_REF_CMD_1_OFFSET                 0x00000494
#define MDDR_DDR_SELF_REF_CMD_2_OFFSET                 0x00000498
#define MDDR_DDR_SELF_REF_CMD_3_OFFSET                 0x0000049C
#define MDDR_DDR_SELF_REF_CMD_4_OFFSET                 0x000004A0
#define MDDR_DDR_SELF_REF_CMD_5_OFFSET                 0x000004A4
#define MDDR_DDR_SELF_REF_CMD_6_OFFSET                 0x000004A8
#define MDDR_DDR_SELF_REF_CMD_7_OFFSET                 0x000004AC
#define MDDR_DDR_SELF_REF_CMD_8_OFFSET                 0x000004B0
#define MDDR_DDR_SELF_REF_CMD_9_OFFSET                 0x000004B4
#define MDDR_DDR_SELF_REF_CMD_10_OFFSET                0x000004B8
#define MDDR_DDR_SELF_REF_CMD_11_OFFSET                0x000004BC
#define MDDR_DDR_SELF_REF_CMD_12_OFFSET                0x000004C0
#define MDDR_DDR_SELF_REF_CMD_13_OFFSET                0x000004C4
#define MDDR_DDR_SELF_REF_CMD_14_OFFSET                0x000004C8
#define MDDR_DDR_SELF_REF_CMD_15_OFFSET                0x000004CC
#define MDDR_TIMING_DRAM_RDWR_0_OFFSET                 0x00000500
#define MDDR_TIMING_DRAM_RDWR_1_OFFSET                 0x00000504
#define MDDR_TIMING_DRAM_RDWR_2_OFFSET                 0x00000508
#define MDDR_TIMING_DRAM_RDWR_3_OFFSET                 0x0000050C
#define MDDR_TIMING_DRAM_RDWR_4_OFFSET                 0x00000510
#define MDDR_TIMING_DRAM_AUTO_REF_0_OFFSET             0x00000514
#define MDDR_TIMING_DRAM_AUTO_REF_1_OFFSET             0x00000518
#define MDDR_TIMING_DRAM_AUTO_REF_2_OFFSET             0x0000051C
#define MDDR_TIMING_DRAM_PWR_DOWN_0_OFFSET             0x00000520
#define MDDR_TIMING_DRAM_PWR_DOWN_1_OFFSET             0x00000524
#define MDDR_TIMING_DRAM_SELF_REF_0_OFFSET             0x00000528
#define MDDR_TIMING_DRAM_SELF_REF_1_OFFSET             0x0000052C
#define MDDR_TIMING_DRAM_SELF_REF_2_OFFSET             0x00000530
#define MDDR_TIMING_DRAM_ZQ_0_OFFSET                   0x00000534
#define MDDR_TIMING_DRAM_ZQ_1_OFFSET                   0x00000538
#define MDDR_TIMING_DRAM_MR_0_OFFSET                   0x0000053C
#define MDDR_TIMING_DRAM_MR_1_OFFSET                   0x00000540
#define MDDR_TIMING_DRAM_MPSM_OFFSET                   0x00000544
#define MDDR_TIMING_ODT_OFFSET                         0x00000548
#define MDDR_TIMING_GEAR_DOWN_OFFSET                   0x0000054C
#define MDDR_TIMING_ADJ_RDWR_0_OFFSET                  0x00000550
#define MDDR_TIMING_ADJ_RDWR_1_OFFSET                  0x00000554
#define MDDR_TIMING_ADJ_AUTO_REF_OFFSET                0x00000558
#define MDDR_TIMING_ADJ_ZQ_OFFSET                      0x0000055C
#define MDDR_TIMING_DFI_0_OFFSET                       0x00000560
#define MDDR_TIMING_DFI_1_OFFSET                       0x00000564
#define MDDR_TIMING_RCD_OFFSET                         0x00000568
#define MDDR_TIMING_DQ_BUS_OFFSET                      0x0000056C
#define MDDR_TIMING_DRAM_AUTO_REF_3_OFFSET             0x00000570
#define MDDR_TIMING_DFI_2_OFFSET                       0x00000574
#define MDDR_SCRUB_ADDR_WR_0_OFFSET                    0x00000600
#define MDDR_SCRUB_ADDR_WR_1_OFFSET                    0x00000604
#define MDDR_SCRUB_ADDR_RD_0_OFFSET                    0x00000608
#define MDDR_SCRUB_ADDR_RD_1_OFFSET                    0x0000060C
#define MDDR_SCRUB_CMD_CNTL_OFFSET                     0x00000610
#define MDDR_SCRUB_EXEC_CNTL_OFFSET                    0x00000614
#define MDDR_SCRUB_CMD_SINGLE_OFFSET                   0x00000618
#define MDDR_SCRUB_STATUS_OFFSET                       0x0000061C
#define MDDR_LFSR_MISCOMPARES_OFFSET                   0x00000620
#define MDDR_LFSR_COMPARE_OKS_OFFSET                   0x00000624
#define MDDR_WDB_FLUSH_WM_OFFSET                       0x00000680
#define MDDR_WDB_FLUSH_CNTL_OFFSET                     0x00000684
#define MDDR_WDB_FLUSH_PH_OFFSET                       0x00000688
#define MDDR_DATAFLOW_CDE_CNTL_0_OFFSET                0x00000700
#define MDDR_DATAFLOW_CDE_CNTL_1_OFFSET                0x00000704
#define MDDR_DATAFLOW_CDE_STATUS_0_OFFSET              0x00000708
#define MDDR_DRAM_VREFDQ_CS0_0_OFFSET                  0x00000800
#define MDDR_DRAM_VREFDQ_CS0_1_OFFSET                  0x00000804
#define MDDR_DRAM_VREFDQ_CS0_2_OFFSET                  0x00000808
#define MDDR_DRAM_VREFDQ_CS0_3_OFFSET                  0x0000080C
#define MDDR_DRAM_VREFDQ_CS0_4_OFFSET                  0x00000810
#define MDDR_DRAM_VREFDQ_CS1_0_OFFSET                  0x00000814
#define MDDR_DRAM_VREFDQ_CS1_1_OFFSET                  0x00000818
#define MDDR_DRAM_VREFDQ_CS1_2_OFFSET                  0x0000081C
#define MDDR_DRAM_VREFDQ_CS1_3_OFFSET                  0x00000820
#define MDDR_DRAM_VREFDQ_CS1_4_OFFSET                  0x00000824
#define MDDR_DRAM_VREFDQ_CS2_0_OFFSET                  0x00000828
#define MDDR_DRAM_VREFDQ_CS2_1_OFFSET                  0x0000082C
#define MDDR_DRAM_VREFDQ_CS2_2_OFFSET                  0x00000830
#define MDDR_DRAM_VREFDQ_CS2_3_OFFSET                  0x00000834
#define MDDR_DRAM_VREFDQ_CS2_4_OFFSET                  0x00000838
#define MDDR_DRAM_VREFDQ_CS3_0_OFFSET                  0x0000083C
#define MDDR_DRAM_VREFDQ_CS3_1_OFFSET                  0x00000840
#define MDDR_DRAM_VREFDQ_CS3_2_OFFSET                  0x00000844
#define MDDR_DRAM_VREFDQ_CS3_3_OFFSET                  0x00000848
#define MDDR_DRAM_VREFDQ_CS3_4_OFFSET                  0x0000084C
#define MDDR_DDR_DEVICE_STATE_OFFSET                   0x00010300
#define MDDR_DDR_IDLE_STATUS_PCHG_OFFSET               0x00010304
#define MDDR_DDR_IDLE_STATUS_ACT_OFFSET                0x00010308
#define MDDR_DDR_RANK_AVAIL_OFFSET                     0x0001030C
#define MDDR_DDR_CMD_STATUS_OFFSET                     0x00010310
#define MDDR_DDR_INTERNAL_STATUS_0_OFFSET              0x00010314
#define MDDR_DDR_THERMAL_CNTL_0_OFFSET                 0x00010460
#define MDDR_DDR_THERMAL_CNTL_1_OFFSET                 0x00010464
#define MDDR_DDR_THERMAL_CNTL_2_OFFSET                 0x00010468
#define MDDR_DDR_THERMAL_CNTL_3_OFFSET                 0x0001046C
#define MDDR_DDR_THERMAL_CNTL_4_OFFSET                 0x00010470
#define MDDR_FREQ_SWITCH_CNTL_OFFSET                   0x00010478
#define MDDR_DATAFLOW_CDE_CNTL_2_OFFSET                0x00010500
#define MDDR_DATAFLOW_CDE_CNTL_3_OFFSET                0x00010504
#define MDDR_DATAFLOW_CDE_CNTL_4_OFFSET                0x00010508
#define MDDR_DATAFLOW_CDE_CNTL_5_OFFSET                0x0001050C
#define MDDR_DATAFLOW_CDE_CNTL_6_OFFSET                0x00010510
#define MDDR_HW_ID_OFFSET                              0x00020000
#define MDDR_HW_VERSION_OFFSET                         0x00020004
#define MDDR_DCVS_CNTL_OFFSET                          0x00020008
#define MDDR_DCVS_BCQFULL_HIGH_THRESHOLD_1_OFFSET      0x00020014
#define MDDR_DCVS_BCQFULL_HIGH_THRESHOLD_2_OFFSET      0x00020018
#define MDDR_DCVS_BCQFULL_HIGH_THRESHOLD_3_OFFSET      0x0002001C
#define MDDR_DCVS_BCQFULL_HIGH_THRESHOLD_4_OFFSET      0x00020020
#define MDDR_DCVS_BCQFULL_LOW_THRESHOLD_1_OFFSET       0x00020024
#define MDDR_DCVS_BCQFULL_LOW_THRESHOLD_2_OFFSET       0x00020028
#define MDDR_DCVS_BCQFULL_LOW_THRESHOLD_3_OFFSET       0x0002002C
#define MDDR_DCVS_BCQFULL_LOW_THRESHOLD_4_OFFSET       0x00020030
#define MDDR_DCVS_BUSY_HIGH_THRESHOLD_1_OFFSET         0x00020034
#define MDDR_DCVS_BUSY_HIGH_THRESHOLD_2_OFFSET         0x00020038
#define MDDR_DCVS_BUSY_HIGH_THRESHOLD_3_OFFSET         0x0002003C
#define MDDR_DCVS_BUSY_HIGH_THRESHOLD_4_OFFSET         0x00020040
#define MDDR_DCVS_BUSY_LOW_THRESHOLD_1_OFFSET          0x00020044
#define MDDR_DCVS_BUSY_LOW_THRESHOLD_2_OFFSET          0x00020048
#define MDDR_DCVS_BUSY_LOW_THRESHOLD_3_OFFSET          0x0002004C
#define MDDR_DCVS_BUSY_LOW_THRESHOLD_4_OFFSET          0x00020050
#define MDDR_DCVS_BCQFULL_SHADOW_OFFSET                0x00020054
#define MDDR_DCVS_BUSY_SHADOW_OFFSET                   0x00020058
#define MDDR_DDR_MANUAL_OFFSET                         0x00020200
#define MDDR_DDR_MANUAL_CKE_OFFSET                     0x00020204
#define MDDR_DDR_MANUAL_RANK_OFFSET                    0x00020208
#define MDDR_DDR_MANUAL_OPT_0_OFFSET                   0x0002020C
#define MDDR_DDR_MANUAL_OPT_1_OFFSET                   0x00020210
#define MDDR_DDR_MANUAL_OPT_2_OFFSET                   0x00020214
#define MDDR_DDR_STOP_ACT_OFFSET                       0x00020220
#define MDDR_DDR_STOP_COL_OFFSET                       0x00020224
#define MDDR_DDR_PCHG_ASAP_OFFSET                      0x00020228
#define MDDR_HW_TIMER_OFFSET                           0x00020230
#define MDDR_CSR_CNTL_OFFSET                           0x00020234
#define MDDR_DDR_AUTO_REF_CNTL_OFFSET                  0x00020238
#define MDDR_DRAM_MR_3_OFFSET                          0x0002040C
#define MDDR_DB_BCW_0_OFFSET                           0x00020600
#define MDDR_ERR_CNTL_OFFSET                           0x00030030
#define MDDR_ERR_CAP_CNTL_OFFSET                       0x000300F0
#define MDDR_ERR_STATUS_OFFSET                         0x00040010
#define MDDR_ERR_CLR_OFFSET                            0x00040020
#define MDDR_ERR_CAP_0_OFFSET                          0x00040080
#define MDDR_ERR_CAP_1_OFFSET                          0x00040090
#define MDDR_ERR_CAP_2_OFFSET                          0x000400A0
#define MDDR_ERR_CAP_3_OFFSET                          0x000400B0
#define MDDR_ERR_CAP_4_OFFSET                          0x000400C0
#define MDDR_ERR_CAP_5_OFFSET                          0x000400D0
#define MDDR_ERR_CAP_6_OFFSET                          0x000400E0
#define MDDR_ERR_CAP_7_OFFSET                          0x000400F0
#define MDDR_ERR_CAP_8_OFFSET                          0x00040100
#define MDDR_ERR_CAP_9_OFFSET                          0x00040110
#define MDDR_ERR_CAP_10_OFFSET                         0x00040120
#define MDDR_ERR_CAP_11_OFFSET                         0x00040130
#define MDDR_ERR_CAP_12_OFFSET                         0x00040140
#define MDDR_ECC_ERR_CNTL_0_OFFSET                     0x000407FC
#define MDDR_ECC_ERR_CNTL_1_OFFSET                     0x00040800
#define MDDR_ECC_ERR_CNTL_2_OFFSET                     0x00040804
#define MDDR_ECC_CE_STATUS_0_OFFSET                    0x00040808
#define MDDR_ECC_CE_STATUS_1_OFFSET                    0x0004080C
#define MDDR_ECC_CE_STATUS_2_OFFSET                    0x00040810
#define MDDR_ECC_CE_STATUS_3_OFFSET                    0x00040814
#define MDDR_ECC_CE_STATUS_4_OFFSET                    0x00040818
#define MDDR_ECC_CE_STATUS_5_OFFSET                    0x0004081C
#define MDDR_ECC_CE_STATUS_6_OFFSET                    0x00040820
#define MDDR_ECC_CE_STATUS_7_OFFSET                    0x00040824
#define MDDR_ECC_CE_CNTR_0_OFFSET                      0x00040828
#define MDDR_ECC_CE_CNTR_1_OFFSET                      0x0004082C
#define MDDR_ECC_CE_CNTR_2_OFFSET                      0x00040830
#define MDDR_ECC_CE_CNTR_3_OFFSET                      0x00040834
#define MDDR_ECC_CE_CNTR_TOTAL_OFFSET                  0x00040838
#define MDDR_ECC_UE_CNTR_0_OFFSET                      0x0004083C
#define MDDR_ECC_UE_CNTR_1_OFFSET                      0x00040840
#define MDDR_ECC_UE_CNTR_2_OFFSET                      0x00040844
#define MDDR_ECC_UE_CNTR_3_OFFSET                      0x00040848
#define MDDR_ECC_UE_CNTR_TOTAL_OFFSET                  0x0004084C
#define MDDR_ERR_INJ_OFFSET                            0x00050060
#define MDDR_QSB_TOKEN_COUNTERS_OFFSET                 0x00050254
#define MDDR_ERR_INJ_WR_ADDR_0_OFFSET                  0x000505D8
#define MDDR_ERR_INJ_WR_ADDR_1_OFFSET                  0x000505DC
#define MDDR_ERR_INJ_WR_MASK_0_OFFSET                  0x000505E0
#define MDDR_ERR_INJ_WR_MASK_1_OFFSET                  0x000505E4
#define MDDR_ERR_INJ_WR_CNTL_OFFSET                    0x000505E8
#define MDDR_ERR_INJ_RD_ADDR_0_OFFSET                  0x000505EC
#define MDDR_ERR_INJ_RD_ADDR_1_OFFSET                  0x000505F0
#define MDDR_ERR_INJ_RD_MASK_0_OFFSET                  0x000505F4
#define MDDR_ERR_INJ_RD_MASK_1_OFFSET                  0x000505F8
#define MDDR_ERR_INJ_RD_CNTL_OFFSET                    0x000505FC
#define MDDR_TEST_GLOBAL_CNTL_OFFSET                   0x00050700
#define MDDR_TEST_PROGRAM_CNTL_OFFSET                  0x00050704
#define MDDR_TEST_REG_CNTL_OFFSET                      0x00050708
#define MDDR_TEST_REG_WR_OFFSET                        0x0005070C
#define MDDR_TEST_REG_RD_OFFSET                        0x00050710
#define MDDR_TEST_STATUS_OFFSET                        0x00050714
#define MDDR_TEST_TRIGGER_OFFSET                       0x00050718
#define MDDR_TEST_SWITCH_OFFSET                        0x0005071C
#define MDDR_TEST_INSTRUCTION_0_OFFSET                 0x00050720
#define MDDR_TEST_INSTRUCTION_1_OFFSET                 0x00050724
#define MDDR_TEST_LOAD_CACHE_OFFSET                    0x00050728


#define DDRPLL_ATB_SEL1_OFFSET                         0x00070000
#define DDRPLL_ATB_SEL2_OFFSET                         0x00070004
#define DDRPLL_ATB_SEL3_OFFSET                         0x00070008
#define DDRPLL_FREQ_UPDATE_OFFSET                      0x0007000C
#define DDRPLL_BG_TIMER_OFFSET                         0x00070010
#define DDRPLL_SSC_EN_CENTER_OFFSET                    0x00070014
#define DDRPLL_SSC_ADJ_PER1_OFFSET                     0x00070018
#define DDRPLL_SSC_ADJ_PER2_OFFSET                     0x0007001C
#define DDRPLL_SSC_PER1_OFFSET                         0x00070020
#define DDRPLL_SSC_PER2_OFFSET                         0x00070024
#define DDRPLL_SSC_STEP_SIZE1_OFFSET                   0x00070028
#define DDRPLL_SSC_STEP_SIZE2_OFFSET                   0x0007002C
#define DDRPLL_SSC_STEP_SIZE3_OFFSET                   0x00070030
#define DDRPLL_SSC_STEP_SIZE1_MODE1_OFFSET             0x00070034
#define DDRPLL_SSC_STEP_SIZE2_MODE1_OFFSET             0x00070038
#define DDRPLL_SSC_STEP_SIZE3_MODE1_OFFSET             0x0007003C
#define DDRPLL_SSC_STEP_SIZE1_MODE2_OFFSET             0x00070040
#define DDRPLL_SSC_STEP_SIZE2_MODE2_OFFSET             0x00070044
#define DDRPLL_SSC_STEP_SIZE3_MODE2_OFFSET             0x00070048
#define DDRPLL_POST_DIV_OFFSET                         0x0007004C
#define DDRPLL_POST_DIV_MUX_OFFSET                     0x00070050
#define DDRPLL_BIAS_EN_CLKBUFLR_EN_OFFSET              0x00070054
#define DDRPLL_CLK_ENABLE1_OFFSET                      0x00070058
#define DDRPLL_SYS_CLK_CTRL_OFFSET                     0x0007005C
#define DDRPLL_SYSCLK_BUF_ENABLE_OFFSET                0x00070060
#define DDRPLL_PLL_EN_OFFSET                           0x00070064
#define DDRPLL_PLL_IVCO_OFFSET                         0x00070068
#define DDRPLL_LOCK_CMP1_MODE0_OFFSET                  0x0007006C
#define DDRPLL_LOCK_CMP2_MODE0_OFFSET                  0x00070070
#define DDRPLL_LOCK_CMP3_MODE0_OFFSET                  0x00070074
#define DDRPLL_LOCK_CMP1_MODE1_OFFSET                  0x00070078
#define DDRPLL_LOCK_CMP2_MODE1_OFFSET                  0x0007007C
#define DDRPLL_LOCK_CMP3_MODE1_OFFSET                  0x00070080
#define DDRPLL_LOCK_CMP1_MODE2_OFFSET                  0x00070084
#define DDRPLL_LOCK_CMP2_MODE2_OFFSET                  0x00070088
#define DDRPLL_LOCK_CMP3_MODE2_OFFSET                  0x0007008C
#define DDRPLL_EP_CLOCK_DETECT_CTRL_OFFSET             0x00070090
#define DDRPLL_SYSCLK_DET_COMP_STATUS_OFFSET           0x00070094
#define DDRPLL_BGV_TRIM_OFFSET                         0x00070098
#define DDRPLL_BGT_TRIM_OFFSET                         0x0007009C
#define DDRPLL_CLK_IETRIM_OFFSET                       0x000700A0
#define DDRPLL_CLK_IPTRIM_OFFSET                       0x000700A4
#define DDRPLL_CLK_EP_DIV_OFFSET                       0x000700A8
#define DDRPLL_CP_CTRL_MODE0_OFFSET                    0x000700AC
#define DDRPLL_CP_CTRL_MODE1_OFFSET                    0x000700B0
#define DDRPLL_CP_CTRL_MODE2_OFFSET                    0x000700B4
#define DDRPLL_PLL_RCTRL_MODE0_OFFSET                  0x000700B8
#define DDRPLL_PLL_RCTRL_MODE1_OFFSET                  0x000700BC
#define DDRPLL_PLL_RCTRL_MODE2_OFFSET                  0x000700C0
#define DDRPLL_PLL_CCTRL_MODE0_OFFSET                  0x000700C4
#define DDRPLL_PLL_CCTRL_MODE1_OFFSET                  0x000700C8
#define DDRPLL_PLL_CCTRL_MODE2_OFFSET                  0x000700CC
#define DDRPLL_PLL_CNTRL_OFFSET                        0x000700D0
#define DDRPLL_SYSCLK_EN_SEL_OFFSET                    0x000700D4
#define DDRPLL_CML_SYSCLK_SEL_OFFSET                   0x000700D8
#define DDRPLL_RESETSM_CNTRL_OFFSET                    0x000700DC
#define DDRPLL_RESETSM_CNTRL2_OFFSET                   0x000700E0
#define DDRPLL_RESTRIM_CTRL_OFFSET                     0x000700E4
#define DDRPLL_RESTRIM_CTRL2_OFFSET                    0x000700E8
#define DDRPLL_RESCODE_DIV_NUM_OFFSET                  0x000700EC
#define DDRPLL_LOCK_CMP_EN_OFFSET                      0x000700F0
#define DDRPLL_LOCK_CMP_CFG_OFFSET                     0x000700F4
#define DDRPLL_DEC_START_MODE0_OFFSET                  0x000700F8
#define DDRPLL_DEC_START_MSB_MODE0_OFFSET              0x000700FC
#define DDRPLL_DEC_START_MODE1_OFFSET                  0x00070100
#define DDRPLL_DEC_START_MSB_MODE1_OFFSET              0x00070104
#define DDRPLL_DEC_START_MODE2_OFFSET                  0x00070108
#define DDRPLL_DEC_START_MSB_MODE2_OFFSET              0x0007010C
#define DDRPLL_VCOCAL_DEADMAN_CTRL_OFFSET              0x00070110
#define DDRPLL_DIV_FRAC_START1_MODE0_OFFSET            0x00070114
#define DDRPLL_DIV_FRAC_START2_MODE0_OFFSET            0x00070118
#define DDRPLL_DIV_FRAC_START3_MODE0_OFFSET            0x0007011C
#define DDRPLL_DIV_FRAC_START1_MODE1_OFFSET            0x00070120
#define DDRPLL_DIV_FRAC_START2_MODE1_OFFSET            0x00070124
#define DDRPLL_DIV_FRAC_START3_MODE1_OFFSET            0x00070128
#define DDRPLL_DIV_FRAC_START1_MODE2_OFFSET            0x0007012C
#define DDRPLL_DIV_FRAC_START2_MODE2_OFFSET            0x00070130
#define DDRPLL_DIV_FRAC_START3_MODE2_OFFSET            0x00070134
#define DDRPLL_VCO_TUNE_MINVAL1_OFFSET                 0x00070138
#define DDRPLL_VCO_TUNE_MINVAL2_OFFSET                 0x0007013C
#define DDRPLL_INTEGLOOP_INITVAL_OFFSET                0x00070140
#define DDRPLL_INTEGLOOP_EN_OFFSET                     0x00070144
#define DDRPLL_INTEGLOOP_GAIN0_MODE0_OFFSET            0x00070148
#define DDRPLL_INTEGLOOP_GAIN1_MODE0_OFFSET            0x0007014C
#define DDRPLL_INTEGLOOP_GAIN0_MODE1_OFFSET            0x00070150
#define DDRPLL_INTEGLOOP_GAIN1_MODE1_OFFSET            0x00070154
#define DDRPLL_INTEGLOOP_GAIN0_MODE2_OFFSET            0x00070158
#define DDRPLL_INTEGLOOP_GAIN1_MODE2_OFFSET            0x0007015C
#define DDRPLL_VCO_TUNE_MAXVAL1_OFFSET                 0x00070160
#define DDRPLL_VCO_TUNE_MAXVAL2_OFFSET                 0x00070164
#define DDRPLL_RES_TRIM_CONTROL2_OFFSET                0x00070168
#define DDRPLL_VCO_TUNE_CTRL_OFFSET                    0x0007016C
#define DDRPLL_VCO_TUNE_MAP_OFFSET                     0x00070170
#define DDRPLL_VCO_TUNE1_MODE0_OFFSET                  0x00070174
#define DDRPLL_VCO_TUNE2_MODE0_OFFSET                  0x00070178
#define DDRPLL_VCO_TUNE1_MODE1_OFFSET                  0x0007017C
#define DDRPLL_VCO_TUNE2_MODE1_OFFSET                  0x00070180
#define DDRPLL_VCO_TUNE1_MODE2_OFFSET                  0x00070184
#define DDRPLL_VCO_TUNE2_MODE2_OFFSET                  0x00070188
#define DDRPLL_VCO_TUNE_INITVAL1_OFFSET                0x0007018C
#define DDRPLL_VCO_TUNE_INITVAL2_OFFSET                0x00070190
#define DDRPLL_VCO_TUNE_TIMER1_OFFSET                  0x00070194
#define DDRPLL_VCO_TUNE_TIMER2_OFFSET                  0x00070198
#define DDRPLL_ADC_FILTER_CTRL_OFFSET                  0x0007019C
#define DDRPLL_ADC_CLK_DIV_OFFSET                      0x000701A0
#define DDRPLL_ADC_CODE_OUT1_STATUS_OFFSET             0x000701A4
#define DDRPLL_ADC_CODE_OUT2_STATUS_OFFSET             0x000701A8
#define DDRPLL_CMN_STATUS_OFFSET                       0x000701AC
#define DDRPLL_RESET_SM_STATUS_OFFSET                  0x000701B0
#define DDRPLL_RESTRIM_CODE_STATUS_OFFSET              0x000701B4
#define DDRPLL_PLLCAL_CODE1_STATUS_OFFSET              0x000701B8
#define DDRPLL_PLLCAL_CODE2_STATUS_OFFSET              0x000701BC
#define DDRPLL_BG_CTRL_OFFSET                          0x000701C0
#define DDRPLL_CLK_SELECT_OFFSET                       0x000701C4
#define DDRPLL_HSCLK_SEL1_OFFSET                       0x000701C8
#define DDRPLL_HSCLK_SEL2_OFFSET                       0x000701CC
#define DDRPLL_INTEGLOOP_BINCODE_STATUS_OFFSET         0x000701D0
#define DDRPLL_PLL_ANALOG_OFFSET                       0x000701D4
#define DDRPLL_CORECLK_DIV_OFFSET                      0x000701D8
#define DDRPLL_SW_RESET_OFFSET                         0x000701DC
#define DDRPLL_CORE_CLK_EN_OFFSET                      0x000701E0
#define DDRPLL_C_READY_STATUS_OFFSET                   0x000701E4
#define DDRPLL_CMN_CONFIG_OFFSET                       0x000701E8
#define DDRPLL_CMN_CONFIG_2_OFFSET                     0x000701EC
#define DDRPLL_CMN_RATE_OVERRIDE_OFFSET                0x000701F0
#define DDRPLL_SVS_MODE_CLK_SEL_OFFSET                 0x000701F4
#define DDRPLL_DEBUG_BUS0_OFFSET                       0x000701F8
#define DDRPLL_DEBUG_BUS1_OFFSET                       0x000701FC
#define DDRPLL_DEBUG_BUS2_OFFSET                       0x00070200
#define DDRPLL_DEBUG_BUS3_OFFSET                       0x00070204
#define DDRPLL_DEBUG_BUS_SEL_OFFSET                    0x00070208
#define DDRPLL_CMN_MISC1_OFFSET                        0x0007020C
#define DDRPLL_CMN_MISC2_OFFSET                        0x00070210
#define DDRPLL_CORECLK_DIV_MODE1_OFFSET                0x00070214
#define DDRPLL_CORECLK_DIV_MODE2_OFFSET                0x00070218
#define DDRPLL_CMN_MODE_OFFSET                         0x0007021C
#define DDRPLL_VREGCLK_DIV1_OFFSET                     0x00070220
#define DDRPLL_VREGCLK_DIV2_OFFSET                     0x00070224
#define DDRPLL_VCO_CAL_CODE1_MODE0_STATUS_OFFSET       0x00070228
#define DDRPLL_VCO_CAL_CODE2_MODE0_STATUS_OFFSET       0x0007022C
#define DDRPLL_VCO_CAL_CODE1_MODE1_STATUS_OFFSET       0x00070230
#define DDRPLL_VCO_CAL_CODE2_MODE1_STATUS_OFFSET       0x00070234
#define DDRPLL_VCO_CAL_CODE1_MODE2_STATUS_OFFSET       0x00070238
#define DDRPLL_VCO_CAL_CODE2_MODE2_STATUS_OFFSET       0x0007023C


#define DIMM_TECH_DEVICE_DDR3                         0x0
#define DIMM_TECH_DEVICE_DDR4                         0x1
#define DIMM_TECH_DRAM_WIDTH___S                      0x8
#define DIMM_TECH_DRAM_WIDTH_X4                       0x0
#define DIMM_TECH_DRAM_WIDTH_X8_X16                   0x1
#define DIMM_TECH_DIMM_TYPE___S                       0x4
#define DIMM_TECH_DIMM_TYPE_UDIMM                     0x1
#define DIMM_TECH_DIMM_TYPE_RDIMM                     0x2
#define DIMM_TECH_DIMM_TYPE_LRDIMM                    0x3
#define DIMM_TECH_NUM_DIMM_SLOTS___S                  0x10
#define DIMM_TECH_NUM_DIMM_SLOTS_2                    0x1
#define DIMM_TECH_SHARED_DIMM_CLK___S                 0xC
#define DIMM_TECH_SHARED_DIMM_CLK_YES                 0x1


#define SLOT_CONFIG_SLOT_READY___S                    28
#define SLOT_CONFIG_SLOT_EN___S                       27
#define SLOT_CONFIG_CA_MIRROR___S                     26
#define SLOT_CONFIG_3DS___S                           24
#define SLOT_CONFIG_NUM_CLK___S                       20
#define SLOT_CONFIG_NUM_CS___S                        16
#define SLOT_CONFIG_SUB_RANKS___S                     12
#define SLOT_CONFIG_ROW___S                           8
#define SLOT_CONFIG_ROWS_SCALE_OFFSET                 0xC
#define SLOT_CONFIG_COL___S                           4
#define SLOT_CONFIG_BANK_GROUP_BITS_2                 0x1
#define SLOT_CONFIG_SUB_RANKS_8                       0x3
#define SLOT_CONFIG_SUB_RANKS_4                       0x2
#define SLOT_CONFIG_SUB_RANKS_2                       0x1
#define SLOT_CONFIG_NUM_CS_4                          0x2
#define SLOT_CONFIG_NUM_CS_2                          0x1
#define SLOT_CONFIG_NUM_CS_1                          0x0
#define SLOT_CONFIG_COL_10                            0x0
#define SLOT_CONFIG_COL_11                            0x1
#define SLOT_CONFIG_COL_12                            0x3


#define SLOT_ADDR_CAPACITY___M                        0x0000001F
#define SLOT_ADDR_CAPACITY___S                        16
#define SLOT_ADDR_BASE_ADDR___M                       0x0000FFFF
#define SLOT_ADDR_BASE_ADDR___S                       0


#define CMD_WDB_ACCESS_WRITE_N_READ_WDB___M           0x1
#define CMD_WDB_ACCESS_WRITE_N_READ_WDB___S           16
#define CMD_WDB_ACCESS_WDB_DATA_NDX___M               0x3F
#define CMD_WDB_ACCESS_WDB_DATA_NDX___S               8
#define CMD_WDB_ACCESS_WDB_SEG_NDX___M                0x3
#define CMD_WDB_ACCESS_WDB_SEG_NDX___S                0
#define CMD_WDB_ACCESS_WRITE_WDB                      0x1


#define DATAFLOW_CNTL_EN_SCRAMBLING___S               5
#define DATAFLOW_CNTL_EN_DBI___S                      2
#define DATAFLOW_CNTL_EN_ECC                          0x3
#define DATAFLOW_CNTL_DISABLE_ECC___M                 0xFFFFFFFC

#define DATAFLOW_CNTL_DBI_OFF                         0x0
#define DATAFLOW_CNTL_DBI_RD                          0x1
#define DATAFLOW_CNTL_DBI_WR                          0x2
#define DATAFLOW_CNTL_DBI_RW                          (DATAFLOW_CNTL_DBI_RD | DATAFLOW_CNTL_DBI_WR)


#define DATAFLOW_CDE_CNTL___M                         0x1

#define DATAFLOW_CDE_CNTL_0_EN_RS_WR___S              0
#define DATAFLOW_CDE_CNTL_0_EN_RS_RD___S              1
#define DATAFLOW_CDE_CNTL_0_EN_COMP___S               2
#define DATAFLOW_CDE_CNTL_0_EN_COMP___M               0x01
#define DATAFLOW_CDE_CNTL_0_EN_DECOMP___S             3
#define DATAFLOW_CDE_CNTL_0_EN_DECOMP___M             0x02
#define DATAFLOW_CDE_CNTL_0_INIT_WR_ALL___S           4
#define DATAFLOW_CDE_CNTL_0_SCRUB_ALL___S             5
#define DATAFLOW_CDE_CNTL_0_DBL_QUAD_DET___S          8
#define DATAFLOW_CDE_CNTL_0_DECOMP_FN_DIS___S         12
#define DATAFLOW_CDE_CNTL_0_DIS_NWDB_ENTRY___S        16
#define DATAFLOW_CDE_CNTL_0_DIS_NWDB_ENTRY___M        0xFF
#define DATAFLOW_CDE_CNTL_0_DIS_RX_CLEAN___S          24
#define DATAFLOW_CDE_CNTL_0_TX_CLEAN___S              25
#define DATAFLOW_CDE_CNTL_0_SNP_RSLT_CLEAN___S        26


#define DATAFLOW_CDE_CNTL_1_BUMP_PRIO_WR___S          0
#define DATAFLOW_CDE_CNTL_1_BUMP_PRIO_WR___M          0x3
#define DATAFLOW_CDE_CNTL_1_BUMP_PRIO_RD___S          4
#define DATAFLOW_CDE_CNTL_1_BUMP_PRIO_RD___M          0x3
#define DATAFLOW_CDE_CNTL_1_COMP_WR_IMPACT_PCHG___S   8
#define DATAFLOW_CDE_CNTL_1_COMP_WR_IMPACT_ACT___S    9


#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD___S         24
#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD___M         0xFF
#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_RD___S      16
#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_RD___M      0xFF
#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_WR___S      8
#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_WR___M      0xFF
#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_EN___S      6
#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_RD_EN___S   5
#define DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_WR_EN___S   4
#define DATAFLOW_CDE_CNTL_2_RD_CYCLE_EN___S           2
#define DATAFLOW_CDE_CNTL_2_WR_CYCLE_EN___S           1
#define DATAFLOW_CDE_CNTL_2_OH_CYCLE_EN___S           0


#define DATAFLOW_CDE_CNTL_3_BUSY_HI_THRESHOLD___S     16
#define DATAFLOW_CDE_CNTL_3_BUSY_HI_THRESHOLD___M     0xFFFF
#define DATAFLOW_CDE_CNTL_3_BUSY_LO_THRESHOLD___S     0
#define DATAFLOW_CDE_CNTL_3_BUSY_LO_THRESHOLD___M     0xFFFF


#define MAX_BUSY_HIST_SIZE                            0x8
#define DATAFLOW_CDE_CNTL_4_BUSY_WINDOW_SIZE___S      16
#define DATAFLOW_CDE_CNTL_4_BUSY_WINDOW_SIZE___M      0xFFFF
#define DATAFLOW_CDE_CNTL_4_BUSY_HIST_THRESHOLD___S   12
#define DATAFLOW_CDE_CNTL_4_BUSY_HIST_THRESHOLD___M   0xF
#define DATAFLOW_CDE_CNTL_4_BUSY_HIST_SIZE___S        8
#define DATAFLOW_CDE_CNTL_4_BUSY_HIST_SIZE___M        0xF
#define DATAFLOW_CDE_CNTL_4_NOT_BUSY_EN___S           1
#define DATAFLOW_CDE_CNTL_4_NOT_BUSY_SEL___S          0


#define DATAFLOW_CDE_CNTL_5_COMPRD_HI_THRESHOLD___S   16
#define DATAFLOW_CDE_CNTL_5_COMPRD_HI_THRESHOLD___M   0xFFFF
#define DATAFLOW_CDE_CNTL_5_COMPRD_LO_THRESHOLD___S   0
#define DATAFLOW_CDE_CNTL_5_COMPRD_LO_THRESHOLD___M   0xFFFF


#define DATAFLOW_CDE_CNTL_6_RD_WINDOW_SIZE___S        16
#define DATAFLOW_CDE_CNTL_6_RD_WINDOW_SIZE___M        0xFFFF
#define DATAFLOW_CDE_CNTL_6_RD_HIST_THRESHOLD___S     12
#define DATAFLOW_CDE_CNTL_6_RD_HIST_THRESHOLD___M     0xF
#define DATAFLOW_CDE_CNTL_6_RD_HIST_SIZE___S          8
#define DATAFLOW_CDE_CNTL_6_RD_HIST_SIZE___M          0xF
#define DATAFLOW_CDE_CNTL_6_WDB_RD_MODE___S           4
#define DATAFLOW_CDE_CNTL_6_WDB_RD_MODE___M           0xF
#define DATAFLOW_CDE_CNTL_6_QSB_RD_MODE___S           0
#define DATAFLOW_CDE_CNTL_6_QSB_RD_MODE___M           0xF


#define FUSE_COMPRESSION_DISABLE___M                  0x4
#define FUSE_COMPRESSION_DISABLE___S                  2


#define EN_ODT_WR_CS_7___S                            28
#define EN_ODT_WR_CS_6___S                            24
#define EN_ODT_WR_CS_5___S                            20
#define EN_ODT_WR_CS_4___S                            16
#define EN_ODT_WR_CS_3___S                            12
#define EN_ODT_WR_CS_2___S                            8
#define EN_ODT_WR_CS_1___S                            4
#define EN_ODT_WR_CS_0___S                            0
#define EN_ODT_WR_CS___M                              0xF
#define EN_ODT_WR_CS_WIDTH                            0x4 // Width of a single write ODT field in bits


#define EN_ODT_RD_CS_7___S                            28
#define EN_ODT_RD_CS_6___S                            24
#define EN_ODT_RD_CS_5___S                            20
#define EN_ODT_RD_CS_4___S                            16
#define EN_ODT_RD_CS_3___S                            12
#define EN_ODT_RD_CS_2___S                            8
#define EN_ODT_RD_CS_1___S                            4
#define EN_ODT_RD_CS_0___S                            0
#define EN_ODT_RD_CS___M                              0xF
#define EN_ODT_RD_CS_WIDTH                            0x4 // Width of a single read ODT field in bits


#define CMD_EXEC_CNTL0_EN_CLK_ON___S                    20
#define CMD_EXEC_CNTL0_NO_RETRY_MODE_IGN_PORTMREL___S   16
#define CMD_EXEC_CNTL0_RETRY_WRWR_HAZ___S               14
#define CMD_EXEC_CNTL0_RETRY_ORWRORWR_HAZ___S           13
#define CMD_EXEC_CNTL0_EN_NO_RETRY___S                  12
#define CMD_EXEC_CNTL0_EN_RMW___S                       8
#define CMD_EXEC_CNTL0_DIS_WDB_SOURCE_RD___S            4
#define DIS_WDB_READ                                    0  // should be 0 long term but 1 for bring-ups
#define EN_NO_RETRY                                     1
#define RETRY_WRWR_HAZ                                  0
#define RETRY_ORWRORWR_HAZ                              1
#define NO_RETRY_MODE_IGN_POR_TMREL                     0
#define EN_CLK_ON                                       0


#define CMD_EXEC_CNTL1_BCQ_TH___S                     24
#define CMD_EXEC_CNTL1_BCQ_TH___M                     0xFF
#define CMD_EXEC_CNTL1_BCQ_TH_WR___S                  16
#define CMD_EXEC_CNTL1_BCQ_TH_WR___M                  0xFF
#define CMD_EXEC_CNTL1_RCQ_TH___S                     8
#define CMD_EXEC_CNTL1_RCQ_TH___M                     0xFF
#define CMD_EXEC_CNTL1_CBQ_TH___S                     0
#define CMD_EXEC_CNTL1_CBQ_TH___M                     0xFF
#define BCQ_TH                                        0xC
#define BCQ_TH_WR                                     0xC
#define RCQ_TH                                        0x8            // short=3
#define CBQ_TH                                        0x10


#define CMD_EXEC_CNTL2_DIS_RCQ___S                    24
#define CMD_EXEC_CNTL2_DIS_RCQ___M                    0xFF
#define CMD_EXEC_CNTL2_DIS_WDB___S                    16
#define CMD_EXEC_CNTL2_DIS_WDB___M                    0xFF
#define CMD_EXEC_CNTL2_DIS_RD_RESP_FIFO___S           8
#define CMD_EXEC_CNTL2_DIS_RD_RESP_FIFO___M           0xFF
#define CMD_EXEC_CNTL2_DIS_RD_DATA_FIFO___S           0
#define CMD_EXEC_CNTL2_DIS_RD_DATA_FIFO___M           0xFF
#define DIS_RCQ                                       0x0
#define DIS_WDB                                       0x0
#define DIS_RD_RESP_FIFO                              0x1
#define DIS_RD_DATA_FIFO                              0x0


#define CMD_EXEC_CNTL3_EN_AUTO_PCHG___M               0x1
#define CMD_EXEC_CNTL3_EN_AUTO_PCHG___S               28
#define CMD_EXEC_CNTL3_DQ_BURST_LEN___M               0x1
#define CMD_EXEC_CNTL3_DQ_BURST_LEN___S               24
#define CMD_EXEC_CNTL3_DIS_OPT_ENTRY___M              0xF
#define CMD_EXEC_CNTL3_DIS_OPT_ENTRY___S              20
#define CMD_EXEC_CNTL3_PAGE_POLICY___M                0x3
#define CMD_EXEC_CNTL3_PAGE_POLICY___S                16
#define CMD_EXEC_CNTL3_PAGE_IDLE_TIMER___M            0xFFFF
#define CMD_EXEC_CNTL3_PAGE_IDLE_TIMER___S            0
#define DISABLE_AUTO_PCHG                             0
#define ENABLE_AUTO_PCHG                              1
#define BURST_LEN_BL8                                 0x0    // BL8 - Burst Length 8
#define BURST_LEN_OTF                                 0x1    // OTF - On The Fly : BL8 & BC4
#define DIS_OPT_ENTRY                                 0      // All entries are used
#define PAGE_POLICY_CLOSED                            0
#define PAGE_POLICY_OPEN                              1
#define PAGE_POLICY_TIMER                             2


#define CMD_EXEC_CNTL4_DISABLE_CMD_INTERLEAVE___S     28
#define CMD_EXEC_CNTL4_SERIAL_MNT_CMD___S             18
#define DISABLE_CMD_INTERLEAVE                        1


#define CMD_EXEC_CNTL5_PRIO_ELEVATION_TH___M          0xFFF
#define PRIO_ELEVATION_TH                             0x400 // was 0x144


#define CMD_EXEC_CNTL6_WR_PREFER_EN___S               31
#define CMD_EXEC_CNTL6_BCQ_ALL___S                    30
#define CMD_EXEC_CNTL6_BCQ_WM_EN___S                  29
#define CMD_EXEC_CNTL6_BCQ_DBE_BOTH___S               28
#define CMD_EXEC_CNTL6_DBE_WM_EN___S                  27
#define CMD_EXEC_CNTL6_BCQ_WM_HI___M                  0xF
#define CMD_EXEC_CNTL6_BCQ_WM_HI___S                  8
#define CMD_EXEC_CNTL6_DBE_WM_HI___M                  0x3F
#define CMD_EXEC_CNTL6_DBE_WM_HI___S                  0
#define WR_PREFER_EN                                  0x1    // enable wr preference; 0=disable, 1=enable
#define BCQ_ALL_HI                                    0x0
#define BCQ_WM_EN_HI                                  0x0
#define BCQ_DBE_BOTH_HI                               0x0
#define DBE_WM_EN_HI                                  0x1
#define BCQ_WM_HI                                     0x0
#define DBE_WM_HI                                     0x14


#define CMD_EXEC_CNTL7_BCQ_ALL___S                    30
#define CMD_EXEC_CNTL7_BCQ_WM_EN___S                  29
#define CMD_EXEC_CNTL7_BCQ_DBE_BOTH___S               28
#define CMD_EXEC_CNTL7_DBE_WM_EN___S                  27
#define CMD_EXEC_CNTL7_BCQ_WM_LO___M                  0xF
#define CMD_EXEC_CNTL7_BCQ_WM_LO___S                  8
#define CMD_EXEC_CNTL7_DBE_WM_LO___M                  0x3F
#define CMD_EXEC_CNTL7_DBE_WM_LO___S                  0
#define BCQ_ALL_LO                                    0x0
#define BCQ_WM_EN_LO                                  0x0
#define BCQ_DBE_BOTH_LO                               0x0
#define DBE_WM_EN_LO                                  0x1
#define BCQ_WM_LO                                     0x0
#define DBE_WM_LO                                     0x4


#define CMD_STATUS_COMPLETE___S                       3
#define CMD_STATUS_COMPLETE___M                       0x1
#define CMD_STATUS_TIMEOUT___S                        2
#define CMD_STATUS_TIMEOUT___M                        0x1
#define CMD_STATUS_REJECTED___S                       1
#define CMD_STATUS_REJECTED___M                       0x1
#define CMD_STATUS_EXPIRED___S                        0
#define CMD_STATUS_EXPIRED___M                        0x1


#define ADDR_DECODE_CNTL_EN_INT_DIMM___S              16
#define ADDR_DECODE_CNTL_ADDR_INT_MODE___S            12
#define ADDR_DECODE_CNTL_ADDR_INT_BNDRY___S           8
#define ADDR_DECODE_CNTL_BG_DECODE___M                0x3
#define ADDR_DECODE_CNTL_ADDR_INTLV_MODE_DIV_1        0x0
#define ADDR_DECODE_CNTL_ADDR_INTLV_MODE_DIV_2        0x1
#define ADDR_DECODE_CNTL_ADDR_INTLV_MODE_DIV_3        0x2
#define ADDR_DECODE_CNTL_ADDR_INTLV_BNDRY_256B        0x0 // MC_PAIR_256B_INTERLEAVE_BOUNDARY
#define ADDR_DECODE_CNTL_ADDR_INTLV_BNDRY_4KB         0x1 // MC_PAIR_4KB_INTERLEAVE_BOUNDARY
#define ADDR_DECODE_CNTL_ADDR_INTLV_BNDRY_8KB         0x2 // MC_PAIR_8KB_INTERLEAVE_BOUNDARY
#define ADDR_DECODE_CNTL_BG_DECODE_MCA_16_15          0x0 // BG[1:0] are at MCA[16:15]
#define ADDR_DECODE_CNTL_BG_DECODE_MCA_8_7            0x1 // BG[1:0] move to MCA[8:7]
#define ADDR_DECODE_CNTL_BG_DECODE_MCA_16_7           0x2 // BG[1:0] move to MCA[16],MCA[7]
#define ADDR_DECODE_CNTL_BG_DECODE_R_C_RK_B_BG        0x3 // Row, Column[9:4], Rank, Bank, Bank Group, Column[3:0] order


#define SCRUB_ADDR_WR_0_DSE_ROW___S                   8
#define SCRUB_ADDR_WR_0_DSE_ROW___M                   0x3FFFF
#define SCRUB_ADDR_WR_0_DSE_COLUMN_MSB___S            0
#define SCRUB_ADDR_WR_0_DSE_COLUMN_MSB___M            0xFF


#define SCRUB_ADDR_WR_1_WDB_DATA_NDX___S              24
#define SCRUB_ADDR_WR_1_WDB_DATA_NDX___M              0x3F
#define SCRUB_ADDR_WR_1_DSE_DIMM___S                  20
#define SCRUB_ADDR_WR_1_DSE_DIMM___M                  0x1
#define SCRUB_ADDR_WR_1_DSE_CID___S                   16
#define SCRUB_ADDR_WR_1_DSE_CID___M                   0x7
#define SCRUB_ADDR_WR_1_DSE_RANK___S                  8
#define SCRUB_ADDR_WR_1_DSE_RANK___M                  0x3
#define SCRUB_ADDR_WR_1_DSE_BANK___S                  0
#define SCRUB_ADDR_WR_1_DSE_BANK___M                  0xF


#define SCRUB_CMD_CNTL_RESET_DCF_PTRS___S             24
#define SCRUB_CMD_CNTL_RESET_DCF_PTRS___M             0x1
#define SCRUB_CMD_CNTL_NWDB_NOT_WDB___S               20
#define SCRUB_CMD_CNTL_NWDB_NOT_WDB___M               0x1
#define SCRUB_CMD_CNTL_CMD_TYPE___S                   16
#define SCRUB_CMD_CNTL_CMD_TYPE___M                   0x3
#define SCRUB_CMD_CNTL_START_SEG___S                  8
#define SCRUB_CMD_CNTL_START_SEG___M                  0x3
#define SCRUB_CMD_CNTL_DATA_SEG___S                   0
#define SCRUB_CMD_CNTL_DATA_SEG___M                   0xF
#define SCRUB_CMD_CNTL_RESET_DCF_PTRS_CLR             0x0
#define SCRUB_CMD_CNTL_RESET_DCF_PTRS_RESET           0x1
#define SCRUB_CMD_CNTL_WDB_ENTRY_WRSRC                0x0
#define SCRUB_CMD_CNTL_NWDB_ENTRY_WRSRC               0x1
#define SCRUB_CMD_CNTL_CMD_TYPE_R                     0x0
#define SCRUB_CMD_CNTL_CMD_TYPE_RMW                   0x1
#define SCRUB_CMD_CNTL_CMD_TYPE_W                     0x3
#define SCRUB_CMD_CNTL_START_SEG_FIRST                0x0
#define SCRUB_CMD_CNTL_DATA_SEG_ALL                   0xF
#define SCRUB_CMD_CNTL_DATA_SEG_NONE                  0x0


#define SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN___S         28
#define SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN___M         0x1
#define SCRUB_EXEC_CNTL_CMD_FIFO_EN___S               27
#define SCRUB_EXEC_CNTL_CMD_FIFO_EN___M               0x1
#define SCRUB_EXEC_CNTL_RESP_DIS___S                  26
#define SCRUB_EXEC_CNTL_RESP_DIS___M                  0x1
#define SCRUB_EXEC_CNTL_FIFO_LOOP___S                 25
#define SCRUB_EXEC_CNTL_FIFO_LOOP___M                 0x1
#define SCRUB_EXEC_CNTL_ADDR_MAX_HALT___S             24
#define SCRUB_EXEC_CNTL_ADDR_MAX_HALT___M             0x1
#define SCRUB_EXEC_CNTL_NUM_CMDS___S                  8
#define SCRUB_EXEC_CNTL_NUM_CMDS___M                  0xFF
#define SCRUB_EXEC_CNTL_CMD_TIMER_SEED___S            0
#define SCRUB_EXEC_CNTL_CMD_TIMER_SEED___M            0xFF
#define SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN_YES         0x1
#define SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN_NO          0x0
#define SCRUB_EXEC_CNTL_CMD_FIFO_EN_YES               0x1
#define SCRUB_EXEC_CNTL_CMD_FIFO_EN_NO                0x0
#define SCRUB_EXEC_CNTL_RESP_DIS_YES                  0x1
#define SCRUB_EXEC_CNTL_RESP_DIS_NO                   0x0
#define SCRUB_EXEC_CNTL_FIFO_LOOP_EN                  0x1
#define SCRUB_EXEC_CNTL_FIFO_LOOP_DIS                 0x0
#define SCRUB_EXEC_CNTL_ADDR_MAX_HALT_YES             0x1
#define SCRUB_EXEC_CNTL_ADDR_MAX_HALT_NO              0x0
#define SCRUB_EXEC_CNTL_NUM_CMDS_16                   0x10
#define SCRUB_EXEC_CNTL_NUM_CMDS_8                    0x8
#define SCRUB_EXEC_CNTL_NUM_CMDS_4                    0x4
#define SCRUB_EXEC_CNTL_NUM_CMDS_2                    0x2
#define SCRUB_EXEC_CNTL_NUM_CMDS_1                    0x1
#define SCRUB_EXEC_CNTL_NUM_CMDS_0                    0x0
#define SCRUB_EXEC_CNTL_CMD_TIMER_SEED_CNT            0x1 // need to change later to larger number
#define SCRUB_EXEC_CNTL_CMD_TIMER_SEED_NONE           0x0

#define SCRUB_EXEC_CNTL_TIME_TO_SCRUB_ALLMEM          86400   // This is derived from a fixed time of 24 hours converted to seconds: (24*60*60).
#define SCRUB_EXEC_CNTL_BYTES_PER_CACHELINE           128     // Bytes per cacheline.
#define SCRUB_EXEC_CNTL_DRAM_CLK_CYCLES_MULT_SEED     65536   // 2^16 DRAM clock cycles.
#define SCRUB_EXEC_CNTL_CMD_TIMER_SEED_MAX            0xFF    // Maximum value of command timer seed.


#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_MIS_COUNT___S    20
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_MIS_COUNT___M    0x1
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_OK_COUNT___S     19
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_OK_COUNT___M     0x1
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOM_BITS___S  18
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOM_BITS___M  0x1
#define SCRUB_CMD_SINGLE_READ_RD_LFSR___S             15
#define SCRUB_CMD_SINGLE_READ_RD_LFSR___M             0x1
#define SCRUB_CMD_SINGLE_SEED_RD_LFSR___S             14
#define SCRUB_CMD_SINGLE_SEED_RD_LFSR___M             0x1
#define SCRUB_CMD_SINGLE_SEED_WR_LFSR___S             13
#define SCRUB_CMD_SINGLE_SEED_WR_LFSR___M             0x1
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE___S   12
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE___M   0x1
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_COMPARE_OK___S   11
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_COMPARE_OK___M   0x1
#define SCRUB_CMD_SINGLE_CLR_ADDR_MAX___S             1
#define SCRUB_CMD_SINGLE_CLR_ADDR_MAX___M             0x1
#define SCRUB_CMD_SINGLE_WRITE_ONLY___S               0
#define SCRUB_CMD_SINGLE_WRITE_ONLY___M               0x1

#define SCRUB_CMD_SINGLE_READ_RD_LFSR                 0x0
#define SCRUB_CMD_SINGLE_SEED_RD_LFSR_SET             0x1
#define SCRUB_CMD_SINGLE_SEED_RD_LFSR_IGNR            0x0
#define SCRUB_CMD_SINGLE_SEED_WR_LFSR_SET             0x1
#define SCRUB_CMD_SINGLE_SEED_WR_LFSR_IGNR            0x0
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE_SET   0x1
#define SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE_IGNR  0x0
#define SCRUB_CMD_SINGLE_CLR_ADDR_MAX_SET             0x1
#define SCRUB_CMD_SINGLE_CLR_ADDR_MAX_IGNR            0x0
#define SCRUB_CMD_SINGLE_WRITE_ONLY_EN                0x1
#define SCRUB_CMD_SINGLE_WRITE_ONLY_DIS               0x0

#define SCRUB_STATUS_WDB_CLEAN___M                    0x1
#define SCRUB_STATUS_WDB_CLEAN___S                    16
#define SCRUB_STATUS_ADDR_MAX___M                     0x1
#define SCRUB_STATUS_ADDR_MAX___S                     0
#define SCRUB_STATUS_RD_LFSR_MISCOMPARE___S           12
#define SCRUB_STATUS_RD_LFSR_MISCOMPARE___M           0x1
#define SCRUB_STATUS_WDB_CLEAN_SET                    0x1
#define SCRUB_STATUS_ADDR_MAX_SET                     0x1


#define WDB_FLUSH_CNTL_IDLE_DELAY___M                 0xFFFF
#define WDB_FLUSH_CNTL_IDLE_DELAY___S                 16
#define WDB_FLUSH_CNTL_WR_DELAY___M                   0x7
#define WDB_FLUSH_CNTL_WR_DELAY___S                   12
#define WDB_FLUSH_CNTL_BCQ_DIST___M                   0xF
#define WDB_FLUSH_CNTL_BCQ_DIST___S                   8
#define WDB_FLUSH_CNTL_FL_WM_INC_WR___M               0x1
#define WDB_FLUSH_CNTL_FL_WM_INC_WR___S               7
#define WDB_FLUSH_CNTL_FL_WM_EN___M                   0x1
#define WDB_FLUSH_CNTL_FL_WM_EN___S                   6
#define WDB_FLUSH_CNTL_WR_WM_EN___M                   0x1
#define WDB_FLUSH_CNTL_WR_WM_EN___S                   5
#define WDB_FLUSH_CNTL_PH_OPT_EN___M                  0x1
#define WDB_FLUSH_CNTL_PH_OPT_EN___S                  4
#define WDB_FLUSH_CNTL_ML_SEL___M                     0x1
#define WDB_FLUSH_CNTL_ML_SEL___S                     3
#define WDB_FLUSH_CNTL_RD_FULL___M                    0x1
#define WDB_FLUSH_CNTL_RD_FULL___S                    2
#define WDB_FLUSH_CNTL_INVALIDATE___M                 0x1
#define WDB_FLUSH_CNTL_INVALIDATE___S                 1
#define WDB_FLUSH_CNTL_DISABLE___M                    0x1
#define WDB_FLUSH_CNTL_DISABLE___S                    0x0
#define WDB_FLUSH_CNTL_IDLE_DELAY                     0x100
#define WDB_FLUSH_CNTL_WR_DELAY                       0x0
#define WDB_FLUSH_CNTL_BCQ_DIST                       0xF          // Must be 0xF per HW.
#define WDB_FLUSH_CNTL_FL_WM_INC_WR                   0x0
#define WDB_FLUSH_CNTL_FL_WM_EN                       0x0
#define WDB_FLUSH_CNTL_WR_WM_EN                       0x1
#define WDB_FLUSH_CNTL_PH_OPT_EN                      0x0          // page hit optimization
#define WDB_FLUSH_CNTL_ML_SEL                         0x1
#define WDB_FLUSH_CNTL_RD_FULL                        0x0
#define WDB_FLUSH_CNTL_INVALIDATE                     0x0
#define WDB_FLUSH_CNTL_DISABLE                        0x0



#define WDB_FLUSH_WM_FL_WM_HI___M                     0xFF
#define WDB_FLUSH_WM_FL_WM_HI___S                     24
#define WDB_FLUSH_WM_FL_WM_LO___M                     0xFF
#define WDB_FLUSH_WM_FL_WM_LO___S                     16
#define WDB_FLUSH_WM_WR_WM_HI___M                     0xFF
#define WDB_FLUSH_WM_WR_WM_HI___S                     8
#define WDB_FLUSH_WM_WR_WM_LO___M                     0xFF
#define WDB_FLUSH_WM_WR_WM_LO___S                     0
#define WDB_FLUSH_WM_FL_WM_HI                         0
#define WDB_FLUSH_WM_FL_WM_LO                         0
#define WDB_FLUSH_WM_WR_WM_HI                         0x20
#define WDB_FLUSH_WM_WR_WM_LO                         0x10


#define WDB_FLUSH_PH_HIT_VAL___M                      0xF
#define WDB_FLUSH_PH_HIT_VAL___S                      8
#define WDB_FLUSH_PH_HIT_INC___M                      0xF
#define WDB_FLUSH_PH_HIT_INC___S                      4
#define WDB_FLUSH_PH_CONFLICT_DEC___M                 0xF
#define WDB_FLUSH_PH_CONFLICT_DEC___S                 0
#define WDB_FLUSH_PH_HIT_VAL                          0x0
#define WDB_FLUSH_PH_HIT_INC                          0x0
#define WDB_FLUSH_PH_CONFLICT_DEC                     0x0


#define TIMING_RCD_TSTAB___S                          16
#define TIMING_RCD_TSTAB___M                          0xFFFF
#define TIMING_RCD_TCKEV___S                          4
#define TIMING_RCD_TCKEV___M                          0xF
#define TIMING_RCD_NLADD___S                          0
#define TIMING_RCD_NLADD___M                          0xF


#define RDWR0_RL___S                                  24
#define RDWR0_WL___S                                  16
#define RDWR0_PL___S                                  8
#define RDWR0_TCAL___S                                4
#define RDWR0_TDBI___S                                0


#define RDWR1_TCCDS___S                               20
#define RDWR1_TCCDS___M                               0xF
#define RDWR1_TCCDL___S                               16
#define RDWR1_TCCDL___M                               0xF
#define RDWR1_TFAW___S                                8
#define RDWR1_TFAW___M                                0xFF
#define RDWR1_TFAW_DLR___S                            0
#define RDWR1_TFAW_DLR___M                            0xFF
#define RDWR_1_WR_DQS_PREAMBLE___S                    26
#define RDWR_1_WR_DQS_PREAMBLE___M                    0x3
#define RDWR_1_RD_DQS_PREAMBLE___S                    24
#define RDWR_1_RD_DQS_PREAMBLE___M                    0x3


#define RDWR2_TRASMIN___S                             16
#define RDWR2_TRASMIN___M                             0xFF
#define RDWR2_TRCD___S                                8
#define RDWR2_TRCD___M                                0xFF
#define RDWR2_TRP___S                                 0
#define RDWR2_TRP___M                                 0xFF


#define RDWR3_TRRDS___S                               20
#define RDWR3_TRRDS___M                               0xFF
#define RDWR3_TRRDL___S                               12
#define RDWR3_TRRDL___M                               0xFF
#define RDWR3_TRRD_DLR___S                            8
#define RDWR3_TRRD_DLR___M                            0xF
#define RDWR3_TRTP___S                                0
#define RDWR3_TRTP___M                                0xFF


#define RDWR4_TWR___S                                 16
#define RDWR4_TWR___M                                 0xFF
#define RDWR4_TWTRS___S                               8
#define RDWR4_TWTRS___M                               0xFF
#define RDWR4_TWTRL___S                               0
#define RDWR4_TWTRL___M                               0xFF


#define ADJ_RDWR0_DIMM_WTR___S                        28
#define ADJ_RDWR0_DIMM_WTR___M                        0xF
#define ADJ_RDWR0_DIMM_WTW___S                        24
#define ADJ_RDWR0_DIMM_WTW___M                        0xF
#define ADJ_RDWR0_DIMM_RTW___S                        20
#define ADJ_RDWR0_DIMM_RTW___M                        0xF
#define ADJ_RDWR0_DIMM_RTR___S                        16
#define ADJ_RDWR0_DIMM_RTR___M                        0xF


#define ADJ_RDWR0_CS_WTR___S                          12
#define ADJ_RDWR0_CS_WTR___M                          0xF
#define ADJ_RDWR0_CS_WTW___S                          8
#define ADJ_RDWR0_CS_WTW___M                          0xF
#define ADJ_RDWR0_CS_RTW___S                          4
#define ADJ_RDWR0_CS_RTW___M                          0xF
#define ADJ_RDWR0_CS_RTR___S                          0
#define ADJ_RDWR0_CS_RTR___M                          0xF


#define ADJ_RDWR1_RANK_WTR___S                        28
#define ADJ_RDWR1_RANK_WTR___M                        0xF
#define ADJ_RDWR1_RANK_WTW___S                        24
#define ADJ_RDWR1_RANK_WTW___M                        0xF
#define ADJ_RDWR1_RANK_RTW___S                        20
#define ADJ_RDWR1_RANK_RTW___M                        0xF
#define ADJ_RDWR1_RANK_RTR___S                        16
#define ADJ_RDWR1_RANK_RTR___M                        0xF


#define ADJ_RDWR1_SRANK_WTR___S                       12
#define ADJ_RDWR1_SRANK_WTR___M                       0xF
#define ADJ_RDWR1_SRANK_WTW___S                       8
#define ADJ_RDWR1_SRANK_WTW___M                       0xF
#define ADJ_RDWR1_SRANK_RTW___S                       4
#define ADJ_RDWR1_SRANK_RTW___M                       0xF
#define ADJ_RDWR1_SRANK_RTR___S                       0
#define ADJ_RDWR1_SRANK_RTR___M                       0xF


#define AUTO_REF0_TREFI___S                           12
#define AUTO_REF0_TREFI___M                           0xFFFF
#define AUTO_REF0_TRFC___S                            0
#define AUTO_REF0_TRFC___M                            0xFFF


#define AUTO_REF1_TRFC2___S                           12
#define AUTO_REF1_TRFC2___M                           0xFFF
#define AUTO_REF1_TRFCDLR___S                         0
#define AUTO_REF1_TRFCDLR___M                         0xFFF


#define AUTO_REF2_TRFC4___S                           0
#define AUTO_REF2_TRFC4___M                           0xFFF


#define ADJ_AUTO_REF_SPACE___S                        0
#define ADJ_AUTO_REF_SPACE___M                        0xFF


#define AUTO_REF_CNTL_FINEGRAIN___S                   16
#define AUTO_REF_CNTL_FINEGRAIN___M                   0x3
#define AUTO_REF_CNTL_ADJ_DIMM1___S                   12
#define AUTO_REF_CNTL_ADJ_DIMM1___M                   0x7
#define AUTO_REF_CNTL_ADJ_DIMM0___S                   8
#define AUTO_REF_CNTL_ADJ_DIMM0___M                   0x7
#define AUTO_REF_CNTL_WM_HIGH___S                     4
#define AUTO_REF_CNTL_WM_HIGH___M                     0x7
#define AUTO_REF_CNTL_WM_LOW___S                      0
#define AUTO_REF_CNTL_WM_LOW___M                      0x7


#define PWR_DOWN0_TCPDED___S                          8
#define PWR_DOWN0_TCPDED___M                          0xF
#define PWR_DOWN0_TXP___S                             0
#define PWR_DOWN0_TXP___M                             0xFF


#define PWR_DOWN1_TREFPDEN___S                        28
#define PWR_DOWN1_TREFPDEN___M                        0xF
#define PWR_DOWN1_TPRPDEN___S                         24
#define PWR_DOWN1_TPRPDEN___M                         0xF
#define PWR_DOWN1_TRDPDEN___S                         16
#define PWR_DOWN1_TRDPDEN___M                         0xFF
#define PWR_DOWN1_TWRPDEN___S                         8
#define PWR_DOWN1_TWRPDEN___M                         0xFF
#define PWR_DOWN1_TWRAPDEN___S                        0
#define PWR_DOWN1_TWRAPDEN___M                        0xFF


#define SELF_REF0_TCKE___S                            24
#define SELF_REF0_TCKE___M                            0xFF
#define SELF_REF0_TCKESR___S                          16
#define SELF_REF0_TCKESR___M                          0xFF
#define SELF_REF0_TCKSRE___S                          8
#define SELF_REF0_TCKSRE___M                          0xFF
#define SELF_REF0_TCKSRX___S                          0
#define SELF_REF0_TCKSRX___M                          0xFF


#define SELF_REF1_TXS___S                             12
#define SELF_REF1_TXS___M                             0xFFF
#define SELF_REF1_TXSDLL___S                          0
#define SELF_REF1_TXSDLL___M                          0xFFF


#define SELF_REF2_TXS_ABORT___S                       12
#define SELF_REF2_TXS_ABORT___M                       0xFFF
#define SELF_REF2_TXS_FAST___S                        0
#define SELF_REF2_TXS_FAST___M                        0xFFF


#define MPSM_TXMP_DLL___S                             4
#define MPSM_TXMP_DLL___M                             0x3FF
#define MPSM_TMPX_LH___S                              0
#define MPSM_TMPX_LH___M                              0xF


#define ZQ0_TZQCS___S                                 0
#define ZQ0_TZQCS___M                                 0xFFF


#define ZQ1_TZQINIT___S                               12
#define ZQ1_TZQINIT___M                               0xFFF
#define ZQ1_TZQOPER___S                               0
#define ZQ1_TZQOPER___M                               0xFFF


#define ZQ_ADJ_SPACE___S                              0
#define ZQ_ADJ_SPACE___M                              0xFF


#define ZQCAL_CNTL_ZQ_EXIT_SR___S                     19
#define ZQCAL_CNTL_ZQ_EXIT_SR___M                     0x1
#define ZQCAL_CNTL_DIS_ZQ_ON_SR_EXIT___S              18
#define ZQCAL_CNTL_DIS_ZQ_ON_SR_EXIT___M              0x1
#define ZQCAL_CNTL_ZQ_SEQ_MODE___S                    16
#define ZQCAL_CNTL_ZQ_SEQ_MODE___M                    0x3
#define ZQCAL_CNTL_ZQ_INTERVAL___S                    0
#define ZQCAL_CNTL_ZQ_INTERVAL___M                    0xFFFF


#define MR_0_TMOD___S                                 24
#define MR_0_TMOD___M                                 0xFF
#define MR_0_TMRD___S                                 16
#define MR_0_TMRD___M                                 0xFF
#define MR_0_TMOD_PDA___S                             8
#define MR_0_TMOD_PDA___M                             0xFF
#define MR_0_TMRD_PDA___S                             0
#define MR_0_TMRD_PDA___M                             0xFF


#define MR_1_TMPRR___S                                8
#define MR_1_TMPRR___M                                0xF
#define MR_1_TWR_MPR___S                              0
#define MR_1_TWR_MPR___M                              0xFF


#define DQ_BUS_PROP_DELAY___S                         0
#define DQ_BUS_PROP_DELAY___M                         0xFF


#define EXTRA_DQS_TOGGLE___S                          8
#define EXTRA_DQS_TOGGLE___M                          0x7

#define MANUAL_DISCARD_RD_DATA___S                    24
#define MANUAL_DISCARD_RD_DATA___M                    0x1
#define MANUAL_BCQ_DIS___S                            12
#define MANUAL_BCQ_DIS___M                            0x3
#define MANUAL_RD_LFSR_EN___S                         7
#define MANUAL_RD_LFSR_EN___M                         0x1
#define MANUAL_WR_LFSR_EN___S                         6
#define MANUAL_WR_LFSR_EN___M                         0x1
#define MANUAL_FLUSH_WDB___S                          1
#define MANUAL_FLUSH_WDB___M                          0x1


#define MANUAL_CKE_CKE_SEL___S                        24
#define MANUAL_CKE_CKE_SEL___M                        0xF
#define MANUAL_CKE_CW_WRITE___S                       11
#define MANUAL_CKE_CW_WRITE___M                       0x1
#define MANUAL_CKE_RESET_ON___S                       10
#define MANUAL_CKE_RESET_ON___M                       0x1
#define MANUAL_CKE_RESET_OFF___S                      9
#define MANUAL_CKE_RESET_OFF___M                      0x1
#define MANUAL_CKE_CK_ON___S                          8
#define MANUAL_CKE_CK_ON___M                          0x1
#define MANUAL_CKE_CK_OFF___S                         7
#define MANUAL_CKE_CK_OFF___M                         0x1
#define MANUAL_CKE_CKE_ON___S                         6
#define MANUAL_CKE_CKE_ON___M                         0x1
#define MANUAL_CKE_CKE_OFF___S                        5
#define MANUAL_CKE_CKE_OFF___M                        0x1
#define MANUAL_CKE_ENTER_SELF_REF_ASAP___S            2
#define MANUAL_CKE_ENTER_SELF_REF_ASAP___M            0x1
#define MANUAL_CKE_ENTER_SELF_REF_IDLE___S            1
#define MANUAL_CKE_ENTER_SELF_REF_IDLE___M            0x1
#define MANUAL_CKE_EXIT_SELF_REF___S                  0
#define MANUAL_CKE_EXIT_SELF_REF___M                  0x1


#define DEVICE_STATE_CKE_EXITED_SELF_REF___S          24
#define DEVICE_STATE_CKE_EXITED_SELF_REF___M          0xF
#define DEVICE_STATE_CK_IS_ON___S                     20
#define DEVICE_STATE_CK_IS_ON___M                     0xF
#define DEVICE_STATE_RESET_IS_ON___S                  16
#define DEVICE_STATE_RESET_IS_ON___M                  0xF
#define DEVICE_STATE_CKE_IS_ON___S                    12
#define DEVICE_STATE_CKE_IS_ON___M                    0xF
#define DEVICE_STATE_CKE_IN_SELF_REF___S              8
#define DEVICE_STATE_CKE_IN_SELF_REF___M              0xF
#define DEVICE_STATE_CKE_IN_PWR_DOWN___S              4
#define DEVICE_STATE_CKE_IN_PWR_DOWN___M              0xF
#define DEVICE_STATE_CKE_IN_MPSM___S                  0
#define DEVICE_STATE_CKE_IN_MPSM___M                  0xF


#define MANUAL_OPT1_ADDR___S                          16
#define MANUAL_OPT1_ADDR___M                          0xFF
#define MANUAL_OPT1_DATA___S                          0
#define MANUAL_OPT1_DATA___M                          0xFFFF

#define MANUAL_OPT2_PDA_MODE___S                      20
#define MANUAL_OPT2_PDA_MODE___M                      0x1
#define MANUAL_OPT2_PDA_MASK___S                      0
#define MANUAL_OPT2_PDA_MASK___M                      0x0003FFFF


#define MANUAL_RANK_SET_VREFDQ_PDA___S                9
#define MANUAL_RANK_ZQ_SHORT___S                      6
#define MANUAL_RANK_ZQ_LONG___S                       5
#define MANUAL_RANK_ZQ_INIT___S                       4
#define MANUAL_RANK_MR_WRITE___S                      3
#define MANUAL_RANK_NOP___S                           2
#define MANUAL_RANK_MPR_WRITE___S                     1
#define MANUAL_RANK_MPR_READ___S                      0


#define HW_TIMER_DOMAIN___S                           16
#define HW_TIMER_DOMAIN___M                           0x00000001
#define HW_TIMER_TIME___S                             0
#define HW_TIMER_TIME___M                             0x0000FFFF
#define HW_TIMER_DOMAIN_DDR_CLK                       0x0
#define HW_TIMER_DOMAIN_XO_CLK                        0x1


// Same bits for INT0 & INT1
#define INT_CNTL___M                                  0x1
#define INT_CNTL_PHY_UPD_REQ___S                      21
#define INT_CNTL_ERR_DFI_RDDATA_VALID___S             20
#define INT_CNTL_ECC_UE_CNTR_TOTAL_THRESHOLD___S      19
#define INT_CNTL_ECC_CE_CNTR_TOTAL_THRESHOLD___S      18
#define INT_CNTL_DCF_NEMPTY_END_INTERVAL___S          17
#define INT_CNTL_WDB_UE_READ___S                      16
#define INT_CNTL_ECC_UE_CNTR_THRESHOLD___S            15
#define INT_CNTL_ECC_CE_CNTR_THRESHOLD___S            14
#define INT_CNTL_INVALID_CMD___S                      13
#define INT_CNTL_EVENT___S                            12
#define INT_CNTL_ERR_OUT_ALERT___S                    11
#define INT_CNTL_QSB_ADDR_DECODE_ERR1___S             10
#define INT_CNTL_QSB_ADDR_DECODE_ERR0___S             9
#define INT_CNTL_ECC_POISON_SCRUB___S                 8
#define INT_CNTL_ECC_UE_SCRUB___S                     7
#define INT_CNTL_ECC_CE_SCRUB___S                     6
#define INT_CNTL_ECC_POISON_RMW___S                   5
#define INT_CNTL_ECC_UE_RMW___S                       4
#define INT_CNTL_ECC_CE_RMW___S                       3
#define INT_CNTL_ECC_POISON_QSB_RD___S                2
#define INT_CNTL_ECC_UE_QSB_RD___S                    1
#define INT_CNTL_ECC_CE_QSB_RD___S                    0



#define ERR_CNTL___M                                  0x1
#define ERR_CNTL_PHY_UPD_REQ___S                      21
#define ERR_CNTL_ERR_DFI_RDDATA_VALID___S             20
#define ERR_CNTL_ECC_UE_CNTR_TOTAL_THRESHOLD___S      19
#define ERR_CNTL_ECC_CE_CNTR_TOTAL_THRESHOLD___S      18
#define ERR_CNTL_DCF_NEMPTY_END_INTERVAL___S          17
#define ERR_CNTL_WDB_UE_READ___S                      16
#define ERR_CNTL_ECC_UE_CNTR_THRESHOLD___S            15
#define ERR_CNTL_ECC_CE_CNTR_THRESHOLD___S            14
#define ERR_CNTL_INVALID_CMD___S                      13
#define ERR_CNTL_EVENT___S                            12
#define ERR_CNTL_ERR_OUT_ALERT___S                    11
#define ERR_CNTL_QSB_ADDR_DECODE_ERR1___S             10
#define ERR_CNTL_QSB_ADDR_DECODE_ERR0___S             9
#define ERR_CNTL_ECC_POISON_SCRUB___S                 8
#define ERR_CNTL_ECC_UE_SCRUB___S                     7
#define ERR_CNTL_ECC_CE_SCRUB___S                     6
#define ERR_CNTL_ECC_POISON_RMW___S                   5
#define ERR_CNTL_ECC_UE_RMW___S                       4
#define ERR_CNTL_ECC_CE_RMW___S                       3
#define ERR_CNTL_ECC_POISON_QSB_RD___S                2
#define ERR_CNTL_ECC_UE_QSB_RD___S                    1
#define ERR_CNTL_ECC_CE_QSB_RD___S                    0


#define ERR_CAP_CNTL_CAPTURE_LAST_ERR___S             2
#define ERR_CAP_CNTL_CAPTURE_LAST_ERR___M             0x1
#define ERR_CAP_CNTL_CAPTURE_LAST_ERR_FRZ___S         1
#define ERR_CAP_CNTL_CAPTURE_LAST_ERR_FRZ___M         0x1
#define ERR_CAP_CNTL_ERR_CAPTURED___S                 0
#define ERR_CAP_CNTL_ERR_CAPTURED___M                 0x1


#define ECC_ERR_CNTL_1_UE_CNTR_TOTAL_THRESHOLD___S    16
#define ECC_ERR_CNTL_1_UE_CNTR_TOTAL_THRESHOLD___M    0xFFFF
#define ECC_ERR_CNTL_1_CE_CNTR_TOTAL_THRESHOLD___S    0
#define ECC_ERR_CNTL_1_CE_CNTR_TOTAL_THRESHOLD___M    0xFFFF


#define TN_TOKEN_CNT_RSLT_CH___S                      8
#define TN_TOKEN_CNT_RSLT_CH___M                      0x1F
#define TN_TOKEN_CNT_RDAT_CH___S                      0
#define TN_TOKEN_CNT_RDAT_CH___M                      0x1F


#define RD_WR_PREF_CNTL_PREFTIMER___S                 8
#define RD_WR_PREF_CNTL_PREFTIMER___M                 0xFFF
#define RD_WR_PREF_CNTL_PRIOTHRESHOLD___S             4
#define RD_WR_PREF_CNTL_PRIOTHRESHOLD___M             0x7
#define RD_WR_PREF_CNTL_PREF_LEVEL___S                0
#define RD_WR_PREF_CNTL_PREF_LEVEL___M                0x3
#define RD_WR_PREF_PREFTIMER                          0x0
#define RD_WR_PREF_PRIOTHRESHOLD                      0x0
#define RD_WR_PREF_PREF_LEVEL                         0x2


#define DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE3___S        27
#define DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE3___M        0x1
#define DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE2___S        26
#define DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE2___M        0x1
#define DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE1___S        25
#define DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE1___M        0x1
#define DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE0___S        24
#define DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE0___M        0x1
#define DDR_DFI_CNTL_DFI_LP_WAKEUP_FROM_SR___S        20
#define DDR_DFI_CNTL_DFI_LP_WAKEUP_FROM_SR___M        0xF
#define DDR_DFI_CNTL_DFI_LP_WAKEUP_FROM_PD___S        16
#define DDR_DFI_CNTL_DFI_LP_WAKEUP_FROM_PD___M        0xF
#define DDR_DFI_CNTL_DFI_CTRLUPD_PERIOD___S           8
#define DDR_DFI_CNTL_DFI_CTRLUPD_PERIOD___M           0xFF
#define DDR_DFI_CNTL_DFI_FREQ_RATIO___S               6
#define DDR_DFI_CNTL_DFI_FREQ_RATIO___M               0x3
#define DDR_DFI_CNTL_EN_DFI_FC_REQ_IN_SR___S          5
#define DDR_DFI_CNTL_EN_DFI_FC_REQ_IN_SR___M          0x1
#define DDR_DFI_CNTL_DFI_CTRLUPD_MODE___S             4
#define DDR_DFI_CNTL_DFI_CTRLUPD_MODE___M             0x1
#define DDR_DFI_CNTL_EN_DFI_LP_REQ_IN_SR___S          3
#define DDR_DFI_CNTL_EN_DFI_LP_REQ_IN_SR___M          0x1
#define DDR_DFI_CNTL_EN_DFI_LP_REQ_IN_PD___S          2
#define DDR_DFI_CNTL_EN_DFI_LP_REQ_IN_PD___M          0x1
#define DDR_DFI_CNTL_EN_DFI_CTRLUPD_REQ___S           1
#define DDR_DFI_CNTL_EN_DFI_CTRLUPD_REQ___M           0x1
#define DDR_DFI_CNTL_EN_DFI_PHYUPD_ACK___S            0
#define DDR_DFI_CNTL_EN_DFI_PHYUPD_ACK___M            0x1


#define DFI_CNTL1_FC_ENTRY_IDLE_DELAY___S             0
#define DFI_CNTL1_FC_ENTRY_IDLE_DELAY___M             0xFFFF


#define PHY_CNTL_EN_DFI_CLK_IN_LP2___S                6
#define PHY_CNTL_EN_DFI_CLK_IN_LP2___M                0x1
#define PHY_CNTL_EN_AC_PDD___S                        5
#define PHY_CNTL_EN_AC_PDD___M                        0x1


#define PWR_DOWN_CNTL_PD_ENTRY_IDLE_DELAY___S         4
#define PWR_DOWN_CNTL_PD_ENTRY_IDLE_DELAY___M         0xFFFF
#define PWR_DOWN_CNTL_EN_PD_ACT___S                   0
#define PWR_DOWN_CNTL_EN_PD_ACT___M                   0xF


#define SELF_REF_CNTL_SR_ENTRY_IDLE_DELAY___S         8
#define SELF_REF_CNTL_SR_ENTRY_IDLE_DELAY___M         0xFFFF
#define SELF_REF_CNTL_EN_SR_ABORT___S                 6
#define SELF_REF_CNTL_EN_SR_ABORT___M                 0x1
#define SELF_REF_CNTL_EN_SR_CONCURRENT___S            4
#define SELF_REF_CNTL_EN_SR_CONCURRENT___M            0x3
#define SELF_REF_CNTL_EN_SR_AUTO___S                  0
#define SELF_REF_CNTL_EN_SR_AUTO___M                  0xF


#define EN_OUTPUT_INVERSION___S                       17
#define EN_OUTPUT_INVERSION___M                       0x1
#define INV_CA_PAR___S                                16
#define INV_CA_PAR___M                                0x1
#define EN_CA_PAR___S                                 12
#define EN_CA_PAR___M                                 0x3
#define CK_ALWAYS_ON___S                              8
#define CK_ALWAYS_ON___M                              0x1
#define EN_GEAR_DOWN___S                              4
#define EN_GEAR_DOWN___M                              0x1
#define CA_STRETCH___S                                0
#define CA_STRETCH___M                                0x3


#define WR_MASK_POLARITY___S                          0
#define WR_MASK_POLARITY___M                          0x1


#define TIMING_DFI_0_TPHY_WRDATA___M                  0x7
#define TIMING_DFI_0_TPHY_WRDATA___S                  16
#define TIMING_DFI_0_TRDDATA_EN___S                   8
#define TIMING_DFI_0_TRDDATA_EN___M                   0xFF
#define TIMING_DFI_0_TPHY_WRLAT___S                   0
#define TIMING_DFI_0_TPHY_WRLAT___M                   0xFF


#define TIMING_DFI_1_TLP_RESP___S                     4
#define TIMING_DFI_1_TLP_RESP___M                     0xF
#define TIMING_DFI_1_TCTRLUPD_MAX___S                 0
#define TIMING_DFI_1_TCTRLUPD_MAX___M                 0xF
#define TIMING_DFI_1_TCTRLUPD_MAX_MSB___S             28
#define TIMING_DFI_1_TCTRLUPD_MAX_MSB___M             0x1
#define TIMING_DFI_1_TGEARDOWN_DELAY___S              20
#define TIMING_DFI_1_TGEARDOWN_DELAY___M              0x3F
#define TIMING_DFI_1_TCTRL_DELAY___S                  16
#define TIMING_DFI_1_TCTRL_DELAY___M                  0xF
#define TIMING_DFI_1_TINIT_START___S                  8
#define TIMING_DFI_1_TINIT_START___M                  0xFF


#define TIMING_DFI_2_TPHY_RDCSLAT___S                 8
#define TIMING_DFI_2_TPHY_RDCSLAT___M                 0xFF
#define TIMING_DFI_2_TPHY_WRCSLAT___S                 0
#define TIMING_DFI_2_TPHY_WRCSLAT___M                 0xFF


#define ODT_LATENCY_RD___S                            20
#define ODT_LATENCY_RD___M                            0xF
#define ODTH4_RD___S                                  16
#define ODTH4_RD___M                                  0xF
#define ODTH8_RD___S                                  12
#define ODTH8_RD___M                                  0xF
#define ODT_LATENCY_WR___S                            8
#define ODT_LATENCY_WR___M                            0xF
#define ODTH4_WR___S                                  4
#define ODTH4_WR___M                                  0xF
#define ODTH8_WR___S                                  0
#define ODTH8_WR___M                                  0xF


#define GEAR_DOWN_TGEAR_HOLD___S                      16
#define GEAR_DOWN_TGEAR_HOLD___M                      0x7
#define GEAR_DOWN_TGEAR_SETUP___S                     8
#define GEAR_DOWN_TGEAR_SETUP___M                     0x7
#define GEAR_DOWN_TSYNC_GEAR___S                      0
#define GEAR_DOWN_TSYNC_GEAR___M                      0x3F


#define MR0_FAST_EXIT___S                             12
#define MR0_FAST_EXIT___M                             0x1
#define MR0_WR___S                                    9
#define MR0_WR_DDR3___M                               0x7   // Mask differs between DDR3 and DDR4 spec
#define MR0_WR_DDR4___M                               0x17  // Mask differs between DDR3 and DDR4 spec
#define MR0_DLL_RESET___S                             8
#define MR0_DLL_RESET___M                             0x1
#define MR0_CL_DDR3___S                               2
#define MR0_CL_DDR3___M                               0x1D
#define MR0_CL_DDR4___S                               0
#define MR0_CL_DDR4___M                               0x74
#define MR0_BL___S                                    0
#define MR0_BL___M                                    0x3


#define MR1_TDQS___S                                  11
#define MR1_TDQS___M                                  0x1
#define MR1_RTT_NOM_DDR3___S                          2
#define MR1_RTT_NOM_DDR3___M                          0x91
#define MR1_RTT_NOM_DDR4___S                          8
#define MR1_RTT_NOM_DDR4___M                          0x7
#define MR1_ODIC___S                                  1
#define MR1_ODIC_DDR3___M                             0x1
#define MR1_ODIC_DDR4___M                             0x3
#define MR1_DLL___S                                   0
#define MR1_DLL___M                                   0x1


#define MR2_CWL___S                                   3
#define MR2_CWL___M                                   0x7
#define MR2_RTT_WR___S                                9
#define MR2_RTT_WR___M                                0x3
#define MR2_WR_CRC___S                                12


#define MR3_FINE_GRAN___S                             6
#define MR3_FINE_GRAN___M                             0x7
#define MR3_WR_CMD_LAT___M                            0x3
#define MR3_WR_CMD_LAT___S                            9


#define MR4_SR_ABORT___S                              9
#define MR4_TEMP_REF___S                              3
#define MR4_RD_PRE___S                                11
#define MR4_WR_PRE___S                                12
#define MR4_CAL___S                                   6
#define MR4_CAL___M                                   0x7


#define MR5_RTT_PARK___S                              6
#define MR5_RD_DBI___S                                12
#define MR5_WR_DBI___S                                11
#define MR5_DM___S                                    10
#define MR5_CA_PL___M                                 0x7


#define MR6_TCCDL___S                                 10
#define MR6_TCCDL___M                                 0x7
#define MR6_RANGE___S                                 6
#define MR6_RANGE___M                                 0x1
#define MR6_VALUE___S                                 0
#define MR6_VALUE___M                                 0x3F
#define MR6_VALUE_MAX                                 0x32



#define MDDR_SLOT0_RANK_MASK                          0x0F
#define MDDR_SLOT1_RANK_MASK                          0xF0


#define THERMAL_CNTL_0_WEIGHT_READ_BL8___S            24
#define THERMAL_CNTL_0_WEIGHT_READ_BL8___M            0xF
#define THERMAL_CNTL_0_WEIGHT_READ_BC4___S            20
#define THERMAL_CNTL_0_WEIGHT_READ_BC4___M            0xF
#define THERMAL_CNTL_0_WEIGHT_WRITE_BL8___S           16
#define THERMAL_CNTL_0_WEIGHT_WRITE_BL8___M           0xF
#define THERMAL_CNTL_0_WEIGHT_WRITE_BC4___S           12
#define THERMAL_CNTL_0_WEIGHT_WRITE_BC4___M           0xF
#define THERMAL_CNTL_0_WEIGHT_PCHG___S                8
#define THERMAL_CNTL_0_WEIGHT_PCHG___M                0xF
#define THERMAL_CNTL_0_WEIGHT_ACT___S                 4
#define THERMAL_CNTL_0_WEIGHT_ACT___M                 0xF
#define THERMAL_CNTL_0_EN_THROTTLING___S              0
#define THERMAL_CNTL_0_EN_THROTTLING___M              0x1

#define THERMAL_CNTL_1_THROTTLE_HIGH_WM___M           0xFFFFFF

#define THERMAL_CNTL_2_THROTTLE_LOW_WM___M            0xFFFFFF

#define THERMAL_CNTL_3_LEAK_AMOUNT___M                0xFFFFFF

#define THERMAL_CNTL_4_LEAK_INTERVAL___M              0xFFFFFF


#define DCVS_CNTL_BCQFULL_CNT_DISABLE___S             0x0
#define DCVS_CNTL_BCQFULL_CNT_DISABLE___M             0x1
#define DCVS_CNTL_BUSY_CNT_DISABLE___S                0x1
#define DCVS_CNTL_BUSY_CNT_DISABLE___M                0x1
#define DCVS_CNTL_ALL_CNT_DISABLE___S                 0x0
#define DCVS_CNTL_ALL_CNT_DISABLE___M                 0x3

#define DCVS_HIGH_THRESHOLD___S                       0x0
#define DCVS_HIGH_THRESHOLD___M                       0xFFFFFFFF

#define DCVS_LOW_THRESHOLD___S                        0x0
#define DCVS_LOW_THRESHOLD___M                        0xFFFFFFFF

#define DCVS_BCQFULL_SHADOW_SHADOW_CNT___S            0x0
#define DCVS_BCQFULL_SHADOW_SHADOW_CNT___M            0xFFFFFFFF

#define DCVS_BUSY_SHADOW_SHADOW_CNT___S               0x0
#define DCVS_BUSY_SHADOW_SHADOW_CNT___M               0xFFFFFFFF



#define MDDR_TEST_STATUS_DDR_TYPE___S                 24
#define MDDR_TEST_STATUS_DDR_TYPE___M                 0xF


#define MDDR_NUM_WDB_CACHE_LINES                      64
#define MDDR_NUM_SEGMENTS_WDB_CACHE_LINE              4


#define MDDR_DDRPLL_C_READY_STATUS___S                0
#define MDDR_DDRPLL_C_READY_STATUS___M                0x1


#define MDDR_TEST_REG_CNTL_WR___S                     29
#define MDDR_TEST_REG_CNTL_WR___M                     0x1
#define MDDR_TEST_REG_CNTL_INDEX_UNIT___S             8
#define MDDR_TEST_REG_CNTL_INDEX_UNIT___M             0xFFF
#define MDDR_TEST_REG_CNTL_INDEX_REG___M              0xFF


#define MDDR_DDR_DFI_CTRLUPD_REQ___S                  30
#define MDDR_DDR_DFI_CTRLUPD_REQ___M                  0x1
#define MDDR_DDR_DFI_CTRLUPD_ACK___S                  29
#define MDDR_DDR_DFI_CTRLUPD_ACK___M                  0x1


#define MDDR_TEST_SWITCH_TCA___S                      4
#define MDDR_TEST_SWITCH_TCA___M                      0x1


#define MDDR_CA_BUS_CNTL_CA_PAR___S                   12
#define MDDR_CA_BUS_CNTL_CA_PAR___M                   0x3


#define MDDR_DDR_DFI_CTRLUPD_REQ_CMD1___S             1
#define MDDR_DDR_DFI_CTRLUPD_REQ_CMD1___M             0x1
