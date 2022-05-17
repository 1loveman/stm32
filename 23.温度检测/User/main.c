#include"stm32f10x.h"
#include"delay.h"
#include"sys.h"
#include"i2c.h"
#include"TM1640.h"
#include"LM75.h"

int main(void){
    RCC_Configuration();
    I2C1_Configuration();
    TM1640_Init();
    TM1640_Show(0x04,20);
    TM1640_Show(0x05,20);
    TM1640_Show(0x06,20);
    TM1640_Show(0x07,20);
    while(1){
        u8 Temperature[3]={0};
        LM75_GetTemp(Temperature);
        TM1640_Show(0x00,Temperature[1]/10);
        TM1640_Show(0x01,Temperature[1]%10+10);
        TM1640_Show(0x02,Temperature[2]/10);
        TM1640_Show(0x03,Temperature[2]%10);

    }
}
