#include"MY1690.h"

void MY1690_Init(void){
    USART3_Init(9600);
    MY1690_Stop();
}
void MY1690_Play(void){
    USART3_printf("\x7e\x03\x11\x12\xef");
}
void MY1690_Pause(void){
    USART3_printf("\x7e\x03\12\x11\xef");
}
void MY1690_PREV(void){
    USART3_printf("\x7e\x03\14\x17\xef");
}
void MY1690_NEXT(void){
    USART3_printf("\x7e\x03\13\x10\xef");
}
void MY1690_VUP(void){
    USART3_printf("\x7e\x03\15\x16\xef");
}
void MY1690_VDOWN(void){
    USART3_printf("\x7e\x03\16\x15\xef");
}
void MY1690_Stop(void){
    USART3_printf("\x7e\x03\x1e\x1d\xef");
}

void MY1690_Cmd1(u8 data){
    USART_SendData(USART3,0X7E);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0X03);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,data);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,(3^data));
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0XEF);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
}
void MY1690_Cmd2(u8 data1,u8 data2){
    USART_SendData(USART3,0X7E);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0X04);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,data1);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,data2);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,(4^data1^data2));
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0XEF);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
}
void MY1690_Cmd3(u8 data1,u16 data2){
    u8 d1=data2/0x100;
    u8 d2=data2%0x100;
    u8 C=5^data1^d1^d2;
    USART_SendData(USART3,0X7E);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0X04);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,data1);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,d1);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,d2);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,C);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
    USART_SendData(USART3,0XEF);
    while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
}
