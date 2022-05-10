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
    u8 i=0;
    while((i++)<8){
        GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(0));
        Delay_us(DEL);
        if(data&0X01){
            GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(1));
            Delay_us(DEL);
        }
        else{
            GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(0));
            Delay_us(DEL);
        }
        GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(1));
        Delay_us(DEL);
        data>>=1;
    }
    GPIO_WriteBit(TM1640PORT,TM1640_SCLK,(BitAction)(0));
    GPIO_WriteBit(TM1640PORT,TM1640_DIN,(BitAction)(0));
    Delay_us(DEL);
}

void TM1640_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin=TM1640_DIN|TM1640_SCLK;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(TM1640PORT,&GPIO_InitStructure);
    TM1640_Start();
    TM1640_Write(TM1640_DSet);
    TM1640_Stop();
    TM1640_Start();
    TM1640_Write(TM1640_SSet);
    TM1640_Stop();
}

void TM1640_Show(u8 address,u8 data){
    u8 val[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0XBF,0X86,0XDB,0XCF,0XE6,0XED,0XFD,0X87,0XFF,0XEF,0X00};
    TM1640_Start();
    TM1640_Write(0XC0+address);
    TM1640_Write(val[data]);
    TM1640_Stop();
}

void TM1640_SLED(u8 address,u8 data){
    TM1640_Start();
    TM1640_Write(0XC0+address);
    TM1640_Write(data);
    TM1640_Stop();
}
