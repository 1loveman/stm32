#ifndef __USART_H__
#define __USART_H__
#include<stdarg.h>
#include<string.h>
#include<stdlib.h>
#include"stdio.h"
#include"sys.h"

#define USART_n USART1	//ѡ��printfĬ�϶˿�

#define USART1_REC_LEN 200 //�����������ֽڳ���
#define USART2_REC_LIN 200
#define USART3_REC_LIN 200

#define EN_USART1 1	  //ѡ��������ò��ö˿�
#define EN_USART2 0
#define EN_USART3 0

//ȫ�ֱ���������--ֻд��usart1�ġ�
extern u8 USART1_RX_BUF[USART1_REC_LEN];	//����
extern u16 USART1_RX_STA;					//����������ƿ��ƼĴ���ԭ��

void USART1_Init(u32 bound);
void USART2_Init(u32 bound);
void USART3_Init(u32 bound);

void USART1_printf(char* fmt,...);
void USART2_printf(char* fmt,...);
void USART3_printf(char* fmt,...);

#endif
