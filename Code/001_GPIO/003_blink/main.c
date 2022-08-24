#include "debug.h"
#include "gpio.h"

void GPIO_OutputBit_1(void);
void GPIO_OutputBit_2(void);

int main(void)
{
  u8 i = 0;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  Delay_Init();
  USART_Printf_Init(115200);
  printf("SystemClk:%d\r\n", SystemCoreClock);
  printf("GPIO Toggle TEST\r\n");
  Gpio_Port_Clock_Output(GPIOA);
  Gpio_SetOut_PP(GPIOA, GPIO_Pin_0, Speed_GPIO_2MHz);
  GPIO_OutputBit_1();
  GPIO_OutputBit_2();
  GPIO_OutputBit_1();
  GPIO_OutputBit_2();

while(1)
 {
  GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
  Delay_Ms(250);
  //GPIO_WriteBit(GPIOA, GPIO_Pin_0,!GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0));
  //Delay_Ms(250);
 }
}

void GPIO_OutputBit_1(void)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);
  printf("GPIO Toggle\r\n");
  Delay_Ms(250);
  GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_RESET);
  printf("GPIO Toggle\r\n");
  Delay_Ms(250);
}

void GPIO_OutputBit_2(void)
{
  u16 uOutputData;
  uOutputData = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
  GPIO_WriteBit(GPIOA, GPIO_Pin_0,!uOutputData);
  printf("GPIO Toggle\r\n");
  Delay_Ms(250);
  uOutputData = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
  GPIO_WriteBit(GPIOA, GPIO_Pin_0,!uOutputData);
  printf("GPIO Toggle\r\n");
  Delay_Ms(250);
}
