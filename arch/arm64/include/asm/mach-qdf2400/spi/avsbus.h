/*==============================================================================
#      Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   avsbus.h
 *  @Author Prashanth Prakash (pprakash@qti.qualcomm.com)
 *  @date   2016.03.10
 *  @brief  Protocol defined constants and helper macros/functions for AVS Bus
 */

#ifndef __AVSBUS_HEADER__
#define __AVSBUS_HEADER__

#include "spi_api.h"
/******************************************************************************
 * UTILITY Macros
 *****************************************************************************/
/* Align to x-byte boundary */
#define ALIGNED(x) __attribute__((aligned (x)))

/******************************************************************************
 * AVSBUS Frame fields
 *****************************************************************************/

/* Start with all Write frame fields */

#define AVSBUS_WF_REQ_CRC_SHFT            (0)
#define AVSBUS_WF_REQ_CRC_BMSK            (0x7)

#define AVSBUS_WF_REQ_CMD_DATA_SHFT       (3)
#define AVSBUS_WF_REQ_CMD_DATA_BMSK       (0x7FFF8)

#define AVSBUS_WF_REQ_SELECT_SHFT         (19)
#define AVSBUS_WF_REQ_SELECT_BMSK         (0x780000)

#define AVSBUS_WF_REQ_CMD_DATA_TYPE_SHFT  (23)
#define AVSBUS_WF_REQ_CMD_DATA_TYPE_BMSK  (0x7800000)

#define AVSBUS_WF_REQ_CMD_GROUP_SHFT      (27)
#define AVSBUS_WF_REQ_CMD_GROUP_BMSK      (0x8000000)

#define AVSBUS_WF_REQ_CMD_SHFT            (28)
#define AVSBUS_WF_REQ_CMD_BMSK            (0x30000000)

#define AVSBUS_WF_REQ_START_CODE_SHFT     (30)
#define AVSBUS_WF_REQ_START_CODE_BMSK     (0xC0000000)

/* Fields for Write frame response */

#define AVSBUS_WF_RES_CRC_SHFT           (0)
#define AVSBUS_WF_RES_CRC_BMSK           (0x7)

#define AVSBUS_WF_RES_RESERVED_SHFT      (3)
#define AVSBUS_WF_RES_RESERVED_BMSK      (0xFFFFF8)

#define AVSBUS_WF_RES_STATUS_RESP_SHFT   (24)
#define AVSBUS_WF_RES_STATUS_RESP_BMSK   (0x1F000000)

#define AVSBUS_WF_RES_0BIT_SHFT          (29)
#define AVSBUS_WF_RES_0BIT_BMSK          (0x20000000)

#define AVSBUS_WF_RES_SLAVE_ACK_SHFT     (30)
#define AVSBUS_WF_RES_SLAVE_ACK_BMSK     (0xC0000000)

/* Fields for the Read Frame */

#define AVSBUS_RF_REQ_CRC_SHFT           (0)
#define AVSBUS_RF_REQ_CRC_BMSK           (0x7)

#define AVSBUS_RF_REQ_RESERVED_SHFT      (3)
#define AVSBUS_RF_REQ_RESERVED_BMSK      (0x7FFF8)

#define AVSBUS_RF_REQ_SELECT_SHFT        (19)
#define AVSBUS_RF_REQ_SELECT_BMSK        (0x780000)

#define AVSBUS_RF_REQ_CMD_DATA_TYPE_SHFT (23)
#define AVSBUS_RF_REQ_CMD_DATA_TYPE_BMSK (0x7800000)

#define AVSBUS_RF_REQ_CMD_GROUP_SHFT     (27)
#define AVSBUS_RF_REQ_CMD_GROUP_BMSK     (0x8000000)

#define AVSBUS_RF_REQ_CMD_SHFT           (28)
#define AVSBUS_RF_REQ_CMD_BMSK           (0x30000000)

#define AVSBUS_RF_REQ_START_CODE_SHFT    (30)
#define AVSBUS_RF_REQ_START_CODE_BMSK    (0xC0000000)

/* Fields for Read Frame response */

#define AVSBUS_RF_RES_CRC_SHFT           (0)
#define AVSBUS_RF_RES_CRC_BMSK           (0x7)

#define AVSBUS_RF_RES_RESERVED_SHFT      (3)
#define AVSBUS_RF_RES_RESERVED_BMSK      (0xF8)

#define AVSBUS_RF_RES_CMD_DATA_SHFT      (8)
#define AVSBUS_RF_RES_CMD_DATA_BMSK      (0xFFFF00)

#define AVSBUS_RF_RES_STATUS_RESP_SHFT   (24)
#define AVSBUS_RF_RES_STATUS_RESP_BMSK   (0x1F000000)

#define AVSBUS_RF_RES_0BIT_SHFT          (29)
#define AVSBUS_RF_RES_0BIT_BMSK          (0x20000000)

#define AVSBUS_RF_RES_SLAVE_ACK_SHFT     (30)
#define AVSBUS_RF_RES_SLAVE_ACK_BMSK     (0xC0000000)

/* Status Response Frame */

#define AVSBUS_SF_CRC_SHFT               (0)
#define AVSBUS_SF_CRC_BMSK               (0x7)

#define AVSBUS_SF_RESERVED_SHFT          (3)
#define AVSBUS_SF_RESERVED_BMSK          (0x00FFFFF8)

#define AVSBUS_SF_STATUS_RESP_SHFT       (24)
#define AVSBUS_SF_STATUS_RESP_BMSK       (0x1F000000)

#define AVSBUS_SF_0BIT_SHFT              (29)
#define AVSBUS_SF_0BIT_BMSK              (0x20000000)

#define AVSBUS_SF_PREFIX_SHFT            (30)
#define AVSBUS_SF_PREFIX_BMSK            (0xC0000000)


/**************************************************************************
 * AVS Bus Field Values  -- Go through section 7
 **************************************************************************/

/* <StartCode> Value */
#define AVSBUS_START_CODE                  (0b01)

/* <Cmd> field */
#define AVSBUS_CMD_WRITE_AND_COMMIT        (0b00)
#define AVSBUS_CMD_WRITE_AND_HOLD          (0b01)
#define AVSBUS_CMD_READ                    (0b11)

/* <CmdGroup> field */
#define AVSBUS_CMD_GROUP_STD_DEFINED      (0b0)
#define AVSBUS_CMD_GROUP_MFR_DEFINED      (0b1)

/* <CmdDataType> field - Standard defined(when CmdGroup = 0) */
#define AVSBUS_D_TYPE_VOLTAGE_RW              (0b0000)
#define AVSBUS_D_TYPE_VOUT_TRANSITION_RATE_RW (0b0001)
#define AVSBUS_D_TYPE_CURRENT_R               (0b0010)
#define AVSBUS_D_TYPE_TEMPERATURE_R           (0b0011)
#define AVSBUS_D_TYPE_VOLTAGE_RESET_W         (0b0100)
#define AVSBUS_D_TYPE_POWER_MODE_RW           (0b0101)
#define AVSBUS_D_TYPE_STATUS_RW               (0b1110)
#define AVSBUS_D_TYPE_VERSION_R               (0b1111)

/* <Select> fiekd */
#define AVSBUS_SELECT_BROADCAST            (0b1111)

/* <CmdData> field */
/* subfields of transition rate */
#define AVSBUS_CMD_DATA_RISE_RATE_BMSK        (0xFF00)
#define AVSBUS_CMD_DATA_RISE_RATE_SHFT        (8)
#define AVSBUS_CMD_DATA_FALL_RATE_BMSK       (0x00FF)
#define AVSBUS_CMD_DATA_FALL_RATE_SHFT        (0)

/* <CRC> field */

/* <SlaveAck> field */
#define AVSBUS_S_ACK_BAD_CRC_FAILURE         (0b10)
#define AVSBUS_S_ACK_INVALID_DATA_FAILURE    (0b11)
#define AVSBUS_S_ACK_FAILURE                 (0b01)
#define AVSBUS_S_ACK_SUCCESS                 (0b00)

/* <StatusResponse> field */
#define AVSBUS_ST_RSP_VDONE_BMSK          (0b10000)
#define AVSBUS_ST_RSP_STATUS_ALERT_BMSK   (0b01000)
#define AVSBUS_ST_RSP_AVS_CONTROL_BMSK    (0b00100)
#define AVSBUS_ST_RSP_MFRSPCFC_STTS1_BMSK (0b00010)
#define AVSBUS_ST_RSP_MFRSPCFC_STTS2_BMSK (0b00001)

/* AVSBus Status Mask - 16-bit return value from avsbus_read_status()
 * See section 8.8
 */
#define AVSBUS_STATUS_BITS_VDONE          (0x8000)
#define AVSBUS_STATUS_BITS_OCW            (0x4000)
#define AVSBUS_STATUS_BITS_UVW            (0x2000)
#define AVSBUS_STATUS_BITS_OTW            (0x1000)
#define AVSBUS_STATUS_BITS_OPW            (0x0800)
#define AVSBUS_STATUS_BITS_RESERVED       (0x0700)
#define AVSBUS_STATUS_BITS_MFRSPCFC       (0x00FF)

/* Helper Macros and functions */

#define AVSBUS_IDLE_FRAME                 ((uint32_t)~0)

#define GET_FIELD_VAL(FrameType, FieldName, FrameVal)           \
    (((FrameVal) & AVSBUS_##FrameType##_##FieldName##_BMSK) >>  \
     AVSBUS_##FrameType##_##FieldName##_SHFT)

#define PARTIAL_FRAME_VAL(FrameType, FieldName, FieldVal)               \
    ((AVSBUS_##FrameType##_##FieldName##_BMSK) &                        \
     (((uint32_t)(FieldVal)) << AVSBUS_##FrameType##_##FieldName##_SHFT))

typedef void* avsbus_handle_t;

typedef enum {
    AVSBUS_SUCCESS = 0,
    AVSBUS_ERR_MEM_ALLOC,       // Memory allocation failure
    AVSBUS_ERR_SPI_OPEN,        // Failure opening SPI instance
    AVSBUS_ERR_SPI_POWER_ON,    // Failure while turning on SPI
    AVSBUS_ERR_SPI_COMM,        // Failure in spi_full_duplex
    AVSBUS_ERR_SPI_CLOSE,       // Failure in closing SPI instance
    AVSBUS_ERR_SPI_CONFIGURE,   // Failure in configuring SPI
    AVSBUS_ERR_PARAM,           // Invalid Parameters
    AVSBUS_ERR_CRC,             // Obtained an invalid CRC
    AVSBUS_ERR_S_ACK_BAD_CRC,   // Error reported by Slave ACK(10)
    AVSBUS_ERR_S_ACK_INV_DATA,  // Error reported by Slave ACK(11)
    AVSBUS_ERR_S_ACK,           // Error reported by Slave ACK(01)
    AVSBUS_ERR_UNSUPPORTED,     // Unsupported functionality
    AVSBUS_ERR_PMBUS,           // PMBUS related error
    AVSBUS_ERR_INV_RESP,        // Invalid response frame
    AVSBUS_ERR,                 // Everything else
}avsbus_status_t;

typedef enum {
    AVSBUS_READ_FRAME,
    AVSBUS_WRITE_FRAME,
    AVSBUS_STATUS_FRAME,
}avsbus_frame_t;

/* Protocol Initialization */
avsbus_status_t avsbus_init(spi_instance_t spi_instance,
                            avsbus_handle_t *handle);

avsbus_status_t avsbus_deinit(avsbus_handle_t *handle);

/* Slave Resynchronization API */
avsbus_status_t avsbus_resync(avsbus_handle_t handle);

/***********************************************************************
 * APIs for AVSBus Standard specified commands
 ***********************************************************************/

/* Version Read */
avsbus_status_t avsbus_read_version(avsbus_handle_t handle,
                                    uint16_t *version,
                                    uint16_t *status_resp);

/* Rail Status */
avsbus_status_t avsbus_read_status(avsbus_handle_t handle,
                                   uint32_t rail_sel,
                                   uint16_t *status,
                                   uint16_t *status_resp);

/* To clear specific status bits */
avsbus_status_t avsbus_set_status(avsbus_handle_t handle,
                                  uint32_t rail_sel,
                                  uint16_t status,
                                  uint16_t *status_resp);

/* Voltage read/set APIs */
avsbus_status_t avsbus_read_voltage(avsbus_handle_t handle,
                                    uint32_t rail_sel,
                                    uint16_t *mv,
                                    uint16_t *status_resp);

avsbus_status_t avsbus_set_voltage(avsbus_handle_t handle,
                                   uint32_t rail_sel,
                                   uint16_t mv,
                                   uint16_t *status_resp);

/* Temperature read */
avsbus_status_t avsbus_read_temperature(avsbus_handle_t handle,
                                        uint32_t rail_sel,
                                        uint16_t *dc,
                                        uint16_t *status_resp);

/* Vout Transition Rate read/set */
avsbus_status_t avsbus_read_vout_trans_rate(avsbus_handle_t handle,
                                            uint32_t rail_sel,
                                            uint8_t *rise_rate,
                                            uint8_t *fall_rate,
                                            uint16_t *status_resp);

avsbus_status_t avsbus_set_vout_trans_rate(avsbus_handle_t handle,
                                           uint32_t rail_sel,
                                           uint8_t rise_rate,
                                           uint8_t fall_rate,
                                           uint16_t *status_resp);

/* Rail Current read */
avsbus_status_t avsbus_read_current(avsbus_handle_t handle,
                                    uint32_t rail_sel,
                                    uint16_t *Damp,
                                    uint16_t *status_resp);

/* Reset rail voltage */
avsbus_status_t avsbus_reset_voltage(avsbus_handle_t handle,
                                     uint32_t rail_sel,
                                     uint16_t *status_resp);


/********** APIs to allow pipelining of multiple commands ***********/

#define AVSBUS_DECLARE_REQ_FRAME_BUFFER(_name, _frame_count)    \
    uint32_t _name[(_frame_count)+1] ALIGNED(4);
#define AVSBUS_DECLARE_RESP_FRAME_BUFFER(_name, _frame_count)   \
    uint32_t _name[(_frame_count)+1] ALIGNED(4);

#define AVSBUS_SET_REQ_FRAME(_name, _idx, _frame_val)  _name[_idx] = _frame_val
#define AVSBUS_GET_RESP_FRAME(_name, _idx) _name[_idx+1]


/* Returns a 3 bit CRC(X^3+X^1+X^0 - 1011) for given 32bit value */
/*
 * Computes 3 bit CRC(X^3+X^1+X^0 - 1011) for given 32bit value
 *
 * It is reponsibility of the caller to reset the last 3 bits of "value"
 * when computing the CRC for a read/write request frame
 */
static  uint32_t avsbus_compute_crc(uint32_t value)
{
    uint32_t divisor = 0b1011 << 28 ; // X^3+X^1+X^0 - 1011<28 zeroes>
    uint32_t mask = 1 << 31;

    while (value > 0b111) {
        if (mask & value) {
            value = value ^ divisor;
        }
        mask = mask >> 1;
        divisor = divisor >> 1;
    }

    return value; //Last 3 bits of value contains the CRC
}

/* Creates a write sub-frame */
 static uint32_t avsbus_create_write_frame(uint32_t cmd, uint32_t cmd_group,
                                          uint32_t cmd_data_type, uint32_t select,
                                          uint32_t cmd_data)
{
    uint32_t frame = 0;

    frame =
        PARTIAL_FRAME_VAL(WF_REQ, START_CODE, AVSBUS_START_CODE)  |
        PARTIAL_FRAME_VAL(WF_REQ, CMD, cmd)                       |
        PARTIAL_FRAME_VAL(WF_REQ, CMD_GROUP, cmd_group)           |
        PARTIAL_FRAME_VAL(WF_REQ, CMD_DATA_TYPE, cmd_data_type)   |
        PARTIAL_FRAME_VAL(WF_REQ, SELECT, select)                 |
        PARTIAL_FRAME_VAL(WF_REQ, CMD_DATA, cmd_data);
    frame |= PARTIAL_FRAME_VAL(WF_REQ, CRC, avsbus_compute_crc(frame));

    return frame;
}


/* Creates a read frame */
static uint32_t avsbus_create_read_frame(uint32_t cmd_group,
                                         uint32_t cmd_data_type,
                                         uint32_t select)
{
    uint32_t frame = 0;

    frame =
        PARTIAL_FRAME_VAL(RF_REQ, START_CODE, AVSBUS_START_CODE)  |
        PARTIAL_FRAME_VAL(RF_REQ, CMD, AVSBUS_CMD_READ)           |
        PARTIAL_FRAME_VAL(RF_REQ, CMD_GROUP, cmd_group)           |
        PARTIAL_FRAME_VAL(RF_REQ, CMD_DATA_TYPE, cmd_data_type)   |
        PARTIAL_FRAME_VAL(RF_REQ, SELECT, select)                 |
        PARTIAL_FRAME_VAL(RF_REQ, RESERVED, ~0);
    frame |= PARTIAL_FRAME_VAL(RF_REQ, CRC, avsbus_compute_crc(frame));

    return frame;
}


/* Execute multi-Frame commands */
 uint32_t avsbus_exec_multiple_cmds(avsbus_handle_t handle,
                                   const uint32_t *req_frame,
                                   uint32_t *resp_frame, int frame_cnt);

#endif /* __AVSBUS_HEADER__ */
