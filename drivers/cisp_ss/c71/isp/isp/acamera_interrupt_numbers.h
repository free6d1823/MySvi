//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2019] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

/** @file acamera_interrupt_numbers.h
    @addtogroup   acamera_interrupts ISP Interrupts
    @{
*/
#ifndef __ACAMERA_IRQ_TYPES_H__
#define __ACAMERA_IRQ_TYPES_H__
#include "system_types.h" //stdint
#include "bitop.h"        //BIT


/** Interrupt mask type.
 */
typedef uint32_t system_fw_interrupt_mask_t;

/** Logical interrupts generated from the ISP registers. */
typedef enum {
    ACAMERA_IRQ_BE_FRAME_END,      /**< Triggered by either MCFE or backend output formatter. */
    ACAMERA_IRQ_FE_FRAME_END,      /**< Triggered by front end frame end*/
    ACAMERA_IRQ_FE_FRAME_START,    /**< Triggered by front end frame start. */
    ACAMERA_IRQ_BE_FRAME_START,    /**< Triggered by back end, usually output formatter. */
    ACAMERA_IRQ_AE_STATS,          /**< Triggered by Start of frame front end (for previous slot) */
    ACAMERA_IRQ_AWB_STATS,         /**< Triggered by Start of frame front end (for previous slot)*/
    ACAMERA_IRQ_ANTIFOG_HIST,      /**< Triggered by Start of frame front end (for previous slot)*/
    ACAMERA_IRQ_AE_METERING_STATS, /**< Triggered by Start of frame front end (for previous slot)*/
    ACAMERA_IRQ_ISP,               /**< Triggered by the model.*/
    ACAMERA_IRQ_COUNT              /**< Number of logical interrupts. */
} acamera_irq_t;


#endif /*__ACAMERA_IRQ_TYPES_H__*/
/**@}*/
