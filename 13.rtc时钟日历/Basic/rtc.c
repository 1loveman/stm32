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
    RTC_ITConfig(RTC_IT_SEC,DISABLE);
    RTC_WaitForLastTask();
}

void RTC_Config(void){
    if(BKP_ReadBackupRegister(BKP_DR1)!=0XA5A5){//
        RTC_First_Config();
        BKP_WriteBackupRegister(BKP_DR1,0XA5A5);//
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
    RTC_WaitForLastTask();
    RTC_ClearITPendingBit(RTC_IT_SEC);
    RTC_WaitForLastTask();
}

void RTCAlarm_IRQHandler(void){
    if(RTC_GetITStatus(RTC_IT_ALR)){

    }
    RTC_WaitForLastTask();
    RTC_ClearITPendingBit(RTC_IT_ALR);
    RTC_WaitForLastTask();
}


u16 ryear;
u8 rmon,rday,rhour,rmin,rsec,rweek;
const u8 mon_tab[]={31,28,31,30,31,30,31,31,30,31,30,31};
const u8 week_tab[]={0,3,3,6,1,4,6,2,5,0,3,5};

u8 Is_Leap_Year(u16 year){
    if(!(year%4)){
        if(!(year%100)){
            if(!(year%400))return 1;
            return 0;
        }
        return 1;
    }
    return 0;
}

u8 RTC_Set(u16 year,u8 mon,u8 day,u8 hour,u8 min,u8 sec){
    u32 counter=0;
    u16 t_num;
    if(year<2000||year>2099)return 1;
    t_num=1970;
    while(t_num<year){
        counter+=(86400*365);
        if(Is_Leap_Year(t_num))counter+=86400;
        t_num++;
    }
    t_num=1;
    while(t_num<mon){
        counter+=mon_tab[t_num-1]*86400;
        if(Is_Leap_Year(year)&&(t_num==2))counter+=86400;
		t_num++;
    }
    counter+=(day-1)*86400;
    counter+=hour*3600;
    counter+=min*60;
    counter+=sec;
    RTC_SetCounter(counter);
    RTC_WaitForLastTask();
	return 0;
}

u8 RTC_GetWeek(u16 year,u8 mon,u8 day){
    u8 yearH=year/100;
    u8 yearL=year%100;
    u16 tmp;
    if(yearH>19)yearL+=100;
    tmp=yearL+yearL/4;
    tmp%=7;
    tmp=tmp+day+week_tab[mon-1];
    if((!(yearL%4))&&(mon<3))tmp++;
    return (tmp%7);
}

u8 RTC_Get(void){
    u32 counter;
    u32 t_daycnt;
    u16 t_num;
    counter=RTC_GetCounter();
    t_daycnt=counter/86400;
    if(t_daycnt){
        t_num=1970;
        while(t_daycnt>=365){//
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
            if(Is_Leap_Year(ryear)&&(t_num==2)){
                if(t_daycnt>=29)t_daycnt-=29;
                else break;
            }
            else{
                if(t_daycnt>=mon_tab[t_num-1])t_daycnt-=mon_tab[t_num-1];
                else break;
            }
            t_num++;
        }
        rmon=t_num;
        rday=t_daycnt+1;
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

