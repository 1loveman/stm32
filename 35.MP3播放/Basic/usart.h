#ifndef __USART_H__
#define __USART_H__
#include"stm32f10x.h"
#include<stdarg.h>
#include<string.h>
#include<stdlib.h>
#include"stdio.h"

#define USARTN USART3
#define USART3_REC_LEN 200
#define EN_USART3 1

void USART3_Init(u32 bound);
void USART3_printf(char* fmt,...);

#endif
