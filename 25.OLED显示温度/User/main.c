#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"LM75.h"
#include"OLED.h"
#include"i2c.h"

int main(void){
    u8 TEMP[3]={0};
    Delay_ms(100);
    RCC_Configuration();
    I2C1_Configuration();
    LM75_Get(TEMP);
    OLED_Init();
    OLED_ShowPhoto();
    Delay_s(1);
    OLED_Clear();
    while(1){
        LM75_Get(TEMP);
        OLED_Show16x16CH(0,3*8,0);
        OLED_Show16x16CH(0,5*8,1);
        OLED_Show16x16CH(0,7*8,2);
        OLED_Show16x16CH(0,9*8,3);
        OLED_Show16x16CH(0,11*8,4);
        if(TEMP[0])OLED_Show8x16(2,2*8,'-');
        else OLED_Show8x16(2,2*8,'+');
        OLED_Show8x16(2,3*8,TEMP[1]/100+0x30);
        OLED_Show8x16(2,4*8,TEMP[1]%100/10+0x30);
        OLED_Show8x16(2,5*8,TEMP[1]%10+0x30);
        OLED_Show8x16(2,6*8,'.');
        OLED_Show8x16(2,7*8,TEMP[2]/10+0X30);
        OLED_Show8x16(2,8*8,TEMP[2]%10+0X30);
        OLED_Show16x16CH(2,9*8,5);
        OLED_Show16x16CH(2,11*8,6);
        OLED_Show16x16CH(2,13*8,7);
        Delay_ms(200);
    }
}
