#include"stm32f10x.h"
#include"sys.h"
#include"TOUCH.h"
#include"RELAY.h"

int main(void){
    RCC_Configuration();
    TOUCH_Init();
    RELAY_Init();
    while(1){
        if(!GPIO_ReadInputDataBit(TOUCHPORT,TOUCHA))RELAY1_Ctrl(1);
        if(!GPIO_ReadInputDataBit(TOUCHPORT,TOUCHB))RELAY1_Ctrl(0);
        if(!GPIO_ReadInputDataBit(TOUCHPORT,TOUCHC))RELAY2_Ctrl(1);
        if(!GPIO_ReadInputDataBit(TOUCHPORT,TOUCHD))RELAY2_Ctrl(0);
    }
}
