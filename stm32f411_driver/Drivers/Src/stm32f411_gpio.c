#include "stm32f411_gpio.h"



void GPIO_init(GPIO_Reg_Def_t *pGpiox, GPIO_PinConfig_t *pinConfig){
    uint32_t temp = 0;

    /* Moder config */
    temp = pinConfig->opMode << (2*pinConfig->pin);
    pGpiox->MODER &= ~(0x3 << (2*pinConfig->pin));
    pGpiox->MODER |= temp;

    /* Output otype config push pull */
    temp = 0;
    temp = pinConfig->otype << (pinConfig->pin);
    pGpiox->OTYPER &= ~(0x1 << (pinConfig->pin));
    pGpiox->OTYPER |= temp;


    /* Output speed config */
    temp = 0;
    temp = pinConfig->speed << (2*pinConfig->pin);    
    pGpiox->OSPEEDR &= ~(0x3 << (2*pinConfig->pin));
    pGpiox->OSPEEDR |= temp;



    /* Pull-up/pull-down config */
    temp = 0;
    temp = pinConfig->pupd << (2*pinConfig->pin);
    pGpiox->PUPDR &= ~(0x3 << (2*pinConfig->pin));
    pGpiox->PUPDR |= temp;
    

    /* Alternate function config */
    if(pinConfig->opMode == GPIO_MODE_ALTFN){
        uint8_t afrIndex = pinConfig->pin / 8;
        uint8_t afrPosition = pinConfig->pin % 8;
        temp = 0;
        temp = pinConfig->altFun << (4*afrPosition);
        pGpiox->AFR[afrIndex] &= ~(0xF << (4*afrPosition));
        pGpiox->AFR[afrIndex] |= temp;

    }
}

void GPIO_writePin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber, uint8_t value){

    if(value == GPIO_PIN_SET){
        pGpiox->ODR |= (1 << pinNumber);
    }else if(value == GPIO_PIN_CLEAR){
        pGpiox->ODR &= ~(1 << pinNumber);
    }
}

void Delay(uint32_t delay){
    for(uint32_t i = 0; i < delay; i++);
}


uint8_t GPIO_readPin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber){
    
    uint8_t value = (pGpiox->IDR >> pinNumber) & 0x1;
    return value;
}

void GPIO_togglePin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber){
    pGpiox->ODR ^= (1 << pinNumber);
}


void GPIO_bssrPin(GPIO_Reg_Def_t *pGpiox,uint8_t pinNumber, uint8_t value){
    if(value == GPIO_PIN_SET){
        pGpiox->BSRR = (1 << pinNumber);
    }else if(value == GPIO_PIN_CLEAR){
        pGpiox->BSRR = (1 << (pinNumber + 16));
    }
}


void NVIC_enableIRQ(uint8_t IRQNumber){
    uint8_t registerIndex = IRQNumber / 32;
    uint8_t bitPosition = IRQNumber % 32;
    NVIC->ISER[registerIndex] = (1 << bitPosition);
}

void NVIC_disableIRQ(uint8_t IRQNumber){
    uint8_t registerIndex = IRQNumber / 32;
    uint8_t bitPosition = IRQNumber % 32;
    NVIC->ICER[registerIndex] = (1 << bitPosition);
}


void SYSCFG_enableEXTI(uint8_t portCodeExti, uint8_t pinNumber){
    uint8_t extiIndex = pinNumber / 4;
    uint8_t extiPosition = pinNumber % 4;
    SYSCFG->EXTICR[extiIndex] &= ~(0xF << (4*extiPosition));
    SYSCFG->EXTICR[extiIndex] |= (portCodeExti << (4*extiPosition));
}


void EXTI_enableIRQ(uint8_t pinNumber){
    EXTI->IMR |= (1 << pinNumber);
}

void EXTI_disableIRQ(uint8_t pinNumber){
    EXTI->IMR &= ~(1 << pinNumber);
}

void EXTI_setTrigger(uint8_t pinNumber, uint8_t triggerType){
    if(triggerType == EXTI_TRIGGER_RISING){
        EXTI->RTSR |= (1 << pinNumber);
        EXTI->FTSR &= ~(1 << pinNumber);
    }else if(triggerType == EXTI_TRIGGER_FALLING){
        EXTI->FTSR |= (1 << pinNumber);
        EXTI->RTSR &= ~(1 << pinNumber);
    }else if(triggerType == EXTI_TRIGGER_RISING_FALLING){
        EXTI->RTSR |= (1 << pinNumber);
        EXTI->FTSR |= (1 << pinNumber);
    }
}

void EXTI_clearPending(uint8_t pinNumber){
    EXTI->PR = (1 << pinNumber);
}