#include"usart.h"

#if 1
#pragma import(__use_no_semihosting)
struct __FILE{
    int handle;
};
FILE __stdout;
void _sys_exit(int x){
    x=x;
}

int fputc(int ch,FILE* fp){
    while(!(USARTN->SR&0X0040));
    USARTN->DR=(u8)ch;
    return ch;
}
#endif


#if EN_USART3
u8 USART3_RX_BUFF[USART3_REC_LEN];

void USART3_printf(char* fmt,...){
    char buf[USART3_REC_LEN+1];
    u8 i=0;
    va_list arg_ptr;
    va_start(arg_ptr,fmt);
    vsnprintf(buf,USART3_REC_LEN+1,fmt,arg_ptr);
    while((i<USART3_REC_LEN)&&(i<strlen(buf))){
        USART_SendData(USART3,(u8)buf[i++]);
        while(!(USART3->SR&0X40));
    }
    va_end(arg_ptr);
}

void USART3_Init(u32 bound){
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    
    USART_InitStructure.USART_BaudRate=bound;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_Init(USART3,&USART_InitStructure);
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3,ENABLE);
}

void USART3_IRQHandler(void){
    if(USART_GetITStatus(USART3,USART_IT_RXNE)){
        USART3_RX_BUFF[0]=USART_ReceiveData(USART3);
    }
}

#endif
