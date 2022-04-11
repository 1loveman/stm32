#ifndef __USART_H__
#define __USART_H__
#include<stdarg.h>
#include<string.h>
#include<stdlib.h>
#include"stdio.h"
#include"sys.h"

#define USART_n USART1	//选择printf默认端口

#define USART1_REC_LEN 200 //设置最大接收字节长度
#define USART2_REC_LIN 200
#define USART3_REC_LIN 200

#define EN_USART1 1	  //选择开启或禁用不用端口
#define EN_USART2 0
#define EN_USART3 0

//全局变量的声明--只写了usart1的。
extern u8 USART1_RX_BUF[USART1_REC_LEN];	//数组
extern u16 USART1_RX_STA;					//定义变量类似控制寄存器原理

void USART1_Init(u32 bound);
void USART2_Init(u32 bound);
void USART3_Init(u32 bound);

void USART1_printf(char* fmt,...);
void USART2_printf(char* fmt,...);
void USART3_printf(char* fmt,...);

#endif
