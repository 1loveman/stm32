#include"rtc.h"

u16 ryear;
u8 rmon,rday,rhour,rmin,rsec,rweek;

void RTC_First_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSEConfig(RCC_LSE_ON);
	while(!RCC_GetFlagStatus(RCC_FLAG_LSERDY));
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaiteForSynchro();
	RTC_WaiteForLastTask();
	RTC_SetPrescaler(32767);
	RTC_WaiteForLastTask();
	RTC_ITConfig(RTC_IT_SEC,DISABLE);
	RTC_WaiteForLastTask();
}

void RTC_Config(void){
	if(BKP_ReadBackupRegister(BKP_DR1)!=0xA5A5){
		RTC_First_Config();
		BKP_WriteBackupRegister(BKP_DR1,0xA5A5);	
	}
	else{
	  	if(!RCC_GetFlagStatus(RCC_FLAG_PORRST)){
		
		}
		else if(!RCC_GetFlagStatus(RCC_FLAG_PINRST)){
		
		}
		RCC_ClearFlag();
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaiteForSynchro();
		RTC_WaiteForLastTask();
		RTC_ITConfig(RTC_IT_SEC,ENABLE);
		RTC_WaiteForLastTask();
		
	}
	#ifndef RCCCLKOutput_Enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_TamperPinCmd(DISABLE);
	BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
	#endif
	
}

void RTC_IRQHandler(void){
	if(RTC_GetITStatus(RTC_IT_SEC)){
	
	}
	RTC_ClearITpendingBit(RCC_IT_SEC);
	RTC_WriteForLastTask();	
}
void RTCAlarm_IRQHandler(void){
	if(RTC_GetITStatus(RTC_IT_ALR)){
	
	}
	RTC_ClearITPendingBit(RTC_IT_ALR);
	RTC_WriteForLastTask();
}

// «∑Ò»ÚƒÍ
u8 Is_Leap_Year(u16 year){
	if(year%4==0){
		if(year%100==0){
			if(year%400==0){
				return 1;
			}else{
				return 0;
			}
		}
		else{
			return 1;
		}
	}
	else{
		return 0;
	}
}