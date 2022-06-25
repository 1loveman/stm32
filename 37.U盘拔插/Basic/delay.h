#ifndef __DELAY_H__
#define __DELAY_H__
#include"stm32f10x.h"
#define AHB 72

void delay_us(u32 us);
void delay_ms(u16 ms);
void delay_s(u16 s);

#endif
