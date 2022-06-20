#ifndef __USART_H__
#define __USART_H__
#include"stm32f10x.h"
#include<stdarg.h>
#include<string.h>
#include<stdlib.h>
#include"stdio.h"

#define USARTN USART3
#define USART1_REC_LEN 200
#define EN_USART1 1
#define USART3_REC_LEN 200
#define EN_USART3 1

extern u16 USART1_RX_STA;
extern u8 USART1_RX_BUF[USART1_REC_LEN];
extern u8 USART3_RX_STA;

void USART1_Init(u32 bound);
void USART1_printf(char* fmt,...);
void USART3_Init(u32 bound);
void USART3_printf(char* fmt,...);

#endif

