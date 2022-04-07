#include"flash.h"

//��
void FLASH_W(u32 add,u16 data){
	FLASH_Unlock();//����
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//�����־λ
	FLASH_ErasePage(add);  //����ҳ
	FLASH_ProgramHalfWord(add,data); //д�����
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	FLASH_Lock(); //����
}
//д
u16 FLASH_R(u32 add){
	return *((u32*)(add));
}
