#include <target/assembler.h>
#include <target/memory.h>

#define Mode_USR 0x10
#define Mode_FIQ 0x11
#define Mode_IRQ 0x12
#define Mode_SVC 0x13
#define Mode_MON 0x16
#define Mode_ABT 0x17
#define Mode_UND 0x1B
#define Mode_SYS 0x1F
#define Mode_HYP 0x1A
#define I_Bit 0x80 // when I bit is set, IRQ is disabled
#define F_Bit 0x40 // when F bit is set, FIQ is disabled

//----------------------------------------------------------------

    .section  VECTORS,"ax"
    .align 3

//----------------------------------------------------------------
// Entry point for the Reset handler
//----------------------------------------------------------------

    .global Start
    .type Start, "function"

Start:

//----------------------------------------------------------------
// EL2 Exception Vector Table
//----------------------------------------------------------------

EL2_Vectors:
        LDR PC, EL2_Reset_Addr
        LDR PC, EL2_Undefined_Addr
        LDR PC, EL2_HVC_Addr
        LDR PC, EL2_Prefetch_Addr
        LDR PC, EL2_Abort_Addr
        LDR PC, EL2_HypModeEntry_Addr
        LDR PC, EL2_IRQ_Addr
        LDR PC, EL2_FIQ_Addr


EL2_Reset_Addr:         .word    EL2_Reset_Handler
EL2_Undefined_Addr:     .word    EL2_Undefined_Handler
EL2_HVC_Addr:           .word    EL2_HVC_Handler
EL2_Prefetch_Addr:      .word    EL2_Prefetch_Handler
EL2_Abort_Addr:         .word    EL2_Abort_Handler
EL2_HypModeEntry_Addr:  .word    EL2_HypModeEntry_Handler
EL2_IRQ_Addr:           .word    EL2_IRQ_Handler
EL2_FIQ_Addr:           .word    EL2_FIQ_Handler


//----------------------------------------------------------------
// EL2 Exception Handlers
//----------------------------------------------------------------

.type EL2_Undefined_Handler, "function"
EL2_Undefined_Handler:
        B   EL2_Undefined_Handler
.type EL2_HVC_Handler, "function"
EL2_HVC_Handler:
        B   EL2_HVC_Handler
.type EL2_Prefetch_Handler, "function"
EL2_Prefetch_Handler:
        B   EL2_Prefetch_Handler
.type EL2_Abort_Handler, "function"
EL2_Abort_Handler:
        B   EL2_Abort_Handler
.type EL2_HypModeEntry_Handler, "function"
EL2_HypModeEntry_Handler:
        B   EL2_HypModeEntry_Handler
.type EL2_IRQ_Handler, "function"
EL2_IRQ_Handler:
        B   EL2_IRQ_Handler
.type EL2_FIQ_Handler, "function"
EL2_FIQ_Handler:
        B   EL2_FIQ_Handler


//----------------------------------------------------------------
// EL1 Exception Vector Table
//----------------------------------------------------------------
// Note: LDR PC instructions are used here, though branch (B) instructions
// could also be used, unless the exception handlers are >32MB away.

    .align 5
EL1_Vectors:
        LDR PC, EL1_Reset_Addr
        LDR PC, EL1_Undefined_Addr
        LDR PC, EL1_SVC_Addr
        LDR PC, EL1_Prefetch_Addr
        LDR PC, EL1_Abort_Addr
        LDR PC, EL1_Reserved
        LDR PC, EL1_IRQ_Addr
        LDR PC, EL1_FIQ_Addr


EL1_Reset_Addr:     .word    EL1_Reset_Handler
EL1_Undefined_Addr: .word    EL1_Undefined_Handler
EL1_SVC_Addr:       .word    EL1_SVC_Handler
EL1_Prefetch_Addr:  .word    EL1_Prefetch_Handler
EL1_Abort_Addr:     .word    EL1_Abort_Handler
EL1_Reserved_Addr:  .word    EL1_Reserved
EL1_IRQ_Addr:       .word    EL1_IRQ_Handler
EL1_FIQ_Addr:       .word    EL1_FIQ_Handler


//----------------------------------------------------------------
// EL1 Exception Handlers
//----------------------------------------------------------------

.type EL1_Undefined_Handler, "function"
EL1_Undefined_Handler:
        B   EL1_Undefined_Handler
.type EL1_SVC_Handler, "function"
EL1_SVC_Handler:
        B   EL1_SVC_Handler
.type EL1_Prefetch_Handler, "function"
EL1_Prefetch_Handler:
        B   vector_pabt
.type EL1_Abort_Handler, "function"
EL1_Abort_Handler:
        B   vector_dabt
EL1_Reserved:
        B   EL1_Reserved
.type EL1_IRQ_Handler, "function"
EL1_IRQ_Handler:
        B   vector_irq
.type EL1_FIQ_Handler, "function"
EL1_FIQ_Handler:
        B   EL1_FIQ_Handler


//----------------------------------------------------------------
// EL2 Reset Handler
//----------------------------------------------------------------

    .section  RESET,"ax"
    .align 3

#ifdef __THUMB__
    .thumb
#endif

.type EL2_Reset_Handler, "function"
EL2_Reset_Handler:

    // Change EL2 exception base address
        LDR r0, =EL2_Vectors
        MCR p15, 4, r0, c12, c0, 0      //  Write to HVBAR

    // Init HSCTLR
        LDR r0, =0x30C5180C             // See TRM for decoding
        MCR p15, 4, r0, c1, c0, 0       // Write to HSCTLR

    // Enable EL1 access to all IMP DEF registers
        LDR r0, =0x7F81
        MCR p15, 4, r0, c1, c0, 1       // Write to HACTLR

    // Change EL1 exception base address
        LDR r0, =EL1_Vectors
        MCR p15, 0, r0, c12, c0, 0      // Write to VBAR

    // Go to SVC mode
        MRS r0, cpsr
        MOV r1, #Mode_SVC
        BFI r0, r1, #0, #5
#ifdef __THUMB__
        ORR r0, r0, #(0x1 << 5)         // Set T bit
#endif
        MSR spsr_hyp, r0
        LDR r0, =EL1_Reset_Handler
        MSR elr_hyp, r0
        DSB
        ISB
        ERET

EL1_Reset_Handler:

//----------------------------------------------------------------
// Disable MPU and caches
//----------------------------------------------------------------

    // Disable MPU and cache in case it was left enabled from an earlier run
    // This does not need to be done from a cold reset

        MRC p15, 0, r0, c1, c0, 0       // Read System Control Register
        BIC r0, r0, #0x05               // Disable MPU (M bit) and data cache (C bit)
        BIC r0, r0, #0x1000             // Disable instruction cache (I bit)
        DSB                             // Ensure all previous loads/stores have completed
        MCR p15, 0, r0, c1, c0, 0       // Write System Control Register
        ISB                             // Ensure subsequent insts execute wrt new MPU settings

//----------------------------------------------------------------
// Initialize Stacks using Linker symbol from scatter file.
// ABT, IRQ, FIQ, UNDEF size = STACKSIZE, SVC the rest.
// Stacks must be 8 byte aligned.
//----------------------------------------------------------------

#define STACKSIZE 512
        //
        // Setup the stack(s) for this CPU
        // the scatter file allocates 2^14 bytes per stack
        //
        MRC  p15, 0, r1, c0, c0, 5      // Read CPU ID register
        AND  r1, r1, #0x03              // Mask off, leaving the CPU ID field
        LDR  r0, =__StackTop
        SUB  r0, r0, r1, lsl #14

        CPS #Mode_ABT
        MOV SP, r0

        CPS #Mode_IRQ
        SUB r0, r0, #STACKSIZE
        MOV SP, r0

        CPS #Mode_FIQ
        SUB r0, r0, #STACKSIZE
        MOV SP, r0

        CPS #Mode_SVC
        SUB r0, r0, #STACKSIZE
        MOV SP, r0

//----------------------------------------------------------------
// Cache invalidation. However Cortex-R52 provides CFG signals to
// invalidate cache automatically out of reset (CFGL1CACHEINVDISx)
//----------------------------------------------------------------


//----------------------------------------------------------------
// TCM Configuration
//----------------------------------------------------------------


//----------------------------------------------------------------
// MPU Configuration
//----------------------------------------------------------------


//----------------------------------------------------------------
// Enable MPU and branch to C library init
// Leaving the caches disabled until after scatter loading.
//----------------------------------------------------------------

//        MRC     p15, 0, r0, c1, c0, 0       // Read System Control Register
//        ORR     r0, r0, #0x01               // Set M bit to enable MPU
//        DSB                                 // Ensure all previous loads/stores have completed
//        MCR     p15, 0, r0, c1, c0, 0       // Write System Control Register
//        ISB                                 // Ensure subsequent insts execute wrt new MPU settings

//Check which CPU I am
        MRC p15, 0, r0, c0, c0, 5       // Read MPIDR
        ANDS r0, r0, #0xF
        BEQ cpu0                        // If CPU0 then initialise C runtime
        CMP r0, #1
        BEQ loop_wfi                    // If CPU1 then jump to loop_wfi
        CMP r0, #2
        BEQ loop_wfi                    // If CPU2 then jump to loop_wfi
        CMP r0, #3
        BEQ loop_wfi                    // If CPU3 then jump to loop_wfi
error:
        B error                         // else.. something is wrong

loop_wfi:
        DSB SY      // Clear all pending data accesses
        WFI         // Go to sleep
        B loop_wfi


cpu0:
	.global     cpu_init
	.global     main

// clear bss section

	LDR	R0, =__bss_start
	LDR	R1, =__bss_end

	LDR R8, =0
	LDR R9, =0
	LDR R10, =0
	LDR R11, =0

bss_loop:
.rept (BSS_ALIGN / 16)
	STMIA	R0!, {R8-R11}
.endr
	CMP	R0, R1
	BLT	bss_loop

	BL      cpu_init
	B       main
