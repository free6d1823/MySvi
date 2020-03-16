//-------------------------------------------------------------------------------
//-- Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
//-- All Rights Reserved.
//-- Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
//--
//-- Copyright (c) 2014, 2016 Qualcomm Technologies, Inc.
//-- All Rights Reserved.
//-- Confidential and Proprietary - Qualcomm Technologies, Inc.
//--
//-- All data and information contained in or disclosed by this document are
//-- confidential and proprietary information of Qualcomm Technologies Incorporated, and
//-- all rights therein are expressly reserved. By accepting this material,
//-- the recipient agrees that this material and the information contained
//-- therein are held in confidence and in trust and will not be used,
//-- copied, reproduced in whole or in part, nor its contents revealed in
//-- any manner to others without the express written permission of QUALCOMM
//-- Incorporated.
//--
//-------------------------------------------------------------------------------
//============================================================================
//
//                            MODULE INCLUDES
//
//============================================================================
#include "hy_sysini_config.inc"
#include <asm/asm_macros.S>
#include <asm/cpu_macros.S>
#include <asm/mach/hydra_macro.h>
#include <asm/mach/platform_def.h>

/* MIDRs for QDF2400 */
#define QC_FALKOR_QDF2400_MIDR		0x510F8000
#define QC_FALKOR_V2_QDF2400_MIDR	0x510FC001
#define QC_FALKOR_V2_1_QDF2400_MIDR	0x510FC002
#define QC_FALKOR_V2_HXT1_MIDR          0x680F0000
#define QC_FALKOR_V2_HXT1_1_MIDR	0x680F0001

#define PCBENCH_PREFETCH_SETTINGS         -1
#define PCBENCH_SYSINI_OVERRIDE_VAR       0x402
//============================================================================
//
//                             MODULE EXPORTS
//
//============================================================================
	.globl	plat_my_core_pos
	.globl sysini_wrapper
	.globl read_clear_l2vrf0_26
	.globl set_l2vrf0_26
	.extern L2_INIT_SEMAPHORE_LOC

//------------------------------------------------------------------------------
.text
.align 3
//------------------------------------------------------------------------------

	/* -----------------------------------------------------
	 *  unsigned int plat_my_core_pos(void);
	 *  With this function: CorePos = (ClusterId * 2) +
	 *  				  CoreId
	 * -----------------------------------------------------
	 */
func plat_my_core_pos
	mrs	x0, MPIDR_EL1
	and	x1, x0, #MPIDR_CPU_MASK
	and	x0, x0, #MPIDR_CLUSTER_MASK
	lsr	x0, x0, #MPIDR_AFF1_SHIFT
	mov	x2, #PLATFORM_MAX_CPUS_PER_CLUSTER
	madd	x0, x0, x2, x1
	ret
endfunc plat_my_core_pos

// void sysini_wrapper(void)
func sysini_wrapper
	stp	x0, x30, [sp, #-0x10]!

	//--------------------------------------------------------------
	// Run sysini
	//--------------------------------------------------------------
	bl	hy_sysini

	//--------------------------------------------------------------
	// Optionally set DCCR0_EL1[EHWPF] to enable certain Lx Prefetch
	// Based on UEFI variable prefetch_settings
	//--------------------------------------------------------------
	//bl	plat_get_prefetch_settings
	ldr	x0, =PCBENCH_PREFETCH_SETTINGS
#if 0
	cmp	x0, QC_HOB_INVALID_PARAM_VAL
	beq	skip_prefetch_settings
#else
	cmp	x0, PCBENCH_PREFETCH_SETTINGS
	beq	skip_prefetch_settings
#endif

	mrs	x1, DCCR0_EL1
	ubfx	x2, x0, #0, #2  // Use bits [0:1] from prefetch_settings
	bfi	x1, x2, #62, #2 // Insert into bits 63:62
	msr	DCCR0_EL1, x1
skip_prefetch_settings:

	//--------------------------------------------------------------
	// Optionally set L2ECR1[ESEALDL2M] to enable SEA on Load L2 Miss
	// Based on UEFI variable sysini_override, bit 0
	//--------------------------------------------------------------
	//bl	plat_get_sysini_override_var
	ldr	x0, =PCBENCH_SYSINI_OVERRIDE_VAR
	tbz	x0, #0x0, skip_ESEALDL2M_enable

	movz	x1, #L2ECR1_IA
	msr	L2CPUSRSELR_EL1, x1
	isb
	mrs	x1, L2CPUSRDR_EL1
	orr	x1, x1, #0x0400000000000000
	msr	L2CPUSRDR_EL1, x1
	isb
skip_ESEALDL2M_enable:

	//--------------------------------------------------------------
	// Optionally set PVR2F0[DL1NCMEMQR]=1'b1 (bit 25) to disable the
	// non-cacheable store gathering in CPU.
	// Based on UEFI variable sysini_override, bit 1
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x1, skip_DL1NCMEMQR_disable

	mrs	x1, PVR2F0_EL1
	orr	x1, x1, #0x02000000	// set bit25
	msr	PVR2F0_EL1, x1
skip_DL1NCMEMQR_disable:

	//--------------------------------------------------------------
	// Get Falkor pass number. Some workarounds apply to pass 1 only.
	//--------------------------------------------------------------

	//---------------------------------------------------------------
	compare_cpuid NOT_PASS1, x2, x1, MIDR_IMPL_HXT, MIDR_PN_HXT_1

	mrs	x2, AIDR_EL1
	ubfx	x1, x2, #12, #4
	add	x1, x1, #1	// x1 = Falkor pass x
	cmp	x1, #0x1	// running on pass 1?
	bne	NOT_PASS1

	//--------------------------------------------------------------
	// Optionally set PVR2F1[DAL2R]=2'b00 to disable Erratum 1031 workaround
	// Based on UEFI variable sysini_override, bit 2
	// Falkor Pass 1 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x2, skip_erratum_1031_disable

	mrs	x1, PVR2F1_EL1
	bfm	x1, xzr, #60, #1	// Clear bits 5:4
	msr	PVR2F1_EL1, x1
skip_erratum_1031_disable:

	//--------------------------------------------------------------
	// Optionally set PVR2F0[DSSTEX]=1'b0 to disable Erratum 1005 workaround
	// Based on UEFI variable sysini_override, bit 3
	// Falkor Pass 1 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x3, skip_erratum_1005_disable

	mrs	x1, PVR2F0_EL1
	bfm	x1, xzr, #19, #0	// Clear bit 45
	msr	PVR2F0_EL1, x1
skip_erratum_1005_disable:

	//--------------------------------------------------------------
	// Optionally set PVR2F0[DSBAR]=1'b0 to disable Erratum 1007 workaround
	// Based on UEFI variable sysini_override, bit 4
	// Falkor Pass 1 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x4, skip_erratum_1007_disable

	mrs	x1, PVR2F0_EL1
	bfm	x1, xzr, #31, #0	// Clear bit 33
	msr	PVR2F0_EL1, x1
skip_erratum_1007_disable:

	//--------------------------------------------------------------
	// Optionally set PVR2F0[DSTLDF]=1'b0 to disable Erratum 1030 workaround
	// Based on UEFI variable sysini_override, bit 5
	// Falkor Pass 1 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x5, skip_erratum_1030_disable

	mrs	x1, PVR2F0_EL1
	bfm	x1, xzr, #43, #0	// Clear bit 21
	msr	PVR2F0_EL1, x1
skip_erratum_1030_disable:

	//--------------------------------------------------------------
	// Optionally set TLBCR_EL1[ERPIPTIC]=1'b1 to Enable Relaxed PIPT Instruction Cache
	// Based on UEFI variable sysini_override, bit 6
	// Falkor Pass 1 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x6, skip_enable_rpipt_icache

	mrs	x1, TLBCR_EL1
	orr	x1, x1, #2		// Set bit 1
	msr	TLBCR_EL1, x1
skip_enable_rpipt_icache:

	//--------------------------------------------------------------
	// Optionally set CPMR_EL1[NOPWFE] = 0'b0 to disable Erratum 1029 workaround
	// Based on UEFI variable sysini_override, bit 7
	// Falkor Pass 1 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x7, skip_erratum_1029_disable

	mrs	x1, CPMR_EL1
	and	x1, x1, #~0x1
	msr	CPMR_EL1, x1
skip_erratum_1029_disable:

	b	SKIP_PASS_2_SPECIFIC

NOT_PASS1:

	// Set PMACTLR_EL0 to 0x1 so reads of PMPCCPTR_EL0 trap to EL3 not EL1.
	MOV	X1, #0x1
	MSR	PMACTLR_EL0, X1

	// Set the PMPCCPTCR1_EL2 register to 0x0.
	MOV	X1, #0x0
	MSR	PMPCCPTCR1_EL2, X1

	//--------------------------------------------------------------
	// Get the MIDR
	//--------------------------------------------------------------
	mrs	x1, midr_el1

	ldr x2, =QC_FALKOR_V2_QDF2400_MIDR

	cmp x1, x2
	beq PASS_2_x

	//--------------------------------------------------------------
	// Optionally control additional barrier acceleration control.
	// -If UEFI sysini_override bit 10 is 1, set L2VRF0[EFBIC]=1
	//  and PVR2F0[DSBAR]=0
	// -If UEFI sysini_override bit 10 is 0, set L2VRV0[EFBIC]=0 and set
	//  PVR2F0[DSBAR] according to the sysini_override bit 8.
	// Based on UEFI variable sysini_override, bit10
	// Falkor Pass 2.1 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #10, skip_disable_additional_barrier_accel

	movz	x1, #L2VRF0_IA
	msr	L2CPUSRSELR_EL1, x1
	isb
	mrs	x1, L2CPUSRDR_EL1
	orr	x1, x1, #0x4000000	// set bit26
	msr	L2CPUSRDR_EL1, x1
	isb

	b skip_disable_barrier_accel

skip_disable_additional_barrier_accel:

PASS_2_x:

	//--------------------------------------------------------------
	// Optionally set PVR2F0[DSBAR]=1'b1 to disable aggressive barrier acceleration
	// Based on UEFI variable sysini_override, bit 8
	// Falkor Pass 2 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x8, skip_disable_barrier_accel

	mrs	x1, PVR2F0_EL1
	orr	x1, x1, #0x0200000000	// set bit33
	msr	PVR2F0_EL1, x1
skip_disable_barrier_accel:

	//--------------------------------------------------------------
	// By default, bus requests for DVM ops such as IC IVAU are
	// pipelined (L2VRF0[DSDVMBR]=1).
	// Optionally, set L2VRF0[DSDVMBR]=0 to serialize bus requests for DVM ops.
	// Based on UEFI variable sysini_override, bit9
	// Falkor Pass 2 only
	//--------------------------------------------------------------

	// x0 still contains sysini_override_var from above
	tbz	x0, #0x9, skip_serialize_dvm_ops

	movz	x1, #L2VRF0_IA
	msr	L2CPUSRSELR_EL1, x1
	isb
	mrs	x1, L2CPUSRDR_EL1
	bfm	x1, xzr, #39, #0	// Clear bit 25
	msr	L2CPUSRDR_EL1, x1
	isb
skip_serialize_dvm_ops:

SKIP_PASS_2_SPECIFIC:

	//--------------------------------------------------------------
	// Set CPMR_EL1[DIVCLKOE] to support Performance Counters
	//--------------------------------------------------------------
	MRS	x1, CPMR_EL1
	MOVZ	x2, #0x1		// Enable
	BFI	x1, x2, #9, #1		// Insert into bits 9:9
	MSR	CPMR_EL1, x1

	//---------------------------------------------------------------
	// Set QOSIDVLR_EL1 to value 239 (255-16) since we have reserved
	// the upper 16 QOSIDs (240-255) for DMA masters.
	//---------------------------------------------------------------
	MOVZ	x1, #239
	MSR	QOSIDVLR_EL1, x1

	//---------------------------------------------------------------
	// Set HACR_EL2 to value 0, to clear bad power on reset config
	//---------------------------------------------------------------
	MOVZ	x1, #0
	MSR	HACR_EL2, x1

	//---------------------------------------------------------------
	// Set CPTR_EL2 to value 0x33FF, to clear bad power on reset config
	//---------------------------------------------------------------
	MOVZ	x1, #0x33FF
	MSR	CPTR_EL2, x1

	//---------------------------------------------------------------
	// Set ACPTR_EL3 = 0xFFFF_FDFF
	//   Trap to EL3 most accesses to implementation-defined
	//   registers at EL1 or EL2.
	//   RBB system registers will trap to EL3.
	//   Clear bit 10 to allow pcc capture w/o trapping.
	//---------------------------------------------------------------
	MOV	X1, #0xFFFFFFFF
	BIC	X1, X1, #0x00000200 // Clear the TCPUPMPCCPT bit to allow PCC capture w/o trapping.
	MSR	ACPTR_EL3, X1

	// Barriers to make sure all above operations have completed
	dsb nsh
	isb

	ldp	x0, x30, [sp], #0x10
	ret
endfunc sysini_wrapper

	/* -----------------------------------------------------
	 *  unsigned read_clear_l2vrf0_26(void);
	 * -----------------------------------------------------
	 */
func read_clear_l2vrf0_26
	movz	x1, #L2VRF0_IA
	msr	L2CPUSRSELR_EL1, x1
	isb
	mrs	x1, L2CPUSRDR_EL1
	mov	x0, xzr
	bfm	x0, x1, #26, #26
	cbz	x0, skip_clear
	bfm	x1, xzr, #38, #0	// clear bit26
	msr	L2CPUSRDR_EL1, x1
	isb
skip_clear:
	ret
endfunc read_clear_l2vrf0_26

	/* -----------------------------------------------------
	 *  void set_l2vrf0_26(void);
	 * -----------------------------------------------------
	 */
func set_l2vrf0_26
	movz	x1, #L2VRF0_IA
	msr	L2CPUSRSELR_EL1, x1
	isb
	mrs	x1, L2CPUSRDR_EL1
	orr	x1, x1, #0x4000000	// set bit26
	msr	L2CPUSRDR_EL1, x1
	isb
	ret
endfunc set_l2vrf0_26

	/* ----------------------------------------------------
	 * void sysini_init_l2(void)
	 *
	 * Sysini uses the data at L2_INIT_SEMAPHORE_LOC to manage
	 * initialization of the L2s. This function resets the data
	 * for the calling core's L2 such that sysini will reinitialize
	 * the L2 when the first core in this cluster comes online the
	 * next time.
	 * ----------------------------------------------------
	 */
func sysini_init_l2
	stp	x0, x30, [sp, #-0x10]!

	/*----------------------------------------------------------------------
	 * Use MPIDR[AFFL1] to calculate the address of the L2 semaphore to use.
	 * L2 semaphores for each cluster are 64 bytes apart (2 semaphores
         * in each reservation granule).
         * This code assumes that AFFL1 contains the cluster number.
	 *----------------------------------------------------------------------
	 */
	mrs	x0, mpidr_el1
	and	x3, x0, #0xFF00		// keep AFFL1
	lsr	x3, x3, #2		// (AFFL1 * 64)

	ldr	x2, =L2_INIT_SEMAPHORE_LOC
	add	x2, x2, x3

	mov	x4, #0x3		// initial value

lock_l2_init_sem:
	ldxr	w3, [x2]		// ignore current value
	stxr	w5, w4, [x2]
	cmp	w5, #0
	bne	lock_l2_init_sem

	ldp	x0, x30, [sp], #0x10
	ret
endfunc sysini_init_l2

	/* ----------------------------------------------------
	 * The CPU Ops reset function
	 * ----------------------------------------------------
	 */
func qc_falkor_QDF2400_reset_func
	/* ---------------------------------------------
	 * As a bare minimum enable the SMP bit.
	 * ---------------------------------------------
	 * mrs	x0, CPUECTLR_EL1
	 * orr	x0, x0, #CPUECTLR_SMP_BIT
	 * msr	CPUECTLR_EL1, x0
	 * isb
	 * mov		x0, #0
	 * mov	x18, x30
	 * bl hy_sysini
	 * mov x30, x18
	 */
	ret
endfunc qc_falkor_QDF2400_reset_func

	/* ----------------------------------------------------
	 * The CPU Ops core power down function
	 * ----------------------------------------------------
	 */
func qc_falkor_QDF2400_core_pwr_dwn
	/* ---------------------------------------------
         * Leave caches enabled due to use of
         * HW_ASSISTED_COHERENCY build flag.
	 * ---------------------------------------------
	 */
	ret
endfunc qc_falkor_QDF2400_core_pwr_dwn

	/* ----------------------------------------------------
	 * The CPU Ops cluster power down function
	 * ----------------------------------------------------
	 */
func qc_falkor_QDF2400_cluster_pwr_dwn
	stp	x0, x30, [sp, #-0x10]!

	/* ---------------------------------------------
         * Leave caches enabled due to use of
         * HW_ASSISTED_COHERENCY build flag.
	 * ---------------------------------------------
	 */

	/* ---------------------------------------------
	 * L2 being powered off, tell sysini to reinit.
	 * ---------------------------------------------
	 */
	bl sysini_init_l2

	ldp	x0, x30, [sp], #0x10
	ret
endfunc qc_falkor_QDF2400_cluster_pwr_dwn

	/* ----------------------------------------------------
	 * Not providing any Falkor-specific register
	 * information for crash reporting.
	 * It needs to return with x6 pointing to
	 * a list of register names in ascii and
	 * x8 - x15 having values of registers to be
	 * reported.
	 * ----------------------------------------------------
	 */
func qc_falkor_QDF2400_cpu_reg_dump
	mov	x6, xzr
	ret
endfunc qc_falkor_QDF2400_cpu_reg_dump


/* declare_cpu_ops MUST be at the end of the file for mem align reasons */
declare_cpu_ops qc_falkor_QDF2400, QC_FALKOR_QDF2400_MIDR, \
	qc_falkor_QDF2400_reset_func, \
	qc_falkor_QDF2400_core_pwr_dwn, \
	qc_falkor_QDF2400_cluster_pwr_dwn
declare_cpu_ops qc_falkor_QDF2400, QC_FALKOR_V2_QDF2400_MIDR, \
	qc_falkor_QDF2400_reset_func, \
	qc_falkor_QDF2400_core_pwr_dwn, \
	qc_falkor_QDF2400_cluster_pwr_dwn
declare_cpu_ops qc_falkor_QDF2400, QC_FALKOR_V2_HXT1_MIDR, \
	qc_falkor_QDF2400_reset_func, \
	qc_falkor_QDF2400_core_pwr_dwn, \
	qc_falkor_QDF2400_cluster_pwr_dwn
declare_cpu_ops qc_falkor_QDF2400, QC_FALKOR_V2_HXT1_1_MIDR, \
	qc_falkor_QDF2400_reset_func, \
	qc_falkor_QDF2400_core_pwr_dwn, \
	qc_falkor_QDF2400_cluster_pwr_dwn
