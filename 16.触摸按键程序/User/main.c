#include"stm32f10x.h"
#include"sys.h"
#include"led.h"
#include"touch_key.h"

int main(void){
    RCC_Configuration();
    LED_Init();
    TK_Init();
    while(1){
        if(!GPIO_ReadInputDataBit(TKPORT,TK1)){
            GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK2)){
            GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK3)){
            GPIO_Write(LEDPORT,0X0000);
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK4)){
            GPIO_Write(LEDPORT,0X0003);
        }
    }
}
