//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2020] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifndef LIB_3A_CONFIG_H
#define LIB_3A_CONFIG_H

/* Versions */


// coverity[misra_c_2012_rule_2_5_violation] the version is for the user, it is not used internally.
#define LIB3A_VERSION_HASH 0x6b53bfb5UL
#define LIB3A_VERSION_STR "1.1"

// coverity[misra_c_2012_rule_2_5_violation] the version is for the user, it is not used internally.
#define LIB3A_VERSION_MAJOR 1

// coverity[misra_c_2012_rule_2_5_violation] the version is for the user, it is not used internally.
#define LIB3A_VERSION_MINOR 1

// coverity[misra_c_2012_rule_2_5_violation] the version is for the user, it is not used internally.
#define LIB3A_VERSION_PATCH

// coverity[misra_c_2012_rule_2_5_violation] the version is for the user, it is not used internally.
#define LIB3A_VERSION ( ( 1 * 10000 ) + ( 1 * 100 ) + )

/* General configuration */

#ifndef FIRMWARE_CONTEXT_NUMBER

/** The library allows the user to manually override this for convenience.*/
#define FIRMWARE_CONTEXT_NUMBER 16
#endif /*FIRMWARE_CONTEXT_NUMBER*/

/* Histogram */
#define ISP_FULL_HISTOGRAM_SIZE 1024

/* Math configuration*/
#define LOG2_GAIN_SHIFT 18

/* AWB configuration */
#define MAX_AWB_ZONES ( 33u * 33u )

/* Iridix configuration */
#define CALIBRATION_IRIDIX_AVG_COEF_INIT 0
#define IRIDIX_STRENGTH_TARGET 128

#endif /*LIB_3A_CONFIG_H*/
