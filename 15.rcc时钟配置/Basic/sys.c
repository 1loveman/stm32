#include"sys.h"

void RCC_Configuration(void){
    //����ö�ٳ��������־
    ErrorStatus HSEStartupStatus;
    //��RCC�ڲ��Ĵ������ó�ȱʡֵ
    RCC_DeInit();
    //�����ⲿ����ʱ��
    RCC_HSEConfig(RCC_HSE_ON);
    //�ȴ�ʱ�ӿ�����������ֵд������־
    HSEStartupStatus=RCC_WaitForHSEStartup();
    //����ⲿ�������ɹ����������ϵͳʱ��
    if(HSEStartupStatus==SUCCESS){
        //����PLLʱ��
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
        //����AHB
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        //����APB1
        RCC_PCLK1Config(RCC_HCLK_Div2);
        //����APB2
        RCC_PCLK2Config(RCC_HCLK_Div1);
        //Ԥ��ȡ
        FLASH_SetLatency(FLASH_Latency_2);
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        //ʹ��PLLCLK
        RCC_PLLCmd(ENABLE);
        while(!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
        //����ϵͳʱ��
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while(RCC_GetSYSCLKSource()!=0X08);
    }
}