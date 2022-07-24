#include "debug.h"
//https://nc-pin.com
uint8_t Count = 0;
//----------------------------------------------------------------------------//
void EXTI0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));//!!!
//----------------------------------------------------------------------------//
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
  {
#if 1
    Count++;
    if(Count==4)Count=0;
#endif
    EXTI_ClearITPendingBit(EXTI_Line0);     /* Clear Flag */
  }
}
//----------------------------------------------------------------------------//
void EXTI0_INT_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    EXTI_InitTypeDef EXTI_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* GPIOA ----> EXTI_Line0 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
//----------------------------------------------------------------------------//
void GPIO_Toggle_INIT(void)
{
  //Configure the GPIO PA.0, PA.1, PA.2, PA.3 --> Led1, Led2, ELLed1, ELLed2 pin
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;
    GPIOA->CFGLR = 0x2222;
  //Set PA.0 PA.1 PA.2 PA.3 high level(1)
    GPIOA->BSHR = 0xF;
}
//----------------------------------------------------------------------------//
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("EXTI0 Test\r\n");
    EXTI0_INT_INIT();
    GPIO_Toggle_INIT();
//----------------------------------------------------------------------------//
    while(1)
    {
    switch(Count){
    case 0:
    GPIOA->OUTDR ^= 0x1;
    Delay_Ms(250);
    GPIOA->OUTDR ^= 0x1;
    Delay_Ms(250);
    break;
    case 1:
    GPIOA->OUTDR ^=0x2;
    Delay_Ms(250);
    GPIOA->OUTDR ^=0x2;
    Delay_Ms(250);
    break;
    case 2:
    GPIOA->OUTDR ^=0x4;
    Delay_Ms(250);
    GPIOA->OUTDR ^=0x4;
    Delay_Ms(250);
    break;
    case 3:
    GPIOA->OUTDR ^=0x8;
    Delay_Ms(250);
    GPIOA->OUTDR ^=0x8;
    Delay_Ms(250);
    break;
   }
 }
}
//----------------------------------------------------------------------------//

