#include"touch_key.h"

void TK_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin=TK1|TK2|TK3|TK4;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(TKPORT,&GPIO_InitStructure);
}
