#include"TOUCH.h"

void TOUCH_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin=TOUCHA|TOUCHB|TOUCHC|TOUCHD;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}
