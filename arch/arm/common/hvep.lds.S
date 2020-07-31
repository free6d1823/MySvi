#include <target/memory.h>

/* Entry Point */
ENTRY(Start)

/* Define output sections */
SECTIONS
{
	. = SVI_TEXT_BASE;
	/* The startup code goes first into internal flash */
	.interrupts :
	{
		. = ALIGN(4);
		KEEP(*(VECTORS))	/* Startup code */
		*(RESET)
		. = ALIGN(4);
	}

	__stext = .;
	/* The program code and other data goes into internal flash */
	.text :
	{
		. = ALIGN(4);
		*(.text)		/* .text sections (code) */
		*(.text*)		/* .text* sections (code) */
		*(*.text)		/* .text sections (code) */
		*(.glue_7)		/* glue arm to thumb code */
		*(.glue_7t)		/* glue thumb to arm code */
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

	.ARM :
	{
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	}

	. = ALIGN(PAGE_SIZE);
	__etext = .;

	__sdata = .;
	.data :
	{
		__data_start = .;
		*(.data .data.*)
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
}
