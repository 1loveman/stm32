#ifndef __KEY_H__
#define	__KEY_H__
#include"sys.h"
#include"led.h"
#include"delay.h"

#define KEYPORT GPIOA
#define KEY1 GPIO_Pin_0
#define KEY2 GPIO_Pin_1

void KEY_Init(void);
u8 KEY_LED1_ON(void);
u8 KEY_LED1_OFF(void);

#endif
