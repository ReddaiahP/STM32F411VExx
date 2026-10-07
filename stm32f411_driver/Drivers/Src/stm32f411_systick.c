#include "stm32f411_systick.h"

void SysTick_Init(uint32_t ticks)
{
    SYSTICK->LOAD = (ticks - 1);
    SYSTICK->VAL = 0;
    SYSTICK->CTRL = 0x7;
}