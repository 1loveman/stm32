#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"i2c.h"
#include"usart.h"
#include"rtc.h"
#include"MY1690.h"
#include"OLED.h"
#include"TOUCH.h"

int main(void){
    delay_ms(400);
    RCC_Configuration();
    RTC_Configuration();
    TOUCH_Init();
    I2C1_Configuration();
    USART1_Init(115200);
    OLED_Init();
    MY1690_Init();
    OLED_Show8x16Buf(0,0*8,"RTC STRIKE");
    while(1){
        if(USART1_RX_STA&0Xc000){
            if((USART1_RX_STA&0X3FFF)==14){
                rYear=(USART1_RX_BUF[0]-0x30)*1000+(USART1_RX_BUF[1]-0x30)*100+(USART1_RX_BUF[2]-0x30)*10+(USART1_RX_BUF[3]-0x30);
                rMon=(USART1_RX_BUF[4]-0x30)*10+(USART1_RX_BUF[5]-0x30);
                rDay=(USART1_RX_BUF[6]-0x30)*10+(USART1_RX_BUF[7]-0x30);
                rHour=(USART1_RX_BUF[8]-0x30)*10+(USART1_RX_BUF[9]-0x30);
                rMin=(USART1_RX_BUF[10]-0x30)*10+(USART1_RX_BUF[11]-0x30);
                rSec=(USART1_RX_BUF[12]-0x30)*10+(USART1_RX_BUF[13]-0x30);
                RTC_SetTime(rYear,rMon,rDay,rHour,rMin,rSec);
                USART1_RX_STA=0;
            }
        }
        if(RTC_GetTime()){
            OLED_Show8x16(2,0*8,rHour/10+0x30);
            OLED_Show8x16(2,1*8,rHour%10+0x30);
            OLED_Show8x16(2,2*8,':');
            OLED_Show8x16(2,3*8,rMin/10+0x30);
            OLED_Show8x16(2,4*8,rMin%10+0x30);
            OLED_Show8x16(2,5*8,':');
            OLED_Show8x16(2,6*8,rSec/10+0x30);
            OLED_Show8x16(2,7*8,rSec%10+0x30);
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK1)){
            delay_ms(20);
            if(!GPIO_ReadInputDataBit(TKPORT,TK1)){
                MY1690_Cmd3(0X41,0X0015);
                if(!(rHour/10)){
                    
                }
                else if(rHour/10==1){
                    MY1690_Cmd3(0X41,0X0011);
                }
                else{
                    MY1690_Cmd3(0x41,rHour/10+1);
                    MY1690_Cmd3(0X41,0X0011);
                }
                if(!(rHour%10)&&(rHour/10)){

                }
                else{
                    MY1690_Cmd3(0X41,rHour%10+1);
                }
                MY1690_Cmd3(0X41,0X0014);

            }
        }
        
    }
}
