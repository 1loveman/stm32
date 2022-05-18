#include"OLED.h"

void OLED_Init(void){
    OLED_OFF();
    OLED_Clear();
    OLED_ON();
}

void OLED_ON(void){
    u8 buf[]={
        0XAE,
        0X00,0X10,
        0XD5,0X80,//
        0XA8,0X3F,
        0XD3,0X00,
        0XB0,
        0X40,
        0X8D,0X14,
        0XA1,//
        0XC8,
        0XDA,0X12,
        0X81,0XFF,
        0XD9,0XF1,
        0XDB,0X30,
        0X20,0X00,
        0XA4,
        0XA6,
        0XAF
    };
    I2C1_Send_Buffer(SlaveAddr,COM,buf,28);
}
void OLED_OFF(void){
    u8 buf[]={
        0XAE,
        0X8D,0X10
    };
    I2C1_Send_Buffer(SlaveAddr,COM,buf,3);
}
void OLED_Light(u8 x){
    I2C1_Send_Byte(SlaveAddr,COM,0X81);
    I2C1_Send_Byte(SlaveAddr,COM,x);
}

void OLED_Clear(void){
    u8 j,i;
    for()
}