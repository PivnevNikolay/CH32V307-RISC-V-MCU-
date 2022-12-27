#include "debug.h"
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;//Включаем тактирование порта GPIOA
    GPIOA->CFGLR = 0x100001;//PA0 и PA5 сконфигурированы на выход с частотой 10 MHz
    //GPIOA->CFGLR = 0x200002;//PA0 и PA5 сконфигурированы на выход с частотой 2 MHz
    //GPIOA->CFGLR = 0x300003;//PA0 и PA5 сконфигурированы на выход с частотой 50 MHz
    GPIOA->OUTDR = 0x21;//PA0 и PA5 установим на выходах логическую еденицу

    while(1)
    {
        GPIOA->BSHR =0x210000;//PA0 и PA5 установим на выходах логическую ноль
        Delay_Ms(750);
        GPIOA->BSHR =0x33;//PA0 и PA5 установим на выходах логическую еденицу
        Delay_Ms(750);
    }
}