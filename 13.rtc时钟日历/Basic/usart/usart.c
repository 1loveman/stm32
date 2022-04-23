#include"usart.h"

#if EN_USART1
u8 USART1_REC_BUFF[USART1_REC_LEN];
u16 USART1_REC_STA=0;

void USART1_Init(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	//

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Output_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=bound;//
	USART_InitStructure.USART_WordLength=USART1_REC_LEN;
	USART_InitStructure.


}

void USART1_IRQHandler(void){
	if(USART1_GetITStatus(USART_IT_RXNE)){
		u8 rec;
		rec=USART_ReceiveData(USART1);
		if(!(USART1_REC_STA&0x8000)){
			if(USART1_REC_STA&0x4000){
				if(rec==0x0a)USART1_REC_STA|=0x8000;
				else USART1_REC_STA=0;//´íÎó
			}
			else{
				if(rec==0x0d)USART1_REC_STA|=0x4000;
				else{
					USART1_REC_BUFF[(USART1_REC_STA++)&0x3FFF]=rec;
					if((USART1_REC_STA&0x3FFF)>=200){
						USART1_REC_STA=0;
					}
				}
			}
		}
	}

}

#endif
