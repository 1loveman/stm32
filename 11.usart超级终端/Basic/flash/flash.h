#ifndef __FLASH_H__
#define __FLASH_H__
#include"sys.h"
#define FLASH_START_ADDR 0x0801f000//选择写入的页

void FLASH_W(u32 add,u16 data);	 //写FLASH声明
u16 FLASH_R(u32 add);			 //读FLASH声明

#endif
