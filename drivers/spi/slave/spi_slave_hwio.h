#ifndef __SPI_SLAVE_HWIO_H__
#define __SPI_SLAVE_HWIO_H__


/*----------------------------------------------------------------------------
 * MODULE: SPI_SLAVE
 *--------------------------------------------------------------------------*/

#include <asm/mach/hal/msmhwiobase.h>

#define READ_REGISTER32(addr)                   inpdw(addr)

#define WRITE_REGISTER32(addr,mask,value)       outpdw(addr, ((READ_REGISTER32(addr) & mask) | value ))
#define WRITE_ONLY_REGISTER32(addr,value)       outpdw(addr, value )

#define SPI_SLAVE_REG_BASE                                            (PERIPH_SS_BASE      + 0x03400000)

#define HWIO_SPI_SLAVE_SANITY_ADDR                                    (SPI_SLAVE_REG_BASE + 0x00000000)
#define HWIO_SPI_SLAVE_SANITY_RMSK                                    0xffffffff
#define HWIO_SPI_SLAVE_SANITY_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_SANITY_ADDR   , HWIO_SPI_SLAVE_SANITY_RMSK)
#define HWIO_SPI_SLAVE_SANITY_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_SANITY_ADDR   , m)
#define HWIO_SPI_SLAVE_SANITY_SANITY_SEQUENCE_BMSK                    0xffffffff
#define HWIO_SPI_SLAVE_SANITY_SANITY_SEQUENCE_SHFT                           0x0

#define HWIO_SPI_SLAVE_DEVICE_ID_ADDR                                 (SPI_SLAVE_REG_BASE + 0x00000004)
#define HWIO_SPI_SLAVE_DEVICE_ID_RMSK                                 0xfff80000
#define HWIO_SPI_SLAVE_DEVICE_ID_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_DEVICE_ID_ADDR   , HWIO_SPI_SLAVE_DEVICE_ID_RMSK)
#define HWIO_SPI_SLAVE_DEVICE_ID_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_DEVICE_ID_ADDR   , m)
#define HWIO_SPI_SLAVE_DEVICE_ID_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_DEVICE_ID_ADDR   ,v)
#define HWIO_SPI_SLAVE_DEVICE_ID_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_DEVICE_ID_ADDR   ,m,v,HWIO_SPI_SLAVE_DEVICE_ID_IN(x))
#define HWIO_SPI_SLAVE_DEVICE_ID_DEV_FAMILY_BMSK                      0xe0000000
#define HWIO_SPI_SLAVE_DEVICE_ID_DEV_FAMILY_SHFT                            0x1d
#define HWIO_SPI_SLAVE_DEVICE_ID_DENSITY_BMSK                         0x1f000000
#define HWIO_SPI_SLAVE_DEVICE_ID_DENSITY_SHFT                               0x18
#define HWIO_SPI_SLAVE_DEVICE_ID_SUB_CODE_BMSK                          0xc00000
#define HWIO_SPI_SLAVE_DEVICE_ID_SUB_CODE_SHFT                              0x16
#define HWIO_SPI_SLAVE_DEVICE_ID_PROD_REV_BMSK                          0x380000
#define HWIO_SPI_SLAVE_DEVICE_ID_PROD_REV_SHFT                              0x13

#define HWIO_SPI_SLAVE_STATUS_ADDR                                    (SPI_SLAVE_REG_BASE + 0x00000008)
#define HWIO_SPI_SLAVE_STATUS_RMSK                                    0xdff70000
#define HWIO_SPI_SLAVE_STATUS_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_STATUS_ADDR   , HWIO_SPI_SLAVE_STATUS_RMSK)
#define HWIO_SPI_SLAVE_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_STATUS_ADDR   , m)
#define HWIO_SPI_SLAVE_STATUS_SANITY_BMSK                             0x80000000
#define HWIO_SPI_SLAVE_STATUS_SANITY_SHFT                                   0x1f
#define HWIO_SPI_SLAVE_STATUS_INIT_BMSK                               0x40000000
#define HWIO_SPI_SLAVE_STATUS_INIT_SHFT                                     0x1e
#define HWIO_SPI_SLAVE_STATUS_TXUERR_BMSK                             0x10000000
#define HWIO_SPI_SLAVE_STATUS_TXUERR_SHFT                                   0x1c
#define HWIO_SPI_SLAVE_STATUS_RXOERR_BMSK                              0x8000000
#define HWIO_SPI_SLAVE_STATUS_RXOERR_SHFT                                   0x1b
#define HWIO_SPI_SLAVE_STATUS_BERR_BMSK                                0x4000000
#define HWIO_SPI_SLAVE_STATUS_BERR_SHFT                                     0x1a
#define HWIO_SPI_SLAVE_STATUS_WEL_BMSK                                 0x2000000
#define HWIO_SPI_SLAVE_STATUS_WEL_SHFT                                      0x19
#define HWIO_SPI_SLAVE_STATUS_NRDY_BMSK                                0x1000000
#define HWIO_SPI_SLAVE_STATUS_NRDY_SHFT                                     0x18
#define HWIO_SPI_SLAVE_STATUS_CMD_ERR_BMSK                              0x800000
#define HWIO_SPI_SLAVE_STATUS_CMD_ERR_SHFT                                  0x17
#define HWIO_SPI_SLAVE_STATUS_HOST_CTRL_BMSK                            0x400000
#define HWIO_SPI_SLAVE_STATUS_HOST_CTRL_SHFT                                0x16
#define HWIO_SPI_SLAVE_STATUS_ADDR_BYTE_LEN_BMSK                        0x300000
#define HWIO_SPI_SLAVE_STATUS_ADDR_BYTE_LEN_SHFT                            0x14
#define HWIO_SPI_SLAVE_STATUS_WIP_BMSK                                   0x40000
#define HWIO_SPI_SLAVE_STATUS_WIP_SHFT                                      0x12
#define HWIO_SPI_SLAVE_STATUS_DMA_ACT_BMSK                               0x20000
#define HWIO_SPI_SLAVE_STATUS_DMA_ACT_SHFT                                  0x11
#define HWIO_SPI_SLAVE_STATUS_CLK_REQ_PEND_BMSK                          0x10000
#define HWIO_SPI_SLAVE_STATUS_CLK_REQ_PEND_SHFT                             0x10

#define HWIO_SPI_SLAVE_CONFIG_ADDR                                    (SPI_SLAVE_REG_BASE + 0x0000000c)
#define HWIO_SPI_SLAVE_CONFIG_RMSK                                    0x7ffdfc00
#define HWIO_SPI_SLAVE_CONFIG_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_CONFIG_ADDR   , HWIO_SPI_SLAVE_CONFIG_RMSK)
#define HWIO_SPI_SLAVE_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_CONFIG_ADDR   , m)
#define HWIO_SPI_SLAVE_CONFIG_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_CONFIG_ADDR   ,v)
#define HWIO_SPI_SLAVE_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_CONFIG_ADDR   ,m,v,HWIO_SPI_SLAVE_CONFIG_IN(x))
#define HWIO_SPI_SLAVE_CONFIG_INIT_BMSK                               0x40000000
#define HWIO_SPI_SLAVE_CONFIG_INIT_SHFT                                     0x1e
#define HWIO_SPI_SLAVE_CONFIG_ACC_SIZE_BMSK                           0x30000000
#define HWIO_SPI_SLAVE_CONFIG_ACC_SIZE_SHFT                                 0x1c
#define HWIO_SPI_SLAVE_CONFIG_N_DUMMY_BMSK                            0x0F000000
#define HWIO_SPI_SLAVE_CONFIG_N_DUMMY_SHIFT                                 0x18
#define HWIO_SPI_SLAVE_CONFIG_HOST_CTRL_BMSK                            0x800000
#define HWIO_SPI_SLAVE_CONFIG_HOST_CTRL_SHFT                                0x17
#define HWIO_SPI_SLAVE_CONFIG_ADDR_BYTE_LEN_BMSK                        0x600000
#define HWIO_SPI_SLAVE_CONFIG_ADDR_BYTE_LEN_SHFT                            0x15
#define HWIO_SPI_SLAVE_CONFIG_RDBREN_BMSK                               0x100000
#define HWIO_SPI_SLAVE_CONFIG_RDBREN_SHFT                                   0x14
#define HWIO_SPI_SLAVE_CONFIG_WRBREN_BMSK                                0x80000
#define HWIO_SPI_SLAVE_CONFIG_WRBREN_SHFT                                   0x13
#define HWIO_SPI_SLAVE_CONFIG_WPDIS_BMSK                                 0x40000
#define HWIO_SPI_SLAVE_CONFIG_WPDIS_SHFT                                    0x12
#define HWIO_SPI_SLAVE_CONFIG_SEQMOD_BMSK                                0x10000
#define HWIO_SPI_SLAVE_CONFIG_SEQMOD_SHFT                                   0x10
#define HWIO_SPI_SLAVE_CONFIG_CPOL_BMSK                                   0x8000
#define HWIO_SPI_SLAVE_CONFIG_CPOL_SHFT                                      0xf
#define HWIO_SPI_SLAVE_CONFIG_CPHA_BMSK                                   0x4000
#define HWIO_SPI_SLAVE_CONFIG_CPHA_SHFT                                      0xe
#define HWIO_SPI_SLAVE_CONFIG_CORE_DIS_STICKY_BMSK                        0x2000
#define HWIO_SPI_SLAVE_CONFIG_CORE_DIS_STICKY_SHFT                           0xd
#define HWIO_SPI_SLAVE_CONFIG_CORE_DIS_BMSK                               0x1000
#define HWIO_SPI_SLAVE_CONFIG_CORE_DIS_SHFT                                  0xc
#define HWIO_SPI_SLAVE_CONFIG_EXT_BASE_ADDR_LOCK_BMSK                      0x800
#define HWIO_SPI_SLAVE_CONFIG_EXT_BASE_ADDR_LOCK_SHFT                        0xb
#define HWIO_SPI_SLAVE_CONFIG_SPI_ACC_CTRL_BMSK                            0x400
#define HWIO_SPI_SLAVE_CONFIG_SPI_ACC_CTRL_SHFT                              0xa

#define HWIO_SPI_SLAVE_SW_RESET_ADDR                                  (SPI_SLAVE_REG_BASE + 0x00000010)
#define HWIO_SPI_SLAVE_SW_RESET_RMSK                                  0x80000000
#define HWIO_SPI_SLAVE_SW_RESET_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_SW_RESET_ADDR   ,v)
#define HWIO_SPI_SLAVE_SW_RESET_SW_RESET_BMSK                         0x80000000
#define HWIO_SPI_SLAVE_SW_RESET_SW_RESET_SHFT                               0x1f

#define HWIO_SPI_SLAVE_IRQ_STATUS_ADDR                                (SPI_SLAVE_REG_BASE + 0x00000014)
#define HWIO_SPI_SLAVE_IRQ_STATUS_RMSK                                0xf0000000
#define HWIO_SPI_SLAVE_IRQ_STATUS_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_IRQ_STATUS_ADDR   , HWIO_SPI_SLAVE_IRQ_STATUS_RMSK)
#define HWIO_SPI_SLAVE_IRQ_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_IRQ_STATUS_ADDR   , m)
#define HWIO_SPI_SLAVE_IRQ_STATUS_TXREG_UERR_BMSK                     0x80000000
#define HWIO_SPI_SLAVE_IRQ_STATUS_TXREG_UERR_SHFT                           0x1f
#define HWIO_SPI_SLAVE_IRQ_STATUS_TXFIFO_UERR_BMSK                    0x40000000
#define HWIO_SPI_SLAVE_IRQ_STATUS_TXFIFO_UERR_SHFT                          0x1e
#define HWIO_SPI_SLAVE_IRQ_STATUS_RXFIFO_OERR_BMSK                    0x20000000
#define HWIO_SPI_SLAVE_IRQ_STATUS_RXFIFO_OERR_SHFT                          0x1d
#define HWIO_SPI_SLAVE_IRQ_STATUS_HRESPERR_BMSK                       0x10000000
#define HWIO_SPI_SLAVE_IRQ_STATUS_HRESPERR_SHFT                             0x1c

#define HWIO_SPI_SLAVE_IRQ_EN_ADDR                                    (SPI_SLAVE_REG_BASE + 0x00000018)
#define HWIO_SPI_SLAVE_IRQ_EN_RMSK                                    0xf8000000
#define HWIO_SPI_SLAVE_IRQ_EN_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_IRQ_EN_ADDR   , HWIO_SPI_SLAVE_IRQ_EN_RMSK)
#define HWIO_SPI_SLAVE_IRQ_EN_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_IRQ_EN_ADDR   , m)
#define HWIO_SPI_SLAVE_IRQ_EN_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_IRQ_EN_ADDR   ,v)
#define HWIO_SPI_SLAVE_IRQ_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_IRQ_EN_ADDR   ,m,v,HWIO_SPI_SLAVE_IRQ_EN_IN(x))
#define HWIO_SPI_SLAVE_IRQ_EN_TXREG_UERR_IRQ_EN_BMSK                  0x80000000
#define HWIO_SPI_SLAVE_IRQ_EN_TXREG_UERR_IRQ_EN_SHFT                        0x1f
#define HWIO_SPI_SLAVE_IRQ_EN_TXFIFO_UERR_IRQ_EN_BMSK                 0x40000000
#define HWIO_SPI_SLAVE_IRQ_EN_TXFIFO_UERR_IRQ_EN_SHFT                       0x1e
#define HWIO_SPI_SLAVE_IRQ_EN_RXFIFO_OERR_IRQ_EN_BMSK                 0x20000000
#define HWIO_SPI_SLAVE_IRQ_EN_RXFIFO_OERR_IRQ_EN_SHFT                       0x1d
#define HWIO_SPI_SLAVE_IRQ_EN_HRESPERR_IRQ_EN_BMSK                    0x10000000
#define HWIO_SPI_SLAVE_IRQ_EN_HRESPERR_IRQ_EN_SHFT                          0x1c
#define HWIO_SPI_SLAVE_IRQ_EN_SW_RESET_IRQ_EN_BMSK                     0x8000000
#define HWIO_SPI_SLAVE_IRQ_EN_SW_RESET_IRQ_EN_SHFT                          0x1b

#define HWIO_SPI_SLAVE_IRQ_CLR_ADDR                                   (SPI_SLAVE_REG_BASE + 0x0000001c)
#define HWIO_SPI_SLAVE_IRQ_CLR_RMSK                                   0xf0000000
#define HWIO_SPI_SLAVE_IRQ_CLR_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_IRQ_CLR_ADDR   ,v)
#define HWIO_SPI_SLAVE_IRQ_CLR_TXREG_UERR_IRQ_CLR_BMSK                0x80000000
#define HWIO_SPI_SLAVE_IRQ_CLR_TXREG_UERR_IRQ_CLR_SHFT                      0x1f
#define HWIO_SPI_SLAVE_IRQ_CLR_TXFIFO_UERR_IRQ_CLR_BMSK               0x40000000
#define HWIO_SPI_SLAVE_IRQ_CLR_TXFIFO_UERR_IRQ_CLR_SHFT                     0x1e
#define HWIO_SPI_SLAVE_IRQ_CLR_RXFIFO_OERR_IRQ_CLR_BMSK               0x20000000
#define HWIO_SPI_SLAVE_IRQ_CLR_RXFIFO_OERR_IRQ_CLR_SHFT                     0x1d
#define HWIO_SPI_SLAVE_IRQ_CLR_HRESPERR_IRQ_CLR_BMSK                  0x10000000
#define HWIO_SPI_SLAVE_IRQ_CLR_HRESPERR_IRQ_CLR_SHFT                        0x1c

#define HWIO_SPI_SLAVE_IRQ_FORCE_ADDR                                 (SPI_SLAVE_REG_BASE + 0x00000020)
#define HWIO_SPI_SLAVE_IRQ_FORCE_RMSK                                 0xf8000000
#define HWIO_SPI_SLAVE_IRQ_FORCE_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_IRQ_FORCE_ADDR   ,v)
#define HWIO_SPI_SLAVE_IRQ_FORCE_TXREG_UERR_IRQ_FORCE_BMSK            0x80000000
#define HWIO_SPI_SLAVE_IRQ_FORCE_TXREG_UERR_IRQ_FORCE_SHFT                  0x1f
#define HWIO_SPI_SLAVE_IRQ_FORCE_TXFIFO_UERR_IRQ_FORCE_BMSK           0x40000000
#define HWIO_SPI_SLAVE_IRQ_FORCE_TXFIFO_UERR_IRQ_FORCE_SHFT                 0x1e
#define HWIO_SPI_SLAVE_IRQ_FORCE_RXFIFO_OERR_IRQ_FORCE_BMSK           0x20000000
#define HWIO_SPI_SLAVE_IRQ_FORCE_RXFIFO_OERR_IRQ_FORCE_SHFT                 0x1d
#define HWIO_SPI_SLAVE_IRQ_FORCE_HRESPERR_IRQ_FORCE_BMSK              0x10000000
#define HWIO_SPI_SLAVE_IRQ_FORCE_HRESPERR_IRQ_FORCE_SHFT                    0x1c
#define HWIO_SPI_SLAVE_IRQ_FORCE_SW_RESET_IRQ_FORCE_BMSK               0x8000000
#define HWIO_SPI_SLAVE_IRQ_FORCE_SW_RESET_IRQ_FORCE_SHFT                    0x1b

#define HWIO_SPI_SLAVE_TX_ADDR                                        (SPI_SLAVE_REG_BASE + 0x00000024)
#define HWIO_SPI_SLAVE_TX_RMSK                                        0xffffffff
#define HWIO_SPI_SLAVE_TX_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_TX_ADDR   , HWIO_SPI_SLAVE_TX_RMSK)
#define HWIO_SPI_SLAVE_TX_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_TX_ADDR   , m)
#define HWIO_SPI_SLAVE_TX_TX_REG_BMSK                                 0xffffffff
#define HWIO_SPI_SLAVE_TX_TX_REG_SHFT                                        0x0

#define HWIO_SPI_SLAVE_TEST_BUS_DATA_ADDR                             (SPI_SLAVE_REG_BASE + 0x0000002c)
#define HWIO_SPI_SLAVE_TEST_BUS_DATA_RMSK                             0xffffffff
#define HWIO_SPI_SLAVE_TEST_BUS_DATA_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_TEST_BUS_DATA_ADDR   , HWIO_SPI_SLAVE_TEST_BUS_DATA_RMSK)
#define HWIO_SPI_SLAVE_TEST_BUS_DATA_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_TEST_BUS_DATA_ADDR   , m)
#define HWIO_SPI_SLAVE_TEST_BUS_DATA_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_TEST_BUS_DATA_ADDR   ,v)
#define HWIO_SPI_SLAVE_TEST_BUS_DATA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_TEST_BUS_DATA_ADDR   ,m,v,HWIO_SPI_SLAVE_TEST_BUS_DATA_IN(x))
#define HWIO_SPI_SLAVE_TEST_BUS_DATA_TB_DATA_BMSK                     0xffffffff
#define HWIO_SPI_SLAVE_TEST_BUS_DATA_TB_DATA_SHFT                            0x0

#define HWIO_SPI_SLAVE_TEST_BUS_CTRL_ADDR                             (SPI_SLAVE_REG_BASE + 0x00000030)
#define HWIO_SPI_SLAVE_TEST_BUS_CTRL_RMSK                                   0x1f
#define HWIO_SPI_SLAVE_TEST_BUS_CTRL_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_TEST_BUS_CTRL_ADDR   , HWIO_SPI_SLAVE_TEST_BUS_CTRL_RMSK)
#define HWIO_SPI_SLAVE_TEST_BUS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_TEST_BUS_CTRL_ADDR   , m)
#define HWIO_SPI_SLAVE_TEST_BUS_CTRL_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_TEST_BUS_CTRL_ADDR   ,v)
#define HWIO_SPI_SLAVE_TEST_BUS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_TEST_BUS_CTRL_ADDR   ,m,v,HWIO_SPI_SLAVE_TEST_BUS_CTRL_IN(x))
#define HWIO_SPI_SLAVE_TEST_BUS_CTRL_TB_SEL_BMSK                            0x1f
#define HWIO_SPI_SLAVE_TEST_BUS_CTRL_TB_SEL_SHFT                             0x0

#define HWIO_SPI_SLAVE_SW_RST_IRQ_ADDR                                (SPI_SLAVE_REG_BASE + 0x00000034)
#define HWIO_SPI_SLAVE_SW_RST_IRQ_RMSK                                       0x1
#define HWIO_SPI_SLAVE_SW_RST_IRQ_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_SW_RST_IRQ_ADDR   , HWIO_SPI_SLAVE_SW_RST_IRQ_RMSK)
#define HWIO_SPI_SLAVE_SW_RST_IRQ_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_SW_RST_IRQ_ADDR   , m)
#define HWIO_SPI_SLAVE_SW_RST_IRQ_SW_RST_REQ_IRQ_BMSK                        0x1
#define HWIO_SPI_SLAVE_SW_RST_IRQ_SW_RST_REQ_IRQ_SHFT                        0x0

#define HWIO_SPI_SLAVE_CHAR_CFG_ADDR                                  (SPI_SLAVE_REG_BASE + 0x00000038)
#define HWIO_SPI_SLAVE_CHAR_CFG_RMSK                                       0x1f1
#define HWIO_SPI_SLAVE_CHAR_CFG_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_CHAR_CFG_ADDR   , HWIO_SPI_SLAVE_CHAR_CFG_RMSK)
#define HWIO_SPI_SLAVE_CHAR_CFG_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_CHAR_CFG_ADDR   , m)
#define HWIO_SPI_SLAVE_CHAR_CFG_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_CHAR_CFG_ADDR   ,v)
#define HWIO_SPI_SLAVE_CHAR_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_CHAR_CFG_ADDR   ,m,v,HWIO_SPI_SLAVE_CHAR_CFG_IN(x))
#define HWIO_SPI_SLAVE_CHAR_CFG_CHAR_STATUS_BMSK                           0x1e0
#define HWIO_SPI_SLAVE_CHAR_CFG_CHAR_STATUS_SHFT                             0x5
#define HWIO_SPI_SLAVE_CHAR_CFG_DIRECTION_BMSK                              0x10
#define HWIO_SPI_SLAVE_CHAR_CFG_DIRECTION_SHFT                               0x4
#define HWIO_SPI_SLAVE_CHAR_CFG_ENABLE_BMSK                                  0x1
#define HWIO_SPI_SLAVE_CHAR_CFG_ENABLE_SHFT                                  0x0

#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_ADDR                            (SPI_SLAVE_REG_BASE + 0x0000003c)
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_RMSK                                 0xfff
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_CHAR_DATA_MOSI_ADDR   , HWIO_SPI_SLAVE_CHAR_DATA_MOSI_RMSK)
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_CHAR_DATA_MOSI_ADDR   , m)
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_CHAR_DATA_MOSI_ADDR   ,v)
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_CHAR_DATA_MOSI_ADDR   ,m,v,HWIO_SPI_SLAVE_CHAR_DATA_MOSI_IN(x))
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_CHAR_MODE_BMSK                       0xf00
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_CHAR_MODE_SHFT                         0x8
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_DOUT_DATA_DIN_EXP_BMSK                0xff
#define HWIO_SPI_SLAVE_CHAR_DATA_MOSI_DOUT_DATA_DIN_EXP_SHFT                 0x0

#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_ADDR                            (SPI_SLAVE_REG_BASE + 0x00000040)
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_RMSK                                 0xfff
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_CHAR_DATA_CS_N_ADDR   , HWIO_SPI_SLAVE_CHAR_DATA_CS_N_RMSK)
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_CHAR_DATA_CS_N_ADDR   , m)
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_CHAR_DATA_CS_N_ADDR   ,v)
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_CHAR_DATA_CS_N_ADDR   ,m,v,HWIO_SPI_SLAVE_CHAR_DATA_CS_N_IN(x))
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_CHAR_MODE_BMSK                       0xf00
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_CHAR_MODE_SHFT                         0x8
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_DOUT_DATA_DIN_EXP_BMSK                0xff
#define HWIO_SPI_SLAVE_CHAR_DATA_CS_N_DOUT_DATA_DIN_EXP_SHFT                 0x0

#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_ADDR                            (SPI_SLAVE_REG_BASE + 0x00000044)
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_RMSK                               0xfffff
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_CHAR_DATA_MISO_ADDR   , HWIO_SPI_SLAVE_CHAR_DATA_MISO_RMSK)
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_CHAR_DATA_MISO_ADDR   , m)
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_CHAR_DATA_MISO_ADDR   ,v)
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_CHAR_DATA_MISO_ADDR   ,m,v,HWIO_SPI_SLAVE_CHAR_DATA_MISO_IN(x))
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_DATA_OE_BMSK                       0xff000
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_DATA_OE_SHFT                           0xc
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_CHAR_MODE_BMSK                       0xf00
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_CHAR_MODE_SHFT                         0x8
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_DOUT_DATA_DIN_EXP_BMSK                0xff
#define HWIO_SPI_SLAVE_CHAR_DATA_MISO_DOUT_DATA_DIN_EXP_SHFT                 0x0

#define HWIO_SPI_SLAVE_TRNS_BYTE_CNT_ADDR                             (SPI_SLAVE_REG_BASE + 0x0000004c)
#define HWIO_SPI_SLAVE_TRNS_BYTE_CNT_RMSK                             0xffff0000
#define HWIO_SPI_SLAVE_TRNS_BYTE_CNT_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_TRNS_BYTE_CNT_ADDR   , HWIO_SPI_SLAVE_TRNS_BYTE_CNT_RMSK)
#define HWIO_SPI_SLAVE_TRNS_BYTE_CNT_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_TRNS_BYTE_CNT_ADDR   , m)
#define HWIO_SPI_SLAVE_TRNS_BYTE_CNT_BYTE_CNT_BMSK                    0xffff0000
#define HWIO_SPI_SLAVE_TRNS_BYTE_CNT_BYTE_CNT_SHFT                          0x10

#define HWIO_SPI_SLAVE_TRNS_LEN_ADDR                                  (SPI_SLAVE_REG_BASE + 0x00000050)
#define HWIO_SPI_SLAVE_TRNS_LEN_RMSK                                  0xffff0000
#define HWIO_SPI_SLAVE_TRNS_LEN_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_TRNS_LEN_ADDR   , HWIO_SPI_SLAVE_TRNS_LEN_RMSK)
#define HWIO_SPI_SLAVE_TRNS_LEN_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_TRNS_LEN_ADDR   , m)
#define HWIO_SPI_SLAVE_TRNS_LEN_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_TRNS_LEN_ADDR   ,v)
#define HWIO_SPI_SLAVE_TRNS_LEN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_TRNS_LEN_ADDR   ,m,v,HWIO_SPI_SLAVE_TRNS_LEN_IN(x))
#define HWIO_SPI_SLAVE_TRNS_LEN_LENGTH_BMSK                           0xffff0000
#define HWIO_SPI_SLAVE_TRNS_LEN_LENGTH_SHFT                                 0x10

#define HWIO_SPI_SLAVE_FIFO_LEVEL_ADDR                                (SPI_SLAVE_REG_BASE + 0x00000054)
#define HWIO_SPI_SLAVE_FIFO_LEVEL_RMSK                                0xffff0000
#define HWIO_SPI_SLAVE_FIFO_LEVEL_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_FIFO_LEVEL_ADDR   , HWIO_SPI_SLAVE_FIFO_LEVEL_RMSK)
#define HWIO_SPI_SLAVE_FIFO_LEVEL_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_FIFO_LEVEL_ADDR   , m)
#define HWIO_SPI_SLAVE_FIFO_LEVEL_FIFO_LEVEL_BMSK                     0xffff0000
#define HWIO_SPI_SLAVE_FIFO_LEVEL_FIFO_LEVEL_SHFT                           0x10

#define HWIO_SPI_SLAVE_GENERICS_ADDR                                  (SPI_SLAVE_REG_BASE + 0x00000058)
#define HWIO_SPI_SLAVE_GENERICS_RMSK                                  0xc0000000
#define HWIO_SPI_SLAVE_GENERICS_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_GENERICS_ADDR   , HWIO_SPI_SLAVE_GENERICS_RMSK)
#define HWIO_SPI_SLAVE_GENERICS_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_GENERICS_ADDR   , m)
#define HWIO_SPI_SLAVE_GENERICS_BYP_BRIDGE_PARAM_BMSK                 0x80000000
#define HWIO_SPI_SLAVE_GENERICS_BYP_BRIDGE_PARAM_SHFT                       0x1f
#define HWIO_SPI_SLAVE_GENERICS_DIS_ON_PWRUP_PARAM_BMSK               0x40000000
#define HWIO_SPI_SLAVE_GENERICS_DIS_ON_PWRUP_PARAM_SHFT                     0x1e

#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_ADDR                             (SPI_SLAVE_REG_BASE + 0x0000005c)
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_RMSK                              0xfffffff
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_IN(x)      \
        in_dword_masked(HWIO_SPI_SLAVE_EXT_BASE_ADDR_ADDR   , HWIO_SPI_SLAVE_EXT_BASE_ADDR_RMSK)
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_SPI_SLAVE_EXT_BASE_ADDR_ADDR   , m)
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_OUT(x, v)      \
        out_dword(HWIO_SPI_SLAVE_EXT_BASE_ADDR_ADDR   ,v)
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPI_SLAVE_EXT_BASE_ADDR_ADDR   ,m,v,HWIO_SPI_SLAVE_EXT_BASE_ADDR_IN(x))
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_BASE_ADDR_BMSK                    0xfff0000
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_BASE_ADDR_SHFT                         0x10
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_BYTE3_ADDR_BMSK                      0xff00
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_BYTE3_ADDR_SHFT                         0x8
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_BYTE2_ADDR_BMSK                        0xff
#define HWIO_SPI_SLAVE_EXT_BASE_ADDR_BYTE2_ADDR_SHFT                         0x0


#endif /* __SPI_SLAVE_HWIO_H__ */
