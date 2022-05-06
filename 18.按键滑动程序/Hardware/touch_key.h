#ifndef __TOUCH_KEY_H__
#define __TOUCH_KEY_H__
#include"sys.h"

#define TKPORT GPIOA
#define TK1 GPIO_Pin_0
#define TK2 GPIO_Pin_1
#define TK3 GPIO_Pin_2
#define TK4 GPIO_Pin_3

void TK_Init(void);

#endif
