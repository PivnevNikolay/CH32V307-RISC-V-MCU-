
#include "debug.h"
#include "string.h"

#define RX_BUF_SIZE 80
volatile char RX_FLAG_END_LINE = 0;
volatile char RXi;
volatile char RXc;
char RX_BUF[RX_BUF_SIZE] = {'\0'};
volatile char buffer[80] = {'\0'};

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void clear_RXBuffer(void);
void USARTSend(char *pucBuffer);


void USART2_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

    /* USART2 TX-->A.2   RX-->A.3 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART2, ENABLE);
}


int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART2_init();
    /* Initialize LED which connected to PC0 */
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, GPIO_Pin_0); // Set C0 to Low level ("1")
    USARTSend(" Hello.\r\nUSART1 is ready.\r\n");

    while(1)
    {
     if (RX_FLAG_END_LINE == 1) {
     // Reset END_LINE Flag
     RX_FLAG_END_LINE = 0;
     USARTSend("\r\nI has received a line:\r\n");
     USARTSend(RX_BUF);
     USARTSend("\r\n");
     if (strncmp(strupr(RX_BUF), "ON\r", 3) == 0) {
     USARTSend("\r\nThis is command \"ON\"!\r\n");
     GPIO_ResetBits(GPIOC, GPIO_Pin_0);
     }
     if (strncmp(strupr(RX_BUF), "OFF\r", 4) == 0) {
     USARTSend("\r\nThis is command \"OFF\"!\r\n");
     GPIO_SetBits(GPIOC, GPIO_Pin_0);
     }
     clear_RXBuffer();
     }
   }
}

void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
     RXc = USART_ReceiveData(USART2);
     RX_BUF[RXi++] = RXc;
     if (RXc != 13) {
     if (RXi > RX_BUF_SIZE-1) {
     clear_RXBuffer();
     }
     }
     else {
     RX_FLAG_END_LINE = 1;
     }
     //Echo!!!
      USART_SendData(USART2, RXc);
    }
}

void USARTSend(char *pucBuffer)
{
    while (*pucBuffer)
    {
     USART_SendData(USART2, *pucBuffer++);
     while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
     {
     }
  }
}

void clear_RXBuffer(void){
   for(RXi=0;RXi<RX_BUF_SIZE;RXi++){
       RX_BUF[RXi] = 0u;}
       RXi=0;
}
