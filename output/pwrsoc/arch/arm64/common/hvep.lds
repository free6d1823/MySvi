/*
 * Automatically generated C config: don't edit
 * HVEP version: 1.0.0.0
 * Mon Mar 16 16:05:11 2020
 */
/* Three system performance ? should be considered carefully to choose the
 * software architecture model:
 * 1. throughput: IO throughput should be as great as possible
 * 2. realtime: time critical tasks can be run on time
 * 3. faireness: tasks can be distributed fairly on difference computing
 *               resources
 * Systems will always take throughput into account, realtime and fairness
 * are left for users' choices.
 */
/*
 */
/*
 */
/*
 */
/*
 */
/*
 */
/*
 */
/*
 */
/*
 */
/* Offset of member MEMBER in a struct of type TYPE. */
/*
 */
/* XXX: Atomic Register Access
 *
 * Be aware that no atomic assurance is made for the following macros.
 * Please use __raw_xxxbwl_atomic versions for atomic register access.
 */
/*
 */
/*
 */
/* =================================================================
 * DDI0487B_b ARMv8 ARM
 * ARM Architecture Reference Manual - ARMv8, for ARMv8-A
 * architecture profile
 * ================================================================= */
/* =================================================================
 * D.10.2 General system control registers
 * ================================================================= */
/* D.10.2.19 CPTR_EL2, Architectural Feature Trap Register (EL2)
 * D.10.2.20 CPTR_EL3, Architectural Feature Trap Register (EL3)
 */
/* D.10.2.34 HCR_EL2, Hypervisor Configuration Register */
/* D10.2.74 MIDR_EL1, Main ID Register */
/* D.10.2.81 RMR_EL1, Reset Management Register (EL1)
 * D.10.2.82 RMR_EL2, Reset Management Register (EL2)
 * D.10.2.83 RMR_EL3, Reset Management Register (EL3)
 */
/* D.10.2.88 SCR_EL3, Secure Configuration Register */
/* D.10.2.89 SCTLR_EL1, System Control Register (EL1)
 * D.10.2.90 SCTLR_EL2, System Control Register (EL2)
 * D.10.2.91 SCTLR_EL3, System Control Register (EL3)
 */
/* EL1 only: */
/* EL3/EL2/EL1: */
/* =================================================================
 * D.10.3 Debug registers
 * ================================================================= */
/* D.10.3.16 MDCCSR_EL0, Monitor DCC Status Register */
/* D10.3.18 MDCR_EL3, Monitor Debug Configuration Register (EL3)
 */
/* =================================================================
 * D.10.6 Generic Timer registers
 * ================================================================= */
/* D.10.6.2 CNTHCTL_EL2, Counter-timer Hypervisor Control register */
/* D10.6.9 CNTKCTL_EL1, Conter-timer Kernel Control register */
/* Fields common to CNTHCTL_EL2/CNTKCTL_EL1 */
/* D10.6.3  CNTHP_CTL_EL2,
 *          Counter-timer Hypervisor Physical Timer Control register
 * D10.6.6  CNTHV_CTL_EL2,
 *          Counter-timer Virtual Timer Control register (EL2)
 * D10.6.10 CNTP_CTL_EL0,
 *          Counter-timer Physical Timer Control register
 * D10.6.14 CNTPS_CTL_EL1,
 *          Counter-timer Physical Secure Timer Control register
 */
/*
 */
/* Auto APC Test Framework (cpu_local_exec):
 *
 * Running Flags:
 * SYNC:  Can be defined by a single test function. Tests flagged with
 *        SYNC will start together from all APCs as long as SYNC flag
 *        is also invoked by the dispatcher caller.
 * RAND:  Can be invoked by the dispatcher caller to run all tests in
 *        randomized order. This is useful for stress tests.
 * NOSMP: Cannot be run in SMP mode, if SMP is configured and multiple
 *        testing cores are selected, each core executes the case
 *        serially.
 * SHARE: Memory chunk allocated for the case should be shared between
 *        the runnning cores.
 * DDR:   Can only be run in DDR, otherwise case are dependent on TCM.
 * META:  A case that implements a pattern running style for all other
 *        non-meta cases.
 */
/* Firmware only programs the system fabric region */
/* System fabric sub-regions */
/* HS5 includes QGIC GICs & QGIC GITS */
/* Skip system fabric sub-regions:
 * GMAC-1 (HS2):    0xFF61800000 - 0xFF61D00000
 * GMAC-0 (HS1):    0xFF61000000 - 0xFF61400000
 * Crypto5-1 (HS4): 0xFF60800000 - 0xFF60D00000
 * Crypto5-0 (HS3): 0xFF60000000 - 0xFF60500000
 */
/* IMC fabric sub-regions */
/* Skip IMC fabric sub-regions:
 * RAM5 Cfg: 0xFF6FE40000 - 0xFF6FE80000
 * RAM4 Cfg: 0xFF6FE00000 - 0XFF6FE40000
 * RAM3 Cfg: 0xFF6FDC0000 - 0xFF6FE00000
 * RAM2 Cfg: 0xFF6FD80000 - 0xFF6FDC0000
 * RAM1 Cfg: 0xFF6FD40000 - 0xFF6FD80000
 * RAM0 Cfg: 0xFF6FD00000 - 0xFF6FD40000
 */
/* Skip IMC fabric sub-regions:
 * AHB S0 APU Cfg: 0xFF6F000000 - 0xFF6FA40000
 */
/* TCM default region */
/* TESTOS image related definitions */
/* IMC stack/heap:
 *
 * IMC image stack/heap region is always in IMC internal RAM, adjasent to
 * APC image stack/heap regions.
 */
/* __always_cache/__always_ncache sections:
 *
 * In the combined images, APC .data may be collected into the IMC internal
 * RAM. This may result in failure if such variables are used to implement
 * IMC/APC synchronization mechanisms.
 * So we prepare .cache.sysdata/.ncache.sysdata sections to collect such
 * variables.
 */
/* Add the base address of registers here */
/* QGIC2 is #0 GIC on QDF2400 */
/* STACK is for per CPU */
/* STACKS is for all CPUs */
/* BSS_ALIGN must be a multiple of 16  */
/*
 */
/*
 */
/*
 */
/*
 */
/*
 */
/* Index of L3 blocks */
/*
 */
/*
 */
/*
 */
OUTPUT_FORMAT("elf64-littleaarch64", "elf64-bigaarch64",
              "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
/* A simple memory map */
/*           *
 *    ...    *
 *           *
 -------------  SVI_TEXT_BASE
 *           *
 *           *  text + data + bss
 *           *
 -------------  HEAP_START if not specified
 *           *
 *           *  heap
 *           *
 -------------	STACKS_START
 *           *
 *           *  STACKs
 *           *
 -------------  SVI_RAM_END
 */
SECTIONS
{
  . = (0xFF6F800000 + 0x40000);
  __stext = .;
  .head.text : {
    *(.head.text .head.text.*)
  }
  .text : {
    *(.init.text .init.text.*)
    *(.text .text.*)
  }
  .rodata : {
    *(.rodata .rodata.*)
    . = ALIGN(8);
    __cmd_array_start = .;
    KEEP (*(SORT(.cmd_array.*)))
    __cmd_array_end = .;
    . = ALIGN(8);
    __testfn_start = .;
    KEEP (*(.testfn))
    __testfn_end = .;
  }
  . = ALIGN(4096);
  __etext = .;
  __sdata = .;
  .data : {
    __data_start = .;
    *(.data .data.*)
    . = ALIGN((1 << 7)); __percpu_start = .; *(.sysdata..percpu) . = ALIGN((1 << 7)); __percpu_end = .;
    __data_end = .;
  }
  .bss (NOLOAD) : ALIGN((16 * 4)) {
    __bss_start = .;
    *(.bss .bss.*)
    . = ALIGN((16 * 4));
    __bss_end = .;
  }
  . = ALIGN(4096);
  __edata = .;
  .pagetable : {
  KEEP (*(.pagetable))
  }
  __heap_start = .;
  ASSERT(. <= ((0xFF6F800000 + 0x0000180000) - ((1 << 12) * 48)), "stacks overflowed with text + data + bss")
}
