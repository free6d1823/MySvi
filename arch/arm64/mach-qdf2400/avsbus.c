/*==============================================================================
# Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
# Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/

#include <stdint.h>
#include <stdio.h>
#include <asm/mach-qdf2400/spi/avsbus.h>
#include <asm/mach-qdf2400/spi/spi_api.h>

struct avsbus_master {
    spi_instance_t spi_instance;
    SPI_HANDLE spi_handle;
    spi_config_t spi_config;
};

/**
 * @function avsbus_send_command
 *
 * Sends one Read/Write sub-frame(cmd) and saves the result into *resp
 *
 * At present we are not saving the StatusResponse Frame(section 7.4),
 * but can be easily added if requires
 */
static avsbus_status_t avsbus_send_command(struct avsbus_master *master,
                                           uint32_t cmd, uint32_t *resp)
{
    /*
     * SPI protocol require that MSb be sent first - same as AVS Bus
     *
     * AVSBus require that the MOSI(AVS_MData) be at 1 when the clock is turned ON
     * to detect the <StartCode>=0b01. So we MIGHT have to send a dummy byte with
     * all 1's prior to command if MOSI is left low when SPI clock is turned ON on
     * our HW
     */
    spi_transfer_t tx, rx;
    uint32_t tx_buf[2] ALIGNED(4);
    uint32_t rx_buf[2] ALIGNED(4);

    tx_buf[0] = cmd;
    tx_buf[1] = AVSBUS_IDLE_FRAME;

    tx.buf_len = rx.buf_len = 8; /* Length in bytes */
    tx.word_count = rx.word_count = 2; /* Number of words */
    tx.buf_addr = tx_buf;
    rx.buf_addr = rx_buf;

    if (spi_full_duplex(master->spi_handle, &tx, &rx) == SPI_SUCCESS) {
        *resp = rx_buf[1];
        return AVSBUS_SUCCESS;
    }
    else {
        return AVSBUS_ERR_SPI_COMM;
    }
}

/**
 * @function avsbus_check_err
 *
 * Checks for all possible errors in response from slave
 * @Note: Status Resp Frame not supported to avoid more conditionals and lack
 *        of good usecases
 */
static avsbus_status_t avsbus_check_err(uint32_t resp, avsbus_frame_t type)
{
    uint32_t slave_ack, reserved_mask;

    reserved_mask = (type == AVSBUS_WRITE_FRAME) ? AVSBUS_WF_RES_RESERVED_BMSK :
        AVSBUS_RF_RES_RESERVED_BMSK;

    /* Check CRC */
    if (avsbus_compute_crc(resp) != 0)
        return AVSBUS_ERR_CRC;

    /* Make sure reserved bits are 1s */
    if ((reserved_mask & resp) != reserved_mask)
        return AVSBUS_ERR_INV_RESP;

    /* Check 0Bit */
    if (GET_FIELD_VAL(RF_RES, 0BIT, resp))
        return AVSBUS_ERR_INV_RESP;

    /* Check Slave ACK */
    slave_ack = GET_FIELD_VAL(RF_RES, SLAVE_ACK, resp);
    if (slave_ack != AVSBUS_S_ACK_SUCCESS) {
        if (slave_ack == AVSBUS_S_ACK_BAD_CRC_FAILURE)
            return AVSBUS_ERR_S_ACK_BAD_CRC;
        else if (slave_ack == AVSBUS_S_ACK_INVALID_DATA_FAILURE)
            return AVSBUS_ERR_S_ACK_INV_DATA;
        else
            return AVSBUS_ERR_S_ACK;
    }

    return AVSBUS_SUCCESS;
}

/*******************************************************************************
                Implementation of the Public APIs below
 ******************************************************************************/

/**
 * @function avsbus_init
 *
 * Initializes an instance of AVS Bus corresponding to a SPI instance
 */
avsbus_status_t avsbus_init(spi_instance_t spi_instance,
                            avsbus_handle_t *handle)
{
    static struct avsbus_master temp;
    struct avsbus_master *master = &temp;
    avsbus_status_t ret = AVSBUS_SUCCESS;

    if (!handle) {
        return AVSBUS_ERR_PARAM;
    }

    if (!master) {
        return AVSBUS_ERR_MEM_ALLOC;
    }
    *handle = master;

    if (spi_open(spi_instance, &master->spi_handle) != SPI_SUCCESS) {
        ret = AVSBUS_ERR_SPI_OPEN;
        goto free_memory;
    }

    master->spi_instance = spi_instance;
    if (spi_power_on(master->spi_handle) != SPI_SUCCESS) {
        ret = AVSBUS_ERR_SPI_POWER_ON;
        goto close_spi;
    }

    /* Required polarity by AVSBus protocol
     */
    (master->spi_config).clk_polarity        = SPI_CLK_IDLE_LOW;

    /* Not specified by AVSBus protocol, so give more time for the slave to
     * react and send the start code first
     */
    (master->spi_config).shift_mode          = SPI_INPUT_FIRST_MODE;

    /* SS line is unused in AVSBus protocol, so set it a valid value
     * not to cause any errors in SPI driver
     */
    (master->spi_config).cs_polarity         = SPI_CS_ACTIVE_LOW;
    (master->spi_config).cs_mode             = SPI_CS_DEASSERT;

    /* Two ways to achieve Idle - turn off clock or keep sending 1s
     * Given the SPI APIs, much better to turn off clock
     */
    (master->spi_config).clk_mode            = SPI_CLK_NORMAL;

    /* Given that the word size can only be 31 bits on our HW and we run on a
     * little endian machine, the requirement of sending the MSb first can be
     * more easily achieved by word size of 8bits. Also helps us to avoid sending
     * too many of unnecessary 1s in each SPI transaction
     *
     * See avsbus_send_command() for more details
     */
    (master->spi_config).bits_per_word       = 32;

    /* Irrelavent as SS line is unused in AVSBus */
    (master->spi_config).slave_index         = 0;

    /* Range allowed by AVSBus spec 5MHz to 50MHz
     * Max allowed in non-HS mode 25MHz
     */
    (master->spi_config).min_slave_freq_hz   = 5*1000*1000;
    (master->spi_config).max_slave_freq_hz   = 25*1000*1000;

    /* Irrelavent as SS line is unused in AVSBus */
    (master->spi_config).deassertion_time_ns = 0;

    /* We are not using loopback mode, so set it to zero */
    (master->spi_config).loopback_mode       = 0;

    /* For AVSBus we need launch/send data on rising edge and read on falling edge
     * which is possible only in non-HS (non- High speed) mode */
    (master->spi_config).hs_mode             = 0;

    /* Configure SPI */
    if (spi_configure(master->spi_handle, &master->spi_config, 0) != SPI_SUCCESS) {
        ret = AVSBUS_ERR_SPI_CONFIGURE;
        goto close_spi;
    }

    /* Protocol recommends us to resynchronize with slave during init before
     * any other communication.
     *
     * Any additional resync's(ex: periodic, CRC error and so on) should be
     * triggered by pmic/module specific code
     */
    avsbus_resync(*handle);

    return ret;

close_spi:
    spi_close(master->spi_handle);

free_memory:
    *handle = NULL;
    return ret;
}


/**
 * @function avsbus_deinit
 *
 * Releases the resources associated with give handle
 */
avsbus_status_t avsbus_deinit(avsbus_handle_t *handle)
{
    struct avsbus_master *master = *handle;
    avsbus_status_t ret = AVSBUS_SUCCESS;

    if (!master)
        return AVSBUS_ERR_PARAM;

    if (spi_close(master->spi_handle) != SPI_SUCCESS)
        ret = AVSBUS_ERR_SPI_CLOSE;

    *handle = NULL;
    return ret;
}


/**
 * @function avsbus_resync
 *
 * If we lose synchronization with AVS Slave, then we send 34 consecutive
 * 1s to resynchronize. We send 40 1s in this function which will still meet
 * the necessry requirement defined in spec. The additional 6 1s will be treated
 * as an Idle state
 *
 * See section 5.6 in AVSBus spec
 */
avsbus_status_t avsbus_resync(avsbus_handle_t handle)
{
    struct avsbus_master *master = handle;
    spi_status_t ret;
    spi_transfer_t tx_pkt, rx_pkt;
    uint32_t tx_buf[2] ALIGNED(4) = {(uint32_t)-1, (uint32_t)-1}; /* 32bit aligned */
    uint32_t rx_buf[2] ALIGNED(4);

    if (!handle)
        return AVSBUS_ERR_PARAM;

    tx_pkt.buf_addr   = tx_buf;
    tx_pkt.buf_len    = 8; /*8B = 64 1's, Protocol requires only 34 1's */
    tx_pkt.word_count = 2; /*8B = 64 1's, Protocol requires only 34 1's */

    /* rx_pkt is required to avoid a crash in SPI if we pass NULL for rx_pkt */
    rx_pkt.buf_addr   = rx_buf;
    rx_pkt.buf_len    = 8; /* Length in bytes */
    rx_pkt.word_count = 2; /*8B = 64 1's, Protocol requires only 34 1's */

    ret = spi_full_duplex(master->spi_handle, &tx_pkt, &rx_pkt);

    if (ret == SPI_SUCCESS)
        return AVSBUS_SUCCESS;
    else
        return AVSBUS_ERR_SPI_COMM;
}


/**
 * @function avsbus_read
 *
 * Create and send a read frame and stores the response into *read_resp
 */
static avsbus_status_t avsbus_read(avsbus_handle_t handle, uint32_t cmd_group,
                                   uint32_t cmd_data_type, uint32_t select,
                                   uint32_t *read_resp)
{
    struct avsbus_master *master = handle;
    uint32_t command;

    if (!master || !read_resp)
        return AVSBUS_ERR_PARAM;

    command = avsbus_create_read_frame(cmd_group, cmd_data_type, select);

    return avsbus_send_command(master, command, read_resp);
}


/**
 * @function avsbus_write
 *
 * Create and send a write frame and stores the response into *write_resp
 */
static avsbus_status_t avsbus_write(avsbus_handle_t handle, uint32_t cmd,
                                    uint32_t cmd_group, uint32_t cmd_data_type,
                                    uint32_t select, uint32_t cmd_data,
                                    uint32_t *write_resp)
{
    struct avsbus_master *master = handle;
    uint32_t command;

    if (!master || !write_resp)
        return AVSBUS_ERR_PARAM;

    command = avsbus_create_write_frame(cmd, cmd_group, cmd_data_type, select, cmd_data);

    return avsbus_send_command(master, command, write_resp);
}


/**
 * @function avsbus_read_voltage
 *
 * reads the voltage(mVolt) for rail_sel into *mv
 */
avsbus_status_t avsbus_read_voltage(avsbus_handle_t handle,
                                    uint32_t rail_sel,
                                    uint16_t *mv,
                                    uint16_t *status_resp)
{
    uint32_t resp;
    avsbus_status_t ret;

    ret = avsbus_read(handle,
                      AVSBUS_CMD_GROUP_STD_DEFINED,
                      AVSBUS_D_TYPE_VOLTAGE_RW,
                      rail_sel,
                      &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    *mv = GET_FIELD_VAL(RF_RES, CMD_DATA, resp);

    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_READ_FRAME);
}

/**
 * @function avsbus_set_voltage
 *
 * Sets the voltage and returns avsbus status
 */
avsbus_status_t avsbus_set_voltage(avsbus_handle_t handle,
                                   uint32_t rail_sel,
                                   uint16_t mv,
                                   uint16_t *status_resp)
{
    uint32_t resp;
    avsbus_status_t ret;

    ret = avsbus_write(handle,
                       AVSBUS_CMD_WRITE_AND_COMMIT,
                       AVSBUS_CMD_GROUP_STD_DEFINED,
                       AVSBUS_D_TYPE_VOLTAGE_RW,
                       rail_sel,
                       mv,
                       &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_WRITE_FRAME);
}


/**
 * @function avsbus_read_temperature
 *
 * reads the temperature(deci Celcius) for rail_sel into *dc
 */
avsbus_status_t avsbus_read_temperature(avsbus_handle_t handle,
                                        uint32_t rail_sel,
                                        uint16_t *dc,
                                        uint16_t *status_resp)
{
    uint32_t resp;
    avsbus_status_t ret;

    ret = avsbus_read(handle,
                      AVSBUS_CMD_GROUP_STD_DEFINED,
                      AVSBUS_D_TYPE_TEMPERATURE_R,
                      rail_sel,
                      &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    *dc = GET_FIELD_VAL(RF_RES, CMD_DATA, resp);
    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_READ_FRAME);
}


/**
 * @function avsbus_read_status
 *
 * Reads the status response of a given rail
 */

avsbus_status_t avsbus_read_status(avsbus_handle_t handle,
                                   uint32_t rail_sel,
                                   uint16_t *status,
                                   uint16_t *status_resp)
{
    avsbus_status_t ret;
    uint32_t resp;

    ret = avsbus_read(handle,
                      AVSBUS_CMD_GROUP_STD_DEFINED,
                      AVSBUS_D_TYPE_STATUS_RW,
                      rail_sel,
                      &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    *status = GET_FIELD_VAL(RF_RES, CMD_DATA, resp);
    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_READ_FRAME);
}

/**
 * @function avsbus_set_status
 *
 * Used to clear specific bits in status
 */

avsbus_status_t avsbus_set_status(avsbus_handle_t handle,
                                  uint32_t rail_sel,
                                  uint16_t status,
                                  uint16_t *status_resp)
{
    avsbus_status_t ret;
    uint32_t resp;

    ret = avsbus_write(handle,
                       AVSBUS_CMD_WRITE_AND_COMMIT,
                       AVSBUS_CMD_GROUP_STD_DEFINED,
                       AVSBUS_D_TYPE_STATUS_RW,
                       rail_sel,
                       status,
                       &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_WRITE_FRAME);
}


/**
 * @function avsbus_read_version
 *
 * Reads the AVSBus version supported by Slave
 */
avsbus_status_t avsbus_read_version(avsbus_handle_t handle,
                                    uint16_t *version,
                                    uint16_t *status_resp)
{
    avsbus_status_t ret;
    uint32_t resp;

    ret = avsbus_read(handle,
                      AVSBUS_CMD_GROUP_STD_DEFINED,
                      AVSBUS_D_TYPE_VERSION_R,
                      0,
                      &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    *version = GET_FIELD_VAL(RF_RES, CMD_DATA, resp);
    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_READ_FRAME);
}


/**
 * @function avsbus_read_vout_trans_rate
 *
 * Reads the voltage transition rate of a given rail
 */
avsbus_status_t avsbus_read_vout_trans_rate(avsbus_handle_t handle,
                                            uint32_t rail_sel,
                                            uint8_t *rise_rate,
                                            uint8_t *fall_rate,
                                            uint16_t *status_resp)
{
    avsbus_status_t ret;
    uint32_t resp;
    uint16_t cmd_data;

    ret = avsbus_read(handle,
                      AVSBUS_CMD_GROUP_STD_DEFINED,
                      AVSBUS_D_TYPE_VOUT_TRANSITION_RATE_RW,
                      rail_sel,
                      &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    cmd_data = GET_FIELD_VAL(RF_RES, CMD_DATA, resp);
    *rise_rate = (cmd_data & AVSBUS_CMD_DATA_RISE_RATE_BMSK) >> AVSBUS_CMD_DATA_RISE_RATE_SHFT;
    *fall_rate = (cmd_data & AVSBUS_CMD_DATA_FALL_RATE_BMSK) >> AVSBUS_CMD_DATA_FALL_RATE_SHFT;

    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_READ_FRAME);
}


/**
 * @function avsbus_set_vout_trans_rate
 *
 * Sets the voltage transition rate and returns avsbus status
 */
avsbus_status_t avsbus_set_vout_trans_rate(avsbus_handle_t handle,
                                           uint32_t rail_sel,
                                           uint8_t rise_rate,
                                           uint8_t fall_rate,
                                           uint16_t *status_resp)
{
    uint32_t resp;
    avsbus_status_t ret;
    uint16_t trans_rate;

    trans_rate = ((rise_rate << AVSBUS_CMD_DATA_RISE_RATE_SHFT) |
                  (fall_rate << AVSBUS_CMD_DATA_FALL_RATE_SHFT));
    ret = avsbus_write(handle,
                       AVSBUS_CMD_WRITE_AND_COMMIT,
                       AVSBUS_CMD_GROUP_STD_DEFINED,
                       AVSBUS_D_TYPE_VOUT_TRANSITION_RATE_RW,
                       rail_sel,
                       trans_rate,
                       &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_WRITE_FRAME);
}


/**
 * @function avsbus_read_vout_trans_rate
 *
 * Reads the current of a given rail in 10s of mA
 */
avsbus_status_t avsbus_read_current(avsbus_handle_t handle,
                                    uint32_t rail_sel,
                                    uint16_t *Dm_amp,
                                    uint16_t *status_resp)
{
    avsbus_status_t ret;
    uint32_t resp;

    ret = avsbus_read(handle,
                      AVSBUS_CMD_GROUP_STD_DEFINED,
                      AVSBUS_D_TYPE_CURRENT_R,
                      rail_sel,
                      &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    *Dm_amp = GET_FIELD_VAL(RF_RES, CMD_DATA, resp);
    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_READ_FRAME);
}


/**
 * @function avsbus_reset_voltage
 *
 * Resets the voltage of a rail to a "Predetermined Value"
 */
avsbus_status_t avsbus_reset_voltage(avsbus_handle_t handle,
                                     uint32_t rail_sel,
                                     uint16_t *status_resp)
{
    uint32_t resp;
    avsbus_status_t ret;

    ret = avsbus_write(handle,
                       AVSBUS_CMD_WRITE_AND_COMMIT,
                       AVSBUS_CMD_GROUP_STD_DEFINED,
                       AVSBUS_D_TYPE_VOLTAGE_RESET_W,
                       rail_sel,
                       0,
                       &resp);

    if (ret != AVSBUS_SUCCESS)
        return ret;

    if (status_resp)
        *status_resp = GET_FIELD_VAL(RF_RES, STATUS_RESP, resp);

    return avsbus_check_err(resp, AVSBUS_WRITE_FRAME);
}

/**
 * @function: avsbus_exec_multiple_cmds
 *
 * Executes multiple commands composed by the client and sends the response
 * If clients are using this mechanism they are responsible for creating and
 * decoding the data from the frames
 */
avsbus_status_t avsbus_exec_multiple_cmds(avsbus_handle_t handle,
                                          const uint32_t *req_buf,
                                          uint32_t *resp_buf, int frame_cnt)
{
    spi_transfer_t tx,rx;
    struct avsbus_master *master = handle;
    avsbus_status_t ret;
    avsbus_frame_t frame_type;
    int i;

    if (!master || !req_buf || !resp_buf)
        return AVSBUS_ERR_PARAM;

    tx.buf_addr = (void *)req_buf;
    rx.buf_addr = resp_buf;
    tx.buf_len = rx.buf_len = (frame_cnt + 1) * sizeof(uint32_t);
    tx.word_count = rx.word_count = (frame_cnt + 1);

    if(spi_full_duplex(master->spi_handle, &tx, &rx) != SPI_SUCCESS)
        return AVSBUS_ERR_SPI_COMM;

    for (i = 0; i < frame_cnt; i++) {
        /* Identify frame type */
        frame_type = (GET_FIELD_VAL(RF_REQ, CMD, req_buf[i]) == AVSBUS_CMD_READ) ?
            AVSBUS_READ_FRAME : AVSBUS_WRITE_FRAME;

        ret = avsbus_check_err(resp_buf[i+1], frame_type);
        if (ret != AVSBUS_SUCCESS)
            return ret;
    }

    return AVSBUS_SUCCESS;
}
