#include <target/memory.h>

ENTRY(Reset_Handler)

/* A simple memory map */
/*		*
 *		*
 *		*
 -------------	SVI_TEXT_BASE
 *		*
 *		*	interrupts + text + data + bss
 *		*
 -------------	SVI_DATA_BASE
 *		*
 *		*	data + bss
 *		*
 -------------	HEAP_START if not specified
 *		*
 *		*	heap
 *		*
  -------------	STACK_START if not specified
 *		*
 *		*	STACKs
 *		*
 -------------	SVI_RAM_END
 */

SECTIONS
{
	. = SVI_TEXT_BASE;
	/* The startup code goes first into internal flash */
	.interrupts :
	{
		__VECTOR_TABLE = .;
		. = ALIGN(4);
		KEEP(*(.isr_vector))     /* Startup code */
		. = ALIGN(4);
	}

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

	.ARM :
	{
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	}

	__etext = .;

	__sdata = .;
	.data :
	{
		__data_start = .;
		*(.data .data.*)
		KEEP(*(.jcr*))
		. = ALIGN(4);
		__data_end = .;
	}

#ifndef CONFIG_BSS_IN_DATA
	.bss (NOLOAD) : ALIGN(BSS_ALIGN) {
#else
	.data : ALIGN(BSS_ALIGN) {
#endif
	__bss_start = .;
	*(.bss)
	*(.bss*)
	*(COMMON)
	. = ALIGN(BSS_ALIGN);
	__bss_end = .;
	}

	. = ALIGN(PAGE_SIZE);
	__edata = .;

	__StackTop = STACKS_END;

	.ARM.attributes 0 : { *(.ARM.attributes) }
}


