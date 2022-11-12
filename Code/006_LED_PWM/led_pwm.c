#include "debug.h"
#include "stdbool.h"
#define PERIOD 1000
volatile bool FLAG = false;
int TIM_Pulse = 500;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    GPIO_InitTypeDef port_B;
    port_B.GPIO_Mode = GPIO_Mode_AF_PP;
    port_B.GPIO_Pin = GPIO_Pin_6;
    port_B.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &port_B);
    TIM_TimeBaseInitTypeDef timer;
    TIM_TimeBaseStructInit(&timer);
    timer.TIM_Prescaler = 720;
    timer.TIM_Period = PERIOD;
    timer.TIM_ClockDivision = 0;
    timer.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &timer);
    TIM_OCInitTypeDef timerPWM;
    TIM_OCStructInit(&timerPWM);
    timerPWM.TIM_Pulse = 10;
    timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
    timerPWM.TIM_OutputState = TIM_OutputState_Enable;
    timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4, &timerPWM);

    TIM_Cmd(TIM4, ENABLE);


    while(1)
    {
          switch(FLAG){
          case 0:
              if (TIM_Pulse < PERIOD){
                  TIM_Pulse++;
              TIM4->CH1CVR = TIM_Pulse;
              Delay_Ms(3);
              //printf("TIM_Pulse:%d\r\n", TIM_Pulse);
              }
              else FLAG = true;
          break;
          case 1:
              if (TIM_Pulse > 0){
                    TIM_Pulse--;
                TIM4->CH1CVR = TIM_Pulse;
                Delay_Ms(3);
                //printf("TIM_Pulse:%d\r\n", TIM_Pulse);
              }
              else FLAG = false;
          break;
    }
}
}