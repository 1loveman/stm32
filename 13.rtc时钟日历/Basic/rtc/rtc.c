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
		/*RTC_ITConfig(RTC_IT_SEC,DISABLE);
		RTC_WaitForLastTask();*/
	}
#ifndef RTCClockOutput_Enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_TamperPinCmd(DISABLE);
	BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif
}

//

u16 ryear;
u8 rmon,rday,rhour,rmin,rsec,rweek;
const u8 mon_tab[]={31,28,31,30,31,30,31,31,30,31,30,31};
const u8 week_tab[]={0,3,3,6,1,4,6,2,5,0,3,5};

u8 Is_Leap_Year(u16 year){
	if(!(year%4)){
		if(!(year%100)){
			if(!(year%400))return 1;
			return 0;
		}return 1;
	}return 0;
}

u8 RTC_Set(u16 year,u8 mon,u8 day,u8 hour,u8 min,u8 sec){
	u32 counter;
	u16 t_num;
	counter=0;
	if(year<2000||year>2099)return 1;
	for(t_num=1970;t_num<year;t_num++){
		counter+=(86400*365);
		if(Is_Leap_Year(t_num))counter+=86400;
	}
	for(t_num=1;t_num<mon;t_num++){
		counter+=(86400*mon_tab[t_num-1]);
		if(Is_Leap_Year(year)&&t_num==2)counter+=86400;
	}
	while(1){
	
	}
	counter+=86400*(day-1);
	counter+=3600*hour;
	counter+=60*min;
	counter+=sec;
	RTC_SetCounter(counter);
	RTC_WaitForLastTask();
	return 0;	
}

u8 RTC_Get(void){
	u32 counter;
	u32 t_daycnt;
	u16 t_num;
	counter=RTC_GetCounter();
	t_daycnt=counter/86400;
	if(t_daycnt){
		t_num=1970;
		while(t_daycnt>=365){
			if(Is_Leap_Year(t_num)){
				if(t_daycnt>=366)t_daycnt-=366;
				else break;
			}
			else t_daycnt-=365;
			t_num++;
		}
		ryear=t_num;
		t_num=1;
		while(t_daycnt>=28){
			if(Is_Leap_Year(ryear)){
				if(t_daycnt>=29)t_daycnt-=29;
				else break;
			}
			else {
				if(t_daycnt>=mon_tab[t_num-1])t_daycnt-=mon_tab[t_num-1];
				else break;
			}
			t_num++;
		}
		rmon=t_num;
		rday=t_daycnt+1;//t_daycnt代表满的一天，所以获取到的时间需要加到第二天；
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
	tmp%=7;
	tmp=tmp+day+week_tab[mon-1];
	if(!(yearL%4)&&mon<3)tmp--;
	return (tmp%7);
}


