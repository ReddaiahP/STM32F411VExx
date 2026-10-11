#include "stm32f411_systick.h"

volatile uint32_t SysTick_FLAG;
volatile uint32_t lastTick;
volatile uint32_t currentTick;

void SysTick_Handler(void){
    SysTick_FLAG++;
}

void SysTick_Init(SysTicReg_Config_t *psystickregconfig)
{

    SYSTICK->VAL = psystickregconfig->VAL_BIT; // Clear the current value
    SYSTICK->LOAD = psystickregconfig->LOAD_BIT; // Set the reload value

    SYSTICK->CTRL |= (psystickregconfig->TICKINT_BIT << 1); // Enable SysTick interrupt
    SYSTICK->CTRL |= (psystickregconfig->CLKSOURCE_BIT << 2); // Set the clock source
}



void SysTick_Start(void){
    SYSTICK->CTRL |= (1 << 0);
}


void SysTick_Stop(void){
    SYSTICK->CTRL &= ~(1 << 0);
}



uint32_t SysTick_GetCurrentValue(void){
    return SYSTICK->VAL;
}


uint8_t SysTick_GetFlagStatus(void){
    return (SYSTICK->CTRL & (1 << 16)) != 0;
}



void SysTick_Delay_ms(uint32_t ms){
    uint32_t local_tick_count = 0;
    while(local_tick_count < ms){
        if(SysTick_GetFlagStatus()){
            local_tick_count++;
        }
    }
}


// delay function non blocking
uint8_t SysTick_Delay_ms_nb(uint32_t previousTick, uint32_t delay_ms){
    return ((SysTick_FLAG-previousTick)>=delay_ms);
}