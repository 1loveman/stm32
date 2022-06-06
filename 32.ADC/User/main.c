#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"i2c.h"
#include"adc.h"
#include"OLED.h"

extern vu16 ADC_DMA_IN5;

int main(void){
    Delay_ms(100);
    RCC_Configuration();
    I2C1_Configuration();
    ADC_Configuration();
    OLED_Init();
    OLED_Show8x16Buffer(0,0*8,"ADC  TESE");
    OLED_Show8x16Buffer(2,0*8,"RES:     ");
    while(1){
        OLED_Show8x16(2,5*8,ADC_DMA_IN5/1000+0X30);
        OLED_Show8x16(2,6*8,ADC_DMA_IN5%1000/100+0X30);
        OLED_Show8x16(2,7*8,ADC_DMA_IN5%100/10+0X30);
        OLED_Show8x16(2,8*8,ADC_DMA_IN5%10+0X30);
        Delay_ms(500);
    }
}
