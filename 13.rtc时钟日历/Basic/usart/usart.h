#ifndef __USART_H__
#define __USART_H__
#include"sys.h"
#include"stdio.h"
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>

#define USARTn USART1
#define EN_USART1 1
#define USART1_REC_LEN 200

extern u8 USART1_RX_BUFF[USART1_REC_LEN];
extern U16 USART1_RX_STA;

void USART1_Init(u32 bound);
void USART1_printf(char* fmt,...);

#endif
