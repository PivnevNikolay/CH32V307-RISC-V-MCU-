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
 * скорость
 * GPIO_Speed_2MHz
 * GPIO_Speed_10MHz
 * GPIO_Speed_50MHz
 * Настройка GPIO как вход
 * GPIO_Mode_AIN — аналоговый вход.
 * GPIO_Mode_IN_FLOATING — вход без подтяжки.
 * GPIO_Mode_IPD — вход с подтяжкой к земле.
 * GPIO_Mode_IPU — вход с подтяжкой к питанию.
 */
/*****************************GPIO_IN*************************************/
void Gpio_Setmode_In(GPIO_TypeDef* GPIOx, u16 G_Mask, u8 G_Speed, u8 G_Mode)
{
  GPIO_InitTypeDef InitStruct;
  InitStruct.GPIO_Pin = G_Mask;

  switch (G_Speed)
    {
    case Speed_GPIO_10MHz:
        InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
      break;
    case Speed_GPIO_2MHz:
        InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
      break;
    case Speed_GPIO_50MHz:
        InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
      break;
    }

  switch (G_Mode)
  {
  case Gpio_IN_NoPull:
    InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//вход без подтяжки
    break;
  case Gpio_IN_PullUp:
    InitStruct.GPIO_Mode = GPIO_Mode_IPU;//вход с подтяжкой к земле
    break;
  case Gpio_IN_PullDown:
    InitStruct.GPIO_Mode = GPIO_Mode_IPD;//вход с подтяжкой к питанию
    break;
  case Gpio_IN_AnalogInput:
    InitStruct.GPIO_Mode = GPIO_Mode_AIN;//аналоговый вход
    break;
  }

  GPIO_Init(GPIOx, &InitStruct);
}
/*****************************GPIO_IN*************************************/
/*****************************GPIO_OUT************************************/
void Gpio_Setmode_Out(GPIO_TypeDef* GPIOx, u16 G_Mask, u8 G_Speed, u8 G_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = G_Mask;
  switch (G_Speed)
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

  switch (G_Mode)
    {
    case Gpio_OUT_OD:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//выход с открытым коллектором
      break;
    case Gpio_OUT_PP:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//выход с подтяжкой.
      break;
    case Gpio_OUT_AF_OD:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//альтернативный выход с открытым коллектором
      break;
    case Gpio_OUT_AF_PP:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//альтернативный выход с подтяжкой
      break;
    }

  GPIO_Init(GPIOx, &GPIO_InitStructure);
}
/*****************************GPIO_OUT************************************/
/*****************************Clock***************************************/
void Gpio_Port_Clock_Init(GPIO_TypeDef *GPIOx)
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
/*****************************Clock***************************************/
/*
 * void GPIO_DeInit(GPIO_TypeDef* GPIOx);
 * --> Деинициализирует периферийные регистры GPIOx до значений сброса по умолчанию.
 * ---------------------------------------------------------------------------------
 * void GPIO_AFIODeInit(void);
 * --> Деинициализирует регистры альтернативных функций (переназначение, управление событиями и конфигурация EXTI)
 *  до значений сброса по умолчанию.
 * ---------------------------------------------------------------------------------
 * void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
 * --> инициализирует периферийное устройство GPIOx в соответствии с указанными параметрами в GPIO_InitStruct.
 * ---------------------------------------------------------------------------------
 * void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
 *  --> Заполняет каждый член GPIO_InitStruct его значением по умолчанию.
 *      (GPIO_Pin_All,GPIO_Speed_2MHz,GPIO_Mode_IN_FLOATING)
 * ---------------------------------------------------------------------------------
 * uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
 * uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
 * uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
 * uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
 * void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
 * void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
 * void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
 * void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
 * void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
 * void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
 * void GPIO_EventOutputCmd(FunctionalState NewState);
 * void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
 * void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
 * void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);
 */

