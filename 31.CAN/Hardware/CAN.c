#include"CAN.h"

u8 CAN_Configuration(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    #if CAN_INT_ENABLE
    NVIC_InitTypeDef NVIC_InitStructure;
    #endif

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

}
