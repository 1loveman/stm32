#include"usart.h"

#if 1
#pragma import(__use_no_semihosting)                           
struct __FILE {
	int handle; 
}; 
FILE __stdout;         
_sys_exit(int x){ 
	x = x; 
} 
int fputc(int ch, FILE *f){      
	while((USART_n->SR&0X40)==0);//循环发送,直到发送完毕   
	USART_n->DR = (u8) ch;      
	return ch;
}
#endif 

#if EN_USART1
u8 USART1_REC_BUFF[USART1_REC_LEN];
u16 USART1_REC_STA=0;

void USART1_printf (char *fmt, ...){ 
	char buffer[USART1_REC_LEN+1];  // 数据长度
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART1_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART1_REC_LEN) && (i < strlen(buffer))){
		USART_SendData(USART1, (u8) buffer[i++]);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
	}
	va_end(arg_ptr);
}

void USART1_Init(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC.InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	//

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器 

	

	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;//无奇偶校验
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardWareFlowControl_None;
	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXEN,ENABLE);
	USART_Cmd(USART1,ENABLE);
}

void USART1_IRQHandler(void){
	if(USART1_GetITStatus(USART_IT_RXNE)){
		u8 rec;
		rec=USART_ReceiveData(USART1);
		if(!(USART1_REC_STA&0x8000)){
			if(USART1_REC_STA&0x4000){
				if(rec==0x0a)USART1_REC_STA|=0x8000;
				else USART1_REC_STA=0;//错误
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
