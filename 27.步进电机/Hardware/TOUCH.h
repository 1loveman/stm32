#ifndef __TOUCH_H__
#define __TOUCH_H__
#include"stm32f10x.h"
#define TPORT GPIOA
#define TA GPIO_Pin_0
#define TB GPIO_Pin_1
#define TC GPIO_Pin_2
#define TD GPIO_Pin_3

void TOUCH_Init(void);
#endif
