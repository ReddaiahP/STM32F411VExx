#ifndef INC_STM32F411_GPIO_H_
#define INC_STM32F411_GPIO_H_

#include "stm32f411_driver.h"


#define GPIO_PIN_SET     1
#define GPIO_PIN_CLEAR   0

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
    GPIO_PU,
    GPIO_PD
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
void GPIO_init(GPIO_Reg_Def_t *pGpiox, GPIO_PinConfig_t *pinConfig);
void GPIO_writePin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber, uint8_t value);
void GPIO_togglePin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber);
uint8_t GPIO_readPin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber);
void GPIO_writePort(GPIO_Reg_Def_t *pGpiox,uint16_t value);
uint16_t GPIO_readPort(GPIO_Reg_Def_t *pGpiox);
void Delay(uint32_t delay);

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t pinNumber);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQEnable(uint8_t IRQNumber);
void GPIO_IRQDisable(uint8_t IRQNumber);
void GPIO_IRQClearPending(uint8_t IRQNumber);
void GPIO_IRQSetPending(uint8_t IRQNumber);
void GPIO_IRQGetPending(uint8_t IRQNumber, uint8_t *pendingStatus);
void GPIO_IRQGetActive(uint8_t IRQNumber, uint8_t *activeStatus);
void GPIO_IRQGetPriority(uint8_t IRQNumber, uint32_t *IRQPriority);
void GPIO_IRQSetPriority(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQSetPriorityGrouping(uint32_t priorityGrouping);
void GPIO_IRQGetPriorityGrouping(uint32_t *priorityGrouping);

#endif 