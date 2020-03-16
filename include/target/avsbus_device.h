/**
 * @file  AvsbusDevice.h
 *
 * @brief This file defines the PMBUS device datatypes.
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 * Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 */

#ifndef AVSBUS_DEVICE_H
#define AVSBUS_DEVICE_H

/*=========================================================================
                                   INCLUDES
===========================================================================*/

#include <asm/mach-qdf2400/spi/avsbus.h>
#define AVSBUS_GLOBAL_RAIL_ID(socket, rail_enum) (((socket)<<8) | (rail_enum))

/*=========================================================================
                             DEFINED CONSTANTS
===========================================================================*/
/* Types of AVSBus Rails supported by platform */
typedef enum {
    AVSBUS_DEV_RAIL_CBF = 0,
    AVSBUS_DEV_RAIL_APC,
    AVSBUS_DEV_RAIL_TOTAL,
}avsbus_dev_rail_t;

typedef void* AvsbusDevicePowerHandle;
typedef void* AvsbusDeviceTempHandle;

typedef enum
{
  AVS_CBF,
  AVS_CPU_CLUSTER,
}avs_apc_cpu_type;

/**
 * @function AvsbusDeviceInitialize
 *
 * @brief Initializes the AVSBUS device.
 *
 * @return avsbus_status_t
 */
avsbus_status_t AvsbusDeviceInitialize();


/**
 * @function AvsbusDeviceDeinitialize
 *
 * @brief Deinitializes the AVSBUS device.
 *
 * @return avsbus_status_t
 */
avsbus_status_t AvsbusDeviceDeinitialize();


/**
 * @function AvsbusDeviceSetVoltage
 *
 * @brief Sets the voltage level in microvolts
 *
 * @return void
 */
void AvsbusDeviceSetVoltage ( avs_apc_cpu_type cpu_type,
                              uint32_t uv_voltage);

/**
 * @function AvsbusDeviceGetVoltage
 *
 * @brief Populates current voltage in *uv_voltage and returns avsbus_status_t
 */
avsbus_status_t AvsbusDeviceGetVoltage (avs_apc_cpu_type cpu_type);

/**
 * @function AvsbusDeviceGetPowerHandle
 *
 * @brief Get a power telemetry handle
 */
avsbus_status_t AvsbusDeviceGetPowerHandle(AvsbusDevicePowerHandle *h);


/**
 * @function AvsbusDeviceRelasePowerHandle
 *
 * @brief Release a power telemetry handle
 */
avsbus_status_t AvsbusDeviceReleasePowerHandle(AvsbusDevicePowerHandle *h);


/**
 * @function AvsbusDeviceGetTempHandle
 *
 * @brief Get a temperature telemetry handle
 */
avsbus_status_t AvsbusDeviceGetTempHandle(AvsbusDeviceTempHandle *h);


/**
 * @function AvsbusDeviceReleaseTempHandle
 *
 * @brief Release a temperature telemetry handle
 */
avsbus_status_t AvsbusDeviceReleaseTempHandle(AvsbusDeviceTempHandle *h);


/**
 * @function: AvsbusDeviceGetPower
 *
 * @brief: Power will be reported in mW and it will be equal to the average
 * power measured since the last AvsbusDeviceGetPower call from the same client
 */
avsbus_status_t
AvsbusDeviceGetPower(AvsbusDevicePowerHandle h,
                     uint32_t (*power_data)[AVSBUS_DEV_RAIL_TOTAL]);


/**
 * @function: AvsbusDeviceGetTemp
 *
 * @brief: Populates 'data' with temperature data. Temperature is in dC(0.1C)
 */
avsbus_status_t
AvsbusDeviceGetTemp(AvsbusDeviceTempHandle h,
                    int16_t (*temp_data)[AVSBUS_DEV_RAIL_TOTAL]);

void avs_device_temp();

void avs_device_power();

int do_avsbus(int argc, char *argv[]);

#endif /* AVSBUS_DEVICE_H */
