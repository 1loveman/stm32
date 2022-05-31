#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"i2c.h"
#include"TOUCH.h"
#include"OLED.h"
#include"CAN.h"

int main(void){
    RCC_Configuration();
    I2C1_Configuration();
    TOUCH_Init();
    CAN_Configuration();
    OLED_Init();
    while(1){
        
    }
}
