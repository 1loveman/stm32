#include"LM75.h"

void LM75_GetTemp(u8* Temperature){
    u8 Buf[2]={0};
    u8 t=0;
    I2C1_Read_Buffer(SlaveAddr,0x00,Buf,2);
    *Temperature=0;
    if(Buf[0]&0x80){
        *Temperature=1;
        Buf[0]=~Buf[0];
        Buf[0]++;
    }
    if(Buf[0]&0x01)t+=1;
    if(Buf[0]&0x02)t+=2;
    if(Buf[0]&0x04)t+=4;
    if(Buf[0]&0x08)t+=8;
    if(Buf[0]&0x10)t+=16;
    if(Buf[0]&0x20)t+=32;
    if(Buf[0]&0x40)t+=64;
    *(++Temperature)=t;
    t=0;
    if(Buf[1]&0x20)t+=12;
    if(Buf[1]&0x40)t+=25;
    if(Buf[1]&0x80)t+=50;
    *(++Temperature)=t;
}

void LM75_PowerDown(void){
    I2C1_Send_Byte(SlaveAddr,0x01,1);
}
