#include"stm32f10x.h"
#include"sys.h"
#include"led.h"
#include"usart.h"
#include"delay.h"


int main(){
	LED_Init();
	RCC_Configuration();
	USART1_Init(115200);//此单片机硬件只有usart1可用	
	USART1_RX_STA=0xC000;
	while(1){
		if(USART1_RX_STA&0xC000){
			if((USART1_RX_STA&0x3FFF)==3){//==的优先级高于&
				if(USART1_RX_BUF[0]=='1'&&USART1_RX_BUF[1]=='O'&&USART1_RX_BUF[2]=='N'){
					GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
					printf("1ON----LED1已经点亮\r\n");
				}
				else if(USART1_RX_BUF[0]=='1'&&USART1_RX_BUF[1]=='O'&&USART1_RX_BUF[2]=='F'){
					GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
					printf("1OF----LED1已经熄灭\r\n");
				}
				else if(USART1_RX_BUF[0]=='2'&&USART1_RX_BUF[1]=='O'&&USART1_RX_BUF[2]=='N'){
					GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));
					printf("2ON----LED2已经点亮\r\n");
				}
				else if(USART1_RX_BUF[0]=='2'&&USART1_RX_BUF[1]=='O'&&USART1_RX_BUF[2]=='F'){
					GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
					printf("2OF----LED2已经熄灭\r\n");
				}
				else{
					printf("输入有误,请重新输入:\r\n");
				}
			}
			else{
				if((USART1_RX_STA&0x3FFF)==0){
					printf("1ON--LED1亮,1OF--LED1灭\r\n");
					printf("2ON--LED2亮,2OF--LED2灭\r\n");
					printf("请输入：\r\n");
				}
				else{
					printf("输入有误！\r\n");
				}
			}
			USART1_RX_STA=0;
		}
			
	}
}
