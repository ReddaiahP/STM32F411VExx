#include "stm32f411_gpio.h"
#include "stm32f411_rcc.h"

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

    //GPIOA0 config as input
    GPIO_Reg_Def_t *pGpioA0 = GPIOA;
    GPIO_PinConfig_t pinConfigA0;

    pinConfigA0.pin = GPIO_PIN_NO_0;
    pinConfigA0.opMode = GPIO_MODE_IN;
    pinConfigA0.pupd = GPIO_PD;
    pinConfigA0.otype = GPIO_OP_TYPE_PP;
    pinConfigA0.speed = GPIO_SPEED_HIGH;

    GPIOA_PCLK_EN();
    GPIO_init(pGpioA0, &pinConfigA0);
    
    
    while(1)
    {
        GPIO_togglePin(pGpioD13, GPIO_PIN_NO_13);
        GPIO_togglePin(pGpioD12, GPIO_PIN_NO_12);
        Delay(500000);
        GPIO_togglePin(pGpioD13, GPIO_PIN_NO_13);
        GPIO_togglePin(pGpioD12, GPIO_PIN_NO_12);  
        Delay(50000);
    }
}