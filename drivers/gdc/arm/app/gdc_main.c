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
#include "acamera_driver_config.h"
#include "system_interrupts.h"
#include "system_control.h"
#include "system_stdlib.h"
#include "system_log.h"

//gdc api functions
#include "acamera_gdc_api.h"

#if HAS_FPGA_WRAPPER
//fpga related functions
#include "acamera_fpga.h"
#endif

#define TEST_CASE 1
struct _gdc_test_param{
	const unsigned char * gdc_sequence;
	uint32_t gdc_sequence_size;
	uint32_t total_planes;
	uint32_t input_addresses[ACAMERA_GDC_MAX_INPUT];
	uint8_t  sequential_mode;
	uint8_t  div_width; //use in dividing UV dimensions; actually a shift right
	uint8_t  div_height; //use in dividing UV dimensions; actually a shift right
};

//gdc configuration sequences
#if (TEST_CASE==1)
#include "gdc_rgb444_256x256_seq.h"
struct _gdc_test_param gdc_test_param = {
		.gdc_sequence=rgb444_256x256_seq, //gdc_sequence
		.gdc_sequence_size=sizeof(rgb444_256x256_seq),
		.total_planes=3, 		//total_planes
		.input_addresses={0x1000000, 0x2000000,0x3000000},//input_addresses
		.sequential_mode=0, 		//plane_sequential_processing
		.div_width=0, 		//div_width
		.div_height=0 		//div_height
};
#elif (TEST_CASE==2)
#include "gdc_yuv420plan_256x256_seq.h"
struct _gdc_test_param gdc_test_param = {
		.gdc_sequence=yuv420plan_256x256_seq, //gdc_sequence
		.gdc_sequence_size=sizeof(yuv420plan_256x256_seq),
		.total_planes=3, 		//total_planes
		.input_addresses={0x1000000, 0x2000000,0x3000000},//input_addresses
		.sequential_mode=0, 		//plane_sequential_processing
		.div_width=1, 		//div_width
		.div_height=1 		//div_height

};
#else
#include "gdc_yuv420semi_256x256_seq.h"
struct _gdc_test_param gdc_test_param = {
		.gdc_sequence=yuv420semi_256x256_seq, //gdc_sequence
		.gdc_sequence_size=sizeof(yuv420semi_256x256_seq),
		.total_planes=2, 		//total_planes
		.input_addresses={0x1000000, 0x2000000},//input_addresses
		.sequential_mode=0, 		//plane_sequential_processing
		.div_width=0, 		//div_width
		.div_height=1 		//div_height

};
#endif


//This is a function callback provided to GDC to update frame buffer addresses and offsets
static void get_frame_buffer_callback(  uint32_t total_input, uint32_t * out_addr, uint32_t * out_lineoffset )
{
#if HAS_FPGA_WRAPPER
    //call frame reader to display
	acamera_fpga_update_frame_reader(total_input,out_addr,out_lineoffset);
#endif
}


//this is the main interrupt handler, for demo purposes gdc status and data are currently not passed
static void interrupt_handler( void *param, uint32_t mask )
{
    //handle the start of frame with acamera_gdc_process
    gdc_settings_t *gdc_settings = (gdc_settings_t *)param;

    //gdc block has finished processing
    if ( mask ) { //can filter mask
        //gdc will save the new frame reader settings
        //will update the frame reader settings via callback

        if ( acamera_gdc_get_frame( gdc_settings,gdc_test_param.total_planes ) != 0 ) {
        	return;
        }

#if HAS_FPGA_WRAPPER
        //get gdc buffer input from fpga writer output
        uint32_t in_addr[gdc_test_param.total_planes];
        uint32_t in_lineoffset[gdc_test_param.total_planes];
        if(acamera_fpga_get_frame_writer( gdc_test_param.total_planes,in_addr,in_lineoffset )!=0){
			LOG( LOG_CRIT, "Cannot get frame_writer_addresses" );
		}else if( acamera_gdc_process( gdc_settings, gdc_test_param.total_planes,in_addr ) != 0 ) {
			LOG( LOG_CRIT, "GDC missed an interrupt" );
		}

#else
        if ( acamera_gdc_process( gdc_settings,gdc_test_param.total_planes, gdc_test_param.input_addresses) != 0 ) {
			LOG( LOG_CRIT, "GDC missed an interrupt" );
		}
#endif

    }
}

//we need to copy the gdc configuration sequence to the gdc config address
uint32_t gdc_load_settings_to_memory( uint32_t * config_mem_start, uint32_t *config_settings_start, uint32_t config_size )
{
    uint32_t i = 0;
    system_memcpy( config_mem_start, config_settings_start, config_size * 4 );
    for ( i = 0; i < config_size; i++ ) {
        if ( config_mem_start[i] != config_settings_start[i] ) {
            LOG( LOG_CRIT, "GDC config mismatch index %ld, values %lX vs %lX\n", i, config_mem_start[i], config_settings_start[i] );
            return 0;
        }
    }

    return config_size * 4;
}

// The basic example of usage gdc is given below.
int gdc_fw_init( void )
{

    static gdc_settings_t gdc_settings;

    // The custom platform must be ready to run
    // any system routines from ./platform folder.
    // So bsp_init allows to initialise the system if necessary.
    // This function may be omitted if no initialisation is required
    bsp_init();
    system_interrupts_disable();
    //configure gdc config, buffer address and resolution
    gdc_settings.base_gdc = 0;
    gdc_settings.buffer_addr = 0x8000000;
    gdc_settings.buffer_size = 256*256*gdc_test_param.total_planes;
    gdc_settings.get_frame_buffer = get_frame_buffer_callback;
    gdc_settings.current_addr = gdc_settings.buffer_addr;
    gdc_settings.seq_planes_pos = 0;
    gdc_settings.ddr_mem = system_ddr_mem_init(); //opaque pointer to memory and system dependent
    acamera_gdc_stop( &gdc_settings );

    //set the gdc config
    gdc_settings.gdc_config.config_addr = 0x4000;
    gdc_settings.gdc_config.config_size = gdc_test_param.gdc_sequence_size / 4; //size of configuration in 4bytes
    gdc_settings.gdc_config.output_width = 256;
    gdc_settings.gdc_config.output_height = 256;
    gdc_settings.gdc_config.total_planes = gdc_test_param.total_planes;
    gdc_settings.gdc_config.sequential_mode=gdc_test_param.sequential_mode;
    gdc_settings.gdc_config.div_width = gdc_test_param.div_width;
    gdc_settings.gdc_config.div_height = gdc_test_param.div_height;

    uint32_t memory_used = gdc_load_settings_to_memory( (uint32_t *)((uintptr_t)gdc_settings.ddr_mem + gdc_settings.gdc_config.config_addr) , (uint32_t *)gdc_test_param.gdc_sequence, gdc_settings.gdc_config.config_size );
    if ( memory_used != gdc_settings.gdc_config.config_size * 4 ) {
        //memory config for gdc ifnitialization failed
        LOG( LOG_CRIT, "memory config for gdc initialization 1 failed" );
        return -1;
    }
    LOG( LOG_INFO, "Done gdc load..\n");

#if HAS_FPGA_WRAPPER
    //fpga initialization with resolution and intended buffers for dma writer output
    //YUV 420 demo
    uint32_t in_lineoffset[]={gdc_settings.gdc_config.output_width,gdc_settings.gdc_config.output_width};
    if ( acamera_fpga_init( gdc_settings.gdc_config.output_width,gdc_settings.gdc_config.output_height,gdc_settings.gdc_config.total_planes,gdc_test_param.input_addresses,in_lineoffset) != 0 ) {
		LOG( LOG_ERR, "Wrong initialisation parameters for fpga reader block" );
		return -1;
	}
#endif

    //initialise the gdc by the first configuration
    if ( acamera_gdc_init( &gdc_settings ) != 0 ) {
        LOG( LOG_ERR, "Failed to initialise GDC block" );
        return -1;
    }

    LOG( LOG_INFO, "Done gdc config..\n" );

    // set the interrupt handler. The last parameter may be used
    // to specify the context. The system must call this interrupt_handler
    // function whenever the interrupt happens.
    // This interrupt handling procedure is only advisable and is used in demo application.
    // It can be changed by a customer discretion.
    system_interrupt_set_handler( interrupt_handler, &gdc_settings );

    //enable the interrupts
    system_interrupts_enable();

    //start gdc process

    acamera_gdc_process( &gdc_settings,gdc_test_param.total_planes, gdc_test_param.input_addresses);

    return 0;
}


int gdc_fw_exit( void )
{

    bsp_destroy();
    return 0;
}
