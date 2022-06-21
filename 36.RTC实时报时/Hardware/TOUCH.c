#include"TOUCH.h"

void TOUCH_Init(void){
    GPIO_InitTypeDef GPIO_InitS;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitS.GPIO_Pin=TK1|TK2|TK3|TK4;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(TKPORT,&GPIO_InitS);
}
