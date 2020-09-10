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

#ifndef __ACAMERA_CALIB_MGR_H__
#define __ACAMERA_CALIB_MGR_H__

#include "acamera_calib_mgr_settings.h"
#include "acamera_math.h"

#include "util/math/acamera_math.h"

typedef struct LookupTable {
    const void *ptr;
    const uint16_t rows;
    const uint16_t cols;
    const uint16_t width;
} LookupTable;

// Calibration table
typedef struct _ACameraCalibrations {

    LookupTable *calibrations[CALIBRATION_TOTAL_SIZE];

} ACameraCalibrations;

// Calibration manager entry
typedef struct _acamera_calib_mgr_entry_t {
    int32_t initialized;
    int32_t ( *get_calibrations )( uint32_t wdr_mode, void *param );
    ACameraCalibrations c;
} acamera_calib_mgr_entry_t;

/**
 *   Initialize a calibration manager entry.
 *
 *   This function MUST be called before any other call to calibration manager. 
 *   It initializes a pointer to get_calibations_*() function and inits internal data. 
 *
 *   @param param - pointer to a get_calibations_*() function.
 *
 *   @return acamera_calib_mgr_entry_t pointer on success otherwise NULL
 */
acamera_calib_mgr_entry_t *acamera_calib_mgr_init( void *param );

/**
 *   Deinitialize a calibration manager entry.
 *
 *   @param entry - pointer to calibration manager entry.
 *
 *   @return none
 */
void acamera_calib_mgr_deinit( acamera_calib_mgr_entry_t *entry );

/**
 *   Update LUT tables of a calibration manager entry according to sensor mode.
 *
 *   @param entry - pointer to calibration manager entry.
 *   @param wdr_mode - sensor mode.
 *
 *   @return 0 on success otherwise -1
 */
int32_t acamera_calib_mgr_update( acamera_calib_mgr_entry_t *entry, uint32_t wdr_mode );

/**
 *   Check whether specified LUT exists in calibration manager entry.
 *
 *   @param entry - pointer to calibration manager entry.
 *   @param idx - LUT index
 *
 *   @return 1 if specified LUT exists otherwise 0
 */
int32_t calib_mgr_lut_exists( acamera_calib_mgr_entry_t *entry, uint32_t idx );

/**
 *   Get pointer to the specified LUT for read only operations.
 *   Pointer is const so treat data as read-only (do not recast to non-const)
 *i
 *inter to calibration manager entry.
 *index
 *i
 *   @return pointer to a LUT if specified LUT exists otherwise NULL
 */
const void *calib_mgr_lut_get( acamera_calib_mgr_entry_t *entry, uint32_t idx );

const uint8_t *calib_mgr_u8_lut_get( acamera_calib_mgr_entry_t *entry, uint32_t idx );

const uint16_t *calib_mgr_u16_lut_get( acamera_calib_mgr_entry_t *entry, uint32_t idx );

const uint32_t *calib_mgr_u32_lut_get( acamera_calib_mgr_entry_t *entry, uint32_t idx );

const modulation_entry_t *calib_mgr_mod16_lut_get( acamera_calib_mgr_entry_t *entry, uint32_t idx );

const modulation_entry_32_t *calib_mgr_mod32_lut_get( acamera_calib_mgr_entry_t *entry, uint32_t idx );

/**
 *   Get pointer to the specified LUT for read-write operations.
 *
 *   @param entry - pointer to calibration manager entry.
 *   @param idx - LUT index
 *
 *   @return pointer to a LUT if specified LUT exists otherwise NULL
 */
uint32_t *calib_mgr_u32_lut_get_rw( acamera_calib_mgr_entry_t *entry, uint32_t idx );

/**
 *   Get property of a specified LUT.
 *
 *   @param entry - pointer to calibration manager entry.
 *   @param idx - LUT index
 *
 *   @return property value on success otherwise 0
 */
uint32_t calib_mgr_lut_rows( acamera_calib_mgr_entry_t *entry, uint32_t idx );

uint32_t calib_mgr_lut_cols( acamera_calib_mgr_entry_t *entry, uint32_t idx );

uint32_t calib_mgr_lut_len( acamera_calib_mgr_entry_t *entry, uint32_t idx );

uint32_t calib_mgr_lut_width( acamera_calib_mgr_entry_t *entry, uint32_t idx );

uint32_t calib_mgr_lut_size( acamera_calib_mgr_entry_t *entry, uint32_t idx );

/**
 *   Read/Write LUT data from/to supplied buffer.
 *
 *   @param entry - pointer to calibration manager entry.
 *   @param data - pointer to a buffer.
 *   @param data_size - size of a buffer in bytes.
 *   @param idx - LUT index.
 *
 *   @return number of bytes read/written otherwise 0
 */
uint32_t calib_mgr_lut_write( acamera_calib_mgr_entry_t *entry, const void *data, uint32_t data_size, uint32_t idx );
uint32_t calib_mgr_lut_read( acamera_calib_mgr_entry_t *entry, void *data, uint32_t data_size, uint32_t idx );

#endif // __ACAMERA_CALIB_MGR_H__
