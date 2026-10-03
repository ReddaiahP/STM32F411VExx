#include "stm32f411_gpio.h"
#include "stm32f411_rcc.h"

// extern void EXTI0_IRQHandler(void);

volatile static uint8_t IRQ0_FLAG = 0;
int main(void)
{   

    // GPIO D13 and D12 config as output
    GPIO_Reg_Def_t *pGpioD13 = GPIOD;
    GPIO_PinConfig_t pinConfigD13;
    pinConfigD13.pin = GPIO_PIN_NO_13;
    pinConfigD13.opMode = GPIO_MODE_OUT;
    pinConfigD13.otype = GPIO_OP_TYPE_PP;
    pinConfigD13.speed = GPIO_SPEED_HIGH;
    pinConfigD13.pupd = GPIO_NO_PUPD;

    GPIO_Reg_Def_t *pGpioD12 = GPIOD;
    GPIO_PinConfig_t pinConfigD12;
    pinConfigD12.pin = GPIO_PIN_NO_12;
    pinConfigD12.opMode = GPIO_MODE_OUT;
    pinConfigD12.otype = GPIO_OP_TYPE_PP;
    pinConfigD12.speed = GPIO_SPEED_HIGH;
    pinConfigD12.pupd = GPIO_NO_PUPD;

    GPIOD_PCLK_EN();
    GPIOD_PREG_RST();
    GPIO_init(pGpioD13, &pinConfigD13);
    GPIO_init(pGpioD12, &pinConfigD12);

    // GPIO A0 config as input
    GPIO_Reg_Def_t *pGpioA0 = GPIOA;
    GPIO_PinConfig_t pinConfigA0;
    pinConfigA0.pin = GPIO_PIN_NO_0;
    pinConfigA0.opMode = GPIO_MODE_IN;
    pinConfigA0.pupd = GPIO_NO_PUPD;

    GPIO_init(pGpioA0, &pinConfigA0);


    SYSCFG_enableEXTI(PORT_CODE_GPIOA, GPIO_PIN_NO_0);
    EXTI_enableIRQ(GPIO_PIN_NO_0);
    EXTI_setTrigger(GPIO_PIN_NO_0, EXTI_TRIGGER_RISING);
    NVIC_enableIRQ(IRQ_NO_EXTI0);

    while(1)
    {
        if(IRQ0_FLAG){
            GPIO_bssrPin(pGpioD13, GPIO_PIN_NO_13, GPIO_PIN_SET);
            GPIO_bssrPin(pGpioD12, GPIO_PIN_NO_12, GPIO_PIN_CLEAR);

            Delay(500000);

            GPIO_bssrPin(pGpioD13, GPIO_PIN_NO_13, GPIO_PIN_CLEAR);
            GPIO_bssrPin(pGpioD12, GPIO_PIN_NO_12, GPIO_PIN_SET);
            Delay(500000);

            IRQ0_FLAG = 0;
        }
        
    }
}



void EXTI0_IRQHandler(void){
    IRQ0_FLAG = 1;
    EXTI_clearPending(GPIO_PIN_NO_0);
}