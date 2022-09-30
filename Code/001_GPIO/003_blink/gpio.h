#ifndef _GPIO_H
#define _GPIO_H

#define Speed_GPIO_10MHz       0
#define Speed_GPIO_2MHz        1
#define Speed_GPIO_50MHz       2

#define Gpio_IN_NoPull         0
#define Gpio_IN_PullUp         1
#define Gpio_IN_PullDown       2
#define Gpio_IN_AnalogInput    3

#define Gpio_OUT_OD            0
#define Gpio_OUT_PP            1
#define Gpio_OUT_AF_OD         2
#define Gpio_OUT_AF_PP         3

void Gpio_Setmode_In (GPIO_TypeDef* GPIOx, u16 G_Mask, u8 G_Speed, u8 G_Mode);
void Gpio_Setmode_Out(GPIO_TypeDef* GPIOx, u16 G_Mask, u8 G_Speed, u8 G_Mode);
void Gpio_Port_Clock_Init(GPIO_TypeDef *GPIOx);

#endif
