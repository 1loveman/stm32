#ifndef __MY1690_H__
#define __MY1690_H__
#include"stm32f10x.h"
#include"usart.h"
void MY1690_Init(void);
void MY1690_Play(void);
void MY1690_Pause(void);
void MY1690_PREV(void);
void MY1690_NEXT(void);
void MY1690_VUP(void);
void MY1690_VDOWN(void);
void MY1690_Stop(void);

void MY1690_Cmd1(u8 data);
void MY1690_Cmd2(u8 data1,u8 data2);
void MY1690_Cmd3(u8 data1,u16 data2);

#endif
