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

#if !defined( __ACAMERA_CONNECTION_H__ )
#define __ACAMERA_CONNECTION_H__

#include "acamera_control_config.h"

#define BUS_ERROR_RESET -1
#define BUS_ERROR_FATAL -2

void acamera_connection_init( void );
void acamera_connection_process( void );
void acamera_connection_destroy( void );
uint32_t acamera_read( uint8_t cmd, uint8_t cmd_type, uint32_t *data );
uint32_t acamera_write( uint8_t cmd, uint8_t cmd_type, uint32_t data );

typedef int32_t ( *slot_done_callback )( uint32_t slot_id, void *user_data );

#endif /* __ACAMERA_CONNECTION_H__ */
