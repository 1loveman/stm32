#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"TOUCH.h"
#include"STEPERMOTOR.h"

int main(void){
    RCC_Configuration();
    TOUCH_Init();
    SMOTOR_Init();
    while(1){
        if(GPIO_ReadInputDataBit(TPORT,TA))SMOTOR_4R(3);
        else if(GPIO_ReadInputDataBit(TPORT,TB))SMOTOR_4L(3);
        else if(GPIO_ReadInputDataBit(TPORT,TC))SMOTOR_8R(3);
        else if(GPIO_ReadInputDataBit(TPORT,TD))SMOTOR_8L(3);
        else SMOTOR_Stop();
    }
}
