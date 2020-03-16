/*==============================================================================
 All Rights Reserved.

 ==============================================================================*/

#ifndef __HDTS_INTERRUPT_H__
#define __HDTS_INTERRUPT_H__

#include "bits/alltypes.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define INTERRUPT_LEVEL_TRIGGERED      0x0
#define INTERRUPT_EDGE_TRIGGERED       0x1

typedef void (*HANDLER_FPTR)(void* param);

void imc_interrupt_init(void);

void imc_raise_interrupt(UINT32 interrupt);
void imc_clear_interrupt(UINT32 interrupt);

void imc_enable_interrupt(UINT32 interrupt);
void imc_disable_interrupt(UINT32 interrupt);

UINT32 interrupt_register(UINT32 interrupt, HANDLER_FPTR handler);
UINT32 interrupt_deregister(UINT32 interrupt);

UINT32 interrupt_set_config(UINT32 interrupt, UINT32 trigger_type,
		UINT32 polarity, UINT32 priority);

UINT32 imc_interrupt_status(UINT32 interrupt);

#endif /* __HDTS_INTERRUPT_H__ */

