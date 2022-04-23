#ifndef __USART_H__
#define __USART_H__

#include"sys.h"

#define USART_n USART1

#define EN_USART1 1
#define EN_USART2 0
#define EN_USART3 0

#define USART1_REC_LEN 200

extern u16 USART1_REC_STA;

extern u8 USART1_REC_BUFF[USART1_REC_LEN];

void USART1_Init(void);
void USART1_Printf(char* fmt,...);


#endif 
