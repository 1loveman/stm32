#include"stm32f10x.h"
#include"sys.h"
#include"usart.h"


int main(){
	RCC_Configuration();
	USART1_Init(115200);//�˵�Ƭ��Ӳ��ֻ��usart1����
	while(1){
		USART_SendData(USART1,'H');
		while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE));
//		printf("h");
//		USART1_printf("h");

	}
}
