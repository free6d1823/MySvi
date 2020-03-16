/**---------------------------------------------------------------------------
 * @file     xgmac_platform.c
 *
 * @brief    Platform specific helper functions for 10Gmac.
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * include files
 *--------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <target/heap.h>/*heap_aligned_alloc, free functions*/
#include <target/delay.h> /*udelay*/

#include "xgmac_platform.h"

/*----------------------------------------------------------------------------
 * Definition Files
 *--------------------------------------------------------------------------*/
#define XGMAC_PRINT(...)                                                       \
  printf("Filename %s, Function %s, Line %d >", __FILE__, __FUNCTION__,        \
         __LINE__);                                                            \
  printf(__VA_ARGS__);

bool xgmac_IsBufAligned(void *ptr) {
  if (((uint64_t)ptr & (TX_DESC_ALIGN - 1)) != 0)
    return false;
  else {
    return true;
  }
}

uint64_t xgmac_GetPhyAddr(void *ptr) { return (uint64_t)ptr; }

void xgmac_free(void *p) { heap_free(p); }

/*Need to make sure malloc is ready before using it*/
void *xgmac_AllocBuffer(uint32_t bufSize, uint16_t align)
{
  uintptr_t *ptr = 0;

  ptr = (uintptr_t *)heap_aligned_alloc(align, bufSize);

  if ((align > 0) && ((ptr && (align - 1)) != 0)) {
    XGMAC_PRINT("AllocBuffer alignment failure 0x%llp!!!\r\n", ptr);
  }

  if (ptr != NULL) {
    // bufData->vaddr = (uintptr_t *)ptr;
    // bufData->paddr = (uintptr_t *)ptr;
    // bufData->size = bufSize;
    memset(ptr, 0, bufSize);
  } else {
    ptr = 0;
    XGMAC_PRINT("AllocBuffer fail!!!\r\n");
  }

  return ptr;
}

uint32_t xgmac_configReg_field(uint32_t oldValue, uint8_t field, uint8_t fLen,
                               uint32_t fValue) {
  uint32_t mask, regValue, regFvalue, i;

  if ((fLen + field) > 32) {
    XGMAC_PRINT("Parameter wrong, too big field %d\n", fLen + field);
  }
  regValue = oldValue;
  regFvalue = fValue;
  mask = 1 << field; /*mask has used the first bit, so index starts from 1*/
  regFvalue = 1 << field;
  for (i = 1; i < fLen; i++) {
    mask = mask << 1;
    mask = mask | 1;
  }
  mask = ~mask;

  regValue &= mask;
  regValue |= regFvalue;
  return regValue;
}
/**
 * @brief       Write value into a specific field of the register
 *
 * @param[in]  reg_index    Register ENUM value from xgmac_regs.h
 * @param[in]  queue        Which queue 0 -127
 * @param[in]  field        The least start bit of the 32bits register
 * @param[in]  fLen         How many bits this field occupy
 * @param[in]  fValue       The Field value want to write into
 *
 * notice: No param valid check
 */
void xgmac_regwrite_field(int mac_index, int reg_index, uint8_t queue,
                          uint8_t field, uint8_t fLen, uint32_t fValue)
{
  uint32_t mask, regValue, regFvalue, i;

  if ((fLen + field) > 32 ) {
    XGMAC_PRINT("Parameter wrong, too big field %d\n", fLen + field);
  }
  regValue = XGREG_READ_I(mac_index,reg_index, queue);
  regFvalue= fValue;
  mask     = 1 << field;/*mask has used the first bit, so index starts from 1*/
  regFvalue= 1 << field;
  for (i=1; i<fLen; i++) {
    mask = mask << 1;
    mask = mask | 1;
  }
  mask = ~mask;

  regValue &= mask;
  regValue |= regFvalue;
  XGREG_WRITE_I(mac_index,reg_index, queue, regValue);
}

uint32_t xgmac_regread_field(int mac_index, int reg_index, uint8_t queue,
                          uint8_t field, uint8_t fLen)
{
  uint32_t mask, regValue, regFvalue, i;
  if ((fLen + field) > 32 ) {
    XGMAC_PRINT("Parameter wrong, too big field %d\n", fLen + field);
  }

  regValue = XGREG_READ_I(mac_index,reg_index, queue);
  regFvalue= regValue >> field;
  mask     = 1; /*mask has used the first bit, so index starts from 1*/
  for (i=1; i<fLen; i++) {
    mask = mask << 1;
    mask = mask | 1;
  }

  regFvalue &= mask;

  return regFvalue;
}

/**
 * @brief		Support sleeping for specified number of Milli seconds
 *
 * @param[in]   sleepPeriod in Micor seconds to sleep
 *
 * @return      none
 */
void xgmac_SleepMS(uint32_t sleepPeriod)
{
  udelay(sleepPeriod * 1000);
}