#include"key.h"

void KEY_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin=KEY1|KEY2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(KEYPORT,&GPIO_InitStructure);	
}
u8 KEY_LED1_OFF(void){
	if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
		delay_ms(20);
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
				
		}
		while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
		return 1;
	}
	return 0;
}

u8 KEY_LED1_ON(void){
	if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
		delay_ms(20);
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
				
		}
		while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
		return 1;
	}
	return 0;
}
