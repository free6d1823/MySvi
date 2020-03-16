#ifndef _MODULE_L3_DEFS_H_
#define _MODULE_L3_DEFS_H_

/*!****************************************************************************
*
* @copyright Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
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
* @file l3_defs.h
*
* @par Description:
*    This header provides various macros, register offsets, field and other
*    definitions and function prototypes necessary to configure the L3 caches.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <asm/mach/monaco/common/common_defs.h>
#include <asm/mach/monaco/common/monaco_defs.h>


/******************************************************************************
* Defined Constants in the QLL and APB spaces
******************************************************************************/

/******************************************************************************
* Defined Constants in the QLL Space
******************************************************************************/
// QLL: HML3 Region (CSR, CFG, PM, QoS) Offsets (on top of the Ring Config
//  Base, RING_CONFIG_BASE).
//#define HML3_CSR_OFFSET        0x00000000
//#define HML3_CFG_OFFSET        0x00010000
//#define HML3_PM_OFFSET         0x00020000
//#define HML3_QOS_OFFSET        0x00030000

// QLL: L3_x Offsets (on top of the Ring Config Base and L3 Region offsets above)
//#define L3_0_QLL_OFFSET        0x00580000
#define L3_1_QLL_OFFSET        0x00680000
#define L3_2_QLL_OFFSET        0x00780000
#define L3_3_QLL_OFFSET        0x00880000
#define L3_4_QLL_OFFSET        0x00980000
#define L3_5_QLL_OFFSET        0x00A80000
#define L3_6_QLL_OFFSET        0x00B80000
#define L3_7_QLL_OFFSET        0x00C80000
#define L3_8_QLL_OFFSET        0x00D80000
#define L3_9_QLL_OFFSET        0x00E80000
#define L3_10_QLL_OFFSET       0x00F80000
#define L3_11_QLL_OFFSET       0x01080000

// QLL: L3_x base addresses.
//#define L3_0_QLL_BASE   (RING_CONFIG_BASE + L3_0_QLL_OFFSET)    // 0xFF_8058_0000
#define L3_1_QLL_BASE   (RING_CONFIG_BASE + L3_1_QLL_OFFSET)    // 0xFF_8068_0000
#define L3_2_QLL_BASE   (RING_CONFIG_BASE + L3_2_QLL_OFFSET)    // 0xFF_8078_0000
#define L3_3_QLL_BASE   (RING_CONFIG_BASE + L3_3_QLL_OFFSET)    // 0xFF_8088_0000
#define L3_4_QLL_BASE   (RING_CONFIG_BASE + L3_4_QLL_OFFSET)    // 0xFF_8098_0000
#define L3_5_QLL_BASE   (RING_CONFIG_BASE + L3_5_QLL_OFFSET)    // 0xFF_80A8_0000
#define L3_6_QLL_BASE   (RING_CONFIG_BASE + L3_6_QLL_OFFSET)    // 0xFF_80B8_0000
#define L3_7_QLL_BASE   (RING_CONFIG_BASE + L3_7_QLL_OFFSET)    // 0xFF_80C8_0000
#define L3_8_QLL_BASE   (RING_CONFIG_BASE + L3_8_QLL_OFFSET)    // 0xFF_80D8_0000
#define L3_9_QLL_BASE   (RING_CONFIG_BASE + L3_9_QLL_OFFSET)    // 0xFF_80E8_0000
#define L3_10_QLL_BASE  (RING_CONFIG_BASE + L3_10_QLL_OFFSET)   // 0xFF_80F8_0000
#define L3_11_QLL_BASE  (RING_CONFIG_BASE + L3_11_QLL_OFFSET)   // 0xFF_8108_0000

// QLL: L3 CSR/CFG Register Offsets
#define HML3_CSR_ALOCR_OFFSET        0x4004  // CSR Common : How and when lines are allocated in L3
#define HML3_CFG_ARYCA_OFFSET        0x5110  // CFG Common:  Array control reg A
#define HML3_CFG_ARYCB_OFFSET        0x5114  // CFG Common:  Array control reg B
#define HML3_CFG_ARYCC_OFFSET        0x5118  // CFG Common:  Array control reg C
#define HML3_CFG_ASTCA0_OFFSET       0x6210  // CFG Itlv0: Controls Trace Bus Sel, trace triggers, dumping trace data into local data arrays - reg A
#define HML3_CFG_ASTCA1_OFFSET       0x6310  // CFG Itlv1: same as above
#define HML3_CFG_ASTCB0_OFFSET       0x6214  // CFG Itlv0: same as above -reg B
#define HML3_CFG_ASTCB1_OFFSET       0x6314  // CFG Itlv1: same as above
#define HML3_CSR_CECNT_OFFSET        0x1564  // CSR Common: Reports a count of detected ECC errors for each group of arrays
#define HML3_CFG_CJSCTL_OFFSET       0xA000  // CFG Common: Controls the clock jitter sensor
#define HML3_CFG_CJSD0_OFFSET        0xA008  // CFG Common: Reports data from the clock jitter sensor - reg 0
#define HML3_CFG_CJSD1_OFFSET        0xA00C  // CFG Common: same as above  - reg 1
#define HML3_CFG_CJSD2_OFFSET        0xA010  // CFG Common: same as above  - reg 2
#define HML3_CFG_CJSD3_OFFSET        0xA014  // CFG Common: same as above  - reg 3
#define HML3_CFG_CJSD4_OFFSET        0xA018  // CFG Common: same as above  - reg 4
#define HML3_CFG_CJSD5_OFFSET        0xA01C  // CFG Common: same as above  - reg 5
#define HML3_CFG_CR0_OFFSET          0x5200  // CFG Itlv0: Some Config Control
#define HML3_CFG_CR1_OFFSET          0x5300  // CFG Itlv1: Config Control
#define HML3_CFG_CRA_OFFSET          0x7020  // CFG Common: Config Control - reg A. Control bits and misc
#define HML3_CFG_CRB_OFFSET          0x7024  // CFG Common: Config Control - reg B. Same as above
#define HML3_CSR_CRC_OFFSET          0x1860  // CSR Common: Config Control - reg C. Causes single cycle control pulses
#define HML3_CFG_CRD_OFFSET          0x702C  // CFG Common: Config Control - reg D i.e. disable/lockdown features
#define HML3_CFG_DAEERR0_OFFSET      0x324C  // CFG Itlv 0: Reports detected ECC errors for data arrays
#define HML3_CFG_DAEERR1_OFFSET      0x334C  // CFG Itlv 1: same as above
#define HML3_CSR_DCHSEL0_OFFSET      0x0614  // CSR Itlv 0: Data Ch. Sel. The strap bit values set to select outbound data (for dest PID) for system bus
#define HML3_CSR_DCHSEL1_OFFSET      0x0714  // CSR Itlv 1: same as above
#define HML3_CFG_DCRSWCR_OFFSET      0x3000  // CFG Common: Data Cache Read Set Way Control reg
#define HML3_CFG_DCRSWDA0_OFFSET     0x3200  // CFG Itlv 0: Data Cache Read Set Way Data - reg A
#define HML3_CFG_DCRSWDA1_OFFSET     0x3300  // CFG Interleave 1: same as above
#define HML3_CFG_DCRSWDB0_OFFSET     0x3204  // CFG Interleave 0: Data Cache Read Set Way Data - reg B
#define HML3_CFG_DCRSWDB1_OFFSET     0x3304  // CFG Interleave 1: same as above
#define HML3_CFG_DCRSWDC0_OFFSET     0x3208  // CFG Interleave 0: Data Cache Read Set Way Data - reg C
#define HML3_CFG_DCRSWDC1_OFFSET     0x3308  // CFG Interleave 1: same as above
#define HML3_CFG_DCRSWDD0_OFFSET     0x320C  // CFG Interleave 0: Data Cache Read Set Way Data - reg D
#define HML3_CFG_DCRSWDD1_OFFSET     0x330C  // CFG Interleave 1: same as above
#define HML3_CFG_DCRSWDE0_OFFSET     0x3210  // CFG Interleave 0: Data Cache Read Set Way Data - reg E
#define HML3_CFG_DCRSWDE1_OFFSET     0x3310  // CFG Interleave 1: same as above
#define HML3_CFG_DCRSWTA0_OFFSET     0x3218  // CFG Interleave 0: Data Cache Read Set Way Tag - reg A
#define HML3_CFG_DCRSWTA1_OFFSET     0x3318  // CFG Interleave 1: same as above
#define HML3_CFG_DCRSWTB0_OFFSET     0x321C  // CFG Interleave 0: Data Cache Read Set Way Tag - reg B
#define HML3_CFG_DCRSWTB1_OFFSET     0x331C  // CFG Interleave 1: same as above
#define HML3_CFG_DCRSWTC0_OFFSET     0x3220  // CFG Itlv0: Data Cache Read Set Way Tag - reg C
#define HML3_CFG_DCRSWTC1_OFFSET     0x3320  // CFG Itlv1: same as above
#define HML3_CFG_FAICCRA0_OFFSET     0x2208  // CFG Interleave 0: Flush Allocation Invalidation Control - reg A
#define HML3_CFG_FAICCRA1_OFFSET     0x2308  // CFG Interleave 1: same as above
#define HML3_CFG_FAICCRB0_OFFSET     0x220C  // CFG Interleave 0: Flush Allocation Invalidation Control - reg B
#define HML3_CFG_FAICCRB1_OFFSET     0x230C  // CFG Interleave 1: same as above
#define HML3_CFG_FAICCRC0_OFFSET     0x2210  // CFG Interleave 0: Flush Allocation Invalidation Control - reg C
#define HML3_CFG_FAICCRC1_OFFSET     0x2310  // CFG Interleave 1: same as above
#define HML3_CFG_FAICSR0_OFFSET      0x223C  // CFG Interleave 0: Flush Allocation Invalidation Status
#define HML3_CFG_FAICSR1_OFFSET      0x233C  // CFG Interleave 1: same as above
#define HML3_CSR_FIRA_OFFSET         0x1000  // CSR Common: Fault Isolation #define  Reporting - reg A
#define HML3_CSR_FIRAC_OFFSET        0x1008  // CSR Common: Fault Isolation #define  Reporting Clear - reg A
#define HML3_CSR_FIRAME_OFFSET       0x1140  // CSR Common: Fault Isolation unMasked Error - reg A
#define HML3_CSR_FIRAMI_OFFSET       0x1120  // CSR Common: Fault Isolation unMasked Info - reg A
#define HML3_CSR_FIRAS_OFFSET        0x1010  // CSR Common: Fault Isolation #define  Reporting Set - reg A
#define HML3_CSR_FIRAT0_OFFSET       0x1020  // CSR Common: FIRA Type 0 reg
#define HML3_CSR_FIRAT0C_OFFSET      0x1028  // CSR Common: FIRA Type 0 Clear reg
#define HML3_CSR_FIRAT0S_OFFSET      0x1030  // CSR Common: FIRA Type 0 Set reg
#define HML3_CSR_FIRAT1_OFFSET       0x1040  // CSR Common: FIRA Type 1 reg
#define HML3_CSR_FIRAT1C_OFFSET      0x1048  // CSR Common: FIRA Type 1 Clear reg
#define HML3_CSR_FIRAT1S_OFFSET      0x1050  // CSR Common: FIRA Type 1 Set reg
#define HML3_CSR_FIRSYNA_OFFSET      0x1440  // CSR Common: Fault Isolation Syndrome - reg A
#define HML3_CSR_FIRSYNB_OFFSET      0x1444  // CSR Common: Fault Isolation Syndrome - reg B
#define HML3_CSR_FIRSYNC_OFFSET      0x1448  // CSR Common: Fault Isolation Syndrome - reg C
#define HML3_CSR_FIRSYND_OFFSET      0x144C  // CSR Common: Fault Isolation Syndrome - reg D
#define HML3_CFG_FUSEDATH_OFFSET     0x302C  // CFG Common: Fuse Data HI reg
#define HML3_CFG_FUSEDATL_OFFSET     0x3028  // CFG Common: Fuse Data LO reg
#define HML3_CFG_FUSEIDX_OFFSET      0x3024  // CFG Common: Fuse Index
#define HML3_CFG_HCRA_OFFSET         0x5010  // CFG Common: Hidden config - reg A
#define HML3_CFG_HPDIV_OFFSET        0x5014  // CFG Common: Hang Pulse Division
#define HML3_CFG_HSHMCTL_OFFSET      0x705C  // CFG Common: Hash Mask Control
#define HML3_CSR_HW_SERIES_OFFSET    0x0004  // CSR Common: Reports HW Series to which this revision belongs
#define HML3_CSR_HW_VERSION_OFFSET   0x0000  // CSR Common: Reports HW L3 functional version number
#define HML3_CSR_ID_OFFSET           0x0008  // CSR Common: Reports Instance ID i.e. the strap bits that assign the L3 inst and corresp. sys bus ID
#define HML3_CFG_INJERR0_OFFSET      0x9210  // CFG Interleave 0: Controls HW Injection of ECC Errors into data and tag banks
#define HML3_CFG_INJERR1_OFFSET      0x9310  // CFG Interleave 1: same
#define HML3_CFG_LLBCR_OFFSET        0x7038  // CFG Common: Controls LiveLock Breaker i.e. sending of livelock query and livelock backoff ops on the bus
#define HML3_CFG_LLBQF_OFFSET        0x703C  // CFG Common: Controls LiveLock Breaker Query Frequency
#define HML3_CSR_LLBSR0_OFFSET       0x1A20  // CSR Itlv 0: Reports LiveLock Breaker Bus Status
#define HML3_CSR_LLBSR1_OFFSET       0x1B20  // CSR Itlv 1: same as above
#define HML3_CSR_LLKCR_OFFSET        0x4010  // CSR Common: Controls how Line Locks are set
#define HML3_CFG_POSCRA_OFFSET       0x5020  // CFG Common: Controls common POS params - reg A
#define HML3_CFG_POSCRB_OFFSET       0x5024  // CFG Common: Controls common POS params - reg B
#define HML3_CFG_POSCRC_OFFSET       0x7008  // CFG Common: Controls common POS params - reg C
#define HML3_CFG_POSCRD_OFFSET       0x502C  // CFG Common: Controls common POS params - reg D
#define HML3_CFG_PSCRA_OFFSET        0x7040  // CFG Common: Power State Control - reg A. Controls the Power States
#define HML3_CFG_PSCRB_OFFSET        0x7044  // CFG Common: Power State Control - reg B. Controls clock OFF and sleep request timers
#define HML3_CFG_PSCRC_OFFSET        0x5038  // CFG Common: Power State Control - reg C. Controls part of Power Management
#define HML3_CFG_PSCRD_OFFSET        0x503C  // CFG Common: Power State Control - reg D. Manages L3 energy usage. DATA_B2BDLY, min spacing between data arry reqs in idle cycles moved from POSCRA
#define HML3_CFG_QBCR_OFFSET         0x7070  // CFG Common: QoS Beacon control. Controls timer-based QoS Beacon snoops
// moved to monaco_defs.h
//#define HML3_CFG_QCCMCR_OFFSET       0x4050  // CFG Common: QoS Cache Capacity Monitoring (CCM) Read Control. Controls behaviour of QoS CCM funct.
//#define HML3_CFG_QCCECR_OFFSET       0x4060  // CFG Common: QoS Cache Capacity Enforcement Control
// L3 QoS regs....
#define HML3_CFG_RSCTL_OFFSET        0xB008  // CFG Common: L3 Register Security Control i.e., whether non-secure processes may access each reg group
#define HML3_CFG_SFAEERR0_OFFSET     0x3244  // CFG Interleave 0: Snoop Filter Array ECC Error Reporting
#define HML3_CFG_SFAEERR1_OFFSET     0x3344  // CFG Interleave 1: same as above
#define HML3_CFG_SFTCR_OFFSET        0x5050  // CFG Common: Snoop Filter Control
#define HML3_CFG_SFTPGC0_OFFSET      0x5254  // CFG Interleave 0: Snoop Filter Partial Good Control
#define HML3_CFG_SFTPGC1_OFFSET      0x5354  // CFG Interleave 1: same as above
#define HML3_CSR_SFTSR0_OFFSET       0x1A14  // CSR Itlv 0: Snoop Filter Suspend Reporting reg
#define HML3_CSR_SFTSR1_OFFSET       0x1B14  // CSR Itlv 1: same as above
#define HML3_CSR_SFTVPMA_OFFSET      0x0440  // CSR Common: Snoop Filter Vector PID Map - reg A
#define HML3_CSR_SFTVPMB_OFFSET      0x0444  // CSR Common: Snoop Filter Vector PID Map - reg B
#define HML3_CSR_SFTVPMC_OFFSET      0x0448  // CSR Common: Snoop Filter Vector PID Map - reg C
#define HML3_CSR_SR0_OFFSET          0x1A04  // CSR Itlv 0: Status Info
#define HML3_CSR_SR1_OFFSET          0x1B04  // CSR Itlv 1: same as above
#define HML3_CFG_TAEERR0_OFFSET      0x3240  // CFG Interleave 0: Tag Array ECC Error Reporting
#define HML3_CFG_TAEERR1_OFFSET      0x3340  // CFG Interleave 1: same as above
#define HML3_CFG_TCMAACA0_OFFSET     0x2200  // CFG Interleave 0: TCM Allocation Address Control - reg A
#define HML3_CFG_TCMAACA1_OFFSET     0x2300  // CFG Itlv1: same as above
#define HML3_CFG_TCMAACB0_OFFSET     0x2204  // CFG Interleave 0: TCM Allocation Address Control - reg B
#define HML3_CFG_TCMAACB1_OFFSET     0x2304  // CFG Interleave 1: same as above
#define HML3_CFG_WDCR0_OFFSET        0x6208  // CFG Interleave 0: Way Disable Control
#define HML3_CFG_WDCR1_OFFSET        0x6308  // CFG Interleave 1: same as above
#define HML3_CFG_WMCR0_OFFSET        0x620C  // CFG Interleave 0: 20-bit Way Mask Vector Control
#define HML3_CFG_WMCR1_OFFSET        0x630C  // CFG Interleave 1: same as above


// QLL: L3 Performance Mgmt Register Offsets
#define HML3_PM_QLL_CNTCTL0_OFFSET    0x8120  // Performance Monitor Counter Control Register 0
#define HML3_PM_QLL_CNTCTL1_OFFSET    0x8128  // Performance Monitor Counter Control Register 1
#define HML3_PM_QLL_CNTCTL2_OFFSET    0x8130  // Performance Monitor Counter Control Register 2
#define HML3_PM_QLL_CNTCTL3_OFFSET    0x8138  // Performance Monitor Counter Control Register 3
#define HML3_PM_QLL_CNTCTL4_OFFSET    0x8140  // Performance Monitor Counter Control Register 4
#define HML3_PM_QLL_CNTCTL5_OFFSET    0x8148  // Performance Monitor Counter Control Register 5
#define HML3_PM_QLL_CNTCTL6_OFFSET    0x8150  // Performance Monitor Counter Control Register 6
#define HML3_PM_QLL_CNTCTL7_OFFSET    0x8158  // Performance Monitor Counter Control Register 7
#define HML3_PM_QLL_CNTRLDA_OFFSET    0x8320  // Performance Monitor Counter Reload - reg A
#define HML3_PM_QLL_CNTRLDB_OFFSET    0x8328  // Performance Monitor Counter Reload - reg B
#define HML3_PM_QLL_CR_OFFSET         0x8000  // Performance Monitors Control

// HML3_PM_QLL_CNTCTLx_OFFSETS moved to monaco_defs.h

#define HML3_PM_QLL_EVTYPER0_OFFSET   0x8220  // Performance Monitor Event Type Register 0
#define HML3_PM_QLL_EVTYPER1_OFFSET   0x8228  // Performance Monitor Event Type Register 1
#define HML3_PM_QLL_EVTYPER2_OFFSET   0x8230  // Performance Monitor Event Type Register 2
#define HML3_PM_QLL_EVTYPER3_OFFSET   0x8238  // Performance Monitor Event Type Register 3
#define HML3_PM_QLL_EVTYPER4_OFFSET   0x8240  // Performance Monitor Event Type Register 4
#define HML3_PM_QLL_EVTYPER5_OFFSET   0x8248  // Performance Monitor Event Type Register 5
#define HML3_PM_QLL_EVTYPER6_OFFSET   0x8250  // Performance Monitor Event Type Register 6
#define HML3_PM_QLL_EVTYPER7_OFFSET   0x8258  // Performance Monitor Event Type Register 7
#define HML3_PM_QLL_FILTRA_OFFSET     0x8300  // Performance Monitor Event Filter A
#define HML3_PM_QLL_FILTRAM_OFFSET    0x8304  // Performance Monitor Event Filter A Mask
#define HML3_PM_QLL_FILTRB_OFFSET     0x8308  // Performance Monitor Event Filter B
#define HML3_PM_QLL_FILTRBM_OFFSET    0x830C  // Performance Monitor Event Filter B Mask
#define HML3_PM_QLL_FILTRC_OFFSET     0x8310  // Performance Monitor Event Filter C
#define HML3_PM_QLL_FILTRCM_OFFSET    0x8314  // Performance Monitor Event Filter C Mask
#define HML3_PM_QLL_OVSS_OFFSET       0x8008  // Performance Monitor Overflow Status Set
#define HML3_PM_QLL_XCNTCTL_OFFSET    0x8010  // Performance Monitor Selected Counter Control Register
#define HML3_PM_QLL_XEVTYPER_OFFSET   0x8018  // Performance Monitor Selected Event Type Register
// QLL: L3 PM Basic counters (BC)
#define M_BC_QLL_CNTENCLR_OFFSET      0x850C   // BCSubunit Counter Enable Clear Register
#define M_BC_QLL_CNTENSET_OFFSET      0x8508   // BCSubunit Counter Enable Set Register
#define M_BC_QLL_CNTR_LO_OFFSET       0x8748   // BCSubunit Count LO Register
#define M_BC_QLL_CR_OFFSET            0x8500   // BCSubunit Global Control Register
#define M_BC_QLL_GANG_OFFSET          0x8718   // BCSubunit Ganging Control Register
#define M_BC_QLL_INTENCLR_OFFSET      0x8514   // BCSubunit Counter Interrupt Enable Clear Register
#define M_BC_QLL_INTENSET_OFFSET      0x8510   // BCSubunit Counter Interrupt Enable Set Register
#define M_BC_QLL_OVERFLOW0_OFFSET     0x871C   // BCSubunit Counter Overflow Configuration Register 0
#define M_BC_QLL_OVERFLOW1_OFFSET     0x8720   // BCSubunit Counter Overflow Configuration Register 1
#define M_BC_QLL_OVSR_OFFSET          0x8740   // BCSubunit Counter Rollover #define  Saturation Status Register
#define M_BC_QLL_SATROLL_CR_OFFSET    0x8504   // BCSubunit Saturation #define  Rollover Control Register
#define M_BC_QLL_SELR_OFFSET          0x8744   // BCSubunit Counter Selection Register
#define M_BC_QLL_SHADOW0_LO_OFFSET    0x8750   // BCSubunit APB Retrieval Shadow LO Register 0
#define M_BC_QLL_SHADOW1_LO_OFFSET    0x8754   // BCSubunit APB Retrieval Shadow LO Register 1
#define M_BC_QLL_SHADOW2_LO_OFFSET    0x8758   // BCSubunit APB Retrieval Shadow LO Register 2
#define M_BC_QLL_SHADOW3_LO_OFFSET    0x875C   // BCSubunit APB Retrieval Shadow LO Register 3
#define M_BC_QLL_SHADOW4_LO_OFFSET    0x8760   // BCSubunit APB Retrieval Shadow LO Register 4
#define M_BC_QLL_SHADOW5_LO_OFFSET    0x8764   // BCSubunit APB Retrieval Shadow LO Register 5
#define M_BC_QLL_SHADOW6_LO_OFFSET    0x8768   // BCSubunit APB Retrieval Shadow LO Register 6
#define M_BC_QLL_SHADOW7_LO_OFFSET    0x876C   // BCSubunit APB Retrieval Shadow LO Register 7
#define M_BC_QLL_SWINC_OFFSET         0x8950   // Performance Monitor Software Increment Register
#define M_BC_QLL_IRQCTL_OFFSET        0x896C   // BCSubunit Counter Interrupt Mode Control


// QLL: L3 CSR/CFG Register Offsets - in Alphabetical Order
#define HML3_ALOCR_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_ALOCR_OFFSET)   // 0x00000000 + 0x4004 = 0x00004004
#define HML3_ARYCA_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_ARYCA_OFFSET)   // 0x00010000 + 0x5110 = 0x00015110
#define HML3_ARYCB_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_ARYCB_OFFSET)
#define HML3_ARYCC_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_ARYCC_OFFSET)
#define HML3_ASTCA0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_ASTCA0_OFFSET)
#define HML3_ASTCA1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_ASTCA1_OFFSET)
#define HML3_ASTCB0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_ASTCB0_OFFSET)
#define HML3_ASTCB1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_ASTCB1_OFFSET)
#define HML3_CECNT_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_CECNT_OFFSET)
#define HML3_CJSCTL_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_CJSCTL_OFFSET)
#define HML3_CJSD0_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_CJSD0_OFFSET)
#define HML3_CJSD1_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_CJSD1_OFFSET)
#define HML3_CJSD2_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_CJSD2_OFFSET)
#define HML3_CJSD3_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_CJSD3_OFFSET)
#define HML3_CJSD4_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_CJSD4_OFFSET)
#define HML3_CJSD5_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_CJSD5_OFFSET)
#define HML3_CR0_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_CR0_OFFSET)  // CFG Itlv0: Some Config Control
#define HML3_CR1_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_CR1_OFFSET)  // CFG Itlv1: Config Control
#define HML3_CRA_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_CRA_OFFSET)
#define HML3_CRB_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_CRB_OFFSET)
#define HML3_CRC_OFFSET        (HML3_CSR_OFFSET + HML3_CSR_CRC_OFFSET)
#define HML3_CRD_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_CRD_OFFSET)
#define HML3_DAEERR0_OFFSET    (HML3_CFG_OFFSET + HML3_CFG_DAEERR0_OFFSET)
#define HML3_DAEERR1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DAEERR1_OFFSET)
#define HML3_DCHSEL0_OFFSET     (HML3_CSR_OFFSET + HML3_CSR_DCHSEL0_OFFSET)
#define HML3_DCHSEL1_OFFSET     (HML3_CSR_OFFSET + HML3_CSR_DCHSEL1_OFFSET)
#define HML3_DCRSWCR_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWCR_OFFSET)
#define HML3_DCRSWDA0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDA0_OFFSET)
#define HML3_DCRSWDA1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDA1_OFFSET)
#define HML3_DCRSWDB0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDB0_OFFSET)
#define HML3_DCRSWDB1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDB1_OFFSET)
#define HML3_DCRSWDC0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDC0_OFFSET)
#define HML3_DCRSWDC1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDC1_OFFSET)
#define HML3_DCRSWDD0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDD0_OFFSET)
#define HML3_DCRSWDD1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDD1_OFFSET)
#define HML3_DCRSWDE0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDE0_OFFSET)
#define HML3_DCRSWDE1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWDE1_OFFSET)
#define HML3_DCRSWTA0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWTA0_OFFSET)
#define HML3_DCRSWTA1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWTA1_OFFSET)
#define HML3_DCRSWTB0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWTB0_OFFSET)
#define HML3_DCRSWTB1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWTB1_OFFSET)
#define HML3_DCRSWTC0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWTC0_OFFSET)  // CFG Itlv0: Data Cache Read Set Way Tag - reg C
#define HML3_DCRSWTC1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_DCRSWTC1_OFFSET)  // CFG Itlv1: same as above
#define HML3_FAICCRA0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_FAICCRA0_OFFSET)
#define HML3_FAICCRA1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_FAICCRA1_OFFSET)
#define HML3_FAICCRB0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_FAICCRB0_OFFSET)
#define HML3_FAICCRB1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_FAICCRB1_OFFSET)
#define HML3_FAICCRC0_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_FAICCRC0_OFFSET)  // CFG Interleave 0: Flush Allocation Invalidation Control - reg C
#define HML3_FAICCRC1_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_FAICCRC1_OFFSET)  // CFG Interleave 1: same as above
#define HML3_FAICSR0_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_FAICSR0_OFFSET)
#define HML3_FAICSR1_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_FAICSR1_OFFSET)
#define HML3_FIRA_OFFSET         (HML3_CSR_OFFSET + HML3_CSR_FIRA_OFFSET)
#define HML3_FIRAC_OFFSET        (HML3_CSR_OFFSET + HML3_CSR_FIRAC_OFFSET)
#define HML3_FIRAME_OFFSET       (HML3_CSR_OFFSET + HML3_CSR_FIRAME_OFFSET)
#define HML3_FIRAMI_OFFSET       (HML3_CSR_OFFSET + HML3_CSR_FIRAMI_OFFSET)
#define HML3_FIRAS_OFFSET        (HML3_CSR_OFFSET + HML3_CSR_FIRAS_OFFSET)
#define HML3_FIRAT0_OFFSET       (HML3_CSR_OFFSET + HML3_CSR_FIRAT0_OFFSET)
#define HML3_FIRAT0C_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_FIRAT0C_OFFSET)
#define HML3_FIRAT0S_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_FIRAT0S_OFFSET)
#define HML3_FIRAT1_OFFSET       (HML3_CSR_OFFSET + HML3_CSR_FIRAT1_OFFSET)
#define HML3_FIRAT1C_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_FIRAT1C_OFFSET)
#define HML3_FIRAT1S_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_FIRAT1S_OFFSET)
#define HML3_FIRSYNA_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_FIRSYNA_OFFSET)
#define HML3_FIRSYNB_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_FIRSYNB_OFFSET)
#define HML3_FIRSYNC_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_FIRSYNC_OFFSET)
#define HML3_FIRSYND_OFFSET      (HML3_CSR_OFFSET + HML3_CSR_FIRSYND_OFFSET)
#define HML3_FUSEDATH_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_FUSEDATH_OFFSET)
#define HML3_FUSEDATL_OFFSET     (HML3_CFG_OFFSET + HML3_CFG_FUSEDATL_OFFSET)
#define HML3_FUSEIDX_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_FUSEIDX_OFFSET)
#define HML3_HCRA_OFFSET         (HML3_CFG_OFFSET + HML3_CFG_HCRA_OFFSET)
#define HML3_HPDIV_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_HPDIV_OFFSET)
#define HML3_HSHMCTL_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_HSHMCTL_OFFSET)
#define HML3_HW_SERIES_OFFSET    (HML3_CSR_OFFSET + HML3_CSR_HW_SERIES_OFFSET)
#define HML3_HW_VERSION_OFFSET   (HML3_CSR_OFFSET + HML3_CSR_HW_VERSION_OFFSET)
#define HML3_ID_OFFSET           (HML3_CSR_OFFSET + HML3_CSR_ID_OFFSET)
#define HML3_INJERR0_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_INJERR0_OFFSET)
#define HML3_INJERR1_OFFSET      (HML3_CFG_OFFSET + HML3_CFG_INJERR1_OFFSET)
#define HML3_LLBCR_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_LLBCR_OFFSET)
#define HML3_LLBQF_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_LLBQF_OFFSET)
#define HML3_LLBSR0_OFFSET       (HML3_CSR_OFFSET + HML3_CSR_LLBSR0_OFFSET)
#define HML3_LLBSR1_OFFSET       (HML3_CSR_OFFSET + HML3_CSR_LLBSR1_OFFSET)
#define HML3_LLKCR_OFFSET        (HML3_CSR_OFFSET + HML3_CSR_LLKCR_OFFSET)
#define HML3_POSCRA_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_POSCRA_OFFSET)
#define HML3_POSCRB_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_POSCRB_OFFSET)
#define HML3_POSCRC_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_POSCRC_OFFSET)
#define HML3_POSCRD_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_POSCRD_OFFSET)
#define HML3_PSCRA_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_PSCRA_OFFSET)
#define HML3_PSCRB_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_PSCRB_OFFSET)
#define HML3_PSCRC_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_PSCRC_OFFSET)
#define HML3_PSCRD_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_PSCRD_OFFSET)
#define HML3_QBCR_OFFSET         (HML3_CFG_OFFSET + HML3_CFG_QBCR_OFFSET)
// HML3_QCCMCR/ECR_OFFSET moved to monaco_defs.h

// L3 QoS regs......
#define HML3_RSCTL_OFFSET          (HML3_CFG_OFFSET + HML3_CFG_RSCTL_OFFSET)
#define HML3_SFAEERR0_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_SFAEERR0_OFFSET)
#define HML3_SFAEERR1_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_SFAEERR1_OFFSET)
#define HML3_SFTCR_OFFSET          (HML3_CFG_OFFSET + HML3_CFG_SFTCR_OFFSET)
#define HML3_SFTPGC0_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_SFTPGC0_OFFSET)
#define HML3_SFTPGC1_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_SFTPGC1_OFFSET)
#define HML3_SFTSR0_OFFSET         (HML3_CSR_OFFSET + HML3_CSR_SFTSR0_OFFSET)
#define HML3_SFTSR1_OFFSET         (HML3_CSR_OFFSET + HML3_CSR_SFTSR1_OFFSET)
#define HML3_SFTVPMA_OFFSET        (HML3_CSR_OFFSET + HML3_CSR_SFTVPMA_OFFSET)
#define HML3_SFTVPMB_OFFSET        (HML3_CSR_OFFSET + HML3_CSR_SFTVPMB_OFFSET)
#define HML3_SFTVPMC_OFFSET        (HML3_CSR_OFFSET + HML3_CSR_SFTVPMC_OFFSET)
#define HML3_SR0_OFFSET            (HML3_CSR_OFFSET + HML3_CSR_SR0_OFFSET)
#define HML3_SR1_OFFSET            (HML3_CSR_OFFSET + HML3_CSR_SR1_OFFSET)
#define HML3_TAEERR0_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_TAEERR0_OFFSET)
#define HML3_TAEERR1_OFFSET        (HML3_CFG_OFFSET + HML3_CFG_TAEERR1_OFFSET)

//  These regs help each L3 instance determine which address belong to it when
//  executing the FAIC-Allocate function
#define HML3_TCMAACA0_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_TCMAACA0_OFFSET)
#define HML3_TCMAACA1_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_TCMAACA1_OFFSET)
#define HML3_TCMAACB0_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_TCMAACB0_OFFSET)
#define HML3_TCMAACB1_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_TCMAACB1_OFFSET)

#define HML3_WDCR0_OFFSET          (HML3_CFG_OFFSET + HML3_CFG_WDCR0_OFFSET)
#define HML3_WDCR1_OFFSET          (HML3_CFG_OFFSET + HML3_CFG_WDCR1_OFFSET)
#define HML3_WMCR0_OFFSET          (HML3_CFG_OFFSET + HML3_CFG_WMCR0_OFFSET)
#define HML3_WMCR1_OFFSET          (HML3_CFG_OFFSET + HML3_CFG_WMCR1_OFFSET)

    // Example: how to determine the address of a Register above
    //  e.g. L3_0 HML3_CSR_ALOCR addr: L3_0_QLL_BASE + HML3_ALOCR_OFFSET) --> FF_8058_4004
    //                                 (0xFF_8058_0000)    (0x0000_4004)


// QLL: L3 PerfMon Register Offsets - Alphabetical order
#define HML3_PM_CNTCTL0_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTCTL0_OFFSET)
#define HML3_PM_CNTCTL1_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTCTL1_OFFSET)
#define HML3_PM_CNTCTL2_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTCTL2_OFFSET)
#define HML3_PM_CNTCTL3_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTCTL3_OFFSET)
#define HML3_PM_CNTCTL4_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTCTL4_OFFSET)
#define HML3_PM_CNTCTL5_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTCTL5_OFFSET)
#define HML3_PM_CNTCTL6_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTCTL6_OFFSET)
#define HML3_PM_CNTCTL7_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTCTL7_OFFSET)
#define HML3_PM_CNTRLDA_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTRLDA_OFFSET)
#define HML3_PM_CNTRLDB_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_CNTRLDB_OFFSET)
#define HML3_PM_CR_OFFSET          (HML3_PM_OFFSET + HML3_PM_QLL_CR_OFFSET)


#define HML3_PM_EVTYPER0_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_EVTYPER0_OFFSET)
#define HML3_PM_EVTYPER1_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_EVTYPER1_OFFSET)
#define HML3_PM_EVTYPER2_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_EVTYPER2_OFFSET)
#define HML3_PM_EVTYPER3_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_EVTYPER3_OFFSET)
#define HML3_PM_EVTYPER4_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_EVTYPER4_OFFSET)
#define HML3_PM_EVTYPER5_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_EVTYPER5_OFFSET)
#define HML3_PM_EVTYPER6_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_EVTYPER6_OFFSET)
#define HML3_PM_EVTYPER7_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_EVTYPER7_OFFSET)
#define HML3_PM_FILTRA_OFFSET      (HML3_PM_OFFSET + HML3_PM_QLL_FILTRA_OFFSET)
#define HML3_PM_FILTRAM_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_FILTRAM_OFFSET)
#define HML3_PM_FILTRB_OFFSET      (HML3_PM_OFFSET + HML3_PM_QLL_FILTRB_OFFSET)
#define HML3_PM_FILTRBM_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_FILTRBM_OFFSET)
#define HML3_PM_FILTRC_OFFSET      (HML3_PM_OFFSET + HML3_PM_QLL_FILTRC_OFFSET)
#define HML3_PM_FILTRCM_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_FILTRCM_OFFSET)
#define HML3_PM_OVSS_OFFSET        (HML3_PM_OFFSET + HML3_PM_QLL_OVSS_OFFSET)
#define HML3_PM_XCNTCTL_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_XCNTCTL_OFFSET)
#define HML3_PM_XEVTYPER_OFFSET    (HML3_PM_OFFSET + HML3_PM_QLL_XEVTYPER_OFFSET)
// PerfMon Basic Counters (BC) is the only type of PerfMon counter implemented for L3. No Tenure Counter at this time.
#define M_BC_CNTENCLR_OFFSET       (HML3_PM_OFFSET + M_BC_QLL_CNTENCLR_OFFSET)
#define M_BC_CNTENSET_OFFSET       (HML3_PM_OFFSET + M_BC_QLL_CNTENSET_OFFSET)
#define M_BC_CNTR_LO_OFFSET        (HML3_PM_OFFSET + M_BC_QLL_CNTR_LO_OFFSET)
#define M_BC_CR_OFFSET             (HML3_PM_OFFSET + M_BC_QLL_CR_OFFSET)
#define M_BC_GANG_OFFSET           (HML3_PM_OFFSET + M_BC_QLL_GANG_OFFSET)
#define M_BC_INTENCLR_OFFSET       (HML3_PM_OFFSET + M_BC_QLL_INTENCLR_OFFSET)
#define M_BC_INTENSET_OFFSET       (HML3_PM_OFFSET + M_BC_QLL_INTENSET_OFFSET)
#define M_BC_OVERFLOW0_OFFSET      (HML3_PM_OFFSET + M_BC_QLL_OVERFLOW0_OFFSET)
#define M_BC_OVERFLOW1_OFFSET      (HML3_PM_OFFSET + M_BC_QLL_OVERFLOW1_OFFSET)
#define M_BC_OVSR_OFFSET           (HML3_PM_OFFSET + M_BC_QLL_OVSR_OFFSET)
#define M_BC_SATROLL_CR_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SATROLL_CR_OFFSET)
#define M_BC_SELR_OFFSET           (HML3_PM_OFFSET + M_BC_QLL_SELR_OFFSET)
#define M_BC_SHADOW0_LO_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SHADOW0_LO_OFFSET)
#define M_BC_SHADOW1_LO_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SHADOW1_LO_OFFSET)
#define M_BC_SHADOW2_LO_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SHADOW2_LO_OFFSET)
#define M_BC_SHADOW3_LO_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SHADOW3_LO_OFFSET)
#define M_BC_SHADOW4_LO_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SHADOW4_LO_OFFSET)
#define M_BC_SHADOW5_LO_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SHADOW5_LO_OFFSET)
#define M_BC_SHADOW6_LO_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SHADOW6_LO_OFFSET)
#define M_BC_SHADOW7_LO_OFFSET     (HML3_PM_OFFSET + M_BC_QLL_SHADOW7_LO_OFFSET)
#define M_BC_SWINC_OFFSET          (HML3_PM_OFFSET + M_BC_QLL_SWINC_OFFSET)
#define M_BC_IRQCTL_OFFSET         (HML3_PM_OFFSET + M_BC_QLL_IRQCTL_OFFSET)  // BCSubunit Counter Interrupt Mode Control

    // Example: how to determine the address of a PerfMon(PM) or BasicCounter (BC) register (above) in QLL space
    //  e.g. L3_0 HML3_PM_CNTCTL0 addr: L3_0_QLL_BASE + HML3_PM_CNTCTL0_OFFSET) --> FF_805A_8120
    //                                  (0xFF_8058_0000)    (0x0002_8120)

// END of the QLL Space Defines


/******************************************************************************
* Defined Constants in the APB Space
******************************************************************************/
// APB: L3_x Ring Switch (MBSUx) Offsets (on top of QDSS base and Ring Offset) --> moved to monaco_defs
// APB: L3 QDSS Region(CTIO, PMU, DBG) Offsets on top of (QDSS base + Ring base + MBSU 0ffsets above) --> monaco_defs
// APB: L3 QDSS Sub-region Offsets --> monaco_defs


// APB: L3 QDSS PM Reg Offsets
#define HML3_PM_CNTCTL0_APB_OFFSET    0x0A0  // Performance Monitor Counter Control Register 0
#define HML3_PM_CNTCTL1_APB_OFFSET    0x0A8  // Performance Monitor Counter Control Register 1
#define HML3_PM_CNTCTL2_APB_OFFSET    0x0B0  // Performance Monitor Counter Control Register 2
#define HML3_PM_CNTCTL3_APB_OFFSET    0x0B8  // Performance Monitor Counter Control Register 3
#define HML3_PM_CNTCTL4_APB_OFFSET    0x0C0  // Performance Monitor Counter Control Register 4
#define HML3_PM_CNTCTL5_APB_OFFSET    0x0C8  // Performance Monitor Counter Control Register 5
#define HML3_PM_CNTCTL6_APB_OFFSET    0x0D0  // Performance Monitor Counter Control Register 6
#define HML3_PM_CNTCTL7_APB_OFFSET    0x0D8  // Performance Monitor Counter Control Register 7
#define HML3_PM_CNTRLDA_APB_OFFSET    0x1A0  // Performance Monitor Counter Reload - reg A
#define HML3_PM_CNTRLDB_APB_OFFSET    0x1A8  // Performance Monitor Counter Reload - reg B
#define HML3_PM_CR_APB_OFFSET         0x000  // Performance Monitors Control

// APB: HML3_PM_EVCNTRx_APB_OFFSET --> monaco_defs


#define HML3_PM_EVTYPER0_APB_OFFSET   0x120  // Performance Monitor Event Type Register 0
#define HML3_PM_EVTYPER1_APB_OFFSET   0x128  // Performance Monitor Event Type Register 1
#define HML3_PM_EVTYPER2_APB_OFFSET   0x130  // Performance Monitor Event Type Register 2
#define HML3_PM_EVTYPER3_APB_OFFSET   0x138  // Performance Monitor Event Type Register 3
#define HML3_PM_EVTYPER4_APB_OFFSET   0x140  // Performance Monitor Event Type Register 4
#define HML3_PM_EVTYPER5_APB_OFFSET   0x148  // Performance Monitor Event Type Register 5
#define HML3_PM_EVTYPER6_APB_OFFSET   0x150  // Performance Monitor Event Type Register 6
#define HML3_PM_EVTYPER7_APB_OFFSET   0x158  // Performance Monitor Event Type Register 7
#define HML3_PM_FILTRA_APB_OFFSET     0x180  // Performance Monitor Event Filter A
#define HML3_PM_FILTRAM_APB_OFFSET    0x184  // Performance Monitor Event Filter A Mask
#define HML3_PM_FILTRB_APB_OFFSET     0x188  // Performance Monitor Event Filter B
#define HML3_PM_FILTRBM_APB_OFFSET    0x18C  // Performance Monitor Event Filter B Mask
#define HML3_PM_FILTRC_APB_OFFSET     0x190  // Performance Monitor Event Filter C
#define HML3_PM_FILTRCM_APB_OFFSET    0x194  // Performance Monitor Event Filter C Mask
#define HML3_PM_OVSS_APB_OFFSET       0x008  // Performance Monitor Overflow Status Set
#define HML3_PM_XCNTCTL_APB_OFFSET    0x010  // Performance Monitor Selected Counter Control Reg
#define HML3_PM_XEVTYPER_APB_OFFSET   0x018  // Performance Monitor Selected Event Type Register
#define M_BC_CNTENCLR_APB_OFFSET      0x28C  // BCSubunit Counter Enable Clear Register
#define M_BC_CNTENSET_APB_OFFSET      0x288  // BCSubunit Counter Enable Set Register
#define M_BC_CNTR_LO_APB_OFFSET       0x3C8  // BCSubunit Count LO Register
#define M_BC_CR_APB_OFFSET            0x280  // BCSubunit Global Control Register
#define M_BC_GANG_APB_OFFSET          0x398  // BCSubunit Ganging Control Register
#define M_BC_INTENCLR_APB_OFFSET      0x294  // BCSubunit Counter Interrupt Enable Clear Reg
#define M_BC_INTENSET_APB_OFFSET      0x290  // BCSubunit Counter Interrupt Enable Set Register
#define M_BC_OVERFLOW0_APB_OFFSET     0x39C  // BCSubunit Counter Overflow Configuration Reg 0
#define M_BC_OVERFLOW1_APB_OFFSET     0x3A0  // BCSubunit Counter Overflow Configuration Reg 1
#define M_BC_OVSR_APB_OFFSET          0x3C0  // BCSubunit Counter Rollover & Saturation Status Reg
#define M_BC_SATROLL_CR_APB_OFFSET    0x284  // BCSubunit Saturation & Rollover Control Register
#define M_BC_SELR_APB_OFFSET          0x3C4  // BCSubunit Counter Selection Register
#define M_BC_SHADOW0_LO_APB_OFFSET    0x3D0  // BCSubunit APB Retrieval Shadow LO Register 0
#define M_BC_SHADOW1_LO_APB_OFFSET    0x3D4  // BCSubunit APB Retrieval Shadow LO Register 1
#define M_BC_SHADOW2_LO_APB_OFFSET    0x3D8  // BCSubunit APB Retrieval Shadow LO Register 2
#define M_BC_SHADOW3_LO_APB_OFFSET    0x3DC  // BCSubunit APB Retrieval Shadow LO Register 3
#define M_BC_SHADOW4_LO_APB_OFFSET    0x3E0  // BCSubunit APB Retrieval Shadow LO Register 4
#define M_BC_SHADOW5_LO_APB_OFFSET    0x3E4  // BCSubunit APB Retrieval Shadow LO Register 5
#define M_BC_SHADOW6_LO_APB_OFFSET    0x3E8  // BCSubunit APB Retrieval Shadow LO Register 6
#define M_BC_SHADOW7_LO_APB_OFFSET    0x3EC  // BCSubunit APB Retrieval Shadow LO Register 7
#define M_BC_SWINC_APB_OFFSET         0x4D0  // Performance Monitor Software Increment Reg
#define M_BC_IRQCTL_APB_OFFSET        0x4EC  // BCSubunit Counter Interrupt Mode Control

// APB: L3 QDSS PMU TPDM CoreSight Register Offsets
#define M_AUTHSTATUS_APB_OFFSET       0x1B8  // Coresight 2.0 Authentication Status Register
#define M_CIDR0_APB_OFFSET            0x1F0  // Coresight 2.0 Component ID Register 0
#define M_CIDR1_APB_OFFSET            0x1F4  // Coresight 2.0 Component ID Register 1
#define M_CIDR2_APB_OFFSET            0x1F8  // Coresight 2.0 Component ID Register 2
#define M_CIDR3_APB_OFFSET            0x1FC  // Coresight 2.0 Component ID Register 3
#define M_CLAIMCLR_APB_OFFSET         0x1A4  // Coresight 2.0 Claim Tag Clear Register
#define M_CLAIMSET_APB_OFFSET         0x1A0  // Coresight 2.0 Claim Tag Set Register
#define M_DEVAFF0_APB_OFFSET          0x1A8  // Coresight 2.0 Device Affinity 0 Register
#define M_DEVAFF1_APB_OFFSET          0x1AC  // Coresight 2.0 Device Affinity 1 Register
#define M_DEVARCH_APB_OFFSET          0x1BC  // Coresight 2.0 Device Architecture Register
#define M_DEVID_APB_OFFSET            0x1C8  // Coresight 2.0 Device Configuration Register
#define M_DEVID1_APB_OFFSET           0x1C4  // Coresight 2.0 Device Configuration Register 1
#define M_DEVID2_APB_OFFSET           0x1C0  // Coresight 2.0 Device Configuration Register 2
#define M_DEVTYPE_APB_OFFSET          0x1CC  // Coresight 2.0 Device Type Register
#define M_LAR_APB_OFFSET              0x1B0  // Coresight 2.0 Lock Access Register
#define M_LSR_APB_OFFSET              0x1B4  // Coresight 2.0 Lock Status Register
#define M_PIDR0_APB_OFFSET            0x1E0  // Coresight 2.0 Peripheral ID Register 0
#define M_PIDR1_APB_OFFSET            0x1E4  // Coresight 2.0 Peripheral ID Register 1
#define M_PIDR2_APB_OFFSET            0x1E8  // Coresight 2.0 Peripheral ID Register 2
#define M_PIDR3_APB_OFFSET            0x1EC  // Coresight 2.0 Peripheral ID Register 3
#define M_PIDR4_APB_OFFSET            0x1D0  // Coresight 2.0 Peripheral ID Register 4
#define M_PIDR5_APB_OFFSET            0x1D4  // Coresight 2.0 Peripheral ID Register 5
#define M_PIDR6_APB_OFFSET            0x1D8  // Coresight 2.0 Peripheral ID Register 6
#define M_PIDR7_APB_OFFSET            0x1DC  // Coresight 2.0 Peripheral ID Register 7


// APB: L3 DBG APB Clock Domain Register Offset - in APB
#define HML3_APB_IDADAT_OFFSET       0x000C  // L3 APB Indirect Access Data: read/write data of the target reg entered to IDAIDX reg below
#define HML3_APB_IDAIDX_OFFSET       0x0008  // L3 APB Indirect Access Index: program address offset of the target reg in this reg
#define HML3_APB_L3STATE_OFFSET      0x0004  // L3 APB L3 State:  L3 is awake or sleeping



// APB: L3_x QDSS Base Addresses ---> moved to monaco_defs.h

// APB: L3 QDSS Register Offsets

// APB: Performance Management Unit(PMU): L3 PerfMon and TPDM CoreSight
//    APB: L3 PMU PerfMon Register Offsets
#define HML3_PM_APB_CNTCTL0_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTCTL0_APB_OFFSET)
#define HML3_PM_APB_CNTCTL1_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTCTL1_APB_OFFSET)
#define HML3_PM_APB_CNTCTL2_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTCTL2_APB_OFFSET)
#define HML3_PM_APB_CNTCTL3_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTCTL3_APB_OFFSET)
#define HML3_PM_APB_CNTCTL4_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTCTL4_APB_OFFSET)
#define HML3_PM_APB_CNTCTL5_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTCTL5_APB_OFFSET)
#define HML3_PM_APB_CNTCTL6_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTCTL6_APB_OFFSET)
#define HML3_PM_APB_CNTCTL7_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTCTL7_APB_OFFSET)
#define HML3_PM_APB_CNTRLDA_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTRLDA_APB_OFFSET)
#define HML3_PM_APB_CNTRLDB_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CNTRLDB_APB_OFFSET)
#define HML3_PM_APB_CR_OFFSET         (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_CR_APB_OFFSET)


#define HML3_PM_APB_EVTYPER0_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVTYPER0_APB_OFFSET)
#define HML3_PM_APB_EVTYPER1_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVTYPER1_APB_OFFSET)
#define HML3_PM_APB_EVTYPER2_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVTYPER2_APB_OFFSET)
#define HML3_PM_APB_EVTYPER3_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVTYPER3_APB_OFFSET)
#define HML3_PM_APB_EVTYPER4_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVTYPER4_APB_OFFSET)
#define HML3_PM_APB_EVTYPER5_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVTYPER5_APB_OFFSET)
#define HML3_PM_APB_EVTYPER6_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVTYPER6_APB_OFFSET)
#define HML3_PM_APB_EVTYPER7_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVTYPER7_APB_OFFSET)
#define HML3_PM_APB_FILTRA_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_FILTRA_APB_OFFSET)
#define HML3_PM_APB_FILTRAM_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_FILTRAM_APB_OFFSET)
#define HML3_PM_APB_FILTRB_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_FILTRB_APB_OFFSET)
#define HML3_PM_APB_FILTRBM_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_FILTRBM_APB_OFFSET)
#define HML3_PM_APB_FILTRC_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_FILTRC_APB_OFFSET)
#define HML3_PM_APB_FILTRCM_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_FILTRCM_APB_OFFSET)
#define HML3_PM_APB_OVSS_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_OVSS_APB_OFFSET)
#define HML3_PM_APB_XCNTCTL_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_XCNTCTL_APB_OFFSET)
#define HML3_PM_APB_XEVTYPER_OFFSET   (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_XEVTYPER_APB_OFFSET)
#define M_BC_APB_CNTENCLR_OFFSET      (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_CNTENCLR_APB_OFFSET)
#define M_BC_APB_CNTENSET_OFFSET      (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_CNTENSET_APB_OFFSET)
#define M_BC_APB_CNTR_LO_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_CNTR_LO_APB_OFFSET)
#define M_BC_APB_CR_OFFSET            (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_CR_APB_OFFSET)
#define M_BC_APB_GANG_OFFSET          (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_GANG_APB_OFFSET)
#define M_BC_APB_INTENCLR_OFFSET      (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_INTENCLR_APB_OFFSET)
#define M_BC_APB_INTENSET_OFFSET      (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_INTENSET_APB_OFFSET)
#define M_BC_APB_OVERFLOW0_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_OVERFLOW0_APB_OFFSET)
#define M_BC_APB_OVERFLOW1_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_OVERFLOW1_APB_OFFSET)
#define M_BC_APB_OVSR_OFFSET          (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_OVSR_APB_OFFSET)
#define M_BC_APB_SATROLL_CR_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SATROLL_CR_APB_OFFSET)
#define M_BC_APB_SELR_OFFSET          (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SELR_APB_OFFSET)
#define M_BC_APB_SHADOW0_LO_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SHADOW0_LO_APB_OFFSET)
#define M_BC_APB_SHADOW1_LO_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SHADOW1_LO_APB_OFFSET)
#define M_BC_APB_SHADOW2_LO_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SHADOW2_LO_APB_OFFSET)
#define M_BC_APB_SHADOW3_LO_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SHADOW3_LO_APB_OFFSET)
#define M_BC_APB_SHADOW4_LO_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SHADOW4_LO_APB_OFFSET)
#define M_BC_APB_SHADOW5_LO_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SHADOW5_LO_APB_OFFSET)
#define M_BC_APB_SHADOW6_LO_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SHADOW6_LO_APB_OFFSET)
#define M_BC_APB_SHADOW7_LO_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SHADOW7_LO_APB_OFFSET)
#define M_BC_APB_SWINC_OFFSET         (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_SWINC_APB_OFFSET)
#define M_BC_APB_IRQCTL_OFFSET        (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + M_BC_IRQCTL_APB_OFFSET)

    // Example: how to determine the address of a register above
    // e.g. L3_0 HML3_PM_CNTCTL0_APB addr: L3_0_APB_BASE + HML3_PM_APB_CNTCTL0_OFFSET--> FF_1213_C0A0
    //                                    (0xFF_1210_0000)    (0x0003_C0A0)

//   APB: L3 PMU TPDM CoreSight Register Offsets
#define M_APB_AUTHSTATUS_OFFSET  (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_AUTHSTATUS_APB_OFFSET) // 0x00030000+0xCE00+0x1B8
#define M_APB_CIDR0_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_CIDR0_APB_OFFSET)
#define M_APB_CIDR1_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_CIDR1_APB_OFFSET)
#define M_APB_CIDR2_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_CIDR2_APB_OFFSET)
#define M_APB_CIDR3_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_CIDR3_APB_OFFSET)
#define M_APB_CLAIMCLR_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_CLAIMCLR_APB_OFFSET)
#define M_APB_CLAIMSET_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_CLAIMSET_APB_OFFSET)
#define M_APB_DEVAFF0_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_DEVAFF0_APB_OFFSET)
#define M_APB_DEVAFF1_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_DEVAFF1_APB_OFFSET)
#define M_APB_DEVARCH_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_DEVARCH_APB_OFFSET)
#define M_APB_DEVID_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_DEVID_APB_OFFSET)
#define M_APB_DEVID1_OFFSET      (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_DEVID1_APB_OFFSET)
#define M_APB_DEVID2_OFFSET      (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_DEVID2_APB_OFFSET)
#define M_APB_DEVTYPE_OFFSET     (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_DEVTYPE_APB_OFFSET)
#define M_APB_LAR_OFFSET         (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_LAR_APB_OFFSET)
#define M_APB_LSR_OFFSET         (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_LSR_APB_OFFSET)
#define M_APB_PIDR0_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_PIDR0_APB_OFFSET)
#define M_APB_PIDR1_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_PIDR1_APB_OFFSET)
#define M_APB_PIDR2_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_PIDR2_APB_OFFSET)
#define M_APB_PIDR3_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_PIDR3_APB_OFFSET)
#define M_APB_PIDR4_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_PIDR4_APB_OFFSET)
#define M_APB_PIDR5_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_PIDR5_APB_OFFSET)
#define M_APB_PIDR6_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_PIDR6_APB_OFFSET)
#define M_APB_PIDR7_OFFSET       (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_TPDMCS_OFFSET + M_PIDR7_APB_OFFSET)

    // Example: how to determine the address of a TPDM register above
    //  e.g. L3_0 M_AUTHSTATUS_APB addr: L3_0_APB_BASE + M_APB_AUTHSTATUS_OFFSET --> FF_1213_CFB8
    //                                (0xFF_1210_0000) + (0x0003_CFB8)

// APB: L3 DBG APB Clock Domain Register Offsets
//   These regs are used to determine whether L3 is in sleep(and therefore access
//     to its registers is not possible)   AND
//     to indirectly access L3 CSR, PerfMon, LLM regs
#define HML3_APB_DBG_IDADAT_OFFSET    (HML3_APB_DBG_TOP_OFFSET + HML3_APB_DBG_OFFSET + HML3_APB_IDADAT_OFFSET) // 0x00020000+0xC000+0x000C
#define HML3_APB_DBG_IDAIDX_OFFSET    (HML3_APB_DBG_TOP_OFFSET + HML3_APB_DBG_OFFSET + HML3_APB_IDAIDX_OFFSET)
#define HML3_APB_DBG_L3STATE_OFFSET   (HML3_APB_DBG_TOP_OFFSET + HML3_APB_DBG_OFFSET + HML3_APB_L3STATE_OFFSET)

    // Example: how to determine the address of a register above
    // e.g. L3_0 HML3_APB_DBG_IDADAT addr: L3_0_APB_BASE + HML3_APB_DBG_IDADAT_OFFSET--> 0xFF_1212_C00C
    //                                    (0xFF_1210_0000)  (0x0002_C00C)

// END of APB Space Defines



// Arrays holding the HML3_TCMAACBi values based on the partial goods to help
//  the snoop pre-filter with the L3 address allocation
uint32_t twelve_good_inst[12] = { 0x07025C9D, 0x07065DFF, 0x07225CDF, 0x07425CFF,
                                  0x07465D9D, 0x07825E9D, 0x07625DDF, 0x07865EFF,
                                  0x07A25EDF, 0x07C25FFF, 0x07C65F9D, 0x07E25FDF
                                };

uint32_t eleven_good_inst[11] = { 0x06C04000, 0x06C44000, 0x07004000, 0x07044000,
                                  0x07404000, 0x07804000, 0x07444000, 0x07865E9D,
                                  0x07C25F9D, 0x07C65EDD, 0x07E25FDD
                                };

uint32_t ten_good_inst[10]  =   { 0x06805F1D, 0x06845F0D, 0x06C05F5D, 0x07005F9D,
                                  0x06C45F4D, 0x07045F8D, 0x07405FDD, 0x07444000,
                                  0x07804000, 0x07845FCD
                                };

uint32_t nine_good_inst[9]  =   { 0x06405E13, 0x06805E33, 0x06445E03, 0x06845F23,
                                  0x06C05F13, 0x06C45F03, 0x07005F33, 0x07045E23,
                                  0x07400000
                                };

uint32_t seven_good_inst[7]  =  { 0x05C25F9D, 0x07C25FDD, 0x05C64000, 0x07C64000,
                                  0x05E24000, 0x07E24000, 0x05E64000
                                };

uint32_t six_good_inst[6]   =   { 0x0580579D, 0x07805F9D, 0x0584578D, 0x07845F8D,
                                  0x05C217CC, 0x07C21FCC
                                };

uint32_t five_good_inst[5]  =   { 0x05401F0C, 0x07400000, 0x05801F4C, 0x07800000,
                                  0x05C01F88
                                };

uint32_t three_good_inst[3] =   { 0x04C21700, 0x04E21F08, 0x06C01F88
                                };




/*!****************************************************************************
*
* @defgroup l3_init_regs L3 POR (Power-on Reset/Initialization) Register defs
*
*
* @par Description
*    Definitions of the register fields with masks and shifts to aid in
*    the implementation of the POR sequence
*
* @{
******************************************************************************/

// Setup POS
// For chip builds R40 and later
#define POSCRA_ENABLE_SFT_VAL            0x109F0000  //!< For SFT enabled
#define POSCRA_DISABLE_SFT_VAL           0x1D9F0000  //!< For SFT disabled


// Setup Snoop Filter (SFT)
#define SFTCR_DISABLE_SFT_VAL            0x00000001    //!< Disable the snoop filter.
#define SFTCR_ENABLE_SFT_VAL             0x00031802    //!< Enable the snoop filter. SFT_MODE = FG


// POS Control: LL/BAR/TLBI/QoS Beacon enable fields of the HML3_POSCRC reg.
// For the even interleave
#define POSCRC_TLBI_OP_IV0_EN__M         0x00000001
#define POSCRC_BAR_OP_IV0_EN__M          0x00000002
#define POSCRC_LLBC_IV0_EN__M            0x00000004
#define POSCRC_QB_IV0_EN__M              0x00000008
#define POSCRC_TLBI_OP_IV0_EN__S         0
#define POSCRC_BAR_OP_IV0_EN__S          1
#define POSCRC_LLBC_IV0_EN__S            2
#define POSCRC_QB_IV0_EN__S              3
#define POSCRC_TLBI_OP_IV0_EN            0x00000001
#define POSCRC_BAR_OP_IV0_EN             0x00000001
#define POSCRC_LLBC_IV0_EN               0x00000001
#define POSCRC_QB_IV0_EN                 0x00000001
// For the odd interleave
#define POSCRC_TLBI_OP_IV1_EN__M         0x00000010
#define POSCRC_BAR_OP_IV1_EN__M          0x00000020
#define POSCRC_LLBC_IV1_EN__M            0x00000040
#define POSCRC_QB_IV1_EN__M              0x00000080
#define POSCRC_TLBI_OP_IV1_EN__S         4
#define POSCRC_BAR_OP_IV1_EN__S          5
#define POSCRC_LLBC_IV1_EN__S            6
#define POSCRC_QB_IV1_EN__S              7
#define POSCRC_TLBI_OP_IV1_EN            0x00000001
#define POSCRC_BAR_OP_IV1_EN             0x00000001
#define POSCRC_LLBC_IV1_EN               0x00000001
#define POSCRC_QB_IV1_EN                 0x00000001

// The TLBI/BAR POS control fields are 1 bit each and adjacent so we'll handle
//   them together as a 2-bit field for either interleave.
#define POSCRC_TLBI_BAR_IV0_EN__M    (POSCRC_TLBI_OP_IV0_EN__M | POSCRC_BAR_OP_IV0_EN__M)


#define POSCRC_TLBI_BAR_IV0_EN__S    POSCRC_TLBI_OP_IV0_EN__S

#define POSCRC_TLBI_BAR_IV0_EN       ((POSCRC_TLBI_OP_IV0_EN << POSCRC_TLBI_OP_IV0_EN__S) |  \
                                           (POSCRC_BAR_OP_IV0_EN << POSCRC_BAR_OP_IV0_EN__S))

#define POSCRC_TLBI_BAR_IV1_EN__M    (POSCRC_TLBI_OP_IV1_EN__M | POSCRC_BAR_OP_IV1_EN__M)

#define POSCRC_TLBI_BAR_IV1_EN__S    POSCRC_TLBI_OP_IV1_EN__S

#define POSCRC_TLBI_BAR_IV1_EN       POSCRC_TLBI_BAR_IV0_EN

// The LL/QB POS control fields are 1 bit each and adjacent so we'll handle
//   them together as a 2-bit field for either interleave.
#define POSCRC_LLBC_QB_IV0_EN__M    (POSCRC_LLBC_IV0_EN__M | POSCRC_QB_IV0_EN__M)

#define POSCRC_LLBC_QB_IV0_EN__S    POSCRC_LLBC_IV0_EN__S

#define POSCRC_LLBC_QB_IV0_EN       ((POSCRC_LLBC_IV0_EN << 0) |  \
                                           (POSCRC_QB_IV0_EN << 1))

#define POSCRC_LLBC_QB_IV1_EN__M    (POSCRC_LLBC_IV1_EN__M | POSCRC_QB_IV1_EN__M)

#define POSCRC_LLBC_QB_IV1_EN__S    POSCRC_LLBC_IV1_EN__S

#define POSCRC_LLBC_QB_IV1_EN       POSCRC_LLBC_QB_IV0_EN

// fatcm faiccra field
#define FAICCRAn_ALLOC_ADDR_HI__M     0x0FFFFFFF
#define FAICCRAn_ALLOC_ADDR_HI__S     0x0

// Invalidate L3 & SFT via FAIC invalidate function using HML3_FAICCRBi reg
// Values to be written to the FAIC_FUNCTION field of HML3_FAICCRBn regs to select
//   the FAIC machine function.
#define FAICCRBn_FAIC_FUNCTION__M      0x0000000F   //!< FAIC machine function, Bits[3:0]
#define FAICCRBn_FAIC_FUNCTION__S      0
#define FAICCRBn_FAIC_FUNCTION_ALLOCATE   0x00000002   //!< ALLOC function
#define FAICCRBn_FAIC_FUNCTION_INV_L3  0x00000006   //!< L3 Tag Invalidate function
#define FAICCRBn_FAIC_FUNCTION_INV_SFT 0x00000007   //!< SFT Invalidate function
#define FAICCRBn_FAIC_ALLOC_ADDR__M       0x00000FFF
#define FAICCRBn_FAIC_ALLOC_ADDR__S       0xF
#define FAICCRBn_FAIC_ALLOC_BLK_CNT__M    0x00FC0000
#define FAICCRBn_FAIC_ALLOC_BLK_CNT__S    0x12
#define FAICCRBn_FAIC_ALLOC_BLK_SIZE__M   0x01000000
#define FAICCRBn_FAIC_ALLOC_BLK_SIZE__S   0x18
#define FAICCRBn_FAIC_ALLOC_NOBACK__M     0x02000000
#define FAICCRBn_FAIC_ALLOC_NOBACK__S     0x19
#define FAICCRBn_FAIC_ALLOC_LLK__M        0x04000000
#define FAICCRBn_FAIC_ALLOC_LLK__S        0x1a
#define FAICCRBn_FAIC_ALLOC_NSPROT__M     0x08000000
#define FAICCRBn_FAIC_ALLOC_NSPROT__S     0x1b

// Wait for the FAIC machine to become idle. Use HML3_FAICSRi reg.
#define FAICSRn_FAIC_MACH_STAT__M      0x00000001
#define FAICSRn_FAIC_MACH_STAT__S      0
#define FAICSRn_FAIC_MACH_STAT_IDLE    0x00000000
#define FAICSRn_FAIC_MACH_STAT_BUSY    0x00000001
#define FAICSRn_FAIC_ALLOCF_FAIL__M    0x00000002
#define FAICSRn_FAIC_ALLOCF_FAIL__S    0x1

// Set Data Array Controls: HML3_ARYCC, L3 Array Control Register C.
#define ARYCC_DARY_ACC_LAT__M    0x00000007    //!< Data Array Access Latency, Bits[2:0]
#define ARYCC_DARY_ACC_LAT__S    0
#define ARYCC_DARY_ACC_LAT       0x00000004    //!< CYCLES_4

// Set Misc L3 Config Bits: HML3_HCRA and HML3_CRA regs.
#define HCRA_FLFSRON__M          0x00010000    //!< (Mask) LFSRON, bit[16]
#define HCRA_FLFSRON__S          16            //!< (Shift)
#define HCRA_FLFSRON_VAL         0x00000001    //!< (Val) if 1 LFSR runs when CBF CLK runs, if 0 LFSR runs only when L3 not idle
#define HCRA_HASH_ENABLED_VAL    0x02608020    //!< Hash on, unchained data allowed, enable improved Tag UE recovery/RAS
#define HCRA_HASH_DISABLED_VAL   0x02608060    //!< Hash off, unchained data allowed, enable improved Tag UE recovery/RAS
#define CRA_VAL                  0x04800008    //!< Default val: Only correct SFT tag ECC errors during tag lookup, don't write corrected data to SFT tag array, Spread Mode
#define CRA_AMVSMC__M            0x00080000    //!< (Mask) Affinity/Spread Mode
#define CRA_AMVSMC__S            19            //!< (Shift) Affinity/Spread Mode

// Set info interrupts - write '1' to bits in HML3_FIRAT0S to set the corresponding
//  bits in HML3_FIRAT0 to be reported as informational (non-fatal) interrupts.
// Add QoSID CE, HML3_FIRA bit[25], to the list of info interrupts.
#define FIRAT0S_VAL              0x028F30AA       //!< Value to write to the register

// Set fatal interrupts - write '1' to bits in HML3_FIRAT1S to set the corresponding
//  bits in HML3_FIRAT1 to be reported as fatal interrupts.
#define FIRAT1S_VAL              0x0160C854    //!< Value to be written to the register

// Disable DCIALL of common reg HML3_CRD
#define CRD_DDCIALL__M           0x00000001    //!< Disable DCIALL. Controls whether DCIALL will be executed or ignored
#define CRD_DDCIALL__S           0x0
#define CRD_DDCIALL_NOP          0x00000001    //!< Ignore DCIALL. Set-only bit i.e. can only be cleared by a reset

// Override Allocation Control
#define ALOCR_REPL_POLICY__M         0x00003000 //!< Replacement Policy, Bits[13:12]
#define ALOCR_REPL_POLICY__S         12         //!<
#define ALOCR_REPL_POLICY_LRU        0x0        //!< LRU (pseudo-LRU): victim is the least recently accessed line from the available lines
#define ALOCR_REPL_POLICY_RANDOM     0x2        //!< RANDOM: victim is randomly chosen from among the available ways

#define ALOCR_PLDL3_HANDLING         0x0        //!< PLDL3 miss. Value of set field: Normal. Read from memory, use alloc attrib as-is
#define ALOCR_PSTL3_HANDLING         0x0        //!< PSTL3 miss. Value of set field: Normal. Read from memory, use alloc attrib as-is

#define ALOCR_WRP_ALLOC_OVR__M       0x00000080 //!< Override alloc attrib that arrived with a partial line write request
#define ALOCR_WRP_ALLOC_OVR__S       7          //!<
#define ALOCR_WRP_ALLOC_OVR_NO_OVR   0x0        //!< Use outer allocation attribute as-is
#define ALOCR_WRP_ALLOC_OVR_OVR      0x1        //!< Do not use outer alloc attrib from req, use WRP_ALLOC_CTL instead

#define ALOCR_WRP_ALLOC_CTL__M       0x00000040 //!< When overriding alloc attrib for a partial line write controls whether to alloc for a write miss
#define ALOCR_WRP_ALLOC_CTL__S       6          //!<
#define ALOCR_WRP_ALLOC_CTL_ALLOC    0x0        //!< Allocate
#define ALOCR_WRP_ALLOC_CTL_NO_ALLOC 0x1        //!< No allocation

#define ALOCR_WRL_ALLOC_OVR__M       0x00000020 //!< Override alloc attrib that arrived with a line write req
#define ALOCR_WRL_ALLOC_OVR__S       5          //!<
#define ALOCR_WRL_ALLOC_OVR_NO_OVR   0x0        //!< Use outer allocation attribute as-is
#define ALOCR_WRL_ALLOC_OVR_OVR      0x1        //!< Do not use outer alloc attrib from req, use WRL_ALLOC_CTL instead

#define ALOCR_WRL_ALLOC_CTL__M       0x00000010 //!< When overriding alloc attrib for a line write controls whether to alloc for a write miss
#define ALOCR_WRL_ALLOC_CTL__S       4          //!<
#define ALOCR_WRL_ALLOC_CTL_ALLOC    0x0        //!< Allocate
#define ALOCR_WRL_ALLOC_CTL_NO_ALLOC 0x1        //!< No allocation

#define ALOCR_WB_ALLOC_OVR__M        0x00000008 //!< Override alloc attrib that arrived with a writeBack or evictWithData
#define ALOCR_WB_ALLOC_OVR__S        3          //!<
#define ALOCR_WB_ALLOC_OVR_NO_OVR    0x0        //!< Use outer allocation attribute as-is
#define ALOCR_WB_ALLOC_OVR_OVR       0x1        //!< Do not use outer alloc attrib from req, use WB_ALLOC_CTL instead

#define ALOCR_WB_ALLOC_CTL__M        0x00000004 //!< When overriding alloc attrib for a writeBack or evictWithData controls whether to alloc for a WB or evictWithData
#define ALOCR_WB_ALLOC_CTL__S        2          //!<
#define ALOCR_WB_ALLOC_CTL_ALLOC     0x0        //!< Allocate
#define ALOCR_WB_ALLOC_CTL_NO_ALLOC  0x1        //!< No allocation

#define ALOCR_RD_ALLOC_OVR__M        0x00000002 //!< Override alloc attrib that arrived with a read req
#define ALOCR_RD_ALLOC_OVR__S        1          //!<
#define ALOCR_RD_ALLOC_OVR_NO_OVR    0x0        //!< Use outer allocation attribute as-is
#define ALOCR_RD_ALLOC_OVR_OVR       0x1        //!< Do not use outer alloc attrib from req, use RD_ALLOC_CTL instead

#define ALOCR_RD_ALLOC_CTL__M        0x00000001 //!< When overriding alloc attrib for a read controls whether to alloc for a read miss
#define ALOCR_RD_ALLOC_CTL__S        0          //!<
#define ALOCR_RD_ALLOC_CTL_ALLOC     0x0        //!< Allocate
#define ALOCR_RD_ALLOC_CTL_NO_ALLOC  0x1        //!< No allocation

// Setup L3 CLK tree gating counter to a desired timeout value
#define PSCRB_L3_SLPREQ_CNT__M     0xFFFF0000   //!< (Mask) Number of clock cycles that the L3 is idle before sleep request to SPM
#define PSCRB_L3_SLPREQ_CNT__S     16           //!< (Shift)
#define PSCRB_L3_SLPREQ_CNT        0x00000FFF   //!< Value of set field

#define PSCRB_CLKOFF_CNT__M        0x0000FFFF   //!< (Mask) Number of CBF cycles that L3 is idle before it turns off its clock/intlv
#define PSCRB_CLKOFF_CNT__S        0            //!< (Shift)
#define PSCRB_CLKOFF_CNT           0x000001FF   //!< Value of set field

// Enable CLK tree gating
#define PSCRA_EL3DCCLKG1__M        0x00000008   //!< (Mask) Enable L3 Dynamic Clock Tree gating, Interleave 1
#define PSCRA_EL3DCCLKG1__S        3            //!< (Shift)
#define PSCRA_EL3DCCLKG1_EN        0x00000001   //!< Value of set field: Enabled
#define PSCRA_EL3DCCLKG1_DIS       0x0          //!< Value of set field: Disabled

#define PSCRA_EL3DCCLKG0__M        0x00000002   //!< (Mask) Enable L3 Dynamic Clock Tree gating, Interleave 0
#define PSCRA_EL3DCCLKG0__S        1            //!< (Shift)
#define PSCRA_EL3DCCLKG0           0x00000001   //!< Value of set field: Enabled

#define PSCRA_NO_POS_GATING_VAL    0x0000000A   //!< Value to be written to the register; LL POS not gating clk
#define PSCRA_POS_GATING_VAL       0x0000000E   //!< Value to be written to the register; LL POS gating clk

// LiveLock Query (LL) setup: HML3_LLBQF, HML3_LLBCR
#define LLBQF_LLQ_ADDR_DLY__M      0x0000FFFF   //!< (Mask) Num of XO cycles (timeout) between address LL queries
#define LLBQF_LLQ_ADDR_DLY__S      0            //!< (Shift)
#define LLBQF_LLQ_DATA_DLY__M      0xFFFF0000   //!< (Mask) Num of XO cycles (timeout) between data LL queries
#define LLBQF_LLQ_DATA_DLY__S      16           //!< (Shift)
#define LLBQF_LLQ_ADDR_DLY_RUMI_VAL     0x1388  //!< (Val) Addr dly for Emulation as recommended by the HW team
#define LLBQF_LLQ_DATA_DLY_RUMI_VAL     0x07D0  //!< (Val) Data dly for Emulation as recommended by the HW team
#define LLBQF_LLQ_ADDR_DLY_SILICON_VAL  0x0140  //!< (Val) Addr dly for SILICON as recommended by the HW team
#define LLBQF_LLQ_DATA_DLY_SILICON_VAL  0x0140  //!< (Val) Data dly for SILICON as recommended by the HW team

//!< Value for data and address timeouts (depending on the execution platform) to be written to the register
#define LLBQF_LLQ_DLY_RUMI_VAL   (LLBQF_LLQ_ADDR_DLY_RUMI_VAL | (LLBQF_LLQ_DATA_DLY_RUMI_VAL << LLBQF_LLQ_DATA_DLY__S))
#define LLBQF_LLQ_DLY_SILICON_VAL   (LLBQF_LLQ_ADDR_DLY_SILICON_VAL | (LLBQF_LLQ_DATA_DLY_SILICON_VAL << LLBQF_LLQ_DATA_DLY__S))

// LiveLock breaker/backoff control: HML3_LLBCR: R/W - L3 LiveLock Query and Breaker Control register.
#define LLBCR_LL_QUERY_A__M        0x00000001   //!< (Mask) Address Phase LiveLock Query
#define LLBCR_LL_QUERY_A__S        0            //!< (Shift)
#define LLBCR_LL_QUERY_A_EN        0x00000001   //!< Enable Address Phase LL Query
#define LLBCR_LL_QUERY_D__M        0x00000002   //!< (Mask) Data Phase LiveLock Query
#define LLBCR_LL_QUERY_D__S        1            //!< (Shift)
#define LLBCR_LL_QUERY_D_EN        0x00000001   //!< Enable Data Phase LL Query
//!< Value controlling the Address/Data query enable
#define LLBCR_QUERY_VAL   (LLBCR_LL_QUERY_A_EN | (LLBCR_LL_QUERY_D_EN << LLBCR_LL_QUERY_D__S))

#define LLBCR_LL_BREAK__M              0x00000004  //!< (Mask) Break/Backoff POS tries to break up a possible livelock/starvation
#define LLBCR_LL_BREAK__S              2           //!< (Shift)
#define LLBCR_LL_BREAK_EN_VAL          0x00000001  //!< (Val) Enable/attempt to break out a suspected LL by sending LL backoff ops on the bus
#define LLBCR_LL_TTAG__M               0x00000018  //!< (Mask) bits[4:3], Trace tag val for LL query/backoff snoops
#define LLBCR_LL_TTAG__S               3           //!< (Shift)
#define LLBCR_LL_TTAG_EN_VAL           0x00000001  //!< (Val) Trace tag val
#define LLBCR_LL_BRKR_LVL_SPACING__M   0xFF000000  //!< (Mask) Control how many LL queries to be sent before incrementing to the next deeper LL breaker mode
#define LLBCR_LL_BRKR_LVL_SPACING__S   24          //!< (Shift)
#define LLBCR_LL_BRKR_LVL_SPACING_VAL  0x40        //!< (Val)

// QoS Beacon Control
#define QBCR_QOSBEACON_DLY__M          0x0000FFFF  //!< (Mask) Num of XO clk cycles between QoS Beacons.
#define QBCR_QOSBEACON_DLY__S          0           //!< (Shift)
#define QBCR_QOSBEACON_DLY_RUMI_VAL      0x1388    //!< (Val) QoS Beacon rate value for Emulation as recommended by the HW team
#define QBCR_QOSBEACON_DLY_SILICON_VAL   0x0500    //!< (Val) QoS Beacon rate value for Silicon as recommended by the HW team

// At-Speed Trace (AST) partitioning Support: HML3_WMCR0/1 regs
#define WMCR_WAYMASK__M                0x000FFFFF  //!< (Mask) Way Allocation control.
#define WMCR_WAYMASK__S                0           //!< (Shift)
#define WMCR_WAYMASK_25_VAL            0xF         //!< (Val) for 25% allocation, use ways[0:3] i.e., col 0
#define WMCR_WAYMASK_50_VAL            0xFF        //!< (Val) for 50% allocation, use ways[0:7] i.e., col 0 and 1

/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    This type of structure stores 4 hex values based on the L3 partial goods
*    yield value employed by the initialization routine
*
* @par Members
*
*                                  <PRE>
*    first_even_inst_num:   The number of the L3 instance that owns the 1st good
*                             even interleave. Used to determine the POS instance
*                             for the even interleave.
*
*    first_odd_inst_num:    The number of the L3 instance that owns the 1st good
*                             odd interleave.  Used to determine the POS instance
*                             for the odd interleave.
*
*    num_even:              The number of L3 nodes(instances) with good even
*                             interleaves. Used for the snoop filter setup.
*
*    num_odd:               The number of L3 nodes with good odd interleaves.
*                                  </PRE>
*
******************************************************************************/

typedef struct
{
    uint32_t first_even_inst_num;
    uint32_t first_odd_inst_num;
    uint32_t num_even;
    uint32_t num_odd;
} l3_pg_t;


#endif   // _MODULE_L3_DEFS_H_
