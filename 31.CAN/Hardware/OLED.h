#ifndef __OLED_H__
#define __OLED_H__
#include"stm32f10x.h"
#include"i2c.h"
#define SlaveAddr 0x78
#define COM 0X00
#define DAT 0X40

void OLED_Init(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_Clear(void);
void OLED_Show8x16(u8 ROL,u8 COL,u16 Data);
void OLED_Show8x16Buffer(u8 ROL,u8 COL,u8* ptr);
void OLED_Show16x16CH(u8 ROL,u8 COL,u16 Data);
void OLED_ShowPhoto(void);
#endif
