#include"stm32f10x.h"
#include"sys.h"
#include"i2c.h"
#include"adc.h"
#include"delay.h"
#include"JOYSTICK.h"
#include"OLED.h"
extern vu16 ADC1_DMA_IN[2];

int main(void){
    Delay_ms(100);
    RCC_Configuration();
    I2C1_Configuration();
    ADC1_Configuration();
    OLED_Init();
    OLED_Show8x16Buffer(0,0*8,"ADC TSET");
    OLED_Show8x16Buffer(2,0*8,"X=      ");
    OLED_Show8x16Buffer(4,0*8,"Y=      ");
    while(1){
        OLED_Show8x16(2,3*8,ADC1_DMA_IN[0]/1000+0X30);
        OLED_Show8x16(2,4*8,ADC1_DMA_IN[0]%1000/100+0X30);
        OLED_Show8x16(2,5*8,ADC1_DMA_IN[0]%100/10+0X30);
        OLED_Show8x16(2,6*8,ADC1_DMA_IN[0]%10+0X30);
        OLED_Show8x16(4,3*8,ADC1_DMA_IN[1]/1000+0X30);
        OLED_Show8x16(4,4*8,ADC1_DMA_IN[1]%1000/100+0X30);
        OLED_Show8x16(4,5*8,ADC1_DMA_IN[1]%100/10+0X30);
        OLED_Show8x16(4,6*8,ADC1_DMA_IN[1]%10+0X30);
        if(!GPIO_ReadInputDataBit(JOYSTICKPORT,JOYSTICK1))OLED_Show8x16(6,0*8,'Z');
        else OLED_Show8x16(6,0*8,' ');
        Delay_ms(500);
    }
}
