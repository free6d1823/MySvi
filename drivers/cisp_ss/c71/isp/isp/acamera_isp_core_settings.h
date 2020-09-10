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

#if !defined( __ACAMERA_ISP_CORE_SETTINGS_H__ )
#define __ACAMERA_ISP_CORE_SETTINGS_H__

#define ISP_AWB_HOR_ZONES_MAX 15
#define ISP_AWB_VERT_ZONES_MAX 15
#define ISP_MCFE_HWIF_MAX_OUTPUTS 3
#define ISP_MCFE_MAX_INPUT 4
#define ISP_MCFE_MAX_OUT_BUF 3//64
#define ISP_MCFE_MAX_RAW_BUF 3//32
#define ISP_MCFE_MAX_SLOT 1//16
#define ISP_MCFE_START_SLOT_IDLE 0xff
#define ISP_METERING_ANTIFOG_HISTOGRAM_OFFSET 8448
#define ISP_METERING_HISTOGRAM_SIZE_BINS 1024
#define ISP_METERING_HISTOGRAM_SIZE_BYTES 2048
#define ISP_METERING_HISTOGRAM_STRIDE_BYTES 2112
#define ISP_METERING_HISTOGRAM_TAIL_SIZE_REGS 12
#define ISP_METERING_OFFSET_AWB 1856
#define ISP_OUT_FORMAT_LUT_RGB_SIZE_REGS 257

#endif /* __ACAMERA_ISP_CORE_SETTINGS_H__*/
