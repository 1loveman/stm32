#ifndef __LM75_H__
#define __LM75_H__
#include"stm32f10x.h"
#include"i2c.h"
#define LM75ADDR 0x9E

void LM75_Get(u8* ptr);
void LM75_PowerDown(void);

#endif
