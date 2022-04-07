#ifndef __KEY_H__
#define	__KEY_H__
#include"sys.h"

#define KEYPORT GPIOA
#define KEY1 GPIO_Pin_0
#define KEY2 GPIO_Pin_1

void KEY_Init(void);

#endif
