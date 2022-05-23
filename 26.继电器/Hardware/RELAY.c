#include"RELAY.h"

void RELAY_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_InitStructure.GPIO_Pin=RELAY1|RELAY2;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
    GPIO_Init(RELAYPORT,&GPIO_InitStructure);
    GPIO_ResetBits(RELAYPORT,RELAY1|RELAY2);
}

void RELAY1_Ctrl(u8 c){
    GPIO_WriteBit(RELAYPORT,RELAY1,(BitAction)(c));
}

void RELAY2_Ctrl(u8 c){
    GPIO_WriteBit(RELAYPORT,RELAY2,(BitAction)(c));
}
