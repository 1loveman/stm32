#include"stm32f10x.h"
#include"sys.h"
#include"usart.h"
#include"delay.h"
#include"led.h"
#include"key.h"
#include"buzzer.h"


int main(){
	char ret=0;
	RCC_Configuration();
	LED_Init();
	KEY_Init();
	BUZZER_Init();
	USART1_Init(115200);//此单片机硬件只有usart1可用
	//第一次初始化使其能一开始使用按键
	while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE)){//如果没有数据传入则进入循环，等待数据传入后赋值给ret并跳出循环。
		ret=USART_ReceiveData(USART1);
	}
	while(1){
		u8 l1,l2;
		//终端控制 --仅可输入一个字符
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)){
			ret=USART_ReceiveData(USART1);
			switch(ret){
			case '0':
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
				printf("%c:LED:OFF ",ret);
				break;
			case '1':
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
				printf("%c:LED:ON ",ret);
				break;
			case '2':
				BUZZER_Work();
				printf("%c:BUZZER ",ret);
				break;
			default:
				break;
			}
		}
		
		//按键控制
		switch(ret){
		case '0':
			l1=KEY_LED1_ON();
			if(l1){
				ret='1';
				printf("%c:LED:ON ",ret);	
			}
			break;
		case '1':
			l2=KEY_LED1_OFF();
			if(l2){
				ret='0';
				printf("%c:LED:OFF ",ret);	
			}
			break;
		default:
			break;
		}
		delay_s(1);
	}
}
