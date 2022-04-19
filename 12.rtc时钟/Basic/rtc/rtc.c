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
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32767);
	RTC_WaiteForLastTask();
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
		else if(RCC_GetFlagStatus(RCC_FLAG_PINRST)){ //
		
		}
		RCC_ClearFlag();
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC,DISABLE);
		RTC_WaitForLastTask();
	}
	#ifndef RCC_RTCClockOutput_Enable //
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	BKP_BackupAccessCmd(ENABLE);
	BKP_TamperPinCmd(DISABLE);	 //
	RCC_RTCOutputConfig(RTC_RTCOutputSource_CalibClock); //
	#endif
}
void RTC_IRQHandler(void){
	if(RTC_GetITStatus(RTC_IT_SEC)){
	
	}
	RTC_ClearITPendingBit(RTC_IT_SEC);
	RTC_WaiteForLastTask();	
}

void RTCAlarm_IRQHandler(void){
	if(RTC_GetITStatus(RTC_IT_ALR)){
	
	}
	RTC_ClearITPendingBit(RTC_IT_ALR);//
	RTC_WaiteForLastTask();	
}

u8 Is_Leap_Year(u16 year){
	if(year%4==0){
		if(year%100==0){
			if(year%400==0){
				return 1;
			}else return 0;
		}else return 1;
	}else return 0;
}

const u8 month[]={31,28,31,30,31,30,31,31,30,31,30,31};//平年
const u8 week[]={0,3,3,6,1,4,6,2,5,0,3,5}; 

u8 RTC_Set(u16 year,u8 mon,u8 day,u8 hour,u8 min,u8 sec){
	u8 i;
	u32 count=0;
	if(year<1970||year>2099)return 1;
	for(i=1970;i<year;i++){
		if(Is_Leap_Year(i)) count+=31622400;
		else count+=31536000;
	}
	for(i=0;i<mon-1;i++){
		count+=(u32)month[i]*86400;
		if(Is_Leap_Year(year)&&i==1)count+=86400;	
	}
	count+=(u32)(day-1)*86400;
	count+=(u32)(hour)*3600;
	count+=(u32)(min)*60;
	count+=(u32)sec;
	RTC_First_Config();
	BKP_WriteBackupRegister(BKP_DR1,0xA5A5);
	RTC_SetCounter(count);
	RTC_WaiteForLastTask();
	return 0;
}

u8 RTC_Get(void){
	u32 ncount=RTC_GetCounter();
	static u16 dcount=0;
	u16 t_year;
	u32 t_sdcount=ncount/86400;
	if(dcount!=t_sdcount){
		dcount=t_sdcount;
		t_year=1970;
		while(dcount>=365){
			if(Is_Leap_Year(t_year)){
				if(dcount>=366)dcount-=366;
				else{
					t_year++;
					break;
				}
			}
			else dcount-=365;
			t_year++;
		}
		ryear=t_year;
		u8 t_month=0;
		while(dcount>=28){
			if(Is_Leap_Year(t_year)){
				if(dcount>=29&&t_month=1)dcount-=(month[t_month]+1);
				else break;
			}
			else{
				if(dcount>=month[t_month])dcount-=month[t_month];
				else break;
			}
			t_month++;	
		}
		rmon=t_month+1;
		rday=dcount;
	}
	rhour=(u8)ncount%86400/3600;
	rmin=(u8)ncount%86400%3600/60;
	rsec=(u8)ncount%86400%3600%60;
	rweek=RTC_GetWeek(ryear,rmon,rday);
	return 0;
}

u8 RTC_GetWeek(u16 year,u8 mon,u8 day){
	u16 tmp;   //u8会溢出
	u8 yearH=year/100;
	u8 yearL=year%100;
	if(year>19)yearL+=100;
	tmp=yearL+yearL/4;
	tmp%=7;
	tmp=tmp+day+week[mon-1];
	if(yearL%4==0&&mon<3)tmp--;
	return (tmp%7);
}


















