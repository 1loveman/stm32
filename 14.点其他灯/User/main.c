#include"stm32f10x.h"
#include"sys.h"
#include"led.h"

int main(void){
    RCC_Configuration();
    LED_Init();
    while(1){
        GPIO_WriteBit(LEDPORT,LED,(BitAction)(1));
    }
}
