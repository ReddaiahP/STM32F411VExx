/* ==========================================================================
 * linker.ld - STM32F411VET6 (32F411EDISCOVERY)
 *   FLASH : 0x0800_0000 .. 0x0807_FFFF   (512 KB)
 *   SRAM  : 0x2000_0000 .. 0x2002_FFFF   (128 KB)
 *
 * The linker script answers three questions:
 *   1. Where do sections live in FLASH / SRAM?          -> MEMORY + SECTIONS
 *   2. How does the code know where they are?           -> the _sdata/_edata/... symbols
 *   3. What is the initial stack pointer?               -> _estack (read by startup.s)
 * ========================================================================== */

ENTRY(Reset_Handler)          /* the ELF entry point -> makes .elf debuggable/resettable */

/* Initial MSP value. The vector table's first word is set to this.
 * Top of RAM = 0x2000_0000 + 128K = 0x2002_0000  (8-byte aligned, as required) */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Room kept between the end of .bss and the initial stack, so the heap has
 * somewhere to grow when you start using malloc. Purely a safety net. */
_Min_Heap_Size  = 0x200;      /* 512 bytes  */
_Min_Stack_Size = 0x400;      /* 1 KB       */

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  /* ---------------------------------------------------------------- code --
   * Everything below lives in FLASH and is copied by the debugger/programmer.
   * Note: .data is an exception, see further down.                        */

  /* The interrupt vector table MUST be the very first thing in the image:
   * the CPU always fetches the initial SP from 0x0800_0000 and the reset
   * handler address from 0x0800_0004. KEEP() prevents --gc-sections from
   * throwing it away (nothing in C "references" it). */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)              /* your functions                                   */
    *(.text*)             /* compiler-generated bits (.text.main, ...)        */
    *(.glue_7)            /* ARM<->Thumb interworking veneers (not needed but */
    *(.glue_7t)           /* harmless, kept for reference toolchains)         */
    *(.eh_frame)
    KEEP(*(.init))
    KEEP(*(.fini))
    . = ALIGN(4);
    _etext = .;           /* end of code; handy symbol to watch in the map    */
  } >FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)            /* const / string literals                          */
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* Unwind tables. Unused in plain C, but C++ or -funwind-tables need them. */
  .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM       : { __exidx_start = .; *(.ARM.exidx*) __exidx_end = .; } >FLASH

  .preinit_array :
  {
    PROVIDE_HIDDEN(__preinit_array_start = .);
    KEEP(*(.preinit_array*))
    PROVIDE_HIDDEN(__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))    /* constructor functions, if you get C++ */
    KEEP(*(.init_array*))
    PROVIDE_HIDDEN(__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array*))
    PROVIDE_HIDDEN(__fini_array_end = .);
  } >FLASH

  /* ----------------------------------------------------------------- data --
   * Initialised globals, e.g.  uint32_t x = 5;
   * >RAM            = VMA: the variable is read/written at an address in SRAM
   * AT>FLASH        = LMA: its init value is stored in FLASH while power is off
   * Reset_Handler has to copy LMA -> VMA, which is exactly why _sidata exists. */
  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;           /* start of .data in SRAM                            */
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;           /* end   of .data in SRAM                            */
  } >RAM AT> FLASH

  /* ------------------------------------------------------------------ bss --
   * Uninitialised / zero-initialised globals. Occupies no FLASH at all;
   * Reset_Handler just writes zeros over it, because SRAM contents after a
   * power-up are undefined. */
  . = ALIGN(4);
  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM

  /* Heap grows up from here, stack grows down from _estack. */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE(end  = .);
    PROVIDE(_end = .);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* Junk the toolchain emits that has no business being in the image.
   * Deliberately narrow: do NOT discard libgcc.a/libc.a wholesale, you will
   * need those helpers once you add -lgcc or printf. */
  /DISCARD/ :
  {
    *(.comment)
    *(.note.gnu.build-id)
  }
}

