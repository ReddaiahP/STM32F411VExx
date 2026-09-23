#ifndef STM32F411_RCC_H_
#define STM32F411_RCC_H_

#include "stm32f411_driver.h"



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


/* GPIO Peripheral Clock Enable */

#define GPIOA_PCLK_EN()    (RCC->AHB1ENR |= (1U << 0))
#define GPIOB_PCLK_EN()    (RCC->AHB1ENR |= (1U << 1))
#define GPIOC_PCLK_EN()    (RCC->AHB1ENR |= (1U << 2))
#define GPIOD_PCLK_EN()    (RCC->AHB1ENR |= (1U << 3))
#define GPIOE_PCLK_EN()    (RCC->AHB1ENR |= (1U << 4))


/* GPIO Peripheral Clock Disable */

#define GPIOA_PCLK_DI()    (RCC->AHB1ENR &= ~(1U << 0))
#define GPIOB_PCLK_DI()    (RCC->AHB1ENR &= ~(1U << 1))
#define GPIOC_PCLK_DI()    (RCC->AHB1ENR &= ~(1U << 2))
#define GPIOD_PCLK_DI()    (RCC->AHB1ENR &= ~(1U << 3))
#define GPIOE_PCLK_DI()    (RCC->AHB1ENR &= ~(1U << 4))


/* GPIO Peripheral Reset */

#define GPIOA_PREG_RST()   do{(RCC->AHB1RSTR |= (1U << 0)); (RCC->AHB1RSTR &= ~(1U << 0));} while(0)
#define GPIOB_PREG_RST()   do{(RCC->AHB1RSTR |= (1U << 1)); (RCC->AHB1RSTR &= ~(1U << 1));} while(0)
#define GPIOC_PREG_RST()   do{(RCC->AHB1RSTR |= (1U << 2)); (RCC->AHB1RSTR &= ~(1U << 2));} while(0)
#define GPIOD_PREG_RST()   do{(RCC->AHB1RSTR |= (1U << 3)); (RCC->AHB1RSTR &= ~(1U << 3));} while(0)
#define GPIOE_PREG_RST()   do{(RCC->AHB1RSTR |= (1U << 4)); (RCC->AHB1RSTR &= ~(1U << 4));} while(0)


#endif