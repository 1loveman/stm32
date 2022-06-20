#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"i2c.h"
#include"usart.h"
#include"rtc.h"
#include"MY1690.h"
#include"OLED.h"

int main(void){
    delay_ms(400);
    RCC_Configuration();
    RTC_Configuration();
    I2C1_Configuration();
    OLED_Init();
    MY1690_Init();
    OLED_Show8x16Buf(0,0*8,"RTC STRIKE");
    while(1){
        
    }
}
