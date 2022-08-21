#ifndef _GPIO_H
#define _GPIO_H

#define Speed_GPIO_10MHz     0
#define Speed_GPIO_2MHz      1
#define Speed_GPIO_50MHz     2
void Gpio_SetOut_PP(GPIO_TypeDef* GPIOx, u16 Mask, u8 GPIOSpeed);
void Gpio_Port_Clock_Output(GPIO_TypeDef *GPIOx);

#endif
