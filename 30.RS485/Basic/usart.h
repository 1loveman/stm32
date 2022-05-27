#ifndef __USART_H__
#define __USART_H__
#include"stm32f10x.h"
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"OLED.h"

#define USARTN USART3
#define USART3_REC_LEN 200
#define EN_USART3 1

extern u8 USART3_RX_BUFF[USART3_REC_LEN];

void USART3_Init(u32 bound);
void USART3_printf(char* fmt,...);

#endif
