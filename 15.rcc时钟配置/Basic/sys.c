#include"sys.h"

void RCC_Configuration(void){
    //定义枚举常量错误标志
    ErrorStatus HSEStartupStatus;
    //将RCC内部寄存器设置成缺省值
    RCC_DeInit();
    //开启外部高速时钟
    RCC_HSEConfig(RCC_HSE_ON);
    //等待时钟开启并将返回值写入错误标志
    HSEStartupStatus=RCC_WaitForHSEStartup();
    //如果外部晶振开启成功则继续配置系统时钟
    if(HSEStartupStatus==SUCCESS){
        //设置PLL时钟
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
        //设置AHB
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        //设置APB1
        RCC_PCLK1Config(RCC_HCLK_Div2);
        //设置APB2
        RCC_PCLK2Config(RCC_HCLK_Div1);
        //预存取
        FLASH_SetLatency(FLASH_Latency_2);
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        //使能PLLCLK
        RCC_PLLCmd(ENABLE);
        while(!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
        //设置系统时钟
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while(RCC_GetSYSCLKSource()!=0X08);
    }
}