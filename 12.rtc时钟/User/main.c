#include"stm32f10x.h"
#include"sys.h"
#include"led.h"
#include"rtc.h"

int main(){
	RCC_Configuration();
	LED_Init();
	RTC_Config();
	while(1){
		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(RTC_GetCounter()%2));
		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(RTC_GetCounter()%2));
	}
}
