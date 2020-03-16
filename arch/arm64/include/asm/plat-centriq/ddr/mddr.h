#ifndef _MODULE_MDDR_H_
#define _MODULE_MDDR_H_

/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file mddr.h
*
* @par Description:
*    This header contains the prototypes, derived data types, etc. to allow the
*    initialization of the Monaco DDR Subsystem.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <asm/mach/monaco/common/monaco_defs.h>
#include <asm/mach/monaco/memory/spd.h>
#include <asm/plat-centriq/ddr/mddr_power.h>
#include <asm/mach/monaco/memory/mddr_si.h>



/******************************************************************************
* Defined Constants
******************************************************************************/



/*!****************************************************************************
*
* @par Description
*    Special temperature marker value indicating that the temperature is
*     invalid. Generally used to indicate temperature for DIMMs that do not
*     incorporate a thermal sensor.
*
* @par Notes
*    The sign bit is set and all other all other bits clear. DIMM temperature
*    is a signed 13 bit 2's complement integer value in degrees C. Bits
*    0..2 represent the fractional portion of the temperature.
*
******************************************************************************/
#define MDDR_DIMM_TEMP_INVALID             0x1000


/*!****************************************************************************
*
* @par Description
*    DDR maximum DIMM frequencies of supported platforms.
*
* @par Members
*
*                                  <PRE>
*    MAX_1DIMM_FREQ_MHZ_SILICON     Maximum DIMM frequency on SDP in 1DPC configuration
*    MAX_1DIMM_FREQ_MHZ_RUMI        Maximum DIMM frequency on RUMI in 1DPC configuration
*
*    MAX_2DIMM_FREQ_MHZ_SILICON     Maximum DIMM frequency on SDP in 2DPC configuration
*    MAX_2DIMM_FREQ_MHZ_RUMI        Maximum DIMM frequency on RUMI in 2DPC configuration
*                                  </PRE>
*
******************************************************************************/
#define MAX_1DIMM_FREQ_MHZ_SILICON          1333
#define MAX_2DIMM_FREQ_MHZ_SILICON          1200

#define MAX_1DIMM_FREQ_MHZ_RUMI             3
#define MAX_2DIMM_FREQ_MHZ_RUMI             3


/*!****************************************************************************
*
* @par Description
*    DDR reference clock frequencies of supported platforms.
*
* @par Members
*                                  <PRE>
*    MDDR_XO_FREQ_KHZ_SILICON       XO Frequency on SDP platform
*    MDDR_XO_FREQ_KHZ_RUMI          XO Frequency on RUMI platform
*                                  </PRE>
*
******************************************************************************/

#define MDDR_XO_FREQ_KHZ_SILICON            20000   // 20 MHz
#define MDDR_XO_FREQ_KHZ_RUMI               332     // 2.66MHz/8


/*!****************************************************************************
*
* @par Description
*    DDR Bandwidth Compression absolute minimum, absolute maximum, and default
*     settings.
*
* @par Members
*                                  <PRE>
*    CDE_RD_WINDOW_SIZE_MIN         Minimum possible size of the read window.
*    CDE_RD_WINDOW_SIZE_MAX         Maximum possible size of the read window.
*    CDE_RD_HIST_SIZE_MIN           Minimum possible depth of read window result history.
*    CDE_RD_HIST_SIZE_MAX           Maximum possible depth of read window result history.
*    CDE_RD_HIST_THRESHOLD_MIN      Minimum possible threshhold of read window history.
*    CDE_RD_HIST_THRESHOLD_MAX      Maximum possible threshhold of read window history.
*    CDE_COMPRD_HI_THRESHOLD_MIN    Minimum possible high threshhold (number of reads that
*                                    must have been compressed within the read window to
*                                    set the window result to 'b1).
*    CDE_COMPRD_HI_THRESHOLD_MAX    Maximum possible high threshhold (number of reads that
*                                    must have been compressed within the read window to
*                                    set the window result to 'b1).
*    CDE_COMPRD_LO_THRESHOLD_MIN    Minimum possible low threshhold (number of reads below which the window result is set to 'b0).
*    CDE_COMPRD_LO_THRESHOLD_MAX    Maximum possible low threshhold (number of reads below which the window result is set to 'b0).
*                                  </PRE>
*
******************************************************************************/
// Valid range is of CDE_RD_WINDOW_SIZE is 0x0001 to 0xFFFF
#define CDE_RD_WINDOW_SIZE_MIN 0x0001
#define CDE_RD_WINDOW_SIZE_MAX 0xFFFF

// Valid range is of CDE_RD_HIST_SIZE is 0x1 to 0x8
#define CDE_RD_HIST_SIZE_MIN 0x1
#define CDE_RD_HIST_SIZE_MAX 0x8

// Valid range is of RD_HIST_THRESHOLD is 0x0 to RD_HIST_SIZE
#define CDE_RD_HIST_THRESHOLD_MIN 0x0
#define CDE_RD_HIST_THRESHOLD_MAX 0x8

// Valid range of COMPRD_HI_THRESHOLD is 1 to RD_WINDOW_SIZE
#define CDE_COMPRD_HI_THRESHOLD_MIN 0x1
#define CDE_COMPRD_HI_THRESHOLD_MAX 0xFFFF

// Valid range of COMPRD_LO_THRESHOLD is 0 to COMPRD_HI_THRESHOLD-1
#define CDE_COMPRD_LO_THRESHOLD_MIN 0x0
#define CDE_COMPRD_LO_THRESHOLD_MAX (0xFFFF - 0x1)


/*!****************************************************************************
*
* @par Description
*    Number of DDR cycles that an idle page remains open before it is closed
*     when the page policy is PAGE_POLICY_TIMER.
*
* @par Members
*                                  <PRE>
*    MDDR_PAGE_IDLE_TIMER_MIN       Minumum value supported by the driver
*    MDDR_PAGE_IDLE_TIMER_MAX       Maximum value supported by the driver
*                                  </PRE>
*
******************************************************************************/
#define MDDR_PAGE_IDLE_TIMER_MIN          0x0000
#define MDDR_PAGE_IDLE_TIMER_MAX          0x03FF


/*!****************************************************************************
*
* @par Description
*    Number of dimm slots physically present in a DDR channel.  This is
*     independent of whether the slots are populated or not.
*
* @par Members
*                                  <PRE>
*    NUM_DIMM_SLOTS_MIN         Minumum value supported by the driver
*    NUM_DIMM_SLOTS_MAX         Maximum value supported by the driver
*                                  </PRE>
*
******************************************************************************/
#define NUM_DIMM_SLOTS_MIN                0x1
#define NUM_DIMM_SLOTS_MAX                0x2


/*!****************************************************************************
*
* @par Description
*    The value represents the command and data latency through the DDR PHY.
*
* @par Members
*                                  <PRE>
*    PROP_DELAY_MIN         Minumum value supported by the driver
*    PROP_DELAY_MAX         Maximum value supported by the driver
*                                  </PRE>
*
******************************************************************************/
#define PROP_DELAY_MIN                    0x0
#define PROP_DELAY_MAX                    0xFF

/*!****************************************************************************
*
* @par Description
*    For memory writes, this field specifies the number of DDR cycles that
*     extra DQS toggles are appended to the end of the write data burst.
*
* @par Members
*                                  <PRE>
*    EXTRA_DQS_TOGGLE_MIN       Minumum value supported by the driver
*    EXTRA_DQS_TOGGLE_MAX       Maximum value supported by the driver
*                                  </PRE>
*
******************************************************************************/
#define EXTRA_DQS_TOGGLE_MIN              0x0
#define EXTRA_DQS_TOGGLE_MAX              0x7


/*!****************************************************************************
*
* @par Description
*    Maximum DDR frequency values (MHz) as per 1DPC/2DPC silicon configurations
*     and DDR frequency for emulation
*
******************************************************************************/
#define MAX_2DPC_CLK                      1200
#define MAX_1DPC_CLK                      1333
#define MAX_EMU_CLK                       3


/*!****************************************************************************
*
* @par Description
*    DDR rank configuration for single, dual and quad chip select DIMMs
*
******************************************************************************/
#define DDR_RANKS_SINGLE_CS_DIMM          1
#define DDR_RANKS_DUAL_CS_DIMM            2
#define DDR_RANKS_QUAD_CS_DIMM            4


/*!****************************************************************************
*
* @par Description
*    Maximum number of Bus Utilization Monitor (BUM) performance indexes
*     to be exposed.
*
* @par Members
*
*                                  <PRE>
*    DDR_BUM_PERF_IDX_MAX             Max number of BUM performance index IDs exposed,
*                                      which could be less than the number supported in hardware.
*    DDR_BUM_LO_THRESHOLD_MIN         Minimum low threshold value supported by the driver.
*    DDR_BUM_LO_THRESHOLD_MAX         Maximum low threshold value supported by the driver.
*    DDR_BUM_HI_THRESHOLD_MIN         Minimum high threshold value supported by the driver.
*    DDR_BUM_HI_THRESHOLD_MAX         Maximum high threshold value supported by the driver.
*                                  </PRE>
*
******************************************************************************/
#define DDR_BUM_PERF_IDX_MAX                4
#define DDR_BUM_LO_THRESHOLD_MIN            0x00000000
#define DDR_BUM_LO_THRESHOLD_MAX            0xFFFFFFFF
#define DDR_BUM_HI_THRESHOLD_MIN            0x00000000
#define DDR_BUM_HI_THRESHOLD_MAX            0xFFFFFFFF


/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    Reed-Solomon quad detection configuration modes.
*
******************************************************************************/
typedef enum
{
    RS_QUAD_DET_DISABLE,    //!< Selects single/double symbol correct, triple symbol detect.
    RS_QUAD_DET_ENABLE,     //!< Selects single symbol correct, double/triple/quad symbol detect.
    RS_QUAD_DET_NUM_TYPES   //!< Number of Reed-Solomon quad detection configuration modes.
} rs_quad_det_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the possible configurations for the DDR distribution
*    granule. The granule is the size of the addressing slice dedicated to a
*    pair of DDR controllers when two pairs (4 channels) or more are active in
*    the DDR subsystem.
*
* @par Notes
*    When two or more pairs of channels exist, DDR memory addressing repeatedly
*    cycles through channel pairs on a granule size basis.  e.g. The 1st pair
*    provides the 1st granule, the 2nd pair provides the 2nd granule, the third
*    pair (if it is populated) provides the 3rd granule, then the cycle
*    repeats with the first pair providing the next granule and so on, covering
*    the entire DDR address space.
*
******************************************************************************/
typedef enum
{
    DDR_DIST_GRANULE_256B,      //!< Selects a granule size of 256 Bytes.
    DDR_DIST_GRANULE_4KB,       //!< Selects a granule size of 4 KBytes.
    DDR_DIST_GRANULE_8KB,       //!< Selects a granule size of 8 KBytes.
    DDR_DIST_GRANULE_NUM_TYPES  //!< Number of granule size configuration options.
} mddr_ddr_intlv_t;



/*!****************************************************************************
*
* @par Description
*    This type defines the possible data bus inversion configuration options.
*
******************************************************************************/
typedef enum
{
    DDR_DBI_OFF,        //!< Selects DBI off.
    DDR_DBI_READ,       //!< Selects DBI for reads only.
    DDR_DBI_WRITE,      //!< Selects DBI for writes only.
    DDR_DBI_READ_WRITE, //!< Selects DBI for both reads and writes.
    DDR_DBI_NUM_TYPES   //!< Number of data bus inversion configuration options.
} mddr_ddr_dbi_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the possible CA parity configuration modes.
*
******************************************************************************/
typedef enum
{
    CA_PARITY_DISABLE,      //!< Selects CA parity disabled.
    CA_PARITY_DRAM,         //!< Selects DRAM CA parity (DDR4) enabled.
    CA_PARITY_DIMM,         //!< Selects DIMM CA parity (L/RDIMM) enabled.
    CA_PARITY_DRAM_DIMM,    //!< Selects DIMM and DRAM CA parity enabled.
    CA_PARITY_NUM_TYPES     //!< Number of CA parity configuration modes.
} mddr_ca_parity_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the data bus burst length modes. Burst Chop 4, BC4
*     is not supported as an independent setting.
*
******************************************************************************/
typedef enum
{
    DB_BURST_LEN_OTF,       //!< OTF - On The Fly : BL8 & BC4
    DB_BURST_LEN_BL8,       //!< BL8 - Burst Length 8
    DB_BURST_LEN_NUM_TYPES  //!< Number of burst length coniguration modes.
} mddr_burst_len_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the page policies to indicate when an open page should
*     be closed.
*
* @par Notes:
*    If the policy is DDR_PAGE_POLICY_TIMER, an idle timer value must also be
*     provided.
*
******************************************************************************/
typedef enum
{
    DDR_PAGE_POLICY_CLOSED,     //!< Close the page as soon as there are no outstanding commands pending for the page.
    DDR_PAGE_POLICY_OPEN,       //!< Hold the page open until there are no outstanding commands pending for the page and either there is a command for another page in the same bank or the page is due a refresh.
    DDR_PAGE_POLICY_TIMER,      //!< Same as open page policy except the page will also be closed when the pages idle timer expires.
    DDR_PAGE_POLICY_NUM_TYPES   //!< Number of page policy modes.
} mddr_page_policy_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the page related
*    configuration controls available to adjust the memory controller
*    initialization.
*
* @par Members
*
*                                  <PRE>
*    enable_auto_pchg       Flag indicating if auto-Precharge in the CAS
*                            commands should be enabled.
*    burst_len_mode         Indicates the memory data bus burst mode to use.
*    page_policy            Indicates the data bus page policy to apply.
*    page_idle_timer        Number of DDR cycles that an idle page remains
*                            open before it is closed when the page policy is
*                            DDR_PAGE_POLICY_TIMER.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    bool enable_auto_pchg;
    mddr_burst_len_t burst_len_mode;
    mddr_page_policy_t page_policy;
    uint16_t page_idle_timer;
} mddr_page_settings_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the DDR refresh command mode. (fine granularity refresh)
*
******************************************************************************/
typedef enum
{
    DDR_REFRESH_1X = 0,     //!< 1X DDR refresh command mode.
    DDR_REFRESH_2X = 1,     //!< 2X DDR refresh command mode.
    DDR_REFRESH_4X = 2      //!< 4X DDR refresh command mode.
} mddr_rfc_cmd_mode_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the DDR4 2Tck preamble configuration modes.
*
******************************************************************************/
typedef enum
{
    DDR4_2T_DISABLE,    //!< Selects DDR4 2Tck preamble disabled.
    DDR4_2T_READ,       //!< Selects DDR4 2Tck preamble for reads enabled.
    DDR4_2T_WRITE,      //!< Selects DDR4 2Tck preamble for writes enabled.
    DDR4_2T_WRITE_READ, //!< Selects DDR4 2Tck preamble for writes and reads enabled.
    DDR4_2T_NUM_TYPES   //!< Number of DDR4 2Tck preamble configuration modes.
} mddr_ddr4_2t_preamble_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the number of stretch cycles for the CA bus before
*     asserting the CS_n.
*
******************************************************************************/
typedef enum
{
    CA_STRETCH_1T = 0,  //!< Selects 1 stretch cycles for the CA bus.
    CA_STRETCH_2T = 1,  //!< Selects 2 stretch cycles for the CA bus.
    CA_STRETCH_3T = 2,  //!< Selects 3 stretch cycles for the CA bus.
    CA_STRETCH_4T = 3   //!< Selects 4 stretch cycles for the CA bus.
} mddr_ca_stretch_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the ECC WR/RD configuration values.
*
******************************************************************************/
typedef enum
{
    ECC_WR     = 0x01,
    ECC_RD     = 0x02,
    RS_WR      = 0x04,
    RS_RD      = 0x08
} mddr_ecc_wrrd_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the supported DDR compression modes.
*
******************************************************************************/
typedef enum
{
    DDR_COMP_DISABLED,          //!< Selects compression mode disabled.
    DDR_COMP_STATIC,            //!< Selects static compression mode enabled.
    DDR_COMP_ADAPTIVE,          //!< Selects adaptive compression mode enabled.
    DDR_COMP_NUM_TYPES          //!< Number of compression modes.
} mddr_comp_mode_t;


/*!****************************************************************************
*
* @par Description
*    This type defines whether DDR compression and decompression should be enabled.
*
******************************************************************************/
typedef enum
{
    COMP_DECOMP_OFF,            //!< Compression and Decompression disabled.
    COMP_DECOMP_ON,             //!< Compression and Decompression enabled.
    COMP_DECOMP_NUM_TYPES       //!< Number of compression and decompression types.
} mddr_decomp_comp_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the mode select for WDB and QSB initiated reads.
*
*    Defines for WDB initiated reads:
*    0=assume uncompressed,
*    1=assume compressed,
*    0x9=adaptive (track QSB rd),
*    0xA=adaptive (track WDB rd),
*    0xB=adaptive (track QSB & WDB rd)
*
*    Defines for QSB initiated reads:
*    0=assume uncompressed,
*    1=assume compressed,
*    0x4=per-master adaptive mode,
*    0x6=per-master adaptive w/ reads for non-tracked masters issued assuming uncompressed,
*    0x7=per-master adaptive w/ reads for non-tracked masters issued assuming compressed,
*    0x9=global adaptive (track QSB rd),
*    0xA=global adaptive (track WDB rd),
*    0xB=global adaptive (track QSB & WDB rd)
*
******************************************************************************/
typedef enum
{
    RD_UNCOMPRESSED               = 0x0,
    RD_COMPRESSED                 = 0x1,
    RD_ADAPTIVE_PER_MASTER        = 0x4,
    RD_ADAPTIVE_PER_MASTER_UNCOMP = 0x6,
    RD_ADAPTIVE_PER_MASTER_COMP   = 0x7,
    RD_GLBL_ADAPTIVE_TRK_QSB      = 0x9,
    RD_GLBL_ADAPTIVE_TRK_WDB      = 0xA,
    RD_GLBL_ADAPTIVE_TRK_QSB_WDB  = 0xB
} mddr_cde_wdb_qsb_rd_mode_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the gcc reset release and assert values.
*    bit0=PHY reset bit, bit1=APB reset bit
*
******************************************************************************/
typedef enum
{
    DEASSERT_GCC_RESET    = 0x0,
    ASSERT_GCC_RESET      = 0x3
} mddr_gcc_reset_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the possible array of DDR frequencies.
*    Note: As per the plan of record, only a subset of these DDR frequencies
*          are supported.
*
******************************************************************************/
typedef enum
{
    DDR_FREQ_IDX_625_MHZ    = 0,
    DDR_FREQ_IDX_660_MHZ    = 1,
    DDR_FREQ_IDX_800_MHZ    = 2,
    DDR_FREQ_IDX_933_MHZ    = 3,
    DDR_FREQ_IDX_1066_MHZ   = 4,
    DDR_FREQ_IDX_1200_MHZ   = 5,
    DDR_FREQ_IDX_1333_MHZ   = 6,
    DDR_FREQ_IDX_1467_MHZ   = 7,
    DDR_FREQ_IDX_1600_MHZ   = 8,
    DDR_FREQ_IDX_MAX        = 9
} mddr_mem_freq_mhz_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the compression-decompression
*    configuration.
*
* @par Members
*
*                                  <PRE>
*    comp_mode                Indicates which compression mode is requested.
*    decomp_comp              Indicates whether compression and decompression are enabled.
*    cde_comprd_hi_threshold  Indicates number of compressed in reads in read window to set
*                              window result to 1
*    cde_comprd_lo_threshold  If number of compressed reads in read window is less than this value,
*                              window result is set to 0
*    cde_rd_window_size       Size of the read window.
*                              Must be programmed to >0 if RD_MODE is set to either 'b10 or 'b11.
*    cde_rd_hist_threshold    Number of bits within the read window history to assume data is compressed
*                              It is required that RD_HIST_THRESHOLD <= RD_HIST_SIZE.
*    cde_rd_hist_size         Depth of read window result history may be programmed to 1 - 8.
*                              A value of 1 uses no history, only the current read window result.
*    cde_wdb_rd_mode          Mode select for WDB initiated reads
*                              0=assume uncompressed, 1=assume compressed,
*                              0x9=adaptive (track QSB rd), 0xA=adaptive (track WDB rd), 0xB=adaptive (track QSB & WDB rd)
*    cde_qsb_rd_mode          Mode select for QSB reads
*                              0=assume uncompressed, 1=assume compressed, 0x4=per-master adaptive mode,
*                              0x6=per-master adaptive w/ reads for non-tracked masters issued assuming uncompressed,
*                              0x7=per-master adaptive w/ reads for non-tracked masters issued assuming compressed,
*                              0x9=global adaptive (track QSB rd),
*                              0xA=global adaptive (track WDB rd), 0xB=global adaptive (track QSB & WDB rd)
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    mddr_comp_mode_t comp_mode;
    mddr_decomp_comp_t decomp_comp;
    uint16_t cde_comprd_hi_threshold;
    uint16_t cde_comprd_lo_threshold;
    uint16_t cde_rd_window_size;
    uint16_t cde_rd_hist_threshold;
    uint16_t cde_rd_hist_size;
    mddr_cde_wdb_qsb_rd_mode_t cde_wdb_rd_mode;
    mddr_cde_wdb_qsb_rd_mode_t cde_qsb_rd_mode;
} mddr_comp_settings_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the clock source to be used for MDDR.
*
******************************************************************************/
typedef enum
{
    CLK_INTERNAL_CLKGEN,    //!< Internal Clock source is Clkgen.
    CLK_EXTERNAL_AGERA,     //!< External Clock source is Agera.
    CLK_NUM_TYPES           //!< Number of clock sources.
} mddr_clk_type_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the bank group address decode types for the
*    Bank group address bits[1:0] of the address decode control register
*
******************************************************************************/
typedef enum
{
    ADDR_DECODE_BG_MCA_16_15   = 0x0, // BG[1:0] are at MCA[16:15]
    ADDR_DECODE_BG_MCA_8_7     = 0x1, // BG[1:0] move to MCA[8:7]
    ADDR_DECODE_BG_MCA_16_7    = 0x2, // BG[1:0] move to MCA[16],MCA[7]
    ADDR_DECODE_BG_R_C_RK_B_BG = 0x3,  // Row, Column[9:4], Rank, Bank, Bank Group, Column[3:0] order
    ADDR_DECODE_BG_NUM_TYPES           //!< Number of address decode bank group types.
} mddr_bg_decode_type_t;


/*!****************************************************************************
*
* @par Description
*    This type provides the recognizable names for MDDR Bus Utilization Monitor
*     (BUM) Events.  Event numbers should correspond to the bit position of the
*     associated disable bit in the MDDR_DCVS_CNTL register.
*
* @par Members
*
*                                  <PRE>
*    DDR_BUM_EVENT_BCQFULL  BCQ Full Event Counter.
*    DDR_BUM_EVENT_BUSY     Busy Event Counter.
*                                  </PRE>
*
******************************************************************************/
typedef enum
{
    DDR_BUM_EVENT_BCQFULL,
    DDR_BUM_EVENT_BUSY,
    DDR_BUM_EVENT_MAX
}mddr_bum_event_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the MDDR Bus Utilization Monitor
*    (BUM) event setting for a particular event.
*
* @par Members
*
*                                  <PRE>
*    enable                   Indicates whether to enable the associated event.
*    lo_threshold             Indicates the low threshold value for each
*                              performance index for the associated event.
*    hi_threshold             Indicates the high threshold value for each
*                              performance index for the associated event.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    bool enable;
    uint32_t lo_threshold[DDR_BUM_PERF_IDX_MAX];
    uint32_t hi_threshold[DDR_BUM_PERF_IDX_MAX];
}mddr_bum_event_settings_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the MDDR Bus Utilization Monitor
*    (BUM) events.  The system is considerred oversubscribed if the BCQ Full
*    event count at the end of the measurement interval configured by the IMC is
*    higher than the high threshhold.  The system is considered undersubscribed
*    if the measurement count for Busy and BCQ Full event counts at the end of
*    the measurement interval configured by the IMC are both lower than the low
*    threshhold.
*
* @par Members
*
*                                  <PRE>
*    busy                     Describes the Busy event.
*    bcqfull                  Describes Back-end Comand Queue (BCQ) Full event.
*                                  </PRE>
*
******************************************************************************/

typedef struct
{
    mddr_bum_event_settings_t   busy;
    mddr_bum_event_settings_t   bcqfull;
}mddr_bum_settings_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to configure DDR PHY for addressing New DDR
*    training flow and right eye margin fix introduced by Hynix DDR DIMM issue.
*    In conjunction with PHY 0.94version, below settings are tunable.
*
* @par Members
*
*                                  <PRE>
*    ddrphy_mem40             Tuning value for PHY dmem40 register.
*    ddrphy_mem41             Tuning value for PHY dmem41 register.
*    ddrphy_mem42             Tuning value for PHY dmem42 register.
*    ddrphy_mem43             Tuning value for PHY dmem43 register.
*    ddrphy_xcnt              Xcnt value for Rd2D Read Group Sizes. This value
*                              combined to bit[1:0] of dmem41 register
*                                  </PRE>
*
******************************************************************************/

typedef struct
{
    uint16_t ddrphy_mem40;
    uint16_t ddrphy_mem41;
    uint16_t ddrphy_mem42;
    uint16_t ddrphy_mem43;
    uint16_t ddrphy_xcnt;
}mddr_phy_config_t;

/*!****************************************************************************
*
* @par Description
*    This type provides a container to group all for the high-level
*    configuration controls available to adjust the memory controller
*    initialization. Include both the hardware dependent settings and
*    the selectable / configurable options.
*
* @par Members
*
*                                  <PRE>
*    mem_freq_mhz               Array of target operation frequencies of the memory.
*                                Must be filled in sequentially. I.e. Skipping entries
*                                is not permitted and all unused entries must be filled
*                                in with the marker value DDR_FREQ_INVALID.
*                                This is the desired frequency
*    max_1dimm_freq_mhz         Max DDR clock set by software for 1 DIMM poped.
*                                This applies to 1DPC and 2DPC 1DIMM poped
*    max_2dimm_freq_mhz         Max DDR clock set by software for 2 DIMMs poped.
*                                This applies to 2DPC.
*    mddr_xo_freq_khz           Reference clock frequency.
*    allow_overclocking         Flag indicating if the DIMM speed grade should be ignored
*                                and the DIMMs forced to run at the requested frequency.
*    disable_ecc                Flag indicating if any DIMM ecc should be disabled.
*    ecc_wrrd_mode              Indicates the ECC read/write configuration,
*                                valid only if DIMM ecc is enabled
*    rs_quad_det_en             Indicates the Reed-Solomon quad detection configuration
*                                Valid only if ecc_wrrd_mode has RS_RD
*                                RS_QUAD_DET_DISABLE = single/double symbol correct, triple symbot detect
*                                RS_QUAD_DET_ENABLE = single symbol correct, double/triple/quad symbol detect
*    disable_patrol_scrub       Flag indicating if the ECC patrol scrub should be
*                                disabled when ECC is enabled. Only the initial
*                                scrub for ECC coherency will be performed.
*    comp_settings              Configuration structure for compression/decompression;
*                                valid only if 72bit DIMM
*    mddr_scrambling_en         Flag indicating if scrambling is to be enabled.
*    dbi_mode                   Indicates the DBI mode to use.
*    ca_parity                  Flag indicating if CA parity is to be enabled.
*    page_settings              Indicates the page related settings to use.
*    ddr_granule                Indicates the interleave mode / granule to use.
*    dimm_intlv_en              Flag indicating if DIMM interleaving is to be enabled.
*                                This field is for future expansion and the feature is
*                                currently unsupported.
*    rfc_mode                   Indicates the DDR refresh command rate.
*    auto_self_refresh_en       Flag indicating if memory controller based auto self
*                                refresh mode is to be enabled.
*    sr_entry_idle_delay        Self-refresh idle time. This is the delay, in number of DDR cycles,
*                                from the time that the controller is idle to the time that the
*                                controller puts the DRAM into self-refresh mode.
*    auto_power_down_en         Flag indicating if memory controller based auto power
*                                down mode is to be enabled.
*    pd_entry_idle_delay        Power-down idle time. This is the delay in number of DDR cycles
*                                from the time that the controller is idle to the time that the
*                                controller puts the DRAM into power down mode.
*    adj_ref_dimm0              Adjustment of DIMM0's refresh rate.
*    adj_ref_dimm1              Adjustment of DIMM1's refresh rate.
*    dfi_lp_mode                Indicates the PHY DFI Low Power Mode configuration.
*    dfi_lp2_entry_idle_delay   This is the delay, in number of DDR cycles, from the time
*                                the system enters-self-refresh until the controller puts the
*                                DDR PHY into DFI-LP2 state.  If the delay is non-zero, and if
*                                DFI-LP is enabled for self-refresh, then the PHY will enter
*                                DFI-LP state first.
*    ddr4_2t_preamble_mode      Defines the DDR4 2T preamble mode configuration to use.
*    num_dimm_slots             Number of DIMM slots physically present on a DDR
*                                channel. This is independent of if the slots are
*                                populated or not.
*    periodic_zq_cal_en         Flag indicating if periodic ZQ cals should be done
*                                by the MC.
*    shared_dimm_clk            Flag indicating if the clock is shared between the
*                                channels DIMMs. Only meaningful if the platform has
*                                2 slots per channel.
*    prop_delay                 Timing for propagation delay on DRAM DQ bus
*    extra_dqs_toggle           Number of extra DQS toggles to be appended to the end
*                                of the write data burst.
*    ca_stretch                 Indicates the number of stretch cycles for the CA bus
*                                before asserting the CS_n
*    ddr4_cal_mode_en           Flag indicating if DDR4 CAL mode is to be enabled.
*    ddr4_geardown_mode_en      Flag indicating if DDR4 geardown mode is to be enabled.
*    ddr4_wr_crc_en             Flag indicating if DDR4 write CRC mode is to be enabled.
*    therm_throttle_en          Flag indicating if thermal throttling is to be enabled.
*    clk_type                   Indicates the clock source to be used for MDDR.
*                                0x0 = Clkgen (Internal); 0x1 = Agera (External)
*    clkgen_ssc_en              Flag indicating if ClkGen Spread Spectrum Clocking
*                                is to be enabled.
*    bank_group_decode          Indicates the bank group address decode type
*    bum_settings               Bus Utilization Monitor event settings.
*    tcrit_event_en             Indicates SPD Temperature Sensor (TS) Critical
*                                Temperature (TCRIT) event is to be enabled.
*    tcrit_threshhold           Indicates SPD Temperature Sensor (TS) Critical
*                                Temperature (TCRIT) Limit in degrees C.
*    ecc_ce_threshold           Indicates ECC CE counter threshold when accumulated number of CE
*                                reaches threshold, ERROR_ECC_EC_TOTAL_CNTR is tirggered.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint16_t mem_freq_mhz[DDR_FREQ_ID_MAX];
    uint16_t max_1dimm_freq_mhz;
    uint16_t max_2dimm_freq_mhz;
    uint16_t mddr_xo_freq_khz;
    bool allow_overclocking;
    bool disable_ecc;
    mddr_ecc_wrrd_t ecc_wrrd_mode;
    uint8_t rs_quad_det_en;
    bool disable_patrol_scrub;
    mddr_comp_settings_t comp_settings;
    bool mddr_scrambling_en;
    mddr_ddr_dbi_t dbi_mode;
    mddr_ca_parity_t ca_parity;
    mddr_page_settings_t page_settings;
    mddr_ddr_intlv_t ddr_granule;
    bool dimm_intlv_en;
    mddr_rfc_cmd_mode_t rfc_mode;
    bool auto_self_refresh_en;
    uint16_t sr_entry_idle_delay;
    bool auto_power_down_en;
    uint16_t pd_entry_idle_delay;
    mddr_dimm_refresh_rate_t adj_ref_dimm0;
    mddr_dimm_refresh_rate_t adj_ref_dimm1;
    mddr_dfi_lpm_t dfi_lp_mode;
    uint16_t dfi_lp2_entry_idle_delay;
    mddr_ddr4_2t_preamble_t ddr4_2t_preamble_mode;
    uint8_t num_dimm_slots;
    bool periodic_zq_cal_en;
    bool shared_dimm_clk;
    uint8_t prop_delay;
    uint8_t extra_dqs_toggle;
    mddr_ca_stretch_t  ca_stretch;
    bool ddr4_cal_mode_en;
    bool ddr4_geardown_mode_en;
    bool ddr4_wr_crc_en;
    bool therm_throttle_en;
    mddr_clk_type_t clk_type;
    bool clkgen_ssc_en;
    mddr_bg_decode_type_t bank_group_decode;
    mddr_bum_settings_t bum_settings;
    bool tcrit_event_en;
    uint8_t tcrit_threshhold;
    uint16_t ecc_ce_threshold;
    bool CA_margin_enabled;
    mddr_phy_config_t phy_config;
} mddr_settings_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to collect the channel specific
*    configuration information so that it can be made available to higher level
*    software.
*
* @par Members
*
*                                  <PRE>
*    num_slots_supported    Number of slots in the channel.
*    num_slots_populated    Number of slots in the channel populated with DIMMs.
*    slot_map               Map of populated DIMM slots.
*    mem_size_gb            Amount of memory in GB populated in the channel.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t  num_slots_supported;
    uint8_t  num_slots_populated;
    uint8_t  slot_map;
    uint32_t mem_size_gb;
} mddr_chan_cfg_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to collect the overall MDDR configuration
*    so that it can be made available to higher level software.
*
* @par Members
*
*                                  <PRE>
*    num_chans_supported    Number of channels supported by the architecture.
*    num_chans_active       Number of channels poplated with DIMMs.
*    chan_map               Map of all active / populated channels.
*    chan_cfg               Array containing the channel specific configuration
*                            information for all channels.
*    mddr_settings          Common settings as currently configured. Primarily
*                            driven by settings setup during driver
*                            initialization.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t  num_chans_supported;
    uint8_t  num_chans_active;
    uint32_t chan_map;
    mddr_chan_cfg_t chan_cfg[DDR_MAX_NUM_CHANS];
    mddr_settings_t mddr_settings;
} mddr_cfg_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a select subset of the SPD information extracted from
*     a DIMM. The fields contain normalized versions of the information rather
*     than the raw data extracted from the DIMM.
*
* @par Members
*
*                                  <PRE>
*    dimm_spd    Array containing key extracted SPD information from all
*                 populated DIMM slots.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    spd_dimm_config_t dimm_spd[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
} mddr_spd_info_t;


/*!****************************************************************************
*
* @par Description
*    This type serves as a package to collect all all DIMM temperatures.
*
* @par Members
*
*                                  <PRE>
*    dimm_temps             Array containing ambient temperature information from
*                            each populated DIMM that contains a thermal sensor.
*    dimm_event_asserted    Array indicating whether the EVENT_n pin is asserted
*                            from each populated DIMM that contains a thermal sensor.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    int16_t dimm_temps[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
    bool dimm_eventn_asserted[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
} mddr_dimm_therm_t;


/*!****************************************************************************
*
* @par Description
*    This type serves as a package to collect all Bus Utilization Monitor (BUM)
*     information for all events (counters) on all populated channels,
*     during the programmed interval.  The primary index into the arrays
*     correspond to the physical (HSDDR) channel number.  The secondary index
*     into the arrays corresponds to the Event Type.
*
* @par Members
*
*                                  <PRE>
*    ddr_bum_counts   Array containing utilization counts for each channel and event
*                      during the programmed interval.
*    ddr_bum_enables  Array containing information for each channel on whether
*                      each event counter is enabled.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint32_t ddr_bum_counts[DDR_MAX_NUM_CHANS][DDR_BUM_EVENT_MAX];
    bool     ddr_bum_enables[DDR_MAX_NUM_CHANS][DDR_BUM_EVENT_MAX];
} mddr_bum_info_t;


/*!****************************************************************************
*
* @par Description
*    This type serves as a package to collect DDR sub-system state
*     information, including Power-Down, Self-Refresh, and Auto-Refresh.
*
* @par Members
*
*                                  <PRE>
*    dimm_in_pd         Array containing Power-Down state for all populated DIMMs.
*                        This will be set to true if any rank on the DIMM indicates
*                        it is in the Power-Down state.
*    dimm_in_sr         Array containing Self-Refresh state for all populated DIMMs.
*                        This will be set to true if any rank on the DIMM indicates
*                        it is in the Self-Refresh state.
*    dimm_ref_rate_adj  Array containing the Periodic Auto-Refresh DIMM Refresh Rate
*                        for all populated DIMMs.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    bool    dimm_in_pd[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
    bool    dimm_in_sr[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
    uint8_t dimm_ref_rate_adj[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
} mddr_state_info_t;



/******************************************************************************
* Global Variables
******************************************************************************/


/******************************************************************************
* Macros
******************************************************************************/
#define MDDR_DIMM_TEMP_WHOLE(_temp_) (_temp_ / 16)
#define MDDR_DIMM_TEMP_FRAC(_temp_)  ((((_temp_ > 0) ? _temp_ : -_temp_) % 16) * 625)
#define MDDR_GET_VAR_NAME(var) #var


/******************************************************************************
* Function Prototypes
******************************************************************************/

unsigned mddr_init(target_mode_e mode, soc_hw_version_t soc_hw_version, mddr_settings_t *mddr_settings_ptr);
unsigned mddr_margining_init(target_mode_e mode, soc_hw_version_t soc_hw_version, mddr_settings_t *mddr_settings_ptr);
void mddr_get_cfg_info(mddr_cfg_t *mddr_cfg_ptr);
void mddr_get_chan_cfg_info(uint8_t chan_num, mddr_chan_cfg_t *mddr_chan_cfg_ptr);
void mddr_get_spd_info(mddr_spd_info_t *spd_info_ptr);
void mddr_get_dimm_spd_info(uint8_t chan_num, uint8_t slot_num, spd_dimm_config_t *spd_info_ptr);
void mddr_get_therm_info(mddr_dimm_therm_t *dimm_therm_ptr);
int16_t mddr_get_dimm_temp(uint8_t chan_num, uint8_t slot_num);
bool mddr_get_dimm_eventn_asserted(uint8_t chan_num, uint8_t slot_num);

void mddr_get_bum_info(mddr_bum_info_t *dimm_bum_counts_ptr);
void get_ddr_state(mddr_state_info_t *mddr_state_info_ptr);


void mddr_mc_enable_clocks(uint64_t mddr_base_addr);
uint32_t mddr_determine_ddr_type(target_mode_e mode, uint8_t ddr_chan);

void mddr_wd_reset_graceful_stop(void);
void mddr_wd_reset_phy_reactivate(void);
void mddr_wd_reset_prep_for_reset(void);
unsigned mddr_wd_reset_reinit(target_mode_e mode, soc_hw_version_t soc_hw_version, mddr_settings_t *mddr_settings_ptr);
void mddr_mc_wd_enable_clocks(uint64_t mddr_base_addr);

/*****************************************************************************/
#endif
