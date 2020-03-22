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

#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/uio_driver.h>
#include <asm/io.h>

#include "system_log.h"

//entry functions to gdc_main
extern int gdc_fw_init( void );
extern void gdc_fw_exit( void );

//need to set system dependent irq and memory area
extern void system_interrupts_set_irq( int irq_num, int flags );
extern int32_t init_gdc_io( resource_size_t addr , resource_size_t size );


static const struct of_device_id gdc_dt_match[] = {
    {.compatible = "arm,gdc"},
    {}};

MODULE_DEVICE_TABLE( of, gdc_dt_match );

static struct platform_driver gdc_platform_driver = {
    .driver = {
        .name = "arm,gdc",
        .owner = THIS_MODULE,
        .of_match_table = gdc_dt_match,
    },
};

static int32_t gdc_platform_probe( struct platform_device *pdev )
{
    int32_t rc = 0;
    struct resource *gdc_res;

    // Initialize irq
    gdc_res = platform_get_resource_byname( pdev,
                                            IORESOURCE_IRQ, "GDC" );

    if ( gdc_res ) {
        LOG( LOG_INFO, "Juno gdc irq = %d, flags = 0x%x !\n", (int)gdc_res->start, (int)gdc_res->flags );
        system_interrupts_set_irq( gdc_res->start, gdc_res->flags );
    } else {
        LOG( LOG_ERR, "Error, no gdc irq found from DT\n" );
        return -1;
    }


    gdc_res = platform_get_resource( pdev,
    		IORESOURCE_MEM, 0 );
    if(gdc_res){
    	LOG( LOG_INFO, "Juno gdc address = 0x%x, end = 0x%x !\n", (int)gdc_res->start, (int)gdc_res->end );
    	if(init_gdc_io(gdc_res->start,gdc_res->end-gdc_res->start)!=0){
    		LOG( LOG_ERR, "Error on mapping gdc memory! \n" );
    	}
    }else{
    	LOG( LOG_ERR, "Error, no IORESOURCE_MEM DT!\n" );
    }



    gdc_fw_init();

    return rc;
}

static int __init fw_module_init( void )
{
    int32_t rc = 0;

    LOG( LOG_INFO, "Juno gdc fw_module_init\n" );

    rc = platform_driver_probe( &gdc_platform_driver,
                                gdc_platform_probe );


    return rc;
}

static void __exit fw_module_exit( void )
{
    LOG( LOG_ERR, "Juno gdc fw_module_exit\n" );

    gdc_fw_exit();

    platform_driver_unregister( &gdc_platform_driver );
}

module_init( fw_module_init );
module_exit( fw_module_exit );
MODULE_LICENSE( "GPL v2" );
MODULE_AUTHOR( "ARM IVG" );
