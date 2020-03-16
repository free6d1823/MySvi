#include "hy_sysini_config.inc"
#include "hy_sysini.inc"
#include <asm/asm_macros.S>
#include <asm/cpu_macros.S>
#include "qc_sysini_port.h"

        EXPORT      hy_sysini
        IMPORT      SYSINI_CONFIG_CPU
        IMPORT      SYSINI_CONFIG_GLOBAL
        IMPORT      L2_INIT_SEMAPHORE_LOC
        IMPORT      Size_CPU_Config_Table

        // Include the common macros
        // INCLUDE     "qctps_common_macros.inc"

        // Include the sysini macros
        //INCLUDE     "hy_sysini.inc"
        //INCLUDE     "hy_sysini_config.inc"

        // Include System Register access macros
        #include    <asm/mach/hydra_macro.h>
        //#include    "hydraSR_AArch64_sysini_only_macro.h"

//------------------------------------------------------------------------------
        //AREA sysini, CODE, ALIGN=3
        AREA sysini, "ax"; .align 3
//------------------------------------------------------------------------------

hy_sysini:
        // Push link reg
        STP             X0, X30, [sp, #-16]!

        // ----------------------------------------------------------------
        // Get pointer to config memory for this CPU
        // ----------------------------------------------------------------

        // Read processor MPIDR[AFFL0] to determine which CPU in the cluster
        MRS             X0, MPIDR_EL1
        AND             X0,X0,#0x00FF


        // Determine offset of CPU configuration table to access
        // (CPU AFFL0 * Size of table)
        LDR             X1, =Size_CPU_Config_Table
        LDR             W1, [X1]

        MUL             X1, X1, X0

        // Calculate location of CPU configuration table to access
        // save in r0 to return from this function : dsr not sure what this means
        LDR             X11, =SYSINI_CONFIG_CPU
        ADD             X11, X11, X1

        // Load L2 init parameter
        LDR             X12, =SYSINI_CONFIG_GLOBAL
        LDRB            W1, [X12, #Offset_L2_Cache_Init]

        // Invalidating the L2 cache arrays, if requested.
        TST             W1, #L2_Init_Flag

        BEQ             l2_init_skip
        BL              hy_l2_init_and_inval
l2_init_skip:

        // Invalidate L1 caches
        BL              hy_l1_init_and_inval

        // Initialize branch prediction
        BL        init_exec_branch_resources

        // Initialize implementation specific SRs that are used statically,
        // but don't get reset to the desired values. These registers
        // don't have to be save/restored at power collapse - they can be reinitialized
        // to a static value on all resets, warm or cold.
        BL              hy_static_reset_init

        // Invalidate TLBs, and initialize implementation-specific translation registers
        BL              init_hydra_tlb_resources

        // Initialize L1 cache related registers
        BL              init_hydra_L1_cache_regs

        // Enable FP if desired
        LDRB            W1, [X11,#Offset_NoFPInit]

        CMP             X1, #0x0
        BNE             skip_fp_enable
        BL              hy_enable_fp
skip_fp_enable:

        // call CPU silicon init function if specified in the config file
        LDRB            W1, [X11,#Offset_Environment]
        CMP             X1, #Environment_Silicon
        BNE             skip_init_silicon_only
        BL              hy_init_silicon_only
skip_init_silicon_only:

        // Restore link reg and return
        LDP             X0, X30, [sp], #16

        RET

//------------------------------------------------------------------------------
// End of sysini main routine. Subroutines follow.
//------------------------------------------------------------------------------

//----------------------------------------------------------------------
// init_exec_branch_resources
// A subset of what is required in simulation.
//----------------------------------------------------------------------

init_exec_branch_resources:

        // Initialize BPCR
        // [63:32]   RES0
        // [31:30]   TBD
        // [29]      FBTICRPBD       Force BTIC Return Payload Branch Disabled (1'b0)
        // [28]      FBTICPCPBD	    Force BTIC PC Relative Payload Branch Disabled (1'b0)
        // [27:26]   BTICT           BTIC threshold (2'b00)
        // [25]      BTICBD          BTIC Branch Disabled (1'b0)
        // [24]      FBTICD          Force BTIC Disabled (1'b0)
        // [23]      FBTICPCED       Force BTIC PC Relative Entries Disabled
        // [22]      FBTICPCGD       Force BTIC PC Relative Gathering Disabled
        // [21:20]   TBD
        // [19]      LSCFG           Link Stack Configuration (1'b0)
        // [18]      FLSRD           Force Link Stack Restore Disabled (1'b0)
        // [17]      FL1BTACD        Force L1 BTAC Disabled (1'b0)
        // [16]      FL0BTACD        Force L0 BTAC Disabled (1'b0)
        // [15:11]   RES0
        // [10]      FTHTUD          Force UHT Useful Bit Disabled (1'b0)
        // [9]       FBHTALTPREDD    Force BHT Alternate Prediction Disabled (1'b0)
        // [8]       FTHT3D          Force THT3 Disabled (1'b0)
        // [7]       FTHT2D          Force THT2 Disabled (1'b0)
        // [6]       FTHT1D          Force THT1 Disabled (1'b0)
        // [5]       FTHT0D          Force THT0 Disabled (1'b0)
        // [4]       FBHTD           Force BHT Disabled (1'b0)
        // [3:2]     RES0
        // [1]       FPHRD           Force Path History Register Disabled (1'b0)
        // [0]       FGHRD           Force Global History Register Disabled (1'b0)

        MOV             X1, #0x0

BPCR_VALUE_SETUP_DONE:

        MSR             BPCR_EL1, X1

        ISB

        ADD             X1, X30, #0          // save return address while ...

        // Initialize link stack with 16 BLs to sequential addresses
        // This must be done with BP enabled to have an effect.
        // Luckily BP is always enabled for Hydra!

        BL              SEQ1
SEQ1:   BL              SEQ2
SEQ2:   BL              SEQ3
SEQ3:   BL              SEQ4
SEQ4:   BL              SEQ5
SEQ5:   BL              SEQ6
SEQ6:   BL              SEQ7
SEQ7:   BL              SEQ8
SEQ8:   BL              SEQ9
SEQ9:   BL              SEQ10
SEQ10:  BL              SEQ11
SEQ11:  BL              SEQ12
SEQ12:  BL              SEQ13
SEQ13:  BL              SEQ14
SEQ14:  BL              SEQ15
SEQ15:  BL              SEQ16
SEQ16:  NOP

        ADD             X30, X1, #0          // restore return address

        RET

//------------------------------------------------------------------------------
// Initialize L1 cache registers and array
//------------------------------------------------------------------------------
hy_l1_init_and_inval:

        // Flash invalidate the I-Cache
        IC IALLU

        // Flash invalidate the D-Cache
        MOVZ            X0, #0
        DCIALL         ,X0

        MOVZ            X0, #0x00000080
        DCIALL         ,X0

        RET

//----------------------------------------------------------------------
// hy_l2_init_and_inval: invalidates L2 arrays and initializes L2 regs
//
//----------------------------------------------------------------------
hy_l2_init_and_inval:

        //----------------------------------------------------------------------
        // Determine which CPU should invalidate the L2 cache and initialize
        // the L2 registers.
        // Use MPIDR[AFFL1] to calculate the address of the L2 semaphore to use.
        // L2 semaphores for each cluster are 64 bytes apart (2 semaphores
        // in each reservation granule).
        // This code assumes that AFFL1 contains the cluster number and AFFL0
        // contains the CPU number within the cluster.
        //----------------------------------------------------------------------
        MRS             X0, MPIDR_EL1
        AND             X3, X0, #0xFF00       // keep AFFL1
        LSR             X3, X3, #2            // (AFFL1 LSR 8) * 64
        AND             X0, X0, #0x00FF       // AFFL0

        // Query and tag the shared memory location to see if
        // this processor is allowed to initialize the L2
        LDR             X5, =L2_INIT_SEMAPHORE_LOC
        ADD             X5, X5, X3

RETRY_SPINLOCK:
        LDAXR           W3, [X5]

        // If not allowed wait
        LSR             X3, X3, X0
        ANDS            X4, X3, #1
        BEQ             WAIT_FOR_L2_INIT

        // If allowed, attempt an exclusive write to the shared location
        // If STXR is successful, initialize the L2, otherwise try again
        LSL             X4, X4, X0
        STXR            W1, W4, [X5]
        CBNZ            W1, RETRY_SPINLOCK

        //----------------------------------------------------------------------
        // Invalidate the L2 cache
        //----------------------------------------------------------------------

L2_INVALIDATE:

        // Use DCIALL op to invalidate L2 cache.
        // The L2 can be variable size of 512KB or 1MB.
        // DCIALL operates per interleave.
        // DCIALL operand:
        //    Bit  7   : interleave (0 or 1)
        //    Bits 2:1 : must be 2'b01 to target L2 cache
        MOVZ            X1, #0x0002
        DCIALL         ,X1
        ADD             X1, X1, #0x80         // advance to the next interleave
        DCIALL         ,X1
        DSB NSH
        ISB

        //--------------------------------------------------------------

        //---------------------------------------------------------------
        MOVZ            X6, #0x0002              // X6 = Falkor pass 2
        compare_cpuid   HXT1_PASS_A, X1, X4, #MIDR_IMPL_HXT, #MIDR_PN_HXT_1

        //----------------------------------------------------------------------
        // Initialize L2 registers
        //----------------------------------------------------------------------
        //---------------------------------------------------------------
        // Read AIDR_EL1, extract the CPU major revision in bits 15:12,
        // and add 1 to determine Falkor pass x.  Use X6 for remainder
        // of this function.
        //---------------------------------------------------------------
        MRS             X4, AIDR_EL1
        UBFX            X6, X4, #12, #4
        ADD             X6, X6, #1           // X6 = Falkor pass x

HXT1_PASS_A:

        // L2CR0 = 0x0007_E7E5
        //
        // 18:16 HWPFL3ASCHT - 3'b111
        // 15 ENHWPFL3AS - 1'b1
        // 14 ENHWPFL3AR - 1'b1
        // 13 ENHWPFL3AI - 1'b1
        // 12:11 TBD -     2'b00
        // 10:8 HWPFL2ASCHT - 3'b111
        // 7 ENHWPFL2AS - 1'b1
        // 6 ENHWPFL2AR - 1'b1
        // 5 ENHWPFL2AI - 1'b1
        // 4 TBD - 1'b0
        // 3:2 WGTOC - 2'b01
        // 1 FRNAL2I - 1'b0
        // 0 DDCIALL - 1'b1

        MOVZ            X1, #L2CR0_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MOVZ            X1, #0xE7E5
        MOVK            X1, #0x0007, LSL #16
        MSR             L2CPUSRDR_EL1, X1
        ISB

        // L2LKCR = 0000_0000
        //
        // 3   LKLLBRE = 1'b0
        // 2   LKLCBRE = 1'b0
        // 1:0 LKE = 2'b00

        MOVZ            X1, #L2LKCR_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MOVZ            X1, #0x0000
        MSR             L2CPUSRDR_EL1, X1
        ISB

        // L2BCR0 = 0x0000_0010
        //
        // 10  OTWBPSS = 1'b0
        // 9   OTWBD = 1'b0
        // 8   QSBMPENCD = 1'b0
        // 7   QSBMPERD = 1'b0
        // 6   EQSBPWE = 1'b0
        // 5:4 EVICTCFG = 2'b01
        // 3   OAWBPBS = 1'b0
        // 2   OAWBD = 1'b0
        // 1   TBD = 1'b0
        // 0   IOSBWCR = 1'b0

        MOVZ            X1, #L2BCR0_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MOVZ            X1, #0x0010
        MSR             L2CPUSRDR_EL1, X1
        ISB

        // L2BCR1 = 0x8006_4213_0FE1_0D14
        //
        // 63    ECPULLQS = 1'b1
        // 62:52 RES0
        // 51:48 LLBOLED = 4'b0110
        // 47:44 LLBOLENCD = 4'b0100
        // 43:40 LLBOLDMLPF = 4'b0010
        // 39:36 LLBONUMBR = 4'b0001
        // 35:32 LLBONUMBOQ = 4'b0011
        // 31:28 LLBOLPMEVT = 4'b0000
        // 27:24 LLBOLESIS = 4'b1111
        // 23:20 LLBOLEIOSD = 4'b1110
        // 19:16 LLBOLERD = 4'b0001
        // 15:12 LLBOLDDI = 4'b0000
        // 11:8  LLBOLTBOQ = 4'b1101
        // 7:4   LLBOLTBR = 4'b0001
        // 3:0   LLQDIV = 4'b0100

        MOVZ            X1, #L2BCR1_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MOVZ            X1, #0x0D14
        MOVK            X1, #0x0FE1, LSL #16
        MOVK            X1, #0x4213, LSL #32
        MOVK            X1, #0x8006, LSL #48
        MSR             L2CPUSRDR_EL1, X1
        ISB

        // L2CPMR = 0x0024_0015
        //
        // 22:20 CPUWUDLYSNP = 3'b010
        // 19:18 CPUSLPDLYSNP = 2'b01
        // 17:16 L2SLPDLYSNPPR = 2'b00
        // 15    DIVCLKOE = 1'b0
        // 14:10 RES0 5'b00000
        // 9     FASTPCACLKEN = 1'b0
        // 8     WUL2SCOR = 1'b0
        // 7:6   RES0 = 2'b00
        // 5:4   L2SLPDLYSNPNR = 2'b01
        // 3:2   L2ACGDLY = 2'b01
        // 1     RES0 = 1'b0
        // 0     EL2SLPREQ = 1'b1

        MOVZ            X1, #L2CPMR_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MOVZ            X1, #0x0015
        MOVK            X1, #0x0024, LSL #16
        MSR             L2CPUSRDR_EL1, X1
        ISB

        // Clear all error status in L2ESR0 by using the write-clear function
        // (i.e. Write a 1 to all L2ESR0 bits to clear)

        MOVZ            X1, #L2ESR0_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MVN             X1, XZR
        MSR             L2CPUSRDR_EL1, X1
        ISB

        // Enable error reporting for:
        //   L2 Tag single bit error CPU Abort or Discard (SEI)
        //   L2 Tag single bit error CPU No Abort (SEI)
        //   L2 Tag single bit error Snoop (SEI to CPU0)
        //   L2 Tag single bit error L2 (SEI to CPU0)
        //
        //   L2 Tag double bit error CPU Abort or Discard (SEI)
        //   L2 Tag double bit error CPU No Abort (SEI)
        //   L2 Tag double bit error Snoop (SEI to CPU0)
        //   L2 Tag double bit error L2 (SEI to CPU0)
        //
        //   L2 Data single bit error CPU Abort or Discard (SEI)
        //   L2 Data single bit error CPU No Abort (SEI)
        //   L2 Data single bit error Snoop (SEI to CPU0)
        //   L2 Data single bit error L2 (SEI to CPU0)
        //
        //   L2 Data double bit error CPU Abort or Discard (SEI)
        //   L2 Data double bit error CPU No Abort (SEI)
        //   L2 Data double bit error Snoop (SEI to CPU0)
        //   L2 Data double bit error L2 (SEI to CPU0)
        //
        //   QSB master port cmd error CPU Abort or Discard (SEI)
        //   QSB master port cmd error CPU No Abort (SEI)
        //   QSB master port cmd error Snoop (SEI to CPU0)
        //   QSB master port cmd error L2 (SEI to CPU0)
        //
        //   QSB master port data error CPU Abort or Discard (SEI)
        //   QSB master port data error CPU No Abort (SEI)
        //
        //
        //   QSB master port LDREX Normal OK error CPU0 (SEI)
        //   QSB master port LDREX Normal OK error CPU1 (SEI)
        //   QSB master port extra read data received error (SEI to CPU0)
        //   QSB snoop port unrecognized command errors (SEI to CPU0)
        //   QSB snoop port unsupported command errors (SEI to CPU0)
        //   QSB snoop port illegal command errors (SEI to CPU0)
        //   Poison error CPU Abort or Discard (SEI)
        //   Poison error CPU No Abort (SEI)
        //   Poison error Snoop (SEI to CPU0)
        //   Poison error L2 (SEI to CPU0)
        //   DECIL2M = 1'b0
        //   FSYNLK = 1'b1          lock syndrome if any L2ESR bit is set
        //   SBECPUADCPURE = 1'b1   indicate error on single corrected error
        //   DCRSWSECE = 1'b1       correct single bit errors if DC_RSW is used
        //   SEDCCFG[1:0] = 2'b01   soft error detect enabled, correction no inline
        //
        //   L2ECR0 = 0x0554_9525_4952_5495
        //   L2ECR1 = 0xD800_0000_0009_5999

        MOVZ            X1, #L2ECR0_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MOVZ            X1, #0x5495
        MOVK            X1, #0x4952, LSL #16
        MOVK            X1, #0x9525, LSL #32
        MOVK            X1, #0x0554, LSL #48
        MSR             L2CPUSRDR_EL1, X1
        ISB

        MOVZ            X1, #L2ECR1_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MOVZ            X1, #0x5999
        MOVK            X1, #0x0009, LSL #16
        MOVK            X1, #0x0000, LSL #32
        MOVK            X1, #0xD800, LSL #48
        MSR             L2CPUSRDR_EL1, X1
        ISB

        //---------------------------------------------------------------
        // Set L2VRF0[DLLQRDVMBAR]=1'b1 (bit 24) for all Falkor variants.
        //    disables LiveLockQuery Response from DVMs and BARriers
        //    DVMs include TLBI, ICIVAU, ICIALLUIS
        //
        // For all Falkor variants:
        //     set L2VRF0[DQSBMPCUCMD[1]]=1'b1 (bit 15)
        //     Originally set only for pass 1 Errata 1027.
        //     Now set for all variants.
        //
        // For Falkor pass 2.0 and later variants:
        //     set L2VRF0[DSDVMBR]=1'b1  (bit 25)
        //---------------------------------------------------------------
        MOVZ            X1, #L2VRF0_IA
        MSR             L2CPUSRSELR_EL1, X1
        ISB
        MRS             X1, L2CPUSRDR_EL1
        ORR             X1, X1, #0x8000
        ORR             X1, X1, #0x01000000
        CMP             X6, #0x1
        BEQ             L2VRF0_WRITE
        ORR             X1, X1, #0x02000000     // pass 2.0 and later
L2VRF0_WRITE:
        MSR             L2CPUSRDR_EL1, X1
        ISB

        //---------------------------------------------------------------
        // If this is a silicon config, call the function that will
        // do any required L2 silicon-specific initialization.
        //---------------------------------------------------------------
        LDRB            W1, [X11,#Offset_Environment]
        CMP             X1, #Environment_Silicon
        BNE             SKIP_L2_SILICON

        // Push link reg and L2 semaphore address (X5), call L2 silicon specific
        // function, and then restore the link reg and X5
        STP             X5, X30, [sp, #-16]!
        BL              hy_init_L2_silicon_only
        LDP             X5, X30, [sp], #16

SKIP_L2_SILICON:

        // Indicate the common L2 init is complete by writing zeros to
        // the shared location.  Address of the L2 semaphore is still
        // held in X5.

        STR             WZR, [X5]
        DSB NSH
        ISB

        B               L2_DONE

WAIT_FOR_L2_INIT:
        // Spin waiting for the shared location to be all 0's
        // All zeros indicates that one of the processors must be done
        // initializing the shared resources
        // X5 still contains the address of the L2 semaphore used
        // with the LDRX instruction above.
        LDR             W1, [X5]
        ANDS            X1, X1, #0xF
        BNE             WAIT_FOR_L2_INIT

L2_DONE:
        RET

//------------------------------------------------------------------------------
// hy_static_reset_init
//
// Initialize implementation specific SRs that are used statically,
// but don't get reset to the desired values. These registers
// don't have to be save/restored at power collapse - they can be reinitialized
// to a static value on all resets, warm or cold.
//------------------------------------------------------------------------------
hy_static_reset_init:

        //---------------------------------------------------------------

        // MIDR = 0x680f0000

        //---------------------------------------------------------------
        MOVZ            X6, #0x0002              // X6 = Falkor pass 2
        compare_cpuid   CHECK_DONE, X5, X4, #MIDR_IMPL_HXT, #MIDR_PN_HXT_1

        //---------------------------------------------------------------
        // Check MIDR value to make sure this is running on Falkor.
        // MIDR = 0x510F8000 (pass 1) or 0x510FC00x (pass 2)
        // If not spin here.
        //---------------------------------------------------------------
        MRS             X5, MIDR_EL1
        ORR             X5, X5, #0x4000          // set bit 14
        BFXIL           X5, XZR, #0, #4          // clear bits 3:0
        MOVZ            X4, #0xC000
        MOVK            X4, #0x510F, LSL #16     // Falkor MIDR
        CMP             X5, X4
NOT_FALKOR:
        BNE             NOT_FALKOR

        //---------------------------------------------------------------
        // Read AIDR_EL1, extract the CPU major revision in bits 15:12,
        // and add 1 to determine Falkor pass x.  Use X6 for remainder
        // of this function.
        //---------------------------------------------------------------
        MRS             X4, AIDR_EL1
        UBFX            X6, X4, #12, #4
        ADD             X6, X6, #1           // X6 = Falkor pass x

CHECK_DONE:
        //---------------------------------------------------------------
        // Initialize ACTLR_ELx to 0.
        //---------------------------------------------------------------
        MSR             ACTLR_EL1, XZR
        MSR             ACTLR_EL2, XZR
        MSR             ACTLR_EL3, XZR

        //---------------------------------------------------------------
        // Set CPACR_EL1 = 0x0030_0000
        // No architectural reset value, so just write directly
        //   28      TTA       = 1'b0
        //   21:20   FPEN      = 2'b11
        //---------------------------------------------------------------
        MOVZ            X1, #0x0030, LSL #16
        MSR             CPACR_EL1, X1

        //---------------------------------------------------------------
        // Clear architectural feature trap register
        // No architectural reset value, so just write directly
        //---------------------------------------------------------------
        MSR             CPTR_EL3, XZR

        // make sure CPACR is complete before continuing
        ISB

        //---------------------------------------------------------------
        // Set CPMR_EL1 = 0x0000_0090
        //  31:30  RES0
        //  29     WFIWFDE  = 1'b0
        //  28     WFEWFDE  = 1'b0
        //  27:16  WAITWFD  = 12'h000
        //  15:10  RES0
        //  9      DIVCLKOE = 1'b0
        //  8:6    L2WUDLY  = 3'b010
        //  5:4    L2SLPDLY = 2'b11
        //  3      FASTPCACLKEN = 1'b0
        //  2      ETMCLKEN = 1'b0
        //  1      NOPWFI   = 1'b0
        //  0      NOPWFE   = 1'b0
        //---------------------------------------------------------------
        MOVZ            X1, #0x00B0
        MSR             CPMR_EL1, X1

        //---------------------------------------------------------------
        // Set ACPTR_EL3 = 0x0000_0000
        //   Don't trap to EL3 any accesses to implementation defined
        //   registers at EL1 or EL2.
        //---------------------------------------------------------------
        MSR             ACPTR_EL3, XZR

        //---------------------------------------------------------------
        // For Falkor Pass 2+, Set ACPTR_EL1 = 0x0000_0000
        //   Don't trap to EL1 any accesses to implementation defined
        //   registers at EL0.
        //---------------------------------------------------------------
        CMP             X6, #1
        BEQ             ACPTR_DONE
WRITE_ACPTR:
        MSR             ACPTR_EL1, XZR

ACPTR_DONE:

        //---------------------------------------------------------------
        // Set QOSIDVLR_EL1 to 0xFF before writing QOSIDR_EL1
        //---------------------------------------------------------------
        MOVZ            X1, #0xFF
        MSR             QOSIDVLR_EL1, X1
        ISB

        //---------------------------------------------------------------
        // Set QOSIDR_ELx registers to 0
        //---------------------------------------------------------------
        MSR             QOSIDR_EL1, XZR
        MSR             QOSIDR_EL2, XZR
        MSR             QOSIDR_EL3, XZR

        //---------------------------------------------------------------
        // Set QOSIDVOR_EL2 to 0
        //---------------------------------------------------------------
        MSR             QOSIDVOR_EL2, XZR

        //---------------------------------------------------------------
        // For all Falkor variants:
        //     set PVR2F0[DSTLDFL1M]=1'b1  (bit 24)  D48246
        //     set PVR2F0[FCDCISW]=1'b1    (bit 1)   D60572
        //---------------------------------------------------------------
        MRS             X1, PVR2F0_EL1
        ORR             X1, X1, #0x01000000
        ORR             X1, X1, #0x00000002
        MSR             PVR2F0_EL1, X1

        //---------------------------------------------------------------
        // For all Falkor variants:
        //     set PVR2F2_EL1[L1DCDPSA] = 0xFF     (bits 31:24)
        //     set PVR2F2_EL1[L1DCDLVPSA] = 0xFF   (bits 39:32)
        //     set PVR2F3_EL1[S1FTLBPSA] = 0xFF    (bits  7:0)
        //---------------------------------------------------------------
        MOVZ            X0, #0xFF
        MRS             X1, PVR2F2_EL1
        BFI             X1, X0, #24, #8
        BFI             X1, X0, #32, #8
        MSR             PVR2F2_EL1, X1

        MRS             X1, PVR2F3_EL1
        BFI             X1, X0, #0, #8
        MSR             PVR2F3_EL1, X1

        //---------------------------------------------------------------
        // For all Falkor variants:
        //     set PVR2F1_EL1[FVRITI] = 1'b1      (bit 15)  D78169
        //---------------------------------------------------------------
        MRS             X1, PVR2F1_EL1
        ORR             X1, X1, #0x00008000
        MSR             PVR2F1_EL1, X1

        //---------------------------------------------------------------
        // Variant specific workarounds start here.
        //---------------------------------------------------------------

        //---------------------------------------------------------------
        // Is this is a pass 1 variant?
        //---------------------------------------------------------------
        CMP             X6, #0x1              // running on pass 1?
        BNE             NOT_PASS1

        //---------------------------------------------------------------
        // For Falkor pass 1 variants:
        //     set PVR2F0[DSSTEX]=1'b1  (bit 45)  Errata 1005
        //     set PVR2F0[DSBAR]=1'b1   (bit 33)  Errata 1007
        //     set PVR2F0[DSTLDF]=1'b1  (bit 21)  Errata 1030
        //---------------------------------------------------------------
        MRS             X1, PVR2F0_EL1
        ORR             X1, X1, #0x0000200000000000
        ORR             X1, X1, #0x0000000200000000
        ORR             X1, X1, #0x0000000000200000
        MSR             PVR2F0_EL1, X1

        //---------------------------------------------------------------
        // For Falkor pass 1 variants:
        //     set PVR2F1[DAL2R] = 2'b11   (bits 5:4)  Errata 1031
        //---------------------------------------------------------------
        MRS             X1, PVR2F1_EL1
        ORR             X1, X1, #0x0030
        MSR             PVR2F1_EL1, X1

        //---------------------------------------------------------------
        // For Falkor pass 1 variants:
        //     set DBGABWR = 0   Errata 1016
        //---------------------------------------------------------------
        MSR             DBGABWR, XZR

        //---------------------------------------------------------------
        // For Falkor pass 1 variants:
        //     set CPMR_EL1[NOPWFE] = 1  (bit 0)  Errata 1029
        //---------------------------------------------------------------
        MRS             X1, CPMR_EL1
        ORR             X1, X1, #0x1
        MSR             CPMR_EL1, X1


        B               WORKAROUND_DONE

NOT_PASS1:

        //---------------------------------------------------------------
        // For Falkor pass 2 variants:
        //     set PVR0F1_EL1[24] = 1  (bit 24)
        //---------------------------------------------------------------
        MRS            X1, PVR0F1_EL1
        ORR            X1, X1, #0x01000000
        MSR            PVR0F1_EL1, X1


WORKAROUND_DONE:

        RET

//-------------------------------------------------------------------------------
// init_hydra_tlb_resources
//
// Initializes TLB and related resources, including:
//
//   TLBCR_EL1
//   CCPR_EL3
//   CCPR_EL1
//   invalidating UTLB array
//
//-------------------------------------------------------------------------------
init_hydra_tlb_resources:

        //--------------------------------------------------------------

        //---------------------------------------------------------------
        MOVZ            X6, #0x0002              // X6 = Falkor pass 2
        compare_cpuid   HXT1_PASS_B, X1, X4, #MIDR_IMPL_HXT, #MIDR_PN_HXT_1

        //---------------------------------------------------------------
        // Read AIDR_EL1, extract the CPU major revision in bits 15:12,
        // and add 1 to determine Falkor pass x.  Use X6 for remainder
        // of this function.
        //---------------------------------------------------------------
        MRS             X4, AIDR_EL1
        UBFX            X6, X4, #12, #4
        ADD             X6, X6, #1           // X6 = Falkor pass x

HXT1_PASS_B:
        //---------------------------------------------------------------
        // TLBCR = 0x0000_0000 (Falkor pass 1)
        // TLBCR = 0x0000_0002 (Falkor pass 2)
        //
        // [8:7]     IWACFG =    2'b00 - use values from page table
        // [6]       DATTLBA =   1'b0
        // [5]       FATDMH =    1'b0
        // [4]       TBD    =    1'b0
        // [3]       DPUIWP =    1'b0
        // [2]       DCONTIG =   1'b0
        // [1]       ERPIPTIC =  1'b0   (pass 1)
        // [1]       EICIALLUISVMF =  1'b1   (pass 2)
        // [0]       DBTLBIIS =  1'b0
        //---------------------------------------------------------------
        MOVZ            X1, #0
        CMP             X6, #0x1              // running on pass 1?
        BEQ             TLBCR_WRITE
        MOVZ            X1, #0x0002
TLBCR_WRITE:
        MSR             TLBCR_EL1, X1

        //---------------------------------------------------------------
        // CCPR_EL3 and CCPR_EL1 = 0x0000_0000  (no forcing)
        //
        // [31:8]    reserved
        // [7]       FWTOCOSH        Force write-through for outer-caches
        //                             for outer-shareable
        // [6]       FNCOCOSH        Force non-cacheable outer-caches
        //                             for other-shareable
        // [5]       FWTICOSH        Force write-through for inner-caches
        //                             for outer-shareable
        // [4]       FNCICOSH        Force non-cacheable inner-caches
        //                             for outer-shareable
        // [3]       FWTOCISH        Force write-through for outer-caches
        //                             for inner-shareable
        // [2]       FNCOCISH        Force non-cacheable outer-caches
        //                             for inner-shareable
        // [1]       FWTICISH        Force write-through for inner-caches
        //                             for inner-shareable
        // [0]       FNCICISH        Force non-cacheable inner-caches
        //                             for inner-shareable
        //---------------------------------------------------------------
        MSR             CCPR_EL3, XZR
        MSR             CCPR_EL1, XZR



        TLBI ALLE3
        TLBI ALLE1

        MRS             X0, SCR_EL3
        MOVZ            X1, #0x1
        ORR             X0, X0, X1
        MSR             SCR_EL3, X0

        ISB             // BMS: Double check that this is required architecturally...it's not
                        // really required micro-architecturally...

        TLBI ALLE2
        TLBI ALLE1

        MOVZ            X1, #0x1
        BIC             X0, X0, X1
        MSR             SCR_EL3, X0

        DSB NSH
        ISB

        RET

//------------------------------------------------------------------------------
// init_hydra_L1_cache_regs
//
// Initialize L1 cache related registers.
//------------------------------------------------------------------------------
init_hydra_L1_cache_regs:

        //---------------------------------------------------------------
        // Clear DCESR (using the write-clear function)
        //---------------------------------------------------------------
        MVN                 X1, XZR
        MSR                 DCESR_EL1, X1

        //---------------------------------------------------------------
        // Set the error report enables in the DCECR
        // Report system errors (SEI) for all L1 D-cache tag/data parity errors
        // and S1FTLB tag/data parity errors.
        // [63]    FSYNLK      - 1'b1
        // [62:10] RES0        - 21'd0
        // [9]     S1FTLBDPEIRE - 1'b0
        // [8]     S1FTLBDPESERE - 1'b1
        // [7]     S1FTLBTPEIRE - 1'b0
        // [6]     S1FTLBTPESERE - 1'b1
        // [5]     L1DPEIRE    - 1'b0
        // [4]     L1DPESERE   - 1'b1
        // [3]     L1PTPEIRE   - 1'b0
        // [2]     L1PTPESERE  - 1'b1
        // [1]     L1VTPEIRE   - 1'b0
        // [0]     L1VTPESERE  - 1'b1
        //---------------------------------------------------------------
        MOVZ                X1, #0x0155
        MOVK                X1, #0x8000, LSL #48
        MSR                 DCECR_EL1, X1

        //---------------------------------------------------------------
        // Clear ICESR (using the write-clear function)
        //---------------------------------------------------------------
        MVN                 X1, XZR
        MSR                 ICESR_EL1, X1

        //---------------------------------------------------------------
        // Set the error report enables in the ICECR
        // Report system errors (SEI) for all L0/L1 I-cache tag/data parity errors
        // [31]    FSYNLK      - 1'b1
        // [30:8]  RES0        - 23'd0
        // [7]     L1DPEIRE    - 1'd0
        // [6]     L1DPESERE   - 1'd1
        // [5]     L1TPEIRE    - 1'd0
        // [4]     L1TPESERE   - 1'd1
        // [3]     L0DPEIRE    - 1'd0
        // [2]     L0DPESERE   - 1'd1
        // [1]     L0TPEIRE    - 1'd0
        // [0]     L0TPESERE   - 1'd1
        //---------------------------------------------------------------
        MOVZ                X1, #0x0055
        MOVK                X1, #0x8000, LSL #16
        MSR                 ICECR_EL1, X1


        //---------------------------------------------------------------
        // Initialize DCCR0_EL1
        //
        // [63:62] EHWPF[1:0]       - 2'b11
        // [61:60] RES0             - 2'b00
        // [59:58] HWPFL3SD[1:0]    - 2'b00   31 deltas ahead
        // [57:56] HWPFL2SD[1:0]    - 2'b00   17 deltas ahead
        // [55:54] HWPFL1SD[1:0]    - 2'b00   2 deltas ahead
        // [53:53] HWPFL1FPE        - 1'b1
        // [52:50] HWPFL1ASCHT[2:0] - 3'b111  16 consecutive
        // [49:48] HWPFL1ADTT[1:0] - 2'b01    5000 cycles
        // [47:47] EHWPFL1AS    - 1'b1
        // [46:46] EHWPFL1AR    - 1'b1
        // [45:45] EHWPFL1AD    - 1'b1
        // [44:44] EHWPFL1AI    - 1'b1
        // [43:43] HWPFL1AC     - 1'b1
        // [42:41] HWPFMST[1:0] - 2'b10
        // [40:40] HWPFGAI      - 1'b0
        // [39:39] TBD          - 2'b00
        // [38:20] RES0         - 19'd0
        // [19:17] TBD          - 3'b000
        // [16:16] DBICMO       - 1'b0
        // [15:12] FBRT[3:0]    - 4'd12 - 13 FBs
        //  [11:8] RES0         - 4'd0
        //   [7:6] FBCTOC[1:0]  - 2'b10 - 255 cycles
        //   [5:5] BDCCMVAU     - 1'b0
        //   [4:4] TRANSL1AC    - 1'b0
        //   [3:3] GPLD         - 1'b0
        //   [2:2] PLDL1AC      - 1'b1
        //   [1:0] PSTL1AC      - 2'b00
        //---------------------------------------------------------------
        MOVZ                X1, #0xC084
        MOVK                X1, #0x0000, LSL #16
        MOVK                X1, #0xFC00, LSL #32
        MOVK                X1, #0xC03D, LSL #48
        MSR                 DCCR0_EL1, X1

CACHE_DONE:

        RET

//----------------------------------------------------------------------
// hy_enable_fp: enables the VeNum VFP/ASE hardware
//----------------------------------------------------------------------
hy_enable_fp:

        //---------------------------------------------------------------
        // Note that the default ARM C environment will set
        // the FZ and DN bits (flush-to-zero, default NaN)
        //---------------------------------------------------------------
        MOVZ            X0, #0x0100, LSL #16        // Set FZ mode
        MSR             FPCR, X0

        MOVZ            X0, #0x0
        MSR             FPSR, X0

        RET

//----------------------------------------------------------------------
// hy_init_silicon_only: Additional settings for silicon.
//----------------------------------------------------------------------
hy_init_silicon_only:


        // Contents TBD

        RET

//----------------------------------------------------------------------
// hy_init_L2_silicon_only: Additional L2 settings for silicon.
//----------------------------------------------------------------------
hy_init_L2_silicon_only:


        // Contents TBD

        RET


        END
