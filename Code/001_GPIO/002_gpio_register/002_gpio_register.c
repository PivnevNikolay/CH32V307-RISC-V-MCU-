/** CH32V307V-EVT-R1
 * connect the pins of the microcontroller PC.0, PC.1, PC.2, PC.3
 * with the corresponding pins on the development board Led1, Led2, ELed1, ELed2
 * connect the output of the microcontroller PA.0
 * to the output on the debug board KEY
 *
 * after pressing the button, all four LEDs flash in turn
 */
#include "debug.h"
/*-----------------------------------------------------------*/
uint8_t Count = 0;
static uint8_t  p_us = 0;
static uint16_t p_ms = 0;
/*-----------------------------------------------------------*/
void Delay_microseconds(uint32_t n);
/*-----------------------------------------------------------*/
void GPIO_Toggle_INIT(void)
{
  //Configure the GPIO PC.0, PC.1, PC.2, PC.3 --> Led1, Led2, ELLed1, ELLed2 pin
  RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;
  GPIOC->CFGLR = 0x2222;
  //Set PC.0 PC.1 PC.2 PC.3 high level(1)
  GPIOC->BSHR = 0xF;
  //Configure the GPIO PA.0 button pin
  RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;
  GPIOA->CFGLR = 0x4;
}
/*-----------------------------------------------------------*/
int main(void)
{
  GPIO_Toggle_INIT();
  p_us = SystemCoreClock / 8000000;
  p_ms = (uint16_t)p_us * 1000;
  while(1){
  if((GPIOA->INDR & 1<<0)!=1){
    switch(Count){
    case 0:
    GPIOC->OUTDR ^= 0x1;
    Delay_microseconds(250);
    GPIOC->OUTDR ^= 0x1;
    Delay_microseconds(250);
    Count++;
    break;
    case 1:
    GPIOC->OUTDR ^=0x2;
    Delay_microseconds(250);
    GPIOC->OUTDR ^=0x2;
    Delay_microseconds(250);
    Count++;
    break;
    case 2:
    GPIOC->OUTDR ^=0x4;
    Delay_microseconds(250);
    GPIOC->OUTDR ^=0x4;
    Delay_microseconds(250);
    Count++;
    break;
    case 3:
    GPIOC->OUTDR ^=0x8;
    Delay_microseconds(250);
    GPIOC->OUTDR ^=0x8;
    Delay_microseconds(250);
    Count=0;
    break;
   }
 }
  else{
    //Set PC.0 PC.1 PC.2 PC.3 high level(1)
    GPIOC->BSHR = 0xF;
   }
 }
}
/*-----------------------------------------------------------*/
void Delay_microseconds(uint32_t n)
{
  uint32_t i;
  SysTick->SR &= ~(1 << 0);
  i = (uint32_t)n * p_ms;
  SysTick->CMP = i;
  SysTick->CTLR |= (1 << 4) | (1 << 5) | (1 << 0);
  while((SysTick->SR & (1 << 0)) != (1 << 0));
  SysTick->CTLR &= ~(1 << 0);
}
/*-----------------------------------------------------------*/
