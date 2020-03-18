#include <target/memory.h>

/* Entry Point */
ENTRY(Start)

_HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x1000;
_STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x4000;

/* Specify the memory areas */
MEMORY
{
  m_interrupts          (RX)  : ORIGIN = R52_RAM_BASE, LENGTH = 0x00000400
  m_text                (RX)  : ORIGIN = R52_RAM_BASE+0x00000400, LENGTH = 0x00010000
  m_data                (RW)  : ORIGIN = R52_RAM_BASE+0x00020000, LENGTH = 0x00040000
}

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into internal flash */
  .interrupts :
  {
    . = ALIGN(4);
    KEEP(*(VECTORS))     /* Startup code */
    . = ALIGN(4);
  } > m_interrupts
  
/* The program code and other data goes into internal flash */
  .text :
  {
    . = ALIGN(4);
    __stext = .;
    *(.text)                 /* .text sections (code) */
    *(.text*)                /* .text* sections (code) */
    *(.rodata)               /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
    __etext = .;
  } > m_text

  .cmd_array : {
    __cmd_array_start = .;
    KEEP (*(SORT(.cmd_array.*)))
    __cmd_array_end = .;
  } > m_text

  .test_array : {
    __testfn_start = .;
    KEEP (*(.testfn))
    __testfn_end = .;
  } > m_text
  
  .data :
  {
    . = ALIGN(4);
    __sdata = .;
    *(.data)                 /* .data sections */
    *(.data*)                /* .data* sections */
    . = ALIGN(4);
    __edata = .;
  } > m_data

/* Uninitialized data section */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    . = ALIGN(BSS_ALIGN);
    __bss_start = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(BSS_ALIGN);
    __bss_end = .;
  } > m_data

  .stack :
  {
    . = ALIGN(8);
    . += _STACK_SIZE;
  } > m_data

  /* Initializes stack on the end of block */
  __StackTop   = ORIGIN(m_data) + LENGTH(m_data);
  __StackLimit = __StackTop - _STACK_SIZE;

}
