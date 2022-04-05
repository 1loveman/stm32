#include"delay.h"

void delay_us(u32 us){
	SysTick->LOAD=AHB_INPUT*us;
	SysTick->VAL=0x00;
	SysTick->CTRL=0x00000005;
	while(!(SysTick->CTRL&0x00010000));
	SysTick->CTRL=0x00000004;
}
void delay_ms(u16 ms){
	while(ms--){
		delay_us(1000);
	}
}
void delay_s(u16 s){
	while(s--){
		delay_ms(1000);
	}
}
