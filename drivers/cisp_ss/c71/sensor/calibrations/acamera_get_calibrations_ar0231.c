/*
*
* SPDX-License-Identifier: GPL-2.0
*
* Copyright (C) 2011-2019 ARM or its affiliates
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

#include "acamera_command_api.h"
#include "acamera_logger.h"

extern int32_t get_calibrations_static_linear_ar0231( void *param );
extern int32_t get_calibrations_dynamic_linear_ar0231( void *param );
extern int32_t get_calibrations_static_fs_lin_ar0231( void *param );
extern int32_t get_calibrations_dynamic_fs_lin_ar0231( void *param );
extern int32_t get_calibrations_static_native_ar0231( void *param );
extern int32_t get_calibrations_dynamic_native_ar0231( void *param );

int32_t get_calibrations_ar0231( uint32_t wdr_mode, void *param )
{
    int32_t ret = 0;
    // Logic to choose which calibration to apply.
    switch ( wdr_mode ) {
    //case WDR_MODE_NATIVE:
    //    LOG( LOG_DEBUG, "Calibration switching to WDR_MODE_NATIVE %d.", (int)wdr_mode );
    //    ret += ( get_calibrations_dynamic_native_ar0231( param ) + get_calibrations_static_native_ar0231( param ) );
    //    break;
    case WDR_MODE_LINEAR:
        LOG( LOG_DEBUG, "Calibration switching to WDR_MODE_LINEAR %d.", (int)wdr_mode );
        ret += ( get_calibrations_dynamic_linear_ar0231( param ) + get_calibrations_static_linear_ar0231( param ) );
        break;
    //case WDR_MODE_FS_HDR:
    //    //case WDR_MODE_NATIVE:
    //    LOG( LOG_DEBUG, "Calibration switching to WDR_MODE_FS_HDR %d.", (int)wdr_mode );
    //    //ret += ( get_calibrations_dynamic_wdr_ar0231( c ) + get_calibrations_static_wdr_ar0231( c ) );
    //    break;
    //case WDR_MODE_FS_LIN:
    //    LOG( LOG_DEBUG, "Calibration switching to WDR mode on mode %d.", (int)wdr_mode );
    //    ret += ( get_calibrations_dynamic_fs_lin_ar0231( param ) + get_calibrations_static_fs_lin_ar0231( param ) );
    //    break;
    //default:
    //    LOG( LOG_DEBUG, "Calibration switching to WDR_MODE_LINEAR %d.", (int)wdr_mode );
    //    ret += ( get_calibrations_dynamic_linear_ar0231( param ) + get_calibrations_static_linear_ar0231( param ) );
    //    break;
    }

    return ret;
}

int32_t get_calibrations_dummy_ar0231( uint32_t wdr_mode, void *param )
{
    return get_calibrations_ar0231( wdr_mode, param );
}
