/* ==========================================================================
 * startup.s - STM32F411VET6 vector table + reset handler
 *
 *   There is no C runtime here: this file is *everything* the CPU needs
 *   to get from power-on to your main().
 *
 *   '@' is the GNU-as comment character for ARM (safe with or without the
 *   C preprocessor). Keep it that way: if you ever rename this file to
 *   startup.S, '#' would become a preprocessor directive and would break
 *   things like  movs r0, #0  placed at the start of a line.
 *
 *   Matches:  KEEP(*(.isr_vector))  in linker.ld
 * ========================================================================== */

  .syntax unified        @ unified (Thumb-2) instruction syntax
  .cpu cortex-m4
  .fpu softvfp           @ matches -mfloat-abi=soft; change to fpv4-sp-d16 with hard float
  .thumb

  .global g_pfnVectors
  .global Reset_Handler

/* --------------------------------------------------------------------------
 * Every peripheral vector is a WEAK alias of Default_Handler.
 * When you write the real handler in C, e.g.
 *     void SysTick_Handler(void) { ... }
 *     void EXTI0_IRQHandler(void) { ... }
 * the linker picks YOUR symbol, because a strong definition always beats a
 * weak one. That is the only reason you never have to touch this file again.
 * -------------------------------------------------------------------------- */
.macro IRQ_DEFAULT handler
  .weak      \handler
  .thumb_set \handler, Default_Handler
.endm

/* --------------------------------------------------------------------------
 * Interrupt vector table
 *   word 0 : initial main stack pointer  (loaded by the CPU itself)
 *   word 1 : Reset_Handler address, bit0 must be 1 (= Thumb state)
 *   word 2+: 15 core exception vectors, then 86 peripheral IRQs
 * Order and names below come straight from RM0383 Table 37 (p.202-204).
 * Reserved slots are 0; an IRQ that can never fire, so nothing to catch.
 * -------------------------------------------------------------------------- */
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
g_pfnVectors:
  .word _estack                 /* 0x00  initial SP  = 0x20020000             */
  .word Reset_Handler           /* 0x04  reset: CPU starts here               */
  .word NMI_Handler             /* 0x08                                       */
  .word HardFault_Handler       /* 0x0C  all faults land here unless you fix them */
  .word MemManage_Handler       /* 0x10                                       */
  .word BusFault_Handler        /* 0x14                                       */
  .word UsageFault_Handler      /* 0x18                                       */
  .word 0                       /* 0x1C  reserved                             */
  .word 0                       /* 0x20  reserved                             */
  .word 0                       /* 0x24  reserved                             */
  .word 0                       /* 0x28  reserved                             */
  .word SVC_Handler             /* 0x2C                                       */
  .word DebugMon_Handler        /* 0x30                                       */
  .word 0                       /* 0x34  reserved                             */
  .word PendSV_Handler          /* 0x38                                       */
  .word SysTick_Handler         /* 0x3C  -> Step 5: your SysTick_Handler(void) */

  /* ---- peripheral interrupts, RM0383 Table 37; the comment is the IRQ number ---- */
  .word WWDG_IRQHandler             /* 0  */
  .word PVD_IRQHandler              /* 1  */
  .word TAMP_STAMP_IRQHandler       /* 2  */
  .word RTC_WKUP_IRQHandler         /* 3  */
  .word FLASH_IRQHandler            /* 4  */
  .word RCC_IRQHandler              /* 5  */
  .word EXTI0_IRQHandler            /* 6   <- Step 6: user button PA0          */
  .word EXTI1_IRQHandler            /* 7  */
  .word EXTI2_IRQHandler            /* 8  */
  .word EXTI3_IRQHandler            /* 9  */
  .word EXTI4_IRQHandler            /* 10 */
  .word DMA1_Stream0_IRQHandler     /* 11 */
  .word DMA1_Stream1_IRQHandler     /* 12 */
  .word DMA1_Stream2_IRQHandler     /* 13 */
  .word DMA1_Stream3_IRQHandler     /* 14 */
  .word DMA1_Stream4_IRQHandler     /* 15 */
  .word DMA1_Stream5_IRQHandler     /* 16 */
  .word DMA1_Stream6_IRQHandler     /* 17 */
  .word ADC_IRQHandler              /* 18 */
  .word 0                           /* 19  reserved */
  .word 0                           /* 20  reserved */
  .word 0                           /* 21  reserved */
  .word 0                           /* 22  reserved */
  .word EXTI9_5_IRQHandler          /* 23 */
  .word TIM1_BRK_TIM9_IRQHandler    /* 24 */
  .word TIM1_UP_TIM10_IRQHandler    /* 25 */
  .word TIM1_TRG_COM_TIM11_IRQHandler /* 26 */
  .word TIM1_CC_IRQHandler          /* 27 */
  .word TIM2_IRQHandler             /* 28 */
  .word TIM3_IRQHandler             /* 29 */
  .word TIM4_IRQHandler             /* 30  <- Step 9: PD12..PD15 PWM         */
  .word I2C1_EV_IRQHandler          /* 31 */
  .word I2C1_ER_IRQHandler          /* 32 */
  .word I2C2_EV_IRQHandler          /* 33 */
  .word I2C2_ER_IRQHandler          /* 34 */
  .word SPI1_IRQHandler             /* 35  <- Step 10: on-board sensors      */
  .word SPI2_IRQHandler             /* 36 */
  .word USART1_IRQHandler           /* 37 */
  .word USART2_IRQHandler           /* 38  <- Step 7: ST-LINK VCP console    */
  .word 0                           /* 39  reserved */
  .word EXTI15_10_IRQHandler        /* 40 */
  .word RTC_Alarm_IRQHandler        /* 41 */
  .word OTG_FS_WKUP_IRQHandler      /* 42 */
  .word 0                           /* 43  reserved */
  .word 0                           /* 44  reserved */
  .word 0                           /* 45  reserved */
  .word 0                           /* 46  reserved */
  .word DMA1_Stream7_IRQHandler     /* 47 */
  .word 0                           /* 48  reserved */
  .word SDIO_IRQHandler             /* 49 */
  .word TIM5_IRQHandler             /* 50 */
  .word SPI3_IRQHandler             /* 51 */
  .word 0                           /* 52  reserved */
  .word 0                           /* 53  reserved */
  .word 0                           /* 54  reserved */
  .word 0                           /* 55  reserved */
  .word DMA2_Stream0_IRQHandler     /* 56  (note the gap: not 52!) */
  .word DMA2_Stream1_IRQHandler     /* 57 */
  .word DMA2_Stream2_IRQHandler     /* 58 */
  .word DMA2_Stream3_IRQHandler     /* 59 */
  .word DMA2_Stream4_IRQHandler     /* 60 */
  .word 0                           /* 61  reserved */
  .word 0                           /* 62  reserved */
  .word 0                           /* 63  reserved */
  .word 0                           /* 64  reserved */
  .word 0                           /* 65  reserved */
  .word 0                           /* 66  reserved */
  .word OTG_FS_IRQHandler           /* 67 */
  .word DMA2_Stream5_IRQHandler     /* 68 */
  .word DMA2_Stream6_IRQHandler     /* 69 */
  .word DMA2_Stream7_IRQHandler     /* 70 */
  .word USART6_IRQHandler           /* 71 */
  .word I2C3_EV_IRQHandler          /* 72 */
  .word I2C3_ER_IRQHandler          /* 73 */
  .word 0                           /* 74  reserved */
  .word 0                           /* 75  reserved */
  .word 0                           /* 76  reserved */
  .word 0                           /* 77  reserved */
  .word 0                           /* 78  reserved */
  .word 0                           /* 79  reserved */
  .word 0                           /* 80  reserved */
  .word FPU_IRQHandler              /* 81  F411 has an FPU interrupt */
  .word 0                           /* 82  reserved */
  .word 0                           /* 83  reserved */
  .word SPI4_IRQHandler             /* 84 */
  .word SPI5_IRQHandler             /* 85  <- last one */


  .size g_pfnVectors, .-g_pfnVectors

/* --------------------------------------------------------------------------
 * Weak aliases for the CORE exceptions (same mechanism as IRQ_DEFAULT, but
 * spelled out so you can see exactly what the macro expands to):
 *     .weak X    -> X may be defined elsewhere without a duplicate-symbol error
 *     .thumb_set -> X points at the same address as Default_Handler, and
 *                   stays in Thumb state
 * -------------------------------------------------------------------------- */
  .weak      NMI_Handler
  .thumb_set NMI_Handler, Default_Handler
  .weak      HardFault_Handler
  .thumb_set HardFault_Handler, Default_Handler
  .weak      MemManage_Handler
  .thumb_set MemManage_Handler, Default_Handler
  .weak      BusFault_Handler
  .thumb_set BusFault_Handler, Default_Handler
  .weak      UsageFault_Handler
  .thumb_set UsageFault_Handler, Default_Handler
  .weak      SVC_Handler
  .thumb_set SVC_Handler, Default_Handler
  .weak      DebugMon_Handler
  .thumb_set DebugMon_Handler, Default_Handler
  .weak      PendSV_Handler
  .thumb_set PendSV_Handler, Default_Handler
  .weak      SysTick_Handler
  .thumb_set SysTick_Handler, Default_Handler

/* --------------------------------------------------------------------------
 * Weak aliases for the 57 named peripheral IRQs (IRQ 0..85 from Table 37).
 * Reserved slots in the vector table are 0 and have no handler here.
 * -------------------------------------------------------------------------- */
  IRQ_DEFAULT WWDG_IRQHandler                 /* 0  */
  IRQ_DEFAULT PVD_IRQHandler                  /* 1  */
  IRQ_DEFAULT TAMP_STAMP_IRQHandler           /* 2  */
  IRQ_DEFAULT RTC_WKUP_IRQHandler             /* 3  */
  IRQ_DEFAULT FLASH_IRQHandler                /* 4  */
  IRQ_DEFAULT RCC_IRQHandler                  /* 5  */
  IRQ_DEFAULT EXTI0_IRQHandler                /* 6  */
  IRQ_DEFAULT EXTI1_IRQHandler                /* 7  */
  IRQ_DEFAULT EXTI2_IRQHandler                /* 8  */
  IRQ_DEFAULT EXTI3_IRQHandler                /* 9  */
  IRQ_DEFAULT EXTI4_IRQHandler                /* 10 */
  IRQ_DEFAULT DMA1_Stream0_IRQHandler         /* 11 */
  IRQ_DEFAULT DMA1_Stream1_IRQHandler         /* 12 */
  IRQ_DEFAULT DMA1_Stream2_IRQHandler         /* 13 */
  IRQ_DEFAULT DMA1_Stream3_IRQHandler         /* 14 */
  IRQ_DEFAULT DMA1_Stream4_IRQHandler         /* 15 */
  IRQ_DEFAULT DMA1_Stream5_IRQHandler         /* 16 */
  IRQ_DEFAULT DMA1_Stream6_IRQHandler         /* 17 */
  IRQ_DEFAULT ADC_IRQHandler                  /* 18 */
  IRQ_DEFAULT EXTI9_5_IRQHandler              /* 23 */
  IRQ_DEFAULT TIM1_BRK_TIM9_IRQHandler        /* 24 */
  IRQ_DEFAULT TIM1_UP_TIM10_IRQHandler        /* 25 */
  IRQ_DEFAULT TIM1_TRG_COM_TIM11_IRQHandler   /* 26 */
  IRQ_DEFAULT TIM1_CC_IRQHandler              /* 27 */
  IRQ_DEFAULT TIM2_IRQHandler                 /* 28 */
  IRQ_DEFAULT TIM3_IRQHandler                 /* 29 */
  IRQ_DEFAULT TIM4_IRQHandler                 /* 30 */
  IRQ_DEFAULT I2C1_EV_IRQHandler              /* 31 */
  IRQ_DEFAULT I2C1_ER_IRQHandler              /* 32 */
  IRQ_DEFAULT I2C2_EV_IRQHandler              /* 33 */
  IRQ_DEFAULT I2C2_ER_IRQHandler              /* 34 */
  IRQ_DEFAULT SPI1_IRQHandler                 /* 35 */
  IRQ_DEFAULT SPI2_IRQHandler                 /* 36 */
  IRQ_DEFAULT USART1_IRQHandler               /* 37 */
  IRQ_DEFAULT USART2_IRQHandler               /* 38 */
  IRQ_DEFAULT EXTI15_10_IRQHandler            /* 40 */
  IRQ_DEFAULT RTC_Alarm_IRQHandler            /* 41 */
  IRQ_DEFAULT OTG_FS_WKUP_IRQHandler          /* 42 */
  IRQ_DEFAULT DMA1_Stream7_IRQHandler         /* 47 */
  IRQ_DEFAULT SDIO_IRQHandler                 /* 49 */
  IRQ_DEFAULT TIM5_IRQHandler                 /* 50 */
  IRQ_DEFAULT SPI3_IRQHandler                 /* 51 */
  IRQ_DEFAULT DMA2_Stream0_IRQHandler         /* 56 */
  IRQ_DEFAULT DMA2_Stream1_IRQHandler         /* 57 */
  IRQ_DEFAULT DMA2_Stream2_IRQHandler         /* 58 */
  IRQ_DEFAULT DMA2_Stream3_IRQHandler         /* 59 */
  IRQ_DEFAULT DMA2_Stream4_IRQHandler         /* 60 */
  IRQ_DEFAULT OTG_FS_IRQHandler               /* 67 */
  IRQ_DEFAULT DMA2_Stream5_IRQHandler         /* 68 */
  IRQ_DEFAULT DMA2_Stream6_IRQHandler         /* 69 */
  IRQ_DEFAULT DMA2_Stream7_IRQHandler         /* 70 */
  IRQ_DEFAULT USART6_IRQHandler               /* 71 */
  IRQ_DEFAULT I2C3_EV_IRQHandler              /* 72 */
  IRQ_DEFAULT I2C3_ER_IRQHandler              /* 73 */
  IRQ_DEFAULT FPU_IRQHandler                  /* 81 */
  IRQ_DEFAULT SPI4_IRQHandler                 /* 84 */
  IRQ_DEFAULT SPI5_IRQHandler                 /* 85 */

/* ==========================================================================
 * Reset_Handler - the first code that runs (vector word 1, address 0x08000004)
 *
 * State when it is entered:
 *   - MSP is already loaded from vector word 0 by the hardware: nothing to do
 *   - .data exists only in FLASH; its SRAM copy holds garbage
 *   - .bss holds garbage too (SRAM contents are undefined after power-up)
 * So the job is: copy .data FLASH->SRAM, zero .bss, then call main().
 * ========================================================================== */
  .section .text.Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
  /* --- if you ever switch the Makefile to -mfloat-abi=hard, enable the FPU
   *     BEFORE any float instruction, or the first one raises UsageFault:
   *       ldr r0, =0xE000ED88        @ CPACR
   *       ldr r1, [r0]
   *       orr r1, r1, #(0xF << 20)   @ CP10 and CP11 full access
   *       str r1, [r0]
   *       dsb
   *       isb
   *     With -mfloat-abi=soft none of this is needed.                    --- */

  /* ---- 1. copy initialised data: FLASH(_sidata) -> SRAM(_sdata .. _edata) --- */
  ldr  r0, =_sdata               @ destination start (VMA, in SRAM)
  ldr  r1, =_edata               @ destination end
  ldr  r2, =_sidata              @ source start (LMA, in FLASH)
  movs r3, #0                    @ byte offset
  b    .Lcopy_test
.Lcopy_body:
  ldr  r4, [r2, r3]              @ read 4 bytes from FLASH
  str  r4, [r0, r3]              @ write them into SRAM
  adds r3, r3, #4
.Lcopy_test:
  adds r4, r0, r3
  cmp  r4, r1
  bcc  .Lcopy_body               @ bcc = unsigned "lower than" -> still more to copy

  /* ---- 2. zero .bss: _sbss .. _ebss ---- */
  ldr  r2, =_sbss
  ldr  r4, =_ebss
  movs r3, #0
  b    .Lzero_test
.Lzero_body:
  str  r3, [r2]
  adds r2, r2, #4
.Lzero_test:
  cmp  r2, r4
  bcc  .Lzero_body

  /* ---- 3. into C ---- */
  bl   main
  b    .                         @ main() must never return; if it does, park here
  .size Reset_Handler, .-Reset_Handler

/* ==========================================================================
 * Default_Handler - catch-all target for every vector you have not written yet.
 * When something unexplainable happens you will usually find GDB sitting here.
 * To find out WHICH interrupt fired, read IPSR (bottom 9 bits of xPSR):
 *     (gdb) p/x $xpsr & 0x1ff          -> 0 = thread mode, else the vector number
 * and if it is a fault, also read:
 *     (gdb) p/x *(unsigned*)0xE000ED28  @ CFSR  (which fault)
 *     (gdb) p/x *(unsigned*)0xE000ED2C  @ HFSR  (escalated to hard fault)
 * ========================================================================== */
  .section .text.Default_Handler,"ax",%progbits
  .type  Default_Handler, %function
Default_Handler:
  b    .                         @ spin here - put a breakpoint on this line
  .size Default_Handler, .-Default_Handler

  .end



