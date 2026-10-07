#include "stm32f411_driver.h"

typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_Reg_Def_t;

#define SYSTICK ((SysTick_Reg_Def_t *)STK_BASE)

void SysTick_Init(uint32_t ticks);