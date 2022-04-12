#include"stm32f10x.h"
#include"sys.h"
#include"led.h"
#include"usart.h"
#include"delay.h"


int main(){
	LED_Init();
	RCC_Configuration();
	USART1_Init(115200);//�˵�Ƭ��Ӳ��ֻ��usart1����	
	USART1_RX_STA=0xC000;
	while(1){
		if(USART1_RX_STA&0xC000){
			if((USART1_RX_STA&0x3FFF)==3){//==�����ȼ�����&
				if(USART1_RX_BUF[0]=='1'&&USART1_RX_BUF[1]=='O'&&USART1_RX_BUF[2]=='N'){
					GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
					printf("1ON----LED1�Ѿ�����\r\n");
				}
				else if(USART1_RX_BUF[0]=='1'&&USART1_RX_BUF[1]=='O'&&USART1_RX_BUF[2]=='F'){
					GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
					printf("1OF----LED1�Ѿ�Ϩ��\r\n");
				}
				else if(USART1_RX_BUF[0]=='2'&&USART1_RX_BUF[1]=='O'&&USART1_RX_BUF[2]=='N'){
					GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));
					printf("2ON----LED2�Ѿ�����\r\n");
				}
				else if(USART1_RX_BUF[0]=='2'&&USART1_RX_BUF[1]=='O'&&USART1_RX_BUF[2]=='F'){
					GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
					printf("2OF----LED2�Ѿ�Ϩ��\r\n");
				}
				else{
					printf("��������,����������:\r\n");
				}
			}
			else{
				if((USART1_RX_STA&0x3FFF)==0){
					printf("1ON--LED1��,1OF--LED1��\r\n");
					printf("2ON--LED2��,2OF--LED2��\r\n");
					printf("�����룺\r\n");
				}
				else{
					printf("��������\r\n");
				}
			}
			USART1_RX_STA=0;
		}
			
	}
}
