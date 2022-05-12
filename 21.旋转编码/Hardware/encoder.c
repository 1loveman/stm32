#include"encoder.h"

u16 lock;

void EC_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin=EC_LEFT|EC_PRESS;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(ECPORTA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=EC_RIGHT;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(ECPORTB,&GPIO_InitStructure);
}

u8 EC_Read(void){
    u8 ret=0;
    if(GPIO_ReadInputDataBit(ECPORTA,EC_LEFT))lock=0;
    if(!GPIO_ReadInputDataBit(ECPORTA,EC_PRESS)&&(!lock)){
        Delay_ms(20);
        if(!GPIO_ReadInputDataBit(ECPORTA,EC_PRESS)){
            while(!GPIO_ReadInputDataBit(ECPORTA,EC_PRESS));
            ret=2;
        }
    }else{
        if(!GPIO_ReadInputDataBit(ECPORTA,EC_LEFT)&&(!lock)){
            Delay_us(100);
            ret=GPIO_ReadInputDataBit(ECPORTB,EC_RIGHT);
            Delay_ms(3);
            if(!GPIO_ReadInputDataBit(ECPORTA,EC_LEFT)){
                if(ret)ret=3;
                else ret=1;
                while(!GPIO_ReadInputDataBit(ECPORTA,EC_LEFT)&&((lock++)<60000)){
                    Delay_us(20);
                }
                lock=lock<60000?0:1;
            }
        }
    }
    return ret;

}
