#include"rtc.h"

void RTC_First_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB2Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSEConfig(RCC_LSE_ON);
	while(!RCC_GetFlagStatus(RCC_FLAG_LSERDY));//
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32767);
	RTC_WaitForLastTask();
	/*RTC_ITConfig(RTC_IT_SEC,DISABLE);
	RTC_WaitForLastTask();*/
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
		/*RTC_WaitForLastTask();
		RTC_ITConfig(RTC_IT_SEC,DISABLE);
		RTC_WaitForLastTask();*/
	}
#ifndef RTCClockOutput_Enable//
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_TamperPinCmd(DISABLE);//
	BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);//

#endif
}

void RTC_IRQHandler(void){
	if(RTC_GetITStatus(RTC_IT_SEC)){
	
	}
	RTC_ClearITPendingBit(RTC_IT_SEC);
	RTC_WaitForLastTask();
}

void RTCAlarm_IRQHandler(void){
	if(RTC_GetITStatus(RTC_IT_ALR)){
	
	}
	RTC_ClearITPendingBit(RTC_IT_ALR);
	RTC_WaitForLastTask();
}

u16 ryear;
u8 rmon,rday,rhour,rmin,rsec,rweek;
const u8 week_table[]={0,3,3,6,1,4,6,2,5,0,3,5};

u8 RTC_Get(void){
	u32 counter;
	u32 t_daycnt;
	u16 t_num;
	counter=RTC_GetCounter();
	t_daycnt=counter/86400;
	if(t_daycnt){
		t_num=1970;
		while(t_daycnt>=365){
			
		}
		ryear=t_year;
	}
	else{
		ryear=1970;
		rmon=1;
		rday=1;
	}
	rhour=counter%86400/3600;
	rmin=counter%86400%3600/60;
	rsec=counter%86400%3600%60;
	rweek=RTC_GetWeek(ryear,rmon,rday);
	return 0;	
}

u8 RTC_GetWeek(u16 year,u8 mon,u8 day){
	u8 yearH;
	u8 yearL;
	u16 tmp;
	yearH=year/100;
	yearL=year%100;
	if(yearH>19)yearL+=100;
	tmp=yearL+yearL/4;
	tmp=tmp%7;
	tmp=tmp+day+week_table[mon-1]
	if(!(yearL%4)&&mon<3)tmp--;
	return (tmp%7);
}