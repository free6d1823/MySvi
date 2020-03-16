#ifndef _MDDR_SI_H_
#define _MDDR_SI_H_

/*!****************************************************************************
*
* @copyright Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file mddr_si.h
*
* @par Description:
*    This header contains the prototypes, derived data types, etc. for the
*    handling of the MDDR SI Loading
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>


/******************************************************************************
* Defined Constants
******************************************************************************/
#define LRDIMM_SI_DDR_FREQ_VARNTS         3

// Maximum value of cycle adjusts for each field of the TIMING_ADJ_RDWR reg
#define DDR_CYCLES_ADJ_RDWR_MAX           0xF

/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    This type defines the types of ODT the PHY supports.
*
******************************************************************************/
typedef enum
{
    ODT_OFF,
    ODT_TARGETED,
    ODT_NON_TARGETED,
    ODT_DUAL_TARGETED,
    ODT_DUAL_OPPOSITE,
    ODT_SINGLE_OPPOSITE,
    ODT_MIXED_OPPOSITE_1R2R,
    ODT_MIXED_OPPOSITE_2R1R
} mddr_si_odt_type_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the types of impedance(drive strength) the PHY supports:
*    per channel, impedance for CA[0] and DQ[1]
*    DQ 28.2, 30, 32, 34.3, 36.9, 40, 43.6, 48, 53.3 60, 68.6 80, 96, 120, 160, 240 480 ohms
*    CA 20, 24, 30, 40, 60, 120 ohms
*
******************************************************************************/
typedef enum __attribute__((packed, aligned(2)))
{
    IMP_OHMS20 = 20,
    IMP_OHMS24 = 24,
    IMP_OHMS28 = 28,
    IMP_OHMS30 = 30,
    IMP_OHMS32 = 32,
    IMP_OHMS34 = 34,
    IMP_OHMS37 = 37,
    IMP_OHMS40 = 40,
    IMP_OHMS44 = 44,
    IMP_OHMS48 = 48,
    IMP_OHMS53 = 53,
    IMP_OHMS60 = 60,
    IMP_OHMS69 = 69,
    IMP_OHMS80 = 80,
    IMP_OHMS96 = 96,
    IMP_OHMS120 = 120,
    IMP_OHMS160 = 160,
    IMP_OHMS240 = 240,
    IMP_OHMS480 = 480
} mddr_si_imp_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the types of termination (ODT) the PHY supports:
*    per channel, termination DQ
*    28.2, 30, 32, 34.3, 36.9, 40, 43.6, 48, 53.3 60, 68.6 80, 96, 120, 160, 240 480 ohms
*
******************************************************************************/
typedef enum __attribute__((packed, aligned(2)))
{
    OHMS28 = 28,
    OHMS30 = 30,
    OHMS32 = 32,
    OHMS34 = 34,
    OHMS37 = 37,
    OHMS40 = 40,
    OHMS44 = 44,
    OHMS48 = 48,
    OHMS53 = 53,
    OHMS60 = 60,
    OHMS69 = 69,
    OHMS80 = 80,
    OHMS96 = 96,
    OHMS120 = 120,
    OHMS160 = 160,
    OHMS240 = 240,
    OHMS480 = 480
} mddr_si_term_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the platform specific cycle
*     adjustments for things like trace length.
*
* @par Members
*
*                                  <PRE>
*    dimm_wtr            Additional cycles from WR to RD different DIMMs
*    dimm_wtw            Additional cycles from WR to WR different DIMMs
*    dimm_rtw            Additional cycles from RD to WR different DIMMs
*    dimm_rtr            Additional cycles from RD to RD different DIMMs
*    cs_wtr              Additional cycles from WR to RD different chip selects
*    cs_wtw              Additional cycles from WR to WR different chip selects
*    cs_rtw              Additional cycles from RD to WR different chip selects
*    cs_rtr              Additional cycles from RD to RD different chip selects
*    rank_wtr            Additional cycles from WR to RD different ranks in a chip select
*    rank_wtw            Additional cycles from WR to WR different ranks in a chip select
*    rank_rtw            Additional cycles from RD to WR different ranks in a chip select
*    rank_rtr            Additional cycles from RD to RD different ranks in a chip select
*    srank_wtr           Additional cycles from WR to RD same rank
*    srank_wtw           Additional cycles from WR to WR same rank
*    srank_rtw           Additional cycles from RD to WR same rank
*    srank_rtr           Additional cycles from RD to RD same rank
*    ref_to_ref          Additional cycles from auto-refresh to any auto-refresh command
*    zq_to_zq            Minimum number of DDR cycles from the end of last ZQ
*                         calibration to the start of the next ZQ calibration.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t dimm_wtr;
    uint8_t dimm_wtw;
    uint8_t dimm_rtw;
    uint8_t dimm_rtr;
    uint8_t cs_wtr;
    uint8_t cs_wtw;
    uint8_t cs_rtw;
    uint8_t cs_rtr;
    uint8_t rank_wtr;
    uint8_t rank_wtw;
    uint8_t rank_rtw;
    uint8_t rank_rtr;
    uint8_t srank_wtr;
    uint8_t srank_wtw;
    uint8_t srank_rtw;
    uint8_t srank_rtr;
    uint16_t ref_to_ref;
    uint16_t zq_to_zq;
} mddr_plat_cycle_adj_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the per rank SI settings.
*    These pertain to SI settings on DRAM side
*
* @par Members
*
*                                  <PRE>
*    rtt_park                For DDR4: 0=disabled, 60, 120, 40, 240, 48, 80, 34 ohms
*                             ODT low or rtt_nom disabled
*    rtt_nom                 For DDR4: 0=disabled, 60, 120, 40, 240, 48, 80, 34 ohms
*                             ODT high
*    rtt_wr                  For DDR4: 0=disabled, 120, 240, 1 (Hi-Z), 80 ohms
*                             Any write command
*    ron                     Ron = 34 ohms, 48 ohms
*    odt_rd, odt_wr          per channel settings;  only CS0:3 are valid
*                             per rank, 4 bits each representing the 4 ODT signals
*                             (DIMM1=[3:2], DIMM0=[1:0])
*    vref                    vrefdq seetings: per channel, slot, rank, dram in hundredth
*                             percentage of VDDQ (eg 77.55%=7755)
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t rtt_park;
    uint8_t rtt_nom;
    uint8_t rtt_wr;
    uint8_t ron;    // drive strength
    uint8_t odt_rd;
    uint8_t odt_wr;

    uint16_t vref[18];      // dq vref in integer to thousandths place, eg 50.00% = 5000
}mddr_si_rank_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the per slot SI settings.
*    These pertain to SI settings on DRAM side
*
* @par Members
*
*                                  <PRE>
*    ibt                     all channels, all slots, RDIMM IBT settings (ca[0], cs[1], cke[2], odt[3])
*    rank_si                 per rank SI settings
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint16_t ibt[4];      // input buffer termination (L/RDIMM)

    mddr_si_rank_t rank_si[DDR_MAX_RANKS_PER_SLOT];
}mddr_si_dimm_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the per channel SI settings.
*    These pertain to SI settings on Controller PHY side (host)
*
* @par Members
*
*                                  <PRE>
*    mc_slew                 per channel, slew for CA[0] and DQ[1], bits n[7:4], p[3:0]
*                             0=slowest, 0xF=fastest
*    mc_imp                  per channel, impedance for CA[0] and DQ[1]
*    mc_term                 per channel, termination DQ
*    mc_vref                 per channel, per slot, mc vrefdq settings
*    cycle_adjusts           per channel, platform specific cycle adjustments.
*    dimm_si                 per channel, per slot SI settings
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t mc_slew[2];      // 0=CA, 1=Data
    mddr_si_imp_t mc_imp[2];        //  0=CA, 1=Data
    mddr_si_term_t mc_term;

    uint16_t mc_vref;

    mddr_plat_cycle_adj_t cycle_adjusts;

    mddr_si_dimm_t dimm_si[DDR_MAX_NUM_SLOTS_PER_CHAN];
}mddr_si_chan_t;


/*!****************************************************************************
*
* @par Description
*    This type provides key information necessary to select the specific set of
*     SI values to use when configuring a single DDR channel.
*
* @par Members
*
*                                  <PRE>
*    ddr_chan           DDR channel to perform function on.
*    mem_freq_mhz       Target operation frequency of the memory.
*    num_dimm_slots     Number of DIMM slots physically present on a DDR
*                        channel. This is independent of if the slots are
*                        populated or not. Must be 1 or 2.
*    num_dimm_slots_pop Number of DIMMs populated in a DDR channel.
*    num_ranks_slot     Array of rank counts for the the DIMMs by slot.
*                        SPD_INVALID_RANK_COUNT indicates no DIMM.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t ddr_chan;
    uint32_t mem_freq_mhz;
    uint8_t num_dimm_slots;
    uint8_t num_dimm_slots_pop;
    uint8_t num_ranks_slot[DDR_MAX_NUM_SLOTS_PER_CHAN];
}mddr_si_selector_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the parameters associated with
*     DDR SI Binary file. This provides the start location and size of the
*     consolidated DDR SI Binary file.
*
* @par Members
*
*                                  <PRE>
*    bin_start_addr      The start address of the DDR SI binary file
*    bin_size            The size of the DDR SI binary file
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint64_t bin_start_addr;
    uint32_t bin_size;
}mddr_si_binary_hdr_t;


/*!****************************************************************************
*
* @par Description
*    This type defines all the parameters used to identify a specific SI configuration.
*    This structure here forms the SI Binary header (used by XBL) of 0x50 bytes.
*
* @par Members
*
*                                  <PRE>
*    ident[8]              8-byte unique identifier signature for the SI configs.
*                           This identifier is defined as "DDRSI"
*    platform[8]           8-byte field for identifying the platform.
*                           Supported platforms are: CRB, RUMI, SDP, OEM
*    hd_size               Header size for a SI configuration
*    sil_min_ver           Silicon version - Minor
*    sil_maj_ver           Silicon version - Major
*    mem_freq_mhz          Target operation frequency of the memory.
*    num_dimm_slots        Number of DIMM slots physically present on a DDR
*                           channel. This is independent of if the slots are
*                           populated or not. Must be 1 or 2.
*    num_dimm_slots_poped  Number of DIMMs populated in a DDR channel.
*    num_ranks             Ranks here are displayed as ranks per channel.
*                           (The actual rank count for each config is rank per slot)
*                            FAR=0, NEAR=1
*    reserved[6]           Reserved for future use.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    char ident[8];
    char platform[8];
    uint16_t hd_size;
    uint8_t sil_min_ver;
    uint8_t sil_maj_ver;
    uint32_t mem_freq_mhz;
    uint16_t num_dimm_slots;
    uint16_t num_dimm_slots_poped;
    uint16_t num_ranks[2];
    uint64_t reserved[6];
}mddr_si_config_t;


/*!****************************************************************************
*
* @par Description
*    This type defines all the parameters for LRDIMM DB (databuffer) Host side
*    interface SI values.
*
* @par Members
*
*                                  <PRE>
*    lr_host_db_rtt_park   LRDIMM DB Host interface rtt_park.
*    lr_host_db_rtt_wr     LRDIMM DB Host interface rtt_wr.
*    lr_host_db_rtt_nom    LRDIMM DB Host interface rtt_nom.
*    lr_host_db_ron        LRDIMM DB Host interface ron.
*    lr_host_db_vrefdq     LRDIMM DB Host interface VrefDQ.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t lr_host_db_rtt_park;
    uint8_t lr_host_db_rtt_wr;
    uint8_t lr_host_db_rtt_nom;
    uint8_t lr_host_db_ron;
    uint16_t lr_host_db_vrefdq;
}mddr_lr_host_db_si_dimm_t;


/*!****************************************************************************
*
* @par Description
*    This type defines all the parameters for LRDIMM DB (databuffer) DRAM side
*    interface SI values and LRDIMM SPD settings for DRAM-DB.
*
* @par Members
*
*                                  <PRE>
*    --------------- LRDIMM databuffer DRAM interface side settings ---------------
*    lr_spd_db_dq_dfe             LRDIMM DB DQ DFE capabilities - feedback equalization support.
*    lr_spd_db_dq_gain_adj        LRDIMM DB DQ DFE capabilities - gain adjustment support.
*    lr_spd_db_mdq_ron            LRDIMM DB drive strength for MDQ/MDQS outputs.
*    lr_spd_db_mdq_term           LRDIMM DB Read RTT termination strength.
*    lr_spd_db_mdq_vrefdq         LRDIMM DB VrefDQ.
*    lr_spd_db_mdq_vrefdq_range   LRDIMM DB VrefDQ range.
*
*    --------------- LRDIMM SPD settings for DRAM-DB ---------------
*    lr_spd_db_rtt_park01         LRDIMM DRAM ODT termination strength (rtt_park) for ranks 0,1.
*    lr_spd_db_rtt_park23         LRDIMM DRAM ODT termination strength (rtt_park) for ranks 2,3.
*    lr_spd_db_rtt_wr             LRDIMM DRAM ODT termination strength (rtt_wr).
*    lr_spd_db_rtt_nom            LRDIMM DRAM ODT termination strength (rtt_nom).
*    lr_spd_db_ron                LRDIMM DRAM output buffer drive strength.
*    lr_spd_db_vrefdq             LRDIMM DRAM VrefDQ for package rank 0-3.
*    lr_spd_db_vrefdq_range       LRDIMM DRAM VrefDQ range.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t lr_spd_db_dq_dfe;
    uint8_t lr_spd_db_dq_gain_adj;
    uint8_t lr_spd_db_mdq_ron[LRDIMM_SI_DDR_FREQ_VARNTS];
    uint8_t lr_spd_db_mdq_term[LRDIMM_SI_DDR_FREQ_VARNTS];
    uint8_t lr_spd_db_mdq_vrefdq;
    uint8_t lr_spd_db_mdq_vrefdq_range;

    uint8_t lr_spd_db_rtt_park01[LRDIMM_SI_DDR_FREQ_VARNTS];
    uint8_t lr_spd_db_rtt_park23[LRDIMM_SI_DDR_FREQ_VARNTS];
    uint8_t lr_spd_db_rtt_wr[LRDIMM_SI_DDR_FREQ_VARNTS];
    uint8_t lr_spd_db_rtt_nom[LRDIMM_SI_DDR_FREQ_VARNTS];
    uint8_t lr_spd_db_ron[LRDIMM_SI_DDR_FREQ_VARNTS];
    uint8_t lr_spd_db_vrefdq[DDR_MAX_RANKS_PER_SLOT];
    uint8_t lr_spd_db_vrefdq_range[DDR_MAX_RANKS_PER_SLOT];
}mddr_lr_spd_db_si_dimm_t;


/*!****************************************************************************
*
* @par Description
*    This type provides the top-level container for LRDIMM Host, databuffer
*    and DRAM interface SI values.
*
* @par Members
*
*                                  <PRE>
*    lr_host_db_si    LRDIMM DB (databuffer) Host side interface values.
*    lr_spd_db_si     LRDIMM DB DRAM side interface values & SPD settings for DRAM-DB.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    mddr_lr_host_db_si_dimm_t lr_host_db_si[DDR_MAX_NUM_SLOTS_PER_CHAN];
    mddr_lr_spd_db_si_dimm_t lr_spd_db_si[DDR_MAX_NUM_SLOTS_PER_CHAN];
}mddr_lr_db_si_chan_t;


/******************************************************************************
* Function Prototypes
******************************************************************************/
void mddr_get_sdp_si(mddr_si_selector_t *selector_ptr, mddr_si_chan_t *si_data_ptr);
uint16_t mddr_si_get_vrefdq_percentage(uint8_t vrefdq_val, uint8_t vrefdq_range);
uint8_t mddr_si_rtt_to_ohms(uint8_t rtt_val);
void mddr_si_configure_lrdimm_db(mddr_si_chan_t *si_data_ptr, uint8_t ddr_chan);
unsigned mddr_si_config_match(mddr_si_selector_t *selector_ptr, mddr_si_chan_t *si_data_ptr, mddr_si_config_t *mddr_load_si_hdr, uint64_t bin_address);
void mddr_load_si(mddr_si_selector_t *selector_ptr, mddr_si_chan_t *si_data_ptr);


/*****************************************************************************/
#endif


