#include"delay.h"

void Delay_us(u32 us){
    SysTick->LOAD=AHB*us;
    SysTick->VAL=0X00;
    SysTick->CTRL=0X05;
    while(!(SysTick->CTRL&0X00010000));
    SysTick->CTRL=0X04;
}

void Delay_ms(u16 ms){
    while(ms--){
        Delay_us(1000);
    }
}

void Delay_s(u16 s){
    while(s--){
        Delay_ms(1000);
    }
}