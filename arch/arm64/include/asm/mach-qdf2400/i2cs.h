/*
 * =====================================================================================
 *
 *       Filename:  i2cs.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/16/2018 10:16:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  dusc ()
 *
 * =====================================================================================
 */

#ifndef I2CS_H
#define I2CS_H

#include <bits/alltypes.h>
#include <asm/hal/HALhwio.h>
#include <stdbool.h>

#define I2C_S_DEVICE_ADDR_BASE                      (0xff7b000000)
#define I2C_S_DEVICE_ADDR_OFFSET                    (0x100000)
#define I2C_S_DEVICE_REG_OFFSET                     (0x4)
#define I2C_S_DEVICE_ADDR(index) (I2C_S_DEVICE_ADDR_BASE + (index * I2C_S_DEVICE_ADDR_OFFSET))

#define DEVICE                                      (0x00)
#define DEVICE_ID                                   (0x04)
#define IRQ_STATUS                                  (0x08)
#define IRQ_CLR                                     (0x0C)
#define IRQ_EN                                      (0x10)
#define IRQ_FORCE                                   (0x14)
#define CONFIG                                      (0x18)
#define CONTROL                                     (0x1C)
#define FIFOS_STATUS                                (0x20)
#define TX_FIFO                                     (0x24)
#define RX_FIFO                                     (0x28)
#define CORE_VERSION                                (0x2C)
#define CHAR_DATA(n)                                (0x30 + 0x4 * n)
#define CHAR_CFG                                    (0x38)
#define DEBUG_REG1                                  (0x3C)
#define DEBUG_REG2                                  (0x40)
#define SW_RESET_REG                                (0x4C)
#define CLK_LOW_TIMEOUT                             (0x50)
#define CLK_RELEASE_DELAY_CNT_VAL                   (0x54)
#define SDA_HOLD_CNT_VAL                            (0x58)

/* I2C_S_DEVICE_ADDR */
#define I2C_S_DEVICE_MASK                           (0x1FFFF)
#define DEVICE_ADDR_SHIFT                           (0)
#define DEVICE_ADDR_MASK                            (0x3FF)
#define TAB_SHIFT                                   (16)
#define TAB_MASK                                    (0x1)
/* I2C_S_DEVICE_ID */
#define I2C_S_DEVICE_ID_MASK                        (0xFFFFFF)
#define MANUFACTURER_NAME_SHIFT                     (12)
#define MANUFACTURER_NAME_MASK                      (0xFFF)
#define PART_IDENTIFICATION_SHIFT                   (3)
#define PART_IDENTIFICATION_MASK                    (0x01FF)
#define SILICON_REVISION_SHIFT                      (0)
#define SILICON_REVISION_MASK                       (0x07)
/* I2C_S_IRQ_STATUS */
#define I2C_S_IRQ_STATUS_MASK                       (0x3FF)
#define RESTART_DETECTED_SHIFT                      (9)
#define ERR_CONDITION_SHIFT                         (8)
#define GCA_DETECTED_SHIFT                          (7)
#define STRCH_RD_SHIFT                              (6)
#define STRCH_WR_SHIFT                              (5)
#define CLOCK_LOW_TIMEOUT_SHIFT                     (4)
#define RX_DATA_AVAIL_SHIFT                         (3)
#define TX_FIFO_EMPTY_SHIFT                         (2)
#define RX_FIFO_FULL_SHIFT                          (1)
#define STOP_DETECTED_SHIFT                         (0)
/* I2C_S_IRQ_CLR */
#define I2C_S_IRQ_CLR_MASK                          (0x03FF)
/* I2C_S_IRQ_EN */
#define I2C_S_IRQ_EN_MASK                           (0x03FF)
/* I2C_S_IRQ_FORCE */
#define I2C_S_IRQ_FORCE_MASK                        (0x03FF)
/* I2C_S_CONFIG */
#define I2C_S_CONFIG_MASK                           (0x0FF)
#define RX_PACKED_MODE_SHIFT                        (7)
#define TX_PACKED_MODE_SHIFT                        (6)
#define SDA_IN_DELAY_EN_SHIFT                       (5)
#define SPIKE_REJECTION_WIDTH_SHIFT                 (4)
#define GCA_SUPPORTED_SHIFT                         (3)
#define INIT_SHIFT                                  (2)
#define STICKY_DISABLE_SHIFT                        (1)
#define EN_SHIFT                                    (0)
/* I2C_S_CONTROL */
#define I2C_S_CONTROL_MASK                          (0x1F)
#define CONTRX_SHIFT                                (4)
#define ACK_RESUME_SHIFT                            (3)
#define NACK_SHIFT                                  (2)
#define CLEAR_TX_FIFO_SHIFT                         (1)
#define CLEAR_RX_FIFO_SHIFT                         (0)
/* I2C_S_FIFOS_STATUS */
#define I2C_S_FIFOS_STATUS_MASK                     (0xFFFFFFFF)
#define RX_FIFO_BYTES_CNT_SHIFT                     (16)
#define RX_FIFO_BYTES_CNT_MASK                      (0xFFFF)
#define TX_FIFO_BYTES_CNT_SHIFT                     (0)
#define TX_FIFO_BYTES_CNT_MASK                      (0xFFFF)
/* I2C_S_TX_FIFO */
#define TX_FIFO_REG_SHIFT                           (0)
#define TX_FIFO_REG_MASK                            (0xFF)
/* I2C_S_RX_FIFO */
#define RX_FIFO_SHIFT                               (0)
#define I2C_S_RX_FIFO_MASK                          (0xFF)
/* I2C_S_CORE_VERSION */
#define I2C_S_FIFOS_STATUS_MASK                     (0xFFFFFFFF)
#define MAJOR_SHIFT                                 (28)
#define MAJOR_MASK                                  (0xF)
#define MINOR_SHIFT                                 (16)
#define MINOR_MASK                                  (0xFFF)
#define STEP_SHIFT                                  (0)
#define STEP_MASK                                   (0xFFFF)
/* I2C_S_CHAR_DATAn*/
#define I2C_S_CHAR_DATAn_MASK                       (0xFFF)
#define CHAR_MODE_SHIFT                             (8)
#define CHAR_MODE_MASK                              (0xF)
#define DOUT_DATA_DIN_EXP_SHIFT                     (0)
#define DOUT_DATA_DIN_EXP_MASK                      (0xFF)
/* I2C_S_CHAR_CFG */
#define I2C_S_CHAR_CFG_MASK                         (0x1FF)
#define CHAR_STATUS_SHIFT                           (5)
#define CHAR_STATUS_MASK                            (0xF)
#define DIRECTION_SHIFT                             (4)
#define ENABLE_SHIFT                                (0)
/* I2C_S_DEBUG_REG1 */
#define I2C_S_DEBUG_REG1_MASK                       (0x0F)
#define I2C_S_TEST_BUS_SEL_SHIFT                    (2)
#define I2C_S_TEST_BUS_SEL_MASK                     (0x3)
#define AHB2AHB_BRIDGE_TEST_BUS_EN_SHIFT            (0)
#define AHB2AHB_BRIDGE_TEST_BUS_EN_MASK             (0x3)
/* I2C_S_DEBUG_REG2 */
#define I2C_S_DEBUG_REG2_MASK                       (0x1F)
#define FSM_STATE_SHIFT                             (0)
/* I2C_S_SW_RESET_REG*/
#define I2C_S_SW_RESET_REG_MASK                     (0x01)
#define SW_RESET_SHIFT                              (0)
/* I2C_S_CLK_LOW_TIMEOUT */
#define I2C_S_CLK_LOW_TIMEOUT_MASK                  (0xFFFFFFFF)
#define TIMER_MODE_SHIFT                            (30)
#define TIMER_MODE_MASK                             (0x3)
#define TIMEOUT_ACTION_SHIFT                        (29)
#define TIMEOUT_ACTION_MASK                         (0x1)
#define TIMEOUT_VALUE_SHIFT                         (0)
#define TIMEOUT_VALUE_MASK                          (0xFFFFF)
/* I2C_S_CLK_RELEASE_DELAY_CNT_VAL */
#define I2C_S_CLK_RELEASE_DELAY_CNT_VAL_MASK        (0xFFFF)
#define CNT_VALUE_SHIFT                             (0)
#define CNT_VALUE_MASK                              (0xFFFF)
/* I2C_S_SDA_HOLD_CNT_VAL */
#define I2C_S_SDA_HOLD_CNT_VAL_MASK                 (0xFFFF)
#define CNT_VALUE_SHIFT                             (0)
#define CNT_VALUE_MASK                              (0xFFFF)

#define I2C_S_REG_ADDR(num,reg)  (I2C_S_DEVICE_ADDR(num) + reg)

#define SBV(name,value) (value  << name##_SHIFT)
#define SBM(name) (1  << name##_SHIFT)
#define GBV(name,value) ((value >> name##_SHIFT) & 0x1)

#define SFV(name,value) (\
    (value  << name##_SHIFT) & (name##_MASK << name##_SHIFT))

#define SFM(name) (name##_MASK  << name##_SHIFT)
#define GFV(name,value) ((value  >> name##_SHIFT) & name##_MASK)

#define _SET_WORD(port,val) __outpdw(port, val)
#define _GET_WORD(port) __inpdw(port)

#define I2C_S_SVRW(index,reg,name,val)  ({ \
    uint32_t _value;\
    uint32_t _val;\
    uint32_t _mask;\
    _mask = ~SBM(name); \
    _val = SBV(name,val); \
    _value = _GET_WORD(I2C_S_REG_ADDR(index,reg)); \
    _value &= _mask; \
    _val &= SBM(name);\
    _value |= _val; \
    _value &= I2C_S_##reg##_MASK; \
    _SET_WORD(I2C_S_REG_ADDR(index,reg),_value);\
})

#define I2C_S_SET_ADDR(index,val)  ({ \
    uint32_t _value;\
    uint32_t _val;\
    uint32_t _mask;\
    _mask = ~SFM(DEVICE_ADDR); \
    _val = SFV(DEVICE_ADDR,val); \
    _value = _GET_WORD(I2C_S_REG_ADDR(index,DEVICE)); \
    _value &= _mask; \
    _val &= SFM(DEVICE_ADDR);\
    _value |= _val; \
    _value &= I2C_S_DEVICE_MASK; \
    _SET_WORD(I2C_S_REG_ADDR(index,DEVICE),_value);\
})

#define I2C_S_SBWO(index,reg,name,val)  ({ \
    uint32_t _val;\
    uint32_t _mask;\
    _mask = SBM(name);\
    _val = SBV(name,val);\
    _val &= _mask; \
    _SET_WORD(I2C_S_REG_ADDR(index,reg),_val);\
})

#define I2C_S_SBV(addr,name,val)  ({ \
    _SET_WORD(addr,val << name##_SHIFT);\
})

#define I2C_S_GBV(addr,reg,name)  ({ \
    uint32_t _value;\
    _value = _GET_WORD(addr); \
    _value &= I2C_S_##reg##_MASK; \
    GBV(name,_value); \
})

#define I2C_S_GFV(addr,reg,name)  ({ \
    uint32_t _value;\
    _value = _GET_WORD(addr); \
    _value &= I2C_S_##reg##_MASK; \
    GFV(name,_value);\
})

/* for wo reg,can not be read */
#define I2C_S_SPV(index,reg,val)  ({ \
    uint32_t _val;\
    _val = val; \
    _val &= I2C_S_##reg##_MASK; \
    _SET_WORD(I2C_S_REG_ADDR(index,reg),_val);\
})

#define I2C_S_GPV(index,reg)  ({ \
    uint32_t _value;\
    _value = _GET_WORD(I2C_S_REG_ADDR(index,reg)); \
    _value &= I2C_S_##reg##_MASK; \
})

#define I2C_S_TX(index,val)  ({ \
    _SET_WORD(I2C_S_REG_ADDR(index,TX_FIFO),((val) & 0xFF));\
})
#define I2C_S_RX(addr)  ({ \
    _GET_WORD(addr); \
})

#define GMASK(name)  (SBM(name))

/***********************************************************/

#define I2CS_CONFIG_NUM_CORES 4
#define I2CS_CONFIG_NUM_GPIOS 2

/* for GPIO */
#define I2C_S_TLMM_BASE 0xff02000000uLL
#define I2C_S_TLMM_CSR_REG_BASE   (I2C_S_TLMM_BASE + 0x00010000)
#define I2C_S_HWIO_TLMM_GPIO_CFGn_ADDR(n) \
    (I2C_S_TLMM_CSR_REG_BASE + 0x00000000 + 0x10000 * (n))
#define I2C_S_TLMM_GPIO_CFGn_MASK                   (0x7FF)
#define I2C_S_GPIO_HIHYS_EN_SHIFT                   (10)
#define I2C_S_GPIO_HIHYS_EN_MASK                    (0x1)
#define I2C_S_GPIO_OE_SHIFT                         (9)
#define I2C_S_GPIO_OE_MASK                          (0x1)
#define I2C_S_DRV_STRENGTH_SHIFT                    (6)
#define I2C_S_DRV_STRENGTH_MASK                     (0x7)
#define I2C_S_FUNC_SEL_SHIFT                        (2)
#define I2C_S_FUNC_SEL_MASK                         (0xF)
#define I2C_S_GPIO_PULL_SHIFT                       (0)
#define I2C_S_GPIO_PULL_MASK                        (0x3)

typedef struct {
    uint32_t devid;
    uint32_t gpios[I2CS_CONFIG_NUM_GPIOS];
    uint32_t irq;
    uint32_t slave_addr;
    uint64_t block_addr;
} i2cs_config_t;

extern i2cs_config_t i2cs_configs[];

typedef struct {
    i2cs_config_t           *config;     // Target-specific config structure
    uint32_t                 uDevId;     // DAL Device ID
    uint32_t                 coreIdx;    // Which core in i2cs_config.h
}I2CS_Device;

void I2CS_AddDevice(int uDevId);

#endif /* I2CS_H */
