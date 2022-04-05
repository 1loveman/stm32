#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"led.h"
#include"key.h"
#include"flash.h"
#include"buzzer.h"


int main(){
	u16 a=0;//根据写入选择半字或者字
	RCC_Configuration();
	LED_Init();
	KEY_Init();
	BUZZER_Init();
	a=FLASH_R(FLASH_START_ADDR);//将值写回a
	BUZZER_Work();
	GPIO_Write(LEDPORT,a|0x0020&GPIO_ReadOutputData(LEDPORT));
	while(1){
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
			a++;
			if(a>3){
				a=0;
			}
			BUZZER_Work();
			GPIO_Write(LEDPORT,a|0x0020&GPIO_ReadOutputData(LEDPORT));
			FLASH_W(FLASH_START_ADDR,a);//写入半字
			while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
			BUZZER_Work4();
			}
		}
	}
}
