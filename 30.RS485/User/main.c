#include"stm32f10x.h"
#include"sys.h"
#include"usart.h"
#include"i2c.h"
#include"delay.h"
#include"OLED.h"
#include"TOUCH.h"
#include"RS485.h"

int main(void){
    Delay_ms(100);
    RCC_Configuration();
    I2C1_Configuration();
    USART3_Init(115200);
    TOUCH_Init();
    RS485_Init();
    OLED_Init();
    OLED_Show8x16Buffer(0,0*8,"RS485 TEST");
    OLED_Show8x16Buffer(2,0*8,"TX:     RX:     ");
    while(1){
        if(!GPIO_ReadInputDataBit(TKPORT,TKA)){
            RS485_printf("A");
            OLED_Show8x16(2,4*8,'A');
            OLED_Show8x16(2,12*8,USART3_RX_BUFF[0]);
        }
        else if(!GPIO_ReadInputDataBit(TKPORT,TKB)){
            RS485_printf("B");
            OLED_Show8x16(2,4*8,'B');
            OLED_Show8x16(2,12*8,USART3_RX_BUFF[0]);
        }
        else if(!GPIO_ReadInputDataBit(TKPORT,TKC)){
            RS485_printf("C");
            OLED_Show8x16(2,4*8,'C');
            OLED_Show8x16(2,12*8,USART3_RX_BUFF[0]);
        }
        else if(!GPIO_ReadInputDataBit(TKPORT,TKD)){
            RS485_printf("D");
            OLED_Show8x16(2,4*8,'D');
            OLED_Show8x16(2,12*8,USART3_RX_BUFF[0]);
        }
    }
}
