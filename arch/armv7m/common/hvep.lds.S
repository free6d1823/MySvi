#include <target/memory.h>
#include <asm/memory.h>

#ifdef STACK_SIZE
#undef STACK_SIZE
#define STACK_SIZE	0x400
#endif

#define M_VECTOR_RAM_SIZE 0x0;

ENTRY(Reset_Handler)

/* A simple memory map */
/*		*
 *		*
 *		*
 -------------	interrupts
 *		*
 *		*
 *		*
 -------------	SVI_TEXT_BASE
 *		*
 *		*	text + data + bss
 *		*
 -------------	SVI_DATA_BASE
 *		*
 *		*	data + bss
 *		*
 -------------  HEAP_START if not specified
 *		*
 *		*	heap
 *		*
  -------------  STACK_START if not specified
 *		*
 *		*	STACKs
 *		*
 -------------	SVI_RAM_END
 */

SECTIONS
{
#ifdef INTERRUPT_BASE
	. = INTERRUPT_BASE;
	/* The startup code goes first into internal flash */
	.interrupts :
	{
		__VECTOR_TABLE = .;
		. = ALIGN(4);
		KEEP(*(.isr_vector))     /* Startup code */
		. = ALIGN(4);
	}
#endif

	. = SVI_TEXT_BASE;
	__stext = .;
	.text :
	{
		. = ALIGN(4);
		*(.text)				 /* .text sections (code) */
		*(.text*)				 /* .text* sections (code) */
		*(.glue_7)				 /* glue arm to thumb code */
		*(.glue_7t) 			 /* glue thumb to arm code */
		*(.eh_frame)
		. = ALIGN(4);
	}

	.rodata :
	{
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

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	}
	__etext = .;

#ifdef INTERRUPT_RAM_BASE
	.interrupts_ram :
	{
		. = ALIGN(4);
		__interrupts_ram_start__ = .; /* Create a global symbol at data start */
		*(.m_interrupts_ram)	 /* This is a user defined section */
		. += M_VECTOR_RAM_SIZE;
		. = ALIGN(4);
		__interrupts_ram_end__ = .; /* Define a global symbol at data end */
	}
#endif

#ifdef SVI_DATA_BASE
	. = SVI_DATA_BASE;
#endif
	__sdata = .;

	.data :
	{
		__data_start = .;
		*(.data .data.*)
		KEEP(*(.jcr*))
		. = ALIGN(4);
		__data_end = .;
	}
	__edata = .;

	/* Uninitialized data section */
	.bss :
	{
		 /* This is used by the startup in order to initialize the .bss section */
		. = ALIGN(4);
		__bss_start = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end = .;
	}

#if CONFIG_HEAP_BASE
	  ASSERT(. <= CONFIG_HEAP_BASE, "heap overlap with data")
	  . = CONFIG_HEAP_BASE;
#endif

	.heap :
	{
		. = ALIGN(8);
		__end__ = .;
		PROVIDE(end = .);
		. += HEAP_SIZE;
		__HeapLimit = .;
	}

#if CONFIG_STACKS_BASE
	. = CONFIG_STACKS_BASE;
#endif

	.stack :
	{
		. = ALIGN(8);
		. += STACK_SIZE;
	}

	__StackTop = STACKS_END;
	__StackLimit = __StackTop - STACK_SIZE;
	PROVIDE(__stack = __StackTop);

	.ARM.attributes 0 : { *(.ARM.attributes) }
}


