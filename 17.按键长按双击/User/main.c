#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"led.h"
#include"touch_key.h"
#define LOAD1 50
#define LOAD2 10

int main(void){
    RCC_Configuration();
    LED_Init();
    TK_Init();
    while(1){
        u8 val1,val2;
        val1=0;
        val2=0;
        while(!GPIO_ReadInputDataBit(TKPORT,TK1)){
            while((!(GPIO_ReadInputDataBit(TKPORT,TK1)))&&((val1++)<LOAD1))delay_ms(20);
            if(val1>=LOAD1){
                //³¤°´
                GPIO_Write(LEDPORT,0X0000);
                while(!GPIO_ReadInputDataBit(TKPORT,TK1));
            }
            else{
                while(GPIO_ReadInputDataBit(TKPORT,TK1)&&((val2++)<LOAD2))delay_ms(20);
                if(val2>=LOAD2){
                    //µ¥»÷
                    GPIO_SetBits(LEDPORT,LED1);
                    while(!GPIO_ReadInputDataBit(TKPORT,TK1));
                }
                else{
                    //Ë«»÷
                    GPIO_Write(LEDPORT,0X0002);
                    while(!GPIO_ReadInputDataBit(TKPORT,TK1));
                }
            }
        }
    }
}
