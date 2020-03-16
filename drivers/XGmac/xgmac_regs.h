/**---------------------------------------------------------------------------
 * @file     xgmac_regs.h
 *
 * @brief    xgmac registers
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/
#ifndef __XGMAC_REGS_H__
#define __XGMAC_REGS_H__

struct xgmac_regs {
  volatile uint32_t network_control; /*        0x0 - 0x4        */
  volatile uint32_t network_config;  /*        0x4 - 0x8        */
  volatile uint32_t network_status;  /*        0x8 - 0xc        */
  /*Is pad better than offset?*/
  // volatile char pad__0[0x18];                     /*        0xc - 0x24 */
  volatile uint32_t int_status;  /*       0x24 - 0x28       */
  volatile uint32_t int_enable;  /*       0x28 - 0x2c       */
  volatile uint32_t int_disable; /*       0x2c - 0x30       */
};

struct xgmac_reg_off_def_t {
  uint32_t reg_offset;  /*offset value to the xgmac base address*/
  uint32_t reg_default; /*reset default value to the xgmac regs*/
  uint32_t reg_RW;      /*Read Only: 0x1, Write Only 0x10, RW: 0x11*/
};

enum XGMAC_REG_NAME {
  NETWORK_CONTROL = 0,
  NETWORK_CONFIG,
  NETWORK_STATUS,
  INT_STATUS,
  INT_ENABLE,
  INT_DISABLE,
  PHY_MANAGEMENT,
  PAUSE_TIME,
  PAUSE_QUANTUM,
  JUMBO_MAX_LENGTH,
  NETWORK_CONFIG2,
  PCICR2,
  CTRL,
  LBCTRL,
  MAL,
  MAH,
  RXC,
  INTS,
  TDBAL, // real index is 1068
  TDBAH, // real index is 1068
  TDLEN, // real index is 1068
  TDPI,  /**/
  TDCI,
  RDBAL,
  RDBAH,
  RDLEN,
  RDPI, /**/
  RDCI,
  RCBAL,
  RCBAH,

};

static struct xgmac_reg_off_def_t xgmac_off_def[] = {
    {0x0, 0x0, 0x11},      /*network_control*/
    {0x4, 0x280000, 0x11}, /*network_config*/
    {0x8, 0x4, 0x1},       /*network_Status*/
    {0x24, 0x0, 0x11},     /*Int_Status*/
    {0x28, 0x0, 0x10},     /*Int_enable*/
    {0x2c, 0x0, 0x10},     /*Int_disable*/
    {0x34, 0x0, 0x11},     /*phy_management*/
    {0x38, 0x0, 0x11},     /*Pause_time*/
    {0x3c, 0x0, 0x11},     /*pause quantum*/
    {0x48, 0x2800, 0x11},  /*jumbo_max_length*/
    {0x50, 0x0, 0x11},     /*network_config2, mode_40G*/
    {0x100004, 0x0, 0x11}, /*PCICR2, BME, bus master enable*/
    {0x101000, 0x0,
     0x11}, /*CTRL, pause command, PAU, QSC, used in software reset*/
    {0x101014, 0x0, 0x11}, /*LBCTRL, loopback config*/
    {0x101140, 0x0, 0x11}, /*MAL: mac address low,32bits*/
    {0x101144, 0x0, 0x11}, /*MAH: mac address high, only 16bit valid*/
    {0x101178, 0x0, 0x11}, /*RXC rx configure resiger, HSE, HBS and RBS*/
    {0x800000, 0x0, 0x11}, /*INTS, tx,rx interrupt status check*/
    {0x900000, 0x0, 0x11}, /*TDBAL tx Desc base address low*/
    {0x900200, 0x0, 0x11}, /*TDBAL tx Desc base address high*/
    {0x900400, 0x0, 0x11}, /*TDBAL tx Desc ring length*/
    {0x900600, 0x0,
     0x11}, /*TDPI tx desc producer index, include 128queues, offset = n*4*/
    {0x900800, 0x0,
     0x11}, /*TDCI tx desc consumer index, include 128queues, offset = n*4*/
    {0x901000, 0x0, 0x11}, /*RDBAL rx Desc base address low*/
    {0x901200, 0x0, 0x11}, /*RDBAL rx Desc base address high*/
    {0x901400, 0x0, 0x11}, /*RDBAL rx Desc ring length*/
    {0x901600, 0x0,
     0x11}, /*RDPI rx desc producer index, include 128queues, offset = n*4*/
    {0x901800, 0x0,
     0x11}, /*RDCI rx desc consumer index, include 128queues, offset = n*4*/
    {0x901c00, 0x0,
     0x11}, /*RCBAL rx desc producer index, include 128queues, offset = n*4*/
    {0x901e00, 0x0,
     0x11}, /*RCBAH rx desc consumer index, include 128queues, offset = n*4*/
};

#endif