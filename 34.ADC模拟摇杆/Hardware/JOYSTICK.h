#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__
#include"stm32f10x.h"
#define JOYSTICKPORT GPIOB
#define JOYSTICK1 GPIO_Pin_2

void JOYSTICK_Init(void);

#endif
