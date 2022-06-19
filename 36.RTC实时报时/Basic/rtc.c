#include"rtc.h"

u16 rYear;
u8 rMON,rDay,rHour,rMin,rSec,rWeek;

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
u8 RTC_SetTime(u16 ryear,u8 rmon,u8 rday,u8 hour,u8 rmin,u8 rsec,u8 rweek);
u8 RTC_GetWeek(u16 ryear,u8 rmon,u8 rday);
u8 RTC_GetTime(void);