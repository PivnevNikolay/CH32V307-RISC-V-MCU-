/*
 * https://stackoverflow.com/questions/35513893/how-to-link-eclipse-project-with-lm-library-for-floor-and-pow-function
 */
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include "stepper.h"
#include "debug.h"

#define SYSCLK_FREQ_HSE    HSE_VALUE

void GPIO_Toggle_INIT( void )
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &GPIO_InitStructure );
}
/**************************************************************************************************
//Двигатель вращается с постоянной скоростью.
//В одном направлении, против часовой стрелки

int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    GPIO_Toggle_INIT();

    AccelStepper_stepper(FULL4WIRE);
    setMaxSpeed(5000);
    setSpeed(4000);
    while(1){
    runSpeed();
   }
}
*************************************************************************************************/
/**************************************************************************************************
//Двигатель вращается с ускорением и торможением, сначала в одну сторону потом в другую .
//Движение происходит к заданной точке, а потом от неё.
int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    GPIO_Toggle_INIT();

    AccelStepper_stepper(FULL4WIRE);
    setMaxSpeed(5000);
    setAcceleration(3500);
    moveTo(1024);
    while(1){
    if (distanceToGo() == 0)
      moveTo(-currentPosition());
      run();
   }
}
*************************************************************************************************/
/*************************************************************************************************/
//Двигатель двигается с ускорением и торможением, по заданной системе координат .
//Движение происходит к заданной точке, а потом от неё.
int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    GPIO_Toggle_INIT();

    AccelStepper_stepper(FULL4WIRE);
    setMaxSpeed(5000);
    setAcceleration(4000);
    while(1){
    moveTo(1024);
    while (currentPosition() != 1024)
    run();
    runToNewPosition(0);
    printf("0_position\r\n");
    moveTo(1024);
    while (currentPosition() != 1024)
    run();
    runToNewPosition(512);
    printf("512_position\r\n");
    moveTo(1024);
    while (currentPosition() != 1024)
    run();
    runToNewPosition(924);
    printf("924_position\r\n");
   }
}
