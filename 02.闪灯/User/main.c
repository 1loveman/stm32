#include"stm32f10x.h"
#include"sys.h"
#include"led.h"
#include"delay.h"

int main(){
	RCC_Configuration();
	LED_Init();
	while(1){
		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(!GPIO_ReadOutputDataBit(LEDPORT,LED1)));
		delay_s(1);
		GPIO_ResetBits(LEDPORT,LED1);
		GPIO_SetBits(LEDPORT,LED2);
		delay_s(1);
	}	

}
