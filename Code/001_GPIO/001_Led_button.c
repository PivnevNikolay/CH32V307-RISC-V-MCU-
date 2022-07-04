#include "debug.h"
/*-----------------------------------------------------------*/
uint8_t Count = 0;
void GPIO_Toggle_INIT(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef GPIO_Output_pin = {0};
  //Configure the GPIO PC.0, PC.1, PC.2, PC.3 --> Led1, Led2, ELLed1, ELLed2 pin
  GPIO_Output_pin.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_Output_pin.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Output_pin.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_Output_pin);
  GPIOC->BSHR = GPIO_Pin_0;//Set PC.0 high level(1)
  GPIOC->BSHR = GPIO_Pin_1;//Set PC.1 high level(1)
  GPIOC->BSHR = GPIO_Pin_2;//Set PC.2 high level(1)
  GPIOC->BSHR = GPIO_Pin_3;//Set PC.3 high level(1)
  //Configure the GPIO PA.0 button pin
  GPIO_InitTypeDef GPIO_Input_pin = {0};
  GPIO_Input_pin.GPIO_Pin = GPIO_Pin_0;
  GPIO_Input_pin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_Input_pin);
}
/*-----------------------------------------------------------*/
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  GPIO_Toggle_INIT();
  Delay_Init();
  USART_Printf_Init(115200);
  printf("SystemClk:%d\r\n",SystemCoreClock);
  printf("This is printf example\r\n");
  printf("Hello world\r\n");
  while(1){
  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)!=1){
        switch(Count){
        case 0:
        GPIOC->OUTDR ^=GPIO_Pin_0;
        Delay_Ms(250);
        GPIOC->OUTDR ^=GPIO_Pin_0;
        Delay_Ms(250);
        printf("Blink Led pin PC.0\r\n");
        Count++;
        break;
        case 1:
        GPIOC->OUTDR ^=GPIO_Pin_1;
        Delay_Ms(250);
        GPIOC->OUTDR ^=GPIO_Pin_1;
        Delay_Ms(250);
        printf("Blink Led pin PC.1\r\n");
        Count++;
        break;
        case 2:
        GPIOC->OUTDR ^=GPIO_Pin_2;
        Delay_Ms(250);
        GPIOC->OUTDR ^=GPIO_Pin_2;
        Delay_Ms(250);
        printf("Blink Led pin PC.2\r\n");
        Count++;
        break;
        case 3:
        GPIOC->OUTDR ^=GPIO_Pin_3;
        Delay_Ms(250);
        GPIOC->OUTDR ^=GPIO_Pin_3;
        Delay_Ms(250);
        printf("Blink Led pin PC.3\r\n");
        Count=0;
        break;
     }
  }
	else{
    GPIOC->BSHR = GPIO_Pin_0;//Set PC.0 high level(1)
    GPIOC->BSHR = GPIO_Pin_1;//Set PC.1 high level(1)
    GPIOC->BSHR = GPIO_Pin_2;//Set PC.2 high level(1)
    GPIOC->BSHR = GPIO_Pin_3;//Set PC.3 high level(1)
   }
 }
}
/*-----------------------------------------------------------*/
