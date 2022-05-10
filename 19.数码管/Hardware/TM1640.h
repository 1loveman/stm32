#ifndef __TM1640_H__
#define __TM1640_H__
#include"stm32f10x.h"
#include"delay.h"
#define TM1640PORT GPIOA
#define TM1640_SCLK GPIO_Pin_11
#define TM1640_DIN GPIO_Pin_12
#define DEL 1
#define TM1640_DSet 0X44
#define TM1640_SSet 0X88

void TM1640_Init(void);
void TM1640_Show(u8 address,u8 data);
void TM1640_SLED(u8 address,u8 data);
#endif
