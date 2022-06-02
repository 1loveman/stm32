#include"adc.h"
 
vu16 ADC_DMA_IN[2];
void ADC_GPIO_Init(void){
    GPIO_InitTypeDef GPIO_InitS;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitS.GPIO_Pin=ADC_IN4|ADC_IN5;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_AIN;
    GPIO_Init(GPIOA,&GPIO_InitS);
}

void ADC_DMA_Init(void){
    DMA_InitTypeDef DMA_InitS;
    DMA_DeInit(DMA1_Channel1);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    DMA_InitS.DMA_PeripheralBaseAddr=ADC1_DR_ADDR;
    DMA_InitS.DMA_MemoryBaseAddr=(u32)ADC_DMA_IN;
    DMA_InitS.DMA_DIR=DMA_DIR_PeripheralSRC;
    DMA_InitS.DMA_BufferSize=2;
    DMA_InitS.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
    DMA_InitS.DMA_MemoryInc=DMA_MemoryInc_Enable;
    DMA_InitS.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
    DMA_InitS.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
    DMA_InitS.DMA_Mode=DMA_Mode_Circular;
    DMA_InitS.DMA_Priority=DMA_Priority_High;
    DMA_InitS.DMA_M2M=DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1,&DMA_InitS);
    DMA_Cmd(DMA1_Channel1,ENABLE);
}

void ADC_Configuration(void){
    ADC_GPIO_Init();
    ADC_DMA_Init();
    ADC_InitTypeDef ADC_InitS;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    
}