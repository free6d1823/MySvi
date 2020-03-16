/**
 * @file   AvsbusDevice.c
 *
 * @brief  AVSBus based APIs to set voltage for ISL68137 - MonoRail setup
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 * Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 */

#include <stdint.h>
#include <stdio.h>
#include <target/avsbus_device.h>
#include <target/delay.h>
#include <target/bitops.h>
#include <bits/alltypes.h>
#include <string.h>
#include <stdlib.h>
#include <target/cmdline.h>

/* Types of AVSBus Telemetry data that can be read by SW */
typedef enum {
    AVSBUS_DEV_READ_TEMP = 0,
    AVSBUS_DEV_READ_CURRENT,
    AVSBUS_DEV_READ_VOLTAGE,
    AVSBUS_DEV_READ_TOTAL,
}avsbus_dev_read_t;

#define UNUSED_FIELD (-1)
#define IS_UNUSED_FIELD(_fld) ((_fld) == (typeof(_fld)) UNUSED_FIELD)

/* Per device Config */
struct avsbus_dev_device_config {
    bool initialized;
    uint16_t avs_port;
    avsbus_handle_t avsbus_handle;
    uint8_t rails[AVSBUS_DEV_RAIL_TOTAL+1]; /* first unused entry must be >AVSBUS_DEV_RAIL_TOTAL */
    uint16_t pmbus_slave_addr;
    uint16_t pmbus_smbus_id;
};


/* Per rail config */
struct avsbus_dev_rail_config {
    bool initialized;
    uint8_t device_idx;            /* Rail belongs to device dev_cfg[device_idx] */
    uint8_t select;                /* rail select within the device */
    uint8_t trans_rate_up;         /* in mv/us */
    uint8_t trans_rate_down;       /* in mv/us */

    uint16_t current_mv;           /* Current voltage */
    uint16_t last_max_mv;          /* Max mV in last measurement period for telemetry */
    uint32_t total_power_samples;  /* Number of samples accumulated until now */
    uint64_t total_power;          /* Cummulative total power in 10^-5 Watts (10s of uW) */
    int16_t temp_in_dC;            /* Temperature in 0.1C */
    /* Read cmds do not changes, so no need to compose them everytime */
    uint32_t read_cmds[AVSBUS_DEV_READ_TOTAL];
};


/* Per-client power telemetry context */
struct avsbus_dev_pwr_cl_ctx {
    uint32_t cl_samples[AVSBUS_DEV_RAIL_TOTAL];
    uint64_t cl_power[AVSBUS_DEV_RAIL_TOTAL];
};

/* Magic value used to assign to the temperature telemetry handle */
#define AVSBUS_DEV_MAGIC_TEMP_HANDLE ((void *)0xFEEDF00D)
/*=============================================================================
                        DEVICE CONFIG
=============================================================================*/
/**
 * Telemetry Config:
 *   AVSBUS_DEV_TELEMETRY_POLL_US - Duration b/w individual power measurements
 */
#define AVSBUS_DEV_TELEMETRY_POLL_US 1000

/* To use timer based wait for VDone */
#define AVSBUS_DEV_TIMER_FOR_VDONE 1

/* Max retry count */
#define AVSBUS_DEV_MAX_CRC_RETRY (10)

/* Total number of external PMICs */
#define AVSBUS_DEV_DEVICE_TOTAL 1

static struct avsbus_dev_device_config dev_cfg[AVSBUS_DEV_DEVICE_TOTAL] =
{
    {   /* Device 0 */
        .avs_port = (uint16_t)SPI_INSTANCE_2,
        .rails =  {0, 1, (uint8_t)-1},
    }
};

/* Group rails belonging to same device adjacent to each other */
static struct avsbus_dev_rail_config rail_cfg[AVSBUS_DEV_RAIL_TOTAL] =
{
    {   /* CBF */
        .device_idx = 0,                    /* Index in dev_cfg */
        .select = AVSBUS_DEV_RAIL_CBF,
        .trans_rate_up = 20,
        .trans_rate_down = 20,
    },
    {   /* APC */
        .device_idx = 0,
        .select = AVSBUS_DEV_RAIL_APC,
        .trans_rate_up = 20,
        .trans_rate_down = 20,
    }
};

/*=============================================================================
                        Global definitions
=============================================================================*/

/*=============================================================================
                        Private Functions
=============================================================================*/
/**
 * @brief: Update the rail_cfg with the telemetry data
 */
static void avsbus_dev_update_rail_data(struct avsbus_dev_rail_config *r_cfg,
                                        avsbus_dev_read_t telemetry_type,
                                        uint16_t val)
{
    switch (telemetry_type) {
    case AVSBUS_DEV_READ_CURRENT:
        /* Reset the total_power and sample count prior to overflow */
        if (r_cfg->total_power_samples == (~0))
            r_cfg->total_power = r_cfg->total_power_samples = 0;

        /* power(in 10s of uW) += (mV * (10*mA)) */
        r_cfg->total_power += (r_cfg->current_mv * val);
        r_cfg->total_power_samples++;

        /*
         * last_max_mv tracks the peak volatge observed in a measurement
         * period, so, set to current_mv
         */
        r_cfg->last_max_mv = r_cfg->current_mv;
        break;

    case AVSBUS_DEV_READ_TEMP:
        r_cfg->temp_in_dC = val;
        break;

    case AVSBUS_DEV_READ_VOLTAGE:
        r_cfg->current_mv = val;
        break;

    default:
        printf("Unknown Telemetry Type\n");
    }
}


/**
 * @brief: Measure and Update a specific telemetry for all rails
 */
static void avsbus_dev_update_telemetry(struct avsbus_dev_device_config *d_cfg,
                                        avsbus_dev_read_t telemetry_type)
{
    AVSBUS_DECLARE_REQ_FRAME_BUFFER(req_buf, AVSBUS_DEV_RAIL_TOTAL);
    AVSBUS_DECLARE_RESP_FRAME_BUFFER(resp_buf, AVSBUS_DEV_RAIL_TOTAL);
    struct avsbus_dev_rail_config *r_cfg;
    int j, resp, retry_count = AVSBUS_DEV_MAX_CRC_RETRY;
    uint16_t val;
    avsbus_status_t ret;

    /* Initialize the request buffer */
    for (j = 0; d_cfg->rails[j] < AVSBUS_DEV_RAIL_TOTAL; j++) {
        r_cfg = rail_cfg + d_cfg->rails[j];
        AVSBUS_SET_REQ_FRAME(req_buf, j,
                             r_cfg->read_cmds[telemetry_type]);
    }
    AVSBUS_SET_REQ_FRAME(req_buf, j, AVSBUS_IDLE_FRAME);

    /* execute the commands in req_buf and frame_cnt = j */
    do {
        ret = avsbus_exec_multiple_cmds(d_cfg->avsbus_handle, req_buf, resp_buf,
                                        j); /* # of frames except idle frame */
        if (ret == AVSBUS_SUCCESS)
            break;

        if (ret == AVSBUS_ERR_CRC || ret == AVSBUS_ERR_S_ACK_BAD_CRC) {
            avsbus_resync(d_cfg->avsbus_handle);
            if (retry_count-- != 0)
                continue;
        }
        if (ret != AVSBUS_SUCCESS)
            printf("Uncorrectable error\n");
    } while(1);

    /* Extract data from the resp_buf */
    for (j = 0; d_cfg->rails[j] < AVSBUS_DEV_RAIL_TOTAL; j++) {
        r_cfg = rail_cfg + d_cfg->rails[j];

        /* Extract value from response */
        resp = AVSBUS_GET_RESP_FRAME(resp_buf, j);
        val = GET_FIELD_VAL(RF_RES, CMD_DATA, resp);

        avsbus_dev_update_rail_data(r_cfg, telemetry_type, val);
    }
}


/**
 * @brief: Initializes a devices
 * We need to use priority inheritence mutex as the APIs can be called by threads
 * of differnt priority levels and PI mutex will avoid us from getting into a
 * deadlock
 */
static avsbus_status_t
avsbus_dev_init_device(struct avsbus_dev_device_config *d_cfg)
{
    avsbus_status_t ret = AVSBUS_SUCCESS;

    if (!d_cfg)
        return AVSBUS_ERR;

    if (d_cfg->initialized)
        return AVSBUS_SUCCESS;

    ret = avsbus_init(d_cfg->avs_port, &d_cfg->avsbus_handle);
    if (ret != AVSBUS_SUCCESS)
        return ret;

    d_cfg->initialized = true;

    return AVSBUS_SUCCESS;
}


/**
 * @brief: Sets the Vout transtion rate for both increasing and decreasing
 * paths
 */
static avsbus_status_t
avsbus_dev_set_trans_rate(struct avsbus_dev_rail_config *r_cfg)
{
    avsbus_status_t ret;
    struct avsbus_dev_device_config *d_cfg = dev_cfg + r_cfg->device_idx;
    int retry_count = AVSBUS_DEV_MAX_CRC_RETRY;

    do {
        ret = avsbus_set_vout_trans_rate(d_cfg->avsbus_handle, r_cfg->select,
                                         r_cfg->trans_rate_up, r_cfg->trans_rate_down,
                                         NULL);
        if (ret == AVSBUS_SUCCESS)
            break;

        if (ret == AVSBUS_ERR_CRC || ret == AVSBUS_ERR_S_ACK_BAD_CRC) {
            avsbus_resync(d_cfg->avsbus_handle);
            if (retry_count-- != 0)
                continue;
        }
        break;
    } while(1);

    return ret;
}


/**
 * @brief: Initializes a given rail config.
 * - Initalized the SW structures
 * - When necessary initialized the parent device
 * - Acquire control and set transition rate
 */
static avsbus_status_t
avsbus_dev_init_rail(struct avsbus_dev_rail_config *r_cfg)
{
    struct avsbus_dev_device_config *d_cfg;
    avsbus_status_t ret;
    uint16_t i, cmd;

    if (!r_cfg)
        return AVSBUS_ERR;

    if (r_cfg->initialized)
        return AVSBUS_SUCCESS;

    d_cfg = dev_cfg + r_cfg->device_idx;

    ret = avsbus_dev_init_device(d_cfg);
    if (ret != AVSBUS_SUCCESS)
        return ret;

    for (i = 0; i < AVSBUS_DEV_READ_TOTAL; i++) {
        switch(i) {
        case AVSBUS_DEV_READ_TEMP:
            cmd = AVSBUS_D_TYPE_TEMPERATURE_R;
            break;
        case AVSBUS_DEV_READ_CURRENT:
            cmd = AVSBUS_D_TYPE_CURRENT_R;
            break;
        case AVSBUS_DEV_READ_VOLTAGE:
            cmd = AVSBUS_D_TYPE_VOLTAGE_RW;
            break;
        default:
            printf("Unknown read type\n");
        }
        r_cfg->read_cmds[i] = avsbus_create_read_frame(AVSBUS_CMD_GROUP_STD_DEFINED,
                                                       cmd, r_cfg->select);
    }

    ret = avsbus_dev_set_trans_rate(r_cfg);
    if (ret != AVSBUS_SUCCESS)
        return ret;

    r_cfg->initialized = true;

    return AVSBUS_SUCCESS;
}


#if AVSBUS_DEV_TIMER_FOR_VDONE

/* Timer based wait implementation */
static avsbus_status_t AvsbusWaitForVdone(struct avsbus_dev_rail_config *r_cfg,
                                          uint16_t new_mv)
{
    uint32_t delay_us;
    uint16_t old_mv = r_cfg->current_mv;
    uint32_t trans_rate = r_cfg->trans_rate_up;

    delay_us = (new_mv > old_mv) ? (new_mv - old_mv) : (old_mv - new_mv); //mv
    delay_us = (delay_us / trans_rate) + 1; //mv/us
    udelay(delay_us);

    return AVSBUS_SUCCESS;
}

#else

/* Poll for VDone implementation */
static avsbus_status_t AvsbusWaitForVdone(struct avsbus_dev_rail_config *r_cfg,
                                          uint16_t new_mv)
{
    avsbus_status_t ret;
    uint16_t status = 0, retry_count = AVSBUS_DEV_MAX_CRC_RETRY;
    uint16_t rail_id = r_cfg->select;
    struct avsbus_dev_device_config *d_cfg = dev_cfg + r_cfg->device_idx;

    do {
        ret = avsbus_read_status(d_cfg->avsbus_handle, rail_id, &status, NULL);
        if (ret == AVSBUS_ERR_CRC || ret == AVSBUS_ERR_S_ACK_BAD_CRC) {
            avsbus_resync(d_cfg->avsbus_handle);
            if (retry_count-- != 0)
                continue;
        }

        /* Uncorrectable failure return - Likely programming error */
        if (ret != AVSBUS_SUCCESS)
            printf("Uncorrectable failure\n");

        /*
         * VDONE bit will be 0 when,
         *   The rail is OFF
         *   The rail is powering up
         *   When a new voltage target is committed
         * VDONE will transition to 1,
         *   as soon as the voltage has reached the set operating point
         *
         * NOTE: Given the above, this API *MUST* not be called when the rail is
         * powered OFF
         */
        if (status & AVSBUS_STATUS_BITS_VDONE)
            return ret;
    } while(1);
}
#endif

/*=============================================================================
                        Public Functions
=============================================================================*/
/**
 * @function AvsbusDeviceInitialize
 *
 * @brief Initializes the AVSBUS device.
 *
 * @return avsbus_status_t
 */
avsbus_status_t AvsbusDeviceInitialize()
{
    avsbus_status_t ret;
    int i;

    for (i = 0 ; i < AVSBUS_DEV_RAIL_TOTAL; i++) {
        ret = avsbus_dev_init_rail(rail_cfg + i);
        if (ret != AVSBUS_SUCCESS)
            break;
    }

    if (ret != AVSBUS_SUCCESS) {
        printf("Avsbus Device Initialized failed\n");
        AvsbusDeviceDeinitialize();
        return ret;
    }

    /* Update the Initial Voltage Values */
    for (i = 0 ; i < AVSBUS_DEV_DEVICE_TOTAL; i++) {
        struct avsbus_dev_device_config *d_cfg = dev_cfg + i;
        avsbus_dev_update_telemetry(d_cfg, AVSBUS_DEV_READ_VOLTAGE);
    }

    printf("Avsbus Device Initialized\n");

    return ret;
}


/**
 * @function AvsbusDeviceDeinitialize
 *
 * @brief Deinitializes the AVSBUS device.
 *
 * @return avsbus_status_t
 */
avsbus_status_t AvsbusDeviceDeinitialize()
{
    /* Don't bother supporting de-initialize
     *  - No real usecase
     *  - Makes implementation unnecessarily complex
     *  - AvsbusDeviceInitialize can handle multiple calls, so we should be covered
     */
    return AVSBUS_SUCCESS;
}


/**
 * @function AvsbusDeviceSetVoltage
 *
 * @brief Sets the voltage level in microvolts
 *
 * @return void
 *
 * @TODO: Since we are converging towards CVR solution, we should clean up
 * this API and all other Monza related stuff, so that it takes in only a new
 * voltage value and avsbus_dev_rail_t
 */
void AvsbusDeviceSetVoltage (avs_apc_cpu_type cpu_type,
                             uint32_t uv_voltage)
{
    avsbus_status_t ret;
    uint16_t st_resp , retry_count = AVSBUS_DEV_MAX_CRC_RETRY;
    struct avsbus_dev_rail_config *r_cfg;
    struct avsbus_dev_device_config *d_cfg;
    uint16_t new_mv = uv_voltage;

    r_cfg = (cpu_type == AVS_CBF) ? &rail_cfg[AVSBUS_DEV_RAIL_CBF] :
        &rail_cfg[AVSBUS_DEV_RAIL_APC];
    d_cfg = &dev_cfg[r_cfg->device_idx];

    do {
        /* Set Voltage */
        ret = avsbus_set_voltage(d_cfg->avsbus_handle, r_cfg->select,
                                 new_mv, &st_resp);
        if (ret == AVSBUS_SUCCESS)
            break;

        /* If the last transition is still in progress then we might get ERR_S_ACK */
        if (ret == AVSBUS_ERR_S_ACK && !(st_resp & AVSBUS_ST_RSP_VDONE_BMSK)) {
            continue;
        }

        /* Check for CRC errors */
        if (ret == AVSBUS_ERR_CRC || ret == AVSBUS_ERR_S_ACK_BAD_CRC) {
            avsbus_resync(d_cfg->avsbus_handle);
            if (retry_count-- != 0)
                continue;
        }
    } while (1);

    /* See if we need to wait for voltage to settle */
    if (r_cfg->current_mv < new_mv)
        AvsbusWaitForVdone(r_cfg, new_mv);

    /* Save the last set voltage */
    r_cfg->current_mv = new_mv;
    r_cfg->last_max_mv = max(r_cfg->last_max_mv, r_cfg->current_mv);
    printf("Rail %d voltage %dmV is set\n", cpu_type, new_mv);
}


/**
 * @function AvsbusDeviceGetVoltage
 *
 * Populates current voltage in *uv_voltage and returns avsbus_status_t
 */
avsbus_status_t AvsbusDeviceGetVoltage (avs_apc_cpu_type cpu_type)
{
    struct avsbus_dev_rail_config *r_cfg;

    r_cfg = (cpu_type == AVS_CBF) ? &rail_cfg[AVSBUS_DEV_RAIL_CBF] :
        &rail_cfg[AVSBUS_DEV_RAIL_APC];

    int i;
    /* Update the Initial Voltage Values */
    for (i = 0 ; i < AVSBUS_DEV_DEVICE_TOTAL; i++) {
        struct avsbus_dev_device_config *d_cfg = dev_cfg + i;
        avsbus_dev_update_telemetry(d_cfg, AVSBUS_DEV_READ_VOLTAGE);
    }

    printf("Rail %d voltage %dmV is measured\n", cpu_type, r_cfg->current_mv);

    return AVSBUS_SUCCESS;
}

/**
 * @function AvsbusDeviceGetPowerHandle
 *
 * @brief Get a power telemetry handle
 * At present, it just enforces a single client requireemnt for power
 * telemetry. in future
 */
avsbus_status_t AvsbusDeviceGetPowerHandle(AvsbusDevicePowerHandle *h)
{
    if (!h)
        return AVSBUS_ERR_PARAM;
    static struct avsbus_dev_pwr_cl_ctx temp;
    *h = (AvsbusDevicePowerHandle *)&temp;

    if (!*h)
        return AVSBUS_ERR_MEM_ALLOC;

    return AVSBUS_SUCCESS;
}


/**
 * @function AvsbusDeviceRelasePowerHandle
 *
 * @brief Release a power telemetry handle
 */
avsbus_status_t AvsbusDeviceReleasePowerHandle(AvsbusDevicePowerHandle *h)
{
    if (!h || !*h)
        return AVSBUS_ERR_PARAM;

    *h = NULL;
    return AVSBUS_SUCCESS;
}

/**
 * @function AvsbusDeviceGetTempHandle
 *
 * @brief Get a temperature telemetry handle
 */
avsbus_status_t AvsbusDeviceGetTempHandle(AvsbusDeviceTempHandle *h)
{
    if (!h)
        return AVSBUS_ERR_PARAM;

    *h = AVSBUS_DEV_MAGIC_TEMP_HANDLE;

    return AVSBUS_SUCCESS;
}


/**
 * @function AvsbusDeviceReleaseTempHandle
 *
 * @brief Release a temperature telemetry handle
 */
avsbus_status_t AvsbusDeviceReleaseTempHandle(AvsbusDeviceTempHandle *h)
{
    if (h && *h == AVSBUS_DEV_MAGIC_TEMP_HANDLE) {
        *h = NULL;
        return AVSBUS_SUCCESS;
    }
    return AVSBUS_ERR;
}


/**
 * @function: AvsbusDeviceGetPower
 *
 * @brief: Populates 'data' with power data. Power data is in mWatts
 */
avsbus_status_t
AvsbusDeviceGetPower(AvsbusDevicePowerHandle h,
                     uint32_t (*data)[AVSBUS_DEV_RAIL_TOTAL])
{
    int i, j, rail_id;
    struct avsbus_dev_rail_config *r_cfg;
    struct avsbus_dev_device_config *d_cfg;
    struct avsbus_dev_pwr_cl_ctx *cl_ctx;
    uint64_t sample_diff, power_diff;

/*    if(!data || !*data || !h)
        return AVSBUS_ERR;*/

    int k;
    for (k = 0 ; k < AVSBUS_DEV_DEVICE_TOTAL; k++) {
        struct avsbus_dev_device_config *d_cfg = dev_cfg + k;
        avsbus_dev_update_telemetry(d_cfg, AVSBUS_DEV_READ_CURRENT);
    }

    cl_ctx = (struct avsbus_dev_pwr_cl_ctx *)h;

    for (i = 0; i < AVSBUS_DEV_DEVICE_TOTAL; i++) {
        d_cfg = dev_cfg + i;

        for (j = 0; d_cfg->rails[j] < AVSBUS_DEV_RAIL_TOTAL; j++) {
            rail_id = d_cfg->rails[j];
            r_cfg = rail_cfg + rail_id;

            /* There was a overflow in power data so reset */
            if (cl_ctx->cl_samples[rail_id] > r_cfg->total_power_samples) {
                cl_ctx->cl_samples[rail_id] = 0;
                cl_ctx->cl_power[rail_id] = 0;
            }

            /* Calculate number of samples since last call to this API */
            sample_diff = r_cfg->total_power_samples - cl_ctx->cl_samples[rail_id];

            /* Calculate average power since last call to this API */
            if (sample_diff) {
                power_diff = r_cfg->total_power - cl_ctx->cl_power[rail_id];
                /* Convert power_diff to mW(/100) and compute average power(/sample_diff) */
                (*data)[rail_id] =  power_diff / (100 * sample_diff);
            }
            else
                (*data)[rail_id] = 0;

            /* Update client context to reflext the state from this call */
            cl_ctx->cl_samples[rail_id] = r_cfg->total_power_samples;
            cl_ctx->cl_power[rail_id] = r_cfg->total_power;
        }
    }

    return AVSBUS_SUCCESS;
}


/**
 * @function: AvsbusDeviceGetTemp
 *
 * @brief: Populates 'data' with temperature data. Temperature is in dC(0.1C)
 */
avsbus_status_t
AvsbusDeviceGetTemp(AvsbusDeviceTempHandle h,
                    int16_t (*data)[AVSBUS_DEV_RAIL_TOTAL])
{
    int i;
    struct avsbus_dev_rail_config *r_cfg;
    struct avsbus_dev_device_config *d_cfg;

    if(!data || !*data || h != AVSBUS_DEV_MAGIC_TEMP_HANDLE)
        return AVSBUS_ERR;

    for (i = 0; i < AVSBUS_DEV_DEVICE_TOTAL; i++) {
        d_cfg = dev_cfg + i;
        avsbus_dev_update_telemetry(d_cfg, AVSBUS_DEV_READ_TEMP);
    }

    for (i = 0; i < AVSBUS_DEV_RAIL_TOTAL; i++) {
        r_cfg = rail_cfg + i;
        (*data)[i] = r_cfg->temp_in_dC;
    }

    return AVSBUS_SUCCESS;
}


static avsbus_status_t global_test_status = AVSBUS_SUCCESS;

#define SET_GLOBAL_TEST_STATUS(ret_val)                           \
    global_test_status = (global_test_status == AVSBUS_SUCCESS) ? \
        (ret_val) : global_test_status
void avs_device_temp()
{
    AvsbusDeviceTempHandle t_handle;
	int16_t temp_data[AVSBUS_DEV_RAIL_TOTAL];
    avsbus_status_t ret;
	ret = AvsbusDeviceGetTempHandle(&t_handle);
    if (ret != AVSBUS_SUCCESS) {
        printf("AvsbusDeviceGetTempHandle Failed\n");
        SET_GLOBAL_TEST_STATUS(ret);
    }
    ret = AvsbusDeviceGetTemp(t_handle, &temp_data);
    if (ret != AVSBUS_SUCCESS) {
        printf("AvsbusDeviceGetTemp Failed\n");
        SET_GLOBAL_TEST_STATUS(ret);
    } else {
        printf("Temp(dC) T0:%d T1:%d\n", temp_data[0], temp_data[1]);
        if (temp_data[0] <= 0 && temp_data[1] <= 0)
            SET_GLOBAL_TEST_STATUS(AVSBUS_ERR);
    }
    ret = AvsbusDeviceReleaseTempHandle(&t_handle);
    if (ret != AVSBUS_SUCCESS) {
        printf("AvsbusDeviceReleaseTempHandle Failed\n");
        SET_GLOBAL_TEST_STATUS(ret);
    }
}


void avs_device_power()
{
    AvsbusDevicePowerHandle p_handle;
	uint32_t pwr_data[AVSBUS_DEV_RAIL_TOTAL];
    avsbus_status_t ret;
    ret = AvsbusDeviceGetPowerHandle(&p_handle);
    if (ret != AVSBUS_SUCCESS) {
        printf("AvsbusDeviceGetPowerHandle Failed\n");
        SET_GLOBAL_TEST_STATUS(ret);
    }
    ret = AvsbusDeviceGetPower(p_handle, &pwr_data);
    if (ret != AVSBUS_SUCCESS) {
        printf("AvsbusDeviceGetPower Failed\n");
        SET_GLOBAL_TEST_STATUS(ret);
    } else {
        printf("Power(mW) P0:%d P1:%d\n", pwr_data[0], pwr_data[1]);
        if (pwr_data[0]+pwr_data[1] <= 0)
            SET_GLOBAL_TEST_STATUS(AVSBUS_ERR);
    }
    ret = AvsbusDeviceReleasePowerHandle(&p_handle);
    if (ret != AVSBUS_SUCCESS) {
        printf("AvsbusDeviceReleasePowerHandle Failed\n");
        SET_GLOBAL_TEST_STATUS(ret);
    }
}

int do_avsbus(int argc, char *argv[])
{
    int ret = 0, num = 0;

    if (argc == 1) {
        printf("Unknown command '%s'\n\n", argv[0]);
    }else if(argc == 2){
        if (strcmp(argv[1], "init") == 0) {
            AvsbusDeviceInitialize();
        }else if (strcmp(argv[1], "temp") == 0){
            avs_device_temp();
        }else if (strcmp(argv[1], "power") == 0){
            avs_device_power();
        }else if (strcmp(argv[1], "APC") == 0){
            AvsbusDeviceGetVoltage(AVS_CPU_CLUSTER);
        }else if (strcmp(argv[1], "CBF") == 0){
            AvsbusDeviceGetVoltage(AVS_CBF);
        }else {
            printf("Unknown command\n\n");
            ret = -1;
        }
    }else{
        if(strtoul(argv[2], NULL, 0) > 1055){
            printf("AVS Voltage %dmv is set too high!\n",strtoul(argv[2], NULL, 0));
        }else{
            if (strcmp(argv[1], "APC") == 0){
                AvsbusDeviceSetVoltage(AVS_CPU_CLUSTER, strtoul(argv[2], NULL, 0));
            }else if (strcmp(argv[1], "CBF") == 0){
                AvsbusDeviceSetVoltage(AVS_CBF, strtoul(argv[2], NULL, 0));
            }
        }
    }

    return ret;
}

MK_CMD(avsbus, do_avsbus, "avsbus initialization, set or get voltage, get temp or power",
    "avsbus init\n"
    "    - avsbus initialization\n"
    "avsbus APC voltage\n"
    "    - set APC rail voltage(mV)\n"
    "avsbus CBF voltage\n"
    "    - set CBF rail voltage(mV)\n"
    "avsbus temp\n"
    "    - read apc and cbf rail temp\n"
    "avsbus power\n"
    "    - read apc and cbf rail power\n"
);
