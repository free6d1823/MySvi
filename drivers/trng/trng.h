#ifndef TRNG_H
#define TRNG_H
/**
* @file Trng.h
* @brief TRNG Library Header File.
* This file contains the definitions of the constants, data
* structures, and interfaces that comprise ChipInfo driver.
*
* All Rights Reserved.
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include "com_dtypes.h"
#include "asm/hal/HALhwio.h"

#include "elpclp890_common.h"
#include "elpclp890_hw.h"

#define TIMER_FREQUENCY            0x01312D00
#define TICKS_TO_MICROSECONDS      (TIMER_FREQUENCY / 1000000UL)
/**
Chip Foundry type.
*/
#define  CRYPTO_TOP_BASE0			0xFF60000000uLL
#define  CRYPTO_TOP_BASE1			0xFF60800000uLL

#define  TRNG_ADDRESS_OFF			0x00010000
#define  TRNG_CTRL_OFF				0x00010000
#define  TRNG_MODE_OFF				0x00010004
#define  TRNG_STAT_OFF				0x0001000C

#define  CE_TRNG_CTRL_OFF			0x000B0000
#define  CE_TRNG_CLK_OFF			0x000B0000
#define  CE_TRNG_RST_OFF			0x000B0004


typedef enum{
   HW_CE0,
   HW_CE1
} hw_ce;
/**
  Returns the version of the chip.
*/
int sdk_trng_init(int dev_sel);
int sdk_trng_generate(unsigned long req_num_bytes,boolean load_flag);
int sdk_get_entropy(unsigned long req_num_bytes,boolean load_flag);
int sdk_trng_kat(int dev_sel,int nonce_operation,int sec_length,int pre_resist);
void pdu_io_write (unsigned long addr, unsigned long val);
unsigned long pdu_io_read (unsigned long addr);


#endif /* TRNG_H */
