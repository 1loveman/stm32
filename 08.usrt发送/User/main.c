#include"stm32f10x.h"
#include"sys.h"
#include"usart.h"


int main(){
	RCC_Configuration();
	USART1_Init(115200);//此单片机硬件只有usart1可用
	while(1){
		USART_SendData(USART1,'H');
		while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE));
//		printf("h");
//		USART1_printf("h");

	}
}
