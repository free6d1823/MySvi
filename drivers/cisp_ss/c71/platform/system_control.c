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

#include "system_control.h"
#include "system_interrupts.h"
#include "system_isp_io.h"
#include "system_platform.h"
#include "acamera_interrupts.h" // For acamera_interrupt_*
#include "acamera_logger.h"
#include "afbc.h"
#include "afbc_interrupt.h"
//isr_data_t param;
void bsp_init_dv_case()
{
    /* Register access is now ready so we can setup interrupt. */
	int irq_class = 0;
    system_interrupts_set_handler( acamera_interrupt_handler, (void*)&irq_class);
	irq_class = 1;
    system_interrupts_set_handler( afbc_interrupt_handler, (void*)&irq_class);
	system_interrupts_enable();
}
void bsp_init( void )
{
    /* user code goes here. */

    system_platform_init();
    system_isp_init();

    /* Register access is now ready so we can setup interrupt. */
	int irq_class = 0;
    system_interrupts_set_handler( acamera_interrupt_handler, (void*)&irq_class);
	irq_class = 1;
	system_interrupts_set_handler( afbc_interrupt_handler, (void*)&irq_class);
    /* Set up ISP interrupt registers. */
    acamera_interrupt_init();
	/* Set up AFBC inerrupt registers*/
	afbc_interrupt_init();
    /* Set up and enable system interrupts */
    system_interrupts_init();
	//LOG( LOG_INFO, "system interrupt init.");
    /* Only enable interrupts once the system handler is ready. */
    acamera_interrupt_enable();
	/*AFBC interrupt enable*/
	afbc_interrupt_enable();
	//LOG( LOG_INFO, "enable interrupt.");
	system_interrupts_enable();
}

void bsp_destroy( void )
{
    system_interrupts_disable();
    system_interrupts_deinit();
    acamera_interrupt_deinit();

    system_isp_deinit();
    system_platform_deinit();

    /* user code goes here*/
}
