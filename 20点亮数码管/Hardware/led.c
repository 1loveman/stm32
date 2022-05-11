#include"led.h"

void LED_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin=LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(LEDPORT,&GPIO_InitStructure);
}

void LED_Show(u8 data){
    u8 val[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
    GPIO_WriteBit(LEDPORT,LED8,(BitAction)(val[data]&0X80));
    GPIO_WriteBit(LEDPORT,LED7,(BitAction)(val[data]&0X40));
    GPIO_WriteBit(LEDPORT,LED6,(BitAction)(val[data]&0X20));
    GPIO_WriteBit(LEDPORT,LED5,(BitAction)(val[data]&0X10));
    GPIO_WriteBit(LEDPORT,LED4,(BitAction)(val[data]&0X08));
    GPIO_WriteBit(LEDPORT,LED3,(BitAction)(val[data]&0X04));
    GPIO_WriteBit(LEDPORT,LED2,(BitAction)(val[data]&0X02));
    GPIO_WriteBit(LEDPORT,LED1,(BitAction)(val[data]&0X01));
}
