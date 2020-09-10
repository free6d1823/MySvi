/*
 * keygen_hw.h
 *
 *  Created on: 2020Äê8ÔÂ12ÈÕ
 *      Author: mingfei.wu
 */

#ifndef KEYGEN_HW_H_
#define KEYGEN_HW_H_

#include "target/crypto_control.h"

#ifdef M4_SMX
#define KEYGEN_BASE                 0x040070000
#endif
#ifdef A76_SMX
#define KEYGEN_BASE                 0x0E3100000
#endif

#define KEYGEN_REG_CTRL             (KEYGEN_BASE + 0x0000)
#define KEYGEN_REG_STAT_SEC         (KEYGEN_BASE + 0x0004)
#define KEYGEN_REG_STAT_NS          (KEYGEN_BASE + 0x0008)
#define KEYGEN_REG_STAT_SMP         (KEYGEN_BASE + 0x000c)
#define KEYGEN_REG_LABEL            (KEYGEN_BASE + 0x0010)
#define KEYGEN_REG_COUNTER          (KEYGEN_BASE + 0x0014)
#define KEYGEN_REG_INT_EN           (KEYGEN_BASE + 0x0018)
#define KEYGEN_REG_INT_RAW          (KEYGEN_BASE + 0x001c)
#define KEYGEN_REG_INT_STAT         (KEYGEN_BASE + 0x0020)
#define KEYGEN_REG_INT_CLR          (KEYGEN_BASE + 0x0024)
#define KEYGEN_REG_SOFTRST          (KEYGEN_BASE + 0x0028)
#define KEYGEN_REG_VF_ALLOC         (KEYGEN_BASE + 0x0030)
#define KEYGEN_REG_VF_FREE          (KEYGEN_BASE + 0x0034)

/* CTRL */
#define KEYGEN_REG_CTRL_GO                  1UL
#define KEYGEN_REG_CTRL_SEC_KEY             0UL
#define KEYGEN_REG_CTRL_NS_KEY              (1UL << 1)
#define KEYGEN_REG_CTRL_SMP_KEY             (1UL << 2)
#define KEYGEN_REG_CTRL_SEED_KEY0           (0UL)
#define KEYGEN_REG_CTRL_SEED_KEY1           (1UL << 3)

/* STAT */
#define KEYGEN_REG_STAT_KEY_READY           1UL

/* IE */
#define _KEYGEN_REG_INT_DONE            0
#define _KEYGEN_REG_INT_ERR             1
#define KEYGEN_REG_INT_DONE_EN          (1 << _KEYGEN_REG_INT_DONE)
#define KEYGEN_REG_INT_ERR_EN           (1 << _KEYGEN_REG_INT_ERR)
#define KEYGEN_REG_INT_DONE             (1 << _KEYGEN_REG_INT_DONE)
#define KEYGEN_REG_INT_ERR              (1 << _KEYGEN_REG_INT_ERR)

#endif /* KEYGEN_HW_H_ */
