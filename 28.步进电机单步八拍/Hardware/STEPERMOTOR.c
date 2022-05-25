#include"STEPERMOTOR.h"

u8 STEP;

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


void SMOTOR_8A(u8 a,u8 speed){
    switch(a){
    case 0:GPIO_ResetBits(SMPORT,SMB|SMC|SMD);
        GPIO_SetBits(SMPORT,SMA);
        break;
    case 1:GPIO_ResetBits(SMPORT,SMC|SMD);
        GPIO_SetBits(SMPORT,SMA|SMB);
        break;
    case 2:GPIO_ResetBits(SMPORT,SMA|SMC|SMD);
        GPIO_SetBits(SMPORT,SMB);
        break;
    case 3:GPIO_ResetBits(SMPORT,SMA|SMD);
        GPIO_SetBits(SMPORT,SMB|SMC);
        break;
    case 4:GPIO_ResetBits(SMPORT,SMB|SMA|SMD);
        GPIO_SetBits(SMPORT,SMC);
        break;
    case 5:GPIO_ResetBits(SMPORT,SMA|SMB);
        GPIO_SetBits(SMPORT,SMC|SMD);
        break;
    case 6:GPIO_ResetBits(SMPORT,SMB|SMC|SMA);
        GPIO_SetBits(SMPORT,SMD);
        break;
    case 7:GPIO_ResetBits(SMPORT,SMB|SMC);
        GPIO_SetBits(SMPORT,SMD|SMA);
        break;
    default:
        break;
    }
    delay_ms(speed);
    SMOTOR_Stop();
}

void SMOTOR_Num(u8 rl,u8 num,u8 speed){
    while(num--){
        if(rl){
            if((++STEP)>7)STEP=0;
        }
        else{
            if((STEP--)==0)STEP=7;
        }
        SMOTOR_8A(STEP,speed);
    }
}

void SMOTOR_Loop(u8 rl,u8 loop,u8 speed){
    SMOTOR_Num(rl,loop*4076,speed);
}
