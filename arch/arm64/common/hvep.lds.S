#include <target/memory.h>
#include <target/percpu.h>

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
  . = SVI_TEXT_BASE;
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

#if CONFIG_DATA_BASE
  ASSERT(. <= CONFIG_DATA_BASE, "data overlap with text")
  . = CONFIG_DATA_BASE;
#endif

  . = ALIGN(PAGE_SIZE);
  __etext = .;

  __sdata = .;

  .data : {
    __data_start = .;
    *(.data .data.*)

    PERCPU_INPUT(SMP_CACHE_BYTES)

    __data_end = .;
  }

#ifndef CONFIG_BSS_IN_DATA
  .bss (NOLOAD) : ALIGN(BSS_ALIGN) {
#else
  .data : ALIGN(BSS_ALIGN) {
#endif
    __bss_start = .;
    *(.bss .bss.*)
    . = ALIGN(BSS_ALIGN);
    __bss_end = .;
  }

  . = ALIGN(PAGE_SIZE);
  __edata = .;

#if CONFIG_HEAP_BASE
  ASSERT(. <= CONFIG_HEAP_BASE, "heap overlap with data")
  . = CONFIG_HEAP_BASE;
#endif

  .pagetable : {
  KEEP (*(.pagetable))
  }
  __heap_start = .;

  ASSERT(. <= STACKS_START, "stacks overflowed with text + data + bss")
}
