#include "debug.h"
#include "gpio.h"

/*
 * @param    GPIOx -  where x can be (A..E) to select the GPIO peripheral.
 * @param    Mask -   This parameter can be GPIO_Pin_x where x can be (0..15).
 * GPIO_Pin_0
 * GPIO_Pin_1
 * GPIO_Pin_2
 * GPIO_Pin_3
 * GPIO_Pin_4
 * GPIO_Pin_5
 * GPIO_Pin_6
 * GPIO_Pin_7
 * GPIO_Pin_8
 * GPIO_Pin_9
 * GPIO_Pin_10
 * GPIO_Pin_11
 * GPIO_Pin_12
 * GPIO_Pin_13
 * GPIO_Pin_14
 * GPIO_Pin_15
 * @param GPIOSpeed -This parameter output maximum frequency selection pin
 * Speed_GPIO_10MHz
 * Speed_GPIO_2MHz
 * Speed_GPIO_50MHz
 */

void Gpio_Setmode_In(GPIO_TypeDef* GPIOx, u16 Mask, u8 PullMode)
{
  GPIO_InitTypeDef InitStruct;
  InitStruct.GPIO_Pin = Mask;
  InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

  switch (PullMode)
  {
  case Gpio_IN_NoPull:
    InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//вход без подтяжки 
    break;
  case Gpio_IN_PullUp:
    InitStruct.GPIO_Mode = GPIO_Mode_IPU;//вход с подтяжкой к питанию
    break;
  case Gpio_IN_PullDown:
    InitStruct.GPIO_Mode = GPIO_Mode_IPD;//вход с подтяжкой к земле 
    break;
  }

  GPIO_Init(GPIOx, &InitStruct);
}

void Gpio_Setmode_Out_PP(GPIO_TypeDef* GPIOx, u16 Mask, u8 GPIOSpeed)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = Mask;
  switch (GPIOSpeed)
  {
  case Speed_GPIO_10MHz:
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    break;
  case Speed_GPIO_2MHz:
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    break;
  case Speed_GPIO_50MHz:
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    break;
  }
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//выход с подтяжкой 
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}

//включение тактирования нужного порта
void Gpio_Port_Clock_Output(GPIO_TypeDef *GPIOx)
{
  if (GPIOx == GPIOA)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  else if (GPIOx == GPIOB)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  else if (GPIOx == GPIOC)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  else if (GPIOx == GPIOD)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  else if (GPIOx == GPIOE)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
}
