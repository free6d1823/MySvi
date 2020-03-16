#ifndef __XGMAC_PLATFORM_H__
#define __XGMAC_PLATFORM_H__

/**---------------------------------------------------------------------------
 * @file     xgmac_platform.h
 *
 * @brief    Header file to abstract platform specific differences
 * help function
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include "xgmac_regs.h"
#include "asm/hal/HALhwio.h"

#define RX_DESC_ALIGN 16 // confirm which kind of align
#define TX_DESC_ALIGN 16 // confirm which kind of align

/*xgmac base address*/
static uint64_t xgmac_base[] = {0xFFA0000000, /*Use macro in the future*/
                                0xFFA1ef0000};

#define XGREG_READ_I(mac_index, reg_index, queue)                              \
  in_dword(xgmac_base[mac_index] + xgmac_off_def[reg_index].reg_offset +       \
           4 * queue)

#define XGREG_READ(mac_index, reg_index)                                       \
  in_dword(xgmac_base[mac_index] + xgmac_off_def[reg_index].reg_offset)

#define XGREG_WRITE_I(mac_index, reg_index, queue, val)                        \
  out_dword((xgmac_base[mac_index] + xgmac_off_def[reg_index].reg_offset +     \
             4 * queue),                                                       \
            val)

#define XGREG_WRITE(mac_index, reg_index, val)                                 \
  out_dword((xgmac_base[mac_index] + xgmac_off_def[reg_index].reg_offset), val)

void *xgmac_AllocBuffer(uint32_t bufSize, uint16_t align);

void xgmac_free(void *p);

uint64_t xgmac_GetPhyAddr(void *ptr);
bool xgmac_IsBufAligned(void *ptr);
uint32_t xgmac_configReg_field(uint32_t oldValue, uint8_t field, uint8_t fLen,
                               uint32_t fValue);
void xgmac_regwrite_field(int mac_index, int reg_index, uint8_t queue,
                          uint8_t field, uint8_t fLen, uint32_t fValue);
uint32_t xgmac_regread_field(int mac_index, int reg_index, uint8_t queue,
                          uint8_t field, uint8_t fLen);
void xgmac_SleepMS(uint32_t sleepPeriod);

#endif