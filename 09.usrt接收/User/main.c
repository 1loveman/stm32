#include"stm32f10x.h"
#include"sys.h"
#include"usart.h"
#include"delay.h"


int main(){
	RCC_Configuration();
	USART1_Init(115200);//此单片机硬件只有usart1可用
	while(1){
//		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)){
//			printf("%c ",USART_ReceiveData(USART1));
//		}
		delay_s(1);
	}
}
