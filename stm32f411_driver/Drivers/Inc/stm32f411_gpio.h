#ifndef INC_STM32F411_GPIO_H_
#define INC_STM32F411_GPIO_H_

#include "stm32f411_driver.h"

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



/* GPIO config Registers definitions */

typedef struct{
    uint8_t  pin;
    uint8_t  opMode;
    uint8_t  otype;
    uint8_t  speed;
    uint8_t  pupd;
    uint8_t  altFun;
} GPIO_PinConfig_t;


typedef enum{
    GPIO_PIN_NO_0 = 0,
    GPIO_PIN_NO_1,
    GPIO_PIN_NO_2,
    GPIO_PIN_NO_3,
    GPIO_PIN_NO_4,
    GPIO_PIN_NO_5,
    GPIO_PIN_NO_6,
    GPIO_PIN_NO_7,
    GPIO_PIN_NO_8,
    GPIO_PIN_NO_9,
    GPIO_PIN_NO_10,
    GPIO_PIN_NO_11,
    GPIO_PIN_NO_12,
    GPIO_PIN_NO_13,
    GPIO_PIN_NO_14,
    GPIO_PIN_NO_15
} GPIO_PinNumber_t;


typedef enum{
    GPIO_MODE_IN = 0,
    GPIO_MODE_OUT,
    GPIO_MODE_ALTFN,
    GPIO_MODE_ANALOG
} GPIO_Mode_t;


typedef enum{
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH,
    GPIO_SPEED_VERY_HIGH
} GPIO_Speed_t;


typedef enum{
    GPIO_NO_PUPD = 0,
    GPIO_PIN_PU,
    GPIO_PIN_PD
} GPIO_PuPd_t;



typedef enum{
    GPIO_OP_TYPE_PP = 0,
    GPIO_OP_TYPE_OD
} GPIO_OutputType_t;


typedef enum{
    GPIO_AF0 = 0,
    GPIO_AF1,
    GPIO_AF2,
    GPIO_AF3,
    GPIO_AF4,
    GPIO_AF5,
    GPIO_AF6,
    GPIO_AF7,
    GPIO_AF8,
    GPIO_AF9,
    GPIO_AF10,
    GPIO_AF11,
    GPIO_AF12,
    GPIO_AF13,
    GPIO_AF14,
    GPIO_AF15
} GPIO_AltFun_t;





/* Function prototypes */
void GPIO_Init(GPIO_Reg_Def_t *pGpiox, GPIO_PinConfig_t *pinConfig);


#endif 