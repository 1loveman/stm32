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
        if(GPIO_ReadInputDataBit(TPORT,TA))SMOTOR_Loop(1,1,3);
        else if(GPIO_ReadInputDataBit(TPORT,TB))SMOTOR_Loop(0,1,3);
        else if(GPIO_ReadInputDataBit(TPORT,TC))SMOTOR_Num(1,100,3);
        else if(GPIO_ReadInputDataBit(TPORT,TD))SMOTOR_Num(0,100,3);
        else SMOTOR_Stop();
    }
}
