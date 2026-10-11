#include "stm32f411_gpio.h"
#include "stm32f411_rcc.h"
#include "stm32f411_systick.h"

extern volatile uint32_t SysTick_FLAG;

int main(void)
{   
    // GPIO D13 and D12 configuration as output
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


    GPIO_Reg_Def_t *pGpioD14 = GPIOD;
    GPIO_PinConfig_t pinConfigD14;
    pinConfigD14.pin = GPIO_PIN_NO_14;
    pinConfigD14.opMode = GPIO_MODE_OUT;
    pinConfigD14.otype = GPIO_OP_TYPE_PP;
    pinConfigD14.speed = GPIO_SPEED_HIGH;
    pinConfigD14.pupd = GPIO_NO_PUPD;


    GPIO_Reg_Def_t *pGpioD15 = GPIOD;
    GPIO_PinConfig_t pinConfigD15;
    pinConfigD15.pin = GPIO_PIN_NO_15;
    pinConfigD15.opMode = GPIO_MODE_OUT;
    pinConfigD15.otype = GPIO_OP_TYPE_PP;
    pinConfigD15.speed = GPIO_SPEED_HIGH;
    pinConfigD15.pupd = GPIO_NO_PUPD;

    // FIX: Clock enabled, reset macro removed completely
    GPIOD_PCLK_EN();

    GPIO_init(pGpioD13, &pinConfigD13);
    GPIO_init(pGpioD12, &pinConfigD12);
    GPIO_init(pGpioD14, &pinConfigD14);
    GPIO_init(pGpioD15, &pinConfigD15);

    SysTicReg_Config_t systickConfig;
    systickConfig.LOAD_BIT = _100MHZ; // 1 ms baseline timing at 100 MHz clock
    systickConfig.TICKINT_BIT = TICKINT_EN;
    systickConfig.CLKSOURCE_BIT = CLKSOURCE_AHB;
    systickConfig.VAL_BIT = 0; 
    
    SysTick_Init(&systickConfig); 
    SysTick_Start(); 
    uint32_t prevTick1 = 0; // for led D12
    uint32_t prevTick2 = 0; // for led D13
    uint32_t prevTick3 = 0; // for led D14
    uint32_t prevTick4 = 0; // for led D15
    
    
    while(1)
    {   

        if(SysTick_Delay_ms_nb(prevTick1,10)){
            GPIO_togglePin(pGpioD12, GPIO_PIN_NO_12);
            prevTick1 = SysTick_FLAG;
        }

        if(SysTick_Delay_ms_nb(prevTick2,150)){
            GPIO_togglePin(pGpioD13, GPIO_PIN_NO_13);
            prevTick2 = SysTick_FLAG;
        }

        if(SysTick_Delay_ms_nb(prevTick3,200)){
            GPIO_togglePin(pGpioD14, GPIO_PIN_NO_14);
            prevTick3 = SysTick_FLAG;
        }

        if(SysTick_Delay_ms_nb(prevTick4,250)){
            GPIO_togglePin(pGpioD15, GPIO_PIN_NO_15);
            prevTick4 = SysTick_FLAG;
        }

    }
}


