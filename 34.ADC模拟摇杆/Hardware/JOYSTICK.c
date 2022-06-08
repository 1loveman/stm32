#include"JOYSTICK.h"

void JOYSTICK_Init(void){
    GPIO_InitTypeDef GPIO_InitS;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitS.GPIO_Pin=JOYSTICK1;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(JOYSTICKPORT,&GPIO_InitS);
}
