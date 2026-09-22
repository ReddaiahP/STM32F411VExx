#ifndef STM32F411_RCC_H_
#define STM32F411_RCC_H_

#include "stm32f411_driver.h"


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

#define GPIOA_PREG_RST()   (RCC->AHB1RSTR |= (1U << 0))
#define GPIOB_PREG_RST()   (RCC->AHB1RSTR |= (1U << 1))
#define GPIOC_PREG_RST()   (RCC->AHB1RSTR |= (1U << 2))
#define GPIOD_PREG_RST()   (RCC->AHB1RSTR |= (1U << 3))
#define GPIOE_PREG_RST()   (RCC->AHB1RSTR |= (1U << 4))


#endif