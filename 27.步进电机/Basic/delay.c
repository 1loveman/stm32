#include"delay.h"

void delay_us(u32 us){
    SysTick->LOAD=AHB*us;
    SysTick->VAL=0X00;
    SysTick->CTRL=0X00000005;
    while(!(SysTick->CTRL&0X00010000));
    SysTick->CTRL=0X00000004;
}

void delay_ms(u16 ms){
    while(ms--){
        delay_us(1000);
    }
}

void delay_s(u16 s){
    while(s--){
        delay_ms(1000);
    }
}
