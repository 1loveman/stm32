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
    u8 r;
    u8 mp3=0;
    delay_ms(300);
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
            delay_ms(500);
            OLED_Show8x16Buf(6,0*8,"            ");
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK2)){
            MY1690_NEXT();
            OLED_Show8x16Buf(6,0*8,"----NEXT----");
            while(!GPIO_ReadInputDataBit(TKPORT,TK2));
            delay_ms(500);
            OLED_Show8x16Buf(6,0*8,"            ");
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK3)){
            MY1690_Cmd2(0x31,0x30);
            OLED_Show8x16Buf(6,0*8,"----VOLULE----");
            while(!GPIO_ReadInputDataBit(TKPORT,TK3));
            delay_ms(500);
            OLED_Show8x16Buf(6,0*8,"              ");
        }
        if(!GPIO_ReadInputDataBit(TKPORT,TK4)){
            MY1690_Stop();
            OLED_Show8x16Buf(6,0*8,"----STOP----");
            while(!GPIO_ReadInputDataBit(TKPORT,TK4));
            delay_ms(500);
            OLED_Show8x16Buf(6,0*8,"            ");
        }
        r=ROTARY_GetStaus();
        if(r==1)MY1690_VDOWN();
        if(r==3)MY1690_VUP();
        if(r==2){
            if(!mp3){
                mp3=1;
                MY1690_Play();
                OLED_Show8x16Buf(6,0*8,"----PLAY----");
                delay_ms(500);
                OLED_Show8x16Buf(6,0*8,"             ");
            }
            else{
                mp3=0;
                MY1690_Pause();
                OLED_Show8x16Buf(6,0*8,"----PAUSE----");
                delay_ms(500);
                OLED_Show8x16Buf(6,0*8,"             ");
            }
        }
        if(USART3_RX_STA==1){ 
            mp3=0;
            OLED_Show8x16Buf(6,0*8,"  -- STOP --    "); 
            USART3_RX_STA=0; 
        }else if(USART3_RX_STA==2){   
            USART3_RX_STA=0; 
        }
    }
}
