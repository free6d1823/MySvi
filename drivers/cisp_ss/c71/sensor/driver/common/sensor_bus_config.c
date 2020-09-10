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

#include "sensor_bus_config.h"
#include "acamera_configuration.h"
#include "acamera_logger.h"


uint32_t bus_addr[] = {
    0x7f80a000, 0x7f80b000, 0x7f80c000, 0x7f80d000};


uint32_t get_sensor_bus_address( uint8_t sensor_pos )
{
    if ( sensor_pos < FIRMWARE_CONTEXT_NUMBER ) {
        return bus_addr[sensor_pos];
    } else {
        LOG( LOG_ERR, "Attempt to initialize more sensor instances than was configured." );
        return -1;
    }
}
