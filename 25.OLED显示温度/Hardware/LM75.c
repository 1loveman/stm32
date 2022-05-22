#include"LM75.h"

void LM75_Get(u8* ptr){
    u8 buf[2]={0};
    I2C1_Read_Buffer(LM75ADDR,0X00,buf,2);
    *ptr=0;
    if(buf[0]&0x80){
        *ptr=1;
        buf[0]=~buf[0];
        buf[0]+=1;
    }
    *(++ptr)=0;
    if(buf[0]&0x01)(*ptr)+=1;
    if(buf[0]&0x02)(*ptr)+=2;
    if(buf[0]&0x04)(*ptr)+=4;
    if(buf[0]&0x08)(*ptr)+=8;
    if(buf[0]&0x10)(*ptr)+=16;
    if(buf[0]&0x20)(*ptr)+=32;
    if(buf[0]&0x40)(*ptr)+=64;
    *(++ptr)=0;
    if(buf[1]&0x80)(*ptr)+=50;
    if(buf[1]&0x40)(*ptr)+=25;
    if(buf[1]&0x20)(*ptr)+=12;
}

void LM75_PowerDown(void){
    I2C1_Send_Byte(LM75ADDR,0X01,0X01);
}
