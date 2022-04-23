#ifndef __RTC_H__
#define __RTC_H__

#include"sys.h"

extern u16 ryear;
extern u8 rmon,rday,rhour,rmin,rsec,rweek;

void RTC_First_Config(void);
void RTC_Config(void);
u8 Is_Leap_Year(u16 year);
u8 RTC_Set(u16 year,u8 mon,u8 day,u8 hour,u8 min,u8 sec);
u8 RTC_Get(void);
u8 RTC_GetWeek(u16 year,u8 mon,u8 day);

#endif
