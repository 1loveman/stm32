#include"delay.h"

#define AHB_INPUT 72//�궨��AHBʱ��Ƶ��

void delay_us(u32 us){
	SysTick->LOAD=AHB_INPUT*us;//������װ��ֵ
	SysTick->VAL=0x00;		   //���ü�����ֵ
	SysTick->CTRL=0x00000005;  //����ʱ��Դ��ͬʱ������ʱ
	while(!(SysTick->CTRL&0x00010000));	//�ж��Ƿ��ʱ��0
	SysTick->CTRL=0x00000004;  //����ʱ��Դ��ͬʱ�رռ�ʱ

}
void delay_ms(u16 ms){
	while(ms--){			   //ͨ������1000��usʵ��
		delay_us(1000);
	}
}
void delay_s(u16 s){
	while(s--){				   //ͨ������1000��msʵ��
		delay_ms(1000);
	}
}
