#ifndef __LM75_H__
#define __LM75_H__
#include"i2c.h"

#define SlaveAddr 0x9E

void LM75_GetTemp(u8* Temperature);
void LM75_PowerDown(void);

#endif
