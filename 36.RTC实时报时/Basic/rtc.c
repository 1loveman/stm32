#include"rtc.h"

u16 rYear;
u8 rMon,rDay,rHour,rMin,rSec,rWeek;
u8 Mon_Tab[]={31,28,31,30,31,30,31,31,30,31,30,31};
u8 Week_Tab[]={0,3,3,6,1,4,6,2,5,0,3,5};

void RTC_Init(void){
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

void RTC_Configuration(void){
    if(BKP_ReadBackupRegister(BKP_DR10)==0XA5A5){
        if(RCC_GetFlagStatus(RCC_FLAG_PORRST)){

        }
        else if(RCC_GetFlagStatus(RCC_FLAG_PINRST)){

        }
        RCC_RTCCLKCmd(ENABLE);
        RTC_WaitForSynchro();
    }
    else{
        RTC_Init();
        BKP_WriteBackupRegister(BKP_DR10,0XA5A5);
    }
    
    #ifndef RTCClockOutput_Enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    BKP_TamperPinCmd(DISABLE);
    BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
    #endif
}


u8 Is_Leep_Year(u16 ryear){
    if(!(ryear%4)){
        if(!(ryear%100)){
            if(ryear%400)return 0;
            return 1;
        }
        return 1;
    }
    return 0;
}
u8 RTC_SetTime(u16 ryear,u8 rmon,u8 rday,u8 rhour,u8 rmin,u8 rsec){
    u32 Count=0;
    u16 temp;
    if(ryear<1970||2099<ryear)return 0;
    for(temp=1970;temp<ryear;temp++){
        Count+=(86400*365);
        if(Is_Leep_Year(temp))Count+=86400;
    }
    for(temp=1;temp<rmon;temp++){
        Count+=(86400*Mon_Tab[temp-1]);
        if((Is_Leep_Year(ryear))&&(temp==2))Count+=86400;
    }
    Count+=(86400*(rday-1));
    Count+=(3600*rhour);
    Count+=(60*rmin);
    Count+=rsec;
    RTC_SetCounter(Count);
    RTC_WaitForLastTask();
    return 1;
}
u8 RTC_GetWeek(u16 ryear,u8 rmon,u8 rday){
    u8 ryearh=ryear/16;
    u8 ryearl=ryear%16;
    u16 temp;
    if(ryearh>19)ryearl+=100;
    temp=ryearl+ryearl/4;
    temp%=7;
    temp=temp+rday+Week_Tab[rmon-1];
    if(!(ryearl%4)&&(rmon<3))temp--;
    return (temp%7);

}
u8 RTC_GetTime(void){
    u32 Count=RTC_GetCounter();
    u32 tcount;
    u16 temp;
    tcount=Count/86400;
    if(tcount){
        for(temp=1970;tcount>=365;temp++){
            if(Is_Leep_Year(temp)){
                if(tcount>=366)tcount-=1;
                else break;
            }
            Count-=365;
        }
        rYear=temp;
        for(temp=1;tcount>=28;temp++){
            if(Is_Leep_Year(rYear)&&(temp==2)){
                if(tcount>=29)tcount-=1;
                else break;
            }
            if(tcount>=Mon_Tab[temp-1])tcount-=Mon_Tab[temp-1];
            else break;
        }
        rMon=temp;
        rDay=tcount+1;
    }
    rHour=(Count%86400)/3600;
    rMin=(Count%86400)%3600/60;
    rSec=(Count%86400)%3600%60;
    rWeek=RTC_GetWeek(rYear,rMon,rDay);
    return 1;
}
