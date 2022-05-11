#ifndef __LED_H__
#define __LED_H__
#include"sys.h"

#define LEDPORT GPIOA
#define LED1 GPIO_Pin_0
#define LED2 GPIO_Pin_1
#define LED3 GPIO_Pin_2
#define LED4 GPIO_Pin_3
#define LED5 GPIO_Pin_4
#define LED6 GPIO_Pin_5
#define LED7 GPIO_Pin_6
#define LED8 GPIO_Pin_7



void LED_Init(void);
void LED_Show(u8 data);

#endif
