#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"TM1640.h"
#include"encoder.h"

int main(void){
    u8 num=0;
    RCC_Configuration();
    TM1640_Init();
    EC_Init();
    while(1){
        u8 flag;
        flag=EC_Read();
        switch(flag){
            case 1:{
                if(num==0)num=99;
                else num--;
            }
            break;
            case 2:num=0;
            break;
            case 3:{
                if(num==99)num=0;
                else num++;
            }
            break;
            default:
            break;
        }
        TM1640_Show(0,num/10);
        TM1640_Show(1,num%10);
    }
}
