#include"flash.h"

//读
void FLASH_W(u32 add,u16 data){
	FLASH_Unlock();//解锁
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
	FLASH_ErasePage(add);  //擦除页
	FLASH_ProgramHalfWord(add,data); //写入半字
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	FLASH_Lock(); //锁定
}
//写
u16 FLASH_R(u32 add){
	return *((u32*)(add));
}
