/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#ifndef __BM_SATA_DEFS_H__
#define __BM_SATA_DEFS_H__

#include "hdts/Target_cust.h"
#include "asm/mach/hal/msmhwiobase.h"
#include "sata_regs.h"

#define SATA_CONTROLLER_NUMBER 8
#define SATA_SP_NUMBER 2
#define LANES_PER_SP 4

#define SATA_SP0 0
#define SATA_SP1 1
#define SATA_SP0_LANE0 0
#define SATA_SP0_LANE1 1
#define SATA_SP0_LANE2 2
#define SATA_SP0_LANE3 3
#define SATA_SP1_LANE0 4
#define SATA_SP1_LANE1 5
#define SATA_SP1_LANE2 6
#define SATA_SP1_LANE3 7

#define SP_DATA 0
#define LANE_DATA 1

#define SATA_PHY_SPEED_GEN1 0
#define SATA_PHY_SPEED_GEN2 1
#define SATA_PHY_SPEED_GEN3 2

#define BLOCK_IO_PROTOCOL_REVISION 0x00010000
#define BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define BLOCK_IO_PROTOCOL_REVISION3 0x00020031
#define MAX_28BIT_TRANSFER_BLOCK_NUM 0x100
#define MAX_48BIT_TRANSFER_BLOCK_NUM 0xFFFF
#define ATA_CMD_READ_SECTORS 0x20
#define ATA_CMD_WRITE_SECTORS 0x30
#define ATA_CMD_READ_SECTORS_EXT 0x24
#define ATA_CMD_WRITE_SECTORS_EXT 0x34
#define ATA_CMD_READ_DMA 0xc8
#define ATA_CMD_WRITE_DMA 0xca
#define ATA_CMD_READ_DMA_EXT 0x25
#define ATA_CMD_WRITE_DMA_EXT 0x35
#define ATA_CMD_SET_FEATURES 0xef
#define ATA_CMD_IDENTIFY_DRIVE 0xec
#define ATA_CMD_READ_FPDMA 0x60
#define ATA_CMD_WRITE_FPDMA 0x61

#define ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA 0x02
#define ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN 0x04
#define ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT 0x05
#define ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN 0x0A
#define ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT 0x0B
#define ATA_PASS_THRU_LENGTH_SECTOR_COUNT 0x20
#define ATA_PASS_THRU_LENGTH_BYTES 0x80

#define ATA_XFER_PROTOCOL_FPDMA_DATA_IN 0x0E
#define ATA_XFER_PROTOCOL_FPDMA_DATA_OUT 0x0F

#define AHCI_D2H_FIS_OFFSET 0x40
#define AHCI_DMA_FIS_OFFSET 0x00
#define AHCI_PIO_FIS_OFFSET 0x20
#define AHCI_SDB_FIS_OFFSET 0x58
#define AHCI_FIS_TYPE_MASK 0xFF
#define AHCI_U_FIS_OFFSET 0x60

#define AHCI_FIS_REGISTER_D2H 0x34 // Register FIS - D2H
#define AHCI_FIS_PIO_SETUP 0x5F    // PIO Setup FIS - D2H
#define AHCI_FIS_DMA_ACTIVATE 0x39
#define AHCI_FIS_DMA_SETUP 0x41
#define AHCI_FIS_SET_DEVICE 0xA1

// SATA IMC core interrupt ID
#define SATA_0_IMC_INTR_ID 61
#define SATA_1_IMC_INTR_ID 62
#define SATA_2_IMC_INTR_ID 63
#define SATA_3_IMC_INTR_ID 64
#define SATA_4_IMC_INTR_ID 65
#define SATA_5_IMC_INTR_ID 66
#define SATA_6_IMC_INTR_ID 67
#define SATA_7_IMC_INTR_ID 68

// SATA interrupts
#define SATA_INTR_DHRE (1)
#define SATA_INTR_PSE (1 << 1)
#define SATA_INTR_DSE (1 << 2)
#define SATA_INTR_SDBE (1 << 3)
#define SATA_INTR_UFE (1 << 4)
#define SATA_INTR_DPE (1 << 5)
#define SATA_INTR_PCE (1 << 6)
#define SATA_INTR_PRCE (1 << 22)
#define SATA_INTR_IPME (1 << 23)
#define SATA_INTR_OFE (1 << 24)
#define SATA_INTR_INFE (1 << 26)
#define SATA_INTR_IFE (1 << 27)
#define SATA_INTR_HBDE (1 << 28)
#define SATA_INTR_HBFE (1 << 29)
#define SATA_INTR_TFEE (1 << 30)
#define SATA_INTR_ALL_IN (0x7dc0007f)

//-------------------------------------------------
// sys imem addr scope: 0xff70000000 ~ 0xff70040000
// fis receive addr: 0xff70020000
// cmd list addr: 0xff70020400
// cmd table addr: 0xff70020800
// prdt addr: 0xff70020C00
//-------------------------------------------------
#define SATA_RW_BUF_SMEM_ADDR (SCL_SYS_IMEM_BASE)
#define SATA_RW_BUF_SMEM_SIZE (SCL_SYS_IMEM_SIZE / 2) // SIZE_128KB
#define SATA_OP_BUF_SMEM_ADDR (SCL_SYS_IMEM_BASE + SIZE_128KB)
#define SATA_OP_BUF_SMEM_SIZE (SCL_SYS_IMEM_SIZE / 2) // SIZE_128KB

#define SATA_FIS_RECV_SMEM_ADDR (SATA_OP_BUF_SMEM_ADDR)
#define SATA_CMD_LIST_SMEM_ADDR (SATA_OP_BUF_SMEM_ADDR + 0x400)
#define SATA_CMD_TAB_SMEM_ADDR (SATA_OP_BUF_SMEM_ADDR + 0x1000)
#define SATA_PRDT_SMEM_ADDR (SCL_SYS_IMEM_BASE)

#define SATA_MAX_DATA_PER_PRDT (1024)
#define SATA_PRDT_NUMS_MAX (SATA_RW_BUF_SMEM_SIZE / SATA_MAX_DATA_PER_PRDT)

#define SATA_MULTI_CMD_NUMS_MAX 32

typedef struct SATA_PHY_INIT_T {
  UINTN Offset;
  UINT32 Value;
} Sata_Phy_Init_t;

typedef struct {
  UINT8 AhciDmaSetupFis[0x1C];
  UINT8 AhciDmaSetupFisRsvd[0x04];
  UINT8 AhciPioSetupFis[0x14];
  UINT8 AhciPioSetupFisRsvd[0x0C];
  UINT8 AhciD2HRegisterFis[0x14];
  UINT8 AhciD2HRegisterFisRsvd[0x04];
  UINT64 AhciSetDeviceBitsFis;
  UINT8 AhciUnknownFis[0x40];
  UINT8 AhciUnknownFisRsvd[0x60];
} SATA_AHCI_RECEIVED_FIS_t;

typedef struct {
  UINT32 AhciCmdCfl : 5;
  UINT32 AhciCmdA : 1;
  UINT32 AhciCmdW : 1;
  UINT32 AhciCmdP : 1;
  UINT32 AhciCmdR : 1;
  UINT32 AhciCmdB : 1;
  UINT32 AhciCmdC : 1;
  UINT32 AhciCmdRsvd : 1;
  UINT32 AhciCmdPmp : 4;
  UINT32 AhciCmdPrdtl : 16;
  UINT32 AhciCmdPrdbc;
  UINT32 AhciCmdCtba;
  UINT32 AhciCmdCtbau;
  UINT32 AhciCmdRsvd1[4];
} SATA_AHCI_COMMAND_LIST_t;

typedef struct { UINT8 AtapiCmd[0x10]; } SATA_AHCI_ATAPI_COMMAND_t;

typedef struct {
  UINT8 AhciCFisType;
  UINT8 AhciCFisPmNum : 4;
  UINT8 AhciCFisRsvd : 1;
  UINT8 AhciCFisRsvd1 : 1;
  UINT8 AhciCFisRsvd2 : 1;
  UINT8 AhciCFisCmdInd : 1;
  UINT8 AhciCFisCmd;
  UINT8 AhciCFisFeature;
  UINT8 AhciCFisSecNum;
  UINT8 AhciCFisClyLow;
  UINT8 AhciCFisClyHigh;
  UINT8 AhciCFisDevHead;
  UINT8 AhciCFisSecNumExp;
  UINT8 AhciCFisClyLowExp;
  UINT8 AhciCFisClyHighExp;
  UINT8 AhciCFisFeatureExp;
  UINT8 AhciCFisSecCount;
  UINT8 AhciCFisSecCountExp;
  UINT8 AhciCFisRsvd3;
  UINT8 AhciCFisControl;
  UINT8 AhciCFisRsvd4[4];
  UINT8 AhciCFisRsvd5[44];
} SATA_AHCI_COMMAND_FIS_t;

typedef struct {
  UINT32 AhciPrdtDba;
  UINT32 AhciPrdtDbau;
  UINT32 AhciPrdtRsvd;
  UINT32 AhciPrdtDbc : 22;
  UINT32 AhciPrdtRsvd1 : 9;
  UINT32 AhciPrdtIoc : 1;
} SATA_AHCI_COMMAND_PRDT_t;

typedef struct {
  SATA_AHCI_COMMAND_FIS_t CommandFis;
  SATA_AHCI_ATAPI_COMMAND_t AtapiCmd;
  UINT8 Reserved[0x30];
  SATA_AHCI_COMMAND_PRDT_t PrdtTable[SATA_PRDT_NUMS_MAX];
} SATA_AHCI_COMMAND_TABLE_t;

typedef struct {
  UINT16 config;
  UINT16 obsolete_1;
  UINT16 specific_config;
  UINT16 obsolete_3;
  UINT16 retired_4_5[2];
  UINT16 obsolete_6;
  UINT16 cfa_reserved_7_8[2];
  UINT16 retired_9;
  CHAR8 SerialNo[20];
  UINT16 retired_20_21[2];
  UINT16 obsolete_22;
  CHAR8 FirmwareVer[8];
  CHAR8 ModelName[40];
  UINT16 multi_sector_cmd_max_sct_cnt;
  UINT16 trusted_computing_support;
  UINT16 capabilities_49;
  UINT16 capabilities_50;
  UINT16 obsolete_51_52[2];
  UINT16 field_validity;
  UINT16 obsolete_54_58[5];
  UINT16 multi_sector_setting;
  UINT16 user_addressable_sectors_lo;
  UINT16 user_addressable_sectors_hi;
  UINT16 obsolete_62;
  UINT16 multi_word_dma_mode;
  UINT16 advanced_pio_modes;
  UINT16 min_multi_word_dma_cycle_time;
  UINT16 rec_multi_word_dma_cycle_time;
  UINT16 min_pio_cycle_time_without_flow_control;
  UINT16 min_pio_cycle_time_with_flow_control;
  UINT16 additional_supported;
  UINT16 reserved_70;
  UINT16 reserved_71_74[4];
  UINT16 queue_depth;
  UINT16 serial_ata_capabilities;
  UINT16 reserved_77;
  UINT16 serial_ata_features_supported;
  UINT16 serial_ata_features_enabled;
  UINT16 major_version_no;
  UINT16 minor_version_no;
  UINT16 command_set_supported_82;
  UINT16 command_set_supported_83;
  UINT16 command_set_feature_extn;
  UINT16 command_set_feature_enb_85;
  UINT16 command_set_feature_enb_86;
  UINT16 command_set_feature_default;
  UINT16 ultra_dma_mode;
  UINT16 time_for_security_erase_unit;
  UINT16 time_for_enhanced_security_erase_unit;
  UINT16 advanced_power_management_level;
  UINT16 master_password_identifier;
  UINT16 hardware_configuration_test_result;
  UINT16 obsolete_94;
  UINT16 stream_minimum_request_size;
  UINT16 streaming_transfer_time_for_dma;
  UINT16 streaming_access_latency_for_dma_and_pio;
  UINT16 streaming_performance_granularity[2];
  UINT16 maximum_lba_for_48bit_addressing[4];
  UINT16 streaming_transfer_time_for_pio;
  UINT16 max_no_of_512byte_blocks_per_data_set_cmd;
  UINT16 phy_logic_sector_support;
  UINT16 interseek_delay_for_iso7779;
  UINT16 world_wide_name[4];
  UINT16 reserved_for_128bit_wwn_112_115[4];
  UINT16 reserved_for_technical_report;
  UINT16 logic_sector_size_lo;
  UINT16 logic_sector_size_hi;
  UINT16 features_and_command_sets_supported_ext;
  UINT16 features_and_command_sets_enabled_ext;
  UINT16 reserved_121_126[6];
  UINT16 obsolete_127;
  UINT16 security_status;
  UINT16 vendor_specific_129_159[31];
  UINT16 cfa_power_mode;
  UINT16 reserved_for_compactflash_161_167[7];
  UINT16 device_nominal_form_factor;
  UINT16 is_data_set_cmd_supported;
  CHAR8 additional_product_identifier[8];
  UINT16 reserved_174_175[2];
  CHAR8 media_serial_number[60];
  UINT16 sct_command_transport;
  UINT16 reserved_207_208[2];
  UINT16 alignment_logic_in_phy_blocks;
  UINT16 write_read_verify_sector_count_mode3[2];
  UINT16 verify_sector_count_mode2[2];
  UINT16 nv_cache_capabilities;
  UINT16 nv_cache_size_in_logical_block_lsw;
  UINT16 nv_cache_size_in_logical_block_msw;
  UINT16 nominal_media_rotation_rate;
  UINT16 reserved_218;
  UINT16 nv_cache_options;
  UINT16 write_read_verify_mode;
  UINT16 reserved_221;
  UINT16 transport_major_revision_number;
  UINT16 transport_minor_revision_number;
  UINT16 reserved_224_229[6];
  UINT64 extended_no_of_addressable_sectors;
  UINT16 min_number_per_download_microcode_mode3;
  UINT16 max_number_per_download_microcode_mode3;
  UINT16 reserved_236_254[19];
  UINT16 integrity_word;
} SATA_ATA_IDENTIFY_DATA_t;

typedef enum {
  SATA_BIST_PATTERN_SSOP,
  SATA_BIST_PATTERN_HTDP,
  SATA_BIST_PATTERN_LTDP,
  SATA_BIST_PATTERN_LFSCP,
  SATA_BIST_PATTERN_COMP,
  SATA_BIST_PATTERN_LBP,
  SATA_BIST_PATTERN_MFTP,
  SATA_BIST_PATTERN_HFTP,
  SATA_BIST_PATTERN_LFTP,
  SATA_BIST_PATTERN_MAX_NUM,
} SATA_BIST_PATTERN_t;

typedef enum {
  SATA_PHY_PRBS_7,
  SATA_PHY_PRBS_9,
  SATA_PHY_PRBS_10,
  SATA_PHY_PRBS_SHIFT10BIT,
  SATA_PHY_PRBS_MAX_NUM,
} SATA_PHY_PRBS_t;

typedef struct {
  BOOLEAN UdmaValid;
  BOOLEAN FpdmaEnable;
  BOOLEAN Lba48Bit;
  UINT32 BlockSize;
  UINT32 IoAlign; // sizeof (UINTN)
  UINT32 LogicalBlksPerPhyBlk;
  UINT32 LowestAlignedLba;
  UINT64 LastBlock;
  UINT64 IORevision;
  UINT32 Controller;
  UINT32 UdmaMode;
} SataDevice_t;

typedef struct {
  UINT8 Reserved1[2];
  UINT8 AtaCommand;
  UINT8 AtaFeatures;
  UINT8 AtaSectorNumber;
  UINT8 AtaCylinderLow;
  UINT8 AtaCylinderHigh;
  UINT8 AtaDeviceHead;
  UINT8 AtaSectorNumberExp;
  UINT8 AtaCylinderLowExp;
  UINT8 AtaCylinderHighExp;
  UINT8 AtaFeaturesExp;
  UINT8 AtaSectorCount;
  UINT8 AtaSectorCountExp;
  UINT8 Reserved2[2];
} ATACmdBlock_t;

typedef struct {
  UINT8 Reserved1[2];
  UINT8 AtaStatus;
  UINT8 AtaError;
  UINT8 AtaSectorNumber;
  UINT8 AtaCylinderLow;
  UINT8 AtaCylinderHigh;
  UINT8 AtaDeviceHead;
  UINT8 AtaSectorNumberExp;
  UINT8 AtaCylinderLowExp;
  UINT8 AtaCylinderHighExp;
  UINT8 Reserved2;
  UINT8 AtaSectorCount;
  UINT8 AtaSectorCountExp;
  UINT8 Reserved3[2];
} ATAStatusBlock_t;

typedef struct {
  ATAStatusBlock_t *Asb;
  ATACmdBlock_t *Acb;
  UINT64 Timeout;
  void *InDataBuffer;
  void *OutDataBuffer;
  UINT32 InTransferLength;
  UINT32 OutTransferLength;
  UINT8 Protocol;
  UINT8 Length;
} ATATransCmdPacket_t;

#endif /* __BM_SATA_DEFS_H__ */
