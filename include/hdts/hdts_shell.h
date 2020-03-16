/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#ifndef __HDTS_SHELL_H__
#define __HDTS_SHELL_H__

#include <stdio.h>
#include <stdint.h>
#include "bits/alltypes.h"
#include <stdbool.h>
#include "hdts_err_code.h"

#define HXT_PARAM_BUFFER_SIZE     256
#define HXT_OUTPUT_BUFFER_SIZE    (10*1024)

#define HDTS_SUCCESS              0
#define HDTS_FAIL                 0x100
#define HDTS_NOT_IMPLEMENTED      0x200

#define HDTS_VERSION_MAJOR        1
#define HDTS_VERSION_MINOR        0
#define HDTS_VERSION_REVISION     1


struct struct_bare_metal_param
{
    int cmd_status;
    char cmd_input[HXT_PARAM_BUFFER_SIZE];
};

extern struct struct_bare_metal_param bare_metal_param;
extern bool HxtBMShell_UART;

#define shell_putch putch
#define shell_puts puts
#define shell_getchar getchar
#define shell_msg printf

void run_shell();

int hdts_hexdump( void *p_peek_location, unsigned long num_bytes, uint8_t data_width );

// for shell history
int history_add_entry( char *cmd, int cmd_len );
unsigned int history_get_num_entries();
int history_get_entry( int which_entry, char *buffer, int buffer_len );

#endif /* __HDTS_SHELL_H__ */
