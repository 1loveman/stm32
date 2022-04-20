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
	RTC_ITConfig(RTC_IT_SEC,DISABLE);
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
		RTC_WaitForLastTask();
		RTC_ITConfig(RTC_IT_SEC,DISABLE);
		RTC_WaitForLastTask();
	}
	#ifndef RTCCLKOutput_Enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_TamperPinCmd(DISABLE);
	BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
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

const u8 month_table[]={31,28,31,30,31,30,31,31,30,31,30,31}
const u8 week_table[]={0,3,3,6,1,4,6,2,5,0,3,5};

u8 Is_Leap_Year(u16 year){
	if(year%4==0){
		if(year%100==0){
			if(year%400==0)return 1;
			return 0;
		}
		return 1;
	}
	return 0;
}

u8 RTC_Set(u16 year,u8 mon,u8 day,u8 hour,u8 min,u8 sec){
	int i_mon;
	u16 t_year;
	u32 counter=0;
	if(year<2000||year>2099)return 1;
	for(t_year=1970;t_year<year;t_year++){
		counter+=31536000;
		if(Is_Leap_Yeat(t_year))counter+=86400;
	}
	for(i_mon=1;i_mon<mon;i_mon++){
		counter+=month_table[i-1]*86400;
		if(Is_Leap_Yeat(t_year)&&i_mon==2)counter+=86400;	
	}
	counter+=86400*(day-1);
	counter+=hour*3600;
	counter+=min*60;
	counter+=sec;
	//将BKP设置为缺省。


	RTC_SetCounter(counter);
	RTC_WaitForLastTask();
	return 0;
}

u8 RTC_Get(){
	u32 counter=RTC_GetCounter();
	u16 t_sday;
	u16 t_year;
	u8 t_mon;
	t_sday=counter/86400;
	if(t_sday){
		t_year=1970;
		while(t_sday>=365){
			if(Is_Leap_Yeat(t_year)){
				 if(t_sday>=366)t_sday-=366;
				 else{t_year++;break;}
			}
			else t_sday-=365;
			t_year++;	
		}
		ryear=t_year;
		t_mon=1;
		while(t_sday>=28){
			if(Is_Leap_Yeat(t_year)&&(t_mon==2)){
				if(t_sday>=29)t_sday-=29;
				else break;
			}
			else{
				if(t_sday>=month_table[t_mon-1])t_sday-=month_table[t_mon-1];
				else break;
			}
			t_mon--;
		}
		rmon=t_mon;
		rday=t_sday+1;
		rhour=counter%86400/3600;
		rmin=counter%86400%3600/60;
		rmin=counter%86400%3600%60;
		
	}
}

u8 RTC_GetWeek(u16 year,u8 mon,u8 day){
	u8 yearH=year/100;
	u8 yearL=year%100;
	u16 tmp;
	if(yearH>19)yearL+=100;
	tmp=yearL+yearL/4;
	tmp=tmp%7;
	tmp=tmp+day+week_table[mon-1];
	if(yearL%4==0&&mon<3)tmp--;
	return (tmp%7);
}





