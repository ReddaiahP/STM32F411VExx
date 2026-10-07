#include "stm32f411_systick.h"


void SysTick_Init(SysTicReg_Config_t *psystickregconfig)
{

    SYSTICK->VAL = psystickregconfig->VAL_BIT; // Clear the current value
    SYSTICK->LOAD = psystickregconfig->LOAD_BIT; // Set the reload value

    SYSTICK->CTRL |= (psystickregconfig->TICKINT_BIT << 1); // Enable SysTick interrupt
    SYSTICK->CTRL |= (psystickregconfig->CLKSOURCE_BIT << 2); // Set the clock source
    SYSTICK->CTRL |= (psystickregconfig->CTRL_BIT << 0); // Set the reload value
    
}