#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"led.h"

int main(){
	u8 Menu=0;
	u16 t=1;//因为定义时就是16位。
	
	RCC_Configuration();
	LED_Init();
	while(1){
		u16 i=0;
		//变亮循环
		if(!Menu){
			while(i++<10){
				GPIO_SetBits(LEDPORT,LED1);
				delay_us(t);
				GPIO_ResetBits(LEDPORT,LED1);
				delay_us(501-t);
			}	
			t++;
			if(t==500){
				Menu=1;
			}
		}
		//变暗循环
		if(Menu){
			while(i++<10){
				GPIO_SetBits(LEDPORT,LED1);
				delay_us(t);
				GPIO_ResetBits(LEDPORT,LED1);
				delay_us(501-t);
			}
			t--;
			if(t==1){
				Menu=0;
			}
		}	
	}
}
//呼吸灯的实质---调节占空比。

