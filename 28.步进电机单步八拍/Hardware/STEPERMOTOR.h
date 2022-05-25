#ifndef __STEPERMOTOR_H__
#define __STEPERMOTOR_H__
#include"stm32f10x.h"
#include"delay.h"
extern u8 STEP;
#define SMPORT GPIOB
#define SMA GPIO_Pin_3
#define SMB GPIO_Pin_4
#define SMC GPIO_Pin_8
#define SMD GPIO_Pin_9

void SMOTOR_Init(void);
void SMOTOR_Stop(void);
void SMOTOR_8A(u8 a,u8 speed);
void SMOTOR_Num(u8 rl,u8 num,u8 speed);
void SMOTOR_Loop(u8 rl,u8 loop,u8 speed);
#endif
