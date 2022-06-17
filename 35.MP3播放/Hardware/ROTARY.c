#include"ROTARY.h"

u8 key;
u8 cont;


void ROTARY_Init(void){
    GPIO_InitTypeDef GPIO_InitS;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitS.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitS);
    GPIO_InitS.GPIO_Pin=GPIO_Pin_2;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_InitS);
}

u8 ROTARY_GetStaus(void){
    u8 F,a=0;
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6))key=0;
    if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)&&(!key)){
        delay_us(100);
        F=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2);
        delay_ms(3);
        if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)){
            if(!F){
                a=3;
            }else{
                a=1;
            }
            cont=0;
            while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)&&((cont++)<60000)){
                key=1;
                delay_us(20);
            }
        }
    }
    if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)){
        delay_ms(20);
        if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)){
            a=2;
            while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7));
        }
    }
    return a;
}
