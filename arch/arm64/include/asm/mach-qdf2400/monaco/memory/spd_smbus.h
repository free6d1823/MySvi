#ifndef _SPD_SMBUS_H
#define _SPD_SMBUS_H

/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* Filename: spd_smbus.h
*
* Description: Provides SMBus related interfacing and usage functionality to
*               get access to the SPD information from a specific DIMM slot.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <string.h>
#include <asm/mach/monaco/memory/spd.h>
#include <asm/plat-centriq/ddr/mddr.h>

/******************************************************************************
* Derived data types
******************************************************************************/

typedef enum
{
   QUP_STATE_RESET = 0,
   QUP_STATE_RUN = 1,
   QUP_STATE_PAUSE = 3
}
qup_state_t;


/******************************************************************************
* Defined Constants
******************************************************************************/
// General definitions to enable I2C/SMBus

// This reg can enable the clock gating in the TLMM
#define TLMM_CLK_GATE_EN_REG_ADDR                   0xFF02970000
// The TLMM_GPIO_CFG[n] controls the GPIO output enable, drive strength, pull and
// alternate function for GPIO[n]
#define TLMM_GPIO_CFG0_REG_ADDR                     (0xFF02010000+0x00000000)
#define TLMM_GPIO_CFG1_REG_ADDR                     (0xFF02010000+0x00010000)
#define TLMM_GPIO_CFG2_REG_ADDR                     (0xFF02010000+0x00020000)
#define TLMM_GPIO_CFG3_REG_ADDR                     (0xFF02010000+0x00030000)


// SMBUS values ...
//   Chan 4,2,3 : BLSP1_I2C0
//   Chan 5,1,0 : BLSP1_I2C1

// QUP I2C master supports transfers up to 256 bytes per tag
#define SPD_SMBUS_MAX_FIFO_BLOCK_SIZE               0x100   // 256B

// in-FIFO contents to the data buffer that contains 32-bit words
#define SPD_SMBUS_MAX_DATABUF_SIZE                  ((256/4)+1)

#define SPD_SMBUS_MAX_DATABUF_SIZE_BYTES            256

// 32-bit message buffer contents will be written to the out-FIFO
#define SPD_SMBUS_MSGBUF_SIZE                       12

// Length in bytes of SPD accesses
#define SPD_DATA_ADDR_LEN                           1
#define SPD_EEPROM_DATA_LEN                         1
#define SPD_TS_DATA_LEN                             2

// QUP Register Base Assignments:
#define QUP0_QUP_BASE_ADDRESS                       0xFF78730000
#define QUP1_QUP_BASE_ADDRESS                       0xFF78740000

// QUP Register Offset Assignments:
// QUP Core reg offsets
#define QUP_CONFIG_OFFSET                           0x0000
#define QUP_STATE_OFFSET                            0x0004
#define QUP_IO_MODES_OFFSET                         0x0008
#define QUP_SW_RESET_OFFSET                         0x000C
#define QUP_TRANSFER_CANCEL_OFFSET                  0x0014
#define QUP_OPERATIONAL_OFFSET                      0x0018
#define QUP_ERROR_FLAGS_OFFSET                      0x001C
#define QUP_ERROR_FLAGS_EN_OFFSET                   0x0020
#define QUP_TEST_CTRL_OFFSET                        0x0024
#define QUP_OPERATIONAL_MASK_OFFSET                 0x0028
#define QUP_HW_VERSION_OFFSET                       0x0030
// QUP Output FIFO reg offsets
#define QUP_MX_OUTPUT_COUNT_OFFSET                  0x0100
#define QUP_MX_OUTPUT_CNT_CURRENT_OFFSET            0x0104
#define QUP_OUTPUT_DEBUG_OFFSET                     0x0108
#define QUP_OUTPUT_FIFO_WORD_CNT_OFFSET             0x010C
#define QUP_OUTPUT_FIFO_BASE_OFFSET                 0x0110  // c [0..15]
#define QUP_MX_WRITE_COUNT_OFFSET                   0x0150
#define QUP_MX_WRITE_CNT_CURRENT_OFFSET             0x0154
// QUP Input FIFO reg offsets
#define QUP_MX_INPUT_COUNT_OFFSET                   0x0200
#define QUP_MX_INPUT_CNT_CURRENT_OFFSET             0x0204
#define QUP_MX_READ_COUNT_OFFSET                    0x0208
#define QUP_MX_READ_CNT_CURRENT_OFFSET              0x020C
#define QUP_INPUT_DEBUG_OFFSET                      0x0210
#define QUP_INPUT_FIFO_WORD_CNT_OFFSET              0x0214
#define QUP_INPUT_FIFO_BASE_OFFSET                  0x0218  // 0x0218+0x4*c where c [0..15]
// I2C Master mini-core reg offsets
#define I2C_MASTER_CLK_CTL_OFFSET                   0x0400
#define I2C_MASTER_STATUS_OFFSET                    0x0404
#define I2C_MASTER_CONFIG_OFFSET                    0x0408
#define I2C_MASTER_BUS_CLEAR_OFFSET                 0x040C
#define I2C_MASTER_LOCAL_ID_OFFSET                  0x0410
#define I2C_MASTER_COMMAND_OFFSET                   0x0414
#define I2C_MASTER_OUT_TAG_OFFSET                   0x0418  // Last tag handled
// I2C Master SMBus reg offsets
#define I2C_MASTER_SMBUS_RESET_CMD_OFFSET           0x0500
#define I2C_MASTER_SMBUS_STOP_CMD_OFFSET            0x0504
#define I2C_MASTER_SMBUS_IRQ_STATUS_OFFSET          0x0510
#define I2C_MASTER_SMBUS_IRQ_CLEAR_OFFSET           0x0514
#define I2C_MASTER_SMBUS_IRQ_MASK_OFFSET            0x0518
#define I2C_MASTER_SMBUS_STATUS_OFFSET              0x0520
#define I2C_MASTER_SMBUS_TIMEOUT_CURRENT_OFFSET     0x0524
#define I2C_MASTER_SMBUS_SEXT_MEXT_CURRENT_OFFSET   0x0528
#define I2C_MASTER_SMBUS_HOST_NOTIFY_CURRENT_OFFSET 0x0534
#define I2C_MASTER_SMBUS_HOST_NOTIFY_CMD_OFFSET     0x0538
#define I2C_MASTER_SMBUS_SEXT_MEXT_OFFSET           0x0530
// QUP Version 2 tags - definitions
#define QUP_TAG2_START                              0x81
#define QUP_TAG2_DATA_WRITE                         0x82
#define QUP_TAG2_DATA_WRITE_N_STOP                  0x83
#define QUP_TAG2_DATA_READ                          0x85
#define QUP_TAG2_DATA_READ_N_NACK                   0x86
#define QUP_TAG2_DATA_READ_N_STOP                   0x87
#define QUP_TAG2_START_STOP                         0x8A
// Specialty v2 tags
#define QUP_TAG2_NOP_MARK                           0x90
#define QUP_TAG2_INPUT_EOT                          0x93    // BAM mode only
#define QUP_TAG2_FLUSH_STOP                         0x96    // BAM
#define QUP_TAG2_NOP_PADDING                        0x97

#define I2C_CLK_VAL                                 0x3fd   //value recklessly stolen from the enablement kernel

// Register field definitions

// QUP_CONFIG register - contents to be changed only in RESET_STATE
#define QUP_CONFIG_N__M                             0x1F
#define QUP_CONFIG_N__S                             0x0
#define QUP_CONFIG_N                                0x7

// Set either NO_INPUT or NO_OUTPUT to 1 to disable either the input or output
//  FIFO(empty). In this case the input/output service interrupt and flag are
//  never set.
#define QUP_CONFIG_NO_INPUT__M                      0x1
#define QUP_CONFIG_NO_INPUT__S                      0x7
#define QUP_CONFIG_NO_INPUT                         0x1
#define QUP_CONFIG_NO_OUTPUT__M                     0x1
#define QUP_CONFIG_NO_OUTPUT__S                     6
#define QUP_CONFIG_NO_OUTPUT                        0x1
#define QUP_CONFIG_MINI_CORE__M                     0xF
#define QUP_CONFIG_MINI_CORE__S                     8
#define QUP_CONFIG_MINI_CORE_I2C_MASTER             0x2
#define QUP_CONFIG_MINI_CORE_SMBUS_MASTER           0x3

// QUP_STATE reg bits
#define QUP_STATE__M                                0x3
#define QUP_STATE__S                                0
#define QUP_STATE_RESET                             0x0
#define QUP_STATE_RUN                               0x1
#define QUP_STATE_PAUSE                             0x3
#define QUP_STATE_VALID__S                          2
#define QUP_STATE_VALID                             0x1     // read only. If 1 w/r of the STATE field are allowed
#define QUP_STATE_SMBUS_MAST_GEN__M                 0x1
#define QUP_STATE_SMBUS_MAST_GEN__S                 7
#define QUP_STATE_SMBUS_MAST_GEN                    0x1
#define QUP_STATE_I2C_MAST_GEN__M                   0x1
#define QUP_STATE_I2C_MAST_GEN__S                   4
#define QUP_STATE_I2C_MAST_GEN                      0x1

// QUP_IO_MODES register
#define QUP_IO_MODES_PACK_EN__S                     15
#define QUP_IO_MODES_PACK_EN                        0x1
#define QUP_IO_MODES_UNPACK_EN__S                   14
#define QUP_IO_MODES_UNPACK_EN                      0x1
#define QUP_IO_MODES_INPUT_MODE__S                  12
#define QUP_IO_MODES_INPUT_MODE__M                  0x3
#define QUP_IO_MODES_INPUT_MODE_FIFO                0x0
#define QUP_IO_MODES_INPUT_MODE_BLOCK               0x01
#define QUP_IO_MODES_OUTPUT_MODE__S                 10
#define QUP_IO_MODES_OUTPUT_MODE__M                 0x3
#define QUP_IO_MODES_OUTPUT_MODE_FIFO               0x0
#define QUP_IO_MODES_OUTPUT_MODE_BLOCK              0x1
#define QUP_IO_MODES_FIFO_SIZE__M                   0x7
#define QUP_IO_MODES_BLOCK_SIZE__M                  0x3

// QUP_OPERATIONAL register
#define QUP_OPER_RESET_VAL                          0x00000ff0
#define QUP_OPER_OUT_FIFO_NOT_EMPTY__S              4
#define QUP_OPER_OUT_FIFO_NOT_EMPTY                 0x1
#define QUP_OPER_IN_FIFO_NOT_EMPTY__S               5
#define QUP_OPER_IN_FIFO_NOT_EMPTY                  0x1
#define QUP_OPER_OUT_FIFO_FULL__S                   6
#define QUP_OPER_OUT_FIFO_FULL                      0x1
#define QUP_OPER_IN_FIFO_FULL__S                    7
#define QUP_OPER_IN_FIFO_FULL                       0x1
#define QUP_OPER_OUT_SERVICE_FLAG__S                8
#define QUP_OPER_OUT_SERVICE_FLAG                   0x1
#define QUP_OPER_IN_SERVICE_FLAG__S                 9
#define QUP_OPER_IN_SERVICE_FLAG                    0x1
#define QUP_OPER_MAX_IN_DONE_FLAG__S                11
#define QUP_OPER_MAX_IN_DONE_FLAG                   0x1

// QUP_ERROR_FLAGS and QUP_ERROR_FLAGS_EN
#define QUP_STATUS_ERROR_FLAGS_VAL                  0x0000007C  // Philip's val. Should it be 0x0000003C?

// I2C_MASTER_CONFIG reg
#define I2C_MASTER_CONFIG_EN_VERS_TWO_TAG           0x1

// I2C_MASTER_STATUS register
#define I2C_MASTER_STATUS_RESET_VAL                 0x00fffffc  // clear all flags
#define I2C_MASTER_STATUS_BUS_ERROR_VAL             0x038000fc
#define I2C_MASTER_STATUS_FAILURE_INFO_2            0x2
#define I2C_MASTER_STATUS_FAILURE_INFO_3            0x3
#define I2C_MASTER_STATUS_FAILURE_INFO__M           0x3
#define I2C_MASTER_STATUS_FAILURE_INFO__S           6
#define I2C_MASTER_STATUS_INV_WRITE                 0x1
#define I2C_MASTER_STATUS_INV_WRITE__M              0x1
#define I2C_MASTER_STATUS_INV_WRITE__S              5
#define I2C_MASTER_STATUS_DIMM_UNDETECTED_VAL       0x000020E8  // packet_nacked | invalid write| data discarded | clk ctrl not master
#define I2C_MASTER_STATUS_PKT_NACKED                0x1
#define I2C_MASTER_STATUS_PKT_NACKED__M             0x1
#define I2C_MASTER_STATUS_PKT_NACKED__S             3
#define I2C_MASTER_STATUS_BUS_ACTIVE__S             8
#define I2C_MASTER_STATUS_BUS_ACTIVE                0x1
#define I2C_MASTER_STATUS_CLK_STATE__M              0x7
#define I2C_MASTER_STATUS_CLK_STATE__S              13
#define I2C_MASTER_STATUS_CLK_STATE_RESET_BUSIDLE   0x0
#define I2C_MASTER_STATUS_CLK_STATE_NOT_MASTER      0x1
#define I2C_MASTER_STATUS_CLK_STATE_FORCED_LOW      0x5
#define I2C_MASTER_STATUS_INVALID_READ_ADDR         0x1
#define I2C_MASTER_STATUS_INVALID_READ_ADDR__S      24

// I2C_MASTER_SMBUS_IRQ_MASK register to mask (set to 1) the various indications.
// I2C Idle interrupt is masked by default.
#define I2C_MASTER_SMBUS_IRQ_MASK_STOP_ENDED__S     6
#define I2C_MASTER_SMBUS_IRQ_MASK_STOP_ENDED        0x1
#define I2C_MASTER_SMBUS_IRQ_MASK_I2C_IDLE__S       5
#define I2C_MASTER_SMBUS_IRQ_MASK_I2C_IDLE          0x1
#define I2C_MASTER_SMBUS_IRQ_MASK_HOST_NOTIFY__S    4
#define I2C_MASTER_SMBUS_IRQ_MASK_HOST_NOTIFY       0x1
#define I2C_MASTER_SMBUS_IRQ_MASK_RESUME__S         3
#define I2C_MASTER_SMBUS_IRQ_MASK_RESUME            0x1
#define I2C_MASTER_SMBUS_IRQ_MASK_MEXT__S           2
#define I2C_MASTER_SMBUS_IRQ_MASK_MEXT              0x1
#define I2C_MASTER_SMBUS_IRQ_MASK_SEXT__S           1
#define I2C_MASTER_SMBUS_IRQ_MASK_SEXT              0x1
#define I2C_MASTER_SMBUS_IRQ_MASK_TIMEOUT__S        0
#define I2C_MASTER_SMBUS_IRQ_MASK_TIMEOUT           0x1

// Allow Reconfig (ie app locks and unlocks while driver thinks it is the same transaction)
// i.e. take ctrl of the I2C bus to write and read bytes in run mode
// MX_CONFIG_DURING_RUN, bit 31 (write only) of the 4 QUP_MX_INPUT/OUTPUT/READ/WRITE_COUNT regs set to allow reconfig in run state
#define QUP_RECONFIG_DURING_RUN                     (0x80000000)

// SPD TS TCRIT Limits in degrees C
#define TCRIT_THRESHHOLD_MIN                        0
#define TCRIT_THRESHHOLD_MAX                        125


/******************************************************************************
* Global Variables
******************************************************************************/

extern dimm_slot_smbus_info_t spd_smbus_info[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];


/******************************************************************************
* Function Prototypes
******************************************************************************/
unsigned spd_smbus_get_dimm_slot_info(unsigned ddr_chan, unsigned dimm_slot, dimm_slot_smbus_info_t *smbus_info_ptr);

unsigned spd_smbus_get_spd_block(uint8_t smbus_id, uint8_t spd_bus_addr, unsigned load_size, uint64_t dst_buff_addr);
unsigned spd_smbus_get_word(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint16_t *spd_data_ptr);
unsigned spd_smbus_get_byte(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint8_t *spd_data_ptr);

unsigned spd_smbus_set_spd_block(uint8_t smbus_id, uint8_t spd_bus_addr, unsigned load_size, uint64_t dst_buff_addr);
unsigned spd_smbus_set_word(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint16_t spd_data);
unsigned spd_smbus_set_byte(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint8_t spd_data);

void spd_smbus_init(void);

unsigned spd_ts_smbus_init(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan);


#endif
