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
#define FW_LOG_LEVEL LOG_IRQ

#include "system_log.h"
#include <target/utils.h>

static void *p_hw_base = NULL;

int32_t init_gdc_io( resource_size_t addr , resource_size_t size )
{
    (void) size;
    p_hw_base = (void*) addr;

    if(!p_hw_base){
    	return -1;
    }

    return 0;
}

void close_gdc_io( void )
{
    LOG( LOG_DEBUG, "IO functionality has been closed" );
}

uint32_t system_gdc_read_32( uint32_t addr )
{
    return readl((uintptr_t)addr);
}

void system_gdc_write_32( uint32_t addr, uint32_t data )
{
	writel(data, (uintptr_t)addr);
}

