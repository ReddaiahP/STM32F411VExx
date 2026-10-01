#ifndef STM32F411_GPIO_H_
#define STM32F411_GPIO_H_

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


typedef enum{
    IRQ_NO_EXTI0 = 6,
    IRQ_NO_EXTI1 = 7,
    IRQ_NO_EXTI2 = 8,
    IRQ_NO_EXTI3 = 9,
    IRQ_NO_EXTI4 = 10,
    IRQ_NO_EXTI9_5 = 23,
    IRQ_NO_EXTI15_10 = 40
} IRQ_Number_t;

typedef enum{
    PORT_CODE_GPIOA = 0,
    PORT_CODE_GPIOB,
    PORT_CODE_GPIOC,
    PORT_CODE_GPIOD,
    PORT_CODE_GPIOE
}PortCode_Exti_t;



/* Interrupt registers */
typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;

} Exti_Reg_Def_t;


typedef struct{
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    volatile uint32_t RESV0[2];
    volatile uint32_t CMPCR;
}SYSCFG_Reg_Def_t;



/* NVIC Definitions */


typedef struct{
    volatile uint32_t ISER[8];
    volatile uint32_t RESERVED0[24]; // Reserved space to align with the NVIC register layout 0x120-0x80 = 0x60 bytes, 0x60/4 = 24 here 4 because each uint32_t is 4 bytes
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






/* GPIO peripheral definitions */

#define GPIOA    ((GPIO_Reg_Def_t *)GPIOA_BASE)
#define GPIOB    ((GPIO_Reg_Def_t *)GPIOB_BASE)
#define GPIOC    ((GPIO_Reg_Def_t *)GPIOC_BASE)
#define GPIOD    ((GPIO_Reg_Def_t *)GPIOD_BASE)
#define GPIOE    ((GPIO_Reg_Def_t *)GPIOE_BASE)


/* Related to Interrupts definition */

#define EXTI    ((Exti_Reg_Def_t *)EXTI_BASE)
#define NVIC    ((NVIC_Reg_Def_t *)NVIC_BASE)
#define SYSCFG  ((SYSCFG_Reg_Def_t *)SYSCFG_BASE)








/* Function prototypes */
void GPIO_init(GPIO_Reg_Def_t *pGpiox, GPIO_PinConfig_t *pinConfig);
void GPIO_writePin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber, uint8_t value);
void GPIO_togglePin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber);
uint8_t GPIO_readPin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber);
void GPIO_writePort(GPIO_Reg_Def_t *pGpiox,uint16_t value);
uint16_t GPIO_readPort(GPIO_Reg_Def_t *pGpiox);
void GPIO_bssrPin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber, uint8_t value);
void Delay(uint32_t delay);
void NVIC_enableIRQ(uint8_t IRQNumber);
void NVIC_disableIRQ(uint8_t IRQNumber);
void SYSCFG_enableEXTI(uint8_t portCode, uint8_t pinNumber);


#endif 