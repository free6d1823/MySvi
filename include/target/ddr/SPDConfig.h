#ifndef __SPDCONFIG_H__
#define __SPDCONFIG_H__

#include <stdint.h>
#include <target/compiler.h>

/*
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */

#pragma pack (1)
typedef struct {
   void * BufferBase;    //SPD Buffer base address
   uint32_t BufferSize;    //SPD Buffer Size
} __packed SPD_CONFIG_BUFFER_PROPS;

#define SPD_CONFIG_TABLE_VERSION 1
typedef struct {
   uint8_t  Version;       //Version of the header
   uint8_t  HeaderSize;    //Size of this header
   uint32_t TotalSize;     //Total size of all SPD and headers
   uint16_t NumDIMMs;      //Number of DIMMS in the system
} __packed SPD_CONFIG_TABLE_HEADER;

#define SPD_CONFIG_ENTRY_VERSION 1
typedef struct {
   uint8_t  Version;       //Version of the header
   uint8_t  HeaderSize;    //Size of this header
   uint16_t TotalSize;     //Total size of SPD and headers
   uint16_t Channel;       //Channel this SPD represents
   uint16_t Slot;          //Slot in the channel
} __packed SPD_CONFIG_ENTRY_HEADER;
#pragma pack ()

#endif //__SPDCONFIG_H__
