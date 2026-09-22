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


/* GPIO register definition */

typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];

} GPIO_Reg_Def_t;


/* GPIO peripheral definitions */

#define GPIOA    ((volatile GPIO_Reg_Def_t *)GPIOA_BASE)
#define GPIOB    ((volatile GPIO_Reg_Def_t *)GPIOB_BASE)
#define GPIOC    ((volatile GPIO_Reg_Def_t *)GPIOC_BASE)
#define GPIOD    ((volatile GPIO_Reg_Def_t *)GPIOD_BASE)
#define GPIOE    ((volatile GPIO_Reg_Def_t *)GPIOE_BASE)


/* RCC register definition */

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;

    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;

    volatile uint32_t RESV0[2];

    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;

    volatile uint32_t RESV1[2];

    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;

    volatile uint32_t RESV2[2];

    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;

    volatile uint32_t RESV3[2];

    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;

    volatile uint32_t RESV4[2];

    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;

    volatile uint32_t RESV5[2];

    volatile uint32_t BDCR;
    volatile uint32_t CSR;

    volatile uint32_t RESV6[2];

    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;

    volatile uint32_t RESV7;
    volatile uint32_t DCKCFGR;

} Rcc_Reg_Def_t;


/* RCC peripheral definition */

#define RCC    ((volatile Rcc_Reg_Def_t *)RCC_BASE)


#endif