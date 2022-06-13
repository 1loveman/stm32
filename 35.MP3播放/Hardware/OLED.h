#ifndef __OLED_H__
#define __OLED_H__
#include"stm32f10x.h"
#include"i2c.h"
#define OLEDADDR 0X78
#define COMADDR 0X00
#define DATAADDR 0X40

void OLED_Init(void);
void OLED_Show8x16(u8 col,u8 rol,u16 data);
void OLED_Show8x16Buf(u8 col,u8 rol,u8* dptr);
void OLED_Show16x16(u8 col,u8 rol,u16 data);
void OLED_ShowPhoto(void);

#endif
