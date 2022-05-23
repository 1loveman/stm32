#ifndef __TOUCH_H__
#define __TOUCH_H__
#include"stm32f10x.h"
#define TOUCHPORT GPIOA
#define TOUCHA GPIO_Pin_0
#define TOUCHB GPIO_Pin_1
#define TOUCHC GPIO_Pin_2
#define TOUCHD GPIO_Pin_3

void TOUCH_Init(void);

#endif
