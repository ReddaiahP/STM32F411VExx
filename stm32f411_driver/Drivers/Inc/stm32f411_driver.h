#ifndef STM32F411_DRIVER_H_
#define STM32F411_DRIVER_H_

#include <stdint.h>


/* Peripheral base addresses */

#define PERIPH_BASE       0x40000000UL
#define APB1PERIPH_BASE   0x40000000UL
#define APB2PERIPH_BASE   0x40010000UL
#define AHB1PERIPH_BASE   0x40020000UL
#define AHB2PERIPH_BASE   0x50000000UL


/* GPIO base addresses */

#define GPIOA_BASE    (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE    (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE    (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE    (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE    (AHB1PERIPH_BASE + 0x1000UL)

#define RCC_BASE      (AHB1PERIPH_BASE + 0x3800UL)

#define EXTI_BASE      (APB2PERIPH_BASE + 0x3C00UL)
#define SYSCFG_BASE    (APB2PERIPH_BASE + 0x3800UL)


#define NVIC_BASE   ((volatile uint32_t *)0xE000E100UL)

typedef struct{
    volatile uint32_t ISER[8];
    volatile uint32_t RESERVED0[24]; // Reserved space to align with the NVIC register layout 0x120-10x80 = 0x60 bytes, 0x60/4 = 24 here 4 because each uint32_t is 4 bytes
    volatile uint32_t ICER[8];
    volatile uint32_t RESERVED1[24]; // Reserved space to align with the NVIC register layout
    volatile uint32_t ISPR[8];
    volatile uint32_t RESERVED2[24]; // Reserved space to align with the NVIC register layout
    volatile uint32_t ICPR[8];
    volatile uint32_t RESERVED3[24]; // Reserved space to align with the NVIC register layout
    volatile uint32_t IABR[8];
    volatile uint32_t RESERVED4[56]; // Reserved space to align with the NVIC register layout
    volatile uint32_t IPR[60];
    volatile uint32_t RESERVED5[580]; // Reserved space to align with the NVIC register layout
    volatile uint32_t STIR;
}NVIC_Reg_Def_t;


#define NVIC    ((NVIC_Reg_Def_t *)NVIC_BASE)

#endif