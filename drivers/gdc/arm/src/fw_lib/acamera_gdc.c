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

//needed for gdc/gdc configuration
#include "acamera_gdc_config.h"

//data types and prototypes
#include "acamera_gdc_api.h"

//system_memcpy
#include "system_stdlib.h"
#define FW_LOG_LEVEL LOG_IRQ
#include "system_log.h"


/**
 *   Configure the output gdc configuration address/size and buffer address/size; and resolution.
 *
 *   More than one gdc settings can be accessed by index to a gdc_config_t.
 *
 *   @return 0 - success
 *           -1 - fail.
 */
int acamera_gdc_init( gdc_settings_t *gdc_settings )
{

    gdc_settings->is_waiting_gdc = 0;
    gdc_settings->current_addr = gdc_settings->buffer_addr;

    /*if ( gdc_config_num >= gdc_settings->gdc_config_total || gdc_settings->gdc_config[gdc_config_num].config_addr & 0xFF ) {
        LOG( LOG_ERR, "GDC config number missing or GDC settings misallinged.\n" );
        return -1;
    }*/

    if ( gdc_settings->gdc_config.output_width == 0 || gdc_settings->gdc_config.output_height == 0 ) {
        LOG( LOG_ERR, "Wrong GDC output resolution.\n" );
        return -1;
    }
    //stop gdc
    acamera_gdc_gdc_start_flag_write( gdc_settings->base_gdc, 0 );
    //set the configuration address and size to the gdc block
    acamera_gdc_gdc_config_addr_write( gdc_settings->base_gdc, gdc_settings->gdc_config.config_addr );
    acamera_gdc_gdc_config_size_write( gdc_settings->base_gdc, gdc_settings->gdc_config.config_size );

    //set the gdc in and output resolution
    acamera_gdc_gdc_datain_width_write( gdc_settings->base_gdc, gdc_settings->gdc_config.output_width );
	acamera_gdc_gdc_datain_height_write( gdc_settings->base_gdc, gdc_settings->gdc_config.output_height );
    acamera_gdc_gdc_dataout_width_write( gdc_settings->base_gdc, gdc_settings->gdc_config.output_width );
    acamera_gdc_gdc_dataout_height_write( gdc_settings->base_gdc, gdc_settings->gdc_config.output_height );

    return 0;
}

/**
 *   This function stops the gdc block
 *
 *   @param  gdc_settings - overall gdc settings and state
 *
 */
void acamera_gdc_stop( gdc_settings_t *gdc_settings )
{
    gdc_settings->is_waiting_gdc = 0;
    acamera_gdc_gdc_start_flag_write( gdc_settings->base_gdc, 0 );
}

/**
 *   This function starts the gdc block
 *
 *   Writing 0->1 transition is necessary for trigger
 *
 *   @param  gdc_settings - overall gdc settings and state
 *
 */
void acamera_gdc_start( gdc_settings_t *gdc_settings )
{
    acamera_gdc_gdc_start_flag_write( gdc_settings->base_gdc, 0 ); //do a stop for sync
    acamera_gdc_gdc_start_flag_write( gdc_settings->base_gdc, 1 );
    gdc_settings->is_waiting_gdc = 1;
}


/**
 *   This function points gdc to its input resolution and yuv address and offsets
 *
 *   Shown inputs to GDC are Y and UV plane address and offsets
 *
 *
 *   @return 0 - success
 *           -1 - no interrupt from GDC.
 */

int acamera_gdc_process( gdc_settings_t *gdc_settings, uint32_t num_input, uint32_t * input_addr)
{
    if ( !gdc_settings->is_waiting_gdc ) {
        LOG(LOG_DEBUG,"starting GDC process.\n");
        uint32_t frame_size=0;
        if(num_input==0 || num_input>ACAMERA_GDC_MAX_INPUT){
        	LOG(LOG_CRIT,"GDC number of input invalid %d.\n",num_input);
        	return -1;
        }

        //uint32_t total_planes=0;
		//int index_plane=0;
		/*if(gdc_settings->gdc_config.sequential_mode==1){
			total_planes=1; //do sequential processing by toggling all planes
			index_plane=gdc_settings->seq_planes_pos++;
			if(gdc_settings->seq_planes_pos>=gdc_settings->gdc_config.total_planes)
				gdc_settings->seq_planes_pos=0;
		}else{
			total_planes=gdc_settings->gdc_config.total_planes;
			index_plane=gdc_settings->gdc_config.toggle_planes_pos;
		}*/

		if(num_input<gdc_settings->gdc_config.total_planes){
			LOG(LOG_CRIT,"GDC number of input less than planes %d.\n",num_input);
			return -1;
		}

		uint32_t lineoffset,height;
        //process input addresses
        if(num_input>=1){
        	lineoffset = gdc_settings->gdc_config.output_width;
        	height=gdc_settings->gdc_config.output_height;
        	if(gdc_settings->gdc_config.sequential_mode==1){
        		acamera_gdc_gdc_data1in_addr_write( gdc_settings->base_gdc,input_addr[gdc_settings->seq_planes_pos]);
        		if(gdc_settings->seq_planes_pos>0){ //UV planes
        			lineoffset = gdc_settings->gdc_config.output_width >> gdc_settings->gdc_config.div_width;
        			height = gdc_settings->gdc_config.output_height >> gdc_settings->gdc_config.div_height;
        		}

        	}else{
				acamera_gdc_gdc_data1in_addr_write( gdc_settings->base_gdc,input_addr[0]);
        	}
        	acamera_gdc_gdc_data1in_line_offset_write( gdc_settings->base_gdc, lineoffset );
        	frame_size+=height * lineoffset;
        }
        if(num_input>=2 && gdc_settings->gdc_config.sequential_mode==0){ //only processed if not in toggle mode
        	lineoffset = gdc_settings->gdc_config.output_width >> gdc_settings->gdc_config.div_width;
        	height = gdc_settings->gdc_config.output_height >> gdc_settings->gdc_config.div_height;
        	acamera_gdc_gdc_data2in_addr_write( gdc_settings->base_gdc, input_addr[1]);
        	acamera_gdc_gdc_data2in_line_offset_write( gdc_settings->base_gdc,lineoffset );
        	frame_size+=height * lineoffset;
        }
        if(num_input>=3 && gdc_settings->gdc_config.sequential_mode==0){ //only processed if not in toggle mode
        	lineoffset = gdc_settings->gdc_config.output_width >> gdc_settings->gdc_config.div_width;
        	height = gdc_settings->gdc_config.output_height >> gdc_settings->gdc_config.div_height;
			acamera_gdc_gdc_data3in_addr_write( gdc_settings->base_gdc, input_addr[2]);
			acamera_gdc_gdc_data3in_line_offset_write( gdc_settings->base_gdc, lineoffset );
			frame_size+=height * lineoffset;
		}

        //sanity check for current output address of gdc
        if ( ( gdc_settings->current_addr + frame_size) > ( gdc_settings->buffer_addr + gdc_settings->buffer_size ) || gdc_settings->current_addr < gdc_settings->buffer_addr ) {
			gdc_settings->current_addr = gdc_settings->buffer_addr;
		}

        LOG( LOG_DEBUG, "GDC processing interrupt current_addr:0x%x total_planes:%d index_plane:%d",gdc_settings->current_addr,gdc_settings->gdc_config.total_planes,gdc_settings->seq_planes_pos );

        //outputs
        if(num_input>=1){
        	lineoffset = gdc_settings->gdc_config.output_width;
        	height=gdc_settings->gdc_config.output_height;

        	if(gdc_settings->gdc_config.sequential_mode==1 && gdc_settings->seq_planes_pos>0){ //UV planes
				lineoffset = gdc_settings->gdc_config.output_width >> gdc_settings->gdc_config.div_width;
				height = gdc_settings->gdc_config.output_height >> gdc_settings->gdc_config.div_height;
			}


        	if(( gdc_settings->current_addr + height * lineoffset) > ( gdc_settings->buffer_addr + gdc_settings->buffer_size ) ){
        		LOG(LOG_CRIT,"Input memory not enough for input 1.\n");
        		return -1;
        	}
        	acamera_gdc_gdc_data1out_addr_write( gdc_settings->base_gdc, gdc_settings->current_addr);
        	acamera_gdc_gdc_data1out_line_offset_write( gdc_settings->base_gdc, lineoffset );
        	gdc_settings->current_addr += height * lineoffset;
		}

        if(num_input>=2 && gdc_settings->gdc_config.sequential_mode==0){
        	lineoffset = gdc_settings->gdc_config.output_width >> gdc_settings->gdc_config.div_width;
        	height = gdc_settings->gdc_config.output_height >> gdc_settings->gdc_config.div_height;
        	if(( gdc_settings->current_addr + height * lineoffset) > ( gdc_settings->buffer_addr + gdc_settings->buffer_size ) ){
				LOG(LOG_CRIT,"Input memory not enough for input 2.\n");
				return -1;
			}
			acamera_gdc_gdc_data2out_addr_write( gdc_settings->base_gdc, gdc_settings->current_addr);
			acamera_gdc_gdc_data2out_line_offset_write( gdc_settings->base_gdc, lineoffset );
			gdc_settings->current_addr += height * lineoffset;
		}

        if(num_input>=3 && gdc_settings->gdc_config.sequential_mode==0){
        	lineoffset = gdc_settings->gdc_config.output_width >> gdc_settings->gdc_config.div_width;
        	height = gdc_settings->gdc_config.output_height >> gdc_settings->gdc_config.div_height;
        	if(( gdc_settings->current_addr +height * lineoffset) > ( gdc_settings->buffer_addr + gdc_settings->buffer_size ) ){
				LOG(LOG_CRIT,"Input memory not enough for input 3.\n");
				return -1;
			}
			acamera_gdc_gdc_data3out_addr_write( gdc_settings->base_gdc, gdc_settings->current_addr);
			acamera_gdc_gdc_data3out_line_offset_write( gdc_settings->base_gdc, lineoffset );
			gdc_settings->current_addr += height * lineoffset;
		}

        if(gdc_settings->gdc_config.sequential_mode==1){ //update the planes position
			if(++(gdc_settings->seq_planes_pos)>=gdc_settings->gdc_config.total_planes)
			   gdc_settings->seq_planes_pos=0;
        }

        acamera_gdc_start(gdc_settings);

        return 0;
    } else {
        acamera_gdc_gdc_start_flag_write( gdc_settings->base_gdc, 0 );
        LOG( LOG_CRIT, "No interrupt from GDC block. Still waiting...\n" );
        acamera_gdc_gdc_start_flag_write( gdc_settings->base_gdc, 1 );

        return -1;
    }
}

/**
 *   This function gets the GDC ouput frame addresses and offsets and updates the frame buffer via callback if it is available
 *
 *   Shown ouputs to GDC are Y and UV plane address and offsets
 *
 *
 *   @return 0 - success
 *           -1 - unexpected interrupt from GDC.
 */
int acamera_gdc_get_frame( gdc_settings_t *gdc_settings, uint32_t num_input )
{
    if ( gdc_settings->is_waiting_gdc ) {
        //pass the frame buffer parameters if callback is available
        if ( gdc_settings->get_frame_buffer ) {
        	uint32_t out_addr[num_input];
        	uint32_t out_lineoffset[num_input];

        	if(num_input>=1){
        		out_addr[0]=acamera_gdc_gdc_data1out_addr_read( gdc_settings->base_gdc );
        		out_lineoffset[0]=acamera_gdc_gdc_data1out_line_offset_read( gdc_settings->base_gdc );
        	}
        	if(num_input>=2){
				out_addr[1]=acamera_gdc_gdc_data2out_addr_read( gdc_settings->base_gdc );
				out_lineoffset[1]=acamera_gdc_gdc_data2out_line_offset_read( gdc_settings->base_gdc );
			}
        	if(num_input>=3){
				out_addr[2]=acamera_gdc_gdc_data3out_addr_read( gdc_settings->base_gdc );
				out_lineoffset[2]=acamera_gdc_gdc_data3out_line_offset_read( gdc_settings->base_gdc );
			}


            gdc_settings->get_frame_buffer( num_input, out_addr, out_lineoffset );
        }
        //done of the current frame and stop gdc block
        acamera_gdc_stop(gdc_settings);
        return 0;
    } else {
        LOG( LOG_CRIT, "Unexpected interrupt from GDC.\n" );
        return -1;
    }
}
