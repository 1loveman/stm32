#ifndef __TOUCH_H__
#define __TOUCH_H__
#include"stm32f10x.h"
#define TKPORT GPIOA
#define TK1 GPIO_Pin_0
#define TK2 GPIO_Pin_1
#define TK3 GPIO_Pin_2
#define TK4 GPIO_Pin_3

void TOUCH_Init(void);

#endif
