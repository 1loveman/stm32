#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"led.h"
#include"key.h"
#include"flash.h"
#define FLASH_START_ADDR 0x0801f000

int main(){
	u16 a=0;
	RCC_Configuration();
	LED_Init();
	KEY_Init();
	a=FLASH_R(FLASH_START_ADDR);
	GPIO_Write(LEDPORT,a);
	while(1){
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
			a++;
			if(a>3){
				a=0;
			}
			GPIO_Write(LEDPORT,a);
			FLASH_W(FLASH_START_ADDR,a);
			while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
			}
		}
	}
}
