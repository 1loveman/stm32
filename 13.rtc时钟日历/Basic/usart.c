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
    while(!(USARTn->SR&0X0040));
    USARTn->DR=(u8)ch;
    return ch;
}

#endif 

#if EN_USART1
u8 USART1_RX_BUFF[USART1_REC_LEN];
u16 USART1_RX_STA=0;

void USART1_printf(char* fmt,...){
    char buffer[USART1_REC_LEN+1];
    u8 i=0;
    va_list arg_ptr;
    va_start(arg_ptr,fmt);
    vsnprintf(buffer,USART1_REC_LEN+1,fmt,arg_ptr);
    while((i<USART1_REC_LEN)&&(i<strlen(buffer))){
        USART_SendData(USART1,(u8)buffer[i++]);
        while(!(USART_GetFlagStatus(USART1,USART_FLAG_TC)));
    }
    va_end(arg_ptr);
}

void USART1_Init(u32 bound){
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
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
    USART_Init(USART1,&USART_InitStructure);
    USART_Cmd(USART1,ENABLE);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

void USART1_IRQHandler(void){
    u8 rec;
    if((USART_GetITStatus(USART1,USART_IT_RXNE))){
        rec=USART_ReceiveData(USART1);
        printf("%c",rec);
        if(!(USART1_RX_STA&0X8000)){
            if(USART1_RX_STA&0X4000){
                if(rec==0X0A)USART1_RX_STA|=0X8000;
                else USART1_RX_STA=0;
            }
            else{
                if(rec==0X0D)USART1_RX_STA|=0X4000;
                else{
                    USART1_RX_BUFF[(USART1_RX_STA++)&0X3FFF]=rec;
                    if((USART1_RX_STA&0X3FFF)>USART1_REC_LEN-1){
                        USART1_RX_STA=0;
                    }
                }
            }
        }
    }
}

#endif
