#ifndef __FLASH_H__
#define __FLASH_H__
#include"sys.h"

void FLASH_W(u32 add,u16 data);	 //дFLASH����
u16 FLASH_R(u32 add);			 //��FLASH����

#endif
