/*
*
* SPDX-License-Identifier: GPL-2.0
*
* Copyright (C) 2011-2018 ARM or its affiliates
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 2.
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#ifndef __SYSTEM_INTERRUPTS_H__
#define __SYSTEM_INTERRUPTS_H__

#include "system_stdlib.h"

//interrupt handler prototype
typedef void ( *system_interrupt_handler_t )( void *ptr, uint32_t mask );


/**
 *   Initialize system interrupts
 *
 *   This function initializes system dependent interrupt functionality
 *
 *   @return none
 */
void system_interrupts_init( int id);


/**
 *   Remove system interrupts
 *
 *   This function clean the system dependent interrupt
 *
 *   @return none
 */
void system_interrupts_deinit( int id );

/**
 *   Set an interrupt handler
 *
 *   This function is used by application to set an interrupt handler for all GDC related interrupt events.
 *
 *   @param
 *          handler - a callback to handle interrupts
 *          param - pointer to a context which must be send to interrupt handler
 *
 *   @return none
 */
void system_interrupt_set_handler( int id, system_interrupt_handler_t handler, void *param );

/**
 *   Set IRQ number
 *
 *   This function is used by application to set an interrupt handler for all GDC related interrupt events.
 *
 *   @param
 *          id - GDC core number
 *          irq_num - irq number
 *          flags - irq trigger flags 
 *
 *   @return none
 */
void system_interrupts_set_irq(int id, int irq_num, int flags);

/**
 *   Enable system interrupts
 *
 *   This function is used by firmware to enable system interrupts in a case if they were disabled before
 *
 *   @return none
 */
void system_interrupts_enable( int id );


/**
 *   Disable system interrupts
 *
 *   This function is used by firmware to disable system interrupts for a short period of time.
 *   Usually IRQ register is updated by new interrupts but main interrupt handler is not called by a system.
 *
 *   @return none
 */
void system_interrupts_disable( int id );

#endif /* __SYSTEM_INTERRUPTS_H__ */
