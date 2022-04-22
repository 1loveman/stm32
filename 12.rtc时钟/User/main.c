#include"stm32f10x.h"
#include"sys.h"
#include"led.h"
#include"rtc.h"

int main(){
	RCC_Configuration();
	RTC_Config();
	LED_Init();
	while(1){
		if(!RTC_Get()){
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(rsec%2));
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(rmin%2));
		}
	}
}


