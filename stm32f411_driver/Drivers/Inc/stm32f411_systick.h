#include "stm32f411_driver.h"


#define _100MHZ (100000-1)


typedef enum{
    CTRL_DI = 0,
    CTRL_EN = 1,
} SysTick_Ctrl_t;

typedef enum{
    TICKINT_DI = 0,
    TICKINT_EN = 1,
} SysTick_TickInt_t;


typedef enum{
    CLKSOURCE_AHB_DIV8 = 0,
    CLKSOURCE_AHB = 1,
} SysTick_ClkSource_t;



typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_Reg_Def_t;

typedef struct {
    volatile uint32_t TICKINT_BIT;
    volatile uint32_t CLKSOURCE_BIT;
    volatile uint32_t LOAD_BIT;
    volatile uint32_t VAL_BIT;

}SysTicReg_Config_t;

#define SYSTICK ((SysTick_Reg_Def_t *)STK_BASE)

void SysTick_Init(SysTicReg_Config_t *psystickregconfig);
void SysTick_Start(void);
void SysTick_Stop(void);
uint32_t SysTick_GetCurrentValue(void);
uint8_t SysTick_GetFlagStatus(void);
void SysTick_Delay_ms(uint32_t ms);
uint8_t SysTick_Delay_ms_nb(uint32_t previousTick, uint32_t delay_ms);
