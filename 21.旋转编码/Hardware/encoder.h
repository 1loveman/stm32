#ifndef __ENCODER_H__
#define __ENCODER_H__
#include"stm32f10x.h"
#include"delay.h"

#define ECPORTA GPIOA
#define EC_LEFT GPIO_Pin_6
#define EC_PRESS GPIO_Pin_7
#define ECPORTB GPIOB
#define EC_RIGHT GPIO_Pin_2

void EC_Init(void);
u8 EC_Read(void);
#endif
