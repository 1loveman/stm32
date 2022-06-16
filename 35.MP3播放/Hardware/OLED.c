#include"OLED.h"
#include"ascall.h"
#include"word.h"
#include"photo.h"

void OLED_ON(void){
    u8 buf[28]={
        0XAE,
        0X00,0X10,
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
    I2C1_SendBuf(OLEDADDR,COMADDR,buf,28);
}

void OLED_CLEAR(void){
    u8 i,j;
    for(i=0;i<0XB8;i++){
        I2C1_SendByte(OLEDADDR,COMADDR,i);
        I2C1_SendByte(OLEDADDR,COMADDR,0X10);
        I2C1_SendByte(OLEDADDR,COMADDR,0X00);
        for(j=0;j<132;j++){
            I2C1_SendByte(OLEDADDR,DATAADDR,0X00);
        }
    }
}

void OLED_OFF(void){
    u8 buf[3]={
        0XAE,
        0X8D,0X10
    };
    I2C1_SendBuf(OLEDADDR,COMADDR,buf,3);
}

void OLED_Init(void){
    OLED_OFF();
    OLED_CLEAR();
    OLED_ON();
}

void OLED_Show8x16(u8 col,u8 rol,u16 data){
    u8 i=0;
    u8 j,x=0;
    while((i++)<2){
        I2C1_SendByte(OLEDADDR,COMADDR,0XB0+(col++));
        I2C1_SendByte(OLEDADDR,COMADDR,0X02+rol%16);
        I2C1_SendByte(OLEDADDR,COMADDR,0x10+rol/16);
        for(j=0;j<8;j++){
            I2C1_SendByte(OLEDADDR,DATAADDR,ASC_TAB[data*16+(x++)-512]);
        }
    }
    
}

void OLED_Show8x16Buf(u8 col,u8 rol,u8* dptr){
    while((*dptr)!='\0'){
        OLED_Show8x16(col,(rol++)*8,*dptr++);
    }
}

void OLED_Show16x16(u8 col,u8 rol,u16 data){
    u8 i=0;
    u8 j,x=0;
    while((i++)<2){
        I2C1_SendByte(OLEDADDR,COMADDR,0XB0+(col++));
        I2C1_SendByte(OLEDADDR,COMADDR,0X02+rol%16);
        I2C1_SendByte(OLEDADDR,COMADDR,0X10+rol/16);
        for(j=0;j<16;j++){
            I2C1_SendByte(OLEDADDR,DATAADDR,WORD_TAB[data*32+(x++)]);
        }
    }
}

void OLED_ShowPhoto(void){
    u8 i=0;
    u8 j;
    while(i<8){
        I2C1_SendByte(OLEDADDR,COMADDR,0XB0+i);
        I2C1_SendByte(OLEDADDR,COMADDR,0x10);
        I2C1_SendByte(OLEDADDR,COMADDR,0x02);
        for(j=0;j<128;j++){
            I2C1_SendByte(OLEDADDR,DATAADDR,PHOTO_TAB[j+i*128]);
        }
    }
}
