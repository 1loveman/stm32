#include"delay.h"

#define AHB_INPUT 72//宏定义AHB时钟频率

void delay_us(u32 us){
	SysTick->LOAD=AHB_INPUT*us;//设置重装载值
	SysTick->VAL=0x00;		   //设置计数初值
	SysTick->CTRL=0x00000005;  //设置时钟源，同时启动计时
	while(!(SysTick->CTRL&0x00010000));	//判断是否计时到0
	SysTick->CTRL=0x00000004;  //设置时钟源，同时关闭计时

}
void delay_ms(u16 ms){
	while(ms--){			   //通过调用1000次us实现
		delay_us(1000);
	}
}
void delay_s(u16 s){
	while(s--){				   //通过调用1000次ms实现
		delay_ms(1000);
	}
}
