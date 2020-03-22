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
/*History:
20200323 Enable multicores support. cj.chang@siengine.com
*/
#include "sys/system_interrupts.h"
#include "sys/system_log.h"

#ifdef USE_SVI
#include <target/irq.h>
#include <target/irqc.h>


/**
 * enum irqreturn
 * @IRQ_NONE            interrupt was not from this device or was not handled
 * @IRQ_HANDLED         interrupt was handled by this device
 * @IRQ_WAKE_THREAD     handler requests to wake the handler thread
 */
enum irqreturn {
        IRQ_NONE                = (0 << 0),
        IRQ_HANDLED             = (1 << 0),
        IRQ_WAKE_THREAD         = (1 << 1),
};

typedef enum irqreturn irqreturn_t;
#define IRQF_TRIGGER_NONE	0x00000000
#define IRQF_TRIGGER_RISING	0x00000001
#define IRQF_TRIGGER_FALLING	0x00000002
#define IRQF_TRIGGER_HIGH	0x00000004
#define IRQF_TRIGGER_LOW	0x00000008
#define IRQF_TRIGGER_MASK	(IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW | \
				 IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)
#define IRQF_TRIGGER_PROBE	0x00000010

#else //LINUX
#include <linux/kernel.h>
#include <linux/interrupt.h>
#endif

typedef enum {
  GDC_IRQ_STATUS_DEINIT = 0,
  GDC_IRQ_STATUS_ENABLED,
  GDC_IRQ_STATUS_DISABLED,
  GDC_IRQ_STATUS_MAX
} irq_status;

#define MAX_GDC_CORES	2
typedef struct dev_info{
	int irq;
	int flags;
	system_interrupt_handler_t app_handler;
	void* app_param;
	irq_status status;
}dev_irq_info;
static dev_irq_info gdc_irq[MAX_GDC_CORES] = {0};

#ifdef USE_SVI
static void svi_interrupt_handler0()
{
	if(gdc_irq[0].app_handler)
		gdc_irq[0].app_handler(gdc_irq[0].app_param, 1);
}
static void svi_interrupt_handler1()
{
	if(gdc_irq[1].app_handler)
		gdc_irq[1].app_handler(gdc_irq[1].app_param, 1);
}

#else //LINUX
static irqreturn_t system_interrupt_handler(int irq, void *dev_id)
{
    int core_id = (int) dev_id;
    LOG(LOG_DEBUG, "GDC core %d: interrupt comes in (irq = %d)", core_id, irq);
    if(core_id < MAX_GDC_CORES && gdc_irq[core_id].app_handler)
	    gdc_irq[core_id].app_handler(gdc_irq[core_id].app_param, 1);

  return IRQ_HANDLED;
}
#endif


void system_interrupts_set_irq(int id, int irq_num, int flags)
{
	if(id < MAX_GDC_CORES) {
        gdc_irq[id].irq = irq_num;
        gdc_irq[id].flags = flags;
        LOG(LOG_INFO, "Set core %d IRQ to %d\n", id, gdc_irq[id].irq);
	}
}

void system_interrupts_init( int id)
{
	int ret = 0;

	if(id >= MAX_GDC_CORES) {
		LOG(LOG_ERR, "system_interrupts_init error: unsupported core id %d", id);
		return;
	}

	if(gdc_irq[id].status != GDC_IRQ_STATUS_DEINIT) {
		LOG(LOG_WARNING, "irq %d is already initied (status = %d)",
		        gdc_irq[id].status);
		return;
	}
	gdc_irq[id].status = GDC_IRQ_STATUS_ENABLED;
 	if(gdc_irq[id].irq >= 0) {
#ifdef USE_SVI
		uint8_t trigger= IRQ_LEVEL_TRIGGERED;
		if (gdc_irq[id].flags & IRQF_TRIGGER_RISING)
            trigger = IRQ_EDGE_TRIGGERED; 
		irqc_configure_irq(gdc_irq[id].irq, 32, trigger);

		if (id == 1) {
			irq_register_vector((sirq_t)gdc_irq[id].irq, svi_interrupt_handler1);
		} else {
			irq_register_vector((sirq_t)gdc_irq[id].irq, svi_interrupt_handler0);		
		}
#else //LINUX
		ret=request_irq(gdc_irq[id].irq, &system_interrupt_handler, gdc_irq[id].flags, "gdc", id);
#endif	  
	    if(ret != 0)
		{
			LOG(LOG_ERR, "Could not get interrupt %d (ret=%d)\n", gdc_irq[id].irq, ret);
		} else {
			LOG(LOG_INFO, "Interrupt %d requested (flags = 0x%x, ret = %d)\n",
	  			gdc_irq[id].irq, gdc_irq[id].flags, ret);
	  }
	}else{
	  LOG(LOG_ERR, "invalid irq id ! (id = %d), please call system_interrupts_set_irq() first\n", gdc_irq[id].irq);
	}
}
void system_interrupt_set_handler(int id, system_interrupt_handler_t handler, void *param )
{
	if(id < MAX_GDC_CORES) {
		gdc_irq[id].app_handler = handler;
		gdc_irq[id].app_param = param;
	}
}

void system_interrupts_deinit( int id )
{
	if(id < MAX_GDC_CORES) {
	    if ( gdc_irq[id].status == GDC_IRQ_STATUS_DEINIT ) {
	        LOG( LOG_WARNING, "irq %d is already deinitied (status = %d)",
	             gdc_irq[id].irq, gdc_irq[id].status );
	    } else {
	        gdc_irq[id].status = GDC_IRQ_STATUS_DEINIT;
#ifdef USE_SVI
			irqc_clear_irq((irq_t)gdc_irq[id].irq );
#else //LINUX
    	    free_irq( gdc_irq[id].irq, NULL );
#endif
        	LOG( LOG_INFO, "Interrupt %d released\n", gdc_irq[id].irq );
			gdc_irq[id].irq = 0;
			gdc_irq[id].flags = 0;
    	}
		gdc_irq[id].app_handler = NULL;
		gdc_irq[id].app_param = NULL;
	}

}

void system_interrupts_enable( int id )
{
    if(gdc_irq[id].status == GDC_IRQ_STATUS_DISABLED) {
        if(gdc_irq[id].irq > 0) {
#ifdef USE_SVI
	        irqc_enable_irq((irq_t) gdc_irq[id].irq);
#else //LINUX
	        enable_irq(gdc_irq[id].irq);
#endif
            gdc_irq[id].status = GDC_IRQ_STATUS_ENABLED;
        }
    }
}

void system_interrupts_disable( int id )
{
    if(gdc_irq[id].status == GDC_IRQ_STATUS_ENABLED) {
        if(gdc_irq[id].irq > 0) {
#ifdef USE_SVI
		    irqc_disable_irq((irq_t) gdc_irq[id].irq);
#else //LINUX
		    disable_irq(gdc_irq[id].irq);
#endif
            gdc_irq[id].status = GDC_IRQ_STATUS_DISABLED;
        }
    }
}
