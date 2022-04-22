#include"rtc.h"

void RTC_First_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSEConfig(RCC_LSE_ON);
	while(!RCC_GetFlagStatus(RCC_FLAG_LSERDY));
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32767);
	RTC_WaitForLastTask();

}

void RTC_Config(void){
	if(BKP_ReadBackupRegister(BKP_DR1)!=0xA5A5){
		RTC_First_Config();
		BKP_WriteBackupRegister(BKP_DR1,0xA5A5);
	}
	else{
		if(RCC_GetFlagStatus(RCC_FLAG_PORRST)){
		
		}
		else if(RCC_GetFlagStatus(RCC_FLAG_PINRST)){
		
		}
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForSynchro();
	}
#ifndef RTCClockOutput_Enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_TamperPinCmd(DISABLE);
	BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);

#endif
}

u8 rmin,rsec;

u8 RTC_Get(void){
	u32 counter;
	counter=RTC_GetCounter();
	rmin=counter%86400%3600/60;
	rsec=counter%86400%3600%60;
	return 0;	
}

