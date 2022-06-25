#ifndef __RTC_H__
#define __RTC_H__
#include"stm32f10x.h"

extern u16 rYear;
extern u8 rMon,rDay,rHour,rMin,rSec,rWeek;

void RTC_Init(void);
void RTC_Configuration(void);
u8 Is_Leep_Year(u16 ryear);
u8 RTC_SetTime(u16 ryear,u8 rmon,u8 rday,u8 rhour,u8 rmin,u8 rsec);
u8 RTC_GetWeek(u16 ryear,u8 rmon,u8 rday);
u8 RTC_GetTime(void);

#endif
