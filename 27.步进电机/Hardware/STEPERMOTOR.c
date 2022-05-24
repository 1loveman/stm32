#include"STEPERMOTOR.h"

void SMOTOR_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    GPIO_InitStructure.GPIO_Pin=SMA|SMB|SMC|SMD;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
    GPIO_Init(SMPORT,&GPIO_InitStructure);
    SMOTOR_Stop();
}

void SMOTOR_Stop(void){
    GPIO_ResetBits(SMPORT,SMA|SMB|SMC|SMD);
}

void SMOTOR_4S(u8 speed){
    GPIO_ResetBits(SMPORT,SMB|SMD);
    GPIO_SetBits(SMPORT,SMA|SMC);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMC);
    GPIO_SetBits(SMPORT,SMB|SMD);
    delay_ms(speed);
    SMOTOR_Stop();
}

void SMOTOR_4R(u8 speed){
    GPIO_ResetBits(SMPORT,SMC|SMD);
    GPIO_SetBits(SMPORT,SMA|SMB);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMD);
    GPIO_SetBits(SMPORT,SMB|SMC);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMB);
    GPIO_SetBits(SMPORT,SMC|SMD);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMB|SMC);
    GPIO_SetBits(SMPORT,SMD|SMA);
    delay_ms(speed);
    SMOTOR_Stop();
}

void SMOTOR_4L(u8 speed){
    GPIO_ResetBits(SMPORT,SMA|SMB);
    GPIO_SetBits(SMPORT,SMD|SMC);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMD);
    GPIO_SetBits(SMPORT,SMC|SMB);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMC|SMD);
    GPIO_SetBits(SMPORT,SMB|SMA);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMB|SMC);
    GPIO_SetBits(SMPORT,SMA|SMD);
    delay_ms(speed);
    SMOTOR_Stop();
}

void SMOTOR_8R(u8 speed){
    GPIO_ResetBits(SMPORT,SMB|SMC|SMD);
    GPIO_SetBits(SMPORT,SMA);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMC|SMD);
    GPIO_SetBits(SMPORT,SMA|SMB);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMC|SMD);
    GPIO_SetBits(SMPORT,SMB);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMD);
    GPIO_SetBits(SMPORT,SMB|SMC);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMB|SMA|SMD);
    GPIO_SetBits(SMPORT,SMC);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMB);
    GPIO_SetBits(SMPORT,SMC|SMD);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMB|SMC|SMA);
    GPIO_SetBits(SMPORT,SMD);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMB|SMC);
    GPIO_SetBits(SMPORT,SMD|SMA);
    delay_ms(speed);
    SMOTOR_Stop();
}

void SMOTOR_8L(u8 speed){
    GPIO_ResetBits(SMPORT,SMB|SMC|SMA);
    GPIO_SetBits(SMPORT,SMD);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMB);
    GPIO_SetBits(SMPORT,SMD|SMC);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMB|SMD);
    GPIO_SetBits(SMPORT,SMC);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMA|SMD);
    GPIO_SetBits(SMPORT,SMB|SMC);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMC|SMA|SMD);
    GPIO_SetBits(SMPORT,SMB);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMC|SMD);
    GPIO_SetBits(SMPORT,SMB|SMA);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMB|SMC|SMD);
    GPIO_SetBits(SMPORT,SMA);
    delay_ms(speed);
    GPIO_ResetBits(SMPORT,SMB|SMC);
    GPIO_SetBits(SMPORT,SMD|SMA);
    delay_ms(speed);
    SMOTOR_Stop();
}

