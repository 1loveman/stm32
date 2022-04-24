#ifndef __USART_H__
#define __USART_H__
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"sys.h"

#define USART_n USART1

#define EN_USART1 1

#define USART1_REC_LEN 200

extern u16 USART1_REC_STA;

extern u8 USART1_REC_BUFF[USART1_REC_LEN];

void USART1_Init(void);
void USART1_printf(char* fmt,...);

#endif 
