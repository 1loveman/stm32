#include"stm32f10x.h"
#include"sys.h"
#include"led.h"
#include"rtc.h"

int main(){
	RCC_Configuration();
	RTC_Config();
	LED_Init();
	while(1){
		
	}
}


