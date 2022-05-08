#ifndef __DELAY_H__
#define __DELAY_H__
#include"stm32f10x.h"
#define AHB 72

void Delay_us(u32 us);
void Delay_ms(u16 ms);
void Delay_s(u16 s);

#endif
