#include "debug.h"
#define ADDR_FIXED 0x44
#define ADDR_AUTO  0x40
const uint8_t digitHEX[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00, 0x40}; //0~9
//*************************************************************************************************************
//                        H     E     L     L     O                 1     6     3     7           D     i     S     P
uint8_t Hello_world[] = {0x76, 0x79, 0x38, 0x38, 0x3f, 0x00, 0x00, 0x06, 0x7d, 0x4f, 0x07, 0x00, 0x3f, 0x10, 0x6d, 0x73,
//                        l     A     Y                           0    1    2    3    4    5    6    7    8    9
                        0x06, 0x77, 0x6e, 0x00, 0x00,0x00, 0x00,0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//*************************************************************************************************************
uint8_t lastData[4];
uint8_t PointData;
uint8_t Cmd_DispCtrl;
uint8_t Cmd_SetData;
uint8_t Cmd_SetAddr;
//*************************************************************************************************************
void clear(void);
void display(uint8_t BitAddr, uint8_t DispData);
void send_Byte(uint8_t BitAddr, int8_t sendData);
void brightness_(uint8_t brightness, uint8_t SetData, uint8_t SetAddr);
int Write_Byte(int8_t wr_data);
void update(void);
void displayByte(uint8_t DispData[]);
void sendArray(uint8_t sendData[]);
void display_Byte(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3);
void start(void);
void stop(void);
void Running_String(uint8_t DispData[], uint8_t amount, int delayMs);
//*************************************************************************************************************
void GPIO_Pin_INIT_TM1637(void);
//*************************************************************************************************************
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  Delay_Init();
  USART_Printf_Init(115200);
  GPIO_Pin_INIT_TM1637();
  printf("SystemClk:%d\r\n",SystemCoreClock);
  clear();
  brightness_(7, 0x40, 0xc0); //brightness,0 - 7(min - max)
  while(1)
  {
    Running_String(Hello_world, sizeof(Hello_world), 300);
  }
}
void GPIO_Pin_INIT_TM1637(void)
{
  /*RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef GPIO_Output_pin = {0};
  //Configure the GPIO PC.0 --> CLK, PC.1 --> DIO
  GPIO_Output_pin.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_Output_pin.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Output_pin.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_Output_pin);*/
  RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;
  GPIOC->CFGLR = 0x22;
}
//*************************************************************************************************************
void clear(void)
{
  display(0x00, 0x7f);
  display(0x01, 0x7f);
  display(0x02, 0x7f);
  display(0x03, 0x7f);
  lastData[0] = 0x00;
  lastData[1] = 0x00;
  lastData[2] = 0x00;
  lastData[3] = 0x00;
}
//*************************************************************************************************************
void display(uint8_t BitAddr, uint8_t DispData)
{
  uint8_t SegData;
  lastData[BitAddr] = digitHEX[DispData];
  SegData = digitHEX[DispData] + PointData;
  send_Byte(BitAddr, SegData);
}
//*************************************************************************************************************
void send_Byte(uint8_t BitAddr, int8_t sendData) {
  start();
  Write_Byte(ADDR_FIXED);
  stop();
  start();
  Write_Byte(BitAddr | 0xc0);
  Write_Byte(sendData);
  stop();
  start();
  Write_Byte(Cmd_DispCtrl);
  stop();
}
//*************************************************************************************************************
void brightness_(uint8_t brightness, uint8_t SetData, uint8_t SetAddr)
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;
  update();
}
//*************************************************************************************************************
int Write_Byte(int8_t wr_data)
{
  uint8_t i;
  for (i = 0; i < 8; i++)
  {
  GPIOC->BCR = GPIO_BCR_BR0;     //GPIO_WriteBit(GPIOC,GPIO_Pin_0, Bit_RESET);// PC0 = 0;
  if (wr_data & 0x01) {
  GPIOC->BSHR = GPIO_BSHR_BS1;   //GPIO_WriteBit(GPIOC,GPIO_Pin_1, Bit_SET);//PC1 = 1;
  }
  else GPIOC->BCR = GPIO_BCR_BR1;//GPIO_WriteBit(GPIOC,GPIO_Pin_1, Bit_RESET);//PC1 = 0;
  wr_data >>= 1;
  GPIOC->BSHR = GPIO_BSHR_BS0;   //GPIO_WriteBit(GPIOC,GPIO_Pin_0, Bit_SET);//PC0 = 1;
  }
  GPIOC->BCR = GPIO_BCR_BR0;     //GPIO_WriteBit(GPIOC,GPIO_Pin_0, Bit_RESET);//PC0 = 0;
  GPIOC->BSHR = GPIO_BSHR_BS1;   //GPIO_WriteBit(GPIOC,GPIO_Pin_1, Bit_SET);//PC1 = 1;
  GPIOC->BSHR = GPIO_BSHR_BS0;   //GPIO_WriteBit(GPIOC,GPIO_Pin_0, Bit_SET);//PC0 = 1;
  uint8_t ack = 1;
  GPIOC->CFGLR = 0x4;            //GPIO_SetMode(PC, BIT1, GPIO_MODE_INPUT);
  Delay_Us(500);//delay 50 microseconds
  if((GPIOC->INDR & 1<<0)==0){//if (PC1 == 0)
  GPIOC->CFGLR = 0x22;//GPIO_SetMode(PC, BIT1,  GPIO_MODE_OUTPUT);
  GPIOC->BCR = GPIO_BCR_BR1;     //GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);//PC1 = 0;
  ack = 0;
  }
  Delay_Us(500);//delay 50 microseconds
  GPIOC->CFGLR = 0x22;//GPIO_SetMode(PC, BIT1,  GPIO_MODE_OUTPUT);
  Delay_Us(500);//delay 50 microseconds
  return ack;
}
//*************************************************************************************************************
void update(void)
{
  displayByte(lastData);
}
//*************************************************************************************************************
void displayByte(uint8_t DispData[])
{
  uint8_t SegData[4];
  for (uint8_t i = 0; i < 4; i ++) {
  lastData[i] = DispData[i];
  SegData[i] = DispData[i] + PointData;
  }
  sendArray(SegData);
}
//*************************************************************************************************************
void sendArray(uint8_t sendData[])
{
  start();
  Write_Byte(ADDR_AUTO);
  stop();
  start();
  Write_Byte(Cmd_SetAddr);
  for (uint8_t i = 0; i < 4; i ++) {
  Write_Byte(sendData[i]);
  }
  stop();
  start();
  Write_Byte(Cmd_DispCtrl);
  stop();
}
//*************************************************************************************************************
void display_Byte(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3)
{
  uint8_t dispArray[] = {bit0, bit1, bit2, bit3};
  displayByte(dispArray);
}
//*************************************************************************************************************
void start(void)
{
  GPIOC->BSHR = GPIO_BSHR_BS0;//GPIO_WriteBit(GPIOC, GPIO_Pin_0,Bit_SET);//PC0 = 1;//CLK
  GPIOC->BSHR = GPIO_BSHR_BS1;//GPIO_WriteBit(GPIOC, GPIO_Pin_1,Bit_SET);//PC1 = 1;//DIO
  GPIOC->BCR = GPIO_BCR_BR1;  //GPIO_WriteBit(GPIOC, GPIO_Pin_1,Bit_RESET);//PC1 = 0;//DIO
  GPIOC->BCR = GPIO_BCR_BR0;  //GPIO_WriteBit(GPIOC, GPIO_Pin_0,Bit_RESET);//PC0 = 0;//CLK
}
//*************************************************************************************************************
void stop(void)
{
  GPIOC->BCR = GPIO_BCR_BR0;  //GPIO_WriteBit(GPIOC, GPIO_Pin_0,Bit_RESET);//-->PC0 = 0;
  GPIOC->BCR = GPIO_BCR_BR1;  //GPIO_WriteBit(GPIOC, GPIO_Pin_1,Bit_RESET);//-->PC1 = 0;
  GPIOC->BSHR = GPIO_BSHR_BS0;//GPIO_WriteBit(GPIOC, GPIO_Pin_0,Bit_SET);//-->PC0 = 1;
  GPIOC->BSHR = GPIO_BSHR_BS1;//GPIO_WriteBit(GPIOC, GPIO_Pin_1,Bit_SET);//-->PC1 = 1;
}
//*************************************************************************************************************
void Running_String(uint8_t DispData[], uint8_t amount, int delayMs) {
  uint8_t segm_data[amount + 8];
  for (uint8_t i = 0; i < 4; i++) {
  segm_data[i] = 0x00;
  }
  for (uint8_t i = 0; i < amount; i++) {
  segm_data[i + 4] = DispData[i];
  }
  for (uint8_t i = amount + 4; i < amount + 8; i++) {
  segm_data[i] = 0x00;
  }
  for (uint8_t i = 0; i <= amount + 4; i++) {
  display_Byte(segm_data[i], segm_data[i + 1], segm_data[i + 2], segm_data[i + 3]);
  Delay_Ms(delayMs);
  }
}
//*************************************************************************************************************
