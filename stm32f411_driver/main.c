#include "stm32f411_gpio.h"
#include "stm32f411_rcc.h"
#include "stm32f411_systick.h"

static volatile uint32_t SysTick_FLAG = 0;

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

    // FIX: Clock enabled, reset macro removed completely
    GPIOD_PCLK_EN();

    GPIO_init(pGpioD13, &pinConfigD13);
    GPIO_init(pGpioD12, &pinConfigD12);

    SysTicReg_Config_t systickConfig;
    systickConfig.LOAD_BIT = 100000 - 1; // 1 ms baseline timing at 100 MHz clock
    systickConfig.TICKINT_BIT = TICKINT_EN;
    systickConfig.CLKSOURCE_BIT = CLKSOURCE_AHB;
    systickConfig.VAL_BIT = 0; 
    
    SysTick_Init(&systickConfig); 
    SysTick_Start(); 

    
    while(1)
    {   
        
        SysTick_Delay_ms(200); // Wait for 200 ms
        // Turn LEDs back ON to restart the cycle
        GPIO_bssrPin(pGpioD13, GPIO_PIN_NO_13, GPIO_PIN_SET);
        GPIO_bssrPin(pGpioD12, GPIO_PIN_NO_12, GPIO_PIN_SET);
        SysTick_Delay_ms(20); // Wait for 200 ms
        // Turn LEDs OFF after 200ms has elapsed
        GPIO_bssrPin(pGpioD13, GPIO_PIN_NO_13, GPIO_PIN_CLEAR);
        GPIO_bssrPin(pGpioD12, GPIO_PIN_NO_12, GPIO_PIN_CLEAR);
        
    }
}

void SysTick_Handler(void){
    SysTick_FLAG++;
}
