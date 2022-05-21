#include"OLED.h"
#include"ASCLL.h"
#include"CH.h"
#include"PHOTO.h"

void OLED_Init(void){
    OLED_OFF();
    OLED_Clear();
    OLED_ON();
}

void OLED_ON(void){
    u8 buf[]={
        0xAE,
        0X10,0X00,
        0XD5,0X80,
        0XA8,0X3F,
        0XD3,0X00,
        0XB0,
        0X40,
        0X8D,0X14,
        0XA1,
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

void OLED_Clear(void){
    u8 i,j;
    for(i=0xB0;i<0XB8;i++){
        I2C1_Send_Byte(SlaveAddr,COM,i);
        I2C1_Send_Byte(SlaveAddr,COM,0X10);
        I2C1_Send_Byte(SlaveAddr,COM,0X00);
        for(j=0;j<132;j++){
            I2C1_Send_Byte(SlaveAddr,DAT,0X00);
        }
    }
}

void OLED_Show8x16(u8 ROL,u8 COL,u16 Data){
    u8 wi,j;
    COL+=2;
    u8 t=0;
    for(wi=0;wi<2;wi++){
        I2C1_Send_Byte(SlaveAddr,COM,0XB0+ROL);
        I2C1_Send_Byte(SlaveAddr,COM,COL/16+0X10);
        I2C1_Send_Byte(SlaveAddr,COM,COL%16+0X00);
        for(j=0;j<8;j++){
           I2C1_Send_Byte(SlaveAddr,DAT,ASCLLCODE[(Data*16)+(t++)-512]);
        }
        ROL++;
    }
}

void OLED_Show8x16Buffer(u8 ROL,u8 COL,u8* ptr){
    while((*ptr)!='\0'){
        OLED_Show8x16(ROL,COL,*(ptr++));
        COL+=8;
    }       
}

void OLED_Show16x16CH(u8 ROL,u8 COL,u16 Data){
    u8 wi,j,t;
    COL+=2;
    t=0;
    for(wi=0;wi<2;wi++){
        I2C1_Send_Byte(SlaveAddr,COM,0XB0+ROL);
        I2C1_Send_Byte(SlaveAddr,COM,COL/16+0X10);
        I2C1_Send_Byte(SlaveAddr,COM,COL%16+0X00);
        for(j=0;j<16;j++){
            I2C1_Send_Byte(SlaveAddr,DAT,CHCODE[Data*32+(t++)]);
        }
        ROL++;
    }
}

void OLED_ShowPhoto(void){
    u8 wi,j;
    for(wi=0;wi<8;wi++){
        I2C1_Send_Byte(SlaveAddr,COM,0XB0+wi);
        I2C1_Send_Byte(SlaveAddr,COM,0X10);
        I2C1_Send_Byte(SlaveAddr,COM,0X02);
        for(j=0;j<128;j++){
            I2C1_Send_Byte(SlaveAddr,DAT,PHOTOCODE[j+wi*128]);
        }
    }
}

