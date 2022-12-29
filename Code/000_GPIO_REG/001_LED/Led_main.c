//-----------------------------------1----------------------------------//
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
        GPIOA->BSHR =0x21;//PA0 и PA5 установим на выходах логическую еденицу
        Delay_Ms(750);
    }
}
//------------------------------END--1----------------------------------//

//-----------------------------------2----------------------------------//
#include "debug.h"
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;//Включаем тактирование порта GPIOA

    GPIOA->CFGLR |=   GPIO_CFGLR_MODE0_0;//PA0 сконфигурирован на выход с частотой 10 MHz
    GPIOA->CFGLR &= ~ GPIO_CFGLR_MODE0_1;
    GPIOA->CFGLR &= ~ GPIO_CFGLR_CNF0_0;
    GPIOA->OUTDR |=   GPIO_OUTDR_ODR0;//PA0 установим на выходе логическую еденицу

    GPIOA->CFGLR |=   GPIO_CFGLR_MODE5_0;//PA5 сконфигурирован на выход с частотой 10 MHz
    GPIOA->CFGLR &= ~ GPIO_CFGLR_MODE5_1;
    GPIOA->CFGLR &= ~ GPIO_CFGLR_CNF5_0;
    GPIOA->OUTDR |=   GPIO_OUTDR_ODR5;//PA5 установим на выходе логическую еденицу

    while(1)
    {
        GPIOA->BSHR =((GPIO_BSHR_BR0)|(GPIO_BSHR_BR5));
		//PA0 и PA5 установим на выходах логическую ноль (регистр BSHR --> WO(Write only)),считывать его нельзя (|= недопустимо)
        Delay_Ms(750);
        GPIOA->BSHR =((GPIO_BSHR_BS0)|(GPIO_BSHR_BS5));
		//PA0 и PA5 установим на выходах логическую еденицу (регистр BSHR --> WO(Write only)),считывать его нельзя (|= недопустимо)
        Delay_Ms(750);

    }
}
//------------------------------END--2----------------------------------//