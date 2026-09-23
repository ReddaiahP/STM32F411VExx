#include "stm32f411_gpio.h"
#include "stm32f411_rcc.h"

int main(void)
{   
    GPIO_Reg_Def_t *pGpioD = GPIOD;
    GPIO_PinConfig_t pinConfigD;
    pinConfigD.pin = GPIO_PIN_NO_13;
    pinConfigD.opMode = GPIO_MODE_OUT;
    pinConfigD.otype = GPIO_OP_TYPE_PP;
    pinConfigD.speed = GPIO_SPEED_HIGH;
    pinConfigD.pupd = GPIO_NO_PUPD;

    GPIOD_PCLK_EN();
    GPIOD_PREG_RST();
    GPIO_Init(pGpioD, &pinConfigD);

    while(1)
    {
    }
}