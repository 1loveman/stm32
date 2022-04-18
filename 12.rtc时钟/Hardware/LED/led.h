#ifndef __LED_H__
#define __LED_H__
#include"sys.h"
#define LEDPORT GPIOB 		//宏定义组
#define LED1 GPIO_Pin_0		//宏定义引脚号
#define LED2 GPIO_Pin_1

void LED_Init(void);		//声明LED初始化函数


#endif
