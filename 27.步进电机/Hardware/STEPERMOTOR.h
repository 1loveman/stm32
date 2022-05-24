#ifndef __STEPERMOTOR_H__
#define __STEPERMOTOR_H__
#include"stm32f10x.h"
#include"delay.h"
#define SMPORT GPIOB
#define SMA GPIO_Pin_3
#define SMB GPIO_Pin_4
#define SMC GPIO_Pin_8
#define SMD GPIO_Pin_9

void SMOTOR_Init(void);
void SMOTOR_Stop(void);
void SMOTOR_4S(u8 speed);
void SMOTOR_4R(u8 speed);
void SMOTOR_4L(u8 speed);
void SMOTOR_8R(u8 speed);
void SMOTOR_8L(u8 speed);
#endif
