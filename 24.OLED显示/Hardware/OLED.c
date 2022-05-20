#include"OLED.h"
#include"ASCLL.h"

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
    for(i=0XB0;i<0XB8;i++){
        I2C1_Send_Byte(SlaveAddr,COM,i);
        I2C1_Send_Byte(SlaveAddr,COM,0X10);
        I2C1_Send_Byte(SlaveAddr,COM,0X00);
        for(j=0;j<132;j++){
            I2C1_Send_Byte(SlaveAddr,DAT,0X00);
        }
    }
}

void OLED_Show_8x16(u8 x,u8 y,u16 w){
    u8 wi,i,t;
    y+=2;
    t=0;
    for(wi=0;wi<2;wi++){
        I2C1_Send_Byte(SlaveAddr,COM,0XB0+x);
        I2C1_Send_Byte(SlaveAddr,COM,y/16+0x10);
        I2C1_Send_Byte(SlaveAddr,COM,y%16);
        for(i=0;i<8;i++){
            I2C1_Send_Byte(SlaveAddr,DAT,AscllCode[(w*16)+t-512]);
            t++;
        }
        x++;
    }
}
void OLED_Show_8X16Buffer(u8 row,u8 col,u8* ptr){
    while(*ptr!='\0'){
        OLED_Show_8x16(row,col*8,*(ptr++));
        col++;
    }
}
