/* GCC Linker script for ATSAMR21G18A */

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SEARCH_DIR(.)

/* Memory Spaces Definitions */
MEMORY
{
  /* NVM layout */
  BOOT   (rx)   : ORIGIN = 0x00000000, LENGTH = 8K
  FLASH  (rx)   : ORIGIN = 0x00002000, LENGTH = 244K
  EEPROM (rw!x) : ORIGIN = 0x0003F000, LENGTH = 4K

  /* SRAM layout */
  RAM    (rw)   : ORIGIN = 0x20000000, LENGTH = 32K
}

ENTRY(__vector_table)

/* Size of single Main Stack used by the application. Process Stack is not used. */
MAIN_STACK_SIZE     = 3K;
PROCESS_STACK_SIZE  = 0;

SECTIONS
{
  /* Code */
   .text :
  {
    __text = .;

    KEEP(*(.vectors)) /* Cortex-M0+ initial vectors table. Should be placed at the beginning of flash. */

    /* PDS NV memory section */
    . = ALIGN(0x2100);
    PROVIDE(__d_nv_mem_start = .);
    . = ALIGN(0x6100); /* Size of D_Nv memory section is 0x4000 i.e., 16KB */
    PROVIDE(__d_nv_mem_end = .);

    /* Non-volatile file system PDS_FF section */
    PROVIDE(__pds_ff_start = .);
    KEEP(*(.pds_ff))
    PROVIDE(__pds_ff_end = .);

    /* Non-volatile file system PDS_FD section */
    PROVIDE(__pds_fd_start = .);
    KEEP(*(.pds_fd))
    PROVIDE(__pds_fd_end = .);

    *(.text*main) /* text.main (if not optimized) or text.startup.main (if optimized) */
    *(.text)
    *(.text*)
    *(.gnu.linkonce.t.*)
    *(.rodata)              /* read-only data (constants) */
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(4);
    __text_end = .;
  } > FLASH

  /* Non-zero initialized data */
  .data :
  {
    __data_load = LOADADDR(.data);
    __data = .;
    *(.ramvectors) /* Real vectors table. Placed at the beginning of RAM to ease alignment requirements. */
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(4);
    __data_end = .;
  } >RAM AT>FLASH

  . = ALIGN(4);
  _etext = .;

  .relocate : AT (_etext)
  {
      . = ALIGN(4);
      _srelocate = .;
      *(.ramfunc .ramfunc.*);
      *(.data .data.*);
      . = ALIGN(4);
      _erelocate = .;
  } > RAM

  /* Zero-initialized data */
  .bss (NOLOAD) :
  {
    __bss = .;
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
  } >RAM

  /* Stacks. The EABI requires the stack be 8-byte aligned. */
  .stack ALIGN(8):
  {
    __stack_bottom = .;
    __process_stack_bottom = .;

    . += MAIN_STACK_SIZE;
    . = ALIGN(8);

    __process_stack_top = .;
    __main_stack_bottom = .;

    . += PROCESS_STACK_SIZE;
    . = ALIGN(8);

    __main_stack_top = .;
    __stack_top = .;
  } >RAM

  __end = .;

  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
}
