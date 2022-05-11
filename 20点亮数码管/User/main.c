#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"led.h"

int main(void){
    RCC_Configuration();
    LED_Init();
    while(1){
        u8 c=0;
        while(c<10){
            LED_Show(c++);
            delay_s(1);
        }
    }
}
