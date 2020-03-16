#ifndef _MDDR_CA_EYEMEASURE_H_
#define _MDDR_CA_EYEMEASURE_H_

/*!****************************************************************************
*
* @copyright Copyright (c) 2017-2018 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file mddr_ca_eyemeasure.h
*
* @par Description:
*    This header contains the prototypes, derived data types, etc. associated
*    with the functionality of DDR eye-measurement in CA Margining mode.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <asm/plat-centriq/ddr/mddr.h>
#include <asm/plat-centriq/ddr/mddr_init.h>
#include <asm/mach/monaco/common/monaco_init.h>

/******************************************************************************
* Defined Constants and Macros
******************************************************************************/

// RCD Training modes - F0RC0C values (Note, these are indexed from 0 and not 1)
#define RCD_CA_TRN_MODE_ADDR_COMPOSITE           0
#define RCD_CA_TRN_MODE_CS0                      1
#define RCD_CA_TRN_MODE_CS1                      2
#define RCD_CA_TRN_MODE_CKE0                     3
#define RCD_CA_TRN_MODE_CKE1                     4
#define RCD_CA_TRN_MODE_ODT0                     5
#define RCD_CA_TRN_MODE_ODT1                     6

#define RCD_CA_TRN_MODE___M                      0x7

#define RCD_FORCOC_MAX_NUM_CATYPES               7


#define MDDR_TEST_SWITCH_TCA_TURN_ON_TRGR        0x1

#define MDDR_CLR_ERR_OUT_ALERT                   0x1

#define MDDR_CA_BUS_CNTL_EN_CA_PAR               0x3

#define MDDR_TEST_REG_CNTL_WR                    0x1

#define DDRPHY_ANIBx_ATXDLY_OFFSET               0x4000

#define DDRPHY_CA_ANIB_ATXDLY_ADDR_BIT_MASK      0x71E
#define DDRPHY_CA_ANIB_ATXDLY_CTRL_BIT_MASK      0xC1


#define RCD_RCW_INTL_VREFCA_MASK                 0X3F
#define DDRPHY_CA_ANIB_ATXDLY_MASK               0X5F

/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    This type provides a container for the CA eye margin result valid channel
*    and rank bitmap.
*
* @par Members
*
*                                  <PRE>
*    valid_ch_bitmap        Provides the bit map of the valid channels on which
*                            margining is performed.
*    valid_slot_bitmap      Provides the bit map of the valid slots on which
*                            margining is performed.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint16_t valid_ch_bitmap;
    uint16_t valid_slot_bitmap;
}mddr_ca_eyemargin_valid_bitmap_t;


/*!****************************************************************************
*
* @par Description
*    This type provides the CA eye measurement results per dimm slot.
*     This applies to both addr and ctrl eyes.
*
* @par Members
*
*                                  <PRE>
*    vref_trained            VREF trained position from the Control Word registers
*                             obtained after mission mode init.
*    delay_trained           Delay trained position from the Control Word registers
*                             obtained after mission mode init.
*    vref_edge_top           Top most valid VREF edge value for the eye
*    vref_edge_bottom        Bottom most valid VREF edge value for the eye
*    delay_edge_left         Left most valid delay edge value for the eye
*    delay_edge_right        Right most valid delay edge value for the eye
*    vref_eye_height         Overall eye height
*    delay_eye_width         Overall eye width
*    vref_margin_top         Top VREF margin/delta from the trained position
*    vref_margin_bottom      Bottom VREF margin/delta from the trained position
*    delay_margin_left       Left delay margin/delta from the trained position
*    delay_margin_right      Right delay margin/delta from the trained position
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t vref_trained;
    uint8_t delay_trained;
    uint8_t vref_edge_top;
    uint8_t vref_edge_bottom;
    uint8_t delay_edge_left;
    uint8_t delay_edge_right;
    uint8_t vref_eye_height;
    uint8_t delay_eye_width;
    uint8_t vref_margin_top;
    uint8_t vref_margin_bottom;
    uint8_t delay_margin_left;
    uint8_t delay_margin_right;
}mddr_ca_eyemargin_measure_t;


/*!****************************************************************************
*
* @par Description
*    This type provides the CA eye measurement results per dimm slot in ps/mV.
*     This applies to both addr and ctrl eyes.
*
* @par Members
*
*                                  <PRE>
*    vref_trained            VREF trained position from the Control Word registers
*                             obtained after mission mode init.
*    delay_trained           Delay trained position from the Control Word registers
*                             obtained after mission mode init.
*    vref_edge_top           Top most valid VREF edge value for the eye
*    vref_edge_bottom        Bottom most valid VREF edge value for the eye
*    delay_edge_left         Left most valid delay edge value for the eye
*    delay_edge_right        Right most valid delay edge value for the eye
*    vref_eye_height         Overall eye height
*    delay_eye_width         Overall eye width
*    vref_margin_top         Top VREF margin/delta from the trained position
*    vref_margin_bottom      Bottom VREF margin/delta from the trained position
*    delay_margin_left       Left delay margin/delta from the trained position
*    delay_margin_right      Right delay margin/delta from the trained position
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint32_t vref_trained;
    uint32_t delay_trained;
    uint32_t vref_edge_top;
    uint32_t vref_edge_bottom;
    uint32_t delay_edge_left;
    uint32_t delay_edge_right;
    uint32_t vref_eye_height;
    uint32_t delay_eye_width;
    uint32_t vref_margin_top;
    uint32_t vref_margin_bottom;
    uint32_t delay_margin_left;
    uint32_t delay_margin_right;
}mddr_ca_eyemargin_measure_ps_mv_t;


/*!****************************************************************************
*
* @par Description
*    This type provides the container for the top level CA eye margining result
*     structure.
*
* @par Members
*
*                                  <PRE>
*    mddr_ca_eyemargin_valid_bitmap   Container for eye margin result valid channel
*                                      and slot bitmap.
*    mddr_ca_eyemargin_address        Container for address eye measurement results
*                                      structure per dimm slot.
*    mddr_ca_eyemargin_address_ps_mv  Container for address eye measurement results
*                                      structure per dimm slot in ps/mV.
*    mddr_ca_eyemargin_control        Container for control eye measurement results
*                                      structure per dimm slot.
*    mddr_ca_eyemargin_control_ps_mv  Container for control eye measurement results
*                                      structure per dimm slot in ps/mV.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    mddr_ca_eyemargin_valid_bitmap_t mddr_ca_eyemargin_valid_bitmap;
    mddr_ca_eyemargin_measure_t mddr_ca_eyemargin_address[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
    mddr_ca_eyemargin_measure_ps_mv_t mddr_ca_eyemargin_address_ps_mv[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
    mddr_ca_eyemargin_measure_t mddr_ca_eyemargin_control[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
    mddr_ca_eyemargin_measure_ps_mv_t mddr_ca_eyemargin_control_ps_mv[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
}mddr_ca_eyemargin_result_t;


typedef enum
{
    ALL_CA_SIG=0,
    ALL_CA_BUT_CKE=1,
    ONLY_CA_ADDR=2,
    ONLY_CA_CONT=3
}mddr_ca_signal_group_t;

/******************************************************************************
* Function Prototypes
******************************************************************************/
unsigned int monaco_init_ca_margining(monaco_init_t *init_parms_ptr, mddr_ca_eyemargin_result_t *mddr_ca_eyemargin_result);
unsigned mddr_ca_eye_margining(monaco_init_t *init_parms_ptr, mddr_ca_eyemargin_result_t *mddr_ca_eyemargin_result);
unsigned mddr_ca_margin_process(mddr_ca_eyemargin_result_t *mddr_ca_eyemargin_result);
void mddr_ca_set_ca_delay(uint64_t mddr_base_addr, uint16_t dly_group, uint8_t fine_dly);
void mddr_ca_set_ca_vref(uint64_t mddr_base_addr, uint8_t slot, uint8_t fine_vref);


/*****************************************************************************/
#endif

