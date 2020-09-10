/*
*
* SPDX-License-Identifier: GPL-2.0
*
* Copyright (C) 2011-2019 ARM or its affiliates
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 2.
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#include "acamera_calib_mgr.h"


// ------------ 3A & iridix
static uint8_t _calibration_evtolux_probability_enable[] = {1};

static uint8_t _calibration_awb_avg_coef[] = {20};

static uint8_t _calibration_iridix_avg_coef[] = {14};

static uint16_t _calibration_ccm_one_gain_threshold[] = {4 * 255 - 1}; //5* 255-1   256* 4

static uint8_t _calibration_iridix_strength_maximum[] = {64}; // max 255

static uint16_t _calibration_iridix_min_max_str[] = {0};

static uint32_t _calibration_iridix_ev_lim_full_str[] = {345000}; // 245000 log2 id

static uint32_t _calibration_iridix_ev_lim_no_str[] = {3200000, 3200000}; //280000   log2 id

static uint8_t _calibration_ae_correction[] = {130, 128, 119, 115, 115, 105, 105, 105, 100};

static uint32_t _calibration_ae_exposure_correction[] = {10, 1000, 350000, 423426, 750000, 890431, 1540000, 4048902, 5000000};


// ------------Noise reduction ----------------------//
static uint16_t _calibration_sinter_strength[][2] = {
    {0 * 256, 25},
    {1 * 256, 35},
    {2 * 256, 35},
    {3 * 256, 40},
    {4 * 256, 40},
    {5 * 256, 40},
    {6 * 256, 55}};

static uint16_t _calibration_sinter_strength_MC_contrast[][2] = {
    {0 * 256, 0}};

static uint16_t _calibration_sinter_strength1[][2] = {
    {0 * 256, 255},
    {1 * 256, 255},
    {2 * 256, 255},
    {3 * 256, 255},
    {4 * 256, 255},
    {5 * 256, 255},
    {6 * 256, 255}};

static uint16_t _calibration_sinter_strength4[][2] = {
    {0 * 256, 255},
    {1 * 256, 255},
    {2 * 256, 255},
    {3 * 256, 255},
    {4 * 256, 255},
    {5 * 256, 255},
    {6 * 256, 255}};

static uint16_t _calibration_sinter_thresh1[][2] = {
    {0 * 256, 25},
    {1 * 256, 55},
    {2 * 256, 90},
    {3 * 256, 150},
    {4 * 256, 180},
    {5 * 256, 200},
    {6 * 256, 200}};

static uint16_t _calibration_sinter_thresh4[][2] = {
    {0 * 256, 40},
    {1 * 256, 80},
    {2 * 256, 120},
    {3 * 256, 150},
    {4 * 256, 150},
    {5 * 256, 230},
    {6 * 256, 230}};

static uint16_t _calibration_sinter_intConfig[][2] = {
    {0 * 256, 10},
    {1 * 256, 10},
    {2 * 256, 8},
    {3 * 256, 8},
    {4 * 256, 7},
    {5 * 256, 5},
    {6 * 256, 4}};

static uint16_t _calibration_sinter_params[] = {
    0, // Int select
};

static uint8_t _calibration_sinter_radial_lut[] = {0, 0, 0, 0, 0, 0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24};

static uint16_t _calibration_sinter_radial_params[] = {
    0,        // rm_enable
    1920 / 2, // rm_centre_x
    1080 / 2, // rm_centre_y
    1770      // rm_off_centre_mult: round( ( 2 ^ 31 ) / ( ( rm_centre_x ^ 2 ) + ( rm_centre_y ^ 2 ) ) )
};

// ------------ Sharpening and demosaic
static uint16_t _calibration_demosaic_config[] = {
    2048, // AA Offset, Offset for angular blending threshold, default =
    // 0x800
    170,   // AA Slope, Slope of angular blending threshold in 4.4 logarithmic format
    80,    // AA Thresh, Threshold for the range of angular blending
    0,     // AC Offset, Offset for AC blending threshold in signed 2.9 format
    207,   // AC Slope, Slope of AC blending threshold in linear format 2.6
    435,   // AC Thresh, Threshold for the range of AC blending in signed 2.9 format
    125,   // FC Alias Slope, (strength) of false colour correction after blending with saturation value in 2.6 unsigned format
    100,   // FC Alias Thresh, Threshold of false colour correction after blending with saturation valuet in in 0.8 unsigned format
    130,   // FC Slope, Slope (strength) of false color correction
    96,    // lum_thresh, Luminance threshold for directional sharpening
    32500, // min_d_strength, Min threshold for the directional L_L in signed 2's complement s.12 format
    32500, // min_ud_strength, Min threshold for the un-directional L_Lu in signed 2's complement s.12 format
    0,     // NP off, Noise profile black level offset
    0,     // NP off reflect Defines how values below black level are obtained.
    // 0: Repeat the first table entry.
    // 1: Reflect the noise profile curve below black level.
    0,    // np_offset Noise profile offset in logarithmic 4.4 format
    25,   // sad_amp, Sad amplifier in unsigned 4.4 format
    0,    // Sat Offset, Offset for saturation blending threshold in signed 2.9 format
    93,   // Sat Slope, Slope of saturation blending threshold in linear format 2.6
    369,  // Sat Thresh, Threshold for the range of saturation blending in signed 2.9 format
    0,    // UU Offset, Offset for undefined blending threshold
    80,   // UU Thresh, Threshold for the range of undefined blending
    2048, // VA Offset, Offset for VA blending threshold
    170,  // VA Slope, Slope of VH-AA (VA) blending threshold in 4.4 logarithmic format
    80,   // VA Thresh, Threshold for the range of VA blending
    2048, // VH Offset, Offset for vertical/horizontal blending threshold
    170,  // VH Slope, Slope of vertical/horizontal blending threshold in 4.4 logarithmic format
    80,   // VH Thresh, Threshold for the range of vertical/horizontal blending
    1,    // sharpen_alg_select,

};


static uint16_t _calibration_sharp_alt_d[][2] = {
    {0 * 256, 32},
    {1 * 256, 25},
    {2 * 256, 25},
    {3 * 256, 18},
    {4 * 256, 3},
    {5 * 256, 3},
    {6 * 256, 3}};

static uint16_t _calibration_sharp_alt_ud[][2] = { // low
    {0 * 256, 0},
    {1 * 256, 0},
    {2 * 256, 0},
    {3 * 256, 0},
    {4 * 256, 0},
    {5 * 256, 0},
    {6 * 256, 0}};

static uint16_t _calibration_sharp_alt_du[][2] = { // medium
    {0 * 256, 30},
    {1 * 256, 20},
    {2 * 256, 3},
    {3 * 256, 2},
    {4 * 256, 2},
    {5 * 256, 1},
    {6 * 256, 1}};

static uint16_t _calibration_demosaic_uu_slope[][2] = {
    {0 * 256, 1},
    {1 * 256, 1},
    {2 * 256, 1},
    {3 * 256, 1},
    {4 * 256, 1},
    {5 * 256, 1},
    {6 * 256, 1}};

static uint16_t _calibration_mesh_shading_strength[][2] = {
    {0 * 256, 4096},
    {1 * 256, 4096},
    {2 * 256, 4096},
    {3 * 256, 4000},
    {4 * 256, 1000},
    {5 * 256, 500}};

static uint16_t _calibration_saturation_strength[][2] = {
    {0 * 256, 128},
    {1 * 256, 128},
    {2 * 256, 108},
    {3 * 256, 100},
    {4 * 256, 95},
    {5 * 256, 90},
    {6 * 256, 90}};

// ----------- Frame stitching motion
static uint16_t _calibration_stitching_lm_np[][2] = {
    {0, 540},
    {3 * 256, 1458},
    {4 * 256, 1458},
    {5 * 256, 3000}};

static uint16_t _calibration_stitching_lm_mov_mult[][2] = {
    {0, 128},
    {2 * 256 - 128, 20},
    {5 * 256, 8},
};

static uint16_t _calibration_stitching_lm_med_noise_intensity_thresh[][2] = {
    {0, 32},
    {6 * 256, 32},
    {8 * 256, 4095},
};

static uint16_t _calibration_stitching_ms_np[][2] = {
    {0, 3680},
    {1 * 256, 3680},
    {2 * 256, 2680}};

static uint16_t _calibration_stitching_ms_mov_mult[][2] = {
    {0, 128},
    {1 * 256, 128},
    {2 * 256, 100}};

static uint16_t _calibration_dp_slope[][2] = {
    {0 * 256, 100},
    {1 * 256, 300},
    {2 * 256, 500},
    {3 * 256, 700},
    {4 * 256, 900},
    {5 * 256, 1050},
    {6 * 256, 1050}};

static uint16_t _calibration_dp_threshold[][2] = {
    {0 * 256, 255},
    {1 * 256, 255},
    {2 * 256, 175},
    {3 * 256, 120},
    {4 * 256, 25},
    {5 * 256, 10},
    {6 * 256, 10}};

static uint16_t _calibration_AWB_bg_max_gain[][2] = {
    {7 * 256, 600}};

static uint32_t _calibration_cmos_control[] = {
    0,   // enable antiflicker
    50,  // antiflicker frequency
    0,   // manual integration time
    0,   // manual sensor analog gain
    0,   // manual sensor digital gain
    0,   // manual isp digital gain
    0,   // manual max integration time
    0,   // manual exposure ratio
    0,   // max integration time
    127, // max sensor AG
    0,   // max sensor DG
    40,  // max isp DG
    255, // max exposure ratio
    0,   // integration time.
    0,   // sensor analog gain. log2 fixed - 5 bits
    0,   // sensor digital gain. log2 fixed - 5 bits
    0,   // isp digital gain. log2 fixed - 5 bits
    0,   // analog_gain_last_priority
    0,   // analog_gain_reserve
    0    // isp_gain_reserve
};

static uint32_t _calibration_iridix8_strength_dk_enh_control[] = {
    20,      // dark_prc
    95,      // bright_prc
    800,     // min_dk: minimum dark enhancement
    1000,    // max_dk: maximum dark enhancement
    8,       // pD_cut_min: minimum intensity cut for dark regions in which dk_enh will be applied
    20,      // pD_cut_max: maximum intensity cut for dark regions in which dk_enh will be applied
    30 << 8, // dark contrast min
    50 << 8, // dark contrast max
    0,       // min_str: iridix strength in percentage //26
    40,      // max_str: iridix strength in percentage: 50 = 1x gain. 100 = 2x gain                //50
    40,      // dark_prc_gain_target: target in histogram ( percentage ) for dark_prc after iridix is applied
    30 << 8, // contrast_min: clip factor of strength for LDR scenes.
    40 << 8, // contrast_max: clip factor of strength for HDR scenes.
    20,      // max iridix gain
    0        // print debug
};

static uint16_t _calibration_iridix8_extended_control[] = {
    1,   // filter_mux: Iridix algorithm: 0 - Iridix v7, 1 - Iridix v8
    10,  // svariance
    220, // bright_pr
    180, // contrast
    0,   // Initial inroi strength value
    512, // Initial outroi strength value
    7,   // variance intensity
    15,  //  variance space
    2,   //FWD Iridix gamma processing select: 0=pass through 1=gamma_dl 2=sqrt 3=gamma_lut.
    2,   //REV Iridix gamma processing select: 0=pass through 1=gamma_dl 2=sqrt 3=gamma_lut.
    64,  // slope min
    128, // slope max
};

static uint32_t _calibration_ae_control[] = {
    20,  // AE convergance
    523, // LDR AE target -> this should match the 18% grey of teh output gamma
    0,   // AE tail weight
    77,  // WDR mode only: Max percentage of clipped pixels for long exposure: WDR mode only: 256 = 100% clipped pixels
    15,  // WDR mode only: Time filter for exposure ratio
    100, // control for clipping: bright percentage (bright_prc) of pixels that should be below hi_target_prc
    99,  // control for clipping: highlights percentage (hi_target_prc): target for tail of histogram
    1,   // 1:0 enable | disable iridix global gain.
    0,   // AE tolerance
};

static uint16_t _calibration_ae_control_HDR_target[][2] = {
    //* {0 * 256, 11}, // HDR AE target should not be higher than LDR target
    {0 * 256, 450},
};

static uint16_t _calibration_exposure_ratio_adjustment[][2] = {
    //contrast, adjustment
    {1 * 256, 256},
    {16 * 256, 256},
    {32 * 256, 256},
    {64 * 256, 256}};

static uint16_t _calibration_fs_mc_off[] = {
    8 * 256, // gain_log2 threshold. if gain is higher than the current gain_log2. mc off mode will be enabed.
};

static uint16_t _calibration_ae_zone_wght_hor[] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
static uint16_t _calibration_ae_zone_wght_ver[] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
static uint16_t _calibration_awb_zone_wght_hor[] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
static uint16_t _calibration_awb_zone_wght_ver[] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};


// CALIBRATION_CMOS_EXP_PARTITION
static uint32_t _calibration_cmos_exp_partition[10][2] = {
    {0, 10},
    {1, 2},
    {0, 30},
    {1, 4},
    {0, 60},
    {1, 6},
    {0, 100},
    {1, 8},
    {0, 0},
    {1, 0}};

// CALIBRATION_DEFECT_PIXEL
static uint32_t _calibration_defect_pixel[] = {
    5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
};                                                                                                                                                                                                  // 1024

// RGB 2 RGB conversion coef for S/HS formats
static uint16_t _calibration_rgb2rgb_hs_conversion[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static uint16_t _calibration_rgb2rgb_hs_conversion_b[3] = {128 << 6, 0, 128 << 6};

// RGB 2 RGB conversion coef for S* formats
static uint16_t _calibration_rgb2rgb_s2_conversion[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static uint16_t _calibration_rgb2rgb_s2_conversion_b[3] = {128 << 6, 0, 128 << 6};

// color matrix calibrations
static uint16_t _calibration_color_matrix_yuv[12] = {66, 129, 25, 32806, 32843, 112, 112, 32862, 32786, 0, 0, 0};
static uint16_t _calibration_color_matrix_b_yuv[3] = {0, 128 << 6, 128 << 6};
static uint16_t _calibration_color_matrix_luv[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint16_t _calibration_color_matrix_b_luv[3] = {0, 0, 0};

// Calibration for decompander fsm.
// Decompander fsm is responsible for configuration of:
// input formatter, gamma fe and Histogram NEQ LUT.
static uint8_t _calibration_decompander_control[] = {
    0, // Enable input_formatter
    0, // Enable Histogram NEQ LUT
    1, // Histogram NEQ LUT position 0 = before histogram, 1 = before white balance
    0, // Enable gamma fe LUT
    1, // Enable gamma fe compander (SQ or DL)
    0, // Enable gamma be LUT
    1, // Enable gamma be compander (SQ or DL)
};

// CALIBRATION INPUT FORMATTER
static uint16_t _calibration_input_formatter[] = {
    3,             // Mode 3 = Companding curve with knee points.
    2,             // input1 bitwidth select: 2 = 12 bits
    0,             // input2 bitwidth select: Not used.
    0,             // input3 bitwidth select: Not used.
    0,             // input4 bitwidth select: Not used.
    1,             // input1 alignment: 1 = MSB aligned.
    0,             // input2 alignment: Not used.
    0,             // input3 alignment: Not used.
    0,             // input4 alignment: Not used.
    0,             // Black level
    ( 2048 << 4 ), // knee_point0: 12 bit placed in to 16 MSB.
    ( 3040 << 4 ), // knee_point1: 12 bit placed in to 16 MSB.
    ( 3040 << 4 ), // knee_point2: 12 bit placed in to 16 MSB.
    4,             // slope0: 16x    (1 * 16)
    10,            // slope1: 1024x  (64 * 16)
    14,            // slope2: 16384x (1024 * 16)
    14,            // slope2: 16384x (1024 * 16)
};

// CALIBRATION CALIBRATION NEQ LUT {x, y}.
// NEQ LUT is used and configured by decompander fsm.
static uint32_t _calibration_neq_lut[][2] = {
    {0, 0},             // x0, y0
    {131072, 370728},   // x1, y1
    {262144, 524288},   // x2, y2
    {393216, 642119},   // x3, y3
    {524288, 741455},   // x4, y4
    {655359, 828971},   // x5, y5
    {786431, 908093},   // x6, y6
    {917503, 980852},   // x7, y7
    {1048575, 1048575}, // x8, y8
};

// CALIBRATION_GAMMA_BE0/BE1 --- only used for non linear non fs_line modes
static uint32_t _calibration_gamma_be0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //33
static uint32_t _calibration_gamma_be1[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64
    0};                                                                                                                                                                                             //257

static uint32_t _calibration_iridix_gtm_lut_x[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint32_t _calibration_iridix_gtm_lut_y[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


static uint32_t _calibration_gamma_black_levels[] = {
    266240, // FE Black level in / BE Black level out
    1000,   // FE Black level out / BE Black level in
    0,      // Alpha, r0 only.
};


static uint16_t _calibration_raw_frontend_config[] = {
    32768, // dpdev threshold
    0,     // dp line thresh
    285,   // ge slope
    128,   // ge sens
    170,   // ge threshold
    64,    // ge strength
    0,     // Thresh Long
    0,     // Thresh Short
};


static uint16_t _calibration_noise_profile_config[] = {
    0,    // Thresh1
    0,    // Thresh2
    0,    // Thresh3
    1,    // Use exp mask
    64,   // Hlog exp rat max Threshold for determining long/short exposure data
    0x0F, // Hlog exp rat 0 1 max diff Threshold for determining long/short exposure data
    0x0F, // Hlog exp rat 0 2 max diff Threshold for determining long/short exposure data
    0x0F, // Hlog exp rat 0 3 max diff Threshold for determining long/short exposure data

};


static uint32_t _calibration_wdr_stitch_config[] = {
    60947,   //LM Thresh high
    49151,   //LM Thresh low
    60947,   //MS Thresh high
    49151,   //MS Thresh low
    60947,   //SVS Thresh high
    49151,   //SVS Thresh low
    8388608, //Consistency thresh lvl
    256,     //Consistency thresh mov
    3500,    //Mcoff L max, r1 only
    3500,    //Mcoff M max, r1 only
    3500,    //Mcoff S max, r1 only
    3500,    //Mcoff VS max, r1 only
};


static uint32_t _calibration_statistics_config[] = {

    0,     //Black Level AWB
    16383, //White Level AWB

};

// Custom settings, this table is generated by the ACT.
// The format of this is as follows:
// {<address offset>, <value>, <mask>, <length>}
// The sequence is terminated by a row set to 0.
static uint32_t _calibration_custom_settings_context[][4] = {
    {0x0000, 0x0000, 0x0000, 0x0000}};

#define DECLARE_LOOKUP_TAB_1D( x ) static LookupTable x = {.ptr = _##x, .rows = 1, .cols = sizeof( _##x ) / sizeof( _##x[0] ), .width = sizeof( _##x[0] )}
#define DECLARE_LOOKUP_TAB_2D( x ) static LookupTable x = {.ptr = _##x, .rows = sizeof( _##x ) / sizeof( _##x[0] ), .cols = sizeof( _##x[0] ) / sizeof( _##x[0][0] ), .width = sizeof( _##x[0][0] )}

DECLARE_LOOKUP_TAB_1D( calibration_ae_control );
DECLARE_LOOKUP_TAB_1D( calibration_ae_correction );
DECLARE_LOOKUP_TAB_1D( calibration_ae_exposure_correction );
DECLARE_LOOKUP_TAB_1D( calibration_ae_zone_wght_hor );
DECLARE_LOOKUP_TAB_1D( calibration_ae_zone_wght_ver );
DECLARE_LOOKUP_TAB_1D( calibration_awb_avg_coef );
DECLARE_LOOKUP_TAB_1D( calibration_awb_zone_wght_hor );
DECLARE_LOOKUP_TAB_1D( calibration_awb_zone_wght_ver );
DECLARE_LOOKUP_TAB_1D( calibration_ccm_one_gain_threshold );
DECLARE_LOOKUP_TAB_1D( calibration_cmos_control );
DECLARE_LOOKUP_TAB_1D( calibration_color_matrix_b_luv );
DECLARE_LOOKUP_TAB_1D( calibration_color_matrix_b_yuv );
DECLARE_LOOKUP_TAB_1D( calibration_color_matrix_luv );
DECLARE_LOOKUP_TAB_1D( calibration_color_matrix_yuv );
DECLARE_LOOKUP_TAB_1D( calibration_decompander_control );
DECLARE_LOOKUP_TAB_1D( calibration_defect_pixel );
DECLARE_LOOKUP_TAB_1D( calibration_evtolux_probability_enable );
DECLARE_LOOKUP_TAB_1D( calibration_fs_mc_off );
DECLARE_LOOKUP_TAB_1D( calibration_gamma_be0 );
DECLARE_LOOKUP_TAB_1D( calibration_gamma_be1 );
DECLARE_LOOKUP_TAB_1D( calibration_input_formatter );
DECLARE_LOOKUP_TAB_1D( calibration_iridix8_extended_control );
DECLARE_LOOKUP_TAB_1D( calibration_iridix8_strength_dk_enh_control );
DECLARE_LOOKUP_TAB_1D( calibration_iridix_avg_coef );
DECLARE_LOOKUP_TAB_1D( calibration_iridix_ev_lim_full_str );
DECLARE_LOOKUP_TAB_1D( calibration_iridix_ev_lim_no_str );

DECLARE_LOOKUP_TAB_1D( calibration_iridix_gtm_lut_x );
DECLARE_LOOKUP_TAB_1D( calibration_iridix_gtm_lut_y );
DECLARE_LOOKUP_TAB_1D( calibration_iridix_min_max_str );
DECLARE_LOOKUP_TAB_1D( calibration_iridix_strength_maximum );
DECLARE_LOOKUP_TAB_1D( calibration_rgb2rgb_hs_conversion );
DECLARE_LOOKUP_TAB_1D( calibration_rgb2rgb_hs_conversion_b );
DECLARE_LOOKUP_TAB_1D( calibration_rgb2rgb_s2_conversion );
DECLARE_LOOKUP_TAB_1D( calibration_rgb2rgb_s2_conversion_b );
DECLARE_LOOKUP_TAB_1D( calibration_sinter_params );
DECLARE_LOOKUP_TAB_1D( calibration_sinter_radial_lut );
DECLARE_LOOKUP_TAB_1D( calibration_sinter_radial_params );
DECLARE_LOOKUP_TAB_2D( calibration_ae_control_HDR_target );
DECLARE_LOOKUP_TAB_2D( calibration_AWB_bg_max_gain );
DECLARE_LOOKUP_TAB_2D( calibration_cmos_exp_partition );
DECLARE_LOOKUP_TAB_2D( calibration_demosaic_uu_slope );
DECLARE_LOOKUP_TAB_2D( calibration_dp_slope );
DECLARE_LOOKUP_TAB_2D( calibration_dp_threshold );
DECLARE_LOOKUP_TAB_2D( calibration_exposure_ratio_adjustment );
DECLARE_LOOKUP_TAB_2D( calibration_mesh_shading_strength );
DECLARE_LOOKUP_TAB_2D( calibration_neq_lut );
DECLARE_LOOKUP_TAB_2D( calibration_saturation_strength );
DECLARE_LOOKUP_TAB_2D( calibration_sharp_alt_d );
DECLARE_LOOKUP_TAB_2D( calibration_sharp_alt_du );
DECLARE_LOOKUP_TAB_2D( calibration_sharp_alt_ud );
DECLARE_LOOKUP_TAB_2D( calibration_sinter_intConfig );
DECLARE_LOOKUP_TAB_2D( calibration_sinter_strength );
DECLARE_LOOKUP_TAB_2D( calibration_sinter_strength1 );
DECLARE_LOOKUP_TAB_2D( calibration_sinter_strength4 );
DECLARE_LOOKUP_TAB_2D( calibration_sinter_strength_MC_contrast );
DECLARE_LOOKUP_TAB_2D( calibration_sinter_thresh1 );
DECLARE_LOOKUP_TAB_2D( calibration_sinter_thresh4 );
DECLARE_LOOKUP_TAB_2D( calibration_stitching_lm_med_noise_intensity_thresh );
DECLARE_LOOKUP_TAB_2D( calibration_stitching_lm_mov_mult );
DECLARE_LOOKUP_TAB_2D( calibration_stitching_lm_np );
DECLARE_LOOKUP_TAB_2D( calibration_stitching_ms_mov_mult );
DECLARE_LOOKUP_TAB_2D( calibration_stitching_ms_np );
DECLARE_LOOKUP_TAB_1D( calibration_demosaic_config );
DECLARE_LOOKUP_TAB_1D( calibration_gamma_black_levels );
DECLARE_LOOKUP_TAB_1D( calibration_raw_frontend_config );
DECLARE_LOOKUP_TAB_1D( calibration_noise_profile_config );
DECLARE_LOOKUP_TAB_1D( calibration_wdr_stitch_config );
DECLARE_LOOKUP_TAB_1D( calibration_statistics_config );
DECLARE_LOOKUP_TAB_2D( calibration_custom_settings_context );

int32_t get_calibrations_dynamic_linear_ar0231( void *param )
{
    int32_t result = 0;
    if ( param != 0 ) {
        ACameraCalibrations *c = (ACameraCalibrations *)param;

        c->calibrations[CALIBRATION_STITCHING_LM_MED_NOISE_INTENSITY] = &calibration_stitching_lm_med_noise_intensity_thresh;
        c->calibrations[CALIBRATION_EXPOSURE_RATIO_ADJUSTMENT] = &calibration_exposure_ratio_adjustment;
        c->calibrations[CALIBRATION_SINTER_STRENGTH_MC_CONTRAST] = &calibration_sinter_strength_MC_contrast;
        c->calibrations[CALIBRATION_SINTER_PARAMS] = &calibration_sinter_params;
        c->calibrations[CALIBRATION_SINTER_RADIAL_LUT] = &calibration_sinter_radial_lut;
        c->calibrations[CALIBRATION_SINTER_RADIAL_PARAMS] = &calibration_sinter_radial_params;
        c->calibrations[CALIBRATION_AWB_BG_MAX_GAIN] = &calibration_AWB_bg_max_gain;
        c->calibrations[CALIBRATION_IRIDIX8_STRENGTH_DK_ENH_CONTROL] = &calibration_iridix8_strength_dk_enh_control;

        c->calibrations[CALIBRATION_IRIDIX8_EXTENDED_CONTROL] = &calibration_iridix8_extended_control;
        c->calibrations[CALIBRATION_CMOS_CONTROL] = &calibration_cmos_control;
        c->calibrations[CALIBRATION_DP_SLOPE] = &calibration_dp_slope;
        c->calibrations[CALIBRATION_DP_THRESHOLD] = &calibration_dp_threshold;
        c->calibrations[CALIBRATION_STITCHING_LM_MOV_MULT] = &calibration_stitching_lm_mov_mult;
        c->calibrations[CALIBRATION_STITCHING_LM_NP] = &calibration_stitching_lm_np;
        c->calibrations[CALIBRATION_STITCHING_MS_MOV_MULT] = &calibration_stitching_ms_mov_mult;
        c->calibrations[CALIBRATION_STITCHING_MS_NP] = &calibration_stitching_ms_np;
        c->calibrations[CALIBRATION_EVTOLUX_PROBABILITY_ENABLE] = &calibration_evtolux_probability_enable;
        c->calibrations[CALIBRATION_AWB_AVG_COEF] = &calibration_awb_avg_coef;
        c->calibrations[CALIBRATION_IRIDIX_AVG_COEF] = &calibration_iridix_avg_coef;
        c->calibrations[CALIBRATION_IRIDIX_STRENGTH_MAXIMUM] = &calibration_iridix_strength_maximum;
        c->calibrations[CALIBRATION_IRIDIX_MIN_MAX_STR] = &calibration_iridix_min_max_str;
        c->calibrations[CALIBRATION_IRIDIX_EV_LIM_FULL_STR] = &calibration_iridix_ev_lim_full_str;
        c->calibrations[CALIBRATION_IRIDIX_EV_LIM_NO_STR] = &calibration_iridix_ev_lim_no_str;
        c->calibrations[CALIBRATION_AE_CORRECTION] = &calibration_ae_correction;
        c->calibrations[CALIBRATION_AE_EXPOSURE_CORRECTION] = &calibration_ae_exposure_correction;
        c->calibrations[CALIBRATION_SINTER_STRENGTH] = &calibration_sinter_strength;
        c->calibrations[CALIBRATION_SINTER_STRENGTH1] = &calibration_sinter_strength1;
        c->calibrations[CALIBRATION_SINTER_STRENGTH4] = &calibration_sinter_strength4;
        c->calibrations[CALIBRATION_SINTER_THRESH1] = &calibration_sinter_thresh1;
        c->calibrations[CALIBRATION_SINTER_THRESH4] = &calibration_sinter_thresh4;
        c->calibrations[CALIBRATION_SINTER_INTCONFIG] = &calibration_sinter_intConfig;
        c->calibrations[CALIBRATION_SHARP_ALT_D] = &calibration_sharp_alt_d;
        c->calibrations[CALIBRATION_SHARP_ALT_UD] = &calibration_sharp_alt_ud;
        c->calibrations[CALIBRATION_SHARP_ALT_DU] = &calibration_sharp_alt_du;
        c->calibrations[CALIBRATION_DEMOSAIC_UU_SLOPE] = &calibration_demosaic_uu_slope;
        c->calibrations[CALIBRATION_MESH_SHADING_STRENGTH] = &calibration_mesh_shading_strength;
        c->calibrations[CALIBRATION_SATURATION_STRENGTH] = &calibration_saturation_strength;
        c->calibrations[CALIBRATION_CCM_ONE_GAIN_THRESHOLD] = &calibration_ccm_one_gain_threshold;
        c->calibrations[CALIBRATION_AE_CONTROL] = &calibration_ae_control;
        c->calibrations[CALIBRATION_AE_CONTROL_HDR_TARGET] = &calibration_ae_control_HDR_target;
        c->calibrations[CALIBRATION_AE_ZONE_WGHT_HOR] = &calibration_ae_zone_wght_hor;
        c->calibrations[CALIBRATION_AE_ZONE_WGHT_VER] = &calibration_ae_zone_wght_ver;
        c->calibrations[CALIBRATION_AWB_ZONE_WGHT_HOR] = &calibration_awb_zone_wght_hor;
        c->calibrations[CALIBRATION_AWB_ZONE_WGHT_VER] = &calibration_awb_zone_wght_ver;
        c->calibrations[CALIBRATION_FS_MC_OFF] = &calibration_fs_mc_off;

        c->calibrations[CALIBRATION_CMOS_EXP_PARTITION] = &calibration_cmos_exp_partition;
        c->calibrations[CALIBRATION_DEFECT_PIXEL] = &calibration_defect_pixel;
        c->calibrations[CALIBRATION_DECOMPANDER_CONTROL] = &calibration_decompander_control;
        c->calibrations[CALIBRATION_INPUT_FORMATTER] = &calibration_input_formatter;
        c->calibrations[CALIBRATION_NEQ_LUT] = &calibration_neq_lut;
        c->calibrations[CALIBRATION_RGB2RGB_HS_CONVERSION] = &calibration_rgb2rgb_hs_conversion;
        c->calibrations[CALIBRATION_RGB2RGB_HS_CONVERSION_B] = &calibration_rgb2rgb_hs_conversion_b;
        c->calibrations[CALIBRATION_RGB2RGB_S2_CONVERSION] = &calibration_rgb2rgb_s2_conversion;
        c->calibrations[CALIBRATION_RGB2RGB_S2_CONVERSION_B] = &calibration_rgb2rgb_s2_conversion_b;
        c->calibrations[CALIBRATION_COLOR_MATRIX_YUV_PRESETS] = &calibration_color_matrix_yuv;
        c->calibrations[CALIBRATION_COLOR_MATRIX_B_YUV_PRESETS] = &calibration_color_matrix_b_yuv;
        c->calibrations[CALIBRATION_COLOR_MATRIX_LUV_PRESETS] = &calibration_color_matrix_luv;
        c->calibrations[CALIBRATION_COLOR_MATRIX_B_LUV_PRESETS] = &calibration_color_matrix_b_luv;
        c->calibrations[CALIBRATION_GAMMA_BE0] = &calibration_gamma_be0;
        c->calibrations[CALIBRATION_GAMMA_BE1] = &calibration_gamma_be1;
        c->calibrations[CALIBRATION_IRIDIX_GTM_LUT_X] = &calibration_iridix_gtm_lut_x;
        c->calibrations[CALIBRATION_IRIDIX_GTM_LUT_Y] = &calibration_iridix_gtm_lut_y;
        c->calibrations[CALIBRATION_DEMOSAIC_CONFIG] = &calibration_demosaic_config;
        c->calibrations[CALIBRATION_GAMMA_BLACK_LEVELS] = &calibration_gamma_black_levels;
        c->calibrations[CALIBRATION_RAW_FRONTEND_CONFIG] = &calibration_raw_frontend_config;
        c->calibrations[CALIBRATION_NOISE_PROFILE_CONFIG] = &calibration_noise_profile_config;
        c->calibrations[CALIBRATION_WDR_STITCH_CONFIG] = &calibration_wdr_stitch_config;
        c->calibrations[CALIBRATION_STATISTICS_CONFIG] = &calibration_statistics_config;
        c->calibrations[CALIBRATION_CUSTOM_SETTINGS] = &calibration_custom_settings_context;
    } else {
        result = -1;
    }
    return result;
}
