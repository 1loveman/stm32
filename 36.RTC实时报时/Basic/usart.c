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

int fputc(int ch,FILE* f){
    while(!(USARTN->SR&0X40));
    USARTN->DR=(u8)ch;
    return ch;
}

#endif

#if EN_USART1
u16 USART1_RX_STA=0;
u8 USART1_RX_BUF[USART1_REC_LEN];

void USART1_printf(char* fmt,...){
    char buf[USART1_REC_LEN+1];
    u8 i=0;
    va_list arg_ptr;
    va_start(arg_ptr,fmt);
    vsnprintf(buf,USART1_REC_LEN+1,fmt,arg_ptr);
    while((i<USART1_REC_LEN)&&(i<strlen(buf))){
        USART_SendData(USART1,(u8)buf[i++]);
        while(!(USART1->SR&0X40));
    }
    va_end(arg_ptr);
}

void USART1_Init(u32 bound){
    GPIO_InitTypeDef GPIO_InitS;
    NVIC_InitTypeDef NVIC_InitS;
    USART_InitTypeDef USART_InitS;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
    
    GPIO_InitS.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitS);
    GPIO_InitS.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&GPIO_InitS);

    NVIC_InitS.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitS.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitS.NVIC_IRQChannelSubPriority=3;
    NVIC_InitS.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitS);

    USART_InitS.USART_BaudRate=bound;
    USART_InitS.USART_WordLength=USART_WordLength_8b;
    USART_InitS.USART_StopBits=USART_StopBits_1;
    USART_InitS.USART_Parity=USART_Parity_No;
    USART_InitS.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitS.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_Init(USART1,&USART_InitS);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1,ENABLE);
}

void USART1_IRQHandler(void){
    u8 res;
    if(USART_GetITStatus(USART1,USART_IT_RXNE)){
        res=USART_ReceiveData(USART1);
        USART1_printf("%c",res);
        if(!(USART1_RX_STA&0X8000)){
            if(USART1_RX_STA&0X4000){
                if(res==0x0A)USART1_RX_STA|=0X8000;
                else USART1_RX_STA=0;
            }
            else{
                if(res==0x0D)USART1_RX_STA|=0X4000;
                else{
                    USART1_RX_BUF[(USART1_RX_STA++)&0X3FFF]=res;
                    if((USART1_RX_STA&0X3FFF)>(USART1_REC_LEN-1)){
                        USART1_RX_STA=0;
                    }
                }
            }
        }
    }
}



#endif


#if EN_USART3

u8 USART3_RX_STA;

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
    GPIO_InitTypeDef GPIO_InitS;
    NVIC_InitTypeDef NVIC_InitS;
    USART_InitTypeDef USART_InitS;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

    GPIO_InitS.GPIO_Pin=GPIO_Pin_11;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitS);
    GPIO_InitS.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitS);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitS.NVIC_IRQChannel=USART3_IRQn;
    NVIC_InitS.NVIC_IRQChannelSubPriority=0;
    NVIC_InitS.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitS);

    USART_InitS.USART_BaudRate=bound;
    USART_InitS.USART_WordLength=USART_WordLength_8b;
    USART_InitS.USART_StopBits=USART_StopBits_1;
    USART_InitS.USART_Parity=USART_Parity_No;
    USART_InitS.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitS.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
    USART_Init(USART3,&USART_InitS);
    USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);
    USART_Cmd(USART3,ENABLE);
}

void USART3_IRQHandler(void){
    u8 Res;
    if(!USART_GetITStatus(USART3, USART_IT_RXNE)){
        Res =USART_ReceiveData(USART3);
        if(Res=='S'){          
            USART3_RX_STA=1;     
        }else if(Res=='K'){           
            USART3_RX_STA=2; 
        }            
    }
}

#endif

