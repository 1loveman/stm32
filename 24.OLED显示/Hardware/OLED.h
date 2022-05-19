#ifndef __OLED_H__
#define __OLED_H__
#include"stm32f10x.h"
#include"i2c.h"
#define SlaveAddr 0X78
#define COM 0X00
#define DAT 0X40

void OLED_Init(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_Light(u8 x);  
void OLED_Clear(void);
void OLED_Show_8x16(u8 x,u8 y,u16 w);
// void OLED_Show_8X16Buffer(u8 row,u8* ptr);

#endif
