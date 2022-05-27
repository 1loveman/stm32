#include"RS485.h"

void RS485_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin=RS4RE;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(RS4PORT,&GPIO_InitStructure);
    GPIO_WriteBit(RS4PORT,RS4RE,(BitAction)(0));
}

void RS485_printf(char* fmt,...){
    char buf[USART3_REC_LEN+1];
    u8 i=0;
    va_list arg_ptr;
    GPIO_WriteBit(RS4PORT,RS4RE,(BitAction)(1));
    va_start(arg_ptr,fmt);
    vsnprintf(buf,USART3_REC_LEN+1,fmt,arg_ptr);
    while((i<USART3_REC_LEN)&&(i<strlen(buf))){
        USART_SendData(USART3,(u8)buf[i++]);
        while(!(USART3->SR&0X40));
    }
    va_end(arg_ptr);
    GPIO_WriteBit(RS4PORT,RS4RE,(BitAction)(0));
}
