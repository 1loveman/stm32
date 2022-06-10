#include"sys.h"

void NVIC_Configuration(void){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

void RCC_Configuration(void){
    ErrorStatus HSEStart;
    RCC_HSEConfig(RCC_HSE_ON);
    HSEStart=RCC_WaitForHSEStartUp();
    if(HSEStart){
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);
        RCC_PCLK2Config(RCC_HCLK_Div1);

        FLASH_SetLatency(FLASH_Latency_2);
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        RCC_PLLCmd(ENABLE);
        while(!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while(RCC_GetSYSCLKSource()!=0x08);
    }
}
