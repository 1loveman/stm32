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
	USART1_Init(115200);//�˵�Ƭ��Ӳ��ֻ��usart1����
	//��һ�γ�ʼ��ʹ����һ��ʼʹ�ð���
	while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE)){//���û�����ݴ��������ѭ�����ȴ����ݴ����ֵ��ret������ѭ����
		ret=USART_ReceiveData(USART1);
	}
	while(1){
		u8 l1,l2;
		//�ն˿��� --��������һ���ַ�
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
		
		//��������
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
