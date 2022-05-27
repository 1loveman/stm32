#ifndef __RS485_H__
#define __RS485_H__
#include"stm32f10x.h"
#include"usart.h"
#define RS4PORT GPIOA
#define RS4RE GPIO_Pin_8

void RS485_Init(void);
void RS485_printf(char* fmt,...);

#endif
