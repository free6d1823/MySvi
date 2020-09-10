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

#include "system_isp_io.h"
#include "system_types.h"
#include "acamera_configuration.h"
#include "acamera_control_config.h"
#include "acamera_logger.h"
#include "acamera_math.h"

#if defined( ISP_HAS_ANALYTIX_FSM )
#include "av.h"
#endif

#if ISP_HAS_CONNECTION_BUFFER
#define ALIGNMENT_MASK 3
#include "acamera_cmd_queues_config.h"
#include "acamera_connection_buffer_manager.h"
#define CMD_QUEUES_HALF_WORD_INX ( ACAMERA_CMD_QUEUES_SIZE >> 3 )
#elif ISP_HAS_CONNECTION_UART
#define ALIGNMENT_MASK 0
#include "acamera_uart.h"
#endif // ISP_HAS_CONNECTION_BUFFER

#if ISP_HAS_CONNECTION_SOCKET
#include "acamera_socket.h"
#include "acamera_socket_inet_strategy.h"
extern struct acamera_socket_strategy acamera_socket_init_strategy();
#define ALIGNMENT_MASK 0
#endif

#include "acamera_command_api.h"
#include "application_command_api.h"

#if ISP_HAS_CONNECTION_BUFFER

#ifndef MIN
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif
typedef struct {
    uint32_t id;
    uint32_t data; // actual data or detailled error code

    union {
        // Parsed values of ACT_CMD_FIELD:
        struct {
            uint32_t cmd_type : 8; // as in application_command( cmd_type, cmd, value, COMMAND_GET, &value );
            uint32_t cmd : 8;
            uint32_t status : 8;
            uint32_t req_type : 8; // One of API_READ, API_WRITE, API_RESET
        };
        uint32_t cmd_field;
    };
} acamera_api_request_t;

typedef struct {
    union {
        // Parsed values of ACT_ACK_CMD_FIELD:
        struct {
            uint32_t acked_req_type : 8; // One of API_READ, API_WRITE, API_RESET
            uint32_t unused : 8;
            uint32_t status : 8;
            uint32_t unused_2 : 8;
        };
        uint32_t ack_cmd_field;
    };

    uint32_t id;
    uint32_t data; // actual data or detailled error code
} acamera_api_ack_t;

static acamera_buffer_manager_t buff_mgr = {0};

#endif // ISP_HAS_CONNECTION_BUFFER

#ifdef TRACE
/* This printf library call put there intentionally to debug the connection
 * on the limited subset of the supported architectures
 * bypassing project loglevel settings.
 */
#define ACAMERA_CONNECTION_TRACE printf
#else
#define ACAMERA_CONNECTION_TRACE( ... )
#endif // TRACE

enum {
    API_RESET = 0,
    API_READ,
    API_WRITE
};

enum TransactionType {
    TransactionTypeRegRead = 1,
    TransactionTypeRegWrite,
    TransactionTypeRegMaskWrite,
    TransactionTypeLUTRead,
    TransactionTypeLUTWrite,

    TransactionTypeAPIRead = 10,
    TransactionTypeAPIWrite,

    TransactionTypeBUFRead = 20,
    TransactionTypeBUFWrite
};

typedef int ( *data_read_f )( void *p_ctrl, uint8_t *data, int size );
typedef int ( *data_write_f )( void *p_ctrl, const uint8_t *data, int size );

enum {
    STATE_IDLE,
    STATE_RX_DATA,
    STATE_SKIP_DATA,
    STATE_TX_PACKET
};

typedef struct {
    void *param;
    data_read_f data_read;
    data_write_f data_write;
    int state;
    uint8_t buffer[CONNECTION_BUFFER_SIZE];
    uint32_t rx_buffer_inx;
    uint32_t rx_buffer_size;
    uint32_t tx_buffer_inx;
    uint32_t tx_buffer_size;
} acamera_socket_connection_t;

// sizeof(.) == 12
typedef struct {
    uint32_t total_size;
    uint32_t id;

    uint16_t type;
    uint16_t padding;
} acamera_socket_packet_header_t;

typedef struct {
    acamera_socket_packet_header_t header;

    union {
        // TransactionTypeRegRead/Write, TransactionTypeRegMaskWrite, TransactionTypeLUTRead/Write:
        struct {
            uint32_t offset;
            uint32_t size;
        } lut_reg_rw;

        // TransactionTypeAPIRead/Write
        struct {
            uint8_t cmd_type;
            uint8_t cmd;
            uint32_t value;
        } api_rw;

        // TransactionTypeBUFRead/Write
        struct {
            uint8_t id;
            uint8_t type;
            uint32_t size;
        } calibration_rw;
    } metadata;

    uint8_t data[];
} acamera_socket_input_packet_t;

typedef struct {
    acamera_socket_packet_header_t header;

    uint32_t status;

    uint8_t data[];
} acamera_socket_output_packet_t;

typedef union {
    acamera_socket_input_packet_t in;
    acamera_socket_output_packet_t out;
} acamera_socket_packet_t;

#if ISP_HAS_STREAM_CONNECTION
static acamera_socket_connection_t con;

static void reset_connection( void )
{
    con.state = STATE_IDLE;
    con.rx_buffer_inx = 0;
    con.tx_buffer_inx = 0;
    ACAMERA_CONNECTION_TRACE( "Reset connection" );
}
#endif // ISP_HAS_STREAM_CONNECTION

#if ISP_HAS_CONNECTION_BUFFER

// Both acamera_api_request_t and acamera_api_ack_t have the same size, 12 bytes
// The layout of the structure corresponds to the layout in memory
static void receive_api_request_and_ack( acamera_api_request_t *req, acamera_api_ack_t *ack )
{
    req->cmd_field = acamera_cmd_queues_array_data_read( PHY_ADDR_ISP, 2 );
    ack->ack_cmd_field = acamera_cmd_queues_array_data_read( PHY_ADDR_ISP, CMD_QUEUES_HALF_WORD_INX );

    req->id = acamera_cmd_queues_array_data_read( PHY_ADDR_ISP, 0 );
    req->data = acamera_cmd_queues_array_data_read( PHY_ADDR_ISP, 1 );
}

static void send_api_request_and_ack( acamera_api_request_t *req, const acamera_api_ack_t *ack )
{
    acamera_cmd_queues_array_data_write( PHY_ADDR_ISP, CMD_QUEUES_HALF_WORD_INX + 1, ack->id );
    acamera_cmd_queues_array_data_write( PHY_ADDR_ISP, CMD_QUEUES_HALF_WORD_INX + 2, ack->data );
    acamera_cmd_queues_array_data_write( PHY_ADDR_ISP, CMD_QUEUES_HALF_WORD_INX + 0, ack->ack_cmd_field );

    acamera_cmd_queues_array_data_write( PHY_ADDR_ISP, 2, req->cmd_field );
}

#endif // ISP_HAS_CONNECTION_BUFFER

#if ISP_HAS_CONNECTION_SOCKET
static int acamera_socket_do_init( acamera_socket_connection_t *con )
{
    struct acamera_socket *socket;
    int rc;


    /* f = acamera_socket_f_impl();
    if ( !f ) {
        LOG( LOG_ERR, "Please double check your platform provide TCP/IP socket routines" );
        return -1;
    }
*/
    socket = acamera_socket_instance();


    rc = acamera_socket_init( socket, acamera_socket_inet_strategy() );
    if ( rc )
        return rc;

    con->param = socket;
    con->data_read = (data_read_f)acamera_socket_read;
    con->data_write = (data_write_f)acamera_socket_write;

    return 0;
}
#endif

void acamera_connection_init( void )
{
#if ISP_HAS_STREAM_CONNECTION
    reset_connection();
#if ISP_HAS_CONNECTION_BUFFER
    acamera_api_request_t req = {0};
    acamera_api_ack_t ack = {0};

    acamera_buffer_manager_init( &buff_mgr, ACAMERA_CMD_QUEUES_BASE_ADDR, ACAMERA_CMD_QUEUES_SIZE / 2 );
    LOG( LOG_INFO, "acamera connection Init." );
    con.param = &buff_mgr;
    con.data_read = (data_read_f)acamera_buffer_manager_read;
    con.data_write = (data_write_f)acamera_buffer_manager_write;

    req.req_type = API_RESET;
    ack.acked_req_type = API_RESET;

    send_api_request_and_ack( &req, &ack );

    ACAMERA_CONNECTION_TRACE( "Connection is buffer" );

#elif ISP_HAS_CONNECTION_SOCKET
    if ( !acamera_socket_do_init( &con ) ) {
        ACAMERA_CONNECTION_TRACE( "Connection is TCP/IP socket" );
    } else {
        LOG( LOG_ERR, "Unable to initialise TCP/IP socket" );
    }
#endif

    if ( !con.data_read || !con.data_write ) {
        LOG( LOG_WARNING, "Connection method is not defined" );
    }
#endif // ISP_HAS_STREAM_CONNECTION
}

void acamera_connection_destroy( void )
{
#if ISP_HAS_STREAM_CONNECTION
    con.param = NULL;
    con.data_read = NULL;
    con.data_write = NULL;
#endif
}

#if ISP_HAS_STREAM_CONNECTION
static void write_8( uint32_t addr, uint8_t value )
{
    int shift = ( addr & 3 ) << 3;
    uint32_t mask = 0xFF << shift;
    uint32_t addr_align = addr & ~3;
    uint32_t data = system_isp_read_32( PHY_ADDR_ISP + addr_align );

    data = ( data & ~mask ) | ( (uint32_t)value << shift );
    system_isp_write_32( PHY_ADDR_ISP + addr_align, data );
}

static bool check_request_reg_offset_range( uint32_t offset, uint32_t size )
{
    uint32_t end_offset = offset + size;
    return end_offset <= LEN_ADDR_ISP && offset <= end_offset;
}

static uint32_t process_request( void )
{
    acamera_socket_packet_t *packet = (acamera_socket_packet_t *)con.buffer;

    // Max packet sizes, for read and writes. We check max_write_size is not "negative" further below.
    static const uint32_t max_read_size = CONNECTION_BUFFER_SIZE - sizeof( acamera_socket_output_packet_t );
    uint32_t max_write_size = packet->in.header.total_size - sizeof( acamera_socket_input_packet_t );

    // Temporary variables
    uint16_t type = packet->in.header.type;
    bool has_extra_data;
    uint32_t offset, size, value, i;
    uint8_t cmdtype, cmd, id, buf_class;

    // Note: if the input is truncated, only the header is sent back...
    // Note: STATE_IDLE set rx_buffer_size to packet->in.header.total_size
    ACAMERA_CONNECTION_TRACE( "Processing packet size %u, id %u, type %u\n", packet->in.header.total_size, packet->in.header.id, type );

    // Check if the packet may contain extra data. If it doesn't, the maximum allowed size of the packet is sizeof(acamera_socket_input_packet_t), also the minimum.
    has_extra_data = type == TransactionTypeRegWrite || type == TransactionTypeRegMaskWrite || type == TransactionTypeLUTWrite || type == TransactionTypeBUFWrite;

    // Check the minimum size of the input packet, and the maximum size allowed by the protcol:
    if ( packet->in.header.total_size < sizeof( acamera_socket_input_packet_t ) || ( !has_extra_data && packet->in.header.total_size > sizeof( acamera_socket_input_packet_t ) ) ) {
        LOG( LOG_WARNING, "Wrong packet size %u for type %u.", (unsigned int)con.rx_buffer_size, (unsigned int)type );
        con.state = STATE_TX_PACKET;
        con.tx_buffer_inx = 0;
        con.tx_buffer_size = sizeof( acamera_socket_packet_header_t );
        packet->out.header.total_size = sizeof( acamera_socket_packet_header_t );
        return packet->out.header.total_size;
    }

    // Set output packet minimum size. Note that this overwrites packet->in.header.total_packet_size and packet->in.total_packet_size...
    packet->out.header.total_size = sizeof( acamera_socket_output_packet_t );

    // Setting output packet status overwrites input metadata fields, so we must parse them first.

    switch ( type ) {
    case TransactionTypeRegRead:
        offset = packet->in.metadata.lut_reg_rw.offset;
        size = packet->in.metadata.lut_reg_rw.size;
        if ( size <= max_read_size && check_request_reg_offset_range( offset, size ) ) {
            packet->out.header.total_size += size;
            packet->out.status = SUCCESS;
            uint8_t *b = packet->out.data;
            while ( size-- ) {
                *b++ = system_isp_read_8( PHY_ADDR_ISP + offset++ );
            }
        } else {
            packet->out.status = FAIL;
            LOG( LOG_WARNING, "Wrong request size %u for type %u.", (unsigned int)size, (unsigned int)type );
        }
        break;
    case TransactionTypeRegWrite:
        offset = packet->in.metadata.lut_reg_rw.offset;
        size = packet->in.metadata.lut_reg_rw.size;
        if ( size <= max_write_size && check_request_reg_offset_range( offset, size ) ) {
            packet->out.status = SUCCESS;
            uint8_t *b = packet->in.data;
            while ( size-- ) {
                write_8( offset++, *b++ );
            }
        } else {
            packet->out.status = FAIL;
            LOG( LOG_WARNING, "Wrong request size %u for type %u.", (unsigned int)size, (unsigned int)type );
        }
        break;
    case TransactionTypeRegMaskWrite:
        offset = packet->in.metadata.lut_reg_rw.offset;
        size = packet->in.metadata.lut_reg_rw.size;
        if ( 2 * size <= max_write_size && check_request_reg_offset_range( offset, 2 * size ) ) {
            packet->out.status = SUCCESS;
            uint8_t *b = packet->out.data;
            uint8_t *mask = packet->out.data + size;
            while ( size-- ) {
                uint8_t m = *mask++;
                write_8( offset, ( system_isp_read_8( PHY_ADDR_ISP + offset ) & ~m ) | ( m & *b++ ) );
                offset++;
            }
        } else {
            packet->out.status = FAIL;
            LOG( LOG_WARNING, "Wrong request size %u for type %u.", (unsigned int)size, (unsigned int)type );
        }
        break;
    case TransactionTypeLUTRead:
        offset = packet->in.metadata.lut_reg_rw.offset;
        size = packet->in.metadata.lut_reg_rw.size;
        if ( size <= max_read_size && !( size & 3 ) && !( offset & 3 ) && check_request_reg_offset_range( offset, size ) ) {
            packet->out.header.total_size += size;
            packet->out.status = SUCCESS;
            uint32_t *b = (uint32_t *)packet->out.data;
            for ( i = 0; i < size; i += 4 ) {
                system_isp_write_32( PHY_ADDR_ISP + offset, i >> 2 );
                *b++ = system_isp_read_32( PHY_ADDR_ISP + offset + 8 );
            }
        } else {
            packet->out.status = FAIL;
            LOG( LOG_WARNING, "Wrong request size %u for type %u.", (unsigned int)size, (unsigned int)type );
        }
        break;
    case TransactionTypeLUTWrite:
        offset = packet->in.metadata.lut_reg_rw.offset;
        size = packet->in.metadata.lut_reg_rw.size;
        if ( size <= max_write_size && !( size & 3 ) && !( offset & 3 ) && check_request_reg_offset_range( offset, size ) ) {
            packet->out.status = SUCCESS;
            uint32_t *b = (uint32_t *)packet->in.data;
            for ( i = 0; i < size; i += 4 ) {
                system_isp_write_32( PHY_ADDR_ISP + offset, i >> 2 );
                system_isp_write_32( PHY_ADDR_ISP + offset + 4, *b++ );
            }
        } else {
            packet->out.status = FAIL;
            LOG( LOG_WARNING, "Wrong request size %u for type %u.", (unsigned int)size, (unsigned int)type );
        }
        break;
    case TransactionTypeAPIRead:
        cmdtype = packet->in.metadata.api_rw.cmd_type;
        cmd = packet->in.metadata.api_rw.cmd;
        value = packet->in.metadata.api_rw.value;
        packet->out.header.total_size += 4;
        packet->out.status = application_command( cmdtype, cmd, value, COMMAND_GET, (uint32_t *)packet->out.data );
        break;
    case TransactionTypeAPIWrite:
        cmdtype = packet->in.metadata.api_rw.cmd_type;
        cmd = packet->in.metadata.api_rw.cmd;
        value = packet->in.metadata.api_rw.value;
        packet->out.header.total_size += 4; // FIXME: explain why? Shouldn't we discard the result?
        packet->out.status = application_command( cmdtype, cmd, value, COMMAND_SET, (uint32_t *)packet->out.data );
        break;
    case TransactionTypeBUFRead:
        id = packet->in.metadata.calibration_rw.id;
        buf_class = packet->in.metadata.calibration_rw.type;
        size = packet->in.metadata.calibration_rw.size;
        if ( size <= max_read_size ) {
            switch ( buf_class ) {
            case STATIC_CALIBRATIONS_ID:
            case DYNAMIC_CALIBRATIONS_ID:
                packet->out.status = application_api_calibration( buf_class, id, COMMAND_GET, packet->out.data, size, &value );
                if ( packet->out.status == SUCCESS ) {
                    packet->out.header.total_size += size;
                }
                break;
            case FILE_TRANSFER_ID:
            default:
                packet->out.status = FAIL;
                LOG( LOG_WARNING, "Wrong buffer class %u.", (unsigned int)buf_class );
            }
        } else {
            packet->out.status = FAIL;
            LOG( LOG_WARNING, "Wrong request size %u for type %u.", (unsigned int)size, (unsigned int)type );
        }
        break;
    case TransactionTypeBUFWrite:
        id = packet->in.metadata.calibration_rw.id;
        buf_class = packet->in.metadata.calibration_rw.type;
        size = packet->in.metadata.calibration_rw.size;
        if ( size <= max_read_size ) {
            switch ( buf_class ) {
            case STATIC_CALIBRATIONS_ID:
            case DYNAMIC_CALIBRATIONS_ID:
                packet->out.status = application_api_calibration( buf_class, id, COMMAND_SET, packet->in.data, size, &value );
                break;
            case FILE_TRANSFER_ID:
            default:
                packet->out.status = FAIL;
                LOG( LOG_WARNING, "Wrong buffer class %d.", buf_class );
            }
        } else {
            packet->out.status = FAIL;
            LOG( LOG_WARNING, "Wrong request size %u for type %u.", (unsigned int)size, (unsigned int)type );
        }
        break;
    default:
        packet->out.header.total_size = sizeof( acamera_socket_packet_header_t ); // no output
        LOG( LOG_WARNING, "Wrong packet type %d.", type );
    }

    return packet->out.header.total_size;
}

#endif // ISP_HAS_STREAM_CONNECTION

#if ISP_HAS_CONNECTION_BUFFER

static void send_api_response( acamera_api_request_t *req, acamera_api_ack_t *ack, uint32_t status, uint32_t data )
{
    ack->id = req->id;
    ack->acked_req_type = req->req_type;
    ack->status = status;
    ack->data = data;
    req->req_type = API_RESET;
    req->status = 0;
    send_api_request_and_ack( req, ack );
}

static void process_api_request( void )
{
    acamera_api_request_t req;
    acamera_api_ack_t ack;

    receive_api_request_and_ack( &req, &ack );

    uint32_t status;
    uint32_t data;

    switch ( req.req_type ) {
    case API_READ:
        if ( ack.acked_req_type == API_RESET ) {
            status = application_command( (uint8_t)req.cmd_type, (uint8_t)req.cmd, req.data, COMMAND_GET, &data );
            if ( ( status != SUCCESS ) && ( status != NOT_SUPPORTED ) && ( status != NOT_IMPLEMENTED ) ) {
                LOG( LOG_ERR, "Error at cmd: 0x%x, value: %d, status: %d.", req.cmd, req.data, status );
            }
            send_api_response( &req, &ack, status, data );
        }
        break;
    case API_WRITE:
        if ( ack.acked_req_type == API_RESET ) {
            status = application_command( (uint8_t)req.cmd_type, (uint8_t)req.cmd, req.data, COMMAND_SET, &data );
            if ( ( status != SUCCESS ) && ( status != NOT_SUPPORTED ) && ( status != NOT_IMPLEMENTED ) ) {
                LOG( LOG_ERR, "Error at cmd: %d, value: %d, status: %d.", req.cmd, req.data, status );
            }
            send_api_response( &req, &ack, status, data );
        }
        break;
    case API_RESET:
        break;
    default:
        LOG( LOG_ERR, "Wrong request %u.", req.req_type );
        data = ERR_BAD_ARGUMENT;
        status = FAIL;
        send_api_response( &req, &ack, status, data );
        break;
    }
}

#endif // ISP_HAS_CONNECTION_BUFFER

void process_socket_request( void )
{
#if ISP_HAS_STREAM_CONNECTION
    int res = 0;
    int cnt = 20;
    uint32_t *const buf = (uint32_t *)con.buffer;

    if ( !con.data_read || !con.data_write ) {
        return;
    }

    do {
        switch ( con.state ) {
        case STATE_IDLE:
            res = con.data_read( con.param, &con.buffer[con.rx_buffer_inx], sizeof( acamera_socket_packet_header_t ) - con.rx_buffer_inx );
            if ( res != 0 )
                ACAMERA_CONNECTION_TRACE( "State %d res %d\n", con.state, res );
            if ( res < 0 ) {
                reset_connection();
                return;
            }
            con.rx_buffer_inx += res;
            if ( con.rx_buffer_inx >= sizeof( acamera_socket_packet_header_t ) ) {
                con.rx_buffer_size = buf[0];
                if ( con.rx_buffer_size > CONNECTION_BUFFER_SIZE ) {
                    reset_connection();
                    LOG( LOG_WARNING, "Too big request %u, maximum allowed %u.", (unsigned int)con.rx_buffer_size, (unsigned int)CONNECTION_BUFFER_SIZE );
                    con.state = STATE_SKIP_DATA;
                } else {
                    con.state = STATE_RX_DATA;
                }
            }
            break;
        case STATE_SKIP_DATA:
            res = con.data_read(
                con.param,
                &con.buffer[sizeof( acamera_socket_packet_header_t )],
                MIN( CONNECTION_BUFFER_SIZE - sizeof( acamera_socket_packet_header_t ), con.rx_buffer_size - con.rx_buffer_inx ) );
            if ( res != 0 )
                ACAMERA_CONNECTION_TRACE( "State %d res %d\n", con.state, res );
            if ( res < 0 ) {
                reset_connection();
                return;
            }
            con.rx_buffer_inx += res;
            if ( con.rx_buffer_inx >= con.rx_buffer_size ) {
                con.tx_buffer_size = sizeof( acamera_socket_packet_header_t );
                *buf = con.tx_buffer_size;
                con.tx_buffer_inx = 0;
                con.state = STATE_TX_PACKET;
            }
            break;
        case STATE_RX_DATA:
            res = con.data_read( con.param, &con.buffer[con.rx_buffer_inx], con.rx_buffer_size - con.rx_buffer_inx );
            if ( res != 0 )
                ACAMERA_CONNECTION_TRACE( "State %d res %d\n", con.state, res );
            if ( res < 0 ) {
                reset_connection();
                return;
            }
            con.rx_buffer_inx += res;
            if ( con.rx_buffer_inx >= con.rx_buffer_size ) {
                uint32_t sz = process_request();
                con.tx_buffer_size = ( sz + ALIGNMENT_MASK ) & ~ALIGNMENT_MASK;
                con.tx_buffer_inx = 0;
                con.state = STATE_TX_PACKET;
            }
            break;
        case STATE_TX_PACKET:
            res = con.data_write( con.param, &con.buffer[con.tx_buffer_inx], con.tx_buffer_size - con.tx_buffer_inx );
            if ( res != 0 )
                ACAMERA_CONNECTION_TRACE( "State %d res %d\n", con.state, res );
            if ( res < 0 ) {
                reset_connection();
                return;
            }
            con.tx_buffer_inx += res;
            if ( con.tx_buffer_inx >= con.tx_buffer_size ) {
                ACAMERA_CONNECTION_TRACE( "Packet size %ld is transferred\n", con.tx_buffer_size );
                reset_connection();
                return; // This will make sure that FW itself will work as required.
            }
            break;
        default:
            res = -1;
            LOG( LOG_CRIT, "Wrong state %d", con.state );
            reset_connection();
            return;
        }
    } while ( res > 0 && --cnt );
#endif // ISP_HAS_STREAM_CONNECTION
}

void acamera_connection_process( void )
{
#if ISP_HAS_STREAM_CONNECTION
#if ISP_HAS_CONNECTION_BUFFER
    process_api_request();
#endif // ISP_HAS_CONNECTION_BUFFER

    process_socket_request();
#endif // ISP_HAS_STREAM_CONNECTION
}
