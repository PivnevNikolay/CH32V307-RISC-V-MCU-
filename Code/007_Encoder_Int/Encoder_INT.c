//https://robocraft.ru/arm/739
#include "debug.h"

#define FORWARD 0
#define BACKWARD 1

#define NOREADY 0
#define READY 1
#define INIT 3

volatile u8 encoder_status = INIT;
volatile u8 encoder_direction = FORWARD;

void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void TIM3_IRQHandler(void) {
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
    if (encoder_status == INIT)
      encoder_status = NOREADY;
    else
      encoder_status = READY;

    encoder_direction = (TIM3->CTLR1 & TIM_DIR ? BACKWARD : FORWARD);

    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  }
}

int main(void) {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  Delay_Init();
  USART_Printf_Init(115200);
  printf("SystemClk:%d\r\n", SystemCoreClock);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef port_A;
  port_A.GPIO_Mode = GPIO_Mode_IPU;
  port_A.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  port_A.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &port_A);
  TIM_TimeBaseInitTypeDef TIMER_InitStructure;
  TIM_TimeBaseStructInit(&TIMER_InitStructure);
  TIMER_InitStructure.TIM_Period = 1;
  TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up | TIM_CounterMode_Down;
  TIM_TimeBaseInit(TIM3, &TIMER_InitStructure);

  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  NVIC_EnableIRQ(TIM3_IRQn);
  TIM_Cmd(TIM3, ENABLE);

  while (1) {
    if (encoder_status) {
      encoder_status = NOREADY;

      if (encoder_direction == FORWARD) {
        printf("FORWARD\r\n");
        //....
      } else {
        printf("BACKWARD\r\n");
        //....
      }
    }
  }
}