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

#include "system_interrupts.h"
#include "acamera_logger.h"
#include <target/irq.h>
irq_t c71_irq = C71_0_IRQ(0);
irq_t afbc_irq = AFBC_ENC_IRQ;
#define C71_CORE 0
int system_interrupts_init( void )
{
    return 0;
}

void system_interrupts_set_handler( system_interrupts_handler_t handler, void *param )
{
	int irq_class = (int)(*(int*)param);
	if (irq_class == 0)
		irq_register_vector(c71_irq, (irq_handler)handler, param);
	else if(irq_class == 1)
		irq_register_vector(afbc_irq, (irq_handler)handler, param);
	else
	{
		LOG( LOG_LEVEL_ERROR, "irq class error.");
	}
}

void system_interrupts_enable()
{
	irqc_configure_irq(c71_irq, 32, IRQ_LEVEL_TRIGGERED);
	irqc_enable_irq(c71_irq);
	irqc_configure_irq(afbc_irq, 32, IRQ_LEVEL_TRIGGERED);
	irqc_enable_irq(afbc_irq);
}

void system_interrupts_enable_c71(void )
{
	//irqc_configure_irq(c71_irq, 32, IRQ_LEVEL_TRIGGERED);
	//irqc_enable_irq(c71_irq);
}
void system_interrupts_disable( void )
{
	irqc_disable_irq(c71_irq);
}

void system_interrupts_deinit( void )
{
}
