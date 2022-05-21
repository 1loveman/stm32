#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"OLED.h"
#include"i2c.h"

int main(void){
    Delay_ms(100);
    RCC_Configuration();
    I2C1_Configuration();
    OLED_Init();
    while(1){
        OLED_ShowPhoto();
        Delay_ms(200);
    }
}
