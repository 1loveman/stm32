#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"rtc.h"
#include"TM1640.h"

int main(void){
    u8 c=0x01;
    RCC_Configuration();
    RTC_Config();
    TM1640_Init();
    while(1){
        if(!RTC_Get()){
            TM1640_Show(0,rday/10);
            TM1640_Show(1,rday%10+10);
            TM1640_Show(2,rhour/10);
            TM1640_Show(3,rhour%10+10);
            TM1640_Show(4,rmin/10);   
            TM1640_Show(5,rmin%10+10);
            TM1640_Show(6,rsec/10);
            TM1640_Show(7,rsec%10); 
        }
        TM1640_SLED(8,c);
        if(c==0x00)c=0x01;
        else c<<=1;
        Delay_s(1);
    }
}
