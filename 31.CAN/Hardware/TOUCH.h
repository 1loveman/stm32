#ifndef __TOUCH_H__
#define __TOUCH_H__
#include"stm32f10x.h"
#define TKPORT GPIOA
#define TKA GPIO_Pin_0
#define TKB GPIO_Pin_1
#define TKC GPIO_Pin_2
#define TKD GPIO_Pin_3
void TOUCH_Init(void);
#endif
