#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"i2c.h"
#include"usart.h"
#include"TOUCH.h"
#include"ROTARY.h"
#include"MY1690.h"
#include"OLED.h"

int main(void){
    delay_ms(200);
    RCC_Configuration();
    I2C1_Configuration();
    TOUCH_Init();
    ROTARY_Init();
    MY1690_Init();
    OLED_Init();
    OLED_Show8x16Buf(0,0*8,"Music Player");
    OLED_Show8x16Buf(3,0*8,"MP3 PLAY TEST");
    while(1){
        if(!GPIO_ReadInputDataBit(TKPORT,TK1)){
            MY1690_PREV();
            OLED_Show8x16Buf(6,0*8,"----PREV----");
            while(!GPIO_ReadInputDataBit(TKPORT,TK1));
            delay_s(1);
            OLED_Show8x16Buf(6,0*8,"            ");
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK2)){
            MY1690_NEXT();
            OLED_Show8x16Buf(6,0*8,"----NEXT----");
            while(!GPIO_ReadInputDataBit(TKPORT,TK2));
            delay_s(1);
            OLED_Show8x16Buf(6,0*8,"            ");
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK3)){
            MY1690_Cmd2(0x31,0x30);
            OLED_Show8x16Buf(6,0*8,"----VOLULE----");
            while(!GPIO_ReadInputDataBit(TKPORT,TK3));
            delay_s(1);
            OLED_Show8x16Buf(6,0*8,"              ");
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK4)){
            MY1690_Stop();
            OLED_Show8x16Buf(6,0*8,"----STOP----");
            while(!GPIO_ReadInputDataBit(TKPORT,TK4));
            delay_s(1);
            OLED_Show8x16Buf(6,0*8,"            ");
        }
    }
}
