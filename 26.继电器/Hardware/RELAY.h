#ifndef __RELAY_H__
#define __RELAY_H__
#include"stm32f10x.h"
#define RELAYPORT GPIOA
#define RELAY1 GPIO_Pin_14
#define RELAY2 GPIO_Pin_13

void RELAY_Init(void);
void RELAY1_Ctrl(u8 c);
void RELAY2_Ctrl(u8 c);

#endif
