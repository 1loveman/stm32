#ifndef __USART_H__
#define __USART_H__
#include"sys.h"
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include"stdio.h"

#define USARTN USART1
#define USART1_REC_LEN 200
#define EN_USART1 1

extern u8 USART1_RX_BUFFER[USART1_REC_LEN];
extern u16 USART1_RX_STA;

void USART1_Init(u32 bound);
void USART1_Printf(char* fmt,...);

#endif
