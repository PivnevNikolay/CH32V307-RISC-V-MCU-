#include "debug.h"
#include "gpio.h"

int main(void)
{
    //u8 i = 0;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("GPIO Toggle TEST\r\n");
    Gpio_Port_Clock_Output(GPIOA);
    Gpio_SetOut_PP(GPIOA, GPIO_Pin_0, Speed_GPIO_2MHz);

    while(1)
    {
        Delay_Ms(250);
       // GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
        GPIO_WriteBit(GPIOA, GPIO_Pin_0,!GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0));
    }
}

