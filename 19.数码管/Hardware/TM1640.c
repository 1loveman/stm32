#include"TM1640.h"

void TM1640_Start(void){
    GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(1));
    GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(1));
    Delay_us(DEL);
    GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(0));
    Delay_us(DEL);
    GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(0));
    Delay_us(DEL);
}

void TM1640_Stop(void){
    GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(1));
    GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(0));
    Delay_us(DEL);
    GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(1));
    Delay_us(DEL);
}

void TM1640_Write(u8 data){
    int i=0;
    GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(0));
    GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(0));
    while((i++)<8){
        GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(0));
        Delay_us(DEL);
        if(data&0x01){
            GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(1));
            Delay_us(DEL);
        }
        else{
            GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(0));
            Delay_us(DEL);
        }
        GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(1));
        Delay_us(DEL);
        data=data>>1;
    }
    GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(0));
    GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(0));
}