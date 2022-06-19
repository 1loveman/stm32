#include"MY1690.h"

void MY1690_Init(void){
    USART3_Init(9600);
    MY1690_Stop();
}
void MY1690_Play(void){
    USART3_printf("\x7E\x03\x11\x12\xEF");
}
void MY1690_Pause(void){
    USART3_printf("\x7E\x03\x12\x11\xEF");
}
void MY1690_NEXT(void){
    USART3_printf("\x7E\x03\x13\x10\xEF");
}
void MY1690_PREV(void){
    USART3_printf("\x7E\x03\x14\x17\xEF");
}
void MY1690_VUP(void){
    USART3_printf("\x7E\x03\x15\x16\xEF");
}
void MY1690_VDOWN(void){
    USART3_printf("\x7E\x03\x16\x15\xEF");
}
void MY1690_Stop(void){
    USART3_printf("\x7E\x03\x1E\x1D\xEF");
}

void MY1690_Cmd1(u8 code){
    USART_SendData(USART3,0X7E);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0X03);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,code);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,3^code);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0XEF);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
}
void MY1690_Cmd2(u8 code ,u8 param){
    USART_SendData(USART3,0X7E);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0X04);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,code);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,param);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,4^code^param);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0XEF);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
}
void MY1690_Cmd3(u8 code ,u16 param){
    u8 p1=param/0x100;
    u8 p2=param%0x100;
    USART_SendData(USART3,0X7E);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0X05);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,code);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,p1);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,p2);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,5^code^p1^p2);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0XEF);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
}

