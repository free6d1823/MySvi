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

#include "system_interrupts.h"
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include "system_log.h"

typedef enum {
  GDC_IRQ_STATUS_DEINIT = 0,
  GDC_IRQ_STATUS_ENABLED,
  GDC_IRQ_STATUS_DISABLED,
  GDC_IRQ_STATUS_MAX
} irq_status;

static system_interrupt_handler_t app_handler = NULL ;
static void* app_param = NULL ;
static int interrupt_line_ACAMERA_JUNO_IRQ = -1;
static int interrupt_line_ACAMERA_JUNO_IRQ_FLAGS = -1;
static irq_status interrupt_request_status = GDC_IRQ_STATUS_DEINIT;


static irqreturn_t system_interrupt_handler(int irq, void *dev_id)
{

  LOG(LOG_DEBUG, "interrupt comes in (irq = %d) dev_id: %p %p", irq, dev_id, app_param);
  if(app_handler){
	if(interrupt_line_ACAMERA_JUNO_IRQ >= 0){
		if(irq==interrupt_line_ACAMERA_JUNO_IRQ)
			app_handler( app_param, 1  ) ;
	}
  }

  return IRQ_HANDLED;
}

void system_interrupts_set_irq(int irq_num, int flags)
{
  interrupt_line_ACAMERA_JUNO_IRQ = irq_num;
  interrupt_line_ACAMERA_JUNO_IRQ_FLAGS = flags & IRQF_TRIGGER_MASK;
  LOG(LOG_INFO, "interrupt id is set to %d\n", interrupt_line_ACAMERA_JUNO_IRQ);
}

void system_interrupts_init( void )
{
  int ret = 0;

  if(interrupt_request_status != GDC_IRQ_STATUS_DEINIT) {
    LOG(LOG_WARNING, "irq %d is already initied (status = %d)",
      interrupt_line_ACAMERA_JUNO_IRQ, interrupt_request_status);
    return;
  }
  interrupt_request_status = GDC_IRQ_STATUS_ENABLED;
  if(interrupt_line_ACAMERA_JUNO_IRQ >= 0) {
	  // No dev_id for now, but will need this to be shared
	  if((ret=request_irq(interrupt_line_ACAMERA_JUNO_IRQ,
		  &system_interrupt_handler, interrupt_line_ACAMERA_JUNO_IRQ_FLAGS, "gdc", NULL))) { //get proper name for device later
		LOG(LOG_ERR, "Could not get interrupt %d (ret=%d)\n", interrupt_line_ACAMERA_JUNO_IRQ, ret);
	  } else {
		LOG(LOG_INFO, "Interrupt %d requested (flags = 0x%x, ret = %d)\n",
		  interrupt_line_ACAMERA_JUNO_IRQ, interrupt_line_ACAMERA_JUNO_IRQ_FLAGS, ret);
	  }
  }else{
	  LOG(LOG_ERR, "invalid irq id ! (id = %d), ISR maybe comming from another module\n", interrupt_line_ACAMERA_JUNO_IRQ);
  }
}

void system_interrupts_deinit( void )
{

    if ( interrupt_request_status == GDC_IRQ_STATUS_DEINIT ) {
        LOG( LOG_WARNING, "irq %d is already deinitied (status = %d)",
             interrupt_line_ACAMERA_JUNO_IRQ, interrupt_request_status );
    } else {
        //interrupt_request_status = GDC_IRQ_STATUS_DISABLED;
        interrupt_request_status = GDC_IRQ_STATUS_DEINIT;
        // No dev_id for now, but will need this to be shared
        free_irq( interrupt_line_ACAMERA_JUNO_IRQ, NULL );
        LOG( LOG_INFO, "Interrupt %d released\n", interrupt_line_ACAMERA_JUNO_IRQ );
    }
    app_handler = NULL;
    app_param = NULL;
}


void system_interrupt_set_handler( system_interrupt_handler_t handler, void *param )
{
  app_handler = handler ;
  app_param = param;
}

void system_interrupts_enable( void )
{
    if(interrupt_request_status == GDC_IRQ_STATUS_DISABLED) {
	if(interrupt_line_ACAMERA_JUNO_IRQ >= 0)
		enable_irq(interrupt_line_ACAMERA_JUNO_IRQ);
    interrupt_request_status = GDC_IRQ_STATUS_ENABLED;
  }
}

void system_interrupts_disable( void )
{
  if(interrupt_request_status == GDC_IRQ_STATUS_ENABLED) {
	if(interrupt_line_ACAMERA_JUNO_IRQ >= 0)
		disable_irq(interrupt_line_ACAMERA_JUNO_IRQ);
    interrupt_request_status = GDC_IRQ_STATUS_DISABLED;
  }
}
