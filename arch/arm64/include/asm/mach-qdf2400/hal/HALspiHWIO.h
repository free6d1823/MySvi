/*==============================================================================
#      Copyright (c) 2014-2016 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#
#
# Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
#
#=============================================================================*/
/** @file   tlmm.h
 *  @brief  Aliases the GPIO manipulation functions to the proper HWIO functions
 */

#ifndef TLMM_H
#define TLMM_H

#include <stdint.h>

#include <asm/hal/HALhwio.h>
#include "HALtlmmHWIO.h"
#include "msmhwiobase.h"

// Extract various fields from TLMM packed configuration
#define GPIO_NUMBER(config)       (((config)&0x3FF0)>>4)
#define GPIO_OUTVAL(config)       (((config)&0x1E00000)>>0x15)
#define GPIO_DRVSTR_VAL(config)   (((config)&0x1E0000)>>17)
#define GPIO_PULL_VAL(config)     (((config)&0x18000)>>15)
#define GPIO_DIR_VAL(config)      (((config)&0x4000)>>14)
#define GPIO_FUNC_VAL(config)     ((config)&0xF)

/* typecast all the gpios to uint64_t to avoid -Wint-to-pointer conversion warnings as
 * the passed gpio variable can be u8, u16 or u32 type
 */
#define GPIO_SET(gpio)             HWIO_TLMM_GPIO_IN_OUTn_OUTMI((uint64_t)gpio, HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK, (1) << HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT)
#define GPIO_CLEAR(gpio)           HWIO_TLMM_GPIO_IN_OUTn_OUTMI((uint64_t)gpio, HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK, (0) << HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT)
#define GPIO_GET(gpio)             HWIO_TLMM_GPIO_IN_OUTn_INMI((uint64_t)gpio, HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_BMSK)

#define GPIO_OUT_EN(gpio)          HWIO_TLMM_GPIO_CFGn_OUTMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_GPIO_OE_BMSK, (1) << HWIO_TLMM_GPIO_CFGn_GPIO_OE_SHFT)
#define GPIO_OUT_DIS(gpio)         HWIO_TLMM_GPIO_CFGn_OUTMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_GPIO_OE_BMSK, (0) << HWIO_TLMM_GPIO_CFGn_GPIO_OE_SHFT)
#define GPIO_OUT_GET(gpio)         HWIO_TLMM_GPIO_CFGn_INMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_GPIO_OE_BMSK)

#define GPIO_SET_STR(gpio, str)    HWIO_TLMM_GPIO_CFGn_OUTMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_BMSK, (str) << HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_SHFT)
#define GPIO_GET_STR(gpio, str)    HWIO_TLMM_GPIO_CFGn_INMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_BMSK)

#define GPIO_SET_PULL(gpio, pull)  HWIO_TLMM_GPIO_CFGn_OUTMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_GPIO_PULL_BMSK, (pull) << HWIO_TLMM_GPIO_CFGn_GPIO_PULL_SHFT)
#define GPIO_GET_PULL(gpio)        HWIO_TLMM_GPIO_CFGn_INMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_GPIO_PULL_BMSK)

#define GPIO_SET_FUNC(gpio, func)  HWIO_TLMM_GPIO_CFGn_OUTMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_FUNC_SEL_BMSK, (func) << HWIO_TLMM_GPIO_CFGn_FUNC_SEL_SHFT)
#define GPIO_GET_FUNC(gpio)        HWIO_TLMM_GPIO_CFGn_INMI((uint64_t)gpio, HWIO_TLMM_GPIO_CFGn_FUNC_SEL_BMSK)

#define GPIO_SET_WAKE_INT(gpio)    HWIO_TLMM_GPIO_WAKEUP_INT_EN_0_OUTM(HWIO_TLMM_GPIO_WAKEUP_INT_EN_0_GPIO_##gpio##_BMSK, (1) << HWIO_TLMM_GPIO_WAKEUP_INT_EN_0_GPIO_##gpio##_SHFT)
#define GPIO_CLEAR_WAKE_INT(gpio)  HWIO_TLMM_GPIO_WAKEUP_INT_EN_0_OUTM(HWIO_TLMM_GPIO_WAKEUP_INT_EN_0_GPIO_##gpio##_BMSK, (0) << HWIO_TLMM_GPIO_WAKEUP_INT_EN_0_GPIO_##gpio##_SHFT)
#define GPIO_GET_WAKE_INT(gpio)    HWIO_TLMM_GPIO_WAKEUP_INT_EN_0_INM(HWIO_TLMM_GPIO_WAKEUP_INT_EN_0_GPIO_##gpio##_BMSK)

/* use this API to trigger a summary interrupt for HLOS on GPIOs not connected to padring */
#define GPIO_SET_INTR(gpio)        HWIO_TLMM_GPIO_INTR_STATUSn_OUTMI((uint64_t)gpio, HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_BMSK, (1) << HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_SHFT)

/*
 * If a SW-only GPIO is configured as direct connect in addition to GPIO_SET_INTR,
 * we need to call the below macro to make sure OSPM gets the interrupt
 * notification
 */
#define GPIO_DIRECT_CONN_SET_SPI(direct_conn_intr_num)  HWIO_APCS_QGICDR_GICD_SETSPI_NSR_OUT(HMSS_QGIC_BASE, direct_conn_intr_num)

#define GPIO_LATEST_VERSION 0x10000000
#define GPIO_GET_VERSION           (HWIO_TLMM_HW_REVISION_NUMBER_INM(HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_BMSK) >> HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_SHFT)
// returns 1 if version is compatible with current code, 0 otherwise
#define GPIO_CHECK_VERSION         (GPIO_GET_VERSION <= GPIO_LATEST_VERSION)

#define GPIO_MFG_ID         0x070
#define GPIO_GET_MFG_ID            (HWIO_TLMM_HW_REVISION_NUMBER_INM(HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_BMSK) >> HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_SHFT)
// returns 1 if mfg_id matches Qualcomm's, 0 otherwise
#define GPIO_CHECK_MFG_ID          (GPIO_GET_MFG_ID == GPIO_MFG_ID)

#define GPIO_PULL_NO_PULL    0x0
#define GPIO_PULL_PULL_DOWN  0x1
#define GPIO_PULL_KEEPER     0x2
#define GPIO_PULL_PULL_UP    0x3

#define GPIO_DRV_2_MA   0x0
#define GPIO_DRV_4_MA   0x1
#define GPIO_DRV_6_MA   0x2
#define GPIO_DRV_8_MA   0x3
#define GPIO_DRV_10_MA  0x4
#define GPIO_DRV_12_MA  0x5
#define GPIO_DRV_14_MA  0x6
#define GPIO_DRV_16_MA  0x7
/*****************************************************************************/
#define REG_BASE_OFFS                                                     0
#define HWIO_QUP_CONFIG_OFFS                                               (REG_BASE_OFFS + 0x00000000)
#define HWIO_QUP_CONFIG_RMSK                                                  0x3ffff
#define HWIO_QUP_CONFIG_DIS_INBUF_FLAG_FIX_BMSK                               0x20000
#define HWIO_QUP_CONFIG_DIS_INBUF_FLAG_FIX_SHFT                                  0x11
#define HWIO_QUP_CONFIG_EN_EXT_OUT_FLAG_BMSK                                  0x10000
#define HWIO_QUP_CONFIG_EN_EXT_OUT_FLAG_SHFT                                     0x10
#define HWIO_QUP_CONFIG_CORE_EXTRA_CLK_ON_EN_BMSK                              0x8000
#define HWIO_QUP_CONFIG_CORE_EXTRA_CLK_ON_EN_SHFT                                 0xf
#define HWIO_QUP_CONFIG_FIFO_CLK_GATE_EN_BMSK                                  0x4000
#define HWIO_QUP_CONFIG_FIFO_CLK_GATE_EN_SHFT                                     0xe
#define HWIO_QUP_CONFIG_CORE_CLK_ON_EN_BMSK                                    0x2000
#define HWIO_QUP_CONFIG_CORE_CLK_ON_EN_SHFT                                       0xd
#define HWIO_QUP_CONFIG_APP_CLK_ON_EN_BMSK                                     0x1000
#define HWIO_QUP_CONFIG_APP_CLK_ON_EN_SHFT                                        0xc
#define HWIO_QUP_CONFIG_MINI_CORE_BMSK                                          0xf00
#define HWIO_QUP_CONFIG_MINI_CORE_SHFT                                            0x8
#define HWIO_QUP_CONFIG_NO_INPUT_BMSK                                            0x80
#define HWIO_QUP_CONFIG_NO_INPUT_SHFT                                             0x7
#define HWIO_QUP_CONFIG_NO_OUTPUT_BMSK                                           0x40
#define HWIO_QUP_CONFIG_NO_OUTPUT_SHFT                                            0x6
#define HWIO_QUP_CONFIG_QUP_HREADY_CTRL_BMSK                                     0x20
#define HWIO_QUP_CONFIG_QUP_HREADY_CTRL_SHFT                                      0x5
#define HWIO_QUP_CONFIG_N_BMSK                                                   0x1f
#define HWIO_QUP_CONFIG_N_SHFT                                                    0x0

#define MINI_CORE_SPI                                                             0x1

#define HWIO_QUP_STATE_OFFS                                                (REG_BASE_OFFS + 0x00000004)
#define HWIO_QUP_STATE_RMSK                                                      0x7f
#define HWIO_QUP_STATE_I2C_FLUSH_BMSK                                            0x40
#define HWIO_QUP_STATE_I2C_FLUSH_SHFT                                             0x6
#define HWIO_QUP_STATE_WAIT_FOR_EOT_BMSK                                         0x20
#define HWIO_QUP_STATE_WAIT_FOR_EOT_SHFT                                          0x5
#define HWIO_QUP_STATE_I2C_MAST_GEN_BMSK                                         0x10
#define HWIO_QUP_STATE_I2C_MAST_GEN_SHFT                                          0x4
#define HWIO_QUP_STATE_SPI_GEN_BMSK                                               0x8
#define HWIO_QUP_STATE_SPI_GEN_SHFT                                               0x3
#define HWIO_QUP_STATE_STATE_VALID_BMSK                                           0x4
#define HWIO_QUP_STATE_STATE_VALID_SHFT                                           0x2
#define HWIO_QUP_STATE_STATE_BMSK                                                 0x3
#define HWIO_QUP_STATE_STATE_SHFT                                                 0x0

#define HWIO_QUP_IO_MODES_OFFS                                             (REG_BASE_OFFS + 0x00000008)
#define HWIO_QUP_IO_MODES_RMSK                                                0x1ffff
#define HWIO_QUP_IO_MODES_OUTPUT_BIT_SHIFT_EN_BMSK                            0x10000
#define HWIO_QUP_IO_MODES_OUTPUT_BIT_SHIFT_EN_SHFT                               0x10
#define HWIO_QUP_IO_MODES_PACK_EN_BMSK                                         0x8000
#define HWIO_QUP_IO_MODES_PACK_EN_SHFT                                            0xf
#define HWIO_QUP_IO_MODES_UNPACK_EN_BMSK                                       0x4000
#define HWIO_QUP_IO_MODES_UNPACK_EN_SHFT                                          0xe
#define HWIO_QUP_IO_MODES_INPUT_MODE_BMSK                                      0x3000
#define HWIO_QUP_IO_MODES_INPUT_MODE_SHFT                                         0xc
#define HWIO_QUP_IO_MODES_OUTPUT_MODE_BMSK                                      0xc00
#define HWIO_QUP_IO_MODES_OUTPUT_MODE_SHFT                                        0xa
#define HWIO_QUP_IO_MODES_INPUT_FIFO_SIZE_BMSK                                  0x380
#define HWIO_QUP_IO_MODES_INPUT_FIFO_SIZE_SHFT                                    0x7
#define HWIO_QUP_IO_MODES_INPUT_BLOCK_SIZE_BMSK                                  0x60
#define HWIO_QUP_IO_MODES_INPUT_BLOCK_SIZE_SHFT                                   0x5
#define HWIO_QUP_IO_MODES_OUTPUT_FIFO_SIZE_BMSK                                  0x1c
#define HWIO_QUP_IO_MODES_OUTPUT_FIFO_SIZE_SHFT                                   0x2
#define HWIO_QUP_IO_MODES_OUTPUT_BLOCK_SIZE_BMSK                                  0x3
#define HWIO_QUP_IO_MODES_OUTPUT_BLOCK_SIZE_SHFT                                  0x0

#define MODE_FIFO                                                                 0x0
#define MODE_BLOCK                                                                0x1
#define MODE_BAM                                                                  0x3

#define HWIO_QUP_SW_RESET_OFFS                                             (REG_BASE_OFFS + 0x0000000c)
#define HWIO_QUP_SW_RESET_RMSK                                             0xffffffff
#define HWIO_QUP_SW_RESET_QUP_SW_RESET_BMSK                                0xffffffff
#define HWIO_QUP_SW_RESET_QUP_SW_RESET_SHFT                                       0x0

#define HWIO_QUP_TRANSFER_CANCEL_OFFS                                      (REG_BASE_OFFS + 0x00000014)
#define HWIO_QUP_TRANSFER_CANCEL_RMSK                                          0xff80
#define HWIO_QUP_TRANSFER_CANCEL_TRANSFER_CANCEL_ID_BMSK                       0xff00
#define HWIO_QUP_TRANSFER_CANCEL_TRANSFER_CANCEL_ID_SHFT                          0x8
#define HWIO_QUP_TRANSFER_CANCEL_TRANSFER_CANCEL_BMSK                            0x80
#define HWIO_QUP_TRANSFER_CANCEL_TRANSFER_CANCEL_SHFT                             0x7

#define HWIO_QUP_OPERATIONAL_OFFS                                          (REG_BASE_OFFS + 0x00000018)
#define HWIO_QUP_OPERATIONAL_RMSK                                              0xfff0
#define HWIO_QUP_OPERATIONAL_NWD_BMSK                                          0x8000
#define HWIO_QUP_OPERATIONAL_NWD_SHFT                                             0xf
#define HWIO_QUP_OPERATIONAL_DONE_TOGGLE_BMSK                                  0x4000
#define HWIO_QUP_OPERATIONAL_DONE_TOGGLE_SHFT                                     0xe
#define HWIO_QUP_OPERATIONAL_IN_BLOCK_READ_REQ_BMSK                            0x2000
#define HWIO_QUP_OPERATIONAL_IN_BLOCK_READ_REQ_SHFT                               0xd
#define HWIO_QUP_OPERATIONAL_OUT_BLOCK_WRITE_REQ_BMSK                          0x1000
#define HWIO_QUP_OPERATIONAL_OUT_BLOCK_WRITE_REQ_SHFT                             0xc
#define HWIO_QUP_OPERATIONAL_MAX_INPUT_DONE_FLAG_BMSK                           0x800
#define HWIO_QUP_OPERATIONAL_MAX_INPUT_DONE_FLAG_SHFT                             0xb
#define HWIO_QUP_OPERATIONAL_MAX_OUTPUT_DONE_FLAG_BMSK                          0x400
#define HWIO_QUP_OPERATIONAL_MAX_OUTPUT_DONE_FLAG_SHFT                            0xa
#define HWIO_QUP_OPERATIONAL_INPUT_SERVICE_FLAG_BMSK                            0x200
#define HWIO_QUP_OPERATIONAL_INPUT_SERVICE_FLAG_SHFT                              0x9
#define HWIO_QUP_OPERATIONAL_OUTPUT_SERVICE_FLAG_BMSK                           0x100
#define HWIO_QUP_OPERATIONAL_OUTPUT_SERVICE_FLAG_SHFT                             0x8
#define HWIO_QUP_OPERATIONAL_INPUT_FIFO_FULL_BMSK                                0x80
#define HWIO_QUP_OPERATIONAL_INPUT_FIFO_FULL_SHFT                                 0x7
#define HWIO_QUP_OPERATIONAL_OUTPUT_FIFO_FULL_BMSK                               0x40
#define HWIO_QUP_OPERATIONAL_OUTPUT_FIFO_FULL_SHFT                                0x6
#define HWIO_QUP_OPERATIONAL_INPUT_FIFO_NOT_EMPTY_BMSK                           0x20
#define HWIO_QUP_OPERATIONAL_INPUT_FIFO_NOT_EMPTY_SHFT                            0x5
#define HWIO_QUP_OPERATIONAL_OUTPUT_FIFO_NOT_EMPTY_BMSK                          0x10
#define HWIO_QUP_OPERATIONAL_OUTPUT_FIFO_NOT_EMPTY_SHFT                           0x4

#define HWIO_QUP_ERROR_FLAGS_OFFS                                          (REG_BASE_OFFS + 0x0000001c)
#define HWIO_QUP_ERROR_FLAGS_RMSK                                                0x3c
#define HWIO_QUP_ERROR_FLAGS_OUTPUT_OVER_RUN_ERR_BMSK                            0x20
#define HWIO_QUP_ERROR_FLAGS_OUTPUT_OVER_RUN_ERR_SHFT                             0x5
#define HWIO_QUP_ERROR_FLAGS_INPUT_UNDER_RUN_ERR_BMSK                            0x10
#define HWIO_QUP_ERROR_FLAGS_INPUT_UNDER_RUN_ERR_SHFT                             0x4
#define HWIO_QUP_ERROR_FLAGS_OUTPUT_UNDER_RUN_ERR_BMSK                            0x8
#define HWIO_QUP_ERROR_FLAGS_OUTPUT_UNDER_RUN_ERR_SHFT                            0x3
#define HWIO_QUP_ERROR_FLAGS_INPUT_OVER_RUN_ERR_BMSK                              0x4
#define HWIO_QUP_ERROR_FLAGS_INPUT_OVER_RUN_ERR_SHFT                              0x2

#define HWIO_QUP_ERROR_FLAGS_EN_OFFS                                       (REG_BASE_OFFS + 0x00000020)
#define HWIO_QUP_ERROR_FLAGS_EN_RMSK                                             0x3c
#define HWIO_QUP_ERROR_FLAGS_EN_OUTPUT_OVER_RUN_ERR_EN_BMSK                      0x20
#define HWIO_QUP_ERROR_FLAGS_EN_OUTPUT_OVER_RUN_ERR_EN_SHFT                       0x5
#define HWIO_QUP_ERROR_FLAGS_EN_INPUT_UNDER_RUN_ERR_EN_BMSK                      0x10
#define HWIO_QUP_ERROR_FLAGS_EN_INPUT_UNDER_RUN_ERR_EN_SHFT                       0x4
#define HWIO_QUP_ERROR_FLAGS_EN_OUTPUT_UNDER_RUN_ERR_EN_BMSK                      0x8
#define HWIO_QUP_ERROR_FLAGS_EN_OUTPUT_UNDER_RUN_ERR_EN_SHFT                      0x3
#define HWIO_QUP_ERROR_FLAGS_EN_INPUT_OVER_RUN_ERR_EN_BMSK                        0x4
#define HWIO_QUP_ERROR_FLAGS_EN_INPUT_OVER_RUN_ERR_EN_SHFT                        0x2

#define HWIO_QUP_OPERATIONAL_MASK_OFFS                                     (REG_BASE_OFFS + 0x00000028)
#define HWIO_QUP_OPERATIONAL_MASK_RMSK                                          0x300
#define HWIO_QUP_OPERATIONAL_MASK_INPUT_SERVICE_MASK_BMSK                       0x200
#define HWIO_QUP_OPERATIONAL_MASK_INPUT_SERVICE_MASK_SHFT                         0x9
#define HWIO_QUP_OPERATIONAL_MASK_OUTPUT_SERVICE_MASK_BMSK                      0x100
#define HWIO_QUP_OPERATIONAL_MASK_OUTPUT_SERVICE_MASK_SHFT                        0x8

#define HWIO_QUP_HW_VERSION_OFFS                                           (REG_BASE_OFFS + 0x00000030)
#define HWIO_QUP_HW_VERSION_RMSK                                           0xffffffff
#define HWIO_QUP_HW_VERSION_MAJOR_BMSK                                     0xf0000000
#define HWIO_QUP_HW_VERSION_MAJOR_SHFT                                           0x1c
#define HWIO_QUP_HW_VERSION_MINOR_BMSK                                      0xfff0000
#define HWIO_QUP_HW_VERSION_MINOR_SHFT                                           0x10
#define HWIO_QUP_HW_VERSION_STEP_BMSK                                          0xffff
#define HWIO_QUP_HW_VERSION_STEP_SHFT                                             0x0

#define HWIO_QUP_MX_OUTPUT_COUNT_OFFS                                      (REG_BASE_OFFS + 0x00000100)
#define HWIO_QUP_MX_OUTPUT_COUNT_RMSK                                      0x8000ffff
#define HWIO_QUP_MX_OUTPUT_COUNT_MX_CONFIG_DURING_RUN_BMSK                 0x80000000
#define HWIO_QUP_MX_OUTPUT_COUNT_MX_CONFIG_DURING_RUN_SHFT                       0x1f
#define HWIO_QUP_MX_OUTPUT_COUNT_MX_OUTPUT_COUNT_BMSK                          0xffff
#define HWIO_QUP_MX_OUTPUT_COUNT_MX_OUTPUT_COUNT_SHFT                             0x0

#define HWIO_QUP_MX_OUTPUT_CNT_CURRENT_OFFS                                (REG_BASE_OFFS + 0x00000104)
#define HWIO_QUP_MX_OUTPUT_CNT_CURRENT_RMSK                                    0xffff
#define HWIO_QUP_MX_OUTPUT_CNT_CURRENT_MX_OUTPUT_CNT_CURRENT_BMSK              0xffff
#define HWIO_QUP_MX_OUTPUT_CNT_CURRENT_MX_OUTPUT_CNT_CURRENT_SHFT                 0x0

#define HWIO_QUP_OUTPUT_FIFO_WORD_CNT_OFFS                                 (REG_BASE_OFFS + 0x0000010c)
#define HWIO_QUP_OUTPUT_FIFO_WORD_CNT_RMSK                                      0x1ff
#define HWIO_QUP_OUTPUT_FIFO_WORD_CNT_OUTPUT_FIFO_WORD_CNT_BMSK                 0x1ff
#define HWIO_QUP_OUTPUT_FIFO_WORD_CNT_OUTPUT_FIFO_WORD_CNT_SHFT                   0x0

#define HWIO_QUP_OUTPUT_FIFOc_OFFS                                         (REG_BASE_OFFS + 0x00000110)
#define HWIO_QUP_OUTPUT_FIFOc_RMSK                                         0xffffffff
#define HWIO_QUP_OUTPUT_FIFOc_MAXc                                                 15
#define HWIO_QUP_OUTPUT_FIFOc_OUTPUT_BMSK                                  0xffffffff
#define HWIO_QUP_OUTPUT_FIFOc_OUTPUT_SHFT                                         0x0

#define HWIO_QUP_MX_WRITE_COUNT_OFFS                                       (REG_BASE_OFFS + 0x00000150)
#define HWIO_QUP_MX_WRITE_COUNT_RMSK                                       0x8000ffff
#define HWIO_QUP_MX_WRITE_COUNT_MX_CONFIG_DURING_RUN_BMSK                  0x80000000
#define HWIO_QUP_MX_WRITE_COUNT_MX_CONFIG_DURING_RUN_SHFT                        0x1f
#define HWIO_QUP_MX_WRITE_COUNT_MX_WRITE_COUNT_BMSK                            0xffff
#define HWIO_QUP_MX_WRITE_COUNT_MX_WRITE_COUNT_SHFT                               0x0

#define HWIO_QUP_MX_WRITE_CNT_CURRENT_OFFS                                 (REG_BASE_OFFS + 0x00000154)
#define HWIO_QUP_MX_WRITE_CNT_CURRENT_RMSK                                     0xffff
#define HWIO_QUP_MX_WRITE_CNT_CURRENT_MX_WRITE_CNT_CURRENT_BMSK                0xffff
#define HWIO_QUP_MX_WRITE_CNT_CURRENT_MX_WRITE_CNT_CURRENT_SHFT                   0x0

#define HWIO_QUP_MX_INPUT_COUNT_OFFS                                       (REG_BASE_OFFS + 0x00000200)
#define HWIO_QUP_MX_INPUT_COUNT_RMSK                                       0x8000ffff
#define HWIO_QUP_MX_INPUT_COUNT_MX_CONFIG_DURING_RUN_BMSK                  0x80000000
#define HWIO_QUP_MX_INPUT_COUNT_MX_CONFIG_DURING_RUN_SHFT                        0x1f
#define HWIO_QUP_MX_INPUT_COUNT_MX_INPUT_COUNT_BMSK                            0xffff
#define HWIO_QUP_MX_INPUT_COUNT_MX_INPUT_COUNT_SHFT                               0x0

#define HWIO_QUP_MX_INPUT_CNT_CURRENT_OFFS                                 (REG_BASE_OFFS + 0x00000204)
#define HWIO_QUP_MX_INPUT_CNT_CURRENT_RMSK                                     0xffff
#define HWIO_QUP_MX_INPUT_CNT_CURRENT_MX_INPUT_CNT_CURRENT_BMSK                0xffff
#define HWIO_QUP_MX_INPUT_CNT_CURRENT_MX_INPUT_CNT_CURRENT_SHFT                   0x0

#define HWIO_QUP_MX_READ_COUNT_OFFS                                        (REG_BASE_OFFS + 0x00000208)
#define HWIO_QUP_MX_READ_COUNT_RMSK                                        0x8000ffff
#define HWIO_QUP_MX_READ_COUNT_MX_CONFIG_DURING_RUN_BMSK                   0x80000000
#define HWIO_QUP_MX_READ_COUNT_MX_CONFIG_DURING_RUN_SHFT                         0x1f
#define HWIO_QUP_MX_READ_COUNT_MX_READ_COUNT_BMSK                              0xffff
#define HWIO_QUP_MX_READ_COUNT_MX_READ_COUNT_SHFT                                 0x0

#define HWIO_QUP_MX_READ_CNT_CURRENT_OFFS                                  (REG_BASE_OFFS + 0x0000020c)
#define HWIO_QUP_MX_READ_CNT_CURRENT_RMSK                                      0xffff
#define HWIO_QUP_MX_READ_CNT_CURRENT_MX_READ_CNT_CURRENT_BMSK                  0xffff
#define HWIO_QUP_MX_READ_CNT_CURRENT_MX_READ_CNT_CURRENT_SHFT                     0x0

#define HWIO_QUP_INPUT_FIFO_WORD_CNT_OFFS                                  (REG_BASE_OFFS + 0x00000214)
#define HWIO_QUP_INPUT_FIFO_WORD_CNT_RMSK                                       0x1ff
#define HWIO_QUP_INPUT_FIFO_WORD_CNT_INPUT_FIFO_WORD_CNT_BMSK                   0x1ff
#define HWIO_QUP_INPUT_FIFO_WORD_CNT_INPUT_FIFO_WORD_CNT_SHFT                     0x0

#define HWIO_QUP_INPUT_FIFOc_OFFS                                          (REG_BASE_OFFS + 0x00000218)
#define HWIO_QUP_INPUT_FIFOc_RMSK                                          0xffffffff
#define HWIO_QUP_INPUT_FIFOc_MAXc                                                  15
#define HWIO_QUP_INPUT_FIFOc_INPUT_BMSK                                    0xffffffff
#define HWIO_QUP_INPUT_FIFOc_INPUT_SHFT                                           0x0

#define HWIO_SPI_CONFIG_OFFS                                               (REG_BASE_OFFS + 0x00000300)
#define HWIO_SPI_CONFIG_RMSK                                                    0x720
#define HWIO_SPI_CONFIG_HS_MODE_BMSK                                            0x400
#define HWIO_SPI_CONFIG_HS_MODE_SHFT                                              0xa
#define HWIO_SPI_CONFIG_INPUT_FIRST_BMSK                                        0x200
#define HWIO_SPI_CONFIG_INPUT_FIRST_SHFT                                          0x9
#define HWIO_SPI_CONFIG_LOOP_BACK_BMSK                                          0x100
#define HWIO_SPI_CONFIG_LOOP_BACK_SHFT                                            0x8
#define HWIO_SPI_CONFIG_SLAVE_OPERATION_BMSK                                     0x20
#define HWIO_SPI_CONFIG_SLAVE_OPERATION_SHFT                                      0x5

#define HWIO_SPI_IO_CONTROL_OFFS                                           (REG_BASE_OFFS + 0x00000304)
#define HWIO_SPI_IO_CONTROL_RMSK                                                0xfff
#define HWIO_SPI_IO_CONTROL_FORCE_CS_BMSK                                       0x800
#define HWIO_SPI_IO_CONTROL_FORCE_CS_SHFT                                         0xb
#define HWIO_SPI_IO_CONTROL_CLK_IDLE_HIGH_BMSK                                  0x400
#define HWIO_SPI_IO_CONTROL_CLK_IDLE_HIGH_SHFT                                    0xa
#define HWIO_SPI_IO_CONTROL_CLK_ALWAYS_ON_BMSK                                  0x200
#define HWIO_SPI_IO_CONTROL_CLK_ALWAYS_ON_SHFT                                    0x9
#define HWIO_SPI_IO_CONTROL_MX_CS_MODE_BMSK                                     0x100
#define HWIO_SPI_IO_CONTROL_MX_CS_MODE_SHFT                                       0x8
#define HWIO_SPI_IO_CONTROL_CS_N_POLARITY_BMSK                                   0xf0
#define HWIO_SPI_IO_CONTROL_CS_N_POLARITY_SHFT                                    0x4
#define HWIO_SPI_IO_CONTROL_CS_SELECT_BMSK                                        0xc
#define HWIO_SPI_IO_CONTROL_CS_SELECT_SHFT                                        0x2
#define HWIO_SPI_IO_CONTROL_TRISTATE_CS_BMSK                                      0x2
#define HWIO_SPI_IO_CONTROL_TRISTATE_CS_SHFT                                      0x1
#define HWIO_SPI_IO_CONTROL_NO_TRI_STATE_BMSK                                     0x1
#define HWIO_SPI_IO_CONTROL_NO_TRI_STATE_SHFT                                     0x0

#define HWIO_SPI_ERROR_FLAGS_OFFS                                          (REG_BASE_OFFS + 0x00000308)
#define HWIO_SPI_ERROR_FLAGS_RMSK                                                 0xf
#define HWIO_SPI_ERROR_FLAGS_TRANSFER_CANCEL_DONE_BMSK                            0x8
#define HWIO_SPI_ERROR_FLAGS_TRANSFER_CANCEL_DONE_SHFT                            0x3
#define HWIO_SPI_ERROR_FLAGS_TRANSFER_CANCEL_ID_MATCH_BMSK                        0x4
#define HWIO_SPI_ERROR_FLAGS_TRANSFER_CANCEL_ID_MATCH_SHFT                        0x2
#define HWIO_SPI_ERROR_FLAGS_SPI_SLV_CLK_OVER_RUN_ERR_BMSK                        0x2
#define HWIO_SPI_ERROR_FLAGS_SPI_SLV_CLK_OVER_RUN_ERR_SHFT                        0x1
#define HWIO_SPI_ERROR_FLAGS_SPI_SLV_CLK_UNDER_RUN_ERR_BMSK                       0x1
#define HWIO_SPI_ERROR_FLAGS_SPI_SLV_CLK_UNDER_RUN_ERR_SHFT                       0x0

#define HWIO_SPI_ERROR_FLAGS_EN_OFFS                                       (REG_BASE_OFFS + 0x0000030c)
#define HWIO_SPI_ERROR_FLAGS_EN_RMSK                                              0xf
#define HWIO_SPI_ERROR_FLAGS_EN_TRANSFER_CANCEL_DONE_EN_BMSK                      0x8
#define HWIO_SPI_ERROR_FLAGS_EN_TRANSFER_CANCEL_DONE_EN_SHFT                      0x3
#define HWIO_SPI_ERROR_FLAGS_EN_TRANSFER_CANCEL_ID_MATCH_EN_BMSK                  0x4
#define HWIO_SPI_ERROR_FLAGS_EN_TRANSFER_CANCEL_ID_MATCH_EN_SHFT                  0x2
#define HWIO_SPI_ERROR_FLAGS_EN_SPI_SLV_CLK_OVER_RUN_ERR_EN_BMSK                  0x2
#define HWIO_SPI_ERROR_FLAGS_EN_SPI_SLV_CLK_OVER_RUN_ERR_EN_SHFT                  0x1
#define HWIO_SPI_ERROR_FLAGS_EN_SPI_SLV_CLK_UNDER_RUN_ERR_EN_BMSK                 0x1
#define HWIO_SPI_ERROR_FLAGS_EN_SPI_SLV_CLK_UNDER_RUN_ERR_EN_SHFT                 0x0

#define HWIO_SPI_DEASSERT_WAIT_OFFS                                        (REG_BASE_OFFS + 0x00000310)
#define HWIO_SPI_DEASSERT_WAIT_RMSK                                              0x3f
#define HWIO_SPI_DEASSERT_WAIT_DEASSERT_WAIT_BMSK                                0x3f
#define HWIO_SPI_DEASSERT_WAIT_DEASSERT_WAIT_SHFT                                 0x0
/***************************************************************************/
#define FLD_BMSK(reg, field) HWIO_##reg##_##field##_BMSK
#define FLD_SHFT(reg, field) HWIO_##reg##_##field##_SHFT

#define REG_IN(base, reg) \
    (*(volatile uint32_t *)(base + HWIO_##reg##_OFFS) & HWIO_##reg##_RMSK)

#define REG_OUT(base, reg, data) \
    (*(volatile uint32_t *)(base + HWIO_##reg##_OFFS)) = data;

#define REG_INF(base, reg, field) \
    ((REG_IN(base, reg) & FLD_BMSK(reg, field)) >> FLD_SHFT(reg, field))

#define REG_OUTF(base, reg, field, data) \
    REG_OUT(base, reg, ((REG_IN(base, reg) & ~(FLD_BMSK(reg, field))) | ((data << FLD_SHFT(reg, field)) & FLD_BMSK(reg, field))))

#define FLD_SET(reg, field, data) \
    (((uint32_t) data << (uint32_t) FLD_SHFT(reg, field)) & (uint32_t) FLD_BMSK(reg, field))

#define FLD_GET(data, reg, field) \
    ((data & FLD_BMSK(reg, field)) >> FLD_SHFT(reg, field))

#endif /* TLMM_H */
